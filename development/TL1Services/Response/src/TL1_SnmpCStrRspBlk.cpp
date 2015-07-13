/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 SNMP Response 
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Source file for TL1 Retrive SNMP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SnmpCStrRspBlk.h>


TL1_SnmpCStrRspBlk::TL1_SnmpCStrRspBlk(
							const string*				theCommStr)
    : myBitSet( INDEX_END, false)
{
    if( theCommStr )  
    {
		myBitSet[ INDEX_CommStr ] = true;
        myCommStr = *theCommStr;
    }

}

TL1_SnmpCStrRspBlk::~TL1_SnmpCStrRspBlk()
{
}
  
TL1_SnmpCStrRspBlk::TL1_SnmpCStrRspBlk(const TL1_SnmpCStrRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myCommStr(theBlock.myCommStr)
{
}

TL1_SnmpCStrRspBlk& TL1_SnmpCStrRspBlk::operator=( const TL1_SnmpCStrRspBlk& theBlock )
{
    myBitSet =			theBlock.myBitSet;
    myCommStr =			theBlock.myCommStr;

    return *this;
}

bool TL1_SnmpCStrRspBlk::GetCStr(string& cStr) const
{
    if( true == myBitSet[ INDEX_CommStr ] )
	{
    	cStr = myCommStr;
		return true;
	}
	else
	{
		return false;
	}
}
