/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Three Multicast Region interface
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S3MCASTREGION_H
#define _INC_TSXC_S3MCASTREGION_H

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BaseRegion.h>
#include "CommonTypes/CT_AgentFacility.h"


//----------------------------------------------------------------------------
//--- This region is used to store multicast configuration
//
//--- Note:  This region is always created without any objects.
//---        The size of the objects are adjusted when SetMyCardType() method is 
//---        invoked with appropriate card types.
//----------------------------------------------------------------------------

template <class T>  class TSXC_S3McRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_S3McRegion(const FC_BbKey theKey) :
                    TSXC_BaseRegion<T>(theKey)
    {
    }

	// Destructor
    virtual ~TSXC_S3McRegion()
    {
    }

    // External Interfaces
    bool AddMcGroup(uint16            theMcastId,
                    uint8             theMembers,          
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

    bool AddMcGroup(uint16            theMcastId,
                    uint16            theSlotBit,
                    uint16            theMulticastIMUXLMap,
                    uint16            theMulticastIMUXL1Map,
                    uint16            theMulticastIMUXPMap,
                    uint16            theMulticastIMUXP1Map,
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

    bool AddMcGroup(uint16            theMcastId,
                    CT_FAC_StsMap&    theMembers,          
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

    bool DeleteMcGroup(uint16         theMcastId,
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

private:
    virtual void          PopulateSSM();
    virtual void          PopulateOSM40();
    virtual void          PopulateFGSM();
    virtual void          PopulateOSM20();    
    virtual void          PopulateOSM();    
};

//------------------------------------------------------------------------------------
template<class T> bool TSXC_S3McRegion<T>::AddMcGroup(uint16            theMcastId,
                                                      uint8             theMembers,
                                                      CT_XC_CQMID*      theRespId,
                                                      bool              theImmediateCommit)
{
    size_t regionIndex;
    bool   found;
    int    availIndex;
    bool   retVal;

    found = false;
    availIndex = -1;
    retVal = true;

    // Iterate through all objects in region.
    for (regionIndex = 0;
         (regionIndex < (int) this->Size()) && (found == false);
         regionIndex++)
    {
        // If this object contains an mcastId,
        if ((*this)[regionIndex].IsMcastIdSet() == true)
        {
            // If this mcastId equals the one being added,
            // set mcastId members.
            if ((*this)[regionIndex].GetMCastId() == theMcastId)
            {
                (*this)[regionIndex].SetDestination(theMembers);
                found = true;
            }
        }
        // Else this object is available for new mcastId.
        else
        {
            if (availIndex == -1)
            {
                availIndex = regionIndex;
            }
        }
    }

    // If no object found with specified mcastId,
    if (found == false)
    {
        // If available object exists, set mcastId members.
        if (availIndex != -1)
        {
            (*this)[availIndex].SetMCastId(theMcastId);
            (*this)[availIndex].SetDestination(theMembers);
        }
        // Set returnValue since available object not found.
        else
        {
            retVal = false;
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
 
    return retVal;
}

//------------------------------------------------------------------------------------
template<class T> bool TSXC_S3McRegion<T>::AddMcGroup(uint16            theMcastId,
                                                      uint16            theSlotBit,
                                                      uint16            theMulticastIMUXLMap,
                                                      uint16            theMulticastIMUXL1Map,
                                                      uint16            theMulticastIMUXPMap,
                                                      uint16            theMulticastIMUXP1Map,
                                                      CT_XC_CQMID*      theRespId,
                                                      bool              theImmediateCommit)
{
    bool   retVal = true;
    uint8  mcastMembers;

    // Calculate members
    mcastMembers = 0;
    if (theSlotBit & theMulticastIMUXLMap)
    {
        mcastMembers |= CT_XC_S3MC_IMUXL_BIT;
    }
    if (theSlotBit & theMulticastIMUXL1Map)
    {
        mcastMembers |= CT_XC_S3MC_IMUXL1_BIT;
    }
    if (theSlotBit & theMulticastIMUXPMap)
    {
        mcastMembers |= CT_XC_S3MC_IMUXP_BIT;
    }
    if (theSlotBit & theMulticastIMUXP1Map)
    {
        mcastMembers |= CT_XC_S3MC_IMUXP1_BIT;
    }

    if (mcastMembers != 0)
    {
        retVal = AddMcGroup(theMcastId, mcastMembers, theRespId, theImmediateCommit);
    }

    return retVal;
}


//------------------------------------------------------------------------------------
template<class T> bool TSXC_S3McRegion<T>::AddMcGroup(uint16            theMcastId,
                                                      CT_FAC_StsMap&    theMembers,          
                                                      CT_XC_CQMID*      theRespId,
                                                      bool              theImmediateCommit)
{
    size_t regionIndex;
    bool   found;
    int    availIndex;
    bool   retVal;

    found = false;
    availIndex = -1;
    retVal = true;

    // Iterate through all objects in region.
    for (regionIndex = 0;
         (regionIndex < (int) this->Size()) && (found == false);
         regionIndex++)
    {
        // If this object contains an mcastId,
        if ((*this)[regionIndex].IsMcastIdSet() == true)
        {
            // If this mcastId equals the one being added,
            // set mcastId members.
            if ((*this)[regionIndex].GetMCastId() == theMcastId)
            {
                (*this)[regionIndex].SetDestination(theMembers);
                found = true;
            }
        }
        // Else this object is available for new mcastId.
        else
        {
            if (availIndex == -1)
            {
                availIndex = regionIndex;
            }
        }
    }

    // If no object found with specified mcastId,
    if (found == false)
    {
        // If available object exists, set mcastId members.
        if (availIndex != -1)
        {
            (*this)[availIndex].SetMCastId(theMcastId);
            (*this)[availIndex].SetDestination(theMembers);
        }
        // Set returnValue since available object not found.
        else
        {
            retVal = false;
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
 
    return retVal;
}

//------------------------------------------------------------------------------------
template<class T> bool TSXC_S3McRegion<T>::DeleteMcGroup(uint16            theMcastId,
                                                         CT_XC_CQMID*      theRespId,
                                                         bool              theImmediateCommit)
{
    size_t regionIndex;
    bool   found;

    found = false;

    // Iterate through all objects in region.
    for (regionIndex = 0;
         (regionIndex < (int) this->Size()) && (found == false);
         regionIndex++)
    {
        // If this mcastId equals the one being deleted,
        // set mcastId members.
        if ((*this)[regionIndex].GetMCastId() == theMcastId)
        {
            (*this)[regionIndex].InitMCast();
            found = true;
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);

    return found;
}

//-----------------------------------------------------------------------------------
template<class T> void TSXC_S3McRegion<T>::PopulateSSM()
{
    this->Resize(XC_MAX_XC_SSM_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//-----------------------------------------------------------------------------------
template<class T> void TSXC_S3McRegion<T>::PopulateOSM40()
{
    this->Resize(XC_MAX_SSM40_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//-----------------------------------------------------------------------------------
template<class T> void TSXC_S3McRegion<T>::PopulateFGSM()
{
    this->Resize(XC_MAX_FGSM_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//-----------------------------------------------------------------------------------
template<class T> void TSXC_S3McRegion<T>::PopulateOSM20()
{
    this->Resize(XC_MAX_OSM20_XC_IM_ALL * 2 + 1);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//-----------------------------------------------------------------------------------
template<class T> void TSXC_S3McRegion<T>::PopulateOSM()
{
    this->Resize(XC_MAX_OSM_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

#endif // _INC_TSXC_S3MCASTREGION_H
