// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TxOptStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>


//##ModelId=3C0FE66F01A6
MON_TxOptStatus::MON_TxOptStatus(uint32 theIndex):
    MON_Status(theIndex),
	myLaserBiasCurrent(0),
	myLaserTemp(0),
	myOutputPower(0),
    myLaserState(false),
    myLowTxPowerDefect(false)
{
}

//##ModelId=3C0FE66F01B0
MON_TxOptStatus::~MON_TxOptStatus(void )
{
}

void MON_TxOptStatus::GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const
{
    switch (theStatus)
    {
    case CT_TEL_OTU_LASER_BIAS_CURRENT_STATUS:
        *theLevel = GetLaserBiasCurrent();
        break;
    case CT_TEL_OTU_LASER_TEMPERATURE_STATUS:
        *theLevel = GetLaserTemp();
        break;
    case CT_TEL_OTU_OUTPUT_POWER_STATUS:
        *theLevel = GetOutputPower();
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TxOptStatus: unsupported status");
    }
}

bool MON_TxOptStatus::SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel)
{
    //Return true if changed
    bool hasChanged = false;

    switch (theStatus)
    {
    case CT_TEL_OTU_LASER_BIAS_CURRENT_STATUS:
        hasChanged = SetLaserBiasCurrent(theLevel);
        break;
    case CT_TEL_OTU_LASER_TEMPERATURE_STATUS:
        hasChanged = SetLaserTemp(theLevel);
        break;
    case CT_TEL_OTU_OUTPUT_POWER_STATUS:
        hasChanged = SetOutputPower(theLevel);
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TxOptStatus: unsupported status");
    }

    return hasChanged;
}

//##ModelId=3C0FE66F01BB
void MON_TxOptStatus::Reset()
{
    MON_Object::Reset();
	myLaserBiasCurrent=0;
	myLaserTemp=0;
	myOutputPower=0;
    myLaserState = false;
    myLowTxPowerDefect = false;
}

//##ModelId=3C162B6E0255
CT_TEL_mBm MON_TxOptStatus::GetOutputPower() const
{
    return myOutputPower;
}

//##ModelId=3C162B93003C
CT_TEL_Percent MON_TxOptStatus::GetLaserBiasCurrent() const
{
    return myLaserBiasCurrent; 
}

//##ModelId=3C162BB7035E
CT_TEL_milliCelcius MON_TxOptStatus::GetLaserTemp() const
{
    return myLaserTemp;
}

//##ModelId=3C162BE601CB
bool MON_TxOptStatus::SetOutputPower(CT_TEL_mBm thePower)
{
    bool hasChanged = false;

    if(thePower != myOutputPower)
    {
        myOutputPower = thePower;
        hasChanged = true;
    }
    return hasChanged;
}

//##ModelId=3C162BFD01C5
bool MON_TxOptStatus::SetLaserTemp(CT_TEL_milliCelcius theTemp)
{
    bool hasChanged = false;
    if(myLaserTemp != theTemp)
    {
        myLaserTemp = theTemp;
        hasChanged = true;
    }
    return hasChanged;
}
//##ModelId=3C162C140087
bool MON_TxOptStatus::SetLaserBiasCurrent(CT_TEL_Percent theLBC)
{
    bool hasChanged = false;
    if(myLaserBiasCurrent != theLBC)
    {
        myLaserBiasCurrent = theLBC;
        hasChanged = true;
    }
    return hasChanged;
}

//##ModelId=3C45A2960231
bool MON_TxOptStatus::SetLaserState(bool theState)
{
    bool hasChanged = false;
    if (myLaserState != theState)
    {
        myLaserState = theState;
        hasChanged = true;
    }
    return hasChanged;
}

//##ModelId=3C45A2960259
bool MON_TxOptStatus::GetLaserState() const
{
    return myLaserState;
}

bool MON_TxOptStatus::GetLowTxPowerDefect() const
{
    return myLowTxPowerDefect;
}

bool MON_TxOptStatus::SetLowTxPowerDefect(bool theState)
{
    bool hasChanged = false;
    if (myLowTxPowerDefect != theState)
    {
        myLowTxPowerDefect = theState;
        hasChanged = true;
    }
    return hasChanged;
}


//##ModelId=3C0FE66F01C4
ostream& MON_TxOptStatus::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
	theStream << FC_InsertVar(myLaserBiasCurrent);
	theStream << FC_InsertVar(myLaserTemp);
	theStream << FC_InsertVar(myOutputPower);
	theStream << FC_InsertVar(myLaserState);
	theStream << FC_InsertVar(myLowTxPowerDefect);
    return theStream;
}

//##ModelId=3C0FE66F01CE
istream& MON_TxOptStatus::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
	theStream >> FC_ExtractVar(myLaserBiasCurrent);
	theStream >> FC_ExtractVar(myLaserTemp);
	theStream >> FC_ExtractVar(myOutputPower);
	theStream >> FC_ExtractVar(myLaserState);
	theStream >> FC_ExtractVar(myLowTxPowerDefect);
    return theStream;
}

//##ModelId=3C0FE66F01D8
FC_Stream& MON_TxOptStatus::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
//	theStream << myLaserBiasCurrent;
//	theStream << myLaserTemp;
	theStream << myOutputPower;
	theStream << myLaserState;
//	theStream << myLowTxPowerDefect;
    return theStream;
}

//##ModelId=3C0FE66F01E2
FC_Stream& MON_TxOptStatus::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
//	theStream >> myLaserBiasCurrent;
//	theStream >> myLaserTemp;
	theStream >> myOutputPower;
	theStream >> myLaserState;
//	theStream >> myLowTxPowerDefect;
    return theStream;
}

//##ModelId=3C7170E8003E
void MON_TxOptStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "TX OPT  - Output Power  (dBm)               = " << DISPLAY_MBM(myOutputPower) << endl;
    theStream   << "TX OPT  - Relative Temperature (degC)       = " << DISPLAY_MCELCIUS(myLaserTemp) << endl;
    theStream   << "TX OPT  - Laser Bias Current. (%)           = " << myLaserBiasCurrent << endl;
    theStream   << "TX OPT  - Laser State                       = " << DISPLAY_BOOL(myLaserState) << endl;
    theStream   << "TX OPT  - Low Tx Power Defect               = " << DISPLAY_BOOL(myLowTxPowerDefect) << endl;
}

