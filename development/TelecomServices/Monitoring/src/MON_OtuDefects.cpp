// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtuDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"


MON_OtuDefects::MON_OtuDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerForMSFailTAState(false),
    myUpperLayerForMSFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),
    myAISCount(0),
    myAISState(false),
    myTIMCount(0),
    myTIMState(false),
    myLOFCount(0),
    myLOFState(false),
    myLOMFCount(0),
    myLOMFState(false),
    myFECMCount(0),
    myFECMState(false),
    myBDICount(0),
    myBDIState(false),
    mySdBerCount(0),
    mySdBerState(false),
    myDispCompInitCount(0),
    myDispCompInitState(false),
    myIAEState(false),
    myIAECount(0),
    myMateDefectState(false),
    myMateDefectCount(0),
    myLayerFailOnTimEnable(false),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),    
    myUpperLayerInternalFailPNLTAState(false),
    myUpperLayerInternalFailPNLTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_OTU_DEFAULT_BITMASK)
{
}

MON_OtuDefects::~MON_OtuDefects(void )
{
}

void MON_OtuDefects::Reset()
{
    MON_Defects::Reset();
    myUpperLayerFailTAState = false;
    myUpperLayerFailTACount = 0;
    myUpperLayerForMSFailTAState = false;
    myUpperLayerForMSFailTACount = 0;
    myUpperLayerFailNTAState = false;
    myUpperLayerFailNTACount = 0;
    myLockState = false;
    myLockCount = 0;
    myAISCount = 0;
    myAISState = false;
    myTIMCount = 0;
    myTIMState = false;
    myLOFCount = 0;
    myLOFState = false;
    myLOMFCount = 0;
    myLOMFState = false;
    myFECMCount = 0;
    myFECMState = false;
    myBDICount = 0;
    myBDIState = false;
    mySdBerState = false;
    mySdBerCount = 0;
    myDispCompInitState = false;
    myDispCompInitCount = 0;
    myIAEState = false;
    myIAECount = 0;
    myMateDefectState = false;
    myMateDefectCount = 0;
    myLayerFailOnTimEnable = false;
    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;    
    myUpperLayerInternalFailPNLTAState = false;
    myUpperLayerInternalFailPNLTACount = 0;
    myInternalLockState = false;
    myInternalLockLockCount = 0;
    myTermLpbkState = false;
    myTermLpbkCount = 0;
    myDefectFailLayerBitMask = MON_FAILLAYER_OTU_DEFAULT_BITMASK;
}

bool MON_OtuDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myAISState || myLOFState || myLOMFState || myFECMState;
    
    if(myLayerFailOnTimEnable)
        aIsLayerFail |=  myTIMState;

    return aIsLayerFail && IsValidated();
}

bool MON_OtuDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = (myAISState && AisFailLayer()) || 
                        (myLOFState && LofFailLayer()) || 
                        (myLOMFState && LomfFailLayer()) || 
                        (myFECMState && FecmFailLayer() ||
                         myUpperLayerForMSFailTAState);
    
    if(myLayerFailOnTimEnable)
        aIsLayerFail |=  (myTIMState && TimFailLayer());

    return aIsLayerFail && IsValidated();
}

bool MON_OtuDefects::AisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUAIS_BITMASK) == 0 ? false : true;
}

bool MON_OtuDefects::LofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTULOF_BITMASK) == 0 ? false : true;
}

bool MON_OtuDefects::LomfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTULOMF_BITMASK) == 0 ? false : true;
}

bool MON_OtuDefects::FecmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUFECM_BITMASK) == 0 ? false : true;
}

bool MON_OtuDefects::TimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUTIM_BITMASK) == 0 ? false : true;
}

bool MON_OtuDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}

bool MON_OtuDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_OtuDefects::IsLayerInternalInDefects() const
{
    return myUpperLayerInternalFailTAState && IsValidated();
}

bool MON_OtuDefects::IsLayerInternalForMaintSigInDefects() const
{
    return myUpperLayerForMSInternalFailTAState && IsValidated();
}

bool MON_OtuDefects::IsInternalInPropagateNextLayerDefectsTA() const
{
    return myUpperLayerInternalFailPNLTAState && IsValidated();
}

bool MON_OtuDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_OtuDefects::IsLayerInNonPropagateDefectsNTA() const
{
    bool aIsLayerNonPropNTA = false;

    aIsLayerNonPropNTA =  myTIMState;

    return aIsLayerNonPropNTA && IsValidated();
}

bool MON_OtuDefects::IsLayerForMaintSigInNonPropagateDefectsNTA() const
{
    bool aIsLayerNonPropNTA = false;

    aIsLayerNonPropNTA = (myTIMState && TimFailLayer());

    return aIsLayerNonPropNTA && IsValidated();
}

void MON_OtuDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

bool MON_OtuDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}

bool MON_OtuDefects::IsLayerInDegrade() const
{
    return mySdBerState && IsValidated();
}

bool MON_OtuDefects::SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable)
{
    bool hasChanged = false;

    if(myLayerFailOnTimEnable != theLayerFailOnTimEnable)
    {
        myLayerFailOnTimEnable = theLayerFailOnTimEnable;
        hasChanged = true;    
    }

    return hasChanged;
}

bool MON_OtuDefects::IsMateLayerInDefects() const
{
    return myMateDefectState && IsValidated();
}

void MON_OtuDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OTU_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_OTU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSFailTAState;
        *theCount = myUpperLayerForMSFailTACount;
        break;        
    case CT_TEL_OTU_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_OTU_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_OTU_LOF_DEFECT:
        *theState = myLOFState;
        *theCount = myLOFCount;
        break;
    case CT_TEL_OTU_LOMF_DEFECT:
        *theState = myLOMFState;
        *theCount = myLOMFCount;
        break;
    case CT_TEL_OTU_FECM_DEFECT:
        *theState = myFECMState;
        *theCount = myFECMCount;
        break;
    case CT_TEL_OTU_TIM_DEFECT:
        *theState = myTIMState;
        *theCount = myTIMCount;
        break;
    case CT_TEL_OTU_AIS_DEFECT:
        *theState = myAISState;
        *theCount = myAISCount;
        break;
    case CT_TEL_OTU_BDI_DEFECT:
        *theState = myBDIState;
        *theCount = myBDICount;
        break;
    case CT_TEL_OTU_SDBER_DEFECT:
        *theCount = mySdBerCount;
        *theState = mySdBerState;
        break;
    case CT_TEL_OTU_DISP_COMP_INIT:
        *theCount = myDispCompInitCount;
        *theState = myDispCompInitState;
        break;
    case CT_TEL_OTU_IAE_DEFECT:
        *theState = myIAEState;
        *theCount = myIAECount;
        break;
    case CT_TEL_OTU_MATE_DEFECT:
        *theState = myMateDefectState;
        *theCount = myMateDefectCount;
        break;
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break;        
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerInternalFailPNLTAState;
        *theCount = myUpperLayerInternalFailPNLTACount;
        break;
    case CT_TEL_OTU_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    case CT_TEL_OTU_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuDefects: unsupported defect");
    }
}

void MON_OtuDefects::GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const
{
    switch (theDefect)
    {
    case CT_TEL_OTU_TIM_DEFECT:
        //-------------------------------------------------------
        // Use myLayerFailOnTimEnable flag to determine if the 
        // TIM_OTU defect is ServiceAffecting or NSA.
        //-------------------------------------------------------
        if ( theSAFlag ) // Is TIM_OTU ServiceAffecting?
        {
            *theState = (myTIMState && myLayerFailOnTimEnable);
            *theCount = myTIMCount;
        }
        else // Is TIM_OTU NonServiceAffecting?
        {
            *theState = (myTIMState && !myLayerFailOnTimEnable);
            *theCount = myTIMCount;
        }
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuDefects: unsupported defect");
    }
}

bool MON_OtuDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OTU_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_OTU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);
    case CT_TEL_OTU_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_OTU_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_OTU_LOF_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOFState, &myLOFCount);
    case CT_TEL_OTU_LOMF_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOMFState, &myLOMFCount);
    case CT_TEL_OTU_FECM_DEFECT:
        return UpdateDefect(theState, theTransition, &myFECMState, &myFECMCount);
    case CT_TEL_OTU_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myTIMState, &myTIMCount);
    case CT_TEL_OTU_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
    case CT_TEL_OTU_BDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myBDIState, &myBDICount);
    case CT_TEL_OTU_SDBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdBerState, &mySdBerCount);
    case CT_TEL_OTU_DISP_COMP_INIT:
        return UpdateDefect(theState, theTransition, &myDispCompInitState, &myDispCompInitCount);
    case CT_TEL_OTU_IAE_DEFECT:
        return UpdateDefect(theState, theTransition, &myIAEState, &myIAECount);
    case CT_TEL_OTU_MATE_DEFECT:
        return UpdateDefect(theState, theTransition, &myMateDefectState, &myMateDefectCount);
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);
    case CT_TEL_OTU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailPNLTAState, &myUpperLayerInternalFailPNLTACount);
    case CT_TEL_OTU_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    case CT_TEL_OTU_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuDefects: unsupported defect");
        return false;
    }
}


ostream& MON_OtuDefects::WriteObject(ostream& theStream)
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
    theStream << FC_InsertVar(myAISCount);
    theStream << FC_InsertVar(myAISState);
    theStream << FC_InsertVar(myTIMCount);
    theStream << FC_InsertVar(myTIMState);
    theStream << FC_InsertVar(myLOFCount);
    theStream << FC_InsertVar(myLOFState);
    theStream << FC_InsertVar(myFECMCount);
    theStream << FC_InsertVar(myFECMState);
    theStream << FC_InsertVar(myBDICount);
    theStream << FC_InsertVar(myBDIState);
    theStream << FC_InsertVar(mySdBerState);
    theStream << FC_InsertVar(mySdBerCount);
    theStream << FC_InsertVar(myDispCompInitState);
    theStream << FC_InsertVar(myDispCompInitCount);
    theStream << FC_InsertVar(myIAEState);
    theStream << FC_InsertVar(myIAECount);
    theStream << FC_InsertVar(myMateDefectState);
    theStream << FC_InsertVar(myMateDefectCount);
    theStream << FC_InsertVar(myLayerFailOnTimEnable);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTACount);    
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTACount);
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);
    theStream << FC_InsertVar(myTermLpbkState);
    theStream << FC_InsertVar(myTermLpbkCount);
    theStream << FC_InsertVar(myLOMFCount);
    theStream << FC_InsertVar(myLOMFState);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

istream& MON_OtuDefects::ReadObject(istream& theStream)
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
    theStream >> FC_ExtractVar(myAISCount);
    theStream >> FC_ExtractVar(myAISState);
    theStream >> FC_ExtractVar(myTIMCount);
    theStream >> FC_ExtractVar(myTIMState);
    theStream >> FC_ExtractVar(myLOFCount);
    theStream >> FC_ExtractVar(myLOFState);
    theStream >> FC_ExtractVar(myFECMCount);
    theStream >> FC_ExtractVar(myFECMState);
    theStream >> FC_ExtractVar(myBDICount);
    theStream >> FC_ExtractVar(myBDIState);
    theStream >> FC_ExtractVar(mySdBerState);
    theStream >> FC_ExtractVar(mySdBerCount);
    theStream >> FC_ExtractVar(myDispCompInitState);
    theStream >> FC_ExtractVar(myDispCompInitCount);
    theStream >> FC_ExtractVar(myIAEState);
    theStream >> FC_ExtractVar(myIAECount);
    theStream >> FC_ExtractVar(myMateDefectState);
    theStream >> FC_ExtractVar(myMateDefectCount);
    theStream >> FC_ExtractVar(myLayerFailOnTimEnable);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount);    
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);
    theStream >> FC_ExtractVar(myTermLpbkState);
    theStream >> FC_ExtractVar(myTermLpbkCount);
    theStream >> FC_ExtractVar(myLOMFCount);
    theStream >> FC_ExtractVar(myLOMFState);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}

FC_Stream& MON_OtuDefects::WriteObjectBinary(FC_Stream& theStream)
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
    theStream << myAISCount;
    theStream << myAISState;
    theStream << myTIMCount;
    theStream << myTIMState;
    theStream << myLOFCount;
    theStream << myLOFState;
    theStream << myFECMCount;
    theStream << myFECMState;
    theStream << myBDICount;
    theStream << myBDIState;
    theStream << mySdBerState;
    theStream << mySdBerCount;
    theStream << myDispCompInitState;
    theStream << myDispCompInitCount;
    theStream << myIAEState;
    theStream << myIAECount;
    theStream << myMateDefectState;
    theStream << myMateDefectCount;
    theStream << myLayerFailOnTimEnable;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myUpperLayerForMSInternalFailTAState;
    theStream << myUpperLayerForMSInternalFailTACount;    
    theStream << myUpperLayerInternalFailPNLTAState;
    theStream << myUpperLayerInternalFailPNLTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;
    theStream << myTermLpbkState;
    theStream << myTermLpbkCount;
    theStream << myLOMFCount;
    theStream << myLOMFState;
    theStream << myDefectFailLayerBitMask;

    return theStream;
}

FC_Stream& MON_OtuDefects::ReadObjectBinary(FC_Stream& theStream)
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
    theStream >> myAISCount;
    theStream >> myAISState;
    theStream >> myTIMCount;
    theStream >> myTIMState;
    theStream >> myLOFCount;
    theStream >> myLOFState;
    theStream >> myFECMCount;
    theStream >> myFECMState;
    theStream >> myBDICount;
    theStream >> myBDIState;
    theStream >> mySdBerState;
    theStream >> mySdBerCount;
    theStream >> myDispCompInitState;
    theStream >> myDispCompInitCount;
    theStream >> myIAEState;
    theStream >> myIAECount;
    theStream >> myMateDefectState;
    theStream >> myMateDefectCount;
    theStream >> myLayerFailOnTimEnable;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myUpperLayerForMSInternalFailTAState;
    theStream >> myUpperLayerForMSInternalFailTACount;
    theStream >> myUpperLayerInternalFailPNLTAState;
    theStream >> myUpperLayerInternalFailPNLTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;
    theStream >> myTermLpbkState;
    theStream >> myTermLpbkCount;
    theStream >> myLOMFCount;
    theStream >> myLOMFState;
    theStream >> myDefectFailLayerBitMask;
    
    return theStream;
}

void MON_OtuDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OTU     - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "OTU     - UPPER LAYER FOR MS FAIL (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState) << " (" << myUpperLayerForMSFailTACount << ")" << endl;
    theStream   << "OTU     - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "OTU     - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "OTU     - OTU-AIS                           = " << DISPLAY_BOOL(myAISState)  << " (" << myAISCount  << ")"<< endl;
    theStream   << "OTU     - OTU-LOF                           = " << DISPLAY_BOOL(myLOFState)  << " (" << myLOFCount  << ")"<< endl;
    theStream   << "OTU     - OTU-LOMF (loss of multi-frame)    = " << DISPLAY_BOOL(myLOMFState)  << " (" << myLOMFCount  << ")"<< endl;
    theStream   << "OTU     - OTU-FECM                          = " << DISPLAY_BOOL(myFECMState) << " (" << myFECMCount << ")"<< endl;
    theStream   << "OTU     - OTU-TIM                           = " << DISPLAY_BOOL(myTIMState)  << " (" << myTIMCount  << ")"<< endl;
    theStream   << "OTU     - OTU-BDI                           = " << DISPLAY_BOOL(myBDIState)  << " (" << myBDICount  << ")"<< endl << endl;
    theStream   << "OTU     - OTU-SDBER                         = " << DISPLAY_BOOL(mySdBerState) << " (" << mySdBerCount << ")" << endl;
    theStream   << "OTU     - OTU-IAE                           = " << DISPLAY_BOOL(myIAEState)  << " (" << myIAECount  << ")" << endl;
    theStream   << "OTU     - OTU-MATE DEFECT                   = " << DISPLAY_BOOL(myMateDefectState)  << " (" << myMateDefectCount  << ")" << endl;
    theStream   << "OTU     - OTU-DISPERSION COMP INIT          = " << DISPLAY_BOOL(myDispCompInitState) << " (" << myDispCompInitCount << ")" << endl;
    // internal defects
    theStream   << "OTU     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "OTU     - INTERNAL UPPER LAYER FOR MSFAIL (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "OTU     - INTERNAL UPPER PROP NEXT LAYER(TA)= " << DISPLAY_BOOL(myUpperLayerInternalFailPNLTAState) << " (" << myUpperLayerInternalFailPNLTACount << ")" << endl;
    theStream   << "OTU     - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;
    theStream   << "OTU     - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;
    theStream   << "OTU     - AIS Fail Layer                    = " << DISPLAY_BOOL(AisFailLayer()) << endl; 
    theStream   << "OTU     - LOF Fail Layer                    = " << DISPLAY_BOOL(LofFailLayer()) << endl; 
    theStream   << "OTU     - LOMF Fail Layer                   = " << DISPLAY_BOOL(LomfFailLayer()) << endl; 
    theStream   << "OTU     - FECM Fail Layer                   = " << DISPLAY_BOOL(FecmFailLayer()) << endl; 
    theStream   << "OTU     - TIM Fail Layer                    = " << DISPLAY_BOOL(TimFailLayer()) << endl; 
}
