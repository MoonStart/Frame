/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2010 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SwitchIf.cpp
* Type:    C++ source
* Description:
*     Definition of the class TSPII_SwitchIf which models the simulation generic
*     Fab (Dune Fabric) Interface entity.
*
*************************************END***************************************
*/
#include <string.h>
#include <strstream>
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_SwitchIf.h"

/************************************BEGIN*************************************
*
* Function:    TSPII_SwitchIf constructor
*
* Description:
*     TSPII_SwitchIfIf class constructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_SwitchIf::TSPII_SwitchIf(bool theDefault,
                               uint8 theNumPortShelves,
                               uint8 theNumPortSlots,
                               uint8 theNumCssSlots,
                               uint8 theNumOsis,
                               uint16 theNumMcgs) :
    TSPII_BaseIf(theDefault)
{
    itsNumPortShelves = theNumPortShelves;
    itsNumPortSlots = theNumPortSlots;
    itsNumCssSlots = theNumCssSlots;
    itsNumOsis = theNumOsis;
    itsNumMcgs = theNumMcgs;
    itsSwitchMode = CT_TEL_SwitchMode_None;

    itsCableLength = static_cast<CT_CableLength *>(malloc((itsNumOsis+1) * sizeof(CT_CableLength)));
    itsOsiPortAssignment = static_cast<CT_ShelfId *>(malloc((itsNumOsis+1) * sizeof(CT_ShelfId)));
    itsOsiEnabled = static_cast<bool *>(malloc((itsNumOsis+1) * sizeof(bool)));
    itsOsiPolarity = static_cast<bool *>(malloc((itsNumOsis+1) * sizeof(bool)));
    itsMcgInitComplete = static_cast<bool *>(malloc(itsNumMcgs * sizeof(bool *)));

    // itsMcGroupsMap cleared in call to Reset below

    itsSlotEnabled = static_cast<bool *>(malloc(itsNumCssSlots * sizeof(bool)));

    // itsTopologyMap cleared in call to Reset below 

    // create null string entry for hw rev of far side for each OSI (1-based);
    // hw rev is usually a single char, but it *can* be up to 4 ascii chars;
    string nullstring;
    for (uint i=1; i <= itsNumOsis; i++)
        itsOtherSideHwRevs[i] = nullstring;

    Reset();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SwitchIf destructor
*
* Description:
*     TSPII_SwitchIf class destructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_SwitchIf::~TSPII_SwitchIf()
{
    if (itsSlotEnabled != NULL) free(itsSlotEnabled);
    if (itsOsiEnabled != NULL) free(itsOsiEnabled);
    if (itsOsiPolarity != NULL) free(itsOsiPolarity);
    if (itsOsiPortAssignment != NULL) free(itsOsiPortAssignment);
    if (itsCableLength != NULL) free(itsCableLength);
    if (itsMcgInitComplete != NULL) free(itsMcgInitComplete);
    itsOtherSideHwRevs.clear();
}

/************************************BEGIN*************************************
*
* Function:    RefreshGet() class method
*
* Description:
*     Used to refresh the SwitchIf entity attributes.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::RefreshGet()
{
    // Configuration attributes
    itsSwitchMode = GetSwitchMode();
    for (uint8 aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        itsCableLength[aSlot] = GetCableLength(aSlot);
        itsOsiPortAssignment[aSlot] = GetOsiPortAssignment(aSlot);
        itsOsiEnabled[aSlot] = GetOsiEnabled(aSlot);
        itsOsiPolarity[aSlot] = GetOsiPolarity(aSlot);
        itsOtherSideHwRevs[aSlot] = GetOtherSideHwRev(aSlot);
    }

    for (uint8 aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        itsSlotEnabled[aSlot] = GetSlotEnabled(aSlot);
    }

    // Update the FapMcGroups table.
    itsMcGroupsMap = GetMcGroups();
}

/************************************BEGIN*************************************
*
* Function:    RefreshSet() class method
*
* Description:
*     Used to refresh the SwitchIf configuration
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::RefreshSet()
{
    // default Backplane mode
    SetSwitchMode(itsSwitchMode);

    for(uint8 aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        SetCableLength(aSlot, itsCableLength[aSlot]);
        SetOsiPortAssignment(aSlot, itsOsiPortAssignment[aSlot]);
        SetOsiEnabled(aSlot, itsOsiEnabled[aSlot]);
        InvertOsiPolarity(aSlot, itsOsiPolarity[aSlot]);
        SetOtherSideHwRev(aSlot, itsOtherSideHwRevs[aSlot]);
    }
 
    // write out the Backplane slot enables
    for(uint8 aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        SetSlotEnabled(aSlot, itsSlotEnabled[aSlot]);
    }

#ifndef PSOSP
     // write out the FAP Multicast groups
    CT_FabMcGroupMap::iterator fapMcIter;
    for(fapMcIter = itsMcGroupsMap.begin();
        fapMcIter != itsMcGroupsMap.end();
        fapMcIter++)
    {
        SetMcGroup(fapMcIter->first.Id, fapMcIter->second.Members);
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    Reset() class method
*
* Description:
*     Used to reset the SwitchIf entity attributes to a default state.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::Reset()
{
    TSPII_BaseIf::Reset();

    itsSwitchMode = CT_TEL_SwitchMode_None;

    string nullstring;
    for (uint8 aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        itsCableLength[aSlot] = CT_CABLELENGTH_UNKNOWN;
        itsOsiPortAssignment[aSlot] = 0;
        itsOsiEnabled[aSlot] = false;
        itsOsiPolarity[aSlot] = false;
        itsOtherSideHwRevs[aSlot] = nullstring;
    }

    for (uint8 aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        itsSlotEnabled[aSlot] = false;
    }

    itsTopologyMap.erase(itsTopologyMap.begin(), itsTopologyMap.end());

    itsMcGroupsMap.clear();

    for( uint aMcg = 0; aMcg < itsNumMcgs; aMcg++ )
    {
        itsMcgInitComplete[aMcg] = false;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetCableLength() class method
*
* Description: Sets the cablelength that the intershelf communication is to 
*               operate within.
*
* Inputs:
*     theCableLength - which Cable Length to set.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetCableLength(uint8 theOsiPort, CT_CableLength theCableLength)
{
    itsCableLength[theOsiPort] = theCableLength;
}

/************************************BEGIN*************************************
*
* Function:    GetCableLength() class method
*
* Description: Gets the cablelength that the intershelf communication
*                is configured for
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     theCableLength - the requested cable length.
*
*************************************END***************************************
*/
CT_CableLength TSPII_SwitchIf::GetCableLength(uint8 theOsiPort)
{
    return itsCableLength[theOsiPort];
}

CT_CableLength TSPII_SwitchIf::GetCableLength()
{
    return itsCableLength[1];
}

/************************************BEGIN*************************************
*
* Function:    GetCableLengthDetected() class method
*
* Description: Gets the OSI cable length detected by the Driver (if not SIM)
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     theCableLength - the requested cable length.
*
*************************************END***************************************
*/
CT_CableLength TSPII_SwitchIf::GetCableLengthDetected(uint8 theOsiPort)
{
    return itsCableLength[theOsiPort];
}

/************************************BEGIN*************************************
*
* Function:    SetOsiPortAssignment()
*
* Description: Sets the CSS OSI port number to which a port shelf is
*              connected.
*
* Inputs:
*     theOsiPort - 1 through 16
*     theShelf   - specified shelf for multishelf system, 2 through 9
*
* Outputs:
*     None
*
* Returns:
*     false = error, true = successful
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetOsiPortAssignment(uint8 theOsiPort, CT_ShelfId theShelf)
{
    if ((theOsiPort <= itsNumOsis) && (theShelf <= itsNumPortShelves+1))
    {
        itsOsiPortAssignment[theOsiPort] = theShelf;
    }
}

/************************************BEGIN*************************************
*
* Function:    GetOsiPortAssignment()
*
* Description: Gets the Port Shelf ID connected to the given OSI
*
* Inputs:
*     theOsiPort - which OSI to use for getting Port Shelf number
*
* Outputs:
*     None
*
* Returns:
*     A port shelf number
*
*************************************END****************************************/
CT_ShelfId TSPII_SwitchIf::GetOsiPortAssignment(uint8 theOsiPort)
{
    if (theOsiPort <= itsNumOsis)
    {
        return itsOsiPortAssignment[theOsiPort];
    }
    return 0;
}

/************************************BEGIN*************************************
*
* Function:    GetOsiCableMismatch()
*
* Description: Gets the mismatch status for the specified OSI Port  
*
* Inputs:
*     theOsiPort
*
* Outputs:
*     
*
* Returns:
*     theOsiPort - the OSI Port
*
*************************************END****************************************/
uint TSPII_SwitchIf::GetOsiCableMismatch(uint theOsiPort,
                                         uint &theFarShelf,
                                         uint &theFarSlot,
                                         uint &theFarSubslot)
{
    uint mismatch = 1; // no mismatch

    return mismatch;
}

/************************************BEGIN*************************************
*
* Function:    SetOsiEnabled() class method
*
* Description: Sets the Activate or deactivate state of the OSI links going
*              to that OSI.
*
* Inputs:
*     theOsi  - the OSI port to be enabled/disabled (1-16)
*
*     theEnable - true = enable, false = disable.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetOsiEnabled(uint8 theOsi, bool theEnable)
{
    char aErrBuf[80];

    if((theOsi > 0) && (theOsi <= itsNumOsis))
    {
        itsOsiEnabled[theOsi] = theEnable;
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::SetOsiEnabled invalid OSI number: %d", theOsi);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetOsiEnabled() class method
*
* Description: Gets the Enabled state of the OSI links going
*              to that OSI.
*
* Inputs:
*     theOsi - the OSI port being queried (1-16)
*
*
* Outputs:
*     None
*
* Returns:
*     theEnable - true = enable, false = disable.
*
*************************************END***************************************
*/
bool TSPII_SwitchIf::GetOsiEnabled(uint8 theOsi)
{
    char aErrBuf[80];

    if((theOsi > 0) && (theOsi <= itsNumOsis))
    {
        return itsOsiEnabled[theOsi];
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::GetOsiEnabled invalid OSI number: %d", theOsi);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return false;
    }
}

/************************************BEGIN*************************************
*
* Function:    InvertOsiPolarity() class method
*
* Description: Sets the Invert or Normal state of the OSI links polarity
*
* Inputs:
*     theOsi  - the OSI port to be set (1-16)
*
*     theEnable - true = enable, false = disable.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::InvertOsiPolarity(uint8 theOsi, bool Invert)
{
    char aErrBuf[128];

    if((theOsi > 0) && (theOsi <= itsNumOsis))
    {
        itsOsiPolarity[theOsi] = Invert;
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::InvertOsiPolarity invalid OSI number: %d", theOsi);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetOsiPolarity() class method
*
* Description: Gets the Enabled state of the OSI links polarity
*
* Inputs:
*     theOsi - the OSI port being queried (1-16)
*
*
* Outputs:
*     None
*
* Returns:
*     theEnable - true = enable, false = disable.
*
*************************************END***************************************
*/
bool TSPII_SwitchIf::GetOsiPolarity(uint8 theOsi)
{
    char aErrBuf[128];

    if((theOsi > 0) && (theOsi <= itsNumOsis))
    {
        return itsOsiPolarity[theOsi];
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::GetOsiPolarity invalid OSI number: %d", theOsi);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return false;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetSlotEnabled() class method
*
* Description: Sets the Activate or deactivate state of the FE600 links going
*              to that backplane slot.
*
* Inputs:
*     theSlot - the Shelf backplane slot to be enabled/disabled (0-13)
*
*     theEnable - true = enable, false = disable.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetSlotEnabled(uint8 theSlot, bool theEnable)
{
    char aErrBuf[80];

    if(theSlot < itsNumCssSlots)
    {
        itsSlotEnabled[theSlot] = theEnable;
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::SetSlotEnabled invalid slot: %d, %d", theSlot, itsNumCssSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetSlotEnabled() class method
*
* Description: Gets the Enabled state of the FE600 links going
*              to that backplane slot.
*
* Inputs:
*     theSlot - the backplane slot being queried (0-13)
*
*
* Outputs:
*     None
*
* Returns:
*     theEnable - true = enable, false = disable.
*
*************************************END***************************************
*/
bool TSPII_SwitchIf::GetSlotEnabled(uint8 theSlot)
{
    char aErrBuf[80];

    if(theSlot < itsNumCssSlots)
    {
        return itsSlotEnabled[theSlot];
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::GetSlotEnabled invalid slot: %d, %d", theSlot, itsNumCssSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return false;
    }
}

/************************************BEGIN*************************************
*
* Function:    GetOtherSideHwRev(), SetOtherSideHwRev()
*
* Description: Gets/Sets the hw revision of the card that the port under question
*              is connected to.
*
* Inputs:
*     theOsiPort - on this module
*
* Outputs:
*     None
*
* Returns:
*     The Get() method returns the hw rev in a string container.
*
*************************************END***************************************
*/
string TSPII_SwitchIf::GetOtherSideHwRev (uint8 theOsiPort)
{
    string rs;

    if (theOsiPort <= itsNumOsis)
        rs = itsOtherSideHwRevs[theOsiPort];
    else
    {   char ebuf[80];
        sprintf (ebuf, "%s: invalid port: %d",
                "GetOtherSideHwRev()", theOsiPort);
        FC_THROW_ERROR (FC_InvalidArgumentError, ebuf);
    }

    return (rs);
}

void TSPII_SwitchIf::SetOtherSideHwRev (uint8 theOsiPort, string hwRev)
{
    if (theOsiPort <= itsNumOsis)
        itsOtherSideHwRevs[theOsiPort] = hwRev;
    else
    {   char ebuf[80];
        sprintf (ebuf, "%s: invalid port: %d",
                "SetOtherSideHwRev()", theOsiPort);
        FC_THROW_ERROR (FC_InvalidArgumentError, ebuf);
    }

    return;
}

/************************************BEGIN*************************************
*
* Function:    SetTopologyMap() class method
*
* Description: Sets up a list of shelves that are in the fabric topology
*
* Inputs:
*     theTopology - list of ShelfIds in the Fabric domain
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetTopologyMap(vector<uint8> theTopology)
{
    itsTopologyMap = theTopology;
}

/************************************BEGIN*************************************
*
* Function:    GetTopologyMap() class method
*
* Description: Gets a list of shelf ids that are in the fabric topology
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     List of associated Shelf Ids
*
*************************************END***************************************
*/
vector<uint8> TSPII_SwitchIf::GetTopologyMap()
{
    return itsTopologyMap;
}

/************************************BEGIN*************************************
*
* Function:    SetMcGroup() class method
*
* Description: Sets up a new Multicast Group in the FAB20 or modifies an existing
*              group including deleting the group by passing an empty list.
*
* Inputs:
*     theMcId - the MultiCast Id (1-16383)
*
*     theMembers - a c++ vector list of multicast members in this group
*
*     theCommitNow - true=commit to hw now, false=commit to hw on next CommitMcGroups()
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::SetMcGroup(uint16 theMcId, vector<CT_FabMcMember> theMembers, bool theCommitNow)
{
#ifndef PSOSP
    char aErrBuf[80];
    CT_FabMcGroupKey   aKey;
    CT_FabMcGroupVal   aVal;
    CT_FabMcGroupMap::iterator fapMcIter;

    if(theMcId < itsNumMcgs)
    {

        aKey.Id = theMcId;
        aVal.Members = theMembers;

        itsMcgInitComplete[theMcId] = true;

        // Search for this element
        fapMcIter = itsMcGroupsMap.find(aKey);

        // If element already exists, check if its value is changing
        if (fapMcIter != itsMcGroupsMap.end())
        {
            if (fapMcIter->second == aVal)
            {
                fapMcIter->second.IsDeleted      = false;
            }
            else
            {
                fapMcIter->second                = aVal;
                fapMcIter->second.IsNewOrChanged = true;
                fapMcIter->second.IsDeleted      = false;
            }
        }
        // Else element doesn't exist, so insert it
        else
        {
            aVal.IsNewOrChanged = true;
            aVal.IsDeleted      = false;
            itsMcGroupsMap.insert(CT_FabMcGroupMap::value_type(aKey, aVal));
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::SetMcGroup invalid McId: %d, %d", theMcId, itsNumMcgs);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    DeleteMcGroup() class method
*
* Description:  Deletes specific Multicast Group in the Dune Fabric
*
* Inputs:
*     theMcId - Multicast Id to be deleted
*
*     theCommitNow - true=commit to hw now, false=commit to hw on next CommitMcGroups()
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::DeleteMcGroup(uint16 theMcId, bool theCommitNow)
{
#ifndef PSOSP
    char aErrBuf[80];
    CT_FabMcGroupKey   aKey;
    CT_FabMcGroupMap::iterator fapMcIter;

    if(theMcId < itsNumMcgs)
    {
        aKey.Id = theMcId;

        itsMcgInitComplete[theMcId] = true;

        // Search for this element
        fapMcIter = itsMcGroupsMap.find(aKey);

        if (fapMcIter != itsMcGroupsMap.end())
        {
            // Element exists - mark for deletion
            fapMcIter->second.IsDeleted = true;
        }
        else
        {
            // Element does not exist
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_SwitchIf::DeleteMcGroup invalid McId: %d, %d", theMcId, itsNumMcgs);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif // PSOSP
}

/************************************BEGIN*************************************
*
** Function:    DeleteAllMcGroups() class method
*
* Description:  Deletes all Multicast Groups in the FAB20
*
* Inputs:
*     theCommitNow - true=commit to hw now, false=commit to hw on next CommitMcGroups()
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::DeleteAllMcGroups(bool theCommitNow)
{
#ifndef PSOSP
    CT_FabMcGroupMap::iterator fapMcIter;

    for(fapMcIter = itsMcGroupsMap.begin();
        fapMcIter != itsMcGroupsMap.end();
        fapMcIter++)
    {
        fapMcIter->second.IsDeleted = true;
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    CommitMcGroups() class method
*
* Description:  Commits all Multicast Groups to the Dune Fabric chip
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::CommitMcGroups()
{
#ifndef PSOSP
    CT_FabMcGroupMap::iterator  fabMcGroupsIter;

    // Commit all connections stored in the Xconn table
    for(fabMcGroupsIter = itsMcGroupsMap.begin();
        fabMcGroupsIter != itsMcGroupsMap.end(); )
    {
        if(fabMcGroupsIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            fabMcGroupsIter = itsMcGroupsMap.erase(fabMcGroupsIter);
#endif
        }
        else if(fabMcGroupsIter->second.IsNewOrChanged)
        {
            // clear the flag since we are committing the changes
            fabMcGroupsIter->second.IsNewOrChanged = false;
            fabMcGroupsIter++;
        }
        else
        {
            // No change on this one.
            fabMcGroupsIter++;
        }
    }
#endif // PSOSP
}

/************************************BEGIN*************************************
*
* Function:    GetMcGroups() class method
*
* Description: Retrieves the currently activated Dune Fabric Multicast Groups
*              from the hardware.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     a list of current active Multicast Groups
*
*************************************END***************************************
*/
CT_FabMcGroupMap & TSPII_SwitchIf::GetMcGroups()
{
    return itsMcGroupsMap;
}

/************************************BEGIN*************************************
*
* Function:    AddMcGroupMember() class method
*
* Description: Adds a single member to a McGroup.
*
* Inputs:
*     theMcId - Mutlicast Group Id
*     theRemShelf - Destination Shelf Id
*     theRemSlot - Destination Slot Id
*     theRemImux - Destination Imux Id
*     theCommitNow - true=commit immediately, false=wait for commit.
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SwitchIf::AddMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow)
{
#ifndef PSOSP
    CT_FabMcGroupMap::iterator  aMcgIter;
    CT_FabMcGroupKey            aKey;
    vector<CT_FabMcMember>      aMembers;
    CT_FabMcMember              aMember;
    vector<CT_FabMcMember>::iterator aMbrIter;
    bool                        aFound = false;

    aKey.Id = theMcId;
    aMcgIter = itsMcGroupsMap.find(aKey);

    if(aMcgIter == itsMcGroupsMap.end())
    {
        // Group doesn't exist - crete it and add the slot
        aMembers.erase(aMembers.begin(), aMembers.end());

        aMember.RemShelf = theRemShelf;
        aMember.RemSlot = theRemSlot;
        aMember.RemImux = theRemImux;

        aMembers.push_back(aMember);
        SetMcGroup(theMcId, aMembers, theCommitNow);
    }
    else
    {
        // Mc Group already exists - Is the slot already in the list
        for(aMbrIter = aMcgIter->second.Members.begin(); aMbrIter != aMcgIter->second.Members.end(); aMbrIter++)
        {
            if((aMbrIter->RemShelf == theRemShelf) &&
               (aMbrIter->RemSlot == theRemSlot) &&
               (aMbrIter->RemImux == theRemImux))
            {
                aFound = true;
                break;
            }
        }

        if(aFound == true)
        {
            // Slot is already in the list - do nothing more
        }
        else
        {
            // The slot is not in this multicast ID's list. So create a new membership list
            // for this multicast ID that includes this slot.
            aMember.RemShelf = theRemShelf;
            aMember.RemSlot = theRemSlot;
            aMember.RemImux = theRemImux;

            aMembers = aMcgIter->second.Members;
            aMembers.push_back(aMember);
            SetMcGroup(aMcgIter->first.Id, aMembers, theCommitNow);
        }
    }
#endif // PSOSP
}

/************************************BEGIN*************************************
*
* Function:    DeleteMcGroupMember() class method
*
* Description: Delete a single member from a Mc Group.
*
* Inputs:
*     theMcId - Multicast Id
*     theRemShelf - Destination Shelf Id
*     theRemSlot - Destination Slot Id
*     theRemImux - Destination Imux Id
*     theCommitNow - true=commit now, false=wait for CommitMcGroups()
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SwitchIf::DeleteMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow)
{
#ifndef PSOSP
    CT_FabMcGroupMap::iterator  aMcgIter;
    CT_FabMcGroupKey            aKey;
    vector<CT_FabMcMember>      aMembers;
    vector<CT_FabMcMember>::iterator aMbrIter;
    bool                        aFound = false;

    aKey.Id = theMcId;
    aMcgIter = itsMcGroupsMap.find(aKey);

    if(aMcgIter == itsMcGroupsMap.end())
    {
        // Group doesn't exist - do nothing
    }
    else
    {
        // Mc Group already exists - Is the slot already in the list
        aMembers = aMcgIter->second.Members;
        for(aMbrIter = aMembers.begin(); aMbrIter != aMembers.end(); aMbrIter++)
        {
            if((aMbrIter->RemShelf == theRemShelf) &&
               (aMbrIter->RemSlot == theRemSlot) &&
               (aMbrIter->RemImux == theRemImux))
            {
                aFound = true;
                break;
            }
        }

        if(aFound == true)
        {
            // Slot is already in the list - remove it - commit immediately
            aMembers.erase(aMbrIter);
            SetMcGroup(aMcgIter->first.Id, aMembers, theCommitNow);
        }
        else
        {
            // Does not exist - do nothing more
        }
    }
#endif // PSOSP
}

/************************************BEGIN*************************************
*
* Function:    WriteObjectBinary() method
*
* Description:
*     Provides the specialized binary based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*
*************************************END***************************************
*/
FC_Stream & TSPII_SwitchIf::WriteObjectBinary(FC_Stream & theStream)
{
    char  aStr[256];
    char  aSubStr[100];
    CT_FabMcGroupMap::iterator aFabIter;
    vector<CT_FabMcMember>::iterator aMemIter;
    uint8 aSlot;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    theStream << static_cast<int>(itsSwitchMode);

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream << static_cast<int>(itsCableLength[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream << itsOsiPortAssignment[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream << itsOsiEnabled[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream << itsOsiPolarity[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream << itsOtherSideHwRevs[aSlot];
    }

    for(aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        theStream << itsSlotEnabled[aSlot];
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////
    // Write out the FAP Multicast table
    theStream << itsMcGroupsMap.size();
    aStr[0] = 0;      // initially null
    aSubStr[0] = 0;   // initially null
    for(aFabIter=itsMcGroupsMap.begin(); aFabIter != itsMcGroupsMap.end(); ++aFabIter)
    {
        // KEY
        sprintf(aSubStr, "%03d,%03d,", aFabIter->first.Id, aFabIter->second.Members.size());
        strcpy(aStr, aSubStr);

        // VAL
        for(aMemIter=aFabIter->second.Members.begin(); aMemIter != aFabIter->second.Members.end(); ++aMemIter)
        {
            // Write out each member of the McGroup as a comma seperated string
            sprintf(aSubStr, "%03d,%03d,%03d,", aMemIter->RemShelf, aMemIter->RemSlot, aMemIter->RemImux);
            strcat(aStr, aSubStr);
        }
        sprintf(aSubStr,"%01d,%01d", aFabIter->second.IsNewOrChanged, aFabIter->second.IsDeleted);
        strcat(aStr, aSubStr);
        theStream << aStr;
    }
#endif // PSOSP

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

/************************************BEGIN*************************************
*
* Function:    ReadObjectBinary() method
*
* Description:
*     Provides the specialized binary based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*
*
*************************************END***************************************
*/
FC_Stream & TSPII_SwitchIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aCount;
    int aMemCount;
    int aTemp;
    uint8 aSlot;
    char aStr[256];
    CT_FabMcMember aMcGroup;

    // Monitoring

    // Configuration
    theStream >> aTemp;
    itsSwitchMode = static_cast<CT_TEL_SwitchMode>(aTemp);
    
    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> itsCableLength[aSlot];
    }

    for (aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> itsOsiPortAssignment[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> itsOsiEnabled[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> itsOsiPolarity[aSlot];
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> itsOtherSideHwRevs[aSlot];
    }

    for(aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        theStream >> itsSlotEnabled[aSlot];
    }

#ifndef PSOSP
    // Read in the FAP Multicast Table
    // first clear out the map
    itsMcGroupsMap.clear();

    // read in  the size of the FAP Multicast Table
    theStream >> aCount;

    // The records must be converted from a char string
    while(aCount > 0)
    {
        CT_FabMcGroupKey   aKey;
        CT_FabMcGroupVal   aVal;

        // Read each Mc record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.Id = static_cast<uint16>(atoi(strtok(aStr, ",")));

        aMemCount = atoi(strtok(NULL, ","));
        while(aMemCount > 0)
        {
            // Read in the Member list for this record
            aMcGroup.RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMcGroup.RemSlot  = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMcGroup.RemImux  = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aVal.Members.push_back(aMcGroup);
            aMemCount--;
        }

        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsMcGroupsMap.insert(CT_FabMcGroupMap::value_type(aKey, aVal));

        aCount--;
    }
#endif // PSOSP

    // Update Sets
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

/************************************BEGIN*************************************
*
* Function:    WriteObject() method
*
* Description:
*     Provides the specialized text based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
ostream & TSPII_SwitchIf::WriteObject(ostream & theStream)
{
    int   aTemp;
    uint8 aSlot;
    char  aStr[256];
    char  aSubStr[100];
    CT_FabMcGroupMap::iterator aFabIter;
    vector<CT_FabMcMember>::iterator aMemIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    aTemp = static_cast<int>(itsSwitchMode);
    theStream << FC_InsertLabelAndVar ("itsSwitchMode", aTemp);

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        sprintf (aStr, "itsCableLength[%d]", aSlot);
        theStream << FC_InsertLabelAndVar (aStr, itsCableLength[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        sprintf (aStr, "itsOsiPortAssignment[%d]", aSlot);
        theStream << FC_InsertLabelAndVar (aStr, itsOsiPortAssignment[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        sprintf (aStr, "itsOsiEnabled[%d]", aSlot);
        theStream << FC_InsertLabelAndVar (aStr, itsOsiEnabled[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        sprintf (aStr, "itsOsiPolarity[%d]", aSlot);
        theStream << FC_InsertLabelAndVar(aStr, itsOsiPolarity[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        sprintf (aStr, "itsOtherSideHwRevs[%d]", aSlot);
        theStream << FC_InsertLabelAndVar(aStr, itsOtherSideHwRevs[aSlot]);
    }

    for(aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        sprintf (aStr, "itsSlotEnabled[%d]", aSlot);
        theStream << FC_InsertLabelAndVar (aStr, itsSlotEnabled[aSlot]);
    }

#ifndef PSOSP
    // Write out the FAP Multicast table
    aTemp = itsMcGroupsMap.size();
    theStream << FC_InsertLabelAndVar ("itsMcGroupsMap.size", aTemp);
    aStr[0] = 0;      // initially null
    aSubStr[0] = 0;   // initially null
    for(aFabIter=itsMcGroupsMap.begin(); aFabIter != itsMcGroupsMap.end(); ++aFabIter)
    {
        // Write out each FAP McGroup record as a comma seperated string
        sprintf(aSubStr, "%03d,%03d,", aFabIter->first.Id, aFabIter->second.Members.size());
        strcpy(aStr, aSubStr);

        for(aMemIter=aFabIter->second.Members.begin(); aMemIter != aFabIter->second.Members.end(); ++aMemIter)
        {
            // Write out each member of the McGroup as a comma seperated string
            sprintf(aSubStr, "%03d,%03d,%03d,", aMemIter->RemShelf, aMemIter->RemSlot, aMemIter->RemImux);
            strcpy(aStr, aSubStr);
        }
        sprintf(aSubStr,"%01d,%01d", aFabIter->second.IsNewOrChanged, aFabIter->second.IsDeleted);
        strcpy(aStr, aSubStr);
        theStream << FC_InsertVar(aStr);
    }
#endif // PSOSP

    return (theStream);
}

/************************************BEGIN*************************************
*
* Function:    ReadObject() method
*
* Description:
*     Provides the specialized text based serialization/deserialization
*     methods required by blackboard.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:

*
*************************************END***************************************
*/
istream & TSPII_SwitchIf::ReadObject(istream & theStream)
{
    int aCount;
    int aMemCount;
    int aTemp;
    uint8 aSlot;
    char aStr[256];
    CT_FabMcMember aMcGroup;

    // Monitoring

    // Configuration
    theStream >> FC_ExtractVar(aTemp);
    itsSwitchMode = static_cast<CT_TEL_SwitchMode>(aTemp);

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> FC_ExtractVar(itsCableLength[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> FC_ExtractVar(itsOsiPortAssignment[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> FC_ExtractVar(itsOsiEnabled[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> FC_ExtractVar(itsOsiPolarity[aSlot]);
    }

    for(aSlot = 1; aSlot <= itsNumOsis; aSlot++)
    {
        theStream >> FC_ExtractVar(itsOtherSideHwRevs[aSlot]);
    }

    for(aSlot = 0; aSlot < itsNumCssSlots; aSlot++)
    {
        theStream >> FC_ExtractVar(itsSlotEnabled[aSlot]);
    }

#ifndef PSOSP
    // Read in the FAP Multicast Table

    // first clear out the map
    itsMcGroupsMap.clear();

    // read in  the size of the FAP Multicast Table
    theStream >> FC_ExtractVar(aCount);

    // The records must be converted from a char string
    while(aCount > 0)
    {
        CT_FabMcGroupKey   aKey;
        CT_FabMcGroupVal   aVal;

        // Read each Mc record as a comma seperated string - write to driver.
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.Id = static_cast<uint16>(atoi(strtok(aStr, ",")));
        aMemCount = atoi(strtok(NULL, ","));
        while(aMemCount > 0)
        {
            // Read in the Member list for this record
            theStream >> FC_ExtractVar(aStr);
            aMcGroup.RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMcGroup.RemSlot  = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMcGroup.RemImux  = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aVal.Members.push_back(aMcGroup);
            aMemCount--;
        }

        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsMcGroupsMap.insert(CT_FabMcGroupMap::value_type(aKey, aVal));

        aCount--;
    }
#endif // PSOSP

    // Update Sets
    RefreshSet();

    return (theStream);
}

/************************************BEGIN*************************************
*
* Function:    Display() class method
*
* Description:
*     The test menu to display the FAB attributes
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SwitchIf::Display(FC_Stream & theStream, int argc, char** argv)
{
    bool aMcxc    = false;
    bool aSummary = false;

    // Update
    UpdateValues();
    RefreshGet();

    if(argc == 0)
    {
        aSummary = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "all") == 0))
    {
        aSummary = true;
        aMcxc  = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "mcxc") == 0))
    {
        aMcxc = true;
    }
    else
    {
        fc_cout << "Usage: tspii display switch <all|mcxc>\n" << endl;
        return;
    }

    theStream << "  Switch Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    if(aSummary)
    {
        theStream << "      itsNumPortShelves           = " << (uint16)itsNumPortShelves       << "\n";
        theStream << "      itsNumCssSlots              = " << (uint16)itsNumCssSlots          << "\n";
        theStream << "      itsNumMcgs                  = " << (uint16)itsNumMcgs              << "\n";
        theStream << "      Switch Mode                 = " << DisplaySwitchMode()             << "\n";
        theStream << "      Slot Enable                 = " << DisplaySlotEnabled()            << "\n";
        theStream << "      Multicast Count             = " << DisplayMcGroups(false)          << "\n";
        theStream << "      Cable Length                = " << DisplayCableLength()            << "\n";
        theStream << "      OSI-Port Shelf Assignment   = " << DisplayOsiPortAssignment()      << "\n";
        theStream << "      OSI Enable                  = " << DisplayOsiEnabled()             << "\n";
        theStream << "      OSI Polarity                = " << DisplayOsiPolarity()            << "\n";
        theStream << "      Other Side Hw Revs          = " << DisplayOtherSideHwRevs()        << "\n";
    }
    if(aMcxc)
    {
        theStream << "      Multicast Groups            = " << DisplayMcGroups(true)           << "\n";
    }

    theStream << "    MONITORING\n";
    TSPII_BaseIf::Display(theStream);
}

/************************************BEGIN*************************************
*
* Function:    Set() class method
*
* Description:
*     Used to modify the Selector attributes via the test menu.
*
* Inputs:
*     Arguments for the configuration attributes
*
* Outputs:
*     Configuration changes
*
* Returns:
*     True/False
*
*************************************END***************************************
*/
bool TSPII_SwitchIf::Set(int argc, char ** argv)
{
    bool printUsage = true;

    if ((argc == 4) && (strcmp(argv[0], "mcgs") == 0))
    {
        char   aOutBuf[256];
        int    aCount;
        uint16 McgId;
        CT_FabMcMember aMember;
        vector<CT_FabMcMember> Members;

        // Read the multicast Id.
        McgId = static_cast<uint16>(atoi(argv[1]));
        // Read the number of members.
        aCount = atoi(argv[2]);
        // Read the Xconn record as a comma seperated string.
        Members.erase(Members.begin(), Members.end());
        strcpy(aOutBuf, argv[3]);
        strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
        while(aCount > 0)
        {
            if(aCount == atoi(argv[2]))
            {
                // First time thru the loop
                aMember.RemShelf = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
            }
            else
            {
                aMember.RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
            }

            aMember.RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMember.RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));

            // Perform validity checks before converting data and adding
            // to membership list. NOTE: An Imux value of 0 is possible
            // if no Imuxs are supported on the module.
            if((aMember.RemShelf > 0) && (aMember.RemShelf <= (itsNumPortShelves+1)) &&
               (aMember.RemSlot > 0) && (aMember.RemSlot <= itsNumPortSlots))
            {
                // Convert it to "0" based numbering
                aMember.RemShelf--;
                aMember.RemSlot--;
                if (aMember.RemImux != 0) // Only convert if Imuxs are supported
                {
                aMember.RemImux--;
                }
                Members.push_back(aMember);
            }
            aCount--;
        }
        if(aCount == 0)
        {
            // Send the request to the Fab
            SetMcGroup(McgId, Members);
            printUsage = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "mcgd") == 0))
    {
        // Read the multicast Id.
        uint16 McgId;

        McgId = static_cast<uint16>(atoi(argv[1]));

        DeleteMcGroup(McgId);
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "mcgda") == 0))
    {
        DeleteAllMcGroups();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "mcgc") == 0))
    {
        CommitMcGroups();
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "mcgam") == 0))
    {
        char   aOutBuf[256];
        uint16 McId;
        uint8  RemShelf;
        uint8  RemSlot;
        uint8  RemImux;
        bool   CommitNow;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,0");    // force some tokens in the string.
        McId = static_cast<uint16>(atoi(strtok(aOutBuf, ",")));
        RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        CommitNow = atoi(strtok(NULL, ",")) ? true : false;

        // Perform validity checks before converting data and adding
        // to membership list. NOTE: An Imux value of 0 is possible
        // if no Imuxs are supported on the module.
        if((RemShelf > 0) && (RemShelf <= (itsNumPortShelves+1)) &&
           (RemSlot > 0) && (RemSlot <= itsNumPortSlots))
        {
            // Convert it to "0" based numbering
            RemShelf--;
            RemSlot--;
            AddMcGroupMember(McId, RemShelf, RemSlot, RemImux, CommitNow);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "mcgdm") == 0))
    {
        char   aOutBuf[256];
        uint16 McId;
        uint8  RemShelf;
        uint8  RemSlot;
        uint8  RemImux;
        bool   CommitNow;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,0");    // force some tokens in the string.
        McId = static_cast<uint16>(atoi(strtok(aOutBuf, ",")));
        RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        CommitNow = atoi(strtok(NULL, ",")) ? true : false;

        // Perform validity checks before converting data and adding
        // to membership list. NOTE: An Imux value of 0 is possible
        // if no Imuxs are supported on the module.
        if((RemShelf > 0) && (RemShelf <= itsNumPortShelves+1) &&
           (RemSlot > 0) && (RemSlot <= itsNumPortSlots))
        {
            // Convert it to "0" based numbering
            RemShelf--;
            RemSlot--;
            DeleteMcGroupMember(McId, RemShelf, RemSlot, RemImux, CommitNow);
            printUsage = false;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "slote") == 0)
    {
        uint8 slot = static_cast<uint8>(atoi(argv[1]));
        if((slot > 0) && (slot <= itsNumCssSlots))
        {
            if(strcmp(argv[2], "on") == 0)
            {
                SetSlotEnabled(slot - 1, true);
                printUsage = false;
            }
            else if(strcmp(argv[2], "off") == 0)
            {
                SetSlotEnabled(slot - 1, false);
                printUsage = false;
            }
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "switch") == 0))
    {
        if(strcmp(argv[1], DISPLAY_SWITCH_MODE(CT_TEL_SwitchMode_Mesh)) == 0)
        {
            SetSwitchMode(CT_TEL_SwitchMode_Mesh);
            printUsage = false;
        }
        else if(strcmp(argv[1], DISPLAY_SWITCH_MODE(CT_TEL_SwitchMode_Cntr_Switch)) == 0)
        {
            SetSwitchMode(CT_TEL_SwitchMode_Cntr_Switch);
            printUsage = false;
        }
        else if(strcmp(argv[1], DISPLAY_SWITCH_MODE(CT_TEL_SwitchMode_End_Switch)) == 0)
        {
            SetSwitchMode(CT_TEL_SwitchMode_End_Switch);
            printUsage = false;
        }
        else if(strcmp(argv[1], DISPLAY_SWITCH_MODE(CT_TEL_SwitchMode_Repeater)) == 0)
        {
            SetSwitchMode(CT_TEL_SwitchMode_Repeater);
            printUsage = false;
        }
        else if(strcmp(argv[1], DISPLAY_SWITCH_MODE(CT_TEL_SwitchMode_None)) == 0)
        {
            SetSwitchMode(CT_TEL_SwitchMode_None);
            printUsage = false;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "cablelen") == 0)
    {
        uint8 osi = static_cast<uint8>(atoi(argv[1]));

        if (strcmp(argv[2],"10") == 0)
        {        
            SetCableLength(osi, CT_CABLELENGTH_10);
            printUsage = false;
        } 
        else if (strcmp(argv[2],"20") == 0)
        {        
            SetCableLength(osi, CT_CABLELENGTH_20);
            printUsage = false;
        } 
        else if (strcmp(argv[2],"80") == 0)
        {        
            SetCableLength(osi, CT_CABLELENGTH_80);
            printUsage = false;
        } 
    }
    else if ((argc == 3) && strcmp(argv[0], "osiport") == 0)
    {
        uint8 osi = static_cast<uint8>(atoi(argv[1]));
        CT_ShelfId port = static_cast<CT_ShelfId>(atoi(argv[2]));

        SetOsiPortAssignment(osi, port);
        printUsage = false;
    }
    else if ((argc == 3) && strcmp(argv[0], "osie") == 0)
    {
        uint8 osi = static_cast<uint8>(atoi(argv[1]));

        if (strcmp(argv[2], "on") == 0)
        {
            SetOsiEnabled(osi,true);
            printUsage = false;
        }
        else if (strcmp(argv[2], "off") == 0)
        {
            SetOsiEnabled(osi,false);
            printUsage = false;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "osipolar") == 0)
    {
        uint8 osi = static_cast<uint8>(atoi(argv[1]));

        if (strcmp(argv[2], "invert") == 0)
        {
            InvertOsiPolarity(osi,true);
            printUsage = false;
        }
        else if (strcmp(argv[2], "norm") == 0)
        {
            InvertOsiPolarity(osi,false);
            printUsage = false;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "oshwrev") == 0)
    {   // set other side hw revision for specified osi port
        uint8 osi = static_cast<uint8>(atoi(argv[1]));
        if (osi <= itsNumOsis)
        {   // hw rev may be up to 4 ascii chars
            char hwrev[5];
            strncpy (hwrev, argv[2], 4);
            hwrev[4] = 0; // to ensure null termination;
#ifndef PSOSP
            std::string s1 = hwrev;
            SetOtherSideHwRev (osi, s1);
#endif
            printUsage = false;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }

    if (printUsage)
    {
        // Convert the integers to strings to get around the C++ auto conversion issues.
        char aNumCssSlotsStr[10];
        char aNumMcgsStr[10];
        char aNumPortShelvesStr[10];
        char aNumOsisStr[10];
        sprintf(aNumCssSlotsStr, "%d", itsNumCssSlots);
        sprintf(aNumMcgsStr, "%d", itsNumMcgs);
        sprintf(aNumPortShelvesStr, "%d", itsNumPortShelves);
        sprintf(aNumOsisStr, "%d", itsNumOsis);

        fc_cout << "    mcgs        <id> <mbrcnt> <dshelf,dslot,dimux,....> \n"
                   "                  id=1-" << aNumMcgsStr << ", mbrcnt=0-255, dshelf=1-"
                                             << aNumPortShelvesStr << "\n"
                   "    mcgd        <id> \n"
                   "    mcgda        \n"
                   "    mcgc         \n"
                   "    mcgam         <mcid,rshelf,rslot,rimux,commit>\n"
                   "    mcgdm         <mcid,rshelf,rslot,rimux,commit>\n"
                   "                   mcid, rshelf=1-N,rslot=1-N,rimux=1L-2P,mcid,commit=0,1\n"
                   "----------------------------------------------------------\n"
                   "    slote       <slot=1-" << aNumCssSlotsStr << "> <on|off>\n"
                   "----------------------------------------------------------\n"
                   "    switch      <None|CtrSwitch|EndSwitch|Repeater>\n"
                   "----------------------------------------------------------\n"
                   "    fabinit     <on|off>\n"
                   "----------------------------------------------------------\n"
                   "    cablelen    <osi=1-"<< aNumOsisStr << "> <10,20,80>\n"
                   "----------------------------------------------------------\n"  
                   "    osiport     <osi=1-"<< aNumOsisStr << "> <portshelf>\n"
                   "----------------------------------------------------------\n"  
                   "    osise       <osi=1-"<< aNumOsisStr << "> <on|off>\n"
                   "----------------------------------------------------------\n"  
                   "    osispolar   <osi=1-"<< aNumOsisStr << "> <invert|norm>\n"
                   "----------------------------------------------------------\n"  
                   "    oshwrev     <osi=1-"<< aNumOsisStr << "> <OtherSideHwRev>\n"
                   "----------------------------------------------------------\n"  
            << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_SwitchIf::Display(FC_Stream & theStream)
{
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayMcGroups(bool printDetail)
{
    char    aBuf[80];
    string  aStr;
    CT_FabMcGroupMap::iterator  aFabIter;
    vector<CT_FabMcMember>::iterator aIter;

    sprintf(aBuf, "%d <mcid: dshelf,dslot,dimux, . . . isNewChanged isDeleted>\n", itsMcGroupsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aFabIter=itsMcGroupsMap.begin(); aFabIter != itsMcGroupsMap.end(); ++aFabIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%05d: ", aFabIter->first.Id);
            aStr += aBuf;
            for(aIter = aFabIter->second.Members.begin(); aIter != aFabIter->second.Members.end(); aIter++)
            {
                sprintf(aBuf, "%03d,%03d,%1d ", aIter->RemShelf + 1, aIter->RemSlot + 1, aIter->RemImux + 1);
                aStr += aBuf;
            }
            sprintf(aBuf, "- %1d %1d\n", aFabIter->second.IsNewOrChanged, aFabIter->second.IsDeleted);
            aStr += aBuf;
        }
    }
#endif // PSOSP

    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplaySwitchMode()
{
    char aBuf[20];
    string  aStr;

    sprintf(aBuf, "%s", DISPLAY_SWITCH_MODE(itsSwitchMode));
    aStr = aBuf;
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplaySlotEnabled()
{
    int     i;
    char    aBuf[80];
    string  aStr;

    for(i = 0; i < itsNumCssSlots; i++)
    {
        sprintf(aBuf, "%s,", itsSlotEnabled[i] ? "on" : "off");
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayOsiEnabled()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 1; i <= itsNumOsis; i++)
    {
        sprintf(aBuf, "%s,", itsOsiEnabled[i] ? "on" : "off");
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayOsiPolarity()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 1; i <= itsNumOsis; i++)
    {
        sprintf(aBuf, "%s,", itsOsiPolarity[i] ? "invert" : "norm");
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayOsiPortAssignment()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 1; i <= itsNumOsis; i++)
    {
        sprintf(aBuf, "%d,", itsOsiPortAssignment[i]);
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayCableLength()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 1; i <= itsNumOsis; i++)
    {
        sprintf(aBuf, "%d,", itsCableLength[i]);
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SwitchIf::DisplayOtherSideHwRevs()
{
    string  aStr;

    for(uint i = 1; i <= itsNumOsis; i++)
    {
        string tempStr (itsOtherSideHwRevs[i]);
        if (tempStr.length() > 0)
            aStr += tempStr;
        else
            aStr += "0";

        if (i < itsNumOsis)
            aStr += ", ";
    }

    return aStr;
}

// eof
