//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_SSMREGION_H
#define SP_SSMREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>

extern const FC_BbKey SP_SSMCOLLECTIONREGIONKEY;
extern const FC_BbKey SP_SSMDISTRIBUTIONREGIONKEY;


//This class hold the position of the selector
class SP_SsmValue :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_SsmValue();

    //Virtual destructor.
    virtual ~SP_SsmValue(void);

	//Returns the SSM value associated with a given interface
	CT_FAC_RxSsm GetSsmValue(CT_SP_Protection theSide);

	bool SetSsmValue(CT_SP_Protection theSide, CT_Port& theInterface, CT_FAC_RxSsm theSsmVal, bool isValid);
	bool Reset(CT_SP_Protection theSide);
	bool IsSsmValid(CT_SP_Protection theSide);
	bool SetSelectedSide(CT_SP_Protection theSide);
	CT_SP_Protection GetSelectedSide();
	CT_SP_ProtectionPair<CT_Port> & GetInterfaces();
    CT_ShelfId GetSsmShelf(CT_SP_Protection theSide);
    CT_SlotId GetSsmSlot(CT_SP_Protection theSide);

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

    CT_SP_ProtectionPair<CT_FAC_RxSsm> mySsmVal;
    CT_SP_ProtectionPair<CT_Port> myInterface;
	CT_SP_ProtectionPair<bool> myDataValid;
	CT_SP_Protection mySelectedSide;
};

class SP_SsmRegion: public TEL_BbRegionBaseImp<SP_SsmValue>
{
public:
	// Default class constructor
    SP_SsmRegion();

    // Class constructor
    SP_SsmRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_SsmRegion();
};

#endif /* SP_SSMREGION_H */
