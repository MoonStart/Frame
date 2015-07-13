/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 11, 2007 - Tong Wu
DESCRIPTION:    Implementation file for SLPF and SLPOLICY TL1 ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLPFPARAMETERS_H__
#include <TL1Core/TL1_SlpfParameters.h>
#endif

TL1_SlpfEdParameters::TL1_SlpfEdParameters()  :
                myHandle((LT_Handle*)0),
                myCtag((LT_Ctag)0),
                myProfName((string*)0),
                myProtLvl((CT_SLPF_ProtLvl*)0),
                myDiversity((CT_SLPF_Diversity*)0),
                myReversion((CT_SLPF_Params*)0),
                myCoRouting((CT_SLPF_Params*)0),
                myTransLineMSDCC((CT_SLPF_Params*)0),
                myTransSectionRSDCC((CT_SLPF_Params*)0),
                myTransOTUGCC0((CT_SLPF_Params*)0),
                myTransODUGCC12((CT_SLPF_Params*)0),
                myWtr((int*)0),
                myCallSetupReroute((CT_SLPF_Params*)0),
                myMaxRerouteAttempts((int*)0),
                myBackoffInterval((int*)0),
                myBoundReroute((CT_SLPF_Params*)0),
                myEndToEndReroute((CT_SLPF_Params*)0),
                myLatency((int*)0),
                myResourceClass((uint32*)0),
                myPriority((CT_SLPF_PRIORITY*)0),
                myReservationStyle((CT_Resv_Style*)0),
                myResConnA((CT_Advertisement*)0),
                myResConnB((CT_Advertisement*)0),
                myDiversityCheck((CT_Slpf_DiversityCheck*)0),
                myCpReversion((CT_Slpf_CpReversion*)0),
                myCpWtr((int*)0)
{
}

TL1_SlpfEdParameters::TL1_SlpfEdParameters(const TL1_SlpfEdParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myProfName=             theInst.myProfName;
    myProtLvl=              theInst.myProtLvl;
    myDiversity=            theInst.myDiversity;
    myReversion=            theInst.myReversion;
    myCoRouting=            theInst.myCoRouting;
    myTransLineMSDCC=       theInst.myTransLineMSDCC;
    myTransSectionRSDCC=    theInst.myTransSectionRSDCC;
    myTransOTUGCC0=         theInst.myTransOTUGCC0;
    myTransODUGCC12=        theInst.myTransODUGCC12;
    myWtr=                  theInst.myWtr;
    myCallSetupReroute=     theInst.myCallSetupReroute;
    myMaxRerouteAttempts=   theInst.myMaxRerouteAttempts;
    myBackoffInterval=      theInst.myBackoffInterval;
    myBoundReroute=         theInst.myBoundReroute;
    myEndToEndReroute=      theInst.myEndToEndReroute;
    myLatency=              theInst.myLatency;
    myResourceClass=        theInst.myResourceClass;
    myPriority=             theInst.myPriority;
    myReservationStyle=     theInst.myReservationStyle;
    myResConnA=             theInst.myResConnA;
    myResConnB=             theInst.myResConnB;
    myDiversityCheck=       theInst.myDiversityCheck;
    myCpReversion=          theInst.myCpReversion;
    myCpWtr=                theInst.myCpWtr;
}

TL1_SlpfEdParameters::~TL1_SlpfEdParameters()
{
}

TL1_SlpfEdParameters& 
TL1_SlpfEdParameters::operator=( const TL1_SlpfEdParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myProfName=             theInst.myProfName;
    myProtLvl=              theInst.myProtLvl;
    myDiversity=            theInst.myDiversity;
    myReversion=            theInst.myReversion;
    myCoRouting=            theInst.myCoRouting;
    myTransLineMSDCC=       theInst.myTransLineMSDCC;
    myTransSectionRSDCC=    theInst.myTransSectionRSDCC;
    myTransOTUGCC0=         theInst.myTransOTUGCC0;
    myTransODUGCC12=        theInst.myTransODUGCC12;
    myWtr=                  theInst.myWtr;
    myCallSetupReroute=     theInst.myCallSetupReroute;
    myMaxRerouteAttempts=   theInst.myMaxRerouteAttempts;
    myBackoffInterval=      theInst.myBackoffInterval;
    myBoundReroute=         theInst.myBoundReroute;
    myEndToEndReroute=      theInst.myEndToEndReroute;
    myLatency=              theInst.myLatency;
    myResourceClass=        theInst.myResourceClass;
    myPriority=             theInst.myPriority;
    myReservationStyle=     theInst.myReservationStyle;
    myResConnA=             theInst.myResConnA;
    myResConnB=             theInst.myResConnB;
    myDiversityCheck=       theInst.myDiversityCheck;
    myCpReversion=          theInst.myCpReversion;
    myCpWtr=                theInst.myCpWtr;

    return *this;
}

bool 
TL1_SlpfEdParameters::operator==( const TL1_SlpfEdParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( !(myProfName == theInst.myProfName) )
        return false;

    if ( myProtLvl != theInst.myProtLvl)
        return false;

    if ( myDiversity != theInst.myDiversity)
        return false;

    if ( myReversion != theInst.myReversion)
        return false;

    if ( myCoRouting != theInst.myCoRouting )
        return false;

    if ( myTransLineMSDCC != theInst.myTransLineMSDCC )
        return false;

    if ( myTransSectionRSDCC != theInst.myTransSectionRSDCC )
        return false;

    if ( myTransOTUGCC0 != theInst.myTransOTUGCC0 )
        return false;

    if ( myTransODUGCC12 != theInst.myTransODUGCC12 )
        return false;
 
    if ( myWtr != theInst.myWtr )
        return false;

    if ( myCallSetupReroute != theInst.myCallSetupReroute )
        return false;

    if ( myMaxRerouteAttempts != theInst.myMaxRerouteAttempts )
        return false;

    if ( myBackoffInterval != theInst.myBackoffInterval )
        return false;

    if ( myBoundReroute != theInst.myBoundReroute )
        return false;

    if ( myEndToEndReroute != theInst.myEndToEndReroute )
        return false;

    if ( myLatency != theInst.myLatency )
        return false;

    if ( myResourceClass != theInst.myResourceClass )
        return false;

    if ( myPriority != theInst.myPriority )
        return false;

    if ( myReservationStyle != theInst.myReservationStyle )
        return false;

    if ( myResConnA != theInst.myResConnA )
        return false;

    if ( myResConnB != theInst.myResConnB )
        return false;
    
    if ( myDiversityCheck != theInst.myDiversityCheck )
        return false;

    if ( myCpReversion != theInst.myCpReversion )
        return false;
    
    if ( myCpWtr != theInst.myCpWtr )
        return false;    

    return true;
}

//--------------------------------------------------------------------------------
CT_Slpf_DiversityCheck*
TL1_SlpfEdParameters::GetDiversityCheck() const
{
    return myDiversityCheck;
}

void
TL1_SlpfEdParameters::SetDiversityCheck(CT_Slpf_DiversityCheck* theDiversityCheck)
{
    myDiversityCheck = theDiversityCheck;
}


//--------------------------------------------------------------------------------
CT_Slpf_CpReversion*
TL1_SlpfEdParameters::GetCpReversion( ) const
{
    return myCpReversion;
}

void
TL1_SlpfEdParameters::SetCpReversion( CT_Slpf_CpReversion* theCpReversion )
{
    myCpReversion = theCpReversion;
}

//--------------------------------------------------------------------------------
int*                       
TL1_SlpfEdParameters::GetCpWtr( ) const
{
    return myCpWtr;
}

void                       
TL1_SlpfEdParameters::SetCpWtr( int* theCpWtr )
{
    myCpWtr = theCpWtr;
}

//------------------------------------------------------------------------------------

TL1_SlpolicyEdParameters::TL1_SlpolicyEdParameters()
{
    myHandle=             (LT_Handle*)0;
    myCtag=               (LT_Ctag)0;
    myPolicyName=         (string*)0;
    mySvcLvlCodePoint1=   (uint16*)0;
    mySvcLvlProfileAid1=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint2=   (uint16*)0;
    mySvcLvlProfileAid2=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint3=   (uint16*)0;
    mySvcLvlProfileAid3=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint4=   (uint16*)0;
    mySvcLvlProfileAid4=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint5=   (uint16*)0;
    mySvcLvlProfileAid5=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint6=   (uint16*)0;
    mySvcLvlProfileAid6=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint7=   (uint16*)0;
    mySvcLvlProfileAid7=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint8=   (uint16*)0;
    mySvcLvlProfileAid8=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint9=   (uint16*)0;
    mySvcLvlProfileAid9=  (CT_TL1_LogicalAddr*)0;
    mySvcLvlCodePoint10=   (uint16*)0;
    mySvcLvlProfileAid10=  (CT_TL1_LogicalAddr*)0;
}

TL1_SlpolicyEdParameters::TL1_SlpolicyEdParameters(const TL1_SlpolicyEdParameters& theInst )
{
    myHandle=             theInst.myHandle;    
    myCtag=               theInst.myCtag;
    myPolicyName=         theInst.myPolicyName;
    mySvcLvlCodePoint1=   theInst.mySvcLvlCodePoint1;
    mySvcLvlProfileAid1=  theInst.mySvcLvlProfileAid1;
    mySvcLvlCodePoint2=   theInst.mySvcLvlCodePoint2;
    mySvcLvlProfileAid2=  theInst.mySvcLvlProfileAid2;
    mySvcLvlCodePoint3=   theInst.mySvcLvlCodePoint3;
    mySvcLvlProfileAid3=  theInst.mySvcLvlProfileAid3;
    mySvcLvlCodePoint4=   theInst.mySvcLvlCodePoint4;
    mySvcLvlProfileAid4=  theInst.mySvcLvlProfileAid4;
    mySvcLvlCodePoint5=   theInst.mySvcLvlCodePoint5;
    mySvcLvlProfileAid5=  theInst.mySvcLvlProfileAid5;
    mySvcLvlCodePoint6=   theInst.mySvcLvlCodePoint6;
    mySvcLvlProfileAid6=  theInst.mySvcLvlProfileAid6;
    mySvcLvlCodePoint7=   theInst.mySvcLvlCodePoint7;
    mySvcLvlProfileAid7=  theInst.mySvcLvlProfileAid7;
    mySvcLvlCodePoint8=   theInst.mySvcLvlCodePoint8;
    mySvcLvlProfileAid8=  theInst.mySvcLvlProfileAid8;
    mySvcLvlCodePoint9=   theInst.mySvcLvlCodePoint9;
    mySvcLvlProfileAid9=  theInst.mySvcLvlProfileAid9;
    mySvcLvlCodePoint10=   theInst.mySvcLvlCodePoint10;
    mySvcLvlProfileAid10=  theInst.mySvcLvlProfileAid10;

}

TL1_SlpolicyEdParameters::~TL1_SlpolicyEdParameters()
{
}

TL1_SlpolicyEdParameters& 
TL1_SlpolicyEdParameters::operator=( const TL1_SlpolicyEdParameters& theInst )
{
    myHandle=             theInst.myHandle;    
    myCtag=               theInst.myCtag;
    myPolicyName=         theInst.myPolicyName;
    mySvcLvlCodePoint1=   theInst.mySvcLvlCodePoint1;
    mySvcLvlProfileAid1=  theInst.mySvcLvlProfileAid1;
    mySvcLvlCodePoint2=   theInst.mySvcLvlCodePoint2;
    mySvcLvlProfileAid2=  theInst.mySvcLvlProfileAid2;
    mySvcLvlCodePoint3=   theInst.mySvcLvlCodePoint3;
    mySvcLvlProfileAid3=  theInst.mySvcLvlProfileAid3;
    mySvcLvlCodePoint4=   theInst.mySvcLvlCodePoint4;
    mySvcLvlProfileAid4=  theInst.mySvcLvlProfileAid4;
    mySvcLvlCodePoint5=   theInst.mySvcLvlCodePoint5;
    mySvcLvlProfileAid5=  theInst.mySvcLvlProfileAid5;
    mySvcLvlCodePoint6=   theInst.mySvcLvlCodePoint6;
    mySvcLvlProfileAid6=  theInst.mySvcLvlProfileAid6;
    mySvcLvlCodePoint7=   theInst.mySvcLvlCodePoint7;
    mySvcLvlProfileAid7=  theInst.mySvcLvlProfileAid7;
    mySvcLvlCodePoint8=   theInst.mySvcLvlCodePoint8;
    mySvcLvlProfileAid8=  theInst.mySvcLvlProfileAid8;
    mySvcLvlCodePoint9=   theInst.mySvcLvlCodePoint9;
    mySvcLvlProfileAid9=  theInst.mySvcLvlProfileAid9;
    mySvcLvlCodePoint10=  theInst.mySvcLvlCodePoint10;
    mySvcLvlProfileAid10= theInst.mySvcLvlProfileAid10;

    return *this;
}

bool 
TL1_SlpolicyEdParameters::operator==( const TL1_SlpolicyEdParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( !(myPolicyName == theInst.myPolicyName) )
        return false;

    if ( mySvcLvlCodePoint1 != theInst.mySvcLvlCodePoint1)
        return false;

    if ( mySvcLvlProfileAid1 != theInst.mySvcLvlProfileAid1)
        return false;

    if ( mySvcLvlCodePoint2 != theInst.mySvcLvlCodePoint2)
        return false;

    if ( mySvcLvlProfileAid2 != theInst.mySvcLvlProfileAid2)
        return false;

    if ( mySvcLvlCodePoint3 != theInst.mySvcLvlCodePoint3)
        return false;

    if ( mySvcLvlProfileAid3 != theInst.mySvcLvlProfileAid3)
        return false;

    if ( mySvcLvlCodePoint4 != theInst.mySvcLvlCodePoint4)
        return false;

    if ( mySvcLvlProfileAid4 != theInst.mySvcLvlProfileAid4)
        return false;

    if ( mySvcLvlCodePoint5 != theInst.mySvcLvlCodePoint5)
        return false;

    if ( mySvcLvlProfileAid5 != theInst.mySvcLvlProfileAid5)
        return false;
  
    if ( mySvcLvlCodePoint6 != theInst.mySvcLvlCodePoint6)
        return false;

    if ( mySvcLvlProfileAid6 != theInst.mySvcLvlProfileAid6)
        return false;

    if ( mySvcLvlCodePoint7 != theInst.mySvcLvlCodePoint7)
        return false;

    if ( mySvcLvlProfileAid7 != theInst.mySvcLvlProfileAid7)
        return false;

    if ( mySvcLvlCodePoint8 != theInst.mySvcLvlCodePoint8)
        return false;

    if ( mySvcLvlProfileAid8 != theInst.mySvcLvlProfileAid8)
        return false;

    if ( mySvcLvlCodePoint9 != theInst.mySvcLvlCodePoint9)
        return false;

    if ( mySvcLvlProfileAid9 != theInst.mySvcLvlProfileAid9)
        return false;

    if ( mySvcLvlCodePoint10 != theInst.mySvcLvlCodePoint10)
        return false;

    if ( mySvcLvlProfileAid10 != theInst.mySvcLvlProfileAid10)
        return false;

    return true;
}

