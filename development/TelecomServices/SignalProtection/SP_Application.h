// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_APPLICATION_INCLUDED
#define _INC_SP_APPLICATION_INCLUDED

#include <AppFramework/FC_BbApp.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>

class T6100_CardIf;
class T6100_TelecomIf;
class SP_SwitchingStatistic;
class SP_SwitchingCommandResult;
class SP_SwitchingCommand;
class SP_ProtectionGroupStatusRegion;
class SP_ProtectionGroupConfigRegion;
class FC_WakeUpProcessAction;

//This class is the base application for all sub-application 
//in the Signal Protection feature. It hold pointer to the 
//configuration and status region as well as an indication 
//about last boot type. It inherits from FC_Application.
class SP_Application : public FC_BbApp  
{
public:
	//Constructor. Requires the PCSM context.
	SP_Application(T6100_CardIf& theCardContext, T6100_TelecomIf& theContext);
	//Destructor.
	virtual ~SP_Application();
	//Return a reference to the config region.
    SP_ProtectionGroupConfigRegion& GetConfigRegion() 
    { 
        return *myConfigRegion;
    }

	//Return a reference to the status region.
    SP_ProtectionGroupStatusRegion& GetStatusRegion() 
    { 
        return *myStatusRegion;
    }

	//Return a reference to the status region.
    const CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*>& GetStatisticsRegionPair() 
    { 
        return myStatRegions;
    }

	//Set the colld boot flag to true.
	virtual void InitCold(FC_Object* theObject = NULL);
    
	//provide an interface to get the status collector action
	//implemented in the target subapplication
	virtual FC_WakeUpProcessAction* GetStatusCollectionAction();
	virtual FC_WakeUpProcessAction* GetLongDelayStatusCollectionAction();
	//True if last boot type was cold.
    static bool myColdBoot;

    T6100_CardIf& GetCardContext() const ;
    T6100_TelecomIf& GetContext() const;

protected:
	//Pointer to the configuration region.
	SP_ProtectionGroupConfigRegion* myConfigRegion;
	//Pointer to the status region.
	SP_ProtectionGroupStatusRegion* myStatusRegion;

    CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*> myStatRegions;

	//Reference to the SmartCard context.
    T6100_CardIf& myCardContext;

    //Reference to the application context
    T6100_TelecomIf& myContext;

};

#endif // _INC_SP_APPLICATION_INCLUDED
