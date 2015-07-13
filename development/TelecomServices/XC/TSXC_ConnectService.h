/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     December, 2007  Kumar C Solai
 DESCRIPTION:   TSXC_ConnectService  Class Definition
--------------------------------------------------------------------------*/
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_XC_CONNECTIONMGR_INCLUDED
#define _INC_XC_CONNECTIONMGR_INCLUDED

#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_RollAction.h>
#include <XC/TSXC_TestMenuOnSPM.h>
#include <Configuration/CFG_Definitions.h>

#define GROUP_1 (1)
#define GROUP_2 (2)
#define GROUP_3 (3)
#define GROUP_4 (4)
#define GROUP_5 (5)
#define GROUP_6 (6)
#define GROUP_7 (7)
#define GROUP_8 (8)

#define GROUP_2P (9)
#define GROUP_3P (10)
#define GROUP_4P (11)
#define GROUP_5P (12)
#define GROUP_8P (13)

#define GROUP_3H (14)
#define GROUP_4H (15)
#define GROUP_5H (16)
#define GROUP_8H (17)
#define GROUP_5M (18)

#define GROUP_6P (19)

#define GROUP_END (20)

#define PS_FIRST_SLOT  (1)
#define PS_LAST_SLOT   (16)
#define DEBUG_MSG_LEN  (160)
// -----------------------------------------------------------------------------------------------------------------------    
// This class is the base class for the Cross connect manager
// -----------------------------------------------------------------------------------------------------------------------    
class TSXC_ConnectService 
{
public:

    // Get TSXC_ConnectService singleton instance
    static TSXC_ConnectService* GetInstance();

    friend class TSXC_TestMenuOnSPM;
    friend class TSXC_TestMenuOnSTPM;
    friend class TSXC_RollAction;
    // -----------------------------------------------------------------------------------------------------------------------
    void CommitPairConns( uint8   ShelfA, uint8   SlotA, uint8   ShelfB, uint8   SlotB);
    
    // -----------------------------------------------------------------------------------------------------------------------
    void Connect(   
                CT_XcTerm& SrcOne,                  // Clsss contains pointers to source information one 
                CT_XcTerm& DstOne,                  // Clsss contains pointers to destination information one
                CT_XcTerm& SrcTwo,                  // Clsss contains pointers to source information Two
                CT_XcTerm& DstTwo,                  // Clsss contains pointers to destination information Two 
                const CT_ProtGpType SrcProtScheme,  // Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
                const CT_ProtGpType DstProtScheme,  // Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
                const CT_XC_ConnectionScheme&   ConnScheme,  // Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
                const CT_XC_ConnectType&        ConnType,    // Connect type such as 3c, 12c and etc.
                CT_InterconMode InterConnectMode)            // SPFAB, NONSPFAB and UNKNOWN
    {
        ConnectPair(SrcOne, DstOne, SrcTwo, DstTwo, SrcProtScheme, DstProtScheme, 
                                ConnScheme, ConnType, InterConnectMode, XC_CONNECT);
    }
    
    // -----------------------------------------------------------------------------------------------------------------------
    void Disconnect(
                        CT_XcTerm& SrcOne,                  // Clsss contains pointers to source information one
                        CT_XcTerm& DstOne,                  // Clsss contains pointers to destination information one
                        CT_XcTerm& SrcTwo,                  // Clsss contains pointers to source information Two 
                        CT_XcTerm& DstTwo,                  // Clsss contains pointers to destination information Two 
                        const CT_ProtGpType SrcProtScheme,  // Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
                        const CT_ProtGpType DstProtScheme,  // Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
                        const CT_XC_ConnectionScheme&   ConnScheme,  // Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
                        const CT_XC_ConnectType&        ConnType,    // Connect type such as 3c, 12c and etc.
                        CT_InterconMode InterConnectMode)            // SPFAB, NONSPFAB and UNKNOWN
    {
        ConnectPair(SrcOne, DstOne, SrcTwo, DstTwo, SrcProtScheme, DstProtScheme, 
                            ConnScheme, ConnType, InterConnectMode, XC_DISCONNECT);
    }
    
    // -----------------------------------------------------------------------------------------------------------------------
    void ReplaceConnection(
                        CT_XcInfo& NewConn,                  // Contains new connection information
                        CT_XcInfo& OldConn);                 // Contains old connection information

    // -----------------------------------------------------------------------------------------------------------------------
    void ConnectRequest(
                CT_XcTerm& SrcOne,                  // Clsss contains pointers to source information one 
                CT_XcTerm& DstOne,                  // Clsss contains pointers to destination information one 
                CT_XcTerm& SrcTwo,                  // Clsss contains pointers to source information Two 
                CT_XcTerm& DstTwo,                  // Clsss contains pointers to destination information Two 
                const CT_ProtGpType SrcProtScheme,  // Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
                const CT_ProtGpType DstProtScheme,  // Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
                const CT_XC_ConnectionScheme&   ConnScheme,   // Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
                const CT_XC_ConnectType&        ConnType,     // Connect type such as 3c, 12c and etc.
                CT_InterconMode InterConnectMode,             // SPFAB, NONSPFAB and UNKNOWN  
                XC_ConnAction             Action,             // action as connect or Disconnect
                bool Roll = false,                            // if roll connect or disconnect
                bool IsQrsTransitionReq = false);             // true if this is part of a Qrs Transition

    // ------------------- Helpers -------------------------------------
    TSXC_FrmCfgRegion<TSXC_Connect>* FindXcFrmRegion       ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_MuxCfgRegion<TSXC_MuxCfg>*  FindXcMuxRegion       ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_ConfigRegion<TSXC_Connect>* FindTSXCConfigRegion  ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_S1McRegion<TSXC_S1MCast>*   FindS1McCfgRegion     ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_S1RtRegion<TSXC_S1Route>*   FindS1RtCfgRegion     ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_S3RtRegion<TSXC_S3Route>*   FindS3RtCfgRegion     ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_S3McRegion<TSXC_S3MCast>*   FindS3McCfgRegion     ( CT_ShelfId ShelfNum, uint8  SlotNum );
    TSXC_S2McRegion<TSXC_S2MCast>*   FindS2McCfgRegion     ( CT_ShelfId ShelfNum, uint16 theMCastId );

    uint8                            GetDstSlice         ( CT_XcTerm& theDstTerm, bool useDstLookup, UINT8 DstMuxFac = 0, const CT_FAC_StsMap* DstMuxFacStsMap = NULL );
    uint8                            GetDstSlice         ( CT_Port&   theDstTerm );
    uint16                           GetSlotMap          ( CT_XcTerm& Dest );
    CT_ShelfType                     GetShelfType        ( CT_ShelfId theShelfId );

    TSXC_S2McRegion<TSXC_S2MCast>*   FindS2CMcCfgRegion  ( uint16 theMCastId );

    TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>*   
                                     FindPortDataAllocRegion ( CT_ShelfId ShelfNum, uint8 SlotNum );

protected:
    //Constructor.
    TSXC_ConnectService(){};  
      
private:
    // -----------------------------------------------------------------------------------------------------------------------
        
    static TSXC_ConnectService* ItsInstance;
    static TSXC_RollAction*     myRollActionPtr;
    static TSXC_RollType        myRollType;
    static INT32                myDebugLevel;

    // ------------------------------------------------------------------------------------------------------------------------               
    void ConnectPair(
                CT_XcTerm& SrcOne,                  // Clsss contains pointers to source information one 
                CT_XcTerm& DstOne,                  // Clsss contains pointers to destination information one 
                CT_XcTerm& SrcTwo,                  // Clsss contains pointers to source information Two 
                CT_XcTerm& DstTwo,                  // Clsss contains pointers to destination information Two 
                const CT_ProtGpType SrcProtScheme,  // Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
                const CT_ProtGpType DstProtScheme,  // Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
                const CT_XC_ConnectionScheme&   ConnScheme,   // Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
                const CT_XC_ConnectType&        ConnType,     // Connect type such as 3c, 12c and etc.
                CT_InterconMode InterConnectMode,             // SPFAB, NONSPFAB and UNKNOWN  
                XC_ConnAction             Action);            // action as connect or Disconnect
    // -----------------------------------------------------------------------------------------------------------------------
    void ConnectOrDisconnect(
                CT_ShelfId  ShelfID, UINT8   SlotID,
                UINT8 SrcFac, 
                const CT_FAC_StsMap* SrcFacStsMap, 
                UINT8 DstFac, 
                const CT_FAC_StsMap* DstFacStsMap, 
                CT_XC_ConnectType ConnType, 
                CT_XC_ConnectMapping Xc_Mapping, 
                XC_ConnAction Action,
                bool Xc_Allowed, bool  Roll = false, bool  PostReq = false, bool IsNanoMesh = false,
                bool IsFabSwitch = false, CT_XC_ConnectMapping imuxXcMapping = CT_XC_MAPPING_UNSPECIFIED,
                CT_ProtGpType SrcProtScheme = PROT_GP_UNKNOWN);
    // -----------------------------------------------------------------------------------------------------------------------
    void ConnectOrDisconnectOnSPFAB(
                CT_ShelfId ShelfNum,
                UINT8 SrcFac,
                const CT_FAC_StsMap* SrcFacStsMap, 
                UINT8 DstFac, 
                const CT_FAC_StsMap* DstFacStsMap, 
                CT_XC_ConnectType ConnType, 
                CT_XC_ConnectMapping Xc_Mapping, 
                XC_ConnAction Action,
                bool theRoll);
    // -----------------------------------------------------------------------------------------------------------------------
    void SetSourceMCInfo(
                CT_XcTerm& theSrc,
                UINT8 SrcMuxFac,
                const CT_FAC_StsMap* SrcMuxFacStsMap,
                CT_XcTerm& theDst,
                CT_XC_ConnectType   ConnType,
                XC_ConnAction Action,
                bool theRoll,
                bool theIsQrsTransitionReq,
                UINT8 DstMuxFac = 0,
                const CT_FAC_StsMap* DstMuxFacStsMap = NULL);

    // -----------------------------------------------------------------------------------------------------------------------
    void SetDestinationSrcInfo(
                CT_XcTerm& Dest,
                CT_XcTerm& SrcOne,
                CT_XcTerm& SrcTwo,
                UINT8 DstMuxFac,
                const CT_FAC_StsMap* DstMuxFacStsMap,
                UINT8 SrcOneMuxFac,
                const CT_FAC_StsMap* SrcOneMuxFacStsMap,
                UINT8 SrcTwoMuxFac,
                const CT_FAC_StsMap* SrcTwoMuxFacStsMap,
                const CT_ProtGpType SrcProtScheme,
                CT_XC_ConnectType   ConnType,
                XC_ConnAction Action,
                bool theRoll = false,
                bool theProcessSrcTwo = true);
    // -----------------------------------------------------------------------------------------------------------------------
    void UpdateS2McGroup(
                XC_ConnAction     theAction,
                CT_XcTerm&        theSrc,
                uint16            theMcastId,
                uint8             theMcastShelfId[TSXC_MAX_SHELF_PER_MCAST],
                uint16            theMcastMembers[TSXC_MAX_SHELF_PER_MCAST]);
    // -----------------------------------------------------------------------------------------------------------------------
    void UpdateS2McGroup(
                XC_ConnAction     theAction,
                uint16            theMcastId,
                CT_SwitchMulticastMapSet& theMcastImuxMap);
    // -----------------------------------------------------------------------------------------------------------------------
    void SetDebugLevel(int theValue);
    void GetConnTypeFromSigType( CT_XC_ConnectType* theConnType, CT_TEL_SignalType theSignalType, CT_TEL_TermSize theTermSize);
    void GetFacilityOnSPFAB(UINT8 * theFacility, const CT_XcTerm *theTerm);
    bool IsLineLevelProtScheme(const CT_ProtGpType theProtScheme);
    void DisplayTerm(char termId[30], CT_XcTerm& Term);
    uint16 GetChanOffset(UINT8 theMuxFac, CT_XcTerm& theTerm);
    uint8 S2MCSlotToBitMtera(uint8 theSlotId);

    // -----------------------------------------------------------------------------------------------------------------------

};    
#endif // _INC_XC_CONNECTIONMGR_INCLUDED
