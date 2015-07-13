/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTSOCHOHAUTOMATIC_H
#define CFG_OTSOCHOHAUTOMATIC_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic configuration 
//for one port.
class CFG_OtsOchOHAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OtsOchOHAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OtsOchOHAutomatic(void);

    bool SetForceFDIO(bool theForceFDIO);
    bool GetForceFDIO() const;

    bool SetForceFDIP(bool theForceFDIP);
    bool GetForceFDIP() const;

    bool SetForceFDIPOS(bool theForceFDIPOS);
    bool GetForceFDIPOS() const;

    bool SetForceOCI(bool theForceOCI);
    bool GetForceOCI() const;

    //Debug methods
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    bool myForceFDIO;
    bool myForceFDIP;
    bool myForceFDIPOS;
    bool myForceOCI;

};

#endif /* CFG_OTSOCHOHAUTOMATIC_H */

