/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     RAMM and SMTM
 AUTHOR   :     16 Feb 2004   Hemant Thakkar
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitMsNearEnd.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitMsNearEnd::PM_BbInhibitMsNearEnd(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeMsNearEnd::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitMsNearEnd::~PM_BbInhibitMsNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitMsNearEnd::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for MsNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSNEAREND, true);
    // Set TCA Inhibition active for MsNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSNEAREND, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitMsNearEnd::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeMsNearEnd::PM_CV:
        case PM_TypeMsNearEnd::PM_SES:
        case PM_TypeMsNearEnd::PM_ES:
        case PM_TypeMsNearEnd::PM_UAS:
        case PM_TypeMsNearEnd::PM_AISS:
        case PM_TypeMsNearEnd::PM_FC:
        case PM_TypeMsNearEnd::PM_PSC:
        case PM_TypeMsNearEnd::PM_PSD:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSNEAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitMsNearEnd::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeMsNearEnd::PM_CV:
        case PM_TypeMsNearEnd::PM_SES:
        case PM_TypeMsNearEnd::PM_ES:
        case PM_TypeMsNearEnd::PM_UAS:
        case PM_TypeMsNearEnd::PM_AISS:
        case PM_TypeMsNearEnd::PM_FC:
        case PM_TypeMsNearEnd::PM_PSC:
        case PM_TypeMsNearEnd::PM_PSD:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSNEAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitMsNearEnd::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeMsNearEnd::PM_CV:
        case PM_TypeMsNearEnd::PM_SES:
        case PM_TypeMsNearEnd::PM_ES:
        case PM_TypeMsNearEnd::PM_UAS:
        case PM_TypeMsNearEnd::PM_AISS:
        case PM_TypeMsNearEnd::PM_FC:
        case PM_TypeMsNearEnd::PM_PSC:
        case PM_TypeMsNearEnd::PM_PSD:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSNEAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitMsNearEnd::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeMsNearEnd::PM_CV:
        case PM_TypeMsNearEnd::PM_SES:
        case PM_TypeMsNearEnd::PM_ES:
        case PM_TypeMsNearEnd::PM_UAS:
        case PM_TypeMsNearEnd::PM_AISS:
        case PM_TypeMsNearEnd::PM_FC:
        case PM_TypeMsNearEnd::PM_PSC:
        case PM_TypeMsNearEnd::PM_PSD:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSNEAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitMsNearEnd::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_CV]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_SES] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_ES]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_UAS])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_AISS]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_FC]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_PSC] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_PSD] );
    
    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitMsNearEnd::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_CV]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_SES] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_ES]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_UAS])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_AISS]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_FC]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_PSC] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsNearEnd::PM_PSD] );

    return theStream;

}
