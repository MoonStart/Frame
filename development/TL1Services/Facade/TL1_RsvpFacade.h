/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 RSVP Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RSVPFACADE_H__
#define __TL1_RSVPFACADE_H__

#ifndef __TL1_RSVPENTITY_H__
#include <TL1Core/TL1_RsvpEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EntRsvp( theAddr, theSignalCtlId, theInterfaceAid, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntRsvp( theAddr, theSignalCtlId, theInterfaceAid, theResponse  ) )
                                    
#define FACI_RtrvRsvp( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvRsvp( theAddr, theResponse ) )
                                      
#define FACI_DltRsvp( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltRsvp( theAddr, theResponse, theHandle, theCtag ) )

#define FACI_EntRsvpAdj( theAddr, theNgbrSignalAddr, theNgbrSignalId, theSetAlarm, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntRsvpAdj( theAddr, theNgbrSignalAddr, theNgbrSignalId,  theSetAlarm, thePst, theResponse  ) )

#define FACI_EdRsvpAdj( theAddr, theAlarmProfile, theClrAlarm, thePst, theResponse, theHandle ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdRsvpAdj( theAddr, theAlarmProfile, theClrAlarm, thePst, theResponse, theHandle  ) )
                                    
#define FACI_RtrvRsvpAdj( theAddr, theNetPart, thePst, theSst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvRsvpAdj( theAddr, theNetPart, thePst, theSst, theResponse ) )
                                      
#define FACI_DltRsvpAdj( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltRsvpAdj( theAddr, theResponse, theHandle, theCtag ) )
    
                                      
#endif
