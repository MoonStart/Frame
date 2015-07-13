/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_IntfStatsData.h>
#include <BaseClass/FC_TextStream.h>

SNMP_BbIntfStatsData::SNMP_BbIntfStatsData() :
SNMP_BbData()
{
    ResetAll();
}

SNMP_BbIntfStatsData::~SNMP_BbIntfStatsData()
{
}

void SNMP_BbIntfStatsData::Init(restart_type theRestart)
{
}

void SNMP_BbIntfStatsData::ResetAll()
{
     SNMP_BbData::ResetAll();
     ResetMtu();
     ResetSpeed();
     ResetInOctets();
     ResetInUCastPkts();
     ResetInDiscards();
     ResetInErrors();
     ResetInUnknownProtos();
     ResetOutOctets();
     ResetOutUCastPkts();
     ResetOutDiscards();
     ResetOutErrors();
     ResetInMulticastPkts();
     ResetInBroadcastPkts();
     ResetOutMulticastPkts();
     ResetOutBroadcastPkts();
     ResetHCInOctets();
     ResetHCInUCastPkts();
     ResetHCInMulticastPkts();
     ResetHCInBroadcastPkts();
     ResetHCOutOctets();
     ResetHCOutUCastPkts();
     ResetHCOutMulticastPkts();
     ResetHCOutBroadcastPkts();
     ResetHighSpeed();
     ResetDiscontinuityTime();
     ResetLastChange();
     ResetConnectorPresent();
     myFirstSample = true;
}

FC_Stream& SNMP_BbIntfStatsData::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbData::ReadObjectBinary(theStream);

    int myConnectorPresentAsInt;
    int myAdminStatusAsInt;
    int myOperStatusAsInt;
    theStream >>  myMtu;
    theStream >>  mySpeed;
    theStream >>  myInOctets;
    theStream >>  myInUCastPkts;
    theStream >>  myInDiscards;
    theStream >>  myInErrors;
    theStream >>  myInUnknownProtos;
    theStream >>  myOutOctets;
    theStream >>  myOutUCastPkts;
    theStream >>  myOutDiscards;
    theStream >>  myOutErrors;
    theStream >>  myInMulticastPkts;
    theStream >>  myInBroadcastPkts;
    theStream >>  myOutMulticastPkts;
    theStream >>  myOutBroadcastPkts;
    theStream >>  myHighSpeed;
    theStream >>  myConnectorPresentAsInt;
    theStream >>  myAdminStatusAsInt;
    theStream >>  myOperStatusAsInt;
    theStream >>  myDiscontinuityTime;
    myHCInOctets.ReadObjectBinary(theStream);
    myHCInUCastPkts.ReadObjectBinary(theStream);
    myHCInMulticastPkts.ReadObjectBinary(theStream);
    myHCInBroadcastPkts.ReadObjectBinary(theStream);
    myHCOutOctets.ReadObjectBinary(theStream);
    myHCOutUCastPkts.ReadObjectBinary(theStream);
    myHCOutMulticastPkts.ReadObjectBinary(theStream);
    myHCOutBroadcastPkts.ReadObjectBinary(theStream);
    myPhysAddress.ReadObjectBinary(theStream);
    myConnectorPresent = static_cast<CT_SNMP_TruthValue> (myConnectorPresentAsInt);
    myAdminStatus = static_cast<CT_SNMP_AdminStatus> (myAdminStatusAsInt);
    myOperStatus = static_cast<CT_SNMP_OperStatus> (myOperStatusAsInt);
    return theStream;
}

FC_Stream& SNMP_BbIntfStatsData::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbData::WriteObjectBinary(theStream);
    int myConnectorPresentAsInt = static_cast<int> (myConnectorPresent);
    int myAdminStatusAsInt = static_cast<int> (myAdminStatus);
    int myOperStatusAsInt = static_cast<int> (myOperStatus);
    theStream <<  myMtu;
    theStream <<  mySpeed;
    theStream <<  myInOctets;
    theStream <<  myInUCastPkts;
    theStream <<  myInDiscards;
    theStream <<  myInErrors;
    theStream <<  myInUnknownProtos;
    theStream <<  myOutOctets;
    theStream <<  myOutUCastPkts;
    theStream <<  myOutDiscards;
    theStream <<  myOutErrors;
    theStream <<  myInMulticastPkts;
    theStream <<  myInBroadcastPkts;
    theStream <<  myOutMulticastPkts;
    theStream <<  myOutBroadcastPkts;
    theStream <<  myHighSpeed;
    theStream <<  myConnectorPresentAsInt;
    theStream <<  myAdminStatusAsInt;
    theStream <<  myOperStatusAsInt;
    theStream <<  myDiscontinuityTime;
    myHCInOctets.WriteObjectBinary(theStream);
    myHCInUCastPkts.WriteObjectBinary(theStream);
    myHCInMulticastPkts.WriteObjectBinary(theStream);
    myHCInBroadcastPkts.WriteObjectBinary(theStream);
    myHCOutOctets.WriteObjectBinary(theStream);
    myHCOutUCastPkts.WriteObjectBinary(theStream);
    myHCOutMulticastPkts.WriteObjectBinary(theStream);
    myHCOutBroadcastPkts.WriteObjectBinary(theStream);
    myPhysAddress.WriteObjectBinary(theStream);
      
    return theStream;
}

ostream& SNMP_BbIntfStatsData::WriteObject (ostream& theStream)
{
    SNMP_BbData::WriteObject(theStream);
    int myConnectorPresentAsInt = static_cast<int> (myConnectorPresent);
    int myAdminStatusAsInt = static_cast<int> (myAdminStatus);
    int myOperStatusAsInt = static_cast<int> (myOperStatus);

    theStream <<  FC_InsertVar(myMtu);
    theStream <<  FC_InsertVar(mySpeed);
    theStream <<  FC_InsertVar(myInOctets);
    theStream <<  FC_InsertVar(myInUCastPkts);
    theStream <<  FC_InsertVar(myInDiscards);
    theStream <<  FC_InsertVar(myInErrors);
    theStream <<  FC_InsertVar(myInUnknownProtos);
    theStream <<  FC_InsertVar(myOutOctets);
    theStream <<  FC_InsertVar(myOutUCastPkts);
    theStream <<  FC_InsertVar(myOutDiscards);
    theStream <<  FC_InsertVar(myOutErrors);
    theStream <<  FC_InsertVar(myInMulticastPkts);
    theStream <<  FC_InsertVar(myInBroadcastPkts);
    theStream <<  FC_InsertVar(myOutMulticastPkts);
    theStream <<  FC_InsertVar(myOutBroadcastPkts);
    theStream <<  FC_InsertVar(myConnectorPresentAsInt);
    theStream <<  FC_InsertVar(myAdminStatusAsInt);
    theStream <<  FC_InsertVar(myOperStatusAsInt);
    theStream <<  FC_InsertVar(myDiscontinuityTime);
    theStream <<  FC_InsertVar(myHighSpeed);
    myHCInOctets.WriteObject(theStream);
    myHCInUCastPkts.WriteObject(theStream);
    myHCInMulticastPkts.WriteObject(theStream);
    myHCInBroadcastPkts.WriteObject(theStream);
    myHCOutOctets.WriteObject(theStream);
    myHCOutUCastPkts.WriteObject(theStream);
    myHCOutMulticastPkts.WriteObject(theStream);
    myHCOutBroadcastPkts.WriteObject(theStream);
    myPhysAddress.WriteObject(theStream);
      
    return theStream;
}

istream& SNMP_BbIntfStatsData::ReadObject (istream& theStream)
{
    SNMP_BbData::ReadObject(theStream);

    int myConnectorPresentAsInt;
    int myAdminStatusAsInt;
    int myOperStatusAsInt;
    theStream >>  FC_ExtractVar(myMtu);
    theStream >>  FC_ExtractVar(mySpeed);
    theStream >>  FC_ExtractVar(myInOctets);
    theStream >>  FC_ExtractVar(myInUCastPkts);
    theStream >>  FC_ExtractVar(myInDiscards);
    theStream >>  FC_ExtractVar(myInErrors);
    theStream >>  FC_ExtractVar(myInUnknownProtos);
    theStream >>  FC_ExtractVar(myOutOctets);
    theStream >>  FC_ExtractVar(myOutUCastPkts);
    theStream >>  FC_ExtractVar(myOutDiscards);
    theStream >>  FC_ExtractVar(myOutErrors);
    theStream >>  FC_ExtractVar(myInMulticastPkts);
    theStream >>  FC_ExtractVar(myInBroadcastPkts);
    theStream >>  FC_ExtractVar(myOutMulticastPkts);
    theStream >>  FC_ExtractVar(myOutBroadcastPkts);
    theStream >>  FC_ExtractVar(myConnectorPresentAsInt);
    theStream >>  FC_ExtractVar(myAdminStatusAsInt);
    theStream >>  FC_ExtractVar(myOperStatusAsInt);

    theStream >>  FC_ExtractVar(myDiscontinuityTime);
    theStream >>  FC_ExtractVar(myHighSpeed);
    myHCInOctets.ReadObject(theStream);
    myHCInUCastPkts.ReadObject(theStream);
    myHCInMulticastPkts.ReadObject(theStream);
    myHCInBroadcastPkts.ReadObject(theStream);
    myHCOutOctets.ReadObject(theStream);
    myHCOutUCastPkts.ReadObject(theStream);
    myHCOutMulticastPkts.ReadObject(theStream);
    myHCOutBroadcastPkts.ReadObject(theStream);
    myPhysAddress.ReadObject(theStream);
    myConnectorPresent = static_cast<CT_SNMP_TruthValue> (myConnectorPresentAsInt);
    myAdminStatus = static_cast<CT_SNMP_AdminStatus> (myAdminStatusAsInt);
    myOperStatus = static_cast<CT_SNMP_OperStatus> (myOperStatusAsInt);
      
    return theStream;
}

