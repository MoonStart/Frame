/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Tspii
 TARGET   :     All.
 AUTHOR   :     14 december 2001, Eric Bernier
 DESCRIPTION:   Tspii Sub-application base class of main context.
--------------------------------------------------------------------------*/

#ifndef TSPII_SUBAPPLICATION_H
#define TSPII_SUBAPPLICATION_H

#include <AppFramework/FC_BbApp.h>
#include <TsPii/TSPII_Region.h>

class TSPII_UpdateAction;

// UNIT definition
const unsigned int TSPII_DONT_CARE   = 0;
const unsigned int TSPII_LINE_SIDE   = 1;
const unsigned int TSPII_PORT_SIDE   = 2;
const unsigned int TSPII_P2L         = 1;
const unsigned int TSPII_L2P         = 2;
const unsigned int TSPII_P2L_A_SIDE  = 1;
const unsigned int TSPII_P2L_B_SIDE  = 2;
const unsigned int TSPII_RX          = 1;
const unsigned int TSPII_TX          = 2;
const unsigned int TSPII_OSC1        = 1;
const unsigned int TSPII_OSC2        = 2;
const unsigned int TSPII_OSC3        = 3;
const unsigned int TSPII_OSC4        = 4;
const unsigned int TSPII_OSC5        = 5;
const unsigned int TSPII_OSC6        = 6;
const unsigned int TSPII_PUMP1       = 1;
const unsigned int TSPII_PUMP2       = 2;
const unsigned int TSPII_PUMP3       = 3;
const unsigned int TSPII_PUMP4       = 4;
const unsigned int TSPII_PRIMARY_A   = 1;
const unsigned int TSPII_SECONDARY_B = 2;
const unsigned int TSPII_OSA_P2L     = 1;
const unsigned int TSPII_OSA_L2P     = 2;
const unsigned int TSPII_DCCL_SECTION= 1;
const unsigned int TSPII_DCCL_LINE   = 2;
const unsigned int TSPII_BACKPLANE   = 3;
const unsigned int TSPII_OCH_P2L     = 0;
const unsigned int TSPII_OCH_L2P     = 1;
const unsigned int TSPII_OMS_P2L     = 2;
const unsigned int TSPII_OMS_L2P     = 3;

// UNIT definitions for modules with multiple
// interfaces on line side and port side.
// The number scheme is 1-based to be consistent with
// TSPII_LINE_SIDE and TSPII_PORT_SIDE above.
const unsigned int TSPII_LINE_SIDE_0  = 1;
const unsigned int TSPII_LINE_SIDE_1  = 2;
const unsigned int TSPII_LINE_SIDE_2  = 3;
const unsigned int TSPII_LINE_SIDE_3  = 4;
const unsigned int TSPII_LINE_SIDE_4  = 5;
const unsigned int TSPII_LINE_SIDE_5  = 6;
const unsigned int TSPII_LINE_SIDE_6  = 7;
const unsigned int TSPII_LINE_SIDE_7  = 8;
const unsigned int TSPII_LINE_SIDE_8  = 9;
const unsigned int TSPII_LINE_SIDE_9  = 10;
const unsigned int TSPII_LINE_SIDE_10 = 11;
const unsigned int TSPII_LINE_SIDE_11 = 12;
const unsigned int TSPII_LINE_SIDE_12 = 13;
const unsigned int TSPII_LINE_SIDE_13 = 14;
const unsigned int TSPII_LINE_SIDE_14 = 15;
const unsigned int TSPII_LINE_SIDE_15 = 16;

const unsigned int TSPII_PORT_SIDE_0  = 17;
const unsigned int TSPII_PORT_SIDE_1  = 18;
const unsigned int TSPII_PORT_SIDE_2  = 19;
const unsigned int TSPII_PORT_SIDE_3  = 20;
const unsigned int TSPII_PORT_SIDE_4  = 21;
const unsigned int TSPII_PORT_SIDE_5  = 22;
const unsigned int TSPII_PORT_SIDE_6  = 23;
const unsigned int TSPII_PORT_SIDE_7  = 24;
const unsigned int TSPII_PORT_SIDE_8  = 25;
const unsigned int TSPII_PORT_SIDE_9  = 26;
const unsigned int TSPII_PORT_SIDE_10 = 27;
const unsigned int TSPII_PORT_SIDE_11 = 28;
const unsigned int TSPII_PORT_SIDE_12 = 29;
const unsigned int TSPII_PORT_SIDE_13 = 30;
const unsigned int TSPII_PORT_SIDE_14 = 31;
const unsigned int TSPII_PORT_SIDE_15 = 32;
const unsigned int TSPII_PORT_SIDE_16 = 33;
const unsigned int TSPII_PORT_SIDE_17 = 34;
const unsigned int TSPII_PORT_SIDE_18 = 35;
const unsigned int TSPII_PORT_SIDE_19 = 36;
const unsigned int TSPII_PORT_SIDE_20 = 37;
const unsigned int TSPII_PORT_SIDE_21 = 38;
const unsigned int TSPII_PORT_SIDE_22 = 39;
const unsigned int TSPII_PORT_SIDE_23 = 40;
const unsigned int TSPII_PORT_SIDE_24 = 41;
const unsigned int TSPII_PORT_SIDE_25 = 42;
const unsigned int TSPII_PORT_SIDE_26 = 43;
const unsigned int TSPII_PORT_SIDE_27 = 44;
const unsigned int TSPII_PORT_SIDE_28 = 45;
const unsigned int TSPII_PORT_SIDE_29 = 46;
const unsigned int TSPII_PORT_SIDE_30 = 47;
const unsigned int TSPII_PORT_SIDE_31 = 48;


const unsigned int TSPII_1NSEL_SIDE_0  = 1;
const unsigned int TSPII_1NSEL_SIDE_1  = 2;
const unsigned int TSPII_1NSEL_SIDE_2  = 3;
const unsigned int TSPII_1NSEL_SIDE_3  = 4;

const unsigned int TSPII_LINES           = TSPII_LINE_SIDE_15;
const unsigned int TSPII_LINES_AND_PORTS = TSPII_PORT_SIDE_31;
const unsigned int TSPII_PORTS           = (TSPII_LINES_AND_PORTS - TSPII_LINES);

namespace OmUpgStatus
{
    typedef enum
    {
        InProgress,
        NotHitless,
        Finished,
        Unknown
    } Enum;
}

class TSPII_SubApplication : public FC_BbApp
{
public:
    friend class TSPII_TestMenu;

    virtual                          ~TSPII_SubApplication();
    static  TSPII_SubApplication *   GetInstance();

    virtual void                     DoInitWarm(FC_Object* theObject);
    virtual void                     DoInitCold(FC_Object* theObject);
    virtual void                     DoInitConfig(FC_Object* theObject);
    virtual void                     InitCommon(restart_type theRestartType);

    virtual void                     DoCreateRegions(FC_Object* theObject);
    virtual void                     DoDeleteRegions(FC_Object* theObject);
    virtual void                     DoCreateActions(FC_Object* theObject);
    virtual void                     DoDeleteActions(FC_Object* theObject);
    virtual void                     DoActivateActions(FC_Object* theObject);
    virtual void                     DoDeactivateActions(FC_Object* theObject);
    virtual void                     DoEnableInterrupts(void);

    virtual TSPII_DwRegion *         GetDw        (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_TcmRegion *        GetTcm       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_FecRegion *        GetFec       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_GccRegion *        GetGcc       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
	virtual TSPII_IBETHRegion *      GetIBETH       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_GccMapRegion *     GetGccMap    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OchOHRegion *      GetOchOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OmsOHRegion *      GetOmsOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OpticalRegion *    GetOptical   (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OsaRegion *        GetOsa       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OtsOHRegion *      GetOtsOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_PilotToneRegion *  GetPilotTone (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_PipeRegion *       GetPipe      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_RsRegion *         GetRs        (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_IPCountersRegion * GetIPCounters(unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);

    virtual TSPII_UpdateAction *     GetUpdateAction(unsigned int theSlot);
    virtual bool                     Override(int argc, char** argv, uint32 theSlot = 0);
    virtual TSPII_MsRegion *         GetMs       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_HopRegion *        GetHop      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_VcgRegion *        GetVcg      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_GfpRegion *        GetGfp      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_T1E1Region *       GetT1E1     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_1NSelRegion *      Get1NSel    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_ClkSelRegion *     GetClkSel   (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_XcRegion *         GetXc       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_RmonRegion *       GetRmon     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_MacRegion *        GetMac      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DcclRegion *       GetDccl     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DrtrRegion *       GetDrtr     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DdltRegion *       GetDdlt     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_LagRegion *        GetLag      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_EvcRegion *        GetEvc      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_L2Region *         GetL2Eth    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_L2Region *         GetL2Lag    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_L2Region *         GetL2Vcg    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_SsmRegion *        GetSsm      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_FabRegion *        GetFab      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_SwitchRegion *     GetSwitch   (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_SncRegion *        GetSnc    (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);

    virtual uint16                   GetOdu0PoolIndex(uint32 theLogicalOduId);
    virtual uint16                   GetOdu1PoolIndex(uint32 theLogicalOduId);
    virtual uint16                   GetOdu2PoolIndex(uint32 theLogicalOduId);
    virtual uint16                   GetOdu3PoolIndex(uint32 theLogicalOduId);
    virtual uint16                   GetOdu4PoolIndex(uint32 theLogicalOduId);
    virtual uint16                   GetOduFPoolIndex(uint32 theLogicalOduId);    
    virtual uint16                   GetOduPoolIndex(uint32 theLogicalOduId);     

    // Interface with CSM for dumb card management.
    virtual void                     InitCard(uint32 theSlot, CT_CardType theCardType);
    virtual void                     SetCardPresent(uint32 theSlot, CT_CardType theCardType);
    virtual void                     StartUpdateActions(uint32 theSlot);
    virtual void                     SetCardAbsent (uint32 theSlot);
    virtual bool                     IsCardInitialized(uint32 theSlot);
    virtual bool                     IsCardReady(uint32 theSlot);
    virtual void                     FwUpgrade(uint32 theSlot, uint16 * theOMLoadPtr, uint32 theOMLoadSizeInBytes);
    virtual bool                     IsFwUpgradeFailed(uint32 theSlot);
    virtual bool                     IsFwUpgradeSuccessful(uint32 theSlot);
    virtual OmUpgStatus::Enum        GetOmUpgStatus(uint32 theSlot);
    virtual void                     ClearResetCause(uint32 theSlot);

    virtual void                     SaveData();
    virtual void                     NotifySignalProtection();

protected:
    TSPII_SubApplication();
    static TSPII_SubApplication * myInstance;
    TSPII_UpdateAction *          myUpdateActionArray[TSPII_MAX_UPDATE_ACTIONS];
};

#endif // TSPII_SUBAPPLICATION_H
