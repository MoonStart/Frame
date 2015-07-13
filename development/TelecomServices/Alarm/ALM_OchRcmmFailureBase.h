/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     RCMM
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the failure type of OCH (Optical 
                Channel) layer specific to the RCMM.
--------------------------------------------------------------------------*/

#ifndef  ALM_OCHRCMMFAILUREBASE_H
#define  ALM_OCHRCMMFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


// This class defines the failure type enumeration and the failure condition
// textual serialization of OCH (Optical Channel) layer specific to the RCMM.
class ALM_OchRcmmFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    ALM_OchRcmmFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
    virtual ~ALM_OchRcmmFailureBase();

    // Get the zero based failure index from the signal alarm common type.
    //
    // PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the
    // failure type defined in the common type.
    //
    // RETURN int: the zero based failure index.
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    // Get a signal alarm common type from a zero based failure index.
    //
    // PARAM int theIndex: the zero based failure index.
    //
    // RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type
    // defined in the common type.
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.
	virtual void PrintHeader() const;

	//Failure type enumeration of OCH (Optical Channel) layer.
    enum ALM_FailureType
    {
		//Diagnostique Tone Detected
		LOS_OCH,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

    // Textual serialization used for BB edition. Writes the internal state of
    // the object to a stream.
	//
	// PARAM ostream& theStream: the output stream to write to.
	//
	// RETURN ostream&: an ostream reference that enables multiple insertion
    // operators on a single line.
    virtual ostream& WriteObject(ostream& theStream);

	// Reads object data from the stream and set the object with it.
	//
	// PARAM istream& theStream: the stream to read from.
	//
	// RETURN istream&: an istream reference that enables multiple extraction
    // operators on a single line.
    virtual istream& ReadObject(istream& theStream);


};

#endif // ALM_OCHRCMMFAILUREBASE_H
