/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbInhibitEon.h>
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3FA1610B016F
PM_BbInhibitEon::PM_BbInhibitEon(uint32 dummy1, uint32 dummy2)
    :PM_BbInhibit(dummy1, dummy2)
{
    // Nothing to do for now.
    for (uint8 i=0; i<PM_TypeEon::PM_PARAM_NUM; i++)
        myPrivateResetCountCurrent[i] = 0;
}

//-----------------------------------------------------------------
//##ModelId=3FA1610B017E
PM_BbInhibitEon::~PM_BbInhibitEon()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B0180
void PM_BbInhibitEon::Reset()
{
    PM_BbInhibit::Reset();

    // Set Inhibition active for EON parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_EON, true);
    // Set TCA Inhibition active for EON parameters.
    SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_EON, true);

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B0182
bool PM_BbInhibitEon::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeEon::PM_ICMPDUR:
        case PM_TypeEon::PM_ICMPDUT:
        case PM_TypeEon::PM_ICMPER:
        case PM_TypeEon::PM_ICMPTTLER:
        case PM_TypeEon::PM_IPADDER:
        case PM_TypeEon::PM_IPDISCR:
        case PM_TypeEon::PM_IPDISCT:
        case PM_TypeEon::PM_IPHDRR:
        case PM_TypeEon::PM_IPNOROUTEST:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_EON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B0185
void PM_BbInhibitEon::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeEon::PM_ICMPDUR:
        case PM_TypeEon::PM_ICMPDUT:
        case PM_TypeEon::PM_ICMPER:
        case PM_TypeEon::PM_ICMPTTLER:
        case PM_TypeEon::PM_IPADDER:
        case PM_TypeEon::PM_IPDISCR:
        case PM_TypeEon::PM_IPDISCT:
        case PM_TypeEon::PM_IPHDRR:
        case PM_TypeEon::PM_IPNOROUTEST:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_EON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B0190
bool PM_BbInhibitEon::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{
    bool inhibitState = false;


    switch(theParameter)
    {
        case PM_TypeEon::PM_ICMPDUR:
        case PM_TypeEon::PM_ICMPDUT:
        case PM_TypeEon::PM_ICMPER:
        case PM_TypeEon::PM_ICMPTTLER:
        case PM_TypeEon::PM_IPADDER:
        case PM_TypeEon::PM_IPDISCR:
        case PM_TypeEon::PM_IPDISCT:
        case PM_TypeEon::PM_IPHDRR:
        case PM_TypeEon::PM_IPNOROUTEST:
            inhibitState = GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_EON);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

    return inhibitState;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B0193
void PM_BbInhibitEon::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    switch(theParameter)
    {
        case PM_TypeEon::PM_ICMPDUR:
        case PM_TypeEon::PM_ICMPDUT:
        case PM_TypeEon::PM_ICMPER:
        case PM_TypeEon::PM_ICMPTTLER:
        case PM_TypeEon::PM_IPADDER:
        case PM_TypeEon::PM_IPDISCR:
        case PM_TypeEon::PM_IPDISCT:
        case PM_TypeEon::PM_IPHDRR:
        case PM_TypeEon::PM_IPNOROUTEST:
            SetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_EON, theBoolVal);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: Parameter not supported" );
            break;
    }

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B019D
ostream& PM_BbInhibitEon::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord)
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPDUR]     )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPDUT]     )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPER]      )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPTTLER]   )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPADDER]     )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPDISCR]     )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPDISCT]     )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPHDRR]      )
              << FC_InsertVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPNOROUTEST] );
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B01A0
istream& PM_BbInhibitEon::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord)
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPDUR]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPDUT]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPER]      )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_ICMPTTLER]   )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPADDER]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPDISCR]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPDISCT]     )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPHDRR]      )
              >> FC_ExtractVar(myPrivateResetCountCurrent[PM_TypeEon::PM_IPNOROUTEST] );

    return theStream;

}
