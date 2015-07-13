/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Common
 AUTHOR      : Eric Bernier, 2003/2/4
 DESCRIPTION : Common class for tspii objects updates.
--------------------------------------------------------------------------*/
#ifndef TSPII_UpdateAction_H
#define TSPII_UpdateAction_H

#include "ExecutionSupport/FC_Action.h"
#include "ExecutionSupport/FC_Milliseconds.h"

#define TSPII_MAX_REGION_UPDATE 100

const FC_Milliseconds TSPII_UPDATE_PERIOD = 200; // milliseconds

class TSPII_BaseRegion;
class FC_PeriodicProcess;

class TSPII_UpdateAction : public FC_Action
{
public:
    /* CONSTRUCTOR */   TSPII_UpdateAction(const char* theName = "Unnamed");
    virtual             ~TSPII_UpdateAction();
    virtual void        Run(FC_Object* theObject = NULL );
    void                RegisterRegion(TSPII_BaseRegion * theRegion);
    void                UnregisterAllRegions();

    void                SetPeriod(FC_Milliseconds thePeriod);
    FC_Milliseconds     GetPeriod();
    void                WakeUp();
    void                Suspend();
    void                Display();

    virtual const char* GetInstanceName(void) const;

private:
    TSPII_BaseRegion *      myRegionArray[TSPII_MAX_REGION_UPDATE];
    unsigned int            myArrayUse;
    FC_PeriodicProcess *    myProcess;
    FC_Milliseconds         myPeriod;
    char                    myName[24]; // name of instance of object (type)
};

#endif // TSPII_UpdateAction_H
