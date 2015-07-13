/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The PM blackboard region.
--------------------------------------------------------------------------*/

#ifndef PM_REGIONIMPVIRTUAL_H
#define PM_REGIONIMPVIRTUAL_H

#include "PM_Def.h"
#include "PM_RegionImp.h"


//Blackboard region template class for TCS Performance 
//Monitoring BB objects. This class contains object of type 
//OBJECT_TYPE. The method Allocate perform allocations of 
//object of type OBJECT_TYPE, while the operator[] returns a 
//reference to an object of type OBJECT_VIRTUAL. It assumes 
//that OBJECT_TYPE is a derived class of OBJECT_VIRTUAL. This 
//functionality is used to hide the specific implementation 
//of BB object from a user. This template allocates BB 
//objects of a specialized class, but its operator[] return a 
//reference to a BB object base class.
//
//PARAM OBJECT_TYPE: the type of BB object allocated by this 
//region.
//
//PARAM OBJECT_VIRTUAL: the type of BB object reference 
//returned by the operator[].
//##ModelId=3C1F6F67010D
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
class PM_RegionImpVirtual:    public PM_RegionImp<OBJECT_VIRTUAL>
{

public:

    //Constructor for this class template.
    //##ModelId=3C1F6F68029F
    PM_RegionImpVirtual ( const FC_BbKey& theKey = "unnamed",
                          uint32          theInitialSize = 0,
                          uint32          theNumberOfParam = 0,
                          CT_PM_Period    thePeriod = CT_PM_PERIOD_UNKNOWN):
        PM_RegionImp<OBJECT_VIRTUAL>( theKey,
                                      0, //Put 0 as size, the resize MUST done at the last derived
                                      theNumberOfParam,
                                      thePeriod)
    {
         this->Resize(theInitialSize);

    }

    //Class default destructor.
    //##ModelId=3C1F6F6802B3
    virtual ~PM_RegionImpVirtual();

    //Allocates one instance of OBJECT_TYPE class. Returns a 
    //reference to the new object. Passes the number of 
    //parameters to the instance to be constructed. It 
    //returns the pointer to the allocated BB object.
    //##ModelId=3C1F6F6802B5
    virtual FC_BbObject* Allocate(bbindex_t theIndex);

    //Deletes object from region.
    //##ModelId=3C1F6F6802C7
    virtual void Deallocate(FC_BbObject* theObject);
};

//-----------------------------------------------------------------
//##ModelId=3C1F6F6802B3
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
inline PM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::~PM_RegionImpVirtual() 
{
    this->Resize(0);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6802B5
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
inline FC_BbObject* PM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::Allocate(bbindex_t theIndex)
{
#ifdef LINUX
    return new OBJECT_TYPE (this->myNumberOfParam, this->myPeriod);
#else
    return new OBJECT_TYPE (myNumberOfParam, myPeriod);
#endif

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6802C7
template<class OBJECT_VIRTUAL, class OBJECT_TYPE>
inline void PM_RegionImpVirtual<OBJECT_VIRTUAL, OBJECT_TYPE>::Deallocate(FC_BbObject* theObject)
{
    delete theObject;

}

#endif //PM_REGIONIMPVIRTUAL_H
