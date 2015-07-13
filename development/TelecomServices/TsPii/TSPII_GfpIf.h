#ifndef _TSPII_GFPIF_H
#define _TSPII_GFPIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds 2003
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for ports hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"

class TSPII_GfpIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_GfpIf(bool theDefault = false);
    virtual                           ~TSPII_GfpIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // GFP Config Interfaces
    // -----------------------------------------------------------------------------------

    // Enable or Disable this GFP hardware entity 
    virtual void                      SetEnabled(bool theEnable);
    virtual bool                      GetEnabled() const;
    
    // Configure the type of framing - Framed or Transparent
    virtual void                      SetFramingMode(CT_TEL_GfpFramingMode theMode);
    virtual CT_TEL_GfpFramingMode     GetFramingMode() const;

    // Configure the GFP user payload id
    virtual void                      SetUpi(CT_TEL_GfpUpiId theUpi);
    virtual CT_TEL_GfpUpiId           GetUpi() const;
    
    // Configure the Superblock size
    virtual void                      SetSuperblockSize(uint32 theSbSize);
    virtual uint32                    GetSuperblockSize() const;

    // Force a Client Management Frame in the Line direction
    virtual void                      SetForceClientMgmtFrame(CT_TEL_GfpClientMgmt theFrame);
    virtual CT_TEL_GfpClientMgmt      GetForceClientMgmtFrame() const;

    // Force 8b/10b Illegal Words in the Port direction
    virtual void                      SetForce8B10BIllegalCodes(bool theEnable);
    virtual bool                      GetForce8B10BIllegalCodes() const;

    // Force GenericLayerFail in the Port direction
    virtual void                      SetForceGenericLayerFail(bool theEnable);
    virtual bool                      GetForceGenericLayerFail() const;

    // Force Idles in the Port direction
    virtual void                      SetForceIdles(bool theEnable);
    virtual bool                      GetForceIdles() const;

    virtual void                      EnableAutoNegotiation(bool enable);
    virtual bool                      GetAutoNegotiationEnabled() const;

    virtual void                      SetRemoteFaultTx(CT_GBE_REMOTE_FAULT fault);
    virtual CT_GBE_REMOTE_FAULT       GetRemoteFaultTx() const;

    virtual void                      SetLinkFailTx(bool enable);
    virtual bool                      GetLinkFailTx() const;

    virtual void                      EnableOneWayGbe(bool enable);
    virtual bool                      GetOneWayGbeEnabled() const;

    virtual void                      EnablePauseFrameTransparency(bool enable);
    virtual bool                      GetPauseFrameTransparencyEnabled() const;

    // Configure the Extension Channel Id
    virtual void                      SetExtCid(uint8 theExtCid);
    virtual uint8                     GetExtCid() const;

    // Configure the Port Index of the facilty when Gfp is pooled
    virtual void                      SetPortIndex(uint8 thePortIndex);
    virtual uint8                     GetPortIndex() const;

    virtual void                      SetExtEnabled(bool theEnable);
    virtual bool                      GetExtEnabled() const;

    // Default GBEP's GFP config
    virtual void                      DefaultGbepGfp();

    // Indicate that GFP updates are complete
    virtual void                      CommitGfp();

    virtual void                      registerEventHandlers(){};

    // -----------------------------------------------------------------------------------
    // GFP Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32                    GetLofd();      // Loss of Frame Deliniation
    virtual uint32                    GetCsfLos();    // Client Signal Failed - Loss of Signal
    virtual uint32                    GetCsfLosync(); // Client Signal Failed - Loss of Sync
    virtual uint32                    GetVirtualLofd();     // Virtual Loss of Frame Deliniation
    virtual uint32                    Get10BErrorCount();   // Line to port direction

    virtual uint32                    GetCsfTrdiRfAnFail();
    virtual uint32                    GetCsfTrdiRfLinkFail();
    virtual uint32                    GetCsfTrdiRfOffline();
    virtual uint32                    GetCsfTrdiCr0();
    virtual uint32                    GetCsfFefi();
    virtual uint32                    GetCsfFdi();
    virtual uint32                    GetCsfRdi();

    virtual uint32                    GetAutoNegotiationCompleted();
    virtual uint32                    GetAutoNegotiationFail();
    virtual uint32                    GetRFLinkFail();
    virtual uint32                    GetRFOffline();
    virtual uint32                    GetRFAutoNegotiationFail();
    virtual uint32                    GetLinkFailRx();
    virtual uint32                    GetFefi();
    virtual uint32                    GetPlm(); 
    virtual uint32                    GetLosAlign(); 
    virtual uint32                    GetSeqMisMatch(); 
    virtual uint32                    GetCoreHec(); 
    virtual uint32                    GetPli(); 


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

    void                  RefreshGet();
    void                  RefreshSet();

    // Configuration attributes
    bool                  itsEnabled;
    CT_TEL_GfpFramingMode itsFramingMode;
    CT_TEL_GfpUpiId       itsUpi;
    uint32                itsSuperblockSize;
    CT_TEL_GfpClientMgmt  itsForceClientMgmtFrame;
    bool                  itsForce8B10BIllegalCodes;
    bool                  itsForceGenericLayerFail;
    bool                  itsForceIdles;
    bool                  itsAutoNegotiationEnabled;
    CT_GBE_REMOTE_FAULT   itsTxRemoteFault;
    bool                  itsLinkFailTx;
    bool                  itsOneWayGbeEnabled;
    bool                  itsPauseFrameTransparencyEnabled;
    uint8                 itsExtCid;
    uint8                 itsPortIndex;
    bool                  itsExtEnabled;

    // Monitoring attributes
    uint32                itsLofd;        // Loss of Frame Deliniation
    uint32                itsCsfLos;      // Client Signal Failed - Loss of Signal
    uint32                itsCsfLosync;   // Client Signal Failed - Loss of Sync
    uint32                itsVirtualLofd; // Virtual Loss of Frame Deliniation
    uint32                its10BErrorCount;
    uint32                itsCsfTrdiRfAnFail;
    uint32                itsCsfTrdiRfLinkFail;
    uint32                itsCsfTrdiRfOffline;
    uint32                itsCsfTrdiCr0;
    uint32                itsAutoNegotiationCompleted;
    uint32                itsLocalAutoNegotiationFail;
    uint32                itsLinkFail;
    uint32                itsOffline;
    uint32                itsAutoNegotiationFail;
    uint32                itsLinkFailRx;
    uint32                itsFefi;
    uint32                itsCsfFefi;
    uint32                itsCsfFdi;
    uint32                itsCsfRdi;
    uint32                itsPlm;
    uint32                itsLosAlign;
    uint32                itsSeqMisMatch;
    uint32                itsCoreHec;
    uint32                itsPli;
};

#endif // _TSPII_GFPIF_H
