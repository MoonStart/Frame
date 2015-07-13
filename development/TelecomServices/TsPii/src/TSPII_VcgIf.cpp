/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds July 2003
 DESCRIPTION:Definition of the class TSPII_VcgIf. Models the Virtual
             Concatination Group termination entity.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_VcgIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

extern "C"
{
    extern uint32 TMBget_timestamp( void );
    extern uint32 TMBusec_since( uint32 timestamp );
}

//TspiiVcgGroupMemberMap gVcgGroupMemberMap;  at some later date I may separate the members from the VCG

///////////////////////////////////////////////////////////////////////////////
TSPII_VcgIf::TSPII_VcgIf(bool theDefault) :
    TSPII_BaseIf(theDefault),
     myDebugFlag(false),
    myLastTime(0),
    myShortestTime(0),
    myLongestTime(0),
    myPoint1(0),
    myPoint2(0),
    myPoint3(0),
    myPoint4(0),
    myPoint5(0),
    myPoint6(0),
    myPoint7(0),
    myPoint8(0),
    myPoint9(0),
    myPoint10(0),
    myProtectLastTime(0),
    myProtectLongestTime(0),
    myProtectShortestTime(0),
    myProtectPoint1(0),
    myProtectPoint2(0),
    myReSeqNeeded(false),
    myRxSeqFixed(false),
    myReSeqEndTimeStamp(0),
    myReSeqExecTime(0),
    myReSeqReqTimeStamp(0),
    myReSeqStartFixTimeStamp(0),
    myReSeqcount(0),
    minReSeqExecTime(0),
    maxReSeqExecTime(0),
    minReSeqEndTime(0),
    maxReSeqEndTime(0),
    mySeqMsMatchFixCount(0)


//    theVcgGroupMemberMap(gVcgGroupMemberMap) for a later date!!

{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_VcgIf::~TSPII_VcgIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::RefreshGet()
{
    int aNdx;

    // Monitoring attributes
    itsNumActiveTxMbrs = GetNumActiveTxMbrs();
    itsNumActiveRxMbrs = GetNumActiveRxMbrs();
    itsTxTlc = GetTxTlc();
    itsTxPlc = GetTxPlc();
    itsRxTlc = GetRxTlc();
    itsRxPlc = GetRxPlc();
    itsLosAlign = GetLosAlign();
    itsLcasDetected = GetLcasDetected();
    itsLcasRxDetected = GetLcasRxDetected();
    itsTxFop = GetTxFop();
    itsRxFop = GetRxFop();
    itsActive = GetActiveVcg();
    itsForceEvcRefresh = GetForceEvcRefreshAndClearForce();

    //only loop through the members assigned to this vcg
    int VcgMaxMbrs = (itsNumActiveTxMbrs >= itsNumActiveRxMbrs) ? itsNumActiveTxMbrs :itsNumActiveRxMbrs;
    for(aNdx=0; aNdx< VcgMaxMbrs; aNdx++)
    {
        itsTxSeqNbr[aNdx] = GetTxSeqNbr(aNdx);
        itsRxSeqNbr[aNdx] = GetRxSeqNbr(aNdx);
        itsRxDiffDelay[aNdx] = GetRxDiffDelay(aNdx);
        itsTxState[aNdx] = GetTxState(aNdx);
        itsRxState[aNdx] = GetRxState(aNdx);
        itsSeqMisMatch[aNdx] = GetSeqMisMatch(aNdx);
        itsLosMfAlign[aNdx] = GetLosMfAlign(aNdx);
        itsMbrNotDskew[aNdx] = GetMbrNotDskew(aNdx);
    }

    // Configuration attributes
    itsHoldOffTimer = GetHoldOffTimer();
    itsWaitToRestoreTimer = GetWaitToRestoreTimer();
    itsPlcThres = GetPlcThres();
    itsTlcThres = GetTlcThres();
    itsDiffDelayThres = GetDiffDelayThres();
    itsVcatType = GetVcatType();
    itsIsConnAsSrc = GetIsConnAsSrc();
    itsIsConnAsDest = GetIsConnAsDest();
    itsActualMembers = GetMembers();
    itsProtectedVcgId = GetProtectedVcgID();
    itsProtectedVcgSlot = GetProtectedVcgSlot();
    itsLcasEnabled = GetLcasEnabled();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::RefreshSet()
{
    // Configuration attributes
    SetHoldOffTimer(itsHoldOffTimer);
    SetWaitToRestoreTimer(itsWaitToRestoreTimer);
    SetPlcThres(itsPlcThres);
    SetTlcThres(itsTlcThres);
    SetDiffDelayThres(itsDiffDelayThres);
    SetVcatType(itsVcatType);
    SetIsConnAsSrc(itsIsConnAsSrc);
    SetIsConnAsDest(itsIsConnAsDest);
    SetMembers(itsMembers);
    SetSrcMembers(itsSrcMembers);
    SetSnkMembers(itsSnkMembers);
    SetProtectedVcgID(itsProtectedVcgId, itsProtectedVcgSlot);
    SetLcasEnabled(itsLcasEnabled);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::Reset()
{
    int aNdx;

    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsNumActiveTxMbrs = 0;
    itsNumActiveRxMbrs = 0;
    itsTxTlc = 0;
    itsTxPlc = 0;
    itsRxTlc = 0;
    itsRxPlc = 0;
    itsLosAlign = 0;
    itsLcasDetected = false;
    itsLcasRxDetected = true;
    itsTxFop = 0;
    itsRxFop = 0;
    itsActive = false;
    itsForceEvcRefresh = false;

    for(aNdx=0; aNdx<TSPII_VCG_MBRS_MAX; aNdx++)
    {
        itsTxSeqNbr[aNdx] = 0;
        itsRxSeqNbr[aNdx] = 0;
        itsRxDiffDelay[aNdx] = 0;
        itsTxState[aNdx] = CT_TEL_VCG_ST_UNKNOWN;
        itsRxState[aNdx] = CT_TEL_VCG_ST_UNKNOWN;
        itsSeqMisMatch[aNdx] = 0;
        itsLosMfAlign[aNdx] = 0;
        itsMbrNotDskew[aNdx] = 0;
    }

    // Stat attributes
    itsIngressEnqueueDropFrames = 0;
    itsIngressEnqueueFrames = 0;
    itsIngressDequeueFrames = 0;
    itsEgressEnqueueDropFrames = 0;
    itsEgressEnqueueFrames = 0;
    itsEgressDequeueFrames = 0;


    // Configuration attributes
    itsHoldOffTimer = 0;
    itsWaitToRestoreTimer = 0;
    itsPlcThres = 0;
    itsTlcThres = 0;
    itsDiffDelayThres = 0;
    itsVcatType = CT_TEL_VCAT_UNKNOWN;
    itsIsConnAsSrc = false;
    itsIsConnAsDest = false;
    itsProtectedVcgId = TSPII_UNDEFINED_PROTECTED_VCG_ID;
    itsProtectedVcgSlot = 0;
    itsLcasEnabled = false;
    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    itsSrcMembers.erase(itsSrcMembers.begin(), itsSrcMembers.end());
    itsSnkMembers.erase(itsSnkMembers.begin(), itsSnkMembers.end());
    itsActualMembers.erase(itsActualMembers.begin(), itsActualMembers.end());
    itsRerouteTtp = false;

    //jej Timestamp Debug
     myDebugFlag = false;
    myLastTime = 0;
    myShortestTime = 0;
    myLongestTime = 0;
    myPoint1 = 0;
    myPoint2 = 0;
    myPoint3 = 0;
    myPoint4 = 0;
    myPoint5 = 0;
    myPoint6 = 0;
    myPoint7 = 0;
    myPoint8 = 0;
    myPoint9 = 0;
    myPoint10 = 0;
    myProtectPoint1 = 0;
    myProtectPoint2 = 0;

    myProtectLastTime = 0;
    myProtectLongestTime = 0;
    myProtectShortestTime = 0;

}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetNumActiveTxMbrs()
{
    return itsNumActiveTxMbrs;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetNumActiveRxMbrs()
{
    return itsNumActiveRxMbrs;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetTxSeqNbr(uint16 theMbr)
{
    return itsTxSeqNbr[theMbr];
}
///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetRxSeqNbr(uint16 theMbr)
{
    return itsRxSeqNbr[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetRxDiffDelay(uint16 theMbr)
{
    return itsRxDiffDelay[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_VCG_STATE TSPII_VcgIf::GetTxState(uint16 theMbr)
{
    return itsTxState[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_VCG_STATE TSPII_VcgIf::GetRxState(uint16 theMbr)
{
    return itsRxState[theMbr];
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetSeqMisMatch(uint16 theMbr)
{
    return itsSeqMisMatch[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetLosMfAlign(uint16 theMbr)
{
    return itsLosMfAlign[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetMbrNotDskew(uint16 theMbr)
{
    return itsMbrNotDskew[theMbr];
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetLcasDetected()
{
    return itsLcasDetected;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetLcasRxDetected()
{
    return itsLcasRxDetected;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetActiveVcg()
{
    return itsActive;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetForceEvcRefreshAndClearForce()
{
    return itsForceEvcRefresh;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetTxTlc()
{
    return itsTxTlc;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetTxPlc()
{
    return itsTxPlc;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetRxTlc()
{
    return itsRxTlc;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetRxPlc()
{
    return itsRxPlc;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetLosAlign()
{
    return itsLosAlign;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetTxFop()
{
    return itsTxFop;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetRxFop()
{
    return itsRxFop;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetHoldOffTimer(uint32 theTime)
{
    itsHoldOffTimer = theTime;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetHoldOffTimer() const
{
    return itsHoldOffTimer;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetWaitToRestoreTimer(uint32 theTime)
{
    itsWaitToRestoreTimer = theTime;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetWaitToRestoreTimer() const
{
    return itsWaitToRestoreTimer;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetPlcThres(uint16 theThres)
{
    itsPlcThres = theThres;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetPlcThres() const
{
    return itsPlcThres;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetTlcThres(uint16 theThres)
{
    itsTlcThres = theThres;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_VcgIf::GetTlcThres() const
{
    return itsTlcThres;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetDiffDelayThres(uint32 theThres)
{
    itsDiffDelayThres = theThres;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_VcgIf::GetDiffDelayThres() const
{
    return itsDiffDelayThres;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetVcatType(CT_TEL_VCAT_TYPE theType)
{
    itsVcatType = theType;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_VCAT_TYPE TSPII_VcgIf::GetVcatType() const
{
    return itsVcatType;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetIsConnAsSrc(bool theMode)
{
    itsIsConnAsSrc = theMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetIsConnAsSrc()
{
    return itsIsConnAsSrc;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetIsConnAsDest(bool theMode)
{
    itsIsConnAsDest = theMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetIsConnAsDest()
{
    return itsIsConnAsDest;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetLcasEnabled(bool theMode)
{
    itsLcasEnabled = theMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetLcasEnabled()
{
    return itsLcasEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetProtectedVcgID(int theVcgId, int theVcgSlot)
{
    itsProtectedVcgId = theVcgId;
    itsProtectedVcgSlot = theVcgSlot;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_VcgIf::GetProtectedVcgID()
{
    return itsProtectedVcgId;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_VcgIf::GetProtectedVcgSlot()
{
    return itsProtectedVcgSlot;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetMembers(const vector<uint16> & theMembers)
{
    itsMembers = theMembers;
}

///////////////////////////////////////////////////////////////////////////////
const vector<uint16> & TSPII_VcgIf::GetMembers()
{
    return itsMembers;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetSrcMembers(const vector<uint16> & theMembers)
{
    itsSrcMembers = theMembers;
}

///////////////////////////////////////////////////////////////////////////////
const vector<uint16> & TSPII_VcgIf::GetSrcMembers()
{
    return itsSrcMembers;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetSnkMembers(const vector<uint16> & theMembers)
{
    itsSnkMembers = theMembers;
}

///////////////////////////////////////////////////////////////////////////////
const vector<uint16> & TSPII_VcgIf::GetSnkMembers()
{
    return itsSnkMembers;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::DoMemberChanges()
{
    //do nothing here
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::SetRerouteTtp(bool theMode)
{
    itsRerouteTtp = theMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::IsLcasMemberBusy(TSPII_XcRecord theXconn)
{
    return false;  // not busy
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::DoDriverEvent(TSPII_VcgDriverEvent theEvent, uint16 theMember, bool isIngress)
{
    // do nothing in simulation
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_VcgIf::WriteObjectBinary(FC_Stream & theStream)
{
    int     aTemp;
    int     aTimeSlotsSize;
    char    aTimeSlot[4];
    string  aTimeSlots;
    string  aSrcTimeSlots;
    string  aSnkTimeSlots;
    int     aIndex;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes
    theStream << itsNumActiveTxMbrs;
    theStream << itsNumActiveRxMbrs;
    theStream << itsTxTlc;
    theStream << itsTxPlc;
    theStream << itsRxTlc;
    theStream << itsRxPlc;
    theStream << itsLosAlign;
    theStream << itsLcasDetected;
    theStream << itsLcasRxDetected;
    theStream << itsActive;
    theStream << itsTxFop;
    theStream << itsRxFop;
    for(aIndex=0; aIndex<TSPII_VCG_MBRS_MAX; aIndex++)
    {
        theStream << itsTxSeqNbr[aIndex];
        theStream << itsRxSeqNbr[aIndex];
        theStream << itsRxDiffDelay[aIndex];
        aTemp = itsTxState[aIndex];
        theStream << aTemp;
        aTemp = itsRxState[aIndex];
        theStream << aTemp;
        theStream << itsSeqMisMatch[aIndex];
        theStream << itsLosMfAlign[aIndex];
        theStream << itsMbrNotDskew[aIndex];
    }

    // Configuration attributes
    theStream << itsHoldOffTimer;
    theStream << itsWaitToRestoreTimer;
    theStream << itsPlcThres;
    theStream << itsTlcThres;
    theStream << itsDiffDelayThres;
    aTemp = itsVcatType;
    theStream << aTemp;
    theStream << itsIsConnAsSrc;
    theStream << itsIsConnAsDest;
    theStream << itsProtectedVcgId;
    theStream << itsProtectedVcgSlot;
    theStream << itsLcasEnabled;

    // Convert theMembers vector into a char string for serialization
    aTimeSlotsSize = itsMembers.size();
    theStream << aTimeSlotsSize;
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << aTimeSlots;

    // Convert theMembers vector into a char string for serialization
    aTimeSlotsSize = itsSrcMembers.size();
    theStream << aTimeSlotsSize;
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsSrcMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aSrcTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << aSrcTimeSlots;
    // Convert theMembers vector into a char string for serialization
    aTimeSlotsSize = itsSnkMembers.size();
    theStream << aTimeSlotsSize;
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsSnkMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aSnkTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << aSnkTimeSlots;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_VcgIf::ReadObjectBinary(FC_Stream & theStream)
{
    int     aTemp;
    int     aTimeSlotsSize;
    char    aTimeSlotsBuf[(TSPII_VCG_MBRS_MAX * 4) + 10];  // Padded Buffer
    char*   aTimeSlot;
    int     aIndex;

    // Monitoring attributes
    theStream >> itsNumActiveTxMbrs;
    theStream >> itsNumActiveRxMbrs;
    theStream >> itsTxTlc;
    theStream >> itsTxPlc;
    theStream >> itsRxTlc;
    theStream >> itsRxPlc;
    theStream >> itsLosAlign;
    theStream >> itsLcasDetected;
    theStream >> itsLcasRxDetected;
    theStream >> itsActive;
    theStream >> itsTxFop;
    theStream >> itsRxFop;
    for(aIndex=0; aIndex<TSPII_VCG_MBRS_MAX; aIndex++)
    {
        theStream >> itsTxSeqNbr[aIndex];
        theStream >> itsRxSeqNbr[aIndex];
        theStream >> itsRxDiffDelay[aIndex];
        theStream >> aTemp;
        itsTxState[aIndex] = (CT_TEL_VCG_STATE) aTemp;
        theStream >> aTemp;
        itsRxState[aIndex] = (CT_TEL_VCG_STATE) aTemp;
        theStream >> itsSeqMisMatch[aIndex];
        theStream >> itsLosMfAlign[aIndex];
        theStream >> itsMbrNotDskew[aIndex];
    }

    // Configuration attributes
    theStream >> itsHoldOffTimer;
    theStream >> itsWaitToRestoreTimer;
    theStream >> itsPlcThres;
    theStream >> itsTlcThres;
    theStream >> itsDiffDelayThres;
    theStream >> aTemp;
    itsVcatType = (CT_TEL_VCAT_TYPE) aTemp;
    theStream >> itsIsConnAsSrc;
    theStream >> itsIsConnAsDest;
    theStream >> itsProtectedVcgId;
    theStream >> itsProtectedVcgSlot;
    theStream >> itsLcasEnabled;

    theStream >> aTimeSlotsSize;
    theStream >> aTimeSlotsBuf;

    // The Members list must be converted from a char string to a vector
    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }
    // The Members list must be converted from a char string to a vector
    theStream >> aTimeSlotsSize;
    theStream >> aTimeSlotsBuf;
    itsSrcMembers.erase(itsSrcMembers.begin(), itsSrcMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsSrcMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }
    // The Members list must be converted from a char string to a vector
    theStream >> aTimeSlotsSize;
    theStream >> aTimeSlotsBuf;
    itsSnkMembers.erase(itsSnkMembers.begin(), itsSnkMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsSnkMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_VcgIf::WriteObject(ostream & theStream)
{
    int     aTemp;
    int     aTimeSlotsSize;
    char    aTimeSlot[4];
    string  aTimeSlots;
    string  aSrcTimeSlots;
    string  aSnkTimeSlots;
    int     aIndex;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes
    theStream << FC_InsertVar(itsNumActiveTxMbrs);
    theStream << FC_InsertVar(itsNumActiveRxMbrs);
    theStream << FC_InsertVar(itsTxTlc);
    theStream << FC_InsertVar(itsTxPlc);
    theStream << FC_InsertVar(itsRxTlc);
    theStream << FC_InsertVar(itsRxPlc);
    theStream << FC_InsertVar(itsLosAlign);
    theStream << FC_InsertVar(itsLcasDetected);
    theStream << FC_InsertVar(itsLcasRxDetected);
    theStream << FC_InsertVar(itsActive);
    theStream << FC_InsertVar(itsTxFop);
    theStream << FC_InsertVar(itsRxFop);
    for(aIndex=0; aIndex<TSPII_VCG_MBRS_MAX; aIndex++)
    {
        theStream << FC_InsertVar(itsTxSeqNbr[aIndex]);
        theStream << FC_InsertVar(itsRxSeqNbr[aIndex]);
        theStream << FC_InsertVar(itsRxDiffDelay[aIndex]);
        aTemp = itsTxState[aIndex];
        theStream << FC_InsertVar(aTemp);
        aTemp = itsRxState[aIndex];
        theStream << FC_InsertVar(aTemp);
        theStream << FC_InsertVar(itsSeqMisMatch[aIndex]);
        theStream << FC_InsertVar(itsLosMfAlign[aIndex]);
        theStream << FC_InsertVar(itsMbrNotDskew[aIndex]);
    }

    // Configuration attributes
    theStream << FC_InsertVar(itsHoldOffTimer);
    theStream << FC_InsertVar(itsWaitToRestoreTimer);
    theStream << FC_InsertVar(itsPlcThres);
    theStream << FC_InsertVar(itsTlcThres);
    theStream << FC_InsertVar(itsDiffDelayThres);
    aTemp = itsVcatType;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsIsConnAsSrc);
    theStream << FC_InsertVar(itsIsConnAsDest);
    theStream << FC_InsertVar(itsProtectedVcgId);
    theStream << FC_InsertVar(itsProtectedVcgSlot);
    theStream << FC_InsertVar(itsLcasEnabled);

    // Convert the Members vector into a char string for serialization
    aTimeSlotsSize = itsMembers.size();
    theStream << FC_InsertVar(aTimeSlotsSize);
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << FC_InsertVar(aTimeSlots);
    // Convert the Source Members vector into a char string for serialization
    aTimeSlotsSize = itsSrcMembers.size();
    theStream << FC_InsertVar(aTimeSlotsSize);
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsSrcMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aSrcTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << FC_InsertVar(aSrcTimeSlots);
    // Convert the Sink Members vector into a char string for serialization
    aTimeSlotsSize = itsSnkMembers.size();
    theStream << FC_InsertVar(aTimeSlotsSize);
    aIndex = 0;
    while (aTimeSlotsSize > 0)
    {
        sprintf(aTimeSlot, "%3d", itsSnkMembers[aIndex]);
        aTimeSlot[3] = 0;          // force null termination
        aSnkTimeSlots += aTimeSlot;   // add to the running string
        aTimeSlotsSize--;
        aIndex++;
    }
    theStream << FC_InsertVar(aSnkTimeSlots);
    //jej timestamp debug
    theStream << FC_InsertVar(myDebugFlag);
    theStream << FC_InsertVar(myLastTime);
    theStream << FC_InsertVar(myShortestTime);
    theStream << FC_InsertVar(myLongestTime);
    theStream << FC_InsertVar(myPoint1);
    theStream << FC_InsertVar(myPoint2);
    theStream << FC_InsertVar(myPoint3);
    theStream << FC_InsertVar(myPoint4);
    theStream << FC_InsertVar(myPoint5);
    theStream << FC_InsertVar(myPoint6);
    theStream << FC_InsertVar(myPoint7);
    theStream << FC_InsertVar(myPoint8);
    theStream << FC_InsertVar(myPoint9);
    theStream << FC_InsertVar(myPoint10);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_VcgIf::ReadObject(istream & theStream)
{
    int     aTemp;
    int     aTimeSlotsSize;
    char    aTimeSlotsBuf[(TSPII_VCG_MBRS_MAX * 4) + 10];  // Padded buffer
    char*   aTimeSlot;
    int     aIndex;

    // Monitoring attributes
    theStream >> FC_ExtractVar(itsNumActiveTxMbrs);
    theStream >> FC_ExtractVar(itsNumActiveRxMbrs);
    theStream >> FC_ExtractVar(itsTxTlc);
    theStream >> FC_ExtractVar(itsTxPlc);
    theStream >> FC_ExtractVar(itsRxTlc);
    theStream >> FC_ExtractVar(itsRxPlc);
    theStream >> FC_ExtractVar(itsLosAlign);
    theStream >> FC_ExtractVar(itsLcasDetected);
    theStream >> FC_ExtractVar(itsLcasRxDetected);
    theStream >> FC_ExtractVar(itsActive);
    theStream >> FC_ExtractVar(itsTxFop);
    theStream >> FC_ExtractVar(itsRxFop);

    for(aIndex=0; aIndex<TSPII_VCG_MBRS_MAX; aIndex++)
    {
        theStream >> FC_ExtractVar(itsTxSeqNbr[aIndex]);
        theStream >> FC_ExtractVar(itsRxSeqNbr[aIndex]);
        theStream >> FC_ExtractVar(itsRxDiffDelay[aIndex]);
        theStream >> FC_ExtractVar(aTemp);
        itsTxState[aIndex] = (CT_TEL_VCG_STATE) aTemp;
        theStream >> FC_ExtractVar(aTemp);
        itsRxState[aIndex] = (CT_TEL_VCG_STATE) aTemp;
        theStream >> FC_ExtractVar(itsSeqMisMatch[aIndex]);
        theStream >> FC_ExtractVar(itsLosMfAlign[aIndex]);
        theStream >> FC_ExtractVar(itsMbrNotDskew[aIndex]);
    }

    // Configuration attributes
    theStream >> FC_ExtractVar(itsHoldOffTimer);
    theStream >> FC_ExtractVar(itsWaitToRestoreTimer);
    theStream >> FC_ExtractVar(itsPlcThres);
    theStream >> FC_ExtractVar(itsTlcThres);
    theStream >> FC_ExtractVar(itsDiffDelayThres);
    theStream >> FC_ExtractVar(aTemp);
    itsVcatType = (CT_TEL_VCAT_TYPE) aTemp;
    theStream >> FC_ExtractVar(itsIsConnAsSrc);
    theStream >> FC_ExtractVar(itsIsConnAsDest);
    theStream >> FC_ExtractVar(itsProtectedVcgId);
    theStream >> FC_ExtractVar(itsProtectedVcgSlot);
    theStream >> FC_ExtractVar(itsLcasEnabled);

    // The Members list must be converted from a char string to a vector
    theStream >> FC_ExtractVar(aTimeSlotsSize);
    theStream >> FC_ExtractVar(aTimeSlotsBuf);

    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }
    // The Source Members list must be converted from a char string to a vector
    theStream >> FC_ExtractVar(aTimeSlotsSize);
    theStream >> FC_ExtractVar(aTimeSlotsBuf);

    itsSrcMembers.erase(itsSrcMembers.begin(), itsSrcMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsSrcMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }
    // The Sink Members list must be converted from a char string to a vector
    theStream >> FC_ExtractVar(aTimeSlotsSize);
    theStream >> FC_ExtractVar(aTimeSlotsBuf);

    itsSnkMembers.erase(itsSnkMembers.begin(), itsSnkMembers.end());
    aTimeSlot = strtok(aTimeSlotsBuf, " ");
    while (aTimeSlotsSize > 0)
    {
        itsSnkMembers.push_back(((uint16) atoi(aTimeSlot)));
        aTimeSlot = strtok(NULL, " ");
        aTimeSlotsSize--;
    }

    //jej timestamp debug
    theStream >> FC_ExtractVar(myDebugFlag);
    theStream >> FC_ExtractVar(myLastTime);
    theStream >> FC_ExtractVar(myShortestTime);
    theStream >> FC_ExtractVar(myLongestTime);
    theStream >> FC_ExtractVar(myPoint1);
    theStream >> FC_ExtractVar(myPoint2);
    theStream >> FC_ExtractVar(myPoint3);
    theStream >> FC_ExtractVar(myPoint4);
    theStream >> FC_ExtractVar(myPoint5);
    theStream >> FC_ExtractVar(myPoint6);
    theStream >> FC_ExtractVar(myPoint7);
    theStream >> FC_ExtractVar(myPoint8);
    theStream >> FC_ExtractVar(myPoint9);
    theStream >> FC_ExtractVar(myPoint10);
    RefreshSet();


    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  VCG Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Hold Off Timer        = " << itsHoldOffTimer                     << "\n";
    theStream << "      Wait To Restore Timer = " << itsWaitToRestoreTimer               << "\n";
    theStream << "      PLC Threshold         = " << itsPlcThres                         << "\n";
    theStream << "      TLC Threshold         = " << itsTlcThres                         << "\n";
    theStream << "      Diff Delay Threshold  = " << itsDiffDelayThres                   << "\n";
    theStream << "      VCAT Type             = " << DISPLAY_VCAT_TYPE(itsVcatType)      << "\n";
    theStream << "      Connected As Source   = " << DISPLAY_BOOL(itsIsConnAsSrc)        << "\n";
    theStream << "      Connected As Dest     = " << DISPLAY_BOOL(itsIsConnAsDest)       << "\n";
    theStream << "      Protected VCG ID      = " << itsProtectedVcgId                   << "\n";
    theStream << "      Protected VCG Slot    = " << itsProtectedVcgSlot                 << "\n";
    theStream << "      LCAS Enabled          = " << DISPLAY_BOOL(itsLcasEnabled)        << "\n";
    theStream << "      Members               = " << DisplayMembers()                    << "\n";
    theStream << "      Source Members        = " << DisplaySrcMembers()                 << "\n";
    theStream << "      Sink Members          = " << DisplaySnkMembers()                 << "\n";
    theStream << "    MONITORING\n";
    theStream << "      Active Tx Members     = " << itsNumActiveTxMbrs                  << "\n";
    theStream << "      Active Rx Members     = " << itsNumActiveRxMbrs                  << "\n";
    theStream << "      Actual Config Members = " << DisplayActualMembers()              << "\n";
    theStream << "      LCAS Detected         = " << DISPLAY_BOOL(itsLcasDetected)       << "\n";
    theStream << "      LCAS Received         = " << DISPLAY_BOOL(itsLcasRxDetected)     << "\n";
    theStream << "      Active (Protection)   = " << DISPLAY_BOOL(itsActive)             << "\n";
    theStream << "      Tx TLC Defect         = " << TEXT_DEFECT(itsTxTlc)               << "\n";
    theStream << "      Tx PLC Defect         = " << TEXT_DEFECT(itsTxPlc)               << "\n";
    theStream << "      Rx TLC Defect         = " << TEXT_DEFECT(itsRxTlc)               << "\n";
    theStream << "      Rx PLC Defect         = " << TEXT_DEFECT(itsRxPlc)               << "\n";
    theStream << "      LOS Align Defect      = " << TEXT_DEFECT(itsLosAlign)            << "\n";
    theStream << "      Tx FOP Defect         = " << TEXT_DEFECT(itsTxFop)               << "\n";
    theStream << "      Rx FOP Defect         = " << TEXT_DEFECT(itsRxFop)               << "\n";
    theStream << "      Seq Mismatch Defect   = " << DisplaySeqMisMatch()                << "\n";
    theStream << "      LOS MF Align Defect   = " << DisplayLosMfAlign()                 << "\n";
    theStream << "      Mbr Not Deskew Defect = " << DisplayMbrNotDskew()                << "\n";
    theStream << "      Tx Seq Number         = " << DisplayTxSeqNbr()                   << "\n";
    theStream << "      Rx Seq Number         = " << DisplayRxSeqNbr()                   << "\n";
    theStream << "      Rx Diff Delay         = " << DisplayRxDiffDelay()                << "\n";
    theStream << "      Tx State              = " << DisplayTxState()                    << "\n";
    theStream << "      Rx State              = " << DisplayRxState()                    << "\n";
    theStream << "      Delayed XCs           = " << DisplayDelayedXc()                  << "\n";
    theStream << "      Rx ReSequenced        = " << DISPLAY_BOOL(myRxSeqFixed)          << "\n";
    //jej tmestamp debug
    if (myDebugFlag)
    {
        theStream << "Debug time measurement in ticks"<<endl;
        theStream << "VCG   - Last Time          = " << myLastTime << endl;
        theStream << "VCG   - Shortest Time      = " << myShortestTime << endl;
        theStream << "VCG   - Longest Time       = " << myLongestTime << endl;
        theStream << "VCG   - Last Breakdown = " << myPoint1 << " "  << myPoint2 << " "  << myPoint3 << " "
                                                 << myPoint4 << " "  << myPoint5 << " "  << myPoint6 << " "
                                                 << myPoint7 << " "  << myPoint8 << " "  << myPoint9 << " "
                                                   << myPoint10 << " "  << endl;

        theStream << "ProtectedVCG - Last Time      = " << myProtectLastTime << endl;
        theStream << "ProtectedVCG - Shortest Time  = " << myProtectShortestTime << endl;
        theStream << "ProtectedVCG - Longest Time   = " << myProtectLongestTime << endl;
        theStream << "ProtectedVCG - Last Breakdown = " << myProtectPoint1 << " "  << myProtectPoint2 << " "  << endl;
    }
        char buf[80];
        theStream << "\nReSequencing Stats              min        max     Last\n";
        sprintf(buf,"    execution time(mSec)       = %4d %4d    %4d\n",minReSeqExecTime/1000, maxReSeqExecTime/1000, myReSeqExecTime/1000);
        theStream << buf;
        sprintf(buf,"    wakeup - fix time(mSec)    = %4d %4d    %4d\n",minReSeqEndTime/1000, maxReSeqEndTime/1000, myReSeqEndTimeStamp/1000);
        theStream << buf;
        theStream << "    ReSequence count           = "<<myReSeqcount<<endl;
        theStream << "    ReSequence fix count       = "<<mySeqMsMatchFixCount<<endl;


    theStream << endl;

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::Set(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "hold") == 0))
    {
        SetHoldOffTimer(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "wait") == 0))
    {
        SetWaitToRestoreTimer(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "plc") == 0))
    {
        SetPlcThres((uint16) atoi(argv[1]));
    }
    else if ((argc == 2) && (strcmp(argv[0], "tlc") == 0))
    {
        SetTlcThres((uint16) atoi(argv[1]));
    }
    else if ((argc == 2) && (strcmp(argv[0], "delay") == 0))
    {
        SetDiffDelayThres(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "type") == 0))
    {
        printUsage = true;
        for (int i = 0; i < CT_TEL_VCAT_LAST; i++) if (strcmp(argv[1], DISPLAY_VCAT_TYPE(i)) == 0)
        {
            SetVcatType((CT_TEL_VCAT_TYPE)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "src") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsConnAsSrc(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsConnAsSrc(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "dest") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsConnAsDest(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsConnAsDest(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "lcas") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLcasEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLcasEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }

    else if ((argc == 2) && (strcmp(argv[0], "members") == 0) &&
             (strcmp(argv[1], "empty") == 0))
    {
        vector<uint16> aTimeSlots;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        SetMembers(aTimeSlots);
    }
    else if ((argc == 2) && (strcmp(argv[0], "members") == 0))
    {
        vector<uint16> aTimeSlots;
        char           *aTimeSlot;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        aTimeSlot = strtok(argv[1], ",");
        while (aTimeSlot != NULL)
        {
            aTimeSlots.push_back(((uint16) (atoi(aTimeSlot) - 1))); // Convert to zero base
            aTimeSlot = strtok(NULL, ",");
        }
        SetMembers(aTimeSlots);
    }
    else if ((argc == 2) && (strcmp(argv[0], "srcmembers") == 0) &&
             (strcmp(argv[1], "empty") == 0))
    {
        vector<uint16> aTimeSlots;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        SetSrcMembers(aTimeSlots);
    }
    else if ((argc == 2) && (strcmp(argv[0], "srcmembers") == 0))
    {
        vector<uint16> aTimeSlots;
        char           *aTimeSlot;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        aTimeSlot = strtok(argv[1], ",");
        while (aTimeSlot != NULL)
        {
            aTimeSlots.push_back(((uint16) (atoi(aTimeSlot) - 1))); // Convert to zero base
            aTimeSlot = strtok(NULL, ",");
        }
        SetSrcMembers(aTimeSlots);
    }
    else if ((argc == 2) && (strcmp(argv[0], "snkmembers") == 0) &&
             (strcmp(argv[1], "empty") == 0))
    {
        vector<uint16> aTimeSlots;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        SetSnkMembers(aTimeSlots);
    }
    else if ((argc == 2) && (strcmp(argv[0], "snkmembers") == 0))
    {
        vector<uint16> aTimeSlots;
        char           *aTimeSlot;

        printUsage = false;
        aTimeSlots.erase(aTimeSlots.begin(), aTimeSlots.end());
        aTimeSlot = strtok(argv[1], ",");
        while (aTimeSlot != NULL)
        {
            aTimeSlots.push_back(((uint16) (atoi(aTimeSlot) - 1))); // Convert to zero base
            aTimeSlot = strtok(NULL, ",");
        }
        SetSnkMembers(aTimeSlots);
    }
    else if ((argc==3) && (strcmp(argv[0],"protect") == 0))
    {
        int vcgid = atoi(argv[1]);
        if ((vcgid >= -1 && vcgid <64) || (vcgid == 99))
        {
            SetProtectedVcgID(vcgid, atoi(argv[2]));

        }
        else
            printUsage = true;
    }
    else if ((argc==2) && (!strncmp(argv[0],"deb",3)))
    {
        SetDebugFlagSet(argv[1][0]=='e');
    }

    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    hold            0-1000\n"
                   "    wait            0-1000\n"
                   "    plc             0-192\n"
                   "    tlc             0-192\n"
                   "    delay           0-1000\n"
                   "    type            <STS1|STS3C|VC3|VC4|DS3|DS1|E3|E1|Unknown>\n"
                   "    encap           <GFP|BITX86|BYTEX86>\n"
                   "    phyid           1-192\n"
                   "    src             <on|off>\n"
                   "    dest            <on|off>\n"
                   "    lcas            <on|off>\n"
                   "    protect         <vcgId><vcgSlot>   vcgId   0-63\n"
                   "                                       vcgslot 1-19\n"
                   "    members         <1,5,19|empty> 1 Based \n"
                   "    srcmembers      <1,5,19|empty> 1 Based \n"
                   "    snkmembers      <1,5,19|empty> 1 Based \n"
                   "    deb             <e-nable|d-isable> \n"

                   << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::Simul(int argc, char ** argv)
{
    int  aMbr;
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "txact") == 0))
    {
        itsNumActiveTxMbrs = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxact") == 0))
    {
        itsNumActiveRxMbrs = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "txtlc") == 0))
    {
        itsTxTlc = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "txplc") == 0))
    {
        itsTxPlc = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxtlc") == 0))
    {
        itsRxTlc = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxplc") == 0))
    {
        itsRxPlc = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "losaln") == 0))
    {
        itsLosAlign = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "txfop") == 0))
    {
        itsTxFop = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxfop") == 0))
    {
        itsRxFop = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 3) && (strcmp(argv[0], "rxseq") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsRxSeqNbr[aMbr - 1] = atoi(argv[2]);  // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "txseq") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsTxSeqNbr[aMbr - 1] = atoi(argv[2]);  // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "rxdelay") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsRxDiffDelay[aMbr - 1] = strtoul(argv[2], NULL, 0); // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "txstate") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            printUsage = true;
            for (int i = 0; i <= CT_TEL_VCG_ST_UNKNOWN; i++) if (strcmp(argv[2], DISPLAY_VCG_STATE(i)) == 0)
            {
                itsTxState[aMbr - 1] = ((CT_TEL_VCG_STATE)i);  // zero based
                printUsage = false;
                break;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "rxstate") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            printUsage = true;
            for (int i = 0; i <= CT_TEL_VCG_ST_UNKNOWN; i++) if (strcmp(argv[2], DISPLAY_VCG_STATE(i)) == 0)
            {
                itsRxState[aMbr - 1] = ((CT_TEL_VCG_STATE)i);  // zero based
                printUsage = false;
                break;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "lcas") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsLcasDetected = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsLcasDetected = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "lcasrx") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsLcasRxDetected = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsLcasRxDetected = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "active") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsActive = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsActive = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "forcerefresh") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsForceEvcRefresh = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsForceEvcRefresh = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "seqmis") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsSeqMisMatch[aMbr - 1] = atoi(argv[2]);  // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "losmfaln") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsLosMfAlign[aMbr - 1] = atoi(argv[2]);  // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "mbrndskw") == 0))
    {
        aMbr = atoi(argv[1]);
        if((aMbr > 0) && (aMbr <= TSPII_VCG_MBRS_MAX))
        {
            itsMbrNotDskew[aMbr - 1] = atoi(argv[2]);  // zero based
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "ingenqdropfc") == 0))
    {
        itsIngressEnqueueDropFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "ingenqframes") == 0))
    {
        itsIngressEnqueueFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "ingdeqframes") == 0))
    {
        itsIngressDequeueFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "egrenqdropfc") == 0))
    {
        itsEgressEnqueueDropFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "egrenqframes") == 0))
    {
        itsEgressEnqueueFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "egrdeqframes") == 0))
    {
        itsEgressDequeueFrames = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 1) && (strcmp(argv[0], "getStats") == 0))
    {
        GetVcgStats(itsIngressEnqueueDropFrames,
                    itsIngressEnqueueFrames,
                    itsIngressDequeueFrames,
                    itsEgressEnqueueDropFrames,
                    itsEgressEnqueueFrames,
                    itsEgressDequeueFrames);
    }
    else if ((argc == 1) && (strcmp(argv[0], "clearStats") == 0))
    {
        ClearVcgStats();
    }
    else if ((argc == 1) && (strcmp(argv[0], "dumpStats") == 0))
    {
        DumpVcgStats();
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    txact           0-192\n"
                   "    rxact           0-192\n"
                   "    lcas            <on|off>\n"
                   "    lcasrx          <on|off>\n"
                   "    active          <on|off>\n"
                   "    forcerefresh    <on|off>\n"
                   "    txtlc           x\n"
                   "    txplc           x\n"
                   "    rxtlc           x\n"
                   "    rxplc           x\n"
                   "    losaln          x\n"
                   "    txfop           x\n"
                   "    rxfop           x\n"
                   "    seqmis          <mbr> <x> 1 Based\n"
                   "    losmfaln        <mbr> <x> 1 Based\n"
                   "    mbrndskw        <mbr> <x> 1 Based\n"
                   "    rxseq           <mbr> <x> 1 Based\n"
                   "    txseq           <mbr> <x> 1 Based\n"
                   "    rxdelay         <mbr> <x> 1 Based\n"
                   "    txstate         <mbr> <x> 1 Based\n"
                   "    rxstate         <mbr> <x> 1 Based\n"
                   "    ingenqdropfc    <uint32>\n"
                   "    ingenqframes    <uint32>\n"
                   "    ingdeqframes    <uint32>\n"
                   "    egrenqdropfc    <uint32>\n"
                   "    egrenqframes    <uint32>\n"
                   "    egrdeqframes    <uint32>\n"
                   "    getStats        \n"
                   "    clearStats      \n"
                   "    dumpStats       "<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayTxSeqNbr()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", itsTxSeqNbr[itsMembers[aIndex]]);
        aBuf[9] = 0;        // force null termination
        aStr += aBuf;       // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayRxSeqNbr()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", itsRxSeqNbr[itsMembers[aIndex]]);
        aBuf[9] = 0;        // force null termination
        aStr += aBuf;       // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}
///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayMembers()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", (itsMembers[aIndex] + 1));  // Convert to 1 base
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplaySrcMembers()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsSrcMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", (itsSrcMembers[aIndex] + 1));  // Convert to 1 base
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplaySnkMembers()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsSnkMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", (itsSnkMembers[aIndex] + 1));  // Convert to 1 base
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayActualMembers()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsActualMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", (itsActualMembers[aIndex] + 1));  // Convert to 1 base
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}
///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayRxDiffDelay()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", (itsRxDiffDelay[itsMembers[aIndex]]));
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayTxState()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%s,", DISPLAY_VCG_STATE(itsTxState[itsMembers[aIndex]]));
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayRxState()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%s,", DISPLAY_VCG_STATE(itsRxState[itsMembers[aIndex]]));
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplaySeqMisMatch()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", itsSeqMisMatch[itsMembers[aIndex]]);
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayLosMfAlign()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", itsLosMfAlign[itsMembers[aIndex]]);
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayMbrNotDskew()
{
    int     aSize;
    char    aBuf[10];
    string  aStr;
    int     aIndex;

    aIndex = 0;
    aSize = itsMembers.size();
    while (aSize > 0)
    {
        sprintf(aBuf, "%d,", itsMbrNotDskew[itsMembers[aIndex]]);
        aBuf[9] = 0;    // force null termination
        aStr += aBuf;   // add to the running string
        aSize--;
        aIndex++;
    }
    if(aStr == "")
    {
        aStr = "empty";
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_VcgIf::DisplayDelayedXc()
{
    return "";
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::GetVcgStats(uint32 & theIngressEnqueueDropFrames,
                              uint32 & theIngressEnqueueFrames,
                              uint32 & theIngressDequeueFrames,
                              uint32 & theEgressEnqueueDropFrames,
                              uint32 & theEgressEnqueueFrames,
                              uint32 & theEgressDequeueFrames)
{
    theIngressEnqueueDropFrames = itsIngressEnqueueDropFrames;
    theIngressEnqueueFrames     = itsIngressEnqueueFrames;
    theIngressDequeueFrames     = itsIngressDequeueFrames;
    theEgressEnqueueDropFrames  = itsEgressEnqueueDropFrames;
    theEgressEnqueueFrames      = itsEgressEnqueueFrames;
    theEgressDequeueFrames      = itsEgressDequeueFrames;
    return(true);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::ClearVcgStats()
{
    itsIngressEnqueueDropFrames = 0;
    itsIngressEnqueueFrames = 0;
    itsIngressDequeueFrames = 0;
    itsEgressEnqueueDropFrames = 0;
    itsEgressEnqueueFrames = 0;
    itsEgressDequeueFrames = 0;
    return(true);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::DumpVcgStats()
{
    GetVcgStats(itsIngressEnqueueDropFrames,
                itsIngressEnqueueFrames,
                itsIngressDequeueFrames,
                itsEgressEnqueueDropFrames,
                itsEgressEnqueueFrames,
                itsEgressDequeueFrames);

    fc_cout << "  VCG Stats " << endl;
    fc_cout << "      Ingress Enqueue Drop Frame Count = " << itsIngressEnqueueDropFrames << endl;
    fc_cout << "      Ingress Enqueue Frame Count      = " << itsIngressEnqueueFrames << endl;
    fc_cout << "      Ingress Dequeue Frame Count      = " << itsIngressDequeueFrames << endl;
    fc_cout << "      Egress  Enqueue Drop Frame Count = " << itsEgressEnqueueDropFrames << endl;
    fc_cout << "      Egress  Enqueue Frame Count      = " << itsEgressEnqueueFrames << endl;
    fc_cout << "      Egress  Dequeue Frame Count      = " << itsEgressDequeueFrames << endl;

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}


///////////////////////////////////////////////////////////////////////////////
// Exclusive method that Cfg_HwRefreshVcg calls to ensure that all EVC's
// are in sync with VCG changes
///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::KickEvcRefresh()
{
}


void TSPII_VcgIf::SetDebugFlagSet(bool theDebugEnable)
{
    myDebugFlag = theDebugEnable;
}

bool TSPII_VcgIf::IsDebugFlagSet() const
{
    return myDebugFlag;
}


void TSPII_VcgIf::SetProcessTime(const uint32 theTime)
{
    myLastTime = theTime;

    if (myLastTime > myLongestTime)
        myLongestTime = myLastTime;

    if (myShortestTime == 0)
    {
        myShortestTime = myLastTime;
    }
    else if ((myLastTime != 0) && (myLastTime < myShortestTime))
    {
        myShortestTime = myLastTime;
    }
}

void TSPII_VcgIf::SetBreakdown(const uint32 aPt1, const uint32 aPt2, const uint32 aPt3,
                               const uint32 aPt4, const uint32 aPt5, const uint32 aPt6,
                               const uint32 aPt7, const uint32 aPt8, const uint32 aPt9,
                               const uint32 aPt10)
{
    myPoint1 = aPt1;
    myPoint2 = aPt2;
    myPoint3 = aPt3;
    myPoint4 = aPt4;
    myPoint5 = aPt5;
    myPoint6 = aPt6;
    myPoint7 = aPt7;
    myPoint8 = aPt8;
    myPoint9 = aPt9;
    myPoint10 = aPt10;
}

void TSPII_VcgIf::SetProtectedVcgProcessTime(const uint32 theTime)
{
    myProtectLastTime = theTime;

    if (myProtectLastTime > myProtectLongestTime)
        myProtectLongestTime = myProtectLastTime;

    if (myProtectShortestTime == 0)
    {
        myProtectShortestTime = myProtectLastTime;
    }
    else if ((myProtectLastTime != 0) && (myProtectLastTime < myProtectShortestTime))
    {
        myProtectShortestTime = myProtectLastTime;
    }
}
void TSPII_VcgIf::SetProtectVcgBreakdown(const uint32 aPt11, const uint32 aPt12)
{
    myProtectPoint1 = aPt11;
    myProtectPoint2 = aPt12;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::getReSequenceNeeded() const
{
    return myReSeqNeeded;
}

///////////////////////////////////////////////////////////////////////////////
// Sets a flag if we have a sequence mismatch and get a timestamp for
// measurement purposes
///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgIf::setReSequenceNeeded(bool state)
{
    int prevfixCount = mySeqMsMatchFixCount;

    if((state == true) && !myReSeqNeeded)
    {
        myReSeqReqTimeStamp = TMBget_timestamp();
    }
    else if ((state == false) && myReSeqNeeded)
    {
        myReSeqExecTime = TMBusec_since(myReSeqStartFixTimeStamp);
        if (myReSeqExecTime > maxReSeqExecTime)
        {
            maxReSeqExecTime = myReSeqExecTime;
        }
        if ((myReSeqExecTime < minReSeqExecTime) || (minReSeqExecTime == 0))
        {
            minReSeqExecTime = myReSeqExecTime;
        }

    }
    myReSeqNeeded = state;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgIf::fixSequenceMisMatch()
{
    myReSeqNeeded = false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
bool  TSPII_VcgIf::CheckSeqMsMatch()
{
    return false;
}

