/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : Device control for OSC mapper FPGA on SPM8560
--------------------------------------------------------------------------*/
#ifndef TSPII_OSCMAPPERFPGACTRL_H
#define TSPII_OSCMAPPERFPGACTRL_H

#include "ss_gdef.h"                          // for uint32 definition
#include "CommonTypes/CT_G709Trace.h"         // for CT_G709Trace definition
#include "CommonTypes/CT_Telecom.h"           // for CT_TEL_SignalType definition
#include "TsPii/TSPII_Region.h"               // for TSPII_MAX_OSC/TSPII_MAX_OCH
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h" // for TSPII_OscMapperFpgaChannel definition

class TSPII_OscMapperFpgaCtrl
{
public:
    static TSPII_OscMapperFpgaCtrl & GetInstance();
    static void              DeleteInstance();

    virtual                  ~TSPII_OscMapperFpgaCtrl();
    void                     Init();
    void                     Refresh();
    void                     Reset();

    // OCh methods
    uint32                   OchGetOCI      (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    uint32                   OchGetFDIP     (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    uint32                   OchGetFDIO     (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    bool                     OchGetForceOCI (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    bool                     OchGetForceFDIP(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    bool                     OchGetForceFDIO(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    void                     OchForceOCI    (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue);
    void                     OchForceFDIP   (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue);
    void                     OchForceFDIO   (TSPII_OscMapperFpgaChannel theOsc, uint32 theOch, bool theValue);

    // OMS methods
    uint32                   OmsGetPMI      (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OmsGetBDIP     (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OmsGetBDIO     (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OmsGetFDIP     (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OmsGetFDIO     (TSPII_OscMapperFpgaChannel theOsc);
    bool                     OmsGetForcePMI (TSPII_OscMapperFpgaChannel theOsc);
    bool                     OmsGetForceBDIP(TSPII_OscMapperFpgaChannel theOsc);
    bool                     OmsGetForceBDIO(TSPII_OscMapperFpgaChannel theOsc);
    bool                     OmsGetForceFDIP(TSPII_OscMapperFpgaChannel theOsc);
    bool                     OmsGetForceFDIO(TSPII_OscMapperFpgaChannel theOsc);
    void                     OmsForcePMI    (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OmsForceBDIP   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OmsForceBDIO   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OmsForceFDIP   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OmsForceFDIO   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);

    // OTS methods
    const CT_G709Trace &     OtsGetRxTTI    (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OtsGetPMI      (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OtsGetBDIP     (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OtsGetBDIO     (TSPII_OscMapperFpgaChannel theOsc);
    const CT_G709Trace &     OtsGetTxTTI    (TSPII_OscMapperFpgaChannel theOsc);
    bool                     OtsGetForcePMI (TSPII_OscMapperFpgaChannel theOsc);
    bool                     OtsGetForceBDIP(TSPII_OscMapperFpgaChannel theOsc);
    bool                     OtsGetForceBDIO(TSPII_OscMapperFpgaChannel theOsc);
    void                     OtsSetTxTTI    (TSPII_OscMapperFpgaChannel theOsc, const CT_G709Trace & theTrace);
    void                     OtsForcePMI    (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OtsForceBDIP   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);
    void                     OtsForceBDIO   (TSPII_OscMapperFpgaChannel theOsc, bool theValue);

    // RS methods
    uint32                   RsGetCVCount   (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   RsGetLOF       (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   RsGetOOF       (TSPII_OscMapperFpgaChannel theOsc);
    void                     RsSetSignalType(CT_TEL_SignalType theSignalType);
    CT_TEL_SignalType        RsGetSignalType() const;

    // Optical method
    bool                     OptGetLaserState               (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OptGetOptLOS                   (TSPII_OscMapperFpgaChannel theOsc);
    uint32                   OptGetLossOfClock              (TSPII_OscMapperFpgaChannel theOsc);
    CT_TEL_mBm               OptGetPowerTransmittedByPeer   (TSPII_OscMapperFpgaChannel theOsc);
	CT_TEL_mBm               OptGetOpticalPowerTransmitted  (TSPII_OscMapperFpgaChannel theOsc);
	CT_TEL_mBm               OptGetOpticalPowerReceived     (TSPII_OscMapperFpgaChannel theOsc);
    CT_TEL_mBm               OptGetPowerTransmittedToPeer   (TSPII_OscMapperFpgaChannel theOsc);
    void                     OptSetPowerTransmittedToPeer   (TSPII_OscMapperFpgaChannel theOsc, CT_TEL_mBm thePower);

    CT_TEL_mBm               OptGetOmsPowerTransmittedByPeer(TSPII_OscMapperFpgaChannel theOsc);
    CT_TEL_mBm               OptGetOmsPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc);
    void                     OptSetOmsPowerTransmittedToPeer(TSPII_OscMapperFpgaChannel theOsc, CT_TEL_mBm thePower);
    CT_TEL_mBm               OptGetOmsPowerTransmitted      (TSPII_OscMapperFpgaChannel theOsc);

    void                     OptSetLaserEnable           (TSPII_OscMapperFpgaChannel theOsc, bool theEnable);
    void                     OptSetFacilityLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc, bool theEnable);
    void                     OptSetTerminalLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc, bool theEnable);
    bool                     OptGetLaserEnable           (TSPII_OscMapperFpgaChannel theOsc) const;
    bool                     OptGetFacilityLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc) const;
    bool                     OptGetTerminalLoopbackEnable(TSPII_OscMapperFpgaChannel theOsc) const;
    void                     OptSetOpticalSwitchControl(bool theEnable);
	void                     OptSetSwitchMastershipControl(bool theMaster);

    bool                     GetAMCCStatusFailure (TSPII_OscMapperFpgaChannel theOsc) const;

private:
    /* Constructor */        TSPII_OscMapperFpgaCtrl();

    TSPII_OscMapperFpgaDrv & myOscDrv;
    uint32                   myOchOCI[TSPII_MAX_OSC*2][TSPII_MAX_OCH];
    uint32                   myOchFDIP[TSPII_MAX_OSC*2][TSPII_MAX_OCH];
    uint32                   myOchFDIO[TSPII_MAX_OSC*2][TSPII_MAX_OCH];
    uint32                   myOmsPMI[TSPII_MAX_OSC*2];
    uint32                   myOmsBDIP[TSPII_MAX_OSC*2];
    uint32                   myOmsBDIO[TSPII_MAX_OSC*2];
    uint32                   myOmsFDIP[TSPII_MAX_OSC*2];
    uint32                   myOmsFDIO[TSPII_MAX_OSC*2];
    uint32                   myOtsPMI[TSPII_MAX_OSC*2];
    uint32                   myOtsBDIP[TSPII_MAX_OSC*2];
    uint32                   myOtsBDIO[TSPII_MAX_OSC*2];
    uint32                   myRsLOF[TSPII_MAX_OSC*2];
    uint32                   myRsOOF[TSPII_MAX_OSC*2];
    uint32                   myOptLOS[TSPII_MAX_OSC*2];
    uint32                   myOptLossOfClock[TSPII_MAX_OSC*2];
    uint32                   myCVCount[TSPII_MAX_OSC*2];
    uint16                   myLastCV[TSPII_MAX_OSC*2];
    CT_G709Trace             myOtsRxTTI[TSPII_MAX_OSC*2];
    CT_G709Trace             myOtsTxTTI[TSPII_MAX_OSC*2];
    bool                     myCADMSupported;

    static TSPII_OscMapperFpgaCtrl * ourInstance;

	CT_SlotId                GetOscInputAmpSlot(TSPII_OscMapperFpgaChannel theOsc);
    uint32                   GetAdjustedOchChanNum(uint32 theOchNum);
};

#endif // TSPII_OSCMAPPERFPGACTRL_H
