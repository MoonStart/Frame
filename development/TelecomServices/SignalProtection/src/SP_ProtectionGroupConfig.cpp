// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ProtectionGroupConfig.h"
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

//##ModelId=3911AE770354
SP_ProtectionGroupConfig::SP_ProtectionGroupConfig():
	myState(CT_SP_NORMAL_STATE),
	myUseStatus(false),
	myWTR(5*60),
	myRevertiveMode(false),
    myStandard(CT_TEL_SONET),
	myGroupID(0)
{}

//##ModelId=3B8BC9CD02FB
SP_ProtectionGroupConfig::SP_ProtectionGroupConfig(const SP_ProtectionGroupConfig& theConfig):
	myState(theConfig.myState),
	myUseStatus(theConfig.myUseStatus),
	myWTR(theConfig.myWTR),
	myRevertiveMode(theConfig.myRevertiveMode),
    myStandard(theConfig.myStandard),
	myGroupID(theConfig.myGroupID)
{}

void SP_ProtectionGroupConfig::SetFacilityStandard(CT_TEL_FacilityStandard theStandard)
{
    myStandard = theStandard;
}

//##ModelId=38DF6A4B0037
bool SP_ProtectionGroupConfig::InUse() const
{
    return myUseStatus;
}

//##ModelId=38DF6AB10160
void SP_ProtectionGroupConfig::SetUsage(bool theStatus)
{
    myUseStatus = theStatus;
}

//##ModelId=38DF9F4D02A7
bool SP_ProtectionGroupConfig::GetRevertiveMode() const
{
	return myRevertiveMode;
}

//##ModelId=38DF9BB10059
void SP_ProtectionGroupConfig::SetRevertiveMode(bool theMode)
{
	myRevertiveMode = theMode;
}

//##ModelId=38DF9AA201C2
void SP_ProtectionGroupConfig::SetWTR(uint16 thePeriod)
{
	myWTR = thePeriod;
}

//##ModelId=38DF9F7401C7
uint16 SP_ProtectionGroupConfig::GetWTR() const
{
    return myWTR;
}

//This method allows setting the group id
void SP_ProtectionGroupConfig::SetGroupID(uint8 theGroupID)
{
	myGroupID = theGroupID;
}

//This method allows retrieval of the group id
uint8 SP_ProtectionGroupConfig::GetGroupID() const
{
	return myGroupID;
}

//##ModelId=390731920062
CT_SP_GroupState SP_ProtectionGroupConfig::GetState() const
{
	return myState;
}


//##ModelId=38E201EF01AC
SP_ProtectionGroupConfig::~SP_ProtectionGroupConfig()
{
}


//##ModelId=390731920166
void SP_ProtectionGroupConfig::SetState(CT_SP_GroupState value)
{
	myState = value;
	return;
}

//##ModelId=3932D1D601E9
ostream& SP_ProtectionGroupConfig::WriteObject( ostream& theStream )
{
	theStream<<FC_InsertVar(myRevertiveMode);
	theStream<<FC_InsertVar(myState);
	theStream<<FC_InsertVar(myUseStatus);
	theStream<<FC_InsertVar(myWTR);
	
    uint8 aFacilityStandard(myStandard);
    theStream<<FC_InsertVar(aFacilityStandard);

	theStream<<FC_InsertVar(myGroupID);

    return theStream;
}

//##ModelId=3932D1D60027
istream& SP_ProtectionGroupConfig::ReadObject( istream& theStream )
{
	theStream>>FC_ExtractVar(myRevertiveMode);
	theStream>>FC_ExtractVar(myState);
	theStream>>FC_ExtractVar(myUseStatus);
	theStream>>FC_ExtractVar(myWTR);

    uint8 aFacilityStandard;
    theStream>>FC_ExtractVar(aFacilityStandard);
    myStandard = (CT_TEL_FacilityStandard)aFacilityStandard;

	theStream>>FC_ExtractVar(myGroupID);

    return theStream;
}

//##ModelId=39ACEFAD01E0
FC_Stream& SP_ProtectionGroupConfig::WriteObjectBinary( FC_Stream& theStream )
{
	theStream<<myRevertiveMode;
	theStream<<myState;
	theStream<<myUseStatus;
	theStream<<myWTR;

    uint8 aFacilityStandard(myStandard);
    theStream<<aFacilityStandard;

	theStream<<myGroupID;

    return theStream;
}

//##ModelId=39ACEFAC03E7
FC_Stream& SP_ProtectionGroupConfig::ReadObjectBinary( FC_Stream& theStream )
{
	theStream>>myRevertiveMode;
	theStream>>myState;
	theStream>>myUseStatus;
	theStream>>myWTR;

    uint8 aFacilityStandard;
    theStream>>aFacilityStandard;
    myStandard = (CT_TEL_FacilityStandard)aFacilityStandard;

    theStream>>myGroupID;

    return theStream;
}

//##ModelId=3937FD33026C
SP_ProtectionGroupConfig& SP_ProtectionGroupConfig::operator=(const SP_ProtectionGroupConfig& theConfig) 
{
    myRevertiveMode  = theConfig.myRevertiveMode;
    myState          = theConfig.myState;
    myUseStatus      = theConfig.myUseStatus;
    myWTR            = theConfig.myWTR;
    myStandard       = theConfig.myStandard;
	myGroupID        = theConfig.myGroupID;

    return (*this);
}

//##ModelId=3B8BC9CD01CE
bool SP_ProtectionGroupConfig::operator==(const SP_ProtectionGroupConfig& theRhs) const
{
    return (myRevertiveMode  == theRhs.myRevertiveMode  &&
            myState          == theRhs.myState          &&
            myUseStatus      == theRhs.myUseStatus      &&
            myWTR            == theRhs.myWTR            &&
			myGroupID        == theRhs.myGroupID        &&
            myStandard       == theRhs.myStandard    );
}

//##ModelId=3B8BC9CD000C
bool SP_ProtectionGroupConfig::IsGroupDifferent(const SP_ProtectionGroupConfig& theRhs) const
{
    return !(myStandard       == theRhs.myStandard);
}
