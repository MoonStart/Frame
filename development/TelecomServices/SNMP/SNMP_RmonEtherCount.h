/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONETHERCOUNT_H
#define SNMP_RMONETHERCOUNT_H

#include <SNMP/SNMP_Counter.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>

/* Forward declaration of classes */
class MON_RmonCounters;

using namespace std;

class SNMP_BbRmonEtherCount : public FC_BbObject
{
public:

    SNMP_BbRmonEtherCount();
    virtual ~SNMP_BbRmonEtherCount();

    virtual void Init(restart_type theRestart);

    inline CT_SNMP_Counter32 GetDropEvents();
    inline CT_SNMP_Counter32 GetOctets();
    inline CT_SNMP_Counter32 GetPkts();
    inline CT_SNMP_Counter32 GetBroadcastPkts();
    inline CT_SNMP_Counter32 GetMulticastPkts();
    inline CT_SNMP_Counter32 GetCRCAlignErrors();
    inline CT_SNMP_Counter32 GetUndersizePkts();
    inline CT_SNMP_Counter32 GetOversizePkts();
    inline CT_SNMP_Counter32 GetFragments();
    inline CT_SNMP_Counter32 GetJabbers();
    inline CT_SNMP_Counter32 GetCollisions();
    inline CT_SNMP_Counter32 GetPkts64();
    inline CT_SNMP_Counter32 GetPkts65to127();
    inline CT_SNMP_Counter32 GetPkts128to255();
    inline CT_SNMP_Counter32 GetPkts256to511();
    inline CT_SNMP_Counter32 GetPkts512to1023();
    inline CT_SNMP_Counter32 GetPkts1024to1518();
    inline CT_SNMP_Counter32 GetDroppedFrames();

    inline CT_SNMP_Counter32 GetHighOctets();
    inline CT_SNMP_Counter32 GetHighPkts();

    void Update(MON_RmonCounters& theCounter);

protected:

    virtual istream& ReadObject( istream& theStream );
    virtual ostream& WriteObject( ostream& theStream );

private:

    SNMP_Counter myDropEvents;
    SNMP_Counter myOctets;
    SNMP_Counter myPkts;
    SNMP_Counter myBroadcastPkts;
    SNMP_Counter myMulticastPkts;
    SNMP_Counter myCRCAlignErrors;
    SNMP_Counter myUndersizePkts;
    SNMP_Counter myOversizePkts;
    SNMP_Counter myFragments;
    SNMP_Counter myJabbers;
    SNMP_Counter myCollisions;
    SNMP_Counter myPkts64;
    SNMP_Counter myPkts65to127;
    SNMP_Counter myPkts128to255;
    SNMP_Counter myPkts256to511;
    SNMP_Counter myPkts512to1023;
    SNMP_Counter myPkts1024to1518;
    SNMP_Counter myDroppedFrames;


    SNMP_Counter myHighOctets;
    SNMP_Counter myHighPkts;
};

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetDropEvents()
{
    return static_cast<CT_SNMP_Counter32> (myDropEvents.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetOctets()
{
    return static_cast<CT_SNMP_Counter32> (myOctets.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts()
{

    return static_cast<CT_SNMP_Counter32> (myPkts.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetBroadcastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myBroadcastPkts.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetMulticastPkts()
{
    return static_cast<CT_SNMP_Counter32> (myMulticastPkts.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetCRCAlignErrors()
{
    return static_cast<CT_SNMP_Counter32> (myCRCAlignErrors.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetUndersizePkts()
{
    return static_cast<CT_SNMP_Counter32> (myUndersizePkts.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetOversizePkts()
{
    return static_cast<CT_SNMP_Counter32> (myOversizePkts.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetFragments()
{
    return static_cast<CT_SNMP_Counter32> (myFragments.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetJabbers()
{
    return static_cast<CT_SNMP_Counter32> (myJabbers.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetCollisions()
{
    return static_cast<CT_SNMP_Counter32> (myCollisions.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts64()
{
    return static_cast<CT_SNMP_Counter32> (myPkts64.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts65to127()
{
    return static_cast<CT_SNMP_Counter32> (myPkts65to127.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts128to255()
{
    return static_cast<CT_SNMP_Counter32> (myPkts128to255.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts256to511()
{
    return static_cast<CT_SNMP_Counter32> (myPkts256to511.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts512to1023()
{
    return static_cast<CT_SNMP_Counter32> (myPkts512to1023.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetPkts1024to1518()
{
    return static_cast<CT_SNMP_Counter32> (myPkts1024to1518.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetDroppedFrames()
{
    return static_cast<CT_SNMP_Counter32> (myDroppedFrames.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetHighOctets()
{
    return static_cast<CT_SNMP_Counter32> (myHighOctets.GetCount());
}

inline CT_SNMP_Counter32 SNMP_BbRmonEtherCount::GetHighPkts()
{

    return static_cast<CT_SNMP_Counter32> (myHighPkts.GetCount());
}
#endif //SNMP_RMONETHERCOUNT_H
