/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbInhibitRmon.h>
#include <PM/PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitRmonCounter::PM_BbInhibitRmonCounter(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbInhibitRmonCounter::~PM_BbInhibitRmonCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonCounter::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for RMON parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON, true);
    // Set TCA Inhibition active for RMON parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON, true);
}

//-----------------------------------------------------------------
bool PM_BbInhibitRmonCounter::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeRmonCounter::PM_DROP:
        case PM_TypeRmonCounter::PM_PKT:
        case PM_TypeRmonCounter::PM_BCPKT:
        case PM_TypeRmonCounter::PM_MCPKT:
        case PM_TypeRmonCounter::PM_CRCAE:
        case PM_TypeRmonCounter::PM_USPKT:
        case PM_TypeRmonCounter::PM_OSPKT:
        case PM_TypeRmonCounter::PM_FRAG:
        case PM_TypeRmonCounter::PM_JABR:
        case PM_TypeRmonCounter::PM_DROP_HIGH:
        case PM_TypeRmonCounter::PM_PKT_HIGH:
        case PM_TypeRmonCounter::PM_BCPKT_HIGH:
        case PM_TypeRmonCounter::PM_MCPKT_HIGH:
        case PM_TypeRmonCounter::PM_CRCAE_HIGH:
        case PM_TypeRmonCounter::PM_USPKT_HIGH:
        case PM_TypeRmonCounter::PM_OSPKT_HIGH:
        case PM_TypeRmonCounter::PM_FRAG_HIGH:
        case PM_TypeRmonCounter::PM_JABR_HIGH:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonCounter::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeRmonCounter::PM_DROP:
        case PM_TypeRmonCounter::PM_PKT:
        case PM_TypeRmonCounter::PM_BCPKT:
        case PM_TypeRmonCounter::PM_MCPKT:
        case PM_TypeRmonCounter::PM_CRCAE:
        case PM_TypeRmonCounter::PM_USPKT:
        case PM_TypeRmonCounter::PM_OSPKT:
        case PM_TypeRmonCounter::PM_FRAG:
        case PM_TypeRmonCounter::PM_JABR:
        case PM_TypeRmonCounter::PM_DROP_HIGH:
        case PM_TypeRmonCounter::PM_PKT_HIGH:
        case PM_TypeRmonCounter::PM_BCPKT_HIGH:
        case PM_TypeRmonCounter::PM_MCPKT_HIGH:
        case PM_TypeRmonCounter::PM_CRCAE_HIGH:
        case PM_TypeRmonCounter::PM_USPKT_HIGH:
        case PM_TypeRmonCounter::PM_OSPKT_HIGH:
        case PM_TypeRmonCounter::PM_FRAG_HIGH:
        case PM_TypeRmonCounter::PM_JABR_HIGH:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
bool PM_BbInhibitRmonCounter::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeRmonCounter::PM_DROP:
        case PM_TypeRmonCounter::PM_PKT:
        case PM_TypeRmonCounter::PM_BCPKT:
        case PM_TypeRmonCounter::PM_MCPKT:
        case PM_TypeRmonCounter::PM_CRCAE:
        case PM_TypeRmonCounter::PM_USPKT:
        case PM_TypeRmonCounter::PM_OSPKT:
        case PM_TypeRmonCounter::PM_FRAG:
        case PM_TypeRmonCounter::PM_JABR:
        case PM_TypeRmonCounter::PM_DROP_HIGH:
        case PM_TypeRmonCounter::PM_PKT_HIGH:
        case PM_TypeRmonCounter::PM_BCPKT_HIGH:
        case PM_TypeRmonCounter::PM_MCPKT_HIGH:
        case PM_TypeRmonCounter::PM_CRCAE_HIGH:
        case PM_TypeRmonCounter::PM_USPKT_HIGH:
        case PM_TypeRmonCounter::PM_OSPKT_HIGH:
        case PM_TypeRmonCounter::PM_FRAG_HIGH:
        case PM_TypeRmonCounter::PM_JABR_HIGH:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonCounter::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeRmonCounter::PM_DROP:
        case PM_TypeRmonCounter::PM_PKT:
        case PM_TypeRmonCounter::PM_BCPKT:
        case PM_TypeRmonCounter::PM_MCPKT:
        case PM_TypeRmonCounter::PM_CRCAE:
        case PM_TypeRmonCounter::PM_USPKT:
        case PM_TypeRmonCounter::PM_OSPKT:
        case PM_TypeRmonCounter::PM_FRAG:
        case PM_TypeRmonCounter::PM_JABR:
        case PM_TypeRmonCounter::PM_DROP_HIGH:
        case PM_TypeRmonCounter::PM_PKT_HIGH:
        case PM_TypeRmonCounter::PM_BCPKT_HIGH:
        case PM_TypeRmonCounter::PM_MCPKT_HIGH:
        case PM_TypeRmonCounter::PM_CRCAE_HIGH:
        case PM_TypeRmonCounter::PM_USPKT_HIGH:
        case PM_TypeRmonCounter::PM_OSPKT_HIGH:
        case PM_TypeRmonCounter::PM_FRAG_HIGH:
        case PM_TypeRmonCounter::PM_JABR_HIGH:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitRmonCounter::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_DROP])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_PKT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_BCPKT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_MCPKT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_CRCAE])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_USPKT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_OSPKT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_FRAG])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_JABR]);

    return theStream;
}

//-----------------------------------------------------------------
istream& PM_BbInhibitRmonCounter::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_DROP])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_PKT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_BCPKT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_MCPKT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_CRCAE])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_USPKT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_OSPKT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_FRAG])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_JABR]);


    return theStream;
}

//-----------------------------------------------------------------
PM_BbInhibitRmonGauge::PM_BbInhibitRmonGauge(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbInhibitRmonGauge::~PM_BbInhibitRmonGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonGauge::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for laser parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON, true);
}

//-----------------------------------------------------------------
bool PM_BbInhibitRmonGauge::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeRmonGauge::PM_UTIL:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonGauge::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeRmonGauge::PM_UTIL:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_RMON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
bool PM_BbInhibitRmonGauge::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeRmonGauge::PM_UTIL:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitRmonGauge::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeRmonGauge::PM_UTIL:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_RMON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitRmonGauge::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeRmonGauge::PM_UTIL]);
    
    return theStream;
}

//-----------------------------------------------------------------
istream& PM_BbInhibitRmonGauge::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeRmonGauge::PM_UTIL]);

    return theStream;
}
