//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RSSTATUS_H
#define MON_RSSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SDH16ByteTrace.h>
#include "MON_Object.h"


//This class hold the status value (trace message, levels) for the RS layer.
class MON_RsStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_RsStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_RsStatus();

    //This method returns the current trace message received.
    const CT_SDH16ByteTrace GetReceivedTrace() const ;
    bool SetReceivedTrace(const CT_SDH16ByteTrace& theTrace) ;

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
    CT_SDH16ByteTrace myReceivedTraceMessage;
};

#endif /* MON_RSSTATUS_H */

