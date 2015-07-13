//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_DRTRSTATUS_H
#define MON_DRTRSTATUS_H

#include "MON_Status.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_DCC_Definitions.h>


//This class hold the status value () for the DRTR layer.
class MON_DrtrStatus 
: public MON_Object
{
public:
	//Constructor.
    MON_DrtrStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_DrtrStatus(void);

    // These methods are modifiers and accessors for 
    // the current state of the DCC Router (Level 1 and Level 2)
    CT_DCC_RouterState GetLevel1_RouterState() const;
    bool SetLevel1_RouterState(CT_DCC_RouterState theRouterState);

    CT_DCC_RouterState GetLevel2_RouterState() const;
    bool SetLevel2_RouterState(CT_DCC_RouterState theRouterState);

    uint32 GetSequenceNumber() const; 
    bool SetSequenceNumber(uint32 theSequenceNumber); 



    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The current state of the DCC Router.
    CT_DCC_RouterState myLevel1_RouterState;
    CT_DCC_RouterState myLevel2_RouterState;

    // The TARP Sequence Number
    uint32 mySequenceNumber;
};

#endif /* MON_DRTRSTATUS_H */
