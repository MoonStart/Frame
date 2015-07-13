//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Vcg.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Vcg::CFG_Vcg(uint32 theIndex):
    CFG_Object(theIndex),
    myIsProvisioned(false),
    myHoldOffTmr(0),
    myWaitToRetoreTmr(0),
    myPartialLossCpyTH(0),
    myTotalLossCpyTH(0),
    myDiffDelay(0),
    myIsConnectedAsSrc(false),
    myIsConnectedAsDest(false),
    myVcatType(CT_TEL_VCAT_UNKNOWN),
    myProtectVcgIdx(CT_TEL_INVALID_VCG_IDX),
    myProtectVcgSlot(UNKNOWN_SLOT_ID),
    myLcasEnabled(false),
    myLayerLocked(false),
    myTTPList(0),
    mySourceTTPList(0),
    mySinkTTPList(0)
//    myDebugFlag(false),
//    myLastTime(0),
//    myShortestTime(0),
//    myLongestTime(0),
//    myPoint1(0),
//    myPoint2(0),
//    myPoint3(0),
//    myPoint4(0),
//    myPoint5(0),
//    myPoint6(0),
//    myPoint7(0),
{
}

CFG_Vcg::~CFG_Vcg(void)
{
}

bool CFG_Vcg::SetHoldOffTmr(uint32 theHoldOffTmr)
{
    bool hasChanged = false;
    if (myHoldOffTmr != theHoldOffTmr)
    {
        myHoldOffTmr = theHoldOffTmr;
        hasChanged = true;
    }
    return hasChanged;
}

uint32 CFG_Vcg::GetHoldOffTmr() const
{
    return myHoldOffTmr;
}

bool CFG_Vcg::SetWaitToRetoreTmr(uint32 theWaitToRetoreTmr)
{
    bool hasChanged = false;
    if (myWaitToRetoreTmr != theWaitToRetoreTmr)
    {
        myWaitToRetoreTmr = theWaitToRetoreTmr;
        hasChanged = true;
    }
    return hasChanged;
}

uint32 CFG_Vcg::GetWaitToRetoreTmr() const
{
    return myWaitToRetoreTmr;
}

bool CFG_Vcg::SetPartialLossCpyTH(uint32 thePartialLossCpyTH)
{
    bool hasChanged = false;
    if (myPartialLossCpyTH != thePartialLossCpyTH)
    {
        myPartialLossCpyTH = thePartialLossCpyTH;
        hasChanged = true;
    }
    return hasChanged;
}

uint32 CFG_Vcg::GetPartialLossCpyTH() const
{
    return myPartialLossCpyTH;
}

bool CFG_Vcg::SetTotalLossCpyTH(uint32 theTotalLossCpyTH)
{
    bool hasChanged = false;
    if (myTotalLossCpyTH != theTotalLossCpyTH)
    {
        myTotalLossCpyTH = theTotalLossCpyTH;
        hasChanged = true;
    }
    return hasChanged;
}

uint32 CFG_Vcg::GetTotalLossCpyTH() const
{
    return myTotalLossCpyTH;
}

bool CFG_Vcg::SetDiffDelay(uint32 theDiffDelay)
{
    bool hasChanged = false;
    if (myDiffDelay != theDiffDelay)
    {
        myDiffDelay = theDiffDelay;
        hasChanged = true;
    }
    return hasChanged;
}

uint32 CFG_Vcg::GetDiffDelay() const
{
    return myDiffDelay;
}

bool CFG_Vcg::SetIsConnectedAsSrc(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsSrc != theState)
    {
        myIsConnectedAsSrc = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_Vcg::GetIsConnectedAsSrc() const
{
    return myIsConnectedAsSrc;
}

bool CFG_Vcg::SetIsConnectedAsDest(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsDest != theState)
    {
        myIsConnectedAsDest = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_Vcg::GetIsConnectedAsDest() const
{
    return myIsConnectedAsDest;
}

void CFG_Vcg::SetVcatType(CT_TEL_VCAT_TYPE theVcatType)
{
    myVcatType = theVcatType;
}

CT_TEL_VCAT_TYPE CFG_Vcg::GetVcatType() const
{
    return myVcatType;
}

void CFG_Vcg::SetTTPList(vector<uint16>& theTTPList)
{
    myTTPList = theTTPList;
}

const vector<uint16>& CFG_Vcg::GetTTPList()
{
    return myTTPList;
}

void CFG_Vcg::SetSourceTTPList(vector<uint16>& theTTPList)
{
    mySourceTTPList = theTTPList;
}

const vector<uint16>& CFG_Vcg::GetSourceTTPList()
{
    return mySourceTTPList;
}

void CFG_Vcg::SetSinkTTPList(vector<uint16>& theTTPList)
{
    mySinkTTPList = theTTPList;
}

const vector<uint16>& CFG_Vcg::GetSinkTTPList()
{
    return mySinkTTPList;
}

void CFG_Vcg::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

bool CFG_Vcg::GetIsProvisioned() const
{
    return myIsProvisioned;
}

void CFG_Vcg::SetLcasEnabled(bool theLcasEnabled)
{
    myLcasEnabled = theLcasEnabled;
}

bool CFG_Vcg::GetLcasEnabled() const
{
    return myLcasEnabled;
}

void CFG_Vcg::SetLayerLocked(bool theState)
{
    myLayerLocked = theState;
}

bool CFG_Vcg::GetLayerLocked() const
{
    return myLayerLocked;
}

bool CFG_Vcg::SetProtectVcgIdx(uint8 theProtectVcgIdx)
{
    bool hasChanged = false;
    if (myProtectVcgIdx != theProtectVcgIdx)
    {
        myProtectVcgIdx = theProtectVcgIdx;
        hasChanged = true;
    }
    return hasChanged;
}

CT_SlotId CFG_Vcg::GetProtectVcgIdx() const
{
    return myProtectVcgIdx;
}

bool CFG_Vcg::SetProtectVcgSlot(CT_SlotId theProtectVcgSlot)
{
    bool hasChanged = false;
    if (myProtectVcgSlot != theProtectVcgSlot)
    {
        myProtectVcgSlot = theProtectVcgSlot;
        hasChanged = true;
    }
    return hasChanged;
}

CT_SlotId CFG_Vcg::GetProtectVcgSlot() const
{
    return myProtectVcgSlot;
}

#if 0 // Debug support to measure process times
void CFG_Vcg::SetDebugFlagSet(bool theDebugEnable)
{
    myDebugFlag = theDebugEnable;
}

bool CFG_Vcg::IsDebugFlagSet() const
{
    return myDebugFlag;
}

void CFG_Vcg::SetProcessTime(const uint32 theTime)
{
    myLastTime = theTime;

    if (myLastTime > myLongestTime)
        myLongestTime = myLastTime;

    if (myShortestTime == 0)
    {
        myShortestTime = myLastTime;
    }
    else if ((myLastTime != 0) && (myLastTime < myShortestTime))
    {
        myShortestTime = myLastTime;
    }
}


void CFG_Vcg::SetBreakdown(const uint32 aPt1, const uint32 aPt2, const uint32 aPt3,
                           const uint32 aPt4, const uint32 aPt5, const uint32 aPt6,
                           const uint32 aPt7)
{
    myPoint1 = aPt1;
    myPoint2 = aPt2;
    myPoint3 = aPt3;
    myPoint4 = aPt4;
    myPoint5 = aPt5;
    myPoint6 = aPt6;
    myPoint7 = aPt7;
}
*/
#endif // end of debug

void CFG_Vcg::Reset(void)
{
    // Initialize all attributes to default values.
    myIsProvisioned     = false;
    myHoldOffTmr        = 0;
    myWaitToRetoreTmr   = 0;
    myPartialLossCpyTH  = 0;
    myTotalLossCpyTH    = 0;
    myDiffDelay         = 0;
    myIsConnectedAsSrc  = false;
    myIsConnectedAsDest = false;
    myVcatType          = CT_TEL_VCAT_UNKNOWN;
    myProtectVcgIdx     = CT_TEL_INVALID_VCG_IDX;
    myProtectVcgSlot    = UNKNOWN_SLOT_ID;
    myLcasEnabled       = false;
    myLayerLocked       = false;
    myTTPList.erase(myTTPList.begin(), myTTPList.end());
    mySourceTTPList.erase(mySourceTTPList.begin(), mySourceTTPList.end());
    mySinkTTPList.erase(mySinkTTPList.begin(), mySinkTTPList.end());
//    myDebugFlag = false;
//    myLastTime = 0;
//    myShortestTime = 0;
//    myLongestTime = 0;
//    myPoint1 = 0;
//    myPoint2 = 0;
//    myPoint3 = 0;
//    myPoint4 = 0;
//    myPoint5 = 0;
//    myPoint6 = 0;
//    myPoint7 = 0;
}

// For Display
ostream& CFG_Vcg::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myIsProvisioned);
    theStream   << FC_InsertVar(myHoldOffTmr);
    theStream   << FC_InsertVar(myWaitToRetoreTmr);
    theStream   << FC_InsertVar(myPartialLossCpyTH);
    theStream   << FC_InsertVar(myTotalLossCpyTH);
    theStream   << FC_InsertVar(myDiffDelay);
    theStream   << FC_InsertVar(myIsConnectedAsSrc);
    theStream   << FC_InsertVar(myIsConnectedAsDest);

    uint32 aVcatType = (uint32) myVcatType;
    theStream   << FC_InsertVar(aVcatType);

    theStream   << FC_InsertVar(myProtectVcgIdx);
    theStream   << FC_InsertVar(myProtectVcgSlot);

    theStream   << FC_InsertVar(myLcasEnabled);

    theStream   << FC_InsertVar(myLayerLocked);

    uint32 anIndex;
    uint32  numberOfMbrs = myTTPList.size();
    theStream << FC_InsertVar(numberOfMbrs);

    /*vector<uint16>::iterator i;
    for (i = myTTPList.begin(); i != myTTPList.end(); i++)
        theStream << FC_InsertVar(*i);*/

    string aTTPIdList;
    char aTTPId[6];
    for (anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        sprintf(aTTPId, "%3d,", myTTPList[anIndex]);
        aTTPId[4] = 0;
        aTTPIdList += aTTPId;
    }
    theStream << FC_InsertVar(aTTPIdList);

    uint32  numberOfSourceMbrs = mySourceTTPList.size();
    theStream << FC_InsertVar(numberOfSourceMbrs);
    string aSourceTTPIdList;
    char aSourceTTPId[6];
    for (anIndex = 0; anIndex < (uint32) numberOfSourceMbrs; anIndex++)
    {
        sprintf(aSourceTTPId, "%3d,", mySourceTTPList[anIndex]);
        aSourceTTPId[4] = 0;
        aSourceTTPIdList += aSourceTTPId;
    }
    theStream << FC_InsertVar(aSourceTTPIdList);

    uint32  numberOfSinkMbrs = mySinkTTPList.size();
    theStream << FC_InsertVar(numberOfSinkMbrs);
    string aSinkTTPIdList;
    char aSinkTTPId[6];
    for (anIndex = 0; anIndex < (uint32) numberOfSinkMbrs; anIndex++)
    {
        sprintf(aSinkTTPId, "%3d,", mySinkTTPList[anIndex]);
        aSinkTTPId[4] = 0;
        aSinkTTPIdList += aSinkTTPId;
    }
    theStream << FC_InsertVar(aSinkTTPIdList);

//    theStream << FC_InsertVar(myDebugFlag);
//    theStream << FC_InsertVar(myLastTime);
//    theStream << FC_InsertVar(myShortestTime);
//    theStream << FC_InsertVar(myLongestTime);
//    theStream << FC_InsertVar(myPoint1);
//    theStream << FC_InsertVar(myPoint2);
//    theStream << FC_InsertVar(myPoint3);
//    theStream << FC_InsertVar(myPoint4);
//    theStream << FC_InsertVar(myPoint5);
//    theStream << FC_InsertVar(myPoint6);
//    theStream << FC_InsertVar(myPoint7);

    return theStream;
}

istream& CFG_Vcg::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myIsProvisioned);
    theStream   >> FC_ExtractVar(myHoldOffTmr);
    theStream   >> FC_ExtractVar(myWaitToRetoreTmr);
    theStream   >> FC_ExtractVar(myPartialLossCpyTH);
    theStream   >> FC_ExtractVar(myTotalLossCpyTH);
    theStream   >> FC_ExtractVar(myDiffDelay);
    theStream   >> FC_ExtractVar(myIsConnectedAsSrc);
    theStream   >> FC_ExtractVar(myIsConnectedAsDest);

    uint32 aVcatType = 0;
    theStream   >> FC_ExtractVar(aVcatType);
    myVcatType = (CT_TEL_VCAT_TYPE) aVcatType;

    theStream   >> FC_ExtractVar(myProtectVcgIdx);
    theStream   >> FC_ExtractVar(myProtectVcgSlot);
    
    theStream   >> FC_ExtractVar(myLcasEnabled);

    theStream   >> FC_ExtractVar(myLayerLocked);

    myTTPList.erase(myTTPList.begin(), myTTPList.end());

    uint32  numberOfMbrs;
    //uint32 i = 0;
    uint32 anIndex;

    theStream   >> FC_ExtractVar(numberOfMbrs);
    /*for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aTTPid;
        theStream >> FC_ExtractVar(aTTPid);
        myTTPList.push_back(aTTPid);
    }*/

    for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        myTTPList.push_back((uint16) 0);
    }

    char aTTPIdList[256];
    theStream >> FC_ExtractVar(aTTPIdList);
    char* aTTPId = strtok(aTTPIdList, ",");
    anIndex = 0;
    while ((anIndex < numberOfMbrs) && (aTTPId != NULL))
    {
        myTTPList[anIndex] = ((uint16) atoi(aTTPId));
        anIndex++;
        aTTPId = strtok(NULL, ",");
    }

    uint32  numberOfSourceMbrs;
    theStream   >> FC_ExtractVar(numberOfSourceMbrs);
    for (anIndex = 0; anIndex < numberOfSourceMbrs; anIndex++)
    {
        mySourceTTPList.push_back((uint16) 0);
    }

    char aSourceTTPIdList[256];
    theStream >> FC_ExtractVar(aSourceTTPIdList);
    char* aSourceTTPId = strtok(aSourceTTPIdList, ",");
    anIndex = 0;
    while ((anIndex < numberOfSourceMbrs) && (aSourceTTPId != NULL))
    {
        mySourceTTPList[anIndex] = ((uint16) atoi(aSourceTTPId));
        anIndex++;
        aSourceTTPId = strtok(NULL, ",");
    }

    uint32  numberOfSinkMbrs;
    theStream   >> FC_ExtractVar(numberOfSinkMbrs);
    for (anIndex = 0; anIndex < numberOfSinkMbrs; anIndex++)
    {
        mySinkTTPList.push_back((uint16) 0);
    }

    char aSinkTTPIdList[256];
    theStream >> FC_ExtractVar(aSinkTTPIdList);
    char* aSinkTTPId = strtok(aSinkTTPIdList, ",");
    anIndex = 0;
    while ((anIndex < numberOfSinkMbrs) && (aSinkTTPId != NULL))
    {
        mySinkTTPList[anIndex] = ((uint16) atoi(aSinkTTPId));
        anIndex++;
        aSinkTTPId = strtok(NULL, ",");
    }
/* Debug
//    theStream >> FC_ExtractVar(myDebugFlag);
//    theStream >> FC_ExtractVar(myLastTime);
//    theStream >> FC_ExtractVar(myShortestTime);
//    theStream >> FC_ExtractVar(myLongestTime);
//    theStream >> FC_ExtractVar(myPoint1);
//    theStream >> FC_ExtractVar(myPoint2);
//    theStream >> FC_ExtractVar(myPoint3);
//    theStream >> FC_ExtractVar(myPoint4);
//    theStream >> FC_ExtractVar(myPoint5);
//    theStream >> FC_ExtractVar(myPoint6);
//    theStream >> FC_ExtractVar(myPoint7);
*/
    return theStream;
}


FC_Stream& CFG_Vcg::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myIsProvisioned;
    theStream   << myHoldOffTmr;
    theStream   << myWaitToRetoreTmr;
    theStream   << myPartialLossCpyTH;
    theStream   << myTotalLossCpyTH;
    theStream   << myDiffDelay;
    theStream   << myIsConnectedAsSrc;
    theStream   << myIsConnectedAsDest;
    theStream   << (uint32) myVcatType;
    theStream   << myProtectVcgIdx;
    theStream   << myProtectVcgSlot;
    theStream   << myLcasEnabled;
    theStream   << myLayerLocked;

    uint32 anIndex;
    uint32  numberOfMbrs = myTTPList.size();
    theStream << numberOfMbrs;

    for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << myTTPList[anIndex];
    }

    numberOfMbrs = mySourceTTPList.size();
    theStream << numberOfMbrs;

    for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << mySourceTTPList[anIndex];
    }

    numberOfMbrs = mySinkTTPList.size();
    theStream << numberOfMbrs;

    for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << mySinkTTPList[anIndex];
    }
    return theStream;
}


FC_Stream& CFG_Vcg::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint32 aVcatType = 0;
    theStream   >> myIsProvisioned;
    theStream   >> myHoldOffTmr;
    theStream   >> myWaitToRetoreTmr;
    theStream   >> myPartialLossCpyTH;
    theStream   >> myTotalLossCpyTH;
    theStream   >> myDiffDelay;
    theStream   >> myIsConnectedAsSrc;
    theStream   >> myIsConnectedAsDest;
    theStream   >> aVcatType;
    myVcatType = (CT_TEL_VCAT_TYPE) aVcatType;
    theStream   >> myProtectVcgIdx;
    theStream   >> myProtectVcgSlot;
    theStream   >> myLcasEnabled;
    theStream   >> myLayerLocked;

    myTTPList.erase(myTTPList.begin(), myTTPList.end());
    mySourceTTPList.erase(mySourceTTPList.begin(), mySourceTTPList.end());
    mySinkTTPList.erase(mySinkTTPList.begin(), mySinkTTPList.end());

    uint32  numberOfMbrs;
    uint32 i = 0;

    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aTTP;
        theStream >> aTTP;
        myTTPList.push_back(aTTP);
    }
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aTTP;
        theStream >> aTTP;
        mySourceTTPList.push_back(aTTP);
    }
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aTTP;
        theStream >> aTTP;
        mySinkTTPList.push_back(aTTP);
    }

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Vcg::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto VCGERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"vcattype"))
    {
        SetVcatType(CFG_STRING_TO_VCAT_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"prov",4))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"hldoff"))
    {
        SetHoldOffTmr(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"waitrst"))
    {
        SetWaitToRetoreTmr(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"plc"))
    {
        SetPartialLossCpyTH(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"tlc"))
    {
        SetTotalLossCpyTH(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"dd"))
    {
        SetDiffDelay(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"dest"))
    {
        SetIsConnectedAsDest(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"src"))
    {
        SetIsConnectedAsSrc(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"vcgidx"))
    {
        SetProtectVcgIdx(atoi(argv[1]));
    }
    else if (!strcmp(aParam,"vcgslot"))
    {
        SetProtectVcgSlot(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"lcas",4)) 
    {
        SetLcasEnabled(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"lock"))
    {
        SetLayerLocked(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"ttplist"))
    {

        myTTPList.erase(myTTPList.begin(), myTTPList.end());

        if(strcmp(argv[1],"NULL"))
        {
            char* aTTPIdStr;

            aTTPIdStr = strtok(argv[1], ",");
            while (aTTPIdStr != 0)
            {
                myTTPList.push_back(((uint16) atoi(aTTPIdStr)));
                aTTPIdStr = strtok(0, ",");
            }
        }

    }
    else if (!strcmp(aParam,"srcttplist"))
    {

        mySourceTTPList.erase(mySourceTTPList.begin(), mySourceTTPList.end());

        if(strcmp(argv[1],"NULL"))
        {
            char* aTTPIdStr;

            aTTPIdStr = strtok(argv[1], ",");
            while (aTTPIdStr != 0)
            {
                mySourceTTPList.push_back(((uint16) atoi(aTTPIdStr)));
                aTTPIdStr = strtok(0, ",");
            }
        }

    }
    else if (!strcmp(aParam,"snkttplist"))
    {

        mySinkTTPList.erase(mySinkTTPList.begin(), mySinkTTPList.end());

        if(strcmp(argv[1],"NULL"))
        {
            char* aTTPIdStr;

            aTTPIdStr = strtok(argv[1], ",");
            while (aTTPIdStr != 0)
            {
                mySinkTTPList.push_back(((uint16) atoi(aTTPIdStr)));
                aTTPIdStr = strtok(0, ",");
            }
        }

    }
//Debug measurement enable
//    else if (!strncmp(argv[0],"deb",3))
//    {
//        SetDebugFlagSet(argv[1][0]=='e');
//    }
    else
    {
        goto VCGERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

VCGERROR:
    {
        fc_cout << "vcg <prov>       <e-nable|d-isable> " << endl;
        fc_cout << "vcg <vcattype>   <sts1|sts3c|vc3|vc4|ds3|e3|ds1|e1> " << endl;
        fc_cout << "vcg <hldoff>     <long integer (time in msecs)> " << endl;
        fc_cout << "vcg <waitrst>    <long integer (time in msecs)> " << endl;
        fc_cout << "vcg <plc>        <integer> " << endl;
        fc_cout << "vcg <tlc>        <integer> " << endl;
        fc_cout << "vcg <dd>         <long integer (time in msecs)> " << endl;
        fc_cout << "vcg <src>        <e-nable|d-isable> " << endl;
        fc_cout << "vcg <dest>       <e-nable|d-isable> " << endl;
        fc_cout << "vcg <vcgidx>     <integer> " << endl;
        fc_cout << "vcg <vcgslot>    <integer> " << endl;
        fc_cout << "vcg <lcas>       <e-nable|d-isable> " << endl;
        fc_cout << "vcg <format>     <gfp|bitx86|bytex86> " << endl;
        fc_cout << "vcg <phyid>      <integer> " << endl;
        fc_cout << "vcg <lock>       <e-nable|d-isable> " << endl;
        fc_cout << "vcg <ttplist>    <list of TTP id integers on one line separated> " << endl;
        fc_cout << "                 <by a comma or type NULL for blank list> " << endl;
        fc_cout << "vcg <srcttplist> <list of TTP id integers on one line separated> " << endl;
        fc_cout << "                 <by a comma or type NULL for blank list> " << endl;
        fc_cout << "vcg <snkttplist> <list of TTP id integers on one line separated> " << endl;
        fc_cout << "                 <by a comma or type NULL for blank list> " << endl;
//        fc_cout << "vcg <debug>      <e-nable|d-isable> (for index 0 only)" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Vcg::Display( FC_Stream& theStream )
{
    theStream   << "VCG   - Provisioned                  [prov]      = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "VCG   - VCAT Type                    [vcattype]  = " << DISPLAY_VCAT_TYPE(myVcatType) << endl;
    theStream   << "VCG   - Hold Off Timer               [hldoff]    = " << myHoldOffTmr         << endl;
    theStream   << "VCG   - Wait To Restore Tmr          [waitrst]   = " << myWaitToRetoreTmr    << endl;
    theStream   << "VCG   - Partial Loss Cap. Tmr        [plc]       = " << myPartialLossCpyTH   << endl;
    theStream   << "VCG   - Total Loss Cap. Tmr          [tlc]       = " << myTotalLossCpyTH     << endl;
    theStream   << "VCG   - Differential Delay           [dd]        = " << myDiffDelay          << endl;
    theStream   << "VCG   - IS CONNECTED AS SOURCE OF XC [src]       = " << DISPLAY_BOOL(myIsConnectedAsSrc)  << endl;
    theStream   << "VCG   - IS CONNECTED AS DEST OF XC   [dest]      = " << DISPLAY_BOOL(myIsConnectedAsDest) << endl;
    theStream   << "VCG   - Protected VCG Index          [vcgidx]    = " << (int)myProtectVcgIdx << endl;
    theStream   << "VCG   - Protected VCG Slot           [vcgslot]   = " << (int)myProtectVcgSlot << endl;
    theStream   << "VCG   - LCAS Enable                  [lcas]      = " << DISPLAY_BOOL(myLcasEnabled) << endl;
    theStream   << "VCG   - Locked                       [lock]      = " << DISPLAY_BOOL(myLayerLocked) << endl;
    theStream   << "VCG   - TTP List                     [ttplist]   = ";

    vector<uint16>::iterator i;
    for (i = myTTPList.begin(); i != myTTPList.end(); i++)
    {
        uint aTTPid;
        aTTPid = uint8(*i);
        theStream << aTTPid << ",";
    }
    theStream << endl;

    theStream   << "VCG   - Source TTP List              [srcttplist]= ";
    for (i = mySourceTTPList.begin(); i != mySourceTTPList.end(); i++)
    {
        uint aTTPid;
        aTTPid = uint8(*i);
        theStream << aTTPid << ",";
    }
    theStream << endl;

    theStream   << "VCG   - Sink TTP List                [snkttplist]= ";
    for (i = mySinkTTPList.begin(); i != mySinkTTPList.end(); i++)
    {
        uint aTTPid;
        aTTPid = uint8(*i);
        theStream << aTTPid << ",";
    }
    theStream << endl;
#if 0
/* debug purpose
    theStream   << "VCG   - Last Time                                = " << myLastTime << endl;
    theStream   << "VCG   - Shortest Time                            = " << myShortestTime << endl;
    theStream   << "VCG   - Longest Time                             = " << myLongestTime << endl;
    theStream   << "VCG   - Last Breakdown = " << myPoint1 << " "  << myPoint2 << " "  << myPoint3 << " "
                                               << myPoint4 << " "  << myPoint5 << " "  << myPoint6 << " "  << myPoint7 << " "  << endl;
*/
#endif
}

