/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 1999 Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of Near-End SONET/SDH MS layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_MsCounters.h>
#include <PM_BbCountMsNearEnd.h>


//-----------------------------------------------------------------
PM_BbCountMsNearEnd::PM_BbCountMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbCountMsNearEnd::~PM_BbCountMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountMsNearEnd::Update(MON_MsCounters& theCounter) 
{
    uint32 count = 0;

    theCounter.GetErrorCount(CT_TEL_MS_B2, &count);
    myBIPCounter.Update(count);
}

//-----------------------------------------------------------------
ostream& PM_BbCountMsNearEnd::WriteObject( ostream& theStream )
{
    return theStream << myBIPCounter;

}

//-----------------------------------------------------------------
istream& PM_BbCountMsNearEnd::ReadObject( istream& theStream )
{
    return theStream >> myBIPCounter;

}

//-----------------------------------------------------------------
void PM_BbCountMsNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
