#ifndef _TSPII_DRTRIF_H
#define _TSPII_DRTRIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Mark Nash/Denham Reynolds - August 2006
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Dcc Hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_DCC_Definitions.h"
#include "CommonTypes/CT_OSI_Definition.h"

class TSPII_DrtrIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_DrtrIf(bool theDefault = false);
    virtual                           ~TSPII_DrtrIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Drtr Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_DCC_RouterState        GetLevel1_RouterState();
    virtual CT_DCC_RouterState        GetLevel2_RouterState();
    virtual uint32                    GetSequenceNumber();

    virtual uint32                    GetRejectedAdjancency(); 
    virtual uint32                    GetAreaAddressMismatch(); 
    virtual uint32                    GetMaxAreaAddressMismatch(); 
    virtual uint32                    GetL1DatabaseOverload(); 
    virtual uint32                    GetL2DatabaseOverload(); 

    virtual uint32                    GetResolutionFailureCount();  
    virtual bool                      GetDefectsChanged();

    // -----------------------------------------------------------------------------------
    // Drtr Config Interfaces for OSI Router
    // -----------------------------------------------------------------------------------   

    virtual void                      SetCommandSequence(CT_DCC_Sequence theCommandSequence);
    virtual CT_DCC_Sequence           GetCommandSequence() const;

    // OSI Router Parameters

    virtual void                      SetTIDID( const CT_AreaAddr& theTIDID);
    virtual CT_AreaAddr               GetTIDID() const;

    virtual void                      SetRouterID(CT_DCC_RouterId theRouterID);
    virtual CT_DCC_RouterId           GetRouterID() const;


    virtual void                      SetDCCRouterEnabled(bool theDCCRouterEnabled);
    virtual bool                      GetDCCRouterEnabled() const;

    virtual void                      SetIsProvisioned(bool theProvisioned);
    virtual bool                      GetIsProvisioned() const;


    virtual void                      SetPrimaryAreaAddr( const CT_AreaAddr& thePrimaryAreaAddr);
    virtual CT_AreaAddr               GetPrimaryAreaAddr() const;

    virtual void                      SetFirstAuxAreaAddr( const CT_AreaAddr& theFirstAuxAreaAddr);
    virtual CT_AreaAddr               GetFirstAuxAreaAddr() const;

    virtual void                      SetSecondAuxAreaAddr( const CT_AreaAddr& theSecondAuxAreaAddr);
    virtual CT_AreaAddr               GetSecondAuxAreaAddr() const;

    virtual void                      SetPgne1IpAddress( const uint32 thePrimaryAreaAddr);
    virtual uint32                    GetPgne1IpAddress() const;

    virtual void                      SetPgne2IpAddress( const uint32 thePrimaryAreaAddr);
    virtual uint32                    GetPgne2IpAddress() const;

    virtual void                      SetMaxNumAddr(uint8 theMaxNumAddr);
    virtual uint8                     GetMaxNumAddr() const;

    virtual void                      SetRoutingSystemID(CT_AreaAddr theRoutingSystemID);
    virtual CT_AreaAddr               GetRoutingSystemID() const;

    virtual void                      SetRoutingLevel(uint8 theRoutingLevel);
    virtual uint8                     GetRoutingLevel() const;

    virtual void                      SetMaxLifetimeControl(uint8 theMaxLifetimeControl);
    virtual uint8                     GetMaxLifetimeControl() const;


    // TARP Parameters

    virtual void                      SetFlushTimer(uint16 theFlushTimer);
    virtual uint16                    GetFlushTimer() const;

    virtual void                      SetEntryTimer(uint8 theEntryTimer);
    virtual uint8                     GetEntryTimer() const;

    virtual void                      SetType1Timer(uint16 theType1Timer);
    virtual uint16                    GetType1Timer() const;

    virtual void                      SetType2Timer(uint16 theType2Timer);
    virtual uint16                    GetType2Timer() const;

    virtual void                      SetType3Timer(uint16 theType3Timer);
    virtual uint16                    GetType3Timer() const;

    virtual void                      SetType4Timer(uint16 theType4Timer);
    virtual uint16                    GetType4Timer() const;

    virtual void                      SetProtocolAddr(uint8 theProtocolAddr);
    virtual uint8                     GetProtocolAddr() const;

    virtual void                      SetResetSequenceCounter(uint8 theResetSequenceCounter);
    virtual uint8                     GetResetSequenceCounter() const;

    virtual void                      SetLifetimeHops(uint16 theLifetimeHops);
    virtual uint16                    GetLifetimeHops() const;

    virtual void                      SetResetCacheCount(uint32 theResetCacheCount);
    virtual uint32                    GetResetCacheCount() const;

    virtual void                      SetDCCTarpEnabled(bool theDCCRouterEnabled);
    virtual bool                      GetDCCTarpEnabled() const;


    // -----------------------------------------------------------------------------------
    // TL1 methods
    // -----------------------------------------------------------------------------------
    virtual rtrvMapNeighbor_T*        GetDccNeighbors( unsigned long routerID, unsigned int  mapType );
    virtual rtrvMapNetwork_T*         GetDccNetwork( unsigned long routerID, unsigned int  mapNtwkType );

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
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();

    // Monitoring attributes
    CT_DCC_RouterState      itsLevel1_RouterState;
    CT_DCC_RouterState      itsLevel2_RouterState;
    uint32                  itsSequenceNumber;

    uint32                  itsRejectedAdjancency; 
    uint32                  itsAreaAddressMismatch; 
    uint32                  itsMaxAreaAddressMismatch; 
    uint32                  itsL1DatabaseOverload; 
    uint32                  itsL2DatabaseOverload;

    uint32                  itsResolutionFailureCount;
    bool                    itsDefectsChanged;

    // Configuration attributes
    CT_DCC_Sequence         itsCommandSequence;

    // For Router
    CT_AreaAddr             itsTIDID;     
    CT_DCC_RouterId         itsRouterID; 

    bool                    itsDCCRouterEnabled;
    bool                    itsProvisioned;

    CT_AreaAddr             itsPrimaryAreaAddr;
    CT_AreaAddr             itsFirstAuxAreaAddr;
    CT_AreaAddr             itsSecondAuxAreaAddr;

    uint32                  itsPgne1IpAddress;
    uint32                  itsPgne2IpAddress;

    uint8                   itsMaxNumAddr;
    CT_AreaAddr             itsRoutingSystemID;
    uint8                   itsRoutingLevel;
    uint8                   itsMaxLifetimeControl;

    uint16                  itsFlushTimer;
    uint8                   itsEntryTimer;
    uint16                  itsType1Timer;
    uint16                  itsType2Timer;
    uint16                  itsType3Timer;
    uint16                  itsType4Timer;
    uint8                   itsProtocolAddr;
    uint8                   itsResetSequenceCounter;
    uint16                  itsLifetimeHops;  
    uint32                  itsResetCacheCount;
    bool                    itsTarpEnable;
};

#endif // _TSPII_DRTRIF_H
