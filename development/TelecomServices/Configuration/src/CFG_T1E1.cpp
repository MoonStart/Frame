//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_T1E1.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_T1E1::CFG_T1E1(uint32 theIndex):
    CFG_Object(theIndex),
    myT1E1Enable(false),
    myT1E1LineCode(CT_LineCode_ALL),
    myT1E1FramingType(CT_FrameFormat_ALL),
    myTimingSourceShelf(UNKNOWN_SHELF_ID),
    myTimingSourceSlot(UNKNOWN_SLOT_ID),
    mySABIT(CT_SaBit_UNKNOWN),
    myQLOverride(CT_QualityLevelOverride_DISABLED)
{
    // Add the ClkOutEnableList
    uint32 anIndex;
    for (anIndex = 0; anIndex < NUMBER_OF_BPCLKS_ON_OPSM ; anIndex++)
    {
        AddToClkOutEnableList(false);
    }
}

CFG_T1E1::~CFG_T1E1(void)
{
}


//This method is used to indicate that the T1E1 facility is configured (for LED)
void CFG_T1E1::SetT1E1Enable(bool theT1E1Enable)
{
    myT1E1Enable = theT1E1Enable;
}

//This method returns the state of the T1E1 facility.
bool CFG_T1E1::GetT1E1Enable() const
{
    return myT1E1Enable;
}


// Set T1E1 Line Code
void CFG_T1E1::SetT1E1LineCoding(CT_FAC_LineCode theT1E1LineCode)
{
    myT1E1LineCode = theT1E1LineCode;
}

//Get T1E1 Line Code
CT_FAC_LineCode CFG_T1E1::GetT1E1LineCoding() const
{
    return myT1E1LineCode;
}


// Set T1E1 Framing  type
void CFG_T1E1::SetT1E1FramingType(CT_FAC_FrameFormat theT1E1FramingType)
{
    myT1E1FramingType = theT1E1FramingType;
}

//Get T1E1 Framing type
CT_FAC_FrameFormat CFG_T1E1::GetT1E1FramingType() const
{
    return myT1E1FramingType;
}


// Set one item of the list of clock output enables that support the T1E1 facility
void CFG_T1E1::SetClkOutEnable(uint32 theSlotNum, bool theClkOutEnable)
{
    uint32 aListSize = myClkOutEnableList.size();
    if ((theSlotNum > 0) && (theSlotNum <= aListSize))
    {
        myClkOutEnableList[theSlotNum-1] = theClkOutEnable;
    }
}

// Get one itemof the list of clock output enables that support the T1E1 facility
bool CFG_T1E1::GetClkOutEnable(uint32 theSlotNum)
{
    bool retClkOutEnable = false;

    uint32 aListSize = myClkOutEnableList.size();
    if ((theSlotNum > 0) && (theSlotNum <= aListSize))
    {
        retClkOutEnable = myClkOutEnableList[theSlotNum-1];
    }

    return retClkOutEnable;
}


// Set list of clock output enables that support the T1E1 facility
void CFG_T1E1::SetClkOutEnableList(vector<bool>& theClkOutEnableList)
{
    myClkOutEnableList = theClkOutEnableList;
}

// Get list of clock output enables that support the T1E1 facility
const vector<bool>& CFG_T1E1::GetClkOutEnableList()
{
    return myClkOutEnableList;
}



// Add item to list of clock output enables that support the T1E1 facility
void CFG_T1E1::AddToClkOutEnableList(bool theInitialValue)
{
    myClkOutEnableList.push_back(theInitialValue);
}

//Set timing source shelf
void CFG_T1E1::SetTimingSourceShelf(CT_ShelfId sourceShelf)
{
    myTimingSourceShelf = sourceShelf;
}

//Get timing source shelf
CT_ShelfId CFG_T1E1::GetTimingSourceShelf() const
{
    return myTimingSourceShelf;
}

//Set timing source slot
void CFG_T1E1::SetTimingSourceSlot(CT_SlotId sourceSlot)
{
    myTimingSourceSlot = sourceSlot;
}

//Get timing source slot
CT_SlotId CFG_T1E1::GetTimingSourceSlot() const
{
    return myTimingSourceSlot;
}

//Set timing source slot
void CFG_T1E1::SetSABIT(CT_FAC_SaBit theSABIT)
{
    mySABIT = theSABIT;
}

//Get timing source slot
CT_FAC_SaBit CFG_T1E1::GetSABIT() const
{
    return mySABIT;
}

//Set QL override value
void CFG_T1E1::SetQualityLevelOverride(CT_FAC_QualityLevelOverride theQLOverride)
{
    myQLOverride = theQLOverride;
}

//Get configured QL override value
CT_FAC_QualityLevelOverride CFG_T1E1::GetQualityLevelOverride()
{
    return myQLOverride;
}

void CFG_T1E1::Reset(void)
{
    // Initialize all attributes to default values.
    myT1E1Enable = false;
    myT1E1LineCode = CT_LineCode_ALL;
    myT1E1FramingType = CT_FrameFormat_ALL;
    uint32 aListSize = myClkOutEnableList.size();
    for (uint32 anIndex = 0; anIndex < (uint32) aListSize; anIndex++)
    {
        myClkOutEnableList[anIndex] = false;
    }

    myTimingSourceShelf = UNKNOWN_SHELF_ID;
    myTimingSourceSlot = UNKNOWN_SLOT_ID;
    mySABIT = CT_SaBit_UNKNOWN;
    myQLOverride = CT_QualityLevelOverride_DISABLED;
}

ostream& CFG_T1E1::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myT1E1Enable);

    uint32 aT1E1Code = (uint32) myT1E1LineCode;
    theStream   << FC_InsertVar(aT1E1Code);

    uint32 aT1E1Type = (uint32) myT1E1FramingType;
    theStream   << FC_InsertVar(aT1E1Type);

    uint32 aListSize = myClkOutEnableList.size();
    for (uint32 anIndex = 0; anIndex < aListSize; anIndex++)
    {
        bool aClkOutEnabled = myClkOutEnableList[anIndex];
        theStream   << FC_InsertVar(aClkOutEnabled);
    }

    theStream   << FC_InsertVar(myTimingSourceShelf);
    theStream   << FC_InsertVar(myTimingSourceSlot);

    uint32 aSABIT = (uint32) mySABIT;
    theStream   << FC_InsertVar(aSABIT);

    uint32 aQLOverride = (uint32) myQLOverride;
    theStream << FC_InsertVar(aQLOverride);

    return theStream;
}

istream& CFG_T1E1::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myT1E1Enable);

    uint32 aT1E1Code = 0;
    theStream   >> FC_ExtractVar(aT1E1Code);
    myT1E1LineCode = (CT_FAC_LineCode) aT1E1Code;

    uint32 aT1E1Type = 0;
    theStream   >> FC_ExtractVar(aT1E1Type);
    myT1E1FramingType = (CT_FAC_FrameFormat) aT1E1Type;

    bool aClkOutEnabled = false;
    uint32 aListSize = myClkOutEnableList.size();
    for (uint32 anIndex = 0; anIndex < aListSize; anIndex++)
    {
        theStream   >> FC_ExtractVar(aClkOutEnabled);
        myClkOutEnableList[anIndex] = aClkOutEnabled;
    }

    theStream   >> FC_ExtractVar(myTimingSourceShelf );
    theStream   >> FC_ExtractVar(myTimingSourceSlot);
    uint32 aSABIT = 0;
    theStream   >> FC_ExtractVar(aSABIT);
    mySABIT = (CT_FAC_SaBit)aSABIT;
    uint32 aQLOverride = 0;
    theStream   >> FC_ExtractVar(aQLOverride);
    myQLOverride = (CT_FAC_QualityLevelOverride)aQLOverride;
    return theStream;
}

FC_Stream& CFG_T1E1::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myT1E1Enable;
    theStream   << (uint32)myT1E1LineCode;
    theStream   << (uint32)myT1E1FramingType;

    uint32 aListSize = myClkOutEnableList.size();
    uint32 anIndex;
    for (anIndex = 0; anIndex < (uint32) aListSize; anIndex++)
    {
        theStream << myClkOutEnableList[anIndex];
    }

    theStream   << myTimingSourceShelf;
    theStream   << myTimingSourceSlot;
    theStream   << (uint32)mySABIT;
    theStream   << (uint32)myQLOverride;

    return theStream;
}

FC_Stream& CFG_T1E1::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myT1E1Enable;

    uint32 aT1E1Code = 0;
    theStream   >> aT1E1Code;
    myT1E1LineCode = (CT_FAC_LineCode)aT1E1Code;

    uint32 aT1E1Type = 0;
    theStream   >> aT1E1Type;
    myT1E1FramingType = (CT_FAC_FrameFormat)aT1E1Type;

    bool aClkOutEnabled = false;
    uint32 aListSize = myClkOutEnableList.size();
    for (uint32 anIndex = 0; anIndex < aListSize; anIndex++)
    {
        theStream   >> aClkOutEnabled;
        myClkOutEnableList[anIndex] = aClkOutEnabled;
    }

    theStream   >> myTimingSourceShelf;
    theStream   >> myTimingSourceSlot;

    uint32 aSABIT = 0;
    theStream   >> aSABIT;
    mySABIT = (CT_FAC_SaBit)aSABIT;

    uint32 aQLOverride = 0;
    theStream   >> aQLOverride;
    myQLOverride = (CT_FAC_QualityLevelOverride)aQLOverride;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_T1E1::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto T1E1ERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"ena",3))
    {
        SetT1E1Enable(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"lin",3))
    {
        SetT1E1LineCoding(CFG_STRING_TO_LINECODE(argv[1]));
    }
    else if (!strncmp(aParam,"fra",3))
    {
        SetT1E1FramingType(CFG_STRING_TO_FRAMINGTYPE(argv[1]));
    }
    else if (!strncmp(aParam,"clk",3))
    {
        uint32 aListSize = myClkOutEnableList.size();
        uint32 aSlotNum  = uint32(atoi(argv[1]));
        if (aSlotNum < aListSize)
        {
            SetClkOutEnable(aSlotNum + 1, argv[2][0]=='e');
        }
        else
        {
            goto T1E1ERROR;
        }
    }
    else if (!strncmp(aParam,"ref",3))
    {
        if(argc == 3)
        {
            int shelf = atoi(argv[1]);
            int slot  = atoi(argv[2]);

            // Check to make sure each argument is valid
            if ((shelf < 1 || shelf> 13 || slot <0 || slot > 19))
            {
                goto T1E1ERROR;
            }
            else
            {
                SetTimingSourceShelf((CT_ShelfId)shelf);
                SetTimingSourceSlot((CT_SlotId)slot);
            }
        }
    }
    else if (!strncmp(aParam,"sabit",5))
    {
        SetSABIT(CFG_STRING_TO_SABIT(argv[1]));
    }
    else if (!strncmp(aParam,"qloverride",5))
    {
        SetQualityLevelOverride(CFG_STRING_TO_QLOVERRIDE(argv[1]));
    }
    else
    {
        goto T1E1ERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

T1E1ERROR:
    {
        fc_cout << "T1E1 <enable>        <e-nable|d-isable> " << endl;
        fc_cout << "T1E1 <linecode>      <ami|b8zs|hdb3> " << endl;
        fc_cout << "T1E1 <framingtype>   <sf|esf|crc4|nocrc4> " << endl;
        fc_cout << "T1E1 <clkoutenable>  <index: 0-15>  <e-nable|d-isable>" << endl;
        fc_cout << "T1E1 <sabit>  <4-8>" << endl;
        fc_cout << "T1E1 <qloverride>    <disabled|dnu|prc|sec|ssua|ssub>" << endl;
        fc_cout << "T1E1 <refShelfandRefSlot> (Note: Enter all two fields on single line) " << endl;
        fc_cout << "                     <refShelf: 1-15> " << endl;
        fc_cout << "                     <refSlot:  0-19>"  << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_T1E1::Display( FC_Stream& theStream )
{
    theStream   << "T1E1       - Enable/Configured    [enable]            = " << DISPLAY_BOOL(myT1E1Enable) << endl;
    theStream   << "T1E1       - Line Coding          [linecode]          = " << DISPLAY_LINECODE(myT1E1LineCode) << endl;
    theStream   << "T1E1       - Framing Type         [framingtype]       = " << display_FRAMEFORMAT(myT1E1FramingType) << endl;
    uint32 aListSize = myClkOutEnableList.size();
    for (uint32 anIndex = 0; anIndex < aListSize; anIndex++)
    {
        // vertically line up output
        if (anIndex == 0)
        {
            theStream << "T1E1       - ClkOutEnableList     clkoutenable[" << anIndex << "]     = " << DISPLAY_BOOL(myClkOutEnableList[anIndex]) << endl;
        }
        else if ((anIndex > 0) && (anIndex < 10))

        {
            theStream << "T1E1       -                      clkoutenable[" << anIndex << "]     = " << DISPLAY_BOOL(myClkOutEnableList[anIndex]) << endl;
        }
        else
        {
            theStream << "T1E1       -                      clkoutenable[" << anIndex << "]    = " << DISPLAY_BOOL(myClkOutEnableList[anIndex]) << endl;
        }
    }

    int theTimingSourceSlot = myTimingSourceSlot;
    theStream   << "T1E1       - TimingSourceShelf    [shelf]             = " << myTimingSourceShelf << endl;
    theStream   << "T1E1       - TimingSourceSlot     [slot]              = " << theTimingSourceSlot << endl;
    theStream   << "T1E1       - SSM SaBit            [sabit]             = " << display_SABIT(mySABIT) << endl;
    theStream   << "T1E1       - QL Override          [qloverride]        = " << display_QLOVERRIDE(myQLOverride) << endl;

    theStream << endl;
}

