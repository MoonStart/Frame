/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_BrMCastMask      Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_BRIDGE_ROLL_MASK_C
#define TSXC_BRIDGE_ROLL_MASK_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_BrMCastMask.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <XC/TSXC_TestMenu.h>

// *************
// Constructor
// *************
TSXC_BrMCastMask::TSXC_BrMCastMask()
{
    Reset();
}

// *************
// Destructor
// *************
TSXC_BrMCastMask::~TSXC_BrMCastMask()
{
}

// *************
// Initialize
// *************
void TSXC_BrMCastMask::Reset()
{
    myMCastId = MULTICASTID_INVALID;
    myMaskAction = CT_XC_BR_MASK_NONE;
    for (int i = 0; i< MAX_HCSS_SWFAB_SHELF; i++)
    {
        myMCastShelfId[i] = UNKNOWN_SHELF_ID;
        myMCastImuxLMask[i] = 0;
        myMCastImuxPMask[i] = 0;
    }
}

// *********************
// Serialization Methods
// *********************

ostream& TSXC_BrMCastMask::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myMCastId);
    theStream<<FC_InsertVar(myMaskAction);
    for (int i = 0; i< MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream<<FC_InsertVar(myMCastShelfId[i]);
        theStream<<FC_InsertVar(myMCastImuxLMask[i]);
        theStream<<FC_InsertVar(myMCastImuxPMask[i]);
    }
    return theStream;
}

istream& TSXC_BrMCastMask::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myMCastId);
    theStream>>FC_ExtractVar(myMaskAction);
    for (int i = 0; i< MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream>>FC_ExtractVar(myMCastShelfId[i]);
        theStream>>FC_ExtractVar(myMCastImuxLMask[i]);
        theStream>>FC_ExtractVar(myMCastImuxPMask[i]);
    }
    return theStream;
}

/*
FC_Stream& TSXC_BrMCastMask::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myMCastType;
    return theStream;
}

FC_Stream& TSXC_BrMCastMask::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myMCastType;
    return theStream;
}
*/

bool TSXC_BrMCastMask::operator==(const TSXC_BrMCastMask& theMask) const
{
    if ( (myMCastId != theMask.myMCastId) ||
         (myMaskAction != theMask.myMaskAction))
    {
        return false;
    }

    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        if ( (myMCastShelfId[i]   != theMask.myMCastShelfId[i] )  ||
             (myMCastImuxLMask[i] != theMask.myMCastImuxLMask[i]) ||
             (myMCastImuxPMask[i] != theMask.myMCastImuxPMask[i]))
        {
            return false;
        }
    }
    return true;
}

bool TSXC_BrMCastMask::operator!=(const TSXC_BrMCastMask& theMask) const
{
    return (!(*this == theMask));
}

// *************
// Set Method
// *************
void TSXC_BrMCastMask::SetMCastId(uint16 theMCastId)
{
    myMCastId = theMCastId;
}

void TSXC_BrMCastMask::SetMaskAction(uint8 theAction)
{
    myMaskAction = theAction;
}

void TSXC_BrMCastMask::SetMCastImuxLMask(uint32 theMCastImuxLMask, uint8 theShelfIdx)
{
    if (theShelfIdx < MAX_HCSS_SWFAB_SHELF)
        myMCastImuxLMask[theShelfIdx] = theMCastImuxLMask;
}

void TSXC_BrMCastMask::SetMCastImuxPMask(uint32 theMCastImuxPMask, uint8 theShelfIdx)
{
    if (theShelfIdx < MAX_HCSS_SWFAB_SHELF)
        myMCastImuxPMask[theShelfIdx] = theMCastImuxPMask;
}

// *************
// Get Method
// *************
bool TSXC_BrMCastMask::IsMaskSet() const
{
    if (myMCastId == MULTICASTID_INVALID)
        return false;
    else
        return true;
}

uint16 TSXC_BrMCastMask::GetMCastId() const
{
    return myMCastId;
}

uint8 TSXC_BrMCastMask::GetMaskAction() const
{
    return myMaskAction;
}

uint32 TSXC_BrMCastMask::GetMCastImuxLMask(uint8 theShelfIdx) const
{
    if (theShelfIdx < MAX_HCSS_SWFAB_SHELF)
        return myMCastImuxLMask[theShelfIdx];
    return 0;
}

uint32 TSXC_BrMCastMask::GetMCastImuxPMask(uint8 theShelfIdx) const
{
    if (theShelfIdx < MAX_HCSS_SWFAB_SHELF)
        return myMCastImuxPMask[theShelfIdx];
    return 0;
}

#endif // TSXC_BRIDGE_ROLL_MASK_C
