/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OCH Response 
TARGET:
AUTHOR:         February 20, 2004 - Thomas Novak
DESCRIPTION:    Source file for TL1 OCH Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_T1RspBlk.h>

TL1_T1RspBlk::TL1_T1RspBlk()
{
}

TL1_T1RspBlk::TL1_T1RspBlk( const string* 				theEntityName,
                            const CT_TL1_FacAddr* 		theAddr,
                            const CT_CardType* 			theCardType,
                            const CT_SubCardType* 		theSubCardType,
							const CT_FAC_LineCode* 		theLineCode,
							const CT_FAC_FrameFormat*   theFrameFormat,
							const CT_FAC_RxSsm*         theClockQuality,
							const CT_ProfileTableId* 	theAlarmProfile,
                            const CT_SM_PST*  			thePST,
                            const CT_SM_PSTQ* 			thePSTQ,
                            const CT_SM_SST*  			theSST )
    : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *theAddr;
    }

    if( theCardType )
    {
        myBitSet[ INDEX_CardType ] = true;
        myCardType = *theCardType;
    }

    if( theSubCardType )
    {
        myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *theSubCardType;
    }

    if( theLineCode )
    {
        myBitSet[ INDEX_LineCode ] = true;
        myLineCode = *theLineCode;
    }

    if( theFrameFormat )
    {
        myBitSet[ INDEX_FrameFormat ] = true;
        myFrameFormat = *theFrameFormat;
    }

    if( theClockQuality )
    {
        myBitSet[ INDEX_ClockQuality ] = true;
        myClockQuality = *theClockQuality;
    }

    if(theAlarmProfile)
    {
        myBitSet[ INDEX_AlarmProfile ] = true;
        myAlarmProfile = *theAlarmProfile;
    }

    if(thePST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }

    if(thePSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }

    if(theSST)
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
}

TL1_T1RspBlk::TL1_T1RspBlk(const TL1_T1RspBlk& t1Blk)
    : myBitSet( INDEX_END, false )
{
    myBitSet                      = t1Blk.myBitSet;
    myEntityName                  = t1Blk.myEntityName;
    myFacAddr                     = t1Blk.myFacAddr;
    myCardType                    = t1Blk.myCardType;
    mySubCardType                 = t1Blk.mySubCardType;
    myLineCode 					  = t1Blk.myLineCode;
	myFrameFormat				  = t1Blk.myFrameFormat;
	myClockQuality				  = t1Blk.myClockQuality;
	myAlarmProfile                = t1Blk.myAlarmProfile;
    myPST                         = t1Blk.myPST;
    myPSTQ                        = t1Blk.myPSTQ;
    mySST                         = t1Blk.mySST;    
    
}

TL1_T1RspBlk::~TL1_T1RspBlk()
{
}

TL1_T1RspBlk& TL1_T1RspBlk::operator=( const TL1_T1RspBlk& theBlock )
{
    myBitSet                      = theBlock.myBitSet;
    myEntityName                  = theBlock.myEntityName;
    myFacAddr                     = theBlock.myFacAddr;
    myCardType                    = theBlock.myCardType;
    mySubCardType                 = theBlock.mySubCardType;
    myLineCode 					  = theBlock.myLineCode;
	myFrameFormat				  = theBlock.myFrameFormat;
	myClockQuality				  = theBlock.myClockQuality;
    myAlarmProfile                = theBlock.myAlarmProfile;
    myPST                         = theBlock.myPST;
    myPSTQ                        = theBlock.myPSTQ;
    mySST                         = theBlock.mySST;

    return *this;
}

bool TL1_T1RspBlk::operator==( const TL1_T1RspBlk& theBlock ) const
{
    return ( myBitSet                      == theBlock.myBitSet &&
             myEntityName                  == theBlock.myEntityName &&
             myFacAddr                     == theBlock.myFacAddr &&
             myCardType                    == theBlock.myCardType &&
             mySubCardType                 == theBlock.mySubCardType &&
			 myLineCode 				   == theBlock.myLineCode &&
			 myFrameFormat				   == theBlock.myFrameFormat &&
			 myClockQuality				   == theBlock.myClockQuality &&
             myAlarmProfile                == theBlock.myAlarmProfile &&
             myPST                         == theBlock.myPST &&
             myPSTQ                        == theBlock.myPSTQ &&
             mySST                         == theBlock.mySST );
}

bool TL1_T1RspBlk::GetEntityName(string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetFacAddr( CT_TL1_FacAddr& theFacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        theFacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetCardType( CT_CardType& theCardType ) const
{
    if( true == myBitSet[ INDEX_CardType ] )
    {
        theCardType = myCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetSubCardType( CT_SubCardType& theSubCardType ) const
{
    if( true == myBitSet[ INDEX_SubCardType ] )
    {
        theSubCardType = mySubCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetLineCode( CT_FAC_LineCode& theLineCode ) const
{
    if( true == myBitSet[ INDEX_LineCode ] )
    {
        theLineCode = myLineCode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetFrameFormat( CT_FAC_FrameFormat& theFrameFormat ) const
{
    if( true == myBitSet[ INDEX_FrameFormat ] )
    {
        theFrameFormat = myFrameFormat;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetClockQuality( CT_FAC_RxSsm& theClockQuality ) const
{
    if( true == myBitSet[ INDEX_ClockQuality ] )
    {
        theClockQuality = myClockQuality;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_T1RspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
{
    if( true == myBitSet[ INDEX_AlarmProfile ] )
    {
        theAlarmProfile = myAlarmProfile;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetPST( CT_SM_PST& thePST ) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_T1RspBlk::GetSST( CT_SM_SST& theSST ) const
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        theSST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}

