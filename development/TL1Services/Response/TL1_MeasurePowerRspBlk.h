/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1  response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MEASUREPOWERRSPBLK_H__
#define __TL1_MEASUREPOWERRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#ifndef CT_TELECOM_H
#include <CommonTypes/CT_Telecom.h>
#endif

#ifndef __CT_CARDSTATUSMONITORING_H__
#include <CommonTypes/CT_CardStatusMonitoring.h>
#endif

#ifndef CT_ITS_DEFINITIONS_H
#include <CommonTypes/CT_ITS_Definitions.h>
#endif

#include <vector>

using namespace std;

class TL1_MeasurePowerResultItem 
{
public:
    TL1_MeasurePowerResultItem();

    ~TL1_MeasurePowerResultItem();

    bool GetPower(CT_TEL_mBm &thePower) const;
    bool GetPowerBit() const;
    bool GetSnr(CT_TEL_mBm &theSnr) const;
    bool GetSnrBit() const;
    bool GetOSnr(CT_TEL_mBm &theOSnr) const;
    bool GetOSnrBit() const;

    void SetPower(CT_TEL_mBm thePower);
    void SetPowerBit(bool thePowerBit);
    void SetSnr(CT_TEL_mBm theSnr);
    void SetSnrBit(bool theSnrBit);
    void SetOSnr(CT_TEL_mBm theOSnr);
    void SetOSnrBit(bool theOSnrBit);

private:
    CT_TEL_mBm myPower;
    bool       myPowerBit;//Used to determine if the measurement has actually been made
    CT_TEL_mBm mySnr;
    bool       mySnrBit;//Used to determine if the measurement has actually been made
    CT_TEL_mBm myOSnr;
    bool       myOSnrBit;//Used to determine if the measurement has actually been made
};
    

class TL1_MeasurePowerRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_MeasurePowerRspBlk();

    TL1_MeasurePowerRspBlk( const TL1_MeasurePowerRspBlk& theBlock );

    TL1_MeasurePowerRspBlk( const string* theEntityName,
                     const CT_TL1_SlotAddr* theSlotAddr,
                     const CT_MeasOptChanNum* theChannel,
                     const CT_TL1_Port* thePort,
                     const CT_MeasOptChanNum* theLane,
                     const vector< TL1_MeasurePowerResultItem >* theResults,
                     const CT_Yes_No_NA* theChannelEquipped, 
                     const bool* thePortEquipped );

    virtual ~TL1_MeasurePowerRspBlk();

    TL1_MeasurePowerRspBlk& operator=( const TL1_MeasurePowerRspBlk& theBlock );

    bool GetEntityName(string&) const;

    bool GetSlotAddr(CT_TL1_SlotAddr&) const;
    
    bool GetChannel(CT_MeasOptChanNum&) const;

    bool GetPort(CT_TL1_Port&) const;

    bool GetLane(CT_MeasOptChanNum&) const;

    bool GetESTPower(CT_TEL_mBm&) const;

    bool GetLSRPower(CT_TEL_mBm&) const;

    bool GetLSRSnr(CT_TEL_mBm&) const;

    bool GetLSTPower(CT_TEL_mBm&) const;

    bool GetLSTOSnr(CT_TEL_mBm&) const;

    bool GetLSTSnr(CT_TEL_mBm&) const;

    bool GetALSTPower(CT_TEL_mBm&) const;

    bool GetALSTSnr(CT_TEL_mBm&) const;

    bool GetBLSTPower(CT_TEL_mBm&) const;

    bool GetBLSTSnr(CT_TEL_mBm&) const;

    bool GetALSRPower(CT_TEL_mBm&) const;

    bool GetBLSRPower(CT_TEL_mBm&) const;

    bool GetPSTPower(CT_TEL_mBm&) const;

    bool GetPSTOSnr(CT_TEL_mBm&) const;

    bool GetPSTSnr(CT_TEL_mBm&) const;

    bool GetPSRPower(CT_TEL_mBm&) const;

    bool GetPSRLLPower(CT_TEL_mBm&) const;

    bool GetPSRLHPower(CT_TEL_mBm&) const;

    bool GetPSTLLPower(CT_TEL_mBm&) const;

    bool GetPSTLHPower(CT_TEL_mBm&) const;

    bool GetPSRLNPower(CT_TEL_mBm&) const;

    bool GetPSTLNPower(CT_TEL_mBm&) const;

    bool GetDSRPower(CT_TEL_mBm&) const;

    bool GetDSTPower(CT_TEL_mBm&) const;
    
    bool GetChannelEquipped(CT_Yes_No_NA&) const;

    bool GetPortEquipped(bool&) const;

private:
    
    enum {
        INDEX_EntityName = 0,
        INDEX_SlotAddr,
        INDEX_Channel,
        INDEX_Port,
        INDEX_Results,
        INDEX_ChannelEquipped,
        INDEX_PortEquipped,  
        INDEX_Lane,
        INDEX_END
	};

        vector<bool>                            myBitSet;
        string                                  myEntityName;
        CT_TL1_SlotAddr                         mySlotAddr;
        CT_MeasOptChanNum                       myChannel;
        CT_TL1_Port                             myPort;
        CT_MeasOptChanNum                       myLane;
        vector< TL1_MeasurePowerResultItem >    myResults;
        CT_Yes_No_NA                            myChannelEquipped; 
        bool                                    myPortEquipped;
};


typedef TL1_Rtv_Response< TL1_MeasurePowerRspBlk > TL1_MeasurePowerResponse;


#endif
