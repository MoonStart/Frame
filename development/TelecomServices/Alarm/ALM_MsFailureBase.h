/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class defines the failure type of MS (Regenerator
                Section) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_MSFAILUREBASE_H
#define  ALM_MSFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of MS (Regenerator Section) layer.
//##ModelId=3C506C36016A
class ALM_MsFailureBase : public ALM_FailureBase
{

public:

    //Constructor for this class.
    //
    //PARAM int theIndex: the index of the object within the region.
    //
    //PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    //##ModelId=3C506C3601E4
    ALM_MsFailureBase (int theIndex, bool theDefaultStatus = false );

    //Destructor for this class.
    //##ModelId=3C506C3601EF
    virtual ~ALM_MsFailureBase();

    /**
     * RETURN : the signal type CT_TEL_SignalType.
     */
    int GetSignalType() const;

    /**
     * PARAM CT_TEL_SignalType (int) the signal type.
     */
    void SetSignalType(int signalType);


    //Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
    //##ModelId=3C506C3601F7
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
    //##ModelId=3C506C3601FA
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
    //##ModelId=3C506C360203
    virtual void PrintHeader() const;

    //Failure type enumeration of MS (Regenerator Section) layer.
    //##ModelId=3C506C360229
    enum ALM_FailureType
    {
        //Signal degraded MS.
		//##ModelId=3F954C2F0189
        SDBER_MS = 0,

        //Signal failure MS.
		//##ModelId=3F954C2F018A
        SFBER_MS,

        //Remote defect indication MS.
		//##ModelId=3F954C2F0199
        RDI_MS,

        //Alarm indication signal MS.
		//##ModelId=3F954C2F019A
        AIS_MS,

        AIS_INT_MS,

        UPPER_INT_SA_MS,

        // Upper None Service Affecting MS.
		//##ModelId=3F954C2F019B
        UPPER_NSA_MS,

        // Upper Service Affecting MS.
		//##ModelId=3F954C2F01A8
        UPPER_SA_MS,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
        //##ModelId=3C506C360279
        ALM_INVALID_FAILURE,
        //##ModelId=3DBFFAEA0255
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    // Signal Protect defect indications enumerations for the MS (Regenerator Section) layer.
    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        SP_PROTNA,

        ALM_SP_INVALID_DEFECT,

        ALM_SP_NB_OF_DEFECT = ALM_SP_INVALID_DEFECT
    };


protected:

    int itsSignalType; // Port Side Signal Type for AIS-L validity.

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
    //##ModelId=3C506C36020C
    virtual ostream& WriteObject(ostream& theStream);

    //Reads object data from the stream and set the object with it.
    //
    //PARAM istream& theStream: the stream to read from.
    //
    //RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
    //##ModelId=3C506C360216
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_MSFAILUREBASE_H
