//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Sync.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>

CFG_Sync::CFG_Sync(uint32 theIndex):
    CFG_Object(theIndex),
    myTimingMode (CT_TEL_SELF_TIMING)
{
}

CFG_Sync::~CFG_Sync(void)
{
}

void CFG_Sync::SetTimingMode(CT_TEL_TimingMode theTimingMode)
{
    myTimingMode = theTimingMode;
}


CT_TEL_TimingMode CFG_Sync::GetTimingMode() const
{
    return myTimingMode;
}

void CFG_Sync::Reset(void)
{
    // Initialize all attributes to default values.
    myTimingMode = CT_TEL_SELF_TIMING;
}

ostream& CFG_Sync::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    uint32 aTimingMode = myTimingMode;
    theStream   << FC_InsertVar(aTimingMode);

    return theStream;

}

istream& CFG_Sync::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint32 aTimingMode = 0;
    theStream   >> FC_ExtractVar(aTimingMode);
    myTimingMode = (CT_TEL_TimingMode) aTimingMode;

    return theStream;

}

FC_Stream& CFG_Sync::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << (uint32)myTimingMode;

    return theStream;

}

FC_Stream& CFG_Sync::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint32 aTimingMode = 0;
    theStream   >> aTimingMode;
    myTimingMode = (CT_TEL_TimingMode)aTimingMode;

    return theStream;

}

FC_CmdProcessor::STATUS CFG_Sync::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto SYNCERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"tmgmode"))
    {
        SetTimingMode(CFG_STRING_TO_TIMING_MODE(argv[1]));
    }
    else
    {
        goto SYNCERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

SYNCERROR:
    {
        fc_cout << "sync <tmgmode> <l-ine | e-xternal| se-lf | b-ack(loopback) | t-hrough | m-ate | sp-fab> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Sync::Display( FC_Stream& theStream )
{
    theStream   << "SYNC       - Timing Mode         [tmgmode]    = " << DISPLAY_TIMING_MODE(myTimingMode) << endl;
}


