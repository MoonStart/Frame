/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2004  Jai Harpalani
 DESCRIPTION:   XC_ActiveSource  Class Definition
--------------------------------------------------------------------------*/

#ifndef XC_SOURCEACTIVESTATUS_H
#define XC_SOURCEACTIVESTATUS_H

#include <TelCommon/TEL_BbObjectBase.h>


//
// This class contains information about one active 
// Facility/Facility Endpoint.
// There will be one instance of this class for each potential
// Facility Endpoint on every Facility.
//
class TSXC_SourceActiveStatus : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_SourceActiveStatus();

    // Class destructor
    virtual ~TSXC_SourceActiveStatus();

    //
    // Methods to set object attributes
    //
    void SetActiveFacility(uint8 Facility);
    void SetActiveFacilityEndpoint(uint8 Endpoint);
    void SetSourceFacility(uint8 Facility);
    void SetSourceFacilityEndpoint(uint8 Endpoint);
    void ResetActiveFacility();
    void ResetActiveFacilityEndpoint();
    
    //
    // Methods to get object attributes
    //
    uint8 GetActiveFacility();        
    uint8 GetActiveFacilityEndpoint();
    uint8 GetSourceFacility();
    uint8 GetSourceFacilityEndpoint();
    bool  IsActiveFacilitySet();
    bool  IsActiveFacilityEndpointSet();

    //
    // Method to display class data
    //
    bool PrintSource(uint8 requestedFacID, bool filter);

    //
    // Operators
    //
    bool operator==(const TSXC_SourceActiveStatus& theActStatus) const;
    bool operator!=(const TSXC_SourceActiveStatus& theActStatus) const;

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
    // Attributes for each source endpoint.
    //
    // (mySourceFacility, mySourceFacilityEndpoint) identifies the source
    // (myActiveFacility, myActiveFacilityEndpoint) identifies the source's active endpoint
    //
    uint8                mySourceFacility;
    uint8                mySourceFacilityEndpoint;
    uint8                myActiveFacility;
    uint8                myActiveFacilityEndpoint;

};

#endif // XC_SOURCEACTIVESTATUS_H

