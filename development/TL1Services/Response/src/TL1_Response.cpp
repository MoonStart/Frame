/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_Response.h>
#include <string.h>

TL1_Response::TL1_Response() :
    myEC(CT_TL1_ErrorIndex::EC_NO_ERROR),
    myER(CT_TL1_ErrorIndex::ER_NO_ERROR)
{
    myNbOfErrorRsp = 0;
    myIgnoreStatus = false;
    myHandle = 0;
    for (int i = 0; i < 20; ++i)
    {
        myCtag[i] = '\0';
    }
}

void TL1_Response::SetError( const CT_TL1_ErrorIndex::EC_Index& EC, const CT_TL1_ErrorIndex::ER_Index& ER)
{
    myEC = EC;
    myER = ER;
}

void TL1_Response::AddResponseBlock( const TL1_GeneralRspBlk &)
{
    // Throw ??????
}

void TL1_Response::SetCtag(LT_Ctag theCtag)
{
    strcpy(myCtag, theCtag);
}
