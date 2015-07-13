/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MACAUTOMATICOBJECT_H
#define CFG_MACAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the automatic configuration
//of one MAC interface.
class CFG_MacAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_MacAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_MacAutomatic(void);

	//This method sets/clears the Remote Fault forced.
	//bool SetRemoteFaultForced(bool theRemoteFaultForced);

	//This method retrieves the Remote Fault forced mode
	//bool GetRemoteFaultForced() const;

    // This method set/clear the Fefi mode
    //bool SetFefiEnabled(bool theFefiEnabled);

    //This method retrieves the FEFI mode
    //bool GetFefiEnabled() const;

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

    // Set to true to force Remote Fault (Link Fail).
    //bool myRemoteFaultForced;

    // set to indicate FEFI
    //bool myFefiEnabled;

};

#endif /* CFG_MACAUTOMATICOBJECT_H */

