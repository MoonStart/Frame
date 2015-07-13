/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     SMTM
 AUTHOR   :     27 Feb 2006   Larry Wolfrum
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbInhibitHopFarEnd.h>
#include <PM/PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitHopFarEnd::PM_BbInhibitHopFarEnd(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbInhibitHopFarEnd::~PM_BbInhibitHopFarEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitHopFarEnd::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSFAREND, true);
    // Set TCA Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPFAREND, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitHopFarEnd::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeHopFarEnd::PM_CV:
        case PM_TypeHopFarEnd::PM_SES:
        case PM_TypeHopFarEnd::PM_ES:
        case PM_TypeHopFarEnd::PM_UAS:
        case PM_TypeHopFarEnd::PM_FC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_HOPFAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitHopFarEnd::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeHopFarEnd::PM_CV:
        case PM_TypeHopFarEnd::PM_SES:
        case PM_TypeHopFarEnd::PM_ES:
        case PM_TypeHopFarEnd::PM_UAS:
        case PM_TypeHopFarEnd::PM_FC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_HOPFAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitHopFarEnd::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeHopFarEnd::PM_CV:
        case PM_TypeHopFarEnd::PM_SES:
        case PM_TypeHopFarEnd::PM_ES:
        case PM_TypeHopFarEnd::PM_UAS:
        case PM_TypeHopFarEnd::PM_FC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPFAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitHopFarEnd::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeHopFarEnd::PM_CV:
        case PM_TypeHopFarEnd::PM_SES:
        case PM_TypeHopFarEnd::PM_ES:
        case PM_TypeHopFarEnd::PM_UAS:
        case PM_TypeHopFarEnd::PM_FC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPFAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitHopFarEnd::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_CV]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_SES] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_ES]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_UAS])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_FC]  );
    
    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitHopFarEnd::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_CV]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_SES] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_ES]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_UAS])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopFarEnd::PM_FC]  );

    return theStream;

}
