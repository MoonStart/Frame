/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 SNMP Response 
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Source file for TL1 Retrive SNMP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SnmpRspBlk.h>

//
//  RtrvSnmp
//

TL1_SnmpRspBlk::TL1_SnmpRspBlk(
                            const string*				theAid,
                            const string*				theROCname,
                            const string*				theRWCname,
                            const bool*			        thePst)
    : myBitSet( INDEX_END, false)
{
    if( theAid )  
    {
        myBitSet[ INDEX_Aid ] = true;
        myAid = *theAid;
    }

    if( theROCname )  
    {
        myBitSet[ INDEX_ROCname ] = true;
        myROCname = *theROCname;
    }

    if( theRWCname )  
    {
        myBitSet[ INDEX_RWCname ] = true;
        myRWCname = *theRWCname;
    }

    if( thePst )  
    {
        myBitSet[ INDEX_Pst ] = true;
        myPst = *thePst;
    }
}

TL1_SnmpRspBlk::~TL1_SnmpRspBlk()
{
}
  
TL1_SnmpRspBlk::TL1_SnmpRspBlk(const TL1_SnmpRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myAid(theBlock.myAid),
    myROCname(theBlock.myROCname),
    myRWCname(theBlock.myRWCname),
    myPst(theBlock.myPst)
{
}

TL1_SnmpRspBlk& TL1_SnmpRspBlk::operator=( const TL1_SnmpRspBlk& theBlock )
{
    myBitSet =			theBlock.myBitSet;
    myAid =				theBlock.myAid;
    myROCname =			theBlock.myROCname;
    myRWCname =			theBlock.myRWCname;
    myPst =				theBlock.myPst;

    return *this;
}

bool TL1_SnmpRspBlk::GetAid(string& Aid) const
{
    if( true == myBitSet[ INDEX_Aid ] )
    {
        Aid = myAid;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SnmpRspBlk::GetROCname(string& ROCname) const
{
    if( true == myBitSet[ INDEX_ROCname ] )
    {
        ROCname = myROCname;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SnmpRspBlk::GetRWCname(string& RWCname) const
{
    if( true == myBitSet[ INDEX_RWCname ] )
    {
        RWCname = myRWCname;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SnmpRspBlk::GetPst(bool& Pst) const
{
    if( true == myBitSet[ INDEX_Pst ] )
    {
        Pst = myPst;
        return true;
    }
    else
    {
        return false;
    }
}


//
//  RtrvEngIdMap
//

TL1_EngIdMapRspBlk::TL1_EngIdMapRspBlk(const string* theAid,
                                       const CT_ShelfId* theShelfId,
                                       const string* theEngIdString)
    : myBitSet( INDEX_END, false)
{
    if( theAid )  
    {
        myBitSet[ INDEX_Aid ] = true;
        myAid = *theAid;
    }

    if( theShelfId )  
    {
        myBitSet[ INDEX_ShelfId ] = true;
        myShelfId = *theShelfId;
    }

    if( theEngIdString )  
    {
        myBitSet[ INDEX_EngIdString ] = true;
        myEngIdString = *theEngIdString;
    }
}

TL1_EngIdMapRspBlk::~TL1_EngIdMapRspBlk()
{
}
  
TL1_EngIdMapRspBlk::TL1_EngIdMapRspBlk(const TL1_EngIdMapRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myAid(theBlock.myAid),
    myShelfId(theBlock.myShelfId),
    myEngIdString(theBlock.myEngIdString)
{
}

TL1_EngIdMapRspBlk& TL1_EngIdMapRspBlk::operator=( const TL1_EngIdMapRspBlk& theBlock )
{
    myBitSet =      theBlock.myBitSet;
    myAid =         theBlock.myAid;
    myShelfId =     theBlock.myShelfId;
    myEngIdString = theBlock.myEngIdString;

    return *this;
}

bool TL1_EngIdMapRspBlk::GetAid(string& Aid) const
{
    if( true == myBitSet[ INDEX_Aid ] )
    {
        Aid = myAid;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EngIdMapRspBlk::GetShelfId(CT_ShelfId& ShelfId) const
{
    if( true == myBitSet[ INDEX_ShelfId ] )
    {
        ShelfId = myShelfId;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EngIdMapRspBlk::GetEngIdString(string& EngIdString) const
{
    if( true == myBitSet[ INDEX_EngIdString ] )
    {
        EngIdString = myEngIdString;
        return true;
    }
    else
    {
        return false;
    }
}

//
//  RtrvTrapIp
//

TL1_TrapIpRspBlk::TL1_TrapIpRspBlk(const uint32* theIpAddr,
                                    const string* theName,
                                    const uint16* thePort,
                                    const int* theVersion,
                                    const string* theUid)
    : myBitSet( INDEX_END, false)
{
    if( theIpAddr )  
    {
        myBitSet[ INDEX_IpAddr ] = true;
        memcpy(myIpAddr , theIpAddr ,4*sizeof(uint32));
    }

    if( theName )  
    {
        myBitSet[ INDEX_Name ] = true;
        myName = *theName;
    }

    if( thePort )  
    {
        myBitSet[ INDEX_Port ] = true;
        myPort = *thePort;
    }

    if( theVersion )  
    {
        myBitSet[ INDEX_Version ] = true;
        myVersion = *theVersion;
    }

   if( theUid )  
    {
        myBitSet[ INDEX_Uid ] = true;
        myUid = *theUid;
    }
}

TL1_TrapIpRspBlk::~TL1_TrapIpRspBlk()
{
}
  
TL1_TrapIpRspBlk::TL1_TrapIpRspBlk(const TL1_TrapIpRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
//    myIpAddr(theBlock.myIpAddr),
    myName(theBlock.myName),
    myPort(theBlock.myPort),
    myVersion(theBlock.myVersion),
    myUid(theBlock.myUid)
{
         memcpy(myIpAddr , theBlock.myIpAddr ,4*sizeof(uint32));
}

TL1_TrapIpRspBlk& TL1_TrapIpRspBlk::operator=( const TL1_TrapIpRspBlk& theBlock )
{
    myBitSet =      theBlock.myBitSet;
   // myIpAddr =      theBlock.myIpAddr;
 memcpy(myIpAddr , theBlock.myIpAddr ,4*sizeof(uint32));
    myName = theBlock.myName;
    myPort = theBlock.myPort;
    myVersion = theBlock.myVersion;
    myUid   =  theBlock.myUid;

    return *this;
}

bool TL1_TrapIpRspBlk::GetIpAddr(uint32* IpAddr) const
{
    if( true == myBitSet[ INDEX_IpAddr ] )
    {
        //IpAddr = myIpAddr;
        memcpy(IpAddr , myIpAddr ,4*sizeof(uint32));
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_TrapIpRspBlk::GetName(string& Name) const
{
    if( true == myBitSet[ INDEX_Name ] )
    {
        Name = myName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_TrapIpRspBlk::GetUid(string& theUid) const
{
    if( true == myBitSet[ INDEX_Uid ] )
    {
        theUid = myUid;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_TrapIpRspBlk::GetPort(uint16& Port) const
{
    if( true == myBitSet[ INDEX_Port ] )
    {
        Port = myPort;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_TrapIpRspBlk::GetVersion(int& Version) const
{
    if( true == myBitSet[ INDEX_Version ] )
    {
        Version = myVersion;
        return true;
    }
    else
    {
        return false;
    }
}


