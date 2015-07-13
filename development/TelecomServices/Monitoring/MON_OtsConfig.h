//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTSCONFIG_H
#define MON_OTSCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>


//This class contains configuration parameters that affects 
//how the monitoring of the OTS layer is performed. 
//This layers handle forward error correction (FEC) 
//as well as add/remove the OTS overhead.
class MON_OtsConfig 
: public MON_Config
{
public:

	//Constructor.
    MON_OtsConfig(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OtsConfig(void);

  	//This method allows setting the current 
	//(received) section expected trace message.
	void SetExpectedTrace(const CT_G709Trace& theExpTrace);

	//This method allows retrieving the current setting for 
	//the  section expected trace message.
	const CT_G709Trace GetExpectedTrace() const;

	//This method allows specifying if the TIM failure is monitored.
    void SetTIMMonitoringEnable(bool theTIMMonitoringState);

	//This method returns the current state of TIM monitoring enable option.
    bool GetTIMMonitoringEnable() const;

    //Debug Methods
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
	//located in the Section Monitoring (SM) of the OTS layer.
	CT_G709Trace myExpectedTrace;

	//The TIM monitoring state configured.
    bool myTIMMonitoringEnable;

};

#endif /* MON_OTSCONFIG_H */
