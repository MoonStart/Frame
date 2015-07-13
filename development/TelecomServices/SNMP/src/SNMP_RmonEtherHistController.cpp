/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:
 TARGET   :
 AUTHOR   :
 DESCRIPTION:
--------------------------------------------------------------------------*/

#include <SNMP/SNMP_RmonEtherHistController.h>
#include <SNMP/SNMP_RmonEtherHistData.h>
#include <SNMP/SNMP_RmonConfig.h>
#include <SNMP/SNMP_Config.h>
#include <SNMP/SNMP_SystemData.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_SNMP_Utilization.h>

SNMP_RmonEtherHistIvalController::SNMP_RmonEtherHistIvalController() :
myStorageRegion(NULL),
mySysUpTimeRegion(NULL)
{
}

SNMP_RmonEtherHistIvalController::SNMP_RmonEtherHistIvalController(SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                 SNMP_SysUpTimeRegion* theSysUpTimeRegion) :
myStorageRegion(theStorageRegion),
mySysUpTimeRegion(theSysUpTimeRegion)
{
}

SNMP_RmonEtherHistIvalController::~SNMP_RmonEtherHistIvalController()
{
}

void SNMP_RmonEtherHistIvalController::UpdateSampleStart(vector<CT_SNMP_Utilization>& theUtilizationMonitors)
{
    size_t loopIndex;

    // Obtain current sysUpTime
    SNMP_BbSystemUpTime& sysUpTimeObj = (*mySysUpTimeRegion)[0];
    CT_SNMP_TimeTicks currSysUpTime = sysUpTimeObj.GetSysUpTime();

    for (loopIndex = 0; loopIndex < myStorageRegion->Size(); loopIndex++)
    {
        SNMP_BbRmonEtherHistStorage& histStorage = (*myStorageRegion)[loopIndex];
        if (histStorage.IsCollectionEnabled())
        {
            SNMP_RmonEtherHistSample& currHistSample = histStorage.GetCurrentSample();
            // Determine interval period in TickTimes
            CT_SNMP_TimeTicks ivalPeriod = static_cast<CT_SNMP_TimeTicks> (histStorage.GetInterval() * 100);

			//currSysUpTime will reset to 0, when currSysUpTime is set to 0 from controller card.
			if(currHistSample.GetIntervalStart() > currSysUpTime)
				currHistSample.SetIntervalStart(currSysUpTime);
			
            if (currHistSample.GetIntervalStart() + ivalPeriod <= currSysUpTime)
            {
                SNMP_RmonEtherHistSample& nextHistSample = histStorage.GetNextSampleToFill();
                nextHistSample.SetIntervalStart(currSysUpTime);
                // Restart the utilzation monitor for new weighted average
                // calculation for the new sample.
                theUtilizationMonitors[loopIndex].EndOfPeriod();
            }
        }
    }
}


