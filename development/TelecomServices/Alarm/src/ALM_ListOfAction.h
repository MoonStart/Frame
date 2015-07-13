/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class is an action that wake-up a one-shot process.
--------------------------------------------------------------------------*/
#ifndef ALM_LISTOFACTION_H
#define ALM_LISTOFACTION_H

#include <ExecutionSupport/FC_ListOfAction.h>

// Foward declaration of classes
class FC_BbRegion;
class FC_Object;
class ALM_SubApplicationOnCard;

//This class (derived from FC_ListOfAction) is used to wake-up a process when at least one of all previously registered regions has been changed. The process can be any kind of, but usually it is usually a transfer process.
//##ModelId=3C506C330170
class ALM_ListOfAction: public FC_ListOfAction
{

public:

	//Constructor for this class.
    //
    //RARAM ALM_SubApplicationOnCard& theApplication: the application supporting this sub-application.
	//##ModelId=3C506C3301CB
    ALM_ListOfAction (ALM_SubApplicationOnCard& theApplication);

	//Destructor for this class.
	//##ModelId=3C506C3301D5
    virtual ~ALM_ListOfAction();

	//This method sets the current transfer enable status.
    //
    //PARAM bool theTransferEnable: the current transfer status to set.
	//##ModelId=3C506C3301D7
    inline void SetTransferEnable(bool theTransferEnable);
    
	//This method returns the current transfer enable status.
    //
    //RETURN bool: the current transfer status.
	//##ModelId=3C506C3301DF
    inline bool GetTransferEnable(void) const;

	//Add a region for which one an update notify will be done for.
    //
    //PARAM FC_BbRegion* theRegion: a pointer to the region.
	//##ModelId=3C506C3301E9
    void InsertRegion(FC_BbRegion* theRegion);

    //This method runs the action list and call an update notify of all regions within the region vector. If at least one of the region is updated and the process to call is appropriately set, a wake-up will be done for that process.
    //
    //PARAM unsigned theRunReason: Integer identifier defined and provided by the invoker object to distinguish between various conditions that led to running this action.
    //
    //PARAM FC_Object* theInvokerObj: Address of the object invoking the Run method on this action.
    //
    //PARAM C_Object* theParam: Generic parameter to be passed to the action. By default this parameter is set to NULL. Used for compatibility.
    //
    //RETURN FC_Object*: return NULL for compatability.
	//##ModelId=3C506C3301F2
    virtual FC_Object* DoRunWithReason( unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam);

    //Increment the modification counter of all regions in itsRegionVector.
	//##ModelId=3DBFFAE700E8
    void IncModifyCounterOfAllRegion();

	//This method delete all actions registered in that list of action.
	//##ModelId=3C603CA102A4
    void DeleteAllAction();

    //Operator[] to get get the action according to the index.
    //
    //PARAM int theIndex: the index of the action in the vector.
    //
    //RETURN FC_Action*: a pointer to the corresponding action.
	//##ModelId=3C95FE090149
    FC_Action* operator[](int theIndex);

    //Return a pointer that points to the instance name.
    //
    //RETURN const char*: the instance name.
	//##ModelId=3CC4D1D3012B
    virtual const char* GetInstanceName(void ) const;


private:

	//This vector contained the regions that will trigger a wake-up of myProcess, if at least one of these are modified.
	//##ModelId=3C515E2B0259
    vector<FC_BbRegion*> itsRegionVector;

	//Transfer enable flag.
	//##ModelId=3C506C33029D
    bool itsTransferEnable;

	//A rererence to my application.
	//##ModelId=3C506FBB012B
    ALM_SubApplicationOnCard& myApplication;

	//First execution flag.
	//##ModelId=3C506C3302BB
    bool itsFirstExec;

    //Keep the previous context active flag.
	//##ModelId=3DBFFAE70110
    bool itsPreviousContextActive;

};

//-----------------------------------------------------------------
//##ModelId=3C506C3301D7
inline void ALM_ListOfAction::SetTransferEnable(bool theTransferEnable)
{
    itsTransferEnable = theTransferEnable;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3301DF
inline bool ALM_ListOfAction::GetTransferEnable(void) const
{
    return itsTransferEnable;
}

#endif //ALM_LISTOFACTION_H

