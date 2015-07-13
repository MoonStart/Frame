/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OPT (Optical)
                layer.
--------------------------------------------------------------------------*/

#ifndef ALM_OPTFAILUREBASE_H
#define ALM_OPTFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"
#include "Alarm/src/ALM_DefectStatusDefinition.h"
#include "Alarm/ALM_FPCommon.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OPT (Optical) layer.
//##ModelId=3C506C380005
class ALM_OptFailureBase : public ALM_FailureBase
{

public:

    //Constructor for this class.
    //
    //PARAM int theIndex: the index of the object within the region.
    //
    //PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    //##ModelId=3C506C38007D
    ALM_OptFailureBase (int theIndex, bool theDefaultStatus = false );

    //Destructor for this class.
    //##ModelId=3C506C380088
    virtual ~ALM_OptFailureBase();

    /**
     * Retrieve the occurring time of a failure using the signal alarm common type.
     *
     * RETURN : the signal type CT_TEL_SignalType.
     */
    inline int GetSignalType() const;

	/**
     * Set the signal type currently associated with the port
	 * 
	 * PARAM CT_TEL_SignalType (int) the signal type.
     */
    inline void SetSignalType(int signalType);

    //Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
    //##ModelId=3C506C38008A
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
    //##ModelId=3C506C380093
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex(int theIndex) const;

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
    //##ModelId=3C506C3800A5
    virtual void PrintHeader() const;

    // Failure type enumeration of OPT (Optical) layer.
    //##ModelId=3C506C3800C3
    enum ALM_FailureType
    {
        //Facility Mismatch
        //##ModelId=3E776501011C
        MFA_OPT = 0,

        //Loss Of Clock OPT.
        //##ModelId=3C506C380109
        LOC_OPT,
  
        //Switch Threshold Crossed
        SWTH_OPT,
  
        //Loss Of Signal power OPT.
        //##ModelId=3C506C38010A
        LOS_OPT,

        // Upper None Service Affecting OPT.
		//##ModelId=3F954C3201C8
        UPPER_NSA_OPT,

        // Upper Service Affecting OPT.
		//##ModelId=3F954C3201C9
        UPPER_SA_OPT,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
        //##ModelId=3C506C380113
        ALM_INVALID_FAILURE,
        //##ModelId=3DBFFAEB03E7
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    // Signal Protect defect indications enumerations for the OPT (Optical) layer.
    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        SP_PROTNA,

        ALM_SP_INVALID_DEFECT,

        ALM_SP_NB_OF_DEFECT = ALM_SP_INVALID_DEFECT
    };

protected:

    /**
     * The TSPII re-uses the LOC-OPTdefect to represent the LOCSYNC defect when the port
     * is defined as a GbE signal instead of a SONET signal, for example, on the RAMM.
     * The SMTM allows the port to be configured either way, therefore this will allow
     * Signal Alarm the ability to indicate the correct alarm to AM.
     */
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
	//##ModelId=3C506C390329
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

	/**
     * Reads object data from the stream and set the object with it.
	 *
	 * PARAM FC_Stream& theStream: the FC stream to read from.
	 *
	 * RETURN FC_Stream&: a FC_Stream reference that enables multiple extraction operators on a single line.
     */
	//##ModelId=3C506C390332
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
    //##ModelId=3C506C3800A7
    virtual ostream& WriteObject(ostream& theStream);

    /**
     * Reads object data from the stream and set the object with it.
     *
     * PARAM istream& theStream: the stream to read from.
     *
     * RETURN istream&: an istream reference that enables multiple extraction operators
     * on a single line.
     */
    //##ModelId=3C506C3800B1
    virtual istream& ReadObject(istream& theStream);

};



#endif //ALM_OPTFAILUREBASE_H
