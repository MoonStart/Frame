/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm   
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class set the failure status according to its defect
                status for a normal failure.
--------------------------------------------------------------------------*/
#ifndef ALM_NORMALFAILURE_H
#define ALM_NORMALFAILURE_H

#include "ALM_DefectStatusDefinition.h"

//This class is responsible to manage the failure status of a normal failure according to its defect status and the requirements relate to that failure.
//##ModelId=3C506C3300DA
class ALM_NormalFailure
{

public:

	//Constructor for this class.
	//##ModelId=3C506C330134
    ALM_NormalFailure ();

    //Destructor for this class.
	//##ModelId=3C506C33013E
    virtual ~ALM_NormalFailure();

	//Reset... to be compatible.
	//##ModelId=3DBFFAE6029F
    virtual void Reset();

	//This method returns the failure status for a normal failure. note that all parameters are for reason of compatibility.
    //
    //PARAM bool theStatus: the status of the defect.
    //
    //PARAM ALM_TCount theTCount: the transition counter of the defect.
    //
    //PARAM bool theRecoveryOverride = false: flag to bypass the recovery timer.
    //
    //RETURN bool: the status of the failure.
	//##ModelId=3C506C330140
    virtual bool DefectUpdated (bool theStatus, ALM_TCount theTCount,
                                bool theRecoveryOverride = false);

};

#endif //ALM_NORMALFAILURE_H
