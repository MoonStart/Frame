// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef __SP_ODUKSNC_H__
#define __SP_ODUKSNC_H__

#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegion.h>
#include <map>

class CSM_CardConfigStatusRegion;
class CSM_CardStatusRegion;
class SP_1plus1SubApplication;
class SP_1plus1ProtectionAction;
class SP_1plus1Selector;

typedef map< unsigned int, unsigned int, greater<unsigned int> > SP_PortMap;

typedef enum SP_SncServerLayer_Enum
{
    Server_Layer_OTUk,
    Server_Layer_ODUk,
    Server_Layer_None
} SP_SncServerLayer;

enum SP_SncSelSwitchDir
{
   SP_SEL_SWITCH_TO,
   SP_SEL_SWITCH_AWAY,
   SP_SEL_SWITCH_DIR_UNKNOWN
};

#define DISPLAY_SNC_SERVER_LAYER_TYPE(layer)  \
    ((layer) ==  Server_Layer_OTUk ? "Server Layer OTUk": \
	 (layer) ==  Server_Layer_ODUk ? "Server Layer ODUk": \
     (layer) ==  Server_Layer_None ? "Server Layer None": "?" )

#define DISPLAY_SNC_SEL_SWITCH_DIR(layer)  \
    ((layer) ==  SP_SEL_SWITCH_TO ? "Switch To": \
	 (layer) ==  SP_SEL_SWITCH_AWAY ? "Switch Away From": \
     (layer) ==  SP_SEL_SWITCH_DIR_UNKNOWN ? "Unknown Direction": "?" )

#define SP_TCM_PORT_ID CT_PORT_SIDE_40

class SP_OduKSnc
{
public:
	/* CTOR */                  SP_OduKSnc(SP_1plus1SubApplication & theApplIf, SP_1plus1ProtectionAction& theProtAction, SP_1plus1Selector& theSelector, int theIndex);
	virtual                     ~SP_OduKSnc();
    CT_SP_Protection            GetCurrentSelection();
	CT_SP_Protection            GetInitialSelection();
	void                        Enable();
	void                        Disable(CT_SP_Protection theSide);
    bool                        GetSFDefects(CT_SP_Protection theSide, uint32* theCount, bool* theState);
	bool                        GetSDDefects(CT_SP_Protection theSide, uint32* theCount, bool* theState);
	bool                        IsConfigurationMismatch(CT_SP_Protection theSide);
	bool                        CheckConfiguration(SP_ProtectionGroupConfig& theConfig);
	bool                        IsProtectionGroupDifferent(SP_ProtectionGroupConfig& theConfig);
	void                        Switch(CT_SP_Protection theSelectedSide);
	void                        Commit();
	void                        AddPortMapping(CT_IntfId thePort, unsigned int tspiiPort, bool isOduType = false);
	void                        ResetData();
	void                        DumpData();
	int                         GetIndex(CT_SP_Protection theSide);
	void                        GetAlmAppIf(uint32 theOduIdentifier, SP_AlmAppIfCollection& theAlmIfCollection);
	bool                        AreDependenciesReady(SP_ProtectionGroupConfig& theConfig);
	CT_IntfId                   GetClientOduKPort(CT_ODU_Identifier aOduIdentifier);
	bool                        ManageInputRegions(CT_SP_Protection theSide, bool addInput, bool removeInput, bool checkInput);
    bool                        ManageTcmInputRegions(CT_SP_Protection theSide, bool addInput, bool removeInput, bool checkInput);
	FC_Milliseconds             GetSncWTROffset();
    void                        SetXcRegions(TSXC_S1RtRegion<TSXC_S1Route>*   theXCRouteCfgRegion, TSXC_MCastFilterRegion<TSXC_MCastFilter>*  theMCFilterRegion);
    void                        SetCfgMiscRegion(CFG_MiscCfgRegion* theCfgSwitchModeRegion);

    //TODO implemetation not merged into this version
    void                        SetFppSquelchEnabled(bool theEnable) {};
    bool                        IsDropContinue(CT_SP_Protection theSide) {return 0; };

    void                        RefreshAps() {};
    uint32                      GetRxLocalApsBytes() {return 0; };
    uint32                      GetRxRemoteApsBytes() {return 0; };
	
	//for aps transmitting
    uint32                      ConvertCurrentReqToTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest);
    uint32                      ConvertCurrentReqToTxApsBytes(CT_SP_Request theRequest, bool theRemoteOrLocalRequest);

    void                        PrepareTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest);

    void                        PrepareTxApsBytes();
    void                        SetTxApsBytes(bool theApsInsert =true);
    void                        DisplayTxApsBytes(uint32 theTxApsBytes);//display TxApsBytes as specified format
    uint32                      GetTxApsBytes();

    CT_SP_ProtectionPair<bool>  GetMySourcesLocal() {return mySourcesLocal;};
	CT_SP_ProtectionPair<uint16> GetMyTspiiOduIdx() {return myTspiiOduIdx;};
    CT_SP_ProtectionPair<unsigned int> GetMyTspiiOduPort() {return myTspiiOduPort;};
    CT_ShelfId GetMyShelfId() {return myShelfId;};
    CT_SlotId  GetMySlotId(){return mySlotId;};

private:
	//Data members:
	SP_1plus1SubApplication & myApplIf;
	SP_1plus1ProtectionAction& myProtectionAction;
	SP_1plus1Selector& mySelector;
    
    int myPrivIndex;
	bool myUserCommandIsPending;
	bool myIsConfigured;

    CT_SP_ProtectionPair<uint8> myPQWChannels;
    CT_SP_ProtectionPair<bool> mySourcesLocal;
    CT_SP_ProtectionPair<bool> myDC;

	CT_SP_ProtectionPair<uint16> myTxMsg;
    CT_SP_ProtectionPair<CT_Port> myMatePortOf;
    CT_SP_ProtectionPair<SP_SncSelSwitchDir> myPrevSelSwitchDir;

	CT_SP_ProtectionPair<int> myXcIndex;

	CT_SP_ProtectionPair<CT_IntfId> myServerLayerPort;
	CT_SP_ProtectionPair<CT_IntfId> myTwoStageTopServerLayerPort;
    CT_SP_ProtectionPair<int>       myServerLayerIdx;
    CT_SP_ProtectionPair<int>       myTwoStageTopServerLayerIdx;
    CT_SP_ProtectionPair<SP_SncServerLayer> myServerLayerType;
    CT_SP_ProtectionPair<SP_SncServerLayer> myTwoStageTopServerLayerType;
	CT_SP_ProtectionPair<CT_ODU_Identifier> myServerLayerOduId;
	CT_SP_ProtectionPair<CT_ODU_Identifier> myTwoStageTopServerLayerOduId;
	CT_SP_ProtectionPair<uint16> myServerTspiiIdx;
	CT_SP_ProtectionPair<uint16> myTwoStageTopServerTspiiIdx;
	CT_SP_ProtectionPair<unsigned int> myServerTspiiPort;
	CT_SP_ProtectionPair<unsigned int> myTwoStageTopServerTspiiPort;

    CT_SP_ProtectionPair<CT_IntfId> myLayerPort;
    CT_SP_ProtectionPair<int>       myLayerIdx;
	CT_SP_ProtectionPair<uint16> myTspiiOduIdx;
	CT_SP_ProtectionPair<unsigned int> myTspiiOduPort;


    CT_SP_ProtectionPair<CT_IntfId> myOtuKPort;
    CT_SP_ProtectionPair<int>       myOtuKIdx;

	//APS/PCC Overhead, take care: it's defined as UINT32 TYPE
    uint32	myTxApsBytes;

    //TCM info
    CT_SP_ProtectionPair<CT_ODU_ServerID> myServerLinkageId;
    CT_SP_ProtectionPair<CT_ODU_Identifier> myTcmId;
    CT_SP_ProtectionPair<int>       myTcmIdx;
    CT_SP_ProtectionPair<uint16> myTspiiTcmIdx;

	//Various XC region ptrs
    TSXC_S1RtRegion<TSXC_S1Route>*   myXCRouteCfgRegion; //Route config region (input)
    TSXC_MCastFilterRegion<TSXC_MCastFilter>*  myMCFilterRegion;

	//CFG Misc region
	CFG_MiscCfgRegion* myCfgSwitchModeRegion;

    //CSM card config region
    CSM_CardConfigStatusRegion* myCsmConfigRegion;
    //CSM card status region
    CSM_CardStatusRegion* myCsmStatusRegion;

    //Shelf id
    CT_ShelfId myShelfId;
    CT_SlotId  mySlotId;
	CT_ShelfId myMateLogicalShelf;

    SP_PortMap myPortMap;
    SP_PortMap myServerObserveMap;
    SP_PortMap myOtuObserveMap;
    SP_PortMap myClientObserveMap;
    SP_PortMap myTcmObserveMap;

    //PQW Debug Info
    CT_SP_ProtectionPair<uint16> myTxPQM;
    CT_SP_ProtectionPair<uint8>  myTxSFH;
    CT_SP_ProtectionPair<uint8>  myTxSFL;
    CT_SP_ProtectionPair<uint8>  myTxSD;
    CT_SP_ProtectionPair<uint8>  myTxPQWInvalid;
    CT_SP_ProtectionPair<uint8>  myTxHWSquelch;
    CT_SP_ProtectionPair<uint16> myRxPQM;
    CT_SP_ProtectionPair<uint8>  myRxSFH;
    CT_SP_ProtectionPair<uint8>  myRxSFL;
    CT_SP_ProtectionPair<uint8>  myRxSD;
    CT_SP_ProtectionPair<uint8>  myRxPQWInvalid;
    CT_SP_ProtectionPair<uint8>  myRxHWSquelch;
    CT_SP_ProtectionPair<uint16> myDefectStatus;
    //SwitchParams Debug Info
    bool                         mySwitchingAllowed;
    uint16                       myUserCmdMsg;
    SP_SncSelSwitchDir           myWDir;
    SP_SncSelSwitchDir           myPDir;
    bool                         mySendMessage;
    bool                         myMateActive;
    CT_SP_Protection             myCurrentSelection;

	//Functions:
	void                        AssignPriorityTable();
	void                        SetupPQWConnection(CT_SP_Protection theSide, bool configure, bool writeToHw);
	bool                        GetRxSFHigh(CT_SP_Protection theSide, uint8 thePQWChannel);
	bool                        GetRxSFLow(uint8 thePQWChannel);
	bool                        GetRxSD(uint8 thePQWChannel);
	bool                        GetTxSFHigh(uint8 thePQWChannel);
	bool                        GetTxSFLow(uint8 thePQWChannel);
	bool                        GetTxSD(uint8 thePQWChannel);
	bool                        EvaluateConnectionPattern(CT_SP_Protection theSide, uint32 thePortId, bool doSave, int* theIdx, bool* isDC);
	bool                        GetMateModPresence(CT_SP_Protection theSide);
	void                        ConfigureLogicalShelfId(bool configure, CT_ShelfId wShelf, CT_ShelfId pShelf);
	void                        MulticastSelectorImp(CT_SP_Protection theSide, SP_SncSelSwitchDir theDir);
	void                        SourceTxControlSelectorImp(CT_SP_Protection theSide, SP_SncSelSwitchDir theDir);
	void                        SendSelStateMessage(uint16 usrCmdMsg, CT_SP_Protection theSide, SP_SncSelSwitchDir theDir);
	void                        GetSwitchParams(bool* switchingAllowed, uint16* userCmdMsg, SP_SncSelSwitchDir* theWDir, SP_SncSelSwitchDir* thePDir, bool* sendMessage, bool* mateActive, CT_SP_Protection theCurrentSelection);
	bool                        SetXcParams(CT_SP_Protection theSide, bool isDropAndContinue, int theXcIndex, bool doSave);
	bool                        FindClientAndServerLayers(CT_SP_Protection theSide, uint32 theOduIdentifier, bool doSave);
    bool                        FindTcmLayers(CT_SP_Protection theSide, uint32 theOduIdentifier, bool doSave);
	CT_IntfId                   GetServerOduKPort(CT_ODU_ServerID theServerId);
	uint16                      GetTSPIIOduKIndex(CT_ODU_Identifier aOduIdentifier);
	unsigned int                GetTspiiPort(CT_IntfId thePort, bool isOduType = false);
	void                        DisableLite(CT_SP_Protection theSide); //Disable function on a diet
    void                        DispPQW();
    void                        DispSwitchParams(bool switchingAllowed, uint16 userCmdMsg, SP_SncSelSwitchDir theWDir, SP_SncSelSwitchDir thePDir, bool sendMessage, bool mateActive, CT_SP_Protection theCurrentSelection);
    uint16                      GetUplayerPhysicalPort(CT_ODU_ServerID theServerID);


};

#endif /* __SP_ODUKSNC_H__ */

