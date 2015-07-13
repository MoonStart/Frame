/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     .
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <SNMP/SNMP_Request.h>

using namespace std;

//--------------------------------------------------------------------------
// SNMP_BbRequest member function implementation 
//--------------------------------------------------------------------------

//-----------------------------------------------------------------
SNMP_BbRequest::SNMP_BbRequest()
{
    Reset();
}

//-----------------------------------------------------------------
SNMP_BbRequest::~SNMP_BbRequest()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_BbRequest::Reset()
{
    myRequestId = NULL;
    myRequestTime.SetUTCTime(0);
}

void SNMP_BbRequest::Init(restart_type theRestart)
{
}

//-----------------------------------------------------------------
FC_Stream& SNMP_BbRequest::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myRequestId;
    return theStream;
}
   
//-----------------------------------------------------------------
FC_Stream& SNMP_BbRequest::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myRequestId;
    return theStream;
}

//-----------------------------------------------------------------
ostream& SNMP_BbRequest::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myRequestId);
    /*
    theStream   << FC_InsertVar(myRequestId)
                << FC_InsertVar(myRequestTime);
                */
    return theStream;
}

//-----------------------------------------------------------------
istream& SNMP_BbRequest::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myRequestId);
    /*
    theStream   >> FC_ExtractVar(myRequestId)
                >> FC_ExtractVar(myRequestTime);
                */
    return theStream;
}

//-----------------------------------------------------------------
uint32 SNMP_BbRequest::ChangeRequestId()
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

