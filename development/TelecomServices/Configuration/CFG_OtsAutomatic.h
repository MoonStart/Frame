/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTSAUTOMATICOBJECT_H
#define CFG_OTSAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic configuration 
//for one port.
class CFG_OtsAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OtsAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OtsAutomatic(void);

    bool SetForceOtsBDIO(bool theForceOtsBDIO);
    bool GetForceOtsBDIO() const;

    bool SetForceOtsBDIP(bool theForceOtsBDIP);
    bool GetForceOtsBDIP() const;

    bool SetForceOtsPMI(bool theForceOtsPMI);
    bool GetForceOtsPMI() const;
    void SetForceOtsPMIReason(string theReason);

    bool SetForceOmsFDIO(bool theForceOmsFDIO);
    bool GetForceOmsFDIO() const;

    bool SetForceOmsFDIP(bool theForceOmsFDIP);
    bool GetForceOmsFDIP() const;

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

    bool myForceOtsBDIO;
    bool myForceOtsBDIP;
    bool myForceOtsPMI;
    bool myForceOmsFDIO;
    bool myForceOmsFDIP;

    // Debug attributes
    string myForceOTS_PMIReason;
};

#endif /* CFG_OTSAUTOMATICOBJECT_H */

