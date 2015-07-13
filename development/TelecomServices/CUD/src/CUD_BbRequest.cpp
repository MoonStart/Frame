/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Configuration File Upload/Download.
 TARGET   :     All.
 AUTHOR   :     April, 2007 Jim Beck.
 DESCRIPTION:   CUD Parameter values class. Keep and set CUD parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "../CUD_BbRequest.h"


using namespace std;

//-----------------------------------------------------------------
CUD_BbRequest::CUD_BbRequest( int dummy, int dummy2  )
{
    Reset();
}

//-----------------------------------------------------------------
CUD_BbRequest::~CUD_BbRequest()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void CUD_BbRequest::Reset()
{
    myRequestId = NULL;
    myRequestTime.SetUTCTime(0);
}

//-----------------------------------------------------------------
CT_CUD_RequestId CUD_BbRequest::ChangeRequestId()
{
    myRequestId++;

    // Ensure that 0 is not part of the free running counter
    // serialized, since this value is a power up value only.
    if (myRequestId == 0)
    {
        myRequestId++;
    }

    return myRequestId;
}

//-----------------------------------------------------------------
FC_Stream& CUD_BbRequest::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myRequestId;

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& CUD_BbRequest::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myRequestId;

    return theStream;
}

//-----------------------------------------------------------------
ostream& CUD_BbRequest::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myRequestId);

    return theStream;
}

//-----------------------------------------------------------------
istream& CUD_BbRequest::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myRequestId);

    return theStream;
}

