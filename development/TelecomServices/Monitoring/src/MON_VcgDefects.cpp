// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_VcgDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_VcgDefects::MON_VcgDefects(uint32 theIndex):
    MON_HopDefects(theIndex)
{
}

MON_VcgDefects::~MON_VcgDefects()
{
}

// All other methods inherited from Hop Layer
