/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAG Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAGFACADE_H__
#define __TL1_LAGFACADE_H__

#ifndef __TL1_LAGDOMAIN_H__
#include <TL1Core/TL1_LagDomain.h>
#endif

#ifndef __TL1_LAGENTITY_H__
#include <TL1Core/TL1_LagEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define LAG_EntLag( \
                        theLagAddr, \
                        theAddAddr,\
                        theAddType,\
                        theVlanTag,\
                        theTagMode,\
                        theTpid,\
                        theCFProfile,\
                        theLacpEnabled, \
                        theSystemPriority, \
                        theSystemIdentifier, \
                        theTimeoutMode, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntLag( \
                                    theLagAddr, \
                                    theAddAddr,\
                                    theAddType,\
                                    theVlanTag,\
                                    theTagMode,\
                                    theTpid,\
                                    theCFProfile,\
                                    theLacpEnabled, \
                                    theSystemPriority, \
                                    theSystemIdentifier, \
                                    theTimeoutMode, \
                                    theAlarmProfile, \
                                    thePrimaryState, \
                                    theResponse  ) )
                                    
#define LAG_EdLag( \
                        theLagAddr, \
                        theAddAddr,\
                        theAddType,\
                        theRmvAddr,\
                        theRmvType,\
                        theVlanTag,\
                        theTagMode,\
                        theTpid,\
                        theCFProfile,\
                        theLacpEnabled, \
                        theSystemPriority, \
                        theSystemIdentifier, \
                        theTimeoutMode, \
                        theAlarmProfile, \
                        theCommandMode,\
                        thePrimaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLag( \
                                    theLagAddr,\
                                    theAddAddr,\
                                    theAddType,\
                                    theRmvAddr,\
                                    theRmvType,\
                                    theVlanTag,\
                                    theTagMode,\
                                    theTpid,\
                                    theCFProfile,\
                                    theLacpEnabled, \
                                    theSystemPriority, \
                                    theSystemIdentifier, \
                                    theTimeoutMode, \
                                    theAlarmProfile,\
                                    theCommandMode,\
                                    thePrimaryState	,\
                                    theResponse ) )

#define LAG_RtrvLag( \
                        theLagAddr, \
                        theAlarmProfile, \
                        theMember, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLag(theLagAddr, \
                                        theAlarmProfile,\
                                        theMember,\
                                        thePrimaryState,\
                                        theSecondaryState,\
                                        theResponse ) )

                                      
#define LAG_RtrvLagMembers( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLagMembers( theAddr, \
                                     theResponse ) )

#define LAG_DltLag( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag,\
                        theRmvMembers ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltLag( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag, \
                                     theRmvMembers ) )

#endif
