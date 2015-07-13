/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive FAC Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive FAC Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
   #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef ___TL1_LAG_RESPONSE_BLOCK_H__
#define ___TL1_LAG_RESPONSE_BLOCK_H__

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_AgentFacility.h>

typedef list<CT_TL1_FacAddr> TL1_FacAddr_List;
typedef list<CT_TL1_FacAddr>::iterator TL1_FacAddr_It;

class TL1_LagRspBlk: public TL1_GeneralRspBlk
{
public:

    TL1_LagRspBlk();

//used by Lag
    TL1_LagRspBlk(
        const TL1_SmartParameter<CT_TL1_FacAddr>& theEntityAddr,
        const TL1_SmartParameter<CT_TL1_FacAddr>& theFac1Addr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theFac1Type,     
        const TL1_SmartParameter<CT_TL1_FacAddr>& theFac2Addr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theFac2Type,
        const TL1_SmartParameter<TL1_FacAddr_List>& theMemberList,
        const TL1_SmartParameter<CT_FacilitySubType>& theMemberFacType,
        const TL1_SmartParameter<CT_TEL_VlanTag>& theVlanTag,
        const TL1_SmartParameter<bool>& theTagMode,
        const TL1_SmartParameter<CT_TEL_Tpid>& theTpid,
        const TL1_SmartParameter<int>&  theCFProfile,
        const TL1_SmartParameter<bool>& theLacpEnabled,
        const TL1_SmartParameter<int>& theLacpSystemPriority,
        const TL1_SmartParameter<CT_LacpSystemId>& theLacpSystemId,
        const TL1_SmartParameter<CT_TEL_LacpTimeoutMode>& theLacpTimeoutMode,
        const TL1_SmartParameter<CT_ProfileTableId>&  theAlarmProfile,
        const TL1_SmartParameter<CT_SM_PST>&      thePST,
        const TL1_SmartParameter<CT_SM_PSTQ>&     thePSTQ,
        const TL1_SmartParameter<CT_SM_SST>&      theSST);


//used by Lag when LACP is enabled
    TL1_LagRspBlk(
        const TL1_SmartParameter<CT_TL1_FacAddr>& theEntityAddr,
        const TL1_SmartParameter<CT_TL1_FacAddr>& theFac1Addr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theFac1Type,     
        const TL1_SmartParameter<CT_TL1_FacAddr>& theFac2Addr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theFac2Type,
        const TL1_SmartParameter<TL1_FacAddr_List>& theMemberList,
        const TL1_SmartParameter<CT_FacilitySubType>& theMemberFacType,
        const TL1_SmartParameter<CT_TEL_VlanTag>& theVlanTag,
        const TL1_SmartParameter<bool>& theTagMode,
        const TL1_SmartParameter<CT_TEL_Tpid>& theTpid,
        const TL1_SmartParameter<int>&  theCFProfile,
        const TL1_SmartParameter<bool>& theLacpEnabled,
        const TL1_SmartParameter<int>& theLacpSystemPriority,
        const TL1_SmartParameter<CT_LacpSystemId>& theLacpSystemId,
        const TL1_SmartParameter<CT_TEL_LacpTimeoutMode>& theLacpTimeoutMode,
        const TL1_SmartParameter<int>& theActLacpSystemPriority,
        const TL1_SmartParameter<CT_LacpSystemId>& theActLacpSystemId,
        const TL1_SmartParameter<uint32>& theActLacpAdminKey,
        const TL1_SmartParameter<int>& thePtnLacpSystemPriority,
        const TL1_SmartParameter<CT_LacpSystemId>& thePtnLacpSystemId,
        const TL1_SmartParameter<uint32>& thePtnLacpAdminKey,
        const TL1_SmartParameter<CT_ProfileTableId>&  theAlarmProfile,
        const TL1_SmartParameter<CT_SM_PST>&      thePST,
        const TL1_SmartParameter<CT_SM_PSTQ>&     thePSTQ,
        const TL1_SmartParameter<CT_SM_SST>&      theSST);

//Used by Lag members
    TL1_LagRspBlk(
        const TL1_SmartParameter<CT_TL1_FacAddr>& theEntityAddr,
        const TL1_SmartParameter<CT_TL1_FacAddr>& theMemberAddr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theMemberType,     
        const TL1_SmartParameter<int>& theLacpPriorityMbr,
        const TL1_SmartParameter<CT_TEL_LacpPartiMode>& theLacpPartiModeMbr,
        const TL1_SmartParameter<CT_TEL_LacpPortState>& theLacpPortState,
        const TL1_SmartParameter<CT_SM_PST>&      thePST,
        const TL1_SmartParameter<CT_SM_PSTQ>&     thePSTQ,
        const TL1_SmartParameter<CT_SM_SST>&      theSST);

    TL1_LagRspBlk(const TL1_LagRspBlk& rspBlk);

    virtual ~TL1_LagRspBlk();

    TL1_LagRspBlk& operator=( const TL1_LagRspBlk& theBlock );

    bool operator==( const TL1_LagRspBlk& theBlock ) const;

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetAid() const
    {
        return myAid;
    }

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetFac1Addr() const
    {
        return myFac1Addr;
    }

    const TL1_SmartParameter<CT_FacilitySubType>& 
        GetFac1Type() const
    {
        return myFac1Type;
    }

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetFac2Addr() const
    {
        return myFac2Addr;
    }

    const TL1_SmartParameter<CT_ProfileTableId>& GetAlarmProfile() const
    {
        return myAlarmProfile;
    }

    const TL1_SmartParameter<CT_FacilitySubType>& 
        GetFac2Type() const
    {
        return myFac2Type;
    }

    const TL1_SmartParameter<TL1_FacAddr_List>&
        GetMemberList() const
    {
        return myMemberList;
    }

    const TL1_SmartParameter<CT_FacilitySubType>&
        GetMemberFacType() const
    {
        return myMemberFacType;
    }

    const TL1_SmartParameter<CT_SM_PST>&
        GetPST() const
    {
        return myPST;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>&
        GetPSTQ() const
    {
        return myPSTQ;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSST() const
    {
        return mySST;
    }

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetMemberAddr() const
    {
        return myMemberAddr;
    }

    const TL1_SmartParameter<CT_FacilitySubType>& 
        GetMemberType() const
    {
        return myMemberType;
    }

    const TL1_SmartParameter<CT_TEL_VlanTag>& 
        GetVlanTag() const
    {
        return myVlanTag;
    }

    const TL1_SmartParameter<bool>& 
        GetTagMode() const
    {
        return myTagMode;
    }

    const TL1_SmartParameter<CT_TEL_Tpid>& 
        GetTpid() const
    {
        return myTpid;
    }

    const TL1_SmartParameter<int>& 
        GetCFProfile() const
    {
        return myCFProfile;
    }

    const TL1_SmartParameter<bool>& 
        GetLacpEnabled() const
    {
        return myLacpEnabled;
    }

    const TL1_SmartParameter<int>& 
        GetLacpSystemPriority() const
    {
        return myLacpSystemPriority;
    }

    const TL1_SmartParameter<CT_LacpSystemId>& 
        GetLacpSystemId() const
    {
        return myLacpSystemId;
    }

    const TL1_SmartParameter<CT_TEL_LacpTimeoutMode>& 
        GetLacpTimeoutMode() const
    {
        return myLacpTimeoutMode;
    }

    const TL1_SmartParameter<int>& 
        GetLacpPriorityMbr() const
    {
        return myLacpPriorityMbr;
    }

    const TL1_SmartParameter<CT_TEL_LacpPartiMode>& 
        GetLacpPartiModeMbr() const
    {
        return myLacpPartiModeMbr;
    }

    const TL1_SmartParameter<CT_TEL_LacpPortState>& 
        GetLacpPortState() const
    {
        return myLacpPortState;
    }

    const TL1_SmartParameter<int>& 
        GetActLacpSystemPriority() const
    {
        return myActLacpSystemPriority;
    }

    const TL1_SmartParameter<CT_LacpSystemId>& 
        GetActLacpSystemId() const
    {
        return myActLacpSystemId;
    }

    const TL1_SmartParameter<uint32>& 
        GetActLacpAdminKey() const
    {
        return myActLacpAdminKey;
    }

    const TL1_SmartParameter<int>& 
        GetPtnLacpSystemPriority() const
    {
        return myPtnLacpSystemPriority;
    }

    const TL1_SmartParameter<CT_LacpSystemId>& 
        GetPtnLacpSystemId() const
    {
        return myPtnLacpSystemId;
    }

    const TL1_SmartParameter<uint32>& 
        GetPtnLacpAdminKey() const
    {
        return myPtnLacpAdminKey;
    }


private:

    TL1_SmartParameter<CT_TL1_FacAddr>      myAid;
    TL1_SmartParameter<CT_TL1_FacAddr>      myFac1Addr;
    TL1_SmartParameter<CT_FacilitySubType>  myFac1Type;
    TL1_SmartParameter<CT_TL1_FacAddr>      myFac2Addr;
    TL1_SmartParameter<CT_FacilitySubType>  myFac2Type;
    TL1_SmartParameter<TL1_FacAddr_List>    myMemberList;
    TL1_SmartParameter<CT_FacilitySubType>  myMemberFacType;
    TL1_SmartParameter<CT_ProfileTableId>   myAlarmProfile;
    TL1_SmartParameter<CT_SM_PST>           myPST;
    TL1_SmartParameter<CT_SM_PSTQ>          myPSTQ;
    TL1_SmartParameter<CT_SM_SST>           mySST;
    TL1_SmartParameter<CT_TL1_FacAddr>      myMemberAddr;
    TL1_SmartParameter<CT_FacilitySubType>  myMemberType;
    TL1_SmartParameter<CT_TEL_VlanTag>      myVlanTag;
    TL1_SmartParameter<bool>                myTagMode;
    TL1_SmartParameter<CT_TEL_Tpid>         myTpid;
    TL1_SmartParameter<int>                 myCFProfile;
    TL1_SmartParameter<bool>                   myLacpEnabled;
    TL1_SmartParameter<int>                    myLacpSystemPriority;
    TL1_SmartParameter<CT_LacpSystemId>        myLacpSystemId;
    TL1_SmartParameter<CT_TEL_LacpTimeoutMode> myLacpTimeoutMode;
    TL1_SmartParameter<int>                  myLacpPriorityMbr;
    TL1_SmartParameter<CT_TEL_LacpPartiMode> myLacpPartiModeMbr;
    TL1_SmartParameter<CT_TEL_LacpPortState> myLacpPortState;

    TL1_SmartParameter<int>                    myActLacpSystemPriority;
    TL1_SmartParameter<CT_LacpSystemId>        myActLacpSystemId;
    TL1_SmartParameter<uint32>                 myActLacpAdminKey;

    TL1_SmartParameter<int>                    myPtnLacpSystemPriority;
    TL1_SmartParameter<CT_LacpSystemId>        myPtnLacpSystemId;
    TL1_SmartParameter<uint32>                 myPtnLacpAdminKey;

};

typedef TL1_Rtv_Response< TL1_LagRspBlk > TL1_LagResponse;



//-----------------------------------------------------------------

class TL1_LagMemberRspBlk: public TL1_GeneralRspBlk
{
public:

    TL1_LagMemberRspBlk();

    TL1_LagMemberRspBlk(
        const TL1_SmartParameter<CT_TL1_FacAddr>& theEntityAddr,
        const TL1_SmartParameter<CT_TL1_FacAddr>& theFacAddr,
        const TL1_SmartParameter<CT_FacilitySubType>&  theFacType,    
        const TL1_SmartParameter<int>& theLacpPriority,
        const TL1_SmartParameter<CT_TEL_LacpPartiMode>& theLacpPartiMode, 
        const TL1_SmartParameter<CT_TEL_LacpPortState>& theLacpPortState,
        const TL1_SmartParameter<CT_SM_PST>&      thePST,
        const TL1_SmartParameter<CT_SM_PSTQ>&     thePSTQ,
        const TL1_SmartParameter<CT_SM_SST>&      theSST);

    TL1_LagMemberRspBlk(const TL1_LagMemberRspBlk& rspBlk);

    virtual ~TL1_LagMemberRspBlk();

    TL1_LagMemberRspBlk& operator=( const TL1_LagMemberRspBlk& theBlock );

    bool operator==( const TL1_LagMemberRspBlk& theBlock ) const;

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetAid() const
    {
        return myAid;
    }

    const TL1_SmartParameter<CT_TL1_FacAddr>& 
        GetFacAddr() const
    {
        return myFac1Addr;
    }

    const TL1_SmartParameter<CT_FacilitySubType>& 
        GetFacType() const
    {
        return myFac1Type;
    }

    const TL1_SmartParameter<CT_SM_PST>&
        GetPST() const
    {
        return myPST;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>&
        GetPSTQ() const
    {
        return myPSTQ;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSST() const
    {
        return mySST;
    }

    const TL1_SmartParameter<int>& 
        GetLacpPriority() const
    {
        return myLacpPriority;
    }

    const TL1_SmartParameter<CT_TEL_LacpPartiMode>& 
        GetLacpPartiMode() const
    {
        return myLacpPartiMode;
    }

    const TL1_SmartParameter<CT_TEL_LacpPortState>& 
        GetLacpPortState() const
    {
        return myLacpPortState;
    }

private:

    TL1_SmartParameter<CT_TL1_FacAddr>       myAid;
    TL1_SmartParameter<CT_TL1_FacAddr>       myFac1Addr;
    TL1_SmartParameter<CT_FacilitySubType>   myFac1Type;
    TL1_SmartParameter<int>                  myLacpPriority;
    TL1_SmartParameter<CT_TEL_LacpPartiMode> myLacpPartiMode;
    TL1_SmartParameter<CT_TEL_LacpPortState> myLacpPortState;
    TL1_SmartParameter<CT_SM_PST>            myPST;
    TL1_SmartParameter<CT_SM_PSTQ>           myPSTQ;
    TL1_SmartParameter<CT_SM_SST>            mySST;

};

typedef TL1_Rtv_Response< TL1_LagMemberRspBlk > TL1_LagMemberResponse;

#endif  // #ifndef __TL1_LAG_RESPONSE_BLOCK_H_
#endif  // #ifdef  __cplusplus

