// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if !defined(AFX_MON_PILOTTONECONTROLLERREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_)
#define AFX_MON_PILOTTONECONTROLLERREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MON_Definitions.h"
#include "MON_Region.h"
#include "MON_OchStatus.h"
#include "MON_OchConfig.h"
#include <TsPii/TSPII_Region.h>


class MON_PilotToneControllerRequest
{
public:
    MON_PilotToneControllerRequest(MON_OchConfigRegion* theOchConfigRegion, 
                                   MON_OchStatusRegion* theOchStatusRegion,
                                   TSPII_PilotToneRegion* theTspiiRegion,
                                   uint32 theBandwidth);
    virtual ~MON_PilotToneControllerRequest();
    MON_OchConfigRegion* GetConfigRegion() const;
    MON_OchStatusRegion* GetStatusRegion() const;
    TSPII_PilotToneRegion* GetTspiiRegion() const;
    uint32 GetBandwidth() const { return myBandwidth;}
    uint32 GetFirstWavelength() const {return myFirstWavelength;}
    bool SetFirstWavelength(uint32 theFirstWavelength);

private:
    MON_OchConfigRegion* myOchConfigRegion;
    MON_OchStatusRegion* myOchStatusRegion;
    TSPII_PilotToneRegion* myTspiiRegion;
    uint32 myFirstWavelength;
    uint32 myBandwidth;
};


#endif // !defined(AFX_MON_PILOTTONECONTROLLERREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_)
