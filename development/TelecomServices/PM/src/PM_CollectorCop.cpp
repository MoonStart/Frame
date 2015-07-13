/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Optical Channel.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_OchStatus.h>
#include <Monitoring/MON_AppIf.h>

#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbStatusCop.h>
#include <PM/PM_BbDefectCop.h>
#include <PM/PM_CollectorCop.h>


//-----------------------------------------------------------------
//##ModelId=3C1F8E7B01CC
PM_CollectorCop::PM_CollectorCop (PM_GenericApplication&    theGenericApplication,
                                  FC_OneShotProcess         &theProcessorProcess,
                                  uint32                    theNumberOfPort,
                                  bool                      theObtainDataFromOpticalLayer,
                                  bool                      theObtainAltPower) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_COP_STRING, theNumberOfPort),
    myStatusCop(NULL),
    myDefectCop(NULL),
    myObtainDataFromOpticalLayer(theObtainDataFromOpticalLayer),
    myObtainAltPower(theObtainAltPower)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8E7B01E0
PM_CollectorCop::~PM_CollectorCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8E7B01E2
void PM_CollectorCop::Init()
{
    // Initialize pointer to optical channel status and defect regions.
    myStatusCop = &(*myGenericApplication.GetRegionStatusCop());
    myDefectCop = &(*myGenericApplication.GetRegionDefectCop());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3C1F8E7B01EA
void PM_CollectorCop::ProcessData()
{
    if (myObtainDataFromOpticalLayer)
    {
        for(uint32 i = 0; i < myNumberOfPort; i++)
        {
            MON_OptStatus &statusObject = (MON_OptStatus &)(*(myGenericApplication.GetMonApplication(i).GetStatusRegion()))[0];
            MON_OptDefects &defectsObject = (MON_OptDefects &)(*(myGenericApplication.GetMonApplication(i).GetDefectsRegion()))[0];

            // Update Optical Channel gauges and defects.
            (*myStatusCop)[(bbindex_t)i].Update(statusObject);
            (*myDefectCop)[(bbindex_t)i].Update(defectsObject);
        }
    }
    else
    {
        for(uint32 i = 0; i < myNumberOfPort; i++)
        {
            MON_OchStatus &statusObject = (MON_OchStatus &)(*(myGenericApplication.GetMonApplication().GetStatusRegion()))[(bbindex_t)i];
            MON_OchDefects &defectsObject = (MON_OchDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[(bbindex_t)i];

            // Update Optical Channel gauges and defects.
            (*myStatusCop)[(bbindex_t)i].Update(statusObject, myObtainAltPower);
            (*myDefectCop)[(bbindex_t)i].Update(defectsObject);
        }
    }

    // Call base class method.
    PM_Collector::ProcessData();
}


