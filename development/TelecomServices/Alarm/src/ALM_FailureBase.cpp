/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class maintains all failures of a layer
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_FailureBase.h"

//--------------------------------------------------------------------------
//##ModelId=3C506C39027E
ALM_FailureBase::ALM_FailureBase (int theIndex,
                                  int theNumberOfFailure,
                                  bool theDefaultStatus,
                                  int theSigProtNumberOfFailure,
                                  int itsSigProtMatePort,
                                  CT_DirectionFlag itsSigProtMatePortType,
                                  uint32 itsSigProtMateStartChannel):
    itsIndex (theIndex),
    itsNumberOfFailure (theNumberOfFailure),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN),
    itsSigProtNumberOfFailure (theSigProtNumberOfFailure),
    itsSigProtMatePort (0),
    itsSigProtMatePortType(CT_DIR_DONT_CARE),
    itsSigProtMateStartChannel(0)
{
    // Get memory to put every failure status of a layer
    itsStatus = new bool[itsNumberOfFailure];

    // Get memory to put every failure occurring time of a layer
    itsOccurTime = new time_t[itsNumberOfFailure];

    // Init every status with the default value
    int aFailureIndex;
    for (aFailureIndex = 0; aFailureIndex < itsNumberOfFailure; aFailureIndex++)
    {
        itsStatus[aFailureIndex] = theDefaultStatus;
        itsOccurTime[aFailureIndex] = CSPII_CardIF::GetInstance()->GetUTCTime();
    }

    // If Signal Protect is using this layer to store defect statuses,
    // allocate the memory and set to the default value, else default
    // the pointer to NULL.
    if (itsSigProtNumberOfFailure != 0)
    {
        itsSigProtStatus = new bool[itsSigProtNumberOfFailure];
        itsSigProtYCable = new bool[itsSigProtNumberOfFailure];
        for (aFailureIndex = 0; aFailureIndex < itsSigProtNumberOfFailure; aFailureIndex++)
        {
            itsSigProtStatus[aFailureIndex] = false;
            itsSigProtYCable[aFailureIndex] = false;
        }
    }
    else 
    {
        itsSigProtStatus = NULL;
        itsSigProtYCable = NULL;
    }
}

//--------------------------------------------------------------------------
//##ModelId=3C506C39028A
ALM_FailureBase::~ALM_FailureBase()
{
    // release memory allocated by the constructor
    delete [] itsStatus;
    delete [] itsOccurTime;
    if (itsSigProtNumberOfFailure != 0)
    {
        delete [] itsSigProtStatus;
        delete [] itsSigProtYCable;
    }
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3902EC
void ALM_FailureBase::Reset()
{
    // Init every status with the default value
    int aFailureIndex;
    for (aFailureIndex = 0; aFailureIndex < itsNumberOfFailure; aFailureIndex++)
    {
        itsStatus[aFailureIndex] = false;
        itsOccurTime[aFailureIndex] = CSPII_CardIF::GetInstance()->GetUTCTime();
    }
    itsSignalType = (int)CT_TEL_SIGNAL_UNKNOWN;

    for (aFailureIndex = 0; aFailureIndex < itsSigProtNumberOfFailure; aFailureIndex++)
    {
        itsSigProtStatus[aFailureIndex] = false;
        itsSigProtYCable[aFailureIndex] = false;
    }
}

//--------------------------------------------------------------------------
char* ALM_GetTimeOnly(char* theTime)
{
    theTime[19] = '\0';
    return theTime + 11;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C390314
void ALM_FailureBase::PrintYourSelf() const
{
	// Failure info.
	bool aStatus;
	time_t anOccurTime;
	tm  aTmData;
	tm* aTmPtr = &aTmData;
	char aTimeBuf[CSPII_TIME_BUFF_LENGTH];

	// Print the port
    fc_cout.Width(3);
    fc_cout << itsIndex << " ";

	// for each failure
    int aFailureIndex = GetNbOfFailure();
	while(aFailureIndex)
	{
        aFailureIndex--;
		// Read failure status occurring time
        aStatus = GetStatusFromIndex(aFailureIndex);
		anOccurTime = GetOccurTimeFromIndex(aFailureIndex);
		// Print failure
        fc_cout << (aStatus ? "T" : ".") << " "
		     << ALM_GetTimeOnly( CSPII_CardIF::GetInstance()->GetAsctime(CSPII_CardIF::GetInstance()->GetGmtime(&anOccurTime, aTmPtr), aTimeBuf ) ) << " ";
	}

	fc_cout << endl;
}

// SERIALIZATION

// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C39033C
ostream& ALM_FailureBase::WriteObject (ostream& theStream)
{
    // Throw an error: Textual serialization must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "ALM: Textual serialization not implemented" );
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C390346
istream& ALM_FailureBase::ReadObject  (istream& theStream)
{
    // Throw an error: Textual serialization must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "ALM: Textual serialization not implemented" );
    return theStream;
}


// Binary mode
//--------------------------------------------------------------------------
//##ModelId=3C506C390329
FC_Stream& ALM_FailureBase::WriteObjectBinary (FC_Stream& theStream)
{
	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	//*itsOccurTime = *itsDbOccurTime; 

    return theStream;
}


//--------------------------------------------------------------------------
//##ModelId=3C506C390332
FC_Stream& ALM_FailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3902E2
void ALM_FailureBase::GetCondition(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, CT_TelAlarmCondition* theCondition) const
{
    theCondition->SetStatus( itsStatus[GetIndexFromType(theFailureType)] );
    theCondition->SetTimeStamp( itsOccurTime[GetIndexFromType(theFailureType)] );
    theCondition->SetAlarmType( theFailureType );
}

//--------------------------------------------------------------------------
//##ModelId=3C506C390316
ALM_FailureBase& ALM_FailureBase::operator=(const ALM_FailureBase& theFailureBase)
{
    int aFailureIndex;

    // Get the index and the number of failure.
	itsIndex = theFailureBase.itsIndex;
	itsSignalType = theFailureBase.itsSignalType;
	itsNumberOfFailure = theFailureBase.itsNumberOfFailure;
	itsSigProtNumberOfFailure = theFailureBase.itsSigProtNumberOfFailure;
    itsSigProtMatePort = theFailureBase.itsSigProtMatePort;
    itsSigProtMatePortType = theFailureBase.itsSigProtMatePortType;
    itsSigProtMateStartChannel = theFailureBase.itsSigProtMateStartChannel;

	// For each Signal Alarm failure, copy its status.
	for(aFailureIndex = 0; aFailureIndex < theFailureBase.itsNumberOfFailure; aFailureIndex++)
	{
		// set the status and the occurtime.
		itsStatus[aFailureIndex] = theFailureBase.itsStatus[aFailureIndex];
		itsOccurTime[aFailureIndex] = theFailureBase.itsOccurTime[aFailureIndex];
	}

	// For each Signal Protect defect, copy its status.
	for(aFailureIndex = 0; aFailureIndex < theFailureBase.itsSigProtNumberOfFailure; aFailureIndex++)
	{
		itsSigProtStatus[aFailureIndex] = theFailureBase.itsSigProtStatus[aFailureIndex];
		itsSigProtYCable[aFailureIndex] = theFailureBase.itsSigProtYCable[aFailureIndex];
	}

	return (*this);
}

//--------------------------------------------------------------------------
//##ModelId=3C506C39031E
bool ALM_FailureBase::operator==(const ALM_FailureBase& theFailureBase) const
{
    int aFailureIndex;

    // if the number of failure is different
	if(itsNumberOfFailure != theFailureBase.itsNumberOfFailure)
	{
		// you can't compare the classes.
		FC_THROW_ERROR(FC_ValueOutOfRangeError, "operator== with wrong types");
	}
	// if the index is different
	if(itsIndex != theFailureBase.itsIndex)
	{
		// you can't compare the classes
		FC_THROW_ERROR(FC_ValueOutOfRangeError, "operator== with wrong index");
	}

	// for each failure
	for(aFailureIndex = 0; aFailureIndex < itsNumberOfFailure; aFailureIndex++)
	{
		// if the statuses are different
		if(itsStatus[aFailureIndex] != theFailureBase.itsStatus[aFailureIndex])
		{
			// the classes are not equal.
			return false;
		}
		// else statuses are the same
		// if Occur times are different
		else if(itsOccurTime[aFailureIndex] != theFailureBase.itsOccurTime[aFailureIndex])
		{
			// the classes are not equal
			return false;
		}
	}

	// all failures have the same status so they are equal.
	return true;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3902F6
int ALM_FailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetIndexFromType not Supported in base class" );
    return 0;
};

//--------------------------------------------------------------------------
//##ModelId=3C506C390301
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_FailureBase::GetTypeFromIndex(int theIndex) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetTypeFromIndex not Supported in base class" );
    return CT_TelAlarmCondition::ALM_NB_OF_ALARM;
};

//--------------------------------------------------------------------------
int ALM_FailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetIndexFromType not Supported in base class" );
    return 0;
};

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_FailureBase::GetSigProtTypeFromIndex(int theIndex) const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "GetTypeFromIndex not Supported in base class" );
    return CT_TelAlarmCondition::ALM_NB_OF_ALARM;
};

//--------------------------------------------------------------------------
//##ModelId=3C506C39030B
void ALM_FailureBase::PrintHeader() const
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "PrintHeader not Supported" );
};


int ALM_FailureBase::GetSignalType() const
{
    // Throw an error: This method must be implemented into derived class
    // FC_THROW_ERROR( FC_NotSupportedError, "GetSignalType not Supported" );
    return (int)CT_TEL_SIGNAL_UNKNOWN;
};

void ALM_FailureBase::SetSignalType( int signalType )
{
    // Throw an error: This method must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "SetSignalType not Supported" );
};

void ALM_FailureBase::ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int sigProtMatePort, CT_DirectionFlag sigProtMatePortType, uint32 sigProtMateStartChannel)
{
    int aFailureIndex;
    
    // Convert the alarm into an index to be used in the status array
    aFailureIndex = GetSigProtIndexFromType( theFailureType );

    // Set the defect status to false.
    itsSigProtStatus[aFailureIndex] = false;

    // Now set the mate port information.
    itsSigProtMatePort = sigProtMatePort;
    itsSigProtMatePortType = sigProtMatePortType;
    itsSigProtMateStartChannel = sigProtMateStartChannel;

    return;
};

void ALM_FailureBase::ClearSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool IsYCablePROTNA )
{
    int aFailureIndex;
    
    // Convert the alarm into an index to be used in the status array
    aFailureIndex = GetSigProtIndexFromType( theFailureType );

    // Set the defect status to false.
    itsSigProtStatus[aFailureIndex] = false;
    itsSigProtYCable[aFailureIndex] = IsYCablePROTNA;

    return;
};

void ALM_FailureBase::ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, int sigProtMatePort, CT_DirectionFlag sigProtMatePortType, uint32 sigProtMateStartChannel)
{
    int aFailureIndex;

    // Convert the alarm into an index to be used in the status array
    aFailureIndex = GetSigProtIndexFromType(theFailureType);

    // Set the defect status to false.
    itsSigProtStatus[aFailureIndex] = true;

    // Now set the mate port information.
    itsSigProtMatePort = sigProtMatePort;
    itsSigProtMatePortType = sigProtMatePortType;
    itsSigProtMateStartChannel = sigProtMateStartChannel;

    return;
};

void ALM_FailureBase::ReportSigProtDefect( CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType, bool IsYCablePROTNA )
{
    int aFailureIndex;

    // Convert the alarm into an index to be used in the status array
    aFailureIndex = GetSigProtIndexFromType(theFailureType);

    // Set the defect status to false.
    itsSigProtStatus[aFailureIndex] = true;
    itsSigProtYCable[aFailureIndex] = IsYCablePROTNA;

    return;
};
