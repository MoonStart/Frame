//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MSSTATUS_H
#define MON_MSSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include "MON_Object.h"


//This class hold the status value (K1/K2 byte values) for the MS layer.
class MON_MsStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_MsStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_MsStatus();

    //These methods are modifiers and accessors for received K1/K2 bytes
    uint8 GetK1RxByte() const ;
    bool SetK1RxByte(uint8 theK1Byte) ;
    uint8 GetK2RxByte() const ;
    bool SetK2RxByte(uint8 theK2Byte) ;

    uint8 GetRxCsi() const ;
    bool SetRxCsi(uint8 theCsi) ;

    CT_FAC_RxSsm GetRxSsm() const ;
    bool SetRxSsm(CT_FAC_RxSsm theRxSsm) ;

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

    //The current K1 byte.
    uint8 myRxK1Byte;

    //The current K2 byte.
    uint8 myRxK2Byte;

    //The current CSI code
    uint8 myRxCsi;

    // The current Rx Ssm
    CT_FAC_RxSsm myRxSsm;
};

#endif /* MON_MSSTATUS_H */

