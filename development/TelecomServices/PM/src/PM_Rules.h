/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Agent 
 AUTHOR   :     20 July, 2000 Marc Vendette
 DESCRIPTION:   Rule base class. Specify how to update period.
--------------------------------------------------------------------------*/

#ifndef PM_RULES_H
#define PM_RULES_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>

// Forward declaration of classes
class PM_GenericApplication;
class PM_AccumulationPeriod;

//This base class is responsible of the accumulation rules of 
//derived class layer. These accumulation rules are deduced 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to update parameters for the derived class 
//layer.
//##ModelId=3C1F6F5F03A1
class PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3C50162A03AD
    PM_Rules(PM_GenericApplication& theGenericApplication,
             uint16                 theIndex, 
             uint32                 theNumberOfParam);

    //Class default destructor.
    //##ModelId=3C1F6F6001F5
    virtual ~PM_Rules();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA161020079
    virtual void Init();

    //Updates the accumulation rules for a given layer. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3C1F6F6001FE
    virtual void UpdateRules(bool* theFilteringStateFirstStage = NULL, 
                             bool* theFilteringStateSecondStage = NULL);

    //Adds an Accumulation Period object pointer to the 
    //vector. Later, at the execution of PM, an update period 
    //function call will be done on all objects in the vector.
    //##ModelId=3C1F6F600200
    void AddAccumulationPeriod(PM_AccumulationPeriod* theAccPeriod);

    //Returns the parameter value for the specified parameter.
    //##ModelId=3C50162B000B
    virtual CT_PM_64BitValue GetValueParam(uint32 theIndex);

protected:

    //Index of the BB objects that are in relation with this 
    //Rules class. This index correspond to the port number.
    //##ModelId=3C1F6F600231
    uint16 myIndex;

   //Reference to the generic PM application.
    //##ModelId=3C1F6F600213
    PM_GenericApplication& myGenericApplication;

    //Vector of accumulation period that are influenced by 
    //these accumulation rules.
    //##ModelId=3C1F6F6102DC
    vector<PM_AccumulationPeriod*> myVectorOfAccumulationPeriod;

    //Array of current value for each supported parameters.
    //##ModelId=3C50162B003E
    CT_PM_64BitValue* myCurrentValueParam;

    //The number of parameters supported by this layer.
    //##ModelId=3C50162B005B
    uint32 myNumberOfParam;

    // My validity flag of all parameters.
	//##ModelId=3FA1610200B7
    bool* myValidityState;

};

#endif //PM_RULES_H


