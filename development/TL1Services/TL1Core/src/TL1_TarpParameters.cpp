/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 23, 2006 - Thomas J. Novak
DESCRIPTION:    Implementation file for TL1 Tarp Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TARPPARAMETERS_H__
#include <TL1Core/TL1_TarpParameters.h>
#endif

TL1_TarpEdParameters::TL1_TarpEdParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAlarmProfile=     (CT_ProfileTableId*)0;
    myPrimaryState=     (CT_SM_PST*)0;
    myIsCommandForced=  (bool*)0;


    myFlushTmr=     (uint16*)0;
    myEntryTmr=     (uint16*)0;
    myT1Tmr=        (uint16*)0;
    myT2Tmr=        (uint16*)0;
    myT3Tmr=        (uint16*)0;
    myT4Tmr=        (uint16*)0;
    myProtAddr=     (uint16*)0;
    mySeqNum=       (uint16*)0;
    myLFTarpMsg=    (uint32*)0;
    myResetType=    (CT_TarpResetType*)0;
}

TL1_TarpEdParameters::TL1_TarpEdParameters(const TL1_TarpEdParameters& theInst )
{
    myHandle=       theInst.myHandle;    
    myCtag=         theInst.myCtag;
    myAlarmProfile= theInst.myAlarmProfile;
    myPrimaryState= theInst.myPrimaryState;

    myFlushTmr=     theInst.myFlushTmr;
    myEntryTmr=     theInst.myEntryTmr;
    myT1Tmr=        theInst.myT1Tmr;
    myT2Tmr=        theInst.myT2Tmr;
    myT3Tmr=        theInst.myT3Tmr;
    myT4Tmr=        theInst.myT4Tmr;
    myProtAddr=     theInst.myProtAddr;
    mySeqNum=       theInst.mySeqNum;
    myLFTarpMsg=    theInst.myLFTarpMsg;
    myResetType=    theInst.myResetType;
}

TL1_TarpEdParameters::~TL1_TarpEdParameters()
{
}

TL1_TarpEdParameters& 
TL1_TarpEdParameters::operator=( const TL1_TarpEdParameters& theInst )
{
    myHandle=       theInst.myHandle;    
    myCtag=         theInst.myCtag;
    myAlarmProfile= theInst.myAlarmProfile;
    myPrimaryState= theInst.myPrimaryState;

    myFlushTmr=     theInst.myFlushTmr;
    myEntryTmr=     theInst.myEntryTmr;
    myT1Tmr=        theInst.myT1Tmr;
    myT2Tmr=        theInst.myT2Tmr;
    myT3Tmr=        theInst.myT3Tmr;
    myT4Tmr=        theInst.myT4Tmr;
    myProtAddr=     theInst.myProtAddr;
    mySeqNum=       theInst.mySeqNum;
    myLFTarpMsg=    theInst.myLFTarpMsg;
    myResetType=    theInst.myResetType;

    return *this;
}

bool 
TL1_TarpEdParameters::operator==( const TL1_TarpEdParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAlarmProfile != theInst.myAlarmProfile )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myFlushTmr != theInst.myFlushTmr )
        return false;

    if ( myEntryTmr != theInst.myEntryTmr )
        return false;

    if ( myT1Tmr != theInst.myT1Tmr )
        return false;

    if ( myT2Tmr != theInst.myT2Tmr )
        return false;

    if ( myT3Tmr != theInst.myT3Tmr )
        return false;

    if ( myT4Tmr != theInst.myT4Tmr )
        return false;

    if ( myProtAddr != theInst.myProtAddr )
        return false;

    if ( mySeqNum != theInst.mySeqNum )
        return false;

    if ( myLFTarpMsg != theInst.myLFTarpMsg )
        return false;

    if ( myResetType != theInst.myResetType )
        return false;

    return true;
}

