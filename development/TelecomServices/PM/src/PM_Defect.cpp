/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   The defect counters and states.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "PM_Defect.h"


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F8400AB
PM_Defect::PM_Defect ()
{
    myCurrentCount = 0;
    myLastCount = 0;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8400AC
PM_Defect::~PM_Defect ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8400B5
bool PM_Defect::IsDeclared() const
{
    return ( (myCurrentCount & PM_DEF_BIT) || (myCurrentCount != myLastCount) );

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8400BF
void PM_Defect::Update( bool theState, uint32 theNewCount) 
{
    // Last count become current.
    myLastCount = myCurrentCount;
    // Current count is the new count with bit 7 to 1 if the state
    // is true, 0 if the state is false.
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif
    myCurrentCount = (theNewCount & (~PM_DEF_BIT)) | (theState ? PM_DEF_BIT : 0);
#ifdef WIN32
#pragma warning( pop ) 
#endif

}

//-----------------------------------------------------------------
ostream& operator <<( ostream& theStream, PM_Defect& theDefect )
{
    return theStream << FC_InsertVar(theDefect.myCurrentCount)
                     << FC_InsertVar(theDefect.myLastCount);

}

//-----------------------------------------------------------------
istream& operator >>( istream& theStream, PM_Defect& theDefect )
{
    return theStream >> FC_ExtractVar(theDefect.myCurrentCount)
                     >> FC_ExtractVar(theDefect.myLastCount);

}
