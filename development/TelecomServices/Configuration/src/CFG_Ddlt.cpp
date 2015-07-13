//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Ddlt.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_Ddlt::CFG_Ddlt(uint32 theIndex):
    CFG_Object(theIndex),
    myDdltEnable(false)
{
}

CFG_Ddlt::~CFG_Ddlt(void)
{
}


//This method is used to indicate that the Ddlt facility is configured (for LED)
void CFG_Ddlt::SetDdltEnable(bool theDdltEnable)
{
    myDdltEnable = theDdltEnable;
}

//This method returns the state of the Ddlt facility.
bool CFG_Ddlt::GetDdltEnable() const
{
    return myDdltEnable;
}


void CFG_Ddlt::Reset(void)
{
    // Initialize all attributes to default values.
    myDdltEnable = false;
}

ostream& CFG_Ddlt::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myDdltEnable);

    return theStream;
}

istream& CFG_Ddlt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myDdltEnable);

    return theStream;
}

FC_Stream& CFG_Ddlt::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myDdltEnable;

    return theStream;
}

FC_Stream& CFG_Ddlt::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myDdltEnable;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Ddlt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto DDLTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"ena",3))
    {
        SetDdltEnable(argv[1][0]=='e');
    }
    else
    {
        goto DDLTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

DDLTERROR:
    {
        fc_cout << "ddtl <enable>        <e-nable|d-isable> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Ddlt::Display( FC_Stream& theStream )
{
    theStream   << "Ddlt Transfer  - Enable/Configured    [enable]        = " << DISPLAY_BOOL(myDdltEnable) << endl;
    theStream << endl;
}

