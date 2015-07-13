/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     RAMM and SMTM
 AUTHOR   :     16 Feb 2004   Hemant Thakkar
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitHopNearEnd.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitHopNearEnd::PM_BbInhibitHopNearEnd(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeHopNearEnd::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitHopNearEnd::~PM_BbInhibitHopNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitHopNearEnd::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_MSNEAREND, true);
    // Set TCA Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPNEAREND, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitHopNearEnd::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeHopNearEnd::PM_CV:
        case PM_TypeHopNearEnd::PM_SES:
        case PM_TypeHopNearEnd::PM_ES:
        case PM_TypeHopNearEnd::PM_UAS:
        case PM_TypeHopNearEnd::PM_FC:
		case PM_TypeHopNearEnd::PM_PJCSGEN:
		case PM_TypeHopNearEnd::PM_PJCSDET:
		case PM_TypeHopNearEnd::PM_PJCDIFF:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_HOPNEAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitHopNearEnd::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeHopNearEnd::PM_CV:
        case PM_TypeHopNearEnd::PM_SES:
        case PM_TypeHopNearEnd::PM_ES:
        case PM_TypeHopNearEnd::PM_UAS:
        case PM_TypeHopNearEnd::PM_FC:
		case PM_TypeHopNearEnd::PM_PJCSGEN:
		case PM_TypeHopNearEnd::PM_PJCSDET:
		case PM_TypeHopNearEnd::PM_PJCDIFF:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_HOPNEAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitHopNearEnd::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeHopNearEnd::PM_CV:
        case PM_TypeHopNearEnd::PM_SES:
        case PM_TypeHopNearEnd::PM_ES:
        case PM_TypeHopNearEnd::PM_UAS:
        case PM_TypeHopNearEnd::PM_FC:
		case PM_TypeHopNearEnd::PM_PJCSGEN:
		case PM_TypeHopNearEnd::PM_PJCSDET:
		case PM_TypeHopNearEnd::PM_PJCDIFF:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPNEAREND);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitHopNearEnd::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeHopNearEnd::PM_CV:
        case PM_TypeHopNearEnd::PM_SES:
        case PM_TypeHopNearEnd::PM_ES:
        case PM_TypeHopNearEnd::PM_UAS:
        case PM_TypeHopNearEnd::PM_FC:
		case PM_TypeHopNearEnd::PM_PJCSGEN:
		case PM_TypeHopNearEnd::PM_PJCSDET:
		case PM_TypeHopNearEnd::PM_PJCDIFF:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_HOPNEAREND, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitHopNearEnd::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_CV]		 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_SES] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_ES]  	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_UAS] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_FC]		 )
		   	  << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCSGEN]  )
			  << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCSDET]  )
			  << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCDIFF] );

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitHopNearEnd::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_CV]		  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_SES]	  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_ES]		  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_UAS]	  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_FC]		  )
			  >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCSGEN]  )
			  >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCSDET]  )
			  >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeHopNearEnd::PM_PJCDIFF] );

    return theStream;

}
