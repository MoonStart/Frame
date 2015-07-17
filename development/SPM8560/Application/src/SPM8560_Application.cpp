/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : Telecom Services - SPM8560 application
 TARGET      : Platform independent
 AUTHOR      : Telecom Services
 DESCRIPTION : SPM8560 Application class implementation file.
--------------------------------------------------------------------------*/

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

//Optional module
#ifdef __SIMULATION__
#endif

#ifdef __TARGET__
#endif

#include <PII_Interrupt.h>
#include <PII_BbSystemLock.h>
#include <PII_DiskDevice.h>
#include <Blackboard/FC_Blackboard.h>

#include "SPM8560_Application.h"
#include "CARD_SwVersion.h"

#include <Facade/FC_FacadeApp.h>
#include <Facade/FC_FacadeAction.h>

#include <CommonTypes/CT_SystemIds.h>
#include <CR/CR_ControllerInfoRegion.h>
#include <CR/CR_ControllerRedundAppIf.h>
#include <CR/CR_ControllerRedundBaseApp.h>
#include <CR/CR_PersControlAction.h>

#include <CsPii/CSPII_AppParams.h>
#include <CsPii/CSPII_CardIF.h>
#include <CsPii_Imp/CSPII_CntrlCardIF.h>
#include <CsPii_Imp/CSPII_Spm8560Menu.h>
#include <CsPii_Imp/CSPII_SpmSysCfgParamImp.h>
#include <CsPii_Imp/CSPII_Spm8560Xfer.h>
#include <CsPii_Imp/CSPII_Spm8560ShelfImp.h>
#include <CsPii_Imp/CSPII_Spm8560SubSlotImp.h>

#include "Diag/DIAG_FailureReasons.h"
#include "CsPii_Imp/CSPII_Spm8560DiagCardImp.h"
#include <Diag/DIAG_Spm8560DiskLossOfFilesTest.h>
#include <Diag/DIAG_Spm8560PacketTest.h>
#ifdef __TARGET__
    #include <CsPii_Imp/NmPii_Spm8560DhcpCfgImp.h>
    #include <CsPii_Imp/CSPII_TaskMenu.h>
    #include <CsPii_Imp/CSPII_BspTestMenuSpm.h>
    #include <CsPii_Imp/CSPII_CFSecDrv.h>
    #include <CsPii/CSPII_ExceptionInfo.h>
    #include <crashHandlerUtils.h>
#endif

#include <Nm/Nm_ApplicationSpm8560.h>
#include <Nm/Nm_MainApplicationSpm8560.h>
#include <Nm/Nm_ApplicationDpm.h>
#include <Nm/Nm_MainApplicationDpm.h>
#include <Nm/Nm_InterfaceIPParamsRegion.h>
#include <Nm/Nm_Defs.h>
#include <Nm/Nm_MgmtGatewayStatusTask.h>

#include "Devices/HdpSpecializedDevice.h"

#include <T6100_CommonTags.h>
#include <T6100_OpticalShelfSlotIf.h>
#include <T6100_PortShelfSlotIf.h>
#include <T6100_OscIf.h>
#include <T6100_OpticalShelfIf.h>
#include <T6100_PortShelfIf.h>
#include <T6100_ControllerStatusRegion.h>
#include <T6100_ControllerIf.h>
#include <T6100_CardIf.h>
#include <T6100_DbCoordApp.h>
#include <T6100_DbAppMaster.h>
#include <T7100_TIDRegion.h>

#include <CUD/CUD_RmManager.h>
#include <CUD/CUD_Spm8560SubApplication.h>
#include <Diag/DIAG_Spm8560SubApplication.h>

#include <TsPii_Imp/TSPII_Spm8560SubApplication.h>
#include <TsPii_Imp/TSPII_DpmSubApplication.h>
#include <Devices/DEV_ShellTestMenu.h>

#include <SD/SD_ManageCardTypeAction.h>
#include <SD/SD_Client.h> // for SD_AddClientTestMenu() for DPMs

#include <cli/CLIApp.h>
#ifdef __TARGET__
#include <chaos_heap.h>
#include <PSMON_DpmTestMenu.h>
#include "UTIL_DiskDevice.h"
#endif

#include "PMXferTaskSpm.h"
#include "PMXferMenuCc.h"

using namespace std;
// Definitions for Memory Heap Manager
//
// Note that these will need to be 'tuned' for every new feature
// package based on heap memory requirement changes.
//
// Definitions are currently set to fulfill initialization needs
// plus slight overhead.  In the future, if more memory allocation
// operations (i.e. malloc, calloc, etc.) are funnelled through the
// memory heap manager, these definitions must change.

// The allocation below does not include Control Plane dynamic region
// objects for CALL, CONN and TL. For Control Plane, we will need:
//
// 256 byte buffers  - 21,000 (CALL 5000, CONN 15000, TL 1000)
// 512 byte buffers  -  1,000 (TL 1000)
// 1024 byte buffers - 20,000 (CALL 5000, CONN 15000)
//
// Use config 40 and 32 to benchmark memory needs

// Following is optimized for config 40 - 12 PS system
//
#define CHAOS_HEAP_NUM_4_BYTE_BUFFERS   (  3697145 )
#define CHAOS_HEAP_NUM_8_BYTE_BUFFERS   (  6062385 )
#define CHAOS_HEAP_NUM_16_BYTE_BUFFERS  ( 13565280 )
#define CHAOS_HEAP_NUM_32_BYTE_BUFFERS  ( 12798720 )
#define CHAOS_HEAP_NUM_64_BYTE_BUFFERS  (  7710340 )
#define CHAOS_HEAP_NUM_128_BYTE_BUFFERS (  5691240 )
#define CHAOS_HEAP_NUM_256_BYTE_BUFFERS (   781160 )
#define CHAOS_HEAP_NUM_512_BYTE_BUFFERS (   185253 )
#define CHAOS_HEAP_NUM_1k_BYTE_BUFFERS  (   233160 )
#define CHAOS_HEAP_NUM_2k_BYTE_BUFFERS  (    15555 )
#define CHAOS_HEAP_NUM_4k_BYTE_BUFFERS  (    59450 )
#define CHAOS_HEAP_NUM_8k_BYTE_BUFFERS  (    10155 )
#define CHAOS_HEAP_NUM_16k_BYTE_BUFFERS (       46 )
#define CHAOS_HEAP_NUM_32k_BYTE_BUFFERS (      400 )
#define CHAOS_HEAP_NUM_64k_BYTE_BUFFERS (       75 )

// Total heap mem = 2,822,743,660 based on buffer sizes above


// This allocation will be able to accommodate config 40 when in upgrade

// Following is optimized for config 32 - 8 PS system
//
#define CHAOS_HEAP_NUM_4_BYTE_BUFFERS_8PS   (  3557500 )
#define CHAOS_HEAP_NUM_8_BYTE_BUFFERS_8PS   (  4268880 )
#define CHAOS_HEAP_NUM_16_BYTE_BUFFERS_8PS  ( 13015300 )
#define CHAOS_HEAP_NUM_32_BYTE_BUFFERS_8PS  ( 10750930 )
#define CHAOS_HEAP_NUM_64_BYTE_BUFFERS_8PS  (  6611700 )
#define CHAOS_HEAP_NUM_128_BYTE_BUFFERS_8PS (  4552675 )
#define CHAOS_HEAP_NUM_256_BYTE_BUFFERS_8PS (   607980 )
#define CHAOS_HEAP_NUM_512_BYTE_BUFFERS_8PS (   248055 )
#define CHAOS_HEAP_NUM_1k_BYTE_BUFFERS_8PS  (   217995 )
#define CHAOS_HEAP_NUM_2k_BYTE_BUFFERS_8PS  (    12000 )
#define CHAOS_HEAP_NUM_4k_BYTE_BUFFERS_8PS  (    55655 )
#define CHAOS_HEAP_NUM_8k_BYTE_BUFFERS_8PS  (    11000 )
#define CHAOS_HEAP_NUM_16k_BYTE_BUFFERS_8PS (       55 )
#define CHAOS_HEAP_NUM_32k_BYTE_BUFFERS_8PS (      315 )
#define CHAOS_HEAP_NUM_64k_BYTE_BUFFERS_8PS (       60 )

// Total heap mem = 2,470,227,440 based on buffer sizes above





SPM8560_Application gApplication;
FC_BbAppIf* gApplicationPtr = &gApplication;

extern bool gActiveLedBlinkOverride;

#ifdef __TARGET__
extern "C" unsigned char PSMaxShelfSlotNumber;
extern "C" unsigned char PSMinLineCardSlotNumber;
extern "C" unsigned char PSMaxLineCardSlotNumber;
extern "C" unsigned char PSMinSWFCardSlotNumber;
extern "C" unsigned char PSMaxSWFCardSlotNumber;
extern "C" void InitPacketSubsystem(int, int, int, int, int, char *, uint64);
extern "C" API_RETCODE CheckRealDevelopmentJumper(void);
extern "C" int UTIL_MaintCntlWriteFile(MAINT_CNTL_INFO*);
extern "C" void startTlabEdrLogTask(int,int);
extern "C" void rawPartitionSetSectorMultiplier(uint32);
extern "C" int  MsrVerifyNoCriticalFilesLost(int *pRecoveryStatus, int StartupDPMFileVerify);
#endif

extern "C" void CLIStartListenThread(int);
extern "C" void CLICreateRcvDataMgr(void);
extern "C" void ftpServerInitStandby(void);
extern "C" void ftpServerInitPortShelf(void);
extern "C" void TlabNetDevAttach();

extern "C" void UTIL_print_bit64mac_address(unsigned long long macAddr64);

#ifdef WIN32
#include <CPIF/CPIF_TLim_cp_PipeApp.h>
#include <CPIF/CPIF_Callback_PipeApp.h>
#include <CPIF/CPIF_agccp_PipeApp.h>
#include <CPIF/CPIF_dbwrapper_PipeApp.h>
#include <CPIF/CPIF_RtrvAllTpPerFac_PipeApp.h>
#define DeleteFileA DeleteFile
#endif
#include "storagePromCommand.h"

#ifdef __TARGET__
extern "C" int cp_app_main();
extern "C" int cp_app_shutdown();
#endif

//##ModelId=37FBAFEA0113
SPM8560_Application::SPM8560_Application():
mySpmNmApp(NULL),
myDpmNmApp(NULL),
myBspTestMenu(NULL),
myNmMainApp(NULL),
myDevTestMenu(NULL),
myCliApp(NULL),
myTlimCpPipeApp(NULL),
myCpifCallbackPipeApp(NULL),
myCpifAgccpPipeApp(NULL),
myCpifDbwrapperPipeApp(NULL),
myCpifRtrvAllTpPerFacPipeApp(NULL),
myManageCardTypeAction(NULL),
myPMXferTask(NULL)
{
}

//##ModelId=37FBAFEA0112
SPM8560_Application::~SPM8560_Application()
{
}

//##ModelId=37FBAFEA00F4
void SPM8560_Application::DoCreateRegions(FC_Object* theObject)
{
    CT_SlotId  aSlotId  = CSPII_CardIF::GetInstance()->GetSlotId();

    CSPII_Spm8560ShelfImp::CreateInstance();
    CSPII_Spm8560SubSlotImp::CreateInstance();

    // Set the validity on the facade action
    FC_FacadeApp::Instance().GetFacadeAction().SetFacadeActionValidity( true );

    PII_BbSystemLock::Lock();

    CT_ControllerMode theCntrlMode = CSPII_CardIF::GetInstance()->GetControllerMode();
    CT_CardType theCardType = CSPII_CardIF::GetInstance()->GetCardType();
    CT_ShelfId theShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
    CSPII_SpmSysCfgParamImp::Instance(); //Get the instance to instantiate the card specific implementation

    // Initialize Heap Memory Manager.
    InitHeapMemMgr();

#ifdef VXWRKS
    TlabNetDevAttach();
#endif // VXWRKS

    // Create and init the Network Management application. This MUST be done
    // before the T6100 contexts get created
    if ( (theCardType == SPM8560) )
    {
        mySpmNmApp = new Nm_ApplicationSpm8560(GetBb());
        mySpmNmApp->InitIoStream();
    }
    else if ( (theCardType == DPM) )
    {
        myDpmNmApp = new Nm_ApplicationDpm(GetBb());
        myDpmNmApp->InitIoStream();
    }

    if (theShelfId != OPTICAL_SHELF_1)
    {
        if ( (theShelfId == OPTICAL_SHELF_2) || (theCntrlMode == MGMT_ACTIVE_MODE) )
        {
            //Turn off led blink override  on cards that do not require it for database application(packet or fc)
            gActiveLedBlinkOverride = false;
        }
    }

#ifdef __TARGET__
    //On target, instantiate True FFS direct access driver. Used for persistent region.
    // Don't worry about resource freeing as CSPII_FlashSecDrv is a Singleton.
    CSPII_FlashSecDrv::SetInstance(* (new CSPII_CFSecDrv()));
    
    //On SPM8560 set the raw partition sector access multipler to 16 (8k access). This is to get around a Compact Flash firmware issue
    //This is required on modules with a rev level less than rev J
    if ( (theCardType == SPM8560) )
    {
        CT_CardMfgInfo aIdProm;
        CSPII_CardIF::GetInstance()->GetMfgInfo(&aIdProm);
        if ((aIdProm.GetHWRevLevel()[0] < 'J'))
        {
            fc_cout << "Setting raw partition sector multiplier to 16" << endl;
            rawPartitionSetSectorMultiplier(16);
        }
    }
#endif

    //Create the singleton instances
    CSPII_SpmSysCfgParamImp::CreateInstance();

    //Call common init functions
    Controller_AppIf::CreateCommonCntrlApps(theObject);

    // If this is a DPM, set up the Configuration file Upload/Download
    //     manager.
    if (theCardType == DPM)
    {
        // Create Configuration Upload/Download Manager
        CUD_RmManager::GetInstance();
    }

#ifdef __TARGET__
    myBspTestMenu = new CSPII_BspTestMenuSpm();
    myBspTestMenu->Register();
    CSPII_TaskMenu();

    if (theCardType == DPM)
    {
        // Get current shelfand slot context
        T6100_ShelfIf* aShelfApp = NULL;
        T6100_SlotIf * aSlotApp = NULL;

        if(theShelfId == OPTICAL_SHELF_1)
        {
            // Get current shelf context
            aShelfApp = &GetOpticalShelf();

            // Get current slot context
            aSlotApp = &(static_cast<T6100_OpticalShelfIf*>(aShelfApp)->GetOSSlotIf(aSlotId));
        }
        else
        {
            // Get current shelf context
            aShelfApp = &GetPortShelf(theShelfId);

            // Get current slot context
            aSlotApp = &(static_cast<T6100_PortShelfIf*>(aShelfApp)->GetPSSlotIf(aSlotId));
        }
        /* Add Packet Subsystem Monitor to FC_Shell monitor */
        PSMON_DpmTestMenu::GetInstance(this, aSlotApp);
    }
#endif // __TARGET__

    CSPII_Spm8560AddMenu();

    // Add software version test menu.
    CARD_RegisterSwVersionCmd();
 
    // add client test menu here to permit its operation on simulator
    if (theCardType == DPM)
    {
        SD_AddClientTestMenu();
    }


#ifdef __TARGET__
    //Saving edr logs currently only supported on MS-1
    int saveEdrLogs = ((theShelfId == OPTICAL_SHELF_1) ? 1 : 0);
    int clearEdrLogs = ((CSPII_CardIF::GetInstance()->GetRestartSignature() == CONFIG_RST ) ? 1 : 0);
    //Always clear edr logs if on the first main shelf
    if (theShelfId == OPTICAL_SHELF_1)
    {
        clearEdrLogs = 1;
    }
    startTlabEdrLogTask(saveEdrLogs, clearEdrLogs);

    // Add crash log menu
    crashLogRegisterCmd();
#endif

#ifdef WIN32
    myTlimCpPipeApp = new CPIF_TLim_cp_PipeApp (NULL,"tlim_cp",true);
    myTlimCpPipeApp->initialize();
    myCpifCallbackPipeApp = new CPIF_Callback_PipeApp (NULL,"CPIF_Callback",false);
    myCpifCallbackPipeApp->initialize();
    myCpifAgccpPipeApp = new CPIF_agccp_PipeApp (NULL,"agccp",false);
    myCpifAgccpPipeApp->initialize();
    myCpifDbwrapperPipeApp = new CPIF_dbwrapper_PipeApp (NULL,"dbwrapper",false);
    myCpifDbwrapperPipeApp->initialize();
    myCpifRtrvAllTpPerFacPipeApp = new CPIF_RtrvAllTpPerFac_PipeApp (NULL,"RtrvAllTpPerFac",false);
    myCpifRtrvAllTpPerFacPipeApp->initialize();
#endif

    if (theShelfId == OPTICAL_SHELF_1)
    {
        CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

        if (aSubNodeCfg.GetNumberOfSides() == 8)
        {
            // in an 8d system, the final port shelf is numbered 15
            // otherwise, the final port shelf number is 13.
            Devices::HdpSpecializedDevice::GetInstance(Devices::HdpApi::Hdp::A).setLastPortShelfToMain();
            Devices::HdpSpecializedDevice::GetInstance(Devices::HdpApi::Hdp::B).setLastPortShelfToMain();
        }
        else
        {
            Devices::HdpSpecializedDevice::GetInstance(Devices::HdpApi::Hdp::A).setLastMainShelfToPort();
            Devices::HdpSpecializedDevice::GetInstance(Devices::HdpApi::Hdp::B).setLastMainShelfToPort();
        }
    }

}

void SPM8560_Application::CreateSpecificDiagApps( void )
{
    //Create diag apps here
    CT_ShelfId theShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();

    if (theShelfId == OPTICAL_SHELF_1 || theShelfId == OPTICAL_SHELF_2)
    {
        T6100_OscIf& theOscIf = T6100_MainAppIf::Instance().GetOpticalShelf(theShelfId).GetOSSlotIf(CSPII_CardIF::GetInstance()->GetSlotId()).GetOscIf();
        theOscIf.SetDiagApp( new DIAG_Spm8560SubApplication(theOscIf,  T6100_MainAppIf::Instance().GetOpticalShelf(theShelfId)) );
    }
    else
    {
        T6100_OscIf& theOscIf = T6100_MainAppIf::Instance().GetPortShelf(theShelfId).GetPSSlotIf(CSPII_CardIF::GetInstance()->GetSlotId()).GetOscIf();
        theOscIf.SetDiagApp( new DIAG_Spm8560SubApplication(theOscIf,  T6100_MainAppIf::Instance().GetPortShelf(theShelfId)) );
    }

    //fc_cout << "SPM8560_Application::CreateSpecificDiagApps: No diags implemented " << endl;
}


void SPM8560_Application::CreateSpecificCudApps( void )
{
    //Create Cud apps here
    CT_ShelfId theShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();


    T6100_OscIf& theOscIf = T6100_MainAppIf::Instance().GetPortShelf(theShelfId).GetPSSlotIf(CSPII_CardIF::GetInstance()->GetSlotId()).GetOscIf();

    theOscIf.SetCudApp( new CUD_Spm8560SubApplication(theOscIf,  T6100_MainAppIf::Instance().GetPortShelf(theShelfId)) );
}


void SPM8560_Application::CreateSpecificTsPiiApps(void)
{
    CT_ShelfId theShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
    if (theShelfId == OPTICAL_SHELF_1 || theShelfId == OPTICAL_SHELF_2)
    {
        SetTspiiApp(new TSPII_Spm8560SubApplication(GetOpticalShelf(theShelfId), *(Controller_AppIf::GetCntrlCardIf())));
    }
    else
    {
        //port shelf
        SetTspiiApp(new TSPII_DpmSubApplication(GetPortShelf(theShelfId), *(Controller_AppIf::GetCntrlCardIf())));
    }
}

void SPM8560_Application::CreateSpecificNmApps(void)
{
    CT_CardType theCardType = CSPII_CardIF::GetInstance()->GetCardType();
    // Insert the Network Management main application
    if ( (theCardType == SPM8560) )
    {
        myNmMainApp = new Nm_MainApplicationSpm8560(*this);
        SetNmApp(dynamic_cast<Nm_MainApplicationSpm8560*>(myNmMainApp));

        // Insert the Network Management card application
        mySpmNmApp->SetCardIf(myCntrlCardIf);
        mySpmNmApp->SetMainNmAppPtr(dynamic_cast<Nm_MainApplicationSpm8560*>(myNmMainApp));
        myCntrlCardIf->SetNmAppIf( *mySpmNmApp );
#ifdef __TARGET__
        NmPii_Spm8560DhcpCfgImp::CreateSpm8560DhcpCfgImpInstance();
#endif
    }
    else if (theCardType == DPM)
    {
        myNmMainApp = new Nm_MainApplicationDpm(*this);
        SetNmApp(dynamic_cast<Nm_MainApplicationDpm*>(myNmMainApp));

        // Insert the Network Management card application
        myDpmNmApp->SetCardIf(myCntrlCardIf);
        myDpmNmApp->SetMainNmAppPtr(dynamic_cast<Nm_MainApplicationDpm*>(myNmMainApp));
        myCntrlCardIf->SetNmAppIf( *myDpmNmApp );
#ifdef __TARGET__
        NmPii_Spm8560DhcpCfgImp::CreateSpm8560DhcpCfgImpInstance();
#endif
    }
}

void SPM8560_Application::DoCreateActions( FC_Object* theObject )
{
#ifdef __TARGET__
    int RecoveryStatus;
    int filesysRetCode;
    API_RETCODE rc;
 
    BspCommon_FixAutoBackplaneSetting();
#endif

    myManageCardTypeAction = new SD_ManageCardTypeAction();

    //Call base class
    Controller_AppIf::DoCreateActions(theObject);

    //Initialize persistence control
    CR_PersControlAction::Instance().AdjustPersReadStartAddress();

    myDevTestMenu = new DEV_ShellTestMenu();
    myDevTestMenu->DEV_AddTestMenu();

    CT_CardType theCardType = CSPII_CardIF::GetInstance()->GetCardType();
    if ( (theCardType == DPM) )
    {
        // Set the Number of Line Cards for the USS
#ifdef __TARGET__
        PSMaxShelfSlotNumber = 18;
        PSMinLineCardSlotNumber = 1;
        PSMaxLineCardSlotNumber = 16;
        PSMinSWFCardSlotNumber = 8;
        PSMaxSWFCardSlotNumber = 9;
#endif

        // Initialize the interworking between the Framework and Packet Services
        CSPII_XferInit();

        // DPM - Create, initialize and run the PM File Transfer Task
        myPMXferTask = new PMXferTaskCc();
        myPMXferTask->InitializeAndRun();
        PMXferMenuCc::Register();

#ifdef __TARGET__
        //Start the ftp server with guest access
        ftpServerInitPortShelf();
#endif

        // On an Active DPM, read the MAC pool information from the Backplane ID EEPROM,
        // store the information in the Controller Info region, and then initialize
        // Packet Services. The Backplane ID EEPROM cannot be read by the Standby DPM,
        // so it must wait for the MAC pool information to be transferred from the
        // Active DPM via the Controller Info region.

        if (CSPII_CntrlCardIF::GetInstance()->GetControllerMode() == MGMT_ACTIVE_MODE)
        {
            int mySlot;
            int isActiveController = 1;
            int isMatePresent = 1;
            CardIdProm_MfgInfo_t aMfgInfo;
            uint64 macAddr64;
            CT_CR_RegionId outputRegion;
            CT_ShelfId currentShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
            T6100_PortShelfIf& aPortShelfApp = GetPortShelf(currentShelfId);
            T6100_ControllerIf& myControllerContext = aPortShelfApp.GetControllerIf();
            CR_ControllerRedundAppIf* theAppIf = &(myControllerContext.GetControllerRedundAppIf());
            CR_ControllerRedundBaseApp* theBaseApp = dynamic_cast <CR_ControllerRedundBaseApp*>(theAppIf);
            int syncToMate = 1;    // Sync to active DPM on init?


#ifdef __SIMULATION__
            char   ShelfIdString[5];

            sprintf(ShelfIdString, "%02d", (int)CSPII_CardIF::GetInstance()->GetShelfId());
            string GuardFileName     = CUD_GUARD_FILE_NAME + ShelfIdString + ".tmp";
            string NewConfigFileName = CUD_ISS_CONFIG_FILE_NAME + ShelfIdString;
            string ConfigFileDir     = PII_DiskDevice::GetConfigDir();
#else
            string GuardFileName  = CUD_GUARD_FILE_NAME + ".tmp";
            string NewConfigFileName = CUD_ISS_CONFIG_FILE_NAME;
            string ConfigFileDir  = PII_DiskDevice::GetConfigDir();
#endif

            string guardFile = ConfigFileDir + GuardFileName;
            string newConfigFile = ConfigFileDir + NewConfigFileName;

            // Check for the Guard file used to flag Ping Pong Restore.
            if (PII_DiskDevice::IsAFile(guardFile))
            {
                // Check for the new Config File to be restored.
                if (PII_DiskDevice::IsAFile(newConfigFile))
                {
                    syncToMate = 0;   // Hold off synchronizing to mate module

                    // Load the configuration file for the ISS.
                    bool RestoreCompleted = CUD_RmConfigFileOp::InstallConfigFile( );

                    if (RestoreCompleted == false)
                    {
                        fc_cout << "SPM8560_Application::DoCreateActions(): Restore of iss.conf file failed on Install." << endl;
                    }
                }
                else
                {
                    fc_cout << "SPM8560_Application::DoCreateActions(): Restore of iss.conf file failed on init." << endl;
                }

                // Clean up the copy of the Config file.
                PII_DiskDevice::DeleteFile(newConfigFile);
            }

            mySlot = CSPII_CardIF::GetInstance()->GetSlotId();
            if (mySlot == SPM_1)
            {
                outputRegion = CT_CR_B;
            }
            else
            {
                outputRegion = CT_CR_A;
            }

            ShIdProm_EraseMemoryStructure(0);
            if (ShIdProm_GetMfgInfo(0, &aMfgInfo, &macAddr64) == 0)
            {
                if (strlen((char *)(&aMfgInfo.SerialNumber)) > 0)
                {
                    if(theBaseApp != NULL)
                    {
                        theBaseApp->GetControllerInfoRegion(outputRegion).SetBackplaneInfo(true,
                                                                                      (char *)&aMfgInfo.SerialNumber,
                                                                                      macAddr64);
                    }

                    if (CSPII_CntrlCardIF::GetInstance()->IsMatePresent() == false)
                    {
                        isMatePresent = 0;
                    }

#ifdef __TARGET__
                    API_RETCODE mntRetCode;
                    MAINT_CNTL_INFO shlfMaintCntlInfo;
                    int fileRetCode;

                    // Copy Shelf Serial Number and Shelf Number to maint cntl
                    // structure
                    fc_cout << "**** Shelf Number is " << (int)currentShelfId << endl;

                    fc_cout << "**** Shelf Serial Number is " << (char *)(&aMfgInfo.SerialNumber) << endl;

                    fc_cout << "**** Shelf Mac Addr is " << endl;
                    UTIL_print_bit64mac_address(macAddr64);

                    strcpy(shlfMaintCntlInfo.shelfSerialNumber, (char *)(&aMfgInfo.SerialNumber));
                    shlfMaintCntlInfo.shelfNumber = (int)currentShelfId;
                    shlfMaintCntlInfo.shelfMacAddr = (uint64)macAddr64;

                    // If Development Jumper is ON, Skip the maintcntl Checks
                    if (CheckRealDevelopmentJumper() == TRUE)
                    {
                        mntRetCode = API_RETCODE_SUCCESS;
                        fc_cout << "**** Development Jumper is ON" << endl;
                        // Write out new maintcntl.txt File
                        fileRetCode = UTIL_MaintCntlWriteFile(&shlfMaintCntlInfo);
                        if (fileRetCode != MAINT_CNTL_SUCCESS)
                        {
                            fc_cout << "**** Failed to Write Out maintcntl.txt File" << endl;
                            mntRetCode = API_RETCODE_FAILURE;
                        }
                        else
                        {
                            fc_cout << "**** maintcntl.txt File Updated" << endl;
                            mntRetCode = API_RETCODE_SUCCESS;
                        }
                    }
                    else
                    {
                        fc_cout << "**** Development Jumper is OFF" << endl;
                        // Check it against maintcntl.txt file
                        mntRetCode = UTIL_CheckMaintCntlInfo(&shlfMaintCntlInfo);
                    }

                    if (mntRetCode == API_RETCODE_SUCCESS)
                    {
                        /* check for loss of critical system files before packet starts */
                        /* has to be done before packet start so it can be latched */
                        /* once packet starts it will try to recover but the latched status */
                        /* will prevent the transfer of the damaged files to a the standby going active */
                        filesysRetCode = MsrVerifyNoCriticalFilesLost(&RecoveryStatus, TRUE);

                        /* if critical system files have been lost or corrupted */
                        if (filesysRetCode == FALSE)
                        {
                            fc_cout << "**** File System Loss of Files - Active file system recovery attempting... " << endl;

                            syncToMate = 0; // dont want to sync bad file

                            /* see if recovery was successful */
                            if (RecoveryStatus == SUCCESS)
                            {
                                /* alllow normal startup without files */
                                /* note: the fault handler will continue to return failure so the */
                                /* diag handlers will soon fault the card and take action */
                                /* by switching over if need be */
                                fc_cout << "**** File System Loss of Files - recovery succeeded but files lost! " << endl;
                            }
                            else
                            {
                                fc_cout << "**** File System Loss of Files - file system recovery failed! " << endl;
                            }
                            fc_cout << "**** File System Loss of Files - Active Waiting for Switch" << endl;

                            /* go ahead and init the pss but without sync to mate as file is corrupt */
                            /* since files or the file system are corrupt a switch will occur when diags run */
                            fc_cout << "Initializing packet subsystem on Active going standby without Sync" << endl;
                        }
                        else
                        {
                            /* go ahead and init the pss normally */
                            fc_cout << "Initializing packet subsystem on Active" << endl;
                        }
                        InitPacketSubsystem((int)CSPII_CardIF::GetInstance()->GetShelfId(),
                            mySlot,
                            isActiveController,
                            isMatePresent,
                            syncToMate,
                            (char *)(&aMfgInfo.SerialNumber),
                            macAddr64);

                        /* clear the alarm once packet starts */
                        DIAG_Spm8560PacketTest::GetInstance()->ReportFailure(DIAG_REASON_NO_FAILURE);

                        /* Create thread for PSMON monitor */
                        rc = PSMON_DpmTestMenu::PsMonSubmenuInit();
                        if ( rc != API_RETCODE_SUCCESS )
                        {
                            fc_cout << "InitPacketSubsystem: PsMonSubmenuInit() failed with rc = " << rc << endl;
                        }
                    } // maintcntl.txt SUCCESS
                    else
                    {
                        fc_cout << "**** Packet subsystem not started - Failed maintcntl.txt Check" << endl;
                        Restart(CONFIG_RST);
                    }
#endif // __TARGET__
                }
                else
                {
                    fc_cout << "**** Packet subsystem not started - No shelf serial number found" << endl;

                    /* set the alarm once packet fails to start */
                    DIAG_Spm8560PacketTest::GetInstance()->ReportFailure(DIAG_PACKET_DPM_FAILURE_ID);
                }
            }
            else
            {
                fc_cout << "**** Packet subsystem not started - Backplane ID EEPROM error" << endl;

                /* set the alarm once packet fails to start */
                DIAG_Spm8560PacketTest::GetInstance()->ReportFailure(DIAG_PACKET_DPM_FAILURE_ID);
            }

            // Clean up the copy of the Guard file.
            PII_DiskDevice::DeleteFile(guardFile);
#ifdef WIN32
        /*
         * Start the CLI cut-through listen thread for simulation.
         * When in simulation, a second SPM8560 application can be running
         * on the same PC as an SPM8560. This call will allow an SPM, at
         * run time, to act as a packet shelf.
         */
        CLIStartListenThread(1);
#endif

        }
#ifdef __TARGET__
        /* else standby node starting up */
        else 
        {
            /* check for loss of critical system files before packet starts */
            /* has to be done before packet start so it can be latched */
            /* once packet starts it will try to recover but the latched status */
            /* will prevent the transfer of the damaged files to a the standby going active */
            filesysRetCode = MsrVerifyNoCriticalFilesLost(&RecoveryStatus, TRUE);

            /* if critical system files have been lost or corrupted */
            if (filesysRetCode == FALSE)
            {
                fc_cout << "**** File System Loss of Files - Standby file system recovery... " << endl;

                /* see if recovery was successful */
                if (RecoveryStatus == SUCCESS)
                {
                    /* alllow normal startup without files */
                    /* note: the fault handler will continue to return failure so the */
                    /* diag handlers will soon fault the card and take action */
                    /* by switching over if need be */
                    fc_cout << "**** File System Loss of Files - file system recovery succeeded! " << endl;
                }
                else
                {
                    fc_cout << "**** File System Loss of Files - file system recovery failed! " << endl;
                }
            }
        }
#endif // __TARGET__
    }
    else
    {
#ifdef __TARGET__
        // This is main shelf SPM
        // set up the streams update for PS mon for the main shelf
        // if this is not done then printf_to_fc does not work correctly on main shelf
        rc = PSMON_DpmTestMenu::PsMonSubmenuInit();
        if ( rc != API_RETCODE_SUCCESS )
        {
            fc_cout << "InitPacketSubsystem: Main Shelf PsMonSubmenuInit() failed rc = " << rc << endl;
        }
#endif // __TARGET__
        if (CSPII_CardIF::GetInstance()->GetShelfId() == OPTICAL_SHELF_1)
        {
            if (CSPII_CntrlCardIF::GetInstance()->GetControllerMode() == MGMT_ACTIVE_MODE)
            {
                // Set cr pers control action as call back for db master action
                FC_DbApp& theDbApp = T6100_DbCoordApp::GetInstance().GetDbApp();
                theDbApp.SetCallback(&CR_PersControlAction::Instance());

                // Start the CLI Cut-through tasks
                // NOTE: CLI cut through should only run on MS-1 active controller
                CLIStartListenThread(0);
                CLICreateRcvDataMgr();
                myCliApp = new CLIApp();
#ifdef __TARGET__
                // Start up Control Plane
                cp_app_main();
                Nm_MgmtGatewayStatusTask::GetInstance()->StartMgmtGatewayStatusTask();
#endif

                // SPM - Create, initialize and run the PM File Transfer Task
                myPMXferTask = new PMXferTaskSPM();
                myPMXferTask->InitializeAndRun();
                PMXferMenuCc::Register();
            }
            else
            {
               //Start ftp server
#ifdef __TARGET__
               ftpServerInitStandby();
#endif
               // Set cr pers control action as call back for db replicant fsm
                FC_DbApp& theDbApp = myCntrlCardIf->GetAgentDbApp();
                theDbApp.SetCallback(&CR_PersControlAction::Instance());
            }
        }
        else
		{
			//Start ftp server on other shelves
#ifdef __TARGET__
			ftpServerInitStandby();
#endif
		}
    }
}

//--------------------------------------------------------------------------
void SPM8560_Application::DoDeactivateActions( FC_Object* theObject )
{
#ifdef __TARGET__
    CT_CardType theCardType = CSPII_CardIF::GetInstance()->GetCardType();
    if (theCardType != DPM)
    {
        if (CSPII_CntrlCardIF::GetInstance()->GetControllerMode() == MGMT_ACTIVE_MODE)
        {
            if (CSPII_CardIF::GetInstance()->GetShelfId() == OPTICAL_SHELF_1)
        {
        // Shut down the Control Plane
        cp_app_shutdown();
        }
        }
        // for both MS1 and MS15 call TSPII_CntrlSlaveSlot to shutdown
        // TSPII actions for the slot.
        TSPII_Spm8560SubApplication::GetSpecificInstance().SuspendSlaveSlotActions();
    }
#endif

    // Call base class operation
    Controller_AppIf::DoDeactivateActions(theObject);
}

//--------------------------------------------------------------------------
void SPM8560_Application::DoDeleteRegions( FC_Object* theObject )
{            
    // Don't forget to let Controller_AppIf do its freeing too.
    
    // Release the base class first as some of the attributes owned
    // by us, the derived class, is passed down to the base class
    // and referenced by the base class. If we should release those
    // attributes first then, the base class would reference an invalid
    // address when it gets down to its freeing of resources.
    Controller_AppIf::DoDeleteRegions( theObject );
    
    // Free up resources allocated in DoCreateRegions   
    if (mySpmNmApp)
    {
        delete mySpmNmApp;
        mySpmNmApp = NULL;
    }
    
    if (myDpmNmApp)
    {
        delete myDpmNmApp;
        myDpmNmApp = NULL;
    }    
    
    if (myBspTestMenu)
    {
        delete myBspTestMenu;
        myBspTestMenu = NULL;
    }    
    
    if (myNmMainApp)
    {
        delete myNmMainApp;
        myNmMainApp = NULL;
    }    
    
    if (myTlimCpPipeApp)
    {
        delete myTlimCpPipeApp;
        myTlimCpPipeApp = NULL;
    }
    
    if (myCpifCallbackPipeApp)
    {
        delete myCpifCallbackPipeApp;
        myCpifCallbackPipeApp = NULL;
    }    
    
    if (myCpifAgccpPipeApp)
    {
        delete myCpifAgccpPipeApp;
        myCpifAgccpPipeApp = NULL;
    }    
    
    if (myCpifDbwrapperPipeApp)
    {
        delete myCpifDbwrapperPipeApp;
        myCpifDbwrapperPipeApp = NULL;
    }    

    if (myCpifRtrvAllTpPerFacPipeApp)
    {
        delete myCpifRtrvAllTpPerFacPipeApp;
        myCpifRtrvAllTpPerFacPipeApp = NULL;
    }
}

//--------------------------------------------------------------------------
void SPM8560_Application::DoDeleteActions( FC_Object* theObject )
{
    // Free up resources allocated in DoCreateActions
    
    if (myDevTestMenu)
    {
        delete myDevTestMenu;
        myDevTestMenu = NULL;
    }
    
    if (myCliApp)
    {
        delete myCliApp;
        myCliApp = NULL;
    }
        
    if (myManageCardTypeAction)
    {
    delete myManageCardTypeAction;
    myManageCardTypeAction = NULL;
    }

    if (myPMXferTask)
    {
        myPMXferTask->DeletePMXfer();
        myPMXferTask = NULL;
    }

    //Call base class operation
    Controller_AppIf::DoDeleteActions( theObject );
}

void SPM8560_Application::Restart(RESTART_TYPE theRestartType)
{
    //Call base class implementation to continue restart procedure
    T6100_MainAppIf::Restart(theRestartType);
}


//
// Initialize Heap Memory Manager
//--------------------------------------------------------------------------
void SPM8560_Application::InitHeapMemMgr(void)
{
#ifdef __TARGET__
    //DPM is not using heap mgr for now
    if (CSPII_CardIF::GetInstance()->GetCardType() == SPM8560)
    {
        CHAOS_Heap_c::Initialize();


        CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
        if ( aSubNodeCfg.GetNumberOfPortShelf() > 8 )
        {
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_4,   CHAOS_HEAP_NUM_4_BYTE_BUFFERS   );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_8,   CHAOS_HEAP_NUM_8_BYTE_BUFFERS   );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_16,  CHAOS_HEAP_NUM_16_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_32,  CHAOS_HEAP_NUM_32_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_64,  CHAOS_HEAP_NUM_64_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_128, CHAOS_HEAP_NUM_128_BYTE_BUFFERS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_256, CHAOS_HEAP_NUM_256_BYTE_BUFFERS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_512, CHAOS_HEAP_NUM_512_BYTE_BUFFERS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_1K,  CHAOS_HEAP_NUM_1k_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_2K,  CHAOS_HEAP_NUM_2k_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_4K,  CHAOS_HEAP_NUM_4k_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_8K,  CHAOS_HEAP_NUM_8k_BYTE_BUFFERS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_16K, CHAOS_HEAP_NUM_16k_BYTE_BUFFERS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_32K, CHAOS_HEAP_NUM_32k_BYTE_BUFFERS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_64K, CHAOS_HEAP_NUM_64k_BYTE_BUFFERS );
        }
        else
        {
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_4,   CHAOS_HEAP_NUM_4_BYTE_BUFFERS_8PS   );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_8,   CHAOS_HEAP_NUM_8_BYTE_BUFFERS_8PS   );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_16,  CHAOS_HEAP_NUM_16_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_32,  CHAOS_HEAP_NUM_32_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_64,  CHAOS_HEAP_NUM_64_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_128, CHAOS_HEAP_NUM_128_BYTE_BUFFERS_8PS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_256, CHAOS_HEAP_NUM_256_BYTE_BUFFERS_8PS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_512, CHAOS_HEAP_NUM_512_BYTE_BUFFERS_8PS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_1K,  CHAOS_HEAP_NUM_1k_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_2K,  CHAOS_HEAP_NUM_2k_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_4K,  CHAOS_HEAP_NUM_4k_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_8K,  CHAOS_HEAP_NUM_8k_BYTE_BUFFERS_8PS  );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_16K, CHAOS_HEAP_NUM_16k_BYTE_BUFFERS_8PS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_32K, CHAOS_HEAP_NUM_32k_BYTE_BUFFERS_8PS );
            CHAOS_Heap_c::ConfigPool( CHAOS_Heap_c::Byte_64K, CHAOS_HEAP_NUM_64k_BYTE_BUFFERS_8PS );
        }

        CHAOS_Heap_c::Enable();
        CHAOS_Heap_c::CreateTestMenu();
    }
#endif
}

#ifdef VXWORKS67
extern "C"
{
    long double ldexpl(long double x, int exp)
    {
        return x*(2^exp);
    }
}
#endif

