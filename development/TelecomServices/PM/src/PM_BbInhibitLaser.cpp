/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitLaser.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F5803A1
PM_BbInhibitLaser::PM_BbInhibitLaser(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeLaser::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5803AC
PM_BbInhibitLaser::~PM_BbInhibitLaser()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5803B5
void PM_BbInhibitLaser::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for laser parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_LASER, true);
    // Set TCA Inhibition active for optical parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_LASER, true);

}

//-----------------------------------------------------------------
//##ModelId=3C9255AF0130
bool PM_BbInhibitLaser::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeLaser::PM_LT:
        case PM_TypeLaser::PM_LBC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_LASER);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3C9255AF0158
void PM_BbInhibitLaser::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeLaser::PM_LT:
        case PM_TypeLaser::PM_LBC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_LASER, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CD50245
bool PM_BbInhibitLaser::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeLaser::PM_LT:
        case PM_TypeLaser::PM_LBC:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_LASER);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CD5029F
void PM_BbInhibitLaser::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeLaser::PM_LT:
        case PM_TypeLaser::PM_LBC:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_LASER, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5803BF
ostream& PM_BbInhibitLaser::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeLaser::PM_LT])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeLaser::PM_LBC]);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5803CA
istream& PM_BbInhibitLaser::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeLaser::PM_LT])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeLaser::PM_LBC]);

    return theStream;

}
