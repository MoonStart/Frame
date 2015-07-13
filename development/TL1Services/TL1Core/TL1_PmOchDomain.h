/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Performance Monitoring Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMOCHDOMAIN_H__
#define __TL1_PMOCHDOMAIN_H__

class TL1_Response;
class CT_TL1_PmArg;

/**
   CLASS TL1_PmDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of PM related TL1 commands, that a TL1 Entities
   for a PM is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_PmOchDomain
{
public:

    virtual void SetOptThOch(CT_TL1_PmArg& theArg,
                             TL1_Response& theResponse) = 0;
};

#endif
