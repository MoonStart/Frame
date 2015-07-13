/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_INTFREGION_H
#define SNMP_INTFREGION_H

#include <SNMP/SNMP_Region.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ErrorService/FC_Error.h>

class SNMP_BbIntfStatsRequest;
class SNMP_BbIntfStatsCfg;
class SNMP_BbIntfStatsData;
class SNMP_BbIntfCount;

typedef SNMP_BbRegion<SNMP_BbIntfStatsRequest>          SNMP_IntfStatsReqRegion;
typedef SNMP_BbRegion<SNMP_BbIntfStatsCfg>              SNMP_IntfStatsCfgRegion;
typedef SNMP_BbRegion<SNMP_BbIntfCount>                 SNMP_IntfCountRegion;
typedef SNMP_BbRegion<SNMP_BbIntfStatsData>             SNMP_IntfStatsDataRegion;

#endif // SNMP_INTFREGION_H
