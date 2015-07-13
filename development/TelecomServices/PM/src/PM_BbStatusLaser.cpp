/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   Update and keep the PM status of the Laser.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_TxOptStatus.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbStatusLaser.h>


//-----------------------------------------------------------------
//##ModelId=3C20AB6C0208
PM_BbStatusLaser::PM_BbStatusLaser ()
:PM_BbStatus(PM_TypeLaser::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6C0212
PM_BbStatusLaser::~PM_BbStatusLaser ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C50163102F8
void PM_BbStatusLaser::Update(MON_TxOptStatus& theTxOptMonitor) 
{
    myParam[PM_TypeLaser::PM_LT].SignedValue  = theTxOptMonitor.GetLaserTemp();
    myParam[PM_TypeLaser::PM_LBC].SignedValue = theTxOptMonitor.GetLaserBiasCurrent();

    myValidity[PM_TypeLaser::PM_LT] = theTxOptMonitor.IsValidated();
    myValidity[PM_TypeLaser::PM_LBC] = myValidity[PM_TypeLaser::PM_LT];

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6C023A
ostream& PM_BbStatusLaser::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myParam[PM_TypeLaser::PM_LT].SignedValue )
                     << FC_InsertVar(myParam[PM_TypeLaser::PM_LBC].SignedValue);

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6C024E
istream& PM_BbStatusLaser::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myParam[PM_TypeLaser::PM_LT].SignedValue )
                     >> FC_ExtractVar(myParam[PM_TypeLaser::PM_LBC].SignedValue);

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F0F002A
void PM_BbStatusLaser::Init(restart_type theRestart)
{
    PM_BbStatus::Init(theRestart);

}
