/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     FGSM SSM40
 AUTHOR   :     May 5, 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the protection switching statistics of 
                Near-End SONET/SDH MS layer
 --------------------------------------------------------------------------*/

#include <SignalProtection/SP_SwitchingStatistic.h>
#include <PM_BbStatusOdu.h>
#include <BaseClass/FC_TextStream.h>

//-----------------------------------------------------------------
PM_BbStatusOdu::PM_BbStatusOdu ()  :
     myLastRevertiveMode(false),
     myCurrentRevertiveMode(false),
     myLastProtectionShemePrsenceStatus(false),
     myCurrentProtectionShemePrsenceStatus(false),
     myProtectionActiveDuration(0),

	 // Set the limits on the PSC and PSD counters
	 // to be the upper limit of the 1 day values,
	 // since they are larger than the 15 minute values.
	 myPSCCounter(86400),
	 myPSDCounter(86400)
{
}

//-----------------------------------------------------------------
PM_BbStatusOdu::~PM_BbStatusOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbStatusOdu::Update(SP_SwitchingStatistic* theSpStat) 
{
    myLastProtectionShemePrsenceStatus = myCurrentProtectionShemePrsenceStatus;
    if (theSpStat == (SP_SwitchingStatistic *) 0) 
    {
        myCurrentProtectionShemePrsenceStatus = false;
    }
    else
    {
        myCurrentProtectionShemePrsenceStatus = theSpStat->IsInvolvedInProtection();
    }
    
    if (myCurrentProtectionShemePrsenceStatus) 
    {
        if (theSpStat->IsProtecting()) 
        {
            // Protect facility

            //UPdate PSC
            myPSCCounter.Update(theSpStat->GetPSCspan());
            // Update PSD
            if (theSpStat->IsCurrentlyActive() && theSpStat->IsRevertive())
            {
                myProtectionActiveDuration++;
            }
            myPSDCounter.Update(myProtectionActiveDuration);
        }
        else
        {
            // Working facility
            myPSCCounter.Update(theSpStat->GetPSCwork());
            // Update PSD
            if ((!(theSpStat->IsCurrentlyActive())) && theSpStat->IsRevertive())
            {
                myProtectionActiveDuration++;
            }
            myPSDCounter.Update(myProtectionActiveDuration);
        }

        // Update change in revertive mode status
        myLastRevertiveMode = myCurrentRevertiveMode;
        myCurrentRevertiveMode = theSpStat->IsRevertive();
    }
    else
    {
        myLastRevertiveMode = false;
        myCurrentRevertiveMode = false;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbStatusOdu::WriteObject( ostream& theStream )
{
    return theStream << myPSCCounter
                     << myPSDCounter
                     << FC_InsertVar(myLastRevertiveMode)
                     << FC_InsertVar(myCurrentRevertiveMode)
                     << FC_InsertVar(myLastProtectionShemePrsenceStatus)
                     << FC_InsertVar(myCurrentProtectionShemePrsenceStatus);
}

//-----------------------------------------------------------------
istream& PM_BbStatusOdu::ReadObject( istream& theStream )
{
    return theStream >> myPSCCounter
                     >> myPSDCounter
                     >> FC_ExtractVar(myLastRevertiveMode)
                     >> FC_ExtractVar(myCurrentRevertiveMode)
                     >> FC_ExtractVar(myLastProtectionShemePrsenceStatus)
                     >> FC_ExtractVar(myCurrentProtectionShemePrsenceStatus);
}

//-----------------------------------------------------------------
void PM_BbStatusOdu::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
