/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders.
 AUTHOR   :     December 13, 2001 Sebastien Cossette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitOpt.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>

using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C50162800CF
PM_BbInhibitOpt::PM_BbInhibitOpt(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeOpt::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C50162800DA
PM_BbInhibitOpt::~PM_BbInhibitOpt()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C50162800E3
void PM_BbInhibitOpt::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT, true);

}

//-----------------------------------------------------------------
//##ModelId=3C9255B60040
bool PM_BbInhibitOpt::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOpt::PM_OPR:
        case PM_TypeOpt::PM_OPT:
        case PM_TypeOpt::PM_DGD:
        case PM_TypeOpt::PM_CD:
        case PM_TypeOpt::PM_OSNR:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3C9255B6004C
void PM_BbInhibitOpt::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOpt::PM_OPR:
        case PM_TypeOpt::PM_OPT:
        case PM_TypeOpt::PM_DGD:
        case PM_TypeOpt::PM_CD:
        case PM_TypeOpt::PM_OSNR:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CCB0100
bool PM_BbInhibitOpt::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOpt::PM_OPR:
        case PM_TypeOpt::PM_OPT:
        case PM_TypeOpt::PM_DGD:
        case PM_TypeOpt::PM_CD:
        case PM_TypeOpt::PM_OSNR:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CCB0150
void PM_BbInhibitOpt::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOpt::PM_OPR:
        case PM_TypeOpt::PM_OPT:
        case PM_TypeOpt::PM_DGD:
        case PM_TypeOpt::PM_CD:
        case PM_TypeOpt::PM_OSNR:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C50162800E5
ostream& PM_BbInhibitOpt::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OPR])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OPT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_DGD])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_CD])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OSNR]);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C50162800F7
istream& PM_BbInhibitOpt::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OPR])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OPT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_DGD])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_CD])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOpt::PM_OSNR]);

    return theStream;

}

//-----------------------------------------------------------------
PM_BbInhibitOptCounter::PM_BbInhibitOptCounter(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeOptCounter::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
PM_BbInhibitOptCounter::~PM_BbInhibitOptCounter()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbInhibitOptCounter::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for MsNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT, true);
    // Set TCA Inhibition active for MsNearEnd parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT, true);

}

//-----------------------------------------------------------------
bool PM_BbInhibitOptCounter::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;

    switch(theParameter)
    {
        case PM_TypeOptCounter::PM_PSC:
        case PM_TypeOptCounter::PM_PSD:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitOptCounter::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOptCounter::PM_PSC:
        case PM_TypeOptCounter::PM_PSD:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OPT, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
bool PM_BbInhibitOptCounter::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOptCounter::PM_PSC:
        case PM_TypeOptCounter::PM_PSD:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
void PM_BbInhibitOptCounter::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOptCounter::PM_PSC:
        case PM_TypeOptCounter::PM_PSD:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OPT, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
ostream& PM_BbInhibitOptCounter::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOptCounter::PM_PSC] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOptCounter::PM_PSD] );
    
    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbInhibitOptCounter::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOptCounter::PM_PSC] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOptCounter::PM_PSD] );

    return theStream;

}