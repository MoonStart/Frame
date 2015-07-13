/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbInhibitTcm.h>
#include <PM/PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
PM_BbInhibitTcm::PM_BbInhibitTcm(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    myPrivateResetCountCurrent[PM_TypeTcm::PM_CV] = 0;
    myPrivateResetCountCurrent[PM_TypeTcm::PM_ES] = 0;
    myPrivateResetCountCurrent[PM_TypeTcm::PM_SES] = 0;
    myPrivateResetCountCurrent[PM_TypeTcm::PM_UAS] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitTcm::~PM_BbInhibitTcm()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitTcm::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for TCM parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM, true);
    // Set TCA Inhibition active for TCM parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitTcm::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeTcm::PM_CV:
        case PM_TypeTcm::PM_ES:
        case PM_TypeTcm::PM_SES:
        case PM_TypeTcm::PM_UAS:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitTcm::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeTcm::PM_CV:
        case PM_TypeTcm::PM_ES:
        case PM_TypeTcm::PM_SES:
        case PM_TypeTcm::PM_UAS:

            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM, theBoolVal);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitTcm::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeTcm::PM_CV:
        case PM_TypeTcm::PM_ES:
        case PM_TypeTcm::PM_SES:
        case PM_TypeTcm::PM_UAS:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitTcm::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeTcm::PM_CV:
        case PM_TypeTcm::PM_ES:
        case PM_TypeTcm::PM_SES:
        case PM_TypeTcm::PM_UAS:

            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM, theBoolVal);
            break;

        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitTcm::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_CV]		 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_ES] 	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_SES]  	 )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_UAS] 	 );

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitTcm::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_CV]      )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_ES]	  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_SES]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeTcm::PM_UAS]	  );

    return theStream;

}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
PM_BbInhibitTcmGauge::PM_BbInhibitTcmGauge(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    myPrivateResetCountCurrent[PM_TypeTcmGauge::PM_DELAY] = 0;
}
 
//-----------------------------------------------------------------
PM_BbInhibitTcmGauge::~PM_BbInhibitTcmGauge()
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
void PM_BbInhibitTcmGauge::Reset()
{
    PM_BbInhibit::Reset();
 
    // Set Inhibition active for laser parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM, true);
}
 
//-----------------------------------------------------------------
bool PM_BbInhibitTcmGauge::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;
 
    switch(theParameter)
    {
        case PM_TypeTcmGauge::PM_DELAY:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitTcmGauge::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeTcmGauge::PM_DELAY:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_TCM, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}
 
//-----------------------------------------------------------------
bool PM_BbInhibitTcmGauge::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;
 
    switch(theParameter)
    {
        case PM_TypeTcmGauge::PM_DELAY:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}
 
//-----------------------------------------------------------------
void PM_BbInhibitTcmGauge::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeTcmGauge::PM_DELAY:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_TCM, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitTcmGauge::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeTcmGauge::PM_DELAY]);
    
    return theStream;
}
 
//-----------------------------------------------------------------
istream& PM_BbInhibitTcmGauge::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeTcmGauge::PM_DELAY]);
 
    return theStream;
}
