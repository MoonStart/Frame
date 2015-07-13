// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SsmTransferAction.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_MainAppIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_ControllerStatusRegion.h>
#include <T6100_OscIf.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegion.h>
#include <SignalProtection/SP_1plus1ProtectionGroupConfig.h>
#include <SignalProtection/SP_1plus1ProtectionGroupStatus.h>
#include <SignalProtection/SP_SsmRegion.h>
#include <SignalProtection/SP_SystemTimingManager.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_T1E1Status.h>
#include <Monitoring/MON_MsStatus.h>
#include <Monitoring/MON_T1E1Status.h>
#include <Monitoring/MON_Region.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <CSM/CSM_ConfigStatus.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_SP_SwitchingPriority.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_T1E1.h>
#include <Configuration/CFG_AppIf.h>



//##ModelId=3BBC9B0F02A0
SP_SsmTransferAction::SP_SsmTransferAction(SP_ProtectionGroupConfigRegion* theConfigRegion, SP_SsmRegion* theSsmRegion, SP_SystemTimingManager* theTimingManager):
myConfigRegion(theConfigRegion),
mySsmRegion(theSsmRegion),
myTimingManager(theTimingManager),
stopped(false)
{
    myBbAction = new FC_BbAction(this);
	myBbAction->AddInputRegion(theConfigRegion);
	myMonRegion.working = myMonRegion.protection = NULL;
	myStatusRegion.working = myStatusRegion.protection = NULL;
    myCfgRegion.working = myCfgRegion.protection = NULL;
	myBbAction->AddOutputRegion(theSsmRegion);
}

//##ModelId=38EDF51800A6
SP_SsmTransferAction::~SP_SsmTransferAction()
{
	if (myConfigRegion)
	    myBbAction->RemoveInputRegion(myConfigRegion);
	if (mySsmRegion)
        myBbAction->RemoveOutputRegion(mySsmRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_SsmTransferAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_SsmTransferAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

	//If input regions exist, then collect SSM from these locations and populate output region
    CT_FAC_RxSsm theRxSsm = CT_RxSsm_ALL;
	bool hasChanged = false;
	MON_MsStatus* aMsMonitoringStatusObject = NULL;
	MON_T1E1Status* aT1E1MonitoringStatusObject = NULL;
    CFG_T1E1* aT1E1CfgObject = NULL;

    if (myMonRegion.working != NULL)
	{
		if (myMonRegion.working->IsValid())
		{
			if (myProtCfgCopy.GetSources().working.GetPortType() == FAC_SUBTYPE_T1)
			{
				if (myProtCfgCopy.GetState() == CT_SP_DEFAULT_CONFIG_STATE)
				{
					theRxSsm = GetFreeRunSsm(myProtCfgCopy.GetFacilityStandard());
				}
				else
				{
					aT1E1MonitoringStatusObject = static_cast<MON_T1E1Status*>(&((*myMonRegion.working)[0]));
					theRxSsm = aT1E1MonitoringStatusObject->GetRxSsm();
					//Check whether there is an SSM override configured
					aT1E1CfgObject = static_cast<CFG_T1E1*>(&((*myCfgRegion.working)[0]));
					if (aT1E1CfgObject->GetQualityLevelOverride() != CT_QualityLevelOverride_DISABLED)
					{
						theRxSsm = CT_SP_SwitchingPriority::GetSsmQLFromQLOverride(aT1E1CfgObject->GetQualityLevelOverride());
					}
				}
			}
			else
			{
				aMsMonitoringStatusObject = static_cast<MON_MsStatus*>(&((*myMonRegion.working)[0]));
		        theRxSsm = aMsMonitoringStatusObject->GetRxSsm();
			}
			//Copy from MON region to signal protect region
			hasChanged |= (*mySsmRegion)[0].SetSsmValue(CT_SP_WORKING_SIDE, myProtCfgCopy.GetSources().working, theRxSsm, true);
		}
		else
		{
			hasChanged |= (*mySsmRegion)[0].Reset(CT_SP_WORKING_SIDE);	
		}
	}

	if (myMonRegion.protection != NULL)
	{
		if (myMonRegion.protection->IsValid())
		{
			//Copy from MON region to signal protect region
			if (myProtCfgCopy.GetSources().protection.GetPortType() == FAC_SUBTYPE_T1)
			{
				if (myProtCfgCopy.GetState() == CT_SP_DEFAULT_CONFIG_STATE)
				{
					theRxSsm = GetFreeRunSsm(myProtCfgCopy.GetFacilityStandard());
				}
				else
				{
					aT1E1MonitoringStatusObject = static_cast<MON_T1E1Status*>(&((*myMonRegion.protection)[0]));
					theRxSsm = aT1E1MonitoringStatusObject->GetRxSsm();
					aT1E1CfgObject = static_cast<CFG_T1E1*>(&((*myCfgRegion.protection)[0]));
					if (aT1E1CfgObject->GetQualityLevelOverride() != CT_QualityLevelOverride_DISABLED)
					{
						theRxSsm = CT_SP_SwitchingPriority::GetSsmQLFromQLOverride(aT1E1CfgObject->GetQualityLevelOverride());
					}
				}
			}
			else
			{
				aMsMonitoringStatusObject = static_cast<MON_MsStatus*>(&((*myMonRegion.protection)[0]));
		        theRxSsm = aMsMonitoringStatusObject->GetRxSsm();
			}
			hasChanged |= (*mySsmRegion)[0].SetSsmValue(CT_SP_PROTECTION_SIDE, myProtCfgCopy.GetSources().protection, theRxSsm, true);
		}
		else
		{
			hasChanged |= (*mySsmRegion)[0].Reset(CT_SP_PROTECTION_SIDE);	
		}
	}

	if (myStatusRegion.working != NULL && myStatusRegion.protection != NULL)
	{
		if (!myProtCfgCopy.GetSources().working.IsDefault())
		{
		    SP_ProtectionGroupStatusRegion* protStatusReg = myTimingManager->GetStatusRegion(myProtCfgCopy.GetSources());
			if (protStatusReg)
			{
				if (protStatusReg->IsValid())
				{
                    CT_SP_Protection theSelectedSide;
				    SP_1plus1ProtectionGroupStatus& theStatusObject = static_cast<SP_1plus1ProtectionGroupStatus&>( (*protStatusReg)[0]);
                    theSelectedSide = theStatusObject.GetSelectedSide();
                    if (theStatusObject.GetSelectedSideUsable() == false)
                    {
                        theSelectedSide = CT_SP_INVALID_PROTECTION_SIDE;
                    }
				    hasChanged |= (*mySsmRegion)[0].SetSelectedSide(theSelectedSide);
				}
				else
				{
					hasChanged |= (*mySsmRegion)[0].SetSelectedSide(CT_SP_INVALID_PROTECTION_SIDE);
				}
			}
		}
	}

	if (hasChanged)
		mySsmRegion->IncModificationCounter();

    return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
bool SP_SsmTransferAction::AddInputs(CT_SP_ProtectionPair<CT_Port> & theSources)
{
	MON_Region* theMonRegion = NULL;
    CFG_Region* theCfgRegion = NULL;

	CT_ShelfId workingShelf = theSources.working.GetShelfId();
	CT_SlotId workingSlot = theSources.working.GetSlotId();
	CT_IntfId workingPort = theSources.working.GetPortId();
	CT_FacilitySubType workingPortType = theSources.working.GetPortType();

	CT_ShelfId protectShelf = theSources.protection.GetShelfId();
	CT_SlotId protectSlot = theSources.protection.GetSlotId();
	CT_IntfId protectPort = theSources.protection.GetPortId();
	CT_FacilitySubType protectPortType = theSources.protection.GetPortType();

	bool isWorkingDefault = theSources.working.IsDefault();
	bool isProtectDefault = theSources.protection.IsDefault();

	bool isReady = true;

	if (!isWorkingDefault && myMonRegion.working == NULL)
	{
		//Get the appropriate mon region and add as input
		//Check if these are T1 or derived
		if (workingPortType == FAC_SUBTYPE_T1)
		{
			//This is a T1 fac
			if (workingPort == CT_LINE_SIDE_5)
            {
				theMonRegion = T6100_MainAppIf::Instance().GetT1E1PriIf().GetMonPortApp(CT_SIDE_A).GetStatusRegion();
                theCfgRegion = T6100_MainAppIf::Instance().GetT1E1PriIf().GetCfgPortApp(CT_SIDE_A).GetCfgRegion();
            }
			else if (workingPort == CT_LINE_SIDE_6)
            {
				theMonRegion = T6100_MainAppIf::Instance().GetT1E1SecIf().GetMonPortApp(CT_SIDE_B).GetStatusRegion();
                theCfgRegion = T6100_MainAppIf::Instance().GetT1E1SecIf().GetCfgPortApp(CT_SIDE_B).GetCfgRegion();
            }
		}
        else if (workingPortType == FAC_SUBTYPE_OSC)
        {
            CT_Side theSide = GetSideFromPort(workingShelf, workingPort);
            CT_SlotId theCtrlSlot = T6100_MainAppIf::Instance().GetControllerStatusRegion()->GetOscSlotFromSide(theSide);
            //This is a OSC fac
			theMonRegion = T6100_MainAppIf::Instance().GetShelfPtr(workingShelf)->GetSlotPtr(theCtrlSlot)->GetCardPtr(OSC_FAM)->GetMsIfPtr()->GetMonLineApp(theSide).GetStatusRegion();
        }
		else
		{
			//Derived timing. Find the appropriate facility add the input region
			T6100_ShelfIf* theShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(workingShelf);
			if (theShelfPtr)
			{
				T6100_SlotIf* theSlotPtr = theShelfPtr->GetSlotPtr(workingSlot);
				if (theSlotPtr)
				{
					CSM_CardConfigStatusRegion& theCsmRegion = theSlotPtr->GetCsmApp().GetCardConfigStatusRegion();
				    CSM_PersistentConfigStatus*  aCSMPtr = &(theCsmRegion[0]);

                    CT_CardFamily theCurCardFam = UNKNOWN_FAM;
                    if(aCSMPtr->IsCardProvisionned() == true)
					{
		                list<CT_PartNumber>* aPnList = aCSMPtr->GetProvisionConfigList();
		                theCurCardFam = aPnList->front().GetCardFamily();
					}
					else
					{
						//Region not ready yet, tell the timing manager to call back when it is
						myTimingManager->AddInput(&theCsmRegion, CT_SP_WORKING_SIDE);
						isReady = false;
					}
					if (theCurCardFam != UNKNOWN_FAM)
					{
						T6100_CardIf* theCardPtr = theSlotPtr->GetCardPtr(SC_FAM);
						if (theCardPtr)
						{
							switch (workingPort)
							{
							case CT_LINE_SIDE_1:
								theMonRegion = theCardPtr->GetMsIfPtr()->GetMonLineSideApp(CT_LINE_SIDE_0).GetStatusRegion();
								break;
							default:
								break;
							}

							if (IsPortFacility(workingPort))
							{
								theMonRegion = theCardPtr->GetMsIfPtr()->GetMonPortSideApp(workingPort).GetStatusRegion();
							}
						}
					}
				}
			}
			
		}


		if (theMonRegion !=NULL)
		{
		    myMonRegion.working = theMonRegion;
		    myBbAction->AddInputRegion(myMonRegion.working, false);
		}
        if (theCfgRegion != NULL)
        {
            myCfgRegion.working = theCfgRegion;
            myBbAction->AddInputRegion(myCfgRegion.working);
        }
	}

	theMonRegion = NULL;
    theCfgRegion = NULL;
	if (!isProtectDefault && myMonRegion.protection == NULL)
	{
		if (protectPortType == FAC_SUBTYPE_T1)
		{
			//This is a T1 fac
			if (protectPort == CT_LINE_SIDE_5)
            {
				theMonRegion = T6100_MainAppIf::Instance().GetT1E1PriIf().GetMonPortApp(CT_SIDE_A).GetStatusRegion();
                theCfgRegion = T6100_MainAppIf::Instance().GetT1E1PriIf().GetCfgPortApp(CT_SIDE_A).GetCfgRegion();
            }
			else if (protectPort == CT_LINE_SIDE_6)
            {
				theMonRegion = T6100_MainAppIf::Instance().GetT1E1SecIf().GetMonPortApp(CT_SIDE_B).GetStatusRegion();
                theCfgRegion = T6100_MainAppIf::Instance().GetT1E1SecIf().GetCfgPortApp(CT_SIDE_B).GetCfgRegion();
            }
		}
        else if (protectPortType == FAC_SUBTYPE_OSC)
        {
            CT_Side theSide = GetSideFromPort(protectShelf, protectPort);
            CT_SlotId theCtrlSlot = T6100_MainAppIf::Instance().GetControllerStatusRegion()->GetOscSlotFromSide(theSide);
            //This is a OSC fac
			theMonRegion = T6100_MainAppIf::Instance().GetShelfPtr(protectShelf)->GetSlotPtr(theCtrlSlot)->GetCardPtr(OSC_FAM)->GetMsIfPtr()->GetMonLineApp(theSide).GetStatusRegion();
        }
		else
		{
			//Derived timing. Find the appropriate facility add the input region
			T6100_ShelfIf* theShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(protectShelf);
			if (theShelfPtr)
			{
				T6100_SlotIf* theSlotPtr = theShelfPtr->GetSlotPtr(protectSlot);
				if (theSlotPtr)
				{
					CSM_CardConfigStatusRegion& theCsmRegion = theSlotPtr->GetCsmApp().GetCardConfigStatusRegion();
				    CSM_PersistentConfigStatus*  aCSMPtr = &(theCsmRegion[0]);

                    CT_CardFamily theCurCardFam = UNKNOWN_FAM;
                    if(aCSMPtr->IsCardProvisionned() == true)
					{
		                list<CT_PartNumber>* aPnList = aCSMPtr->GetProvisionConfigList();
		                theCurCardFam = aPnList->front().GetCardFamily();
					}
					else
					{
						//Region not ready yet, tell the timing manager to call back when it is
						myTimingManager->AddInput(&theCsmRegion, CT_SP_PROTECTION_SIDE);
						isReady = false;
					}
					if (theCurCardFam != UNKNOWN_FAM)
					{
						T6100_CardIf* theCardPtr = theSlotPtr->GetCardPtr(SC_FAM);
						if (theCardPtr)
						{
						    switch (protectPort)
							{
							case CT_LINE_SIDE_1:
								theMonRegion = theCardPtr->GetMsIfPtr()->GetMonLineSideApp(CT_LINE_SIDE_0).GetStatusRegion();
								break;
							default:
								break;
							}

							if (IsPortFacility(protectPort))
							{
								theMonRegion = theCardPtr->GetMsIfPtr()->GetMonPortSideApp(protectPort).GetStatusRegion();
							}
						}
					}
				}
			}
			
		}


        if (theMonRegion != NULL)
		{
		    //Get the appropriate mon region and add as input
		    myMonRegion.protection = theMonRegion;
		    myBbAction->AddInputRegion(myMonRegion.protection, false);
		}

        if (theCfgRegion != NULL)
        {
            myCfgRegion.protection = theCfgRegion;
            myBbAction->AddInputRegion(myCfgRegion.protection);
        }
	}

	return isReady;

}
void SP_SsmTransferAction::RemoveInputs()
{
	if (myMonRegion.working != NULL)
	    myBbAction->RemoveInputRegion(myMonRegion.working);
	myMonRegion.working= NULL;

	if (myMonRegion.protection != NULL)
	    myBbAction->RemoveInputRegion(myMonRegion.protection);
	myMonRegion.protection= NULL;

    if (myCfgRegion.working != NULL)
        myBbAction->RemoveInputRegion(myCfgRegion.working);
    myCfgRegion.working = NULL;

    if (myCfgRegion.protection != NULL)
        myBbAction->RemoveInputRegion(myCfgRegion.protection);
    myCfgRegion.protection = NULL;
}

bool SP_SsmTransferAction::IsProtectionGroupDifferent(SP_1plus1ProtectionGroupConfig& aConfig)
{
	if (myProtCfgCopy.InUse() != aConfig.InUse() ||
		myProtCfgCopy.GetState() != aConfig.GetState() ||
        myProtCfgCopy.Get1plus1Type() != aConfig.Get1plus1Type() ||
		myProtCfgCopy.GetSources().working != aConfig.GetSources().working ||
		myProtCfgCopy.GetSources().protection != aConfig.GetSources().protection)
	{
		return true;
	}
	else
		return false;
}

void SP_SsmTransferAction::CopyConfiguration(SP_1plus1ProtectionGroupConfig& theConfig)
{
	myProtCfgCopy = theConfig;
}

void SP_SsmTransferAction::AddStatusInputs(CT_SP_ProtectionPair<CT_Port> & theSources)
{
	if (myStatusRegion.working == NULL && myStatusRegion.protection == NULL)
	{
		CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
		bool isHw4 = aSubNodeCfg.IsCtrlHwVer4(CSPII_CardIF::GetInstance()->GetCardType());
		bool isHw5 = aSubNodeCfg.IsCtrlHwVer5(CSPII_CardIF::GetInstance()->GetCardType());
		if (isHw4  || isHw5)
		{
			CT_ShelfId ctrlShelf1 = theSources.working.GetShelfId();
			CT_ShelfId ctrlShelf2 = theSources.working.GetShelfId(); //Set equal to working since NANO derived sources always come from the same shelf
			if (isHw5)
			{
				//Both set to first main shelf since the master timing source is on the main shelf
                ctrlShelf1 = OPTICAL_SHELF_1;
				ctrlShelf2 = OPTICAL_SHELF_1;
			}
	        CT_SlotId ctrlSlot1;
            CT_SlotId ctrlSlot2;
	        aSubNodeCfg.GetCtrlSlots(ctrlSlot1, ctrlSlot2);

		    SP_ProtectionGroupStatusRegion& theStatusRegion = T6100_MainAppIf::Instance().GetShelfPtr(ctrlShelf1)->GetSlotPtr(ctrlSlot1)->GetCardPtr(OSC_FAM)->GetSyncProtectionIf().GetSyncProtectionApp().GetStatusRegion();
		    myStatusRegion.working =  (&theStatusRegion);

	        SP_ProtectionGroupStatusRegion& theStatusRegion2 = T6100_MainAppIf::Instance().GetShelfPtr(ctrlShelf2)->GetSlotPtr(ctrlSlot2)->GetCardPtr(OSC_FAM)->GetSyncProtectionIf().GetSyncProtectionApp().GetStatusRegion();
		    myStatusRegion.protection =  (&theStatusRegion2);

		    myBbAction->AddInputRegion(myStatusRegion.working, false);
		    myBbAction->AddInputRegion(myStatusRegion.protection, false);
		}
	}
}
void SP_SsmTransferAction::RemoveStatusInputs()
{
	if (myStatusRegion.working != NULL) 
	{
		myBbAction->RemoveInputRegion(myStatusRegion.working);
		myStatusRegion.working = NULL;
	}

	if (myStatusRegion.protection != NULL)
	{
		myBbAction->RemoveInputRegion(myStatusRegion.protection);
		myStatusRegion.protection = NULL;
	}
}

CT_Side SP_SsmTransferAction::GetSideFromPort(CT_ShelfId theShelf, CT_IntfId thePort)
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    CT_Side aSide = CT_SIDE_UNKNOWN;

    if (NANO_SBOADM_CH88_N_S == aSubNodeCfg)
    {
        if (OPTICAL_SHELF_2 == theShelf)
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_G; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_H; break;
              default:                  break;
            }
        }
        else
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_A; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_B; break;
              case CT_LINE_SIDE_9:      aSide = CT_SIDE_C; break;
              case CT_LINE_SIDE_10:      aSide = CT_SIDE_D; break;
              case CT_LINE_SIDE_11:      aSide = CT_SIDE_E; break;
              case CT_LINE_SIDE_12:      aSide = CT_SIDE_F; break;
              default:                  break;
            }
        }
    }
    else if (NANO_SBOADM_CH88_N == aSubNodeCfg)
    {
        if (OPTICAL_SHELF_1 == theShelf)
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_A; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_B; break;
              default:                  break;
            }
        }
        else if (OPTICAL_SHELF_2 == theShelf)
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_C; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_D; break;
              default:                  break;
            }
        }
        else if (OPTICAL_SHELF_3 == theShelf)
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_E; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_F; break;
              default:                  break;
            }
        }
        else if (OPTICAL_SHELF_4 == theShelf)
        {
            switch (thePort)
            {
              case CT_LINE_SIDE_7:      aSide = CT_SIDE_G; break;
              case CT_LINE_SIDE_8:      aSide = CT_SIDE_H; break;
              default:                  break;
            }
        }
    }
    else
    {
       aSide = (thePort == CT_LINE_SIDE_7 ? CT_SIDE_A : CT_SIDE_B);
    }

    return aSide;
}
