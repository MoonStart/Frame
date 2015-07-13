/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Signal Alarm application base class definition.
--------------------------------------------------------------------------*/
#ifndef __ALM_APP_IF_H__
#define __ALM_APP_IF_H__

#include <ctime>
#include <string>

#include <AppFramework/FC_BbApp.h>

#include <CommonTypes/CT_TelAlarmCondition.h>
#include <CommonTypes/CT_AM_Definitions.h>

//Forward class declaration
class FC_Context;
class ALM_FailureBase;
template <class OBJECT_TYPE> class ALM_FailureRegionImp;
class ALM_LayerFailures;
class T6100_CardActiveRegion;

//This is the alarm processing application interface, which is used as a base class by the alarm applications.
//##ModelId=3C506C350155
class ALM_AppIf : public FC_BbApp
{
public:

	//Class default constructor.
	//##ModelId=3C506C3501CD
	ALM_AppIf();

	//Virtual destructor.
	//##ModelId=3C506C3501CE
	virtual ~ALM_AppIf();

	//Retrieve the status of a failure using the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //PARAM int index = 0: the index of the BB object within the region.
    //
    //RETURN bool: the status of the failure.
	//##ModelId=3DBFFAE801E4
    bool GetStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index = 0) const;

	//Retrieve the occurring time of a failure using the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
    //
    //PARAM int index = 0: the index of the BB object within the region.
	//##ModelId=3DBFFAE80356
    time_t GetOccurTime(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index = 0) const;

	//Retrieve the status of a Signal Protect defect using the signal alarm common type.
    //
    //PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type
    // which is only one of the Signal Protect alarms.
    //
    //PARAM int index = 0: the index of the BB object within the region.
    //
    //RETURN bool: the status of the failure.
    bool GetSigProtStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index = 0) const;

    /**
     * Clear the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, int theMatePort, CT_DirectionFlag theMatePortType, uint32 theMateStartChannel);

	/**
     * Clear the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, bool IsYCablePROTNA=false);

    /**
     * Set the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, int theMatePort, CT_DirectionFlag theMatePortType, uint32 theMateStartChannel);

    /**
     * Set the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int index, bool IsYCablePROTNA=false);


	//This method returns a pointer to the filtered failures region.
    //
    //RETURN ALM_FailureRegionImp<ALM_FailureBase>*: pointer to the filtered failures region.
	//##ModelId=3C6D0E5F03B4
	virtual ALM_FailureRegionImp<ALM_FailureBase>* GetFilteredRegionPtr() const;

	//Command not implemented. This method wakes-up.
	//##ModelId=3C506C350232
    virtual void WakeUpTimeBeforeTransfer();

	//Get the number of elements i.e. BB objects in the region instantiated in 
	//this application.
	//
	//RETURN number of elements i.e. BB objects.
	//##ModelId=3C506C35023C
    virtual int GetNumberOfElement() const;

    //Get the offset to be used, if any, into the monitored region.
	//
	//RETURN offset
    virtual int GetMonElementOffset() const;

	//Get the pointer to the layer failure instance according to the index.
	//
	//PARAM int theIndex: the index of the layer failure in the vector. It 
	//corresponds to the index of the BB object associated to the layer failure 
	//object.
	//
	//RETURN ALM_LayerFailures*: a pointer to the corresponding layer failure 
	//action.
	//##ModelId=3C95FE0A0187
    virtual ALM_LayerFailures* GetLayerFailurePtr(int theIndex) const;

    //Return a flag indicate that all defects must be masked.
    //
    //PARAM int theIndex: the index of the layer failure in the vector. It corresponds to the index of the BB object associated to the layer failure object.
    //
    //RETURN bool: a flag to indicate that all failures must be masked.
	//##ModelId=3CC4D1D400BF
    virtual bool GetMaskAllDefectFlag(int theIndex) const;

	//Return the suffix of a blackboard key.
	//
	//RETURN const string&: the BB key suffix.
	//##ModelId=3CC4D1D40173
    virtual const string& GetKeySuffix() const;

    //Return the instance name of this instance as a string of characters.
    //
    //RETURN const char*: the instance name.
	//##ModelId=3CC4D1D401D7
    virtual const char* GetInstanceName(void ) const;

    //Return the context of this application as a FC_Context.
    //
    //RETURN FC_Context&: a reference to the context.
	//##ModelId=3CC4D1D40281
    virtual FC_Context& GetContext() const;

	//Get the context status region.
	//
	//RETURN T6100_CardActiveRegion&: a reference to the context status region.
	//##ModelId=3DBFFAE90159
    virtual T6100_CardActiveRegion& GetContextStatusRegion(void) const;

	//Wakeup polling process.
	//##ModelId=3DBFFAE9023F
    virtual bool WakeUpAlm();

	//Suspend polling process.
	//##ModelId=3DBFFAE902E9
    virtual bool SuspendAlm();

    //Get status of a polling process
    virtual bool GetAlmAppState();

    //Set the application debug flag
    virtual void SetTraceFlag(bool theDebugFlag);
};

#endif  // __ALM_APP_IF_H__
