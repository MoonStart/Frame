#ifndef _TSPII_DDLTIF_H
#define _TSPII_DDLTIF_H
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

class TSPII_DdltIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_DdltIf(bool theDefault = false);
    virtual                           ~TSPII_DdltIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Ddlt Config Interfaces for OSI Router
    // -----------------------------------------------------------------------------------   

    virtual void                      SetCommandSequence(CT_DCC_Sequence theCommandSequence);
    virtual CT_DCC_Sequence           GetCommandSequence() const;

    // -----------------------------------------------------------------------------------
    // Ddlt Config Interfaces for DCC Links
    // -----------------------------------------------------------------------------------

    virtual void                      SetIsProvisioned(bool theProvisioned);
    virtual bool                      GetIsProvisioned() const;

    virtual void                      SetIntfID(CT_IfIndexIdent theIntfID);
    virtual CT_IfIndexIdent           GetIntfID() const;

    virtual void                      SetLinkRouterID(CT_DCC_RouterId theLinkRouterID);
    virtual CT_DCC_RouterId           GetLinkRouterID() const;

    virtual void                      SetRouterShelfID(CT_ShelfId theRouterShelf);
    virtual CT_ShelfId                GetRouterShelfID() const;

    
    // From LAPD Profile
    virtual void                      SetTransferMode(CT_LPF_TxMode theTransferMode);
    virtual CT_LPF_TxMode             GetTransferMode() const;

    virtual void                      SetMaxFrameSize(uint16 theMaxFrameSize);
    virtual uint16                    GetMaxFrameSize() const;


    // From LAPD Command
    virtual void                      SetProtocolLinkEnabled(bool theEnabled);
    virtual bool                      GetProtocolLinkEnabled() const;

    virtual void                      SetFollowProtection(bool theFollowProtection);
    virtual bool                      GetFollowProtection() const;
    
    virtual void                      SetChecksumEnabled(bool theEnabled);
    virtual bool                      GetChecksumEnabled() const;

    virtual void                      SetHoldingTimerMultiplier(uint8 theHTMultiplier);
    virtual uint8                     GetHoldingTimerMultiplier() const;

    virtual void                      SetConfigurationTimer(uint16 theConfigTimer);
    virtual uint16                    GetConfigurationTimer() const;

    virtual void                      SetHelloTimer(uint8 theHelloTimer);
    virtual uint8                     GetHelloTimer() const;

    virtual void                      SetDefaultMetric(uint8 theDefaultMetric);
    virtual uint8                     GetDefaultMetric() const;

    virtual void                      SetReDirectHoldingTimer(uint16 theReDirectHoldingTimer);
    virtual uint16                    GetReDirectHoldingTimer() const;

    virtual void                      SetLinkRoutingLevel(uint8 theLinkRoutingLevel);
    virtual uint8                     GetLinkRoutingLevel() const;

    virtual void                      SetESConfigurationTimer(uint16 theESConfigurationTimer);
    virtual uint16                    GetESConfigurationTimer() const;


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

protected:

    void                 RefreshGet();
    void                 RefreshSet();

    // Configuration attributes
    CT_DCC_Sequence         itsCommandSequence;

    // For DCC Links
    bool                    itsProvisioned;
    CT_IfIndexIdent         itsIntfID;
    CT_DCC_RouterId         itsLinkRouterID;
    CT_ShelfId              itsRouterShelfID;   
    bool                    itsProtocolLinkEnabled;
    CT_LPF_TxMode           itsTransferMode;
    uint16                  itsMaxFrameSize;
    bool                    itsFollowProtection;

    bool                    itsChecksumEnabled;
    uint8                   itsHTMultiplier;
    uint16                  itsConfigTimer;
    uint8                   itsHelloTimer;
    uint8                   itsDefaultMetric;
    uint16                  itsReDirectHoldingTimer;
    uint8                   itsLinkRoutingLevel;
    uint16                  itsESConfigurationTimer;
};

#endif // _TSPII_DDLTIF_H
