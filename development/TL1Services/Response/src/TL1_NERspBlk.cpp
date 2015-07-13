/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_NERspBlk.h>

const string TL1_NERspBlk::DefaultSID("TELLABS7100");

// Required for psos build
TL1_NERspBlk::TL1_NERspBlk() : mySubNodeCfg(UNKNOWN_SUBTYPE_CONFIG)
{
}

TL1_NERspBlk::TL1_NERspBlk(const string* EntityName, 
                  const CT_NodeConfiguration* NodeCfg,
                  const CT_NodeSubTypeConfiguration* SubNodeCfg, 
                  const CT_NodeReleaseConfiguration* HWVersion,
                  const CT_NodeSpanConfiguration* SpanA,
                  const CT_NodeSpanConfiguration* SpanB,
                  const string* Location,
                  const string* SystemID,
                  const string* Site,
                  const string* Version,
                  const string* Vendor,
                  const CT_TimeZone* TimeZone,
                  const bool* DSPMode,
                  const CT_NodeStsVcMode* StsVcMode,
                  const CT_ARCInterval* StsVcArcIntvHr,
                  const CT_ARCInterval* StsVcArcIntvMn,
                  const CT_SyncOsc* SyncOsc,
                  const uint8* defInterPacketGap,
                  const int* ctIntValueIntA,
                  const CT_DCM_FiberType* ctFiberTypeIntA,
                  const bool* ctLowLatencyIntA,
                  const int* ctIntValueIntB,
                  const CT_DCM_FiberType* ctFiberTypeIntB,
                  const bool* ctLowLatencyIntB,
                  const int* ctIntValueIntC,
                  const CT_DCM_FiberType* ctFiberTypeIntC,
                  const bool* ctLowLatencyIntC,
                  const int* ctIntValueIntD,
                  const CT_DCM_FiberType* ctFiberTypeIntD,
                  const bool* ctLowLatencyIntD,
                  const int* ctIntValueIntE,
                  const CT_DCM_FiberType* ctFiberTypeIntE,
                  const bool* ctLowLatencyIntE,
                  const int* ctIntValueIntF,
                  const CT_DCM_FiberType* ctFiberTypeIntF,
                  const bool* ctLowLatencyIntF,
                  const int* ctIntValueIntG,
                  const CT_DCM_FiberType* ctFiberTypeIntG,
                  const bool* ctLowLatencyIntG,
                  const int* ctIntValueIntH,
                  const CT_DCM_FiberType* ctFiberTypeIntH,
                  const bool* ctLowLatencyIntH,
                  const int* ctIntValueExtA,
                  const CT_DCM_FiberType* ctFiberTypeExtA,
                  const bool* ctLowLatencyExtA,
                  const int* ctIntValueExtB,
                  const CT_DCM_FiberType* ctFiberTypeExtB,
                  const bool* ctLowLatencyExtB,
                  const int* ctIntValueExtC,
                  const CT_DCM_FiberType* ctFiberTypeExtC,
                  const bool* ctLowLatencyExtC,
                  const int* ctIntValueExtD,
                  const CT_DCM_FiberType* ctFiberTypeExtD,
                  const bool* ctLowLatencyExtD,
                  const int* ctIntValueExtE,
                  const CT_DCM_FiberType* ctFiberTypeExtE,
                  const bool* ctLowLatencyExtE,
                  const int* ctIntValueExtF,
                  const CT_DCM_FiberType* ctFiberTypeExtF,
                  const bool* ctLowLatencyExtF,
                  const int* ctIntValueExtG,
                  const CT_DCM_FiberType* ctFiberTypeExtG,
                  const bool* ctLowLatencyExtG,
                  const int* ctIntValueExtH,
                  const CT_DCM_FiberType* ctFiberTypeExtH,
                  const bool* ctLowLatencyExtH,
                  const CT_ProfileTableId* SysAlmPf,
                  const CT_CPInit* CpInit,
                  const uint8* CpReady,
                  const CT_SM_PST* PST, 
                  const CT_SM_PSTQ* PSTQ, 
                  const CT_SM_SST* SST)
    : myBitSet( INDEX_END, false), mySubNodeCfg(UNKNOWN_SUBTYPE_CONFIG)
{
    if( EntityName )  
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( NodeCfg )  
    {
        myBitSet[ INDEX_NodeCfg ] = true;
        myNodeCfg = *NodeCfg;
    }

    if( SubNodeCfg)
    {
        myBitSet[ INDEX_SubNodeCfg ] = true;
        mySubNodeCfg = *SubNodeCfg;
    }

    if(HWVersion)
    {
        myBitSet[ INDEX_HWVersion ] = true;
        myHWVersion = *HWVersion;
    }

    if( SpanA)
    {
        myBitSet[ INDEX_SpanA ] = true;
        mySpanA = *SpanA;
    }
    
    if( SpanB)
    {
        myBitSet[ INDEX_SpanB ] = true;
        mySpanB = *SpanB;
    }
    
    if( Location)
    {
        myBitSet[ INDEX_Location ] = true;
        myLocation = *Location;
    }

    if( SystemID)
    {
        myBitSet[ INDEX_SystemID ] = true;
        mySystemID = *SystemID;
    }

    if( Site)
    {
        myBitSet[ INDEX_Site ] = true;
        mySite = *Site;
    }
    
    if(Version)
    {
        myBitSet[ INDEX_Version ] = true;
        myVersion = *Version;
    }

    if( Vendor)
    {
        myBitSet[ INDEX_Vendor ] = true;
        myVendor = *Vendor;
    }
    
    if( TimeZone)
    {
        myBitSet[ INDEX_TimeZone ] = true;
        myTimeZone = *TimeZone;
    }
    
    if( DSPMode)
    {
        myBitSet[ INDEX_DSPMode ] = true;
        myDSPMode = *DSPMode;
    }

    if( StsVcMode)
    {
        myBitSet[ INDEX_StsVcMode ] = true;
        myStsVcMode = *StsVcMode;
    }

    if( StsVcArcIntvHr)
    {
        myBitSet[ INDEX_StsVcArcIntvHr ] = true;
        myStsVcArcIntvHr = *StsVcArcIntvHr;
    }

    if( StsVcArcIntvMn)
    {
        myBitSet[ INDEX_StsVcArcIntvMn ] = true;
        myStsVcArcIntvMn = *StsVcArcIntvMn;
    }

    if( SyncOsc)
    {
        myBitSet[ INDEX_SyncOsc ] = true;
        mySyncOsc = *SyncOsc;
    }

    if( defInterPacketGap)
    {
        myBitSet[ INDEX_DefInterPacketGap ] = true;
        myDefInterPacketGap = *defInterPacketGap;
    }

    if( ctIntValueIntA)
    {
        myBitSet[ INDEX_IntValueIntA ] = true;
        myIntValueIntA = *ctIntValueIntA;
    }

    if( ctFiberTypeIntA)
    {
        myBitSet[ INDEX_FiberTypeIntA ] = true;
        myFiberTypeIntA = *ctFiberTypeIntA;
    }

    if ( ctLowLatencyIntA)
    {
        myBitSet[ INDEX_LowLatencyIntA ] = true;
        myLowLatencyIntA = *ctLowLatencyIntA;
    }

    if( ctIntValueIntB)
    {
        myBitSet[ INDEX_IntValueIntB ] = true;
        myIntValueIntB = *ctIntValueIntB;
    }

    if( ctFiberTypeIntB)
    {
        myBitSet[ INDEX_FiberTypeIntB ] = true;
        myFiberTypeIntB = *ctFiberTypeIntB;
    }

    if ( ctLowLatencyIntB)
    {
        myBitSet[ INDEX_LowLatencyIntB ] = true;
        myLowLatencyIntB = *ctLowLatencyIntB;
    }

    if( ctIntValueIntC)
    {
        myBitSet[ INDEX_IntValueIntC ] = true;
        myIntValueIntC = *ctIntValueIntC;
    }

    if( ctFiberTypeIntC)
    {
        myBitSet[ INDEX_FiberTypeIntC ] = true;
        myFiberTypeIntC = *ctFiberTypeIntC;
    }

    if ( ctLowLatencyIntC)
    {
        myBitSet[ INDEX_LowLatencyIntC ] = true;
        myLowLatencyIntC = *ctLowLatencyIntC;
    }

    if( ctIntValueIntD)
    {
        myBitSet[ INDEX_IntValueIntD ] = true;
        myIntValueIntD = *ctIntValueIntD;
    }

    if( ctFiberTypeIntD)
    {
        myBitSet[ INDEX_FiberTypeIntD ] = true;
        myFiberTypeIntD = *ctFiberTypeIntD;
    }

    if ( ctLowLatencyIntD)
    {
        myBitSet[ INDEX_LowLatencyIntD ] = true;
        myLowLatencyIntD = *ctLowLatencyIntD;
    }

    if( ctIntValueIntE)
    {
        myBitSet[ INDEX_IntValueIntE ] = true;
        myIntValueIntE = *ctIntValueIntE;
    }

    if( ctFiberTypeIntE)
    {
        myBitSet[ INDEX_FiberTypeIntE ] = true;
        myFiberTypeIntE = *ctFiberTypeIntE;
    }

    if ( ctLowLatencyIntE)
    {
        myBitSet[ INDEX_LowLatencyIntE ] = true;
        myLowLatencyIntE = *ctLowLatencyIntE;
    }

    if( ctIntValueIntF)
    {
        myBitSet[ INDEX_IntValueIntF ] = true;
        myIntValueIntF = *ctIntValueIntF;
    }

    if( ctFiberTypeIntF)
    {
        myBitSet[ INDEX_FiberTypeIntF ] = true;
        myFiberTypeIntF = *ctFiberTypeIntF;
    }

    if ( ctLowLatencyIntF)
    {
        myBitSet[ INDEX_LowLatencyIntF ] = true;
        myLowLatencyIntF = *ctLowLatencyIntF;
    }

    if( ctIntValueIntG)
    {
        myBitSet[ INDEX_IntValueIntG ] = true;
        myIntValueIntG = *ctIntValueIntG;
    }

    if( ctFiberTypeIntG)
    {
        myBitSet[ INDEX_FiberTypeIntG ] = true;
        myFiberTypeIntG = *ctFiberTypeIntG;
    }

    if ( ctLowLatencyIntG)
    {
        myBitSet[ INDEX_LowLatencyIntG ] = true;
        myLowLatencyIntG = *ctLowLatencyIntG;
    }

    if( ctIntValueIntH)
    {
        myBitSet[ INDEX_IntValueIntH ] = true;
        myIntValueIntH = *ctIntValueIntH;
    }

    if( ctFiberTypeIntH)
    {
        myBitSet[ INDEX_FiberTypeIntH ] = true;
        myFiberTypeIntH = *ctFiberTypeIntH;
    }

    if ( ctLowLatencyIntH)
    {
        myBitSet[ INDEX_LowLatencyIntH ] = true;
        myLowLatencyIntH = *ctLowLatencyIntH;
    }

    if( ctIntValueExtA)
    {
        myBitSet[ INDEX_IntValueExtA ] = true;
        myIntValueExtA = *ctIntValueExtA;
    }

    if( ctFiberTypeExtA)
    {
        myBitSet[ INDEX_FiberTypeExtA ] = true;
        myFiberTypeExtA = *ctFiberTypeExtA;
    }

    if ( ctLowLatencyExtA)
    {
        myBitSet[ INDEX_LowLatencyExtA ] = true;
        myLowLatencyExtA = *ctLowLatencyExtA;
    }

    if( ctIntValueExtB)
    {
        myBitSet[ INDEX_IntValueExtB ] = true;
        myIntValueExtB = *ctIntValueExtB;
    }

    if( ctFiberTypeExtB)
    {
        myBitSet[ INDEX_FiberTypeExtB ] = true;
        myFiberTypeExtB = *ctFiberTypeExtB;
    }

    if ( ctLowLatencyExtB)
    {
        myBitSet[ INDEX_LowLatencyExtB ] = true;
        myLowLatencyExtB = *ctLowLatencyExtB;
    }

    if( ctIntValueExtC)
    {
        myBitSet[ INDEX_IntValueExtC ] = true;
        myIntValueExtC = *ctIntValueExtC;
    }

    if( ctFiberTypeExtC)
    {
        myBitSet[ INDEX_FiberTypeExtC ] = true;
        myFiberTypeExtC = *ctFiberTypeExtC;
    }

    if ( ctLowLatencyExtC)
    {
        myBitSet[ INDEX_LowLatencyExtC ] = true;
        myLowLatencyExtC = *ctLowLatencyExtC;
    }

    if( ctIntValueExtD)
    {
        myBitSet[ INDEX_IntValueExtD ] = true;
        myIntValueExtD = *ctIntValueExtD;
    }

    if( ctFiberTypeExtD)
    {
        myBitSet[ INDEX_FiberTypeExtD ] = true;
        myFiberTypeExtD = *ctFiberTypeExtD;
    }

    if ( ctLowLatencyExtD)
    {
        myBitSet[ INDEX_LowLatencyExtD ] = true;
        myLowLatencyExtD = *ctLowLatencyExtD;
    }

    if( ctIntValueExtE)
    {
        myBitSet[ INDEX_IntValueExtE ] = true;
        myIntValueExtE = *ctIntValueExtE;
    }

    if( ctFiberTypeExtE)
    {
        myBitSet[ INDEX_FiberTypeExtE ] = true;
        myFiberTypeExtE = *ctFiberTypeExtE;
    }

    if ( ctLowLatencyExtE)
    {
        myBitSet[ INDEX_LowLatencyExtE ] = true;
        myLowLatencyExtE = *ctLowLatencyExtE;
    }

    if( ctIntValueExtF)
    {
        myBitSet[ INDEX_IntValueExtF ] = true;
        myIntValueExtF = *ctIntValueExtF;
    }

    if( ctFiberTypeExtF)
    {
        myBitSet[ INDEX_FiberTypeExtF ] = true;
        myFiberTypeExtF = *ctFiberTypeExtF;
    }

    if ( ctLowLatencyExtF)
    {
        myBitSet[ INDEX_LowLatencyExtF ] = true;
        myLowLatencyExtF = *ctLowLatencyExtF;
    }

    if( ctIntValueExtG)
    {
        myBitSet[ INDEX_IntValueExtG ] = true;
        myIntValueExtG = *ctIntValueExtG;
    }

    if( ctFiberTypeExtG)
    {
        myBitSet[ INDEX_FiberTypeExtG ] = true;
        myFiberTypeExtG = *ctFiberTypeExtG;
    }

    if ( ctLowLatencyExtG)
    {
        myBitSet[ INDEX_LowLatencyExtG ] = true;
        myLowLatencyExtG = *ctLowLatencyExtG;
    }

    if( ctIntValueExtH)
    {
        myBitSet[ INDEX_IntValueExtH ] = true;
        myIntValueExtH = *ctIntValueExtH;
    }

    if( ctFiberTypeExtH)
    {
        myBitSet[ INDEX_FiberTypeExtH ] = true;
        myFiberTypeExtH = *ctFiberTypeExtH;
    }

    if ( ctLowLatencyExtH)
    {
        myBitSet[ INDEX_LowLatencyExtH ] = true;
        myLowLatencyExtH = *ctLowLatencyExtH;
    }

    if( SysAlmPf)
    {
        myBitSet[ INDEX_SysAlmPf ] = true;
        mySysAlmPf = *SysAlmPf;
    }

    if  ( CpInit ) 
    {
        myBitSet [ INDEX_CpInit ] = true;
        myCpInit = *CpInit;
    }

    if ( CpReady )
    {
        myBitSet [ INDEX_CpReady ] = true;
        myCpReady = *CpReady;
    }

    if(PST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *PST;
    }

    if(PSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *PSTQ;
    }

    if(SST)
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *SST;
    }

}

TL1_NERspBlk::TL1_NERspBlk(const TL1_NERspBlk& neBlk)
    : myBitSet( neBlk.myBitSet), myEntityName( neBlk.myEntityName), myNodeCfg( neBlk.myNodeCfg),
      mySubNodeCfg( neBlk.mySubNodeCfg), myHWVersion(neBlk.myHWVersion),myLocation( neBlk.myLocation), 
      mySystemID( neBlk.mySystemID), mySite( neBlk.mySite), myVersion( neBlk.myVersion),
      myVendor( neBlk.myVendor), myTimeZone( neBlk.myTimeZone), myDSPMode( neBlk.myDSPMode),
      myStsVcMode( neBlk.myStsVcMode), myStsVcArcIntvHr( neBlk.myStsVcArcIntvHr), myStsVcArcIntvMn( neBlk.myStsVcArcIntvMn), 
      mySyncOsc( neBlk.mySyncOsc), myDefInterPacketGap( neBlk.myDefInterPacketGap),
      myIntValueIntA( neBlk.myIntValueIntA), myFiberTypeIntA(neBlk.myFiberTypeIntA), myLowLatencyIntA(neBlk.myLowLatencyIntA),
      myIntValueIntB( neBlk.myIntValueIntB), myFiberTypeIntB(neBlk.myFiberTypeIntB), myLowLatencyIntB(neBlk.myLowLatencyIntB),
      myIntValueIntC( neBlk.myIntValueIntC), myFiberTypeIntC(neBlk.myFiberTypeIntC), myLowLatencyIntC(neBlk.myLowLatencyIntC),
      myIntValueIntD( neBlk.myIntValueIntD), myFiberTypeIntD(neBlk.myFiberTypeIntD), myLowLatencyIntD(neBlk.myLowLatencyIntD),
      myIntValueIntE( neBlk.myIntValueIntE), myFiberTypeIntE(neBlk.myFiberTypeIntE), myLowLatencyIntE(neBlk.myLowLatencyIntE),
      myIntValueIntF( neBlk.myIntValueIntF), myFiberTypeIntF(neBlk.myFiberTypeIntF), myLowLatencyIntF(neBlk.myLowLatencyIntF),
      myIntValueIntG( neBlk.myIntValueIntG), myFiberTypeIntG(neBlk.myFiberTypeIntG), myLowLatencyIntG(neBlk.myLowLatencyIntG),
      myIntValueIntH( neBlk.myIntValueIntH), myFiberTypeIntH(neBlk.myFiberTypeIntH), myLowLatencyIntH(neBlk.myLowLatencyIntH),
      myIntValueExtA( neBlk.myIntValueExtA), myFiberTypeExtA(neBlk.myFiberTypeExtA), myLowLatencyExtA(neBlk.myLowLatencyExtA),
      myIntValueExtB( neBlk.myIntValueExtB), myFiberTypeExtB(neBlk.myFiberTypeExtB), myLowLatencyExtB(neBlk.myLowLatencyExtB),
      myIntValueExtC( neBlk.myIntValueExtC), myFiberTypeExtC(neBlk.myFiberTypeExtC), myLowLatencyExtC(neBlk.myLowLatencyExtC),
      myIntValueExtD( neBlk.myIntValueExtD), myFiberTypeExtD(neBlk.myFiberTypeExtD), myLowLatencyExtD(neBlk.myLowLatencyExtD),
      myIntValueExtE( neBlk.myIntValueExtE), myFiberTypeExtE(neBlk.myFiberTypeExtE), myLowLatencyExtE(neBlk.myLowLatencyExtE),
      myIntValueExtF( neBlk.myIntValueExtF), myFiberTypeExtF(neBlk.myFiberTypeExtF), myLowLatencyExtF(neBlk.myLowLatencyExtF),
      myIntValueExtG( neBlk.myIntValueExtG), myFiberTypeExtG(neBlk.myFiberTypeExtG), myLowLatencyExtG(neBlk.myLowLatencyExtG),
      myIntValueExtH( neBlk.myIntValueExtH), myFiberTypeExtH(neBlk.myFiberTypeExtH), myLowLatencyExtH(neBlk.myLowLatencyExtH),
      mySysAlmPf( neBlk.mySysAlmPf), myCpInit(neBlk.myCpInit), myCpReady(neBlk.myCpReady), myPST( neBlk.myPST), myPSTQ( neBlk.myPSTQ), 
      mySST( neBlk.mySST), mySpanA( neBlk.mySpanA), mySpanB( neBlk.mySpanB)
{
}

TL1_NERspBlk::~TL1_NERspBlk()
{
}

TL1_NERspBlk& TL1_NERspBlk::operator=( const TL1_NERspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myNodeCfg = theBlock.myNodeCfg;
    mySubNodeCfg = theBlock.mySubNodeCfg;
    myHWVersion = theBlock.myHWVersion;
    myLocation = theBlock.myLocation;    
    mySystemID = theBlock.mySystemID;
    mySite = theBlock.mySite; 
    myVersion = theBlock.myVersion;
    myVendor = theBlock.myVendor;
    myTimeZone = theBlock.myTimeZone;
    myDSPMode = theBlock.myDSPMode;
    myStsVcMode = theBlock.myStsVcMode;
    myStsVcArcIntvHr = theBlock.myStsVcArcIntvHr;
    myStsVcArcIntvMn = theBlock.myStsVcArcIntvMn;
    mySyncOsc = theBlock.mySyncOsc;
    myDefInterPacketGap = theBlock.myDefInterPacketGap;
    myIntValueIntA = theBlock.myIntValueIntA;
    myFiberTypeIntA = theBlock.myFiberTypeIntA;
    myLowLatencyIntA = theBlock.myLowLatencyIntA;
    myIntValueIntB = theBlock.myIntValueIntB;
    myFiberTypeIntB = theBlock.myFiberTypeIntB;
    myLowLatencyIntB = theBlock.myLowLatencyIntB;
    myIntValueIntC = theBlock.myIntValueIntC;
    myFiberTypeIntC = theBlock.myFiberTypeIntC;
    myLowLatencyIntC = theBlock.myLowLatencyIntC;
    myIntValueIntD = theBlock.myIntValueIntD;
    myFiberTypeIntD = theBlock.myFiberTypeIntD;
    myLowLatencyIntD = theBlock.myLowLatencyIntD;
    myIntValueIntE = theBlock.myIntValueIntE;
    myFiberTypeIntE = theBlock.myFiberTypeIntE;
    myLowLatencyIntE = theBlock.myLowLatencyIntE;
    myIntValueIntF = theBlock.myIntValueIntF;
    myFiberTypeIntF = theBlock.myFiberTypeIntF;
    myLowLatencyIntF = theBlock.myLowLatencyIntF;
    myIntValueIntG = theBlock.myIntValueIntG;
    myFiberTypeIntG = theBlock.myFiberTypeIntG;
    myLowLatencyIntG = theBlock.myLowLatencyIntG;
    myIntValueIntH = theBlock.myIntValueIntH;
    myFiberTypeIntH = theBlock.myFiberTypeIntH;
    myLowLatencyIntH = theBlock.myLowLatencyIntH;
    myIntValueExtA = theBlock.myIntValueExtA;
    myFiberTypeExtA = theBlock.myFiberTypeExtA;
    myLowLatencyExtA = theBlock.myLowLatencyExtA;
    myIntValueExtB = theBlock.myIntValueExtB;
    myFiberTypeExtB = theBlock.myFiberTypeExtB;
    myLowLatencyExtB = theBlock.myLowLatencyExtB;
    myIntValueExtC = theBlock.myIntValueExtC;
    myFiberTypeExtC = theBlock.myFiberTypeExtC;
    myLowLatencyExtC = theBlock.myLowLatencyExtC;
    myIntValueExtD = theBlock.myIntValueExtD;
    myFiberTypeExtD = theBlock.myFiberTypeExtD;
    myLowLatencyExtD = theBlock.myLowLatencyExtD;
    myIntValueExtE = theBlock.myIntValueExtE;
    myFiberTypeExtE = theBlock.myFiberTypeExtE;
    myLowLatencyExtE = theBlock.myLowLatencyExtE;
    myIntValueExtF = theBlock.myIntValueExtF;
    myFiberTypeExtF = theBlock.myFiberTypeExtF;
    myLowLatencyExtF = theBlock.myLowLatencyExtF;
    myIntValueExtG = theBlock.myIntValueExtG;
    myFiberTypeExtG = theBlock.myFiberTypeExtG;
    myLowLatencyExtG = theBlock.myLowLatencyExtG;
    myIntValueExtH = theBlock.myIntValueExtH;
    myFiberTypeExtH = theBlock.myFiberTypeExtH;
    myLowLatencyExtH = theBlock.myLowLatencyExtH;
    mySysAlmPf = theBlock.mySysAlmPf;
    myCpInit = theBlock.myCpInit;
    myCpReady = theBlock.myCpReady;
    myPST = theBlock.myPST;
    myPSTQ = theBlock.myPSTQ;
    mySST = theBlock.mySST;
    mySpanA = theBlock.mySpanA;
    mySpanB = theBlock.mySpanB;

    return *this;
}

bool TL1_NERspBlk::operator==( const TL1_NERspBlk& theBlock ) const
{
    return ( myBitSet == theBlock.myBitSet &&
             myEntityName == theBlock.myEntityName &&
             myNodeCfg == theBlock.myNodeCfg &&
             mySubNodeCfg == theBlock.mySubNodeCfg &&
             myHWVersion == theBlock.myHWVersion &&
             myLocation == theBlock.myLocation &&   
             mySystemID == theBlock.mySystemID && 
             mySite == theBlock.mySite &&
             myVersion == theBlock.myVersion &&
             myVendor == theBlock.myVendor &&
             myTimeZone == theBlock.myTimeZone &&
             myDSPMode == theBlock.myDSPMode &&
             myStsVcMode == theBlock.myStsVcMode &&
             myStsVcArcIntvHr == theBlock.myStsVcArcIntvHr &&
             myStsVcArcIntvMn == theBlock.myStsVcArcIntvMn &&
             mySyncOsc == theBlock.mySyncOsc &&
             myDefInterPacketGap == theBlock.myDefInterPacketGap &&
             myIntValueIntA == theBlock.myIntValueIntA &&
             myFiberTypeIntA == theBlock.myFiberTypeIntA &&
             myLowLatencyIntA == theBlock.myLowLatencyIntA &&
             myIntValueIntB == theBlock.myIntValueIntB &&
             myFiberTypeIntB == theBlock.myFiberTypeIntB &&
             myLowLatencyIntB == theBlock.myLowLatencyIntB &&
             myIntValueIntC == theBlock.myIntValueIntC &&
             myFiberTypeIntC == theBlock.myFiberTypeIntC &&
             myLowLatencyIntC == theBlock.myLowLatencyIntC &&
             myIntValueIntD == theBlock.myIntValueIntD &&
             myFiberTypeIntD == theBlock.myFiberTypeIntD &&
             myLowLatencyIntD == theBlock.myLowLatencyIntD &&
             myIntValueIntE == theBlock.myIntValueIntE &&
             myFiberTypeIntE == theBlock.myFiberTypeIntE &&
             myLowLatencyIntE == theBlock.myLowLatencyIntE &&
             myIntValueIntF == theBlock.myIntValueIntF &&
             myFiberTypeIntF == theBlock.myFiberTypeIntF &&
             myLowLatencyIntF == theBlock.myLowLatencyIntF &&
             myIntValueIntG == theBlock.myIntValueIntG &&
             myFiberTypeIntG == theBlock.myFiberTypeIntG &&
             myLowLatencyIntG == theBlock.myLowLatencyIntG &&
             myIntValueIntH == theBlock.myIntValueIntH &&
             myFiberTypeIntH == theBlock.myFiberTypeIntH &&
             myLowLatencyIntH == theBlock.myLowLatencyIntH &&
             myIntValueExtA == theBlock.myIntValueExtA &&
             myFiberTypeExtA == theBlock.myFiberTypeExtA &&
             myLowLatencyExtA == theBlock.myLowLatencyExtA &&
             myIntValueExtB == theBlock.myIntValueExtB &&
             myFiberTypeExtB == theBlock.myFiberTypeExtB &&
             myLowLatencyExtB == theBlock.myLowLatencyExtB &&
             myIntValueExtC == theBlock.myIntValueExtC &&
             myFiberTypeExtC == theBlock.myFiberTypeExtC &&
             myLowLatencyExtC == theBlock.myLowLatencyExtC &&
             myIntValueExtD == theBlock.myIntValueExtD &&
             myFiberTypeExtD == theBlock.myFiberTypeExtD &&
             myLowLatencyExtD == theBlock.myLowLatencyExtD &&
             myIntValueExtE == theBlock.myIntValueExtE &&
             myFiberTypeExtE == theBlock.myFiberTypeExtE &&
             myLowLatencyExtE == theBlock.myLowLatencyExtE &&
             myIntValueExtF == theBlock.myIntValueExtF &&
             myFiberTypeExtF == theBlock.myFiberTypeExtF &&
             myLowLatencyExtF == theBlock.myLowLatencyExtF &&
             myIntValueExtG == theBlock.myIntValueExtG &&
             myFiberTypeExtG == theBlock.myFiberTypeExtG &&
             myLowLatencyExtG == theBlock.myLowLatencyExtG &&
             myIntValueExtH == theBlock.myIntValueExtH &&
             myFiberTypeExtH == theBlock.myFiberTypeExtH &&  
             myLowLatencyExtH == theBlock.myLowLatencyExtH &&           
             mySysAlmPf == theBlock.mySysAlmPf &&
             myCpInit == theBlock.myCpInit &&
             myCpReady == theBlock.myCpReady &&
             myPST == theBlock.myPST &&
             myPSTQ == theBlock.myPSTQ &&
             mySST == theBlock.mySST &&
             mySpanA == theBlock.mySpanA &&
             mySpanB == theBlock.mySpanB );
}

// Definition for GetEntityName()
bool TL1_NERspBlk::GetEntityName( string& entityName) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
	{
    	entityName = myEntityName;
		return true;
	}
	else
	{
		return false;
	}
}


// Definition for GetNodeCfg()
bool TL1_NERspBlk::GetNodeCfg( CT_NodeConfiguration& NodeCfg) const
{
    if( true == myBitSet[ INDEX_NodeCfg ] )
	{
   	    NodeCfg = myNodeCfg;
	    return true;
	}
	else
	{
		return false;
	}
}

bool TL1_NERspBlk::GetSubNodeCfg( CT_NodeSubTypeConfiguration& SubNodeCfg) const 
{
    if( true == myBitSet[ INDEX_SubNodeCfg ] )
    {
        SubNodeCfg = mySubNodeCfg;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLocation( string& Location) const 
{
    if( true == myBitSet[ INDEX_Location ] )
    {
        Location = myLocation;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSystemID( string& SystemID) const 
{
    if( true == myBitSet[ INDEX_SystemID ] )
    {
        SystemID = mySystemID;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSite( string& Site) const 
{
    if( true == myBitSet[ INDEX_Site ] )
    {
        Site = mySite;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetVersion( string& Version) const
{
    if( true == myBitSet[ INDEX_Version ] )
    {
        Version = myVersion;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetVendor( string& Vendor) const 
{
    if( true == myBitSet[ INDEX_Vendor ] )
    {
        Vendor = myVendor;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetTimeZone( CT_TimeZone& TimeZone) const 
{
    if( true == myBitSet[ INDEX_TimeZone ] )
    {
        TimeZone = myTimeZone;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetDSPMode( bool& DSPMode) const 
{
    if( true == myBitSet[ INDEX_DSPMode ] )
    {
        DSPMode = myDSPMode;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetStsVcMode(CT_NodeStsVcMode& StsVcMode) const
{
    if( true == myBitSet[ INDEX_StsVcMode ] )
    {
        StsVcMode = myStsVcMode;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetStsVcArcIntvHr(CT_ARCInterval& StsVcArcIntvHr) const
{
    if( true == myBitSet[ INDEX_StsVcArcIntvHr ] )
    {
        StsVcArcIntvHr = myStsVcArcIntvHr;
        return true;
    }
    else
    {
        return false;
    }
}
 
bool TL1_NERspBlk::GetStsVcArcIntvMn(CT_ARCInterval& StsVcArcIntvMn) const
{
    if( true == myBitSet[ INDEX_StsVcArcIntvMn ] )
    {
        StsVcArcIntvMn = myStsVcArcIntvMn;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSyncOsc(CT_SyncOsc& SyncOsc) const
{
    if( true == myBitSet[ INDEX_SyncOsc ] )
    {
        SyncOsc = mySyncOsc;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetDefInterPacketGap(uint8& defInterPacketGap) const
{
    if( true == myBitSet[ INDEX_DefInterPacketGap] )
    {
        defInterPacketGap = myDefInterPacketGap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntA( int& IntValueIntA) const 
{
    if( true == myBitSet[ INDEX_IntValueIntA ] )
    {
        IntValueIntA = myIntValueIntA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntA( CT_DCM_FiberType& FiberTypeIntA) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntA ] )
    {
        FiberTypeIntA = myFiberTypeIntA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntA( bool& LowLatencyIntA) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntA ] )
    {
        LowLatencyIntA = myLowLatencyIntA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntB( int& IntValueIntB) const 
{
    if( true == myBitSet[ INDEX_IntValueIntB ] )
    {
        IntValueIntB = myIntValueIntB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntB( CT_DCM_FiberType& FiberTypeIntB) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntB ] )
    {
        FiberTypeIntB = myFiberTypeIntB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntB( bool& LowLatencyIntB) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntB ] )
    {
        LowLatencyIntB = myLowLatencyIntB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntC( int& IntValueIntC) const 
{
    if( true == myBitSet[ INDEX_IntValueIntC ] )
    {
        IntValueIntC = myIntValueIntC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntC( CT_DCM_FiberType& FiberTypeIntC) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntC ] )
    {
        FiberTypeIntC = myFiberTypeIntC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntC( bool& LowLatencyIntC) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntC ] )
    {
        LowLatencyIntC = myLowLatencyIntC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntD( int& IntValueIntD) const 
{
    if( true == myBitSet[ INDEX_IntValueIntD ] )
    {
        IntValueIntD = myIntValueIntD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntD( CT_DCM_FiberType& FiberTypeIntD) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntD ] )
    {
        FiberTypeIntD = myFiberTypeIntD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntD( bool& LowLatencyIntD) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntD ] )
    {
        LowLatencyIntD = myLowLatencyIntD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntE( int& IntValueIntE) const 
{
    if( true == myBitSet[ INDEX_IntValueIntE ] )
    {
        IntValueIntE = myIntValueIntE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntE( CT_DCM_FiberType& FiberTypeIntE) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntE ] )
    {
        FiberTypeIntE = myFiberTypeIntE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntE( bool& LowLatencyIntE) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntE ] )
    {
        LowLatencyIntE = myLowLatencyIntE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntF( int& IntValueIntF) const 
{
    if( true == myBitSet[ INDEX_IntValueIntF ] )
    {
        IntValueIntF = myIntValueIntF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntF( CT_DCM_FiberType& FiberTypeIntF) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntF ] )
    {
        FiberTypeIntF = myFiberTypeIntF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntF( bool& LowLatencyIntF) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntF ] )
    {
        LowLatencyIntF = myLowLatencyIntF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntG( int& IntValueIntG) const 
{
    if( true == myBitSet[ INDEX_IntValueIntG ] )
    {
        IntValueIntG = myIntValueIntG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntG( CT_DCM_FiberType& FiberTypeIntG) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntG ] )
    {
        FiberTypeIntG = myFiberTypeIntG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntG( bool& LowLatencyIntG) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntG ] )
    {
        LowLatencyIntG = myLowLatencyIntG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueIntH( int& IntValueIntH) const 
{
    if( true == myBitSet[ INDEX_IntValueIntH ] )
    {
        IntValueIntH = myIntValueIntH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeIntH( CT_DCM_FiberType& FiberTypeIntH) const 
{
    if( true == myBitSet[ INDEX_FiberTypeIntH ] )
    {
        FiberTypeIntH = myFiberTypeIntH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyIntH( bool& LowLatencyIntH) const 
{
    if( true == myBitSet[ INDEX_LowLatencyIntH ] )
    {
        LowLatencyIntH = myLowLatencyIntH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtA( int& IntValueExtA) const 
{
    if( true == myBitSet[ INDEX_IntValueExtA ] )
    {
        IntValueExtA = myIntValueExtA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtA( CT_DCM_FiberType& FiberTypeExtA) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtA ] )
    {
        FiberTypeExtA = myFiberTypeExtA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtA( bool& LowLatencyExtA) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtA ] )
    {
        LowLatencyExtA = myLowLatencyExtA;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtB( int& IntValueExtB) const 
{
    if( true == myBitSet[ INDEX_IntValueExtB ] )
    {
        IntValueExtB = myIntValueExtB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtB( CT_DCM_FiberType& FiberTypeExtB) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtB ] )
    {
        FiberTypeExtB = myFiberTypeExtB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtB( bool& LowLatencyExtB) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtB ] )
    {
        LowLatencyExtB = myLowLatencyExtB;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtC( int& IntValueExtC) const 
{
    if( true == myBitSet[ INDEX_IntValueExtC ] )
    {
        IntValueExtC = myIntValueExtC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtC( CT_DCM_FiberType& FiberTypeExtC) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtC ] )
    {
        FiberTypeExtC = myFiberTypeExtC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtC( bool& LowLatencyExtC) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtC ] )
    {
        LowLatencyExtC = myLowLatencyExtC;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtD( int& IntValueExtD) const 
{
    if( true == myBitSet[ INDEX_IntValueExtD ] )
    {
        IntValueExtD = myIntValueExtD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtD( CT_DCM_FiberType& FiberTypeExtD) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtD ] )
    {
        FiberTypeExtD = myFiberTypeExtD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtD( bool& LowLatencyExtD) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtD ] )
    {
        LowLatencyExtD = myLowLatencyExtD;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtE( int& IntValueExtE) const 
{
    if( true == myBitSet[ INDEX_IntValueExtE ] )
    {
        IntValueExtE = myIntValueExtE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtE( CT_DCM_FiberType& FiberTypeExtE) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtE ] )
    {
        FiberTypeExtE = myFiberTypeExtE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtE( bool& LowLatencyExtE) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtE ] )
    {
        LowLatencyExtE = myLowLatencyExtE;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtF( int& IntValueExtF) const 
{
    if( true == myBitSet[ INDEX_IntValueExtF ] )
    {
        IntValueExtF = myIntValueExtF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtF( CT_DCM_FiberType& FiberTypeExtF) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtF ] )
    {
        FiberTypeExtF = myFiberTypeExtF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtF( bool& LowLatencyExtF) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtF ] )
    {
        LowLatencyExtF = myLowLatencyExtF;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtG( int& IntValueExtG) const 
{
    if( true == myBitSet[ INDEX_IntValueExtG ] )
    {
        IntValueExtG = myIntValueExtG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtG( CT_DCM_FiberType& FiberTypeExtG) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtG ] )
    {
        FiberTypeExtG = myFiberTypeExtG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtG( bool& LowLatencyExtG) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtG ] )
    {
        LowLatencyExtG = myLowLatencyExtG;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetIntValueExtH( int& IntValueExtH) const 
{
    if( true == myBitSet[ INDEX_IntValueExtH ] )
    {
        IntValueExtH = myIntValueExtH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetFiberTypeExtH( CT_DCM_FiberType& FiberTypeExtH) const 
{
    if( true == myBitSet[ INDEX_FiberTypeExtH ] )
    {
        FiberTypeExtH = myFiberTypeExtH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetLowLatencyExtH( bool& LowLatencyExtH) const 
{
    if( true == myBitSet[ INDEX_LowLatencyExtH ] )
    {
        LowLatencyExtH = myLowLatencyExtH;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSysAlmPf( CT_ProfileTableId& SysAlmPf) const 
{
    if( true == myBitSet[ INDEX_SysAlmPf ] )
    {
        SysAlmPf = mySysAlmPf;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetHWVersion( CT_NodeReleaseConfiguration& HWVersion) const 
{
    if( true == myBitSet[ INDEX_HWVersion ] )
    {
        HWVersion = myHWVersion;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetCpInit( CT_CPInit& CpInit) const 
{
    if( true == myBitSet[ INDEX_CpInit ] )
    {
        CpInit = myCpInit;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetCpReady( uint8& CpReady) const 
{
    if( true == myBitSet[ INDEX_CpReady ] )
    {
        CpReady = myCpReady;  
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetPST( CT_SM_PST& PST) const 
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        PST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetPSTQ( CT_SM_PSTQ& PSTQ) const 
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        PSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSST( CT_SM_SST& SST) const 
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        SST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_NERspBlk::GetSpanA( CT_NodeSpanConfiguration& SpanA) const 
{
    if( true == myBitSet[ INDEX_SpanA ] )
    {
        SpanA = mySpanA;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_NERspBlk::GetSpanB( CT_NodeSpanConfiguration& SpanB) const 
{
    if( true == myBitSet[ INDEX_SpanB ] )
    {
        SpanB = mySpanB;
        return true;
    }
    else
    {
        return false;
    }
}


