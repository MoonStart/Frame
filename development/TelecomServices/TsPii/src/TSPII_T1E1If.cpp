/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_T1E1If.cpp 
* Type:    C++ source
* Description:
*     Definition of the class TSPII_T1E1If which models the simulation
*     T1E1 Interface entity within the 7100 System        
*
*     The T1E1 entity is used to configure and monitor T1/E1 interface 
*     (Transceiver/Framer & BITS Clock source) hardware, and also
*     the clock distribution and control. 
*
*************************************END***************************************
*/

#include "TsPii/TSPII_T1E1If.h"
#include <string.h>

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If constructor
*
* Description:
*     TSPII_T1If class constructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_T1E1If::TSPII_T1E1If(uint theClkOutSize, bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    itsClkOutSize = theClkOutSize;
    Reset();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If destructor
*
* Description:
*     TSPII_T1E1If class destructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_T1E1If::~TSPII_T1E1If()
{   
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::RefreshGet() class method
*
* Description:
*     Used to refresh the T1E1 entity attributes.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::RefreshGet()
{
    // T1E1 Monitoring attributes
    itsLofDefect = GetLof();
    itsLosDefect = GetLos();
    itsAisDefect = GetAis();
	itsOffFreqDefect = GetOffFreq();
    itsSsmCode   = GetRxSsm();     

    // T1E1 Configuration attributes
    itsLineCode = GetLineCoding();       
    itsFramingType = GetFramingType();
    GetTimingSource(itsTimingSourceShelf, itsTimingSourceSlot);
    itsSsmSaBit = GetSSMSaBit();

    // Get Clock control attributes - Enable/Disable list and disqualify state
    for (uint16 i = 0; i < itsClkOutSize; i++ ) 
    {
        myClkOutEnableList[i] = GetClkOutEnable(i);
    }
    
    itsClkRefDisqualified = GetClkDisqualifyRef();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::RefreshSet() class method
*
* Description:
*     Used to refresh the T1E1 configuration
*
* Inputs:
*     None
*
* Outputs:
*     FrameFormat, LineCode and clock control are reconfigured
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::RefreshSet()
{
    // set T1 configuration attributes
    SetFramingType(itsFramingType);
    SetLineCoding(itsLineCode);
    GetTimingSource(itsTimingSourceShelf, itsTimingSourceSlot);
    SetSSMSaBit(itsSsmSaBit);

    // set clock control attributes

    for (uint16 i = 0; i < itsClkOutSize; i++ ) 
    {
        SetClkOutput(i, myClkOutEnableList[i]);
    }

    SetClkDisqualifyRef(itsClkRefDisqualified);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::Reset() class method
*
* Description:
*     Used to reset the T1E1 entity attributes to a default state.
*
* Inputs:
*     None
*
* Outputs:
*     Monitor attributes zeroed
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::Reset()
{
    TSPII_BaseIf::Reset();
    
    // Reset monitor attributes
    itsLofDefect = 0;
    itsLosDefect = 0;
    itsAisDefect = 0;
	itsOffFreqDefect = 0;
    itsSsmCode = CT_TEL_NOT_SUPPORTED_SSM; 
        
    // Reset T1 configuration attributes
    itsLineCode = CT_LineCode_AMI;       
    itsFramingType = CT_FrameFormat_SF; 
    itsTimingSourceShelf = UNKNOWN_SHELF_ID;
    itsTimingSourceSlot  = UNKNOWN_SLOT_ID;
    itsSsmSaBit = CT_SaBit_UNKNOWN;

    // Reset clock control attributes
    itsClkRefDisqualified = FALSE;   // disqualified state (not available)
    
    // is this the first T1E1 reset? Then size will always be zero
    if ( myClkOutEnableList.size() < itsClkOutSize )
    {
        // empty the container just in case - to keep the size right
        myClkOutEnableList.clear();

        for ( uint16 i=0; i < itsClkOutSize; i++ )
        {
            // initialize vector
            myClkOutEnableList.push_back(FALSE);
        }
    }
    else if ( myClkOutEnableList.size() <= itsClkOutSize )
    {
        for ( uint16 i=0; i < itsClkOutSize; i++ )
        {
            // reset vector elements
            myClkOutEnableList[i] = FALSE;
        }
    }
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetLineCoding() class method
*
* Description:
*     Used to configure the Line Code for the T1/E1 framer hardware.
*
* Inputs:
*     Value which specifies the possible T1E1 framer hardware line codes.
*     
*     Values:
*         AMI   - Alternate Mark Inversion
*         B8ZS  - Binary Eight Zero Substitution
*
* Outputs:
*     T1E1 framer hardware line encoding is configured.
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetLineCoding(CT_FAC_LineCode theLineCode)
{
    itsLineCode = theLineCode;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetFramingType() class method
*
* Description:
*     Used to configure the Framing Format for the T1/E1 framer hardware.
*
* Inputs:
*     FramingType
*
* Outputs:
*     Update itsFramingType
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetFramingType(CT_FAC_FrameFormat theFramingType)
{
	itsFramingType = theFramingType;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetTimingSource() class method
*
* Description:
*     Used to configure the source of the timing for the hdp device
*
* Inputs:
*     Shelf and Slot Id
*
* Outputs:
*     Update itsTimingSourceShelf
*            itsTimingSourceSlot
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetTimingSource(CT_ShelfId theShelf, CT_SlotId theSlot)
{
	itsTimingSourceShelf = theShelf;
	itsTimingSourceSlot  = theSlot;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetSSMSaBit() class method
*
* Description:
*     Used to configure the E1 Sa bit used for SSM for the hdp device
*
* Inputs:
*     SaBit
*
* Outputs:
*     Update itsSsmSaBit
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetSSMSaBit(CT_FAC_SaBit theSaBit)
{
    itsSsmSaBit = theSaBit;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetLineCoding() class method
*
* Description:
*     Used to read back the SetLineCode() setting.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsLineCode
*
*************************************END***************************************
*/
CT_FAC_LineCode TSPII_T1E1If::GetLineCoding(void)
{
	return itsLineCode;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetFramingType() class method
*
* Description:
*     Used to read back the SetFramingType() setting.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsFramingType
*
*************************************END***************************************
*/
CT_FAC_FrameFormat TSPII_T1E1If::GetFramingType(void)
{
	return itsFramingType;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetTimingSource() class method
*
* Description:
*     Used to retrieve the input source timing configuration from the hdp device
*
* Inputs:
*     None
*
* Outputs:
*     Update itsTimingSourceShelf
*            itsTimingSourceSlot
*
* Returns:
*     void
*
*************************************END***************************************
*/
bool TSPII_T1E1If::GetTimingSource(CT_ShelfId& theShelf, CT_SlotId& theSlot) const
{
	theShelf = itsTimingSourceShelf;
	theSlot  = itsTimingSourceSlot;
	return true;
}
/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetSSMSaBit() class method
*
* Description:
*     Used to read back the E1 Sa bit used for SSM for the hdp device
*
* Inputs:
*     SaBit
*
* Outputs:
*     Update itsSsmSaBit
*
* Returns:
*     void
*
*************************************END***************************************
*/
CT_FAC_SaBit TSPII_T1E1If::GetSSMSaBit(void)
{
    return itsSsmSaBit;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetRxSsm() class method
*
* Description:
*     Used to read the current Sync Status Message being received from the 
*     T1/E1 facility.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsSsmCode
*
*************************************END***************************************
*/
CT_FAC_RxSsm TSPII_T1E1If::GetRxSsm(void)
{
	return itsSsmCode;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetAis() class method
*
* Description:
*     Used to read the current AIS (Alarm Indication Signal) defect count.
*     Odd value  = Clear
*     Even value = Active 
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsAisDefect
*
*************************************END***************************************
*/
uint32 TSPII_T1E1If::GetAis(void)
{
    return itsAisDefect;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetLof() class method
*
* Description:
*     Used to read the current LOF (Loss Of Frame) defect count.  
*     Odd value  = Clear
*     Even value = Active
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsLofDefect
*
*************************************END***************************************
*/
uint32 TSPII_T1E1If::GetLof(void)
{
    return itsLofDefect;    
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetLos() class method
*
* Description:
*     Used to read the current LOS (Loss Of Signal) defect count.  
*     Odd value  = Clear
*     Even value = Active
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsLosDefect
*
*************************************END***************************************
*/
uint32 TSPII_T1E1If::GetLos(void)
{    
    return itsLosDefect;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetOffFreq() class method
*
* Description:
*     Used to read the current Off Frequency defect count.  
*     Odd value  = Clear
*     Even value = Active
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     itsLosDefect
*
*************************************END***************************************
*/
uint32 TSPII_T1E1If::GetOffFreq(void)
{    
    return itsOffFreqDefect;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetClkOutEnable() class method
*
* Description:
*     Used to configure myClkOutEnableList[] 
*
* Inputs:
*
* Outputs:
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetClkOutEnable(const vector<bool>& theClkOutEnableList)
{      
    for (uint16 i = 0; i < itsClkOutSize; i++ ) 
    {
        SetClkOutput(i, theClkOutEnableList[i]);
    }
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetClkOutput() class method
*
* Description:
*     Used to configure a single clock output
*
* Inputs:
*
* Outputs:
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetClkOutput(uint16 theSlotNum, bool theClkOutEnable)
{
    if (theSlotNum < itsClkOutSize)
    {
        myClkOutEnableList[theSlotNum] = theClkOutEnable;
    }
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetClkOutEnable() class method
*
* Description:
*     Used to read back the myClkOutEnableList setting for a single slot.
*
* Inputs:
*     None
*
* Outputs:
*
* Returns:
*     slot enable status
*
*************************************END***************************************
*/
bool TSPII_T1E1If::GetClkOutEnable(uint16 theSlotNum)
{
    bool status = false;

    if (theSlotNum < itsClkOutSize)
    {
        status = myClkOutEnableList[theSlotNum];
    }

	return status;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::SetClkDisqualifyRef() class method
*
* Description:
*     Used to configure itsClkRefDisqualified 
*
* Inputs: theClkRefDisqualified = true = reference is not available
*
* Outputs:
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::SetClkDisqualifyRef(bool theClkRefDisqualified)
{
    itsClkRefDisqualified = !theClkRefDisqualified; 
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::GetClkDisqualifyRef() class method
*
* Description:
*     Used to read back the itsClkRefDisqualified setting.
*
* Inputs:
*     None
*
* Outputs:
*
* Returns:
*     itsClkRefDisqualified - reference status
*
*************************************END***************************************
*/
bool TSPII_T1E1If::GetClkDisqualifyRef(void)
{
	return itsClkRefDisqualified;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::WriteObjectBinary() method
*
* Description:
*     Provides the specialized binary based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
* 
*
* Returns:

*
*************************************END***************************************
*/
FC_Stream & TSPII_T1E1If::WriteObjectBinary(FC_Stream & theStream)
{
    // Update Gets
    UpdateValues();
    RefreshGet();

    int aSsmCode = itsSsmCode;
    int aLineCode = itsLineCode;
    int aFramingType = itsFramingType;
    int aSsmSaBit = itsSsmSaBit;

    // T1 monitor attributes
    theStream << itsLofDefect;
    theStream << itsLosDefect;
    theStream << itsAisDefect;
	theStream << itsOffFreqDefect;
    theStream << aSsmCode;

    // T1 configuration attributes
    theStream << aLineCode;       
    theStream << aFramingType; 
    theStream << itsTimingSourceShelf; 
    theStream << itsTimingSourceSlot;
    theStream << aSsmSaBit; 

    // clock control attributes
    for (uint16 i=0; i < itsClkOutSize; i++) 
    {
        theStream << myClkOutEnableList[i];
    }

    theStream << itsClkRefDisqualified;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::ReadObjectBinary() method
*
* Description:
*     Provides the specialized binary based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
* 
*     None
* Returns:
*
*
*************************************END***************************************
*/
FC_Stream & TSPII_T1E1If::ReadObjectBinary(FC_Stream & theStream)
{
    int aSsmCode;
    int aLineCode;
    int aFramingType;
    int aSsmSaBit;

    // T1 monitor attributes
    theStream >> itsLofDefect;
    theStream >> itsLosDefect;
    theStream >> itsAisDefect;
	theStream >> itsOffFreqDefect;
    theStream >> aSsmCode;

    // T1 configuration attributes
    theStream >> aLineCode;       
    theStream >> aFramingType;
    theStream >> itsTimingSourceShelf;
    theStream >> itsTimingSourceSlot;
    theStream >> aSsmSaBit; 

    // clock control attributes

    for (uint16 i=0; i < itsClkOutSize; i++) 
    {
        bool aClkOutEnabled = myClkOutEnableList[i];
        theStream >> aClkOutEnabled;
    }

    theStream >> itsClkRefDisqualified;

    itsSsmCode = (CT_FAC_RxSsm) aSsmCode;
    itsLineCode = (CT_FAC_LineCode) aLineCode;
    itsFramingType = (CT_FAC_FrameFormat) aFramingType;
    itsSsmSaBit = (CT_FAC_SaBit) aSsmSaBit;

    // Update Sets
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1If::WriteObject() method
*
* Description:
*     Provides the specialized text based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
* 
*     None
* Returns:

*
*************************************END***************************************
*/
ostream & TSPII_T1E1If::WriteObject(ostream & theStream)
{
    // Update 
    UpdateValues();
    RefreshGet();

    int aSsmCode = itsSsmCode;
    int aLineCode = itsLineCode;
    int aFramingType = itsFramingType;
    int aSsmSaBit = itsSsmSaBit;

    // T1 monitor attributes
    theStream << FC_InsertVar(itsLofDefect);
    theStream << FC_InsertVar(itsLosDefect);
    theStream << FC_InsertVar(itsAisDefect);
	theStream << FC_InsertVar(itsOffFreqDefect);
    theStream << FC_InsertVar(aSsmCode);

    // T1 configuration attributes
    theStream << FC_InsertVar(aLineCode);       
    theStream << FC_InsertVar(aFramingType);
    theStream << FC_InsertVar(itsTimingSourceShelf);
    theStream << FC_InsertVar(itsTimingSourceSlot);
    theStream << FC_InsertVar(aSsmSaBit);

    // clock control attributes
    for (uint16 i=0; i < itsClkOutSize; i++) 
    {
        bool aClkOutEnabled = myClkOutEnableList[i];
        theStream << FC_InsertVar(aClkOutEnabled);
    }

    theStream << FC_InsertVar(itsClkRefDisqualified);

    return TSPII_BaseIf::WriteObject(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::ReadObject() method
*
* Description:
*     Provides the specialized text based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:

*
*************************************END***************************************
*/
istream & TSPII_T1E1If::ReadObject(istream & theStream)
{
    int aSsmCode;
    int aLineCode;
    int aFramingType;
    int aSsmSaBit;

    // T1 monitor attributes
    theStream >> FC_ExtractVar(itsLofDefect);
    theStream >> FC_ExtractVar(itsLosDefect);
    theStream >> FC_ExtractVar(itsAisDefect);
	theStream >> FC_ExtractVar(itsOffFreqDefect);
    theStream >> FC_ExtractVar(aSsmCode);

    // T1 configuration attributes
    theStream >> FC_ExtractVar(aLineCode);       
    theStream >> FC_ExtractVar(aFramingType);
    theStream >> FC_ExtractVar(itsTimingSourceShelf);
    theStream >> FC_ExtractVar(itsTimingSourceSlot);
    theStream >> FC_ExtractVar(aSsmSaBit);

    // clock control attributes 
    for (uint16 i=0; i < itsClkOutSize; i++) 
    {
        bool aClkOutEnabled = myClkOutEnableList[i];
        theStream >> FC_ExtractVar(aClkOutEnabled);
    }

    theStream >> FC_ExtractVar(itsClkRefDisqualified);

    itsSsmCode = (CT_FAC_RxSsm) aSsmCode;
    itsLineCode = (CT_FAC_LineCode) aLineCode;
    itsFramingType = (CT_FAC_FrameFormat) aFramingType;
    itsSsmSaBit = (CT_FAC_SaBit) aSsmSaBit;

    // Update Sets
    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::Display() class method
*
* Description:
*     The test menu to display the E1T1 entity attributes 
*
* Inputs:
*     None
*
* Outputs:
*     None
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_T1E1If::Display(FC_Stream & theStream)
{ 
    // Update
    UpdateValues(); 
    RefreshGet();

    theStream << "  T1E1 Configuration/Monitoring\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Line Code             = " << DISPLAY_LINECODE(itsLineCode)       << "\n";
    theStream << "      Framing Type          = " << display_FRAMEFORMAT(itsFramingType) << "\n";
    theStream << "      Timing Source Shelf   = " << itsTimingSourceShelf << "\n";
    int theTimingSourceSlot = itsTimingSourceSlot;
    theStream << "      Timing Source Slot    = " << theTimingSourceSlot << "\n";
    theStream << "      SSM Sa Bit (E1 only)  = " << display_SABIT(itsSsmSaBit) << "\n";
        
    if (itsClkRefDisqualified)
    {
        theStream << "      Reference Available   = AVAILABLE\n"; 
    }
    else
    {
        theStream << "      Reference Available   = NOT AVAILABLE\n"; 
    }

    for (uint16 i=0; i < itsClkOutSize; i++) 
    {
        // vertically line up "=" signs

        if (i == 0)
        {
            theStream << "      Clock Enable  Slot  " << (i + 1) << " = " << DISPLAY_BOOL(myClkOutEnableList[i]) << "\n";
        }
        else if ((i > 0) && (i < 9))
        {
            theStream << "                    Slot  " << (i + 1) << " = " << DISPLAY_BOOL(myClkOutEnableList[i]) << "\n";
        }
        else
        {
            theStream << "                    Slot " << (i + 1) << " = " << DISPLAY_BOOL(myClkOutEnableList[i]) << "\n";
        }
    }

    theStream << "    MONITORING\n";
    theStream << "      AIS                   = " << TEXT_DEFECT(itsAisDefect)    << "\n";
    theStream << "      LOF                   = " << TEXT_DEFECT(itsLofDefect)    << "\n";
    theStream << "      LOS                   = " << TEXT_DEFECT(itsLosDefect)    << "\n";
	theStream << "      Off Freq              = " << TEXT_DEFECT(itsOffFreqDefect)    << "\n";
    theStream << "      Sync Status Message   = " << display_RXSSM(itsSsmCode) << endl;

    TSPII_BaseIf::Display(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::Set() class method
*
* Description:
*     Used to modify the configuration attributes via the test menu.
*
* Inputs:
*     Arguments for the configuration attributes
*
* Outputs:
*     Configuration changes
* Returns:
*     True/False
*
*************************************END***************************************
*/
bool TSPII_T1E1If::Set(int argc, char ** argv)
{
	bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "framingtype") == 0)
    {
        printUsage = true;
        for ( int i = 0; i < CT_FrameFormat_ALL; i++ )  
        {
            if (strcmp(argv[1], display_FRAMEFORMAT(i)) == 0)
            {
                SetFramingType((CT_FAC_FrameFormat)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "linecode") == 0)
    {
        printUsage = true;
        for (int i = 0; i < CT_LineCode_ALL; i++) 
        {
            if (strcmp(argv[1], DISPLAY_LINECODE(i)) == 0)
            {
                SetLineCoding((CT_FAC_LineCode)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "sabit") == 0)
    {
        printUsage = true;
        for (int i = 0; i < (CT_SaBit_UNKNOWN+1); i++) 
        {
            if (strcmp(argv[1], display_SABIT(i)) == 0)
            {
                SetSSMSaBit((CT_FAC_SaBit)i);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 3 && strcmp(argv[0], "sourceshelfslot") == 0)
    {       
        int shelf = atoi(argv[1]); 
        int slot  = atoi(argv[2]); 
		if ((shelf < 1 || shelf> 13 || slot <0 || slot > 19))
		{
			printUsage = true;
		}
		else
		{
			SetTimingSource((CT_ShelfId) shelf, (CT_SlotId) slot);
		}

    }
    else if ((argc == 2) && strcmp(argv[0], "refavailable") == 0)
    {
        if (strcmp(argv[1], "no") == 0)
        {
            SetClkDisqualifyRef(true);
        }
        else if (strcmp(argv[1], "yes") == 0)
        {
            SetClkDisqualifyRef(false);   
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "clockenable") == 0)
    {
        printUsage = true;
        unsigned int aClock = static_cast<unsigned int>(atoi(argv[1])); // Get the slot number - "1" Based
        if ((aClock > 0) && (aClock <= itsClkOutSize)) 
        {
            printUsage = false;
            if (strcmp(argv[2], "on") == 0)
            {
                SetClkOutput((aClock - 1), true);   // slotnum is "0" Based
                printUsage = false;     
            }
            else if (strcmp(argv[2], "off") == 0)
            {
                SetClkOutput((aClock - 1), false);  // slotnum is "0" Based
                printUsage = false;
            }
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }

	if (printUsage)
    {
        fc_cout << "    linecode        <AMI|B8ZS|HDB3>\n"
                   "    framingtype     <ESF|SF|NOCRC4|CRC4>\n"
                   "    sabit           <4|5|6|7|8|UNKNOWN>\n"
                   "    refavailable    <yes|no>\n" 
                   "    clockenable     <slotnum[1-" << itsClkOutSize << "]> <on|off>\n" 
				   "    sourceshelfslot <shelfNum[1-13]> <slotNum[0-19]>" << endl;

    }

    return printUsage;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_T1E1If::Simul() class method
*
* Description:
*     Used to modify the configuration attributes via the test menu.
*
* Inputs:
*     Arguments for the configuration attributes
*
* Outputs:
*     Configuration changes
* Returns:
*     True/False
*
*************************************END***************************************
*/
bool TSPII_T1E1If::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "ais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsAisDefect)) itsAisDefect++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
           if (TSPII_DEFECT(itsAisDefect)) itsAisDefect++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "lof") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLofDefect)) itsLofDefect++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLofDefect)) itsLofDefect++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "los") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLosDefect)) itsLosDefect++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLosDefect)) itsLosDefect++;
        }
        else
        {
            printUsage = true;
        }
    }
	else if ((argc == 2) && strcmp(argv[0], "freq") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsOffFreqDefect)) itsOffFreqDefect++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsOffFreqDefect)) itsOffFreqDefect++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (((argc == 2) && strcmp(argv[0], "ssm") == 0))
    {
        printUsage = true;
        for (int i = 0; i < CT_RxSsm_ALL; i++) 
        {
            if (strcmp(argv[1], display_RXSSM(i)) == 0)
            {
                itsSsmCode = ((CT_FAC_RxSsm)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "refavailable") == 0)
    {
        if (strcmp(argv[1], "no") == 0)
        {
            SetClkDisqualifyRef(true);
        }
        else if (strcmp(argv[1], "yes") == 0)
        {
            SetClkDisqualifyRef(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "clockenable") == 0)
    {
        printUsage = true;
        unsigned int aClock = static_cast<unsigned int>(atoi(argv[1])); // Get the slot number - "1" Based
        if ((aClock > 0) && (aClock <= itsClkOutSize)) 
        {
            printUsage = false;
            if (strcmp(argv[2], "on") == 0)
            {
                SetClkOutput((aClock - 1), true);  // slotnum is "0" Based
                printUsage = false;     
            }
            else if (strcmp(argv[2], "off") == 0)
            {
                SetClkOutput((aClock - 1), false); // slotnum is "0" Based
                printUsage = false;               
            }
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    ais             <on|off>\n"
                   "    lof             <on|off>\n"
                   "    los             <on|off>\n"
				   "    freq            <on|off>\n"
                   "    ssm             <DUS|PNO|PRS|SMC|ST2|ST3|ST3E|ST4|STU|TNC>\n" 
                   "    refavailable    <yes|no>\n" 
                   "    clockenable     <slotnum[1-" << itsClkOutSize << "]> <on|off>\n" << endl;
    }

    return printUsage;
}
    


///////////////////////////////////////////////////////////////////////////////
void TSPII_T1E1If::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
