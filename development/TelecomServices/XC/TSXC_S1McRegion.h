/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage One Multicast Region interface
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S1MCASTREGION_H
#define _INC_TSXC_S1MCASTREGION_H

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BaseRegion.h>
#include <QRS/QRS_RequestTypes.h>

//-----------------------------------------------------------------------------------------------------
//--- This region is used to store multicast configuration on SSM modules 
//
//--- Note:  This region is always created without any objects.
//---        The size of the objects are adjusted when SetMyCardType() method is invoked 
//---        with appropriate card types.
//-----------------------------------------------------------------------------------------------------

template <class T>  class TSXC_S1McRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_S1McRegion(const FC_BbKey theKey) :
                    TSXC_BaseRegion<T>(theKey)
    {
    }

    // Destructor
    virtual ~TSXC_S1McRegion()
    {
    }

    // External Interfaces
    bool AddMcGroup(uint16            theMcastId,
                    uint16            theImuxlMembers,
                    uint16            theImuxpMembers,
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

    bool DeleteMcGroup(uint16         theMcastId,
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true);

    void ApplyMcGroupToBothSlices(uint16  theMcastId,
                    QRS_ConnectXcTerm&    theTermToApply,
                    CT_XC_CQMID*          theRespId = NULL,
                    bool                  theImmediateCommit = true);

    void RmvFromMcGroup(uint16            theMcastId,
                    QRS_ConnectXcTerm&    theTermToRmv,
                    CT_XC_CQMID*          theRespId = NULL,
                    bool                  theImmediateCommit = true);

protected:

    virtual void          PopulateSSM();
    virtual void          PopulateOSM40();
    virtual void          PopulateOSM20();
};

// ----------------------------------------------------------------------------------------
template<class T> bool TSXC_S1McRegion<T>::AddMcGroup(uint16            theMcastId,
                                                      uint16            theImuxlMembers,
                                                      uint16            theImuxpMembers,
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
         (regionIndex < this->Size()) && (found == false); 
         regionIndex++)
    {
        // If this object contains an mcastId,
        if ((*this)[regionIndex].IsMcastSet() == true)
        {
            // If this mcastId equals the one being added,
            // set mcastId members.
            if ((*this)[regionIndex].GetMcastId() == theMcastId)
            {
                (*this)[regionIndex].SetMCastImuxLMap(theImuxlMembers);
                (*this)[regionIndex].SetMCastImuxPMap(theImuxpMembers);
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
            (*this)[availIndex].SetMCastImuxLMap(theImuxlMembers);
            (*this)[availIndex].SetMCastImuxPMap(theImuxpMembers);
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

// ----------------------------------------------------------------------------------------
template<class T> bool TSXC_S1McRegion<T>::DeleteMcGroup(uint16            theMcastId,
                                                         CT_XC_CQMID*      theRespId,
                                                         bool              theImmediateCommit)
{
    size_t regionIndex;
    bool   found;

    found = false;

    // Iterate through all objects in region.
    for (regionIndex = 0;
         (regionIndex < this->Size()) && (found == false); 
         regionIndex++)
    {
        // If this mcastId equals the one being deleted,
        // set mcastId members.
        if ((*this)[regionIndex].GetMcastId() == theMcastId)
        {
            (*this)[regionIndex].InitMCast();
            found = true;
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);

    return found;
}

// ----------------------------------------------------------------------------------------
template<class T> void TSXC_S1McRegion<T>::ApplyMcGroupToBothSlices(uint16  theMcastId,
                                                      QRS_ConnectXcTerm&    theTermToApply,
                                                      CT_XC_CQMID*          theRespId,
                                                      bool                  theImmediateCommit)
{ 
    size_t    regionIndex;
    uint16    aImuxMembers;
    CT_SlotId aSlotToApply;

    // Iterate through all objects in region.
    // Note -- Continue after one is found to take care
    //         of multiple indices with same McastId which
    //         occurs when McastIdFlex = McastIdFix
    for (regionIndex = 0;
         (regionIndex < this->Size());
         regionIndex++)
    {
        // If this mcastId equals the one being modified,
        if ((*this)[regionIndex].GetMCastId() == theMcastId)
        {
            // Calculate slot
            aSlotToApply = theTermToApply.FacData.GetSlot() - 1;

            // Add slot to IMUXL Map
            aImuxMembers = (*this)[regionIndex].GetMCastImuxLMap();
            aImuxMembers |= (1 << aSlotToApply);
            (*this)[regionIndex].SetMCastImuxLMap(aImuxMembers);

            // Add slot to IMUXP Map
            aImuxMembers = (*this)[regionIndex].GetMCastImuxPMap();
            aImuxMembers |= (1 << aSlotToApply);
            (*this)[regionIndex].SetMCastImuxPMap(aImuxMembers);
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
}

// ----------------------------------------------------------------------------------------
template<class T> void TSXC_S1McRegion<T>::RmvFromMcGroup(uint16    theMcastId,
                                               QRS_ConnectXcTerm&   theTermToRmv,
                                               CT_XC_CQMID*         theRespId,
                                               bool                 theImmediateCommit)
{
    size_t    regionIndex;
    uint16    aImuxMembers;
    CT_SlotId aSlotToRmv;

    // Iterate through all objects in region.
    // Note -- Continue after one is found to take care
    //         of multiple indices with same McastId which
    //         occurs when McastIdFlex = McastIdFix
    for (regionIndex = 0;
         (regionIndex < this->Size());
         regionIndex++)
    {
        // If this mcastId equals the one being modified,
        if ((*this)[regionIndex].GetMCastId() == theMcastId)
        {
            // Calculate slot
            aSlotToRmv = theTermToRmv.FacData.GetSlot() - 1;

            // If termination is associated with line-side, remove
            // this termination slot from IMUXLMap
            if(theTermToRmv.IsLineTerm())
            {
                aImuxMembers = (*this)[regionIndex].GetMCastImuxLMap();
                aImuxMembers &= ~(1 << aSlotToRmv);
                (*this)[regionIndex].SetMCastImuxLMap(aImuxMembers);
            }
            // If termination is associated with port-side, remove
            // this termination slot from IMUXPMap
            else
            {
                aImuxMembers = (*this)[regionIndex].GetMCastImuxPMap();
                aImuxMembers &= ~(1 << aSlotToRmv);
                (*this)[regionIndex].SetMCastImuxPMap(aImuxMembers);
            }
        }
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
}

//----------------------------------------------------------------------------------------
template<class T> void TSXC_S1McRegion<T>::PopulateSSM()
{
    this->Resize(XC_MAX_FIXED_MCASTID*2);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].InitMCast();
    }
}

//----------------------------------------------------------------------------------------
template<class T> void TSXC_S1McRegion<T>::PopulateOSM40()
{
    this->Resize(XC_MAX_SSM40_FIXED_MCASTID*2);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].InitMCast();
    }
}

//----------------------------------------------------------------------------------------
template<class T> void TSXC_S1McRegion<T>::PopulateOSM20()
{
    this->Resize(XC_MAX_OSM20_FIXED_MCASTID*2);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress OSM20, for now index is MCast Id
        (*this)[regionIndex].InitMCast();
    }
}

#endif // _INC_TSXC_S1MCASTREGION_H
