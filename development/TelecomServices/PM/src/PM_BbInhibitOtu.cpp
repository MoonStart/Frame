/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitOtu.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F5E02F6
PM_BbInhibitOtu::PM_BbInhibitOtu(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeOtu::PM_PARAM_NUM-2; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5E0300
PM_BbInhibitOtu::~PM_BbInhibitOtu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5E030A
void PM_BbInhibitOtu::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for OTU parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU, true);
    // Set TCA Inhibition active for OTU parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU, true);

}

//-----------------------------------------------------------------
//##ModelId=3C9255AB00C6
bool PM_BbInhibitOtu::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOtu::PM_BE:
        case PM_TypeOtu::PM_UBE:
        case PM_TypeOtu::PM_PSC:
        case PM_TypeOtu::PM_PSD:
        case PM_TypeOtu::PM_CV:
        case PM_TypeOtu::PM_ES:
        case PM_TypeOtu::PM_SES:
        case PM_TypeOtu::PM_UAS:
        case PM_TypeOtu::PM_CV_HIGH:
        case PM_TypeOtu::PM_BE_HIGH:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3C9255AB00EE
void PM_BbInhibitOtu::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOtu::PM_BE:
        case PM_TypeOtu::PM_UBE:
        case PM_TypeOtu::PM_PSC:
        case PM_TypeOtu::PM_PSD:
        case PM_TypeOtu::PM_CV:
        case PM_TypeOtu::PM_ES:
        case PM_TypeOtu::PM_SES:
        case PM_TypeOtu::PM_UAS:
        case PM_TypeOtu::PM_CV_HIGH:
        case PM_TypeOtu::PM_BE_HIGH:

            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CCE030D
bool PM_BbInhibitOtu::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOtu::PM_BE:
        case PM_TypeOtu::PM_UBE:
        case PM_TypeOtu::PM_PSC:
        case PM_TypeOtu::PM_PSD:
        case PM_TypeOtu::PM_CV:
        case PM_TypeOtu::PM_ES:
        case PM_TypeOtu::PM_SES:
        case PM_TypeOtu::PM_UAS:
        case PM_TypeOtu::PM_CV_HIGH:
        case PM_TypeOtu::PM_BE_HIGH:

            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CCE0368
void PM_BbInhibitOtu::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOtu::PM_BE:
        case PM_TypeOtu::PM_UBE:
        case PM_TypeOtu::PM_PSC:
        case PM_TypeOtu::PM_PSD:
        case PM_TypeOtu::PM_CV:
        case PM_TypeOtu::PM_ES:
        case PM_TypeOtu::PM_SES:
        case PM_TypeOtu::PM_UAS:
        case PM_TypeOtu::PM_CV_HIGH:
        case PM_TypeOtu::PM_BE_HIGH:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5E0314
ostream& PM_BbInhibitOtu::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_BE])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_UBE])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_PSC])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_PSD])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_CV])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_ES])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_SES])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_UAS]);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5E0327
istream& PM_BbInhibitOtu::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_BE])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_UBE])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_PSC])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_PSD])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_CV])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_ES])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_SES])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtu::PM_UAS]);

    return theStream;

}


//-----------------------------------------------------------------
PM_BbInhibitOtuGauge::PM_BbInhibitOtuGauge(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeOtuGauge::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitOtuGauge::~PM_BbInhibitOtuGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbInhibitOtuGauge::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for OTU parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU, true);
    // Set TCA Inhibition active for OTU parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU, true);
}

//-----------------------------------------------------------------
bool PM_BbInhibitOtuGauge::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOtuGauge::PM_BER:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitOtuGauge::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeOtuGauge::PM_BER:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OTU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
bool PM_BbInhibitOtuGauge::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOtuGauge::PM_BER:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
    return inhibitState;
}

//-----------------------------------------------------------------
void PM_BbInhibitOtuGauge::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    switch(theParameter)
    {
        case PM_TypeOtuGauge::PM_BER:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OTU, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }
}

//-----------------------------------------------------------------
ostream& PM_BbInhibitOtuGauge::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOtuGauge::PM_BER]);
    
    return theStream;
}

//-----------------------------------------------------------------
istream& PM_BbInhibitOtuGauge::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOtuGauge::PM_BER]);

    return theStream;
}
