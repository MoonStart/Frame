/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:
AUTHOR:         July 25, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 VCG Profile Facade declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_VCGFACADE_H__
#define __TL1_VCGFACADE_H__

#ifndef __TL1_VCGDOMAIN_H__
#include <TL1Core/TL1_VcgDomain.h>
#endif

#ifndef __TL1_VCGENTITY_H__
#include <TL1Core/TL1_VcgEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define VCG_EntVcg( \
                        theVcgAddr, \
                        theIsAutoMode, \
                        theVcatType, \
                        theAlarmProfile, \
                        theCCPath, \
                        thePlcThr, \
                        theTlcThr, \
                        theHoTmr, \
                        theWtrTmr, \
                        theNValue, \
                        thePVid, \
                        theTagMode, \
                        theTPid, \
                        theProt, \
                        theLcas, \
                        thePrimaryState, \
                        myHandle, \
                        myCtag, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntVcg( theVcgAddr, \
                                     theIsAutoMode, \
                                     theVcatType, \
                                     theAlarmProfile, \
                                     theCCPath, \
                                     thePlcThr, \
                                     theTlcThr, \
                                     theHoTmr, \
                                     theWtrTmr, \
                                     theNValue, \
                                     thePVid, \
                                     theTagMode, \
                                     theTPid, \
                                     theProt, \
                                     theLcas, \
                                     thePrimaryState, \
                                     myHandle, \
                                     myCtag, \
                                     theResponse  ) )

#define VCG_EdVcg( \
                        theAddr, \
                        theAlarmProfile, \
                        thePlcThr, \
                        theTlcThr, \
                        theHoTmr, \
                        theWtrTmr, \
                        theNValue, \
                        theAddTtp, \
                        theRmvTtp, \
                        theTtpFacType, \
                        theAddCrs, \
                        theRmvCrs, \
                        theCrsFacType, \
                        theCCT, \
                        thePVid, \
                        theTagMode, \
                        theTPid, \
                        theProt, \
                        theLcas, \
                        theAddStsMap, \
                        theRmvStsMap, \
                        thePrimaryState, \
                        theIsCommandForced, \
                        theHandle, \
                        theCtag, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdVcg( \
                                    theAddr, \
                                    theAlarmProfile, \
                                    thePlcThr, \
                                    theTlcThr, \
                                    theHoTmr, \
                                    theWtrTmr, \
                                    theNValue, \
                                    theAddTtp, \
                                    theRmvTtp, \
                                    theTtpFacType, \
                                    theAddCrs, \
                                    theRmvCrs, \
                                    theCrsFacType, \
                                    theCCT, \
                                    thePVid, \
                                    theTagMode, \
                                    theTPid, \
                                    theProt, \
                                    theLcas, \
                                    theAddStsMap, \
                                    theRmvStsMap, \
                                    thePrimaryState, \
                                    theIsCommandForced, \
                                    theHandle, \
                                    theCtag, \
                                    theResponse ) )

#define VCG_RtrvVcg( \
                        theAddr, \
                        theAlarmProfile, \
                        theMember, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvVcg( theAddr, \
                                      theAlarmProfile, \
                                      theMember, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ) )

#define VCG_RtrvVcgMembers( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvVcgMembers( theAddr, \
                                      theResponse ) )

#define VCG_DltVcg( \
                        theAddr, \
                        theRmvMembers, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltVcg( theAddr, \
                                     theRmvMembers, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )

#endif
