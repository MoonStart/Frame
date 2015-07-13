/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 5, 2006, Larry Wolfrum.
 DESCRIPTION:   Base class to manage AutoRate Lock processing.
--------------------------------------------------------------------------*/

#include <EPM/src/PM_AutoRateLock.h>
#include <T6100/T6100_TelecomIf.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_OptAutoRateLock.h>
#include <Monitoring/MON_AppIf.h>

//-----------------------------------------------------------------
PM_AutoRateLock::PM_AutoRateLock()
{
    ResetAutoRateLockStates();
}

//-----------------------------------------------------------------
PM_AutoRateLock::~PM_AutoRateLock()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_AutoRateLock::ResetAutoRateLockStates()
{
    myLastLockedAutoBitRate = 0;
    myAutoRateLockRefresh = false;
    myAutoRateLockProfile = NULL;
}

//-----------------------------------------------------------------
bool* PM_AutoRateLock::GetAutoRateInhibitProfile()
{
    return  myAutoRateLockProfile;
}

//-----------------------------------------------------------------
bool PM_AutoRateLock::IsAutoRateStateRefreshed()
{
    return  myAutoRateLockRefresh;
}

//-----------------------------------------------------------------
void PM_AutoRateLock::AdjustForAutoRateLock( T6100_CardIf& theCardContext,
                                             uint32 theNumberOfParam,
                                             CT_PM_64BitValue* theCurrentValueParam,
                                             bool* theFilteringStateFirstStage,
                                             bool* theFilteringStateSecondStage,
                                             CT_PM_Side thePMSide )
{
    CT_TEL_daHz currentAutoBitRate = 0;
    MON_OptStatus* aMonOptStatus = NULL;
    bool currentRateNotFound = true;

    if ( theCardContext.GetCardFamily() == TRN_FAM ) // MRTME
    {
        if ( (aMonOptStatus = GetMonOptStatusRegion( theCardContext )) != NULL )
        {
            currentAutoBitRate = aMonOptStatus->GetDetectedClockRate();
            currentRateNotFound = false;
        }
    }

    //-----------------------------------
    // Check for errors.
    //-----------------------------------
    if ( currentRateNotFound )
    {
        FC_REPORT_ERROR( FC_RuntimeError, "AdjustForAutoRateLock(): current rate not found" );
        ResetAutoRateLockStates();
        return;
    }

    //--------------------------------------------------------------------
    // Set the flag indicating a need to reset the current values.
    // This is done if the facility has locked to a new rate or if
    // it has no history of locking yet.
    //--------------------------------------------------------------------
    if ( (currentAutoBitRate == myLastLockedAutoBitRate) ||
         ((currentAutoBitRate == 0) && (myLastLockedAutoBitRate != 0)) )
    {
        myAutoRateLockRefresh = false;
    }
    else
    {
        myAutoRateLockRefresh = true;
    }

    // Check to see if the facility is locked
    if( currentAutoBitRate != 0 )
    {
        // Update/reaffirm the last locked bit rate with the current rate
        myLastLockedAutoBitRate = currentAutoBitRate;
    }

    // Get the Auto-Rate Lock inhibit profile.
    myAutoRateLockProfile = MapAutoRateToProfile( myLastLockedAutoBitRate );
    bool* inhibitProfile = myAutoRateLockProfile;

    // Adjust the TCA filtering states and current values based on the
    // Auto-Rate lock profile.
    for (uint32 param = 0; param < theNumberOfParam; param++)
    {
        if( *inhibitProfile )
        {
            theFilteringStateFirstStage[param] = true;
            theFilteringStateSecondStage[param] = true;
            theCurrentValueParam[param].UnsignedValue = 0;
        }
        inhibitProfile++;
    }
}

//-----------------------------------------------------------------
CFG_Opt* PM_AutoRateLock::GetCfgOptRegion( T6100_CardIf& theCardContext, CT_PM_Side theSide )
{
    CFG_Opt* aCfgOpt = NULL;
    CFG_AppIf* aCfgApp = NULL;

    //conversion formula to CT_PORT_SIDE_x
    CT_IntfId aIntfId;

    if(( theSide >= CT_PM_PORT_SIDE_0 ) || ( theSide <= CT_PM_PORT_SIDE_31 ))
    {
            aIntfId = (CT_IntfId)(theSide - CT_PM_PORT_SIDE_0 + CT_PORT_SIDE_0);
            aCfgApp = theCardContext.GetOptIf().GetCfgPortSideAppPtr(aIntfId);
    }
    else if(( theSide >= CT_PM_PORT_SIDE_85 ) || ( theSide <= CT_PM_PORT_SIDE_88 ))
    {
            aIntfId = (CT_IntfId)(theSide - CT_PM_PORT_SIDE_85 + CT_PORT_SIDE_85);
            aCfgApp = theCardContext.GetOptIf().GetCfgPortSideAppPtr(aIntfId);
    }
    else if( theSide == CT_PM_LINE_SIDE_0 )
    {
        aCfgApp = theCardContext.GetOptIf().GetCfgLineSideAppPtr(CT_LINE_SIDE_0);
    }

    if( aCfgApp == NULL )
    {
        return NULL;
    }

     aCfgOpt = (CFG_Opt *) &((*(aCfgApp->GetCfgRegion()))[0]);

    return  aCfgOpt;
}

//-----------------------------------------------------------------
MON_OptStatus* PM_AutoRateLock::GetMonOptStatusRegion( T6100_CardIf& theCardContext )
{
    MON_OptStatus* aMonOptStatus = NULL;
    MON_AppIf* aMonApp = NULL;

    aMonApp = theCardContext.GetOptIf().GetMonPortSideAppPtr(CT_PORT_SIDE_0);

    if( aMonApp == NULL )
    {
        return NULL;
    }

    aMonOptStatus = (MON_OptStatus *) &((*(aMonApp->GetStatusRegion()))[0]);

    return  aMonOptStatus;
}

//-----------------------------------------------------------------
MON_MacStatus* PM_AutoRateLock::GetMonMacStatusRegion( T6100_CardIf& theCardContext, CT_PM_Side thePMSide )
{
    MON_MacStatus* aMonMacStatus = NULL;
    MON_AppIf* aMonApp = NULL;

    CT_IntfId aIntfId = (CT_IntfId)(thePMSide - CT_PM_PORT_SIDE_0 + CT_PORT_SIDE_0);

    aMonApp = theCardContext.GetMacIf().GetMonPortSideAppPtr(aIntfId);

    if( aMonApp == NULL )
    {
        return NULL;
    }

    aMonMacStatus = (MON_MacStatus *) &((*(aMonApp->GetStatusRegion()))[0]);

    return  aMonMacStatus;
}

//-----------------------------------------------------------------
CT_TEL_SignalType PM_AutoRateLock::GetAutoRateLockSignalType(T6100_CardIf& theCardContext, CT_TEL_SignalType origSignalType)
{
    // Return what is passed in (just in case nothing is found)
    CT_TEL_SignalType retSignalType = origSignalType;

    MON_OptStatus* aMonOptStatus;

    if( (aMonOptStatus = GetMonOptStatusRegion( theCardContext )) != NULL )
    {
        CT_TEL_daHz currentAutoBitRate = aMonOptStatus->GetDetectedClockRate();

        if( currentAutoBitRate != 0 )
        {
            // Return the Signal Type
            retSignalType = CT_TelecomUtilities::ConvertSignalRateToSignalType( currentAutoBitRate );
        }
    }

    return retSignalType;
}

//-----------------------------------------------------------------
CT_IntfId PM_AutoRateLock::ConvertPmSideToCtIfId( const CT_PM_Side theSide )
{
    CT_IntfId aSide;

    if( (theSide >= CT_PM_PORT_SIDE_0) && (theSide <= CT_PM_PORT_SIDE_31) )
    {
        aSide = (CT_IntfId)(theSide - CT_PM_PORT_SIDE_0 + CT_PORT_SIDE_0);
    }
    else if( (theSide >= CT_PM_PORT_SIDE_85) && (theSide <= CT_PM_PORT_SIDE_88) )
    {
        aSide = (CT_IntfId)(theSide - CT_PM_PORT_SIDE_85 + CT_PORT_SIDE_85);
    }
    else if( (theSide >= CT_PM_LINE_SIDE_0) && (theSide <= CT_PM_LINE_SIDE_9) )
    {
        aSide = (CT_IntfId)(theSide - CT_PM_LINE_SIDE_0 + CT_PORT_SIDE_0);
    }
    else
    {
        aSide = CT_INTF_ID_UNKNOWN;
    }

    return aSide;
}
