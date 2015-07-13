/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#include <SNMP/SNMP_IntfStatsConfigController.h>
#include <SNMP/SNMP_SystemData.h>

void SNMP_IntfConfigController::UpdateConfig()
{
    SNMP_BbIntfStatsData& dataObj = static_cast<SNMP_BbIntfStatsData&> ((*myDataRegion)[0]);
    SNMP_BbIntfStatsCfg& cfgObj = static_cast<SNMP_BbIntfStatsCfg&> ((*myCfgRegion)[0]);

    // Enable/disable collection mode
    if (cfgObj.IsCollectionEnabled()) 
    {
        if (!dataObj.IsCollectionEnabled()) 
        {
            dataObj.EnableCollection();
        }
    }
    else
    {
        if (dataObj.IsCollectionEnabled()) 
        {
            // The reset call disables the collection also.
            dataObj.DisableCollection();
            dataObj.ResetAll();
        }
    }
}

