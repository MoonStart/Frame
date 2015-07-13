#ifndef _TSPII_RMONIF_H
#define _TSPII_RMONIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - October 2005
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Ethernet RMON statistics layer
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"

class TSPII_RmonIf : public TSPII_BaseIf
{

public:
    
    /* Constructor */           TSPII_RmonIf(bool theDefault = false); 
    virtual                     ~TSPII_RmonIf();
    virtual void                Reset();

    // -----------------------------------------------------------------------------------
    // Optical Mon Interfaces RFC 2819
    // -----------------------------------------------------------------------------------   
    virtual uint32              GetEtherStatsDropEvents();
    virtual uint32              GetEtherStatsOctets();
    virtual uint32              GetEtherStatsPkts();
    virtual uint32              GetEtherStatsBroadcastPkts();
    virtual uint32              GetEtherStatsMulticastPkts();
    virtual uint32              GetEtherStatsCRCAlignErrors();
    virtual uint32              GetEtherStatsUndersizePkts();
    virtual uint32              GetEtherStatsOversizePkts();
    virtual uint32              GetEtherStatsFragments();
    virtual uint32              GetEtherStatsJabbers();
    virtual uint32              GetEtherStatsCollisions();
    virtual uint32              GetEtherStatsPkts64Octets();
    virtual uint32              GetEtherStatsPkts65to127Octets();
    virtual uint32              GetEtherStatsPkts128to255Octets();
    virtual uint32              GetEtherStatsPkts256to511Octets();
    virtual uint32              GetEtherStatsPkts512to1023Octets();
    virtual uint32              GetEtherStatsPkts1024to1518Octets();
    // Add support for 64 bit counters
    virtual uint32              GetEtherStatsHighDropEvents();
    virtual uint32              GetEtherStatsHighOctets();
    virtual uint32              GetEtherStatsHighPkts();
    virtual uint32              GetEtherStatsHighBroadcastPkts();
    virtual uint32              GetEtherStatsHighMulticastPkts();
    virtual uint32              GetEtherStatsHighCRCAlignErrors();
    virtual uint32              GetEtherStatsHighUndersizePkts();
    virtual uint32              GetEtherStatsHighOversizePkts();
    virtual uint32              GetEtherStatsHighFragments();
    virtual uint32              GetEtherStatsHighJabbers();
    virtual uint32              GetEtherStatsHighCollisions();
    virtual uint32              GetEtherStatsHighPkts64Octets();
    virtual uint32              GetEtherStatsHighPkts65to127Octets();
    virtual uint32              GetEtherStatsHighPkts128to255Octets();
    virtual uint32              GetEtherStatsHighPkts256to511Octets();
    virtual uint32              GetEtherStatsHighPkts512to1023Octets();
    virtual uint32              GetEtherStatsHighPkts1024to1518Octets();


    // -----------------------------------------------------------------------------------
    // Optical Mon Interfaces RFC 2021
    // -----------------------------------------------------------------------------------   
    virtual uint32              GetEtherStatsDroppedFrames();
    // Add support for 64 bit counters
    virtual uint32              GetEtherStatsHighDroppedFrames();

    // -----------------------------------------------------------------------------------
    // Optical Mon Interfaces IfTable Mib
    // -----------------------------------------------------------------------------------   
    virtual uint32              GetIfOutMulticastPkts();
    virtual uint32              GetIfOutBroadcastPkts();
    virtual uint32              GetIfInUcastPkts();
    virtual uint32              GetIfInDiscards();
    virtual uint32              GetIfInErrors();
    virtual uint32              GetIfOutOctets();
    virtual uint32              GetIfOutUcastPkts();
    virtual uint32              GetIfOutDiscards();
    virtual uint32              GetIfOutErrors();
    // Add support for 64 bit counters
    virtual uint32              GetIfHighOutMulticastPkts();
    virtual uint32              GetIfHighOutBroadcastPkts();
    virtual uint32              GetIfHighInUcastPkts();
    virtual uint32              GetIfHighInDiscards();
    virtual uint32              GetIfHighInErrors();
    virtual uint32              GetIfHighOutOctets();
    virtual uint32              GetIfHighOutUcastPkts();
    virtual uint32              GetIfHighOutDiscards();
    virtual uint32              GetIfHighOutErrors();

    virtual bool                GetIfPhysAddress(uint32 & theIfPhysAddressHigh, uint32 & theIfPhysAddressLow);
    virtual uint32              GetIfMtu();

    virtual void                registerEventHandlers(){};

    // -----------------------------------------------------------------------------------
    // Optical Config Interfaces
    // -----------------------------------------------------------------------------------

    // Enable or Disable RMON on this interface
    virtual void                      SetEnabled(bool theEnable);
    virtual bool                      GetEnabled() const;

    // -----------------------------------------------------------------------------------
    // Availability Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool                GetPortMuxStuckStatus(){return false;};
    virtual void                ResetPortMux(){};
    virtual uint32              GetPortResetCount();
    virtual void                SetAllowPortMuxOverflowReset(bool theReset);
    virtual bool                GetAllowPortMuxOverflowReset() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &         WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &         ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &         WriteObject(ostream & theStream);
    virtual istream   &         ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                Display(FC_Stream & theStream);
    virtual void                Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                Set(int argc, char ** argv);
    virtual bool                Simul(int argc, char ** argv);

protected:

    void                RefreshGet();
    void                RefreshSet();

    // Monitoring attributes  RFC 2819
    uint32              itsEtherStatsDropEvents;
    uint32              itsEtherStatsOctets;
    uint32              itsEtherStatsPkts;
    uint32              itsEtherStatsBroadcastPkts;
    uint32              itsEtherStatsMulticastPkts;
    uint32              itsEtherStatsCRCAlignErrors;
    uint32              itsEtherStatsUndersizePkts;
    uint32              itsEtherStatsOversizePkts;
    uint32              itsEtherStatsFragments;
    uint32              itsEtherStatsJabbers;
    uint32              itsEtherStatsCollisions;
    uint32              itsEtherStatsPkts64Octets;
    uint32              itsEtherStatsPkts65to127Octets;
    uint32              itsEtherStatsPkts128to255Octets;
    uint32              itsEtherStatsPkts256to511Octets;
    uint32              itsEtherStatsPkts512to1023Octets;
    uint32              itsEtherStatsPkts1024to1518Octets;

    // Add support for 64 bit counters
    uint32              itsEtherStatsHighDropEvents;
    uint32              itsEtherStatsHighOctets;
    uint32              itsEtherStatsHighPkts;
    uint32              itsEtherStatsHighBroadcastPkts;
    uint32              itsEtherStatsHighMulticastPkts;
    uint32              itsEtherStatsHighCRCAlignErrors;
    uint32              itsEtherStatsHighUndersizePkts;
    uint32              itsEtherStatsHighOversizePkts;
    uint32              itsEtherStatsHighFragments;
    uint32              itsEtherStatsHighJabbers;
    uint32              itsEtherStatsHighCollisions;
    uint32              itsEtherStatsHighPkts64Octets;
    uint32              itsEtherStatsHighPkts65to127Octets;
    uint32              itsEtherStatsHighPkts128to255Octets;
    uint32              itsEtherStatsHighPkts256to511Octets;
    uint32              itsEtherStatsHighPkts512to1023Octets;
    uint32              itsEtherStatsHighPkts1024to1518Octets;

    // Monitoring attributes  RFC 2021
    uint32              itsEtherStatsDroppedFrames;
    // Add support for 64 bit counters
    uint32              itsEtherStatsHighDroppedFrames;

    // Monitoring attributes IfTable Mib
    uint32              itsIfOutMulticastPkts;
    uint32              itsIfOutBroadcastPkts;
    uint32              itsIfInUcastPkts;
    uint32              itsIfInDiscards;
    uint32              itsIfInErrors;
    uint32              itsIfOutOctets;
    uint32              itsIfOutUcastPkts;
    uint32              itsIfOutDiscards;
    uint32              itsIfOutErrors;
    // Add support for 64 bit counters
    uint32              itsIfHighOutMulticastPkts;
    uint32              itsIfHighOutBroadcastPkts;
    uint32              itsIfHighInUcastPkts;
    uint32              itsIfHighInDiscards;
    uint32              itsIfHighInErrors;
    uint32              itsIfHighOutOctets;
    uint32              itsIfHighOutUcastPkts;
    uint32              itsIfHighOutDiscards;
    uint32              itsIfHighOutErrors;

    uint32              itsIfPhysAddressHigh;
    uint32              itsIfPhysAddressLow;
    uint32              itsIfMtu;

    // Configuration attributes
    bool                  itsEnabled;

    // Availability attributes.
    uint32              itsPortResetCount;
    bool                itsAllowPortMuxOverflowReset;

    // Debug attributes
};
#endif // _TSPII_RMONIF_H
