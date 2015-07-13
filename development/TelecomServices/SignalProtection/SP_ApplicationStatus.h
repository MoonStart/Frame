/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Protect
 TARGET   :     All
 DESCRIPTION:   Object indicates readiness of signal protect application
--------------------------------------------------------------------------*/

#ifndef SP_APPLICATIONSTATUS_H
#define SP_APPLICATIONSTATUS_H

#include <TelCommon/TEL_BbObjectBase.h>


//
// This class contains ready-state information for an entity. 
//
class SP_ApplicationStatus : public TEL_BbObjectBase
{
public:

    // Class constructor
    SP_ApplicationStatus();

    // Class destructor
    virtual ~SP_ApplicationStatus();

    //
    // Methods to change ready state.
    //
    void SetApplicationStatus(bool status);
    
    bool IsStatusDifferent(bool newStatus);
    //
    // Methods to get ready state.
    //
    bool IsReady();

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    
private:

    //
    // Attribute to store ready state
    //
    bool   myReadyState;

};

#endif // SP_APPLICATIONSTATUS_H

