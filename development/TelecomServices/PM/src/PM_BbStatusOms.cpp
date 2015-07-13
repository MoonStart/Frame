/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Update and keep the PM status of Oms parameters.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OmsStatus.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbStatusOms.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CF70028
PM_BbStatusOms::PM_BbStatusOms ()
:PM_BbStatus(PM_TypeOms::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF70031
PM_BbStatusOms::~PM_BbStatusOms ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF70063
void PM_BbStatusOms::Update(MON_OmsStatus& theOmsMonitor) 
{
    myParam[PM_TypeOms::PM_OPR].SignedValue = theOmsMonitor.GetOmsInputPower();
    myParam[PM_TypeOms::PM_OPT].SignedValue = theOmsMonitor.GetOmsOutputPower();

    myValidity[PM_TypeOms::PM_OPR] = theOmsMonitor.ForPmIsValidated();
    myValidity[PM_TypeOms::PM_OPT] = myValidity[PM_TypeOms::PM_OPR];

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF700E6
ostream& PM_BbStatusOms::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myParam[PM_TypeOms::PM_OPR].SignedValue)
                     << FC_InsertVar(myParam[PM_TypeOms::PM_OPT].SignedValue)
                     << FC_InsertVar(myValidity[PM_TypeOms::PM_OPR])
                     << FC_InsertVar(myValidity[PM_TypeOms::PM_OPT]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF70104
istream& PM_BbStatusOms::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myParam[PM_TypeOms::PM_OPR].SignedValue)
                     >> FC_ExtractVar(myParam[PM_TypeOms::PM_OPT].SignedValue)
                     >> FC_ExtractVar(myValidity[PM_TypeOms::PM_OPR])
                     >> FC_ExtractVar(myValidity[PM_TypeOms::PM_OPT]);
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF7003B
void PM_BbStatusOms::Init(restart_type theRestart)
{
    PM_BbStatus::Init(theRestart);

}
