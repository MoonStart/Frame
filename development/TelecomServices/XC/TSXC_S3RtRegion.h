/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Three Route Region interface
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S3RTREGION_H
#define _INC_TSXC_S3RTREGION_H

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BaseRegion.h>
#include <set>

//-----------------------------------------------------------------------------
//--- This region is used to store stage three route configuration on SSM 
//    modules 
//
//--- Note:  This region is always created without any objects.
//---        The size of the objects are adjusted when SetMyCardType() method 
//           is invoked with appropriate card types.
//----------------------------------------------------------------------------

template <class T>  class TSXC_S3RtRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_S3RtRegion(const FC_BbKey theKey) : TSXC_BaseRegion<T>(theKey)
    {
    }

	// Destructor
    virtual ~TSXC_S3RtRegion()
    {
    }

//------------------------------------------------------------------------------
    void Connect(
                uint8             theSrcShelf,
                uint8             theSrcSlot,
                uint16            theSrcSts,
                uint16            theDstSts,          // range 0..383
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                CT_XC_CQMID*      theRespId = NULL,
                bool              theImmediateCommit = true);
                
    void Disconnect(
                uint8             theSrcShelf,
                uint8             theSrcSlot,
                uint16            theSrcSts,
                uint16            theDstSts,          // range 0..383            
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                CT_XC_CQMID*      theRespId = NULL,
                bool              theImmediateCommit = true);
    
//------------------------------------------------------------------------------
private:
    virtual void          PopulateSSM();
    virtual void          PopulateOSM40();
    virtual void          PopulateFGSM();
    virtual void          PopulateOSM20();
};

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::Connect(
                uint8             theSrcShelf,
                uint8             theSrcSlot,
                uint16            theSrcSts,
                uint16            theDstSts,          // range 0..383      
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                CT_XC_CQMID*      theRespId,
                bool              theImmediateCommit)
{
    uint16                aLastSts;
    bool                  aResult;
    set<uint16>::iterator aConnIdIter;
    uint16                aConnId;
    char                  ErrorMsg[80];

    aLastSts = theDstSts + this->ConnTypeToChans(theConnType);

    if ( aLastSts <= this->Size() )
    {
        // There are cases where connectionIds are not specified
        if ( (theConnIds.size() == 0) ||
             (theConnIds.size() == this->ConnTypeToChans(theConnType)) )
        {
            for(aResult = true, aConnIdIter = theConnIds.begin(); 
                (theDstSts < aLastSts) && (aResult == true); 
                theDstSts++, theSrcSts++)
            {
                // If connectionId is not specified, set it to 0
                aConnId = 0;
                if (aConnIdIter != theConnIds.end())
                {
                    aConnId = *aConnIdIter;
                    aConnIdIter++;
                }

                aResult = (*this)[theDstSts].AddSrc(theSrcSts, theSrcSlot, theSrcShelf, aConnId);
            }

            if (aResult == true)
            {       
                this->SetRespIdAndCommit(theRespId, theImmediateCommit);
            }
            else
            {
                // For failures, generate error message and let caller timeout
                FC_REPORT_ERROR(FC_RuntimeError, "TSXC_S3RtRegion::Connect() trouble adding a source");
            }
        }
        else
        {
            // For failures, generate error message and let caller timeout
            sprintf(ErrorMsg, "TSXC_S3RtRegion::Connect() theConnIds size (%d) != NumChans (%d)\n", 
                          theConnIds.size(), this->ConnTypeToChans(theConnType) );
            FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
        }
    }
    else
    {
        // For failures, generate error message and let caller timeout
        sprintf(ErrorMsg, "TSXC_S3RtRegion::Connect() theDstSts (%d) out of range\n", theDstSts);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }    
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::Disconnect(
                uint8             theSrcShelf,
                uint8             theSrcSlot,
                uint16            theSrcSts,
                uint16            theDstSts,          // range 0..383      
                CT_XC_ConnectType theConnType,
                set<uint16>&      theConnIds,
                CT_XC_CQMID*      theRespId,
                bool              theImmediateCommit)
{
    uint16                aLastSts;
    set<uint16>::iterator aConnIdIter;
    uint16                aConnId;
    char                  ErrorMsg[80];

    aLastSts = theDstSts + this->ConnTypeToChans(theConnType);

    if ( aLastSts <= this->Size() )
    {
        // There are cases where connectionIds are not specified
        if ( (theConnIds.size() == 0) ||
             (theConnIds.size() == this->ConnTypeToChans(theConnType)) )
        {
            for( aConnIdIter = theConnIds.begin();
                 theDstSts < aLastSts; 
                 theDstSts++, theSrcSts++ )
            {
                // If connectionId is not specified, set it to 0
                aConnId = 0;
                if (aConnIdIter != theConnIds.end())
                {
                    aConnId = *aConnIdIter;
                    aConnIdIter++;
                }

                (*this)[theDstSts].RmvSrc(theSrcSts, theSrcSlot, theSrcShelf, aConnId);
            }

            this->SetRespIdAndCommit(theRespId, theImmediateCommit);
        }
        else
        {
            // For failures, generate error message and let caller timeout
            sprintf(ErrorMsg, "TSXC_S3RtRegion::Disconnect() theConnIds size (%d) != NumChans (%d)\n", 
                              theConnIds.size(), this->ConnTypeToChans(theConnType) );
            FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
        }
    }
    else
    {
        // For failures, generate error message and let caller timeout
        sprintf(ErrorMsg, "TSXC_S3RtRegion::Connect() theDstSts (%d) out of range\n", theDstSts);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }    
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::PopulateSSM()
{
    this->Resize(XC_MAX_XC_SSM_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Egress SSM source info
        (*this)[regionIndex].InitSrc();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::PopulateOSM40()
{
    this->Resize(XC_MAX_SSM40_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Egress SSM source info
        (*this)[regionIndex].InitSrc();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::PopulateFGSM()
{
    this->Resize(XC_MAX_FGSM_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //source info
        (*this)[regionIndex].InitSrc();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_S3RtRegion<T>::PopulateOSM20()
{
    this->Resize(XC_MAX_OSM20_XC_IM_ALL);

    for (size_t regionIndex = 0; regionIndex < (int) this->Size(); regionIndex++)
    {
        //source info
        (*this)[regionIndex].InitSrc();
    }
}

#endif // _INC_TSXC_S3RTREGION_H
