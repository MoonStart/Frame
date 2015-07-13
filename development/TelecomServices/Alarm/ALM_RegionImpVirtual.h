/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards 
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Blackboard region template class for Signal Alarm BB objects
--------------------------------------------------------------------------*/

#ifndef ALM_REGIONIMPVIRTUAL_H
#define ALM_REGIONIMPVIRTUAL_H

#include "ALM_FailureRegionImp.h"


//Blackboard region template class for Signal Alarm BB objects. This class contains object of type OBJECT_TYPE. The method Allocate perform allocations of OBJECT_TYPE, while the operator[] returns a reference to an OBJECT_VIRTUAL. It assumes that OBJECT_TYPE is a derived class of OBJECT_VIRTUAL. This functionality is used to hide the specific implementation of BB object from a user. This template allocates BB objects of a specialized class, but its operator[] return a reference to a BB object base class.
//
//PARAM OBJECT_TYPE: the type of BB object allocated by this region.
//
//PARAM OBJECT_VIRTUAL: the type of BB object reference returned by the operator[].
//##ModelId=3C506C36028D
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
class ALM_RegionImpVirtual:    public ALM_FailureRegionImp<OBJECT_VIRTUAL>
{

	//This class is used to display at the console (when ebable) the condition of a 
//failure when it changed.
	//##ModelId=3DBFFAEA0395
	typedef FC_BbRegionModifNotifyImp<ALM_RegionImpVirtual<OBJECT_VIRTUAL,OBJECT_TYPE>,OBJECT_VIRTUAL> FC_BbRegionModifNotifyVir;

public:

	//Constructor for this class template.
	//
	//PARAM const FC_BbKey& theKey = "unnamed": the BB key for this region. Must be unique.
	//
	//PARAM int theInitialSize = 0: initial number of objects in region.
	//##ModelId=3C506C3603CF
    ALM_RegionImpVirtual ( const FC_BbKey& theKey = "unnamed", int theInitialSize = 0):
        ALM_FailureRegionImp<OBJECT_VIRTUAL>( theKey )
    {
        Resize(theInitialSize);
        myBbRegionModifNotifyVirPtr = NULL;
    }

    //Class default destructor.
	//##ModelId=3C506C3603D8
    virtual ~ALM_RegionImpVirtual();

    //Allocates one instance of OBJECT_TYPE class. Returns a reference to the new object. Passes the number of parameters to the instance to be constructed. It returns the pointer to the allocated BB object.
    //
    //PARAM bbindex_t theIndex: the index of the object in the region.
    //
    //RETURN FC_BbObject*: a pointer of type OBJECT_TYPE to the new object.
	//##ModelId=3C506C3603DA
    virtual FC_BbObject* Allocate(bbindex_t theIndex);

	//Set the action that is called when one object of the region has changed.
    //
    //PARAM FC_Action* theAction: the action to run when the region is modified.
	//##ModelId=3DBFFAEA02C3
	virtual void SetNotifyAction(FC_Action* theAction);

	//Reset the notify action.
	//##ModelId=3DBFFAEA031D
	virtual void ResetNotifyAction();

private:

	// Modification notification class pointer.
	//##ModelId=3DBFFAEA036E
	FC_BbRegionModifNotifyVir* myBbRegionModifNotifyVirPtr;

};

//-----------------------------------------------------------------------------
//##ModelId=3C506C3603D8
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
ALM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::~ALM_RegionImpVirtual() 
{
    Resize(0);
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C3603DA
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
FC_BbObject* ALM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::Allocate(bbindex_t theIndex)
{
    return new OBJECT_TYPE (theIndex);
}

//-----------------------------------------------------------------------------
//##ModelId=3DBFFAEA02C3
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
void ALM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::SetNotifyAction(FC_Action* theAction)
{
	if(myBbRegionModifNotifyVirPtr == NULL)
	{
		myBbRegionModifNotifyVirPtr = new FC_BbRegionModifNotifyVir((*this));
	}

	myBbRegionModifNotifyVirPtr->AddModifAction(theAction);
}

//-----------------------------------------------------------------------------
//##ModelId=3DBFFAEA031D
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
void ALM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::ResetNotifyAction()
{
	delete myBbRegionModifNotifyVirPtr; myBbRegionModifNotifyVirPtr = NULL;
}


#endif //ALM_REGIONIMPVIRTUAL_H
