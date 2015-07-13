// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Signal Alarm
//  TARGET   :     APM
//  AUTHOR   :     Marc Vendette, Patrick Meehan
//  DESCRIPTION:   The class object, when instantiated, is the primary interface
//                 to Alarm Management (AM) and reports changes to the Signal
//                 Alarm regions.
// --------------------------------------------------------------------------*/

#ifndef ALM_FAILUREMODIFICATIONACTION_H
#define ALM_FAILUREMODIFICATIONACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <AM/AM_Definitions.h>
#include <CommonTypes/CT_TelAlarmCondition.h>
#include "../ALM_FailureRegionImp.h"

//Forward class declaration
class ALM_AppIf;
class ALM_FailureBase;
class T6100_CardIf;
class T6100_TelecomIf;

template <class OBJECT_TYPE> class ALM_FailureRegionImp;

//This action is responsible to call the Alarm Management interface when a signal alarm occurred.
class ALM_FailureModificationAction : public FC_Action
{
public:

	/**
	 * Constructor of this class.
	 */
    ALM_FailureModificationAction(ALM_AppIf& theAppIf, T6100_CardIf* theCardIf, T6100_TelecomIf* theRptIf = NULL);
	ALM_FailureModificationAction(ALM_AppIf& theAppIf, T6100_TelecomIf* theT1E1If);
    
    /**
	 * Virtual destructor.
	 */
	virtual ~ALM_FailureModificationAction();

	//Obsolete.
	void Run(FC_Object* theObject = NULL);

    virtual FC_Object* DoRunWithReason(unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam);

    bool isLOFLOCAlmExists();

private:

    //==============================================================================

    void         InitUidTable();
    void         CustomizeUIDTableForScCardFamily();
    void         ALM_CalculatePortOffset();
    AM_UID       GetUIDFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theAlarmType) const;
    CT_Direction GetCTDirection() const;
    CT_Side      GetCTSide() const;
    HGTMMS_FGEHGE_PORTGROUP_TYPE GetHgtmmsFgeHgePortGroupType(CT_IntfId thePort);
    HGTMMS_FGEHGE_PORTGROUP_MAP GetHgtmmsFgeHgePortGroupMap(CT_IntfId thePort);
    void         SetFgeHgeLedGroupLos(bool isSet, time_t anOccurTime = 0);
    bool         IsFgeHgeGroupHasLos();
    CT_IntfId    GetFgeHgeGroupRepresentPort();

    bool HandleT1E1FailureAction();
    bool HandleSignalProtectFailureAction();
    bool HandleGenericFailureAction(CT_CardFamily aCardFamily);

    bool HandleOtsOmsFailureAction(CT_CardFamily aCardFamily);
    bool HandleOchFailureAction(CT_CardFamily aCardFamily);
    bool HandleOptFailureAction(CT_CardFamily aCardFamily);
    bool HandleRsFailureAction(CT_CardFamily aCardFamily);
    bool HandleMsFailureAction(CT_CardFamily aCardFamily);
    bool HandleOtuFailureAction(CT_CardFamily aCardFamily);
    bool HandleOduFailureAction(CT_CardFamily aCardFamily);
    bool HandleGfpFailureAction(CT_CardFamily aCardFamily);
    bool HandleHopFailureAction(CT_CardFamily aCardFamily);
    bool HandleVcgFailureAction(CT_CardFamily aCardFamily);
    bool HandleSyncFailureAction(CT_CardFamily aCardFamily);

    bool isStartChannelUsed() const;

    bool isOtsOms() const;
    bool isOch() const;
    bool isOpt() const;
    bool isRs() const;
    bool isMs() const;
    bool isOtu() const;
    bool isOdu() const;
    bool isTcm() const;
    bool isGfp() const;
    bool isHop() const;
    bool isVcg() const;
    bool isSync() const;
    bool isDccl() const;
    bool isGcc() const;

    //==============================================================================

    T6100_CardIf* myCardIf;
    T6100_TelecomIf* myT1E1If;
    T6100_TelecomIf* myRptIf;
    ALM_AppIf& myAppIf;
    AM_UID theirUidTable[CT_TelAlarmCondition::ALM_NB_OF_ALARM];
    AM_PortType myAmPortType;
    unsigned char myPortOffset;
    bool myStartChannelProvisionedHasDefect[48];
    bool myLOFLOCAlmExists;
};

#endif /* ALM_FAILUREMODIFICATIONACTION_H */
