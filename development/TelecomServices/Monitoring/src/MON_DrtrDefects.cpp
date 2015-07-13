// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_DrtrDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_DrtrDefects::MON_DrtrDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myUpperLayerFailTAState(false),
    myUpperLayerFailTACount(0),
    myUpperLayerFailNTAState(false),
    myUpperLayerFailNTACount(0),
    myLockState(false),
    myLockCount(0),

    myRejectedAdjancencyCount(0),
    myAreaAddressMismatchCount(0),
    myMaxAreaAddressMismatchCount(0),
    myL1DatabaseOverloadCount(0),
    myL2DatabaseOverloadCount(0),

    myRejectedAdjancencyState(false),
    myAreaAddressMismatchState(false),
    myMaxAreaAddressMismatchState(false),
    myL1DatabaseOverloadState(false),
    myL2DatabaseOverloadState(false)
{
}

MON_DrtrDefects::~MON_DrtrDefects()
{
}

bool MON_DrtrDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myRejectedAdjancencyState ||
                        myAreaAddressMismatchState ||
                        myMaxAreaAddressMismatchState ||
                        myL1DatabaseOverloadState ||
                        myL2DatabaseOverloadState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_DrtrDefects::IsLayerInDefectsNTA() const
{
    return myUpperLayerFailNTAState && IsValidated();
}


void MON_DrtrDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myUpperLayerFailTACount = 0;
    myUpperLayerFailNTACount = 0;
    myLockCount = 0;
    myRejectedAdjancencyCount = 0;
    myAreaAddressMismatchCount = 0;
    myMaxAreaAddressMismatchCount = 0;
    myL1DatabaseOverloadCount = 0;
    myL2DatabaseOverloadCount = 0;

    myUpperLayerFailTAState = false;
    myUpperLayerFailNTAState = false;
    myLockState = false;
    myRejectedAdjancencyState = false;
    myAreaAddressMismatchState = false;
    myMaxAreaAddressMismatchState = false;
    myL1DatabaseOverloadState = false;
    myL2DatabaseOverloadState = false;

}

bool MON_DrtrDefects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}

void MON_DrtrDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    /*
    case CT_TEL_DRTR_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerFailTAState;
        *theCount = myUpperLayerFailTACount;
        break;
    case CT_TEL_DRTR_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerFailNTAState;
        *theCount = myUpperLayerFailNTACount;
        break;
    case CT_TEL_DRTR_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    */
    case CT_TEL_DRTR_REJECTED_ADJ_DEFECT:
        *theCount = myRejectedAdjancencyCount;
        *theState = myRejectedAdjancencyState;
        break;

    case CT_TEL_DRTR_AREA_MISMATCH_DEFECT:
        *theCount = myAreaAddressMismatchCount;
        *theState = myAreaAddressMismatchState;
        break;

    case CT_TEL_DRTR_MAX_AREA_ADDR_DEFECT:
        *theCount = myMaxAreaAddressMismatchCount;
        *theState = myMaxAreaAddressMismatchState;
        break;

    case CT_TEL_DRTR_L1DB_OVERLOAD_DEFECT:
        *theCount = myL1DatabaseOverloadCount;
        *theState = myL1DatabaseOverloadState;
        break;

    case CT_TEL_DRTR_L2DB_OVERLOAD_DEFECT:
        *theCount = myL2DatabaseOverloadCount;
        *theState = myL2DatabaseOverloadState;
        break;

    default:
        FC_THROW_ERROR(FC_SWError, "MON_DrtrDefects: defect not supported");
        break;
    }

}

bool MON_DrtrDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    /*
    case CT_TEL_DRTR_UPPER_LAYER_FAIL_TA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailTAState, &myUpperLayerFailTACount);
    case CT_TEL_DRTR_UPPER_LAYER_FAIL_NTA_DEFECT:
        return UpdateDefect(theState, theTransition, &myUpperLayerFailNTAState, &myUpperLayerFailNTACount);
    case CT_TEL_DRTR_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    */
    case CT_TEL_DRTR_REJECTED_ADJ_DEFECT:
        return UpdateDefect(theState, theTransition, &myRejectedAdjancencyState,     &myRejectedAdjancencyCount);

    case CT_TEL_DRTR_AREA_MISMATCH_DEFECT:
        return UpdateDefect(theState, theTransition, &myAreaAddressMismatchState,    &myAreaAddressMismatchCount);

    case CT_TEL_DRTR_MAX_AREA_ADDR_DEFECT:
        return UpdateDefect(theState, theTransition, &myMaxAreaAddressMismatchState, &myMaxAreaAddressMismatchCount);

    case CT_TEL_DRTR_L1DB_OVERLOAD_DEFECT:
        return UpdateDefect(theState, theTransition, &myL1DatabaseOverloadState,     &myL1DatabaseOverloadCount);

    case CT_TEL_DRTR_L2DB_OVERLOAD_DEFECT:
        return UpdateDefect(theState, theTransition, &myL2DatabaseOverloadState,     &myL2DatabaseOverloadCount);

    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DrtrDefects: unsupported defect");
        return false;
    }
}

ostream& MON_DrtrDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myUpperLayerFailTAState);
    theStream << FC_InsertVar(myUpperLayerFailTACount);
    theStream << FC_InsertVar(myUpperLayerFailNTAState);
    theStream << FC_InsertVar(myUpperLayerFailNTACount); 
    theStream << FC_InsertVar(myLockState); 
    theStream << FC_InsertVar(myLockCount);

    theStream << FC_InsertVar(myRejectedAdjancencyCount);
    theStream << FC_InsertVar(myAreaAddressMismatchCount);
    theStream << FC_InsertVar(myMaxAreaAddressMismatchCount);
    theStream << FC_InsertVar(myL1DatabaseOverloadCount);
    theStream << FC_InsertVar(myL2DatabaseOverloadCount);

    theStream << FC_InsertVar(myRejectedAdjancencyState);
    theStream << FC_InsertVar(myAreaAddressMismatchState);
    theStream << FC_InsertVar(myMaxAreaAddressMismatchState);
    theStream << FC_InsertVar(myL1DatabaseOverloadState);
    theStream << FC_InsertVar(myL2DatabaseOverloadState);

    return theStream;
}

istream& MON_DrtrDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream); 
    theStream >> FC_ExtractVar(myUpperLayerFailTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailTACount);
    theStream >> FC_ExtractVar(myUpperLayerFailNTAState);
    theStream >> FC_ExtractVar(myUpperLayerFailNTACount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLockCount);

    theStream >> FC_ExtractVar(myRejectedAdjancencyCount);
    theStream >> FC_ExtractVar(myAreaAddressMismatchCount);
    theStream >> FC_ExtractVar(myMaxAreaAddressMismatchCount);
    theStream >> FC_ExtractVar(myL1DatabaseOverloadCount);
    theStream >> FC_ExtractVar(myL2DatabaseOverloadCount);

    theStream >> FC_ExtractVar(myRejectedAdjancencyState);
    theStream >> FC_ExtractVar(myAreaAddressMismatchState);
    theStream >> FC_ExtractVar(myMaxAreaAddressMismatchState);
    theStream >> FC_ExtractVar(myL1DatabaseOverloadState);
    theStream >> FC_ExtractVar(myL2DatabaseOverloadState);

    return theStream;
}

FC_Stream& MON_DrtrDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myUpperLayerFailTAState;
    theStream << myUpperLayerFailTACount;
    theStream << myUpperLayerFailNTAState;
    theStream << myUpperLayerFailNTACount;
    theStream << myLockState;
    theStream << myLockCount;

    theStream << myRejectedAdjancencyCount;
    theStream << myAreaAddressMismatchCount;
    theStream << myMaxAreaAddressMismatchCount;
    theStream << myL1DatabaseOverloadCount;
    theStream << myL2DatabaseOverloadCount;

    theStream << myRejectedAdjancencyState;
    theStream << myAreaAddressMismatchState;
    theStream << myMaxAreaAddressMismatchState;
    theStream << myL1DatabaseOverloadState;
    theStream << myL2DatabaseOverloadState;

    return theStream;
}

FC_Stream& MON_DrtrDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myUpperLayerFailTAState;
    theStream >> myUpperLayerFailTACount;
    theStream >> myUpperLayerFailNTAState;
    theStream >> myUpperLayerFailNTACount;
    theStream >> myLockState;
    theStream >> myLockCount;

    theStream >> myRejectedAdjancencyCount;
    theStream >> myAreaAddressMismatchCount;
    theStream >> myMaxAreaAddressMismatchCount;
    theStream >> myL1DatabaseOverloadCount;
    theStream >> myL2DatabaseOverloadCount;

    theStream >> myRejectedAdjancencyState;
    theStream >> myAreaAddressMismatchState;
    theStream >> myMaxAreaAddressMismatchState;
    theStream >> myL1DatabaseOverloadState;
    theStream >> myL2DatabaseOverloadState;

    return theStream;
}

void MON_DrtrDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);  
    theStream   << "DRTR    - UPPER LAYER FAIL (TA)             = " << DISPLAY_BOOL(myUpperLayerFailTAState) << " (" << myUpperLayerFailTACount << ")" << endl;
    theStream   << "DRTR    - UPPER LAYER FAIL (NTA)            = " << DISPLAY_BOOL(myUpperLayerFailNTAState) << " (" << myUpperLayerFailNTACount << ")" << endl;
    theStream   << "DRTR    - LOCK STATE                        = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "DRTR    - REJECTED ADJANCENCY               = " << DISPLAY_BOOL(myRejectedAdjancencyState) << " (" << myRejectedAdjancencyCount << ")"<< endl;
    theStream   << "DRTR    - AREA ADDRESS MISMATCH             = " << DISPLAY_BOOL(myAreaAddressMismatchState) << " (" << myAreaAddressMismatchCount << ")"<< endl;
    theStream   << "DRTR    - MAXIMUM AREA ADRESS MISMATCHY     = " << DISPLAY_BOOL(myMaxAreaAddressMismatchState) << " (" << myMaxAreaAddressMismatchCount << ")"<< endl;
    theStream   << "DRTR    - L1 DATABASE OVERLOAD              = " << DISPLAY_BOOL(myL1DatabaseOverloadState) << " (" << myL1DatabaseOverloadCount << ")"<< endl;
    theStream   << "DRTR    - L2 DATABASE OVERLOAD              = " << DISPLAY_BOOL(myL2DatabaseOverloadState) << " (" << myL2DatabaseOverloadCount << ")"<< endl;

}
