// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OCHREQUEST_
#define _MON_OCHREQUEST_

#include "MON_Config.h"
#include "MON_Definitions.h"
#include <CommonTypes/CT_CardStatusMonitoring.h>

//This class defines a pilot tone ID and a request ID number. 
//It is used by on-demand pilot tone power request.
class MON_OchRequest 
: public MON_Config
{
public:
	//Constructor.
    MON_OchRequest(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OchRequest(void);

    virtual MON_RequestID SetChannelId(CT_Wavelength theChannelId, bool theInterferenceAnalyserEnable = true);
    MON_RequestID GetRequestID() const;

    //Set the interferance analyser state
    void SetInterferenceAnalyserEnable(bool theInterferenceAnalyserEnable);
    bool GetInterferenceAnalyserEnable() const;

	//Returns the expected pilot tone frequency.
    CT_Wavelength GetChannelId() const;


    void Reset();

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	MON_RequestID myRequestID;

    bool myInterferenceAnalyserEnable;
	
    //The pilot to frequency to expect.
	CT_Wavelength myChannelId;
};

#endif /* _INC_MON_OCHREQUEST_3C4825D403BB_INCLUDED */
