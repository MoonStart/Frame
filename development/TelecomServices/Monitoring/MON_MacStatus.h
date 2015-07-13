//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MACSTATUS_H
#define MON_MACSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_LacpTypes.h>
#include "MON_Object.h"


//This class hold the status values for the MAC layer.
class MON_MacStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_MacStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_MacStatus();

    // These methods are modifiers and accessors for 
    // the current Auto Negotiation Status
    CT_TEL_MAC_AUTONEGSTATUS GetAutoNegStatus() const;
    bool SetAutoNegStatus(CT_TEL_MAC_AUTONEGSTATUS theAutoNegStatus);

    // These methods are modifiers and accessors for the current
    // state of the Auto Negotiation Remote Signal Detected
    CT_TEL_DETECTED GetAutoNegRmtSignal() const;
    bool SetAutoNegRmtSignal(CT_TEL_DETECTED theAutoNegRmtSignal);

    // These methods are modifiers and accessors for 
    // the current operational ethernet rate.
    CT_TEL_daHz GetOperRate() const; 
    bool SetOperRate(CT_TEL_daHz theOperRate);

    // These methods are modifiers and accessors for 
    // the current operational duplex mode.
    CT_TEL_MAC_DUPLEX_MODE GetOperDuplexMode() const; 
    bool SetOperDuplexMode(CT_TEL_MAC_DUPLEX_MODE theOperDuplex);
    
    // These methods are modifiers and accessors for 
    // the current operational flow control mode.
    CT_TEL_MAC_FLOWCTRL GetOperFlowCtrl() const; 
    bool SetOperFlowCtrl(CT_TEL_MAC_FLOWCTRL theOperFlowCtrl);

    // These methods are modifiers and accessors for 
    // the current operational Auto Negotiation mode.
    bool GetOperAutoNeg() const; 
    bool SetOperAutoNeg(bool theOperAutoNeg);

    // These methods are modifiers and accessors for 
    // the current LinkFailRx state.
    bool GetLinkFailRx() const; 
    bool SetLinkFailRx(bool theLinkFailRx);


    // These methods are modifiers and accessors for 
    // the current LACP Port State.
    CT_TEL_LacpPortState GetPortLacpState() const;
    bool SetPortLacpState(CT_TEL_LacpPortState theState);

    // These methods are modifiers and accessors for 
    //The current LACP Aggregation Field.
    CT_AGGRE_FIELD GetPortAggregationField() const;
    bool SetPortAggregationField(CT_AGGRE_FIELD theField);

    // These methods are modifiers and accessors for 
    // the current LACP Port Prioity.
    uint16 GetPortLacpPriority() const;
    bool SetPortLacpPriority(uint16 thePriority);

    // These methods are modifiers and accessors for 
    // the current Partner Active Flag.
    bool GetPartnerActiveFlag() const;
    bool SetPartnerActiveFlag(bool theFlag);    

    // These methods are modifiers and accessors for 
    // the current Partner System ID.
    CT_LacpSystemId GetPartnerSystemID() const;
    bool SetPartnerSystemID(CT_LacpSystemId theSystemID);

    // These methods are modifiers and accessors for 
    // the current Partner Port Prioity.
    uint16 GetPartnerPortPriority() const;
    bool SetPartnerPortPriority(uint16 thePriority);

    // These methods are modifiers and accessors for 
    // the current Partner Operational Key.
    uint32 GetPartnerOperationalKey() const;
    bool SetPartnerOperationalKey(uint32 theKey);

    // These methods are modifiers and accessors for 
    // the current Partner Port State.
    uint8 GetPartnerPortState() const;
    bool SetPartnerPortState(uint8 theState);

    // These methods are modifiers and accessors for 
    // the current Lag Actor System ID.
    CT_LacpSystemId GetLagActorSystemID() const;
    bool SetLagActorSystemID(CT_LacpSystemId theSystemID);

    // These methods are modifiers and accessors for 
    // the current Lag Actor System Prioity.
    uint16 GetLagActorSystemPriority() const;
    bool SetLagActorSystemPriority(uint16 thePriority);

    // These methods are modifiers and accessors for 
    // the current Lag Actor Operational Key.
    uint32 GetLagActorOperationalKey() const;
    bool SetLagActorOperationalKey(uint32 theKey);

    // These methods are modifiers and accessors for 
    // the current Lag Actor Admin Key.
    uint16 GetLagActorAdminKey() const;
    bool SetLagActorAdminKey(uint16 theKey);

    // These methods are modifiers and accessors for 
    // the current Lag Partner System ID.
    CT_LacpSystemId GetLagPartnerSystemID() const;
    bool SetLagPartnerSystemID(CT_LacpSystemId theSystemID);

    // These methods are modifiers and accessors for 
    // the current Lag Partner System Prioity.
    uint16 GetLagPartnerSystemPriority() const;
    bool SetLagPartnerSystemPriority(uint16 thePriority);

    // These methods are modifiers and accessors for 
    // the current Lag Partner Operational Key.
    uint32 GetLagPartnerOperationalKey() const;
    bool SetLagPartnerOperationalKey(uint32 theKey);

    // These methods are modifiers and accessors for 
    // the current Lag Partner Admin Key.
    uint16 GetLagPartnerAdminKey() const;
    bool SetLagPartnerAdminKey(uint16 theKey);

    // These methods are modifiers and accessors for 
    // the current Ethernet Sfp/Xfp Type.
    CT_ETH_SFP_XFP_TYPE GetEthSfpXfpType() const;
    bool SetEthSfpXfpType(CT_ETH_SFP_XFP_TYPE theType);

    // These methods are modifiers and accessors for 
    // the current value of whether Software Auto Neg is enabled.
    bool GetIsSoftwareAutoNegEnabled() const;
    void SetIsSoftwareAutoNegEnabled(CT_ETH_SFP_XFP_TYPE theType);

    //Debug Methods
    void Reset();
	virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The current Auto Negotiation Status.
    CT_TEL_MAC_AUTONEGSTATUS myAutoNegStatus;
    
    //The current Auto Negotiation Remote Signal Detected.
    CT_TEL_DETECTED myAutoNegRmtSignal;
    
    //The current operational ethernet rate.
    CT_TEL_daHz myOperRate;

    //The current operational duplex mode.
    CT_TEL_MAC_DUPLEX_MODE myOperDuplex;

    //The current operational flow control mode.
    CT_TEL_MAC_FLOWCTRL myOperFlowCtrl;

    //The current operational Auto Negotiation mode.
    bool myOperAutoNeg;

    //The current LinkFailRx state.  
    bool myLinkFailRx;

    //The current LACP Port State.
    CT_TEL_LacpPortState     myPortLacpState;

    //The current LACP Aggregation.
    CT_AGGRE_FIELD           myPortAggregationField;

    //The current LACP Port Prioity.
    uint16                   myPortLacpPriority;

    //The current Partner Active Flag.
    bool                     myPartnerActiveFlag;

    //The current Partner System ID.
    CT_LacpSystemId          myPartnerSystemID;

    //The current Partner Port Prioity.
    uint16                   myPartnerPortPriority;

    //The current Partner Operational Key.
    uint32                   myPartnerOperationalKey;

    //The current Partner Port State.
    uint8                    myPartnerPortState;

    //The current Lag Actor System ID.
    CT_LacpSystemId          myLagActorSystemID;

    //The current Lag Actor System Priority.
    uint16                   myLagActorSystemPriority;

    //The current Lag Actor Operational Key.
    uint32                   myLagActorOperationalKey;

    //The current Lag Actor Admin Key.
    uint16                   myLagActorAdminKey;

    //The current Lag Partner System ID.
    CT_LacpSystemId          myLagPartnerSystemID;

    //The current Lag Partner System Priority.
    uint16                   myLagPartnerSystemPriority;

    //The current Lag Partner Operational Key.
    uint32                   myLagPartnerOperationalKey;

    //The current Lag Partner Admin Key.
    uint16                   myLagPartnerAdminKey;

    // the current Ethernet Sfp/Xfp Type.
    CT_ETH_SFP_XFP_TYPE      myEthSfpXfpType;

    // the current value of Software Auto Neg is enabled.
    bool                     myIsSoftwareAutoNegEnabled;
};

#endif /* MON_MACSTATUS_H */

