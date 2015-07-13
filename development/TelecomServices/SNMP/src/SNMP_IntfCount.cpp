/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RmonCounters.h>
#include <Monitoring/MON_RmonStatus.h>
#include <SNMP/SNMP_IntfCount.h>
#include <stdlib.h>

//-----------------------------------------------------------------
SNMP_BbIntfCount::SNMP_BbIntfCount ()
{
}

//-----------------------------------------------------------------
SNMP_BbIntfCount::~SNMP_BbIntfCount ()
{
    // Nothing to do for now.
}

void SNMP_BbIntfCount::SetPhysAddressString(uint32 theLowAddr, uint32 theHighAddr)
{
    char lowAddrStr[16];
    char highAddrStr[16];
    sprintf(&(lowAddrStr[0]), "%08X", theLowAddr);
    sprintf(&(highAddrStr[0]), "%08X", theHighAddr);
    string physAddr;
    physAddr += (&(highAddrStr[4]));
    physAddr += lowAddrStr;
    myPhysAddress = physAddr;
}

//-----------------------------------------------------------------
void SNMP_BbIntfCount::Update(MON_RmonCounters& theCounter, MON_RmonStatus& theStatus) 
{
    uint32 count = 0;
    uint32 lowPhysAddr = theStatus.GetIfPhysAddressLow();
    uint32 highPhysAddr = theStatus.GetIfPhysAddressHigh();
    if ((lowPhysAddr != myPrevLowPhysAddr) || (highPhysAddr != myPrevHighPhysAddr)) 
    {
        SetPhysAddressString(lowPhysAddr, highPhysAddr);
        myPrevLowPhysAddr = lowPhysAddr;
        myPrevHighPhysAddr = highPhysAddr;
    }
    theCounter.GetErrorCount(CT_TEL_RMON_OCTETS, &count);
    myInOctets.Update(count);
    myHCInOctets.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_IN_UCAST_PKTS, &count);
    myInUCastPkts.Update(count);
    myHCInUCastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_IN_DISCARDS, &count);
    myInDiscards.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_IN_ERRORS, &count);
    myInErrors.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_OCTETS, &count);
    myOutOctets.Update(count);
    myHCOutOctets.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_UCAST_PKTS, &count);
    myOutUCastPkts.Update(count);
    myHCOutUCastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_DISCARDS, &count);
    myOutDiscards.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_ERRORS, &count);
    myOutErrors.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_MULTICAST_PKTS, &count);
    myInMCastPkts.Update(count);
    myHCInMCastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_BROADCAST_PKTS, &count);
    myInBCastPkts.Update(count);
    myHCInBCastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_MULTICAST_PKTS, &count);
    myOutMCastPkts.Update(count);
    myHCOutMCastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_IF_OUT_BROADCAST_PKTS, &count);
    myOutBCastPkts.Update(count);
    myHCOutBCastPkts.Update(count);
}

//-----------------------------------------------------------------
ostream& SNMP_BbIntfCount::WriteObject( ostream& theStream )
{
    theStream <<  myInOctets;
    theStream <<  myInUCastPkts;
    theStream <<  myInDiscards;
    theStream <<  myInErrors;
    theStream <<  myOutOctets;
    theStream <<  myOutUCastPkts;
    theStream <<  myOutDiscards;
    theStream <<  myOutErrors;
    theStream <<  myInMCastPkts;
    theStream <<  myInBCastPkts;
    theStream <<  myOutMCastPkts;
    theStream <<  myOutBCastPkts;
    theStream <<  myHCInOctets;
    theStream <<  myHCInUCastPkts;
    theStream <<  myHCInMCastPkts;
    theStream <<  myHCInBCastPkts;
    theStream <<  myHCOutOctets;
    theStream <<  myHCOutUCastPkts;
    theStream <<  myHCOutMCastPkts;
    theStream <<  myHCOutBCastPkts;
    return theStream;
}

//-----------------------------------------------------------------
istream& SNMP_BbIntfCount::ReadObject( istream& theStream )
{
    theStream >>  myInOctets;
    theStream >>  myInUCastPkts;
    theStream >>  myInDiscards;
    theStream >>  myInErrors;
    theStream >>  myOutOctets;
    theStream >>  myOutUCastPkts;
    theStream >>  myOutDiscards;
    theStream >>  myOutErrors;
    theStream >>  myInMCastPkts;
    theStream >>  myInBCastPkts;
    theStream >>  myOutMCastPkts;
    theStream >>  myOutBCastPkts;
    theStream >>  myHCInOctets;
    theStream >>  myHCInUCastPkts;
    theStream >>  myHCInMCastPkts;
    theStream >>  myHCInBCastPkts;
    theStream >>  myHCOutOctets;
    theStream >>  myHCOutUCastPkts;
    theStream >>  myHCOutMCastPkts;
    theStream >>  myHCOutBCastPkts;
    return theStream;
}

//-----------------------------------------------------------------
void SNMP_BbIntfCount::Init(restart_type theRestart)
{
    // Nothing to do for now.
}
