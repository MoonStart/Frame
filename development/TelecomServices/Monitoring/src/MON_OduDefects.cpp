// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OduDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OduDefects::MON_OduDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myIsOduNonTerm(false),
    myLockBitMask(0),
    myInternalLockBitMask(0),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerForMSFailTAState(false),
    myUpperLayerForMSFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myUpperLayerFailPNLTAState(false),
    myUpperLayerFailPNLTACount(0),
    myLockState(false),
    myLockCount(0),
    myIsConnectedAsSrcState(false),
    myIsConnectedAsSrcCount(0),
    myIsConnectedAsDstState(false),
    myIsConnectedAsDstCount(0),
    myTIMState(false),
    myTIMCount(0),
    myBDIState(false),
    myBDICount(0),
    myAISState(false),
    myAISCount(0),
    myLCKState(false),
    myLCKCount(0),
    myOCIState(false),
    myOCICount(0),
    mySdBerCount(0),
    mySdBerState(false), 
    mySfBerCount(0),
    mySfBerState(false),
    myLayerFailOnTimEnable(false),
    myInternalAISState(false),
    myInternalAISCount(0),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),    
    myUpperLayerInternalFailNTAState(false),
    myUpperLayerInternalFailNTACount(0),
    myUpperLayerInternalFailPNLTAState(false),
    myUpperLayerInternalFailPNLTACount(0),
    myInternalLockState(false),
    myInternalLockCount(0),
    myPLMState(false),
    myPLMCount(0),
    myMSIMState(false),
    myMSIMCount(0),
    myGenAISState(false),
    myGenAISCount(0),
    myLOFLOMState(false),
    myLOFLOMCount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0),
    myUpperLayerDegradeState(false),
    myUpperLayerDegradeCount(0),
    myUpperLayerLockState(false),
    myUpperLayerLockCount(0),
    myLOOMFIState(false),
    myLOOMFICount(0),
    mySSFState(false),
    mySSFCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_ODU_DEFAULT_BITMASK)
{
}

MON_OduDefects::~MON_OduDefects()
{
}


void MON_OduDefects::Reset(void)
{
    // Initialize all attributes to zero
    MON_Defects::Reset();
    myIsOduNonTerm = false;
    myLockBitMask = 0;
    myInternalLockBitMask = 0;
    myUpperLayerFailTAState = false;
    myUpperLayerFailTACount = 0;
    myUpperLayerForMSFailTAState = false;
    myUpperLayerForMSFailTACount = 0;
    myUpperLayerFailNTAState = false;
    myUpperLayerFailNTACount = 0;
    myUpperLayerFailPNLTAState = false;
    myUpperLayerFailPNLTACount = 0;
    myLockState  = false;
    myLockCount  = 0;
    myIsConnectedAsSrcState = false;
    myIsConnectedAsSrcCount = 0;
    myIsConnectedAsDstState = false;
    myIsConnectedAsDstCount = 0;
    myTIMState   = false;
    myTIMCount   = 0;
    myBDIState   = false;
    myBDICount   = 0;
    myAISState   = false;
    myAISCount   = 0;
    myLCKState   = false;
    myLCKCount   = 0;
    myOCIState   = false;
    myOCICount   = 0;
    mySdBerState = false;
    mySdBerCount = 0;
    mySfBerState = false;   
    mySfBerCount = 0;
    myLayerFailOnTimEnable = false;
    myInternalAISState = false;
    myInternalAISCount = 0;
    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;
    myUpperLayerInternalFailNTAState = false;
    myUpperLayerInternalFailNTACount = 0;
    myUpperLayerInternalFailPNLTAState = false;
    myUpperLayerInternalFailPNLTACount = 0;
    myInternalLockState = false;
    myInternalLockCount = 0;
    myPLMState = false;
    myPLMCount = 0;
    myMSIMState = false;
    myMSIMCount = 0;
    myGenAISState = false;
    myGenAISCount = 0;
    myLOFLOMState = false;
    myLOFLOMCount = 0;
    myTermLpbkState = false;
    myTermLpbkCount = 0;
    myUpperLayerDegradeState = false;
    myUpperLayerDegradeCount = 0;
    myUpperLayerLockState = false;
    myUpperLayerLockCount = 0;
    myLOOMFIState = false;
    myLOOMFICount = 0;
    mySSFState = false;
    mySSFCount = 0;
    myDefectFailLayerBitMask = MON_FAILLAYER_ODU_DEFAULT_BITMASK;
}


void MON_OduDefects::SetIsOduNonTerm(bool theIsOduTerm)
{
    myIsOduNonTerm = theIsOduTerm;
}

bool MON_OduDefects::GetIsOduNonTerm() const
{
    return myIsOduNonTerm;
}


bool MON_OduDefects::SetLockBitMask(uint8 theBitMask)
{
    bool hasChanged = false;

    if(myLockBitMask != theBitMask)
    {
        myLockBitMask = theBitMask;
        hasChanged = true;    
    }

    return hasChanged;
}

uint8 MON_OduDefects::GetLockBitMask() const
{
    return myLockBitMask;
}

bool MON_OduDefects::SetInternalLockBitMask(uint8 theBitMask)
{
    bool hasChanged = false;

    if(myInternalLockBitMask != theBitMask)
    {
        myInternalLockBitMask = theBitMask;
        hasChanged = true;    
    }

    return hasChanged;
}

uint8 MON_OduDefects::GetInternalLockBitMask() const
{
    return myInternalLockBitMask;
}

bool MON_OduDefects::IsOtuLayerLocked(uint8 theBitMask) const
{
    // Otu layer is the high order bit
    uint8 aCheckMask = 0x80;

    // And check mask with the passed in bit mask and return true/false
    return(bool(theBitMask & aCheckMask));
}

bool MON_OduDefects::IsAnyTcmLevelLocked(uint8 theBitMask) const
{
    // Tcm levels are everything except the high and low order bits
    uint8 aCheckMask = 0x7E;

    // And check mask with the passed in bit mask and return true/false
    return(bool(theBitMask & aCheckMask));
}

bool MON_OduDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = false;

    // If Odu Non Terminating, consider only upper layer defects
    if (myIsOduNonTerm)
    {
        aIsLayerFail = myUpperLayerFailTAState;
    }
    else
    {
        // Only fail layer on ODU layer defects if Odu Terminating
        aIsLayerFail = myAISState||myLCKState||myOCIState||myPLMState||myGenAISState||myLOOMFIState;
    
        if(myLayerFailOnTimEnable)
            aIsLayerFail |=  myTIMState;
    }

    return (aIsLayerFail || IsAdaptionLayerInDefectsTA()) && IsValidated();
}

bool MON_OduDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = false;

    // If Odu Non Terminating, consider only upper layer defects
    if (myIsOduNonTerm)
    {
        aIsLayerFail = myUpperLayerForMSFailTAState;
    }
    else
    {
        // Only fail layer on ODU layer defects if Odu Terminating
        aIsLayerFail = (myAISState && AisFailLayer()) ||
                       (myLCKState && LckFailLayer()) ||
                       (myOCIState && OciFailLayer()) ||
                       (myPLMState && PlmFailLayer()) || 
                       (myGenAISState && GenAisFailLayer()) ||
                       (myLOOMFIState && MfiFailLayer() ||
                        myUpperLayerForMSFailTAState);
    
        if (myLayerFailOnTimEnable)
            aIsLayerFail |=  (myTIMState && TimFailLayer());
    }

    return (aIsLayerFail || IsAdaptionLayerForMaintSigInDefectsTA()) && IsValidated();
}

bool MON_OduDefects::AisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::OciFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUOCI_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::LckFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULCK_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::PlmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUPLM_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::MfiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULOOMFI_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::GenAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUGENAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::TimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUTIM_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::InternalAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUINTERNALAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::MsimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUMSIM_BITMASK) == 0 ? false : true;
}

bool MON_OduDefects::LoflomFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULOFLOM_BITMASK) == 0 ? false : true;
}

void MON_OduDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

bool MON_OduDefects::IsInPropagateNextLayerDefectsTA() const
{
    bool aPropagateNextLayerDefectsTA = false;

    aPropagateNextLayerDefectsTA = myUpperLayerFailPNLTAState;

    return aPropagateNextLayerDefectsTA && IsValidated();
}

bool MON_OduDefects::IsLayerInDefectsNTA() const
{
    bool aIsLayerFailNTA = false;

    // If Odu Non Terminating, ODU layer defects become NTA
    if (myIsOduNonTerm)
    {
        aIsLayerFailNTA = myAISState||myLCKState||myOCIState||myPLMState||myGenAISState||myLOOMFIState;
    
        if(myLayerFailOnTimEnable)
            aIsLayerFailNTA |=  myTIMState;
    }
    else
    {
        // If Odu Terminating, consider only upper layer defects
        aIsLayerFailNTA =  myUpperLayerFailNTAState;
    }

    return aIsLayerFailNTA && IsValidated();
}


bool MON_OduDefects::IsLayerInNonPropagateDefectsNTA() const
{
    bool aIsLayerNonPropNTA = false;

    aIsLayerNonPropNTA =  myTIMState;

    return aIsLayerNonPropNTA && IsValidated();
}


bool MON_OduDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_OduDefects::IsLayerInternalInDefects() const
{
    bool aIsLayerFail = myInternalAISState;

    return aIsLayerFail && IsValidated();
}

bool MON_OduDefects::IsLayerInternalForMaintSigInDefects() const
{
    bool aIsLayerFail = (myInternalAISState && InternalAisFailLayer()) ||
                         myUpperLayerForMSInternalFailTAState;

    return aIsLayerFail && IsValidated();
}

bool MON_OduDefects::IsInternalInPropagateNextLayerDefectsTA() const
{
    bool aPropagateNextLayerDefectsTA = false;

    aPropagateNextLayerDefectsTA = myUpperLayerInternalFailPNLTAState;

    return aPropagateNextLayerDefectsTA && IsValidated();
}

bool MON_OduDefects::IsLayerInternalInDefectsNTA() const
{
    bool aIsLayerFailNTA = false;

    aIsLayerFailNTA = myUpperLayerInternalFailNTAState;

    return aIsLayerFailNTA && IsValidated();
}

bool MON_OduDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_OduDefects::IsConnectedAsSrc() const
{
    return myIsConnectedAsSrcState && IsValidated();
}

bool MON_OduDefects::IsConnectedAsDst() const
{
    return myIsConnectedAsDstState && IsValidated();
}

bool MON_OduDefects::IsAdaptionLayerInDefectsTA() const
{
    bool aIsAdaptionLayerInDefectsTA = false;

    // Note: These always fail the layer if detected.
    aIsAdaptionLayerInDefectsTA =  myMSIMState || myLOFLOMState;

    return aIsAdaptionLayerInDefectsTA && IsValidated();
}

bool MON_OduDefects::IsAdaptionLayerForMaintSigInDefectsTA() const
{
    bool aIsAdaptionLayerInDefectsTA = false;

    // Note: These always fail the layer if detected.
    aIsAdaptionLayerInDefectsTA =  (myMSIMState && MsimFailLayer()) || 
                                   (myLOFLOMState && LoflomFailLayer());

    return aIsAdaptionLayerInDefectsTA && IsValidated();
}

bool MON_OduDefects::IsBDIForcedForDefects() const
{
    bool aIsBDIForced = false;

    aIsBDIForced = myAISState||myLCKState||myOCIState||myTIMState||myLOOMFIState||
                   IsAdaptionLayerInDefectsTA()||IsLayerInDefectsNTA()||
                   IsInPropagateNextLayerDefectsTA();

    return aIsBDIForced && IsValidated();
}

bool MON_OduDefects::IsBDIForcedForDefectsForMaintSig() const
{
    bool aIsBDIForced = false;

    aIsBDIForced = (myAISState && AisFailLayer()) ||
                   (myLCKState && LckFailLayer()) ||
                   (myOCIState && OciFailLayer()) ||
                   (myTIMState && TimFailLayer()) ||
                   (myLOOMFIState && MfiFailLayer()) ||
                   IsAdaptionLayerForMaintSigInDefectsTA() ||
                   IsLayerInDefectsNTA() || IsInPropagateNextLayerDefectsTA();

    return aIsBDIForced && IsValidated();
}

bool MON_OduDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}

bool MON_OduDefects::IsLayerInDegrade() const
{
    return (mySdBerState || myUpperLayerDegradeState) && IsValidated();
}

bool MON_OduDefects::SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable)
{
    bool hasChanged = false;

    if(myLayerFailOnTimEnable != theLayerFailOnTimEnable)
    {
        myLayerFailOnTimEnable = theLayerFailOnTimEnable;
        hasChanged = true;    
    }

    return hasChanged;
}

void MON_OduDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_ODU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSFailTAState;
        *theCount = myUpperLayerForMSFailTACount;
        break;
    case CT_TEL_ODU_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerFailPNLTAState;
        *theCount = myUpperLayerFailPNLTACount;
        break;
    case CT_TEL_ODU_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_ODU_IS_SRC:
        *theState = myIsConnectedAsSrcState;
        *theCount = myIsConnectedAsSrcCount;
        break;
    case CT_TEL_ODU_IS_DST:
        *theState = myIsConnectedAsDstState;
        *theCount = myIsConnectedAsDstCount;
        break;
    case CT_TEL_ODU_TIM_DEFECT:
        *theState = myTIMState;
        *theCount = myTIMCount;
        break;
    case CT_TEL_ODU_BDI_DEFECT:
        *theState = myBDIState;
        *theCount = myBDICount;
        break;
    case CT_TEL_ODU_AIS_DEFECT:
        *theState = myAISState;
        *theCount = myAISCount;
        break;
    case CT_TEL_ODU_LCK_DEFECT:
        *theState = myLCKState;
        *theCount = myLCKCount;
        break;
    case CT_TEL_ODU_OCI_DEFECT:
        *theState = myOCIState;
        *theCount = myOCICount;
        break;
    case CT_TEL_ODU_SDBER_DEFECT:
        *theCount = mySdBerCount;
        *theState = mySdBerState;
        break;
    case CT_TEL_ODU_SFBER_DEFECT:
        *theCount = mySfBerCount;
        *theState = mySfBerState;
        break;
    case CT_TEL_ODU_INTERNAL_AIS_DEFECT:
        *theCount = myInternalAISCount;
        *theState = myInternalAISState;
        break;
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break;        
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerInternalFailNTAState;
        *theCount = myUpperLayerInternalFailNTACount;
        break;
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerInternalFailPNLTAState;
        *theCount = myUpperLayerInternalFailPNLTACount;
        break;
    case CT_TEL_ODU_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockCount;
        break;
    case CT_TEL_ODU_PLM_DEFECT:
        *theState = myPLMState;
        *theCount = myPLMCount;
        break;
    case CT_TEL_ODU_MSIM_DEFECT:
        *theState = myMSIMState;
        *theCount = myMSIMCount;
        break;
    case CT_TEL_ODU_GENAIS_DEFECT:
        *theState = myGenAISState;
        *theCount = myGenAISCount;
        break;
    case CT_TEL_ODU_LOFLOM_DEFECT:
        *theState = myLOFLOMState;
        *theCount = myLOFLOMCount;
        break;
    case CT_TEL_ODU_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;
    case CT_TEL_ODU_UPPER_LAYER_DEGRADE_DEFECT:
        *theState = myUpperLayerDegradeState;
        *theCount = myUpperLayerDegradeCount;
        break;
    case CT_TEL_ODU_UPPER_LAYER_LOCK:
        *theState = myUpperLayerLockState;
        *theCount = myUpperLayerLockCount;
        break;
    case CT_TEL_ODU_LOOMFI_DEFECT:
        *theState = myLOOMFIState;
        *theCount = myLOOMFICount;
        break;
    case CT_TEL_ODU_SSF_DEFECT:
    	 *theState = mySSFState;
        *theCount = mySSFCount;
        break;

    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OduDefects: unsupported defect");
    }
}

void MON_OduDefects::GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const
{
    switch (theDefect)
    {
    case CT_TEL_ODU_TIM_DEFECT:
        //-------------------------------------------------------
        // Use myLayerFailOnTimEnable flag to determine if the 
        // TIM_ODU defect is ServiceAffecting or NSA.
        // for non-teminated with ENABLED-AIS, TIM is NSA
        //-------------------------------------------------------
        if ( theSAFlag ) // Is TIM_ODU ServiceAffecting?
        {
            *theState = (myTIMState && myLayerFailOnTimEnable && !myIsOduNonTerm);
            *theCount = myTIMCount;
        }
        else // Is TIM_ODU NonServiceAffecting?
        {
            *theState = (myTIMState && (!myLayerFailOnTimEnable || (myLayerFailOnTimEnable && myIsOduNonTerm)));
            *theCount = myTIMCount;
        }
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OduDefects: unsupported defect");
    }
}
    
bool MON_OduDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_ODU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);
    case CT_TEL_ODU_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailPNLTAState, &myUpperLayerFailPNLTACount);
    case CT_TEL_ODU_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_ODU_IS_SRC:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsSrcState, &myIsConnectedAsSrcCount);
    case CT_TEL_ODU_IS_DST:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsDstState, &myIsConnectedAsDstCount);
    case CT_TEL_ODU_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myTIMState, &myTIMCount);
    case CT_TEL_ODU_BDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myBDIState, &myBDICount);
    case CT_TEL_ODU_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
    case CT_TEL_ODU_LCK_DEFECT:
        return UpdateDefect(theState, theTransition, &myLCKState, &myLCKCount);
    case CT_TEL_ODU_OCI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOCIState, &myOCICount);
    case CT_TEL_ODU_SDBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdBerState, &mySdBerCount);
    case CT_TEL_ODU_SFBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySfBerState, &mySfBerCount);
    case CT_TEL_ODU_INTERNAL_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myInternalAISState, &myInternalAISCount);
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailNTAState, &myUpperLayerInternalFailNTACount);
    case CT_TEL_ODU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailPNLTAState, &myUpperLayerInternalFailPNLTACount);
    case CT_TEL_ODU_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockCount);
    case CT_TEL_ODU_PLM_DEFECT:
        return UpdateDefect(theState, theTransition, &myPLMState, &myPLMCount);
    case CT_TEL_ODU_MSIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myMSIMState, &myMSIMCount);
    case CT_TEL_ODU_GENAIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myGenAISState, &myGenAISCount);
    case CT_TEL_ODU_LOFLOM_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOFLOMState, &myLOFLOMCount);
    case CT_TEL_ODU_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);
    case CT_TEL_ODU_UPPER_LAYER_DEGRADE_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerDegradeState, &myUpperLayerDegradeCount);
    case CT_TEL_ODU_UPPER_LAYER_LOCK:
        return UpdateDefect(theState, theTransition, &myUpperLayerLockState, &myUpperLayerLockCount);
    case CT_TEL_ODU_LOOMFI_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOOMFIState, &myLOOMFICount);
    case CT_TEL_ODU_SSF_DEFECT:
    	return UpdateDefect(theState, theTransition, &mySSFState, &mySSFCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OduDefects: unsupported defect");
        return false;
    }
}

bool MON_OduDefects::IsOnlyPlmFailLayer() const
{
    bool isTimLayerfailed = false;
    if (myLayerFailOnTimEnable)
    {
        isTimLayerfailed = (myTIMState && TimFailLayer());
    }
    
    return (!myAISState && !myLCKState && !myOCIState &&
                myPLMState && PlmFailLayer() &&
                !myGenAISState && !myLOOMFIState && !isTimLayerfailed &&
                !myUpperLayerForMSFailTAState);
}

bool MON_OduDefects::IsFilterPlmDefect() const
{
    return ((myAISState && AisFailLayer()) ||
       (myLCKState && LckFailLayer()) ||
       (myOCIState && OciFailLayer()) ||
       (myTIMState && TimFailLayer()) ||
        myUpperLayerFailTAState);
}

ostream& MON_OduDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myUpperLayerFailTAState);
    theStream   << FC_InsertVar(myUpperLayerFailTACount);
    theStream   << FC_InsertVar(myUpperLayerForMSFailTAState);
    theStream   << FC_InsertVar(myUpperLayerForMSFailTACount);
    theStream   << FC_InsertVar(myUpperLayerFailNTAState);
    theStream   << FC_InsertVar(myUpperLayerFailNTACount);
    theStream   << FC_InsertVar(myUpperLayerFailPNLTAState);
    theStream   << FC_InsertVar(myUpperLayerFailPNLTACount);
    theStream   << FC_InsertVar(myLockState);
    theStream   << FC_InsertVar(myLockCount);
    theStream   << FC_InsertVar(myTIMState);
    theStream   << FC_InsertVar(myTIMCount);
    theStream   << FC_InsertVar(myBDIState);
    theStream   << FC_InsertVar(myBDICount);
    theStream   << FC_InsertVar(myAISState);
    theStream   << FC_InsertVar(myAISCount);
    theStream   << FC_InsertVar(myLCKState);
    theStream   << FC_InsertVar(myLCKCount);
    theStream   << FC_InsertVar(myOCIState);
    theStream   << FC_InsertVar(myOCICount);
    theStream   << FC_InsertVar(mySdBerState);
    theStream   << FC_InsertVar(mySdBerCount); 
    theStream   << FC_InsertVar(mySfBerState);
    theStream   << FC_InsertVar(mySfBerCount);
    theStream   << FC_InsertVar(myLayerFailOnTimEnable);
    theStream   << FC_InsertVar(myInternalAISState);
    theStream   << FC_InsertVar(myInternalAISCount);
    theStream   << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream   << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream   << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream   << FC_InsertVar(myUpperLayerForMSInternalFailTACount);    
    theStream   << FC_InsertVar(myUpperLayerInternalFailNTAState);
    theStream   << FC_InsertVar(myUpperLayerInternalFailNTACount);
    theStream   << FC_InsertVar(myUpperLayerInternalFailPNLTAState);
    theStream   << FC_InsertVar(myUpperLayerInternalFailPNLTACount);
    theStream   << FC_InsertVar(myInternalLockState);
    theStream   << FC_InsertVar(myInternalLockCount);
    theStream   << FC_InsertVar(myPLMState);
    theStream   << FC_InsertVar(myPLMCount);
    theStream   << FC_InsertVar(myMSIMState);
    theStream   << FC_InsertVar(myMSIMCount);
    theStream   << FC_InsertVar(myGenAISState);
    theStream   << FC_InsertVar(myGenAISCount);
    theStream   << FC_InsertVar(myLOFLOMState);
    theStream   << FC_InsertVar(myLOFLOMCount);
    theStream   << FC_InsertVar(myIsOduNonTerm);
    theStream   << FC_InsertVar(myLockBitMask);
    theStream   << FC_InsertVar(myInternalLockBitMask);
    theStream   << FC_InsertVar(myTermLpbkState);
    theStream   << FC_InsertVar(myTermLpbkCount);
    theStream   << FC_InsertVar(myIsConnectedAsSrcState);
    theStream   << FC_InsertVar(myIsConnectedAsSrcCount);
    theStream   << FC_InsertVar(myIsConnectedAsDstState);
    theStream   << FC_InsertVar(myIsConnectedAsDstCount);
    theStream   << FC_InsertVar(myUpperLayerDegradeState);
    theStream   << FC_InsertVar(myUpperLayerDegradeCount);
    theStream   << FC_InsertVar(myUpperLayerLockState);
    theStream   << FC_InsertVar(myUpperLayerLockCount);
    theStream   << FC_InsertVar(myLOOMFIState);
    theStream   << FC_InsertVar(myLOOMFICount);
    theStream   << FC_InsertVar(mySSFState);
    theStream   << FC_InsertVar(mySSFCount);
    theStream   << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

istream& MON_OduDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream   >> FC_ExtractVar(myUpperLayerForMSFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerForMSFailTACount);
    theStream   >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream   >> FC_ExtractVar(myUpperLayerFailPNLTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailPNLTACount);
    theStream   >> FC_ExtractVar(myLockState);
    theStream   >> FC_ExtractVar(myLockCount);
    theStream   >> FC_ExtractVar(myTIMState);
    theStream   >> FC_ExtractVar(myTIMCount);
    theStream   >> FC_ExtractVar(myBDIState);
    theStream   >> FC_ExtractVar(myBDICount);
    theStream   >> FC_ExtractVar(myAISState);
    theStream   >> FC_ExtractVar(myAISCount);
    theStream   >> FC_ExtractVar(myLCKState);
    theStream   >> FC_ExtractVar(myLCKCount);
    theStream   >> FC_ExtractVar(myOCIState);
    theStream   >> FC_ExtractVar(myOCICount);
    theStream   >> FC_ExtractVar(mySdBerState);
    theStream   >> FC_ExtractVar(mySdBerCount);    
    theStream   >> FC_ExtractVar(mySfBerState);
    theStream   >> FC_ExtractVar(mySfBerCount);
    theStream   >> FC_ExtractVar(myLayerFailOnTimEnable);
    theStream   >> FC_ExtractVar(myInternalAISState);
    theStream   >> FC_ExtractVar(myInternalAISCount);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream   >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount);    
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailNTAState);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailNTACount);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailPNLTAState);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailPNLTACount);
    theStream   >> FC_ExtractVar(myInternalLockState);
    theStream   >> FC_ExtractVar(myInternalLockCount);
    theStream   >> FC_ExtractVar(myPLMState);
    theStream   >> FC_ExtractVar(myPLMCount);
    theStream   >> FC_ExtractVar(myMSIMState);
    theStream   >> FC_ExtractVar(myMSIMCount);
    theStream   >> FC_ExtractVar(myGenAISState);
    theStream   >> FC_ExtractVar(myGenAISCount);
    theStream   >> FC_ExtractVar(myLOFLOMState);
    theStream   >> FC_ExtractVar(myLOFLOMCount);
    theStream   >> FC_ExtractVar(myIsOduNonTerm);
    theStream   >> FC_ExtractVar(myLockBitMask);
    theStream   >> FC_ExtractVar(myInternalLockBitMask);
    theStream   >> FC_ExtractVar(myTermLpbkState);
    theStream   >> FC_ExtractVar(myTermLpbkCount);
    theStream   >> FC_ExtractVar(myIsConnectedAsSrcState);
    theStream   >> FC_ExtractVar(myIsConnectedAsSrcCount);
    theStream   >> FC_ExtractVar(myIsConnectedAsDstState);
    theStream   >> FC_ExtractVar(myIsConnectedAsDstCount);
    theStream   >> FC_ExtractVar(myUpperLayerDegradeState);
    theStream   >> FC_ExtractVar(myUpperLayerDegradeCount);
    theStream   >> FC_ExtractVar(myUpperLayerLockState);
    theStream   >> FC_ExtractVar(myUpperLayerLockCount);
    theStream   >> FC_ExtractVar(myLOOMFIState);
    theStream   >> FC_ExtractVar(myLOOMFICount);
    theStream   >> FC_ExtractVar(mySSFState);
    theStream   >> FC_ExtractVar(mySSFCount);
    theStream   >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}

FC_Stream& MON_OduDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream   << myUpperLayerFailTAState;
    theStream   << myUpperLayerFailTACount;
    theStream   << myUpperLayerForMSFailTAState;
    theStream   << myUpperLayerForMSFailTACount;    
    theStream   << myUpperLayerFailNTAState;
    theStream   << myUpperLayerFailNTACount;
    theStream   << myUpperLayerFailPNLTAState;
    theStream   << myUpperLayerFailPNLTACount;
    theStream   << myLockState;
    theStream   << myLockCount;
    theStream   << myTIMState;
    theStream   << myTIMCount;
    theStream   << myBDIState;
    theStream   << myBDICount;
    theStream   << myAISState;
    theStream   << myAISCount;
    theStream   << myLCKState;
    theStream   << myLCKCount;
    theStream   << myOCIState;
    theStream   << myOCICount;
    theStream   << mySdBerState;
    theStream   << mySdBerCount;    
    theStream   << mySfBerState;
    theStream   << mySfBerCount;
    theStream   << myLayerFailOnTimEnable;
    theStream   << myInternalAISState;
    theStream   << myInternalAISCount;
    theStream   << myUpperLayerInternalFailTAState;
    theStream   << myUpperLayerInternalFailTACount;
    theStream   << myUpperLayerForMSInternalFailTAState;
    theStream   << myUpperLayerForMSInternalFailTACount;    
    theStream   << myUpperLayerInternalFailNTAState;
    theStream   << myUpperLayerInternalFailNTACount;
    theStream   << myUpperLayerInternalFailPNLTAState;
    theStream   << myUpperLayerInternalFailPNLTACount;
    theStream   << myInternalLockState;
    theStream   << myInternalLockCount;
    theStream   << myPLMState;
    theStream   << myPLMCount;
    theStream   << myMSIMState;
    theStream   << myMSIMCount;
    theStream   << myGenAISState;
    theStream   << myGenAISCount;
    theStream   << myLOFLOMState;
    theStream   << myLOFLOMCount;
    theStream   << myIsOduNonTerm;
    theStream   << myLockBitMask;
    theStream   << myInternalLockBitMask;
    theStream   << myTermLpbkState;
    theStream   << myTermLpbkCount;
    theStream   << myIsConnectedAsSrcState;
    theStream   << myIsConnectedAsSrcCount;
    theStream   << myIsConnectedAsDstState;
    theStream   << myIsConnectedAsDstCount;
    theStream   << myUpperLayerDegradeState;
    theStream   << myUpperLayerDegradeCount;
    theStream   << myUpperLayerLockState;
    theStream   << myUpperLayerLockCount;
    theStream   << myLOOMFIState;
    theStream   << myLOOMFICount;
    theStream   << mySSFState;
    theStream   << mySSFCount;
    theStream   << myDefectFailLayerBitMask;

    return theStream;

}

FC_Stream& MON_OduDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myUpperLayerFailTAState;
    theStream   >> myUpperLayerFailTACount;
    theStream   >> myUpperLayerForMSFailTAState;
    theStream   >> myUpperLayerForMSFailTACount;    
    theStream   >> myUpperLayerFailNTAState;
    theStream   >> myUpperLayerFailNTACount;
    theStream   >> myUpperLayerFailPNLTAState;
    theStream   >> myUpperLayerFailPNLTACount;
    theStream   >> myLockState;
    theStream   >> myLockCount;
    theStream   >> myTIMState;
    theStream   >> myTIMCount;
    theStream   >> myBDIState;
    theStream   >> myBDICount;
    theStream   >> myAISState;
    theStream   >> myAISCount;
    theStream   >> myLCKState;
    theStream   >> myLCKCount;
    theStream   >> myOCIState;
    theStream   >> myOCICount;
    theStream   >> mySdBerState;
    theStream   >> mySdBerCount;   
    theStream   >> mySfBerState;
    theStream   >> mySfBerCount;
    theStream   >> myLayerFailOnTimEnable;
    theStream   >> myInternalAISState;
    theStream   >> myInternalAISCount;
    theStream   >> myUpperLayerInternalFailTAState;
    theStream   >> myUpperLayerInternalFailTACount;
    theStream   >> myUpperLayerForMSInternalFailTAState;
    theStream   >> myUpperLayerForMSInternalFailTACount;    
    theStream   >> myUpperLayerInternalFailNTAState;
    theStream   >> myUpperLayerInternalFailNTACount;
    theStream   >> myUpperLayerInternalFailPNLTAState;
    theStream   >> myUpperLayerInternalFailPNLTACount;
    theStream   >> myInternalLockState;
    theStream   >> myInternalLockCount;
    theStream   >> myPLMState;
    theStream   >> myPLMCount;
    theStream   >> myMSIMState;
    theStream   >> myMSIMCount;
    theStream   >> myGenAISState;
    theStream   >> myGenAISCount;
    theStream   >> myLOFLOMState;
    theStream   >> myLOFLOMCount;
    theStream   >> myIsOduNonTerm;
    theStream   >> myLockBitMask;
    theStream   >> myInternalLockBitMask;
    theStream   >> myTermLpbkState;
    theStream   >> myTermLpbkCount;
    theStream   >> myIsConnectedAsSrcState;
    theStream   >> myIsConnectedAsSrcCount;
    theStream   >> myIsConnectedAsDstState;
    theStream   >> myIsConnectedAsDstCount;
    theStream   >> myUpperLayerDegradeState;
    theStream   >> myUpperLayerDegradeCount;
    theStream   >> myUpperLayerLockState;
    theStream   >> myUpperLayerLockCount;
    theStream   >> myLOOMFIState;
    theStream   >> myLOOMFICount;
    theStream   >> mySSFState;
    theStream   >> mySSFCount;
    theStream   >> myDefectFailLayerBitMask;

    return theStream;

}

void MON_OduDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "ODU     - Non Terminating (from MON Config) = " << DISPLAY_BOOL(myIsOduNonTerm)  << endl;
    theStream   << "ODU     - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState)  << " (" << myUpperLayerFailTACount  << ")" << endl;
    theStream   << "ODU     - UPPER LAYER FAIL FOR MS (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState)  << " (" << myUpperLayerForMSFailTACount  << ")" << endl;
    theStream   << "ODU     - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "ODU     - UPPER LAYER DEGRADE               = " << DISPLAY_BOOL(myUpperLayerDegradeState) << " (" << myUpperLayerDegradeCount << ")" << endl;
    theStream   << "ODU     - UPPER LAYER LOCK                  = " << DISPLAY_BOOL(myUpperLayerLockState) << " (" << myUpperLayerLockCount << ")" << endl;
    theStream   << "ODU     - UPPER LAYER PROP NEXT LAYER(TA)   = " << DISPLAY_BOOL(myUpperLayerFailPNLTAState) << " (" << myUpperLayerFailPNLTACount << ")" << endl;
    theStream   << "ODU     - LOCK STATE                        = " << DISPLAY_BOOL(myLockState)  << " (" << myLockCount  << ")" << endl;
    uint16 aBitMask16 = uint16(myLockBitMask);
    theStream   << "ODU     - LOCK BIT MASK                     = " << hex << " [0x" << aBitMask16  << "]" << dec << endl;    
    theStream   << "ODU     - IS CONNECTED AS SOURCE OF XC      = " << DISPLAY_BOOL(myIsConnectedAsSrcState) << " (" << myIsConnectedAsSrcCount << ")" << endl;
    theStream   << "ODU     - IS CONNECTED AS DESTINATION OF XC = " << DISPLAY_BOOL(myIsConnectedAsDstState) << " (" << myIsConnectedAsDstCount << ")" << endl;
    theStream   << "ODU     - ODU-BDI                           = " << DISPLAY_BOOL(myBDIState)   << " (" << myBDICount   << ")" << endl;
    theStream   << "ODU     - ODU-AIS                           = " << DISPLAY_BOOL(myAISState)   << " (" << myAISCount   << ")" << endl;
    theStream   << "ODU     - ODU-LCK                           = " << DISPLAY_BOOL(myLCKState)   << " (" << myLCKCount   << ")" << endl;
    theStream   << "ODU     - ODU-OCI                           = " << DISPLAY_BOOL(myOCIState)   << " (" << myOCICount   << ")" << endl;
    theStream   << "ODU     - ODU-PLM                           = " << DISPLAY_BOOL(myPLMState)   << " (" << myPLMCount   << ")" << endl;
    theStream   << "ODU     - ODU-MSIM                          = " << DISPLAY_BOOL(myMSIMState)  << " (" << myMSIMCount  << ")" << endl;
    theStream   << "ODU     - ODU-LOFLOM                        = " << DISPLAY_BOOL(myLOFLOMState)<< " (" << myLOFLOMCount<< ")" << endl;
    theStream   << "ODU     - ODU-TIM                           = " << DISPLAY_BOOL(myTIMState)   << " (" << myTIMCount   << ")" << endl;
    theStream   << "ODU     - ODU-SDBER                         = " << DISPLAY_BOOL(mySdBerState) << " (" << mySdBerCount << ")" << endl;
    theStream   << "ODU     - ODU-SFBER                         = " << DISPLAY_BOOL(mySfBerState) << " (" << mySfBerCount << ")" << endl; 
    theStream   << "ODU     - ODU-LOOMFI                        = " << DISPLAY_BOOL(myLOOMFIState)<< " (" << myLOOMFICount<< ")" << endl; 
    theStream   << "ODU     - ODU-GENERIC AIS                   = " << DISPLAY_BOOL(myGenAISState)       << " (" << myGenAISCount           << ")" << endl << endl;

    // internal defects
    theStream   << "ODU     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "ODU     - INTERNAL UPPER LAYER For MS FAIL (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "ODU     - INTERNAL UPPER LAYER FAIL (NTA)   = " << DISPLAY_BOOL(myUpperLayerInternalFailNTAState) << " (" << myUpperLayerInternalFailNTACount << ")" << endl;
    theStream   << "ODU     - INTERNAL UPPER PROP NEXT LAYER(TA)= " << DISPLAY_BOOL(myUpperLayerInternalFailPNLTAState) << " (" << myUpperLayerInternalFailPNLTACount << ")" << endl;
    theStream   << "ODU     - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockCount << ")" << endl;
    uint16 aInternalBitMask16 = uint16(myInternalLockBitMask);
    theStream   << "ODU     - INTERNAL LOCK BIT MASK            = " << hex << " [0x" << aInternalBitMask16  << "]" << dec << endl;
    theStream   << "ODU     - ODU-INTERNAL AIS                  = " << DISPLAY_BOOL(myInternalAISState)  << " (" << myInternalAISCount      << ")"<< endl;

    theStream   << "ODU     - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;

    theStream   << "ODU     - AIS Fail Layer                    = " << DISPLAY_BOOL(AisFailLayer()) << endl;  
    theStream   << "ODU     - LCK Fail Layer                    = " << DISPLAY_BOOL(LckFailLayer()) << endl;  
    theStream   << "ODU     - OCI Fail Layer                    = " << DISPLAY_BOOL(OciFailLayer()) << endl;  
    theStream   << "ODU     - PLM Fail Layer                    = " << DISPLAY_BOOL(PlmFailLayer()) << endl;  
    theStream   << "ODU     - GENAIS Fail Layer                 = " << DISPLAY_BOOL(GenAisFailLayer()) << endl;  
    theStream   << "ODU     - MFI Fail Layer                    = " << DISPLAY_BOOL(MfiFailLayer()) << endl;  
    theStream   << "ODU     - TIM Fail Layer                    = " << DISPLAY_BOOL(TimFailLayer()) << endl;
    theStream   << "ODU     - INTERNALAIS Fail Layer            = " << DISPLAY_BOOL(InternalAisFailLayer()) << endl;
    theStream   << "ODU     - MSIM Fail Layer                   = " << DISPLAY_BOOL(MsimFailLayer()) << endl;
    theStream   << "ODU     - LOFLOM Fail Layer                 = " << DISPLAY_BOOL(LoflomFailLayer()) << endl;
}
