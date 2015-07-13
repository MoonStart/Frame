/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     3 August, 2001 Steve Thiffault.
 DESCRIPTION:   This file contains global definitions for PM
                used internally.
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <CommonTypes/CT_Telecom.h>
#include <PM_Def.h>


//-----------------------------------------------------------------
FC_Time PM_GetAccumulationPeriod(CT_PM_Period thePeriod, FC_Time theCurrentTime, time_t thePstOffset)
{
    switch (thePeriod)
    {
    case CT_PM_PERIOD_15_MINUTES:
        {
        // Compute period start time.
        theCurrentTime -= (theCurrentTime % CT_PM_NUMBER_OF_SEC_IN_15M);

        return theCurrentTime;
        }
        //break;
    case CT_PM_PERIOD_1_DAY:
        {
        // Determine total offset to remove before computing period start time:
        // Period offset - time zone offset (contain daylight saving offset if enable).
        int timeOffset = (int)thePstOffset -
                         FC_TimeService::Instance()->GetLocalTimeOffset(theCurrentTime.GetUTCTime());
        FC_Time timeRef(theCurrentTime.GetUTCTime() - timeOffset);
        FC_Time result(0);

        // Compute period start time.
        timeRef -= (timeRef % CT_PM_NUMBER_OF_SEC_IN_1DAY);

        // Put back total offset to computed period start time.
        result.SetUTCTime(timeRef.GetUTCTime() + timeOffset);

        return result;
        }
        //break;
    case CT_PM_PERIOD_UNKNOWN:
    default:
        FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
        return NULL;
        //break;
    }

}

//-----------------------------------------------------------------
CT_PM_Side PM_GetGenericSide( CT_PM_Side thePmSide )
{
    CT_PM_Side pmSide = CT_PM_UNKNOWN_SIDE;

    if( thePmSide >= CT_PM_PORT_SIDE_0 && thePmSide <= CT_PM_PORT_SIDE_88 )
    {
        pmSide = CT_PM_PORT_SIDE;
    }
    else if (thePmSide >= CT_PM_LINE_SIDE_0 && thePmSide <= CT_PM_LINE_SIDE_9)
    {
        pmSide = CT_PM_LINE_SIDE;
    }
    else
    {
        pmSide = CT_PM_UNKNOWN_SIDE;
    }

    return pmSide;
}
