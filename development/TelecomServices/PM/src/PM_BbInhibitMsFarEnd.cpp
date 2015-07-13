/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     RAMM and SMTM
 AUTHOR   :     16 Feb 2004   Hemant Thakkar
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitMsFarEnd.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitMsFarEnd::PM_BbInhibitMsFarEnd(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeMsFarEnd::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitMsFarEnd::~PM_BbInhibitMsFarEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitMsFarEnd::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for MsFarEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSFAREND, true);
    // Set TCA Inhibition active for MsFarEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSFAREND, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitMsFarEnd::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeMsFarEnd::PM_CV:
        case PM_TypeMsFarEnd::PM_SES:
        case PM_TypeMsFarEnd::PM_ES:
        case PM_TypeMsFarEnd::PM_UAS:
        case PM_TypeMsFarEnd::PM_AISS:
        case PM_TypeMsFarEnd::PM_FC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSFAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitMsFarEnd::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeMsFarEnd::PM_CV:
        case PM_TypeMsFarEnd::PM_SES:
        case PM_TypeMsFarEnd::PM_ES:
        case PM_TypeMsFarEnd::PM_UAS:
        case PM_TypeMsFarEnd::PM_AISS:
        case PM_TypeMsFarEnd::PM_FC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSFAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitMsFarEnd::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeMsFarEnd::PM_CV:
        case PM_TypeMsFarEnd::PM_SES:
        case PM_TypeMsFarEnd::PM_ES:
        case PM_TypeMsFarEnd::PM_UAS:
        case PM_TypeMsFarEnd::PM_AISS:
        case PM_TypeMsFarEnd::PM_FC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSFAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitMsFarEnd::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeMsFarEnd::PM_CV:
        case PM_TypeMsFarEnd::PM_SES:
        case PM_TypeMsFarEnd::PM_ES:
        case PM_TypeMsFarEnd::PM_UAS:
        case PM_TypeMsFarEnd::PM_AISS:
        case PM_TypeMsFarEnd::PM_FC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_MSFAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitMsFarEnd::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_CV]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_SES] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_ES]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_UAS])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_AISS]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_FC]  );
    
    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitMsFarEnd::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_CV]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_SES] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_ES]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_UAS])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_AISS]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeMsFarEnd::PM_FC]  );

    return theStream;

}
