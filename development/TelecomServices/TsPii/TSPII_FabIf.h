#ifndef _TSPII_FABIF_H
#define _TSPII_FABIF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_FabIf.h
* Type:    C++ include
* Description:
*    Provides the platform independent interface for the Dune Fabric methods.
*
*************************************END***************************************
*/
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_FabMulticast.h"
#include "CommonTypes/CT_Equipment.h"
#include "CommonTypes/CT_SwitchDomainMap.h"
#include "TsPii/TSPII_BaseIf.h"

enum TSPII_FabIf_TrafficType
{
    TSPII_FabIf_Traffic_Sonet,
    TSPII_FabIf_Traffic_Packet,
    TSPII_FabIf_Traffic_CesPacket,
    TSPII_FabIf_Traffic_Unknown
};

#define DISPLAY_FABIF_TRAFFIC_TYPE(x) (\
                   (x==TSPII_FabIf_Traffic_Sonet)     ? "Sonet" :\
                   (x==TSPII_FabIf_Traffic_Packet)    ? "Packet" :\
                   (x==TSPII_FabIf_Traffic_CesPacket) ? "CesPacket" :\
                   (x==TSPII_FabIf_Traffic_Unknown)   ? "Unknown" : "?")

const uint16 TSPII_FABIF_MCGROUP_START     =  8192; // starting multicast group value for CES_PACKET(SONET/TDM)
const uint16 TSPII_FABIF_MCGROUP_END       = 16383; // ending multicast group value for CES_PACKET(SONET/TDM)
const uint16 TSPII_FABIF_RESERVED_MCGROUP  = 16382; // Reserved multicast group. Currently not used.
const uint16 TSPII_FABIF_PQW_MCGROUP       = 16383; // PQW multicast group ID

// Structure of EdgeEgrXc Record --> Key + Val
class TSPII_FabIfEdgeEgrXcKey
{
public:
    uint8      SrcShelf;
    uint8      SrcSlot;
    uint16     SrcSts;
    uint16     ConId;
    uint16     DstSts;
    inline bool operator < (const TSPII_FabIfEdgeEgrXcKey& aKey) const;
};

class TSPII_FabIfEdgeEgrXcVal
{
public:
    uint8      DummyVal;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_FabIfEdgeEgrXcVal& operator = (const TSPII_FabIfEdgeEgrXcVal& aVal);
    inline bool operator == (const TSPII_FabIfEdgeEgrXcVal& aVal);
};

// Structure of EdgeIngXc Record --> Key + Val
class TSPII_FabIfEdgeIngXcKey
{
public:
    uint16     SrcSts;   // KEY
    inline bool operator < (const TSPII_FabIfEdgeIngXcKey& aDiagKey) const;
};

class TSPII_FabIfEdgeIngXcVal
{
public:
    bool       IsMc;
    uint16     McId;      // multicast only
    uint8      RemShelf;  // unicast only
    uint8      RemSlot;   // unicast only
    uint8      RemImux;   // unicast only
    uint8      RemCardType;  // unicast only
    uint16     ConId;
    bool       IsBypass;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_FabIfEdgeIngXcVal& operator = (const TSPII_FabIfEdgeIngXcVal& aVal);
    inline bool operator == (const TSPII_FabIfEdgeIngXcVal& aVal);
};

typedef map<TSPII_FabIfEdgeEgrXcKey, TSPII_FabIfEdgeEgrXcVal, less<TSPII_FabIfEdgeEgrXcKey> > TSPII_FabIfEdgeEgrXcMap;
typedef map<TSPII_FabIfEdgeIngXcKey, TSPII_FabIfEdgeIngXcVal, less<TSPII_FabIfEdgeIngXcKey> > TSPII_FabIfEdgeIngXcMap;

class TSPII_FabIf : public TSPII_BaseIf
{
public:

    /*************************************************************************/
    /** Constructor                                                         **/
    /*************************************************************************/
    TSPII_FabIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, uint16 theNumStss, bool theForceShelf, uint16 theNumMcgs, uint16 theNumConIds, bool theIsConMode);

    /*************************************************************************/
    /** Destructor                                                          **/
    /*************************************************************************/
    virtual ~TSPII_FabIf();

    /**************************************************************************/
    /** Utility functions                                                   **/
    /*************************************************************************/
    virtual void Reset();

    virtual void SetSlotTrafficType(uint8 theSlot, bool isRemote, TSPII_FabIf_TrafficType theType);
    virtual TSPII_FabIf_TrafficType GetSlotTrafficType(uint8 theSlot, bool isRemote);

    virtual void SetSlotSpeed(uint8 theSlot, bool isRemote, CT_TEL_LinkRate theSpeed);
    virtual CT_TEL_LinkRate GetSlotSpeed(uint8 theSlot, bool isRemote);

    virtual void SetSlotFecEnabled(uint8 theSlot, bool isRemote, bool theEnabled);
    virtual bool GetSlotFecEnabled(uint8 theSlot, bool isRemote);

    virtual void SetSwitchMode(CT_TEL_SwitchMode theMode);
    virtual CT_TEL_SwitchMode GetSwitchMode();

    virtual void SetSwitchDomainMode(CT_SwitchDomainMode theSwitchDomain);
    virtual CT_SwitchDomainMode GetSwitchDomainMode();

    virtual void SetSlotEnabled(uint8 theSlot, bool theEnable);
    virtual bool GetSlotEnabled(uint8 theSlot);

    virtual void SetPSInitComplete(bool isComplete);
    virtual bool GetPSInitComplete();

    virtual void SetTopologyMap(vector<uint8> theTopology);
    virtual vector<uint8> GetTopologyMap();

    virtual void SetMcGroup(uint16 theMcId, vector<CT_FabMcMember> theMembers, bool theCommitNow = false);
    virtual void DeleteMcGroup(uint16 theMcId, bool theCommitNow = false);
    virtual void DeleteAllMcGroups(bool theCommitNow = false);
    virtual void CommitMcGroups();
    virtual CT_FabMcGroupMap & GetMcGroups();
    virtual void AddMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow);
    virtual void DeleteMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow);

    virtual void AddEdgeEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint16 theSrcSts, uint16 theConId, uint16 theDstSts);
    virtual void DeleteEdgeEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint16 theSrcSts, uint16 theConId, uint16 theDstSts);
    virtual void DeleteAllEdgeEgressXconns();
    virtual void CommitEdgeEgressXconns(bool theForceHw = false);
    virtual TSPII_FabIfEdgeEgrXcMap& GetEdgeEgressXconns();

    virtual void AddEdgeIngressXconn(uint16 theSrcSts, bool theIsMc, uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, uint16 theConId, bool bypass = false, uint8 theRemCardType = 0);
    virtual void DeleteEdgeIngressXconn(uint16 theSrcSts);
    virtual void DeleteAllEdgeIngressXconns();
    virtual void CommitEdgeIngressXconns(bool theForceHw = false);
    virtual TSPII_FabIfEdgeIngXcMap& GetEdgeIngressXconns();
    virtual bool FindEdgeIngressXconn( uint16 theSrcSts, TSPII_FabIfEdgeIngXcMap::iterator & theIterator );

    virtual void HwInit() {};
    virtual void HwInitCold() {};
    virtual void HwInitWarm() {};

    virtual bool GetFapPortIdFromRemImuxId(uint8 remImux, uint8 &fapPort);
    virtual bool GetRemImuxIdFromFapPortId(uint8 fapPort, uint8 &remImux);

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
    virtual void RefreshGet();
    virtual void RefreshSet();
    virtual string DisplaySwitchMode();
    virtual string DisplaySwitchDomainMode();
    virtual string DisplaySlotTrafficType();
    virtual string DisplaySlotSpeed();
    virtual string DisplaySlotFecEnabled();
    virtual string DisplaySlotEnabled();
    virtual string DisplayMcGroups(bool printDetail);
    virtual string DisplayEdgeEgressXc(bool printDetail);
    virtual string DisplayEdgeIngressXc(bool printDetail);
    virtual string DisplaySlotFecInitComplete();
    virtual string DisplaySlotSpeedInitComplete();
    virtual string DisplaySlotFeInitComplete();
    virtual string DisplayFabricInitComplete(bool printDetail);

    bool                 itsIsConMode;
    uint16               itsNumConIds;
    uint8                itsNumShelves;
    uint8                itsNumSlots;
    uint8                itsNumImuxs;
    uint16               itsNumStss;
    bool                 itsForceShelf;
    bool                 itsPSInitComplete;
    bool                 itsPSCardInShelf;
    bool                 itsFabInitComplete;
    uint16               itsNumMcgs;
    CT_TEL_SwitchMode    itsSwitchMode;
    CT_SwitchDomainMode  itsSwitchDomain;
    TSPII_FabIf_TrafficType **itsSlotTrafficType;
    CT_TEL_LinkRate      **itsSlotSpeed;
    bool                 **itsSlotFecEnabled;
    bool                 **itsSlotFecInitComplete;
    bool                 **itsSlotSpeedInitComplete;
    bool                 **itsSlotFeInitComplete;
    bool                  *itsMcgInitComplete;
    CT_FabMcGroupMap     itsMcGroupsMap;
    bool                     *itsSlotEnabled;
    TSPII_FabIfEdgeEgrXcMap   itsEdgeEgressXconnsMap;
    TSPII_FabIfEdgeIngXcMap   itsEdgeIngressXconnsMap;
    vector<uint8>        itsTopologyMap;
    bool                 *itsEdgeEgressXconnUsage;

};

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_FabIfEdgeIngXcKey::operator < (const TSPII_FabIfEdgeIngXcKey& aKey) const
{
    return (SrcSts < aKey.SrcSts) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_FabIfEdgeEgrXcKey::operator < (const TSPII_FabIfEdgeEgrXcKey& aKey) const
{
    uint32 itsShSlSts;
    uint32 theShSlSts;
    uint32 itsConDst;
    uint32 theConDst;
    bool   retVal;

    itsShSlSts = (SrcShelf      << 24) | (SrcSlot      << 16) |      SrcSts;
    theShSlSts = (aKey.SrcShelf << 24) | (aKey.SrcSlot << 16) | aKey.SrcSts;

    itsConDst  = (ConId         << 16) | DstSts;
    theConDst  = (aKey.ConId    << 16) | aKey.DstSts;

    retVal = false;
    if (itsShSlSts < theShSlSts)
    {
        retVal = true;
    }
    else if (itsShSlSts == theShSlSts)
    {
        retVal = (itsConDst < theConDst) ? true : false;
    }

    return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_FabIfEdgeEgrXcVal& TSPII_FabIfEdgeEgrXcVal::operator = (const TSPII_FabIfEdgeEgrXcVal& aVal)
{
    DummyVal = aVal.DummyVal;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_FabIfEdgeIngXcVal& TSPII_FabIfEdgeIngXcVal::operator = (const TSPII_FabIfEdgeIngXcVal& aVal)
{
    IsMc = aVal.IsMc;
    McId = aVal.McId;
    RemShelf = aVal.RemShelf;
    RemSlot = aVal.RemSlot;
    RemImux = aVal.RemImux;
    RemCardType = aVal.RemCardType;
    ConId = aVal.ConId;
    IsBypass = aVal.IsBypass;
    IsNewOrChanged = aVal.IsNewOrChanged;
    IsDeleted = aVal.IsDeleted;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_FabIfEdgeEgrXcVal::operator == (const TSPII_FabIfEdgeEgrXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if (DummyVal == aVal.DummyVal)
    {
        retVal = true;
    }

    return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_FabIfEdgeIngXcVal::operator == (const TSPII_FabIfEdgeIngXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (IsMc     == aVal.IsMc)     &&
         (McId     == aVal.McId)     &&
         (RemShelf == aVal.RemShelf) &&
         (RemSlot  == aVal.RemSlot)  &&
         (RemImux  == aVal.RemImux)  &&
         (RemCardType == aVal.RemCardType) &&
         (ConId    == aVal.ConId)    &&
         (IsBypass == aVal.IsBypass) )
    {
        retVal = true;
    }

    return retVal;
}

#endif // _TSPII_FABIF_H

