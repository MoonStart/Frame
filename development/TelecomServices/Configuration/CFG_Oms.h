/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OMSOBJECT_H
#define CFG_OMSOBJECT_H

#include "CFG_Object.h"
#include <CommonTypes/CT_Telecom.h>

//This object contains all the generic OMS configuration for OMS line interface.
class CFG_Oms 
: public CFG_Object
{

public:
	//Constructor.
    CFG_Oms(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Oms(void);

    // Controls whether the Gain is Auto (true) or Manual (false).
    bool GetPowerControlEnable() const;
    void SetPowerControlEnable(bool thePowerControlEnable);

    // The Manual setting of the Gain
    CT_TEL_mBm GetGain() const;
    void SetGain(CT_TEL_mBm theGain);

    // Controls whether the Group Evoa is Auto (true) or Manual (false).
    bool GetGroupEvoaPowerControlEnable() const;
    void SetGroupEvoaPowerControlEnable(bool thePowerControlEnable);

    // Group EVOA is being added for a special case where we are applying an EVOA 
    // to a group of wavelenghts on the Express / Pass Through channels.
    // This can be used for other situations in the future. 
    // This value is for the Manual setting of the Evoa
    CT_TEL_mBm GetGroupEvoa() const;
    void SetGroupEvoa(CT_TEL_mBm theEvoa);

    //Debug methods
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

    bool myPowerControlEnable;
    CT_TEL_mBm myGain;

    bool myGroupEvoaPowerControlEnable;
    CT_TEL_mBm myGroupEvoa;
};

#endif /* CFG_OMSOBJECT_H */

