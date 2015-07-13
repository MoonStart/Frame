/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Blackboard region for Signal Alarm BB objects.
--------------------------------------------------------------------------*/

#include <cstdio>

#include <ExecutionSupport/FC_Action.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_TelAlarmCondition.h>

#include "../ALM_FPCommon.h"
#include "../ALM_FailureBase.h"

#include "../ALM_FailureRegion.h"

//-----------------------------------------------------------------------------
//##ModelId=3C506C390151
ALM_FailureRegion::ALM_FailureRegion(const FC_BbKey theKey) :
    TEL_BbRegionBase(theKey)
{
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C390153
ALM_FailureRegion::~ALM_FailureRegion()
{
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C39015D
void ALM_FailureRegion::PrintYourSelf( int anObjectIndex ) const
{
    fc_cout << endl;

    // print region context to std output.
    const_cast<ALM_FailureRegion&>(*this).SendRegionId(fc_cout);
    if ((*this).IsValid() == true) {
        fc_cout << " VALID";
    } else {
        fc_cout << " IN-VALID";
    }

    // If an object index was specified, display just that object
    if ( (anObjectIndex >= 0) && ((size_t)anObjectIndex < Size()) )
    {
        // Print the specified object from the region
        // get the alarm failure object in the region
        const ALM_FailureBase* aFailureObject = dynamic_cast <ALM_FailureBase*>(&ElementAt(anObjectIndex));

        if (aFailureObject)
        {
            // print the header.
            aFailureObject->PrintHeader();
            // print the object.
            aFailureObject->PrintYourSelf();
        }
        else
        {
            FC_THROW_ERROR( FC_NotSupportedError, "This instance is not an ALM_FailureBase class" );
        }
    }
    else
    {
        // Print all of the objects in the region
        for(anObjectIndex = 0; (size_t)anObjectIndex < Size(); anObjectIndex++)
        {
            // get the alarm failure object in the region
            const ALM_FailureBase* aFailureObject = dynamic_cast <ALM_FailureBase*>(&ElementAt(anObjectIndex));

            if (aFailureObject)
            {
                // if it is the first we go trough this
                if(anObjectIndex == 0)
                {
                    // print the header.
                    aFailureObject->PrintHeader();
                }

                // print the object.
                aFailureObject->PrintYourSelf();
            }
            else
            {
                FC_THROW_ERROR( FC_NotSupportedError, "This instance is not an ALM_FailureBase class" );
            }
        }
    }

    fc_cout << endl;
}
