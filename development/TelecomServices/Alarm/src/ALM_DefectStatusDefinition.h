/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards 
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   General definition for Signal Alarm
--------------------------------------------------------------------------*/

#ifndef ALM_DEFECTSTATUSDEFINITION_H
#define ALM_DEFECTSTATUSDEFINITION_H

#include <gdef.h>

//Transition counter, a free running counter that counts the rising transition of a defect.
//##ModelId=3C506C340262
typedef uint32 ALM_TCount;

//Defect status structure definition. This structure holds the parameters of a defect: "status" and "tCount".
//##ModelId=3C506C3402EE
class ALM_DefectStatus
{
public:

    //Class default constructor.
	//##ModelId=3C603CA10312
    ALM_DefectStatus()
    {
        Reset();
    };

    //ALM_DefectStatus::~ALM_DefectStatus(){};

    //Reset my status and my transition count.
	//##ModelId=3DBFFAE800C1
    inline void Reset() {myStatus = false; myTCount = 0; myIsYCablePROTNA = false;}

    //Set the transition counter with the value in parameter.
    //
    //PARAM ALM_TCount theTCount: the transition counter to set.
	//##ModelId=3DBFFAE800D5
    inline void SetTCount(ALM_TCount theTCount) {myTCount = theTCount;};

    //Set the status with the value in parameter.
    //
    //PARAM bool theStatus: the status to set.
	//##ModelId=3DBFFAE800E9
    inline void SetStatus(bool theStatus) {myStatus = theStatus;};

    //Get the transition count.
    //
    //RETURN ALM_TCount: the alarm transition counter.
	//##ModelId=3DBFFAE80107
    inline ALM_TCount GetTCount() const {return myTCount;};

    //Get the status.
    //
    //RETURN bool: the status.
	//##ModelId=3DBFFAE80111
    inline bool GetStatus() const {return myStatus;};

    bool GetYCablePROTNA(){ return myIsYCablePROTNA; }
    void SetYCablePROTNA(bool theValue){ myIsYCablePROTNA = theValue; }

private:

    //The status of a failure, either true or false.
	//##ModelId=3C506C340384
    bool myStatus;

    //The transition count, a free running counter that count the rising transition of a defect.
	//##ModelId=3C63F2770185
    ALM_TCount myTCount;

    //Special field to indicate if PROTNA is occuring in Y-Cable Protection config
    bool myIsYCablePROTNA;
};

//Definition of Defect Status pointer.
//##ModelId=3C506C3403A2
typedef ALM_DefectStatus* ALM_DefectStatusPtr;

//Definition of filter type.
//##ModelId=3C506C35005B
enum ALM_FilterType
{
	//Standby mode, filtering action is not started.
	//##ModelId=3C506C3500FB
    ALM_FILTER_STANDBY,

	//Apply when no filtering is needed.
	//##ModelId=3C506C350105
    ALM_FILTER_LOCAL,

	//Apply when all failures must be filtered du to a failure from the higher layer.
	//##ModelId=3C506C35010F
    ALM_FILTER_ALL
};

#endif //ALM_DEFECTSTATUSDEFINITION_H
