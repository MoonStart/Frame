/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBREQUEST_H
#define PM_BBREQUEST_H

using namespace std;

#include <TimeService/FC_Time.h>
#include <TimeService/FC_TimeService.h>
#include <CommonTypes/CT_PM_Definition.h>
#include "PM_BbObject.h"


//This class is responsible to keep the information about a 
//request sent from the Admin to the back-end. This class 
//keeps the RequestId and the request pending status. The only 
//information sent to the back-end is the RequestId. The other 
// attributes are used to control the request.
//##ModelId=3C1F6F730024
class PM_BbRequest : public PM_BbObject
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F73024B
    PM_BbRequest ( int dummy = 0, int dummy2 = 0);

    //Class default destructor.
    //##ModelId=3C1F6F730256
    virtual ~PM_BbRequest();

    //This method prepares the request information to send.
    //##ModelId=3C1F6F730274
    inline CT_PM_RequestId SendRequest();

    //Gets the Request Id.
    //##ModelId=3C1F6F730269
    inline CT_PM_RequestId GetRequestId() const;

    //Gets the request time of the last request.
	//##ModelId=3FA16110037F
    inline FC_Time GetRequestTime() const;

        //Resets all parameters.
    //##ModelId=3C1F6F730260
    virtual void Reset();

protected:

    //Stores the values to the binary stream.
    //##ModelId=3C1F6F7302C4
    FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7302D7
    FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3C1F6F7302E2
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7302F5
    virtual istream& ReadObject( istream& theStream );

private:

    //A request is about to be sent, increments the request 
    //counter.
    //##ModelId=3C1F6F730309
    CT_PM_RequestId ChangeRequestId();
    
    //The request id of the last request.
    //##ModelId=3C1F6F73031E
    CT_PM_RequestId myRequestId;

    //Time-stamp of the last request.
	//##ModelId=3FA161100390
    FC_Time myRequestTime;

};

//-----------------------------------------------------------------
//##ModelId=3C1F6F730269
inline CT_PM_RequestId PM_BbRequest::GetRequestId() const
{
    return myRequestId;

}

//-----------------------------------------------------------------
//##ModelId=3FA16110037F
inline FC_Time PM_BbRequest::GetRequestTime() const
{
    return myRequestTime;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F730274
inline CT_PM_RequestId PM_BbRequest::SendRequest()
{
    // Set the request time with the current time.
    myRequestTime.GetCurrentTime();

    return ChangeRequestId();

}

#endif //PM_BBREQUEST_H
