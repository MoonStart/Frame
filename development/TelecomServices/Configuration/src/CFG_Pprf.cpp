//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Pprf.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Pprf::CFG_Pprf(uint32 theIndex):
    CFG_Object(theIndex),
    myMaxReceiveUnits(0),
    myFCS(0),
    myRestartTimer(0),
    myMaxTerminateValue(0),
    myMaxConfigureValue(0),
    myMaxFailureValue(0)
{
}

CFG_Pprf::~CFG_Pprf(void)
{
}



void CFG_Pprf::SetMaxReceiveUnits(uint16 theMaxReceiveUnits)
{
    myMaxReceiveUnits = theMaxReceiveUnits;
}

uint16 CFG_Pprf::GetMaxReceiveUnits() const
{
    return myMaxReceiveUnits;
}

void CFG_Pprf::SetFCS(uint8 theFCS)
{
    myFCS = theFCS;
}

uint8 CFG_Pprf::GetFCS() const
{
    return myFCS;
}

void CFG_Pprf::SetRestartTimer(uint8 theRestartTimer)
{
    myRestartTimer = theRestartTimer;
}

uint8 CFG_Pprf::GetRestartTimer() const
{
    return myRestartTimer;
}


void CFG_Pprf::SetMaxTerminateValue(uint8 theMaxTerminateValue)
{
    myMaxTerminateValue = theMaxTerminateValue;
}

uint8 CFG_Pprf::GetMaxTerminateValue() const
{
    return myMaxTerminateValue;
}

void CFG_Pprf::SetMaxConfigureValue(uint8 theMaxConfigureValue)
{
    myMaxConfigureValue = theMaxConfigureValue;
}

uint8 CFG_Pprf::GetMaxConfigureValue() const
{
    return myMaxConfigureValue;
}

void CFG_Pprf::SetMaxFailureValue(uint8 theMaxFailureValue)
{
    myMaxFailureValue = theMaxFailureValue;
}

uint8 CFG_Pprf::GetMaxFailureValue() const
{
    return myMaxFailureValue;
}




void CFG_Pprf::Reset(void)
{
    // Initialize all attributes to default values.
    myMaxReceiveUnits = 0;
    myFCS = 0;
    myRestartTimer = 0;
    myMaxTerminateValue = 0;
    myMaxConfigureValue = 0;
    myMaxFailureValue = 0;
}

// For Display
ostream& CFG_Pprf::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myMaxReceiveUnits);
    theStream   << FC_InsertVar(myFCS);
    theStream   << FC_InsertVar(myRestartTimer);
    theStream   << FC_InsertVar(myMaxTerminateValue);
    theStream   << FC_InsertVar(myMaxConfigureValue);
    theStream   << FC_InsertVar(myMaxFailureValue);

    return theStream;
}

istream& CFG_Pprf::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myMaxReceiveUnits);
    theStream   >> FC_ExtractVar(myFCS);
    theStream   >> FC_ExtractVar(myRestartTimer);
    theStream   >> FC_ExtractVar(myMaxTerminateValue);
    theStream   >> FC_ExtractVar(myMaxConfigureValue);
    theStream   >> FC_ExtractVar(myMaxFailureValue);

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Pprf::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myMaxReceiveUnits;
    theStream   << myFCS;
    theStream   << myRestartTimer;
    theStream   << myMaxTerminateValue;
    theStream   << myMaxConfigureValue;
    theStream   << myMaxFailureValue;

    return theStream;
}

FC_Stream& CFG_Pprf::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myMaxReceiveUnits;
    theStream   >> myFCS;
    theStream   >> myRestartTimer;
    theStream   >> myMaxTerminateValue;
    theStream   >> myMaxConfigureValue;
    theStream   >> myMaxFailureValue;

    return theStream;
}


FC_CmdProcessor::STATUS CFG_Pprf::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        return PprfError();

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"maxrec",6))
    {
        SetMaxReceiveUnits(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"fcs",3))
    {
        int fcsValue = atoi(argv[1]);

        if ( fcsValue == 16 || fcsValue == 32 )
        {
            SetFCS( (uint8) fcsValue );
        }
        else
        {
            return PprfError();
        }
    }
    else if (!strncmp(aParam,"restar",6))
    {
        SetRestartTimer(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"maxter",6))
    {
        SetMaxTerminateValue(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"maxcon",6))
    {
        SetMaxConfigureValue(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"maxfai",6))
    {
        SetMaxFailureValue(uint8(atoi(argv[1])));
    }
    else
    {
        return PprfError();
    }

    return FC_CmdProcessor::E_SUCCESS;
}


FC_CmdProcessor::STATUS 
CFG_Pprf::PprfError( void )
{
    fc_cout << "pprf maxrec-units   <64-65535>" << endl;
    fc_cout << "pprf fcs            <16 or 32>" << endl;
    fc_cout << "pprf restar-ttimer  <1-10>" << endl;
    fc_cout << "pprf maxter-minate  <2-10>" << endl;
    fc_cout << "pprf maxcon-fig     <4-20>" << endl;
    fc_cout << "pprf maxfai-lure    <2-10>" << endl;
    fc_cout << endl;

    return FC_CmdProcessor::E_FAILURE;
}


void CFG_Pprf::Display( FC_Stream& theStream )
{
    theStream   << "PPRF     - Max Receive Units    [maxrecunits]  = " << uint32(myMaxReceiveUnits) << endl;
    theStream   << "PPRF     - Frame Check Sequence [fcs]          = " << uint32(myFCS) << endl;
    theStream   << "PPRF     - Restart Timer        [restarttimer] = " << uint32(myRestartTimer) << endl;
    theStream   << "PPRF     - Max Terminate Value  [maxterminate] = " << uint32(myMaxTerminateValue) << endl;
    theStream   << "PPRF     - Max Config Value     [maxconfig]    = " << uint32(myMaxConfigureValue) << endl;
    theStream   << "PPRF     - Max Failure Value    [maxfailure]   = " << uint32(myMaxFailureValue) << endl;
}

