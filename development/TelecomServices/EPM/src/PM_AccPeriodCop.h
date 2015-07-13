
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 3, 2010 Larry Wolfrum.
 DESCRIPTION:   Class for all COP parameters for an accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODCOP_H
#define PM_ACCUMULATIONPERIODCOP_H

#include <PM/src/PM_AccPeriodGauge.h>
#include <PM/PM_GenericApplication.h>


// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_Rules;
class PM_GenericApplication;
template <class OBJECT_TYPE> class PM_RegionImp;

class PM_AccumulationPeriodCop : public PM_AccumulationPeriodGauge
{
public:

    PM_AccumulationPeriodCop(PM_GenericApplication    &theGenericApplication,
                             CT_PM_Value*             theMaxValueTable,
                             PM_Rules&                theRules,
                             uint32                   theNumberOfParam,
                             uint32                   thePortNumber,
                             CT_PM_Period             thePeriod);

    virtual ~PM_AccumulationPeriodCop();

    //Updates the PM parameters of a given accumulation 
    //period. This class must be overload by the derived 
    //class.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    virtual bool UpdateEndPeriod();

    //Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    virtual void AdjustCurrentIdf();

protected:


    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

	// Adjusts the current value data and IDF states
	// based on directionless state.
    virtual bool AdjustForDirectionless( PM_BbValue& theValue );

    bool myDisableCopInhibit;
    bool myPrevDirectionlessState;
};

#endif //PM_ACCUMULATIONPERIODCOP_H
