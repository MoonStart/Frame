// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_SyncDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_SyncDefects::MON_SyncDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myFreerunCount(0),
    myHoldoverCount(0),
    myFreerunState(false),
    myHoldoverState(false)
{
}

MON_SyncDefects::~MON_SyncDefects()
{
}

bool MON_SyncDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myFreerunState && myHoldoverState;
    
    return aIsLayerFail && IsValidated();
}

void MON_SyncDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myFreerunCount = 0;
    myHoldoverCount = 0;

    myFreerunState = false;
    myHoldoverState = false;
}

void MON_SyncDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_SYNC_FREERUN_DEFECT:
        *theCount = myFreerunCount;
        *theState = myFreerunState;
        break;
    case CT_TEL_SYNC_HOLDOVER_DEFECT:
        *theCount = myHoldoverCount;
        *theState = myHoldoverState;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_SyncDefects: defect not supported");
        break;
    }

}

bool MON_SyncDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_SYNC_FREERUN_DEFECT:
        return UpdateDefect(theState, theTransition, &myFreerunState, &myFreerunCount);
    case CT_TEL_SYNC_HOLDOVER_DEFECT:
        return UpdateDefect(theState, theTransition, &myHoldoverState, &myHoldoverCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_SyncDefects: unsupported defect");
        return false;
    }
}

ostream& MON_SyncDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myFreerunCount);
    theStream << FC_InsertVar(myHoldoverCount);
    theStream << FC_InsertVar(myFreerunState);
    theStream << FC_InsertVar(myHoldoverState);

    return theStream;
}

istream& MON_SyncDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myFreerunCount);
    theStream >> FC_ExtractVar(myHoldoverCount);
    theStream >> FC_ExtractVar(myFreerunState);
    theStream >> FC_ExtractVar(myHoldoverState);

    return theStream;
}

FC_Stream& MON_SyncDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myFreerunCount;
    theStream << myHoldoverCount;
    theStream << myFreerunState;
    theStream << myHoldoverState;

    return theStream;
}

FC_Stream& MON_SyncDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myFreerunCount;
    theStream >> myHoldoverCount;
    theStream >> myFreerunState;
    theStream >> myHoldoverState;

    return theStream;
}

void MON_SyncDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "SYNC    - SYNC-FREERUN                   = " << DISPLAY_BOOL(myFreerunState) << " (" << myFreerunCount << ")"<< endl;
    theStream   << "SYNC    - SYNC-HOLDOVER                  = " << DISPLAY_BOOL(myHoldoverState) << " (" << myHoldoverCount << ")"<< endl;
}
