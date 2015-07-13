//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHCONFIG_H
#define MON_OCHCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>

//This class contains configuration parameters that affects 
//how the monitoring of the optical channel layer is performed.
class MON_OchConfig 
: public MON_Config
{
public:
	//Constructor.
    MON_OchConfig(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OchConfig(void);

    //Sets the loss of input power S/N ratio threshold.
	void SetLossOfInputPowerThreshold(CT_TEL_mBm thePowerThreshold);
	//Sets the loss of input power threshold.
	void SetMinimumSNRatio(CT_TEL_mBm theMinimumSNRatio);

	//Returns the loss of input power threshold.
	CT_TEL_mBm GetLossOfInputPowerThreshold();
	//Returns the minimum S/N ratio threshold.
	CT_TEL_mBm GetMinimumSNRatio();

	void SetExpectedChannelId(CT_Wavelength theExpectedChannelId);
    CT_Wavelength GetExpectedChannelId();

    //Those methods are used to get and set the state of the Trace Id Interference feature. (DEBUG PURPOSE)
    void SetInterferenceEnable(bool theInterferenceEnable);
    bool GetInterferenceEnable(void);


	//Resets all attributes to default value.
    virtual void Reset();

    //Debug Methods
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//This is the minimum value at which a Loss of input 
	//power should be declared.
	CT_TEL_mBm myLossOfInputPowerThreshold;
	CT_TEL_mBm myMinimumSNRatio;
    CT_Wavelength myExpectedChannelId;

    //Debug attributes
    bool myInterferenceEnable; //True if Trace Id interference feature is enable    

	void Refresh();
};

#endif /* MON_OCHCONFIG_H */
