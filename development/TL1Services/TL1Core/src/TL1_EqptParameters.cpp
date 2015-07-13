/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 17, 2009 - Ed Bandyk
DESCRIPTION:    Implementation file for TL1 Eqpt Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EQPTPARAMETERS_H__
#include <TL1Core/TL1_EqptParameters.h>
#endif

#include <CommonTypes/CT_TL1_Error.h>

TL1_EqptParameters::TL1_EqptParameters()
: myAlarmProfile(NULL), myName(NULL), myBand(NULL),myHalfBand(NULL),
myChannel(NULL), myShelfName(NULL), myPumpPower(NULL), myFunction(NULL), myCapacity(NULL),
myTimingMode(NULL), myNumberOfPorts(NULL), myRate(NULL), myOeoRegen(NULL), myInterconMode(NULL),
myInterconModeDflt(NULL), myWaitToRestoreTmr(NULL), myVcgTmr(NULL), myDiffDelayThreashold(NULL), myMount(NULL),
myNumbrChan(), myChanLimit(), myChanRange(), myPreamp(), myExtAttn(),
myPostamp(NULL), myType(NULL), mySwitchDomain(NULL), myReach(NULL), myUsage(NULL), myCableLength(NULL),
myConnPort(NULL), myConnPortRange(NULL), myPrimaryState(NULL),myLacpSystemIdentifier(NULL),myLacpSystemPriority(NULL),
myModVersion(NULL),myPktShelfType(NULL)
{
}

TL1_EqptParameters::TL1_EqptParameters(CT_ProfileTableId*      theAlarmProfile,
                                            CT_EqName*          theName,
                                            CT_Band*            theBand,
                                            CT_HalfBand*        theHalfBand,
                                            CT_Wavelength*      theChannel,
                                            CT_EqName*          theShelfName,
                                            CT_TL1_PumpPower*   thePumpPower,
                                            CT_Function*        theFunction,
                                            CT_Capacity*        theCapacity,
                                            CT_TEL_TimingMode*  theTimingMode,
                                            CT_NumberOfPort*    theNumberOfPorts,
                                            CT_Rate*            theRate,
                                            CT_OeoRegen*        theOeoRegen,
                                            CT_InterconMode*    theInterconMode,
                                            CT_InterconMode*    theInterconModeDflt,
                                            CT_Timer*           theWaitToRestoreTmr,
                                            CT_Timer*           theVcgTmr,
                                            CT_Timer*           theDiffDelayThreashold,
                                            int*                theLacpSystemPriority,
                                            char*               theLacpSystemIdentifier,
                                            CT_Mount*           theMount,
                                            CT_NumberOfChan*    theNumbrChan,
                                            CT_NumberOfChan*    theChanLimit,
                                            CT_ChanRange*       theChanRange,
                                            CT_Preamp*          thePreamp,
                                            CT_Extattn*         theExtAttn,
                                            CT_Postamp*         thePostamp,
                                            CT_Type*            theType,
                                            CT_SwitchDomain*    theSwitchDomain,
                                            CT_Reach*           theReach,
											CT_Usage*           theUsage,
                                            CT_CableLength*     theCableLength,
                                            CT_ConnPort*        theConnPort,
                                            CT_ConnPortRange*   theConnPortRange,
                                            CT_SM_PST*          thePrimaryState,
                                            CT_ModVersion*      theModVersion,
                                            CT_PktShelfType*    thePktShelfType)
: myAlarmProfile(NULL), myName(NULL), myBand(NULL),myHalfBand(NULL),
myChannel(NULL), myShelfName(NULL), myPumpPower(NULL), myFunction(NULL), myCapacity(NULL),
myTimingMode(NULL), myNumberOfPorts(NULL), myRate(NULL), myOeoRegen(NULL), myInterconMode(NULL),
myInterconModeDflt(NULL), myWaitToRestoreTmr(NULL), myVcgTmr(NULL), myDiffDelayThreashold(NULL),
myLacpSystemPriority(NULL),myLacpSystemIdentifier(theLacpSystemIdentifier),myMount(NULL),
myNumbrChan(NULL), myChanLimit(NULL), myChanRange(NULL), myPreamp(NULL), myExtAttn(NULL),
myPostamp(NULL), myType(NULL), mySwitchDomain(NULL), myReach(NULL), myUsage(NULL), myCableLength(NULL), 
myConnPort(NULL), myConnPortRange(NULL), myPrimaryState(NULL),myModVersion(NULL),myPktShelfType(NULL)
{
    if (theAlarmProfile)  
    {
        SetAlarmProfile(theAlarmProfile);
    }

    if (theName)  
    {
        myName = theName;
    }

    if (theBand)  
    {
        myBand = theBand;
    }

    if (theHalfBand)  
    {
        myHalfBand = theHalfBand;
    }

    if (theChannel)  
    {
        myChannel = theChannel;
    }

    if (theShelfName)  
    {
        myShelfName = theShelfName;
    }

    if (thePumpPower)  
    {
        myPumpPower = thePumpPower;
    }

    if (theFunction)  
    {
        myFunction = theFunction;
    }

    if (theCapacity)  
    {
        myCapacity = theCapacity;
    }

    if (theTimingMode)  
    {
        myTimingMode = theTimingMode;
    }

    if (theNumberOfPorts)  
    {
        myNumberOfPorts = theNumberOfPorts;
    }

    if (theRate)  
    {
        myRate = theRate;
    }

    if (theOeoRegen)  
    {
        myOeoRegen = theOeoRegen;
    }

    if (theInterconMode)  
    {
        myInterconMode = theInterconMode;
    }

    if (theInterconModeDflt)  
    {
        myInterconModeDflt = theInterconModeDflt;
    }

    if (theWaitToRestoreTmr)  
    {
        myWaitToRestoreTmr = theWaitToRestoreTmr;
    }

    if (theVcgTmr)  
    {
        myVcgTmr = theVcgTmr;
    }

    if (theDiffDelayThreashold)  
    {
        myDiffDelayThreashold = theDiffDelayThreashold;
    }

    if (theLacpSystemPriority)
    {
        myLacpSystemPriority = theLacpSystemPriority;
    }

    if (theLacpSystemIdentifier)
    {
        myLacpSystemIdentifier = theLacpSystemIdentifier;
    }

    if (theMount)  
    {
        myMount = theMount;
    }

    if (theNumbrChan)  
    {
        myNumbrChan = theNumbrChan;
    }

    if (theChanLimit)  
    {
        myChanLimit = theChanLimit;
    }

    if (theChanRange)  
    {
        myChanRange = theChanRange;
    }

    if (thePreamp)  
    {
        myPreamp = thePreamp;
    }

    if (theExtAttn)  
    {
        myExtAttn = theExtAttn;
    }

    if (thePostamp)  
    {
        myPostamp = thePostamp;
    }

    if (theType)  
    {
        myType = theType;
    }

    if (theSwitchDomain)  
    {
        mySwitchDomain = theSwitchDomain;
    }

    if (theReach)  
    {
        myReach = theReach;
    }

	if (theUsage)  
    {
        myUsage = theUsage;
    }

	if (theCableLength)  
    {
        myCableLength = theCableLength;
    }

    if (theConnPort)
    {
        myConnPort = theConnPort;
    }

    if (theConnPortRange)
    {
        myConnPortRange = theConnPortRange;
    }

    if (thePrimaryState)  
    {
        myPrimaryState = thePrimaryState;
    }

    if (theModVersion)  
    {
        myModVersion = theModVersion;
    }
    if (thePktShelfType) {
        myPktShelfType = thePktShelfType;
    }
}

TL1_EqptParameters::~TL1_EqptParameters()
{
}

TL1_EqptParameters& TL1_EqptParameters::operator=( const TL1_EqptParameters& theBlock )
{
    myAlarmProfile=         theBlock.myAlarmProfile;
    myName=                 theBlock.myName;
    myBand=                 theBlock.myBand;
    myHalfBand=             theBlock.myHalfBand;
    myChannel=              theBlock.myChannel;
    myShelfName=            theBlock.myShelfName;
    myPumpPower=            theBlock.myPumpPower;
    myFunction=             theBlock.myFunction;
    myCapacity=             theBlock.myCapacity;
    myTimingMode=           theBlock.myTimingMode;
    myNumberOfPorts=        theBlock.myNumberOfPorts;
    myRate=                 theBlock.myRate;
    myOeoRegen=             theBlock.myOeoRegen;
    myInterconMode=         theBlock.myInterconMode;
    myInterconModeDflt=     theBlock.myInterconModeDflt;
    myWaitToRestoreTmr=     theBlock.myWaitToRestoreTmr;
    myVcgTmr=               theBlock.myVcgTmr;
    myDiffDelayThreashold=  theBlock.myDiffDelayThreashold;
    myLacpSystemIdentifier= theBlock.myLacpSystemIdentifier;
    myLacpSystemPriority=   theBlock.myLacpSystemPriority;
    myMount=                theBlock.myMount;
    myNumbrChan=            theBlock.myNumbrChan;
    myChanLimit=            theBlock.myChanLimit;
    myChanRange=            theBlock.myChanRange;
    myPreamp=               theBlock.myPreamp;
    myExtAttn=              theBlock.myExtAttn;
    myPostamp=              theBlock.myPostamp;
    myType=                 theBlock.myType;
    mySwitchDomain=         theBlock.mySwitchDomain;
    myReach=                theBlock.myReach;
	myUsage=                theBlock.myUsage;
	myCableLength=          theBlock.myCableLength;
    myConnPort=             theBlock.myConnPort;
    myConnPortRange=        theBlock.myConnPortRange;
    myPrimaryState=         theBlock.myPrimaryState;
    myModVersion=           theBlock.myModVersion;
    myPktShelfType=         theBlock.myPktShelfType;

    return *this;
}

bool TL1_EqptParameters::operator==( const TL1_EqptParameters& theBlock ) const
{
     return ( myAlarmProfile          == theBlock.myAlarmProfile &&
                myName                  == theBlock.myName &&
                myBand                  == theBlock.myBand &&
                myHalfBand              == theBlock.myHalfBand &&
                myChannel               == theBlock.myChannel &&
                myShelfName             == theBlock.myShelfName &&
                myPumpPower             == theBlock.myPumpPower &&
                myFunction              == theBlock.myFunction &&
                myCapacity              == theBlock.myCapacity &&
                myTimingMode            == theBlock.myTimingMode &&
                myNumberOfPorts         == theBlock.myNumberOfPorts &&
                myRate                  == theBlock.myRate &&
                myOeoRegen              == theBlock.myOeoRegen &&
                myInterconMode          == theBlock.myInterconMode &&
                myInterconModeDflt      == theBlock.myInterconModeDflt &&
                myWaitToRestoreTmr      == theBlock.myWaitToRestoreTmr &&
                myVcgTmr                == theBlock.myVcgTmr &&
                myDiffDelayThreashold   == theBlock.myDiffDelayThreashold &&
                myLacpSystemIdentifier  == theBlock.myLacpSystemIdentifier &&
                myLacpSystemPriority    == theBlock.myLacpSystemPriority &&
                myMount                 == theBlock.myMount &&
                myNumbrChan             == theBlock.myNumbrChan &&
                myChanLimit             == theBlock.myChanLimit &&
                myChanRange             == theBlock.myChanRange &&
                myPreamp                == theBlock.myPreamp &&
                myExtAttn               == theBlock.myExtAttn &&
                myPostamp               == theBlock.myPostamp &&
                myType                  == theBlock.myType &&
                mySwitchDomain          == theBlock.mySwitchDomain &&
                myReach                 == theBlock.myReach &&
				myUsage                 == theBlock.myUsage &&
				myCableLength           == theBlock.myCableLength &&
                myConnPort              == theBlock.myConnPort &&
                myConnPortRange         == theBlock.myConnPortRange &&
                myPrimaryState          == theBlock.myPrimaryState &&
                myModVersion            == theBlock.myModVersion  &&
                myPktShelfType          == theBlock.myPktShelfType );
}

void TL1_EqptParameters::SetLacpSystemIdentifier(char* theSystemIdentifier)
{
    myLacpSystemIdentifier = theSystemIdentifier;
}

//*******************************************************************************************************************************************
TL1_EqptValidateParameters::TL1_EqptValidateParameters( ) :
    myEdParametersSet( (int)AnyParameters + 1, false ),
    myEntParametersSet( (int)AnyParameters + 1, false )
{
}

TL1_EqptValidateParameters::~TL1_EqptValidateParameters( )
{
}

void TL1_EqptValidateParameters::ValidateEdParameters( const TL1_EqptParameters& theParameters )
{
    ValidateParameters(theParameters, myEdParametersSet);
}

void TL1_EqptValidateParameters::ValidateEntParameters( const TL1_EqptParameters& theParameters )
{
    ValidateParameters(theParameters, myEntParametersSet);
}

void TL1_EqptValidateParameters::ValidateParameters( const TL1_EqptParameters& theParameters, vector<bool>& theParametersSet ) const
{

    if ( true == theParametersSet[AnyParameters] )
    {
        return;
    }

    if ( ( false == theParametersSet[AlarmProfileEditable] ) &&
         ( theParameters.GetAlarmProfile() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[EqNameEditable] ) &&
         ( theParameters.GetName() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[BandEditable] ) &&
         ( theParameters.GetBand() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[HalfBandEditable] ) &&
         ( theParameters.GetHalfBand() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ChannelEditable] ) &&
         ( theParameters.GetChannel() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ShelfNameEditable] ) &&
         ( theParameters.GetShelfName() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[PumpPowerEditable] ) &&
         ( theParameters.GetPumpPower() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[FunctionEditable] ) &&
         ( theParameters.GetFunction() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[CapacityEditable] ) &&
         ( theParameters.GetCapacity() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[TimingModeEditable] ) &&
         ( theParameters.GetTimingMode() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[NumberOfPortsEditable] ) &&
         ( theParameters.GetNumberOfPorts() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[RateEditable] ) &&
         ( theParameters.GetRate() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[OeoRegenEditable] ) &&
         ( theParameters.GetOeoRegen() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[InterconModeEditable] ) &&
         ( theParameters.GetInterconMode() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    
    if ( ( false == theParametersSet[InterconModeDfltEditable] ) &&
         ( theParameters.GetInterconModeDflt() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[WaitToRestoreTmrEditable] ) &&
         ( theParameters.GetWaitToRestoreTmr() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[VcgTmrEditable] ) &&
         ( theParameters.GetVcgTmr() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[DiffDelayThreasholdEditable] ) &&
         ( theParameters.GetDiffDelayThreashold() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[LacpSystemPriorityEditable] ) &&
         ( theParameters.GetLacpSystemPriority() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if((false == theParametersSet[LacpSystemIdentifierEditable]) &&
       (theParameters.GetLacpSystemIdentifier()))
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if((false == theParametersSet[MountEditable]) &&
       (theParameters. GetMount()))
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[NumbrChanEditable] ) &&
         ( theParameters.GetNumbrChan() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ChanLimitEditable] ) &&
         ( theParameters.GetChanLimit() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ChanRangeEditable] ) &&
         ( theParameters.GetChanRange() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[PreampEditable] ) &&
         ( theParameters.GetPreamp() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ExtAttnEditable] ) &&
         ( theParameters.GetExtAttn() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[PostampEditable] ) &&
         ( theParameters.GetPostamp() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[TypeEditable] ) &&
         ( theParameters.GetType() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[SwitchDomainEditable] ) &&
         ( theParameters.GetSwitchDomain() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ReachEditable] ) &&
         ( theParameters.GetReach() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[UsageEditable] ) &&
         ( theParameters.GetUsage() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[CableLengthEditable] ) &&
         ( theParameters.GetCableLength() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ConnPortEditable] ) &&
         ( theParameters.GetConnPort() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ConnPortRangeEditable] ) &&
         ( theParameters.GetConnPortRange() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[PrimaryStateEditable] ) &&
         ( theParameters.GetPrimaryState() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == theParametersSet[ModVersionEditable] ) &&
         ( theParameters.GetModVersion() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == theParametersSet[PktShelfTypeEditable] ) &&
         ( theParameters.GetPktShelfType() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
}


