// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_T1E1Defects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_T1E1Defects::MON_T1E1Defects(uint32 theIndex):
    MON_Defects(theIndex),
    myLockCount(0),
    myLOSCount(0),
    myLOFCount(0),
    myAISCount(0),
	myOffFreqCount(0),
    myLockState(false),
    myLOSState(false),
    myLOFState(false),
    myAISState(false),
	myOffFreqState(false)
{
}

MON_T1E1Defects::~MON_T1E1Defects()
{
}


void MON_T1E1Defects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myLockCount = 0;
    myLOSCount  = 0;
    myLOFCount  = 0;
    myAISCount  = 0;
	myOffFreqCount = 0;

    myLockState = false;
    myLOSState  = false;
    myLOFState  = false;
    myAISState  = false;
	myOffFreqState = false;
}


bool MON_T1E1Defects::IsLayerInDefects() const
{
    bool aIsLayerFail = myLOSState || myLOFState || myAISState || myOffFreqState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_T1E1Defects::IsLayerLocked() const
{
    return myLockState && IsValidated();
}


void MON_T1E1Defects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_T1E1_LOCK:
        *theState = myLockState;
        *theCount = myLockCount;
        break;
    case CT_TEL_T1E1_LOS_DEFECT:
        *theCount = myLOSCount;
        *theState = myLOSState;
        break;
    case CT_TEL_T1E1_LOF_DEFECT:
        *theCount = myLOFCount;
        *theState = myLOFState;
        break;
    case CT_TEL_T1E1_AIS_DEFECT:
        *theCount = myAISCount;
        *theState = myAISState;
        break;
	case CT_TEL_T1E1_OFF_FREQ_DEFECT:
        *theCount = myOffFreqCount;
        *theState = myOffFreqState;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_T1E1Defects: defect not supported");
        break;
    }

}

bool MON_T1E1Defects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_T1E1_LOCK:
        return UpdateDefect(theState, theTransition, &myLockState, &myLockCount);
    case CT_TEL_T1E1_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOSState, &myLOSCount);
    case CT_TEL_T1E1_LOF_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOFState, &myLOFCount);
    case CT_TEL_T1E1_AIS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAISState, &myAISCount);
	case CT_TEL_T1E1_OFF_FREQ_DEFECT:
        return UpdateDefect(theState, theTransition, &myOffFreqState, &myOffFreqCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_T1E1Defects: unsupported defect");
        return false;
    }
}

ostream& MON_T1E1Defects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myLockCount);
    theStream << FC_InsertVar(myLOSCount);
    theStream << FC_InsertVar(myLOFCount);
    theStream << FC_InsertVar(myAISCount);
	theStream << FC_InsertVar(myOffFreqCount);
    theStream << FC_InsertVar(myLockState);
    theStream << FC_InsertVar(myLOSState);
    theStream << FC_InsertVar(myLOFState);
    theStream << FC_InsertVar(myAISState);
	theStream << FC_InsertVar(myOffFreqState);

    return theStream;
}

istream& MON_T1E1Defects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myLockCount);
    theStream >> FC_ExtractVar(myLOSCount);
    theStream >> FC_ExtractVar(myLOFCount);
    theStream >> FC_ExtractVar(myAISCount);
	theStream >> FC_ExtractVar(myOffFreqCount);
    theStream >> FC_ExtractVar(myLockState);
    theStream >> FC_ExtractVar(myLOSState);
    theStream >> FC_ExtractVar(myLOFState);
    theStream >> FC_ExtractVar(myAISState);
	theStream >> FC_ExtractVar(myOffFreqState);

    return theStream;
}

FC_Stream& MON_T1E1Defects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myLockCount;
    theStream << myLOSCount;
    theStream << myLOFCount;
    theStream << myAISCount;
	theStream << myOffFreqCount;
    theStream << myLockState;
    theStream << myLOSState;
    theStream << myLOFState;
    theStream << myAISState;
	theStream << myOffFreqState;

    return theStream;
}

FC_Stream& MON_T1E1Defects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myLockCount;
    theStream >> myLOSCount;
    theStream >> myLOFCount;
    theStream >> myAISCount;
	theStream >> myOffFreqCount;
    theStream >> myLockState;
    theStream >> myLOSState;
    theStream >> myLOFState;
    theStream >> myAISState;
	theStream >> myOffFreqState;

    return theStream;
}

void MON_T1E1Defects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "T1E1    - LOCK STATE                    = " << DISPLAY_BOOL(myLockState) << " (" << myLockCount << ")" << endl;
    theStream   << "T1E1    - LOS                           = " << DISPLAY_BOOL(myLOSState) << " (" << myLOSCount << ")"<< endl;
    theStream   << "T1E1    - LOF                           = " << DISPLAY_BOOL(myLOFState) << " (" << myLOFCount << ")"<< endl;
    theStream   << "T1E1    - AIS                           = " << DISPLAY_BOOL(myAISState) << " (" << myAISCount << ")"<< endl;
	theStream   << "T1E1    - OFF FREQ                      = " << DISPLAY_BOOL(myOffFreqState) << " (" << myOffFreqCount << ")"<< endl;
}
