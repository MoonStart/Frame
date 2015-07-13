/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MSOBJECT_H
#define CFG_MSOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>

#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Ms
: public CFG_Object
{

public:

	//Constructor.
    CFG_Ms(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Ms(void);


    // Set the Timing Reference type
    bool SetRefType(CT_TEL_MsTref theRefType);

    // Get the Timing Reference type
    CT_TEL_MsTref GetRefType() const;


    // Set SSM Generation mode
    bool SetSsmSupported(bool theSsmSupported);

    // Get the Timing Reference type
    bool GetSsmSupported() const;

	// Set Transmit SSM
    bool SetTxSsm (CT_FAC_RxSsm theTxSsm);

    // Get Transmit SSM
    CT_FAC_RxSsm GetTxSsm() const;

    // Set Transmit SSM Force
    bool SetTxSsmForce (bool theTxSsmForce);

    // Get Transmit SSM forcing
    bool GetTxSsmForce() const;


    //This method set the first timeslot for facility.
    bool SetFirstTimeslot(uint16 theFirstTimeslot);

    // This method returns the first timeslot for facility.
    uint16 GetFirstTimeslot() const;

	// Set derived source supported mode
    bool SetDerivedTimingSourceMode(CT_TEL_DT_Source_Mode theDTMode);

    // Get the derived timing supported mode
    CT_TEL_DT_Source_Mode GetDerivedTimingSourceMode() const;

    bool SetIsAutoTimingRedProv(bool isAutoTimingActive);
    bool GetIsAutoTimingRedProv() const;

    // User provisioning locked flag.
    bool SetIsProvLocked(bool isUserProvLocked);
    bool GetIsProvLocked() const;


	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
                    
    // The Timing Reference Type configured
    CT_TEL_MsTref     myRefType;

    // The SSM Supported Mode configured
    bool              mySsmSupported;

    // This method returns the first timeslot for facility.
    uint16            myFirstTimeslot;

	// The derived timing source mode configured
	CT_TEL_DT_Source_Mode  myDTSourceMode;

    // Is auto timing redundancy provisioned
    bool              myIsAutoTimingRedProv;

    // Is auto timing redundancy provisioned
    bool              myIsUserProvLocked;

    // The Transmit SSM
    CT_FAC_RxSsm      myTxSsm;

    // The Transmit SSM Forcing
    bool              myTxSsmForce;
};

#endif /* CFG_MSOBJECT_H */

