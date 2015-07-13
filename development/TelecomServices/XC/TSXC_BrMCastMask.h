/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008    Teresa Chen
 DESCRIPTION:   TSXC_BrMCastMask   Class Definition
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_BRIDGE_ROLL_MASK_H
#define TSXC_BRIDGE_ROLL_MASK_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>

//
// This class contains information to support destination IMUX mapping
//

class TSXC_BrMCastMask : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_BrMCastMask();

    // Class destructor
    virtual ~TSXC_BrMCastMask();

    void Reset();
    //
    // Set/Get Methods
    //
    bool IsMaskSet() const;
    uint16 GetMCastId() const;
    uint8  GetMaskAction() const;
    uint32 GetMCastImuxLMask(uint8 theShelfIdx=0) const;
    uint32 GetMCastImuxPMask(uint8 theShelfIdx=0) const;

    void SetMCastId( uint16 theMCastId );
    void SetMaskAction( uint8 theAction );
    void SetMCastImuxLMask(uint32 theMCastImuxLMask, uint8 theShelfIdx=0);
    void SetMCastImuxPMask(uint32 theMCastImuxPMask, uint8 theShelfIdx=0);
    //
    // Operators
    //
    bool operator==(const TSXC_BrMCastMask& theMask) const;
    bool operator!=(const TSXC_BrMCastMask& theMask) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    // virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    // virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    uint16   myMCastId;                                // Multicast id
    uint8    myMaskAction;                             // '&' or '|' the mask
    uint8    myMCastShelfId[MAX_HCSS_SWFAB_SHELF];     // Multicast shelf id
    uint32   myMCastImuxLMask[MAX_HCSS_SWFAB_SHELF];   // card slot IMUXL Mask
    uint32   myMCastImuxPMask[MAX_HCSS_SWFAB_SHELF];   // card slot IMUXP Mask
};

#endif // TSXC_BRIDGE_ROLL_MASK_H
