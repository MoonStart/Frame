/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_S1Route      Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_S1ROUTE_C
#define TSXC_S1ROUTE_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_S1Route.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_S1Route::TSXC_S1Route()
{
    InitDst();
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_S1Route::~TSXC_S1Route()
{
}

//--------------------------------------------------------------------------------------------------
// Serialization Methods
//--------------------------------------------------------------------------------------------------

ostream& TSXC_S1Route::WriteObject( ostream& theStream )
{
    uint8  tmpDstCardType = myDstCardType;

    theStream<<FC_InsertVar(myMCastId[0]);
    theStream<<FC_InsertVar(myMCastId[1]);
    theStream<<FC_InsertVar(myDstShelf);
    theStream<<FC_InsertVar(myDstSlot);
    theStream<<FC_InsertVar(myDstSlice);   
    theStream<<FC_InsertVar(myConnId);
    theStream<<FC_InsertVar(tmpDstCardType);

    return theStream;
}

istream& TSXC_S1Route::ReadObject( istream& theStream )
{
    uint8 tmpDstCardType;

    theStream>>FC_ExtractVar(myMCastId[0]);
    theStream>>FC_ExtractVar(myMCastId[1]);
    theStream>>FC_ExtractVar(myDstShelf);
    theStream>>FC_ExtractVar(myDstSlot);
    theStream>>FC_ExtractVar(myDstSlice);
    theStream>>FC_ExtractVar(myConnId);
    theStream>>FC_ExtractVar(tmpDstCardType);

    myDstCardType = tmpDstCardType;

    return theStream;
}

FC_Stream& TSXC_S1Route::WriteObjectBinary( FC_Stream& theStream )
{
    uint8  tmpDstCardType = myDstCardType;

    theStream<<myMCastId[0];
    theStream<<myMCastId[1];
    theStream<<myDstShelf;
    theStream<<myDstSlot;
    theStream<<myDstSlice;
    theStream<<myConnId;
    theStream<<tmpDstCardType;

    return theStream;
}

FC_Stream& TSXC_S1Route::ReadObjectBinary( FC_Stream& theStream )
{
    uint8  tmpDstCardType;

    theStream>>myMCastId[0];
    theStream>>myMCastId[1];
    theStream>>myDstShelf;
    theStream>>myDstSlot;
    theStream>>myDstSlice;           
    theStream>>myConnId;
    theStream>>tmpDstCardType;

    myDstCardType = tmpDstCardType;

    return theStream;
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S1Route::operator==(const TSXC_S1Route& theRoute) const
{
    for (int i = 0; i < XC_MAX_MCASTID; i++)
    {
        if (myMCastId[i]  != theRoute.myMCastId[i])
            return false;
    }

    return  ( (myDstShelf     == theRoute.myDstShelf) && 
              (myDstSlot      == theRoute.myDstSlot)  &&
              (myDstSlice     == theRoute.myDstSlice) &&
              (myConnId       == theRoute.myConnId)   &&
              (myDstCardType  == theRoute.myDstCardType)   );
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S1Route::operator!=(const TSXC_S1Route& theRoute) const
{
    return (!(*this == theRoute));
}

//--------------------------------------------------------------------------------------------------
// Validate Methods
//--------------------------------------------------------------------------------------------------
bool TSXC_S1Route::IsDstSet() const
{        
    return (!(myMCastId[0] == XC_MCASTID_UNKNOWN && 
             myMCastId[1] == XC_MCASTID_UNKNOWN &&
             myDstShelf   == 0 && 
             myDstSlot    == 0));
}

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_S1Route::InitDst()
{
    for (int i = 0; i < XC_MAX_MCASTID; i++)
    {
        myMCastId[i] = XC_MCASTID_UNKNOWN;
    }
    myDstShelf = 0;
    myDstSlot  = 0;
    myDstSlice = 0;
    myConnId   = 0;
    myDstCardType = CARD_TYPE_UNKNOWN;
}

//--------------------------------------------------------------------------------------------------
void TSXC_S1Route::SetMCastId(uint16 theMCastId, CT_XC_ConnectMapping theMCastType)
{
    if ((theMCastType != CT_XC_MAPPING_FIXED) && (theMCastType != CT_XC_MAPPING_FLEXIBLE))
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S1Route::SetMCastId() CT_XC_ConnectMapping (%d) out of range\n", theMCastType);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    else
    {
        uint8 anIndex = (uint8)(theMCastType - 1);
        myMCastId[anIndex] = theMCastId;
    }
}

//--------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------
uint16 TSXC_S1Route::GetMCastId(CT_XC_ConnectMapping theMCastType) const
{
    uint16  retVal = XC_MCASTID_UNKNOWN;

    if ((theMCastType != CT_XC_MAPPING_FIXED) && (theMCastType != CT_XC_MAPPING_FLEXIBLE))
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S1Route::GetMCastId() CT_XC_ConnectMapping (%d) out of range\n", theMCastType);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    else
    {
        uint8 anIndex = (uint8)(theMCastType - 1);
        retVal = myMCastId[anIndex];
    }

    return retVal;
}

#endif // TSXC_S1ROUTE_C
