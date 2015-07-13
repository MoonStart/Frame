//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef MON_UPDATESTATUSACTION_H
#define MON_UPDATESTATUSACTION_H

#include <CommonTypes/CT_Telecom.h>
#include <ExecutionSupport/FC_Action.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <string>

class MON_AppIf;
class FC_BbAction;

//This action is invoked periodically in order to update 
//statuses with current hardware registers values.
//##ModelId=3C0FE66D03B8
class MON_UpdateStatusAction : public FC_Action
{
public:

	//Constructor for .
	//##ModelId=3C0FE66D03C0
    MON_UpdateStatusAction(MON_AppIf& theMonIf,
                           MON_AppIf* theUpstreamLayerIf);

	//Virtual destructor of the class.
	//##ModelId=3C0FE66D03DF
    virtual ~MON_UpdateStatusAction();

	//##ModelId=3C3B52F00269
    MON_AppIf& GetMonIf() { return myMonIf;}
	//##ModelId=3C7170D501BD
    MON_AppIf* GetUpstreamLayerMonIf() { return myUpstreamLayerIf;}
	//##ModelId=3C7170D501D1
    bool IsUpstreamLayerFailed() const;
    bool IsUpstreamLayerFailedForMaintSig() const;
    bool IsUpstreamLayerFailedNTA() const;
    bool IsUpstreamLayerLocked() const;

    // New for 5.1, Intrnal Failure/Lock is propagated
    bool IsUpstreamLayerInternalFailed() const;
    bool IsUpstreamLayerInternalLocked() const;
    bool IsUpstreamLayerInternalFailedForMaintSig() const;

    bool IsUpstreamLayerInternalPropagateNextLayer() const;

    bool IsUpstreamLayerTermLpbk() const;

    bool IsUpstreamLayerDegrade() const;

    virtual bool GetInternalRealTimeDefects(uint16 index = 0, uint8 facNumber = 0, CT_TEL_Defect theDefect = CT_TEL_OCH_LOSS_PTONE_DEFECT);
    virtual bool GetExternalRealTimeDefects(uint16 index = 0, uint8 facNumber = 0, CT_TEL_Defect theDefect = CT_TEL_OCH_LOSS_PTONE_DEFECT);

	//##ModelId=3C7170D501E6
    FC_BbAction* GetBbAction() { return myBbAction; }

    virtual const char* GetInstanceName(void ) const;
    
    void Run(FC_Object* theObject = NULL);
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL) = 0;
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL) = 0;
    static bool myEnable;

protected:
private:
    void SetInstanceName();

	//##ModelId=3C3B52F002A6
    MON_AppIf& myMonIf;
	//##ModelId=3C7170D50222
    MON_AppIf* myUpstreamLayerIf;
	//##ModelId=3C7170D50240
    FC_BbAction* myBbAction;
    string itsInstanceName;


};

#endif  // MON_UPDATESTATUSACTION_H
