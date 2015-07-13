/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive LED Response Class
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Header file for TL1 Retrive LED Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_LEDRESPONSE_BLOCK_H_
#define __TL1_LEDRESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_LED_Definitions.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_Telecom.h>

#include <Agent/Equipment/EQ_BbCardConfig.h>
#include <Agent/Equipment/EQ_BbShelfConfig.h>

#include <vector>
using namespace std;

class TL1_LEDRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_LEDRspBlk();

    TL1_LEDRspBlk(const string* entityName,
                  const CT_TL1_SlotAddr* slotAddr,
                  const CT_LEDColor  Active, // not optional
                  const CT_LEDColor  Power,  // not optional
                  const CT_LEDColor  Fault,  // not optional
                  const CT_LEDColor* ActLine,
                  const CT_LEDColor* Line,
                  const CT_LEDColor* Express,
                  const CT_LEDColor* Port,
                  const CT_LEDColor* Port1,
                  const CT_LEDColor* Port2,
                  const CT_LEDColor* Port3,
                  const CT_LEDColor* Port4,
                  const CT_LEDColor* Port5,
                  const CT_LEDColor* Port6,
                  const CT_LEDColor* Port7,
                  const CT_LEDColor* Port8,
                  const CT_LEDColor* Port9,
                  const CT_LEDColor* Port10,
                  const CT_LEDColor* Input,
                  const CT_LEDColor* Lpbk,
                  const CT_LEDColor* Sync,
                  const CT_LEDColor* Osc,
                  const CT_LEDColor* NeCr,
                  const CT_LEDColor* NeMj,
                  const CT_LEDColor* NeMn,
                  const CT_LEDColor* Ocp1,
                  const CT_LEDColor* Ocp2,
                  const CT_LEDColor* Ocp3,
                  const CT_LEDColor* Ocp4,
                  const CT_LEDColor* Apr,
                  const CT_LEDColor* DWDM44,
                  const CT_LEDColor* DWDM45,
                  const CT_LEDColor* DWDM1,
                  const CT_LEDColor* DWDM2,
                  const CT_LEDColor* Bits,
		          const CT_LEDColor* Aco,
                  const CT_LEDColor* Port11 = NULL,
                  const CT_LEDColor* Port12 = NULL,
                  const CT_LEDColor* Port13 = NULL,
                  const CT_LEDColor* Port14 = NULL,
                  const CT_LEDColor* Mode = NULL,
		          const CT_LEDColor* Port15 = NULL,
                  const CT_LEDColor* Port16 = NULL,
                  const CT_LEDColor* Port17 = NULL,
                  const CT_LEDColor* Port18 = NULL,
                  const CT_LEDColor* Port19 = NULL,
                  const CT_LEDColor* Port20 = NULL,                  
                  const CT_LEDColor* Port21 = NULL,
                  const CT_LEDColor* Port22 = NULL,
                  const CT_LEDColor* Port23 = NULL,
                  const CT_LEDColor* Port24 = NULL,
                  const CT_LEDColor* Port25 = NULL,
                  const CT_LEDColor* Port26 = NULL,
                  const CT_LEDColor* Port27 = NULL,
                  const CT_LEDColor* Port28 = NULL,
                  const CT_LEDColor* Port29 = NULL,                  
                  const CT_LEDColor* Port30 = NULL,
                  const CT_LEDColor* Port31 = NULL,
                  const CT_LEDColor* Port32 = NULL,
                  const CT_LEDColor* ActFlt = NULL
                 );
                 
    TL1_LEDRspBlk(const TL1_LEDRspBlk& ledBlk);
    
    virtual ~TL1_LEDRspBlk();

    TL1_LEDRspBlk& operator=( const TL1_LEDRspBlk& theBlock );

    bool operator==( const TL1_LEDRspBlk& theBlock ) const;

    bool GetEntityName( string&) const ;

    bool GetSlotAddr( CT_TL1_SlotAddr&) const ;

    bool GetActiveLED( CT_LEDColor&) const ;
    bool GetPowerLED( CT_LEDColor&) const ;
    bool GetFaultLED( CT_LEDColor&) const ;
    bool GetActLineLED( CT_LEDColor&) const ;
    bool GetLineLED( CT_LEDColor&) const ;
    bool GetExpressLED( CT_LEDColor&) const ;
    bool GetPortLED( CT_LEDColor&) const ;
    bool GetPort1LED( CT_LEDColor&) const ;
    bool GetPort2LED( CT_LEDColor&) const ;
    bool GetPort3LED( CT_LEDColor&) const ;
    bool GetPort4LED( CT_LEDColor&) const ;
    bool GetPort5LED( CT_LEDColor&) const ;
    bool GetPort6LED( CT_LEDColor&) const ;
    bool GetPort7LED( CT_LEDColor&) const ;
    bool GetPort8LED( CT_LEDColor&) const ;
    bool GetPort9LED( CT_LEDColor&) const ;
    bool GetPort10LED( CT_LEDColor&) const ;
    bool GetPort11LED( CT_LEDColor&) const ;
    bool GetPort12LED( CT_LEDColor&) const ;
    bool GetPort13LED( CT_LEDColor&) const ;
    bool GetPort14LED( CT_LEDColor&) const ;
    bool GetInputLED( CT_LEDColor&) const ;
    bool GetLpbkLED( CT_LEDColor&) const ;
    bool GetSyncLED( CT_LEDColor&) const ;
    bool GetOscLED( CT_LEDColor&) const ;
    bool GetNeCrLED( CT_LEDColor&) const ;
    bool GetNeMjLED( CT_LEDColor&) const ;
    bool GetNeMnLED( CT_LEDColor&) const ;
    bool GetOcp1LED( CT_LEDColor&) const ;
    bool GetOcp2LED( CT_LEDColor&) const ;
    bool GetOcp3LED( CT_LEDColor&) const ;
    bool GetOcp4LED( CT_LEDColor&) const ;
    bool GetAprLED( CT_LEDColor&) const ;
    bool GetDWDM44LED( CT_LEDColor&) const ;
    bool GetDWDM45LED( CT_LEDColor&) const ;
    bool GetDWDM1LED( CT_LEDColor&) const ;
    bool GetDWDM2LED( CT_LEDColor&) const ;
    bool GetBitsLED( CT_LEDColor&) const ;
    bool GetAcoLED( CT_LEDColor&) const ;
    bool GetModeLED( CT_LEDColor&) const ;
    bool GetPort15LED( CT_LEDColor&) const ;
    bool GetPort16LED( CT_LEDColor&) const ;
    bool GetPort17LED( CT_LEDColor&) const ;
    bool GetPort18LED( CT_LEDColor&) const ;
    bool GetPort19LED( CT_LEDColor&) const ;
    bool GetPort20LED( CT_LEDColor&) const ;
    bool GetActFltLED( CT_LEDColor&) const ;
    bool GetPort21LED( CT_LEDColor&) const ;
    bool GetPort22LED( CT_LEDColor&) const ;
    bool GetPort23LED( CT_LEDColor&) const ;
    bool GetPort24LED( CT_LEDColor&) const ;
    bool GetPort25LED( CT_LEDColor&) const ;
    bool GetPort26LED( CT_LEDColor&) const ;
    bool GetPort27LED( CT_LEDColor&) const ;
    bool GetPort28LED( CT_LEDColor&) const ;
    bool GetPort29LED( CT_LEDColor&) const ;
    bool GetPort30LED( CT_LEDColor&) const ;
    bool GetPort31LED( CT_LEDColor&) const ;
    bool GetPort32LED( CT_LEDColor&) const ;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_SlotAddr,
        INDEX_Active,
        INDEX_Power,
        INDEX_Fault,
        INDEX_ActLine,
        INDEX_Line,
        INDEX_Express,
        INDEX_Port,
        INDEX_Port1,
        INDEX_Port2,
        INDEX_Port3,
        INDEX_Port4,
        INDEX_Port5,
        INDEX_Port6,
        INDEX_Port7,
        INDEX_Port8,
        INDEX_Port9,
        INDEX_Port10,
        INDEX_Input,
        INDEX_Lpbk,
        INDEX_Sync,
        INDEX_Osc,
        INDEX_NeCr,
        INDEX_NeMj,
        INDEX_NeMn,
        INDEX_Ocp1,
        INDEX_Ocp2,
        INDEX_Ocp3,
        INDEX_Ocp4,
        INDEX_Apr,
        INDEX_DWDM44,
        INDEX_DWDM45,
        INDEX_DWDM1,
        INDEX_DWDM2,
        INDEX_Bits,
        INDEX_Aco,
        INDEX_Port11,
        INDEX_Port12,
        INDEX_Port13,
        INDEX_Port14,
        INDEX_Mode,
        INDEX_Port15,
        INDEX_Port16,
        INDEX_Port17,
        INDEX_Port18,
        INDEX_Port19,
        INDEX_Port20,
        INDEX_Port21,
        INDEX_Port22,
        INDEX_Port23,
        INDEX_Port24,
        INDEX_Port25,
        INDEX_Port26,
        INDEX_Port27,
        INDEX_Port28,
        INDEX_Port29,
        INDEX_Port30,
        INDEX_Port31,
        INDEX_Port32,
        INDEX_ActFlt,
        INDEX_END
	};

        vector<bool>      myBitSet;
        string            myEntityName; 
        CT_TL1_SlotAddr   mySlotAddr; 
        CT_LEDColor       myActive; 
        CT_LEDColor       myPower;
        CT_LEDColor       myFault;
        CT_LEDColor       myActLine;
        CT_LEDColor       myLine;
        CT_LEDColor       myExpress;
        CT_LEDColor       myPort;
        CT_LEDColor       myPort1;
        CT_LEDColor       myPort2;
        CT_LEDColor       myPort3;
        CT_LEDColor       myPort4;
        CT_LEDColor       myPort5;
        CT_LEDColor       myPort6;
        CT_LEDColor       myPort7;
        CT_LEDColor       myPort8;
        CT_LEDColor       myPort9;
        CT_LEDColor       myPort10;
        CT_LEDColor       myPort11;
        CT_LEDColor       myPort12;
        CT_LEDColor       myPort13;
        CT_LEDColor       myPort14;
        CT_LEDColor       myPort15;
        CT_LEDColor       myPort16;
        CT_LEDColor       myPort17;
        CT_LEDColor       myPort18;
        CT_LEDColor       myPort19;
        CT_LEDColor       myPort20;
        CT_LEDColor       myPort21;
        CT_LEDColor       myPort22;
        CT_LEDColor       myPort23;
        CT_LEDColor       myPort24;
        CT_LEDColor       myPort25;
        CT_LEDColor       myPort26;
        CT_LEDColor       myPort27;
        CT_LEDColor       myPort28;
        CT_LEDColor       myPort29;
        CT_LEDColor       myPort30;
        CT_LEDColor       myPort31;
        CT_LEDColor       myPort32;
        CT_LEDColor       myInput;
        CT_LEDColor       myLpbk;
        CT_LEDColor       mySync;
        CT_LEDColor       myOsc;
        CT_LEDColor       myNeCr;
        CT_LEDColor       myNeMj;
        CT_LEDColor       myNeMn;
        CT_LEDColor       myOcp1;
        CT_LEDColor       myOcp2;
        CT_LEDColor       myOcp3;
        CT_LEDColor       myOcp4;
        CT_LEDColor       myApr;
        CT_LEDColor       myDWDM44;
        CT_LEDColor       myDWDM45;
        CT_LEDColor       myDWDM1;
        CT_LEDColor       myDWDM2;
        CT_LEDColor       myBits;
        CT_LEDColor       myAco;
        CT_LEDColor       myMode;
        CT_LEDColor       myActFlt;
};

typedef TL1_Rtv_Response< TL1_LEDRspBlk > TL1_LEDResponse;

#endif  // #ifndef __TL1_LEDRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
