/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_SwitchDomainRspBlk.h>

TL1_SwitchDomainRspBlk::TL1_SwitchDomainRspBlk():
mySwitchDomain(CT_SWITCH_DOMAIN_UNKNOWN),
myAlmPf(CT_DEFAULT_PT),
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS),
myBitSet( INDEX_END, false)
{
    myCntrSwitch.clear();
    myRepeaterSwitch.clear();
    myEndSwitch.clear();
}

TL1_SwitchDomainRspBlk::TL1_SwitchDomainRspBlk(const CT_SwitchDomain* SwitchDomain,
                    const CT_SwitchDomainMembers* CntrSwitch,
                    const CT_SwitchDomainMembers* RepeaterSwitch,
                    const CT_SwitchDomainMembers* EndSwitch,
                    const CT_ProtLevel* ProtLevel,
                    const CT_SwitchDomainMode* SwitchDomainMode,
                    const CT_ProfileTableId* AlmPf,                                       
                    const CT_SM_PST* PST,
                    const CT_SM_PSTQ* PSTQ,
                    const CT_SM_SST* SST) : 
mySwitchDomain(CT_SWITCH_DOMAIN_UNKNOWN),
myProtLevel(CT_NONE),
mySwitchDomainMode(CT_SWITCHDOMAINMODE_ALL),
myAlmPf(CT_DEFAULT_PT),
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS),
myBitSet( INDEX_END, false)
{

    myCntrSwitch.clear();
    myRepeaterSwitch.clear();
    myEndSwitch.clear();


    if ( SwitchDomain )  
    {
		myBitSet[ INDEX_SwitchDomain ] = true;
        mySwitchDomain = *SwitchDomain;
    }

    if ( CntrSwitch )  
    {
		myBitSet[ INDEX_CntrSwitch ] = true;
        myCntrSwitch = *CntrSwitch;
    }

    if ( RepeaterSwitch )  
    {
		myBitSet[ INDEX_RepeaterSwitch ] = true;
        myRepeaterSwitch = *RepeaterSwitch;
    }

    if ( EndSwitch )  
    {
		myBitSet[ INDEX_EndSwitch ] = true;
        myEndSwitch = *EndSwitch;
    }

    if ( ProtLevel )  
    {
		myBitSet[ INDEX_ProtLevel ] = true;
        myProtLevel = *ProtLevel;
    }

	if ( SwitchDomainMode )  
    {
        myBitSet[ INDEX_SwitchDomainMode ] = true;
        mySwitchDomainMode = *SwitchDomainMode;
    }

    if ( AlmPf )  
    {
		myBitSet[ INDEX_AlmPf ] = true;
        myAlmPf = *AlmPf;
    }

    if (PST)
    {
		myBitSet[ INDEX_PST ] = true;
        myPST = *PST;
    }

    if (PSTQ)
    {
		myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *PSTQ;
    }

    if (SST)
    {
		myBitSet[ INDEX_SST ] = true;
        mySST = *SST;
    }
}

//--------------------------------------------------------------------------------------------------    
TL1_SwitchDomainRspBlk::TL1_SwitchDomainRspBlk(const TL1_SwitchDomainRspBlk& rspBlk)
    : myBitSet(rspBlk.myBitSet), mySwitchDomain(rspBlk.mySwitchDomain), myCntrSwitch(rspBlk.myCntrSwitch), 
    myAlmPf(rspBlk.myAlmPf), myProtLevel(rspBlk.myProtLevel), mySwitchDomainMode(rspBlk.mySwitchDomainMode), 
	myRepeaterSwitch(rspBlk.myRepeaterSwitch), myEndSwitch(rspBlk.myEndSwitch), myPST(rspBlk.myPST), 
	myPSTQ( rspBlk.myPSTQ), mySST( rspBlk.mySST )
{
}

TL1_SwitchDomainRspBlk::~TL1_SwitchDomainRspBlk()
{
}

//--------------------------------------------------------------------------------------------------    
TL1_SwitchDomainRspBlk& TL1_SwitchDomainRspBlk::operator=( const TL1_SwitchDomainRspBlk& theBlock )
{
    myBitSet            = theBlock.myBitSet;
    mySwitchDomain      = theBlock.mySwitchDomain;
    myCntrSwitch        = theBlock.myCntrSwitch;
    myRepeaterSwitch	= theBlock.myRepeaterSwitch;
    myEndSwitch			= theBlock.myEndSwitch;		
    myAlmPf             = theBlock.myAlmPf;
    myPST               = theBlock.myPST;
    myPSTQ              = theBlock.myPSTQ;
    mySST               = theBlock.mySST;
    myProtLevel			= theBlock.myProtLevel;
    mySwitchDomainMode	= theBlock.mySwitchDomainMode;
     
    return *this;
}

//--------------------------------------------------------------------------------------------------    
bool TL1_SwitchDomainRspBlk::operator==( const TL1_SwitchDomainRspBlk& theBlock ) const
{
    return ( myBitSet           	== theBlock.myBitSet &&
                mySwitchDomain  	== theBlock.mySwitchDomain &&
                myCntrSwitch    	== theBlock.myCntrSwitch &&
                myRepeaterSwitch	== theBlock.myRepeaterSwitch &&
                myEndSwitch     	== theBlock.myEndSwitch &&
                myAlmPf         	== theBlock.myAlmPf &&
                myPST           	== theBlock.myPST &&
                myPSTQ          	== theBlock.myPSTQ &&
                mySST           	== theBlock.mySST &&
                myProtLevel			== theBlock.myProtLevel &&
                mySwitchDomainMode  == theBlock.mySwitchDomainMode
            );
}

//--------------------------------------------------------------------------------------------------    
bool TL1_SwitchDomainRspBlk::GetSwitchDomain(CT_SwitchDomain& switchDomain) const
{
    if( true == myBitSet[ INDEX_SwitchDomain ] )
	{
    	switchDomain = mySwitchDomain;
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------------------    
bool TL1_SwitchDomainRspBlk::GetRepeaterSwitch(CT_SwitchDomainMembers& repeaterSwitch) const
{
    if( true == myBitSet[ INDEX_RepeaterSwitch ] )
	{
    	repeaterSwitch = myRepeaterSwitch;
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------------------    
bool TL1_SwitchDomainRspBlk::GetEndSwitch(CT_SwitchDomainMembers& endSwitch) const
{
    if( true == myBitSet[ INDEX_EndSwitch ] )
	{
    	endSwitch = myEndSwitch;
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------------------    
bool TL1_SwitchDomainRspBlk::GetCntrSwitch(CT_SwitchDomainMembers& cntrSwitch) const
{
    if( true == myBitSet[ INDEX_CntrSwitch ] )
	{
    	cntrSwitch = myCntrSwitch;
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------------------
bool TL1_SwitchDomainRspBlk::GetProtLevel( CT_ProtLevel& protLevel) const
{
    if( true == myBitSet[ INDEX_ProtLevel ] )
    {
    	protLevel = myProtLevel;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------
bool TL1_SwitchDomainRspBlk::GetSwitchDomainMode( CT_SwitchDomainMode& switchDomainMode) const
{
	if( true == myBitSet[ INDEX_SwitchDomainMode ] )
	{
		switchDomainMode = mySwitchDomainMode;
		return true;
	}
	else
	{
		return false;
	}

}

//--------------------------------------------------------------------------------------------------
bool TL1_SwitchDomainRspBlk::GetAlmPf( CT_ProfileTableId& almPf) const
{
    if( true == myBitSet[ INDEX_AlmPf ] )
    {
    	almPf = myAlmPf;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SwitchDomainRspBlk::GetPST( CT_SM_PST& PST) const 
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        PST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_SwitchDomainRspBlk::GetPSTQ( CT_SM_PSTQ& PSTQ) const 
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        PSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SwitchDomainRspBlk::GetSST( CT_SM_SST& SST) const 
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        SST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}

CT_SM_PST TL1_SwitchDomainRspBlk::GetPST() const 
{
    return myPST;
}

CT_SM_PSTQ TL1_SwitchDomainRspBlk::GetPSTQ() const 
{
    return myPSTQ;
}

CT_SM_SST TL1_SwitchDomainRspBlk::GetSST() const 
{
    return mySST;
}
