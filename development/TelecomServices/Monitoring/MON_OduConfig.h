//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_ODUCONFIG_H
#define MON_ODUCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include "MON_OduDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the optical data unit (ODU) layer is performed.
class MON_OduConfig 
: public MON_Config
{
public:
    //Constructor.
    MON_OduConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OduConfig();

    //This method allows setting the current 
    //(received) section expected trace message.
    bool SetExpectedTrace(const CT_G709Trace& theExpTrace);
    bool DeleteExpectedTrace();

    //This method allows retrieving the current setting for 
    //the  section expected trace message.
    CT_G709Trace & GetExpectedTrace() const;

    //This method allows specifying if the TIM failure is monitored.
    bool SetTIMMonitoringEnable(bool theTIMMonitoringState);

    //This method returns the current state of TIM monitoring enable option.
    bool GetTIMMonitoringEnable() const;

    //This method allows specifying what kind of the TIM failure is monitored.
    bool SetTimCriteria(const CT_TEL_TimCriteriaMode& theTimCriteria);

    //This method returns the current type of TIM monitoring.
    const CT_TEL_TimCriteriaMode GetTimCriteria() const;

    //This method allows specifying if the TIM defect fails the layer.
    bool SetLayerFailOnTIM(bool theLayerFailOnTIM);

    //This method returns the current state of Layer failure on TIM option.
    bool GetLayerFailOnTIM() const;

    //This method allows specifying if the ODU layer is locked.
    bool SetLayerLocked(bool theState);

    //This method returns the current state of layer lock.
    bool GetLayerLocked() const;

    //This method sets the Odu Terminating flag of the facility (YES or NO).
    bool SetIsMonOduTerm(bool theIsMonOduTerm);

    //This method returns the Odu Terminating flag of the facility.
    bool GetIsMonOduTerm() const;

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

    bool SetAisFailLayer(bool theState);

    bool GetAisFailLayer() const;

    bool SetLckFailLayer(bool theState);

    bool GetLckFailLayer() const;

    bool SetOciFailLayer(bool theState);

    bool GetOciFailLayer() const;

    bool SetPlmFailLayer(bool theState);

    bool GetPlmFailLayer() const;

    bool SetGenAisFailLayer(bool theState);

    bool GetGenAisFailLayer() const;

    bool SetMfiFailLayer(bool theState);

    bool GetMfiFailLayer() const;

    bool SetTimFailLayer(bool theState);

    bool GetTimFailLayer() const;

    bool SetInternalAisFailLayer(bool theState);

    bool GetInternalAisFailLayer() const;

    bool GetMsimFailLayer() const;

    bool SetMsimFailLayer(bool theState);

    bool GetLoflomFailLayer() const;
    
    bool SetLoflomFailLayer(bool theState);
    
    uint16 GetFailLayerBitMask() const;

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //The 64 byte trace message to expect. The structure of 
    //this trace is conform to G.709 TTI definition. It is 
    //located in the Path Monitoring (PM) of the ODU layer.
    CT_G709Trace* myExpectedTracePtr;
    bool myTraceInUse;

    //The TIM monitoring state configured.
    bool myTIMMonitoringEnable;

    //The Layer Failure on TIM defect configured
    bool myLayerFailOnTIM;

    //The layer is locked configured
    bool myLayerLocked;

    //Set to true to indicate that the facility is Terminating Odu Monitoring.
    bool myIsMonOduTerm;

    // Is the facility involved in a connection as the source
    bool myIsConnectedAsSrc;

    // Is the facility involved in a connection as the destination
    bool myIsConnectedAsDst;

    //The mismatch type of TIM
    CT_TEL_TimCriteriaMode myTIMCriteriaMode;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;    
};

#endif /* MON_ODUCONFIG_H */

