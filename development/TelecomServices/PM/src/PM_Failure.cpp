/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     12 Feb 2004  Hemant Thakkar
 DESCRIPTION:   The failure counters and states.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "PM_Failure.h"


using namespace std;

//-----------------------------------------------------------------
PM_Failure::PM_Failure ()
{
    myCurrentCount = 0;
    myLastCount = 0;

}

//-----------------------------------------------------------------
PM_Failure::~PM_Failure ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_Failure::DidTransitionToDeclared() const
{
    return ( (myCurrentCount & PM_FAIL_BIT) && (myCurrentCount != myLastCount) );

}

//-----------------------------------------------------------------
void PM_Failure::Update(bool theState) 
{
    // Last count become current.
    myLastCount = myCurrentCount;
    // Current count is the new count with bit 7 to 1 if the state
    // is true, 0 if the state is false.
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4800 )
#endif
    bool theCurrentState = (bool) (myCurrentCount & PM_FAIL_BIT);
    if (theCurrentState != theState) 
    {
        myCurrentCount = ((myCurrentCount + 1) & (~PM_FAIL_BIT)) | (theState ? PM_FAIL_BIT : 0);
    }
#ifdef WIN32
#pragma warning( pop ) 
#endif

}

//-----------------------------------------------------------------
ostream& operator <<( ostream& theStream, PM_Failure& theFailure )
{
    return theStream << FC_InsertVar(theFailure.myCurrentCount)
                     << FC_InsertVar(theFailure.myLastCount);

}

//-----------------------------------------------------------------
istream& operator >>( istream& theStream, PM_Failure& theFailure )
{
    return theStream >> FC_ExtractVar(theFailure.myCurrentCount)
                     >> FC_ExtractVar(theFailure.myLastCount);

}
