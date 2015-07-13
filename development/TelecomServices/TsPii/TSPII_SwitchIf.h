#ifndef _TSPII_SWITCH_IF_H
#define _TSPII_SWITCH_IF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2010 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SwitchIf.h
* Type:    C++ include
* Description:
*    Provides the platform independent interface for the Dune Fabric methods.
*
*************************************END***************************************
*/
#include <vector>
#include <map>
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_FabMulticast.h"
#include "CommonTypes/CT_Equipment.h"
#include "TsPii/TSPII_BaseIf.h"

enum TSPII_SwitchIf_TrafficType
{
    TSPII_SwitchIf_Traffic_Sonet,
    TSPII_SwitchIf_Traffic_Packet,
    TSPII_SwitchIf_Traffic_CesPacket,
    TSPII_SwitchIf_Traffic_Unknown
};

class TSPII_SwitchIf: public TSPII_BaseIf
{
public:

    //************************************************************************/
    // Constructor/destructor
    //************************************************************************/
    TSPII_SwitchIf(bool theDefault,
                   uint8 theNumPortShelves,
                   uint8 theNumPortSlots,
                   uint8 theNumCssSlots,
                   uint8 theNumOsis,
                   uint16 theNumMcgs);

    virtual ~TSPII_SwitchIf();

    //*************************************************************************/
    // Utility functions
    //************************************************************************/
    virtual void Reset();

    virtual void              SetSwitchMode(CT_TEL_SwitchMode theMode) { itsSwitchMode = theMode; }
    virtual CT_TEL_SwitchMode GetSwitchMode() { return itsSwitchMode; }

    virtual void           SetCableLength(uint8 theOsiPort, CT_CableLength theLength);
    virtual CT_CableLength GetCableLength(uint8 theOsiPort);
    virtual CT_CableLength GetCableLength();
    virtual CT_CableLength GetCableLengthDetected(uint8 theOsiPort);

    virtual void        SetOsiPortAssignment(uint8 theOsiPort, CT_ShelfId theShelf);
    virtual CT_ShelfId  GetOsiPortAssignment(uint8 theOsiPort);
    virtual uint        GetOsiCableMismatch(uint theOsiPort, uint &theFarShelf,
                                            uint &theFarSlot, uint &theFarSubSlot);
    virtual void        SetOsiEnabled(uint8 theOsi, bool theEnable);
    virtual bool        GetOsiEnabled(uint8 theOsi);
    virtual void        SetSlotEnabled(uint8 theSlot, bool theEnable);
    virtual bool        GetSlotEnabled(uint8 theSlot);
    virtual void        InvertOsiPolarity(uint8 theOsi, bool invert);
    virtual bool        GetOsiPolarity(uint8 theOsi);
    virtual void        SetOtherSideHwRev (uint8 theOsiPort, string hwRev);
    virtual string      GetOtherSideHwRev (uint8 theOsiPort);

    virtual void SetTopologyMap(vector<uint8> theTopology);
    virtual vector<uint8> GetTopologyMap();

    virtual void SetMcGroup(uint16 theMcId, vector<CT_FabMcMember> theMembers, bool theCommitNow = false);
    virtual void DeleteMcGroup(uint16 theMcId, bool theCommitNow = false);
    virtual void DeleteAllMcGroups(bool theCommitNow = false);
    virtual void CommitMcGroups();

    virtual CT_FabMcGroupMap & GetMcGroups();
    virtual void AddMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow);
    virtual void DeleteMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow);

    virtual void HwInit() {};
    virtual void HwInitCold() {};
    virtual void HwInitWarm() {};

    //************************************************************************/
    // Blackboard serialization
    //************************************************************************/
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream & WriteObject(ostream & theStream);
    virtual istream & ReadObject(istream & theStream);

    //************************************************************************/
    // Test Menus
    //************************************************************************/
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);

    //************************************************************************/
    // Retrieve local variables
    //************************************************************************/
    uint8 GetNumCssSlots() { return itsNumCssSlots; }

protected:
    // methods
    virtual void RefreshGet();
    virtual void RefreshSet();
    virtual string DisplaySwitchMode();
    virtual string DisplaySlotEnabled();
    virtual string DisplayMcGroups(bool printDetail);
    virtual string DisplayCableLength();
    virtual string DisplayOsiPortAssignment();
    virtual string DisplayOsiEnabled();
    virtual string DisplayOsiPolarity();
    virtual string DisplayOtherSideHwRevs();

    // data
    uint8                itsNumPortShelves;
    uint8                itsNumPortSlots;
    uint8                itsNumCssSlots;
    uint8                itsNumOsis;
    uint16               itsNumMcgs;
    CT_TEL_SwitchMode    itsSwitchMode;
    CT_CableLength       *itsCableLength;
    CT_ShelfId           *itsOsiPortAssignment;
    bool                 *itsOsiEnabled;
    bool                 *itsOsiPolarity;
    bool                 *itsMcgInitComplete;
    CT_FabMcGroupMap     itsMcGroupsMap;
    bool                 *itsSlotEnabled;
    vector<uint8>        itsTopologyMap;
    map< unsigned int, string, less<unsigned int> > itsOtherSideHwRevs;
};

#endif // _TSPII_SWITCH_IF_H
