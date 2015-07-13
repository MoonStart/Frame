//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_HOPCONFIG_H
#define MON_HOPCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SONET64ByteTrace.h>

//This class contains configuration parameters that affects 
//how the monitoring of the SONET HOP (high order path) layer 
//is performed.
class MON_HopConfig : public MON_Config
{
public:

    //Constructor.
    MON_HopConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_HopConfig();

/////////////////////////////////////////////////////////////////////
// MON Config parameters (that are written to TSPII) moved to CFG for 
// perfomance reasons.
// Calls included BER SF Theshold, BER SD Threhhold, and Expected C2.
#if 0
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
#endif
/////////////////////////////////////////////////////////////////////

    //This method allows setting the current   
    //(received) HOP expected trace message.
    void SetExpectedTrace(const CT_SONET64ByteTrace& theTrace);

    //This method allows retrieving the current setting for 
    //the HOP expected trace message.
    const CT_SONET64ByteTrace GetExpectedTrace() const;


    //This method allows specifying if the TIM failure is monitored.
    void SetTIMMonitoringEnable(bool theTIMMonitoringState);

    //This method returns the current state of TIM monitoring enable option.
    bool GetTIMMonitoringEnable() const;


    // This method allows specifying if the hop is involved in a 
    // connection as the source of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsSrc(bool theState);

    // This method returns whether the hop is involved in a 
    // connection as the source of a connection
    bool GetIsConnectedAsSrc() const;

    // This method allows specifying if the hop is involved in a 
    // connection as the destination of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsDst(bool theState);

    // This method returns whether the hop is involved in a 
    // connection as the destination of a connection
    bool GetIsConnectedAsDst() const;


    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
/////////////////////////////////////////////////////////////////////
// See comment above on moving Mon Config parameters
#if 0
    //Signal degrade BER threshold
    CT_TEL_BERLevels mySdBerLevel;

    // Signal failure BER threshold
    CT_TEL_BERLevels mySfBerLevel;

    // The C2 byte to expect
    uint8 myExpectedC2;
#endif
/////////////////////////////////////////////////////////////////////


    //The 64 byte trace message (J1) to expect.
    CT_SONET64ByteTrace myExpectedTrace;

    //The TIM monitoring state configured.
    bool myTIMMonitoringEnable;

    // Is the facility involved in a connection as the source
    bool myIsConnectedAsSrc;

    // Is the facility involved in a connection as the destination
    bool myIsConnectedAsDst;
};

#endif /* HOPCONFIG_H */
