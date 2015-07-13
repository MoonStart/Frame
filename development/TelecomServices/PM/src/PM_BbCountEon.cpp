/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSC.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Update and keep the error count of EON.
--------------------------------------------------------------------------*/

#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_IPCountersIf.h>
#include <PM_BbCountEon.h>


//-----------------------------------------------------------------
//##ModelId=3FA16112015C
PM_BbCountEon::PM_BbCountEon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA16112015D
PM_BbCountEon::~PM_BbCountEon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA16112018E
void PM_BbCountEon::Update(TSPII_IPCountersIf& theCounter) 
{
    // Update all IP counters at TSPII level.
    theCounter.UpdateCounters();

    // Update counters at PM level.
    myIcmpDurCounter.Update(theCounter.GetICMP_DestUnreachableReceived());
    myIcmpDutCounter.Update(theCounter.GetICMP_DestUnreachableTransmitted());
    myIcmpErCounter.Update(theCounter.GetICMP_ErrorsReceived());
    myIcmpTtlerCounter.Update(theCounter.GetICMP_TTLExceededReceived());
    myIpAdderCounter.Update(theCounter.GetIP_AddressErrorsReceived());
    myIpDiscrCounter.Update(theCounter.GetIP_DiscardsReceived());
    myIpDisctCounter.Update(theCounter.GetIP_DiscardsTransmitted());
    myIpHdrrCounter.Update(theCounter.GetIP_HeaderErrorsReceived());
    myIpNoroutestCounter.Update(theCounter.GetIP_NoRoutesTransmitted());

}

//-----------------------------------------------------------------
//##ModelId=3FA161120190
ostream& PM_BbCountEon::WriteObject( ostream& theStream )
{
    return theStream << myIcmpDurCounter
                     << myIcmpDutCounter
                     << myIcmpErCounter
                     << myIcmpTtlerCounter
                     << myIpAdderCounter
                     << myIpDiscrCounter
                     << myIpDisctCounter
                     << myIpHdrrCounter
                     << myIpNoroutestCounter;

}

//-----------------------------------------------------------------
//##ModelId=3FA16112019C
istream& PM_BbCountEon::ReadObject( istream& theStream )
{
    return theStream >> myIcmpDurCounter
                     >> myIcmpDutCounter
                     >> myIcmpErCounter
                     >> myIcmpTtlerCounter
                     >> myIpAdderCounter
                     >> myIpDiscrCounter
                     >> myIpDisctCounter
                     >> myIpHdrrCounter
                     >> myIpNoroutestCounter;

}

//-----------------------------------------------------------------
//##ModelId=3FA16112015F
void PM_BbCountEon::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
