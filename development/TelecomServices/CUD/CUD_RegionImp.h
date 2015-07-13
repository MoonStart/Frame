/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     April, 2007 Jim Beck
 DESCRIPTION:   The CUD blackboard region.
--------------------------------------------------------------------------*/

#ifndef CUD_REGIONIMP_H
#define CUD_REGIONIMP_H

//#include "CUD_Def.h"
#include "CommonTypes/CT_CUD_Definition.h"
#include <TelCommon/TEL_BbRegionBase.h>
#include "CUD_BbObject.h"


//Blackboard region template class for TCS Performance 
//Monitoring BB objects. This class can contain any type of 
//CUD related BB objects. The Allocate method performs an 
//allocation of the good BB object type. The operator[] 
//returns a reference to the good BB object type.
//
//PARAM OBJECT_TYPE: the type of BB object handled by this 
//region.

template<class OBJECT_TYPE>

class CUD_RegionImp:    public TEL_BbRegionBase
{

public:

    //Constructor for this class template.
    CUD_RegionImp ( const FC_BbKey& theKey = "unnamed",
                    uint32          theInitialSize = 0,
                    uint32          theNumberOfParam = 0,
                    CT_CUD_Status   theStatus = CT_CUD_UNKNOWN)
:
    TEL_BbRegionBase(theKey),
    myNumberOfParam(theNumberOfParam),
    myStatus(CT_CUD_UNKNOWN)
    {
         Resize(theInitialSize);
    }

    //Class default destructor.
    virtual ~CUD_RegionImp();

    //Allocates one instance of OBJECT_TYPE class. Returns a 
    //reference to the new object. Passes the number of 
    //parameters to the instance to be constructed. It 
    //returns the pointer to the allocated BB object.
    virtual FC_BbObject* Allocate(bbindex_t theIndex);

    //Deletes object from region.
    virtual void Deallocate(FC_BbObject* theObject);

    //Returns the BB object indexed by theIndex parameter.
    OBJECT_TYPE& operator[] ( int theIndex ) const
    {
        return static_cast<OBJECT_TYPE&> (ElementAt(theIndex));
    }

protected:

    //The number of parameters supported by the object 
    //allocated in this region. It depens of the signal (or 
    //layer) represented by this region. From now one, the 
    //only signal supported are Optical, Regenerator and 
    //Multiplexor Section. They are seen like a single signal.
    int myNumberOfParam;

    //The accumulation period type.
    CT_CUD_Status myStatus;
};

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline CUD_RegionImp<OBJECT_TYPE>::~CUD_RegionImp() 
{
    Resize(0);
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline FC_BbObject* CUD_RegionImp<OBJECT_TYPE>::Allocate(bbindex_t theIndex)
{
    return new OBJECT_TYPE (myNumberOfParam, myStatus);
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline void CUD_RegionImp<OBJECT_TYPE>::Deallocate(FC_BbObject* theObject)
{
    delete theObject;
}

#endif //CUD_REGIONIMP_H

