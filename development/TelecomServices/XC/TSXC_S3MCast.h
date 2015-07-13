/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2009        Kumar Solai
    DESCRIPTION:   TSXC Stage Three Multicast Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_S3MCAST_H
#define TSXC_S3MCAST_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include "CommonTypes/CT_AgentFacility.h"


//--------------------------------------------------------------------------------------------------
// This class contains information to support multicast connection
//--------------------------------------------------------------------------------------------------

class TSXC_S3MCast : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_S3MCast();

    // Class destructor
    virtual ~TSXC_S3MCast();

    //
    // Validate Methods
    //
    bool IsMcastIdSet() const;
    
    //
    // Methods to set object attributes
    //
    void InitMCast();
    void SetMCastId( uint16 theMCastId );
    void SetDestination( uint8 theDest );
    void SetDestination( CT_FAC_StsMap& theDst );

    //
    // Methods to get object attributes
    //
    uint16 GetMCastId();
    uint8 GetDestination();
    void GetDestinationMap(CT_FAC_StsMap& theDstMap);

    //
    // Method to display class data
    //
    void PrintMulticast(int theChan);

    //
    // Operators
    //
    bool operator==(const TSXC_S3MCast& theMCast) const;
    bool operator!=(const TSXC_S3MCast& theMCast) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // MulticastId
    uint16  myMCastId;

    // Bit field, each bit representing destination (supports 8 destinations)
    uint8   myDestination;      

    // Larger set of bit fields, each bit representing a destination (supports 160 destinations)
    uint16  myDst[10];
};

#endif // TSXC_S3MCAST_H
