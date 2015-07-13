// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_RSREADYREGION_H
#define _INC_TSXC_RSREADYREGION_H


#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_RsReady.h>
#include <CommonTypes/CT_CardTypes.h>


//
// This region acts as a trigger for TSXC_CfgAction and
// will only be marked valid when CFG RS information matches
// TSPII RS information.
//
template <class T>
class TSXC_RsReadyRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_RsReadyRegion(const FC_BbKey theKey):
                                TEL_BbRegionBaseImp<T>(theKey, 1)
    {
    }

	// Destructor.
    ~TSXC_RsReadyRegion()
    {
    }

private:
   
};

#endif // _INC_TSXC_RSREADYREGION_H

