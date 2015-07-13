// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchMainDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OchMainDefects::MON_OchMainDefects(uint32 theIndex):
    MON_Defects(theIndex),
	myChannelFailDefects(false),
	myChannelFailDefectsCount(0)
{
}

MON_OchMainDefects::~MON_OchMainDefects(void )
{
}

void MON_OchMainDefects::Reset()
{
    MON_Defects::Reset();
	myChannelFailDefects = false;
    myChannelFailDefectsCount = 0;
}

bool MON_OchMainDefects::IsLayerInDefects() const
{
    return false;
}

bool MON_OchMainDefects::IsLayerInDefectsNTA() const
{
    return (myChannelFailDefects);
}

void MON_OchMainDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OCH_CHANNEL_FAIL_DEFECT:
        *theState = myChannelFailDefects;
        *theCount = myChannelFailDefectsCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OchMainDefects: unsupported defect");
    }
}

    
bool MON_OchMainDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OCH_CHANNEL_FAIL_DEFECT:
        return UpdateDefect(theState, theTransition, &myChannelFailDefects, &myChannelFailDefectsCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OchDefects: unsupported defect");
        return false;
    }
}

ostream& MON_OchMainDefects::WriteObject(ostream& theStream)
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myChannelFailDefects);
    theStream << FC_InsertVar(myChannelFailDefectsCount);
    return theStream;
}

istream& MON_OchMainDefects::ReadObject(istream& theStream)
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myChannelFailDefects);
    theStream >> FC_ExtractVar(myChannelFailDefectsCount);
    return theStream;
}

FC_Stream& MON_OchMainDefects::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myChannelFailDefects;
    theStream >> myChannelFailDefectsCount;
    return theStream;
}

FC_Stream& MON_OchMainDefects::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myChannelFailDefects;
    theStream << myChannelFailDefectsCount;
    return theStream;
}

void MON_OchMainDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OCH     - CHANNEL FAIL DEFECT               = " << DISPLAY_BOOL(myChannelFailDefects) << " (" << myChannelFailDefectsCount << ")"<< endl;
}

