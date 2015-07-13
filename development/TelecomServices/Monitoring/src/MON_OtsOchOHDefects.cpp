// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtsOchOHDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OtsOchOHDefects::MON_OtsOchOHDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myOCH_FDIPState(false),
    myOCH_FDIPCount(0),
    myOCH_FDIOState(false),
    myOCH_FDIOCount(0),
    myOCH_OCIState(false),
    myOCH_OCICount(0)
{
}

MON_OtsOchOHDefects::~MON_OtsOchOHDefects()
{
}

void MON_OtsOchOHDefects::Reset(void)
{
    // Initialize all attributes to zero
    MON_Defects::Reset();
    myOCH_FDIPState = false;
    myOCH_FDIPCount = 0;
    myOCH_FDIOState = false;
    myOCH_FDIOCount = 0;
    myOCH_OCIState  = false;
    myOCH_OCICount  = 0;
}

void MON_OtsOchOHDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OCH_FDIP_DEFECT:
        *theState = myOCH_FDIPState;
        *theCount = myOCH_FDIPCount;
        break;
    case CT_TEL_OCH_FDIO_DEFECT:
        *theState = myOCH_FDIOState;
        *theCount = myOCH_FDIOCount;
        break;
    case CT_TEL_OCH_OCI_DEFECT:
        *theState = myOCH_OCIState;
        *theCount = myOCH_OCICount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsOchOHDefects: unsupported defect");
    }
}

    
bool MON_OtsOchOHDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OCH_FDIP_DEFECT:
        return UpdateDefect(theState, theTransition, &myOCH_FDIPState, &myOCH_FDIPCount);
    case CT_TEL_OCH_FDIO_DEFECT:
        return UpdateDefect(theState, theTransition, &myOCH_FDIOState, &myOCH_FDIOCount);
    case CT_TEL_OCH_OCI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOCH_OCIState, &myOCH_OCICount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsOchOHDefects: unsupported defect");
        return false;
    }
}


ostream& MON_OtsOchOHDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myOCH_FDIPState);
    theStream   << FC_InsertVar(myOCH_FDIPCount);
    theStream   << FC_InsertVar(myOCH_FDIOState);
    theStream   << FC_InsertVar(myOCH_FDIOCount);
    theStream   << FC_InsertVar(myOCH_OCIState );
    theStream   << FC_InsertVar(myOCH_OCICount );
    return theStream;
}


istream& MON_OtsOchOHDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myOCH_FDIPState);
    theStream   >> FC_ExtractVar(myOCH_FDIPCount);
    theStream   >> FC_ExtractVar(myOCH_FDIOState);
    theStream   >> FC_ExtractVar(myOCH_FDIOCount);
    theStream   >> FC_ExtractVar(myOCH_OCIState );
    theStream   >> FC_ExtractVar(myOCH_OCICount );
    return theStream;
}


FC_Stream& MON_OtsOchOHDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream   << myOCH_FDIPState;
    theStream   << myOCH_FDIPCount;
    theStream   << myOCH_FDIOState;
    theStream   << myOCH_FDIOCount;
    theStream   << myOCH_OCIState ;
    theStream   << myOCH_OCICount ;
    return theStream;

}


FC_Stream& MON_OtsOchOHDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myOCH_FDIPState;
    theStream   >> myOCH_FDIPCount;
    theStream   >> myOCH_FDIOState;
    theStream   >> myOCH_FDIOCount;
    theStream   >> myOCH_OCIState ;
    theStream   >> myOCH_OCICount ;
    return theStream;

}

void MON_OtsOchOHDefects::Display(FC_Stream& theStream)
{
    theStream   << DISPLAY_BOOL(myOCH_FDIPState) << "(" << myOCH_FDIPCount << ")\t"
                << DISPLAY_BOOL(myOCH_FDIOState) << "(" << myOCH_FDIOCount << ")\t"
                << DISPLAY_BOOL(myOCH_OCIState)  << "(" << myOCH_OCICount  << ")\t"
                << DISPLAY_BOOL(IsValidated()) << endl;
}

