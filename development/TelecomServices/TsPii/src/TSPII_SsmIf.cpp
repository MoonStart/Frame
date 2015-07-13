/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SsmIf.cpp
* Type:    C++ source
* Author:  Denham Reynolds - September 2008
* Description:
*     Definition of the class TSPII_SsmIf which models the simulation
*     SSM Card specific Interface entity.
*
*
*************************************END***************************************
*/
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_SsmIf.h"
#include <strstream>
#include "TsPii/TSPII_Region.h"
#include "TsPii/TSPII_SubApplication.h"
#include <cstring>

/************************************BEGIN*************************************
*
* Function:    TSPII_SsmIf constructor
*
* Description:
*     TSPII_SsmIfIf class constructor
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
TSPII_SsmIf::TSPII_SsmIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, bool theForceShelf) :
    TSPII_BaseIf(theDefault)
{
    uint8 aShelf;

    itsNumShelves = theNumShelves;
    itsNumSlots = theNumSlots;
    itsNumImuxs = theNumImuxs;
    itsForceShelf = theForceShelf;

        // Dynamically allocate the memory for the PQW Timeout table
    itsPqwTimeout = (uint32 **) malloc(sizeof(uint32 *) * itsNumShelves);
    for (aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        itsPqwTimeout[aShelf] = (uint32 *) malloc(sizeof(uint32) * itsNumSlots);
    }

    Reset();
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SsmIf destructor
*
* Description:
*     TSPII_SsmIf class destructor
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
TSPII_SsmIf::~TSPII_SsmIf()
{
    uint8 aShelf;

    for (aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        free(itsPqwTimeout[aShelf]);
    }
    free(itsPqwTimeout);
}

/************************************BEGIN*************************************
*
* Function:    RefreshGet() class method
*
* Description:
*     Used to refresh the SsmIf entity attributes.
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
void TSPII_SsmIf::RefreshGet()
{
    int i;
    uint8  aShelf;
    uint8  aSlot;

    // Monitoring attributes
    for(aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
        {
            itsPqwTimeout[aShelf][aSlot] = GetPqwTimeout(aShelf, aSlot);
        }
    }

    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i] = GetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_LINE, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i));
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i] = GetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_PATH, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i));
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_ALT_LINE][i] = GetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_ALT_LINE, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i));
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        itsTohPriorAssign[i] = GetTohPriorityAssignment(i);
    }

    // Update the TohPqwEgressXconns table.
    itsTohPqwEgressXconnsMap = GetTohPqwEgressXconns();    // get snapshot

    // Update the TohPqwIngressXconns table.
    itsTohPqwIngressXconnsMap = GetTohPqwIngressXconns();   // get snapshot

    // Update the TohFppXconns table.
    itsTohFppXconnMap = GetTohFppXconns();   // get snapshot
}

/************************************BEGIN*************************************
*
* Function:    RefreshSet() class method
*
* Description:
*     Used to refresh the SsmIf configuration
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
void TSPII_SsmIf::RefreshSet()
{
    int i;
    TSPII_SsmIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;
    TSPII_SsmIfTohPqwIngXcMap::iterator tohPqwIngXcIter;
    TSPII_SsmIfTohFppXcMap::iterator tohFppXcIter;

     // write out the TOH Priority Table
     for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
     {
         SetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_LINE, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i), itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i]);
         SetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_PATH, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i), itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i]);
         SetTohPriorityTable(TSPII_SSMIF_PRIOR_TBL_ALT_LINE, static_cast<TSPII_SSMIF_PRIORITY_DEFECT>(i), itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_ALT_LINE][i]);
     }

     // write out the TOH Priority Assignments.
     for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
     {
         SetTohPriorityAssignment(i, itsTohPriorAssign[i]);
     }

#ifndef PSOSP

     // write out the TOH Egress Xconns
    for(tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.begin();
        tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end();
        ++tohPqwEgrXcIter)
    {
        AddTohPqwEgressXconn(tohPqwEgrXcIter->second.SrcShelf,
                             tohPqwEgrXcIter->second.SrcSlot,
                             tohPqwEgrXcIter->second.SrcPort,
                             tohPqwEgrXcIter->second.SrcSts,
                             tohPqwEgrXcIter->first.DstSts);
    }

     // write out the TOH Ingress Xconns
    for(tohPqwIngXcIter = itsTohPqwIngressXconnsMap.begin();
        tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end();
        ++tohPqwIngXcIter)
    {
        AddTohPqwIngressXconn(tohPqwIngXcIter->second.SrcPort,
                              tohPqwIngXcIter->second.SrcSts,
                              tohPqwIngXcIter->first.DstSts,
                              tohPqwIngXcIter->second.SrcCat);
    }

     // write out the TOH Fpp Xconns
    for(tohFppXcIter = itsTohFppXconnMap.begin();
        tohFppXcIter != itsTohFppXconnMap.end();
        ++tohFppXcIter)
    {
        AddTohFppXconn(tohFppXcIter->second.SrcPort,
                              tohFppXcIter->second.SrcSts,
                              tohFppXcIter->first.DstSts,
                              tohFppXcIter->second.SrcCat);
    }
#endif

}

/************************************BEGIN*************************************
*
* Function:    Reset() class method
*
* Description:
*     Used to reset the SsmIf entity attributes to a default state.
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
void TSPII_SsmIf::Reset()
{
    int i;
    uint8 aShelf;
    uint8 aSlot;

    TSPII_BaseIf::Reset();

    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i] = TSPII_SSMIF_PRIOR_NONE;
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i] = TSPII_SSMIF_PRIOR_NONE;
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        itsTohPriorAssign[i] = TSPII_SSMIF_PRIOR_TBL_LINE;
    }

    for(aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
        {
            itsPqwTimeout[aShelf][aSlot] = 0;
        }
    }

    itsTohPqwEgressXconnsMap.clear();
    itsTohPqwIngressXconnsMap.clear();
    itsTohFppXconnMap.clear();

    // Can't use clear here because of psos
    itsL2List.erase(itsL2List.begin(), itsL2List.end());
    itsL2ResourcesLow = false;
    itsL2ResourcesUnavailable = false;
}

/************************************BEGIN*************************************
*
* Function:    SetTohPriotityTable() class method
*
* Description: Sets the mode that the backplane
*
* Inputs:
*     theTable - which priority table to set.
*
*     theDefect - which defect in this table to set
*
*     thePriority - which priority to assign to the defect
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SsmIf::SetTohPriorityTable(TSPII_SSMIF_PRIORITY_TABLE theTable, TSPII_SSMIF_PRIORITY_DEFECT theDefect, TSPII_SSMIF_PRIORITY thePriority)
{
    if((theDefect < TSPII_SSMIF_PRIOR_DEF_MAX) &&
       (theTable < TSPII_SSMIF_PRIOR_TBL_MAX))
    {
        itsTohPriorTbl[theTable][theDefect] = thePriority;
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SsmIf::SetTohPriorityTable invalid arguments");
    }
}

/************************************BEGIN*************************************
*
* Function:    GetTohPriotityTable() class method
*
* Description: Gets the Toh Priority Table configuration
*
* Inputs:
*     theTable - which priority table to get.
*
*     theDefect - which defect in this table to get
*
*
* Outputs:
*     None
*
* Returns:
*     thePriority - which priority assigned to the defect
*
*************************************END***************************************
*/
TSPII_SSMIF_PRIORITY TSPII_SsmIf::GetTohPriorityTable(TSPII_SSMIF_PRIORITY_TABLE theTable, TSPII_SSMIF_PRIORITY_DEFECT theDefect)
{
    if((theDefect < TSPII_SSMIF_PRIOR_DEF_MAX) &&
       (theTable < TSPII_SSMIF_PRIOR_TBL_MAX))
    {
        return itsTohPriorTbl[theTable][theDefect];
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SsmIf::GetTohPriorityTable invalid arguments");
        return itsTohPriorTbl[0][0];
    }
}

/************************************BEGIN*************************************
*
* Function:    SetTohPriorityAssignment() class method
*
* Description: Sets the mode that the backplane will operate in
*
* Inputs:
*     thePort - the SFP to be assigned to this priority table (0-11 = SFP, 12 = XFP, 13 = WDM)
*
*     theTable -  the Priority Table to be assigned to this Port
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SsmIf::SetTohPriorityAssignment(uint8 thePort, TSPII_SSMIF_PRIORITY_TABLE theTable)
{
    if(thePort < TSPII_SSMIF_NUM_PORTS)
    {
        itsTohPriorAssign[thePort] = theTable;
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SsmIf::SetTohPriorityAssignment invalid port");
    }
}

/************************************BEGIN*************************************
*
* Function:    GetTohPriorityAssignment() class method
*
* Description: Get the Priority Table Assignment
*
* Inputs:
*     thePort - the SFP to be assigned to this priority table (0-11 = SFP, 12 = XFP, 13 = WDM)
*
* Outputs:
*     None
*
* Returns:
*     theTable -  the Priority Table that is assigned to this Port
*
*************************************END***************************************
*/
TSPII_SSMIF_PRIORITY_TABLE TSPII_SsmIf::GetTohPriorityAssignment(uint8 thePort)
{
    if(thePort < TSPII_SSMIF_NUM_PORTS)
    {
        return itsTohPriorAssign[thePort];
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SsmIf::SetTohPriorityAssignment invalid port");
        return itsTohPriorAssign[0];
    }
}

/************************************BEGIN*************************************
*
* Function:    AddTohPqwEgressXconn() class method
*
* Description: Sets up a new CES association of how to route Egress traffic.
*
* Inputs:
*     theSrcShelf - the Nano Source Shelf (0)
*
*     theSrcSlot - the Nano Source Slot (0-5)
*
*     theSrcPort - the Source Port (SFP) (0-11 = SFP, 12 = XFP, 13 = WDM, 14 = TTP)
*
*     theSrcSts - the Source Timeslot (0-191)
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
void TSPII_SsmIf::AddTohPqwEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts)
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwEgrXcKey   aKey;
    TSPII_SsmIfTohPqwEgrXcVal   aVal;
    TSPII_SsmIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

    aKey.DstSts   = theDstSts;

    aVal.SrcShelf = theSrcShelf;
    aVal.SrcSlot  = theSrcSlot;
    aVal.SrcPort  = theSrcPort;
    aVal.SrcSts   = theSrcSts;

    // Search for this element
    tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.find(aKey);

    // If element already exists, check if its value is changing
    if (tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end())
    {
        if (tohPqwEgrXcIter->second == aVal)
        {
            tohPqwEgrXcIter->second.IsDeleted      = false;
        }
        else
        {
            tohPqwEgrXcIter->second                = aVal;
            tohPqwEgrXcIter->second.IsNewOrChanged = true;
            tohPqwEgrXcIter->second.IsDeleted      = false;
        }
    }
    // Else element doesn't exist, so insert it
    else
    {
        aVal.IsNewOrChanged = true;
        aVal.IsDeleted      = false;
        itsTohPqwEgressXconnsMap.insert(TSPII_SsmIfTohPqwEgrXcMap::value_type(aKey, aVal));
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    DeleteTohPqwEgressXconn() class method
*
* Description:  Delete a TOH Protect association of how to route PQW traffic.
*
* Inputs:
*     theDstSts - the Destination Timeslot (0-191=IMUXL, 192-383=IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SsmIf::DeleteTohPqwEgressXconn(uint16 theDstSts)
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwEgrXcKey   aKey;
    TSPII_SsmIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

    aKey.DstSts = theDstSts;

    // Search for this element
    tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.find(aKey);

    if(tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end())
    {
        // element exsists - mark for deletion
        tohPqwEgrXcIter->second.IsDeleted = true;
    }
    else
    {
        // Element doesn't exist, so ignore this request
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    DeleteAllTohPqwEgressXconns() class method
*
* Description: Sets up a new TOH Egress PQW association.
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
void TSPII_SsmIf::DeleteAllTohPqwEgressXconns()
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

    // Mark all connections as deleted in the Xconn table
    for(tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.begin();
        tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end();
        tohPqwEgrXcIter++)
    {
        tohPqwEgrXcIter->second.IsDeleted = true;
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    CommitTohPqwEgressXconns() class method
*
* Description:  Commits all Egress PQW Xconns to the TOH chip
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
void TSPII_SsmIf::CommitTohPqwEgressXconns()
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwEgrXcMap::iterator  tohPqwEgrXcIter;

    // Commit all connections stored in the Xconn table
    for(tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.begin();
        tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end(); )
    {
        if(tohPqwEgrXcIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.erase(tohPqwEgrXcIter);
#endif
        }
        else if(tohPqwEgrXcIter->second.IsNewOrChanged)
        {
            // clear the changed flag since we are committing the changes
            tohPqwEgrXcIter->second.IsNewOrChanged = false;
            tohPqwEgrXcIter++;
        }
        else
        {
            // no change on this one.
            tohPqwEgrXcIter++;
        }
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    GetTohPqwEgressXconns() class method
*
* Description: Retrieves the currently activated TOH PQW Egress Xconns from the
*              hardware.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     a list of current TOH Egress Xconns
*
*************************************END***************************************
*/
TSPII_SsmIfTohPqwEgrXcMap& TSPII_SsmIf::GetTohPqwEgressXconns()
{
    return itsTohPqwEgressXconnsMap;
}


/************************************BEGIN*************************************
*
* Function:    AddTohPqwIngressXconn() class method
*
* Description: Sets up a new TOH Ingress PQW association.
*
* Inputs:
*     theSrcPort - the Source Port (SFP) (0-11 = SFP, 12 = XFP, 13 = WDM, 14 = TTP)
*
*     theSrcSts - the Source Timeslot (0-191)
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
void TSPII_SsmIf::AddTohPqwIngressXconn(uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts, CT_TEL_SignalType theSrcCat)
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwIngXcKey   aKey;
    TSPII_SsmIfTohPqwIngXcVal   aVal;
    TSPII_SsmIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

    aKey.DstSts   = theDstSts;

    aVal.SrcPort  = theSrcPort;
    aVal.SrcSts   = theSrcSts;
    aVal.SrcCat   = theSrcCat;
    // Search for this element
    tohPqwIngXcIter = itsTohPqwIngressXconnsMap.find(aKey);

    // If element already exists, check if its value is changing
    if (tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end())
    {
        if (tohPqwIngXcIter->second == aVal)
        {
            tohPqwIngXcIter->second.IsDeleted      = false;
        }
        else
        {
            tohPqwIngXcIter->second                = aVal;
            tohPqwIngXcIter->second.IsNewOrChanged = true;
            tohPqwIngXcIter->second.IsDeleted      = false;
        }
    }
    // Else element doesn't exist, so insert it
    else
    {
        aVal.IsNewOrChanged = true;
        aVal.IsDeleted      = false;
        itsTohPqwIngressXconnsMap.insert(TSPII_SsmIfTohPqwIngXcMap::value_type(aKey, aVal));
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    DeleteTohPqwIngressXconn() class method
*
* Description:  Delete a TOH PQW Ingress association..
*
* Inputs:
*     theDstSts - the Destination Timeslot (0-191=IMUXL, 192-383=IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SsmIf::DeleteTohPqwIngressXconn(uint16 theDstSts)
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwIngXcKey   aKey;
    TSPII_SsmIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

    aKey.DstSts = theDstSts;

    // Search for this element
    tohPqwIngXcIter = itsTohPqwIngressXconnsMap.find(aKey);

    if(tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end())
    {
        // element exsists - mark for deletion
        tohPqwIngXcIter->second.IsDeleted = true;
    }
    else
    {
        // Element doesn't exist, so ignore this request
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    DeleteAllTohPqwIngressXconns() class method
*
* Description: Sets up a new TOH PQW Ingress association.
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
void TSPII_SsmIf::DeleteAllTohPqwIngressXconns()
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

    // Mark all connections as deleted in the Xconn table
    for(tohPqwIngXcIter = itsTohPqwIngressXconnsMap.begin();
        tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end();
        tohPqwIngXcIter++)
    {
        tohPqwIngXcIter->second.IsDeleted = true;
    }
#endif
}

/************************************BEGIN*************************************
*
** Function:    CommitTohPqwIngressXconns() class method
*
* Description:  Commits all Ingress PQW Xconns to the TOH chip
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
void TSPII_SsmIf::CommitTohPqwIngressXconns()
{
#ifndef PSOSP
    TSPII_SsmIfTohPqwIngXcMap::iterator  tohPqwIngXcIter;

    // Commit all connections stored in the Xconn table
    for(tohPqwIngXcIter = itsTohPqwIngressXconnsMap.begin();
        tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end(); )
    {
        if(tohPqwIngXcIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            tohPqwIngXcIter = itsTohPqwIngressXconnsMap.erase(tohPqwIngXcIter);
#endif
        }
        else if(tohPqwIngXcIter->second.IsNewOrChanged)
        {
            // clear the flag since we are committing the changes
            tohPqwIngXcIter->second.IsNewOrChanged = false;
            tohPqwIngXcIter++;
        }
        else
        {
            // No change on this one.
            tohPqwIngXcIter++;
        }
    }
#endif
}

/************************************BEGIN*************************************
*
* Function:    GetTohPqwIngressXconns() class method
*
* Description: Retrieves the currently activated TOH PQW Ingress Xconns from the
*              hardware.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     a list of current TOH Ingress Xconns
*
*************************************END***************************************
*/
TSPII_SsmIfTohPqwIngXcMap& TSPII_SsmIf::GetTohPqwIngressXconns()
{
    return itsTohPqwIngressXconnsMap;
}



/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  AddTohFppXconn                                             **/
/**                                                                        **/
/**  Description:                                                          **/
/**      program the TOH FPP path connection matrix                        **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theSrcPort - 0 = Port XFP;                                        **/
/**                   1-12 = SFPs 1-12                                     **/
/**                   13 = Line XFP/MSA                                    **/
/**                   14 = TTP Port                                        **/
/**      theSrcSts  - range  0-191                                         **/
/**      theDstSts  - range 0-191                                          **/
/**      theSrcCat  - enum none,sts3c,sts12c,sts48,sts192c                 **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SsmIf::AddTohFppXconn( uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts, CT_TEL_SignalType theSrcCat )
{
#ifndef PSOSP
    TSPII_SsmIfTohFppXcKey   aKey;
    TSPII_SsmIfTohFppXcVal   aVal;
    TSPII_SsmIfTohFppXcMap::iterator tohFppIter;

    aKey.DstSts   = theDstSts;

    aVal.SrcPort  = theSrcPort;
    aVal.SrcSts   = theSrcSts;
    aVal.SrcCat   = theSrcCat;

    // Search for this element
    tohFppIter = itsTohFppXconnMap.find(aKey);

    // If element already exists, check if its value is changing
    if (tohFppIter != itsTohFppXconnMap.end())
    {
        if (tohFppIter->second == aVal)
        {
            tohFppIter->second.IsDeleted      = false;
        }
        else
        {
            tohFppIter->second                = aVal;
            tohFppIter->second.IsNewOrChanged = true;
            tohFppIter->second.IsDeleted      = false;
        }
    }
    // Else element doesn't exist, so insert it
    else
    {
        aVal.IsNewOrChanged = true;
        aVal.IsDeleted      = false;
        itsTohFppXconnMap.insert(TSPII_SsmIfTohFppXcMap::value_type(aKey, aVal));
    }
#endif

}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  DeleteAllTohFppXconn                                       **/
/**                                                                        **/
/**  Description:                                                          **/
/**      removes all toh FPP xconn entries from tohfppXcMap                **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SsmIf::DeleteAllTohFppXconn()
{
#ifndef PSOSP
    TSPII_SsmIfTohFppXcMap::iterator tohFppXcIter;

    // Mark all connections as deleted in the Xconn table
    for(tohFppXcIter = itsTohFppXconnMap.begin();
        tohFppXcIter != itsTohFppXconnMap.end();
        ++tohFppXcIter)
    {
        tohFppXcIter->second.IsDeleted = true;
    }
#endif

}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  DeleteTohFppXconn                                          **/
/**                                                                        **/
/**  Description:                                                          **/
/**      removes selected TOH fpp xconn from thosFPP XC map                **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theDstSts - 0-393                                                 **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SsmIf::DeleteTohFppXconn(uint16 theDstSts)
{
#ifndef PSOSP
    TSPII_SsmIfTohFppXcKey   aKey;
    TSPII_SsmIfTohFppXcMap::iterator tohFppXcIter;

    aKey.DstSts = theDstSts;

    // Search for this element
    tohFppXcIter = itsTohFppXconnMap.find(aKey);

    if(tohFppXcIter != itsTohFppXconnMap.end())
    {
        // element exsists - mark for deletion
        tohFppXcIter->second.IsDeleted = true;
    }
    else
    {
        // Element doesn't exist, so ignore this request
    }
#endif

}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  CommitTohFppXconn                                          **/
/**                                                                        **/
/**  Description:                                                          **/
/**      causes any FPP cross connect entry in map that is to be deleted   **/
/**      and erased. any new or changes to existing entries  are marked    **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SsmIf::CommitTohFppXconn()
{
#ifndef PSOSP
    TSPII_SsmIfTohFppXcMap::iterator  tohFppXcIter;

    // Commit all connections stored in the Xconn table
    for(tohFppXcIter = itsTohFppXconnMap.begin();
        tohFppXcIter != itsTohFppXconnMap.end(); )
    {
        if(tohFppXcIter->second.IsDeleted)
        {
            // remove the element since we are committing
#ifndef LINUX
            tohFppXcIter = itsTohFppXconnMap.erase(tohFppXcIter);
#endif
        }
        else if(tohFppXcIter->second.IsNewOrChanged)
        {
            // clear the flag since we are committing the changes
            tohFppXcIter->second.IsNewOrChanged = false;
            ++tohFppXcIter;
        }
        else
        {
            // No change on this one.
            ++tohFppXcIter;
        }
    }
#endif
}


/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  GetTohFppXconns                                            **/
/**                                                                        **/
/**  Description:                                                          **/
/**      returns  a reference to a TSPII_SsmIfTohFppXcMap                  **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      reference to TSPII_SsmIfTohFppXcMap                               **/
/**                                                                        **/
/************************************END*************************************/
TSPII_SsmIfTohFppXcMap& TSPII_SsmIf::GetTohFppXconns()
{
    return itsTohFppXconnMap;
}

/************************************BEGIN*************************************
*
* Function:    GetPqwTimeout() class method
*
* Description: Retrieves the currently defect counter for the PqwTimout indicator
*              in the hardware.
*
* Inputs:
*     theShelf - shelf number
*     theSlot - slot number within shelf
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SsmIf::GetPqwTimeout(uint8 theShelf, uint8 theSlot)
{
    if((theShelf < itsNumShelves) && (theSlot < itsNumSlots))
    {
        return(itsPqwTimeout[theShelf][theSlot]);
    }
    else
    {
        return 0;  // Fake the response - shelf or slot out of range
    }
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
*
*
* Returns:

*
*************************************END***************************************
*/
FC_Stream & TSPII_SsmIf::WriteObjectBinary(FC_Stream & theStream)
{
    int   i;
    int   aTemp;
    char  aStr[1024];
    TSPII_SsmIfTohPqwEgrXcMap::iterator  aToheIter;
    TSPII_SsmIfTohPqwIngXcMap::iterator  aTohiIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        theStream << static_cast<int>(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i]);
        theStream << static_cast<int>(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i]);
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        theStream << static_cast<int>(itsTohPriorAssign[i]);
    }

#ifndef PSOSP

    //////////////////////////////////////////////////////////////////////////
    // Write out the TOH Egress Xconns table
    aTemp = itsTohPqwEgressXconnsMap.size();
    theStream << aTemp;
    for(aToheIter=itsTohPqwEgressXconnsMap.begin(); aToheIter != itsTohPqwEgressXconnsMap.end(); ++aToheIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%03d,%03d,%03d,%03d,%01d,%01d",
                      aToheIter->first.DstSts, aToheIter->second.SrcShelf,
                      aToheIter->second.SrcSlot, aToheIter->second.SrcPort,
                      aToheIter->second.SrcSts, aToheIter->second.IsNewOrChanged,
                      aToheIter->second.IsDeleted);
        theStream << aStr;
    }

    //////////////////////////////////////////////////////////////////////////
    // Write out the TOH Ingress Xconns table
    aTemp = itsTohPqwIngressXconnsMap.size();
    theStream << aTemp;
    for(aTohiIter=itsTohPqwIngressXconnsMap.begin(); aTohiIter != itsTohPqwIngressXconnsMap.end(); ++aTohiIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%03d,%03d,%01d,%01d",
                      aTohiIter->first.DstSts, aTohiIter->second.SrcPort,
                      aTohiIter->second.SrcSts, aTohiIter->second.IsNewOrChanged,
                      aTohiIter->second.IsDeleted);
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
*
*     None
* Returns:
*
*
*************************************END***************************************
*/
FC_Stream & TSPII_SsmIf::ReadObjectBinary(FC_Stream & theStream)
{
    int i;
    int aTemp;
    int aCount;
    char aStr[1024];

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_ALT_LINE][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        theStream >> aTemp;
        itsTohPriorAssign[i] = static_cast<TSPII_SSMIF_PRIORITY_TABLE>(aTemp);
    }

#ifndef PSOSP
    ///////////////////////////////////////////////////////////////////////////
    // Read in the TOH Egress Xconn Table

    // first clear out the map
    itsTohPqwEgressXconnsMap.clear();

    // read in the number of TOH Egress Xconns
    theStream >> aCount;

    // The records must be converted from a char string
    while(aCount > 0)
    {
        TSPII_SsmIfTohPqwEgrXcKey  aKey;
        TSPII_SsmIfTohPqwEgrXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.DstSts = static_cast<uint16>(atoi(strtok(aStr, ",")));

        aVal.SrcShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcPort = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSts  = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwEgressXconnsMap.insert(TSPII_SsmIfTohPqwEgrXcMap::value_type(aKey, aVal));

        aCount--;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read in the TOH Ingress Xconn Table

    // first clear out the map
    itsTohPqwIngressXconnsMap.clear();

    // read in the size of the list of TOH Egress Xconns
    theStream >> aCount;

    // The records must be converted from a char
    while(aCount > 0)
    {
        TSPII_SsmIfTohPqwIngXcKey  aKey;
        TSPII_SsmIfTohPqwIngXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.DstSts = static_cast<uint16>(atoi(strtok(aStr, ",")));

        aVal.SrcPort = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSts  = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwIngressXconnsMap.insert(TSPII_SsmIfTohPqwIngXcMap::value_type(aKey, aVal));

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
*
*     None
* Returns:

*
*************************************END***************************************
*/
ostream & TSPII_SsmIf::WriteObject(ostream & theStream)
{
    int   i;
    int   aTemp;
    char  aStr[1024];
    TSPII_SsmIfTohPqwEgrXcMap::iterator  aToheIter;
    TSPII_SsmIfTohPqwIngXcMap::iterator  aTohiIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        aTemp = static_cast<int>(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i]);
        theStream << FC_InsertVar(aTemp);
        aTemp = static_cast<int>(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i]);
        theStream << FC_InsertVar(aTemp);
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        aTemp = static_cast<int>(itsTohPriorAssign[i]);
        theStream << FC_InsertVar(aTemp);
    }

#ifndef PSOSP
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    // Write out the TOH Egress Xconns table
    aTemp = itsTohPqwEgressXconnsMap.size();
    theStream << FC_InsertVar(aTemp);
    for(aToheIter=itsTohPqwEgressXconnsMap.begin(); aToheIter != itsTohPqwEgressXconnsMap.end(); ++aToheIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%03d,%03d,%03d,%03d,%01d,%01d",
                      aToheIter->first.DstSts, aToheIter->second.SrcShelf,
                      aToheIter->second.SrcSlot, aToheIter->second.SrcPort,
                      aToheIter->second.SrcSts, aToheIter->second.IsNewOrChanged,
                      aToheIter->second.IsDeleted);
        theStream << FC_InsertVar(aStr);
    }

    //////////////////////////////////////////////////////////////////////////
    // Write out the TOH Ingress Xconns table
    aTemp = itsTohPqwIngressXconnsMap.size();
    theStream << FC_InsertVar(aTemp);
    for(aTohiIter=itsTohPqwIngressXconnsMap.begin(); aTohiIter != itsTohPqwIngressXconnsMap.end(); ++aTohiIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%03d,%03d,%01d,%01d",
                      aTohiIter->first.DstSts, aTohiIter->second.SrcPort,
                      aTohiIter->second.SrcSts, aTohiIter->second.IsNewOrChanged,
                      aTohiIter->second.IsDeleted);
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
istream & TSPII_SsmIf::ReadObject(istream & theStream)
{
    int i;
    int aTemp;
    int aCount;
    char aStr[256];

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_ALT_LINE][i] = static_cast<TSPII_SSMIF_PRIORITY>(aTemp);
    }

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorAssign[i] = static_cast<TSPII_SSMIF_PRIORITY_TABLE>(aTemp);
    }

#ifndef PSOSP
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // Read in the TOH Egress Xconn Table

    // first clear out the map
    itsTohPqwEgressXconnsMap.clear();

    // read in the size of the list of TOH Egress Xconns
    theStream >> FC_ExtractVar(aCount);

    // The records must be converted from a char string
    while(aCount > 0)
    {
        TSPII_SsmIfTohPqwEgrXcKey  aKey;
        TSPII_SsmIfTohPqwEgrXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.DstSts = static_cast<uint16>(atoi(strtok(aStr, ",")));

        aVal.SrcShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcPort = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSts  = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwEgressXconnsMap.insert(TSPII_SsmIfTohPqwEgrXcMap::value_type(aKey, aVal));

        aCount--;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read in the TOH Ingress Xconn Table

    // first clear out the map
    itsTohPqwIngressXconnsMap.clear();

    // read in the size of the list of TOH Ingress Xconns
    theStream >> FC_ExtractVar(aCount);

    // The records must be converted from a char
    while(aCount > 0)
    {
        TSPII_SsmIfTohPqwIngXcKey  aKey;
        TSPII_SsmIfTohPqwIngXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.DstSts = static_cast<uint16>(atoi(strtok(aStr, ",")));

        aVal.SrcPort = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSts  = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwIngressXconnsMap.insert(TSPII_SsmIfTohPqwIngXcMap::value_type(aKey, aVal));

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
*     The test menu to display the Ssm attributes
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
void TSPII_SsmIf::Display(FC_Stream & theStream, int argc, char** argv)
{
    bool aSummary = false;
    bool aTohexc  = false;
    bool aTohixc  = false;
    bool aTohfxc  = false;

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
        aTohexc  = true;
        aTohixc  = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "tohexc") == 0))
    {
        aTohexc = true;
    }
    else if((argc == 1) && (strcmp(argv[0], "tohixc") == 0))
    {
        aTohixc = true;
    }

    else if((argc == 1) && (strcmp(argv[0], "tohfxc") == 0))
    {
        aTohfxc = true;
    }
    else
    {
        theStream << "   tspii display ssm           - a summary\n";
        theStream << "   tspii display ssm all       - everything\n";
        theStream << "   tspii display ssm tohexc    - TOH Egress Xconns\n";
        theStream << "   tspii display ssm tohixc    - TOH Ingress Xconns\n";
        theStream << "   tspii display ssm tohfxc    - TOH Fpp Xconns\n";
        return;
    }

    theStream << "  SSM Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    if(aSummary)
    {
        theStream << "    Priority Table                = " << DisplayPriorityTable()          << "\n";
        theStream << "    Priority Table Assign         = " << DisplayPriorityAssign()         << "\n";
        theStream << "    TOH Egress PQW Xconn Count    = " << DisplayTohPqwEgressXc(false)    << "\n";
        theStream << "    TOH Ingress PQW Xconn Count   = " << DisplayTohPqwIngressXc(false)   << "\n";
        theStream << "    TOH Fpp Xconn Count           = " << DisplayTohFppXc(false)   << "\n";
    }
    if(aTohexc)
    {
        theStream << "      TOH Egress PQW Xconns        = " << DisplayTohPqwEgressXc(true)    << "\n";
    }
    if(aTohixc)
    {
        theStream << "      TOH Ingress PQW Xconns       = " << DisplayTohPqwIngressXc(true)   << "\n";
    }
    if(aTohfxc)
    {
        theStream << "      TOH Fpp Xconns               = " << DisplayTohFppXc(true)   << "\n";
    }

    theStream << "    MONITORING\n";
    theStream << "      Pqw Timeout = " << DisplayPqwTimeout()             << "\n";
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
bool TSPII_SsmIf::Set(int argc, char ** argv)
{
    bool printUsage = true;

    if ((argc == 4) && (strcmp(argv[0], "prior") == 0))
    {
        TSPII_SSMIF_PRIORITY_TABLE Table;
        TSPII_SSMIF_PRIORITY_DEFECT Defect;
        TSPII_SSMIF_PRIORITY Priority;

        for (int i = 0; i < TSPII_SSMIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[1], TSPII_SSMIF_DISPLAY_PRIORTBL(i)) == 0)
        {
            Table = (TSPII_SSMIF_PRIORITY_TABLE)i;
            for (int j = 0; j <= TSPII_SSMIF_PRIOR_DEF_SDL; j++) if (strcmp(argv[2], TSPII_SSMIF_DISPLAY_PRIORDEF(j)) == 0)
            {
                Defect = (TSPII_SSMIF_PRIORITY_DEFECT)j;
                for (int k = 0; k <= TSPII_SSMIF_PRIOR_SFH; k++) if (strcmp(argv[3], TSPII_SSMIF_DISPLAY_PRIORITY(k)) == 0)
                {
                    Priority = (TSPII_SSMIF_PRIORITY)k;
                    SetTohPriorityTable(Table, Defect, Priority);
                    printUsage = false;
                    break;
                }
                break;
            }
            break;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "prasign") == 0))
    {
        uint8 Port = static_cast<uint8>(atoi(argv[1]));

        printUsage = true;
        for (int i = 0; i < TSPII_SSMIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[2], TSPII_SSMIF_DISPLAY_PRIORTBL(i)) == 0)
        {
            if((Port > 0) && (Port <= TSPII_SSMIF_NUM_PORTS))
            {
                SetTohPriorityAssignment(Port - 1, (TSPII_SSMIF_PRIORITY_TABLE)i);
                printUsage = false;
            }
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tohexca") == 0))
    {
        char aOutBuf[256];
        uint8 SrcShelf;
        uint8 SrcSlot;
        uint8 SrcPort;
        uint8 SrcSts;
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
        SrcPort = static_cast<uint8>(atoi(strtok(NULL, ",")));
        SrcSts = static_cast<uint8>(atoi(strtok(NULL, ",")));
        DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));
        if((SrcShelf > 0) && (SrcShelf <= itsNumShelves) &&
           (SrcSlot > 0) && (SrcSlot <= itsNumSlots) &&
           (SrcPort > 0) && (SrcPort <= TSPII_SSMIF_NUM_PORTS + 1) &&
           (SrcSts > 0) && (SrcSts <= (192 * itsNumImuxs)) &&
           (DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            AddTohPqwEgressXconn(SrcShelf - 1, SrcSlot - 1, SrcPort - 1, SrcSts - 1, DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tohexcd") == 0))
    {
        uint16 DstSts;

        DstSts = static_cast<uint16>(atoi(argv[1]));
        if((DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            DeleteTohPqwEgressXconn(DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohexcda") == 0))
    {
        DeleteAllTohPqwEgressXconns();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohexcc") == 0))
    {
        CommitTohPqwEgressXconns();
        printUsage = false;
    }
    else if ((argc == 3) && (strcmp(argv[0], "tohixca") == 0))
    {
        char aOutBuf[256];
        uint8 SrcPort;
        uint8 SrcSts;
        uint16 DstSts;
        CT_TEL_SignalType SrcCat = CT_TEL_SIGNAL_UNKNOWN;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
        SrcPort = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        SrcSts = static_cast<uint8>(atoi(strtok(NULL, ",")));
        DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));

        strcpy(aOutBuf,argv[2]);

        if (!strcmp(aOutBuf, "NC"))
        {
            SrcCat = CT_TEL_SIGNAL_UNKNOWN;
        }
        else if (!strcmp(aOutBuf, "STS3C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS3C;
        }
        else if (!strcmp(aOutBuf, "STS12C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS12C;
        }
        else if (!strcmp(aOutBuf, "STS48C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS48C;
        }
        else if (!strcmp(aOutBuf, "STS192C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS192C;
        }
        else
        {
            SrcCat = CT_TEL_SIGNAL_UNKNOWN;
        }

        if((SrcPort > 0) && (SrcPort <= TSPII_SSMIF_NUM_PORTS + 1) &&
           (SrcSts > 0) && (SrcSts <= (192)) &&
           (DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            AddTohPqwIngressXconn(SrcPort - 1, SrcSts - 1, DstSts - 1, SrcCat);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tohixcd") == 0))
    {
        uint16 DstSts;

        DstSts = static_cast<uint16>(atoi(argv[1]));
        if((DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            DeleteTohPqwIngressXconn(DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohfxcda") == 0))
    {
        DeleteAllTohFppXconn();
        printUsage = false;
    }
    else if ((argc == 3) && (strcmp(argv[0], "tohfxca") == 0))
    {
        char aOutBuf[256];
        uint8 SrcPort;
        uint8 SrcSts;
        uint16 DstSts;
        CT_TEL_SignalType SrcCat;

        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
        SrcPort = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        SrcSts = static_cast<uint8>(atoi(strtok(NULL, ",")));
        DstSts = static_cast<uint16>(atoi(strtok(NULL, ",")));

        strcpy(aOutBuf,argv[2]);

        if (!strcmp(aOutBuf, "NC"))
        {
            SrcCat = CT_TEL_SIGNAL_UNKNOWN  ;
        }
        else if (!strcmp(aOutBuf, "STS3C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS3C;
        }
        else if (!strcmp(aOutBuf, "STS12C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS12C;
        }
        else if (!strcmp(aOutBuf, "STS48C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS48C;
        }
        else if (!strcmp(aOutBuf, "STS192C"))
        {
            SrcCat = CT_TEL_SIGNAL_STS192C;
        }
        else
        {
            SrcCat = CT_TEL_SIGNAL_UNKNOWN;
        }


        if((SrcPort > 0) && (SrcPort <= TSPII_SSMIF_NUM_PORTS ) &&
           (SrcSts > 0) && (SrcSts <= (192)) &&
           (DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            AddTohFppXconn( SrcPort - 1, SrcSts - 1, DstSts - 1 ,SrcCat);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tohfxcd") == 0))
    {
        uint16 DstSts;

        DstSts = static_cast<uint16>(atoi(argv[1]));
        if((DstSts > 0) && (DstSts <= (192 * itsNumImuxs)))
        {
            // Convert it to "0" based numbering
            DeleteTohFppXconn(DstSts - 1);
            printUsage = false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohixcda") == 0))
    {
        DeleteAllTohPqwIngressXconns();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohixcc") == 0))
    {
        CommitTohPqwIngressXconns();
        printUsage = false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "tohfxcc") == 0))
    {
        CommitTohFppXconn();
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "serdes") == 0))
    {
        static strstream buf;
        FC_Stream stream(buf, FC_Stream::BINARY);
        TSPII_SsmRegion * SsmRegion = TSPII_SubApplication::GetInstance()->GetSsm();
        if(strcmp(argv[1], "write") == 0)
        {
            stream << (*SsmRegion)[0];    // write
            printUsage = false;
        }
        else if(strcmp(argv[1], "read") == 0)
        {
            stream >> (*SsmRegion)[0];    // read
            printUsage = false;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    prior           <table> <defect> <priority>\n"
                   "                     table=line|path|alt(alternate line)\n"
                   "                     defect=tims|aisl|sfl|aisp|lopp|uneqp|timp|plmp|sfp|pdi|sdp|sdl\n"
                   "                     priority=none|sd|sfl|sfh\n"
                   "    prasign         <port=1-14> <table=line|path|alt>\n"
                   "                     port=1-12=sfp 13=clientxfp 14=linexfp 15=ttp\n"
                   "----------------------------------------------------------\n"
                   "    tohexca         <sshelf,sslot,sport,ssts,dsts>     Add Egress Xconn\n"
                   "    tohexcd         <dsts>    Delete Egress Xconn\n"
                   "                     sshelf=1, sslot=1-6, sport=1-15, ssts=1-192, dsts=1-192L 193-384P\n"
                   "    tohexcda         Delete all Egress Xconn\n"
                   "    tohexcc          Commit Egress Xconn\n"
                   "----------------------------------------------------------\n"
                   "    tohixca         <sport,ssts,dsts,cat>     Add Ingress Xconn\n"
                   "    tohixcd         <dsts>    Delete Ingress Xconn\n"
                   "                     sport=1-15, ssts=1-192, dsts=1-192L 193-384P\n"
                   "                     cat = NC, STS3C,STS12C,STS48C,STS192C\n"
                   "    tohixcda         Delete all Ingress Xconn\n"
                   "    tohixcc          Commit Ingress Xconn\n"
                   "----------------------------------------------------------\n"
                   "    tohfxca         <sport,ssts,dsts,cat>     Add Fpp Xconn\n"
                   "    tohfxcd         <dsts>    Delete Fpp Xconn\n"
                   "                     sport=1-15, ssts=1-192, dsts=1-192L 193-384P\n"
                   "                     cat = NC, STS3C,STS12C,STS48C,STS192C\n"
                   "    tohfxcda         Delete all Fpp Xconn\n"
                   "    tohfxcc          Commit Fpp Xconn\n"
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
bool TSPII_SsmIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 4) && (strcmp(argv[0], "pqwto") == 0))
    {
        uint8 aShelf;
        uint8 aSlot;

        aShelf = static_cast<uint8>(atoi(argv[1]));
        if(itsForceShelf)
        {
            aShelf = 1;  // For now force to shelf 1
        }
        aSlot = static_cast<uint8>(atoi(argv[2]));
        if((aShelf > 0) && (aShelf <= itsNumShelves) &&
           (aSlot > 0) && (aShelf <= itsNumSlots))
        {
            // Convert it to "0" based numbering
            if (strcmp(argv[3], "on") == 0)
            {
                if (!TSPII_DEFECT(itsPqwTimeout[aShelf-1][aSlot-1])) itsPqwTimeout[aShelf-1][aSlot-1]++;
            }
            else if (strcmp(argv[3], "off") == 0)
            {
                if (TSPII_DEFECT(itsPqwTimeout[aShelf-1][aSlot-1])) itsPqwTimeout[aShelf-1][aSlot-1]++;
            }
            else
            {
                printUsage = true;
            }
        }
        else
        {
            // Out of range
            printUsage = true;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "startl2stat") == 0))
    {
        StartEqptStatsCollection(TSPII_SSMIF_LAYER_L2);
    }
    else if ((argc == 1) && (strcmp(argv[0], "getl2Stat") == 0))
    {
        GetEqptStats(TSPII_SSMIF_LAYER_L2, &itsL2List);
    }
    else if ((argc == 2) && (strcmp(argv[0], "addl2string") == 0))
    {
        char theCurL2ListEntry[80];
        uint16 aLen = strlen(argv[1]);

        if (aLen > 79)
        {
            aLen = 79;
        }
        memcpy(theCurL2ListEntry, argv[1], aLen);
        theCurL2ListEntry[aLen] = NULL;
        string theStrCurL2ListEntry = theCurL2ListEntry;

        itsL2List.push_front(theStrCurL2ListEntry);
    }
    else if ((argc == 1) && (strcmp(argv[0], "dumpl2list") == 0))
    {
        DumpEqptStats(TSPII_SSMIF_LAYER_L2);
    }
    else if ((argc == 2) && strcmp(argv[0], "reslow") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsL2ResourcesLow = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsL2ResourcesLow = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "resunavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsL2ResourcesUnavailable = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsL2ResourcesUnavailable = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "dumpl2diags") == 0))
    {
        DumpDiags(TSPII_SSMIF_LAYER_L2);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    pqwto           <shelf> <slot> <on|off>\n"
                   "                     shelf=1, slot=1-N\n"
                   "    startl2stat     \n"
                   "    getl2Stat       \n"
                   "    addl2string     <string>\n"
                   "    dumpl2list      \n"
                   "    reslow          <on|off>\n"
                   "    resunavail      <on|off>\n"
                   "    dumpl2diags     " << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_SsmIf::Display(FC_Stream & theStream)
{
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayPriorityTable()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    aStr = "Line: ";
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        sprintf(aBuf, "%s,", TSPII_SSMIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_LINE][i]));
        aStr += aBuf;
    }
    aStr += "\n                                    Path: ";
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        sprintf(aBuf, "%s,", TSPII_SSMIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_PATH][i]));
        aStr += aBuf;
    }
    aStr += "\n                                 AltLine: ";
    for(i = 0; i < TSPII_SSMIF_PRIOR_DEF_MAX; i++)
    {
        sprintf(aBuf, "%s,", TSPII_SSMIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_ALT_LINE][i]));
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayPriorityAssign()
{
    int     i;
    char    aBuf[128];
    string  aStr;

    for(i = 0; i < TSPII_SSMIF_NUM_PORTS; i++)
    {
        sprintf(aBuf, "%s,", TSPII_SSMIF_DISPLAY_PRIORTBL(itsTohPriorAssign[i]));
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayPqwTimeout()
{
    uint8   aShelf;
    uint8   aSlot;
    char    aBuf[128];
    string  aStr;

    for(aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        sprintf(aBuf, "\n\tShelf %2d: ", aShelf+1);
        aStr += aBuf;
        for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
        {
            if (aSlot == 8)
            {
                sprintf(aBuf, "%3s %5u,\n", TEXT_ON_OFF(itsPqwTimeout[aShelf][aSlot] & 1), itsPqwTimeout[aShelf][aSlot]);
            }
            else if (aSlot == 9)
            {
                sprintf(aBuf, "\t%13s %5u, ", TEXT_ON_OFF(itsPqwTimeout[aShelf][aSlot] & 1), itsPqwTimeout[aShelf][aSlot]);
            }
            else
            {
                sprintf(aBuf, "%3s %5u, ", TEXT_ON_OFF(itsPqwTimeout[aShelf][aSlot] & 1), itsPqwTimeout[aShelf][aSlot]);
            }
            aStr += aBuf;
        }
    }
    return aStr;
}


///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayTohPqwEgressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SsmIfTohPqwEgrXcMap::iterator  aToheIter;

    sprintf(aBuf, "%d <shelf,sslot,sport,ssts,dsts - isNewChanged isDeleted>\n", itsTohPqwEgressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aToheIter=itsTohPqwEgressXconnsMap.begin(); aToheIter != itsTohPqwEgressXconnsMap.end(); ++aToheIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%03d,%03d,%03d,%03d,%05d - %1d %1d", aToheIter->second.SrcShelf + 1,
                                                      aToheIter->second.SrcSlot + 1,
                                                      aToheIter->second.SrcPort + 1,
                                                      aToheIter->second.SrcSts + 1,
                                                      aToheIter->first.DstSts + 1,
                                                      aToheIter->second.IsNewOrChanged,
                                                      aToheIter->second.IsDeleted);

            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayTohPqwIngressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SsmIfTohPqwIngXcMap::iterator  aTohiIter;

    sprintf(aBuf, "%d <sport,ssts,dsts,cat - isNewChanged isDeleted>\n", itsTohPqwIngressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aTohiIter=itsTohPqwIngressXconnsMap.begin(); aTohiIter != itsTohPqwIngressXconnsMap.end(); ++aTohiIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%03d,%03d,%05d,%s - %1d %1d", aTohiIter->second.SrcPort + 1,
                                            aTohiIter->second.SrcSts + 1,
                                            aTohiIter->first.DstSts + 1,
                                            DISPLAY_SIGNAL_TYPE(aTohiIter->second.SrcCat),
                                            aTohiIter->second.IsNewOrChanged,
                                            aTohiIter->second.IsDeleted);
            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SsmIf::DisplayTohFppXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SsmIfTohFppXcMap::iterator  aTohiIter;

    sprintf(aBuf, "%d <sport,ssts,dsts,cat - isNewChanged isDeleted>\n", itsTohFppXconnMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aTohiIter=itsTohFppXconnMap.begin(); aTohiIter != itsTohFppXconnMap.end(); ++aTohiIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%03d,%03d,%05d,%s - %1d %1d", aTohiIter->second.SrcPort + 1,
                                            aTohiIter->second.SrcSts + 1,
                                            aTohiIter->first.DstSts + 1,
                                            DISPLAY_SIGNAL_TYPE(aTohiIter->second.SrcCat),
                                            aTohiIter->second.IsNewOrChanged,
                                            aTohiIter->second.IsDeleted);
            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool TSPII_SsmIf::StartEqptStatsCollection(TSPII_SSMIF_LAYER theLayer)
{
    bool retVal = false;

    if (theLayer == TSPII_SSMIF_LAYER_L2)
    {
        // Can't use clear here because of psos
        itsL2List.erase(itsL2List.begin(), itsL2List.end());
        retVal = true;
    }

    return(retVal);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_SsmIf::GetEqptStats(TSPII_SSMIF_LAYER theLayer, list<string> *theList)
{
    bool retVal = false;

    if (theLayer == TSPII_SSMIF_LAYER_L2)
    {
        *theList = itsL2List;
        retVal = true;
    }

    return(retVal);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_SsmIf::DumpEqptStats(TSPII_SSMIF_LAYER theLayer)
{
    if (theLayer == TSPII_SSMIF_LAYER_L2)
    {
        bool ret = GetEqptStats(TSPII_SSMIF_LAYER_L2, &itsL2List);

        if (ret)
        {
            list<string>::iterator iter;

            fc_cout << "  L2 List Stats :" << endl;
            for ( iter=itsL2List.begin() ; iter != itsL2List.end(); iter++ )
            {
                fc_cout << "Entry: " << *iter << endl;
            }
        }

    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_SsmIf::GetDiagState(TSPII_SSMIF_LAYER theLayer, TSPII_SSMIF_DIAG theDiag)
{
    bool state = false;

    if (theLayer == TSPII_SSMIF_LAYER_L2)
    {
        if (theDiag == TSPII_SSMIF_DIAG_RESOURCE_LOW)
        {
            state = itsL2ResourcesLow;
        }
        else if (theDiag == TSPII_SSMIF_DIAG_RESOURCE_UNAVAIL)
        {
            state = itsL2ResourcesUnavailable;
        }
    }

    return(state);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_SsmIf::DumpDiags(TSPII_SSMIF_LAYER theLayer)
{
    if (theLayer == TSPII_SSMIF_LAYER_L2)
    {
        bool aState = false;
        fc_cout << "  L2 Diags :" << endl;

        aState = GetDiagState(TSPII_SSMIF_LAYER_L2, TSPII_SSMIF_DIAG_RESOURCE_LOW);
        fc_cout << "     L2 Resource Low          = " << DISPLAY_BOOL(aState) << endl;

        aState = GetDiagState(TSPII_SSMIF_LAYER_L2, TSPII_SSMIF_DIAG_RESOURCE_UNAVAIL);
        fc_cout << "     L2 Resource Unavailable  = " << DISPLAY_BOOL(aState) << endl;
    }
}
