/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:   Telecom Services/Facility Monitoring.
 TARGET   :   All.
 AUTHOR   :   Steve Thiffault, December 6, 2001.
 DESCRIPTION: Header file for the generic application.
--------------------------------------------------------------------------*/

#ifndef PM_GENERICAPPLICATION_H
#define PM_GENERICAPPLICATION_H

#include <AppFramework/FC_BbApp.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <CommonTypes/CT_PMA_General.h>
#include <ErrorService/FC_Error.h>

// Forward Declarator
class PM_BbDefectData;
class PM_BbDefectMsNearEnd;
class PM_BbDefectMsFarEnd;
class PM_BbDefectHopNearEnd;
class PM_BbDefectGfp;
class PM_BbDefectOdu;
class PM_BbDefectOtu;
class PM_BbDefectCop;
class PM_BbDefectOpt;
class PM_BbDefectOms;
class PM_BbDefectTcm;
class PM_BbCountData;
class PM_BbCountMsNearEnd;
class PM_BbCountMsFarEnd;
class PM_BbCountHopNearEnd;
class PM_BbCountEon;
class PM_BbCountOdu;
class PM_BbCountOtu;
class PM_BbCountGfp;
class PM_BbCountRmon;
class PM_BbCountTcm;
class PM_BbStatusTcmGauge;
class PM_BbFailureMsNearEnd;
class PM_BbFailureMsFarEnd;
class PM_BbFailureHopNearEnd;
class PM_BbStatusOpt;
class PM_BbStatusOptCounter;
class PM_BbStatusOms;
class PM_BbStatusCop;
class PM_BbStatusLaser;
class PM_BbStatusMsNearEnd;
class PM_BbStatusOtu;
class PM_BbStatusOdu;
class PM_BbStatusOduGauge;
class PM_BbStatusOtuGauge;
class PM_BbStatusRmon;
class PM_BbValue;
class PM_BbCfg;
class PM_BbRequest;
class PM_MainBaseSubApplication;
class MON_AppIf;
class CSM_AppIf;
class CFG_AppIf;
class ALM_AppIf;
class T6100_CardActiveRegion;
class T6100_SlotIf;
class PM_Processor;
class SP_1plus1BaseApplication;
template <class T> class TEL_BbRegionBaseImp;
template<class OBJECT_TYPE>class PM_RegionImp;
class PM_TestMenuInSubApp;
class T6100_ObjectAllocManager;

//This is the performance monitoring base application class.
//##ModelId=3C22418C0025
class PM_GenericApplication: public FC_BbApp
{
public:

    //Constructor.
    //##ModelId=3C22418C01D1
    PM_GenericApplication(PM_MainBaseSubApplication& thePmMainApplication,
                          CT_PM_Side                 theSide,
                          uint32                     theMaxEntities,
                          const char*                theSuffixStr = NULL);

    //Virtual destructor.
    //##ModelId=3C22418C01DB
    virtual ~PM_GenericApplication();

    //Returns a reference to the main performance monitoring 
    //application.
    //##ModelId=3C22418C01DD
    PM_MainBaseSubApplication& GetPmMainApplication();

    //Returns a pointer to the monitoring application.
    //##ModelId=3C22418C01E5
    MON_AppIf& GetMonApplication(uint32 theMonAppIndex = 0);
    MON_AppIf* GetMonApplicationPtr(uint32 theMonAppIndex = 0); 

    //Returns a pointer to the Data monitoring application.
    //##ModelId=3E6E4C8B0311
    MON_AppIf& GetMonRsApplication();

    //Returns a reference to the TX monitoring application.
    //##ModelId=3C98CCC90286
    MON_AppIf& GetMonTxApplication();

	//Returns a pointer to the TX monitoring application.
	MON_AppIf* GetMonTxApplicationPtr();

    //##ModelId=3E6E4C8B039D
    void SetCardActiveRegionRef(T6100_CardActiveRegion &theCardActiveRegion);

    //##ModelId=3E6E4C8C00B0
    T6100_CardActiveRegion& GetCardActiveRegionRef() const;

    //Sets the pointer to the monitoring application.
    //##ModelId=3C22418C01EF
    void SetMonApplication(MON_AppIf* theMonApplication, uint32 theMonAppIndex = 0);

    //Sets the pointer to the Data monitoring application.
    //##ModelId=3E6E4C8C029B
    void SetMonRsApplication(MON_AppIf* theMonRsApplication);

    //Sets the pointer to the TX monitoring application.
    //##ModelId=3C98CCC902D6
    void SetMonTxApplication(MON_AppIf* theMonTxApplication);

    //Returns a pointer to the card service module 
    //application.
    //##ModelId=3C9255A101C6
    CSM_AppIf& GetCsmApplication();

    //Sets the pointer to the card service module application.
    //##ModelId=3C9255A101DA
    void SetCsmApplication(CSM_AppIf* theCsmApplication);

    //Returns a reference to the configuration application.
    //##ModelId=3E6E4C8C034F
    CFG_AppIf& GetCfgApplication();

	//Returns a pointer to the configuration application.
    CFG_AppIf* GetCfgApplicationPtr();

    //Sets the pointer to the configuration application.
    //##ModelId=3E6E4C8C038B
    void SetCfgApplication(CFG_AppIf* theCfgApplication);

    //Returns a pointer to the opposite side configuration 
    //application.
    CFG_AppIf* GetOppositeSideCfgApplication();

    //Sets the pointer to the opposite side configuration 
    //application.
    void SetOppositeSideCfgApplication(CFG_AppIf* theCfgApplication);

    //Returns a pointer to the alarm application.
	//##ModelId=3FA161000089
    ALM_AppIf& GetAlmApplication();

    //Sets the pointer to 1+1 LAPS signal protection application.
    void Set1plus1SpApplication(SP_1plus1BaseApplication* theSpApplication);

    //Returns a pointer to the 1+1 LAPS signal protection application
    SP_1plus1BaseApplication* Get1plus1SpApplication();

    //Sets the pointer to the alarm application.
	//##ModelId=3FA161000099
    void SetAlmApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm optical application.
	//##ModelId=3FA1610000B8
    ALM_AppIf& GetAlmOptApplication();

    //Sets the pointer to the alarm optical application.
	//##ModelId=3FA1610000C8
    void SetAlmOptApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Ots application.
	//##ModelId=3FA1610000E7
    ALM_AppIf& GetAlmOtsApplication();

    //Sets the pointer to the alarm Ots application.
	//##ModelId=3FA1610000F7
    void SetAlmOtsApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Ots Oh application.
	//##ModelId=3FA161000116
    ALM_AppIf& GetAlmOtsOhApplication();

    //Sets the pointer to the alarm Ots Oh application.
	//##ModelId=3FA161000126
    void SetAlmOtsOhApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Otu application.
	//##ModelId=3FA161000145
    ALM_AppIf& GetAlmOtuApplication();
    ALM_AppIf* GetAlmOtuApplicationPtr() { return myAlmOtuApplication;}

    //Sets the pointer to the alarm Otu application.
	//##ModelId=3FA161000154
    void SetAlmOtuApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Odu application.
	//##ModelId=3FA161000183
    ALM_AppIf& GetAlmOduApplication();

    //Sets the pointer to the alarm Tcm application.
    void SetAlmTcmApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Tcm application.
    ALM_AppIf& GetAlmTcmApplication();

    //Sets the pointer to the alarm Odu application.
	//##ModelId=3FA161000184
    void SetAlmOduApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Oms application.
	//##ModelId=3FA1610001B2
    ALM_AppIf& GetAlmOmsApplication();

    //Sets the pointer to the alarm Oms application.
	//##ModelId=3FA1610001B3
    void SetAlmOmsApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Rs application.
	//##ModelId=3FA1610001E1
    ALM_AppIf& GetAlmRsApplication();

    //Returns a pointer to the alarm MS application.
    ALM_AppIf& GetAlmMsApplication();

    //Returns a pointer to the alarm HOP application.
    ALM_AppIf& GetAlmHopApplication();

    //Returns a pointer to the alarm GFP application.
    ALM_AppIf& GetAlmGfpApplication();

    //Returns a pointer to the alarm RMON application.
    ALM_AppIf& GetAlmRmonApplication();

    //Sets the pointer to the alarm Rs application.
	//##ModelId=3FA1610001E2
    void SetAlmRsApplication(ALM_AppIf* theAlmApplication);

    //Sets the pointer to the alarm Ms application.
    void SetAlmMsApplication(ALM_AppIf* theAlmApplication);

    //Sets the pointer to the alarm Hop application.
    void SetAlmHopApplication(ALM_AppIf* theAlmApplication);

    //Sets the pointer to the alarm GFP application.
    void SetAlmGfpApplication(ALM_AppIf* theAlmApplication);

    //Sets the pointer to the alarm RMON application.
    void SetAlmRmonApplication(ALM_AppIf* theAlmApplication);

    //Returns a pointer to the alarm Osc Och application.
	//##ModelId=3FA161000210
    ALM_AppIf& GetAlmOscOchApplication();

    //Sets the pointer to the alarm Osc Och application.
	//##ModelId=3FA161000211
    void SetAlmOscOchApplication(ALM_AppIf* theAlmApplication);

    //Sets PM processor.    
    //##ModelId=3E6E4C8D0089
    void SetPmProcessor(PM_Processor& theProcessor);

    //Gets PM processor.
    //##ModelId=3E6E4C8D013D
    PM_Processor& GetPmProcessor() const;

    // All the following methods should be overloaded by specific application when required,
    // otherwise they will throw.

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR DATA
    //--------------------------------------------------------
    //Returns a pointer to the Data defect region.
    //##ModelId=3C22418C01F9
    virtual TEL_BbRegionBaseImp<PM_BbDefectData>* GetRegionDefectData();

    //Returns a pointer to the Data count region.
    //##ModelId=3C22418C01FB
    virtual TEL_BbRegionBaseImp<PM_BbCountData>* GetRegionCountData();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR NEAR-END MS
    //--------------------------------------------------------
    //Returns a pointer to the MS defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectMsNearEnd>* GetRegionDefectMsNearEnd();

    //Returns a pointer to the MS defect region.
    virtual TEL_BbRegionBaseImp<PM_BbFailureMsNearEnd>* GetRegionFailureMsNearEnd();

    //Returns a pointer to the MS count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountMsNearEnd>* GetRegionCountMsNearEnd();

    //Returns a pointer to the MS status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusMsNearEnd>* GetRegionStatusMsNearEnd();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR GFP
    //--------------------------------------------------------
    //Returns a pointer to the MS defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectGfp>* GetRegionDefectGfp();

    //Returns a pointer to the MS count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountGfp>* GetRegionCountGfp();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR FAR-END MS
    //--------------------------------------------------------
    //Returns a pointer to the MS defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectMsFarEnd>* GetRegionDefectMsFarEnd();

    //Returns a pointer to the MS defect region.
    virtual TEL_BbRegionBaseImp<PM_BbFailureMsFarEnd>* GetRegionFailureMsFarEnd();

    //Returns a pointer to the MS count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountMsFarEnd>* GetRegionCountMsFarEnd();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR NEAR-END HOP
    //--------------------------------------------------------
    //Returns a pointer to the HOP defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectHopNearEnd>* GetRegionDefectHopNearEnd();

    //Returns a pointer to the HOP defect region.
    virtual TEL_BbRegionBaseImp<PM_BbFailureHopNearEnd>* GetRegionFailureHopNearEnd();

    //Returns a pointer to the HOP count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountHopNearEnd>* GetRegionCountHopNearEnd();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR EON
    //--------------------------------------------------------
    //Returns a pointer to the Eon count region.
	//##ModelId=3FA16100023F
    virtual TEL_BbRegionBaseImp<PM_BbCountEon>* GetRegionCountEon();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR OTU
    //--------------------------------------------------------
    //Returns a pointer to the OTU defect region.
    //##ModelId=3E6E4C8D01B5
    virtual TEL_BbRegionBaseImp<PM_BbDefectOtu>* GetRegionDefectOtu();

    //Returns a pointer to the OTU count region.
    //##ModelId=3C9255A10217
    virtual TEL_BbRegionBaseImp<PM_BbCountOtu>* GetRegionCountOtu();

    //Returns a pointer to the OTU status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusOtu>* GetRegionStatusOtu();

    //Returns a pointer to the OTU status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusOtuGauge>* GetRegionStatusOtuGauge();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR LASER
    //--------------------------------------------------------
    //Returns a pointer to the laser status region.
    //##ModelId=3C50162202BB
    virtual TEL_BbRegionBaseImp<PM_BbStatusLaser>* GetRegionStatusLaser();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR OPT
    //--------------------------------------------------------
    //Returns a pointer to the optical status region.
    //##ModelId=3C22418C0204
    virtual TEL_BbRegionBaseImp<PM_BbStatusOpt>* GetRegionStatusOpt();

    virtual TEL_BbRegionBaseImp<PM_BbStatusOptCounter>* GetRegionStatusOptCounter();
    
    //Returns a pointer to the optical defect region.
    //##ModelId=3E6E4C8D0224
    virtual TEL_BbRegionBaseImp<PM_BbDefectOpt>* GetRegionDefectOpt();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR OMS
    //--------------------------------------------------------
    //Returns a pointer to the oms status region.
    //##ModelId=3E6E4C8D0261
    virtual TEL_BbRegionBaseImp<PM_BbStatusOms>* GetRegionStatusOms();

    //Returns a pointer to the oms defect region.
    //##ModelId=3E6E4C8D029D
    virtual TEL_BbRegionBaseImp<PM_BbDefectOms>* GetRegionDefectOms();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR COP
    //--------------------------------------------------------
    //Returns a pointer to the optical channel status region.
    //##ModelId=3C22418C020E
    virtual TEL_BbRegionBaseImp<PM_BbStatusCop>* GetRegionStatusCop();

    //Returns a pointer to the optical channel defect region.
    //##ModelId=3E6E4C8D02E2
    virtual TEL_BbRegionBaseImp<PM_BbDefectCop>* GetRegionDefectCop();

	//--------------------------------------------------------
	//REGIONS OF COLLECTOR RMON
	//--------------------------------------------------------

	//Returns a pointer to the RMON count region.
	virtual TEL_BbRegionBaseImp<PM_BbCountRmon>* GetRegionCountRmon();

	//Returns a pointer to the RMON status region.
	virtual TEL_BbRegionBaseImp<PM_BbStatusRmon>* GetRegionStatusRmon();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR ODU
    //--------------------------------------------------------
    //Returns a pointer to the ODU defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectOdu>* GetRegionDefectOdu();

    //Returns a pointer to the ODU count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountOdu>* GetRegionCountOdu();

    //Returns a pointer to the ODU status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusOdu>* GetRegionStatusOdu();

    //Returns a pointer to the ODU status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusOduGauge>* GetRegionStatusOduGauge();

    //--------------------------------------------------------
    //REGIONS OF COLLECTOR TCM
    //--------------------------------------------------------
    //Returns a pointer to the TCM defect region.
    virtual TEL_BbRegionBaseImp<PM_BbDefectTcm>* GetRegionDefectTcm();

    //Returns a pointer to the TCM count region.
    virtual TEL_BbRegionBaseImp<PM_BbCountTcm>* GetRegionCountTcm();

    //Returns a pointer to the TCM status region.
    virtual TEL_BbRegionBaseImp<PM_BbStatusTcmGauge>* GetRegionStatusTcmGauge();

    //--------------------------------------------------------
    //REGIONS OF PROCESSOR
    //--------------------------------------------------------
    //Returns a pointer to the 1 day control region.
    //##ModelId=3C9255A10267
    virtual PM_RegionImp<PM_BbCfg>* GetDayRegionConfig();

    //Returns a pointer to the 15 minutes control region.
    //##ModelId=3C9255A1027B
    virtual PM_RegionImp<PM_BbCfg>* Get15MRegionConfig();

    //Returns a pointer to the control region.
    virtual PM_RegionImp<PM_BbCfg>* GetRegionConfig(CT_PM_Period thePeriod);

    //Returns a pointer to the 15 minutes current value 
    //region.
    //##ModelId=3C9255A10290
    virtual PM_RegionImp<PM_BbValue>* Get15MCurrentRegionValue();

    //Returns a pointer to the 1 day current value region.
    //##ModelId=3C9255A102A4
    virtual PM_RegionImp<PM_BbValue>* GetDayCurrentRegionValue();

    //Returns a pointer to the current value region.
    //##ModelId=3C9255A102B8
    virtual PM_RegionImp<PM_BbValue>* GetCurrentRegionValue(CT_PM_Period thePeriod);

    //Returns a pointer to the request region.
    //##ModelId=3C9255A102F3
    virtual PM_RegionImp<PM_BbRequest>* GetRegionRequest();
    
    //Returns a pointer to the previous value region.
    //##ModelId=3C9255A10308
    virtual PM_RegionImp<PM_BbValue>* GetPreviousRegionValue(CT_PM_Period thePeriod);
    
    //Returns a pointer to the 15 minutes previous value 
    //region.
    //##ModelId=3C9255A10343
    virtual PM_RegionImp<PM_BbValue>* Get15MPreviousRegionValue();

    //Returns a pointer to the 1 day previous value region.
    //##ModelId=3C9255A10358
    virtual PM_RegionImp<PM_BbValue>* GetDayPreviousRegionValue();

    //Returns number of objects contained in the PM regions
    virtual uint32 GetMaxRegionObjects();

    //Sets or not the display of warning.
    //##ModelId=3C9255A10375
    virtual void SetWarning(bool theState);

	// Causes PM_BbValue objects in specified region to allocate space
	// for TCA crossing event data.
	virtual void AllocateTca( PM_RegionImp<PM_BbValue>* theValueRegion, uint32 theNumberOfObjects );

	// Method to retrieve a control period timestamp.
	virtual FC_Time GetControlPeriodTimeStamp( CT_PM_Period thePeriod );

	// Method to set a control period timestamp.
	virtual void SetControlPeriodTimeStamp( CT_PM_Period thePeriod, FC_Time theStartTime );

	// Method to get the sort value of the subapplication based on side setting.
	virtual uint32 GetSortValue();

	// Method to retrieve the offset of the starting STS.
//	virtual CT_PM_Sts_Offset GetOffset();

	// Method to retrieve facility signal type.
//	virtual uint32 GetSignalType( uint32 theEntity = 0 );
	// 

	// Returns the side indication.
	virtual CT_PM_Side GetSide();

	// Returns the maximum number of entities managed by this subapp.
	virtual uint32 GetMaxEntities();

	// Returns the maximum number of parameters in the subapp instance.
	virtual uint32 GetMaxParams();

	// Returns the type of layer maintained by the subapp.
	virtual CT_PM_LayerType GetLayerType();

	// Returns the name of layer maintained by the subapp.
	virtual string& GetLayerName();

	// Converts subapp/layer param ID to PMA param ID.
	virtual CT_PMA_ParamId ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType = CT_PM_PARAM_CURRENT );

	// Method to get the state of the processor action.
	virtual bool IsProcessorActionRunning();

	// Marks the previous value region as ready in the 
	// file storage subapp vector.
	virtual void SetPreviousRegionReady( CT_PM_Period thePeriod, bool theState );

    // Register SubApp with PM_SubApplicationMap.
    virtual void RegisterSubAppToMap( T6100_SlotIf& theSlotIf );

    // Method to retrieve the embedded test menu object.
    PM_TestMenuInSubApp& GetTestMenu();

    // Test menu support to obtain a parameter name.
    virtual string& GetParamName( CT_PM_Parameter theParam );

    // Test menu support to obtain a parameter unit.
    virtual string& GetParamUnit( CT_PM_Parameter theParam );

    string GetKeySuffix(){ return myKeySuffix; }

    // Method to retrieve a reference to the object allocation manager
    virtual T6100_ObjectAllocManager& GetObjectAllocMgr();

    // Method to set index into vector in PM_FileStorageSubapplication
    virtual void SetFileStoreIndex( uint32 theFileStoreIndex );

protected:

    // Method to set the PM layer name.
    virtual void SetLayerName( string theLayerName );

    //The region key suffix string
    string              myKeySuffix;

    //The layer name string
    string              myLayerName;

    // The PM line or port side
    CT_PM_Side mySide;

    // Maximum number of entities supported by this PM subapp.
    uint32 myMaxEntities;

	// Index into vector in PM_FileStorageSubapplication
	uint32 myFileStoreIndex;

private:

    //Pointer to the main PM application.
    //##ModelId=3C22418C0345
    PM_MainBaseSubApplication&  myPmMainApplication;

    //Some modules may require multiple MON applications
    MON_AppIf* myMonApplications[CT_PM_MAX_MON_APPLICATIONS];

    //Pointer to the TX monitoring application.
    //##ModelId=3C98CCCA002F
    MON_AppIf*              myMonTxApplication;

    //Pointer to the CSM application.
    //##ModelId=3C9255A103BC
    CSM_AppIf*              myCsmApplication;

    //Pointer to the CFG application.
    //##ModelId=3E6E4C8D0351
    CFG_AppIf*              myCfgApplication;

    //Pointer to the 1+1 LAPS Signal Protection application
    SP_1plus1BaseApplication*         my1plus1SpApplication;

    //Pointer to the opposite side CFG application.
    CFG_AppIf*              myOppositeSideCfgApplication;

    //Pointer to the ALM application.
	//##ModelId=3FA16100027E
    ALM_AppIf*              myAlmApplication;

    //Pointer to the ALM Optical application.
	//##ModelId=3FA16100028E
    ALM_AppIf*              myAlmOptApplication;

    //Pointer to the ALM Ots application.
	//##ModelId=3FA1610002AD
    ALM_AppIf*              myAlmOtsApplication;

    //Pointer to the ALM Ots Oh application.
	//##ModelId=3FA1610002BD
    ALM_AppIf*              myAlmOtsOhApplication;

    //Pointer to the ALM Otu application.
	//##ModelId=3FA1610002DC
    ALM_AppIf*              myAlmOtuApplication;

    //Pointer to the ALM Odu application.
	//##ModelId=3FA1610002EB
    ALM_AppIf*              myAlmOduApplication;

    //Pointer to the ALM Tcm application.
    ALM_AppIf*              myAlmTcmApplication;

    //Pointer to the ALM Oms application.
	//##ModelId=3FA16100030B
    ALM_AppIf*              myAlmOmsApplication;

    //Pointer to the ALM Rs application.
	//##ModelId=3FA16100031A
    ALM_AppIf*              myAlmRsApplication;

    //Pointer to the ALM MS application.
    ALM_AppIf*              myAlmMsApplication;

    //Pointer to the ALM HOP application.
    ALM_AppIf*              myAlmHopApplication;

    //Pointer to the ALM GFP application.
    ALM_AppIf*              myAlmGfpApplication;

    //Pointer to the ALM RMON application.
    ALM_AppIf*              myAlmRmonApplication;
    //Pointer to the ALM Osc Och application.
	//##ModelId=3FA16100033A
    ALM_AppIf*              myAlmOscOchApplication;

    //Pointer to card status region.
    //##ModelId=3E6E4C8E0027
    T6100_CardActiveRegion* myCardActiveRegionPtr;

    //Pointer to my processor.
    //##ModelId=3E6E4C8E00BE
    PM_Processor            *myProcessor;

    // Number of MON applications
    uint32 myMonApplicationCount;

	// Pointer to control period timestamps.
	FC_Time myControlPeriodTimestamp[CT_PM_PERIOD_UNKNOWN];

    // Embedded test menu object.
    PM_TestMenuInSubApp* myTestMenu;

    // Dummy string value for base class default methods.
    static string defaultString;

};

#endif //PM_GENERICAPPLICATION_H


