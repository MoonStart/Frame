/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 DHCP Response 
TARGET:
AUTHOR:         OCtober 19, 2005 - Mike Rodgers
DESCRIPTION:    Source file for TL1 Retrive DHCP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_DhcpRspBlk.h>

//
//  RtrvDhcp
//

TL1_DhcpRspBlk::TL1_DhcpRspBlk(
    						const string*				theAid,
							const string*				theHWID,
							const CT_ProfileTableId*	theProfileId,
							const bool*					theOption82,
							const uint32*				theServerIp,
							const uint32*				theMinIp,
							const uint32*				theMaxIp,
							const bool*					theStatus,
							const CT_SM_PST*			thePst,
							const CT_SM_PSTQ*			thePstq,
							const CT_SM_SST*			theSst)
    : myBitSet( INDEX_END, false)
{
    if( theAid )  
    {
		myBitSet[ INDEX_Aid ] = true;
        myAid = *theAid;
    }
    else
    {
        myBitSet[ INDEX_Aid ] = false;
    }

    if( theHWID )  
    {
		myBitSet[ INDEX_HWID ] = true;
        myHWID = *theHWID;
    }
    else
    {
        myBitSet[ INDEX_HWID ] = false;
    }

    if( theProfileId )  
    {
		myBitSet[ INDEX_ProfileId ] = true;
        myProfileId = *theProfileId;
    }
    else
    {
        myBitSet[ INDEX_ProfileId ] = false;
        myProfileId = (CT_ProfileTableId)0;
    }

    if( theMinIp )  
    {
		myBitSet[ INDEX_MinIp ] = true;
        myMinIp = *theMinIp;
    }
    else
    {
        myBitSet[ INDEX_MinIp ] = false;
        myMinIp = 0;
    }

    if( theMaxIp )  
    {
		myBitSet[ INDEX_MaxIp ] = true;
        myMaxIp = *theMaxIp;
    }
    else
    {
        myBitSet[ INDEX_MaxIp ] = false;
        myMaxIp = 0;
    }

    if( theStatus )  
    {
		myBitSet[ INDEX_Status ] = true;
        myStatus = *theStatus;
    }
    else
    {
        myBitSet[ INDEX_Status ] = false;
        myStatus = 0;
    }

    if( theOption82 )  
    {
		myBitSet[ INDEX_Option82 ] = true;
        myOption82 = *theOption82;
    }
    else
    {
        myBitSet[ INDEX_Option82 ] = false;   
        myOption82 = 0;
    }
	
    if( theServerIp )  
    {
		myBitSet[ INDEX_ServerIp ] = true;
        myServerIp = *theServerIp;
    }
    else
    {
        myBitSet[ INDEX_ServerIp ] = false;
        myServerIp = 0;
    }

    if( thePst )  
    {
		myBitSet[ INDEX_Pst ] = true;
        myPst = *thePst;
    }
    else
    {
        myBitSet[ INDEX_Pst ] = false;
        myPst = 0;
    }

    if( thePstq )  
    {
		myBitSet[ INDEX_Pstq ] = true;
        myPstq = *thePstq;
    }
    else
    {
        myBitSet[ INDEX_Pstq ] = false; 	
        myPstq = 0;
    }

    if( theSst )  
    {
		myBitSet[ INDEX_Sst ] = true;
        mySst = *theSst;
    }
    else
    {
        myBitSet[ INDEX_Sst ] = false;
        mySst = 0;
    }

}


TL1_DhcpRspBlk::~TL1_DhcpRspBlk()
{
}
  
TL1_DhcpRspBlk::TL1_DhcpRspBlk(const TL1_DhcpRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myAid(theBlock.myAid),
    myHWID(theBlock.myHWID),
    myProfileId(theBlock.myProfileId),
    myMinIp(theBlock.myMinIp),
    myMaxIp(theBlock.myMaxIp),
    myStatus(theBlock.myStatus),
    myOption82(theBlock.myOption82),
    myServerIp(theBlock.myServerIp),
    myPst(theBlock.myPst),
    myPstq(theBlock.myPstq),
    mySst(theBlock.mySst)
{
}

TL1_DhcpRspBlk& TL1_DhcpRspBlk::operator=( const TL1_DhcpRspBlk& theBlock )
{
    myBitSet =			theBlock.myBitSet;
    myAid =				theBlock.myAid;
    myHWID =			theBlock.myHWID;
    myProfileId =		theBlock.myProfileId;
    myMinIp =			theBlock.myMinIp;
    myMaxIp =			theBlock.myMaxIp;
    myStatus =			theBlock.myStatus;
    myOption82 =	    theBlock.myOption82;
    myServerIp =	    theBlock.myServerIp;
    myPst =				theBlock.myPst;
    myPstq =			theBlock.myPstq;
    mySst =				theBlock.mySst;

    return *this;
}

bool TL1_DhcpRspBlk::GetAid(string& Aid) const
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

bool TL1_DhcpRspBlk::GetHWID(string& HWID) const
{
    if( true == myBitSet[ INDEX_HWID ] )
	{
    	HWID = myHWID;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetProfileId(CT_ProfileTableId& ProfileId) const
{
    if( true == myBitSet[ INDEX_ProfileId ] )
	{
    	ProfileId = myProfileId;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetMinIp(uint32& MinIp) const
{
    if( true == myBitSet[ INDEX_MinIp ] )
	{
    	MinIp = myMinIp;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetMaxIp(uint32& MaxIp) const
{
    if( true == myBitSet[ INDEX_MaxIp ] )
	{
    	MaxIp = myMaxIp;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetStatus(bool& Status) const
{
    if( true == myBitSet[ INDEX_Status ] )
	{
    	Status = myStatus;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetOption82(bool& Option82) const
{
    if( true == myBitSet[ INDEX_Option82 ] )
	{
    	Option82 = myOption82;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetServerIp(uint32& ServerIp) const
{
    if( true == myBitSet[ INDEX_ServerIp ] )
	{
    	ServerIp = myServerIp;
		return true;
	}
	else
	{
		return false;
	}
}


bool TL1_DhcpRspBlk::GetPst(CT_SM_PST& Pst) const
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

bool TL1_DhcpRspBlk::GetPstq(CT_SM_PSTQ& Pstq) const
{
    if( true == myBitSet[ INDEX_Pstq ] )
	{
    	Pstq = myPstq;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpRspBlk::GetSst(CT_SM_SST& Sst) const
{
    if( true == myBitSet[ INDEX_Sst ] )
	{
    	Sst = mySst;
		return true;
	}
	else
	{
		return false;
	}
}

//
//  RtrvDhcpIpaddr
//

TL1_DhcpIpaddrRspBlk::TL1_DhcpIpaddrRspBlk(
							const string*				theHwid,
    						const string*				theRneTid,
							const uint32*				theRneIp) 
    : myBitSet( INDEX_END, false)
{
    if( theHwid )  
    {
		myBitSet[ INDEX_Hwid ] = true;
        myHwid = *theHwid;
    }

    if( theRneTid )  
    {
		myBitSet[ INDEX_RneTid ] = true;
        myRneTid = *theRneTid;
    }

    if( theRneIp )  
    {
		myBitSet[ INDEX_RneIp ] = true;
        myRneIp = *theRneIp;
    }

}

TL1_DhcpIpaddrRspBlk::~TL1_DhcpIpaddrRspBlk()
{
}
  
TL1_DhcpIpaddrRspBlk::TL1_DhcpIpaddrRspBlk(const TL1_DhcpIpaddrRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myHwid(theBlock.myHwid),
    myRneTid(theBlock.myRneTid),
    myRneIp(theBlock.myRneIp)
{
}

TL1_DhcpIpaddrRspBlk& TL1_DhcpIpaddrRspBlk::operator=( const TL1_DhcpIpaddrRspBlk& theBlock )
{
    myBitSet =			theBlock.myBitSet;
    myHwid =			theBlock.myHwid;
    myRneTid =			theBlock.myRneTid;
    myRneIp =			theBlock.myRneIp;

    return *this;
}

bool TL1_DhcpIpaddrRspBlk::GetHwid(string& Hwid) const
{
    if( true == myBitSet[ INDEX_Hwid ] )
	{
    	Hwid = myHwid;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpIpaddrRspBlk::GetRneTid(string& RneTid) const
{
    if( true == myBitSet[ INDEX_RneTid ] )
	{
    	RneTid = myRneTid;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_DhcpIpaddrRspBlk::GetRneIp(uint32& RneIp) const
{
    if( true == myBitSet[ INDEX_RneIp ] )
	{
    	RneIp = myRneIp;
		return true;
	}
	else
	{
		return false;
	}
}

