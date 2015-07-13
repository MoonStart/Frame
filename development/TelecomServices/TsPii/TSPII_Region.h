/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/19
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#ifndef TSPII_REGION_H
#define TSPII_REGION_H

#include "Blackboard/FC_BbRegionAsVector.h"
#include "CommonTypes/CT_SystemIds.h"

class TSPII_BaseIf;
class TSPII_DwIf;
class TSPII_TcmIf;
class TSPII_FecIf;
class TSPII_GccIf;
class TSPII_GccMapIf;
class TSPII_GccMapSimIf;
class TSPII_OchOHIf;
class TSPII_OmsOHIf;
class TSPII_OpticalIf;
class TSPII_OsaIf;
class TSPII_OtsOHIf;
class TSPII_PilotToneIf;
class TSPII_PipeIf;
class TSPII_RsIf;
class TSPII_IPCountersIf;
class TSPII_MsIf;
class TSPII_HopIf;
class TSPII_GfpIf;
class TSPII_T1E1If;
class TSPII_1NSelIf;
class TSPII_XcIf;
class TSPII_ClkSelIf;
class TSPII_RmonIf;
class TSPII_DcclIf;
class TSPII_DrtrIf;
class TSPII_DdltIf;
class TSPII_LagIf;
class TSPII_MacIf;
class TSPII_EvcIf;
class TSPII_VcgIf;
class TSPII_L2If;
class TSPII_SsmIf;
class TSPII_SncIf;
class TSPII_FabIf;
class TSPII_SwitchIf;
class TSPII_IBETHIf;

const unsigned int TSPII_MAX_SLOT           = NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF;
const unsigned int TSPII_MAX_UNIT           = 2;
const unsigned int TSPII_MAX_PIPE           = 2;
const unsigned int TSPII_MAX_PUMP           = 2;
const unsigned int TSPII_MAX_OSC            = 2;
const unsigned int TSPII_MAX_OSA            = 2;
const unsigned int TSPII_MAX_PT             = 2;
const unsigned int TSPII_MAX_OCH            = 88;
const unsigned int TSPII_MAX_OPT            = 88; // OPT regions - ROADM ADD ports
const unsigned int TSPII_MAX_UPDATE_ACTIONS = TSPII_MAX_SLOT +1; //+1 for OSC channel update actions

class TSPII_BaseRegion : public FC_BbRegionAsVector
{
public:
    /* Constructor */     TSPII_BaseRegion(const FC_BbKey & theKey);
    virtual FC_BbObject * Allocate(bbindex_t theIndex); 
    virtual void          Deallocate(FC_BbObject* theObject);
    virtual void          AddAt(bbindex_t theIndex, TSPII_BaseIf * theObject);
    virtual void          RemoveAt(bbindex_t theIndex);
    TSPII_BaseIf &        operator[](bbindex_t theIndex) const;
protected:
    virtual void          AddAt(bbindex_t theIndex,  FC_BbObject* theObject); //implement this to prevent vxWorks Warning
};

template <class T> class TSPII_Region : public TSPII_BaseRegion
{
public:
    TSPII_Region(const FC_BbKey theKey) : TSPII_BaseRegion(theKey) {}
    T & operator[] (bbindex_t theIndex) const { return static_cast<T &>(*(*myObjVectorPtr)[theIndex]); }
};

typedef TSPII_Region<TSPII_DwIf>         TSPII_DwRegion;
typedef TSPII_Region<TSPII_TcmIf>        TSPII_TcmRegion;
typedef TSPII_Region<TSPII_FecIf>        TSPII_FecRegion;
typedef TSPII_Region<TSPII_GccIf>        TSPII_GccRegion;
typedef TSPII_Region<TSPII_GccMapIf>     TSPII_GccMapRegion;
typedef TSPII_Region<TSPII_OchOHIf>      TSPII_OchOHRegion;
typedef TSPII_Region<TSPII_OmsOHIf>      TSPII_OmsOHRegion;
typedef TSPII_Region<TSPII_OpticalIf>    TSPII_OpticalRegion;
typedef TSPII_Region<TSPII_OsaIf>        TSPII_OsaRegion;
typedef TSPII_Region<TSPII_OtsOHIf>      TSPII_OtsOHRegion;
typedef TSPII_Region<TSPII_PilotToneIf>  TSPII_PilotToneRegion;
typedef TSPII_Region<TSPII_PipeIf>       TSPII_PipeRegion;
typedef TSPII_Region<TSPII_RsIf>         TSPII_RsRegion;
typedef TSPII_Region<TSPII_IPCountersIf> TSPII_IPCountersRegion;
typedef TSPII_Region<TSPII_MsIf>         TSPII_MsRegion;
typedef TSPII_Region<TSPII_HopIf>        TSPII_HopRegion;
typedef TSPII_Region<TSPII_GfpIf>        TSPII_GfpRegion;
typedef TSPII_Region<TSPII_T1E1If>       TSPII_T1E1Region;
typedef TSPII_Region<TSPII_1NSelIf>      TSPII_1NSelRegion;
typedef TSPII_Region<TSPII_VcgIf>        TSPII_VcgRegion;
typedef TSPII_Region<TSPII_XcIf>         TSPII_XcRegion;
typedef TSPII_Region<TSPII_ClkSelIf>     TSPII_ClkSelRegion;
typedef TSPII_Region<TSPII_RmonIf>       TSPII_RmonRegion;
typedef TSPII_Region<TSPII_DcclIf>       TSPII_DcclRegion;
typedef TSPII_Region<TSPII_DrtrIf>       TSPII_DrtrRegion;
typedef TSPII_Region<TSPII_DdltIf>       TSPII_DdltRegion;
typedef TSPII_Region<TSPII_LagIf>        TSPII_LagRegion;
typedef TSPII_Region<TSPII_MacIf>        TSPII_MacRegion;
typedef TSPII_Region<TSPII_EvcIf>        TSPII_EvcRegion;
typedef TSPII_Region<TSPII_VcgIf>        TSPII_VcgRegion;
typedef TSPII_Region<TSPII_L2If>         TSPII_L2Region;
typedef TSPII_Region<TSPII_L2If>         TSPII_L2LagRegion;
typedef TSPII_Region<TSPII_L2If>         TSPII_L2VcgRegion;
typedef TSPII_Region<TSPII_SsmIf>        TSPII_SsmRegion;
typedef TSPII_Region<TSPII_SncIf>        TSPII_SncRegion;
typedef TSPII_Region<TSPII_FabIf>        TSPII_FabRegion;
typedef TSPII_Region<TSPII_SwitchIf>     TSPII_SwitchRegion;
typedef TSPII_Region<TSPII_IBETHIf>      TSPII_IBETHRegion;


#endif // TSPII_REGION_H
