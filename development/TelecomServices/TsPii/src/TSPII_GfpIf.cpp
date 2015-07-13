/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Definition of the class TSPII_GfpIf - Models the Generic 
             Framing Procedure termination entity.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_GfpIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_Region.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_GfpIf::TSPII_GfpIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_GfpIf::~TSPII_GfpIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::RefreshGet()
{   
    // Monitoring attributes
    itsLofd                     = GetLofd();
    itsCsfLos                   = GetCsfLos();
    itsCsfLosync                = GetCsfLosync();
    itsVirtualLofd                     = GetVirtualLofd();
    its10BErrorCount            = Get10BErrorCount();
    itsAutoNegotiationCompleted = GetAutoNegotiationCompleted();
    itsLocalAutoNegotiationFail = GetAutoNegotiationFail();
    itsLinkFail                 = GetRFLinkFail(); 
    itsOffline                  = GetRFOffline(); 
    itsAutoNegotiationFail      = GetRFAutoNegotiationFail();
    itsLinkFailRx               = GetLinkFailRx();

    itsCsfTrdiRfAnFail          = GetCsfTrdiRfAnFail();
    itsCsfTrdiRfLinkFail        = GetCsfTrdiRfLinkFail();
    itsCsfTrdiRfOffline         = GetCsfTrdiRfOffline();
    itsCsfTrdiCr0               = GetCsfTrdiCr0();
    itsFefi                     = GetFefi();
    itsCsfFefi                  = GetCsfFefi();
    itsCsfFdi                   = GetCsfFdi();
    itsCsfRdi                   = GetCsfRdi();
    itsLosAlign                 = GetLosAlign();
    itsSeqMisMatch              = GetSeqMisMatch();
    itsCoreHec                  = GetCoreHec();
    itsPli                      = GetPli();

    // Configuration attributes
    itsEnabled                = GetEnabled();
    itsFramingMode            = GetFramingMode();
    itsUpi                    = GetUpi();
    itsSuperblockSize         = GetSuperblockSize(); 
    itsForceClientMgmtFrame   = GetForceClientMgmtFrame();
    itsForce8B10BIllegalCodes = GetForce8B10BIllegalCodes();
    itsForceGenericLayerFail  = GetForceGenericLayerFail();
    itsForceIdles             = GetForceIdles();
    itsAutoNegotiationEnabled = GetAutoNegotiationEnabled();
    itsTxRemoteFault          = GetRemoteFaultTx();
    itsLinkFailTx             = GetLinkFailTx();
    itsOneWayGbeEnabled       = GetOneWayGbeEnabled();
    itsPauseFrameTransparencyEnabled = GetPauseFrameTransparencyEnabled();
    itsExtCid                 = GetExtCid();
    itsPortIndex              = GetPortIndex();
    itsExtEnabled             = GetExtEnabled();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::RefreshSet()
{   
    // Configuration attributes
    SetEnabled(itsEnabled);
    SetFramingMode(itsFramingMode); 
    SetUpi(itsUpi);
    SetSuperblockSize(itsSuperblockSize);
    SetForceClientMgmtFrame(itsForceClientMgmtFrame);
    SetForce8B10BIllegalCodes(itsForce8B10BIllegalCodes);
    SetForceGenericLayerFail(itsForceGenericLayerFail);
    SetForceIdles(itsForceIdles);
    SetRemoteFaultTx(itsTxRemoteFault);
    EnableAutoNegotiation(itsAutoNegotiationEnabled);
    SetLinkFailTx(itsLinkFailTx);
    EnableOneWayGbe(itsOneWayGbeEnabled);
    EnablePauseFrameTransparency(itsPauseFrameTransparencyEnabled);
    SetExtCid(itsExtCid);
    SetPortIndex(itsPortIndex);
    SetExtEnabled(itsExtEnabled);
    CommitGfp();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitor attributes
    itsLofd                     = 0;
    itsCsfLos                   = 0;
    itsCsfLosync                = 0;
    itsVirtualLofd                     = 0;
    its10BErrorCount            = 0;
    itsAutoNegotiationCompleted = 0;
    itsLocalAutoNegotiationFail = 0;
    itsLinkFail                 = 0;
    itsOffline                  = 0;
    itsAutoNegotiationFail      = 0;
    itsLinkFailRx               = 0;
    itsCsfTrdiRfAnFail          = 0;
    itsCsfTrdiRfLinkFail        = 0;
    itsCsfTrdiRfOffline         = 0;
    itsCsfTrdiCr0               = 0;
    itsFefi                     = 0;
    itsCsfFefi                  = 0;
    itsCsfFdi                   = 0;
    itsCsfRdi                   = 0;
    itsPlm                      = 0;
    itsLosAlign                 = 0;
    itsSeqMisMatch              = 0;
    itsCoreHec                  = 0;
    itsPli                      = 0;
    
    // Configuration attributes
    itsEnabled                = false;
    itsFramingMode            = CT_TEL_GFP_FRAMING_TRANSPARENT;
    itsUpi                    = CT_TEL_GfpUpiId_G709AMD3;
    itsSuperblockSize         = 0;
    itsForceClientMgmtFrame   = CT_TEL_GFP_CMGMT_NONE;
    itsForce8B10BIllegalCodes = false;
    itsForceGenericLayerFail  = false;
    itsForceIdles             = false;
    itsAutoNegotiationEnabled = false;
    itsTxRemoteFault          = CT_GBE_REMOTE_OK;
    itsLinkFailTx             = false;
    itsOneWayGbeEnabled       = false;
    itsPauseFrameTransparencyEnabled = false;
    itsExtCid                 = 0;
    itsPortIndex              = TSPII_MAX_OPT;
    itsExtEnabled             = false;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetEnabled(bool theEnable)
{
    itsEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetEnabled() const
{
    return itsEnabled;
}
    
///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetFramingMode(CT_TEL_GfpFramingMode theMode)
{
    itsFramingMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_GfpFramingMode TSPII_GfpIf::GetFramingMode() const
{
    return itsFramingMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetUpi(CT_TEL_GfpUpiId theUpi)
{
    itsUpi = theUpi;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_GfpUpiId TSPII_GfpIf::GetUpi() const
{
    return itsUpi;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetSuperblockSize(uint32 theSuperblockSize)
{
    itsSuperblockSize = theSuperblockSize;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetSuperblockSize() const
{
    return itsSuperblockSize;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetForceClientMgmtFrame(CT_TEL_GfpClientMgmt theFrame)
{
    itsForceClientMgmtFrame = theFrame;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_GfpClientMgmt TSPII_GfpIf::GetForceClientMgmtFrame() const
{
    return itsForceClientMgmtFrame;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetForce8B10BIllegalCodes(bool theEnable)
{
    itsForce8B10BIllegalCodes = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetForce8B10BIllegalCodes() const
{
    return itsForce8B10BIllegalCodes;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetForceGenericLayerFail() const
{
    return itsForceGenericLayerFail;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetForceGenericLayerFail(bool theEnable)
{
    itsForceGenericLayerFail = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetForceIdles(bool theEnable)
{
    itsForceIdles = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetForceIdles() const
{
    return itsForceIdles;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetLofd()
{
    return itsLofd;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfLos()
{
    return itsCsfLos;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfLosync()
{
    return itsCsfLosync;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetVirtualLofd()
{
    return itsVirtualLofd;
}


///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::Get10BErrorCount()
{
    return its10BErrorCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetAutoNegotiationCompleted()
{
    return itsAutoNegotiationCompleted;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetAutoNegotiationFail()
{
    return itsLocalAutoNegotiationFail;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetRFLinkFail()
{
    return itsLinkFail;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetRFOffline()
{
    return itsOffline;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetRFAutoNegotiationFail()
{
    return itsAutoNegotiationFail;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetLinkFailRx()
{
    return itsLinkFailRx;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::EnableAutoNegotiation(bool enable)
{
	itsAutoNegotiationEnabled = enable;    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetRemoteFaultTx(CT_GBE_REMOTE_FAULT fault)
{
    itsTxRemoteFault = fault;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetAutoNegotiationEnabled() const
{
    return itsAutoNegotiationEnabled;
}

///////////////////////////////////////////////////////////////////////////////
CT_GBE_REMOTE_FAULT TSPII_GfpIf::GetRemoteFaultTx() const
{
    return itsTxRemoteFault;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetLinkFailTx(bool enable)
{
    itsLinkFailTx = enable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetLinkFailTx() const
{
    return itsLinkFailTx;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::EnableOneWayGbe(bool enable)
{
    itsOneWayGbeEnabled = enable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetOneWayGbeEnabled() const
{
    return itsOneWayGbeEnabled;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfTrdiRfAnFail()
{
    return itsCsfTrdiRfAnFail;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfTrdiRfLinkFail()
{
    return itsCsfTrdiRfLinkFail;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfTrdiRfOffline()
{
    return itsCsfTrdiRfOffline;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfTrdiCr0()
{
    return itsCsfTrdiCr0;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfFefi()
{
    return itsCsfFefi;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfFdi()
{
    return itsCsfFdi;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCsfRdi()
{
    return itsCsfRdi;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetFefi()
{
    return itsFefi;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetPlm()
{
    return itsPlm;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetLosAlign()
{
    return itsLosAlign;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetSeqMisMatch()
{
    return itsSeqMisMatch;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetCoreHec()
{
    return itsCoreHec;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GfpIf::GetPli()
{
    return itsPli;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::EnablePauseFrameTransparency(bool enable)
{
    itsPauseFrameTransparencyEnabled = enable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetPauseFrameTransparencyEnabled() const
{
    return itsPauseFrameTransparencyEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetExtCid(uint8 theExtCid)
{
    itsExtCid = theExtCid;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_GfpIf::GetExtCid() const
{
    return itsExtCid;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetPortIndex(uint8 thePortIndex)
{
    itsPortIndex = thePortIndex;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_GfpIf::GetPortIndex() const
{
    return itsPortIndex;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::SetExtEnabled(bool theExtEnable)
{
    itsExtEnabled = theExtEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::GetExtEnabled() const
{
    return itsExtEnabled;
}
    
///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::DefaultGbepGfp()
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::CommitGfp()
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GfpIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aFramingMode = itsFramingMode;
    int aClientMgmtFrame = itsForceClientMgmtFrame;
    int faultTx = itsTxRemoteFault;

    // Monitor attributes
    theStream << itsLofd;
    theStream << itsCsfLos;
    theStream << itsCsfLosync;
    theStream << itsVirtualLofd;
    theStream << its10BErrorCount;
    theStream << itsAutoNegotiationCompleted;
    theStream << itsLocalAutoNegotiationFail;
    theStream << itsLinkFail;
    theStream << itsOffline;
    theStream << itsAutoNegotiationFail;
    theStream << itsLinkFailRx;
    theStream << itsCsfTrdiRfAnFail;
    theStream << itsCsfTrdiRfLinkFail;
    theStream << itsCsfTrdiRfOffline;
    theStream << itsCsfTrdiCr0;
    theStream << itsFefi;
    theStream << itsCsfFefi;
    theStream << itsCsfFdi;
    theStream << itsCsfRdi;
    theStream << itsPlm;
    theStream << itsLosAlign;
    theStream << itsSeqMisMatch;
    theStream << itsCoreHec;
    theStream << itsPli;
    
    // Configuration attributes
    theStream << itsEnabled;
    theStream << aFramingMode;
    theStream << itsSuperblockSize;
    theStream << aClientMgmtFrame;
    theStream << itsForce8B10BIllegalCodes;
    theStream << itsForceGenericLayerFail;
    theStream << itsForceIdles;
    theStream << itsAutoNegotiationEnabled;
    theStream << faultTx;
    theStream << itsLinkFailTx;
    theStream << itsOneWayGbeEnabled;
    theStream << itsPauseFrameTransparencyEnabled;
    theStream << itsUpi;
    theStream << itsExtCid;
    theStream << itsPortIndex;
    theStream << itsExtEnabled;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GfpIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aFramingMode;
    int aClientMgmtFrame;
    int faultTx;

    // Monitor attributes
    theStream >> itsLofd;
    theStream >> itsCsfLos;
    theStream >> itsCsfLosync;
    theStream >> itsVirtualLofd;
    theStream >> its10BErrorCount;
    theStream >> itsAutoNegotiationCompleted;
    theStream >> itsLocalAutoNegotiationFail;
    theStream >> itsLinkFail;
    theStream >> itsOffline;
    theStream >> itsAutoNegotiationFail;
    theStream >> itsLinkFailRx;
    theStream >> itsCsfTrdiRfAnFail;
    theStream >> itsCsfTrdiRfLinkFail;
    theStream >> itsCsfTrdiRfOffline;
    theStream >> itsCsfTrdiCr0;
    theStream >> itsFefi;
    theStream >> itsCsfFefi;
    theStream >> itsCsfFdi;
    theStream >> itsCsfRdi;
    theStream >> itsPlm;
    theStream >> itsLosAlign;
    theStream >> itsSeqMisMatch;
    theStream >> itsCoreHec;
    theStream >> itsPli;
    
    // Configuration attributes
    theStream >> itsEnabled;
    theStream >> aFramingMode;
    theStream >> itsSuperblockSize;
    theStream >> aClientMgmtFrame;
    theStream >> itsForce8B10BIllegalCodes;
    theStream >> itsForceGenericLayerFail;
    theStream >> itsForceIdles;
    theStream >> itsAutoNegotiationEnabled;
    theStream >> faultTx;
    theStream >> itsLinkFailTx;
    theStream >> itsOneWayGbeEnabled;
    theStream >> itsPauseFrameTransparencyEnabled;
    theStream >> itsUpi;
    theStream >> itsExtCid;
    theStream >> itsPortIndex;
    theStream >> itsExtEnabled;

    // Update the H/W
    itsFramingMode = (CT_TEL_GfpFramingMode) aFramingMode;
    itsForceClientMgmtFrame = (CT_TEL_GfpClientMgmt) aClientMgmtFrame;
    itsTxRemoteFault = (CT_GBE_REMOTE_FAULT)faultTx;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_GfpIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aFramingMode     = itsFramingMode;
    int aClientMgmtFrame = itsForceClientMgmtFrame;
    int faultTx = itsTxRemoteFault;

    // Monitor attributes
    theStream << FC_InsertVar(itsLofd);
    theStream << FC_InsertVar(itsCsfLos);
    theStream << FC_InsertVar(itsCsfLosync);
    theStream << FC_InsertVar(itsVirtualLofd);
    theStream << FC_InsertVar(its10BErrorCount);
    theStream << FC_InsertVar(itsAutoNegotiationCompleted);
    theStream << FC_InsertVar(itsLocalAutoNegotiationFail);
    theStream << FC_InsertVar(itsLinkFail);
    theStream << FC_InsertVar(itsOffline);
    theStream << FC_InsertVar(itsAutoNegotiationFail);
    theStream << FC_InsertVar(itsLinkFailRx);
    theStream << FC_InsertVar(itsCsfTrdiRfAnFail);
    theStream << FC_InsertVar(itsCsfTrdiRfLinkFail);
    theStream << FC_InsertVar(itsCsfTrdiRfOffline);
    theStream << FC_InsertVar(itsCsfTrdiCr0);
    theStream << FC_InsertVar(itsFefi);
    theStream << FC_InsertVar(itsCsfFefi);
    theStream << FC_InsertVar(itsCsfFdi);
    theStream << FC_InsertVar(itsCsfRdi);
    theStream << FC_InsertVar(itsPlm);
    theStream << FC_InsertVar(itsLosAlign);
    theStream << FC_InsertVar(itsSeqMisMatch);
    theStream << FC_InsertVar(itsCoreHec);
    theStream << FC_InsertVar(itsPli);
    
    // Configuration attributes
    theStream << FC_InsertVar(itsEnabled);
    theStream << FC_InsertVar(aFramingMode);
    theStream << FC_InsertVar(itsSuperblockSize);
    theStream << FC_InsertVar(aClientMgmtFrame);
    theStream << FC_InsertVar(itsForce8B10BIllegalCodes);
    theStream << FC_InsertVar(itsForceGenericLayerFail);
    theStream << FC_InsertVar(itsForceIdles);
    theStream << FC_InsertVar(itsAutoNegotiationEnabled);
    theStream << FC_InsertVar(faultTx);
    theStream << FC_InsertVar(itsLinkFailTx);
    theStream << FC_InsertVar(itsOneWayGbeEnabled);
    theStream << FC_InsertVar(itsPauseFrameTransparencyEnabled);
    theStream << FC_InsertVar(itsUpi);
    theStream << FC_InsertVar(itsExtCid);
    theStream << FC_InsertVar(itsPortIndex);
    theStream << FC_InsertVar(itsExtEnabled);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_GfpIf::ReadObject(istream & theStream)
{
    int aFramingMode;
    int aClientMgmtFrame;
    int faultTx;

    // Monitor attributes
    theStream >> FC_ExtractVar(itsLofd);
    theStream >> FC_ExtractVar(itsCsfLos);
    theStream >> FC_ExtractVar(itsCsfLosync);
    theStream >> FC_ExtractVar(itsVirtualLofd);
    theStream >> FC_ExtractVar(its10BErrorCount);
    theStream >> FC_ExtractVar(itsAutoNegotiationCompleted);
    theStream >> FC_ExtractVar(itsLocalAutoNegotiationFail);
    theStream >> FC_ExtractVar(itsLinkFail);
    theStream >> FC_ExtractVar(itsOffline);
    theStream >> FC_ExtractVar(itsAutoNegotiationFail);
    theStream >> FC_ExtractVar(itsLinkFailRx);
    theStream >> FC_ExtractVar(itsCsfTrdiRfAnFail);
    theStream >> FC_ExtractVar(itsCsfTrdiRfLinkFail);
    theStream >> FC_ExtractVar(itsCsfTrdiRfOffline);
    theStream >> FC_ExtractVar(itsCsfTrdiCr0);
    theStream >> FC_ExtractVar(itsFefi);
    theStream >> FC_ExtractVar(itsCsfFefi);
    theStream >> FC_ExtractVar(itsCsfFdi);
    theStream >> FC_ExtractVar(itsCsfRdi);
    theStream >> FC_ExtractVar(itsPlm);
    theStream >> FC_ExtractVar(itsLosAlign);
    theStream >> FC_ExtractVar(itsSeqMisMatch);
    theStream >> FC_ExtractVar(itsCoreHec);
    theStream >> FC_ExtractVar(itsPli);
    
    // Configuration attributes
    theStream >> FC_ExtractVar(itsEnabled);
    theStream >> FC_ExtractVar(aFramingMode);
    theStream >> FC_ExtractVar(itsSuperblockSize);
    theStream >> FC_ExtractVar(aClientMgmtFrame);
    theStream >> FC_ExtractVar(itsForce8B10BIllegalCodes);
    theStream >> FC_ExtractVar(itsForceGenericLayerFail);
    theStream >> FC_ExtractVar(itsForceIdles);
    theStream >> FC_ExtractVar(itsAutoNegotiationEnabled);
    theStream >> FC_ExtractVar(faultTx);
    theStream >> FC_ExtractVar(itsLinkFailTx);
    theStream >> FC_ExtractVar(itsOneWayGbeEnabled);
    theStream >> FC_ExtractVar(itsPauseFrameTransparencyEnabled);
    theStream >> FC_ExtractVar(itsUpi);
    theStream >> FC_ExtractVar(itsExtCid);
    theStream >> FC_ExtractVar(itsPortIndex);
    theStream >> FC_ExtractVar(itsExtEnabled);

    // Update the H/W
    itsFramingMode = (CT_TEL_GfpFramingMode) aFramingMode;
    itsForceClientMgmtFrame = (CT_TEL_GfpClientMgmt) aClientMgmtFrame;
    itsTxRemoteFault = (CT_GBE_REMOTE_FAULT)faultTx;
    
    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::Display(FC_Stream & theStream)
{    
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  GFP Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Enabled               = " << DISPLAY_BOOL(itsEnabled)                   << "\n";
    theStream << "      Framing Mode          = " << DISPLAY_GFP_FRAMING(itsFramingMode)        << "\n";
    theStream << "      Superblock Size       = " << itsSuperblockSize                          << "\n";
    theStream << "      Force Client Mgmt Frm = " << DISPLAY_GFP_CMGMT(itsForceClientMgmtFrame) << "\n";
    theStream << "      User Payload ID       = " << DISPLAY_GFP_UPI(itsUpi)                    << "\n";
    theStream << "      Force 8b/10b Ill Code = " << DISPLAY_BOOL(itsForce8B10BIllegalCodes)    << "\n";
    theStream << "      Force GenericLayerFail= " << DISPLAY_BOOL(itsForceGenericLayerFail)     << "\n";
    theStream << "      Force Idles           = " << DISPLAY_BOOL(itsForceIdles)                << "\n";
    theStream << "      Auto Neg. Enabled     = " << TEXT_ON_OFF(itsAutoNegotiationEnabled) << "\n";
    theStream << "      Remote Fault Tx       = " << DISPLAY_GBE_REMOTE_FAULT(itsTxRemoteFault) << "\n";
    theStream << "      Link Fail Tx          = " << TEXT_ON_OFF(itsLinkFailTx)         << "\n";
    theStream << "      GbE TX Only Enabled   = " << TEXT_ON_OFF(itsOneWayGbeEnabled)   << "\n";
    theStream << "      Pause Frame Xparency  = " << TEXT_ON_OFF(itsPauseFrameTransparencyEnabled) << "\n";
    theStream << "      Linear Ext Enabled    = " << TEXT_ON_OFF(itsExtEnabled)                 << endl;
    theStream << "      Ext Channel Id        = " << (unsigned int)itsExtCid                    << endl;
    theStream << "      Port Index            = " << (unsigned int)itsPortIndex                    << endl;
    theStream << "    MONITORING\n";
    theStream << "      10B Error Count       = " << its10BErrorCount                           << "\n";
    theStream << "      LOFD                  = " << TEXT_DEFECT(itsLofd)                       << "\n";
    theStream << "      CSF-LOS               = " << TEXT_DEFECT(itsCsfLos)                     << "\n";
    theStream << "      CSF-LOSYNC            = " << TEXT_DEFECT(itsCsfLosync)                  << endl;
    theStream << "      VIRTUAL LOFD (VCG TLC)= " << TEXT_DEFECT(itsVirtualLofd)                       << "\n";
    theStream << "      CSF-FDI               = " << TEXT_DEFECT(itsCsfFdi)                    << endl;
    theStream << "      CSF-RDI               = " << TEXT_DEFECT(itsCsfRdi)                    << endl;
    theStream << "      CSF-TRDI-AUTONEG-FAIL = " << TEXT_DEFECT(itsCsfTrdiRfAnFail)            << endl;
    theStream << "      CSF-TRDI-LINK-FAIL    = " << TEXT_DEFECT(itsCsfTrdiRfLinkFail)          << endl;
    theStream << "      CSF-TRDI-OFFLINE      = " << TEXT_DEFECT(itsCsfTrdiRfOffline)           << endl;
    theStream << "      CSF-TRDI-CR0          = " << TEXT_DEFECT(itsCsfTrdiCr0)                 << endl;
    theStream << "      CSF-FEFI              = " << TEXT_DEFECT(itsCsfFefi)                    << endl;
    theStream << "      Local Auto Neg. Faild = " << TEXT_DEFECT(itsLocalAutoNegotiationFail)   << "\n";
    theStream << "      Auto Neg. Completed   = " << itsAutoNegotiationCompleted        << "\n";
    theStream << "      RF Link Fail          = " << TEXT_DEFECT(itsLinkFail)           << "\n";
    theStream << "      RF Offline            = " << TEXT_DEFECT(itsOffline)            << "\n";
    theStream << "      RF Auto Neg. Fail     = " << TEXT_DEFECT(itsAutoNegotiationFail)<< "\n";
    theStream << "      Link Fail Rx          = " << TEXT_DEFECT(itsLinkFailRx)         << "\n";
    theStream << "      GFP-PLM               = " << TEXT_DEFECT(itsPlm)         << "\n";
    theStream << "      Loss Alignment        = " << TEXT_DEFECT(itsLosAlign)         << "\n";
    theStream << "      Sequence Mismatch     = " << TEXT_DEFECT(itsSeqMisMatch)         << "\n";
    theStream << "      cHEC (Core HEC)       = " << TEXT_DEFECT(itsCoreHec)         << "\n";
    theStream << "      PLI (Payload Len Ind) = " << TEXT_DEFECT(itsPli)         << "\n";
    theStream << "      FEFI                  = " << TEXT_DEFECT(itsFefi)               << endl;
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if ((argc == 1) && strcmp(argv[0], "commit") == 0)
    {
        CommitGfp();
    }
    else if ((argc == 2) && strcmp(argv[0], "enabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "framingmode") == 0)
    {
        printUsage = true;
        for (int i = 0; i < CT_TEL_GFP_FRAMING_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_GFP_FRAMING(i)) == 0)
        {
            SetFramingMode((CT_TEL_GfpFramingMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "sblocksize") == 0)
    {
        SetSuperblockSize((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "forcecmgmt") == 0) 
    {
        printUsage = true;
        for (int i = 0; i < CT_TEL_GFP_CMGMT_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_GFP_CMGMT(i)) == 0)
        {
            SetForceClientMgmtFrame((CT_TEL_GfpClientMgmt)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "force8b10billcode") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForce8B10BIllegalCodes(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForce8B10BIllegalCodes(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "upi") == 0)
    {
        if (strcmp(argv[1], "tlablegacy") == 0)
        {
            SetUpi(CT_TEL_GfpUpiId_TLABLEGACY);
        }
        else if (strcmp(argv[1], "gsupp43") == 0)
        {
            SetUpi(CT_TEL_GfpUpiId_GSUPP43);
        }
        else if (strcmp(argv[1], "g709amd3") == 0)
        {
            SetUpi(CT_TEL_GfpUpiId_G709AMD3);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "forcegenericlayerfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceGenericLayerFail(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceGenericLayerFail(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "forceidle") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceIdles(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceIdles(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc ==2 && strcmp(argv[0], "fault") == 0)
    {
        if(strcmp(argv[1], "none") == 0)
        {
            SetRemoteFaultTx(CT_GBE_REMOTE_OK);
        }
        else if (strcmp(argv[1], "link") == 0)
        {
            SetRemoteFaultTx(CT_GBE_REMOTE_LINK_FAIL);
        }
        else if (strcmp(argv[1], "offline") == 0)
        {
            SetRemoteFaultTx(CT_GBE_REMOTE_OFFLINE);
        }
        else if (strcmp(argv[1], "auto") == 0)
        {
            SetRemoteFaultTx(CT_GBE_REMOTE_AUTO_NEGOTIATION_FAIL);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "autonegotiate") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            EnableAutoNegotiation(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            EnableAutoNegotiation(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "fail") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetLinkFailTx(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLinkFailTx(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "gbeoneway") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            EnableOneWayGbe(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            EnableOneWayGbe(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "pausetransparent") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            EnablePauseFrameTransparency(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            EnablePauseFrameTransparency(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "extcid") == 0)
    {
        SetExtCid((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strncmp(argv[0], "porti", 5) == 0)
    {
        SetPortIndex((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "extenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetExtEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetExtEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    enabled            <on|off>\n"
                   "    framingmode        <Transparent|Framed>\n"
                   "    upi                <tlablegacy|gsupp43|g709amd3>\n"
                   "    sblocksize         <0 ... 1000>\n"
                   "    forcecmgmt         <None|CsfLos|CsfLosync|CsfFdi|CsfRdi|CsfTrdiAnFail|\n"
                   "                        CsfTrdiLinkFail|CsfTrdiOffline|CsfTrdiCr0|CsfFefi>\n" 
                   "    force8b10billcode  <on|off>\n"
                   "    forcegenericlayerfail  <on|off>\n"
                   "    forceidle          <on|off>\n" 
                   "    fault              <none|link|offline|auto>\n"
                   "    autonegotiate      <on|off>\n"
                   "    fail               <on|off>\n"
                   "    gbeoneway          <on|off>\n"  
                   "    pausetransparent   <on|off>\n"
                   "    portindex          <0-255> 255=none\n"
                   "    extenabled         <on|off>\n"
                   "    extcid             <0-255> 0=Off\n"
                   "    commit" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GfpIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "lofd") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLofd)) itsLofd++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLofd)) itsLofd++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "csflos") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsCsfLos)) itsCsfLos++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsCsfLos)) itsCsfLos++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "csflosync") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsCsfLosync)) itsCsfLosync++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsCsfLosync)) itsCsfLosync++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "virtlofd") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsVirtualLofd)) itsVirtualLofd++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsVirtualLofd)) itsVirtualLofd++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "10berrcount") == 0))
    {
        its10BErrorCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "inc10berrcount") == 0))
    {
        its10BErrorCount += strtoul(argv[1], NULL, 0);
    }
    else if(argc == 2 && strcmp(argv[0], "autonegotiate") == 0)
    {
        itsAutoNegotiationCompleted = strtoul(argv[1], NULL, 0);
    }
    else if(argc == 2 && strcmp(argv[0], "rflinkfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsLinkFail))
            {
                itsLinkFail++;
            }
            else
            {
                itsLinkFail+=2;
            }
            if(TSPII_DEFECT(itsOffline))
            {
                itsOffline++;
            }
            if(TSPII_DEFECT(itsAutoNegotiationFail))
            {
                itsAutoNegotiationFail++;
            }
            itsAutoNegotiationCompleted++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsLinkFail))
            {
                itsLinkFail++;
            }
            else
            {
                itsLinkFail+=2;
            }
            itsAutoNegotiationCompleted++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "rfoffline") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsOffline))
            {
                itsOffline++;
            }
            else
            {
                itsOffline+=2;
            }
            if(TSPII_DEFECT(itsLinkFail))
            {
                itsLinkFail++;
            }
            if(TSPII_DEFECT(itsAutoNegotiationFail))
            {
                itsAutoNegotiationFail++;
            }
            itsAutoNegotiationCompleted++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsOffline))
            {
                itsOffline++;
            }
            else
            {
                itsOffline+=2;
            }
            itsAutoNegotiationCompleted++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "rfautofail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsAutoNegotiationFail))
            {
                itsAutoNegotiationFail++;
            }
            else
            {
                itsAutoNegotiationFail+=2;
            }
            if(TSPII_DEFECT(itsOffline))
            {
                itsOffline++;
            }
            if(TSPII_DEFECT(itsLinkFail))
            {
                itsLinkFail++;
            }
            itsAutoNegotiationCompleted++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsAutoNegotiationFail))
            {
                itsAutoNegotiationFail++;
            }
            else
            {
                itsAutoNegotiationFail+=2;
            }
            itsAutoNegotiationCompleted++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "linkfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsLinkFailRx))
            {
                itsLinkFailRx++;
            }
            else
            {
                itsLinkFailRx+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsLinkFailRx))
            {
                itsLinkFailRx++;
            }
            else
            {
                itsLinkFailRx+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csftrdianfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfTrdiRfAnFail))
            {
                itsCsfTrdiRfAnFail++;
            }
            else
            {
                itsCsfTrdiRfAnFail+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfTrdiRfAnFail))
            {
                itsCsfTrdiRfAnFail++;
            }
            else
            {
                itsCsfTrdiRfAnFail+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csftrdilinkfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfTrdiRfLinkFail))
            {
                itsCsfTrdiRfLinkFail++;
            }
            else
            {
                itsCsfTrdiRfLinkFail+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfTrdiRfLinkFail))
            {
                itsCsfTrdiRfLinkFail++;
            }
            else
            {
                itsCsfTrdiRfLinkFail+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csftrdioffline") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfTrdiRfOffline))
            {
                itsCsfTrdiRfOffline++;
            }
            else
            {
                itsCsfTrdiRfOffline+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfTrdiRfOffline))
            {
                itsCsfTrdiRfOffline++;
            }
            else
            {
                itsCsfTrdiRfOffline+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csftrdicr0") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfTrdiCr0))
            {
                itsCsfTrdiCr0++;
            }
            else
            {
                itsCsfTrdiCr0+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfTrdiCr0))
            {
                itsCsfTrdiCr0++;
            }
            else
            {
                itsCsfTrdiCr0+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csffefi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfFefi))
            {
                itsCsfFefi++;
            }
            else
            {
                itsCsfFefi+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfFefi))
            {
                itsCsfFefi++;
            }
            else
            {
                itsCsfFefi+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csffdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfFdi))
            {
                itsCsfFdi++;
            }
            else
            {
                itsCsfFdi+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfFdi))
            {
                itsCsfFdi++;
            }
            else
            {
                itsCsfFdi+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "csfrdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCsfRdi))
            {
                itsCsfRdi++;
            }
            else
            {
                itsCsfRdi+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCsfRdi))
            {
                itsCsfRdi++;
            }
            else
            {
                itsCsfRdi+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "fefi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsFefi))
            {
                itsFefi++;
            }
            else
            {
                itsFefi+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsFefi))
            {
                itsFefi++;
            }
            else
            {
                itsFefi+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "plm") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsPlm))
            {
                itsPlm++;
            }
            else
            {
                itsPlm+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsPlm))
            {
                itsPlm++;
            }
            else
            {
                itsPlm+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "losalign") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsLosAlign))
            {
                itsLosAlign++;
            }
            else
            {
                itsLosAlign+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsLosAlign))
            {
                itsLosAlign++;
            }
            else
            {
                itsLosAlign+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }    
    else if(argc == 2 && strcmp(argv[0], "seqmismatch") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsSeqMisMatch))
            {
                itsSeqMisMatch++;
            }
            else
            {
                itsSeqMisMatch+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsSeqMisMatch))
            {
                itsSeqMisMatch++;
            }
            else
            {
                itsSeqMisMatch+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "chec") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsCoreHec))
            {
                itsCoreHec++;
            }
            else
            {
                itsCoreHec+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsCoreHec))
            {
                itsCoreHec++;
            }
            else
            {
                itsCoreHec+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "pli") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsPli))
            {
                itsPli++;
            }
            else
            {
                itsPli+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsPli))
            {
                itsPli++;
            }
            else
            {
                itsPli+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "localautonegfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsLocalAutoNegotiationFail))
            {
                itsLocalAutoNegotiationFail++;
            }
            else
            {
                itsLocalAutoNegotiationFail+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsLocalAutoNegotiationFail))
            {
                itsLocalAutoNegotiationFail++;
            }
            else
            {
                itsLocalAutoNegotiationFail+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    10berrcount     <0 ... 0xFFFFFFFF>\n"
                   "    inc10berrcount  <0 ... 0xFFFFFFFF>\n"
                   "    lofd            <on|off>\n"
                   "    csflos          <on|off>\n"
                   "    csflosync       <on|off>\n" 
                   "    virtlofd        <on|off>\n"
                   "    csffdi          <on|off>\n"
                   "    csfrdi          <on|off>\n"
                   "    csftrdianfail   <on|off>\n"
                   "    csftrdilinkfail <on|off>\n"
                   "    csftrdioffline  <on|off>\n"
                   "    csftrdicr0      <on|off>\n"
                   "    csffefi         <on|off>\n"
                   "    autonegotiate     <count>\n"
                   "    localautonegfail <on|off>\n"
                   "    rflinkfail      <on|off>\n"
                   "    rfoffline       <on|off>\n"
                   "    rfautofail      <on|off>\n" 
                   "    linkfail        <on|off>\n"
                   "    plm             <on|off>\n"
                   "    losalign        <on|off>\n"
                   "    seqmismatch     <on|off>\n"
                   "    chec            <on|off>\n"
                   "    pli             <on|off>\n"
                   "    fefi            <on|off>\n" << endl;
    }
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GfpIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}

