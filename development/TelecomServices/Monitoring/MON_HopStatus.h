//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_HOPSTATUS_H
#define MON_HOPSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SONET64ByteTrace.h>
#include <ExecutionSupport/FC_BaseTimer.h>
#include "MON_Object.h"


//This class hold the status value (Rx Trace message) for the HOP layer.
class MON_HopStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_HopStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_HopStatus();


    //This method returns the current trace message received.
    const CT_SONET64ByteTrace GetReceivedTrace() const ;
    bool SetReceivedTrace(const CT_SONET64ByteTrace& theTrace) ;

    //Added to debug how long Automatic Action is taking.
    void SetProcessTime(const FC_Milliseconds& theTime) ;
    bool IsDebugFlagSet() const;

    //Debug Methods
    void Reset();
	virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The current trace message monitored.
    CT_SONET64ByteTrace myReceivedTraceMessage;

    //Added to debug how long Automatic Action is taking.
    bool myDebugFlag;
    FC_Milliseconds myLastTime;
    FC_Milliseconds myShortestTime;  
    FC_Milliseconds myLongestTime;

};

#endif /* MON_HOPSTATUS_H */

