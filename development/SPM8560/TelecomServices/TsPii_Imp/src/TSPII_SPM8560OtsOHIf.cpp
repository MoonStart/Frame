/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560OtsOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OtsOHIf::TSPII_SPM8560OtsOHIf(TSPII_OscMapperFpgaChannel theOsc) :
    TSPII_OtsOHIf(false),
    myOscCtrl(TSPII_OscMapperFpgaCtrl::GetInstance()),
    myOsc(theOsc)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OtsOHIf::~TSPII_SPM8560OtsOHIf()
{
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OtsOHIf::GetPMI()
{
    return myOscCtrl.OtsGetPMI(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OtsOHIf::GetBDIP()
{
    return myOscCtrl.OtsGetBDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OtsOHIf::GetBDIO()
{
    return myOscCtrl.OtsGetBDIO(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_SPM8560OtsOHIf::GetRxTTI()
{
    return myOscCtrl.OtsGetRxTTI(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OtsOHIf::ForcePMI(bool theForcePMI)
{
    myOscCtrl.OtsForcePMI(myOsc, theForcePMI);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OtsOHIf::ForceBDIP(bool theForceBDIP)
{
    myOscCtrl.OtsForceBDIP(myOsc, theForceBDIP);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OtsOHIf::ForceBDIO(bool theForceBDIO)
{
    myOscCtrl.OtsForceBDIO(myOsc, theForceBDIO);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OtsOHIf::SetTxTTI(const CT_G709Trace & theTrace)
{
    myOscCtrl.OtsSetTxTTI(myOsc, theTrace);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OtsOHIf::GetForcePMI() const
{
    return myOscCtrl.OtsGetForcePMI(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OtsOHIf::GetForceBDIP() const
{
    return myOscCtrl.OtsGetForceBDIP(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OtsOHIf::GetForceBDIO() const
{
    return myOscCtrl.OtsGetForceBDIO(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_SPM8560OtsOHIf::GetTxTTI() const
{
    return myOscCtrl.OtsGetTxTTI(myOsc);
}
