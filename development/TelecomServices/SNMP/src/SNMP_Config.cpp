/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_Config.h>
#include <BaseClass/FC_TextStream.h>

//----------------------------------------------------------------------------
// SNMP_BbRCfg member function implementation
//----------------------------------------------------------------------------
SNMP_BbCfg::SNMP_BbCfg() :
SNMP_COLL_DISABLED(1),
SNMP_COLL_ENABLED(2)
{
    myCollMode = SNMP_COLL_DISABLED;
}

SNMP_BbCfg::~SNMP_BbCfg()
{
}

void SNMP_BbCfg::Init(restart_type theRestart)
{
    myCollMode = SNMP_COLL_DISABLED;
}

FC_Stream& SNMP_BbCfg::ReadObjectBinary (FC_Stream& theStream)
{
    theStream >> myCollMode;
    return theStream;
}

FC_Stream& SNMP_BbCfg::WriteObjectBinary (FC_Stream& theStream)
{
    theStream << myCollMode;
    return theStream;
}

istream& SNMP_BbCfg::ReadObject (istream& theStream)
{
    theStream >> FC_ExtractVar(myCollMode);
    return theStream;
}

ostream& SNMP_BbCfg::WriteObject (ostream& theStream)
{
    theStream << FC_InsertVar(myCollMode);
    return theStream;
}

