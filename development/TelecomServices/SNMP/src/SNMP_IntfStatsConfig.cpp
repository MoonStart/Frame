/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_IntfStatsConfig.h>
#include <BaseClass/FC_TextStream.h>

//----------------------------------------------------------------------------
// SNMP_BbIntfStatsCfg member function implementation
//----------------------------------------------------------------------------
SNMP_BbIntfStatsCfg::SNMP_BbIntfStatsCfg() :
SNMP_BbCfg()
{
    ResetAll();
}

SNMP_BbIntfStatsCfg::~SNMP_BbIntfStatsCfg()
{
}

void SNMP_BbIntfStatsCfg::ResetAll()
{
    ResetAdminStatus();
}

void SNMP_BbIntfStatsCfg::Init(restart_type theRestart)
{
    ResetAll();
}

FC_Stream& SNMP_BbIntfStatsCfg::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbCfg::ReadObjectBinary(theStream);
    int adminStatusAsInt;
    theStream >> adminStatusAsInt;
    myAdminStatus = (CT_SNMP_AdminStatus) adminStatusAsInt;

    return theStream;
}

FC_Stream& SNMP_BbIntfStatsCfg::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbCfg::WriteObjectBinary(theStream);
    int adminStatusAsInt = (int) myAdminStatus;
    theStream << adminStatusAsInt;

    return theStream;
}

istream& SNMP_BbIntfStatsCfg::ReadObject (istream& theStream)
{
    SNMP_BbCfg::ReadObject(theStream);
    int adminStatusAsInt;
    theStream >> FC_ExtractVar(adminStatusAsInt); 
    myAdminStatus = (CT_SNMP_AdminStatus) adminStatusAsInt;

    return theStream;
}

ostream& SNMP_BbIntfStatsCfg::WriteObject (ostream& theStream)
{
    SNMP_BbCfg::WriteObject(theStream);
    int adminStatusAsInt = (int) myAdminStatus;
    theStream << FC_InsertVar(adminStatusAsInt); 

    return theStream;
}

