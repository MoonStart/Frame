/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         2013.9.16 - Gang Zhu	
DESCRIPTION:    Header file for TL1 MGTETH Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MGTETHFACADE_H__
#define __TL1_MGTETHFACADE_H__

#ifndef __TL1_MGTETHDOMAIN_H__
#include <TL1Core/TL1_MgtETHDomain.h>
#endif

#ifndef __TL1_MGTETHENTITY_H__
#include <TL1Core/TL1_MgtETHEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define MGTETH_EntMgtETH( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntMgtETH( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define MGTETH_EdMgtETH( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdMgtETH( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define MGTETH_RtrvMgtETH( \
                        theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvMgtETH( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ) )
                                      
#define MGTETH_DltMgtETH( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltMgtETH( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )

#endif
