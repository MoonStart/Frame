/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2007  Kumar C Solai
 DESCRIPTION:   TSXC_RollAction  Class Definition
--------------------------------------------------------------------------*/
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef TSXC_ROLLACTION_H
#define TSXC_ROLLACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>
#include <T6100_ShelfIf.h>
#include <T6100_CardIf.h>
#include <XC/TSXC_RollCommand.h>
#include <XC/TSXC_RollResponse.h>

#define ROLL_TIMEOUT  10*1000  // 10 seconds

//-------------------------------------------------------------------------------
enum TSXC_RollType
{
    ROLL_TYPE_NONE = 0,
    ROLL_TYPE_SIMPLE,
    ROLL_TYPE_COMPLEX
};
    
//-------------------------------------------------------------------------------
typedef struct roll_conn_info {
    UINT8                   ShelfID;
    UINT8                   SlotID;
    UINT8                   SrcFac;
    CT_FAC_StsMap           SrcFacStsMap; 
    UINT8                   DstFac;
    CT_FAC_StsMap           DstFacStsMap; 
    CT_XC_ConnectType       ConnType;
    CT_XC_ConnectMapping    Xc_Mapping;
    bool                    IsNanoMesh;
    bool                    XcAllowed;
    TSXC_RollType           RollType;
    UINT8                   RemoteSrcSlot;    
    UINT16                  RemoteSrcChan;
    UINT16                  DestChanIndex;
    UINT16                  ChannelIndex;
    UINT16                  ChannelCount;             
    UINT16                  MulticastId;    
    UINT16                  MulticastIMUXLMap;
    UINT16                  MulticastIMUXPMap;
    UINT16                  MulticastIdFlex;    
    UINT16                  MulticastIMUXLMapFlex;   
    UINT16                  MulticastIMUXPMapFlex;
} TSXC_RollConnInfo;

//-------------------------------------------------------------------------------
typedef struct roll_queue {
    vector<TSXC_RollConnInfo>    newSrcConnInfo;
    vector<TSXC_RollConnInfo>    spfabConnInfo;
    vector<TSXC_RollConnInfo>    removeConnInfo;
    vector<TSXC_RollConnInfo>    postConnInfo;        
} TSXC_RollQueue;

//-------------------------------------------------------------------------------
enum TSXC_RollFsmState
{
   ROLL_IDLE=0x0100,
   ROLL_WAIT_FOR_RES_FROM_NSM,
   ROLL_WAIT_FOR_RES_FROM_OSM,
   ROLL_WAIT_FOR_RES_FROM_FDM,
   ROLL_WAIT_FOR_RES_FROM_NSMA,           
   ROLL_WAIT_FOR_RES_FROM_SMN,                      
   ROLL_WAIT_FOR_RES_FROM_SPFAB,                   
   ROLL_STATE_INVALID
};
       
//-------------------------------------------------------------------------------
class FC_BbAction;
	
class TSXC_RollAction : public FC_Action
{
public:

	// Constructor 
	TSXC_RollAction(); 

	// Destructor
	virtual ~TSXC_RollAction();

	// ***************************************************
	// This method causes this object to execute its main
	// function of monitoring the Roll connections.
	// ***************************************************
	virtual FC_Object* DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam = NULL);

	virtual void Run( FC_Object* theObject = NULL );

	FC_BbAction* GetBbAction() { return myBbAction; }
    
    void SetDebugLevel(int theValue);
    void SetupNextQueueElements();
    void StartRoll();
    void AddNewSrcConnection(const TSXC_RollConnInfo& theNewSrc);
    void AddPostConnection(const TSXC_RollConnInfo& theNewDst);
    void AddSpfabConnection(const TSXC_RollConnInfo& theSpfabConn);
    void AddRemoveConnection(const TSXC_RollConnInfo& theRemoveConn);
    void AddSpfabRemoveConnection(const TSXC_RollConnInfo& theRemoveConn);
    void SetConnection(const TSXC_RollConnInfo& theCInfo, bool theResponseNeeded);
    void RemoveConnection(const TSXC_RollConnInfo& theCInfo);
    void ClearLastRequest(const TSXC_RollConnInfo& aCInfo, bool theClearMyInput, bool theSendNoReq);
    
    /* void SendQueryActivateStatus(TSXC_RollConnInfo theCInfo, bool theResponseNeeded); */
    void SendQueryRemoteSrcAdded(const TSXC_RollConnInfo& theCInfo, bool theResponseNeeded);
    void SetSourceMC(const TSXC_RollConnInfo& theCInfo, XC_ConnAction Action);
    void SetRouteInfo(CT_ShelfId theShelfID, UINT8 theSlotID, int theChanIndex, int theSrcChan, UINT8 theSrcSlot);     
    void NanoMeshSendRollRmvRequest(const TSXC_RollConnInfo& theCInfo, int theMIndex, bool theResponseNeeded, int theCmd);
    void NanoMeshSetConnection(const TSXC_RollConnInfo& theCInfo, int theMIndex, bool theResponseNeeded);    
    void NanoMeshStartRoll();
    
    TSXC_RollFsmState GetRollState();
    UINT32  GetCommandID(const TSXC_RollConnInfo& theCInfo);
      
private:

	FC_BbAction*            myBbAction;
    FC_PeriodicProcess*     myPeriodicProcess;
    FC_Milliseconds         myTimeStart;             
    FC_Milliseconds         myTimeEnd;
    bool                    myShelfIsNano;
    INT32                   myResponseFlag;               
    INT32                   myDebugLevel;
    UINT32                  myRollCommandID;
    TSXC_RollFsmState       myRollState;
    vector<TSXC_RollQueue>  myRollQueue;
};

#endif /* TSXC_ROLLACTION_H */
