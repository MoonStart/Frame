/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:   Telecom Services/Facility Monitoring.
 TARGET   :   All.
 AUTHOR   :   Steve Thiffault, December 6, 2001.
 DESCRIPTION: Implementation file for the generic application.
--------------------------------------------------------------------------*/

#include <T6100_CardActiveRegion.h>
#include <T6100/T6100_CardIf.h>
#include <T6100/T6100_SlotIf.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_RegionImp.h>
#include <PM/src/PM_Processor.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbDefectData.h>
#include <PM/PM_BbDefectMsNearEnd.h>
#include <PM/PM_BbDefectMsFarEnd.h>
#include <PM/PM_BbDefectHopNearEnd.h>
#include <PM/PM_BbDefectGfp.h>
#include <EPM/PM_BbDefectOdu.h>
#include <EPM/PM_BbDefectTcm.h>
#include <PM/PM_BbDefectOtu.h>
#include <PM/PM_BbDefectCop.h>
#include <PM/PM_BbCountData.h>
#include <PM/PM_BbCountMsNearEnd.h>
#include <PM/PM_BbCountMsFarEnd.h>
#include <PM/PM_BbCountHopNearEnd.h>
#include <PM/PM_BbCountGfp.h>
#include <PM/PM_BbCountEon.h>
#include <EPM/PM_BbCountOdu.h>
#include <EPM/PM_BbCountTcm.h>
#include <PM/PM_BbCountOtu.h>
#include <EPM/PM_BbCountRmon.h>
#include <PM/PM_BbStatusOpt.h>
#include <PM/PM_BbStatusOptCounter.h>
#include <PM/PM_BbStatusOms.h>
#include <PM/PM_BbStatusCop.h>
#include <PM/PM_BbStatusLaser.h>
#include <PM/PM_BbStatusMsNearEnd.h>
#include <EPM/PM_BbStatusRmon.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_SubApplicationMap.h>
#include <PM/PM_TestMenuOnTrn_Ram.h>

string PM_GenericApplication::defaultString = "Default string";

//-----------------------------------------------------------------
//##ModelId=3C22418C01D1
PM_GenericApplication::PM_GenericApplication(PM_MainBaseSubApplication& thePmMainApplication,
                                             CT_PM_Side                 theSide,
                                             uint32                     theMaxEntities,
                                             const char*                theSuffixStr):

    myPmMainApplication(thePmMainApplication),
    myMonTxApplication(NULL),
    myCsmApplication(NULL),
    myCfgApplication(NULL),
    myAlmApplication(NULL),
    myAlmOptApplication(NULL),
    myAlmOtsApplication(NULL),
    myAlmOtsOhApplication(NULL),
    myAlmOtuApplication(NULL),
    myAlmOduApplication(NULL),
    myAlmTcmApplication(NULL),
    myAlmOmsApplication(NULL),
    myAlmRsApplication(NULL),
    myAlmMsApplication(NULL),
    myAlmHopApplication(NULL),
    myAlmGfpApplication(NULL),
    myAlmRmonApplication(NULL),
    myAlmOscOchApplication(NULL),
    myCardActiveRegionPtr(NULL),
    my1plus1SpApplication(NULL),
    myProcessor(NULL),
    myMonApplicationCount(1),
    mySide(theSide),
    myMaxEntities(theMaxEntities),
    myFileStoreIndex(0),
    myLayerName("Default layer name"),
    myTestMenu(NULL)
{
    if (theSuffixStr != NULL)
    {
        myKeySuffix = theSuffixStr;
    }
    else
    {
        myKeySuffix = "";
    }

    for (int i = 0; i < CT_PM_MAX_MON_APPLICATIONS; i++)
    {
        myMonApplications[i] = (MON_AppIf *) NULL;
    }

    myTestMenu = new PM_TestMenuInSubApp( *this );
}

//-----------------------------------------------------------------
//##ModelId=3C22418C01DB
PM_GenericApplication::~PM_GenericApplication()
{
    // Nothing to do for now.
    delete myTestMenu;
}

//-----------------------------------------------------------------
//##ModelId=3C22418C01DD
PM_MainBaseSubApplication& PM_GenericApplication::GetPmMainApplication()
{
    return myPmMainApplication;

}

//-----------------------------------------------------------------
//##ModelId=3C22418C01E5
MON_AppIf& PM_GenericApplication::GetMonApplication(uint32 theMonAppIndex)
{
    if (theMonAppIndex < CT_PM_MAX_MON_APPLICATIONS)
    {
        if (myMonApplications[theMonAppIndex] == (MON_AppIf *) 0)
        {
            FC_THROW_ERROR(FC_RuntimeError, "Monitoring application does not exist");
        }
        else
        {
            return *(myMonApplications[theMonAppIndex]);
        }
    }
    else
    {
        FC_THROW_ERROR(FC_RuntimeError, "Monitoring application index out of range");
    }

    FC_THROW_ERROR(FC_RuntimeError, "Monitoring application index out of range");
    return *(myMonApplications[0]); //never run the return, just for eliminate the compile waring
}

MON_AppIf* PM_GenericApplication::GetMonApplicationPtr(uint32 theMonAppIndex)
{
    if (theMonAppIndex < CT_PM_MAX_MON_APPLICATIONS)
    {
        return myMonApplications[theMonAppIndex];
    }
    else
    return (MON_AppIf*)0;
}

//-----------------------------------------------------------------
//##ModelId=3C22418C01EF
void PM_GenericApplication::SetMonApplication(MON_AppIf* theMonApplication, uint32 theMonAppIndex)
{
    if (theMonAppIndex < CT_PM_MAX_MON_APPLICATIONS)
    {
        myMonApplications[theMonAppIndex] = theMonApplication;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C98CCC90286
MON_AppIf& PM_GenericApplication::GetMonTxApplication()
{
    if(!myMonTxApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "Monitoring Tx application does not exist");
    }

    return *myMonTxApplication;

}


//-----------------------------------------------------------------
MON_AppIf* PM_GenericApplication::GetMonTxApplicationPtr()
{
    return myMonTxApplication;
}

//-----------------------------------------------------------------
//##ModelId=3C98CCC902D6
void PM_GenericApplication::SetMonTxApplication(MON_AppIf* theMonTxApplication)
{
    myMonTxApplication = theMonTxApplication;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A101C6
CSM_AppIf& PM_GenericApplication::GetCsmApplication()
{
    if(!myCsmApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "CSM application does not exist");
    }

    return *myCsmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A101DA
void PM_GenericApplication::SetCsmApplication(CSM_AppIf* theCsmApplication)
{
    myCsmApplication = theCsmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8C034F
CFG_AppIf& PM_GenericApplication::GetCfgApplication()
{
    if(!myCfgApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "CFG application does not exist");
    }

    return *myCfgApplication;

}

//-----------------------------------------------------------------
CFG_AppIf* PM_GenericApplication::GetCfgApplicationPtr()
{
    return myCfgApplication;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8C038B
void PM_GenericApplication::SetCfgApplication(CFG_AppIf* theCfgApplication)
{
    myCfgApplication = theCfgApplication;

}

//-----------------------------------------------------------------
SP_1plus1BaseApplication* PM_GenericApplication::Get1plus1SpApplication()
{
    return my1plus1SpApplication;
}

//-----------------------------------------------------------------
void PM_GenericApplication::Set1plus1SpApplication(SP_1plus1BaseApplication* theSpApplication)
{
    my1plus1SpApplication = theSpApplication;

}

//-----------------------------------------------------------------
CFG_AppIf* PM_GenericApplication::GetOppositeSideCfgApplication()
{
    return myOppositeSideCfgApplication;
}

//-----------------------------------------------------------------
void PM_GenericApplication::SetOppositeSideCfgApplication(CFG_AppIf* theCfgApplication)
{
    myOppositeSideCfgApplication = theCfgApplication;
}

//-----------------------------------------------------------------
//##ModelId=3FA161000089
ALM_AppIf& PM_GenericApplication::GetAlmApplication()
{
    if(!myAlmApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM application does not exist");
    }

    return *myAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000099
void PM_GenericApplication::SetAlmApplication(ALM_AppIf* theAlmApplication)
{
    myAlmApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610000B8
ALM_AppIf& PM_GenericApplication::GetAlmOptApplication()
{
    if(!myAlmOptApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM optical application does not exist");
    }

    return *myAlmOptApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610000C8
void PM_GenericApplication::SetAlmOptApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOptApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610000E7
ALM_AppIf& PM_GenericApplication::GetAlmOtsApplication()
{
    if(!myAlmOtsApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Ots application does not exist");
    }

    return *myAlmOtsApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610000F7
void PM_GenericApplication::SetAlmOtsApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOtsApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000116
ALM_AppIf& PM_GenericApplication::GetAlmOtsOhApplication()
{
    if(!myAlmOtsOhApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Ots Oh application does not exist");
    }

    return *myAlmOtsOhApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000126
void PM_GenericApplication::SetAlmOtsOhApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOtsOhApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000145
ALM_AppIf& PM_GenericApplication::GetAlmOtuApplication()
{
    if(!myAlmOtuApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Otu application does not exist");
    }

    return *myAlmOtuApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000154
void PM_GenericApplication::SetAlmOtuApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOtuApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000183
ALM_AppIf& PM_GenericApplication::GetAlmOduApplication()
{
    if(!myAlmOduApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Odu application does not exist");
    }

    return *myAlmOduApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000184
void PM_GenericApplication::SetAlmOduApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOduApplication = theAlmApplication;

}

//-----------------------------------------------------------------
ALM_AppIf& PM_GenericApplication::GetAlmTcmApplication()
{
    if(!myAlmTcmApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Tcm application does not exist");
    }

    return *myAlmTcmApplication;

}

//-----------------------------------------------------------------
void PM_GenericApplication::SetAlmTcmApplication(ALM_AppIf* theAlmApplication)
{
    myAlmTcmApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610001B2
ALM_AppIf& PM_GenericApplication::GetAlmOmsApplication()
{
    if(!myAlmOmsApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Oms application does not exist");
    }

    return *myAlmOmsApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610001B3
void PM_GenericApplication::SetAlmOmsApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOmsApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610001E1
ALM_AppIf& PM_GenericApplication::GetAlmRsApplication()
{
    if(!myAlmRsApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Rs application does not exist");
    }

    return *myAlmRsApplication;

}

//-----------------------------------------------------------------
ALM_AppIf& PM_GenericApplication::GetAlmMsApplication()
{
    if(!myAlmMsApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Ms application does not exist");
    }

    return *myAlmMsApplication;

}

//-----------------------------------------------------------------
ALM_AppIf& PM_GenericApplication::GetAlmHopApplication()
{
    if(!myAlmHopApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Hop application does not exist");
    }

    return *myAlmHopApplication;

}


//-----------------------------------------------------------------
ALM_AppIf& PM_GenericApplication::GetAlmGfpApplication()
{
    if(!myAlmGfpApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM GFP application does not exist");
    }

    return *myAlmGfpApplication;

}

//-----------------------------------------------------------------
ALM_AppIf& PM_GenericApplication::GetAlmRmonApplication()
{
    if(!myAlmRmonApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM RMON application does not exist");
    }

    return *myAlmRmonApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610001E2
void PM_GenericApplication::SetAlmRsApplication(ALM_AppIf* theAlmApplication)
{
    myAlmRsApplication = theAlmApplication;

}

//-----------------------------------------------------------------
void PM_GenericApplication::SetAlmMsApplication(ALM_AppIf* theAlmApplication)
{
    myAlmMsApplication = theAlmApplication;

}

//-----------------------------------------------------------------
void PM_GenericApplication::SetAlmHopApplication(ALM_AppIf* theAlmApplication)
{
    myAlmHopApplication = theAlmApplication;

}



//-----------------------------------------------------------------
void PM_GenericApplication::SetAlmGfpApplication(ALM_AppIf* theAlmApplication)
{
    myAlmGfpApplication = theAlmApplication;

}

//-----------------------------------------------------------------
void PM_GenericApplication::SetAlmRmonApplication(ALM_AppIf* theAlmApplication)
{
    myAlmRmonApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000210
ALM_AppIf& PM_GenericApplication::GetAlmOscOchApplication()
{
    if(!myAlmOscOchApplication)
    {
        FC_THROW_ERROR(FC_RuntimeError, "ALM Osc Och application does not exist");
    }

    return *myAlmOscOchApplication;

}

//-----------------------------------------------------------------
//##ModelId=3FA161000211
void PM_GenericApplication::SetAlmOscOchApplication(ALM_AppIf* theAlmApplication)
{
    myAlmOscOchApplication = theAlmApplication;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8B039D
void PM_GenericApplication::SetCardActiveRegionRef(T6100_CardActiveRegion &theCardActiveRegion)
{
    myCardActiveRegionPtr = &theCardActiveRegion;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8C00B0
T6100_CardActiveRegion& PM_GenericApplication::GetCardActiveRegionRef() const
{
    if(!myCardActiveRegionPtr)
    {
        FC_THROW_ERROR(FC_RuntimeError, "Card Active Region does not exist");
    }

    return *myCardActiveRegionPtr;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D0089
void PM_GenericApplication::SetPmProcessor(PM_Processor& theProcessor)
{
        myProcessor = &theProcessor;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D013D
PM_Processor& PM_GenericApplication::GetPmProcessor() const
{
    if(!myProcessor)
    {
        FC_THROW_ERROR(FC_RuntimeError, "Pm Processor does not exist");
    }

    return *myProcessor;
}

//-----------------------------------------------------------------
//##ModelId=3C22418C01F9
TEL_BbRegionBaseImp<PM_BbDefectData>* PM_GenericApplication::GetRegionDefectData()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Data not initialized");

    return NULL;

};

//-----------------------------------------------------------------
//##ModelId=3C22418C01FB
TEL_BbRegionBaseImp<PM_BbCountData>* PM_GenericApplication::GetRegionCountData()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Data not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectMsNearEnd>* PM_GenericApplication::GetRegionDefectMsNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Near-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbFailureMsNearEnd>* PM_GenericApplication::GetRegionFailureMsNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region failure Near-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountMsNearEnd>* PM_GenericApplication::GetRegionCountMsNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Near-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusMsNearEnd>* PM_GenericApplication::GetRegionStatusMsNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Near-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectGfp>* PM_GenericApplication::GetRegionDefectGfp()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect GFP not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountGfp>* PM_GenericApplication::GetRegionCountGfp()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count GFP not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectMsFarEnd>* PM_GenericApplication::GetRegionDefectMsFarEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Far-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbFailureMsFarEnd>* PM_GenericApplication::GetRegionFailureMsFarEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region failure Far-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountMsFarEnd>* PM_GenericApplication::GetRegionCountMsFarEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Far-End MS not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectHopNearEnd>* PM_GenericApplication::GetRegionDefectHopNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Near-End HOP not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbFailureHopNearEnd>* PM_GenericApplication::GetRegionFailureHopNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region failure Near-End HOP not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountHopNearEnd>* PM_GenericApplication::GetRegionCountHopNearEnd()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Near-End HOP not initialized");

    return NULL;

};


//-----------------------------------------------------------------
//##ModelId=3FA16100023F
TEL_BbRegionBaseImp<PM_BbCountEon>* PM_GenericApplication::GetRegionCountEon()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Eon not initialized");

    return NULL;

};

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D01B5
TEL_BbRegionBaseImp<PM_BbDefectOtu>* PM_GenericApplication::GetRegionDefectOtu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Otu not initialized");

    return NULL;

};

//-----------------------------------------------------------------
//##ModelId=3C9255A10217
TEL_BbRegionBaseImp<PM_BbCountOtu>* PM_GenericApplication::GetRegionCountOtu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Otu. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusOtu>* PM_GenericApplication::GetRegionStatusOtu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status OTU not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusOtuGauge>* PM_GenericApplication::GetRegionStatusOtuGauge()
{         
    FC_THROW_ERROR(FC_SWError, "PM: region status OTU GAUGE not initialized");

    return NULL;

};

//-----------------------------------------------------------------
//##ModelId=3C50162202BB
TEL_BbRegionBaseImp<PM_BbStatusLaser>* PM_GenericApplication::GetRegionStatusLaser()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Laser. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C22418C0204
TEL_BbRegionBaseImp<PM_BbStatusOpt>* PM_GenericApplication::GetRegionStatusOpt()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Opt. not initialized");

    return NULL;

}

TEL_BbRegionBaseImp<PM_BbStatusOptCounter>* PM_GenericApplication::GetRegionStatusOptCounter()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Opt COUNTER. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D0224
TEL_BbRegionBaseImp<PM_BbDefectOpt>* PM_GenericApplication::GetRegionDefectOpt()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Opt. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D0261
TEL_BbRegionBaseImp<PM_BbStatusOms>* PM_GenericApplication::GetRegionStatusOms()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Oms not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D029D
TEL_BbRegionBaseImp<PM_BbDefectOms>* PM_GenericApplication::GetRegionDefectOms()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Oms not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C22418C020E
TEL_BbRegionBaseImp<PM_BbStatusCop>* PM_GenericApplication::GetRegionStatusCop()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Cop. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C8D02E2
TEL_BbRegionBaseImp<PM_BbDefectCop>* PM_GenericApplication::GetRegionDefectCop()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Cop. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountRmon>* PM_GenericApplication::GetRegionCountRmon()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count RMON not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusRmon>* PM_GenericApplication::GetRegionStatusRmon()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status RMON not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectOdu>* PM_GenericApplication::GetRegionDefectOdu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Odu not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusOdu>* PM_GenericApplication::GetRegionStatusOdu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Odu not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusOduGauge>* PM_GenericApplication::GetRegionStatusOduGauge()
{         
    FC_THROW_ERROR(FC_SWError, "PM: region status ODU GAUGE not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountOdu>* PM_GenericApplication::GetRegionCountOdu()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Odu. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbDefectTcm>* PM_GenericApplication::GetRegionDefectTcm()
{
    FC_THROW_ERROR(FC_SWError, "PM: region defect Tcm not initialized");

    return NULL;

};

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbCountTcm>* PM_GenericApplication::GetRegionCountTcm()
{
    FC_THROW_ERROR(FC_SWError, "PM: region count Tcm. not initialized");

    return NULL;

}

//-----------------------------------------------------------------
TEL_BbRegionBaseImp<PM_BbStatusTcmGauge>* PM_GenericApplication::GetRegionStatusTcmGauge()
{
    FC_THROW_ERROR(FC_SWError, "PM: region status Tcm not initialized");

    return NULL;

};


//-----------------------------------------------------------------
//##ModelId=3C9255A10267
PM_RegionImp<PM_BbCfg>* PM_GenericApplication::GetDayRegionConfig()
{
    FC_THROW_ERROR(FC_SWError, "PM: region Day control not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A1027B
PM_RegionImp<PM_BbCfg>* PM_GenericApplication::Get15MRegionConfig()
{
    FC_THROW_ERROR(FC_SWError, "PM: region 15M control not initialized");

    return NULL;

}

//-----------------------------------------------------------------
PM_RegionImp<PM_BbCfg>* PM_GenericApplication::GetRegionConfig(CT_PM_Period thePeriod)
{
    switch (thePeriod)
    {
        case CT_PM_PERIOD_15_MINUTES:
            return Get15MRegionConfig();
        case CT_PM_PERIOD_1_DAY:
            return GetDayRegionConfig();
        case CT_PM_PERIOD_UNKNOWN:
        default:
            FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
            return NULL;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C9255A10290
PM_RegionImp<PM_BbValue>* PM_GenericApplication::Get15MCurrentRegionValue()
{
    FC_THROW_ERROR(FC_SWError, "PM: region 15M current not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A102A4
PM_RegionImp<PM_BbValue>* PM_GenericApplication::GetDayCurrentRegionValue()
{
    FC_THROW_ERROR(FC_SWError, "PM: region Day current not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A102B8
PM_RegionImp<PM_BbValue>* PM_GenericApplication::GetCurrentRegionValue(CT_PM_Period thePeriod)
{
    switch (thePeriod)
    {
        case CT_PM_PERIOD_15_MINUTES:
            return Get15MCurrentRegionValue();
        case CT_PM_PERIOD_1_DAY:
            return GetDayCurrentRegionValue();
        case CT_PM_PERIOD_UNKNOWN:
        default:
            FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
            return NULL;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C9255A102F3
PM_RegionImp<PM_BbRequest>* PM_GenericApplication::GetRegionRequest()
{
    FC_THROW_ERROR(FC_SWError, "PM: region request not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A10308
PM_RegionImp<PM_BbValue>* PM_GenericApplication::GetPreviousRegionValue(CT_PM_Period thePeriod)
{
    switch (thePeriod)
    {
        case CT_PM_PERIOD_15_MINUTES:
            return Get15MPreviousRegionValue();
        case CT_PM_PERIOD_1_DAY:
            return GetDayPreviousRegionValue();
        case CT_PM_PERIOD_UNKNOWN:
        default:
            FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
            return NULL;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C9255A10343
PM_RegionImp<PM_BbValue>* PM_GenericApplication::Get15MPreviousRegionValue()
{
    FC_THROW_ERROR(FC_SWError, "PM: region 15M previous value not initialized");

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A10358
PM_RegionImp<PM_BbValue>* PM_GenericApplication::GetDayPreviousRegionValue()
{
    FC_THROW_ERROR(FC_SWError, "PM: region Day previous value not initialized");

    return NULL;

}

//-----------------------------------------------------------------
uint32 PM_GenericApplication::GetMaxRegionObjects()
{
    FC_THROW_ERROR(FC_SWError, "PM: Maximum no of objects in region not initialized");

    return 1;
}

//-----------------------------------------------------------------
//##ModelId=3C9255A10375
void PM_GenericApplication::SetWarning(bool theState)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: Test menu command not Supported" );

}

//-----------------------------------------------------------------
void PM_GenericApplication::AllocateTca( PM_RegionImp<PM_BbValue>* theValueRegion, uint32 theNumberOfObjects )
{
    PM_BbValue* valueObject;

    for( uint32 i=0; i<theNumberOfObjects; i++ )
    {
        valueObject = &(*(theValueRegion))[i];
        valueObject->AllocateTca();
    }
}

//-----------------------------------------------------------------
FC_Time PM_GenericApplication::GetControlPeriodTimeStamp( CT_PM_Period thePeriod )
{
    return myControlPeriodTimestamp[thePeriod];
}

//-----------------------------------------------------------------
void PM_GenericApplication::SetControlPeriodTimeStamp( CT_PM_Period thePeriod, FC_Time theStartTime )
{
    myControlPeriodTimestamp[thePeriod] = theStartTime;
}

//-----------------------------------------------------------------
uint32 PM_GenericApplication::GetSortValue()
{
    FC_THROW_ERROR(FC_SWError, "PM: not supported in base class");
    return 0;
}

/*
//-----------------------------------------------------------------
CT_PM_Sts_Offset GetOffset()
{
    FC_THROW_ERROR(FC_SWError, "PM: not supported in base class");

    return 0;
}

//-----------------------------------------------------------------
uint32 GetSignalType( uint32 theEntity )
{
    FC_THROW_ERROR(FC_SWError, "PM: not supported in base class");

    return 0;
}
*/

//-----------------------------------------------------------------
CT_PM_Side PM_GenericApplication::GetSide()
{
    return mySide;
}


//-----------------------------------------------------------------
uint32 PM_GenericApplication::GetMaxEntities()
{
    return myMaxEntities;
}

//-----------------------------------------------------------------
uint32 PM_GenericApplication::GetMaxParams()
{
    FC_THROW_ERROR(FC_SWError, "PM_GenericApplication::GetMaxParams(): not supported in base class");
    return 0;
}

//-----------------------------------------------------------------
CT_PM_LayerType PM_GenericApplication::GetLayerType()
{
    FC_THROW_ERROR(FC_SWError, "PM_GenericApplication::GetLayerType(): not supported in base class");
    return CT_PM_LAYER_UNKNOWN;
}

//-----------------------------------------------------------------
CT_PMA_ParamId PM_GenericApplication::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
    FC_THROW_ERROR(FC_SWError, "PM_GenericApplication::ConvertPmIdToPmaId(): not supported in base class");
    return PMA_INVALID_PARAMETER;
}

//-----------------------------------------------------------------
bool PM_GenericApplication::IsProcessorActionRunning()
{
    FC_THROW_ERROR(FC_SWError, "PM_GenericApplication::IsProcessorActionRunning(): not supported in base class");
    return false;
}

//-----------------------------------------------------------------
void PM_GenericApplication::SetPreviousRegionReady( CT_PM_Period thePeriod, bool theState )
{
}

//-----------------------------------------------------------------
void PM_GenericApplication::RegisterSubAppToMap( T6100_SlotIf& theSlotIf )
{
    theSlotIf.GetPmSubAppMap().RegisterSubApp( this );
}

//-----------------------------------------------------------------
void PM_GenericApplication::SetLayerName( string theLayerName )
{
    myLayerName = theLayerName;
}

//-----------------------------------------------------------------
PM_TestMenuInSubApp& PM_GenericApplication::GetTestMenu()
{
    return *myTestMenu;
}

//-----------------------------------------------------------------
string& PM_GenericApplication::GetLayerName()
{
    return myLayerName;
}

//-----------------------------------------------------------------
string& PM_GenericApplication::GetParamName( CT_PM_Parameter theParam )
{
    return defaultString;
}

//-----------------------------------------------------------------
string& PM_GenericApplication::GetParamUnit( CT_PM_Parameter theParam )
{
    return defaultString;
}

//-----------------------------------------------------------------
T6100_ObjectAllocManager& PM_GenericApplication::GetObjectAllocMgr()
{
    T6100_ObjectAllocManager* mgrPtr = NULL;
    FC_THROW_ERROR(FC_SWError, "PM_GenericApplication::GetObjectAllocMgr(): not supported in base class");
    return *mgrPtr;
}

//-----------------------------------------------------------------
void PM_GenericApplication::SetFileStoreIndex( uint32 theFileStoreIndex )
{
    myFileStoreIndex = theFileStoreIndex;
}

