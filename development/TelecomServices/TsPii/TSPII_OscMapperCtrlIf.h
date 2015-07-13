#ifndef TSPII_OSCMAPPERCTRLIF_H
#define TSPII_OSCMAPPERCTRLIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPMNANO
 DESCRIPTION : Pure Virtual OSC Controller Class API
--------------------------------------------------------------------------*/

#include "ss_gdef.h"                          // for uint32 definition
#include "CommonTypes/CT_G709Trace.h"         // for CT_G709Trace definition
#include "CommonTypes/CT_SDH16ByteTrace.h"    // for CT_G709Trace definition
#include "CommonTypes/CT_Telecom.h"           // for CT_TEL_SignalType definition
#include "TsPii/TSPII_Region.h"               // for TSPII_MAX_OSC/TSPII_MAX_OCH

typedef uint8 TSPII_OscChannel;

class TSPII_OscMapperCtrlIf
{
public:
    /* Constructor */             TSPII_OscMapperCtrlIf(TSPII_OscChannel theOsc=0);
    virtual                       ~TSPII_OscMapperCtrlIf() {};

    virtual void                  Init() = 0;
    virtual void                  Refresh() = 0;
    virtual void                  Reset() = 0;

    // OCh methods
    virtual uint32                OchGetOCI      (uint32 theOch) = 0;
    virtual uint32                OchGetFDIP     (uint32 theOch) = 0;
    virtual uint32                OchGetFDIO     (uint32 theOch) = 0;
    virtual bool                  OchGetForceOCI (uint32 theOch) = 0;
    virtual bool                  OchGetForceFDIP(uint32 theOch) = 0;
    virtual bool                  OchGetForceFDIO(uint32 theOch) = 0;
    virtual void                  OchForceOCI    (uint32 theOch, bool theValue) = 0;
    virtual void                  OchForceFDIP   (uint32 theOch, bool theValue) = 0;
    virtual void                  OchForceFDIO   (uint32 theOch, bool theValue) = 0;

    // OMS methods
    virtual uint32                OmsGetPMI      (void) = 0;
    virtual uint32                OmsGetBDIP     (void) = 0;
    virtual uint32                OmsGetBDIO     (void) = 0;
    virtual uint32                OmsGetFDIP     (void) = 0;
    virtual uint32                OmsGetFDIO     (void) = 0;
    virtual bool                  OmsGetForcePMI (void) = 0;
    virtual bool                  OmsGetForceBDIP(void) = 0;
    virtual bool                  OmsGetForceBDIO(void) = 0;
    virtual bool                  OmsGetForceFDIP(void) = 0;
    virtual bool                  OmsGetForceFDIO(void) = 0;
    virtual void                  OmsForcePMI    (bool theValue) = 0;
    virtual void                  OmsForceBDIP   (bool theValue) = 0;
    virtual void                  OmsForceBDIO   (bool theValue) = 0;
    virtual void                  OmsForceFDIP   (bool theValue) = 0;
    virtual void                  OmsForceFDIO   (bool theValue) = 0;

    // OTS methods
    virtual const CT_G709Trace &  OtsGetRxTTI    (void) = 0;
    virtual uint32                OtsGetPMI      (void) = 0;
    virtual uint32                OtsGetBDIP     (void) = 0;
    virtual uint32                OtsGetBDIO     (void) = 0;
    virtual const CT_G709Trace &  OtsGetTxTTI    (void) = 0;
    virtual bool                  OtsGetForcePMI (void) = 0;
    virtual bool                  OtsGetForceBDIP(void) = 0;
    virtual bool                  OtsGetForceBDIO(void) = 0;
    virtual void                  OtsSetTxTTI    (const CT_G709Trace & theTrace) = 0;
    virtual void                  OtsForcePMI    (bool theValue) = 0;
    virtual void                  OtsForceBDIP   (bool theValue) = 0;
    virtual void                  OtsForceBDIO   (bool theValue) = 0;

    // RS methods
    virtual uint32                RsGetCVCount   (void) = 0;
    virtual uint32                RsGetLOF       (void) = 0;
    virtual uint32                RsGetOOF       (void) = 0;
    virtual void                  RsSetSignalType(CT_TEL_SignalType theSignalType) = 0;
    virtual CT_TEL_SignalType     RsGetSignalType(void) const = 0;
    virtual CT_SDH16ByteTrace &   RsGetRxTrace   (void) = 0;
    virtual void                  RsSetTxTrace   (const CT_SDH16ByteTrace & theTrace) = 0;
    virtual CT_SDH16ByteTrace &   RsGetTxTrace   (void) = 0;

    // Optical method
    virtual bool                  OptGetLaserState               (void) = 0;
    virtual uint32                OptGetOptLOS                   (void) = 0;
    virtual uint32                OptGetLossOfClock              (void) = 0;
    virtual CT_TEL_mBm            OptGetPowerTransmittedByPeer   (void) = 0;
    virtual CT_TEL_mBm            OptGetOpticalPowerTransmitted  (void) = 0;
    virtual CT_TEL_mBm            OptGetOpticalPowerReceived     (void) = 0;
    virtual CT_TEL_mBm            OptGetPowerTransmittedToPeer   (void) = 0;
    virtual void                  OptSetPowerTransmittedToPeer   (CT_TEL_mBm thePower) = 0;

    virtual CT_TEL_mBm            OptGetOmsPowerTransmittedByPeer(void) = 0;
    virtual CT_TEL_mBm            OptGetOmsPowerTransmittedToPeer(void) = 0;
    virtual void                  OptSetOmsPowerTransmittedToPeer(CT_TEL_mBm thePower) = 0;
    virtual CT_TEL_mBm            OptGetOmsPowerTransmitted      (void) = 0;

    virtual void                  OptSetLaserEnable           (bool theEnable) = 0;
    virtual void                  OptSetFacilityLoopbackEnable(bool theEnable) = 0;
    virtual void                  OptSetTerminalLoopbackEnable(bool theEnable) = 0;
    virtual bool                  OptGetLaserEnable           (void) const = 0;
    virtual bool                  OptGetFacilityLoopbackEnable(void) const = 0;
    virtual bool                  OptGetTerminalLoopbackEnable(void) const = 0;
    virtual void                  OptSetOpticalSwitchControl(bool theEnable) = 0;
    virtual void                  OptSetSwitchMastershipControl(bool theMaster) = 0;

    virtual bool                  OptGetLossOfDcmLock(void){return false;};
    virtual void                  OptResetSerdes(){};

    //MS methods
    virtual CT_FAC_RxSsm          MsGetRxSsm(void) = 0;
    virtual void                  MsSetTxSsm(CT_FAC_RxSsm theSsm) = 0;
    virtual CT_FAC_RxSsm          MsGetTxSsm(void) const = 0;
    virtual void                  MsSetOscTxTimingMode(CT_TEL_DT_Source_Mode theDTSourceMode) = 0;
    virtual CT_TEL_DT_Source_Mode MsGetOscTxTimingMode(void) const = 0;

    virtual void                  DisplayContent(int argc, char ** argv) = 0;
    virtual bool                  GetLinkState(void) = 0;
    virtual void                  SetEthDestAddr(uint8 * aMac) = 0;
    virtual void                  SetEthSrcAddr(uint8 * aMac) = 0;
    virtual void                  EnableOscChannel(bool theEnable) = 0;
    virtual void                  SetTxFifoCfg(uint16 hiWM, uint16 loWM) = 0;
    virtual bool                  IsLoopbackDetected(void) = 0;
    virtual void                  SetMcnVid(uint16 aTag) = 0;
    virtual void                  SetScnVid(uint16 aTag) = 0;

protected:

    uint32                        myOchOCI[TSPII_MAX_OCH];
    uint32                        myOchFDIP[TSPII_MAX_OCH];
    uint32                        myOchFDIO[TSPII_MAX_OCH];
    uint32                        myOmsPMI;
    uint32                        myOmsBDIP;
    uint32                        myOmsBDIO;
    uint32                        myOmsFDIP;
    uint32                        myOmsFDIO;
    uint32                        myOtsPMI;
    uint32                        myOtsBDIP;
    uint32                        myOtsBDIO;
    uint32                        myRsLOF;
    uint32                        myRsOOF;
    uint32                        myOptLOS;
    uint32                        myOptLossOfClock;
    uint32                        myCVCount;
    uint16                        myLastCV;
    CT_G709Trace                  myOtsRxTTI;
    CT_G709Trace                  myOtsTxTTI;
    CT_SDH16ByteTrace             myRsTxTrace;
    CT_SDH16ByteTrace             myRsRxTrace;

    TSPII_OscChannel              myOscChannel;
};

#endif /* TSPII_OSCMAPPERCTRLIF_H */
