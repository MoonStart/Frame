// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Signal Alarm
//  AUTHOR   :     Michael Sharkey
//  DESCRIPTION:   Report Defect/Flags to AM based upon XCON status.
// --------------------------------------------------------------------------*/

#ifndef ALM_XCONMODIFICATIONACTION_H
#define ALM_XCONMODIFICATIONACTION_H

#include <AM/AM_Definitions.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_TelAlarmCondition.h>

//Forward class declaration
class ALM_AppIf;
class ALM_RsSubApplicationOnCard;
class ALM_HopSubApplicationOnCard;
class ALM_OduSubApplicationOnTrn;
class T6100_CardIf;
class T6100_TelecomIf;

class ALM_XCONModificationAction : public FC_Action
{
public:

	ALM_XCONModificationAction(ALM_AppIf& theAppIf);

	virtual ~ALM_XCONModificationAction();

	void Run(FC_Object* theObject = NULL);

    virtual FC_Object* DoRunWithReason(unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam);

private:

    ////////////////////////////////////////////////////////////////////////////////
    void HandleRsLayer();
    void HandleRsNormalLayer();
    void HandleRsHDTGLayer();
    void HandleRsESMLayer();
    void HandleRsSSM40Layer();
    void HandleRsFGSMLayer();
    void HandleHopLayer();
    void HandleOduLayer();
    void HandleOduFGTMMLayer();
    void HandleOduSSM40Layer();
    void HandleOduFGSMLayer();
    void HandleRSHGTMMLayer();
    void HandleOduHGTMMLayer();
    void HandleRSHDTG2Layer();
    void HandleRsEnhTrnLayer();
    void HandleRsTrnLayer();
    ////////////////////////////////////////////////////////////////////////////////

    ALM_AppIf& myAppIf;

    ALM_RsSubApplicationOnCard* myRsAppIf;

    ALM_HopSubApplicationOnCard* myHopAppIf;

    ALM_OduSubApplicationOnTrn* myOduAppIf;

    T6100_CardIf* myCardIf;

    bbindex_t myPortNumber; // 0..9 PORT side ports.
    
    CT_DirectionFlag myDirection; // LINE or PORT (HOP).

};

#endif /* ALM_XCONMODIFICATIONACTION_H */
