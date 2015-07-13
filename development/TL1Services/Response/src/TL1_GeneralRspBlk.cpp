/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response Base Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Response base class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif
#include <Response/TL1_GeneralRspBlk.h>

TL1_GeneralRspBlk::~TL1_GeneralRspBlk()
{;}

TL1_GeneralRspBlk::TL1_GeneralRspBlk() :
    myEC(CT_TL1_ErrorIndex::EC_NO_ERROR),
    myER(CT_TL1_ErrorIndex::ER_NO_ERROR)
{
}

void TL1_GeneralRspBlk::SetError( const CT_TL1_ErrorIndex::EC_Index& EC, const CT_TL1_ErrorIndex::ER_Index& ER)
{
    myEC = EC;
    myER = ER;
}

bool TL1_GeneralRspBlk::operator==( const TL1_GeneralRspBlk& theBlock ) const
{
    return false;
}
    
