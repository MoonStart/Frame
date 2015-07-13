/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Action invoked when a request of current or previous
                data was performed on Admin.
--------------------------------------------------------------------------*/

#include <PM_RegionImp.h>
#include <PM_BbRequest.h>
#include <PM_BbValue.h>
#include "PM_RequestAction.h"


//-----------------------------------------------------------------
//##ModelId=3C1F6F620324
PM_RequestAction::PM_RequestAction(PM_RegionImp<PM_BbRequest>& theRequestRegion,
                                   PM_RegionImp<PM_BbValue>& the15MValueCurrentRegion,
                                   PM_RegionImp<PM_BbValue>& theDayValueCurrentRegion,
                                   PM_RegionImp<PM_BbValue>& the15MValuePreviousRegion,
                                   PM_RegionImp<PM_BbValue>& theDayValuePreviousRegion,
                                   uint32 numberOfObject):
    myRequestRegion(theRequestRegion),
    my15MCurrentValueRegion(the15MValueCurrentRegion),
    myDayCurrentValueRegion(theDayValueCurrentRegion),
    my15MPreviousValueRegion(the15MValuePreviousRegion),
    myDayPreviousValueRegion(theDayValuePreviousRegion),
    myNumberOfObject(numberOfObject),
    myRequestId(NULL)
{
    theRequestRegion.AddObserver(this);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F620341
PM_RequestAction::~PM_RequestAction()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F620342
void PM_RequestAction::Run(FC_Object* theObject)
{
    if (myRequestRegion[0].GetRequestId() != myRequestId)
    {
        uint32 index;
        uint32 regionSize15m = my15MCurrentValueRegion.Size();
        uint32 regionSizeDay = myDayCurrentValueRegion.Size();

        if( regionSize15m != regionSizeDay)
        {
            FC_REPORT_ERROR(FC_SWError, "15M and Day current value region size mismatch");
        }

        // A Get Request is pending at the Admin, 
        // force a send of the requested port/period of the value region.
        // Change the request Id of the requested register in the value region.

        // Retrieve the request id.
        /*
        fc_cout << "myRequestRegion[0].GetRequestId() = "
                << myRequestRegion[0].GetRequestId()
                << ", myRequestId = " << myRequestId << endl;
        */
        myRequestId = myRequestRegion[0].GetRequestId();
        
        //
        // Force a transfer of current and previous data.
        //
        for (index = 0; index < regionSizeDay; index++)
        {
            myDayPreviousValueRegion[index].SetRequestId(myRequestId);
            myDayCurrentValueRegion[index].SetRequestId(myRequestId);
        }

        for (index = 0; index < regionSize15m; index++)
        {
            my15MPreviousValueRegion[index].SetRequestId(myRequestId);
            my15MCurrentValueRegion[index].SetRequestId(myRequestId);
        }

        // Force a transfer of previous day period.
        myDayPreviousValueRegion.IncModificationCounter();
        myDayPreviousValueRegion.UpdateNotify();

        // Force a transfer of current day period.
        myDayCurrentValueRegion.IncModificationCounter();
        myDayCurrentValueRegion.UpdateNotify();

        // Force a transfer of previous 15 minutes period.
        my15MPreviousValueRegion.IncModificationCounter();
        my15MPreviousValueRegion.UpdateNotify();

        // Force a transfer of current 15 minutes period.
        //
        // 15-MIN Current always has to be last, since PMA
        // only observe this region and not the other three.
        // FC_Blackboard serializes the regions and wake up
        // the actions in the same order, making 15-MIN Current
        // the last region ensures all other three regions are
        // updated before PMA_DataRequestAction is woken up.
        my15MCurrentValueRegion.IncModificationCounter();
        my15MCurrentValueRegion.UpdateNotify();

    }

}
