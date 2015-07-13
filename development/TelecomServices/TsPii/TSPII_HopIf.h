#ifndef _TSPII_HOPIF_H
#define _TSPII_HOPIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Base class for the hardware independent interface.
             Provides the interface for High Order Path SONET/SDH Hardware.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_SONET64ByteTrace.h"

class TSPII_HopIf : public TSPII_BaseIf
{
public:

    /* Constructor */                 TSPII_HopIf(bool theDefault = false);
    virtual                           ~TSPII_HopIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32                      GetAis();
    virtual uint32                      GetUneq();
    virtual uint32                      GetLop();
    virtual uint32                      GetRdi();
    virtual uint32                      GetPlm();
    virtual uint32                      GetBerSf();
    virtual uint32                      GetBerSd();
    virtual uint32                      GetSFHigh();
    virtual uint32                      GetSFLow();
    virtual uint32                      GetSD();

    virtual uint32                      GetReiCount();
    virtual uint32                      GetCvCount();
    virtual uint32                      GetPpjgCount(); // Positive pointer justification Generated
    virtual uint32                      GetNpjgCount(); // Negative pointer justification Generated
    virtual uint32                      GetPpjdCount(); // Positive pointer justification Detected
    virtual uint32                      GetNpjdCount(); // Positive pointer justification Detected
    virtual uint16                      GetRxPQM();
    virtual const CT_SONET64ByteTrace & GetRxTrace();
    virtual bool                        GetDefectsChanged();
    virtual bool                        GetTxHwPQWSquelch();
    virtual bool                        GetRxHwPQWSquelch();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetSpeMapping(CT_TEL_HopSpeMapping theMapping);
    virtual CT_TEL_HopSpeMapping      GetSpeMapping() const;

    virtual void                      SetTxTrace(const CT_SONET64ByteTrace & theTrace);
    virtual const CT_SONET64ByteTrace & GetTxTrace() const;

    virtual void                      SetForceUneqEnabled(bool theEnabled);
    virtual bool                      GetForceUneqEnabled() const;

    virtual void                      SetForceAisEnabled(bool theEnabled);
    virtual bool                      GetForceAisEnabled() const;

    virtual void                      SetForceInternalAisEnabled(bool theEnabled);
    virtual bool                      GetForceInternalAisEnabled() const;

    virtual void                      SetForceRdiEnabled(bool theEnabled);
    virtual bool                      GetForceRdiEnabled() const;

    virtual void                      SetBerSdThreshold(CT_TEL_BERLevels theThreshold);
    virtual CT_TEL_BERLevels          GetBerSdThreshold() const;

    virtual void                      SetBerSfThreshold(CT_TEL_BERLevels theThreshold);
    virtual CT_TEL_BERLevels          GetBerSfThreshold() const;

    virtual void                      SetExpectedC2(uint8 theC2);
    virtual uint8                     GetExpectedC2() const;

    virtual void                      SetPointerJustEnabled(bool theEnabled);
    virtual bool                      GetPointerJustEnabled() const;

    virtual void                      SetSrcTrafficEnabled(bool theEnable);
    virtual bool                      GetSrcTrafficEnabled() const;

    virtual void                      SetTxPQM(uint16 thePQM, uint16 theMask = 0xFFFF);
    virtual uint16                    GetTxPQM() const;

    virtual void                      SetFppEnabled(bool theEnabled);
    virtual bool                      GetFppEnabled() const;

    virtual void                      SetFppSquelchEnabled(bool theEnabled);
    virtual bool                      GetFppSquelchEnabled() const;


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
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();

    // Monitoring attributes
    uint32               itsAis;
    uint32               itsUneq;
    uint32               itsLop;
    uint32               itsRdi;
    uint32               itsPlm;
    uint32               itsBerSd;
    uint32               itsSFHigh;
    uint32               itsSFLow;
    uint32               itsSD;
    uint32               itsBerSf;
    uint32               itsReiCount;
    uint32               itsCvCount;
    uint32               itsPpjgCount;    // Positive pointer justification Generated
    uint32               itsNpjgCount;    // Negative pointer justification Generated
    uint32               itsPpjdCount;    // Positive pointer justification Detected
    uint32               itsNpjdCount;    // Positive pointer justification Detected
    uint16               itsRxPQM;
    CT_SONET64ByteTrace  itsRxTrace;
    bool                 itsDefectsChanged;
    bool                 itsRxHwPQWSquelch;
    bool                 itsTxHwPQWSquelch;

    // Configuration attributes
    CT_TEL_HopSpeMapping itsSpeMapping;
    CT_SONET64ByteTrace  itsTxTrace;
    bool                 itsForceUneqEnabled;
    bool                 itsForceAisEnabled;
    bool                 itsForceIntAisEnabled;
    bool                 itsForceRdiEnabled;
    CT_TEL_BERLevels     itsBerSdThreshold;
    CT_TEL_BERLevels     itsBerSfThreshold;
    uint8                itsExpectedC2;
    bool                 itsPointerJustEnabled;
    bool                 itsSrcTrafficEnabled;
    uint16               itsTxPQM;
    bool                 itsFppEnabled;
    bool                 itsFppSquelchEnabled;
};

#endif // _TSPII_HOPIF_H
