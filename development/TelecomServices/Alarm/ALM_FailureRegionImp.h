/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Blackboard region template for Signal Alarm BB objects.
--------------------------------------------------------------------------*/

#ifndef ALM_FAILUREREGIONIMP_H
#define ALM_FAILUREREGIONIMP_H

#include <Blackboard/FC_BbRegionModifNotifyImp.h>

#include "Alarm/ALM_FailureRegion.h"


//Blackboard region template for Signal Alarm BB objects. This class contains BB objects and defines methods to allocate and de-allocate them.
//
//PARAM OBJECT_TYPE: the type of BB object allocated by this region.
//##ModelId=3C506C380394
template <class OBJECT_TYPE>
class ALM_FailureRegionImp : public ALM_FailureRegion
{

        //This class is used to display at the console (when ebable) the condition of a
//failure when it changed.
        //##ModelId=3C506C39007E
        typedef FC_BbRegionModifNotifyImp<ALM_FailureRegionImp<OBJECT_TYPE>,OBJECT_TYPE> FC_BbRegionModifNotify;

public:

        //Constructor for this class template.
    //
    //PARAM const FC_BbKey theKey = "unnamed": the BB key use at the region creation.
    //
    //PARAM int theInitialSize = 0: the initial size of the region.
        //##ModelId=3C506C390026
    ALM_FailureRegionImp (const FC_BbKey theKey = "unnamed", int theInitialSize = 0):
        ALM_FailureRegion(theKey)
    {
         Resize(theInitialSize);
                 myBbRegionModifNotifyPtr = NULL;
    }


        //Destructor for this class.
        //##ModelId=3C506C390030
    virtual ~ALM_FailureRegionImp();

        //Allocates one instance of OBJECT_TYPE class in RAM. Returns a reference to the new object. Passes the Index to the instance to be constructed. It return the pointer to the allocated BB object.
    //
    //PARAM bbindex_t theIndex: the index of the object in the region.
    //
    //RETURN FC_BbObject*: a pointer of the created object.
        //##ModelId=3C506C390039
    virtual FC_BbObject* Allocate(bbindex_t theIndex);

        //Return the BB object indexed by theIndex parameter.
        //
        //PARAM int theIndex: the index of the object in the region.
        //
        //RETURN OBJECT_TYPE&: a reference to the BB object indexed by the index.
        //##ModelId=3C506C39004C
    OBJECT_TYPE& operator[] ( int theIndex ) const
    {
                return static_cast<OBJECT_TYPE&> (ElementAt(theIndex));
    }

        //Reset all BB objects with in the region.
        //##ModelId=3C506C39004F
    virtual void Reset();

        //Set the action that is called when one object of the region has changed.
    //
    //PARAM FC_Action* theAction: the action to run when the region is modified.
        //##ModelId=3C506C390057
        virtual void SetNotifyAction(FC_Action* theAction);

        //Reset the notify action.
        //##ModelId=3C506C390060
        virtual void ResetNotifyAction();


protected:

private:

        // Modification notification class pointer.
        //##ModelId=3C515E2E007C
        FC_BbRegionModifNotify* myBbRegionModifNotifyPtr;

};


//-----------------------------------------------------------------------------
//##ModelId=3C506C390030
template <class OBJECT_TYPE>
ALM_FailureRegionImp<OBJECT_TYPE>::~ALM_FailureRegionImp()
{
     Resize(0);
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C390039
template <class OBJECT_TYPE>
FC_BbObject* ALM_FailureRegionImp<OBJECT_TYPE>::Allocate(bbindex_t theIndex)
{
    return new OBJECT_TYPE (theIndex);
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C39004F
template <class OBJECT_TYPE>
void ALM_FailureRegionImp<OBJECT_TYPE>::Reset()
{
        size_t aBbIndex;

    for(aBbIndex = 0; aBbIndex < Size(); aBbIndex++)
        {
                (*this)[aBbIndex].Reset();
        }
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C390057
template <class OBJECT_TYPE>
void ALM_FailureRegionImp<OBJECT_TYPE>::SetNotifyAction(FC_Action* theAction)
{
        if(myBbRegionModifNotifyPtr == NULL)
        {
                myBbRegionModifNotifyPtr = new FC_BbRegionModifNotify((*this));
        }

        myBbRegionModifNotifyPtr->AddModifAction(theAction);
}

//-----------------------------------------------------------------------------
//##ModelId=3C506C390060
template <class OBJECT_TYPE>
void ALM_FailureRegionImp<OBJECT_TYPE>::ResetNotifyAction()
{
        delete myBbRegionModifNotifyPtr; myBbRegionModifNotifyPtr = NULL;
}




#endif //ALM_FAILUREREGIONIMP_H
