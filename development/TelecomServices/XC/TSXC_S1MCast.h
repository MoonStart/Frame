/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009     Teresa Chen 
    DESCRIPTION:   TSXC Stage One Multicast Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_S1MCAST_H
#define TSXC_S1MCAST_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>

//--------------------------------------------------------------------------------------------------
// This class contains information to support multicast configuration
//--------------------------------------------------------------------------------------------------

class TSXC_S1MCast : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_S1MCast();

    // Class destructor
    virtual ~TSXC_S1MCast();

    //
    // Validate Methods
    //
    bool IsMcastSet() const;
    bool IsImuxSet() const;
    bool IsImuxSet( uint8 theImuxType, uint8 theSlot, uint32 theMask,
                    uint8 theMaskAction ) const;
    
    //
    // Methods to set object attributes
    //
    void InitMCast();
    void SetMCastId( uint16 theMCastId );
    void SetMCastImuxLMap( uint16 theMcastImuxLMap );
    void SetMCastImuxPMap( uint16 theMcastImuxPMap );

    //
    // Methods to get object attributes
    //
    uint16  GetMCastId();
    uint16  GetMCastImuxLMap();
    uint16  GetMCastImuxPMap();

    // Composite method to get source slot and endpoint based on index

    //
    // Method to display class data
    //
    void PrintMulticast(int theChan);

    //
    // Operators
    //
    bool operator==(const TSXC_S1MCast& theMCast) const;
    bool operator!=(const TSXC_S1MCast& theMCast) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    uint16   myMCastId;         // Multicast id
    uint16   myMCastImuxLMap;   // Destination IMUXL Slot(s)
    uint16   myMCastImuxPMap;   // Destination IMUXP Slot(s) 

};

#endif // TSXC_S1MCAST_H
