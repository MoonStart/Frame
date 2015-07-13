/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_HOPAUTOMATICOBJECT_H
#define CFG_HOPAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_HopAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_HopAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_HopAutomatic(void);


    //This method will set the Force Internal Ais atribute
    bool SetForceInternalAIS(bool theForceLCK);

    //This method will return the value of the Force Internal Ais atribute
    bool GetForceInternalAIS() const;


    //This method resets all attributes to their default value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // Set to true to Disqulaify Reference
    bool myForceInternalAIS;
};

#endif /* CFG_HOPAUTOMATICOBJECT_H */

