// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_Application.h"
#include <ExecutionSupport/FC_WakeUpProcessAction.h>

//##ModelId=3B8BC9E4002D
bool SP_Application::myColdBoot = false;

//##ModelId=39ACEFBC0099
SP_Application::SP_Application(T6100_CardIf& theCardContext, T6100_TelecomIf& theContext):
    myContext(theContext),
    myCardContext(theCardContext),
    myConfigRegion(NULL),
    myStatusRegion(NULL),
    myStatRegions(NULL,NULL)
{

}

//##ModelId=39ACEFBC0098
SP_Application::~SP_Application()
{

}


//##ModelId=3B8BC9E40376
void SP_Application::InitCold(FC_Object* theObject)
{
    myColdBoot = true;
}

//Return my card context
T6100_CardIf& SP_Application::GetCardContext() const 
{
    return myCardContext;
}

//Return my context
T6100_TelecomIf& SP_Application::GetContext() const 
{
    return myContext;
}

//implemented in sub class
FC_WakeUpProcessAction* SP_Application::GetStatusCollectionAction()
{
    return NULL;
}

//implemented in sub class
FC_WakeUpProcessAction* SP_Application::GetLongDelayStatusCollectionAction()
{
	return NULL;
}

