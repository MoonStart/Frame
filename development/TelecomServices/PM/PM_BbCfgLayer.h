/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   Configuration classes for each type of PM.
--------------------------------------------------------------------------*/
#ifndef PM_BBCONFIGLAYER_H
#define PM_BBCONFIGLAYER_H

#include <PM/PM_BbCfg.h>
#include <PM/PM_BbCounterReset.h>
#include <PM/PM_BbGaugeReset.h>
#include <PM/PM_BbThresholdData.h>
#include <PM/PM_BbInhibitData.h>
#include <PM/PM_BbThresholdMsNearEnd.h>
#include <PM/PM_BbThresholdGfp.h>
#include <PM/PM_BbThresholdHopNearEnd.h>
#include <EPM/PM_BbThresholdHopFarEnd.h>
#include <PM/PM_BbInhibitMsNearEnd.h>
#include <PM/PM_BbInhibitGfp.h>
#include <PM/PM_BbInhibitHopNearEnd.h>
#include <EPM/PM_BbInhibitHopFarEnd.h>
#include <PM/PM_BbThresholdMsFarEnd.h>
#include <PM/PM_BbInhibitMsFarEnd.h>
#include <EPM/PM_BbThresholdOdu.h>
#include <EPM/PM_BbInhibitOdu.h>
#include <PM/PM_BbThresholdOtu.h>
#include <PM/PM_BbInhibitOtu.h>
#include <PM/PM_BbThresholdCop.h>
#include <PM/PM_BbInhibitCop.h>
#include <PM/PM_BbThresholdOpt.h>
#include <PM/PM_BbInhibitOpt.h>
#include <PM/PM_BbThresholdOms.h>
#include <PM/PM_BbInhibitOms.h>
#include <PM/PM_BbThresholdLaser.h>
#include <PM/PM_BbInhibitLaser.h>
#include <PM/PM_BbThresholdEon.h>
#include <PM/PM_BbInhibitEon.h>
#include <EPM/PM_BbInhibitRmon.h>
#include <EPM/PM_BbThresholdRmon.h>
#include <EPM/PM_BbThresholdTcm.h>
#include <EPM/PM_BbInhibitTcm.h>
#include <BaseClass/FC_ObjectIdStatus.h>
#include <CommonTypes/CT_OduDefinitions.h>


//-----------------------------------------------------------------
class PM_BbCfgData : public PM_BbCfg
{
public :

    PM_BbCfgData(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgData();

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);

private:

    PM_BbThresholdData      myThresholdCfg;
    PM_BbInhibitData        myInhibitCfg;
    PM_BbCounterReset       myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOtu : public PM_BbCfg
{
public :

    PM_BbCfgOtu(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOtu();

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);

private:

    PM_BbThresholdOtu   myThresholdCfg;
    PM_BbInhibitOtu     myInhibitCfg;
    PM_BbCounterReset   myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOpt : public PM_BbCfg
{
public :

    PM_BbCfgOpt(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOpt();

private:

    PM_BbThresholdOpt myThresholdCfg;
    PM_BbInhibitOpt   myInhibitCfg;
    PM_BbGaugeReset   myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOptCounter : public PM_BbCfg
{
public :

    PM_BbCfgOptCounter(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOptCounter();

private:

    PM_BbThresholdOptCounter    myThresholdCfg;
    PM_BbInhibitOptCounter      myInhibitCfg;
    PM_BbCounterReset           myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOms : public PM_BbCfg
{
public :

    PM_BbCfgOms(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOms();

private:

    PM_BbThresholdOms myThresholdCfg;
    PM_BbInhibitOms   myInhibitCfg;
    PM_BbGaugeReset   myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgLaser : public PM_BbCfg
{
public :

    PM_BbCfgLaser(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgLaser();

private:

    PM_BbThresholdLaser   myThresholdCfg;
    PM_BbInhibitLaser     myInhibitCfg;
    PM_BbGaugeReset       myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgCop : public PM_BbCfg
{
public :

    PM_BbCfgCop(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgCop();

private:

    PM_BbThresholdCop myThresholdCfg;
    PM_BbInhibitCop   myInhibitCfg;
    PM_BbGaugeReset   myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgEon : public PM_BbCfg
{
public :

    PM_BbCfgEon(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgEon();

private:

    PM_BbThresholdEon       myThresholdCfg;
    PM_BbInhibitEon         myInhibitCfg;
    PM_BbCounterReset       myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgMsNearEnd : public PM_BbCfg
{
public :

    PM_BbCfgMsNearEnd(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgMsNearEnd();

private:

    PM_BbThresholdMsNearEnd      myThresholdCfg;
    PM_BbInhibitMsNearEnd        myInhibitCfg;
    PM_BbCounterReset            myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgHopNearEnd : public PM_BbCfg
{
public :

    PM_BbCfgHopNearEnd(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgHopNearEnd();

    PM_BbInhibitHopNearEnd& GetInhibitHopNearEnd() { return myInhibitCfg; }

private:

    PM_BbThresholdHopNearEnd      myThresholdCfg;
    PM_BbInhibitHopNearEnd        myInhibitCfg;
    PM_BbCounterReset             myResetCfg;

};



//-----------------------------------------------------------------
class PM_BbCfgHopPFNearEnd : public PM_BbCfg
{
public :

    PM_BbCfgHopPFNearEnd(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgHopPFNearEnd();

    PM_BbInhibitHopNearEnd& GetInhibitHopNearEnd() { return myInhibitCfg; }

private:

    PM_BbInhibitHopNearEnd        myInhibitCfg;
    PM_BbCounterReset             myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgHopFarEnd : public PM_BbCfg
{
public :

    PM_BbCfgHopFarEnd(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgHopFarEnd();

private:

    PM_BbThresholdHopFarEnd       myThresholdCfg;
    PM_BbInhibitHopFarEnd         myInhibitCfg;
    PM_BbCounterReset             myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgMsFarEnd : public PM_BbCfg
{
public :

    PM_BbCfgMsFarEnd(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgMsFarEnd();

private:

    PM_BbThresholdMsFarEnd      myThresholdCfg;
    PM_BbInhibitMsFarEnd        myInhibitCfg;
    PM_BbCounterReset           myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgGfp : public PM_BbCfg
{
public :

    PM_BbCfgGfp(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgGfp();

private:

    PM_BbThresholdGfp      myThresholdCfg;
    PM_BbInhibitGfp        myInhibitCfg;
    PM_BbCounterReset      myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgRmonCounter : public PM_BbCfg
{
public :

    PM_BbCfgRmonCounter(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgRmonCounter();

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);

private:

    PM_BbThresholdRmonCounter      myThresholdCfg;
    PM_BbInhibitRmonCounter        myInhibitCfg;
    PM_BbCounterReset              myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgRmonGauge : public PM_BbCfg
{
public :

    PM_BbCfgRmonGauge(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgRmonGauge();

private:

    PM_BbThresholdRmonGauge myThresholdCfg;
    PM_BbInhibitRmonGauge   myInhibitCfg;
    PM_BbGaugeReset         myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOtuGauge : public PM_BbCfg
{
public :

    PM_BbCfgOtuGauge(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOtuGauge();

private:

    PM_BbThresholdOtuGauge myThresholdCfg;
    PM_BbInhibitOtuGauge   myInhibitCfg;
    PM_BbGaugeReset         myResetCfg;

};

//-----------------------------------------------------------------
class PM_BbCfgOduPF : public PM_BbCfg
{
public :

    PM_BbCfgOduPF(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOduPF();

    PM_BbInhibitOdu& GetInhibitOdu() { return myInhibitCfg; }

private:

    PM_BbInhibitOdu        myInhibitCfg;
    PM_BbCounterReset      myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgOdu : public PM_BbCfg
{
public :

    PM_BbCfgOdu(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgOdu();

    PM_BbInhibitOdu& GetInhibitOdu() { return myInhibitCfg; }

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);

private:

    PM_BbThresholdOdu      myThresholdCfg;
    PM_BbInhibitOdu        myInhibitCfg;
    PM_BbCounterReset      myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgOduGaugePF : public PM_BbCfg
{
public :
 
    PM_BbCfgOduGaugePF(uint32 dummy1 = 0, uint32 dummy2 = 0);
 
    virtual ~PM_BbCfgOduGaugePF();
 
private:
 
    PM_BbInhibitOduGauge   myInhibitCfg;
    PM_BbGaugeReset        myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgOduGauge : public PM_BbCfg
{
public :
 
    PM_BbCfgOduGauge(uint32 dummy1 = 0, uint32 dummy2 = 0);
 
    virtual ~PM_BbCfgOduGauge();
 
private:
 
    PM_BbThresholdOduGauge myThresholdCfg;
    PM_BbInhibitOduGauge   myInhibitCfg;
    PM_BbGaugeReset        myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgTcmPF : public PM_BbCfg
{
public :

    PM_BbCfgTcmPF(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgTcmPF();

    PM_BbInhibitTcm& GetInhibitTcm() { return myInhibitCfg; }

private:

    PM_BbInhibitTcm        myInhibitCfg;
    PM_BbCounterReset      myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgTcm : public PM_BbCfg
{
public :

    PM_BbCfgTcm(uint32 dummy1 = 0, uint32 dummy2 = 0);

    virtual ~PM_BbCfgTcm();

    PM_BbInhibitTcm& GetInhibitTcm() { return myInhibitCfg; }

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);

    void SetCurrTcmMode(CT_TCM_Mode theTcmMode);
    CT_TCM_Mode GetCurrTcmMode() { return myCurrTcmMode; }
    void SetPrevTcmMode(CT_TCM_Mode theTcmMode);
    CT_TCM_Mode GetPrevTcmMode() { return myPrevTcmMode; }
    bool GetTcmModeChgedFlag() {return myIsTcmModeChged; }
    void SetModeChgedFlag(bool theModeChged);
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4CAF01AB
    virtual istream& ReadObject( istream& theStream );
    
protected:
    // myCurrTcmMode -- current tcm mode from CFG
    // myPrevTcmMode -- previous tcm mode during one bin
    //               -- if switch to next bin, reset to UNKNOWN
    // myIsTcmModeChged- indicate if tcm-mode is changed or not 
    //                  during one bin
    CT_TCM_Mode myCurrTcmMode;
    CT_TCM_Mode myPrevTcmMode;
    bool myIsTcmModeChged;
private:

    PM_BbThresholdTcm      myThresholdCfg;
    PM_BbInhibitTcm        myInhibitCfg;
    PM_BbCounterReset      myResetCfg;
};

//-----------------------------------------------------------------
class PM_BbCfgTcmGaugePF : public PM_BbCfg
{
public :
 
    PM_BbCfgTcmGaugePF(uint32 dummy1 = 0, uint32 dummy2 = 0);
 
    virtual ~PM_BbCfgTcmGaugePF();
 
private:
 
    PM_BbInhibitTcmGauge   myInhibitCfg;
    PM_BbGaugeReset        myResetCfg;
};
 
//-----------------------------------------------------------------
class PM_BbCfgTcmGauge : public PM_BbCfg
{
public :
 
    PM_BbCfgTcmGauge(uint32 dummy1 = 0, uint32 dummy2 = 0);
 
    virtual ~PM_BbCfgTcmGauge();
 
     void SetCurrTcmMode(CT_TCM_Mode theTcmMode);
     CT_TCM_Mode GetCurrTcmMode() { return myCurrTcmMode; }
     void SetPrevTcmMode(CT_TCM_Mode theTcmMode);
     CT_TCM_Mode GetPrevTcmMode() { return myPrevTcmMode; }
     bool GetTcmModeChgedFlag() {return myIsTcmModeChged; }
     void SetModeChgedFlag(bool theModeChged);
     virtual ostream& WriteObject( ostream& theStream );
     
     //Reads the values from the stream.
     //##ModelId=3E6E4CAF01AB
     virtual istream& ReadObject( istream& theStream );
protected:
    
    // myCurrTcmMode -- current tcm mode from CFG
    // myPrevTcmMode -- previous tcm mode during one bin
    //               -- if switch to next bin, reset to UNKNOWN
    // myIsTcmModeChged- indicate if tcm-mode is changed or not 
    //                  during one bin
    CT_TCM_Mode myCurrTcmMode;
    CT_TCM_Mode myPrevTcmMode;
    bool myIsTcmModeChged;
private:
 
    PM_BbThresholdTcmGauge myThresholdCfg;
    PM_BbInhibitTcmGauge   myInhibitCfg;
    PM_BbGaugeReset        myResetCfg;
};

#endif //PM_BBCONFIGLAYER_H
