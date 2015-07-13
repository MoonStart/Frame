/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - July 2003
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for the Crossconnect (TSI) hardware
 MODIFIED :  
--------------------------------------------------------------------------*/

#ifndef TSPII_XCIF_H
#define TSPII_XCIF_H

#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"
#include <Devices/DEV_XcTbl.h>

class CT_FAC_StsMap;

// Crossconnect Types Supported.
// PLEASE KEEP THIS IN SYNCH WITH OTHER DEFINES BELOW
enum TSPII_XcType
{
    TSPII_XC_TYPE_LAMBDA,   // Lambda connections
    TSPII_XC_TYPE_OC3M,     // OC3M port LAPS
    TSPII_XC_TYPE_OC12M,    // OC3M port LAPS
    TSPII_XC_TYPE_OC48M,    // OC3M port LAPS
    TSPII_XC_TYPE_OC3U,     // OC3U port UPSR
    TSPII_XC_TYPE_OC12U,    // OC3U port UPSR
    TSPII_XC_TYPE_OC48U,    // OC3U port UPSR
    TSPII_XC_TYPE_OCHM,     // OCH-DPring 
    TSPII_XC_TYPE_STS3T,    // STS3 Transparent 
    TSPII_XC_TYPE_STS12T,   // STS12 Transparent 
    TSPII_XC_TYPE_STS48T,   // STS48 Transparent
    TSPII_XC_TYPE_STS1,     // STS1 
    TSPII_XC_TYPE_STS3C,    // STS3 
    TSPII_XC_TYPE_STS12C,   // STS12 
    TSPII_XC_TYPE_STS48C,   // STS48 
    TSPII_XC_TYPE_STS192C,  // STS192C 
    TSPII_XC_TYPE_STS1C22V, // 22 Concatenated STS1 for GBE 
    TSPII_XC_TYPE_STSNV,    // N  Concatenated STS1 for Data Rate
    TSPII_XC_TYPE_OPTD1M,   // Optical Data port LAPS uses STS1
    TSPII_XC_TYPE_STSNV3,   // N  Concatenated STS3C for Data Rate
    TSPII_XC_TYPE_OPTD3M,   // Optical Data port LAPS uses STS3C
    TSPII_XC_TYPE_OC192M,   // OC192M port LAPS   
    TSPII_XC_TYPE_STS192T,  // STS192 Transparent
    TSPII_XC_TYPE_ODU0,     // ODU0
    TSPII_XC_TYPE_ODU1,     // ODU1
    TSPII_XC_TYPE_ODU2,     // ODU2
    TSPII_XC_TYPE_ODU2E,    // ODU2E
    TSPII_XC_TYPE_ODUF,     // ODUflex
    TSPII_XC_TYPE_ODU1F,     // ODU1F
    TSPII_XC_TYPE_ODU1E,     // ODU1E
    TSPII_XC_TYPE_ODU3,     // ODU3
    TSPII_XC_TYPE_ODU4,     // ODU4
    TSPII_XC_TYPE_UNKNOWN
};

// Macro to print the Xc type as a string
// PLEASE KEEP THIS IN SYNCH WITH THE GET MACRO BELOW
#define TSPII_XC_TYPE_DISPLAY(type) \
    ((type) == TSPII_XC_TYPE_LAMBDA      ? "LAMBDA"   : \
     (type) == TSPII_XC_TYPE_OC3M        ? "OC3M"     : \
     (type) == TSPII_XC_TYPE_OC12M       ? "OC12M"    : \
     (type) == TSPII_XC_TYPE_OC48M       ? "OC48M"    : \
     (type) == TSPII_XC_TYPE_OC3U        ? "OC3U"     : \
     (type) == TSPII_XC_TYPE_OC12U       ? "OC12U"    : \
     (type) == TSPII_XC_TYPE_OC48U       ? "OC48U"    : \
     (type) == TSPII_XC_TYPE_OCHM        ? "OCHM"     : \
     (type) == TSPII_XC_TYPE_STS3T       ? "STS3T"    : \
     (type) == TSPII_XC_TYPE_STS12T      ? "STS12T"   : \
     (type) == TSPII_XC_TYPE_STS48T      ? "STS48T"   : \
     (type) == TSPII_XC_TYPE_STS1        ? "STS1"     : \
     (type) == TSPII_XC_TYPE_STS3C       ? "STS3C"    : \
     (type) == TSPII_XC_TYPE_STS12C      ? "STS12C"   : \
     (type) == TSPII_XC_TYPE_STS48C      ? "STS48C"   : \
     (type) == TSPII_XC_TYPE_STS192C     ? "STS192C"  : \
     (type) == TSPII_XC_TYPE_STS1C22V    ? "STS1C22V" : \
     (type) == TSPII_XC_TYPE_STSNV       ? "STSNV"    : \
     (type) == TSPII_XC_TYPE_OPTD1M      ? "OPTD1M"   : \
     (type) == TSPII_XC_TYPE_STSNV3      ? "STSNV3"   : \
     (type) == TSPII_XC_TYPE_OPTD3M      ? "OPTD3M"   : \
     (type) == TSPII_XC_TYPE_OC192M      ? "OC192M"   : \
     (type) == TSPII_XC_TYPE_STS192T     ? "STS192T"  : \
     (type) == TSPII_XC_TYPE_ODU0        ? "ODU0"     : \
     (type) == TSPII_XC_TYPE_ODU1        ? "ODU1"     : \
     (type) == TSPII_XC_TYPE_ODU2        ? "ODU2"     : \
     (type) == TSPII_XC_TYPE_ODU2E       ? "ODU2E"    : \
     (type) == TSPII_XC_TYPE_ODU3        ? "ODU3"     : \
     (type) == TSPII_XC_TYPE_ODU4        ? "ODU4"     : \
     (type) == TSPII_XC_TYPE_ODUF        ? "ODUFlex"  :"?")
             
// Macro to convert input string into Xc Type
// PLEASE KEEP THIS IN SYNCH WITH THE DISPLAY MACRO ABOVE
#define TSPII_XC_TYPE_GET(type) \
    ((strcmp(type, "lambda") == 0)   ? TSPII_XC_TYPE_LAMBDA : \
     (strcmp(type, "oc3m") == 0)     ? TSPII_XC_TYPE_OC3M : \
     (strcmp(type, "oc12m") == 0)    ? TSPII_XC_TYPE_OC12M : \
     (strcmp(type, "oc48m") == 0)    ? TSPII_XC_TYPE_OC48M : \
     (strcmp(type, "oc3u") == 0)     ? TSPII_XC_TYPE_OC3U : \
     (strcmp(type, "oc12u") == 0)    ? TSPII_XC_TYPE_OC12U : \
     (strcmp(type, "oc48u") == 0)    ? TSPII_XC_TYPE_OC48U : \
     (strcmp(type, "ochm") == 0)     ? TSPII_XC_TYPE_OCHM : \
     (strcmp(type, "sts3t") == 0)    ? TSPII_XC_TYPE_STS3T : \
     (strcmp(type, "sts12t") == 0)   ? TSPII_XC_TYPE_STS12T : \
     (strcmp(type, "sts48t") == 0)   ? TSPII_XC_TYPE_STS48T : \
     (strcmp(type, "sts1") == 0)     ? TSPII_XC_TYPE_STS1 : \
     (strcmp(type, "sts3c") == 0)    ? TSPII_XC_TYPE_STS3C : \
     (strcmp(type, "sts12c") == 0)   ? TSPII_XC_TYPE_STS12C : \
     (strcmp(type, "sts48c") == 0)   ? TSPII_XC_TYPE_STS48C : \
     (strcmp(type, "sts192c") == 0)  ? TSPII_XC_TYPE_STS192C : \
     (strcmp(type, "sts1c22v") == 0) ? TSPII_XC_TYPE_STS1C22V : \
     (strcmp(type, "stsnv") == 0)    ? TSPII_XC_TYPE_STSNV : \
     (strcmp(type, "stsnv3") == 0)   ? TSPII_XC_TYPE_STSNV3 : \
     (strcmp(type, "optd1m") == 0)   ? TSPII_XC_TYPE_OPTD1M : \
     (strcmp(type, "optd3m") == 0)   ? TSPII_XC_TYPE_OPTD3M : \
     (strcmp(type, "oc192m") == 0)   ? TSPII_XC_TYPE_OC192M : \
     (strcmp(type, "sts192t") == 0)  ? TSPII_XC_TYPE_STS192T : \
     (strcmp(type, "odu0") == 0)     ? TSPII_XC_TYPE_ODU0 : \
     (strcmp(type, "odu1") == 0)     ? TSPII_XC_TYPE_ODU1 : \
     (strcmp(type, "odu2") == 0)     ? TSPII_XC_TYPE_ODU2 : \
     (strcmp(type, "odu2e") == 0)    ? TSPII_XC_TYPE_ODU2E : \
     (strcmp(type, "oduflex") == 0)  ? TSPII_XC_TYPE_ODUF : TSPII_XC_TYPE_UNKNOWN)
     
// This class describes one uni-directional crossconnect
class TSPII_XcRecord
{
public:
    TSPII_XcType  Type;       // Crossconnect type
    uint16        InPort;     // Input Port - "0" based
    uint16        InTslot;    // Input Timeslot - "0" based
    uint16        OutPort;    // Output Port - "0" based
    uint16        OutTslot;   // Output Timeslot - "0" based

    TSPII_XcRecord()
    {
        Type=TSPII_XC_TYPE_UNKNOWN; InPort=0; InTslot=0; OutPort=0; OutTslot=0;
    }

    void Clear()
    {
        Type=TSPII_XC_TYPE_UNKNOWN; InPort=0; InTslot=0; OutPort=0; OutTslot=0;
    }

    void operator=(const TSPII_XcRecord &right)
    {
        this->Type     = right.Type;
        this->InPort   = right.InPort;
        this->InTslot  = right.InTslot;
        this->OutPort  = right.OutPort;
        this->OutTslot = right.OutTslot;
    }

    bool operator==( const TSPII_XcRecord &right) const
    {
        if((this->Type     == right.Type) &&
           (this->InPort   == right.InPort) &&
           (this->InTslot  == right.InTslot) &&
           (this->OutPort  == right.OutPort) &&
           (this->OutTslot == right.OutTslot))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class TSPII_XcIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_XcIf(bool theDefault = false, 
                                                 uint16 theNumPorts = 0,
                                                 uint16 theNumTslotsPerPort = 0);
    virtual                           ~TSPII_XcIf();
    virtual void                      Reset();
    virtual void                      UpdateValues();
    virtual void                      HwInit();
    
    // -----------------------------------------------------------------------------------
    // Mon Interfaces
    // -----------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
                                      // Add a single connection
    virtual void                      AddXconn(const TSPII_XcRecord & theXconn);

                                      // Add connection for ODU mux
    virtual void                      AddMux(uint16 highOdu, uint16 lowOdu, uint16* tribslot);

                                      // Delete a single connection
    virtual void                      DeleteXconn(const TSPII_XcRecord & theXconn);

                                      // Delete all the connections
    virtual void                      DeleteAllXconns();

                                      // Write the Adds and Deletes to hardware
    virtual void                      CommitXconns();

                                      // Get the committed xcons
    virtual const vector<TSPII_XcRecord> & GetCommitXconns();

                                      // Get the list of Output connections given an Input
    virtual bool                      GetXconnsFromInput(uint16 theInPort, uint16 theInTslot,
                                                         vector<TSPII_XcRecord> & theXconns);

                                      // Get the Input connection given the Output
    virtual bool                      GetXconnFromOutput(uint16 theOutPort, uint16 theOutTslot, 
                                                         TSPII_XcRecord & theXconn);

    virtual bool                      GetXconnListFromOutput(uint16 theOutPort, uint16 theOutTslot, 
                                                         vector<TSPII_XcRecord> & theXconns);
    
                                      // Check if Input Port is source for any connections
    virtual bool                      IsInputPortConnected(uint16 theInPort, bool autoDisconnect=false);

                                      // Check if Output Port is destination for any connections
    virtual bool                      IsOutputPortConnected(uint16 theOutPort, bool autoDisconnect=false);

                                      // XC Hardware has changed - resync
    virtual void                      HwConfigChanged(bool theIsSwitchModeNew);
        
                                      // Get ptr to XC table (for performance improvement on specific cards)
    virtual DEV_XcTbl*                GetXcTbl();
    
                                      // Setup the internal Xconns that are driven off of Port enables
    virtual bool                      AddPortSonetXconns(uint16 thePort);

                                      // Delete the internal Xconn that are driven off of the Port disables
    virtual bool                      DeletePortSonetXconns(uint16 thePort);
    
                                      // Convert XC port number to TSPII port number
    virtual uint16                    TsPortToTspiiPort(uint16 theTsPort);
     
                                      // Convert TSPII port number to XC port number
    virtual uint16                    TspiiPortToTsPort(uint16 theTspiiPort);

                                      // Convert XC port number to TSPII port number for Mux only
    virtual uint16                    TsPortToTspiiPortMux(uint16 theTsPort);
     
                                      // Convert TSPII port number to XC port number for Mux only
    virtual uint16                    TspiiPortToTsPortMux(uint16 theTspiiPort);
                       
                                      // Set AutoFallback status
    virtual void                      SetAutoFallback( bool theIsAutoFallback ) { }

                                      // Get Point C Ingress Allocation map
    virtual CT_FAC_StsMap             GetPointCIngressAlloc();

                                      // Get Point C Egress Allocation map
    virtual CT_FAC_StsMap             GetPointCEgressAlloc();

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);
    virtual bool                      DisplayTables(int argc, char ** argv);

protected:

    void                    RefreshGet();
    void                    RefreshSet();

    // Monitoring attributes
    
    // Configuration attributes
    uint16                  itsNumPorts;
    uint16                  itsNumTslotsPerPort;
    vector<TSPII_XcRecord> & itsCommitted;      // Reference to the HW committed list
    vector<TSPII_XcRecord>  itsDummyBuf;
};

#endif // TSPII_XCIF_H
