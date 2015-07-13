/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_SourceTxStatus  Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_SourceTxStatus.h>
#include <XC/TSXC_BaseApplication.h>
//----------------------------------------------------------------------------------------------------------------------
//--- Constructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_SourceTxStatus::TSXC_SourceTxStatus(T6100_TelecomIf& theContext):myContext(theContext)
{
    Reset();
}

//----------------------------------------------------------------------------------------------------------------------
//--- Destructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_SourceTxStatus::~TSXC_SourceTxStatus()
{
}
    
//----------------------------------------------------------------------------------------------------------------------
//  The "theChannel" perameter is assumes as zero based 
//  If a Channel need to be deactivated then it will return true 
//  if so it update the previous state as well for the next time use.
//----------------------------------------------------------------------------------------------------------------------
bool TSXC_SourceTxStatus::IsDeactivationNeeded(UINT16 theChannel)
{
    bool    aResult = false;
    if (myPreviousActiveStatus[theChannel] == true && myCurrentActiveStatus[theChannel] == false)
    {
        aResult = true;
        myPreviousActiveStatus[theChannel] = false;
    }
    return aResult;
}

//----------------------------------------------------------------------------------------------------------------------
//  The "theChannel" perameter is assumes as zero based 
//  Set the current and the previous status as active for the new connections
//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceTxStatus::SetCurrentStatus(UINT16 theChannel)
{
    if (theChannel < (XC_MAX_XC_SSM_IM_LINE + XC_MAX_XC_SSM_IM_PORT))
    {
        myCurrentActiveStatus[theChannel] = true;
        myPreviousActiveStatus[theChannel] = true;
    }    
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceTxStatus::ClearCurrent()
{
    memset(&myCurrentActiveStatus, false, sizeof(myCurrentActiveStatus));
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceTxStatus::Reset()
{
    memset(&myCurrentActiveStatus, false, sizeof(myCurrentActiveStatus));
    memset(&myPreviousActiveStatus, false, sizeof(myPreviousActiveStatus));    
}

//----------------------------------------------------------------------------------------------------------------------
