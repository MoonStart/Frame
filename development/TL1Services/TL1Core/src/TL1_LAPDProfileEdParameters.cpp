/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 30, 2005 - Thomas J. Novak
DESCRIPTION:    Implementation file for TL1 EDIT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPROFILEEDPARAMETERS_H__
#include <TL1Core/TL1_LAPDProfileEdParameters.h>
#endif

TL1_LAPDProfileEdParameters::TL1_LAPDProfileEdParameters()
{
	myPfName=           (CT_Fac_TraceString*)0;
    myTransferMode=     (CT_LPF_TxMode*)0;
    myRetransmitCount=  (uint16*)0;
    myAckTimer=         (CT_LapdProfile_Timer*)0;
    myMaxSize=          (uint16*)0;
    myFrameCount=       (uint16*)0;
    myInactivityTimer=  (uint16*)0;
    mySide=             (CT_LPF_Side*)0;
    mySequenceNumber=   (CT_LPF_SeqNum*)0;
    myIsCommandForced=  (bool*)0;
    myHandle=           (LT_Handle*)0;             
    myCtag=             (LT_Ctag)0;
}

TL1_LAPDProfileEdParameters::TL1_LAPDProfileEdParameters(const TL1_LAPDProfileEdParameters& theBlock )
{
	myPfName=           theBlock.myPfName;
    myTransferMode=     theBlock.myTransferMode;
    myRetransmitCount=  theBlock.myRetransmitCount;
    myAckTimer=         theBlock.myAckTimer;
    myMaxSize=          theBlock.myMaxSize;
    myFrameCount=       theBlock.myFrameCount;
    myInactivityTimer=  theBlock.myInactivityTimer;
    mySide=             theBlock.mySide;
    mySequenceNumber=   theBlock.mySequenceNumber;
    myIsCommandForced=  theBlock.myIsCommandForced;
    myHandle=           theBlock.myHandle;     
    myCtag=             theBlock.myCtag;
}

TL1_LAPDProfileEdParameters::~TL1_LAPDProfileEdParameters()
{
}

TL1_LAPDProfileEdParameters& 
TL1_LAPDProfileEdParameters::operator=( const TL1_LAPDProfileEdParameters& theBlock )
{
    myPfName=           theBlock.myPfName;
	myTransferMode=     theBlock.myTransferMode;
    myRetransmitCount=  theBlock.myRetransmitCount;
    myAckTimer=         theBlock.myAckTimer;
    myMaxSize=          theBlock.myMaxSize;
    myFrameCount=       theBlock.myFrameCount;
    myInactivityTimer=  theBlock.myInactivityTimer;
    mySide=             theBlock.mySide;
    mySequenceNumber=   theBlock.mySequenceNumber;
    myIsCommandForced=  theBlock.myIsCommandForced;
    myHandle=           theBlock.myHandle;     
    myCtag=             theBlock.myCtag;

    return *this;
}

bool 
TL1_LAPDProfileEdParameters::operator==( const TL1_LAPDProfileEdParameters& theBlock ) const
{
	if( myPfName != myPfName )
		return false;

    if( myTransferMode != theBlock.myTransferMode )
        return false;  

    if( myRetransmitCount != theBlock.myRetransmitCount )
        return false;

    if( myAckTimer != theBlock.myAckTimer )
        return false;

    if( myMaxSize != theBlock.myMaxSize )
        return false;

    if( myFrameCount != theBlock.myFrameCount )
        return false;

    if( myInactivityTimer != theBlock.myInactivityTimer )
        return false;

    if( mySide != theBlock.mySide )
        return false;

    if( mySequenceNumber != theBlock.mySequenceNumber )
        return false;

    if( myIsCommandForced != theBlock.myIsCommandForced )
        return false;

    if( myHandle != theBlock.myHandle )     
        return false;

    if( myCtag != theBlock.myCtag )
        return false;

    return true;
}

