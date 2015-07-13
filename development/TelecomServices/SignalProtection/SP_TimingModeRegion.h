//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_TIMINGMODEREGION_H
#define SP_TIMINGMODEREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>


//This class hold the timing state
class SP_TimingModeObject :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_TimingModeObject();

    //Virtual destructor.
    virtual ~SP_TimingModeObject(void);

    // Set timing mode
    bool SetTimingMode(CT_TEL_ClkMode theTimingMode);
	// Get timing mode
	CT_TEL_ClkMode GetTimingMode();
    // Set selected ref SSM
    bool SetSelectedRefSsm(CT_FAC_RxSsm theSelectedRefSsm);
	// Get selected ref SSM
    CT_FAC_RxSsm GetSelectedRefSsm();
	// Set the current selected timing reference
	bool SetTimingReference(CT_TEL_ClkSelRef theTimingReference);
	// Get the current selected timing reference
	CT_TEL_ClkSelRef GetTimingReference();

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

	//Timing Mode
    CT_TEL_ClkMode myTimingMode;
	//Selected ref SSM
    CT_FAC_RxSsm mySelectedRefSsm;
	//Selected timing reference
	CT_TEL_ClkSelRef myTimingReference;
};

class SP_TimingModeRegion: public TEL_BbRegionBaseImp<SP_TimingModeObject>
{
public:
	// Default class constructor
    SP_TimingModeRegion();

    // Class constructor
    SP_TimingModeRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_TimingModeRegion();
};

#endif /* SP_TIMINGMODEREGION_H */
