// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_PORTDATAALLOCREGION_H
#define _INC_TSXC_PORTDATAALLOCREGION_H


#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_CrossConnect.h>

//
// This region contains client-side data configuration
// information. It is owned by the smartCard.
//
template <class T>
class TSXC_PortDataAllocRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_PortDataAllocRegion(const FC_BbKey theKey):
                                TEL_BbRegionBaseImp<T>(theKey, 1)
    {
    }

	// Destructor.
    ~TSXC_PortDataAllocRegion()
    {
    }

    // External Interfaces
    bool   IsIngress3cBwAvail(CT_XcTerm* theSrc);
    bool   IsEgress3cBwAvail (CT_XcTerm* theDst);
    bool   IsIngressReconfigurable(CT_XcTerm* theSrc);
    bool   IsEgressReconfigurable (CT_XcTerm* theDst);

    const CT_FAC_StsMap&   GetIngressBwUsage();
    const CT_FAC_StsMap&   GetEgressBwUsage();

    void   SetIngressBwUsage(CT_FAC_StsMap* theIngressMap);
    void   SetEgressBwUsage (CT_FAC_StsMap* theEgressMap);

private:
   
};

//------------------------------------------------------------------------------------
template<class T> bool TSXC_PortDataAllocRegion<T>::IsIngress3cBwAvail(CT_XcTerm* theSrc)
{
    CT_FAC_StsMap   aIngressMap;
    uint8           aNum3cNeeded;
    uint8           aMapIndex;

    aNum3cNeeded = theSrc->FacStsMap->CountSts();
    aIngressMap = (*this)[0].GetIngressMap();

    // Search for available 3c channels.
    for(aMapIndex = 0; (aMapIndex < 192) && (aNum3cNeeded > 0); aMapIndex += 3)
    {
        if ( (aIngressMap.IsInUse(aMapIndex)     == false) &&
             (aIngressMap.IsInUse(aMapIndex + 1) == false) &&
             (aIngressMap.IsInUse(aMapIndex + 2) == false) )
        {
            aNum3cNeeded--;
        }
    }

    // Return true if enough available 3c channels were found.
    return (aNum3cNeeded == 0);
}

//------------------------------------------------------------------------------------
template<class T> bool TSXC_PortDataAllocRegion<T>::IsEgress3cBwAvail(CT_XcTerm* theDst)
{
    CT_FAC_StsMap   aEgressMap;
    uint8           aNum3cNeeded;
    uint8           aMapIndex;

    aNum3cNeeded = theDst->FacStsMap->CountSts();
    aEgressMap = (*this)[0].GetEgressMap();

    // Search for available 3c channels.
    for(aMapIndex = 0; (aMapIndex < 192) && (aNum3cNeeded > 0); aMapIndex += 3)
    {
        if ( (aEgressMap.IsInUse(aMapIndex)     == false) &&
             (aEgressMap.IsInUse(aMapIndex + 1) == false) &&
             (aEgressMap.IsInUse(aMapIndex + 2) == false) )
        {
            aNum3cNeeded--;
        }
    }

    // Return true if enough available 3c channels were found.
    return (aNum3cNeeded == 0);
}

//------------------------------------------------------------------------------------
template<class T> bool TSXC_PortDataAllocRegion<T>::IsIngressReconfigurable(CT_XcTerm* theSrc)
{
    CT_FAC_StsMap   aIngressMap;
    uint8           aNum3cNeeded;
    uint8           aMapIndex;

    aNum3cNeeded = theSrc->FacStsMap->CountSts();
    aIngressMap = (*this)[0].GetIngressMap();

    // Search for all unassigned sts1.
    uint8 aUnusedSts1Num = 0;
    for (aMapIndex = 0; (aMapIndex < 192); aMapIndex++)
    {
        if (aIngressMap.IsInUse(aMapIndex) == false)
        {
            aUnusedSts1Num++;
        }
    }

    // Return true if the number of unassigned sts1 is enough.
    return (aUnusedSts1Num >= aNum3cNeeded * 3);
}

//------------------------------------------------------------------------------------
template<class T> bool TSXC_PortDataAllocRegion<T>::IsEgressReconfigurable(CT_XcTerm* theDst)
{
    CT_FAC_StsMap   aEgressMap;
    uint8           aNum3cNeeded;
    uint8           aMapIndex;

    aNum3cNeeded = theDst->FacStsMap->CountSts();
    aEgressMap = (*this)[0].GetEgressMap();

    // Search for all unassigned sts1.
    uint8 aUnusedSts1Num = 0;
    for (aMapIndex = 0; (aMapIndex < 192); aMapIndex++)
    {
        if (aEgressMap.IsInUse(aMapIndex) == false)
        {
            aUnusedSts1Num++;
        }
    }

    // Return true if the number of unassigned sts1 is enough.
    return (aUnusedSts1Num >= aNum3cNeeded * 3);
}

//------------------------------------------------------------------------------------
template<class T> const CT_FAC_StsMap& TSXC_PortDataAllocRegion<T>::GetIngressBwUsage()
{
    return (*this)[0].GetIngressMap();
}

//------------------------------------------------------------------------------------
template<class T> const CT_FAC_StsMap& TSXC_PortDataAllocRegion<T>::GetEgressBwUsage()
{
    return (*this)[0].GetEgressMap();
}

//------------------------------------------------------------------------------------
template<class T> void TSXC_PortDataAllocRegion<T>::SetIngressBwUsage(CT_FAC_StsMap* theIngressMap)
{
    (*this)[0].SetIngressMap(theIngressMap);
}

//------------------------------------------------------------------------------------
template<class T> void TSXC_PortDataAllocRegion<T>::SetEgressBwUsage(CT_FAC_StsMap* theEgressMap)
{
    (*this)[0].SetEgressMap(theEgressMap);
}

#endif // _INC_TSXC_PORTDATAALLOCREGION_H
