/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2009        Jai Harpalani
    DESCRIPTION:   TSXC Base Region Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_BASEREGION_INCLUDED
#define _INC_TSXC_BASEREGION_INCLUDED

#include <Blackboard/FC_BbRegion.h>
#include <Blackboard/FC_BbTxAction.h>
#include <Blackboard/FC_BbReason.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_QrsService.h>
#include <CommonTypes/CT_QrsTypes.h>

#ifdef __TARGET__
extern "C" void DelayNmsec(ULONG msec);
#endif

//-----------------------------------------------------------------------------
// This is a base class obstracting common fuctionality 
// for TSXC configuration regions
//-----------------------------------------------------------------------------
template <class T> class TSXC_BaseRegion : public TEL_BbRegionBaseImp<T>
{
public:

    // Constructor 
    TSXC_BaseRegion(const FC_BbKey theKey) :
                    TEL_BbRegionBaseImp<T>(theKey, 0),
                    myCardType(CARD_TYPE_UNKNOWN)
    {
        myCQMRequest.type = 0;
        myCQMRequest.reqid   = 0;
        myCQMRequest.step = 0;
        myCQMRequest.shelf = 0;
        myCQMRequest.slot = 0;
        myCQMRequest.port = 0;
        myCQMRequest.qmgrIdx = 0;
    }

    // Destructor
    virtual ~TSXC_BaseRegion()
    {
    }

    // Internal interfaces
    CT_CardType         GetMyCardType()   { return myCardType; }
    CT_XC_CQMID         GetCQMRequest()   { return myCQMRequest; }

    void SetMyCardType(CT_CardType theCardType);
    void SetCQMResponse(CT_XC_CQMID* theRespId);
    void ResetCQMResponse();
    void SetRespIdAndCommit(CT_XC_CQMID* theRespId, bool theImmediateCommit, 
                          uint8 theNumResponses = 1);
    uint16 ConnTypeToChans(CT_XC_ConnectType theConnType);

    // Serialization methods
    FC_Stream& ReadObjectBinary(FC_Stream& theStream);
    FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    istream& ReadObject(istream& theStream);
    ostream& WriteObject(ostream& theStream);

    // Operators
    TSXC_BaseRegion& operator=(const TSXC_BaseRegion& theRegion);
    bool operator==(const TSXC_BaseRegion& theRegion) const;
    bool operator!=(const TSXC_BaseRegion& theRegion) const;

    // Region Transfer methods
    void ImmediateXfer();

protected:
    void              PopulateUnknown();
    virtual void      PopulateSSM()        { }
    virtual void      PopulateSPFAB()      { }
    virtual void      PopulateFGTMM()      { }
    virtual void      PopulateSMTMU()      { }
    virtual void      PopulateSMTMUDSD()   { }
    virtual void      PopulateOTNM()       { }
    virtual void      PopulateRCMM()       { }
    virtual void      PopulateDCMM()       { }
    virtual void      PopulateNANOCCM()    { }
    virtual void      PopulateCADM()       { }
    virtual void      PopulateUFAB()       { }
    virtual void      PopulateMFAB()       { }
    virtual void      PopulateSSM40()      { }
    virtual void      PopulateOSM40()      { }
    virtual void      PopulateHDTG()       { }
    virtual void      PopulateHDTG2()      { }
    virtual void      PopulateFGSM()       { }
    virtual void      PopulateOSM20()      { }
    virtual void      PopulateOMMX()       { }
    virtual void      PopulateHGTMM()      { }
    virtual void      PopulateOSM()        { }
    virtual void      PopulateOSM1S()      { }

    CT_CardType       myCardType;
    CT_XC_CQMID       myCQMRequest;
};

//----------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::SetMyCardType(CT_CardType theCardType)
{
    //--- Do something only if CardType has changed
    if ( myCardType != theCardType )
    {
        //--- Populate the region based on the new card type
        switch(theCardType)
        {
            case CARD_TYPE_SPFAB:
                PopulateSPFAB();
                break;
            case CARD_TYPE_FGTMM:
                PopulateFGTMM();
                break;
            case CARD_TYPE_SSMX:
            case CARD_TYPE_SSMD:
                PopulateSSM();
                break;
            case CARD_TYPE_SSM40:
                PopulateSSM40();
                break;
            case CARD_TYPE_OSM40:
                PopulateOSM40();
                break;
            case CARD_TYPE_FGSM:
                PopulateFGSM();
                break;
            case CARD_TYPE_OSM20:
                PopulateOSM20();
                break;
            case CARD_TYPE_SMTMU:
                PopulateSMTMU();
                break;
            case CARD_TYPE_SMTMUD:
            case CARD_TYPE_SMTMSD:
                PopulateSMTMUDSD();
                break;
            case CARD_TYPE_OTNMX:
            case CARD_TYPE_OTNMD:
                PopulateOTNM();
                break;
            case CARD_TYPE_HDTG:
                PopulateHDTG();
                break;
            case CARD_TYPE_HDTG2:
                PopulateHDTG2();
                break;
            case CARD_TYPE_RCMM:
                PopulateRCMM();
                break;
            case CARD_TYPE_DCMM:
                PopulateDCMM();
                break;
            case CARD_TYPE_CCMIR:
            case CARD_TYPE_CCMLR:
            case CARD_TYPE_CCMER:
                PopulateNANOCCM();
                break;
            case CARD_TYPE_CCM88IR:
            case CARD_TYPE_CCM88LR:
            case CARD_TYPE_CCM88ER:
            case CARD_TYPE_OADM88IR:
            case CARD_TYPE_OADM88LR:
            case CARD_TYPE_OADM88ER:
            case CARD_TYPE_OTSM:
            case CARD_TYPE_ELRAME:
            case CARD_TYPE_LIAME:
            case CARD_TYPE_LRAME:
            case CARD_TYPE_OADM88IR8D:
            case CARD_TYPE_OADM88LR8D:
            case CARD_TYPE_OADM88ER8D:
            case CARD_TYPE_OADM8DSIR:
            case CARD_TYPE_OADM8DSLR:
            case CARD_TYPE_OADM8DSER:
            case CARD_TYPE_OADMF8IR:
            case CARD_TYPE_OADMF8LR:
            case CARD_TYPE_DXOADM:
                PopulateCADM();
                break;
            case CARD_TYPE_UFAB:
                PopulateUFAB();
                break;
            case CARD_TYPE_MFAB:
                PopulateMFAB();
                break;
            case CARD_TYPE_OMMX:
                PopulateOMMX();
                break;
			case CARD_TYPE_HGTMM:
            case CARD_TYPE_HGTMMS: // Coriant HGTMMS
				PopulateHGTMM();
				break;
            case CARD_TYPE_OSM2S:
            case CARD_TYPE_OSM2C:
                PopulateOSM();
                break;
            case CARD_TYPE_OSM1S:
                PopulateOSM1S();
                break;
            default:
            case CARD_TYPE_UNKNOWN:
                PopulateUnknown();
                break;
        }
    }

    myCardType = theCardType;
}

//----------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::SetCQMResponse(CT_XC_CQMID* theRespId)
{
    if (theRespId != NULL)
    {
        myCQMRequest = *theRespId;
    }
    else
    {
        ResetCQMResponse();
    }
}

//----------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::ResetCQMResponse()
{
    myCQMRequest.type = 0;
    myCQMRequest.reqid   = 0;
    myCQMRequest.step = 0;
    myCQMRequest.shelf = 0;
    myCQMRequest.slot = 0;
    myCQMRequest.port = 0;
}

//----------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::SetRespIdAndCommit(CT_XC_CQMID* theRespId, 
                                                           bool theImmediateCommit,
                                                           uint8 theNumResponses)
{
    //
    // If intialization is in progress, and QRS XC request is expecting
    // a response, generate it immediately to speed up initialization.
    // Also, do NOT commit this region since it may not yet be fully
    // populated.  The QRSXc_UpdateBackendRegions request will commit
    // all regions after all BE XC regions are populated.
    //
    if ((TSXC_QrsService::GetInstance()->GetXcInitComplete() == false) ||
        (TSXC_QrsService::GetInstance()->GetXcByPassFlag()   == true)   )
    {
        if ( (theRespId != NULL) && (theImmediateCommit == true) )
        {
            while (theNumResponses-- > 0)
            {
                TSXC_QrsService::GetInstance()->RequestResponse(theRespId);
            }
        }
    }
    // Else let normal response from smartCard trigger request
    else
    {
        // Set responseId
        SetCQMResponse(theRespId);

        // Always Inc Mod Counter so FlushRegions will transfer region.
        this->IncModificationCounter();

        // If immediate commit was requested, update and transfer region.
        if (theImmediateCommit == true)
        {
            // Transfer region quickly (to speed up QRS requests)
            this->ImmediateXfer();
        }
    }
}

//----------------------------------------------------------------------------------
template<class T>uint16 TSXC_BaseRegion<T>::ConnTypeToChans(CT_XC_ConnectType theConnType)
{
    uint16  numChans;
    char    errMsg[80];

    switch(theConnType)
    {
        case CT_XC_TYPE_STS1:
        case CT_XC_TYPE_STS1D:
            numChans = 1;
            break;
        case CT_XC_TYPE_STS3C:
        case CT_XC_TYPE_STS3CD:
        case CT_XC_TYPE_STS3T:
            numChans = 3;
            break;
        case CT_XC_TYPE_STS12C:
        case CT_XC_TYPE_STS12T:
            numChans = 12;
            break;
        case CT_XC_TYPE_STS48C:
        case CT_XC_TYPE_STS48T:
            numChans = 48;
            break;
        case CT_XC_TYPE_STS192C:
            numChans = 192;
            break;
        case CT_XC_TYPE_ODU0:
        case CT_XC_TYPE_ODU1:
        case CT_XC_TYPE_ODU2:
        case CT_XC_TYPE_ODU2E:
        case CT_XC_TYPE_ODU3:
        case CT_XC_TYPE_ODU4:
        case CT_XC_TYPE_ODUF:
            numChans = 1;
            break;
        default:
            numChans = 0;
            sprintf(errMsg, "TSXC_BaseRegion::ConnTypeToChans(): Invalid ConnType of %d", theConnType);
            FC_REPORT_ERROR(FC_RuntimeError, errMsg);
            break;
    }

    return numChans;
}

//----------------------------------------------------------------------------------
template<class T>FC_Stream& TSXC_BaseRegion<T>::ReadObjectBinary(FC_Stream& theStream)
{
    FC_BbRegion::ReadObjectBinary(theStream);
    theStream >> myCQMRequest.type;
    theStream >> myCQMRequest.reqid;
    theStream >> myCQMRequest.step;
    theStream >> myCQMRequest.shelf;
    theStream >> myCQMRequest.slot;
    theStream >> myCQMRequest.port;
    theStream >> myCQMRequest.qmgrIdx;
    return theStream;
}

//----------------------------------------------------------------------------------
template<class T>FC_Stream& TSXC_BaseRegion<T>::WriteObjectBinary(FC_Stream& theStream)
{
    FC_BbRegion::WriteObjectBinary(theStream);
    theStream << myCQMRequest.type;
    theStream << myCQMRequest.reqid;
    theStream << myCQMRequest.step;
    theStream << myCQMRequest.shelf;
    theStream << myCQMRequest.slot;
    theStream << myCQMRequest.port;
    theStream << myCQMRequest.qmgrIdx;

    return theStream;
}

//----------------------------------------------------------------------------------
template<class T>istream& TSXC_BaseRegion<T>::ReadObject(istream& theStream)
{
    FC_BbRegion::ReadObject(theStream);
    theStream >> FC_ExtractVar(myCQMRequest.type);
    theStream >> FC_ExtractVar(myCQMRequest.reqid);
    theStream >> FC_ExtractVar(myCQMRequest.step);
    theStream >> FC_ExtractVar(myCQMRequest.shelf);
    theStream >> FC_ExtractVar(myCQMRequest.slot);
    theStream >> FC_ExtractVar(myCQMRequest.port);
    theStream >> FC_ExtractVar(myCQMRequest.qmgrIdx);

    return theStream;
}

//----------------------------------------------------------------------------------
template<class T>ostream& TSXC_BaseRegion<T>::WriteObject(ostream& theStream)
{
    FC_BbRegion::WriteObject(theStream);
    theStream << FC_InsertVar(myCQMRequest.type);
    theStream << FC_InsertVar(myCQMRequest.reqid);
    theStream << FC_InsertVar(myCQMRequest.step);
    theStream << FC_InsertVar(myCQMRequest.shelf);
    theStream << FC_InsertVar(myCQMRequest.slot);
    theStream << FC_InsertVar(myCQMRequest.port);
    theStream << FC_InsertVar(myCQMRequest.qmgrIdx);

    return theStream;
}

//-----------------------------------------------------------------------------------------------
template<class T>TSXC_BaseRegion<T>& TSXC_BaseRegion<T>::operator=(const TSXC_BaseRegion& theRegion)
{
    int regionPos;

    // If this region is different then make them same as Source
    if ( (*this).Size() != theRegion.Size() )
    {
        (*this).Resize(theRegion.Size());
    }

    for (regionPos = 0; regionPos < (int) (*this).Size(); regionPos++)
    {
        (*this)[regionPos] = theRegion[regionPos];
    }

    return *this;
}

//-----------------------------------------------------------------------------------------------
template<class T>bool TSXC_BaseRegion<T>::operator==(const TSXC_BaseRegion& theRegion) const
{
    bool retVal = false;
    int  regionPos;
    if ( (*this).Size() == theRegion.Size() )
    {
       for (regionPos = 0, retVal = true;
            (regionPos < (*this).Size()) && (retVal == true);
            regionPos++)
       {
           if ((*this)[regionPos] != theRegion[regionPos])
           {
               retVal = false;
           }
       }
    }
    return retVal;
}

//-----------------------------------------------------------------------------------------------
template<class T>bool TSXC_BaseRegion<T>::operator!=(const TSXC_BaseRegion& theRegion) const
{
    return (!(*this == theRegion));
}

//-----------------------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//-----------------------------------------------------------------------------------------------
template<class T>void TSXC_BaseRegion<T>::ImmediateXfer()
{
    // Invoke base-class immediate transfer
    FC_BbRegion::ImmediateXfer();

    /* Temporarily disabled true immediate xfer so no reason for delay
    // Delay for 10 milliseconds to avoid flooding network
    // with too many regions quickly, as this could result in
    // packet loss on receiving cards.
    //
#ifdef __TARGET__
    DelayNmsec(10);
#endif
    */
}

#endif /* _INC_TSXC_BASEREGION_INCLUDED */
