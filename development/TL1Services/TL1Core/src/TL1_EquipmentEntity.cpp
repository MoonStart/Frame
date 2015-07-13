/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 20, 2003- Jean-Francois Tremblay
DESCRIPTION:    Implementation file for TL1 Equipment Entity Base class
-----------------------------------------------------------------------------*/ 

#include "../TL1_EquipmentEntity.h"



//--------------------------------------------------------------------------
TL1_EquipmentEntity::TL1_EquipmentEntity()
{
}

//--------------------------------------------------------------------------
TL1_EquipmentEntity::~TL1_EquipmentEntity()
{
}

Card_CapabilityMatrix *Card_CapabilityMatrix::myInstance = NULL;


Card_CapabilityMatrix::Card_Capability Card_CapabilityMatrix::myMatrix[CARD_TYPE_MAX] =
{
//   Enter      Edit      Rmv      Fpga      Switch      InitSys      AM      Diag      LED      PM      Arc             CardType      TL1EntityName
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 0    UNKNOWN      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 1    BMM1_3       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 2    BMM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 3    BPM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 4    FCMM1_3      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 5    ECMM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 6    FCMM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 7    IAM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 8    NIAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 9    NOAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 10   OAM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 11   MIAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 12   MOAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 13   RIAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 14   OLIM1_3      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 15   OLIM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 16   OSC          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 17   OSC8250      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 18   APM8250      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 19   PM           UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 20   QUAD1_3      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 21   QUAD         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 22   SCAD1_3      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 23   SCAD         UNKNOWN
    {true,      true,     true,    true,     false,      true,        true,   true,     false,   true,   true},  // 24   TRN_2R       BBTM
    {true,      true,     true,    true,     false,      true,        true,   true,     false,   true,   true},  // 25   TRN_3R       STTM
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 26   TRN_10G      TGTM
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 27   TRN_MRTM     MRTM/MRTMT
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 28   FILLER       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 29   OFM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 30   BFM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 31   FAN          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 32   CPM1_3       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 33   CPM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 34   PSM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 35   AIP          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 36   SHELF        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 37   SFPEL        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 38   RAM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 39   SMTMA        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 40   OPSM         UNKNOWN
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 41   TRN_10GT     TGTMT
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 42   DCMM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 43   RCMM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 44   LIAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 45   LOAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 46   LRAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 47   SMTMM        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 48   SPM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 49   OBM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 50   SMTMU        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 51   SMTMSD       UNKNOWN
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 52   TRN_MRTMT    MRTME/MRTMS        
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 53   LIAME        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 54   LOAME        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 55   LRAME        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 56   SPM8560      UNKNOWN
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 57   TRN_10GTE    TGTME  
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 58   SFP          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 59   SMTMUD       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 60   ELRAME       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 61   EMOAM        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 62   TGIME        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 63   CMM44        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 64   RCMMS        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 65   RCMMS44      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 66   SPFAB        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 67   DPM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 68   URAM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 69   MRCMMCX8     UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 70   SMTMULX      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 71   SMTMP        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 72   TGIMP        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 73   TGIMELX      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 74   SPMNANO      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 75   CCMIR        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 76   CCMLR        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 77   CCMER        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 78   OLAIR        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 79   OLALR        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 80   OLAER        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 81   AIM          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 82   HDPCT        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 83   HDPP         UNKNOWN
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    true,   true},  // 84   FGTM         FGTM
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 85   SPM8547      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 86   OTNMD        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 87   OTNMX        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 88   SSMX         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 89   SSMD         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 90   FGTMM        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 91   DCMM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 92   OMD          UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 93   UFAB         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 94   SPMH         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 95   CCM88IR      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 96   CCM88LR      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 97   CCM88ER      UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 98   OADM88IR     UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 99   OADM88LR     UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 100  OADM88ER     UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 101  OTSM         UNKNOWN
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 102  OSM40        OSM40
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 103  HDTG         UNKNOWN
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 104  SSM40        SSM40
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 105  ESIM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 106  ESM40        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 107  ESM20        UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 108  SPMC         UNKNOWN
    {true ,     true ,    true ,   true ,    false,      false,       true ,  true ,    true ,   false , false}, // 109  FGSM         copy from OSM40
    {false,     false,    false,   false,    false,      false,       false,  false,    true ,   false,  false}, // 110  HGTM         UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 111  OADM88IR8D   UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 112  OADM88LR8D   UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 113  OADM88ER8D   UNKNOWN                                                                                                                
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 114  OSM20        OSM20
    {true,      true,     true,    true,     false,      true,        true,   true,     true,    false,   true}, // 115  FGTME        FGTME
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 116  DXOADM       UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 117  OADMF8IR     UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 118  OADMF8LR     UNKNOWN
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 119  OMMXP, copied from OMMX
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   true ,  false}, // 120  SMTMUX       UNKNOWN                                                                                                                 
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 121  OMMX, copied from OSM20
    {false,     false,    false,   false,    false,      false,       false,  false,    true,    false,  false}, // 122  HGTM-M       UNKNOWN
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 123  OSM2S,       TODO..
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 124  OSM2C,       TODO..
    {true,      true,     false,   false,    false,      false,       false,  false,    false,   false,  false}, // 125  STPM         TODO       
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 126  STIM         TODO   
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 127  SAIM         TODO   
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 128  SEIM         TODO   
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 129  MFAB         copied from SPFAB
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 130  MBFM         TODO   
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 131  MSFM         TODO   
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 132  UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 133  UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 134  UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 135  UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 136   UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 137   UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    true ,   false,  false}, // 138  HGTMS
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 139  UNKNOWN
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}, // 140  UNKNOWN
    {true,      true,     true,    true,     false,      false,       true,   true,     true,    false,  false}, // 141  OMMX83, copied from OMMXP
    {false,     false,    false,   false,    false,      false,       false,  false,    false,   false,  false}  // 142  ALL          ALL    
//   Enter      Edit      Rmv      Fpga      Switch      InitSys      AM      Diag      LED      PM      Arc      CardType      TL1EntityName
};

//--------------------------------------------------------------------------
Card_CapabilityMatrix::Card_CapabilityMatrix()
{

}

//--------------------------------------------------------------------------
Card_CapabilityMatrix::~Card_CapabilityMatrix()
{

}

//--------------------------------------------------------------------------
const Card_CapabilityMatrix& Card_CapabilityMatrix::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new Card_CapabilityMatrix();

    return *myInstance;
}

//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsEnterable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myEnterable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsEditable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myEditable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsRmvable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myRmvable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsFpgaRetrievable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myFpgaRetrievable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsSwitchable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].mySwitchable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsInitializable(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myInitializable;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsAMSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myAMSupported;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsDiagSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myDiagSupported;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsLedSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myLedSupported;
}
//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsPmSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myIsPmSupported;
}

//--------------------------------------------------------------------------
bool Card_CapabilityMatrix::IsArcSupported(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myIsArcSupported;
}
//=======================================================================================================
Card_EnterParameterMatrix *Card_EnterParameterMatrix::myInstance = NULL;


Card_EnterParameterMatrix::Card_EnterParameter Card_EnterParameterMatrix::myMatrix[CARD_TYPE_MAX] =
{
//   Band     HalfBand     Channel     PumpPower     Function     Capacity      TMG      NumOfPort      Rate      Oeo      IntMode      WTR      VcgTmr      DDThr      NumbOfChan      ChanLimit      ChanRange      PreAmp      ExtAttn      PostAmp      CardType      TL1EntityName
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 0    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 1    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 2    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 3    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 4    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 5    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 6    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 7    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 8    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 9    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 10   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 11   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 12   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 13   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 14   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 15   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 16   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 17   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 18   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 19   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 20   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 21   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 22   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 23   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 24   TRN_2R       BBTM
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 25   TRN_3R       STTM
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 26   TRN_10G      TGTM
    {false,     true,      false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 27   TRN_MRTM     MRTM/MRTMT
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 28   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 29   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 30   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 31   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 32   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 33   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 34   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 35   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 36   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 37   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 38   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 39   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 40   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 41   TRN_10GT     TGTMT
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 42   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 43   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 44   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 45   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 46   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 47   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 48   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 49   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 50   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 51   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 52   TRN_MRTMT    MRTME/MRTMS        
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 53   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 54   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 55   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 56   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 57   TRN_10GTE    TGTME  
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 58   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 59   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 60   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 61   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 62   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 63   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 64   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 65   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 66   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 67   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 68   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 69   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 70   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 71   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 72   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 73   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 74   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 75   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 76   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 77   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 78   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 79   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 80   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 81   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 82   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 83   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 84   FGTM         FGTM
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 85   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 86   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 87   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 88   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 89   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 90   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 91   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 92   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 93   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 94   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 95   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 96   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 97   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 98   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 99   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 100  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 101  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 102  OSM40        OSM40(copied from TRN_10GTE)  
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 103  HDTG         UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 104  SSM40        UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 105  ESIM         ESIM
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 106  ESM40        UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 107  ESM20        ESM20
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 108  SPMC         SPMC
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 109  FGSM         copy from OSM40
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 110  HGTM         UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 111  OADM88IR8D   UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 112  OADM88LR8D   UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 113  OADM88ER8D   UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 114  OSM20        OSM40(copied from TRN_10GTE)  
    {false,     false,     false,        true,       false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 115  FGTME        copy from FGTM
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 116  DXOADM       UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 117  OADMF8IR     UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 118  OADMF8LR     UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 119  OMMXP, copied from OMMX
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 120  SMTMUX       UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 121  OMMX, copied from OSM20  
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 122  HGTM-M         UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 123  OSM2S, TODO..
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 124  OSM2C, TODO..
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 125  STPM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 126  STIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 127  SAIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 128  SEIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 129  MFAB         UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 130  MBFM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 131  MSFM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 132  OADM8DSIR    UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 133  OADM8DSLR    UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 134  OADM8DSER    UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 135  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 136  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 137  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 138  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 139  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 140  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}, // 141  OMMX83       OMMX83

    {false,     false,     false,        false,      false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false}  // 142  ALL          ALL
//   Band     HalfBand     Channel     PumpPower     Function     Capacity      TMG      NumOfPort      Rate      Oeo      IntMode      WTR      VcgTmr      DDThr      NumbOfChan      ChanLimit      ChanRange      PreAmp      ExtAttn      PostAmp      CardType      TL1EntityName
};

//--------------------------------------------------------------------------
Card_EnterParameterMatrix::Card_EnterParameterMatrix()
{

}

//--------------------------------------------------------------------------
Card_EnterParameterMatrix::~Card_EnterParameterMatrix()
{

}

//--------------------------------------------------------------------------
const Card_EnterParameterMatrix& Card_EnterParameterMatrix::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new Card_EnterParameterMatrix();

    return *myInstance;
}

bool Card_EnterParameterMatrix::isBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myBand;
}
bool Card_EnterParameterMatrix::isHalfBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    if (theCardType == TRN_MRTM && theSubCardType == TRN_44_TUNABLE) //MRTMT
    {
        return false;
    }
    return myMatrix[theCardType].myHalfBand;
}
bool Card_EnterParameterMatrix::isPumpPower(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPumpPower;
}
bool Card_EnterParameterMatrix::isChannel(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChannel;
}
bool Card_EnterParameterMatrix::isFunction(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myFunction;
}
bool Card_EnterParameterMatrix::isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myCapacity;
}
bool Card_EnterParameterMatrix::isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myTimingMode;
}
bool Card_EnterParameterMatrix::isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumberOfPorts;
}
bool Card_EnterParameterMatrix::isRate(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myRate;
}
bool Card_EnterParameterMatrix::isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myOeoRegen;
}
bool Card_EnterParameterMatrix::isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myInterconMode;
}
bool Card_EnterParameterMatrix::isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myWaitToRestoreTmr;
}
bool Card_EnterParameterMatrix::isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myVcgTmr;
}
bool Card_EnterParameterMatrix::isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myDiffDelayThreashold;
}
bool Card_EnterParameterMatrix::isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumbrChan;
}
bool Card_EnterParameterMatrix::isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChanLimit;
}
bool Card_EnterParameterMatrix::isChanRange(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChanRange;
}
bool Card_EnterParameterMatrix::isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPreamp;
}
bool Card_EnterParameterMatrix::isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myExtAttn;
}
bool Card_EnterParameterMatrix::isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPostamp;
}
//=======================================================================================================
Card_EditParameterMatrix *Card_EditParameterMatrix::myInstance = NULL;


Card_EditParameterMatrix::Card_EditParameter Card_EditParameterMatrix::myMatrix[CARD_TYPE_MAX] =
{
//   CmdMde     Capacity      TMG      CardType      Oeo      NumOfPort      IntMode      WTR        VcgTmr      DDThr      NumbOfChan      ChanLimit      PreAmp      ExtAttn      PostAmp      CardType      TL1EntityName
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 0    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 1    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 2    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 3    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 4    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 5    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 6    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 7    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 8    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 9    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 10   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 11   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 12   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 13   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 14   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 15   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 16   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 17   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 18   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 19   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 20   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 21   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 22   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 23   UNKNOWN      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 24   TRN_2R       BBTM
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 25   TRN_3R       STTM
    {true,      false,     false,        true,       false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 26   TRN_10G      TGTM
    {true,      false,     false,        true,       false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 27   TRN_MRTM     MRTM/MRTMT
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 28   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 29   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 30   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 31   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 32   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 33   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 34   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 35   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 36   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 37   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 38   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 39   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 40   UNKNOWN      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 41   TRN_10GT     TGTMT
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 42   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 43   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 44   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 45   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 46   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 47   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 48   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 49   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 50   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 51   UNKNOWN      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 52   TRN_MRTMT    MRTME/MRTMS        
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 53   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 54   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 55   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 56   UNKNOWN      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 57   TRN_10GTE    TGTME  
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 58   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 59   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 60   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 61   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 62   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 63   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 64   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 65   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 66   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 67   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 68   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 69   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 70   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 71   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 72   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 73   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 74   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 75   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 76   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 77   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 78   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 79   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 80   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 81   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 82   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 83   UNKNOWN      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 84   FGTM         FGTM
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 85   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 86   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 87   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 88   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 89   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 90   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 91   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 92   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 93   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 94   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 95   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 96   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 97   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 98   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 99   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 100  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 101  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 102  OSM40        OSM40
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 103  SSM40        SSM40
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 104  HDTG      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 105  ESIM      ESIM
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 106  ESM40      ESM40
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 107  ESM20      ESM20
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 108  SPMC         SPMC
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 109  FGSM         FGSM
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 110  HGTM         
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 111  OADM88IR8D         
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 112  OADM88LR8D
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 113  OADM88ER8D
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 114  OSM20
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 115  FGTME        FGTME
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 116  DXOADM      DXOADM
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 117  OADMF8IR      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 118  OADMF8LR      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 119  OMMXP
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 120  SMTMUX      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 121  OMMX
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 122  HGTM-M      UNKNOWN
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 123  OSM2S, TODO..
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 124  OSM2C, TODO..
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 125  STPM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 126  STIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 127  SAIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 128  SEIM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 129  MFAB         UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 130  MBFM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 131  MSFM TODO
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 132  OADM8DSIR         
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 133  OADM8DSLR
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 134  OADM8DSER
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 135   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 136   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 137   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 138  HGTMS         // Coriant lhu
    {true,      false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 139  HGTM-MS      UNKNOWN // Coriant lhu
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 140  UNKNOWN
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}, // 141  OMMX83
    
    {false,     false,     false,        false,      false,       false,        false,   false,      false,      false,     false,          false,         false,      false,       false}  // 142  ALL          ALL
//   CmdMde     Capacity      TMG      CardType      Oeo      NumOfPort      IntMode      WTR        VcgTmr      DDThr      NumbOfChan      ChanLimit      PreAmp      ExtAttn      PostAmp      CardType      TL1EntityName
};

//--------------------------------------------------------------------------
Card_EditParameterMatrix::Card_EditParameterMatrix()
{

}

//--------------------------------------------------------------------------
Card_EditParameterMatrix::~Card_EditParameterMatrix()
{

}

//--------------------------------------------------------------------------
const Card_EditParameterMatrix& Card_EditParameterMatrix::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new Card_EditParameterMatrix();

    return *myInstance;
}

bool Card_EditParameterMatrix::isCommandMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myCommandMode;
}

bool Card_EditParameterMatrix::isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myCapacity;
}
bool Card_EditParameterMatrix::isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myTimingMode;
}
bool Card_EditParameterMatrix::isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumberOfPorts;
}
bool Card_EditParameterMatrix::isCardType(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    if (theCardType == TRN_MRTM && theSubCardType == TRN_44_TUNABLE)
    {
        return false;
    }
    return myMatrix[theCardType].myCardType;
}
bool Card_EditParameterMatrix::isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myOeoRegen;
}
bool Card_EditParameterMatrix::isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myInterconMode;
}
bool Card_EditParameterMatrix::isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myWaitToRestoreTmr;
}
bool Card_EditParameterMatrix::isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myVcgTmr;
}
bool Card_EditParameterMatrix::isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myDiffDelayThreashold;
}
bool Card_EditParameterMatrix::isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumbrChan;
}
bool Card_EditParameterMatrix::isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChanLimit;
}
bool Card_EditParameterMatrix::isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPreamp;
}
bool Card_EditParameterMatrix::isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myExtAttn;
}
bool Card_EditParameterMatrix::isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPostamp;
}

//=======================================================================================================
Card_RtrvParameterMatrix *Card_RtrvParameterMatrix::myInstance = NULL;


Card_RtrvParameterMatrix::Card_RtrvParameter Card_RtrvParameterMatrix::myMatrix[CARD_TYPE_MAX] =
{
//   Band     HalfBand     PumpPower     Wave     ID     Function     Capacity      TMG      NumOfPort      Rate      Oeo      IntMode      WTR      VcgTmr      DDThr      NumbOfChan      ChanLimit      ChanRange      Length      FiberType      IL      PreAmp      ExtAttn      PostAmp      SwitchMode      CardType      TL1EntityName
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 0    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 1    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 2    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 3    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 4    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 5    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 6    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 7    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 8    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 9    UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 10   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 11   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 12   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 13   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 14   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 15   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 16   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 17   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 18   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 19   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 20   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 21   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 22   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 23   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 24   TRN_2R       BBTM
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 25   TRN_3R       STTM
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 26   TRN_10G      TGTM
    {false,     true,      false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 27   TRN_MRTM     MRTM/MRTMT
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 28   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 29   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 30   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 31   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 32   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 33   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 34   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 35   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 36   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 37   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 38   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 39   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 40   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 41   TRN_10GT     TGTMT
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 42   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 43   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 44   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 45   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 46   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 47   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 48   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 49   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 50   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 51   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 52   TRN_MRTMT    MRTME/MRTMS        
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 53   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 54   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 55   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 56   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 57   TRN_10GTE    TGTME  
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 58   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 59   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 60   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 61   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 62   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 63   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 64   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 65   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 66   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 67   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 68   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 69   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 70   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 71   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 72   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 73   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 74   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 75   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 76   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 77   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 78   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 79   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 80   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 81   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 82   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 83   UNKNOWN      UNKNOWN
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 84   FGTM         FGTM
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 85   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 86   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 87   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 88   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 89   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 90   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 91   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 92   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 93   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 94   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 95   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 96   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 97   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 98   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 99   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 100  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 101  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 102  OSM40        OSM40
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 103  SSM40        SSM40
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 104  HDTG         HDTG
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 105  ESIM         ESIM
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 106  ESM40        ESM40
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 107  ESM20        ESM20
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 108  SPMC         SPMC
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 109  FGSM 
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 110  HGTM         HGTM
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 111  OADM88IR8D   OADM88IR8D
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 112  OADM88LR8D   OADM88LR8D
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 113  OADM88ER8D   OADM88ER8D 
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 114  OSM20        OSM20
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 115  FGTME        FGTME
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 116  DXOADM       DXOADM
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 117  OADMF8IR     UNKNOWN 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 118  OADMF8LR     UNKNOWN 
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 121  OMMXP        OMMXP
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 120  SMTMUX       UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 121  OMMX         OMMX
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 122  HGTM-M       HGTMM
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 123  OSM2S, TODO..
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 124  OSM2C, TODO..
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 125  STPM TODO 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 126  STIM TODO 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 127  SAIM TODO 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 128  SEIM TODO 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 129  MFAB         UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 130  MBFM TODO 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 131  MSFM TODO 
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 132  OADM8DSIR    OADM8DSIR
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 133  OADM8DSLR    OADM8DSLR
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 134  OADM8DSER    OADM8DSER 
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 135   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 136   UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 137  UNKNOWN      UNKNOWN
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 138  HGTMS        // Coriant lhu
    {false,     false,     false,        true,    false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 139  HGTM-MS       // Coriant lhu
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 140  UNKNOWN      UNKNOWN    
    {false,     false,     false,        false,   false, false,       false,        true,    false,         false,    false,   true,        false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}, // 141  OMMX83       OMMX83
    
    {false,     false,     false,        false,   false, false,       false,        false,   false,         false,    false,   false,       false,   false,      false,     false,          false,         false,         false,      false,         false,  false,      false,       false,       false}  // 142  ALL          ALL
//   Band     HalfBand     PumpPower     Wave     ID     Function     Capacity      TMG      NumOfPort      Rate      Oeo      IntMode      WTR      VcgTmr      DDThr      NumbOfChan      ChanLimit      ChanRange      Length      FiberType      IL      PreAmp      ExtAttn      PostAmp      SwitchMode      CardType      TL1EntityName
};

//--------------------------------------------------------------------------
Card_RtrvParameterMatrix::Card_RtrvParameterMatrix()
{

}

//--------------------------------------------------------------------------
Card_RtrvParameterMatrix::~Card_RtrvParameterMatrix()
{

}

//--------------------------------------------------------------------------
const Card_RtrvParameterMatrix& Card_RtrvParameterMatrix::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new Card_RtrvParameterMatrix();

    return *myInstance;
}

bool Card_RtrvParameterMatrix::isBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myBand;
}
bool Card_RtrvParameterMatrix::isHalfBand(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    if (theCardType == TRN_MRTM && theSubCardType == TRN_44_TUNABLE) //MRTMT
    {
        return false;
    }
    return myMatrix[theCardType].myHalfBand;
}
bool Card_RtrvParameterMatrix::isPumpPower(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPumpPower;
}
bool Card_RtrvParameterMatrix::isWave(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myWave;
}
bool Card_RtrvParameterMatrix::isID(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myID;
}
bool Card_RtrvParameterMatrix::isFunction(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myFunction;
}
bool Card_RtrvParameterMatrix::isCapacity(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myCapacity;
}
bool Card_RtrvParameterMatrix::isTimingMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myTimingMode;
}
bool Card_RtrvParameterMatrix::isNumberOfPort(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumberOfPort;
}
bool Card_RtrvParameterMatrix::isRate(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myRate;
}
bool Card_RtrvParameterMatrix::isOeoRegen(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myOeoRegen;
}
bool Card_RtrvParameterMatrix::isInterconMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myInterconMode;
}
bool Card_RtrvParameterMatrix::isWaitToRestoreTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myWaitToRestoreTmr;
}
bool Card_RtrvParameterMatrix::isVcgTmr(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myVcgTmr;
}
bool Card_RtrvParameterMatrix::isDiffDelayThreashold(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myDiffDelayThreashold;
}
bool Card_RtrvParameterMatrix::isNumbrChan(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myNumbrChan;
}
bool Card_RtrvParameterMatrix::isChanLimit(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChanLimit;
}
bool Card_RtrvParameterMatrix::isChanRange(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myChanRange;
}
bool Card_RtrvParameterMatrix::isLength(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myLength;
}
bool Card_RtrvParameterMatrix::isFiberType(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myFiberType;
}
bool Card_RtrvParameterMatrix::isIL(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myIL;
}
bool Card_RtrvParameterMatrix::isPreamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPreamp;
}
bool Card_RtrvParameterMatrix::isExtAttn(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myExtAttn;
}
bool Card_RtrvParameterMatrix::isPostamp(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].myPostamp;
}
bool Card_RtrvParameterMatrix::isSwitchMode(CT_CardType theCardType, CT_SubCardType theSubCardType)const
{
    return myMatrix[theCardType].mySwitchMode;
}





//=======================================================================================================
Card_LedParameterMatrix *Card_LedParameterMatrix::myInstance = NULL;


Card_LedParameterMatrix::Card_LedParameter Card_LedParameterMatrix::myMatrix[CARD_TYPE_MAX] =
{
//   Active     Power     Fault     Sync     NECr     NEMj     NEMn     ACO Active     Line     Port     PortX     OSC     Express     APR     Input    Lpbk     DWDM44     DWDM45     DWDM1     DWDM2     OPCX     Bits     PII             CardType     TL1EntityName
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 0    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 1    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 2    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 3    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 4    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 5    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 6    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 7    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 8    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 9    UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 10   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 11   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 12   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 13   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 14   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 15   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 16   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 17   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 18   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 19   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 20   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 21   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 22   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 23   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 24   TRN_2R       BBTM
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 25   TRN_3R       STTM
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   true,    false,     false,     false,    false,    false,   false,   false}, // 26   TRN_10G      TGTM
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   true,    false,     false,     false,    false,    false,   false,   false}, // 27   TRN_MRTM     MRTM/MRTMT
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 28   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 29   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 30   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 31   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 32   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 33   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 34   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 35   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 36   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 37   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 38   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 39   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 40   UNKNOWN      UNKNOWN
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   true,    false,     false,     false,    false,    false,   false,   false}, // 41   TRN_10GT     TGTMT
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 42   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 43   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 44   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 45   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 46   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 47   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 48   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 49   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 50   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 51   UNKNOWN      UNKNOWN
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 52   TRN_MRTMT    MRTME/MRTMS        
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 53   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 54   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 55   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 56   UNKNOWN      UNKNOWN
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 57   TRN_10GTE    TGTME  
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 58   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 59   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 60   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 61   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 62   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 63   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 64   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 65   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 66   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 67   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 68   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 69   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 70   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 71   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 72   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 73   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 74   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 75   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 76   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 77   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 78   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 79   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 80   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 81   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 82   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 83   UNKNOWN      UNKNOWN
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 84   FGTM         FGTM
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 85   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 86   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 87   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 88   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 89   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 90   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 91   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 92   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 93   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 94   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 95   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 96   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 97   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 98   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 99   UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 100  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 101  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 102  OSM40        OSM40
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 103  SSM40        OSM40
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 104  HDTG         HDTG
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 105  ESIM         ESIM
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 106  ESM40        ESM40
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 107  ESM20        ESM20
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 108  SPMC         SPMC
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 109  FGSM         FGSM
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 110  HGTM         HGTM
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 111  OADM88IR8D   OADM88IR8D
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 112  OADM88LR8D   OADM88LR8D
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 113  OADM88ER8D   OADM88ER8D
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 114  OSM20        OSM20
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 115  FGTME        FGTME
    {true,      true,     true,     false,   false,   false,   false,   false,         false,   true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 116  DXOADM       DXOADM
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 117  OADMF8IR     UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 118  OADMF8LR     UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 119  OMMXP        OMMXP
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 120  SMTMUX       UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 121  OMMX         OMMX
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 122  HGTM-M       HGTMM
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 123  OSM2S,       TODO..
    {true,      true,     true,     true,    false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 124  OSM2C,       TODO..
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 125  STPM         TODO
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 126  STIM         TODO
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 127  SAIM         TODO 
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 128  SEIM         TODO
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 129  MFAB         UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 130  MBFM         TODO
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 131  MSFM         TODO
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 132  OADM8DSIR    OADM8DSIR
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 133  OADM8DSLR    OADM8DSLR
    {true,      true,     true,     false,   false,   false,   false,   false,         true,    true,    false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 134  OADM8DSER    OADM8DSER
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 135  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 136  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 137  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 138  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 139  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 140  UNKNOWN      UNKNOWN
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}, // 141  OMMX83        OMMX83
    
    {false,     false,    false,    false,   false,   false,   false,   false,         false,   false,   false,    false,  false,      false,  false,   false,   false,     false,     false,    false,    false,   false,   false}  // 142  ALL          ALL
//   Active     Power     Fault     Sync     NECr     NEMj     NEMn     ACO Active     Line     Port     PortX     OSC     Express     APR     Input    Lpbk     DWDM44     DWDM45     DWDM1     DWDM2     OPCX     Bits     PII             CardType     TL1EntityName
};

//--------------------------------------------------------------------------
Card_LedParameterMatrix::Card_LedParameterMatrix()
{

}

//--------------------------------------------------------------------------
Card_LedParameterMatrix::~Card_LedParameterMatrix()
{

}

//--------------------------------------------------------------------------
const Card_LedParameterMatrix& Card_LedParameterMatrix::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new Card_LedParameterMatrix();

    return *myInstance;
}

//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isActiveLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myActiveLed;
}

//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isPowerLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myPowerLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isFaultLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myFaultLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isActLineLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myActLineLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isLineLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myLineLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isExpressLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myExpressLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isPortLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myPortLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isPortXLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myPortXLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isInputLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myInputLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isLpbkLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myLpbkLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isSyncLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].mySyncLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isOscLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myOscLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isNeCrLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myNeCrLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isNeMjLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myNeMjLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isNeMnLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myNeMnLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isOcpXLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myOcpXLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isAprLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myAprLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isDWDM44Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myDWDM44Led;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isDWDM45Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myDWDM45Led;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isDWDM1Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myDWDM1Led;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isDWDM2Led(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myDWDM2Led;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isBitsLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myBitsLed;
}
//--------------------------------------------------------------------------
bool Card_LedParameterMatrix::isPII_AlarmCutOffLed(CT_CardType theCardType, CT_SubCardType theSubCardType) const
{
    return myMatrix[theCardType].myPII_AlarmCutOffLed;
}


