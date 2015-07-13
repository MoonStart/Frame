/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTSOBJECT_H
#define CFG_OTSOBJECT_H

#include "CFG_Object.h"
#include "CommonTypes/CT_G709Trace.h"

//This object contains all the generic OTS configuration for OTS line interface.
class CFG_Ots 
: public CFG_Object
{

public:
    //Constructor.
    CFG_Ots(uint32 theIndex);

    //Virtual destructor.
    virtual ~CFG_Ots(void);

    bool GetCatpsEnable() const;
    void SetCatpsEnable(bool theCatpsEnable);

    const CT_G709Trace& GetTxTrace() const;
    void SetTxTrace(const CT_G709Trace& theTrace);

    CT_TEL_mBm GetChannelOutputPowerTarget() const;
    void SetChannelOutputPowerTarget(CT_TEL_mBm thePower);

    CT_TEL_mBm GetChannelInputPowerTarget() const;
    void SetChannelInputPowerTarget(CT_TEL_mBm thePower);

    CT_TEL_mBm GetMaximumGain() const;
    void       SetMaximumGain(CT_TEL_mBm theGain);

    CT_TEL_mBm GetMinimumChOutputPwr() const;
    void       SetMinimumChOutputPwr(CT_TEL_mBm thePower);

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
    bool myCatpsEnable;
    CT_G709Trace myTxTrace;
    CT_TEL_mBm myChOutputPwrTarget;
    CT_TEL_mBm myChInputPwrTarget;
    CT_TEL_mBm myMaximumGain;
    CT_TEL_mBm myMinimumChOutputPwr;

};

#endif /* CFG_OTSOBJECT_H */

