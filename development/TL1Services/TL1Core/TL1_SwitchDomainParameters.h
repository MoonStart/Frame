/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 12, 2011 - Tim Thacher
DESCRIPTION:    Header file for TL1 SwitchDomain Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWITCHDOMAINPARAMETERS_H__
#define __TL1_SWITCHDOMAINPARAMETERS_H__

#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_SwitchDomainMap.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <vector>

class TL1_SwitchDomainParameters
{
public:
    
    TL1_SwitchDomainParameters();

    TL1_SwitchDomainParameters(CT_ProfileTableId*   theAlarmProfile,
                               CT_SwitchDomainMode* theSwitchDomainMode,
                               CT_SM_PST*           thePrimaryState);

    virtual ~TL1_SwitchDomainParameters();

    TL1_SwitchDomainParameters& operator=( const TL1_SwitchDomainParameters& theBlock );

    bool operator==( const TL1_SwitchDomainParameters& theBlock ) const;

    inline void SetAlarmProfile(CT_ProfileTableId* theAlarmProfile);
    inline void SetSwitchDomainMode(CT_SwitchDomainMode* theSwitchDomainMode);
    inline void SetPrimaryState(CT_SM_PST* thePrimaryState);

    inline CT_ProfileTableId*   GetAlarmProfile() const ;
    inline CT_SwitchDomainMode* GetSwitchDomainMode() const ;
    inline CT_SM_PST*           GetPrimaryState() const ;

private:

    CT_ProfileTableId*      myAlarmProfile;
    CT_SwitchDomainMode*    mySwitchDomainMode;
    CT_SM_PST*              myPrimaryState;
};

inline void TL1_SwitchDomainParameters::SetAlarmProfile(CT_ProfileTableId* theAlarmProfile){myAlarmProfile = theAlarmProfile;}
inline void TL1_SwitchDomainParameters::SetSwitchDomainMode(CT_SwitchDomainMode* theSwitchDomainMode){mySwitchDomainMode = theSwitchDomainMode;}
inline void TL1_SwitchDomainParameters::SetPrimaryState(CT_SM_PST* thePrimaryState){myPrimaryState = thePrimaryState;}

inline CT_ProfileTableId*   TL1_SwitchDomainParameters::GetAlarmProfile() const { return myAlarmProfile; }
inline CT_SwitchDomainMode* TL1_SwitchDomainParameters::GetSwitchDomainMode() const { return mySwitchDomainMode; }
inline CT_SM_PST*           TL1_SwitchDomainParameters::GetPrimaryState() const { return myPrimaryState; }


#endif
