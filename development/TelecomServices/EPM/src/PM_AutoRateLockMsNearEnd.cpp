/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     April 17, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage MS Near End Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#include <EPM/src/PM_AutoRateLockMsNearEnd.h>
#include <CsPii/CSPII_CardIF.h>

// Table of Auto-Rate Lock Parameter Inhibit Profiles.
bool PM_AutoRateLockMsNearEnd::AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeMsNearEnd::PM_PARAM_NUM] = 
{
    //  PM_AutoRateLockProfile_INHIBIT_ALL
    {
        true,    // CV
        true,    // SES
        true,    // ES
        true,    // UAS
        true,    // AISS
        true,    // FC
        true,    // PSC
        true    // PSD
    },

    //  PM_AutoRateLockProfile_1
    {
        false,    // CV
        false,    // SES
        false,    // ES
        false,    // UAS
        false,    // AISS
        false,    // FC
        false,    // PSC
        false     // PSD
    }
};

PM_AutoRateLockMsNearEnd::PM_AutoRateLockMsNearEnd()
{
    // Nothing to do for now.
}

PM_AutoRateLockMsNearEnd::~PM_AutoRateLockMsNearEnd()
{
    // Nothing to do for now.
}

bool* PM_AutoRateLockMsNearEnd::MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate )
{
    bool* profile;

    switch( theAutoBitRate )
    {
    case 0:
         profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
         break;

    case BIT_RATE_OC3:
    case BIT_RATE_OC12:
    case BIT_RATE_OC48:
         if (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OTNM)
             profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
         else
             profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_1][0];
         break;

    default:
         profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
         break;
    }

    return profile;
}

