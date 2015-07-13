/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_BB_REGION_H
#define SNMP_BB_REGION_H

#include <Blackboard/FC_BbRegionVectImp.h>

template <class T>
class SNMP_BbRegion : public FC_BbRegionVectImp<T>
{
public:
    //Constructor
    SNMP_BbRegion(const FC_BbKey theKey,
                   size_t numberOfElement)
          :FC_BbRegionVectImp<T>(theKey,0)
    {
        this->Resize(numberOfElement);
    }

    virtual ~SNMP_BbRegion() {}

    T& operator[] ( bbindex_t theIndex ) const
    {
#ifdef LINUX
        return static_cast<T&>(*(*this->myObjVectorPtr)[theIndex]);
#else
        return static_cast<T&>(*(*myObjVectorPtr)[theIndex]);
#endif
    }

};


#endif // SNMP_BB_REGION_H
