/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage One Route Region Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S1RTREGION_H
#define _INC_TSXC_S1RTREGION_H

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BaseRegion.h>

#include <T6100_ShelfIf.h>
#include <T6100_SlotIf.h>

#include <set>

//------------------------------------------------------------------------------
//--- This region is used to store stage one route configuration on SSM modules 
//
//--- Note:  This region is always created without any objects.
//---        The size of the objects are adjusted when SetMyCardType() method is 
//---        invoked with appropriate card types.
//------------------------------------------------------------------------------

template <class T>  class TSXC_S1RtRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_S1RtRegion(const FC_BbKey theKey) :
                    TSXC_BaseRegion<T>(theKey)
    {
    }

	// Destructor
    virtual ~TSXC_S1RtRegion()
    {
    }

//------------------------------------------------------------------------------
    void Connect(
                uint16            theSrcSts,          // range 0..383
                bool              IsMc,               // true = use multicast else use unicast.
                uint16            theMCastId,         // range 1..768 (Mesh) or 8192..16384 on HCSS
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                bool              theIsFlexible = false,
                uint8             theDstShelf = 0,
                uint8             theDstSlot  = 0,
                uint8             theDstSlice = 0,
                CT_XC_CQMID*      theRespId = NULL,
                bool              theImmediateCommit = true);
                
    void Disconnect(
                uint16            theSrcSts,          // range 0..383
                CT_XC_ConnectType theConnType,
                CT_XC_CQMID*      theRespId = NULL,
                bool              theImmediateCommit = true);

    void SetDstSlice(
                uint16            theSrcSts,          // range 0..383
                uint8             theDstSlice,
                CT_XC_CQMID*      theRespId = NULL,
                bool              theImmediateCommit = true);
    
//------------------------------------------------------------------------------
private:
    virtual void          PopulateSSM();
    virtual void          PopulateOSM40();
    virtual void          PopulateFGSM();
    virtual void          PopulateOSM20();
    virtual void          PopulateOSM();
    virtual void          PopulateOSM1S();
};

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::Connect(
                uint16            theSrcSts,
                bool              IsMc,
                uint16            theMCastId,
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                bool              theIsFlexible,
                uint8             theDstShelf,
                uint8             theDstSlot,
                uint8             theDstSlice,
                CT_XC_CQMID*      theRespId,
                bool              theImmediateCommit)
{
    uint16                            aLastSts;
    CT_XC_ConnectMapping              aConnMapping;
    set<uint16>::iterator             aConnIdIter;
    uint16                            aConnId;
    char                              ErrorMsg[80];
    CT_CardType                       aDstCardType = CARD_TYPE_UNKNOWN;

    aLastSts     = theSrcSts + this->ConnTypeToChans(theConnType);
    aConnMapping = theIsFlexible ? CT_XC_MAPPING_FLEXIBLE : CT_XC_MAPPING_FIXED;

    // For unicast connections, the destination's card type is needed
    if (IsMc == false)
    {
        T6100_ShelfIf*  aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theDstShelf);
        T6100_SlotIf*   aSlotPtr  = aShelfPtr->GetSlotPtr(theDstSlot);
        aDstCardType = aSlotPtr->GetProvCardType();
    }

    if ( aLastSts <= this->Size() )
    {
        // There are cases where connectionIds are not specified
        if ( (theConnIds.size() == 0) ||
             (theConnIds.size() == this->ConnTypeToChans(theConnType)) )
        {
            for(aConnIdIter = theConnIds.begin(); theSrcSts < aLastSts; theSrcSts++ )
            {
                // If connectionId is not specified, set it to 0
                aConnId = 0;
                if (aConnIdIter != theConnIds.end())
                {
                    aConnId = *aConnIdIter;
                    aConnIdIter++;
                }

                if (IsMc == true)
                {
                    (*this)[theSrcSts].SetMCastId(theMCastId, aConnMapping);
                    (*this)[theSrcSts].SetConnId(aConnId);
                    (*this)[theSrcSts].SetDstShelf(0);
                    (*this)[theSrcSts].SetDstSlot(0);
                    (*this)[theSrcSts].SetDstSlice(0);
                    (*this)[theSrcSts].SetDstCardType(CARD_TYPE_UNKNOWN);                 
                }
                else    // set it as unicast connection.
                {
                    (*this)[theSrcSts].InitDst();
                    (*this)[theSrcSts].SetConnId(aConnId);
                    (*this)[theSrcSts].SetDstShelf(theDstShelf);
                    (*this)[theSrcSts].SetDstSlot(theDstSlot);
                    (*this)[theSrcSts].SetDstSlice(theDstSlice);
                    (*this)[theSrcSts].SetDstCardType(aDstCardType);                 
                }
            }

            this->SetRespIdAndCommit(theRespId, theImmediateCommit);
        }
        else
        {
            // For failures, generate error message and let caller timeout
            sprintf(ErrorMsg, "TSXC_S1RtRegion::Connect() theConnIds size (%d) != NumChans (%d)\n", 
                      theConnIds.size(), this->ConnTypeToChans(theConnType) );
            FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
        }
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::Disconnect(
                uint16            theSrcSts,
                CT_XC_ConnectType theConnType,
                CT_XC_CQMID*      theRespId,
                bool              theImmediateCommit)
{

    uint16               aLastSts;

    aLastSts = theSrcSts + this->ConnTypeToChans(theConnType);

    if ( aLastSts <=  this->Size() )
    {
        for( ;theSrcSts < aLastSts; theSrcSts++)
        {
            (*this)[theSrcSts].InitDst();
        }

        this->SetRespIdAndCommit(theRespId, theImmediateCommit);
    }
    else
    {
        // For failures, generate error message and let caller timeout
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S1RtRegion::Disconnect() theSrcSts (%d) out of range\n", theSrcSts);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }        
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::SetDstSlice(
                uint16            theSrcSts,
                uint8             theDstSlice,
                CT_XC_CQMID*      theRespId,
                bool              theImmediateCommit)
{
    if ( theSrcSts <=  this->Size() )
    {
        (*this)[theSrcSts].SetDstSlice(theDstSlice);

        this->SetRespIdAndCommit(theRespId, theImmediateCommit);
    }
    else
    {
        // For failures, generate error message and let caller timeout
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S1RtRegion::SetDstSlice() theSrcSts (%d) out of range\n", theSrcSts);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }        
}
    
//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateSSM()
{
    this->Resize(XC_MAX_XC_SSM_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateOSM40()
{
    this->Resize(XC_MAX_SSM40_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateFGSM()
{
    this->Resize(XC_MAX_FGSM_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateOSM20()
{
    this->Resize(XC_MAX_OSM20_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateOSM()
{
    this->Resize(XC_MAX_OSM_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S1RtRegion<T>::PopulateOSM1S()
{
    this->Resize(XC_MAX_OSM1S_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //for now index is MCast Id
        (*this)[regionIndex].InitDst();
    }
}

#endif // _INC_TSXC_S1RTREGION_H
