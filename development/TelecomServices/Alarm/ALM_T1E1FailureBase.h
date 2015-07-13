/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the T1E1 failure types.
--------------------------------------------------------------------------*/

#ifndef  ALM_T1E1FAILUREBASE_H
#define  ALM_T1E1FAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


// This class defines the failure type enumerations and the failure condition textual
// serialization of T1E1.
class ALM_T1E1FailureBase : public ALM_FailureBase
{

public:

    // Constructor for this class.
    //
    // PARAM int theIndex: the index of the object within the region.
    //
    // PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    ALM_T1E1FailureBase (int theIndex, bool theDefaultStatus = false );

    // Destructor for this class.
    virtual ~ALM_T1E1FailureBase();

    // Get the zero based failure index from the signal alarm common type.
    //
    // PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the
	//      failure type defined in the common type.
    //
    // RETURN int: the zero based failure index.
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    // Get a signal alarm common type from a zero based failure index.
    //
    // PARAM int theIndex: the zero based failure index.
    //
    // RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type
	//       defined in the common type.
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

    // This method prints the alarm header.
    virtual void PrintHeader() const;

    // Failure type enumerations for the T1E1 input.
    enum ALM_FailureType
    {
        // Frequency Offset on NANO
        FREQOFF_T1E1 = 0,

		// Loss Of Frame on the T1E1 input.
        // SRS 7100000250 requirement 895
        LOF_T1E1,

		// AIS on the T1E1 input.
        // SRS 7100000250 requirement 895
        AIS_T1E1,

        // Loss Of Signal on the T1E1 input.
        // SRS 7100000250 requirement 895
        LOS_T1E1,

        // NUMBER OF FAILURES FOR THAT LAYER.
        // This identifier is the same for every enum ALM_FailureType defined
		// into the other FailureBase class definitions.
        ALM_INVALID_FAILURE,
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

    // Textual serialization used for the BB edition. Writes the internal state
	// of the object to a stream.
    //
    // PARAM ostream& theStream: the output stream to write to.
    //
    // RETURN ostream&: an ostream reference that enables multiple insertion
	//        operators on a single line.
    virtual ostream& WriteObject(ostream& theStream);

    // Reads object data from the stream and set the object with it.
    //
    // PARAM istream& theStream: the stream to read from.
    //
    // RETURN istream&: an istream reference that enables multiple extraction
	//        operators on a single line.
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_T1E1FAILUREBASE_H
