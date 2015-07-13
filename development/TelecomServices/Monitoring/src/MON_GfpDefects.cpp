// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_GfpDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_GfpDefects::MON_GfpDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerForMSFailTAState(false),
    myUpperLayerForMSFailTACount(0),
    myLOFDCount(0),
    myPLMCount(0),
    myCsfLosCount(0),
    myCsfLosyncCount(0),
    myVirtualLOFDCount(0),
    myCsfRFLinkFailCount(0),
    myCsfRFOfflineCount(0),
    myCsfRFAutoNegFailCount(0),
    myCsfLinkFailRxCount(0),
    myCsfAnfCount(0),
    myRFLinkFailCount(0),
    myRFOfflineCount(0),
    myRFAutoNegFailCount(0),
    myLinkFailRxCount(0),
    myFefiCount(0),
    myCsfFefiCount(0),
    myCsfFdiCount(0),
    myCsfRdiCount(0),
    myLosAlignCount(0),
    mySeqMisMatchCount(0),
    myCoreHecCount(0),
    myPliCount(0),
    myLOFDState(false),
    myPLMState(false),
    myCsfLosState(false),
    myCsfLosyncState(false),
    myVirtualLOFDState(false),
    myCsfRFLinkFailState(false),
    myCsfRFOfflineState(false),
    myCsfAnfState(false),
    myCsfRFAutoNegFailState(false),
    myCsfLinkFailRxState(false),
    myRFLinkFailState(false),
    myRFOfflineState(false),
    myRFAutoNegFailState(false),
    myLinkFailRxState(false),
    myFefiState(false),
    myCsfFefiState(false),
    myCsfFdiState(false),
    myCsfRdiState(false),
    myLosAlignState(false),
    mySeqMisMatchState(false),
    myCoreHecState(false),
    myPliState(false),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_GFP_DEFAULT_BITMASK)
{
}

MON_GfpDefects::~MON_GfpDefects()
{
}


void MON_GfpDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerForMSFailTAState = false;
    myUpperLayerForMSFailTACount = 0;
    myLOFDCount = 0;
    myPLMCount = 0;
    myCsfLosCount = 0;
    myCsfLosyncCount = 0;
    myVirtualLOFDCount = 0;
    myCsfRFLinkFailCount = 0;
    myCsfRFOfflineCount = 0;
    myCsfRFAutoNegFailCount = 0;
    myCsfLinkFailRxCount = 0;
    myRFLinkFailCount = 0;
    myRFOfflineCount = 0;
    myRFAutoNegFailCount = 0;
    myCsfAnfCount = 0;
    myLinkFailRxCount = 0;
    myFefiCount = 0;
    myCsfFefiCount = 0;
    myCsfFdiCount = 0;
    myCsfRdiCount = 0;
    myLosAlignCount = 0;
    mySeqMisMatchCount = 0;
    myCoreHecCount = 0;
    myPliCount = 0;

    myLOFDState = false;
    myPLMState = false;
    myCsfLosState = false;
    myCsfLosyncState = false;
    myVirtualLOFDState = false;
    myCsfRFLinkFailState = false;
    myCsfRFOfflineState = false;
    myCsfRFAutoNegFailState = false;
    myCsfAnfState = false;
    myCsfLinkFailRxState = false;
    myRFLinkFailState = false;
    myRFOfflineState = false;
    myRFAutoNegFailState = false;
    myLinkFailRxState = false;
    myFefiState = false;
    myCsfFefiState = false;
    myCsfFdiState = false;
    myCsfRdiState = false;
    myLosAlignState = false;
    mySeqMisMatchState = false;
    myCoreHecState = false;
    myPliState = false;

    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;
    myInternalLockState = false;
    myInternalLockLockCount = 0;

    myDefectFailLayerBitMask = MON_FAILLAYER_GFP_DEFAULT_BITMASK;
}


// Add myUpperLayerInternalFailTAState to InLayerInDefects because it does not automatically set any defect (i.e., LOFD) 
bool MON_GfpDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myLOFDState || myPLMState || myCsfLosState || myCsfLosyncState || myVirtualLOFDState || myCsfFdiState || myUpperLayerInternalFailTAState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_GfpDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = (myLOFDState && LofdFailLayer())
                     || (myPLMState && PlmFailLayer())
                     || (myCsfLosState && CsfLosFailLayer())
                     || (myCsfLosyncState && CsfLosyncFailLayer()) 
                     || (myVirtualLOFDState)
                     || (myCsfFdiState && CsfFdiFailLayer())
                     || (myUpperLayerForMSInternalFailTAState);
    
    return aIsLayerFail && IsValidated();
}

bool MON_GfpDefects::IsLayerLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_GfpDefects::LfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLF_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::RfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPRF_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::FefiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPFEFI_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::CsfFefiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFFEFI_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::LinkFailRxFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLINKFAILRX_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::CsfLosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFLOS_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::CsfLosyncFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFLOSYNC_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::LofdFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLOFD_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::PlmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPPLM_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::CsfFdiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFFDI_BITMASK) == 0 ? false : true;
}

bool MON_GfpDefects::CsfRdiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFRDI_BITMASK) == 0 ? false : true;
}

void MON_GfpDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

// There is no IsLayerInternalInDefects because that is the IsLayerInDefects (line to port defects) 

bool MON_GfpDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_GfpDefects::GetDefectForMaintSig(CT_TEL_Defect theDefect) const
{
    uint32 aCount = 0;
    bool aState = false;
    bool rtv = false;
    GetDefectStatus(theDefect, &aCount, &aState);

    switch (theDefect)
    {
    case CT_TEL_GFP_LOFD_DEFECT:
        rtv = aState && LofdFailLayer();
        break;
    case CT_TEL_GFP_PLM_DEFECT:
        rtv = myPLMState && PlmFailLayer();
        break;
    case CT_TEL_GFP_CSF_LOSYNC_DEFECT:
        rtv = aState && CsfLosyncFailLayer();
        break;
    case CT_TEL_GFP_CSF_LOS_DEFECT:
        rtv = aState && CsfLosFailLayer();
        break;
    case CT_TEL_GFP_LINKFAILRX_DEFECT:
        rtv = aState && LinkFailRxFailLayer();
        break;
    case CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        rtv = aState;
        break;
    case CT_TEL_GFP_FEFI_DEFECT:
        rtv = aState && FefiFailLayer();
        break;
    case CT_TEL_GFP_CSF_FEFI_DEFECT:
        rtv = aState && CsfFefiFailLayer();
        break;
    case CT_TEL_GFP_CSF_FDI_DEFECT:
        rtv = aState && CsfFdiFailLayer();
        break;
    case CT_TEL_GFP_CSF_RDI_DEFECT:
        rtv = aState && CsfRdiFailLayer();
        break;        
    default:
        rtv = aState;
        break;
    }

    // return state && xxxFailLayer()
    return rtv;
}

void MON_GfpDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                          uint32* theCount, 
                                          bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_GFP_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theCount = myUpperLayerForMSFailTACount;
        *theState = myUpperLayerForMSFailTAState;
        break;    
    case CT_TEL_GFP_LOFD_DEFECT:
        *theCount = myLOFDCount;
        *theState = myLOFDState;
        break;
    case CT_TEL_GFP_PLM_DEFECT:
        *theCount = myPLMCount;
        *theState = myPLMState;
        break;
    case CT_TEL_GFP_CSF_LOSYNC_DEFECT:
        *theCount = myCsfLosyncCount;
        *theState = myCsfLosyncState;
        break;
    case CT_TEL_GFP_CSF_LOS_DEFECT:
        *theCount = myCsfLosCount;
        *theState = myCsfLosState;
        break;
    case CT_TEL_GFP_VIRTUAL_LOFD_DEFECT:
        *theCount = myVirtualLOFDCount;
        *theState = myVirtualLOFDState;
        break;
    case CT_TEL_GFP_CSF_TRDI_RFLINKFAIL_DEFECT:
        *theCount = myCsfRFLinkFailCount;
        *theState = myCsfRFLinkFailState;
        break;
    case CT_TEL_GFP_CSF_TRDI_RFOFFLINE_DEFECT:
        *theCount = myCsfRFOfflineCount;
        *theState = myCsfRFOfflineState;
        break;
    case CT_TEL_GFP_CSF_TRDI_RFAUTONEGFAIL_DEFECT:
        *theCount = myCsfRFAutoNegFailCount;
        *theState = myCsfRFAutoNegFailState;
        break;
    case CT_TEL_GFP_CSF_TRDI_CR0_DEFECT:
        *theCount = myCsfLinkFailRxCount;
        *theState = myCsfLinkFailRxState;
        break;
    case CT_TEL_GFP_RFLINKFAIL_DEFECT:
        *theCount = myRFLinkFailCount;
        *theState = myRFLinkFailState;
        break;
    case CT_TEL_GFP_RFOFFLINE_DEFECT:
        *theCount = myRFOfflineCount;
        *theState = myRFOfflineState;
        break;
    case CT_TEL_GFP_RFAUTONEGFAIL_DEFECT:
        *theCount = myRFAutoNegFailCount;
        *theState = myRFAutoNegFailState;
        break;
    case CT_TEL_GFP_LINKFAILRX_DEFECT:
        *theCount = myLinkFailRxCount;
        *theState = myLinkFailRxState;
        break;
    case CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break;
    case CT_TEL_GFP_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    case CT_TEL_GFP_FEFI_DEFECT:
        *theState = myFefiState;
        *theCount = myFefiCount;
        break;
    case CT_TEL_GFP_CSF_FEFI_DEFECT:
        *theState = myCsfFefiState;
        *theCount = myCsfFefiCount;
        break;
    case CT_TEL_GFP_CSF_FDI_DEFECT:
        *theState = myCsfFdiState;
        *theCount = myCsfFdiCount;
        break;
    case CT_TEL_GFP_CSF_RDI_DEFECT:
        *theState = myCsfRdiState;
        *theCount = myCsfRdiCount;
        break;
    case CT_TEL_VCG_LOS_ALIGN:
        *theCount = myLosAlignCount;
        *theState = myLosAlignState;
        break;
    case CT_TEL_VCG_SEQMISMATCH:
        *theCount = mySeqMisMatchCount;
        *theState = mySeqMisMatchState;
        break;
    case CT_TEL_GFP_CORE_HEC_DEFECT:
        *theCount = myCoreHecCount;
        *theState = myCoreHecState;
        break;
    case CT_TEL_GFP_PLI_DEFECT:
        *theCount = myPliCount;
        *theState = myPliState;
        break;
    case CT_TEL_GFP_ANF_DEFECT:
        *theState = myCsfAnfState;
        *theCount = myCsfAnfCount;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_GfpDefects: defect not supported");
        break;
    }

}

bool MON_GfpDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_GFP_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);    
    case CT_TEL_GFP_LOFD_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOFDState, &myLOFDCount);
    case CT_TEL_GFP_PLM_DEFECT:
        return UpdateDefect(theState, theTransition, &myPLMState, &myPLMCount);
    case CT_TEL_GFP_CSF_LOSYNC_DEFECT:
        return UpdateDefect(theState, theTransition, &myCsfLosyncState, &myCsfLosyncCount);
    case CT_TEL_GFP_CSF_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myCsfLosState, &myCsfLosCount);
    case CT_TEL_GFP_VIRTUAL_LOFD_DEFECT:
        return UpdateDefect(theState, theTransition, &myVirtualLOFDState, &myVirtualLOFDCount);
    case CT_TEL_GFP_CSF_TRDI_RFLINKFAIL_DEFECT:
        return UpdateDefect(theState, theTransition, &myCsfRFLinkFailState, &myCsfRFLinkFailCount);
    case CT_TEL_GFP_CSF_TRDI_RFOFFLINE_DEFECT:
       return UpdateDefect(theState, theTransition, &myCsfRFOfflineState, &myCsfRFOfflineCount);
    case CT_TEL_GFP_CSF_TRDI_RFAUTONEGFAIL_DEFECT:
       return UpdateDefect(theState, theTransition, &myCsfRFAutoNegFailState, &myCsfRFAutoNegFailCount);
    case CT_TEL_GFP_CSF_TRDI_CR0_DEFECT:
      return UpdateDefect(theState, theTransition, &myCsfLinkFailRxState, &myCsfLinkFailRxCount);
    case CT_TEL_GFP_RFLINKFAIL_DEFECT:
      return UpdateDefect(theState, theTransition, &myRFLinkFailState, &myRFLinkFailCount);
    case CT_TEL_GFP_RFOFFLINE_DEFECT:
      return UpdateDefect(theState, theTransition, &myRFOfflineState, &myRFOfflineCount); 
    case CT_TEL_GFP_RFAUTONEGFAIL_DEFECT:
      return UpdateDefect(theState, theTransition, &myRFAutoNegFailState, &myRFAutoNegFailCount); 
    case CT_TEL_GFP_LINKFAILRX_DEFECT:
      return UpdateDefect(theState, theTransition, &myLinkFailRxState, &myLinkFailRxCount);
    case CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
      return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
      return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);
    case CT_TEL_GFP_INTERNAL_LOCK:
      return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    case CT_TEL_GFP_FEFI_DEFECT:
      return UpdateDefect(theState, theTransition, &myFefiState, &myFefiCount);
    case CT_TEL_GFP_CSF_FEFI_DEFECT:
      return UpdateDefect(theState, theTransition, &myCsfFefiState, &myCsfFefiCount);
    case CT_TEL_GFP_CSF_FDI_DEFECT:
      return UpdateDefect(theState, theTransition, &myCsfFdiState, &myCsfFdiCount);
    case CT_TEL_GFP_CSF_RDI_DEFECT:
      return UpdateDefect(theState, theTransition, &myCsfRdiState, &myCsfRdiCount);
    case CT_TEL_VCG_LOS_ALIGN:
        return UpdateDefect(theState, theTransition, &myLosAlignState, &myLosAlignCount);
    case CT_TEL_VCG_SEQMISMATCH:
        return UpdateDefect(theState, theTransition, &mySeqMisMatchState, &mySeqMisMatchCount);
    case CT_TEL_GFP_CORE_HEC_DEFECT:
        return UpdateDefect(theState, theTransition, &myCoreHecState, &myCoreHecCount);
    case CT_TEL_GFP_PLI_DEFECT:
        return UpdateDefect(theState, theTransition, &myPliState, &myPliCount);
    case CT_TEL_GFP_ANF_DEFECT:
      return UpdateDefect(theState, theTransition, &myCsfAnfState, &myCsfAnfCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GfpDefects: unsupported defect");
        return false;
    }
}

ostream& MON_GfpDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerForMSFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSFailTACount);
    theStream << FC_InsertVar(myLOFDCount);
    theStream << FC_InsertVar(myPLMCount);
    theStream << FC_InsertVar(myCsfLosCount);
    theStream << FC_InsertVar(myCsfLosyncCount);
    theStream << FC_InsertVar(myLOFDState);
    theStream << FC_InsertVar(myPLMState);
    theStream << FC_InsertVar(myCsfLosState);
    theStream << FC_InsertVar(myCsfLosyncState);
    theStream << FC_InsertVar(myVirtualLOFDState);
    theStream << FC_InsertVar(myVirtualLOFDCount);
    theStream << FC_InsertVar(myCsfRFLinkFailState);
    theStream << FC_InsertVar(myCsfRFLinkFailCount);
    theStream << FC_InsertVar(myCsfRFOfflineState);
    theStream << FC_InsertVar(myCsfRFOfflineCount);
    theStream << FC_InsertVar(myCsfRFAutoNegFailState);
    theStream << FC_InsertVar(myCsfRFAutoNegFailCount);
    theStream << FC_InsertVar(myCsfLinkFailRxState);
    theStream << FC_InsertVar(myCsfLinkFailRxCount);
    theStream << FC_InsertVar(myRFLinkFailState);
    theStream << FC_InsertVar(myRFLinkFailCount);
    theStream << FC_InsertVar(myRFOfflineState);
    theStream << FC_InsertVar(myRFOfflineCount);
    theStream << FC_InsertVar(myRFAutoNegFailState);
    theStream << FC_InsertVar(myRFAutoNegFailCount);
    theStream << FC_InsertVar(myLinkFailRxState);
    theStream << FC_InsertVar(myLinkFailRxCount);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTACount);
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);
    theStream << FC_InsertVar(myFefiState);
    theStream << FC_InsertVar(myFefiCount);
    theStream << FC_InsertVar(myCsfFefiState);
    theStream << FC_InsertVar(myCsfFefiCount);
    theStream << FC_InsertVar(myCsfFdiState);
    theStream << FC_InsertVar(myCsfFdiCount);
    theStream << FC_InsertVar(myCsfRdiState);
    theStream << FC_InsertVar(myCsfRdiCount);
    theStream << FC_InsertVar(myLosAlignCount);
    theStream << FC_InsertVar(myLosAlignState);
    theStream << FC_InsertVar(mySeqMisMatchCount);
    theStream << FC_InsertVar(mySeqMisMatchState);
    theStream << FC_InsertVar(myCoreHecCount);
    theStream << FC_InsertVar(myCoreHecState);
    theStream << FC_InsertVar(myPliCount);
    theStream << FC_InsertVar(myPliState);
    theStream << FC_InsertVar(myCsfAnfState);
    theStream << FC_InsertVar(myCsfAnfCount);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

istream& MON_GfpDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTACount); 
    theStream >> FC_ExtractVar(myLOFDCount);
    theStream >> FC_ExtractVar(myPLMCount);
    theStream >> FC_ExtractVar(myCsfLosCount);
    theStream >> FC_ExtractVar(myCsfLosyncCount);
    theStream >> FC_ExtractVar(myLOFDState);
    theStream >> FC_ExtractVar(myPLMState);
    theStream >> FC_ExtractVar(myCsfLosState);
    theStream >> FC_ExtractVar(myCsfLosyncState);
    theStream >> FC_ExtractVar(myVirtualLOFDState);
    theStream >> FC_ExtractVar(myVirtualLOFDCount);
    theStream >> FC_ExtractVar(myCsfRFLinkFailState);
    theStream >> FC_ExtractVar(myCsfRFLinkFailCount);
    theStream >> FC_ExtractVar(myCsfRFOfflineState);
    theStream >> FC_ExtractVar(myCsfRFOfflineCount);
    theStream >> FC_ExtractVar(myCsfRFAutoNegFailState);
    theStream >> FC_ExtractVar(myCsfRFAutoNegFailCount);
    theStream >> FC_ExtractVar(myCsfLinkFailRxState);
    theStream >> FC_ExtractVar(myCsfLinkFailRxCount);
    theStream >> FC_ExtractVar(myRFLinkFailState);
    theStream >> FC_ExtractVar(myRFLinkFailCount);
    theStream >> FC_ExtractVar(myRFOfflineState);
    theStream >> FC_ExtractVar(myRFOfflineCount);
    theStream >> FC_ExtractVar(myRFAutoNegFailState);
    theStream >> FC_ExtractVar(myRFAutoNegFailCount);
    theStream >> FC_ExtractVar(myLinkFailRxState);
    theStream >> FC_ExtractVar(myLinkFailRxCount);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);
    theStream >> FC_ExtractVar(myFefiState);
    theStream >> FC_ExtractVar(myFefiCount);
    theStream >> FC_ExtractVar(myCsfFefiState);
    theStream >> FC_ExtractVar(myCsfFefiCount);
    theStream >> FC_ExtractVar(myCsfFdiState);
    theStream >> FC_ExtractVar(myCsfFdiCount);
    theStream >> FC_ExtractVar(myCsfRdiState);
    theStream >> FC_ExtractVar(myCsfRdiCount);
    theStream >> FC_ExtractVar(myLosAlignCount);
    theStream >> FC_ExtractVar(myLosAlignState);
    theStream >> FC_ExtractVar(mySeqMisMatchCount);
    theStream >> FC_ExtractVar(mySeqMisMatchState);
    theStream >> FC_ExtractVar(myCoreHecCount);
    theStream >> FC_ExtractVar(myCoreHecState);
    theStream >> FC_ExtractVar(myPliCount);
    theStream >> FC_ExtractVar(myPliState);
    theStream >> FC_ExtractVar(myCsfAnfState);
    theStream >> FC_ExtractVar(myCsfAnfCount);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}

FC_Stream& MON_GfpDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerForMSFailTAState;
    theStream << myUpperLayerForMSFailTACount;
    theStream << myLOFDCount;
    theStream << myPLMCount;
    theStream << myCsfLosCount;
    theStream << myCsfLosyncCount;
    theStream << myLOFDState;
    theStream << myPLMState;
    theStream << myCsfLosState;
    theStream << myCsfLosyncState;
    theStream << myVirtualLOFDState;
    theStream << myVirtualLOFDCount;
    theStream << myCsfRFLinkFailState;
    theStream << myCsfRFLinkFailCount;
    theStream << myCsfRFOfflineState;
    theStream << myCsfRFOfflineCount;
    theStream << myCsfRFAutoNegFailState;
    theStream << myCsfRFAutoNegFailCount;
    theStream << myCsfLinkFailRxState;
    theStream << myCsfLinkFailRxCount;
    theStream << myRFLinkFailState;
    theStream << myRFLinkFailCount;
    theStream << myRFOfflineState;
    theStream << myRFOfflineCount;
    theStream << myRFAutoNegFailState;
    theStream << myRFAutoNegFailCount;
    theStream << myLinkFailRxState;
    theStream << myLinkFailRxCount;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myUpperLayerForMSInternalFailTAState;
    theStream << myUpperLayerForMSInternalFailTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;
    theStream << myFefiState;
    theStream << myFefiCount;
    theStream << myCsfFefiState;
    theStream << myCsfFefiCount;
    theStream << myCsfFdiState;
    theStream << myCsfFdiCount;
    theStream << myCsfRdiState;
    theStream << myCsfRdiCount;
    theStream << myLosAlignCount;
    theStream << myLosAlignState;
    theStream << mySeqMisMatchCount;
    theStream << mySeqMisMatchState;
    theStream << myCoreHecCount;
    theStream << myCoreHecState;
    theStream << myPliCount;
    theStream << myPliState;
    theStream << myCsfAnfState;
    theStream << myCsfAnfCount;
    theStream << myDefectFailLayerBitMask;

    return theStream;
}

FC_Stream& MON_GfpDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerForMSFailTAState;
    theStream >> myUpperLayerForMSFailTACount;
    theStream >> myLOFDCount;
    theStream >> myPLMCount;
    theStream >> myCsfLosCount;
    theStream >> myCsfLosyncCount;
    theStream >> myLOFDState;
    theStream >> myPLMState;
    theStream >> myCsfLosState;
    theStream >> myCsfLosyncState;
    theStream >> myVirtualLOFDState;
    theStream >> myVirtualLOFDCount;
    theStream >> myCsfRFLinkFailState;
    theStream >> myCsfRFLinkFailCount;
    theStream >> myCsfRFOfflineState;
    theStream >> myCsfRFOfflineCount;
    theStream >> myCsfRFAutoNegFailState;
    theStream >> myCsfRFAutoNegFailCount;
    theStream >> myCsfLinkFailRxState;
    theStream >> myCsfLinkFailRxCount;
    theStream >> myRFLinkFailState;
    theStream >> myRFLinkFailCount;
    theStream >> myRFOfflineState;
    theStream >> myRFOfflineCount;
    theStream >> myRFAutoNegFailState;
    theStream >> myRFAutoNegFailCount;
    theStream >> myLinkFailRxState;
    theStream >> myLinkFailRxCount;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myUpperLayerForMSInternalFailTAState;
    theStream >> myUpperLayerForMSInternalFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;
    theStream >> myFefiState;
    theStream >> myFefiCount;
    theStream >> myCsfFefiState;
    theStream >> myCsfFefiCount;
    theStream >> myCsfFdiState;
    theStream >> myCsfFdiCount;
    theStream >> myCsfRdiState;
    theStream >> myCsfRdiCount;
    theStream >> myLosAlignCount;
    theStream >> myLosAlignState;
    theStream >> mySeqMisMatchCount;
    theStream >> mySeqMisMatchState;
    theStream >> myCoreHecCount;
    theStream >> myCoreHecState;
    theStream >> myPliCount;
    theStream >> myPliState;
    theStream >> myCsfAnfState;
    theStream >> myCsfAnfCount;
    theStream >> myDefectFailLayerBitMask;

    return theStream;
}

void MON_GfpDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "GFP     - UPPER LAYER FOR MS FAIL (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState) << " (" << myUpperLayerForMSFailTACount << ")" << endl;
    theStream   << "GFP     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "GFP     - INTERNAL UPPER LAYER FOR MS FAIL (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "GFP     - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;
    theStream   << "GFP     - GFP-LOFD                          = " << DISPLAY_BOOL(myLOFDState) << " (" << myLOFDCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-LOS                       = " << DISPLAY_BOOL(myCsfLosState) << " (" << myCsfLosCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-LOSYNC                    = " << DISPLAY_BOOL(myCsfLosyncState) << " (" << myCsfLosyncCount << ")"<< endl;
    theStream   << "GFP     - GFP-VIRTUAL LOFD (VCG TLC)        = " << DISPLAY_BOOL(myVirtualLOFDState) << " (" << myVirtualLOFDCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-FDI                       = " << DISPLAY_BOOL(myCsfFdiState) << " (" << myCsfFdiCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-RDI                       = " << DISPLAY_BOOL(myCsfRdiState) << " (" << myCsfRdiCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-TRDI-RFLINKFAIL           = " << DISPLAY_BOOL(myCsfRFLinkFailState) << " (" << myCsfRFLinkFailCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-TRDI-RFOFFLINE            = " << DISPLAY_BOOL(myCsfRFOfflineState) << " (" << myCsfRFOfflineCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-TRDI-RFUTONEGFAIL         = " << DISPLAY_BOOL(myCsfRFAutoNegFailState) << " (" << myCsfRFAutoNegFailCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-TRDI-CR0-DEFECT           = " << DISPLAY_BOOL(myCsfLinkFailRxState) << " (" << myCsfLinkFailRxCount << ")"<< endl;
    theStream   << "GFP     - GFP-RFLINKFAIL                    = " << DISPLAY_BOOL(myRFLinkFailState) << " (" << myRFLinkFailCount << ")"<< endl;
    theStream   << "GFP     - GFP-RFOFFLINE                     = " << DISPLAY_BOOL(myRFOfflineState) << " (" << myRFOfflineCount << ")"<< endl;
    theStream   << "GFP     - GFP-RFAUTONEGFAIL                 = " << DISPLAY_BOOL(myRFAutoNegFailState) << " (" << myRFAutoNegFailCount << ")"<< endl;
    theStream   << "GFP     - GFP-LINKFAILRX                    = " << DISPLAY_BOOL(myLinkFailRxState) << " (" << myLinkFailRxCount << ")"<< endl;
    theStream   << "GFP     - GFP-FEFI                          = " << DISPLAY_BOOL(myFefiState) << " (" << myFefiCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-FEFI                      = " << DISPLAY_BOOL(myCsfFefiState) << " (" << myCsfFefiCount << ")"<< endl;
    theStream   << "GFP     - GFP-CSF-ANF                       = " << DISPLAY_BOOL(myCsfAnfState)  << " (" << myCsfAnfCount << ")"<< endl;
    theStream   << "GFP     - GFP-PLM                           = " << DISPLAY_BOOL(myPLMState) << " (" << myPLMCount << ")"<< endl;
    theStream   << "GFP     - GFP-LOSS ALIGNMENT                = " << DISPLAY_BOOL(myLosAlignState) << " (" << myLosAlignCount << ")"<< endl;
    theStream   << "GFP     - GFP-SEQUENCE MISMATCH             = " << DISPLAY_BOOL(mySeqMisMatchState) << " (" << mySeqMisMatchCount << ")"<< endl;
    theStream   << "GFP     - GFP-cHEC (CORE HEC)               = " << DISPLAY_BOOL(myCoreHecState) << " (" << myCoreHecCount << ")"<< endl;
    theStream   << "GFP     - GFP-PLI (Payload Length Ind)      = " << DISPLAY_BOOL(myPliState) << " (" << myPliCount << ")"<< endl;
    theStream   << "GFP     - LF Fail Layer                     = " << DISPLAY_BOOL(LfFailLayer()) << endl;  
    theStream   << "GFP     - RF Fail Layer                     = " << DISPLAY_BOOL(RfFailLayer()) << endl;  
    theStream   << "GFP     - FEFI Fail Layer                   = " << DISPLAY_BOOL(FefiFailLayer()) << endl;  
    theStream   << "GFP     - CSF FEFI Fail Layer               = " << DISPLAY_BOOL(CsfFefiFailLayer()) << endl;  
    theStream   << "GFP     - LINK FAIL RX Fail Layer           = " << DISPLAY_BOOL(LinkFailRxFailLayer()) << endl; 
    theStream   << "GFP     - CSF LOS Fail Layer                = " << DISPLAY_BOOL(CsfLosFailLayer()) << endl; 
    theStream   << "GFP     - LOFD Fail Layer                   = " << DISPLAY_BOOL(LofdFailLayer()) << endl; 
    theStream   << "GFP     - PLM Fail Layer                    = " << DISPLAY_BOOL(PlmFailLayer()) << endl; 
    theStream   << "GFP     - CSFLOSYNC Fail Layer              = " << DISPLAY_BOOL(CsfLosyncFailLayer()) << endl;  
    theStream   << "GFP     - CSF FDI Fail Layer                = " << DISPLAY_BOOL(CsfFdiFailLayer()) << endl;
    theStream   << "GFP     - CSF RDI Fail Layer                = " << DISPLAY_BOOL(CsfRdiFailLayer()) << endl;
}
