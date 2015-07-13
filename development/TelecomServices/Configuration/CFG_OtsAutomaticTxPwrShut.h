/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTSAUTOMATICTXPWRSHUT_H
#define CFG_OTSAUTOMATICTXPWRSHUT_H

#include "CFG_Object.h"
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>

//This object contains all the generic OTS to apply directly to hardware.
//This configuration is controlled by the automatic action.
class CFG_OtsAutomaticTxPwrShut
: public CFG_Object
{

public:
	//Constructor.
    CFG_OtsAutomaticTxPwrShut(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OtsAutomaticTxPwrShut(void);

    bool GetAtpsActive() const;
    bool SetAtpsActive(bool theState);

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);

protected:
	//Serialization methods 
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    bool myAtpsActive;

};

#endif /* CFG_OTSAUTOMATICTXPWRSHUT_H */

