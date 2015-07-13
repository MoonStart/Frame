/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds March 2008
 DESCRIPTION:Definition of the class TSPII_MacIf. Models the Level 2
             switching and bandwidth management termination entity.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_L2If.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>
 
using namespace TSPII_L2;

///////////////////////////////////////////////////////////////////////////////
TSPII_L2If::TSPII_L2If(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_L2If::~TSPII_L2If()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::RefreshGet()
{
    // Monitoring attributes
    
    // Configuration attributes
    itsCommittedInfoRate = GetCommittedInfoRate();
    itsCommittedBurstSize = GetCommittedBurstSize();
    itsExcessBurstSize = GetExcessBurstSize();
    itsExcessInfoRate = GetExcessInfoRate();
    itsColorMode = GetColorMode();
    itsMeterType = GetMeterType();
    itsPortMode = GetPortMode();
    itsPVID = GetPVID();
    itsTPID = GetTPID();
    if (TSPII_L2::UNKNOWN  != itsTagMode)
    {
        if(GetTagmode())
            itsTagMode = TSPII_L2::TAGGED;
        else
            itsTagMode = TSPII_L2::UNTAGGED;
    }

    itsLACPMode = GetLACPMode();
    itsLinkOAMMode = GetLinkOAMMode();
    itsDot1XMode = GetDot1XMode();
    itsELMIMode = GetELMIMode();
    itsLLDPMode = GetLLDPMode();
    //itsGARPMode = GetGARPMode();

    itsPortLacpPriority  = GetPortLacpPriority();
    itsPortLacpPartiMode = GetPortLacpPartiMode();
    itsMateLacpPriority  = GetMateLacpPriority();
    itsMateLacpPartiMode = GetMateLacpPartiMode();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::RefreshSet()
{
    // Configuration attributes
    SetCommittedInfoRate(itsCommittedInfoRate);
    SetCommittedBurstSize(itsCommittedBurstSize);
    SetExcessBurstSize(itsExcessBurstSize);
    SetExcessInfoRate(itsExcessInfoRate);
    SetColorMode(itsColorMode);
    SetMeterType(itsMeterType);
    SetPortMode(itsPortMode);
    SetPVID(itsPVID);
    SetTPID(itsTPID);
    if (itsTagMode == TSPII_L2::TAGGED)
    {
        SetTagmode(true);
    }
    else if (itsTagMode == TSPII_L2::UNTAGGED)
    {
        SetTagmode(false);
    }

    SetLACPMode(itsLACPMode);
    SetLinkOAMMode(itsLinkOAMMode);
    SetDot1XMode(itsDot1XMode);
    SetELMIMode(itsELMIMode);
    SetLLDPMode(itsLLDPMode);
    //SetGARPMode(itsGARPMode);

    SetPortLacpPriority(itsPortLacpPriority);
    SetPortLacpPartiMode(itsPortLacpPartiMode);
    SetMateLacpPriority(itsMateLacpPriority);
    SetMateLacpPartiMode(itsMateLacpPartiMode);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::Reset()
{
    TSPII_BaseIf::Reset();
    
    // Monitoring attributes
    
    // Configuration attributes
    itsCommittedInfoRate = 0;
    itsCommittedBurstSize = 0;
    itsExcessBurstSize = 0;
    itsExcessInfoRate = 0;
    itsColorMode = CT_TEL_BW_CM_UNKNOWN;
    itsMeterType = CT_TEL_BW_METERTYPE_UNKNOWN;
    itsPortMode = CT_TEL_PortMode_Undefined;
    // itsPVID = TSPII_PVID_DEFAULT; 
    itsPVID = TSPII_PVID_UNDEFINED; 
    itsTPID = TSPII_TPID_UNDEFINED;
    itsTagMode = TSPII_L2::UNKNOWN;
    itsLACPMode = false;
    itsLinkOAMMode = false;
    itsDot1XMode = false;
    itsELMIMode = false;
    itsLLDPMode = false;
    //itsGARPMode = false;

    itsPortLacpPriority  = 0;;
    itsPortLacpPartiMode = CT_TEL_LacpPartiMode_UNKNOWN;
    itsMateLacpPriority  = 0;;
    itsMateLacpPartiMode = CT_TEL_LacpPartiMode_UNKNOWN;
}
    
///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetCommittedInfoRate(uint32 theRate)
{
    itsCommittedInfoRate = theRate;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetCommittedInfoRate() const
{
    return itsCommittedInfoRate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetCommittedBurstSize(uint32 theSize)
{
    itsCommittedBurstSize = theSize;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetCommittedBurstSize() const
{
    return itsCommittedBurstSize;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetExcessBurstSize(uint32 theSize)
{
    itsExcessBurstSize = theSize;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetExcessBurstSize() const
{
    return itsExcessBurstSize;   
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetExcessInfoRate(uint32 theSize)
{
    itsExcessInfoRate = theSize;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetExcessInfoRate() const
{
    return itsExcessInfoRate;   
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetColorMode(CT_TEL_BW_CM theMode)
{
    itsColorMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BW_CM TSPII_L2If::GetColorMode() const
{
    return itsColorMode;   
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetMeterType(CT_TEL_BW_METERTYPE theMode)
{
    itsMeterType = theMode;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetPVID() const
{
    return itsPVID;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetPVID(uint32 thePVID)
{

    itsPVID = thePVID;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetTagmode() const
{
    bool rc = false;

    if (itsTagMode == TSPII_L2::TAGGED)
    {
        rc = true;
    }
    return rc;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetTagmode(bool theTagmode)
{
    if (theTagmode)
    {
        itsTagMode = TSPII_L2::TAGGED;
    }
    else
    {
        itsTagMode = TSPII_L2::UNTAGGED;
    }
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_L2If::GetTPID() const
{
    return itsTPID;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetTPID(uint32 theTPID)
{
    itsTPID = theTPID;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_L2If::GetPortMode() const
{
    return itsPortMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetPortMode(uint8 thePortMode)
{
    if (CT_TEL_PortMode_Undefined != thePortMode)
    {
        itsPortMode = thePortMode;
    }
}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_BW_METERTYPE TSPII_L2If::GetMeterType() const
{
    return itsMeterType;   
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetLACPMode() const
{
    return itsLACPMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetLACPMode(bool theLACPMode)
{
    itsLACPMode = theLACPMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetLinkOAMMode() const
{
    return itsLinkOAMMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetLinkOAMMode(bool theLinkOAMMode)
{
    itsLinkOAMMode = theLinkOAMMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetDot1XMode() const
{
    return itsDot1XMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetDot1XMode(bool theDot1XMode)
{
    itsDot1XMode = theDot1XMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetELMIMode() const
{
    return itsELMIMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetELMIMode(bool theELMIMode)
{
    itsELMIMode = theELMIMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::GetLLDPMode() const
{
    return itsLLDPMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetLLDPMode(bool theLLDPMode)
{
    itsLLDPMode = theLLDPMode;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_L2If::GetPortLacpPriority() const
{
    return itsPortLacpPriority;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetPortLacpPriority(uint16 theLacpPriority)
{
    itsPortLacpPriority = theLacpPriority;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_LacpPartiMode TSPII_L2If::GetPortLacpPartiMode() const
{
    return itsPortLacpPartiMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetPortLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode)
{
    itsPortLacpPartiMode = theLacpPartiMode;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_L2If::GetMateLacpPriority() const
{
    return itsMateLacpPriority;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetMateLacpPriority(uint16 theLacpPriority)
{
    itsMateLacpPriority = theLacpPriority;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_LacpPartiMode TSPII_L2If::GetMateLacpPartiMode() const
{
    return itsMateLacpPartiMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::SetMateLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode)
{
    itsMateLacpPartiMode = theLacpPartiMode;
}

///////////////////////////////////////////////////////////////////////////////
//bool TSPII_L2If::GetGARPMode() const
//{
//    return itsGARPMode;
//}

///////////////////////////////////////////////////////////////////////////////
//void TSPII_L2If::SetGARPMode(bool theGARPMode)
//{
//    itsGARPMode = theGARPMode;
//}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_L2If::WriteObjectBinary(FC_Stream & theStream)
{
//    int     aTemp;
    int     aColormode;
    int     aMeterType;
    int     aPartiMode;

    // Update H/W
    UpdateValues();
    RefreshGet();
  
    // Monitoring attributes

    // Configuration attributes
    theStream << itsCommittedInfoRate;
    theStream << itsCommittedBurstSize;
    theStream << itsExcessBurstSize;
    theStream << itsExcessInfoRate;
    aColormode = itsColorMode;
    theStream << aColormode;
    aMeterType = itsMeterType;
    theStream << aMeterType;
    theStream << itsPortMode;
    theStream << itsPVID;
    theStream << itsTPID;
    theStream << itsTagMode;
    theStream << itsLACPMode;
    theStream << itsLinkOAMMode;
    theStream << itsDot1XMode;
    theStream << itsELMIMode;
    theStream << itsLLDPMode;
    //theStream << itsGARPMode;
    theStream << itsPortLacpPriority;
    aPartiMode = int(itsPortLacpPartiMode);
    theStream << aPartiMode;
    theStream << itsMateLacpPriority;
    aPartiMode = int(itsMateLacpPartiMode);
    theStream << aPartiMode;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_L2If::ReadObjectBinary(FC_Stream & theStream)
{   
//    int     aTemp;
    int     aColormode;
    int     aMeterType;
    int     aTagMode;
    int     aPartiMode;

    // Monitoring attributes
    
    // Configuration attributes
    theStream >> itsCommittedInfoRate;
    theStream >> itsCommittedBurstSize;
    theStream >> itsExcessBurstSize;
    theStream >> itsExcessInfoRate;
    theStream >> aColormode;
    itsColorMode = (CT_TEL_BW_CM) aColormode;
    theStream >> aMeterType;
    itsMeterType = (CT_TEL_BW_METERTYPE) aMeterType;
    theStream >> itsPortMode;
    theStream >> itsPVID;
    theStream >> itsTPID;
    theStream >> aTagMode;
    itsTagMode = (TSPII_L2::Enum)aTagMode;
    theStream >> itsLACPMode;
    theStream >> itsLinkOAMMode;
    theStream >> itsDot1XMode;
    theStream >> itsELMIMode;
    theStream >> itsLLDPMode;
    //theStream >> itsGARPMode;
    theStream >> itsPortLacpPriority;
    theStream >> aPartiMode;
    itsPortLacpPartiMode = (CT_TEL_LacpPartiMode) aPartiMode;
    theStream >> itsMateLacpPriority;
    theStream >> aPartiMode;
    itsMateLacpPartiMode = (CT_TEL_LacpPartiMode) aPartiMode;

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_L2If::WriteObject(ostream & theStream)
{
    int     aTemp;
    int     aPartiMode;

    // Update H/W
    UpdateValues();
    RefreshGet();
    
    // Monitoring attributes

    // Configuration attributes
    theStream << FC_InsertVar(itsCommittedInfoRate);
    theStream << FC_InsertVar(itsCommittedBurstSize);
    theStream << FC_InsertVar(itsExcessBurstSize);
    theStream << FC_InsertVar(itsExcessInfoRate);
    aTemp = itsColorMode;
    theStream << FC_InsertVar(aTemp);
    aTemp = itsMeterType;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsPortMode);
    theStream << FC_InsertVar(itsPVID);
    theStream << FC_InsertVar(itsTPID);
    aTemp = itsTagMode;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsLACPMode);
    theStream << FC_InsertVar(itsLinkOAMMode);
    theStream << FC_InsertVar(itsDot1XMode);
    theStream << FC_InsertVar(itsELMIMode);
    theStream << FC_InsertVar(itsLLDPMode);
    //theStream << FC_InsertVar(itsGARPMode);
    theStream << FC_InsertVar(itsPortLacpPriority);
    aPartiMode = int(itsPortLacpPartiMode);
    theStream << FC_InsertVar(aPartiMode);
    theStream << FC_InsertVar(itsMateLacpPriority);
    aPartiMode = int(itsMateLacpPartiMode);
    theStream << FC_InsertVar(aPartiMode);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_L2If::ReadObject(istream & theStream)
{
    int     aTemp;
    int     aPartiMode;
    
    // Monitoring attributes
    
    // Configuration attributes
    theStream >> FC_ExtractVar(itsCommittedInfoRate);
    theStream >> FC_ExtractVar(itsCommittedBurstSize);
    theStream >> FC_ExtractVar(itsExcessBurstSize);
    theStream >> FC_ExtractVar(itsExcessInfoRate);
    theStream >> FC_ExtractVar(aTemp);
    itsColorMode = (CT_TEL_BW_CM) aTemp;
    theStream >> FC_ExtractVar(aTemp);
    itsMeterType = (CT_TEL_BW_METERTYPE) aTemp;
    theStream >> FC_ExtractVar(itsPortMode);
    theStream >> FC_ExtractVar(itsPVID);
    theStream >> FC_ExtractVar(itsTPID);
    itsTagMode = (TSPII_L2::Enum)(aTemp);
    theStream >> FC_ExtractVar(aTemp);
    theStream >> FC_ExtractVar(itsLACPMode);
    theStream >> FC_ExtractVar(itsLinkOAMMode);
    theStream >> FC_ExtractVar(itsDot1XMode);
    theStream >> FC_ExtractVar(itsELMIMode);
    theStream >> FC_ExtractVar(itsLLDPMode);
    //theStream >> FC_ExtractVar(itsGARPMode);
    theStream >> FC_ExtractVar(itsPortLacpPriority);
    theStream >> FC_ExtractVar(aPartiMode);
    itsPortLacpPartiMode = (CT_TEL_LacpPartiMode) aPartiMode;
    theStream >> FC_ExtractVar(itsMateLacpPriority);
    theStream >> FC_ExtractVar(aPartiMode);
    itsMateLacpPartiMode = (CT_TEL_LacpPartiMode) aPartiMode;

    RefreshSet();
        
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_L2If::Display(FC_Stream & theStream)
{ 
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  L2 Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Committed Info Rate   = " << itsCommittedInfoRate                     << "\n";
    theStream << "      Committed Burst Size  = " << itsCommittedBurstSize                    << "\n";
    theStream << "      Excess Burst Size     = " << itsExcessBurstSize                       << "\n";
    theStream << "      Excess Info Rate      = " << itsExcessInfoRate                        << "\n";
    theStream << "      PVID                  = " << itsPVID << "\n";
    theStream << "      TPID                  = " << itsTPID << "\n";
    theStream << "      Color Mode            = " << DISPLAY_BW_COLOR_MODE(itsColorMode)      << "\n";
    theStream << "      Meter Type            = " << DISPLAY_BW_METER_TYPE(itsMeterType)      << "\n";
    theStream << "      Port Mode             = " << (int)itsPortMode                              << "\n";
    theStream << "      Tag Mode              = " << DISPLAY_TAGMODE(itsTagMode)              << "\n";
    theStream << "      Tunneling LACP Mode   = " << DISPLAY_BOOL(itsLACPMode) << "\n";
    theStream << "      Tunneling LnkOAM Mode = " << DISPLAY_BOOL(itsLinkOAMMode) << "\n";
    theStream << "      Tunneling Dot1X Mode  = " << DISPLAY_BOOL(itsDot1XMode) << "\n";
    theStream << "      Tunneling ELMI Mode   = " << DISPLAY_BOOL(itsELMIMode)<< "\n";
    theStream << "      Tunneling LLDP Mode   = " << DISPLAY_BOOL(itsLLDPMode) << "\n";
    //theStream << "      Tunneling GARP Mode   = " << DISPLAY_BOOL(itsGARPMode) << "\n";
    theStream << "      Port Lacp Priority      = " << (int)itsPortLacpPriority                 << "\n";
    theStream << "      Port Lacp Participation = " << DISPLAY_PARTI_MODE(itsPortLacpPartiMode) << "\n";
    theStream << "      Mate Lacp Priority      = " << (int)itsMateLacpPriority                 << "\n";
    theStream << "      Mate Lacp Participation = " << DISPLAY_PARTI_MODE(itsMateLacpPartiMode) << "\n";

    theStream << "    MONITORING\n"; 
    theStream << endl;
        
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::Set(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "cir") == 0))
    {
        SetCommittedInfoRate(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "cbs") == 0))
    {
        SetCommittedBurstSize(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "ebs") == 0))
    {
        SetExcessBurstSize(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "eir") == 0))
    {
        SetExcessInfoRate(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "color") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_BW_CM_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_BW_COLOR_MODE(i)) == 0)
        {
            SetColorMode((CT_TEL_BW_CM)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "meter") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_BW_METERTYPE_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_BW_METER_TYPE(i)) == 0)
        {
            SetMeterType((CT_TEL_BW_METERTYPE)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portmode") == 0))
    {
        uint8 pmode = (uint8)strtoul(argv[1], NULL, 0);
        if (pmode <= CT_TEL_PortMode_Uni_DT || pmode == CT_TEL_PortMode_Undefined)
        {
            SetPortMode(pmode);
            printUsage = false;
        }
        else 
            printUsage = true;
    }
    else if ((argc == 2) && (strcmp(argv[0], "lacp") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLACPMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLACPMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "oam") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLinkOAMMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLinkOAMMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "dot1x") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetDot1XMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetDot1XMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "elmi") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetELMIMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetELMIMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "lldp") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLLDPMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLLDPMode(false);
        }
        else
        {
            printUsage = true;
        }
    }   
    //else if ((argc == 2) && (strcmp(argv[0], "garp") == 0))
    //{
    //    if (strcmp(argv[1], "on") == 0)
    //    {
    //        SetGARPMode(true);
    //    }
    //    else if (strcmp(argv[1], "off") == 0)
    //    {
    //        SetGARPMode(false);
    //    }
    //    else
    //    {
    //        printUsage = true;
    //    }
    //}
    else if ((argc == 2) && (strcmp(argv[0], "pvid") == 0))
    {
        uint32 val = strtoul(argv[1], NULL, 0);
        if (val >=1 && val <= 4095) 
        {
            SetPVID(val);

        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portpriority") == 0))
    {
        uint16 priority = (uint16) atoi(argv[1]);
        SetPortLacpPriority(priority);
    }
    else if ((argc == 2) && (strcmp(argv[0], "portparti") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_LacpPartiMode_ALL; i++) if (strcmp(argv[1], DISPLAY_PARTI_MODE(i)) == 0)
        {
            SetPortLacpPartiMode((CT_TEL_LacpPartiMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "matepriority") == 0))
    {
        uint16 priority = (uint16) atoi(argv[1]);
        SetMateLacpPriority(priority);
    }
    else if ((argc == 2) && (strcmp(argv[0], "mateparti") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_LacpPartiMode_ALL; i++) if (strcmp(argv[1], DISPLAY_PARTI_MODE(i)) == 0)
        {
            SetMateLacpPartiMode((CT_TEL_LacpPartiMode)i);
            printUsage = false;
            break;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    cir             <0-X> (50 * #sts1 defined)\n"
                   "    cbs             <0-X> \n"
                   "    ebs             <0-X>\n"
                   "    eir             <0-X>\n"
                   "    color           <Blind,Aware,Unknown>\n"
                   "    meter           <srTCM,trTCM,Unknown>\n" 
                   "    lacp            <on,off>\n" 
                   "    oam             <on,off>\n" 
                   "    dot1x           <on,off>\n" 
                   "    elmi            <on,off>\n" 
                   "    lldp            <on,off>\n"
                   //"    garp            <on,off>\n"
                   "    portpriority    <0- 65535>\n"
                   "    portparti       <PARTI_MODE_ACTIVE | PARTI_MODE_STATIC | PARTI_MODE_PASSIVE>\n"
                   "    matepriority    <0- 65535>\n"
                   "    mateparti       <PARTI_MODE_ACTIVE | PARTI_MODE_STATIC | PARTI_MODE_PASSIVE>\n"
                   "    pvid            <1- 4095>\n"
                   "    portmode        <0 - 4, 255>\n"
                   "                       0 = Uni_Cb\n"
                   "                       1 = Nni\n"
                   "                       2 = Transparent\n"
                   "                       3 = Uni_Pb\n"
                   "                       4 = Uni_Dt\n"
                   "                      255= Undefined"<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_L2If::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    printUsage = TSPII_BaseIf::Simul(argc, argv);
    
    return printUsage;
}

