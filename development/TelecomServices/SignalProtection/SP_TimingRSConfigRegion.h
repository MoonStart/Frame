//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_TIMINGRSCONFIGREGION_H
#define SP_TIMINGRSCONFIGREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SignalProtection.h>


//This class hold the timing redundancy support (RS) config object
class SP_TimingRSConfig :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_TimingRSConfig();

    //Virtual destructor.
    virtual ~SP_TimingRSConfig(void);

    // Set RS config
    bool SetRedundancyMode(CT_SP_RSMode theRedundancyMode);
	// Get RS config
	CT_SP_RSMode GetRedundancyMode();

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

	//Timing Mode
    CT_SP_RSMode myRedundancyMode;
};

class SP_TimingRSConfigRegion: public TEL_BbRegionBaseImp<SP_TimingRSConfig>
{
public:
	// Default class constructor
    SP_TimingRSConfigRegion();

    // Class constructor
    SP_TimingRSConfigRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_TimingRSConfigRegion();
};

#endif /* SP_TIMINGMODEREGION_H */
