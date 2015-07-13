/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OMSAUTOMATICSHUTDOWN_H
#define CFG_OMSAUTOMATICSHUTDOWN_H

#include "CFG_Object.h"
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>



//This object contains the output of the action that automaticly
//shutdown the amplifier laser when no signal is detected at their input.
// This class also hold the maximum gain that can be applied to the 
// amplifier to comply with class 3A requirement.
class CFG_OmsAutomaticShutdown
: public CFG_Object
{

public:
	//Constructor.
    CFG_OmsAutomaticShutdown(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OmsAutomaticShutdown(void);
    
    bool SetAmplifierShutdown(bool theAmplifierShutdown);
    bool GetAmplifierShutdown() const;

	//Debug methods.
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    bool myAmplifierShutdown;
};

#endif /* CFG_OMSAUTOMATIC_H */

