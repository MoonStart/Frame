// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_PilotToneControllerRequest.h"
#include <ErrorService/FC_Error.h>

MON_PilotToneControllerRequest::MON_PilotToneControllerRequest(
                               MON_OchConfigRegion* theOchConfigRegion, 
                               MON_OchStatusRegion* theOchStatusRegion,
                               TSPII_PilotToneRegion* theTspiiRegion,
                               uint32 theBandwidth):
    myOchConfigRegion(theOchConfigRegion),
    myOchStatusRegion(theOchStatusRegion),
    myTspiiRegion(theTspiiRegion),
    myFirstWavelength(0),
    myBandwidth(theBandwidth)
{
    FC_THROW_ERROR_IF(myBandwidth > myOchConfigRegion->Size(), 
                      FC_ValueOutOfRangeError, "Bancwidth exceed region capacity");
}

MON_PilotToneControllerRequest::~MON_PilotToneControllerRequest()
{
}

bool MON_PilotToneControllerRequest::SetFirstWavelength(uint32 theFirstWavelength)
{
    // make sure this new offset does not exceed region with current bandwidth
    bool hasChanged = false;
    if (theFirstWavelength < myOchConfigRegion->Size() &&
        (myOchConfigRegion->Size() - myFirstWavelength >=  myBandwidth))
    {
        if (myFirstWavelength != theFirstWavelength)
        {
            myFirstWavelength = theFirstWavelength;
            hasChanged = true;
        }
    }
    else
        FC_THROW_ERROR(FC_ValueOutOfRangeError, "1st wavelenght makes bandwidth exceed region capacity");

    return hasChanged;
}


MON_OchConfigRegion* MON_PilotToneControllerRequest::GetConfigRegion()  const
{ 
    return myOchConfigRegion; 
}

MON_OchStatusRegion* MON_PilotToneControllerRequest::GetStatusRegion()  const
{ 
    return myOchStatusRegion; 
}

TSPII_PilotToneRegion* MON_PilotToneControllerRequest::GetTspiiRegion()  const
{ 
    return myTspiiRegion; 
}

