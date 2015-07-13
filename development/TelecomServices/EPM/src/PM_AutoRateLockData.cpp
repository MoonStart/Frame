/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 5, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage Data Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#include <EPM/src/PM_AutoRateLockData.h>
#include <CsPii/CSPII_CardIF.h>

// Table of Auto-Rate Lock Parameter Inhibit Profiles
bool PM_AutoRateLockData::AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeData::PM_PARAM_NUM-1] = 
{
    //  PM_AutoRateLockProfile_INHIBIT_ALL
    {
        true,    // LOSS
        true,    // CV
        true,    // SE
        true,    // SEFS
        true,    // SES
        true,    // ES
    },

    //  PM_AutoRateLockProfile_1
    {
        false,   // LOSS
        true,    // CV
        true,    // SE
        true,    // SEFS
        true,    // SES
        true,    // ES
    },

    //  PM_AutoRateLockProfile_2
    {
        false,   // LOSS
        true,    // CV
        false,   // SE
        true,    // SEFS
        true,    // SES
        true,    // ES
    },

    //  PM_AutoRateLockProfile_3
    {
        false,    // LOSS
        false,    // CV
        true,     // SE
        false,    // SEFS
        false,    // SES
        false,    // ES
    }
};

PM_AutoRateLockData::PM_AutoRateLockData()
{
    // Nothing to do for now.
}

PM_AutoRateLockData::~PM_AutoRateLockData()
{
    // Nothing to do for now.
}

bool* PM_AutoRateLockData::MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate )
{
    bool* profile;

    switch( theAutoBitRate )
    {
    case 0:
         profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
         break;

    case BIT_RATE_100BFX:
    case BIT_RATE_FC133:
    case BIT_RATE_ESCON:
    case BIT_RATE_FC266:
    case BIT_RATE_DVBASI:
    case BIT_RATE_FC531:
    case BIT_RATE_FICON:
    case BIT_RATE_GBE:
    case BIT_RATE_2GFC:
    case BIT_RATE_4GFC:
        profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_2][0];
        break;

    case BIT_RATE_OC3:
    case BIT_RATE_OC12:
    case BIT_RATE_OC48:
         if (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OTNM)
             profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_1][0];
         else
             profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_3][0];
         break;

    case BIT_RATE_DV6:
    default:

        profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_1][0];
        break;
    }

    return profile;
}
