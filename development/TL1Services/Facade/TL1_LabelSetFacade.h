/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 LABELSET Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LABELSETFACADE_H__
#define __TL1_LABELSETFACADE_H__

#ifndef __TL1_LABELSETDOMAIN_H__
#include <TL1Core/TL1_LabelSetDomain.h>
#endif

#ifndef __TL1_LABELSETENTITY_H__
#include <TL1Core/TL1_LabelSetEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EntLabelSet( \
                        theLabelSetNum, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntLabelSet( \
                                    theLabelSetNum, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_EdLabelSet( \
                        theLabelSetNum, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLabelSet( \
                                    theLabelSetNum, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_DltLabelSet( \
                        theLabelSetNum, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltLabelSet( \
                                    theLabelSetNum, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_RtrvLabelSet( \
                        theLabelSetNum, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLabelSet( \
                                    theLabelSetNum, \
                                    theParameters, \
                                    theResponse  ) )

#endif
