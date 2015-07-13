/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OMSAUTOMATICPWRADJ_H
#define CFG_OMSAUTOMATICPWRADJ_H

#include "CFG_Object.h"
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>

//This object contains the output of the action that controls the EVOA.
class CFG_OmsAutomaticPwrAdj
: public CFG_Object
{

public:
	//Constructor.
    CFG_OmsAutomaticPwrAdj(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OmsAutomaticPwrAdj(void);

    CT_TEL_mBm GetGain() const;
    bool SetGain(CT_TEL_mBm theGain);

    CT_TEL_mBm GetGainTilt() const;
    bool SetGainTilt(CT_TEL_mBm theGain);

    CT_TEL_mBm GetGroupEvoa() const;
    bool SetGroupEvoa(CT_TEL_mBm theEvoa);

    //Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CT_TEL_mBm myGain;
    CT_TEL_mBm myGainTilt;

    CT_TEL_mBm myGroupEvoa;
};

#endif /* CFG_OMSAUTOMATICPWRADJ_H */

