//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_CONFIG_H
#define MON_CONFIG_H

#include "MON_Object.h"
#include "MON_Definitions.h"

//This is the base class for configuration parameter of 
//signal monitoring. It is derived from a CFG_Object.
//##ModelId=3C0FE67001ED
class MON_Config: public MON_Object
{
public:

	//Constructor.
	//##ModelId=3C0FE67001F7
    MON_Config(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C0FE6700201
    virtual ~MON_Config();

    virtual void Reset();

protected:
	//##ModelId=3C0FE6700203
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C0FE670020C
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C0FE6700216
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C0FE670022A
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif /* MON_CONFIG_H */

