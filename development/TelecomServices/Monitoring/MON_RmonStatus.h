//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RMONSTATUS_H
#define MON_RMONSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include "MON_Object.h"


// This class hold the status value (current state of the Clock Selection Timing Mode) 
// for the RMON layer.
class MON_RmonStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_RmonStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_RmonStatus();


    // These methods are modifiers and accessors for the MAC address
    // Note: 2 fields
    uint32 GetIfPhysAddressHigh() const;
    bool SetIfPhysAddressHigh(uint32 theIfPhysAddressHigh);

    uint32 GetIfPhysAddressLow() const;
    bool SetIfPhysAddressLow(uint32 theIfPhysAddressLow);


    // These methods are modifiers and accessors for MTU Size  
    uint32 GetIfMtu() const;
    bool SetIfMtu(uint32 theIfMtu);
 
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

    //The MAC address of the interface.
    uint32              myIfPhysAddressHigh;
    uint32              myIfPhysAddressLow;

    //MTU Size
    uint32              myIfMtu;
};

#endif /* MON_RMONSTATUS_H */

