// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_SOURCEACTIVESTATUSREGION_H
#define _INC_TSXC_SOURCEACTIVESTATUSREGION_H


#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_SourceActiveStatus.h>
#include <CommonTypes/CT_CardTypes.h>


//
// This class is responsible for abstracting 
// away Cross Connects region implementation from SP
//
template <class T>
class TSXC_SourceActiveStatusRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_SourceActiveStatusRegion(const FC_BbKey theKey,
                                size_t theInitialSize):
                                TEL_BbRegionBaseImp<T>(theKey, theInitialSize),
                                myCardType(CARD_TYPE_UNKNOWN)
    {
    }

	// Destructor.
    ~TSXC_SourceActiveStatusRegion()
    {
    }

	// Sets a source to the object at specified index.
    // This method is one based.
	void SetActiveSource(uint8 Port,
                         uint8 Channel,
                         uint8 ToActivePort,
                         uint8 ToActiveChannel);

    CT_CardType GetMyCardType() { return myCardType; }
    void SetMyCardType(CT_CardType theCardType) { myCardType = theCardType; }

    TSXC_SourceActiveStatusRegion& operator=(const TSXC_SourceActiveStatusRegion& theRegion);
    bool operator==(const TSXC_SourceActiveStatusRegion& theRegion) const;
    bool operator!=(const TSXC_SourceActiveStatusRegion& theRegion) const;


private:
    CT_CardType   myCardType;
   
};

// 
// Interface method for SP to XC's region to set a specific
// port and channel to an active port and active channel.
// SP's going to use the 1 based port naming to interface with
// XC.
//
template<class T> void TSXC_SourceActiveStatusRegion<T>::SetActiveSource(uint8 Port,
                                                  uint8 Channel,
                                                  uint8 ToActivePort,
                                                  uint8 ToActiveChannel)
{
    uint32 maxPort;
    uint8  maxChan;

    maxPort = 0;
    maxChan = 0;

    if (myCardType == CARD_TYPE_SMTMU)
    {
        maxPort = XC_MAX_SMTMU_PORT_INTF +
                  XC_MAX_SMTMU_DWDM_INTF +
                  XC_MAX_SMTMU_IM_LINE_INTF +
                  XC_MAX_SMTMU_IM_PORT_INTF;

        maxChan = XC_MAX_XC_SMTMU_DWDM;

        // To everyone else zeros mean invalid. Also make sure
        // the Port and channel do not exceed our alloted region.
        if((Port != 0) &&
           (Channel != 0) &&
           (Port <= maxPort) &&
           (Channel <= maxChan))
        {
           
           if ((ToActivePort != 0) &&
               (ToActiveChannel != 0))
           {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[SMTMUConfigMap[Port]+Channel-1].SetActiveFacility(ToActivePort);
                (*this)[SMTMUConfigMap[Port]+Channel-1].SetActiveFacilityEndpoint(ToActiveChannel);
           }
           else if ( (ToActivePort == 0) &&
                     (ToActiveChannel == 0) )
           {
               // Subtract one because we store it in memory zero based.
		       // For readability the stored values are 1 based.
               (*this)[SMTMUConfigMap[Port]+Channel-1].ResetActiveFacility();
               (*this)[SMTMUConfigMap[Port]+Channel-1].ResetActiveFacilityEndpoint();
           }
        }
    }
    else if (myCardType == CARD_TYPE_SPFAB)
    {
        maxPort = XC_MAX_SPFAB_LINE_INTF;

        maxChan = XC_MAX_XC_SPFAB_LINE;

        // To everyone else zeros mean invalid. Also make sure
        // the Port and channel do not exceed our alloted region.
        if((Port != 0) &&
           (Channel != 0) &&
           (Port <= maxPort) &&
           (Channel <= maxChan))
        {
            if ((ToActivePort != 0) &&
                (ToActiveChannel != 0))
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[SPFABConfigMap[Port]+Channel-1].SetActiveFacility(ToActivePort);
                (*this)[SPFABConfigMap[Port]+Channel-1].SetActiveFacilityEndpoint(ToActiveChannel);
            }
            else if ( (ToActivePort == 0) &&
                      (ToActiveChannel == 0) )
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[SPFABConfigMap[Port]+Channel-1].ResetActiveFacility();
                (*this)[SPFABConfigMap[Port]+Channel-1].ResetActiveFacilityEndpoint();
            }
        }
    }
	else if ( (myCardType == CARD_TYPE_SSMX) || (myCardType == CARD_TYPE_SSMD) )
    {
		maxPort = XC_MAX_SSM_PORT_INTF +
                  XC_MAX_SSM_DWDM_INTF +
                  XC_MAX_SSM_IM_LINE_INTF +
                  XC_MAX_SSM_IM_PORT_INTF +
                  XC_MAX_SSM_TTP_INTF;

        maxChan = XC_MAX_XC_SSM_DWDM;

        // To everyone else zeros mean invalid. Also make sure
        // the Port and channel do not exceed our alloted region.
        if((Port != 0) &&
           (Channel != 0) &&
           (Port <= maxPort) &&
           (Channel <= maxChan))
        {
            if ((ToActivePort != 0) &&
                (ToActiveChannel != 0))
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[SSMConfigMap[Port]+Channel-1].SetActiveFacility(ToActivePort);
                (*this)[SSMConfigMap[Port]+Channel-1].SetActiveFacilityEndpoint(ToActiveChannel);
            }
            else if ( (ToActivePort == 0) &&
                      (ToActiveChannel == 0) )
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[SSMConfigMap[Port]+Channel-1].ResetActiveFacility();
                (*this)[SSMConfigMap[Port]+Channel-1].ResetActiveFacilityEndpoint();
            }
        }
	}
    else if ((myCardType == CARD_TYPE_HDTG))
    {
        maxPort = XC_MAX_HDTG_PORT_INTF;

        maxChan = XC_MAX_XC_HDTG_ODU2_PORT;

        // To everyone else zeros mean invalid. Also make sure
        // the Port and channel do not exceed our alloted region.
        if((Port != 0) &&
           (Channel != 0) &&
           (Port <= maxPort) &&
           (Channel <= maxChan))
        {
            if ((ToActivePort != 0) &&
                (ToActiveChannel != 0))
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[HDTGConfigMap[Port]+Channel-1].SetActiveFacility(ToActivePort);
                (*this)[HDTGConfigMap[Port]+Channel-1].SetActiveFacilityEndpoint(ToActiveChannel);
            }
            else if ( (ToActivePort == 0) &&
                      (ToActiveChannel == 0) )
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[HDTGConfigMap[Port]+Channel-1].ResetActiveFacility();
                (*this)[HDTGConfigMap[Port]+Channel-1].ResetActiveFacilityEndpoint();
            }
        }
    }
    else if ((myCardType == CARD_TYPE_HDTG2))
    {
        maxPort = XC_MAX_HDTG2_PORT_INTF;

        maxChan = XC_MAX_XC_HDTG2_ODU2F_PORT;

        // To everyone else zeros mean invalid. Also make sure
        // the Port and channel do not exceed our alloted region.
        if((Port != 0) &&
           (Channel != 0) &&
           (Port <= maxPort) &&
           (Channel <= maxChan))
        {
            if ((ToActivePort != 0) &&
                (ToActiveChannel != 0))
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[HDTG2ConfigMap[Port]+Channel-1].SetActiveFacility(ToActivePort);
                (*this)[HDTG2ConfigMap[Port]+Channel-1].SetActiveFacilityEndpoint(ToActiveChannel);
            }
            else if ( (ToActivePort == 0) &&
                      (ToActiveChannel == 0) )
            {
                // Subtract one because we store it in memory zero based.
		        // For readability the stored values are 1 based.
                (*this)[HDTG2ConfigMap[Port]+Channel-1].ResetActiveFacility();
                (*this)[HDTG2ConfigMap[Port]+Channel-1].ResetActiveFacilityEndpoint();
            }
        }
    }
}

template<class T> 
TSXC_SourceActiveStatusRegion<T>& TSXC_SourceActiveStatusRegion<T>::operator=(const TSXC_SourceActiveStatusRegion& theRegion)
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
        (*this)[regionPos].SetActiveFacility(theRegion[regionPos].GetActiveFacility());
        (*this)[regionPos].SetActiveFacilityEndpoint(theRegion[regionPos].GetActiveFacilityEndpoint());
        (*this)[regionPos].SetSourceFacility(theRegion[regionPos].GetSourceFacility());
        (*this)[regionPos].SetSourceFacilityEndpoint(theRegion[regionPos].GetSourceFacilityEndpoint());
    }

    return *this;
}

template<class T> 
bool TSXC_SourceActiveStatusRegion<T>::operator==(const TSXC_SourceActiveStatusRegion& theRegion) const
{
    bool                      retVal;
    int                       regionPos;

    if ( (*this).Size() != theRegion.Size() )
    {
        FC_THROW_ERROR(FC_LogicError, "TSXC_ConfigRegion::operator=, this and theRegion differ in size");
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

template<class T> 
bool TSXC_SourceActiveStatusRegion<T>::operator!=(const TSXC_SourceActiveStatusRegion& theRegion) const
{
    return (!(*this == theRegion));
}

#endif // _INC_TSXC_SOURCEACTIVESTATUSREGION_H

