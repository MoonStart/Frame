#ifndef _TSPII_PIPEIF_H
#define _TSPII_PIPEIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"

// constants to size array members of this class
//****************************************************************
//   WARNING    WARNING    WARNING    WARNING    WARNING
// Make sure these array size constants are large enough for the 
// application specific maximums declared below.
//****************************************************************
const uint32 TSPII_MAX_NUM_OF_LOS_IN_PIPE = 7;
const uint32 TSPII_MAX_NUM_OF_GAIN_IN_PIPE = 88;
const uint32 TSPII_MAX_NUM_OF_GAIN_TILT_IN_PIPE = 1;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_PIPE = TSPII_MAX_NUM_OF_GAIN_IN_PIPE;
const uint32 TSPII_MAX_NUM_OF_ACTIVE_PATH_IN_PIPE = TSPII_MAX_NUM_OF_GAIN_IN_PIPE;

// constants to define application specific maximums
const uint32 TSPII_MAX_NUM_OF_LOS_IN_RCMM_L2P_PIPE = 2;
const uint32 TSPII_MAX_NUM_OF_GAIN_IN_RCMM_L2P_PIPE = 3;

const uint32 TSPII_MAX_NUM_OF_LOS_IN_RCMM_P2L_PIPE = 2;
const uint32 TSPII_MAX_NUM_OF_GAIN_IN_RCMM_P2L_PIPE = 1;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_RCMM_P2L_PIPE = 44;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_RCMM88_P2L_PIPE = 88;

// NANO specific constants
const uint32 TSPII_MAX_NUM_OF_GAIN_IN_NANO_PIPE = 1;
const uint32 TSPII_MAX_NUM_OF_LOS_IN_NANO_OLA_L2P_PIPE = 5;
const uint32 TSPII_MAX_NUM_OF_LOS_IN_NANO_OLA_P2L_PIPE = 3;
const uint32 TSPII_MAX_NUM_OF_LOS_IN_NANO_CCM_L2P_PIPE = 5;
const uint32 TSPII_MAX_NUM_OF_LOS_IN_NANO_CCM_P2L_PIPE = 7;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_NANO_CCM_PIPE = 44;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_NANO_CCM_P2L_PIPE = TSPII_MAX_NUM_OF_EVOA_IN_NANO_CCM_PIPE;  // One of 44 possible channels mapped to a evoa port
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_NANO_CCM_L2P_PIPE = TSPII_MAX_NUM_OF_EVOA_IN_NANO_CCM_PIPE;
const uint32 TSPII_MAX_NUM_OF_EVOA_IN_NANO_OLA_PIPE = 0;

const uint32 TSPII_MAX_NUM_OF_EVOA_PORTS_IN_NANO_CCM_P2L_PIPE = 8;

class TSPII_PipeIf : public TSPII_BaseIf
{
public:
    /* Constructor */   TSPII_PipeIf(bool theDefault = false, uint32 theNumberOfLOS = 1, uint32 theNumberOfGain = 1,
                                     uint32 theNumberOfEvoa = 0, uint32 theNumberOfActivePath = 0,
                                     uint32 theNumberOfEvoaPorts = 0);
    virtual             ~TSPII_PipeIf();
    virtual void        Reset();

    // -----------------------------------------------------------------------------------
    // Pipe Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_TEL_mBm  GetOutputPower();
    virtual CT_TEL_mBm  GetInputPower();
    virtual CT_TEL_mBm  GetAlternatePower();
    virtual CT_TEL_mBm  GetDcmOutputPower();
    virtual CT_TEL_mBm  GetDcmInputPower();
    virtual CT_TEL_mBm  GetMinGain();
    virtual CT_TEL_mBm  GetMaxGain();
    virtual uint32      GetLOS(uint32 theIndex = 0);
    virtual CT_TEL_mBm  GetActualGroupEvoa();
    virtual CT_TEL_mBm  GetActualEvoa(uint32 theIndex = 0);
    virtual bool        GetOutputPowerLimited();
    virtual bool        GetOutOfGain();
    virtual uint32      GetNumberOfGain();
    virtual void        SetNumberOfGain(uint32 theNumberOfGain);
    virtual uint32      GetNumberOfEvoa();
    virtual void        SetNumberOfEvoa(uint32 theNumberOfEvoa);
    virtual uint32      GetNumberOfLOS();
    virtual uint32      GetNumberOfActivePath();
    virtual CT_TEL_mBm  GetOpticalOverloadThreshold();
    virtual CT_TEL_mBm  GetAopeThreshold();
    virtual CT_TEL_mBm  GetInputLowThreshold();
    virtual CT_TEL_mBm  GetInputUpThreshold();
    virtual CT_TEL_mBm  GetOutputLowThreshold();
    virtual CT_TEL_mBm  GetOutputUpThreshold();

    // -----------------------------------------------------------------------------------
    // Pipe Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void        SetGain(CT_TEL_mBm theGain, uint32 theIndex = 0);

                        // write the gain values to hardware
    virtual void        CommitGains();

    virtual CT_TEL_mBm  GetGain(uint32 theIndex = 0) const;
    
    virtual void        SetActualGain(CT_TEL_mBm theGain, uint32 theIndex = 0);
    virtual CT_TEL_mBm  GetActualGain(uint32 theIndex = 0);

    // New methods for pipes with group evoas
    virtual void        SetGroupEvoa(CT_TEL_mBm theEvoa);
    virtual CT_TEL_mBm  GetGroupEvoa() const;

    // New methods for pipes with evoas
    virtual void        SetEvoa(CT_TEL_mBm theGain, uint32 theIndex = 0);
    virtual void        SetCfgEvoa(CT_TEL_mBm theGain, uint32 theIndex);

                        // write the evoa values to hardware
    virtual void        CommitEvoas();

    virtual CT_TEL_mBm  GetEvoa(uint32 theIndex = 0) const;
    virtual CT_TEL_mBm  GetCfgEvoa(uint32 theIndex) const;

    virtual void        SetPortNumber(uint8 thePortIndex, uint32 theIndex = 0);

    virtual uint8       GetPortNumber(uint32 theIndex = 0) const;

    virtual void        SetActivePath(uint32 theIndex, bool theEnable);

    virtual bool        GetActivePath(uint32 theIndex) const;

    virtual CT_TEL_mBm  GetGainTilt(void) const;
    virtual void        SetGainTilt(CT_TEL_mBm theTilt);

    virtual bool        IsRefreshNeeded(void) const;
    virtual void        SetRefreshNeeded(bool theState);

    virtual void        SetInputLowThreshold(CT_TEL_mBm theInputLowThreshold);
    virtual void        SetInputUpThreshold(CT_TEL_mBm theInputUpThreshold);
    virtual void        SetOutputLowThreshold(CT_TEL_mBm theOutputLowThreshold);
    virtual void        SetOutputUpThreshold(CT_TEL_mBm theOutputUpThreshold);

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   & WriteObject(ostream & theStream);
    virtual istream   & ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void         RefreshGet();
    void         RefreshSet();

    uint32       itsNumberOfLOS;
    uint32       itsNumberOfGain;
    uint32       itsNumberOfEvoa;
    uint32       itsNumberOfActivePath;
    uint32       itsNumberOfEvoaPorts;

    // Monitoring
    CT_TEL_mBm   itsInputPower;
    CT_TEL_mBm   itsOutputPower;
    CT_TEL_mBm   itsAlternatePower;
    CT_TEL_mBm   itsDcmInputPower;
    CT_TEL_mBm   itsDcmOutputPower;
    CT_TEL_mBm   itsMinGain;
    CT_TEL_mBm   itsMaxGain;
    uint32       itsLOS[TSPII_MAX_NUM_OF_LOS_IN_PIPE];
    CT_TEL_mBm   itsActualGain[TSPII_MAX_NUM_OF_GAIN_IN_PIPE];
    CT_TEL_mBm   itsActualGroupEvoa;
    CT_TEL_mBm   itsActualEvoa[TSPII_MAX_NUM_OF_EVOA_IN_PIPE];
    bool         itsOutputPowerLimited;
    bool         itsOutOfGain;
    CT_TEL_mBm   itsOpticalOverloadThreshold;
    CT_TEL_mBm   itsAopeThreshold;
    CT_TEL_mBm   itsInputLowThreshold;
    CT_TEL_mBm   itsInputUpThreshold;
    CT_TEL_mBm   itsOutputLowThreshold;
    CT_TEL_mBm   itsOutputUpThreshold;

    // Configuration attributes
    CT_TEL_mBm   itsGainTilt;
    CT_TEL_mBm   itsGain[TSPII_MAX_NUM_OF_GAIN_IN_PIPE];
    CT_TEL_mBm   itsGroupEvoa;
    CT_TEL_mBm   itsEvoa[TSPII_MAX_NUM_OF_EVOA_IN_PIPE];
    uint8        itsEvoaChannelPort[TSPII_MAX_NUM_OF_EVOA_IN_PIPE];
    bool         itsActivePath[TSPII_MAX_NUM_OF_ACTIVE_PATH_IN_PIPE];

    // CFG coordination
    bool         itsRefreshNeeded;
};

#endif // _TSPII_PIPEIF_H
