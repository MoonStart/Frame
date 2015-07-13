/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSC.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Update and keep the error count of EON.
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTEON_H
#define PM_BBCOUNTEON_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


// Forward declaration of classes.
class TSPII_IPCountersIf;

using namespace std;

//Keeps various EON counters up to date for the current second.
//##ModelId=3FA1611103CD
class PM_BbCountEon: public TEL_BbObjectBase
{
public:

    //Class default constructor.
	//##ModelId=3FA16112015C
    PM_BbCountEon();

    //Class default destructor.
	//##ModelId=3FA16112015D
    virtual ~PM_BbCountEon();

    //Initializes BB object according to the restart type.
	//##ModelId=3FA16112015F
    virtual void Init(restart_type theRestart);

    //Returns the current count of ICMP Destination Unreachable Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112016B
    inline uint32 GetIcmpDur() const;

    //Returns the current count of ICMP Destination Unreachable Transmitted
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112016D
    inline uint32 GetIcmpDut() const;

    //Returns the current count of ICMP Errors Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112016F
    inline uint32 GetIcmpEr() const;

    //Returns the current count of ICMP Time To Live Exceeded Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA161120171
    inline uint32 GetIcmpTtler() const;

    //Returns the current count of IP Address Error Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112017C
    inline uint32 GetIpAdder() const;

    //Returns the current count of IP Discards Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112017E
    inline uint32 GetIpDiscr() const;

    //Returns the current count of IP Discrard Transmitted
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA161120180
    inline uint32 GetIpDisct() const;

    //Returns the current count of IP Header Errors Received
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112018A
    inline uint32 GetIpHdrr() const;

    //Returns the current count of IP No Routes Transmitted
    //(current hardware counter minus last hardware counter).
	//##ModelId=3FA16112018C
    inline uint32 GetIpNoroutest() const;

    //Updates the PM counters for IP and ICMP.
	//##ModelId=3FA16112018E
    void Update(TSPII_IPCountersIf& theCounter);

protected:

    //Stores the counter to the stream.
	//##ModelId=3FA161120190
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
	//##ModelId=3FA16112019C
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM counter that memorizes ICMP Destination Unreachable Received.
	//##ModelId=3FA164C30010
    PM_Counter myIcmpDurCounter;

    //The PM counter that memorizes ICMP Destination Unreachable Transmitted.
	//##ModelId=3FA164C30015
    PM_Counter myIcmpDutCounter;

    //The PM counter that memorizes ICMP Errors Received.
	//##ModelId=3FA164C3001F
    PM_Counter myIcmpErCounter;

    //The PM counter that memorizes ICMP Time To Live Exceeded Received.
	//##ModelId=3FA164C3002F
    PM_Counter myIcmpTtlerCounter;

    //The PM counter that memorizes IP Address Error Received.
	//##ModelId=3FA164C3003E
    PM_Counter myIpAdderCounter;

    //The PM counter that memorizes IP Discards Received.
	//##ModelId=3FA164C30043
    PM_Counter myIpDiscrCounter;

    //The PM counter that memorizes IP Discrard Transmitted.
	//##ModelId=3FA164C3004E
    PM_Counter myIpDisctCounter;

    //The PM counter that memorizes IP Header Errors Received.
	//##ModelId=3FA164C3005E
    PM_Counter myIpHdrrCounter;

    //The PM counter that memorizes IP No Routes Transmitted.
	//##ModelId=3FA164C3006D
    PM_Counter myIpNoroutestCounter;

};

//-----------------------------------------------------------------
//##ModelId=3FA16112016B
inline uint32 PM_BbCountEon::GetIcmpDur() const
{
    return myIcmpDurCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112016D
inline uint32 PM_BbCountEon::GetIcmpDut() const
{
    return myIcmpDutCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112016F
inline uint32 PM_BbCountEon::GetIcmpEr() const
{
    return myIcmpErCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA161120171
inline uint32 PM_BbCountEon::GetIcmpTtler() const
{
    return myIcmpTtlerCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112017C
inline uint32 PM_BbCountEon::GetIpAdder() const
{
    return myIpAdderCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112017E
inline uint32 PM_BbCountEon::GetIpDiscr() const
{
    return myIpDiscrCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA161120180
inline uint32 PM_BbCountEon::GetIpDisct() const
{
    return myIpDisctCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112018A
inline uint32 PM_BbCountEon::GetIpHdrr() const
{
    return myIpHdrrCounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3FA16112018C
inline uint32 PM_BbCountEon::GetIpNoroutest() const
{
    return myIpNoroutestCounter.GetCount();

}

#endif //PM_BBCOUNTEON_H
