/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     12 December, 2001 Sebastien Cossette.
 DESCRIPTION:   Update and keep the PM status of Optical parameters.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbStatusRmon.h>


//-----------------------------------------------------------------
PM_BbStatusRmon::PM_BbStatusRmon ():
	PM_BbStatus(PM_TypeRmonGauge::PM_PARAM_NUM),
	myPreviousBitRate(0),
    myUtilTrace(false),
    mySide(CT_PM_UNKNOWN_SIDE)

{
	// Create utilization object with a bit rate of 0 for now.
	// This will get set later once the facility rate is determined.
    myUtilizationPtr = new CT_SNMP_Utilization( myPreviousBitRate );
}

//-----------------------------------------------------------------
PM_BbStatusRmon::~PM_BbStatusRmon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbStatusRmon::Update( MON_RmonCounters &theCounter, CT_TEL_daHz theBitRate )
{
	// Check to see if the bit rate has changed from the previous sampling period.
	if( theBitRate == myPreviousBitRate )
	{
		// The bit rate has not changed. Check to see if it is not 0.
		if( theBitRate != 0 )
		{
			// Get the packet and octet counts
			uint32 packets = 0;
			theCounter.GetErrorCount(CT_TEL_RMON_PKTS, &packets);
			uint32 octets = 0;
			theCounter.GetErrorCount(CT_TEL_RMON_OCTETS, &octets);

			// Get the high packet and octet counts
			uint32 packetsHigh = 0;
			theCounter.GetErrorCount(CT_TEL_RMON_HIGH_PKTS, &packetsHigh);
			uint32 octetsHigh = 0;
			theCounter.GetErrorCount(CT_TEL_RMON_HIGH_OCTETS, &octetsHigh);

            // Calculate 64bit value
            CT_PM_64bit_ull packets64bit = 0;
            CT_PM_64bit_ull octets64bit = 0;
            packets64bit = ( packetsHigh * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + packets;
            octets64bit  = ( octetsHigh  * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + octets;

			// Update the utilization calculation for this sampling interval
			myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue = GetUtilizationRef().Update( packets64bit, octets64bit, myUtilTrace );

            if( myUtilTrace && ((packets64bit == 0) || (octets64bit == 0)) )
            {
                fc_cout << "PM_BbStatusRmon::Update() " << DISPLAY_CT_PM_Side(mySide) 
                        << " pkts=" << packets << " octets=" << octets << endl;
                fc_cout << "PM_BbStatusRmon::Update() " << DISPLAY_CT_PM_Side(mySide) 
                        << " pktsHI=" << packetsHigh << " octetsHI=" << octetsHigh << endl;
            }
		}
	}
	else
	{
		// The bit rate has changed.
		// Reset the utilization object with the new bit rate.
		GetUtilizationRef().SetBitRate( theBitRate );

		// Update bit rate history.
		myPreviousBitRate = theBitRate;

		// Force utilization to 0 until the facility stabilizes.
		myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue = 0;
	}
}

//-----------------------------------------------------------------
void PM_BbStatusRmon::EndOfPeriod()
{
	// Reset local value for utilization
	myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue = 0;

	// Reset the utilization object.
	GetUtilizationRef().EndOfPeriod();
}

//-----------------------------------------------------------------
uint32 PM_BbStatusRmon::GetLastUtilization()
{
	// Return the last utilization value.
	return GetUtilizationRef().GetLastUtilizationAverage();
}

//-----------------------------------------------------------------
ostream& PM_BbStatusRmon::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue);
}

//-----------------------------------------------------------------
istream& PM_BbStatusRmon::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myParam[PM_TypeRmonGauge::PM_UTIL].UnsignedValue);
}

//-----------------------------------------------------------------
void PM_BbStatusRmon::Init(restart_type theRestart)
{
    PM_BbStatus::Init(theRestart);
}

//-----------------------------------------------------------------
void PM_BbStatusRmon::SetUtilTrace( bool theState, CT_PM_Side theSide )
{
    myUtilTrace = theState;
    mySide = theSide;
}
