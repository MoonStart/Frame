/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of ODU (Optical Data
                Unit) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_ODUFAILUREBASE_H
#define  ALM_ODUFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of ODU (Optical Data Unit) layer.
//##ModelId=3C506C380131
class ALM_OduFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	//##ModelId=3C506C3801B3
    ALM_OduFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	//##ModelId=3C506C3801BD
    virtual ~ALM_OduFailureBase();

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

	// Failure type enumeration of ODU (Optical Data Unit) layer.
	//##ModelId=3C506C3801FA
    enum ALM_FailureType
    {
        PLM_ODU = 0,

	    //Backward Defect Indication ODU.
		//##ModelId=3C506C380236
        BDI_ODU,

	    // Bit Error Rate (SignalDegrade)
        BER_ODU,

        // Loss of OPU MultiFrame Identifier
        LOOMFI_ODU,
	    //Trace Id Mismatch ODU.
		//##ModelId=3C506C38024A
        TIM_NSA_ODU,
        TIM_ODU,

	    //Open Connection Indication ODU.
		//##ModelId=3C506C380240
        OCI_ODU,

	    //Lock ODU.
		//##ModelId=3C506C380241
        LCK_ODU,
        
        //Alarm Indication Signal ODU.
        //##ModelId=3C506C380254
        AIS_ODU,

        LOFLOM_ODU,

        MSIM_ODU,

        GENAIS_ODU,

        SSF_ODU,

        // Upper None Service Affecting OTU.
        UPPER_NSA_ODU,
 
        // Upper Service Affecting OTU.
        UPPER_SA_ODU,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    // Signal Protect defect indications enumerations for the ODU (Optical Data Unit) layer.
    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        SP_PROTNA,

        SP_ODUKP_NOT_SERVICE_AFFECTING,

        SP_ODUKP_PROTNA,

        SP_FOP_PM,

        SP_FOP_NR,

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

#endif // ALM_ODUFAILUREBASE_H
