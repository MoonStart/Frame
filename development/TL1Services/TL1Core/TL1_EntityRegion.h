/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 14, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Entity Region class template
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITYREGION_H__
#define __TL1_ENTITYREGION_H__

#ifndef __FC_BBREGIONVECTIMP_H__
#include <Blackboard/FC_BbRegionVectImp.h>
#endif

/**
   class T is assumed to be a TL1_Entity derived class
 */
template <class T>
class TL1_EntityRegion : public FC_BbRegionVectImp<T>
{
public:
    TL1_EntityRegion( const FC_BbKey& theKey = "unnamed",
                      size_t theInitialSize = 0 );

};

template <class T>
TL1_EntityRegion<T>::TL1_EntityRegion( const FC_BbKey& theKey,
                                       size_t theInitialSize ) :
    FC_BbRegionVectImp<T>( theKey, theInitialSize )
{
    for( bbindex_t cpt = 0; (size_t)cpt < Size(); ++cpt)
    {
        (*this)[cpt].SetParent( *this );
    }
}

#endif
