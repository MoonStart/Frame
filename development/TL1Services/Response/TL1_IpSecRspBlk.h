#ifndef __TL1_IPSECRSPBLK_H_
#define __TL1_IPSECRSPBLK_H_

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive IPSEC Response Class
TARGET:
AUTHOR:         December 3, 2005 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Retrive IPSEC Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SYSTEM_IDS_H_
#include <CommonTypes/CT_IpSec.h>
#endif

#include <CommonTypes/CT_SM_Types.h>

#include <vector>

using namespace std;

//
//	RtrvIpSecSpd
//

class TL1_IpSecRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IpSecRspBlk() {}
    
    TL1_IpSecRspBlk(const TL1_IpSecRspBlk&);

    TL1_IpSecRspBlk( const string*                    theEid,
                     const CT_SecuSpdEntryDirection*  theSecurityPolicy,
                     const string                     theSrcAddr,
                     const string                     theDstAddr,
                     const CT_SecuSpdNewSaPolicyType* theSecurityAssociation,
                     const CT_SecuSpdPolicyType*      theSecurityPolicyAction,
                     const CT_TransProtType*          theTransportProtocol,
                     const CT_SrcPortType*            theSourceAddress,
                     const CT_DestPortType*           theDestinationAddress );
                 
    virtual ~TL1_IpSecRspBlk();

    TL1_IpSecRspBlk& operator=( const TL1_IpSecRspBlk& theBlock );

    bool GetEid(string&) const;
    bool GetSecurityPolicy(CT_SecuSpdEntryDirection&) const;
    bool GetSrcAddr(string&) const;
    bool GetDstAddr(string&) const;
    bool GetSecurityAssociation(CT_SecuSpdNewSaPolicyType&) const;
    bool GetSecurityPolicyAction(CT_SecuSpdPolicyType&) const;
    bool GetTransportProtocol( CT_TransProtType& ) const;
    bool GetSourceAddress( CT_SrcPortType&  ) const;
    bool GetDestinationAddress( CT_DestPortType&  ) const;

private:

    enum {
        INDEX_Aid = 0,
        INDEX_Eid,
        INDEX_SecurityPolicy,
        INDEX_SrcAddr,
        INDEX_DstAddr,
        INDEX_Status,
        INDEX_SecurityAssociation,
        INDEX_SecurityPolicyAction,
        INDEX_TransportProtocol,
        INDEX_SourceAddress,
        INDEX_DestinationAddress,
        INDEX_END
	};

    vector<bool>              myBitSet;
    string                    myEid;
    CT_SecuSpdEntryDirection  mySecurityPolicy;
    string                    mySrcAddr;
    string                    myDstAddr;
    CT_SecuSpdNewSaPolicyType mySecurityAssociation;
    CT_SecuSpdPolicyType      mySecurityPolicyAction;
    CT_TransProtType          myTransportProtocol;
    CT_SrcPortType            mySourceAddress;
    CT_DestPortType           myDestinationAddress;
};



//
//	RtrvPsk
//

class TL1_IpSecPskRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IpSecPskRspBlk( ) {myIsDeleteNotif = false;}
    
    TL1_IpSecPskRspBlk( const TL1_IpSecPskRspBlk& );

    TL1_IpSecPskRspBlk( const CT_PskIdentifier& thePskIdentifier,
                        const string& theEntryId,
                        bool theIsDeleteNotif  );
                 
    virtual ~TL1_IpSecPskRspBlk( );

    TL1_IpSecPskRspBlk& operator=( const TL1_IpSecPskRspBlk& theBlock );

    const CT_PskIdentifier& GetIdentifier( ) const {return myPskIdentifier;}

    void SetIdentifier(const CT_PskIdentifier& thePskIdentifier) 
        {myPskIdentifier = thePskIdentifier;}

    void SetEntryId(const string& theEntryId) {myEntryId = theEntryId;}

    const string& GetEntryId() const {return myEntryId;}

    bool GetIsDeleteNotif() const {return myIsDeleteNotif;}
private:

    enum {
        INDEX_Aid = 0,
        INDEX_EntryId,
        INDEX_PskIdentifier,
        INDEX_END
	};

    vector<bool>                 myBitSet;
    CT_PskIdentifier             myPskIdentifier;
    string                       myEntryId;
    bool                         myIsDeleteNotif;
};


//
//	RtrvIpsec
//

class TL1_IpSecEnabledRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IpSecEnabledRspBlk( ) {}
    
    TL1_IpSecEnabledRspBlk( const TL1_IpSecEnabledRspBlk& );

    TL1_IpSecEnabledRspBlk( const string& theIpAddress,
                            const bool theIsEnabled  );
                 
    virtual ~TL1_IpSecEnabledRspBlk( );

    TL1_IpSecEnabledRspBlk& operator=( const TL1_IpSecEnabledRspBlk& theBlock );

    const string& GetIpAddress( ) const {return myIpAddress;}

    bool GetIsEnabled() const {return myIsEnabled;}
private:

    string          myIpAddress;
    bool            myIsEnabled;
};
typedef TL1_Rtv_Response< TL1_IpSecRspBlk > TL1_IpSecResponse;
typedef TL1_Rtv_Response< TL1_IpSecEnabledRspBlk > TL1_IpSecEnabledResponse;
typedef TL1_Rtv_Response< TL1_IpSecPskRspBlk > TL1_IpSecPskResponse;

//
//	RtrvSpd
//

class TL1_SpdRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SpdRspBlk( ) {myIsDeleteNotif = false;}
    
    TL1_SpdRspBlk( const TL1_SpdRspBlk& );

    TL1_SpdRspBlk( const string& theEntryId,
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
                   bool theIsDeleteNotif );
                 
    virtual ~TL1_SpdRspBlk( );

    TL1_SpdRspBlk& operator=( const TL1_SpdRspBlk& theBlock );

    void SetEntryId(const string& theEntryId) {myEntryId = theEntryId;}
    const string& GetEntryId() const {return myEntryId;}

    const string& GetName( ) const {return myName;}
    void SetName(const string& theName) {myName = theName;}

    void SetLocalAddress(const string& theLocalAddress) {myLocalAddress = theLocalAddress;}
    const string& GetLocalAddress() const {return myLocalAddress;}

    void SetRemoteAddress(const string& theRemoteAddress) {myRemoteAddress = theRemoteAddress;}
    const string& GetRemoteAddress() const {return myRemoteAddress;}

    void SetLocalPort(const string& theLocalPort) {myLocalPort = theLocalPort;}
    const string& GetLocalPort() const {return myLocalPort;}

    void SetRemotePort(const string& theRemotePort){myRemotePort = theRemotePort;}
    const string& GetRemotePort() const {return myRemotePort;}

    void SetProtocol(const string& theProtocol) {myProtocol = theProtocol;}
    const string& GetProtocol() const {return myProtocol;}

    void SetAction(const CT_SecuSpdPolicyType theAction) {myAction = theAction;}
    CT_SecuSpdPolicyType GetAction() const {return myAction;}

    void SetConnectionType(const CT_SecuSpdModeType theConnectionType) {myConnectionType = theConnectionType;}
    CT_SecuSpdModeType GetConnectionType() const {return myConnectionType;}

    void SetAlgorithmSuite(const CT_SecuSpdSuite theAlgorithmSuite) {myAlgorithmSuite = theAlgorithmSuite;}
    CT_SecuSpdSuite GetAlgorithmSuite() const {return myAlgorithmSuite;}

    void SetIkeVersion(const CT_SecuIkeVersion theVersion) {myIkeVersion = theVersion;}
    CT_SecuIkeVersion GetIkeVersion() const {return myIkeVersion;}

    void SetIkeAuthorization(const string& theIkeAuthorization) {myIkeAuthorization = theIkeAuthorization;}
    const string& GetIkeAuthorization() const {return myIkeAuthorization;}

    bool GetIsDeleteNotif() const {return myIsDeleteNotif;}
private:

    string          myName;
    string          myLocalAddress;
    string          myRemoteAddress;
    string          myLocalPort;
    string          myRemotePort;
    string          myProtocol;
    CT_SecuSpdPolicyType myAction;
    CT_SecuSpdModeType   myConnectionType;
    CT_SecuSpdSuite      myAlgorithmSuite;
    CT_SecuIkeVersion    myIkeVersion;
    string               myIkeAuthorization;
    string          myEntryId;
    bool myIsDeleteNotif;
   };

typedef TL1_Rtv_Response< TL1_SpdRspBlk > TL1_SpdResponse;

//
//	RtrvIpSecCert
//

class TL1_IpSecCertRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IpSecCertRspBlk() {}
    
    TL1_IpSecCertRspBlk(const TL1_IpSecCertRspBlk&);

    TL1_IpSecCertRspBlk( const string 			theCertId,
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
                  const CT_SM_SST *  theSST);
                 
    virtual ~TL1_IpSecCertRspBlk();

    TL1_IpSecCertRspBlk& operator=( const TL1_IpSecCertRspBlk& theBlock );

    bool GetCertId(string&) const;
    bool GetActCert(CT_Yes_No&) const;
    bool GetCertIssuer(string&) const;
    bool GetCertSubj(string&) const;
    bool GetCertValidFrom(string&) const;
    bool GetCertValidTo(string&) const;
    bool GetCertMinExpThreshold(CT_MinorExpThreshold&) const;
    bool GetCertMajExpThreshold(CT_MajorExpThreshold&) const;
    bool GetCertValidState(CT_ValidState&) const;
    bool GetCertIpSecEnabled(CT_Yes_No&) const;
    bool GetCertAlarmProfile(CT_AlarmProfile&) const;
    bool GetCertPrimaryState(CT_SM_PST&) const;
    bool GetCertPrimaryStateQualifier(CT_SM_PSTQ&) const;
    bool GetCertSecondaryState(CT_SM_SST&) const;

private:

    enum {
        INDEX_CertId = 0,
	INDEX_ActCert,
        INDEX_CertIssuer,
        INDEX_CertSubj,
        INDEX_CertValidFrom,
        INDEX_CertValidTo,
	INDEX_MinExpThreshold,
	INDEX_MajExpThreshold,
	INDEX_ValidState,
	INDEX_IpSecEnabled,
	INDEX_AlarmProfile,
	INDEX_PrimaryState,
        INDEX_PrimaryStateQualifier,
        INDEX_SecondaryState,
        INDEX_END
	};

    vector<bool>              myBitSet;
    string		      myCertId;
    CT_Yes_No		      myActCert;
    string		      myCertIssuer;
    string		      myCertSubj;
    string		      myCertValidFrom;
    string		      myCertValidTo;
    CT_MinorExpThreshold      myMinExpThreshold;
    CT_MajorExpThreshold      myMajExpThreshold;
    CT_ValidState	      myValidState;
    CT_Yes_No		      myIpSecEnabled;
    CT_AlarmProfile	      myAlarmProfile;
    CT_SM_PST	      myPrimaryState;
    CT_SM_PSTQ	      myPrimaryStateQualifier;
    CT_SM_SST	      mySecondaryState;

};

typedef TL1_Rtv_Response< TL1_IpSecCertRspBlk > TL1_IpSecCertResponse;


#endif
