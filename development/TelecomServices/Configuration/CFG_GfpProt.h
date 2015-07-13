//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_GFPPROT_H
#define CFG_GFPPROT_H

#include "gdef.h"
#include "Blackboard/FC_BbObject.h"
#include "BaseClass/FC_TextStream.h"
#include "CFG_Object.h"
#include <CommonTypes/CT_FacilityIds.h>

//This object contains all the protection configuration for 
//GFP layer.
class CFG_GfpProt : public CFG_Object
{
public:

	//Constructor.
    CFG_GfpProt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_GfpProt(void);

	//This method sets the Force Link Fail TX (CR0) Offline.
    void SetForceLinkFailTx(bool theForceLinkFailTx);

	//This method retrieves the Force Link Fail TX (CR0)value.
    bool GetForceLinkFailTx(void);

	//This method resets all attributes to their default 
	//value.
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization text mode: This function allows writing 
	//object content to the output stream for debugging with 
	//the console.
    virtual ostream& WriteObject( ostream& theStream );

	//Serialization text mode: This function allows reading 
	//object content from the input stream for debugging with 
	//the console.
    virtual istream& ReadObject( istream& theStream );

	//Serialization binary mode: This function allows writing 
	//object content to the output stream for blackboard 
	//transfer.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

	//Serialization binary mode: This function allows reading 
	//object content from the input stream for blackboard 
	//transfer.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	//The Force Link Fail TX (CR0) configured.
    bool myForceLinkFailTx;

	//The object has valid states 
    bool itsReady;

};

#endif /* CFG_MSPROT_H */