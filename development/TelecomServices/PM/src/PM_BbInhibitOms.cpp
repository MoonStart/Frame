/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitOms.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E026E
PM_BbInhibitOms::PM_BbInhibitOms(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeOms::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E028D
PM_BbInhibitOms::~PM_BbInhibitOms()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E0296
void PM_BbInhibitOms::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OMS, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OMS, true);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E02AA
bool PM_BbInhibitOms::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOms::PM_OPR:
        case PM_TypeOms::PM_OPT:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OMS);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E02C8
void PM_BbInhibitOms::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOms::PM_OPR:
        case PM_TypeOms::PM_OPT:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_OMS, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E02F0
bool PM_BbInhibitOms::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeOms::PM_OPR:
        case PM_TypeOms::PM_OPT:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OMS);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E0304
void PM_BbInhibitOms::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeOms::PM_OPR:
        case PM_TypeOms::PM_OPT:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_OMS, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E0319
ostream& PM_BbInhibitOms::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOms::PM_OPR])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeOms::PM_OPT]);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9E0340
istream& PM_BbInhibitOms::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOms::PM_OPR])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeOms::PM_OPT]);

    return theStream;

}
