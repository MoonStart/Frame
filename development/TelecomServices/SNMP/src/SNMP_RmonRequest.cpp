/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     .
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <SNMP/SNMP_RmonRequest.h>
#include <BaseClass/FC_TextStream.h>

using namespace std;

//--------------------------------------------------------------------------
// SNMP_BbRmonRequest member function implementation 
//--------------------------------------------------------------------------

//-----------------------------------------------------------------
SNMP_BbRmonRequest::SNMP_BbRmonRequest()
{
    Reset();
}

//-----------------------------------------------------------------
SNMP_BbRmonRequest::~SNMP_BbRmonRequest()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_BbRmonRequest::Reset()
{
    myIndex = 0;
    SNMP_BbRequest::Reset();
}

//-----------------------------------------------------------------
FC_Stream& SNMP_BbRmonRequest::WriteObjectBinary( FC_Stream& theStream )
{
    SNMP_BbRequest::WriteObjectBinary(theStream);
    theStream << myIndex;
    return theStream;
}
   
//-----------------------------------------------------------------
FC_Stream& SNMP_BbRmonRequest::ReadObjectBinary( FC_Stream& theStream )
{
    SNMP_BbRequest::ReadObjectBinary(theStream);
    theStream >> myIndex;
    return theStream;
}

//-----------------------------------------------------------------
ostream& SNMP_BbRmonRequest::WriteObject( ostream& theStream )
{
    SNMP_BbRequest::WriteObject(theStream);
    theStream   << FC_InsertVar(myIndex);
    return theStream;
}

//-----------------------------------------------------------------
istream& SNMP_BbRmonRequest::ReadObject( istream& theStream )
{
    SNMP_BbRequest::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myIndex);
    return theStream;
}


//--------------------------------------------------------------------------
// SNMP_BbRmonEhterStatsRequest member function implementation 
//--------------------------------------------------------------------------

//-----------------------------------------------------------------
SNMP_BbRmonEtherStatsRequest::SNMP_BbRmonEtherStatsRequest()
{
    Reset();
}

//-----------------------------------------------------------------
SNMP_BbRmonEtherStatsRequest::~SNMP_BbRmonEtherStatsRequest()
{
    // Nothing to do for now.
}

//--------------------------------------------------------------------------
// SNMP_BbRmonEhterHistRequest member function implementation 
//--------------------------------------------------------------------------

//-----------------------------------------------------------------
SNMP_BbRmonEtherHistRequest::SNMP_BbRmonEtherHistRequest()
{
    Reset();
}

//-----------------------------------------------------------------
SNMP_BbRmonEtherHistRequest::~SNMP_BbRmonEtherHistRequest()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_BbRmonEtherHistRequest::Reset()
{
    myNextSampleRequested = false;
    mySampleIndex = 0;
    SNMP_BbRmonRequest::Reset();
}

//-----------------------------------------------------------------
FC_Stream& SNMP_BbRmonEtherHistRequest::WriteObjectBinary( FC_Stream& theStream )
{
    SNMP_BbRmonRequest::WriteObjectBinary(theStream);
    theStream << mySampleIndex;
    theStream << myNextSampleRequested;
    return theStream;
}
   
//-----------------------------------------------------------------
FC_Stream& SNMP_BbRmonEtherHistRequest::ReadObjectBinary( FC_Stream& theStream )
{
    SNMP_BbRmonRequest::ReadObjectBinary(theStream);
    theStream >> mySampleIndex;
    theStream >> myNextSampleRequested;
    return theStream;
}

//-----------------------------------------------------------------
ostream& SNMP_BbRmonEtherHistRequest::WriteObject( ostream& theStream )
{
    SNMP_BbRmonRequest::WriteObject(theStream);
    theStream   << FC_InsertVar(mySampleIndex);
    theStream   << FC_InsertVar(myNextSampleRequested);
    return theStream;
}

//-----------------------------------------------------------------
istream& SNMP_BbRmonEtherHistRequest::ReadObject( istream& theStream )
{
    SNMP_BbRmonRequest::ReadObject(theStream);
    theStream   >> FC_ExtractVar(mySampleIndex);
    theStream   >> FC_ExtractVar(myNextSampleRequested);
    return theStream;
}


