/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 4, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to accumulate Rmon Counter parameters for one accumulation
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_TypeRmon.h>
#include <EPM/src/PM_RulesRmonCounter.h>
#include <EPM/src/PM_AccPeriodRmonCounter.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodRmonCounter::PM_AccumulationPeriodRmonCounter( PM_GenericApplication &theGenericApplication,
                                                      CT_PM_64BitValue*     theMaxValueTable,
                                                      PM_Rules&             theRules,
                                                      uint32                thePortNumber,
                                                      CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits(),
                                  thePortNumber,
                                  thePeriod),
    // RMON layer stuff.
    myDisableAutoRateInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodRmonCounter::~PM_AccumulationPeriodRmonCounter()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodRmonCounter::UpdatePeriod(bool* theValidityState,
                                             bool* theFilteringStateFirstStage,
                                             bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Apply Auto-Rate Lock adjustments to current value data.
    SetSomeTcaChangedState( AdjustForAutoRateLock() );

    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, theValidityState,
                                                  theFilteringStateFirstStage,
                                                  theFilteringStateSecondStage,
                                                  false) );
    }

    return GetSomeTcaChangedState();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodRmonCounter::UpdateEndPeriod()
{
    bool    validityState[PM_MAX_NUMBER_OF_PARAMETERS];             // Computed validity state.
    bool    filteringStateFirstStage[PM_MAX_NUMBER_OF_PARAMETERS];  // Computed filtering state first stage.
    bool    filteringStateSecondStage[PM_MAX_NUMBER_OF_PARAMETERS]; // Computed filtering state second stage.
    uint32  param;                                                  // Parameter index.


    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Set validity state to valid and filtering state to no filtering.
    for (param = 0; param < myNumberOfParam; param++)
    {
        filteringStateFirstStage[param] = false;
        filteringStateSecondStage[param] = false;
        validityState[param] = true;
    }

    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, validityState,
                                                  filteringStateFirstStage,
                                                  filteringStateSecondStage,
                                                  true) );
    }

    return GetSomeTcaChangedState();

}

//------------------------------------------------------------------
bool PM_AccumulationPeriodRmonCounter::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Get pointer to Auto-Rate Lock inhibit profile
        PM_RulesRmonCounter& rulesRef = dynamic_cast<PM_RulesRmonCounter&>(GetRules());
        bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

        // Validate pointer to see if this facility is configured for
        // Auto-Rate Lock
        if( aAutoRateInhibitProfile == NULL )
        {
            // This is a fixed rate facility.
            for (param = 0; param < myNumberOfParam; param++)
            {
                theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
            }
        }
        else
        {
            // This is an Auto-Rate Lock facility

            // Within a period, any change in inhibition sets the
            // invalid flag.
            theValue.GetIdf()->ForcedSetAllIdf( true );

            if( myDisableAutoRateInhibit && !(GetCurrentAllInhibit()) )
            {
                // This is the first time PM collection has been enabled
                // during this period.
                 myDisableAutoRateInhibit = false;
            }

            if( !myDisableAutoRateInhibit )
            {
                for (param = 0; param < myNumberOfParam; param++)
                {

                    theValue.GetIdf()->ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                    aAutoRateInhibitProfile++;
                }
            }
        }
        isRegionChanged = true;
    }

    // Verify TCA inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL) != GetCurrentAllTcaInhibit() )
    {
        SetCurrentAllTcaInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL));
        isRegionChanged = true;
    }

    return isRegionChanged;

}

bool PM_AccumulationPeriodRmonCounter::AdjustForAutoRateLock()
{
    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesRmonCounter& rulesRef = dynamic_cast<PM_RulesRmonCounter&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();
    bool retVal = false;

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( (aAutoRateInhibitProfile != NULL) && (!myDisableAutoRateInhibit) )
    {
        // Determine if an Auto-Rate Lock update has occured.
        if( rulesRef.IsAutoRateStateRefreshed() )
        {
            // An Auto-Rate update has occured.
            // Reset all of the current data.
            ResetAll();

            // Get a reference to the IDF object.
            PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

            // Adjust the IDF inhibit states per the Auto-Rate
            // inhibit profile.
            for (uint32 param=0; param<myNumberOfParam; param++)
            {
                idf.ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                aAutoRateInhibitProfile++;
            }

            retVal = true;
        }
    }
    return retVal;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodRmonCounter::AdjustCurrentIdf()
{
    uint32 param;

    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesRmonCounter& rulesRef = dynamic_cast<PM_RulesRmonCounter&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( aAutoRateInhibitProfile != NULL )
    {
        // Set initial rules for applying Auto-Rate Lock inhibit.
        myDisableAutoRateInhibit =  GetCurrentAllInhibit();

        // Adjust the IDF inhibit states per the Auto-Rate
        // inhibit profile combined with the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, (*aAutoRateInhibitProfile | myDisableAutoRateInhibit) );
            aAutoRateInhibitProfile++;
        }
    }
    else
    {
        // Set the IDF inhibit states based on the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
        }
    }
}
 
//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodRmonCounter::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    bool isHgtmms64BitPort = false;
    if((CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMMS) &&
        (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_2 || myGenericApplication.GetSide() == CT_PM_PORT_SIDE_6))
    {
         isHgtmms64BitPort = true;
    }

    if ( (((CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTM)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_FGTME)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OSM2C)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS)) &&
         ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_0) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_1)))  || isHgtmms64BitPort)
    {
        switch ( theParameter )
        {
            case PM_TypeRmonCounter::PM_DROP:  return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_DROP_HIGH];
            case PM_TypeRmonCounter::PM_PKT:   return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_PKT_HIGH];
            case PM_TypeRmonCounter::PM_BCPKT: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_BCPKT_HIGH];
            case PM_TypeRmonCounter::PM_MCPKT: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_MCPKT_HIGH];
            case PM_TypeRmonCounter::PM_CRCAE: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_CRCAE_HIGH];
            case PM_TypeRmonCounter::PM_USPKT: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_USPKT_HIGH];
            case PM_TypeRmonCounter::PM_OSPKT: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_OSPKT_HIGH];
            case PM_TypeRmonCounter::PM_FRAG: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_FRAG_HIGH];
            case PM_TypeRmonCounter::PM_JABR: return myMaxValueTable64Bit[PM_TypeRmonCounter::PM_JABR_HIGH];

        }
    }
 
    return myMaxValueTable64Bit[theParameter];
}
 
//-----------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodRmonCounter::GetEntityTypeFor64BitPM()
{
    CT_EntityType a64BitEntityType = CT_UNKNOWN_ENTITY_TYPE;
 
    if ( ((CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTM)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OSM2C)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS))&&
         ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_0) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_1)) )
    {
        a64BitEntityType = CT_HGE;
    }
    else if ( (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_FGTME) &&
         ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_0) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_1)) )
    {
        a64BitEntityType = CT_FGE;
    }
    else if ( (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMMS) &&
              (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_6) )
    {
        a64BitEntityType = CT_FGE;
    }
    else if ( (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMMS) &&
              (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_2) )
    {
        a64BitEntityType = CT_HGE;
    }
 
    return a64BitEntityType;
}

