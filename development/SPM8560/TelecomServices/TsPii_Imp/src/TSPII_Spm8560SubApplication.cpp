/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     TSPII
 TARGET   :     SPM8560
 AUTHOR   :     Anoop Mathew
 DESCRIPTION:   TSPII Sub-application on SPM8560
--------------------------------------------------------------------------*/
#ifdef WIN32
    #pragma warning( disable : 4786 )
#endif

#include "TsPii_Imp/TSPII_Spm8560SubApplication.h"
#include <CommonTypes/CT_DCC_Definitions.h>
#include "T6100_CardIf.h"
#include "T6100_ShelfIf.h"
#include "T6100_SlotIf.h"
#include "T6100_MainAppIf.h"
#include "T6100_ControllerStatusRegion.h"
#include "Blackboard/FC_Blackboard.h"
#include "CsPii/CSPII_ShelfIF.h"
#include "CsPii/CSPII_SysCfgParamIF.h"
#include "TsPii/TSPII_UpdateAction.h"
#include "TsPii/TSPII_IPCountersIf.h"
#include "TsPii/TSPII_MsIf.h"
#include "TsPii_Imp/TSPII_Spm8560TestMenu.h"
#include "TsPii_Imp/TSPII_SPM8560OpticalIf.h"
#include "TsPii_Imp/TSPII_SPM8560RsIf.h"
#include "TsPii_Imp/TSPII_SPM8560OtsOHIf.h"
#include "TsPii_Imp/TSPII_SPM8560OmsOHIf.h"
#include "TsPii_Imp/TSPII_SPM8560OchOHIf.h"
#include "TsPii_Imp/TSPII_SPM8560T1E1HwDrvIf.h"
#include "TsPii_Imp/TSPII_CntrlDrtrHwDrvIf.h"
#include "TsPii_Imp/TSPII_CntrlDdltHwDrvIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"
#include "TsPii_Imp/TSPII_SPM8560HwRefreshAction.h"
#include "TsPii_Imp/TSPII_LxameUpgrSwitchCntrlAction.h"
#include "Devices/DEV_TdmDefinition.h"
#include "Devices/HdpTimingCard.h"
#include "TsPii_Imp/TSPII_CntrlSlaveSlot.h"
#include "TsPii_Imp/TSPII_TdmSlaveCtrl.h"
#include "TsPii_Imp/TSPII_NcmSlaveCtrl.h"

#define OSC_UPDATE_ACTION_INDEX TSPII_MAX_SLOT

#ifdef __SIMULATION__
#define OBJECT_OPT   new TSPII_OpticalIf(false /* SIMUL */, false  /* PT CTRL */, true /* OPR */, true /* OPT */, true /* OPTPEER */)
#define OBJECT_RS    new TSPII_RsIf     (false /* SIMUL */)
#define OBJECT_MS    new TSPII_MsIf     (false /* SIMUL */)
#define OBJECT_OTSOH new TSPII_OtsOHIf  (false /* SIMUL */)
#define OBJECT_OMSOH new TSPII_OmsOHIf  (false /* SIMUL */)
#define OBJECT_OCHOH new TSPII_OchOHIf  (false /* SIMUL */)
#else
#define OBJECT_OPT   new TSPII_SPM8560OpticalIf(mapperChannel)
#define OBJECT_RS    new TSPII_SPM8560RsIf     (mapperChannel)
#define OBJECT_MS    new TSPII_MsIf     (false /* SIMUL */)
#define OBJECT_OTSOH new TSPII_SPM8560OtsOHIf  (mapperChannel)
#define OBJECT_OMSOH new TSPII_SPM8560OmsOHIf  (mapperChannel)
#define OBJECT_OCHOH new TSPII_SPM8560OchOHIf  (mapperChannel, j)
#endif

///////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560SubApplication::TSPII_Spm8560SubApplication(T6100_ShelfIf & theShelfContext, T6100_CardIf & theCardContext) :
    TSPII_SubApplication(),
    myRefreshAction(NULL),
	myUpgSwitchCntrlAction(NULL),
    myTestMenu(NULL),
    myCardContext(theCardContext),
	myShelfContext(theShelfContext),
    mySlot(theCardContext.GetCardId())
{
    unsigned int i;
    for (i = 0; i < TSPII_MAX_OSC*2; i++)
    {
        myOscOptical[i] = NULL;
        myOscRs[i]      = NULL;
        myOscMs[i]      = NULL;
        myOscOts[i]     = NULL;
        myOscOms[i]     = NULL;
        myOscOch[i]     = NULL;
    }

	for (i = 0; i < TSPII_MAX_SLOT; i++) mySlaveSlot[i] = NULL;
}
    
///////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560SubApplication::~TSPII_Spm8560SubApplication()
{
}
  
///////////////////////////////////////////////////////////////////////////////
TSPII_Spm8560SubApplication & TSPII_Spm8560SubApplication::GetSpecificInstance()
{
    return *(static_cast<TSPII_Spm8560SubApplication *>(TSPII_SubApplication::myInstance));
}
  
///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoCreateRegions(FC_Object* theObject)
{
    unsigned int i;
    unsigned int j;
    char         s[80];
    bool         isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();

    // Create each slave slot if on the active controller.
    if (isActiveController)
    {
		unsigned int nMaxTdmNumberOfSlot = TDM_MAX_NUMBER_OF_SLOT;
		CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

        for (i = 0; i < nMaxTdmNumberOfSlot; i++) 
        {
            unsigned int slot             = TSPII_TdmSlaveCtrl::Tdm2Slot(i);
            myUpdateActionArray[slot - 1] = new TSPII_UpdateAction(gTspiiSlotName[slot]);
            mySlaveSlot[slot - 1]         = new TSPII_CntrlSlaveSlot(*myShelfContext.GetSlotPtr(slot), *myUpdateActionArray[slot - 1]);
        }
    }

    // Update Action creation for OSC facilities
    // OSC update actions are placed in the update arrays after the slave slot update actions
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX] = new TSPII_UpdateAction();

    // Create T1E1 Regions
    myT1E1[0] = new TSPII_T1E1Region("TSPII_T1E1_A");
    myT1E1[1] = new TSPII_T1E1Region("TSPII_T1E1_B");

    // Create Drtr Regions
    myDrtr = new TSPII_DrtrRegion("TSPII_DRTR");

    // Create Ddlt Regions
    myDdlt = new TSPII_DdltRegion("TSPII_DDLT");


#if defined(__TARGET__) 
    if (isActiveController)
    {
        // Create hardware bindings for T1E1 objects - only on active controller
        myT1E1[0]->AddAt(0, new TSPII_SPM8560T1E1HwDrvIf(16, 0));   // A Side
        myT1E1[1]->AddAt(0, new TSPII_SPM8560T1E1HwDrvIf(16, 1));   // B Side

		for(j=0; j<CT_DCC_MAX_ROUTERS; j++)
		{
            myDrtr->AddAt(j, new TSPII_CntrlDrtrHwDrvIf());
		}
		
        myDdlt->AddAt(0, &(TSPII_CntrlDdltHwDrvIf::GetInstance()));    
    }
    else
    {
        // Create dummy simulation objects on standby controller
        myT1E1[0]->AddAt(0, new TSPII_T1E1If(16, false));     // A Side
        myT1E1[1]->AddAt(0, new TSPII_T1E1If(16, false));     // B Side

		for(j=0; j<CT_DCC_MAX_ROUTERS; j++)
		{
            myDrtr->AddAt(j, new TSPII_DrtrIf(false));
		}
        
        myDdlt->AddAt(0, new TSPII_DdltIf(false));     // 
    }
#else
    // SIMULATION
    myT1E1[0]->AddAt(0, new TSPII_T1E1If(16, false));     // A Side
    myT1E1[1]->AddAt(0, new TSPII_T1E1If(16, false));     // B Side
    
    for(j=0; j<CT_DCC_MAX_ROUTERS; j++)
	{
        myDrtr->AddAt(j, new TSPII_CntrlDrtrHwDrvIf());
	}

    myDdlt->AddAt(0, &(TSPII_CntrlDdltHwDrvIf::GetInstance()));     // 
#endif

    // Register the T1E1 regions
    myCardContext.GetBb().Register(*myT1E1[0]);
    myCardContext.GetBb().Register(*myT1E1[1]);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myT1E1[0]);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myT1E1[1]);

    myCardContext.GetBb().Register(*myDrtr);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myDrtr);

    myCardContext.GetBb().Register(*myDdlt);
    myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myDdlt);

    // OSC regions
    for (i = 0; i < TSPII_MAX_OSC*2; i++)
    {
#ifdef __TARGET__
        //Convert OSC channel to mapper channel
		TSPII_OscMapperFpgaChannel mapperChannel = GetMapperChannel(i);
#endif
        // Configure OSC OCh regions
        sprintf(s, "TSPII_OCH_OSC%d", i + 1);
        myOscOch[i] = new TSPII_OchOHRegion(s);
        for (j = 0; j < TSPII_MAX_OCH; j++) myOscOch[i]->AddAt(j, OBJECT_OCHOH);
        myCardContext.GetBb().Register(*myOscOch[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscOch[i]);

        // Configure OSC OMS regions
        sprintf(s, "TSPII_OMS_OSC%d", i + 1);
        myOscOms[i] = new TSPII_OmsOHRegion(s);
        myOscOms[i]->AddAt(0, OBJECT_OMSOH);
        myCardContext.GetBb().Register(*myOscOms[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscOms[i]);

        // Configure OSC OTS regions
        sprintf(s, "TSPII_OTS_OSC%d", i + 1);
        myOscOts[i] = new TSPII_OtsOHRegion(s);
        myOscOts[i]->AddAt(0, OBJECT_OTSOH);
        myCardContext.GetBb().Register(*myOscOts[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscOts[i]);

        // Configure OSC RS regions
        sprintf(s, "TSPII_RS_OSC%d", i + 1);
        myOscRs[i] = new TSPII_RsRegion(s);
        myOscRs[i]->AddAt(0, OBJECT_RS);
        myCardContext.GetBb().Register(*myOscRs[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscRs[i]);

        // Configure OSC MS regions
        sprintf(s, "TSPII_MS_OSC%d", i + 1);
        myOscMs[i] = new TSPII_MsRegion(s);
        myOscMs[i]->AddAt(0, OBJECT_MS);
        myCardContext.GetBb().Register(*myOscMs[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscMs[i]);

        // Configure OSC optical regions
        sprintf(s, "TSPII_OPTICAL_OSC%d", i + 1);
        myOscOptical[i] = new TSPII_OpticalRegion(s);
        myOscOptical[i]->AddAt(0, OBJECT_OPT);
        myCardContext.GetBb().Register(*myOscOptical[i]);
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->RegisterRegion(myOscOptical[i]);
    }

    // IP counters region
    myIPCountersRegion = new TSPII_IPCountersRegion("TSPII_IP_COUNTERS");
    myIPCountersRegion->AddAt(0, new TSPII_IPCountersIf());
    myCardContext.GetBb().Register(*myIPCountersRegion);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoInitCold(FC_Object* theObject)
{
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController())
    {
        // Init the Timing Controller and assoc hardware devices.
        HdpTimingCard::GetInstance(HdpTiming::Reference::A).InitCold();
        HdpTimingCard::GetInstance(HdpTiming::Reference::B).InitCold();
    }

    TSPII_SubApplication::DoInitCold(theObject); // Invoke base class which calls InitCommon
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoInitWarm(FC_Object* theObject)
{
    if (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController())
    {
        // Init the Timing Controller and assoc hardware devices.
        HdpTimingCard::GetInstance(HdpTiming::Reference::A).InitWarm();
        HdpTimingCard::GetInstance(HdpTiming::Reference::B).InitWarm();
    }

    TSPII_SubApplication::DoInitWarm(theObject);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::InitCommon(restart_type theRestartType)
{
    TSPII_OscMapperFpgaCtrl::GetInstance().Refresh();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoCreateActions(FC_Object* theObject)
{
	bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();
    myTestMenu      = new TSPII_Spm8560TestMenu();
    myRefreshAction = new TSPII_SPM8560HwRefreshAction();

	//on active controller init the BPFPGA drivers and
	//Lxame upgrade switch control actions
	if (isActiveController)
	{
	    DEV_BackplaneIfFpgaDrv::GetInstance().Init();
#ifdef __TARGET__
            myUpgSwitchCntrlAction = new TSPII_LxameUpgrSwitchCntrlAction();
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoActivateActions(FC_Object* theObject)
{
	bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();

	myRefreshAction->GetProcess().WakeUp();

	//TSPII has nothing to do on the standby SPM with regards to the OSC channels. 
	//Hence do not wake up 
	//the update actions on the standby controller
	if (isActiveController)
	{
            myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->WakeUp();
	}
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoDeactivateActions(FC_Object* theObject)
{
    bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();
    myRefreshAction->GetProcess().SuspendImmediate();
	
    if (isActiveController)
    {    
        myUpdateActionArray[OSC_UPDATE_ACTION_INDEX]->Suspend();
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoDeleteActions(FC_Object* theObject)
{
    delete myRefreshAction; myRefreshAction = NULL;
    delete myTestMenu;      myTestMenu = NULL;
    if (myUpgSwitchCntrlAction)
        delete myUpgSwitchCntrlAction; 
    myUpgSwitchCntrlAction = NULL;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::DoDeleteRegions(FC_Object* theObject)
{
    unsigned int i;

	
    for (i = 0; i < TSPII_MAX_SLOT; i++)
    {
        if (mySlaveSlot[i])
		    delete mySlaveSlot[i]; 
		mySlaveSlot[i] = NULL;
    }

    // OSC regions
    for (i = 0; i < TSPII_MAX_OSC*2; i++)
    {
        delete myOscOptical[i]; myOscOptical[i] = NULL;
        delete myOscRs[i];      myOscRs[i]      = NULL;
        delete myOscMs[i];      myOscMs[i]      = NULL;
        delete myOscOts[i];     myOscOts[i]     = NULL;
        delete myOscOms[i];     myOscOms[i]     = NULL;
        delete myOscOch[i];     myOscOch[i]     = NULL;
    }

    delete myT1E1[0];
    delete myT1E1[1];
    delete myDrtr;
    delete myDdlt;

    delete myUpdateActionArray[OSC_UPDATE_ACTION_INDEX];

    delete myIPCountersRegion; myIPCountersRegion = NULL;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_T1E1Region * TSPII_Spm8560SubApplication::GetT1E1(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= sizeof(myT1E1)/sizeof(myT1E1[0])) return myT1E1[theUnit - 1];
    return TSPII_SubApplication::GetT1E1(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DrtrRegion * TSPII_Spm8560SubApplication::GetDrtr(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE) && (theUnit == TSPII_DONT_CARE)) return myDrtr;
    return TSPII_SubApplication::GetDrtr(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DdltRegion * TSPII_Spm8560SubApplication::GetDdlt(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE) && (theUnit == TSPII_DONT_CARE)) return myDdlt;
    return TSPII_SubApplication::GetDdlt(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OchOHRegion * TSPII_Spm8560SubApplication::GetOchOH(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscOch[theUnit - 1];
    return TSPII_SubApplication::GetOchOH(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OmsOHRegion * TSPII_Spm8560SubApplication::GetOmsOH(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscOms[theUnit - 1];
    return TSPII_SubApplication::GetOmsOH(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OpticalRegion * TSPII_Spm8560SubApplication::GetOptical(unsigned int theUnit, unsigned int theSlot)
{
    //4D subnodes have LOAMs in slot 6 where as some 2D subnodes (RCMM with old AMPS) have RCMM in slot 6
    //Check the subnode to determine how to proceed
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

    // See if this is subnode config using NANO-like Core Add/Drop Modules (CADM)
    if ( aSubNodeCfg == SBOADM_CH88_4D_HCSS )
    {
        if ( ((theSlot == CADM_FP3_A) || (theSlot == CADM_FP3_B) || (theSlot == CADM_FP3_C) || (theSlot == CADM_FP3_D)) && 
             mySlaveSlot[theSlot - 1]                                                                                   && 
             ((1 <= theUnit) && (theUnit <= (TSPII_MAX_PUMP * 2))) )
        {
            return (mySlaveSlot[theSlot - 1]->myNanoCoreOpticalRegion[theUnit - 1]);
        }
    }

    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscOptical[theUnit - 1];
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && theUnit == TSPII_DONT_CARE) return mySlaveSlot[theSlot - 1]->myPumpOpticalRegion[0];
    if ((theSlot == RCMM_3) || (theSlot == RCMM_14) || (theSlot == RCMM_7) || (theSlot == RCMM_10) || (theSlot == RCMM_11) || (theSlot == RCMM_4) || (theSlot == RCMM_8) || (theSlot == RCMM_15))
    {
        if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_OPT)  return mySlaveSlot[theSlot - 1]->myRcmmOpticalRegion[theUnit - 1];
    }
    else if (theSlot == RCMM_6 || theSlot == LOAM_6)
    {
        if ( (aSubNodeCfg == SBOADM_FP3_CH44_RCMM4_AMP)      ||
             (aSubNodeCfg == SBOADM_FP3_CH44_RCMM8_AMP)      || 
             (aSubNodeCfg == SBOADM_FP3_CH32PLUS_RCMM4_AMP)  ||
             (aSubNodeCfg == SBOADM_FP3_CH88_RCMM8_AMP)      ||
             (aSubNodeCfg == SBOADM_FP3_CH88_RCMM8_HCSS_AMP) ||
             (aSubNodeCfg == SBOADM_FP3_CH44_RCMM8_HCSS_AMP) ) //this is a LOAM
        {
            if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_PUMP) return mySlaveSlot[theSlot - 1]->myPumpOpticalRegion[theUnit - 1];
        }
        else //an RCMM
        {
            if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_OPT)  return mySlaveSlot[theSlot - 1]->myRcmmOpticalRegion[theUnit - 1];
        }
    }
    else
    {
        if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_PUMP) return mySlaveSlot[theSlot - 1]->myPumpOpticalRegion[theUnit - 1];
    }
    return TSPII_SubApplication::GetOptical(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OtsOHRegion * TSPII_Spm8560SubApplication::GetOtsOH(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscOts[theUnit - 1];
    return TSPII_SubApplication::GetOtsOH(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_RsRegion * TSPII_Spm8560SubApplication::GetRs(unsigned int theUnit, unsigned int theSlot)
{
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscRs[theUnit - 1];
    return TSPII_SubApplication::GetRs(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_MsRegion * TSPII_Spm8560SubApplication::GetMs(unsigned int theUnit, unsigned int theSlot)
{
    //Check OSC MS first
    if ((theSlot == TSPII_DONT_CARE || theSlot == mySlot) && 1 <= theUnit && theUnit <= (TSPII_MAX_OSC*2)) return myOscMs[theUnit - 1];
    return TSPII_SubApplication::GetMs(theUnit, theSlot);
}


///////////////////////////////////////////////////////////////////////////////
TSPII_IPCountersRegion * TSPII_Spm8560SubApplication::GetIPCounters(unsigned int theUnit, unsigned int theSlot)
{
    return myIPCountersRegion;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneRegion * TSPII_Spm8560SubApplication::GetPilotTone(unsigned int theUnit, unsigned int theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && theUnit == TSPII_DONT_CARE) return mySlaveSlot[theSlot - 1]->myPilotToneRegion[0];
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_PT) return mySlaveSlot[theSlot - 1]->myPilotToneRegion[theUnit - 1];
    return TSPII_SubApplication::GetPilotTone(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OsaRegion * TSPII_Spm8560SubApplication::GetOsa(unsigned int theUnit, unsigned int theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && theUnit == TSPII_DONT_CARE) return mySlaveSlot[theSlot - 1]->myOsaRegion[0];
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_OSA) return mySlaveSlot[theSlot - 1]->myOsaRegion[theUnit - 1];
    return TSPII_SubApplication::GetOsa(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PipeRegion * TSPII_Spm8560SubApplication::GetPipe(unsigned int theUnit, unsigned int theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && theUnit == TSPII_DONT_CARE) return mySlaveSlot[theSlot - 1]->myPipeRegion[0];
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] && 1 <= theUnit && theUnit <= TSPII_MAX_PIPE) return mySlaveSlot[theSlot - 1]->myPipeRegion[theUnit - 1];
    return TSPII_SubApplication::GetPipe(theUnit, theSlot);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_CntrlPilotToneCtrlAction * TSPII_Spm8560SubApplication::GetPilotToneControlAction(unsigned int theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1]) return mySlaveSlot[theSlot - 1]->myPilotToneCtrlAction;
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_CntrlLxameOsaCtrlAction * TSPII_Spm8560SubApplication::GetLxameOsaCtrlAction(unsigned int theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1]) return mySlaveSlot[theSlot - 1]->myLxameOsaCtrlAction;
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_XcRegion * TSPII_Spm8560SubApplication::GetXc(unsigned int theUnit, unsigned int theSlot)
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

    // See if this is subnode config using NANO-like Core Add/Drop Modules (CADM)
    if ( aSubNodeCfg == SBOADM_CH88_4D_HCSS )
    {
        if ( ((theSlot == CADM_FP3_A) || (theSlot == CADM_FP3_B) || (theSlot == CADM_FP3_C) || (theSlot == CADM_FP3_D)) && 
             mySlaveSlot[theSlot - 1] )
        {
            return (mySlaveSlot[theSlot - 1]->myNanoCcmXcRegion);
        }
    }

    // only the RCMM in 3&14 or 6&11 or 3&14&7&10 support the XC region
    if ((theSlot == RCMM_3) || (theSlot == RCMM_6) || (theSlot == RCMM_7) || (theSlot == RCMM_10) || 
        (theSlot == RCMM_11) || (theSlot == RCMM_14) || (theSlot == RCMM_4) || (theSlot == RCMM_8) ||
        (theSlot == RCMM_15)) 
    {
        return mySlaveSlot[theSlot - 1]->myRcmmXcRegion;
    }
    else
    {
        return NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::InitCard(uint32 theSlot, CT_CardType theCardType)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot)).InitCard(theCardType);
        }
        else
        {
            TSPII_NcmSlaveCtrl::GetInstance(theSlot).InitCard(theCardType);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::SetCardPresent(uint32 theSlot, CT_CardType theCardType)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        mySlaveSlot[theSlot - 1]->SetCardPresent(theCardType);

        switch ( theCardType )
        {
        case OADM88IR:
        case OADM88LR:
        case OADM88ER:
        case CCM88IR:
        case CCM88LR:
        case CCM88ER:
        case OTSM:
            // these modules don't have upgrade switches, nor associated LOAME;
            // don't mess with the SwitchCtrlAction
            break;
        default:
            if (theSlot == LIAM_1 || theSlot == LIAM_19 || theSlot == LIAM_5 || theSlot == LIAM_13 ||
                theSlot == LOAM_2 || theSlot == LOAM_16 || theSlot == LOAM_6 || theSlot == LOAM_12)
            {
                if (myUpgSwitchCntrlAction)
                {
                    myUpgSwitchCntrlAction->ResetArmingCount((CT_SlotId)theSlot);
                    myUpgSwitchCntrlAction->GetSwitchTimedProcess()->WakeUp();
                }
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::StartUpdateActions(uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        myUpdateActionArray[theSlot - 1]->WakeUp();
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::SetCardAbsent(uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        // set absent for both controllers because there is no card type to worry about
        mySlaveSlot[theSlot - 1]->SetCardAbsent();
        TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot)).SetCardAbsent();
        TSPII_NcmSlaveCtrl::GetInstance(theSlot).SetCardAbsent();
        myUpdateActionArray[theSlot-1]->Suspend();
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_Spm8560SubApplication::IsCardInitialized(uint32 theSlot)
{
    if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
    {
        return TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot)).IsInitialized();
    }
    return TSPII_NcmSlaveCtrl::GetInstance(theSlot).IsInitialized();
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_Spm8560SubApplication::IsCardReady(uint32 theSlot)
{
    bool status = false;

    // is the slot valid?
    if ( (1 <= theSlot) && (theSlot <= TSPII_MAX_SLOT) && (mySlaveSlot[theSlot - 1] != NULL) )
    {
#if defined(__TARGET__) 
        // is the card a TDM or ETH card?
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            // for TDM just return the TSPII initialization status
            status = TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot)).IsInitialized();
        }
        else
        {
            // for ETH cards, the comm engine has to be running and
            // the card configuration has been retrieved
            if ( TSPII_NcmSlaveCtrl::GetInstance(theSlot).IsInitialized()
            &&   mySlaveSlot[theSlot - 1]->IsNanoCardInitialized() )
            {
                status = true;
            }
        }
#else
        status = true;
#endif
    }
    return status;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_Spm8560SubApplication::Override(int argc, char** argv, uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        return mySlaveSlot[theSlot - 1]->Override(argc, argv);
    }
    fc_cout << "Override: Invalid slot number." << endl;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::FwUpgrade(uint32 theSlot, uint16 * theOMLoadPtr, uint32 theOMLoadSizeInBytes)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            TSPII_TdmSlaveCtrl & slave = TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot));
            slave.FwUpgrade(theOMLoadPtr, theOMLoadSizeInBytes);
        }
        else
        {
            FC_THROW_ERROR( FC_RuntimeError, "can't FW Upgrade to Ethernet Dumb Card" );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_Spm8560SubApplication::IsFwUpgradeFailed(uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            TSPII_TdmSlaveCtrl & slave = TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot));
            return slave.GetFwUpgradeStatus() == TSPII_TdmSlaveCtrl::FW_UPGRADE_FAILED;
        }
        else
        {
            return TSPII_NcmSlaveCtrl::GetInstance(theSlot).GetFwUpgradeStatus() == TSPII_NcmSlaveCtrl::FW_UPGRADE_FAILED;
        }
    }
    return TSPII_SubApplication::IsFwUpgradeFailed(theSlot);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_Spm8560SubApplication::IsFwUpgradeSuccessful(uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            TSPII_TdmSlaveCtrl & slave = TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot));
            return slave.GetFwUpgradeStatus() == TSPII_TdmSlaveCtrl::FW_UPGRADE_COMPLETED;
        }
        else
        {
            return TSPII_NcmSlaveCtrl::GetInstance(theSlot).GetFwUpgradeStatus() == TSPII_NcmSlaveCtrl::FW_UPGRADE_COMPLETED;
        }
    }
    return TSPII_SubApplication::IsFwUpgradeSuccessful(theSlot);
}

///////////////////////////////////////////////////////////////////////////////
OmUpgStatus::Enum TSPII_Spm8560SubApplication::GetOmUpgStatus(uint32 theSlot)
{
    OmUpgStatus::Enum upgStatus = OmUpgStatus::Finished;
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            // TDM modules are in progress or finished
            TSPII_TdmSlaveCtrl & slave = TSPII_TdmSlaveCtrl::GetInstance(TSPII_TdmSlaveCtrl::Slot2Tdm(theSlot));
            if ( slave.GetFwUpgradeStatus() == TSPII_TdmSlaveCtrl::FW_UPGRADE_IN_PROGRESS )
            {
                upgStatus = OmUpgStatus::InProgress;
            }
        }
        else
        {
            // Ethernet modules are in progress or finished. If finished, then 
            // it could be because the module indicated the upgrade is not hitless,
            // the upgrade completed successfully, or the upgrade failed.
            TSPII_NcmSlaveCtrl::TSPII_NcmFwUpgradeState theState = TSPII_NcmSlaveCtrl::GetInstance(theSlot).GetFwUpgradeStatus();
            if ( theState == TSPII_NcmSlaveCtrl::FW_UPGRADE_IN_PROGRESS )
            {
                upgStatus = OmUpgStatus::InProgress;
            }
            else if ( theState == TSPII_NcmSlaveCtrl::FW_UPGRADE_FAILED )
            {
                upgStatus = OmUpgStatus::Finished;
            }
            // done, but need to find out if the upgrade was successful.
            else if ( theState == TSPII_NcmSlaveCtrl::FW_UPGRADE_NOT_HITLESS )
            {
                upgStatus = OmUpgStatus::NotHitless;
            }
            // upgStatus was initialized to Finished
        }
    }
    else
    {
        upgStatus = TSPII_SubApplication::GetOmUpgStatus(theSlot);
    }
    return upgStatus;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::ClearResetCause(uint32 theSlot)
{
    if (1 <= theSlot && theSlot <= TSPII_MAX_SLOT && mySlaveSlot[theSlot - 1] != NULL)
    {
        if ( !CSPII_ShelfIF::GetInstance()->cardHasTdmFpga(theSlot) )
        {
            // tell the slave controller to step through the reset cause
            TSPII_NcmSlaveCtrl::GetInstance(theSlot).ClearReset();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

    //NOTE: There is a conversion required here between the application and 
    // the fpga.
	//2 conversions are possible

    //The first is for configurations that use the LxAME based cards
	//------------------------------------------------------------------
	//Application  View                |       Mapper View             //
	//------------------------------------------------------------------
	//0 A side  (1) OSC_FPGA_CHANNEL1    |        A  OSC_FPGA_CHANNEL1
	//1 B side  (19)OSC_FPGA_CHANNEL2    |        D  OSC_FPGA_CHANNEL4
	//2 C side  (5) OSC_FPGA_CHANNEL3    |        B  OSC_FPGA_CHANNEL2
	//3 D side  (13) OSC_FPGA_CHANNEL4   |        C  OSC_FPGA_CHANNEL3
	//------------------------------------------------------------------

    //The second is for configurations that use the CADM based cards
	//------------------------------------------------------------------
	//Application  View                |       Mapper View             //
	//------------------------------------------------------------------
	//0 A side  (1) OSC_FPGA_CHANNEL1    |        A  OSC_FPGA_CHANNEL1
	//1 B side  (13)OSC_FPGA_CHANNEL2    |        C  OSC_FPGA_CHANNEL3
	//2 C side  (5) OSC_FPGA_CHANNEL3    |        B  OSC_FPGA_CHANNEL2
	//3 D side  (9) OSC_FPGA_CHANNEL4    |        D  OSC_FPGA_CHANNEL4
	//------------------------------------------------------------------
#ifdef __TARGET__
TSPII_OscMapperFpgaChannel TSPII_Spm8560SubApplication::GetMapperChannel(int oscChan)
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    if (aSubNodeCfg == SBOADM_CH88_4D_HCSS)
    {
        switch(oscChan)
	    {
	    case 0:
		    return OSC_FPGA_CHANNEL1;
	    case 1:
		    return OSC_FPGA_CHANNEL3;
	    case 2:
		    return OSC_FPGA_CHANNEL2;
	    case 3:
		    return OSC_FPGA_CHANNEL4;
	    default:
		    fc_cout << "Invalid osc channel" << endl;
		    return OSC_FPGA_CHANNEL1;
	    }
    }
    else
    {
	    switch(oscChan)
	    {
	    case 0:
		    return OSC_FPGA_CHANNEL1;
	    case 1:
		    return OSC_FPGA_CHANNEL4;
	    case 2:
		    return OSC_FPGA_CHANNEL2;
	    case 3:
		    return OSC_FPGA_CHANNEL3;
	    default:
		    fc_cout << "Invalid osc channel" << endl;
		    return OSC_FPGA_CHANNEL1;
	    }
    }
}
#endif

///////////////////////////////////////////////////////////////////////////////
TSPII_CardNanoCoreCtrl* TSPII_Spm8560SubApplication::GetNanoCoreCtrl(unsigned int slot)
{
    TSPII_CardNanoCoreCtrl* ret = NULL;
    if(slot<NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF)
    {
        TSPII_CntrlSlaveSlot* slotPtr = mySlaveSlot[slot-1];
        if(slotPtr)
        {
            ret = slotPtr->myCardNanoCoreCtrl;
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_Spm8560SubApplication::SuspendSlaveSlotActions(void)
{
    int i;
    bool isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();

    if ( isActiveController )
    {
        for ( i=0; i<TSPII_MAX_SLOT; i++ )
        {
            if ( mySlaveSlot[i] != NULL )
            {
                mySlaveSlot[i]->SuspendActions();
            }
        }
    }
}


