/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2004  Jai Harpalani
 DESCRIPTION:   TSXC_Connect  Class Definition
 LAST REVISION:
    Date    Description
    ----    -----------
  09-03-08  t71mr00073743:Allocate 7 bits for myInputFacility and myOutput-
            Facility and pack them into bits16 along with myConnectState.
--------------------------------------------------------------------------*/

#ifndef TSXC_CONNECT_H
#define TSXC_CONNECT_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>

//
// This class contains information about one unidirectional connection.
// There will be one instance of this class for each potential
// unidirectional connection.
//
class TSXC_Connect : public TEL_BbObjectBase
{
public:
	
    // Class constructor
    TSXC_Connect();

    // Class destructor
    virtual ~TSXC_Connect();

    //
    // Methods to set object attributes
    //
    inline void SetInputFacility(uint8 Facility);
    inline void SetInputFacilityEndpoint(uint8 Endpoint);
    inline void SetOutputFacility(uint8 Facility);
    inline void SetOutputFacilityEndpoint(uint8 Endpoint);
    inline void SetType( CT_XC_ConnectType ConnType );
    inline void SetMapping( CT_XC_ConnectMapping ConnMapping );
    inline void SetState( CT_XC_ConnectState ConnState );


    //
    // Methods to get object attributes
    //
    inline uint8 GetInputFacility();
    inline uint8 GetInputFacilityEndpoint();
    inline uint8 GetOutputFacility();
    inline uint8 GetOutputFacilityEndpoint();
    inline CT_XC_ConnectType GetType();
    inline CT_XC_ConnectMapping GetMapping();
    inline CT_XC_ConnectState GetState();

    //
    // Method to display class data
    //
    void PrintConnect();
    void PrintConnectActive(UINT8 theInput, UINT8 theInputEndpt);

    //
    // Operators
    //
    bool operator==(const TSXC_Connect& theConnect) const;
    bool operator!=(const TSXC_Connect& theConnect) const;
    TSXC_Connect& operator=(const TSXC_Connect& theConnect);

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
    // Attributes for each unidirectional connection.
    // Note that data members have been packed into bits to conserve space.
    //
    uint8   myInputFacilityEndpoint;
    uint8   myOutputFacilityEndpoint;
    uint8   myInputFacility;
    uint8   myOutputFacility;
    bits8   myConnectState:1;               // CT_XC_ConnectState
    bits8   myConnectType:5;                // CT_XC_ConnectType
    bits8   myConnectMapping:2;             // CT_XC_ConnectMapping

};

// *************
// Set Methods
// *************
inline void TSXC_Connect::SetInputFacility( uint8 Facility )
{
    myInputFacility = Facility; 
}

inline void TSXC_Connect::SetInputFacilityEndpoint( uint8 Endpoint )
{
    myInputFacilityEndpoint = Endpoint;
}

inline void TSXC_Connect::SetOutputFacility( uint8 Facility )
{
    myOutputFacility = Facility;
}

inline void TSXC_Connect::SetOutputFacilityEndpoint( uint8 Endpoint )
{
    myOutputFacilityEndpoint = Endpoint;
}

inline void TSXC_Connect::SetType( CT_XC_ConnectType ConnType )
{
    myConnectType = ConnType;
}

inline void TSXC_Connect::SetMapping( CT_XC_ConnectMapping ConnMapping )
{
    myConnectMapping = ConnMapping;
}

inline void TSXC_Connect::SetState( CT_XC_ConnectState ConnState )
{
    myConnectState = ConnState;
}

// *************
// Get Methods
// *************
inline uint8 TSXC_Connect::GetInputFacility()
{
    return myInputFacility;
}

inline uint8 TSXC_Connect::GetInputFacilityEndpoint()
{
    return myInputFacilityEndpoint;
}

inline uint8 TSXC_Connect::GetOutputFacility()
{
    return myOutputFacility;
}

inline uint8 TSXC_Connect::GetOutputFacilityEndpoint()
{
    return myOutputFacilityEndpoint;
}

inline CT_XC_ConnectType TSXC_Connect::GetType()
{
    return static_cast<CT_XC_ConnectType>(myConnectType);
}

inline CT_XC_ConnectMapping TSXC_Connect::GetMapping()
{
    return static_cast<CT_XC_ConnectMapping>(myConnectMapping);
}

inline CT_XC_ConnectState TSXC_Connect::GetState()
{
    return static_cast<CT_XC_ConnectState>(myConnectState);
}

#endif // TSXC_CONNECT_H
