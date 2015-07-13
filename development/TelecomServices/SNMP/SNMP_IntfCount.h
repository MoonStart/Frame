/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_INTFCOUNT_H
#define SNMP_INTFCOUNT_H

#include <SNMP/SNMP_Counter.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>

/* Forward declaration of classes */
class MON_RmonCounters;
class MON_RmonStatus;

using namespace std;

class SNMP_BbIntfCount : public FC_BbObject
{
public:

    SNMP_BbIntfCount();
    virtual ~SNMP_BbIntfCount();

    virtual void Init(restart_type theRestart);

    inline CT_SNMP_Integer32 GetMtu();
    inline CT_SNMP_Guage32   GetSpeed();
    inline CT_SNMP_String&   GetPhysAddress();
    inline CT_SNMP_Counter32 GetInOctets();
    inline CT_SNMP_Counter32 GetInUCastPkts();
    inline CT_SNMP_Counter32 GetInDiscards();
    inline CT_SNMP_Counter32 GetInErrors();
    inline CT_SNMP_Counter32 GetInUnknownProtos();
    inline CT_SNMP_Counter32 GetOutOctets();
    inline CT_SNMP_Counter32 GetOutUCastPkts();
    inline CT_SNMP_Counter32 GetOutDiscards();
    inline CT_SNMP_Counter32 GetOutErrors();
    inline CT_SNMP_Counter32 GetInMulticastPkts();
    inline CT_SNMP_Counter32 GetInBroadcastPkts();
    inline CT_SNMP_Counter32 GetOutMulticastPkts();
    inline CT_SNMP_Counter32 GetOutBroadcastPkts();
    inline CT_SNMP_Counter32 GetHCInOctets();
    inline CT_SNMP_Counter32 GetHCInUCastPkts();
    inline CT_SNMP_Counter32 GetHCInMulticastPkts();
    inline CT_SNMP_Counter32 GetHCInBroadcastPkts();
    inline CT_SNMP_Counter32 GetHCOutOctets();
    inline CT_SNMP_Counter32 GetHCOutUCastPkts();
    inline CT_SNMP_Counter32 GetHCOutMulticastPkts();
    inline CT_SNMP_Counter32 GetHCOutBroadcastPkts();
    inline CT_SNMP_Guage32   GetHighSpeed();
    inline CT_SNMP_TruthValue GetConnectorPresent();
    inline CT_SNMP_TimeStamp GetDiscontinuityTime();

    void Update(MON_RmonCounters& theCounter, MON_RmonStatus& theStatus);

protected:

    virtual istream& ReadObject( istream& theStream );
    virtual ostream& WriteObject( ostream& theStream );

private:
    void SetPhysAddressString(uint32 theLowAddr, uint32 theHighAddr);
    SNMP_Counter myInOctets;
    SNMP_Counter myInUCastPkts;
    SNMP_Counter myInDiscards;
    SNMP_Counter myInErrors;
    SNMP_Counter myOutOctets;
    SNMP_Counter myOutUCastPkts;
    SNMP_Counter myOutDiscards;
    SNMP_Counter myOutErrors;
    SNMP_Counter myInMCastPkts;
    SNMP_Counter myInBCastPkts;
    SNMP_Counter myOutMCastPkts;
    SNMP_Counter myOutBCastPkts;
    SNMP_Counter myHCInOctets;
    SNMP_Counter myHCInUCastPkts;
    SNMP_Counter myHCInMCastPkts;
    SNMP_Counter myHCInBCastPkts;
    SNMP_Counter myHCOutOctets;
    SNMP_Counter myHCOutUCastPkts;
    SNMP_Counter myHCOutMCastPkts;
    SNMP_Counter myHCOutBCastPkts;
    CT_SNMP_String myPhysAddress;
    uint32       myPrevLowPhysAddr;
    uint32       myPrevHighPhysAddr;

};

inline CT_SNMP_Integer32 SNMP_BbIntfCount::GetMtu()
{
    return 0;
}
inline CT_SNMP_Guage32   SNMP_BbIntfCount::GetSpeed()
{
    return 0;
}
inline CT_SNMP_String&   SNMP_BbIntfCount::GetPhysAddress()
{
    return myPhysAddress;
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInOctets()
{
    return static_cast<CT_SNMP_Counter32> (myInOctets.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInUCastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myInUCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInDiscards()
{
    return static_cast<CT_SNMP_Counter32> (myInDiscards.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInErrors()
{
    return static_cast<CT_SNMP_Counter32> (myInErrors.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInUnknownProtos()
{
    return 0;
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutOctets()
{
    return static_cast<CT_SNMP_Counter32> (myOutOctets.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutUCastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myOutUCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutDiscards()
{
    return static_cast<CT_SNMP_Counter32> (myOutDiscards.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutErrors()
{
    return static_cast<CT_SNMP_Counter32> (myOutErrors.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInMulticastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myInMCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetInBroadcastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myInBCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutMulticastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myOutMCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetOutBroadcastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myOutBCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCInOctets()
{
    return static_cast<CT_SNMP_Counter32> (myHCInOctets.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCInUCastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCInUCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCInMulticastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCInMCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCInBroadcastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCInBCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCOutOctets()
{
    return static_cast<CT_SNMP_Counter32> (myHCOutOctets.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCOutUCastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCOutUCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCOutMulticastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCOutMCastPkts.GetCount());
}
inline CT_SNMP_Counter32 SNMP_BbIntfCount::GetHCOutBroadcastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myHCOutBCastPkts.GetCount());
}
inline CT_SNMP_Guage32   SNMP_BbIntfCount::GetHighSpeed()
{
    return 0;
}
inline CT_SNMP_TruthValue SNMP_BbIntfCount::GetConnectorPresent()
{
    return CT_SNMP_TruthValue_true;
}
inline CT_SNMP_TimeStamp SNMP_BbIntfCount::GetDiscontinuityTime()
{
    return 0;
}

#endif //SNMP_INTFCOUNT_H
