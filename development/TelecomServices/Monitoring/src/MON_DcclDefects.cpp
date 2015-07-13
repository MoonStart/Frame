// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_DcclDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_DcclDefects::MON_DcclDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),
    myLinkDownCount(0),
    myLinkIncompleteCount(0),
    myLinkDownState(false),
    myLinkIncompleteState(false)
{
}

MON_DcclDefects::~MON_DcclDefects()
{
}

bool MON_DcclDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myLinkDownState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_DcclDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}


void MON_DcclDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerFailTACount = 0;
    myUpperLayerFailNTACount = 0;
    myLockCount = 0;
    myLinkDownCount = 0;
    myLinkIncompleteCount = 0;

    myUpperLayerFailTAState = false;
    myUpperLayerFailNTAState = false;
    myLockState = false;
    myLinkDownState = false;
    myLinkIncompleteState = false;

}

bool MON_DcclDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

void MON_DcclDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    /*
    case CT_TEL_DCCL_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_DCCL_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_DCCL_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    */
    case CT_TEL_DCCL_LINK_DOWN_DEFECT:
        *theCount = myLinkDownCount;
        *theState = myLinkDownState;
        break;
    case CT_TEL_DCCL_LINK_INCOMPLETE_DEFECT:
        *theCount = myLinkIncompleteCount;
        *theState = myLinkIncompleteState;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_DcclDefects: defect not supported");
        break;
    }

}

bool MON_DcclDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    /*
    case CT_TEL_DCCL_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_DCCL_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_DCCL_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    */
    case CT_TEL_DCCL_LINK_DOWN_DEFECT:
        return UpdateDefect(theState, theTransition, &myLinkDownState, &myLinkDownCount);
    case CT_TEL_DCCL_LINK_INCOMPLETE_DEFECT:
        return UpdateDefect(theState, theTransition, &myLinkIncompleteState, &myLinkIncompleteCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DcclDefects: unsupported defect");
        return false;
    }
}

ostream& MON_DcclDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerFailTAState);
    theStream << FC_InsertVar(myUpperLayerFailTACount);
    theStream << FC_InsertVar(myUpperLayerFailNTAState);
    theStream << FC_InsertVar(myUpperLayerFailNTACount); 
    theStream << FC_InsertVar(myLockState); 
    theStream << FC_InsertVar(myLockCount);

    theStream << FC_InsertVar(myLinkDownCount);
    theStream << FC_InsertVar(myLinkIncompleteCount);

    theStream << FC_InsertVar(myLinkDownState);
    theStream << FC_InsertVar(myLinkIncompleteState);

    return theStream;
}

istream& MON_DcclDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream); 
    theStream >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLockCount);

    theStream >> FC_ExtractVar(myLinkDownCount);
    theStream >> FC_ExtractVar(myLinkIncompleteCount);


    theStream >> FC_ExtractVar(myLinkDownState);
    theStream >> FC_ExtractVar(myLinkIncompleteState);

    return theStream;
}

FC_Stream& MON_DcclDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerFailTAState;
    theStream << myUpperLayerFailTACount;
    theStream << myUpperLayerFailNTAState;
    theStream << myUpperLayerFailNTACount;
    theStream << myLockState;
    theStream << myLockCount;

    theStream << myLinkDownCount;
    theStream << myLinkIncompleteCount;


    theStream << myLinkDownState;
    theStream << myLinkIncompleteState;


    return theStream;
}

FC_Stream& MON_DcclDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerFailTAState;
    theStream >> myUpperLayerFailTACount;
    theStream >> myUpperLayerFailNTAState;
    theStream >> myUpperLayerFailNTACount;
    theStream >> myLockState;
    theStream >> myLockCount;

    theStream >> myLinkDownCount;
    theStream >> myLinkIncompleteCount;

    theStream >> myLinkDownState;
    theStream >> myLinkIncompleteState;


    return theStream;
}

void MON_DcclDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);  
    theStream   << "DCCL    - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "DCCL    - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "DCCL    - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "DCCL    - DCC LINK DOWN                     = " << DISPLAY_BOOL(myLinkDownState) << " (" << myLinkDownCount << ")"<< endl;
    theStream   << "DCCL    - DCC LINK INCOMPLETE               = " << DISPLAY_BOOL(myLinkIncompleteState) << " (" << myLinkIncompleteCount << ")"<< endl;

}
