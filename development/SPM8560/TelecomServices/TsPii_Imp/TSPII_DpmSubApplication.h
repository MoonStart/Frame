/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     TSPII
 TARGET   :     DPM
 AUTHOR   :     Anoop Mathew
 DESCRIPTION:   TSPII Sub-application for DPM
--------------------------------------------------------------------------*/

#ifndef TSPII_DPMSUBAPPLICATION_H
#define TSPII_DPMSUBAPPLICATION_H

#include "CommonTypes/CT_SystemIds.h"
#include "TsPii/TSPII_SubApplication.h"

class T6100_ShelfIf;
class T6100_CardIf;
class TSPII_DpmTestMenu;
class TSPII_DpmHwRefreshAction;



class TSPII_DpmSubApplication : public TSPII_SubApplication
{
    friend class TSPII_DpmTestMenu;


public:

    /* From base class */
    /* CTOR */                           TSPII_DpmSubApplication(T6100_ShelfIf & theShelfContext, T6100_CardIf & theCardContext);
    virtual                              ~TSPII_DpmSubApplication();
    virtual void                         DoCreateRegions(FC_Object* theObject);
    virtual void                         DoInitCold(FC_Object* theObject);
    virtual void                         DoInitWarm(FC_Object* theObject);
    virtual void                         InitCommon(restart_type theRestartType);
    virtual void                         DoCreateActions(FC_Object* theObject);
    virtual void                         DoActivateActions(FC_Object* theObject);
    virtual void                         DoDeactivateActions(FC_Object* theObject);
    virtual void                         DoDeleteActions(FC_Object* theObject);
    virtual void                         DoDeleteRegions(FC_Object* theObject);

 
    virtual TSPII_DrtrRegion *           GetDrtr      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DdltRegion *           GetDdlt      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);

	virtual bool                         Override(int argc, char** argv, uint32 theSlot = 0);


	// Interface with CSM for dumb card management.
    // None for now


    static TSPII_DpmSubApplication & GetSpecificInstance();

private:

    // Regions
    TSPII_DrtrRegion *             myDrtr;
    TSPII_DdltRegion *             myDdlt;

    // Contexts
    TSPII_DpmHwRefreshAction *     myRefreshAction;
    TSPII_DpmTestMenu *            myTestMenu;
    T6100_CardIf &                 myCardContext;
	T6100_ShelfIf &                myShelfContext;
    unsigned long                  mySlot;
};

#endif // TSPII_DPMSUBAPPLICATION_H
