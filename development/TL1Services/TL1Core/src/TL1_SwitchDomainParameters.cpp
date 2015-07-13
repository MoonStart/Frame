/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 12th, 2011 - Tim Thacher
DESCRIPTION:    Implementation file for TL1 SwitchDomain Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWITCHDOMAINPARAMETERS_H__
#include <TL1Core/TL1_SwitchDomainParameters.h>
#endif

#include <CommonTypes/CT_TL1_Error.h>

TL1_SwitchDomainParameters::TL1_SwitchDomainParameters()
: myAlarmProfile(NULL), mySwitchDomainMode(NULL), myPrimaryState(NULL)
{
}

TL1_SwitchDomainParameters::TL1_SwitchDomainParameters(CT_ProfileTableId*      theAlarmProfile,
                                                       CT_SwitchDomainMode*    theSwitchDomainMode,
                                                       CT_SM_PST*              thePrimaryState)
: myAlarmProfile(theAlarmProfile), 
  mySwitchDomainMode(theSwitchDomainMode), 
  myPrimaryState(thePrimaryState)
{
}

TL1_SwitchDomainParameters::~TL1_SwitchDomainParameters()
{
}

TL1_SwitchDomainParameters& TL1_SwitchDomainParameters::operator=( const TL1_SwitchDomainParameters& theBlock )
{
    myAlarmProfile=         theBlock.myAlarmProfile;
    mySwitchDomainMode=     theBlock.mySwitchDomainMode;
    myPrimaryState=         theBlock.myPrimaryState;

    return *this;
}

bool TL1_SwitchDomainParameters::operator==( const TL1_SwitchDomainParameters& theBlock ) const
{
     return (   myAlarmProfile          == theBlock.myAlarmProfile &&
                mySwitchDomainMode      == theBlock.mySwitchDomainMode &&
                myPrimaryState          == theBlock.myPrimaryState );
}



