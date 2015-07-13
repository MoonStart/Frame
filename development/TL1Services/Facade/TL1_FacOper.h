/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 24, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 Fac Oper 
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACOPER_H__
#define __TL1_FACOPER_H__

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#ifndef __CT_TL1_ERROR_H__
#include <CommonTypes/CT_TL1_Error.h>
#endif

#define TL1FAC_OPER(RET,FAC_TYPE,INSTANCE_ID,CONSTANT_METHOD)\
{ \
	try \
	{\
        GetFacadeOperObj<FAC_TYPE> aFacadeOperObj =  GetFacadeOperObj<FAC_TYPE>(); \
    	RET InitFacadeObj(INSTANCE_ID,CONSTANT_METHOD ; \
	}\
	catch (FC_InvalidArgumentError)\
	{\
		throw CT_TL1_IICMError(CT_TL1_IICMError::ER_IICM_INV);\
	}\
}

#endif
