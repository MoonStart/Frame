/***********************************************************************/
/*                                                                     */
/*   MODULE:  sys_conf.h                                               */
/*   DATE:    98/11/17                                                 */
/*   PURPOSE: SPM8560 App specific VXWorks configuration definitions   */
/*                                                                     */
/*																	   */
/*                                                                     */
/***********************************************************************/
#ifndef _SYS_CONF_H
#define _SYS_CONF_H



/***********************************************************************/
/*                                                                     */
/* SC_APP_PARMS must be defined before you include sysvars.h file.     */
/* Since "sysvars.h" file depends on SC_APP_PARMS and BSP_PARMS        */
/* to define the Storage Parms Structure.                              */
/*                                                                     */
/* Defining this variable to a Non-Zero Value will create a space in   */
/* the Storage Parms corresponding to the value. The total space       */
/* allocated is the sum of the BSP_PARMS and SC_APP_PARMS.             */
/*                                                                     */
/* SC_APP_NAME define controls the application name string that will   */
/* be displayed during the boot dialog.                                */
/*                                                                     */
/***********************************************************************/
/* Note: Changing SC_APP_PARMS may invalidate the existing checksum.   */
/* and cause PBOOT to call AppGetdefaults(). Be very careful!  SJE     */
#define SC_APP_PARMS 128
#define SC_APP_NAME  "SPM8560 Application"

#define GNE_SES      18                   /* Number of GNE works */
#define TL1_SES      (TLAB_NE*2)          /* Number of TL1 session to OSS */
#define TL1_SUBSES   TLAB_NE              /* Number of Sub Session to SNE */

/*---------------------------------------------------------------------*/
/* sys/types.h contains common definitions, (example YES, NO and more) */
/*---------------------------------------------------------------------*/
//#include <sys/types.h>

/*---------------------------------------------------------------------*/
/* sysvars.h contains the structures and definitions for the system    */
/* variables that are stored in NVRAM. These structures and            */
/* definitions are also used when creating the boot ROM for the        */
/* target system. By using the same sysvars.h file it will ensure      */
/* consistency of the values stored by the boot ROM and the downloaded */
/* RAM application.                                                    */
/*---------------------------------------------------------------------*/
//#include <sysvars.h>

/***********************************************************************/
/*                                                                     */
/*                 B A S I C   P A R A M E T E R S                     */
/*                                                                     */
/*  The parameters in this section determine the fashion in which      */
/*  many of the other parameters in this file will be used.            */
/*                                                                     */
/*  Many of the parameters in this file have names beginning with      */
/*  either "SC_" or "SD_".  Those beginning with "SC_" are ALWAYS      */
/*  controlled by the values you set in this file.  The values of      */
/*  the "SD_" parameters can be determined either by the definitions   */
/*  given in this file, or by the data found in the target board's     */
/*  parameter storage area.  SC_SD_PARAMETERS determines this.  If     */
/*  SC_SD_PARAMETERS is "SYS_CONF", then the values given in this      */
/*  file will be used for the SD_ parameters.  If SC_SD_PARAMETERS     */
/*  is "STORAGE", then pSOSystem will attempt to use the values found  */
/*  in the board's parameter storage area for the SD_ variables.  If   */
/*  the parameter storage area has not been initialized or has been    */
/*  corrupted, then the values given in this file will be used.  They  */
/*  will also be written to the storage area.                          */
/*                                                                     */
/*  If SC_SD_PARAMETERS is STORAGE, you may enable a "startup dialog"  */
/*  which will allow you to view, and optionally change, the           */
/*  parameter values found in the storage area.  The dialog is enabled */
/*  by setting SC_STARTUP_DIALOG to YES.  In this case,                */
/*  SD_STARTUP_DELAY specifies the number of seconds that the dialog   */
/*  will wait for input before proceeding to boot the system.          */
/*                                                                     */
/*  The SC_STARTUP_DIALOG define either enables the boot dialog if set */
/*  to YES, or disables the boot dialog if set to NO.                  */
/*                                                                     */
/*  SC_BOOT_ROM when set to YES, configures the application as a       */
/*  ROMable application. If set to NO, treats it as a RAM application. */
/*                                                                     */
/*  SC_SD_DEBUG_MODE determines the mode of the system, as follows:    */
/*                                                                     */
/*     DBG_SA: Boot pROBE+ in standalone mode.                         */
/*                                                                     */
/*     DBG_XS: Boot into pROBE+ and wait for the host debugger         */
/*             via a serial connection                                 */
/*                                                                     */
/*     DBG_XN: Boot into pROBE+ and wait for the host debugger         */
/*             via a network connection                                */
/*                                                                     */
/*     DBG_AP: Same as DBG_SA, but also does a pROBE+ "silent startup",*/
/*             meaning that pROBE+ initializes itself without          */
/*             printing a startup banner.  pROBE+ then initializes     */
/*             pSOS+ and starts the application running.   This mode   */
/*             was created to simplify implementation of the pSOSystem */
/*             Boot ROMs. Note that when this mode is used, SMODE_MASK */
/*             in TD_FLAGS is always set. (See pROBE+ configuration    */
/*             parameters below.)                                      */
/*                                                                     */
/*    STORAGE: Use the mode (DBG_SA, DBG_XS, or DBG_XN) found in the   */
/*             parameter storage area.  If a valid mode is not found,  */
/*             then use DBG_SA.                                        */
/*                                                                     */
/*  An important consequence of using SC_SD_DEBUG_MODE=STORAGE should  */
/*  be noted.  If you use the TFTP bootloader in the pSOSystem ROMs    */
/*  to download and start your system, you will be setting             */
/*  SC_SD_DEBUG_MODE = DBG_AP in your target board's parameter storage */
/*  area.  Thus, if you have left SC_SD_DEBUG_MODE set to STORAGE in   */
/*  this file, your downloaded system will also use DBG_AP, meaning    */
/*  that the application will begin running immediately after the      */
/*  TFTP bootloader has loaded and started your system.                */
/*                                                                     */
/*                                                                     */
/***********************************************************************/
#define SC_SD_PARAMETERS    STORAGE 

// This way if you want or not to have a dialog ... you are not stuck with the default value
#ifndef SC_STARTUP_DIALOG
#define SC_STARTUP_DIALOG   0 //Temporary...until pboot is ready
#endif

#define SC_BOOT_ROM         0
#define SD_STARTUP_DELAY    10
#define SC_SD_DEBUG_MODE    STORAGE

#define SD_LAN1               1         /* Enable the LAN interface  */
#define SD_LAN1_IP            0x01000112  /* IP address of the node    */
#define SD_LAN1_SUBNET_MASK   0xffff0000  /* subnet mask for the node  */


/***********************************************************************/
/*                                                                     */
/*         M I S C E L L A N E O U S   N E T W O R K I N G             */
/*                       P A R A M E T E R S                           */
/*                                                                     */
/***********************************************************************/
#define SD_DEF_GTWY_IP        0x00000000  /* Default gateway IP address*/

/***********************************************************************/
/*                                                                     */
/* C O M P O N E N T   C O N F I G U R A T I O N   P A R A M E T E R S */
/*                                                                     */
/*  These parameters should work as is for this application.  You      */
/*  may want to change some of them if you start customizing this      */
/*  application.                                                       */
/*                                                                     */
/***********************************************************************/
//Task Info
#define KC_ROOTSSTK    0x2C000  /* ROOT supervisor stack size          */
#define KC_IDLESTK     0x1000   /* IDLE stack size                     */
#define KC_ROOTUSTK    0        /* ROOT user stack size                */
//#define KC_ROOTMODE    (T_SUPV | T_ISR) /* ROOT initial mode         */
#define KC_ROOTPRI     52      /* ROOT task priority                  */
#define KC_TICKS2SEC   100      /* ticks per second                    */

#endif /* _SYS_CONF_H */

