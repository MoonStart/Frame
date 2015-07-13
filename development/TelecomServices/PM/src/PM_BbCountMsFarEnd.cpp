/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 1999 Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of Far-End SONET/SDH MS layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_MsCounters.h>
#include <PM_BbCountMsFarEnd.h>


//-----------------------------------------------------------------
PM_BbCountMsFarEnd::PM_BbCountMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbCountMsFarEnd::~PM_BbCountMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountMsFarEnd::Update(MON_MsCounters& theCounter) 
{
    uint32 count = 0;

    theCounter.GetErrorCount(CT_TEL_MS_REI, &count);
    myREICounter.Update(count);
}

//-----------------------------------------------------------------
ostream& PM_BbCountMsFarEnd::WriteObject( ostream& theStream )
{
    return theStream << myREICounter;

}

//-----------------------------------------------------------------
istream& PM_BbCountMsFarEnd::ReadObject( istream& theStream )
{
    return theStream >> myREICounter;

}

//-----------------------------------------------------------------
void PM_BbCountMsFarEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
