// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <CommonTypes/CT_SP_CommandType.h>
#include <CommonTypes/CT_Port.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_MainAppIf.h>
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_1plus1Selector.h"
#include "../SP_1plus1DefectProcessorAction.h"
#include "../SP_SsmRegion.h"
#include "../SP_TestMenu.h"
#include "../SP_Utilities.h"
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include <SignalProtection/SP_SystemTimingBaseApplication.h>
#include <Blackboard/FC_BbAction.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_MsDefects.h>
#include <Monitoring/MON_MsStatus.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OduStatus.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_HopDefects.h>
#include <Monitoring/MON_HopStatus.h>
#include <Monitoring/MON_VcgDefects.h>
#include <Monitoring/MON_T1E1Status.h>
#include <ExecutionSupport/FC_EventLogger.h>
#include <CsPii/CSPII_CardIF.h>


//add other include files for other layers as needed


//##ModelId=3BBC9B390387
SP_1plus1DefectProcessorAction::SP_1plus1DefectProcessorAction(	
		SP_ProtectionLayer theLayer,
		SP_ProtectionSide theSide,
		SP_Application& theApplIf,
		CT_IntfId thePortId) :
		SP_DefectProcessorAction(theLayer, theSide, theApplIf, thePortId)
		
{
    
}

//##ModelId=3BBC9B3903A4
SP_1plus1DefectProcessorAction::~SP_1plus1DefectProcessorAction()
{
}

void SP_1plus1DefectProcessorAction::RegisterForDefects(SP_ProtectionAction* theProtectionAction, 
		                                                CT_ShelfId theWShelf, CT_SlotId theWSlot, CT_IntfId theWFacility, 
									                    CT_ShelfId thePShelf, CT_SlotId thePSlot, CT_IntfId thePFacility)
{
	bool valid = true;
	bool lookup = true;
	bool sharedSystemRegion = false;
    bool sharedShelfRegion = false;

	SP_1plus1ProtectionAction * the1plus1ProtectionAction = dynamic_cast<SP_1plus1ProtectionAction*> (theProtectionAction);
	//Register for defects
	

	// if the defect processor is already monitoring, skip the region retrieval process
	// This can happen for UPSR/SNCP where multiple protection schemes are monitoring the same region
	if (myMonDefectsRegion.working == NULL)
	{
		myMonDefectsRegion.working          =  GetMONDefectRegion(theWShelf, theWSlot, theWFacility);
		myMonDefectsRegion.protection       =  GetMONDefectRegion(thePShelf, thePSlot, thePFacility);
		myMonStatusRegion.working           =  GetMONStatusRegion(theWShelf, theWSlot, theWFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());
		myMonStatusRegion.protection        =  GetMONStatusRegion(thePShelf, thePSlot, thePFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());
		mySpSystemStatusRegion.working      =  GetSPSystemStatusRegion(theWFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());
		mySpSystemStatusRegion.protection   =  GetSPSystemStatusRegion(thePFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());
        mySpShelfStatusRegion.working       =  GetSPShelfStatusRegion(theWFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());
		mySpShelfStatusRegion.protection    =  GetSPShelfStatusRegion(thePFacility, the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType());

		//If the working shelf/slot/fac is the same as protect shelf/slot/fac, then no need to add/remove inputs twice so clear out protection info
		if (theWShelf == thePShelf &&
			theWSlot == thePSlot &&
			theWFacility == thePFacility)
		{
            myMonDefectsRegion.protection = NULL;
			myMonStatusRegion.protection = NULL;
		}

	    if (myLayer == SP_MS)
		{
	    	FC_THROW_ERROR_IF(dynamic_cast<MON_MsDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_MsDefects objects");
            FC_THROW_ERROR_IF(dynamic_cast<MON_MsStatus*>(&((*myMonStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_MsStatus objects");

	
		}
	    else if (myLayer == SP_ODU)
		{
		    FC_THROW_ERROR_IF(dynamic_cast<MON_OduDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_OduDefects objects");
            FC_THROW_ERROR_IF(dynamic_cast<MON_OduStatus*>(&((*myMonStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_OduStatus objects");
		}
	    else if (myLayer == SP_OPT)
		{
		    FC_THROW_ERROR_IF(dynamic_cast<MON_OptDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_OduDefects objects");
            FC_THROW_ERROR_IF(dynamic_cast<MON_OptStatus*>(&((*myMonStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_OptStatus objects");
		}
	    else if (myLayer == SP_SYNC)
		{
		    FC_THROW_ERROR_IF(dynamic_cast<MON_MsDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_MsDefects objects");

			if (the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_OPSM ||
                the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_LINE)
			{
                FC_THROW_ERROR_IF(dynamic_cast<MON_MsStatus*>(&((*myMonStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_MsStatus objects");
			}
			else if (the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SYS ||
				     the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SLAVE)
			{
				FC_THROW_ERROR_IF(dynamic_cast<SP_SsmValue*>(&((*mySpSystemStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting SP_SsmValue objects");
                FC_THROW_ERROR_IF(dynamic_cast<SP_SsmValue*>(&((*mySpShelfStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting SP_SsmValue objects");
			}

		}
	    else if (myLayer == SP_HOP)
		{
		    FC_THROW_ERROR_IF(dynamic_cast<MON_HopDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_HopDefects objects");
            FC_THROW_ERROR_IF(dynamic_cast<MON_HopStatus*>(&((*myMonStatusRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_HopStatus objects");
		}
	    else if (myLayer == SP_VCG)
		{
		    FC_THROW_ERROR_IF(dynamic_cast<MON_VcgDefects*>(&((*myMonDefectsRegion.working)[0]))==NULL,
                      FC_RuntimeError,
                      "Expecting MON_VcgDefects objects");
		}
	    else
		{
	    	//unknown protection layer
		    valid = false;
		}
	}
	else
	{
		lookup = false; //didnt lookup a mon region. Region has already been looked up
	}
	

	if (valid)
	{
		if (lookup)
		{
		    //the defect or status regions could be null
		    //if a sync protection scheme observer
			//register as a low priority observer
			//else register as a high priority observer
			if (myLayer == SP_SYNC)
			{
		        //the defect or status regions could be null
		        if (myMonDefectsRegion.working != NULL)
	                GetBbAction()->AddInputRegion(myMonDefectsRegion.working);
		        if (myMonStatusRegion.working != NULL)
				{
					GetBbAction()->AddInputRegion(myMonStatusRegion.working);
				}

                if (the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SYS ||
				    the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SLAVE)
				{
				    if (mySpSystemStatusRegion.working != NULL)
				    {
						//For system or system derived slave timing, the status region is transferred from the SPM. In order to allow
						//the protection scheme to be up and running prior to the SPM being ready, we bypass
						//region validity check and disable switching based on SSM until the SPM is ready.
                        GetBbAction()->AddInputRegion(mySpSystemStatusRegion.working, false);
						sharedSystemRegion = true;
					}
				    if (mySpShelfStatusRegion.working != NULL)
                    {
                        //For system or system derived slave timing, the status region is transferred from the SPM. In order to allow
						//the protection scheme to be up and running prior to the SPM being ready, we bypass
						//region validity check and disable switching based on SSM until the SPM is ready.
                        GetBbAction()->AddInputRegion(mySpShelfStatusRegion.working, false);
                        sharedShelfRegion = true;
                    }
                }
		        if (myMonDefectsRegion.protection != NULL)
		            GetBbAction()->AddInputRegion(myMonDefectsRegion.protection);
		        if (myMonStatusRegion.protection != NULL)
				{
					GetBbAction()->AddInputRegion(myMonStatusRegion.protection);
				}
				
			    if (the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SYS ||
					the1plus1ProtectionAction->Get1plus1Config().Get1plus1SubType() == CT_SP_EXT_SLAVE)
				{
                    if (mySpSystemStatusRegion.protection != NULL && !sharedSystemRegion)
				    {
						//For system or system derived slave timing, the status region is transferred from the SPM. In order to allow
						//the protection scheme to be up and running prior to the SPM being ready, we bypass
						//region validity check and disable switching based on SSM until the SPM is ready.
                        GetBbAction()->AddInputRegion(mySpSystemStatusRegion.protection, false);
                    }
                    if (mySpShelfStatusRegion.protection != NULL && !sharedShelfRegion)
				    {
                        //For system or system derived slave timing, the status region is transferred from the SPM. In order to allow
						//the protection scheme to be up and running prior to the SPM being ready, we bypass
						//region validity check and disable switching based on SSM until the SPM is ready.
                        GetBbAction()->AddInputRegion(mySpShelfStatusRegion.protection, false);
					}
				}
			}
			else
			{
				//the defect or status regions could be null
		        if (myMonDefectsRegion.working != NULL)
	                GetBbAction()->AddInputRegion(myMonDefectsRegion.working, true, true, true, FC_BbRegObsPriority::HIGH);
		        if (myMonStatusRegion.working != NULL)
                    GetBbAction()->AddInputRegion(myMonStatusRegion.working, true, true, true, FC_BbRegObsPriority::HIGH);
		        if (myMonDefectsRegion.protection != NULL)
		            GetBbAction()->AddInputRegion(myMonDefectsRegion.protection, true, true, true, FC_BbRegObsPriority::HIGH);
		        if (myMonStatusRegion.protection != NULL)
                    GetBbAction()->AddInputRegion(myMonStatusRegion.protection, true, true, true, FC_BbRegObsPriority::HIGH);
			}
			
            theProtectionAction->RegisterSpecificObservers(this);
		}

		//insert the action into our callback list
		FC_ListOfAction::Insert(*theProtectionAction);

		//indicate that the protection action is allowed to operate
		if (CheckValidity())
			theProtectionAction->AllowOperation();
	}
}

bool SP_1plus1DefectProcessorAction::CheckValidity()
{
	bool valid = true;
	if (myMonDefectsRegion.working != NULL)
	    valid &= myMonDefectsRegion.working->IsValid();
    if (myMonStatusRegion.working != NULL)
        valid &= myMonStatusRegion.working->IsValid();
    if (myMonDefectsRegion.protection != NULL)
		valid &= myMonDefectsRegion.protection->IsValid();
    if (myMonStatusRegion.protection != NULL)
        valid &= myMonStatusRegion.protection->IsValid();

	return valid;
}
	
void SP_1plus1DefectProcessorAction::UnregisterFromDefects(SP_ProtectionAction* theProtectionAction)
{
	//Remove action from callback list
	FC_ListOfAction::Remove(*theProtectionAction);
	//if the callback list is now empty
	//stop observing the region
	if (IsEmpty())
	{
		//stop listening to the regions
		if (myMonDefectsRegion.working != NULL)
	        GetBbAction()->RemoveInputRegion(myMonDefectsRegion.working);
		if (myMonStatusRegion.working != NULL)
            GetBbAction()->RemoveInputRegion(myMonStatusRegion.working);
		if (myMonDefectsRegion.protection != NULL)
		    GetBbAction()->RemoveInputRegion(myMonDefectsRegion.protection);
		if (myMonStatusRegion.protection != NULL)
            GetBbAction()->RemoveInputRegion(myMonStatusRegion.protection);
		if (mySpSystemStatusRegion.working != NULL)
            GetBbAction()->RemoveInputRegion(mySpSystemStatusRegion.working);
        if (mySpShelfStatusRegion.working != NULL)
            GetBbAction()->RemoveInputRegion(mySpShelfStatusRegion.working);
		//Don't need to remove input region on protection for sp status since the region is shared

		theProtectionAction->UnregisterSpecificObservers(this);

		myMonDefectsRegion.working = NULL;
        myMonStatusRegion.working = NULL;
		myMonDefectsRegion.protection = NULL;
		myMonStatusRegion.protection = NULL;
		mySpSystemStatusRegion.working     = NULL;
		mySpSystemStatusRegion.protection  = NULL;
        mySpShelfStatusRegion.working = NULL;
        mySpShelfStatusRegion.protection = NULL;

		//Mark this processor as not used
		SetUsageStatus(false);

	}

}

//##ModelId=3BBC9B3903A6
FC_Object* SP_1plus1DefectProcessorAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

	//Log an event (DEBUG PUPOSE)
	if (SP_TestMenu::mySpEventLog)
        FC_EventRecord(EVENT_SP_MON_ISR,0);



    //Perform any prerun operations
	if (myLayer == SP_HOP ||
        myLayer == SP_VCG)
	{
		iterator it = Begin();
	    if (*it)
	        dynamic_cast<SP_1plus1ProtectionAction*> (*it) ->PreRun();
	}
	//call back registered observers on this defect processor
	if (myLayer == SP_HOP ||
		myLayer == SP_VCG)
	{
        FC_ListOfAction::DoRunWithReason(SP_DEFECT_REASON_NO_COMMIT, this, theParam);
		//commit the operation
	    iterator it = Begin();
	    if (*it)
	        dynamic_cast<SP_1plus1ProtectionAction*> (*it) ->mySelectorPtr->Commit();

        //PERFORMANCE RELATED CHANGE: Now that we have commited the operation, wake up the status collector
		GetAppIf().GetStatusCollectionAction()->RunWithReason(theRunReason, this, theParam);

	}
	else
	{
		FC_ListOfAction::DoRunWithReason(SP_DEFECT_REASON_COMMIT, this, theParam);
	}

    return NULL;
}

MON_Region* SP_1plus1DefectProcessorAction::GetMONDefectRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility)
{
	if (myLayer == SP_MS)
	{
		if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetMsIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		    //return (GetAppIf().GetCardContext().GetMsIf().GetMonLineSideApp(theFacility).GetDefectsRegion());   
		}
		else if (mySide == SP_PORT)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetMsIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		    //return (GetAppIf().GetCardContext().GetMsIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		}
	}
	else if (myLayer == SP_ODU)
	{
	    if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOduIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		    //return (GetAppIf().GetCardContext().GetOduIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
        }
		else if (mySide == SP_PORT)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOduIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		}
	}
	else if (myLayer == SP_OPT)
	{
		if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		    //return (GetAppIf().GetCardContext().GetOptIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		}
		else if (mySide == SP_PORT)
		{
            if (IsPortFacility(theFacility))
		    {
			    return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
            }

            if (IsLineFacility(theFacility))
            {
				return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
			}

		}
	}
	else if (myLayer == SP_SYNC)
	{
		//Using application card context for sync since protection cannot be traversing multiple modules.
		//sync protection can have either line or port facilities as sources
		if (IsLineFacility(theFacility))
		{
			//a line side facility
			return (GetAppIf().GetCardContext().GetMsIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		}

		if (IsPortFacility(theFacility))
		{
		    //a port side facility
            return (GetAppIf().GetCardContext().GetMsIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		}
	}
	else if (myLayer == SP_HOP)
	{
		if (IsLineFacility(theFacility))
		{
		   return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetHopIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		   //return (GetAppIf().GetCardContext().GetHopIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		}

		if (IsPortFacility(theFacility))
		{
			//a port side facility
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetHopIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		}
	}
	else if (myLayer == SP_VCG)
	{
		if (IsLineFacility(theFacility))
		{
		    return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetVcgIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		    //return (GetAppIf().GetCardContext().GetVcgIf().GetMonLineSideApp(theFacility).GetDefectsRegion());
		}

		if (IsPortFacility(theFacility))
		{
			//a port side facility
		    return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetVcgIf().GetMonPortSideApp(theFacility).GetDefectsRegion());
		}
	}

	return NULL;
	  
}

MON_Region* SP_1plus1DefectProcessorAction::GetMONStatusRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType)
{
	if (myLayer == SP_MS)
	{
		if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetMsIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetMsIf().GetMonLineSideApp(theFacility).GetStatusRegion());   
		}
		else if (mySide == SP_PORT)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetMsIf().GetMonPortSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetMsIf().GetMonPortSideApp(theFacility).GetStatusRegion());
		}
	}
	else if (myLayer == SP_ODU)
	{
	    if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOduIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetOduIf().GetMonLineSideApp(theFacility).GetStatusRegion());
        }
		else if (mySide == SP_PORT)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOduIf().GetMonPortSideApp(theFacility).GetStatusRegion());
		}
	}
	else if (myLayer == SP_OPT)
	{
		if (mySide == SP_LINE)
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetOptIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		}
		else if (mySide == SP_PORT)
		{
            if (IsPortFacility(theFacility))
		    {
			    return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonPortSideApp(theFacility).GetStatusRegion());
            }

            if (IsLineFacility(theFacility))
            {
				return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetOptIf().GetMonLineSideApp(theFacility).GetStatusRegion());	
			}

		}
	}
	else if (myLayer == SP_SYNC)
	{
		//Using application card context for sync since protection cannot be traversing multiple modules.
		//sync protection can have either line or port facilities as sources
		if (IsLineFacility(theFacility))
		{
			if (theFacility == CT_LINE_SIDE_5 ||
				theFacility == CT_LINE_SIDE_6)
			{
				if (the1plus1SubType == CT_SP_EXT_OPSM ||
					the1plus1SubType == CT_SP_LINE)
				{
					return (GetAppIf().GetCardContext().GetMsIf().GetMonLineSideApp(theFacility).GetStatusRegion());
				}
			}
			else
			{
				if (the1plus1SubType != CT_SP_EXT_SYS &&
					the1plus1SubType != CT_SP_EXT_SLAVE)
				{
			        //a line side facility
			        return (GetAppIf().GetCardContext().GetMsIf().GetMonLineSideApp(theFacility).GetStatusRegion());
				}
			}
		}

		if (IsPortFacility(theFacility))
		{
			if (the1plus1SubType != CT_SP_EXT_SYS &&
					the1plus1SubType != CT_SP_EXT_SLAVE)
			{
			    //a port side facility
			    return (GetAppIf().GetCardContext().GetMsIf().GetMonPortSideApp(theFacility).GetStatusRegion());
			}
		}
	}
	else if (myLayer == SP_HOP)
	{
		if (IsLineFacility(theFacility))
		{
			return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetHopIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetHopIf().GetMonLineSideApp(theFacility).GetStatusRegion());
		}

		if (IsPortFacility(theFacility))
		{
			//a port side facility
		    return (T6100_MainAppIf::Instance().GetShelfPtr(theShelf)->GetSlotPtr(theSlot)->GetGenericCardIf().GetHopIf().GetMonPortSideApp(theFacility).GetStatusRegion());
		    //return (GetAppIf().GetCardContext().GetHopIf().GetMonPortSideApp(theFacility).GetStatusRegion());
		}
	}
	else if (myLayer == SP_VCG)
	{
	    if (mySide == SP_LINE || mySide == SP_PORT)
		{
		   //No status region defined for VCG
		}	    
	}

	return NULL;
}

SP_SsmRegion* SP_1plus1DefectProcessorAction::GetSPSystemStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType)
{
	if (myLayer == SP_SYNC)
	{
		//Working and protect sides share the same region
		if (the1plus1SubType == CT_SP_EXT_SYS ||
			the1plus1SubType == CT_SP_EXT_SLAVE)
		{
			if (theFacility != CT_INTF_ID_UNKNOWN)
			    return (T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion());
		}
	}
	return NULL;
}

SP_SsmRegion* SP_1plus1DefectProcessorAction::GetSPShelfStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType)
{
	if (myLayer == SP_SYNC)
	{
		//Working and protect sides share the same region
		if (the1plus1SubType == CT_SP_EXT_SYS ||
			the1plus1SubType == CT_SP_EXT_SLAVE)
		{
			if (theFacility != CT_INTF_ID_UNKNOWN)
            {
			    return (T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion(CSPII_CardIF::GetInstance()->GetShelfId()));
            }
		}
	}
	return NULL;
}

