#ifndef _TSPII_FECIF_H
#define _TSPII_FECIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Martin Piotte, 2002/12/17
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_Float32.h"
#include "CommonTypes/CT_G709Trace.h"
#include "TsPii/TSPII_BaseIf.h"

class TSPII_FecIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */            TSPII_FecIf(bool theDefault = false);
    virtual                      ~TSPII_FecIf();
    virtual void                 Reset();

    // -----------------------------------------------------------------------------------
    // FEC Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32               GetFECCorrectedBytesCount();
    virtual uint32               GetHighFECCorrectedBytesCount();
    virtual uint32               GetBitErrorCountOnOnes();
    virtual uint32               GetHighBitErrorCountOnOnes();
    virtual uint32               GetBitErrorCountOnZeros();
    virtual uint32               GetHighBitErrorCountOnZeros();
    virtual uint32               GetNonCorrectableRSFrameCount();
    virtual uint32               GetHighNonCorrectableRSFrameCount();
    virtual uint32               GetBip8Count();
    virtual uint32               GetHighBip8Count();
    virtual uint32               GetBeiCount();
    virtual uint32               GetHighBeiCount();
    virtual uint32               GetLOF();
    virtual uint32               GetLOMF();
    virtual uint32               GetFECM();
    virtual uint32               GetAIS();
    virtual uint32               GetBDI();
    virtual uint32               GetBerSf();
    virtual uint32               GetBerSd();
    virtual uint32               GetMateDefect();
    virtual const CT_G709Trace & GetRxTrace();
    virtual const CT_Float32 &   GetBER();
    virtual uint32               GetIAE();
    virtual CT_TEL_DispCompState GetDispCompState();
    virtual uint32               GetTIM();

    // -----------------------------------------------------------------------------------
    // FEC Event/Counter Monitoring Interface
    // -----------------------------------------------------------------------------------
    virtual void                 registerEventHandlers(){};

    // -----------------------------------------------------------------------------------
    // FEC Config Interfaces
    // -----------------------------------------------------------------------------------
     
    //SHOULD BE DEPRECATED - CAN USE SetFECType IN IN FUTURE CARDS
    virtual void                 SetCorrectionEnable(bool theEnable);
    virtual void                 SetTxTrace(const CT_G709Trace & theTrace);
    virtual void                 SetExpectedTrace(const CT_G709Trace & theTrace);
    virtual void                 SetTIMMonitoringEnable(bool theTIMMonitoringState);
    virtual void                 SetLayerFailOnTIM(bool theLayerFailOnTIM);
    virtual void                 ForceAIS(bool theEnable);
    virtual void                 ForceBDI(bool theEnable);
    virtual void                 SetErrorGeneration(bool theEnable);
    //SHOULD BE DEPRECATED - CAN USE SetFECType IN IN FUTURE CARDS
    virtual void                 SetSuperFecEnable(bool theEnable);
    virtual void                 SetBerSfThreshold(CT_TEL_BERLevels theThreshold);
    virtual void                 SetBerSdThreshold(CT_TEL_BERLevels theThreshold);
    virtual void                 SetBurstyBerSdThreshold(uint intervals, uint32 threshold);
    virtual void                 SetBDIAndBEIAllowed(bool allowed);
    // In 7.1, changed the name of SetFECTypemethod from SetSuperFecType so that it 
    // would be more generic.  OSM40 still expects only Super of SuperI7.
    // Other cards can now use SetFecType for all enums and eliminate the
    // need to use SetCorrectionEnable and SetSuperFecEnable.    
    virtual void                 SetFECType(CT_TEL_FecType theFECType);
    virtual void                 SetSendDefectToMate(bool theEnable);
    virtual void                 SetTimCriteria(CT_TEL_TimCriteriaMode theTimCriteria);

    virtual bool                 GetCorrectionEnable() const;
    virtual const CT_G709Trace & GetTxTrace() const;
    virtual const CT_G709Trace & GetExpectedTrace() const;
    virtual bool                 GetTIMMonitoringEnable() const;
    virtual bool                 GetLayerFailOnTIM() const;    
    virtual bool                 GetForcedAIS() const;
    virtual bool                 GetForcedBDI() const;
    virtual bool                 GetErrorGeneration() const;
    virtual bool                 GetSuperFecEnable() const;
    virtual CT_TEL_BERLevels     GetBerSfThreshold() const;
    virtual CT_TEL_BERLevels     GetBerSdThreshold() const;
    virtual uint                 GetBurstyBerSdIntervals() const;
    virtual uint32               GetBurstyBerSdThreshold() const;
    virtual bool                 GetBDIAndBEIAllowed() const;
    virtual CT_TEL_FecType       GetFECType() const;
    virtual bool                 GetSendDefectToMate() const;
    virtual CT_TEL_TimCriteriaMode GetTimCriteria() const;
    

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &          WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &          ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &          WriteObject(ostream & theStream);
    virtual istream   &          ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void         RefreshGet();
    void         RefreshSet();

    // Monitoring attributes
    uint32       itsErrorCountOnZeros;
    uint32       itsHighErrorCountOnZeros;
    uint32       itsErrorCountOnOnes;
    uint32       itsHighErrorCountOnOnes;
    uint32       itsCorrectedBytesCount;
    uint32       itsHighCorrectedBytesCount;
    uint32       itsNonCorrectableRSFrameCount;
    uint32       itsHighNonCorrectableRSFrameCount;
    uint32       itsBip8Count;
    uint32       itsHighBip8Count;
    uint32       itsBeiCount;
    uint32       itsHighBeiCount;
    uint32       itsLOF;
    uint32       itsLOMF;
    uint32       itsAIS;
    uint32       itsBDI;
    uint32       itsFECM;
    uint32       itsBerSf;
    uint32       itsBerSd;
    uint32       itsMateDefect;
    CT_G709Trace itsRxTrace;
    CT_Float32   itsBER;
    uint32       itsIAE;
    uint32       itsTIM;

    // Configuration attributes
    bool             itsFECEnabled;
    bool             itsForcedAIS;
    bool             itsForcedBDI;
    bool             itsErrorGeneration;
    bool             itsSuperFecEnabled;
    CT_TEL_BERLevels itsBerSfThreshold;
    CT_TEL_BERLevels itsBerSdThreshold;
    CT_G709Trace     itsTxTrace;
    CT_G709Trace     itsExpectedTrace;
    bool             itsAllowBDIBEI;
    uint             itsBurstySdBerIntervals;
    uint32           itsBurstySdBerThreshold;
    CT_TEL_FecType   itsFECType;
    CT_TEL_DispCompState  itsDispCompState;
    bool             itsSendDefectToMate;
    CT_TEL_TimCriteriaMode itsTIMCriteraMode;
    bool             itsTIMMonitoringEnable;
    bool             itsLayerFailOnTIM;
};

#endif // _TSPII_FECIF_H
