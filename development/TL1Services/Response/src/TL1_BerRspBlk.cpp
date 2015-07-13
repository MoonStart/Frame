/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         Nov. 9, 2005 -- Maggie Zhang 
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_BerRspBlk.h>

TL1_BerRspBlk:: TL1_BerRspBlk(const string* entityName,
                            const CT_TL1_FacAddr* facAddr,
                            const CT_FAC_BerType* theBerType,
                            const bool* thePrbsTx,
							const bool* thePrbsRx,
                            const CT_TEL_PrbsFormat* thePrbsCompa,
							const uint32* thePrbsRate,
							const CT_FAC_PrbsState* thePrbsSync,
							const uint32* thePrbsDuration,
                            const uint8* thePrbsCalcRate,
                            const uint32* thePrbsCount)
    : myBitSet( INDEX_END, false)
{
    if( entityName )  
    {
		myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *entityName;
    }

    if( facAddr )  
    {
		myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *facAddr;
    }

    if( theBerType  )  
    {
		myBitSet[ INDEX_BerType ] = true;
        myBerType = *theBerType;
    }

    if( thePrbsTx  )  
    {
		myBitSet[ INDEX_PrbsTx ] = true;
        myPrbsTx = *thePrbsTx;
    }
    if( thePrbsRx  )  
    {
		myBitSet[ INDEX_PrbsRx ] = true;
        myPrbsRx = *thePrbsRx;
    }
    if( thePrbsCompa )
    {
        myBitSet[ INDEX_PrbsCompa ] = true;
        myPrbsCompa = *thePrbsCompa;
    }
    if( thePrbsRate  )  
    {
		myBitSet[ INDEX_PrbsRate ] = true;
        myPrbsRate = *thePrbsRate;
    }
    if( thePrbsSync  )  
    {
		myBitSet[ INDEX_PrbsSync ] = true;
        myPrbsSync = *thePrbsSync;
    }
    if( thePrbsDuration  )  
    {
		myBitSet[ INDEX_PrbsDuration ] = true;
        myPrbsDuration = *thePrbsDuration;
    }
    if( thePrbsCalcRate  )  
    {
		myBitSet[ INDEX_PrbsCalcRate ] = true;
        myPrbsCalcRate = *thePrbsCalcRate;
    }
    if( thePrbsCount  )  
    {
		myBitSet[ INDEX_PrbsCount ] = true;
        myPrbsCount = *thePrbsCount;
    }
}

TL1_BerRspBlk::TL1_BerRspBlk(const TL1_BerRspBlk& berBlk)
    : myBitSet(berBlk.myBitSet), myEntityName(berBlk.myEntityName), myFacAddr(berBlk.myFacAddr),
	  myBerType(berBlk.myBerType), myPrbsTx(berBlk.myPrbsTx), myPrbsRx(berBlk.myPrbsRx),myPrbsCompa(berBlk.myPrbsCompa),
	  myPrbsRate(berBlk.myPrbsRate),myPrbsSync(berBlk.myPrbsSync), myPrbsDuration(berBlk.myPrbsDuration),
	  myPrbsCalcRate(berBlk.myPrbsCalcRate), myPrbsCount(berBlk.myPrbsCount)
{
}

TL1_BerRspBlk::~TL1_BerRspBlk()
{
}

TL1_BerRspBlk& TL1_BerRspBlk::operator=( const TL1_BerRspBlk& theBlock )
{
    myBitSet      = theBlock.myBitSet;
    myEntityName  = theBlock.myEntityName; 
    myFacAddr     = theBlock.myFacAddr; 
	myBerType	  = theBlock.myBerType;
	myPrbsTx      = theBlock.myPrbsTx;
	myPrbsRx      = theBlock.myPrbsRx;
    myPrbsCompa   = theBlock.myPrbsCompa;
	myPrbsRate    = theBlock.myPrbsRate;
	myPrbsSync    = theBlock.myPrbsSync;
	myPrbsDuration= theBlock.myPrbsDuration;
	myPrbsCalcRate= theBlock.myPrbsCalcRate;
	myPrbsCount   = theBlock.myPrbsCount;

    return *this;
}

bool TL1_BerRspBlk::operator==( const TL1_BerRspBlk& theBlock ) const
{
    return ( myBitSet      == theBlock.myBitSet &&
             myEntityName  == theBlock.myEntityName && 
             myFacAddr     == theBlock.myFacAddr && 
			 myBerType	   == theBlock.myBerType &&
			 myPrbsTx      == theBlock.myPrbsTx  &&
			 myPrbsRx      == theBlock.myPrbsRx  &&
             myPrbsCompa   == theBlock.myPrbsCompa &&
			 myPrbsRate    == theBlock.myPrbsRate &&
			 myPrbsSync    == theBlock.myPrbsSync &&
			 myPrbsDuration== theBlock.myPrbsDuration &&
			 myPrbsCalcRate== theBlock.myPrbsCalcRate &&
			 myPrbsCount   == theBlock.myPrbsCount );
}

// Definition for GetEntityName()
bool TL1_BerRspBlk::GetEntityName( string& entityName) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
	{
    	entityName = myEntityName;
		return true;
	}
	else
	{
		return false;
	}
}


// Definition for GetFacAddr()
bool TL1_BerRspBlk::GetFacAddr( CT_TL1_FacAddr& facAddr) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
	{
   	    facAddr = myFacAddr;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetBerType()
bool TL1_BerRspBlk::GetBerType( CT_FAC_BerType& berType) const
{
    if( true == myBitSet[ INDEX_BerType ] )
	{
   	    berType = myBerType;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsTx()
bool TL1_BerRspBlk::GetPrbsTx( bool& prbsTx) const
{
    if( true == myBitSet[ INDEX_PrbsTx ] )
	{
   	    prbsTx = myPrbsTx;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsRx()
bool TL1_BerRspBlk::GetPrbsRx( bool& prbsRx) const
{
    if( true == myBitSet[ INDEX_PrbsRx ] )
	{
   	    prbsRx = myPrbsRx;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsCompa()
bool TL1_BerRspBlk::GetPrbsCompa( CT_TEL_PrbsFormat& prbsCompa) const
{
    if( true == myBitSet[ INDEX_PrbsCompa ] )
    {
        prbsCompa = myPrbsCompa;
        return true;
    }
    else
    {
        return false;
    }
}

// Definition for GetPrbsRate()
bool TL1_BerRspBlk::GetPrbsRate( uint32& prbsRate) const
{
    if( true == myBitSet[ INDEX_PrbsRate ] )
	{
   	    prbsRate = myPrbsRate;
	    return true;
	}
	else
	{
		return false;
	}
}
// Definition for GetPrbsSync()
bool TL1_BerRspBlk::GetPrbsSync( CT_FAC_PrbsState& prbsSync) const
{
    if( true == myBitSet[ INDEX_PrbsSync ] )
	{
   	    prbsSync = myPrbsSync;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsDuration()
bool TL1_BerRspBlk::GetPrbsDuration( uint32& prbsDuration) const
{
    if( true == myBitSet[ INDEX_PrbsDuration ] )
	{
   	    prbsDuration = myPrbsDuration;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsCalcRate()
bool TL1_BerRspBlk::GetPrbsCalcRate( uint8& prbsCalcRate) const
{
    if( true == myBitSet[ INDEX_PrbsCalcRate ] )
	{
   	    prbsCalcRate = myPrbsCalcRate;
	    return true;
	}
	else
	{
		return false;
	}
}

// Definition for GetPrbsCount()
bool TL1_BerRspBlk::GetPrbsCount( uint32& prbsCount) const
{
    if( true == myBitSet[ INDEX_PrbsCount ] )
	{
   	    prbsCount = myPrbsCount;
	    return true;
	}
	else
	{
		return false;
	}
}


