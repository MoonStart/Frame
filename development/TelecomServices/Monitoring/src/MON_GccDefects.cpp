// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_GccDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"
#include <CommonTypes/CT_DCC_Definitions.h>

MON_GccDefects::MON_GccDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myLinkDownCount(0),
    myLinkIncompleteCount(0),
    myLinkDownState(false),
    myLinkIncompleteState(false)
{
}

MON_GccDefects::~MON_GccDefects()
{
}

bool MON_GccDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myLinkDownState;
    
    return aIsLayerFail && IsValidated();
}


void MON_GccDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myLinkDownCount = 0;
    myLinkIncompleteCount = 0;

    myLinkDownState = false;
    myLinkIncompleteState = false;

}


void MON_GccDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    /*
    case CT_TEL_GCC_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_GCC_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_GCC_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    */
    case CT_TEL_GCC_LINK_DOWN_DEFECT:
        *theCount = myLinkDownCount;
        *theState = myLinkDownState;
        break;
    case CT_TEL_GCC_LINK_INCOMPLETE_DEFECT:
        *theCount = myLinkIncompleteCount;
        *theState = myLinkIncompleteState;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_GccDefects: defect not supported");
        break;
    }

}

bool MON_GccDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    /*
    case CT_TEL_GCC_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_GCC_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_GCC_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    */
    case CT_TEL_GCC_LINK_DOWN_DEFECT:
        return UpdateDefect(theState, theTransition, &myLinkDownState, &myLinkDownCount);
    case CT_TEL_GCC_LINK_INCOMPLETE_DEFECT:
        return UpdateDefect(theState, theTransition, &myLinkIncompleteState, &myLinkIncompleteCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GccDefects: unsupported defect");
        return false;
    }
}

ostream& MON_GccDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);

    theStream << FC_InsertVar(myLinkDownCount);
    theStream << FC_InsertVar(myLinkIncompleteCount);

    theStream << FC_InsertVar(myLinkDownState);
    theStream << FC_InsertVar(myLinkIncompleteState);

    return theStream;
}

istream& MON_GccDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream); 

    theStream >> FC_ExtractVar(myLinkDownCount);
    theStream >> FC_ExtractVar(myLinkIncompleteCount);


    theStream >> FC_ExtractVar(myLinkDownState);
    theStream >> FC_ExtractVar(myLinkIncompleteState);

    return theStream;
}

FC_Stream& MON_GccDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);

    theStream << myLinkDownCount;
    theStream << myLinkIncompleteCount;


    theStream << myLinkDownState;
    theStream << myLinkIncompleteState;


    return theStream;
}

FC_Stream& MON_GccDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);

    theStream >> myLinkDownCount;
    theStream >> myLinkIncompleteCount;

    theStream >> myLinkDownState;
    theStream >> myLinkIncompleteState;


    return theStream;
}

void MON_GccDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);  
    theStream   << "GCC    - GCC LINK DOWN                     = " << DISPLAY_BOOL(myLinkDownState) << " (" << myLinkDownCount << ")"<< endl;
    theStream   << "GCC    - GCC LINK INCOMPLETE               = " << DISPLAY_BOOL(myLinkIncompleteState) << " (" << myLinkIncompleteCount << ")"<< endl;
}
