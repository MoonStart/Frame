/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 31, 2011 - Avinash Kumar
DESCRIPTION:    Header file for TL1 RtrvALL Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RTRVALLPARAMETERS_H__
#define __TL1_RTRVALLPARAMETERS_H__

#include <CommonTypes/CT_Equipment.h>

class TL1_RtrvAllParameters  
{
public:
    
    TL1_RtrvAllParameters();
    virtual ~TL1_RtrvAllParameters();

    inline void             SetShowSlot(bool*  theShowSlot);
    inline void             SetShowSubslot(bool* theShowSubslot);
    inline void             SetShelfId(CT_ShelfId theShelfId);
    inline void             SetSlotId(CT_SlotId theSlotId);
    inline void             SetSubslotId(CT_SlotId theSubslotId);
    inline void             SetAidString(const string& theAidString);

    inline bool*            GetShowSlot() const ;
    inline bool*            GetShowSubslot() const ;
    inline CT_ShelfId       GetShelfId() const;
    inline CT_SlotId        GetSlotId() const;
    inline CT_SlotId        GetSubslotId() const;
    inline const string&    GetAidString() const;

    void                    ValidateParameters() const;
    void                    SetDefaultParameters(bool& theShowSlotBuf, bool& theShowSubslotBuf);


private:
    bool*            myShowSlot;
    bool*            myShowSubslot;
    CT_ShelfId       myShelfId;
    CT_SlotId        mySlotId;
    CT_SlotId        mySubSlotId;
    string           myAidString;
};

inline void TL1_RtrvAllParameters::SetShowSlot(bool* theShowSlot)           { myShowSlot = theShowSlot; }
inline void TL1_RtrvAllParameters::SetShowSubslot(bool* theShowSubslot)     { myShowSubslot = theShowSubslot; }
inline void TL1_RtrvAllParameters::SetShelfId(CT_ShelfId theShelfId)        { myShelfId = theShelfId; }
inline void TL1_RtrvAllParameters::SetSlotId(CT_SlotId theSlotId)           { mySlotId = theSlotId; }
inline void TL1_RtrvAllParameters::SetSubslotId(CT_SlotId theSubslotId)     { mySubSlotId = theSubslotId; }
inline void TL1_RtrvAllParameters::SetAidString(const string& theAidString) { myAidString = theAidString; }

inline bool*            TL1_RtrvAllParameters::GetShowSlot() const     { return myShowSlot; }
inline bool*            TL1_RtrvAllParameters::GetShowSubslot() const  { return myShowSubslot; }
inline CT_ShelfId       TL1_RtrvAllParameters::GetShelfId() const      { return myShelfId; }
inline CT_SlotId        TL1_RtrvAllParameters::GetSlotId() const       { return mySlotId; }
inline CT_SlotId        TL1_RtrvAllParameters::GetSubslotId() const    { return mySubSlotId; }
inline const string&    TL1_RtrvAllParameters::GetAidString() const    { return myAidString; }

#endif  //__TL1_RTRVALLPARAMETERS_H__
