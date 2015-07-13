/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 DESCRIPTION:   Class for Tcm gauge parameters for an accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODTcmGAUGE_H
#define PM_ACCUMULATIONPERIODTcmGAUGE_H

#include <PM/src/PM_AccPeriodGauge.h>

class PM_AccumulationPeriodTcmGauge : public PM_AccumulationPeriodGauge
{
public:

    //Class default constructor.
    PM_AccumulationPeriodTcmGauge(PM_GenericApplication &theGenericApplication,
                              CT_PM_Value*          theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodTcmGauge();

    //This method verifies if each entity inhibition is 
    //enabled or not. If not it calls update period of each entity.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    virtual bool UpdateEndPeriod();

    //Sets all modification actions on region changing and 
    //setup the attributes according to the actual 
    //configuration of the control region.
    virtual void Init(uint16 thePortNumber);

    //Resets all PM values to zero, TCA statues are reset,
    //IDF are set to invalid.
    virtual void ResetAll();

    //Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    virtual void AdjustCurrentIdf();

    //Set the availability when monitoring 
    //status is invalid or valid of specifier parameter.
    virtual void SetAvailability(CT_PM_Parameter theParameter, bool theAvailability);

protected:

    //Verifies if there is a pending threshold configuration.
    virtual bool VerifyConfigChange();

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig);

private:

    // Index to associated dynamically allocated object.
    uint16 myDynamicIndex;
};

#endif //PM_ACCUMULATIONPERIODTcmGAUGE_H
