/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Path Trace Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Path Trace Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_PTHRspBlk.h>

TL1_PTHRspBlk:: TL1_PTHRspBlk(){;}

TL1_PTHRspBlk:: TL1_PTHRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_Fac_TraceString* ExpectedTrace,
                  const CT_Fac_TraceString* IncomingTrace,
                  const CT_Fac_TraceString* Trace,
                  const CT_Fac_TraceString* RxSapi,
                  const CT_Fac_TraceString* RxDapi,
                  const CT_Fac_TraceString* RxOper,
                  const CT_Fac_TraceString* ExpDapi,
                  const CT_Fac_TraceString* ExpSapi,
                  const CT_Fac_TraceString* TxDapi,
                  const CT_Fac_TraceString* TxSapi,
                  const CT_Fac_TraceString* ExpOper,
                  const CT_Fac_TraceString* TxOper)
    : myBitSet( INDEX_END, false )
{
    if( EntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( FacAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *FacAddr;
    }

    if(ExpectedTrace)
    {
        myBitSet[ INDEX_ExpectedTrace ] = true;
        myExpectedTrace = *ExpectedTrace;
    }

    if(IncomingTrace)
    {
        myBitSet[ INDEX_IncomingTrace ] = true;
        myIncomingTrace = *IncomingTrace;
    }

    if(Trace)
    {
        myBitSet[ INDEX_Trace ] = true;
        myTrace = *Trace;
    }

    if(RxSapi)
    {
        myBitSet[ INDEX_RxSapi ] = true;
        myRxSapi = *RxSapi;
    }

    if(RxDapi)
    {
        myBitSet[ INDEX_RxDapi ] = true;
        myRxDapi = *RxDapi;
    }

    if(RxOper)
    {
        myBitSet[ INDEX_RxOper ] = true;
        myRxOper = *RxOper;
    }

    if(ExpDapi)
    {
        myBitSet[ INDEX_ExpDapi ] = true;
        myExpDapi = *ExpDapi;
    }
    
    if(ExpSapi)
    {
        myBitSet[ INDEX_ExpSapi ] = true;
        myExpSapi = *ExpSapi;
    }
    
    if(TxDapi)
    {
        myBitSet[ INDEX_TxDapi ] = true;
        myTxDapi = *TxDapi;
    } 

    if(TxSapi)
    {
        myBitSet[ INDEX_TxSapi ] = true;
        myTxSapi = *TxSapi;
    }

    if(ExpOper)
    {
        myBitSet[ INDEX_ExpOper ] = true;
        myExpOper = *ExpOper;
    } 

    if(TxOper)
    {
        myBitSet[ INDEX_TxOper ] = true;
        myTxOper = *TxOper;
    }
   
}

TL1_PTHRspBlk::TL1_PTHRspBlk(const TL1_PTHRspBlk& attnBlk)
    : myBitSet( attnBlk.myBitSet), myEntityName( attnBlk.myEntityName),
      myFacAddr( attnBlk.myFacAddr), myExpectedTrace( attnBlk.myExpectedTrace),
      myIncomingTrace( attnBlk.myIncomingTrace), myTrace( attnBlk.myTrace),myRxSapi(attnBlk.myRxSapi),
      myRxDapi(attnBlk.myRxDapi),myRxOper(attnBlk.myRxOper),myExpDapi(attnBlk.myExpDapi), 
      myExpSapi(attnBlk.myExpSapi), myTxDapi(attnBlk.myTxDapi), myTxSapi(attnBlk.myTxSapi),
      myExpOper(attnBlk.myExpOper), myTxOper(attnBlk.myTxOper)
{
}

TL1_PTHRspBlk::~TL1_PTHRspBlk()
{
}

TL1_PTHRspBlk& TL1_PTHRspBlk::operator=( const TL1_PTHRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myExpectedTrace = theBlock.myExpectedTrace;
    myIncomingTrace = theBlock.myIncomingTrace;
    myTrace = theBlock.myTrace;
    myRxSapi = theBlock.myRxSapi;
    myRxDapi = theBlock.myRxDapi;
    myRxOper = theBlock.myRxOper;
    myExpDapi = theBlock.myExpDapi;
    myExpSapi = theBlock.myExpSapi;
    myTxDapi = theBlock.myTxDapi;
    myTxSapi = theBlock.myTxSapi;
    myExpOper = theBlock.myExpOper;
    myTxOper = theBlock.myTxOper;
    
    return *this;
}

bool TL1_PTHRspBlk::GetEntityName(string &EntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        EntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        FacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetExpectedTrace(CT_Fac_TraceString& ExpectedTrace ) const
{
    if( true == myBitSet[ INDEX_ExpectedTrace ] )
    {
        ExpectedTrace = myExpectedTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetIncomingTrace(CT_Fac_TraceString& IncomingTrace) const
{
    if( true == myBitSet[ INDEX_IncomingTrace ] )
    {
        IncomingTrace = myIncomingTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetTrace( CT_Fac_TraceString &Trace) const
{
    if( true == myBitSet[ INDEX_Trace ] )
    {
        Trace = myTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetRxSapi( CT_Fac_TraceString &RxSapi) const
{
    if( true == myBitSet[ INDEX_RxSapi ] )
    {
        RxSapi = myRxSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetRxDapi( CT_Fac_TraceString &RxDapi) const
{
    if( true == myBitSet[ INDEX_RxDapi ] )
    {
        RxDapi = myRxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetRxOper( CT_Fac_TraceString &RxOper) const
{
    if( true == myBitSet[ INDEX_RxOper ] )
    {
        RxOper = myRxOper;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetExpDapi( CT_Fac_TraceString &ExpDapi) const
{
    if( true == myBitSet[ INDEX_ExpDapi ] )
    {
        ExpDapi = myExpDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetExpSapi( CT_Fac_TraceString &ExpSapi) const
{
    if( true == myBitSet[ INDEX_ExpSapi ] )
    {
        ExpSapi = myExpSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetTxDapi( CT_Fac_TraceString &TxDapi) const
{
    if( true == myBitSet[ INDEX_TxDapi ] )
    {
        TxDapi = myTxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetTxSapi( CT_Fac_TraceString &TxSapi) const
{
    if( true == myBitSet[ INDEX_TxSapi ] )
    {
        TxSapi = myTxSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetExpOper( CT_Fac_TraceString &ExpOper) const
{
    if( true == myBitSet[ INDEX_ExpOper ] )
    {
        ExpOper = myExpOper;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHRspBlk::GetTxOper( CT_Fac_TraceString &TxOper) const
{
    if( true == myBitSet[ INDEX_TxOper ] )
    {
        TxOper = myTxOper;
        return true;
    }
    else
    {
        return false;
    }
}

TL1_PTHOtsRspBlk:: TL1_PTHOtsRspBlk(){;}

TL1_PTHOtsRspBlk:: TL1_PTHOtsRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_Fac_TraceString* ExpectedTrace,
                  const CT_Fac_TraceString* IncomingTrace,
                  const CT_Fac_TraceString* Trace)
    : myBitSet( INDEX_END, false )
{
    if( EntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( FacAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *FacAddr;
    }

    if(ExpectedTrace)
    {
        myBitSet[ INDEX_ExpectedTrace ] = true;
        myExpectedTrace = *ExpectedTrace;
    }

    if(IncomingTrace)
    {
        myBitSet[ INDEX_IncomingTrace ] = true;
        myIncomingTrace = *IncomingTrace;
    }

    if(Trace)
    {
        myBitSet[ INDEX_Trace ] = true;
        myTrace = *Trace;
    }
}

TL1_PTHOtsRspBlk::TL1_PTHOtsRspBlk(const TL1_PTHOtsRspBlk& attnBlk)
    : myBitSet( attnBlk.myBitSet), myEntityName( attnBlk.myEntityName),
      myFacAddr( attnBlk.myFacAddr), myExpectedTrace( attnBlk.myExpectedTrace),
      myIncomingTrace( attnBlk.myIncomingTrace), myTrace( attnBlk.myTrace)
{
}

TL1_PTHOtsRspBlk::~TL1_PTHOtsRspBlk()
{
}

TL1_PTHOtsRspBlk& TL1_PTHOtsRspBlk::operator=( const TL1_PTHOtsRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myExpectedTrace = theBlock.myExpectedTrace;
    myIncomingTrace = theBlock.myIncomingTrace;
    myTrace = theBlock.myTrace;
    
    return *this;
}

bool TL1_PTHOtsRspBlk::GetEntityName(string &EntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        EntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtsRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        FacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtsRspBlk::GetExpectedTrace(CT_Fac_TraceString& ExpectedTrace ) const
{
    if( true == myBitSet[ INDEX_ExpectedTrace ] )
    {
        ExpectedTrace = myExpectedTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtsRspBlk::GetIncomingTrace(CT_Fac_TraceString& IncomingTrace) const
{
    if( true == myBitSet[ INDEX_IncomingTrace ] )
    {
        IncomingTrace = myIncomingTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtsRspBlk::GetTrace( CT_Fac_TraceString &Trace) const
{
    if( true == myBitSet[ INDEX_Trace ] )
    {
        Trace = myTrace;
        return true;
    }
    else
    {
        return false;
    }
}

TL1_PTHOtuOduRspBlk:: TL1_PTHOtuOduRspBlk(){;}

TL1_PTHOtuOduRspBlk:: TL1_PTHOtuOduRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_Fac_TraceString* ExpectedTrace,
                  const CT_Fac_TraceString* Trace,
                  const CT_Fac_TraceString* RxSapi,
                  const CT_Fac_TraceString* RxDapi,
                  const CT_Fac_TraceString* RxOper,
                  const CT_Fac_TraceString* ExpDapi,
                  const CT_Fac_TraceString* ExpSapi,
                  const CT_Fac_TraceString* TxDapi,
                  const CT_Fac_TraceString* TxSapi)
    : myBitSet( INDEX_END, false )
{
    if( EntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( FacAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *FacAddr;
    }

    if(ExpectedTrace)
    {
        myBitSet[ INDEX_ExpectedTrace ] = true;
        myExpectedTrace = *ExpectedTrace;
    }

    if(Trace)
    {
        myBitSet[ INDEX_Trace ] = true;
        myTrace = *Trace;
    }

    if(RxSapi)
    {
        myBitSet[ INDEX_RxSapi ] = true;
        myRxSapi = *RxSapi;
    }

    if(RxDapi)
    {
        myBitSet[ INDEX_RxDapi ] = true;
        myRxDapi = *RxDapi;
    }

    if(RxOper)
    {
        myBitSet[ INDEX_RxOper ] = true;
        myRxOper = *RxOper;
    }

    if(ExpDapi)
    {
        myBitSet[ INDEX_ExpDapi ] = true;
        myExpDapi = *ExpDapi;
    }
    
    if(ExpSapi)
    {
        myBitSet[ INDEX_ExpSapi ] = true;
        myExpSapi = *ExpSapi;
    }
    
    if(TxDapi)
    {
        myBitSet[ INDEX_TxDapi ] = true;
        myTxDapi = *TxDapi;
    } 

    if(TxSapi)
    {
        myBitSet[ INDEX_TxSapi ] = true;
        myTxSapi = *TxSapi;
    }
   
}

TL1_PTHOtuOduRspBlk::TL1_PTHOtuOduRspBlk(const TL1_PTHOtuOduRspBlk& attnBlk)
    : myBitSet( attnBlk.myBitSet), myEntityName( attnBlk.myEntityName),
      myFacAddr( attnBlk.myFacAddr), myExpectedTrace( attnBlk.myExpectedTrace),
      myTrace( attnBlk.myTrace),myRxSapi(attnBlk.myRxSapi),myRxDapi(attnBlk.myRxDapi),myRxOper(attnBlk.myRxOper),
      myExpDapi(attnBlk.myExpDapi), myExpSapi(attnBlk.myExpSapi), myTxDapi(attnBlk.myTxDapi), myTxSapi(attnBlk.myTxSapi)
{
}

TL1_PTHOtuOduRspBlk::~TL1_PTHOtuOduRspBlk()
{
}

TL1_PTHOtuOduRspBlk& TL1_PTHOtuOduRspBlk::operator=( const TL1_PTHOtuOduRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myExpectedTrace = theBlock.myExpectedTrace;
    myTrace = theBlock.myTrace;
    myRxSapi = theBlock.myRxSapi;
    myRxDapi = theBlock.myRxDapi;
    myRxOper = theBlock.myRxOper;
    myExpDapi = theBlock.myExpDapi;
    myExpSapi = theBlock.myExpSapi;
    myTxDapi = theBlock.myTxDapi;
    myTxSapi = theBlock.myTxSapi;
    
    return *this;
}

bool TL1_PTHOtuOduRspBlk::GetEntityName(string &EntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        EntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        FacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetExpectedTrace(CT_Fac_TraceString& ExpectedTrace ) const
{
    if( true == myBitSet[ INDEX_ExpectedTrace ] )
    {
        ExpectedTrace = myExpectedTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetTrace( CT_Fac_TraceString &Trace) const
{
    if( true == myBitSet[ INDEX_Trace ] )
    {
        Trace = myTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetRxSapi( CT_Fac_TraceString &RxSapi) const
{
    if( true == myBitSet[ INDEX_RxSapi ] )
    {
        RxSapi = myRxSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetRxDapi( CT_Fac_TraceString &RxDapi) const
{
    if( true == myBitSet[ INDEX_RxDapi ] )
    {
        RxDapi = myRxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetRxOper( CT_Fac_TraceString &RxOper) const
{
    if( true == myBitSet[ INDEX_RxOper ] )
    {
        RxOper = myRxOper;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetExpDapi( CT_Fac_TraceString &ExpDapi) const
{
    if( true == myBitSet[ INDEX_ExpDapi ] )
    {
        ExpDapi = myExpDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetExpSapi( CT_Fac_TraceString &ExpSapi) const
{
    if( true == myBitSet[ INDEX_ExpSapi ] )
    {
        ExpSapi = myExpSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetTxDapi( CT_Fac_TraceString &TxDapi) const
{
    if( true == myBitSet[ INDEX_TxDapi ] )
    {
        TxDapi = myTxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PTHOtuOduRspBlk::GetTxSapi( CT_Fac_TraceString &TxSapi) const
{
    if( true == myBitSet[ INDEX_TxSapi ] )
    {
        TxSapi = myTxSapi;
        return true;
    }
    else
    {
        return false;
    }
}
