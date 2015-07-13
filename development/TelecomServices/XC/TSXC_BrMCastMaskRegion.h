// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_BRIDGE_ROLL_MASK_REGION_H
#define _INC_TSXC_BRIDGE_ROLL_MASK_REGION_H


#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BrMCastMask.h>
#include <CommonTypes/CT_CardTypes.h>

//
// This class is responsible for abstracting 
// multicast region implementation on SSM
//
template <class T>
class TSXC_BrMCastMaskRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_BrMCastMaskRegion(const FC_BbKey theKey)
                    :TEL_BbRegionBaseImp<T>(theKey, 0)
                    ,myCardType(CARD_TYPE_UNKNOWN)
    {
    }

	// Destructor
    ~TSXC_BrMCastMaskRegion()
    {
    }

    istream& ReadObject(istream& theStream)
    {
        FC_BbRegion::ReadObject(theStream);
        return theStream;
    }
 
    ostream& WriteObject(ostream& theStream)
    {
        FC_BbRegion::WriteObject(theStream);
        return theStream;
    }
    
    CT_CardType GetMyCardType() { return myCardType; }
    void SetMyCardType(CT_CardType theCardType);
                     
    TSXC_BrMCastMaskRegion& operator=(const TSXC_BrMCastMaskRegion& theRegion);
    bool operator==(const TSXC_BrMCastMaskRegion& theRegion) const;
    bool operator!=(const TSXC_BrMCastMaskRegion& theRegion) const;

private:
    void          PopulateUnknown();
    void          PopulateSSM();
    void          PopulateOSM40();
    void          PopulateOSM20();
    
    CT_CardType   myCardType;
};

// -----------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_BrMCastMaskRegion<T>::SetMyCardType(CT_CardType theCardType)
{
    // Do something only if CardType has changed
    if ( myCardType != theCardType )
    {
        // Populate the region based on the new card type
        switch(theCardType)
        {
            case CARD_TYPE_SSMX:
            case CARD_TYPE_SSMD:
                PopulateSSM();
                break;
            case CARD_TYPE_OSM40:
                PopulateOSM40();
                break;
            case CARD_TYPE_OSM20:
                PopulateOSM20();
                break;
            default:
                PopulateUnknown();
                break;
        }
    }

    myCardType = theCardType;
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_BrMCastMaskRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_BrMCastMaskRegion<T>::PopulateSSM()
{
    this->Resize(1);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].Reset();
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_BrMCastMaskRegion<T>::PopulateOSM40()
{
    this->Resize(1);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].Reset();
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_BrMCastMaskRegion<T>::PopulateOSM20()
{
    this->Resize(1);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress OSM20, for now index is MCast Id
        (*this)[regionIndex].Reset();
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> 
TSXC_BrMCastMaskRegion<T>& TSXC_BrMCastMaskRegion<T>::operator=(const
        TSXC_BrMCastMaskRegion& theRegion)
{
    int regionPos;

    // If THIS region size is different than THE region size, 
    // resize THIS region to be the same size as THE region.
    if ( (*this).Size() != theRegion.Size() )
    {
        (*this).Resize(theRegion.Size());
    }

    for (regionPos = 0; regionPos < (*this).Size(); regionPos++)
    {
        (*this)[regionPos].SetMCastId(theRegion[regionPos].GetMCastId());
        (*this)[regionPos].SetMCastAction(theRegion[regionPos].GetMaskAction());
        (*this)[regionPos].SetMCastImuxLMask(theRegion[regionPos].GetMCastImuxLMask());
        (*this)[regionPos].SetMCastImuxPMask(theRegion[regionPos].GetMCastImuxPMask());
    }

    return *this;
}

//----------------------------------------------------------------------------------------------------------
template<class T> 
bool TSXC_BrMCastMaskRegion<T>::operator==(const TSXC_BrMCastMaskRegion& theRegion) const
{
    bool retVal;
    int  regionPos;

    if ( (*this).Size() != theRegion.Size() )
    {
        FC_THROW_ERROR(FC_LogicError, "TSXC_BrMCastMaskRegion::operator==, this and theRegion differ in size");
    }

    for (regionPos = 0, retVal = true; 
         (regionPos < (*this).Size()) && (retVal == true); 
         regionPos++)
    {
        if ((*this)[regionPos] != theRegion[regionPos])
        {
            retVal = false;
        }
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------
template<class T> 
bool TSXC_BrMCastMaskRegion<T>::operator!=(const TSXC_BrMCastMaskRegion& theRegion) const
{
    return (!(*this == theRegion));
}

#endif // _INC_TSXC_BRIDGE_ROLL_MASK_REGION_H
