//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTUCONFIG_H
#define MON_OTUCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include "MON_OtuDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the optical transport unit (OTU) layer is performed.
class MON_OtuConfig 
: public MON_Config
{
public:
    //Constructor.
    MON_OtuConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OtuConfig();

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
    
    bool SetAisFailLayer(bool theState);

    bool GetAisFailLayer() const;   

    bool SetLofFailLayer(bool theState);

    bool GetLofFailLayer() const;   

    bool SetLomfFailLayer(bool theState);

    bool GetLomfFailLayer() const;

    bool SetFecmFailLayer(bool theState);

    bool GetFecmFailLayer() const;

    bool SetTimFailLayer(bool theState);

    bool GetTimFailLayer() const;
    
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
    //located in the Section Monitoring (SM) of the OTU layer.
    CT_G709Trace* myExpectedTracePtr;
    bool myTraceInUse;

    //The TIM monitoring state configured.
    bool myTIMMonitoringEnable;

    //The Layer Failure on TIM defect configured
    bool myLayerFailOnTIM;

    //The mismatch type of TIM
    CT_TEL_TimCriteriaMode myTIMCriteraMode;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;    
};

#endif /* MON_OTUCONFIG_H */
