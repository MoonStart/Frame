/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SPM
 AUTHOR   :     May 4, 2006  Larry Wolfrum
 DESCRIPTION:   Class defining the state of PM data collection
				files.
--------------------------------------------------------------------------*/

#ifndef PM_BBFILEPERIODSTATUS_H
#define PM_BBFILEPERIODSTATUS_H

#include <TimeService/FC_Time.h>
#include <PM/PM_BbObject.h>

class PM_BbFilePeriodStatus : public PM_BbObject
{
public:

    // Class default constructor.
    PM_BbFilePeriodStatus(uint32 dummy = 0, uint32 dummy1 = 0);
    
    // Class default destructor.
    virtual ~PM_BbFilePeriodStatus();

	// Reset() method must be defined to satisfy
	// the pure virtual function defined in the base
	// class.
	virtual void Reset();

	// Method to retieve the timestamp of the
	// latest control period for which data 
	// collection is complete.
	FC_Time& GetTimestamp();

	// Method to set the timestamp of the 
	// latest valid control period.
	void SetTimestamp( FC_Time& theTimestamp );

protected:

    // Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    // Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	// Timestamp of the latest control period for which
	// PM data collection is complete.
	FC_Time myTimestamp;
};

#endif //PM_BBFILEPERIODSTATUS_H

