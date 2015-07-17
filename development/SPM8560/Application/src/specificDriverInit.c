/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : BSP
 TARGET      : PCSM
 AUTHOR      : G. Desilets
 DESCRIPTION : This file contains the driver initialization routine
               that should be run before the application is started,
               but also after the root task is invoked
--------------------------------------------------------------------------*/

/* vxWork includes */
#include <vxWorks.h>
#include <stdio.h>
#include <shellInterpCmdLib.h>
#include <private/shellInternalLibP.h>
#include <taskLibCommon.h>
#include <telnetLib.h>
#include <sysLib.h>
#include <edrLib.h>
#include "shlLib.h"
#include "ioLib.h"
#include "time.h"

/*  7100 includes */
#include "specificDriverInit.h"
//#include <phile.h>
#include "gdef.h"
#include "inf_api.h"

#include "config.h"
#include "pcf8563.h"
#include "optionDefines.h"
#include "mcuBootDiag.h"
#include "IdProm/CardIdProm.h"
#include "sysvars.h"
#include "restart.h"

#pragma use_section DATA  gCardtype_SPM, gCardtype_DPM;

//extern void diskonchipVolInit();
//extern int McuDiagSocketLoopbacks();
extern int CSPII_Spm8560Layer2Switch_Init();
extern bool gCardtype_SPM;
extern bool gCardtype_DPM;
static void checkForImproperShelfId();
extern void bcm2_cli1(void); /*MR-122454*/

#ifndef HWTF

extern STATUS commonShellCmdInit (void);

/* Forward declarations */
static int  StartBCMShell (int argc,char **  argv);/*122454*/

const uint32 DEV_CTRL_BACKPLANE_IF_FPGA_DRV_ADDRESS = 0xfdfe0000;


#define OUTBUF_SIZE 600

/***************NOTE********NOTE*****NOTE****************************/
/* ONLY COMMANDS THAT ARE SPECIFIC TO SPM8560 SHOULD BE ADDED TO THE TABLES */
/* BELOW. ANY COMMANDS THAT ARE COMMON TO ALL CONTROLLER PLATFORMS SHOULD */
/* BE ADDED TO: development/CommonPlatforms/CardServices/BspCommon/vx7100Cmds.c */
/*****************************************************************************/
/*---------------------------------------------------------------------*/
/* Table of command extensions to the shell - these execute as part of */
/* the shell task.
    Command format
    nameStruct = {"cmdFullname",
    func,
    "opt",
    "shortDesc",
    "fullDesc",
    "%s [synopsis]"}; */
/*---------------------------------------------------------------------*/
static const SHELL_CMD specific_cmds_tab[] =
{
    { "BCMShell",/*122454*/
      StartBCMShell,
      NULL,
      "BCM Shell",
      "BCMShell - Access the BCM shell interface",
      ""},

    { NULL,        NULL,        NULL,           NULL,   NULL, NULL }
};

static const SHELL_CMD_ALIAS    specific_cmds_tab_Alias[] = {
    {"bcmshell", "BCMShell"},
    {NULL, NULL}};

/*******************************************************************************
*
* specificShellCmdInit - initialize the shell commands
*
* This function is used to initialize the shell commands custom to SPM8560 platform. It 
* adds new commands to the list of available commands.
*
* RETURNS: OK, or ERROR if an error occured.
*
* ERRNO
* malloc() errnos
*/

STATUS specificShellCmdInit (void)
    {
    STATUS  status;

    /* Create a new topic for the commands */

    status = shellCmdTopicAdd ("Spm8560Commands",
                   "Command specific to SPM8560 platform.");
    if (status != OK)
    return ERROR;

    /* Register the commands */

    status = shellCmdArrayAdd ("Spm8560Commands", specific_cmds_tab);
    if (status != OK)
    return ERROR;

    /* Add default aliases */

    shellCmdAliasArrayAdd (specific_cmds_tab_Alias, FALSE);

    return OK;
    }

#endif // ndef HWTF

void InitSpecificDrivers(void)
{
    int rc, i;
    int   dectime[7] = {  0, 0, 0, 0, 0, 0, 0 };
    UCHAR bcdtime[7] = {  0, 0, 0, 0, 0, 0, 0 };
    struct tm  rtc;
    time_t num_seconds;
    struct timespec sys_time;
    char outbuf[OUTBUF_SIZE];

#ifndef HWTF
    int retVal;
#endif
    CardIdProm_PartNumber_t aPartNum;

    checkForImproperShelfId();

//    McuDiagReport_t* report = getMcuDiagReportPtr();

    printf("-Getting RTC Date and Time - Setting OS clock\n");

    // If RTC time is valid, get time from RTC and set system time
    if (Pcf8563IsTimeValid() == PCF8563_DRV_OK)
    {
    /*Get RTC Time*/
    Pcf8563GetTime(PCF8563_ADD, bcdtime);
    bcd2dec(bcdtime, dectime);
    }
    else
    {
        // -RTC was not initialized - Setting default date and time
        dectime[3] = 1;
        dectime[5] = 1;
        dectime[6] = 2006;
        dectime[2] = 0;
        dectime[1] = 0;
        dectime[0] = 0;

        /*Initialize the RTC so it's done once and for all. */
        dec2bcd(dectime, bcdtime);
        Pcf8563SetTime(PCF8563_ADD, bcdtime);
    }

    // Put time and date into tm structure format
    rtc.tm_sec = dectime[0];                // seconds
    rtc.tm_min = dectime[1];                // minutes
    rtc.tm_hour = dectime[2];               // hours
    rtc.tm_mon = (dectime[5] - 1);          // month
    rtc.tm_mday = dectime[3];               // day
    rtc.tm_year = ((dectime[6]%100) + 100); // year

    num_seconds = mktime(&rtc); // set all fields in tm structure  
    // Convert calender time to broken down time
    rc = localtime_r (&num_seconds, &rtc);
    if (rc != 0 )  
    {
        printf("\nError converting calender time to broken down time");
        return;
    }

    sys_time.tv_sec = num_seconds;
    sys_time.tv_nsec = 0;
    
    /* Set VXWRKS Clock */
    rc = clock_settime(CLOCK_REALTIME, &sys_time);    

    /* Output time that was set on OS clock */
    printf("\nUTC Date set (DD:MM:YY) : %.2d-%.2d-%.2d  UTC Time set (HH:MM:SS) : %.2d:%.2d:%.2d\n", dectime[3], dectime[5], dectime[6], dectime[2], dectime[1], dectime[0]);

    // Now that we have a valid timestamp, add an edr message with reset info
    CreateRestartLogReport(outbuf, OUTBUF_SIZE);
    EDR_USER_INFO_INJECT(0, outbuf);

    // INCLUDE_PCI shall be included in the config.h
    //InitSwitchDriver();

    printf("\n-Testing GBP memory of switch\n");
    rc= SwitchGbpTest();
    //report->specific.Spm8560.switchRamTest= rc;
    if (rc)
    {
        printf("######## GBP mem test FAILED ##########\n");
    }

    printf("-Running BIST on all memories of switch\n");
    rc= SwitchBistAll();
    //taskDelay(200 * sysClkRateGet()); /* Wait for a while before initializing the switch */
    taskDelay(200); /* Wait for a while before initializing the switch */
    //report->specific.Spm8560.switchBist= rc;
    if (rc)
    {
        printf("######## BIST FAILED ##########\n");
    }

    printf("-Basic Setup of switch\n");
    SwitchBasicSetup();

    CSPII_Spm8560Layer2Switch_Init();

    /* Call loopback test in mcuDiagSpecific */
    //printf("-Loopback tests\n");
    //rc= McuDiagSocketLoopbacks();


#ifndef HWTF
    /* Enable echo and canonical input */
    if ( CSPII_SetEchoAndCanon( true, true ) )
    {
        printf(" ### Can not set console mode\n");
    }

    //initializer custom commands
	commonShellCmdInit();
    specificShellCmdInit();

#else
    /* Disable canonical mode - for HWTF */
    SetEchoAndCanon(0, 0);
#endif // ndef HWTF
}

int SetEchoAndCanon(int theEcho, int theCanon)
{
    //OPT_ECHO = echo characters
    //OPT_LINE = non-canonical
    int rc;
    int     consoleFd;
    int options = 0;
    char        consoleName[20];
    char tyName [20];
    sprintf (tyName, "%s%d", "/tyCo/", 0);
    strcpy (consoleName, tyName);
    consoleFd = open (consoleName, O_RDWR, 0);
    options = ioctl (consoleFd, FIOGETOPTIONS, 0);
    options &= ~(OPT_LINE | OPT_ECHO );
    options |= ( (theEcho ? OPT_ECHO:0) | (theCanon ? OPT_LINE:0) );
    rc = ioctl (consoleFd, FIOSETOPTIONS, options);
    if (rc)
    {
        return rc;
    }

    return 0;

}


//------------------------------------------------------------------------------
typedef struct { uint8 numChars;  char ch; } charSequence;
static void printCharSequence( const charSequence *seq )
{
    int i;
    while(seq->numChars)
    {
        for (i=0; i<seq->numChars; i++)
            putchar(seq->ch);
        seq++;
    }
}

static void checkForImproperShelfId()
{
  // The only valid shelf IDs for an SPM are shelf IDs 1 and 15.
  // The only valid shelf IDs for a DPM are anything OTHER than 1 and 15.

  int sid = GetBpShelfId();
  if ((gCardtype_SPM && ((sid != OPTICAL_SHELF) && (sid != OPTICAL_SHELF2))) ||
      (gCardtype_DPM && ((sid == OPTICAL_SHELF) || (sid == OPTICAL_SHELF2))) ||
      (!gCardtype_SPM && !gCardtype_DPM))
  {
    const charSequence topHalf[] =
    {
        5, '\n', 75, '-', 1, '\n',
        1, ' ', 2, '\\', 20, ' ', 2, '\\', 25, ' ', 2, '/', 20, ' ', 2, '/', 1, '\n',
        2, ' ', 2, '\\', 20, ' ', 2, '\\', 23, ' ', 2, '/', 20, ' ', 2, '/', 1, '\n',
        3, ' ', 2, '\\', 20, ' ', 2, '\\', 21, ' ', 2, '/', 20, ' ', 2, '/', 1, '\n',
        4, ' ', 2, '\\', 20, ' ', 2, '\\', 19, ' ', 2, '/', 20, ' ', 2, '/', 1, '\n',
        5, ' ', 2, '\\', 20, ' ', 2, '\\', 17, ' ', 2, '/', 20, ' ', 2, '/', 1, '\n',
        0, 0  // Indicate end of sequence
    };
    const charSequence bottomHalf[] =
    {
        5, ' ', 2, '/', 20, ' ', 2, '/', 17, ' ', 2, '\\', 20, ' ', 2, '\\', 1, '\n',
        4, ' ', 2, '/', 20, ' ', 2, '/', 19, ' ', 2, '\\', 20, ' ', 2, '\\', 1, '\n',
        3, ' ', 2, '/', 20, ' ', 2, '/', 21, ' ', 2, '\\', 20, ' ', 2, '\\', 1, '\n',
        2, ' ', 2, '/', 20, ' ', 2, '/', 23, ' ', 2, '\\', 20, ' ', 2, '\\', 1, '\n',
        1, ' ', 2, '/', 20, ' ', 2, '/', 25, ' ', 2, '\\', 20, ' ', 2, '\\', 1, '\n',
        75, '-', 3, '\n',
        0, 0  // Indicate end of sequence
    };

    printCharSequence( topHalf );
    if (gCardtype_SPM)
    {
      printf(" WARNING: This SPM is in a shelf whose rotary switch is set to shelf ID %d.\n"
             "   The only valid shelf IDs for an SPM are 1 and 15.  Due to this error,\n"
             "   the software will likely crash during or shortly after initialization.\n",
             sid);
    }
    else if (gCardtype_DPM)
    {
      printf(" WARNING: This DPM is in a shelf whose rotary switch is set to shelf ID %d.\n"
             "   The only valid shelf IDs for a DPM are 2...14.  Due to this error,\n"
             "   the software will likely crash during or shortly after initialization.\n",
             sid);
    }
    else
    {
      printf(" WARNING: Card type in EEPROM is not programmed for SPM or DPM!\n");
    }

    printCharSequence( bottomHalf );
  }
}

static int StartBCMShell/*122454*/
    (
    int       argc,       /* number of argument */
    char **   argv        /* pointer on the array of arguments */
    )
{
    bcm2_cli1();
    return OK;
}

