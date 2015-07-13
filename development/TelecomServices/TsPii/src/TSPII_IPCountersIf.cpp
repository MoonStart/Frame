/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Simon Cadieux, 2003/06/12
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_IPCountersIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "PII_Network.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_IPCountersIf::TSPII_IPCountersIf(bool theDefault) :
    TSPII_BaseIf(theDefault),
    mySimulationFlag(false)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_IPCountersIf::~TSPII_IPCountersIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_IPCountersIf::Reset()
{
    TSPII_BaseIf::Reset();

    myICMP_DestUnreachableReceived = 0;
    myICMP_DestUnreachableTransmitted = 0;
    myICMP_ErrorsReceived = 0;
    myICMP_TTLExceededReceived = 0;
    myIP_AddressErrorsReceived = 0;
    myIP_DiscardsReceived = 0;
    myIP_DiscardsTransmitted = 0;
    myIP_HeaderErrorsReceived = 0;
    myIP_NoRoutesTransmitted = 0;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_IPCountersIf::UpdateCounters()
{
    UpdateValues();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_IPCountersIf::UpdateValues()
{
    if (!mySimulationFlag)
    {
        PII_NetworkCounters aNetworkCounters;
        PII_Network::GetNetworkCounters(aNetworkCounters);

        myICMP_DestUnreachableReceived = aNetworkCounters.ICMP_DestUnreachableReceived;
        myICMP_DestUnreachableTransmitted = aNetworkCounters.ICMP_DestUnreachableTransmitted;
        myICMP_ErrorsReceived = aNetworkCounters.ICMP_ErrorsReceived;
        myICMP_TTLExceededReceived = aNetworkCounters.ICMP_TTLExceededReceived;
        myIP_AddressErrorsReceived = aNetworkCounters.IP_AddressErrorsReceived;
        myIP_DiscardsReceived = aNetworkCounters.IP_DiscardsReceived;
        myIP_DiscardsTransmitted = aNetworkCounters.IP_DiscardsTransmitted;
        myIP_HeaderErrorsReceived = aNetworkCounters.IP_HeaderErrorsReceived;
        myIP_NoRoutesTransmitted = aNetworkCounters.IP_NoRoutesTransmitted;
    }
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetICMP_DestUnreachableReceived()
{
    return myICMP_DestUnreachableReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetICMP_DestUnreachableTransmitted()
{
    return myICMP_DestUnreachableTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetICMP_ErrorsReceived()
{
    return myICMP_ErrorsReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetICMP_TTLExceededReceived()
{
    return myICMP_TTLExceededReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetIP_AddressErrorsReceived()
{
    return myIP_AddressErrorsReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetIP_DiscardsReceived()
{
    return myIP_DiscardsReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetIP_DiscardsTransmitted()
{
    return myIP_DiscardsTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetIP_HeaderErrorsReceived()
{
    return myIP_HeaderErrorsReceived;
}

///////////////////////////////////////////////////////////////////////////////
int TSPII_IPCountersIf::GetIP_NoRoutesTransmitted() 
{
    return myIP_NoRoutesTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_IPCountersIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();

    theStream << myICMP_DestUnreachableReceived;
    theStream << myICMP_DestUnreachableTransmitted;
    theStream << myICMP_ErrorsReceived;
    theStream << myICMP_TTLExceededReceived;
    theStream << myIP_AddressErrorsReceived;
    theStream << myIP_DiscardsReceived;
    theStream << myIP_DiscardsTransmitted;
    theStream << myIP_HeaderErrorsReceived;
    theStream << myIP_NoRoutesTransmitted;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_IPCountersIf::ReadObjectBinary(FC_Stream & theStream)
{
    theStream >> myICMP_DestUnreachableReceived;
    theStream >> myICMP_DestUnreachableTransmitted;
    theStream >> myICMP_ErrorsReceived;
    theStream >> myICMP_TTLExceededReceived;
    theStream >> myIP_AddressErrorsReceived;
    theStream >> myIP_DiscardsReceived;
    theStream >> myIP_DiscardsTransmitted;
    theStream >> myIP_HeaderErrorsReceived;
    theStream >> myIP_NoRoutesTransmitted;

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_IPCountersIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();

    theStream << FC_InsertVar(myICMP_DestUnreachableReceived);
    theStream << FC_InsertVar(myICMP_DestUnreachableTransmitted);
    theStream << FC_InsertVar(myICMP_ErrorsReceived);
    theStream << FC_InsertVar(myICMP_TTLExceededReceived);
    theStream << FC_InsertVar(myIP_AddressErrorsReceived);
    theStream << FC_InsertVar(myIP_DiscardsReceived);
    theStream << FC_InsertVar(myIP_DiscardsTransmitted);
    theStream << FC_InsertVar(myIP_HeaderErrorsReceived);
    theStream << FC_InsertVar(myIP_NoRoutesTransmitted);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_IPCountersIf::ReadObject(istream & theStream)
{
    theStream >> FC_ExtractVar(myICMP_DestUnreachableReceived);
    theStream >> FC_ExtractVar(myICMP_DestUnreachableTransmitted);
    theStream >> FC_ExtractVar(myICMP_ErrorsReceived);
    theStream >> FC_ExtractVar(myICMP_TTLExceededReceived);
    theStream >> FC_ExtractVar(myIP_AddressErrorsReceived);
    theStream >> FC_ExtractVar(myIP_DiscardsReceived);
    theStream >> FC_ExtractVar(myIP_DiscardsTransmitted);
    theStream >> FC_ExtractVar(myIP_HeaderErrorsReceived);
    theStream >> FC_ExtractVar(myIP_NoRoutesTransmitted);

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_IPCountersIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();

    theStream << "  TCP/IP COUNTERS" << endl;
    theStream << "      ICMP Destination Unreachable Received    = " << myICMP_DestUnreachableReceived << endl;
    theStream << "      ICMP Destination Unreachable Transmitted = " << myICMP_DestUnreachableTransmitted << endl;
    theStream << "      ICMP Errors Received                     = " << myICMP_ErrorsReceived << endl;
    theStream << "      ICMP Time To Live Exceeded Received      = " << myICMP_TTLExceededReceived << endl;
    theStream << "      IP Address Errors Received               = " << myIP_AddressErrorsReceived << endl;
    theStream << "      IP Input Packets Discarded               = " << myIP_DiscardsReceived << endl;
    theStream << "      IP Output Packets Discarded              = " << myIP_DiscardsTransmitted << endl;
    theStream << "      IP Header Errors Received                = " << myIP_HeaderErrorsReceived << endl;
    theStream << "      IP Output Packets Discarded No Route     = " << myIP_NoRoutesTransmitted << endl;

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_IPCountersIf::Set(int argc, char ** argv)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_IPCountersIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if (argc == 1 && strcmp(argv[0], "on") == 0)
    {
        mySimulationFlag = true;
    }
    else if (argc == 1 && strcmp(argv[0], "off") == 0)
    {
        mySimulationFlag = false;
    }
    else if (argc == 2 && strcmp(argv[0], "ICMPDestUnrRx") == 0)
    {
        myICMP_DestUnreachableReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "ICMPDestUnrTx") == 0)
    {
        myICMP_DestUnreachableTransmitted = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "ICMPErrRx") == 0)
    {
        myICMP_ErrorsReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "ICMPTTLExRx") == 0)
    {
        myICMP_TTLExceededReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "IPAddrErrRx") == 0)
    {
        myIP_AddressErrorsReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "IPInPackDisc") == 0)
    {
        myIP_DiscardsReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "IPOutPackDisc") == 0)
    {
        myIP_DiscardsTransmitted = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "IPHeaderErrRx") == 0)
    {
        myIP_HeaderErrorsReceived = atoi(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "IPOutPDiscNoRte") == 0)
    {
        myIP_NoRoutesTransmitted = atoi(argv[1]);
    }
    else
    {
        printUsage = true;
    }

    if (printUsage)
    {
        fc_cout << "Usage: tspii simip ...     " << endl;
        fc_cout << "    <on|off>               " << endl;
        fc_cout << "    ICMPDestUnrRx   <value>" << endl;
        fc_cout << "    ICMPDestUnrTx   <value>" << endl;
        fc_cout << "    ICMPErrRx       <value>" << endl;
        fc_cout << "    ICMPTTLExRx     <value>" << endl;
        fc_cout << "    IPAddrErrRx     <value>" << endl;
        fc_cout << "    IPInPackDisc    <value>" << endl;
        fc_cout << "    IPOutPackDisc   <value>" << endl;
        fc_cout << "    IPHeaderErrRx   <value>" << endl;
        fc_cout << "    IPOutPDiscNoRte <value>" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_IPCountersIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
