/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Network Element Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Network Element Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_NE_RESPONSE_BLOCK_H_
#define __TL1_NE_RESPONSE_BLOCK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_CardInventory.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TIMEZONE_H_
#include <CommonTypes/CT_TimeZone.h>
#endif

#ifndef _CT_CONTROLPLANEDEFS_H_
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_ARC_Definitions.h>

class TL1_NERspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_NERspBlk();
    
    TL1_NERspBlk(const string* EntityName, 
                  const CT_NodeConfiguration* NodeCfg,
                  const CT_NodeSubTypeConfiguration* SubNodeCfg, 
                  const CT_NodeReleaseConfiguration* HWVersion,
                  const CT_NodeSpanConfiguration* SpanA,
                  const CT_NodeSpanConfiguration* SpanB,
                  const string* Location,
                  const string* SystemID,
                  const string* Site,
                  const string* Version,
                  const string* Vendor,
                  const CT_TimeZone* TimeZone,
                  const bool* DSPMode,
                  const CT_NodeStsVcMode* StsVcMode,
                  const CT_ARCInterval* StsVcArcIntvHr,
                  const CT_ARCInterval* StsVcArcIntvMn,
                  const CT_SyncOsc* SyncOsc,
                  const uint8* defInterPacketGap,
                  const int* ctIntValueIntA,
                  const CT_DCM_FiberType* ctFiberTypeIntA,
                  const bool* ctLowLatencyIntA,
                  const int* ctIntValueIntB,
                  const CT_DCM_FiberType* ctFiberTypeIntB,
                  const bool* ctLowLatencyIntB,
                  const int* ctIntValueIntC,
                  const CT_DCM_FiberType* ctFiberTypeIntC,
                  const bool* ctLowLatencyIntC,
                  const int* ctIntValueIntD,
                  const CT_DCM_FiberType* ctFiberTypeIntD,
                  const bool* ctLowLatencyIntD,
                  const int* ctIntValueIntE,
                  const CT_DCM_FiberType* ctFiberTypeIntE,
                  const bool* ctLowLatencyIntE,
                  const int* ctIntValueIntF,
                  const CT_DCM_FiberType* ctFiberTypeIntF,
                  const bool* ctLowLatencyIntF,
                  const int* ctIntValueIntG,
                  const CT_DCM_FiberType* ctFiberTypeIntG,
                  const bool* ctLowLatencyIntG,
                  const int* ctIntValueIntH,
                  const CT_DCM_FiberType* ctFiberTypeIntH,
                  const bool* ctLowLatencyIntH,
                  const int* ctIntValueExtA,
                  const CT_DCM_FiberType* ctFiberTypeExtA,
                  const bool* ctLowLatencyExtA,
                  const int* ctIntValueExtB,
                  const CT_DCM_FiberType* ctFiberTypeExtB,
                  const bool* ctLowLatencyExtB,
                  const int* ctIntValueExtC,
                  const CT_DCM_FiberType* ctFiberTypeExtC,
                  const bool* ctLowLatencyExtC,
                  const int* ctIntValueExtD,
                  const CT_DCM_FiberType* ctFiberTypeExtD,
                  const bool* ctLowLatencyExtD,
                  const int* ctIntValueExtE,
                  const CT_DCM_FiberType* ctFiberTypeExtE,
                  const bool* ctLowLatencyExtE,
                  const int* ctIntValueExtF,
                  const CT_DCM_FiberType* ctFiberTypeExtF,
                  const bool* ctLowLatencyExtF,
                  const int* ctIntValueExtG,
                  const CT_DCM_FiberType* ctFiberTypeExtG,
                  const bool* ctLowLatencyExtG,
                  const int* ctIntValueExtH,
                  const CT_DCM_FiberType* ctFiberTypeExtH,
                  const bool* ctLowLatencyExtH,
                  const CT_ProfileTableId* SysAlmPf,
                  const CT_CPInit* CpInit,
                  const uint8* CpReady,
                  const CT_SM_PST* PST, 
                  const CT_SM_PSTQ* PSTQ, 
                  const CT_SM_SST* SST);

    TL1_NERspBlk(const TL1_NERspBlk& NEBlk);
    
    virtual ~TL1_NERspBlk();

    TL1_NERspBlk& operator=( const TL1_NERspBlk& theBlock );

    bool operator==( const TL1_NERspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetNodeCfg( CT_NodeConfiguration& ) const ;
    
    bool GetSubNodeCfg(CT_NodeSubTypeConfiguration& ) const;

    bool GetHWVersion(CT_NodeReleaseConfiguration & ) const;

    bool GetSpanA(CT_NodeSpanConfiguration & ) const;

    bool GetSpanB(CT_NodeSpanConfiguration & ) const;

    bool GetLocation(string & ) const;

    bool GetSystemID(string & ) const;

    bool GetSite(string & ) const;

    bool GetVersion(string & ) const;

    bool GetVendor(string & ) const;

    bool GetTimeZone(CT_TimeZone & ) const;

    bool GetDSPMode(bool & ) const;

    bool GetStsVcMode(CT_NodeStsVcMode & ) const;

    bool GetStsVcArcIntvHr(CT_ARCInterval & ) const;

    bool GetStsVcArcIntvMn(CT_ARCInterval & ) const;
    
    bool GetSyncOsc(CT_SyncOsc & ) const;

    bool GetDefInterPacketGap(uint8 & ) const;

    bool GetIntValueIntA(int & ) const;
    
    bool GetFiberTypeIntA(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntA(bool & ) const;

    bool GetIntValueIntB(int & ) const;
    
    bool GetFiberTypeIntB(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntB(bool & ) const;

    bool GetIntValueIntC(int & ) const;
    
    bool GetFiberTypeIntC(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntC(bool & ) const;

    bool GetIntValueIntD(int & ) const;
    
    bool GetFiberTypeIntD(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntD(bool & ) const;

    bool GetIntValueIntE(int & ) const;
    
    bool GetFiberTypeIntE(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntE(bool & ) const;

    bool GetIntValueIntF(int & ) const;
    
    bool GetFiberTypeIntF(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntF(bool & ) const;

    bool GetIntValueIntG(int & ) const;
    
    bool GetFiberTypeIntG(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntG(bool & ) const;

    bool GetIntValueIntH(int & ) const;
    
    bool GetFiberTypeIntH(CT_DCM_FiberType & ) const;

    bool GetLowLatencyIntH(bool & ) const;

    bool GetIntValueExtA(int & ) const;
    
    bool GetFiberTypeExtA(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtA(bool & ) const;

    bool GetIntValueExtB(int & ) const;
    
    bool GetFiberTypeExtB(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtB(bool & ) const;

    bool GetIntValueExtC(int & ) const;
    
    bool GetFiberTypeExtC(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtC(bool & ) const;

    bool GetIntValueExtD(int & ) const;
    
    bool GetFiberTypeExtD(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtD(bool & ) const;

    bool GetIntValueExtE(int & ) const;
    
    bool GetFiberTypeExtE(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtE(bool & ) const;

    bool GetIntValueExtF(int & ) const;
    
    bool GetFiberTypeExtF(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtF(bool & ) const;

    bool GetIntValueExtG(int & ) const;
    
    bool GetFiberTypeExtG(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtG(bool & ) const;

    bool GetIntValueExtH(int & ) const;
    
    bool GetFiberTypeExtH(CT_DCM_FiberType & ) const;

    bool GetLowLatencyExtH(bool & ) const;

    bool GetSysAlmPf(CT_ProfileTableId & ) const;

    bool GetCpInit( CT_CPInit & ) const;

    bool GetCpReady(uint8 & ) const;

    bool GetPST( CT_SM_PST &) const;

    bool GetPSTQ( CT_SM_PSTQ &) const;

    bool GetSST( CT_SM_SST &) const;

private:
    static const string DefaultSID;
    enum {
        INDEX_EntityName = 0,
        INDEX_NodeCfg,
        INDEX_SubNodeCfg,
        INDEX_HWVersion,
        INDEX_SpanA,
        INDEX_SpanB,
        INDEX_Location,
        INDEX_SystemID,
        INDEX_Site,
        INDEX_Version,
        INDEX_Vendor,
        INDEX_TimeZone,
        INDEX_DSPMode,
        INDEX_StsVcMode,
        INDEX_StsVcArcIntvHr,
        INDEX_StsVcArcIntvMn,
        INDEX_SyncOsc,
        INDEX_DefInterPacketGap,
        INDEX_IntValueIntA,
        INDEX_FiberTypeIntA,
        INDEX_LowLatencyIntA,
        INDEX_IntValueIntB,
        INDEX_FiberTypeIntB,
        INDEX_LowLatencyIntB,
        INDEX_IntValueIntC,
        INDEX_FiberTypeIntC,
        INDEX_LowLatencyIntC,
        INDEX_IntValueIntD,
        INDEX_FiberTypeIntD,
        INDEX_LowLatencyIntD,
        INDEX_IntValueIntE,
        INDEX_FiberTypeIntE,
        INDEX_LowLatencyIntE,
        INDEX_IntValueIntF,
        INDEX_FiberTypeIntF,
        INDEX_LowLatencyIntF,
        INDEX_IntValueIntG,
        INDEX_FiberTypeIntG,
        INDEX_LowLatencyIntG,
        INDEX_IntValueIntH,
        INDEX_FiberTypeIntH,
        INDEX_LowLatencyIntH,
        INDEX_IntValueExtA,
        INDEX_FiberTypeExtA,
        INDEX_LowLatencyExtA,
        INDEX_IntValueExtB,
        INDEX_FiberTypeExtB,
        INDEX_LowLatencyExtB,
        INDEX_IntValueExtC,
        INDEX_FiberTypeExtC,
        INDEX_LowLatencyExtC,
        INDEX_IntValueExtD,
        INDEX_FiberTypeExtD,
        INDEX_LowLatencyExtD,
        INDEX_IntValueExtE,
        INDEX_FiberTypeExtE,
        INDEX_LowLatencyExtE,
        INDEX_IntValueExtF,
        INDEX_FiberTypeExtF,
        INDEX_LowLatencyExtF,
        INDEX_IntValueExtG,
        INDEX_FiberTypeExtG,
        INDEX_LowLatencyExtG,
        INDEX_IntValueExtH,
        INDEX_FiberTypeExtH,
        INDEX_LowLatencyExtH,
        INDEX_SysAlmPf,
        INDEX_CpInit,
        INDEX_CpReady,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool> myBitSet;
    string myEntityName;
    CT_NodeConfiguration myNodeCfg;
    CT_NodeSubTypeConfiguration mySubNodeCfg;
    CT_NodeReleaseConfiguration myHWVersion;
    CT_NodeSpanConfiguration mySpanA;
    CT_NodeSpanConfiguration mySpanB;
    string myLocation;
    string mySystemID;
    string mySite;
    string myVersion;
    string myVendor;
    CT_TimeZone myTimeZone;
    bool myDSPMode;
    CT_NodeStsVcMode myStsVcMode;
    CT_ARCInterval myStsVcArcIntvHr;
    CT_ARCInterval myStsVcArcIntvMn;
    CT_SyncOsc mySyncOsc;
    uint8 myDefInterPacketGap;
    int myIntValueIntA;
    CT_DCM_FiberType myFiberTypeIntA;
    bool myLowLatencyIntA;
    int myIntValueIntB;
    CT_DCM_FiberType myFiberTypeIntB;
    bool myLowLatencyIntB;
    int myIntValueIntC;
    CT_DCM_FiberType myFiberTypeIntC;
    bool myLowLatencyIntC;
    int myIntValueIntD;
    CT_DCM_FiberType myFiberTypeIntD;
    bool myLowLatencyIntD;
    int myIntValueIntE;
    CT_DCM_FiberType myFiberTypeIntE;
    bool myLowLatencyIntE;
    int myIntValueIntF;
    CT_DCM_FiberType myFiberTypeIntF;
    bool myLowLatencyIntF;
    int myIntValueIntG;
    CT_DCM_FiberType myFiberTypeIntG;
    bool myLowLatencyIntG;
    int myIntValueIntH;
    CT_DCM_FiberType myFiberTypeIntH;
    bool myLowLatencyIntH;
    int myIntValueExtA;
    CT_DCM_FiberType myFiberTypeExtA;
    bool myLowLatencyExtA;
    int myIntValueExtB;
    CT_DCM_FiberType myFiberTypeExtB;
    bool myLowLatencyExtB;
    int myIntValueExtC;
    CT_DCM_FiberType myFiberTypeExtC;
    bool myLowLatencyExtC;
    int myIntValueExtD;
    CT_DCM_FiberType myFiberTypeExtD;
    bool myLowLatencyExtD;
    int myIntValueExtE;
    CT_DCM_FiberType myFiberTypeExtE;
    bool myLowLatencyExtE;
    int myIntValueExtF;
    CT_DCM_FiberType myFiberTypeExtF;
    bool myLowLatencyExtF;
    int myIntValueExtG;
    CT_DCM_FiberType myFiberTypeExtG;
    bool myLowLatencyExtG;
    int myIntValueExtH;
    CT_DCM_FiberType myFiberTypeExtH;
    bool myLowLatencyExtH;
    CT_ProfileTableId mySysAlmPf;
    CT_CPInit myCpInit;
    uint8 myCpReady;

    CT_SM_PST          myPST;
    CT_SM_PSTQ         myPSTQ;
    CT_SM_SST          mySST;
};

typedef TL1_Rtv_Response< TL1_NERspBlk > TL1_NEResponse;
#endif  // #ifndef __TL1_NE_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
