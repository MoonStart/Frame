// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1REQUESTPARSER_38FDC64E02F8_INCLUDED
#define _INC_SP_1PLUS1REQUESTPARSER_38FDC64E02F8_INCLUDED

#include <CommonTypes/CT_SP_CommandType.h>
#include "SP_1plus1ProtectionAction.h"
#include "SP_RequestParser.h"
#include "SP_CallbackTimer.h"

class SP_1plus1K1K2Receiver;
class SP_1plus1ProtectionAction;
class MON_Region;


// BISNC
struct APS_BYTES{
    // first byte
    struct {
         uint8 request   :4,
               bitA      :1,
               bitB      :1,
               bitD      :1,
               bitR      :1;
    } requestAndProtType;

    // second byte
    uint8 requestedSignal;
    
    // third byte
    uint8 bridgedSignal;
    
    // fourth byte
    uint8 reservedByte;
};

//This class is responsible to receiving the switching 
//command, reading facility defects, and establishing a 
//request priority for each side.
//##ModelId=38FDC64E02F8
class SP_1plus1RequestParser 
: public SP_RequestParser
{
    friend class SP_RammTestMenu;
public:
	//This method is responsible to reading facility defects 
	//(line for linear mode, path for UPSR mode)  
	//establishing a request priority for each side according 
	//to defect priority and switch commands. It also 
	//implements a possible hold off period on defects if 
	//enabled (Drop&Continue UPSR). Finaly it also 
	//established which side is now the side to be selected 
	//as well as clearing any switching commands that could 
	//have been preempted.
	//##ModelId=3911CCD6005A
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Applies the received command to the protection group. 
	//Fails if the command cannot be performed.
	//##ModelId=3911CCD500F9
	virtual CT_SP_CommandResultCode SetSwitchingCommand(CT_SP_CommandType& theCommand);

	//Returns the command being applied to the request parser.
	//##ModelId=39043789009D
	inline const CT_SP_CommandType& GetCommand() const;

	//Returns the status of the protection facility defects.
	//##ModelId=3904378900E3
	inline const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& GetDefectStatus() const;

	//This method returns the highest priority request to be 
	//considered for switching as well as the side to switch 
	//to depending on the switching command and facilities 
	//status. The following examples show how values are 
	//returned:
	//Manual switch to protection:  Request=MS,  
	//Destination=Protection; Lock out of Protection: 
	//Request=LP, Destination=Working; Signal Degrade on 
	//Working: Request=SD, Destination=Protection; Clear: 
	//Request=CLEAR, Destination=N/A.
	//##ModelId=390437890133
	inline const CT_SP_ProtectionPair<CT_SP_Request>& GetHighestRequest() const;

	inline const CT_SP_ProtectionPair<bool>& GetHighestRequestIsRemote() const;

	inline const CT_SP_APS_REQUEST GetRemoteRequest() const;

	inline const CT_SP_Request GetEffectiveRequest() const;

    inline const bool IsEffectiveRequestFromRemote() const;

	//Returns true if the parser received a CLEAR command. 
	//This method with result in clear command to be flushed 
	//from parser.
	//##ModelId=39170C3F02E1
	bool GetClearCommand();

	//Constructor. Takes the protection action.
	//##ModelId=390583FB0158
	SP_1plus1RequestParser(SP_1plus1ProtectionAction& theProtectionAction);

	//Destructor.
	//##ModelId=390583FB019E
	virtual ~SP_1plus1RequestParser();

	//Returns the current best side.
	//##ModelId=39ACEFBA006C
	inline CT_SP_Protection GetBestSide() const;

	//Returns whether the current best side is usable
	inline bool IsBestSideUsable() const;

	//set the usability status of the selected source
	inline void BestSideUsable(bool usageState);

	//Resets difference attributes to default values and stop 
	//running timers.
	//##ModelId=39ACEFBA0058
    void Reset();

    //Setup values to proper intial values
    void InitWarm();

	//Set the hold off period (ms).
	//##ModelId=3B8BC9E10336
    void SetUpsrHoldOffTime(FC_Milliseconds theHoldOffTime);
	//Returns the hold off period (ms).
	//##ModelId=3B8BC9E1032C
    FC_Milliseconds GetUpsrHoldOffTime();
	//This method stops the hold off timers on both facility 
	//(if started).
	//##ModelId=3B8BC9E10323
    void StopTimers();

	//This method flushes any clear command.
	//##ModelId=3B8BC9E10322
    void ClearSwitchingCommand();

	//Returns true if request parser state has changes since 
	//last call.
	//##ModelId=3B8BC9E10318
    virtual bool HasChangedSinceLastCheck();

	//Sends the attributes to a stream.
	//##ModelId=3B8BC9E102FA
    virtual ostream& WriteObject( ostream& theStream );
	//Extracts the attributes from a stream.
	//##ModelId=3B8BC9E102DC
    virtual istream& ReadObject( istream& theStream );
	//Sends the attributes to a binary stream.
	//##ModelId=3B8BC9E102BE
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extracts the attributes from a binary stream.
	//##ModelId=3B8BC9E102A0
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    void ConvertApsRequestToSpRequest(APS_BYTES apsBytes, CT_SP_ProtectionPair<CT_SP_Request>& spRequest);

	//Returns the request with the highest priority between 
	//the given two.
	//##ModelId=39170C3F00CF
    CT_SP_Request GetHighestPriorityRequest(CT_SP_Request theARequest, CT_SP_Request theBRequest) const;

    void   SetTestingApsBytes(uint32 apsBytes);
    uint32 GetTestingApsBytes(void);
    void   SetTestingMode(uint32 testingMode);
    uint32 GetTestingMode(void);

    inline bool FopPmNeedToBeReported() { return myFopPmDetected; }
    inline void SetFopPmToggle(bool detected) { myFopPmDetected = detected; }

    CT_SP_ApsBidirType GetActualApsBidir() const;
    void SetActualApsBidir(CT_SP_ApsBidirType theActualApsBidir);

private:
	//##ModelId=3BC5A362019D
    CT_SP_ProtectionPair<Defect>* mySFDefects;
	CT_SP_ProtectionPair<Defect>* mySFLowDefects;
	//##ModelId=3BC5A36201E2
    CT_SP_ProtectionPair<Defect>* mySDDefects;

	//Reference to the protection action.
	//##ModelId=38FDF4160318
	SP_1plus1ProtectionAction& myProtectionAction;

	//The current command being applied to the protection 
	//group.
	//##ModelId=38FF6D17014B
	CT_SP_CommandType myCommand;

	//Switching command since last check.
	//##ModelId=3BBC9B310281
    CT_SP_CommandType myCommandHistory;

    //Current defect status of the protection facility.
	//##ModelId=390436E003D9
	CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect> myDefectStatus;

	//The highest request of that should be considered for 
	//each side.
	//##ModelId=390436F50271
	CT_SP_ProtectionPair<CT_SP_Request> myHighestRequest;

    // BISNC -- to record the source of the highest requests.
	CT_SP_ProtectionPair<bool> myHighestRequestIsRemote;
	CT_SP_APS_REQUEST myRemoteRequest;
	CT_SP_Request myEffectiveRequest;
	bool myEffectiveRequestIsRemote;

    //BISNC. describe actual Aps/Bidirectional Switch
    CT_SP_ApsBidirType myActualApsBidir;
	//Side with the high priority request.
	//##ModelId=39ACEFB9027E
    CT_SP_Protection myBestSide;

	//The hold off period (ms). Default value is 60ms.
	//##ModelId=3B8BC9E10229
    FC_Milliseconds myUpsrHoldOffTime;
	//Reference to the protection facility hold off timer.
	//##ModelId=3B8BC9E1021F
    SP_CallbackTimer myWorkingCallbackTimer;
	//Reference to the protection facility hold off timer.
	//##ModelId=3B8BC9E10213
    SP_CallbackTimer myProtectionCallbackTimer;
	//Pointers to the hold off timers (one for each facility).
	//##ModelId=3BBC9B310390
    CT_SP_ProtectionPair<SP_CallbackTimer*> myHoldOffTimer;

	//indicates whether the selected side is usable
    bool myBestSideUsable;

    uint32 myTestingApsBytes;
    uint32 myTestingMode;

    bool myFopPmDetected;

};





//##ModelId=39043789009D
inline const CT_SP_CommandType& SP_1plus1RequestParser::GetCommand() const
{
	return myCommand;
}

//##ModelId=3904378900E3
inline const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& SP_1plus1RequestParser::GetDefectStatus() const
{
	return myDefectStatus;
}

//##ModelId=390437890133
inline const CT_SP_ProtectionPair<CT_SP_Request>& SP_1plus1RequestParser::GetHighestRequest() const
{
	return myHighestRequest;
}

inline const CT_SP_ProtectionPair<bool>& SP_1plus1RequestParser::GetHighestRequestIsRemote() const
{
    return myHighestRequestIsRemote;
}

inline const CT_SP_APS_REQUEST SP_1plus1RequestParser::GetRemoteRequest() const
{
    return myRemoteRequest;
}

inline const CT_SP_Request SP_1plus1RequestParser::GetEffectiveRequest() const
{
    return myEffectiveRequest;
}

inline const bool SP_1plus1RequestParser::IsEffectiveRequestFromRemote() const
{
    return myEffectiveRequestIsRemote;
}

//##ModelId=39ACEFBA006C
inline CT_SP_Protection SP_1plus1RequestParser::GetBestSide() const
{
    return myBestSide;
}

inline bool SP_1plus1RequestParser::IsBestSideUsable() const
{
    return myBestSideUsable;
}

inline void SP_1plus1RequestParser::BestSideUsable(bool usageState)
{
    myBestSideUsable = usageState;
}

inline void SP_1plus1RequestParser::SetTestingApsBytes(uint32 apsBytes)
{
    myTestingApsBytes = apsBytes;
}

inline uint32 SP_1plus1RequestParser::GetTestingApsBytes(void)
{
    return myTestingApsBytes;
}

inline void SP_1plus1RequestParser::SetTestingMode(uint32 testingMode)
{
    myTestingMode = testingMode;
}

inline uint32 SP_1plus1RequestParser::GetTestingMode(void)
{
    return myTestingMode;
}





#endif /* _INC_SP_1PLUS1REQUESTPARSER_38FDC64E02F8_INCLUDED */

