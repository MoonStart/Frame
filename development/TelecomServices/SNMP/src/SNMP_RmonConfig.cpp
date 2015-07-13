
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_RmonConfig.h>
#include <BaseClass/FC_TextStream.h>

//----------------------------------------------------------------------------
// SNMP_BbRmonEtherCfg member function implementation
//----------------------------------------------------------------------------
SNMP_BbRmonEtherCfg::SNMP_BbRmonEtherCfg() :
SNMP_BbCfg()
{
    ResetAll();
}

SNMP_BbRmonEtherCfg::~SNMP_BbRmonEtherCfg()
{
}

void SNMP_BbRmonEtherCfg::ResetAll()
{
    ResetIndex();
    //ResetStatus();
}

void SNMP_BbRmonEtherCfg::Init(restart_type theRestart)
{
    ResetAll();
}

FC_Stream& SNMP_BbRmonEtherCfg::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbCfg::ReadObjectBinary(theStream);
    //int statusAsInt;
    theStream >> myIndex;
    //theStream >> statusAsInt;
   // myStatus = (CT_SNMP_EntryStatus) statusAsInt;

    return theStream;
}

FC_Stream& SNMP_BbRmonEtherCfg::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbCfg::WriteObjectBinary(theStream);
   // int statusAsInt = (int) myStatus;
    theStream << (static_cast<long> (myIndex));
   // theStream << statusAsInt;

    return theStream;
}

istream& SNMP_BbRmonEtherCfg::ReadObject (istream& theStream)
{
    SNMP_BbCfg::ReadObject(theStream);
   // int statusAsInt;
    theStream >> FC_ExtractVar(myIndex);
   // theStream >> FC_ExtractVar(statusAsInt); 
  //  myStatus = (CT_SNMP_EntryStatus) statusAsInt;

    return theStream;
}

ostream& SNMP_BbRmonEtherCfg::WriteObject (ostream& theStream)
{
    SNMP_BbCfg::WriteObject(theStream);
   // int statusAsInt = (int) myStatus;
    theStream << FC_InsertVar(myIndex);
   // theStream << FC_InsertVar(statusAsInt); 

    return theStream;
}

//----------------------------------------------------------------------------
// SNMP_BbRmonEtherHistCfg member function implementation
//----------------------------------------------------------------------------

SNMP_BbRmonEtherHistCfg::SNMP_BbRmonEtherHistCfg() :
  SNMP_BbRmonEtherCfg()
{
    ResetAll();
}

SNMP_BbRmonEtherHistCfg::~SNMP_BbRmonEtherHistCfg()
{
}

void SNMP_BbRmonEtherHistCfg::ResetAll()
{
    SNMP_BbRmonEtherCfg::ResetAll();

    ResetBucketsRequested();
    ResetInterval();
}

FC_Stream& SNMP_BbRmonEtherHistCfg::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonEtherCfg::ReadObjectBinary(theStream);

    theStream >> myBucketsRequested;
    theStream >> myInterval;

    return theStream;
}

FC_Stream& SNMP_BbRmonEtherHistCfg::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonEtherCfg::WriteObjectBinary(theStream);

    theStream << myBucketsRequested;
    theStream << myInterval;

    return theStream;
}

istream& SNMP_BbRmonEtherHistCfg::ReadObject (istream& theStream)
{
    SNMP_BbRmonEtherCfg::ReadObject(theStream);

    theStream >> FC_ExtractVar(myBucketsRequested);
    theStream >> FC_ExtractVar(myInterval);

    return theStream;
}

ostream& SNMP_BbRmonEtherHistCfg::WriteObject (ostream& theStream)
{    
    SNMP_BbRmonEtherCfg::WriteObject(theStream);

    theStream << FC_InsertVar(myBucketsRequested);
    theStream << FC_InsertVar(myInterval);

    return theStream;
}


//----------------------------------------------------------------------------
// SNMP_BbRmonEtherHistCfg member function implementation
//----------------------------------------------------------------------------

SNMP_BbRmonEtherStatsCfg::SNMP_BbRmonEtherStatsCfg() :
SNMP_BbRmonEtherCfg()
{
}

SNMP_BbRmonEtherStatsCfg::~SNMP_BbRmonEtherStatsCfg()
{
}

