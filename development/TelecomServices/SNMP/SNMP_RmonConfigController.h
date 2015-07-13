
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:
 TARGET   :
 AUTHOR   :
 DESCRIPTION:
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONCONFIGCONTROLLER_H
#define SNMP_RMONCONFIGCONTROLLER_H

#include <vector>
#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Monitoring/MON_AppIf.h>
#include <Configuration/CFG_Opt.h>
#include <SNMP/SNMP_RmonRegion.h>
#include <SNMP/SNMP_RmonConfig.h>
#include <SNMP/SNMP_RmonData.h>
#include <SNMP/SNMP_SystemRegion.h>
#include <vector>

class CFG_Region;
class CT_SNMP_Utilization;
class MON_AppIf;

using namespace std;

template <class DATA_REGION, class CFG_REGION, class DATA_FWD_REGION = DATA_REGION>
class SNMP_RmonConfigController
{
public:
    SNMP_RmonConfigController(DATA_REGION*     theDataRegion,
                              CFG_REGION*      theCfgRegion,
                              DATA_FWD_REGION* theDataFwdRegion = NULL) :
        myCfgRegion(theCfgRegion),
        myDataRegion(theDataRegion),
        myDataFwdRegion(theDataFwdRegion) { }
    virtual ~SNMP_RmonConfigController() { }

    void UpdateConfig();
protected:

    vector<int>      myUpdateIndices;
    CFG_REGION*      myCfgRegion;
    DATA_REGION*     myDataRegion;
    DATA_FWD_REGION* myDataFwdRegion;

private:
    SNMP_RmonConfigController();

};

template <class DATA_REGION, class CFG_REGION, class DATA_FWD_REGION>
inline void SNMP_RmonConfigController<DATA_REGION, CFG_REGION, DATA_FWD_REGION>::UpdateConfig()
{
    unsigned int loopIndex, dataIndexCount, cfgIndexCount;
    myUpdateIndices.erase(myUpdateIndices.begin(), myUpdateIndices.end());

    SNMP_BbRmonData* dataObj = NULL;
    SNMP_BbRmonData* dataFwdObj = NULL;
    for (loopIndex = 0; loopIndex < myCfgRegion->Size(); loopIndex++)
    {
        SNMP_BbRmonEtherCfg& cfgObj = static_cast<SNMP_BbRmonEtherCfg&> ((*myCfgRegion)[loopIndex]);
        if (cfgObj.IsValidIndex())
        {
            // Update RMON entry index value.
            if (myDataRegion->DoesEntryExist(cfgObj.GetIndex()))
            {
                dataObj = static_cast<SNMP_BbRmonData *> (&((myDataRegion->GetEntry(cfgObj.GetIndex()))));
                if (cfgObj.IsCollectionEnabled())
                {
                    if (!dataObj->IsCollectionEnabled())
                    {
                        dataObj->SetIndex(cfgObj.GetIndex());
                        if (myDataFwdRegion)
                        {
                            dataFwdObj = static_cast<SNMP_BbRmonData *> (&((myDataFwdRegion->GetEntry(cfgObj.GetIndex()))));
                            dataFwdObj->SetIndex(cfgObj.GetIndex());
                        }
                        myUpdateIndices.push_back(loopIndex);
                    }
                }
            }
            // Create new RMON entry
            else
            {
                // If room for entry is not available, clean up myDataRegion.
                if (myDataRegion->DoesUnusedEntryExist() == false)
                {
                    // Iterate through all objects in myDataRegion
                    for (dataIndexCount = 0; dataIndexCount < myDataRegion->Size(); dataIndexCount++)
                    {
                        SNMP_BbRmonData& loopDataObj = static_cast<SNMP_BbRmonData&> ((*myDataRegion)[dataIndexCount]);

                        // If this data object has collection enabled, check if corresponding
                        // cfg object exists.
                        if (loopDataObj.IsCollectionEnabled() == true)
                        {
                            bool matchFound = false;
                            for (cfgIndexCount = 0; cfgIndexCount < myCfgRegion->Size() && matchFound == false; cfgIndexCount++)
                            {
                                SNMP_BbRmonEtherCfg& loopCfgObj = static_cast<SNMP_BbRmonEtherCfg&> ((*myCfgRegion)[cfgIndexCount]);
                                if ( (loopCfgObj.IsCollectionEnabled() == true) &&
                                     (loopCfgObj.GetIndex() == loopDataObj.GetIndex()) )
                                {
                                    matchFound = true;
                                }
                            }

                            if (matchFound == false)
                            {
                                // This data object is stale so free it for subsequent use.
                                loopDataObj.DisableCollection();
                            }
                        }
                    }
                }

                // If room for entry is not available, clean up myDataFwdRegion.
                if (myDataFwdRegion != NULL)
                {
                    if (myDataFwdRegion->DoesUnusedEntryExist() == false)
                    {
                        // Iterate through all objects in myDataRegion/myDataFwdRegion
                        for (dataIndexCount = 0; dataIndexCount < myDataRegion->Size(); dataIndexCount++)
                        {
                            SNMP_BbRmonData& loopDataFwdObj = static_cast<SNMP_BbRmonData&> ((*myDataFwdRegion)[dataIndexCount]);

                            // If this data object has collection enabled, check if corresponding
                            // cfg object exists.
                            if (loopDataFwdObj.IsCollectionEnabled() == true)
                            {
                                bool matchFound = false;
                                for (cfgIndexCount = 0; cfgIndexCount < myCfgRegion->Size() && matchFound == false; cfgIndexCount++)
                                {
                                    SNMP_BbRmonEtherCfg& loopCfgObj = static_cast<SNMP_BbRmonEtherCfg&> ((*myCfgRegion)[cfgIndexCount]);
                                    if ( (loopCfgObj.IsCollectionEnabled() == true) &&
                                         (loopCfgObj.GetIndex() == loopDataFwdObj.GetIndex()) )
                                    {
                                        matchFound = true;
                                    }
                                }

                                if (matchFound == false)
                                {
                                    // This data object is stale so free it for subsequent use.
                                    loopDataFwdObj.DisableCollection();
                                }
                            }
                        }
                    }
                }

                try
                {
                    // New entry configuration
                    dataObj = static_cast<SNMP_BbRmonData *> (&((myDataRegion->CreateNewEntry(cfgObj.GetIndex()))));
                    dataObj->SetIndex(cfgObj.GetIndex());
                    if (myDataFwdRegion)
                    {
                        dataFwdObj = static_cast<SNMP_BbRmonData *> (&((myDataFwdRegion->CreateNewEntry(cfgObj.GetIndex()))));
                        dataFwdObj->SetIndex(cfgObj.GetIndex());
                    }
                    myUpdateIndices.push_back(loopIndex);
                }
                catch (FC_RuntimeError theError)
                {
                    // Table full
                    theError.ReportError();
                    continue;
                }
            }

            // Enable/disable collection mode
            if (cfgObj.IsCollectionEnabled())
            {
                if (!dataObj->IsCollectionEnabled())
                {
                    myUpdateIndices.push_back(loopIndex);
                    dataObj->EnableCollection();
                    if (dataFwdObj)
                    {
                        dataFwdObj->EnableCollection();
                    }
                }
            }
            else
            {
                if (dataObj->IsCollectionEnabled())
                {
                    //myUpdateIndices.push_back(loopIndex);
                    dataObj->DisableCollection();
                    dataObj->ResetAll();
                    if (myDataFwdRegion)
                    {
                        dataFwdObj = static_cast<SNMP_BbRmonData *> (&((myDataFwdRegion->GetEntry(cfgObj.GetIndex()))));
                        if (dataFwdObj)
                        {
                            dataFwdObj->DisableCollection();

                        }
                    }
                }
            }
        }
    }
}


class  SNMP_RmonEtherStatsCfgCtrl : public SNMP_RmonConfigController<SNMP_RmonEtherStatsDataRegion,
                                  SNMP_RmonEtherStatsCfgRegion>
{
public:
    SNMP_RmonEtherStatsCfgCtrl(SNMP_RmonEtherStatsCfgRegion*  theStatsCfgRegion,
                               SNMP_RmonEtherStatsDataRegion* theStatsDataRegion,
                               SNMP_SysUpTimeRegion*          theSysUpTimeRegion);
    virtual ~SNMP_RmonEtherStatsCfgCtrl();
    void UpdateEtherStatsConfig();
private:
    SNMP_SysUpTimeRegion*            mySysUpTimeRegion;
};

class SNMP_RmonEtherHistCfgCtrl : public SNMP_RmonConfigController<SNMP_RmonEtherHistStorageRegion,
                                  SNMP_RmonEtherHistCfgRegion, SNMP_RmonEtherHistDataRegion>
{
public:
    SNMP_RmonEtherHistCfgCtrl(SNMP_RmonEtherHistCfgRegion*     theStatsCfgRegion,
                              SNMP_RmonEtherHistStorageRegion* theStatsDataRegion,
                              SNMP_RmonEtherHistDataRegion*    theDataFwdRegion,
                              SNMP_SysUpTimeRegion*  theSysUpTimeRegion,
                              CFG_Region* theOptCfgRegion,
                              MON_AppIf& theMonApp,
                              CFG_AppIf& theCfgApp,
                              MON_AppIf* theMacMonApp);
    virtual ~SNMP_RmonEtherHistCfgCtrl();
    void UpdateEtherHistConfig(vector<CT_SNMP_Utilization>& theUtilizationMonitors);
    CT_TEL_daHz GetBitRate(CFG_Opt* aOptCfgObject);
    uint32 GetRateMultiplier(CFG_Opt* aOptCfgObject);
    CT_TEL_daHz SignalTypeToBitRate( CT_TEL_SignalType theSignalType );
    void MapToPayloadBitRate( CT_TEL_daHz& theBitRate );
    void SetUtilBitRate(CT_TEL_daHz theBitRate);
    CT_TEL_daHz GetUtilBitRate();

private:
    SNMP_SysUpTimeRegion*            mySysUpTimeRegion;
    CFG_Region*                      myOptCfgRegion;
    MON_AppIf&                       myMonApp;
    MON_AppIf*                       myMacMonApp;
    CFG_AppIf&                       myCfgRsApp;
    CT_TEL_daHz                      myUtilBitRate;

};
#endif //SNMP_RMONCONFIGCONTROLLER_H
