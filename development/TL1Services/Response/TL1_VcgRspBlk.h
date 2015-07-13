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

#ifndef ___TL1_VCG_RESPONSE_BLOCK_H__
#define ___TL1_VCG_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_TL1_Base.h>

#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>

class TL1_VcgRspBlk: public TL1_GeneralRspBlk
{
public:

    TL1_VcgRspBlk();

    TL1_VcgRspBlk(
        const CT_TL1_FacAddr& theAddr,
        bool vcgType,
        const CT_ProfileTableId* theAlarmProfile,
        CT_TEL_TermSize vcatType,
        CT_XcPath ccPath,
        uint32 thePlcThr,
        uint32 theTlcThr,
        bool theHoTmr,
        bool theWtrTmr,
        //CT_TL1_FacAddr rmvTtp,
        CT_XcType theCct,
        int thevcatXarCap,
        bool theLcasActive,
        int thevcatDd,
        CT_TL1_FacAddr addTtp,
        int thevcatXar,
        int thevcatXat,
        int theNValue,
        int thevcatXatCap,
        CT_TL1_SlotAddr theVcgStat,
        int theNpOwner,
        list<int> ttpList,
        const CT_SM_PST&      thePST,
        const CT_SM_PSTQ&     thePSTQ,
        const CT_SM_SST&      theSST);
//constructor used for vcg configuration
    TL1_VcgRspBlk(
        const CT_TL1_FacAddr& theAddr,
        const CT_SM_PST&      thePST,
        const CT_SM_PSTQ&     thePSTQ,
        const CT_SM_SST&      theSST);
//constructor used  vcg member configuration
    TL1_VcgRspBlk(
        const CT_TL1_FacAddr& theAddr,
        const CT_TL1_FacAddr& theTtpAddr,
        const CT_XcFacType&   theTtpType,
        const CT_SM_PST&      thePST,
        const CT_SM_PSTQ&     thePSTQ,
        const CT_SM_SST&      theSST);


    TL1_VcgRspBlk(const TL1_VcgRspBlk& rspBlk);

    virtual ~TL1_VcgRspBlk();

    TL1_VcgRspBlk& operator=( const TL1_VcgRspBlk& theBlock );

    bool operator==( const TL1_VcgRspBlk& theBlock ) const;

    bool GetAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetCardType(CT_CardType& ) const;
    bool GetSubCardType( CT_SubCardType&) const ;
    bool GetIsAutoMode(bool&) const;
    bool GetAlarmProfile(CT_ProfileTableId&) const;
    bool GetVcatType(CT_TEL_TermSize&) const;
    bool GetCCPath(CT_XcPath&) const;
    bool GetPlcThr(uint32&) const;
    bool GetTlcThr(uint32&) const;
    bool GetHoTmr(bool&) const;
    bool GetWtrTmr(bool&) const;
    bool GetAddTtp(CT_TL1_FacAddr&) const;
    bool GetRmvTtp(CT_TL1_FacAddr&) const;
    bool GetAddCrs(CT_TL1_FacAddr&) const;
    bool GetRmvCrs(CT_TL1_FacAddr&) const;
    bool GetCct(CT_XcType&) const;
    bool GetVcatXarCap(int&) const;
    bool GetLcasActive(bool&) const;
    bool GetVcatDd(int&) const;
    bool GetVcatXar(int&) const;
    bool GetVcatXat(int&) const;
    bool GetNValue(int&) const;
    bool GetVcatXatCap(int&) const;
    bool GetVcgStat(CT_TL1_SlotAddr&) const;
    bool GetNpOwner(int& theNpOwner ) const;
    bool GetTtpList(list<int>&) const;
    bool GetAddTtpList(list<int>&) const;
    bool GetRmvTtpList(list<int>&) const;
    bool GetPST(CT_SM_PST& thePst) const;
    bool GetPSTQ(CT_SM_PSTQ& thePstq) const;
    bool GetSST(CT_SM_SST& theSst) const;
    bool GetVlanTag( CT_TEL_VlanTag& theVTag) const;
    bool GetTagMode( bool& theTagMode) const;
    bool GetTpid( CT_TEL_Tpid& theTpid) const;
    bool GetProt( bool& isProtected) const;
    bool GetLcasEnabled( bool& isLcasEnabled) const;

    //VCG member part
    bool GetTtpAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetTtpFacType(CT_XcFacType&) const;
    bool GetCrsAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetCrsFacType(CT_XcFacType&) const;
    bool GetMemberCct(CT_XcType&) const;
    bool GetAutocfg(bool&) const;
    bool GetMemberVcatDd(int&) const;
    bool GetActiveTransmit(bool&) const;
    bool GetActiveReceive(bool&) const;
    bool GetSequenceTransmit(int&) const;
    bool GetSequenceReceive(int&) const;
    bool GetCondition(CT_ConditionType&) const;



    void SetAddr(const CT_TL1_FacAddr& );
    void SetCardType(const CT_CardType& theCardType);
    void SetSubCardType( const CT_SubCardType& theSubCardType);
    void SetIsAutoMode(const bool& );
    void SetAlarmProfile(const CT_ProfileTableId& );
    void SetVcatType(const CT_TEL_TermSize& );
    void SetCCPath(const CT_XcPath& );
    void SetPlcThr(const uint32& );
    void SetTlcThr(const uint32& );
    void SetHoTmr(const bool& );
    void SetWtrTmr(const bool& );
    void SetAddTtp(const CT_TL1_FacAddr&, const CT_XcFacType&  );
    void SetRmvTtp(const CT_TL1_FacAddr&, const CT_XcFacType&  );
    void SetAddCrs(const CT_TL1_FacAddr&, const CT_XcFacType&  );
    void SetRmvCrs(const CT_TL1_FacAddr&, const CT_XcFacType&  );
    void SetCct(const CT_XcType& );
    void SetVcatXarCap(const int& );
    void SetLcasActive(const bool& );
    void SetVcatDd(const int& );
    void SetVcatXar(const int& );
    void SetVcatXat(const int& );
    void SetNValue(const int& );
    void SetVcatXatCap(const int& );
    void SetVcgStat(const CT_TL1_SlotAddr& );
    void SetNpOwner( const int& theNpOwner );
    void SetTtpList(const list<int>& );
    void SetAddTtpList(const list<int>& );
    void SetRmvTtpList(const list<int>& );
    void SetPST(const CT_SM_PST& );
    void SetPSTQ(const CT_SM_PSTQ& );
    void SetSST(const CT_SM_SST& );
    void SetProt(const bool&);
    void SetLcasEnabled(const bool&);

    //VCG member part
    void SetTtpAddr(const CT_TL1_FacAddr& memberAddr, const CT_XcFacType&  theInput);
    void SetCrsAddr(const CT_TL1_FacAddr& memberAddr, const CT_XcFacType&  theInput);
    void SetMemberCct(const CT_XcType& );
    void SetAutocfg(const bool&);
    void SetMemberVcatDd(const int& );
    void SetActiveTransmit(const bool&);
    void SetActiveReceive(const bool&);
    void SetSequenceTransmit(const int&);
    void SetSequenceReceive(const int&);
    void SetVlanTag(const CT_TEL_VlanTag& theVTag);
    void SetTagMode(const bool& theTagMode);
    void SetTpid(const CT_TEL_Tpid& theTpid);
    void SetCondition(const CT_ConditionType& theCond);


private:

/*
   From LumosTypes/LT_Vcg.h:
typedef struct {
    LT_TL1Aid           tl1Aid;
    LT_AutoManual*      vcgType;
    LT_AlarmProfile*    almProfile;
    int *               vcatDd;
    LT_Vcat_Type*       vcatType;
    LT_CCPath*          ccPath;
    int*                plcThr;
    int*                tlcThr;
    LT_On_Off*          hoTmr;
    LT_On_Off*          wtrTmr;
    LT_TL1Aid           rmvTtp;
    LT_TL1Aid           addCrs;
    LT_TL1Aid           rmvCrs;
    LT_Cct*             Cct;
    LT_Yes_No*          lcasActive;
    LT_TL1Aid           addTtp;
    LT_IntRangeList *        ttpMap;
    LT_CpType *         cpType;
    //vcg member part
    LT_TL1Aid           ttpAid;
    LT_TL1Aid           crsAid;
    LT_Yes_No *         autoCfg;
    LT_DiffDelay        differentialDelay;
    LT_Yes_No *         activeTransmit;
    LT_Yes_No *         activeReceive;
    int*                vcatSeqTransmit;
    int*                vcatSeqReceive;
    //evpl
    LT_VLanID           pvid;
    LT_TagMode *        tagMode;
    LT_TPid *           tpid;
    LT_Yes_No *         vcgProt;
    //vcg member part
    LT_ConditionType*        memberCond;
    LT_On_Off*          lcas;
    int *               NValue;
    int *               vcatXar;
    int *               vcatXat;
    int *               vcatXarCap;
    int *               vcatXatCap;
    LT_TL1Aid           vcgStat;
    LT_NpOwner*         npOwner;        // int
    LT_PrimaryState*    primaryState;
    LT_SecondaryStateList * secondaryState;
} LT_VcgRespBlock;

*/

    enum {
        INDEX_EntityName = 0,
        INDEX_myAddr,
        INDEX_myCardType,
        INDEX_mySubCardType,
        INDEX_myIsAutoMode,
        INDEX_myAlarmProfile,
        INDEX_myVcatType,
        INDEX_myCCPath,
        INDEX_myPlcThr,
        INDEX_myTlcThr,
        INDEX_myHoTmr,
        INDEX_myWtrTmr,
        INDEX_myAddTtp,
        INDEX_myRmvTtp,
        INDEX_myAddCrs,
        INDEX_myRmvCrs,
        INDEX_myCct,
        INDEX_myVcatXarCap,
        INDEX_myLcasActive,
        INDEX_myVcatDd,
        INDEX_myVcatXar,
        INDEX_myVcatXat,
        INDEX_myNValue,
        INDEX_myVcatXatCap,
        INDEX_myVcgStat,
        INDEX_myNpOwner,
        INDEX_myTtpList,
        INDEX_myAddTtpList,
        INDEX_myRmvTtpList,
        //VCG member part
        INDEX_myTtpAddr,
        INDEX_myTtpFacType,
        INDEX_myCrsAddr,
        INDEX_myCrsFacType,
        INDEX_myMemberCct,
        INDEX_myAutocfg,
        INDEX_myMemberVcatDd,
        INDEX_myActiveTransmit,
        INDEX_myActiveReceive,
        INDEX_mySequenceTransmit,
        INDEX_mySequenceReceive,
        INDEX_myConditionType,
        //end of member part
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_VlanTag,
        INDEX_TagMode,
        INDEX_Tpid,
        INDEX_myIsProtected,
        INDEX_myLcasEnabled,
        INDEX_END
    };

    vector<bool>       myBitSet;

    CT_TL1_FacAddr          myAddr;
    CT_CardType             myCardType;
    CT_SubCardType          mySubCardType;
    bool                    myIsAutoMode;
    CT_ProfileTableId       myAlarmProfile;
    CT_TEL_TermSize         myVcatType;
    CT_XcPath               myCCPath;
    uint32                  myPlcThr;
    uint32                  myTlcThr;
    bool                    myHoTmr;
    bool                    myWtrTmr;
    CT_TL1_FacAddr          myAddTtp;
    CT_TL1_FacAddr          myRmvTtp;
    CT_TL1_FacAddr          myAddCrs;
    CT_TL1_FacAddr          myRmvCrs;
    CT_XcType               myCct;
    int                     myVcatXarCap;
    bool                    myLcasActive;
    int                     myVcatDd;
    int                     myVcatXar;
    int                     myVcatXat;
    int                     myNValue;
    int                     myVcatXatCap;
    CT_TL1_SlotAddr         myVcgStat;
    int                     myNpOwner;
    list<int>               myTtpList;
    list<int>               myAddTtpList;
    list<int>               myRmvTtpList;
    //VCG member part
    CT_TL1_FacAddr          myTtpAddr;
    CT_XcFacType            myTtpFacType;
    CT_TL1_FacAddr          myCrsAddr;
    CT_XcFacType            myCrsFacType;
    CT_XcType               myMemberCct;
    bool                    myAutocfg;
    int                     myMemberVcatDd;
    bool                    myActiveTransmit;
    bool                    myActiveReceive;
    int                     mySequenceTransmit;
    int                     mySequenceReceive;
    CT_ConditionType        myConditionType;
    //end of member part
    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;
    CT_TEL_VlanTag          myVlanTag;
    bool                    myTagMode;
    CT_TEL_Tpid             myTpid;
    bool                    myIsProtected;
    bool                    myLcasEnabled;
};

typedef TL1_Rtv_Response< TL1_VcgRspBlk > TL1_VCGResponse;

// ---------------------------------------------------------
class TL1_VcgMemberRspBlk: public TL1_GeneralRspBlk
{
public:

    TL1_VcgMemberRspBlk();

    TL1_VcgMemberRspBlk(
        const CT_TL1_FacAddr& theAddr,
        const CT_TL1_FacAddr& theMemberAddr,
        const CT_XcFacType&   theMemberType,
        const CT_SM_PST&      thePST,
        const CT_SM_PSTQ&     thePSTQ,
        const CT_SM_SST&      theSST);


    TL1_VcgMemberRspBlk(const TL1_VcgMemberRspBlk& rspBlk);

    virtual ~TL1_VcgMemberRspBlk();

    TL1_VcgMemberRspBlk& operator=( const TL1_VcgMemberRspBlk& theBlock );

    bool operator==( const TL1_VcgMemberRspBlk& theBlock ) const;

    bool GetAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetMemberAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetMemberFacType(CT_XcFacType&) const;
    bool GetCrsAddr(CT_TL1_FacAddr& theAddr) const;
    bool GetCrsFacType(CT_XcFacType&) const;
    bool GetCct(CT_XcType&) const;
    bool GetAutocfg(bool&) const;
    bool GetVcatDd(int&) const;
    bool GetActiveTransmit(bool&) const;
    bool GetActiveReceive(bool&) const;
    bool GetSequenceTransmit(int&) const;
    bool GetSequenceReceive(int&) const;
    bool GetPST(CT_SM_PST& thePst) const;
    bool GetPSTQ(CT_SM_PSTQ& thePstq) const;
    bool GetSST(CT_SM_SST& theSst) const;
    bool GetCondition(CT_ConditionType& theCond) const;


    void SetAddr(const CT_TL1_FacAddr& );
    void SetMemberAddr(const CT_TL1_FacAddr& memberAddr, const CT_XcFacType&  theInput);
    void SetCrsAddr(const CT_TL1_FacAddr& memberAddr, const CT_XcFacType&  theInput);
    void SetCct(const CT_XcType& );
    void SetAutocfg(const bool&);
    void SetVcatDd(const int& );
    void SetActiveTransmit(const bool&);
    void SetActiveReceive(const bool&);
    void SetSequenceTransmit(const int&);
    void SetSequenceReceive(const int&);
    void SetPST(const CT_SM_PST& );
    void SetPSTQ(const CT_SM_PSTQ& );
    void SetSST(const CT_SM_SST& );
    void SetCondition(const CT_ConditionType&);

private:
/*
typedef struct {
    LT_TL1Aid           vcgAid;
    LT_TL1Aid           ttpAid;
    LT_TL1Aid           crsAid;
    LT_Cct*             Cct;
    LT_Yes_No *         autoCfg;
    LT_DiffDelay *      differentialDelay;
    LT_Yes_No *         activeTransmit;
    LT_Yes_No *         activeReceive;
    int*                vcatSeqTransmit;
    int*                vcatSeqReceive;
    LT_ConditionType *       condType;
    LT_PrimaryState*     primaryState;
    LT_SecondaryStateList * secondaryState;

} LT_VcgMemberRespBlock;*/

    enum {
        INDEX_myAddr = 0,
        INDEX_myMemberAddr,
        INDEX_myMemberFacType,
        INDEX_myCrsAddr,
        INDEX_myCrsFacType,
        INDEX_myCct,
        INDEX_myAutocfg,
        INDEX_myVcatDd,
        INDEX_myActiveTransmit,
        INDEX_myActiveReceive,
        INDEX_mySequenceTransmit,
        INDEX_mySequenceReceive,
        INDEX_myConditionType,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>       myBitSet;

    CT_TL1_FacAddr          myAddr;
    CT_TL1_FacAddr          myMemberAddr;
    CT_XcFacType            myMemberFacType;
    CT_TL1_FacAddr          myCrsAddr;
    CT_XcFacType            myCrsFacType;
    CT_XcType               myCct;
    bool                    myAutocfg;
    int                     myVcatDd;
    bool                    myActiveTransmit;
    bool                    myActiveReceive;
    int                     mySequenceTransmit;
    int                     mySequenceReceive;
    CT_ConditionType        myConditionType;
    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;

};

typedef TL1_Rtv_Response< TL1_VcgMemberRspBlk > TL1_VCGMemberResponse;

#endif  // #ifndef __TL1_VCG_RESPONSE_BLOCK_H_
#endif  // #ifdef  __cplusplus

