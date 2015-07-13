/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the HOP (High Order Path) layer failure
                types.
--------------------------------------------------------------------------*/

#ifndef  ALM_HOPFAILUREBASE_H
#define  ALM_HOPFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


// This class defines the failure type enumerations and the failure condition textual
// serialization of the HOP (High Order Path) layer.
class ALM_HopFailureBase : public ALM_FailureBase
{

public:

    // Constructor for this class.
    //
    // PARAM int theIndex: the index of the object within the region.
    //
    // PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    ALM_HopFailureBase (int theIndex, bool theDefaultStatus = false );

    // Destructor for this class.
    virtual ~ALM_HopFailureBase();

    // Get the zero based failure index from the signal alarm common type.
    //
    // PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type
	//      defined in the common type.
    //
    // RETURN int: the zero based failure index.
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    // Get a signal alarm common type from a zero based failure index.
    //
    // PARAM int theIndex: the zero based failure index.
    //
    // RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the
	//       common type.
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

    // Get the zero based failure index from the signal protect common type.
    //
    // PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type
	//      defined in the common type.
    //
    // RETURN int: the zero based failure index.
    virtual int GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    // Get a signal protect common type from a zero based failure index.
    //
    // PARAM int theIndex: the zero based failure index.
    //
    // RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the
	//       common type.
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetSigProtTypeFromIndex( int theIndex) const;

    // This method prints the alarm header.
    virtual void PrintHeader() const;

    // Failure type enumerations for the HOP (High Order Path) layer.
    enum ALM_FailureType
    {
        // Signal Degrade Bit-Error-Rate HOP failure.
        // SrS 7100000715 requirement 1004, 1005
        SDBER_HOP = 0,

        // Signal Fail Bit-Error-Rate HOP failure.
        // SrS 7100000715 requirement 997, 998
        SFBER_HOP,

        // Remote Failure Indication HOP failure.
        // SrS 7100000715 requirement 928, 929
        RDI_HOP,

        // Payload Label Mismatch HOP failure.
        // SrS 7100000715 requirement 928, 929
        PLM_HOP,

        // STS Path Unequipped HOP failure.
        // SrS 7100000715 requirement 920, 921
        UNEQ_HOP,

        // Loss Of Pointer HOP failure.
        // SrS 7100000715 requirement 903, 904
        LOP_HOP,

        // Alarm Indication Signal HOP failure.
        // SrS 7100000715 requirement 911, 912
        AIS_HOP,

        // Upper None Service Affecting HOP.
        UPPER_NSA_HOP,

        // Upper Service Affecting HOP.
        UPPER_SA_HOP,

        // NUMBER OF FAILURES FOR THAT LAYER.
        // This identifier is the same for every enum ALM_FailureType defined into the other
		// FailureBase class definitions.
        ALM_INVALID_FAILURE,
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    // Signal Protect defect indications enumerations for the HOP (High Order Path) layer.
    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        SP_STREAM_ALM_NR,

        SP_ALM_W_MATE_ID,

        SP_PROTNA,

        ALM_SP_INVALID_DEFECT,

        ALM_SP_NB_OF_DEFECT = ALM_SP_INVALID_DEFECT
    };


protected:

    /**
     * Binary serialization used for BB transfer between cards. Writes the internal
     * data of the object to a stream.
	 *
	 * PARAM FC_Stream& theStream: the FC stream to write to.
	 *
	 * RETURN FC_Stream&: a FC_Stream reference that enables multiple insertion
     * operators on a single line.
     */
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

	/**
     * Reads object data from the stream and set the object with it.
	 *
	 * PARAM FC_Stream& theStream: the FC stream to read from.
	 *
	 * RETURN FC_Stream&: a FC_Stream reference that enables multiple extraction operators on a single line.
     */
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    // Textual serialization used for the BB edition. Writes the internal state of the object
	// to a stream.
    //
    // PARAM ostream& theStream: the output stream to write to.
    //
    // RETURN ostream&: an ostream reference that enables multiple insertion operators on a
	//        single line.
    virtual ostream& WriteObject(ostream& theStream);

    // Reads object data from the stream and set the object with it.
    //
    // PARAM istream& theStream: the stream to read from.
    //
    // RETURN istream&: an istream reference that enables multiple extraction operators on a
	//        single line.
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_HOPFAILUREBASE_H
