/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_T1E1AUTOMATICOBJECT_H
#define CFG_T1E1AUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_T1E1Automatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_T1E1Automatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_T1E1Automatic(void);

    //This method sets the current state of Disqulaify Reference.
    bool SetDisqualifyRef(bool theDisqualifyRef);

    //This method returns the current state of Disqulaify Reference.
    bool GetDisqualifyRef() const;


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
    bool myDisqualifyRef;
};

#endif /* CFG_T1E1AUTOMATICOBJECT_H */

