/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_HOPOBJECT_H
#define CFG_HOPOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SONET64ByteTrace.h>
#include <CommonTypes/CT_PM_Definition.h>

#include "CFG_Object.h"


//This object contains all the generic SONET/SDH High Order Path 
//section configuration for one HOP.
class CFG_Hop
: public CFG_Object
{

public:

	//Constructor.
    CFG_Hop(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Hop(void);

    // Set SPE mapping (in SDH world: Administrative Unit)
    void SetSpeMapping(CT_TEL_HopSpeMapping theMapping);

    // Get SPE mapping (in SHD world: Administrative Unit)
    CT_TEL_HopSpeMapping GetSpeMapping() const;

    void SetPMProfileId(CT_PMProfileTableId thePMPFId);
    CT_PMProfileTableId GetPMProfileId() const;

    // Set transmitted path trace message
    void SetSentTrace(const CT_SONET64ByteTrace& theSentTrace);

    // Get transmitted path trace message
    const CT_SONET64ByteTrace& GetSentTrace() const;
  
    // Enable/disable transmission of path trace message
    void SetSendTraceFlag(bool theSendTraceFlag);

    // Retrieve enable/disable status of transmission of path trace message
    bool GetSendTraceFlag() const;

    // Set force AIS-P enable/disable flag value
    void SetForceAISP(bool theForceAISP);

    // Get force AIS-P enable/disable flag value
    bool GetForceAISP() const;

    // Set force UNEQ-P enable/disable flag value
    void SetForceUNEQ(bool theForceUNEQ);

    // Get force UNEQ-P enable/disable flag value
    bool GetForceUNEQ() const;

    // Add in Monitoring Configurations also 
    //Set Signal Degrade threshold for BER
    void SetBerSdThreshold(CT_TEL_BERLevels theSdBerThreshold);

    //Set Signal Failure threshold for BER
    void SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold);

    //Get Signal Degrade threshold for BER
    CT_TEL_BERLevels GetBerSdThreshold() const;

    //Get Signal Failure threshold for BER
    CT_TEL_BERLevels GetBerSfThreshold() const;

    //Set the expected C2 byte
    void SetExpectedC2(uint8 theC2);

    //Get the expected C2 byte
    uint8 GetExpectedC2() const;

    // Enable/disable collection of path pointer justification data
    void SetPointerJustEnabled(bool thePointerJustEnabled);

    // Retrieve enable/disable status of path pointer justification data collection
    bool GetPointerJustEnabled() const;


	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	//The 64 byte trace message to transmit into J1 bytes.
    // Path trace message
	CT_SONET64ByteTrace mySentTrace;

    // SPE mapping (SDH world: Adminstrative unit)
    // STS-1, STS-3C
    CT_TEL_HopSpeMapping mySpeMapping;

    CT_PMProfileTableId myPMProfileId;

    // Sent trace enable flag (false = Do not send)
    bool mySendTraceFlag;

	//The AIS Path forced state configured (false = no AISP forced).
    bool myForceAISP;

	//The UNEQ Path forced state configured (false = no UNEQ-P forced).
    bool myForceUNEQ;

    // Add in Monitoring Configurations also
    //Signal degrade BER threshold
    CT_TEL_BERLevels mySdBerLevel;

    // Signal failure BER threshold
    CT_TEL_BERLevels mySfBerLevel;

    // The C2 byte to expect
    uint8 myExpectedC2;

    // Keeps the state of path pointer justification data collection
    bool myPointerJustEnabled;
};

#endif /* CFG_HOPOBJECT_H */

