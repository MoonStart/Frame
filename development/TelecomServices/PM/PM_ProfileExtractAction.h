/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTMU, SSM, HDTG.
 AUTHOR   :     Michael Sharkey
--------------------------------------------------------------------------*/

#ifndef PM_PROFILE_EXTRACT_ACTION_H
#define PM_PROFILE_EXTRACT_ACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_PM_Definition.h>

class PM_GenericApplication;
class PM_HopNearEndSubApplication;
class PM_OduSubApplication;
class PM_OduGaugeSubApplication;
class PM_TcmSubApplication;
class PM_TcmGaugeSubApplication;

using namespace std;

class PM_ProfileExtractAction: public FC_Action
{
public:

    PM_ProfileExtractAction(PM_GenericApplication* thePMSubApp);
    
    virtual ~PM_ProfileExtractAction();

    virtual void Run(FC_Object* theObject = NULL);


protected:

private:

    void ProcessProfileHopAction(PM_HopNearEndSubApplication* theHopPmSubApp);
    void ProcessPMCfgHopAction(PM_HopNearEndSubApplication* theHopPmSubApp);

    void ProcessProfileOduAction(PM_OduSubApplication* theOduPmSubApp);
    void ProcessPMCfgOduAction(PM_OduSubApplication* theOduPmSubApp);

    void ProcessProfileOduGaugeAction(PM_OduGaugeSubApplication* theOduGaugePmSubApp);
    void ProcessPMCfgOduGaugeAction(PM_OduGaugeSubApplication* theOduGaugePmSubApp);

    void ProcessProfileTcmAction(PM_TcmSubApplication* theTcmPmSubApp);
    void ProcessPMCfgTcmAction(PM_TcmSubApplication* theTcmPmSubApp);

    void ProcessProfileTcmGaugeAction(PM_TcmGaugeSubApplication* theTcmGaugePmSubApp);
    void ProcessPMCfgTcmGaugeAction(PM_TcmGaugeSubApplication* theTcmGaugePmSubApp);

    PM_GenericApplication* myPMSubApp;
};

#endif // PM_PROFILE_EXTRACT_ACTION_H 
