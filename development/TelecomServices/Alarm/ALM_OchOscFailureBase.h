/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class defines the failure type of OCH within the 
                OSC channel layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_OCHOSCFAILUREBASE_H
#define  ALM_OCHOSCFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OCH layer within the OSC Channel.

//##ModelId=3E776502010A
class ALM_OchOscFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.

	//##ModelId=3E77650202B8
    ALM_OchOscFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.

	//##ModelId=3E77650202C3
    virtual ~ALM_OchOscFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.

	//##ModelId=3E77650202CC
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.

	//##ModelId=3E77650202D6
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.

	//##ModelId=3E77650202E0
	virtual void PrintHeader() const;

	//Failure type enumeration of OCH layer within the OSC channel.

	//##ModelId=3E7765020308
    enum ALM_FailureType
    {
		//Open Connection Indication.
		//##ModelId=3E77650203E5
        OCI_OCH = 0,

		//Foward defect indication Payload
		//##ModelId=3E7765030007
		FDIP_OCH,

		//Foward defect indication Overhead
		//##ModelId=3E7765030011
		FDIO_OCH,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.

		//##ModelId=3E776503001B
        ALM_INVALID_FAILURE,

		//##ModelId=3E7765030025
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.

	//##ModelId=3E77650202E2
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.

	//##ModelId=3E77650202F4
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_OCHOSCFAILUREBASE_H
