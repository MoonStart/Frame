/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm   
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class set the failure status according to the defect
                status for a normal failure.
--------------------------------------------------------------------------*/

#include "ALM_NormalFailure.h"

//-----------------------------------------------------------------
//##ModelId=3C506C330134
ALM_NormalFailure::ALM_NormalFailure ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C33013E
ALM_NormalFailure::~ALM_NormalFailure ()
{
}

//-----------------------------------------------------------------
//Reset... to be compatible
//##ModelId=3DBFFAE6029F
void ALM_NormalFailure::Reset()
{
};

//-----------------------------------------------------------------
//Return the failure status for a normal failure.
//Param theStatus: The status of the defect.
//Param theTCount: The transition counter of the defect.
//##ModelId=3C506C330140
bool ALM_NormalFailure::DefectUpdated (bool theStatus, ALM_TCount theTCount,
                                       bool theRecoveryOverride)
{
    // The theTCount parameter is there for interface compatibitity with
    // the derived class
    return theStatus;
}


