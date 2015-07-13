//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_SELECTORSTATEREGION_H
#define SP_SELECTORSTATEREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

extern const FC_BbKey SP_SELECTORSTATEREGION_KEY;


//This class hold the position of the selector
class SP_SelectorState :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_SelectorState();

    //Virtual destructor.
    virtual ~SP_SelectorState(void);

	//Returns true if the current state doesnt match new state
	bool SetSelectorState(CT_SP_Protection theNewSelState);

	CT_SP_Protection GetSelectorState() {return mySelectorState;};

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

    //Selector state
    CT_SP_Protection mySelectorState;
};

class SP_SelectorStateRegion: public TEL_BbRegionBaseImp<SP_SelectorState>
{
public:
	// Default class constructor
    SP_SelectorStateRegion();

    // Class constructor
    SP_SelectorStateRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_SelectorStateRegion();

};

#endif /* SP_SELECTORSTATEREGION_H */
