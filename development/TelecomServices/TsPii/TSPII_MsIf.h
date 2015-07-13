#ifndef _TSPII_MSIF_H
#define _TSPII_MSIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for SONET/SDH Line termination hardware
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_Telecom.h" 
#include "TsPii/TSPII_BaseIf.h"

class TSPII_MsIf : public TSPII_BaseIf
{
    friend class SP_FsmTestParser;

public:
    /* Constructor */                 TSPII_MsIf(bool theDefault = false);
    virtual                           ~TSPII_MsIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32                    GetAis();
    virtual uint32                    GetInternalAis();
    virtual uint32                    GetProprietaryInternalAis();
    virtual uint32                    GetRdi();
    virtual uint32                    GetBerSf();
    virtual uint32                    GetBerSd();
    virtual uint32                    GetCvCount();
    virtual uint32                    GetReiCount();
    virtual uint8                     GetK1RxByte();
    virtual uint8                     GetK2RxByte();
    virtual CT_FAC_RxSsm              GetRxSsm();
    virtual uint8                     GetRxCsi();
    virtual bool                      GetIsTimingRefValid();

    virtual void                      registerEventHandlers(){};
    
    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetBerSdThreshold(CT_TEL_BERLevels theThreshold);
    virtual CT_TEL_BERLevels          GetBerSdThreshold() const;

    virtual void                      SetBerSfThreshold(CT_TEL_BERLevels theThreshold);
    virtual CT_TEL_BERLevels          GetBerSfThreshold() const;

    virtual void                      SetK1TxByte(uint8 theValue);
    virtual uint8                     GetK1TxByte() const;

    virtual void                      SetK2TxByte(uint8 theValue);
    virtual uint8                     GetK2TxByte() const;

    virtual void                      SetTxSsm(CT_FAC_RxSsm theSsm);
    virtual CT_FAC_RxSsm              GetTxSsm() const;

    virtual void                      SetAsTimingRef(CT_TEL_MsTref theRef);
    virtual CT_TEL_MsTref             GetAsTimingRef() const;

    virtual void                      SetFirstTimeslot(uint16 theTslot);
    virtual uint16                    GetFirstTimeslot() const;

    virtual void                      SetTxCsi(uint8 theValue);
    virtual uint8                     GetTxCsi() const;

    virtual void                      SetDerivedTimingSourceMode(CT_TEL_DT_Source_Mode theDTSourceMode);
    virtual CT_TEL_DT_Source_Mode     GetDerivedTimingSourceMode() const;

	virtual void                      SetInputReferenceMapping(uint16 theInputRef);
	virtual uint16                    GetInputReferenceMapping() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void      Display(FC_Stream & theStream);
    virtual void      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool      Set(int argc, char ** argv);
    virtual bool      Simul(int argc, char ** argv);

protected:

    void              RefreshGet();
    void              RefreshSet();

    // Monitoring attributes
    uint32            itsAis;                  // Defect count
    uint32            itsInternalAis;          // Defect count
    uint32            itsProprietaryInternalAis;  // Defect count
    uint32            itsRdi;                  // Defect count
    uint32            itsBerSf;                // Defect count
    uint32            itsBerSd;                // Defect count
    uint32            itsCvCount;
    uint32            itsReiCount;
    uint8             itsK1RxByte;
    uint8             itsK2RxByte;
    uint8             itsRxCsi;
    CT_FAC_RxSsm      itsRxSsm;
    bool              itsIsTimingRefValid;
    
    // Configuration attributes
    CT_TEL_BERLevels      itsBerSdThreshold;
    CT_TEL_BERLevels      itsBerSfThreshold;
    uint8                 itsK1TxByte;
    uint8                 itsK2TxByte;
    CT_FAC_RxSsm          itsTxSsm;
    uint8                 itsTxCsi;
    CT_TEL_MsTref         itsTimingRef;
    uint16                itsFirstTimeslot;
    CT_TEL_DT_Source_Mode itsDerivedSourceMode;
	uint16                itsMappedInputReference;
};

#endif // _TSPII_MSIF_H
