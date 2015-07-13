/*--------------------------------------------------------------.0---------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Protection Response 
TARGET:
AUTHOR:         April 12, 2004- Maggie Zhang
DESCRIPTION:    Source file for TL1 Retrive Protection Group Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_ProtnRspBlk.h>


TL1_ProtnRspBlk::TL1_ProtnRspBlk( const CT_TL1_ProtnAddr*   theAddr,
                                  const CT_ProtGpType*      theType,
                                  const bool*               theRtrtv,
                                  const int*                theWtr, // includes from_cp_aid and to_cp_aid
                                  const int*                theProtHoldOffTime,
                                  const CT_ProtGpType*      theProtectType,
                                  const bool*               theCPFlag,
                                  const int*                theNpOwner,
                                  const CT_SM_PST*          thePST,
                                  const CT_SM_PSTQ*         thePSTQ,
                                  const CT_SM_SST*          theSST) :
    itsType(PROT_GP_UNKNOWN ),
       itsBiSwitching(false),
    itsProtnRequest(CT_ProtnRequest_NR),
	itsRtrtv(false),
	itsWtr(0),
	itsProtHoldOffTime(0),
    itsProtectType(0),
    itsCPFlag(false),
    itsNpOwner(0),
	itsPST(0),
	itsPSTQ(0),
	itsSST(0),
	itsBitSet(INDEX_END,false)
{

	if(theAddr)
	{
		itsBitSet[INDEX_Addr] = true;
		itsAddr = *theAddr;
	}

	if(theType)
	{
		itsBitSet[INDEX_Type] = true;
		itsType = *theType;
	}

	if(theRtrtv)
	{
		itsBitSet[INDEX_Rtrtv] = true;
		itsRtrtv = *theRtrtv;
	}

	if(theWtr)
	{
		itsBitSet[INDEX_Wtr] = true;
		itsWtr = *theWtr;
	}

	if(theProtHoldOffTime)
	{
        CT_FacilitySubType theWorkType = itsAddr.GetWorkFacType();

        if(theWorkType == FAC_SUBTYPE_GBEP    || 
		   theWorkType == FAC_SUBTYPE_GOPT_W  ||
		   theWorkType == FAC_SUBTYPE_GOPT_P  ||
           theWorkType == FAC_SUBTYPE_STS1    ||
           theWorkType == FAC_SUBTYPE_STS3C   ||
           theWorkType == FAC_SUBTYPE_STS12C  ||
           theWorkType == FAC_SUBTYPE_STS48C  ||
           theWorkType == FAC_SUBTYPE_STS1CNV ||
           theWorkType == FAC_SUBTYPE_STS3CNV ||
		   theWorkType == FAC_SUBTYPE_ODU0    ||
           theWorkType == FAC_SUBTYPE_ODU1    ||
           theWorkType == FAC_SUBTYPE_ODUF    ||
           theWorkType == FAC_SUBTYPE_ODU2    ||
           theWorkType == FAC_SUBTYPE_ODU2E   ||
           theWorkType == FAC_SUBTYPE_ODU3    ||
           theWorkType == FAC_SUBTYPE_ODU4    ||
           theWorkType == FAC_SUBTYPE_OCH_P)
        {
			itsBitSet[INDEX_ProtHoldTime] = true;
			itsProtHoldOffTime = *theProtHoldOffTime;
        }
        else if (itsType == PROT_GP_YCABLE)
        {
			itsBitSet[INDEX_ProtHoldTime] = true;
			itsProtHoldOffTime = *theProtHoldOffTime;
        }
        else // (FFP group other than GBEP or GOPT)
        {
			itsBitSet[INDEX_ProtHoldTime] = false;
        }
	}

	if(theProtectType)
	{
		itsBitSet[INDEX_ProtectType] = true;
		itsProtectType = *theProtectType;
	}

	if(theCPFlag)
	{
		itsBitSet[INDEX_CPFlag] = true;
		itsCPFlag = *theCPFlag;
	}

    if(theNpOwner)
    {
        itsBitSet[INDEX_NpOwner] = true;
        itsNpOwner = *theNpOwner;
    }

	if(thePST)
    {
		itsBitSet[ INDEX_PST ] = true;
        itsPST = *thePST;
    }

    if(thePSTQ)
    {
		itsBitSet[ INDEX_PSTQ ] = true;
        itsPSTQ = *thePSTQ;
    }

    if(theSST)
    {
		itsBitSet[ INDEX_SST ] = true;
        itsSST = *theSST;
    }


}

TL1_ProtnRspBlk::~TL1_ProtnRspBlk()
{
}

void TL1_ProtnRspBlk::Reset()
{
	itsPST = CT_SM_PST_OOS;
	itsPSTQ = CT_SM_PSTQ_DNE;
	itsSST = CT_SM_SST_NOREQUEST;
}

TL1_ProtnRspBlk::TL1_ProtnRspBlk(const TL1_ProtnRspBlk& theBlock) :
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST)
{
	itsBitSet           = theBlock.itsBitSet;
	itsAddr             = theBlock.itsAddr;
	itsType             = theBlock.itsType;
        itsBiSwitching      = theBlock.itsBiSwitching;
        itsProtnRequest     = theBlock.itsProtnRequest;
	itsRtrtv            = theBlock.itsRtrtv;
	itsWtr              = theBlock.itsWtr;
	itsProtHoldOffTime  = theBlock.itsProtHoldOffTime;
    itsProtectType      = theBlock.itsProtectType;
    itsCPFlag           = theBlock.itsCPFlag;
    itsNpOwner          = theBlock.itsNpOwner;
	itsPST              = theBlock.itsPST;
}

TL1_ProtnRspBlk& TL1_ProtnRspBlk::operator=( const TL1_ProtnRspBlk& theBlock )
{
    itsBitSet           = theBlock.itsBitSet;
	itsAddr             = theBlock.itsAddr;
    itsType             = theBlock.itsType;
        itsBiSwitching      = theBlock.itsBiSwitching;
    itsProtnRequest     = theBlock.itsProtnRequest;
    itsRtrtv            = theBlock.itsRtrtv;
    itsWtr              = theBlock.itsWtr;
    itsProtHoldOffTime  = theBlock.itsProtHoldOffTime;
    itsProtectType      = theBlock.itsProtectType;
    itsCPFlag           = theBlock.itsCPFlag;
    itsNpOwner          = theBlock.itsNpOwner;
    itsPST              = theBlock.itsPST;
    itsPSTQ             = theBlock.itsPSTQ;
    itsSST              = theBlock.itsSST;
    return *this;
} 

bool TL1_ProtnRspBlk::operator ==(const TL1_ProtnRspBlk& theBlock) const
{
	return (itsBitSet == theBlock.itsBitSet &&
			itsAddr == theBlock.itsAddr &&
			itsType == theBlock.itsType &&
                            itsBiSwitching == theBlock.itsBiSwitching &&
            itsProtnRequest == theBlock.itsProtnRequest &&
			itsRtrtv == theBlock.itsRtrtv &&
			itsWtr == theBlock.itsWtr &&
			itsProtHoldOffTime == theBlock.itsProtHoldOffTime &&
            itsProtectType == theBlock.itsProtectType &&
            itsCPFlag == theBlock.itsCPFlag &&
            itsNpOwner == theBlock.itsNpOwner &&
			itsPST == theBlock.itsPST &&
			itsPSTQ == theBlock.itsPSTQ &&
			itsSST == theBlock.itsSST);

}


void TL1_ProtnRspBlk::SetBiSwitching(bool isBiSwitching)
{
	itsBitSet[INDEX_BiSwitching] = true;
	itsBiSwitching = isBiSwitching;
}

void TL1_ProtnRspBlk::SetProtnRequset(CT_ProtnRequest theProtnRequest)
{
	itsBitSet[INDEX_ProtnRequest] = true;
	itsProtnRequest = theProtnRequest;
}

bool TL1_ProtnRspBlk::GetAddr(CT_TL1_ProtnAddr& theAddr) const
{
        if(itsBitSet.empty())
        {
            return false;
        }

	else if(true == itsBitSet[INDEX_Addr])
	{
		theAddr = itsAddr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetType(CT_ProtGpType& theType) const
{
        if(itsBitSet.empty())
        {
            return false;
        }

	if(true == itsBitSet[INDEX_Type])
	{
		theType = itsType;
		return true;
	}
	else
	{
		return false;
	}
}


bool TL1_ProtnRspBlk::GetBiSwitching(bool& theBiSwitching) const
{
	if(true == itsBitSet[INDEX_BiSwitching])
	{
		theBiSwitching = itsBiSwitching;
		return true;
	}
	else
	{
		return false;
	}
}


bool TL1_ProtnRspBlk::GetProtnRequest(CT_ProtnRequest& theProtnRequest) const
{
	if(true == itsBitSet[INDEX_ProtnRequest])
	{
		theProtnRequest = itsProtnRequest;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetRtrtv(bool& theRtrtv) const
{
	if(true == itsBitSet[INDEX_Rtrtv])
	{
		theRtrtv = itsRtrtv;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetWtr(int& theWtr) const
{
	if(true == itsBitSet[INDEX_Wtr])
	{
		theWtr = itsWtr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetProtHoldOffTime(int& theProtHoldOffTime) const
{
        if(itsBitSet.empty())
        {
            return false;
        }

	else if(true == itsBitSet[INDEX_ProtHoldTime])
	{
		theProtHoldOffTime = itsProtHoldOffTime;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetProtectType(CT_ProtGpType& theProtectType) const
{
        if(itsBitSet.empty())
        {
            return false;
        }

	if(true == itsBitSet[INDEX_ProtectType])
	{
		theProtectType = itsProtectType;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetCPFlag(bool& theCPFlag) const
{
	if(true == itsBitSet[INDEX_CPFlag])
	{
		theCPFlag = itsCPFlag;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetNpOwner(int& theNpOwner) const 
{
	if(true == itsBitSet[INDEX_NpOwner])
	{
		theNpOwner = itsNpOwner;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetPST(CT_SM_PST& thePST) const
{
	if(true == itsBitSet[INDEX_PST])
	{
		thePST = itsPST;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetPSTQ(CT_SM_PSTQ& thePSTQ) const
{
	if(true == itsBitSet[INDEX_PSTQ])
	{
		thePSTQ = itsPSTQ;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_ProtnRspBlk::GetSST(CT_SM_SST& theSST) const
{
	if(true == itsBitSet[INDEX_SST])
	{
		theSST = itsSST;
		return true;
	}
	else
	{
		return false;
	}
}

/******************** Protection Event Response ******************/

TL1_ProtnEvtSSTChgRspBlk::TL1_ProtnEvtSSTChgRspBlk(
                  const TL1_SmartParameter< const CT_TL1_ProtnAddr* > &theEntityAddr,
                  const TL1_SmartParameter< string > &theEntityName,
                  const TL1_SmartParameter< CT_ConditionType > &theSST,
                  const TL1_SmartParameter< CT_TL1_ConditionEffect > &theConditionEffect,
                  const TL1_SmartParameter< CT_NEFlag > &theLocation,
                  const TL1_SmartParameter< string > &theDescription) :
                  /*
	          const TL1_SmartParameter< CT_PMA_ParamId > &theParamId,
                  const TL1_SmartParameter< CT_TimeTm >& theOcrDateOcrTime, const TL1_SmartParameter< CT_NEFlag >& theLocation,
                  */
     itsEntityName(theEntityName),
     itsSST(theSST),
     itsConditionEffect(theConditionEffect),
     itsLocation(theLocation),
     itsDescription(theDescription)
     /*
     itsParamId(theParamId),
     itsOcrDateOcrTime(theOcrDateOcrTime),
     */
{
    const CT_TL1_ProtnAddr* aProtnAddr =
    dynamic_cast<const CT_TL1_ProtnAddr*>( theEntityAddr.GetValue() );
    
    if (aProtnAddr)
    {   
        itsProtnAddr = *aProtnAddr;
    }
}

TL1_ProtnEvtSSTChgRspBlk::~TL1_ProtnEvtSSTChgRspBlk()
{
}
