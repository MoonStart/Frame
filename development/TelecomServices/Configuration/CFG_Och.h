/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OCHOBJECT_H
#define CFG_OCHOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains configuration for OCH layer
class CFG_Och
: public CFG_Object
{

public:

    //Constructor.
    CFG_Och(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Och(void);

    void SetGain(CT_TEL_mBm theGain);
    CT_TEL_mBm GetGain() const;

    bool GetAutoPowerAdjEnable() const;
    void SetAutoPowerAdjEnable(bool theAutoPowerAdjEnable);


    //Debug methods
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CT_TEL_mBm myGain;
    bool myAutoPowerAdjEnable;
};

#endif /* CFG_OPTOBJECT_H */

