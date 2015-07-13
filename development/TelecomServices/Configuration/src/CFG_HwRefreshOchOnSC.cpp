// //Copyright(c Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include "../CFG_HwRefreshOchOnSC.h"
#include "../CFG_Och.h"
#include "../CFG_OchAutoOnSC.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_PipeIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ITS/ITS_AppIfMain.h>
#include <ITS/ITS_Region.h>
#include <ITS/ITS_Config.h>
#include <T6100_MainAppIf.h>
#include <CSM/CSM_ConfigStatus.h>
#include <CSM/CSM_AppIf.h>
#include <T6100_OpticalShelfSlotIf.h>
#include <T6100_OpticalShelfIf.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_OchHistory.h>
#include <ITS/ITS_SubApplicationConfigForSC.h>

const FC_Milliseconds CFG_OCH_REFRESH_PERIOD        = (20 * 60 * 1000);// 20 minutes

CFG_HwRefreshOchOnSC::CFG_HwRefreshOchOnSC(CFG_AppIf& theCfgIf,
                                   TSPII_PipeRegion& thePipePiiRegion,
                                   unsigned int thePipePiiUnit,
                                   CT_Side theSide) :
    CFG_HwRefreshAction(theCfgIf),
    myPipePiiRegion(thePipePiiRegion),
    myCardContext(NULL),
    myPipePiiUnit(thePipePiiUnit),
    mySide(theSide),
    myHistoryCfgRegion(NULL),
    myRefreshTimer(CFG_OCH_REFRESH_PERIOD),
    myHistorySize(0)
{
    myCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    FC_THROW_ERROR_IF(myCardContext==NULL, FC_RuntimeError, "Cannot get card context");

    // false required until autopower adjustment is implemented
    GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion(),false);
    myHistoryCfgRegion = static_cast<CFG_OchHistoryCfgRegion*>(theCfgIf.GetHistoryCfgRegion());
    if(myHistoryCfgRegion)
        GetBbAction()->AddOutputRegion(myHistoryCfgRegion);

    for(int i = 0; i < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        myPrevGain[i]= TRAFFIC_DEFAULT_POWER;
    }    

    myRefreshTimer.Start();
}

CFG_HwRefreshOchOnSC::~CFG_HwRefreshOchOnSC()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());

    if(myHistoryCfgRegion)
       GetBbAction()->RemoveOutputRegion(myHistoryCfgRegion);
}

FC_Object* CFG_HwRefreshOchOnSC::Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    uint32 aSize  = GetCfgIf().GetAutomaticCfgRegion()->Size();
    myHistorySize = GetCfgIf().GetHistoryCfgRegion()->Size();   

    uint32 aIndex=0;
    while (aIndex<aSize)
    {
        UpdateObject(theRunReason, aIndex);
        aIndex++;
    }

    Commit();
    return NULL;
}

bool CFG_HwRefreshOchOnSC::UpdateObject(unsigned theRunReason, uint32 theIndex)
{
    TSPII_PipeIf& aPipePii = myPipePiiRegion[0];

    CT_TEL_mBm aGain = 0;
    uint8 aPortNumber = CT_TEL_INVALID_PORT_NUMBER;
    bool hasEvoaChanged = false;

    CFG_OchAutoOnSC& aAutoCfgObject = static_cast<CFG_OchAutoOnSC&>((*GetCfgIf().GetAutomaticCfgRegion())[(bbindex_t)theIndex]);
    aGain = aAutoCfgObject.GetGain();
    aPortNumber = aAutoCfgObject.GetPortNumber();
    bool activePath = aAutoCfgObject.GetActivePath();
    
    if (aGain != TRAFFIC_DEFAULT_POWER && (abs(aGain) != abs(myPrevGain[theIndex])))
    {
        hasEvoaChanged = true;
    }
   
    if (hasEvoaChanged)
    {
        if ((myHistoryCfgRegion) && (theIndex < myHistorySize)) 
       {
    	    CFG_OchHistory& aOchHist = (*myHistoryCfgRegion)[(bbindex_t)theIndex];
    	    aOchHist.RecordHistory(aGain, myPrevGain[theIndex]);
    	    aOchHist.RecordMoreHistory(activePath, aPortNumber);
       }
    }

    if (activePath == true)
    {
        aPipePii.SetActivePath(theIndex, activePath);
        aPipePii.SetPortNumber(aPortNumber, theIndex);
        aPipePii.SetEvoa(aGain, theIndex);
        //aPipePii.CommitEvoas();
    }
    else
    {
        aPipePii.SetActivePath(theIndex, activePath);
        aPipePii.SetPortNumber(CT_TEL_INVALID_PORT_NUMBER, theIndex);
        aPipePii.SetEvoa(TRAFFIC_DEFAULT_POWER, theIndex);
        //aPipePii.CommitEvoas();
    }

    myPrevGain[theIndex] = aGain;

    return true;
 }

void CFG_HwRefreshOchOnSC::Commit()
{
    TSPII_PipeIf& aPipePii = myPipePiiRegion[0];
    aPipePii.CommitEvoas();
}
 
uint32 CFG_HwRefreshOchOnSC::GetWavelengthFromEvoa(uint32 theEvoa) const
{
    return 0;
}
