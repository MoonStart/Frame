/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_GCCAUTOMATICOBJECT_H
#define CFG_GCCAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_GccAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_GccAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_GccAutomatic(void);

    //This method will set the Force Disbale Link atribute
    bool SetDisableLink(bool theDisableLink);

    //This method will return the value of the Force Disbale Link atribute
    bool GetDisableLink() const;

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

    // Set to true to Disable Link
    bool myDisableLink;
 
};

#endif /* CFG_GCCAUTOMATICOBJECT_H */

