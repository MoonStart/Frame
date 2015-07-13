/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds March 2008
 DESCRIPTION:Definition of the class TSPII_MacIf. Models the Ethernet 
             Virtual Connection hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_EvcIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

                                                                  // 
//static bool ReadPortInput(int argc, char ** argv, char* aBuf, char * astring, CT_ShelfId *aShelfId,CT_SlotId* aSlotId, CT_IntfId* aPortId, CT_FacilitySubType* aPortType, CT_ChannelId* aChannelId );

///////////////////////////////////////////////////////////////////////////////
TSPII_EvcIf::TSPII_EvcIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_EvcIf::~TSPII_EvcIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::RefreshGet()
{
    // Monitoring attributes
    
    // Configuration attributes
    itsIsEpl = GetIsEpl();
    itsAllFrames = GetAllFrames();
    itsSrcIncludedInAnyEVC  = GetSrcIncludedInAnyEVC();
    itsDestIncludedInAnyEVC = GetDestIncludedInAnyEVC();
    itsDestPort = GetDestPort();
    itsSrcPort = GetSrcPort();
    itsPairId = GetPairId();
    itsPauseFrameTransparencyEnabled = GetPauseFrameTransparencyEnabled();
    itsPbitRegen = GetPbitRegen();
    itsGARPMode = GetGARPMode();
    itsAisEnabled = GetAisEnabled();
    itsAisInterval = GetAisInterval();
    itsAisMegLevel = GetAisMegLevel();
    itsAisDestMacMode = GetAisDestMacMode();
    itsAisDestMacAddr = GetAisDestMacAddr();
    itsForceAIS = GetForceAis();
    itsFacilityLoopBackEnable = GetFacilityLoopBackEnable();
    itsTerminalLoopBackEnable = GetTerminalLoopBackEnable();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::RefreshSet()
{
    // Configuration attributes
    SetIsEpl(itsIsEpl);
    SetAllFrames(itsAllFrames);
    SetSrcIncludedInAnyEVC(itsSrcIncludedInAnyEVC);
    SetDestIncludedInAnyEVC(itsDestIncludedInAnyEVC);
    SetDestPort(itsDestPort);
    SetSrcPort(itsSrcPort);
    SetPairId(itsPairId);
    EnablePauseFrameTransparency(itsPauseFrameTransparencyEnabled);
    SetPbitRegen(itsPbitRegen);
    SetGARPMode(itsGARPMode);
    SetAisEnabled(itsAisEnabled);
    SetAisInterval(itsAisInterval);
    SetAisMegLevel(itsAisMegLevel);
    SetAisDestMacMode(itsAisDestMacMode);
    SetAisDestMacAddr(itsAisDestMacAddr);
    SetForceAis(itsForceAIS);
    SetFacilityLoopBackEnable(itsFacilityLoopBackEnable);
    SetTerminalLoopBackEnable(itsTerminalLoopBackEnable);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::Reset()
{
    TSPII_BaseIf::Reset();
    
    // Monitoring attributes
    
    // Configuration attributes
    itsIsEpl = false;
    itsAllFrames = false;
    itsSrcIncludedInAnyEVC  = true;
    itsDestIncludedInAnyEVC = true;
    itsDestPort.Reset(); 
    itsSrcPort.Reset();
    itsPairId = 999;
    itsPauseFrameTransparencyEnabled = 0;
    itsPbitRegen = CT_TEL_PbitRegen_Off;
    itsGARPMode = false;
    itsAisEnabled = false;
    itsAisInterval = 60;
    itsAisMegLevel = 2;
    itsAisDestMacMode = CT_TEL_MacMode_MULTICAST;
    itsAisDestMacAddr = CT_LacpSystemId();
    itsForceAIS = false;
    itsFacilityLoopBackEnable = false;
    itsTerminalLoopBackEnable = false;
}
    
///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::InitWarm()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetIsEpl(bool theEnable)
{
    itsIsEpl = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetIsEpl() const
{
    return itsIsEpl;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAllFrames(bool theAllFrames)
{
    itsAllFrames = theAllFrames;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetAllFrames() const
{
    return itsAllFrames;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetSrcIncludedInAnyEVC(bool theIncluded)
{
    itsSrcIncludedInAnyEVC = theIncluded;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetSrcIncludedInAnyEVC() const
{
    return itsSrcIncludedInAnyEVC;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetDestIncludedInAnyEVC(bool theIncluded)
{
    itsDestIncludedInAnyEVC = theIncluded;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetDestIncludedInAnyEVC() const
{
    return itsDestIncludedInAnyEVC;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetDestPort(CT_Port thePort)
{
    itsDestPort = thePort;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetEvc(CT_Port srcPort, CT_Port dstPort, bool theEnable, uint32 thePairId, 
                         bool allframes, bool srcIncluded, bool dstIncluded, bool isProtected)
{
    itsDestPort = dstPort;
    itsSrcPort = srcPort;
    itsPairId = thePairId;
    itsAllFrames = allframes;
    itsSrcIncludedInAnyEVC = srcIncluded;
    itsDestIncludedInAnyEVC = dstIncluded;
}

///////////////////////////////////////////////////////////////////////////////
CT_Port TSPII_EvcIf::GetDestPort() const
{
    return itsDestPort;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetSrcPort(CT_Port thePort)
{
    itsSrcPort = thePort;
}

///////////////////////////////////////////////////////////////////////////////
CT_Port TSPII_EvcIf::GetSrcPort() const
{
    return itsSrcPort;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetPairId(uint32 thePairId)
{
    itsPairId = thePairId;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_EvcIf::GetPairId() const
{
    return itsPairId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetSTAG(uint32 theSTAG)
{
    itsStag = theSTAG;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_EvcIf::GetSTAG()
{
    return itsStag;
}

///////////////////////////////////////////////////////////////////////////////
vector<uint16> TSPII_EvcIf::GetSVID()
{
    return itsSvid;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetSVID(vector<uint16> theSVID)
{
    itsSvid = theSVID;
}

///////////////////////////////////////////////////////////////////////////////
vector<uint16> TSPII_EvcIf::GetCVID()
{
    return itsCvid;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetCVID(vector<uint16> theCVID)
{
    itsCvid = theCVID;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetCommittedInfoRate(uint32 theRate)
{
     itsCommittedInfoRate = theRate;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_EvcIf::GetCommittedInfoRate() const
{
    return itsCommittedInfoRate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetCommittedBurstSize(uint32 theSize)
{
    itsCommittedBurstSize = theSize;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_EvcIf::GetCommittedBurstSize() const
{
    return itsCommittedBurstSize;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::EnablePauseFrameTransparency(bool enable)
{
    itsPauseFrameTransparencyEnabled = enable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetPauseFrameTransparencyEnabled() const
{
    return itsPauseFrameTransparencyEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetPbitRegen(CT_TEL_PbitRegen thePbitRegen)
{
    itsPbitRegen = thePbitRegen;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_PbitRegen TSPII_EvcIf::GetPbitRegen() const
{
    return itsPbitRegen;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetGARPMode() const
{
    return itsGARPMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetGARPMode(bool theGARPMode)
{
    itsGARPMode = theGARPMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetAisEnabled() const
{
    return itsAisEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAisEnabled(bool theAisEnabled)
{
    itsAisEnabled = theAisEnabled;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_EvcIf::GetAisInterval() const
{
    return itsAisInterval;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAisInterval(uint16 theAisInterval)
{
    itsAisInterval = theAisInterval;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_EvcIf::GetAisMegLevel() const
{
    return itsAisMegLevel;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAisMegLevel(uint8 theAisMegLevel)
{
    itsAisMegLevel = theAisMegLevel;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MacMode TSPII_EvcIf::GetAisDestMacMode() const
{
    return itsAisDestMacMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAisDestMacMode(CT_TEL_MacMode theAisDestMacMode)
{
    itsAisDestMacMode = theAisDestMacMode;
}

///////////////////////////////////////////////////////////////////////////////
const CT_LacpSystemId & TSPII_EvcIf::GetAisDestMacAddr() const
{
    return itsAisDestMacAddr;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetAisDestMacAddr(const CT_LacpSystemId & theMacAddr)
{
    itsAisDestMacAddr = theMacAddr;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetForceAis() const
{
    return itsForceAIS;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetForceAis(bool theEnable)
{
    itsForceAIS = theEnable;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetFacilityLoopBackEnable() const
{
    return itsFacilityLoopBackEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetFacilityLoopBackEnable(bool theEnabled)
{
    itsFacilityLoopBackEnable = theEnabled;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::GetTerminalLoopBackEnable() const
{
    return itsTerminalLoopBackEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::SetTerminalLoopBackEnable(bool theEnabled)
{
    itsTerminalLoopBackEnable = theEnabled;
}



///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_EvcIf::WriteObjectBinary(FC_Stream & theStream)
{
    int aMacMode;

    // Update H/W
    UpdateValues();
    RefreshGet();
  
    // Monitoring attributes

    // Configuration attributes
    theStream << itsIsEpl;
    itsDestPort.WriteObjectBinary(theStream);
    itsSrcPort.WriteObjectBinary(theStream);
    theStream << itsPairId;
    theStream << itsStag;
    theStream << itsSrcIncludedInAnyEVC;
    theStream << itsDestIncludedInAnyEVC;
    theStream << itsAllFrames;
    theStream << itsPauseFrameTransparencyEnabled;
    theStream << itsPbitRegen;
    theStream << itsGARPMode;
    theStream << itsAisEnabled;
    theStream << itsAisInterval;
    theStream << itsAisMegLevel;
    aMacMode = int(itsAisDestMacMode);
    theStream << aMacMode;
    theStream << itsAisDestMacAddr;
    theStream << itsForceAIS;
    theStream << itsFacilityLoopBackEnable;
    theStream << itsTerminalLoopBackEnable;

    //loop thru cvid and svid

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_EvcIf::ReadObjectBinary(FC_Stream & theStream)
{   
    int aMacMode;

    // Monitoring attributes
    
    // Configuration attributes
    theStream >> itsIsEpl;
    itsDestPort.ReadObjectBinary(theStream);
    itsSrcPort.ReadObjectBinary(theStream);
    theStream >> itsPairId;
    theStream >> itsStag;
    theStream >> itsSrcIncludedInAnyEVC;
    theStream >> itsDestIncludedInAnyEVC;
    theStream >> itsAllFrames;
    theStream >> itsPauseFrameTransparencyEnabled;
    theStream >> itsPbitRegen;
    theStream >> itsGARPMode;
    theStream >> itsAisEnabled;
    theStream >> itsAisInterval;
    theStream >> itsAisMegLevel;
    theStream >> aMacMode;
    itsAisDestMacMode = (CT_TEL_MacMode) aMacMode;
    theStream >> itsAisDestMacAddr;
    theStream >> itsForceAIS;
    theStream >> itsFacilityLoopBackEnable;
    theStream >> itsTerminalLoopBackEnable;

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_EvcIf::WriteObject(ostream & theStream)
{
    int aMacMode;

    // Update H/W
    UpdateValues();
    RefreshGet();
    
    // Monitoring attributes

    // Configuration attributes
    theStream << FC_InsertVar(itsIsEpl);
    itsDestPort.WriteObject(theStream);
    itsSrcPort.WriteObject(theStream);
    theStream << FC_InsertVar(itsPairId);
    theStream << FC_InsertVar(itsStag);
    theStream << FC_InsertVar(itsSrcIncludedInAnyEVC);
    theStream << FC_InsertVar(itsDestIncludedInAnyEVC);
    theStream << FC_InsertVar(itsAllFrames);
    theStream << FC_InsertVar(itsPauseFrameTransparencyEnabled);
    theStream << FC_InsertVar(itsPbitRegen);
    theStream << FC_InsertVar(itsGARPMode);
    theStream << FC_InsertVar(itsAisEnabled);
    theStream << FC_InsertVar(itsAisInterval);
    theStream << FC_InsertVar(itsAisMegLevel);
    aMacMode = int(itsAisDestMacMode);
    theStream << FC_InsertVar(aMacMode);
    theStream << FC_InsertVar(itsAisDestMacAddr);
    theStream << FC_InsertVar(itsForceAIS);
    theStream << FC_InsertVar(itsFacilityLoopBackEnable);
    theStream << FC_InsertVar(itsTerminalLoopBackEnable);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_EvcIf::ReadObject(istream & theStream)
{   
    int aMacMode;

    // Monitoring attributes
    
    // Configuration attributes
    theStream >> FC_ExtractVar(itsIsEpl);
    itsDestPort.ReadObject(theStream);
    itsSrcPort.ReadObject(theStream);
    theStream >> FC_ExtractVar(itsPairId);
    theStream >> FC_ExtractVar(itsStag);
    theStream >> FC_ExtractVar(itsSrcIncludedInAnyEVC);
    theStream >> FC_ExtractVar(itsDestIncludedInAnyEVC);
    theStream >> FC_ExtractVar(itsAllFrames);
    theStream >> FC_ExtractVar(itsPauseFrameTransparencyEnabled);
    theStream >> FC_ExtractVar(itsPbitRegen);
    theStream >> FC_ExtractVar(itsGARPMode);
    theStream >> FC_ExtractVar(itsAisEnabled);
    theStream >> FC_ExtractVar(itsAisInterval);
    theStream >> FC_ExtractVar(itsAisMegLevel);
    theStream >> FC_ExtractVar(aMacMode);
    itsAisDestMacMode = (CT_TEL_MacMode) aMacMode;
    theStream >> FC_ExtractVar(itsAisDestMacAddr);
    theStream >> FC_ExtractVar(itsForceAIS);
    theStream >> FC_ExtractVar(itsFacilityLoopBackEnable);
    theStream >> FC_ExtractVar(itsTerminalLoopBackEnable);

    RefreshSet();
        
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_EvcIf::Display(FC_Stream & theStream)
{ 
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  EVC Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Is EPL                = " << DISPLAY_BOOL(itsIsEpl)     << "\n";
    theStream << "      Is All Frames         = " << DISPLAY_BOOL(itsAllFrames)  << "\n";
    theStream << "      Eth-AIS Enabled       = " << DISPLAY_BOOL(itsAisEnabled)  << "\n";
    theStream << "      Force AIS             = " << DISPLAY_BOOL(itsForceAIS)  << "\n";
    theStream << "      AIS Interval (xmit)   = " << uint32(itsAisInterval)    << "\n";
    theStream << "      AIS MEG Level         = " << uint32(itsAisMegLevel)    << "\n";
    theStream << "      AIS Dest Mac Mode     = " << DISPLAY_MAC_MODE(itsAisDestMacMode)    << "\n";
    theStream << "      AIS Dest Mac Addr     = " << itsAisDestMacAddr.DisplayAddr()    << "\n";
    theStream << "      Faclilty LoopBack     = " << DISPLAY_BOOL(itsFacilityLoopBackEnable)  << "\n";
    theStream << "      Terminal LoopBack     = " << DISPLAY_BOOL(itsTerminalLoopBackEnable)  << "\n";
    theStream << "      Dest Port             = " << DisplayPort(itsDestPort)   << "\n";
    theStream << "      Src Port              = " << DisplayPort(itsSrcPort)    << "\n";
    theStream << "      Dest In Any EVC       = " << DISPLAY_BOOL(itsDestIncludedInAnyEVC)  << "\n";
    theStream << "      Src In Any EVC        = " << DISPLAY_BOOL(itsSrcIncludedInAnyEVC)  << "\n";
    theStream << "      Pair Id               = " << uint32(itsPairId)    << "\n";
    theStream << "      S Tag                 = " << uint32(itsStag)    << "\n";
    theStream << "      Committed Rate        = " << uint32(itsCommittedInfoRate) << "\n";
    theStream << "      Committed Burst Size  = " << uint32(itsCommittedBurstSize) << "\n";                                                                                  
    theStream << "      Pause Frame Xparency  = " << DISPLAY_BOOL(itsPauseFrameTransparencyEnabled) << endl;
    theStream << "      Priority Bits Regen   =" << DISPLAY_PBIT(itsPbitRegen) << endl;
    theStream << "      Tunneling GARP Mode   = " << DISPLAY_BOOL(itsGARPMode) << "\n";
    theStream << "      CVID list             = ";
    for (uint16 i=0; i<itsCvid.size(); i++)
    {
        theStream << uint32(itsCvid[i]) << " ";
    }
    theStream << "\n";
    theStream << "      SVID list             = ";
    for (uint16 i=0; i <itsSvid.size(); i++)
    {
        theStream << uint32(itsSvid[i]) << " ";
    }
    theStream << "\n";

    theStream << "    MONITORING\n"; 
    theStream << endl;
        
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::Set(int argc, char ** argv)
{
    char aBuf[128];
    char aTemp[128];
    char *aStr;
    CT_ShelfId aShelfId;
    CT_SlotId aSlotId;
    CT_IntfId aPortId;
    CT_FacilitySubType aPortType;
    CT_ChannelId aChannelId;
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "epl") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsEpl(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsEpl(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc >= 2) && (strcmp(argv[0], "cvid") == 0))
    {
        // get list of id's 
        strcpy(aBuf, argv[1]);
//        strcat(aBuf, ",\0");    // force a token comma in the string.
        vector<uint16> idlist;
        int i = 0;
        char * uinput = NULL;
        uinput =strtok(aBuf, ",");
        while (uinput != NULL)
        {
            idlist.push_back(atoi(uinput));
            i++;
            uinput = strtok(NULL,",");
        }
        if (idlist.size())
        {
            SetCVID(idlist);
        }
    }

    else if ((argc >= 2) && (strcmp(argv[0], "svid") == 0))
    {
        // get list of id's 
        strcpy(aBuf, argv[1]);
//        strcat(aBuf, ",\0,");    // force some tokens in the string.
        vector<uint16> idlist;
        int i = 0;
        char * uinput = NULL;
        uinput =strtok(aBuf, ",");
        while (uinput != NULL)
        {
            idlist.push_back(atoi(uinput));
            i++;
            uinput = strtok(NULL,",");
        }
        if (idlist.size() )
        {
            SetSVID(idlist);
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "dport") == 0))
    {
        strcpy(aBuf, argv[1]);
        strcat(aBuf, ",0,0,0,0,");    // force some tokens in the string.
        aShelfId = (CT_ShelfId) atoi(strtok(aBuf, ","));
        aSlotId = (CT_SlotId) atoi(strtok(NULL, ","));
        aStr = strtok(NULL, ",");
        strcpy(&aTemp[1], aStr);       // Add space before and after 
        aTemp[0] = ' ';                //
        aTemp[strlen(aStr)+2] = '\0';  //
        aTemp[strlen(aStr)+1] = ' ';   //
        printUsage = true;
        for (int i = 0; i <= CT_INTF_ID_UNKNOWN; i++) if (strcmp(aTemp, DISPLAY_CT_IntfId(i)) == 0)
        {
            aPortId = ((CT_IntfId)i);
            printUsage = false;
            break;
        }

        if(printUsage == false)
        {
            aStr = strtok(NULL, ",");
            printUsage = true;
            for (int i = 0; i < FAC_SUBTYPE_ALL; i++) if (strcmp(aStr, DISPLAY_CT_FacilitySubType(i)) == 0)
            {
                aPortType = ((CT_FacilitySubType)i);
                printUsage = false;
                break;
            }
        }

        if(printUsage == false)
        {
            aChannelId = (CT_ChannelId) atoi(strtok(NULL, ","));
            itsDestPort.SetPortInfo(aShelfId, aSlotId, aPortId, aPortType, aChannelId);
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "sport") == 0))
    {
        strcpy(aBuf, argv[1]);
        strcat(aBuf, ",0,0,0,0,");    // force some tokens in the string.
        aShelfId = (CT_ShelfId) atoi(strtok(aBuf, ","));
        aSlotId = (CT_SlotId) atoi(strtok(NULL, ","));
        aStr = strtok(NULL, ",");
        strcpy(&aTemp[1], aStr);       // Add space before and after
        aTemp[0] = ' ';                //
        aTemp[strlen(aStr)+2] = '\0';  //
        aTemp[strlen(aStr)+1] = ' ';   //
        printUsage = true;
        for (int i = 0; i <= CT_INTF_ID_UNKNOWN; i++) if (strcmp(aTemp, DISPLAY_CT_IntfId(i)) == 0)
        {
            aPortId = ((CT_IntfId)i);
            printUsage = false;
            break;
        }

        if(printUsage == false)
        {
            // Success up to the subType
            aStr = strtok(NULL, ",");
            printUsage = true;
            for (int i = 0; i < FAC_SUBTYPE_ALL; i++) if (strcmp(aStr, DISPLAY_CT_FacilitySubType(i)) == 0)
            {
                aPortType = ((CT_FacilitySubType)i);
                printUsage = false;
                break;
            }
        }

        if(printUsage == false)
        {
            // Success with subType
            aChannelId = (CT_ChannelId) atoi(strtok(NULL, ","));
            itsSrcPort.SetPortInfo(aShelfId, aSlotId, aPortId, aPortType, aChannelId);
        }
    }
    else if (((argc == 5) || (argc == 7)) && (strcmp(argv[0], "evc") == 0))
    {
       //read src port info
        if(ReadPortInput(argc,&argv[1],aBuf,0,&aShelfId,&aSlotId,&aPortId,&aPortType,&aChannelId))
            printUsage = true;

        if(printUsage == false)
            //read dest port info
           if(ReadPortInput(argc,&argv[2],aBuf,1,&aShelfId,&aSlotId,&aPortId,&aPortType,&aChannelId))
           printUsage=true;

        if (printUsage == false)
        {
            uint32 thePairId = 999;

            //check allframe
            bool allframe = true;   //assume EPL
            if (strcmp(argv[4], "false") ==0)
            {
                allframe = false;
            }
            bool srcIncluded = true;
            bool dstIncluded = true;
            if (argc == 7) 
            {
                if (strcmp(argv[5], "false") ==0)
                {
                    srcIncluded = false;
                }
                if (strcmp(argv[6], "false") ==0)
                {
                    dstIncluded = false;
                }
            }

            //check the enable flag
            if (strcmp(argv[3], "on") == 0)
            {
                SetEvc(itsSrcPort, itsDestPort,true,thePairId, allframe, srcIncluded, dstIncluded, true);
            }
            else
            {
                SetEvc(itsSrcPort, itsDestPort, false,thePairId, allframe, srcIncluded, dstIncluded, true);
            }
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "pairid") == 0))
    {

        uint32 thePairId = atoi(argv[1]);
        SetPairId(thePairId);

    }
    else if ((argc == 2) && (strcmp(argv[0], "stag") == 0))
    {
        uint32 theStag = atoi(argv[1]);
        SetSTAG(theStag);
    }
    else if(argc == 2 && strcmp(argv[0], "pausetransparent") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            EnablePauseFrameTransparency(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            EnablePauseFrameTransparency(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "committedrate") == 0)
    {
        SetCommittedInfoRate(atoi(argv[1]));
    }
    else if (argc == 2 && strcmp(argv[0], "committedburst") == 0)
    {
        SetCommittedBurstSize(atoi(argv[1]));
    }
    else if ((argc == 2) && (strcmp(argv[0], "pbitregen") == 0))
    {
        uint8 thePbit = atoi(argv[1]);
        SetPbitRegen(thePbit);
    }
    else if ((argc == 2) && (strcmp(argv[0], "garp") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetGARPMode(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetGARPMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "ethais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAisEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAisEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "forceais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceAis(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceAis(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "aisinterval") == 0))
    {
        uint16 theInterval = atoi(argv[1]);
        // Note: value can either be 1 or 60, 60 is default
        if (theInterval != 1) 
        {
            theInterval = 60;
        }
        SetAisInterval(theInterval);
    }
    else if ((argc == 2) && (strcmp(argv[0], "aismeglevel") == 0))
    {
        uint8 theLevel = atoi(argv[1]);
        // Note: value can only be between 0 and 7, 2 is default
        if (theLevel > 7)
        {
            theLevel = 2;
        }
        SetAisMegLevel(theLevel);
    }
    else if ((argc == 2) && (strcmp(argv[0], "aisdestmac") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MacMode_ALL; i++) if (strcmp(argv[1], DISPLAY_MAC_MODE(i)) == 0)
        {
            SetAisDestMacMode((CT_TEL_MacMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 7) && (strcmp(argv[0], "aisdestaddr") == 0))
    {
        CT_LacpSystemId macaddr(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
        SetAisDestMacAddr(macaddr);
    }
    else if ((argc == 2) && (strcmp(argv[0], "facloop") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetFacilityLoopBackEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFacilityLoopBackEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "termloop") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetTerminalLoopBackEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTerminalLoopBackEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    epl                <on,off>\n"
                   "    cvid               <id#,id#...>  use a comma between each value\n"
                   "    svid               <id#,id#...>  use a comma between each value\n"
                   "    pairid             <Evc Id On Mate Card>\n"
                   "    stag               <uint32>\n"
                   "    pausetransparent   <on,off>\n"
                   "    committedrate      <0-x> (50 * # sts1)\n"
                   "    committedburst     <0-x> (57680 fixed )\n"
                   "    pbitregen          <0,1,2,3,255> (0=Off,1=Both,2=Egress)\n"
                   "                                     (3=Ingress,255=Unknown)\n"
                   "    garp               <on,off>\n"
                   "    ethais             <on,off>, Enable Ethernet AIS Service\n"
                   "    forceais           <on,off>, Force Ethernet AIS\n"
                   "    aisinterval        <1 | 60>, default=60\n"
                   "    aismeglevel        <0-7>, default=2\n"
                   "    aisdestmac         <MAC_MODE_UNICAST | MAC_MODE_MULTICAST>\n"
                   "    facloop            <on,off>, Facility (client) LoopBack\n"
                   "    termloop           <on,off>, Terminal LoopBack\n"
                   "    evc sport,vcgport, <on,off>, allframes srcIncluded dstIncluded\n"
                   "       dport           <Sh,Sl,If,Ty,Ch>\n"
                   "       sport           <Sh,Sl,If,Ty,VC>\n"
                   "       where:           Sh=(shelf)1-12\n"
                   "                        Sl=(slot)1-18\n"
                   "                        If=(interface)CT_PORT_SIDE_0 - 12|CT_INTF_ID_UNKNOWN\n"
                   "                        Ty=(type)OC3,OC12,OC48,OC192,ETH,VCG,Unknown\n"
                   "                        Ch=(channel)1-13\n" 
                   "                        VC=(VC channel )<0-63>\n"
                   "       allframes        <true,false>  false for EVPL\n"
                   "       srcIncluded      <true,false>  false if src port is not included in any EVC\n"
                   "       dstIncluded      <true,false>  false if dst port is not included in any EVC\n"
                   "    \n"
                   "    EVPL example\n"
                   "     TL1... (ent-evc::evc-1-12-10:ct:::SRCFAC=ETH-1-12-10,DESTFAC=VCG-1-12-10,allframes=false\n"
                   "    \n"
                   "    setevc 1,12,CT_PORT_SIDE_10,ETH,10, 1,12,CT_PORT_SIDE_10,ETH,10,0 on, false\n"
                   "    \n"
                   "    EPL  example \n"
                   "      TL1...(ent-evc::evc-1-12-10:Fish:::SRCFAC=ETH-1-12-10,DESTFAC=VCG-1-12-10;\n"
                   "    \n"
                   "    setevc 1,12,CT_PORT_SIDE_10,ETH,10, 1,12,CT_PORT_SIDE_10,ETH,10,0 on, true"<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    printUsage = TSPII_BaseIf::Simul(argc, argv);
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_EvcIf::DisplayPort(CT_Port thePort)
{
    char aBuf[128];

    sprintf(aBuf, "%d,%d%,%s,%s,%d", thePort.GetShelfId(),
                                     thePort.GetSlotId(),
                                     DISPLAY_CT_IntfId(thePort.GetPortId()),
                                     DISPLAY_CT_FacilitySubType(thePort.GetPortType()),
                                     thePort.GetChannelId());
    
    string aStr(aBuf);
    return aStr;
    
}





 ///////////////////////////////////////////////////////////////////////////////
bool TSPII_EvcIf::ReadPortInput(int argc, char ** argv, char* aBuf, int porttype, CT_ShelfId *aShelfId,CT_SlotId* aSlotId, CT_IntfId* aPortId, CT_FacilitySubType* aPortType, CT_ChannelId* aChannelId )
{
    char aTemp[128];
    char *aStr;
    bool printUsage = false;

    strcpy(aBuf, argv[0]);
    strcat(aBuf, ",0,0,0,0,");    // force some tokens in the string.
    *aShelfId = (CT_ShelfId) atoi(strtok(aBuf, ","));
    *aSlotId = (CT_SlotId) atoi(strtok(NULL, ","));
    aStr = strtok(NULL, ",");
    strcpy(&aTemp[1], aStr);       // Add space before and after
    aTemp[0] = ' ';                //
    aTemp[strlen(aStr)+2] = '\0';  //
    aTemp[strlen(aStr)+1] = ' ';   //
    printUsage = true;
    for (int i = 0; i <= CT_INTF_ID_UNKNOWN; i++) if (strcmp(aTemp, DISPLAY_CT_IntfId(i)) == 0)
    {
        *aPortId = ((CT_IntfId)i);
        printUsage = false;
        break;
    }

    if(printUsage == false)
    {
        // Success up to the subType
        aStr = strtok(NULL, ",");
        printUsage = true;
        for (int i = 0; i < FAC_SUBTYPE_ALL; i++) if (strcmp(aStr, DISPLAY_CT_FacilitySubType(i)) == 0)
        {
            *aPortType = ((CT_FacilitySubType)i);
            printUsage = false;
            break;
        }
    }

    if(printUsage == false)
    {
        // Success with subType
        *aChannelId = (CT_ChannelId) atoi(strtok(NULL, ","));
        if (porttype == 0)
        {
            itsSrcPort.SetPortInfo(*aShelfId, *aSlotId, *aPortId, *aPortType, *aChannelId);
        }
        else if (porttype == 1)
        {
            itsDestPort.SetPortInfo(*aShelfId, *aSlotId, *aPortId, *aPortType, *aChannelId);
        }
        else
            printUsage = true;
    }

    return printUsage;

}


 

