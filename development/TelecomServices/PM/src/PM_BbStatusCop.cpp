/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   Update and keep the PM status of Optical Channel.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OchStatus.h>
#include <Monitoring/MON_OptStatus.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbStatusCop.h>


//-----------------------------------------------------------------
//##ModelId=3C5016320214
PM_BbStatusCop::PM_BbStatusCop ()
    :PM_BbStatus(PM_TypeCop::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C5016320215
PM_BbStatusCop::~PM_BbStatusCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C5016320233
void PM_BbStatusCop::Update(MON_OchStatus& theCopMonitor, bool theAltPower) 
{
    if (theAltPower) 
    {
        myParam[PM_TypeCop::PM_COP].SignedValue = theCopMonitor.GetPreAmpPower();   
    }
    else
    {
        myParam[PM_TypeCop::PM_COP].SignedValue = theCopMonitor.GetPower();
    }

    myValidity[PM_TypeCop::PM_COP] = theCopMonitor.IsValidated();
}

//-----------------------------------------------------------------
void PM_BbStatusCop::Update(MON_OptStatus& theCopMonitor) 
{
    myParam[PM_TypeCop::PM_COP].SignedValue = theCopMonitor.GetTotalInputPower();

    myValidity[PM_TypeCop::PM_COP] = theCopMonitor.IsValidated();

}

//-----------------------------------------------------------------
//##ModelId=3C501632023D
ostream& PM_BbStatusCop::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myParam[PM_TypeCop::PM_COP].SignedValue)
                     << FC_InsertVar(myValidity[PM_TypeCop::PM_COP]);

}

//-----------------------------------------------------------------
//##ModelId=3C5016320248
istream& PM_BbStatusCop::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myParam[PM_TypeCop::PM_COP].SignedValue)
                     >> FC_ExtractVar(myValidity[PM_TypeCop::PM_COP]);

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F0F026F
void PM_BbStatusCop::Init(restart_type theRestart)
{
    PM_BbStatus::Init(theRestart);

}
