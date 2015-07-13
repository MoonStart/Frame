/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2006  Jai Harpalani
 DESCRIPTION:   TSXC_RsReady  Class Implementation
--------------------------------------------------------------------------*/

#ifndef TSXC_RSREADY_C
#define TSXC_RSREADY_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_RsReady.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>

// *************
// Constructor
// *************
TSXC_RsReady::TSXC_RsReady():
    myReadyFlag(0)
{
    uint8  aPort;

    for(aPort = 0; aPort < XC_MAX_PORT_INTF; aPort++)
    {
        myCfgSigType[aPort] = CT_TEL_SIGNAL_UNKNOWN;
    }
}

// *************
// Destructor
// *************
TSXC_RsReady::~TSXC_RsReady()
{
}

// *************
// Set Methods
// *************
void TSXC_RsReady::SetReadyFlag(bool theFlagValue)
{
    myReadyFlag = theFlagValue;
}

void TSXC_RsReady::SetSignalType(uint8 thePort, CT_TEL_SignalType theSigType)
{
    myCfgSigType[thePort] = theSigType;
}

// *************
// Get Methods
// *************
bool TSXC_RsReady::GetReadyFlag()
{
    return myReadyFlag;
}

CT_TEL_SignalType   TSXC_RsReady::GetSignalType(uint8 thePort)
{
    return myCfgSigType[thePort];
}

// *********************
// Serialization Methods
// *********************

ostream& TSXC_RsReady::WriteObject( ostream& theStream )
{
    uint8  aSignalType;
    uint8  aPort;

    theStream << FC_InsertVar(myReadyFlag);

    for(aPort = 0; aPort < XC_MAX_PORT_INTF; aPort++)
    {
        aSignalType = myCfgSigType[aPort];
        theStream << FC_InsertVar(aSignalType);
    }

    return theStream;
}

istream& TSXC_RsReady::ReadObject( istream& theStream )
{
    uint8  aSignalType;
    uint8  aPort;

    theStream >> FC_ExtractVar(myReadyFlag);

    for(aPort = 0; aPort < XC_MAX_PORT_INTF; aPort++)
    {
        theStream >> FC_ExtractVar(aSignalType);
        myCfgSigType[aPort] = (CT_TEL_SignalType) aSignalType;
    }

    return theStream;
}

FC_Stream& TSXC_RsReady::WriteObjectBinary( FC_Stream& theStream )
{
    uint8  aPort;

    theStream << myReadyFlag;

    for(aPort = 0; aPort < XC_MAX_PORT_INTF; aPort++)
    {
        theStream << (uint8) myCfgSigType[aPort];
    }

    return theStream;
}

FC_Stream& TSXC_RsReady::ReadObjectBinary( FC_Stream& theStream )
{
    uint8  aSignalType;
    uint8  aPort;

    theStream >> myReadyFlag;

    for(aPort = 0; aPort < XC_MAX_PORT_INTF; aPort++)
    {
        theStream >> aSignalType;
        myCfgSigType[aPort] = (CT_TEL_SignalType) aSignalType;
    }

    return theStream;
}

#endif // TSXC_RSREADY_C

