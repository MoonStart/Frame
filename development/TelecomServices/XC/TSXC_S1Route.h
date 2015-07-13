/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009     Teresa Chen
    DESCRIPTION:   TSXC Stage One route Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_S1ROUTE_H
#define TSXC_S1ROUTE_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_CardTypes.h>
#include <XC/TSXC_CrossConnect.h>

//--------------------------------------------------------------------------------------------------
// This class contains information to support Stage one route configuration
//--------------------------------------------------------------------------------------------------

class TSXC_S1Route : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_S1Route();

    // Class destructor
    virtual ~TSXC_S1Route();

    //
    // Validate Methods
    //
    bool IsDstSet() const;

    //
    // Methods to set object attributes
    //
    void InitDst();
            
    void SetMCastId (uint16 theMCastId, CT_XC_ConnectMapping theMCastType );
    void SetDstShelf(uint8  theDstShelf) { myDstShelf = theDstShelf; }
    void SetDstSlot (uint8  theDstSlot)  { myDstSlot = theDstSlot;   }
    void SetDstSlice(uint8  theDstSlice) { myDstSlice = theDstSlice; }
    void SetConnId  (uint16 theConnId)   { myConnId = theConnId; }
    void SetDstCardType (CT_CardType theDstCardType)   { myDstCardType = theDstCardType; }
            
    //
    // Methods to get object attributes
    //
    uint16 GetMCastId( CT_XC_ConnectMapping theMCastType ) const;
    uint8  GetDstShelf() { return myDstShelf; }
    uint8  GetDstSlot () { return myDstSlot;  }
    uint8  GetDstSlice() { return myDstSlice; }
    uint16 GetConnId()   { return myConnId;   }
    uint16 GetDstCardType()   { return myDstCardType;   }

    //
    // Operators
    //
    bool operator==(const TSXC_S1Route& theRoute) const;
    bool operator!=(const TSXC_S1Route& theRoute) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
        
    uint16      myMCastId[XC_MAX_MCASTID]; //--- MCast Id for ingress IMUXL/IMUXP Channel
    uint8       myDstShelf;
    uint8       myDstSlot;
    uint8       myDstSlice;
    uint16      myConnId;
    CT_CardType myDstCardType;
};

#endif // TSXC_S1ROUTE_H
