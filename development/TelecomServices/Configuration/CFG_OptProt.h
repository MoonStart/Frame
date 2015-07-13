//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_OPTPROT_H
#define CFG_OPTPROT_H

#include "gdef.h"
#include "Blackboard/FC_BbObject.h"
#include "BaseClass/FC_TextStream.h"
#include "CFG_Object.h"
#include <CommonTypes/CT_FacilityIds.h>

//This object contains all the protection configuration for 
//OPT layer.
class CFG_OptProt : public CFG_Object
{
public:

	//Constructor.
    CFG_OptProt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OptProt(void);

    //This method sets the current state of laser.
    void SetForceLaserShutdown(bool theLaserShutdown);

    //This method returns the current state of laser.
    bool GetForceLaserShutdown(void) const;

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

    //Set to true to disable laser.
    bool myForceLaserShutdown;

	//The object has valid states 
    bool itsReady;

};

#endif /* CFG_MSPROT_H */