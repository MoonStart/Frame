//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RSCONFIG_H
#define MON_RSCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SDH16ByteTrace.h>
#include "MON_RsDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the SDH Regenerator Section (or SONET 
//section) layer is performed.
class MON_RsConfig 
: public MON_Config
{
public:

    //Constructor.
    MON_RsConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_RsConfig();

    //This method allows setting the current   
    //(received) section expected trace message.
    bool SetExpectedTrace(const CT_SDH16ByteTrace& theTrace);

    //This method allows retrieving the current setting for 
    //the  section expected trace message.
    const CT_SDH16ByteTrace GetExpectedTrace() const;

    //This method allows specifying if the TIM failure is monitored.
    bool SetTIMMonitoringEnable(bool theTIMMonitoringState);

    //This method returns the current state of TIM monitoring enable option.
    bool GetTIMMonitoringEnable() const;

    //This method allows specifying if the TIM defect fails the layer.
    bool SetLayerFailOnTIM(bool theLayerFailOnTIM);

    //This method returns the current state of Layer failure on TIM option.
    bool GetLayerFailOnTIM() const;

    // This method allows specifying if the facility is involved in a 
    // connection as the source of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsSrc(bool theState);

    // This method returns whether the facility is involved in a 
    // connection as the source of a connection
    bool GetIsConnectedAsSrc() const;

    // This method allows specifying if the facility is involved in a 
    // connection as the destination of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsDst(bool theState);

    // This method returns whether the facility is involved in a 
    // connection as the destination of a connection
    bool GetIsConnectedAsDst() const;

    bool SetLosFailLayer(bool theState);

    bool GetLosFailLayer() const;

    bool SetLofFailLayer(bool theState);

    bool GetLofFailLayer() const;

    bool SetTlabAisFailLayer(bool theState);

    bool GetTlabAisFailLayer() const;

    bool SetGenAisFailLayer(bool theState);

    bool GetGenAisFailLayer() const;

    bool SetTimFailLayer(bool theState);

    bool GetTimFailLayer() const;

    bool SetLfFailLayer(bool theState);

    bool GetLfFailLayer() const;

    bool SetInternalLofFailLayer(bool theState);

    bool GetInternalLofFailLayer() const;

    bool SetRfFailLayer(bool theState);

    bool GetRfFailLayer() const;

    uint16 GetFailLayerBitMask() const;
    
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
    //The 16 byte trace message (J0) to expect.
    CT_SDH16ByteTrace myExpectedTrace;

    //The TIM monitoring state configured.
    bool myTIMMonitoringEnable;

    //The Layer Failure on TIM defect configured
    bool myLayerFailOnTIM;

    // Is the facility involved in a connection as the source
    bool myIsConnectedAsSrc;

    // Is the facility involved in a connection as the destination
    bool myIsConnectedAsDst;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;
};

#endif /* MON_OTUCONFIG_H */
