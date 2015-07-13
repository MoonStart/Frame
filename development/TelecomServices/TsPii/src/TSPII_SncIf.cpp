/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SncIf.cpp
* Type:    C++ source
* Author:  Jessica Chen, - June 2010
* Description:
*     Definition of the class TSPII_SncIf which models the simulation
*     SNC Card specific Interface entity.
*
*
*************************************END***************************************
*/
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_SncIf.h"
#include <strstream>
#include "TsPii/TSPII_Region.h"
#include "TsPii/TSPII_SubApplication.h"
#include <cstring>
#include <CommonTypes/CT_OduDefinitions.h>

#define GET_THE_ENABLE(arg) \
    ((strcmp(arg,"true")==0) ? true : false)
#define GET_CHANNEL_NUMBER(arg) \
    ((static_cast<unsigned int>(atoi(arg)) <= TSPII_SNCIF_NUM_CHANNEL) ? atoi(arg) : 255)
/************************************BEGIN*************************************
*
* Function:    TSPII_SncIf constructor
*
* Description:
*     TSPII_SncIfIf class constructor
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
TSPII_SncIf::TSPII_SncIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, bool theForceShelf) :
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
* Function:    TSPII_SncIf destructor
*
* Description:
*     TSPII_SncIf class destructor
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
TSPII_SncIf::~TSPII_SncIf()
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
*     Used to refresh the SncIf entity attributes.
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
void TSPII_SncIf::RefreshGet()
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

    for(i = 0; i < TSPII_SNCIF_DEFECT_UNKNOWN; i++)
    {
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i] = GetTohPriorityTable(TSPII_SNCIF_PRIOR_TBL_0, static_cast<TSPII_SNCIF_DEFECT_GROUP>(i));
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i] = GetTohPriorityTable(TSPII_SNCIF_PRIOR_TBL_1, static_cast<TSPII_SNCIF_DEFECT_GROUP>(i));
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i] = GetTohPriorityTable(TSPII_SNCIF_PRIOR_TBL_2, static_cast<TSPII_SNCIF_DEFECT_GROUP>(i));
        //itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_3][i] = GetTohPriorityTable(TSPII_SNCIF_PRIOR_TBL_3, static_cast<TSPII_SNCIF_DEFECT_GROUP>(i));
    }

    for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        itsTohPriorAssign[i] = GetTohPriorityAssignment(i);
    }

    // Update the TohPqwEgressXconns table.
    itsTohPqwEgressXconnsMap = GetTohPqwEgressXconns();    // get snapshot

    // Update the TohPqwIngressXconns table.
    itsTohPqwIngressXconnsMap = GetTohPqwIngressXconns();   // get snapshot

    for(i=0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        itsTxPQM[i] = GetTxPQM(i);
        itsRxPQM[i] = GetRxPQM(i);
        itsFppEnbl[i] = GetFppEnabled(i);
        itsFppSqlEnbl[i] = GetFppSquelchEnabled(i);
        itsSrcTfcEnbl[i] = GetSrcTrafficEnabled(i);
        itsSquelchHoldOffDelay[i] = GetSquelchHoldOffDelay(i);
        itsRxSFHigh[i] = GetRxSFHigh(i);
        itsRxSFLow[i] = GetRxSFLow(i);
        itsRxSD[i] = GetRxSD(i);
        itsTxSFHigh[i] = GetTxSFHigh(i);
        itsTxSFLow[i] = GetTxSFLow(i);
        itsTxSD[i] = GetTxSD(i);
        itsTxHwPQWSql[i] = GetTxHwPQWSquelch(i);
        itsRxHwPQWSql[i] = GetRxHwPQWSquelch(i);
        itsTxPQWInvalid[i] = GetTxPQWInvalid(i);
        itsRxPQWInvalid[i] = GetRxPQWInvalid(i);
    }

    for(i=0; i < TSPII_SNCIF_APS_CHANNEL; i++)
    {
        itsRxLocalApsBytes[i] = GetRxLocalApsBytes(i);
        itsRxRemoteApsBytes[i] = GetRxRemoteApsBytes(i);
    }
//    itsPqwTransmit = GetPqwTransmitEnable();
}

/************************************BEGIN*************************************
*
* Function:    RefreshSet() class method
*
* Description:
*     Used to refresh the SncIf configuration
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
void TSPII_SncIf::RefreshSet()
{
    int i;
    TSPII_SncIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;
    TSPII_SncIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

     // write out the TOH Priority Table

    // write out the TOH Priority Assignments.
     for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
     {
         SetTohPriorityAssignment(i, itsTohPriorAssign[i]);
     }

#ifndef PSOSP

     // write out the TOH Egress Xconns
    for(tohPqwEgrXcIter = itsTohPqwEgressXconnsMap.begin();
        tohPqwEgrXcIter != itsTohPqwEgressXconnsMap.end();
        tohPqwEgrXcIter++)
    {
        AddTohPqwEgressXconn(tohPqwEgrXcIter->second.SrcShelf,
                             tohPqwEgrXcIter->second.SrcSlot,
                             tohPqwEgrXcIter->second.SrcOtnPqwChannel,
                             tohPqwEgrXcIter->first.DstOtnPqwChannel);
    }

     // write out the TOH Ingress Xconns
    for(tohPqwIngXcIter = itsTohPqwIngressXconnsMap.begin();
        tohPqwIngXcIter != itsTohPqwIngressXconnsMap.end();
        tohPqwIngXcIter++)
    {
        AddTohPqwIngressXconn(tohPqwIngXcIter->first.OtnPqwChannel,
                              tohPqwIngXcIter->second.cLogicalOduId,
                              tohPqwIngXcIter->second.sLogicalOduId,
                              tohPqwIngXcIter->second.tLogicalOduId);

    }
#endif

    for(i=0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
       EnableRxSwPqwInterrupt(i, itsRxSwPqwIntEnbl[i]);
       EnableRxHwPqwInterrupt(i, itsRxHwPqwIntEnbl[i]);
       EnableTxHwPqwInterrupt(i, itsTxHwPqwIntEnbl[i]);
       SetTxPQM(i, itsTxPQM[i], 0xffff);

       SetFppEnabled(i, itsFppEnbl[i]);
       SetFppSquelchEnabled(i, itsFppSqlEnbl[i]);
       SetSrcTrafficEnabled(i, itsSrcTfcEnbl[i]);
       SetSquelchHoldOffDelay(i, itsSquelchHoldOffDelay[i]);
    }

    for(i=0; i < TSPII_SNCIF_APS_CHANNEL; i++)
    {
        EnableLocalApsInterrupt(itsLocalApsInterruptCfg[i].oduId, 
                                itsLocalApsInterruptCfg[i].apsChannel,
                                i,
                                itsLocalApsInterruptCfg[i].enable);
        EnableRemoteApsInterrupt(itsRemoteApsInterruptCfg[i].shelfId, 
                                 itsRemoteApsInterruptCfg[i].slotId,
                                 itsRemoteApsInterruptCfg[i].apsIndex,
                                 i,
                                 itsRemoteApsInterruptCfg[i].enable);
    }

    EnableAps(itsApsEnable);
    //EnablePqwTransmit(itsPqwTransmit);
}

/************************************BEGIN*************************************
*
* Function:    Reset() class method
*
* Description:
*     Used to reset the SncIf entity attributes to a default state.
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
void TSPII_SncIf::Reset()
{
    int i;
    uint8 aShelf;
    uint8 aSlot;

    TSPII_BaseIf::Reset();

    for(i = 0; i < TSPII_SNCIF_PRIOR_DEF_MAX; i++)
    {
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i] = TSPII_SNCIF_PRIOR_NONE;
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i] = TSPII_SNCIF_PRIOR_NONE;
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i] = TSPII_SNCIF_PRIOR_NONE;
    }


    for(aShelf = 0; aShelf < itsNumShelves; aShelf++)
    {
        for(aSlot = 0; aSlot < itsNumSlots; aSlot++)
        {
            itsPqwTimeout[aShelf][aSlot] = 0;
        }
    }

    for(i=0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        itsTohPriorAssign[i] = TSPII_SNCIF_PRIOR_TBL_0;
        itsRxSwPqwIntEnbl[i] = false;
        itsRxHwPqwIntEnbl[i] = false;
        itsTxHwPqwIntEnbl[i] = false;
        itsTxPQM[i] = 0;
        itsRxPQM[i] = 0;
        itsFppEnbl[i] = false;
        itsFppSqlEnbl[i] = false;
        itsSrcTfcEnbl[i] = false;
        itsRxSFHigh[i] = 0;
        itsRxSFLow[i] = 0;
        itsRxSD[i] = 0;
        itsTxSFHigh[i] = 0;
        itsTxSFLow[i] = 0;
        itsTxSD[i] = 0;
        itsTxHwPQWSql[i] = false;
        itsRxHwPQWSql[i] = false;
        itsOduStreamPqwIndex[i] = TSPII_SNCIF_INVALID_PQW_CHANNEL;
        itsSquelchHoldOffDelay[i] = 0;
        itsTxPQWInvalid[i] = true;
        itsRxPQWInvalid[i] = true;
    }
    itsTohPqwEgressXconnsMap.clear();
    itsTohPqwIngressXconnsMap.clear();
    itsPqwTransmit = false;
    itsdebuglevel = DEBUG_OFF;

    itsApsEnable = false;

    //here reset 160 channels,but we only use the front 16 channel for aps
    resetChannelPropertyVector<LocalApsInterruptCfg>(itsLocalApsInterruptCfg);
    resetChannelPropertyVector<RemoteApsInterruptCfg>(itsRemoteApsInterruptCfg);
    resetChannelPropertyVector<uint32>(itsRxLocalApsBytes);
    resetChannelPropertyVector<uint32>(itsRxRemoteApsBytes);

    for(i=0; i < TSPII_SNCIF_APS_CHANNEL; i++)
    {
        itsLocalApsInterruptCfg[i].enable  = false;
        itsRemoteApsInterruptCfg[i].enable = false;
        itsRxLocalApsBytes[i]  = 0;
        itsRxRemoteApsBytes[i] = 0;
    }
}


/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  SetTohPriorityTable                                        **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Sets the Defect Indirect Control/Address/BitMask/Priority         **/
/**      Registers                                                         **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theDefectGroup - enum value {ODU_SF, ODU_SD, OTU_SF, OTU_SD,      **/
/**                       TCM_SF, TCM_SD}                                  **/
/**      theDefectType  - Enum {TCM, Client, Server}                       **/
/**      theFramer      - Enum {Port_Odu0, Port_Odu1, Port_Odu2}           **/
/**      theDefectIndex - int                                              **/
/**      thePriority    - enum {SFH, SFL, SD, None}                        **/
/**      theTable       - int                                              **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SncIf::SetTohPriorityTable(TSPII_SNCIF_DEFECT_GROUP theDefectGroup,
                                      TSPII_SNCIF_DEFECT_TYPE theDefectType,
                                      TSPII_SNCIF_FRAMER theFramer,
                                      uint8 theDefectIndex,
                                      TSPII_SNCIF_PRIORITY thePriority,
                                      TSPII_SNCIF_PRIORITY_TABLE theTable)
{
    if((theDefectGroup < TSPII_SNCIF_DEFECT_UNKNOWN) &&
       (theTable < TSPII_SNCIF_PRIOR_TBL_MAX))
    {
        itsTohPriorTbl[theTable][theDefectGroup] = thePriority;
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SncIf::SetTohPriorityTable invalid arguments");
    }
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  GetTohPriorityTable                                        **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Return the Priority table                                         **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theTable       - enum TSPII_SNCIF_PRIORITY _TABLE                 **/
/**      theDefectGroup - enum TSPII_SNCIF_DEFECT_GROU                     **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      enum TSPII_SNCIF_PRIORITY                                         **/
/**                                                                        **/
/************************************END*************************************/
TSPII_SNCIF_PRIORITY TSPII_SncIf::GetTohPriorityTable(TSPII_SNCIF_PRIORITY_TABLE theTable, TSPII_SNCIF_DEFECT_GROUP theDefectGroup)
{
    if((theDefectGroup < TSPII_SNCIF_DEFECT_UNKNOWN) &&
       (theTable < TSPII_SNCIF_PRIOR_TBL_MAX))
    {
        return itsTohPriorTbl[theTable][theDefectGroup];
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SncIf::GetTohPriorityTable invalid arguments");
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
void TSPII_SncIf::SetTohPriorityAssignment(uint8 theOtnPqwChannel, TSPII_SNCIF_PRIORITY_TABLE theTable)
{
    if(theOtnPqwChannel < TSPII_SNCIF_NUM_CHANNEL)
    {
        itsTohPriorAssign[theOtnPqwChannel] = theTable;
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SncIf::SetTohPriorityAssignment invalid port");
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
TSPII_SNCIF_PRIORITY_TABLE TSPII_SncIf::GetTohPriorityAssignment(uint8 theOtnPqwChannel)
{
    if(theOtnPqwChannel < TSPII_SNCIF_NUM_CHANNEL)
    {
        return itsTohPriorAssign[theOtnPqwChannel];
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "TSPII_SncIf::SetTohPriorityAssignment invalid port");
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
*     theSrcOtnPqwChannel - the Source Port (SFP) (0-11 = SFP, 12 = XFP, 13 = WDM, 14 = TTP)
*
*     theDstOtnPqwChannel - the Destination Timeslot (0-191 = IMUXL, 192-383 = IMUXP)
*
* Outputs:
*     None
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SncIf::AddTohPqwEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot,
                                         uint8 theSrcOtnPqwChannel, uint8 theDstOtnPqwChannel)
{
#ifndef PSOSP
    TSPII_SncIfTohPqwEgrXcKey   aKey;
    TSPII_SncIfTohPqwEgrXcVal   aVal;
    TSPII_SncIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

    aKey.DstOtnPqwChannel   = theDstOtnPqwChannel;

    aVal.SrcShelf = theSrcShelf;
    aVal.SrcSlot  = theSrcSlot;
    aVal.SrcOtnPqwChannel  = theSrcOtnPqwChannel;


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
        itsTohPqwEgressXconnsMap.insert(TSPII_SncIfTohPqwEgrXcMap::value_type(aKey, aVal));
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
void TSPII_SncIf::DeleteTohPqwEgressXconn(uint8 theDstOtnPqwChannel)
{
#ifndef PSOSP
    TSPII_SncIfTohPqwEgrXcKey   aKey;
    TSPII_SncIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

    aKey.DstOtnPqwChannel = theDstOtnPqwChannel;

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
void TSPII_SncIf::DeleteAllTohPqwEgressXconns()
{
#ifndef PSOSP
    TSPII_SncIfTohPqwEgrXcMap::iterator tohPqwEgrXcIter;

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
TSPII_SncIfTohPqwEgrXcMap& TSPII_SncIf::GetTohPqwEgressXconns()
{
    return itsTohPqwEgressXconnsMap;
}
/************************************BEGIN*************************************
*
* Function:    TSPII_SncHwDrvIf::AddTohPqwIngressXconn() class method
*
* Description:
*       Sets up a new TOH Ingress PQW association.
*       This mapping is telling the fpga to poll defects from src Oduk,
*       and put the resulting PQW message in dst pqw channel
*
* Inputs:
*       theOtnPqwChannel  - The destination channel ID (0-191 IMUX-L) / (192-383 IMUX-P)
*       theClientOduId   - The source ODU ID for Client interfaces()
*       theServerOduId   - The source ODU ID for Servers interfaces()
*       theTcmId         - The source ODU ID for TCM circuits()
*
* Outputs:
*       None
*
* Returns:
*       None
*
*************************************END**************************************/
void TSPII_SncIf::AddTohPqwIngressXconn(uint8 theOtnPqwChannel, uint32 theClientOduId, uint32 theServerOduId, uint32 theTcmId)
{
#ifndef PSOSP
    TSPII_SncIfTohPqwIngXcKey   aKey;
    TSPII_SncIfTohPqwIngXcVal   aVal;
    TSPII_SncIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

    aKey.OtnPqwChannel   = theOtnPqwChannel;

    if(theClientOduId != TSPII_SNCIF_NO_CLIENT_ODU_ID)
    {
        aVal.cLogicalOduId   = theClientOduId;
    }
    if(theTcmId !=TSPII_SNCIF_NO_TCM_ODU_ID )
    {
        aVal.tLogicalOduId = theTcmId;
    }
    if(theServerOduId != TSPII_SNCIF_NO_SERVER_ODU_ID )
    {
           aVal.sLogicalOduId = theServerOduId;
    }


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
        itsTohPqwIngressXconnsMap.insert(TSPII_SncIfTohPqwIngXcMap::value_type(aKey, aVal));
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
void TSPII_SncIf::DeleteTohPqwIngressXconn(uint8 theOtnPqwChannel)
{
#ifndef PSOSP
    TSPII_SncIfTohPqwIngXcKey   aKey;
    TSPII_SncIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

    aKey.OtnPqwChannel = theOtnPqwChannel;

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
void TSPII_SncIf::DeleteAllTohPqwIngressXconns()
{
#ifndef PSOSP
    TSPII_SncIfTohPqwIngXcMap::iterator tohPqwIngXcIter;

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
TSPII_SncIfTohPqwIngXcMap& TSPII_SncIf::GetTohPqwIngressXconns()
{
    return itsTohPqwIngressXconnsMap;
}



/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  SetPqwTimeoutInterruptEnable                               **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Enables specific Pqw Timeout interrupts                           **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theEnable - bool - true enables                                   **/
/**      shelf     - Zero based value for shelf                            **/
/**      slot      - Zero based value for slots                            **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SncIf::SetPqwTimeoutInterruptEnable(bool theEnable, uint16 shelf , uint8 slot )
{
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
uint32 TSPII_SncIf::GetPqwTimeout(uint8 theShelf, uint8 theSlot)
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
* Function:    EnableRxSwPqwInterrupt() class method
*
* Description: Enable the Rx Remote OTN PQW SW Change Interrupt
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnable        - True: Enable
*                        Flase: Disable
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::EnableRxSwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable)
{
    itsRxSwPqwIntEnbl[theOtnPqwChannel] = theEnable;
}

/************************************BEGIN*************************************
*
* Function:    EnableRxHwPqwInterrupt() class method
*
* Description: Enable the Rx Remote OTN PQW HW Change Interrupt
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnable        - True: Enable
*                        Flase: Disable
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::EnableRxHwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable)
{
    itsRxHwPqwIntEnbl[theOtnPqwChannel] = theEnable;
}

/************************************BEGIN*************************************
*
* Function:    EnableTxHwPqwInterrupt() class method
*
* Description: Enable the Tx Local OTN PQW SW Change Interrupt
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnable        - True: Enable
*                        Flase: Disable
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::EnableTxHwPqwInterrupt(uint8 theOtnPqwChannel, bool theEnable)
{
    itsTxHwPqwIntEnbl[theOtnPqwChannel] = theEnable;
}

/************************************BEGIN*************************************
*
* Function:    SetTxPQM() class method
*
* Description: Set the Tx Local OTN PQW SW Programmable Status bits
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     thePQM           - the value of Programmable Status bits
*     theMask          - the mask for Programmable Status bits
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::SetTxPQM(uint8 theOtnPqwChannel, uint16 thePQM, uint16 theMask)
{
   itsTxPQM[theOtnPqwChannel]= (thePQM&(theMask&0x7FFF));
}
/************************************BEGIN*************************************
*
* Function:    GetTxPQM() class method
*
* Description: Get the value of the Tx Local OTN PQW SW Programmable Status bits
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     thePQM           - the value of Programmable Status bits
*
*************************************END***************************************
*/
uint16 TSPII_SncIf::GetTxPQM(uint8 theOtnPqwChannel) const
{
    return itsTxPQM[theOtnPqwChannel];
}

/************************************BEGIN*************************************
*
* Function:    GetRxPQM() class method
*
* Description: Get the value of the Rx Remote OTN PQW SW Programmable Status bits
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     thePQM           - the value of Programmable Status bits
*
*************************************END***************************************
*/
uint16 TSPII_SncIf::GetRxPQM(uint8 theOtnPqwChannel)
{
    return itsRxPQM[theOtnPqwChannel];     //default = 0;
}

/************************************BEGIN*************************************
*
* Function:    SetFppEnabled() class method
*
* Description: Enable the OTN FPP
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnabled       - True: Enable
*                      - False: Disable
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::SetFppEnabled(uint8 theOtnPqwChannel, bool theEnable)
{
    itsFppEnbl[theOtnPqwChannel]=theEnable;
}

/************************************BEGIN*************************************
*
* Function:    GetFppEnabled() class method
*
* Description: Get the value of the OTN FPP
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     theEnabled           - the value of the OTN FPP Registers
*
*************************************END***************************************
*/
bool TSPII_SncIf::GetFppEnabled(uint8 theOtnPqwChannel) const
{
    return itsFppEnbl[theOtnPqwChannel];
}

/************************************BEGIN*************************************
*
* Function:    SetFppSquelchEnabled() class method
*
* Description: Enable the OTN Hardware Squelch Enable
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnabled       - True: Enable
*                      - False: Disable
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::SetFppSquelchEnabled(uint8 theOtnPqwChannel, bool theEnable)
{
    itsFppSqlEnbl[theOtnPqwChannel]=theEnable;
}

/************************************BEGIN*************************************
*
* Function:    GetFppSquelchEnabled() class method
*
* Description: Get the value of the OTN Hardware Squelch Enable
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     theEnabled           - the value of OTN Hardware Squelch Enable Registers
*
*************************************END***************************************
*/
bool TSPII_SncIf::GetFppSquelchEnabled(uint8 theOtnPqwChannel) const
{
    return itsFppSqlEnbl[theOtnPqwChannel];
}

/************************************BEGIN*************************************
*
* Function:    SetSrcTrafficEnabled() class method
*
* Description: Enable the OTN
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*     theEnabled       - True: Enable
*                      - False: Disable
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::SetSrcTrafficEnabled(uint8 theOtnPqwChannel, bool theEnable)
{
    itsSrcTfcEnbl[theOtnPqwChannel]=theEnable;
}

/************************************BEGIN*************************************
*
* Function:    GetSrcTrafficEnabled() class method
*
* Description: Get the value of the OTN
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     theEnabled           - the value of OTN Hardware Squelch Enable Registers
*
*************************************END***************************************
*/
bool TSPII_SncIf::GetSrcTrafficEnabled(uint8 theOtnPqwChannel) const
{
    return itsSrcTfcEnbl[theOtnPqwChannel];
}

/************************************BEGIN*************************************
*
* Function:    GetRxSFHigh() class method
*
* Description: Retrieves the currently defect counter for Remote PQW Path Alarm Severity-SFHigh
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetRxSFHigh(uint8 theOtnPqwChannel)
{
    return itsRxSFHigh[theOtnPqwChannel]; //default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetRxSFLow() class method
*
* Description: Retrieves the currently defect counter for Remote PQW Path Alarm Severity--SFLow
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*    uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetRxSFLow(uint8 theOtnPqwChannel)
{
    return itsRxSFLow[theOtnPqwChannel];  //default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetRxSD() class method
*
* Description: Retrieves the currently defect counter for Remote PQW Path Alarm Severity--SD
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetRxSD(uint8 theOtnPqwChannel)
{
    return itsRxSD[theOtnPqwChannel];   // default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetTxSFHigh() class method
*
* Description: Retrieves the currently defect counter for Local PQW Path Alarm Severity--SFHigh
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetTxSFHigh(uint8 theOtnPqwChannel)
{
    return itsTxSFHigh[theOtnPqwChannel];    //default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetTxSFLow() class method
*
* Description: Retrieves the currently defect counter for  Local PQW Path Alarm Severity--SFLow
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetTxSFLow(uint8 theOtnPqwChannel)
{
    return itsTxSFLow[theOtnPqwChannel];  //default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetTxSD() class method
*
* Description: Retrieves the currently defect counter for Local PQW Path Alarm Severity--SD
*              in the hardware.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     uint32 value odd = active, even = inactive
*
*************************************END***************************************
*/
uint32 TSPII_SncIf::GetTxSD(uint8 theOtnPqwChannel)
{
    return itsTxSD[theOtnPqwChannel];      // default = 0;
}

/************************************BEGIN*************************************
*
* Function:    GetTxHwPQWSquelch() class method
*
* Description: Get the value of the Local HW Squelch bit
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     theEnabled           - the value of Local HW Squelch bit
*
*************************************END***************************************
*/
bool TSPII_SncIf::GetTxHwPQWSquelch(uint8 theOtnPqwChannel)
{
    return itsTxHwPQWSql[theOtnPqwChannel];  //default = false;
}

/************************************BEGIN*************************************
*
* Function:    GetRxHwPQWSquelch() class method
*
* Description: Get the value of the Remote HW Squelch bit
*              Registers.
*
* Inputs:
*     theOtnPqwChannel - The source channel ID
*
* Outputs:
*     None
*
* Returns:
*     theEnabled           - the value of Remote HW Squelch bit
*
*************************************END***************************************
*/
bool TSPII_SncIf::GetRxHwPQWSquelch(uint8 theOtnPqwChannel)
{
    return itsRxHwPQWSql[theOtnPqwChannel];  //default = false;
}

/************************************BEGIN*************************************
*
* Function:    SetGeneralSncControlParams() class method
*
* Description: Function used to setup general SNC control related parameters
*
* Inputs:
*     uint32 theShelf,
*     uint32 theSlot
*
* Outputs:
*     None
*
* Returns:
*     None
*
*************************************END***************************************
*/
void TSPII_SncIf::SetGeneralSncControlParams(uint32 theShelf, uint32 theSlot)
{
    //Default, does nothing
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  EnablePqwTransmit                                          **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Enables the PQW transmit interface                                **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theEnable - true enables                                          **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SncIf::EnablePqwTransmit(bool theEnable)
{
    itsPqwTransmit = theEnable;
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  GetPqwTransmitEnable                                       **/
/**                                                                        **/
/**  Description:                                                          **/
/**      returns PqwTranmsit enable state                                  **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**                                                                        **/
/**                                                                        **/
/************************************END*************************************/
bool TSPII_SncIf::GetPqwTransmitEnable() const
{
    return itsPqwTransmit;
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  SetOduStreamPqwIndex                                       **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Setup the FPP mapping for the specified ODU stream                **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theOduStreamId   - uint8 0 - 31 identifies the ODU stream         **/
/**      theOtnPqwChannel - uint8 0 -16                                    **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SncIf::SetOduStreamPqwIndex(uint8 theOduStreamId, uint8 theOtnPqwChannel)
{
    itsOduStreamPqwIndex[theOduStreamId] = theOtnPqwChannel;
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  GetOduStreamPqwIndex                                       **/
/**                                                                        **/
/**  Description:                                                          **/
/**      returns state of the FPP Odu mapping                              **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theOduStreamId   uint8 {0-31}  identifies the odu stream          **/
/**                                                                        **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      uint8  pqw channel associated with this odu stream                **/
/**                                                                        **/
/************************************END*************************************/
uint8 TSPII_SncIf::GetOduStreamPqwIndex(uint8 theOduStreamId) const
{
    return itsOduStreamPqwIndex[theOduStreamId];
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  SetSquelchHoldOffDelay                                     **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Setup the amount of time(in msecs) to wait before squelching      **/
/**      traffic on a failure                                              **/
/**  Inputs:                                                               **/
/**      theOtnPqwChannel - uint8 0 -16                                    **/
/**      theDelay         - amount of time to wait(in msecs)               **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_SncIf::SetSquelchHoldOffDelay(uint8 theOtnPqwChannel, uint32 theDelay)
{
    itsSquelchHoldOffDelay[theOtnPqwChannel] = theDelay;
}

/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  GetSquelchHoldOffDelay                                     **/
/**                                                                        **/
/**  Description:                                                          **/
/**      returns current squelching delay provisioned                      **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theOtnPqwChannel - uint8 0 -16                                    **/
/**                                                                        **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      uint8  pqw channel associated with this odu stream                **/
/**                                                                        **/
/************************************END*************************************/
uint32 TSPII_SncIf::GetSquelchHoldOffDelay(uint8 theOtnPqwChannel) const
{
    return itsSquelchHoldOffDelay[theOtnPqwChannel];
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
FC_Stream & TSPII_SncIf::WriteObjectBinary(FC_Stream & theStream)
{
    int   i;
    int   aTemp;
    char  aStr[1024];
    TSPII_SncIfTohPqwEgrXcMap::iterator  aToheIter;
    TSPII_SncIfTohPqwIngXcMap::iterator  aTohiIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SNCIF_PRIOR_DEF_MAX; i++)
    {
        theStream << static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i]);
        theStream << static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i]);
        theStream << static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i]);
    }

    for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        theStream << static_cast<int>(itsTohPriorAssign[i]);
        theStream << static_cast<uint32>(itsRxLocalApsBytes[i]);
        theStream << static_cast<uint32>(itsRxRemoteApsBytes[i]);
    }

#ifndef PSOSP

    //////////////////////////////////////////////////////////////////////////
    // Write out the TOH Egress Xconns table
    aTemp = itsTohPqwEgressXconnsMap.size();
    theStream << aTemp;
    for(aToheIter=itsTohPqwEgressXconnsMap.begin(); aToheIter != itsTohPqwEgressXconnsMap.end(); ++aToheIter)
    {
        // KEY + VAL
        sprintf(aStr, "%05d,%03d,%03d,%03d,%01d,%01d",
                      aToheIter->first.DstOtnPqwChannel, aToheIter->second.SrcShelf,
                      aToheIter->second.SrcSlot, aToheIter->second.SrcOtnPqwChannel,
                      aToheIter->second.IsNewOrChanged,
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
        sprintf(aStr, "%03d,%012lu,%012lu, %012lu,%01d,%01d",
                      aTohiIter->first.OtnPqwChannel, aTohiIter->second.cLogicalOduId,
                      aTohiIter->second.sLogicalOduId,
                      aTohiIter->second.tLogicalOduId,
                      aTohiIter->second.IsNewOrChanged,
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
FC_Stream & TSPII_SncIf::ReadObjectBinary(FC_Stream & theStream)
{
    int i;
    int aTemp;
    int aCount;
    char aStr[1024];

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SNCIF_PRIOR_DEF_MAX; i++)
    {
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        theStream >> aTemp;
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        //theStream >> aTemp;
        //itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_3][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
    }

    for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        theStream >> aTemp;
        itsTohPriorAssign[i] = static_cast<TSPII_SNCIF_PRIORITY_TABLE>(aTemp);
        theStream >> aTemp;
        itsRxLocalApsBytes[i] = static_cast<uint32>(aTemp);
        theStream >> aTemp;
        itsRxRemoteApsBytes[i] = static_cast<uint32>(aTemp);
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
        TSPII_SncIfTohPqwEgrXcKey  aKey;
        TSPII_SncIfTohPqwEgrXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.DstOtnPqwChannel = static_cast<uint8>(atoi(strtok(aStr, ",")));

        aVal.SrcShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwEgressXconnsMap.insert(TSPII_SncIfTohPqwEgrXcMap::value_type(aKey, aVal));

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
        TSPII_SncIfTohPqwIngXcKey  aKey;
        TSPII_SncIfTohPqwIngXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> aStr;

        // Parse string and populate key/val
        aKey.OtnPqwChannel = static_cast<uint8>(atoi(strtok(aStr, ",")));

        //aVal.LogicalOduId = static_cast<uint32>(atol(strtok(NULL, ",")));
        aVal.cLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.sLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.tLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwIngressXconnsMap.insert(TSPII_SncIfTohPqwIngXcMap::value_type(aKey, aVal));

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
ostream & TSPII_SncIf::WriteObject(ostream & theStream)
{
    int   i;
    int   aTemp;
    char  aStr[1024];
    TSPII_SncIfTohPqwEgrXcMap::iterator  aToheIter;
    TSPII_SncIfTohPqwIngXcMap::iterator  aTohiIter;

    // Update Gets
    UpdateValues();
    RefreshGet();

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SNCIF_PRIOR_DEF_MAX; i++)
    {
        aTemp = static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i]);
        theStream << FC_InsertVar(aTemp);
        aTemp = static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i]);
        theStream << FC_InsertVar(aTemp);
        aTemp = static_cast<int>(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i]);
        theStream << FC_InsertVar(aTemp);
    }

    for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
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
        sprintf(aStr, "%05d,%03d,%03d,%03d,%01d,%01d",
                      aToheIter->first.DstOtnPqwChannel, aToheIter->second.SrcShelf,
                      aToheIter->second.SrcSlot, aToheIter->second.SrcOtnPqwChannel,
                      aToheIter->second.IsNewOrChanged,
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
        sprintf(aStr, "%03d,%012lu,%012lu,%012lu,%01d,%01d",
                      aTohiIter->first.OtnPqwChannel,
                      aTohiIter->second.cLogicalOduId,
                      aTohiIter->second.sLogicalOduId,
                      aTohiIter->second.tLogicalOduId,
                      aTohiIter->second.IsNewOrChanged,
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
istream & TSPII_SncIf::ReadObject(istream & theStream)
{
    int i;
    int aTemp;
    int aCount;
    char aStr[256];

    // Monitoring

    // Configuration
    for(i = 0; i < TSPII_SNCIF_PRIOR_DEF_MAX; i++)
    {
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
        //theStream >> FC_ExtractVar(aTemp);
        //itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_3][i] = static_cast<TSPII_SNCIF_PRIORITY>(aTemp);
    }

    for(i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        theStream >> FC_ExtractVar(aTemp);
        itsTohPriorAssign[i] = static_cast<TSPII_SNCIF_PRIORITY_TABLE>(aTemp);
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
        TSPII_SncIfTohPqwEgrXcKey  aKey;
        TSPII_SncIfTohPqwEgrXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.DstOtnPqwChannel = static_cast<uint8>(atoi(strtok(aStr, ",")));

        aVal.SrcShelf = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.SrcOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwEgressXconnsMap.insert(TSPII_SncIfTohPqwEgrXcMap::value_type(aKey, aVal));

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
        TSPII_SncIfTohPqwIngXcKey  aKey;
        TSPII_SncIfTohPqwIngXcVal  aVal;

        // Read each Xconn record as a comma seperated string
        theStream >> FC_ExtractVar(aStr);

        // Parse string and populate key/val
        aKey.OtnPqwChannel = static_cast<uint8>(atoi(strtok(aStr, ",")));

        //aVal.LogicalOduId = static_cast<uint32>(atol(strtok(NULL, ",")));
        aVal.cLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.sLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.tLogicalOduId = static_cast<uint32>(strtoul(strtok(NULL, ","),NULL,0));
        aVal.IsNewOrChanged = atoi(strtok(NULL, ",")) ? true: false;
        aVal.IsDeleted = atoi(strtok(NULL, ",")) ? true: false;

        // Insert element into map
        itsTohPqwIngressXconnsMap.insert(TSPII_SncIfTohPqwIngXcMap::value_type(aKey, aVal));

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
*     The test menu to display the Snc attributes
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
void TSPII_SncIf::Display(FC_Stream & theStream, int argc, char** argv)
{
    bool aDisplayUsage = true;
    //for display table
    bool aSummary    = false;
    bool aPriTab     = false;
    bool aTohexc     = false;
    bool aTohixc     = false;
    bool aEnableInt  = false;
    bool aEnableFpp  = false;
    bool aEnableSrc  = false;
    bool aEnablePqw  = false;
    bool aCountTx    = false;
    bool aCountRx    = false;
    bool aPqmTx      = false;
    bool aPqmRx      = false;
    bool aApsLocal   = false;
    bool aApsRemote  = false;
    bool aApsInterrupt = false;
    bool aTimeOut    = false;
    //for only single channel display
    uint8 aChannel    = 255; //default 255
    bool aEnableIntCh = false;
    bool aEnableFppCh = false;
    bool aEnableSrcCh = false;
    bool aEnablePqwCh = false;
    bool aCountTxCh   = false;
    bool aCountRxCh   = false;
    bool aPqmTxCh     = false;
    bool aPqmRxCh     = false;
    bool apqw         = false;

    //show channel Ch
    const char *aCh = "Ch";
    const char *aSl = "SL";
    const char *aTrue = "T";
    const char *aFalse ="F";
    const char *aOn = "ON";
    const char *aOff ="OFF";

    //

    // Update
    UpdateValues();
    RefreshGet();

    // if(argc == 0)
    //{//display help info
        //aSummary = true;
    //}
    //else
    if((argc == 1) && (strcmp(argv[0], "all") == 0))
    {
        aSummary = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "pritab") == 0))
    {
        aPriTab = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "tohexc") == 0))
    {
        aTohexc = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "tohixc") == 0))
    {
        aTohixc = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "enable") == 0))
    {
        aEnableInt = true;
        aEnableFpp = true;
        aEnableSrc = true;
        aEnablePqw = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "count") == 0))
    {
        aCountTx = true;
        aCountRx = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "pqm") == 0))
    {
        aPqmTx     = true;
        aPqmRx     = true;
        aDisplayUsage = false;
    }
    else if((argc == 1) && (strcmp(argv[0], "timeout") == 0))
    {
        aTimeOut    = true;
        aDisplayUsage = false;
    }

    else if((argc == 2) && (strcmp(argv[0], "pqw") ==0))
    {
        aChannel = GET_CHANNEL_NUMBER((argv[1]));
        if((aChannel !=255) && (aChannel >0))
        {
            --aChannel;   //need to subtract one since TSPII user interface is ones's base
            apqw = true;
            aDisplayUsage = false;

        }
    }
    else if(((argc == 2) && (strcmp(argv[0], "enable") == 0))||((argc == 3) && (strcmp(argv[0], "enable") == 0)&&(strcmp(argv[2], "all") == 0)))
    {
        if((strcmp(argv[1],"int")==0)||(strcmp(argv[1],"all")==0))
        {
            aEnableInt = true;
            aDisplayUsage = false;
        }
        else if((strcmp(argv[1],"fpp")==0)||(strcmp(argv[1],"all")==0))
        {
            aEnableFpp = true;
            aDisplayUsage = false;
        }
        else if((strcmp(argv[1],"src")==0)||(strcmp(argv[1],"all")==0))
        {
            aEnableSrc = true;
            aDisplayUsage = false;
        }
        else if((strcmp(argv[1],"pqw")==0)||(strcmp(argv[1],"all")==0))
        {
            aEnablePqw = true;
            aDisplayUsage = false;
        }
    }
    else if(((argc == 2) && (strcmp(argv[0], "count") == 0))||((argc == 3) && (strcmp(argv[0], "count") == 0)&&(strcmp(argv[2], "all") == 0)))
    {
        if((strcmp(argv[1],"tx")==0)||(strcmp(argv[1],"all")==0))
        {
            aCountTx = true;
            aDisplayUsage = false;
        }
        else if((strcmp(argv[1],"rx")==0)||(strcmp(argv[1],"all")==0))
        {
            aCountRx = true;
            aDisplayUsage = false;
        }
    }
    else if(((argc == 2) && (strcmp(argv[0], "pqm") == 0))||((argc == 3) && (strcmp(argv[0], "pqm") == 0)&&(strcmp(argv[2], "all") == 0)))
    {
        if((strcmp(argv[1],"tx")==0)||(strcmp(argv[1],"all")==0))
        {
            aPqmTx     = true;
            aDisplayUsage = false;
        }
        else if((strcmp(argv[1],"rx")==0)||(strcmp(argv[1],"all")==0))
        {
            aPqmRx     = true;
            aDisplayUsage = false;
        }
    }
    else if(((argc == 3) && (strcmp(argv[0], "enable") == 0)&&(strcmp(argv[2], "all") != 0)))
    {
        //enable int|fpp|src|pqw|all  [0-15]
        aChannel = GET_CHANNEL_NUMBER((argv[2]));
        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;   //need to subtract one since TSPII user interface is ones's base
            if((strcmp(argv[1],"int")==0)||(strcmp(argv[1],"all")==0))
           {
                aEnableIntCh = true;
                aDisplayUsage = false;
           }
           if((strcmp(argv[1],"fpp")==0)||(strcmp(argv[1],"all")==0))
           {
                aEnableFppCh = true;
                aDisplayUsage = false;
           }
           if((strcmp(argv[1],"src")==0)||(strcmp(argv[1],"all")==0))
           {
                aEnableSrcCh = true;
                aDisplayUsage = false;
            }
            if((strcmp(argv[1],"pqw")==0)||(strcmp(argv[1],"all")==0))
            {
                aEnablePqwCh = true;
                aDisplayUsage = false;
            }
        }
    }

    else if(((argc == 3) && (strcmp(argv[0], "count") == 0)&&(strcmp(argv[2], "all") != 0)))
    {
        //count  tx |rx |all          [0-15]
        aChannel = GET_CHANNEL_NUMBER((argv[2]));
        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;   //need to subtract one since TSPII user interface is ones's base
            if((strcmp(argv[1],"tx")==0)||(strcmp(argv[1],"all")==0))
           {
                aCountTxCh = true;
                aDisplayUsage = false;
            }
            if((strcmp(argv[1],"rx")==0)||(strcmp(argv[1],"all")==0))
            {
                 aCountRxCh = true;
                 aDisplayUsage = false;
            }
        }
    }
    else if(((argc == 3) && (strcmp(argv[0], "pqm") == 0)&&(strcmp(argv[2], "all") != 0)))
    {//pqm    tx |rx |all          [0-15]
        aChannel = GET_CHANNEL_NUMBER((argv[2]));
        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;   //need to subtract one since TSPII user interface is ones's base
            if((strcmp(argv[1],"tx")==0)||(strcmp(argv[1],"all")==0))
            {
                aPqmTxCh = true;
                aDisplayUsage = false;
            }
            if((strcmp(argv[1],"rx")==0)||(strcmp(argv[1],"all")==0))
            {
                aPqmRxCh = true;
                aDisplayUsage = false;
            }

        }
    }
    else if((argc == 2) && (strcmp(argv[0], "aps") == 0))
    {//aps    remote |local |int        
        if(strcmp(argv[1],"remote")==0)
        {
            aApsRemote = true;
            aDisplayUsage = false;
        }
        else if(strcmp(argv[1],"local")==0)
        {
            aApsLocal = true;
            aDisplayUsage = false;
        }
        else if(strcmp(argv[1],"int")==0)
        {
            aApsInterrupt = true;
            aDisplayUsage = false;
        }
    }

    if(aDisplayUsage)
    {
        theStream << "   tspii display snc                                     - a command list\n";
        theStream << "   tspii display snc pqw channel                         - display pqw configuration and status\n";
        theStream << "   tspii display snc all                                 - everything\n";
        theStream << "   tspii display snc tohexc                                  - 2.TOH Egress Xconns\n";
        theStream << "   tspii display snc tohixc                                  - 3.TOH Ingress Xconns\n";
        theStream << "   tspii display snc enable int|fpp|src|pqw|all  [0-15]|all  - 4.channel[0-15].Enable Interrupt\n";
        theStream << "                                                                 ,FPP/PQW(Squelch),Source Traffic\n";
        theStream << "   tspii display snc count  tx |rx |all          [0-15]|all  - 5.channel[0-15].Tx Defects counter\n";
        theStream << "                                                             - 6.channel[0-15].Rx Defects counter\n";
        theStream << "   tspii display snc pqm    tx |rx |all          [0-15]|all  - 7.channel[0-15].Tx PQM value\n";
        theStream << "                                                             - 8.channel[0-15].Rx PQM value\n";
        theStream << "   tspii display snc aps    remote |local |int               - 9.channel[0-15].Rx Remote APS value\n";
        theStream << "                                                             - 10.channel[0-15].Rx Local APS value\n";
        theStream << "                                                             - 11.Local and Remote APS Interrupt enabled\n";        
        theStream << "   tspii display snc timeout                                 - 12.PQW timeout\n";
        theStream << "   tspii display snc defecttab                             - Displays the defect prioriy table\n";
        return;
    }


    theStream << "  SNC Configuration/Status\n";
    if(apqw)
    {
        theStream <<"   OTN PQW Channel "<<DisplayOtnPqwChannel(aChannel,(aChannel+1),aCh,false)<<":\n";
        theStream << "    \nCONFIGURATION\n";
        theStream << DisplayOtnDefectGroup() <<endl;
        theStream << DisplayOtnPriorityTable(itsTohPriorAssign[aChannel])<<endl;
        theStream << DisplayOtnPqwChannelConfiguration(aChannel)<<endl;

        theStream << DisplayOtnPqwChannelStatus(aChannel)<<endl;
    }
    // aSummary will be displayed step by step.
    if(aPriTab||aSummary)
    {
        theStream << "                OTN Priority Table                                                                       \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << DisplayOtnDefectGroup()                                            <<" \n";
        theStream << DisplayOtnPriorityTable()                                            <<" \n";
        theStream << "                OTN Priority Table Assign                                                                \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)<<" \n";
        theStream << "Table?:  "<<DisplayOtnPriorityAssign()                              <<" \n";

    }
    if(aTohexc||aSummary)
    {
        theStream << "                OTN TOH Egress PQW Xconns                                                                \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        if(aTohexc)
        {
            theStream << DisplayOtnTohPqwEgressXc(true)                                   <<" \n";
        }
        else
        {
            theStream << DisplayOtnTohPqwEgressXc(false)                                  << "\n";
        }

    }
    if(aTohixc||aSummary)
    {
        theStream << "                OTN TOH Ingress PQW Xconns                                                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        if(aTohixc)
        {
            theStream << DisplayOtnTohPqwIngressXc(true)                                  << "\n";
        }
        else
        {
            theStream << DisplayOtnTohPqwIngressXc(false)                                 << "\n";
        }

    }
    if(aEnableInt||aSummary)
    {
        theStream << "                 OTN Rx Sw Interrupt Enable                                                              \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)             <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsRxSwPqwIntEnbl[0],false) <<" \n";
        theStream << "                 OTN Rx Hw Interrupt Enable                                                              \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)             <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsRxHwPqwIntEnbl[0],false) <<" \n";
        theStream << "                 OTN Tx Hw Interrupt Enable                                                              \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)             <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsTxHwPqwIntEnbl[0],false) <<" \n";
    }
    if(aEnableFpp||aSummary)
    {
        theStream << "                 OTN FPP Channel Enable                                                                  \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)                                <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsFppEnbl[0],false)        <<" \n";
        theStream << "                 OTN FPP Squelch Enable                                                                  \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)                                <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsFppSqlEnbl[0],false)     <<" \n";
    }
    if(aEnableSrc||aSummary)
    {
         theStream << "                 OTN Source Traffic Enable                                                               \n";
         theStream << "-------------------------------------------------------------------------------------------------------------------\n";
         theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)                                <<" \n";
         theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsSrcTfcEnbl[0],false)     <<" \n";
    }
    if(aEnablePqw||aSummary)
    {
        theStream << "                 OTN Tx Hw PQW Squelch Enable                                                            \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)                                <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsTxHwPQWSql[0],false)     <<" \n";
        theStream << "                 OTN Rx Hw PQW Squelch Enable                                                            \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel: "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)                                <<" \n";
        theStream << "Enabled?:"<<DisplayOtnPqwEnabled(0,TSPII_SNCIF_NUM_CHANNEL,aTrue,aFalse,&itsRxHwPQWSql[0],false)     <<" \n";
    }
    if(aCountTx||aSummary)
    {
        theStream << "                 OTN Tx SF High                                                                          \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                                     <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsTxSFHigh[0])                                              <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)                               <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsTxSFHigh[8])                        <<" \n";
        theStream << "                 OTN Tx SF lOW                                                                           \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                                     <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsTxSFLow[0])                                               <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)                               <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsTxSFLow[8])                         <<" \n";
        theStream << "                 OTN Tx SD                                                                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                                     <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsTxSD[0])                                                  <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)                               <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsTxSD[8])                            <<" \n";
    }
    if(aCountRx||aSummary)
    {
        theStream << "                 OTN Rx SF High                                                                          \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                                     <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsRxSFHigh[0])                                              <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)                               <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsRxSFHigh[8])                        <<" \n";
        theStream << "                 OTN Rx SF lOW                                                                           \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                                     <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsRxSFLow[0])                                               <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)                               <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsRxSFLow[8])                         <<" \n";
        theStream << "                 OTN Rx SD                                                                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,8,aCh,true)                                    <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,8,&itsRxSD[0])                               <<" \n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(8,TSPII_SNCIF_NUM_CHANNEL,aCh,true)              <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(8,TSPII_SNCIF_NUM_CHANNEL,&itsRxSD[8])     <<" \n";
    }

    if(aPqmTx||aSummary)
    {
        theStream << "                 OTN Tx PQM  (Remote PQW SW programmable Status bits[14:0])                              \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)             <<" \n";
        theStream << "Status(0x):"<<DisplayOtnPqwStatus(0,TSPII_SNCIF_NUM_CHANNEL,&itsTxPQM[0])                            <<" \n";
    }
    if(aPqmRx||aSummary)
    {
        theStream << "                 OTN Rx PQM  (Local PQW SW programmable Status bits[14:0])                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:   "<<DisplayOtnPqwChannel(0,TSPII_SNCIF_NUM_CHANNEL,aCh,false)             <<" \n";
        theStream << "Status(0x):"<<DisplayOtnPqwStatus(0,TSPII_SNCIF_NUM_CHANNEL,&itsRxPQM[0])                            <<" \n";
    }
    if(aApsLocal||aSummary)
    {
        theStream << "                 OTN Rx Local APS  (Local APS bits[31:0])                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:"<<DisplayOtnApsChannel(0,TSPII_SNCIF_APS_CHANNEL,aCh,false)             <<" \n";
        theStream << "Status(0x):"<<DisplayApsBytes(0,TSPII_SNCIF_APS_CHANNEL,itsRxLocalApsBytes)                          <<" \n";
    }
    if(aApsRemote||aSummary)
    {
        theStream << "                 OTN Rx Remote APS  (Remote APS bits[31:0])                               \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:"<<DisplayOtnApsChannel(0,TSPII_SNCIF_APS_CHANNEL,aCh,false)             <<" \n";
        theStream << "Status(0x):"<<DisplayApsBytes(0,TSPII_SNCIF_APS_CHANNEL,itsRxRemoteApsBytes)                          <<" \n";
    }
    if(aApsInterrupt||aSummary)
    {
        theStream << "                 OTN Remote/Local APS Enable                                              \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Channel:"<<DisplayOtnApsChannel(0,TSPII_SNCIF_APS_CHANNEL,aCh,false)             <<" \n";
        theStream << "Local:     "<<DisplayApsInterruptEnable<LocalApsInterruptCfg>(0,TSPII_SNCIF_APS_CHANNEL,itsLocalApsInterruptCfg)<<" \n";
        theStream << "Remote:    "<<DisplayApsInterruptEnable<RemoteApsInterruptCfg>(0,TSPII_SNCIF_APS_CHANNEL,itsRemoteApsInterruptCfg)<<" \n";
    }    
    if(aTimeOut||aSummary)
    {
        theStream << "    MONITORING\n";
        bool      aTimeout[20];//20
        for(uint8 aShelf = 0; aShelf < itsNumShelves; aShelf++)
       {

         for(uint8 i=0; i<itsNumSlots;i++)
         {
             aTimeout[i]=((itsPqwTimeout[aShelf][i]) & 1);
         }
        theStream << "   OTN PQW Timeout Shelf  "<<DisplayOtnPqwChannel((aShelf+1),(aShelf+1),aSl,false)<<":                  \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Slot:      "<<DisplayOtnPqwChannel(0,10,aSl,true)                                                    <<" \n";
        theStream << "On ?:      "<<DisplayOtnPqwEnabled(0,10,aOn,aOff,&aTimeout[0],true)                                  <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(0,10,&itsPqwTimeout[aShelf][0])                                   <<" \n";
        theStream << "-------------------------------------------------------------------------------------------------------------------\n";
        theStream << "Slot:      "<<DisplayOtnPqwChannel(10,itsNumSlots,aSl,true)                                         <<" \n";
        theStream << "On ?:      "<<DisplayOtnPqwEnabled(10,itsNumSlots,aOn,aOff,&aTimeout[10],true)                      <<" \n";
        theStream << "Count(0x): "<<DisplayOtnPqwCounter(10,itsNumSlots,&itsPqwTimeout[aShelf][10])                       <<" \n";
       }
    }
    //the following for display single channel info
    if(aChannel!=255)
    {
        theStream <<"   OTN PQW Channel "<<DisplayOtnPqwChannel(aChannel,(aChannel+1),aCh,false)<<":                               \n";
        if(aEnableIntCh)
        {

             theStream << "   OTN           Rx Sw Interrupt Enable      Rx Hw Interrupt Enable     Tx  Hw  Interrupt Enable         \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Enabled ?    :           "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsRxSwPqwIntEnbl[aChannel],false)<<"                      "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsRxHwPqwIntEnbl[aChannel],false)<<"                      "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsTxHwPqwIntEnbl[aChannel],false)<<" \n";
        }


         if(aEnableFppCh&&aEnableSrcCh)
         {//show both fpp and src

             theStream << "   OTN           FPP   Channel   Enable      FPP   Squelch   Enable     Source   Traffic  Enable         \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Enabled ?    :           "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsFppEnbl[aChannel],false)<<"                      "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsFppSqlEnbl[aChannel],false)<<"                      "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsSrcTfcEnbl[aChannel],false)<<" \n";
         }
         else if(aEnableFppCh)
         {//only show fpp
             theStream << "   OTN           FPP   Channel   Enable      FPP   Squelch   Enable                                      \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Enabled ?    :           "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsFppEnbl[aChannel],false)   <<"                      "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsFppSqlEnbl[aChannel],false)<<" \n";
         }
         else if(aEnableSrcCh)
         {//only show src
             theStream << "   OTN                                                                  Source   Traffic  Enable         \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Enabled ?    :                                                                   "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsSrcTfcEnbl[aChannel],false)<<" \n";
          }

         if(aEnablePqwCh)
         {
             theStream << "   OTN           Rx Hw PQW Squelch Enable                               Tx Hw PQW Squelch Enable         \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Enabled ?    :           "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsRxHwPQWSql[aChannel],false)<<"                                                  "
                       << DisplayOtnPqwEnabled(aChannel,(aChannel+1),aTrue,aFalse,&itsTxHwPQWSql[aChannel],false)<<" \n";
         }


         if(aCountTxCh)
         {
             theStream << "   OTN           Tx SF High                  Tx SF Low                  Tx SD                            \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Count(0x):        "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsTxSFHigh[aChannel])<<"                    "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsTxSFLow[aChannel])<<"                    "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsTxSD[aChannel])<<" \n";
         }
         if(aCountRxCh)
         {
             theStream << "   OTN           Rx SF High                  Rx SF Low                  Rx SD                            \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Count(0x):       "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsRxSFHigh[aChannel])<<"                    "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsRxSFLow[aChannel])<<"                    "
                       << DisplayOtnPqwCounter(aChannel,(aChannel+1),&itsRxSD[aChannel])<<" \n";
         }
         if(aPqmTxCh)
         {
             theStream << "   OTN           Tx PQM  (Remote PQW SW programmable Status bits[14:0])                                  \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Status(0x):      "
                       << DisplayOtnPqwStatus(aChannel,(aChannel+1),&itsTxPQM[aChannel])<<" \n";
         }
         if(aPqmRxCh)
         {
             theStream << "   OTN           Rx PQM  (Local PQW SW programmable Status bits[14:0])                                   \n";
             theStream << "-------------------------------------------------------------------------------------------------------------------\n";
             theStream << "Status(0x):      "
                       << DisplayOtnPqwStatus(aChannel,(aChannel+1),&itsRxPQM[aChannel])<<" \n";
         }
    }
   // TSPII_BaseIf::Display(theStream);
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
bool TSPII_SncIf::Set(int argc, char ** argv)
{
    bool printUsage = true;

    if ((argc == 7) && (strcmp(argv[0], "prior") == 0))
    {
        TSPII_SNCIF_PRIORITY_TABLE Table;
        TSPII_SNCIF_DEFECT_GROUP DefectGrp;
        TSPII_SNCIF_PRIORITY Priority;
        TSPII_SNCIF_FRAMER Framer;
        TSPII_SNCIF_DEFECT_TYPE DefectType;
        int DefectIndex;

        for (int i = 0; i < TSPII_SNCIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[1], TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(i)) == 0)
        {
            Table = (TSPII_SNCIF_PRIORITY_TABLE)i;
            for (int j = 0; j < TSPII_SNCIF_DEFECT_UNKNOWN; j++) if (strcmp(argv[2], TSPII_SNCIF_DISPLAY_DEFECTGRP(j)) == 0)
            {
                DefectGrp = (TSPII_SNCIF_DEFECT_GROUP)j;
                for (int k = 0; k <= TSPII_SNCIF_PRIOR_SFH; k++) if (strcmp(argv[3], TSPII_SNCIF_DISPLAY_PRIORITY(k)) == 0)
                {
                    Priority = (TSPII_SNCIF_PRIORITY)k;
                    for(int m = 0; m <TSPII_SNCIF_NONE; m++) if (strcmp(argv[4], TSPII_SNCIF_DISPLAY_DEFECTTYPE(m)) ==0 )
                    {
                        DefectType = (TSPII_SNCIF_DEFECT_TYPE)m;
                        for(int n = 0; n<=TSPII_SNCIF_ODU2; n++) if(strcmp(argv[5], TSPII_SNCIF_DISPLAY_FRAMER(n)) == 0)
                        {
                            Framer = (TSPII_SNCIF_FRAMER)n;
                            DefectIndex =atoi(argv[6]);
                            if(DefectIndex >0 )
                            {
                                --DefectIndex;
                            }
                        }
                        SetTohPriorityTable(DefectGrp, DefectType, Framer, DefectIndex, Priority, Table );
                        printUsage = false;
                        break;
                    }
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
        for (int i = 0; i < TSPII_SNCIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[2], TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(i)) == 0)
        {
            if((Port <= TSPII_SNCIF_NUM_CHANNEL) && (Port >0))
            {
                SetTohPriorityAssignment(Port-1, (TSPII_SNCIF_PRIORITY_TABLE)i);
                printUsage = false;
            }
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "egressxc") == 0))
    {
        char aOutBuf[256];
        uint8 SrcShelf;
        uint8 SrcSlot;
        uint8 SrcOtnPqwChannel;
        uint8 DstOtnPqwChannel;


        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
        SrcShelf = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        if(itsForceShelf)
        {
            SrcShelf = 1;  // For now force to shelf 1
        }
        SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        SrcOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));
        DstOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));

        if((SrcShelf > 0) && (SrcShelf <= itsNumShelves) &&
           (SrcSlot > 0) && (SrcSlot <= itsNumSlots) &&
           (SrcOtnPqwChannel > 0) && (SrcOtnPqwChannel <= TSPII_SNCIF_NUM_CHANNEL + 1) &&
           (DstOtnPqwChannel > 0) && (DstOtnPqwChannel <= TSPII_SNCIF_NUM_CHANNEL + 1))
        {
            // Convert it to "0" based numbering
            AddTohPqwEgressXconn(SrcShelf - 1, SrcSlot - 1, SrcOtnPqwChannel - 1, DstOtnPqwChannel - 1);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "egressxcd") == 0))
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
    else if ((argc == 1) && (strcmp(argv[0], "egressxcda") == 0))
    {
        DeleteAllTohPqwEgressXconns();
        printUsage = false;
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
    else if ((argc == 1) && (strcmp(argv[0], "tohixcda") == 0))
    {
        DeleteAllTohPqwIngressXconns();
        printUsage = false;
    }
  //  else if ((argc == 1) && (strcmp(argv[0], "tohixcc") == 0))
  //  {
  //      CommitTohPqwIngressXconns();
  //      printUsage = false;
  //  }
  //  else if ((argc == 2) && (strcmp(argv[0], "serdes") == 0))
  //  {
  //      static strstream buf;
  //      FC_Stream stream(buf, FC_Stream::BINARY);
  //      TSPII_SncRegion * SncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
  //      if(strcmp(argv[1], "write") == 0)
  //      {
  //          stream << (*SncRegion)[0];    // write
  //          printUsage = false;
  //      }
  //      else if(strcmp(argv[1], "read") == 0)
  //      {
  //          stream >> (*SncRegion)[0];    // read
  //          printUsage = false;
  //      }
  //  }
    else if ((argc == 4) && (strcmp(argv[0], "enable") == 0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[2]));
        bool  aEnable  = GET_THE_ENABLE((argv[3]));
        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            if(strcmp(argv[1],"intrxsw")==0)
            {
                EnableRxSwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"intrxhw")==0)
            {
                EnableRxHwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"inttxhw")==0)
            {
                EnableTxHwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"fpp")==0)
            {
                SetFppEnabled(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"fppsql")==0)
            {
                SetFppSquelchEnabled(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"src")==0)
            {
                SetSrcTrafficEnabled(aChannel,aEnable);
                printUsage = false;
            }

        }
    }

    else if((argc == 4) &&(strcmp(argv[0],"pqmtx")==0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[1]));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            uint16 aPQM = static_cast<unsigned int>(atoi(argv[2]));
            uint16 aMask = static_cast<unsigned int>(atoi(argv[3]));
            SetTxPQM(aChannel,aPQM,aMask);
            printUsage = false;
        }
    }

    else if ((argc == 5) && (strcmp(argv[0], "enable") ==0))
    {
        bool  aEnable  = GET_THE_ENABLE((argv[2]));
        uint16 aShelf = static_cast<uint16>(atoi(argv[3]))-1;
        uint8 aSlot = static_cast<uint8>(atoi(argv[4]))-1;

        if ((strcmp(argv[1], "timeout") ==0) && (aShelf <= itsNumShelves) && (aSlot <=itsNumSlots))
        {
            SetPqwTimeoutInterruptEnable(aEnable, aShelf, aSlot);
            printUsage = false;
        }

        else if (strcmp(argv[1], "pqw")==0 && (aShelf <= itsNumShelves) && (aSlot <=itsNumSlots))
        {
            SetGeneralSncControlParams(aShelf, aSlot);
            EnablePqwTransmit(aEnable);
            printUsage = false;
        }
    }
    else if((argc == 5) && (strcmp(argv[0], "ingxc") == 0))
    {
        CT_ODU_Identifier coduID;  //initalized to DEFAULT 0xffffffff
        CT_ODU_Identifier soduID;  //initalized to DEFAULT 0xffffffff
        CT_ODU_Identifier tcmID;  //initalized to DEFAULT 0xffffffff
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[1]));
//        uint32 coduID = 0x10000000;
//        uint32 soduID = 0x10000000;
//        uint32 tcmID  = 0x10000000;
        uint32 port, chan;


        port = strtoul(argv[2], NULL ,0);
        chan = strtoul(argv[3], NULL ,0);
        if((port <= SSM40_VCAT1_ODU0_PORT_1) && (chan >0) && (chan <= 16))
        {
            if(port < 5)
            {
                port--;   //adjust to match SSM40_VCAT1_ODU1_PORT table
            }
            chan--;       //adjust for ones base entry

            if (strcmp(argv[4],"client") == 0)
            {
                coduID.SetDevicePort(port);
                coduID.SetDeviceChannel(chan);
                coduID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);

                soduID.SetDevicePort(port);
                soduID.SetDeviceChannel(chan);
                soduID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);

                tcmID.SetDevicePort(0);
                tcmID.SetDeviceChannel(0);
                tcmID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);
//                coduID |= port << 16;  //static const uint32 SSM40_PORT_SHIFT = 16;
//                coduID |= chan;        //static const uint32 SSM40_CHAN_SHIFT = 0;
//                soduID |= port << 16;  // if they're the same then only client set!!
//                soduID |= chan;
//                tcmID  |= 0;
            }
            else if (strcmp(argv[4],"server") == 0)
            {
                coduID.SetDevicePort(0);
                coduID.SetDeviceChannel(0);
                coduID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);

                soduID.SetDevicePort(port);
                soduID.SetDeviceChannel(chan);
                soduID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);

                tcmID.SetDevicePort(0);
                tcmID.SetDeviceChannel(0);
                tcmID.SetIdTelecomLayer(port< SSM40_VCAT1_ODU1_PORT_1 ?CT_ServerPool_Layer_Otu:CT_ServerPool_Layer_Odu);
//                soduID |= port << 16; //static const uint32 SSM40_PORT_SHIFT = 16;
//                soduID |= chan;       //static const uint32 SSM40_CHAN_SHIFT = 0;
//                coduID |= 0;
//                tcmID  |= 0;
            }

            coduID.SetOduKvalue(CT_ODU_Layer0);
            soduID.SetOduKvalue(CT_ODU_Layer0);
            tcmID.SetOduKvalue(CT_ODU_Layer0);
            if((aChannel > 0) && (coduID.GetIdValue() != 0xffffffff) && (soduID.GetIdValue() !=0xffffffff) && (tcmID.GetIdValue() !=0xffffffff))
            {
                AddTohPqwIngressXconn(aChannel-1, coduID.GetIdValue(), soduID.GetIdValue(), tcmID.GetIdValue());
                printUsage = false;
            }
        }

    }
    else if((argc == 2) && (strcmp(argv[0], "debug") == 0))
    {
        int level = atoi(argv[1]);
        if(level>1)
        {
            itsdebuglevel = DEBUG_DETAILED;
        }
        else if(level)
        {
            itsdebuglevel = DEBUG_BASIC;
        }
        else
            itsdebuglevel = DEBUG_OFF;
        printUsage = false;
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    prior           <table> <defectGrp> <priority> <defectType> <framer> <defectindex>\n"
                   "                     table     = 1|2|3\n"
                   "                     defectGrp=odu_sf|odu_sd|otu_sf|otu_sd|tcm_sf|tcm_sd\n"
                   "                     priority=none|sd|sfl|sfh\n"
                   "                     defectType=client|server|tcm\n"
                   "                     framer=odu0|odu1|odu2\n"
                   "                     defectIndex= 1|2|3\n"
                   " \n"
                   "    prasign         <OtnPqwChannel= 1-32> <table=1|2|3>\n"
                   "                     OtnPqwChannel  = 1..32\n"
                   "                     table     = 1|2|3\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    egressxc        <sshelf,sslot,sOtnPqwChannel,dOtnPqwChannel>\n"
                   "    egressxcd       <dOtnPqwChannel>\n"
                   "                     sshelf=1, sslot=1-6, sOtnPqwChannel=1-32, dOtnPqwChannel=1-32\n"
                   "    egressxcda       \n"
                   "----------------------------------------------------------------------------------------\n"
                   "    tohixcd         <OtnPqwChannel>\n"
                   "                     LogicalOduId =1-4294967296, dOtnPqwChannel=1-32\n"
                   "    tohixcda         \n"
                   "----------------------------------------------------------------------------------------\n"
                   "    enable          <type><OtnPqwChannel><theEnable>\n"
                   "                     type          = intrxsw|intrxhw|inttxhw|fpp|fppsql|src\n"
                   "                     OtnPqwChannel  = 1..32\n"
                   "                     theEnable     = true|false\n"
                   "    enable           <type><theEnable>< shelf#> <slot#>\n "
                   "                     type          = timeout | pqw\n"
                   "                     shelf #       1 - 16\n"
                   "                     slot          1 - 18\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    pqmtx           <OtnPqwChannel><theValue><theMask> \n"
                   "                     OtnPqwChannel  = 1..32\n"
                   "                     theValue       = 1-32767\n"
                   "                     theMask        = 1-32767\n"
                   "----------------------------------------------------------------------------------------\n"
                   "   ingxc           <OtnPqwChannel><port><channel><portType> \n"
                   "                     OtnPqwChannel  = 1..32\n"
                   "                     port =    1 - OTU1  ODU1 - HyPhy 0\n"
                   "                               2 - OTU2  ODU2 - HyPhy 0\n"
                   "                               3 - VCAT0 ODU1 - HyPhy 0\n"
                   "                               4 - VCAT1 ODU1 - HyPhy 0\n"
                   "                               5 - OTU1  ODU1 - HyPhy 1\n"
                   "                               6 - OTU2  ODU2 - HyPhy 1\n"
                   "                               7 - VCAT0 ODU1 - HyPhy 1\n"
                   "                               8 - VCAT1 ODU1 - HyPhy 1\n"
                   "                               50 - ODU0_PORT_0- CES 0\n"
                   "                               51 - VCAT0 ODU0 - CES 0\n"
                   "                               52 - VCAT1 ODU0 - CES 0\n"
                   "                               53 - ODU0_PORT_1- CES 1\n"
                   "                               54 - VCAT0 ODU0 - CES 1\n"
                   "                               55 - VCAT0 ODU0 - CES 1\n"
                   "                     chan#  {1 - 16}\n"
                   "                     portType = client | server\n"
                   "----------------------------------------------------------------------------------------\n"
                   "  debug            <level> 0- off| 1- On | 2- Detailed\n"
                    << endl;
    }
/*
    "   ingxc           <OtnPqwChannel><ClientID><ServerId><TcmID> \n"
    "                     OtnPqwChannel  = 1..32\n"
    "                     ClientId, ServerId, TcmId {logicalOduId}\n"
    "                     logicalOduId  = 0xfffffff\n"
    "                     where port# {1-32} bits 16 -24 \n"
    "                           chan# {}     bits 0 -15\n"
*/
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
bool TSPII_SncIf::Simul(int argc, char ** argv)
{
    bool printUsage = true;

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
                printUsage = false;
            }
            else if (strcmp(argv[3], "off") == 0)
            {
                if (TSPII_DEFECT(itsPqwTimeout[aShelf-1][aSlot-1])) itsPqwTimeout[aShelf-1][aSlot-1]++;
                printUsage = false;
            }
            //else
            //{
            //    printUsage = true;
            //}
        }
        //else
        //{
        //    // Out of range
        //    printUsage = true;
        //}
    }
    else if ((argc == 7) && (strcmp(argv[0], "prior") == 0))
    {
        TSPII_SNCIF_PRIORITY_TABLE Table;
        TSPII_SNCIF_DEFECT_GROUP DefectGrp;
        TSPII_SNCIF_PRIORITY Priority;
        TSPII_SNCIF_FRAMER Framer;
        TSPII_SNCIF_DEFECT_TYPE DefectType;
        int DefectIndex;

        for (int i = 0; i < TSPII_SNCIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[1], TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(i)) == 0)
        {
            Table = (TSPII_SNCIF_PRIORITY_TABLE)i;
            for (int j = 0; j < TSPII_SNCIF_DEFECT_UNKNOWN; j++) if (strcmp(argv[2], TSPII_SNCIF_DISPLAY_DEFECTGRP(j)) == 0)
            {
                DefectGrp = (TSPII_SNCIF_DEFECT_GROUP)j;
                for (int k = 0; k <= TSPII_SNCIF_PRIOR_SFH; k++) if (strcmp(argv[3], TSPII_SNCIF_DISPLAY_PRIORITY(k)) == 0)
                {
                    Priority = (TSPII_SNCIF_PRIORITY)k;
                    for (int k = 0; k <= TSPII_SNCIF_PRIOR_SFH; k++) if (strcmp(argv[3], TSPII_SNCIF_DISPLAY_PRIORITY(k)) == 0)
                    {
                        Priority = (TSPII_SNCIF_PRIORITY)k;
                        for(int m = 0; m <TSPII_SNCIF_NONE;m++) if (strcmp(argv[4], TSPII_SNCIF_DISPLAY_DEFECTTYPE(m)) ==0 )
                        {
                            DefectType = (TSPII_SNCIF_DEFECT_TYPE)m;
                            for(int n = 0; n<=TSPII_SNCIF_ODU2;n++) if(strcmp(argv[5], TSPII_SNCIF_DISPLAY_FRAMER(n)) == 0)
                            {
                                Framer = (TSPII_SNCIF_FRAMER)n;
                                DefectIndex =atoi(argv[6]);
                            }
                            SetTohPriorityTable(DefectGrp, DefectType, Framer, DefectIndex, Priority, Table );
                            printUsage = false;
                            break;
                        }
                        break;
                    }
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
        for (int i = 0; i < TSPII_SNCIF_PRIOR_TBL_MAX; i++) if (strcmp(argv[2], TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(i)) == 0)
        {
            if(Port <= TSPII_SNCIF_NUM_CHANNEL)
            {
                SetTohPriorityAssignment(Port, (TSPII_SNCIF_PRIORITY_TABLE)i);
                printUsage = false;
            }
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "egressxc") == 0))
    {
        char aOutBuf[256];
        uint8 SrcShelf;
        uint8 SrcSlot;
        uint8 SrcOtnPqwChannel;
        uint8 DstOtnPqwChannel;


        // Read the Xconn record as a comma seperated string.
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
        SrcShelf = static_cast<uint8>(atoi(strtok(aOutBuf, ",")));
        if(itsForceShelf)
        {
            SrcShelf = 1;  // For now force to shelf 1
        }
        SrcSlot = static_cast<uint8>(atoi(strtok(NULL, ",")));
        SrcOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));
        DstOtnPqwChannel = static_cast<uint8>(atoi(strtok(NULL, ",")));

        if((SrcShelf > 0) && (SrcShelf <= itsNumShelves) &&
           (SrcSlot > 0) && (SrcSlot <= itsNumSlots) &&
           (SrcOtnPqwChannel > 0) && (SrcOtnPqwChannel <= TSPII_SNCIF_NUM_CHANNEL + 1) &&
           (DstOtnPqwChannel > 0) && (DstOtnPqwChannel <= TSPII_SNCIF_NUM_CHANNEL + 1))
        {
            // Convert it to "0" based numbering
            AddTohPqwEgressXconn(SrcShelf - 1, SrcSlot - 1, SrcOtnPqwChannel - 1, DstOtnPqwChannel - 1);
            printUsage = false;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "egressxcd") == 0))
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
    else if ((argc == 1) && (strcmp(argv[0], "egressxcda") == 0))
    {
        DeleteAllTohPqwEgressXconns();
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "ingressxc") == 0))
    {

        uint8 aChannel = GET_CHANNEL_NUMBER((argv[1]));
        uint32 coduID, soduID, tcmID;

        coduID = strtoul(argv[2], NULL ,0);
        soduID = strtoul(argv[3], NULL ,0);
        tcmID  = strtoul(argv[4], NULL ,0);


        if((aChannel > 0) && (coduID != 0xffffffff) && (soduID !=0xffffffff)  && (tcmID !=0xffffffff))
        {

            AddTohPqwIngressXconn(aChannel-1, coduID, soduID, tcmID);
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
    else if ((argc == 1) && (strcmp(argv[0], "tohixcda") == 0))
    {
        DeleteAllTohPqwIngressXconns();
        printUsage = false;
    }
  //  else if ((argc == 1) && (strcmp(argv[0], "tohixcc") == 0))
  //  {
  //      CommitTohPqwIngressXconns();
  //      printUsage = false;
  //  }
  // else if ((argc == 2) && (strcmp(argv[0], "serdes") == 0))
  // {
  //     static strstream buf;
  //     FC_Stream stream(buf, FC_Stream::BINARY);
  //     TSPII_SncRegion * SncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
  //     if(strcmp(argv[1], "write") == 0)
  //     {
  //         stream << (*SncRegion)[0];    // write
  //         printUsage = false;
  //     }
  //     else if(strcmp(argv[1], "read") == 0)
  //     {
  //         stream >> (*SncRegion)[0];    // read
  //         printUsage = false;
  //     }
  // }
    else if ((argc == 4) && (strcmp(argv[0], "enable") == 0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[2]));
        bool  aEnable  = GET_THE_ENABLE((argv[3]));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            if(strcmp(argv[1],"intrxsw")==0)
            {
                EnableRxSwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"intrxhw")==0)
            {
                EnableRxHwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"inttxhw")==0)
            {
                EnableTxHwPqwInterrupt(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"fpp")==0)
            {
                SetFppEnabled(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"fppsql")==0)
            {
                SetFppSquelchEnabled(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"src")==0)
            {
                SetSrcTrafficEnabled(aChannel,aEnable);
                printUsage = false;
            }
            else if(strcmp(argv[1],"pqwrxhwsql")==0)
            {
                itsRxHwPQWSql[aChannel] = aEnable;
                printUsage = false;
            }
            else if(strcmp(argv[1],"pqwtxhwsql")==0)
            {
                itsTxHwPQWSql[aChannel] = aEnable;
                printUsage = false;
            }

        }
    }
    else if((argc == 4) &&(strcmp(argv[0],"count")==0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[2]));
        //uint32 aValue = static_cast<uint32>(atol(argv[3]));
        uint32 aValue = static_cast<uint32>(strtoul(argv[3],NULL,0));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            if(strcmp(argv[1],"txsfhigh")==0)
            {
                itsTxSFHigh[aChannel] = aValue;
                printUsage = false;
            }
            else if(strcmp(argv[1],"txsflow")==0)
            {
                itsTxSFLow[aChannel] = aValue;
                printUsage = false;
            }
            else if(strcmp(argv[1],"txsd")==0)
            {
                itsTxSD[aChannel] = aValue;
                printUsage = false;
            }
            else if(strcmp(argv[1],"rxsfhigh")==0)
            {
                itsRxSFHigh[aChannel] = aValue;
                printUsage = false;
            }
            else if(strcmp(argv[1],"rxsflow")==0)
            {
                itsRxSFLow[aChannel] = aValue;
                printUsage = false;
            }
            else if(strcmp(argv[1],"rxsd")==0)
            {
                itsRxSD[aChannel] = aValue;
                printUsage = false;
            }
        }

    }
    else if((argc == 4) &&(strcmp(argv[0],"pqmtx")==0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[1]));
      //uint16 aPQM = static_cast<uint16>(atoi(argv[2]));
        uint16 aPQM = static_cast<uint16>(strtoul(argv[2],NULL,0));
      //uint16 aMask = static_cast<uint16>(atoi(argv[3]));
        uint16 aMask = static_cast<uint16>(strtoul(argv[3],NULL,0));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            SetTxPQM(aChannel,aPQM,aMask);
            printUsage = false;
        }
    }
    else if((argc == 4) &&(strcmp(argv[0],"pqmrx")==0))
    {
        uint8 aChannel = GET_CHANNEL_NUMBER((argv[1]));
      //uint16 aPQM = static_cast<uint16>(atoi(argv[2]));
        uint16 aPQM = static_cast<uint16>(strtoul(argv[2],NULL,0));
      //uint16 aMask = static_cast<uint16>(atoi(argv[3]));
        uint16 aMask = static_cast<uint16>(strtoul(argv[3],NULL,0));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            itsRxPQM[aChannel] = (aPQM&(aMask&0x7FFF));
            printUsage = false;
        }
    }
    else if((argc == 4) &&(strcmp(argv[0],"apsrxlocal")==0))
    {
        uint16 aChannel = GET_CHANNEL_NUMBER((argv[1]));
        uint16 aRxLocalAps = static_cast<uint32>(strtoul(argv[2],NULL,0));
        uint16 aMask = static_cast<uint32>(strtoul(argv[3],NULL,0));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            itsRxLocalApsBytes[aChannel] = (aRxLocalAps&(aMask&0x7FFF));
            printUsage = false;
        }
    }
    else if((argc == 4) &&(strcmp(argv[0],"apsrxremote")==0))
    {
        uint16 aChannel = GET_CHANNEL_NUMBER((argv[1]));
        uint16 aRxRemoteAps = static_cast<uint32>(strtoul(argv[2],NULL,0));
        uint16 aMask = static_cast<uint32>(strtoul(argv[3],NULL,0));

        if((aChannel!=255) && (aChannel >0))
        {
            --aChannel;  // tspii user interface is ones's based
            itsRxRemoteApsBytes[aChannel] = (aRxRemoteAps&(aMask&0x7FFF));
            printUsage = false;
        }
    }    
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }



    if (printUsage)
    {
        fc_cout << "    prior           <table> <defectGrp> <priority> <defectType> <framer> <defectIndex>\n"
                   "                     table     = 0|1|2\n"
                   "                     defectGrp=odu_sf|odu_sd|otu_sf|otu_sd|tcm_sf|tcm_sd\n"
                   "                     priority=none|sd|sfl|sfh\n"
                   "                     defectType=client|server|tcm\n"
                   "                     framer=odu0|odu1|odu2\n"
                   "                     defectIndex=0|1|2\n"
                   " \n"
                   "    prasign         <OtnPqwChannel=0-15> <table=0|1|2>\n"
                   "                     OtnPqwChannel = 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15 \n"
                   "                     table     = 0|1|2\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    egressxc         <sshelf,sslot,sOtnPqwChannel,dOtnPqwChannel>\n"
                   "    egressxcd         <dOtnPqwChannel>\n"
                   "                     sshelf=1, sslot=1-6, sOtnPqwChannel=0-15, dOtnPqwChannel=0-15\n"
                   "    egressxcda         \n"
                   "----------------------------------------------------------------------------------------\n"
                   "    ingressxc         <LogicalOduId, OtnPqwChannel>\n"
                   "    tohixcd         <OtnPqwChannel>\n"
                   "                     LogicalOduId =0-4294967295, dOtnPqwChannel=0-15\n"
                   "    tohixcda         \n"
                   "----------------------------------------------------------------------------------------\n"
                   "    enable          <type><OtnPqwChannel><theEnable>\n"
                   "                     type          = intrxsw|intrxhw|inttxhw|fpp|fppsql|src|pqwrxhwsql|pqwtxhwsql \n"
                   "                     OtnPqwChannel = 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15 \n"
                   "                     theEnable     = true|false\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    count           <type><OtnPqwChannel><theValue> \n"
                   "                     type           = txsfhigh|txsflow|txsd|rxsfhigh|rxsflow|rxsd\n"
                   "                     OtnPqwChannel  = 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15\n"
                   "                     theValue       = 0-4294967295\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    pqmtx            <OtnPqwChannel><theValue><theMask> \n"
                   "                     OtnPqwChannel  = 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15\n"
                   "                     theValue       = 0-32767\n"
                   "                     theMask        = 0-32767\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    pqmrx            <OtnPqwChannel><theValue><theMask> \n"
                   "                     OtnPqwChannel  = 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15\n"
                   "                     theValue       = 0-32767\n"
                   "                     theMask        = 0-32767\n"
                   "----------------------------------------------------------------------------------------\n"
                   "    pqwto           <shelf> <slot> <on|off>\n"
                   "                     shelf=1, slot=1-N" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_SncIf::Display(FC_Stream & theStream)
{
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnPriorityTable()
{
    char    aBuf[128];
    string  aStr;

    aStr = "Table0       :  ";
    for(uint8 i = 0; i < TSPII_SNCIF_PRIOR_UNKNOWN; i++)
    {
        sprintf(aBuf, "%6s", TSPII_SNCIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_0][i]));
        aStr += aBuf;
    }
    aStr += "\n";
    aStr += "Table1       :  ";
    for(uint8 i = 0; i < TSPII_SNCIF_PRIOR_UNKNOWN; i++)
    {
        sprintf(aBuf, "%6s", TSPII_SNCIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_1][i]));
        aStr += aBuf;
    }
    aStr += "\n";
    aStr += "Table2       :  ";
    for(uint8 i = 0; i < TSPII_SNCIF_PRIOR_UNKNOWN; i++)
    {
        sprintf(aBuf, "%6s", TSPII_SNCIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_2][i]));
        aStr += aBuf;
    }
   // aStr += "\n                                 table3: ";
   // for(i = 0; i < TSPII_SNCIF_PRIOR_UNKNOWN; i++)
   // {
   //     sprintf(aBuf, "%s,", TSPII_SNCIF_DISPLAY_PRIORITY(itsTohPriorTbl[TSPII_SNCIF_PRIOR_TBL_3][i]));
   //     aStr += aBuf;
   // }
    return aStr;
}


string TSPII_SncIf::DisplayOtnPriorityTable(int aTable)
{
    char    aBuf[128];
    string  aStr;

    sprintf(aBuf, "               ");
    aStr += aBuf;
    if(aTable < TSPII_SNCIF_PRIOR_TBL_MAX)
    {
        for(uint8 i = 0; i < TSPII_SNCIF_DEFECT_UNKNOWN; i++)
        {
            sprintf(aBuf, "%8s", TSPII_SNCIF_DISPLAY_PRIORITY(itsTohPriorTbl[aTable][i]));
            aStr += aBuf;
        }
    }
    else
    {
        sprintf(aBuf, " *** Table number undefined *** %d\n",aTable);
        aStr += aBuf;
    }
    sprintf(aBuf, "\n");
    aStr += aBuf;

    return aStr;
}
///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnDefectList()
{
    char    aBuf[128];
    string  aStr;

    aStr ="Defect:   ";
    for(uint8 i=0; i<TSPII_SNCIF_PRIOR_DEF_MAX;i++)
    {
        sprintf(aBuf, "%8s", TSPII_SNCIF_DISPLAY_PRIORDEF(i));
        aStr += aBuf;
    }
    return aStr;
}
string TSPII_SncIf::DisplayOtnDefectGroup()
{
    char    aBuf[128];
    string  aStr;

    aStr = "\nDefect Groups: ";
    for(uint8 i=0; i <TSPII_SNCIF_DEFECT_UNKNOWN; i++)
    {
        sprintf(aBuf, "%8s", TSPII_SNCIF_DISPLAY_DEFECTGRP(i));
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnPqwChannel(uint8 theBeginCh,uint8 theEndCh, const char* argv,bool showCount)
{

    char    aBuf[128];
    string  aStr;


    //aStr = "Channel: ";   or aStr = "Slot:      ";

    for(uint8 i=theBeginCh; i<theEndCh;i++)
    {
        if(showCount)
        {//10s--for showCount
            aStr +="    ";
        }
        if(i<10)
        {
            //6s---for not showCount

            sprintf(aBuf, "   %2s%1d",argv, i);
        }
        else
        {
            //6s---for not showCount
            sprintf(aBuf, "  %2s%2d",argv, i);
        }
        aStr += aBuf;
    }
    return aStr;
}
string TSPII_SncIf::DisplayOtnPqwEnabled(uint8 theBeginCh,uint8 theEndCh,const char * theOn,const char * theOff,bool *theEnable,bool showCount)
{
    char    aBuf[128];
    string  aStr;
    bool    aValue[TSPII_SNCIF_NUM_CHANNEL];


    //aStr = "Enabled?:";
    for(uint8 i=0; i<(theEndCh-theBeginCh);i++)
    {
        aValue[i]= *theEnable;
        if(showCount)
        {//10s
            if(aValue[i])
            {
                //sprintf(aBuf, "%10s", TSPII_SNCIF_PRIORITY_ENABLED(aValue[i]));
                  sprintf(aBuf, "%10s", theOn);
            }
            else
            {
                //sprintf(aBuf, "%10s", TSPII_SNCIF_PRIORITY_ENABLED(aValue[i]));
                  sprintf(aBuf, "%10s", theOff);
            }

        }
        else
        {//6s
            if(aValue[i])
            {  //sprintf(aBuf, "%6s", TSPII_SNCIF_PRIORITY_ENABLED(aValue[i]));
                sprintf(aBuf, "%6s", theOn);
            }
            else
            {  //sprintf(aBuf, "%6s", TSPII_SNCIF_PRIORITY_ENABLED(aValue[i]));
                sprintf(aBuf, "%6s", theOff);
            }

        }

        theEnable++;
        aStr += aBuf;
    }
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnPriorityAssign()
{
    char    aBuf[128];
    string  aStr;

    //aStr = "Table?: ";
    for(uint8 i = 0; i < TSPII_SNCIF_NUM_CHANNEL; i++)
    {
        sprintf(aBuf, "%6s", TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(static_cast<int>(itsTohPriorAssign[i])));
        aStr += aBuf;
    }
    return aStr;
}



///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnPqwCounter(uint8 theBeginCh,uint8 theEndCh,uint32 *theValue)
{
    char    aBuf[128];
    string  aStr;
    uint32  aValue[TSPII_SNCIF_NUM_CHANNEL];

    //aStr = "Count(0x): ";
    for(uint8 i=0; i<(theEndCh-theBeginCh);i++)
    {//10s
        aValue[i]= *theValue;
        sprintf(aBuf, "%10X",aValue[i]);
        theValue++;
        aStr += aBuf;
    }
    return aStr;
}
///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnPqwStatus(uint8 theBeginCh,uint8 theEndCh,uint16 *theValue)
{
    char    aBuf[128];
    string  aStr;
    uint16  aValue[TSPII_SNCIF_NUM_CHANNEL];

    //aStr = "Status(0x):";
    for(uint8 i=0; i<(theEndCh-theBeginCh);i++)
    {//6s
        aValue[i]= *theValue;
        sprintf(aBuf, "%6X",aValue[i]);
        theValue++;
        aStr += aBuf;
    }
    return aStr;
}

string TSPII_SncIf::DisplayOtnApsChannel(uint8 theBeginCh,uint8 theEndCh, const char* argv,bool showCount)
{

    char    aBuf[128];
    string  aStr;


    //aStr = "Channel: ";   or aStr = "Slot:      ";

    for(uint8 i=theBeginCh; i<theEndCh;i++)
    {
        if(showCount)
        {//10s--for showCount
            aStr +="  ";
        }
        if(i<10)
        {
            //8s---for not showCount

            sprintf(aBuf, "    %-2s%-2d",argv, i);
        }
        else
        {
            //8s---for not showCount
            sprintf(aBuf, "    %-2s%-2d",argv, i);
        }
        aStr += aBuf;
    }
    return aStr;
}
string TSPII_SncIf::DisplayApsBytes(uint16 theBeginCh,uint16 theEndCh,vector<uint32> &theValue)
{
    char    aBuf[128] = {0};
    string  aStr;
    uint32  aValue[TSPII_SNCIF_NUM_CHANNEL] = {0};

    for(uint8 i=0; i<(theEndCh-theBeginCh);i++)
    {
        aValue[i]= theValue[i];
        sprintf(aBuf, "%-9x",aValue[i]);
        aStr += aBuf;    
    }

    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnTohPqwEgressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SncIfTohPqwEgrXcMap::iterator  aToheIter;

    sprintf(aBuf, "%d <shelf,sslot,SrcOtnPqwChannel,DstOtnPqwChannel - isNewChanged isDeleted>\n", itsTohPqwEgressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aToheIter=itsTohPqwEgressXconnsMap.begin(); aToheIter != itsTohPqwEgressXconnsMap.end(); ++aToheIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%03d,%03d,%03d,%05d - %1d %1d", aToheIter->second.SrcShelf + 1,
                                                      aToheIter->second.SrcSlot + 1,
                                                      aToheIter->second.SrcOtnPqwChannel + 1,
                                                      aToheIter->first.DstOtnPqwChannel + 1,
                                                      aToheIter->second.IsNewOrChanged,
                                                      aToheIter->second.IsDeleted);

            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}
string TSPII_SncIf::DisplayOtnTohPqwEgressXc(int pqwchannel)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SncIfTohPqwEgrXcKey aKey;
    aKey.DstOtnPqwChannel = pqwchannel;

    TSPII_SncIfTohPqwEgrXcMap::iterator  aToheIter;

    sprintf(aBuf, "<shelf sslot SrcOtnPqwChannel DstOtnPqwChannel - isNewChanged isDeleted>\n");
    aStr += aBuf;

#ifndef PSOSP
    aToheIter = itsTohPqwEgressXconnsMap.find(aKey);
    if((aToheIter!=itsTohPqwEgressXconnsMap.end()) && (aToheIter->first.DstOtnPqwChannel == pqwchannel))
    {
        sprintf(aBuf, "  %3d   %3d      %3d             %3d          -    %s           %s", aToheIter->second.SrcShelf +1,
                                                  aToheIter->second.SrcSlot + 1,
                                                  aToheIter->second.SrcOtnPqwChannel + 1,
                                                  aToheIter->first.DstOtnPqwChannel + 1,
                                                  (aToheIter->second.IsNewOrChanged == true ? "New":"Changed"),
                                                  (aToheIter->second.IsDeleted == true ? "True":"False"));

        aStr += aBuf;
    }
        aStr += "\n";

#endif
    return aStr;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_SncIf::DisplayOtnTohPqwIngressXc(bool printDetail)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SncIfTohPqwIngXcMap::iterator  aTohiIter;

    sprintf(aBuf, "%d <    LogicalOduId, OtnPqwChannel - isNewChanged isDeleted>\n", itsTohPqwIngressXconnsMap.size());
    aStr += aBuf;

#ifndef PSOSP
    if(printDetail)
    {
        for(aTohiIter=itsTohPqwIngressXconnsMap.begin(); aTohiIter != itsTohPqwIngressXconnsMap.end(); ++aTohiIter)
        {
            sprintf(aBuf, "         ");
            aStr += aBuf;
            sprintf(aBuf, "%012lu,%012lu,%012lu,%03d - %1d %1d", aTohiIter->second.cLogicalOduId,
                                                                aTohiIter->second.sLogicalOduId,
                                                                aTohiIter->second.tLogicalOduId,
                                                                aTohiIter->first.OtnPqwChannel + 1,
                                                                aTohiIter->second.IsNewOrChanged,
                                                                aTohiIter->second.IsDeleted);
            aStr += aBuf;
            aStr += "\n";
        }
    }
#endif
    return aStr;
}

string TSPII_SncIf::DisplayOtnTohPqwIngressXc(int aChannel)
{
    char    aBuf[128];
    string  aStr;
    TSPII_SncIfTohPqwIngXcKey aKey;
    aKey.OtnPqwChannel = aChannel;

    TSPII_SncIfTohPqwIngXcMap::iterator  aTohiIter;

    sprintf(aBuf, "server OduId  client OduId  tcm OduId - isNewChanged isDeleted>\n");
    aStr += aBuf;

#ifndef PSOSP
    aTohiIter = itsTohPqwIngressXconnsMap.find(aKey);
    if((aTohiIter != itsTohPqwIngressXconnsMap.end()) && (aTohiIter->first.OtnPqwChannel == aChannel))
    {
        sprintf(aBuf, "0x%-8x    0x%-8x    0x%-8x - %s     %s\n", aTohiIter->second.sLogicalOduId,
                                        aTohiIter->second.cLogicalOduId,
                                        aTohiIter->second.tLogicalOduId,
                                        (aTohiIter->second.IsNewOrChanged ==true ?"New":"Change"),
                                        (aTohiIter->second.IsDeleted ==true ? "True":"False"));
        aStr += aBuf;
    }
        aStr += "\n";

#endif
    return aStr;
}

string TSPII_SncIf::DisplayOtnPqwChannelConfiguration(int aChannel)
{
    char aBuf[128];
    string aStr;

    //Display TOH priority assignment
    sprintf (aBuf,"priority Table  = Table %s\n",TSPII_SNCIF_DISPLAY_PRIORITY_TABLE(itsTohPriorAssign[aChannel]));
    aStr += aBuf;
    aStr += "\n";

     //Display Local PQM
    sprintf (aBuf, "Tx PQM        : 0x%-8X\n",itsTxPQM[aChannel]);
    aStr +=aBuf;
    aStr += "\n";
    //Display Local Cross Connect
    sprintf (aBuf, "    Local Cross Connections\n");
    aStr += aBuf;
    aStr += DisplayOtnTohPqwIngressXc(aChannel);
    //Display Remote Cross Connect Map
    sprintf (aBuf, "    Remote Cross Connetion Map\n");
    aStr += aBuf;
    aStr += DisplayOtnTohPqwEgressXc(aChannel);
//    stream << "     destination shelf          "<<(dec)<<itsTohPqwIngressXconnsMap.find(aChannel).first->()<<endl;
//    stream << "     destination slot           "<<(dec)<<itsTohPqwIngressXconnsMap.find(aChannel).first->()<<endl;
//    stream << "     destination index          "<<(dec)<<itsTohPqwIngressXconnsMap.find(aChannel).first->()<<endl;


    return aStr;
}

string TSPII_SncIf::DisplayOtnPqwChannelStatus(int aChannel)
{
    //Display Tx SD, SF counters
    char aBuf[128];
    string aStr;

    aStr += "STATUS\n\n";

    sprintf (aBuf, "   Tx Defects\n");
    aStr += aBuf;
    sprintf (aBuf, "Tx_SFhigh %10u : %s\n", itsTxSFHigh[aChannel],(itsTxSFHigh[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;
    sprintf (aBuf, "Tx_SFLow  %10u : %s\n", itsTxSFLow[aChannel],(itsTxSFLow[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;
    sprintf (aBuf, "Tx_SD     %10u : %s\n", itsTxSD[aChannel],(itsTxSD[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;

    //Display Rx SD,SF
    sprintf (aBuf, "   Rx Defects\n");
    aStr += aBuf;
    sprintf (aBuf, "Rx_SFhigh %10u : %s\n", itsRxSFHigh[aChannel],(itsRxSFHigh[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;
    sprintf (aBuf, "Rx_SFLow  %10u : %s\n", itsRxSFLow[aChannel],(itsRxSFLow[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;
    sprintf (aBuf, "Rx_SD     %10u : %s\n", itsRxSD[aChannel],(itsRxSD[aChannel]%2 ? "ON":"OFF"));
    aStr += aBuf;
    aStr += "\n";
    sprintf (aBuf, "Rx PQM         : 0x%8X \n", itsRxPQM[aChannel]);
    aStr += aBuf;

    return aStr;
}

bool TSPII_SncIf::GetTxPQWInvalid(uint8 theOtnPqwChannel)
{
    return itsTxPQWInvalid[theOtnPqwChannel];  //default = true;
}

bool TSPII_SncIf::GetRxPQWInvalid(uint8 theOtnPqwChannel)
{
    return itsRxPQWInvalid[theOtnPqwChannel];  //default = true;
}

void TSPII_SncIf::EnableAps(bool enable)
{
    itsApsEnable = enable;
}

void TSPII_SncIf::EnableLocalApsInterrupt(CT_ODU_Identifier& oduId, uint8 apsChannel, uint16 apsIndex, bool enable)
{
    itsLocalApsInterruptCfg[apsIndex].oduId = oduId;
    itsLocalApsInterruptCfg[apsIndex].apsChannel = apsChannel;
    itsLocalApsInterruptCfg[apsIndex].enable = enable;
}

void TSPII_SncIf::EnableRemoteApsInterrupt(uint8 shelfId,
                                          uint8 slotId,
                                          uint16 apsIndex,
                                          uint16 remoteApsIndex,
                                          bool enable)
{
    itsRemoteApsInterruptCfg[remoteApsIndex].shelfId = shelfId;
    itsRemoteApsInterruptCfg[remoteApsIndex].slotId = slotId;
    itsRemoteApsInterruptCfg[remoteApsIndex].apsIndex = apsIndex;
    itsRemoteApsInterruptCfg[remoteApsIndex].enable = enable;
}

uint32 TSPII_SncIf::GetRxLocalApsBytes(uint16 theOduTpChannel)
{
    return itsRxLocalApsBytes[theOduTpChannel];
}

uint32 TSPII_SncIf::GetRxRemoteApsBytes(uint16 theOduTpChannel)
{
    return itsRxRemoteApsBytes[theOduTpChannel];
}

//end of file
