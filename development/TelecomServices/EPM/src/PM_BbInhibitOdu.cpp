/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbInhibitOdu.h>
#include <PM/PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitOdu::PM_BbInhibitOdu(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    myPrivateResetCountCurrent[PM_TypeOdu::PM_CV] = 0;
    myPrivateResetCountCurrent[PM_TypeOdu::PM_ES] = 0;
    myPrivateResetCountCurrent[PM_TypeOdu::PM_SES] = 0;
    myPrivateResetCountCurrent[PM_TypeOdu::PM_UAS] = 0;
    myPrivateResetCountCurrent[PM_TypeOdu::PM_PSC] = 0;
    myPrivateResetCountCurrent[PM_TypeOdu::PM_PSD] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitOdu::~PM_BbInhibitOdu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitOdu::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU, true);
    // Set TCA Inhibition active for HopNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitOdu::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOdu::PM_CV:
        case PM_TypeOdu::PM_ES:
        case PM_TypeOdu::PM_SES:
        case PM_TypeOdu::PM_UAS:
        case PM_TypeOdu::PM_PSC:
        case PM_TypeOdu::PM_PSD:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitOdu::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOdu::PM_CV:
        case PM_TypeOdu::PM_ES:
        case PM_TypeOdu::PM_SES:
        case PM_TypeOdu::PM_UAS:
        case PM_TypeOdu::PM_PSC:
        case PM_TypeOdu::PM_PSD:

            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU, theBoolVal);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitOdu::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOdu::PM_CV:
        case PM_TypeOdu::PM_ES:
        case PM_TypeOdu::PM_SES:
        case PM_TypeOdu::PM_UAS:
        case PM_TypeOdu::PM_PSC:
        case PM_TypeOdu::PM_PSD:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitOdu::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOdu::PM_CV:
        case PM_TypeOdu::PM_ES:
        case PM_TypeOdu::PM_SES:
        case PM_TypeOdu::PM_UAS:
        case PM_TypeOdu::PM_PSC:
        case PM_TypeOdu::PM_PSD:

            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU, theBoolVal);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitOdu::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_CV]		 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_ES] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_SES]  	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_UAS] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_PSC] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_PSD] 	 );

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitOdu::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_CV]      )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_ES]	  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_SES]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_UAS]	  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_PSC]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOdu::PM_PSD]	  );

    return theStream;

}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
PM_BbInhibitOduGauge::PM_BbInhibitOduGauge(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    myPrivateResetCountCurrent[PM_TypeOduGauge::PM_DELAY] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitOduGauge::~PM_BbInhibitOduGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbInhibitOduGauge::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for laser parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU, true);
}

//-----------------------------------------------------------------
bool PM_BbInhibitOduGauge::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOduGauge::PM_DELAY:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitOduGauge::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeOduGauge::PM_DELAY:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ODU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
bool PM_BbInhibitOduGauge::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOduGauge::PM_DELAY:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitOduGauge::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeOduGauge::PM_DELAY:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ODU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitOduGauge::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOduGauge::PM_DELAY]);
    
    return theStream;
}

//-----------------------------------------------------------------
istream& PM_BbInhibitOduGauge::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOduGauge::PM_DELAY]);

    return theStream;
}
