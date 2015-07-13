// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)   
#endif

#include "../MON_MsDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_MsDefects::MON_MsDefects(uint32 theIndex):
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
    myInternalAISLCount(0),
    myPropritaryInternalAISLCount(0),
    mySdBerCount(0),
    mySfBerCount(0),
    myRDICount(0),
    myRefCount(0),
    myAISState(false),
    myInternalAISLState(false),
    myPropritaryInternalAISLState(false),
    mySdBerState(false), 
    mySfBerState(false),
    myRDIState(false),
    myRefState(false),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myUpperLayerForMSInternalFailTAState(false),
    myUpperLayerForMSInternalFailTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0),
    myTermLpbkState(false),
    myTermLpbkCount(0),
    myDefectFailLayerBitMask(MON_FAILLAYER_MS_DEFAULT_BITMASK)
{
}

MON_MsDefects::~MON_MsDefects()
{
}

void MON_MsDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerFailTACount = 0;
    myUpperLayerForMSFailTACount = 0;
    myUpperLayerFailNTACount = 0;
    myLockCount = 0;
    myAISCount = 0;
    myInternalAISLCount = 0;
    myPropritaryInternalAISLCount = 0;
    mySdBerCount = 0;
    mySfBerCount = 0;
    myRDICount = 0;
    myRefCount = 0;

    myUpperLayerFailTAState = false;
    myUpperLayerForMSFailTAState = false;
    myUpperLayerFailNTAState = false;
    myLockState = false;
    myAISState = false;
    myInternalAISLState = false;
    myPropritaryInternalAISLState = false;
    mySdBerState = false;
    mySfBerState = false;
    myRDIState = false;
    myRefState = false;
    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myUpperLayerForMSInternalFailTAState = false;
    myUpperLayerForMSInternalFailTACount = 0;    
    myInternalLockState = false;
    myInternalLockLockCount = 0;

    myTermLpbkState = false;
    myTermLpbkCount = 0;

    myDefectFailLayerBitMask = MON_FAILLAYER_MS_DEFAULT_BITMASK;
}

bool MON_MsDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myAISState;
    
    return aIsLayerFail && IsValidated();
}

void MON_MsDefects::SetFailLayerBitMask(uint16 theBitMask)
{
    myDefectFailLayerBitMask = theBitMask;
}

bool MON_MsDefects::AisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSAIS_BITMASK) == 0 ? false : true;
}

bool MON_MsDefects::InternalAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSINTAIS_BITMASK) == 0 ? false : true;
}

bool MON_MsDefects::PropritaryInternalAisLFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSPROPAIS_BITMASK) == 0 ? false : true;
}

bool MON_MsDefects::IsLayerForMaintSigInDefects() const
{
    bool aIsLayerFail = (myAISState && AisFailLayer()) ||
						 myUpperLayerForMSFailTAState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_MsDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}

bool MON_MsDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

// Add myUpperLayerInternalFailTAState to IsLayerInternalInDefects because it does not automatically set Internal AIS
bool MON_MsDefects::IsLayerInternalInDefects() const
{
    bool aIsLayerFail = myInternalAISLState || myPropritaryInternalAISLState || myUpperLayerInternalFailTAState;

    return aIsLayerFail && IsValidated();
}

bool MON_MsDefects::IsLayerInternalForMaintSigInDefects() const
{
    bool aIsLayerFail = (myInternalAISLState && InternalAisFailLayer()) 
        || (myPropritaryInternalAISLState && PropritaryInternalAisLFailLayer()) 
        || (myUpperLayerForMSInternalFailTAState);

    return aIsLayerFail && IsValidated();
}


bool MON_MsDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

bool MON_MsDefects::IsLayerInTermLpbk() const
{
    return myTermLpbkState && IsValidated();
}

bool MON_MsDefects::GetDefectForMaintSig(CT_TEL_Defect theDefect) const
{
    uint32 aCount = 0;
    bool aState = false;
    bool rtv = false;
    GetDefectStatus(theDefect, &aCount, &aState);

    switch (theDefect)
    {
    case CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT:
        rtv = aState && PropritaryInternalAisLFailLayer();
        break;

    case CT_TEL_MS_INTERNAL_AISL_DEFECT:
        rtv = aState && InternalAisFailLayer();
        break;

    case CT_TEL_MS_AIS_DEFECT:
        rtv = aState && AisFailLayer();
        break;
        
    default:
        rtv = aState;
        break;
    }
    
    // return state && xxxFailLayer()
    return rtv;        
}
void MON_MsDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_MS_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_MS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSFailTAState;
        *theCount = myUpperLayerForMSFailTACount;
        break;
    case CT_TEL_MS_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_MS_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_MS_AIS_DEFECT:
        *theCount = myAISCount;
        *theState = myAISState;
        break;
    case CT_TEL_MS_INTERNAL_AISL_DEFECT:
        *theCount = myInternalAISLCount;
        *theState = myInternalAISLState;
        break;
    case CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT:
        *theCount = myPropritaryInternalAISLCount;
        *theState = myPropritaryInternalAISLState;
        break;
    case CT_TEL_MS_SDBER_DEFECT:
        *theCount = mySdBerCount;
        *theState = mySdBerState;
        break;
    case CT_TEL_MS_SFBER_DEFECT:
        *theCount = mySfBerCount;
        *theState = mySfBerState;
        break;
    case CT_TEL_MS_RDI_DEFECT:
        *theCount = myRDICount;
        *theState = myRDIState;
        break;
    case CT_TEL_MS_REF_DEFECT:
        *theCount = myRefCount;
        *theState = myRefState;
        break;
    case CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        *theState = myUpperLayerForMSInternalFailTAState;
        *theCount = myUpperLayerForMSInternalFailTACount;
        break; 
    case CT_TEL_MS_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    case CT_TEL_MS_TERM_LPBK:
        *theState = myTermLpbkState;
        *theCount = myTermLpbkCount;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_MsDefects: defect not supported");
        break;
    }

}

bool MON_MsDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_MS_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_MS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSFailTAState, &myUpperLayerForMSFailTACount);
    case CT_TEL_MS_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_MS_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_MS_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
    case CT_TEL_MS_INTERNAL_AISL_DEFECT:
        return UpdateDefect(theState, theTransition, &myInternalAISLState, &myInternalAISLCount);
    case CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT:
        return UpdateDefect(theState, theTransition, &myPropritaryInternalAISLState, &myPropritaryInternalAISLCount);
    case CT_TEL_MS_SDBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdBerState, &mySdBerCount);
    case CT_TEL_MS_SFBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySfBerState, &mySfBerCount);
    case CT_TEL_MS_RDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myRDIState, &myRDICount);
    case CT_TEL_MS_REF_DEFECT:
        return UpdateDefect(theState, theTransition, &myRefState, &myRefCount);
    case CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerForMSInternalFailTAState, &myUpperLayerForMSInternalFailTACount);     
    case CT_TEL_MS_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    case CT_TEL_MS_TERM_LPBK:
        return UpdateDefect(theState, theTransition, &myTermLpbkState, &myTermLpbkCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_MsDefects: unsupported defect");
        return false;
    }
}

ostream& MON_MsDefects::WriteObject( ostream& theStream )
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
    theStream << FC_InsertVar(myInternalAISLCount);
    theStream << FC_InsertVar(myPropritaryInternalAISLCount);
    theStream << FC_InsertVar(mySdBerCount);
    theStream << FC_InsertVar(mySfBerCount);
    theStream << FC_InsertVar(myRDICount);
    theStream << FC_InsertVar(myRefCount);
    theStream << FC_InsertVar(myAISState);
    theStream << FC_InsertVar(myInternalAISLState);
    theStream << FC_InsertVar(myPropritaryInternalAISLState);
    theStream << FC_InsertVar(mySdBerState);
    theStream << FC_InsertVar(mySfBerState);
    theStream << FC_InsertVar(myRDIState);
    theStream << FC_InsertVar(myRefState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerForMSInternalFailTACount);
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);
    theStream << FC_InsertVar(myTermLpbkState);
    theStream << FC_InsertVar(myTermLpbkCount);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

istream& MON_MsDefects::ReadObject( istream& theStream )
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
    theStream >> FC_ExtractVar(myInternalAISLCount);
    theStream >> FC_ExtractVar(myPropritaryInternalAISLCount);
    theStream >> FC_ExtractVar(mySdBerCount);
    theStream >> FC_ExtractVar(mySfBerCount);
    theStream >> FC_ExtractVar(myRDICount);
    theStream >> FC_ExtractVar(myRefCount);
    theStream >> FC_ExtractVar(myAISState);
    theStream >> FC_ExtractVar(myInternalAISLState);
    theStream >> FC_ExtractVar(myPropritaryInternalAISLState);
    theStream >> FC_ExtractVar(mySdBerState);
    theStream >> FC_ExtractVar(mySfBerState);
    theStream >> FC_ExtractVar(myRDIState);
    theStream >> FC_ExtractVar(myRefState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerForMSInternalFailTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);
    theStream >> FC_ExtractVar(myTermLpbkState);
    theStream >> FC_ExtractVar(myTermLpbkCount);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}

FC_Stream& MON_MsDefects::WriteObjectBinary( FC_Stream& theStream )
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
    theStream << myInternalAISLCount;
    theStream << myPropritaryInternalAISLCount;
    theStream << mySdBerCount;
    theStream << mySfBerCount;
    theStream << myRDICount;
    theStream << myRefCount;
    theStream << myAISState;
    theStream << myInternalAISLState;
    theStream << myPropritaryInternalAISLState;
    theStream << mySdBerState;
    theStream << mySfBerState;
    theStream << myRDIState;
    theStream << myRefState;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myUpperLayerForMSInternalFailTAState;
    theStream << myUpperLayerForMSInternalFailTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;
    theStream << myTermLpbkState;
    theStream << myTermLpbkCount;
    theStream << myDefectFailLayerBitMask;


    return theStream;
}

FC_Stream& MON_MsDefects::ReadObjectBinary( FC_Stream& theStream ) 
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
    theStream >> myInternalAISLCount;
    theStream >> myPropritaryInternalAISLCount;
    theStream >> mySdBerCount;
    theStream >> mySfBerCount;
    theStream >> myRDICount;
    theStream >> myRefCount;
    theStream >> myAISState;
    theStream >> myInternalAISLState;
    theStream >> myPropritaryInternalAISLState;
    theStream >> mySdBerState;
    theStream >> mySfBerState;
    theStream >> myRDIState;
    theStream >> myRefState;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myUpperLayerForMSInternalFailTAState;
    theStream >> myUpperLayerForMSInternalFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;
    theStream >> myTermLpbkState;
    theStream >> myTermLpbkCount;
    theStream >> myDefectFailLayerBitMask;

    return theStream;
}

void MON_MsDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "MS      - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "MS      - UPPER LAYER FOR MS FAIL (TA)      = " << DISPLAY_BOOL(myUpperLayerForMSFailTAState) << " (" << myUpperLayerForMSFailTACount << ")" << endl;
    theStream   << "MS      - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "MS      - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "MS      - MS-AIS                            = " << DISPLAY_BOOL(myAISState) << " (" << myAISCount << ")"<< endl;
    theStream   << "MS      - MS-SFBER                          = " << DISPLAY_BOOL(mySfBerState) << " (" << mySfBerCount << ")"<< endl;
    theStream   << "MS      - MS-SDBER                          = " << DISPLAY_BOOL(mySdBerState) << " (" << mySdBerCount << ")"<< endl;
    theStream   << "MS      - MS-RDI                            = " << DISPLAY_BOOL(myRDIState) << " (" << myRDICount << ")"<< endl;
    theStream   << "MS      - MS-REFERENCE                      = " << DISPLAY_BOOL(myRefState) << " (" << myRefCount << ")"<< endl << endl;
    // internal defects
    theStream   << "MS      - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "MS      - INTERNAL UPPER LAYER FOR MSFAIL (TA) = " << DISPLAY_BOOL(myUpperLayerForMSInternalFailTAState) << " (" << myUpperLayerForMSInternalFailTACount << ")" << endl;
    theStream   << "MS      - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;
    theStream   << "MS      - MS-INTERNAL AIS-L                 = " << DISPLAY_BOOL(myInternalAISLState) << " (" << myInternalAISLCount << ")"<< endl;
    theStream   << "MS      - MS-PROPRIETARY INTERNAL AIS       = " << DISPLAY_BOOL(myPropritaryInternalAISLState) << " (" << myPropritaryInternalAISLCount << ")"<< endl;

    theStream   << "MS      - TERMINAL LOOPBACK STATE           = " << DISPLAY_BOOL(myTermLpbkState) << " (" << myTermLpbkCount << ")" << endl;
    theStream   << "MS      - AIS Fail Layer                    = " << DISPLAY_BOOL(AisFailLayer()) << endl; 

}
