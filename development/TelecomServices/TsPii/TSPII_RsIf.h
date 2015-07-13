#ifndef _TSPII_RSIF_H
#define _TSPII_RSIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Opm
 AUTHOR   :  Eric Bernier November 30th 1999
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for ports hardware
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_SDH16ByteTrace.h"
#include "TsPii/TSPII_BaseIf.h"

typedef CT_RS_IndicationType CT_RS_ReplaceSigType;

class TSPII_RsIf : public TSPII_BaseIf
{
    friend class SP_FsmTestParser;

public:
    
    /* Constructor */                 TSPII_RsIf(bool theDefault = false);
    virtual                           ~TSPII_RsIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual const CT_SDH16ByteTrace & GetRxTrace();
    virtual uint32                    GetCVCount();
    virtual uint32                    GetHighCVCount();
    virtual uint32                    GetLOS();
    virtual uint32                    GetLOF();
    virtual uint32                    GetGENAIS();
    virtual uint32                    GetOOF();
    virtual uint32                    GetTlabAISRx();
    //Internal LOF
    virtual uint32                    GetInternalLOF();
    //Internal GENAIS
    virtual uint32                    GetInternalGENAIS();
    //CSF-OPU (Client Signal Fail)
    virtual uint32                    GetInternalCSFOPU();
    //LF(Local Fault)
    virtual uint32                    GetLocalFault();
    //RF(Remote Fault)
    virtual uint32                    GetRemoteFault();
    // Tim
    virtual uint32                    GetTIM();

    virtual void                      registerEventHandlers(){};
    
    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetTxTrace(const CT_SDH16ByteTrace & theTrace);
    virtual void                      SetExpectedTrace(const CT_SDH16ByteTrace& theTrace);
    virtual void                      SetTIMMonitoringEnable(bool theTIMMonitoringState);
    virtual void                      SetLayerFailOnTIM(bool theLayerFailOnTIM);
    virtual void                      ForceAIS(bool theEnable);
    virtual void                      SetTxTraceTransparent(bool theTransparent);
    virtual void                      SetSignalType(CT_TEL_SignalType theSignalType);
    virtual void                      SetClockType(CT_TEL_ClkType theClockType);
    virtual void                      SetSfpRouteAndSignalType(uint32 theEndDevice, uint32 theMiddleDevice, CT_TEL_SignalType theSignalType, CT_TEL_ClkType theClockType = CT_TEL_CLK_UNKNOWN);
    virtual void                      SetForceInternalAIS(bool theEnable);
    virtual void                      SetForceRDI(bool theEnable);
    virtual void                      SetRdiReiAutomatic(bool theEnable);
    virtual void                      SetEnableMessaging(bool);
    virtual void                      SetForceInternalCSFOPU(bool theEnable);
    virtual void                      SetForceTlabAIS(bool theEnable);
    virtual void                      SetAutoTlabAIS(bool theEnable);
    virtual void                      SetAutoRateLockActive(bool theEnable);
    virtual void                      SetTrueSDHMode(bool useSDHMode);
    virtual void                      SetAddonly(bool theEnable);
    virtual void                      SetDroponly(bool theEnable);
    virtual void                      SetCBRMappingMode(CT_TEL_PayloadType theMappingMode); 
    virtual void					  ForceRsIndication(CT_RS_IndicationType theIndication);
    virtual void					  ForceInternalRsIndication(CT_RS_IndicationType theIndication);
    virtual void					  SetReplaceSig(CT_RS_ReplaceSigType theIndication);
    virtual void                      SetInterPacketGap(uint8 theInterPacketGap);
     
    virtual const CT_SDH16ByteTrace & GetTxTrace() const;
    virtual const CT_SDH16ByteTrace & GetExpectedTrace() const;
    virtual bool                      GetTIMMonitoringEnable() const;
    virtual bool                      GetLayerFailOnTIM() const;
    virtual bool                      GetForceAIS() const;
    virtual bool                      GetTxTraceTransparent() const;
    virtual CT_TEL_SignalType         GetSignalType() const;
    virtual CT_TEL_ClkType            GetClockType() const;
    virtual bool                      GetSfpRouteAndSignalType(uint32 & theEndDevice, uint32 & theMiddleDevice, CT_TEL_SignalType & theSignalType) const;
    virtual bool                      GetForceInternalAIS() const;
    virtual bool                      GetForceRDI() const;
    virtual bool                      GetRdiReiAutomatic() const;
    virtual bool                      GetMessagingEnabled() const;
    virtual bool                      GetForceInternalCSFOPU() const;
    virtual bool                      GetForceTlabAIS() const;
    virtual bool                      GetAutoTlabAIS() const;
    virtual bool                      GetAutoRateLockActive() const;
    virtual bool                      GetTlabAISTx() const;
    virtual bool                      GetTrueSDHMode() const;
    virtual bool                      GetAddonly() const;
    virtual bool                      GetDroponly() const;
    virtual CT_TEL_PayloadType        GetCBRMappingMode()const;
    virtual CT_RS_IndicationType      GetForceRsIndication() const;
    virtual CT_RS_IndicationType      GetForceInternalRsIndication() const;
    virtual CT_RS_ReplaceSigType      GetReplaceSig() const;
    virtual uint8                     GetInterPacketGap() const;

    virtual bool                      IsSonetTerminated();
    virtual void                      ForceFrmOduXconn(uint32 theCurSfpRouteEnd, uint32 thePrevSfpRouteEnd);
    
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
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void              RefreshGet();
    void              RefreshSet();
    void              DisplaySignalTypes();
    void              DisplayClockTypes();
    void              DisplayRouteAndSignalTypes();

    // Monitoring attributes
    uint32            itsLOS;
    uint32            itsLOF;
    uint32            itsOOF;
    uint32            itsTIM;
    uint32            itsGENAIS;
    uint32            itsCVCount;
    uint32            itsHighCVCount;
    CT_SDH16ByteTrace itsRxTrace;
    uint32            itsTlabAISRx;
    bool              itsTlabAISTx;
    uint32            itsInternalLOF;
    uint32            itsInternalGENAIS;
    uint32            itsInternalCSFOPU;
    uint32            itsOrderedSetLocalFault;
    uint32            itsOrderedSetRemoteFault;


    // Configuration attributes
    bool              itsTxTraceTransparent;
    bool              itsForceAIS;
    CT_SDH16ByteTrace itsTxTrace;
    CT_SDH16ByteTrace itsExpectedTrace;
    CT_TEL_SignalType itsSignalType;
    CT_TEL_ClkType    itsClockType;
    uint32            itsSfpRouteEnd;
    uint32            itsSfpRouteMiddle;
    bool              itsForceInternalAIS;
    bool              itsForceRDI;
    bool              itsRdiReiAutomatic;
    bool              itsMessagingEnabled;
    bool              itsForceInternalCSFOPU;
    bool              itsForceTlabAIS;
    bool              itsAutoTlabAIS;
    bool              itsAutoRateLockActive;
    bool              itsUseSDHMode;
    bool              itsAddEnable;
    bool              itsDropEnable;
    bool              itsSonetTerminated;
    CT_TEL_PayloadType    itsOduMappingMode;
    CT_RS_IndicationType  itsForcedRsIndication;
    CT_RS_IndicationType  itsForcedInternalRsIndication;
    CT_RS_ReplaceSigType  itsReplaceSig;
    uint8                 itsInterPacketGap;
    bool              itsTIMMonitoringEnable;
    bool              itsLayerFailOnTIM;
};

#endif // _TSPII_RSIF_H
