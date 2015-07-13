//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_SYNCSTATUS_H
#define MON_SYNCSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include "MON_Object.h"


// This class hold the status value (current state of the Clock Selection Timing Mode) 
// for the SYNC layer.
class MON_SyncStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_SyncStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_SyncStatus();

    // These methods are modifiers and accessors for 
    // the current state of the Clock Selection Timing Mode
    CT_TEL_ClkSelState GetCurrentState() const;
    bool SetCurrentState(CT_TEL_ClkSelState theCurrentState);

    // These methods are modifiers and accessors for the Freerun SSM  
    CT_FAC_RxSsm GetFreerunSsm() const;
    bool SetFreerunSsm(CT_FAC_RxSsm theFreerunSsm);

    //These methods are modifiers and accessors for the card clock mode
	bool SetClockMode(CT_TEL_ClkMode theMateClockMode);
	CT_TEL_ClkMode GetClockMode() const;
	
	//These methods are modifiers and accessors for the mate card clock mode
	bool SetMateClockMode(CT_TEL_ClkMode theMateClockMode);
	CT_TEL_ClkMode GetMateClockMode() const;
 
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

    //The current state of the Clock Selection Timing Mode.
    CT_TEL_ClkSelState myCurrentState;

    // The Freerun SSM
    CT_FAC_RxSsm       myFreerunSsm;

	//The clock mode
    CT_TEL_ClkMode myClockMode;

	//The remote clock mode
    CT_TEL_ClkMode myMateClockMode;
};

#endif /* MON_SYNCSTATUS_H */

