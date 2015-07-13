/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   Configuration classes for each type of PM.
--------------------------------------------------------------------------*/
#include <BaseClass/FC_TextStream.h>

#include <PM/PM_BbCfgLayer.h>

//-----------------------------------------------------------------
PM_BbCfgData::PM_BbCfgData(uint32 dummy1, uint32 dummy2)
    :myResetCfg( dummy1 ),
     myThresholdCfg( dummy1 ),
     myInhibitCfg( dummy1 ),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgData::~PM_BbCfgData()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCfgData::GetThreshold(CT_PM_Parameter theParameter)
{
    if ( (theParameter == PM_TypeData::PM_SE) && (GetThresholdPtr()->GetNumberOfParam() > PM_TypeData::PM_SE_HIGH) )
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeData::PM_SE_HIGH);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeData::PM_SE);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
 
    return GetThresholdPtr()->GetThreshold(theParameter);
}

//-----------------------------------------------------------------
PM_BbCfgOtu::PM_BbCfgOtu(uint32 dummy1, uint32 dummy2)
    :myResetCfg( dummy1 ),
     myThresholdCfg( dummy1 ),
     myInhibitCfg( dummy1 ),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOtu::~PM_BbCfgOtu()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCfgOtu::GetThreshold(CT_PM_Parameter theParameter)
{
    if ( (theParameter == PM_TypeOtu::PM_CV) && (GetThresholdPtr()->GetNumberOfParam() > PM_TypeOtu::PM_CV_HIGH) )
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOtu::PM_CV_HIGH);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOtu::PM_CV);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
    else if ( (theParameter == PM_TypeOtu::PM_BE) && (GetThresholdPtr()->GetNumberOfParam() > PM_TypeOtu::PM_BE_HIGH) )
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOtu::PM_BE_HIGH);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOtu::PM_BE);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
 
    return GetThresholdPtr()->GetThreshold(theParameter);
}

//-----------------------------------------------------------------
PM_BbCfgOpt::PM_BbCfgOpt(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOpt::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOpt::~PM_BbCfgOpt()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOptCounter::PM_BbCfgOptCounter(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOptCounter::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOptCounter::~PM_BbCfgOptCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOms::PM_BbCfgOms(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOms::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOms::~PM_BbCfgOms()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgLaser::PM_BbCfgLaser(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeLaser::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgLaser::~PM_BbCfgLaser()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgCop::PM_BbCfgCop(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeCop::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgCop::~PM_BbCfgCop()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgEon::PM_BbCfgEon(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeEon::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgEon::~PM_BbCfgEon()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgMsNearEnd::PM_BbCfgMsNearEnd(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeMsNearEnd::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgMsNearEnd::~PM_BbCfgMsNearEnd()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgHopNearEnd::PM_BbCfgHopNearEnd(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeHopNearEnd::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgHopNearEnd::~PM_BbCfgHopNearEnd()
{
    // Nothing to do for now.
}


//-----------------------------------------------------------------
PM_BbCfgHopPFNearEnd::PM_BbCfgHopPFNearEnd(uint32 dummy1, uint32 dummy2):

    myResetCfg(PM_TypeHopNearEnd::PM_PARAM_NUM),
    myInhibitCfg(),
    PM_BbCfg(myInhibitCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgHopPFNearEnd::~PM_BbCfgHopPFNearEnd()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgHopFarEnd::PM_BbCfgHopFarEnd(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeHopFarEnd::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgHopFarEnd::~PM_BbCfgHopFarEnd()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgMsFarEnd::PM_BbCfgMsFarEnd(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeMsFarEnd::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgMsFarEnd::~PM_BbCfgMsFarEnd()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgGfp::PM_BbCfgGfp(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeGfp::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgGfp::~PM_BbCfgGfp()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgRmonCounter::PM_BbCfgRmonCounter(uint32 dummy1, uint32 dummy2)
    :myResetCfg( dummy1 ),
     myThresholdCfg( dummy1 ),
     myInhibitCfg( dummy1 ),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgRmonCounter::~PM_BbCfgRmonCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCfgRmonCounter::GetThreshold(CT_PM_Parameter theParameter)
{
    PM_TypeRmonCounter::PM_Param aLowParam  = PM_TypeRmonCounter::PM_PARAM_NUM;
    PM_TypeRmonCounter::PM_Param aHighParam = PM_TypeRmonCounter::PM_PARAM_NUM;
 
    switch ( theParameter )
    {
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_DROP: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_DROP_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_DROP;
                aHighParam = PM_TypeRmonCounter::PM_DROP_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_PKT: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_PKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_PKT;
                aHighParam = PM_TypeRmonCounter::PM_PKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_BCPKT: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_BCPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_BCPKT;
                aHighParam = PM_TypeRmonCounter::PM_BCPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_MCPKT: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_MCPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_MCPKT;
                aHighParam = PM_TypeRmonCounter::PM_MCPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_CRCAE: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_CRCAE_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_CRCAE;
                aHighParam = PM_TypeRmonCounter::PM_CRCAE_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_USPKT: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_USPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_USPKT;
                aHighParam = PM_TypeRmonCounter::PM_USPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_OSPKT: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_OSPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_OSPKT;
                aHighParam = PM_TypeRmonCounter::PM_OSPKT_HIGH;
            }
            break;
         case (CT_PM_Parameter) PM_TypeRmonCounter::PM_FRAG: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_FRAG_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_FRAG;
                aHighParam = PM_TypeRmonCounter::PM_FRAG_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_JABR: 
            if ( GetThresholdPtr()->GetNumberOfParam() > PM_TypeRmonCounter::PM_JABR_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_JABR;
                aHighParam = PM_TypeRmonCounter::PM_JABR_HIGH;
            }
            break;
        default:
            break;
    }
 
    if ( aLowParam != aHighParam ) // both defaulted to PM_PARAM_NUM
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(aHighParam);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(aLowParam);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
 
    return GetThresholdPtr()->GetThreshold(theParameter);
}

//-----------------------------------------------------------------
PM_BbCfgRmonGauge::PM_BbCfgRmonGauge(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeRmonGauge::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgRmonGauge::~PM_BbCfgRmonGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOtuGauge::PM_BbCfgOtuGauge(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOtuGauge::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOtuGauge::~PM_BbCfgOtuGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOdu::PM_BbCfgOdu(uint32 dummy1, uint32 dummy2)
    :myResetCfg( dummy1 ),
     myThresholdCfg( dummy1 ),
     myInhibitCfg( dummy1 ),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOdu::~PM_BbCfgOdu()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCfgOdu::GetThreshold(CT_PM_Parameter theParameter)
{
    if ( (theParameter == PM_TypeOdu::PM_CV) && (GetThresholdPtr()->GetNumberOfParam() > PM_TypeOdu::PM_CV_HIGH) )
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOdu::PM_CV_HIGH);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeOdu::PM_CV);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
 
    return GetThresholdPtr()->GetThreshold(theParameter);
}

//-----------------------------------------------------------------
PM_BbCfgOduPF::PM_BbCfgOduPF(uint32 dummy1, uint32 dummy2):

    myResetCfg( dummy1 ),
    myInhibitCfg( dummy1 ),
    PM_BbCfg(myInhibitCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOduPF::~PM_BbCfgOduPF()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOduGauge::PM_BbCfgOduGauge(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOduGauge::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbCfgOduGauge::~PM_BbCfgOduGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgOduGaugePF::PM_BbCfgOduGaugePF(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeOduGauge::PM_PARAM_NUM),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myResetCfg)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbCfgOduGaugePF::~PM_BbCfgOduGaugePF()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgTcm::PM_BbCfgTcm(uint32 dummy1, uint32 dummy2)
    :myResetCfg( dummy1 ),
     myThresholdCfg( dummy1 ),
     myInhibitCfg( dummy1 ),
     myCurrTcmMode(CT_TCM_MODE_UNKNOWN),
     myPrevTcmMode(CT_TCM_MODE_UNKNOWN),
     myIsTcmModeChged(false),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgTcm::~PM_BbCfgTcm()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCfgTcm::GetThreshold(CT_PM_Parameter theParameter)
{
    if ( (theParameter == PM_TypeTcm::PM_CV) && (GetThresholdPtr()->GetNumberOfParam() > PM_TypeTcm::PM_CV_HIGH) )
    {
        uint32 theHighValue = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeTcm::PM_CV_HIGH);
        uint32 theLowValue  = (uint32)GetThresholdPtr()->GetThreshold(PM_TypeTcm::PM_CV);
        return ( (theHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + theLowValue );
    }
 
    return GetThresholdPtr()->GetThreshold(theParameter);
}

void PM_BbCfgTcm::SetCurrTcmMode(CT_TCM_Mode theTcmMode)
{
    if(theTcmMode != myCurrTcmMode)
    {
        myIsTcmModeChged = true;
    myCurrTcmMode = theTcmMode;
}
}
void PM_BbCfgTcm::SetPrevTcmMode(CT_TCM_Mode theTcmMode)
{
    myPrevTcmMode = theTcmMode;
}

void PM_BbCfgTcm::SetModeChgedFlag(bool theModeChged)
{
    myIsTcmModeChged = theModeChged;
}

ostream& PM_BbCfgTcm::WriteObject( ostream& theStream )
{
    PM_BbCfg::WriteObject(theStream);
    uint8 aPrevTcmMode = (uint8)(myPrevTcmMode);
    uint8 aCurrTcmMode = (uint8)(myCurrTcmMode);
    uint8 aTcmModeChg = (uint8)(myIsTcmModeChged);
    
    theStream << FC_InsertVar(aPrevTcmMode);
    theStream << FC_InsertVar(aCurrTcmMode);
    theStream << FC_InsertVar(aTcmModeChg);

    return theStream;
}

istream& PM_BbCfgTcm::ReadObject( istream& theStream )
{
    PM_BbCfg::ReadObject(theStream);
    uint8 aPrevTcmMode, aCurrTcmMode, aTcmModeChg;
    
    theStream >> FC_ExtractVar(aPrevTcmMode);
    theStream >> FC_ExtractVar(aCurrTcmMode);
    theStream >> FC_ExtractVar(aTcmModeChg);

    return theStream;
}


//-----------------------------------------------------------------
PM_BbCfgTcmPF::PM_BbCfgTcmPF(uint32 dummy1, uint32 dummy2):

    myResetCfg( dummy1 ),
    myInhibitCfg( dummy1 ),
    PM_BbCfg(myInhibitCfg, myResetCfg)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgTcmPF::~PM_BbCfgTcmPF()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbCfgTcmGauge::PM_BbCfgTcmGauge(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeTcmGauge::PM_PARAM_NUM),
     myThresholdCfg(),
     myInhibitCfg(),
     myCurrTcmMode(CT_TCM_MODE_UNKNOWN),
     myPrevTcmMode(CT_TCM_MODE_UNKNOWN),
     myIsTcmModeChged(false),
     PM_BbCfg(myInhibitCfg, myThresholdCfg, myResetCfg)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbCfgTcmGauge::~PM_BbCfgTcmGauge()
{
    // Nothing to do for now.
}
 
void PM_BbCfgTcmGauge::SetCurrTcmMode(CT_TCM_Mode theTcmMode)
{
    if(theTcmMode != myCurrTcmMode)
    {
        myIsTcmModeChged = true;
    myCurrTcmMode = theTcmMode;
}
}
void PM_BbCfgTcmGauge::SetPrevTcmMode(CT_TCM_Mode theTcmMode)
{
    myPrevTcmMode = theTcmMode;
}

void PM_BbCfgTcmGauge::SetModeChgedFlag(bool theModeChged)
{
    myIsTcmModeChged = theModeChged;
}

ostream& PM_BbCfgTcmGauge::WriteObject( ostream& theStream )
{
    PM_BbCfg::WriteObject(theStream);
    
    uint8 aPrevTcmMode = (uint8)(myPrevTcmMode);
    uint8 aCurrTcmMode = (uint8)(myCurrTcmMode);
    uint8 aTcmModeChg = (uint8)(myIsTcmModeChged);
    
    theStream << FC_InsertVar(aPrevTcmMode);
    theStream << FC_InsertVar(aCurrTcmMode);
    theStream << FC_InsertVar(aTcmModeChg);

    return theStream;
}

istream& PM_BbCfgTcmGauge::ReadObject( istream& theStream )
{
    PM_BbCfg::ReadObject(theStream);
    uint8 aPrevTcmMode, aCurrTcmMode, aTcmModeChg;
    
    theStream >> FC_ExtractVar(aPrevTcmMode);
    theStream >> FC_ExtractVar(aCurrTcmMode);
    theStream >> FC_ExtractVar(aTcmModeChg);

    return theStream;
}

//-----------------------------------------------------------------
PM_BbCfgTcmGaugePF::PM_BbCfgTcmGaugePF(uint32 dummy1, uint32 dummy2)
    :myResetCfg(PM_TypeTcmGauge::PM_PARAM_NUM),
     myInhibitCfg(),
     PM_BbCfg(myInhibitCfg, myResetCfg)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbCfgTcmGaugePF::~PM_BbCfgTcmGaugePF()
{
    // Nothing to do for now.
}

