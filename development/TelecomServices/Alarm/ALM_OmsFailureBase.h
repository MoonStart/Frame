/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OMS (Optical
                Transport Section) layer.
--------------------------------------------------------------------------*/

#ifndef  ALM_OMSFAILUREBASE_H
#define  ALM_OMSFAILUREBASE_H

#include "Alarm/ALM_FailureBase.h"


//This class defines the failure type enumeration and the failure condition textual serialization of OMS (Optical Multiplex Section) layer.

//##ModelId=3E776501014E
class ALM_OmsFailureBase : public ALM_FailureBase
{
public:

	//Constructor for this class.
	//
	//PARAM int theIndex: the index of the object within the region.
	//
	//PARAM bool theDefaultStatus = false: the failures initial condition of this layer.
	
	//##ModelId=3E7765010307
    ALM_OmsFailureBase (int theIndex, bool theDefaultStatus = false );

	//Destructor for this class.
	
	//##ModelId=3E7765010312
    virtual ~ALM_OmsFailureBase();

	//Get the zero based failure index from the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //RETURN int: the zero based failure index.
	
	//##ModelId=3E7765010314
	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    //Get a signal alarm common type from a zero based failure index.
    //
    //PARAM int theIndex: the zero based failure index.
    //
    //RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined in the common type.
	
	//##ModelId=3E7765010325
	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

	//This method prints the alarm header.
	
	//##ModelId=3E776501032F
	virtual void PrintHeader() const;

	//Failure type enumeration of OMS (Optical Multiplex Section) layer.
	
	//##ModelId=3E7765010357
    enum ALM_FailureType
    {
        //Loss Of Signal Internal OMS.
        //##ModelId=3E776502004B
        LOSINT_OMS = 0,
        //Loss Of Signal OMS.
        //##ModelId=3E7765020060
        LOS_OMS,

        // Optical Power overLoad
		//##ModelId=3F954C320206
        OPOVLD_OMS,

        // Auto power management in proress
		//##ModelId=3F954C320207
        AOPE_OMS,

        //NUMBER OF FAILURES FOR THAT LAYER.
        //This identifier is the same for every enum ALM_FailureType defined into the other FailureBase class definition.
		//##ModelId=3E776502006A
        ALM_INVALID_FAILURE,
		//##ModelId=3E7765020074
	    ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

	//Textual serialization used for BB edition. Writes the internal state of the object to a stream.
	//
	//PARAM ostream& theStream: the output stream to write to.
	//
	//RETURN ostream&: an ostream reference that enables multiple insertion operators on a single line.

	//##ModelId=3E7765010331
    virtual ostream& WriteObject(ostream& theStream);

	//Reads object data from the stream and set the object with it.
	//
	//PARAM istream& theStream: the stream to read from.
	//
	//RETURN istream&: an istream reference that enables multiple extraction operators on a single line.

	//##ModelId=3E7765010343
    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_OMSFAILUREBASE_H
