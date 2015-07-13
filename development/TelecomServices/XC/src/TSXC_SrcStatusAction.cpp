// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <XC/TSXC_SrcStatusAction.h>
#include <XC/TSXC_SourceConnectStatus.h>
#include <XC/TSXC_BaseApplication.h>

#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>

#include <Blackboard/FC_BoolRegion.h>

//------------------------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------------------------
TSXC_SrcStatusAction::TSXC_SrcStatusAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    mySrcStatusRegion(NULL)
{
}

//------------------------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------------------------
TSXC_SrcStatusAction::~TSXC_SrcStatusAction()
{

}

//------------------------------------------------------------------------------------------------------------
// Do the work
//
FC_Object* TSXC_SrcStatusAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{

    TSXC_SourceConnectStatus*       aSrcConnectStatus;

    aSrcConnectStatus = myCardContext.GetXCAppIf().GetXCApp().GetSrcConnectStatus();

    aSrcConnectStatus->Reset();             //--- clear  the content
    aSrcConnectStatus->SetConnectStatus();  //--- update the content

    mySrcStatusRegion->IncModificationCounter();

    return NULL;
}

//------------------------------------------------------------------------------------------------------------
void TSXC_SrcStatusAction::SetSrcStatusRegion(FC_BoolRegion* theSrcStatusRegion)
{
    mySrcStatusRegion = theSrcStatusRegion;
}

