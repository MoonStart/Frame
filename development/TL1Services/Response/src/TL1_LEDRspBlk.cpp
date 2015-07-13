/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_LEDRspBlk.h>

TL1_LEDRspBlk::TL1_LEDRspBlk(){;}

TL1_LEDRspBlk::TL1_LEDRspBlk(const string* entityName,
                  const CT_TL1_SlotAddr* slotAddr,
                  const CT_LEDColor  Active, // not optional
                  const CT_LEDColor  Power,  // not optional
                  const CT_LEDColor  Fault,  // not optional
                  const CT_LEDColor* ActLine,
                  const CT_LEDColor* Line,
                  const CT_LEDColor* Express,
                  const CT_LEDColor* Port,
                  const CT_LEDColor* Port1,
                  const CT_LEDColor* Port2,
                  const CT_LEDColor* Port3,
                  const CT_LEDColor* Port4,
                  const CT_LEDColor* Port5,
                  const CT_LEDColor* Port6,
                  const CT_LEDColor* Port7,
                  const CT_LEDColor* Port8,
                  const CT_LEDColor* Port9,
                  const CT_LEDColor* Port10,
                  const CT_LEDColor* Input,
                  const CT_LEDColor* Lpbk,
                  const CT_LEDColor* Sync,
                  const CT_LEDColor* Osc,
                  const CT_LEDColor* NeCr,
                  const CT_LEDColor* NeMj,
                  const CT_LEDColor* NeMn,
                  const CT_LEDColor* Ocp1,
                  const CT_LEDColor* Ocp2,
                  const CT_LEDColor* Ocp3,
                  const CT_LEDColor* Ocp4,
                  const CT_LEDColor* Apr,
                  const CT_LEDColor* DWDM44,
                  const CT_LEDColor* DWDM45,
                  const CT_LEDColor* DWDM1,
                  const CT_LEDColor* DWDM2,
                  const CT_LEDColor* Bits,
                  const CT_LEDColor* Aco,
                  const CT_LEDColor* Port11,
                  const CT_LEDColor* Port12,
                  const CT_LEDColor* Port13,
                  const CT_LEDColor* Port14,
                  const CT_LEDColor* Mode,
                  const CT_LEDColor* Port15,
                  const CT_LEDColor* Port16,
                  const CT_LEDColor* Port17,
                  const CT_LEDColor* Port18,
                  const CT_LEDColor* Port19,
                  const CT_LEDColor* Port20,
                  const CT_LEDColor* Port21,
                  const CT_LEDColor* Port22,
                  const CT_LEDColor* Port23,
                  const CT_LEDColor* Port24,
                  const CT_LEDColor* Port25,
                  const CT_LEDColor* Port26,
                  const CT_LEDColor* Port27,
                  const CT_LEDColor* Port28,
                  const CT_LEDColor* Port29,
                  const CT_LEDColor* Port30,
                  const CT_LEDColor* Port31,
                  const CT_LEDColor* Port32,
		          const CT_LEDColor* ActFlt)

: myBitSet( INDEX_END, false), mySlotAddr(*slotAddr)

{
    if( entityName )  
    {
		myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *entityName;
    }

    if( slotAddr )  
    {
		myBitSet[ INDEX_SlotAddr ] = true;
        mySlotAddr = *slotAddr;
    }

    //----------------------------------------------
    // not optional
    //----------------------------------------------
	myBitSet[ INDEX_Active ] = true;
    myActive = Active;
    
	myBitSet[ INDEX_Power ] = true;
    myPower = Power;

    myBitSet[ INDEX_Fault ] = true;
    myFault = Fault;
    //----------------------------------------------
    // not optional
    //----------------------------------------------

    if( ActLine )
    {
		myBitSet[ INDEX_ActLine ] = true;
        myActLine = *ActLine;
    }

    if( Line )
    {
		myBitSet[ INDEX_Line ] = true;
        myLine = *Line;
    }

    if( Express )
    {
		myBitSet[ INDEX_Express ] = true;
        myExpress = *Express;
    }

    if( Port )
    {
		myBitSet[ INDEX_Port ] = true;
        myPort = *Port;
    }

    if( Port1 )
    {
		myBitSet[ INDEX_Port1 ] = true;
        myPort1 = *Port1;
    }

    if( Port2 )
    {
		myBitSet[ INDEX_Port2 ] = true;
        myPort2 = *Port2;
    }

    if( Port3 )
    {
		myBitSet[ INDEX_Port3 ] = true;
        myPort3 = *Port3;
    }

    if( Port4 )
    {
		myBitSet[ INDEX_Port4 ] = true;
        myPort4 = *Port4;
    }

    if( Port5 )
    {
		myBitSet[ INDEX_Port5 ] = true;
        myPort5 = *Port5;
    }

    if( Port6 )
    {
		myBitSet[ INDEX_Port6 ] = true;
        myPort6 = *Port6;
    }

    if( Port7 )
    {
		myBitSet[ INDEX_Port7 ] = true;
        myPort7 = *Port7;
    }

    if( Port8 )
    {
		myBitSet[ INDEX_Port8 ] = true;
        myPort8 = *Port8;
    }

    if( Port9 )
    {
		myBitSet[ INDEX_Port9 ] = true;
        myPort9 = *Port9;
    }

    if( Port10 )
    {
		myBitSet[ INDEX_Port10 ] = true;
        myPort10 = *Port10;
    }

    if( Port11 )
    {
		myBitSet[ INDEX_Port11 ] = true;
        myPort11 = *Port11;
    }

    if( Port12 )
    {
		myBitSet[ INDEX_Port12 ] = true;
        myPort12 = *Port12;
    }

    if( Port13 )
    {
		myBitSet[ INDEX_Port13 ] = true;
        myPort13 = *Port13;
    }

    if( Port14 )
    {
		myBitSet[ INDEX_Port14 ] = true;
        myPort14 = *Port14;
    }

    if( Input )
    {
		myBitSet[ INDEX_Input ] = true;
        myInput = *Input;
    }

    if( Lpbk )
    {
		myBitSet[ INDEX_Lpbk ] = true;
        myLpbk = *Lpbk;
    }

    if( Sync )
    {
		myBitSet[ INDEX_Sync ] = true;
        mySync = *Sync;
    }

    if( Osc )
    {
		myBitSet[ INDEX_Osc ] = true;
        myOsc = *Osc;
    }

    if( NeCr )
    {
		myBitSet[ INDEX_NeCr ] = true;
        myNeCr = *NeCr;
    }

    if( NeMj )
    {
		myBitSet[ INDEX_NeMj ] = true;
        myNeMj = *NeMj;
    }

    if( NeMn )
    {
		myBitSet[ INDEX_NeMn ] = true;
        myNeMn = *NeMn;
    }

    if( Ocp1 )
    {
		myBitSet[ INDEX_Ocp1 ] = true;
        myOcp1 = *Ocp1;
    }

    if( Ocp2 )
    {
		myBitSet[ INDEX_Ocp2 ] = true;
        myOcp2 = *Ocp2;
    }

    if( Ocp3 )
    {
		myBitSet[ INDEX_Ocp3 ] = true;
        myOcp3 = *Ocp3;
    }

    if( Ocp4 )
    {
		myBitSet[ INDEX_Ocp4 ] = true;
        myOcp4 = *Ocp4;
    }

    if( Apr )
    {
		myBitSet[ INDEX_Apr ] = true;
        myApr = *Apr;
    }

    if( DWDM44 )
    {
		myBitSet[ INDEX_DWDM44 ] = true;
        myDWDM44 = *DWDM44;
    }

    if( DWDM45 )
    {
		myBitSet[ INDEX_DWDM45 ] = true;
        myDWDM45 = *DWDM45;
    }

    if( DWDM1 )
    {
		myBitSet[ INDEX_DWDM1 ] = true;
        myDWDM1 = *DWDM1;
    }

    if( DWDM2 )
    {
		myBitSet[ INDEX_DWDM2 ] = true;
        myDWDM2 = *DWDM2;
    }

    if( Bits )
    {
		myBitSet[ INDEX_Bits ] = true;
        myBits = *Bits;
    }
    
    if( Aco )
    {
		myBitSet[ INDEX_Aco ] = true;
        myAco = *Aco;
    }

	if( Mode )
    {
		myBitSet[ INDEX_Mode ] = true;
        myMode = *Mode;
    }
    
    if( Port15 )
    {
		myBitSet[ INDEX_Port15 ] = true;
        myPort15 = *Port15;
    }

    if( Port16 )
    {
		myBitSet[ INDEX_Port16 ] = true;
        myPort16 = *Port16;
    }

    if( Port17 )
    {
		myBitSet[ INDEX_Port17 ] = true;
        myPort17 = *Port17;
    }

    if( Port18 )
    {
		myBitSet[ INDEX_Port18 ] = true;
        myPort18 = *Port18;
    }

    if( Port19 )
    {
		myBitSet[ INDEX_Port19 ] = true;
        myPort19 = *Port19;
    }

    if( Port20 )
    {
		myBitSet[ INDEX_Port20 ] = true;
        myPort20 = *Port20;
    }

    if( Port21 )
    {
		myBitSet[ INDEX_Port21 ] = true;
        myPort21 = *Port21;
    }

    if( Port22 )
    {
		myBitSet[ INDEX_Port22 ] = true;
        myPort22 = *Port22;
    }

    if( Port23 )
    {
		myBitSet[ INDEX_Port23 ] = true;
        myPort23 = *Port23;
    }

    if( Port24 )
    {
		myBitSet[ INDEX_Port24 ] = true;
        myPort24 = *Port24;
    }

    if( Port25 )
    {
		myBitSet[ INDEX_Port25 ] = true;
        myPort25 = *Port25;
    }

    if( Port26 )
    {
		myBitSet[ INDEX_Port26 ] = true;
        myPort26 = *Port26;
    }

    if( Port27 )
    {
		myBitSet[ INDEX_Port27 ] = true;
        myPort27 = *Port27;
    }

    if( Port28 )
    {
		myBitSet[ INDEX_Port28 ] = true;
        myPort28 = *Port28;
    }

    if( Port29 )
    {
		myBitSet[ INDEX_Port29 ] = true;
        myPort29 = *Port29;
    }

    if( Port30 )
    {
		myBitSet[ INDEX_Port30 ] = true;
        myPort30 = *Port30;
    }

    if( Port31 )
    {
		myBitSet[ INDEX_Port31 ] = true;
        myPort31 = *Port31;
    }

    if( Port32 )
    {
		myBitSet[ INDEX_Port32 ] = true;
        myPort32 = *Port32;
    }

    if( ActFlt )
    {
		myBitSet[ INDEX_ActFlt ] = true;
        myActFlt = *ActFlt;
    }
}

TL1_LEDRspBlk::TL1_LEDRspBlk (const TL1_LEDRspBlk& ledBlk) : mySlotAddr(0,0)
{
    myBitSet      = ledBlk.myBitSet;
    myEntityName  = ledBlk.myEntityName; 
    mySlotAddr    = ledBlk.mySlotAddr; 
	myActive      = ledBlk.myActive; 
	myPower       = ledBlk.myPower;
	myFault       = ledBlk.myFault;
	myActLine     = ledBlk.myActLine;
	myLine        = ledBlk.myLine;
	myExpress     = ledBlk.myExpress;
	myPort        = ledBlk.myPort;
	myPort1       = ledBlk.myPort1;
	myPort2       = ledBlk.myPort2;
	myPort3       = ledBlk.myPort3;
	myPort4       = ledBlk.myPort4;
	myPort5       = ledBlk.myPort5;
	myPort6       = ledBlk.myPort6;
	myPort7       = ledBlk.myPort7;
	myPort8       = ledBlk.myPort8;
	myPort9       = ledBlk.myPort9;
	myPort10      = ledBlk.myPort10;
	myPort11      = ledBlk.myPort11;
	myPort12      = ledBlk.myPort12;
	myPort13      = ledBlk.myPort13;
	myPort14      = ledBlk.myPort14;
	myInput       = ledBlk.myInput;
	myLpbk        = ledBlk.myLpbk;
	mySync        = ledBlk.mySync;
	myOsc         = ledBlk.myOsc;
	myNeCr        = ledBlk.myNeCr;
	myNeMj        = ledBlk.myNeMj;
	myNeMn        = ledBlk.myNeMn;
	myOcp1        = ledBlk.myOcp1;
	myOcp2        = ledBlk.myOcp2;
	myOcp3        = ledBlk.myOcp3;
	myOcp4        = ledBlk.myOcp4;
	myApr         = ledBlk.myApr;
	myDWDM44      = ledBlk.myDWDM44;
	myDWDM45      = ledBlk.myDWDM45;
	myDWDM1       = ledBlk.myDWDM1;
	myDWDM2       = ledBlk.myDWDM2;
	myBits        = ledBlk.myBits;
	myAco         = ledBlk.myAco;
	myMode        = ledBlk.myMode;
	myPort15       = ledBlk.myPort15;
	myPort16       = ledBlk.myPort16;
	myPort17       = ledBlk.myPort17;
	myPort18       = ledBlk.myPort18;
	myPort19       = ledBlk.myPort19;
	myPort20       = ledBlk.myPort20;
    myPort21       = ledBlk.myPort21;
    myPort22       = ledBlk.myPort22;
    myPort23       = ledBlk.myPort23;
    myPort24       = ledBlk.myPort24;
    myPort25       = ledBlk.myPort25;
    myPort26       = ledBlk.myPort26;
    myPort27       = ledBlk.myPort27;
    myPort28       = ledBlk.myPort28;
    myPort29       = ledBlk.myPort29;
    myPort30       = ledBlk.myPort30;
    myPort31       = ledBlk.myPort31;
    myPort32       = ledBlk.myPort32;
	myActFlt       = ledBlk.myActFlt;
}

TL1_LEDRspBlk::~TL1_LEDRspBlk()
{
}

TL1_LEDRspBlk& TL1_LEDRspBlk::operator=( const TL1_LEDRspBlk& theBlock )
{
    myBitSet      = theBlock.myBitSet;
    myEntityName  = theBlock.myEntityName; 
    mySlotAddr    = theBlock.mySlotAddr; 
    myActive      = theBlock.myActive;
    myPower       = theBlock.myPower;
    myFault       = theBlock.myFault;
    myActLine     = theBlock.myActLine;
    myLine        = theBlock.myLine;
    myExpress     = theBlock.myExpress;
    myPort        = theBlock.myPort;
    myPort1       = theBlock.myPort1;
    myPort2       = theBlock.myPort2;
    myPort3       = theBlock.myPort3;
    myPort4       = theBlock.myPort4;
    myPort5       = theBlock.myPort5;
    myPort6       = theBlock.myPort6;
    myPort7       = theBlock.myPort7;
    myPort8       = theBlock.myPort8;
    myPort9       = theBlock.myPort9;
    myPort10      = theBlock.myPort10;
    myPort11      = theBlock.myPort11;
    myPort12      = theBlock.myPort12;
    myPort13      = theBlock.myPort13;
    myPort14      = theBlock.myPort14;
    myInput       = theBlock.myInput;
    myLpbk        = theBlock.myLpbk;
    mySync        = theBlock.mySync;
    myOsc         = theBlock.myOsc;
    myNeCr        = theBlock.myNeCr;
    myNeMj        = theBlock.myNeMj;
    myNeMn        = theBlock.myNeMn;
    myOcp1        = theBlock.myOcp1;
    myOcp2        = theBlock.myOcp2;
    myOcp3        = theBlock.myOcp3;
    myOcp4        = theBlock.myOcp4;
    myApr         = theBlock.myApr;
    myDWDM44      = theBlock.myDWDM44;
    myDWDM45      = theBlock.myDWDM45;
    myDWDM1       = theBlock.myDWDM1;
    myDWDM2       = theBlock.myDWDM2;
    myBits        = theBlock.myBits;
    myAco         = theBlock.myAco;
    myMode        = theBlock.myMode;
    myPort15       = theBlock.myPort15;
    myPort16       = theBlock.myPort16;
    myPort17       = theBlock.myPort17;
    myPort18       = theBlock.myPort18;
    myPort19       = theBlock.myPort19;
    myPort20       = theBlock.myPort20;
    myPort21       = theBlock.myPort21;
    myPort22	   = theBlock.myPort22;
    myPort23	   = theBlock.myPort23;
    myPort24	   = theBlock.myPort24;
    myPort25	   = theBlock.myPort25;
    myPort26	   = theBlock.myPort26;
    myPort27	   = theBlock.myPort27;
    myPort28	   = theBlock.myPort28;
    myPort29	   = theBlock.myPort29;
    myPort30	   = theBlock.myPort30;
    myPort31	   = theBlock.myPort31;
    myPort32	   = theBlock.myPort32;
    myActFlt       = theBlock.myActFlt;

    return *this;
}

bool TL1_LEDRspBlk::operator==( const TL1_LEDRspBlk& theBlock ) const
{
    return ( myBitSet      == theBlock.myBitSet &&
             myEntityName  == theBlock.myEntityName && 
             mySlotAddr    == theBlock.mySlotAddr && 
             myActive      == theBlock.myActive &&
             myPower       == theBlock.myPower &&
             myFault       == theBlock.myFault &&
             myActLine     == theBlock.myActLine &&
             myLine        == theBlock.myLine &&
             myExpress     == theBlock.myExpress &&
             myPort        == theBlock.myPort &&
             myPort1       == theBlock.myPort1 &&
             myPort2       == theBlock.myPort2 &&
             myPort3       == theBlock.myPort3 &&
             myPort4       == theBlock.myPort4 &&
             myPort5       == theBlock.myPort5 &&
             myPort6       == theBlock.myPort6 &&
             myPort7       == theBlock.myPort7 &&
             myPort8       == theBlock.myPort8 &&
             myPort9       == theBlock.myPort9 &&
             myPort10      == theBlock.myPort10 &&
             myPort11      == theBlock.myPort11 &&
             myPort12      == theBlock.myPort12 &&
             myPort13      == theBlock.myPort13 &&
             myPort14      == theBlock.myPort14 &&
             myInput       == theBlock.myInput &&
             myLpbk        == theBlock.myLpbk &&
             mySync        == theBlock.mySync &&
             myOsc         == theBlock.myOsc &&
             myNeCr        == theBlock.myNeCr &&
             myNeMj        == theBlock.myNeMj &&
             myNeMn        == theBlock.myNeMn &&
             myOcp1        == theBlock.myOcp1 &&
             myOcp2        == theBlock.myOcp2 &&
             myOcp3        == theBlock.myOcp3 &&
             myOcp4        == theBlock.myOcp4 &&
             myApr         == theBlock.myApr &&
             myDWDM44      == theBlock.myDWDM44 &&
             myDWDM45      == theBlock.myDWDM45 &&
             myDWDM1       == theBlock.myDWDM1 &&
             myDWDM2       == theBlock.myDWDM2 &&
             myBits        == theBlock.myBits &&
             myAco         == theBlock.myAco &&
             myMode        == theBlock.myMode &&
             myPort15      == theBlock.myPort15 &&
             myPort16      == theBlock.myPort16 &&
             myPort17      == theBlock.myPort17 &&
             myPort18      == theBlock.myPort18 &&
             myPort19      == theBlock.myPort19 &&
             myPort20      == theBlock.myPort20 &&
             myPort21      == theBlock.myPort21 &&
             myPort22      == theBlock.myPort22 &&
             myPort23      == theBlock.myPort23 &&
             myPort24      == theBlock.myPort24 &&
             myPort25      == theBlock.myPort25 &&
             myPort26      == theBlock.myPort26 &&
             myPort27      == theBlock.myPort27 &&
             myPort28      == theBlock.myPort28 &&
             myPort29      == theBlock.myPort29 &&
             myPort30      == theBlock.myPort30 &&
             myPort31      == theBlock.myPort31 &&
             myPort32      == theBlock.myPort32 &&
             myActFlt      == theBlock.myActFlt
           );
}

bool TL1_LEDRspBlk::GetEntityName( string& entityName) const
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

bool TL1_LEDRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr ) const
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

bool TL1_LEDRspBlk::GetActiveLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Active ] )
	{
    	theColor = myActive;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPowerLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Power ] )
	{
    	theColor = myPower;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetFaultLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Fault ] )
	{
    	theColor = myFault;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetActLineLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_ActLine ] )
	{
    	theColor = myActLine;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetLineLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Line ] )
	{
    	theColor = myLine;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetExpressLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Express ] )
	{
    	theColor = myExpress;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPortLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port ] )
	{
    	theColor = myPort;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort1LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port1 ] )
	{
    	theColor = myPort1;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort2LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port2 ] )
	{
    	theColor = myPort2;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort3LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port3 ] )
	{
    	theColor = myPort3;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort4LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port4 ] )
	{
    	theColor = myPort4;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort5LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port5 ] )
	{
    	theColor = myPort5;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort6LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port6 ] )
	{
    	theColor = myPort6;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort7LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port7 ] )
	{
    	theColor = myPort7;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort8LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port8 ] )
	{
    	theColor = myPort8;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort9LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port9 ] )
	{
    	theColor = myPort9;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort10LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port10 ] )
	{
    	theColor = myPort10;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort11LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port11 ] )
	{
    	theColor = myPort11;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort12LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port12 ] )
	{
    	theColor = myPort12;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort13LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port13 ] )
	{
    	theColor = myPort13;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort14LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port14 ] )
	{
    	theColor = myPort14;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetInputLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Input ] )
	{
    	theColor = myInput;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetLpbkLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Lpbk ] )
	{
    	theColor = myLpbk;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetSyncLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Sync ] )
	{
    	theColor = mySync;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetOscLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Osc ] )
	{
    	theColor = myOsc;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetNeCrLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_NeCr ] )
	{
    	theColor = myNeCr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetNeMjLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_NeMj ] )
	{
    	theColor = myNeMj;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetNeMnLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_NeMn ] )
	{
    	theColor = myNeMn;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetOcp1LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Ocp1 ] )
	{
    	theColor = myOcp1;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetOcp2LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Ocp2 ] )
	{
    	theColor = myOcp2;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetOcp3LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Ocp3 ] )
	{
    	theColor = myOcp3;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetOcp4LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Ocp4 ] )
	{
    	theColor = myOcp4;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetAprLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Apr ] )
	{
    	theColor = myApr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetDWDM44LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_DWDM44 ] )
	{
    	theColor = myDWDM44;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetDWDM45LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_DWDM45 ] )
	{
    	theColor = myDWDM45;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetDWDM1LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_DWDM1 ] )
	{
    	theColor = myDWDM1;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetDWDM2LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_DWDM2 ] )
	{
    	theColor = myDWDM2;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetBitsLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Bits ] )
	{
    	theColor = myBits;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetAcoLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Aco ] )
	{
    	theColor = myAco;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetModeLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Mode ] )
	{
    	theColor = myMode;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort15LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port15 ] )
	{
    	theColor = myPort15;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort16LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port16 ] )
	{
    	theColor = myPort16;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort17LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port17 ] )
	{
    	theColor = myPort17;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort18LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port18 ] )
	{
    	theColor = myPort18;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort19LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port19 ] )
	{
    	theColor = myPort19;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort20LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port20 ] )
	{
    	theColor = myPort20;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort21LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port21 ] )
	{
    	theColor = myPort21;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort22LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port22 ] )
	{
    	theColor = myPort22;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort23LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port23 ] )
	{
    	theColor = myPort23;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort24LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port24 ] )
	{
    	theColor = myPort24;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort25LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port25 ] )
	{
    	theColor = myPort25;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort26LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port26 ] )
	{
    	theColor = myPort26;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort27LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port27 ] )
	{
    	theColor = myPort27;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort28LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port28 ] )
	{
    	theColor = myPort28;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort29LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port29 ] )
	{
    	theColor = myPort29;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort30LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port30 ] )
	{
    	theColor = myPort30;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort31LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port31 ] )
	{
    	theColor = myPort31;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetPort32LED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_Port32 ] )
	{
    	theColor = myPort32;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_LEDRspBlk::GetActFltLED( CT_LEDColor& theColor ) const
{
    if( true == myBitSet[ INDEX_ActFlt ] )
	{
    	theColor = myActFlt;
		return true;
	}
	else
	{
		return false;
	}
}
