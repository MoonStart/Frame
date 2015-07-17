/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

  SUBSYSTEM  : HWTF( HWTestFramework ) for the SPM
               MPC8560
  TARGET     : ALL
  AUTHOR     : Ken Carlson
  FUNCTION   : Test the JTAG interface

  NOTES      : Some of the functions are either copys of or similar to
               functions in the JTAG driver. Since the driver is written
               in C++ for the application it cannot be easily incorporated
               here. Look in /development/CommonPlatforms/CardServices/JTAG
               for the driver versions.

               Direction i.e. test data in (TDI) and test data out (TDO)
               are from the perspective of the unit under test (UUT).
--------------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stat.h"
#include "fcntl.h"
#include "pquicc3.h"
#include "jtagDiag.h"
#include "micro.h"
#include "ports.h"
#include "JTAG_Types.h"
#include "JTAG_BspWrapper.h"

#define JTAG_MIN_SLOT   1
#define JTAG_MAX_SLOT  19

#define TI_IDLE    (1)  // IDLE Bit value for putting TI 8996 command
#define TI_SELECT  (0)  // SELECT Bit value for putting TI 8996 command

// Globals
unsigned long gJtagSvfVerbose  = 0;
unsigned long gJtagTaskVerbose = 0;
unsigned long gJtagLoopMsDelay = 0;
extern volatile int gPII_TickCounter;
extern int xsvf_iDebugLevel;

// Forward references
void EnableBuffers(bool theEnablestate);
UINT32 GetShelfId(void);
UINT32 EncodeSlotId(bool theCardIsA1_3_1Amp, UINT32 theSlotId);
UINT32 ShadowProtocol(UINT32 theEncodedSlotId);
bool SendCmd(UINT32 theEncodedSlotId);
bool DisableJtag(void);
bool EnableJtag(bool theCardIsA1_3_1Amp, UINT32 theSlotId);
void JTAG_TaskWkAfter(long ticks);
void pulseClock(void);


///////////////////////////////////////////////////////////////////////////////
//
//  Purpose: From the command line, if the user wishes to see a description
//           of the Test, then this function will be invoked and will display
//           the purpose of the Test
//
///////////////////////////////////////////////////////////////////////////////

void jtagDiagDisplayUsage(void)
{
    printf("usage: jtagDiagTest slot, \"file\", dbgl\n");
    printf("       slot - Slot number of slave device (%d..%d). Set to 0 to display help.\n", JTAG_MIN_SLOT, JTAG_MAX_SLOT);
    printf("       file - [path]name of JTAG test file. Quotes are required.\n");
    printf("       dbgl - Debug level. 0=Error Msg Only 1=Verbose 5=Full\n");
}


///////////////////////////////////////////////////////////////////////////////
//
//  Purpose: Address a JTAG device and run the JTAG instructions.
//
///////////////////////////////////////////////////////////////////////////////

UINT32 jtagDiagTest(UINT32 slot, char *file, int dbgLevel)
{
    int i;
    int fd;  // The JTAG file descriptor number
    int numBytes;
    UINT32 rc;
    struct stat fileStat;
    unsigned char *jtagTestDataStream;

    if (slot == 0)
    {
        jtagDiagDisplayUsage();
        return(JTAG_DRV_SUCCESS);
    }

    xsvf_iDebugLevel = dbgLevel;
    gJtagSvfVerbose  = dbgLevel;
    gJtagTaskVerbose = dbgLevel;

    // Validate slot number
    if ((slot < JTAG_MIN_SLOT) || (slot > JTAG_MAX_SLOT))
    {
        printf("Slot number is out of range. (%d .. %d)\n", JTAG_MIN_SLOT, JTAG_MAX_SLOT);
        return(JTAG_DRV_SLOT_ERR);
    }

    // Open the file
    fd = open((const char *)file, O_RDONLY, 0777);
    if (fd == ERROR)
    {
        printf("JTAG file not found: %s.\n", file);
        return(JTAG_DRV_PSOS_ERR);
    }

    rc = JTAG_DRV_SUCCESS;

    // Get the number of bytes in the file
    if ((fstat(fd, &fileStat) == ERROR) || (fileStat.st_size == 0))
    {
        printf("JTAG file status error. Size: %d\n", fileStat.st_size);
        rc = JTAG_DRV_PSOS_ERR;
    }

    if (rc == JTAG_DRV_SUCCESS)
    {
        // Allocate a buffer to hold the contents of the file
        jtagTestDataStream = (unsigned char *) calloc(fileStat.st_size, sizeof(unsigned char) + 1);
        if (jtagTestDataStream != NULL)
        {
            // Copy the contents of the file to the array
            numBytes = read(fd, jtagTestDataStream, fileStat.st_size);
            if (numBytes != fileStat.st_size)
            {
                printf("JTAG file read failed.  Expected: %d  Actual: %d\n", fileStat.st_size, numBytes);
                rc = JTAG_DRV_PSOS_ERR;
            }
        }
        else  // calloc() failed
        {
            printf("JTAG calloc() failed.\n");
            rc = JTAG_DRV_PSOS_ERR;
        }
    }

    close(fd);

    if (rc != JTAG_DRV_SUCCESS)
        return(rc);

    if (dbgLevel > 0)
    {
        printf("JTAG file: %s.  Size: %d  Slot: %d  dbg: %d\n", file, fileStat.st_size, slot, dbgLevel);
        if (dbgLevel > 5)
        {
            for (i = 0; i < fileStat.st_size; i++)
            {
                if ((i % 16) == 0)
                    printf("\n");
                printf("%2x ", jtagTestDataStream[i]);
            }
            printf("\n");
        }
    }

    rc = EnableJtag(false, slot);
    if (rc == true)
    {
        setSvfData(jtagTestDataStream);  // Use SVF player
        rc = xsvfExecute();              // Play the data
        setSvfData(NULL);                // Clear the data array

        if (rc == XSVF_ERROR_NONE)
            rc = JTAG_DRV_SUCCESS;
        else
            rc = JTAG_DRV_SVF_ERR;
    }
    else
        rc = JTAG_DRV_XCV_ERR;

    DisableJtag();

    if (rc == JTAG_DRV_SUCCESS)
        printf("JTAG Test passed.\n");
    else
        printf("JTAG Test failed. Result: %d\n", rc);

    return(rc);
}


/*******************************************************************************/
/*******************************************************************************/
/***
/*** The following is a copy of a function that can be found in:
/*** /development/CommonPlatforms/CardServices/JTAG/JTAGDrv/src/JTAG_Task.cpp
/***
/*******************************************************************************/
/*******************************************************************************/

// ____________________________________________________________________________
//
// Method:     Jtag_TaskWkAfter()
//
// Purpose:    This is the implementation of the tm_wkafter that should be used
//             by the JTAG Task
//
// Arguments:  ticks : Number of PSOS or VXWORKS Ticks to suspend the task
//
// Returns:    none
//
// Notes:      none
// ____________________________________________________________________________

void JTAG_TaskWkAfter(long ticks)
{
    long start, end;

    if (gJtagTaskVerbose)
    {
        printf("JTAG-TASK: Suspending Task ... %d ms\n", (ticks * 10));
    }

    start = gPII_TickCounter;
    gJtagLoopMsDelay = 0;
    // Suspend the task
#if ! defined VXWRKS
    tm_wkafter(ticks);
#else
    taskDelay((int)ticks);
#endif

    if (gJtagTaskVerbose)
    {
        end = gPII_TickCounter;
        printf("JTAG-TASK: Suspending Done ... %d ms\n", (end-start));
    }
}


/*******************************************************************************/
/*******************************************************************************/
/***
/*** The following are copies of functions that can be found in:
/*** /development/CommonPlatforms/CardServices/JTAG/JTAGDrv/src/JTAG_Xceiver.cpp
/***
/*******************************************************************************/
/*******************************************************************************/

bool EnableJtag(bool theCardIsA1_3_1Amp, UINT32 theSlotId)
{
    UINT32 aCodedSlotID = 0;

    // Build the command based on the Slot Id
    if (theSlotId)
    {
        // enable buffers to access the backplane
        EnableBuffers(true);
        // enable address.
        aCodedSlotID = EncodeSlotId(theCardIsA1_3_1Amp, theSlotId);
        aCodedSlotID = ShadowProtocol(aCodedSlotID);
    }
    else
        return false;

    if (xsvf_iDebugLevel > 0)
        printf("JTAG  Encoded ID: 0x%x\n", aCodedSlotID);

    return(SendCmd(aCodedSlotID));
}

bool DisableJtag(void)
{
    UINT32  aCodedSlotID = 0;
    bool rc;

    aCodedSlotID = ShadowProtocol(0x3FE);  // disable address.
    rc = SendCmd(aCodedSlotID);            // Send the disable command
    EnableBuffers(false);                  // enable buffers to access the backplane

    return(rc);
}

bool SendCmd(UINT32 theEncodedSlotId)
{
    int32  i;
    UINT8  tdi;
    UINT8  tdo;
    UINT32 answer = 0;

    // Shouldn't we set TRST high here, too - or none of this will work...

    // Make TDI HIGH for 2 clock cycles
    setPort(_JTAG_TMS_, 1);
    setPort(_JTAG_TDI_, 1);
    for (i = 0; i < 20; i++)
        pulseClock();

    // Serialize the coded address
    for (i = 27; i >= 0; i--)
    {
        tdi = (UINT8)((theEncodedSlotId >> i) & 0x1);
        setPort(_JTAG_TDI_, tdi);
        pulseClock();
    }

    // Transmit 28 clock pulses to receive the response from the Xceiver
    setPort(_JTAG_TDI_, 1);
    for (i = 0; i < 28; i++)
    {
        pulseClock();                  // Prepare the bit
        tdo = readTDOBit();            // Read '1' or '0'
        answer = (answer << 1) + tdo;  // Append the read bit
    }

    // Verify if a Xceiver responded (Ignore disconnect command because it is normal not to receive any response)
    if ((answer == theEncodedSlotId) || (theEncodedSlotId == ShadowProtocol(0x3FE)))
    {
        return(true);
    }
    else
    {
        printf("JTAG: No address match. answer: 0x%x  EncodedSlotId: 0x%x  Shadow: 0x%x\n",
                                        answer, theEncodedSlotId, ShadowProtocol(0x3FE));
        return(false);
    }
}

UINT32 ShadowProtocol(UINT32 theEncodedSlotId)
{
    UINT32 i;
    UINT32 aCodedSlotID = 0;

    /* first two bit should be idle followed by two select bits. */
    aCodedSlotID = (aCodedSlotID << 1) + TI_IDLE;
    aCodedSlotID = (aCodedSlotID << 1) + TI_IDLE;
    aCodedSlotID = (aCodedSlotID << 1) + TI_SELECT;
    aCodedSlotID = (aCodedSlotID << 1) + TI_SELECT;
    for (i = 0; i < 10; i++)
    {
        if (theEncodedSlotId & 1)
        {
            aCodedSlotID = (aCodedSlotID << 1) + 0;
            aCodedSlotID = (aCodedSlotID << 1) + 1;
        }
        else
        {
            aCodedSlotID = (aCodedSlotID << 1) + 1;
            aCodedSlotID = (aCodedSlotID << 1) + 0;
        }
        theEncodedSlotId =	theEncodedSlotId >> 1;
	}

    aCodedSlotID = (aCodedSlotID << 1) + TI_SELECT;
    aCodedSlotID = (aCodedSlotID << 1) + TI_SELECT;
    aCodedSlotID = (aCodedSlotID << 1) + TI_IDLE;
    aCodedSlotID = (aCodedSlotID << 1) + TI_IDLE;

	return (aCodedSlotID);
}

UINT32 EncodeSlotId(bool theCardIsA1_3_1Amp, UINT32 theSlotId)
{
    UINT32 i;
    UINT32 aEncodedSlotNum = 0;
    UINT32 aShelfId;

    for (i=0; i<5; i++)
    {
        aEncodedSlotNum <<= 1;
        aEncodedSlotNum |= (theSlotId & 0x01);
        theSlotId >>= 1;
    }

    aShelfId = GetShelfId();
    if (xsvf_iDebugLevel > 0)
        printf("JTAG shelf: %d\n", aShelfId);

    for (i=0; i<3; i++)
    {
        aEncodedSlotNum <<= 1;
        aEncodedSlotNum |= (aShelfId & 0x01);
        aShelfId >>= 1;
    }

    if (theCardIsA1_3_1Amp)
        // the address bits A8 and A9 are connected to 5V on this board only
        aEncodedSlotNum |= 0x0300;

    return(aEncodedSlotNum);
}

UINT32 GetShelfId(void)
{
    UINT32 aSlotId;

    aSlotId = BspGetShelfIdJtag();

    return aSlotId;
}

void EnableBuffers(bool theEnablestate)
{
    if (theEnablestate)
    {
	BspEnableJtag();
    }
    else
    {
	BspDisableJtag();
    }
}
