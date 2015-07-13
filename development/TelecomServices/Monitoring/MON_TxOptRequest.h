// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TXOPTREQUEST_
#define _MON_TXOPTREQUEST_

#include "MON_Object.h"
#include "MON_Definitions.h"

//This class defines a request ID number. 
//It is used by on-demand transmit power request.
class MON_TxOptRequest
: public MON_Object
{
public:
    //Constructor.
    MON_TxOptRequest(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_TxOptRequest(void);

    //Start the On-Demand action.
    MON_RequestID RequestTxPower();
    
    //Retrieve the request ID.
    MON_RequestID GetRequestID() const;

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

	MON_RequestID myRequestID;

};

#endif /* _MON_TXOPTREQUEST_ */
