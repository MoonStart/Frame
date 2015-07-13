/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette, Patrick Meehan
 DESCRIPTION:   This class represents all failures with in a layer for 
                Signal Alarm. The class object, when instantiated, is the
				primary interface to MON for retrieving, soaking, and updating
				the Signal Alarm region.
--------------------------------------------------------------------------*/
#ifndef ALM_LAYERFAILURES_H
#define ALM_LAYERFAILURES_H

#include <ExecutionSupport/FC_Action.h>

#include "../ALM_FPCommon.h"
#include "ALM_DefectStatusDefinition.h"

// Foward declaration of classes
class ALM_FailureBase;
class FC_BbRegion;
class FC_OneShotProcess;
class ALM_NormalFailure;
class ALM_AppIf;
class ALM_SubApplicationOnCard;

//Macro definition
#define ALM_GET_DEFECT_STATUS(aMonitor, aMonDefect, anAlmDefect) \
    aMonitor.GetDefectStatus(aMonDefect, &aTCount, &aStatus); \
    itsDefect[anAlmDefect].SetTCount(aTCount); \
    itsDefect[anAlmDefect].SetStatus(aStatus); \
    if (aStatus) { aBitFieldDefect += (1 << anAlmDefect);  }

/**
 * This class is the action base class for each Signal layer which has failures to
 * be processed. It is responsible for filtering and soaking all failures for a
 * given layer. The specific information of a layer comes from the derived class.
 * This class is the entry point of an action; it is derived from FC_Action, so
 * the DoRunWithReason() method must be defined. Before calling DoRunWithReason()
 * method, the derived class must register all failures to process using the AddAt()
 * method. Each failure type must be defined in the derived class as either a type
 * ALM_SoakingFailure or type ALM_NormalFailure failure. The ReadDefects() method
 * must also be defined by the derived class, which is used to retrieve the condition
 * status and transition count of all the layer defects from the MON region.
 */
//##ModelId=3C506C3200D8
class ALM_LayerFailures: public FC_Action
{

public:

    /**
     * Constructor for this class.
     * 
     * PARAM const ALM_FailureNb theNbOfFailure: the number of failure handle by this object.
     * 
     * PARAM ALM_IndexNb theIndex: the index of this object in the region.
     * 
     * PARAM ALM_AppIf& theApplication: a reference to the Saignal Alarm application interface.
     * 
     * PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: a pointer to the hierarchically higher layer.
     * 
     * PARAM const ALM_FailureNb theNbOfSigProtSoakFailure: the number of Signal Protect failures which must be soaked
     *                                                      prior to reporting/clearing the alarm to Alarm Management (AM).
     */
    //##ModelId=3C506C32013D
    ALM_LayerFailures (const ALM_FailureNb theNbOfFailure,
        ALM_IndexNb theIndex,
        ALM_AppIf& theApplication,
        ALM_LayerFailures* theHigherLayerPtr = NULL,
        const ALM_FailureNb theNbOfSigProtSoakFailure = 0);

    //Destructor for this class.
    //##ModelId=3C506C320151
    virtual ~ALM_LayerFailures();

    //Obsolete.
    //##ModelId=3C506C320153
    virtual void Run( FC_Object* theObject = NULL );

    /**
     * This overloaded method, is the entry point for the execution of Signal Alarm
     * on the smart cards. The method is called once every 500 ms for each Signal
     * Alarm sub-application created on the card. It will first read the defects of
     * the specific specified layer from the MON region using the ReadDefects()
     * pure virtual method, and then apply that layers predefined filter. The result
     * is a filtered bit map containing the layers current failure status. It will
     * then call the DefectUpdated() method of either the ALM_NormalFailure or
     * ALM_SoakingFailure class (depending on the defined type) for each failure to
     * determine the current failure condition, and whether the failure is to be
     * soaked or not. If the failures type is defined as ALM_NormalFailure, the
     * current failure status is returned. Otherwise, the failure type is defined as
     * ALM_SoakingFailure and the soaking/recovery state machine is applied before
     * the failure status is returned. If the returned failure status from the
     * DefectUpdated() method indicates a change in status, the FailureFiltering()
     * method is called to update the failure status in the Signal Alarm blackboard
     * region.
     * 
     * PARAM unsigned theRunReason: integer identifier defined and provided by the 
     * invoker object to distinguish between various conditions that led to 
     * running this action.
     * 
     * PARAM FC_Object* theInvokerObj: address of the object invoking the Run 
     * method on this action.
     * 
     * PARAM C_Object* theParam: generic parameter to be passed to the action. By 
     * default this parameter is set to NULL. Used for compatibility.
     * 
     * RETURN FC_Object*: return NULL for compatibility.
     */
    //##ModelId=3DBFFAE4030A
    virtual FC_Object* DoRunWithReason( unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam);

    /**
     * This method reads all the defect conditions associated to the layer. The
     * behavior depends on the derived class.
     * 
     * RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
     */
    //##ModelId=3C506C32015C
    virtual ALM_BitField ReadDefects() const = 0;

    /**
     * This method applies the filter to the layers current raw
	 * failure status and then updates the Signal Alarm blackboard
	 * region if a change in the defect status has occurred.
     */
    //##ModelId=3C506C320166
    virtual void FailureFiltering();

    //Get the bit field mask that will be used to filter all failures of the 
    //lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    //##ModelId=3C506C320171
    virtual ALM_BitField GetFilterAllMask() const = 0;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
	//##ModelId=3F954C3000DD
    virtual ALM_BitField GetNoFilterMask() const;


    /**
     * This method filters failures associated to a layer using the failure
     * hierarchy table defined into the derived class. If no failure hierarchy
     * is applied to the layer, the base class's method can be used. In that
     * case, the method returns the value of theFailure.
     * 
     * PARAM ALM_BitField theFailure: the status of all failures (handle by this
     *     class) concatenated in a bit field.
     * 
     * RETURN ALM_BitField: the status of all failures (handle by this class)
     *     concatenated in a bit field once they are filtered.
     */
    //##ModelId=3C506C320179
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    //Get the defect filter type to apply to the lower layer.
    //
    //RETURN ALM_FilterType: the failure filter type.
    //##ModelId=3C506C320183
    inline ALM_FilterType GetFailureFilterType() const;

    //Get the failure filter type to apply to the lower layer.
    //
    //RETURN ALM_FilterType: the defect filter type.
    //##ModelId=3C506C320184
    inline ALM_FilterType GetDefectFilterType() const;

    //Set the higher layer.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr: a pointer to the hierarchically higher layer.
    //##ModelId=3C95FE0801B6
    inline void SetHigherLayerPtr(ALM_LayerFailures* theHigherLayerPtr);

    ALM_LayerFailures*  GetHigherLayerPtr() {return itsHigherLayerPtr;};

    // Invoke the ALM_SoakFailure's DefectUpdated method for Signal Protect.
    inline void InvokeSPSoakFailureDefectUpdated(CT_TelAlarmCondition::CT_FacilityAlarmType theDefect, 
                                                 bool theStatus,
                                                 bool IsYCablePROTNA);

    //Reset this layer failure. Called when the context is deactivated.
    //##ModelId=3C95FE08021A
    void Reset();

    // Signal Protect enumerations for the SP Defects which must be SOAKED.
    enum ALM_SP_Soak_DefectType
    {
        SOAK_SP_NOT_SA = 0,
        SOAK_SP_STRM_A_NR,
        SOAK_SP_ALM_MATE_ID,
        SOAK_SP_PROTNA_UID,
        SOAK_SP_ODUKP_NOT_SA,
        SOAK_SP_ODUKP_PROTNA_UID,
        SOAK_SP_FOP_PM_UID,
        SOAK_SP_FOP_NR_UID,
        ALM_SP_INVALID_SOAK_DEFECT,
        ALM_SP_NB_OF_SOAK_DEFECT = ALM_SP_INVALID_SOAK_DEFECT
    };

protected:

    /**
     * Pointer to our filtered failure region region.
     */
    //##ModelId=3C515E2A030B
    ALM_FailureRegionImp<ALM_FailureBase>* itsFilteredFailureRegionPtr;

    /**
     * Reference to its Filtered Failure Base object within the blackboard.
     */
    //##ModelId=3C506FBA011F
    ALM_FailureBase& itsFilteredFailureBase;

    /**
     * Reference to the Signal Alarm application.
     */
    //##ModelId=3C506FBA013E
    ALM_SubApplicationOnCard& myApplication;

    /**
     * Type of defect filter to apply on defects of lower layer.
     */
    //##ModelId=3C627EA3006A
    ALM_FilterType itsDefectFilterType;

    /**
     * Type of failure filter to apply on failures of lower layer.
     */
    //##ModelId=3C627EA300F5
    ALM_FilterType itsFailureFilterType;

    /**
     * Index associated to the BB object in the region. This index can be
     * a Port Number or a Channel Number depending on the context on which
     * this object is instanciated.
     */
    //##ModelId=3C60A209013A
    ALM_IndexNb itsIndex;

    /**
     * Bit field containing the layer's raw failure value.
     */
    //##ModelId=3C606BAD0360
    ALM_BitField itsRawFailure;

    /**
     * Bit field containing the layer's filtered failure value.
     */
    //##ModelId=3C606BAD03BB
    ALM_BitField itsFilteredFailure;

    /**
     * Status of all defects within the layer. This structure includes the
     * status (true or false) and the transition count.
     */
    //##ModelId=3C506FBA01AC
    ALM_DefectStatus* itsDefect;

    /**
     * Status of all Signal Protect Soak alarms.
     * status (true or false) and the transition count.
     */
    ALM_DefectStatus* itsSigProtSoakDefect;

    /**
     * Method used by the derived class to to add a failure object to
	 * itsFailures array.
     * 
     * PARAM ALM_FailureNb theIndex: the zero base failure index, as defined
     *     by the derived class.
     * 
     * PARAM ALM_NormalFailure* theFailurePtr: a pointer of the normal or
     *     soaking failure wich is to be added to the table.
     */
    //##ModelId=3C506C32022D
    void AddAt (ALM_FailureNb theIndex, ALM_NormalFailure* theFailurePtr);

    /**
     * Method used by the derived class to to add a failure object to
	 * itsSigProtSoakFailures array.
     * 
     * PARAM ALM_FailureNb theIndex: the zero base failure index, as defined
     *     by the derived class.
     * 
     * PARAM ALM_NormalFailure* theFailurePtr: a pointer of the normal or
     *     soaking failure wich is to be added to the table.
     */
    //##ModelId=3C506C32022D
    void AddSigProtSoakAt (ALM_FailureNb theIndex, ALM_NormalFailure* theFailurePtr);

    /**
     * This method is called right after defects of a layer are soaked. It is used 
     * to put any behavior defined by the derived class. The base class has no 
     * behavior.
     */
    //##ModelId=3C506C320242
    virtual void ProcessAfterSoaking();

    /**
     * This method returns true if all defects must be masked.
     * 
     * RETURN bool: true if defect must be all filtered, false otherwise.
     */
    //##ModelId=3CC4D1D201A2
    bool MaskAllDefect() const;

    /**
     * Pointer to the higher layer of this layer. This pointer is used to get
     * the bit field defect of the higher layer to know the type of filter
     * type to apply to this layer. Note that if this layer is the highest of
     * the hierarchy, itsHigherLayer pointer is null.
     */
    //##ModelId=3C515E2A0372
    ALM_LayerFailures* itsHigherLayerPtr;

    /**
     * Return the Signal Protect Alarm Type corresponding to the index
     * with respect to the enum ALM_SP_Soak_DefectType().
     */
    CT_TelAlarmCondition::CT_FacilityAlarmType GetSigProtSoakTypeFromIndex(int theIndex) const;

private:

    /**
     * Use to get and initialize memory space to kept pointers to ALM_NormalFailure
     * instances. Note that, these pointers can point to any type of ALM_NormalFailure.
     * The class instantiated depends on the behavior related to the failure type.
     */
    //##ModelId=3C506C320273
    void GetInitFailurePtr();

    /**
     * Number of defined failures within this layer.
     */
    //##ModelId=3C60A20901E4
    const ALM_FailureNb itsNbOfFailure;

    /**
     * Number of defined SigProtSoak failures within this layer.
     */
    const ALM_FailureNb itsNbOfSigProtSoakFailure;

    /**
     * Pointer to an array that contains Failure object pointers for all failures of
     * a given layer. These pointers are initialized to NULL by the constructor, and
     * set to their respective value using AddAt method by the derived class. Note that,
     * the memory is allocated by the constructor of the DERIVED CLASS and deallocated
     * by the destructor of THIS CLASS.
     */
    //##ModelId=3C506FBA0238
    ALM_NormalFailure** itsFailureTable;

    /**
     * Pointer to an array that contains Failure object pointers for all SigProtSoak failures
     * of a given layer. These pointers are initialized to NULL by the constructor, and
     * set to their respective value using AddSigProtSoakAt method by the derived class. Note that,
     * the memory is allocated by the constructor of the DERIVED CLASS and deallocated
     * by the destructor of THIS CLASS.
     */
    ALM_NormalFailure** itsSigProtSoakFailureTable;
};


//-----------------------------------------------------------------
//##ModelId=3C506C320183
inline ALM_FilterType ALM_LayerFailures::GetFailureFilterType() const
{
    if ((itsFailureFilterType == ALM_FILTER_LOCAL) && itsHigherLayerPtr)
    {
        return itsHigherLayerPtr->GetFailureFilterType();
    }

    return itsFailureFilterType;
}

//-----------------------------------------------------------------
//##ModelId=3C506C320184
inline ALM_FilterType ALM_LayerFailures::GetDefectFilterType() const
{
    if ((itsDefectFilterType == ALM_FILTER_LOCAL) && itsHigherLayerPtr)
    {
        return itsHigherLayerPtr->GetDefectFilterType();
    }

    return itsDefectFilterType;
}

//-----------------------------------------------------------------
//##ModelId=3C95FE0801B6
inline void ALM_LayerFailures::SetHigherLayerPtr(ALM_LayerFailures* theHigherLayerPtr)
{
    itsHigherLayerPtr = theHigherLayerPtr;
}

//-----------------------------------------------------------------
// Invoke the ALM_SoakFailure's DefectUpdated method for Signal Protect.
//-----------------------------------------------------------------
inline void ALM_LayerFailures::InvokeSPSoakFailureDefectUpdated(CT_TelAlarmCondition::CT_FacilityAlarmType theDefect, 
                                                                bool theStatus,
                                                                bool IsYCablePROTNA)
{
    ALM_FailureNb Index = ALM_SP_INVALID_SOAK_DEFECT;

    if (theDefect == CT_TelAlarmCondition::ALM_SP_NOT_SA)
    {
        Index = SOAK_SP_NOT_SA;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_STRM_A_NR)
    {
        Index = SOAK_SP_STRM_A_NR;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_ALM_MATE_ID)
    {
        Index = SOAK_SP_ALM_MATE_ID;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_PROTNA_UID)
    {
        Index = SOAK_SP_PROTNA_UID;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA)
    {
        Index = SOAK_SP_ODUKP_NOT_SA;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID)
    {
        Index = SOAK_SP_ODUKP_PROTNA_UID;
    }

    else if (theDefect == CT_TelAlarmCondition::ALM_SP_FOP_PM_UID)
    {
        Index = SOAK_SP_FOP_PM_UID;
    }
    else if (theDefect == CT_TelAlarmCondition::ALM_SP_FOP_NR_UID)
    {
        Index = SOAK_SP_FOP_NR_UID;
    }

    if (Index != ALM_SP_INVALID_SOAK_DEFECT)
    {
        //---------------------------------------------------------
        // Set the itsSigProtSoakDefect[] and let the RunWithReason
        // actually call the DefectUpdated method!!!
        // NOTE: if the current Status has not changed, then
        //       ignore the notification. Signal Protect observes
        //       MON region (not a periodic process) and ALWAYS
        //       notifies ALM when the PROTNA status changes -
        //       we will not miss any set/clear/set transitions.
        //---------------------------------------------------------
        if (itsSigProtSoakDefect[Index].GetStatus() != theStatus)
        {
            itsSigProtSoakDefect[Index].SetStatus(theStatus);
            itsSigProtSoakDefect[Index].SetTCount( (((itsSigProtSoakDefect[Index].GetTCount()) + 1) % 1000) ); // max history 1000!
            itsSigProtSoakDefect[Index].SetYCablePROTNA(IsYCablePROTNA);
        }
    }
}

#endif //ALM_LAYERFAILURES_H

