/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_S3Route      Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_S3ROUTE_C
#define TSXC_S3ROUTE_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_S3Route.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_S3Route::TSXC_S3Route()
{
    InitSrc();      
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_S3Route::~TSXC_S3Route()
{
}

//--------------------------------------------------------------------------------------------------
// Serialization Methods
//--------------------------------------------------------------------------------------------------

ostream& TSXC_S3Route::WriteObject( ostream& theStream )
{
    uint8                 srcNum;

    for(srcNum = 0; srcNum < XC_MAX_SRC_ENDPT; srcNum++)
    {
        theStream<<FC_InsertVar(mySource[srcNum].Shelf);
        theStream<<FC_InsertVar(mySource[srcNum].Slot);
        theStream<<FC_InsertVar(mySource[srcNum].Channel);
        theStream<<FC_InsertVar(mySource[srcNum].ConnId);
    }

    return theStream;
}

istream& TSXC_S3Route::ReadObject( istream& theStream )
{
    uint8                 srcNum;

    for(srcNum = 0; srcNum < XC_MAX_SRC_ENDPT; srcNum++)
    {
        theStream>>FC_ExtractVar(mySource[srcNum].Shelf);
        theStream>>FC_ExtractVar(mySource[srcNum].Slot);
        theStream>>FC_ExtractVar(mySource[srcNum].Channel);
        theStream>>FC_ExtractVar(mySource[srcNum].ConnId);
    }
    
    return theStream;
}

FC_Stream& TSXC_S3Route::WriteObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        theStream<<mySource[i].Shelf;
        theStream<<mySource[i].Slot;
        theStream<<mySource[i].Channel;
        theStream<<mySource[i].ConnId;
    }
    
    return theStream;
}

FC_Stream& TSXC_S3Route::ReadObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        theStream>>mySource[i].Shelf;
        theStream>>mySource[i].Slot;
        theStream>>mySource[i].Channel;
        theStream>>mySource[i].ConnId;
    }
    return theStream;
}

//--------------------------------------------------------------------------------------------------
void TSXC_S3Route::PrintEgressImux(uint16 egress_imux_chan)
{
    FC_FmtFlags previousFlags;

    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);

    fc_cout.Width(15);
    fc_cout << static_cast<int>(egress_imux_chan+1);
    fc_cout.Width(6);
    fc_cout << (int) GetNumSrc();
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        if (IsSrcSet(i))
        {
            fc_cout.Width(6);
            fc_cout << static_cast<int>(GetSrcSlot(i));
            fc_cout.Width(6);
            fc_cout << static_cast<int>(GetSrcFacilityEndpoint(i));
            fc_cout.Width(6);
            fc_cout << static_cast<int>(GetSrcConnId(i));
        }
    }
    fc_cout << endl;

    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S3Route::operator==(const TSXC_S3Route& theRoute) const
{
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        if (mySource[i]  != theRoute.mySource[i])
            return false;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S3Route::operator!=(const TSXC_S3Route& theRoute) const
{
    return (!(*this == theRoute));
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S3Route::IsSrcSet( uint8 idx ) const
{
        
    if (idx >= XC_MAX_SRC_ENDPT)
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S3Route::IsSrcSet() Index (%d) out of range\n", idx);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    
    return !(mySource[idx].IsEmpty()); 
}

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_S3Route::InitSrc()
{
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        mySource[i].Init();
    }
}
//--------------------------------------------------------------------------------------------------
uint16 TSXC_S3Route::GetSrcFacilityEndpoint(uint8 idx) const
{
    uint16  aSrcEndpt = 0xFFFF;

    if (idx >= XC_MAX_SRC_ENDPT)
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S3Route::GetSrcFacilityEndpoint() Index (%d) out of range\n", idx);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    else
    {
        aSrcEndpt = mySource[idx].Channel;
    }

    return aSrcEndpt;
}

//--------------------------------------------------------------------------------------------------
uint8 TSXC_S3Route::GetSrcSlot(uint8 idx) const
{
    uint8   aSrcSlot = 0xFF;

    if (idx >= XC_MAX_SRC_ENDPT)
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S3Route::GetSrcSlot() Index (%d) out of range\n", idx);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    else
    {
        aSrcSlot = mySource[idx].Slot;
    }

    return aSrcSlot;
}

//--------------------------------------------------------------------------------------------------
uint8 TSXC_S3Route::GetSrcShelf(uint8 idx) const
{
    uint8   aSrcShelf = 0xFF;

    if (idx >= XC_MAX_SRC_ENDPT)
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S3Route::GetSrcShelf() Index (%d) out of range\n", idx);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }
    else
    {
        aSrcShelf = mySource[idx].Shelf;
    }

    return aSrcShelf;
}

//--------------------------------------------------------------------------------------------------
uint16 TSXC_S3Route::GetSrcConnId(uint8 idx) const
{
    uint16   aSrcConnId = 0xFFFF;

    if (idx >= XC_MAX_SRC_ENDPT)
    {
        char ErrorMsg[80];
        sprintf(ErrorMsg, "TSXC_S3Route::GetConnId() Index (%d) out of range\n", idx);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    } 
    else
    {
        aSrcConnId = mySource[idx].ConnId;
    }

    return aSrcConnId;
}

//--------------------------------------------------------------------------------------------------
uint8  TSXC_S3Route::GetNumSrc() const
{
    uint8   aNumSrc =0;
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        if (!(mySource[i].IsEmpty()))
             aNumSrc++;
    }
    return  aNumSrc;    
} 
//--------------------------------------------------------------------------------------------------
bool TSXC_S3Route::AddSrc( uint16 theEndpoint, uint8 theSlot, uint8 theShelf, uint16 theConnId)
{
    class TSXC_SOURCE aSrc;

    aSrc.Shelf   = theShelf;
    aSrc.Slot    = theSlot;
    aSrc.Channel = theEndpoint;
    aSrc.ConnId  = theConnId;

    bool    isAddOkay  = true;
    bool    aAddStatus = false;

    //--- Make sure that we are not duplicating 
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        if (mySource[i] == aSrc)
        {
            isAddOkay = false;
            aAddStatus = true; 
        }
    }
    
    if (isAddOkay)
    {
        //--- find an empty spot and place it
        for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
        {
            if (mySource[i].IsEmpty())
            {
                mySource[i] = aSrc;
                aAddStatus = true;
                break;
            }
        }        
    }    
    return aAddStatus;
}

//--------------------------------------------------------------------------------------------------
void TSXC_S3Route::RmvSrc( uint16 theEndpoint, uint8 theSlot, uint8 theShelf, uint16 theConnId)
{
    class TSXC_SOURCE aSrc;

    aSrc.Shelf = theShelf;
    aSrc.Slot  = theSlot;
    aSrc.Channel = theEndpoint;
    aSrc.ConnId  = theConnId;
    
    for (int i = 0; i < XC_MAX_SRC_ENDPT; i++)
    {
        if (mySource[i] == aSrc)
        {
            mySource[i].Init();
            break; 
        }
    }        
}
//--------------------------------------------------------------------------------------------------
#endif // TSXC_S3ROUTE_C
