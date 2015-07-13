/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_DDLTOBJECT_H
#define CFG_DDLTOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <vector>

#include "CFG_Object.h"


//This object contains all the DDLT configuration.
class CFG_Ddlt
: public CFG_Object
{

public:

	//Constructor.
    CFG_Ddlt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Ddlt(void);

    //This method is used to indicate that the Ddlt Transfer facility is configured (for LED).
    void SetDdltEnable(bool theDdltEnable);

    //This method returns the state of the Ddlt Transfer facility.
    bool GetDdltEnable() const;


	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);


protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:
    // Set to true if the DDLT facility is enabled
    bool myDdltEnable;

};

#endif /* CFG_DDLTOBJECT_H */

