/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_SYNCOBJECT_H
#define CFG_SYNCOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>

#include "CFG_Object.h"


//This object contains syncronization related configuration.
class CFG_Sync 
: public CFG_Object
{

public:

	//Constructor.
    CFG_Sync(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Sync(void);

  	//This method sets the timing mode.
	void SetTimingMode(CT_TEL_TimingMode theTimingMode);

	//This method returns the current timing mode.
	CT_TEL_TimingMode GetTimingMode() const;

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

    // Timing mode
    CT_TEL_TimingMode myTimingMode;
};

#endif /* CFG_SYNCOBJECT_H */

