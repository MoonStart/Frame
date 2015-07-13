/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_Data.h>
#include <BaseClass/FC_TextStream.h>

SNMP_BbData::SNMP_BbData() :
SNMP_COLL_DISABLED(1),
SNMP_COLL_ENABLED(2),
myRequestId(0),
myLastError(CT_SNMP_Des_NoError)
{
    myCollMode = SNMP_COLL_DISABLED;
}

SNMP_BbData::~SNMP_BbData()
{
    myCollMode = SNMP_COLL_DISABLED;
}

void SNMP_BbData::Init(restart_type theRestart)
{
}

void SNMP_BbData::ResetAll()
{
    myRequestId = 0;
    myLastError = CT_SNMP_Des_NoError;
    myCollMode = SNMP_COLL_DISABLED;
    myLastUpdateTime.SetUTCTime(0);
}

FC_Stream& SNMP_BbData::ReadObjectBinary (FC_Stream& theStream)
{
    int myLastErrorAsInt;
    theStream >> myRequestId;
    myLastUpdateTime.ReadObjectBinary(theStream);
    theStream >> myCollMode;
    theStream >> myLastErrorAsInt;

    myLastError = static_cast<CT_SNMP_DataErrorStatus> (myLastErrorAsInt);
    return theStream;
}

FC_Stream& SNMP_BbData::WriteObjectBinary (FC_Stream& theStream)
{
    int myLastErrorAsInt = static_cast<int> (myLastError);
    theStream << myRequestId;
    myLastUpdateTime.GetCurrentTime();
    myLastUpdateTime.WriteObjectBinary(theStream);
    theStream << myCollMode;
    theStream << myLastErrorAsInt;
    return theStream;
}

istream& SNMP_BbData::ReadObject (istream& theStream)
{
    int myLastErrorAsInt;
    theStream >> FC_ExtractVar(myRequestId);
    theStream >> FC_ExtractVar(myCollMode);
    theStream >> FC_ExtractVar(myLastErrorAsInt);

    myLastError = static_cast<CT_SNMP_DataErrorStatus> (myLastErrorAsInt);
    return theStream;
}

ostream& SNMP_BbData::WriteObject (ostream& theStream)
{
    int myLastErrorAsInt = static_cast<int> (myLastError);
    theStream << FC_InsertVar(myRequestId);
    myLastUpdateTime.WriteObject(theStream);
    theStream << endl;
    theStream << FC_InsertVar(myCollMode);
    theStream << FC_InsertVar(myLastErrorAsInt);
    return theStream;
}

