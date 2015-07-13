/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_1NSelIf.cpp 
* Type:    C++ source
* Description:
*     Definition of the class TSPII_1NSelIf which models the simulation
*     1NSel Interface entity.        
*
*     
*************************************END***************************************
*/

#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_1NSelIf.h"
#include <string.h>

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf constructor
*
* Description:
*     TSPII_1NSelIfIf class constructor
*
* Inputs:
*     interpretAsWorkProtect - If true the selector is treated as a 2:1 Working/Protect
*         style unit - This is the way the OPSM got created originally and to maintain
*         back compatibility we left this in the base class even though it should not be here.
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_1NSelIf::TSPII_1NSelIf(bool theDefault, bool interpretAsWorkProtect) :
    TSPII_BaseIf(theDefault)
{
    itsInterpretAsWorkProtect = interpretAsWorkProtect;
    Reset();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf destructor
*
* Description:
*     TSPII_1NSelIf class destructor
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
TSPII_1NSelIf::~TSPII_1NSelIf()
{   
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::RefreshGet() class method
*
* Description:
*     Used to refresh the 1NSel entity attributes.
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
void TSPII_1NSelIf::RefreshGet()
{
    // Selector attribute
    itsSelected = GetSelector();
     
}


/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::RefreshSet() class method
*
* Description:
*     Used to refresh the 1NSel configuration
*
* Inputs:
*     None
*
* Outputs:
*    itsSelected is reconfigured
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_1NSelIf::RefreshSet()
{
    // Selected attribute
	SetSelector(itsSelected);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::Reset() class method
*
* Description:
*     Used to reset the 1NSel entity attributes to a default state.
*
* Inputs:
*     None
*
* Outputs:
*     Selector attribute zeroed
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_1NSelIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Reset Selector attribute
	itsSelected = 0;

}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::SetSelector() class method
*
* Description:
*     Used to configure itsSelected 
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
void TSPII_1NSelIf::SetSelector(uint16 itsInput)
{
    itsSelected = itsInput;
}


/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::GetSelector() class method
*
* Description:
*     Used to read back the itsSeleted setting.
*
* Inputs:
*     None
*
* Outputs:
*
* Returns:
*     itsistSelected
*
*************************************END***************************************
*/
uint16 TSPII_1NSelIf::GetSelector(void)
{
	return itsSelected;
}




/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::WriteObjectBinary() method
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
FC_Stream & TSPII_1NSelIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update Gets
    UpdateValues();
    RefreshGet();

    // Selector attributes
	theStream << itsSelected;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::ReadObjectBinary() method
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
FC_Stream & TSPII_1NSelIf::ReadObjectBinary(FC_Stream & theStream)
{
    // Selector attribute
    theStream >> itsSelected;
	
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
ostream & TSPII_1NSelIf::WriteObject(ostream & theStream)
{
    // Update 
    UpdateValues();
    RefreshGet();

    // Selector attributes
	theStream << FC_InsertVar(itsSelected);
    
    return TSPII_BaseIf::WriteObject(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::ReadObject() method
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
istream & TSPII_1NSelIf::ReadObject(istream & theStream)
{
    // Selector attribute
	theStream >> FC_ExtractVar(itsSelected);

    // Update Sets
    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::Display() class method
*
* Description:
*     The test menu to display the 1NSel Selector attribute
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
void TSPII_1NSelIf::Display(FC_Stream & theStream)
{ 
    // Update
    UpdateValues(); 
    RefreshGet();

    theStream << "  1NSel Configuration/Monitoring\n";
    theStream << "    CONFIGURATION\n";
    if(itsInterpretAsWorkProtect)
    {
        theStream << "      Selector              = " << DISPLAY_1NSEL_INPUTS(itsSelected);     
        if (itsSelected) 
        {
            theStream  << "rotect\n";
        }
        else
        {
            theStream  << "orking\n";
        }
    }
    else
    {
        theStream << "      Selector              = " << itsSelected << endl;     
    }
  
    TSPII_BaseIf::Display(theStream);
}

/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::Set() class method
*
* Description:
*     Used to modify the Selector attributes via the test menu.
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
bool TSPII_1NSelIf::Set(int argc, char ** argv)
{
	bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "selector") == 0)
    {
        if(itsInterpretAsWorkProtect)
        {
            // is it w(orking)
            if (strcmp(argv[1], DISPLAY_1NSEL_INPUTS(0)) == 0)
            {
                SetSelector((TSPII_1NSEL_Input)0);
                printUsage = false;

            } // or p(rotect)
            else if (strcmp(argv[1], DISPLAY_1NSEL_INPUTS(1)) == 0)
            {
                SetSelector((TSPII_1NSEL_Input)1);
                printUsage = false;
            }
            else
            {
                printUsage = true;
            }
        }
        else
        {
            SetSelector(atoi(argv[1]));
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }

	if (printUsage)
    {
        if(itsInterpretAsWorkProtect)
        {
            fc_cout << "    selector            <w(orking) | p(rotect)>\n" << endl;
        }
        else
        {
            fc_cout << "    selector            n\n" << endl;
        }
    }

    return printUsage;
}


/************************************BEGIN*************************************
*
* Function:    TSPII_1NSelIf::Simul() class method
*
* Description:
*     Dummy simul method
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
bool TSPII_1NSelIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    printUsage = TSPII_BaseIf::Simul(argc, argv);
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_1NSelIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
