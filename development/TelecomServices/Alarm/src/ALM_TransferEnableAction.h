/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :   Signal Alarm 
TARGET      :   All cards
AUTHOR      :   Marc Vendette
DESCRIPTION :   Implementation file for the ALM_TransferEnableAction class.
--------------------------------------------------------------------------*/
#ifndef ALM_TRANSFERENABLEACTION_H
#define ALM_TRANSFERENABLEACTION_H

#include <ExecutionSupport/FC_Action.h>


//Forward class declaration;
class ALM_ListOfAction;


//This class defines the action that will enable the transfer after that the specified time before transfer is elapsed.
//##ModelId=3C506C3202A5
class ALM_TransferEnableAction : public FC_Action
{

public:

	//Class constructor.
    //
    //PARAM ALM_ListOfAction* theListOfActionPt: a pointer to the list of action for which all regions associated to should be transfer.
	//##ModelId=3C506C32030A
    ALM_TransferEnableAction(ALM_ListOfAction* theListOfActionPtr);

	//Virtual class destructor.
	//##ModelId=3C506C32031D
    virtual ~ALM_TransferEnableAction();

	//Obselete.
	//##ModelId=3C506C320314
    void Run(FC_Object* theObject = NULL);

	//Set the transfer enable action flag to true.
    //
    //PARAM unsigned theRunReason: Integer identifier defined and provided by the invoker object to distinguish between various conditions that led to running this action.
    //
    //PARAM FC_Object* theInvokerObj: Address of the object invoking the Run method on this action.
    //
    //PARAM C_Object* theParam: Generic parameter to be passed to the action. By default this parameter is set to NULL. Used for compatibility.
    //
    //RETURN FC_Object*: return NULL for compatability.
	//##ModelId=3DBFFAE600F0
    virtual FC_Object* DoRunWithReason( unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam);


private:

	//The list of action pointer that enable the transfer.
	//##ModelId=3C506FBA027E
    ALM_ListOfAction* itsListOfActionPtr;

};

#endif  // ALM_TRANSFERENABLEACTION_H
