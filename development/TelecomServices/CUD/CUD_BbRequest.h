/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Configuration File Upload/Download.
 TARGET   :     All.
 AUTHOR   :     April, 2007 Jim Beck
 DESCRIPTION:   CUD Parameter values class. Keep and set CUD parameter values.
--------------------------------------------------------------------------*/
#ifndef CUD_BBREQUEST_H
#define CUD_BBREQUEST_H

using namespace std;

#include <TimeService/FC_Time.h>
#include <TimeService/FC_TimeService.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include "CUD_BbObject.h"


// This class is responsible to keep the information about a 
// request sent from the Admin to the back-end. This class 
// keeps the RequestId and the request pending status. The only 
// information sent to the back-end is the RequestId. The other 
// attributes are used to control the request.

class CUD_BbRequest : public CUD_BbObject
{

public:

    // Class default constructor.
    CUD_BbRequest ( int dummy = 0, int dummy2 = 0);

    // Class default destructor.
    virtual ~CUD_BbRequest();

    // This method prepares the request information to send.
    inline CT_CUD_RequestId SendRequest();

    // Gets the Request Id.
    inline CT_CUD_RequestId GetRequestId() const;

    //Gets the request time of the last request.
    inline FC_Time GetRequestTime() const;

    //Resets all parameters.
    virtual void Reset();

protected:

    //Stores the values to the binary stream.
    FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the values from the stream.
    FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    // A request is about to be sent, increments the request 
    // counter.
    CT_CUD_RequestId ChangeRequestId();
    
    // The request id of the last request.
    CT_CUD_RequestId myRequestId;

    // Time-stamp of the last request.
    FC_Time myRequestTime;

};

//-----------------------------------------------------------------
inline CT_CUD_RequestId CUD_BbRequest::GetRequestId() const
{
    return myRequestId;
}

//-----------------------------------------------------------------
inline FC_Time CUD_BbRequest::GetRequestTime() const
{
    return myRequestTime;
}

//-----------------------------------------------------------------
inline CT_CUD_RequestId CUD_BbRequest::SendRequest()
{
    // Set the request time with the current time.
    myRequestTime.GetCurrentTime();

    return ChangeRequestId();
}

#endif // CUD_BBREQUEST_H
