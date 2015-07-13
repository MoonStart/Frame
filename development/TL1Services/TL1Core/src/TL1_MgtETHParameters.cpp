/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         2013.9.16 - Gang Zhu
DESCRIPTION:    Implementation file for TL1 MGTETH Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_MgtETHParameters.h>

TL1_MgtETHParameters::TL1_MgtETHParameters()
{

    myAlarmProfile          = (CT_ProfileTableId*)0;
	myAutoNegotiation       = (bool *)0;
	myEthRate               = (CT_TEL_daHz*)0;
    myDuplexMode            = (CT_TEL_MAC_DUPLEX_MODE*)0;
    myFlowCtrl              = (CT_TEL_MAC_FLOWCTRL*)0;
	myHandle                = (LT_Handle*)0;             
    myCtag                  = (LT_Ctag)0;
	myPst                   = (CT_SM_PST*)0;
}

TL1_MgtETHParameters::TL1_MgtETHParameters(const TL1_MgtETHParameters& theBlock )
{
	myAlarmProfile         = theBlock.myAlarmProfile;
    myAutoNegotiation      = theBlock.myAutoNegotiation;
    myEthRate              = theBlock.myEthRate;
    myDuplexMode           = theBlock.myDuplexMode;
    myFlowCtrl             = theBlock.myFlowCtrl;
    myHandle               = theBlock.myHandle;     
    myCtag                 = theBlock.myCtag;
	myPst                  = theBlock.myPst;
}

TL1_MgtETHParameters::~TL1_MgtETHParameters()
{
}

TL1_MgtETHParameters& 
TL1_MgtETHParameters::operator=( const TL1_MgtETHParameters& theBlock )
{
    myAlarmProfile         = theBlock.myAlarmProfile;
    myAutoNegotiation      = theBlock.myAutoNegotiation;
    myEthRate              = theBlock.myEthRate;
    myDuplexMode           = theBlock.myDuplexMode;
    myFlowCtrl             = theBlock.myFlowCtrl;
    myHandle               = theBlock.myHandle;     
    myCtag                 = theBlock.myCtag;
	myPst                  = theBlock.myPst;

    return *this;
}

bool 
TL1_MgtETHParameters::operator==( const TL1_MgtETHParameters& theBlock ) const
{
	
    if( myAlarmProfile != theBlock.myAlarmProfile )
        return false;  

    if( myAutoNegotiation != theBlock.myAutoNegotiation )
        return false;

    if( myEthRate != theBlock.myEthRate )
        return false;

    if( myDuplexMode != theBlock.myDuplexMode )
        return false;

    if( myFlowCtrl != theBlock.myFlowCtrl )
        return false;

    if( myHandle != theBlock.myHandle )     
        return false;

    if( myCtag != theBlock.myCtag )
        return false;

	if( myPst != theBlock.myPst)
		return false;

    return true;
}

