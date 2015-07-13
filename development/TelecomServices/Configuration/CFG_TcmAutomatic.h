/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_TCMAUTOMATICOBJECT_H
#define CFG_TCMAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include "CFG_Object.h"

//This object contains all the generic ODU TCM configuration 
//for one port.
class CFG_TcmAutomatic: public CFG_Object
{

public:

    //Constructor.
    CFG_TcmAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_TcmAutomatic(void);

    //This method will set the force BDI attribute
    bool SetForceBDI(bool theForceBDI);

    //This method will return the value of the Force BDI atribute
    bool GetForceBDI() const;

    //This method will set the force BIAE attribute
    bool SetForceBIAE(bool theForceBIAE);

    //This method will return the value of the Force BIAE atribute
    bool GetForceBIAE() const;

    //This method will set the Suppress Backward Indicator attribute
    bool SetSuppressBackwardInd(bool theSuppressBackwardInd);

    //This method will return the value Suppress Backward Indicator attribute
    bool GetSuppressBackwardInd() const;


    //Debug Methods  
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    bool myForceBDI;
    bool myForceBIAE;

    // The Suppress Backward Indicators Exists
    bool mySuppressBackwardInd;
};

#endif /* CFG_TCMAUTOMATICOBJECT_H */

