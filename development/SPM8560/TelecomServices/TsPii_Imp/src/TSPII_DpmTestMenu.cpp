/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TSPII
TARGET:         DPM
AUTHOR:         Anoop Mathew
DESCRIPTION:    Test menu class for TSPII on DPM
-----------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_DpmTestMenu.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii_Imp/TSPII_DpmSubApplication.h"
#include "TsPii_Imp/TSPII_DpmHwRefreshAction.h"
#include "TsPii_Imp/TSPII_CntrlDrtrHwDrvIf.h"
#include "TsPii_Imp/TSPII_CntrlDdltHwDrvIf.h"
#include "T6100_MainAppIf.h"
#include "T6100_ControllerStatusRegion.h"
#include "Devices/CardFirmwareStatus.h"


#define CMD     "tspii"
#define HELP    "tspii - control and monitor low level telecom H/W drivers"
#define HWLP    "hw - control and monitor telecom hardware"


const FC_CmdProcessor::CMD_TABLE_STRUCT TSPII_DpmTestMenu::ourTspiiDpmMainMenu[]=
{
    {CMD,  "displayDrtr",   HELP, "displayDrtr  - dump DCC router/TARP cache data",         TspiiDrtrDisplay},
    {NULL, "displayDdlt",   NULL, "displayDdlt  - dump DCC linkage cache data",             TspiiDdltDisplay},

    {"hw", "dump",          HWLP, "dump       - dump different hw values",                  HwDump},
    {NULL, "vers",          NULL, "vers       - display versions of devices on card",       HwVers},
    {NULL, "refresh",       NULL, "refresh    - controls periodic refresh of HW",           HwRefresh}
};

///////////////////////////////////////////////////////////////////////////////
TSPII_DpmTestMenu::TSPII_DpmTestMenu()
{
    FC_CmdProcessor& cmdProcessor = *FC_CmdProcessor::GetShellInstance();
    cmdProcessor.FC_RegisterCommand(ourTspiiDpmMainMenu, sizeof(ourTspiiDpmMainMenu)/sizeof(ourTspiiDpmMainMenu[0]));
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DpmTestMenu::~TSPII_DpmTestMenu()
{
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_DpmTestMenu::HwRefresh(int argc, char** argv)
{
    TSPII_DpmSubApplication & app = TSPII_DpmSubApplication::GetSpecificInstance();
    if (argc == 3 && strcmp(argv[2], "on") == 0)
    {
        app.myRefreshAction->GetProcess().WakeUp();
    }
    else if (argc == 3 && strcmp(argv[2], "off") == 0)
    {
        app.myRefreshAction->GetProcess().SuspendImmediate();
    }
    else
    {
        fc_cout << "Usage: hw refresh [on|off]" << endl;
    }
    fc_cout << "Refresh is " << TEXT_ON_OFF(app.myRefreshAction->GetProcess().IsWakeUp()) << endl;
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_DpmTestMenu::HwDump(int argc, char** argv)
{
   return FC_CmdProcessor::E_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_DpmTestMenu::HwVers(int argc, char ** argv)
{
    Devices::CardFirmwareStatus::GetInstance()->HwVersions (argc-2, argv+2);
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_DpmTestMenu::TspiiDrtrDisplay(int argc, char** argv)
{

	bool printUsage = false;
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

	if (argc==3)
    {
		uint32 routerIndex = strtoul(argv[2], NULL, 0);
		if (routerIndex < 1 || routerIndex>15)
		{
			printUsage = true;
		}
		else
		{
			TSPII_CntrlDrtrHwDrvIf* theDrtrInstance = dynamic_cast <TSPII_CntrlDrtrHwDrvIf*> (&( (*(TSPII_DpmSubApplication::GetSpecificInstance().GetDrtr()) )[(bbindex_t)routerIndex-1]));
			if (theDrtrInstance)
                theDrtrInstance->DisplayDccRouterData();
		}
	}
	else
	{
		printUsage = true;
	}

	if (printUsage)
	{
		fc_cout << " tspii displayDrtr [routerIndex: 1-15] \n" << endl;
	}
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_DpmTestMenu::TspiiDdltDisplay(int argc, char** argv)
{
	bool printUsage = false;

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

	if (argc==6)
    {
		bool isSection;
		uint32 aShelf = GET_INTERNAL_SHELF_ID(strtoul(argv[2], NULL, 0));
		uint32 aSlot =  strtoul(argv[3], NULL, 0);
		uint32 aPort =  strtoul(argv[4], NULL, 0);
		if (argv[5][0] == 'l' || argv[5][0] == 'L')
		{
			isSection = false;
		}
		else if (argv[5][0] == 's' || argv[5][0] == 'S')
		{
			isSection = true;
		}
		else
		{
			fc_cout << "Invalid type" << endl;
			printUsage = true;
			isSection = false;
		}

		if (aShelf == UNKNOWN_SHELF_ID ||
			aSlot  == UNKNOWN_SLOT_ID ||
			aPort  == UNKNOWN_PORT_ID)
		{
			fc_cout << "Invalid shelf/slot/port" << endl;
			printUsage = true;
		}

		if (!printUsage)
		{
		    TSPII_CntrlDdltHwDrvIf::GetInstance().DisplayLapdLinkageData((CT_ShelfId)aShelf, (CT_SlotId)aSlot, (CT_PortId)aPort, isSection);
		}
	}
	else
	{
		printUsage = true;
	}

	if (printUsage)
	{
		fc_cout << " tspii displayDdlt [shelf] [slot] [port] [(s)ection/(l)ine] \n" << endl;
	}
	
    return FC_CmdProcessor::E_SUCCESS;
}

