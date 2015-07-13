// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_SyncCfgAction.h"
#include "../SP_Application.h"
#include "../SP_TimingModeRegion.h"
#include "../SP_Utilities.h"
#include "../SP_TimingRSIF.h"
#include <Blackboard/FC_BbAction.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Sync.h>
#include <Configuration/CFG_SyncSubApplication.h>
#include <Configuration/CFG_Ms.h>
#include <ErrorService/FC_Error.h>
#include <T6100_TelecomIf.h>
#include <T6100_CardIf.h>
#include <TsPii/TSPII_MsIf.h>
#include <TsPii/TSPII_SubApplication.h>

SP_SyncCfgAction::SP_SyncCfgAction(	
	SP_Application& theApplIf,
    SP_TimingModeRegion& theTimingModeRegion,
    SP_TimingRSIF& theTimingRSIF,
    CT_IntfId theMateTimingIntf):
    myAppIf(theApplIf),
	myTimingModeRegion(theTimingModeRegion),
    myTimingRSIF(theTimingRSIF),
    myMateTimingIntf(theMateTimingIntf)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&myTimingModeRegion);
}

//##ModelId=38EDF51800A6
SP_SyncCfgAction::~SP_SyncCfgAction()
{
	myBbAction->RemoveInputRegion(&myTimingModeRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_SyncCfgAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_SyncCfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	CFG_SyncSubApplication& theSyncApp = static_cast<CFG_SyncSubApplication&> (myAppIf.GetCardContext().GetSyncIf().GetCfgCardApp());
	CFG_Region* theSyncRegion = theSyncApp.GetAltCfgRegion();
	CFG_Sync& aCfgObject = static_cast<CFG_Sync&>((*theSyncRegion)[0]);

	CT_TEL_ClkMode theTimingMode = myTimingModeRegion[0].GetTimingMode();

	CT_TEL_TimingMode theConvMode;
	switch (theTimingMode)
	{
	case CT_TEL_CLKMODE_MASTER:
		theConvMode = CT_TEL_EXTERNAL_TIMING;
		break;
	case CT_TEL_CLKMODE_SLAVE:
		theConvMode = CT_TEL_MATE_TIMING;
		break;
	case CT_TEL_CLKMODE_HOLDOVER:
		theConvMode = CT_TEL_SELF_TIMING;
		break;
	default:
		theConvMode = CT_TEL_SELF_TIMING;
		break;
	}

	aCfgObject.SetTimingMode(theConvMode);
	
    theSyncRegion->IncModificationCounter();
    theSyncRegion->UpdateNotify();

    myTimingRSIF.SendLocalClockMode(theTimingMode);

    
    for (int i=0; i<myMSTimingCfgRegionList.size(); i++)
    {
        CFG_MsCfgRegion* theCfgMsCfgRegion = static_cast<CFG_MsCfgRegion*> (myMSTimingCfgRegionList[i]);
        if (theCfgMsCfgRegion->IsValid())
        {
            CFG_Ms& aCfgMsObj = (*theCfgMsCfgRegion)[0];

            //Read the hardware for current state.
            CT_TEL_MsTref curTrefConfig = (*myTSPIIRegionList[i])[0].GetAsTimingRef();
            CT_TEL_MsTref newTrefConfig = aCfgMsObj.GetRefType();

            if (aCfgMsObj.GetIsAutoTimingRedProv())
            {
                if (newTrefConfig == CT_TEL_MS_TREF_PRIMARY ||
                    newTrefConfig == CT_TEL_MS_TREF_SECONDARY)
                {
                
                    //If auto timing is provisioned, then look up the timing mode from earlier and use
                    //that to provision TSPII
                    if (theConvMode == CT_TEL_EXTERNAL_TIMING ||
                        theConvMode == CT_TEL_SELF_TIMING)
                    {
                        //Provision TSPII with this reference as master, and move on to the next one
                        (*myTSPIIRegionList[i])[0].SetAsTimingRef(newTrefConfig);
                    }
                    else if (theConvMode == CT_TEL_MATE_TIMING)
                    {
                        if (myMateTimingIntf != CT_INTF_ID_UNKNOWN)
                        {
                            //Configure as slave and bail
                            TSPII_MsRegion* theMsRegion = TSPII_SubApplication::GetInstance()->GetMs(GetTspiiIntfFromCTIntfId(myMateTimingIntf));
                            (*theMsRegion)[0].SetAsTimingRef(CT_TEL_MS_TREF_PRIMARY);
                            break;
                        }
                    }
                
                }
                else if (newTrefConfig == CT_TEL_MS_TREF_NONE)
                {
                    if (curTrefConfig != CT_TEL_MS_TREF_NONE)
                    {
                        //Deprovision in TSPII
                        (*myTSPIIRegionList[i])[0].SetAsTimingRef(newTrefConfig);
                    }
                }
            }
        }
    }
		
	return NULL;
}

void SP_SyncCfgAction::AddToRegionList(CFG_Region* theCfgRegion, TSPII_MsRegion* theTspiiRegion)
{
    if (theCfgRegion && theTspiiRegion)
    {
        myMSTimingCfgRegionList.push_back(theCfgRegion);
        myTSPIIRegionList.push_back(theTspiiRegion);
        myBbAction->AddInputRegion(theCfgRegion, false);
    }
}

void SP_SyncCfgAction::RemoveFromRegionList(CFG_Region* theCfgRegion)
{
    if (theCfgRegion)
    {
        myBbAction->RemoveInputRegion(theCfgRegion);
    }
}