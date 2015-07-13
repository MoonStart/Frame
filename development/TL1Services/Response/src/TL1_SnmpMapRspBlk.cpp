/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 SNMP Response 
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Source file for TL1 Retrive SNMP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SnmpMapRspBlk.h>

//
//  RtrvSnmpMap
//

TL1_SnmpMapRspBlk::TL1_SnmpMapRspBlk(
							const string*				theROCname,
							const string*				theRWCname,
							const string*				theRemoteTid)
    : myBitSet( INDEX_END, false)
{
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

    if( theRemoteTid )  
    {
		myBitSet[ INDEX_RemoteTid ] = true;
        myRemoteTid = *theRemoteTid;
    }
}

TL1_SnmpMapRspBlk::~TL1_SnmpMapRspBlk()
{
}
  
TL1_SnmpMapRspBlk::TL1_SnmpMapRspBlk(const TL1_SnmpMapRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myROCname(theBlock.myROCname),
    myRWCname(theBlock.myRWCname),
    myRemoteTid(theBlock.myRemoteTid)
{
}

TL1_SnmpMapRspBlk& TL1_SnmpMapRspBlk::operator=( const TL1_SnmpMapRspBlk& theBlock )
{
    myBitSet =			theBlock.myBitSet;
    myROCname =			theBlock.myROCname;
    myRWCname =			theBlock.myRWCname;
    myRemoteTid =		theBlock.myRemoteTid;

    return *this;
}

bool TL1_SnmpMapRspBlk::GetROCname(string& ROCname) const
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

bool TL1_SnmpMapRspBlk::GetRWCname(string& RWCname) const
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

bool TL1_SnmpMapRspBlk::GetRemoteTid(string& RemoteTid) const
{
    if( true == myBitSet[ INDEX_RemoteTid ] )
	{
    	RemoteTid = myRemoteTid;
		return true;
	}
	else
	{
		return false;
	}
}
