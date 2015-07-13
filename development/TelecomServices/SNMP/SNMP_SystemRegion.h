/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_SYSTEMREGION_H
#define SNMP_SYSTEMREGION_H

#include <SNMP/SNMP_Region.h>
#include <CommonTypes/CT_SNMP_Definition.h>

class SNMP_BbSystemUpTime;
class SNMP_BbSystemInfo;

typedef SNMP_BbRegion<SNMP_BbSystemUpTime>                    SNMP_SysUpTimeRegion;
typedef SNMP_BbRegion<SNMP_BbSystemInfo>                      SNMP_SysInfoRegion;


#endif // SNMP_SYSTEMREGION_H
