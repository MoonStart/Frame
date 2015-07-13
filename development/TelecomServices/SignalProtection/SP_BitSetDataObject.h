#ifndef SP_BITSETDATAOBJECT_H
#define SP_BITSETDATAOBJECT_H
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   Equipment Redundancy Support
TARGET:          
AUTHOR:      Feb, 2005 - Anoop Mathew
DESCRIPTION: signal protection object used to store generic data.
-----------------------------------------------------------------------------*/ 
#include <Blackboard/FC_BbObject.h>
#include <CommonTypes/CT_SignalProtection.h>

using namespace std;

class SP_BitSetDataObject : public FC_BbObject
{
public:
    /** Default constructor.*/
    SP_BitSetDataObject(void);
    virtual ~SP_BitSetDataObject();
//-----------------------------------------------------------------------------

    
    //Add Set and Get methods here
    bool Set(uint32 theMask);
    bool IsSet(uint32 theMask);
    bool Clear(uint32 theMask);
//-----------------------------------------------------------------------------
    virtual ostream& WriteObject( ostream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------

private:
    //Add class data members here
    uint32 myBitSet;
};

#endif //SP_BITSETDATAOBJECT_H
