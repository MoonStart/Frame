/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OCH (Optical 
                Channel) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_OCHFAILUREBASE_H
#define  ALM_OCHFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OCH (Optical Channel) layer.
//##ModelId=3C506C380272
class ALM_OchFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	//##ModelId=3C506C3802EB
    ALM_OchFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	//##ModelId=3C506C3802F6
    virtual ~ALM_OchFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
	//##ModelId=3C506C3802FE
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
	//##ModelId=3C506C380308
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.
	//##ModelId=3C506C380312
	virtual void PrintHeader() const;

	//Failure type enumeration of OCH (Optical Channel) layer.
	//##ModelId=3C506C380330
    enum ALM_FailureType
    {
	//Pilot Tone Missing OCH.
		//##ModelId=3C506C38036C
        DTD_OCH = 0,

		//Diagnostique Tone Detected
		//##ModelId=3E7765030089
		LOS_OCH,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
		//##ModelId=3C506C380376
        ALM_INVALID_FAILURE,
		//##ModelId=3DBFFAEC01A3
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.
	//##ModelId=3C506C380314
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
	//##ModelId=3C506C38031D
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_OCHFAILUREBASE_H
