/*----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Tremblay
DESCRIPTION:    Implementation file for TL1 Alarm response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_MeasurePowerRspBlk.h>

#include <CommonTypes/CT_TL1_Error.h>

TL1_MeasurePowerResultItem::TL1_MeasurePowerResultItem()
: myPowerBit(false), mySnrBit(false), myOSnrBit(false),
myPower(TRAFFIC_DEFAULT_POWER), mySnr(TRAFFIC_DEFAULT_POWER), myOSnr(TRAFFIC_DEFAULT_POWER)
{
}

TL1_MeasurePowerResultItem::~TL1_MeasurePowerResultItem() 
{
}    

bool TL1_MeasurePowerResultItem::GetPower(CT_TEL_mBm &thePower) const 
{
    if (myPowerBit)
    {
        thePower = myPower;
        return true;
    }
    else
        return false;
}

bool TL1_MeasurePowerResultItem::GetPowerBit() const 
{
    return myPowerBit;
}

bool TL1_MeasurePowerResultItem::GetSnr(CT_TEL_mBm &theSnr) const 
{
    if (mySnrBit)
    {
        theSnr = mySnr;
        return true;
    }
    else
        return false;
}

bool TL1_MeasurePowerResultItem::GetSnrBit() const 
{
    return mySnrBit;
}

bool TL1_MeasurePowerResultItem::GetOSnr(CT_TEL_mBm &theOSnr) const 
{
    if (myOSnrBit)
    {
        theOSnr = myOSnr;
        return true;
    }
    else
        return false;
}

bool TL1_MeasurePowerResultItem::GetOSnrBit() const 
{
    return myOSnrBit;
}

void TL1_MeasurePowerResultItem::SetPower(CT_TEL_mBm thePower) {myPower = thePower;}
void TL1_MeasurePowerResultItem::SetPowerBit(bool thePowerBit) {myPowerBit = thePowerBit;}
void TL1_MeasurePowerResultItem::SetSnr(CT_TEL_mBm theSnr) {mySnr = theSnr;}
void TL1_MeasurePowerResultItem::SetSnrBit(bool theSnrBit) {mySnrBit = theSnrBit;}
void TL1_MeasurePowerResultItem::SetOSnr(CT_TEL_mBm theOSnr) {myOSnr = theOSnr;}
void TL1_MeasurePowerResultItem::SetOSnrBit(bool theOSnrBit) {myOSnrBit = theOSnrBit;}


TL1_MeasurePowerRspBlk::TL1_MeasurePowerRspBlk( ) : myChannel( CT_MEAS_OPT_CHAN_NUM_NA), myLane( CT_MEAS_OPT_CHAN_NUM_NA), myResults( CT_SIGNALDIRECTION_ALL)
{
}

TL1_MeasurePowerRspBlk::TL1_MeasurePowerRspBlk( const string* theEntityName,
                                            const CT_TL1_SlotAddr* theSlotAddr,
                                            const CT_MeasOptChanNum* theChannel,
                                            const CT_TL1_Port* thePort,
                                            const CT_MeasOptChanNum* theLane,
                                            const vector< TL1_MeasurePowerResultItem >* theResults,
                                            const CT_Yes_No_NA* theChannelEquipped, 
                                            const bool* thePortEquipped ) 
                                            : myBitSet( INDEX_END, false), myChannel( CT_MEAS_OPT_CHAN_NUM_NA ),myLane( CT_MEAS_OPT_CHAN_NUM_NA ), myResults( CT_SIGNALDIRECTION_ALL), myPort(CT_TL1_PORT_UNKNOWN),
											  myPortEquipped(false), myChannelEquipped(CT_NA)

{
    if( theEntityName )  
    {
		myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theSlotAddr )  
    {
		myBitSet[ INDEX_SlotAddr ] = true;
        mySlotAddr = *theSlotAddr;
    }

    if( theChannel )  
    {
		myBitSet[ INDEX_Channel ] = true;
        myChannel = *theChannel;
    }

    if( thePort )  
    {
		myBitSet[ INDEX_Port ] = true;
        myPort = *thePort;
    }

    if( theLane )  
    {
        myBitSet[ INDEX_Lane ] = true;
        myLane = *theLane;
    }

    if( theResults )  
    {
        if( theResults->size() != CT_SIGNALDIRECTION_ALL)
        {
            throw CT_TL1_SROFError(CT_TL1_SROFError::ER_SROF_CMD_NC); // TODO: Throw specific TL1Error.
        }

		myBitSet[ INDEX_Results ] = true;
        myResults = *theResults;
    }

    if( theChannelEquipped )  
    {
		myBitSet[ INDEX_ChannelEquipped ] = true;
        myChannelEquipped = *theChannelEquipped;
    }

    if( thePortEquipped )  
    {
		myBitSet[ INDEX_PortEquipped ] = true;
        myPortEquipped = *thePortEquipped;
    }
}

TL1_MeasurePowerRspBlk::~TL1_MeasurePowerRspBlk() 
{
}

TL1_MeasurePowerRspBlk::TL1_MeasurePowerRspBlk( const TL1_MeasurePowerRspBlk& theBlock ) :
    myEntityName( theBlock.myEntityName ),
    mySlotAddr( theBlock.mySlotAddr ),
    myChannel( theBlock.myChannel ),
    myPort( theBlock.myPort ),
    myLane( theBlock.myLane ),
    myResults( theBlock.myResults ),
    myChannelEquipped( theBlock.myChannelEquipped ),
    myPortEquipped( theBlock.myPortEquipped ),
    myBitSet( theBlock.myBitSet )
{
}

TL1_MeasurePowerRspBlk& TL1_MeasurePowerRspBlk::operator=( const TL1_MeasurePowerRspBlk& theBlock )
{
    myEntityName = theBlock.myEntityName;
    mySlotAddr = theBlock.mySlotAddr;
    myChannel = theBlock.myChannel;
    myPort = theBlock.myPort;
    myLane = theBlock.myLane;	
    myResults = theBlock.myResults;
    myChannelEquipped = theBlock.myChannelEquipped;
    myPortEquipped = theBlock.myPortEquipped;

    myBitSet = theBlock.myBitSet;

    return *this;
}

bool TL1_MeasurePowerRspBlk::GetEntityName( string& entityName) const
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

bool TL1_MeasurePowerRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr) const
{
    if( true == myBitSet[ INDEX_SlotAddr ] )
	{
   	    slotAddr = mySlotAddr;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetChannel(CT_MeasOptChanNum& theChannel) const
{
    if( true == myBitSet[ INDEX_Channel ] )
	{
   	    theChannel = myChannel;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPort(CT_TL1_Port& thePort) const
{
    if( true == myBitSet[ INDEX_Port ] )
	{
   	    thePort = myPort;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLane(CT_MeasOptChanNum& theLane) const
{
    if( true == myBitSet[ INDEX_Lane] )
    {
        theLane = myLane;
        return true;
    }
    else
    {
    	return false;
    }
}

bool TL1_MeasurePowerRspBlk::GetESTPower(CT_TEL_mBm& theESTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_EXPRESSTRANSMIT].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_EXPRESSTRANSMIT].GetPower(theESTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLSRPower(CT_TEL_mBm& theLSRPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINERECEIVE].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINERECEIVE].GetPower(theLSRPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLSRSnr(CT_TEL_mBm& theLSRSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINERECEIVE].GetSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINERECEIVE].GetSnr(theLSRSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLSTPower(CT_TEL_mBm& theLSTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetPower(theLSTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLSTOSnr(CT_TEL_mBm& theLSTOSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetOSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetOSnr(theLSTOSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetLSTSnr(CT_TEL_mBm& theLSTSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT].GetSnr(theLSTSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetALSTPower(CT_TEL_mBm& theALSTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT_A].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT_A].GetPower(theALSTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetALSTSnr(CT_TEL_mBm& theALSTSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT_A].GetSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT_A].GetSnr(theALSTSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetBLSTPower(CT_TEL_mBm& theBLSTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT_B].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT_B].GetPower(theBLSTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetBLSTSnr(CT_TEL_mBm& theBLSTSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINETRANSMIT_B].GetSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINETRANSMIT_B].GetSnr(theBLSTSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetALSRPower(CT_TEL_mBm& theALSRPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINERECEIVE_A].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINERECEIVE_A].GetPower(theALSRPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetBLSRPower(CT_TEL_mBm& theBLSRPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_LINERECEIVE_B].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_LINERECEIVE_B].GetPower(theBLSRPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSTPower(CT_TEL_mBm& thePSTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetPower(thePSTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSTOSnr(CT_TEL_mBm& thePSTOSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetOSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetOSnr(thePSTOSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSTSnr(CT_TEL_mBm& thePSTSnr) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetSnrBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT].GetSnr(thePSTSnr);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSRPower(CT_TEL_mBm& thePSRPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTRECEIVE].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTRECEIVE].GetPower(thePSRPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSRLLPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANELOW].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANELOW].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSRLHPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANEHIGH].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANEHIGH].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}
bool TL1_MeasurePowerRspBlk::GetPSTLLPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANELOW].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANELOW].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}
bool TL1_MeasurePowerRspBlk::GetPSTLHPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANEHIGH].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANEHIGH].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPSRLNPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANENUM].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTRECEIVE_LANENUM].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}
bool TL1_MeasurePowerRspBlk::GetPSTLNPower(CT_TEL_mBm& thePower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANENUM].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_PORTTRANSMIT_LANENUM].GetPower(thePower);
	    return true;
	}
	else
	{
		return false;
	}
}


bool TL1_MeasurePowerRspBlk::GetDSTPower(CT_TEL_mBm& theDSTPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_DCMTRANSMIT].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_DCMTRANSMIT].GetPower(theDSTPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetDSRPower(CT_TEL_mBm& theDSRPower) const
{
    if( true == myResults[CT_SIGNALDIRECTION_DCMRECEIVE].GetPowerBit() )
	{
   	    myResults[CT_SIGNALDIRECTION_DCMRECEIVE].GetPower(theDSRPower);
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetChannelEquipped(CT_Yes_No_NA& theChannelEquipped) const
{
    if( true == myBitSet[ INDEX_ChannelEquipped ] )
	{
   	    theChannelEquipped = myChannelEquipped;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_MeasurePowerRspBlk::GetPortEquipped(bool& thePortEquipped) const
{
    if( true == myBitSet[ INDEX_PortEquipped ] )
	{
   	    thePortEquipped = myPortEquipped;
	    return true;
	}
	else
	{
		return false;
	}
}
