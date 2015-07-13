/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 17, 2009 - Ed Bandyk
DESCRIPTION:    Header file for TL1 Eqpt Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EQPTPARAMETERS_H__
#define __TL1_EQPTPARAMETERS_H__

#include <vector>
#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>

#include <vector>
using namespace std;


class TL1_EqptParameters  
{
public:
    
    TL1_EqptParameters();

    TL1_EqptParameters(CT_ProfileTableId*      theAlarmProfile,
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
                            CT_ConnPort*        theConnPort,
                            CT_ConnPortRange*   theConnPortRange,
							CT_CableLength*     theCableLength,
                            CT_SM_PST*          thePrimaryState,
                            CT_ModVersion*      theModVersion,
                            CT_PktShelfType*    thePktShelfType);

    virtual ~TL1_EqptParameters();

    TL1_EqptParameters& operator=( const TL1_EqptParameters& theBlock );

    bool operator==( const TL1_EqptParameters& theBlock ) const;

    inline void SetAlarmProfile(CT_ProfileTableId* theAlarmProfile);
    inline void SetName(CT_EqName* theName);
    inline void SetBand(CT_Band* theBand);
    inline void SetHalfBand(CT_HalfBand* theHalfBand);
    inline void SetChannel(CT_Wavelength* theChannel);
    inline void SetShelfName(CT_EqName* theShelfName);
    inline void SetPumpPower(CT_TL1_PumpPower* thePumpPower);
    inline void SetFunction(CT_Function* theFunction);
    inline void SetCapacity(CT_Capacity* theCapacity);
    inline void SetTimingMode(CT_TEL_TimingMode* theTimingMode);
    inline void SetNumberOfPorts(CT_NumberOfPort* theNumberOfPorts);
    inline void SetRate(CT_Rate* theRate);
    inline void SetOeoRegen(CT_OeoRegen* theOeoRegen);
    inline void SetInterconMode(CT_InterconMode* theInterconMode);
    inline void SetInterconModeDflt(CT_InterconMode* theInterconModeDflt);
    inline void SetWaitToRestoreTmr(CT_Timer* theWaitToRestoreTmr);
    inline void SetVcgTmr(CT_Timer* theVcgTmr);
    inline void SetDiffDelayThreashold(CT_Timer* theDiffDelayThreashold);
    void SetLacpSystemIdentifier(char* theIdentifier);
    inline void SetLacpSystemPriority(int* thePriority);
    inline void SetMount(CT_Mount* theMount);
    inline void SetNumbrChan(CT_NumberOfChan* theNumbrChan);
    inline void SetChanLimit(CT_NumberOfChan* theChanLimit);
    inline void SetChanRange(CT_ChanRange* theChanRange);
    inline void SetPreamp(CT_Preamp* thePreamp);
    inline void SetExtAttn(CT_Extattn* theExtAttn);
    inline void SetPostamp(CT_Postamp* thePostamp);
    inline void SetType(CT_Type* theType);
    inline void SetSwitchDomain(CT_SwitchDomain* theSwitchDomain);
    inline void SetReach(CT_Reach* theReach);
	inline void SetUsage(CT_Usage* theUsage);
    inline void SetPktShelfType(CT_PktShelfType* thePktShelfType);
    inline void SetConnPort(CT_ConnPort* theConnPort, CT_ConnPortRange* theRange);
	inline void SetCableLength(CT_CableLength* theCableLength);
    inline void SetPrimaryState(CT_SM_PST* thePrimaryState);
    inline void SetModVersion(CT_ModVersion* theModVersion);

    inline CT_ProfileTableId* GetAlarmProfile() const ;
    inline CT_EqName* GetName() const ;
    inline CT_Band* GetBand() const ;
    inline CT_HalfBand* GetHalfBand() const ;
    inline CT_Wavelength* GetChannel() const ;
    inline CT_EqName* GetShelfName() const ;
    inline CT_TL1_PumpPower* GetPumpPower() const ;
    inline CT_Function* GetFunction() const ;
    inline CT_Capacity* GetCapacity() const ;
    inline CT_TEL_TimingMode* GetTimingMode() const ;
    inline CT_NumberOfPort* GetNumberOfPorts() const ;
    inline CT_Rate* GetRate() const ;
    inline CT_OeoRegen* GetOeoRegen() const ;
    inline CT_InterconMode* GetInterconMode() const ;
    inline CT_InterconMode* GetInterconModeDflt() const ;
    inline CT_Timer* GetWaitToRestoreTmr() const ;
    inline CT_Timer* GetVcgTmr() const ;
    inline CT_Timer* GetDiffDelayThreashold() const ;
    inline char* GetLacpSystemIdentifier() const;
    inline int*  GetLacpSystemPriority() const;
    inline CT_Mount* GetMount() const ;
    inline CT_NumberOfChan* GetNumbrChan() const ;
    inline CT_NumberOfChan* GetChanLimit() const ;
    inline CT_ChanRange* GetChanRange() const ;
    inline CT_Preamp* GetPreamp() const ;
    inline CT_Extattn* GetExtAttn() const ;
    inline CT_Postamp* GetPostamp() const ;
    inline CT_Type* GetType() const ;
    inline CT_SwitchDomain* GetSwitchDomain() const ;
    inline CT_Reach* GetReach() const ;
	inline CT_Usage* GetUsage() const ;
    inline CT_PktShelfType* GetPktShelfType() const ;
    inline CT_ConnPort* GetConnPort() const;
    inline CT_ConnPortRange* GetConnPortRange() const;
	inline CT_CableLength* GetCableLength() const ;
    inline CT_SM_PST* GetPrimaryState() const ;
    inline CT_ModVersion* GetModVersion() const ;

private:

    CT_ProfileTableId*      myAlarmProfile;
    CT_EqName*              myName;
    CT_Band*                myBand;
    CT_HalfBand*            myHalfBand;
    CT_Wavelength*          myChannel;
    CT_EqName*              myShelfName;
    CT_TL1_PumpPower*       myPumpPower;
    CT_Function*            myFunction;
    CT_Capacity*            myCapacity;
    CT_TEL_TimingMode*      myTimingMode;
    CT_NumberOfPort*        myNumberOfPorts;
    CT_Rate*                myRate;
    CT_OeoRegen*            myOeoRegen;
    CT_InterconMode*        myInterconMode;
    CT_InterconMode*        myInterconModeDflt;
    CT_Timer*               myWaitToRestoreTmr;
    CT_Timer*               myVcgTmr;
    CT_Timer*               myDiffDelayThreashold;
    char*                   myLacpSystemIdentifier;
    int*                    myLacpSystemPriority;
    CT_Mount*               myMount;
    CT_NumberOfChan*        myNumbrChan;
    CT_NumberOfChan*        myChanLimit;
    CT_ChanRange*           myChanRange;
    CT_Preamp*              myPreamp;
    CT_Extattn*             myExtAttn;
    CT_Postamp*             myPostamp;
    CT_Type*                myType;
    CT_SwitchDomain*        mySwitchDomain;
    CT_Reach*               myReach;
	CT_Usage*               myUsage;
    CT_ConnPort*            myConnPort;
    CT_ConnPortRange*       myConnPortRange;
	CT_CableLength*         myCableLength;
    CT_SM_PST*              myPrimaryState;
    CT_ModVersion*          myModVersion;
    CT_PktShelfType*        myPktShelfType;
};

inline void TL1_EqptParameters::SetAlarmProfile(CT_ProfileTableId* theAlarmProfile){myAlarmProfile = theAlarmProfile;}
inline void TL1_EqptParameters::SetName(CT_EqName* theName){myName = theName;}
inline void TL1_EqptParameters::SetBand(CT_Band* theBand){myBand = theBand;}
inline void TL1_EqptParameters::SetHalfBand(CT_HalfBand* theHalfBand){myHalfBand = theHalfBand;}
inline void TL1_EqptParameters::SetChannel(CT_Wavelength* theChannel){myChannel = theChannel;}
inline void TL1_EqptParameters::SetShelfName(CT_EqName* theShelfName){myShelfName = theShelfName;}
inline void TL1_EqptParameters::SetPumpPower(CT_TL1_PumpPower* thePumpPower){myPumpPower = thePumpPower;}
inline void TL1_EqptParameters::SetFunction(CT_Function* theFunction){myFunction = theFunction;}
inline void TL1_EqptParameters::SetCapacity(CT_Capacity* theCapacity){myCapacity = theCapacity;}
inline void TL1_EqptParameters::SetTimingMode(CT_TEL_TimingMode* theTimingMode){myTimingMode = theTimingMode;}
inline void TL1_EqptParameters::SetNumberOfPorts(CT_NumberOfPort* theNumberOfPorts){myNumberOfPorts = theNumberOfPorts;}
inline void TL1_EqptParameters::SetRate(CT_Rate* theRate){myRate = theRate;}
inline void TL1_EqptParameters::SetOeoRegen(CT_OeoRegen* theOeoRegen){myOeoRegen = theOeoRegen;}
inline void TL1_EqptParameters::SetInterconMode(CT_InterconMode* theInterconMode){myInterconMode = theInterconMode;}
inline void TL1_EqptParameters::SetInterconModeDflt(CT_InterconMode* theInterconModeDflt){myInterconModeDflt = theInterconModeDflt;}
inline void TL1_EqptParameters::SetWaitToRestoreTmr(CT_Timer* theWaitToRestoreTmr){myWaitToRestoreTmr = theWaitToRestoreTmr;}
inline void TL1_EqptParameters::SetVcgTmr(CT_Timer* theVcgTmr){myVcgTmr = theVcgTmr;}
inline void TL1_EqptParameters::SetDiffDelayThreashold(CT_Timer* theDiffDelayThreashold){myDiffDelayThreashold = theDiffDelayThreashold;}
inline void TL1_EqptParameters::SetLacpSystemPriority(int* theLacpSystemPriority){myLacpSystemPriority = theLacpSystemPriority;}
inline void TL1_EqptParameters::SetMount(CT_Mount* theMount){myMount = theMount;}
inline void TL1_EqptParameters::SetNumbrChan(CT_NumberOfChan* theNumbrChan){myNumbrChan = theNumbrChan;}
inline void TL1_EqptParameters::SetChanLimit(CT_NumberOfChan* theChanLimit){myChanLimit = theChanLimit;}
inline void TL1_EqptParameters::SetChanRange(CT_ChanRange* theChanRange){myChanRange = theChanRange;}
inline void TL1_EqptParameters::SetPreamp(CT_Preamp* thePreamp){myPreamp = thePreamp;}
inline void TL1_EqptParameters::SetExtAttn(CT_Extattn* theExtAttn){myExtAttn = theExtAttn;}
inline void TL1_EqptParameters::SetPostamp(CT_Postamp* thePostamp){myPostamp = thePostamp;}
inline void TL1_EqptParameters::SetType(CT_Type* theType){myType = theType;}
inline void TL1_EqptParameters::SetSwitchDomain(CT_SwitchDomain* theSwitchDomain){mySwitchDomain = theSwitchDomain;}
inline void TL1_EqptParameters::SetReach(CT_Reach* theReach){myReach = theReach;}
inline void TL1_EqptParameters::SetUsage(CT_Usage* theUsage){myUsage = theUsage;}
inline void TL1_EqptParameters::SetPktShelfType(CT_PktShelfType* thePktShelfType){myPktShelfType = thePktShelfType;}
inline void TL1_EqptParameters::SetConnPort(CT_ConnPort* theConnPort, CT_ConnPortRange* theRange){myConnPort = theConnPort; 
                                                                                                  myConnPortRange=theRange;}
inline void TL1_EqptParameters::SetCableLength(CT_CableLength* theCableLength){myCableLength = theCableLength;}
inline void TL1_EqptParameters::SetPrimaryState(CT_SM_PST* thePrimaryState){myPrimaryState = thePrimaryState;}
inline void TL1_EqptParameters::SetModVersion(CT_ModVersion* theModVersion){myModVersion = theModVersion;}

inline CT_ProfileTableId* TL1_EqptParameters::GetAlarmProfile() const { return myAlarmProfile; }
inline CT_EqName* TL1_EqptParameters::GetName() const { return myName; }
inline CT_Band* TL1_EqptParameters::GetBand() const { return myBand; }
inline CT_HalfBand* TL1_EqptParameters::GetHalfBand() const { return myHalfBand; }
inline CT_Wavelength* TL1_EqptParameters::GetChannel() const { return myChannel; }
inline CT_EqName* TL1_EqptParameters::GetShelfName() const { return myShelfName; }
inline CT_TL1_PumpPower* TL1_EqptParameters::GetPumpPower() const { return myPumpPower; }
inline CT_Function* TL1_EqptParameters::GetFunction() const { return myFunction; }
inline CT_Capacity* TL1_EqptParameters::GetCapacity() const { return myCapacity; }
inline CT_TEL_TimingMode* TL1_EqptParameters::GetTimingMode() const { return myTimingMode; }
inline CT_NumberOfPort* TL1_EqptParameters::GetNumberOfPorts() const { return myNumberOfPorts; }
inline CT_Rate* TL1_EqptParameters::GetRate() const { return myRate; }
inline CT_OeoRegen* TL1_EqptParameters::GetOeoRegen() const { return myOeoRegen; }
inline CT_InterconMode* TL1_EqptParameters::GetInterconMode() const { return myInterconMode; }
inline CT_InterconMode* TL1_EqptParameters::GetInterconModeDflt() const { return myInterconModeDflt; }
inline CT_Timer* TL1_EqptParameters::GetWaitToRestoreTmr() const { return myWaitToRestoreTmr; }
inline CT_Timer* TL1_EqptParameters::GetVcgTmr() const { return myVcgTmr; }
inline CT_Timer* TL1_EqptParameters::GetDiffDelayThreashold() const { return myDiffDelayThreashold; }
inline char* TL1_EqptParameters::GetLacpSystemIdentifier() const { return myLacpSystemIdentifier; }
inline int* TL1_EqptParameters::GetLacpSystemPriority() const { return myLacpSystemPriority; }
inline CT_Mount* TL1_EqptParameters::GetMount() const { return myMount; }
inline CT_NumberOfChan* TL1_EqptParameters::GetNumbrChan() const { return myNumbrChan; }
inline CT_NumberOfChan* TL1_EqptParameters::GetChanLimit() const { return myChanLimit; }
inline CT_ChanRange* TL1_EqptParameters::GetChanRange() const { return myChanRange; }
inline CT_Preamp* TL1_EqptParameters::GetPreamp() const { return myPreamp; }
inline CT_Extattn* TL1_EqptParameters::GetExtAttn() const { return myExtAttn; }
inline CT_Postamp* TL1_EqptParameters::GetPostamp() const { return myPostamp; }
inline CT_Type* TL1_EqptParameters::GetType() const { return myType; }
inline CT_SwitchDomain* TL1_EqptParameters::GetSwitchDomain() const { return mySwitchDomain; }
inline CT_Reach* TL1_EqptParameters::GetReach() const { return myReach; }
inline CT_Usage* TL1_EqptParameters::GetUsage() const { return myUsage; }
inline CT_PktShelfType * TL1_EqptParameters::GetPktShelfType() const { return myPktShelfType; }
inline CT_ConnPort* TL1_EqptParameters::GetConnPort() const { return myConnPort; }
inline CT_ConnPortRange* TL1_EqptParameters::GetConnPortRange() const { return myConnPortRange; }
inline CT_CableLength* TL1_EqptParameters::GetCableLength() const { return myCableLength; }
inline CT_SM_PST* TL1_EqptParameters::GetPrimaryState() const { return myPrimaryState; }
inline CT_ModVersion* TL1_EqptParameters::GetModVersion() const { return myModVersion; }


//**************************************************************************************************************************************
class TL1_EqptValidateParameters  
{
public:

    enum ValidationParameters
    {
        AlarmProfileEditable = 0,
        EqNameEditable,
        BandEditable,
        HalfBandEditable,
        ChannelEditable,
        ShelfNameEditable,
        PumpPowerEditable,
        FunctionEditable,
        CapacityEditable,
        TimingModeEditable,
        NumberOfPortsEditable,
        RateEditable,
        OeoRegenEditable,
        InterconModeEditable,
        InterconModeDfltEditable,
        WaitToRestoreTmrEditable,
        VcgTmrEditable,
        DiffDelayThreasholdEditable,
        LacpSystemPriorityEditable,
        LacpSystemIdentifierEditable,
        MountEditable,
        NumbrChanEditable,
        ChanLimitEditable,
        ChanRangeEditable,
        PreampEditable,
        ExtAttnEditable,
        PostampEditable,
        TypeEditable,
        SwitchDomainEditable,
        ReachEditable,
        UsageEditable,
        CableLengthEditable,
        ConnPortEditable,
        ConnPortRangeEditable,
        PrimaryStateEditable,
        ModVersionEditable,
        PktShelfTypeEditable,
        AnyParameters               /* this should always be the last enum */
    };

    TL1_EqptValidateParameters();

    virtual ~TL1_EqptValidateParameters();

    void ValidateEdParameters( const TL1_EqptParameters& theParameters );
    void ValidateEntParameters( const TL1_EqptParameters& theParameters );

    inline vector<bool>& GetEdParametersSet();
    inline vector<bool>& GetEntParametersSet();

private:
    vector<bool>       myEdParametersSet;
    vector<bool>       myEntParametersSet;

    void ValidateParameters( const TL1_EqptParameters& theParameters, vector<bool>& theParametersSet ) const;
};

inline vector<bool>& TL1_EqptValidateParameters::GetEdParametersSet()
{
    return myEdParametersSet;
}

inline vector<bool>& TL1_EqptValidateParameters::GetEntParametersSet()
{
    return myEntParametersSet;
}

#endif
