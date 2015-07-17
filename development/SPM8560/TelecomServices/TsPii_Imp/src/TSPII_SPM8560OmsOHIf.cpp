/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560OmsOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OmsOHIf::TSPII_SPM8560OmsOHIf(TSPII_OscMapperFpgaChannel theOsc) :
    TSPII_OmsOHIf(false),
    myOscCtrl(TSPII_OscMapperFpgaCtrl::GetInstance()),
    myOsc(theOsc)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OmsOHIf::~TSPII_SPM8560OmsOHIf()
{
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OmsOHIf::GetPMI()
{
    return myOscCtrl.OmsGetPMI(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OmsOHIf::GetBDIP()
{
    return myOscCtrl.OmsGetBDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OmsOHIf::GetBDIO()
{
    return myOscCtrl.OmsGetBDIO(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OmsOHIf::GetFDIP()
{
    return myOscCtrl.OmsGetFDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OmsOHIf::GetFDIO()
{
    return myOscCtrl.OmsGetFDIO(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OmsOHIf::ForcePMI(bool theForcePMI)
{
    myOscCtrl.OmsForcePMI(myOsc, theForcePMI);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OmsOHIf::ForceBDIP(bool theForceBDIP)
{
    myOscCtrl.OmsForceBDIP(myOsc, theForceBDIP);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OmsOHIf::ForceBDIO(bool theForceBDIO)
{
    myOscCtrl.OmsForceBDIO(myOsc, theForceBDIO);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OmsOHIf::ForceFDIP(bool theForceFDIP)
{
    myOscCtrl.OmsForceFDIP(myOsc, theForceFDIP);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OmsOHIf::ForceFDIO(bool theForceFDIO)
{
    myOscCtrl.OmsForceFDIO(myOsc, theForceFDIO);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OmsOHIf::GetForcePMI() const
{
    return myOscCtrl.OmsGetForcePMI(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OmsOHIf::GetForceBDIP() const
{
    return myOscCtrl.OmsGetForceBDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OmsOHIf::GetForceBDIO() const
{
    return myOscCtrl.OmsGetForceBDIO(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OmsOHIf::GetForceFDIP() const
{
    return myOscCtrl.OmsGetForceFDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OmsOHIf::GetForceFDIO() const
{
    return myOscCtrl.OmsGetForceFDIO(myOsc);
}
