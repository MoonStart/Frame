/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 DESCRIPTION:   Class for Odu gauge parameters for an accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODOduGAUGE_H
#define PM_ACCUMULATIONPERIODOduGAUGE_H

#include <PM/src/PM_AccPeriodGauge.h>

class PM_AccumulationPeriodOduGauge : public PM_AccumulationPeriodGauge
{
public:

    //Class default constructor.
    PM_AccumulationPeriodOduGauge(PM_GenericApplication &theGenericApplication,
                              CT_PM_Value*          theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodOduGauge();

    //This method verifies if each entity inhibition is 
    //enabled or not. If not it calls update period of each entity.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

protected:

    //Verifies if there is a pending threshold configuration.
    virtual bool VerifyConfigChange();

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);
};

#endif //PM_ACCUMULATIONPERIODOduGAUGE_H
