// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TcmDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_TcmDefects::MON_TcmDefects(uint32 theIndex):
    MON_Defects(theIndex),    
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myUpperLayerFailPNLTAState(false),
    myUpperLayerFailPNLTACount(0),
    myLockState(false),
    myLockCount(0),
    myLTCState(false),
    myLTCCount(0),
    myAISState(false),
    myAISCount(0),
    myLCKState(false),
    myLCKCount(0),
    myOCIState(false),
    myOCICount(0),
    myTIMState(false),
    myTIMCount(0),
    mySdBerState(false), 
    mySdBerCount(0),    
    myBDIState(false),
    myBDICount(0),
    myIAEState(false),
    myIAECount(0),
    myBIAEState(false),
    myBIAECount(0),
    myLayerFailOnTimEnable(false),
    myLayerFailOnLtcEnable(false),
    mySnkOnlyModeState(false),
    mySnkOnlyModeCount(0),
    mySrcOnlyModeState(false),
    mySrcOnlyModeCount(0),
    myNimModeState(false),
    myNimModeCount(0),
    myLockBitMask(0),
    myInternalLockBitMask(0),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerInternalFailPNLTAState(false),
    myUpperLayerInternalFailPNLTACount(0),
    myUpperLayerDegradeState(false),
    myUpperLayerDegradeCount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0)
{
}

MON_TcmDefects::~MON_TcmDefects()
{
}


void MON_TcmDefects::Reset(void)
{
    // Initialize all attributes to zero
    MON_Defects::Reset();
    
    myUpperLayerFailTAState    = false;
    myUpperLayerFailTACount    = 0;
    myUpperLayerFailNTAState   = false;
    myUpperLayerFailNTACount   = 0;
    myUpperLayerFailPNLTAState = false;
    myUpperLayerFailPNLTACount = 0;
    myLockState            = false;
    myLockCount            = 0;
    myLTCState             = false;
    myLTCCount             = 0;
    myAISState             = false;
    myAISCount             = 0;
    myLCKState             = false;
    myLCKCount             = 0;
    myOCIState             = false;
    myOCICount             = 0;
    myTIMState             = false;
    myTIMCount             = 0;
    mySdBerState           = false;
    mySdBerCount           = 0;
    myBDIState             = false;
    myBDICount             = 0;
    myIAEState             = false;
    myIAECount             = 0;
    myBIAEState            = false;
    myBIAECount            = 0;
    myLayerFailOnTimEnable = false;
    myLayerFailOnLtcEnable = false;
    mySnkOnlyModeState     = false;
    mySnkOnlyModeCount     = 0;
    mySrcOnlyModeState     = false;
    mySrcOnlyModeCount     = 0;
    myNimModeState         = false;
    myNimModeCount         = 0;

    myLockBitMask          = 0;
    myInternalLockBitMask  = 0;

    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerInternalFailPNLTAState = false;
    myUpperLayerInternalFailPNLTACount = 0;

    myUpperLayerDegradeState = false;
    myUpperLayerDegradeCount = 0;

    myTermLpbkState = false;
    myTermLpbkCount = 0;
}

bool MON_TcmDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = false;

    aIsLayerFail = myLCKState||myOCIState||myUpperLayerFailTAState;

    if(myLayerFailOnTimEnable)
            aIsLayerFail |= myTIMState;

    if(myLayerFailOnLtcEnable)
            aIsLayerFail |= myLTCState;

    return aIsLayerFail && IsValidated();
}

bool MON_TcmDefects::IsLayerForMaintSigInDefects() const
{
    return IsLayerInDefects();
}

// new added begin.
bool MON_TcmDefects::IsInPropagateNextLayerDefectsTA() const
{
    bool aPropagateNextLayerDefectsTA = false;

    aPropagateNextLayerDefectsTA = myAISState||myUpperLayerFailPNLTAState;

    return aPropagateNextLayerDefectsTA && IsValidated();
}

bool MON_TcmDefects::IsLayerInDefectsNTA() const
{
    bool aIsLayerFailNTA = false;

    // consider only upper layer defects
    aIsLayerFailNTA = myUpperLayerFailNTAState;

    return aIsLayerFailNTA && IsValidated();
}


bool MON_TcmDefects::IsLayerInNonPropagateDefectsNTA() const
{
    bool aIsLayerNonPropNTA = false;

    aIsLayerNonPropNTA =  myTIMState;

    return aIsLayerNonPropNTA && IsValidated();
}


bool MON_TcmDefects::IsIgnoreDirectUpperLayerDefects() const
{
    bool aIsIgnore = false;

    aIsIgnore =  mySrcOnlyModeState || myNimModeState;

    return aIsIgnore && IsValidated();
}
// new added end.

bool MON_TcmDefects::IsServerLayerFailed() const
{
    return myUpperLayerFailTAState && IsValidated();
}


bool MON_TcmDefects::IsLayerInternalInDefects() const
{
    return myUpperLayerInternalFailTAState && IsValidated();
}

bool MON_TcmDefects::IsInternalInPropagateNextLayerDefectsTA() const
{
    return myUpperLayerInternalFailPNLTAState && IsValidated();
}


bool MON_TcmDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_TcmDefects::IsLayerInDegrade() const
{
    return (mySdBerState || myUpperLayerDegradeState) && IsValidated();
}

bool MON_TcmDefects::SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable)
{
    bool hasChanged = false;

    if(myLayerFailOnTimEnable != theLayerFailOnTimEnable)
    {
        myLayerFailOnTimEnable = theLayerFailOnTimEnable;
        hasChanged = true;    
    }

    return hasChanged;
}

bool MON_TcmDefects::SetLayerFailOnLtcEnable(bool theLayerFailOnLtcEnable)
{
    bool hasChanged = false;

    if(myLayerFailOnLtcEnable != theLayerFailOnLtcEnable)
    {
        myLayerFailOnLtcEnable = theLayerFailOnLtcEnable;
        hasChanged = true;    
    }

    return hasChanged;
}

bool MON_TcmDefects::SetLockBitMask(uint8 theBitMask)
{
    bool hasChanged = false;

    if(myLockBitMask != theBitMask)
    {
        myLockBitMask = theBitMask;
        hasChanged = true;    
    }

    return hasChanged;
}

uint8 MON_TcmDefects::GetLockBitMask() const
{
    return myLockBitMask;
}

bool MON_TcmDefects::SetInternalLockBitMask(uint8 theBitMask)
{
    bool hasChanged = false;

    if(myInternalLockBitMask != theBitMask)
    {
        myInternalLockBitMask = theBitMask;
        hasChanged = true;    
    }

    return hasChanged;
}

uint8 MON_TcmDefects::GetInternalLockBitMask() const
{
    return myInternalLockBitMask;
}


bool MON_TcmDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}


void MON_TcmDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerFailPNLTAState;
        *theCount = myUpperLayerFailPNLTACount;
        break;
    case CT_TEL_TCM_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_TCM_LTC_DEFECT:
        *theState = myLTCState;
        *theCount = myLTCCount;
        break;
    case CT_TEL_TCM_AIS_DEFECT:
        *theState = myAISState;
        *theCount = myAISCount;
        break;
    case CT_TEL_TCM_LCK_DEFECT:
        *theState = myLCKState;
        *theCount = myLCKCount;
        break;
    case CT_TEL_TCM_OCI_DEFECT:
        *theState = myOCIState;
        *theCount = myOCICount;
        break;
    case CT_TEL_TCM_TIM_DEFECT:
        *theState = myTIMState;
        *theCount = myTIMCount;
        break;
    case CT_TEL_TCM_SDBER_DEFECT:
        *theCount = mySdBerCount;
        *theState = mySdBerState;
        break;
    case CT_TEL_TCM_BDI_DEFECT:
        *theState = myBDIState;
        *theCount = myBDICount;
        break;
    case CT_TEL_TCM_IAE_DEFECT:
        *theState = myIAEState;
        *theCount = myIAECount;
        break;
    case CT_TEL_TCM_BIAE_DEFECT:
        *theState = myBIAEState;
        *theCount = myBIAECount;
        break;
    case CT_TEL_TCM_SNK_MODE_DEFECT:
        *theState = mySnkOnlyModeState;
        *theCount = mySnkOnlyModeCount;
        break;
    case CT_TEL_TCM_SRC_MODE_DEFECT:
        *theState = mySrcOnlyModeState;
        *theCount = mySrcOnlyModeCount;
        break;
    case CT_TEL_TCM_NIM_MODE_DEFECT:
        *theState = myNimModeState;
        *theCount = myNimModeCount;
        break;
    case CT_TEL_TCM_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_TCM_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerInternalFailPNLTAState;
        *theCount = myUpperLayerInternalFailPNLTACount;
        break;
    case CT_TEL_TCM_UPPER_LAYER_DEGRADE_DEFECT:
        *theState = myUpperLayerDegradeState;
        *theCount = myUpperLayerDegradeCount;
        break;
    case CT_TEL_TCM_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;

    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmDefects: unsupported defect");
    }
}

void MON_TcmDefects::GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const
{
    switch (theDefect)
    {
    case CT_TEL_TCM_TIM_DEFECT:
        //-------------------------------------------------------
        // Use myLayerFailOnTimEnable flag to determine if the 
        // TIM_TCM defect is ServiceAffecting or NSA.
        //-------------------------------------------------------
        if ( theSAFlag ) // Is TIM_TCM ServiceAffecting?
        {
            *theState = (myTIMState && myLayerFailOnTimEnable && !myNimModeState);
            *theCount = myTIMCount;
        }
        else // Is TIM_TCM NonServiceAffecting?
        {
            *theState = (myTIMState && (!myLayerFailOnTimEnable || myNimModeState));
            *theCount = myTIMCount;
        }
        break;
    case CT_TEL_TCM_LTC_DEFECT:
        if ( theSAFlag ) // Is LTC_TCM ServiceAffecting?
        {
            *theState = (myLTCState && myLayerFailOnLtcEnable);
            *theCount = myLTCCount;
        }
        else // Is LTC_TCM NonServiceAffecting?
        {
            *theState = (myLTCState && !myLayerFailOnLtcEnable);
            *theCount = myLTCCount;
        }
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmDefects: unsupported defect");
    }
}

bool MON_TcmDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailPNLTAState, &myUpperLayerFailPNLTACount);
    case CT_TEL_TCM_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_TCM_LTC_DEFECT:
        return UpdateDefect(theState, theTransition, &myLTCState, &myLTCCount);
    case CT_TEL_TCM_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
    case CT_TEL_TCM_LCK_DEFECT:
        return UpdateDefect(theState, theTransition, &myLCKState, &myLCKCount);
    case CT_TEL_TCM_OCI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOCIState, &myOCICount);
    case CT_TEL_TCM_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myTIMState, &myTIMCount);
    case CT_TEL_TCM_SDBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdBerState, &mySdBerCount);
    case CT_TEL_TCM_BDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myBDIState, &myBDICount);
    case CT_TEL_TCM_IAE_DEFECT:
        return UpdateDefect(theState, theTransition, &myIAEState, &myIAECount);
    case CT_TEL_TCM_BIAE_DEFECT:
        return UpdateDefect(theState, theTransition, &myBIAEState, &myBIAECount);
    case CT_TEL_TCM_SNK_MODE_DEFECT:
        return UpdateDefect(theState, theTransition, &mySnkOnlyModeState, &mySnkOnlyModeCount);
    case CT_TEL_TCM_SRC_MODE_DEFECT:
        return UpdateDefect(theState, theTransition, &mySrcOnlyModeState, &mySrcOnlyModeCount);
    case CT_TEL_TCM_NIM_MODE_DEFECT:
        return UpdateDefect(theState, theTransition, &myNimModeState, &myNimModeCount);
    case CT_TEL_TCM_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_TCM_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailPNLTAState, &myUpperLayerInternalFailPNLTACount);
    case CT_TEL_TCM_UPPER_LAYER_DEGRADE_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerDegradeState, &myUpperLayerDegradeCount);
    case CT_TEL_TCM_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);

    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmDefects: unsupported defect");
        return false;
    } 
}

bool MON_TcmDefects::IsOtuLayerLocked(uint8 theBitMask) const
{
    // Otu layer is the high order bit
    uint8 aCheckMask = 0x80;

    // And check mask with the passed in bit mask and return true/false
    return((theBitMask & aCheckMask)==aCheckMask);
}

ostream& MON_TcmDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myUpperLayerFailTAState);
    theStream   << FC_InsertVar(myUpperLayerFailTACount);
    theStream   << FC_InsertVar(myUpperLayerFailNTAState);
    theStream   << FC_InsertVar(myUpperLayerFailNTACount);
    theStream   << FC_InsertVar(myUpperLayerFailPNLTAState);
    theStream   << FC_InsertVar(myUpperLayerFailPNLTACount);
    theStream   << FC_InsertVar(myLockState);
    theStream   << FC_InsertVar(myLockCount);
    theStream   << FC_InsertVar(myLTCState);
    theStream   << FC_InsertVar(myLTCCount);
    theStream   << FC_InsertVar(myAISState);
    theStream   << FC_InsertVar(myAISCount);
    theStream   << FC_InsertVar(myLCKState);
    theStream   << FC_InsertVar(myLCKCount);
    theStream   << FC_InsertVar(myOCIState);
    theStream   << FC_InsertVar(myOCICount);
    theStream   << FC_InsertVar(myTIMState);
    theStream   << FC_InsertVar(myTIMCount);
    theStream   << FC_InsertVar(mySdBerState);
    theStream   << FC_InsertVar(mySdBerCount); 
    theStream   << FC_InsertVar(myBDIState);
    theStream   << FC_InsertVar(myBDICount);
    theStream   << FC_InsertVar(myIAEState);
    theStream   << FC_InsertVar(myIAECount);
    theStream   << FC_InsertVar(myBIAEState);
    theStream   << FC_InsertVar(myBIAECount);
    theStream   << FC_InsertVar(myLayerFailOnTimEnable);
    theStream   << FC_InsertVar(myLayerFailOnLtcEnable);
    theStream   << FC_InsertVar(mySnkOnlyModeState);
    theStream   << FC_InsertVar(mySnkOnlyModeCount);
    theStream   << FC_InsertVar(mySrcOnlyModeState);
    theStream   << FC_InsertVar(mySrcOnlyModeCount);
    theStream   << FC_InsertVar(myNimModeState);
    theStream   << FC_InsertVar(myNimModeCount);

    theStream   << FC_InsertVar(myLockBitMask);
    theStream   << FC_InsertVar(myInternalLockBitMask);

    theStream   << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream   << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream   << FC_InsertVar(myUpperLayerInternalFailPNLTAState);
    theStream   << FC_InsertVar(myUpperLayerInternalFailPNLTACount);

    theStream   << FC_InsertVar(myUpperLayerDegradeState);
    theStream   << FC_InsertVar(myUpperLayerDegradeCount);

    theStream   << FC_InsertVar(myTermLpbkState);
    theStream   << FC_InsertVar(myTermLpbkCount);
    return theStream;
}

istream& MON_TcmDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream   >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream   >> FC_ExtractVar(myUpperLayerFailPNLTAState);
    theStream   >> FC_ExtractVar(myUpperLayerFailPNLTACount);
    theStream   >> FC_ExtractVar(myLockState);
    theStream   >> FC_ExtractVar(myLockCount);
    theStream   >> FC_ExtractVar(myLTCState);
    theStream   >> FC_ExtractVar(myLTCCount);
    theStream   >> FC_ExtractVar(myAISState);
    theStream   >> FC_ExtractVar(myAISCount);
    theStream   >> FC_ExtractVar(myLCKState);
    theStream   >> FC_ExtractVar(myLCKCount);
    theStream   >> FC_ExtractVar(myOCIState);
    theStream   >> FC_ExtractVar(myOCICount);
    theStream   >> FC_ExtractVar(myTIMState);
    theStream   >> FC_ExtractVar(myTIMCount);
    theStream   >> FC_ExtractVar(mySdBerState);
    theStream   >> FC_ExtractVar(mySdBerCount);    
    theStream   >> FC_ExtractVar(myBDIState);
    theStream   >> FC_ExtractVar(myBDICount);
    theStream   >> FC_ExtractVar(myIAEState);
    theStream   >> FC_ExtractVar(myIAECount);
    theStream   >> FC_ExtractVar(myBIAEState);
    theStream   >> FC_ExtractVar(myBIAECount);    
    theStream   >> FC_ExtractVar(myLayerFailOnTimEnable);
    theStream   >> FC_ExtractVar(myLayerFailOnLtcEnable);        
    theStream   >> FC_ExtractVar(mySnkOnlyModeState);    
    theStream   >> FC_ExtractVar(mySnkOnlyModeCount);
    theStream   >> FC_ExtractVar(mySrcOnlyModeState);    
    theStream   >> FC_ExtractVar(mySrcOnlyModeCount);
    theStream   >> FC_ExtractVar(myNimModeState);    
    theStream   >> FC_ExtractVar(myNimModeCount);

    theStream   >> FC_ExtractVar(myLockBitMask);
    theStream   >> FC_ExtractVar(myInternalLockBitMask);

    theStream   >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailPNLTAState);
    theStream   >> FC_ExtractVar(myUpperLayerInternalFailPNLTACount);

    theStream   >> FC_ExtractVar(myUpperLayerDegradeState);
    theStream   >> FC_ExtractVar(myUpperLayerDegradeCount);

    theStream   >> FC_ExtractVar(myTermLpbkState);
    theStream   >> FC_ExtractVar(myTermLpbkCount);

    return theStream;
}

FC_Stream& MON_TcmDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);

    theStream   << myUpperLayerFailTAState;
    theStream   << myUpperLayerFailTACount;
    theStream   << myUpperLayerFailNTAState;
    theStream   << myUpperLayerFailNTACount;
    theStream   << myUpperLayerFailPNLTAState;
    theStream   << myUpperLayerFailPNLTACount;
    theStream   << myLockState;
    theStream   << myLockCount;
    theStream   << myLTCState;
    theStream   << myLTCCount;
    theStream   << myAISState;
    theStream   << myAISCount;
    theStream   << myLCKState;
    theStream   << myLCKCount;
    theStream   << myOCIState;
    theStream   << myOCICount;    
    theStream   << myTIMState;
    theStream   << myTIMCount;
    theStream   << mySdBerState;
    theStream   << mySdBerCount;    
    theStream   << myBDIState;
    theStream   << myBDICount;    
    theStream   << myIAEState;
    theStream   << myIAECount;
    theStream   << myBIAEState;
    theStream   << myBIAECount;
    theStream   << myLayerFailOnTimEnable;
    theStream   << myLayerFailOnLtcEnable;
    theStream   << mySnkOnlyModeState;
    theStream   << mySnkOnlyModeCount;
    theStream   << mySrcOnlyModeState;
    theStream   << mySrcOnlyModeCount;
    theStream   << myNimModeState;
    theStream   << myNimModeCount;

    theStream   << myLockBitMask;
    theStream   << myInternalLockBitMask;

    theStream   << myUpperLayerInternalFailTAState;
    theStream   << myUpperLayerInternalFailTACount;
    theStream   << myUpperLayerInternalFailPNLTAState;
    theStream   << myUpperLayerInternalFailPNLTACount;

    theStream   << myUpperLayerDegradeState;
    theStream   << myUpperLayerDegradeCount;
    
    theStream   << myTermLpbkState;
    theStream   << myTermLpbkCount;

    return theStream;
}

FC_Stream& MON_TcmDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myUpperLayerFailTAState;
    theStream   >> myUpperLayerFailTACount;
    theStream   >> myUpperLayerFailNTAState;
    theStream   >> myUpperLayerFailNTACount;
    theStream   >> myUpperLayerFailPNLTAState;
    theStream   >> myUpperLayerFailPNLTACount;
    theStream   >> myLockState;
    theStream   >> myLockCount;
    theStream   >> myLTCState;
    theStream   >> myLTCCount;
    theStream   >> myAISState;
    theStream   >> myAISCount;
    theStream   >> myLCKState;
    theStream   >> myLCKCount;
    theStream   >> myOCIState;
    theStream   >> myOCICount;
    theStream   >> myTIMState;
    theStream   >> myTIMCount;
    theStream   >> mySdBerState;
    theStream   >> mySdBerCount;   
    theStream   >> myBDIState;
    theStream   >> myBDICount;
    theStream   >> myIAEState;
    theStream   >> myIAECount;
    theStream   >> myBIAEState;
    theStream   >> myBIAECount;
    theStream   >> myLayerFailOnTimEnable;
    theStream   >> myLayerFailOnLtcEnable;
    theStream   >> mySnkOnlyModeState;
    theStream   >> mySnkOnlyModeCount;
    theStream   >> mySrcOnlyModeState;
    theStream   >> mySrcOnlyModeCount;
    theStream   >> myNimModeState;
    theStream   >> myNimModeCount;

    theStream   >> myLockBitMask;
    theStream   >> myInternalLockBitMask;
    
    theStream   >> myUpperLayerInternalFailTAState;
    theStream   >> myUpperLayerInternalFailTACount;
    theStream   >> myUpperLayerInternalFailPNLTAState;
    theStream   >> myUpperLayerInternalFailPNLTACount;

    theStream   >> myUpperLayerDegradeState;
    theStream   >> myUpperLayerDegradeCount;

    theStream   >> myTermLpbkState;
    theStream   >> myTermLpbkCount;

    return theStream;
}

void MON_TcmDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "TCM     - SERVER LAYER FAIL(TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState)  << " (" << myUpperLayerFailTACount  << ")" << endl;
    theStream   << "TCM     - SERVER LAYER FAIL(NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount  << ")" << endl;
    theStream   << "TCM     - SERVER LAYER DEGRADE              = " << DISPLAY_BOOL(myUpperLayerDegradeState) << " (" << myUpperLayerDegradeCount  << ")" << endl;
    theStream   << "TCM     - SERVER LAYER PROP NEXT LAYER(TA)  = " << DISPLAY_BOOL(myUpperLayerFailPNLTAState) << " (" << myUpperLayerFailPNLTACount  << ")" << endl;
    theStream   << "TCM     - LOCK STATE                        = " << DISPLAY_BOOL(myLockState)  << " (" << myLockCount  << ")" << endl;
    theStream   << "TCM     - TCM-LTC                           = " << DISPLAY_BOOL(myLTCState)   << " (" << myLTCCount   << ")" << endl;
    theStream   << "TCM     - TCM-AIS                           = " << DISPLAY_BOOL(myAISState)   << " (" << myAISCount   << ")" << endl;
    theStream   << "TCM     - TCM-LCK                           = " << DISPLAY_BOOL(myLCKState)   << " (" << myLCKCount   << ")" << endl;
    theStream   << "TCM     - TCM-OCI                           = " << DISPLAY_BOOL(myOCIState)   << " (" << myOCICount   << ")" << endl;
    theStream   << "TCM     - TCM-TIM                           = " << DISPLAY_BOOL(myTIMState)   << " (" << myTIMCount   << ")" << endl;
    theStream   << "TCM     - TCM-SDBER                         = " << DISPLAY_BOOL(mySdBerState) << " (" << mySdBerCount << ")" << endl;
    theStream   << "TCM     - TCM-BDI                           = " << DISPLAY_BOOL(myBDIState)   << " (" << myBDICount   << ")" << endl;
    theStream   << "TCM     - TCM-IAE                           = " << DISPLAY_BOOL(myIAEState)   << " (" << myIAECount   << ")" << endl;
    theStream   << "TCM     - TCM-BIAE                          = " << DISPLAY_BOOL(myBIAEState)  << " (" << myBIAECount  << ")" << endl;
    theStream   << "TCM     - TCM-Layer Fail on TIM Enable      = " << DISPLAY_BOOL(myLayerFailOnTimEnable) << endl;
    theStream   << "TCM     - TCM-Layer Fail on LTC Enable      = " << DISPLAY_BOOL(myLayerFailOnLtcEnable) << endl;
    theStream   << "TCM     - TCM-Snk Mode                      = " << DISPLAY_BOOL(mySnkOnlyModeState)  << " (" << mySnkOnlyModeCount  << ")" << endl;
    theStream   << "TCM     - TCM-Src Mode                      = " << DISPLAY_BOOL(mySrcOnlyModeState)  << " (" << mySrcOnlyModeCount  << ")" << endl;
    theStream   << "TCM     - TCM-Nim Mode                      = " << DISPLAY_BOOL(myNimModeState)  << " (" << myNimModeCount  << ")" << endl;

    theStream   << "TCM     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "TCM     - INTERNAL UPPER PROP NEXT LAYER(TA)= " << DISPLAY_BOOL(myUpperLayerInternalFailPNLTAState) << " (" << myUpperLayerInternalFailPNLTACount << ")" << endl;
    uint16 aBitMask16 = myLockBitMask;
    theStream   << "TCM     - Lock Bit Mask                     = 0x" << hex << aBitMask16 << endl;
    uint16 aInternalBitMask16 = myInternalLockBitMask;
    theStream   << "TCM     - Internal Lock Bit Mask            = 0x" << hex << aInternalBitMask16 << dec << endl;

    theStream   << "TCM     - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;
}

