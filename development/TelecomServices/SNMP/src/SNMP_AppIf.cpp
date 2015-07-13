//Copyright(c) Tellabs Transport Group. All rights reserved

#include <SNMP_AppIf.h>
#include <ErrorService/FC_Error.h>
#include <CsPii/CSPII_CardIF.h>
#include <Blackboard/FC_BbTagGeneric.h>
#include <T6100_CardIf.h>

SNMP_BbAppIf::SNMP_BbAppIf(T6100_TelecomIf& theTelecomContext):
    myTelecomContext(&theTelecomContext)
{
}

SNMP_BbAppIf::SNMP_BbAppIf():
    myTelecomContext(NULL)
{
}

SNMP_BbAppIf::~SNMP_BbAppIf()
{}

T6100_TelecomIf& SNMP_BbAppIf::GetTelecomContext() 
{ 
    FC_THROW_ERROR_IF(myTelecomContext==NULL, FC_RuntimeError, "Context unavailable");
    return *myTelecomContext; 
}

T6100_CardIf& SNMP_BbAppIf::GetCardContext()
{
    T6100_CardIf* aCardIf = dynamic_cast<T6100_CardIf*>(GetTelecomContext().GetParent());    

    FC_THROW_ERROR_IF(aCardIf==NULL, FC_RuntimeError, "Unable to get card context from parent");

    return *aCardIf;
}

T6100_CardActiveRegion& SNMP_BbAppIf::GetTelecomContextStatusRegion()
{
    return GetTelecomContext().GetStatusRegion();
}

CT_SlotId SNMP_BbAppIf::GetSlotId()
{
    T6100_CardIf* aCardIf = dynamic_cast<T6100_CardIf*>(GetTelecomContext().GetParent());    

    FC_THROW_ERROR_IF(aCardIf==NULL, FC_RuntimeError, "Unable to get slot ID from parent");

    return aCardIf->GetCardId();
}
