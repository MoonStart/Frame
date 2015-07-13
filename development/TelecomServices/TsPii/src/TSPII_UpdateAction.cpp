/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Common
 AUTHOR      : Eric Bernier, 2003/2/4
 DESCRIPTION : Common class for tspii objects updates.
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_UpdateAction.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_Region.h"
#include "T6100_Dispatcher.h"
#include "ExecutionSupport/FC_PeriodicProcess.h"
#include <string.h>


TSPII_UpdateAction::TSPII_UpdateAction(const char* theName):
    myArrayUse(0),
    myPeriod(TSPII_UPDATE_PERIOD)
{
    for (int i=0; i<TSPII_MAX_REGION_UPDATE; i++)
        myRegionArray[i] = NULL;
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, myPeriod);
    strcpy(myName, theName);
}

TSPII_UpdateAction::~TSPII_UpdateAction()
{
    delete myProcess;
}

void TSPII_UpdateAction::Run(FC_Object* theObject)
{
    unsigned int i, k;
    for (i=0; i<myArrayUse; i++)
    {
        if (myRegionArray[i] != NULL)
        {
            for (k=0; k < myRegionArray[i]->Size(); k++)
            {
                (*myRegionArray[i])[k].UpdateValues();
            }
            myRegionArray[i]->IncModificationCounter();
            myRegionArray[i]->UpdateNotify();
        }
    }
}

void TSPII_UpdateAction::RegisterRegion(TSPII_BaseRegion* theRegion)
{
    if (myArrayUse < TSPII_MAX_REGION_UPDATE)
    {
        myRegionArray[myArrayUse] = theRegion;
        myArrayUse++;
    }
    else
        fc_cout << " Last position of TSPII update action array has been used " << endl;
}

void TSPII_UpdateAction::UnregisterAllRegions()
{
    for (int i=0; i<TSPII_MAX_REGION_UPDATE; i++)
    {
        myRegionArray[i] = NULL;
    }
    myArrayUse=0;
}

void TSPII_UpdateAction::SetPeriod(FC_Milliseconds thePeriod)
{
    myProcess->SuspendImmediate();
    myProcess->SetDelay(thePeriod);
    myProcess->WakeUp();
    myPeriod = thePeriod;
}

FC_Milliseconds TSPII_UpdateAction::GetPeriod()
{
    return myPeriod;
}

void TSPII_UpdateAction::WakeUp()
{
    myProcess->WakeUp();
}

void TSPII_UpdateAction::Suspend()
{
    myProcess->SuspendImmediate();
}

void TSPII_UpdateAction::Display()
{
    fc_cout << "  Update Action Config \n" 
            << "      Period                =       " << myPeriod << "\n"
            << "      Nb Regions to Update  =       " << myArrayUse << endl;

}

const char* TSPII_UpdateAction::GetInstanceName(void) const
{
    return myName;
}
