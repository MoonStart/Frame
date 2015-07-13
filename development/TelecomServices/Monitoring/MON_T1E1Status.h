//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_T1E1STATUS_H
#define MON_T1E1STATUS_H

#include <CommonTypes/CT_Telecom.h>
#include "MON_Object.h"


//This class hold the status value (trace message, levels) for the T1E1 layer.
class MON_T1E1Status 
: public MON_Object
{
public:

	//Constructor.
    MON_T1E1Status(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_T1E1Status();

    //These methods are modifiers and accessors for received SSM value
    CT_FAC_RxSsm GetRxSsm() const ;
    bool SetRxSsm(CT_FAC_RxSsm theSsm) ;

    //Debug Methods
    void Reset();
	virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The current SSM value.
    CT_FAC_RxSsm myRxSsm;
};

#endif /* MON_T1E1STATUS_H */

