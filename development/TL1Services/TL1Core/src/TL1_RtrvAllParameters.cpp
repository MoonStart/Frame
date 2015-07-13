/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 31, 2011 - Avinash Kumar
DESCRIPTION:    Implementation file for TL1 RtrvAll Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RTRVALLPARAMETERS_H__
#include <TL1Core/TL1_RtrvAllParameters.h>
#endif

#include <CommonTypes/CT_TL1_Error.h>

TL1_RtrvAllParameters::TL1_RtrvAllParameters()
: myShowSlot(NULL), myShowSubslot(NULL), myShelfId(0),mySlotId(0),mySubSlotId(0)
{
}

TL1_RtrvAllParameters::~TL1_RtrvAllParameters()
{
}

void TL1_RtrvAllParameters::SetDefaultParameters(bool& theShowSlotBuf, bool& theShowSubslotBuf)
{
    if (myShowSlot == 0 || myShowSubslot == 0)
    {
        if (mySubSlotId != 0)    //Aid-Type is Subslot-Id
        {
            if (myShowSlot == 0)
            {
                theShowSlotBuf = false;
            }
            if (myShowSubslot == 0)
            {   
                theShowSubslotBuf = true;  
            }              
        }
        else if (mySlotId != 0)  //Aid-Type is Slot-Id
        {
            if (myShowSlot == 0)
            {
                theShowSlotBuf = true;     
            }
            if (myShowSubslot == 0)
            {   
                theShowSubslotBuf = false;  
            }            
        }
        else if (myShelfId != 0)   //Aid-Type is Shelf-Id
        {
            if (myShowSlot == 0)
            {   
                theShowSlotBuf = false;     
            }
            if (myShowSubslot == 0)
            {   
                theShowSubslotBuf = false;  
            }
        }
        else                                //Aid-Type is 'ALL'
        {
            if (myShowSlot == 0)
            {   
                theShowSlotBuf = true;     
            }
            if (myShowSubslot == 0)
            {   
                theShowSubslotBuf = true;  
            }
        }
    }
    if (myShowSlot == 0)
    {
        myShowSlot = &theShowSlotBuf;
    }
    if (myShowSubslot == 0)
    {
        myShowSubslot = &theShowSubslotBuf;
    }
    return;
}

void TL1_RtrvAllParameters::ValidateParameters() const
{
    if (mySubSlotId != 0)    //Aid-Type is Subslot-Id
    {
        if (*myShowSlot != false)
        {
            throw CT_TL1_IDNVError(CT_TL1_IDNVError::ER_IDNV_SUBSLOT_SHOWSLOT);
        }
        else if (*myShowSubslot != true)
        {
            throw CT_TL1_IDNVError(CT_TL1_IDNVError::ER_IDNV_SUBSLOT_SHOWSUBSLOT);
        }
    }
    else if (mySlotId != 0)  //Aid-Type is Slot-Id
    {
        if (*myShowSlot == false)
        {
            throw CT_TL1_IDNVError(CT_TL1_IDNVError::ER_IDNV_SLOT_SHOWSLOT);
        }
    }
    // For All other cases, all the options are valid.
    return;
}

