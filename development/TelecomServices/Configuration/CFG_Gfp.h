/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_GFPOBJECT_H
#define CFG_GFPOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <vector>

#include "CFG_Object.h"


//This object contains all the generic framing procedure
// configuration for one port.
class CFG_Gfp
: public CFG_Object
{

public:

	//Constructor.
    CFG_Gfp(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Gfp(void);

    // Set GFP framing mode 
    bool SetFramingMode(CT_TEL_GfpFramingMode theFramingMode);

    // Set GFP enable mode
    bool SetEnableMode(bool theEnableMode);

    //Get GFP framing mode
    CT_TEL_GfpFramingMode GetFramingMode() const;

    // Get GFP enable mode
    bool GetEnableMode() const;

    //Set Auto-Negotiation
    bool SetAutoNegotiationEnabled(bool theAutoNegotiationEnabled);

    //Get Auto-Negotiation
    bool GetAutoNegotiationEnabled() const;

    //This method sets the Auto-Negotiation Session Counter.
    bool SetAutoNegSessionCounter(uint32 theAutoNegSessionCounter);

    //This method returns the Auto-Negotiation Session Counter.
    uint32 GetAutoNegSessionCounter() const;

    // This method sets the superblock size.
    bool SetSuperblockSize(uint32 theSuperblockSize);

    // This method retrieves the current setting of superblock size.
    uint32 GetSuperblockSize() const;

    // Set Pause frame discard .
    bool SetPauseDiscardEnabled(bool thePauseDiscardEnabled);

    // Get Pause frame discard .
    bool GetPauseDiscardEnabled() const;

    //Set GFP User Payload Id
    bool SetUpi(CT_TEL_GfpUpiId theUpi);

    //Get Gfp User Payload
    CT_TEL_GfpUpiId GetUpi() const;


    //Set GFP Linear Extention Enabled
    bool SetExtEnabled(bool theExtEnabled);

    //Get Gfp Linear Extention Enabled    
    bool GetExtEnabled() const;

    //Set GFP Linear Extention Channel ID
    bool SetExtChannelId(uint8 theExternalChannelId);

    //Get Gfp Linear Extention Channel ID
    uint8 GetExtChannelId() const;

    // This method allows enabling or disabling the Ignore GFP defect flag.
    // When set, CFG/MON will not force insert GFP-LOS/LOSYNC when client side has 8GFC LOS/LOSYNC. Now 
    // it is added for HDTG FC8G.
    bool SetIgnoreLosLosyncFlag(bool theIgnoreFlag);

    // This method allows retrieving the state of Ignore GFP defect flag.
    bool GetIgnoreLosLosyncFlag() const;


	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

    //Added to debug how long Automatic Action is taking.
    void SetDebugFlagSet(bool theDebugEnable);
    bool IsDebugFlagSet() const;
    void SetProcessTime(const uint32 theTime, bool theRealTimeDefectsRead, uint32 theRealTimeDefectReadPasses, uint32 theNormalReadPasses);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    // GFP Framing Mode
    CT_TEL_GfpFramingMode myFramingMode;

    // GFP enable status
    bool myEnableMode;

    // Auto-Negotiation Enabled
    bool myAutoNegotiationEnabled;
    
    // The session number for Auto-Negotiation on a facility.
    uint32 myAutoNegSessionCounter;

    // GFP Superblock size
    uint32 mySuperblockSize;

    // Pause frame discard Enabled
    bool myPauseDiscardEnabled;

    // UPI
    CT_TEL_GfpUpiId myUpi;

    // The Linear Extention Enabled
    bool myExtEnabled;

    // The Linear Extention Channel ID
    uint8 myExtChannelId;

    //Added to debug how long Automatic Action is taking.
    bool myDebugFlag;

    //For HDTG FC8G, CFG will not force insert GFP-LOS/LOSYNC when client side has 8GFC LOS/LOSYNC. FW will handle it.
    bool myIgnoreLosLosync;

    uint32 myLastTime;
    uint32 myShortestTime;
    uint32 myLongestTime;
    uint32 myRealTimeDefLastTime;
    uint32 myRealTimeDefShortestTime;
    uint32 myRealTimeDefLongestTime;
    uint32 myRealTimeDefectReadPasses;
    uint32 myNormalReadPasses; 
};

#endif /* CFG_GFPOBJECT_H */

