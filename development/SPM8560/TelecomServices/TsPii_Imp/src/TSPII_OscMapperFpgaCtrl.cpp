/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM : TSPII
 TARGET : SPM8560
 AUTHOR : Martin Piotte, 2003/1/20
 DESCRIPTION : Device control for OSC mapper FPGA on SPM8560.
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

#include "TsPii/TSPII_BaseIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"
#include "CsPii_Imp/CSPII_Spm8560Layer3switch.h"
#include "T6100_MainAppIf.h"
#include "T6100_ControllerStatusRegion.h"
#include "Blackboard/FC_Blackboard.h"
#include "TsPii_Imp/TSPII_Spm8560SubApplication.h"
#include "TsPii/TSPII_PipeIf.h"
#include "TsPii_Imp/TSPII_CardInputAmpOlimCtrl.h"
#include "TsPii_Imp/TSPII_CntrlSlaveSlot.h"
#include "TsPii_Imp/TSPII_CardNanoCoreCtrl.h"

#ifdef __SIMULATION__
    #define CLEAR_EVENT (*pEvent &= ~event)
#else
    #define CLEAR_EVENT (*pEvent = event)
#endif
#define UPDATE_COUNT (count = TSPII_DEFECT(count) != value ? count + 1 : event ? count + 2 : count)


TSPII_OscMapperFpgaCtrl * TSPII_OscMapperFpgaCtrl::ourInstance = NULL;

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaCtrl & TSPII_OscMapperFpgaCtrl::GetInstance()
{
    if (ourInstance == NULL) ourInstance = new TSPII_OscMapperFpgaCtrl;
    return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::DeleteInstance()
{
    delete ourInstance; ourInstance = NULL;
}

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaCtrl::TSPII_OscMapperFpgaCtrl() :
    myOscDrv(TSPII_OscMapperFpgaDrv::GetInstance())
{
    Reset();
}

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaCtrl::~TSPII_OscMapperFpgaCtrl()
{
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::Init()
{
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::Refresh()
{
    const uint16 OSC_FPGA_CHANNEL_CONTROL_MASK     = 0x01FC;
    const uint16 OSC_FPGA_CHANNEL_CONTROL_VALUE    = 0x0110;
    const uint16 OSC_FPGA_K1_K2_TRANSMIT_MASK      = 0xFFFF;
    const uint16 OSC_FPGA_K1_K2_TRANSMIT_VALUE     = 0x0000;
    const uint16 OSC_FPGA_DEBUG_MASK               = 0x003F;
    const uint16 OSC_FPGA_DEBUG_VALUE              = 0x0000;
    int          i;
	bool         isActiveController = T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController();

    //Make sure signal detect polarity is active high
	myOscDrv.ReadModWrBool(OSC_FPGA_BACKPLANE_CHANNEL_CONFIGURATION,OSC_FPGA_SIGNAL_DETECT_POLARITY,true);

    for (i = 0; i < 4; i++)
    {
		TSPII_OscMapperFpgaChannel osc;
		switch (i)
		{
		case 0:
			osc = OSC_FPGA_CHANNEL1;
			break;
		case 1:
			osc = OSC_FPGA_CHANNEL2;
			break;
		case 2:
			osc = OSC_FPGA_CHANNEL3;
			break;
		case 3:
			osc = OSC_FPGA_CHANNEL4;
			break;
		default:
			osc = OSC_FPGA_CHANNEL1; //should never happen
		}
        myOscDrv.ChannelReadModWr(osc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_CHANNEL_CONTROL_MASK, OSC_FPGA_CHANNEL_CONTROL_VALUE);
        myOscDrv.ChannelReadModWr(osc, OSC_FPGA_DEBUG, OSC_FPGA_DEBUG_MASK, OSC_FPGA_DEBUG_VALUE);
		myOscDrv.ChannelReadModWrBool(osc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_CONTROL, OSC_FPGA_SIGNAL_DETECT, true); 
    }

	//Make sure that on the active controller module we assert the mastership
	if (isActiveController)
	{
	    OptSetSwitchMastershipControl(true);
	}
	else
	{
		OptSetSwitchMastershipControl(false);
	}

    // Make sure OSC lasers are always on at start up
    //OptSetLaserEnable(OSC_FPGA_CHANNEL1, true);
    //OptSetLaserEnable(OSC_FPGA_CHANNEL2, true);
	//Make sure that channel A/B source/destination select is set to the backplane
	myOscDrv.ReadModWrBool(OSC_FPGA_MAPPER_CONFIGURATION, OSC_FPGA_CHANNEL_AB_DEST_SELECT, true);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::Reset()
{
    int i;
    int j;

    RsGetCVCount(OSC_FPGA_CHANNEL1);
    RsGetCVCount(OSC_FPGA_CHANNEL2);
	RsGetCVCount(OSC_FPGA_CHANNEL3);
    RsGetCVCount(OSC_FPGA_CHANNEL4);
    for (i = 0; i < TSPII_MAX_OSC*2; i++)
    {
        for (j = 0; j < TSPII_MAX_OCH; j++)
        {
            myOchOCI[i][j]  = 0;
            myOchFDIP[i][j] = 0;
            myOchFDIO[i][j] = 0;;
        }
        myOmsPMI[i]         = 0;
        myOmsBDIP[i]        = 0;
        myOmsBDIO[i]        = 0;
        myOmsFDIP[i]        = 0;
        myOmsFDIO[i]        = 0;
        myOtsPMI[i]         = 0;
        myOtsBDIP[i]        = 0;
        myOtsBDIO[i]        = 0;
        myRsLOF[i]          = 0;
        myRsOOF[i]          = 0;
        myOptLOS[i]         = 0;
        myOptLossOfClock[i] = 0;
        myCVCount[i]        = 0;
    }

    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    if (aSubNodeCfg == SBOADM_CH88_4D_HCSS)
    {
        myCADMSupported = true;
    }
    else
    {
        myCADMSupported = false;
    }
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OchGetOCI(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 &          count  = myOchOCI[theOsc][theOch];
    uint16            mask   = OSC_FPGA_OCH_OCI;

    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);
    
    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_BRAM)       + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    volatile uint16 * pEvent = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_LATCH_BRAM) + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    bool              value  = (*pValue & mask) != 0;
    uint16            event  = *pEvent & mask;
    CLEAR_EVENT;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OchGetFDIP(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 &          count  = myOchFDIP[theOsc][theOch];
    uint16            mask   = OSC_FPGA_OCH_FDIP;

    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_BRAM)       + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    volatile uint16 * pEvent = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_LATCH_BRAM) + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    bool              value  = (*pValue & mask) != 0;
    uint16            event  = *pEvent & mask;
    CLEAR_EVENT;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OchGetFDIO(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 &          count  = myOchFDIO[theOsc][theOch];
    uint16            mask   = OSC_FPGA_OCH_FDIO;

    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_BRAM)       + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    volatile uint16 * pEvent = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_RECEIVE_LATCH_BRAM) + (aAdjOch << OSC_FPGA_OCH_OFFSET);
    bool              value  = (*pValue & mask) != 0;
    uint16            event  = *pEvent & mask;
    CLEAR_EVENT;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OchGetForceOCI(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_OCI;
    return (*pValue & mask) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OchGetForceFDIP(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_FDIP;
    return (*pValue & mask) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OchGetForceFDIO(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_FDIO;
    return (*pValue & mask) != 0;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OchForceOCI(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_OCI;
    *pValue                  = theValue ? *pValue | mask : *pValue & ~mask;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OchForceFDIP(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_FDIP;
    *pValue                  = theValue ? *pValue | mask : *pValue & ~mask;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OchForceFDIO(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue)
{
    uint32            aAdjOch  = GetAdjustedOchChanNum(theOch);

    volatile uint16 * pValue = myOscDrv.OchChannelGetAddr(theOsc, theOch, OSC_FPGA_OCH_TRANSMIT_BRAM) + aAdjOch;
    uint16            mask   = OSC_FPGA_OCH_FDIO;
    *pValue                  = theValue ? *pValue | mask : *pValue & ~mask;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OmsGetPMI(TSPII_OscMapperFpgaChannel theOsc)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 & count = myOmsPMI[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OMS_PMI) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OMS_PMI)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OmsGetBDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 & count = myOmsBDIP[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OMS_BDIP) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OMS_BDIP)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OmsGetBDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 & count = myOmsBDIO[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OMS_BDIO) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OMS_BDIO)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OmsGetFDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 & count = myOmsFDIP[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OMS_FDIP) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OMS_FDIP)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OmsGetFDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    if (RsGetSignalType() == CT_TEL_SIGNAL_E1) return 0;
    uint32 & count = myOmsFDIO[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OMS_FDIO) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OMS_FDIO)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OmsGetForcePMI(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OMS_PMI) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OmsGetForceBDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OMS_BDIP) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OmsGetForceBDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OMS_BDIO) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OmsGetForceFDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OMS_FDIP) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OmsGetForceFDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OMS_FDIO) != 0;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OmsForcePMI(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OMS_PMI, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OmsForceBDIP(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OMS_BDIP, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OmsForceBDIO(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OMS_BDIO, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OmsForceFDIP(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OMS_FDIP, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OmsForceFDIO(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OMS_FDIO, theValue);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OtsGetPMI(TSPII_OscMapperFpgaChannel theOsc)
{
    uint32 & count = myOtsPMI[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OTS_PMI) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OTS_PMI)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OtsGetBDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    uint32 & count = myOtsBDIP[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OTS_BDIP) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OTS_BDIP)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OtsGetBDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    uint32 & count = myOtsBDIO[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS) & OSC_FPGA_OTS_BDIO) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH, OSC_FPGA_OTS_BDIO)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OtsGetForcePMI(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OTS_PMI) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OtsGetForceBDIP(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OTS_BDIP) != 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OtsGetForceBDIO(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT) & OSC_FPGA_OTS_BDIO) != 0;
}

////////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_OscMapperFpgaCtrl::OtsGetRxTTI(TSPII_OscMapperFpgaChannel theOsc)
{
    const int         size = CT_MAX_G709_TTI_SIZE/2;
    uint16            ttiRaw[size];
    CT_G709TTI        dstShifted;
    uint8*            tempTTI;
    volatile uint16 * src  = myOscDrv.ChannelGetAddr(theOsc, OSC_FPGA_OTS_TTI_RECEIVE_BRAM);
    int               i;

    // if not in Trace LOF, read trace
    if ( (myOscDrv.ChannelRead(theOsc, OSC_FPGA_INGRESS_ALARM_STATUS) & OSC_FPGA_OTS_TTI_LOF) == 0 )
    {
        for (i = 0; i < size; i++) ttiRaw[i] = *src++;
        tempTTI = (uint8*)ttiRaw;
        for (i = 0; i<CT_MAX_G709_TTI_SIZE-1; i++) dstShifted[i] = tempTTI[i+1];
        dstShifted[CT_MAX_G709_TTI_SIZE-1] = tempTTI[0];
    }
    else
        // Clear memory
        memset(dstShifted, 0, sizeof(dstShifted));

    myOtsRxTTI[theOsc].SetTTI(dstShifted);
    return myOtsRxTTI[theOsc];
}

////////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_OscMapperFpgaCtrl::OtsGetTxTTI(TSPII_OscMapperFpgaChannel theOsc)
{
    const int         size = CT_MAX_G709_TTI_SIZE/2;
    uint16            dst[size];
    volatile uint16 * src  = myOscDrv.ChannelGetAddr(theOsc, OSC_FPGA_OTS_TTI_TRANSMIT_BRAM);
    int               i;

    for (i = 0; i < size; i++) dst[i] = *src++;
    myOtsTxTTI[theOsc].SetTTI((uint8 *)dst);
    return myOtsTxTTI[theOsc];
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OtsSetTxTTI(TSPII_OscMapperFpgaChannel theOsc, const CT_G709Trace & theTrace)
{
    const int         size = CT_MAX_G709_TTI_SIZE/2;
    uint16            src[size];
    volatile uint16 * dst  = myOscDrv.ChannelGetAddr(theOsc, OSC_FPGA_OTS_TTI_TRANSMIT_BRAM);
    int               i;

    theTrace.GetTTI((uint8 *)src);
    for (i = 0; i < size; i++) *dst++ = src[i];
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OtsForcePMI(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OTS_PMI, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OtsForceBDIP(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OTS_BDIP, theValue);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OtsForceBDIO(TSPII_OscMapperFpgaChannel theOsc, bool theValue)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_OOS_OVERHEAD_TRANSMIT, OSC_FPGA_OTS_BDIO, theValue);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::RsGetCVCount(TSPII_OscMapperFpgaChannel theOsc)
{
    uint16 current   = myOscDrv.ChannelRead(theOsc, OSC_FPGA_B1_ERROR_COUNTER);
    uint16 count     = current - myLastCV[theOsc];
    myLastCV[theOsc] = current;
    return myCVCount[theOsc] += (uint32)count;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::RsGetLOF(TSPII_OscMapperFpgaChannel theOsc)
{
    uint32 & count = myRsLOF[theOsc];

	/*This is for front panel optics
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_INGRESS_ALARM_STATUS) & OSC_FPGA_LOF) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_INGRESS_ALARM_LATCH, OSC_FPGA_LOF)  != 0;
	*/
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS) & OSC_FPGA_BAM_LOF) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_LATCH, OSC_FPGA_BAM_LOF)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::RsGetOOF(TSPII_OscMapperFpgaChannel theOsc)
{
    uint32 & count = myRsOOF[theOsc];

	/*This is for front panel optics
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_INGRESS_ALARM_STATUS) & OSC_FPGA_OOF) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_INGRESS_ALARM_LATCH, OSC_FPGA_OOF)  != 0;
	*/
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS) & OSC_FPGA_BAM_OOF) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_LATCH, OSC_FPGA_BAM_OOF)  != 0;
    return UPDATE_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::RsSetSignalType(CT_TEL_SignalType theSignalType)
{
    switch (theSignalType)
    {
    case CT_TEL_SIGNAL_E1:
        myOscDrv.ReadModWrBool(OSC_FPGA_MAPPER_CONFIGURATION, OSC_FPGA_FORMAT_E1, true);
		/* @ TO DO: Fix me
        CSPII_Spm8560Layer3Switch::GetInstance()->SetPortInterframeGap(BCM_EAST_PORT_FD, 0x5b);  
        CSPII_Spm8560Layer3Switch::GetInstance()->SetPortInterframeGap(BCM_WEST_PORT_FD, 0x5b);  
		*/
        break;
    case CT_TEL_SIGNAL_OC3:
    case CT_TEL_SIGNAL_UNKNOWN:
        myOscDrv.ReadModWrBool(OSC_FPGA_MAPPER_CONFIGURATION, OSC_FPGA_FORMAT_E1, false);
		/* @TO DO: Fix me
        CSPII_Spm8560Layer3Switch::GetInstance()->SetPortInterframeGap(BCM_EAST_PORT_FD, 0x15);  
        CSPII_Spm8560Layer3Switch::GetInstance()->SetPortInterframeGap(BCM_WEST_PORT_FD, 0x15);  
		*/
        break;
    default:
        FC_THROW_ERROR(FC_InvalidArgumentError, "Unexpected OSC signal type");
    }
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_SignalType TSPII_OscMapperFpgaCtrl::RsGetSignalType() const
{
    uint16 value = myOscDrv.Read(OSC_FPGA_MAPPER_CONFIGURATION) & OSC_FPGA_FORMAT_E1;
    return value ? CT_TEL_SIGNAL_E1 : CT_TEL_SIGNAL_OC3;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OptGetLaserState(TSPII_OscMapperFpgaChannel theOsc)
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_DISABLE_LASER) == 0;
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OptGetOptLOS(TSPII_OscMapperFpgaChannel theOsc)
{
	/* This is for front panel optics
    uint32 & count = myOptLOS[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_STATUS) &       OSC_FPGA_LOL_DETECT) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_CHANNEL_STATUS_LATCH, OSC_FPGA_LOL_DETECT) != 0;
    return UPDATE_COUNT;
	*/
	

	//OPT LOS is read from the Amps. When we support front panel optics, this will have to change to read either
	//from the front panel optics or the Amps
	unsigned int theUnit = TSPII_L2P; //Line2Port
	uint32 theSlot = GetOscInputAmpSlot(theOsc);
	uint32 theIndex = 4; // for OSC drop LOS
	
	TSPII_PipeRegion* theRegion = TSPII_SubApplication::GetInstance()->GetPipe(theUnit, theSlot);
	if (!theRegion)
	{
		FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve PII Pipe region for OSC channel LOS");
	}

	TSPII_PipeIf& aPipePii        = (*theRegion)[0];
	return (aPipePii.GetLOS(theIndex));
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::OptGetLossOfClock(TSPII_OscMapperFpgaChannel theOsc)
{
	/*
    uint32 & count = myOptLossOfClock[theOsc];
    bool     value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_STATUS) &       OSC_FPGA_LOS_DETECT) != 0;
    bool     event = myOscDrv.ChannelReadW1C(theOsc, OSC_FPGA_CHANNEL_STATUS_LATCH, OSC_FPGA_LOS_DETECT) != 0;
    return UPDATE_COUNT;
	*/
	//How do we get loss of clock for the OSC channels now??
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Get OSC power transmitted by the peer NE
////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetPowerTransmittedByPeer(TSPII_OscMapperFpgaChannel theOsc)
{
	uint16 rxVal = myOscDrv.ChannelRead(theOsc, OSC_FPGA_RECEIVE_POWER_VALUE);
	float rxVal_mB = (float)((float)rxVal * 0.01) - 40;
    CT_TEL_mBm rxVal_mBm = (CT_TEL_mBm)(rxVal_mB*100);
    return(rxVal_mBm); 
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetOpticalPowerTransmitted(TSPII_OscMapperFpgaChannel theOsc)
{
    CT_TEL_mBm thePower = TRAFFIC_DEFAULT_POWER;
    uint32 theSlot = GetOscInputAmpSlot(theOsc);
    if (myCADMSupported)
    {
        TSPII_CardNanoCoreCtrl* ctrl = TSPII_Spm8560SubApplication::GetSpecificInstance().GetNanoCoreCtrl(theSlot);
        if (!ctrl)
        {
            FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve NanoCoreCtrl for OSC channel Tx Power");
        }
        thePower = ctrl->GetOscAddPower();
    }
    else
    {
        TSPII_CardInputAmpOlimCtrl* theAmp = TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[theSlot-1]->myCardInputAmpOlimCtrl;
        if (!theAmp)
        {
        FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve InputAmpOlimCtrl for OSC channel Tx Power");
        }
        return theAmp->GetOscAddPower();
    }

    return thePower;
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetOpticalPowerReceived(TSPII_OscMapperFpgaChannel theOsc)
{
    CT_TEL_mBm thePower = TRAFFIC_DEFAULT_POWER;
	uint32 theSlot = GetOscInputAmpSlot(theOsc);
    if (myCADMSupported)
    {
        TSPII_CardNanoCoreCtrl* ctrl = TSPII_Spm8560SubApplication::GetSpecificInstance().GetNanoCoreCtrl(theSlot);
        if (!ctrl)
        {
                FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve NanoCoreCtrl for OSC channel Rx Power");
        }
        thePower = ctrl->GetOscDropPower();
    }
    else
    {
        TSPII_CardInputAmpOlimCtrl* theAmp = TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[theSlot-1]->myCardInputAmpOlimCtrl;
        if (!theAmp)
        {
            FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve InputAmpOlimCtrl for OSC channel Rx Power");
        }
        thePower = theAmp->GetOscDropPower();
    }

	return thePower;
}

////////////////////////////////////////////////////////////////////////////////
// Set OSC power transmitted to the peer NE
////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc, CT_TEL_mBm thePower)
{
	float txVal_mB = (float)((float)thePower/100.0);
	uint16 aValue = (uint16)((txVal_mB + 40)/0.01);
	myOscDrv.ChannelWrite(theOsc, OSC_FPGA_TRANSMIT_POWER_VALUE, aValue);
}

////////////////////////////////////////////////////////////////////////////////
// Get OSC power transmitted to the peer NE
////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc)
{
	uint16 txVal = myOscDrv.ChannelRead(theOsc, OSC_FPGA_TRANSMIT_POWER_VALUE);
	float txVal_mB = (float)((float)txVal * 0.01) - 40;
    CT_TEL_mBm txVal_mBm = (CT_TEL_mBm)(txVal_mB*100);
    return(txVal_mBm); 
}

////////////////////////////////////////////////////////////////////////////////
// Get OMS power transmitted by the peer NE
////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetOmsPowerTransmittedByPeer(TSPII_OscMapperFpgaChannel theOsc)
{
    uint16 rxVal = myOscDrv.ChannelRead(theOsc, OSC_FPGA_K1_K2_RECEIVE);
    float rxVal_mB = (float)((float)rxVal * 0.01) - 99;
    CT_TEL_mBm rxVal_mBm = (CT_TEL_mBm)(rxVal_mB*100);
    return(rxVal_mBm);
}

////////////////////////////////////////////////////////////////////////////////
// Set OMS power transmitted to the peer NE
////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetOmsPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc, CT_TEL_mBm thePower)
{
    float txVal_mB = (float)(((float)thePower)/100.0);
    uint16 aValue = (uint16)((txVal_mB + 99)/0.01);
    myOscDrv.ChannelWrite(theOsc, OSC_FPGA_K1_K2_TRANSMIT, aValue);
}

////////////////////////////////////////////////////////////////////////////////
// Get OMS power transmitted to the peer NE
////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetOmsPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc)
{
    uint16 txVal = myOscDrv.ChannelRead(theOsc, OSC_FPGA_K1_K2_TRANSMIT);
    float txVal_mB = (float)((float)txVal * 0.01) - 99;
    CT_TEL_mBm txVal_mBm = (CT_TEL_mBm)(txVal_mB*100);
    return(txVal_mBm);
}

CT_TEL_mBm TSPII_OscMapperFpgaCtrl::OptGetOmsPowerTransmitted(TSPII_OscMapperFpgaChannel theOsc)
{
    CT_TEL_mBm thePower = TRAFFIC_DEFAULT_POWER;
    uint32 theSlot = GetOscInputAmpSlot(theOsc);
    if (myCADMSupported)
    {
        TSPII_CardNanoCoreCtrl* ctrl = TSPII_Spm8560SubApplication::GetSpecificInstance().GetNanoCoreCtrl(theSlot);
        if (!ctrl)
        {
            FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve NanoCoreCtrl for OMS Tx Power");
        }
        thePower = ctrl->GetLineOutOmsPower();
    }
    else
    {
        TSPII_CardInputAmpOlimCtrl* theAmp = TSPII_Spm8560SubApplication::GetSpecificInstance().mySlaveSlot[theSlot-1]->myCardInputAmpOlimCtrl;
        if (!theAmp)
        {
            FC_THROW_ERROR(FC_RuntimeError, "Unable to retrieve InputAmpOlimCtrl for OMS Tx Power");
        }
        return theAmp->GetLineOutOmsPower();
    }

    return thePower;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetLaserEnable(TSPII_OscMapperFpgaChannel theOsc, bool theEnable)
{
    myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_DISABLE_LASER, !theEnable);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetFacilityLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc, bool theEnable)
{
    if (myOscDrv.Read(OSC_FPGA_MAPPER_CONFIGURATION) & OSC_FPGA_FORMAT_E1)
    {
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_OPT_FAC_LOOP_CTRL, theEnable);
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_FACILITY_LOOPBACK, 0);
    }
    else
    {
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_FACILITY_LOOPBACK, theEnable);
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_OPT_FAC_LOOP_CTRL, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetTerminalLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc, bool theEnable)
{
    if (myOscDrv.Read(OSC_FPGA_MAPPER_CONFIGURATION) & OSC_FPGA_FORMAT_E1)
    {
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_OPT_EQUIP_LOOP_CTRL, theEnable);
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_EQUIPMENT_LOOPBACK, 0);
    }
    else
    {
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_EQUIPMENT_LOOPBACK, theEnable);
        myOscDrv.ChannelReadModWrBool(theOsc, OSC_FPGA_CHANNEL_CONTROL, OSC_FPGA_OPT_EQUIP_LOOP_CTRL, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OptGetLaserEnable(TSPII_OscMapperFpgaChannel theOsc) const
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_DISABLE_LASER) == 0;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OptGetFacilityLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc) const
{
    bool value = false;
    if (myOscDrv.Read(OSC_FPGA_MAPPER_CONFIGURATION) & OSC_FPGA_FORMAT_E1)
    {
        value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_OPT_FAC_LOOP_CTRL) != 0;
    }
    else
    {
        value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_FACILITY_LOOPBACK) != 0;
    }
    return value;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::OptGetTerminalLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc) const
{
    bool value = false;
    if (myOscDrv.Read(OSC_FPGA_MAPPER_CONFIGURATION) & OSC_FPGA_FORMAT_E1)
    {
        value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_OPT_EQUIP_LOOP_CTRL) != 0;
    }
    else
    {
        value = (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_CONTROL) & OSC_FPGA_EQUIPMENT_LOOPBACK) != 0;
    }
    return value;
}

////////////////////////////////////////////////////////////////////////////////
// OptSetOpticalSwitchControl(bool theEnable)
// 
// This method is used to assert/negate the OLA optical switch on the LIAME/LRAME
// input amplifiers at slots 1, 5, 13 and 19 simultaneously.
// 
// Prior to calling this method it is required that the amps first be armed and
// that the arming state is verified at each amplifier. 
// 
// See TSPII_CntrlLxameOsaCtrlAction() for all methods associated with arming, 
// arming status, arming timout, disarming and switch position status.
// 
// Note: This method uses register 0x0108 to activate the OLA optical upgrade switch.
//       Any of the following register write commands will also set the switch 
//       on all 4 amplifier slots:
// 
//       setting bit 1 in register 0x0108 will assert all 4 outputs OR
//       setting bit 1 in register 0x1108 will assert all 4 outputs OR
//       setting bit 1 in register 0x2108 will assert all 4 outputs OR
//       setting bit 1 in register 0x3108 will assert all 4 outputs 
////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetOpticalSwitchControl(bool theEnable)
{
    myOscDrv.ChannelReadModWrBool(OSC_FPGA_CHANNEL1, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_CONTROL, OSC_FPGA_OPTICAL_SWITCH_CONTROL, theEnable); 
}

////////////////////////////////////////////////////////////////////////////////
//
// 
// Note: This method uses register 0x0108 to convey SPM mastership to the LxamE.
//
// 
//       setting bit 2 in register 0x0108 will assert all 4 outputs OR
//       setting bit 2 in register 0x1108 will assert all 4 outputs OR
//       setting bit 2 in register 0x2108 will assert all 4 outputs OR
//       setting bit 2 in register 0x3108 will assert all 4 outputs 
////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaCtrl::OptSetSwitchMastershipControl(bool theMaster)
{
    myOscDrv.ChannelReadModWrBool(OSC_FPGA_CHANNEL1, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_CONTROL, OSC_FPGA_MASTERSHIP_CONTROL, theMaster); 
}


////////////////////////////////////////////////////////////////////////////////
//Utility function
CT_SlotId TSPII_OscMapperFpgaCtrl::GetOscInputAmpSlot(TSPII_OscMapperFpgaChannel theOsc)
{
    //NOTE: There is a conversion required here between the mapper channel
    //and the input amp slots based on configuration type
	//2 conversions are possible

    //The first is for configurations that use the LxAME based cards	
	//A(1)   OSC_FPGA_CHANNEL1
    //B(19)  OSC_FPGA_CHANNEL2
    //C(5)   OSC_FPGA_CHANNEL3
	//D(13)  OSC_FPGA_CHANNEL4
	//------------------------------------------------------------------

    //The second is for configurations that use the CADM based cards
	//A(1)   OSC_FPGA_CHANNEL1
    //C(5)   OSC_FPGA_CHANNEL2
	//B(13)  OSC_FPGA_CHANNEL3
	//D(9)   OSC_FPGA_CHANNEL4
	//------------------------------------------------------------------

    CT_SlotId theSlot = 0;
    if (myCADMSupported)
    {
	    switch(theOsc)
	    {
	    case OSC_FPGA_CHANNEL1:
		    theSlot = CADM_FP3_A;
		    break;
	    case OSC_FPGA_CHANNEL2:
		    theSlot = CADM_FP3_C;
		    break;
	    case OSC_FPGA_CHANNEL3:
		    theSlot = CADM_FP3_B;
		    break;
	    case OSC_FPGA_CHANNEL4:
		    theSlot = CADM_FP3_D;
		    break;
	    default:
		    fc_cout << "Invalid OSC channel specified" << endl;
		    break;
	    }
    }
    else
    {
	    switch(theOsc)
	    {
	    case OSC_FPGA_CHANNEL1:
		    theSlot = LIAM_1;
		    break;
	    case OSC_FPGA_CHANNEL2:
		    theSlot = LIAM_5;
		    break;
	    case OSC_FPGA_CHANNEL3:
		    theSlot = LIAM_13;
		    break;
	    case OSC_FPGA_CHANNEL4:
		    theSlot = LIAM_19;
		    break;
	    default:
		    fc_cout << "Invalid OSC channel specified" << endl;
		    break;
	    }
    }

	return theSlot;
}

////////////////////////////////////////////////////////////////////////////////
//BRAM for OCH overhead signaling is split up into 2 sections. One section covers
//och 0-63 and the other 64-87. So a conversion is needed to make the second one
//start at index 0
/////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OscMapperFpgaCtrl::GetAdjustedOchChanNum(uint32 theOchNum)
{
    if (theOchNum >=OSC_FPGA_OCH_64_VAL)
        return (theOchNum - OSC_FPGA_OCH_64_VAL);
    else
        return theOchNum;
}

////////////////////////////////////////////////////////////////////////////////
// Check for AMCC Chip failure - if return TRUE, then chip is BAD!
////////////////////////////////////////////////////////////////////////////////
bool TSPII_OscMapperFpgaCtrl::GetAMCCStatusFailure (TSPII_OscMapperFpgaChannel theOsc) const
{
    return (myOscDrv.ChannelRead(theOsc, OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS) & OSC_FPGA_OC3_TX_19M_CLOCK_OUT_OF_RANGE);
}

