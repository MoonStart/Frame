//Copyright(c) Tellabs Transport Group. All rights reserved
//This file contains definitions for all regions (and associated objects) related to Automatic ReRoute
#ifndef SP_ARRREGION_H
#define SP_ARRREGION_H

#include <Blackboard/FC_BbRegionVectImp.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include "SP_Definitions.h"
#include "SP_BitSetDataObject.h"
#include "SP_MapDataObject.h"
#include <map>

extern const FC_BbKey SP_REROUTE_DEFECTS_REGION_KEY;
extern const FC_BbKey SP_REROUTE_CONFIG_REGION_KEY;

/** Port reroute defect object */
class SP_ArrDefectObject : public FC_BbObject
{
public:

    friend class SP_ReRouteDefectRegion;

    /** Default constructor.*/
    SP_ArrDefectObject(void);
    virtual ~SP_ArrDefectObject();
//-----------------------------------------------------------------------------

    
    //Add Set and Get methods here
    bool SetDefect(uint8 theIndex, CT_SP_DefectLayer theMask);
    bool IsDefectSet(uint8 theIndex, CT_SP_DefectLayer theMask);
    bool ClearDefect(uint8 theIndex, CT_SP_DefectLayer theMask);
    uint8 GetDefects(uint8 theIndex);
//-----------------------------------------------------------------------------

protected:
    virtual ostream& WriteObject( ostream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------

private:
    //Add class data members here
    uint8 myPortDefectList[SP_MAX_ARR_DEFECT_PORT_COUNT];
    SP_MapDataObject myOduDefectList;
};

/** Arr config object */
class SP_ArrConfigObject : public FC_BbObject
{
public:

    friend class SP_ReRouteConfigRegion;
    /** Default constructor.*/
    SP_ArrConfigObject(void);
    virtual ~SP_ArrConfigObject();
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

protected:
    virtual ostream& WriteObject( ostream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------

private:
    //Add class data members here
    SP_BitSetDataObject myPortConfigList;
    SP_MapDataObject myOduConfigList;
};


/** Region used to contain reroute defect data */
class SP_ReRouteDefectRegion : public FC_BbRegionVectImp<SP_ArrDefectObject>
{
public:
    /** Constructor.
    @param theKey: The region key. */
    SP_ReRouteDefectRegion(FC_BbKey theKey);
    virtual ~SP_ReRouteDefectRegion();
//-----------------------------------------------------------------------------

   //Add set and get methods here
    bool SetDefects(CT_IntfId theInterface, uint8 defectMask);
    bool ClearDefects(CT_IntfId theInterface);
    bool IsDefectSet(CT_IntfId theInterface);
    uint8 GetDefectList(CT_IntfId theInterface);

    bool SetDefects(CT_ODU_Identifier theOdu);
    bool ClearDefects(CT_ODU_Identifier theOdu);
    bool IsDefectSet(CT_ODU_Identifier theOdu);

    void GetOduDefectList(vector<uint32>* theDefectList);
    
//-----------------------------------------------------------------------------
};

/** Region used to contain reroute config data */
class SP_ReRouteConfigRegion : public FC_BbRegionVectImp<SP_ArrConfigObject>
{
public:
    /** Constructor.
    @param theKey: The region key. */
    SP_ReRouteConfigRegion(FC_BbKey theKey);
    virtual ~SP_ReRouteConfigRegion();
//-----------------------------------------------------------------------------

   //Add set and get methods here
    bool SetConfig(CT_IntfId theInterface, bool isSet);
    bool IsConfigSet(CT_IntfId theInterface);

    bool SetPhyLayerMonitorEnabled(CT_IntfId theInterface, bool isEnabled);
    bool IsPhyLayerMonitorEnabled(CT_IntfId theInterface);

    bool SetConfig(CT_ODU_Identifier theOdu, bool isSet);
    bool IsConfigSet(CT_ODU_Identifier theOdu);

    void GetOduConfigList(vector<uint32>* theConfigList);
    
//-----------------------------------------------------------------------------
};

#endif /* SP_RESOURCEREGION_H */
