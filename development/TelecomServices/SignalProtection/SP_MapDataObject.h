#ifndef SP_MAPDATAOBJECT_H
#define SP_MAPDATAOBJECT_H
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   
TARGET:          
AUTHOR:      Feb, 2005 - Anoop Mathew
DESCRIPTION: signal protection object used to store generic data.
-----------------------------------------------------------------------------*/ 
#include <Blackboard/FC_BbObject.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <map>
#include <vector>

using namespace std;

typedef map< uint32, bool, greater<uint32> > SP_Map;

class SP_MapDataObject : public FC_BbObject
{
public:
    /** Default constructor.*/
    SP_MapDataObject(void);
    virtual ~SP_MapDataObject();
//-----------------------------------------------------------------------------

    
    //Add Set and Get methods here
    bool Set(uint32 theKey);
    bool IsSet(uint32 theKey);
    bool Clear(uint32 theKey);
    void GetKeys(vector<uint32>* theKeys);
    void GetValues(vector<uint32>* theValues);
//-----------------------------------------------------------------------------
    virtual ostream& WriteObject( ostream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------

private:
    //Add class data members here
    SP_Map myMap;
};

#endif //SP_MAPDATAOBJECT_H
