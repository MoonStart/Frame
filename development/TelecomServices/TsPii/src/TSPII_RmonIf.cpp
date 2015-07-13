/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  
 AUTHOR   :  Denham Reynolds - October 2005
 DESCRIPTION:Definition of the class TSPII_RmonIf
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_RmonIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_RmonIf::TSPII_RmonIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_RmonIf::~TSPII_RmonIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::RefreshGet()
{
    // Mon Attributes  RFC 2819
    itsEtherStatsDropEvents            = GetEtherStatsDropEvents();
    itsEtherStatsOctets                = GetEtherStatsOctets();
    itsEtherStatsPkts                  = GetEtherStatsPkts();
    itsEtherStatsBroadcastPkts         = GetEtherStatsBroadcastPkts();
    itsEtherStatsMulticastPkts         = GetEtherStatsMulticastPkts();
    itsEtherStatsCRCAlignErrors        = GetEtherStatsCRCAlignErrors();
    itsEtherStatsUndersizePkts         = GetEtherStatsUndersizePkts();
    itsEtherStatsOversizePkts          = GetEtherStatsOversizePkts();
    itsEtherStatsFragments             = GetEtherStatsFragments();
    itsEtherStatsJabbers               = GetEtherStatsJabbers();
    itsEtherStatsCollisions            = GetEtherStatsCollisions();
    itsEtherStatsPkts64Octets          = GetEtherStatsPkts64Octets();
    itsEtherStatsPkts65to127Octets     = GetEtherStatsPkts65to127Octets();
    itsEtherStatsPkts128to255Octets    = GetEtherStatsPkts128to255Octets();
    itsEtherStatsPkts256to511Octets    = GetEtherStatsPkts256to511Octets();
    itsEtherStatsPkts512to1023Octets   = GetEtherStatsPkts512to1023Octets();
    itsEtherStatsPkts1024to1518Octets  = GetEtherStatsPkts1024to1518Octets();

    itsEtherStatsHighDropEvents            = GetEtherStatsHighDropEvents();
    itsEtherStatsHighOctets                = GetEtherStatsHighOctets();
    itsEtherStatsHighPkts                  = GetEtherStatsHighPkts();
    itsEtherStatsHighBroadcastPkts         = GetEtherStatsHighBroadcastPkts();
    itsEtherStatsHighMulticastPkts         = GetEtherStatsHighMulticastPkts();
    itsEtherStatsHighCRCAlignErrors        = GetEtherStatsHighCRCAlignErrors();
    itsEtherStatsHighUndersizePkts         = GetEtherStatsHighUndersizePkts();
    itsEtherStatsHighOversizePkts          = GetEtherStatsHighOversizePkts();
    itsEtherStatsHighFragments             = GetEtherStatsHighFragments();
    itsEtherStatsHighJabbers               = GetEtherStatsHighJabbers();
    itsEtherStatsHighCollisions            = GetEtherStatsHighCollisions();
    itsEtherStatsHighPkts64Octets          = GetEtherStatsHighPkts64Octets();
    itsEtherStatsHighPkts65to127Octets     = GetEtherStatsHighPkts65to127Octets();
    itsEtherStatsHighPkts128to255Octets    = GetEtherStatsHighPkts128to255Octets();
    itsEtherStatsHighPkts256to511Octets    = GetEtherStatsHighPkts256to511Octets();
    itsEtherStatsHighPkts512to1023Octets   = GetEtherStatsHighPkts512to1023Octets();
    itsEtherStatsHighPkts1024to1518Octets  = GetEtherStatsHighPkts1024to1518Octets();

    // Mon Attributes  RFC 2021
    itsEtherStatsDroppedFrames         = GetEtherStatsDroppedFrames();

    itsEtherStatsHighDroppedFrames     = GetEtherStatsHighDroppedFrames();

    // Mon Attributes  IfTable Mib
    itsIfOutMulticastPkts              = GetIfOutMulticastPkts();
    itsIfOutBroadcastPkts              = GetIfOutBroadcastPkts();
    itsIfInUcastPkts                   = GetIfInUcastPkts();
    itsIfInDiscards                    = GetIfInDiscards();
    itsIfInErrors                      = GetIfInErrors();
    itsIfOutOctets                     = GetIfOutOctets();
    itsIfOutUcastPkts                  = GetIfOutUcastPkts();
    itsIfOutDiscards                   = GetIfOutDiscards();
    itsIfOutErrors                     = GetIfOutErrors();

    itsIfHighOutMulticastPkts          = GetIfHighOutMulticastPkts();
    itsIfHighOutBroadcastPkts          = GetIfHighOutBroadcastPkts();
    itsIfHighInUcastPkts               = GetIfHighInUcastPkts();
    itsIfHighInDiscards                = GetIfHighInDiscards();
    itsIfHighInErrors                  = GetIfHighInErrors();
    itsIfHighOutOctets                 = GetIfHighOutOctets();
    itsIfHighOutUcastPkts              = GetIfHighOutUcastPkts();
    itsIfHighOutDiscards               = GetIfHighOutDiscards();
    itsIfHighOutErrors                 = GetIfHighOutErrors();

    bool Done                          = GetIfPhysAddress(itsIfPhysAddressHigh, itsIfPhysAddressLow);
    itsIfMtu                           = GetIfMtu();

    // Cfg Attributes
    itsEnabled                         = GetEnabled();

    // Availability attributes.
    itsPortResetCount                  = GetPortResetCount();
    itsAllowPortMuxOverflowReset       = GetAllowPortMuxOverflowReset();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::RefreshSet()
{
    // Cfg Attributes
    SetEnabled(itsEnabled);

    // Availability attributes.
    SetAllowPortMuxOverflowReset(itsAllowPortMuxOverflowReset);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Mon Attributes  RFC 2819
    itsEtherStatsDropEvents            = 0;
    itsEtherStatsOctets                = 0;
    itsEtherStatsPkts                  = 0;
    itsEtherStatsBroadcastPkts         = 0;
    itsEtherStatsMulticastPkts         = 0;
    itsEtherStatsCRCAlignErrors        = 0;
    itsEtherStatsUndersizePkts         = 0;
    itsEtherStatsOversizePkts          = 0;
    itsEtherStatsFragments             = 0;
    itsEtherStatsJabbers               = 0;
    itsEtherStatsCollisions            = 0;
    itsEtherStatsPkts64Octets          = 0;
    itsEtherStatsPkts65to127Octets     = 0;
    itsEtherStatsPkts128to255Octets    = 0;
    itsEtherStatsPkts256to511Octets    = 0;
    itsEtherStatsPkts512to1023Octets   = 0;
    itsEtherStatsPkts1024to1518Octets  = 0;

    itsEtherStatsHighDropEvents            = 0;
    itsEtherStatsHighOctets                = 0;
    itsEtherStatsHighPkts                  = 0;
    itsEtherStatsHighBroadcastPkts         = 0;
    itsEtherStatsHighMulticastPkts         = 0;
    itsEtherStatsHighCRCAlignErrors        = 0;
    itsEtherStatsHighUndersizePkts         = 0;
    itsEtherStatsHighOversizePkts          = 0;
    itsEtherStatsHighFragments             = 0;
    itsEtherStatsHighJabbers               = 0;
    itsEtherStatsHighCollisions            = 0;
    itsEtherStatsHighPkts64Octets          = 0;
    itsEtherStatsHighPkts65to127Octets     = 0;
    itsEtherStatsHighPkts128to255Octets    = 0;
    itsEtherStatsHighPkts256to511Octets    = 0;
    itsEtherStatsHighPkts512to1023Octets   = 0;
    itsEtherStatsHighPkts1024to1518Octets  = 0;

    // Mon Attributes  RFC 2021
    itsEtherStatsDroppedFrames         = 0;
    itsEtherStatsHighDroppedFrames     = 0;

    // Mon Attributes  IfTable Mib
    itsIfOutMulticastPkts              = 0;
    itsIfOutBroadcastPkts              = 0;
    itsIfInUcastPkts                   = 0;
    itsIfInDiscards                    = 0;
    itsIfInErrors                      = 0;
    itsIfOutOctets                     = 0;
    itsIfOutUcastPkts                  = 0;
    itsIfOutDiscards                   = 0;
    itsIfOutErrors                     = 0;

    itsIfHighOutMulticastPkts          = 0;
    itsIfHighOutBroadcastPkts          = 0;
    itsIfHighInUcastPkts               = 0;
    itsIfHighInDiscards                = 0;
    itsIfHighInErrors                  = 0;
    itsIfHighOutOctets                 = 0;
    itsIfHighOutUcastPkts              = 0;
    itsIfHighOutDiscards               = 0;
    itsIfHighOutErrors                 = 0;

    itsIfPhysAddressHigh               = 0;
    itsIfPhysAddressLow                = 0;
    itsIfMtu                           = 0;

    // Cfg Attributes
    itsEnabled                         = false;

    // Availability attributes.
    itsPortResetCount                  = 0;
    itsAllowPortMuxOverflowReset       = true;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::SetEnabled(bool theEnable)
{
    itsEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RmonIf::GetEnabled() const
{
    return itsEnabled;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsDropEvents()
{
    return itsEtherStatsDropEvents;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsOctets()
{
    return itsEtherStatsOctets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts()
{
    return itsEtherStatsPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsBroadcastPkts()
{
    return itsEtherStatsBroadcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsMulticastPkts()
{
    return itsEtherStatsMulticastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsCRCAlignErrors()
{
    return itsEtherStatsCRCAlignErrors;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsUndersizePkts()
{
    return itsEtherStatsUndersizePkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsOversizePkts()
{
    return itsEtherStatsOversizePkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsFragments()
{
    return itsEtherStatsFragments;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsJabbers()
{
    return itsEtherStatsJabbers;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsCollisions()
{
    return itsEtherStatsCollisions;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts64Octets()
{
    return itsEtherStatsPkts64Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts65to127Octets()
{
    return itsEtherStatsPkts65to127Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts128to255Octets()
{
    return itsEtherStatsPkts128to255Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts256to511Octets()
{
    return itsEtherStatsPkts256to511Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts512to1023Octets()
{
    return itsEtherStatsPkts512to1023Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsPkts1024to1518Octets()
{
    return itsEtherStatsPkts1024to1518Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsDroppedFrames()
{
    return itsEtherStatsDroppedFrames;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutMulticastPkts()
{
    return itsIfOutMulticastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutBroadcastPkts()
{
    return itsIfOutBroadcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfInUcastPkts()
{
    return itsIfInUcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfInDiscards()
{
    return itsIfInDiscards;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfInErrors()
{
    return itsIfInErrors;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutOctets()
{
    return itsIfOutOctets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutUcastPkts()
{
    return itsIfOutUcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutDiscards()
{
    return itsIfOutDiscards;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfOutErrors()
{
    return itsIfOutErrors;
}


///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighDropEvents()
{
    return itsEtherStatsHighDropEvents;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighOctets()
{
    return itsEtherStatsHighOctets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts()
{
    return itsEtherStatsHighPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighBroadcastPkts()
{
    return itsEtherStatsHighBroadcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighMulticastPkts()
{
    return itsEtherStatsHighMulticastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighCRCAlignErrors()
{
    return itsEtherStatsHighCRCAlignErrors;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighUndersizePkts()
{
    return itsEtherStatsHighUndersizePkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighOversizePkts()
{
    return itsEtherStatsHighOversizePkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighFragments()
{
    return itsEtherStatsHighFragments;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighJabbers()
{
    return itsEtherStatsHighJabbers;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighCollisions()
{
    return itsEtherStatsHighCollisions;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts64Octets()
{
    return itsEtherStatsHighPkts64Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts65to127Octets()
{
    return itsEtherStatsHighPkts65to127Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts128to255Octets()
{
    return itsEtherStatsHighPkts128to255Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts256to511Octets()
{
    return itsEtherStatsHighPkts256to511Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts512to1023Octets()
{
    return itsEtherStatsHighPkts512to1023Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighPkts1024to1518Octets()
{
    return itsEtherStatsHighPkts1024to1518Octets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetEtherStatsHighDroppedFrames()
{
    return itsEtherStatsHighDroppedFrames;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutMulticastPkts()
{
    return itsIfHighOutMulticastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutBroadcastPkts()
{
    return itsIfHighOutBroadcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighInUcastPkts()
{
    return itsIfHighInUcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighInDiscards()
{
    return itsIfHighInDiscards;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighInErrors()
{
    return itsIfHighInErrors;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutOctets()
{
    return itsIfHighOutOctets;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutUcastPkts()
{
    return itsIfHighOutUcastPkts;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutDiscards()
{
    return itsIfHighOutDiscards;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfHighOutErrors()
{
    return itsIfHighOutErrors;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_RmonIf::GetIfPhysAddress(uint32 & theIfPhysAddressHigh, uint32 & theIfPhysAddressLow)
{
    bool foundIt = true;   // Can force false with debugger to simulate failure

    theIfPhysAddressHigh = itsIfPhysAddressHigh;
    theIfPhysAddressLow = itsIfPhysAddressLow;
    return foundIt;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetIfMtu()
{
    return itsIfMtu;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RmonIf::GetPortResetCount()
{
    return itsPortResetCount;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::SetAllowPortMuxOverflowReset(bool theReset)
{
    itsAllowPortMuxOverflowReset = theReset;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RmonIf::GetAllowPortMuxOverflowReset() const
{
    return itsAllowPortMuxOverflowReset;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_RmonIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsEtherStatsDropEvents;
    theStream << itsEtherStatsOctets;
    theStream << itsEtherStatsPkts;
    theStream << itsEtherStatsBroadcastPkts;
    theStream << itsEtherStatsMulticastPkts;
    theStream << itsEtherStatsCRCAlignErrors;
    theStream << itsEtherStatsUndersizePkts;
    theStream << itsEtherStatsOversizePkts;
    theStream << itsEtherStatsFragments;
    theStream << itsEtherStatsJabbers;
    theStream << itsEtherStatsCollisions;
    theStream << itsEtherStatsPkts64Octets;
    theStream << itsEtherStatsPkts65to127Octets;
    theStream << itsEtherStatsPkts128to255Octets;
    theStream << itsEtherStatsPkts256to511Octets;
    theStream << itsEtherStatsPkts512to1023Octets;
    theStream << itsEtherStatsPkts1024to1518Octets;
    theStream << itsEtherStatsDroppedFrames;

    theStream << itsIfOutMulticastPkts;
    theStream << itsIfOutBroadcastPkts;
    theStream << itsIfInUcastPkts;
    theStream << itsIfInDiscards;
    theStream << itsIfInErrors;
    theStream << itsIfOutOctets;
    theStream << itsIfOutUcastPkts;
    theStream << itsIfOutDiscards;
    theStream << itsIfOutErrors;
    theStream << itsIfPhysAddressHigh;
    theStream << itsIfPhysAddressLow;
    theStream << itsIfMtu;

    // For 64 Bits
    theStream << itsEtherStatsHighDropEvents;
    theStream << itsEtherStatsHighOctets;
    theStream << itsEtherStatsHighPkts;
    theStream << itsEtherStatsHighBroadcastPkts;
    theStream << itsEtherStatsHighMulticastPkts;
    theStream << itsEtherStatsHighCRCAlignErrors;
    theStream << itsEtherStatsHighUndersizePkts;
    theStream << itsEtherStatsHighOversizePkts;
    theStream << itsEtherStatsHighFragments;
    theStream << itsEtherStatsHighJabbers;
    theStream << itsEtherStatsHighCollisions;
    theStream << itsEtherStatsHighPkts64Octets;
    theStream << itsEtherStatsHighPkts65to127Octets;
    theStream << itsEtherStatsHighPkts128to255Octets;
    theStream << itsEtherStatsHighPkts256to511Octets;
    theStream << itsEtherStatsHighPkts512to1023Octets;
    theStream << itsEtherStatsHighPkts1024to1518Octets;
    theStream << itsEtherStatsHighDroppedFrames;

    theStream << itsIfHighOutMulticastPkts;
    theStream << itsIfHighOutBroadcastPkts;
    theStream << itsIfHighInUcastPkts;
    theStream << itsIfHighInDiscards;
    theStream << itsIfHighInErrors;
    theStream << itsIfHighOutOctets;
    theStream << itsIfHighOutUcastPkts;
    theStream << itsIfHighOutDiscards;
    theStream << itsIfHighOutErrors;


    // Configuration
    theStream << itsEnabled;

    // Availability attributes.
    theStream << itsPortResetCount;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_RmonIf::ReadObjectBinary(FC_Stream & theStream)
{
    
    // Monitoring
    theStream >> itsEtherStatsDropEvents;
    theStream >> itsEtherStatsOctets;
    theStream >> itsEtherStatsPkts;
    theStream >> itsEtherStatsBroadcastPkts;
    theStream >> itsEtherStatsMulticastPkts;
    theStream >> itsEtherStatsCRCAlignErrors;
    theStream >> itsEtherStatsUndersizePkts;
    theStream >> itsEtherStatsOversizePkts;
    theStream >> itsEtherStatsFragments;
    theStream >> itsEtherStatsJabbers;
    theStream >> itsEtherStatsCollisions;
    theStream >> itsEtherStatsPkts64Octets;
    theStream >> itsEtherStatsPkts65to127Octets;
    theStream >> itsEtherStatsPkts128to255Octets;
    theStream >> itsEtherStatsPkts256to511Octets;
    theStream >> itsEtherStatsPkts512to1023Octets;
    theStream >> itsEtherStatsPkts1024to1518Octets;
    theStream >> itsEtherStatsDroppedFrames;
    
    theStream >> itsIfOutMulticastPkts;
    theStream >> itsIfOutBroadcastPkts;
    theStream >> itsIfInUcastPkts;
    theStream >> itsIfInDiscards;
    theStream >> itsIfInErrors;
    theStream >> itsIfOutOctets;
    theStream >> itsIfOutUcastPkts;
    theStream >> itsIfOutDiscards;
    theStream >> itsIfOutErrors;
    theStream >> itsIfPhysAddressHigh;
    theStream >> itsIfPhysAddressLow;
    theStream >> itsIfMtu;

    // For 64 Bits
    theStream >> itsEtherStatsHighDropEvents;
    theStream >> itsEtherStatsHighOctets;
    theStream >> itsEtherStatsHighPkts;
    theStream >> itsEtherStatsHighBroadcastPkts;
    theStream >> itsEtherStatsHighMulticastPkts;
    theStream >> itsEtherStatsHighCRCAlignErrors;
    theStream >> itsEtherStatsHighUndersizePkts;
    theStream >> itsEtherStatsHighOversizePkts;
    theStream >> itsEtherStatsHighFragments;
    theStream >> itsEtherStatsHighJabbers;
    theStream >> itsEtherStatsHighCollisions;
    theStream >> itsEtherStatsHighPkts64Octets;
    theStream >> itsEtherStatsHighPkts65to127Octets;
    theStream >> itsEtherStatsHighPkts128to255Octets;
    theStream >> itsEtherStatsHighPkts256to511Octets;
    theStream >> itsEtherStatsHighPkts512to1023Octets;
    theStream >> itsEtherStatsHighPkts1024to1518Octets;
    theStream >> itsEtherStatsHighDroppedFrames;

    theStream >> itsIfHighOutMulticastPkts;
    theStream >> itsIfHighOutBroadcastPkts;
    theStream >> itsIfHighInUcastPkts;
    theStream >> itsIfHighInDiscards;
    theStream >> itsIfHighInErrors;
    theStream >> itsIfHighOutOctets;
    theStream >> itsIfHighOutUcastPkts;
    theStream >> itsIfHighOutDiscards;
    theStream >> itsIfHighOutErrors;

    // Configuration
    theStream >> itsEnabled;

    // Availability attributes.
    theStream >> itsPortResetCount;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_RmonIf::WriteObject(ostream & theStream)
{
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << FC_InsertVar(itsEtherStatsDropEvents);
    theStream << FC_InsertVar(itsEtherStatsOctets);
    theStream << FC_InsertVar(itsEtherStatsPkts);
    theStream << FC_InsertVar(itsEtherStatsBroadcastPkts);
    theStream << FC_InsertVar(itsEtherStatsMulticastPkts);
    theStream << FC_InsertVar(itsEtherStatsCRCAlignErrors);
    theStream << FC_InsertVar(itsEtherStatsUndersizePkts);
    theStream << FC_InsertVar(itsEtherStatsOversizePkts);
    theStream << FC_InsertVar(itsEtherStatsFragments);
    theStream << FC_InsertVar(itsEtherStatsJabbers);
    theStream << FC_InsertVar(itsEtherStatsCollisions);
    theStream << FC_InsertVar(itsEtherStatsPkts64Octets);
    theStream << FC_InsertVar(itsEtherStatsPkts65to127Octets);
    theStream << FC_InsertVar(itsEtherStatsPkts128to255Octets);
    theStream << FC_InsertVar(itsEtherStatsPkts256to511Octets);
    theStream << FC_InsertVar(itsEtherStatsPkts512to1023Octets);
    theStream << FC_InsertVar(itsEtherStatsPkts1024to1518Octets);
    theStream << FC_InsertVar(itsEtherStatsDroppedFrames);
        
    theStream << FC_InsertVar(itsIfOutMulticastPkts);
    theStream << FC_InsertVar(itsIfOutBroadcastPkts);
    theStream << FC_InsertVar(itsIfInUcastPkts);
    theStream << FC_InsertVar(itsIfInDiscards);
    theStream << FC_InsertVar(itsIfInErrors);
    theStream << FC_InsertVar(itsIfOutOctets);
    theStream << FC_InsertVar(itsIfOutUcastPkts);
    theStream << FC_InsertVar(itsIfOutDiscards);
    theStream << FC_InsertVar(itsIfOutErrors);
    theStream << FC_InsertVar(itsIfPhysAddressHigh);
    theStream << FC_InsertVar(itsIfPhysAddressLow);
    theStream << FC_InsertVar(itsIfMtu);

    // for 64 bits
    theStream << FC_InsertVar(itsEtherStatsHighDropEvents);
    theStream << FC_InsertVar(itsEtherStatsHighOctets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts);
    theStream << FC_InsertVar(itsEtherStatsHighBroadcastPkts);
    theStream << FC_InsertVar(itsEtherStatsHighMulticastPkts);
    theStream << FC_InsertVar(itsEtherStatsHighCRCAlignErrors);
    theStream << FC_InsertVar(itsEtherStatsHighUndersizePkts);
    theStream << FC_InsertVar(itsEtherStatsHighOversizePkts);
    theStream << FC_InsertVar(itsEtherStatsHighFragments);
    theStream << FC_InsertVar(itsEtherStatsHighJabbers);
    theStream << FC_InsertVar(itsEtherStatsHighCollisions);
    theStream << FC_InsertVar(itsEtherStatsHighPkts64Octets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts65to127Octets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts128to255Octets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts256to511Octets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts512to1023Octets);
    theStream << FC_InsertVar(itsEtherStatsHighPkts1024to1518Octets);
    theStream << FC_InsertVar(itsEtherStatsHighDroppedFrames);
        
    theStream << FC_InsertVar(itsIfHighOutMulticastPkts);
    theStream << FC_InsertVar(itsIfHighOutBroadcastPkts);
    theStream << FC_InsertVar(itsIfHighInUcastPkts);
    theStream << FC_InsertVar(itsIfHighInDiscards);
    theStream << FC_InsertVar(itsIfHighInErrors);
    theStream << FC_InsertVar(itsIfHighOutOctets);
    theStream << FC_InsertVar(itsIfHighOutUcastPkts);
    theStream << FC_InsertVar(itsIfHighOutDiscards);
    theStream << FC_InsertVar(itsIfHighOutErrors);

    // Configuration
    theStream << FC_InsertVar(itsEnabled);

    // Availability attributes.
    theStream << FC_InsertVar(itsPortResetCount);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_RmonIf::ReadObject(istream & theStream)
{

    // Monitoring
    theStream >> FC_ExtractVar(itsEtherStatsDropEvents);
    theStream >> FC_ExtractVar(itsEtherStatsOctets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts);
    theStream >> FC_ExtractVar(itsEtherStatsBroadcastPkts);
    theStream >> FC_ExtractVar(itsEtherStatsMulticastPkts);
    theStream >> FC_ExtractVar(itsEtherStatsCRCAlignErrors);
    theStream >> FC_ExtractVar(itsEtherStatsUndersizePkts);
    theStream >> FC_ExtractVar(itsEtherStatsOversizePkts);
    theStream >> FC_ExtractVar(itsEtherStatsFragments);
    theStream >> FC_ExtractVar(itsEtherStatsJabbers);
    theStream >> FC_ExtractVar(itsEtherStatsCollisions);
    theStream >> FC_ExtractVar(itsEtherStatsPkts64Octets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts65to127Octets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts128to255Octets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts256to511Octets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts512to1023Octets);
    theStream >> FC_ExtractVar(itsEtherStatsPkts1024to1518Octets);
    theStream >> FC_ExtractVar(itsEtherStatsDroppedFrames);
    
    theStream >> FC_ExtractVar(itsIfOutMulticastPkts);
    theStream >> FC_ExtractVar(itsIfOutBroadcastPkts);
    theStream >> FC_ExtractVar(itsIfInUcastPkts);
    theStream >> FC_ExtractVar(itsIfInDiscards);
    theStream >> FC_ExtractVar(itsIfInErrors);
    theStream >> FC_ExtractVar(itsIfOutOctets);
    theStream >> FC_ExtractVar(itsIfOutUcastPkts);
    theStream >> FC_ExtractVar(itsIfOutDiscards);
    theStream >> FC_ExtractVar(itsIfOutErrors);
    theStream >> FC_ExtractVar(itsIfPhysAddressHigh);
    theStream >> FC_ExtractVar(itsIfPhysAddressLow);
    theStream >> FC_ExtractVar(itsIfMtu);

    // Fro 64 bits
    theStream >> FC_ExtractVar(itsEtherStatsHighDropEvents);
    theStream >> FC_ExtractVar(itsEtherStatsHighOctets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts);
    theStream >> FC_ExtractVar(itsEtherStatsHighBroadcastPkts);
    theStream >> FC_ExtractVar(itsEtherStatsHighMulticastPkts);
    theStream >> FC_ExtractVar(itsEtherStatsHighCRCAlignErrors);
    theStream >> FC_ExtractVar(itsEtherStatsHighUndersizePkts);
    theStream >> FC_ExtractVar(itsEtherStatsHighOversizePkts);
    theStream >> FC_ExtractVar(itsEtherStatsHighFragments);
    theStream >> FC_ExtractVar(itsEtherStatsHighJabbers);
    theStream >> FC_ExtractVar(itsEtherStatsHighCollisions);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts64Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts65to127Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts128to255Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts256to511Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts512to1023Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighPkts1024to1518Octets);
    theStream >> FC_ExtractVar(itsEtherStatsHighDroppedFrames);
    
    theStream >> FC_ExtractVar(itsIfHighOutMulticastPkts);
    theStream >> FC_ExtractVar(itsIfHighOutBroadcastPkts);
    theStream >> FC_ExtractVar(itsIfHighInUcastPkts);
    theStream >> FC_ExtractVar(itsIfHighInDiscards);
    theStream >> FC_ExtractVar(itsIfHighInErrors);
    theStream >> FC_ExtractVar(itsIfHighOutOctets);
    theStream >> FC_ExtractVar(itsIfHighOutUcastPkts);
    theStream >> FC_ExtractVar(itsIfHighOutDiscards);
    theStream >> FC_ExtractVar(itsIfHighOutErrors);

    // Configuration
    theStream >> FC_ExtractVar(itsEnabled);

    // Availability attributes.
    theStream >> FC_ExtractVar(itsPortResetCount);

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Ethernet Rmon Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Enabled                                = " << DISPLAY_BOOL(itsEnabled)                   << "\n";
    theStream << "    MONITORING " << "\n";
    theStream << "      Rmon EtherStatsDropEvents              = " << itsEtherStatsDropEvents            << "\n";
    theStream << "      Rmon EtherStatsHighDropEvents          = " << itsEtherStatsHighDropEvents            << "\n";
    theStream << "      Rmon EtherStatsOctets                  = " << itsEtherStatsOctets                << "\n";
    theStream << "      Rmon EtherStatsHighOctets              = " << itsEtherStatsHighOctets                << "\n";
    theStream << "      Rmon EtherStatsPkts                    = " << itsEtherStatsPkts                  << "\n";
    theStream << "      Rmon EtherStatsHighPkts                = " << itsEtherStatsHighPkts                  << "\n";
    theStream << "      Rmon EtherStatsBroadcastPkts           = " << itsEtherStatsBroadcastPkts         << "\n";
    theStream << "      Rmon EtherStatsHighBroadcastPkts       = " << itsEtherStatsHighBroadcastPkts         << "\n";
    theStream << "      Rmon EtherStatsMulticastPkts           = " << itsEtherStatsMulticastPkts         << "\n";
    theStream << "      Rmon EtherStatsHighMulticastPkts       = " << itsEtherStatsHighMulticastPkts         << "\n";
    theStream << "      Rmon EtherStatsCRCAlignErrors          = " << itsEtherStatsCRCAlignErrors        << "\n";
    theStream << "      Rmon EtherStatsHighCRCAlignErrors      = " << itsEtherStatsHighCRCAlignErrors        << "\n";
    theStream << "      Rmon EtherStatsUndersizePkts           = " << itsEtherStatsUndersizePkts         << "\n";
    theStream << "      Rmon EtherStatsHighUndersizePkts       = " << itsEtherStatsHighUndersizePkts         << "\n";
    theStream << "      Rmon EtherStatsOversizePkts            = " << itsEtherStatsOversizePkts          << "\n";
    theStream << "      Rmon EtherStatsHighOversizePkts        = " << itsEtherStatsHighOversizePkts          << "\n";
    theStream << "      Rmon EtherStatsFragments               = " << itsEtherStatsFragments             << "\n";
    theStream << "      Rmon EtherStatsHighFragments           = " << itsEtherStatsHighFragments             << "\n";
    theStream << "      Rmon EtherStatsJabbers                 = " << itsEtherStatsJabbers               << "\n";
    theStream << "      Rmon EtherStatsHighJabbers             = " << itsEtherStatsHighJabbers               << "\n";
    theStream << "      Rmon EtherStatsCollisions              = " << itsEtherStatsCollisions            << "\n";
    theStream << "      Rmon EtherStatsHighCollisions          = " << itsEtherStatsHighCollisions            << "\n";
    theStream << "      Rmon EtherStatsPkts64Octets            = " << itsEtherStatsPkts64Octets          << "\n";
    theStream << "      Rmon EtherStatsHighPkts64Octets        = " << itsEtherStatsHighPkts64Octets          << "\n";
    theStream << "      Rmon EtherStatsPkts65to127Octets       = " << itsEtherStatsPkts65to127Octets     << "\n";
    theStream << "      Rmon EtherStatsHighPkts65to127Octets   = " << itsEtherStatsHighPkts65to127Octets     << "\n";
    theStream << "      Rmon EtherStatsPkts128to255Octets      = " << itsEtherStatsPkts128to255Octets    << "\n";
    theStream << "      Rmon EtherStatsHighPkts128to255Octets  = " << itsEtherStatsHighPkts128to255Octets    << "\n";
    theStream << "      Rmon EtherStatsPkts256to511Octets      = " << itsEtherStatsPkts256to511Octets    << "\n";
    theStream << "      Rmon EtherStatsHighPkts256to511Octets  = " << itsEtherStatsHighPkts256to511Octets    << "\n";
    theStream << "      Rmon EtherStatsPkts512to1023Octets     = " << itsEtherStatsPkts512to1023Octets   << "\n";
    theStream << "      Rmon EtherStatsHighPkts512to1023Octets = " << itsEtherStatsHighPkts512to1023Octets   << "\n";
    theStream << "      Rmon EtherStatsPkts1024to1518Octets    = " << itsEtherStatsPkts1024to1518Octets  << "\n";
    theStream << "      Rmon EtherStatsHighPkts1024to1518Octets= " << itsEtherStatsHighPkts1024to1518Octets  << "\n";
    theStream << "      Rmon EtherStatsDroppedFrames           = " << itsEtherStatsDroppedFrames         << "\n";
    theStream << "      Rmon EtherStatsHighDroppedFrames       = " << itsEtherStatsHighDroppedFrames         << "\n";
    theStream << "      Rmon IfOutMulticastPkts                = " << itsIfOutMulticastPkts              << "\n";
    theStream << "      Rmon IfHighOutMulticastPkts            = " << itsIfHighOutMulticastPkts              << "\n";
    theStream << "      Rmon IfOutBroadcastPkts                = " << itsIfOutBroadcastPkts              << "\n";
    theStream << "      Rmon IfHighOutBroadcastPkts            = " << itsIfHighOutBroadcastPkts              << "\n";
    theStream << "      Rmon IfInUcastPkts                     = " << itsIfInUcastPkts                  << "\n";
    theStream << "      Rmon IfHighInUcastPkts                 = " << itsIfHighInUcastPkts                  << "\n";
    theStream << "      Rmon IfInDiscards                      = " << itsIfInDiscards                    << "\n";
    theStream << "      Rmon IfHighInDiscards                  = " << itsIfHighInDiscards                    << "\n";
    theStream << "      Rmon IfInErrors                        = " << itsIfInErrors                      << "\n";
    theStream << "      Rmon IfHighInErrors                    = " << itsIfHighInErrors                      << "\n";
    theStream << "      Rmon IfOutOctets                       = " << itsIfOutOctets                     << "\n";
    theStream << "      Rmon IfHighOutOctets                   = " << itsIfHighOutOctets                     << "\n";
    theStream << "      Rmon IfOutUcastPkts                    = " << itsIfOutUcastPkts                  << "\n";
    theStream << "      Rmon IfHighOutUcastPkts                = " << itsIfHighOutUcastPkts                  << "\n";
    theStream << "      Rmon IfOutDiscards                     = " << itsIfOutDiscards                   << "\n";
    theStream << "      Rmon IfHighOutDiscards                 = " << itsIfHighOutDiscards                   << "\n";
    theStream << "      Rmon IfOutErrors                       = " << itsIfOutErrors                     << "\n";
    theStream << "      Rmon IfHighOutErrors                   = " << itsIfHighOutErrors                     << "\n";
    theStream << "      Rmon IfPhysAddressHigh                 = " << itsIfPhysAddressHigh               << "\n";
    theStream << "      Rmon IfPhysAddressLow                  = " << itsIfPhysAddressLow                << "\n";
    theStream << "      Rmon IfMtu                             = " << itsIfMtu                               << "\n";
    theStream << "      Rmon PortResetCount                    = " << itsPortResetCount                  << endl;
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RmonIf::Set(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "enabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "resetport") == 0)
    {
        if (strcmp(argv[1], "force") == 0)
        {
            ResetPortMux();
        }
        else if (strcmp(argv[1], "soft") == 0)
        {
            // Check for channel mux overflow
            if(GetPortMuxStuckStatus())
            {
                // Reset the channel
                ResetPortMux();
            }
        }
        else if (strcmp(argv[1], "stop") == 0)
        {
            // Stop the mux rest algorithm
            SetAllowPortMuxOverflowReset(false);
        }
        else if (strcmp(argv[1], "resume") == 0)
        {
            // Stop the mux rest algorithm
            SetAllowPortMuxOverflowReset(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    enabled            <on|off>" << endl;
        fc_cout << "    resetport          <force|soft|stop|resume>" << endl;
        fc_cout << "    Usage:             " << endl;
        fc_cout << "                       force  = do not check for mux overflow/stuck status" << endl;
        fc_cout << "                       soft   = check for mux overflow/stuck status" << endl;
        fc_cout << "                       stop   = Stop the mux rest algorithm - debug only!!!" << endl;
        fc_cout << "                       resume = resume the mux rest algorithm - debug only!!!" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RmonIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if (argc == 2 && strcmp(argv[0], "drop") == 0)
    {
        itsEtherStatsDropEvents = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "octets") == 0)
    {
        itsEtherStatsOctets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "pkts") == 0)
    {
        itsEtherStatsPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "broadcast") == 0)
    {
        itsEtherStatsBroadcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "multicast") == 0)
    {
        itsEtherStatsMulticastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "crc") == 0)
    {
        itsEtherStatsCRCAlignErrors = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "undersize") == 0)
    {
        itsEtherStatsUndersizePkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "oversize") == 0)
    {
        itsEtherStatsOversizePkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "fragments") == 0)
    {
        itsEtherStatsFragments = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "jabbers") == 0)
    {
        itsEtherStatsJabbers = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "collisions") == 0)
    {
        itsEtherStatsCollisions = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "64") == 0)
    {
        itsEtherStatsPkts64Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "65-127") == 0)
    {
        itsEtherStatsPkts65to127Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "128-255") == 0)
    {
        itsEtherStatsPkts128to255Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "256-511") == 0)
    {
        itsEtherStatsPkts256to511Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "512-1023") == 0)
    {
        itsEtherStatsPkts512to1023Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "1024-1518") == 0)
    {
        itsEtherStatsPkts1024to1518Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "dropframes") == 0)
    {
        itsEtherStatsDroppedFrames = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outmulticast") == 0)
    {
        itsIfOutMulticastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outbroadcast") == 0)
    {
        itsIfOutBroadcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "inucast") == 0)
    {
        itsIfInUcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "indiscards") == 0)
    {
        itsIfInDiscards = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "inerrors") == 0)
    {
        itsIfInErrors = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outoctets") == 0)
    {
        itsIfOutOctets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outucast") == 0)
    {
        itsIfOutUcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outdiscards") == 0)
    {
        itsIfOutDiscards = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "outerrors") == 0)
    {
        itsIfOutErrors = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "physadrhi") == 0)
    {
        itsIfPhysAddressHigh = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "physadrlo") == 0)
    {
        itsIfPhysAddressLow = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "mtu") == 0)
    {
        itsIfMtu = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIdrop") == 0)
    {
        itsEtherStatsHighDropEvents = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoctets") == 0)
    {
        itsEtherStatsHighOctets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIpkts") == 0)
    {
        itsEtherStatsHighPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIbroadcast") == 0)
    {
        itsEtherStatsHighBroadcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HImulticast") == 0)
    {
        itsEtherStatsHighMulticastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIcrc") == 0)
    {
        itsEtherStatsHighCRCAlignErrors = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIundersize") == 0)
    {
        itsEtherStatsHighUndersizePkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoversize") == 0)
    {
        itsEtherStatsHighOversizePkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIfragments") == 0)
    {
        itsEtherStatsHighFragments = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIjabbers") == 0)
    {
        itsEtherStatsHighJabbers = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIcollisions") == 0)
    {
        itsEtherStatsHighCollisions = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI64") == 0)
    {
        itsEtherStatsHighPkts64Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI65-127") == 0)
    {
        itsEtherStatsHighPkts65to127Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI128-255") == 0)
    {
        itsEtherStatsHighPkts128to255Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI256-511") == 0)
    {
        itsEtherStatsHighPkts256to511Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI512-1023") == 0)
    {
        itsEtherStatsHighPkts512to1023Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HI1024-1518") == 0)
    {
        itsEtherStatsHighPkts1024to1518Octets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIdropframes") == 0)
    {
        itsEtherStatsHighDroppedFrames = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoutmulticast") == 0)
    {
        itsIfHighOutMulticastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoutbroadcast") == 0)
    {
        itsIfHighOutBroadcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIinucast") == 0)
    {
        itsIfHighInUcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIindiscards") == 0)
    {
        itsIfHighInDiscards = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIinerrors") == 0)
    {
        itsIfHighInErrors = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoutoctets") == 0)
    {
        itsIfHighOutOctets = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoutucast") == 0)
    {
        itsIfHighOutUcastPkts = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIoutdiscards") == 0)
    {
        itsIfHighOutDiscards = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "HIouterrors") == 0)
    {
        itsIfHighOutErrors = strtoul(argv[1], NULL, 0);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    drop            <count>\n"
                   "    HIdrop          <count>\n"
                   "    octets          <count>\n"
                   "    HIoctets        <count>\n"
                   "    pkts            <count>\n"
                   "    HIpkts          <count>\n"
                   "    broadcast       <count>\n"
                   "    HIbroadcast     <count>\n"
                   "    multicast       <count>\n"
                   "    HImulticast     <count>\n"
                   "    crc             <count>\n"
                   "    HIcrc           <count>\n"
                   "    undersize       <count>\n"
                   "    HIundersize     <count>\n"
                   "    oversize        <count>\n"
                   "    HIoversize      <count>\n"
                   "    fragments       <count>\n"
                   "    HIfragments     <count>\n"
                   "    jabbers         <count>\n"
                   "    HIjabbers       <count>\n"
                   "    collisions      <count>\n"
                   "    HIcollisions    <count>\n"
                   "    64              <count>\n"
                   "    HI64            <count>\n"
                   "    65-127          <count>\n"
                   "    HI65-127        <count>\n"
                   "    128-255         <count>\n"
                   "    HI128-255       <count>\n"
                   "    256-511         <count>\n"
                   "    HI256-511       <count>\n"
                   "    512-1023        <count>\n"
                   "    HI512-1023      <count>\n"
                   "    1024-1518       <count>\n"
                   "    HI1024-1518     <count>\n"
                   "    dropframes      <count>\n"
                   "    HIdropframes    <count>\n"
                   "    outmulticast    <count>\n"
                   "    HIoutmulticast  <count>\n"
                   "    outbroadcast    <count>\n"
                   "    HIoutbroadcast  <count>\n"
                   "    inucast         <count>\n"
                   "    HIinucast       <count>\n"
                   "    indiscards      <count>\n"
                   "    HIindiscards    <count>\n"
                   "    inerrors        <count>\n"
                   "    HIinerrors      <count>\n"
                   "    outoctets       <count>\n"
                   "    HIoutoctets     <count>\n"
                   "    outucast        <count>\n"
                   "    HIoutucast      <count>\n"
                   "    outdiscards     <count>\n"
                   "    HIoutdiscards   <count>\n"
                   "    outerrors       <count>\n"
                   "    HIouterrors     <count>\n"
                   "    physadrhi       <addr>\n"
                   "    physadrlo       <addr>\n"
                   "    mtu             <size>\n"  << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RmonIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
