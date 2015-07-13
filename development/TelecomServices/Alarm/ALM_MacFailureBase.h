/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM
 DESCRIPTION:   This class defines the failure type of Mac layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_MACFAILUREBASE_H
#define  ALM_MACFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"

class ALM_MacFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	//##ModelId=3C506C3801B3
    ALM_MacFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	//##ModelId=3C506C3801BD
    virtual ~ALM_MacFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
	//##ModelId=3C506C3801BF
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
	//##ModelId=3C506C3801C8
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

	//This method prints the alarm header.
	//##ModelId=3C506C3801D1
	virtual void PrintHeader() const;

    inline int  GetSignalType() const;
    inline void SetSignalType(int signalType);

    enum ALM_FailureType
    {
        RFLINKFAIL_MAC = 0,

        LACPFAIL_MAC,

        UPPER_NSA_MAC,
 
        UPPER_SA_MAC,

        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        ALM_SP_INVALID_DEFECT,

        ALM_SP_NB_OF_DEFECT = ALM_SP_INVALID_DEFECT
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

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.
	//##ModelId=3C506C3801DB
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
	//##ModelId=3C506C3801E5
    virtual istream& ReadObject(istream& theStream);
};

#endif // ALM_MACFAILUREBASE_H
