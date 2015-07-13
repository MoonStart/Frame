// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>

#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_IncModificationAction.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <XC/TSXC_Connect.h>
#include <CSM/CSM_AppIf.h>
#include <TimeService/FC_Time.h>



//
// Constructor
//
TSXC_IncModificationAction::TSXC_IncModificationAction(T6100_CardIf& theCardContext) :
    myCardContext(theCardContext),
    myBbAction(NULL),
    myXCAgentConfig_Region(NULL),
	myCardStatusRegion(NULL)
{
    myBbAction = new FC_BbAction(this);
	//add CSM card status region as an input region to this Bb action
	T6100_SlotIf * theSlotIf = dynamic_cast<T6100_SlotIf*> (myCardContext.GetParent());
    if (theSlotIf)
    {
	    myCardStatusRegion = &(theSlotIf->GetCsmApp().GetCardStatusRegion());
	    myBbAction->AddInputRegion(myCardStatusRegion);
    }
    else
    {
        FC_REPORT_ERROR(FC_LogicError, "Unexpected null pointer");
    }
	FC_Time aTimeStamp;
	aTimeStamp.GetCurrentTime();
    myOccurTime = aTimeStamp.GetUTCTime();
}

//
// Destructor
//
TSXC_IncModificationAction::~TSXC_IncModificationAction()
{
	//remove the CSM card status region as an input region
	myBbAction->RemoveInputRegion(myCardStatusRegion);
    delete myBbAction;
}


//
// Get Methods
//
TSXC_ConfigRegion<TSXC_Connect>* TSXC_IncModificationAction::GetAgCfgRegion()
{
    return myXCAgentConfig_Region;
}



//
// Set Methods
//
void TSXC_IncModificationAction::SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion)
{
    myXCAgentConfig_Region = theAGCfgRegion;
}


//
// Do the work
//
FC_Object* TSXC_IncModificationAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    

	  //This action updates the modification counter and calls
	  //UpdateNotify on the XC AG Config Region to force a reapply
	  //of crossconnect information to the hardware.
	  //This update is done only if all the following conditions are true
	  // 1. The card status has transitioned to the OK (present with no defects) state
	  // 2. The XC AG Config region is valid

	  time_t theOccurTime;
	  TSXC_ConfigRegion<TSXC_Connect>* theConfigRegion = GetAgCfgRegion();
	  if (theConfigRegion->IsValid())
	  {
		  CSM_CardStatus& aCardStatus = static_cast<CSM_CardStatus&>((*myCardStatusRegion)[0]);
		  if (aCardStatus.GetCardStatus(theOccurTime) == CT_OK)
		  {
			  //If the status has toggled since the last time the action
			  //ran, then reapply the crossconnects
			  if (myOccurTime != theOccurTime)
			  {
			      myOccurTime = theOccurTime;
                  theConfigRegion->IncModificationCounter();
                  theConfigRegion->UpdateNotify();
			  }
		  }
	  }

      return NULL;

}



void TSXC_IncModificationAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
