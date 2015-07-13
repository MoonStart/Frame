/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 15, 2002 Sebastien Cossette.
 DESCRIPTION:   Base class for all counter parameters for an accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODCOUNTER_H
#define PM_ACCUMULATIONPERIODCOUNTER_H

#include <PM/src/PM_AccPeriod.h>
#include <PM/PM_GenericApplication.h>


// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_Rules;
class PM_GenericApplication;
template <class OBJECT_TYPE> class PM_RegionImp;

//##ModelId=3E6E4CC101F6
class PM_AccumulationPeriodCounter : public PM_AccumulationPeriod
{
public:

    //##ModelId=3E6E4CC2034C
    PM_AccumulationPeriodCounter(PM_GenericApplication  &theGenericApplication,
                                 CT_PM_Value*           theMaxValueTable,
                                 PM_Rules&              theRules,
                                 uint32                 theNumberOfParam,
                                 uint32                 thePortNumber,
                                 CT_PM_Period           thePeriod);

    PM_AccumulationPeriodCounter(PM_GenericApplication  &theGenericApplication,
                                 CT_PM_64BitValue*      theMaxValueTable,
                                 PM_Rules&              theRules,
                                 uint32                 theNumberOfParam,
                                 uint32                 thePortNumber,
                                 CT_PM_Period           thePeriod);

    //##ModelId=3E6E4CC20388
    virtual ~PM_AccumulationPeriodCounter();

    //Updates All parameters for this accumulation 
    //period.
    //##ModelId=3E6E4CC20392
    virtual bool UpdatePeriodOfAll(PM_BbValue& theValue, 
                                   PM_BbCfg&   theConfig,
                                   bool*       theValidityState,
                                   bool*       theFilteringStateFirstStage,
                                   bool*       theFilteringStateSecondStage,
                                   bool        theEndOfPeriod);

    //Adds a number to a PM value.
    //##ModelId=3E6E4CC203B1
    virtual CT_PM_64BitValue AddValue(
                                 PM_BbValue&        theValue, 
                                 CT_PM_Parameter    theParam, 
                                 CT_PM_64BitValue   theNumber, 
                                 CT_PM_64BitValue   theMaxValue, 
                                 bool               theUaState, 
                                 bool               thePotential2ChgState, 
                                 bool               theEndOfPeriod);

protected:

    //Verifies if threshold has to be reset due to a 
    //threshold configuration changing.
    //##ModelId=3E6E4CC203E3
    virtual bool CheckThresholdChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

    //Verifies if threshold and values has to be reset due to 
    //a reset request.
    //##ModelId=3E6E4CC3006A
    virtual bool CheckResetReqChange(PM_BbCfg& theConfig, PM_BbValue& theCurrentValue);

    virtual CT_PM_64BitValue GetMaxValueTable64Bit(CT_PM_Parameter theParameter);
    virtual CT_EntityType    GetEntityTypeFor64BitPM();

    bool myUaDeclared;
    bool myPotentialStateChange;

private:

    CT_PM_64BitValue GetMaxValueTable(CT_PM_Parameter theParameter);
};

#endif //PM_ACCUMULATIONPERIODCOUNTER_H
