/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 19, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Equipment Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EQPTENTITY_H__
#define __TL1_EQPTENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_EQPTDOMAIN_H__
#include <TL1Core/TL1_EqptDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <gdef.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>

#ifndef __CT_EQUIPMENT_H__
#include <CommonTypes/CT_Equipment.h>
#endif

#include <CommonTypes/CT_AG_PortId.h>
#include <TL1Core/TL1_EqptParameters.h>

class TL1_Response;
class CT_Wavelength;

class TL1_EquipmentEntity : public TL1_Entity,     // Base Class
                            public TL1_EqptDomain,  // Protocol Class
                            public TL1_AlarmDomain, // Protocol Class
                            public TL1_EqptValidateParameters
{
public:    
    TL1_EquipmentEntity();

    virtual ~TL1_EquipmentEntity();
  
};



class Card_CapabilityMatrix
{
public :
    virtual ~Card_CapabilityMatrix();

    static const Card_CapabilityMatrix& GetInstance();

    bool IsEnterable(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsEditable(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsRmvable(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsFpgaRetrievable (CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsSwitchable(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsInitializable(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsAMSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsDiagSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsLedSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsPmSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool IsArcSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const;

private:
    struct Card_Capability
    {
        bool myEnterable;
        bool myEditable;
        bool myRmvable;
        bool myFpgaRetrievable;
        bool mySwitchable;
        bool myInitializable;
        bool myAMSupported;
        bool myDiagSupported;
        bool myLedSupported;
        bool myIsPmSupported;
        bool myIsArcSupported;
    };
    
    Card_CapabilityMatrix();

    static Card_CapabilityMatrix *myInstance;

    static Card_Capability        myMatrix[CARD_TYPE_MAX];
};

class Card_EnterParameterMatrix
{
public :
    virtual ~Card_EnterParameterMatrix();

    static const Card_EnterParameterMatrix& GetInstance();
    bool            isBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isHalfBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChannel(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPumpPower(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isFunction(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isRate(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChanRange(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
private:
    struct Card_EnterParameter //copy from TL1_EqptDomain::EntEqpt
    {  //supported on all cards
       //bool        myAddr,
       //bool        myAlarmProfile,
       //bool        myName,
       bool           myBand;
       bool           myHalfBand;
       bool           myChannel;
       //supported on all cards
       //bool      myShelfName;
       bool           myPumpPower;
       bool           myFunction;
       bool           myCapacity;
       bool           myTimingMode;
       bool           myNumberOfPorts;
       bool           myRate;
       bool           myOeoRegen;
       bool           myInterconMode;
       //supported on shelf only
       //bool         myInterconModeDflt;
       bool           myWaitToRestoreTmr;
       bool           myVcgTmr;
       bool           myDiffDelayThreashold;
       //supported on shelf only
       //bool          myMount;
       bool           myNumbrChan;
       bool           myChanLimit;
       bool           myChanRange;
       bool           myPreamp;
       bool           myExtAttn;
       bool           myPostamp;
       //supported on shelf only
       //bool           myType;
       //bool         mySwitchDomain;
       //supported on all cards
       //bool          myPrimaryState;
};

    Card_EnterParameterMatrix();
    static Card_EnterParameterMatrix *myInstance;
    static Card_EnterParameter myMatrix[CARD_TYPE_MAX];
};

class Card_EditParameterMatrix
{
public :
    virtual ~Card_EditParameterMatrix();

    static const Card_EditParameterMatrix& GetInstance();
    bool            isCommandMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isCardType(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
private:
    struct Card_EditParameter //copy from TL1_EqptDomain::EdEqpt
    {    //supported on all cards
        //bool                 myAddr;
        bool                   myCommandMode;
        //supported on all cards
        //bool                 myAlarmProfile;
        //bool                 myName;
        //supported on shelf only
        //bool                 myShelfName;
        bool                   myCapacity;
        bool                   myTimingMode;
        bool                   myCardType;
        bool                   myOeoRegen;
        //supported on all cards
        //bool                 myPrimaryState;
        bool                   myNumberOfPorts;
        bool                   myInterconMode;
        //supported on shelf only
        //bool                 myInterconModeDflt;
        bool                   myWaitToRestoreTmr;
        bool                   myVcgTmr;
        bool                   myDiffDelayThreashold;
        //supported on shelf only
        //bool                 myMount;
        bool                   myNumbrChan;
        bool                   myChanLimit;
        bool                   myPreamp;
        bool                   myExtAttn;
        bool                   myPostamp;
};

    Card_EditParameterMatrix();
    static Card_EditParameterMatrix *myInstance;
    static Card_EditParameter myMatrix[CARD_TYPE_MAX];
};

class Card_RtrvParameterMatrix
{
public :
    virtual ~Card_RtrvParameterMatrix();

    static const Card_RtrvParameterMatrix& GetInstance();
    bool            isBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isHalfBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPumpPower(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isWave(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isID(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isFunction(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isRate(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isChanRange(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isLength(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isFiberType(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isIL(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const;
    bool            isSwitchMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const;

private:
    struct Card_RtrvParameter //copy from TL1_EQRspBlk.
    {     
        //supported by all cards
        //bool        myEntityName;
        //bool        mySlotAddr;
        //bool        myCardType;
        //bool        mySubCardType;
        //bool        myCardName;
        bool            myBand;
        bool            myHalfBand;
        bool            myPumpPower;
        bool            myWave;
        //supported by shelf only
        //bool          myShelfType;
        //bool          myShelfName;
        bool            myID;
        bool            myFunction;
        bool            myCapacity;
        bool            myTimingMode;
        bool            myNumberOfPort;
        bool            myRate;
        bool            myOeoRegen;
        bool            myInterconMode;
        //supported by shelf only
        //bool          myInterconModeDflt;
        //bool          myMount;
        //bool          myPktEquip;
        //supported by all cards
        //bool          myPST;
        //bool          myPSTQ;
        //bool          mySST;
        bool            myWaitToRestoreTmr;
        bool            myVcgTmr;
        bool            myDiffDelayThreashold;
        bool            myNumbrChan;
        bool            myChanLimit;
        bool            myChanRange;
        bool            myLength;
        bool            myFiberType;
        bool            myIL;
        bool            myPreamp;
        bool            myExtAttn;
        bool            myPostamp;
        //supported by shelf only
        //bool          mySwitchDomain;
        bool            mySwitchMode;
    };

    Card_RtrvParameterMatrix();
    static Card_RtrvParameterMatrix *myInstance;
    static Card_RtrvParameter myMatrix[CARD_TYPE_MAX];
};

class Card_LedParameterMatrix
{
public :
    virtual ~Card_LedParameterMatrix();

    static const Card_LedParameterMatrix& GetInstance();

    bool isActiveLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isPowerLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isFaultLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isActLineLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isLineLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isExpressLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isPortLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isPortXLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isInputLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isLpbkLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isSyncLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isOscLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isNeCrLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isNeMjLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isNeMnLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isOcpXLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isAprLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isDWDM44Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isDWDM45Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isDWDM1Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isDWDM2Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isBitsLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;
    bool isPII_AlarmCutOffLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const;

private:
    struct Card_LedParameter
    {    
        bool myActiveLed;
        bool myPowerLed;
        bool myFaultLed;
        bool mySyncLed;
        bool myNeCrLed;
        bool myNeMjLed;
        bool myNeMnLed;
        bool myActLineLed;
        bool myLineLed;
        bool myPortLed;
        bool myPortXLed;
        bool myOscLed;
        bool myExpressLed;
        bool myAprLed;
        bool myInputLed;
        bool myLpbkLed;
        bool myDWDM44Led;
        bool myDWDM45Led;
        bool myDWDM1Led;
        bool myDWDM2Led;
        bool myOcpXLed;
        bool myBitsLed;
        bool myPII_AlarmCutOffLed;
    };

    Card_LedParameterMatrix();
    static Card_LedParameterMatrix *myInstance;
    static Card_LedParameter myMatrix[CARD_TYPE_MAX];
};



#endif

