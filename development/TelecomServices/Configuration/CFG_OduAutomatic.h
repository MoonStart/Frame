/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_ODUAUTOMATICOBJECT_H
#define CFG_ODUAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_OduAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OduAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OduAutomatic(void);

    //This method will set the force BDI attribute
    bool SetForceBDI(bool theForceBDI);

    //This method will return the value of the Force BDI atribute
    bool GetForceBDI() const;

    //This method will set the force OCI attribute
    bool SetForceOCI(bool theForceOCI);

    //This method will return the value of the Force OCI atribute
    bool GetForceOCI() const;

    //This method will set the force LCK attribute
    bool SetForceLCK(bool theForceLCK);

    //This method will return the value of the Force AIS atribute
    bool GetForceLCK() const;

    //This method will set the force LCK attribute
    bool SetForceAIS(bool theForceAIS);

    //This method will return the value of the Force AIS atribute
    bool GetForceAIS() const;


    //This method will set the Force Internal OCI attribute
    bool SetForceInternalOCI(bool theForceInternalOCI);

    //This method will return the value of the Force Internal OCI atribute
    bool GetForceInternalOCI() const;

    //This method will set the Force Internal LCK attribute
    bool SetForceInternalLCK(bool theForceInternalLCK);

    //This method will return the value of the Force Internal LCK atribute
    bool GetForceInternalLCK() const;

    //This method will set the Force Internal AIS attribute
    bool SetForceInternalAIS(bool theForceInternalAIS);

    //This method will return the value of the Force Internal AIS atribute
    bool GetForceInternalAIS() const;


    //This method will set the Suppress Backward Indicator attribute
    bool SetSuppressBackwardInd(bool theSuppressBackwardInd);

    //This method will return the value Suppress Backward Indicator attribute
    bool GetSuppressBackwardInd() const;

    //This method will set the 1 Way Drop XC attribute
    bool SetDrop(bool theDrop);

    //This method will return the value 1 Way Drop XC attribute
    bool GetDrop() const;

    //This method will set the 1 Way Add XC attribute
    bool SetAdd(bool theDrop);

    //This method will return the value 1 Way Add XC attribute
    bool GetAdd() const;

    bool SetTxPayloadType(CT_TEL_PayloadSignalId theTxPayloadType);
    CT_TEL_PayloadSignalId GetTxPayloadType() const;

    bool SetTribSize(CT_TEL_TS_SIZE theTsSize);
    CT_TEL_TS_SIZE GetTribSize() const;

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
    bool myForceOCI;
    bool myForceLCK;
    bool myForceAIS;

    bool myForceInternalOCI;
    bool myForceInternalLCK;
    bool myForceInternalAIS;

    // The Suppress Backward Indicators Exists
    bool mySuppressBackwardInd;
    // 1 Way Drop XC
    bool myAdd;
    // 1 Way Add XC
    bool myDrop;

    //Payload Structure Identifier
    CT_TEL_PayloadSignalId myTxPayloadType;

    //Trib slot size
    CT_TEL_TS_SIZE myTribSize;
};

#endif /* CFG_ODUAUTOMATICOBJECT_H */

