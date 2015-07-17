/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     TSPII
 TARGET   :     SPM8560
 AUTHOR   :     Anoop Mathew
 DESCRIPTION:   TSPII Sub-application for SPM8560
--------------------------------------------------------------------------*/

#ifndef TSPII_SPM8560SUBAPPLICATION_H
#define TSPII_SPM8560SUBAPPLICATION_H

#include "CommonTypes/CT_SystemIds.h"
#include "TsPii/TSPII_SubApplication.h"

class T6100_ShelfIf;
class T6100_CardIf;
class TSPII_Spm8560TestMenu;
class TSPII_SPM8560HwRefreshAction;
class TSPII_CntrlPilotToneCtrlAction;
class TSPII_CntrlSlaveSlot;
class TSPII_OsaIf;
class TSPII_XcIf;
class TSPII_CntrlLxameOsaCtrlAction;
class TSPII_LxameUpgrSwitchCntrlAction;
class TSPII_CardNanoCoreCtrl;

#ifdef __TARGET__
#include "TSPII_OscMapperFpgaDrv.h"
#endif


class TSPII_Spm8560SubApplication : public TSPII_SubApplication
{
    friend class TSPII_Spm8560TestMenu;
	friend class TSPII_OscMapperFpgaCtrl;

public:

    /* From base class */
    /* CTOR */                           TSPII_Spm8560SubApplication(T6100_ShelfIf & theShelfContext, T6100_CardIf & theCardContext);
    virtual                              ~TSPII_Spm8560SubApplication();
    virtual void                         DoCreateRegions(FC_Object* theObject);
    virtual void                         DoInitCold(FC_Object* theObject);
    virtual void                         DoInitWarm(FC_Object* theObject);
    virtual void                         InitCommon(restart_type theRestartType);
    virtual void                         DoCreateActions(FC_Object* theObject);
    virtual void                         DoActivateActions(FC_Object* theObject);
    virtual void                         DoDeactivateActions(FC_Object* theObject);
    virtual void                         DoDeleteActions(FC_Object* theObject);
    virtual void                         DoDeleteRegions(FC_Object* theObject);
    virtual void                         SuspendSlaveSlotActions(void);

    virtual TSPII_T1E1Region *           GetT1E1      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DrtrRegion *           GetDrtr      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_DdltRegion *           GetDdlt      (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OchOHRegion *          GetOchOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OmsOHRegion *          GetOmsOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OpticalRegion *        GetOptical   (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OsaRegion *            GetOsa       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_OtsOHRegion *          GetOtsOH     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_RsRegion *             GetRs        (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_MsRegion *             GetMs        (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_IPCountersRegion *     GetIPCounters(unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);

    virtual TSPII_PilotToneRegion *      GetPilotTone(unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_PipeRegion *           GetPipe     (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual TSPII_XcRegion *             GetXc       (unsigned int theUnit = TSPII_DONT_CARE, unsigned int theSlot = TSPII_DONT_CARE);
    virtual bool                         Override(int argc, char** argv, uint32 theSlot = 0);


	// Interface with CSM for dumb card management.
    virtual void                         InitCard(uint32 theSlot, CT_CardType theCardType);
    virtual void                         SetCardPresent(uint32 theSlot, CT_CardType theCardType);
    virtual void                         SetCardAbsent (uint32 theSlot);
    virtual bool                         IsCardInitialized(uint32 theSlot);
    virtual bool                         IsCardReady(uint32 theSlot);
    virtual void                         FwUpgrade(uint32 theSlot, uint16 * theOMLoadPtr, uint32 theOMLoadSizeInBytes);
    virtual bool                         IsFwUpgradeFailed(uint32 theSlot);
    virtual bool                         IsFwUpgradeSuccessful(uint32 theSlot);
    virtual void                         StartUpdateActions(uint32 theSlot);
    virtual OmUpgStatus::Enum            GetOmUpgStatus(uint32 theSlot);
    virtual void                         ClearResetCause(uint32 theSlot);


    static TSPII_Spm8560SubApplication & GetSpecificInstance();

    TSPII_CntrlPilotToneCtrlAction *     GetPilotToneControlAction(unsigned int theSlot);
    TSPII_CntrlLxameOsaCtrlAction  *     GetLxameOsaCtrlAction(unsigned int theSlot);
    TSPII_CardNanoCoreCtrl*              GetNanoCoreCtrl(unsigned int slot);
private:

    // OSC regions
    TSPII_OpticalRegion *          myOscOptical[TSPII_MAX_OSC*2];
    TSPII_RsRegion *               myOscRs[TSPII_MAX_OSC*2];
    TSPII_MsRegion *               myOscMs[TSPII_MAX_OSC*2];
    TSPII_OtsOHRegion *            myOscOts[TSPII_MAX_OSC*2];
    TSPII_OmsOHRegion *            myOscOms[TSPII_MAX_OSC*2];
    TSPII_OchOHRegion *            myOscOch[TSPII_MAX_OSC*2];
    TSPII_T1E1Region *             myT1E1[2];
    TSPII_DrtrRegion *             myDrtr;
    TSPII_DdltRegion *             myDdlt;
    TSPII_IPCountersRegion *       myIPCountersRegion;

    // Contexts
    TSPII_SPM8560HwRefreshAction * myRefreshAction;
	TSPII_LxameUpgrSwitchCntrlAction* myUpgSwitchCntrlAction;
    TSPII_Spm8560TestMenu *        myTestMenu;
    T6100_CardIf &                 myCardContext;
	T6100_ShelfIf &                myShelfContext;
    unsigned long                  mySlot;

	//Slave slot regions
	// Slot specific info
    TSPII_CntrlSlaveSlot * mySlaveSlot[TSPII_MAX_SLOT];

    // RCMM XC region 
    TSPII_XcRegion *         myRcmmXcRegion;

#ifdef __TARGET__
	//Conversion from tspii2fpga channels
	TSPII_OscMapperFpgaChannel GetMapperChannel(int oscChan);
#endif

};

#endif // TSPII_SPM8560SUBAPPLICATION_H
