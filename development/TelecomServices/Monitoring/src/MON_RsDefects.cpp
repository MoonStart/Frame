// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_RsDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_RsDefects::MON_RsDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerForMSFailTAState(false),
    myUpperLayerForMSFailTACount(0),    
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),
    myIsConnectedAsSrcState(false),
    myIsConnectedAsSrcCount(0),
    myIsConnectedAsDstState(false),
    myIsConnectedAsDstCount(0),
    myAISTxCount(0),
    myTlabAISTxCount(0),
    myLOSCount(0),
    myPiiLOSCount(0),
    myOOFCount(0),
    myLOFCount(0),
    myTIMCount(0),
    myTlabAISCount(0),
    myGenAISCount(0),
    myInternalGenAISCount(0),
    myAISTxState(false),
    myTlabAISTxState(false),
    myLOSState(false),
    myPiiLOSState(false),
    myOOFState(false),
    myLOFState(false),
    myTIMState(false),
    myTlabAISState(false),
    myGenAISState(false),
    myInternalGenAISState(false),
    myLayerFailOnTimCount(0),
    myLayerFailOnTimEnable(false),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),
    myInternalLockState(false),
    myInternalLockCount(0),
    myUpperLayerInternalFailPNLTAState(false),
    myUpperLayerInternalFailPNLTACount(0),
    myInternalLOFState(false),
    myInternalLOFCount(0),
    myInternalCSFOPUState(false),
    myInternalCSFOPUCount(0),
    myLocalFaultState(false),
    myLocalFaultCount(0),
    myRemoteFaultState(false),
    myRemoteFaultCount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_RS_DEFAULT_BITMASK)
{
}

MON_RsDefects::~MON_RsDefects()
{
}


void MON_RsDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerFailTACount = 0;
    myUpperLayerForMSFailTACount = 0;
    myUpperLayerFailNTACount = 0;
    myLockCount = 0;
    myIsConnectedAsSrcCount = 0;
    myIsConnectedAsDstCount = 0;
    myAISTxCount = 0;
    myTlabAISTxCount = 0;
    myLOSCount = 0;
    myPiiLOSCount = 0;
    myOOFCount = 0;
    myLOFCount = 0;
    myTIMCount = 0;
    myTlabAISCount = 0;
    myGenAISCount = 0;
    myInternalGenAISCount = 0;
    myUpperLayerFailTAState = false;
    myUpperLayerForMSFailTAState = false;
    myUpperLayerFailNTAState = false;
    myLockState = false;
    myIsConnectedAsSrcState = false;
    myIsConnectedAsDstState = false;
    myAISTxState = false;
    myTlabAISTxState = false;
    myLOSState = false;
    myPiiLOSState = false;
    myOOFState = false;
    myLOFState = false;
    myTIMState = false;
    myTlabAISState = false;
    myGenAISState = false;
    myInternalGenAISState = false;

    myLayerFailOnTimEnable = false;

    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;
    myInternalLockState = false;
    myInternalLockCount = 0;
    myUpperLayerInternalFailPNLTAState = false;
    myUpperLayerInternalFailPNLTACount = 0;
    myInternalLOFState = false;
    myInternalLOFCount = 0;
    myInternalCSFOPUState = false;
    myInternalCSFOPUCount = 0;

    myLocalFaultState = false;
    myLocalFaultCount = 0;

    myRemoteFaultState = false;
    myRemoteFaultCount = 0;

    myTermLpbkState = false;
    myTermLpbkCount = 0;

    myDefectFailLayerBitMask = MON_FAILLAYER_RS_DEFAULT_BITMASK;
}


bool MON_RsDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myLOSState || myLOFState || myTlabAISState || myGenAISState;
    
    if(myLayerFailOnTimEnable)
        aIsLayerFail |=  myTIMState;

    return aIsLayerFail && IsValidated();
}

bool MON_RsDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = (myLOSState && LosFailLayer()) || 
                        (myLOFState && LofFailLayer()) || 
                        (myTlabAISState && TlabAisFailLayer()) || 
                        (myGenAISState && GenAisFailLayer() ||
                         myUpperLayerForMSFailTAState);
    
    if(myLayerFailOnTimEnable)
        aIsLayerFail |=  (myTIMState && TimFailLayer());

    return aIsLayerFail && IsValidated();
}

bool MON_RsDefects::LosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLOS_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::LofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLOF_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::TlabAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSTLABAIS_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::GenAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSGENAIS_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::TimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSTIM_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::LfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLF_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::RfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSRF_BITMASK) == 0 ? false : true;
}

bool MON_RsDefects::InternalLofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSINTLOF_BITMASK) == 0 ? false : true;
}

void MON_RsDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

bool MON_RsDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}

bool MON_RsDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_RsDefects::IsLayerInternalForMaintSigInDefects() const
{
    // Note: 
    // 1. Internal CSF-OPU does not fail the internal layer because we do not want to force 
    // maintenance signaling, but it will be used to shut off the laser (CFG Opt Automatic Action).
    // 2. GEN-AIS does not cause GEN-AIS insertion.
    bool aIsLayerFail = (myInternalLOFState && InternalLofFailLayer())
                     || (myUpperLayerForMSInternalFailTAState);

    return aIsLayerFail && IsValidated();
}

bool MON_RsDefects::IsLayerInternalInDefects() const
{
    // Note: 
    // 1. Internal CSF-OPU does not fail the internal layer because we do not want to force 
    // maintenance signaling, but it will be used to shut off the laser (CFG Opt Automatic Action).
    // 2. GEN-AIS does not cause GEN-AIS insertion.
    bool aIsLayerFail = myInternalLOFState || myUpperLayerInternalFailTAState;

    return aIsLayerFail && IsValidated();
}

bool MON_RsDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_RsDefects::IsInternalInPropagateNextLayerDefectsTA() const
{
    // Note: Internal PropagateNextLayerDefects does not fail the internal layer because we do not want to force 
    // maintenance signaling, but it will be used to shut off the laser (CFG Opt Automatic Action).
    return myUpperLayerInternalFailPNLTAState && IsValidated();
}


bool MON_RsDefects::IsConnectedAsSrc() const
{
    return myIsConnectedAsSrcState && IsValidated();
}

bool MON_RsDefects::IsConnectedAsDst() const
{
    return myIsConnectedAsDstState && IsValidated();
}


bool MON_RsDefects::SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable)
{
    bool hasChanged = false;

    if(myLayerFailOnTimEnable != theLayerFailOnTimEnable)
    {
        myLayerFailOnTimEnable = theLayerFailOnTimEnable;
        // Add count for dubugging
        myLayerFailOnTimCount++;
        hasChanged = true;    
    }

    return hasChanged;
}

bool MON_RsDefects::GetLocalFault() const
{
    return myLocalFaultState && IsValidated();
}

bool MON_RsDefects::GetRemoteFault() const
{
    return myRemoteFaultState && IsValidated();
}


bool MON_RsDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}

bool MON_RsDefects::GetDefectForMaintSig(CT_TEL_Defect theDefect) const
{
    uint32 aCount = 0;
    bool aState = false;
    bool rtv = false;
    GetDefectStatus(theDefect, &aCount, &aState);
    
    switch (theDefect)
    {
    case CT_TEL_RS_LOS_DEFECT:
        rtv = aState && LosFailLayer();
        break;
    case CT_TEL_RS_LOF_DEFECT:
        rtv = aState && LofFailLayer();
        break;
    case CT_TEL_RS_TIM_DEFECT:
        rtv = aState && TimFailLayer();
        break;
    case CT_TEL_RS_TLABAIS_DEFECT:
        rtv = aState && TlabAisFailLayer();
        break;
    case CT_TEL_RS_GENAIS_DEFECT:
        rtv = aState && GenAisFailLayer();
        break;
    case CT_TEL_RS_INTERNAL_LOF_DEFECT:
        rtv = aState && InternalLofFailLayer();
        break;
    case CT_TEL_RS_LOCAL_FAULT_DEFECT:
        rtv = aState && LfFailLayer();
        break;
    case CT_TEL_RS_REMOTE_FAULT_DEFECT:
        rtv = aState && RfFailLayer();
        break;
    default:
        rtv = aState;
        break;
    }
    
    // return state && xxxFailLayer()
    return rtv;    
}

void MON_RsDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_RS_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_RS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSFailTAState;
        *theCount = myUpperLayerForMSFailTACount;
        break;        
    case CT_TEL_RS_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_RS_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_RS_IS_SRC:
        *theState = myIsConnectedAsSrcState;
        *theCount = myIsConnectedAsSrcCount;
        break;
    case CT_TEL_RS_IS_DST:
        *theState = myIsConnectedAsDstState;
        *theCount = myIsConnectedAsDstCount;
        break;
    case CT_TEL_RS_AIS_TX_DEFECT:
        *theCount = myAISTxCount;
        *theState = myAISTxState;
        break;
    case CT_TEL_RS_TLABAIS_TX_DEFECT:
        *theCount = myTlabAISTxCount;
        *theState = myTlabAISTxState;
        break;
    case CT_TEL_RS_LOS_DEFECT:
        *theCount = myLOSCount;
        *theState = myLOSState;
        break;
    case CT_TEL_PII_RS_LOS_DEFECT:
        *theCount = myPiiLOSCount;
        *theState = myPiiLOSState;
        break;
    case CT_TEL_RS_OOF_DEFECT:
        *theCount = myOOFCount;
        *theState = myOOFState;
        break;
    case CT_TEL_RS_LOF_DEFECT:
        *theCount = myLOFCount;
        *theState = myLOFState;
        break;
    case CT_TEL_RS_TIM_DEFECT:
        *theCount = myTIMCount;
        *theState = myTIMState;
        break;
    case CT_TEL_RS_TLABAIS_DEFECT:
        *theCount = myTlabAISCount;
        *theState = myTlabAISState;
        break;
    case CT_TEL_RS_GENAIS_DEFECT:
        *theCount = myGenAISCount;
        *theState = myGenAISState;
        break;
    case CT_TEL_RS_INTERNAL_GENAIS_DEFECT:
        *theCount = myInternalGenAISCount;
        *theState = myInternalGenAISState;
        break;
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;     
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break;
    case CT_TEL_RS_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockCount;
        break;
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerInternalFailPNLTAState;
        *theCount = myUpperLayerInternalFailPNLTACount;
        break;
    case CT_TEL_RS_INTERNAL_LOF_DEFECT:
        *theState = myInternalLOFState;
        *theCount = myInternalLOFCount;
        break;
    case CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT:
        *theState = myInternalCSFOPUState;
        *theCount = myInternalCSFOPUCount;
        break;
    case CT_TEL_RS_LOCAL_FAULT_DEFECT:
        *theState = myLocalFaultState;
        *theCount = myLocalFaultCount;
        break;
    case CT_TEL_RS_REMOTE_FAULT_DEFECT:
        *theState = myRemoteFaultState;
        *theCount = myRemoteFaultCount;
        break;
    case CT_TEL_RS_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;

    default:
        FC_THROW_ERROR(FC_SWError, "MON_RsDefects: defect not supported");
        break;
    }

}

void MON_RsDefects::GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const
{
    switch (theDefect)
    {
    case CT_TEL_RS_TIM_DEFECT:
        //-------------------------------------------------------
        // Use myLayerFailOnTimEnable flag to determine if the 
        // TIM_RS defect is ServiceAffecting or NSA.
        //-------------------------------------------------------
        if ( theSAFlag ) // Is TIM_RS ServiceAffecting?
        {
            *theState = (myTIMState && myLayerFailOnTimEnable);
            *theCount = myTIMCount;
        }
        else // Is TIM_RS NonServiceAffecting?
        {
            *theState = (myTIMState && !myLayerFailOnTimEnable);
            *theCount = myTIMCount;
        }
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RsDefects: unsupported defect");
    }
}

bool MON_RsDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_RS_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_RS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);
    case CT_TEL_RS_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_RS_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_RS_IS_SRC:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsSrcState, &myIsConnectedAsSrcCount);
    case CT_TEL_RS_IS_DST:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsDstState, &myIsConnectedAsDstCount);
    case CT_TEL_RS_AIS_TX_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISTxState, &myAISTxCount);
    case CT_TEL_RS_TLABAIS_TX_DEFECT:
        return UpdateDefect(theState, theTransition, &myTlabAISTxState, &myTlabAISTxCount);
    case CT_TEL_RS_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOSState, &myLOSCount);
    case CT_TEL_PII_RS_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myPiiLOSState, &myPiiLOSCount);
    case CT_TEL_RS_OOF_DEFECT:
        return UpdateDefect(theState, theTransition, &myOOFState, &myOOFCount);
    case CT_TEL_RS_LOF_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOFState, &myLOFCount);
    case CT_TEL_RS_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myTIMState, &myTIMCount);
    case CT_TEL_RS_TLABAIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myTlabAISState, &myTlabAISCount);
    case CT_TEL_RS_GENAIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myGenAISState, &myGenAISCount);
    case CT_TEL_RS_INTERNAL_GENAIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myInternalGenAISState, &myInternalGenAISCount);
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);
    case CT_TEL_RS_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockCount);
    case CT_TEL_RS_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailPNLTAState, &myUpperLayerInternalFailPNLTACount);
    case CT_TEL_RS_INTERNAL_LOF_DEFECT:
        return UpdateDefect(theState, theTransition, &myInternalLOFState, &myInternalLOFCount);
    case CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT:
        return UpdateDefect(theState, theTransition, &myInternalCSFOPUState, &myInternalCSFOPUCount);
    case CT_TEL_RS_LOCAL_FAULT_DEFECT:
        return UpdateDefect(theState, theTransition, &myLocalFaultState, &myLocalFaultCount);
    case CT_TEL_RS_REMOTE_FAULT_DEFECT:
        return UpdateDefect(theState, theTransition, &myRemoteFaultState, &myRemoteFaultCount);
    case CT_TEL_RS_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RsDefects: unsupported defect");
        return false;
    }
}

ostream& MON_RsDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerFailTAState);
    theStream << FC_InsertVar(myUpperLayerFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSFailTACount);
    theStream << FC_InsertVar(myUpperLayerFailNTAState);
    theStream << FC_InsertVar(myUpperLayerFailNTACount);
    theStream << FC_InsertVar(myLockState);
    theStream << FC_InsertVar(myLockCount);
    theStream << FC_InsertVar(myIsConnectedAsSrcState);
    theStream << FC_InsertVar(myIsConnectedAsSrcCount);
    theStream << FC_InsertVar(myIsConnectedAsDstState);
    theStream << FC_InsertVar(myIsConnectedAsDstCount);
    theStream << FC_InsertVar(myAISTxCount);
    theStream << FC_InsertVar(myTlabAISTxCount);
    theStream << FC_InsertVar(myLOSCount);
    theStream << FC_InsertVar(myPiiLOSCount);
    theStream << FC_InsertVar(myOOFCount);
    theStream << FC_InsertVar(myLOFCount);
    theStream << FC_InsertVar(myTIMCount);
    theStream << FC_InsertVar(myTlabAISCount);
    theStream << FC_InsertVar(myAISTxState);
    theStream << FC_InsertVar(myTlabAISTxState);
    theStream << FC_InsertVar(myLOSState);
    theStream << FC_InsertVar(myPiiLOSState);
    theStream << FC_InsertVar(myOOFState);
    theStream << FC_InsertVar(myLOFState);
    theStream << FC_InsertVar(myTIMState);
    theStream << FC_InsertVar(myTlabAISState);
    theStream << FC_InsertVar(myGenAISState);
    theStream << FC_InsertVar(myInternalGenAISState);
    theStream << FC_InsertVar(myLayerFailOnTimEnable);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTACount);    
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockCount);
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTACount);
    theStream << FC_InsertVar(myInternalLOFState);
    theStream << FC_InsertVar(myInternalLOFCount);
    theStream << FC_InsertVar(myInternalCSFOPUState);
    theStream << FC_InsertVar(myInternalCSFOPUCount);
    theStream << FC_InsertVar(myLocalFaultState);
    theStream << FC_InsertVar(myLocalFaultCount);
    theStream << FC_InsertVar(myRemoteFaultState);
    theStream << FC_InsertVar(myRemoteFaultCount);
    theStream << FC_InsertVar(myTermLpbkState);
    theStream << FC_InsertVar(myTermLpbkCount);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

istream& MON_RsDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLockCount);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcState);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcCount);
    theStream >> FC_ExtractVar(myIsConnectedAsDstState);
    theStream >> FC_ExtractVar(myIsConnectedAsDstCount);
    theStream >> FC_ExtractVar(myAISTxCount);
    theStream >> FC_ExtractVar(myTlabAISTxCount);
    theStream >> FC_ExtractVar(myLOSCount);
    theStream >> FC_ExtractVar(myPiiLOSCount);
    theStream >> FC_ExtractVar(myOOFCount);
    theStream >> FC_ExtractVar(myLOFCount);
    theStream >> FC_ExtractVar(myTIMCount);
    theStream >> FC_ExtractVar(myTlabAISCount);
    theStream >> FC_ExtractVar(myAISTxState);
    theStream >> FC_ExtractVar(myTlabAISTxState);
    theStream >> FC_ExtractVar(myLOSState);
    theStream >> FC_ExtractVar(myPiiLOSState);
    theStream >> FC_ExtractVar(myOOFState);
    theStream >> FC_ExtractVar(myLOFState);
    theStream >> FC_ExtractVar(myTIMState);
    theStream >> FC_ExtractVar(myTlabAISState);
    theStream >> FC_ExtractVar(myGenAISState);
    theStream >> FC_ExtractVar(myInternalGenAISState);
    theStream >> FC_ExtractVar(myLayerFailOnTimEnable);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockCount);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTACount);
    theStream >> FC_ExtractVar(myInternalLOFState);
    theStream >> FC_ExtractVar(myInternalLOFCount);
    theStream >> FC_ExtractVar(myInternalCSFOPUState);
    theStream >> FC_ExtractVar(myInternalCSFOPUCount);
    theStream >> FC_ExtractVar(myLocalFaultState);
    theStream >> FC_ExtractVar(myLocalFaultCount);
    theStream >> FC_ExtractVar(myRemoteFaultState);
    theStream >> FC_ExtractVar(myRemoteFaultCount);
    theStream >> FC_ExtractVar(myTermLpbkState);
    theStream >> FC_ExtractVar(myTermLpbkCount);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}

FC_Stream& MON_RsDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerFailTAState;
    theStream << myUpperLayerFailTACount;
    theStream << myUpperLayerForMSFailTAState;
    theStream << myUpperLayerForMSFailTACount;
    theStream << myUpperLayerFailNTAState;
    theStream << myUpperLayerFailNTACount;
    theStream << myLockState;
    theStream << myLockCount;
    theStream << myIsConnectedAsSrcState;
    theStream << myIsConnectedAsSrcCount;
    theStream << myIsConnectedAsDstState;
    theStream << myIsConnectedAsDstCount;
    theStream << myAISTxCount;
    theStream << myTlabAISTxCount;
    theStream << myLOSCount;
    theStream << myPiiLOSCount;
    theStream << myOOFCount;
    theStream << myLOFCount;
    theStream << myTIMCount;
    theStream << myTlabAISCount;
    theStream << myAISTxState;
    theStream << myTlabAISTxState;
    theStream << myLOSState;
    theStream << myPiiLOSState;
    theStream << myOOFState;
    theStream << myLOFState;
    theStream << myTIMState;
    theStream << myTlabAISState;
    theStream << myGenAISState;
    theStream << myInternalGenAISState;
    theStream << myLayerFailOnTimEnable;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myUpperLayerForMSInternalFailTAState;
    theStream << myUpperLayerForMSInternalFailTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockCount;
    theStream << myUpperLayerInternalFailPNLTAState;
    theStream << myUpperLayerInternalFailPNLTACount;
    theStream << myInternalLOFState;
    theStream << myInternalLOFCount;
    theStream << myInternalCSFOPUState;
    theStream << myInternalCSFOPUCount;
    theStream << myLocalFaultState;
    theStream << myLocalFaultCount;
    theStream << myRemoteFaultState;
    theStream << myRemoteFaultCount;
    theStream << myTermLpbkState;
    theStream << myTermLpbkCount;
    theStream << myDefectFailLayerBitMask;

    return theStream;
}

FC_Stream& MON_RsDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerFailTAState;
    theStream >> myUpperLayerFailTACount;
    theStream >> myUpperLayerForMSFailTAState;
    theStream >> myUpperLayerForMSFailTACount;
    theStream >> myUpperLayerFailNTAState;
    theStream >> myUpperLayerFailNTACount;
    theStream >> myLockState;
    theStream >> myLockCount;
    theStream >> myIsConnectedAsSrcState;
    theStream >> myIsConnectedAsSrcCount;
    theStream >> myIsConnectedAsDstState;
    theStream >> myIsConnectedAsDstCount;
    theStream >> myAISTxCount;
    theStream >> myTlabAISTxCount;
    theStream >> myLOSCount;
    theStream >> myPiiLOSCount;
    theStream >> myOOFCount;
    theStream >> myLOFCount;
    theStream >> myTIMCount;
    theStream >> myTlabAISCount;
    theStream >> myAISTxState;
    theStream >> myTlabAISTxState;
    theStream >> myLOSState;
    theStream >> myPiiLOSState;
    theStream >> myOOFState;
    theStream >> myLOFState;
    theStream >> myTIMState;
    theStream >> myTlabAISState;
    theStream >> myGenAISState;
    theStream >> myInternalGenAISState;
    theStream >> myLayerFailOnTimEnable;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myUpperLayerForMSInternalFailTAState;
    theStream >> myUpperLayerForMSInternalFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockCount;
    theStream >> myUpperLayerInternalFailPNLTAState;
    theStream >> myUpperLayerInternalFailPNLTACount;
    theStream >> myInternalLOFState;
    theStream >> myInternalLOFCount;
    theStream >> myInternalCSFOPUState;
    theStream >> myInternalCSFOPUCount;
    theStream >> myLocalFaultState;
    theStream >> myLocalFaultCount;
    theStream >> myRemoteFaultState;
    theStream >> myRemoteFaultCount;
    theStream >> myTermLpbkState;
    theStream >> myTermLpbkCount;
    theStream >> myDefectFailLayerBitMask;

    return theStream;
}

void MON_RsDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "RS      - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "RS      - UPPER LAYER FOR MS FAIL (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState) << " (" << myUpperLayerForMSFailTACount << ")" << endl;
    theStream   << "RS      - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "RS      - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "RS      - IS CONNECTED AS SOURCE OF XC      = " << DISPLAY_BOOL(myIsConnectedAsSrcState) << " (" << myIsConnectedAsSrcCount << ")" << endl;
    theStream   << "RS      - IS CONNECTED AS DESTINATION OF XC = " << DISPLAY_BOOL(myIsConnectedAsDstState) << " (" << myIsConnectedAsDstCount << ")" << endl;
    theStream   << "RS      - RS-AIS Transmitted                = " << DISPLAY_BOOL(myAISTxState) << " (" << myAISTxCount << ")"<< endl;
    theStream   << "RS      - RS-TLAB AIS Transmitted           = " << DISPLAY_BOOL(myTlabAISTxState) << " (" << myTlabAISTxCount << ")"<< endl;
    theStream   << "RS      - RS-LOS                            = " << DISPLAY_BOOL(myLOSState) << " (" << myLOSCount << ")"<< endl;
    theStream   << "RS      - (PII) RS-LOS                      = " << DISPLAY_BOOL(myPiiLOSState) << " (" << myPiiLOSCount << ")"<< endl;
    theStream   << "RS      - RS-OOF                            = " << DISPLAY_BOOL(myOOFState) << " (" << myOOFCount << ")"<< endl;
    theStream   << "RS      - RS-LOF                            = " << DISPLAY_BOOL(myLOFState) << " (" << myLOFCount << ")"<< endl;
    theStream   << "RS      - RS-TLAB AIS                       = " << DISPLAY_BOOL(myTlabAISState) << " (" << myTlabAISCount << ")"<< endl;
    theStream   << "RS      - RS-GEN  AIS                       = " << DISPLAY_BOOL(myGenAISState) << " (" << myGenAISCount << ")"<< endl;
    theStream   << "RS      - RS-TIM                            = " << DISPLAY_BOOL(myTIMState) << " (" << myTIMCount << ")"<< endl;
    // Add Layer Fail On TIM Enable settings for dubugging
    theStream   << "RS      - RS-Layer Fail On TIM Enable       = " << DISPLAY_BOOL(myLayerFailOnTimEnable) << " (" << myLayerFailOnTimCount << ")"<< endl << endl;
    // internal defects
    theStream   << "RS      - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "RS      - INTERNAL UPPER LAYER FOR MS FAIL (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "RS      - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockCount << ")" << endl;
    theStream   << "RS      - INTERNAL UL PROP NEXT LAYER (TA)  = " << DISPLAY_BOOL(myUpperLayerInternalFailPNLTAState) << " (" << myUpperLayerInternalFailPNLTACount << ")" << endl;
    theStream   << "RS      - INTERNAL LOF                      = " << DISPLAY_BOOL(myInternalLOFState) << " (" << myInternalLOFCount << ")" << endl;
    theStream   << "RS      - INTERNAL CSF-OPU                  = " << DISPLAY_BOOL(myInternalCSFOPUState) << " (" << myInternalCSFOPUCount << ")" << endl;
    theStream   << "RS      - INTERNAL GEN AIS                  = " << DISPLAY_BOOL(myInternalGenAISState) << " (" << myInternalGenAISCount << ")"<< endl;

    theStream   << "RS      - Local Fault                       = " << DISPLAY_BOOL(myLocalFaultState) << " (" << myLocalFaultCount << ")" << endl;
    theStream   << "RS      - Remote Fault                      = " << DISPLAY_BOOL(myRemoteFaultState) << " (" << myRemoteFaultCount << ")" << endl;

    theStream   << "RS      - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;

    theStream   << "RS      - LOS Fail Layer                    = " << DISPLAY_BOOL(LosFailLayer()) << endl;  
    theStream   << "RS      - LOF Fail Layer                    = " << DISPLAY_BOOL(LofFailLayer()) << endl;  
    theStream   << "RS      - TLABAIS Fail Layer                = " << DISPLAY_BOOL(TlabAisFailLayer()) << endl;  
    theStream   << "RS      - TIM Fail Layer                    = " << DISPLAY_BOOL(TimFailLayer()) << endl;  
    theStream   << "RS      - GENAIS Fail Layer                 = " << DISPLAY_BOOL(GenAisFailLayer()) << endl; 
    theStream   << "RS      - LF Fail Layer                     = " << DISPLAY_BOOL(LfFailLayer()) << endl; 
    theStream   << "RS      - RF Fail Layer                     = " << DISPLAY_BOOL(RfFailLayer()) << endl;
    theStream   << "RS      - INTERNALLOF Fail Layer            = " << DISPLAY_BOOL(InternalLofFailLayer()) << endl; 
}
