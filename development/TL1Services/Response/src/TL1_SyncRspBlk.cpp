/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Protection Response 
TARGET:
AUTHOR:         August 12, 2004- Maggie Zhang
DESCRIPTION:    Source file for TL1 Retrive Sync Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SyncRspBlk.h>


TL1_SyncRspBlk::TL1_SyncRspBlk(const CT_TL1_ProtnAddr* theAddr,
                             const CT_SM_PST*  thePST,
                             const CT_SM_PSTQ* thePSTQ,
                             const CT_SM_SST*  theSST) :
    itsBitSet(INDEX_END,false)
{

	if(theAddr)
	{
		itsBitSet[INDEX_Addr] = true;
		itsAddr = *theAddr;
	}

	if(thePST)
    {
		itsBitSet[ INDEX_PST ] = true;
        itsPST = *thePST;
    }

    if(thePSTQ)
    {
		itsBitSet[ INDEX_PSTQ ] = true;
        itsPSTQ = *thePSTQ;
    }

    if(theSST)
    {
		itsBitSet[ INDEX_SST ] = true;
        itsSST = *theSST;
    }


}

TL1_SyncRspBlk::~TL1_SyncRspBlk()
{
}
  
TL1_SyncRspBlk::TL1_SyncRspBlk(const TL1_SyncRspBlk& theBlock) :
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST)
{
	itsBitSet = theBlock.itsBitSet;
	itsAddr = theBlock.itsAddr;
	itsPST = theBlock.itsPST;
}

TL1_SyncRspBlk& TL1_SyncRspBlk::operator=( const TL1_SyncRspBlk& theBlock )
{
    itsBitSet = theBlock.itsBitSet;
	itsAddr=         theBlock.itsAddr;
    itsPST=          theBlock.itsPST;
    itsPSTQ=         theBlock.itsPSTQ;
    itsSST=          theBlock.itsSST;
    return *this;
} 

bool TL1_SyncRspBlk::operator ==(const TL1_SyncRspBlk& theBlock) const
{
	return (itsBitSet == theBlock.itsBitSet &&
			itsAddr == theBlock.itsAddr &&
			itsPST == theBlock.itsPST &&
			itsPSTQ == theBlock.itsPSTQ &&
			itsSST == theBlock.itsSST);

}


bool TL1_SyncRspBlk::GetAddr(CT_TL1_ProtnAddr& theAddr) const
{
	if(true == itsBitSet[INDEX_Addr])
	{
		theAddr = itsAddr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_SyncRspBlk::GetPST(CT_SM_PST& thePST) const
{
	if(true == itsBitSet[INDEX_PST])
	{
		thePST = itsPST;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_SyncRspBlk::GetPSTQ(CT_SM_PSTQ& thePSTQ) const
{
	if(true == itsBitSet[INDEX_PSTQ])
	{
		thePSTQ = itsPSTQ;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_SyncRspBlk::GetSST(CT_SM_SST& theSST) const
{
	if(true == itsBitSet[INDEX_SST])
	{
		theSST = itsSST;
		return true;
	}
	else
	{
		return false;
	}
}
