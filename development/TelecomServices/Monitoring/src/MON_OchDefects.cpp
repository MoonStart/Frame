// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OchDefects::MON_OchDefects(uint32 theIndex):
    MON_Defects(theIndex),
	myDebugTraceDetected(false),
	myDebugTraceDetectedCount(0),
	myLossOfPilotTone(false),
	myLossOfPilotToneCount(0),
    myDetectedTraceId(MON_ID_UNKNOWN),
    myDisableLos(false)
{
}

MON_OchDefects::~MON_OchDefects(void )
{
}

void MON_OchDefects::Reset()
{
    MON_Defects::Reset();
	myDebugTraceDetected = false;
	myDebugTraceDetectedCount = 0;
	myLossOfPilotTone = false;
	myLossOfPilotToneCount = 0;
    myDetectedTraceId=MON_ID_UNKNOWN;
    myDisableLos = false;
}

bool MON_OchDefects::IsLayerInDefects() const
{
    return (myLossOfPilotTone && !myDisableLos) && IsValidated();
}

void MON_OchDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OCH_DEBUG_TRACE_DETECTED_DEFECT:
        *theState = myDebugTraceDetected;
        *theCount = myDebugTraceDetectedCount;
        break;
    case CT_TEL_OCH_LOSS_PTONE_DEFECT:
        *theState = (myLossOfPilotTone && !myDisableLos);
        *theCount = myLossOfPilotToneCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OchDefects: unsupported defect");
    }
}

    
bool MON_OchDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OCH_DEBUG_TRACE_DETECTED_DEFECT:
        return UpdateDefect(theState, theTransition, &myDebugTraceDetected, &myDebugTraceDetectedCount);
    case CT_TEL_OCH_LOSS_PTONE_DEFECT:
        return UpdateDefect(theState, theTransition, &myLossOfPilotTone, &myLossOfPilotToneCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OchDefects: unsupported defect");
        return false;
    }
}


bool MON_OchDefects::SetDetectedId(MON_RelativeTraceId theRelTraceId)
{
    bool hasChanged = false;
    if (myDetectedTraceId != theRelTraceId)
    {
        myDetectedTraceId = theRelTraceId;
        hasChanged = true;
    }
    return hasChanged;
}


MON_RelativeTraceId MON_OchDefects::GetDetectedId() const
{
    return myDetectedTraceId;
}

void MON_OchDefects::DisableLos(bool theDisableLos)
{
    myDisableLos = theDisableLos;
}

ostream& MON_OchDefects::WriteObject(ostream& theStream)
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myDebugTraceDetected)
              << FC_InsertVar(myDebugTraceDetectedCount);
    theStream << FC_InsertVar(myLossOfPilotTone)
              << FC_InsertVar(myLossOfPilotToneCount);
    uint32 aDetectedTraceId = myDetectedTraceId;
    theStream << FC_InsertVar(aDetectedTraceId);
    theStream << FC_InsertVar(myDisableLos);
    return theStream;
}

istream& MON_OchDefects::ReadObject(istream& theStream)
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myDebugTraceDetected)
              >> FC_ExtractVar(myDebugTraceDetectedCount);
    theStream >> FC_ExtractVar(myLossOfPilotTone)
              >> FC_ExtractVar(myLossOfPilotToneCount);
    uint32 aDetectedTraceId;
    theStream >> FC_ExtractVar(aDetectedTraceId);
    myDetectedTraceId = (MON_RelativeTraceId)aDetectedTraceId;
    theStream >> FC_ExtractVar(myDisableLos);
    return theStream;
}

FC_Stream& MON_OchDefects::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myDebugTraceDetected
              >> myDebugTraceDetectedCount;
    theStream >> myLossOfPilotTone
              >> myLossOfPilotToneCount;
    uint32 aDetectedTraceId;
    theStream >> aDetectedTraceId;
    myDetectedTraceId = (MON_RelativeTraceId)aDetectedTraceId;
    theStream >> myDisableLos;
    return theStream;
}

FC_Stream& MON_OchDefects::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myDebugTraceDetected
              << myDebugTraceDetectedCount;
    theStream << myLossOfPilotTone
              << myLossOfPilotToneCount;
    theStream << myDetectedTraceId;
    theStream << myDisableLos;
    return theStream;
}

void MON_OchDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OCH     - LOS OF PTONE                      = " << DISPLAY_BOOL(myLossOfPilotTone) << " (" << myLossOfPilotToneCount << ")"<< endl;
    theStream   << "OCH     - LOS DISABLED                      = " << DISPLAY_BOOL(myDisableLos) << endl;
    theStream   << "OCH     - DEBUG TRACE DETECT                = " << DISPLAY_BOOL(myDebugTraceDetected) << " (" << myDebugTraceDetectedCount << ")" << endl;
    theStream   << "OCH     - DETECTED ID                       = " << DISPLAY_REL_TRACE_ID(myDetectedTraceId) << endl;
}

