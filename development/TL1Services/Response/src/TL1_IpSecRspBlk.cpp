/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 IPSEC Response 
TARGET:
AUTHOR:         December 5, 2005 - Mike Rodgers
DESCRIPTION:    Source file for TL1 Retrive IPSEC Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IpSecRspBlk.h>

//
//	RtrvIpSecSpd
//

TL1_IpSecRspBlk::TL1_IpSecRspBlk(
    						const string*                    theEid,
							const CT_SecuSpdEntryDirection*  theSecurityPolicy,
							const string                     theSrcAddr,
							const string                     theDstAddr,
							const CT_SecuSpdNewSaPolicyType* theSecurityAssociation,
							const CT_SecuSpdPolicyType*      theSecurityPolicyAction,
                            const CT_TransProtType*          theTransportProtocol,
                            const CT_SrcPortType*            theSourceAddress,
                            const CT_DestPortType*           theDestinationAddress )
    : myBitSet( INDEX_END, false)
{
    if( theEid )  
    {
		myBitSet[ INDEX_Eid ] = true;
        myEid = *theEid;
    }

    if( theSecurityPolicy )  
    {
		myBitSet[ INDEX_SecurityPolicy ] = true;
        mySecurityPolicy = *theSecurityPolicy;
    }

    if( theSrcAddr.length() )  
    {
		myBitSet[ INDEX_SrcAddr ] = true;
        mySrcAddr = theSrcAddr;
    }

    if( theDstAddr.length() )  
    {
		myBitSet[ INDEX_DstAddr ] = true;
        myDstAddr = theDstAddr;
    }

    if( theSecurityAssociation )  
    {
		myBitSet[ INDEX_SecurityAssociation ] = true;
        mySecurityAssociation = *theSecurityAssociation;
    }

    if( theSecurityPolicyAction )  
    {
		myBitSet[ INDEX_SecurityPolicyAction ] = true;
        mySecurityPolicyAction = *theSecurityPolicyAction;
    }

    if ( theTransportProtocol )
    {
        myBitSet[ INDEX_TransportProtocol ] = true;
        myTransportProtocol = *theTransportProtocol;
    }

    if( theSourceAddress )
    {
        myBitSet[ INDEX_SourceAddress ] = true;
        mySourceAddress = *theSourceAddress;
    }

    if( theDestinationAddress )
    {
        myBitSet[ INDEX_DestinationAddress ] = true;
        myDestinationAddress = *theDestinationAddress;
    }
}


TL1_IpSecRspBlk::~TL1_IpSecRspBlk()
{
}
  
TL1_IpSecRspBlk::TL1_IpSecRspBlk(const TL1_IpSecRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myEid(theBlock.myEid),
    mySecurityPolicy(theBlock.mySecurityPolicy),
    mySrcAddr(theBlock.mySrcAddr),
    myDstAddr(theBlock.myDstAddr),
    mySecurityAssociation(theBlock.mySecurityAssociation),
    mySecurityPolicyAction(theBlock.mySecurityPolicyAction),
    myTransportProtocol( theBlock.myTransportProtocol ),
    mySourceAddress( theBlock.mySourceAddress ),
    myDestinationAddress( theBlock.myDestinationAddress )
{
}

TL1_IpSecRspBlk& TL1_IpSecRspBlk::operator=( const TL1_IpSecRspBlk& theBlock )
{
    myBitSet                    = theBlock.myBitSet;
    myEid                       = theBlock.myEid;
    mySecurityPolicy            = theBlock.mySecurityPolicy;
    mySrcAddr                   = theBlock.mySrcAddr;
    myDstAddr                   = theBlock.myDstAddr;
    mySecurityAssociation       = theBlock.mySecurityAssociation;
    mySecurityPolicyAction      = theBlock.mySecurityPolicyAction;
    myTransportProtocol         = theBlock.myTransportProtocol;
    mySourceAddress             = theBlock.mySourceAddress;
    myDestinationAddress        = theBlock.myDestinationAddress;

    return *this;
}

bool TL1_IpSecRspBlk::GetEid(string& Eid) const
{
    if( true == myBitSet[ INDEX_Eid ] )
	{
    	Eid = myEid;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_IpSecRspBlk::GetSecurityPolicy(CT_SecuSpdEntryDirection& SecurityPolicy) const
{
    if( true == myBitSet[ INDEX_SecurityPolicy ] )
	{
    	SecurityPolicy = mySecurityPolicy;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_IpSecRspBlk::GetSrcAddr(string& SrcAddr) const
{
    if( true == myBitSet[ INDEX_SrcAddr ] )
	{
    	SrcAddr = mySrcAddr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_IpSecRspBlk::GetDstAddr(string& DstAddr) const
{
    if( true == myBitSet[ INDEX_DstAddr ] )
	{
    	DstAddr = myDstAddr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_IpSecRspBlk::GetSecurityAssociation(CT_SecuSpdNewSaPolicyType& SecurityAssociation) const
{
    if( true == myBitSet[ INDEX_SecurityAssociation ] )
	{
    	SecurityAssociation = mySecurityAssociation;
		return true;
	}
	else
	{
		return false;
	}
}

bool TL1_IpSecRspBlk::GetSecurityPolicyAction(CT_SecuSpdPolicyType& SecurityPolicyAction) const
{
    if( true == myBitSet[ INDEX_SecurityPolicyAction ] )
	{
    	SecurityPolicyAction = mySecurityPolicyAction;
		return true;
	}
	else
	{
		return false;
	}
}

bool 
TL1_IpSecRspBlk::GetTransportProtocol( CT_TransProtType& TransportProtocol ) const
{
    if( true == myBitSet[ INDEX_TransportProtocol ] )
	{
    	TransportProtocol = myTransportProtocol;
		return true;
	}
	else
	{
		return false;
	}
}

bool 
TL1_IpSecRspBlk::GetSourceAddress( CT_SrcPortType& SourceAddress ) const
{
    if( true == myBitSet[ INDEX_SourceAddress ] )
	{
    	SourceAddress = mySourceAddress;
		return true;
	}
	else
	{
		return false;
	}
}

bool 
TL1_IpSecRspBlk::GetDestinationAddress( CT_DestPortType&  DestinationAddress ) const
{
    if( true == myBitSet[ INDEX_DestinationAddress ] )
	{
    	DestinationAddress = myDestinationAddress;
		return true;
	}
	else
	{
		return false;
	}
}

//
//	RtrvPsk
//

TL1_IpSecPskRspBlk::TL1_IpSecPskRspBlk( const CT_PskIdentifier& thePskIdentifier,
                                        const string& theEntryId,
                                        bool theIsDeleteNotif )
    : myBitSet( INDEX_END, false)
{
    myBitSet[ INDEX_PskIdentifier ] = true;
    myPskIdentifier = thePskIdentifier;
    myBitSet[ INDEX_EntryId ] = true;
    myEntryId = theEntryId;
    myIsDeleteNotif = theIsDeleteNotif;
}

TL1_IpSecPskRspBlk::~TL1_IpSecPskRspBlk()
{
}
  
TL1_IpSecPskRspBlk::TL1_IpSecPskRspBlk(const TL1_IpSecPskRspBlk& theBlock) :
    myBitSet( theBlock.myBitSet ),
    myPskIdentifier( theBlock.myPskIdentifier ),
    myEntryId( theBlock.myEntryId ),
    myIsDeleteNotif(theBlock.myIsDeleteNotif)
{
}

TL1_IpSecPskRspBlk& 
TL1_IpSecPskRspBlk::operator=( const TL1_IpSecPskRspBlk& theBlock )
{
    myBitSet =        theBlock.myBitSet;
    myPskIdentifier = theBlock.myPskIdentifier;
    myEntryId =       theBlock.myEntryId;
    myIsDeleteNotif = theBlock.myIsDeleteNotif;

    return *this;
}

//
//	RtrvIpSec
//

TL1_IpSecEnabledRspBlk::TL1_IpSecEnabledRspBlk( const string& theIpAddress,
                                                const bool theIsEnabled )
{
    myIpAddress = theIpAddress;
    myIsEnabled = theIsEnabled;
}

TL1_IpSecEnabledRspBlk::~TL1_IpSecEnabledRspBlk()
{
}
  
TL1_IpSecEnabledRspBlk::TL1_IpSecEnabledRspBlk(const TL1_IpSecEnabledRspBlk& theBlock) :
    myIpAddress( theBlock.myIpAddress ),
    myIsEnabled(theBlock.myIsEnabled)
{
}

TL1_IpSecEnabledRspBlk& 
TL1_IpSecEnabledRspBlk::operator=( const TL1_IpSecEnabledRspBlk& theBlock )
{
    myIpAddress =        theBlock.myIpAddress;
    myIsEnabled =    theBlock.myIsEnabled;

    return *this;
}

//
//	RtrvSpd
//

TL1_SpdRspBlk::TL1_SpdRspBlk( const string& theEntryId,
                              const string& theName,
                              const string& theLocalAddress,
                              const string& theRemoteAddress,
                              const string& theLocalPort,
                              const string& theRemotePort,
                              const string& theProtocol,
                              const CT_SecuSpdPolicyType& theAction,
                              const CT_SecuSpdModeType& theConnectionType,
                              const CT_SecuSpdSuite& theAlgorithmSuite,
                              const CT_SecuIkeVersion& theIkeVersion,
                              const string& theIkeAuthorization,
                              bool theIsDeleteNotif )
{
    myEntryId = theEntryId;
    myName = theName;
    myLocalAddress = theLocalAddress;
    myRemoteAddress = theRemoteAddress;
    myLocalPort = theLocalPort;
    myRemotePort = theRemotePort;
    myProtocol = theProtocol;
    myAction = theAction;
    myConnectionType = theConnectionType;
    myAlgorithmSuite = theAlgorithmSuite;
    myIkeVersion = theIkeVersion;
    myIkeAuthorization = theIkeAuthorization;
    myIsDeleteNotif = theIsDeleteNotif;
}

TL1_SpdRspBlk::~TL1_SpdRspBlk()
{
}
  
TL1_SpdRspBlk::TL1_SpdRspBlk(const TL1_SpdRspBlk& theBlock) :
    myEntryId( theBlock.myEntryId ),
    myName( theBlock.myName ),
    myLocalAddress( theBlock.myLocalAddress ),
    myRemoteAddress( theBlock.myRemoteAddress ),
    myLocalPort( theBlock.myLocalPort ),
    myRemotePort( theBlock.myRemotePort ),
    myProtocol( theBlock.myProtocol ),
    myAction( theBlock.myAction ),
    myConnectionType( theBlock.myConnectionType ),
    myAlgorithmSuite( theBlock.myAlgorithmSuite ),
    myIkeVersion( theBlock.myIkeVersion ),
    myIkeAuthorization( theBlock.myIkeAuthorization ),
    myIsDeleteNotif(theBlock.myIsDeleteNotif)
{
}

TL1_SpdRspBlk& 
TL1_SpdRspBlk::operator=( const TL1_SpdRspBlk& theBlock )
{
    myEntryId = theBlock.myEntryId;
    myName =  theBlock.myName;
    myLocalAddress =     theBlock.myLocalAddress;
    myRemoteAddress =     theBlock.myRemoteAddress;
    myLocalPort =     theBlock.myLocalPort;
    myRemotePort =     theBlock.myRemotePort;
    myProtocol =     theBlock.myProtocol;
    myAction =     theBlock.myAction;
    myConnectionType =     theBlock.myConnectionType;
    myAlgorithmSuite =     theBlock.myAlgorithmSuite;
    myIkeVersion =     theBlock.myIkeVersion;
    myIkeAuthorization =     theBlock.myIkeAuthorization;
    myIsDeleteNotif = theBlock.myIsDeleteNotif;

    return *this;
}

//
//	RtrvIpSecCert
//

TL1_IpSecCertRspBlk::TL1_IpSecCertRspBlk( const string	theCertId,
			const CT_Yes_No *		theActCert,
			const string                 	theCertIssuer,
                     	const string                   	theCertSubj,
                     	const string                    theCertValidFrom,
                     	const string                    theCertValidTo,
			const CT_MinorExpThreshold *	theMinExpThreshold,
			const CT_MajorExpThreshold *	theMajExpThreshold,
			const CT_ValidState *		theValidState,
			const CT_Yes_No *		theIpSecEnabled,
			const CT_AlarmProfile *		theAlarmProfile,
			const CT_SM_PST *  thePST,
                  const CT_SM_PSTQ * thePSTQ,
                  const CT_SM_SST *  theSST)
    : myBitSet( INDEX_END, false)
{
    if (theCertId.length())
    {
	myBitSet[ INDEX_CertId] = true;
	myCertId = theCertId;
    }
    if (theActCert)
    {
	myBitSet[ INDEX_ActCert] = true;
	myActCert = *theActCert;
    }
    if( theCertIssuer.length() )  
    {
	myBitSet[ INDEX_CertIssuer ] = true;
        myCertIssuer = theCertIssuer;
    }
    if( theCertSubj.length() )  
    {
	myBitSet[ INDEX_CertSubj ] = true;
        myCertSubj = theCertSubj;
    }
    if( theCertValidFrom.length() )  
    {
	myBitSet[ INDEX_CertValidFrom ] = true;
        myCertValidFrom = theCertValidFrom;
    }
    if( theCertValidTo.length() )  
    {
	myBitSet[ INDEX_CertValidTo ] = true;
        myCertValidTo = theCertValidTo;
    }
    if (theMinExpThreshold)
    {
	myBitSet[INDEX_MinExpThreshold] = true;
	myMinExpThreshold = *theMinExpThreshold;
    }
    if (theMajExpThreshold)
    {
	myBitSet[INDEX_MajExpThreshold] = true;
	myMajExpThreshold = *theMajExpThreshold;
    }
    if (theValidState)
    {
	myBitSet[INDEX_ValidState] = true;
	myValidState = *theValidState;
    }    
    if (theIpSecEnabled)
    {
	myBitSet[INDEX_IpSecEnabled] = true;
	myIpSecEnabled = *theIpSecEnabled;
    }
    if (theAlarmProfile)
    {
	myBitSet[INDEX_AlarmProfile] = true;
	myAlarmProfile = *theAlarmProfile;
    }
    if (thePST)
    {
	myBitSet[INDEX_PrimaryState] = true;
	myPrimaryState = *thePST;
    }
    if (thePSTQ)
    {
    myBitSet[INDEX_PrimaryStateQualifier] = true;
    myPrimaryStateQualifier = *thePSTQ;
    }
    if (theSST)
    {
    myBitSet[INDEX_SecondaryState] = true;
    mySecondaryState = *theSST;
    }

}


TL1_IpSecCertRspBlk::~TL1_IpSecCertRspBlk()
{
}
  
TL1_IpSecCertRspBlk::TL1_IpSecCertRspBlk(const TL1_IpSecCertRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myCertId(theBlock.myCertId),
    myActCert(theBlock.myActCert),
    myCertIssuer(theBlock.myCertIssuer),
    myCertSubj(theBlock.myCertSubj),
    myCertValidFrom(theBlock.myCertValidFrom),
    myCertValidTo(theBlock.myCertValidTo),
    myMinExpThreshold(theBlock.myMinExpThreshold),
    myMajExpThreshold(theBlock.myMajExpThreshold),
    myValidState(theBlock.myValidState),
    myIpSecEnabled(theBlock.myIpSecEnabled),
    myAlarmProfile(theBlock.myAlarmProfile),
    myPrimaryState(theBlock.myPrimaryState),
    myPrimaryStateQualifier(theBlock.myPrimaryStateQualifier),
    mySecondaryState(theBlock.mySecondaryState)
{
}

TL1_IpSecCertRspBlk& TL1_IpSecCertRspBlk::operator=( const TL1_IpSecCertRspBlk& theBlock )
{
    myBitSet		= theBlock.myBitSet;
    myCertId		= theBlock.myCertId;
    myActCert		= theBlock.myActCert;
    myCertIssuer	= theBlock.myCertIssuer;
    myCertSubj		= theBlock.myCertSubj;
    myCertValidFrom	= theBlock.myCertValidFrom;
    myCertValidTo	= theBlock.myCertValidTo;
    myMinExpThreshold	= theBlock.myMinExpThreshold;
    myMajExpThreshold	= theBlock.myMajExpThreshold;
    myValidState        = theBlock.myValidState;
    myIpSecEnabled	= theBlock.myIpSecEnabled;
    myAlarmProfile	= theBlock.myAlarmProfile;
    myPrimaryState	= theBlock.myPrimaryState;
    myPrimaryStateQualifier	= theBlock.myPrimaryStateQualifier;
    mySecondaryState	= theBlock.mySecondaryState;

    return *this;
}

bool TL1_IpSecCertRspBlk::GetCertIssuer(string& CertIssuer) const
{
    if( true == myBitSet[ INDEX_CertIssuer ] )
	{
    	CertIssuer = myCertIssuer;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_IpSecCertRspBlk::GetCertSubj(string& CertSubj) const
{
    if( true == myBitSet[ INDEX_CertSubj ] )
	{
    	CertSubj = myCertSubj;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_IpSecCertRspBlk::GetCertValidFrom(string& CertValidFrom) const
{
    if( true == myBitSet[ INDEX_CertValidFrom ] )
	{
    	CertValidFrom = myCertValidFrom;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_IpSecCertRspBlk::GetCertValidTo(string& CertValidTo) const
{
    if( true == myBitSet[ INDEX_CertValidTo ] )
	{
    	CertValidTo = myCertValidTo;
		return true;
	}
	else
	{
		return false;
	}
}
bool TL1_IpSecCertRspBlk::GetCertId(string& CertIdVal) const
{
   if (true == myBitSet[ INDEX_CertId] )
	{
	CertIdVal = myCertId;
	return true;
	}
   else
	return false;
}

bool TL1_IpSecCertRspBlk::GetActCert(CT_Yes_No& ActCertVal) const
{
   if (true == myBitSet[ INDEX_ActCert] )
	{
	ActCertVal = myActCert;
	return true;
	}
   else
	return false;
}

bool TL1_IpSecCertRspBlk::GetCertMinExpThreshold(CT_MinorExpThreshold& MinExpThreshold ) const
{
   if (true == myBitSet[ INDEX_MinExpThreshold] )
	{
	MinExpThreshold = myMinExpThreshold;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertMajExpThreshold(CT_MajorExpThreshold& MajExpThreshold) const
{
   if (true == myBitSet[ INDEX_MajExpThreshold] )
	{
	MajExpThreshold = myMajExpThreshold;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertValidState(CT_ValidState& ValidState) const
{
   if (true == myBitSet[ INDEX_ValidState] )
	{
	ValidState = myValidState;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertIpSecEnabled(CT_Yes_No& IpSecEnabled) const
{
   if (true == myBitSet[ INDEX_IpSecEnabled] )
	{
	IpSecEnabled = myIpSecEnabled;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertAlarmProfile(CT_AlarmProfile& AlarmProfile) const
{
   if (true == myBitSet[ INDEX_AlarmProfile] )
	{
	AlarmProfile = myAlarmProfile;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertPrimaryState(CT_SM_PST& PrimaryState) const
{
   if (true == myBitSet[ INDEX_PrimaryState] )
	{
	PrimaryState = myPrimaryState;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertPrimaryStateQualifier(CT_SM_PSTQ& PrimaryStateQualifier) const
{
   if (true == myBitSet[ INDEX_PrimaryStateQualifier] )
	{
	PrimaryStateQualifier = myPrimaryStateQualifier;
	return true;
	}
   else
	return false;
}
bool TL1_IpSecCertRspBlk::GetCertSecondaryState(CT_SM_SST& SecondaryState) const
{
   if (true == myBitSet[ INDEX_SecondaryState] )
	{
	SecondaryState = mySecondaryState;
	return true;
	}
   else
	return false;
}

