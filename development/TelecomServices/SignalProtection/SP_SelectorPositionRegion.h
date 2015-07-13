//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_SELECTORPOSITIONREGION_H
#define SP_SELECTORPOSITIONREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

extern const FC_BbKey SP_SELECTORPOSREGIONKEY;
extern const FC_BbKey SP_ALTSELECTORPOSREGIONKEY;


//This class hold the position of the selector
class SP_SelectorPosition :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_SelectorPosition();

    //Virtual destructor.
    virtual ~SP_SelectorPosition(void);

	//Returns true if the current position does not match new position
	bool SetSelectorPostion(CT_SP_Protection theNewSelPosition);

	CT_SP_Protection GetSelectorPosition() {return mySelectorPosition;};

	//Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

protected:

private:

    //Selector position
    CT_SP_Protection mySelectorPosition;
};

class SP_SelectorPositionRegion: public TEL_BbRegionBaseImp<SP_SelectorPosition>
{
public:
	// Default class constructor
    SP_SelectorPositionRegion();

    // Class constructor
    SP_SelectorPositionRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_SelectorPositionRegion();

    /** The default convert method de-serializes the region. */
    virtual void Conversion(FC_Version& theRxVersion, FC_Stream& theStream);
};

#endif /* SP_SELECTORPOSITIONREGION_H */
