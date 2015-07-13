/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SMTM card
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class defines the failure type of DCC Link layer.
--------------------------------------------------------------------------*/

#ifndef ALM_DCCLFAILUREBASE_H
#define ALM_DCCLFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"
#include "Alarm/src/ALM_DefectStatusDefinition.h"
#include "Alarm/ALM_FPCommon.h"

//This class defines the failure type enumeration and the failure condition textual serialization
class ALM_DcclFailureBase : public ALM_FailureBase
{
public:

    //Constructor for this class.
    //
    //PARAM int theIndex: the index of the object within the region.
    //
    //PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    ALM_DcclFailureBase (int theIndex, bool theDefaultStatus = false );

    //Destructor for this class.
    virtual ~ALM_DcclFailureBase();

    /**
     * Retrieve the occurring time of a failure using the signal alarm common type.
     *
     * RETURN : the signal type CT_TEL_SignalType.
     */
    int GetSignalType() const;

	/**
     * Set the signal type currently associated with the port
	 * 
	 * PARAM CT_TEL_SignalType (int) the signal type.
     */
    void SetSignalType(int signalType);

    //Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex(int theIndex) const;

    //This method prints the alarm header.
    virtual void PrintHeader() const;

    // Failure type enumeration of OPT (Optical) layer.
    enum ALM_FailureType
    {
        // Dcc Link Down
        DCC_LINK_DOWN = 0,

        DCC_LINK_INCMPLT,

        // Upper None Service Affecting
        UPPER_NSA_DCC,

        // Upper Service Affecting
        UPPER_SA_DCC,

        //NUMBER OF FAILURES FOR THAT LAYER.
        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

    int itsSignalType;

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

    /**
     * Textual serialization used for BB edition. Writes the internal state of
     * the object to a stream.
     *
     * PARAM ostream& theStream: the output stream to write to.
     *
     * RETURN ostream&: an ostream reference that enables multiple insertion operators
     * on a single line.
     */
    virtual ostream& WriteObject(ostream& theStream);

    /**
     * Reads object data from the stream and set the object with it.
     *
     * PARAM istream& theStream: the stream to read from.
     *
     * RETURN istream&: an istream reference that enables multiple extraction operators
     * on a single line.
     */
    virtual istream& ReadObject(istream& theStream);

};

#endif //ALM_DCCLFAILUREBASE_H
