/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     January, 2009    Teresa Chen
    DESCRIPTION:   TSXC Stage Three Route Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_S3ROUTE_H
#define TSXC_S3ROUTE_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>

//--------------------------------------------------------------------------------------------------
class TSXC_SOURCE
{
public:
    void    Init()
    {
        Shelf = 0;
        Slot = 0;
        Channel = 0;
        ConnId = 0;
    }
    bool    IsEmpty() const
    {
        return (Shelf == 0 && Slot == 0);
    }
    bool operator==(const TSXC_SOURCE& theSrc) const
    {
        return ( (Shelf   == theSrc.Shelf) && 
                 (Slot    == theSrc.Slot ) && 
                 (Channel == theSrc.Channel) &&
                 (ConnId  == theSrc.ConnId) );
    }
    bool operator!=(const TSXC_SOURCE& theSrc) const
    {
        return (!(*this == theSrc));
    }
//--- Data members    
    UINT8        Shelf;
    UINT8        Slot;
    UINT16       Channel;
    UINT16       ConnId;
};

//--------------------------------------------------------------------------------------------------
// This class contains information to support Stage three route configuration
//--------------------------------------------------------------------------------------------------

class TSXC_S3Route : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_S3Route();

    // Class destructor
    virtual ~TSXC_S3Route();

    //
    // Validate Methods
    //

    bool IsSrcSet( uint8 idx ) const;

    //
    // Methods to set object attributes
    //
    void InitSrc();

    //
    // Methods to get object attributes
    //
    uint8        GetNumSrc() const ;  
    uint16       GetSrcFacilityEndpoint( uint8 idx ) const;
    uint8        GetSrcSlot( uint8 idx ) const;
    uint8        GetSrcShelf( uint8 idx ) const;
    uint16       GetSrcConnId( uint8 idx ) const;
     
    // Composite method to add source shelf, slot and endpoint
    bool AddSrc( uint16 theEndpoint, uint8 theSlot, uint8 theShelf, uint16 theConnId );

    // Composite method to remove source shelf, slot and endpoint
    void RmvSrc( uint16 theEndpoint, uint8 theSlot, uint8 theShelf, uint16 theConnId );
    
    //
    // Method to display class data
    //
    void PrintEgressImux(uint16 egress_imux_chan);
    
    //
    // Operators
    //
    bool operator==(const TSXC_S3Route& theRoute) const;
    bool operator!=(const TSXC_S3Route& theRoute) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //--- Egress Info
    TSXC_SOURCE   mySource[XC_MAX_SRC_ENDPT];  // Contains Shelf, Slot, IMUX Channel, and ConnId
};

#endif // TSXC_S3ROUTE_H
