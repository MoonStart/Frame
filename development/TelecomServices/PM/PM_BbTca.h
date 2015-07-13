/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     1 June, 1998 Jean-Francois Birtz.
 DESCRIPTION:   TCA State class. Keep and set the TCA PM states.
--------------------------------------------------------------------------*/

#ifndef PM_BBTCA_H
#define PM_BBTCA_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include "PM_BbObject.h"

using namespace std;


//Keeps and sets TCA for PM. This contains an array of bits 
//that keep states. The number of TCA in the array is passed 
//to the constructor.
//##ModelId=3C1F6F72005F
class PM_BbTca : public PM_BbObject
{

public:

    //Class constructor.
    //##ModelId=3C1F6F720290
    PM_BbTca (uint32 theNumberOfParam);

    //Class default destructor.
    //##ModelId=3C1F6F72029A
    virtual ~PM_BbTca();

    //Resets all TCAs to default value.
    //##ModelId=3C1F6F72029C
    virtual void Reset();

    //Gets the state of a PM parameter.
    //##ModelId=3C1F6F7202A5
    bool GetTcaState(CT_PM_Parameter theParameter) const;

    //Gets the state before filtering 
    //of a PM parameter.
    //##ModelId=3E6E4CA8006A
    bool GetTcaUnFilteredState(CT_PM_Parameter theParameter) const;

	// Returns true if any TCA has been declared.
	bool GetAnyTcaDeclared() const;

    //Gets the TCA counter of a PM parameter.
    //##ModelId=3E6E4CA800EC
    uint8 GetTcaCounter(CT_PM_Parameter theParameter) const;

    //Sets to True the state.
    //##ModelId=3C1F6F7202B9
    void SetBbTca(CT_PM_Parameter theParameter,
                  FC_Time         theOccurTime,
                  CT_PM_64BitValue theCrossedValue,
                  CT_EntityType theEntityType = CT_UNKNOWN_ENTITY_TYPE);

    //Sets to True the state before filtering.
    //##ModelId=3E6E4CA80150
    void SetTcaUnFiltered(CT_PM_Parameter theParameter);

    //Gets the last TCA occuring time.
    //##ModelId=3C1F6F7202D6
    FC_Time GetOccurTime(CT_PM_Parameter theParameter) const;

    //Sets the last TCA occuring time.
    //##ModelId=3C1F6F7202F4
    void SetOccurTime(CT_PM_Parameter theParameter, FC_Time theOccurTime);

    //Gets the last TCA crossed value.
	//##ModelId=3FA1610401FF
    CT_PM_64BitValue GetCrossedValue(CT_PM_Parameter theParameter, 
                                     CT_EntityType theEntityType = CT_UNKNOWN_ENTITY_TYPE,
                                     bool isGaugeValue = false) const;

    //Sets the last TCA crossed value.
	//##ModelId=3FA16104020E
    void SetCrossedValue(CT_PM_Parameter theParameter, CT_PM_64BitValue theCrossedValue, CT_EntityType theEntityType = CT_UNKNOWN_ENTITY_TYPE);

    //Sets to False the state.
    //##ModelId=3C1F6F7202FE
    void ResetTca(CT_PM_Parameter theParameter);

    //Sets to False the state of unfitered TCA.
    //##ModelId=3FA16104024C
    void ResetTcaUnFiltered(CT_PM_Parameter theParameter);

    //Resets to False all states.
    //##ModelId=3C1F6F720308
    void ResetAllTca();

	//Allocates memory for TCA crossing event data storage.
	void AllocateEventData();

    //Operator that returns true if TCA states of this object 
    //are equal to the TCA states of theOtherState object.
    //##ModelId=3C1F6F72031C
    bool operator==(const PM_BbTca& theOtherState) const;

    //Operator that copies the statuses.
    //##ModelId=3C1F6F720328
    PM_BbTca& operator=(const PM_BbTca& theOtherState);

    //Contains all the states of all parameters of this layer.
    //##ModelId=3C1F6F7203A9
    uint32 myStates;

    //Contains all the unfiltered states of all parameters of 
    //this layer.
    //##ModelId=3E6E4CA801FB
    uint32 myStatesUnFiltered;

    //Array that contains the time stamps when the
	//respecitve TCAs occured.
    //##ModelId=3C1F6F7203D0
    FC_Time* myOccurTime;

    //Array that contains the crossed values when the
	//respective TCAs occured.
	//##ModelId=3FA16104026D
    CT_PM_Value* myCrossedValue;

protected:

    //Stores the states to the stream.
    //##ModelId=3C1F6F720331
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the states from the stream.
    //##ModelId=3C1F6F72034E
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    //##ModelId=3C1F6F720359
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    //##ModelId=3C1F6F72036C
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //Contains all the TCA counters of all parameters of this layer.
    //##ModelId=3E6E4CA80273
    uint32 myCounters;

	//Contains the number of parameters in this PM layer instance.
	uint32 myNumberOfParam;

};


#endif //PM_BBTCA_H

