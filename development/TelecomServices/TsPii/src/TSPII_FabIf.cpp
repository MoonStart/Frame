/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_FabIf.cpp
* Type:    C++ source
* Author:  Denham Reynolds - September 2008
* Description:
*     Definition of the class TSPII_FabIf which models the simulation generic
*     Fab (Dune Fabric) Interface entity.
*
*
*************************************END***************************************
*/
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_FabIf.h"
#include <strstream>
#include "TsPii/TSPII_Region.h"
#include "TsPii/TSPII_SubApplication.h"
#include <string.h>

/************************************BEGIN*************************************
*
* Function:    TSPII_FabIf constructor
*
* Description:
*     TSPII_FabIfIf class constructor
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
TSPII_FabIf::TSPII_FabIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, uint16 theNumStss, bool theForceShelf, uint16 theNumMcgs, uint16 theNumConIds, bool theIsConMode) :
    TSPII_BaseIf(theDefault)
{
    int aSlot;
    itsIsConMode = theIsConMode;
    itsNumShelves = theNumShelves;
    itsNumSlots = theNumSlots;
    itsNumImuxs = theNumImuxs;
    itsNumStss = theNumStss;
    itsForceShelf = theForceShelf;
    itsNumMcgs = theNumMcgs;
    itsNumConIds = theNumConIds;
    itsSlotEnabled = static_cast<bool *>(malloc(itsNumSlots * sizeof(bool)));
    itsEdgeEgressXconnUsage = static_cast<bool *>(malloc(itsNumStss * sizeof(bool)));

    itsSlotTrafficType = static_cast<TSPII_FabIf_TrafficType **>(malloc(itsNumSlots * sizeof(TSPII_FabIf_TrafficType*)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotTrafficType[aSlot] = (TSPII_FabIf_TrafficType *)(malloc(2 * sizeof(TSPII_FabIf_TrafficType)));  // local - remote
    }

    itsSlotSpeed = (CT_TEL_LinkRate **)(malloc(itsNumSlots * sizeof(CT_TEL_LinkRate *)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotSpeed[aSlot] = (CT_TEL_LinkRate *)(malloc(2 * sizeof(CT_TEL_LinkRate)));  // local - remote
    }

    itsSlotFecEnabled = (bool **)(malloc(itsNumSlots * sizeof(bool *)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotFecEnabled[aSlot] = (bool *)(malloc(2 * sizeof(bool)));   // local - remote
    }

    itsSlotFecInitComplete = (bool **)(malloc(itsNumSlots * sizeof(bool *)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotFecInitComplete[aSlot] = (bool *)(malloc(2 * sizeof(bool)));   // local - remote
    }

    itsSlotSpeedInitComplete = (bool **)(malloc(itsNumSlots * sizeof(bool *)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotSpeedInitComplete[aSlot] = (bool *)(malloc(2 * sizeof(bool)));   // local - remote
    }

    itsMcgInitComplete = static_cast<bool *>(malloc(itsNumMcgs * sizeof(bool *)));

    itsSlotFeInitComplete = (bool **)(malloc(itsNumSlots * sizeof(bool *)));
    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotFeInitComplete[aSlot] = (bool *)(malloc(2 * sizeof(bool)));   // local - remote
    }


    Reset();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_FabIf destructor
*
* Description:
*     TSPII_FabIf class destructor
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
TSPII_FabIf::~TSPII_FabIf()
{
    uint8 aSlot;

    free(itsSlotEnabled);
    free(itsEdgeEgressXconnUsage);

    for (aSlot=0; aSlot < itsNumSlots; aSlot++)
    {
        free(itsSlotTrafficType[aSlot]);
        free(itsSlotSpeed[aSlot]);
        free(itsSlotFecEnabled[aSlot]);
        free(itsSlotFecInitComplete[aSlot]);
        free(itsSlotSpeedInitComplete[aSlot]);
        free(itsSlotFeInitComplete[aSlot]);
    }
    free(itsSlotTrafficType);
    free(itsSlotSpeed);
    free(itsSlotFecEnabled);
    free(itsSlotFecInitComplete);
    free(itsSlotSpeedInitComplete);
    free(itsSlotFeInitComplete);

    free(itsMcgInitComplete);
}

/************************************BEGIN*************************************
*
* Function:    RefreshGet() class method
*
* Description:
*     Used to refresh the FabIf entity attributes.
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
void TSPII_FabIf::RefreshGet()
{
    uint8 aSlot;

    // Configuration attributes
    itsSwitchMode = GetSwitchMode();
    itsSwitchDomain = GetSwitchDomainMode();

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotEnabled[aSlot] = GetSlotEnabled(aSlot);
        itsSlotTrafficType[aSlot][0] = GetSlotTrafficType(aSlot, false);   // local
        itsSlotTrafficType[aSlot][1] = GetSlotTrafficType(aSlot, true);    // remote
        itsSlotSpeed[aSlot][0] = GetSlotSpeed(aSlot, false);   // local
        itsSlotSpeed[aSlot][1] = GetSlotSpeed(aSlot, true);    // remote
        itsSlotFecEnabled[aSlot][0] = GetSlotFecEnabled(aSlot, false);   // local
        itsSlotFecEnabled[aSlot][1] = GetSlotFecEnabled(aSlot, true);    // remote
    }

    // Update the EdgeEgressXconns table.
    itsEdgeEgressXconnsMap = GetEdgeEgressXconns();          // get snapshot

    // Update the EdgeIngressXconns table.
    itsEdgeIngressXconnsMap = GetEdgeIngressXconns();        // get snapshot

    // Update the FapMcGroups table.
    itsMcGroupsMap = GetMcGroups();
}

/************************************BEGIN*************************************
*
* Function:    RefreshSet() class method
*
* Description:
*     Used to refresh the FabIf configuration
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
void TSPII_FabIf::RefreshSet()
{
    TSPII_FabIfEdgeEgrXcMap::iterator edgeEgrXcIter;
    TSPII_FabIfEdgeIngXcMap::iterator edgeIngXcIter;
    CT_FabMcGroupMap::iterator fapMcIter;
    uint8 aSlot;

    // default Backplane mode
    SetSwitchMode(itsSwitchMode);
    SetSwitchDomainMode(itsSwitchDomain);

    // write out the Backplane slot enables
    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        SetSlotEnabled(aSlot, itsSlotEnabled[aSlot]);
        SetSlotTrafficType(aSlot, false, itsSlotTrafficType[aSlot][0]);   // local
        SetSlotTrafficType(aSlot, true, itsSlotTrafficType[aSlot][1]);    // remote
        SetSlotSpeed(aSlot, false, itsSlotSpeed[aSlot][0]);   // local
        SetSlotSpeed(aSlot, true, itsSlotSpeed[aSlot][1]);    // remote
        SetSlotFecEnabled(aSlot, false, itsSlotFecEnabled[aSlot][0]);   // local
        SetSlotFecEnabled(aSlot, true, itsSlotFecEnabled[aSlot][1]);    // remote
    }

#ifndef PSOSP
     // write out the EDGE Egress Xconns
    for(edgeEgrXcIter = itsEdgeEgressXconnsMap.begin();
        edgeEgrXcIter != itsEdgeEgressXconnsMap.end();
        edgeEgrXcIter++)
    {
        AddEdgeEgressXconn(edgeEgrXcIter->first.SrcShelf,
                           edgeEgrXcIter->first.SrcSlot,
                           edgeEgrXcIter->first.SrcSts,
                           edgeEgrXcIter->first.ConId,
                           edgeEgrXcIter->first.DstSts);
    }

     // write out the EDGE Ingress Xconns
    for(edgeIngXcIter = itsEdgeIngressXconnsMap.begin();
        edgeIngXcIter != itsEdgeIngressXconnsMap.end();
        edgeIngXcIter++)
    {
        AddEdgeIngressXconn(edgeIngXcIter->first.SrcSts,
                            edgeIngXcIter->second.IsMc,
                            edgeIngXcIter->second.McId,
                            edgeIngXcIter->second.RemShelf,
                            edgeIngXcIter->second.RemSlot,
                            edgeIngXcIter->second.RemImux,
                            edgeIngXcIter->second.ConId,
                            false,
                            edgeIngXcIter->second.RemCardType);
    }

     // write out the FAP Multicast groups
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
*     Used to reset the FabIf entity attributes to a default state.
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
void TSPII_FabIf::Reset()
{
    uint8 aSlot;
    uint  aMcg;

    TSPII_BaseIf::Reset();

    itsSwitchMode = CT_TEL_SwitchMode_None;
    itsSwitchDomain = CT_SWITCHDOMAINMODE_UNKNOWN;

    itsPSInitComplete = false;
    itsPSCardInShelf = false;
    itsFabInitComplete = false;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        itsSlotEnabled[aSlot] = false;
        itsSlotTrafficType[aSlot][0] = TSPII_FabIf_Traffic_Unknown; // local
        itsSlotTrafficType[aSlot][1] = TSPII_FabIf_Traffic_Unknown; // remote
        itsSlotSpeed[aSlot][0] = CT_TEL_LinkRateNone;   // local
        itsSlotSpeed[aSlot][1] = CT_TEL_LinkRateNone;   // remote
        itsSlotFecEnabled[aSlot][0] = false;   // local
        itsSlotFecEnabled[aSlot][1] = false;   // remote
        itsSlotFecInitComplete[aSlot][0] = false;   // local
        itsSlotFecInitComplete[aSlot][1] = false;   // remote
        itsSlotSpeedInitComplete[aSlot][0] = false;   // local
        itsSlotSpeedInitComplete[aSlot][1] = false;   // remote
        itsSlotFeInitComplete[aSlot][0] = false;   // local
        itsSlotFeInitComplete[aSlot][1] = false;   // remote
    }

    itsEdgeEgressXconnsMap.clear();
    itsEdgeIngressXconnsMap.clear();

    itsTopologyMap.erase(itsTopologyMap.begin(),
                              itsTopologyMap.end());

    itsMcGroupsMap.clear();

    for( aMcg = 0; aMcg < itsNumMcgs; aMcg++ )
    {
        itsMcgInitComplete[aMcg] = false;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetSlotTrafficType()
*
* Description: Set the traffic type on the specified slot
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*     theType - the requested traffic type
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_FabIf::SetSlotTrafficType(uint8 theSlot, bool isRemote, TSPII_FabIf_TrafficType theType)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            itsSlotTrafficType[theSlot][1] = theType;   // remote
        }
        else
        {
            itsSlotTrafficType[theSlot][0] = theType;   // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::SetSlotTrafficType invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetSlotTrafficType()
*
* Description: Retrieve the traffic type for specified slot
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*
* Outputs:
*     None
*
* Returns:
*     theTrafficType
*
*************************************END***************************************
*/
TSPII_FabIf_TrafficType TSPII_FabIf::GetSlotTrafficType(uint8 theSlot, bool isRemote)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            return itsSlotTrafficType[theSlot][1];   // remote
        }
        else
        {
            return itsSlotTrafficType[theSlot][0];   // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::GetSlotTrafficType invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return TSPII_FabIf_Traffic_Unknown;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetSlotSpeed()
*
* Description: Sets the link speeds for the specified slot
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*     theSpeed - the requested link speed
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_FabIf::SetSlotSpeed(uint8 theSlot, bool isRemote, CT_TEL_LinkRate theSpeed)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            itsSlotSpeed[theSlot][1] = theSpeed;   // remote
        }
        else
        {
            itsSlotSpeed[theSlot][0] = theSpeed;   // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::SetSlotSpeed invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetSlotSpeed()
*
* Description: Retireves the link speed on specified slot.
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*
* Outputs:
*     None
*
* Returns:
*     LinkRate - CT_TEL_LinkRateXXX -
*
*************************************END***************************************
*/
CT_TEL_LinkRate TSPII_FabIf::GetSlotSpeed(uint8 theSlot, bool isRemote)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            return itsSlotSpeed[theSlot][1];   // remote
        }
        else
        {
            return itsSlotSpeed[theSlot][0];   // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::GetSlotSpeed invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return CT_TEL_LinkRateNone;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetSlotFecEnabled()
*
* Description: Set the FEC enable on the specified link
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*     theEnabled - false = disabled, true = enabled
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_FabIf::SetSlotFecEnabled(uint8 theSlot, bool isRemote, bool theEnabled)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            itsSlotFecEnabled[theSlot][1] = theEnabled;    // remote
        }
        else
        {
            itsSlotFecEnabled[theSlot][0] = theEnabled;    // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::SetSlotFecEnabled invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetSlotFecEnabled()
*
* Description:
*
* Inputs:
*     theSlot - specified slot
*     isRemote - false = local, true = remote
*
* Outputs:
*     None
*
* Returns:
*     false = disabled, true = enabled
*
*************************************END***************************************
*/
bool TSPII_FabIf::GetSlotFecEnabled(uint8 theSlot, bool isRemote)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        if(isRemote == true)
        {
            return itsSlotFecEnabled[theSlot][1];    // remote
        }
        else
        {
            return itsSlotFecEnabled[theSlot][0];    // local
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::GetSlotFecEnabled invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return false;
    }
}

/************************************BEGIN*************************************
*
* Function:    SetSwitchMode() class method
*
* Description: Sets the mode that the backplane is to operate in.
*
* Inputs:
*     theMode - which backplane mode to set.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::SetSwitchMode(CT_TEL_SwitchMode theMode)
{
    itsSwitchMode = theMode;
}

/************************************BEGIN*************************************
*
* Function:    GetSwitchMode() class method
*
* Description: Gets the mode that the backplane is configured for
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     theMode - the requested mode of operation.
*
*************************************END***************************************
*/
CT_TEL_SwitchMode TSPII_FabIf::GetSwitchMode()
{
    return itsSwitchMode;
}

/************************************BEGIN*************************************
*
* Function:    SetSwitchDomainMode() class method
*
* Description: Sets the mode that the system is operating in.
*
* Inputs:
*     theSwitchDomain - System mode.
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::SetSwitchDomainMode(CT_SwitchDomainMode theSwitchDomain)
{
    itsSwitchDomain = theSwitchDomain;
}

/************************************BEGIN*************************************
*
* Function:    GetSwitchDomainMode() class method
*
* Description: Gets the mode that the System is operating in
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     theMode - the requested mode of operation.
*
*************************************END*************************************** 
*/ 
CT_SwitchDomainMode TSPII_FabIf::GetSwitchDomainMode()
{
    return itsSwitchDomain;
}

/************************************BEGIN*************************************
*
* Function:    SetSlotEnabled() class method
*
* Description: Sets the Activate or deactivate state of the FAP20X links going
*              to that backplane slot.
*
* Inputs:
*     theSlot - the Shelf backplane slot to be enabled/disabled (0-15)
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
void TSPII_FabIf::SetSlotEnabled(uint8 theSlot, bool theEnable)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        itsSlotEnabled[theSlot] = theEnable;
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::SetSlotEnabled invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
}

/************************************BEGIN*************************************
*
* Function:    GetSlotEnabled() class method
*
* Description: Gets the Enabled state of the FAP20X links going
*              to that backplane slot.
*
* Inputs:
*     theSlot - the backplane slot being queried (0-15)
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
bool TSPII_FabIf::GetSlotEnabled(uint8 theSlot)
{
    char aErrBuf[128];

    if(theSlot < itsNumSlots)
    {
        return itsSlotEnabled[theSlot];
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::GetSlotEnabled invalid slot: %d, %d", theSlot, itsNumSlots);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        return false;
    }
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
void TSPII_FabIf::SetTopologyMap(vector<uint8> theTopology)
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
vector<uint8> TSPII_FabIf::GetTopologyMap()
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
void TSPII_FabIf::SetMcGroup(uint16 theMcId, vector<CT_FabMcMember> theMembers, bool theCommitNow)
{
#ifndef PSOSP
    char aErrBuf[128];
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
        sprintf(aErrBuf, "TSPII_FabIf::SetMcGroup invalid McId: %d, %d", theMcId, itsNumMcgs);
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
void TSPII_FabIf::DeleteMcGroup(uint16 theMcId, bool theCommitNow)
{
#ifndef PSOSP
    char aErrBuf[128];
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
        sprintf(aErrBuf, "TSPII_FabIf::DeleteMcGroup invalid McId: %d, %d", theMcId, itsNumMcgs);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
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
void TSPII_FabIf::DeleteAllMcGroups(bool theCommitNow)
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
void TSPII_FabIf::CommitMcGroups()
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
#endif
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
CT_FabMcGroupMap & TSPII_FabIf::GetMcGroups()
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
void TSPII_FabIf::AddMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow)
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
#endif
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
void TSPII_FabIf::DeleteMcGroupMember(uint16 theMcId, uint8 theRemShelf, uint8 theRemSlot, uint8 theRemImux, bool theCommitNow)
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
#endif
}

/************************************BEGIN*************************************
*
* Function:    AddEdgeEgressXconn() class method
*
* Description: Sets up a new EDGE association of how to route Egress traffic.
*
* Inputs:
*     theSrcShelf - the Source Shelf (0 - itsNumShelves)
*
*     theSrcSlot - the Source Slot (0 - itsNumSlots)
*
*     theSrcSts - the Source Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
*     theConId - the Connection Id (0-32767)
*
*     theDstSts - the Destination Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::AddEdgeEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint16 theSrcSts, uint16 theConId, uint16 theDstSts)
{
#ifndef PSOSP
    char  aErrBuf[128];
    TSPII_FabIfEdgeEgrXcKey   aKey;
    TSPII_FabIfEdgeEgrXcVal   aVal;
    TSPII_FabIfEdgeEgrXcMap::iterator  edgeEgrXcIter;

    if(theSrcShelf < itsNumShelves)
    {
        if(theSrcSlot < itsNumSlots)
        {
            if((theSrcSts < itsNumStss) && (theDstSts < itsNumStss))
            {
                if(theConId < itsNumConIds)
                {
                    aKey.SrcShelf = theSrcShelf;
                    aKey.SrcSlot  = theSrcSlot;
                    aKey.SrcSts   = theSrcSts;
                    aKey.ConId    = theConId;
                    aKey.DstSts   = theDstSts;

                    aVal.DummyVal = 0;

                    // Search for this element
                    edgeEgrXcIter = itsEdgeEgressXconnsMap.find(aKey);

                    // If element already exists, check if its value is changing
                    if (edgeEgrXcIter != itsEdgeEgressXconnsMap.end())
                    {
                        if (edgeEgrXcIter->second == aVal)
                        {
                            edgeEgrXcIter->second.IsDeleted      = false;
                        }
                        else
                        {
                            edgeEgrXcIter->second                = aVal;
                            edgeEgrXcIter->second.IsNewOrChanged = true;
                            edgeEgrXcIter->second.IsDeleted      = false;
                        }
                    }
                    // Else element doesn't exist, so insert it
                    else
                    {
                        aVal.IsNewOrChanged = true;
                        aVal.IsDeleted      = false;
                        itsEdgeEgressXconnsMap.insert(TSPII_FabIfEdgeEgrXcMap::value_type(aKey, aVal));
                    }
                }
                else
                {
                    sprintf(aErrBuf, "TSPII_FabIf::AddEdgeEgressXconn invalid ConId: %d, %d", theConId, itsNumConIds);
                    FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
                }
            }
            else
            {
                sprintf(aErrBuf, "TSPII_FabIf::AddEdgeEgressXconn invalid SrcSts or DstSts: %d, %d, %d", theSrcSts, theDstSts, itsNumStss);
                FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
            }
        }
        else
        {
            sprintf(aErrBuf, "TSPII_FabIf::AddEdgeEgressXconn invalid SrcSlot: %d, %d", theSrcSlot, itsNumSlots);
            FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::AddEdgeEgressXconn invalid SrcShelf: %d, %d", theSrcShelf, itsNumShelves);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    DeleteEdgeEgressXconn() class method
*
* Description: Tears down a EDGE association of how to route Egress traffic.
*              There could be more than one entry so do the whole table.
*
* Inputs:
*     theSrcShelf - the Source Shelf (0 - itsNumShelves)
*
*     theSrcSlot - the Source Slot (0 - itsNumSlots)
*
*     theSrcSts - the Source Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
*     theConId - the Connection Id (0-32767)
*
*     theDstSts - the Destination Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::DeleteEdgeEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint16 theSrcSts, uint16 theConId, uint16 theDstSts)
{
#ifndef PSOSP
    char aErrBuf[128];
    TSPII_FabIfEdgeEgrXcKey   aKey;
    TSPII_FabIfEdgeEgrXcMap::iterator edgeEgrXcIter;

    if(theSrcShelf < itsNumShelves)
    {
        if(theSrcSlot < itsNumSlots)
        {
            if((theSrcSts < itsNumStss) && (theDstSts < itsNumStss))
            {
                if(theConId < itsNumConIds)
                {
                    aKey.SrcShelf = theSrcShelf;
                    aKey.SrcSlot  = theSrcSlot;
                    aKey.SrcSts   = theSrcSts;
                    aKey.ConId    = theConId;
                    aKey.DstSts   = theDstSts;

                    // Search for this element
                    edgeEgrXcIter = itsEdgeEgressXconnsMap.find(aKey);

                    if (edgeEgrXcIter != itsEdgeEgressXconnsMap.end())
                    {
                        // element exsists - mark for deletion
                        edgeEgrXcIter->second.IsDeleted = true;
                    }
                    else
                    {
                        // Element doesn't exist, so ignore this request
                    }
                }
                else
                {
                    sprintf(aErrBuf, "TSPII_FabIf::DeleteEdgeEgressXconn invalid ConId: %d, %d", theConId, itsNumConIds);
                    FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
                }
            }
            else
            {
                sprintf(aErrBuf, "TSPII_FabIf::DeleteEdgeEgressXconn invalid SrcSts or DstSts: %d, %d, %d", theSrcSts, theDstSts, itsNumStss);
                FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
            }
        }
        else
        {
            sprintf(aErrBuf, "TSPII_FabIf::DeleteEdgeEgressXconn invalid SrcSlot: %d, %d", theSrcSlot, itsNumSlots);
            FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::DeleteEdgeEgressXconn invalid SrcShelf: %d, %d", theSrcShelf, itsNumShelves);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    DeleteAllEdgeEgressXconns() class method
*
* Description: Tears down all EDGE association of how to route Egress traffic.
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
void TSPII_FabIf::DeleteAllEdgeEgressXconns()
{
#ifndef PSOSP
    TSPII_FabIfEdgeEgrXcMap::iterator edgeEgrXcIter;

    // Mark all connections as deleted in the Xconn table
    for(edgeEgrXcIter = itsEdgeEgressXconnsMap.begin();
        edgeEgrXcIter != itsEdgeEgressXconnsMap.end();
        edgeEgrXcIter++)
    {
        edgeEgrXcIter->second.IsDeleted = true;
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    CommitEdgeEgressXconns() class method
*
* Description:  Commits all Egress Xconns to the TOH chip
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
void TSPII_FabIf::CommitEdgeEgressXconns(bool theForceHw)
{
#ifndef PSOSP
    TSPII_FabIfEdgeEgrXcMap::iterator  edgeEgrXcIter;

    // Commit all connections stored in the Xconn table
    for(edgeEgrXcIter = itsEdgeEgressXconnsMap.begin();
        edgeEgrXcIter != itsEdgeEgressXconnsMap.end(); )
    {
        if(edgeEgrXcIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            edgeEgrXcIter = itsEdgeEgressXconnsMap.erase(edgeEgrXcIter);
#endif
        }
        else if (edgeEgrXcIter->second.IsNewOrChanged)
        {
            // clear the flag since we are committing the changes
            edgeEgrXcIter->second.IsNewOrChanged = false;
            edgeEgrXcIter++;
        }
        else
        {
            // No change on this one.
            edgeEgrXcIter++;
        }
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    GetEdgeEgressXconns() class method
*
* Description: Retrieves the currently activated EDGE Egress Xconns from
*              the hardware.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     a list of current Edge Egress Xconns
*
*************************************END***************************************
*/
TSPII_FabIfEdgeEgrXcMap& TSPII_FabIf::GetEdgeEgressXconns()
{
    return itsEdgeEgressXconnsMap;
}

/************************************BEGIN*************************************
*
* Function:    AddEdgeIngressXconn() class method
*
* Description: Sets up a new EDGE association of how to route Ingress traffic to FAP.
*
* Inputs:
*     theSrcSts - the Source Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
*     theIsMc - false = unicast, true = multicast.
*
*     theMcId - the Mutlicast ID (1-16383). Only used if theIfMc = true
*
*     theRemShelf - the Destination Shelf (0 - itsNumShelves). Only used if theIsMc = false
*
*     theRemSlot - the Destination Slot (0 - itsNumSlots). Only used if theIsMc = false
*
*     theRemImux - the Destination IMUX (0 = IMUXL, 1 = IMUXP). Only used if theIsMc = false
*
*     theConId - the Connection Id (0-32767)
*
*     theIsBypass - immediate commit flag (true=commit immediately, false=don't commit immediately
*                   Wait until next CommitEdgeIngressXconns().
* 
*     theRemCardType - the Remote Card Type - CT_CardTypes.h
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::AddEdgeIngressXconn(uint16 theSrcSts, bool theIsMc,
                                      uint16 theMcId, uint8 theRemShelf,
                                      uint8 theRemSlot, uint8 theRemImux,
                                      uint16 theConId, bool theIsBypass,
                                      uint8 theRemCardType)
{
#ifndef PSOSP
    char aErrBuf[128];
    TSPII_FabIfEdgeIngXcKey   aKey;
    TSPII_FabIfEdgeIngXcVal   aVal;
    TSPII_FabIfEdgeIngXcMap::iterator edgeIngXcIter;

    if(theSrcSts < itsNumStss)
    {
        if(theMcId < itsNumMcgs)
        {
            if(theRemShelf < itsNumShelves)
            {
                if(theRemSlot < itsNumSlots)
                {
                    if(theRemImux < itsNumImuxs)
                    {
                        if(theConId < itsNumConIds)
                        {
                            aKey.SrcSts   = theSrcSts;

                            aVal.IsMc     = theIsMc;
                            aVal.McId     = theMcId;
                            aVal.RemShelf = theRemShelf;
                            aVal.RemSlot  = theRemSlot;
                            aVal.RemImux  = theRemImux;
                            aVal.RemCardType = theRemCardType;
                            aVal.ConId    = theConId;
                            aVal.IsBypass = theIsBypass;

                            // Search for this element
                            edgeIngXcIter = itsEdgeIngressXconnsMap.find(aKey);

                            // If element already exists, check if its value is changing
                            if (edgeIngXcIter != itsEdgeIngressXconnsMap.end())
                            {
                                if (edgeIngXcIter->second == aVal)
                                {
                                    edgeIngXcIter->second.IsDeleted      = false;
                                }
                                else
                                {
                                    edgeIngXcIter->second                = aVal;
                                    edgeIngXcIter->second.IsNewOrChanged = true;
                                    edgeIngXcIter->second.IsDeleted      = false;
                                }
                            }
                            // Else element doesn't exist, so insert it
                            else
                            {
                                aVal.IsNewOrChanged = true;
                                aVal.IsDeleted      = false;
                                itsEdgeIngressXconnsMap.insert(TSPII_FabIfEdgeIngXcMap::value_type(aKey, aVal));
                            }
                        }
                        else
                        {
                            sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid ConId: %d, %d", theConId, itsNumConIds);
                            FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
                        }
                    }
                    else
                    {
                        sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid Imux: %d, %d", theRemImux, itsNumImuxs);
                        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
                    }
                }
                else
                {
                    sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid RemSlot: %d, %d", theRemSlot, itsNumSlots);
                    FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
                }
            }
            else
            {
                sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid RemShelf: %d, %d", theRemShelf, itsNumShelves);
                FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
            }
        }
        else
        {
            sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid McId: %d, %d", theMcId, itsNumMcgs);
            FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::AddEdgeIngressXconn invalid SrcSts: %d, %d", theSrcSts, itsNumStss);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    DeleteEdgeIngressXconn() class method
*
* Description: Tears down a EDGE association of how to route Ingress traffic to the FAP.
*
* Inputs:
*     theSrcSts - the Source Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::DeleteEdgeIngressXconn(uint16 theSrcSts)
{
#ifndef PSOSP
    char aErrBuf[128];
    TSPII_FabIfEdgeIngXcKey   aKey;
    TSPII_FabIfEdgeIngXcMap::iterator edgeIngXcIter;

    if(theSrcSts < itsNumStss)
    {
        aKey.SrcSts = theSrcSts;

        // Search for this element
        edgeIngXcIter = itsEdgeIngressXconnsMap.find(aKey);

        if(edgeIngXcIter != itsEdgeIngressXconnsMap.end())
        {
            // element exsists - mark for deletion
            edgeIngXcIter->second.IsDeleted = true;
        }
        else
        {
            // Element doesn't exist, so ignore this request
        }
    }
    else
    {
        sprintf(aErrBuf, "TSPII_FabIf::DeleteEdgeIngressXconn invalid SrcSts: %d, %d", theSrcSts, itsNumStss);
        FC_THROW_ERROR(FC_RuntimeError, aErrBuf);
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    FindEdgeIngressXconn() class method
*
* Description: lookup theSrcSts. If a connection exists the return the
*
* Inputs:
*     theSrcSts - the Source Timeslot
*
* Outputs:
*     edgeIngXcIter points to an entry in the ingress connection map
*
* Returns:
*     bool
*
*************************************END***************************************
*/
bool TSPII_FabIf::FindEdgeIngressXconn(uint16 theSrcSts, TSPII_FabIfEdgeIngXcMap::iterator & edgeIngXcIter)
{
    bool isFound = false;
#ifndef PSOSP
    TSPII_FabIfEdgeIngXcKey   aKey;

    if(theSrcSts < itsNumStss)
    {
        aKey.SrcSts = theSrcSts;

        // Search for this element
        edgeIngXcIter = itsEdgeIngressXconnsMap.find(aKey);

        if(edgeIngXcIter != itsEdgeIngressXconnsMap.end())
        {
            // element exsists
            isFound = true;
        }
    }
#endif
    return isFound;
}

/************************************BEGIN*************************************
*
* Function:    DeleteAllEdgeIngressXconns() class method
*
* Description: Tears down all EDGE association of how to route Ingress traffic to FAP.
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
void TSPII_FabIf::DeleteAllEdgeIngressXconns()
{
#ifndef PSOSP
    TSPII_FabIfEdgeIngXcMap::iterator edgeIngXcIter;

    // Mark all connections as deleted in the Xconn table
    for(edgeIngXcIter = itsEdgeIngressXconnsMap.begin();
        edgeIngXcIter != itsEdgeIngressXconnsMap.end();
        edgeIngXcIter++)
    {
        edgeIngXcIter->second.IsDeleted = true;
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    CommitEdgeIngressXconns() class method
*
* Description:  Commits all Egress Xconns to the EDGE chip
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
void TSPII_FabIf::CommitEdgeIngressXconns(bool theForceHw)
{
#ifndef PSOSP
    TSPII_FabIfEdgeIngXcMap::iterator  edgeIngXcIter;

    // Commit all connections stored in the Xconn table
    for(edgeIngXcIter = itsEdgeIngressXconnsMap.begin();
        edgeIngXcIter != itsEdgeIngressXconnsMap.end(); )
    {
        if(edgeIngXcIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            edgeIngXcIter = itsEdgeIngressXconnsMap.erase(edgeIngXcIter);
#endif
        }
        else if(edgeIngXcIter->second.IsNewOrChanged)
        {
            // clear the flag since we are committing the changes
            edgeIngXcIter->second.IsNewOrChanged = false;
            edgeIngXcIter++;
        }
        else
        {
            edgeIngXcIter++;
        }
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    GetEdgeIngressXconns() class method
*
* Description: Retrieves the currently activated EDGE Ingress Xconns from
*              the hardware.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     a list of current Edge Ingress Xconns
*
*************************************END***************************************
*/
TSPII_FabIfEdgeIngXcMap& TSPII_FabIf::GetEdgeIngressXconns()
{
    return itsEdgeIngressXconnsMap;
}

/************************************BEGIN*************************************
*
* Function:    SetPSInitComplete() class method
*
* Description: Sets the status of Packet Services fabric initialization
*
* Inputs:
*     isComplete - is Packet Services initialization complete
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_FabIf::SetPSInitComplete(bool isComplete)
{
    itsPSInitComplete = isComplete;
}

/************************************BEGIN*************************************
*
* Function:    GetPSInitComplete() class method
*
* Description: Returns the status of Packet Services initializaton
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     isComplete
*
*************************************END***************************************
*/
bool TSPII_FabIf::GetPSInitComplete()
{
    return itsPSInitComplete;
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
FC_Stream & TSPII_FabIf::WriteObjectBinary(FC_Stream & theStream)
{
    char  aStr[256];
    char  aSubStr[100];
    TSPII_FabIfEdgeEgrXcMap::iterator  aEdgeEgrIter;
    TSPII_FabIfEdgeIngXcMap::iterator  aEdgeIngIter;
    CT_FabMcGroupMap::iterator aFabIter;
    vector<CT_FabMcMember>::iterator aMemIter;
    int   aTemp;
    uint8 aSlot;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    theStream << static_cast<int>(itsSwitchMode);
    theStream << static_cast<int>(itsSwitchDomain);

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        theStream << itsSlotEnabled[aSlot];
        theStream << static_cast<int>(itsSlotTrafficType[aSlot][0]);     // local
        theStream << static_cast<int>(itsSlotTrafficType[aSlot][1]);     // remote
        theStream << static_cast<int>(itsSlotSpeed[aSlot][0]);     // local
        theStream << static_cast<int>(itsSlotSpeed[aSlot][1]);     // remote
        theStream << itsSlotFecEnabled[aSlot][0];    // local
        theStream << itsSlotFecEnabled[aSlot][1];    // remote
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////
    // Write out the EDGE Egress Xconns table
    aTemp = itsEdgeEgressXconnsMap.size();
    theStream << aTemp;
    for(aEdgeEgrIter=itsEdgeEgressXconnsMap.begin(); aEdgeEgrIter != itsEdgeEgressXconnsMap.end(); ++aEdgeEgrIter)
    {
        // KEY + VAL
        sprintf(aStr, "%03d,%03d,%05d,%05d,%05d,%03d,%01d,%01d",
                      aEdgeEgrIter->first.SrcShelf, aEdgeEgrIter->first.SrcSlot,
                      aEdgeEgrIter->first.SrcSts, aEdgeEgrIter->first.ConId, aEdgeEgrIter->first.DstSts,
                      aEdgeEgrIter->second.DummyVal, aEdgeEgrIter->second.IsNewOrChanged,
                      aEdgeEgrIter->second.IsDeleted);
        theStream << aStr;
    }

    //////////////////////////////////////////////////////////////////////////
    // Write out the EDGE Ingress Xconns table
    aTemp = itsEdgeIngressXconnsMap.size();
    theStream << aTemp;
    for(aEdgeIngIter=itsEdgeIngressXconnsMap.begin(); aEdgeIngIter != itsEdgeIngressXconnsMap.end(); ++aEdgeIngIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%01d,%05d,%03d,%03d,%03d,%05d,%01d,%03d,%01d,%01d",
                      aEdgeIngIter->first.SrcSts, aEdgeIngIter->second.IsMc,
                      aEdgeIngIter->second.McId, aEdgeIngIter->second.RemShelf,
                      aEdgeIngIter->second.RemSlot, aEdgeIngIter->second.RemImux,
                      aEdgeIngIter->second.ConId, aEdgeIngIter->second.IsBypass,
                      aEdgeIngIter->second.RemCardType,
                      aEdgeIngIter->second.IsNewOrChanged, aEdgeIngIter->second.IsDeleted);
        theStream << aStr;
    }

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
#endif

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
FC_Stream & TSPII_FabIf::ReadObjectBinary(FC_Stream & theStream)
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
    theStream >> aTemp;
    itsSwitchDomain = static_cast<CT_SwitchDomainMode>(aTemp);
    
    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        theStream >> itsSlotEnabled[aSlot];

        theStream >> aTemp;
        itsSlotTrafficType[aSlot][0] = static_cast<TSPII_FabIf_TrafficType>(aTemp);     // local

        theStream >> aTemp;
        itsSlotTrafficType[aSlot][1] = static_cast<TSPII_FabIf_TrafficType>(aTemp);     // remote

        theStream >> aTemp;
        itsSlotSpeed[aSlot][0] = static_cast<CT_TEL_LinkRate>(aTemp);     // local

        theStream >> aTemp;
        itsSlotSpeed[aSlot][1] = static_cast<CT_TEL_LinkRate>(aTemp);     // remote

        theStream >> itsSlotFecEnabled[aSlot][0];    // local
        theStream >> itsSlotFecEnabled[aSlot][1];    // remote
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////////

    // first clear out the map
    itsEdgeEgressXconnsMap.clear();

    // read in the number of EDGE Egress Xconns
    theStream >> aCount;

    // The records must be converted from a char string
    while(aCount > 0)
    {
        TSPII_FabIfEdgeEgrXcKey   aKey;
        TSPII_FabIfEdgeEgrXcVal   aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.SrcShelf = static_cast<uint8>(atoi(strtok(aStr, ",")));
        aKey.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aKey.SrcSts  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aKey.ConId  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aKey.DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));

        aVal.DummyVal = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsEdgeEgressXconnsMap.insert(TSPII_FabIfEdgeEgrXcMap::value_type(aKey, aVal));

        // Update count
        aCount--;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read in the EDGE Ingress Xconn Table
    // first clear out the map
    itsEdgeIngressXconnsMap.clear();

    // read in the number of EDGE Ingress Xconns
    theStream >> aCount;

    // The records must be converted from a char string
    while(aCount > 0)
    {
        TSPII_FabIfEdgeIngXcKey   aKey;
        TSPII_FabIfEdgeIngXcVal   aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.SrcSts = static_cast<uint8>(atoi(strtok(aStr, ",")));

        aVal.IsMc = atoi(strtok(NULL, ",")) ? true : false;
        aVal.McId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aVal.RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.ConId  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aVal.IsBypass = atoi(strtok(NULL, ",")) ? true : false;
        aVal.RemCardType = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsEdgeIngressXconnsMap.insert(TSPII_FabIfEdgeIngXcMap::value_type(aKey, aVal));

        // Update count
        aCount--;
    }

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
#endif

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
ostream & TSPII_FabIf::WriteObject(ostream & theStream)
{
    int   aTemp;
    uint8 aSlot;
    char  aStr[256];
    char  aSubStr[100];
    TSPII_FabIfEdgeEgrXcMap::iterator  aEdgeEgrIter;
    TSPII_FabIfEdgeIngXcMap::iterator  aEdgeIngIter;
    CT_FabMcGroupMap::iterator aFabIter;
    vector<CT_FabMcMember>::iterator aMemIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    aTemp = static_cast<int>(itsSwitchMode);
    theStream << FC_InsertVar(aTemp);
    aTemp = static_cast<int>(itsSwitchDomain);
    theStream << FC_InsertVar(aTemp);

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        theStream << FC_InsertVar(itsSlotEnabled[aSlot]);

        aTemp = static_cast<int>(itsSlotTrafficType[aSlot][0]);     // local
        theStream << FC_InsertVar(aTemp);

        aTemp = static_cast<int>(itsSlotTrafficType[aSlot][1]);     // remote
        theStream << FC_InsertVar(aTemp);

        aTemp = static_cast<int>(itsSlotSpeed[aSlot][0]);     // local
        theStream << FC_InsertVar(aTemp);

        aTemp = static_cast<int>(itsSlotSpeed[aSlot][1]);     // remote
        theStream << FC_InsertVar(aTemp);

        theStream << FC_InsertVar(itsSlotFecEnabled[aSlot][0]);    // local
        theStream << FC_InsertVar(itsSlotFecEnabled[aSlot][1]);    // remote
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////
    // Write out the EDGE Egress Xconns table
    aTemp = itsEdgeEgressXconnsMap.size();
    theStream << FC_InsertVar(aTemp);
    for(aEdgeEgrIter=itsEdgeEgressXconnsMap.begin(); aEdgeEgrIter != itsEdgeEgressXconnsMap.end(); ++aEdgeEgrIter)
    {
        // KEY + VAL
        sprintf(aStr, "%03d,%03d,%05d,%05d,%05d,%03d,%01d,%01d",
                      aEdgeEgrIter->first.SrcShelf, aEdgeEgrIter->first.SrcSlot,
                      aEdgeEgrIter->first.SrcSts, aEdgeEgrIter->first.ConId, aEdgeEgrIter->first.DstSts,
                      aEdgeEgrIter->second.DummyVal, aEdgeEgrIter->second.IsNewOrChanged,
                      aEdgeEgrIter->second.IsDeleted);
        theStream << FC_InsertVar(aStr);
    }

    //////////////////////////////////////////////////////////////////////////
    // Write out the EDGE Ingress Xconns table
    aTemp = itsEdgeIngressXconnsMap.size();
    theStream << FC_InsertVar(aTemp);
    for(aEdgeIngIter=itsEdgeIngressXconnsMap.begin(); aEdgeIngIter != itsEdgeIngressXconnsMap.end(); ++aEdgeIngIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%01d,%05d,%03d,%03d,%03d,%05d,%01d,%03d,%01d,%01d",
                      aEdgeIngIter->first.SrcSts, aEdgeIngIter->second.IsMc,
                      aEdgeIngIter->second.McId, aEdgeIngIter->second.RemShelf,
                      aEdgeIngIter->second.RemSlot, aEdgeIngIter->second.RemImux,
                      aEdgeIngIter->second.ConId, aEdgeIngIter->second.IsBypass,
                      aEdgeIngIter->second.RemCardType,
                      aEdgeIngIter->second.IsNewOrChanged, aEdgeIngIter->second.IsDeleted);
        theStream << FC_InsertVar(aStr);
    }

    // Write out the FAP Multicast table
    aTemp = itsMcGroupsMap.size();
    theStream << FC_InsertVar(aTemp);
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
#endif

    return TSPII_BaseIf::WriteObject(theStream);
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
istream & TSPII_FabIf::ReadObject(istream & theStream)
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
    
    theStream >> FC_ExtractVar(aTemp);
    itsSwitchDomain = static_cast<CT_SwitchDomainMode>(aTemp);

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        theStream >> FC_ExtractVar(itsSlotEnabled[aSlot]);

        theStream >> FC_ExtractVar(aTemp);
        itsSlotTrafficType[aSlot][0] = static_cast<TSPII_FabIf_TrafficType>(aTemp);     // local

        theStream >> FC_ExtractVar(aTemp);
        itsSlotTrafficType[aSlot][1] = static_cast<TSPII_FabIf_TrafficType>(aTemp);     // remote

        theStream >> FC_ExtractVar(aTemp);
        itsSlotSpeed[aSlot][0] = static_cast<CT_TEL_LinkRate>(aTemp);     // local

        theStream >> FC_ExtractVar(aTemp);
        itsSlotSpeed[aSlot][1] = static_cast<CT_TEL_LinkRate>(aTemp);     // remote

        theStream >> FC_ExtractVar(itsSlotFecEnabled[aSlot][0]);    // local
        theStream >> FC_ExtractVar(itsSlotFecEnabled[aSlot][1]);    // remote
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////////
    // Read in the EDGE Xconn Table

    // first clear out the map
    itsEdgeEgressXconnsMap.clear();

    // read in the EDGE Egress Xconn list size
    theStream >> FC_ExtractVar(aCount);

    // The records must be converted from a char string
    while(aCount > 0)
    {
        TSPII_FabIfEdgeEgrXcKey   aKey;
        TSPII_FabIfEdgeEgrXcVal   aVal;

        // Read each Xconn record as a comma seperated string - write to driver.
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.SrcShelf = static_cast<uint8>(atoi(strtok(aStr, ",")));
        aKey.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aKey.SrcSts  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aKey.ConId  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aKey.DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));

        aVal.DummyVal = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsEdgeEgressXconnsMap.insert(TSPII_FabIfEdgeEgrXcMap::value_type(aKey, aVal));

        aCount--;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read in the EDGE Ingress Xconn Table

    // first clear out the map
    itsEdgeIngressXconnsMap.clear();

    // read in the number of EDGE Ingress Xconns
    theStream >> FC_ExtractVar(aCount);

    // The records must be converted from a char string to the array
    while(aCount > 0)
    {
        TSPII_FabIfEdgeIngXcKey   aKey;
        TSPII_FabIfEdgeIngXcVal   aVal;

        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.SrcSts = static_cast<uint8>(atoi(strtok(aStr, ",")));

        aVal.IsMc = atoi(strtok(NULL, ",")) ? true : false;
        aVal.McId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aVal.RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.ConId  = static_cast<uint16>(atoi(strtok(NULL, ",")));
        aVal.IsBypass = atoi(strtok(NULL, ",")) ? true : false;
        aVal.RemCardType = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsEdgeIngressXconnsMap.insert(TSPII_FabIfEdgeIngXcMap::value_type(aKey, aVal));

        aCount--;
    }

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
#endif
    // Update Sets
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
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
void TSPII_FabIf::Display(FC_Stream & theStream, int argc, char** argv)
{
    bool aEexc    = false;
    bool aEixc    = false;
    bool aMcxc    = false;
    bool aFinit   = false;
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
        aEexc  = true;
        aEixc  = true;
        aMcxc  = true;
        aFinit = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "eexc") == 0))
    {
        aEexc = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "eixc") == 0))
    {
        aEixc = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "mcxc") == 0))
    {
        aMcxc = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "finit") == 0))
    {
        aFinit = true;
    }
    else
    {
        fc_cout << "Usage: tspii display fab <all|eexc|eixc|mcxc|finit>\n" << endl;
        return;
    }

    theStream << "  FAB Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    if(aSummary)
    {
        theStream << "      itsNumShelves               = " << (uint16)itsNumShelves           << "\n";
        theStream << "      itsNumSlots                 = " << (uint16)itsNumSlots             << "\n";
        theStream << "      itsNumImuxs                 = " << (uint16)itsNumImuxs             << "\n";
        theStream << "      itsNumStss                  = " << (uint16)itsNumStss              << "\n";
        theStream << "      itsNumMcgs                  = " << (uint16)itsNumMcgs              << "\n";
        theStream << "      itsConIds                   = " << (uint16)itsNumConIds            << "\n";
        theStream << "      itsIsConMode                = " << TEXT_ON_OFF(itsIsConMode)       << "\n";
        theStream << "      itsForceShelf               = " << TEXT_ON_OFF(itsForceShelf)      << "\n";
        theStream << "      Slot Traffic Type           = " << DisplaySlotTrafficType()        << "\n";
        theStream << "      Slot Speed                  = " << DisplaySlotSpeed()              << "\n";
        theStream << "      Slot Fec Enabled            = " << DisplaySlotFecEnabled()         << "\n";
        theStream << "      Switch Mode                 = " << DisplaySwitchMode()             << "\n";
        theStream << "      Switch Domain Mode          = " << DisplaySwitchDomainMode()       << "\n";
        theStream << "      Slot Enable                 = " << DisplaySlotEnabled()            << "\n";
        theStream << "      Edge Egress Xconn Count     = " << DisplayEdgeEgressXc(false)      << "\n";
        theStream << "      Edge Ingress Xconn Count    = " << DisplayEdgeIngressXc(false)     << "\n";
        theStream << "      Multicast Count             = " << DisplayMcGroups(false)          << "\n";
        theStream << "      Fabric Init Complete        = " << DisplayFabricInitComplete(false)<< "\n";
    }
    if(aEexc)
    {
        theStream << "      Edge Egress Xconns          = " << DisplayEdgeEgressXc(true)       << "\n";
    }
    if(aEixc)
    {
        theStream << "      Edge Ingress Xconns         = " << DisplayEdgeIngressXc(true)      << "\n";
    }
    if(aMcxc)
    {
        theStream << "      Multicast Groups            = " << DisplayMcGroups(true)           << "\n";
    }
    if(aFinit)
    {
        theStream << "      Fabric Init Complete        = " << DisplayFabricInitComplete(true) << "\n";
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
bool TSPII_FabIf::Set(int argc, char ** argv)
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

            if(itsForceShelf)
            {
                aMember.RemShelf = 1;  // For now force shelf to 1
            }

            aMember.RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
            aMember.RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));

            // Perform validity checks before converting data and adding
            // to membership list. NOTE: An Imux value of 0 is possible
            // if no Imuxs are supported on the module.
            if((aMember.RemShelf > 0) && (aMember.RemShelf <= itsNumShelves) &&
               (aMember.RemSlot > 0) && (aMember.RemSlot <= itsNumSlots) &&
               (aMember.RemImux <= itsNumImuxs))
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
        if(itsForceShelf)
        {
            RemShelf = 1;  // For now force to shelf 1
        }
        RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        CommitNow = atoi(strtok(NULL, ",")) ? true : false;

        // Perform validity checks before converting data and adding
        // to membership list. NOTE: An Imux value of 0 is possible
        // if no Imuxs are supported on the module.
        if((RemShelf > 0) && (RemShelf <= itsNumShelves) &&
           (RemSlot > 0) && (RemSlot <= itsNumSlots) &&
           (RemImux <= itsNumImuxs))
        {
            // Convert it to "0" based numbering
            RemShelf--;
            RemSlot--;
            if (RemImux != 0) // Only convert if Imuxs are supported
            {
                RemImux--;
            }
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
        if(itsForceShelf)
        {
            RemShelf = 1;  // For now force to shelf 1
        }
        RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        CommitNow = atoi(strtok(NULL, ",")) ? true : false;

        // Perform validity checks before converting data and adding
        // to membership list. NOTE: An Imux value of 0 is possible
        // if no Imuxs are supported on the module.
        if((RemShelf > 0) && (RemShelf <= itsNumShelves) &&
           (RemSlot > 0) && (RemSlot <= itsNumSlots) &&
           (RemImux <= itsNumImuxs))
        {
            // Convert it to "0" based numbering
            RemShelf--;
            RemSlot--;
            if (RemImux != 0) // Only convert if Imuxs are supported
            {
                RemImux--;
            }
            DeleteMcGroupMember(McId, RemShelf, RemSlot, RemImux, CommitNow);
            printUsage = false;
        }
    }
    else if((argc == 4) && (strcmp(argv[0], "stype") == 0))
    {
        uint8 Slot = static_cast<uint8>(atoi(argv[1]));
        bool isRemote = false;
        if(strcmp(argv[2], "on") == 0)
        {
            isRemote = true;
        }
        if((Slot > 0) && (Slot <= itsNumSlots))
        {
            for (int i = 0; i <= TSPII_FabIf_Traffic_Unknown; i++) if (strcmp(argv[3], DISPLAY_FABIF_TRAFFIC_TYPE(i)) == 0)
            {
                SetSlotTrafficType(Slot - 1, isRemote, (TSPII_FabIf_TrafficType)i);
                printUsage = false;
            }
        }
    }
    else if((argc == 4) && (strcmp(argv[0], "sspeed") == 0))
    {
        uint8 Slot = static_cast<uint8>(atoi(argv[1]));
        bool isRemote = false;
        if(strcmp(argv[2], "on") == 0)
        {
            isRemote = true;
        }

        if((Slot > 0) && (Slot <= itsNumSlots))
        {
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRate3Gbs)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRate3Gbs);
                printUsage = false;
            }
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRate4Gbs)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRate4Gbs);
                printUsage = false;
            }
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRate5Gbs)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRate5Gbs);
                printUsage = false;
            }
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRate5_75Gbs)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRate5_75Gbs);
                printUsage = false;
            }
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRate6Gbs)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRate6Gbs);
                printUsage = false;
            }
            if(strcmp(argv[3], DISPLAY_LINK_RATE(CT_TEL_LinkRateNone)) == 0)
            {
                SetSlotSpeed(Slot - 1, isRemote, CT_TEL_LinkRateNone);
                printUsage = false;
            }
        }
    }
    else if ((argc == 4) && strcmp(argv[0], "sfec") == 0)
    {
        uint8 Slot = static_cast<uint8>(atoi(argv[1]));
        bool isRemote = false;
        if(strcmp(argv[2], "on") == 0)
        {
            isRemote = true;
        }

        if((Slot > 0) && (Slot <= itsNumSlots))
        {
            if(strcmp(argv[3], "on") == 0)
            {
                SetSlotFecEnabled(Slot - 1, isRemote, true);
                printUsage = false;
            }
            else if(strcmp(argv[3], "off") == 0)
            {
                SetSlotFecEnabled(Slot - 1, isRemote, false);
                printUsage = false;
            }
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "slote") == 0)
    {
        uint8 Slot = static_cast<uint8>(atoi(argv[1]));
        if((Slot > 0) && (Slot <= itsNumSlots))
        {
            if(strcmp(argv[2], "on") == 0)
            {
                SetSlotEnabled(Slot - 1, true);
                printUsage = false;
            }
            else if(strcmp(argv[2], "off") == 0)
            {
                SetSlotEnabled(Slot - 1, false);
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
    else if ((argc == 2) && (strcmp(argv[0], "eexca") == 0))
    {
        char aOutBuf[256];
        uint8 SrcShelf;
        uint8 SrcSlot;
        uint16 SrcSts;
        uint16 ConId;
        uint16 DstSts;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,0");    // force some tokens in the string.
        SrcShelf = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        if(itsForceShelf)
        {
            SrcShelf = 1;  // For now force to shelf 1
        }
        SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        SrcSts = static_cast<uint16>(atoi(strtok(NULL, ",")));
        ConId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));
        if((SrcShelf > 0) && (SrcShelf <= itsNumShelves) &&
           (SrcSlot > 0) && (SrcSlot <= itsNumSlots) &&
           (SrcSts > 0) && (SrcSts <= itsNumStss) &&
           (DstSts > 0) && (DstSts <= itsNumStss))
        {
            // Convert it to "0" based numbering - Leave ConId alone
            AddEdgeEgressXconn(SrcShelf - 1, SrcSlot - 1, SrcSts - 1, ConId, DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "eexcd") == 0))
    {
        char   aOutBuf[256];
        uint8  SrcShelf;
        uint8  SrcSlot;
        uint16 SrcSts;
        uint16 ConId;
        uint16 DstSts;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0");    // force some tokens in the string.
        SrcShelf = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        if(itsForceShelf)
        {
            SrcShelf = 1;  // For now force to shelf 1
        }
        SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        SrcSts = static_cast<uint16>(atoi(strtok(NULL, ",")));
        ConId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));
        if((SrcShelf > 0) && (SrcShelf <= itsNumShelves) &&
           (SrcSlot > 0) && (SrcSlot <= itsNumSlots) &&
           (SrcSts > 0) && (SrcSts <= itsNumStss) &&
           (DstSts > 0) && (DstSts <= itsNumStss))
        {
            // Convert it to "0" based numbering - Leave ConId untranslated
            DeleteEdgeEgressXconn(SrcShelf - 1, SrcSlot - 1, SrcSts - 1, ConId, DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "eexcda") == 0))
    {
        DeleteAllEdgeEgressXconns();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "eexcc") == 0))
    {
        CommitEdgeEgressXconns();
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "eixca") == 0))
    {
        char   aOutBuf[256];
        uint16 SrcSts;
        bool   IsMc;
        bool   IsBypass;
        uint16 McId;
        uint8  RemShelf;
        uint8  RemSlot;
        uint8  RemImux;
        uint8  RemCardType;
        uint16 ConId;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,0,0,0,0,0");    // force some tokens in the string.
        SrcSts = static_cast<uint16>(atoi(strtok(aOutBuf, ",")));
        IsMc = atoi(strtok(NULL, ",")) ? true : false;
        McId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        RemShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        if(itsForceShelf)
        {
            RemShelf = 1;  // For now force to shelf 1
        }
        RemSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        RemImux = static_cast<uint8>(atoi(strtok(NULL, ",")));
        ConId = static_cast<uint16>(atoi(strtok(NULL, ",")));
        IsBypass = atoi(strtok(NULL, ",")) ? true : false;
        RemCardType = static_cast<uint8>(atoi(strtok(NULL, ",")));
        if((SrcSts > 0) && (SrcSts <=  itsNumStss) &&
           (RemShelf > 0) && (RemShelf <= itsNumShelves) &&
           (RemSlot > 0) && (RemSlot <= itsNumSlots) &&
           (RemImux > 0) && (RemImux <= itsNumImuxs) &&
           (ConId > 0) && (ConId <= itsNumConIds))
        {
            // Convert it to "0" based numbering - Leave McId and ConId untransplated
            AddEdgeIngressXconn(SrcSts - 1, IsMc, McId, RemShelf - 1, RemSlot - 1, RemImux - 1, ConId, IsBypass, RemCardType);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "eixcd") == 0))
    {
        uint16 SrcSts;

        SrcSts = static_cast<uint16>(atoi(argv[1]));
        if((SrcSts > 0) && (SrcSts <= itsNumStss))
        {
            // Convert it to "0" based numbering
            DeleteEdgeIngressXconn(SrcSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "eixcda") == 0))
    {
        DeleteAllEdgeIngressXconns();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "eixcc") == 0))
    {
        CommitEdgeIngressXconns();
        printUsage = false;
    }
    else if ((argc == 2) && strcmp(argv[0], "fabinit") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            itsFabInitComplete = true;
            printUsage = false;
        }
        else if(strcmp(argv[1], "off") == 0)
        {
            itsFabInitComplete = false;
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
        char aNumSlotsStr[10];
        char aNumMcgsStr[10];
        char aNumShelvesStr[10];
        char aNumStssStr[10];
        char aNumImuxsStr[10];
        char aNumConIdsStr[10];
        sprintf(aNumSlotsStr, "%d", itsNumSlots);
        sprintf(aNumMcgsStr, "%d", itsNumMcgs);
        sprintf(aNumShelvesStr, "%d", itsNumShelves);
        sprintf(aNumStssStr, "%d", itsNumStss);
        sprintf(aNumImuxsStr, "%d", itsNumImuxs);
        sprintf(aNumConIdsStr, "%d", itsNumConIds);

        fc_cout << "    mcgs        <id> <mbrcnt> <dshelf,dslot,dimux,....> \n"
                   "                  id=1-" << aNumMcgsStr << ", mbrcnt=0-255, dshelf=1-" << aNumShelvesStr << ", dimux=1-" << aNumImuxsStr << "\n"
                   "    mcgd        <id> \n"
                   "    mcgda        \n"
                   "    mcgc         \n"
                   "    mcgam         <mcid,rshelf,rslot,rimux,commit>\n"
                   "    mcgdm         <mcid,rshelf,rslot,rimux,commit>\n"
                   "                   mcid, rshelf=1-N,rslot=1-N,rimux=1L-2P,mcid,commit=0-1\n"
                   "----------------------------------------------------------\n"
                   "    slote       <slot=1-" << aNumSlotsStr << "> <on|off>\n"
                   "----------------------------------------------------------\n"
                   "    stype       <slot=1-" << aNumSlotsStr << "> <on|off - remote> <Sonet|Packet|CesPacket|Unknown>\n"
                   "----------------------------------------------------------\n"
                   "    sspeed      <slot=1-" << aNumSlotsStr << "> <on|off - remote> <3Gbs|4Gbs|5Gbs|6Gbs|None>\n"
                   "----------------------------------------------------------\n"
                   "    sfec        <slot=1-" << aNumSlotsStr << "> <on|off - remote> <on|off>\n"
                   "----------------------------------------------------------\n"
                   "    switch      <None|Mesh|CtrSwitch|EndSwitch|Repeater>\n"
                   "----------------------------------------------------------\n"
                   "    eexca       <sshelf,sslot,ssts,conid,dsts>\n"
                   "    eexcd       <sshelf,sslot,ssts,conid,dsts>\n"
                   "                   sshelf=1-" << aNumShelvesStr << ", sslot=1-" << aNumSlotsStr << ", ssts=1-" << aNumStssStr << ", conid=0-" << aNumConIdsStr <<  ", dsts=1-" << aNumStssStr << "\n"
                   "    eexcda       \n"
                   "    eexcc        \n"
                   "----------------------------------------------------------\n"
                   "    eixca       <ssts,ismc,mcid,dshelf,dslot,dimux,conid,isbp,dctype>\n"
                   "    eixcd       <ssts>\n"
                   "                   ssts=1-" << aNumStssStr << ", ismc=0Uni 1=Multi, mcid=0-" << aNumMcgsStr-1 << ", dshelf=1-" << aNumShelvesStr << ",\n"
                   "                   dslot=1-" << aNumSlotsStr << ", dimux=1-" << aNumImuxsStr << ", conid=0-" << aNumConIdsStr << ", isbp=0No 1=Yes, dctype=CT_CardTypes.h\n"
                   "    eixcda       \n"
                   "    eixcc        \n"
                   "----------------------------------------------------------\n"
                   "    fabinit     <on|off>\n"
                   "----------------------------------------------------------\n"
                   "    cable       <10,20,80>\n"
                   "----------------------------------------------------------\n"  

                                     << endl;
    }

    return printUsage;
}

/************************************BEGIN*************************************
*
* Function:    Simul() class method
*
* Description:
*     Dummy simul method
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
bool TSPII_FabIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FabIf::Display(FC_Stream & theStream)
{
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplayMcGroups(bool printDetail)
{
    char    aBuf[128];
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
#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotTrafficType()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", DISPLAY_FABIF_TRAFFIC_TYPE(itsSlotTrafficType[aSlot][0]),   /* local */
                                 DISPLAY_FABIF_TRAFFIC_TYPE(itsSlotTrafficType[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotSpeed()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", DISPLAY_LINK_RATE(itsSlotSpeed[aSlot][0]),   /* local */
                                 DISPLAY_LINK_RATE(itsSlotSpeed[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotFecEnabled()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", TEXT_ON_OFF(itsSlotFecEnabled[aSlot][0]),   /* local */
                                 TEXT_ON_OFF(itsSlotFecEnabled[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySwitchMode()
{
    char aBuf[128];
    string  aStr;

    sprintf(aBuf, "%s", DISPLAY_SWITCH_MODE(itsSwitchMode));
    aStr = aBuf;
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySwitchDomainMode()
{
    char aBuf[128];
    string  aStr;

    sprintf(aBuf, "%s", DISPLAY_SWITCH_DOMAIN_MODE(itsSwitchDomain));
    aStr = aBuf;
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotEnabled()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 0; i < itsNumSlots; i++)
    {
        sprintf(aBuf, "%s,", itsSlotEnabled[i] ? "on" : "off");
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplayEdgeEgressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_FabIfEdgeEgrXcMap::iterator  aEdgeEgrIter;
    TSPII_FabIfEdgeIngXcMap::iterator  aEdgeIngIter;

    sprintf(aBuf, "%d <sshelf,sslot,ssts,conid,dsts - isNewChanged isDeleted>\n", itsEdgeEgressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aEdgeEgrIter=itsEdgeEgressXconnsMap.begin(); aEdgeEgrIter != itsEdgeEgressXconnsMap.end(); ++aEdgeEgrIter)
        {
                sprintf(aBuf, "         ");
                aStr += aBuf;

                sprintf(aBuf, "%03d,%03d,%05d,%05d,%05d - %1d %1d", aEdgeEgrIter->first.SrcShelf + 1,
                                                     aEdgeEgrIter->first.SrcSlot + 1,
                                                     aEdgeEgrIter->first.SrcSts + 1,
                                                     aEdgeEgrIter->first.ConId, 
                                                     aEdgeEgrIter->first.DstSts + 1,
                                                     aEdgeEgrIter->second.IsNewOrChanged,
                                                     aEdgeEgrIter->second.IsDeleted);
                aStr += aBuf;
                aStr += "\n";
        }
    }
#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplayEdgeIngressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_FabIfEdgeIngXcMap::iterator  aEdgeIngIter;


    sprintf(aBuf, "%d <ssts,ismc,mcid,rshelf,rslot,rimux,conid,isbp,rctype - isNewChanged isDeleted>\n", itsEdgeIngressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aEdgeIngIter=itsEdgeIngressXconnsMap.begin(); aEdgeIngIter != itsEdgeIngressXconnsMap.end(); ++aEdgeIngIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%03d,%1d,%05d,%03d,%03d,%03d,%05d,%1d,%03d - %1d %1d", aEdgeIngIter->first.SrcSts + 1,
                                                          aEdgeIngIter->second.IsMc,
                                                          aEdgeIngIter->second.McId,
                                                          aEdgeIngIter->second.RemShelf + 1,
                                                          aEdgeIngIter->second.RemSlot + 1,
                                                          aEdgeIngIter->second.RemImux + 1,
                                                          aEdgeIngIter->second.ConId,
                                                          aEdgeIngIter->second.IsBypass,
                                                          aEdgeIngIter->second.RemCardType,
                                                          aEdgeIngIter->second.IsNewOrChanged,
                                                          aEdgeIngIter->second.IsDeleted);
            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotFecInitComplete()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", TEXT_ON_OFF(itsSlotFecInitComplete[aSlot][0]),   /* local */
                                 TEXT_ON_OFF(itsSlotFecInitComplete[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotSpeedInitComplete()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", TEXT_ON_OFF(itsSlotSpeedInitComplete[aSlot][0]),   /* local */
                                 TEXT_ON_OFF(itsSlotSpeedInitComplete[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplaySlotFeInitComplete()
{
    char aBuf[128];
    string  aStr;
    uint8 aSlot;

    for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
    {
        sprintf(aBuf, "%s %s, ", TEXT_ON_OFF(itsSlotFeInitComplete[aSlot][0]),   /* local */
                                 TEXT_ON_OFF(itsSlotFeInitComplete[aSlot][1]));  /* remote */
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_FabIf::DisplayFabricInitComplete(bool printDetail)
{
    char aBuf[128];
    string  aStr;
    uint16  theMcId;
    bool    allMcgInitComplete;

    aStr = TEXT_ON_OFF(itsFabInitComplete);
    aStr += "\n";

    if (printDetail)
    {
        aStr += "      Slot Fe    Init Complete: " + DisplaySlotFeInitComplete() + "\n";
        aStr += "      Slot Fec   Init Complete: " + DisplaySlotFecInitComplete() + "\n";
        aStr += "      Slot Speed Init Complete: " + DisplaySlotSpeedInitComplete() + "\n";
        sprintf(aBuf,"      Packet Services Init Complete: %s\n", TEXT_ON_OFF(itsPSInitComplete));
        aStr += aBuf;
        sprintf(aBuf,"      Packet Services Card In Shelf: %s\n", TEXT_ON_OFF(itsPSCardInShelf));
        aStr += aBuf;

        allMcgInitComplete = true;
        for (theMcId = TSPII_FABIF_MCGROUP_START;
                (theMcId <TSPII_FABIF_PQW_MCGROUP) && allMcgInitComplete;
                theMcId++)
        {
            if (!itsMcgInitComplete[theMcId])
            {
                allMcgInitComplete = false;
            }
        }
        sprintf(aBuf,"      Multicast Group Init Complete: %s\n", TEXT_ON_OFF(allMcgInitComplete));
        aStr += aBuf;
        if (!allMcgInitComplete)
        {
            sprintf(aBuf,"      First Multicast Group not initialized: %d\n", theMcId);
            aStr += aBuf;
        }
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FabIf::GetFapPortIdFromRemImuxId(uint8 remImux, uint8 &fapPort)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FabIf::GetRemImuxIdFromFapPortId(uint8 fapPort, uint8 &remImux)
{
    return false;
}
