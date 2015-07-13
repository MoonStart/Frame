/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/19
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

// Used by TSPII_UpdateAction to return significant instance name
const char*     gTspiiSlotName[] =
{
    "Invalid", "Slot1",  "Slot2",  "Slot3",  "Slot4",  "Slot5",  "Slot6",
    "Slot7",   "Slot8",  "Slot9",  "Slot10", "Slot11", "Slot12", "Slot13",
    "Slot14",  "Slot15", "Slot16", "Slot17", "Slot18", "Slot19"
};

const char*     gTspiiPumpName[] =
{
    "Invalid", "Pump1", "Pump2"
};

///////////////////////////////////////////////////////////////////////////////
TSPII_BaseIf::TSPII_BaseIf(bool theDefault) :
    FC_BbObject(),
    itsDefault(theDefault)
{
}

///////////////////////////////////////////////////////////////////////////////
TSPII_BaseIf::~TSPII_BaseIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseIf::UpdateValues()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseIf::Reset()
{
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_BaseIf::IsDefault() const
{
    return itsDefault;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_BaseIf::WriteObjectBinary(FC_Stream & theStream)
{
    theStream << itsDefault;
    return theStream;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_BaseIf::ReadObjectBinary(FC_Stream & theStream)
{
    theStream >> itsDefault;
    return theStream;
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_BaseIf::WriteObject(ostream & theStream)
{
    theStream << FC_InsertVar(itsDefault);
    return theStream;
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_BaseIf::ReadObject(istream & theStream)
{
    theStream >> FC_ExtractVar(itsDefault);
    return theStream;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseIf::Display(FC_Stream & theStream)
{
    // Availability
    theStream << "    BASE\n";
    theStream << "      Default               = " << TEXT_ON_OFF(itsDefault) << endl;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    theStream << "    Reserved for special target specific display." << endl;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_BaseIf::Set(int argc, char ** argv)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_BaseIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "default") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            itsDefault = false;
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            itsDefault = true;
        }
        else
        {
            printUsage = true;
        }
    }    
    else
    {
        printUsage = true;
    }
    if (printUsage)
    {
        fc_cout << "    default         <on|off>" << endl;
    }
    return printUsage;
}
