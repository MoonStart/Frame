/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor 
                Laser.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OtsStatus.h>

#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbStatusLaser.h>
#include <PM/PM_CollectorLaser.h>


//-----------------------------------------------------------------
//##ModelId=3C50178201C7
PM_CollectorLaser::PM_CollectorLaser (PM_GenericApplication&    theGenericApplication,
                                      FC_OneShotProcess         &theProcessorProcess,
                                      uint32                    theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_LASER_STRING, theNumberOfPort),
    myStatusLaser(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C50178201D2
PM_CollectorLaser::~PM_CollectorLaser ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C50178201DC
void PM_CollectorLaser::Init()
{
    // Initialize pointer to laser status region.
    myStatusLaser = &(*myGenericApplication.GetRegionStatusLaser());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3C50178201E5
void PM_CollectorLaser::ProcessData() 
{
    MON_TxOptStatus &txStatusObject = (MON_TxOptStatus &)(*(myGenericApplication.GetMonTxApplication().GetStatusRegion()))[0];


    // Update Optical gauges.
    (*myStatusLaser)[0].Update(txStatusObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
