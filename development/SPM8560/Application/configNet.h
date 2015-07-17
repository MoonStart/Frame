/* configNet.h - network configuration header */

/* Copyright 1984-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,30aug04,j_b  remove INCLUDE_NETWORK dependencies (SPR #99747)
01e,20aug03,dtr  Adding in TSEC config.
01d,31jul03,dtr  Adding fei secondary enet.
01c,07jul03,mil  Added FCC END.
01b,12jun02,kab  SPR 74987: cplusplus protection
01a,10oct99,mtl   written from yk 750 by teamF1

*/

#ifdef INCLUDE_END

#ifndef INCnetConfigh
#define INCnetConfigh

#ifdef __cplusplus
    extern "C" {
#endif

/* includes */

#include "vxWorks.h"
#include "end.h"


/* defines */
/* Sixteen devices configurable :
   primary/secondary/tertiary/quaternary/quinary/senary
   TSEC assumed highest buffer priority followed by FCC */

#define SYS_END_BUFF_LOAN_PRI   1
#define SYS_END_BUFF_LOAN_SEC   2
#define SYS_END_BUFF_LOAN_TER   3
#define SYS_END_BUFF_LOAN_QUA   4

#ifdef INCLUDE_MOT_TSEC_END
#define END_LOAD_FUNC_TSC       sysMotTsecEndLoad
#define END_BUFF_LOAN_TSC       SYS_END_BUFF_LOAN_PRI
#endif

#ifdef INCLUDE_VIRTUAL_TSEC_END
#define END_LOAD_FUNC_VTSC      sysVirtMotTsecEndLoad
#define END_LOAD_FUNC_DFVTSC    sysDfVirtMotTsecEndLoad
#define END_BUFF_LOAN_VTSC      SYS_END_BUFF_LOAN_PRI
#endif

#ifdef INCLUDE_VIRTUAL_END
#define END_LOAD_FUNC_VIRT      sysVirtualEndLoad
#define END_BUFF_LOAN_VIRT      SYS_END_BUFF_LOAN_SEC
#endif

#ifdef INCLUDE_MOT_FCC_END
#define END_LOAD_FUNC_FCC       sysMotFccEndLoad
#define END_BUFF_LOAN_FCC       SYS_END_BUFF_LOAN_TER
#endif

/* The END_LOAD_STRING is defined empty and created dynamicaly */

#define END_LOAD_STRING ""      /* created in sys<device>End.c */

#if defined(INCLUDE_PRIMARY_TSEC_END) || defined(INCLUDE_SECONDARY_TSEC_END)
IMPORT END_OBJ * END_LOAD_FUNC_TSC (char *, void*);
#endif

#if defined(INCLUDE_PRIMARY_TSEC_END) && defined(INCLUDE_VIRTUAL_TSEC_END)
IMPORT END_OBJ * END_LOAD_FUNC_VTSC (char *, void*);
IMPORT END_OBJ * END_LOAD_FUNC_DFVTSC (char *, void*);
#endif

#if defined(INCLUDE_PRIMARY_FCC_END) || defined(INCLUDE_SECONDARY_FCC_END)
IMPORT END_OBJ * END_LOAD_FUNC_FCC (char *, void*);
#endif
#if defined(INCLUDE_VIRTUAL_END)
IMPORT END_OBJ * END_LOAD_FUNC_VIRT (char *, void*);
#endif

/* each entry will be processed by muxDevLoad() */

END_TBL_ENTRY endDevTbl [] =
    {
#if defined(INCLUDE_PRIMARY_TSEC_END)
    {0, END_LOAD_FUNC_TSC, END_LOAD_STRING, END_BUFF_LOAN_TSC, NULL},
#endif
#if defined(INCLUDE_SECONDARY_TSEC_END)
    {1, END_LOAD_FUNC_TSC, END_LOAD_STRING, END_BUFF_LOAN_TSC, NULL},
#endif
#if defined(INCLUDE_PRIMARY_TSEC_END) && defined(INCLUDE_VIRTUAL_TSEC_END)
    {0, END_LOAD_FUNC_VTSC, END_LOAD_STRING, END_BUFF_LOAN_VTSC, NULL},
    {1, END_LOAD_FUNC_VTSC, END_LOAD_STRING, END_BUFF_LOAN_VTSC, NULL},
    {2, END_LOAD_FUNC_VTSC, END_LOAD_STRING, END_BUFF_LOAN_VTSC, NULL},
    {3, END_LOAD_FUNC_DFVTSC, END_LOAD_STRING, END_BUFF_LOAN_VTSC, NULL},
    {4, END_LOAD_FUNC_VTSC, END_LOAD_STRING, END_BUFF_LOAN_VTSC, NULL},
#endif
#if defined(INCLUDE_PRIMARY_FCC_END)
    {0, END_LOAD_FUNC_FCC, END_LOAD_STRING, END_BUFF_LOAN_FCC, NULL},
#endif
#if defined(INCLUDE_SECONDARY_FCC_END)
    {1, END_LOAD_FUNC_FCC, END_LOAD_STRING, END_BUFF_LOAN_FCC, NULL},
#endif
#if defined(INCLUDE_VIRTUAL_END)
    {0, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {1, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {2, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {3, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {4, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {5, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {6, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {7, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {8, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {9, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {10, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {11, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {12, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {13, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {14, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {15, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {16, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {17, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {18, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {19, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {20, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {21, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {22, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {23, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {24, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {25, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {26, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {27, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {28, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {29, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {30, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {31, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {32, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {33, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {34, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {35, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {36, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {37, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {38, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {39, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
    {40, END_LOAD_FUNC_VIRT, END_LOAD_STRING, END_BUFF_LOAN_VIRT, NULL},
#endif
    {0, END_TBL_END, NULL, 0, NULL}     /* must be last */
    };

/* define IP_MAX_UNITS to the actual number in the table. */

#ifndef IP_MAX_UNITS
#define IP_MAX_UNITS            (NELEMENTS(endDevTbl) - 1)
#endif  /* ifndef IP_MAX_UNITS */

#ifdef __cplusplus
    }
#endif

#endif /* INCnetConfigh */

#endif /* INCLUDE_END */

