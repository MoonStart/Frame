/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   The errors counter.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "PM_Counter.h"
#include <CommonTypes/CT_PMA_General.h>

using namespace std;


//-----------------------------------------------------------------
//##ModelId=3C1F6F8403B8
PM_Counter::PM_Counter ()
{
    ResetCount();
    my64BitPMSupported = false;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8403B9
PM_Counter::~PM_Counter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& operator <<( ostream& theStream, PM_Counter& theCounter )
{

#ifdef PSOSP
    uint32 aLowCurrCount  = theCounter.myCurrentCount;
    uint32 aLowLastCount  = theCounter.myLastCount;

    return theStream << FC_InsertVar(aLowCurrCount)
                     << FC_InsertVar(aLowLastCount);
#else
    uint32 aLowCurrCount  = (uint32)(theCounter.myCurrentCount % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
    uint32 aHighCurrCount = (uint32)(theCounter.myCurrentCount / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
    uint32 aLowLastCount  = (uint32)(theCounter.myLastCount % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
    uint32 aHighLastCount = (uint32)(theCounter.myLastCount / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);

    return theStream << FC_InsertVar(aLowCurrCount)
                     << FC_InsertVar(aHighCurrCount)
                     << FC_InsertVar(aLowLastCount)
                     << FC_InsertVar(aHighLastCount);
#endif
}

//-----------------------------------------------------------------
istream& operator >>( istream& theStream, PM_Counter& theCounter )
{
    uint32 aLowCurrCount  = 0;
    uint32 aHighCurrCount = 0; 
    uint32 aLowLastCount  = 0; 
    uint32 aHighLastCount = 0; 

    theStream >> FC_ExtractVar(aLowCurrCount)
              >> FC_ExtractVar(aHighCurrCount)
              >> FC_ExtractVar(aLowLastCount)
              >> FC_ExtractVar(aHighLastCount);

    theCounter.myCurrentCount = (aHighCurrCount * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowCurrCount;
    theCounter.myLastCount    = (aHighLastCount * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowLastCount;

    return theStream;
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_Counter::GetCount() const
{
	CT_PM_64bit_ull countChange;

	// Check and adjust for count rollover
    // This rollover compensation assumes that this counter will 
    // rollover at most once between update invocations.
	if( myCurrentCount >=  myLastCount )
	{
		// No rollover. Calculate the change. 
		countChange = myCurrentCount - myLastCount;
	}
	else
	{
        //-------------------------------------------------------------------
		// The count has rolled over. Calculate change based on the rollover.
        //-------------------------------------------------------------------
        if ( my64BitPMSupported )
            countChange = ((static_cast<CT_PM_64bit_ull>(0xffffffffffffffff)) - myLastCount) + myCurrentCount + 1;
        else
            countChange = ((static_cast<CT_PM_64bit_ull>(0xffffffff)) - myLastCount) + myCurrentCount + 1;
	}

	return countChange;
}
