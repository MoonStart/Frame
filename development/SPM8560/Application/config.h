/* config.h - wrSbc85xx configuration header file */

/*
 * Copyright (c) 2002-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02u,24oct08,j_z  remove RAM_LOW_ADRS, RAM_HIGH_ADRS
02t,26aug08,d_l  correct the oscillator frequency.(WIND00127676)
02s,20aug08,d_l  break default mac(ENET_DEFAULT) to three bytes.(WIND00121398)
02r,23jul08,l_z  Support END2
02q,26may08,syt  modify BSP_REV form "/6" to "/7"
02p,17sep07,h_k  removed INCLUDE_PCI_BUS_SHOW. (CQ:105028)
02o,21aug07,mmi  remove legacy power management define
02o,17aug07,pmr  remove non-default components; fix cache error recovery
02n,12aug07,wap  Correct PCI_MSTR_MEM_BUS and PCI_BRIDGE_PIMMR_BASE_ADRS
                 (WIND00099736)
02m,30jul07,mil  Excluded PCI to workaround boot problem on some boards.
02l,27jul07,vik  Fix for WIND00099581, added macro INCLUDE_VXB_CMDLINE
02k,31may07,h_k  added INCLUDE_SIO_UTILS.
02j,23mar07,pmr  fix bootapp support
02i,05mar07,dtr  Use new PCi bbus controller driver.
02h,06feb07,d_z  Increase BSP revision to 2.0/6.
02g,01feb07,wap  Convert to VxBus TSEC driver
02f,31jan07,wap  VxBus CPM component is now named INCLUDE_VXB_CPM
02e,29aug06,wap  Add VxBus FCC driver support
02d,29nov06,rec	 NOR update - change RAM_HIGH_ADRS, don't lock bootrom text
02c,24oct06,jmt	 Add SYS_MODEL define for bspvts
02b,13sep06,tfo	 Remove WLAN support for Atheros AR521X, not supported
02a,09sep06,jmt	 Fix problem with INCLUDE_AR521X_END undefining INCLUDE_PCI
01z,30aug06,tfo	 WLAN support for Atheros AR521X
01y,28Jul06,tor	 incorporate PCI support, VXBUS mods
01x,06feb06,wap	 Add INCLUDE_PARAM_SYS
01w,15sep05,to	 revision update for VxWorks 6.2.
01v,06apr05,dtr	 Add in SNOOP for cache.
01v,13jun05,pcm	 removed INCLUDE_DOSFS
01u,27aug04,mil	 Modified TFFS macros.
01t,27sep04,mil	 Added conditional for L1 parity error handler (SPR 102069).
01s,30sep04,dtr	 Add in AIM MMU configuration.
01r,30jul04,md	 use default PM_RESERVED_MEM 
01r,14sep04,j_b	 remove INCLUDE_SHOW_ROUTINES (SPR 101418)
01q,10sep04,mil	 Make RAM_LOW_ADRS and RAM_HIGH_ADRS conditional.
01p,10jun04,mil	 Added L1 errata workaround.
01o,08jun04,mdo	 Change MMU configuration - dependency is elsewhere.
01n,26may04,mil	 Fixed L2 not being enabled by default.
01m,10may04,mil	 Repositioned defines of cache macros.
01l,05may04,mil	 Removed TSEC cache undef, added cache settings, N boot cmd.
01k,02feb04,mil	 Added config for L2 cache and L2 SRAM.
01j,23oct03,mil	 Cleanup.
01i,20oct03,mil	 Changed TFFS to optional, removed CTORS_DTORS.
01h,17oct03,mil	 Fixed RAM_HIGH_ADRS value.
01g,12sep03,mil	 Updated settings for cache, clock and interrupt.
01f,29jul03,dtr	 Added snoop and disable L2 because of dcbi/dcbst issue.
01e,22jul03,mil	 Added flash parameters.
01d,07jul03,mil	 Added CPM and SCC.
01c,25jun03,mil	 Added prjParams.h for project build.
01b,09oct02,dtr	 Added more defines for more complete base for BSP.
01a,03oct02,dtr	 Created.
*/


#ifndef	INCconfigh
#define	INCconfigh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */


#define BSP_VER_1_1     1
#define BSP_VER_1_2     1
#define BSP_VERSION     "2.0"
#define BSP_REV         "/7"

#ifndef BOARD_IA_AUTOGENERATE
    #include "configAll.h"
#undef INCLUDE_WDB

#if 1
/* SYM_TBL_HASH_SIZE_LOG2 defines the width of the symbol table's hash table. It takes
 * a positive value that is interpreted as a power of two. The default value for
 * SYM_TBL_HASH_SIZE_LOG2 is 8; and the default width of the symbol table is
 * therefore 256. Using smaller values requires less memory, but degrades lookup
 * performance, so the search takes longer on the average.
 */
#undef SYM_TBL_HASH_SIZE_LOG2
/* Tests were run with a 220656 symbols in the symbol table */
//#define SYM_TBL_HASH_SIZE_LOG2  4 /* blows up, due to failure to satisfy watchdog */
//#define SYM_TBL_HASH_SIZE_LOG2  6 /* 142 seconds to load all symbols. Hash table takes  1.5K less than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2  7 /*  83 seconds to load all symbols. Hash table takes    1K less than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2  8 /*  51 seconds to load all symbols. Hash table takes    0K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2  9 /*  29 seconds to load all symbols. Hash table takes    2K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 10 /*  19 seconds to load all symbols. Hash table takes    6K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 11 /*  14 seconds to load all symbols. Hash table takes   14K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 12 /*  12 seconds to load all symbols. Hash table takes   30K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 13 /*  10 seconds to load all symbols. Hash table takes   62K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 14 /*  10 seconds to load all symbols. Hash table takes  126K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 15 /*  10 seconds to load all symbols. Hash table takes  254K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 16 /*  10 seconds to load all symbols. Hash table takes  510K more than hash size 8 */
//#define SYM_TBL_HASH_SIZE_LOG2 18 /*  10 seconds to load all symbols. Hash table takes 2046K more than hash size 8 */

#define SYM_TBL_HASH_SIZE_LOG2   12 /*  12 seconds to load all symbols. Hash table takes   30K more than hash size 8 */


#undef WDB_POOL_SIZE
#define WDB_POOL_SIZE 0x200000
/* using motfcc1 for WDB Agent connection */
#undef WDB_END_DEVICE_NAME
#define WDB_END_DEVICE_NAME     "motfcc" 
#undef WDB_END_DEVICE_UNIT 
#define WDB_END_DEVICE_UNIT     1
#undef WDB_END_DEVICE_ADDRESS
//#define WDB_END_DEVICE_ADDRESS	(char *)(getIfAddr("motfcc1"))
#define WDB_END_DEVICE_ADDRESS	"1.0.1.18"


#define INCLUDE_WINDVIEW
#define INCLUDE_WVUPLOAD_ALL
#define INCLUDE_WDB_TSFS
#define INCLUDE_TIMESTAMPING
#endif
    #include "wrSbc85xx.h"

    /* Common Includes for VXBUS RIO and ETSEC */

    //#define INCLUDE_VXBUS
    //#define INCLUDE_VXB_CMDLINE

    #undef INCLUDE_RAPIDIO_BUS

#endif // BOARD_IA_AUTOGENERATE

//ttran- for 4GB mem. WDB requires 1/16% of free space and cause erroneous calculation
// of MEM_POOL_START_ADRS. Need to undef INCLUDE_WDB
//LRU- Beware this is defined in configAll.h.
#undef INCLUDE_WDB

/* Base model string. sysModel adds processor details */
#define SYS_MODEL	"MPC85"

//#define INCLUDE_VXBUS
#define INCLUDE_PARAM_SYS
#define INCLUDE_HWMEM_ALLOC
#define HWMEM_POOL_SIZE 50000
#define INCLUDE_PLB_BUS
//#define INCLUDE_VXB_CMDLINE

/*
 * FCC ethernet support
 * This is only available on the 8560 board with CPM expansion card.
 */

#ifdef INCLUDE_CPM
//#define INCLUDE_VXB_CPM
//#define INCLUDE_FCC_VXB_END
#define INCLUDE_BCM52XXPHY
#define INCLUDE_MDIO
#endif /* INCLUDE_CPM */

/*
 * TSEC ethernet support
 */
#define INCLUDE_TSEC_VXB_END
#define INCLUDE_BCM54XXPHY

#define INCLUDE_END

/*
 * PCI support
 * This is off by default. Uncomment the following #define to enable it.
 * With newer boards that have no additional PCI slots available, leaving
 * PCI support enabled here will cause the CPU to hang.

#define INCLUDE_PCI_BUS
 */

#ifdef INCLUDE_PCI_BUS
#define INCLUDE_PCI_BUS_AUTOCONF
#define DRV_PCIBUS_M85XX

/*
 * If PCI support and END support are available, enable the
 * Intel PRO/1000 ethernet driver too.
 */
#if defined(INCLUDE_END) || defined(INCLUDE_END2)
#define INCLUDE_GEI825XX_VXB_END 
#define INCLUDE_MII_BUS
#define INCLUDE_GENERICPHY
#define INCLUDE_GEITBIPHY
#endif /* defined(INCLUDE_END) || defined(INCLUDE_END2) */

#endif /* INCLUDE_PCI_BUS */

#define DRV_RESOURCE_M85XXCCSR
#define DRV_SIO_NS16550
#define INCLUDE_SIO_UTILS

/* This constant must be here for the SPM BSP. This will force system to use
 *   the SPM usrNetwork.c version of code. This constant is used in usrConfig.c
 */
#define INCLUDE_IPATTACH
#define PROJECT_SPECIFIC_USRNETWORK
#define INCLUDE_SEM_READ_WRITE
#define INCLUDE_SEM_READ_WRITE_CREATE
#define INCLUDE_SEM_BINARY
#define INCLUDE_SEM_BINARY_CREATE



/*
 *  Customizations for running the pboot image on the WindRiver eval board.
 * Defines needed before the global configuration information.
 */

#ifndef BBOOT
#define INCLUDE_IP_SECURITY
#define IPTCP_DEBUG
#endif

#define INCLUDE_TLS

#ifndef BBOOT
/*---------------------------------------------------------------------*/
/* VxWork core configuration parameters                                */
/*---------------------------------------------------------------------*/

#ifdef ISR_STACK_SIZE
  #undef ISR_STACK_SIZE
#endif /* ISR_STACK_SIZE */
#define ISR_STACK_SIZE          (0x8000)  /* size of ISR stack, in bytes */

/*---------------------------------------------------------------------*/
/* VxWork network configuration parameters                             */
/*---------------------------------------------------------------------*/
#define INCLUDE_BCM1
#define INCLUDE_BCM5324
#define INCLUDE_NWT
#define INCLUDE_NMT
	
/* We used to define INCLUDE_ADDIF, but all it did was to try to establish
   a nonsense interface called "fei1" during boot up, and then proceed to
   generate an annoying error message about its inability to do so. We don't
   need that grief. Undefine it here so that it isn't left enabled by
   accident due to an inclusion of "configAll.h". SJE */
#undef INCLUDE_ADDIF
	
/* Socket Components */
#define INCLUDE_SOCKLIB
#define INCLUDE_BSD_SOCKET
#define INCLUDE_ROUTING_SOCKET
#ifdef INCLUDE_RTP
    #define INCLUDE_SC_SOCKLIB
#endif

/* POSIX components */
#define INCLUDE_POSIX_MQ
#define INCLUDE_POSIX_TIMERS
#define INCLUDE_POSIX_CLOCKS
#define INCLUDE_POSIX_SEM
#define INCLUDE_POSIX_SIGNALS
#define INCLUDE_POSIX_PTHREADS
#define INCLUDE_SIGNALS


/* Network Application Components */
#define INCLUDE_PING
#define INCLUDE_TELNET
#define INCLUDE_TELNET_CLIENT

/* Various Device Components */
#define INCLUDE_UPM
#define INCLUDE_SPI
#define INCLUDE_I2C
//#define INCLUDE_ATA
#define INCLUDE_LOADFPGA
#endif /* not BBOOT */

/*Undef network file storage*/
#ifdef INCLUDE_NFS2_CLIENT
  #undef INCLUDE_NFS2_CLIENT
#endif
#ifdef INCLUDE_NFS3_CLIENT
  #undef INCLUDE_NFS3_CLIENT
#endif
#ifdef INCLUDE_NFS_CLIENT_ALL
  #undef INCLUDE_NFS_CLIENT_ALL
#endif
#ifdef INCLUDE_NFS2_SERVER
  #undef INCLUDE_NFS2_SERVER
#endif
#ifdef INCLUDE_NFS3_SERVER
  #undef INCLUDE_NFS3_SERVER
#endif
#ifdef INCLUDE_NFS_SERVER_ALL
  #undef INCLUDE_NFS_SERVER_ALL
#endif
#ifdef INCLUDE_NFS_MOUNT_ALL
  #undef INCLUDE_NFS_MOUNT_ALL
#endif


#define INCLUDE_SYS_HW_INIT_0

#define INCLUDE_TLAB_DECREMENTER
#undef INCLUDE_VX_DECREMENTER        // only 1 can be defined. Either VX_DEC or TLAB_DEC
#define DEC_TICKS_PER_VX_TICKS 5  //Run the system clock 5 times faster than the VX ticks

#define INCLUDE_TIMESTAMP


/* configAll.h has this value defined as 60, which is the default. We will override this
   to match up with the Application code setting.
 */
#undef SYS_CLK_RATE
#define SYS_CLK_RATE 100


//#define HALT_STRING      "TLAB"
//#define HALT_STR_SIZE    4
#define HALT_STRING      " "
#define HALT_STR_SIZE    1
#define HALT_WAIT_TIME   5

#ifndef BBOOT
#define INCLUDE_USER_APPL  //This is used to pull user specific code
#endif

#undef INCLUDE_ROMFS

/*
 * 8610 Customizations for running the pboot image on the WindRiver eval board.
 * Defines needed after the global configuration information.
 */

#ifdef SHELL_SECURE
#undef SHELL_SECURE
#endif
#define SHELL_SECURE		TRUE


/* for debugging CFI only - comment out for normal operations */
//#define  PRINT_CFIDEBUG

#define INCLUDE_SHELL
#define INCLUDE_SECURITY
	
#ifdef BBOOT
  /* We don't need no stinkin' FTP... */
  #undef INCLUDE_FTP
  #undef INCLUDE_FTP6
  #undef INCLUDE_FTP6_SERVER
  #undef INCLUDE_TFTP_SERVER
  #undef INCLUDE_TFTP_CLIENT

  #undef INCLUDE_UDPV4
  #undef INCLUDE_TCPV4
  #undef INCLUDE_BPF
  #undef INCLUDE_SYSCTL

  #undef INCLUDE_BOOTP
  #undef INCLUDE_NETBUFLIB
  #undef INCLUDE_NETBUFPOOL
  #undef INCLUDE_LINKBUFPOOL
  #undef INCLUDE_NET_DAEMON
  #undef INCLUDE_NET_REM_IO
  #undef INCLUDE_NETWORK
  #undef INCLUDE_APPL_LOG_UTIL

  #undef INCLUDE_ETHERNET
  #undef INCLUDE_END
  #undef INCLUDE_MUX
#endif /* BBOOT */

#define INCLUDE_IPFTPS

/* No guest logins allowed! */
#ifdef INCLUDE_FTPD6_GUEST_LOGIN
  #undef INCLUDE_FTPD6_GUEST_LOGIN
#endif

#ifndef BBOOT
  #define INCLUDE_SYM_TBL
	
/* Login security initial user name and password.
 * Use vxencrypt on host to find encrypted password.
 * Default password provided here is "tellabs1$".
 */

#ifdef LOGIN_USER_NAME
  #undef LOGIN_USER_NAME
#endif
#define LOGIN_USER_NAME "Admin1"
	
#ifdef LOGIN_PASSWORD
  #undef LOGIN_PASSWORD
#endif
#define LOGIN_PASSWORD "R99SR9zRb"  /* "tellabs1$" encrypted by 'vxencrypt' */

#ifdef NUM_DRIVERS
#undef NUM_DRIVERS
#endif
#define NUM_DRIVERS		50	/* max 50 drivers in drvTable */

#ifdef NUM_FILES
#undef NUM_FILES
#endif
#define NUM_FILES		2000	/* max 2000 files open simultaneously */

#ifdef NUM_DOSFS_FILES
#undef NUM_DOSFS_FILES
#endif
#define NUM_DOSFS_FILES		200	/* max 50 dosFs files open */

#ifdef NUM_RAWFS_FILES
#undef NUM_RAWFS_FILES
#endif
#define NUM_RAWFS_FILES		70	/* max 70  rawFs files open */

#endif /* not BBOOT */

#define INCLUDE_LOADER
#define INCLUDE_HW_FP_SHOW
#define	INCLUDE_CTORS_DTORS
#define	INCLUDE_CPLUS
#define	INCLUDE_CPLUS_LANG
//#define	INCLUDE_CPLUS_IOSTREAMS
#define INCLUDE_CPLUS_IOSTREAMS_FULL  /* include all of iostreams */
#define INCLUDE_CPLUS_DEMANGLER
#define INCLUDE_STAT_SYM_TBL        /* include symbols for VxWorks status codes */
#define INCLUDE_STARTUP_SCRIPT

#define INCLUDE_KERNEL_HARDENING

# ifdef INCLUDE_SHELL
/*---------------------------------------------------------------------*/
/* VxWork show configuration parameters enabling VxShell features      */
/*---------------------------------------------------------------------*/
#  define INCLUDE_DEBUG
#  define INCLUDE_SHOW_ROUTINES
#  define INCLUDE_TASK_SHOW
#  define INCLUDE_NET_SHOW
#  define INCLUDE_SYM_TBL_SHOW
#  define INCLUDE_SHELL_INTERP_C
#  define INCLUDE_SHELL_INTERP_CMD
#  define INCLUDE_DEBUG_SHELL_CMD
#  define INCLUDE_TASK_SHELL_CMD
#  define INCLUDE_SYM_SHELL_CMD
#  define INCLUDE_STANDALONE_SYM_TBL  /* We'll optionally build full or empty symbol table into APP image. */
#  define INCLUDE_FILE_SYM_TBL        /* If symbol table is empty, try to load symbols from separate file. */

#  undef SHELL_DEFAULT_CONFIG
#  define SHELL_DEFAULT_CONFIG "LINE_EDIT_MODE=,LINE_LENGTH=256,STRING_FREE=manual,INTERPRETER=Cmd,VXE_PATH=.;/romfs"
//#  define SHELL_FIRST_CONFIG "LINE_EDIT_MODE=,LINE_LENGTH=256,STRING_FREE=manual,INTERPRETER=Cmd,VXE_PATH=.;/romfs"

# endif /* INCLUDE_SHELL */


#ifdef BBOOT
#undef ONBOARD_STORAGE     /* allows turning on of Flash file system and RAM drv */
#else
#define ONBOARD_STORAGE     /* allows turning on of Flash file system and RAM drv */
#undef  INCLUDE_USER_FFS    /*customized flash file system */
#endif

#ifndef BBOOT
#define INCLUDE_RAM_DISK
#define INCLUDE_RAMDRV
#define INCLUDE_DOSFS
#define INCLUDE_DOSFS_CHKDSK
#define INCLUDE_TFFS
#define INCLUDE_TFFS_SHOW

#define BSP_7100           /* this constant should be defined to force vxworks usrDepend.c
                               to not include systffs.c in it. The BSP will include the file instead.
                               The version used by usrDepend.c is an older version and doesn't work
                               with the 8560 BSP. */
#endif

/* Use DOS File System */
#ifdef INCLUDE_DOSFS
#   define  INCLUDE_DOSFS_MAIN
#   define  INCLUDE_DOSFS_CACHE
#   define  INCLUDE_DOSFS_FAT
#	define	INCLUDE_DOSFS_FMT
#	define	INCLUDE_DOSFS_DIR_FIXED
#   define  INCLUDE_DOSFS_DIR_VFAT
#   define  INCLUDE_DISK_UTIL
#   define INCLUDE_XBD
#   define INCLUDE_XBD_BLK_DEV
#endif  /* INCLUDE_DOSFS */

//
//flash memory device driver include
//#define INCLUDE_MTD_CFISCS
#define SAVE_NVRAM_REGION		/* reserve last region of flash for NVRAM */

#define INCLUDE_SPY

//ttran - take out for now.  #define INCLUDE_USER_APPL


#define  INCLUDE_NET_IF_SHOW     /* Interface show routines */
#define  INCLUDE_NET_HOST_SHOW	 /* Host show routines */
#define  INCLUDE_NET_ROUTE_SHOW  /* Routing show routines */
#define  INCLUDE_ICMP_SHOW       /* ICMP show routines */
#define  INCLUDE_IGMP_SHOW       /* IGMP show routines */
#define  INCLUDE_TCP_SHOW        /* TCP show routines */
#define  INCLUDE_UDP_SHOW        /* UDP show routines */
#define  INCLUDE_IFCONFIG        /* ifconfig command line/API */
#define  INCLUDE_IFCONFIG_PREFIX /* prefix component for ifconfig */


//------------------------------------------------
// Console Serial Port Configuration
//
// SCC4 is used as the console debug port.  CONSOLE_TTY is defined in
// configAll.h, but we override it here for the SPM, which uses SCC4.
//
#undef CONSOLE_TTY               // override configAll.h
#define CONSOLE_TTY 3            // For SCC4, the TTY port is 3.
#include "consoleConfig.h"       // Defines CONSOLE_BAUD_RATE and CONSOLE_PORT_NUM
//------------------------------------------------


#ifndef BBOOT
#define INCLUDE_EDR_PM
#define INCLUDE_EDR_ERRLOG
#define INCLUDE_EDR_SHOW
#define INCLUDE_EDR_SYSDBG_FLAG
#define INCLUDE_MEM_EDR
#define INCLUDE_EDR_POLICIES
#define INCLUDE_MEM_EDR_SHOW
#endif

//ttran - set to reserve memory for error logging
#define USER_RESERVED_MEM   0x10000   // set aside for persistent storage

//Use our own value if it was previously defined
#ifdef PM_RESERVED_MEM
#undef PM_RESERVED_MEM
#endif
#define PM_RESERVED_MEM       0x100000
#ifdef EDR_ERRLOG_SIZE
#undef EDR_ERRLOG_SIZE
#endif
#define EDR_ERRLOG_SIZE       PM_RESERVED_MEM - USER_RESERVED_MEM

/* Boot device and file location */

//#define DEFAULT_SERVER_NAME  "usvattran2kt"
//#define DEFAULT_BOOT_IMAGE   "pboot.elf"
//#define DEFAULT_SERVER       "192.168.208.90"
//#define DEFAULT_IP_ADDR1     "192.168.208.241"
//#define DEFAULT_GATEWAY_ADDR1 ""
//#define DEFAULT_IP_ADDR2      "192.168.218.242"
//#define DEFAULT_GATEWAY_ADDR2 ""
//#define DEFAULT_NETMASK	      0xffffff00
//....
#define DEFAULT_SERVER_NAME  "SERVER"
#define DEFAULT_BOOT_IMAGE   ""
#define DEFAULT_SERVER       "1.1.1.1"
#define DEFAULT_IP_ADDR1     "1.1.1.2"
#define DEFAULT_GATEWAY_ADDR1 ""
#define DEFAULT_IP_ADDR2      "1.1.1.3"
#define DEFAULT_GATEWAY_ADDR2 ""
#define DEFAULT_NETMASK	      0xffffff00


#define DEFAULT_BOOT_LINE \
  ("motetsec(0,0)" DEFAULT_SERVER_NAME ":"DEFAULT_BOOT_IMAGE" h="  DEFAULT_SERVER " e="  DEFAULT_IP_ADDR1  " u=vxworks")
#define DEFAULT_ENET_BOOT_LINE_8560 \
  ("motetsec(0,0)"DEFAULT_SERVER_NAME ":" DEFAULT_BOOT_IMAGE " h="  DEFAULT_SERVER " e="  DEFAULT_IP_ADDR1  " u=vxworks")
#define DEFAULT_ENET_BOOT_LINE2_8560 \
  ("motetsec(1,0)"DEFAULT_SERVER_NAME ":" DEFAULT_BOOT_IMAGE " h="  DEFAULT_SERVER " e="  DEFAULT_IP_ADDR2  " u=vxworks")
#define ALT_BOOT_LINE \
   ("motfcc(0,0)" DEFAULT_SERVER_NAME ":" DEFAULT_BOOT_IMAGE "h=" DEFAULT_SERVER "e=" DEFAULT_IP_ADDR1 "u=vxworks")
#undef	USE_ALT_BOOTLINE	/* define when no bootrom or override NVRAM */


/* Clock speed and source  */

#define	FREQ_33_MHZ	 33333333
#define	FREQ_66_MHZ	 66666666
#define	FREQ_100_MHZ	 99999999
#define	FREQ_133_MHZ	133333333
#define	FREQ_266_MHZ	266666666
#define	FREQ_USR_MHZ	196800000	/* expr result CCB @ 200 MHz */

#define BRG_CLK_RATE  (0x27bc86a)   /* BRG = VCO = 2*CPM/16 */

#define	OSCILLATOR_FREQ     FREQ_33_MHZ	/* oscillator installed */
#define PLAT_FREQ_DEFAULT   (OSCILLATOR_FREQ*10)  /* 10:1 CCB ratio */



/* MMU and cache */

/* To allow recovery from a parity error in the L1 instruction or data
 * cache, the following macro can be defined.  The cache will be put
 * in writethrough mode and hence has a slight penalty on performance.
 * This is available in VxWorks 6.0 only.
 *
 * If this macro is not defined (including VxWorks 6.0 and 5.5.x),
 * it will default to allow recovery from a parity error in the L1
 * instruction cache, but not the data cache.  Writethrough is not
 * required and thus no performance impact.
 */

#undef E500_L1_PARITY_RECOVERY

#ifdef E500_L1_PARITY_RECOVERY
  /* *** NOTE FOR PROJECT FACILITY USERS ***
   * Needs to use WRITETHROUGH, building with Project Facility must also
   * change USER_D_CACHE_MODE and USER_I_CACHE_MODE in Project Facility.
   */

# define CACHE_LIBRARY_MODE     CACHE_WRITETHROUGH
# define CAM_DRAM_CACHE_MODE    _MMU_TLB_ATTR_W
# define TLB_CACHE_MODE         VM_STATE_CACHEABLE_WRITETHROUGH

#else  /* E500_L1_PARITY_RECOVERY */

# define CACHE_LIBRARY_MODE     (CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
# define CAM_DRAM_CACHE_MODE    _MMU_TLB_ATTR_M
# define TLB_CACHE_MODE         (VM_STATE_CACHEABLE | \
                                VM_STATE_MEM_COHERENCY)


  /* If E500_L1_PARITY_RECOVERY is not defined, use local BSP handler.
   * Works for L1 instr cache but not data cache.  Writethrough not needed.
   */
# if defined(INCLUDE_CACHE_SUPPORT) && defined(USER_I_CACHE_ENABLE)
#   if (defined(_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6))
#     define INCLUDE_L1_IPARITY_HDLR              /* VxWorks 6.x */
#   else  /* _WRS_VXWORKS_MAJOR */
#     define INCLUDE_L1_IPARITY_HDLR_INBSP        /* VxWorks 5.5.x */
#   endif /* _WRS_VXWORKS_MAJOR */
# endif  /* INCLUDE_CACHE_SUPPORT && USER_I_CACHE_ENABLE */

#endif  /* E500_L1_PARITY_RECOVERY */

/* ttran - test - put back*/
#define	INCLUDE_MMU_BASIC
#define	USER_I_MMU_ENABLE
#define	USER_D_MMU_ENABLE


#ifdef CACHE_LIBRARY_MODE
# define ICACHE_MODE	CACHE_LIBRARY_MODE
# define DCACHE_MODE	CACHE_LIBRARY_MODE
#else  /* CACHE_LIBRARY_MODE */
# define ICACHE_MODE	CACHE_COPYBACK
# define DCACHE_MODE	CACHE_COPYBACK
#endif  /* CACHE_LIBRARY_MODE */

#define	INCLUDE_CACHE_SUPPORT
#define	USER_D_CACHE_ENABLE
#undef	USER_D_CACHE_MODE
#define	USER_D_CACHE_MODE	(DCACHE_MODE)
#define	USER_I_CACHE_ENABLE
#undef	USER_I_CACHE_MODE
#define	USER_I_CACHE_MODE	(ICACHE_MODE)

#define	INCLUDE_L2_CACHE
#undef	INCLUDE_L2_SRAM   //disable L2_SRAM and give to cache

#if defined(INCLUDE_L2_CACHE) && !defined(INCLUDE_CACHE_SUPPORT)
# warning "Excluding L2 cache because INCLUDE_CACHE_SUPPORT is not defined"
# undef INCLUDE_L2_CACHE        /* L2 requires L1 */
#endif

#define	L2SRAM_ADDR		    (CCSBAR - 0x01000000)   //0x7FFC0000
#define	L2SRAM_WINDOW_SIZE	0x40000

#if (defined(INCLUDE_L2_CACHE) && defined(INCLUDE_L2_SRAM))
# define L2_CACHE_SIZE		L2SIZ_128KB
# define L2_SRAM_SIZE		L2SIZ_128KB
#elif (defined(INCLUDE_L2_CACHE) && !defined(INCLUDE_L2_SRAM))
# define L2_CACHE_SIZE		L2SIZ_256KB
# define L2_SRAM_SIZE		0
#else
# define L2_SRAM_SIZE		L2SIZ_256KB
# define L2_CACHE_SIZE		0
#endif

#define INCLUDE_BRANCH_PREDICTION


/* Serial channel and TTY
 *
 * INCLUDE_CPM should be defined for a MPC8560-based board, or undefined
 * otherwise.  It should be found in EXTRA_DEFINE in the Makefile for a
 * wrSbc8560 board, where the on-board DUART device will be used.  On a
 * wrSbc8540 board, the serial is the on-chip DUART device.  Both the
 * on-board or on-chip devices share the same physical com port.
 *
 * If a mezzanine card with a second serial port is installed on the
 * wrSbc8560, define INCLUDE_MEZZ_COM2 to avoid no output from both
 * COM1 and COM2.
 */

#undef INCLUDE_MEZZ_COM2

#ifdef  INCLUDE_CPM
    #undef INCLUDE_DUART	/* */
    #undef INCLUDE_DUART_EXT	/* */
    #define  INCLUDE_SCC_SERIAL	/*use on-board serial*/
    #undef SCC1_UART
    #undef SCC2_UART
    #undef SCC3_UART
    #define SCC4_UART     /* SPM card only has SCC4 as uart */
#endif

#if (defined(INCLUDE_DUART) || defined(INCLUDE_SCC_SERIAL))
#  undef  NUM_TTY
#ifdef INCLUDE_SCC_SERIAL
#  define NUM_TTY 4    //make sure that this number matches the number of SCC enabled
#else
#  define NUM_TTY 2
#endif
#else
#  undef  NUM_TTY
#  define NUM_TTY 0
#  undef  INCLUDE_TTY_DEV
#endif  /* INCLUDE_DUART || INCLUDE_SCC_SERIAL */


/* EPIC configuration
 *
 * Define INCLUDE_EPIC_CRT_INTR to include EPIC critical handler
 */

#undef	INCLUDE_EPIC_CRT_INTR


/* Optional features support */

#define	INCLUDE_SPE			/* signal processing engine */
#define	INCLUDE_AUX_CLK			/* aux clock */
//#undef	INCLUDE_TIMESTAMP		/* optional timestamp */
//#undef	INCLUDE_SYS_HW_INIT_0		/* extended vectors */
#define	INCLUDE_USR_FLASH		/* maps usr (SIMM) flash */
#define	INCLUDE_LOCAL_SDRAM		/* maps LBC SDRAM */


/* Network driver config */

#ifdef BBOOT
#undef	INCLUDE_PRIMARY_TSEC_END
#undef	INCLUDE_SECONDARY_TSEC_END
#undef	INCLUDE_PRIMARY_FCC_END		/* will undef below if !INCLUDE_CPM */
#undef	INCLUDE_SECONDARY_FCC_END	/* will undef below if !INCLUDE_CPM */
#else
#define	INCLUDE_PRIMARY_TSEC_END
#define	INCLUDE_SECONDARY_TSEC_END
#define	INCLUDE_PRIMARY_FCC_END		/* will undef below if !INCLUDE_CPM */
#define	INCLUDE_SECONDARY_FCC_END	/* will undef below if !INCLUDE_CPM */
#endif

#if defined(INCLUDE_PRIMARY_TSEC_END) || defined(INCLUDE_SECONDARY_TSEC_END)
#   define INCLUDE_END
#   define INCLUDE_MOT_TSEC_END
#   define ETHERNET_ADR_SET
#endif	/* TSEC_END */

#ifdef	INCLUDE_CPM
#   if defined(INCLUDE_PRIMARY_FCC_END) || defined(INCLUDE_SECONDARY_FCC_END)
#       define INCLUDE_END
#       define INCLUDE_MOT_FCC_END
#       define INCLUDE_MOTFCCEND
//#       /* may need to define INCLUDE_MEZZ_COM2 */
#   endif
#else	/* INCLUDE_CPM */
#   undef  INCLUDE_PRIMARY_FCC_END
#   undef  INCLUDE_SECONDARY_FCC_END
#endif	/* INCLUDE_CPM */


/* MAC Address configuration */

#define WR_MAC0                 0x00	/* WR portion of MAC (MSB->LSB) */
#define WR_MAC1                 0xa0
#define WR_MAC2                 0x1e

#define USR_MAC3a               0xb4	/* user portion of MAC address */
#define USR_MAC3b               0xb5	/* user portion of MAC address */
#define USR_MAC3c               0xb6	/* user portion of MAC address */
#define USR_MAC3d               0xb7	/* user portion of MAC address */
#define USR_MAC4                0x2e
#define USR_MAC5                0x3f

#define ENET_DEFAULT		0x1ea00000


/* Remove unsupported drivers */

#undef INCLUDE_SM_NET
#undef INCLUDE_SM_SEQ_ADD


/* TFFS configuration
 *
 * Define INCLUDE_TFFS here if TrueFFS is needed.  Optionally, TFFS
 * can be used to program the bootrom when INCLUDE_TFFS_BOOTROM_OVERWRITE
 * is defined.  Use caution to avoid erasing the bootrom accidentally.
 */

#undef  INCLUDE_TFFS_BOOTROM_OVERWRITE	/* define only when flashing bootrom */

#ifdef	INCLUDE_TFFS
#   define INCLUDE_DOSFS		/* requires dosFs file system */
#endif	/* INCLUDE_TFFS */


/* PCI configuration
 *
 * PCI is not currently supported by this BSP
 */
#define INCLUDE_PCI
#ifdef  INCLUDE_PCI
#define INCLUDE_PCI_AUTOCONF

/*
 *  CPU Addr                                         PCI Addr
 *  PCI_LOCAL_MEM_BUS     -------------------------- PCI_MSTR_MEM_BUS
 *                        -                        -
 *                        -                        -
 *  PCI_LOCAL_MEM_BUS +   -------------------------- PCI_MSTR_MEM_BUS +
 *  PCI_LOCAL_MEM_SIZE    -                        - PCI_MSTR_MEM_SIZE
 *                        -                        -
 *                        -                        ----- PCI Bridge
 *                        -                        -     configuration regs
 *                        -                        -
 *  CPU_PCI_MEM_ADRS      -------------------------- PCI_MEM_ADRS
 *                        -                        -
 *                        -                        -
 *  CPU_PCI_MEMIO_ADRS    -------------------------- PCI_MEMIO_ADRS
 *                        -                        -
 *                        -                        -
 *  CPU_PCI_IO_ADRS       -------------------------- PCI_IO_ADRS
 *                        -                        -
 *                        -                        -
 *  CPU_PCI_IO_ADRS +     -------------------------- PCI_IO_ADRS +
 *  CPU_PCI_IO_SIZE       -                        - PCI_IO_SIZE
 *                        -                        -
 *                        -                        -
 *                        ----PCI Bridge           -
 *                        -------------------------- 4GBytes
 */

/* For custom sysPciAutoConfig.c */

/* PCI based addresses */

#define PCI_MEM_ADRS		0x90000000
#define PCI_MEM_SIZE		0x01000000	/* 16MB */
#define PCI_MEMIO_ADRS		0xa0000000
#define PCI_MEMIO_SIZE		0x01000000	/* 16MB */
#define PCI_IO_ADRS		0xb0000000
#define PCI_IO_SIZE		0x01000000	/* 16MB */

#define PCI_MEM_SIZE_MASK	PCI_ATTR_WS_16M
#define PCI_MEMIO_SIZE_MASK	PCI_ATTR_WS_16M

#define LRU
#ifdef LRU
#define PCI_IO_SIZE_MASK	PCI_ATTR_WS_16M
#endif

/* CPU based addresses */

#define CPU_PCI_MEM_ADRS	0x90000000
#define CPU_PCI_MEM_SIZE	PCI_MEM_SIZE
#define CPU_PCI_MEMIO_ADRS	0xa0000000
#define CPU_PCI_MEMIO_SIZE	PCI_MEMIO_SIZE
#define CPU_PCI_IO_ADRS		0xb0000000
#define CPU_PCI_IO_SIZE		PCI_IO_SIZE

/* CPU from PCI bus */

#define PCI_MSTR_MEM_BUS	0x00000000
#define PCI_MSTR_MEM_SIZE	LOCAL_MEM_SIZE /* 64MB */
#ifdef LRU
#define PCI_BRIDGE_PIMMR_BASE_ADRS	0x50000000
#else
#define PCI_BRIDGE_PIMMR_BASE_ADRS	0x40000000
#endif

/* CPU Address that is visible from PCI */

#define PCI_LOCAL_MEM_BUS	0x00000000
#define PCI_LOCAL_MEM_SIZE	PCI_MSTR_MEM_SIZE
#ifdef LRU
#define PCI_LOCAL_MEM_SIZE_MASK	PCI_ATTR_WS_512M
#else
#define PCI_LOCAL_MEM_SIZE_MASK	PCI_ATTR_WS_128M
#endif

#ifndef	PCI_CFG_TYPE
#   ifdef INCLUDE_PCI_AUTOCONF
#       define PCI_CFG_TYPE PCI_CFG_AUTO
#   else
#       define PCI_CFG_TYPE PCI_CFG_FORCE
#   endif /* INCLUDE_PCI_AUTOCONF */
#endif	/* PCI_CFG_TYPE */

#endif	/* INCLUDE_PCI */


/* Saving boot parameters */

/* NVRAM configuration */

/* NVRAM configuration */
//TTRAN 02/23/05
#undef INCLUDE_NV_RAM
#ifdef  INCLUDE_NV_RAM
#   define NV_RAM_ADRS		0x28b00000
#   undef  NV_RAM_SIZE
#   define NV_RAM_SIZE		0x2000 /* 8KB */
#   define NV_RAM_INTRVL	1
#   undef  NV_BOOT_OFFSET
#   define NV_BOOT_OFFSET	0
#   define NV_MAC_ADRS_OFFSET   0x200

#   define NV_RAM_WR_ENBL	sysNvRamWrEnbl()
#   define NV_RAM_WR_DSBL	sysNvRamWrDsbl()
#   define NV_RAM_READ		sysNvRamRead
#   define NV_RAM_WRITE		sysNvRamWrite
#endif  /* INCLUDE_NV_RAM */

/* Using flash to store boot params is not supported */

#undef INCLUDE_FLASH
#ifdef INCLUDE_FLASH

#ifdef intel_28f640
#   define SYS_FLASH_TYPE	FLASH_28F640J3A    /* flash device type */
#   define FLASH_WIDTH		2
#   define FLASH_CHIP_WIDTH	2
#endif

#   define SYS_FLASH_TYPE	FLASH_28F128J3A    /* flash device type */
#   define FLASH_WIDTH		4
#   define FLASH_CHIP_WIDTH	1


#   define FLASH_WIDTH_SPECIAL_2
#   define FLASH_SEGMENT_SIZE	0x20000


//BOOT_FLASH_ADRS is defined in wrSbc85xx.h
//#   define FLASH_ADRS		(0xff800000 + 0x700000 - FLASH_SEGMENT_SIZE)
#   define FLASH_SIZE		FLASH_SEGMENT_SIZE
#   define FLASH_SIZE_WRITEABLE	FLASH_SEGMENT_SIZE
#   undef  NV_RAM_SIZE
#   define NV_RAM_SIZE		FLASH_SEGMENT_SIZE
#   undef  FLASH_NO_OVERLAY
#   undef  NV_BOOT_OFFSET
#   define NV_BOOT_OFFSET	FLASH_SEGMENT_SIZE - 0x200
//test#define FLASH_BASE_ADDR         0xfc000000
#define FLASH_BASE_ADDR         0xff8000000

#endif  /* INCLUDE_FLASH */

#ifndef NV_RAM_SIZE
#   define NV_RAM_SIZE		NONE
#endif

/* Tellabs Change */
/* Increasing the stack size of tRootTask */
#ifdef ROOT_STACK_SIZE
  #undef ROOT_STACK_SIZE
#endif  /* ROOT_STACK_SIZE */
#define ROOT_STACK_SIZE         (0x75000)   /* size of ROOT stack, in bytes */
#define INCLUDE_VIRTUAL_END

/* Memory addresses */
/* Make this corresponds with information in wrSbc85xx.h */
#ifdef TELLABS_BRD
#define LOCAL_MEM_SIZE		    0x04000000	/* 64 MB memory available - using SDRAM*/
#else
  #define LOCAL_MEM_SIZE		    0x80000000	/*2GB memory available - using DDR*/
  #define LOCAL_MEM_SIZE_2GB                0x80000000  /*2GB */
  #define LOCAL_MEM_SIZE_4GB                0xe0000000  /* 4GB physical space but only 3.5GB usable space */
  #define LOCAL_MEM_SIZE_PTR                0x10        /* Location to retrieve actual memory size given by BBOOT */
  #define MIN_LOCAL_MEM_256_BLK             1           /* 1 * 256 MB = 256MB */
  #define MAX_LOCAL_MEM_256_BLK             14          /* 14 * 256MB = 3.5GB */
  #define DEFAULT_LOCAL_MEM_256_BLK         8           /* 8 * 256MB = 2GB */
#endif
#define LOCAL_MEM_LOCAL_ADRS	0x00000000	/* Base of RAM */


/* Toolchain related defines */

#undef	INCLUDE_PPC_FPU		/* e500 has no std PowerPC fp unit */
#undef	INCLUDE_HW_FP		/* disable hardware fp support */
#define	INCLUDE_SW_FP		/* enable software fp support */


/* Power Management */
#define	DEFAULT_POWER_MGT_MODE	VX_POWER_MODE_DISABLE

#ifdef INCLUDE_MMU_BASIC

#define INCLUDE_AIM_MMU_CONFIG
#define INCLUDE_MMU_OPTIMIZE
#define INCLUDE_AIM_MMU_SHOW
#define INCLUDE_AIM_MMU_MEM_POOL_CONFIG

/*
 * The following parameters are to configure initial memory usage for
 * page table and region tables and in event of running out the increment
 * of memory allocation and is specified as a number of MMU pages (4KByte
 * blocks).
 */
#define AIM_MMU_INIT_PT_NUM 0x40
#define AIM_MMU_INIT_PT_INCR 0x20
#define AIM_MMU_INIT_RT_NUM 0x10
#define AIM_MMU_INIT_RT_INCR 0x10

/* This write protects the page tables */
#define INCLUDE_AIM_MMU_PT_PROTECTION

/*
 * INCLUDE_LOCK_TEXT_SECTION Requires use of CAM entries which can
 * possibly be already used in sysStaticTlbDesc. Also the larger the
 * page size that can be used the less CAM entries required so aligning
 * RAM_LOW_ADRS on a large page size boundary is usually necessary.
 * Locking the text section should increase performance because no
 * Instruction TLB misses are taken within the text section.
 */
#define INCLUDE_LOCK_TEXT_SECTION
#undef INCLUDE_PAGE_SIZE_OPTIMIZATION /* Not available for 85XX */

#endif /* INCLUDE_MMU_BASIC */

#undef _WRS_ARCH_HAS_CPU_PWR_MGMT
#undef INCLUDE_CPU_PWR_MGMT


/*
 * The constants ROM_XXX_ADRS, ROM_SIZE, and RAM_XXX_ADRS are defined
 * in both config.h and Makefile.  All definitions for these constants
 * must be identical.
 */
#ifndef RAM_LOW_ADRS
    #ifdef IMAGE_APP
      #define   RAM_LOW_ADRS        0x00100000
    #else
      #define   RAM_LOW_ADRS        0x01000000
    #endif
#endif  /* RAM_LOW_ADRS */

#ifndef RAM_HIGH_ADRS
    #ifdef IMAGE_APP
      #define   RAM_HIGH_ADRS       0x00e00000
    #else
      #define   RAM_HIGH_ADRS       0x01e00000
    #endif
#endif  /* RAM_HIGH_ADRS */

/* Defines for SwitchDmaBuffer memory block - These MUST match values in 'mem.link' */
#define SWITCH_DMA_BUFFER_ADRS  0x015b0000
#define SWITCH_DMA_BUFFER_SIZE  0x00200000

#define	ROM_BASE_ADRS		0xFFF00000
#define	ROM_TEXT_ADRS		0xFFF00200
#define	ROM_SIZE		0x00100000

#define MEM_EEPROM_BASE_OFFSET   0x0
#define MEM_EEPROM_MAC_OFFSET    0x100


#define MEM_EEPROM_MAC_SIZE    6
#define MEM_EEPROM_IP_SIZE     4

#ifndef BBOOT
/* security libraries, ipsec and ike */
/* tbd is to be done or to be determined */
/* initialization */
/* common cryptographic interface (cci) */

#define INCLUDE_IPCRYPTO
#define INCLUDE_IPCRYPTO_USE_TEST_CMDS

#  define OPENSSL_CONF	"openssl.cnf"
#define OPENSSL_HOME "/dbm/ike"

#define INCLUDE_CCI_DEFAULT_PROVIDER
#define INCLUDE_CCI_IMPORT_AES
#define INCLUDE_CCI_IMPORT_AESKW
#define INCLUDE_CCI_IMPORT_DES
#define INCLUDE_CCI_IMPORT_HASH_CRC32
#define INCLUDE_CCI_IMPORT_HASH_MD2
#define INCLUDE_CCI_IMPORT_HASH_MD4
#define INCLUDE_CCI_IMPORT_HASH_MD5
#define INCLUDE_CCI_IMPORT_HASH_RIP128
#define INCLUDE_CCI_IMPORT_HASH_RIP160
#define INCLUDE_CCI_IMPORT_HASH_SHA1
#define INCLUDE_CCI_IMPORT_HASH_SHA256
#define INCLUDE_CCI_IMPORT_HASH_SHA384
#define INCLUDE_CCI_IMPORT_HASH_SHA512
#define INCLUDE_CCI_IMPORT_HMAC_AESXCBC
#define INCLUDE_CCI_IMPORT_HMAC_MD4
#define INCLUDE_CCI_IMPORT_HMAC_MD5
#define INCLUDE_CCI_IMPORT_HMAC_RIP128
#define INCLUDE_CCI_IMPORT_HMAC_RIP160
#define INCLUDE_CCI_IMPORT_HMAC_SHA1
#define INCLUDE_CCI_IMPORT_HMAC_SHA256
#define INCLUDE_CCI_IMPORT_HMAC_SHA384
#define INCLUDE_CCI_IMPORT_HMAC_SHA512
#define INCLUDE_CCI_IMPORT_INTEGER
#define INCLUDE_CCI_IMPORT_NULL
#define INCLUDE_CCI_IMPORT_PRNG
#define INCLUDE_CCI_IMPORT_PUBLICKEY_RSA
#define INCLUDE_CCI_IMPORT_RC4
#define INCLUDE_CCI_IMPORT_RC4TKIP
#define INCLUDE_CCI_PERFORMANCE
#define INCLUDE_CCI_PROVIDERS
#define INCLUDE_CCI_SSP500_PROVIDER
#define INCLUDE_CCI_VALIDATE
#endif /* BBOOT */


/* web1 */
#undef INCLUDE_WEB1_INIT  /* We don't need the web server in PBOOT or BBOOT */
//#define INCLUDE_SSL
//#define INCLUDE_SSL_APPS
/* tbd FOLDER_NET_UTILS */
/* tbd FOLDER_NET_NETSTAT */
//#define INCLUDE_NETSTAT
//#define INCLUDE_NETSTAT_ICMP
//#define INCLUDE_NETSTAT_IPV4
//#define INCLUDE_NETSTAT_ROUTE
//#define INCLUDE_NETSTAT_TCP
//#define INCLUDE_NETSTAT_UDP
//#define INCLUDE_NETSTAT_IF
/* tbd FOLDER_NET_SHOW */
// NOTICE: Many similar #defines (e.g, INCLUDE_IFCONFIG) are #defined far above.


#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif  /* INCconfigh */

#ifndef BOARD_IA_AUTOGENERATE
    #if defined(PRJ_BUILD)
	#include "prjParams.h"
    #endif // PRJ_BUILD
#endif //BOARD_IA_AUTOGENERATE

