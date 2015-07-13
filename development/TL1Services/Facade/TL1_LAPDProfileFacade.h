/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 24, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 LAPD Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPROFILEFACADE_H__
#define __TL1_LAPDPROFILEFACADE_H__

#ifndef __TL1_LAPDPROFILEFACADE_H__
#include <TL1Core/TL1_LAPDProfileDomain.h>
#endif

#ifndef __TL1_LAPDPROFILEENTITY_H__
#include <TL1Core/TL1_LAPDProfileEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define LAPDPROFILE_EdLapdPf( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLapdPf( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ))

#define LAPDPROFILE_RtrvLapdPf( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLapdPf( \
                        theAddr, \
                        theResponse ) )
#endif
