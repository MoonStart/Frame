// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_MCAST_FILTER_REGION_H
#define _INC_TSXC_MCAST_FILTER_REGION_H

#include <XC/TSXC_MCastFilter.h>
#include <XC/TSXC_CrossConnect.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_CardTypes.h>

//
// This class is responsible for abstracting 
// away Cross Connects region implementation from SP
//
template <class T>
class TSXC_MCastFilterRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_MCastFilterRegion(const FC_BbKey theKey)
                    :TEL_BbRegionBaseImp<T>(theKey, 0)
                    ,myCardType(CARD_TYPE_UNKNOWN)
    {
    }

	// Destructor
    ~TSXC_MCastFilterRegion()
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
    
    TSXC_MCastFilterRegion& operator=(const TSXC_MCastFilterRegion& theRegion);
    bool operator==(const TSXC_MCastFilterRegion& theRegion) const;
    bool operator!=(const TSXC_MCastFilterRegion& theRegion) const;

private:
    void          PopulateUnknown();
    void          PopulateSSM();
    void          PopulateOSM40();
    void          PopulateOSM20();
    void          PopulateFGSM();
    void          PopulateOSM();
    void          PopulateOSM1S();

    CT_CardType   myCardType;
};

// -----------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::SetMyCardType(CT_CardType theCardType)
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
            case CARD_TYPE_SSM40:
            case CARD_TYPE_OSM40:
                PopulateOSM40();
                break;                            
            case CARD_TYPE_OSM20:
                PopulateOSM20();
                break;
            case CARD_TYPE_FGSM:
                PopulateFGSM();
                break;
            case CARD_TYPE_OSM2C:
            case CARD_TYPE_OSM2S:
                PopulateOSM();
                break;
            case CARD_TYPE_OSM1S:
                PopulateOSM1S();
                break;  
            default:
                PopulateUnknown();
                break;
        }
    }

    myCardType = theCardType;
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateSSM()
{
    this->Resize(XC_MAX_XC_SSM_IM_LINE + XC_MAX_XC_SSM_IM_PORT);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateOSM40()
{
    this->Resize(XC_MAX_SSM40_ODUXC_IMUX_INTF * XC_MAX_XC_SSM40_ODUXC_IMUX * 2);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress SSM, for now index is MCast Id
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateOSM20()
{
    this->Resize(XC_MAX_OSM20_ODUXC_IMUX_INTF * XC_MAX_XC_OSM20_ODUXC_IMUX * 2);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress OSM20, for now index is MCast Id
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateFGSM()
{
    this->Resize(XC_MAX_FGSM_ODUXC_IMUX_INTF * XC_MAX_XC_FGSM_ODUXC_IMUX * 2);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        // Ingress FGSM, for now index is MCast Id
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateOSM()
{
    this->Resize(XC_MAX_OSM_ODUXC_IMUX_INTF * XC_MAX_XC_OSM_ODUXC_IMUX);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_MCastFilterRegion<T>::PopulateOSM1S()
{
    this->Resize(XC_MAX_OSM1S_ODUXC_IMUX * XC_MAX_OSM1S_ODUXC_IMUX_INTF);

    for (int regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> 
TSXC_MCastFilterRegion<T>& TSXC_MCastFilterRegion<T>::operator=(const TSXC_MCastFilterRegion& theRegion)
{
    int regionPos, i;

    // If THIS region size is different than THE region size, 
    // resize THIS region to be the same size as THE region.
    if ( (*this).Size() != theRegion.Size() )
    {
        (*this).Resize(theRegion.Size());
    }

    for (regionPos = 0; regionPos < (*this).Size(); regionPos++)
    {
        (*this)[regionPos].SetMCastToUse(theRegion[regionPos].GetMCastToUse());
    }

    return *this;
}

//----------------------------------------------------------------------------------------------------------
template<class T> 
bool TSXC_MCastFilterRegion<T>::operator==(const TSXC_MCastFilterRegion& theRegion) const
{
    bool retVal;
    int  regionPos;

    if ( (*this).Size() != theRegion.Size() )
    {
        FC_THROW_ERROR(FC_LogicError, "TSXC_MCastFilterRegion::operator==, this and theRegion differ in size");
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
bool TSXC_MCastFilterRegion<T>::operator!=(const TSXC_MCastFilterRegion& theRegion) const
{
    return (!(*this == theRegion));
}

#endif // _INC_TSXC_MCAST_FILTER_REGION_H
