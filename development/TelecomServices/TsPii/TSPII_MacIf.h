/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - March 2008
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for ports MAC hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#ifndef TSPII_MACIF_H
#define TSPII_MACIF_H

#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_AgentFacility.h"
#include "CommonTypes/CT_LacpTypes.h"
#include "TsPii/TSPII_BaseIf.h"


class TSPII_MacIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_MacIf(bool theDefault = false);
    virtual                           ~TSPII_MacIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Monitor Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_TEL_MAC_AUTONEGSTATUS  GetAutoNegStatus();
    virtual CT_TEL_DETECTED           GetAutoNegRemoteSignal();
    virtual CT_TEL_daHz               GetOpRate();
    virtual CT_TEL_MAC_DUPLEX_MODE    GetOpDuplexMode();
    virtual CT_TEL_MAC_FLOWCTRL       GetOpFlowCtrl();
    virtual bool                      GetOpAutoNeg();
    virtual uint32                    GetLinkFailRx();
    virtual uint32                    GetRFLinkFail();

    //virtual uint32                    GetLacpFail();

    virtual CT_TEL_LacpPortState      GetPortLacpState() const;
    virtual CT_AGGRE_FIELD            GetPortAggregationField() const;
    virtual uint16                    GetPortLacpPriority() const;
    virtual bool                      GetPartnerActiveFlag() const;
    virtual const CT_LacpSystemId   & GetPartnerSystemID() const;
    virtual uint16                    GetPartnerPortPriority() const;
    virtual uint32                    GetPartnerOperationalKey() const;
    virtual uint8                     GetPartnerPortState() const;

    virtual const CT_LacpSystemId   & GetLagActorSystemID() const;
    virtual uint16                    GetLagActorSystemPriority() const;
    virtual uint32                    GetLagActorOperationalKey() const;
    virtual uint16                    GetLagActorAdminKey() const;

    virtual const CT_LacpSystemId   & GetLagPartnerSystemID() const;
    virtual uint16                    GetLagPartnerSystemPriority() const;
    virtual uint32                    GetLagPartnerOperationalKey() const;
    virtual uint16                    GetLagPartnerAdminKey() const;


    virtual uint32                    GetFefi();

    virtual void                      EnableFefiTransparency(bool enable);
    virtual bool                      GetFefiTransparencyEnabled() const;

    virtual CT_ETH_SFP_XFP_TYPE       GetEthSfpXfpType() const;

    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetAutoNeg(bool theEnable); 
    virtual bool                      GetAutoNeg() const;

    virtual void                      SetCfgRate(CT_TEL_daHz theRate);
    virtual CT_TEL_daHz               GetCfgRate() const;

    virtual void                      SetCfgDuplexMode(CT_TEL_MAC_DUPLEX_MODE theMode);
    virtual CT_TEL_MAC_DUPLEX_MODE    GetCfgDuplexMode() const;

    virtual void                      SetCfgFlowCtrl(CT_TEL_MAC_FLOWCTRL theMode);
    virtual CT_TEL_MAC_FLOWCTRL       GetCfgFlowCtrl() const;

    virtual void                      SetCfgAdvrtFlowCtrl(CT_TEL_MAC_ADFLW_CTRL theMode);
    virtual CT_TEL_MAC_ADFLW_CTRL     GetCfgAdvrtFlowCtrl() const;

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
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv)
                                          { TSPII_BaseIf::Display(theStream, argc, argv); }
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                     RefreshGet();
    void                     RefreshSet();

    // Monitoring attributes
    CT_TEL_MAC_AUTONEGSTATUS itsAutoNegStatus;
    CT_TEL_DETECTED          itsAutoNegRemoteSignal;
    CT_TEL_daHz              itsOpRate;
    CT_TEL_MAC_DUPLEX_MODE   itsOpDuplexMode;
    CT_TEL_MAC_FLOWCTRL      itsOpFlowCtrl;
    bool                     itsOpAutoNeg;
    uint32                   itsLinkFailRx;
    uint32                   itsRFLinkFail;

    //uint32                   itsLacpFail;

    CT_TEL_LacpPortState     itsPortLacpState;
    CT_AGGRE_FIELD           itsPortAggregationField;
    uint16                   itsPortLacpPriority;
    bool                     itsPartnerActiveFlag;
    CT_LacpSystemId          itsPartnerSystemID;
    uint16                   itsPartnerPortPriority;
    uint32                   itsPartnerOperationalKey;
    uint8                    itsPartnerPortState;

    CT_LacpSystemId          itsLagActorSystemID;
    uint16                   itsLagActorSystemPriority;
    uint32                   itsLagActorOperationalKey;
    uint16                   itsLagActorAdminKey;

    CT_LacpSystemId          itsLagPartnerSystemID;
    uint16                   itsLagPartnerSystemPriority;
    uint32                   itsLagPartnerOperationalKey;
    uint16                   itsLagPartnerAdminKey;

    uint32                   itsFefi;

    CT_ETH_SFP_XFP_TYPE      itsEthSfpXfpType;


    // Configuration attributes
    bool                     itsAutoNeg;
    CT_TEL_daHz              itsCfgRate;
    CT_TEL_MAC_DUPLEX_MODE   itsCfgDuplexMode;
    CT_TEL_MAC_FLOWCTRL      itsCfgFlowCtrl;
    CT_TEL_MAC_ADFLW_CTRL    itsCfgAdvrtFlowCtrl;
    uint32                   trace;
    bool                     itsFefiTransparencyEnabled;
};

#define DISPLAY_MAC_TRACE(x) ((x==0)  ? "OFF" : \
                             (x==1)   ? "DEBUG" : \
                             (x==2)   ? "DETAIL": \
                             "DETAIL")

#endif // TSPII_MACIF_H
