//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Gfp.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Gfp::CFG_Gfp(uint32 theIndex):
    CFG_Object(theIndex),
    myFramingMode(CT_TEL_GFP_FRAMING_UNKNOWN),
    myAutoNegotiationEnabled(false),
    myAutoNegSessionCounter(0),
    mySuperblockSize(1),
    myPauseDiscardEnabled(true),
    myUpi(CT_TEL_GfpUpiId_G709AMD3),
    myExtEnabled(false),
    myExtChannelId(0),
    myDebugFlag(false),
    myIgnoreLosLosync(false),
    myLastTime(0),
    myShortestTime(0),
    myLongestTime(0),
    myRealTimeDefLastTime(0),
    myRealTimeDefShortestTime(0),
    myRealTimeDefLongestTime(0),
    myRealTimeDefectReadPasses(0),
    myNormalReadPasses(0)
{
}

CFG_Gfp::~CFG_Gfp(void)
{
}

bool CFG_Gfp::SetFramingMode(CT_TEL_GfpFramingMode theFramingMode)
{
    bool hasChanged = (myFramingMode != theFramingMode);
    myFramingMode = theFramingMode;
    return hasChanged;
}

CT_TEL_GfpFramingMode CFG_Gfp::GetFramingMode() const
{
    return myFramingMode;
}

bool CFG_Gfp::SetEnableMode(bool theEnableMode)
{
    bool hasChanged = (myEnableMode != theEnableMode);
    myEnableMode = theEnableMode;
    return hasChanged;
}

bool CFG_Gfp::GetEnableMode() const
{
    return myEnableMode;
}

bool CFG_Gfp::SetAutoNegotiationEnabled(bool theAutoNegotiationEnabled)
{
    bool hasChanged = (myAutoNegotiationEnabled != theAutoNegotiationEnabled);
    myAutoNegotiationEnabled = theAutoNegotiationEnabled;
    return hasChanged;
}

bool CFG_Gfp::GetAutoNegotiationEnabled() const
{
    return myAutoNegotiationEnabled;
}

bool CFG_Gfp::SetAutoNegSessionCounter(uint32 theAutoNegSessionCounter)
{
    bool hasChanged = (myAutoNegSessionCounter != theAutoNegSessionCounter);
    myAutoNegSessionCounter = theAutoNegSessionCounter;
    return hasChanged;
}

uint32 CFG_Gfp::GetAutoNegSessionCounter() const
{
    return myAutoNegSessionCounter;
}

bool CFG_Gfp::SetSuperblockSize(uint32 theSuperblockSize)
{
    bool hasChanged = (mySuperblockSize != theSuperblockSize);
    mySuperblockSize = theSuperblockSize;
    return hasChanged;
}

uint32 CFG_Gfp::GetSuperblockSize() const
{
    return mySuperblockSize;
}

bool CFG_Gfp::SetPauseDiscardEnabled(bool thePauseDiscardEnabled)
{
    bool hasChanged = (myPauseDiscardEnabled != thePauseDiscardEnabled);
    myPauseDiscardEnabled = thePauseDiscardEnabled;
    return hasChanged;
}

bool CFG_Gfp::GetPauseDiscardEnabled() const
{
    return myPauseDiscardEnabled;
}


bool CFG_Gfp::SetUpi(CT_TEL_GfpUpiId theUpi)
{
    bool hasChanged = (myUpi != theUpi);
    myUpi = theUpi;
    return hasChanged;
}

CT_TEL_GfpUpiId CFG_Gfp::GetUpi() const
{
    return myUpi;
}


bool CFG_Gfp::SetExtEnabled(bool theExtEnabled)
{
    bool hasChanged = (myExtEnabled != theExtEnabled);
    myExtEnabled = theExtEnabled;
    return hasChanged;
}

bool CFG_Gfp::GetExtEnabled() const
{
    return myExtEnabled;
}


bool CFG_Gfp::SetExtChannelId(uint8 theExtChannelId)
{
    bool hasChanged = (myExtChannelId != theExtChannelId);
    myExtChannelId = theExtChannelId;
    return hasChanged;
}

uint8 CFG_Gfp::GetExtChannelId() const
{
    return myExtChannelId;
}



void CFG_Gfp::SetDebugFlagSet(bool theDebugEnable)
{
    myDebugFlag = theDebugEnable;
}

bool CFG_Gfp::IsDebugFlagSet() const
{
    return myDebugFlag;
}

bool CFG_Gfp::SetIgnoreLosLosyncFlag(bool theIgnoreFlag)
{
    bool hasChanged = (myIgnoreLosLosync != theIgnoreFlag);
    myIgnoreLosLosync = theIgnoreFlag;
    return hasChanged;
}

bool CFG_Gfp::GetIgnoreLosLosyncFlag() const
{
    return myIgnoreLosLosync;
}


void CFG_Gfp::SetProcessTime(const uint32 theTime, bool theRealTimeDefectsRead, uint32 theRealTimeDefectReadPasses, uint32 theNormalReadPasses)
{
    myRealTimeDefectReadPasses = theRealTimeDefectReadPasses; 
    myNormalReadPasses = theNormalReadPasses;

    if (theRealTimeDefectsRead)
    {
        myRealTimeDefLastTime = theTime;

        if (myRealTimeDefLastTime > myRealTimeDefLongestTime)
            myRealTimeDefLongestTime = myRealTimeDefLastTime;

        if (myRealTimeDefShortestTime == 0)
        {
            myRealTimeDefShortestTime = myRealTimeDefLastTime;
        }
        else if ((myRealTimeDefLastTime != 0) && (myRealTimeDefLastTime < myRealTimeDefShortestTime))
        {
            myRealTimeDefShortestTime = myRealTimeDefLastTime;
        }
    }
    else
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
}


void CFG_Gfp::Reset(void)

{
    // Initialize all attributes to default values.
    myFramingMode = CT_TEL_GFP_FRAMING_UNKNOWN;
    myEnableMode = false;
    myAutoNegotiationEnabled = false;
    myAutoNegSessionCounter = 0;
    mySuperblockSize = 1;
    myPauseDiscardEnabled = true;
    myUpi = CT_TEL_GfpUpiId_G709AMD3;
    myExtEnabled = false;
    myExtChannelId = 0;
    myDebugFlag = false;
    myIgnoreLosLosync = false;
    myLastTime = 0;
    myShortestTime = 0;
    myLongestTime = 0;
    myRealTimeDefLastTime = 0;
    myRealTimeDefShortestTime = 0;
    myRealTimeDefLongestTime = 0;
    myRealTimeDefectReadPasses = 0;
    myNormalReadPasses = 0;
}

// For Display
ostream& CFG_Gfp::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint32 aGfpFramingMode = (uint32) myFramingMode;

    theStream   << FC_InsertVar(aGfpFramingMode);
    theStream   << FC_InsertVar(myEnableMode);
    theStream   << FC_InsertVar(myAutoNegotiationEnabled);
    theStream   << FC_InsertVar(myAutoNegSessionCounter);
    theStream   << FC_InsertVar(mySuperblockSize);
    theStream   << FC_InsertVar(myPauseDiscardEnabled);
    theStream   << FC_InsertVar(myUpi);
    theStream   << FC_InsertVar(myExtEnabled);
    theStream   << FC_InsertVar(myExtChannelId);

    theStream   << FC_InsertVar(myDebugFlag);
    theStream   << FC_InsertVar(myIgnoreLosLosync);

    theStream   << FC_InsertVar(myLastTime);
    theStream   << FC_InsertVar(myShortestTime);
    theStream   << FC_InsertVar(myLongestTime);
    theStream   << FC_InsertVar(myRealTimeDefLastTime);
    theStream   << FC_InsertVar(myRealTimeDefShortestTime);
    theStream   << FC_InsertVar(myRealTimeDefLongestTime);
    theStream   << FC_InsertVar(myRealTimeDefectReadPasses);
    theStream   << FC_InsertVar(myNormalReadPasses);

    return theStream;
}

istream& CFG_Gfp::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint32 aGfpFramingMode = 0;

    theStream   >> FC_ExtractVar(aGfpFramingMode);
    theStream   >> FC_ExtractVar(myEnableMode);
    theStream   >> FC_ExtractVar(myAutoNegotiationEnabled);
    theStream   >> FC_ExtractVar(myAutoNegSessionCounter);
    theStream   >> FC_ExtractVar(mySuperblockSize);
    theStream   >> FC_ExtractVar(myPauseDiscardEnabled);
    theStream   >> FC_ExtractVar(myUpi);
    theStream   >> FC_ExtractVar(myExtEnabled);
    theStream   >> FC_ExtractVar(myExtChannelId);

    myFramingMode = (CT_TEL_GfpFramingMode) aGfpFramingMode;

    theStream >> FC_ExtractVar(myDebugFlag);
    theStream >> FC_ExtractVar(myIgnoreLosLosync);
    theStream >> FC_ExtractVar(myLastTime);
    theStream >> FC_ExtractVar(myShortestTime);
    theStream >> FC_ExtractVar(myLongestTime);
    theStream >> FC_ExtractVar(myRealTimeDefLastTime);
    theStream >> FC_ExtractVar(myRealTimeDefShortestTime);
    theStream >> FC_ExtractVar(myRealTimeDefLongestTime);
    theStream >> FC_ExtractVar(myRealTimeDefectReadPasses);
    theStream >> FC_ExtractVar(myNormalReadPasses);

    return theStream;
}


FC_Stream& CFG_Gfp::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << (uint32) myFramingMode;
    theStream << myEnableMode;
    theStream << myAutoNegotiationEnabled;
    theStream << myAutoNegSessionCounter;
    theStream << mySuperblockSize;
    theStream << myPauseDiscardEnabled;
    theStream << myUpi;
    theStream << myExtEnabled;
    theStream << myExtChannelId;
    theStream << myIgnoreLosLosync;
    return theStream;
}

FC_Stream& CFG_Gfp::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    uint32 aGfpFramingMode = 0;

    theStream   >> aGfpFramingMode;
    theStream   >> myEnableMode;
    theStream   >> myAutoNegotiationEnabled;
    theStream   >> myAutoNegSessionCounter;
    theStream   >> mySuperblockSize;
    theStream   >> myPauseDiscardEnabled;
    theStream   >> myUpi;
    theStream   >> myExtEnabled;
    theStream   >> myExtChannelId;
    theStream   >> myIgnoreLosLosync;

    myFramingMode = (CT_TEL_GfpFramingMode) aGfpFramingMode;
    
    return theStream;
}

FC_CmdProcessor::STATUS CFG_Gfp::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto GFPERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"fram",4))
    {
        SetFramingMode(CFG_STRING_TO_GFP_FRAMING_MODE(argv[1]));
    }
    else if (!strncmp(aParam,"gfpe",4))
    {
        SetEnableMode(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"auton",5))
    {
        SetAutoNegotiationEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"autos",5))
    {
        SetAutoNegSessionCounter(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"super",5))
    {
        SetSuperblockSize(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if  (!strncmp(aParam,"pause",5))
    {
        SetPauseDiscardEnabled(argv[1][0]=='e');
    }
    else if(!strncmp(aParam,"upi",3))
    {
        if(argv[1][0]=='t')
            SetUpi( CT_TEL_GfpUpiId_TLABLEGACY );
        else if(argv[1][0]=='s')
            SetUpi( CT_TEL_GfpUpiId_GSUPP43 );
        else if(argv[1][0]=='g')
            SetUpi( CT_TEL_GfpUpiId_G709AMD3 );
    }
    else if (!strncmp(aParam,"exten",5))
    {
        SetExtEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"extch",5))
    {
        SetExtChannelId(atoi(argv[1]));
    }
    //Debug measurement enable
    else if (!strncmp(argv[0],"deb",3))
    {
        SetDebugFlagSet(argv[1][0]=='e');
    }
    else
    {
        goto GFPERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

GFPERROR:
    {
        fc_cout << "gfp <fram-ing>      <f-ramed|t-ransparent> " << endl;
        fc_cout << "gfp <gfpe-nabled>   <e-nabled|d-isabled> " << endl;
        fc_cout << "gfp <auton-eg>      <e-nabled|d-isabled> " << endl;
        fc_cout << "gfp <autos-ession>  <long integer (counter)> " << endl;
        fc_cout << "gfp <super-blocksz> <long integer> " << endl;
        fc_cout << "gfp <pause-discard> <e-nabled|d-isabled> " << endl;
        fc_cout << "gfp <upi>           <t-tlablegacy|s-gsupp43|g-G709amd3> " << endl;
        fc_cout << "gfp <exten-abled>   <e-nabled|d-isabled> " << endl;
        fc_cout << "gfp <extch-annel>   <uint8 extension channel ID> " << endl;
        fc_cout << "gfp <debug>         <e-nable|d-isable> (for index 0 only)" << endl;
        fc_cout << endl;      
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}


void CFG_Gfp::Display( FC_Stream& theStream )
{
    theStream   << "GFP       - GFP Framing           [framing]          = " << DISPLAY_GFP_FRAMING(myFramingMode) << endl;
    theStream   << "GFP       - GFP Enabled           [gfpenabled]       = " << DISPLAY_BOOL(myEnableMode) << endl;
    theStream   << "GFP       - GFP Auto-Negotiation  [autoneg]          = " << DISPLAY_BOOL(myAutoNegotiationEnabled) << endl;
    theStream   << "GFP       - GFP Auto-NegSession   [autosession]      = " << myAutoNegSessionCounter << endl;
    theStream   << "GFP       - GFP Super Block Size  [superblocksz]     = " << mySuperblockSize << endl;
    theStream   << "GFP       - GFP Pause Discard     [pausediscard]     = " << DISPLAY_BOOL(myPauseDiscardEnabled) << endl;
    theStream   << "GFP       - GFP UPI               [upi]              = " << DISPLAY_GFP_UPI(myUpi) << endl;
    theStream   << "GFP       - GFP Ext Enabled       [extenabled]       = " << DISPLAY_BOOL(myExtEnabled) << endl;
    theStream   << "GFP       - GFP Ignore LOS/LOSYNC [ignoreloslosync]  = " << DISPLAY_BOOL(myIgnoreLosLosync) << endl;
    theStream   << "GFP       - GFP Ext Channel ID    [extchannel]       = " << (uint32)myExtChannelId << endl;
    theStream   << endl;
if (myDebugFlag)
{
    theStream   << "GFP       - Normal Read Passes                  = " << myNormalReadPasses << endl;
    theStream   << "GFP       - Last Time                           = " << myLastTime << endl;
    theStream   << "GFP       - Shortest Time                       = " << myShortestTime << endl;
    theStream   << "GFP       - Longest Time                        = " << myLongestTime << endl;
    theStream   << endl;
    theStream   << "GFP       - Real Time Def Read Passes           = " << myRealTimeDefectReadPasses << endl;
    theStream   << "GFP       - Last Real Time Def Read Time        = " << myRealTimeDefLastTime << endl;
    theStream   << "GFP       - Shortest Real Time Def Read Time    = " << myRealTimeDefShortestTime << endl;
    theStream   << "GFP       - Longest Real Time Def Read Time     = " << myRealTimeDefLongestTime << endl;
    theStream   << endl;
}
}

