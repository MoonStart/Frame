/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_RmonEtherStatsData.h>
#include <BaseClass/FC_TextStream.h>

SNMP_BbRmonEtherStatsData::SNMP_BbRmonEtherStatsData() :
SNMP_BbRmonData()
{
    ResetAll();
}

SNMP_BbRmonEtherStatsData::~SNMP_BbRmonEtherStatsData()
{
}

void SNMP_BbRmonEtherStatsData::ResetAll()
{
     SNMP_BbRmonData::ResetAll();
     ResetDropEvents();
     ResetOctets();
     ResetPkts();
     ResetBroadcastPkts();
     ResetMulticastPkts();
     ResetCRCAlignErrors();
     ResetUndersizePkts();
     ResetOversizePkts();
     ResetFragments();
     ResetJabbers();
     ResetCollisions();
     ResetPkts64();
     ResetPkts65to127();
     ResetPkts128to255();
     ResetPkts256to511();
     ResetPkts512to1023();
     ResetPkts1024to1518();
     ResetDroppedFrames();
     ResetCreateTime();
}

FC_Stream& SNMP_BbRmonEtherStatsData::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonData::ReadObjectBinary(theStream);

    theStream >> myEtherData.myDropEvents;
    theStream >> myEtherData.myOctets;
    theStream >> myEtherData.myPkts;
    theStream >> myEtherData.myBroadcastPkts;
    theStream >> myEtherData.myMulticastPkts;
    theStream >> myEtherData.myCRCAlignErrors;
    theStream >> myEtherData.myUndersizePkts;
    theStream >> myEtherData.myOversizePkts;
    theStream >> myEtherData.myFragments;
    theStream >> myEtherData.myJabbers;
    theStream >> myEtherData.myCollisions;
    theStream >> myPkts64Octets;
    theStream >> myPkts65to127Octets;
    theStream >> myPkts128to255Octets;
    theStream >> myPkts256to511Octets;
    theStream >> myPkts512to1023Octets;
    theStream >> myPkts1024to1518Octets;
    theStream >> myDroppedFrames;
    theStream >> myCreateTime;

    return theStream;
}

FC_Stream& SNMP_BbRmonEtherStatsData::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonData::WriteObjectBinary(theStream);

    theStream << myEtherData.myDropEvents;
    theStream << myEtherData.myOctets;
    theStream << myEtherData.myPkts;
    theStream << myEtherData.myBroadcastPkts;
    theStream << myEtherData.myMulticastPkts;
    theStream << myEtherData.myCRCAlignErrors;
    theStream << myEtherData.myUndersizePkts;
    theStream << myEtherData.myOversizePkts;
    theStream << myEtherData.myFragments;
    theStream << myEtherData.myJabbers;
    theStream << myEtherData.myCollisions;
    theStream << myPkts64Octets;
    theStream << myPkts65to127Octets;
    theStream << myPkts128to255Octets;
    theStream << myPkts256to511Octets;
    theStream << myPkts512to1023Octets;
    theStream << myPkts1024to1518Octets;
    theStream << myDroppedFrames;
    theStream << myCreateTime;

    return theStream;
}

istream& SNMP_BbRmonEtherStatsData::ReadObject (istream& theStream)
{
    SNMP_BbRmonData::ReadObject(theStream);

    theStream >> FC_ExtractVar(myEtherData.myDropEvents);
    theStream >> FC_ExtractVar(myEtherData.myOctets);
    theStream >> FC_ExtractVar(myEtherData.myPkts);
    theStream >> FC_ExtractVar(myEtherData.myBroadcastPkts);
    theStream >> FC_ExtractVar(myEtherData.myMulticastPkts);
    theStream >> FC_ExtractVar(myEtherData.myCRCAlignErrors);
    theStream >> FC_ExtractVar(myEtherData.myUndersizePkts);
    theStream >> FC_ExtractVar(myEtherData.myOversizePkts);
    theStream >> FC_ExtractVar(myEtherData.myFragments);
    theStream >> FC_ExtractVar(myEtherData.myJabbers);
    theStream >> FC_ExtractVar(myEtherData.myCollisions);
    theStream >> FC_ExtractVar(myPkts64Octets);
    theStream >> FC_ExtractVar(myPkts65to127Octets);
    theStream >> FC_ExtractVar(myPkts128to255Octets); 
    theStream >> FC_ExtractVar(myPkts256to511Octets); 
    theStream >> FC_ExtractVar(myPkts512to1023Octets); 
    theStream >> FC_ExtractVar(myPkts1024to1518Octets); 
    theStream >> FC_ExtractVar(myDroppedFrames); 
    theStream >> FC_ExtractVar(myCreateTime); 

    return theStream;
}

ostream& SNMP_BbRmonEtherStatsData::WriteObject (ostream& theStream)
{
    SNMP_BbRmonData::WriteObject(theStream);

    theStream << FC_InsertVar(myEtherData.myDropEvents);
    theStream << FC_InsertVar(myEtherData.myOctets);
    theStream << FC_InsertVar(myEtherData.myPkts);
    theStream << FC_InsertVar(myEtherData.myBroadcastPkts);
    theStream << FC_InsertVar(myEtherData.myMulticastPkts);
    theStream << FC_InsertVar(myEtherData.myCRCAlignErrors);
    theStream << FC_InsertVar(myEtherData.myUndersizePkts);
    theStream << FC_InsertVar(myEtherData.myOversizePkts);
    theStream << FC_InsertVar(myEtherData.myFragments);
    theStream << FC_InsertVar(myEtherData.myJabbers);
    theStream << FC_InsertVar(myEtherData.myCollisions);
    theStream << FC_InsertVar(myPkts64Octets);
    theStream << FC_InsertVar(myPkts65to127Octets);
    theStream << FC_InsertVar(myPkts128to255Octets); 
    theStream << FC_InsertVar(myPkts256to511Octets); 
    theStream << FC_InsertVar(myPkts512to1023Octets); 
    theStream << FC_InsertVar(myPkts1024to1518Octets); 
    theStream << FC_InsertVar(myDroppedFrames); 
    theStream << FC_InsertVar(myCreateTime); 

    return theStream;
}

