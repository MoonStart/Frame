/*--------------------------------------------------------------.0---------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 cross-connection Response 
TARGET:
AUTHOR:         Mar 14, 2008- Brian Clever
DESCRIPTION:    Source file for TL1 Retrive EVC Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_EvcRspBlk.h>


//For RTRV-EVC
TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                             const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<bool>& theRedlined,
                             const TL1_SmartParameter<bool>& isAllFrame,
                             const TL1_SmartParameter<VlanTag_List>& theCVidList,
                             const TL1_SmartParameter<VlanTag_List>& theSVidList,
                             const TL1_SmartParameter<CT_TEL_VlanTag>& theSVid,
                             const TL1_SmartParameter<int>& theBwpfCOS0,
                             const TL1_SmartParameter<bool>& theDiscPause,
                             const TL1_SmartParameter<CT_TEL_PbitRegen>& thePbitRegen,
                             const TL1_SmartParameter<bool> theAisState,
                             const TL1_SmartParameter<int>  theAisInterval,
                             const TL1_SmartParameter<int>  theAisMegLevel,
                             const TL1_SmartParameter<CT_TEL_MacMode> theDestMacMode,
                             const TL1_SmartParameter<bool>& theLoopbackState,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST,
							 const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile) :
    itsEvcId(theEvcId),
    itsAddr(theAddr),
    itsCircuitId(theCircuitId),
    itsRedline(theRedlined),
    itsAllFrame(isAllFrame),
    itsCVidList(theCVidList),
    itsSVidList(theSVidList),
    itsSVid(theSVid),
    itsBwpfCOS0(theBwpfCOS0),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST),
    itsDiscPause(theDiscPause),
    itsPbitRegen(thePbitRegen),
    itsAisState(theAisState),
    itsAisInterval(theAisInterval),
    itsAisMegLevel(theAisMegLevel),
    itsDestMacMode(theDestMacMode),
    itsLoopbackState(theLoopbackState),
	itsAlarmProfile(theAlarmProfile)
{
    VlanTag_List emptyList;
    itsAddCVidList = emptyList;
    itsAddSVidList = emptyList;
    itsRmvCVidList= emptyList;
    itsRmvSVidList= emptyList;
}

//For EVC DBCHG with ADD/RMV VlanTag List
TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                             const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<bool>& theRedlined,
                             const TL1_SmartParameter<bool>& isAllFrame,
                             const TL1_SmartParameter<VlanTag_List>& theCVidList,
                             const TL1_SmartParameter<VlanTag_List>& theSVidList,
                             const TL1_SmartParameter<VlanTag_List>& theAddCVidList,
                             const TL1_SmartParameter<VlanTag_List>& theAddSVidList,
                             const TL1_SmartParameter<VlanTag_List>& theRmvCVidList,
                             const TL1_SmartParameter<VlanTag_List>& theRmvSVidList,
                             const TL1_SmartParameter<CT_TEL_VlanTag>& theSVid,
                             const TL1_SmartParameter<int>& theBwpfCOS0,
                             const TL1_SmartParameter<bool>& theDiscPause,
                             const TL1_SmartParameter<CT_TEL_PbitRegen>& thePbitRegen,
                             const TL1_SmartParameter<bool> theAisState,
                             const TL1_SmartParameter<int>  theAisInterval,
                             const TL1_SmartParameter<int>  theAisMegLevel,
                             const TL1_SmartParameter<CT_TEL_MacMode> theDestMacMode,
                             const TL1_SmartParameter<bool>& theLoopbackState,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST,
                             const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile) :
    itsEvcId(theEvcId),
    itsAddr(theAddr),
    itsCircuitId(theCircuitId),
    itsRedline(theRedlined),
    itsAllFrame(isAllFrame),
    itsCVidList(theCVidList),
    itsSVidList(theSVidList),
    itsAddCVidList(theAddCVidList),
    itsAddSVidList(theAddSVidList),
    itsRmvCVidList(theRmvCVidList),
    itsRmvSVidList(theRmvSVidList),
    itsSVid(theSVid),
    itsBwpfCOS0(theBwpfCOS0),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST),
    itsDiscPause(theDiscPause),
    itsPbitRegen(thePbitRegen),
    itsAisState(theAisState),
    itsAisInterval(theAisInterval),
    itsAisMegLevel(theAisMegLevel),
    itsDestMacMode(theDestMacMode),
    itsLoopbackState(theLoopbackState),
    itsAlarmProfile(theAlarmProfile)
{
}

TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                             const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<int>&  theNpOwner,
                             const TL1_SmartParameter<bool>& theQua,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsEvcId(theEvcId),
    itsAddr(theAddr),
    itsCircuitId(theCircuitId),
    itsNpOwner(theNpOwner),
    itsQua(theQua),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsEvcId(theEvcId),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                             const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                             const TL1_SmartParameter<string>& theCircuitId) :
    itsEvcId(theEvcId),
    itsAddr(theAddr),
    itsCircuitId(theCircuitId)
{
}

TL1_EvcRspBlk::~TL1_EvcRspBlk()
{
}
  
TL1_EvcRspBlk::TL1_EvcRspBlk(const TL1_EvcRspBlk& theBlock) :
    itsEvcId(theBlock.itsEvcId),
    itsAddr(theBlock.itsAddr),
    itsCircuitId(theBlock.itsCircuitId),
    itsRedline(theBlock.itsRedline),
    itsNpOwner(theBlock.itsNpOwner),
    itsQua(theBlock.itsQua),
    itsAllFrame(theBlock.itsAllFrame),
    itsCVidList(theBlock.itsCVidList),
    itsSVidList(theBlock.itsSVidList),
    itsAddCVidList(theBlock.itsAddCVidList),
    itsAddSVidList(theBlock.itsAddSVidList),
    itsRmvCVidList(theBlock.itsRmvCVidList),
    itsRmvSVidList(theBlock.itsRmvSVidList),
    itsSVid(theBlock.itsSVid),
    itsBwpfCOS0(theBlock.itsBwpfCOS0),
    itsPST(theBlock.itsPST),
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST),
    itsDiscPause(theBlock.itsDiscPause),
    itsPbitRegen(theBlock.itsPbitRegen),
    itsAisState(theBlock.itsAisState),
    itsAisInterval(theBlock.itsAisInterval),
    itsAisMegLevel(theBlock.itsAisMegLevel),
    itsDestMacMode(theBlock.itsDestMacMode),
    itsLoopbackState(theBlock.itsLoopbackState),
    itsAlarmProfile(theBlock.itsAlarmProfile)
{
}

TL1_EvcRspBlk& TL1_EvcRspBlk::operator=( const TL1_EvcRspBlk& theBlock )
{
    itsEvcId=           theBlock.itsEvcId;
    itsAddr=            theBlock.itsAddr;
    itsCircuitId=       theBlock.itsCircuitId;
    itsRedline=         theBlock.itsRedline;
    itsNpOwner=         theBlock.itsNpOwner;
    itsQua=             theBlock.itsQua;
    itsAllFrame=        theBlock.itsAllFrame;
    itsCVidList=        theBlock.itsCVidList;
    itsSVidList=        theBlock.itsSVidList;
    itsAddCVidList=     theBlock.itsAddCVidList;
    itsAddSVidList=     theBlock.itsAddSVidList;
    itsRmvCVidList=     theBlock.itsRmvCVidList;
    itsRmvSVidList=     theBlock.itsRmvSVidList;
    itsSVid=            theBlock.itsSVid;
    itsBwpfCOS0=        theBlock.itsBwpfCOS0;
    itsPST=             theBlock.itsPST;
    itsPSTQ=            theBlock.itsPSTQ;
    itsSST=             theBlock.itsSST;
    itsDiscPause=       theBlock.itsDiscPause;
    itsPbitRegen=       theBlock.itsPbitRegen;
    itsAisState=        theBlock.itsAisState;
    itsAisInterval=     theBlock.itsAisInterval;
    itsAisMegLevel=     theBlock.itsAisMegLevel;
    itsDestMacMode=     theBlock.itsDestMacMode;
    itsLoopbackState=   theBlock.itsLoopbackState;
    itsAlarmProfile=    theBlock.itsAlarmProfile;

    return *this;
}

bool TL1_EvcRspBlk::operator==( const TL1_EvcRspBlk& theBlock ) const
{
    return ( itsEvcId           == theBlock.itsEvcId &&
             itsAddr            == theBlock.itsAddr &&
             itsCircuitId       == theBlock.itsCircuitId &&
             itsRedline         == theBlock.itsRedline &&
             itsNpOwner         == theBlock.itsNpOwner &&
             itsQua             == theBlock.itsQua &&
             itsAllFrame        == theBlock.itsAllFrame &&
             itsCVidList        == theBlock.itsCVidList &&
             itsSVidList        == theBlock.itsSVidList &&
             itsAddCVidList     == theBlock.itsAddCVidList &&
             itsAddSVidList     == theBlock.itsAddSVidList &&
             itsRmvCVidList     == theBlock.itsRmvCVidList &&
             itsRmvSVidList     == theBlock.itsRmvSVidList &&
             itsSVid            == theBlock.itsSVid &&
             itsBwpfCOS0        == theBlock.itsBwpfCOS0 &&
             itsPST             == theBlock.itsPST &&
             itsPSTQ            == theBlock.itsPSTQ &&
             itsSST             == theBlock.itsSST &&
             itsDiscPause       == theBlock.itsDiscPause &&
             itsPbitRegen       == theBlock.itsPbitRegen &&
             itsAisState        == theBlock.itsAisState &&
             itsAisInterval     == theBlock.itsAisInterval &&
             itsAisMegLevel     == theBlock.itsAisMegLevel &&
             itsDestMacMode     == theBlock.itsDestMacMode &&
             itsLoopbackState   == theBlock.itsLoopbackState &&
             itsAlarmProfile    == theBlock.itsAlarmProfile);

}
