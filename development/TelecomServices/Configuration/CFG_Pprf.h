/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_PPRFOBJECT_H
#define CFG_PPRFOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>


#include "CFG_Object.h"


// This object contains all the DCC IP Link Profile
// configuration.
class CFG_Pprf
: public CFG_Object
{

public:

	//Constructor.
    CFG_Pprf(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Pprf(void);

    // From LAPD Profile
    void SetMaxReceiveUnits(uint16 theMaxReceiveUnits);
    uint16 GetMaxReceiveUnits() const;

    void SetFCS(uint8 theFCS);
    uint8 GetFCS() const;

    void SetRestartTimer(uint8 theRestartTimer);
    uint8 GetRestartTimer() const;

    void SetMaxTerminateValue(uint8 theMaxTerminateValue);
    uint8 GetMaxTerminateValue() const;

    void SetMaxConfigureValue(uint8 theMaxConfigureValue);
    uint8 GetMaxConfigureValue() const;

    void SetMaxFailureValue(uint8 theMaxFailureValue);
    uint8 GetMaxFailureValue() const;


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

    uint16            myMaxReceiveUnits;
    uint8             myFCS;
    uint8             myRestartTimer;
    uint8             myMaxTerminateValue;
    uint8             myMaxConfigureValue;
    uint8             myMaxFailureValue;

    FC_CmdProcessor::STATUS PprfError( void );
};

#endif /* CFG_PPRFOBJECT_H */

