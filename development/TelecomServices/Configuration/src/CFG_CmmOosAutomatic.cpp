/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_CmmOosAutomatic.h
 *    DATE:          11/16/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Configuration
 *    OVERVIEW:      CMM Out-of-service object
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#include "../CFG_CmmOosAutomatic.h"
#include <BaseClass/FC_TextStream.h>

////////////////////////////////////////////////////////////////////////////////
CFG_CmmOosAutomatic::CFG_CmmOosAutomatic(uint32 theIndex) :
    CFG_Object(theIndex),
    myAmplifierShutdown(false)
{
}

////////////////////////////////////////////////////////////////////////////////
CFG_CmmOosAutomatic::~CFG_CmmOosAutomatic()
{
}

////////////////////////////////////////////////////////////////////////////////
bool CFG_CmmOosAutomatic::GetAmplifierShutdown() const
{
    return(myAmplifierShutdown);
}

////////////////////////////////////////////////////////////////////////////////
bool CFG_CmmOosAutomatic::SetAmplifierShutdown(bool theState)
{
    bool hasChanged = false;
    if (myAmplifierShutdown != theState)
    {
        myAmplifierShutdown = theState;
        hasChanged = true;
    }
    return hasChanged;
}

////////////////////////////////////////////////////////////////////////////////
FC_Stream & CFG_CmmOosAutomatic::WriteObjectBinary(FC_Stream & theStream)
{
    theStream << myAmplifierShutdown;
    return theStream;
}

////////////////////////////////////////////////////////////////////////////////
FC_Stream & CFG_CmmOosAutomatic::ReadObjectBinary(FC_Stream & theStream)
{
    theStream >> myAmplifierShutdown;
    return theStream;
}

////////////////////////////////////////////////////////////////////////////////
ostream & CFG_CmmOosAutomatic::WriteObject(ostream & theStream)
{
    theStream << FC_InsertVar(myAmplifierShutdown);
    return theStream;
}

////////////////////////////////////////////////////////////////////////////////
istream & CFG_CmmOosAutomatic::ReadObject(istream & theStream)
{
    theStream >> FC_ExtractVar(myAmplifierShutdown);
    return theStream;
}

////////////////////////////////////////////////////////////////////////////////
void CFG_CmmOosAutomatic::Menu(int argc, char ** argv)
{
}

void CFG_CmmOosAutomatic::Display(FC_Stream& theStream)
{
    theStream << "myAmplifierShutdown = " << DISPLAY_BOOL(myAmplifierShutdown) << endl;
}
