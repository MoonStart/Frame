/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Signal Alarm application base class definition.
--------------------------------------------------------------------------*/

#include    <typeinfo>

#include <ErrorService/FC_Error.h>
#include "../ALM_FailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "../ALM_RegionKeyDefinition.h"
#include "ALM_LayerFailures.h"

#include "../ALM_AppIf.h"


static const int theirNumberOfElement(1);
static const int theirMonElementOffset(0);

//-----------------------------------------------------------------------------
//##ModelId=3C506C3501CD
ALM_AppIf::ALM_AppIf()
{
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C3501CE
ALM_AppIf::~ALM_AppIf()
{
}


//-----------------------------------------------------------------------------
//##ModelId=3DBFFAE801E4
bool ALM_AppIf::GetStatus(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index) const
{
    return (*GetFilteredRegionPtr())[index].GetStatus(theFailureType);
}

//-----------------------------------------------------------------------------
//##ModelId=3DBFFAE80356
time_t ALM_AppIf::GetOccurTime(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index) const
{
    return (*GetFilteredRegionPtr())[index].GetOccurTime(theFailureType);
}

//-----------------------------------------------------------------------------
bool ALM_AppIf::GetSigProtStatus(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index) const
{
    return (*GetFilteredRegionPtr())[index].GetSigProtStatus(theFailureType);
}

//-----------------------------------------------------------------------------
void ALM_AppIf::ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, int theMatePort, CT_DirectionFlag theMatePortType, uint32 theMateStartChannel)
{

    (*GetFilteredRegionPtr())[index].ClearSigProtDefect( theFailureType, theMatePort, theMatePortType, theMateStartChannel);
    (*GetFilteredRegionPtr()).IncModificationCounter();
}

//-----------------------------------------------------------------------------
void ALM_AppIf::ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, bool IsYCablePROTNA)
{
    //-------------------------------------------------
    // We will update the appropriate ALM_LayerFailures
    // itsSigProtFailureTable[].ALM_SoakingFailure.
    //-------------------------------------------------
    GetLayerFailurePtr(index)->InvokeSPSoakFailureDefectUpdated(theFailureType, false, IsYCablePROTNA); // false=defect cleared!
}

//-----------------------------------------------------------------------------
void ALM_AppIf::ReportSigProtDefect(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, int theMatePort, CT_DirectionFlag theMatePortType, uint32 theMateStartChannel )
{
    //-------------------------------------------------
    // sharkey...If StreamEndpoints come back, then 
    // these MATE alarms must be modified to follow
    // SOAKing logic, like the other SP conditions!
    //-------------------------------------------------
    (*GetFilteredRegionPtr())[index].ReportSigProtDefect( theFailureType, theMatePort, theMatePortType, theMateStartChannel);
    (*GetFilteredRegionPtr()).IncModificationCounter();
}

//-----------------------------------------------------------------------------
// Report Signal Protection Defect must handle alarms that need to be soaked.
// Currently, this is only the PROTNA alarm. If any alarms need soaking from
// Signal Protect in the future, this list will need updating.
//-----------------------------------------------------------------------------
void ALM_AppIf::ReportSigProtDefect(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, bool IsYCablePROTNA)
{
    //-------------------------------------------------
    // We will update the appropriate ALM_LayerFailures
    // itsSigProtFailureTable[].ALM_SoakingFailure.
    //-------------------------------------------------
    GetLayerFailurePtr(index)->InvokeSPSoakFailureDefectUpdated(theFailureType, true, IsYCablePROTNA); // true=defect exists!
}

//-----------------------------------------------------------------------------
//##ModelId=3C6D0E5F03B4
ALM_FailureRegionImp<ALM_FailureBase>* ALM_AppIf::GetFilteredRegionPtr() const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetFilteredRegion not Supported" );
    return NULL;
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C350232
void ALM_AppIf::WakeUpTimeBeforeTransfer()
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "WakeUpTimeBeforeTransfer not Supported" );
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C35023C
int ALM_AppIf::GetNumberOfElement() const
{
    //The default is 1 element (object in region)
    return theirNumberOfElement;
}

//-----------------------------------------------------------------------------
int ALM_AppIf::GetMonElementOffset() const
{
    //The default is 1 element (object in region)
    return theirMonElementOffset;
}

//-----------------------------------------------------------------------------
//##ModelId=3C95FE0A0187
ALM_LayerFailures* ALM_AppIf::GetLayerFailurePtr(int theIndex) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetLayerFailurePtr not Supported" );
    return NULL;
}

//-----------------------------------------------------------------------------
//##ModelId=3CC4D1D400BF
bool ALM_AppIf::GetMaskAllDefectFlag(int theIndex) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetMaskAllDefectFlag not Supported" );
    return false;
}

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D40173
const string& ALM_AppIf::GetKeySuffix() const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetKeySuffix not Supported" );
    return ALM_NULL_SUFFIX;
}

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D401D7
const char* ALM_AppIf::GetInstanceName(void ) const
{
    return typeid(*this).name();
}

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D40281
FC_Context& ALM_AppIf::GetContext() const
{
    FC_THROW_ERROR( FC_NotSupportedError, "GetContext not Supported" );
    FC_Context* dummy = NULL;
    return *dummy;
}

//##ModelId=3DBFFAE90159
T6100_CardActiveRegion& ALM_AppIf::GetContextStatusRegion(void) const
{
    FC_THROW_ERROR( FC_NotSupportedError, "GetStatusRegion not Supported" );
    T6100_CardActiveRegion* dummy = NULL;
    return *dummy;
}

//---------------------------------------------------------------------------
//##ModelId=3DBFFAE9023F
bool ALM_AppIf::WakeUpAlm()
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "WakeUpAlm not Supported" );
    return false;
}

//---------------------------------------------------------------------------
//##ModelId=3DBFFAE902E9
bool ALM_AppIf::SuspendAlm()
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "SuspendAlm not Supported" );
    return false;
}

//---------------------------------------------------------------------------
bool ALM_AppIf::GetAlmAppState()
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetAlmAppState not Supported" );
    return false;
}

//---------------------------------------------------------------------------
void ALM_AppIf::SetTraceFlag(bool theDebugFlag)
{
    // Throw an error: This method must be implemented in the derived class
    FC_THROW_ERROR( FC_NotSupportedError, "SetTraceFlag not Supported" );
    return;
}

