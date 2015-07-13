/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         November 7, 2005 - Ed Bandyk
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_RtrvOptPwrRspBlk.h>

TL1_RtrvOptPwrRspBlk::TL1_RtrvOptPwrRspBlk()
{;}

TL1_RtrvOptPwrRspBlk::TL1_RtrvOptPwrRspBlk( const string* theEntityName,
                            const CT_TL1_SlotAddr* theSlotAddr,
                            const CT_MeasOptChanNum* theChannel,
                            const CT_TL1_Port* thePort,
                            const CT_MeasOptChanNum* theLane,
                            CT_TEL_mBm* theAttn,               
                            CT_TEL_mBm* theIGain,              
                            CT_TEL_mBm* theOGain,  
                            CT_TEL_mBm* theEstOptPwr,
                            CT_TEL_mBm* theLsrOptPwr,          
                            CT_TEL_mBm* theLstOptPwr,          
	                        CT_TEL_mBm* thePsrOptPwr,			
                            CT_TEL_mBm* thePstOptPwr,		
							CT_TEL_mBm* thePsrLaneLowOptPwr,			
							CT_TEL_mBm* thePsrLaneHighOptPwr,		
							CT_TEL_mBm* thePstLaneLowOptPwr,			
							CT_TEL_mBm* thePstLaneHighOptPwr,
							CT_TEL_mBm* thePsrLaneNumOptPwr,			
							CT_TEL_mBm* thePstLaneNumOptPwr,							
							CT_TEL_mBm* theDsrOptPwr,
	                        CT_TEL_mBm* theDstOptPwr,		
                            CT_TimeTm* theDateTime )
    : myBitSet( INDEX_END, false), myChannel(CT_MEAS_OPT_CHAN_NUM_NA), myPort(CT_TL1_PORT_UNKNOWN), myLane(CT_MEAS_OPT_CHAN_NUM_NA),
    myAttn(TRAFFIC_DEFAULT_POWER), myIGain(TRAFFIC_DEFAULT_POWER), myOGain(TRAFFIC_DEFAULT_POWER), 
    myEstOptPwr(TRAFFIC_DEFAULT_POWER), myLsrOptPwr(TRAFFIC_DEFAULT_POWER), myLstOptPwr(TRAFFIC_DEFAULT_POWER), 
    myPsrOptPwr(TRAFFIC_DEFAULT_POWER), myPstOptPwr(TRAFFIC_DEFAULT_POWER), myPsrLaneLowOptPwr(TRAFFIC_DEFAULT_POWER), 
	myPsrLaneHighOptPwr(TRAFFIC_DEFAULT_POWER), myPstLaneLowOptPwr(TRAFFIC_DEFAULT_POWER),	myPstLaneHighOptPwr(TRAFFIC_DEFAULT_POWER), 
	myPsrLaneNumOptPwr(TRAFFIC_DEFAULT_POWER),	myPstLaneNumOptPwr(TRAFFIC_DEFAULT_POWER), 
	myDsrOptPwr(TRAFFIC_DEFAULT_POWER), myDstOptPwr(TRAFFIC_DEFAULT_POWER),	myDateTime()
{
    if ( theEntityName )  
    {
		myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if ( theSlotAddr )  
    {
		myBitSet[ INDEX_SlotAddr ] = true;
        mySlotAddr = *theSlotAddr;
    }

    if ( theChannel )  
    {
		myBitSet[ INDEX_Channel ] = true;
        myChannel = *theChannel;
    }

    if ( thePort )  
    {
		myBitSet[ INDEX_Port ] = true;
        myPort = *thePort;
    }

    if ( theLane )  
    {
		myBitSet[ INDEX_Lane ] = true;
        myLane = *theLane;
    }

    if ( theAttn )  
    {
		myBitSet[ INDEX_Attn ] = true;
        myAttn = *theAttn;
    }

    if ( theIGain )  
    {
		myBitSet[ INDEX_IGain ] = true;
        myIGain = *theIGain;
    }

    if ( theOGain )  
    {
		myBitSet[ INDEX_OGain ] = true;
        myOGain = *theOGain;
    }

    if ( theEstOptPwr )  
    {
		myBitSet[ INDEX_EstOptPwr ] = true;
        myEstOptPwr = *theEstOptPwr;
    }

    if ( theLsrOptPwr )  
    {
		myBitSet[ INDEX_LsrOptPwr ] = true;
        myLsrOptPwr = *theLsrOptPwr;
    }

    if ( theLstOptPwr )  
    {
		myBitSet[ INDEX_LstOptPwr ] = true;
        myLstOptPwr = *theLstOptPwr;
    }

    if ( thePsrOptPwr )  
    {
		myBitSet[ INDEX_PsrOptPwr ] = true;
        myPsrOptPwr = *thePsrOptPwr;
    }

    if ( thePstOptPwr )  
    {
		myBitSet[ INDEX_PstOptPwr ] = true;
        myPstOptPwr = *thePstOptPwr;
    }

	if ( thePsrLaneLowOptPwr )  
	{
		myBitSet[ INDEX_PsrLaneLowOptPwr ] = true;
		myPsrLaneLowOptPwr = *thePsrLaneLowOptPwr;
	}

	if ( thePsrLaneHighOptPwr )  
	{
		myBitSet[ INDEX_PsrLaneHighOptPwr ] = true;
		myPsrLaneHighOptPwr = *thePsrLaneHighOptPwr;
	}

	if ( thePstLaneLowOptPwr )  
	{
		myBitSet[ INDEX_PstLaneLowOptPwr ] = true;
		myPstLaneLowOptPwr = *thePstLaneLowOptPwr;
	}

	if ( thePstLaneHighOptPwr )  
	{
		myBitSet[ INDEX_PstLaneHighOptPwr ] = true;
		myPstLaneHighOptPwr = *thePstLaneHighOptPwr;
	}

	if ( thePsrLaneNumOptPwr )  
	{
		myBitSet[ INDEX_PsrLaneNumOptPwr ] = true;
		myPsrLaneNumOptPwr = *thePsrLaneNumOptPwr;
	}

	if ( thePstLaneNumOptPwr )  
	{
		myBitSet[ INDEX_PstLaneNumOptPwr ] = true;
		myPstLaneNumOptPwr = *thePstLaneNumOptPwr;
	}

	if ( theDsrOptPwr )
	{
		myBitSet[ INDEX_DsrOptPwr ] = true;
		myDsrOptPwr = *theDsrOptPwr;
	}

	if ( theDstOptPwr )
	{
		myBitSet[ INDEX_DstOptPwr ] = true;
		myDstOptPwr = *theDstOptPwr;
	}

	if ( theDateTime )  
    {
		myBitSet[ INDEX_DateTime ] = true;
        myDateTime = *theDateTime;
    }
}

TL1_RtrvOptPwrRspBlk::TL1_RtrvOptPwrRspBlk(const TL1_RtrvOptPwrRspBlk& theBlock)
{
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName; 
    mySlotAddr      = theBlock.mySlotAddr; 
    myChannel       = theBlock.myChannel; 
    myPort          = theBlock.myPort; 
	myLane       = theBlock.myLane; 
    myAttn          = theBlock.myAttn;                
    myIGain         = theBlock.myIGain;               
    myOGain         = theBlock.myOGain;  
    myEstOptPwr     = theBlock.myEstOptPwr;   
    myLsrOptPwr     = theBlock.myLsrOptPwr;           
    myLstOptPwr     = theBlock.myLstOptPwr;           
    myPsrOptPwr     = theBlock.myPsrOptPwr; 			
    myPstOptPwr     = theBlock.myPstOptPwr; 		
	myPsrLaneLowOptPwr   = theBlock.myPsrLaneLowOptPwr; 			
	myPsrLaneHighOptPwr   = theBlock.myPsrLaneHighOptPwr; 		
	myPstLaneLowOptPwr   = theBlock.myPstLaneLowOptPwr; 			
	myPstLaneHighOptPwr   = theBlock.myPstLaneHighOptPwr; 
	myPsrLaneNumOptPwr   = theBlock.myPsrLaneNumOptPwr; 			
	myPstLaneNumOptPwr   = theBlock.myPstLaneNumOptPwr;	
	myDsrOptPwr		= theBlock.myDsrOptPwr;
	myDstOptPwr		= theBlock.myDstOptPwr;		
    myDateTime      = theBlock.myDateTime;
}

TL1_RtrvOptPwrRspBlk::~TL1_RtrvOptPwrRspBlk()
{
}

TL1_RtrvOptPwrRspBlk& TL1_RtrvOptPwrRspBlk::operator=( const TL1_RtrvOptPwrRspBlk& theBlock )
{
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName; 
    mySlotAddr      = theBlock.mySlotAddr; 
    myChannel       = theBlock.myChannel; 
    myPort          = theBlock.myPort; 
	myLane       = theBlock.myLane;
    myAttn          = theBlock.myAttn;                
    myIGain         = theBlock.myIGain;               
    myOGain         = theBlock.myOGain;
    myEstOptPwr     = theBlock.myEstOptPwr;  
    myLsrOptPwr     = theBlock.myLsrOptPwr;           
    myLstOptPwr     = theBlock.myLstOptPwr;           
    myPsrOptPwr     = theBlock.myPsrOptPwr; 			
    myPstOptPwr     = theBlock.myPstOptPwr; 		
	myPsrLaneLowOptPwr   = theBlock.myPsrLaneLowOptPwr; 			
	myPsrLaneHighOptPwr   = theBlock.myPsrLaneHighOptPwr; 		
	myPstLaneLowOptPwr   = theBlock.myPstLaneLowOptPwr; 			
	myPstLaneHighOptPwr   = theBlock.myPstLaneHighOptPwr; 	
	myPsrLaneNumOptPwr   = theBlock.myPsrLaneNumOptPwr; 			
	myPstLaneNumOptPwr   = theBlock.myPstLaneNumOptPwr;	
	myDsrOptPwr		= theBlock.myDsrOptPwr;
	myDstOptPwr		= theBlock.myDstOptPwr;		
    myDateTime      = theBlock.myDateTime;

    return *this;
}

bool TL1_RtrvOptPwrRspBlk::operator==( const TL1_RtrvOptPwrRspBlk& theBlock ) const
{
    return (    myBitSet        == theBlock.myBitSet &&
                myEntityName    == theBlock.myEntityName && 
                mySlotAddr      == theBlock.mySlotAddr && 
                myChannel       == theBlock.myChannel && 
                myPort          == theBlock.myPort &&
                myLane       == theBlock.myLane && 
                myAttn          == theBlock.myAttn &&                
                myIGain         == theBlock.myIGain &&               
                myOGain         == theBlock.myOGain && 
                myEstOptPwr     == theBlock.myEstOptPwr &&    
                myLsrOptPwr     == theBlock.myLsrOptPwr &&          
                myLstOptPwr     == theBlock.myLstOptPwr &&           
                myPsrOptPwr     == theBlock.myPsrOptPwr && 			
                myPstOptPwr     == theBlock.myPstOptPwr && 		
				myPsrLaneLowOptPwr   == theBlock.myPsrLaneLowOptPwr &&
				myPsrLaneHighOptPwr   == theBlock.myPsrLaneHighOptPwr &&
				myPstLaneLowOptPwr   == theBlock.myPstLaneLowOptPwr &&
				myPstLaneHighOptPwr   == theBlock.myPstLaneHighOptPwr &&
				myPsrLaneNumOptPwr   == theBlock.myPsrLaneNumOptPwr &&
				myPstLaneNumOptPwr   == theBlock.myPstLaneNumOptPwr &&				
				myDsrOptPwr		== theBlock.myDsrOptPwr &&
				myDstOptPwr		== theBlock.myDstOptPwr &&
                myDateTime      == theBlock.myDateTime );
}

bool TL1_RtrvOptPwrRspBlk::GetEntityName( string& entityName) const
{
    if ( true == myBitSet[ INDEX_EntityName ] )
	{
    	entityName = myEntityName;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr) const
{
    if ( true == myBitSet[ INDEX_SlotAddr ] )
	{
   	    slotAddr = mySlotAddr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetChannel(CT_MeasOptChanNum& theChannel) const
{
    if ( true == myBitSet[ INDEX_Channel ] )
	{
   	    theChannel = myChannel;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPort(CT_TL1_Port& thePort) const
{
    if ( true == myBitSet[ INDEX_Port ] )
	{
   	    thePort = myPort;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetLane(CT_MeasOptChanNum& theLane) const
{
    if ( true == myBitSet[ INDEX_Lane ] )
	{
   	    theLane = myLane;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetAttn(CT_TEL_mBm& theAttn) const
{
    if ( true == myBitSet[ INDEX_Attn ] )
	{
   	    theAttn = myAttn;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetIGain(CT_TEL_mBm& theIGain) const
{
    if ( true == myBitSet[ INDEX_IGain ] )
	{
   	    theIGain = myIGain;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetOGain(CT_TEL_mBm& theOGain) const
{
    if ( true == myBitSet[ INDEX_OGain ] )
	{
   	    theOGain = myOGain;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetEstOptPwr(CT_TEL_mBm& theEstOptPwr) const
{
    if ( true == myBitSet[ INDEX_EstOptPwr ] )
	{
   	    theEstOptPwr = myEstOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetLsrOptPwr(CT_TEL_mBm& theLsrOptPwr) const
{
    if ( true == myBitSet[ INDEX_LsrOptPwr ] )
	{
   	    theLsrOptPwr = myLsrOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetLstOptPwr(CT_TEL_mBm& theLstOptPwr) const
{
    if ( true == myBitSet[ INDEX_LstOptPwr ] )
	{
   	    theLstOptPwr = myLstOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPsrOptPwr(CT_TEL_mBm& thePsrOptPwr) const
{
    if ( true == myBitSet[ INDEX_PsrOptPwr ] )
	{
   	    thePsrOptPwr = myPsrOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPstOptPwr(CT_TEL_mBm& thePstOptPwr) const
{
    if ( true == myBitSet[ INDEX_PstOptPwr ] )
	{
   	    thePstOptPwr = myPstOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPsrLaneLowOptPwr(CT_TEL_mBm& thePsrLaneLowOptPwr) const
{
    if ( true == myBitSet[ INDEX_PsrLaneLowOptPwr ] )
	{
   	    thePsrLaneLowOptPwr = myPsrLaneLowOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPsrLaneHighOptPwr(CT_TEL_mBm& thePsrLaneHighOptPwr) const
{
    if ( true == myBitSet[ INDEX_PsrLaneHighOptPwr ] )
	{
   	    thePsrLaneHighOptPwr = myPsrLaneHighOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPstLaneLowOptPwr(CT_TEL_mBm& thePstLaneLowOptPwr) const
{
    if ( true == myBitSet[ INDEX_PstLaneLowOptPwr ] )
	{
   	    thePstLaneLowOptPwr = myPstLaneLowOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPstLaneHighOptPwr(CT_TEL_mBm& thePstLaneHighOptPwr) const
{
    if ( true == myBitSet[ INDEX_PstLaneHighOptPwr ] )
	{
   	    thePstLaneHighOptPwr = myPstLaneHighOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPsrLaneNumOptPwr(CT_TEL_mBm& thePsrLaneNumOptPwr) const
{
    if ( true == myBitSet[ INDEX_PsrLaneNumOptPwr ] )
	{
   	    thePsrLaneNumOptPwr = myPsrLaneNumOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetPstLaneNumOptPwr(CT_TEL_mBm& thePstLaneNumOptPwr) const
{
    if ( true == myBitSet[ INDEX_PstLaneNumOptPwr ] )
	{
   	    thePstLaneNumOptPwr = myPstLaneNumOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetDsrOptPwr(CT_TEL_mBm& theDsrOptPwr) const
{
    if ( true == myBitSet[ INDEX_DsrOptPwr ] )
	{
   	    theDsrOptPwr = myDsrOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetDstOptPwr(CT_TEL_mBm& theDstOptPwr) const
{
    if ( true == myBitSet[ INDEX_DstOptPwr ] )
	{
   	    theDstOptPwr = myDstOptPwr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_RtrvOptPwrRspBlk::GetDateTime(CT_TimeTm& theDateTime) const
{
    if ( true == myBitSet[ INDEX_DateTime ] )
	{
   	    theDateTime = myDateTime;
	    return true;
	}
	else
	{
		return false;
	}
}



