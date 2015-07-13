// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_1plus1DccConfigAction.h"
#include <ExecutionSupport/FC_TimedProcess.h>
#include <Blackboard/FC_BbAction.h>
#include <ErrorService/FC_Error.h>
#include <T6100_Dispatcher.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_ControllerStatusRegion.h>
#include <Configuration/CFG_DcclProt.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>


// Initialize the static members
SP_1plus1DccConfigAction * SP_1plus1DccConfigAction::myInstance = NULL;

////-----Action to configure LAPS broadcast on DCC-------------------------------------------
//##ModelId=3BBC9B0F02A0
SP_1plus1DccConfigAction::SP_1plus1DccConfigAction(T6100_CardIf* theCardContext):
myCardContext(theCardContext),
myAppStatusRegionLine(NULL),
myAppStatusRegionPort(NULL),
myModeRegion(NULL)
{
    for (int i=0; i< CT_TEL_LAPD_IN_SC; i++)
    {
        mySelection[i] = false;
        myRemotePort[i] = 0;
    }

    myBbAction = new FC_BbAction(this);
    myProcess = new FC_TimedProcess(*myBbAction, gTimerDispatcher, 100);
    if (myCardContext->GetLineSideProtIfPtr())
    {
        myAppStatusRegionLine = myCardContext->GetLineSideProtectionIf().GetLineSideProtectionAppPtr()->GetSPReadyRegion();
        myBbAction->AddInputRegion(myAppStatusRegionLine);
    }

    if (myCardContext->GetPortSideProtIfPtr())
    {
        myAppStatusRegionPort = myCardContext->GetPortSideProtectionIf().GetPortSideProtectionAppPtr()->GetSPReadyRegion();
        myBbAction->AddInputRegion(myAppStatusRegionPort);
    }
}

//##ModelId=38EDF51800A6
SP_1plus1DccConfigAction::~SP_1plus1DccConfigAction()
{
    myProcess->SuspendImmediate();
    if (myAppStatusRegionLine)
        myBbAction->RemoveInputRegion(myAppStatusRegionLine);
    if (myAppStatusRegionPort)
        myBbAction->RemoveInputRegion(myAppStatusRegionPort);
    delete myProcess;
    delete myBbAction;
    myProcess = NULL;
    myBbAction= NULL;
}

//##ModelId=3B8BC9D30390
void SP_1plus1DccConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_1plus1DccConfigAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    //Get the config dccl prot region
    CFG_Region* sProtCfgRegion = myCardContext->GetDcclIf().GetCfgDcclSectionApp().GetProtCfgRegion();
    CFG_Region* lProtCfgRegion = myCardContext->GetDcclIf().GetCfgDcclLineApp().GetProtCfgRegion();


    //Get the application ready status region and verify that we are ready
    if (myAppStatusRegionLine)
    {
        SP_ApplicationStatus& aAppStatusLine = static_cast<SP_ApplicationStatus&>((*myAppStatusRegionLine)[0]);
        if (!aAppStatusLine.IsReady())
            return NULL;
    }

    if (myAppStatusRegionPort)
    {
        SP_ApplicationStatus& aAppStatusPort = static_cast<SP_ApplicationStatus&>( (*myAppStatusRegionPort) [0]);
        if (!aAppStatusPort.IsReady())
            return NULL;
    }

    bool hasChanged;

    if (sProtCfgRegion && myModeRegion)
    {
        hasChanged = Configure(sProtCfgRegion);

        if (!sProtCfgRegion->IsValid() || hasChanged)
        {
            sProtCfgRegion->IncModificationCounter();
            sProtCfgRegion->UpdateNotify();
        }
    }

    if (lProtCfgRegion && myModeRegion)
    {
        hasChanged = Configure(lProtCfgRegion);

        if (!lProtCfgRegion->IsValid() || hasChanged)
        {
            lProtCfgRegion->IncModificationCounter();
            lProtCfgRegion->UpdateNotify();
        }
    }

    return NULL;
}

void SP_1plus1DccConfigAction::SetLapsData(uint8 remotePort, bool isSelected, uint8 index)
{
    FC_THROW_ERROR_IF(index >= CT_TEL_LAPD_IN_SC, FC_RuntimeError, "SP_1plus1DccConfigAction::SetLapsData() index greater than CT_TEL_LAPD_IN_SC");
    myRemotePort[index] = remotePort;
    mySelection[index] = isSelected;
}

void SP_1plus1DccConfigAction::ApplyConfiguration()
{
    myProcess->WakeUp();
}

//Static functions
SP_1plus1DccConfigAction & SP_1plus1DccConfigAction::GetInstance(T6100_CardIf* theCardContext)
    {
        if(myInstance == NULL)
        {
          myInstance = new SP_1plus1DccConfigAction(theCardContext);
        }

        return(*myInstance);
    }


void SP_1plus1DccConfigAction::DeleteInstance()
{
    if (myInstance != NULL)
    {
        delete myInstance;
        myInstance = NULL;
    }
}

bool SP_1plus1DccConfigAction::Configure(CFG_Region* aProtCfgRegion)
{
    //The following rules apply for selection:
    /*
    If (Master & selected)
      Master/Local
    if (Master & !selected)
        if (remote = good)
           Master/Remote
        if (remote = bad)
           Master/Local
    if (Slave & ! selected)
      Slave/Remote
    if (Slave & selected)
      if (remote = good)
        Slave/Remote
      else
        Master/Local
    */

    uint32 index;
    bool hasChanged;
    CT_DCC_BroadcastMode theNewBcastMode;
    CT_DCC_SelectionMode theNewSelMode;
    bool theRxSelected = false;

    CT_ControllerMode theMode = myModeRegion->GetControllerMode();
    //Configure based on the mode
    if (theMode == ACTIVE_MODE)
    {
        theNewBcastMode = CT_DCC_MASTER;
    }
    else if (theMode == STNBY_MODE)
    {
        theNewBcastMode = CT_DCC_SLAVE;
    }
    else
    {
        return false; //bail since we don't know the mode yet
    }

    for (index=0; index < aProtCfgRegion->Size(); index++)
    {
        CFG_DcclProt& aProtCfgObject = static_cast<CFG_DcclProt&> ((*aProtCfgRegion)[(bbindex_t)index]);
        hasChanged |= aProtCfgObject.SetRemotePort(myRemotePort[index]);

        //Configure based on the mode
        if (theNewBcastMode == CT_DCC_MASTER)
        {
            if (mySelection[index])
            {
                theNewSelMode = CT_DCC_LOCAL;
                theRxSelected = true;
            }
            else
            {
                theNewSelMode = CT_DCC_REMOTE;
                theRxSelected = false;
            }
        }
        else if (theNewBcastMode == CT_DCC_SLAVE)
        {
            theNewSelMode = CT_DCC_REMOTE;
            theRxSelected = false;
        }

        hasChanged |= aProtCfgObject.SetBroadcastMode(theNewBcastMode);
        hasChanged |= aProtCfgObject.SetSelectionMode(theNewSelMode);
        hasChanged |= aProtCfgObject.SetRxSelected(theRxSelected);
    }


    return hasChanged;
}

void SP_1plus1DccConfigAction::SetModeRegion(T6100_ControllerStatusRegion* theModeRegion)
{
    myModeRegion = theModeRegion;
}
