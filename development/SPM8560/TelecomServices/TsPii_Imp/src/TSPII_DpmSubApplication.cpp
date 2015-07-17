/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     TSPII
 TARGET   :     DPM
 AUTHOR   :     Anoop Mathew
 DESCRIPTION:   TSPII Sub-application on DPM
--------------------------------------------------------------------------*/
#ifdef WIN32
    #pragma warning( disable : 4786 )
#endif

#include "TsPii_Imp/TSPII_DpmSubApplication.h"
#include "T6100_CardIf.h"
#include "T6100_ShelfIf.h"
#include "T6100_SlotIf.h"
#include "T6100_MainAppIf.h"
#include "T6100_ControllerStatusRegion.h"
#include "Blackboard/FC_Blackboard.h"
#include "CsPii/CSPII_CardIF.h"
#include "CsPii/CSPII_SysCfgParamIF.h"
#include "TsPii/TSPII_UpdateAction.h"
#include "TsPii_Imp/TSPII_DpmTestMenu.h"
#include "TsPii_Imp/TSPII_CntrlDrtrHwDrvIf.h"
#include "TsPii_Imp/TSPII_CntrlDdltHwDrvIf.h"
#include "TsPii_Imp/TSPII_DpmHwRefreshAction.h"
#include "Devices/DEV_BackplaneIfFpgaDrv.h"


#define OSC_UPDATE_ACTION_INDEX 0

///////////////////////////////////////////////////////////////////////////////
TSPII_DpmSubApplication::TSPII_DpmSubApplication(T6100_ShelfIf & theShelfContext, T6100_CardIf & theCardContext) :
    TSPII_SubApplication(),
    myRefreshAction(NULL),
    myTestMenu(NULL),
    myCardContext(theCardContext),
	myShelfContext(theShelfContext),
    mySlot(theCardContext.GetCardId())
{
}
    
///////////////////////////////////////////////////////////////////////////////
TSPII_DpmSubApplication::~TSPII_DpmSubApplication()
{
}
  
///////////////////////////////////////////////////////////////////////////////
TSPII_DpmSubApplication & TSPII_DpmSubApplication::GetSpecificInstance()
{
    return *(static_cast<TSPII_DpmSubApplication *>(TSPII_SubApplication::myInstance));
}
  
///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoCreateRegions(FC_Object* theObject)
{

    // Update Action creation for OSC facilities
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX] = new TSPII_UpdateAction();

    // Create Drtr Regions
    myDrtr = new TSPII_DrtrRegion("TSPII_DRTR");

    // Create Ddlt Regions
    myDdlt = new TSPII_DdltRegion("TSPII_DDLT");


#if defined(__TARGET__) 
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController())
    {
		myDrtr->AddAt(0, new TSPII_CntrlDrtrHwDrvIf());     // 
        myDdlt->AddAt(0, &(TSPII_CntrlDdltHwDrvIf::GetInstance()));    
    }
    else
    {
        // Create dummy simulation objects on standby controller
        myDrtr->AddAt(0, new TSPII_DrtrIf(false));     // 
        myDdlt->AddAt(0, new TSPII_DdltIf(false));     // 
    }
#else
    // SIMULATION
    
    myDrtr->AddAt(0, new TSPII_CntrlDrtrHwDrvIf());     // 
    myDdlt->AddAt(0, &(TSPII_CntrlDdltHwDrvIf::GetInstance()));     // 
#endif

    myCardContext.GetBb().Register(*myDrtr);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myDrtr);

    myCardContext.GetBb().Register(*myDdlt);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myDdlt);

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoInitCold(FC_Object* theObject)
{
    TSPII_SubApplication::DoInitCold(theObject); // Invoke base class which calls InitCommon
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoInitWarm(FC_Object* theObject)
{
    TSPII_SubApplication::DoInitWarm(theObject);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::InitCommon(restart_type theRestartType)
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoCreateActions(FC_Object* theObject)
{
	bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();
    myTestMenu      = new TSPII_DpmTestMenu();
    myRefreshAction = new TSPII_DpmHwRefreshAction();

	//on active controller init the BPFPGA drivers and
	//Lxame upgrade switch control actions
	if (isActiveController)
	{
	    DEV_BackplaneIfFpgaDrv::GetInstance().Init();
	}
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoActivateActions(FC_Object* theObject)
{
	bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();

	myRefreshAction->GetProcess().WakeUp();

	//TSPII has nothing to do on the standby SPM with regards to the OSC channels. 
	//Hence do not wake up 
	//the update actions on the standby controller
	if (isActiveController)
	{
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->WakeUp();
	}
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoDeactivateActions(FC_Object* theObject)
{
	bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();
    myRefreshAction->GetProcess().SuspendImmediate();
	
	if (isActiveController)
	{    
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->Suspend();
	}
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoDeleteActions(FC_Object* theObject)
{
    delete myRefreshAction; myRefreshAction = NULL;
    delete myTestMenu;      myTestMenu = NULL;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DpmSubApplication::DoDeleteRegions(FC_Object* theObject)
{
    delete myDrtr;
    delete myDdlt;

    delete myUpdateActionArray[OSC_UPDATE_ACTION_INDEX];
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DrtrRegion * TSPII_DpmSubApplication::GetDrtr(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE) && (theUnit == TSPII_DONT_CARE)) return myDrtr;
    return TSPII_SubApplication::GetDrtr(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DdltRegion * TSPII_DpmSubApplication::GetDdlt(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE) && (theUnit == TSPII_DONT_CARE)) return myDdlt;
    return TSPII_SubApplication::GetDdlt(theUnit, theSlot);
}



///////////////////////////////////////////////////////////////////////////////
bool TSPII_DpmSubApplication::Override(int argc, char** argv, uint32 theSlot)
{
    return true;
}

