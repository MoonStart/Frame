/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     23 October, 2006 Larry M. Wolfrum.
 DESCRIPTION:   The errors counter, with a limit.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/src/PM_CounterLimit.h>


using namespace std;


//-----------------------------------------------------------------
//##ModelId=3C1F6F8403B8
PM_CounterLimit::PM_CounterLimit ( uint32 theLimit ):
	myLimit(theLimit)
{
    ResetCount();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8403B9
PM_CounterLimit::~PM_CounterLimit ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& operator <<( ostream& theStream, PM_CounterLimit& theCounter )
{
    return theStream << FC_InsertVar(theCounter.myCurrentCount)
                     << FC_InsertVar(theCounter.myLastCount);

}

//-----------------------------------------------------------------
istream& operator >>( istream& theStream, PM_CounterLimit& theCounter )
{
    return theStream >> FC_ExtractVar(theCounter.myCurrentCount)
                     >> FC_ExtractVar(theCounter.myLastCount);

}

