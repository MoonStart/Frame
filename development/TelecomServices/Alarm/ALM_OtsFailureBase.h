/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OTS (Optical
                Transport Section) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_OTSFAILUREBASE_H
#define  ALM_OTSFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OTS (Optical Transport Section) and OMS (Optical Multiplex Section) layer.
//##ModelId=3C506C370158
class ALM_OtsFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	//##ModelId=3C506C3701DB
    ALM_OtsFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	//##ModelId=3C506C3701E5
    virtual ~ALM_OtsFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
	//##ModelId=3C506C3701E7
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
	//##ModelId=3C506C3701F0
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.
	//##ModelId=3C506C3701FA
	virtual void PrintHeader() const;

	//Failure type enumeration of OTS (Optical Transport Section) and OMS (Optical Multiplex Section) layer.
	//##ModelId=3C506C370220
    enum ALM_FailureType
    {
        //Loss Of Signal OTS.
		//##ModelId=3C506C37025D
        LOS_OTS = 0,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
		//##ModelId=3C506C370266
        ALM_INVALID_FAILURE,
		//##ModelId=3DBFFAEB022E
        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.
	//##ModelId=3C506C370202
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.
	//##ModelId=3C506C37020C
    virtual istream& ReadObject(istream& theStream);

};




#endif // ALM_OTSFAILUREBASE_H
