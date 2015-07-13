/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 13, 2001 Sebastien Cossette.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitData.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C9255BB0070
PM_BbInhibitData::PM_BbInhibitData(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeData::PM_PARAM_NUM-1; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C9255BB007B
PM_BbInhibitData::~PM_BbInhibitData()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB0084
void PM_BbInhibitData::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for Data parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_DATA, true);
    // Set TCA Inhibition active for Data parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_DATA, true);

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB008E
bool PM_BbInhibitData::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeData::PM_LOSS:
        case PM_TypeData::PM_CV:
        case PM_TypeData::PM_SE:
        case PM_TypeData::PM_SEFS:
        case PM_TypeData::PM_SES:
        case PM_TypeData::PM_ES:
        case PM_TypeData::PM_SE_HIGH:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_DATA);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB0098
void PM_BbInhibitData::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeData::PM_LOSS:
        case PM_TypeData::PM_CV:
        case PM_TypeData::PM_SE:
        case PM_TypeData::PM_SEFS:
        case PM_TypeData::PM_SES:
        case PM_TypeData::PM_ES:
        case PM_TypeData::PM_SE_HIGH:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_DATA, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE002EB
bool PM_BbInhibitData::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeData::PM_LOSS:
        case PM_TypeData::PM_CV:
        case PM_TypeData::PM_SE:
        case PM_TypeData::PM_SEFS:
        case PM_TypeData::PM_SES:
        case PM_TypeData::PM_ES:
        case PM_TypeData::PM_SE_HIGH:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_DATA);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE00363
void PM_BbInhibitData::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeData::PM_LOSS:
        case PM_TypeData::PM_CV:
        case PM_TypeData::PM_SE:
        case PM_TypeData::PM_SEFS:
        case PM_TypeData::PM_SES:
        case PM_TypeData::PM_ES:
        case PM_TypeData::PM_SE_HIGH:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_DATA, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB00AB
ostream& PM_BbInhibitData::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_LOSS])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_CV]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_SE]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_SEFS])
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_SES] )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_ES]  )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeData::PM_SE_HIGH]  );
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB00B6
istream& PM_BbInhibitData::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_LOSS])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_CV]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_SE]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_SEFS])
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_SES] )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_ES]  )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeData::PM_SE_HIGH]  );

    return theStream;

}
