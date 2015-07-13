/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     December 20, 2005 Larry Wolfrum.
 DESCRIPTION:   Update and keep the PM status RMON Ethernet statistics.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSRMON_H
#define PM_BBSTATUSRMON_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_BbStatus.h>
#include <EPM/PM_TypeRmon.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_RmonCounters.h>
#include <CommonTypes/CT_SNMP_Utilization.h>

// Forward declaration of classes
//class MON_OptStatus;

using namespace std;

//This class keeps and updates the Status related to Optical 
//parameters.
class PM_BbStatusRmon:    public PM_BbStatus
{
public:

    //Class default constructor.
    PM_BbStatusRmon ();

    //Class default destructor.
    virtual ~PM_BbStatusRmon();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Updates PM statuses of RMON
    //Ethernet statistics.
    void Update( MON_RmonCounters &theCounter, CT_TEL_daHz theBitRate );

    //Returns the Ethernet utilization.
    uint32 GetUtilization() const;

    //Returns reference to utilization calculation object.
    CT_SNMP_Utilization& GetUtilizationRef();

    //Causes utilization object to reset history state at end of 
    //averaging period
    void EndOfPeriod();

    // Set utilization trace mode.
    void SetUtilTrace( bool theState, CT_PM_Side theSide );

    // Get the last utilization value.
    uint32 GetLastUtilization();
	
protected:
    
    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    // Pointer to utilization calculation object.
    CT_SNMP_Utilization* myUtilizationPtr;

    // Bit rate of last sampling period.
    CT_TEL_daHz	myPreviousBitRate;

    // Flag to determine if a trace message should be output
    // if zero packets or octets were collected in the last
    // interval.
    bool myUtilTrace;

    // Side of containing subapp.
    CT_PM_Side mySide;
};

//-----------------------------------------------------------------
inline uint32 PM_BbStatusRmon::GetUtilization() const
{
    return myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue;
}

inline CT_SNMP_Utilization& PM_BbStatusRmon::GetUtilizationRef()
{
	return *myUtilizationPtr;
}

#endif //PM_BBSTATUSRMON_H

