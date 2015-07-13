//Copyright(c) Tellabs Transport Group. All rights reserved
/*
#include "../CFG_Mesh.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Mesh::CFG_Mesh(uint32 theIndex):
    CFG_Object(theIndex),
    mySwitchMode(CT_TEL_SwitchMode_None),
    myNbrSlots(NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF)
{
    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        myLinkEnabled[i] = false;
    }
}

CFG_Mesh::~CFG_Mesh(void)
{
}

void CFG_Mesh::SetLinkEnabled(CT_SlotId theSlotId)
{
    // CFG Link Enabled array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
        myLinkEnabled[theSlotId] = true;
}

void CFG_Mesh::SetLinkDisabled(CT_SlotId theSlotId)
{
    // CFG Link Enabled array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
        myLinkEnabled[theSlotId] = false;
}

bool CFG_Mesh::GetLinkStatus(CT_SlotId theSlotId) const
{
    // CFG Link Enabled array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
        return myLinkEnabled[theSlotId];

    return false;
}

void CFG_Mesh::SetSwitchMode(CT_TEL_SwitchMode theMode)
{
    mySwitchMode = theMode;
}

CT_TEL_SwitchMode CFG_Mesh::GetSwitchMode() const
{
    return mySwitchMode;
}

void CFG_Mesh::SetNbrOfSlots(uint8 theNbrSlots)
{
    myNbrSlots = theNbrSlots;
}

uint8 CFG_Mesh::GetNbrOfSlots() const
{
    return myNbrSlots;
}

void CFG_Mesh::Reset(void)
{
    // Initialize all attributes to default values.
    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        myLinkEnabled[i] = false;
    }
    mySwitchMode = CT_TEL_SwitchMode_None;
    myNbrSlots = NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF;
}

ostream& CFG_Mesh::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(mySwitchMode);
    theStream   << FC_InsertVar(myNbrSlots);
    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        theStream   << FC_InsertVar(myLinkEnabled[i]);
    }

    return theStream;
}

istream& CFG_Mesh::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(mySwitchMode);
    theStream   >> FC_ExtractVar(myNbrSlots);
    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        theStream   >> FC_ExtractVar(myLinkEnabled[i]);
    }

    return theStream;
}

FC_Stream& CFG_Mesh::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << mySwitchMode;
    theStream   << myNbrSlots;

    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        theStream   << myLinkEnabled[i];
    }

    return theStream;
}

FC_Stream& CFG_Mesh::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> mySwitchMode;
    theStream   >> myNbrSlots;

    for (int i = 0; i < NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; i++)
    {
        theStream   >> myLinkEnabled[i];
    }

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Mesh::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);


    if (!strncmp(aParam,"mode",4))
    {
        CT_TEL_SwitchMode aMode;
        if (argv[1][0]=='e')
        {
            aMode = CT_TEL_SwitchMode_Mesh;
            SetSwitchMode(aMode);
        }
        else if (argv[1][0]=='d')
        {
            aMode = CT_TEL_SwitchMode_None;
            SetSwitchMode(aMode);
        }
    }
    else if (!strncmp(aParam,"nbr",3))
    {
        SetNbrOfSlots(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"enable",6))
    {
        SetLinkEnabled(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"disable",7))
    {
        SetLinkDisabled(uint8(atoi(argv[1])));
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "MESH <mode>         <e-nable|d-isable> " << endl;
        fc_cout << "MESH <nbr>          <1 to 19> " << endl;
        fc_cout << "MESH <enable>       <SlotId 0-18> " << endl;
        fc_cout << "MESH <disable>      <SlotId 0-18> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Mesh::Display( FC_Stream& theStream )
{
    if ( mySwitchMode == CT_TEL_SwitchMode_Mesh)
        theStream   << "MESH - Mode             [mode]   = MESH " << endl;
    
    else if ( mySwitchMode == CT_TEL_SwitchMode_Cntr_Switch)
        theStream   << "MESH - Mode             [mode]   = UFAB SWITCHED " << endl;
    else if ( mySwitchMode == CT_TEL_SwitchMode_Repeater)
        theStream   << "MESH - Mode             [mode]   = UFAB REPEATER " << endl;
    
    else
        theStream   << "MESH - Mode             [mode]   = None " << endl;

    theStream   << "MESH - Number of Slots  [nbr]    = " << uint32(myNbrSlots) << endl;
    theStream   << "MESH - LINK STATUS = ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_BOOL(myLinkEnabled[i]);

    }
    theStream   << endl;
} */
