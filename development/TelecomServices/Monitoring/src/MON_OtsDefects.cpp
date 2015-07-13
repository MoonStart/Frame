// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtsDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OtsDefects::MON_OtsDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myOTS_LOSState(false),
    myOTS_LOSCount(0)
{
}

MON_OtsDefects::~MON_OtsDefects()
{
}

void MON_OtsDefects::Reset(void)
{
    // Initialize all attributes to zero
    MON_Defects::Reset();
    myOTS_LOSState = false;
    myOTS_LOSCount = 0;
}

void MON_OtsDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OTS_LOS_DEFECT:
        *theState = myOTS_LOSState;
        *theCount = myOTS_LOSCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsDefects: unsupported defect");
    }
}

    
bool MON_OtsDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OTS_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_LOSState, &myOTS_LOSCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsDefects: unsupported defect");
        return false;
    }
}


ostream& MON_OtsDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myOTS_LOSState );
    theStream   << FC_InsertVar(myOTS_LOSCount );
    return theStream;
}


istream& MON_OtsDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myOTS_LOSState );
    theStream   >> FC_ExtractVar(myOTS_LOSCount );
    return theStream;
}


FC_Stream& MON_OtsDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream   << myOTS_LOSState ;
    theStream   << myOTS_LOSCount ;
    return theStream;

}


FC_Stream& MON_OtsDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myOTS_LOSState ;
    theStream   >> myOTS_LOSCount ;
    return theStream;

}

void MON_OtsDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OTS     - OTS-LOS                           = " << DISPLAY_BOOL(myOTS_LOSState)      << " (" << myOTS_LOSCount << ")"<< endl;
}

bool MON_OtsDefects::IsLayerInDefects() const
{
    return (myOTS_LOSState);
}
