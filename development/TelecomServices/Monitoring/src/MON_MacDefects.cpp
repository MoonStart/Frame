// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_MacDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"


MON_MacDefects::MON_MacDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myRFLinkFailCount(0),
    myFefiCount(0),
    myLacpFailCount(0),
    myRFLinkFailState(false),
    myFefiState(false),
    myLacpFailState(false),
    myUpperLayerInternalFailTAState(false),
    myUpperLayerInternalFailTACount(0),
    myInternalLockState(false),
    myInternalLockLockCount(0)
{
}

MON_MacDefects::~MON_MacDefects()
{
}


void MON_MacDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myRFLinkFailCount = 0;
    myFefiCount = 0;
    myLacpFailCount = 0;

    myRFLinkFailState = false;
    myFefiState = false;
    myLacpFailState = false;

    myUpperLayerInternalFailTAState = false;
    myUpperLayerInternalFailTACount = 0;
    myInternalLockState = false;
    myInternalLockLockCount = 0;
}


// Add myUpperLayerInternalFailTAState to InLayerInDefects because it does not automatically set any defect (i.e., LOFD) 
bool MON_MacDefects::IsLayerInDefects() const
{
    //bool aIsLayerFail = myRFLinkFailState || myFefiState || myUpperLayerInternalFailTAState;
    bool aIsLayerFail = myFefiState || myUpperLayerInternalFailTAState;
    return aIsLayerFail && IsValidated();
}

bool MON_MacDefects::IsLayerLocked() const
{
    return myInternalLockState && IsValidated();
}


// There is no IsLayerInternalInDefects because that is the IsLayerInDefects (line to port defects) 

bool MON_MacDefects::IsLayerInternalLocked() const
{
    return myInternalLockState && IsValidated();
}

void MON_MacDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_MAC_RFLINKFAIL_DEFECT:
        *theCount = myRFLinkFailCount;
        *theState = myRFLinkFailState;
        break;
    case CT_TEL_MAC_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerInternalFailTAState;
        *theCount = myUpperLayerInternalFailTACount;
        break;
    case CT_TEL_MAC_INTERNAL_LOCK:
        *theState = myInternalLockState;
        *theCount = myInternalLockLockCount;
        break;
    case CT_TEL_MAC_FEFI_DEFECT:
        *theState = myFefiState;
        *theCount = myFefiCount;
        break;
    case CT_TEL_LACPFAIL_DEFECT:
        *theState = myLacpFailState;
        *theCount = myLacpFailCount;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_MacDefects: defect not supported");
        break;
    }

}

bool MON_MacDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_MAC_RFLINKFAIL_DEFECT:
      return UpdateDefect(theState, theTransition, &myRFLinkFailState, &myRFLinkFailCount);
    case CT_TEL_MAC_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT:
      return UpdateDefect(theState, theTransition, &myUpperLayerInternalFailTAState, &myUpperLayerInternalFailTACount);
    case CT_TEL_MAC_INTERNAL_LOCK:
      return UpdateDefect(theState, theTransition, &myInternalLockState, &myInternalLockLockCount);
    case CT_TEL_MAC_FEFI_DEFECT:
      return UpdateDefect(theState, theTransition, &myFefiState, &myFefiCount);
    case CT_TEL_LACPFAIL_DEFECT:
      return UpdateDefect(theState, theTransition, &myLacpFailState, &myLacpFailCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_MacDefects: unsupported defect");
        return false;
    }
}

ostream& MON_MacDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myRFLinkFailState);
    theStream << FC_InsertVar(myRFLinkFailCount);
    theStream << FC_InsertVar(myUpperLayerInternalFailTAState);
    theStream << FC_InsertVar(myUpperLayerInternalFailTACount);
    theStream << FC_InsertVar(myInternalLockState);
    theStream << FC_InsertVar(myInternalLockLockCount);
    theStream << FC_InsertVar(myFefiState);
    theStream << FC_InsertVar(myFefiCount);
    theStream << FC_InsertVar(myLacpFailState);
    theStream << FC_InsertVar(myLacpFailCount);

    return theStream;
}

istream& MON_MacDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRFLinkFailState);
    theStream >> FC_ExtractVar(myRFLinkFailCount);;
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerInternalFailTACount);
    theStream >> FC_ExtractVar(myInternalLockState);
    theStream >> FC_ExtractVar(myInternalLockLockCount);
    theStream >> FC_ExtractVar(myFefiState);
    theStream >> FC_ExtractVar(myFefiCount);
    theStream >> FC_ExtractVar(myLacpFailState);
    theStream >> FC_ExtractVar(myLacpFailCount);

    return theStream;
}

FC_Stream& MON_MacDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myRFLinkFailState;
    theStream << myRFLinkFailCount;
    theStream << myUpperLayerInternalFailTAState;
    theStream << myUpperLayerInternalFailTACount;
    theStream << myInternalLockState;
    theStream << myInternalLockLockCount;
    theStream << myFefiState;
    theStream << myFefiCount;
    theStream << myLacpFailState;
    theStream << myLacpFailCount;

    return theStream;
}

FC_Stream& MON_MacDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myRFLinkFailState;
    theStream >> myRFLinkFailCount;
    theStream >> myUpperLayerInternalFailTAState;
    theStream >> myUpperLayerInternalFailTACount;
    theStream >> myInternalLockState;
    theStream >> myInternalLockLockCount;
    theStream >> myFefiState;
    theStream >> myFefiCount;
    theStream >> myLacpFailState;
    theStream >> myLacpFailCount;

    return theStream;
}

void MON_MacDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "MAC    - INTERNAL UPPER LAYER FAIL (TA)   = " << DISPLAY_BOOL(myUpperLayerInternalFailTAState) << " (" << myUpperLayerInternalFailTACount << ")" << endl;
    theStream   << "MAC    - INTERNAL LOCK STATE              = " << DISPLAY_BOOL(myInternalLockState) << " (" << myInternalLockLockCount << ")" << endl;
    theStream   << "MAC    - MAC-RFLINKFAIL                   = " << DISPLAY_BOOL(myRFLinkFailState) << " (" << myRFLinkFailCount << ")"<< endl;
    theStream   << "MAC    - MAC-FEFI                         = " << DISPLAY_BOOL(myFefiState) << " (" << myFefiCount << ")"<< endl;
    theStream   << "MAC    - LACP FAIL                        = " << DISPLAY_BOOL(myLacpFailState) << " (" << myLacpFailCount << ")"<< endl;
}
