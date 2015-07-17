/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560OpticalIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OpticalIf::TSPII_SPM8560OpticalIf(TSPII_OscMapperFpgaChannel theOsc) :
    TSPII_OpticalIf(false, true, true, true, true),
    myOscCtrl(TSPII_OscMapperFpgaCtrl::GetInstance()),
    myOsc(theOsc)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OpticalIf::~TSPII_SPM8560OpticalIf()
{
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OpticalIf::GetLaserState()
{
    return myOscCtrl.OptGetLaserState(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OpticalIf::GetOptLOS()
{
    return myOscCtrl.OptGetOptLOS(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OpticalIf::GetLossOfClock()
{
    return myOscCtrl.OptGetLossOfClock(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_SPM8560OpticalIf::GetOpticalPowerTransmittedByPeer()
{
    return myOscCtrl.OptGetPowerTransmittedByPeer(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OpticalIf::SetOpticalPowerTransmittedToPeer()
{
    myOscCtrl.OptSetPowerTransmittedToPeer(myOsc, GetOpticalPowerTransmitted());
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_SPM8560OpticalIf::GetOpticalPowerTransmittedToPeer()
{
    return myOscCtrl.OptGetPowerTransmittedToPeer(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_SPM8560OpticalIf::GetOmsPowerTransmittedByPeer()
{
    return myOscCtrl.OptGetOmsPowerTransmittedByPeer(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OpticalIf::SetOmsPowerTransmittedToPeer()
{
    myOscCtrl.OptSetOmsPowerTransmittedToPeer(myOsc, GetOmsPowerTransmitted());
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_SPM8560OpticalIf::GetOmsPowerTransmittedToPeer()
{
    return myOscCtrl.OptGetOmsPowerTransmittedToPeer(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OpticalIf::SetLaserEnable(bool theEnable)
{
    myOscCtrl.OptSetLaserEnable(myOsc, theEnable);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OpticalIf::SetFacilityLoopbackEnable(bool theEnable)
{
    myOscCtrl.OptSetFacilityLoopbackEnable(myOsc, theEnable);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OpticalIf::SetTerminalLoopbackEnable(bool theEnable)
{
    myOscCtrl.OptSetTerminalLoopbackEnable(myOsc, theEnable);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OpticalIf::GetLaserEnable() const
{
    return myOscCtrl.OptGetLaserEnable(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OpticalIf::GetFacilityLoopbackEnable() const
{
    return myOscCtrl.OptGetFacilityLoopbackEnable(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OpticalIf::GetTerminalLoopbackEnable() const
{
    return myOscCtrl.OptGetTerminalLoopbackEnable(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_SPM8560OpticalIf::GetOpticalPowerReceived()
{
	return myOscCtrl.OptGetOpticalPowerReceived(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_SPM8560OpticalIf::GetOpticalPowerTransmitted()
{
	return myOscCtrl.OptGetOpticalPowerTransmitted(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_SPM8560OpticalIf::GetOmsPowerTransmitted()
{
    return myOscCtrl.OptGetOmsPowerTransmitted(myOsc);
}

