/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560RsIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"
#include "CSPII_NetworkIf.h"

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560RsIf::TSPII_SPM8560RsIf(TSPII_OscMapperFpgaChannel theOsc) :
    TSPII_RsIf(false),
    myOscCtrl(TSPII_OscMapperFpgaCtrl::GetInstance()),
    myOsc(theOsc)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560RsIf::~TSPII_SPM8560RsIf()
{
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560RsIf::GetCVCount()
{
    return myOscCtrl.RsGetCVCount(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560RsIf::GetLOF()
{
    return myOscCtrl.RsGetLOF(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_SPM8560RsIf::GetOOF()
{
    return myOscCtrl.RsGetOOF(myOsc);
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560RsIf::SetSignalType(CT_TEL_SignalType theSignalType)
{
    // because H/W only supports same type on both side, only side 1 will be considered
    if (myOsc==OSC_FPGA_CHANNEL1)
        myOscCtrl.RsSetSignalType(theSignalType);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_SignalType TSPII_SPM8560RsIf::GetSignalType() const
{
    return myOscCtrl.RsGetSignalType();
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560RsIf::SetEnableMessaging(bool enable)
{
    CSPII_NetworkIf::SetOscLinkState(myOsc, enable);
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_SPM8560RsIf::GetMessagingEnabled() const
{
    return(CSPII_NetworkIf::GetOscLinkState(myOsc));
}
