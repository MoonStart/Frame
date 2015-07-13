/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 16, 2005 - Thomas J. Novak
DESCRIPTION:    Implementation file for TL1 ETN Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_mTeraFacilityRtrvParameters.h>
#include <TL1Facility/T7100_TL1FacilityEntity.h>
#include <TL1Core/T7100_TL1AgentUtility.h>

TL1_mTeraFacilityRtrvParameters::TL1_mTeraFacilityRtrvParameters()
{
    myAlarmProfile=             (CT_ProfileTableId*)0;
    myPrimaryState=             (CT_SM_PST*)0;
    mySecondaryState=           (CT_SM_SST*)0;
    myRtrvMembers=              (bool*)0;
    myHandle=                   (LT_Handle*)0;             
    myCtag=                     (LT_Ctag)0;
    
    myAlarmProfileVal=             (CT_ProfileTableId)0;
    myPrimaryStateVal=             (CT_SM_PST)0;
    mySecondaryStateVal=           (CT_SM_SST)0;
    myRtrvMembersVal=              false;
    myHandleVal=                   (LT_Handle)0;
}



TL1_mTeraFacilityRtrvParameters::~TL1_mTeraFacilityRtrvParameters()
{
}

TL1_mTeraFacilityRtrvParameters& 
TL1_mTeraFacilityRtrvParameters::operator=( const TL1_mTeraFacilityRtrvParameters& theBlock )
{
    SET_VAL(myAlarmProfile,             theBlock.myAlarmProfile);
    SET_VAL(myPrimaryState,             theBlock.myPrimaryState);
    SET_VAL(mySecondaryState,           theBlock.mySecondaryState);
    SET_VAL(myRtrvMembers,              theBlock.myRtrvMembers);
    SET_VAL(myHandle,                   theBlock.myHandle);
    if (theBlock.myCtag != NULL)
    {
        myCtagVal = string(theBlock.myCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }

    return *this;
}

