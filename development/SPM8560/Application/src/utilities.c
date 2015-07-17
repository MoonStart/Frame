/*
 * utilities.c
 *
 *  Created on: Feb 8, 2005
 *      Author: ttran4
 */


#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"

#include "config.h"
#include "string.h"
#include "timers.h"
#include "blkIo.h"
#include "ioLib.h"    
#include "iosLib.h"
#include "memLib.h"
#include "errnoLib.h"
#include "dosFsLib.h"
#include "usrLib.h"
#include "sysLib.h"
#include "cacheLib.h"
#include "iv.h"
#include "intLib.h"
#include "muxLib.h"

#include "elf.h"
#include "loadLib.h"

#include "edrErrLogLib.h"
#include "edrLib.h"
#include "mmuAttr.h"
#include "vmLibCommon.h"
#include "vxWorksCommon.h"

//#include "tffsDrv.h" --Commented out by Anoop
//#include "fatlite.h" --Commented out by Anoop
//#include "edrLib.h"
#include "pmLib.h"
#include "private/edrLibP.h"
#include "edrLibCommon.h"
#include "setjmp.h"

#include "dirent.h"
#include "stat.h"
#include "ioLib.h"
#include "tickLib.h"
#include "sysLib.h"

#include "wrSbc85xx.h"
#include "utilities.h"
#include "LoadHeader.h"
#include "typeDefine.h"
#include "ss_gdef.h"
#include "flash.h"
//#include "flash_drv.h" --Commented out by Anoop

#include "cfDrv.h"
#include "diskPartitions.h"

#ifdef INCLUDE_LOADFPGA
#include "mapper_fpga.h"
#include "bpif_fpga.h"
#include "boardRegs.h"
#endif

#include "chipSelects.h"
#include "IdProm/CardIdProm.h"
#include "bpfpga.h"
#include "osc_version.h"
#include "bpif_version.h"
#include "bsp.h"

#define EVAL_BRD_LED_ADDR	0x28000000
#define RAMDISK_BYTES_PER_BLOCK    512
#define RAMDISK_NUM_BLOCK	   275000
#define RAMDISK_SIZE		(RAMDISK_BYTES_PER_BLOCK * RAMDISK_NUM_BLOCK) /*approx 134 MB*/

extern BLK_DEV* ramDevCreate
    (
    char	*ramAddr,	/* where it is in memory (0 = malloc) */
    int		bytesPerBlk,	/* number of bytes per block */
    int		blksPerTrack,	/* number of blocks per track */
    int		nBlocks,	/* number of blocks on this device */
    int		blkOffset	/* no. of blks to skip at start of device */
    );
    
extern STATUS sysTffsFormat(int drvNum);
extern STATUS usrTffsConfig(int drive, int removable,char *fileName);
extern void jumpToCode(unsigned int memory);

extern STATUS sysEnetAddrGet( int, unsigned char*);
extern STATUS sysIpAddrGet( int, unsigned char*);
extern unsigned int sysSubnetMaskAddrGet( int );
extern int sysIfInUseGet( int );


char *flashVolume[] = {"/flashdisk0", "/flashdisk1"};
char *ramdisk = {"/ramdisk0"};

unsigned char TEST_MAC_ADDR[36] = {0x01, 0x00, 0xce, 0xfa, 0xed, 0xfe,
				0x02, 0x00, 0xce, 0xfa, 0xed, 0xfe,
				0x03, 0x00, 0xce, 0xfa, 0xed, 0xfe,
				0x04, 0x00, 0xce, 0xfa, 0xed, 0xfe,
				0x05, 0x00, 0xce, 0xfa, 0xed, 0xfe,
				0x06, 0x00, 0xce, 0xfa, 0xed, 0xfe};

extern void* ApplRomLocation;

unsigned char ledPattern[9] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0xff};

extern int xilinx_parallel_fpga_dnld(unsigned char *startAddr,
		             unsigned int fpgaSize,
                     char verbose,
		             unsigned int x_data_reg,
		             unsigned int x_config_reg,
		             unsigned int x_prgrm_bit_mask,
		             unsigned int x_init_bit_mask,
		             unsigned int x_busy_bit_mask,
		             unsigned int x_done_bit_mask);

extern int xilinx_serial_fpga_dnld(unsigned char *startAddr,
		             unsigned int fpgaSize,
                     char verbose,
		             unsigned int x_data_reg,
		             unsigned int x_config_reg,
		             unsigned int x_prgrm_bit_mask,
		             unsigned int x_init_bit_mask,
		             unsigned int x_done_bit_mask);

int gFPGAIsProgrammed = 0;
int gMapperFpgaSupported = 0; /*0 = unknown, 1=Supported, 2= not supported */

extern int CSPII_Spm8560Layer2Switch_StopHDP();

extern volatile int REBOOT_IS_COLD;

void printTellabsLogo()
{
    printf("\n .::::::::::::::::::::."
           "\n::::::::::::::::::::::::"
           "\n:::::              :::::"
           "\n:::::  ::::  ::::  :::::  ::           :: ::         ::"
           "\n       ::::  ::::       ::::::  .:::.  :: ::  .:::.  ::.::.   .:::.(R)"
           "\n       ::::  ::::         ::   ::   :: :: :: ''   :: ::'  :: ::   `` "
           "\n       ::::               ::   ::::::: :: ::  .::::: ::   ::  `:::. "
           "\n       ::::::::::         ::   ::   .. :: :: ::   :: ::.  :: ..   ::"
           "\n       `:::::::::         `::   `:::'  :: ::  `:::': ::`::'   `:::'\n\n\n");
}


//------------------------------------------------------------------------------
// getPartNumber()
//
// Returns a pointer to the card's part number ASCII string.
// Also sets the global variables gCardtype_SPM and gCardtype_DPM.
//
bool gCardtype_SPM = false;
bool gCardtype_DPM = false;
CardIdProm_PartNumber_t * getPartNumber()
{
    static CardIdProm_PartNumber_t myCardPartNumber;

    CardIdProm_GetPartNumber(&myCardPartNumber);
    if(strncmp(myCardPartNumber, "81.71115", CARDIDPROM_FIRST_PART_PARTNUM_SIZE) == 0)
        gCardtype_DPM = true;
    else if (strncmp(myCardPartNumber, "81.71114", CARDIDPROM_FIRST_PART_PARTNUM_SIZE) == 0)
        gCardtype_SPM = true;

    //Overwrite the cardtype if there is none found to be an SPM - yes, I realize this will
    //screw up the DPM, but it is the lesser of two problems -- see mr 176953
    if(!gCardtype_DPM && !gCardtype_SPM)
    {
        gCardtype_SPM = true;
    }
    return &myCardPartNumber;
}

/*
 * Description: This routine will try to mount the filesystem. 
 * If it fails, it assumes that the flash has not been formatted yet.
 * It will format the flash and then try to mount the volume for the
 * filesystem.
 *
 * It will also mount the RAM drive.
 */
STATUS setupFileSystem()
{
#ifdef INCLUDE_RAMDRV
     BLK_DEV *pBlkDev;
     DOS_VOL_DESC *pVolDesc;
     device_t xbd;
#endif
    int retVal=0;	
	
#ifdef INCLUDE_USER_FFS
    int	drvNum = 0;
    int ID;

    printf("\nMounting Flash Disk %d \n",drvNum);
	retVal = usrTffsConfig(drvNum,0,flashVolume[drvNum]);	
	if(retVal != OK)  //Failed to mount device. Volume is not formatted
	{
		taskDelay(50);
		printf("\nFailed to mount Flash Disk %d.",drvNum);
		printf("\nFormatting Flash Disk %d \n",drvNum);
		ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);
		retVal = sysTffsFormat(drvNum);
		if (ID != NULL)
		{
		    taskSuspend(ID);
		}
		printf("\nCompleted Formatting Flash Disk %d",drvNum);
		if(retVal == OK)
		{
			printf("\nRe-attempting to mount Flash Disk %d",drvNum);
			retVal = usrTffsConfig(drvNum,0,flashVolume[0]);
			if(retVal == OK)
				printf("\nMounted Flash Disk %d",drvNum);			
		}
	}
	else
	    printf("\nMounted Flash Disk %d",drvNum);
	if(retVal == OK)
		cd(flashVolume[0]);
	
#endif

#ifdef INCLUDE_RAMDRV
     printf("\n\nMounting RAM drive : %s ",ramdisk);
	xbd = xbdRamDiskDevCreate (512, RAMDISK_SIZE, 0, ramdisk);
	if( xbd == NULL )
        	printf("FAILED!! to create Ramdisk device\n");
	else
		{
		/* format the RAM disk, ignore memory contents */
		if (dosFsVolFormat( ramdisk, DOS_OPT_BLANK | DOS_OPT_QUIET, NULL ) != OK)
            printf("FAILED to format volume for ramdisk!!\n");
     }
#endif
    
	
	return(retVal);
}


/* Description: Retrieve ethernet address from memory. The content of 
 *  this memory was copied from the serial eeprom on the control module. 
 * */
void getEnetAddr_8560(unsigned char *addr, int unit)
{

	sysEnetAddrGet( unit, addr);
	/*
    unsigned char tempAddr[6];	
    
    memcpy(tempAddr,(unsigned char *)(MEM_LKUP_TBLE_ADRS + 
	         (MEM_EEPROM_IP_SIZE + (unit * (MEM_EEPROM_IP_SIZE + MEM_EEPROM_MAC_SIZE)))),
	           MEM_EEPROM_MAC_SIZE);
	*(addr + 0) = tempAddr[5];
	*(addr + 1) = tempAddr[4];
	*(addr + 2) = tempAddr[3];
	*(addr + 3) = tempAddr[2];
	*(addr + 4) = tempAddr[1];
	*(addr + 5) = tempAddr[0];
	*/
	return;
}

void getIPAddr_8560(unsigned char *addr, int unit)
{
	sysIpAddrGet( unit, addr);
	/*
    unsigned char tempAddr[4];
    
	memcpy(tempAddr,(unsigned char *)(MEM_LKUP_TBLE_ADRS + 
	         (unit * (MEM_EEPROM_IP_SIZE + MEM_EEPROM_MAC_SIZE))),
	           MEM_EEPROM_IP_SIZE);
	sprintf((char *)addr,"%u.%u.%u.%u",tempAddr[0],tempAddr[1],tempAddr[2],tempAddr[3]);
	*/
	           
	return;
}


/* Description: This routine will copy the default IP address and MAC address
 * information into memory.
 * 
 * */
void setEnetAddr_8560(void)
{
	/*
	memcpy((unsigned char *)(MEM_LKUP_TBLE_ADRS),(unsigned char *)USR_FLASH_LKUP_ADDR, 60);
	return;
	*/
}


/* Description : Light up the debug LED so that we have some kind of visual
 * indication that the software is running. 
 * 
 * */
void startWalkingLEDs(void)
{
	int loop;
	
    unsigned int tempData;
 
	sleep(1);
	for(;;)
	{
	   for(loop=0;loop<8;loop++)
	   {
	   	   tempData = (*(unsigned int *)PDATD_ADRS); 
	   	   tempData = (tempData & 0xffffff00) | ((unsigned int)ledPattern[loop]);
	       (*(unsigned int *)PDATD_ADRS) = tempData;
	       sleep(1);
	   }
	}
	return;
}



/* Description : This routine is used to display a pin wheel while the
 * flash is being formatted. This helps to indicate to the user that
 * something is being worked on.
 *
 * */
void heartbeat(void)
{

	static int heartbeatIndex = 0; //, size = 3;
	static char heartbeatChars[4] = {'-', '\\', '|', '/'},
            restoreCursorStr[] = "8\0",
            heartbeatStr[3];


	printf("\nPlease standby..... %s","7\0");
	for(;;)                     
	{                           
             /* Build the heartbeat string, which consists of a heartbeat
                character and the "return the cursor to ground zero" string      */
             sprintf(heartbeatStr, "%s%c\0", restoreCursorStr, heartbeatChars[heartbeatIndex]);
             printf("%s",heartbeatStr);
                                
             /* Increase the heartbeat index, to force the next character        */
             heartbeatIndex++;  
             heartbeatIndex &= 0x00000003;
             taskDelay(50);     
        }                       
                                
}                                
                                
/* Description : Start the LEDS process for visual confirmation of board running
 *                              
 * */                           
                                
void startLEDS(void)            
{  
    int ID;                     
	
    ID = taskSpawn("walkingLEDs", 200, 0, 1000,(FUNCPTR)startWalkingLEDs,0,0,0,0,0,0,0,0,0,0);

    return;
}

/* Description : Load elf image file to RAM
 *
 *
 */
int loadElfFileToRam(char *filename)
{
    unsigned int nbytes;
    Elf32_Ehdr ehdr;
    Elf32_Phdr *pPhdr, *pph;
    char tempBuffer[1024];
    int retVal, fd;
    int segment = 0,i;
        
    fd = open(filename, O_RDONLY,  0x444);
    if(fd == ERROR)
       return(ERROR);
 
    retVal = read(fd, tempBuffer, sizeof(tempBuffer));
    if(retVal < (sizeof(Elf32_Ehdr) + sizeof(Elf32_Phdr)))
    {
       	close(fd);
       return(ERROR);
    }
       
    /* Get the Elf header and the program header to find out where
        to load the code and where to start running the code */   
    memcpy(&ehdr, tempBuffer, sizeof(Elf32_Ehdr));
    /* check the program header validity */
    if (ehdr.e_phoff == 0 ||
	ehdr.e_phnum == 0 || ehdr.e_phentsize != sizeof(Elf32_Phdr))
	{
	close(fd);
	return (ERROR);
	}
    /* read the program header */
    nbytes = ehdr.e_phnum * ehdr.e_phentsize;
    if ((pPhdr = (Elf32_Phdr *) calloc (nbytes,1)) == NULL)
	{
	close(fd);
	return (ERROR);
	}
    if (lseek (fd, ehdr.e_phoff, L_SET) == ERROR ||
	read (fd, (char *) pPhdr, nbytes) != nbytes)
	{
	cfree ((char *)pPhdr);
	close(fd);
	return (ERROR);
	}
    /* read each loadable segment */
    for (i = 0, pph = pPhdr; i < ehdr.e_phnum; i++, pph++)
	{
	if (pph->p_type == PT_LOAD)
	    {
	    /* This segment is to be loaded, so do it */
	    printf ("\nLoading %s%ld", segment++ == 0 ? "" : " + ", pph->p_memsz);

	    /* load the bits that are present in the file */
	    if (pph->p_filesz) {
		if (lseek (fd, pph->p_offset, L_SET) != pph->p_offset ||
		    read (fd, (char *) pph->p_vaddr, pph->p_filesz) != pph->p_filesz)
		    {
        	cfree ((char *)pPhdr);
        	close(fd);
        	return (ERROR);
		    }
		}

	    /* zap the bits that didn't appear in the file */
	    if (pph->p_filesz < pph->p_memsz)
		bzero ((char *) (pph->p_vaddr+pph->p_filesz),
		       pph->p_memsz - pph->p_filesz);
	    /* if we might end up executing this we need to flush the cache */
	    if (pph->p_flags & PF_X)
		cacheTextUpdate ((char *)pph->p_vaddr, pph->p_memsz);
	    }
	}                
    cfree ((char *)pPhdr);
    close(fd);      
    return(ehdr.e_entry);    
}

/* Description : Load application code into memory and then jump to the new code.
 *
 * Input : 
 *        char imageTypeLoc : Is the information a file or a memory location
 *        char *filename    : filename including path to load
 *
 * Return : OK or ERROR
 *
 * */
 STATUS loadCodeToRam(char imageTypeLoc, char *filename)
 {
    
    int retVal;
    unsigned int fileAddress;
      
    switch(imageTypeLoc)
    {
        case 'F':
        case 'f':
            retVal = loadElfFileToRam(filename);
            if(retVal != -1)
                cleanCPMAndJump((void*)retVal);
            break;  //FileType = File
         case 'M':
         case 'm':
            fileAddress = strToNum(filename);
            cleanCPMAndJump((void*)loadTlfImage((void*)fileAddress));
            break;
         case 'H':
         case 'h':
         default:
             printf("\nLoadCodeToRam -- This command will allow the user to load code that is in the");
             printf("\n                  file system or currently in flash to be loaded into RAM to");
             printf("\n                  be executed.");
             printf("\n\n Current syntax");
             printf("\n\n loadCodeToRam <file type> <file name or memory location>");
             printf("\n   <file type> : F/f - indicates that the image is a file and the following arguement");
             printf("\n                       is the file name.");
             printf("\n                 M/m - Indicates that the next argument is a memory location where ");
             printf("\n                        images can be retrieved.");
             printf("\n                 H/h - Help");
             printf("\n   <file name/Memory loc> : This will either be a file name or the physical location of");
             printf("\n                           of where the image can be located in flash.");
             break;
    }
     
    return(OK);
}

/* Load TLF image from Flash into RAM. Address of where code to run is returned
 *
 */
unsigned int loadTlfImage(void *loadLocation)
{
    unsigned int loop,srcAddr,destAddr,fileSize,retVal;

    fileSize = GetImageLength(loadLocation);
    destAddr = GetImageLoadAddress(loadLocation);
    srcAddr = ((uint)loadLocation) + GetHeaderLength(loadLocation);
    loop=0;

    while(loop < fileSize)
    {
        if((fileSize - loop) > 4096)
        {
            retVal=flash_read((unsigned char *)(srcAddr + loop),
                              (unsigned char *)(destAddr + loop),-1,4096);
            loop += 4096;
        }
        else
        {
            retVal=flash_read((unsigned char *)(srcAddr + loop),
                              (unsigned char *)(destAddr + loop),
                              -1,(fileSize - loop));
            loop += (fileSize - loop);
        }
    }

    return(destAddr);
}


//=======================================================================================
// cleanCPMAndJump() - This routine will clean up the CPM and then jump to the
//                     load or memory location specified.
//
// Parameter 'loadLocation' may be either the address of the new load's entry point, or
// a pointer to a 7100 LoadHeader struct (which contains the load's entry point as well
// as other data about the load).  cleanCPMAndJump() is clever enough to automatically
// detect which it is.
//
// NOTE: It is STRONGLY PREFERRED that 'loadLocation' be the start addr of a conforming
//       7100 load (with a LoadHeader struct prefixed to it), so that the BBOOT Patch
//       Manager can examine the load and install any required patches for this board's
//       hardware.  If 'loadLocation' is merely the new load's entry point, there is no
//       way for the BBOOT Patch Manager to examine the load for any required patches.
//
void cleanCPMAndJump(void *loadLocation)
{
    unsigned int memAdr,loop;
    FUNCPTR entryPoint;

    if (ValidateHeader((void*)loadLocation) == SUCCESS)
    {
        // Huzzah!  'loadLocation' points to a 7100 LoadHeader!  We can determine the
        // load's entry point (and lots of other stuff!) from it.

        entryPoint = (FUNCPTR)GetImageEntryPoint((void*)loadLocation);
    }
    else
    {
        // Drat!  'loadLocation' is merely the load's entry point.  We can't determine
        // anything at all about the load.

        entryPoint = (FUNCPTR)loadLocation;
    }

    /* call up function to clean up CPM devices */

    taskDelay (sysClkRateGet ());   /* give the network a moment to close */

#ifdef INCLUDE_END
    /* Stop all ENDs to restore to known state for interrupts and DMA */

    (void) muxDevStopAll (0);
#endif  /* INCLUDE_END */

    memAdr = LOCAL_MEM_LOCAL_ADRS;
    /* Lock interrupts before jumping out of boot image. The interrupts
     * enabled during system initialization in sysHwInit()
     */

    intLock();
    for(loop=1;loop<64;loop++)
      m85xxCpmIntDisable(loop);
    //clear out all pending bits  
    *M85XX_CPM_SIPNR_H(CCSBAR) = 0xffffffff;
    *M85XX_CPM_SIPNR_L(CCSBAR) = 0xffffffff;

	/* disable EPIC controller */
    for(loop=1;loop<56;loop++)
      sysEpicIntEnable(loop);
    
    cacheTextUpdate ((void *) (memAdr),   /* cache coherency */
             (size_t) (sysMemTop() - memAdr));
    cacheDisable(INSTRUCTION_CACHE);
    cacheDisable(DATA_CACHE);
    sysClkDisable(); 

    if (! CheckDevelopmentJumper() )  //If dev jumper not present    
       vxMsrSet (0x00020000);   //Only have CE on so that watchdog is still enabled
    else  //dev jumper present
        vxMsrSet(0);


    // Perform a dummy read to ensure the flash is in read-array mode...
    {int dummy; flash_read((uint8*)FLASH_BASE,(uint8*)&dummy,-1,1);}

    // For boards whose ENABLE_FLASH_WRITES/DISABLE_FLASH_WRITES macros were at one point
    // defined to nothing, we must implement the following workaround before jumping to
    // the new load.  If these macros are now defined to turn flash write-protect off/on
    // respectively, and if we're jumping to a load that was built with them defined to
    // nothing, then that load will crash with a machine check exception the first time
    // it tries to access flash.  Turn flash write-protection off to ensure the new load
    // won't crash on its first flash access...
    ENABLE_FLASH_WRITES;  // Would not be required here except for the reason above.


#ifndef BBOOT_ENTRYPTS_IS_VALID
#error "BBOOT_ENTRYPTS_IS_VALID must be defined in your bsp.h file!"
#endif
    if (BBOOT_ENTRYPTS_IS_VALID)
    {
        // This card's BBOOT has a valid bbootEntryPoints table. Jump to the load through
        // BBOOT's patchAndJumpToLoad(), which will examine the load, patch it if
        // necessary, and jump to it.  (patchAndJumpToLoad(), like this function, is also
        // clever enough to detect whether loadLocation is a LoadHeader ptr or not.)
        //
        entryPt_patchAndJumpToLoad(BOOT_NORMAL, (void*)loadLocation);
    }
    else
    {
        // This card's BBOOT doesn't have a bbootEntryPoints table.
        // Just jump to the entry point without patching.
        //
        (entryPoint)(BOOT_NORMAL, (void*)loadLocation);
    }
}



void tlabSpecificRebootHook (int startType)
{
    extern void ShutDownTDM(void);
	uint16 shelf = GetBpShelfId();
	if (shelf != 1 && shelf != 15)
	{
	    //Release mastership
        BP_FPGA_CLR_MASTER;
    }
    else
    {
        //this is a main shelf - shutdown TDM bus
        ShutDownTDM();
    }
}

/* Handle fatal kernel exceptions by performing a warm reboot of the card */
void handleFatalKernelError (int kind, EDR_TASK_INFO *info, bool mode)
{
	if (!CheckDevelopmentJumper()) /*Development jumper not present*/
	{
        if (kind == EDR_FACILITY_KERNEL)
		{
            printf("\nhandleFatalKernelError kind %x - REBOOT\n", kind);
            REBOOT_IS_COLD=1;
		    reboot(BOOT_NORMAL);
		}
	}
    else
    {
        if (kind == EDR_FACILITY_KERNEL)
        {
            printf("\nhandleFatalKernelError kind %x - Reboot Ignored by Dev Jumper\n", kind);
        }
    }

}

/* Handle user fatal exceptions by performing a warm reboot of the card*/
EDR_ERRINJ_HOOK_FUNCPTR handleFatalUserError(int kind,const char * fileName, int lineNumber,void * address, const char *    msg)
{
    int kindToCheck = (EDR_FACILITY_USER | EDR_SEVERITY_FATAL);
	if (!CheckDevelopmentJumper()) /*Development jumper not present*/
	{
        if (kind == kindToCheck)
		{
            printf("\nhandleFatalUserError kind %x line %d - REBOOT\n", kind, lineNumber);
            if (msg)
            {
                printf("Msg: %s\n", msg);
            }
            if (fileName)
            {
                printf("File: %s\n", fileName);
            }
            REBOOT_IS_COLD=1;
		    reboot(BOOT_NORMAL);
		}
	}
    else
    {
        if (kind == kindToCheck)
		{
            printf("\nhandleFatalUserError kind %x line %d - Reboot ignored by Dev Jumper\n", kind, lineNumber);
            if (msg)
            {
                printf("Msg: %s\n", msg);
            }
            if (fileName)
            {
                printf("File: %s\n", fileName);
            }
		}
	}
}

 

 
 
 /* Description: Perform a test load of the application code under the PRIMARY directory
  *                under /flashdisk0
  *
  * */
void testLoad()
{
    loadCodeToRam('f',"app.elf");
    return;
}


/* Description : Erase flash sector. This routine will erase the sector that contains the offset.
 * It will erase only one flash sector.
 *
 * */
int rawFlashErase(int driveNo, int offset)
{
	/* Commented out by Anoop
    PhysicalInfo info;
    int unitNo,loop;
    int unitSize,count;
    

    if (tffsRawio (driveNo, TFFS_GET_PHYSICAL_INFO, (int)&info, 0, 0) != OK)
    {
//        printErr ("Unable to get physical info from drive\n");
	    return (ERROR);
	}

    // Now let us determine is hardware sector size is the same as what we think it is.
    // Our assumed sector size can only be smaller or the same size as the h/w.
    // If our sector size is smaller than the h/w, we need to make sure that we erase the
    // entire h/w sector by performing multiple erases.
    if(FLASH_SECTOR_SIZE > info.unitSize)
      count = FLASH_SECTOR_SIZE/info.unitSize;
    else
       count=1;
    
    for(loop=0;loop<count;loop++)
    {
        unitNo = (offset+(loop*info.unitSize)) / info.unitSize;
        unitSize = info.unitSize - (offset % info.unitSize);
            
        if (tffsRawio (driveNo, TFFS_PHYSICAL_ERASE, unitNo, 1, 0) != OK)
    	{
    //    	printErr ("Failed attempting to erase Erase Unit %d\n", unitNo);
    	    return (ERROR);
	    }
	}

  */
    return(OK);
}




 
/* Description : Perform writes to flash. It assumes that where ever
 * it is writing, that the flash has been erased and ready to be written.
 *
 * */
int rawFlashWrite(int driveNo, int offset, int size, unsigned char *buffer)
{
	/* Commented out by Anoop
    PhysicalInfo info;
    unsigned int unitNo;
    int unitSize;
    unsigned int addr;

    if (tffsRawio (driveNo, TFFS_GET_PHYSICAL_INFO, (int)&info, 0, 0) != OK)
    {
//        printErr ("Unable to get physical info from drive\n");
	    return (ERROR);
	}

    addr = offset;
    unitNo = offset / info.unitSize;
    unitSize = info.unitSize - (offset % info.unitSize);


    if (tffsRawio (driveNo, TFFS_PHYSICAL_WRITE, offset,size,(int)buffer) != OK)
    {
//	printErr ("Failed attempting to restore Erase Unit %d\n", unitNo);
	return (ERROR);
	}

   */
    return(OK);
} 
 
 
/* Description : Performs reads of the flash. Instead of doing a direct
 *  read of the flash, we will us tffsRawIO routine. This will guarantee
 *  that the flash is not being used by any other task during our access.
 *
 *
 * */
int rawFlashRead(int driveNo, int offset, int size, unsigned char *buffer)
{
	/* Commented out by Anoop
    PhysicalInfo info;

    if (tffsRawio (driveNo, TFFS_GET_PHYSICAL_INFO, (int)&info, 0, 0) != OK)
    {
//        printErr ("Unable to get physical info from drive\n");
    	return (ERROR);
	}

    if (tffsRawio (driveNo, TFFS_PHYSICAL_READ, offset, size, (int) buffer) != OK)
       return (ERROR);
	   */
    
    return(OK);
} 
   


    
/* --------------------------------- */
#if 0

STATUS tffsBootImagePut 
    (
    int driveNo,		/* TFFS drive number */
    int offset,			/* offset in the flash chip/card */
    char * filename		/* binary format of the bootimage */
    )
    {
    PhysicalInfo info;
    UINT unitNo;
    UINT unitSize;
    UINT addr;
    char * pBuf;
    int fd;
    int ix;

    if (tffsSocket[driveNo] == NULL)
	return (ERROR);

    if (tffsRawio (driveNo, TFFS_GET_PHYSICAL_INFO, (int)&info, 0, 0) != OK)
        {
        printErr ("Unable to get physical info from drive\n");
	return (ERROR);
	}

    if ((pBuf = (char *)calloc (info.unitSize,1)) == NULL)
	{
       	printErr ("Can't allocate %d bytes of memory\n", info.unitSize);
	return( ERROR ) ;
	}

    if ((fd = open (filename, O_RDONLY, 0644)) == ERROR)
        {
        printErr ("Can't open \"%s\"\n", filename);
	cfree( pBuf ) ;
        return (ERROR);
	}

    addr = offset;
    unitNo = offset / info.unitSize;
    unitSize = info.unitSize - (offset % info.unitSize);

    /* If the offset is not Erase Unit aligned we need to save the the
     * contents of the region begining at the start of this erase unit 
     * and ending at the specified address so we can restore it after
     * we erase the Erase Unit
     */
    if (tffsRawio (driveNo, TFFS_PHYSICAL_READ, unitNo * info.unitSize,
	           offset % info.unitSize, (int)pBuf) != OK)
        {
	printErr ("Failed attempting to save Erase Unit %d\n", unitNo);
	close (fd);
	cfree( pBuf ) ;
	return (ERROR);
	}
        
    if (tffsRawio (driveNo, TFFS_PHYSICAL_ERASE, unitNo, 1, 0) != OK)
	{
	printErr ("Failed attempting to erase Erase Unit %d\n", unitNo);
	close (fd);
	cfree( pBuf ) ;
	return (ERROR);
	}

    if (tffsRawio (driveNo, TFFS_PHYSICAL_WRITE, unitNo * info.unitSize,
	           offset % info.unitSize, (int)pBuf) != OK)
        {
	printErr ("Failed attempting to restore Erase Unit %d\n", unitNo);
	close (fd);
	cfree( pBuf ) ;
	return (ERROR);
	}

    while (unitSize)
	{
        if ((ix = read (fd, pBuf, unitSize)) == ERROR)
            {
            printErr ("Error reading inputfile: 0x%x\n", errno);
	    cfree( pBuf ) ;
            return (ERROR);
            }

        if (ix == 0)
	    break;

        if ((addr + ix) > info.mediaSize)
	    {
	    printErr ("Error : Attempting to write beyond Flash boundary\n");
	    close (fd);
	    cfree( pBuf ) ;
	    return (ERROR);
	    }

        if (tffsRawio (driveNo, TFFS_PHYSICAL_WRITE, addr, ix, (int)pBuf) != OK)
	    {
	    printErr ("Physical write failed at address 0x%x\n", addr);
	    close (fd);
	    cfree( pBuf ) ;
	    return (ERROR);
	    }

	addr += ix;
	unitSize -= ix;
	if (unitSize == 0)
	    {
            unitSize = info.unitSize;
            unitNo++;
            if (tffsRawio (driveNo, TFFS_PHYSICAL_ERASE, unitNo, 1, 0) != OK)
	        {
		printErr ("Failed attempting to erase Erase Unit %d\n", unitNo);
	        close (fd);
	        cfree( pBuf ) ;
	        return (ERROR);
	        }
	    }
	}

    close (fd);
    cfree( pBuf ) ;
    return (OK);
    }


#endif

/* Flash operations below want a delay service with the */
/* prototype 'void (*delay_func)(uint)', but the VxWorks */
/* gives us 'STATUS taskDelay (int ticks)'. */
void taskDelayService(uint delay_ticks)
{
    taskDelay((int)delay_ticks);
}
 
void initFlashDriver(void)
{
	
	int retVal;
	char dataString[] = "The big brown fox jumped over the lazy sleeping dog.<";

	printf("\nTesting - Initializing FLash driver\n");
	retVal = flash_init((void *)printf, taskDelayService, 10);
	printf("\nReturn value : %x ",retVal);
	printf("\nAttempting to erase first sector of flash");
	retVal = flash_erase((uint8 *)0xfc000000, (uint8 *)0xfc07ffff, 0, taskDelayService, 1);
	printf("\nReturn from flash erase : %x:",retVal);
	retVal = flash_prog((uint8 *)0xfc000001, (uint8 *)dataString, 0, -1, sizeof(dataString)-1, 0);
	printf("\nReturn from flash programming : %x",retVal);
	retVal = flash_prog((uint8 *)0xfc000102, (uint8 *)dataString, 0, -1, sizeof(dataString)-1 ,0);
	printf("\nReturn from flash programming : %x",retVal);
	retVal = flash_prog((uint8 *)0xfc000203, (uint8 *)dataString, 0, -1, sizeof(dataString)-1 ,0);
	printf("\nReturn from flash programming : %x",retVal);
	retVal = flash_prog((uint8 *)0xfc000400, (uint8 *)dataString, 0, -1, sizeof(dataString)-1 ,0);
	printf("\nReturn from flash programming : %x",retVal);
	return;
} 


int saveImage2Flash(char *filename, unsigned int where2Write)
{
    int retVal;
    unsigned int sizeOfFile;
    unsigned int totalsize=0,mallocSize=FLASH_SECTOR_SIZE,partialsize,blockSize=FLASH_SECTOR_SIZE;
    unsigned char *dataLoc;
    int fileDesc;
    unsigned int tickRate,tickRead1,tickRead2,fileSize;
    
    struct stat pStat;
    unsigned int startOfBlock, endOfBlock, bytes2Read, dataOffset,flashLocation, writeDataFlag;

    tickRead1=tickGet();

        flashLocation = where2Write;
        fileDesc = open(filename,O_RDONLY,0x777);
        if(fileDesc < 0)
        {
            printf("\nInvalid filename: %s\n",filename);
            return(-1);
        }
        printf("\nWriting image .");
 
        dataLoc = (unsigned char *)calloc(mallocSize,1);
        printf("\ndataLoc = %x",dataLoc);
        if(dataLoc == NULL)
        {
            close(fileDesc);
            printf("\nFailed to allocate memory\n");
            return(-1);
        }
        if (stat(filename,&pStat) == -1)
        {
            printf("\nCannot stat  filename: %s\n",filename);
            close(fileDesc);
            cfree((char *)dataLoc);
            return(-1);
        }
        sizeOfFile=fileSize = pStat.st_size;
        
        do
        {
           writeDataFlag=0;
        /* We will first read the content of the flash at the selected sector.
           Then we will fill our data. If we are filling in the entire sector, 
           there is no need the read the flash. */
            partialsize=0;
            startOfBlock = (0xffffffff - blockSize + 1) & flashLocation;
            endOfBlock = startOfBlock + blockSize - 1;
            if(sizeOfFile > blockSize)
                bytes2Read = blockSize;
            else
                bytes2Read = sizeOfFile;            
            if(bytes2Read != blockSize)
            {
              retVal=flash_read((unsigned char *)startOfBlock,dataLoc,-1,blockSize);
            }
            dataOffset = flashLocation - startOfBlock;
            do
            {
                if(bytes2Read > 4096)
                  retVal=read(fileDesc, (char *)(dataLoc + dataOffset), 4096);
                else
                  retVal=read(fileDesc, (char *)(dataLoc + dataOffset), bytes2Read);
                
                if(retVal < 0)
                {
                   close(fileDesc);
                   cfree((char *)dataLoc);
                   return(-1);
                }
                printf(".");
                fflush(stdout);
                dataOffset += retVal;
                bytes2Read -= retVal;
                writeDataFlag = 1;
                sizeOfFile -= retVal;
            } while ((retVal > 0) && (bytes2Read > 0));
            printf("\ndataOffset = %x",dataOffset);
            if (writeDataFlag == 1)
            {
                   retVal=flash_erase((uint8 *)startOfBlock, (uint8 *)endOfBlock, 0, taskDelayService, 1);
                   retVal=flash_prog((uint8 *)startOfBlock,(uint8 *)dataLoc, 0, -1, blockSize, 0);
                   writeDataFlag = 0;
            }
            flashLocation += blockSize;
        } while (sizeOfFile > 0);

    printf("\nFinished writing image (%d bytes)\n", totalsize);
    cfree((char *)dataLoc);
    close(fileDesc);
    tickRead2=tickGet();
    tickRate = sysClkRateGet();
    printf("\nTicks per second = %d ",tickRate);  
    printf("\nRead ticks  1) %d   2) %d    Diff) %d",tickRead1,tickRead2,tickRead2-tickRead1);  
    printf("\nFile Size        = %d\n",fileSize);

    return(0);
}


int memTest7100(void)
{
    
    char *memory1;
    
    printf("\nSetting malloc");
    memory1 = (char *)malloc(FLASH_SECTOR_SIZE);
    
    printf("\nMemory location = %x",memory1);
    free(memory1);
    printf("\nFreeing memory\n");
    
    return 0;
}
    


/* Utility to take a ascii string and convert it into a number. The string code be a
 *  decimal or hexadecimal string.
 *
 */
    
unsigned int strToNum(char *str)
{
        unsigned int strSize, value,nibbleCnt,hexOrDec,tempVal,temp10Level;
        int loop,xPos;
        strSize = strlen(str);
        nibbleCnt=0;
        hexOrDec=0;
        value=0;
        temp10Level=1;

        if ((str[1] == 0x58) || (str[1] == 0x78))
        {
                xPos = 2;
                hexOrDec = 1;
        }
        else xPos = 0;

        for(loop=strSize-1;(loop >= xPos);--loop)
        {
                if(hexOrDec == 1)
                {
                   if((str[loop] >= 0x30) && (str[loop] <=0x39)) tempVal = str[loop] - 0x30;
                   else
                   {
                        if((str[loop] >= 97) && (str[loop] <= 102))
                          tempVal = str[loop] - 87;
                        else
                        {
                                if((str[loop] >= 65) && (str[loop] <=70))
                                   tempVal = str[loop] - 55;
                                else return(0);
                        }
                   }
                   value = value | (tempVal << nibbleCnt);

                }
                else
                {
                       if((str[loop] >= 0x30) && (str[loop] <=0x39))
                           tempVal = str[loop] - 0x30;
                        else return(0);

                        value = value + (tempVal * temp10Level);
                        temp10Level = temp10Level * 10;
                }

                nibbleCnt += 4;
        }

        return(value);
}


void BootBcopy(uint8 *src, uint8 *dest, unsigned int len)
{
    memcpy(dest,src,len);
    return;
}

void bspHelp(void)
{  
   printf("\nLoadCodeToRam -- This command will allow the user to load code that is in the");
   printf("\n                  file system or currently in flash to be loaded into RAM to");
   printf("\n                  be executed.");
   printf("\n\n Current syntax");
   printf("\n\n loadCodeToRam <file type> <file name or memory location>");
   printf("\n   <file type> : F/f - indicates that the image is a file and the following arguement");
   printf("\n                       is the file name.");
   printf("\n                 M/m - Indicates that the next argument is a memory location where ");
   printf("\n                        images can be retrieved.");
   printf("\n                 H/h - Help");
   printf("\n   <file name/Memory loc> : This will either be a file name or the physical location of");
   printf("\n                           of where the image can be located in flash.");
   printf("\n\n");
   printf("\ndiagMenu -- Run diagnostic menu");
   printf("\n            Set serial eeprom, Display memory limits, & ...");
   printf("\n\ndosFsShow - Display information about a DOS device");
   printf("\n    ex: dosFsShow ""/ramdisk0"" ");
   printf("\n\ndevs -- Display devices that are registered with the kernel");  
   printf("\n\nramTest - performs a quick DDR DRAM test");
   printf("\n    ex: ramTest <# of processes>,<# of words to write>,<# of blocks of memory>,<# of loop per test>");
   printf("\n\nsaveImage2Flash - save an image stored in the filesystem and write to a locatio in flash");
   printf("\n	 ex: saveImage2Flash <File name is quotes>,<storage location>");
   printf("\n\nloadCodeToRam - load an image(TLF or ELF) into RAM to execute");
   printf("\n	 ex: loadCodeToRam <Image type (F:f:M:m)>,<filename or memory location>");
   printf("\n   If image type = F/f, The filename is the name of the ELF image to load from filesystem into RAM");
   printf("\n   If image type = M/m, the filename is really the location in flash to retrieve the TLF file");
   printf("\n\nedrHelp -- Display utilities for displaying Error Log");
   printf("\n\nfileWriteTest -- Perform a file write to a filesystem to determine rate of writes");
   printf("\n    ex fileWriteTest <filename>,<filesize>");
   printf("\n\ncfReadWriteTest -- Perform a write and read back test on the compact flash database section.");
   printf("\n                      Each block written will be %d bytes in size",CF_SECTOR_SIZE);
   printf("\n                      %d blocks have been allocated for the database",gRaw0.pPart->nblks);
   printf("\n	 ex: cfReadWriteTest <starting block>,<number of blocks>");
   printf("\n\nloadfpga <fpga type>,[name of file]");
   printf("\n     fpga_type : 0 = Mapper fpga compiled in");
   printf("\n     fpga_type : 1 = BKIF fpga compiled in");
   printf("\n     fpga_type : 2 = Mapper fpga from a file");
   printf("\n     fpga_type : 3 = BKIF fpga from a file");
   printf("\n     name of file : This is only used for fpga_type 2 and 3");
   printf("\n"); 
   printf("\nisFPGALoaded <Base address of FPGA>");
   printf("\n     Determine if a selected FPGA is loaded or not");
   printf("\n     Mapper FPGA Base address = 0x%x",BRD_MAPPER_FPGA_REG_BASE);
   printf("\n     BPIF FPGA Base address = 0x%x\n",BRD_BP_FPGA_REG_BASE);
   printf("\n");  
   return;
}


//------------------------------------------------------------------------------
int loadfpga(int fpgaType, char *filename)
{
    int retVal = 1; //ERROR

    char *fpgaArray,tempStr[5];
    unsigned char *binArray;
    int	fpgaSize,fileID,byteRead,loop,ID;
     
#ifdef INCLUDE_LOADFPGA
    ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);

    switch(fpgaType)
    {
    	case 0: //mapper from internal memory location
		//Put the Quad OC3 transeiver in reset
		ASSERT_BP_XCVR_RESET;
		retVal = xilinx_parallel_fpga_dnld(mapper_fpga,sizeof(mapper_fpga),0,
		                                   0xfdfe8000,0xfdfd800a,0x40000000,
		                                   0x00400000,0x00002000,0x00004000);
		if(retVal == 0)
		   printf("\nSuccessfully loaded Mapper FPGA");
		else
		   printf("\nFailed loading Mapper FPGA");

		//Release the reset on the Quad OC3 transeiver
		RELEASE_BP_XCVR_RESET;
        break;
      case 1: //backplane fpga
		retVal = xilinx_serial_fpga_dnld(bpif_fpga,sizeof(bpif_fpga),0,
		                                   0xfdfe0000,0xfdfd800a,0x80000000,
		                                   0x00800000,0x00008000); 		
		if(retVal == 0)
		   printf("\nSuccessfully loaded Backplane FPGA");
		else
		   printf("\nFailed loading Backplane FPGA");		                                   
        break;
      case 2:  //mapper fpga from a file
	    
            fpgaArray = malloc(5000000);
	    binArray = malloc(2500000);
	    if(fpgaArray != NULL)
	    {
	    	if(binArray == NULL)
	    	{
	    		filename = (char *)0x00;
	    	}
	    	if(filename != NULL)
	    	{
	    	   fileID = open(filename, O_RDONLY,0x777);
	    	   if(fileID >= 0)
	    	   {
	    	       byteRead=0;
	    	       fpgaSize=0;
            	       do
            	       {
            	       	   byteRead = read(fileID,(char *)(fpgaArray + fpgaSize),1024);
            	       	   fpgaSize += byteRead;
            	       }
            	       while(byteRead != 0);   
            	       close(fileID);
            	       for(loop=0;loop<fpgaSize;loop+=2)
            	       {
            	       	  sprintf(tempStr,"0x%c%c",*(fpgaArray+loop),*(fpgaArray+loop+1));
            	       	  *(binArray+(loop/2)) = strToNum(tempStr);
            	       }      
			retVal = xilinx_parallel_fpga_dnld((unsigned char *)binArray,fpgaSize,0,
			                                   0xfdfe8000,0xfdfd800a,0x40000000,
			                                   0x00400000,0x00002000,0x00004000);
			if(retVal == 0)
			   printf("\nSuccessfully loaded Mapper FPGA");
			else
			   printf("\nFailed loading Mapper FPGA");    
	    	    }
	    	}
                else
                {
                    printf("\nInvalid filename\n");
                }
                free(fpgaArray);
            }
            if (binArray != NULL)
                free (binArray);
        break;
      case 3:

	    fpgaArray = malloc(5000000);
	    binArray = malloc(2500000);
	    if(fpgaArray != NULL)
	    {
	    	if(binArray == NULL)
	    	{
	    		filename=(char *)0x00;
	    	}
	    	if(filename != NULL)
	    	{
	    	   fileID = open(filename, O_RDONLY,0x777);
	    	   if(fileID >= 0)
	    	   {
	    	       byteRead=0;
	    	       fpgaSize=0;
            	       do
            	       {
            	       	   byteRead = read(fileID,(char *)(fpgaArray + fpgaSize),1024);
            	       	   fpgaSize += byteRead;
            	       }
            	       while(byteRead != 0);   
            	       close(fileID);
            	       for(loop=0;loop<fpgaSize;loop+=2)
            	       {
            	       	  sprintf(tempStr,"0x%c%c",*(fpgaArray+loop),*(fpgaArray+loop+1));
            	       	  *(binArray+(loop/2)) = strToNum(tempStr);
            	       }      
			retVal = xilinx_serial_fpga_dnld((unsigned char *)binArray,fpgaSize,0,
		                                   0xfdfe0000,0xfdfd800a,0x80000000,
		                                   0x00800000,0x00008000); 		
			if(retVal == 0)
			   printf("\nSuccessfully loaded Backplane FPGA");
			else
			   printf("\nFailed loading Backplane FPGA");
	    	    }
	    	}
	    	else
                {
	    	   printf("\nInvalid filename\n");
                }
                free(fpgaArray);
            }
            if (binArray != NULL)
                free (binArray);
        break;
      default:
      	printf("\nInvalid fpga selection");
      	printf("\n\nloadfpga <fpga type>,[name of file]");
      	printf("\n     fpga_type : 0 = Mapper fpga compiled in");
      	printf("\n     fpga_type : 1 = BKIF fpga compiled in");
      	printf("\n     fpga_type : 2 = Mapper fpga from a file");
      	printf("\n     fpga_type : 3 = BKIF fpga from a file");
      	break;
    }
 	printf("\n");
	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}
  	
 	
#endif 	

 	return retVal;
}

void IsMapperFpgaSupported(void)
{
	CardIdProm_PartNumber_t anPartNumber;
	CardIdProm_GetPartNumber(&anPartNumber);
	if(strncmp(anPartNumber, "81.71115", CARDIDPROM_FIRST_PART_PARTNUM_SIZE) == 0)
        gMapperFpgaSupported = 2; //Not supported
	else
       gMapperFpgaSupported = 1; //Supported
}


// Returns 1 if all FPGA on card have been programmed.
// Returns 0 if at least 1 device needs to be programmed.
int FPGAIsProgrammed(void)
{
	int rc;
	rc = isFPGALoaded(BRD_BP_FPGA_REG_BASE);
	if (rc != 1)
    {
		return 0; //bp fpga not programmed
    }
    else
    {
        //If the backplane fpga is loaded but the version is not current, we program
		//the fpga here and return all programmed to the caller. This is required
		//to support upgrades of backplane fpga on warm restarts.
		if (isBpFPGACurrent() == 0)
		{
			printf("\nBackplane FPGA version out of date..upgrading");
			loadfpga(1, NULL);
		}
    }

	if (gMapperFpgaSupported ==0)
		IsMapperFpgaSupported();

    if (gMapperFpgaSupported ==1)
	{
	    rc = isFPGALoaded(BRD_MAPPER_FPGA_REG_BASE);
	    if (rc != 1)
		{
		    return 0; //mapper fpga not programmed
		}
		else
		{
			//If the mapper fpga is loaded but the version is not current, we program
			//the fpga here and return all programmed to the caller. This is required
			//to support upgrades of mapper fpga on warm restarts.
			if (isMapperFPGACurrent() == 0)
			{
				printf("\nMapper FPGA version out of date..upgrading");
				loadfpga(0, NULL);
			}
		}
	}

	return 1; //All fpga's programmed
}

void FPGAProgram(void)
{
	//Load backplane fpga
	loadfpga(1, NULL);

	if (gMapperFpgaSupported ==0)
		IsMapperFpgaSupported();

    if (gMapperFpgaSupported == 1)
	{
	    //Load mapper fpga
	    loadfpga(0, NULL);
	}

    gFPGAIsProgrammed = 1;
}

//Check whether the specified fpga is loaded
//It will return:
// -1 : Invalid base address
//  0 : FPGA not loaded
//  1 : FPGA is loaded

int isFPGALoaded(unsigned int fpgaBase)
{

    UINT16 fpgaLoaded=0,oldVal;
    
    if((fpgaBase != BRD_BP_FPGA_REG_BASE) && (fpgaBase != BRD_MAPPER_FPGA_REG_BASE))
       return(-1);  //Invalid fpga base address
       
    oldVal = *(volatile UINT16 *)(fpgaBase + 0x04);
    *(volatile UINT16 *)(fpgaBase + 0x04) = 0xa5c3;
    if(*(volatile UINT16 *)(fpgaBase + 0x04) == 0xa5c3)
       fpgaLoaded = 1;
    *(volatile UINT16 *)(fpgaBase + 0x04) = oldVal;
    
    return(fpgaLoaded);
}

//Check whether the mapper fpga version is different
//It will return:
//  0 : FPGA version is not current
//  1 : FPGA version is current
int isMapperFPGACurrent()
{
	unsigned int fpgaBase = BRD_MAPPER_FPGA_REG_BASE;
	UINT16 vers;
	vers = *(volatile UINT16 *)(fpgaBase + 0x02);
	if (vers != (UINT16)OSC_FPGA_VERSION)
	{
		return 0;
	}

	return 1;
}
	 
//Check whether the bp fpga version is different
//It will return:
//  0 : FPGA version is not current
//  1 : FPGA version is current
int isBpFPGACurrent()
{
	unsigned int fpgaBase = BRD_BP_FPGA_REG_BASE;
	UINT16 vers;
	vers = *(volatile UINT16 *)(fpgaBase + 0x02);
    //printf ("**********bpfpga version %d\n", vers);
	if (vers != (UINT16)BPIF_FPGA_VERSION)
	{
        //Only upgrade the FPGA on the standby SPM
        if (protRamGetControllerActivePreference() == 0x0 &&
            protRamGetControllerStbyPreference() == 0xab)
        {
		    return 0;
        }
	}

	return 1;
}
	 
    
    
/* ----------------- */
void ramTest(int numProc, int globNumWords, int globNumBlocks, int globNumLoop)
{

    char name[40];
    U32 loop;
    int ID;
    
    for(loop=0;loop<numProc;loop++)
    {
        sprintf(name,"ramTestProc%d",loop);
        ID = taskSpawn(name, 200, 0, 5000,(FUNCPTR)ramTestProc,globNumBlocks,globNumLoop,globNumWords,0,0,0,0,0,0,0);     
    }
    return;  
}

void ramTestProc(int globNumBlocks, int globNumLoop, int globNumWords)
{

    U32 numWords=0,numTest,readVal,loop,loop1,loop2,value,errCnt=0,numBlock=0;
    volatile U32 testMemory[100],actualMemory[100];
    int myPid;


    numTest = globNumLoop;
    numBlock = globNumBlocks;
    numWords = globNumWords;

    if(numTest == 0) 
       return;
    for(loop = 0;loop<numBlock;loop++)
    {
        testMemory[loop]=0;
        actualMemory[loop]=0;
    }      
    if(globNumBlocks > 100) 
          numBlock=100;
    myPid = taskIdSelf();
    for(loop = 0;loop<numBlock;loop++)
    {   
        testMemory[loop] = (U32)malloc(4 * numWords);
        printf("\nPID = 0x%0x -> Memory %d = 0x%x   (cnt = %d)",myPid,loop,testMemory[loop],loop);
    }  
    for(loop=0;loop<numTest; loop++)
    {
        printf("\nPID = 0x%0x ->Loop Count = %d",myPid,loop+1);
        printf("\nPID = 0x%0x ->Write - Blocks",myPid);
            
        for(loop1=0;loop1<(numBlock/2);loop1++)
        {
/* write */         
            for(loop2=0;loop2<numWords;loop2++)
            {
                value = (loop1 << ((loop2) & 0x0000001f));
                *(U32 *)(testMemory[loop1*2] + (4*loop2))= value;
            }
            for(loop2=0;loop2<numWords;loop2++)
            {
                value = ((loop1 << 24) >> ((loop2) & 0x0000001f));
                *(U32 *)(testMemory[(loop1*2)+1] + (4*loop2)) = value;
            }
        }
                        
/* read */          
        for(loop1=0;loop1<(numBlock/2);loop1++)
        {
            printf(".");
            for(loop2=0;loop2<numWords;loop2++)
            {
                value = (loop1 << ((loop2) & 0x0000001f));
                readVal = *(U32 *)(testMemory[loop1*2] + (4*loop2));
                if(value != readVal)
                {
                    ++errCnt;
                    printf("\nPID = 0x%0x ->Memory error 0x%x at 0x%08x read = 0x%08x original = 0x%08x\n",myPid,
                                                       errCnt,(testMemory[loop1*2] + (4*loop2)),
                                                                                readVal,value);     
                }
            }
            for(loop2=0;loop2<numWords;loop2++)
            {
                value = ((loop1 << 24) >> ((loop2) & 0x0000001f));
                readVal = *(U32 *)(testMemory[(loop1*2)+1] + (loop2*4));
                if(value != readVal)
                {
                    ++errCnt;
                    printf("\nPID = 0x%0x ->Memory error 0x%x at 0x%08x read = 0x%08x original = 0x%08x\n",myPid,
                                                             errCnt,(testMemory[(loop1*2)+1] + (loop2*4)),
                                                                                readVal,value);     
                }
            }
        }
      }
      
      printf("\n");
    for(loop = 0;loop<numBlock;loop++)
    {
        free((U32 *)testMemory[loop]);      
    }  

    printf("\nPID = 0x%0x ->%d Blocks of %d bytes each, ran %d loops = %d errors\n",myPid,numBlock,4*numWords,numTest,errCnt);
    taskExit(1);
    return;
}

void fileWriteTest(char *filename,int fileSize)
{
int size, fd, ID;
    int loop,retVal,loop1;
    char tempArray[1024],readArray[1024];
     unsigned int tickRate, tickRead1,tickRead2;
    
    /*delete old file if it exists*/
    remove(filename);    
    fd = creat(filename, O_RDWR);
    if(fd == ERROR)
       return;
 
    memset(tempArray,0x31,256);
    memset(&tempArray[256],0x32,256);
    memset(&tempArray[512],0x33,256);
    memset(&tempArray[768],0x34,256);
   
     printf("\nPerforming write test for file %s with size of %d Bytes",filename,fileSize);
//     printf("\nPlease standby...");
	 ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);
    size =0;
    tickRead1=tickGet();
    for(loop=0;loop<fileSize;loop+=size)
    {
    	if((fileSize - loop) > 1024)
    	    size = 1024;
    	else
    	    size = fileSize - loop;
    	    
        retVal = write(fd, tempArray, size);
    }
    tickRead2=tickGet();    
    close(fd);
	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}

    printf("\nCompleted write test for file %s with size of %d Bytes",filename,fileSize);

    tickRate = sysClkRateGet();
    printf("\nTicks per second = %d ",tickRate);  
    printf("\nNumber of ticks for writing file = %d ",tickRead2-tickRead1);
    printf("\nFile write throughput = %d B/sec\n",fileSize/((tickRead2-tickRead1)/tickRate));
    printf("\n\nWe will read back the file to verify content.");

    fd = open(filename, O_RDONLY, 0x777);
    if(fd == ERROR)
      return;

    ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);

    size =0;
    for(loop=0;loop<fileSize;loop+=size)
    {
    	if((fileSize - loop) > 1024)
    	    size = 1024;
    	else
    	    size = fileSize - loop;
    	    
        retVal = read(fd, readArray, size);
        if(size != retVal)
        {
        	printf("\nRead Error : Invalid size");
        	printf("\nExpecting %d bytes - Read %d bytes",size,retVal);
        	break;
        }
        for(loop1=0;loop1<size;loop1++)
        {
        	if(readArray[loop1] != tempArray[loop1])
        	{ 
        		printf("\nData readback error");
        		printf("\nExpecting %x  read back %x",readArray[loop1],tempArray[loop1]);
        		break;
            }
       }
    }
    close(fd);
	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}
    printf("\nCompleted reading back file %s",filename);
    printf("\nTest completed\n\n");

   
    return;
}
	
	

void cfReadWriteTest(unsigned int startBlk, unsigned int nBlk)
{
	unsigned int loop;
	unsigned char *readBlk,*writeBlk;
	STATUS retVal;	
	int ID;
     unsigned int tickRate, tickRead1,tickRead2, tickRead3,tickRead4;
	
	if((startBlk >= gRaw0.pPart->nblks) || ((startBlk + nBlk) >= gRaw0.pPart->nblks))
	{
		printf("\nInvalid startBlk or nBlk value.");
		printf("\nMaximum number of block is %d\n",gRaw0.pPart->nblks);
	    return;
	}
	
	readBlk = malloc(nBlk * CF_SECTOR_SIZE);
	if(readBlk == NULL)
	{
		printf("\nUnable to allocate read block.");
		printf("\nTerminating test\n");
		return;
	}
	writeBlk = malloc(nBlk * CF_SECTOR_SIZE);
	if(writeBlk == NULL)
	{
		printf("\nUnable to allocate write block.");
		printf("\nTerminating test\n");
		free(readBlk);
		return;
	}

    tickRead1=tickGet();			
/* We will use tick value to help us with random values to write into the rawIO */
	memset(readBlk,0x00,CF_SECTOR_SIZE*nBlk);
	memset(writeBlk,0x00,CF_SECTOR_SIZE*nBlk);
	for(loop =0;loop <CF_SECTOR_SIZE*nBlk;loop++)
	{
        if((loop & 0x0000000f) == 0x0000000f)
           tickRead1=tickGet();			
		*(writeBlk + loop) = ((loop + (tickRead1 & 0x000000ff)) & 0x000000ff);
	}	
		
	printf("\nStarting Compact Flash write and read back test");
	printf("\nSize of each block = %d",CF_SECTOR_SIZE);
	printf("\nWriting to Block %d",startBlk);
    ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);
    tickRead1=tickGet();
	retVal =  rawPartitionWrite(startBlk, nBlk, writeBlk);
    tickRead2=tickGet();

	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}
    printf("\nVerifying data...performing read back ");
    ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);
    if(retVal == OK)
    {
  	    tickRead3=tickGet();
    	retVal = rawPartitionRead(startBlk, nBlk, readBlk);
   	    tickRead4=tickGet();

    	if(retVal == OK)
    	{
    	   for(loop=0;loop< CF_SECTOR_SIZE*nBlk;loop++)
    	   {
    	   	   if(*readBlk != *writeBlk)
    	   	     printf("\nError at offset %d, read value = %x    expect value = %x",(UINT32)writeBlk,*readBlk,*writeBlk);
    	   	   else
    	   	   {
    	   	   	  ++readBlk;
    	   	   	  ++writeBlk;
    	   	   }
    	   }   	
	    }
	    else 
	      printf("\nFailed to read compact flash");
	}
	else
	  printf("\nFailed to write compact flash");

	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}
 
    printf("\nCompleted write test from block %d to %d",startBlk, startBlk+nBlk);	  
    tickRate = sysClkRateGet();
    printf("\nTicks per second = %d ",tickRate);  
    printf("\nNumber of ticks for writing file = %d ",tickRead2-tickRead1);
    printf("\nFile write throughput = %d B/sec\n",(CF_SECTOR_SIZE*nBlk)/((tickRead2-tickRead1)/tickRate));
     printf("\nNumber of ticks for reading file = %d ",tickRead4-tickRead3);
    printf("\nFile read rate = %d B/sec\n",(CF_SECTOR_SIZE*nBlk)/((tickRead4-tickRead3)/tickRate));


	printf("\n");  
	free(readBlk);
	free(writeBlk);
}
   
STATUS isCFPresent()
{     
   STATUS retVal = 1;
   
   if((*(UINT32*)PDATA_ADRS) & (PA22 | PA23))
      retVal = 0;
      
   return(retVal);
}

//------------------------------------------------------------------------
// Load the selected image into RAM and execute.
//------------------------------------------------------------------------
STATUS loadImage(void)
{
    const char elfSig[] = {0x7F, 'E', 'L', 'F'};
    char *imageStart;
    STATUS status;
    int	ID;

    // Check for ELF image or binary image
    imageStart = (char *) &ApplRomLocation;
    printf("\n\nLoading Application code from 0x%x",imageStart);
    ID = taskSpawn("heartbeat", 200, 0, 2000,(FUNCPTR)heartbeat,0,0,0,0,0,0,0,0,0,0);
    
    if (strncmp(imageStart, elfSig, sizeof(elfSig)) == 0)
    {
        status = loadCodeToRam('M',imageStart);
    }
    else  // Binary file
    {
        status = ERROR;
        if (CopyAndValidateLoad(imageStart) == SUCCESS)
        {
            status = OK;
        }
    }

	if (ID != NULL)
	{
		    taskSuspend(ID);
		    taskDelete(ID);	
	}
    if (status == OK)
    {
    	 printf("\nJumping to 0x%x\n\n",GetLoadEntryPoint(imageStart));
         cleanCPMAndJump((void*)imageStart);
    }
    else
    {
        printf("Invalid %s\r\n", GetLoadEntity(imageStart));  /* P/F BOOT or APPL */
    }

    return(status);
}

void spm8560WDTimeout_ISR()
{
	EDR_USER_FATAL_INJECT(1, "******* ERROR - 1st STAGE WATCHDOG TIMER EXPIRED *******");
        /* Trigger an HRESET in the CPLD */
        DoPOreset();
 	
	return;
}

void spm8560_kickWD(int period)
{
	int timerDelay;
	
	if(period == 0)
	  timerDelay=1;
	else
	  timerDelay=(period * 1000)/4;
	  //period being passed in is in seconds. We'll convert to ms and set
	  //  delay for a quarter of the period.
     for(;;)
     {	  
	taskDelay(timerDelay);
	sysWdtPet();
     }
}

void setUpWatchdog1stTime(int period)
{
	int retVal;

        if(period == 0)
        {
        	printf("\nInvalid period for Watchdog. Must be greater than 0\n");
        	return;
        }
	sysWdtDisable();  //We will disable the watchdog before config
 	sysWdtRateSet(period);
       	retVal = sysWdtConnect(spm8560WDTimeout_ISR,0);
        sysWdtEnable();        

	return;
 }	
 

void setUpWatchdog2ndTime(int period)
{
	int retVal;

        if(period == 0)
        {
        	printf("\nInvalid period for Watchdog. Must be greater than 0\n");
        	return;
        }
	sysWdtDisable();  //We will disable the watchdog before config
	InitWatchdogInterface();  //bsp
//	printf("\nRequested period = %d mSec  Actual period = %d mSec",period, sysWdtRateGet());
//Take out for final code
	watchdogStartKicker();  //bsp use
	
	reconfigWdt(period);
 
	return;
 }	
 
 
 
void reconfigWdt(int period)
 {
	sysWdtDisable();         //We will disable the watchdog before config
	sysWdtRateSet(period);   //Set new wdt period
        if (! CheckDevelopmentJumper() )  //If dev jumper not present
           sysWdtEnable();          //Re-enable period
        return;
 }	


   
