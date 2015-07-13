/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :   Signal Alarm
TARGET      :   All cards
AUTHOR      :   Marc Vendette
DESCRIPTION :   Implementation file for the ALM_TransferEnableAction class.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>

#include "ALM_TransferEnableAction.h"
#include "Alarm/src/ALM_ListOfAction.h"


//---------------------------------------------------------------------------
//##ModelId=3C506C32030A
ALM_TransferEnableAction::ALM_TransferEnableAction(ALM_ListOfAction* theListOfActionPtr) :
    itsListOfActionPtr(theListOfActionPtr)
{
}

//---------------------------------------------------------------------------
//##ModelId=3C506C32031D
ALM_TransferEnableAction::~ALM_TransferEnableAction()
{
}

//---------------------------------------------------------------------------
//##ModelId=3C506C320314
void ALM_TransferEnableAction::Run( FC_Object* theObject)
{
    FC_THROW_ERROR( FC_NotSupportedError, "Run not supported" );
}

//---------------------------------------------------------------------------
//##ModelId=3DBFFAE600F0
FC_Object* ALM_TransferEnableAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvoker, FC_Object* theParam)
{
    itsListOfActionPtr->SetTransferEnable(true);
    itsListOfActionPtr->IncModifyCounterOfAllRegion();
    return NULL;
}
