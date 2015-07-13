/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MSAUTOMATICOBJECT_H
#define CFG_MSAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the automatic configuration
//of one Ms interface.
class CFG_MsAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_MsAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_MsAutomatic(void);

	//This method sets the current selected timing reference
    bool SetIsActiveRef(bool theIsActiveRef);

	//This method sets the current selected timing reference
    bool GetIsActiveRef() const;


	//This method sets the current selected timing reference
    bool SetSelectedRefSSM(CT_FAC_RxSsm theSelectedRefSSM);

	//This method sets the current selected timing reference
    CT_FAC_RxSsm GetSelectedRefSSM() const;


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

    // The Is Actice Reference flag (true if this is the active reference)
    bool myIsActiveRef;

    // The SSM of the Selected Reference
    CT_FAC_RxSsm mySelectedRefSSM;
};

#endif /* CFG_MSAUTOMATICOBJECT_H */

