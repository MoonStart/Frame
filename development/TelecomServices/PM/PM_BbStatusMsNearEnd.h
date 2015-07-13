/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     5 May 2004  Hemant Thakkar
 DESCRIPTION:   Update and keep the protection switching statistics of 
                Near-End SONET/SDH MS layer
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSMSNEAREND_H
#define PM_BBSTATUSMSNEAREND_H

#include <EPM/src/PM_CounterLimit.h>

//Forward declaration.
class SP_SwitchingStatistic;

using namespace std;

//Keeps various Near-End SONET/SDH MS switching statistics up to 
//date for the current second. Note that unlike the PM_BbStatus classes
//of other layers such as OPT, the MsNearEnd does not derive from the base
//class PM_BbStatus. The purpose of PM_BbStatus and the status classes, in
//general, has been to hold status of guage type parameters. In MsNearEnd
//case, however, the status information is primarily for singal protection
//status information. 
class PM_BbStatusMsNearEnd : public FC_BbObject
{
public:

    //Class default constructor.
    PM_BbStatusMsNearEnd();

    //Class default destructor.
    virtual ~PM_BbStatusMsNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of PSC counts from the 
    inline uint32 GetPSC() const;

    //Returns the current count of seconds accumulated 
    //where each second is the second during which the MS-NearEnd
    //facility was selected for traffic by Signal Protection.
    inline uint32 GetPSD() const;

    //Returns the status of a change in revertive mode of
    //signal protection mode.
    inline bool EverPresentRevertiveMode();

    //Was the facility ever removed from a protection scheme.
    inline bool EverRemovedFromProtectionScheme();

    //Was the facility ever present in a protection scheme.
    inline bool EverPresentInProtectionScheme();

	// Was the state of the protection scheme changed?
	inline bool EverChangedProtectionScheme();

	// Was the revertive mode changed?
	inline bool EverChangedRevertiveMode();

    //Updates the PM counters.
    void Update(SP_SwitchingStatistic* theMsStatuser);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM counter that memorizes the number of PSC for this second.
    PM_CounterLimit myPSCCounter;

    //The PM counter that memorizes the number of seconds. Since the
    //collector executes every second, the PSD counter should always 
    //be 1 or 0 depending on whether the facility represented by this
    //MSNearEnd application is currently carrying traffic.
    PM_CounterLimit myPSDCounter;

    //The number of seconds the SONET/SDH facility has been protecting
    //since the facility was added to the current protection scheme.
    uint32 myProtectionActiveDuration;

    //Last recorded revertive mode. TRUE if revertive mode is active
    bool myLastRevertiveMode;

    //Current revertive mode.  TRUE if revertive mode is active
    bool myCurrentRevertiveMode;

    // Last recorded state of presence in a protection scheme
    bool myLastProtectionShemePrsenceStatus;

    //Current state of presence in a protection scheme
    bool myCurrentProtectionShemePrsenceStatus;
};

//-----------------------------------------------------------------
inline uint32 PM_BbStatusMsNearEnd::GetPSC() const
{
    return myPSCCounter.GetCount();
}

//-----------------------------------------------------------------
inline uint32 PM_BbStatusMsNearEnd::GetPSD() const
{
    return myPSDCounter.GetCount();
}

//-----------------------------------------------------------------
inline bool PM_BbStatusMsNearEnd::EverPresentRevertiveMode()
{
	return  myCurrentRevertiveMode;
}

//-----------------------------------------------------------------
inline bool PM_BbStatusMsNearEnd::EverRemovedFromProtectionScheme()
{
    if ((!myCurrentProtectionShemePrsenceStatus) &&
        (myLastProtectionShemePrsenceStatus != myCurrentProtectionShemePrsenceStatus))
        return true;
    else
        return false;
}

//-----------------------------------------------------------------
inline bool PM_BbStatusMsNearEnd::EverPresentInProtectionScheme()
{
    return myCurrentProtectionShemePrsenceStatus;
}

//-----------------------------------------------------------------
inline bool PM_BbStatusMsNearEnd::EverChangedProtectionScheme()
{
    if ( myLastProtectionShemePrsenceStatus != myCurrentProtectionShemePrsenceStatus )
        return true;
    else
        return false;
}

//-----------------------------------------------------------------
inline bool PM_BbStatusMsNearEnd::EverChangedRevertiveMode()
{
    if ( myLastRevertiveMode != myCurrentRevertiveMode )
        return true;
    else
        return false;
}

#endif //PM_BBSTATUSMSNEAREND_H
