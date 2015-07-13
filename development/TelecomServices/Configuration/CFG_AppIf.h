//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_APPIF_H
#define CFG_APPIF_H

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning (disable:4786)
#endif


#include <AppFramework/FC_BbApp.h>
#include <AppFramework/FC_Context.h>
#include <ErrorService/FC_Error.h>
#include <Configuration/CFG_Definitions.h>
#include <TelCommon/TEL_AppIf.h>
#include <CommonTypes/CT_SystemIds.h>
#include "CFG_Region.h"
#include "CFG_HoldOffTimer.h"
#include <T6100_TelecomIf.h>

class T6100_CardActiveRegion;
class CFG_OptAutomaticAction;
class CFG_OptAutoRateLock;
class CFG_OduAutomaticAction;
class CFG_RsAutomaticAction;
class CFG_GfpAutomaticAction;
class CFG_OtsOchOHAutomaticAction;
class FC_OneShotProcess;
class CFG_HoldOffTimer;

//This is the base configuration application. It declares 
//interface to access configuration region of any layers. 
//This is the interface that should be used by client of 
//signal configuration feature.
//##ModelId=3C3B463E0125
class CFG_AppIf: public TEL_AppIf
{
public:

	//Constructor.
	//##ModelId=3C3B463E0342
    CFG_AppIf(T6100_TelecomIf& theContext);

	//Virtual destructor.
	//##ModelId=3C3B463E0343
    virtual ~CFG_AppIf();

	//##ModelId=3C3B463E0345
    virtual CFG_Region*    GetCfgRegion();
    virtual CFG_Region*    GetAutomaticCfgRegion();
    virtual CFG_Region*    GetOutputCfgRegion();
    virtual CFG_Region*    GetProtCfgRegion();
    virtual CFG_Region*    GetHistoryCfgRegion();
    virtual CFG_Region*    GetAltConfigRegion();
    virtual CFG_Region*    GetCriticalCfgRegion();

    virtual CFG_OptAutoRateLockRegion* GetAutoRateLockRegion();

    virtual CFG_OptAutomaticAction* GetAutomaticAutomaticAction();
    virtual CFG_OduAutomaticAction* GetOduAutomaticAction();
    virtual CFG_RsAutomaticAction*  GetRsAutomaticAction();
    virtual CFG_GfpAutomaticAction* GetGfpAutomaticAction();
    virtual CFG_OtsOchOHAutomaticAction* GetOtsOchOHAutomaticAction();    

    // provide an interface to get the holdoff timer
    // implemented in the target subapplication
    virtual CFG_HoldOffTimer*       GetHoldOffTimer(uint32 theInstance = 0);
    virtual CFG_HoldOffTimer*       GetAltHoldOffTimer(uint32 theInstance = 0);

    virtual void WakeUpNextRun();

class FC_OneShotProcess;

    virtual void DoInitWarm(FC_Object* theObject);
    virtual void DoInitCold(FC_Object* theObject);
    virtual void DoInitConfig(FC_Object* theObject);

    virtual void Display(FC_Stream& theStream, uint16 theObjectIndex = USHRT_MAX);
    virtual FC_CmdProcessor::STATUS Set(int argc,char** argv);
    virtual FC_CmdProcessor::STATUS Debug(int argc,char** argv);
    virtual void Reset(void);

private:

};

#endif //CFG_APPIF_H

