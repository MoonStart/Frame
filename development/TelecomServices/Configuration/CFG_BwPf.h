/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_BWPFOBJECT_H
#define CFG_BWPFOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Bwpf
: public CFG_Object
{

public:

	//Constructor.
    CFG_Bwpf(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Bwpf(void);

    // Get Committed Information Rate.
    uint32 GetComitInfoRate() const;

    // Set Committed Information Rate.
    void SetComitInfoRate(uint32 theComitInfoRate);

    // Get Committed Burst Size.
    uint32 GetComitBrstSz() const;

    // Set Committed Burst Size.
    void SetComitBrstSz(uint32 theComitBrstSz);

    // Get Excess Information Rate.
    uint32 GetExcessInfoRate() const;

    // Set Excess Information Rate.
    void SetExcessInfoRate(uint32 theExcessInfoRate);

    // Get Excess Burst Size
    uint32 GetExcessBrstSz() const;

    // Set Excess Burst Size.
    void SetExcessBrstSz(uint32 theExcessBrstSz);

    // Get Color Mode.
    CT_TEL_BW_CM GetColorMode() const;

    // Set Color Mode.
    void SetColorMode(CT_TEL_BW_CM theColorMode);

    // Get Meter Type
    CT_TEL_BW_METERTYPE GetMeterType() const;

    // Set Meter Type.
    void SetMeterType(CT_TEL_BW_METERTYPE theMeterType);

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

    // Committed Information Rate.
    uint32 myComitInfoRate;
	
    // Committed Burst Size.
    uint32 myComitBrstSz;

    // Excess Burst Size.
    uint32 myExcessBrstSz;

    // Excess Information Rate.
    uint32 myExcessInfoRate;

    // Color Mode.
    CT_TEL_BW_CM myColorMode;

    // Meter Type.
    CT_TEL_BW_METERTYPE myMeterType;

};

#endif /* CFG_BWPFOBJECT_H */

