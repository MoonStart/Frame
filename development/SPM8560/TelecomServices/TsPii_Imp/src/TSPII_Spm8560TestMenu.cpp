/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TSPII
TARGET:         SPM8560
AUTHOR:         Anoop Mathew
DESCRIPTION:    Test menu class for TSPII on SPM8560
-----------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_Spm8560TestMenu.h"
#include <string.h>
#include <sys/stat.h>
#include "CommonTypes/CT_CardTypes.h"
#include "ExecutionSupport/FC_BaseStopwatch.h"
#include "ExecutionSupport/FC_BaseTimer.h"

#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_OtsOHIf.h"
#include "TsPii/TSPII_OmsOHIf.h"
#include "TsPii/TSPII_OchOHIf.h"
#include "TsPii/TSPII_OpticalIf.h"
#include "TsPii/TSPII_PilotToneIf.h"
#include "TsPii/TSPII_PipeIf.h"
#include "TsPii/TSPII_OsaIf.h"
#include "TsPii/TSPII_UpdateAction.h"

#include "TsPii_Imp/TSPII_CntrlPilotToneCtrlAction.h"
#include "TsPii_Imp/TSPII_CntrlLxameOsaCtrlAction.h"
#include "TsPii_Imp/TSPII_CntrlSlaveSlot.h"
#include "TsPii_Imp/TSPII_Spm8560SubApplication.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"
#include "TsPii_Imp/TSPII_SPM8560HwRefreshAction.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"
#include "TsPii_Imp/TSPII_CntrlDrtrHwDrvIf.h"
#include "TsPii_Imp/TSPII_CntrlDdltHwDrvIf.h"
#include "TsPii_Imp/TSPII_CardAmpCtrl.h"
#include "TsPii_Imp/TSPII_CardInputAmpOlimCtrl.h"
#include "TsPii_Imp/TSPII_CardCOPMCtrl.h"
#include "TsPii_Imp/TSPII_PilotToneSchedulerAction.h"
#include "TsPii_Imp/TSPII_TdmSlaveCtrl.h"
#include "TsPii_Imp/TSPII_CardRcmmCtrl.h"
#include "TsPii_Imp/TSPII_CardRcmmXDCmdQueue.h"
#include "TsPii_Imp/JdsuRoamSpecializedDev.h"
#include "TsPii_Imp/AmpOpmDevice.h"
#include "TsPii_Imp/TSPII_CardSPURCtrl.h"
#include "TsPii_Imp/Lxame88Pne.h"

#include "CSM/CSM_ConfigStatus.h"
#include "CSM/CSM_AppIf.h"

#include "CsPii/CSPII_DiskDefs.h"
#include "CsPii/CSPII_General.h"
#include "CsPii/CSPII_CardIF.h"
#include "CsPii/CSPII_ShelfIF.h"

#include "Devices/DEV_BackplaneIfFpgaDrv.h"
#include "Devices/DEV_TdmCtrl.h"
#include "Devices/CardFirmwareStatus.h"

#include "T6100_OpticalShelfSlotIf.h"
#include "T6100_OpticalShelfIf.h"
#include "T6100_Dispatcher.h"
#include "T6100_MainAppIf.h"
#include "T6100_ControllerStatusRegion.h"

#include "TsPii_Imp/TSPII_CardNanoCoreCtrl.h"
// #include "TsPii_Imp/NanoCcmDevice.h"
// #include "TsPii_Imp/NanoOlacmDevice.h"
#include "TsPii_Imp/TSPII_NcmSlaveCtrl.h"

#include "BspCommon/storagePromCommand.h"

// the following line is actually declared in CT_CardTypes.h;
// it is here just for documentation purposes;
// extern CardTypeLabel CardTypeLabelTable[];  // in CT_CardTypes.c


using namespace JdsuRoamDevice;
using namespace RcmmCommand;

#ifdef __TARGET__
    #define ACTIVE_LOAD_DIRECTORY ROOTVOLUME OSIEXECPATH
    #define FOPEN_MODE            "r"
#else
    #define ACTIVE_LOAD_DIRECTORY "\\development\\loads\\"
    #define stat_f _stat
    #define stat   _stat
    #define FOPEN_MODE            "rb"
#endif

// TDM_NUM_CARD_SUPPORTED was used, however it is 22, shelf has 19 slots.
// and I'm not willing to change a global definition.
#define NUMBER_OF_SLOTS_IN_SHELF 19

uint8 gTspiiCopmPowerMonitorTest[17][2][100]; //[TdmSlot][port0-port1][Sample]

struct TDM_SupportedCardName
{
    CT_CardType  cardType;
    char         cardTypeName[10];
};

const TDM_SupportedCardName TDM_SupportedCardTypes[TDM_NUM_CARD_SUPPORTED] =
{
    { BMM1_3 ,  "BMM1_3" },   // 0
    { BMM    ,  "BMM"    },   // 1
    { QUAD1_3,  "QUAD1_3"},   // 2
    { QUAD   ,  "QUAD"   },   // 3
    { SCAD1_3,  "SCAD1_3"},   // 4
    { SCAD   ,  "SCAD"   },   // 5
    { FCMM1_3,  "FCMM1_3"},   // 6
    { ECMM   ,  "ECMM"   },   // 7
    { FCMM   ,  "FCMM"   },   // 8
    { OLIM1_3,  "OLIM1_3"},   // 9
    { OLIM   ,  "OLIM"   },   //10
    { NIAM   ,  "NIAM"   },   //11
    { IAM    ,  "IAM"    },   //12
    { NOAM   ,  "NOAM"   },   //13
    { OAM    ,  "OAM"    },   //14
    { MIAM   ,  "MIAM"   },   //15
    { MOAM   ,  "MOAM"   },   //16
    { RIAM   ,  "RIAM"   },   //17
    { RCMM   ,  "RCMM"   },   //18
    { LIAM   ,  "LIAM"   },   //19
    { LOAM   ,  "LOAM"   },   //20
    { LRAM   ,  "LRAM"   },   //21
    { LIAME  ,  "LIAM-E" },   //22
    { LRAME  ,  "LRAM-E" },   //23
    { LOAME  ,  "LOAM-E" },   //24
    { ELRAME ,  "ELRAM-E"},   //25
    { EMOAM  ,  "EMOAM"  },   //26
    { CMM44  ,  "CMM44"  },   //27
    { RCMMS  ,  "RCMMS"  },   //28
    { RCMMS44,  "RCMMS44"}    //29
};
// The number of elements in TDM_SupportedCardTypes is defined by TDM_NUM_CARD_SUPPORTED in DEV_TdmDefinitions.h

//*****************************************************************************
//
//*****************************************************************************

#define CMD     "tspii"
#define HELP    "tspii - control and monitor low level telecom H/W drivers"
#define HWLP    "hw - control and monitor telecom hardware"
#define TDM_DISPLAY_TX_RX(x) (x ? "*" : " ")

#define TSPII_TEST_OK_FAIL(x) ((x) ? "OK    " : "FAILED")

const char* TSPII_StateName[12] =
{
    "TEST_IDLE",
    "TEST_OTS_PMI",
    "TEST_OTS_BDIP",
    "TEST_OTS_BDIO",
    "TEST_OMS_PMI",
    "TEST_OMS_BDIP",
    "TEST_OMS_BDIO",
    "TEST_OMS_FDIP",
    "TEST_OMS_FDIO",
    "TEST_OCH_OCI",
    "TEST_OCH_FDIP",
    "TEST_OCH_FDIO"
};

const FC_CmdProcessor::CMD_TABLE_STRUCT TSPII_Spm8560TestMenu::ourTspiiSpm8560MainMenu[]=
{
    {CMD,  "display",      HELP, "display  - dump interface data",                      TspiiDisplay      },
    {NULL, "displayShelf", NULL, "displayShelf - dump shelf interface data",            TspiiShelfDisplay },
    {NULL, "displayDrtr",  NULL, "displayDrtr  - dump DCC router/TARP cache data",      TspiiDrtrDisplay  },
    {NULL, "displayDdlt",  NULL, "displayDdlt  - dump DCC linkage cache data",          TspiiDdltDisplay  },
    {NULL, "override",     NULL, "override - control manual simulation on target",      TspiiOverride     },
    {NULL, "overrideSlave",NULL, "overrideSlave - control manual simulation on target", TspiiSlaveOverride},
    {NULL, "ochhist",      NULL, "ochhist  - display OCH history for an OSA region", TspiiDisplayOchHist},
    {NULL, "pt",           NULL, "pt       - acquire pilot tone data",              TspiiPilotToneGetData},
    {NULL, "rcmm",         NULL, "rcmm     - select RCMM slot# for future commands",TspiiRcmm        },
    {NULL, "reset",        NULL, "reset    - reset interface data to default",      TspiiReset       },
    {NULL, "resetShelf",   NULL, "resetShelf - reset shelf interface data to default", TspiiShelfReset},
//  {NULL, "setdrtr",      NULL, "setdrtr  - modifies Drtr related attributes",     TspiiDrtr        },
    {NULL, "setoch",       NULL, "setoch   - modify OCH overhead attributes",       TspiiOch         },
    {NULL, "setoms",       NULL, "setoms   - modify OMS overhead attributes",       TspiiOms         },
    {NULL, "setoptAmp",    NULL, "setoptAmp- modify optical attributes on amp",     TspiiAmpOptical  },
    {NULL, "setopt",       NULL, "setopt   - modify optical attributes",            TspiiOptical     },
    {NULL, "setosa",       NULL, "setosa   - modify OSA attributes",                TspiiOsa         },
    {NULL, "setots",       NULL, "setots   - modify OTS overhead attributes",       TspiiOts         },
    {NULL, "setpipe",      NULL, "setpipe  - modify pipe attributes",               TspiiPipe        },
    {NULL, "setpt",        NULL, "setpt    - modify pilot tone attributes",         TspiiPilotTone   },
    {NULL, "setrs",        NULL, "setrs    - modify RS attributes",                 TspiiRs          },
    {NULL, "sett1e1",      NULL, "sett1e1  - modifies t1e1 related attributes",     TspiiT1E1        },
//  {NULL, "simdrtr",      NULL, "simdrtr  - simulates Drtr related hardware",      TspiiSimulDrtr   },
    {NULL, "simip",        NULL, "simip    - simulate IP counters",                 TspiiSimulIp     },
    {NULL, "simoch",       NULL, "simoch   - simulate OCH overhead attributes",     TspiiSimulOch    },
    {NULL, "simoms",       NULL, "simoms   - simulate OMS overhead attributes",     TspiiSimulOms    },
    {NULL, "simopt",       NULL, "simopt   - simulate optical attributes",          TspiiSimulOptical},
    {NULL, "simoptAmp",    NULL, "simoptAmp- simulate optical attributes on amp",   TspiiSimulAmpOptical},
    {NULL, "simosa",       NULL, "simosa   - simulate OSA attributes",              TspiiSimulOsa    },
    {NULL, "simots",       NULL, "simots   - simulate OTS overhead attributes",     TspiiSimulOts    },
    {NULL, "simpt",        NULL, "simpt    - simulate pilot tone attributes",       TspiiSimulPilotTone},
    {NULL, "simpipe",      NULL, "simpipe  - simulate pipe attributes",             TspiiSimulPipe   },
    {NULL, "simrs",        NULL, "simrs    - simulate RS attributes",               TspiiSimulRs     },
    {NULL, "simt1e1",      NULL, "simt1e1  - simulates t1e1 related hardware",      TspiiSimulT1E1   },
    {NULL, "slot",         NULL, "slot     - select slot# for future commands",     TspiiSlot        },
    {NULL, "unit",         NULL, "unit     - select unit# for future commands",     TspiiUnit        },
    {NULL, "nanocore",     NULL, "nanocore - select Nano Core for xc commands",     TspiiNanoCore    },
    {NULL, "update",       NULL, "update   - update action params",                 TspiiUpdateParam },

    // hw related cmds - sorted on 2nd column
    {"hw", "amm",        HWLP, "amm        - display attributes of an AMM card",    HwAmm               },
    {NULL, "ampolim",    NULL, "ampolim    - display attributes of a Single Slot AMP card", HwAmpOlim   },
    {NULL, "amposa",     NULL, "amposa     - Enhanced AMP (LIAM-E/LRAM-E/ELRAM-E) - OSA controller", HwAmpOsa},
    {NULL, "copm",       NULL, "copm       - display attributes of an COPM card",   HwCopm               },
    {NULL, "dcd",        NULL, "dcd        - display card data, module, FPGA, MATRIX", HwDcd             },
    {NULL, "dump",       NULL, "dump       - dump different hw values",             HwDump               },
    {NULL, "dumpOsc",    NULL, "dumpOsc    - display driver registers",             HwDumpOsc            },
    {NULL, "fwstatus",   NULL, "fwstatus   - status of programmable components",    HwFwStatus           },
    {NULL, "mappertest", NULL, "mappertest - tests traffic part of mapper fpga",    HwTestMapper         },
    {NULL, "ncm",        NULL, "ncm        - Core Module device menu",              HwNcm                },
    {NULL, "om",         NULL, "om         - optical module upgrade",               HwOM                 },
    {NULL, "pe",         NULL, "pe         - passive element",                      HwPe                 },
    {NULL, "pt",         NULL, "pt         - pilot tone controller",                HwPt                 },
    {NULL, "rcmm",       NULL, "rcmm       - RCMM controller and card attributes",  HwRcmm               },
    {NULL, "refresh",    NULL, "refresh    - controls periodic refresh of HW",      HwRefresh            },
    {NULL, "slave",      NULL, "slave      - update slave tdm fpga",                HwSlave              },
    {NULL, "nslave",     NULL, "nslave     - NCM slave ctrl menu",                  HwNcmSlave           },
    {NULL, "spur",       NULL, "spur       - display attributes of a SPUR card",    HwSpur               },
    {NULL, "storage",    NULL, "storage    - update Storage Prom ",                 HwStorage               },
    {NULL, "tdm",        NULL, "tdm        - update tdm related cfg/mon",           HwTdm                },
    {NULL, "vers",       NULL, "vers       - display versions of devices on card",  HwVers               },
    {NULL, "wss",        NULL, "wss        - RCMM-XD device menu",                  HwWss                }
};

TSPII_Spm8560TestMapperAction * TSPII_Spm8560TestMapperAction::ourInstance = NULL;

// TSPII_Spm8560TestMapperAction Code
////////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560TestMapperAction::TSPII_Spm8560TestMapperAction():
    myState(TEST_IDLE),
    myIterationCount(0),
    myOscIndex(0),
    myOchIndex(0),
    myMapperTestProcess(NULL)
{
    myIsDualOsc = CSPII_CardIF::GetInstance()->GetSubCardType() == OSC_DUAL;
    // Run Action every 100 ms
    myMapperTestProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, 100);

    for (int i=0; i<TSPII_MAX_OSC*2; i++)
    {
        myTTIResult[i] = false;
        for (int j=0; j<TSPII_SPM8560_NB_STATE_MAPPER_TEST; j++)
            for (int k=0; k<2; k++)
                for (int l=0; l<32; l++)
                    myResultTable[i][j][k][l] = false;
    }
}

////////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560TestMapperAction::~TSPII_Spm8560TestMapperAction()
{
    myMapperTestProcess->SuspendImmediate();
    delete myMapperTestProcess;
    delete ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560TestMapperAction * TSPII_Spm8560TestMapperAction::GetInstance()
{
    if (ourInstance == NULL) ourInstance = new TSPII_Spm8560TestMapperAction();
    return ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560TestMapperAction::Reset()
{
    myState = TEST_IDLE;
    myIterationCount = 0;
    myOscIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560TestMapperAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run method should not be called");
}

////////////////////////////////////////////////////////////////////////////////
FC_Object* TSPII_Spm8560TestMapperAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    TSPII_Spm8560TestMapperState aNextState;
    uint32 aTempCount=0;

    CT_G709Trace  aTxTrace("mySapi", "myDapi", "myUserTrace", 1);
    CT_G709Trace  aRxTrace;
    TSPII_Spm8560SubApplication & anSPM8560SubApp = TSPII_Spm8560SubApplication::GetSpecificInstance();

    switch (myState)
    {
    case TEST_IDLE:
        if (anSPM8560SubApp.GetOtsOH(myOscIndex+1) == NULL)
        {
            fc_cout << " Unable to retrieve TSPII region " << endl;
            fc_cout << " Aborting Test " << endl;
            aNextState = TEST_IDLE;
            myMapperTestProcess->SuspendImmediate();
        }
        else
        {
            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForcePMI(true);
            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].SetTxTTI(aTxTrace);
            aNextState = TEST_OTS_PMI;
        }
        break;
    case TEST_OTS_PMI:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetPMI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForcePMI(false);
            myIterationCount++;
            aNextState = TEST_OTS_PMI;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetPMI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForceBDIP(true);
            myIterationCount = 0;
            aNextState = TEST_OTS_BDIP;
        }
        break;
    case TEST_OTS_BDIP:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetBDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForceBDIP(false);
            myIterationCount++;
            aNextState = TEST_OTS_BDIP;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetBDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForceBDIO(true);
            myIterationCount = 0;
            aNextState = TEST_OTS_BDIO;
        }
        break;
    case TEST_OTS_BDIO:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetBDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].ForceBDIO(false);
            myIterationCount++;
            aNextState = TEST_OTS_BDIO;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetBDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForcePMI(true);
            myIterationCount = 0;
            aNextState = TEST_OMS_PMI;
        }
        break;
    case TEST_OMS_PMI:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetPMI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForcePMI(false);
            myIterationCount++;
            aNextState = TEST_OMS_PMI;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetPMI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceBDIP(true);
            myIterationCount = 0;
            aNextState = TEST_OMS_BDIP;
        }
        break;
    case TEST_OMS_BDIP:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetBDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceBDIP(false);
            myIterationCount++;
            aNextState = TEST_OMS_BDIP;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetBDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceBDIO(true);
            myIterationCount = 0;
            aNextState = TEST_OMS_BDIO;
        }
        break;
    case TEST_OMS_BDIO:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetBDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceBDIO(false);
            myIterationCount++;
            aNextState = TEST_OMS_BDIO;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetBDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceFDIP(true);
            myIterationCount = 0;
            aNextState = TEST_OMS_FDIP;
        }
        break;
    case TEST_OMS_FDIP:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetFDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceFDIP(false);
            myIterationCount++;
            aNextState = TEST_OMS_FDIP;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetFDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceFDIO(true);
            myIterationCount = 0;
            aNextState = TEST_OMS_FDIO;
        }
        break;
    case TEST_OMS_FDIO:
        if (myIterationCount == 0)
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetFDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].ForceFDIO(false);
            myIterationCount++;
            aNextState = TEST_OMS_FDIO;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOmsOH(myOscIndex+1)))[0].GetFDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][0] = !TSPII_DEFECT(aTempCount);

            myOchIndex = 0;
            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceOCI(true);
            myIterationCount = 0;
            aNextState = TEST_OCH_OCI;
        }
        break;
    case TEST_OCH_OCI:
        if (myOchIndex < 31)
        {
            if (myIterationCount == 0)
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetOCI();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceOCI(false);
                myIterationCount++;
                aNextState = TEST_OCH_OCI;
            }
            else
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetOCI();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = !TSPII_DEFECT(aTempCount);

                myOchIndex++;
                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceOCI(true);
                myIterationCount = 0;
                aNextState = TEST_OCH_OCI;
            }
        }
        else if (myOchIndex == 31)
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetOCI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceOCI(false);

            myOchIndex++;
            myIterationCount++;
            aNextState = TEST_OCH_OCI;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex-1].GetOCI();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex-1] = !TSPII_DEFECT(aTempCount);

            myOchIndex = 0;
            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIP(true);
            myIterationCount = 0;
            aNextState = TEST_OCH_FDIP;
        }
        break;
    case TEST_OCH_FDIP:
        if (myOchIndex < 31)
        {
            if (myIterationCount == 0)
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIP();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIP(false);
                myIterationCount++;
                aNextState = TEST_OCH_FDIP;
            }
            else
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIP();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = !TSPII_DEFECT(aTempCount);

                myOchIndex++;
                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIP(true);
                myIterationCount = 0;
                aNextState = TEST_OCH_FDIP;
            }
        }
        else if (myOchIndex == 31)
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIP(false);

            myOchIndex++;
            myIterationCount++;
            aNextState = TEST_OCH_FDIP;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex-1].GetFDIP();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex-1] = !TSPII_DEFECT(aTempCount);

            myOchIndex = 0;
            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIO(true);
            myIterationCount = 0;
            aNextState = TEST_OCH_FDIO;
        }
        break;
    case TEST_OCH_FDIO:
        if (myOchIndex < 31)
        {
            if (myIterationCount == 0)
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIO();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIO(false);
                myIterationCount++;
                aNextState = TEST_OCH_FDIO;
            }
            else
            {
                aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIO();
                // Update Result table
                myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = !TSPII_DEFECT(aTempCount);

                myOchIndex++;
                (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIO(true);
                myIterationCount = 0;
                aNextState = TEST_OCH_FDIO;
            }
        }
        else if (myOchIndex == 31)
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].GetFDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex] = TSPII_DEFECT(aTempCount);

            (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex].ForceFDIO(false);

            myOchIndex++;
            myIterationCount++;
            aNextState = TEST_OCH_FDIO;
        }
        else
        {
            aTempCount = (*(anSPM8560SubApp.GetOchOH(myOscIndex+1)))[(bbindex_t)myOchIndex-1].GetFDIO();
            // Update Result table
            myResultTable[myOscIndex][myState][myIterationCount][(bbindex_t)myOchIndex-1] = !TSPII_DEFECT(aTempCount);

            myTTIResult[myOscIndex] = ( ( (*(anSPM8560SubApp.GetOtsOH(myOscIndex+1)))[0].GetRxTTI() ) == aTxTrace );
            myOchIndex = 0;
            myIterationCount = 0;
            aNextState = TEST_IDLE;

            fc_cout << "-----------------------" << endl;
            if ( !myIsDualOsc || (myIsDualOsc && myOscIndex==1) )
            {
                myMapperTestProcess->Suspend();
                DisplayResults();
            }
            else
            {
                myOscIndex++;
            }
        }
        break;
    default:
        aNextState = TEST_IDLE;
        break;
    }

    myState = aNextState;
    return NULL;
}

void TSPII_Spm8560TestMapperAction::DisplayResults()
{
    int j;

    fc_cout << "-----------------------" << endl;

    for (int i=0; i<TSPII_MAX_OSC*2; i++)
    {
        if ((myIsDualOsc) || (!myIsDualOsc && i<1))
        {
            fc_cout << " Results OSC_" << i+1 << endl;
            fc_cout << " OTS TTI Test Result    \t\t"  << TSPII_TEST_OK_FAIL(myTTIResult[i]) << endl;
            for (j=1; j<TSPII_SPM8560_NB_STATE_MAPPER_TEST-3; j++)
            {
                fc_cout << TSPII_StateName[j] << " Defect     " ;
                fc_cout << "\tDetected: " << TSPII_TEST_OK_FAIL(myResultTable[i][j][0][0])
                        << "\tCleared:  " << TSPII_TEST_OK_FAIL(myResultTable[i][j][1][0]) << endl;
            }

            for (j=TSPII_SPM8560_NB_STATE_MAPPER_TEST-3; j<TSPII_SPM8560_NB_STATE_MAPPER_TEST; j++)
            {
                for (int k=0; k<32; k++)
                {
                    fc_cout << TSPII_StateName[j] << "_" << k+1 << " Defect    ";
                    fc_cout << "\tDetected: " << TSPII_TEST_OK_FAIL(myResultTable[i][j][0][k])
                            << "\tCleared:  " << TSPII_TEST_OK_FAIL(myResultTable[i][j][1][k]) << endl;
                }
            }
            fc_cout << "-----------------------" << endl;
        }
    }
}

TSPII_Spm8560TestMapperAction* TSPII_Spm8560TestMenu::myMapperAction = NULL;

///////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560TestMenu::TSPII_Spm8560TestMenu() :
TSPII_OscCommonTestMenu(CSPII_CardIF::GetInstance()->GetSlotId(), TSPII_MAX_OSC*2),
TSPII_ShelfTestMenu("")
{
    FC_CmdProcessor& cmdProcessor = *FC_CmdProcessor::GetShellInstance();
    cmdProcessor.FC_RegisterCommand(ourTspiiSpm8560MainMenu, sizeof(ourTspiiSpm8560MainMenu)/sizeof(ourTspiiSpm8560MainMenu[0]));
    myMapperAction = TSPII_Spm8560TestMapperAction::GetInstance();

    for (int j=0; j<17; j++)
        for (int k=0; k<2; k++)
            for (int i=0; i<100; i++)
                gTspiiCopmPowerMonitorTest[j][k][i] = 0;

}

///////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560TestMenu::~TSPII_Spm8560TestMenu()
{
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwDumpOsc(int argc, char** argv)
{
    if (argc >= 3 && strcmp(argv[2], "fpga") == 0)
    {
        TSPII_OscMapperFpgaDrv::GetInstance().DisplayContent(argc - 3, argv + 3);
    }
    else
    {
        fc_cout << "Usage: hw dumpOsc fpga..." << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwFwStatus(int argc, char ** argv)
{
    Devices::CardFirmwareStatus::GetInstance()->Menu (argc-2, argv+2);
    return FC_CmdProcessor::E_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwVers(int argc, char ** argv)
{
    Devices::CardFirmwareStatus::GetInstance()->HwVersions (argc-2, argv+2);
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwRefresh(int argc, char** argv)
{
    TSPII_Spm8560SubApplication & app = TSPII_Spm8560SubApplication::GetSpecificInstance();
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
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwTestMapper(int argc, char** argv)
{
    if (argc == 3)
    {
        if (strcmp(argv[2], "start") == 0)
        {
            if (myMapperAction->GetState() != TEST_IDLE)
            {
                fc_cout << " Restarting OSC Mapper test ... " << endl;
                myMapperAction->Reset();
            }
            fc_cout << " OSC Mapper test Action Waking Up ... " << endl;
            myMapperAction->GetProcess().WakeUp();
        }
        else if (strcmp(argv[2], "stop") == 0)
        {
            myMapperAction->GetProcess().SuspendImmediate();
            myMapperAction->Reset();
        }
        else
        {
            fc_cout << " Third argument must be [start|stop]" << endl;
        }
    }
    else
    {
        fc_cout << "Usage: hw mappertest [start|stop]" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// Test menu commands for an active LIAME, LRAME, ELRAME OSA control action
///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwAmpOsa(int argc, char** argv)
{
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active Enhanced AMP card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    TSPII_CntrlLxameOsaCtrlAction * osaCntrl = NULL;

    if (argc >= 4)
    {
        int slot = strtoul(argv[3], NULL, 0);
        osaCntrl = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(slot);
        FC_THROW_ERROR_IF(osaCntrl == NULL, FC_RuntimeError, "AMP OSA control action not found");
    }
    if (argc == 4 && argv[2][0] == 'c')
    {
        osaCntrl->ResetStats();
    }
    else if (argc == 4 && argv[2][0] == 'd')
    {
        osaCntrl->DisplayPower();
    }
    else if (argc == 5 && argv[2][0] == 'a' && strcmp(argv[4], "arm") == 0)
    {
        osaCntrl->ArmUpgradeSwitch();
    }
    else if (argc == 5 && argv[2][0] == 'a' && strcmp(argv[4], "disarm") == 0)
    {
        osaCntrl->DisarmUpgradeSwitch();
    }
    else if (argc == 5 && argv[2][0] == 'o' && strcmp(argv[4], "enable") == 0)
    {
        osaCntrl->SetOscTxControl(TSPII_OSC_TX_ENABLE);
    }
    else if (argc == 5 && argv[2][0] == 'o' && strcmp(argv[4], "disable") == 0)
    {
        osaCntrl->SetOscTxControl(TSPII_OSC_TX_DISABLE);
    }
    else if (argc == 5 && argv[2][0] == 'r')
    {
        osaCntrl->DisplayRawRegisters(argv[4]);
    }
    else if (argc == 4 && argv[2][0] == 's')
    {
        osaCntrl->DisplayStatus();
    }
    else if (argc == 5 && argv[2][0] == 't')
    {
        uint timeout = strtoul(argv[4], NULL, 0);
        osaCntrl->SetUpgradeSwitchArmingTimeout(timeout);
    }
    else if (argc == 5 && argv[2][0] == 'f')
    {
        osaCntrl->SetFilterThreshold(argv[4]);
    }
    else if (argc == 5 && argv[2][0] == 'k')
    {
        osaCntrl->SetFilterConstant(argv[4]);
    }
    else if ((argc == 5 && argv[2][0] == 'u') && (strcmp(argv[4], "sboadm") == 0))
    {
        TSPII_OscMapperFpgaCtrl::GetInstance().OptSetOpticalSwitchControl(1); // switch position A
    }
    else if ((argc == 5 && argv[2][0] == 'u') && (strcmp(argv[4], "ola") == 0))
    {
        TSPII_OscMapperFpgaCtrl::GetInstance().OptSetOpticalSwitchControl(0); // switch position B
    }
    else
    {
        fc_cout << "Usage: hw amposa a(rm-disarm)        [slot] <arm|disarm> \n"
                   "       hw amposa c(learstats)        [slot]\n"
                   "       hw amposa d(isplay power)     [slot]\n"
                   "       hw amposa f(ilter threshold)  [slot] [0.0 - 12.75]\n"
                   "       hw amposa k(filter constant)  [slot] [0.0-1.0]\n"
                   "       hw amposa o(sc transmit)      [slot] <enable|disable>\n"
                   "       hw amposa r(aw register dump) [slot] [0 or 1]\n"
                   "       hw amposa s(tatus display)    [slot]\n"
                   "       hw amposa t(imeout)           [slot] <00h-ffh seconds>\n"
                   "       hw amposa u(pgrade switch)    [slot] <ola|sboadm>" << endl;
    }

    return FC_CmdProcessor::E_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
//Commands when an active controller
///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwPt(int argc, char** argv)
{
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }


    TSPII_CntrlPilotToneCtrlAction * pt = NULL;
    if (argc >= 3)
    {
        int slot = strtoul(argv[2], NULL, 0);
        pt       = TSPII_Spm8560SubApplication::GetSpecificInstance().GetPilotToneControlAction(slot);
        FC_THROW_ERROR_IF(pt == NULL, FC_RuntimeError, "Pilot tone control action not found");
    }
    if (argc == 4 && argv[3][0] == 'c')
    {
        pt->ResetStats();
    }
    else if (argc == 4 && argv[3][0] == 'd')
    {
        pt->GetScheduler().Dump();
        pt->DisplayStats();
    }
    else if (argc == 5 && argv[3][0] == 't' && strcmp(argv[4], "on") == 0)
    {
        pt->GetScheduler().TraceOn();
        pt->TraceOn();
    }
    else if (argc == 5 && argv[3][0] == 't' && strcmp(argv[4], "off") == 0)
    {
        pt->GetScheduler().TraceOff();
        pt->TraceOff();
    }
    else
    {
        fc_cout << "Usage: hw pt <slot> c(learstats)\n"
                   "       hw pt <slot> d(isplaystats)\n"
                   "       hw pt <slot> t(race) <on|off>" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwPe(int argc, char** argv)
{
    unsigned int slot = 0;

    if (argv[2])
        slot = strtoul (argv[2], NULL, 0);

    if ((slot == 0) || (slot > NUMBER_OF_SLOTS_IN_SHELF))
        Lxame88Pne::Lxame88Pne::PrintUsage();
    else
        Lxame88Pne::Lxame88Pne::GetInstance(slot)->Menu(argc-2, argv+2);

    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwTdm(int argc, char** argv)
{
    bool printUsage=false;
    DEV_TdmCtrl& aTdmCtrl = DEV_TdmCtrl::GetInstance();
    uint32 slotNumTdm;
    uint32 frameNum;
    uint32 byteNum;
    bool aEnable=false;
    bool aDisable=false;
    bool aRxDisplay=false;
    bool aMarkAsTxOrRx=false;
    int  linecount=0;
    char line[80];

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if ( (argc>3) && (argc<8) )
    {
        if ( (strcmp(argv[2], "setrx")==0) && (argc>4) )
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));

            if (argc==5)
            {
                if (strcmp(argv[4], "en")==0)
                    aEnable = true;
                else if (strcmp(argv[4], "dis")==0)
                    aDisable = true;
                else
                    printUsage = true;
                if (aEnable)
                {
                    for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                        aTdmCtrl.SetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum), true);
                }
                else if (aDisable)
                {
                    for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                        aTdmCtrl.SetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum), false);
                }
            }
            else
            {
                frameNum = strtoul(argv[4], NULL, 0);
                if (strcmp(argv[5], "en")==0)
                    aEnable = true;
                else if (strcmp(argv[5], "dis")==0)
                    aDisable = true;
                else
                    printUsage = true;
                if (aEnable)
                {
                    aTdmCtrl.SetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum), true);
                }
                else if (aDisable)
                {
                    aTdmCtrl.SetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum), false);
                }
            }
        }
        else if ( (strcmp(argv[2], "settx")==0) && (argc>4) )
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));

            if (argc==5)
            {
                if (strcmp(argv[4], "en")==0)
                    aEnable = true;
                else if (strcmp(argv[4], "dis")==0)
                    aDisable = true;
                else
                    printUsage = true;
                if (aEnable)
                {
                    for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                        aTdmCtrl.SetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum), true);
                }
                else if (aDisable)
                {
                    for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                        aTdmCtrl.SetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum), false);
                }
            }
            else
            {
                frameNum = strtoul(argv[4], NULL, 0);
                if (strcmp(argv[5], "en")==0)
                    aEnable = true;
                else if (strcmp(argv[5], "dis")==0)
                    aDisable = true;
                else
                    printUsage = true;
                if (aEnable)
                {
                    aTdmCtrl.SetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum), true);
                }
                else if (aDisable)
                {
                    aTdmCtrl.SetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum), false);
                }
            }
        }
        else if ( argv[2][0] == 'd' && (argc>4) )
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[4], NULL, 0));
            aRxDisplay = (strcmp(argv[3], "rx")==0);
            if (argc>5)
            {
                frameNum = strtoul(argv[5], NULL, 0);
                if (aRxDisplay)
                    aMarkAsTxOrRx = aTdmCtrl.GetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum));
                else
                    aMarkAsTxOrRx = aTdmCtrl.GetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum));
            }

            FC_FmtFlags previousFlags = fc_cout.Flags();
            fc_cout.Setf(ios::hex, ios::basefield);

            if (argc==5)
            {
                for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                {
                    if (aRxDisplay)
                        aMarkAsTxOrRx = aTdmCtrl.GetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum));
                    else
                        aMarkAsTxOrRx = aTdmCtrl.GetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum));

                    fc_cout << " Tdm Bram Ctrl If Frame 0x" << frameNum
                            << "\n  Byte Number :\n";

                    for (byteNum=0; byteNum<TDM_NUMBER_BYTES_IN_BRAM_FRAME; byteNum++)
                    {
                        sprintf(line, " %6d-> 0x%02x %s ",
                                (int)byteNum,
                                (int)aTdmCtrl.ReadBramByte(slotNumTdm,
                                                           static_cast<uint8>(frameNum),
                                                           static_cast<uint8>(byteNum),
                                                           aRxDisplay),
                                TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                        fc_cout << line;
                        linecount++;
                        if (linecount == 4)
                        {
                            fc_cout << '\n';
                            linecount = 0;
                        }
                    }
                }
            }
            else if (argc==6)
            {
                for (byteNum=0; byteNum<TDM_NUMBER_BYTES_IN_BRAM_FRAME; byteNum++)
                {
                    sprintf(line, " %6d-> 0x%02x %s ",
                            (int)byteNum,
                            (int)aTdmCtrl.ReadBramByte(slotNumTdm,
                                                       static_cast<uint8>(frameNum),
                                                       static_cast<uint8>(byteNum),
                                                       aRxDisplay),
                            TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                    fc_cout << line;
                    linecount++;
                    if (linecount == 4)
                    {
                        fc_cout << '\n';
                        linecount = 0;
                    }
                }
            }
            else if (argc==7)
            {
                byteNum = strtoul(argv[6], NULL, 0);
                sprintf(line, " %6d-> 0x%02x %s ",
                        (int)byteNum,
                        (int)aTdmCtrl.ReadBramByte(slotNumTdm,
                                                   static_cast<uint8>(frameNum),
                                                   static_cast<uint8>(byteNum),
                                                   aRxDisplay),
                        TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                fc_cout << line;
            }

            fc_cout << endl;
            fc_cout.Flags(previousFlags);
        }
        else
            printUsage = true;

    }
    else
        printUsage=true;

    if (printUsage)
    {
        fc_cout << " hw tdm <settx|setrx> <slot> <frame> <en|dis> \n"
                << " hw tdm <settx|setrx> <slot> <en|dis> \n"
                << " hw tdm d(isplay) <rx|tx> <slot> \n"
                << " hw tdm d(isplay) <rx|tx> <slot> <frame> \n"
                << " hw tdm d(isplay) <rx|tx> <slot> <frame> <byte>\n" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwSlave(int argc, char** argv)
{
    bool printUsage=false;
    DEV_TdmCtrl& aTdmCtrl = DEV_TdmCtrl::GetInstance();
    uint32 slotNumTdm;
    uint32 slotNumPhysical;
    uint32 frameNum;
    uint32 byteNum;
    uint32 aValue;
    bool aRxDisplay=false;
    bool aDisplayCardSupported=false;
    bool aMarkAsTxOrRx=false;
    uint32 tempCode=0;
    int i=0;
    int  linecount=0;
    char line[80];

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if ( (argc>3) && (argc<8) )
    {
        if ( argv[2][0] == 'd' && (argc>4) )
        {
            slotNumTdm                  = Slot2Tdm(strtoul(argv[4], NULL, 0));
            TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm);
            if (strcmp(argv[3], "rx")==0)
                aRxDisplay = true;
            else if (strcmp(argv[3], "tx")==0)
                aRxDisplay = false;
            else
            {
                fc_cout << " hw slave display <rx|tx> ... " << endl;
                printUsage = true;
                return FC_CmdProcessor::E_SUCCESS;
            }
            if (argc>5)
            {
                frameNum = strtoul(argv[5], NULL, 0);
                if (aRxDisplay)
                    aMarkAsTxOrRx = aTdmCtrl.GetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum));
                else
                    aMarkAsTxOrRx = aTdmCtrl.GetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum));
            }

            FC_FmtFlags previousFlags = fc_cout.Flags();
            fc_cout.Setf(ios::hex, ios::basefield);

            if (argc==5)
            {
                for (frameNum=0; frameNum<TDM_NUMBER_FRAMES_PER_SLOT; frameNum++)
                {
                    if (aRxDisplay)
                        aMarkAsTxOrRx = aTdmCtrl.GetPacketRXEnable(slotNumTdm, static_cast<uint8>(frameNum));
                    else
                        aMarkAsTxOrRx = aTdmCtrl.GetPacketTXEnable(slotNumTdm, static_cast<uint8>(frameNum));
                    fc_cout << "Slave Tdm Ctrl -> Frame 0x" << frameNum << "\n";
                    tempCode = frameNum << TDM_FRAME_OFFSET_BYTE;
                    for (byteNum = 0; byteNum < TDM_NUMBER_BYTES_IN_BRAM_FRAME; byteNum++, tempCode++)
                    {
                        uint8 aValue = aRxDisplay ? aSlave.ReadByte((TDM_RX_Byte)tempCode) : aSlave.ReadByte((TDM_TX_Byte)tempCode);
                        sprintf(line, " %6d-> 0x%02x %s ", (int)byteNum, aValue, TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                        fc_cout << line;
                        linecount++;
                        if (linecount == 4)
                        {
                            fc_cout << '\n';
                            linecount = 0;
                        }
                    }
                }
            }
            else if (argc==6)
            {
                tempCode = frameNum << TDM_FRAME_OFFSET_BYTE;
                fc_cout << "Slave Tdm Ctrl -> Frame 0x" << frameNum << "\n";
                for (byteNum = 0; byteNum<TDM_NUMBER_BYTES_IN_BRAM_FRAME; byteNum++, tempCode++)
                {
                    uint8 aValue = aRxDisplay ? aSlave.ReadByte((TDM_RX_Byte)tempCode) : aSlave.ReadByte((TDM_TX_Byte)tempCode);
                    sprintf(line, " %6d-> 0x%02x %s ", (int)byteNum, aValue, TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                    fc_cout << line;
                    linecount++;
                    if (linecount == 4)
                    {
                        fc_cout << '\n';
                        linecount = 0;
                    }
                }
            }
            else if (argc==7)
            {
                byteNum = strtoul(argv[6], NULL, 0);

                // Display client interface (slave ctrl) only if needed
                tempCode     = (frameNum << TDM_FRAME_OFFSET_BYTE) | (byteNum & TDM_BYTE_NUMBER_MASK);
                uint8 aValue = aRxDisplay ? aSlave.ReadByte((TDM_RX_Byte)tempCode) : aSlave.ReadByte((TDM_TX_Byte)tempCode);
                sprintf(line, " %6d-> 0x%02x %s ", (int)byteNum, aValue, TDM_DISPLAY_TX_RX(aMarkAsTxOrRx));
                fc_cout << line;
            }
            fc_cout << endl;
            fc_cout.Flags(previousFlags);
        }
        else if (argc == 4 && ((strcmp(argv[2], "insert")==0) || (strcmp(argv[2], "init")==0)) )
        {
            aDisplayCardSupported = true;
        }
        else if (argc == 5 && (strcmp(argv[2], "insert")==0) )
        {
            slotNumPhysical = strtoul(argv[3], NULL, 0);
            slotNumTdm = Slot2Tdm(slotNumPhysical);
            CT_CardType card = static_cast<CT_CardType>(strtoul(argv[4], NULL, 0));
            for (i=0; i<TDM_NUM_CARD_SUPPORTED; i++)
            {
                if (card == TDM_SupportedCardTypes[i].cardType)
                {
                    TSPII_Spm8560SubApplication::GetSpecificInstance().SetCardPresent(slotNumPhysical, card);
                    aDisplayCardSupported = false;
                    i = TDM_NUM_CARD_SUPPORTED;
                }
                else
                    aDisplayCardSupported = true;
            }
        }
        else if (argc == 5 && (strcmp(argv[2], "init")==0) )
        {
            slotNumPhysical = strtoul(argv[3], NULL, 0);
            slotNumTdm = Slot2Tdm(slotNumPhysical);
            CT_CardType card = static_cast<CT_CardType>(strtoul(argv[4], NULL, 0));
            for (i=0; i<TDM_NUM_CARD_SUPPORTED; i++)
            {
                if (card == TDM_SupportedCardTypes[i].cardType)
                {
                    TSPII_Spm8560SubApplication::GetSpecificInstance().InitCard(slotNumPhysical, card);
                    aDisplayCardSupported = false;
                    i = TDM_NUM_CARD_SUPPORTED;
                }
                else
                    aDisplayCardSupported = true;
            }
        }
        else if (argc == 4 && (strcmp(argv[2], "coldstart")==0))
        {
            slotNumPhysical = strtoul(argv[3], NULL, 0);
            slotNumTdm = Slot2Tdm(slotNumPhysical);
            TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm).EnableHardReset( true );
        }
        // match / compare "remove" verses "r"
        else if (argc == 4 && (strcmp(argv[2],"remove")==0))
        {
            slotNumPhysical = strtoul(argv[3], NULL, 0);
            slotNumTdm = Slot2Tdm(slotNumPhysical);
            TSPII_Spm8560SubApplication::GetSpecificInstance().SetCardAbsent(slotNumPhysical);
        }
        else if ( argv[2][0] == 'w' && (argc==7) )
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));
            frameNum = strtoul(argv[4], NULL, 0);
            byteNum = strtoul(argv[5], NULL, 0);
            aValue = strtoul(argv[6], NULL, 0);
            TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm).
                WriteByte((TDM_TX_Byte)((frameNum << TDM_FRAME_OFFSET_BYTE) | (byteNum & TDM_BYTE_NUMBER_MASK)), (uint8)aValue);
        }
        else if ( (strcmp(argv[2], "trace")==0) && (argc==5) )
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));

            if (strcmp(argv[4], "en")==0)
                TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm).TraceOn();
            else if (strcmp(argv[4], "dis")==0)
                TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm).TraceOff();
            else
                printUsage = true;
        }
        else if (argc == 4 && argv[2][0] == 'a')
        {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));

            TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm).DisplayAttributes();
        }
        else
            printUsage = true;

        if (aDisplayCardSupported)
        {
            fc_cout << " Supported card numbers are the following : \n";
            for (i=0; i<TDM_NUM_CARD_SUPPORTED; i++)
            {
                   fc_cout << "  " << TDM_SupportedCardTypes[i].cardTypeName << " = "
                           << (int)(TDM_SupportedCardTypes[i].cardType) << "\n";
            }
            fc_cout << endl;
        }
    }
    else
        printUsage=true;

    if (printUsage)
    {   static const char *prefix = " hw slave ";
        fc_cout << prefix << "insert <slot> <cardtype>\n"
                << prefix << "init <slot> <cardtype>\n"
                << prefix << "remove <slot>\n"
                << prefix << "trace <slot> <en|dis> \n"
                << prefix << "w(rite) <slot> <frame> <byte> <value>\n"
                << prefix << "a(ttributes) <slot>\n"
                << prefix << "d(isplay) <rx|tx> <slot> \n"
                << prefix << "d(isplay) <rx|tx> <slot> <frame> \n"
                << prefix << "d(isplay) <rx|tx> <slot> <frame> <byte>\n"
                << prefix << "coldstart <slot>\n"
                << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwDump(int argc, char** argv)
{
   bool printUsage=false;
   DEV_BackplaneIfFpgaDrv& aTdmDrv = DEV_BackplaneIfFpgaDrv::GetInstance();
   int slotNumTdm;

   if(T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
   {
      fc_cout << "Command only supported on active controller card." << endl;
      return FC_CmdProcessor::E_SUCCESS;
   }

   if((argc==3) || (argc==4))
   {
      if((strcmp(argv[2], "slot")==0) && (argc==4))
      {
         slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));
         aTdmDrv.DisplayContent(DEV_TDM_SLOT_REG, slotNumTdm);
      }
      else if(strcmp(argv[2], "general")==0)
      {
         aTdmDrv.DisplayContent(DEV_TDM_GENERAL_REG);
      }
      else if(strcmp(argv[2], "bram")==0)
      {
         if(argc==4)
         {
            slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));
            aTdmDrv.DisplayContent(DEV_TDM_BRAM_SLOT_REG, slotNumTdm);
         }
         else
            aTdmDrv.DisplayContent(DEV_TDM_ALL_BRAM_REG);
      }
      else if(strcmp(argv[2], "all")==0)
      {
         aTdmDrv.DisplayContent(DEV_TDM_ALL_REG);
      }
      else if((strcmp(argv[2], "bd")==0) && (argc==4))
      {
         slotNumTdm = Slot2Tdm(strtoul(argv[3], NULL, 0));
         aTdmDrv.DisplayContent(DEV_TDM_BUF_DESC_REG, slotNumTdm);
      }
      else
      {
         printUsage=true;
      }
   }
   else
      printUsage = true;

   if(printUsage)
   {
        fc_cout << " hw dump <slot|general|bram|all|bd> \n"
      << " <slot> displays Bram and BufDesc of slot  \n" 
      << " general \n"
      << " bram \n"
      << " all \n"
      << " bd \n"
      << endl;
   }
   return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
unsigned int TSPII_Spm8560TestMenu::Slot2Tdm(unsigned int theSlot)
{
    if (theSlot<=0 || theSlot==17 || theSlot==18 || theSlot>19)
    {
        fc_cout << " Invalid slot number <1|16> + <19>.  Slot set to 1 " << endl;
        return 1;
    }
    return TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot);
}

///////////////////////////////////////////////////////////////////////////////
unsigned int TSPII_Spm8560TestMenu::Tdm2Slot(unsigned int theTdm)
{
    return TSPII_TdmSlaveCtrl::Tdm2Slot(theTdm);
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwAmm(int argc, char** argv)
{
    bool printUsage=false;
    uint32 slotNumTdm;

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if (argc==4 || argc==5)
    {
        uint32 aSlot = strtoul(argv[3], NULL, 0);
        if ( aSlot>0 && aSlot<=19 && aSlot!=17 && aSlot!=18)
        {
            if (argv[2][0] == 'd')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardAmpCtrl->Display();
            else if (argv[2][0] == 'o')
            {
                slotNumTdm                  = Slot2Tdm(aSlot);
                TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm);
                FC_BaseTimer aTimer1000(1000);
                // Remove recovery mode => put to load default mode
                aSlave.WriteByte(TDM_8_M2S_FR4_CTRL_SETTING, 0x13);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                // Reset Amp OM
                aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, true);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, false);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                aSlave.WriteByte(TDM_8_M2S_FR4_CTRL_SETTING, 0x23);
            }
            else if (argv[2][0] == 'r')
            {
                slotNumTdm                  = Slot2Tdm(aSlot);
                TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm);
                if (argc == 5)
                {
                    if (strcmp(argv[4], "on") == 0)
                        aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, true);
                    else if (strcmp(argv[4], "off") == 0)
                        aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, false);
                    else
                        printUsage = true;
                }
                else
                    printUsage = true;
            }
            else
                printUsage = true;
        }
        else
            printUsage = true;
    }
    else
        printUsage = true;


    if (printUsage)
    {
        fc_cout << " hw amm d(isplay) [slot] \n"
                << "        r(eset)   [slot] <on|off>\n"
                << "        o(orm)    [slot] \n" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwAmpOlim(int argc, char** argv)
{
    bool printUsage=false;
    uint32 slotNumTdm;

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if (argc==4 || argc==5 || argc==6)
    {
        uint32 aSlot = strtoul(argv[3], NULL, 0);
        if ( aSlot>0 && aSlot<=19 && aSlot!=17 && aSlot!=18)
        {
            if ((argc == 4) && (argv[2][0] == 'd'))
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardInputAmpOlimCtrl->Display();
            else if ((argc == 4) && (argv[2][0] == 'o'))
            {
                slotNumTdm                  = Slot2Tdm(aSlot);
                TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm);
                FC_BaseTimer aTimer1000(1000);
                // Remove recovery mode => put to load default mode
                aSlave.WriteByte(TDM_8_M2S_FR4_CTRL_SETTING, 0x13);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                // Reset Amp OM
                aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, true);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, false);
                aTimer1000.Start();
                while (!aTimer1000.IsExpired()){;}
                aSlave.WriteByte(TDM_8_M2S_FR4_CTRL_SETTING, 0x23);
            }            
            else if (argv[2][0] == 'm') // mid-stage loss
            {
                slotNumTdm                  = Slot2Tdm(aSlot);

                if ((argc == 5) && (strcmp(argv[4], "ogb") == 0)) // loss value is invalid
                {
                    TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardInputAmpOlimCtrl->ResetUserMidStageLoss();
                } 
                else if ((argc == 6) && (strcmp(argv[4], "user") == 0)) 
                {
                    int32 loss;
                    int count = sscanf(argv[5],"%d", &loss);
                    if ( count == 1 )
                    {
                        TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardInputAmpOlimCtrl->SetUserMidStageLoss(loss);
                    } 
                    else
                        printUsage = true;
                }
                else
                    printUsage = true;
            }
            else if ((argc == 5) && (argv[2][0] == 'r'))
            {
                slotNumTdm                  = Slot2Tdm(aSlot);
                TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(slotNumTdm);
                if (argc == 5)
                {
                    if (strcmp(argv[4], "on") == 0)
                        aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, true);
                    else if (strcmp(argv[4], "off") == 0)
                        aSlave.WriteBit(TDM_1_M2S_FR0_OM_RESET, false);
                    else
                        printUsage = true;
                }
                else
                    printUsage = true;
            }
            else
                printUsage = true;
        }
        else
            printUsage = true;
    }
    else
        printUsage = true;


    if (printUsage)
    {
        fc_cout << " hw ampolim d(isplay) [slot] \n"
                << "            m(sl)     [slot] <ogb|user> <0 - 255>\n"
                << "            r(eset)   [slot] <on|off>\n"
                << "            o(orm)    [slot] \n" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}
 
///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwCopm(int argc, char** argv)
{
    bool printUsage=false;
    int i;
    uint32 aTdmSlot;
    char line[100];

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if (argc==4)
    {
        uint32 aSlot = strtoul(argv[3], NULL, 0);
        if ( aSlot>0 && aSlot<=19 && aSlot!=17 && aSlot!=18)
        {
            aTdmSlot = Slot2Tdm(aSlot);
            TSPII_TdmSlaveCtrl & aSlave = TSPII_TdmSlaveCtrl::GetInstance(aTdmSlot);

            if (argv[2][0] == 'd')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardCOPMCtrl->Display();
            else if (argv[2][0] == 'p')
            {
                FC_BaseTimer aTimer(10);
  //              gTspiiCopmPowerMonitorTest[17][2][100];
                for (i=0; i<100; i++)
                {
                    gTspiiCopmPowerMonitorTest[aTdmSlot][0][i] = aSlave.ReadByte(TDM_8_S2M_FR6_POWER_MONITOR_PORT_0);
                    gTspiiCopmPowerMonitorTest[aTdmSlot][1][i] = aSlave.ReadByte(TDM_8_S2M_FR6_POWER_MONITOR_PORT_1);
                    aTimer.Start();
                    while (!aTimer.IsExpired()){;}
                }
            }
            else if (argv[2][0] == 'a')
            {
                fc_cout << " Sample#   Port0   Port1 \n";
                for (i=0; i<100; i++)
                {
                    sprintf(line, " %4d-> %8d %8d \n ", i,
                                                        (int)gTspiiCopmPowerMonitorTest[aTdmSlot][0][i],
                                                        (int)gTspiiCopmPowerMonitorTest[aTdmSlot][1][i]);
                    fc_cout << line;
                }
                fc_cout << endl;
            }
            else if (argv[2][0] == 'r')
            {
                for (i=0; i<100; i++)
                {
                    gTspiiCopmPowerMonitorTest[aTdmSlot][0][i] = 0;
                    gTspiiCopmPowerMonitorTest[aTdmSlot][1][i] = 0;
                }
            }
            else
                printUsage = true;
        }
        else
            printUsage = true;
    }
    else
        printUsage = true;

    if (printUsage)
    {
        fc_cout << " hw copm d(isplay)       [slot] \n"
                << "         p(ower_test)    [slot] \n"
                << "         a(rray_display) [slot] \n"
                << "         r(eset_array)   [slot] \n" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

/***********************************************************************
Name
    HwDcd - display card data (dumb cards only)

Synopsis
    FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwDcd (int argc, char** argv)

Description
    xx

Inputs
    argc -
    argv -

Returns
    n/a

----------------------------------------------------------------------*/
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwDcd(int argc, char** argv)
{
    static const char * msgCard = "Card ";
    static const char *msgUsage =
        "USAGE: hw dcd <slot>\n\tslot = 1 thru 16, 19, or * for all slots";

    MatrixDataRecord MatrixData; // from file
    MatrixDataRecord MatrixDataFpga;
    MatrixDataRecord CardData; // from card
    MatrixDataRecord CardDataFpga;

    char    Hab[3] = {'0','0',NULL}; // Hex ASCII Buffer
    char    *prefixSpaces = "    ";
    char    *prefix;
    uint32  aSlot;
    uint32  SlotLast;

    if (argc < 3)
    {
        fc_cout << msgUsage << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    // display all slots for "hw dcd *"
    if (*argv[2] == '*')
    {   // start with slot 1, and end with last slot
        aSlot = 1;
        SlotLast = NUMBER_OF_SLOTS_IN_SHELF;
    }
    else
    {   // display the specified slot, if valid;
        // slots 1-16 or 19; slot 17 and 18 are not allowed;
        aSlot = strtoul (argv[2], NULL, 0);
        if ((aSlot > NUMBER_OF_SLOTS_IN_SHELF)
        ||  (aSlot == 17)
        ||  (aSlot == 18))
        {
            aSlot = 0;
        }
        else
        {
            SlotLast = aSlot;
        }
    }

    if (aSlot == 0)
    {   // error; display usage and return
        fc_cout << msgUsage << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    // go through slots; single slot if so specified
    for (;aSlot <= SlotLast; aSlot++)
    {
        if ((aSlot == 17) || (aSlot == 18))
        {   // skip; these are controller slots;
            fc_cout << "Slot: " << aSlot << " bypassed." << endl;
            continue;
        }

        // get OPM data from card;
        // GetCardData() does a TSPII_TdmSlaveCtrl() lookup to fill in CardData
        CSPII_ShelfIF::GetInstance()->GetCardData (aSlot, &CardData);

        fc_cout << "Slot: " << aSlot << endl;
        if (CardData.CardID == 0)
        {
            fc_cout << " - does not have a card in it. (card type = 0)" << endl;
            continue;
        }

        // get FPGA data from card;
        // the GetCardData() call above does not obtain the following fields:
        // - CardHwVersion
        // - HwSwCompatibility
        // - PcbRevision
        // getting these fields now permits us to print 'em out below
        // with the card information;
        // note the ModuleHwVersionMajor is set to the jtag operation "upgrade"
        // for no reason other than to maintain tradition; it doesn't appear
        // to serve any real purpose here;
        CSPII_ShelfIF::GetInstance()->GetCardDataFpga (aSlot, &CardDataFpga);
        CardDataFpga.ModuleHwVersionMajor = 0x04; // FPGA_MODULE_HW_VERSION_UPGRADE

        // display card info
        fc_cout << msgCard << "ID: "
                << dec << int(CardDataFpga.CardID)
                << " (0x" << Uint8ToHexASCII((uint8)CardDataFpga.CardID, Hab) << ")"
                << " is "
                << CardTypeLabelTable[(CardDataFpga.CardID < CARD_TYPE_MAX ? CardDataFpga.CardID : 0)]
                << endl;
        fc_cout << msgCard << "SubCardType: "
                << dec << int(CardDataFpga.SubCardType)
                << " (0x" << Uint8ToHexASCII((uint8)CardDataFpga.SubCardType, Hab) << ")"
                << endl;

        // put the CardHwVersion, HwSw compatibility, and PcbRevision fields
        // into the CardData struct for display by DisplayMatrixDataRecord
        CardData.CardHwVersion = CardDataFpga.CardHwVersion;
        CardData.HwSwCompatibility[0] = CardDataFpga.HwSwCompatibility[0];
        CardData.HwSwCompatibility[1] = CardDataFpga.HwSwCompatibility[1];
        CardData.HwSwCompatibility[2] = CardDataFpga.HwSwCompatibility[2];
        CardData.HwSwCompatibility[3] = CardDataFpga.HwSwCompatibility[3];
        CardData.PcbRevision[0] = CardDataFpga.PcbRevision[0];
        CardData.PcbRevision[1] = CardDataFpga.PcbRevision[1];
        CardData.PcbRevision[2] = CardDataFpga.PcbRevision[2];
        CardData.PcbRevision[3] = CardDataFpga.PcbRevision[3];

        // display OPM data
        fc_cout << msgCard << "Module Data:" << endl;
        DisplayMatrixDataRecord ("    ", &CardData);

        // display matrix spec for OPM
        fc_cout << "MATRIX Module Spec:";
        if (CSPII_ShelfIF::GetInstance()->LookupMatrixData(&CardData, &MatrixData))
        {
            fc_cout << endl;
            DisplayMatrixDataRecord (prefixSpaces, &MatrixData);
            fc_cout << prefixSpaces << "Image File Name: "
                    << MatrixData.FileName
                    << endl;
        }
        else
        {   // no spec found for OPM in MATRIX file
            fc_cout << " Not Found." << endl;
        }

        // following input amps have a 2nd upgradeable entity
        if ((CardData.SubCardType != NUM_CHANNELS_88)
        && ((CardData.CardID == CARD_TYPE_LIAME)
        ||  (CardData.CardID == CARD_TYPE_LRAME)
        ||  (CardData.CardID == CARD_TYPE_ELRAME)))
        {
            AmpOpmDevice *anOpm = AmpOpmDevice::GetInstance (aSlot, AmpOpmDev::OPM_DEV_L2P);
            // Leave the vendor ID from earlier call to obtain OPM info...
            // TSPII_TdmSlaveCtrl & tdm =
            //          TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(aSlot));
            // CardData.ModuleVendorID = tdm.ReadByte(TDM_8_S2M_FR2_OM_VENDOR_NUMBER);
            // ModuleType is OPM, but not read.  Will have to hard code.
            CardData.ModuleType = anOpm->GetModuleID(); // get the Opm module ID
            CardData.ModuleHwVersionMajor = 0; // tdm.ReadByte(TDM_8_S2M_FR2_OM_HW_VERSION);
            CardData.ModuleHwVersionMinor = 0;
            // get the version of the 2nd upgradeable entity on this amp
            CardData.ModuleImageVersionMajor = anOpm->GetFwVersion();
            CardData.ModuleImageVersionMinor = 0;

            // display OPM info from card pertaining to 2nd upgradeable entity
            prefix = " Module 2 (OPM) ";
            fc_cout << msgCard << prefix << "Data:" << endl;
            DisplayMatrixDataRecord (prefixSpaces, &CardData);

            // display matrix spec for OPM (2nd upgradeable entity)
            fc_cout << "MATRIX" << prefix << "Spec:";
            if (CSPII_ShelfIF::GetInstance()->LookupMatrixData (&CardData, &MatrixData))
            {
                fc_cout << endl;
                DisplayMatrixDataRecord (prefixSpaces, &MatrixData);
                fc_cout << prefixSpaces << "Image File Name: "
                        << MatrixData.FileName
                        << endl;
            }
            else
            {   // no spec found for OPM in MATRIX file
                fc_cout << " Not Found." << endl;
            }

        } // end if (LIAME || LRAME || ELRAME)

        // display FPGA data from card obtained above
        fc_cout << msgCard << "FPGA Data:" << endl;
        DisplayMatrixDataRecord (prefixSpaces, &CardDataFpga);
        fc_cout << prefixSpaces << "New FPGA rev (frame 0, offset 0x0F): "
                << int(CardDataFpga.NewFpgaRev)
                << " (0x" << Uint8ToHexASCII (CardDataFpga.NewFpgaRev, Hab) << ")"
                << endl;

        // display fpga spec from MATRIX file
        fc_cout << "MATRIX FPGA Spec:";
        if (CSPII_ShelfIF::GetInstance()->LookupMatrixData (&CardDataFpga, &MatrixDataFpga))
        {
            fc_cout << endl;
            DisplayMatrixDataRecord (prefixSpaces, &MatrixDataFpga);
            fc_cout << prefixSpaces << "New FPGA rev (frame 0, offset 0x0F): "
                    << int(MatrixDataFpga.NewFpgaRev)
                    << " (0x" << Uint8ToHexASCII (MatrixDataFpga.NewFpgaRev, Hab) << ")"
                    << endl;
            fc_cout << prefixSpaces << "Image File Name: "
                    << MatrixDataFpga.FileName
                    << endl;
        }
        else
        {   // no spec found for FPGA in MATRIX file
            fc_cout << " Not Found." << endl;
        }

    } // end for aSlot

    return FC_CmdProcessor::E_SUCCESS;
}

//******************************************************************************
// Output is placed in the 2 sequential locations pointed to.
//******************************************************************************

char * TSPII_Spm8560TestMenu::Uint8ToHexASCII(uint8 what, char * where)
{
   char x;
   char * OriginalPointer = where;

   x = (what & 0xF0) >> 4;
   if(x > 0x09) x += '7'; else x += '0';
   *where = x;
   where++;
   x = what & 0x0F;
   if(x > 0x09) x += '7'; else x += '0';
   *where = x;

   return OriginalPointer;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560TestMenu::DisplayMatrixDataRecord (char *prefix, MatrixDataRecord *mdr)
{
    char Hab[3] = {'0','0',NULL}; // Hex ASCII Buffer

    fc_cout << prefix << "CardType: "
            << int(mdr->CardID)
            << " (0x" << Uint8ToHexASCII ((uint8)mdr->CardID, Hab) << ")"
            << endl;
    fc_cout << prefix << "SubCardType: "
            << int(mdr->SubCardType)
            << " (0x" << Uint8ToHexASCII ((uint8)mdr->SubCardType, Hab) << ")"
            << endl;
    fc_cout << prefix << "HW Rev: "
            << int(mdr->CardHwVersion)
            << " (0x" << Uint8ToHexASCII ((uint8)mdr->CardHwVersion, Hab) << ")"
            << endl;
    fc_cout << prefix << "Vendor ID: "
            << int(mdr->ModuleVendorID)
            << " (0x" << Uint8ToHexASCII ((uint8)mdr->ModuleVendorID, Hab) << ")"
            << endl;
    fc_cout << prefix << "Type: "
            << int(mdr->ModuleType)
            << " (0x" << Uint8ToHexASCII ((uint8)mdr->ModuleType, Hab) << ")"
            << endl;
    fc_cout << prefix << "Hardware Version: "
            << int(mdr->ModuleHwVersionMajor) << "." << int(mdr->ModuleHwVersionMinor)
            << " (0x"
                << Uint8ToHexASCII ((uint8)mdr->ModuleHwVersionMajor, Hab)
                << Uint8ToHexASCII ((uint8)mdr->ModuleHwVersionMinor, Hab)
            << ")"
            << endl;
    fc_cout << prefix << "Image Version: "
            << int(mdr->ModuleImageVersionMajor) << "." << int(mdr->ModuleImageVersionMinor)
            << " (0x"
                << Uint8ToHexASCII ((uint8)mdr->ModuleImageVersionMajor, Hab)
                << Uint8ToHexASCII ((uint8)mdr->ModuleImageVersionMinor, Hab)
            << ")"
            << endl;
    fc_cout << prefix << "Hw Sw Compatibility: "
            << "0x" << Uint8ToHexASCII(mdr->HwSwCompatibility[0], Hab)
            << Uint8ToHexASCII(mdr->HwSwCompatibility[1], Hab)
            << Uint8ToHexASCII(mdr->HwSwCompatibility[2], Hab)
            << Uint8ToHexASCII(mdr->HwSwCompatibility[3], Hab)
            << endl;
    fc_cout << prefix << "Pcb Revision: "
            << "0x" << Uint8ToHexASCII(mdr->PcbRevision[0], Hab)
            << Uint8ToHexASCII(mdr->PcbRevision[1], Hab)
            << Uint8ToHexASCII(mdr->PcbRevision[2], Hab)
            << Uint8ToHexASCII(mdr->PcbRevision[3], Hab)
            << endl;
    fc_cout << prefix << "Control Bits: "
            << "0x"
                << Uint8ToHexASCII ((uint8)mdr->ControlBits[0], Hab)
                << Uint8ToHexASCII ((uint8)mdr->ControlBits[1], Hab)
            << endl;

    return;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwOM(int argc, char** argv)
{
    static uint16 *             sLoad  = NULL;
    static TSPII_TdmSlaveCtrl * sSlave = NULL;

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if (argc == 3 && strcmp(argv[2], "display") == 0)
    {
        if (sLoad == NULL || sSlave == NULL)
        {
            fc_cout << "No firmware upgrade in progress." << endl;
        }
        else
        {
            fc_cout << "Slave slot                 = " << TSPII_TdmSlaveCtrl::Tdm2Slot(sSlave->GetMyTdmSlot()) << endl;
            fc_cout << "CONTROLS:" << endl;
            fc_cout << "    OM_FWDWNLD_SEQ_NB      = " << (int)(sSlave->ReadByte(TDM_8_M2S_BD_MASTER_CONTROL_DATA3) & 7)            << endl;
            fc_cout << "    OM_MOD_RST             = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_M2S_FR0_OM_RESET))                      << endl;
            fc_cout << "    OM_DWNLD_EN            = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_M2S_FR0_OM_DWNLD_EN))                   << endl;
            fc_cout << "STATUS:" << endl;
            fc_cout << "    OM_FWDWNLD_PREV_SEQ_NB = " << (int)((sSlave->ReadByte(TDM_8_S2M_FR0_OM_FW_UPGRADE_STATUS2) >> 4) & 7)   << endl;
            fc_cout << "    OM_FWDWNLD_SEQ_NB      = " << (int)(sSlave->ReadByte(TDM_8_S2M_FR0_OM_FW_UPGRADE_STATUS2) & 7)          << endl;
            fc_cout << "    OM_FW_DATA_REQ         = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_FR0_OM_FW_DATA_REQ))                << endl;
            fc_cout << "    OM_FW_DATA_RDY         = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_FR0_OM_FW_DATA_RDY))                << endl;
            fc_cout << "    OM_FW_DWNLD_FAILURE    = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_FR0_OM_FW_DWNLD_FAILURE))           << endl;
            fc_cout << "    OM_DWNLD_RDY           = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_BD_OM_DWNLD_RDY))                   << endl;
            fc_cout << "    OM_MOD_RDY             = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_BD_OM_MOD_RDY))                     << endl;
            fc_cout << "    OM_DWNLD_FAIL          = " << TEXT_ON_OFF(sSlave->ReadBit(TDM_1_S2M_BD_OM_DWNLD_FAIL))                  << endl;
            fc_cout << "Slave state                = " << TSPII_TdmSlaveCtrl::GetStateName(sSlave->GetMyCurrentState()) << endl;
            fc_cout << "Load size left             = " << sSlave->GetMyOMLoadSize() << endl;
            switch (sSlave->GetFwUpgradeStatus())
            {
            case TSPII_TdmSlaveCtrl::FW_UPGRADE_COMPLETED:
                fc_cout << "Upgrade status             = FW_UPGRADE_COMPLETED" << endl;
                free(sLoad);
                sLoad  = NULL;
                sSlave = NULL;
                fc_cout << "Load buffer released." << endl;
                break;
            case TSPII_TdmSlaveCtrl::FW_UPGRADE_IN_PROGRESS:
                fc_cout << "Upgrade status             = FW_UPGRADE_IN_PROGRESS" << endl;
                break;
            case TSPII_TdmSlaveCtrl::FW_UPGRADE_FAILED:
                fc_cout << "Upgrade status             = FW_UPGRADE_FAILED" << endl;
                free(sLoad);
                sLoad  = NULL;
                sSlave = NULL;
                fc_cout << "Load buffer released." << endl;
                fc_cout << "Restart upgrade or remove slave card to continue." << endl;
                break;
            default:
                fc_cout << "Upgrade status = ?" << endl;
            }
        }
    }
    else if (argc == 5 && strcmp(argv[2], "upgrade") == 0)
    {
        struct stat     buf;
        char            name[256];
        unsigned int    slot      = strtoul(argv[3], NULL, 0);
        if (sLoad != NULL || sSlave != NULL)
        {
            fc_cout << "Firmware upgrade already in progress." << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
        if (slot < 1 || 19 < slot || slot == 17 && slot == 18)
        {
            fc_cout << "Invalid slot: use 1-16, 19" << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
        sSlave = &TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(slot));
        strcpy(name, ACTIVE_LOAD_DIRECTORY);
        strcat(name + strlen(name), argv[4]);
        if (stat(name, &buf))
        {
            sSlave = NULL;
            fc_cout << "Cannot access file '" << name << "'" << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
        uint32   size   = buf.st_size;
        uint32   size32 = (size + 31) & (~31);
        fc_cout << "Opening file " << name << "..." << endl;
        FILE *   f      = fopen(name, FOPEN_MODE);
        if (f == NULL)
        {
            sSlave = NULL;
            fc_cout << "Failed to open file '" << name << "' (" << size << " bytes)" << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
        fc_cout << "Allocating memory..." << endl;
        sLoad = (uint16 *)malloc(size32);
        if (sLoad == NULL)
        {
            sSlave = NULL;
            fc_cout << "Failed to allocated load buffer (" << size32 << " bytes)" << endl;
            fclose(f);
            return FC_CmdProcessor::E_FAILURE;
        }
        fc_cout << "Reading file..." << endl;
        if (size != fread(sLoad, 1, size, f))
        {
            free(sLoad);
            sLoad  = NULL;
            sSlave = NULL;
            fc_cout << "Failed to read file '" << name << "' (" << size << " bytes)" << endl;
            fclose(f);
            return FC_CmdProcessor::E_FAILURE;
        }
        fclose(f);
        fc_cout << "Starting upgrade..." << endl;
        sSlave->FwUpgrade(sLoad, size32);
        fc_cout << "Upgrade started to '" << name << "' (" << size << " bytes) in slot " << slot << endl;
    }
    else
    {
        fc_cout << "Usage: hw om upgrade <slot> <filename>" << endl;
        fc_cout << "       hw om display" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//               Note: The wavelength/frequency plan on the Metconnex WSS
//               device is flipped from the 7100 standard.
//               The first channel in TSPII is the last channel on the
//               WSS device. the conversion takes place at the low level
//               RCMM controller.
//
//               Note: RCMM-2D support removed January 2006
///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwRcmm(int argc, char** argv)
{
    bool printUsage=false, cardInit=false;

    if ((argc >=4) && (argc <= 6))
    {
        CT_SlotId aSlot = static_cast<CT_SlotId>(strtoul(argv[3], NULL, 0));

        // Verify the RCMM slot selected
        if ((aSlot == RCMM_3)  || (aSlot == RCMM_6)  ||
            (aSlot == RCMM_7)  || (aSlot == RCMM_10) ||
            (aSlot == RCMM_11) || (aSlot == RCMM_14))
        {
            // Get the Optical Shelf Interface to determine the card type of the slave module
	        CT_ShelfId currentShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_OpticalShelfIf& theOsShelfIf = T6100_MainAppIf::Instance().GetOpticalShelf(currentShelfId);
            T6100_SlotIf* aSlotIf = &theOsShelfIf.GetOSSlotIf(aSlot);
            CT_PartNumber slaveMfgData = aSlotIf->GetCsmApp().GetCardStatusRegion()[0].GetPartNumber();
            CT_CardType slaveCardType = slaveMfgData.GetCardType();

            // "hw wss" is valid only for RCMM modules
            if ( slaveCardType != RCMM )
            {
                fc_cout << "sorry, slot does not contain an RCMM" << endl;
                return FC_CmdProcessor::E_FAILURE;            
            }

            // check to see if this RCMM is up and running
            cardInit = TSPII_Spm8560SubApplication::GetSpecificInstance().IsCardInitialized(aSlot);
            FC_THROW_ERROR_IF(cardInit == false, FC_RuntimeError, "RCMM Slot has NOT been initialized");

            if (argv[2][0] == 'c')
            {
                fc_cout << " RCMM-4D/8D controller status\n" <<  endl;

                if (TSPII_CardRcmmXDCmdQueue::RcmmXDCommandsEnabled(aSlot))
                    fc_cout << " Slot " << aSlot <<" is enabled\n" << endl;
                else
                    fc_cout << " Slot " << aSlot <<" is disabled\n" << endl;
            }
            else if (argv[2][0] == 'e') // Enable-Disable controller
            {
                if (argc >= 5)
                {
                    if (strcmp(argv[4], "on") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDCommands(aSlot, true);
                    }
                    else if (strcmp(argv[4], "off") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDCommands(aSlot, false);
                    }
                    else
                        printUsage = true;
                }
                else
                    printUsage = true;
            }
            else if (argv[2][0] == 'i') // IDPROM B:F1 and B:F2 info
            {
                TSPII_CardRcmmCtrl *theRcmmCtrl = TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardRcmmCtrl;
                FC_THROW_ERROR_IF(theRcmmCtrl == NULL, FC_RuntimeError, "invalid RCMM object pointer");
                theRcmmCtrl->DisplayIdpromData();
            }
            else if (argv[2][0] == 'm') // Message Statistics
            {
                if (argc == 5)
                {
                    if (strcmp(argv[4], "status") == 0)
                    {
                        fc_cout << "\n\nRCMM Message Transport Statistics"<< endl;

                        if (TSPII_CardRcmmXDCmdQueue::RcmmXDStatisticsEnabled(aSlot))
                            fc_cout << " Slot " << aSlot <<" is collecting stats\n" << endl;
                        else
                            fc_cout << " Slot " << aSlot <<" is not collecting stats\n" << endl;
                    }
                    else if (strcmp(argv[4], "on") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDStatistics(aSlot, true);
                    }
                    else if (strcmp(argv[4], "off") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDStatistics(aSlot, false);
                    }
                    else
                        printUsage = true;
                }
                else
                     printUsage = true;
            }
            else if (argv[2][0] == 't') // XC debug options
            {
                if (argc == 5)
                {
                    if (argv[4][0] == 's')
                    {
                        fc_cout << "RCMM XC slot " << int(aSlot) << " trace messages are " <<
                            TEXT_ON_OFF(TSPII_CardRcmmXDCmdQueue::RcmmXDTraceEnabled(aSlot)) << endl;
                    }
                    else if (strcmp(argv[4], "on") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDTrace(aSlot, true);
                    }
                    else if (strcmp(argv[4], "off") == 0)
                    {
                        TSPII_CardRcmmXDCmdQueue::EnableRcmmXDTrace(aSlot, false);
                    }
                    else
                        printUsage = true;
                }
                else
                    printUsage = true;
            }
            else if (argv[2][0] == 'w') // WSS Cfg Manager display
            {
                TSPII_CardRcmmXDCmdQueue *theRcmmCmdQue = TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardRcmmCmdQueue;
                FC_THROW_ERROR_IF(theRcmmCmdQue == NULL, FC_RuntimeError, "invalid RCMM object pointer");
                theRcmmCmdQue->DisplayWssCfg();
            }
            else if (argv[2][0] == 'x') // XC debug options
            {
                if (argc == 5)
                {
                    if (argv[4][0] == 's')
                    {
                        fc_cout << "RCMM XC slot " << int(aSlot) << " trace messages are " <<
                            TEXT_ON_OFF(TSPII_CntrlSlaveSlot::GetSpecificInstance(aSlot)->GetRcmmXcDebug()) << endl;
                    }
                    else if (strcmp(argv[4], "on") == 0)
                    {
                        TSPII_CntrlSlaveSlot::GetSpecificInstance(aSlot)->SetRcmmXcDebug(true);
                    }
                    else if (strcmp(argv[4], "off") == 0)
                    {
                        TSPII_CntrlSlaveSlot::GetSpecificInstance(aSlot)->SetRcmmXcDebug(false);
                    }
                    else
                        printUsage = true;
                }
                else
                     printUsage = true;
            }
            else
            {
                printUsage = true;
            }
        }
        else
        {
            // Invalid RCMM slot
            fc_cout << "Invalid RCMM slot: use 3, 6, 7, 10, 11 or 14" << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
    }
    else
    {
        printUsage = true;
    }

    if (printUsage)
    {
        fc_cout << "\tc(ontroller) status               [slot]\n"
                << "\te(nable) controller queue         [slot] <on|off>\n"
                << "\ti(dprom) compatibility field info [slot]\n"
                << "\tm(essage) statistics              [slot] <on|off|status>\n"
                << "\tt(race)                           [slot] <s|on|off>\n"
                << "\tw(c) RCMM Cfg Manager Display     [slot]\n"
                << "\tx(c) RCMM XC debug options        [slot] <s|on|off>\n"
                << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwStorage(int argc, char** argv)
{
#ifndef __SIMULATION__
    BspCommon_StoragePromCommand(argc, argv);
#endif

    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwSpur(int argc, char** argv)
{
    bool printUsage=false;
    uint32 aTdmSlot;

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    if (argc==4)
    {
        CT_SlotId aSlot = static_cast<CT_SlotId>(strtoul(argv[3], NULL, 0));

        // Verify the SPUR slot selected
        if ((aSlot == RCMM_3)  || (aSlot == RCMM_4)  ||
            (aSlot == RCMM_7)  || (aSlot == RCMM_8)  ||
            (aSlot == RCMM_10) || (aSlot == RCMM_11) ||
            (aSlot == RCMM_14) || (aSlot == RCMM_15))
        {
            // Get the Optical Shelf Interface to determine the card type of the slave module
	        CT_ShelfId currentShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_OpticalShelfIf& theOsShelfIf = T6100_MainAppIf::Instance().GetOpticalShelf(currentShelfId);
            T6100_SlotIf* aSlotIf = &theOsShelfIf.GetOSSlotIf(aSlot);
            CT_PartNumber slaveMfgData = aSlotIf->GetCsmApp().GetCardStatusRegion()[0].GetPartNumber();
            CT_CardType slaveCardType = slaveMfgData.GetCardType();

            // "hw spur" is invalid on a RCMM-4D/8D module
            if ((slaveCardType != CMM44) && (slaveCardType != RCMMS) && (slaveCardType != RCMMS44))
            {
                fc_cout << endl << "Invalid command: CMM SPUR module not installed" << endl;
                return FC_CmdProcessor::E_FAILURE;            
            }

            aTdmSlot = Slot2Tdm(aSlot);

            if (argv[2][0] == 'a')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardSPURCtrl->DisplaySpurAwg(slaveCardType);
            else if (argv[2][0] == 'c')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardSPURCtrl->DisplayClassAttributes(slaveCardType);
            else if (argv[2][0] == 'd')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardSPURCtrl->Display(slaveCardType);
            else if (argv[2][0] == 'f')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardSPURCtrl->ForceAwgFailure();
            else if (argv[2][0] == 's')
                TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[aSlot-1]->myCardSPURCtrl->ClearAwgStats();
            else
                printUsage = true;
        }
        else
            printUsage = true;
    }
    else
        printUsage = true;

    if (printUsage)
    {
        fc_cout << " hw spur a(wg display)       [slot] // display AWG failure status"   << endl;
        fc_cout << " hw spur c(lass display)     [slot] // display SPUR class attributes"<< endl;
        fc_cout << " hw spur d(isplay)           [slot] // display SPUR info" << endl;
        fc_cout << " hw spur f(orce) awg failure [slot] // toggle AWG DIAG failure" << endl;
        fc_cout << " hw spur s(tat) clear        [slot] // clear AWG statistics" << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwWss(int argc, char** argv)
{
    bool cardInit;

    if (argc >=4)
    {
        CT_SlotId aSlot = static_cast<CT_SlotId>(strtoul(argv[3], NULL, 0));

        // Verify the RCMM slot selected
        if ((aSlot == RCMM_3)  || (aSlot == RCMM_6)  ||
            (aSlot == RCMM_7)  || (aSlot == RCMM_10) ||
            (aSlot == RCMM_11) || (aSlot == RCMM_14))
        {
            // Get the Optical Shelf Interface to determine the card type of the slave module
            CT_ShelfId currentShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_OpticalShelfIf& theOsShelfIf = T6100_MainAppIf::Instance().GetOpticalShelf(currentShelfId);
            T6100_SlotIf* aSlotIf = &theOsShelfIf.GetOSSlotIf(aSlot);
            CT_PartNumber slaveMfgData = aSlotIf->GetCsmApp().GetCardStatusRegion()[0].GetPartNumber();
            CT_CardType slaveCardType = slaveMfgData.GetCardType();

            // "hw wss" is valid only for RCMM modules
            if ( slaveCardType == RCMM )
            {
                // check to see if this RCMM is up and running
                cardInit = TSPII_Spm8560SubApplication::GetSpecificInstance().IsCardInitialized(aSlot);
                FC_THROW_ERROR_IF(cardInit == false, FC_RuntimeError, "RCMM Slot has NOT been initialized");
                JdsuRoamSpecializedDev * theRcmm = JdsuRoamSpecializedDev::GetInstance(aSlot);
                FC_THROW_ERROR_IF(theRcmm == NULL, FC_RuntimeError, "invalid RCMM object pointer");
                if ( theRcmm != NULL )
                {
                    theRcmm->HwWss( argc, argv);
                }
            }
            else
            {
                fc_cout << "sorry, slot does not contain an RCMM" << endl;
                return FC_CmdProcessor::E_FAILURE;
            }
        }
        else
        {
            // Invalid RCMM slot
            fc_cout << "Invalid RCMM slot: use 3, 6, 7, 10, 11 or 14" << endl;
            return FC_CmdProcessor::E_FAILURE;
        }
    }
    else
    {
        JdsuRoamSpecializedDev::HwWssHelp();
    }

    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwDemux(int argc, char** argv)
{

    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false)
    {
        fc_cout << "Command only supported on active controller card." << endl;
        return FC_CmdProcessor::E_SUCCESS;
    }

    return FC_CmdProcessor::E_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::TspiiDrtrDisplay(int argc, char** argv)
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
			TSPII_CntrlDrtrHwDrvIf* theDrtrInstance = dynamic_cast <TSPII_CntrlDrtrHwDrvIf*> (&( (*(TSPII_Spm8560SubApplication::GetSpecificInstance().GetDrtr()) )[(bbindex_t)routerIndex-1]));
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
FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::TspiiDdltDisplay(int argc, char** argv)
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
		    TSPII_CntrlDdltHwDrvIf::GetInstance().DisplayLapdLinkageData(
                                static_cast<CT_ShelfId>(aShelf), 
                                static_cast<CT_SlotId>(aSlot),
                                static_cast<CT_PortId>(aPort), isSection);
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

FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwNcm(int argc, char** argv)
{
    bool cardInit = false;
    bool slotInit = false;

    // argv  0  1   2      3     4
    //       hw ncm <slot> <cmd> [arg] [arg] [args]
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == true)
    {
        // must have at least slot and cmd arguments.if (argc >=4)
        if (argc >=4)
        {
            uint32 aSlot = strtoul(argv[2], NULL, 0);

            CT_ShelfId theShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_OpticalShelfIf& theOsShelfIf = T6100_MainAppIf::Instance().GetOpticalShelf(theShelfId);
            T6100_SlotIf* aSlotIf = &theOsShelfIf.GetOSSlotIf(static_cast<CT_SlotId>(aSlot));
            CT_PartNumber mfgData = aSlotIf->GetCsmApp().GetCardStatusRegion()[0].GetPartNumber();
            CT_CardType cardType = mfgData.GetCardType();
            enumCARD_FAM aCardFam = CT_CardFamily(static_cast<enumCARD_TYPE>(cardType)).GetCardFamily();

            // Verify the slot selected contains an OLACM, or CCM_FAM, or CADM_FAM
            if ( (cardType == OLAIR) || (cardType == OLALR) || (cardType == OLAER) ||
                 (aCardFam == CARD_FAM_CCM) ||
                 (aCardFam == CARD_FAM_CADM) )
            {
                // check to see if this card is up and running
                cardInit = TSPII_Spm8560SubApplication::GetSpecificInstance().IsCardInitialized(aSlot);
                FC_THROW_ERROR_IF(cardInit == false, FC_RuntimeError, "Slot has NOT been initialized");
                TSPII_CardNanoCoreCtrl* slotPtr = TSPII_Spm8560SubApplication::GetSpecificInstance().GetNanoCoreCtrl(aSlot);
                if ( slotPtr == NULL )
                {
                    FC_THROW_ERROR(FC_RuntimeError, "Slot Controller has NOT been initialized");
                }
                else
                {
                    slotInit = true;
                }
            }
            else
            {
                fc_cout << "That slot does not contain a Core Module" << endl;
                return FC_CmdProcessor::E_FAILURE;
            }

            // a Core Module is in the slot and is initialized
            if ( (cardInit == true) && (slotInit == true) )
            {
                switch ( cardType )
                {
                case OLAIR:
                case OLALR:
                case OLAER:
                    NanoOlacmDevice::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                case CCMIR:
                case CCMLR:
                case CCMER:
                    NanoCcmDevice::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                case CCM88IR:
                case CCM88LR:
                case CCM88ER:
                    Ccm88Device::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                case OADM88IR:
                case OADM88LR:
                case OADM88ER:
                case OADM88IR8D:
                case OADM88LR8D:
                case OADM88ER8D:
                case OADM8DSIR:
                case OADM8DSLR:
                case OADM8DSER:
                    Oadm88Device::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                case DXOADM:
                    OadmDxDevice::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                case OADMF8IR:
                case OADMF8LR:
                    OadmF8Device::GetInstance(theShelfId, aSlot)->Menu(argc, argv);
                    break;
                default:
                    fc_cout << "Error: unknown card type: " << int(cardType) << endl;
                    break;
                }
            }
        }
        else
        {
            fc_cout << "hw ncm <slot> <cmd> [args]" << endl;
            fc_cout << "try \"hw ncm <slot> h\" for additional help (when a module is inserted)" << endl;
        }
    }
    else
    {
        fc_cout << "Command only supported on active controller card." << endl;
    }
    return FC_CmdProcessor::E_SUCCESS;
}

FC_CmdProcessor::STATUS TSPII_Spm8560TestMenu::HwNcmSlave(int argc, char** argv)
{
    bool cardInit = false;

    // argv  0  1     2      3     4
    //       hw slave <slot> <cmd> [arg] [arg] [args]
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == true)
    {
        // must have at least slot and cmd arguments.
        if (argc >=4)
        {
            uint32 aSlot = strtoul(argv[2], NULL, 0);

            CT_ShelfId theShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_OpticalShelfIf& theOsShelfIf = T6100_MainAppIf::Instance().GetOpticalShelf(theShelfId);
            T6100_SlotIf* aSlotIf = &theOsShelfIf.GetOSSlotIf(static_cast<CT_SlotId>(aSlot));
            CT_PartNumber mfgData = aSlotIf->GetCsmApp().GetCardStatusRegion()[0].GetPartNumber();
            CT_CardType cardType = mfgData.GetCardType();

#if 0
            // Verify the slot selected contains an OLACM or CCM
            if ( (cardType == OLAIR) || (cardType == OLALR) || (cardType == OLAER) ||
                 (cardType == CCMIR) || (cardType == CCMLR) || (cardType == CCMER) )
            {
                // check to see if this NCM is up and running
                cardInit = TSPII_Spm8560SubApplication::GetSpecificInstance().IsCardInitialized(aSlot);
                FC_THROW_ERROR_IF(cardInit == false, FC_RuntimeError, "Slot has NOT been initialized");
                TSPII_NcmSlaveCtrl::GetInstance(aSlot).Menu(argc-3, &argv[3]);
            }
            else
            {
                fc_cout << "That slot does not contain a Core Module" << endl;
                return FC_CmdProcessor::E_FAILURE;
            }
#else
            cardInit = true;
#endif

            // a Core Module is in the slot and is initialized
            if ( cardInit == true )
            {
                TSPII_NcmSlaveCtrl::GetInstance(aSlot).Menu(argc-3, &argv[3]);
                //TSPII_NcmSlaveCtrl::GetInstance(aSlot).DisplayAttributes();
            }
        }
        else
        {
            fc_cout << "hw slave <slot> <cmd>" << endl;
        }
    }
    else
    {
        fc_cout << "Command only supported on active controller card." << endl;
    }

    return FC_CmdProcessor::E_SUCCESS;
}


// eof
