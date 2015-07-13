//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Evc.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Evc::CFG_Evc(uint32 theIndex):
    CFG_Object(theIndex),
    myAllFrames(false),
    mySrcIncludedInAnyEVC(false),
    myDestIncludedInAnyEVC(false),
    myIsProvisioned(false),
    myIsProtected(false),
    myDestPort(UNKNOWN_SHELF_ID,UNKNOWN_SLOT_ID,CT_INTF_ID_UNKNOWN,FAC_SUBTYPE_UNKNOWN,CT_TEL_INVALID_VCG_IDX),
    mySrcPort(UNKNOWN_SHELF_ID,UNKNOWN_SLOT_ID,CT_INTF_ID_UNKNOWN,FAC_SUBTYPE_UNKNOWN,UNKNOWN_CHANNEL_ID),
    myEvcPairId(CT_TEL_EvcPairIdNone),
    myBWPF(-1),
    mySTAG(CT_TEL_VlanNone),
    myPauseDiscardEnabled(true),
    mySVID(0),
    myCVID(0),
    myAisEnabled(false),
    myAisInterval(0),
    myAisMegLevel(0),
    myAisDestMacMode(CT_TEL_MacMode_UNKNOWN),
    myAisDestMacAddr(),
    myFacilityLoopBackEnable(false),
    myTerminalLoopBackEnable(false),
    myPbitRegen(CT_TEL_PbitRegen_Off),
    myCFPF(CT_TEL_DefaultCFPF)
{
}

CFG_Evc::~CFG_Evc(void)
{
}

void CFG_Evc::SetAllFrames(bool theAllFrames)
{
    myAllFrames = theAllFrames;
}

bool CFG_Evc::GetAllFrames() const
{
    return myAllFrames;
}

void CFG_Evc::SetDestPort(CT_Port theDestPort)
{
    myDestPort = theDestPort;
}

CT_Port CFG_Evc::GetDestPort() const
{
    return myDestPort;
}

void CFG_Evc::SetSrcPort(CT_Port theSrcPort)
{
    mySrcPort = theSrcPort;
}

CT_Port CFG_Evc::GetSrcPort() const
{
    return mySrcPort;
}

void CFG_Evc::SetSrcIncludedInAnyEVC(bool theIncluded)
{
    mySrcIncludedInAnyEVC = theIncluded;
}

bool CFG_Evc::GetSrcIncludedInAnyEVC() const
{
    return mySrcIncludedInAnyEVC;
}

void CFG_Evc::SetDestIncludedInAnyEVC(bool theIncluded)
{
    myDestIncludedInAnyEVC = theIncluded;
}

bool CFG_Evc::GetDestIncludedInAnyEVC() const
{
    return myDestIncludedInAnyEVC;
}

void CFG_Evc::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

bool CFG_Evc::GetIsProvisioned() const
{
    return myIsProvisioned;
}

void CFG_Evc::SetIsProtected(bool theIsProtected)
{
    myIsProtected = theIsProtected;
}

bool CFG_Evc::GetIsProtected() const
{
    return myIsProtected;
}

void CFG_Evc::SetEvcPairId(uint32 theEvcPairId)
{
    myEvcPairId = theEvcPairId;
}

uint32 CFG_Evc::GetEvcPairId() const
{
    return myEvcPairId;
}
void CFG_Evc::SetBWPF(int theBWPF)
{
    myBWPF = theBWPF;
}

int CFG_Evc::GetBWPF() const
{
    return myBWPF;
}

uint32 CFG_Evc::GetSTAG() const
{
    return mySTAG;
}

void CFG_Evc::SetSTAG(uint32 theSTAG)
{
    mySTAG = theSTAG;
}

void CFG_Evc::SetSVID(vector<uint16>& theSVID)
{
    mySVID = theSVID;
}

const vector<uint16>& CFG_Evc::GetSVID()
{
    return mySVID;
}

void CFG_Evc::SetCVID(vector<uint16>& theCVID)
{
    myCVID = theCVID;
}

const vector<uint16>& CFG_Evc::GetCVID()
{
    return myCVID;
}

void CFG_Evc::SetPauseDiscardEnabled(bool thePauseDiscardEnabled)
{
    myPauseDiscardEnabled = thePauseDiscardEnabled;
}

bool CFG_Evc::GetPauseDiscardEnabled() const
{
    return myPauseDiscardEnabled;
}

void CFG_Evc::SetPbitRegen(CT_TEL_PbitRegen thePbitRegen)
{
    myPbitRegen = thePbitRegen;
}

CT_TEL_PbitRegen CFG_Evc::GetPbitRegen() const
{
    return myPbitRegen;
}

void CFG_Evc::SetCFPF(int theCFPF)
{
    myCFPF = theCFPF;
}

int CFG_Evc::GetCFPF() const
{
    return myCFPF;
}



void CFG_Evc::SetAisEnabled(bool theAisEnabled)
{
    myAisEnabled = theAisEnabled;
}

bool CFG_Evc::GetAisEnabled() const
{
    return myAisEnabled;
}

void CFG_Evc::SetAisInterval(uint16 theAisInterval)
{
    myAisInterval = theAisInterval;
}

uint16 CFG_Evc::GetAisInterval() const
{
    return myAisInterval;
}

void CFG_Evc::SetAisMegLevel(uint8 theAisMegLevel)
{
    myAisMegLevel = theAisMegLevel;
}

uint8 CFG_Evc::GetAisMegLevel() const
{
    return myAisMegLevel;
}

void CFG_Evc::SetAisDestMacMode(CT_TEL_MacMode theAisDestMacMode)
{
    myAisDestMacMode = theAisDestMacMode;
}

CT_TEL_MacMode CFG_Evc::GetAisDestMacMode() const
{
    return myAisDestMacMode;
}

void CFG_Evc::SetAisDestMacAddr(CT_LacpSystemId theMacAddr)
{
    myAisDestMacAddr = theMacAddr;
}

CT_LacpSystemId CFG_Evc::GetAisDestMacAddr() const
{
    return myAisDestMacAddr;
}

void CFG_Evc::SetFacilityLoopBackEnable(bool theEnabled)
{
    myFacilityLoopBackEnable = theEnabled;
}

bool CFG_Evc::GetFacilityLoopBackEnable() const
{
    return myFacilityLoopBackEnable;
}

void CFG_Evc::SetTerminalLoopBackEnable(bool theEnabled)
{
    myTerminalLoopBackEnable = theEnabled;
}

bool CFG_Evc::GetTerminalLoopBackEnable() const
{
    return myTerminalLoopBackEnable;
}


void CFG_Evc::Reset(void)
{
    // Initialize all attributes to default values.
    myAllFrames = false;
    mySrcIncludedInAnyEVC = false;
    myDestIncludedInAnyEVC = false;
    myIsProvisioned = false;
    myIsProtected = false;
    myEvcPairId = CT_TEL_EvcPairIdNone;
    myBWPF = -1;
    myCFPF = CT_TEL_DefaultCFPF;
    mySTAG = CT_TEL_VlanNone;
    myPauseDiscardEnabled = true;
    myPbitRegen = CT_TEL_PbitRegen_Off;
    myDestPort.Reset();
    mySrcPort.Reset();
    myDestPort.SetPortInfo(UNKNOWN_SHELF_ID,UNKNOWN_SLOT_ID,CT_INTF_ID_UNKNOWN,FAC_SUBTYPE_UNKNOWN,CT_TEL_INVALID_VCG_IDX);
    mySrcPort.Reset();
    mySVID.erase(mySVID.begin(), mySVID.end());
    myCVID.erase(myCVID.begin(), myCVID.end());
    myAisEnabled  = false;
    myAisInterval = 0;
    myAisMegLevel = 0;
    myAisDestMacMode = CT_TEL_MacMode_UNKNOWN;
    myAisDestMacAddr = CT_LacpSystemId();
    myFacilityLoopBackEnable = false;
    myTerminalLoopBackEnable = false;
}

// For Display
ostream& CFG_Evc::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myAllFrames);
    theStream   << FC_InsertVar(mySrcIncludedInAnyEVC);
    theStream   << FC_InsertVar(myDestIncludedInAnyEVC);
    theStream   << FC_InsertVar(myIsProvisioned);
    theStream   << FC_InsertVar(myIsProtected);
    theStream   << FC_InsertVar(myDestPort);
    theStream   << FC_InsertVar(mySrcPort);
    theStream   << FC_InsertVar(myEvcPairId);
    theStream   << FC_InsertVar(myBWPF);
    theStream   << FC_InsertVar(mySTAG);
    theStream   << FC_InsertVar(myPauseDiscardEnabled);
    theStream   << FC_InsertVar(myPbitRegen);
    theStream   << FC_InsertVar(myCFPF);

    uint32  numberOfMbrs;
    numberOfMbrs   = mySVID.size();
    theStream << FC_InsertVar(numberOfMbrs);

    string aSVIDList;
    char aSVID[6];
    for (uint32 anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        sprintf(aSVID, "%4d,", mySVID[anIndex]);
        aSVID[5] = 0;
        aSVIDList += aSVID;
    }
    theStream << FC_InsertVar(aSVIDList);

    numberOfMbrs = myCVID.size();
    theStream << FC_InsertVar(numberOfMbrs);

    string aCVIDList;
    char aCVID[6];
    for (uint32 anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        sprintf(aCVID, "%4d,", myCVID[anIndex]);
        aCVID[5] = 0;
        aCVIDList += aCVID;
    }
    theStream << FC_InsertVar(aCVIDList);

    theStream   << FC_InsertVar(myAisEnabled);
    theStream   << FC_InsertVar(myAisInterval);
    theStream   << FC_InsertVar(myAisMegLevel);
    uint8 aAisDestMacMode = (uint8) myAisDestMacMode;
    theStream   << FC_InsertVar(aAisDestMacMode);
    theStream   << FC_InsertVar(myAisDestMacAddr);
    theStream   << FC_InsertVar(myFacilityLoopBackEnable);
    theStream   << FC_InsertVar(myTerminalLoopBackEnable);

    return theStream;
}

istream& CFG_Evc::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myAllFrames);
    theStream   >> FC_ExtractVar(mySrcIncludedInAnyEVC);
    theStream   >> FC_ExtractVar(myDestIncludedInAnyEVC);
    theStream   >> FC_ExtractVar(myIsProvisioned);
    theStream   >> FC_ExtractVar(myIsProtected);
    theStream   >> FC_ExtractVar(myDestPort);
    theStream   >> FC_ExtractVar(mySrcPort);
    theStream   >> FC_ExtractVar(myEvcPairId);
    theStream   >> FC_ExtractVar(myBWPF);
    theStream   >> FC_ExtractVar(mySTAG);
    theStream   >> FC_ExtractVar(myPauseDiscardEnabled);
    theStream   >> FC_ExtractVar(myPbitRegen);
    theStream   >> FC_ExtractVar(myCFPF);

    uint32  numberOfMbrs;
    uint32 anIndex;

    theStream   >> FC_ExtractVar(numberOfMbrs);
    mySVID.erase(mySVID.begin(), mySVID.end());

    if (numberOfMbrs != 0)
    {
        for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
        {
            mySVID.push_back((uint16) 0);
        }
        char* aSVIDList = new char[numberOfMbrs * 6 + 10];
        theStream >> FC_ExtractVar(aSVIDList);

        char* aSVIDId = strtok(aSVIDList, ",");
        anIndex = 0;
        while ((anIndex < numberOfMbrs) && (aSVIDId != NULL))
        {
            mySVID[anIndex] = ((uint16) atoi(aSVIDId));
            anIndex++;
            aSVIDId = strtok(NULL, ",");
        }

        delete [] aSVIDList;

    }
    else
    {
        string aSVIDList;
        theStream >> FC_ExtractVar(aSVIDList);
    }

    theStream   >> FC_ExtractVar(numberOfMbrs);
    myCVID.erase(myCVID.begin(), myCVID.end());

    if (numberOfMbrs != 0)
    {

        for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
        {
            myCVID.push_back((uint16) 0);
        }

        char* aCVIDList = new char[numberOfMbrs * 6 + 10];
        theStream >> FC_ExtractVar(aCVIDList);

        char* aCVIDId = strtok(aCVIDList, ",");
        anIndex = 0;
        while ((anIndex < numberOfMbrs) && (aCVIDId != NULL))
        {
            myCVID[anIndex] = ((uint16) atoi(aCVIDId));
            anIndex++;
            aCVIDId = strtok(NULL, ",");
        }

        delete [] aCVIDList;
    }
    else
    {
        string aSVIDList;
        theStream >> FC_ExtractVar(aSVIDList);
    }

    theStream   >> FC_ExtractVar(myAisEnabled);
    theStream   >> FC_ExtractVar(myAisInterval);
    theStream   >> FC_ExtractVar(myAisMegLevel);
    uint8 aAisDestMacMode;
    theStream   >> FC_ExtractVar(aAisDestMacMode);
    myAisDestMacMode = (CT_TEL_MacMode) aAisDestMacMode;
    theStream   >> FC_ExtractVar(myAisDestMacAddr);
    theStream   >> FC_ExtractVar(myFacilityLoopBackEnable);
    theStream   >> FC_ExtractVar(myTerminalLoopBackEnable);

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Evc::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   <<  myAllFrames;
    theStream   <<  mySrcIncludedInAnyEVC;
    theStream   <<  myDestIncludedInAnyEVC;
    theStream   <<  myIsProvisioned;
    theStream   <<  myIsProtected;
    theStream   <<  myDestPort;
    theStream   <<  mySrcPort;
    theStream   <<  myEvcPairId;
    theStream   <<  myBWPF;
    theStream   <<  mySTAG;
    theStream   <<  myPauseDiscardEnabled;
    theStream   <<  myPbitRegen;
    theStream   <<  myCFPF;

    uint32  numberOfMbrs;
    numberOfMbrs = mySVID.size();
    theStream << numberOfMbrs;
    for (uint32 anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << mySVID[anIndex];
    }

    numberOfMbrs = myCVID.size();
    theStream << numberOfMbrs;
    for (uint32 anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << myCVID[anIndex];
    }

    theStream   <<  myAisEnabled;
    theStream   <<  myAisInterval;
    theStream   <<  myAisMegLevel;
    uint8 aAisDestMacMode = (uint8) myAisDestMacMode;
    theStream   <<  aAisDestMacMode;
    theStream   <<  myAisDestMacAddr;
    theStream   <<  myFacilityLoopBackEnable;
    theStream   <<  myTerminalLoopBackEnable;

    return theStream;
}

FC_Stream& CFG_Evc::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >>  myAllFrames;
    theStream   >>  mySrcIncludedInAnyEVC;
    theStream   >>  myDestIncludedInAnyEVC;
    theStream   >>  myIsProvisioned;
    theStream   >>  myIsProtected;
    theStream   >>  myDestPort;
    theStream   >>  mySrcPort;
    theStream   >>  myEvcPairId;
    theStream   >>  myBWPF;
    theStream   >>  mySTAG;
    theStream   >>  myPauseDiscardEnabled;
    theStream   >>  myPbitRegen;
    theStream   >>  myCFPF;

    mySVID.erase(mySVID.begin(), mySVID.end());
    uint32  numberOfMbrs;
    uint32 i = 0;
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aSVID;
        theStream >> aSVID;
        mySVID.push_back(aSVID);
    }

    myCVID.erase(myCVID.begin(), myCVID.end());
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aCVID;
        theStream >> aCVID;
        myCVID.push_back(aCVID);
    }

    theStream   >>  myAisEnabled;
    theStream   >>  myAisInterval;
    theStream   >>  myAisMegLevel;
    uint8 aAisDestMacMode;
    theStream   >>  aAisDestMacMode;
    myAisDestMacMode = (CT_TEL_MacMode) aAisDestMacMode;
    theStream   >>  myAisDestMacAddr;
    theStream   >>  myFacilityLoopBackEnable;
    theStream   >>  myTerminalLoopBackEnable;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Evc::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"allfrm",6))
    {
        SetAllFrames(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"sinevc",6))
    {
        SetSrcIncludedInAnyEVC(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"dinevc",6))
    {
        SetDestIncludedInAnyEVC(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"prov",4))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"prot",4))
    {
        SetIsProtected(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"dest",4))
    {
        CT_Port aDst;
        aDst = GetDestPort();
        aDst.SetPortInfo(UNKNOWN_SHELF_ID, uint8(atoi(argv[1])), CT_IntfId(atoi(argv[2])), FAC_SUBTYPE_UNKNOWN, uint8(atoi(argv[3])));
        SetDestPort(aDst);
    }
    else if (!strncmp(aParam,"src",3))
    {
        CT_Port aSrc;
        aSrc = GetSrcPort();
        aSrc.SetPortInfo(UNKNOWN_SHELF_ID, uint8(atoi(argv[1])), CT_IntfId(atoi(argv[2])), CFG_STRING_TO_SUBTYPE(argv[3]), uint8(atoi(argv[4])));
        SetSrcPort(aSrc);
    }
    else if (!strncmp(aParam,"pair",4))
    {
        SetEvcPairId(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"bwpf",4))
    {
        SetBWPF(int(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"stag",4))
    {
        SetSTAG(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"svid"))
    {
        mySVID.erase(mySVID.begin(), mySVID.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aSVIDStr;
            aSVIDStr = strtok(argv[1], ",");
            while (aSVIDStr != 0)
            {
                mySVID.push_back(((uint16) atoi(aSVIDStr)));
                aSVIDStr = strtok(0, ",");
            }
        }
    }
    else if (!strcmp(aParam,"cvid"))
    {
        myCVID.erase(myCVID.begin(), myCVID.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aCVIDStr;
            aCVIDStr = strtok(argv[1], ",");
            while (aCVIDStr != 0)
            {
                myCVID.push_back(((uint16) atoi(aCVIDStr)));
                aCVIDStr = strtok(0, ",");
            }
        }
    }
    else if  (!strncmp(aParam,"pause",5))
    {
        SetPauseDiscardEnabled(argv[1][0]=='e');
    }
    else if  (!strncmp(aParam,"pbit",4))
    {
        SetPbitRegen(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"cfpf",4))
    {
        SetCFPF(int(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"aisen",5))
    {
        SetAisEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"aisint",6))
    {
        SetAisInterval(uint16(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"aismeg",6))
    {
        SetAisMegLevel(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"aisdmac",7))
    {
        SetAisDestMacMode(CFG_STRING_TO_MAC_MODE(argv[1]));
    }
    else if (!strncmp(aParam,"aisdadd",7))
    {
        myAisDestMacAddr = CT_LacpSystemId(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
    }
    else if (!strncmp(aParam,"fac",3))
    {
        SetFacilityLoopBackEnable(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"term",4))
    {
        SetTerminalLoopBackEnable(argv[1][0]=='e');
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "EVC <prov>         <e-nable|d-isable> " << endl;
        fc_cout << "EVC <prot>         <e-nable|d-isable> " << endl;
        fc_cout << "EVC <allfrm>       <e-nable|d-isable> " << endl;
        fc_cout << "EVC <dest>         <Slot Port Channel> " << endl;
        fc_cout << "EVC <src>          <Slot Port SubType Channel> " << endl;
        fc_cout << "EVC <pair>         <0-255> " << endl;
        fc_cout << "EVC <sinevc>       <e-nable|d-isable> " << endl;
        fc_cout << "EVC <dinevc>       <e-nable|d-isable> " << endl;
        fc_cout << "EVC <bwpf>         <int> " << endl;
        fc_cout << "EVC <cfpf>         <int> " << endl;
        fc_cout << "EVC <stag>         0-4094" << endl;
        fc_cout << "EVC <pausediscard> <e-nabled|d-isabled> " << endl;
        fc_cout << "EVC <pbit>         <0,1,2,3,255> (0=Off,1=Both,2=Egress) " << endl;
        fc_cout << "                                 (3=Ingress,255=Unknown)" << endl;
        fc_cout << "EVC <svid>         <list of SVID integers on one line of string> " << endl;
        fc_cout << "                   <separated by a comma or NULL for blank list> " << endl;
        fc_cout << "EVC <cvid>         <list of CVID integers on one line of string> " << endl;
        fc_cout << "                   <separated by a comma or NULL for blank list> " << endl;
        fc_cout << "EVC <aisenable>    <e-nable|d-isable> " << endl;
        fc_cout << "EVC <aisinterval>  <1 | 60> " << endl;
        fc_cout << "EVC <aismeglevel>  <0-7> " << endl;
        fc_cout << "EVC <aisdmacmode>  <unicast | multicast> " << endl;
        fc_cout << "EVC <aisdaddr>     <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated - mac addr)> " << endl;
        fc_cout << "EVC <fac-loop>     <e-nable|d-isable> " << endl;
        fc_cout << "EVC <term-loop>    <e-nable|d-isable> " << endl;
        fc_cout << "EVC Note:          Port 0-12" << endl;
        fc_cout << "EVC Note:          Dest Channel (VCG Index) 0-63" << endl;
        fc_cout << "EVC Note:          Src Channel (Lag Index) 0-12 lag, 0 eth" << endl;
        fc_cout << "EVC Note:          SubType eth or lag" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Evc::Display( FC_Stream& theStream )
{
    theStream   << "EVC - Provisioned           [prov]           = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "EVC - Protected             [prot]           = " << DISPLAY_BOOL(myIsProtected) << endl;
    theStream   << "EVC - All Frames            [allfrm]         = " << DISPLAY_BOOL(myAllFrames) << endl;

    theStream   << "EVC - Eth-AIS Enabled       [aisen]          = " << DISPLAY_BOOL(myAisEnabled) << endl;
    theStream   << "EVC - AIS Interval (xmit)   [aisint]         = " << myAisInterval << endl;
    theStream   << "EVC - AIS MEG Level         [aismeg]         = " << uint16(myAisMegLevel) << endl;
    theStream   << "EVC - AIS Dest Mac Mode     [aisdmac]        = " << DISPLAY_MAC_MODE(myAisDestMacMode) << endl;
    theStream   << "EVC - AIS Dest Mac Addr     [aisdaddr]       = " << myAisDestMacAddr.DisplayAddr() << endl;
    theStream   << "EVC - Facility Loopback     [facloop]        = " << DISPLAY_BOOL(myFacilityLoopBackEnable) << endl;
    theStream   << "EVC - Terminal Loopback     [termloop]       = " << DISPLAY_BOOL(myTerminalLoopBackEnable) << endl;

    theStream   << "EVC - Src In Any EVC        [sinevc]         = " << DISPLAY_BOOL(mySrcIncludedInAnyEVC) << endl;
    theStream   << "EVC - Dst In Any EVC        [dinevc]         = " << DISPLAY_BOOL(myDestIncludedInAnyEVC) << endl;
    theStream   << "EVC - Pair Id               [pair]           = " << uint32(myEvcPairId) << endl;
    theStream   << "EVC - BandWidth Profile     [bwpf]           = " << (int)myBWPF << endl;
    theStream   << "EVC - Control Frame Profile [cfpf]           = " << (int)myCFPF << endl;
    theStream   << "EVC - STAG                  [stag]           = " << (uint32)mySTAG << endl;
    theStream   << "EVC - PauseDiscard          [pausediscard]   = " << DISPLAY_BOOL(myPauseDiscardEnabled) << endl;
    theStream   << "EVC - PbitRegen             [pbit]           = " << (uint32)myPbitRegen  << endl;
    CT_Port* aDstPtr;
    aDstPtr = &myDestPort;
    theStream   << "EVC - Dst Slot Port VcgIdx  [dest]   = " << (uint32)(aDstPtr->GetSlotId()) << " , " << DISPLAY_CT_IntfId(aDstPtr->GetPortId()) << " , " << (uint32)(aDstPtr->GetChannelId()) << endl;
    CT_Port* aSrcPtr;
    aSrcPtr = &mySrcPort;
    theStream   << "EVC - Src Slot Port Type    [src]    = " << (uint32)(aSrcPtr->GetSlotId()) << " , " << DISPLAY_CT_IntfId(aSrcPtr->GetPortId()) << " , " << DISPLAY_CT_FacilitySubType(aSrcPtr->GetPortType()) << " , " << (uint32)(aSrcPtr->GetChannelId()) << endl;
    theStream   << "EVC - SVID List             [svid]   = ";
    vector<uint16>::iterator i;
    for (i = mySVID.begin(); i != mySVID.end(); i++)
    {
        uint aSVID;
        aSVID = uint32(*i);
        theStream << aSVID << ",";
    }
    theStream << endl << "EVC - CVID List             [cvid]   = ";
    for (i = myCVID.begin(); i != myCVID.end(); i++)
    {
        uint aCVID;
        aCVID = uint32(*i);
        theStream << aCVID << ",";
    }
    theStream   << endl;
}

