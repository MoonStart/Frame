// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtsOHDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OtsOHDefects::MON_OtsOHDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myOTS_BDIPState(false),
    myOTS_BDIPCount(0),
    myOTS_BDIOState(false),
    myOTS_BDIOCount(0),
    myOTS_BDIState(false),
    myOTS_BDICount(0),
    myOTS_PMIState(false),
    myOTS_PMICount(0),
    myOTS_TIMState(false),
    myOTS_TIMCount(0),
    myOMS_FDIPState(false),
    myOMS_FDIPCount(0),
    myOMS_FDIOState(false),
    myOMS_FDIOCount(0),
    myOMS_PMIState(false),
    myOMS_PMICount(0)
{
}

MON_OtsOHDefects::~MON_OtsOHDefects()
{
}

void MON_OtsOHDefects::Reset(void)
{
    // Initialize all attributes to zero
    MON_Defects::Reset();
    myOTS_BDIPState = false;
    myOTS_BDIPCount = 0;
    myOTS_BDIOState = false;
    myOTS_BDIOCount = 0;
    myOTS_BDIState = false;
    myOTS_BDICount = 0;
    myOTS_PMIState = false;
    myOTS_PMICount = 0;
    myOTS_TIMState = false;
    myOTS_TIMCount = 0;
    myOMS_FDIPState = false;
    myOMS_FDIPCount = 0;
    myOMS_FDIOState = false;
    myOMS_FDIOCount = 0;
    myOMS_PMIState = false;
    myOMS_PMICount = 0;
}

void MON_OtsOHDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OTS_BDIP_DEFECT:
        *theState = myOTS_BDIPState;
        *theCount = myOTS_BDIPCount;
        break;
    case CT_TEL_OTS_BDIO_DEFECT:
        *theState = myOTS_BDIOState;
        *theCount = myOTS_BDIOCount;
        break;
    case CT_TEL_OTS_BDI_DEFECT:
        *theState = myOTS_BDIState;
        *theCount = myOTS_BDICount;
        break;
    case CT_TEL_OTS_PMI_DEFECT:
        *theState = myOTS_PMIState;
        *theCount = myOTS_PMICount;
        break;
    case CT_TEL_OTS_TIM_DEFECT:
        *theState = myOTS_TIMState;
        *theCount = myOTS_TIMCount;
        break;
    case CT_TEL_OMS_FDIP_DEFECT:
        *theState = myOMS_FDIPState;
        *theCount = myOMS_FDIPCount;
        break;
    case CT_TEL_OMS_FDIO_DEFECT:
        *theState = myOMS_FDIOState;
        *theCount = myOMS_FDIOCount;
        break;
    case CT_TEL_OMS_PMI_DEFECT:
        *theState = myOMS_PMIState;
        *theCount = myOMS_PMICount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsDefects: unsupported defect");
    }
}

    
bool MON_OtsOHDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OTS_BDIP_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_BDIPState, &myOTS_BDIPCount);
    case CT_TEL_OTS_BDIO_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_BDIOState, &myOTS_BDIOCount);
    case CT_TEL_OTS_BDI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_BDIState, &myOTS_BDICount);
    case CT_TEL_OTS_PMI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_PMIState, &myOTS_PMICount);
    case CT_TEL_OTS_TIM_DEFECT:
        return UpdateDefect(theState, theTransition, &myOTS_TIMState, &myOTS_TIMCount);
    case CT_TEL_OMS_FDIP_DEFECT:
        return UpdateDefect(theState, theTransition, &myOMS_FDIPState, &myOMS_FDIPCount);
    case CT_TEL_OMS_FDIO_DEFECT:
        return UpdateDefect(theState, theTransition, &myOMS_FDIOState, &myOMS_FDIOCount);
    case CT_TEL_OMS_PMI_DEFECT:
        return UpdateDefect(theState, theTransition, &myOMS_PMIState, &myOMS_PMICount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtsDefects: unsupported defect");
        return false;
    }
}


ostream& MON_OtsOHDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myOTS_BDIPState);
    theStream   << FC_InsertVar(myOTS_BDIPCount);
    theStream   << FC_InsertVar(myOTS_BDIOState);
    theStream   << FC_InsertVar(myOTS_BDIOCount);
    theStream   << FC_InsertVar(myOTS_BDIState);
    theStream   << FC_InsertVar(myOTS_BDICount);
    theStream   << FC_InsertVar(myOTS_PMIState );
    theStream   << FC_InsertVar(myOTS_PMICount );
    theStream   << FC_InsertVar(myOTS_TIMState );
    theStream   << FC_InsertVar(myOTS_TIMCount );
    theStream   << FC_InsertVar(myOMS_FDIPState);
    theStream   << FC_InsertVar(myOMS_FDIPCount);
    theStream   << FC_InsertVar(myOMS_FDIOState);
    theStream   << FC_InsertVar(myOMS_FDIOCount);
    theStream   << FC_InsertVar(myOMS_PMIState );
    theStream   << FC_InsertVar(myOMS_PMICount );
    return theStream;
}


istream& MON_OtsOHDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myOTS_BDIPState);
    theStream   >> FC_ExtractVar(myOTS_BDIPCount);
    theStream   >> FC_ExtractVar(myOTS_BDIOState);
    theStream   >> FC_ExtractVar(myOTS_BDIOCount);
    theStream   >> FC_ExtractVar(myOTS_BDIState);
    theStream   >> FC_ExtractVar(myOTS_BDICount);
    theStream   >> FC_ExtractVar(myOTS_PMIState );
    theStream   >> FC_ExtractVar(myOTS_PMICount );
    theStream   >> FC_ExtractVar(myOTS_TIMState );
    theStream   >> FC_ExtractVar(myOTS_TIMCount );
    theStream   >> FC_ExtractVar(myOMS_FDIPState);
    theStream   >> FC_ExtractVar(myOMS_FDIPCount);
    theStream   >> FC_ExtractVar(myOMS_FDIOState);
    theStream   >> FC_ExtractVar(myOMS_FDIOCount);
    theStream   >> FC_ExtractVar(myOMS_PMIState );
    theStream   >> FC_ExtractVar(myOMS_PMICount );
    return theStream;
}


FC_Stream& MON_OtsOHDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream   << myOTS_BDIPState;
    theStream   << myOTS_BDIPCount;
    theStream   << myOTS_BDIOState;
    theStream   << myOTS_BDIOCount;
    theStream   << myOTS_BDIState;
    theStream   << myOTS_BDICount;
    theStream   << myOTS_PMIState ;
    theStream   << myOTS_PMICount ;
    theStream   << myOTS_TIMState ;
    theStream   << myOTS_TIMCount ;
    theStream   << myOMS_FDIPState;
    theStream   << myOMS_FDIPCount;
    theStream   << myOMS_FDIOState;
    theStream   << myOMS_FDIOCount;
    theStream   << myOMS_PMIState ;
    theStream   << myOMS_PMICount ;
    return theStream;

}


FC_Stream& MON_OtsOHDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myOTS_BDIPState;
    theStream   >> myOTS_BDIPCount;
    theStream   >> myOTS_BDIOState;
    theStream   >> myOTS_BDIOCount;
    theStream   >> myOTS_BDIState;
    theStream   >> myOTS_BDICount;
    theStream   >> myOTS_PMIState ;
    theStream   >> myOTS_PMICount ;
    theStream   >> myOTS_TIMState ;
    theStream   >> myOTS_TIMCount ;
    theStream   >> myOMS_FDIPState;
    theStream   >> myOMS_FDIPCount;
    theStream   >> myOMS_FDIOState;
    theStream   >> myOMS_FDIOCount;
    theStream   >> myOMS_PMIState ;
    theStream   >> myOMS_PMICount ;
    return theStream;

}

void MON_OtsOHDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OTS     - OTS-TIM                           = " << DISPLAY_BOOL(myOTS_TIMState)      << " (" << myOTS_TIMCount << ")"<< endl;
    theStream   << "OTS     - OTS-BDIP                          = " << DISPLAY_BOOL(myOTS_BDIPState)     << " (" << myOTS_BDIPCount << ")"<< endl;
    theStream   << "OTS     - OTS-BDIO                          = " << DISPLAY_BOOL(myOTS_BDIOState)     << " (" << myOTS_BDIOCount << ")"<< endl;
    theStream   << "OTS     - OTS-BDI                           = " << DISPLAY_BOOL(myOTS_BDIState)      << " (" << myOTS_BDICount << ")"<< endl;
    theStream   << "OTS     - OTS-PMI                           = " << DISPLAY_BOOL(myOTS_PMIState)      << " (" << myOTS_PMICount << ")"<< endl;
    theStream   << "OTS     - OMS-FDIP                          = " << DISPLAY_BOOL(myOMS_FDIPState)     << " (" << myOMS_FDIPCount << ")"<< endl;
    theStream   << "OTS     - OMS-FDIO                          = " << DISPLAY_BOOL(myOMS_FDIOState)     << " (" << myOMS_FDIOCount << ")"<< endl;
    theStream   << "OTS     - OMS-PMI                           = " << DISPLAY_BOOL(myOMS_PMIState)      << " (" << myOMS_PMICount << ")"<< endl;
}

bool MON_OtsOHDefects::IsLayerInDefects() const
{
    return (myOTS_TIMState);
}
