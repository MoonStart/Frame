/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 16, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 ENTER Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACILITYRTRVPARAMETERS_H__
#define __TL1_FACILITYRTRVPARAMETERS_H__

#include <vector>
using namespace std;

#include <TL1Core/TL1_Entity.h>
#include <TL1Core/TL1_FacDomain.h>
#include <TL1Core/TL1_AlarmDomain.h>
#include <Response/TL1_Response.h>
#include <Response/TL1_FACRspBlk.h>


#define SET_VAL(X, Y) do \
{ \
    if ((Y) != NULL) \
    { \
        X##Val = *(Y); \
        X = &(X##Val); \
    } \
    else \
    { \
        X = NULL; \
    } \
}while(0);

class TL1_mTeraFacilityRtrvParameters  
{
public:
    
    TL1_mTeraFacilityRtrvParameters();

    virtual ~TL1_mTeraFacilityRtrvParameters();

    TL1_mTeraFacilityRtrvParameters& operator=( const TL1_mTeraFacilityRtrvParameters& theBlock );

    inline CT_ProfileTableId*           GetAlarmProfile( ) const;
    inline void                         SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile );

    inline CT_SM_PST*                   GetPrimaryState( ) const;
    inline void                         SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_SM_SST*                   GetSecondaryState( ) const;
    inline void                         SetSecondaryState(CT_SM_SST* theSecondaryState);

    inline bool*                        GetRtrvMembers( ) const;
    inline void                         SetRtrvMembers(bool* theSecondaryState);

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline CT_PMProfileTableId*         GetPmProfile( ) const;
    inline void                         SetPmProfile(  CT_PMProfileTableId* thePmProfile );

protected:
    CT_ProfileTableId*            myAlarmProfile;
    CT_SM_PST*                    myPrimaryState;
    CT_SM_SST*                    mySecondaryState;
    bool*                         myRtrvMembers;
    LT_Handle*                    myHandle;
    LT_Ctag                       myCtag;

    CT_ProfileTableId             myAlarmProfileVal;
    CT_SM_PST                     myPrimaryStateVal;
    CT_SM_SST                     mySecondaryStateVal;
    bool                          myRtrvMembersVal;
    LT_Handle                     myHandleVal;
    string                        myCtagVal;

};

inline CT_ProfileTableId*                         
TL1_mTeraFacilityRtrvParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile )
{
    SET_VAL(myAlarmProfile, theAlarmProfile);
}

inline CT_SM_PST*                   
TL1_mTeraFacilityRtrvParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    SET_VAL(myPrimaryState, thePrimaryState);
}

//--------------------------------------------------------------------------------

inline CT_SM_SST*                   
TL1_mTeraFacilityRtrvParameters::GetSecondaryState( ) const
{
    return mySecondaryState;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetSecondaryState(CT_SM_SST* theSecondaryState)
{
    SET_VAL(mySecondaryState, theSecondaryState);
}

//--------------------------------------------------------------------------------

inline bool*                   
TL1_mTeraFacilityRtrvParameters::GetRtrvMembers( ) const
{
    return myRtrvMembers;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetRtrvMembers(bool* theRtrvMembers)
{
    SET_VAL(myRtrvMembers, theRtrvMembers);
}

//---------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_mTeraFacilityRtrvParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetHandle( LT_Handle* theHandle )
{
    SET_VAL(myHandle, theHandle);
}
//--------------------------------------------------------------------------------

inline LT_Ctag                    
TL1_mTeraFacilityRtrvParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_mTeraFacilityRtrvParameters::SetCtag( LT_Ctag theCtag )
{
    if (theCtag)
    {
        myCtagVal = string(theCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }
}

#endif
