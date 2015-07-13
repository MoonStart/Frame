// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ArrRegion.h"
#include "../SP_BitSetDataObject.h"
#include "../SP_MapDataObject.h"
#include "../SP_Utilities.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_REROUTE_DEFECTS_REGION_KEY = "SP_RerouteDefects";
const FC_BbKey SP_REROUTE_CONFIG_REGION_KEY = "SP_RerouteConfig";


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////SP_ArrDefectObject///////////////////////////////////////////////////////////
SP_ArrDefectObject::SP_ArrDefectObject()
{
	for (uint8 i =0; i < SP_MAX_ARR_DEFECT_PORT_COUNT; i++)
    {
        myPortDefectList[i] =0;
    }
}

SP_ArrDefectObject::~SP_ArrDefectObject()
{
}

bool SP_ArrDefectObject::SetDefect(uint8 theIndex, uint8 theMask)
{
	if (IsDefectSet(theIndex, theMask))
        return false;
    
    myPortDefectList[theIndex] |= theMask;
    return true;
}

bool SP_ArrDefectObject::IsDefectSet(uint8 theIndex, uint8 theMask)
{
	if ( (myPortDefectList[theIndex] & theMask) == theMask)
        return true;

    return false;
}

bool SP_ArrDefectObject::ClearDefect(uint8 theIndex, uint8 theMask)
{
	if (IsDefectSet(theIndex, theMask))
    {
        myPortDefectList[theIndex] &= ~(theMask);
        return true;
    }

    return false;
}

uint8 SP_ArrDefectObject::GetDefects(uint8 theIndex)
{
	return myPortDefectList[theIndex];
}

ostream& SP_ArrDefectObject::WriteObject( ostream& theStream )
{
    theStream << endl;
    for (uint8 i =0; i < SP_MAX_ARR_DEFECT_PORT_COUNT; i++)
    {
        theStream << "Index " << (uint32)i << ": " << (uint32) (myPortDefectList[i]) << endl;
    }

    myOduDefectList.WriteObject(theStream);
    return theStream;
}

istream& SP_ArrDefectObject::ReadObject( istream& theStream )
{
    return theStream;
}

FC_Stream& SP_ArrDefectObject::WriteObjectBinary( FC_Stream& theStream )
{
    for (uint8 i =0; i < SP_MAX_ARR_DEFECT_PORT_COUNT; i++)
    {
        theStream << myPortDefectList[i];
    }

    myOduDefectList.WriteObjectBinary(theStream);

    return theStream;

}

FC_Stream& SP_ArrDefectObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    for (uint8 i =0; i < SP_MAX_ARR_DEFECT_PORT_COUNT; i++)
    {
        theStream >> myPortDefectList[i];
    }

    myOduDefectList.ReadObjectBinary(theStream);

    return theStream;

}

//*****************************************************************************
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////SP_ArrConfigObject///////////////////////////////////////////////////////////
SP_ArrConfigObject::SP_ArrConfigObject()
{
}

SP_ArrConfigObject::~SP_ArrConfigObject()
{
}

ostream& SP_ArrConfigObject::WriteObject( ostream& theStream )
{
    myPortConfigList.WriteObject(theStream);
    myOduConfigList.WriteObject(theStream);
    return theStream;
}

istream& SP_ArrConfigObject::ReadObject( istream& theStream )
{
    myPortConfigList.ReadObject(theStream);
    myOduConfigList.ReadObject(theStream);
    return theStream;
}

FC_Stream& SP_ArrConfigObject::WriteObjectBinary( FC_Stream& theStream )
{
    myPortConfigList.WriteObjectBinary(theStream);
    myOduConfigList.WriteObjectBinary(theStream);
    return theStream;

}

FC_Stream& SP_ArrConfigObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    myPortConfigList.ReadObjectBinary(theStream);
    myOduConfigList.ReadObjectBinary(theStream);
    return theStream;

}

//*****************************************************************************
//-----------------------------------------------------------------------------
SP_ReRouteDefectRegion::SP_ReRouteDefectRegion(FC_BbKey theKey):
    FC_BbRegionVectImp<SP_ArrDefectObject>(theKey, 1)
{
    
}

SP_ReRouteDefectRegion::~SP_ReRouteDefectRegion()
{
}

bool SP_ReRouteDefectRegion::SetDefects(CT_IntfId theInterface, uint8 defectMask)
{
    uint8 theIndex = GetRerouteObjectIndex(theInterface);
    uint8 curDefects = (*this)[0].GetDefects(theIndex);
    ClearDefects(theInterface);
    (*this)[0].SetDefect(theIndex, defectMask);
    return (curDefects != defectMask);
}

bool SP_ReRouteDefectRegion::ClearDefects(CT_IntfId theInterface)
{
    //Clear all defects
    if (IsDefectSet(theInterface))
    {
        uint8 theIndex = GetRerouteObjectIndex(theInterface);
        uint8 curDefects = (*this)[0].GetDefects(theIndex);
        return ((*this)[0].ClearDefect(theIndex, curDefects));
    }
    else
    {
        return false;
    }
}

bool SP_ReRouteDefectRegion::IsDefectSet(CT_IntfId theInterface)
{
    //Is any defect set on any layer?
    uint8 theIndex = GetRerouteObjectIndex(theInterface);
    return ((*this)[0].GetDefects(theIndex) != 0);
}

uint8 SP_ReRouteDefectRegion::GetDefectList(CT_IntfId theInterface)
{
    uint8 theIndex = GetRerouteObjectIndex(theInterface);
    return (*this)[0].GetDefects(theIndex);
}

bool SP_ReRouteDefectRegion::SetDefects(CT_ODU_Identifier theOdu)
{
    return ((*this)[0].myOduDefectList.Set(theOdu.GetIdValue()));
}

bool SP_ReRouteDefectRegion::ClearDefects(CT_ODU_Identifier theOdu)
{
    //Clear all defects
    return ((*this)[0].myOduDefectList.Clear(theOdu.GetIdValue()));
}

bool SP_ReRouteDefectRegion::IsDefectSet(CT_ODU_Identifier theOdu)
{
    //Is any defect set on any layer?
    return ((*this)[0].myOduDefectList.IsSet(theOdu.GetIdValue()));
}

void SP_ReRouteDefectRegion::GetOduDefectList(vector<uint32>* theDefectList)
{
    (*this)[0].myOduDefectList.GetKeys(theDefectList);
}

//*****************************************************************************
//-----------------------------------------------------------------------------

SP_ReRouteConfigRegion::SP_ReRouteConfigRegion(FC_BbKey theKey):
    FC_BbRegionVectImp<SP_ArrConfigObject>(theKey, 2)
{
    
}

SP_ReRouteConfigRegion::~SP_ReRouteConfigRegion()
{
}

bool SP_ReRouteConfigRegion::SetConfig(CT_IntfId theInterface, bool isSet)
{
    uint32 theMask =GetRerouteObjectMask(theInterface);
    if (isSet)
    {
        return ((*this)[0].myPortConfigList.Set(theMask));
    }
    else
    {
        return ((*this)[0].myPortConfigList.Clear(theMask));
    }
}

bool SP_ReRouteConfigRegion::IsConfigSet(CT_IntfId theInterface)
{
    uint32 theMask =GetRerouteObjectMask(theInterface);
    return (*this)[0].myPortConfigList.IsSet(theMask);
}

bool SP_ReRouteConfigRegion::SetPhyLayerMonitorEnabled(CT_IntfId theInterface, bool isEnabled)
{
    uint32 theMask =GetRerouteObjectMask(theInterface);
    if (isEnabled)
    {
        return ((*this)[1].myPortConfigList.Set(theMask));
    }
    else
    {
        return ((*this)[1].myPortConfigList.Clear(theMask));
    }
}
bool SP_ReRouteConfigRegion::IsPhyLayerMonitorEnabled(CT_IntfId theInterface)
{
    uint32 theMask =GetRerouteObjectMask(theInterface);
    return (*this)[1].myPortConfigList.IsSet(theMask);
}

bool SP_ReRouteConfigRegion::SetConfig(CT_ODU_Identifier theOdu, bool isSet)
{
    if (isSet)
    {
        return ((*this)[0].myOduConfigList.Set(theOdu.GetIdValue()));
    }
    else
    {
        return ((*this)[0].myOduConfigList.Clear(theOdu.GetIdValue()));
    }
}

bool SP_ReRouteConfigRegion::IsConfigSet(CT_ODU_Identifier theOdu)
{
    return ((*this)[0].myOduConfigList.IsSet(theOdu.GetIdValue()));
}

void SP_ReRouteConfigRegion::GetOduConfigList(vector<uint32>* theConfigList)
{
    (*this)[0].myOduConfigList.GetKeys(theConfigList);
}
