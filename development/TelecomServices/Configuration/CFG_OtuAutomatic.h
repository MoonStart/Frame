/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTUAUTOMATICOBJECT_H
#define CFG_OTUAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_OtuAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OtuAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OtuAutomatic(void);

    //This method will set the force BDI attribute
    bool SetForceBDI(bool theForceBDI);

    //This method will return the value of the Force BDI attribute
    bool GetForceBDI() const;

    //This method will set the Suppress Backward Indicator attribute
    bool SetSuppressBackwardInd(bool theSuppressBackwardInd);

    //This method will return the value Suppress Backward Indicator attribute
    bool GetSuppressBackwardInd() const;

    //This method will set the Send Defect To Mate attribute
    bool SetSendDefectToMate(bool theSendDefectToMate);

    //This method will return the value of the Send Defect To Mate attribute
    bool GetSendDefectToMate() const;


    //This method resets all attributes to their default value.
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
    bool mySuppressBackwardInd;
    bool mySendDefectToMate;

};

#endif /* CFG_OTUAUTOMATICOBJECT_H */

