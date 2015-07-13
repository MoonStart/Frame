// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TXOPTRESULT_
#define _MON_TXOPTRESULT_

#include "MON_Object.h"

//This class is used for resut of On-Demand transmit power.
class MON_TxOptResult 
: public MON_Object
{
public:

    //Constructor.
    MON_TxOptResult(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_TxOptResult(void);

    //Returns or set the request ID associated with this result.
    void SetRequestID(MON_RequestID theRequestID);
    MON_RequestID GetRequestID(void) const;

    //Returns or set the power transmitted (mBm).
    void SetTransmitPower(CT_TEL_mBm thePower);
    CT_TEL_mBm GetTransmitPower() const;

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    MON_RequestID myRequestID;
    CT_TEL_mBm myTransmitPower;
};

#endif /* _MON_TXOPTRESULT_ */
