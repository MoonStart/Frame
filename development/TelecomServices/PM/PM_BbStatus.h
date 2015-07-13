/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, January 07, 2002.
 DESCRIPTION:   Update and keep the PM status.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUS_H
#define PM_BBSTATUS_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_PM_Definition.h>


using namespace std;

class MON_Object;

//This class keeps and updates the counters.
//##ModelId=3C50163402AD
class PM_BbStatus: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    //##ModelId=3C50163500F6
    PM_BbStatus (uint32 theNumberOfParam);

    //Class default destructor.
    //##ModelId=3C5016350100
    virtual ~PM_BbStatus();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F150390
    virtual void Init(restart_type theRestart);

    //Updates PM defects/gauges.
    //##ModelId=3C5016350114
    virtual void Update(MON_Object& theMonitor);

    // Validity of status region associated with parameter.
	//##ModelId=3FA161140283
    bool StatusIsValid(CT_PM_Parameter theParameter) {return myValidity[theParameter];}

protected:

    //Statuses of all supported parameters.
    //##ModelId=3C501635013D
    CT_PM_Value* myParam;

    //The number of parameters supported by this object.
    //##ModelId=3C5016350151
    uint32 myNumberOfParam;

    // My validity flag of all parameters.
	//##ModelId=3FA161140293
    bool* myValidity;

};

#endif //PM_BBSTATUS_H
