/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Mark Nash - Sept 2006
 DESCRIPTION:Definition of the class TSPII_DrtrIf - Models the Generic 
             Framing Procedure termination entity.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_DrtrIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_DrtrIf::TSPII_DrtrIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DrtrIf::~TSPII_DrtrIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::RefreshGet()
{ 
    // Monitor attributes
    itsLevel1_RouterState       = GetLevel1_RouterState();
    itsLevel2_RouterState       = GetLevel2_RouterState();
    itsSequenceNumber           = GetSequenceNumber();

    itsRejectedAdjancency       = GetRejectedAdjancency(); 
    itsAreaAddressMismatch      = GetAreaAddressMismatch(); 
    itsMaxAreaAddressMismatch   = GetMaxAreaAddressMismatch(); 
    itsL1DatabaseOverload       = GetL1DatabaseOverload(); 
    itsL2DatabaseOverload       = GetL2DatabaseOverload();

    itsResolutionFailureCount   = GetResolutionFailureCount();
    itsDefectsChanged           = GetDefectsChanged();

    // Configuration attributes
    itsTIDID                    = GetTIDID();     
    itsRouterID                 = GetRouterID();
    itsCommandSequence          = GetCommandSequence();
    itsDCCRouterEnabled         = GetDCCRouterEnabled();
    itsProvisioned              = GetIsProvisioned();
    itsPrimaryAreaAddr          = GetPrimaryAreaAddr();
    itsFirstAuxAreaAddr         = GetFirstAuxAreaAddr();
    itsSecondAuxAreaAddr        = GetSecondAuxAreaAddr();
    itsMaxNumAddr               = GetMaxNumAddr();
    itsRoutingSystemID          = GetRoutingSystemID();
    itsRoutingLevel             = GetRoutingLevel();
    itsMaxLifetimeControl       = GetMaxLifetimeControl();
    itsPgne1IpAddress           = GetPgne1IpAddress();
    itsPgne2IpAddress           = GetPgne2IpAddress();

    itsFlushTimer               = GetFlushTimer();
    itsEntryTimer               = GetEntryTimer();
    itsType1Timer               = GetType1Timer();
    itsType2Timer               = GetType2Timer();
    itsType3Timer               = GetType3Timer();
    itsType4Timer               = GetType4Timer();
    itsProtocolAddr             = GetProtocolAddr();
    itsResetSequenceCounter     = GetResetSequenceCounter();
    itsLifetimeHops             = GetLifetimeHops();
    itsResetCacheCount          = GetResetCacheCount();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::RefreshSet()
{      
    // Configuration attributes
    SetTIDID(itsTIDID);     
    SetRouterID(itsRouterID);
    SetCommandSequence(itsCommandSequence);
    SetDCCRouterEnabled(itsDCCRouterEnabled);
    SetIsProvisioned(itsProvisioned);
    SetPrimaryAreaAddr(itsPrimaryAreaAddr);
    SetFirstAuxAreaAddr(itsFirstAuxAreaAddr);
    SetSecondAuxAreaAddr(itsSecondAuxAreaAddr);
    SetMaxNumAddr(itsMaxNumAddr);
    SetRoutingSystemID(itsRoutingSystemID);
    SetRoutingLevel(itsRoutingLevel);
    SetMaxLifetimeControl(itsMaxLifetimeControl);
    SetPgne1IpAddress(itsPgne1IpAddress);
    SetPgne2IpAddress(itsPgne2IpAddress);

    SetFlushTimer(itsFlushTimer);
    SetEntryTimer(itsEntryTimer);
    SetType1Timer(itsType1Timer);
    SetType2Timer(itsType2Timer);
    SetType3Timer(itsType3Timer);
    SetType4Timer(itsType4Timer);
    SetProtocolAddr(itsProtocolAddr);
    SetResetSequenceCounter(itsResetSequenceCounter);
    SetLifetimeHops(itsLifetimeHops);
    SetResetCacheCount(itsResetCacheCount);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsLevel1_RouterState       = CT_DCC_ROUTER_STATE_NOT_CONFIGURED;
    itsLevel2_RouterState       = CT_DCC_ROUTER_STATE_NOT_CONFIGURED;
    itsSequenceNumber           = 0; 

    itsRejectedAdjancency       = 0; 
    itsAreaAddressMismatch      = 0; 
    itsMaxAreaAddressMismatch   = 0; 
    itsL1DatabaseOverload       = 0; 
    itsL2DatabaseOverload       = 0;

    itsResolutionFailureCount   = 0;
    itsDefectsChanged           = false;

    // Configuration attributes
    itsTIDID                    = CT_AreaAddr("NULL         ");     
    itsRouterID                 = UNKNOWN_DCC_Router_ID;
    itsCommandSequence          = CT_DCC_IDLE;
    itsDCCRouterEnabled         = false;
    itsProvisioned              = false;
    itsPrimaryAreaAddr          = CT_AreaAddr("NULL         ");
    itsFirstAuxAreaAddr         = CT_AreaAddr("NULL         ");
    itsSecondAuxAreaAddr        = CT_AreaAddr("NULL         ");
    itsMaxNumAddr               = 0;
    itsRoutingSystemID          = CT_AreaAddr("NULL         ");
    itsRoutingLevel             = 0;
    itsMaxLifetimeControl       = 0;
    itsPgne1IpAddress           = 0;
    itsPgne2IpAddress           = 0;

    itsFlushTimer               = 0;
    itsEntryTimer               = 0;
    itsType1Timer               = 0;
    itsType2Timer               = 0;
    itsType3Timer               = 0;
    itsType4Timer               = 0;
    itsProtocolAddr             = 0;
    itsResetSequenceCounter     = 0;
    itsLifetimeHops             = 0;
    itsResetCacheCount          = 0;
    itsTarpEnable               = false;
}


// CONFIGURATION METHODS
// 

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetCommandSequence(CT_DCC_Sequence theCommandSequence)
{
    itsCommandSequence = theCommandSequence;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_Sequence TSPII_DrtrIf::GetCommandSequence() const
{
    return itsCommandSequence;
}


// Configuration Router Parameters

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetTIDID( const CT_AreaAddr& theTIDID)
{
    itsTIDID = theTIDID;
}

///////////////////////////////////////////////////////////////////////////////
CT_AreaAddr TSPII_DrtrIf::GetTIDID() const
{
    return itsTIDID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetRouterID( const CT_DCC_RouterId theRouterID)
{
    itsRouterID = theRouterID;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_RouterId TSPII_DrtrIf::GetRouterID() const
{
    return itsRouterID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetDCCRouterEnabled(bool theDCCRouterEnabled)
{
    itsDCCRouterEnabled = theDCCRouterEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DrtrIf::GetDCCRouterEnabled() const
{
    return itsDCCRouterEnabled;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetIsProvisioned(bool theProvisioned)
{
    itsProvisioned = theProvisioned;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DrtrIf::GetIsProvisioned() const
{
    return itsProvisioned;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetPrimaryAreaAddr( const CT_AreaAddr& thePrimaryAreaAddr)
{
    itsPrimaryAreaAddr = thePrimaryAreaAddr;
}

///////////////////////////////////////////////////////////////////////////////
CT_AreaAddr TSPII_DrtrIf::GetPrimaryAreaAddr() const
{
    return itsPrimaryAreaAddr;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetPgne1IpAddress( const uint32 thePgneIpAddress)
{
    itsPgne1IpAddress = thePgneIpAddress;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetPgne1IpAddress() const
{
    return itsPgne1IpAddress;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetPgne2IpAddress( const uint32 thePgneIpAddress)
{
    itsPgne2IpAddress = thePgneIpAddress;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetPgne2IpAddress() const
{
    return itsPgne2IpAddress;
}



///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetFirstAuxAreaAddr( const CT_AreaAddr& theFirstAuxAreaAddr)
{
    itsFirstAuxAreaAddr = theFirstAuxAreaAddr;
}

///////////////////////////////////////////////////////////////////////////////
CT_AreaAddr TSPII_DrtrIf::GetFirstAuxAreaAddr() const
{
    return itsFirstAuxAreaAddr;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetSecondAuxAreaAddr( const CT_AreaAddr& theSecondAuxAreaAddr)
{
    itsSecondAuxAreaAddr = theSecondAuxAreaAddr;
}

///////////////////////////////////////////////////////////////////////////////
CT_AreaAddr TSPII_DrtrIf::GetSecondAuxAreaAddr() const
{
    return itsSecondAuxAreaAddr;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetMaxNumAddr(uint8 theMaxNumAddr)
{
    itsMaxNumAddr = theMaxNumAddr;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetMaxNumAddr() const
{
    return itsMaxNumAddr;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetRoutingSystemID(CT_AreaAddr theRoutingSystemID)
{
    itsRoutingSystemID = theRoutingSystemID;
}

///////////////////////////////////////////////////////////////////////////////
CT_AreaAddr TSPII_DrtrIf::GetRoutingSystemID() const
{
    return itsRoutingSystemID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetRoutingLevel(uint8 theRoutingLevel)
{
    itsRoutingLevel = theRoutingLevel;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetRoutingLevel() const
{
    return itsRoutingLevel;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetMaxLifetimeControl(uint8 theMaxLifetimeControl)
{
    itsMaxLifetimeControl = theMaxLifetimeControl;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetMaxLifetimeControl() const
{
    return itsMaxLifetimeControl;
}



// Configuration TARP Parameters
     
///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetFlushTimer(uint16 theFlushTimer)
{
    itsFlushTimer = theFlushTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetFlushTimer() const
{
    return itsFlushTimer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetEntryTimer(uint8 theEntryTimer)
{
    itsEntryTimer = theEntryTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetEntryTimer() const
{
    return itsEntryTimer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetType1Timer(uint16 theType1Timer)
{
    itsType1Timer = theType1Timer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetType1Timer() const
{
    return itsType1Timer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetType2Timer(uint16 theType2Timer)
{
    itsType2Timer = theType2Timer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetType2Timer() const
{
    return itsType2Timer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetType3Timer(uint16 theType3Timer)
{
    itsType3Timer = theType3Timer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetType3Timer() const
{
    return itsType3Timer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetType4Timer(uint16 theType4Timer)
{
    itsType4Timer = theType4Timer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetType4Timer() const
{
    return itsType4Timer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetProtocolAddr(uint8 theProtocolAddr)
{
    itsProtocolAddr = theProtocolAddr;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetProtocolAddr() const
{
    return itsProtocolAddr;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetResetSequenceCounter(uint8 theResetSequenceCounter)
{
    itsResetSequenceCounter = theResetSequenceCounter;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DrtrIf::GetResetSequenceCounter() const
{
    return itsResetSequenceCounter;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::SetLifetimeHops(uint16 theLifetimeHops)
{
    itsLifetimeHops = theLifetimeHops;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DrtrIf::GetLifetimeHops() const
{
    return itsLifetimeHops;
}


// MONITORING METHODS

///////////////////////////////////////////////////////////////////////////////
CT_DCC_RouterState TSPII_DrtrIf::GetLevel1_RouterState()
{
    return itsLevel1_RouterState;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_RouterState TSPII_DrtrIf::GetLevel2_RouterState()
{
    return itsLevel2_RouterState;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetSequenceNumber()
{
    return itsSequenceNumber;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetRejectedAdjancency()
{
    return itsRejectedAdjancency;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetAreaAddressMismatch()
{
    return itsAreaAddressMismatch;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetMaxAreaAddressMismatch()
{
    return itsMaxAreaAddressMismatch;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetL1DatabaseOverload()
{
    return itsL1DatabaseOverload;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetL2DatabaseOverload()
{
    return itsL2DatabaseOverload;
}
 

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DrtrIf::GetResolutionFailureCount()
{
    return itsResolutionFailureCount;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_DrtrIf::GetDefectsChanged()
{
    return itsDefectsChanged;
}


///////////////////////////////////////////////////////////////////////////////
rtrvMapNeighbor_T*       
TSPII_DrtrIf::GetDccNeighbors( unsigned long routerID, unsigned int  mapType )
{
    return (rtrvMapNeighbor_T*)0;
}

rtrvMapNetwork_T*         
TSPII_DrtrIf::GetDccNetwork( unsigned long routerID, unsigned int  mapNtwkType )
{
    return (rtrvMapNetwork_T*)0;
}

///////////////////////////////////////////////////////////////////////////////
void                      
TSPII_DrtrIf::SetResetCacheCount(uint32 theResetCacheCount)
{
    itsResetCacheCount = theResetCacheCount;
}

uint32                    
TSPII_DrtrIf::GetResetCacheCount() const
{
    return itsResetCacheCount;
}


void
TSPII_DrtrIf::SetDCCTarpEnabled(bool theDCCTarpEnabled)
{
    itsTarpEnable = theDCCTarpEnabled;
}

bool
TSPII_DrtrIf::GetDCCTarpEnabled() const
{
    return  itsTarpEnable;      
}


///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DrtrIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLevel1_RouterState = (int) itsLevel1_RouterState;
    int aLevel2_RouterState = (int) itsLevel2_RouterState;
    int aCommandSequence  = itsCommandSequence; 

    // Monitor attributes
    theStream << aLevel1_RouterState;
    theStream << aLevel2_RouterState;
    theStream << itsSequenceNumber; 
    theStream << itsRejectedAdjancency; 
    theStream << itsAreaAddressMismatch; 
    theStream << itsMaxAreaAddressMismatch; 
    theStream << itsL1DatabaseOverload; 
    theStream << itsL2DatabaseOverload; 
    theStream << itsResolutionFailureCount;
    theStream << itsDefectsChanged;
    
    // Configuration attributes
    theStream << itsTIDID;
    theStream << itsRouterID;
    theStream << aCommandSequence;
    theStream << itsDCCRouterEnabled;
    theStream << itsProvisioned;
    theStream << itsPrimaryAreaAddr;
    theStream << itsFirstAuxAreaAddr;
    theStream << itsSecondAuxAreaAddr;
    theStream << itsMaxNumAddr;
    theStream << itsRoutingSystemID;
    theStream << itsRoutingLevel;
    theStream << itsMaxLifetimeControl;
    theStream << itsPgne1IpAddress;
    theStream << itsPgne2IpAddress;

    theStream << itsFlushTimer;
    theStream << itsEntryTimer;
    theStream << itsType1Timer;
    theStream << itsType2Timer;
    theStream << itsType3Timer;
    theStream << itsType4Timer;
    theStream << itsProtocolAddr;
    theStream << itsResetSequenceCounter;
    theStream << itsLifetimeHops;
    theStream << itsResetCacheCount;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DrtrIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aLevel1_RouterState;
    int aLevel2_RouterState;
    int aCommandSequence;

    // Monitor attributes
    theStream >> aLevel1_RouterState;
    theStream >> aLevel2_RouterState;
    theStream >> itsSequenceNumber; 
    theStream >> itsRejectedAdjancency; 
    theStream >> itsAreaAddressMismatch; 
    theStream >> itsMaxAreaAddressMismatch; 
    theStream >> itsL1DatabaseOverload; 
    theStream >> itsL2DatabaseOverload;
    theStream >> itsResolutionFailureCount;
    theStream >> itsDefectsChanged;
    
    // Configuration attributes
    theStream >> itsTIDID;
    theStream >> itsRouterID;
    theStream >> aCommandSequence;
    theStream >> itsDCCRouterEnabled;
    theStream >> itsProvisioned;
    theStream >> itsPrimaryAreaAddr;
    theStream >> itsFirstAuxAreaAddr;
    theStream >> itsSecondAuxAreaAddr;
    theStream >> itsMaxNumAddr;
    theStream >> itsRoutingSystemID;
    theStream >> itsRoutingLevel;
    theStream >> itsMaxLifetimeControl;
    theStream >> itsPgne1IpAddress;
    theStream >> itsPgne2IpAddress;

    theStream >> itsFlushTimer;
    theStream >> itsEntryTimer;
    theStream >> itsType1Timer;
    theStream >> itsType2Timer;
    theStream >> itsType3Timer;
    theStream >> itsType4Timer;
    theStream >> itsProtocolAddr;
    theStream >> itsResetSequenceCounter;
    theStream >> itsLifetimeHops;
    theStream >> itsResetCacheCount;

    itsCommandSequence  = (CT_DCC_Sequence) aCommandSequence;
    itsLevel1_RouterState = (CT_DCC_RouterState)aLevel1_RouterState;
    itsLevel2_RouterState = (CT_DCC_RouterState)aLevel2_RouterState;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_DrtrIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLevel1_RouterState = (int) itsLevel1_RouterState;
    int aLevel2_RouterState = (int) itsLevel2_RouterState;
    int aCommandSequence  = itsCommandSequence;

    // Monitor attributes
    theStream << FC_InsertVar(aLevel1_RouterState);
    theStream << FC_InsertVar(aLevel2_RouterState);
    theStream << FC_InsertVar(itsSequenceNumber); 
    theStream << FC_InsertVar(itsRejectedAdjancency); 
    theStream << FC_InsertVar(itsAreaAddressMismatch); 
    theStream << FC_InsertVar(itsMaxAreaAddressMismatch); 
    theStream << FC_InsertVar(itsL1DatabaseOverload); 
    theStream << FC_InsertVar(itsL2DatabaseOverload);
    theStream << FC_InsertVar(itsResolutionFailureCount);
    theStream << FC_InsertVar(itsDefectsChanged);
    
    // Configuration attributes
    theStream << FC_InsertVar(itsTIDID);
    theStream << FC_InsertVar(itsRouterID);
    theStream << FC_InsertVar(aCommandSequence);
    theStream << FC_InsertVar(itsDCCRouterEnabled);
    theStream << FC_InsertVar(itsProvisioned);
    theStream << FC_InsertVar(itsPrimaryAreaAddr);
    theStream << FC_InsertVar(itsFirstAuxAreaAddr);
    theStream << FC_InsertVar(itsSecondAuxAreaAddr);
    theStream << FC_InsertVar(itsMaxNumAddr);
    theStream << FC_InsertVar(itsRoutingSystemID);
    theStream << FC_InsertVar(itsRoutingLevel);
    theStream << FC_InsertVar(itsMaxLifetimeControl);
    theStream << FC_InsertVar(itsPgne1IpAddress);
    theStream << FC_InsertVar(itsPgne2IpAddress);

    theStream << FC_InsertVar(itsFlushTimer);
    theStream << FC_InsertVar(itsEntryTimer);
    theStream << FC_InsertVar(itsType1Timer);
    theStream << FC_InsertVar(itsType2Timer);
    theStream << FC_InsertVar(itsType3Timer);
    theStream << FC_InsertVar(itsType4Timer);
    theStream << FC_InsertVar(itsProtocolAddr);
    theStream << FC_InsertVar(itsResetSequenceCounter);
    theStream << FC_InsertVar(itsLifetimeHops);
    theStream << FC_InsertVar(itsResetCacheCount);
     
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_DrtrIf::ReadObject(istream & theStream)
{
    int aLevel1_RouterState;
    int aLevel2_RouterState;
    int aCommandSequence;

    // Monitor attributes
    theStream >> FC_ExtractVar(aLevel1_RouterState);
    theStream >> FC_ExtractVar(aLevel2_RouterState);
    theStream >> FC_ExtractVar(itsSequenceNumber); 
    theStream >> FC_ExtractVar(itsRejectedAdjancency); 
    theStream >> FC_ExtractVar(itsAreaAddressMismatch); 
    theStream >> FC_ExtractVar(itsMaxAreaAddressMismatch); 
    theStream >> FC_ExtractVar(itsL1DatabaseOverload); 
    theStream >> FC_ExtractVar(itsL2DatabaseOverload);
    theStream >> FC_ExtractVar(itsResolutionFailureCount);
    theStream >> FC_ExtractVar(itsDefectsChanged);
    
    // Configuration attributes
    theStream >> FC_ExtractVar(itsTIDID);
    theStream >> FC_ExtractVar(itsRouterID);
    theStream >> FC_ExtractVar(aCommandSequence);
    theStream >> FC_ExtractVar(itsDCCRouterEnabled);
    theStream >> FC_ExtractVar(itsProvisioned);
    theStream >> FC_ExtractVar(itsPrimaryAreaAddr);
    theStream >> FC_ExtractVar(itsFirstAuxAreaAddr);
    theStream >> FC_ExtractVar(itsSecondAuxAreaAddr);
    theStream >> FC_ExtractVar(itsMaxNumAddr);
    theStream >> FC_ExtractVar(itsRoutingSystemID);
    theStream >> FC_ExtractVar(itsRoutingLevel);
    theStream >> FC_ExtractVar(itsMaxLifetimeControl);
    theStream >> FC_ExtractVar(itsPgne1IpAddress);
    theStream >> FC_ExtractVar(itsPgne2IpAddress);

    theStream >> FC_ExtractVar(itsFlushTimer);
    theStream >> FC_ExtractVar(itsEntryTimer);
    theStream >> FC_ExtractVar(itsType1Timer);
    theStream >> FC_ExtractVar(itsType2Timer);
    theStream >> FC_ExtractVar(itsType3Timer);
    theStream >> FC_ExtractVar(itsType4Timer);
    theStream >> FC_ExtractVar(itsProtocolAddr);
    theStream >> FC_ExtractVar(itsResetSequenceCounter);
    theStream >> FC_ExtractVar(itsLifetimeHops);
    theStream >> FC_ExtractVar(itsResetCacheCount);

    itsCommandSequence  = (CT_DCC_Sequence) aCommandSequence;
    itsLevel1_RouterState = (CT_DCC_RouterState)aLevel1_RouterState;
    itsLevel2_RouterState = (CT_DCC_RouterState)aLevel2_RouterState;
    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DrtrIf::Display(FC_Stream & theStream)
{   
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  OSI Router Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Command Sequence         = " << DISPLAY_DCC_SEQUENCE(itsCommandSequence)       << "\n";
    theStream << "     DCC Router Parameters\n";
    theStream << "      TID ID                   = " << itsTIDID.GetAreaPrintable(false)   << "\n";
    theStream << "      Router ID                = " << static_cast<uint>(itsRouterID)       << "\n";
    theStream << "      Router Enabled           = " << DISPLAY_BOOL(itsDCCRouterEnabled)       << "\n";
    theStream << "      Router Provisioned       = " << DISPLAY_BOOL(itsProvisioned)       << "\n";
    theStream << "      Primary Area Address     = " << itsPrimaryAreaAddr.GetAreaPrintable(false)   << "\n";
    theStream << "      First Aux Address        = " << itsFirstAuxAreaAddr.GetAreaPrintable(false)   << "\n";
    theStream << "      Second Aux Address       = " << itsSecondAuxAreaAddr.GetAreaPrintable(false)   << "\n";
    theStream << "      Max Number of Area Addr  = " << static_cast<uint>(itsMaxNumAddr)       << "\n";
    theStream << "      Routing System ID        = " << hex << itsRoutingSystemID.GetAreaPrintable(false)   << "\n";
    theStream << "      Routing Level            = " << static_cast<uint>(itsRoutingLevel)       << "\n";
    theStream << "      Max Lifetime Control     = " << static_cast<uint>(itsMaxLifetimeControl)       << "\n";
    theStream << "     TARP Parameters\n";
    theStream << "      Flush Timer              = " << dec << (itsFlushTimer)       << " min\n";
    theStream << "      Entry Timer              = " << static_cast<uint>(itsEntryTimer)       << " min\n";
    theStream << "      Type 1 Timer             = " << dec << (itsType1Timer)       << " sec\n";
    theStream << "      Type 2 Timer             = " << dec << (itsType2Timer)       << " sec\n";
    theStream << "      Type 3 Timer             = " << dec << (itsType3Timer)       << " sec\n";
    theStream << "      Type 4 Timer             = " << dec << (itsType4Timer)       << " sec\n";
    theStream << "      Protocol Address         = " << static_cast<uint>(itsProtocolAddr)       << "\n";
    theStream << "      Reset Sequence Counter   = " << static_cast<uint>(itsResetSequenceCounter)       << "\n";
    theStream << "      TARP Lifetime Hops       = " << dec << (itsLifetimeHops)       << "\n";
    theStream << "      Flush Cache Count        = " << dec << (itsResetCacheCount)       << "\n";
    theStream << "      PGNE 1 Address           = " << hex << (itsPgne1IpAddress)   <<"\n";
    theStream << "      PGNE 2 Address           = " << hex << (itsPgne2IpAddress)   <<"\n";

    theStream << "    MONITORING\n";
    theStream << "      Level 1 Router State     = " << DISPLAY_DCC_RouterState(itsLevel1_RouterState)         << "\n";
    theStream << "      Level 2 Router State     = " << DISPLAY_DCC_RouterState(itsLevel2_RouterState)         << "\n";
    theStream << "      Sequence Number          = " << dec << itsSequenceNumber        << "\n";
    theStream << "      Rejected Adjancency      = " << dec << itsRejectedAdjancency        << "\n";
    theStream << "      Area Address Mismatch    = " << dec << itsAreaAddressMismatch        << "\n";
    theStream << "      Max Area Address Mismatch= " << dec << itsMaxAreaAddressMismatch        << "\n";
    theStream << "      L1 Database Overload     = " << dec << itsL1DatabaseOverload        << "\n";
    theStream << "      L2 Database Overload     = " << dec << itsL2DatabaseOverload        << "\n";
    theStream << "      Resolution Failure Count = " << dec << itsResolutionFailureCount        << "\n";
    theStream << "      Defects Changed          = " << DISPLAY_BOOL(itsDefectsChanged)        << "\n";
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DrtrIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "commandsequence") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_REFRESH; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_SEQUENCE(i)) == 0)
            {
                SetCommandSequence((CT_DCC_Sequence)i);
                printUsage = false;
                break;
            }
        }
    }
    // Router Operations
    else if (argc == 2 && strcmp(argv[0], "tidid") == 0)
    {
        CT_AreaAddr addr(argv[1]);
        SetTIDID(addr);
    }
    else if ((argc == 2) && strcmp(argv[0], "routerid") == 0)
    {
        SetRouterID((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "routerenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetDCCRouterEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetDCCRouterEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "isprovisioned") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsProvisioned(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsProvisioned(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "primaryaddr") == 0)
    {
        CT_AreaAddr addr(argv[1]);
        SetPrimaryAreaAddr(addr);
    }
    else if (argc == 2 && strcmp(argv[0], "firstauxaddr") == 0)
    {
        CT_AreaAddr addr(argv[1]);
        SetFirstAuxAreaAddr(addr);
    }
    else if (argc == 2 && strcmp(argv[0], "secondauxaddr") == 0)
    {
        CT_AreaAddr addr(argv[1]);
        SetSecondAuxAreaAddr(addr);
    }
    else if ((argc == 2) && strcmp(argv[0], "maxnumareaaddr") == 0)
    {
        SetMaxNumAddr((uint8)strtoul(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "routingsystemid") == 0)
    {
        CT_AreaAddr addr(argv[1]);
        SetRoutingSystemID(addr);
    }
    else if ((argc == 2) && strcmp(argv[0], "routelevel") == 0)
    {
        SetRoutingLevel((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxlifetimecontrol") == 0)
    {
        SetMaxLifetimeControl((uint8)strtoul(argv[1], NULL, 0));
    }
    // Tarp Operations
    else if ((argc == 2) && strcmp(argv[0], "flushtimer") == 0)
    {
        SetFlushTimer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "entrytimer") == 0)
    {
        SetEntryTimer((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxtype1timer") == 0)
    {
        SetType1Timer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxtype2timer") == 0)
    {
        SetType2Timer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxtype3timer") == 0)
    {
        SetType3Timer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxtype4timer") == 0)
    {
        SetType4Timer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "protocoladdr") == 0)
    {
        SetProtocolAddr((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "resetsequencecounter") == 0)
    {
        SetResetSequenceCounter((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "liftimehops") == 0)
    {
        SetLifetimeHops((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "resetcachecount") == 0)
    {
        SetResetCacheCount((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "enablegretnl") == 0))
    {
        SetPgne1IpAddress((uint32)strtoul(argv[1], NULL, 0));
    }

    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << 

                   "    routerenabled            <on|off>\n"
                   "    isprovisioned            <on|off>\n"
                   "    commandsequence          <Idle|TIDIdBegin|TIDIdCommit|RouterBegin|RouterCommit|TarpBegin|TarpCommit|LinkBegin|LinkCommit>\n"
                   "    tidid                    <20 byte field>"
                   "    routerid                 <1 ... 15>\n"
                   "    primaryaddr              <13 byte hex value>\n"
                   "    firstauxaddr             <13 byte hex value>\n"
                   "    secondauxaddr            <13 byte hex value>\n"
                   "    maxnumareaaddr           <1 ... 3>\n"
                   "    routingsystemid          <1-8 byte hex value>\n"
                   "    routelevel               <1 ... 3>\n"
                   "    maxlifetimecontrol       <1 ... 255>\n"
                   "    flushtimer               <0 ... 1440 min>\n"
                   "    entrytimer               <1 ... 10 min>\n"
                   "    type1timer               <2 ... 3600s>\n"
                   "    type2timer               <2 ... 3600s>\n"
                   "    type3timer               <2 ... 3600s>\n"
                   "    type4timer               <2 ... 3600s>\n"
                   "    protocoladdr             <0 ... 255>\n"
                   "    resetsequencecounter     <0 ... 255>\n"
                   "    liftimehops              <0 ... 65535>\n" 
                   "    resetcachecount          <0 ... 65535>\n" 
                   "    enablegretnl             <0 ... 1>\n"<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DrtrIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "level1router") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_ROUTER_STATE_DISABLED; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_RouterState(i)) == 0)
            {
                itsLevel1_RouterState = ((CT_DCC_RouterState)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "level2router") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_ROUTER_STATE_DISABLED; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_RouterState(i)) == 0)
            {
                itsLevel2_RouterState = ((CT_DCC_RouterState)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "sequencenumber") == 0))
    {
        itsSequenceNumber = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "incsequencenumber") == 0))
    {
        itsSequenceNumber += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "rejectedadj") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsRejectedAdjancency)) itsRejectedAdjancency++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsRejectedAdjancency)) itsRejectedAdjancency++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "areamismatch") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsAreaAddressMismatch)) itsAreaAddressMismatch++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsAreaAddressMismatch)) itsAreaAddressMismatch++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "maxareamismatch") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsMaxAreaAddressMismatch)) itsMaxAreaAddressMismatch++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsMaxAreaAddressMismatch)) itsMaxAreaAddressMismatch++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "L1dboverload") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsL1DatabaseOverload)) itsL1DatabaseOverload++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsL1DatabaseOverload)) itsL1DatabaseOverload++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "L2dboverload") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsL2DatabaseOverload)) itsL2DatabaseOverload++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsL2DatabaseOverload)) itsL2DatabaseOverload++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "defectschangedmon") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsDefectsChanged = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsDefectsChanged = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "resolutionfailurecount") == 0))
    {
        itsResolutionFailureCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "incresolutionfailurecount") == 0))
    {
        itsResolutionFailureCount += strtoul(argv[1], NULL, 0);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    level1router              <Unknown|NotConfigured|Operating|Overload|Disabled>\n"
                   "    level2router              <Unknown|NotConfigured|Operating|Overload|Disabled>\n"
                   "    sequencenumber            <0 ... 0xFFFFFFFF>\n"
                   "    incsequencenumber         <0 ... 0xFFFFFFFF>\n"
                   "    rejectedadj               <on|off>\n"
                   "    areamismatch              <on|off>\n"
                   "    maxareamismatch           <on|off>\n"
                   "    L1dboverload              <on|off>\n"
                   "    L2dboverload              <on|off>\n"
                   "    resolutionfailurecount    <0 ... 0xFFFFFFFF>\n"
                   "    incresolutionfailurecount <0 ... 0xFFFFFFFF>\n"
                   "    defectschangedmon         <on|off>\n" << endl;
    }
    
    return printUsage;
}

