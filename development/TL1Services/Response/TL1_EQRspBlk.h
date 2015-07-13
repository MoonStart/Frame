/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Equipment Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Equipment Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_EQPTRESPONSE_BLOCK_H_
#define __TL1_EQPTRESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_Telecom.h>

#include <Agent/Equipment/EQ_BbCardConfig.h>
#include <Agent/Equipment/EQ_BbShelfConfig.h>

#include <vector>
using namespace std;

class TL1_EQRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_EQRspBlk();

    TL1_EQRspBlk(const string* entityName,
                 const CT_TL1_SlotAddr* slotAddr,
                 const CT_CardType*,
                 const CT_SubCardType*,
                 const CT_EqName* cardName,
                 const CT_Band*,
                 const CT_HalfBand*,
                 const CT_TL1_PumpPower*,
                 const CT_Wavelength*,
                 const CT_ShelfType*,
                 const CT_EqName* shelfName,                 
                 const CT_ProfileTableId*,
                 const CT_Function*,
                 const CT_Capacity*,
                 const CT_TEL_TimingMode*,
                 const CT_NumberOfPort*,
                 const CT_Rate*,
                 const CT_OeoRegen*,
                 const CT_InterconMode*,
                 const CT_InterconMode*,//The DFLT for shelves
                 const CT_Mount*,
                 const CT_PktEquip*,
                 const CT_SM_PST*,
                 const CT_SM_PSTQ*,
                 const CT_SM_SST*,
                 const CT_Timer*,       // WaitTo restore timer
                 const CT_Timer*,       // Vcg Timer
                 const CT_Timer*,        // DiffDelayThreashold
                 const CT_NumberOfChan*, //NumbrChan
                 const CT_NumberOfChan*, //ChanLimit
                 const CT_ChanRange*,
                 const CT_Length*,
                 const CT_DCM_FiberType*,
                 const CT_TEL_mBm*,
                 const CT_Preamp*,
                 const CT_Extattn*,
                 const CT_Postamp*,
                 const CT_Type*,
                 const CT_SwitchDomain*,
                 const CT_TEL_SwitchMode*,
                 const CT_Reach*,
				 const CT_Usage*,
                 const CT_CableLength*,//CableLength
                 const CT_ConnPort*,//Connection Port
                 const CT_ConnPortRange*,//Connection Port Range
                 const int* = 0, // theLacpSystemPriority,
                 const CT_LacpSystemId* = 0,//theLacpSystemId,
                 const CT_Modulation* = 0,
                 const CT_FanProfile* = 0,
                 const CT_ModVersion* = 0,
                 const CT_PktShelfType* = 0,//pktshelftype
				 const CT_DiskFormatType* = 0
                 );
                 
    TL1_EQRspBlk(const TL1_EQRspBlk& eqBlk);
    
    virtual ~TL1_EQRspBlk();

    TL1_EQRspBlk& operator=( const TL1_EQRspBlk& theBlock );

    bool operator==( const TL1_EQRspBlk& theBlock ) const;

    bool GetEntityName( string&) const ;

    bool GetSlotAddr( CT_TL1_SlotAddr&) const ;

    bool GetCardType( CT_CardType&) const ;

    bool GetSubCardType( CT_SubCardType&) const ;

    bool GetCardName( CT_EqName&) const ;

    bool GetBand( CT_Band&) const ;

    bool GetHalfBand( CT_HalfBand&) const ;

    bool GetPumpPower( CT_TL1_PumpPower&) const ;

    bool GetChan( CT_Wavelength&) const ;

    bool GetShelfType( CT_ShelfType&) const ;

    bool GetShelfName( CT_EqName&) const ;

    bool GetALMPF( CT_ProfileTableId&) const ;

    bool GetFunction( CT_Function&) const ;

    bool GetCapacity( CT_Capacity&) const ;

    bool GetTimingMode( CT_TEL_TimingMode&) const ;

    bool GetNumberOfPor( CT_NumberOfPort&) const ;

    bool GetRate( CT_Rate&) const ;

    bool GetOeoRegen( CT_OeoRegen&) const ;

    bool GetInterconMode(CT_InterconMode&) const;

    bool GetInterconModeDflt(CT_InterconMode&) const;

    bool GetMount(CT_Mount&) const;

    bool GetPktEquip(CT_PktEquip&) const;

    bool GetPST( CT_SM_PST&) const ;

    bool GetPSTQ( CT_SM_PSTQ&) const ;

    bool GetSST( CT_SM_SST&) const ;

    CT_SM_PST  GetPST() const ;
    CT_SM_PSTQ GetPSTQ() const ;
    CT_SM_SST  GetSST() const ;

    bool GetWaitToRestoreTmr(CT_Timer&) const;
    bool GetVcgTmr(CT_Timer&) const;
    bool GetDiffDelayThreashold(CT_Timer&) const;

    bool GetNumbrChan(CT_NumberOfChan&) const;
    bool GetChanLimit(CT_NumberOfChan&) const;
    bool GetChanRange(CT_ChanRange&) const;
    bool GetLength(CT_Length&) const;
    bool GetFiberType(CT_DCM_FiberType&) const;
    bool GetIL(CT_TEL_mBm&) const;

    bool GetPreamp(CT_Preamp &thePreamp) const;
    bool GetExtAttn(CT_Extattn &theExtAttn) const;
    bool GetPostamp(CT_Postamp &thePostamp) const;

    bool GetType(CT_Type &theType) const;
    bool GetSwitchDomain(CT_SwitchDomain &theSwitchDomain) const;
    bool GetSwitchMode(CT_TEL_SwitchMode &theSwitchMode) const;   
    bool GetReach(CT_Reach &theReach) const; 
	bool GetUsage(CT_Usage &theUsage) const; 
    bool GetCableLength( CT_CableLength &theCableLength) const ;
    bool GetPktShelfType( CT_PktShelfType &PktShelfType) const ;
    bool GetDiskFormatType( CT_DiskFormatType &DiskFormatType) const ;
    bool GetConnPort( CT_ConnPort &theConnPort, CT_ConnPortRange &theConnPortRange)const ;
	bool GetLacpSystemPriority(int &thePriority) const;
	bool GetLacpSystemId(CT_LacpSystemId &theId) const;
    bool GetModulation(CT_Modulation &theModulation) const;
    bool GetFanProfile (CT_FanProfile &theFanProfile) const;
    bool GetModVersion (CT_ModVersion &theModVersion) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_SlotAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_CardName,
        INDEX_Band,
        INDEX_HalfBand,
        INDEX_PumpPower,
        INDEX_Wave,
        INDEX_ShelfType,
        INDEX_ShelfName,
        INDEX_profileID,
        INDEX_Function,
        INDEX_Capacity,
        INDEX_TimingMode,
        INDEX_NumberOfPort,
        INDEX_Rate,
        INDEX_OeoRegen,
        INDEX_InterconMode,
        INDEX_InterconModeDflt,
        INDEX_Mount,
        INDEX_PktEquip,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_WaitToRestore,
        INDEX_VcgTmr,
        INDEX_DiffDelayThreashold,
        INDEX_NumbrChan,
        INDEX_ChanLimit,                        
        INDEX_ChanRange,
        INDEX_Length,
        INDEX_FiberType,
        INDEX_IL,
        INDEX_Preamp,
        INDEX_ExtAttn,
        INDEX_Postamp,
        INDEX_Type,
        INDEX_SwitchDomain,
        INDEX_SwitchMode,
        INDEX_Reach,
		INDEX_Usage,
        INDEX_CableLength,
        INDEX_PktShelfType,
        INDEX_DiskFormatType,
        INDEX_ConnPort,
        INDEX_LacpPri,
        INDEX_LacpId,
        INDEX_Modulation,
        INDEX_FanProfile,
        INDEX_ModVersion,
        INDEX_END
	};

        vector<bool>      myBitSet;
        string            myEntityName; 
        CT_TL1_SlotAddr   mySlotAddr; 
        CT_CardType       myCardType; 
        CT_SubCardType    mySubCardType; 
        CT_EqName         myCardName; 
        CT_Band           myBand; 
        CT_HalfBand       myHalfBand; 
        CT_TL1_PumpPower  myPumpPower; 
        CT_Wavelength     myWave; 
        CT_ShelfType      myShelfType; 
        CT_EqName         myShelfName; 
        CT_ProfileTableId myID; 
        CT_Function       myFunction;
        CT_Capacity       myCapacity;
        CT_TEL_TimingMode myTimingMode;
        CT_NumberOfPort   myNumberOfPort;  
        CT_Rate           myRate;   
        CT_OeoRegen       myOeoRegen;
        CT_InterconMode   myInterconMode;
        CT_InterconMode   myInterconModeDflt;
        CT_Mount          myMount;
        CT_PktEquip       myPktEquip;
        CT_SM_PST         myPST; 
        CT_SM_PSTQ        myPSTQ; 
        CT_SM_SST         mySST;
        CT_Timer          myWaitToRestoreTmr;
        CT_Timer          myVcgTmr;
        CT_Timer          myDiffDelayThreashold;
        CT_NumberOfChan   myNumbrChan;
        CT_NumberOfChan   myChanLimit;                        
        CT_ChanRange      myChanRange;
        CT_Length         myLength;
        CT_DCM_FiberType  myFiberType;
        CT_TEL_mBm        myIL;
        CT_Preamp         myPreamp;
        CT_Extattn        myExtAttn;
        CT_Postamp        myPostamp;
        CT_Type           myType;
        CT_SwitchDomain   mySwitchDomain;
        CT_TEL_SwitchMode mySwitchMode;
        CT_Reach          myReach;
		CT_Usage          myUsage;
        CT_CableLength    myCableLength; 
        CT_PktShelfType   myPktShelfType; 
        CT_DiskFormatType myDiskFormatType; 
        CT_ConnPort       myConnPort;
        CT_ConnPortRange  myConnPortRange;
        CT_LacpSystemId   myLacpSystemId;
        int               myLacpSystemPriority;
        CT_Modulation     myModulation;
        CT_FanProfile     myFanProfile;
        CT_ModVersion     myModVersion;
};

typedef TL1_Rtv_Response< TL1_EQRspBlk > TL1_EQResponse;

#endif  // #ifndef __TL1_EQPTRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
