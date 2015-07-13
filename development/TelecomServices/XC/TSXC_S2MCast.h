/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     January, 2009    Teresa Chen
    DESCRIPTION:   TSXC Stage Two Multicast Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_S2MCAST_H
#define TSXC_S2MCAST_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>
//--------------------------------------------------------------------------------------------------
class TSXC_DESTINATION
{
public:
    void    Init()
    {
        Shelf = 0;
        ImuxSlotMap = 0;
    }
    void    InitPrev()
    {
        Shelf = 0xff;
        ImuxSlotMap = 0xffff;
    }
    bool    IsEmpty() const
    {
        return (Shelf == 0 && ImuxSlotMap == 0);
    }
    bool operator==(const TSXC_DESTINATION& theSrc) const
    {
        return (Shelf == theSrc.Shelf && ImuxSlotMap == theSrc.ImuxSlotMap);
    }
    bool operator!=(const TSXC_DESTINATION& theSrc) const
    {
        return (!(*this == theSrc));
    }
//--- Data members    
    UINT8   Shelf;
    UINT16  ImuxSlotMap;
};

//--------------------------------------------------------------------------------------------------
// This class contains information to support Stage two multicast configuration
//--------------------------------------------------------------------------------------------------

class TSXC_S2MCast : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_S2MCast();

    // Class destructor
    virtual ~TSXC_S2MCast();

    //
    // Validate Methods
    //
    
    //
    // Methods to set object attributes
    //
    void InitMCast();
    void InitMCastPrev();
    void SetShelfSlots(const TSXC_DESTINATION theDest[]);

    //
    // Methods to get object attributes
    //
    void    GetShelfSlots(TSXC_DESTINATION theDest[]);
    bool    IsEmpty();

    // Composite method to get source slot and endpoint based on index

    //
    // Method to display class data
    //
    void PrintMulticast(int theChan);

    //
    // Operators
    //
    bool operator==(const TSXC_S2MCast& theS2MCast) const;
    bool operator!=(const TSXC_S2MCast& theS2MCast) const;
    void operator=(const TSXC_S2MCast& theS2MCast);

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
protected:
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    TSXC_DESTINATION   myDest[TSXC_MAX_SHELF_PER_MCAST]; // Contains the dst shelves and slot maps per shelf
};

#endif // TSXC_S2MCAST_H
