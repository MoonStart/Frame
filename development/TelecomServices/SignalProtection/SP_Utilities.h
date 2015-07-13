#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_UTILITIES_INCLUDED
#define _INC_SP_UTILITIES_INCLUDED

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_CrossConnect.h>
#include "SP_Definitions.h"


CT_IntfId GetImuxIntfIdFromPort(CT_IntfId thePortId, CT_SP_1plus1Type the1plus1Type=CT_SP_UNKNOWN, CT_CardFamily theFam = CARD_FAM_UNKNOWN);
CT_FacilitySubType GetImuxFacType(CT_FacilitySubType theFacType);
//void GetAMMappingFromIntfId(CT_DirectionFlag * thePortType, int * thePort, CT_IntfId theIntfId);
void GetXConnTypeFromPortType(CT_XC_ConnectType * theConnType, CT_FacilitySubType thePortType);
CT_TEL_SignalType GetSignalType(CT_FacilitySubType theFacType);
CT_FAC_RxSsm GetFreeRunSsm (CT_TEL_FacilityStandard theFacStandard);
unsigned int GetTspiiIntfFromCTIntfId(CT_IntfId thePortId);
bool IsMFacility(CT_FacilitySubType theFacType);
bool IsPortFacility(CT_IntfId thePortId);
bool IsLineFacility(CT_IntfId thePortId);
int GetResourceIndex( CT_SP_1plus1Type the1plus1Type, SP_ProtectionSide theSide, CT_CardFamily theFam, CT_IntfId thePortId);
bool IsSdhFacility(CT_FacilitySubType theFacType);
uint8 GetOPDefectObjIndex(CT_IntfId thePortId);
uint32 GetRerouteObjectMask(CT_IntfId thePortId);
uint8 GetRerouteObjectIndex(CT_IntfId thePortId);
CT_SP_DefectLayer GetRerouteLayerMask(SP_ArrDefectLayer_Enum theLayer);
unsigned int GetTspiiIntfFromSlotId(CT_CardType theCardType, CT_SlotId theSlotId);

class SP_PairMappingTblLookup
{
public:
    static CT_SlotId GetProtectionPairSlot(
        CT_SlotId  theSlot,
        CT_ShelfType theShelfType);  
};

#endif /* _INC_SP_UTILITIES_INCLUDED */

