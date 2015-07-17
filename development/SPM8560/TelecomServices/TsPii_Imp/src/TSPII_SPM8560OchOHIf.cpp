/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560OchOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OchOHIf::TSPII_SPM8560OchOHIf(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch) :
    TSPII_OchOHIf(false),
    myOscCtrl(TSPII_OscMapperFpgaCtrl::GetInstance()),
    myOsc(theOsc),
    myOch(theOch)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560OchOHIf::~TSPII_SPM8560OchOHIf()
{
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OchOHIf::GetOCI()
{
    return myOscCtrl.OchGetOCI(myOsc, myOch);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OchOHIf::GetFDIP()
{
    return myOscCtrl.OchGetFDIP(myOsc, myOch);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560OchOHIf::GetFDIO()
{
    return myOscCtrl.OchGetFDIO(myOsc, myOch);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OchOHIf::ForceOCI(bool theForceOCI)
{
    myOscCtrl.OchForceOCI(myOsc, myOch, theForceOCI);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OchOHIf::ForceFDIP(bool theForceFDIP)
{
    myOscCtrl.OchForceFDIP(myOsc, myOch, theForceFDIP);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560OchOHIf::ForceFDIO(bool theForceFDIO)
{
    myOscCtrl.OchForceFDIO(myOsc, myOch, theForceFDIO);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OchOHIf::GetForceOCI() const
{
    return myOscCtrl.OchGetForceOCI(myOsc, myOch);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OchOHIf::GetForceFDIP() const
{
    return myOscCtrl.OchGetForceFDIP(myOsc, myOch);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560OchOHIf::GetForceFDIO() const
{
    return myOscCtrl.OchGetForceFDIO(myOsc, myOch);
}
