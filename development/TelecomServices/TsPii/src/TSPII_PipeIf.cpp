/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_PipeIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_PipeIf::TSPII_PipeIf(bool theDefault, uint32 theNumberOfLOS, uint32 theNumberOfGain,
                           uint32 theNumberOfEvoa, uint32 theNumberOfActivePath,
                           uint32 theNumberOfEvoaPorts):
    TSPII_BaseIf(theDefault),
    itsNumberOfLOS(theNumberOfLOS),
    itsNumberOfGain(theNumberOfGain),
    itsNumberOfEvoa(theNumberOfEvoa),
    itsNumberOfActivePath(theNumberOfActivePath),
    itsNumberOfEvoaPorts(theNumberOfEvoaPorts)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PipeIf::~TSPII_PipeIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::RefreshGet()
{
    uint32 i;

    // Mon Attributes
    for (i=0; i < itsNumberOfLOS; i++)
        itsLOS[i] = GetLOS(i);
    itsInputPower  = GetInputPower();
    itsOutputPower = GetOutputPower();
    itsAlternatePower = GetAlternatePower();
    itsDcmInputPower  = GetDcmInputPower();
    itsDcmOutputPower = GetDcmOutputPower();
    itsMinGain  = GetMinGain();
    itsMaxGain = GetMaxGain();
    itsOutputPowerLimited = GetOutputPowerLimited();
    itsOpticalOverloadThreshold = GetOpticalOverloadThreshold();
    itsInputLowThreshold = GetInputLowThreshold();
    itsInputUpThreshold = GetInputUpThreshold();
    itsOutputLowThreshold = GetOutputLowThreshold();
    itsOutputUpThreshold = GetOutputUpThreshold();
    itsAopeThreshold = GetAopeThreshold();
    itsGainTilt = GetGainTilt();
    for (i=0; i<itsNumberOfGain; i++)
    {
        itsActualGain[i]  = GetActualGain(i);
        // Cfg Attributes
        itsGain[i]        = GetGain(i);
    }

    // Mon Atrribute
    itsActualGroupEvoa  = GetActualGroupEvoa();
    // Cfg Attribute
    itsGroupEvoa        = GetGroupEvoa();

    for (i=0; i< TSPII_MAX_NUM_OF_EVOA_IN_PIPE; i++)
    {
        itsEvoaChannelPort[i] = GetPortNumber(i);

        itsActualEvoa[i]  = GetActualEvoa(i);
        // Cfg Attributes
        itsEvoa[i]        = GetEvoa(i);
    }

    for (i=0; i<itsNumberOfActivePath; i++)
    {
        // Cfg Attributes
        itsActivePath[i]   = GetActivePath(i);
    }
    itsRefreshNeeded = IsRefreshNeeded();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::RefreshSet()
{
    uint32 i;
    for (i=0; i<itsNumberOfGain; i++)
    {
        SetGain(itsGain[i], i);
    }

    SetGroupEvoa(itsGroupEvoa);

    for (i=0; i<itsNumberOfEvoa; i++)
    {
        SetEvoa(itsEvoa[i], i);
        SetPortNumber(itsActivePath[i], CT_TEL_INVALID_PORT_NUMBER);
        SetActivePath(itsActivePath[i], false);
    }
    SetGainTilt(itsGainTilt);
    SetRefreshNeeded(itsRefreshNeeded);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::Reset()
{
    int i;

    TSPII_BaseIf::Reset();

    // Mon Attributes
    for (i=0; i < TSPII_MAX_NUM_OF_LOS_IN_PIPE; i++)
    {
        itsLOS[i] = 0;   
    }
    itsInputPower               = TRAFFIC_DEFAULT_POWER;
    itsOutputPower              = TRAFFIC_DEFAULT_POWER;
    itsAlternatePower           = TRAFFIC_DEFAULT_POWER;
    itsDcmInputPower            = TRAFFIC_DEFAULT_POWER;
    itsDcmOutputPower           = TRAFFIC_DEFAULT_POWER;
    itsMinGain                  = TRAFFIC_DEFAULT_POWER;
    itsMaxGain                  = TRAFFIC_DEFAULT_POWER;
    itsOutputPowerLimited       = false;
    itsOutOfGain                = false;
    // Newly defined CT_TEL_DEFAULT_AOPE_THRESHOLD is set to 999900, which is so high 
    // that it will turn off the defect. Use it for OPOVLD also.
    itsOpticalOverloadThreshold = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsInputLowThreshold        = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsInputUpThreshold         = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsOutputLowThreshold       = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsOutputUpThreshold        = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsAopeThreshold            = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    itsGainTilt                 = 0;

    for (i=0; i<TSPII_MAX_NUM_OF_GAIN_IN_PIPE; i++)
    {
        itsActualGain[i]               = 0;   
        // Cfg Attributes
        itsGain[i]                     = 0;
    }

    // Mon Attribute
    itsActualGroupEvoa  = 0;   
    // Cfg Attribute
    itsGroupEvoa        = 0;
           
    for (i=0; i<TSPII_MAX_NUM_OF_EVOA_IN_PIPE; i++)
    {            
        itsActualEvoa[i]               = 0;
        // Cfg Attributes
        itsEvoa[i]                     = 0;
        itsEvoaChannelPort[i]          = CT_TEL_INVALID_PORT_NUMBER;
    }

    for (i=0; i<TSPII_MAX_NUM_OF_ACTIVE_PATH_IN_PIPE; i++)
    {            
        // Cfg Attributes
        itsActivePath[i]                = false;
    }
    itsRefreshNeeded = false;
}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetOpticalOverloadThreshold()
{
    return itsOpticalOverloadThreshold;
}

///////////////////////////////////////////////////////////////////////////////
// For optical cards, the Input threshold will be read from TSPII
// It is for debug use currently, for DWDM port input threshold set
// TSPII need add this interface for Input LOS report or not        
///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetInputLowThreshold()
{
    return itsInputLowThreshold;
}

CT_TEL_mBm TSPII_PipeIf::GetInputUpThreshold()
{
    return itsInputUpThreshold;
}

///////////////////////////////////////////////////////////////////////////////
// For optical cards, the Input threshold will be read from TSPII
// It is for debug use currently, for EDFA input LOS threshold set
// TSPII need add this interface for Output LOS report or not        
///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetOutputLowThreshold()
{
    return itsOutputLowThreshold;
}

CT_TEL_mBm TSPII_PipeIf::GetOutputUpThreshold()
{
    return itsOutputUpThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetAopeThreshold()
{
    return itsAopeThreshold;
}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetOutputPower()
{
    return itsOutputPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetInputPower()
{
    return itsInputPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetAlternatePower()
{
    return itsAlternatePower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetDcmOutputPower()
{
    return itsDcmOutputPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetDcmInputPower()
{
    return itsDcmInputPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetMinGain()
{
    return itsMinGain;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetMaxGain()
{
    return itsMaxGain;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_PipeIf::GetLOS(uint32 theIndex)
{
    if (theIndex < itsNumberOfLOS)
        return itsLOS[theIndex];
    else
        return itsLOS[0];
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_PipeIf::GetNumberOfLOS()
{
    return itsNumberOfLOS;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetActualGain(uint32 theIndex)
{
    if (theIndex<itsNumberOfGain)
        return itsActualGain[theIndex];
    else
        return itsActualGain[0];
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetActualGroupEvoa()
{
    return itsActualGroupEvoa;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetActualEvoa(uint32 theIndex)
{
    if(itsNumberOfEvoa)
    {
        if (theIndex<itsNumberOfEvoa)
            return itsActualEvoa[theIndex];
        else
            return itsActualEvoa[0];
    }
    else
    {
        // For backward compatibilty we'll call base class GetActualGain here.
        // No Evoa methods were used before MR 45530
        return GetActualGain(theIndex);
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::GetOutputPowerLimited()
{
    return itsOutputPowerLimited;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::GetOutOfGain()
{
    return itsOutOfGain;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetGainTilt(CT_TEL_mBm theTilt)
{
    itsGainTilt = theTilt;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetGainTilt(void) const
{
    return itsGainTilt;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetGain(CT_TEL_mBm theGain, uint32 theIndex)
{
    if (theIndex<itsNumberOfGain)
        itsGain[theIndex] = theGain;

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::CommitGains()
{
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetGain(uint32 theIndex) const
{
    if (theIndex<itsNumberOfGain)
        return itsGain[theIndex];
    else
        return itsGain[0];
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetGroupEvoa(CT_TEL_mBm theEvoa)
{
    itsGroupEvoa = theEvoa;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetGroupEvoa() const
{
    return itsGroupEvoa;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetActivePath(uint32 theIndex, bool theEnable)
{
    if (theIndex<itsNumberOfActivePath)
        itsActivePath[theIndex] = theEnable;

}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::GetActivePath(uint32 theIndex) const
{
    if (theIndex<itsNumberOfActivePath)
        return itsActivePath[theIndex];
    else
        return itsActivePath[0];
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_PipeIf::GetNumberOfActivePath()
{
    return itsNumberOfActivePath;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_PipeIf::GetNumberOfGain()
{
    return itsNumberOfGain;
}

void TSPII_PipeIf::SetNumberOfGain(uint32 theNumberOfGain)
{
    if (theNumberOfGain <= TSPII_MAX_NUM_OF_GAIN_IN_PIPE)
    {
        itsNumberOfGain = theNumberOfGain;
    }
    else
    {
        itsNumberOfGain = TSPII_MAX_NUM_OF_GAIN_IN_PIPE;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetEvoa(CT_TEL_mBm theEvoa, uint32 theIndex)
{
    if(itsNumberOfEvoa)
    {
        if(theIndex < itsNumberOfEvoa) 
        {
            itsEvoa[theIndex] = theEvoa;
        }
    }
    else
    {
        // For backward compatibilty we'll call base class SetGain here.
        // No Evoa methods were used before MR 45530
        SetGain(theEvoa, theIndex);
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetActualGain(CT_TEL_mBm theGain, uint32 theIndex)
{
    if(itsNumberOfGain)
    {
        if(theIndex < itsNumberOfGain) 
        {
            itsActualGain[theIndex] = theGain;
        }
    }
    else
    {
    }
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetCfgEvoa(CT_TEL_mBm, uint32)
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::CommitEvoas()
{
    // CommitEvoas is the offical interface between CFG and the Pipe class
    // Some legacy cards only override CommitGains() (RCMM for one). This
    // method's default behavior should call the CommitGains() for backward
    // compatibility.
    CommitGains();
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetEvoa(uint32 theIndex) const
{
    if(itsNumberOfEvoa)
    {
        if (theIndex<itsNumberOfEvoa)
            return itsEvoa[theIndex];
        else
            return itsEvoa[0];
    }
    else
    {
        // For backward compatibilty we'll call base class GetGain here.
        // No Evoa methods were used before MR 45530
        return GetGain(theIndex);
    }
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_PipeIf::GetCfgEvoa(uint32) const
{
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_PipeIf::GetNumberOfEvoa()
{
    if(itsNumberOfEvoa)
    {
        return itsNumberOfEvoa;
    }
    else
    {
        // For backward compatibilty we'll call base class GetGain here.
        // No Evoa methods were used before MR 45530
        return GetNumberOfGain();
    }
}

void TSPII_PipeIf::SetNumberOfEvoa(uint32 theNumberOfEvoa)
{
    if (theNumberOfEvoa <= TSPII_MAX_NUM_OF_EVOA_IN_PIPE)
    {
        itsNumberOfEvoa = theNumberOfEvoa;
    }
    else
    {
        itsNumberOfEvoa = TSPII_MAX_NUM_OF_EVOA_IN_PIPE;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetInputLowThreshold(CT_TEL_mBm theInputLowThreshold)
{
    itsInputLowThreshold = theInputLowThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetInputUpThreshold(CT_TEL_mBm theInputUpThreshold)
{
    itsInputUpThreshold = theInputUpThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetOutputLowThreshold(CT_TEL_mBm theOutputLowThreshold)
{
    itsOutputLowThreshold = theOutputLowThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetOutputUpThreshold(CT_TEL_mBm theOutputUpThreshold)
{
    itsOutputUpThreshold = theOutputUpThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetPortNumber(uint8 thePortIndex, uint32 theIndex)
{
    if (thePortIndex<=itsNumberOfEvoaPorts && theIndex<itsNumberOfEvoa) 
    {
        itsEvoaChannelPort[theIndex] = thePortIndex;
    }
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_PipeIf::GetPortNumber(uint32 theIndex) const
{ 
    if (theIndex < TSPII_MAX_NUM_OF_EVOA_IN_PIPE) 
    {
        return itsEvoaChannelPort[theIndex];
    }
    else 
    {
        return 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::IsRefreshNeeded(void) const
{
    return itsRefreshNeeded;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::SetRefreshNeeded(bool theState)
{
    itsRefreshNeeded = theState;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_PipeIf::WriteObjectBinary(FC_Stream & theStream)
{
    uint32 i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsNumberOfLOS;
    theStream << itsNumberOfGain;
    theStream << itsNumberOfEvoa;
    theStream << itsNumberOfActivePath;
    for (i=0; i < itsNumberOfLOS; i++)
    {
        theStream << itsLOS[i];
    }
    theStream << itsInputPower;
    theStream << itsOutputPower;
    theStream << itsAlternatePower;
    theStream << itsDcmInputPower;
    theStream << itsDcmOutputPower;
    theStream << itsMinGain;
    theStream << itsMaxGain;
    theStream << itsOutputPowerLimited;
    theStream << itsOutOfGain;
    theStream << itsOpticalOverloadThreshold;
    theStream << itsInputLowThreshold;
    theStream << itsInputUpThreshold;
    theStream << itsOutputLowThreshold;
    theStream << itsOutputUpThreshold;
    theStream << itsAopeThreshold;
    for (i=0; i < itsNumberOfGain; i++)
    {
        theStream << itsActualGain[i];
        // Configuration
        theStream << itsGain[i];
    }
    
    theStream << itsActualGroupEvoa;
    // Configuration
    theStream << itsGroupEvoa;

    for (i=0; i < itsNumberOfEvoa; i++)
    {
        theStream << itsEvoaChannelPort[i];
        theStream << itsActualEvoa[i];
        // Configuration
        theStream << itsEvoa[i];
    }

    for (i=0; i < itsNumberOfActivePath; i++)
    {
        // Configuration
        theStream << itsActivePath[i];
    }
    theStream << itsGainTilt;
    theStream << itsRefreshNeeded;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_PipeIf::ReadObjectBinary(FC_Stream & theStream)
{
    uint32 i;

    // Monitoring
    theStream >> itsNumberOfLOS;
    theStream >> itsNumberOfGain;
    theStream >> itsNumberOfEvoa;
    theStream >> itsNumberOfActivePath;

    for (i=0; i < itsNumberOfLOS; i++)
    {
        theStream >> itsLOS[i];
    }
    theStream >> itsInputPower;
    theStream >> itsOutputPower;
    theStream >> itsAlternatePower;
    theStream >> itsDcmInputPower;
    theStream >> itsDcmOutputPower;
    theStream >> itsMinGain;
    theStream >> itsMaxGain;
    theStream >> itsOutputPowerLimited;
    theStream >> itsOutOfGain;
    theStream >> itsOpticalOverloadThreshold;
    theStream >> itsInputLowThreshold;
    theStream >> itsInputUpThreshold;
    theStream >> itsOutputLowThreshold;
    theStream >> itsOutputUpThreshold;
    theStream >> itsAopeThreshold;
    for (i=0; i < itsNumberOfGain; i++)
    {
        theStream >> itsActualGain[i];
        // Configuration
        theStream >> itsGain[i];
    }

    theStream >> itsActualGroupEvoa;
    // Configuration
    theStream >> itsGroupEvoa;

    for (i=0; i < itsNumberOfEvoa; i++)
    {
        theStream >> itsEvoaChannelPort[i];
        theStream >> itsActualEvoa[i];
        // Configuration
        theStream >> itsEvoa[i];
    }

    for (i=0; i < itsNumberOfActivePath; i++)
    {
        // Configuration
        theStream >> itsActivePath[i];
    }
    theStream >> itsGainTilt;
    theStream >> itsRefreshNeeded;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_PipeIf::WriteObject(ostream & theStream)
{
    uint32 i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << FC_InsertVar(itsNumberOfLOS);
    theStream << FC_InsertVar(itsNumberOfGain);
    theStream << FC_InsertVar(itsNumberOfEvoa);
    theStream << FC_InsertVar(itsNumberOfActivePath);

    for (i=0; i < itsNumberOfLOS; i++)
    {
        theStream << FC_InsertArrayVar(itsLOS, i);
    }
    theStream << FC_InsertVar(itsInputPower);
    theStream << FC_InsertVar(itsOutputPower);
    theStream << FC_InsertVar(itsAlternatePower);
    theStream << FC_InsertVar(itsDcmInputPower);
    theStream << FC_InsertVar(itsDcmOutputPower);
    theStream << FC_InsertVar(itsMinGain);
    theStream << FC_InsertVar(itsMaxGain);
    theStream << FC_InsertVar(itsOutputPowerLimited);
    theStream << FC_InsertVar(itsOutOfGain);
    theStream << FC_InsertVar(itsOpticalOverloadThreshold);
    theStream << FC_InsertVar(itsInputLowThreshold);
    theStream << FC_InsertVar(itsInputUpThreshold);
    theStream << FC_InsertVar(itsOutputLowThreshold);
    theStream << FC_InsertVar(itsOutputUpThreshold);
    theStream << FC_InsertVar(itsAopeThreshold);
    for (i=0; i < itsNumberOfGain; i++)
    {
        theStream << FC_InsertArrayVar(itsActualGain, i);
        // Configuration
        theStream << FC_InsertArrayVar(itsGain, i);
    }

    theStream << FC_InsertVar(itsActualGroupEvoa);
    // Configuration
    theStream << FC_InsertVar(itsGroupEvoa);

    for (i=0; i < itsNumberOfEvoa; i++)
    {
        theStream << FC_InsertArrayVar(itsEvoaChannelPort, i);
        theStream << FC_InsertArrayVar(itsActualEvoa, i);
        // Configuration
        theStream << FC_InsertArrayVar(itsEvoa, i);
    }

    for (i=0; i < itsNumberOfActivePath; i++)
    {
        // Configuration
        theStream << FC_InsertArrayVar(itsActivePath, i);
    }
    theStream << FC_InsertVar(itsGainTilt);
    theStream << FC_InsertVar(itsRefreshNeeded);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_PipeIf::ReadObject(istream & theStream)
{
    uint32 i;

    // Monitoring
    theStream >> FC_ExtractVar(itsNumberOfLOS);
    theStream >> FC_ExtractVar(itsNumberOfGain);
    theStream >> FC_ExtractVar(itsNumberOfEvoa);
    theStream >> FC_ExtractVar(itsNumberOfActivePath);

    for (i=0; i < itsNumberOfLOS; i++)
    {
        theStream >> FC_ExtractVar(itsLOS[i]);
    }
    theStream >> FC_ExtractVar(itsInputPower);
    theStream >> FC_ExtractVar(itsOutputPower);
    theStream >> FC_ExtractVar(itsAlternatePower);
    theStream >> FC_ExtractVar(itsDcmInputPower);
    theStream >> FC_ExtractVar(itsDcmOutputPower);
    theStream >> FC_ExtractVar(itsMinGain);
    theStream >> FC_ExtractVar(itsMaxGain);
    theStream >> FC_ExtractVar(itsOutputPowerLimited);
    theStream >> FC_ExtractVar(itsOutOfGain);
    theStream >> FC_ExtractVar(itsOpticalOverloadThreshold);
    theStream >> FC_ExtractVar(itsInputLowThreshold);
    theStream >> FC_ExtractVar(itsInputUpThreshold);
    theStream >> FC_ExtractVar(itsOutputLowThreshold);
    theStream >> FC_ExtractVar(itsOutputUpThreshold);
    theStream >> FC_ExtractVar(itsAopeThreshold);
    for (i=0; i < itsNumberOfGain; i++)
    {
        theStream >> FC_ExtractVar(itsActualGain[i]);
        // Configuration
        theStream >> FC_ExtractVar(itsGain[i]);
    }

    theStream >> FC_ExtractVar(itsActualGroupEvoa);
    // Configuration
    theStream >> FC_ExtractVar(itsGroupEvoa);

    for (i=0; i < itsNumberOfEvoa; i++)
    {
        theStream >> FC_ExtractVar(itsEvoaChannelPort[i]);
        theStream >> FC_ExtractVar(itsActualEvoa[i]);
        // Configuration
        theStream >> FC_ExtractVar(itsEvoa[i]);
    }

    for (i=0; i < itsNumberOfActivePath; i++)
    {
        // Configuration
        theStream >> FC_ExtractVar(itsActivePath[i]);
    }
    theStream >> FC_ExtractVar(itsGainTilt);
    theStream >> FC_ExtractVar(itsRefreshNeeded);

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::Display(FC_Stream & theStream)
{
    uint32 i;
    char OutBuf[256];

    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Pipe Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream <<    "      Refresh Requested     = " << TEXT_ON_OFF(itsRefreshNeeded) << "\n";
    sprintf(OutBuf,     "      Group Evoa            = %5d mB", itsGroupEvoa);
    theStream << OutBuf << endl;
    sprintf(OutBuf,     "      Gain Tilt             = %5d mB", itsGainTilt);
    theStream << OutBuf << endl;
    for (i=0; i<itsNumberOfGain; i++)
    {
        sprintf(OutBuf, "      Configured Gain %2d    = %5d mB", i, itsGain[i]);
        theStream << OutBuf << endl;
    }


    for (i=0; i<itsNumberOfEvoa; i++)
    {
        sprintf(OutBuf, "      Configured Evoa %2d    = %5d mB | Port = %2d", i, itsEvoa[i], itsEvoaChannelPort[i]);

        theStream << OutBuf << endl;
    }

    for (i=0; i<itsNumberOfActivePath; i++)
        theStream << "      Active Path     " << i <<"     = " << TEXT_ON_OFF(itsActivePath[i]) << "\n";
    theStream << "    MONITORING\n";
    theStream << "      Actual Group Evoa     = " << (itsActualGroupEvoa)       << " mBm\n";
    theStream << "      Gain Range            = " << (itsMinGain) << ".." << (itsMaxGain) << "\n";
    theStream << "      Input Power           = " << (itsInputPower)            << " mBm\n";
    theStream << "      Output Power          = " << (itsOutputPower)           << " mBm\n";
    theStream << "      Alternate Power       = " << (itsAlternatePower)        << " mBm\n";
    theStream << "      DCM Input Power  (DSR)= " << (itsDcmInputPower)         << " mBm\n";
    theStream << "      DCM Output Power (DST)= " << (itsDcmOutputPower)        << " mBm\n";
    theStream << "      Output Power Limited  = " << TEXT_ON_OFF(itsOutputPowerLimited) << " \n";
    theStream << "      Out Of Gain           = " << TEXT_ON_OFF(itsOutOfGain)  << " \n";
    theStream << "      Opt. Overload Thresh  = " << (itsOpticalOverloadThreshold) << " mBm\n";
    theStream << "      Input Low Thresh  = "     << (itsInputLowThreshold) << " mBm\n";
    theStream << "      Input Up Thresh  = "      << (itsInputUpThreshold) << " mBm\n";
    theStream << "      Output Low Thresh  = "    << (itsOutputLowThreshold) << " mBm\n";
    theStream << "      Output Up Thresh  = "     << (itsOutputUpThreshold) << " mBm\n";
    theStream << "      AOPE Threshold        = " << (itsAopeThreshold) << " mBm\n";
    for (i=0; i < itsNumberOfLOS; i++)
        theStream << "      LOS Defect  " << i << "         = " << TEXT_DEFECT(itsLOS[i]) << "\n";

    for (i=0; i<itsNumberOfGain; i++)
    {
        sprintf(OutBuf, "      Actual Gain %2d        = %-5d mB", i, itsActualGain[i]);
        theStream << OutBuf << endl;
    }
    for (i=0; i<itsNumberOfEvoa; i++)
    {
        sprintf(OutBuf, "      Actual Evoa %2d        = %-5d mB | Port = %-2d", i, itsActualEvoa[i], itsEvoaChannelPort[i]);
        theStream << OutBuf << endl;
    }
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    uint32 anIndex=0;
    uint8 anPortIndex=0;
    if ((argc == 3) && (strcmp(argv[0], "gain") == 0))
    {
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfGain)
        {
            SetGain(atoi(argv[1]), anIndex);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "groupevoa") == 0))
    {
        SetGroupEvoa(atoi(argv[1]));
    }
    else if ((argc == 3) && (strcmp(argv[0], "evoa") == 0))
    {
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfEvoa)
        {
            SetEvoa(atoi(argv[1]), anIndex);
            CommitEvoas();
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "port") == 0))
    {
        anPortIndex = static_cast<uint8>(strtoul(argv[1], NULL, 0));
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfActivePath)
        {
            SetPortNumber(anPortIndex, anIndex);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "path") == 0))
    {
        bool aEnable = false; 
        anIndex = strtoul(argv[2], NULL, 0);
        if(strcmp(argv[1], "true") == 0)
        {
            aEnable = true;
        }
        if (anIndex < itsNumberOfActivePath)
        {
            SetActivePath(anIndex, aEnable);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tilt") == 0))
    {
        SetGainTilt(atoi(argv[1]));
    }
    else if ((argc == 2) && (strcmp(argv[0], "refresh") == 0))
    {
        if (strcmp(argv[1], "true") == 0)
        {
            itsRefreshNeeded = true;
        }
        else if (strcmp(argv[1], "false") == 0)
        {
            itsRefreshNeeded = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);;
    }
    if (printUsage)
    {
        fc_cout << "    groupevoa <mbm>\n" << endl;
        fc_cout << "    gain      <mBm> <index = (0-" << itsNumberOfGain-1 << ")>\n" << endl;
        fc_cout << "    evoa      <mBm> <index = (0-" << itsNumberOfEvoa-1 << ")>\n" << endl;
        fc_cout << "    port      <portIndex = 0-16 (no port assoc = 0)> <index = (0-" << itsNumberOfActivePath-1 << ")>\n" << endl;
        fc_cout << "    path      <true/false> <index = (0-" << itsNumberOfActivePath-1 << ")>\n" << endl;
        fc_cout << "    tilt      <mbm>\n" << endl;
        fc_cout << "    refresh   <true/false> (force CFG HwRefresh)\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PipeIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    uint32 anIndex=0;
    
    if ((argc == 2) && (strcmp(argv[0], "inpwr") == 0))
    {
        itsInputPower = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "outpwr") == 0))
    {
        itsOutputPower = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "altpwr") == 0))
    {
        itsAlternatePower = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "dcminpwr") == 0))
    {
        itsDcmInputPower = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "dcmoutpwr") == 0))
    {
        itsDcmOutputPower = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "outpwrlim") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
            itsOutputPowerLimited = true;
        else if (strcmp(argv[1], "off") == 0)
            itsOutputPowerLimited = false;
        else
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "outofgain") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
            itsOutOfGain = true;
        else if (strcmp(argv[1], "off") == 0)
            itsOutOfGain = false;
        else
            printUsage = true;
    }
    else if ((argc == 3) && (strcmp(argv[0], "los") == 0))
    {
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfLOS)
        {
            if (strcmp(argv[1], "on") == 0)
            {
                if (!TSPII_DEFECT(itsLOS[anIndex])) itsLOS[anIndex]++;
            }
            else if (strcmp(argv[1], "off") == 0)
            {
                if (TSPII_DEFECT(itsLOS[anIndex])) itsLOS[anIndex]++;
            }
            else
            {
                printUsage = true;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "actgain") == 0))
    {
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfGain)
        {
            itsActualGain[anIndex] = strtoul(argv[1], NULL, 0);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "actgroupevoa") == 0))
    {
        itsActualGroupEvoa = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 3) && (strcmp(argv[0], "actevoa") == 0))
    {
        anIndex = strtoul(argv[2], NULL, 0);
        if (anIndex < itsNumberOfEvoa)
        {
            itsActualEvoa[anIndex] = strtoul(argv[1], NULL, 0);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "loscount") == 0))
    {
        anIndex = strtoul(argv[1], NULL, 0);
        if ((anIndex >= 1) && (anIndex <= TSPII_MAX_NUM_OF_LOS_IN_PIPE))
            itsNumberOfLOS = anIndex;
        else
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "gaincount") == 0))
    {
        anIndex = strtoul(argv[1], NULL, 0);
        if ((anIndex >= 1) && (anIndex <= TSPII_MAX_NUM_OF_GAIN_IN_PIPE))
            itsNumberOfGain = anIndex;
        else
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "evoacount") == 0))
    {
        anIndex = strtoul(argv[1], NULL, 0);
        if ((anIndex >= 1) && (anIndex <= TSPII_MAX_NUM_OF_EVOA_IN_PIPE))
            itsNumberOfGain = anIndex;
        else
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "actpathcount") == 0))
    {
        anIndex = strtoul(argv[1], NULL, 0);
        if ((anIndex >= 1) && (anIndex <= TSPII_MAX_NUM_OF_ACTIVE_PATH_IN_PIPE))
            itsNumberOfGain = anIndex;
        else
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "optoverldthresh") == 0))
    {
        itsOpticalOverloadThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "inputlowthresh") == 0))
    {
        itsInputLowThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "inputupthresh") == 0))
    {
        itsInputUpThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "outputlowthresh") == 0))
    {
        itsOutputLowThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "outputupthresh") == 0))
    {
        itsOutputUpThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "aopethresh") == 0))
    {
        itsAopeThreshold = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "tilt") == 0))
    {
        itsGainTilt = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 3) && (strcmp(argv[0], "gainrange") == 0))
    {
        itsMinGain = strtoul(argv[1], NULL, 0);
        itsMaxGain = strtoul(argv[2], NULL, 0);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    inpwr           <mBm>\n";
        fc_cout << "    outpwr          <mBm>\n";
        fc_cout << "    altpwr          <mBm>\n";
        fc_cout << "    dcminpwr        <mBm>\n";
        fc_cout << "    dcmoutpwr       <mBm>\n";
        fc_cout << "    outpwrlim       <on|off>\n";
        fc_cout << "    outofgain       <on|off>\n";
        fc_cout << "    optoverldthresh <mBm>\n";
        fc_cout << "    inputthresh <mBm>\n";
        fc_cout << "    outputthresh <mBm>\n";
        fc_cout << "    aopethresh      <mBm>\n";
        fc_cout << "    actgroupevoa    <mBm>\n";
        fc_cout << "    tilt            <mBm>\n";
        fc_cout << "    gainrange       <low mBm> <high mBm>\n";
        if(itsNumberOfLOS)
        {
            fc_cout << "    los             <on|off> [index (0-" << (itsNumberOfLOS-1) << " )]\n";
            fc_cout << "    loscount        <0-" << TSPII_MAX_NUM_OF_LOS_IN_PIPE <<  ">\n";
        }
        else
        {
            fc_cout << "    No LOS's to set" << endl;
        }

        if(itsNumberOfGain)
        {
            fc_cout << "    actgain         <mBm>    [index (0-" << (itsNumberOfGain-1) << " )]\n";
            fc_cout << "    gaincount       <0-" << TSPII_MAX_NUM_OF_GAIN_IN_PIPE << ">\n";
        }
        else
        {
            fc_cout << "    No gains to set" << endl;
        }

        if(itsNumberOfEvoa)
        {
            fc_cout << "    actevoa         <mBm>    [index (0-" << (itsNumberOfEvoa-1) << " )]\n";
            fc_cout << "    evoacount       <0-" << TSPII_MAX_NUM_OF_EVOA_IN_PIPE << ">\n";
        }
        else
        {
            fc_cout << "    No evoas to set" << endl;
        }
        
        if(itsNumberOfActivePath)
        {
            fc_cout << "    actpathcount    <0-" << TSPII_MAX_NUM_OF_ACTIVE_PATH_IN_PIPE << ">\n";
        }
        else
        {
            fc_cout << "    Active Paths to set" << endl;
        }

    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PipeIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
