/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 20, 2005 Larry Wolfrum.
 DESCRIPTION:   Update and keep the error count of
                RMON Ethernet facilities.
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTRMON_H
#define PM_BBCOUNTRMON_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <PM/src/PM_Counter.h>


/* Forward declaration of classes */
class MON_RmonCounters;

using namespace std;

//Keeps various RMON counters up to date for the current second.
class PM_BbCountRmon: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbCountRmon();

    //Class default destructor.
    virtual ~PM_BbCountRmon();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of Dropped Events from the 
    //RMON Ethernet statistics (current hardware counter minus 
    //last hardware counter).
    inline CT_PM_64bit_ull GetDroppedEvents() const;

	//Returns the current packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetPackets() const;

	//Returns the current braodcast packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetBroadcastPackets() const;

	//Returns the current multicast packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetMulticastPackets() const;

	//Returns the count if CRC alignment errors from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetCrcAlignErrors() const;

	//Returns the undersize packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetUndersizePackets() const;

	//Returns the oversize packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetOversizePackets() const;

	//Returns the fragmented packet count from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetFragmentedPackets() const;

	//Returns the count of packet jabbers from the 
	//RMON Ethernet statistics (current hardware counter minus 
	//last hardware counter).
	inline CT_PM_64bit_ull GetJabbers() const;

    //Updates the PM counters for the RMON Ethernet statistics.
    void Update(MON_RmonCounters& theCounter);

protected:

    //Stores the counter to the stream.
    //##ModelId=3C9255C700D2
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    //##ModelId=3C9255C700DD
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that maintains the number of dropped events for this second.
    PM_Counter myDroppedEventsCounter;

	//The PM Counter that maintains the number of packets for this second.
	PM_Counter myPacketCounter;

	//The PM Counter that maintains the number of broadcast packets for this second.
	PM_Counter myBroadcastPacketCounter;

	//The PM Counter that maintains the number of multicast packets for this second.
	PM_Counter myMulticastPacketCounter;

	//The PM Counter that maintains the CRC alignment errors for this second.
	PM_Counter myCrcAlignErrorCounter;

	//The PM Counter that maintains the number of undersize packets for this second.
	PM_Counter myUndersizePacketCounter;

	//The PM Counter that maintains the number of oversize packets for this second.
	PM_Counter myOversizePacketCounter;

	//The PM Counter that maintains the number of fragmented packets for this second.
	PM_Counter myFragmentCounter;

	//The PM Counter that maintains the number of packet jabbers for this second.
	PM_Counter myJabberCounter;

};

//-----------------------------------------------------------------
inline CT_PM_64bit_ull PM_BbCountRmon::GetDroppedEvents() const
{
    return myDroppedEventsCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetPackets() const
{
    return myPacketCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetBroadcastPackets() const
{
    return myBroadcastPacketCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetMulticastPackets() const
{
    return myMulticastPacketCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetCrcAlignErrors() const
{
    return myCrcAlignErrorCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetUndersizePackets() const
{
    return myUndersizePacketCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetOversizePackets() const
{
    return myOversizePacketCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetFragmentedPackets() const
{
    return myFragmentCounter.GetCount();

}

inline CT_PM_64bit_ull PM_BbCountRmon::GetJabbers() const
{
    return myJabberCounter.GetCount();

}

#endif //PM_BBCOUNTRMON_H
