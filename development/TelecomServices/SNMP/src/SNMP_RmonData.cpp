
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_RmonData.h>
#include <BaseClass/FC_TextStream.h>

SNMP_BbRmonData::SNMP_BbRmonData() :
    SNMP_BbData()
{
}

SNMP_BbRmonData::~SNMP_BbRmonData()
{
}

void SNMP_BbRmonData::Init(restart_type theRestart)
{
}

void SNMP_BbRmonData::ResetAll()
{
    SNMP_BbData::ResetAll();
    myIndex = 0;
}

FC_Stream& SNMP_BbRmonData::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbData::ReadObjectBinary(theStream);
    theStream >> myIndex;
    return theStream;
}

FC_Stream& SNMP_BbRmonData::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbData::WriteObjectBinary(theStream);
    theStream << myIndex;
    return theStream;
}

istream& SNMP_BbRmonData::ReadObject (istream& theStream)
{
    SNMP_BbData::ReadObject(theStream);
    theStream >> FC_ExtractVar(myIndex);
    return theStream;
}

ostream& SNMP_BbRmonData::WriteObject (ostream& theStream)
{
    SNMP_BbData::WriteObject(theStream);
    theStream << FC_InsertVar(myIndex);
    return theStream;
}

