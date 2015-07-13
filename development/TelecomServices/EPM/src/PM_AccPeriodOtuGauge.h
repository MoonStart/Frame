/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     January 6, 2006 Larry Wolfrum.
 DESCRIPTION:   Class for OTU gauge parameters for an accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODOTUGAUGE_H
#define PM_ACCUMULATIONPERIODOTUGAUGE_H

#include <PM/src/PM_AccPeriodGauge.h>

class PM_AccumulationPeriodOtuGauge : public PM_AccumulationPeriodGauge
{
public:

    //Class default constructor.
    PM_AccumulationPeriodOtuGauge(PM_GenericApplication &theGenericApplication,
                              CT_PM_Value*          theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodOtuGauge();

    //Updates All parameters for this accumulation 
    //period.
    virtual bool UpdatePeriodOfAll(PM_BbValue& theValue, 
                                   PM_BbCfg&   theConfig,
                                   bool*       theValidityState,
                                   bool*       theFilteringStateFirstStage,
                                   bool*       theFilteringStateSecondStage,
                                   bool        theEndOfPeriod);

    //Adds a number to a PM value.
    virtual CT_PM_Value AddValue(PM_BbValue&        theValue, 
                                 CT_PM_Parameter    theParam, 
                                 CT_PM_Value        theNumber, 
                                 CT_PM_Value        theMaxValue, 
                                 bool               theUaState, 
                                 bool               thePotential2ChgState, 
                                 bool               theEndOfPeriod);

protected:

};

#endif //PM_ACCUMULATIONPERIODOTUGAUGE_H
