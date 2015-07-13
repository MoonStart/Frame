/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 1999 Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of Near-End SONET/SDH HOP layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_HopCounters.h>
#include <PM_BbCountHopNearEnd.h>


//-----------------------------------------------------------------
PM_BbCountHopNearEnd::PM_BbCountHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbCountHopNearEnd::~PM_BbCountHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountHopNearEnd::Update(MON_HopCounters& theCounter) 
{
    uint32 count = 0;

    theCounter.GetErrorCount(CT_TEL_HOP_B3, &count);
    myBIPCounter.Update(count);

	theCounter.GetErrorCount(CT_TEL_HOP_PPJ_DET, &count);
    myPPJCDETCounter.Update(count);

	theCounter.GetErrorCount(CT_TEL_HOP_NPJ_DET, &count);
    myNPJCDETCounter.Update(count);

	theCounter.GetErrorCount(CT_TEL_HOP_PPJ_GEN, &count);
	myPPJCGENCounter.Update(count);

	theCounter.GetErrorCount(CT_TEL_HOP_NPJ_GEN, &count);
	myNPJCGENCounter.Update(count);

}

//-----------------------------------------------------------------
ostream& PM_BbCountHopNearEnd::WriteObject( ostream& theStream )
{
    return (theStream << myBIPCounter
					  << myPPJCDETCounter
					  << myNPJCDETCounter
					  << myPPJCGENCounter
					  << myNPJCGENCounter);
		

}

//-----------------------------------------------------------------
istream& PM_BbCountHopNearEnd::ReadObject( istream& theStream )
{
    return (theStream >> myBIPCounter
					  >> myPPJCDETCounter
					  >> myNPJCDETCounter
					  >> myPPJCGENCounter
					  >> myNPJCGENCounter);

}

//-----------------------------------------------------------------
void PM_BbCountHopNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
