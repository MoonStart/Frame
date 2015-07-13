// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OmsDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_OmsDefects::MON_OmsDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myLOSState(false),
    myLOSCount(0),
    myAprState(false),
    myAprCount(0),
    myAltLOSState(false),
    myAltLOSCount(0),
    myAltTwoLOSState(false),
    myAltTwoLOSCount(0),
    myAltThreeLOSState(false),
    myAltThreeLOSCount(0),
    myLOSAfterAmpliState(false),
	myLOSAfterAmpliCount(0),
    myOutputPowerLimitedState(false),
    myOutputPowerLimitedCount(0),
    myOpovldState(false),
    myOpovldCount(0),
    myAopeState(false),
    myAopeCount(0)

{
}

MON_OmsDefects::~MON_OmsDefects()
{
}

void MON_OmsDefects::Reset(void)
{
    MON_Defects::Reset();
    myLOSState = false;
    myLOSCount = 0;
    myAprState = false;
    myAprCount = 0;
    myAltLOSState = false;
    myAltLOSCount = 0;
    myAltTwoLOSState = false;
    myAltTwoLOSCount = 0;
    myAltThreeLOSState = false;
    myAltThreeLOSCount = 0;
    myLOSAfterAmpliState = false;
	myLOSAfterAmpliCount = 0;
    myOutputPowerLimitedState = false;
    myOutputPowerLimitedCount = 0;
    myOpovldState = false;
    myOpovldCount = 0;
    myAopeState = false;
    myAopeCount = 0;

}

void MON_OmsDefects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OMS_LOS_DEFECT:
        *theState = myLOSState;
        *theCount = myLOSCount;
        break;
    case CT_TEL_OMS_APR_DEFECT:
        *theState = myAprState;
        *theCount = myAprCount;
        break;
    case CT_TEL_OMS_ALT_LOS_DEFECT:
        *theState = myAltLOSState;
        *theCount = myAltLOSCount;
        break;
    case CT_TEL_OMS_ALT_TWO_LOS_DEFECT:
        *theState = myAltTwoLOSState;
        *theCount = myAltTwoLOSCount;
        break;
    case CT_TEL_OMS_ALT_THREE_LOS_DEFECT:
        *theState = myAltThreeLOSState;
        *theCount = myAltThreeLOSCount;
        break;
    case CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT:
        *theState = myLOSAfterAmpliState;
        *theCount = myLOSAfterAmpliCount;
        break;
    case CT_TEL_OMS_OUTPUT_POWER_LIMITED_DEFECT:
        *theState = myOutputPowerLimitedState;
        *theCount = myOutputPowerLimitedCount;
        break;
    case CT_TEL_OMS_OPOVLD_DEFECT:
        *theState = myOpovldState;
        *theCount = myOpovldCount;
        break;
    case CT_TEL_OMS_AOPE_DEFECT:
        *theState = myAopeState;
        *theCount = myAopeCount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OmsDefects: unsupported defect");
    }
}

    
bool MON_OmsDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_OMS_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOSState, &myLOSCount);
    case CT_TEL_OMS_APR_DEFECT:
        return UpdateDefect(theState, theTransition, &myAprState, &myAprCount);
    case CT_TEL_OMS_ALT_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAltLOSState, &myAltLOSCount);
    case CT_TEL_OMS_ALT_TWO_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAltTwoLOSState, &myAltTwoLOSCount);
    case CT_TEL_OMS_ALT_THREE_LOS_DEFECT:
        return UpdateDefect(theState, theTransition, &myAltThreeLOSState, &myAltThreeLOSCount);
    case CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT:
        return UpdateDefect(theState, theTransition, &myLOSAfterAmpliState, &myLOSAfterAmpliCount);
    case CT_TEL_OMS_OUTPUT_POWER_LIMITED_DEFECT:
        return UpdateDefect(theState, theTransition, &myOutputPowerLimitedState, &myOutputPowerLimitedCount);
    case CT_TEL_OMS_OPOVLD_DEFECT:
        return UpdateDefect(theState, theTransition, &myOpovldState, &myOpovldCount);
    case CT_TEL_OMS_AOPE_DEFECT:
        return UpdateDefect(theState, theTransition, &myAopeState, &myAopeCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OmsDefects: unsupported defect");
        return false;
    }
}

ostream& MON_OmsDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream   << FC_InsertVar(myLOSState );
    theStream   << FC_InsertVar(myLOSCount );
    theStream   << FC_InsertVar(myAprState );
    theStream   << FC_InsertVar(myAprCount );
    theStream   << FC_InsertVar(myAltLOSState );
    theStream   << FC_InsertVar(myAltLOSCount );
    theStream   << FC_InsertVar(myAltTwoLOSState );
    theStream   << FC_InsertVar(myAltTwoLOSCount );
    theStream   << FC_InsertVar(myAltThreeLOSState );
    theStream   << FC_InsertVar(myAltThreeLOSCount );
    theStream   << FC_InsertVar(myLOSAfterAmpliState );
    theStream   << FC_InsertVar(myLOSAfterAmpliCount );
    theStream   << FC_InsertVar(myOutputPowerLimitedState );
    theStream   << FC_InsertVar(myOutputPowerLimitedCount );
    theStream   << FC_InsertVar(myOpovldState );
    theStream   << FC_InsertVar(myOpovldCount );
    theStream   << FC_InsertVar(myAopeState );
    theStream   << FC_InsertVar(myAopeCount );
    return theStream;
}

istream& MON_OmsDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myLOSState );
    theStream   >> FC_ExtractVar(myLOSCount );
    theStream   >> FC_ExtractVar(myAprState );
    theStream   >> FC_ExtractVar(myAprCount );
    theStream   >> FC_ExtractVar(myAltLOSState );
    theStream   >> FC_ExtractVar(myAltLOSCount );
    theStream   >> FC_ExtractVar(myAltTwoLOSState );
    theStream   >> FC_ExtractVar(myAltTwoLOSCount );
    theStream   >> FC_ExtractVar(myAltThreeLOSState );
    theStream   >> FC_ExtractVar(myAltThreeLOSCount );
    theStream   >> FC_ExtractVar(myLOSAfterAmpliState );
    theStream   >> FC_ExtractVar(myLOSAfterAmpliCount );
    theStream   >> FC_ExtractVar(myOutputPowerLimitedState );
    theStream   >> FC_ExtractVar(myOutputPowerLimitedCount );
    theStream   >> FC_ExtractVar(myOpovldState );
    theStream   >> FC_ExtractVar(myOpovldCount );
    theStream   >> FC_ExtractVar(myAopeState );
    theStream   >> FC_ExtractVar(myAopeCount );
    return theStream;
}

FC_Stream& MON_OmsDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream   << myLOSState ;
    theStream   << myLOSCount ;
    theStream   << myAprState ;
    theStream   << myAprCount ;
    theStream   << myAltLOSState ;
    theStream   << myAltLOSCount ;
    theStream   << myAltTwoLOSState ;
    theStream   << myAltTwoLOSCount ;
    theStream   << myAltThreeLOSState ;
    theStream   << myAltThreeLOSCount ;
    theStream   << myLOSAfterAmpliState ;
    theStream   << myLOSAfterAmpliCount ;
    theStream   << myOutputPowerLimitedState ;
    theStream   << myOutputPowerLimitedCount ;
    theStream   << myOpovldState ;
    theStream   << myOpovldCount ;
    theStream   << myAopeState ;
    theStream   << myAopeCount ;
    return theStream;

}

FC_Stream& MON_OmsDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream   >> myLOSState ;
    theStream   >> myLOSCount ;
    theStream   >> myAprState ;
    theStream   >> myAprCount ;
    theStream   >> myAltLOSState ;
    theStream   >> myAltLOSCount ;
    theStream   >> myAltTwoLOSState ;
    theStream   >> myAltTwoLOSCount ;
    theStream   >> myAltThreeLOSState ;
    theStream   >> myAltThreeLOSCount ;
    theStream   >> myLOSAfterAmpliState ;
    theStream   >> myLOSAfterAmpliCount ;
    theStream   >> myOutputPowerLimitedState ;
    theStream   >> myOutputPowerLimitedCount ;
    theStream   >> myOpovldState ;
    theStream   >> myOpovldCount ;
    theStream   >> myAopeState ;
    theStream   >> myAopeCount ;
    return theStream;

}

void MON_OmsDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "OMS     - OMS-LOS                           = " << DISPLAY_BOOL(myLOSState) << " (" << myLOSCount << ")"<< endl;
    theStream   << "OMS     - Amplifier Power Reduce (APR)      = " << DISPLAY_BOOL(myAprState) << " (" << myAprCount << ")"<< endl;
    theStream   << "OMS     - Alternate OMS-LOS                 = " << DISPLAY_BOOL(myAltLOSState) << " (" << myAltLOSCount << ")"<< endl;
    theStream   << "OMS     - Alternate 2 OMS-LOS               = " << DISPLAY_BOOL(myAltTwoLOSState) << " (" << myAltTwoLOSCount << ")"<< endl;
    theStream   << "OMS     - Alternate 3 OMS-LOS               = " << DISPLAY_BOOL(myAltThreeLOSState) << " (" << myAltThreeLOSCount << ")"<< endl;
    theStream   << "OMS     - LOS After Ampli                   = " << DISPLAY_BOOL(myLOSAfterAmpliState) << " (" << myLOSAfterAmpliCount << ")"<< endl;
    theStream   << "OMS     - Output Power Limited              = " << DISPLAY_BOOL(myOutputPowerLimitedState) << " (" << myOutputPowerLimitedCount << ")"<< endl;
    theStream   << "OMS     - Output Power Overload             = " << DISPLAY_BOOL(myOpovldState) << " (" << myOpovldCount << ")"<< endl;
    theStream   << "OMS     - Aggregate Output Power Exceeded   = " << DISPLAY_BOOL(myAopeState) << " (" << myAopeCount << ")"<< endl;
}

