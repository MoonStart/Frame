/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Signal Alarm application decorator definition.
--------------------------------------------------------------------------*/

#include "../ALM_AppDecorator.h"
#include "../ALM_AppIf.h"


//-----------------------------------------------------------------------------
//##ModelId=3C506C350373
ALM_AppDecorator::ALM_AppDecorator(ALM_AppIf* theAppIfPtr, bool theAutoDelete):
    FC_BbAppDecoratorImp<ALM_AppIf>(theAppIfPtr, theAutoDelete)
{
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C35037E
ALM_AppDecorator::~ALM_AppDecorator()
{
}

//-----------------------------------------------------------------------------
//##ModelId=3C6D0E600289
ALM_FailureRegionImp<ALM_FailureBase>* ALM_AppDecorator::GetFilteredRegionPtr() const
{ return GetPtrApp()->GetFilteredRegionPtr(); }

//-----------------------------------------------------------------------------
//##ModelId=3C603CA20185
int ALM_AppDecorator::GetNumberOfElement() const
{ return GetPtrApp()->GetNumberOfElement(); }

//-----------------------------------------------------------------------------
int ALM_AppDecorator::GetMonElementOffset() const
{ return GetPtrApp()->GetMonElementOffset(); }

//-----------------------------------------------------------------------------
//##ModelId=3C95FE0B014C
ALM_LayerFailures* ALM_AppDecorator::GetLayerFailurePtr(int theIndex) const
{ return GetPtrApp()->GetLayerFailurePtr(theIndex); }

//-----------------------------------------------------------------------------
//##ModelId=3CC4D1D502F1
bool ALM_AppDecorator::GetMaskAllDefectFlag(int theIndex) const
{ return GetPtrApp()->GetMaskAllDefectFlag(theIndex); }

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D50391
const string& ALM_AppDecorator::GetKeySuffix() const
{ return GetPtrApp()->GetKeySuffix(); }

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D503E1
const char* ALM_AppDecorator::GetInstanceName(void ) const
{ return GetPtrApp()->GetInstanceName(); }

//---------------------------------------------------------------------------
//##ModelId=3CC4D1D6008F
FC_Context& ALM_AppDecorator::GetContext() const
{ return GetPtrApp()->GetContext(); }

//---------------------------------------------------------------------------
//##ModelId=3DBFFAEA0088
T6100_CardActiveRegion& ALM_AppDecorator::GetContextStatusRegion(void) const
{ return GetPtrApp()->GetContextStatusRegion(); }

//---------------------------------------------------------------------------
//##ModelId=3DBFFAEA0114
bool ALM_AppDecorator::WakeUpAlm()
{ return GetPtrApp()->WakeUpAlm(); }

//---------------------------------------------------------------------------
//##ModelId=3DBFFAEA0164
bool ALM_AppDecorator::SuspendAlm()
{ return GetPtrApp()->SuspendAlm(); }

//---------------------------------------------------------------------------
bool ALM_AppDecorator::GetAlmAppState()
{ return GetPtrApp()->GetAlmAppState(); }

//---------------------------------------------------------------------------
void ALM_AppDecorator::SetTraceFlag(bool theDebugFlag)
{ GetPtrApp()->SetTraceFlag(theDebugFlag); }
