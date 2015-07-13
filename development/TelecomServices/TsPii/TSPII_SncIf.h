#ifndef _TSPII_SNCIF_H
#define _TSPII_SNCIF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SncIf.h
* Type:    C++ include
* Author:  Jessica Chen, - June 2010
* Description:
*    Provides the platform specific interface for the SNC card methods.
*
*************************************END***************************************
*/
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_OduDefinitions.h"
#include "TsPii/TSPII_BaseIf.h"
#include <map>
#include <vector>
#include <string>

// Includes the client SFPs, XFP & line XFP, TTP
const uint8  TSPII_SNCIF_NUM_CHANNEL      = 160; 
const uint8  TSPII_SNCIF_NUM_ODU_ID       = 160;
const uint8  TSPII_SNCIF_INVALID_PQW_CHANNEL = 0xFF;
const uint8  TSPII_SNCIF_APS_CHANNEL      = 16; 

const uint32 TSPII_SNCIF_NO_CLIENT_ODU_ID = 4095;
const uint32 TSPII_SNCIF_NO_SERVER_ODU_ID = 4095;
const uint32 TSPII_SNCIF_NO_TCM_ODU_ID = 7;

enum DEBUG_LEVEL
{
    DEBUG_OFF=0,
    DEBUG_BASIC,
    DEBUG_DETAILED
};
#define TSPII_SNCIF_PRIORITY_ENABLED(x) (\
                     (x==true) ? "T" :\
                     (x==false)? "F" : " ? ")
enum TSPII_SNCIF_PRIORITY_TABLE
{
    TSPII_SNCIF_PRIOR_TBL_0 = 0,
    TSPII_SNCIF_PRIOR_TBL_1,
    TSPII_SNCIF_PRIOR_TBL_2,
    TSPII_SNCIF_PRIOR_TBL_3,
    TSPII_SNCIF_PRIOR_TBL_4,
    TSPII_SNCIF_PRIOR_TBL_5,
    TSPII_SNCIF_PRIOR_TBL_6,
    TSPII_SNCIF_PRIOR_TBL_7,
    TSPII_SNCIF_PRIOR_TBL_MAX,
};

#define TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(x) (\
                     (x==TSPII_SNCIF_PRIOR_TBL_0) ? "0" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_1) ? "1" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_2) ? "2" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_3) ? "3" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_4) ? "4" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_5) ? "5" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_6) ? "6" :\
                     (x==TSPII_SNCIF_PRIOR_TBL_7) ? "7" : " ? ")

enum TSPII_SNCIF_PRIORITY_DEFECT
{
    TSPII_SNCIF_PRIOR_DEF_TIMS = 0,
    TSPII_SNCIF_PRIOR_DEF_AISL,
    TSPII_SNCIF_PRIOR_DEF_SFL,
    TSPII_SNCIF_PRIOR_DEF_AISP,
    TSPII_SNCIF_PRIOR_DEF_LOPP,
    TSPII_SNCIF_PRIOR_DEF_UNEQP,
    TSPII_SNCIF_PRIOR_DEF_TIMP,
    TSPII_SNCIF_PRIOR_DEF_PLMP,
    TSPII_SNCIF_PRIOR_DEF_SFP,
    TSPII_SNCIF_PRIOR_DEF_PDI,
    TSPII_SNCIF_PRIOR_DEF_SDP,
    TSPII_SNCIF_PRIOR_DEF_SDL,
    TSPII_SNCIF_PRIOR_DEF_MAX,

};

#define TSPII_SNCIF_DISPLAY_PRIORDEF(x) (\
                     (x==TSPII_SNCIF_PRIOR_DEF_TIMS) ? "tims" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_AISL) ? "aisl" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_SFL)  ? "sfl" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_AISP) ? "aisp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_LOPP) ? "lopp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_UNEQP)? "uneqp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_TIMP) ? "timp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_PLMP) ? "plmp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_SFP)  ? "sfp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_PDI)  ? "pdi" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_SDP)  ? "sdp" :\
                     (x==TSPII_SNCIF_PRIOR_DEF_SDL)  ? "sdl" : "?")

enum TSPII_SNCIF_PRIORITY
{
    TSPII_SNCIF_PRIOR_NONE = 0,
    TSPII_SNCIF_PRIOR_SD,
    TSPII_SNCIF_PRIOR_SFL,
    TSPII_SNCIF_PRIOR_SFH,
    TSPII_SNCIF_PRIOR_UNKNOWN

};

#define TSPII_SNCIF_DISPLAY_PRIORITY(x) (\
                     (x==TSPII_SNCIF_PRIOR_NONE) ? "none" :\
                     (x==TSPII_SNCIF_PRIOR_SD)   ? "sd" :\
                     (x==TSPII_SNCIF_PRIOR_SFL)  ? "sfl" :\
                     (x==TSPII_SNCIF_PRIOR_SFH)  ? "sfh" :\
                     (x==TSPII_SNCIF_PRIOR_UNKNOWN) ? "Unknown" :"?")


enum TSPII_SNCIF_DEFECT_GROUP
{
    TSPII_SNCIF_ODU_SF = 0,
    TSPII_SNCIF_ODU_SD,
    TSPII_SNCIF_OTU_SF,
    TSPII_SNCIF_OTU_SD,
    TSPII_SNCIF_TCM_SF,
    TSPII_SNCIF_TCM_SD,
    TSPII_SNCIF_DEFECT_UNKNOWN
};

#define TSPII_SNCIF_DISPLAY_DEFECTGRP(x) (\
                     (x == TSPII_SNCIF_ODU_SF) ? "odu_sf" :\
                     (x == TSPII_SNCIF_ODU_SD) ? "odu_sd" :\
                     (x == TSPII_SNCIF_OTU_SF) ? "otu_sf" :\
                     (x == TSPII_SNCIF_OTU_SD) ? "otu_sd" :\
                     (x == TSPII_SNCIF_TCM_SF) ? "tcm_sf" :\
                     (x == TSPII_SNCIF_TCM_SD) ? "tcm_sd" : \
                     (x == TSPII_SNCIF_DEFECT_UNKNOWN) ? "unknown":"?")

enum TSPII_SNCIF_DEFECT_TYPE
{
    TSPII_SNCIF_CLIENT,
    TSPII_SNCIF_SERVER,
    TSPII_SNCIF_TCM,
    TSPII_SNCIF_NONE
};

#define TSPII_SNCIF_DISPLAY_DEFECTTYPE(x) (\
                      (x == TSPII_SNCIF_CLIENT) ? "client" : \
                      (x == TSPII_SNCIF_SERVER) ? "server" :\
                      (x == TSPII_SNCIF_TCM)    ? "tcm" : \
                      (x == TSPII_SNCIF_NONE)   ? "none" : "?")

enum TSPII_SNCIF_FRAMER
{
    TSPII_SNCIF_ODU0,
    TSPII_SNCIF_ODU1,
    TSPII_SNCIF_ODU2,
    TSPII_SNCIF_ODU3,
    TSPII_SNCIF_ODU4,
    TSPII_SNCIF_ODUF
};
#define TSPII_SNCIF_DISPLAY_FRAMER(x) (\
                     (x == TSPII_SNCIF_ODU0) ? "odu0" : \
                     (x == TSPII_SNCIF_ODU1) ? "odu1" : \
                     (x == TSPII_SNCIF_ODU2) ? "odu2" : \
                     (x == TSPII_SNCIF_ODU3) ? "odu3" : \
                     (x == TSPII_SNCIF_ODU4) ? "odu4" : \
                     (x == TSPII_SNCIF_ODUF) ? "oduf" : "?")


/////////////////////////////////////////////////////////////////////////////////////


// Structure of TohPqwEgrXc Record --> Key + Val
class TSPII_SncIfTohPqwEgrXcKey
{
public:
    uint8      DstOtnPqwChannel;
    inline bool operator < (const TSPII_SncIfTohPqwEgrXcKey& aDiagKey) const;
};

class TSPII_SncIfTohPqwEgrXcVal
{
public:
    uint8      SrcShelf;
    uint8      SrcSlot;
    uint8      SrcOtnPqwChannel;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_SncIfTohPqwEgrXcVal& operator = (const TSPII_SncIfTohPqwEgrXcVal& aVal);
    inline bool operator == (const TSPII_SncIfTohPqwEgrXcVal& aVal);
};

// Structure of TohPqwIngXc Record --> Key + Val
class TSPII_SncIfTohPqwIngXcKey
{
public:
    uint8      OtnPqwChannel; //dst
    inline bool operator < (const TSPII_SncIfTohPqwIngXcKey& aDiagKey) const;
};

class TSPII_SncIfTohPqwIngXcVal
{
public:
//    uint32     LogicalOduId;    //JEJ remove
    uint32     cLogicalOduId;
    uint32     sLogicalOduId;
    uint32     tLogicalOduId;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_SncIfTohPqwIngXcVal& operator = (const TSPII_SncIfTohPqwIngXcVal& aVal);
    inline bool operator == (const TSPII_SncIfTohPqwIngXcVal& aVal);
};

typedef map<TSPII_SncIfTohPqwEgrXcKey, TSPII_SncIfTohPqwEgrXcVal, less<TSPII_SncIfTohPqwEgrXcKey> > TSPII_SncIfTohPqwEgrXcMap;
typedef map<TSPII_SncIfTohPqwIngXcKey, TSPII_SncIfTohPqwIngXcVal, less<TSPII_SncIfTohPqwIngXcKey> > TSPII_SncIfTohPqwIngXcMap;

class TSPII_SncIf : public TSPII_BaseIf
{
public:

    /*************************************************************************/
    /** Constructor                                                         **/
    /*************************************************************************/
    TSPII_SncIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, bool theForceShelf);

    /*************************************************************************/
    /** Destructor                                                          **/
    /*************************************************************************/
    virtual ~TSPII_SncIf();

    /**************************************************************************/
    /** Utility functions                                                   **/
    /*************************************************************************/
    virtual void Reset();
    virtual void                      registerEventHandlers(){};

    virtual void SetTohPriorityTable(TSPII_SNCIF_DEFECT_GROUP theDefectGroup,
                                     TSPII_SNCIF_DEFECT_TYPE theDefectType,
                                     TSPII_SNCIF_FRAMER theFramer,
                                     uint8 theDefectIndex,
                                     TSPII_SNCIF_PRIORITY thePriority,
                                     TSPII_SNCIF_PRIORITY_TABLE theTable);

    virtual TSPII_SNCIF_PRIORITY GetTohPriorityTable(TSPII_SNCIF_PRIORITY_TABLE theTable, TSPII_SNCIF_DEFECT_GROUP theDefectGroup);

    virtual void SetTohPriorityAssignment(uint8 theOtnPqwChannel, TSPII_SNCIF_PRIORITY_TABLE theTable);
    virtual TSPII_SNCIF_PRIORITY_TABLE GetTohPriorityAssignment(uint8 theOtnPqwChannel);

    virtual void AddTohPqwEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint8 theSrcOtnPqwChannel, uint8 theDstOtnPqwChannel);
    virtual void DeleteTohPqwEgressXconn(uint8 theDstOtnPqwChannel);
    virtual void DeleteAllTohPqwEgressXconns();
    virtual TSPII_SncIfTohPqwEgrXcMap& GetTohPqwEgressXconns();

    virtual void AddTohPqwIngressXconn(uint8 theOtnPqwChannel, uint32 theClientOduId, uint32 theServerOduId, uint32 theTcmId);
    virtual void DeleteTohPqwIngressXconn(uint8 theOtnPqwChannel);
    virtual void DeleteAllTohPqwIngressXconns();
    virtual TSPII_SncIfTohPqwIngXcMap& GetTohPqwIngressXconns();

    virtual void SetPqwTimeoutInterruptEnable(bool theEnable, uint16 shelf , uint8 slot );
    virtual uint32 GetPqwTimeout(uint8 theShelf, uint8 theSlot);



    virtual void EnableRxSwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable);
    virtual void EnableRxHwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable);
    virtual void EnableTxHwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable);


    virtual void  SetTxPQM(uint8 theOtnPqwChannel, uint16 thePQM, uint16 theMask = 0xFFFF);
    virtual uint16  GetTxPQM(uint8 theOtnPqwChannel) const;
    virtual uint16  GetRxPQM(uint8 theOtnPqwChannel) ;

    virtual void  SetFppEnabled(uint8 theOtnPqwChannel, bool theEnable);
    virtual bool  GetFppEnabled(uint8 theOtnPqwChannel) const;

    virtual void  SetFppSquelchEnabled(uint8 theOtnPqwChannel, bool theEnable);
    virtual bool  GetFppSquelchEnabled(uint8 theOtnPqwChannel) const;

    virtual void  SetSrcTrafficEnabled(uint8 theOtnPqwChannel, bool theEnable);
    virtual bool  GetSrcTrafficEnabled(uint8 theOtnPqwChannel) const;

    virtual uint32  GetRxSFHigh(uint8 theOtnPqwChannel);
    virtual uint32  GetRxSFLow(uint8 theOtnPqwChannel);
    virtual uint32  GetRxSD(uint8 theOtnPqwChannel);

    virtual uint32  GetTxSFHigh(uint8 theOtnPqwChannel);
    virtual uint32  GetTxSFLow(uint8 theOtnPqwChannel);
    virtual uint32  GetTxSD(uint8 theOtnPqwChannel);

    virtual bool  GetTxHwPQWSquelch(uint8 theOtnPqwChannel);
    virtual bool  GetRxHwPQWSquelch(uint8 theOtnPqwChannel);

    virtual void SetGeneralSncControlParams(uint32 theShelf, uint32 theSlot);
    virtual void EnablePqwTransmit(bool theEnable);
    virtual bool GetPqwTransmitEnable() const;


    virtual void SetOduStreamPqwIndex(uint8 theOduStreamId, uint8 theOtnPqwChannel);
    virtual uint8 GetOduStreamPqwIndex(uint8 theOduStreamId) const;

    virtual void SetSquelchHoldOffDelay(uint8 theOtnPqwChannel, uint32 theDelay);
    virtual uint32 GetSquelchHoldOffDelay(uint8 theOtnPqwChannel) const;

    virtual bool  GetTxPQWInvalid(uint8 theOtnPqwChannel);
    virtual bool  GetRxPQWInvalid(uint8 theOtnPqwChannel);

	virtual void EnableAps(bool enable);
    virtual void EnableLocalApsInterrupt(CT_ODU_Identifier& oduId,
                                     uint8 apsChannel,
                                     uint16 apsIndex,
                                     bool enable);

    virtual void EnableRemoteApsInterrupt(uint8 shelfId,
                                          uint8 slotId,
                                          uint16 apsIndex,
                                          uint16 remoteApsIndex,
                                          bool enable);
    virtual uint32 GetRxLocalApsBytes(uint16 theOduTpChannel);
    virtual uint32 GetRxRemoteApsBytes(uint16 theOduTpChannel);

    virtual void HwInit() {};

    /*************************************************************************/
    /** Blackboard serialization                                            **/
    /*************************************************************************/
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream & WriteObject(ostream & theStream);
    virtual istream & ReadObject(istream & theStream);

    /*************************************************************************/
    /** Test Menus                                                          **/
    /*************************************************************************/
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:
	typedef struct
    {
        CT_ODU_Identifier oduId;
        uint8 apsChannel;
        bool enable;   
    }LocalApsInterruptCfg;

    typedef struct
    {
        uint8 shelfId;
        uint8 slotId;
        uint16 apsIndex;
        bool enable;    
    }RemoteApsInterruptCfg;

    typedef vector<LocalApsInterruptCfg> LocalApsInterruptCfgVector;
    typedef vector<RemoteApsInterruptCfg> RemoteApsInterruptCfgVector;
	
    virtual void RefreshGet();
    virtual void RefreshSet();
    virtual string DisplayOtnDefectList();
    virtual string DisplayOtnDefectGroup();
    virtual string DisplayOtnPriorityTable();
    virtual string DisplayOtnPriorityTable(int aTable);   //overloaded method!  JEJ
    virtual string DisplayOtnPriorityAssign();
    virtual string DisplayOtnTohPqwEgressXc(bool printDetail);
    virtual string DisplayOtnTohPqwIngressXc(bool printDetail);
    virtual string DisplayOtnPqwChannel(uint8 theBeginCh,uint8 theEndCh,const char * argv,bool showCount);
    virtual string DisplayOtnApsChannel(uint8 theBeginCh,uint8 theEndCh,const char * argv,bool showCount);
    virtual string DisplayOtnPqwEnabled(uint8 theBeginCh,uint8 theEndCh,const char * theOn,const char * theOff,bool *theEnable,bool showCount);
    virtual string DisplayOtnPqwCounter(uint8 theBeginCh,uint8 theEndCh,uint32 *theValue);
    virtual string DisplayOtnPqwStatus(uint8 theBeginCh,uint8 theEndCh,uint16 *theValue);
	virtual string DisplayApsBytes(uint16 theBeginCh,uint16 theEndCh,vector<uint32> &theValue);
    virtual string DisplayOtnPqwChannelConfiguration(int achannel);
    virtual string DisplayOtnPqwChannelStatus(int aChannel);
    virtual string DisplayOtnTohPqwEgressXc(int pqwchannel);
    virtual string DisplayOtnTohPqwIngressXc(int channel);

	template <typename T>
    string DisplayApsInterruptEnable(uint16 theBeginCh,uint16 theEndCh,vector<T> &theValueVector);
	
	template <typename T>
    void resetChannelPropertyVector(vector<T>& theVector);

    uint8                      itsNumShelves;
    uint8                      itsNumSlots;
    uint8                      itsNumImuxs;
    bool                       itsForceShelf;
    TSPII_SNCIF_PRIORITY       itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_MAX][TSPII_SNCIF_DEFECT_UNKNOWN];  // Line and Path table storage
    TSPII_SNCIF_PRIORITY_TABLE itsTohPriorAssign[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     **itsPqwTimeout;
    TSPII_SncIfTohPqwEgrXcMap  itsTohPqwEgressXconnsMap;
    TSPII_SncIfTohPqwIngXcMap  itsTohPqwIngressXconnsMap;
    bool                       itsRxSwPqwIntEnbl[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsRxHwPqwIntEnbl[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsTxHwPqwIntEnbl[TSPII_SNCIF_NUM_CHANNEL];
    uint16                     itsTxPQM[TSPII_SNCIF_NUM_CHANNEL];
    uint16                     itsRxPQM[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsFppEnbl[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsFppSqlEnbl[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsSrcTfcEnbl[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsRxSFHigh[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsRxSFLow[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsRxSD[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsTxSFHigh[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsTxSFLow[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsTxSD[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsTxHwPQWSql[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsRxHwPQWSql[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsPqwTransmit;
    uint8                      itsOduStreamPqwIndex[TSPII_SNCIF_NUM_CHANNEL];
    uint32                     itsSquelchHoldOffDelay[TSPII_SNCIF_NUM_CHANNEL];
    DEBUG_LEVEL                itsdebuglevel;
    bool                       itsTxPQWInvalid[TSPII_SNCIF_NUM_CHANNEL];
    bool                       itsRxPQWInvalid[TSPII_SNCIF_NUM_CHANNEL];
	bool                            itsApsEnable;
    LocalApsInterruptCfgVector      itsLocalApsInterruptCfg;
    RemoteApsInterruptCfgVector     itsRemoteApsInterruptCfg;
    vector<uint32>        itsRxRemoteApsBytes;
    vector<uint32>        itsRxLocalApsBytes;
};

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SncIfTohPqwEgrXcKey::operator < (const TSPII_SncIfTohPqwEgrXcKey& aKey) const
{
    return (DstOtnPqwChannel < aKey.DstOtnPqwChannel) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SncIfTohPqwIngXcKey::operator < (const TSPII_SncIfTohPqwIngXcKey& aKey) const
{
    return (OtnPqwChannel < aKey.OtnPqwChannel) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_SncIfTohPqwEgrXcVal& TSPII_SncIfTohPqwEgrXcVal::operator = (const TSPII_SncIfTohPqwEgrXcVal& aVal)
{
    SrcShelf = aVal.SrcShelf;
    SrcSlot = aVal.SrcSlot;
    SrcOtnPqwChannel = aVal.SrcOtnPqwChannel;

    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_SncIfTohPqwIngXcVal& TSPII_SncIfTohPqwIngXcVal::operator = (const TSPII_SncIfTohPqwIngXcVal& aVal)
{
    cLogicalOduId = aVal.cLogicalOduId;
    sLogicalOduId = aVal.sLogicalOduId;
    tLogicalOduId = aVal.tLogicalOduId;

    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SncIfTohPqwEgrXcVal::operator == (const TSPII_SncIfTohPqwEgrXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (SrcShelf == aVal.SrcShelf) &&
         (SrcSlot  == aVal.SrcSlot)  &&
         (SrcOtnPqwChannel  == aVal.SrcOtnPqwChannel))
    {
        retVal = true;
    }

    return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SncIfTohPqwIngXcVal::operator == (const TSPII_SncIfTohPqwIngXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (cLogicalOduId == aVal.cLogicalOduId) && (sLogicalOduId == aVal.sLogicalOduId) && (tLogicalOduId == aVal.tLogicalOduId))
    {
        retVal = true;
    }

    return retVal;
}

template <typename T>
string TSPII_SncIf::DisplayApsInterruptEnable(uint16 theBeginCh,uint16 theEndCh,vector<T> &theValueVector)
{
	string s;
	char    aBuf[128] = {0};

	for(uint8 i=0; i<(theEndCh-theBeginCh);i++)
	{
		sprintf(aBuf, "%-8x", (theValueVector[i].enable ? 1 : 0));
		s += aBuf;    
	}

    return s.c_str();
}

template <typename T>
void TSPII_SncIf::resetChannelPropertyVector(vector<T>& theVector)
{
    theVector.clear();
	for(uint8 i=0; i<TSPII_SNCIF_NUM_CHANNEL;i++)
    {
    	T element;
    	theVector.push_back(element);
    } 
    //theVector.resize(TSPII_SNCIF_NUM_CHANNEL);
}

#endif // _TSPII_SNCIF_H

