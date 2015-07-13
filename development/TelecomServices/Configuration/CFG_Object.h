// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef CFG_OBJECT_H
#define CFG_OBJECT_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <Shell/FC_CmdProcessor.h>
#include <gdef.h>

//This class is a blackboard base object for signal 
//configuration.
//##ModelId=3C0FE6300029
class CFG_Object : public TEL_BbObjectBase
{

public:

	//Constructor.
	//##ModelId=3C0FE6300033
    CFG_Object(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C0FE6300035
    virtual ~CFG_Object();

	//##ModelId=3C0FE6300040
    virtual void Reset() { }

	//##ModelId=3C0FE6300048
    uint32 GetIndex() const 
    {
        return myIndex;
    }

	//##ModelId=3C716FF3019A
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);
    virtual FC_CmdProcessor::STATUS Debug(int argc, char **argv);

    virtual bool IsValidated() const;
    void Validate();
    void Invalidate();

protected:
	//##ModelId=3C3B463A0148
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C3B463A01A2
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C3B463A01F2
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C3B463A0242
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	//##ModelId=3C0FE79701C0
    uint32 myIndex;
    bool isValidated;
};

#endif /* CFG_OBJECT_H */

