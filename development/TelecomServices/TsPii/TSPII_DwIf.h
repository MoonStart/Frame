#ifndef _TSPII_DWIF_H
#define _TSPII_DWIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Martin Piotte, 2002/12/17
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_G709Trace.h"
#include "CommonTypes/CT_OduDefinitions.h"
#include "CoreTypes/CT_SignalProtection.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_SncIf.h"

class TSPII_DwIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */               TSPII_DwIf(bool theDefault = false);
    virtual                         ~TSPII_DwIf();
    virtual void                    Reset();

    // -----------------------------------------------------------------------------------
    // Digital Wrapper Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual const CT_G709Trace &    GetRxTrace();
    virtual uint32                  GetAIS();
    virtual uint32                  GetLCK();
    virtual uint32                  GetOCI();
    virtual uint32                  GetBDI();
    virtual uint32                  GetBerSf();
    virtual uint32                  GetBerSd();
    virtual uint32                  GetPLM();
    virtual uint32                  GetMSIM();
    virtual uint32                  GetGenAIS();
    virtual uint32                  GetLOFLOM();
    virtual uint32                  GetLOOMFI();
    virtual uint32                  GetBip8Count();
    virtual uint32                  GetHighBip8Count();
    virtual uint8                   GetRxPayloadType();
    virtual uint32                  GetInternalAIS();
    virtual int32                   GetPathDelay();
    virtual uint32                  GetPrbsRxLosync() ; 
    virtual bool                    GetPrbsRxErrors(uint32 & theCountHigh, uint32 & theCountLow, uint32 & theTime) ;  
    virtual uint32                  GetInternalLCK() ;
    virtual uint32                  GetInternalOCI() ;
    virtual uint32                  GetTIM();

    virtual uint32                  GetRxAps(uint8 apsChannel);

    //For OSM20, SSF will be used for protection, but it won't lead to SGEO, GetSSF() is used.
    virtual uint32                  GetSSF() ;

    //For some boards like HGTMM, SSF will lead to SGEO, in this case GetSSFforSGEO() needs to be implemented.
    virtual uint32                  GetSSFforSGEO() ;

    // -----------------------------------------------------------------------------------
    // Digital Wrapper Event/Counter Monitoring Interface
    // -----------------------------------------------------------------------------------
    virtual void                    registerEventHandlers(){};

    // -----------------------------------------------------------------------------------
    // Digital Wrapper Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                    SetTxTrace(const CT_G709Trace & theTraceToTransmit);
    virtual void                    SetExpectedTrace(const CT_G709Trace & theTrace);
    virtual void                    SetTIMMonitoringEnable(bool theTIMMonitoringState);
    virtual void                    SetLayerFailOnTIM(bool theLayerFailOnTIM);
    virtual void                    ForceODUIndication(CT_ODU_IndicationType theIndication);
    virtual void                    ForceInternalODUIndication(CT_ODU_IndicationType theInternalIndication);
    virtual void                    ForceInternalAIS(bool theEnable);
    virtual void                    ForceBDI(bool theEnable);
    virtual void                    SetBerSfThreshold(CT_TEL_BERLevels theThreshold);
    virtual void                    SetBerSdThreshold(CT_TEL_BERLevels theThreshold);
    virtual void                    SetTxPayloadType(uint8 pt);
    virtual void                    SetExpectedPayloadType(uint8 pt);
    virtual void                    SetIsOduTerm(bool theIsOduTerm);
    virtual void                    SetSrcTrafficEnabled(bool theEnable);
    virtual void                    SetBurstyBerSdThreshold(uint intervals, uint32 threshold);
    virtual void                    SetODUTsSize(CT_TEL_TS_SIZE theODUTsSize,  bool theIsAutoFallback = false);
    virtual void                    SetClockType(CT_TEL_ClkType theClockType);
    virtual void                    SetTribPort(uint16 theTribPort);
    virtual void                    SetPathDelayEnabled(bool theEnable);
    virtual void                    SetExpRate(uint32 theRate); 
    virtual void                    SetNULLSignalEnable(bool theEnable);
    virtual void                    SetPRBSTXEnable(bool theEnable);
    virtual void                    SetPRBSRXEnable(bool theEnable);
    virtual void                    SetPRBSRXSessionCounter(uint32 thePRBSRXSessionCounter);
    virtual void                    SetDiagSigTxEnable(CT_TEL_DiagSignal theSig, bool theEnable);
    virtual void                    SetGfpTsNum(uint8 theTsNum);
    virtual void                    SetServer(CT_ODU_ServerID theServer);
    // This method sets cross connected ODU's index in the same board.
    virtual void                    SetXcOtherSideIndex(uint8 theOduIndex);
    virtual void                    SetTimCriteria(CT_TEL_TimCriteriaMode theTimCriteria);
    virtual void                    SetIsProvisioned(bool theEnable);
    /**
     * @brief Method to configure the APS bytes to be transmitted on ODU OH
     * @param theApsChannel APS channel where the APS bytes will be inserted
     * @param theApsBytes APS bytes value to be inserted
     */
    virtual void                    SetTxApsBytes(CT_SP_APS_Channel theApsChannel, uint32 theApsBytes ,bool theApsInsert);
    virtual const CT_G709Trace &    GetTxTrace() const;
    virtual const CT_G709Trace &    GetExpectedTrace() const;
    virtual bool                    GetTIMMonitoringEnable() const;
    virtual bool                    GetLayerFailOnTIM() const;    
    virtual CT_ODU_IndicationType   GetForcedODUIndication() const;
    virtual CT_ODU_IndicationType   GetForcedInternalODUIndication() const;
    virtual bool                    GetForcedInternalAIS() const;
    virtual bool                    GetForcedBDI() const;
    virtual CT_TEL_BERLevels        GetBerSfThreshold() const;
    virtual CT_TEL_BERLevels        GetBerSdThreshold() const;
    virtual uint8                   GetTxPayloadType() const;
    virtual uint8                   GetExpectedPayloadType() const;
    virtual bool                    GetIsOduTerm() const;
    virtual bool                    GetSrcTrafficEnabled() const;
    virtual uint                    GetBurstyBerSdIntervals() const;
    virtual uint32                  GetBurstyBerSdThreshold() const;
    virtual CT_TEL_TS_SIZE          GetODUTsSize() const;
    virtual CT_TEL_ClkType          GetClockType() const;
    virtual uint16                  GetTribPort() const;
    virtual bool                    GetPathDelayEnabled() const;
    virtual uint32                  GetExpRate() const; 
    virtual bool                    GetNULLSignalEnable() const; 
    virtual bool                    GetPRBSRXEnable() const;
    virtual bool                    GetPRBSTXEnable() const;
    virtual uint32                  GetPRBSRXSessionCounter() const;
    virtual uint8                   GetGfpTsNum() const;
    virtual CT_ODU_ServerID         GetServer() const;
    //This method returns cross connected ODU's index in the same board.
    virtual uint8                   GetXcOtherSideIndex() const;
    virtual CT_TEL_TimCriteriaMode  GetTimCriteria() const;
    virtual bool                    GetIsProvisioned() const;
    virtual bool                    GetIsCrossConnected();
    
    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &                WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &                ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &                WriteObject(ostream & theStream);
    virtual istream   &                ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:
    void         DisplayClockTypes();

    void         RefreshGet();
    void         RefreshSet();

    // Monitoring attributes
    CT_G709Trace            itsRxTrace;
    uint32                  itsAIS;
    uint32                  itsLCK;
    uint32                  itsOCI;
    uint32                  itsBDI;
    uint32                  itsBerSf;
    uint32                  itsBerSd;
    uint32                  itsPLM;
    uint32                  itsMSIM;
    uint32                  itsGenAIS;
    uint32                  itsLOFLOM;
    uint32                  itsLOOMFI;
    uint32                  itsBip8Count;
    uint32                  itsHighBip8Count;
    uint8                   itsRxPayloadType;
    uint32                  itsInternalAIS;
    uint32                  itsInternalLCK;
    uint32                  itsInternalOCI;
    uint32                  itsSSF;
    uint32                  itsTIM;
    uint32                  itsSSFforSGEO;
    int32                   itsPathDelay;
    uint32                  itsPrbsRxLosync;
    uint32                  itsPrbsRxErrorCountHigh;
    uint32                  itsPrbsRxErrorCountLow;
    uint32                  itsPrbsRxErrorTime;
    uint32                  itsRxAps;

    // Configuration attributes
    CT_G709Trace            itsTxTrace;
    CT_G709Trace            itsExpectedTrace;
    CT_ODU_IndicationType   itsForcedODUIndication;
    CT_ODU_IndicationType   itsForcedInternalODUIndication;
    bool                    itsForcedBDI;
    bool                    itsForcedInternalAIS;
    CT_TEL_BERLevels        itsBerSfThreshold;
    CT_TEL_BERLevels        itsBerSdThreshold;
    uint8                   itsTxPayloadType;
    uint8                   itsExpectedPayloadType;
    bool                    itsIsOduTerm;
    bool                    itsSrcTrafficEnabled;
    uint                    itsBurstySdBerIntervals;
    uint32                  itsBurstySdBerThreshold;
    CT_TEL_TS_SIZE          itsODUTsSize;
    CT_TEL_ClkType          itsClockType;
    uint16                  itsTribPort;
    bool                    itsPathDelayEnabled;
    uint32                  itsExpRate;
    bool                    itsNULLSignalEnable;
    bool                    itsPRBSRXEnable;
    bool                    itsPRBSTXEnable;
    uint32                  itsPRBSRXSessionCounter;
    uint8                   itsGfpTsNum;
    CT_ODU_ServerID         itsServer;
    uint8                   itsXcOtherSideIndex;
    CT_TEL_TimCriteriaMode  itsTIMCriteraMode;
    bool                    itsTIMMonitoringEnable;
    bool                    itsLayerFailOnTIM;
    bool                    itsProvisioned;
    bool                    itsCrossConnected;
    struct TxApsData
    {
        CT_SP_APS_Channel channel;
        uint32 bytes;
	    bool apsInsert;
    } itsTxAps;
};    

#endif // _TSPII_DWIF_H
