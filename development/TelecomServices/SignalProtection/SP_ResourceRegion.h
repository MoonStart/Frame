//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_RESOURCEREGION_H
#define SP_RESOURCEREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

extern const FC_BbKey SP_RESOURCEREGION_A_KEY;
extern const FC_BbKey SP_RESOURCEREGION_B_KEY;



//This class hold the position of the selector
class SP_ResourceObject :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_ResourceObject();

    //Virtual destructor.
    virtual ~SP_ResourceObject(void);

    // Set resource and facility id
    void SetResourceList(CT_FAC_StsMap& theResourceList, CT_IntfId thePortId);
	// Set enable/disable state
	void SetEnabledState(bool theState);

    // Get resoure list
    CT_FAC_StsMap& GetResourceList();
	// Get the facility id
	CT_IntfId GetResourceFacility();
	// Get Is Enabled
	bool GetIsEnabled();

	void Reset();

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

    //resource identifier
	uint8 myResourceId;
    // List of resources
    CT_FAC_StsMap myResourceList;
	//Enabled?
	bool myIsEnable;
};

class SP_ResourceRegion: public TEL_BbRegionBaseImp<SP_ResourceObject>
{
public:
	// Default class constructor
    SP_ResourceRegion();

    // Class constructor
    SP_ResourceRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_ResourceRegion();
};

#endif /* SP_RESOURCEREGION_H */
