/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OSC (Optical
                Supervisory Channel) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_OSCFAILUREBASE_H
#define  ALM_OSCFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OSC (Optical Supervisory Channel) layer.
//##ModelId=3C506C37028E
class ALM_OscFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	//##ModelId=3C506C370306
    ALM_OscFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	//##ModelId=3C506C370311
    virtual ~ALM_OscFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
	//##ModelId=3C506C370313
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
	//##ModelId=3C506C37031C
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.
	//##ModelId=3C506C370327
	virtual void PrintHeader() const;

	//Failure type enumeration of OSC (Optical Supervisory Channel) layer.
	//##ModelId=3C506C370357
    enum ALM_FailureType
    {
	    //Backward Defect Indication Payload OMS.
		//##ModelId=3C506C3703B1
        //BDIP_OMS = 0, not supported in fp2.0

	    //Backward Defect Indication Overhead OMS.
		//##ModelId=3C506C3703B2
        //BDIO_OMS = 0, not supported in fp2.0

        //Payload Missing Indication Overhead OMS.
		//##ModelId=3E776501009A
        PMI_OMS = 0,

	    //Farward Defect Indication Payload OMS.
		//##ModelId=3C506C3703BB
        FDIP_OMS,

	    //Farward Defect Indication Overhead OMS.
		//##ModelId=3C506C3703BC
        FDIO_OMS,

	    //Backward Defect Indication Paylaod OTS.
		//##ModelId=3C506C370393
        BDIP_OTS,

	    //Backward Defect Indication Overhead OTS.
		//##ModelId=3C506C37039D
        BDIO_OTS,

	    //Backward Defect Indication OTS.
		//##ModelId=3CC4D1D60374
        BDI_OTS,
        
	    //Payload Missing Indication OTS.
		//##ModelId=3C506C37039E
        PMI_OTS,

        //Trace Id Mismatch OTS.
		//##ModelId=3C506C3703A7
        TIM_OTS,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
		//##ModelId=3C506C3703CF
        ALM_INVALID_FAILURE,
		//##ModelId=3DBFFAEB0314
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.
	//##ModelId=3C506C37032F
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
	//##ModelId=3C506C37033A
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_OSCFAILUREBASE_H
