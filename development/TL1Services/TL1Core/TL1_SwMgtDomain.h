/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Software Management Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWMGTDOMAIN_H__
#define __TL1_SWMGTDOMAIN_H__

//#ifndef __CT_TL1_SWMGT_H__
//#include <CommonTypes/CT_TL1_SwMgt.h>
//#endif

/**
   CLASS TL1_SwMgtDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Software Management related TL1 commands, that a
   TL1 Entities for Software Management  is expected to implement. This class
   contains no data member nor any default implementation.
 */

// Not completetely defined for AP100, to be updated later.

class TL1_SwMgtDomain
{
public:

    virtual void AlwBkupSchedMem( ) = 0;       //AP300

    virtual void InhBkupSchedMem( ) = 0;       //AP300

    virtual void RtrvBkupSchedMem( )const = 0; //AP300

    virtual void SchedBkupMem( ) = 0;          //AP300
};

#endif

