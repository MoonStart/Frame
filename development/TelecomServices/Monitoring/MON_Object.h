// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OBJECT_H
#define MON_OBJECT_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_Telecom.h>
#include <Shell/FC_CmdProcessor.h>
#include "MON_Definitions.h"


class MON_Config;
//This is the base class for monitoring. It is a blackboard 
//object.
//##ModelId=3C0FE6700157
class MON_Object : public TEL_BbObjectBase
{

public:

	//Constructor.
	//##ModelId=3C0FE670016B
    MON_Object(uint32 theIndex);
    MON_Object(const MON_Object& theObject);
    bool operator==(const MON_Object& theObject) const;
    void operator=(const MON_Object& theObject);

	//Virtual destructor.
	//##ModelId=3C0FE670016D
    virtual ~MON_Object();

	//##ModelId=3C0FE6700177
    virtual void Reset();
	//##ModelId=3C7170F202EB
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);
    virtual FC_CmdProcessor::STATUS Debug(int argc, char **argv);


	//##ModelId=3C0FE6700180
    uint32 GetIndex() const
    {
        return myIndex;
    }

    virtual bool IsValidated() const;
    bool Validate();
    bool Invalidate();

protected:
	//##ModelId=3C0FE6700194
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C0FE670019E
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C0FE67001A8
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C0FE67001B3
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//##ModelId=3C0FE791024D
    uint32 myIndex;
    bool isValidated;
};

#endif /* MON_OBJECT_H */

