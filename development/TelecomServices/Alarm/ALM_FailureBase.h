/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class maintains all failures of a layer
--------------------------------------------------------------------------*/

#ifndef ALM_FAILUREBASE_H
#define ALM_FAILUREBASE_H

#include <Blackboard/FC_BbObject.h>
#include <CommonTypes/CT_TelAlarmCondition.h>
#include <CommonTypes/CT_AM_Definitions.h>


/**
 * This is the base class for the Signal Alarm blackboard failure objects which are
 * common for all of the derived Signal Alarm classes. It provides a common interface
 * to set and retrieve the status and occurring time of each failure, as well as
 * the BB transfer interface. Additionally, some Signal Protection alarms are included
 * in the BB for various layers. Those alarms are not filtered nor modified by Signal
 * Alarm. Rather, the status of those alarms are set/cleared by Signal Protect, and
 * the built in region transfer is used to notify the AM application on the APM.
 */
//##ModelId=3C506C390205
class ALM_FailureBase : public FC_BbObject
{

public:

	/**
     * Constructor for this class. Allocate memory to store the Signal Alarm failure
     * condition of all Signal Alarm failures managed by this class. Additionally, the
     * Signal Protect uses the signal alarm region to store some of its defect statuses.
     * This data is set to default values when created.
     *
	 * PARAM int theIndex: the index of the object within the region.
	 *
	 * PARAM int theNumberOfFailure = 0: the number of Signal Alarm failures handled by
     * this layer.
     *
     * PARAM bool theDefaultStatus = false: Signal Alarm failures initial condition of
     * this layer.
     * 
	 * PARAM int theSPNumberOfFailure = 0: the number of Signal Protect defects tracked in
     * this layer.
     * 
     * PARAM int itsSigProtMatePort = 0: Signal Protect data
     * 
     * PARAM AM_PortType itsSigProtMatePortType = CT_DIR_DONT_CARE: Signal Protect data
     * 
     * PARAM uint32 itsSigProtMateStartChannel = 0: Signal Protect data
     */
	//##ModelId=3C506C39027E
    ALM_FailureBase(int theIndex,
                    int theNumberOfFailure = 0,
                    bool theDefaultStatus = false,
                    int theSigProtNumberOfFailure = 0,
                    int itsSigProtMatePort = 0,
                    CT_DirectionFlag itsSigProtMatePortType = CT_DIR_DONT_CARE,
                    uint32 itsSigProtMateStartChannel = 0);
    
	/**
     * Destructor for this class.
     */
	//##ModelId=3C506C39028A
	virtual ~ALM_FailureBase();

	/**
     * Retrieve the status of a Signal Alarm failure using the signal alarm common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * RETURN bool: the status of the failure.
     */
	//##ModelId=3C506C390292
    inline bool GetStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

	/**
     * Set the status of a Signal Alarm failure using the signal alarm common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * PARAM bool theStatus: the status of the failure to set.
     */
	//##ModelId=3C506C39029C
    inline void SetStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theStatus);

	/**
     * Retrieve the status of a Signal Protection failure using the signal alarm
     * common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * RETURN bool: the status of the failure.
     */
    inline bool GetSigProtStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;
    inline bool GetSigProtYCable (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

	/**
     * Set the status of a Signal Protection failure using the signal alarm common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * PARAM bool theStatus: the status of the failure to set.
     */
    inline void SetSigProtStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theSigProtStatus);
    inline void SetSigProtYCable (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theSigProtYCable);

	/**
     * Retrieve the occurring time of a Signal Alarm failure using the signal alarm common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * RETURN time_t: the occurring time of the failure.
     */
	//##ModelId=3C506C3902A6
    inline time_t GetOccurTime(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

	/**
     * Set the occurring time of a Signal Alarm failure using the signal alarm common type.
	 *
	 * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the 
	 * failure type defined in the common type.
	 *
	 * PARAM time_t theOccurTime: the failure occurring time to set.
     */
	//##ModelId=3C506C3902B0
    inline void SetOccurTime(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, time_t theOccurTime);

	/**
     * Retrieve the status of a failure using the zero based failure index.
     *
     * PARAM uint32 theFailureIndex: the zero based failure index.
     *
     * RETURN bool: the status of the failure.
     */
	//##ModelId=3C506C3902BA
    inline bool GetStatusFromIndex (uint32 theFailureIndex) const;

	/**
     * Set the status of a failure using the zero based failure index.
     *
     * PARAM uint32 theFailureIndex: the zero based failure index.
     *
     * PARAM bool theStatus: the status of the failure to set.
     */
	//##ModelId=3C506C3902C3
    inline void SetStatusFromIndex (uint32 theFailureIndex, bool theStatus);

	/**
     * Retrieve the status of a Signal Protect failure using the zero based failure index.
     *
     * PARAM uint32 theFailureIndex: the zero based failure index.
     *
     * RETURN bool: the status of the failure.
     */
    inline bool GetSigProtStatusFromIndex (uint32 theFailureIndex) const;
    inline bool GetSigProtYCableFromIndex (uint32 theFailureIndex) const;
    inline void SetSigProtYCableFromIndex (uint32 theFailureIndex, bool theSigProtYCable);

	/**
     * Retrieve the occurring time of a failure using the zero based failure index.
     *
     * PARAM uint32 theFailureIndex: the zero based failure index.
     *
     * RETURN time_t: the occurring time of the failure.
     */
	//##ModelId=3C506C3902CE
    inline time_t GetOccurTimeFromIndex(uint32 theFailureIndex) const;

	/**
     * Set the occurring time of a failure using the zero based failure index.
     *
     * PARAM uint32 theFailureIndex: the zero based failure index.
     *
     * PARAM time_t theOccurTime: the failure occurring time to set.
     */
	//##ModelId=3C506C3902D8
    inline void SetOccurTimeFromIndex(uint32 theFailureIndex, time_t theOccurTime);

	/**
     * Retrieve the condition (status and occurring time) of a failure using the signal alarm common type return the result writing in theCondition pointer.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type defined in the common type.
     *
     * PARAM CT_TelAlarmCondition* theCondition: pointer to the instance where alarm condition will be returned.
     */
	//##ModelId=3C506C3902E2
	void GetCondition(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, CT_TelAlarmCondition* theCondition) const;

	/**
     * Reset all failure's conditions to cleared and all occurring times with the
     * current system time.
     */
	//##ModelId=3C506C3902EC
    void Reset();

	/**
     * Get the object's index with in the region.
     *
     * RETURN int: the index of the object in the region.
     */
	//##ModelId=3C506C3902ED
    inline int GetIndex() const { return itsIndex; };

	/**
     * This method returns the number of failure supported by this layer.
	 *
	 *RETURN int: the number of failure handle by this object.
     */
	//##ModelId=3C506C3902F5
	inline int GetNbOfFailure() const { return itsNumberOfFailure; };

	/**
     * This method returns the number of Signal Protect defects supported by
     * this layer.
	 *
	 *RETURN int: the number of Signal Protect failure handle by this object.
     */
	inline int GetSigProtNbOfFailure() const { return itsSigProtNumberOfFailure; };

	/**
     * Get the zero based failure index from the signal alarm common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type
     * defined in the common type.
     *
     * RETURN int: the zero based failure index.
     */
	//##ModelId=3C506C3902F6
    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    /**
     * Get a signal alarm common type from a zero based failure index.
     *
     * PARAM int theIndex: the zero based failure index.
     *
     * RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined
     * in the common type.
     */
	//##ModelId=3C506C390301
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex(int theIndex) const;

	/**
     * Get the zero based failure index from the signal protect common type.
     *
     * PARAM CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType: the failure type
     * defined in the common type.
     *
     * RETURN int: the zero based failure index.
     */
    virtual int GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType sigProtFailureType) const;

    /**
     * Get a signal protect common type from a zero based failure index.
     *
     * PARAM int theIndex: the zero based failure index.
     *
     * RETURN CT_TelAlarmCondition::CT_FacilityAlarmType: the failure type defined
     * in the common type.
     */
    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetSigProtTypeFromIndex(int theIndex) const;

    /**
     * Get the Signal Protect mate port.
     *
     * PARAM none: 
     *
     * RETURN int: the port number currently contained in the region.
     */
    inline int GetSigProtMatePort() const;

    /**
     * Get the Signal Protect mate port type.
     *
     * PARAM none: 
     *
     * RETURN int: the mate port type currently contained in the region.
     */
    inline CT_DirectionFlag GetSigProtMatePortType() const;

    /**
     * Get the Signal Protect mate start channel.
     *
     * PARAM none: 
     *
     * RETURN int: the mate start channel currently contained in the region.
     */
    inline uint32 GetSigProtMateStartChannel() const;

    /**
     * Set the Signal Protect mate port.
     *
     * PARAM none: 
     *
     * RETURN int: the port number currently contained in the region.
     */
    inline void SetSigProtMatePort(int sigProtMatePort);

    /**
     * Set the Signal Protect mate port type.
     *
     * PARAM none: 
     *
     * RETURN int: the mate port type currently contained in the region.
     */
    inline void SetSigProtMatePortType( CT_DirectionFlag sigProtMatePortType);

    /**
     * Set the Signal Protect mate start channel.
     *
     * PARAM none: 
     *
     * RETURN int: the mate start channel currently contained in the region.
     */
    inline void SetSigProtMateStartChannel( uint32 sigProtMateStartChannel);

    /**
     * Clear the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int sigProtMatePort, CT_DirectionFlag sigProtMatePortType, uint32 sigProtMateStartChannel);
    void ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool IsYCablePROTNA );

    /**
     * Set the status bit for a specified Signal Protect alarm. This interface provides
     * a mechanism to update the Signal Protection defect status bit, located in the
     * Signal Alarm region.
     */
    void ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int sigProtMatePort, CT_DirectionFlag sigProtMatePortType, uint32 sigProtMateStartChannel);
    void ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool IsYCablePROTNA );

	/**
     * This method prints the alarm header.
     */
	//##ModelId=3C506C39030B
    virtual void PrintHeader() const;

	/**
     * Print failure statuses.
     */
	//##ModelId=3C506C390314
	virtual void PrintYourSelf() const;

    /**
     * Retrieve the signal type currently assigned to the port or line.
     *
     * RETURN : the signal type CT_TEL_SignalType.
     */
    virtual int GetSignalType() const;

	/**
     * Set the signal type currently associated with the port. This is just information
     * stored in the Signal Alarm region which allows it to determine which alarm type
     * needs to be reported.
	 * 
	 * PARAM CT_TEL_SignalType (int) the signal type.
     */
    virtual void SetSignalType(int signalType);


	/**
     * Operator =, set this instance with the instance pass in parameter.
     *
     * PARAM const ALM_FailureBase& theFailureBase: a reference to instance used
     * to set this instance.
     *
     * RETURN ALM_FailureBase&: a reference to this instance.
     */
	//##ModelId=3C506C390316
	ALM_FailureBase& operator=(const ALM_FailureBase& theFailureBase);

    /**
	 * Operator ==, return true if this instance is equal to the instance pass in parameter.
     *
     * PARAM const ALM_FailureBase& theFailureBase: a reference to instance used
     * to compare this instance.
     *
     * RETURN bool: true if the instance are equal, false otherwise.
     */
	//##ModelId=3C506C39031E
	bool operator==(const ALM_FailureBase& theFailureBase) const;

protected:

    /**
	 * Binary serialization used for BB transfer between cards. Writes the
     * internal data of the object to a stream. If the derived class contains
     * additional information from what is in this base class, override this method.
	 *
	 * PARAM FC_Stream& theStream: the FC stream to write to.
	 *
	 * RETURN FC_Stream&: a FC_Stream reference that enables multiple insertion
     * operators on a single line.
     */
	//##ModelId=3C506C390329
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

	/**
     * Reads the object data from the stream and sets the object with it. If the
     * derived class contains additional information from what is in this base
     * class, override this method.
	 *
	 * PARAM FC_Stream& theStream: the FC stream to read from.
	 *
	 * RETURN FC_Stream&: a FC_Stream reference that enables multiple extraction
     * operators on a single line.
     */
	//##ModelId=3C506C390332
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
        
	/**
     * Textual serialization used for BB edition. Writes the internal data of
     * the object to a stream. All derived classes will override this method
     * to write the specific regions objects.
	 *
	 * PARAM ostream& theStream: the output stream to write to.
	 *
	 * RETURN ostream&: an ostream reference that enables multiple insertion
     * operators on a single line.
     */
	//##ModelId=3C506C39033C
    virtual ostream& WriteObject(ostream& theStream);

	/**
     * Reads object data from the stream and set the object with it.All derived
     * classes will override this method to display the specific regions objects.
	 *
	 * PARAM istream& theStream: the stream to read from.
	 *
	 * RETURN istream&: an istream reference that enables multiple extraction
     * operators on a single line.
     */
	//##ModelId=3C506C390346
    virtual istream& ReadObject(istream& theStream);

	/**
     * Index of the object within the region.
     */
	//##ModelId=3C506C390350
    int itsIndex;

    /**
     * The signal type.
     */
    int itsSignalType;

	/**
     * Holds the status of all Signal Alarm failures managed by this layer.
     * This ARRAY pointer is indexed by the enumeration ALM_FAILURE_TYPE
     * defined  for every layer. The memory is allocated in the constructor.
     */
	//##ModelId=3C506C390359
    bool* itsStatus;

    /**
     * Holds the array of occurring time of all Signal Alarm failures managed
     * by this layer. This ARRAY pointer is indexed by the enumeration
     * ALM_FAILURE_TYPE defined for every layer. The memory is allocated in
     * the constructor.
     */
	//##ModelId=3C506C390363
    time_t* itsOccurTime;

	/**
     * The number of Signal Alarm failures defined for this layer.
     */
	//##ModelId=3C506C390364
    int itsNumberOfFailure;

	/**
     * Holds the status of the Signal Protect failures managed by Signal
     * alarm for this layer. The memory is allocated in the constructor.
     */
    bool* itsSigProtStatus;
    bool* itsSigProtYCable;

	/**
     * The number of Signal Protection failures defined for this layer.
     */
    int itsSigProtNumberOfFailure;

    /**
     * Used for Signal Protection, holds the mate port number.
     */
    int itsSigProtMatePort;

    /**
     * Used for Signal Protection, holds the mate port type
     */
	CT_DirectionFlag itsSigProtMatePortType;

    /**
     * Used for Signal Protection, holds the mate start channel (ie: the
     * HOP number in the HOP layer).
     */
	uint32 	itsSigProtMateStartChannel;

private:

};

//##ModelId=3C506C390292
inline bool ALM_FailureBase::GetStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    return itsStatus[GetIndexFromType(theFailureType)];
}

//##ModelId=3C506C39029C
inline void ALM_FailureBase::SetStatus(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theStatus)
{
    itsStatus[GetIndexFromType(theFailureType)] = theStatus;
}

inline bool ALM_FailureBase::GetSigProtStatus (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    return itsSigProtStatus[GetSigProtIndexFromType(theFailureType)];
}

inline bool ALM_FailureBase::GetSigProtYCable (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    return itsSigProtYCable[GetSigProtIndexFromType(theFailureType)];
}

inline void ALM_FailureBase::SetSigProtStatus(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theSigProtStatus)
{
    itsSigProtStatus[GetSigProtIndexFromType(theFailureType)] = theSigProtStatus;
}

inline void ALM_FailureBase::SetSigProtYCable(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool theSigProtYCable)
{
    itsSigProtYCable[GetSigProtIndexFromType(theFailureType)] = theSigProtYCable;
}

//##ModelId=3C506C3902A6
inline time_t ALM_FailureBase::GetOccurTime(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    return itsOccurTime[GetIndexFromType(theFailureType)];
}

//##ModelId=3C506C3902B0
inline void ALM_FailureBase::SetOccurTime (CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, time_t theOccurTime)
{
    itsOccurTime[GetIndexFromType(theFailureType)] = theOccurTime;
}

//##ModelId=3C506C3902BA
inline bool ALM_FailureBase::GetStatusFromIndex (uint32 theFailureIndex) const
{
    return itsStatus[theFailureIndex];
}

//##ModelId=3C506C3902C3
inline void ALM_FailureBase::SetStatusFromIndex (uint32 theFailureIndex, bool theStatus)
{
    itsStatus[theFailureIndex] = theStatus;
}

inline bool ALM_FailureBase::GetSigProtStatusFromIndex (uint32 theFailureIndex) const
{
    return itsSigProtStatus[theFailureIndex];
}

inline bool ALM_FailureBase::GetSigProtYCableFromIndex (uint32 theFailureIndex) const
{
    return itsSigProtYCable[theFailureIndex];
}
 
inline void ALM_FailureBase::SetSigProtYCableFromIndex (uint32 theFailureIndex, bool theSigProtYCable)
{
    itsSigProtYCable[theFailureIndex] = theSigProtYCable;
}

//##ModelId=3C506C3902CE
inline time_t ALM_FailureBase::GetOccurTimeFromIndex (uint32 theFailureIndex) const
{
    return itsOccurTime[theFailureIndex];
}

//##ModelId=3C506C3902D8
inline void ALM_FailureBase::SetOccurTimeFromIndex (uint32 theFailureIndex, time_t theOccurTime)
{
    itsOccurTime[theFailureIndex] = theOccurTime;
}

inline int ALM_FailureBase::GetSigProtMatePort() const
{
    return itsSigProtMatePort;
}

inline CT_DirectionFlag ALM_FailureBase::GetSigProtMatePortType() const
{
    return itsSigProtMatePortType;
}

inline uint32 ALM_FailureBase::GetSigProtMateStartChannel() const
{
    return itsSigProtMateStartChannel;
}

inline void ALM_FailureBase::SetSigProtMatePort( int sigProtMatePort )
{
    itsSigProtMatePort = sigProtMatePort;
}

inline void ALM_FailureBase::SetSigProtMatePortType( CT_DirectionFlag sigProtMatePortType )
{
    itsSigProtMatePortType = sigProtMatePortType;
}

inline void ALM_FailureBase::SetSigProtMateStartChannel( uint32 sigProtMateStartChannel )
{
    itsSigProtMateStartChannel = sigProtMateStartChannel;
}

#endif //ALM_FAILUREBASE_H
