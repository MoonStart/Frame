/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of RS (Regenerator
                Section) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_RSFAILUREBASE_H
#define  ALM_RSFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of RS (Regenerator Section) layer.
//##ModelId=3F954C310225
class ALM_RsFailureBase : public ALM_FailureBase
{

public:

    //Constructor for this class.
    //
    //PARAM int theIndex: the index of the object within the region.
    //
    //PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
    //##ModelId=3F954C31035F
    ALM_RsFailureBase (int theIndex, bool theDefaultStatus = false );

    //Destructor for this class.
    //##ModelId=3F954C310362
    virtual ~ALM_RsFailureBase();

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
    //##ModelId=3F954C31036E
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
    //##ModelId=3F954C310371
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

    //This method prints the alarm header.
    //##ModelId=3F954C310374
    virtual void PrintHeader() const;

    //Failure type enumeration of RS (Regenerator Section) layer.
    //##ModelId=3F954C31038D
    enum ALM_FailureType
    {
        CSF_OPU_RS = 0,

        LOF_INT_RS,

        // Internal Generic AIS
        GEN_AIS_INT_RS,

        //Trace Id Mismatch RS.
        TIM_NSA_RS,
        TIM_RS,

        //Local Fault TGLAN RS.
        LF_RS,

        //Remote Fault TGLAN RS.
        RF_RS,
        //Loss Of Frame RS.
        //##ModelId=3F954C320042
        LOF_RS,
        //Tellabs AIS Internal Signal
        TAIS_RS,
        // Generic AIS For OC192
        GEN_AIS_RS,
        
        //Loss Of Signal RS.
        //##ModelId=3F954C320051
        LOS_RS,

        //Force TX AIS
        AIS_TX_RS,

        UPPER_INT_SA_RS,

        // Upper None Service Affecting RS.
		//##ModelId=3F954C320052
        UPPER_NSA_RS,

        // Upper Service Affecting RS.
		//##ModelId=3F954C320053
        UPPER_SA_RS,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
        //##ModelId=3F954C320060
        ALM_INVALID_FAILURE,
        //##ModelId=3F954C320061
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

    /**
     * The TSPII re-uses the LOF-RS defect to represent the LOSYNC defect when the port
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

    //Textual serialization used for BB edition. Writes the internal state of the object to a stream.
    //
    //PARAM ostream& theStream: the output stream to write to.
    //
    //RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.
    //##ModelId=3F954C31037D
    virtual ostream& WriteObject(ostream& theStream);

    //Reads object data from the stream and set the object with it.
    //
    //PARAM istream& theStream: the stream to read from.
    //
    //RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
    //##ModelId=3F954C310380
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_RSFAILUREBASE_H
