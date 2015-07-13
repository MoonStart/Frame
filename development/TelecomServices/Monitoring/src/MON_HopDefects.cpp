// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_HopDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_HopDefects::MON_HopDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),
    myIsConnectedAsSrcState(false),
    myIsConnectedAsSrcCount(0),
    myIsConnectedAsDstState(false),
    myIsConnectedAsDstCount(0),

    myAISCount(0),
    myLOPCount(0),
    myUNEQCount(0),
    myPLMCount(0),
    myTIMCount(0),
    myRDICount(0), 
    mySdBerCount(0),
    mySfBerCount(0),

    myAISState(false),
    myLOPState(false),
    myUNEQState(false),
    myPLMState(false),
    myTIMState(false),
    myRDIState(false),
    mySdBerState(false),
    mySfBerState(false),

    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0)
{
}

MON_HopDefects::~MON_HopDefects()
{
}

void MON_HopDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerFailTACount = 0;
    myUpperLayerFailNTACount = 0;
    myLockCount = 0;
    myIsConnectedAsSrcCount = 0;
    myIsConnectedAsDstCount = 0;
    myAISCount = 0;
    myLOPCount = 0;
    myUNEQCount = 0;
    myPLMCount = 0;
    myTIMCount = 0;
    myRDICount = 0;
    mySdBerCount = 0;
    mySfBerCount = 0;

    myUpperLayerFailTAState = false;
    myUpperLayerFailNTAState = false;
    myLockState = false;
    myIsConnectedAsSrcState = false;
    myIsConnectedAsDstState = false;
    myAISState = false;
    myLOPState = false;
    myUNEQState = false;
    myPLMState = false;
    myTIMState = false;
    myRDIState = false;
    mySdBerState = false;
    mySfBerState = false;

    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myInternalLockState = false;
    myInternalLockLockCount = 0;
}


bool MON_HopDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myAISState || myLOPState || myUNEQState || myPLMState;

    // Currently, Path Trace is not supported.
    // if(myLayerFailOnTimEnable)
    //     aIsLayerFail |=  myTIMState;

    return aIsLayerFail && IsValidated();
}

bool MON_HopDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}

bool MON_HopDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

bool MON_HopDefects::IsLayerInternalInDefects() const
{
    return myUpperLayerInternalFailTAState && IsValidated();
}

bool MON_HopDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}


bool MON_HopDefects::IsConnectedAsSrc() const
{
    return myIsConnectedAsSrcState && IsValidated();
}

bool MON_HopDefects::IsConnectedAsDst() const
{
    return myIsConnectedAsDstState && IsValidated();
}


void MON_HopDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_HOP_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_HOP_IS_SRC:
        *theState = myIsConnectedAsSrcState;
        *theCount = myIsConnectedAsSrcCount;
        break;
    case CT_TEL_HOP_IS_DST:
        *theState = myIsConnectedAsDstState;
        *theCount = myIsConnectedAsDstCount;
        break;
    case CT_TEL_HOP_AIS_DEFECT:
        *theCount = myAISCount;
        *theState = myAISState;
        break;
    case CT_TEL_HOP_LOP_DEFECT:
        *theCount = myLOPCount;
        *theState = myLOPState;
        break;
    case CT_TEL_HOP_UNEQ_DEFECT:
        *theCount = myUNEQCount;
        *theState = myUNEQState;
        break;
    case CT_TEL_HOP_PLM_DEFECT:
        *theCount = myPLMCount;
        *theState = myPLMState;
        break;
    case CT_TEL_HOP_TIM_DEFECT:
        *theCount = myTIMCount;
        *theState = myTIMState;
        break;
    case CT_TEL_HOP_RDI_DEFECT:
        *theCount = myRDICount;
        *theState = myRDIState;
        break;
    case CT_TEL_HOP_SDBER_DEFECT:
        *theCount = mySdBerCount;
        *theState = mySdBerState;
        break;
    case CT_TEL_HOP_SFBER_DEFECT:
        *theCount = mySfBerCount;
        *theState = mySfBerState;
        break;
    case CT_TEL_HOP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_HOP_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_HopDefects: defect not supported");
        break;
    }

}

bool MON_HopDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_HOP_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_HOP_IS_SRC:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsSrcState, &myIsConnectedAsSrcCount);
    case CT_TEL_HOP_IS_DST:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsDstState, &myIsConnectedAsDstCount);
    case CT_TEL_HOP_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
    case CT_TEL_HOP_LOP_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOPState, &myLOPCount);
    case CT_TEL_HOP_UNEQ_DEFECT:
        return UpdateDefect(theState, theTransition, &myUNEQState, &myUNEQCount);
    case CT_TEL_HOP_PLM_DEFECT:
        return UpdateDefect(theState, theTransition, &myPLMState, &myPLMCount);
    case CT_TEL_HOP_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myTIMState, &myTIMCount);
    case CT_TEL_HOP_RDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myRDIState, &myRDICount);
    case CT_TEL_HOP_SDBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySdBerState, &mySdBerCount);
    case CT_TEL_HOP_SFBER_DEFECT:
        return UpdateDefect(theState, theTransition, &mySfBerState, &mySfBerCount);
    case CT_TEL_HOP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_HOP_INTERNAL_LOCK:
        return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_HopDefects: unsupported defect");
        return false;
    }
}

ostream& MON_HopDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerFailTAState);
    theStream << FC_InsertVar(myUpperLayerFailTACount);
    theStream << FC_InsertVar(myUpperLayerFailNTAState);
    theStream << FC_InsertVar(myUpperLayerFailNTACount); 
    theStream << FC_InsertVar(myLockState); 
    theStream << FC_InsertVar(myLockCount);
    theStream << FC_InsertVar(myIsConnectedAsSrcState);
    theStream << FC_InsertVar(myIsConnectedAsSrcCount);
    theStream << FC_InsertVar(myIsConnectedAsDstState);
    theStream << FC_InsertVar(myIsConnectedAsDstCount);

    theStream << FC_InsertVar(myAISCount);
    theStream << FC_InsertVar(myLOPCount);
    theStream << FC_InsertVar(myUNEQCount);
    theStream << FC_InsertVar(myPLMCount);
    theStream << FC_InsertVar(myTIMCount);
    theStream << FC_InsertVar(myRDICount);
    theStream << FC_InsertVar(mySdBerCount);
    theStream << FC_InsertVar(mySfBerCount);

    theStream << FC_InsertVar(myAISState);
    theStream << FC_InsertVar(myLOPState);
    theStream << FC_InsertVar(myUNEQState);
    theStream << FC_InsertVar(myPLMState);
    theStream << FC_InsertVar(myTIMState);
    theStream << FC_InsertVar(myRDIState);
    theStream << FC_InsertVar(mySdBerState);
    theStream << FC_InsertVar(mySfBerState);

    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);

    return theStream;
}

istream& MON_HopDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream); 
    theStream >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLockCount);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcState);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcCount);
    theStream >> FC_ExtractVar(myIsConnectedAsDstState);
    theStream >> FC_ExtractVar(myIsConnectedAsDstCount);

    theStream >> FC_ExtractVar(myAISCount);
    theStream >> FC_ExtractVar(myLOPCount);
    theStream >> FC_ExtractVar(myUNEQCount);
    theStream >> FC_ExtractVar(myPLMCount);
    theStream >> FC_ExtractVar(myTIMCount);
    theStream >> FC_ExtractVar(myRDICount);
    theStream >> FC_ExtractVar(mySdBerCount);
    theStream >> FC_ExtractVar(mySfBerCount);

    theStream >> FC_ExtractVar(myAISState);
    theStream >> FC_ExtractVar(myLOPState);
    theStream >> FC_ExtractVar(myUNEQState);
    theStream >> FC_ExtractVar(myPLMState);
    theStream >> FC_ExtractVar(myTIMState);
    theStream >> FC_ExtractVar(myRDIState);
    theStream >> FC_ExtractVar(mySdBerState);
    theStream >> FC_ExtractVar(mySfBerState);

    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);

    return theStream;
}

FC_Stream& MON_HopDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerFailTAState;
    theStream << myUpperLayerFailTACount;
    theStream << myUpperLayerFailNTAState;
    theStream << myUpperLayerFailNTACount;
    theStream << myLockState;
    theStream << myLockCount;
    theStream << myIsConnectedAsSrcState;
    theStream << myIsConnectedAsSrcCount;
    theStream << myIsConnectedAsDstState;
    theStream << myIsConnectedAsDstCount;

    theStream << myAISCount;
    theStream << myLOPCount;
    theStream << myUNEQCount;
    theStream << myPLMCount;
    theStream << myTIMCount;
    theStream << myRDICount;
    theStream << mySdBerCount;
    theStream << mySfBerCount;

    theStream << myAISState;
    theStream << myLOPState;
    theStream << myUNEQState;
    theStream << myPLMState;
    theStream << myTIMState;
    theStream << myRDIState;
    theStream << mySdBerState;
    theStream << mySfBerState;

    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;

    return theStream;
}

FC_Stream& MON_HopDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerFailTAState;
    theStream >> myUpperLayerFailTACount;
    theStream >> myUpperLayerFailNTAState;
    theStream >> myUpperLayerFailNTACount;
    theStream >> myLockState;
    theStream >> myLockCount;
    theStream >> myIsConnectedAsSrcState;
    theStream >> myIsConnectedAsSrcCount;
    theStream >> myIsConnectedAsDstState;
    theStream >> myIsConnectedAsDstCount;

    theStream >> myAISCount;
    theStream >> myLOPCount;
    theStream >> myUNEQCount;
    theStream >> myPLMCount;
    theStream >> myTIMCount;
    theStream >> myRDICount;
    theStream >> mySdBerCount;
    theStream >> mySfBerCount;

    theStream >> myAISState;
    theStream >> myLOPState;
    theStream >> myUNEQState;
    theStream >> myPLMState;
    theStream >> myTIMState;
    theStream >> myRDIState;
    theStream >> mySdBerState;
    theStream >> mySfBerState;

    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;

    return theStream;
}

void MON_HopDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);  
    theStream   << "HOP     - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "HOP     - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "HOP     - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "HOP     - IS CONNECTED AS SOURCE OF XC      = " << DISPLAY_BOOL(myIsConnectedAsSrcState) << " (" << myIsConnectedAsSrcCount << ")" << endl;
    theStream   << "HOP     - IS CONNECTED AS DESTINATION OF XC = " << DISPLAY_BOOL(myIsConnectedAsDstState) << " (" << myIsConnectedAsDstCount << ")" << endl;
    theStream   << "HOP     - HOP-AIS                           = " << DISPLAY_BOOL(myAISState) << " (" << myAISCount << ")"<< endl;
    theStream   << "HOP     - HOP-LOP                           = " << DISPLAY_BOOL(myLOPState) << " (" << myLOPCount << ")"<< endl;
    theStream   << "HOP     - HOP-UNEQ                          = " << DISPLAY_BOOL(myUNEQState) << " (" << myUNEQCount << ")"<< endl;
    theStream   << "HOP     - HOP-PLM                           = " << DISPLAY_BOOL(myPLMState) << " (" << myPLMCount << ")"<< endl;
    theStream   << "HOP     - HOP-TIM                           = " << DISPLAY_BOOL(myTIMState) << " (" << myTIMCount << ")"<< endl;
    theStream   << "HOP     - HOP-RDI                           = " << DISPLAY_BOOL(myRDIState) << " (" << myRDICount << ")"<< endl;
    theStream   << "HOP     - HOP-SDBER                         = " << DISPLAY_BOOL(mySdBerState) << " (" << mySdBerCount << ")"<< endl;
    theStream   << "HOP     - HOP-SFBER                         = " << DISPLAY_BOOL(mySfBerState) << " (" << mySfBerCount << ")"<< endl << endl;
    // internal defects
    theStream   << "HOP     - INTERNAL UPPER LAYER FAIL (TA)    = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "HOP     - INTERNAL LOCK STATE               = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;

}
