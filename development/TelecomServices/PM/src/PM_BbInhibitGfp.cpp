/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitGfp.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitGfp::PM_BbInhibitGfp(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeGfp::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitGfp::~PM_BbInhibitGfp()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitGfp::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for Gfp parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_GFP, true);
    // Set TCA Inhibition active for Gfp parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_GFP, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitGfp::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    if (theParameter == PM_TypeGfp::PM_10B_ERR)
    {
        inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_GFP);
    }
    else
    {
        FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
    }
    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitGfp::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    if (theParameter == PM_TypeGfp::PM_10B_ERR)
    {
        SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_GFP, theBoolVal);
    }
    else
    {
        FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
    }
}

//-----------------------------------------------------------------
bool PM_BbInhibitGfp::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    if (theParameter == PM_TypeGfp::PM_10B_ERR)
    {
        inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_GFP);
    }
    else
    {
        FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
    }
    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitGfp::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    if (theParameter == PM_TypeGfp::PM_10B_ERR)
    {
        SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_GFP, theBoolVal);
    }
    else
    {
        FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitGfp::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeGfp::PM_10B_ERR]);
    
    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitGfp::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeGfp::PM_10B_ERR] );

    return theStream;

}
