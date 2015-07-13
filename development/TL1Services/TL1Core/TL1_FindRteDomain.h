#ifndef __TL1_FINDRTEDOMAIN_H__
#define __TL1_FINDRTEDOMAIN_H__
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 11, 2011 - TLD
DESCRIPTION:    Header file for TL1 Find Route Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <CommonTypes/CT_TL1_Base.h>



class TL1_Response;
class TL1_OprFindRteParameters;


class TL1_FindRteDomain
{
public:

    virtual void OprFindRte( const TL1_OprFindRteParameters&   theParameters,
                             TL1_Response&                     theResponse ) = 0;
};

#endif // __TL1_FINDRTEDOMAIN_H__
