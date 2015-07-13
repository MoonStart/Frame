/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitCop.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F5302B3
PM_BbInhibitCop::PM_BbInhibitCop(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeCop::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5302BD
PM_BbInhibitCop::~PM_BbInhibitCop()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5302C7
void PM_BbInhibitCop::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for optical channel parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_COP, true);
    // Set TCA Inhibition active for optical channel parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_COP, true);

}

//-----------------------------------------------------------------
//##ModelId=3C9255B301C2
bool PM_BbInhibitCop::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeCop::PM_COP:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_COP);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3C9255B301EA
void PM_BbInhibitCop::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeCop::PM_COP:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_COP, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CDA008A
bool PM_BbInhibitCop::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeCop::PM_COP:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_COP);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CDA00DA
void PM_BbInhibitCop::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeCop::PM_COP:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_COP, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5302C9
ostream& PM_BbInhibitCop::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeCop::PM_COP]);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5302DB
istream& PM_BbInhibitCop::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeCop::PM_COP]);

    return theStream;

}
