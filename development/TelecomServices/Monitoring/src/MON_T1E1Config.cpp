// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_T1E1Config.h"
#include <BaseClass/FC_TextStream.h>

MON_T1E1Config::MON_T1E1Config(uint32 theIndex):
    MON_Config(theIndex)
{
}

MON_T1E1Config::~MON_T1E1Config(void )
{
}


bool MON_T1E1Config::SetLayerLocked(bool theState)
{
    bool hasChanged = false;
    if (myLayerLocked != theState)
    {
        myLayerLocked = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_T1E1Config::GetLayerLocked() const
{
    return myLayerLocked;
}


void MON_T1E1Config::Reset()
{
    myLayerLocked = false;
    MON_Config::Reset();
}

ostream& MON_T1E1Config::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myLayerLocked);
    return theStream;
}

istream& MON_T1E1Config::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myLayerLocked);
    return theStream;
}

FC_Stream& MON_T1E1Config::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream   << myLayerLocked;
    return theStream;
}

FC_Stream& MON_T1E1Config::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream   >> myLayerLocked;
    return theStream;
}

void MON_T1E1Config::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "T1E1    - Forced Layer Lock [layerlock] = " << DISPLAY_BOOL(myLayerLocked) << endl;
}

FC_CmdProcessor::STATUS MON_T1E1Config::Set(int argc, char** argv)
{
    if (argc < 2)
        goto T1E1ERROR;

    if (!strcmp(argv[0],"layerlock"))
    {
        SetLayerLocked(argv[1][0]=='e');
    }
    else
        goto T1E1ERROR;

    return FC_CmdProcessor::E_SUCCESS;

T1E1ERROR:
    {
        fc_cout << "layerlock <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

