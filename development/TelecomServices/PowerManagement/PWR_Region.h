/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/

#ifndef PWR_REGION_H
#define PWR_REGION_H

#include "TelCommon/TEL_BbRegionBaseImp.h"
#include "TelCommon/TEL_BbRegionBaseImpWithIndex.h"



class PWR_Cx16uOchCfgObject ;
class PWR_Cx16uOchMonObject;
class PWR_Cx16uEventObject;

typedef TEL_BbRegionBaseImp<PWR_Cx16uOchCfgObject > PWR_Cx16uOchCfgRegion;
typedef TEL_BbRegionBaseImp<PWR_Cx16uOchMonObject> PWR_Cx16uOchMonRegion;

typedef TEL_BbRegionBaseImp<PWR_Cx16uEventObject>  PWR_Cx16uEventRegion;



#endif // PWR_REGION_H
