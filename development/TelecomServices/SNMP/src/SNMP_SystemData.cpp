/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_SystemData.h>
#include <BaseClass/FC_TextStream.h>

SNMP_BbSystemInfo::SNMP_BbSystemInfo() :
mySnmpEnableTimestamp(0)
{
}

SNMP_BbSystemInfo::~SNMP_BbSystemInfo()
{
}

void SNMP_BbSystemInfo::Init(restart_type theRestart)
{
    mySnmpEnableTimestamp = 0;
}

istream& SNMP_BbSystemInfo::ReadObject (istream& theStream)
{
    theStream >> FC_ExtractVar(mySnmpEnableTimestamp);
    return theStream;
}

ostream& SNMP_BbSystemInfo::WriteObject (ostream& theStream)
{
    theStream << FC_InsertVar(mySnmpEnableTimestamp);
    return theStream;
}

SNMP_BbSystemUpTime::SNMP_BbSystemUpTime() :
    mySysUpTime(0)
{
}

SNMP_BbSystemUpTime::~SNMP_BbSystemUpTime()
{
}

void SNMP_BbSystemUpTime::Init(restart_type theRestart)
{
    mySysUpTime = 0;
}

FC_Stream& SNMP_BbSystemUpTime::ReadObjectBinary (FC_Stream& theStream)
{
    theStream >> mySysUpTime;
    return theStream;
}

FC_Stream& SNMP_BbSystemUpTime::WriteObjectBinary (FC_Stream& theStream)
{
    theStream << mySysUpTime;
    return theStream;
}

istream& SNMP_BbSystemUpTime::ReadObject (istream& theStream)
{
    theStream >> FC_ExtractVar(mySysUpTime);
    return theStream;
}

ostream& SNMP_BbSystemUpTime::WriteObject (ostream& theStream)
{
    theStream << FC_InsertVar(mySysUpTime);
    return theStream;
}

