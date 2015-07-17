/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : BSP
 TARGET      : DPM
 AUTHOR      : Anoop Mathew
 DESCRIPTION : This file contains the packet subsystem initialization routine
               that should be run after root is initialized
--------------------------------------------------------------------------*/
#include <locale.h>
#include "api_retcodes.h"
#include "RPR_dpm_init.h"
#include "UTIL_mac_pool.h"
extern VOID  MsrIssDeleteIssUpgrFile (VOID);

/*
Function that is called to initialize the packet subsystem. Control point
for launching all packet applications
Inputs: shelfNum    : Shelf the dpm is running on
        SlotNum     : Slot the dpm is running on
        active      : 1 =active controller, 0 =inactive controller
        matePresent : 
        syncToMate  : true = sync config data to mate, false = do not sync.
**/

int StartPssControlPlane(int active, int matePresent, int syncToMate);

extern int IssInitTask(int active, int matePresent, int syncToMate);
extern void UTIL_ModuleFaultInit(void);
extern API_RETCODE UtilTimestampFunctionsInit(void);

void InitPacketSubsystem(int shelfNum, int slotNum, int active, int matePresent, int syncToMate,
                         char *serialNum, UINT8_64BIT macAddr64)
{
    /* whenever packet starts make sure any upgrade DB files are removed */
    /* if this DPM is standby it will get them back but iss.upgr and issnvram.upgr */
    /* should not be persistent on the active */
    MsrIssDeleteIssUpgrFile();
    /*
     * Init fault reporting services
     */
    UTIL_ModuleFaultInit();
        
    /* Initialize shelf pool of MAC addresses */
    if (UTIL_macPoolInit(serialNum, macAddr64) != API_RETCODE_SUCCESS)
    {
        printf("InitPacketSubsystem: MAC Pool initialization FAILED...\n");
        /* Probably want to exit here with a fatal error - <TODO - grj> */
    }

    //Start PSS Control Plane
    StartPssControlPlane(active, matePresent, syncToMate);
     
    /* Initialize timestamp functions */
    UtilTimestampFunctionsInit();
}

int StartPssControlPlane(int active, int matePresent, int syncToMate)
{
    if(IssInitTask(active, matePresent, syncToMate) != 0)
        printf("StartPssControlPlane: ISS Startup FAILED...\n");

    return(0);
}

