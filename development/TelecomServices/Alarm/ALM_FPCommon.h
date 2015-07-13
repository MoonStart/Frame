/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Signal Alarm 
TARGET:         All cards
AUTHOR:         Marc Vendette
DESCRIPTION:    Common definitions for Signal Alarm
-----------------------------------------------------------------------------*/ 

#ifndef ALM_COMMON_H
#define ALM_COMMON_H


#include <gdef.h>

//----------------
// Type definition
//----------------

//Definition of failure number.
//##ModelId=3C506C3302CF
typedef int ALM_FailureNb;

//Definition of defect number.
//##ModelId=3C506C330365
typedef int ALM_DefectNb;

//Index number definition.
//##ModelId=3C506C340013
typedef int ALM_IndexNb;

//Bit fiels definition. Usualy used to concatenate defects/failures status from 
//booleen to bitfield. The number of bit depends on the definition. It can be 8, 
//16 or 32 bits.
//##ModelId=3C506C3401CC
typedef uint16 ALM_BitField;


#endif // ALM_COMMON_H




