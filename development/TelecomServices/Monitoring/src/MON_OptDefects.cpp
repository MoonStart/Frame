// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OptDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OptDefects::MON_OptDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),
	myLossOfClock(false),
	myLossOfClockCount(0),
	myLossOfLock(false),
	myLossOfLockCount(0),
	myLossOfLight(false),
	myLossOfLightCount(0),
	myPiiLossOfLight(false),
	myPiiLossOfLightCount(0),
    mySdPwrState(false),
	mySdPwrCount(0),
    myMFAState(false),
    myMFACount(0),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),
    myUpperLayerForMSFailTAState(false),
    myUpperLayerForMSFailTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0),
    myUpperLayerInternalFailPNLTAState(false),
    myUpperLayerInternalFailPNLTACount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_OPT_DEFAULT_BITMASK)
{
}

MON_OptDefects::~MON_OptDefects(void )
{
}

void MON_OptDefects::Reset()
{
    MON_Defects::Reset();
    myUpperLayerFailTAState = false;
    myUpperLayerFailTACount = 0;
    myUpperLayerFailNTAState = false;
    myUpperLayerFailNTACount = 0;
    myLockState = false;
    myLockCount = 0;
	myLossOfClock = false;
	myLossOfClockCount = 0;
	myLossOfLock = false;
	myLossOfLockCount = 0;
	myLossOfLight = false;
	myLossOfLightCount = 0;
	myPiiLossOfLight = false;
	myPiiLossOfLightCount = 0;
    mySdPwrState = false;
	mySdPwrCount = 0;
    myMFAState = false;
    myMFACount = 0;
    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;    
    myUpperLayerForMSFailTAState = false;
    myUpperLayerForMSFailTACount = 0;
    myInternalLockState = false;
    myInternalLockLockCount = 0;
    myUpperLayerInternalFailPNLTAState = false;
    myUpperLayerInternalFailPNLTACount = 0;
    myTermLpbkState = false;
    myTermLpbkCount = 0;
    myDefectFailLayerBitMask = MON_FAILLAYER_OPT_DEFAULT_BITMASK;
}

bool MON_OptDefects::IsLayerInDefects() const
{
    // dont' fail the layer if terminal loopback is active
    // in order to avoid propagation of defect and wrongfull AIS generation
    return (( myLossOfLight) && IsValidated());
}

bool MON_OptDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = (myLossOfLight && LosFailLayer()) || 
                         myUpperLayerForMSFailTAState;

    return aIsLayerFail && IsValidated();
}

bool MON_OptDefects::LosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OPTLOS_BITMASK) == 0 ? false : true;
}

void MON_OptDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

bool MON_OptDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}

bool MON_OptDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_OptDefects::IsLayerInternalInDefects() const
{
    return myUpperLayerInternalFailTAState && IsValidated();
}

bool MON_OptDefects::IsLayerInternalForMaintSigInDefects() const
{
    return myUpperLayerForMSInternalFailTAState && IsValidated();
}

bool MON_OptDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_OptDefects::IsInternalInPropagateNextLayerDefectsTA() const
{
    return myUpperLayerInternalFailPNLTAState && IsValidated();
}

bool MON_OptDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}

void MON_OptDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_OPT_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_OPT_LOSS_CLK_DEFECT:
        *theState = myLossOfClock;
        *theCount = myLossOfClockCount;
        break;
    case CT_TEL_OPT_LOSS_LOCK_DEFECT:
        *theState = myLossOfLock;
        *theCount = myLossOfLockCount;
        break;
    case CT_TEL_OPT_LOSS_LIGHT_DEFECT:
        *theState = myLossOfLight;
        *theCount = myLossOfLightCount;
        break;
    case CT_TEL_PII_OPT_LOSS_LIGHT_DEFECT:
        *theState = myPiiLossOfLight;
        *theCount = myPiiLossOfLightCount;
        break;
    case CT_TEL_OPT_SDPWR_DEFECT:
        *theState = mySdPwrState;
        *theCount = mySdPwrCount;
        break;
    case CT_TEL_OPT_MISMATCH_FACILITY_DEFECT:
        *theState = myMFAState;
        *theCount = myMFACount;
        break;
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break;
    case CT_TEL_OPT_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSFailTAState;
        *theCount = myUpperLayerForMSFailTACount;
        break;
    case CT_TEL_OPT_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        *theState = myUpperLayerInternalFailPNLTAState;
        *theCount = myUpperLayerInternalFailPNLTACount;
        break;
    case CT_TEL_OPT_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OptDefects: unsupported defect");
    }
}

    
bool MON_OptDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_OPT_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_OPT_LOSS_CLK_DEFECT:
        return UpdateDefect(theState, theTransition, &myLossOfClock, &myLossOfClockCount);
    case CT_TEL_OPT_LOSS_LOCK_DEFECT:
        return UpdateDefect(theState, theTransition, &myLossOfLock, &myLossOfLockCount);
    case CT_TEL_OPT_LOSS_LIGHT_DEFECT:
        return UpdateDefect(theState, theTransition, &myLossOfLight, &myLossOfLightCount);
    case CT_TEL_PII_OPT_LOSS_LIGHT_DEFECT:
        return UpdateDefect(theState, theTransition, &myPiiLossOfLight, &myPiiLossOfLightCount);
    case CT_TEL_OPT_SDPWR_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdPwrState, &mySdPwrCount);
    case CT_TEL_OPT_MISMATCH_FACILITY_DEFECT:
        return UpdateDefect(theState, theTransition, &myMFAState, &myMFACount);
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);
    case CT_TEL_OPT_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);
    case CT_TEL_OPT_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    case CT_TEL_OPT_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailPNLTAState, &myUpperLayerInternalFailPNLTACount);
    case CT_TEL_OPT_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OptDefects: unsupported defect");
        return false;
    }
}

ostream& MON_OptDefects::WriteObject(ostream& theStream)
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerFailTAState);
    theStream << FC_InsertVar(myUpperLayerFailTACount);
    theStream << FC_InsertVar(myUpperLayerFailNTAState);
    theStream << FC_InsertVar(myUpperLayerFailNTACount);
    theStream << FC_InsertVar(myLockState);
    theStream << FC_InsertVar(myLockCount);
    theStream << FC_InsertVar(myLossOfClock);
    theStream << FC_InsertVar(myLossOfClockCount);
    theStream << FC_InsertVar(myLossOfLock);
    theStream << FC_InsertVar(myLossOfLockCount);
    theStream << FC_InsertVar(myLossOfLight);
    theStream << FC_InsertVar(myLossOfLightCount);
    theStream << FC_InsertVar(myPiiLossOfLight);
    theStream << FC_InsertVar(myPiiLossOfLightCount);
    theStream << FC_InsertVar(mySdPwrState);
    theStream << FC_InsertVar(mySdPwrCount);
    theStream << FC_InsertVar(myMFAState);
    theStream << FC_InsertVar(myMFACount);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTACount);    
    theStream << FC_InsertVar(myUpperLayerForMSFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSFailTACount); 
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailPNLTACount);
    theStream << FC_InsertVar(myTermLpbkState);
    theStream << FC_InsertVar(myTermLpbkCount);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);
    
    return theStream;
}

istream& MON_OptDefects::ReadObject(istream& theStream)
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLockCount);
    theStream >> FC_ExtractVar(myLossOfClock);
    theStream >> FC_ExtractVar(myLossOfClockCount);
    theStream >> FC_ExtractVar(myLossOfLock);
    theStream >> FC_ExtractVar(myLossOfLockCount);
    theStream >> FC_ExtractVar(myLossOfLight);
    theStream >> FC_ExtractVar(myLossOfLightCount);
    theStream >> FC_ExtractVar(myPiiLossOfLight);
    theStream >> FC_ExtractVar(myPiiLossOfLightCount);
    theStream >> FC_ExtractVar(mySdPwrState);
    theStream >> FC_ExtractVar(mySdPwrCount);
    theStream >> FC_ExtractVar(myMFAState);
    theStream >> FC_ExtractVar(myMFACount);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount); 
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSFailTACount);    
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailPNLTACount);
    theStream >> FC_ExtractVar(myTermLpbkState);
    theStream >> FC_ExtractVar(myTermLpbkCount);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);
    
    return theStream;
}

FC_Stream& MON_OptDefects::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerFailTAState;
    theStream << myUpperLayerFailTACount;
    theStream << myUpperLayerFailNTAState;
    theStream << myUpperLayerFailNTACount;
    theStream << myLockState;
    theStream << myLockCount;
    theStream << myLossOfClock;
    theStream << myLossOfClockCount;
    theStream << myLossOfLock;
    theStream << myLossOfLockCount;
    theStream << myLossOfLight;
    theStream << myLossOfLightCount;
    theStream << myPiiLossOfLight;
    theStream << myPiiLossOfLightCount;
    theStream << mySdPwrState;
    theStream << mySdPwrCount;
    theStream << myMFAState;
    theStream << myMFACount;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myUpperLayerForMSInternalFailTAState;
    theStream << myUpperLayerForMSInternalFailTACount;
    theStream << myUpperLayerForMSFailTAState;
    theStream << myUpperLayerForMSFailTACount; 
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;
    theStream << myUpperLayerInternalFailPNLTAState;
    theStream << myUpperLayerInternalFailPNLTACount;
    theStream << myTermLpbkState;
    theStream << myTermLpbkCount;
    theStream << myDefectFailLayerBitMask;

    return theStream;
}

FC_Stream& MON_OptDefects::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerFailTAState;
    theStream >> myUpperLayerFailTACount;
    theStream >> myUpperLayerFailNTAState;
    theStream >> myUpperLayerFailNTACount;
    theStream >> myLockState;
    theStream >> myLockCount;
    theStream >> myLossOfClock;
    theStream >> myLossOfClockCount;
    theStream >> myLossOfLock;
    theStream >> myLossOfLockCount;
    theStream >> myLossOfLight;
    theStream >> myLossOfLightCount;
    theStream >> myPiiLossOfLight;
    theStream >> myPiiLossOfLightCount;
    theStream >> mySdPwrState;
    theStream >> mySdPwrCount;
    theStream >> myMFAState;
    theStream >> myMFACount;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myUpperLayerForMSInternalFailTAState;
    theStream >> myUpperLayerForMSInternalFailTACount;
    theStream >> myUpperLayerForMSFailTAState;
    theStream >> myUpperLayerForMSFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;
    theStream >> myUpperLayerInternalFailPNLTAState;
    theStream >> myUpperLayerInternalFailPNLTACount;
    theStream >> myTermLpbkState;
    theStream >> myTermLpbkCount;
    theStream >> myDefectFailLayerBitMask;

    return theStream;
}

void MON_OptDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OPT     - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "OPT     - UPPER LAYER FAIL FOR MS (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState) << " (" << myUpperLayerForMSFailTACount << ")" << endl;
    theStream   << "OPT     - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "OPT     - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "OPT     - LOS OF LIGHT                      = " << DISPLAY_BOOL(myLossOfLight) << " (" << myLossOfLightCount << ")"<< endl;
    theStream   << "OPT     - (PII) LOS OF LIGHT                = " << DISPLAY_BOOL(myPiiLossOfLight) << " (" << myPiiLossOfLightCount << ")"<< endl;
    theStream   << "OPT     - LOSS OF CLK                       = " << DISPLAY_BOOL(myLossOfClock) << " (" << myLossOfClockCount << ")" << endl;
    theStream   << "OPT     - LOSS OF LOCK                      = " << DISPLAY_BOOL(myLossOfLock) << " (" << myLossOfLockCount << ")" << endl;
    theStream   << "OPT     - SIGNAL DEGRADE POWER (SDPWR)      = " << DISPLAY_BOOL(mySdPwrState) << " (" << mySdPwrCount << ")" << endl;
    theStream   << "OPT     - MFA                               = " << DISPLAY_BOOL(myMFAState) << " (" << myMFACount << ")" << endl << endl;
    // internal defects
    theStream   << "OPT     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "OPT     - INTERNAL UPPER LAYER FAIL FOR MS (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "OPT     - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;
    theStream   << "OPT     - INTERNAL UL PROP NEXT LAYER (TA)  = " << DISPLAY_BOOL(myUpperLayerInternalFailPNLTAState) << " (" << myUpperLayerInternalFailPNLTACount << ")" << endl;
    theStream   << "OPT     - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;
    theStream   << "OPT     - LOS Fail Layer                    = " << DISPLAY_BOOL(LosFailLayer()) << endl; 
}

