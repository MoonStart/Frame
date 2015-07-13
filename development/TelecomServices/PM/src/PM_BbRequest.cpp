/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "../PM_BbRequest.h"


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F73024B
PM_BbRequest::PM_BbRequest( int dummy, int dummy2  )
{
    Reset();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F730256
PM_BbRequest::~PM_BbRequest()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F730260
void PM_BbRequest::Reset()
{
    myRequestId = NULL;
    myRequestTime.SetUTCTime(0);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7302C4
FC_Stream& PM_BbRequest::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myRequestId;

    return theStream;

}
   
//-----------------------------------------------------------------
//##ModelId=3C1F6F7302D7
FC_Stream& PM_BbRequest::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myRequestId;

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7302E2
ostream& PM_BbRequest::WriteObject( ostream& theStream )
{

    theStream   << FC_InsertVar(myRequestId)
                << FC_InsertVar(myRequestTime);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7302F5
istream& PM_BbRequest::ReadObject( istream& theStream )
{

    theStream   >> FC_ExtractVar(myRequestId)
                >> FC_ExtractVar(myRequestTime);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F730309
CT_PM_RequestId PM_BbRequest::ChangeRequestId()
{
    myRequestId++;

    // Ensure that 0 is not part of the free running counter
    // serialized, since this value is a power up value only.
    if (myRequestId == 0)
    {
        myRequestId++;
    }

    // fc_cout << "myRequestId = " << myRequestId << endl;
    return myRequestId;

}
