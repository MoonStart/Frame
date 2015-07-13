// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_OCHAUTOMATICACTION_INCLUDED
#define _INC_CFG_OCHAUTOMATICACTION_INCLUDED

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "CFG_HwRefreshAction.h"
#include "CFG_PilotToneAssignment.h"
#include <gdef.h>
#include <Monitoring/MON_Definitions.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_PilotToneAction.h>
#include <PII_TickTimer.h>
#include <TsPii/TSPII_Region.h>
#include <ExecutionSupport/FC_BaseTimer.h>

// Forward declaration of class.
class MON_AppIf;
class CFG_AppIf;
class FC_TimedProcess;

//This class is an action that automatically performs
//some action on the transmission of RS layer.
class CFG_TxOchAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_TxOchAutomaticAction(CFG_AppIf& theAppIf, 
                             CFG_AppIf* theCfgOptAppIf, 
                             MON_AppIf* theMonAppIf,
                             MON_OchStatusRegion* theAcStatusRegion,
                             TSPII_PilotToneRegion* theTspiiPilotToneRegion,
                             TSPII_OpticalRegion* theTspiiOpticalRegion,
                             MON_OptDefectsRegion& theOptDefectsRegion,
                             CT_CardType theCardType,
                             MON_AppIf* theMonOchLineAppIf);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_TxOchAutomaticAction();
    void UpdateObject(unsigned theRunReason);

    void EnableTrace(bool theTraceEnable);

private:
    void UpdatePowerStatus(MON_OchStatusRegion& aRegion, 
                           uint32 theSamples, 
                           MON_PilotToneAction& theAction,
                           MON_RelativeTraceId theTraceId);
    MON_RelativeTraceId GetActualRelativeTraceId(const CT_Wavelength& theChannelId, bool theG709Enable) const;

    CFG_AppIf* myCfgOptAppIf;
    MON_OtuStatusRegion* myOtuStatusRegion;
    MON_OchStatusRegion* myOchStatusRegion;
    MON_OptDefectsRegion& myOptDefectsRegion;
    TSPII_PilotToneRegion* myTspiiPilotToneRegion;
    TSPII_OpticalRegion* myTspiiOpticalRegion;
    MON_OchStatusRegion myDcStatusRegion;
    MON_OchStatusRegion* myAcStatusRegion;
    FC_Milliseconds myRefreshRequestTime;
    FC_Milliseconds myNextUpdateTime;
    FC_Milliseconds myUpdateRate;
    MON_PilotToneAction myDcPilotToneAction;
    bool myCorrectionFilter;
    FC_TimedProcess* myTimedProcess;
    FC_BaseTimer myLastIdChangeExpirationTimer;
    bool myLastIdChangeExpirationTimerStopped;
    bool myRetrieveTxIdFromPII;
    MON_AppIf* myMonOchLineAppIf;

    uint32 myPtMaxTxAmp;
    uint32 myPtMinTxAmp;

    bool   myAmpliRatioNeeded;
    float  myPtMaxTxAmpRatio;
    float  myPtMinTxAmpRatio; 

    bool myTraceEnabled;
    RESTART_TYPE myRestartType;
};



#endif /* _INC_CFG_OCHAUTOMATICACTION_INCLUDED */
