// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPCONFIG_38DB80630106_INCLUDED
#define _INC_SP_PROTECTIONGROUPCONFIG_38DB80630106_INCLUDED

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_Definitions.h"
#include <CommonTypes/CT_Telecom.h>

//This is the base class of the protection group 
//configuration. It contains the properties common to both 
//types of protection. It inherits for TEL_BbObject, which is 
//a FC_BbObject.
//##ModelId=38DB80630106
class SP_ProtectionGroupConfig 
: public TEL_BbObjectBase
{
public:
	//Sets the standard to use (SONET or SDH).
	//##ModelId=3B8BC9CE003F
    void SetFacilityStandard(CT_TEL_FacilityStandard theStandard);
	//Returns the current standard in use (SONET or SDH).
	//##ModelId=3B8BC9CD03CD
    CT_TEL_FacilityStandard GetFacilityStandard() const;
 
	//Returns the state of the protection group: locked, 
	//normal or shutting down.
	//##ModelId=390731920062
	CT_SP_GroupState GetState() const;

	//Sets the state of the protection group: locked, normal 
	//or shutting down.
	//##ModelId=390731920166
	void SetState(CT_SP_GroupState value);

	//This method returns true if the protection group is 
	//currently in use.
	//##ModelId=38DF6A4B0037
	bool InUse() const;

	//This method allows setting the usage status of the 
	//protection group. True is in use.
	//##ModelId=38DF6AB10160
	void SetUsage(bool theStatus);

	//This method returns true if the switching is revertive.
	//##ModelId=38DF9F4D02A7
	bool GetRevertiveMode() const;

	//This method allows specifying if switching is revertive 
	//or not.
	//##ModelId=38DF9BB10059
	void SetRevertiveMode(bool theMode);

	//This method allows setting the wait to restore period.
	//##ModelId=38DF9AA201C2
	void SetWTR(uint16 thePeriod);

	//This method returns the wait-to-restore period in 
	//seconds.
	//##ModelId=38DF9F7401C7
	uint16 GetWTR() const;

	//This method allows setting the group id
	void SetGroupID(uint8 theGroupID);

	//This method allows retrieval of the group id
	uint8 GetGroupID() const;

	//Class destructor.
	//##ModelId=38E201EF01AC
	virtual ~SP_ProtectionGroupConfig();

	//Constructor.
	//##ModelId=3911AE770354
	SP_ProtectionGroupConfig();
	//Copy constructor.
	//##ModelId=3B8BC9CD02FB
	SP_ProtectionGroupConfig(const SP_ProtectionGroupConfig& theConfig);

	//This method reset all the protection values to default 
	//one. This method is an abstract method.
	//##ModelId=38F37B4E012D
	virtual void Reset() = 0;

	//Assignment operator.
	//##ModelId=3937FD33026C
    virtual SP_ProtectionGroupConfig& operator=(const SP_ProtectionGroupConfig& theConfig);
	//Comparison operator.
	//##ModelId=3B8BC9CD01CE
    virtual bool operator==(const SP_ProtectionGroupConfig& theRhs) const ;
	//Unequal operator.
	//##ModelId=3B8BC9CD00E8
    virtual bool operator!=(const SP_ProtectionGroupConfig& theRhs) const {return !(*this==theRhs);}
	//Return true if the group ID, the rate or the standard 
	//are different than the given one.
	//##ModelId=3B8BC9CD000C
    virtual bool IsGroupDifferent(const SP_ProtectionGroupConfig& theRhs) const;

protected:

	//Writes the attributes of the configuration to a stream.
	//##ModelId=3932D1D601E9
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the configuration from a stream.
	//##ModelId=3932D1D60027
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the configuration to a binary 
	//stream.
	//##ModelId=39ACEFAD01E0
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the configuration from binary  
	//stream.
	//##ModelId=39ACEFAC03E7
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//State of the protection group: locked, normal or 
	//shutting down.
	//##ModelId=39072F29028B
	CT_SP_GroupState myState;

	//True if the protection group is in use.
	//##ModelId=38DF6A68010B
	bool myUseStatus;

	//The wait-to-restore period in number of seconds.
	//##ModelId=38DF9B7802F6
	uint16 myWTR;

	//True if switching is revertive.
	//##ModelId=38DF9BF30177
	bool myRevertiveMode;

	//Stanrd in use: SONET or SDH. This might affect specific 
	//behavior depending on requirement (e .g. protocol 
	//signaling).
	//##ModelId=3B8BC9CC0137
    CT_TEL_FacilityStandard myStandard;

	//The group id
	uint8 myGroupID;
};


//##ModelId=3B8BC9CD03CD
inline CT_TEL_FacilityStandard SP_ProtectionGroupConfig::GetFacilityStandard() const
{
    return myStandard;
}

#endif /* _INC_SP_PROTECTIONGROUPCONFIG_38DB80630106_INCLUDED */

