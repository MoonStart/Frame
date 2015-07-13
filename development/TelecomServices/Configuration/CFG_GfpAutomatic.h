/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_GFPAUTOMATICOBJECT_H
#define CFG_GFPAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Definitions.h"
#include "CFG_Object.h"

//This object contains all the automatic configuration
//of one GFP interface.
class CFG_GfpAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_GfpAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_GfpAutomatic(void);

    //This method sets/clears the enable flag of 10B_ERR force mode.
    bool SetForce10BError(bool theForce10BError);

    //This method returns the current mode of 10B_ERR force mode
    bool GetForce10BError() const;

    //This method sets/clears the enable flag of GenericLayerFail force mode.
    bool SetForceGenericLayerFail(bool theForceGenericLayerFail);

    //This method returns the current mode of GenericLayerFail force mode
    bool GetForceGenericLayerFail() const;

    // This method sets the current client management frame type
    void SetForceClientMgmtFrame(CT_TEL_GfpClientMgmt theClientMgmtFrameType);

    // This method returns the curreht client managment frame type
    CT_TEL_GfpClientMgmt GetForceClientMgmtFrame() const;

    //This method sets/clears the idle code force mode
    bool SetForceIdle(bool theForceMode);

    //This method retrieves the idle code force mode
    bool GetForceIdle() const;

    //This method sets/clears the Link Fail Tx force mode
    bool SetForceLinkFailTx(bool theForceLinkFailTx);

    //This method retrieves the Link Fail Tx force mode
    bool GetForceLinkFailTx() const;

    //This method sets/clears the One Way Cross Connect to router mode.
    bool SetOneWayGbe(bool theOneWayGbe);

    //This method retrieves the One Way Cross Connect to router mode.
    bool GetOneWayGbe() const;

    //This method sets/clears the Remote Fault force mode
    bool SetForceRemoteFault(CT_GBE_REMOTE_FAULT theForceRemoteFault);

    // This method retrieves the Remote Fault force mode
    CT_GBE_REMOTE_FAULT GetForceRemoteFault() const;


    //This method sets/clears whether Auto Negotiation is set in the Mac Layer.
    bool SetMacAutoNegEnabled(bool theMacAutoNegEnabled);

    //This method retrieves whether Auto Negotiation is set in the Mac Layer.
    bool GetMacAutoNegEnabled() const;

    // This method stores the Port Index of the facilty when Gfp is pooled
    bool SetPortIndex(uint8 theIndex);

    // This method stores the Port Index of the facilty when Gfp is pooled
    uint8 GetPortIndex() const;

    //This method resets all attributes to their default value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // Set to true to enable 10B_ERR
    bool myForce10BError;

    // Set to true to enable Generic Layer Fail
    bool myForceGenericLayerFail;

    // Client management frame mode
    CT_TEL_GfpClientMgmt myClientMgmtFrameType;

	// Set to true to force idle codes
	bool myForceIdle;

    // Set to true to force Link Fail Tx CR0 to be sent.
    bool myForceLinkFailTx;

    // Set to indicate which Remote Fault should be forced.
    CT_GBE_REMOTE_FAULT myForceRemoteFault;

    // Set to true to indicate One Way Cross Connect to router.
    bool myOneWayGbe;


    // The reading whether Auto Negotiation is set in the Mac Layer.
    bool myMacAutoNegEnabled;

    // The Port Index of the facilty when Gfp are pooled
    uint8 myPortIndex;
};

#endif /* CFG_GFPAUTOMATICOBJECT_H */

