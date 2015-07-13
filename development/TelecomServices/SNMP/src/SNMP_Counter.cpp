/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :    
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "SNMP_Counter.h"

using namespace std;


//-----------------------------------------------------------------
SNMP_Counter::SNMP_Counter ()
{
    ResetCount();

}

//-----------------------------------------------------------------
SNMP_Counter::~SNMP_Counter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& operator <<( ostream& theStream, SNMP_Counter& theCounter )
{
    return theStream << FC_InsertVar(theCounter.myCurrentCount)
                     << FC_InsertVar(theCounter.myLastCount);

}

//-----------------------------------------------------------------
istream& operator >>( istream& theStream, SNMP_Counter& theCounter )
{
    return theStream >> FC_ExtractVar(theCounter.myCurrentCount)
                     >> FC_ExtractVar(theCounter.myLastCount);

}
