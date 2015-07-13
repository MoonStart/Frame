/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITEON_H
#define PM_BBINHIBITEON_H

#include <PM/PM_BbInhibit.h>
#include <PM/PM_TypeEon.h>


//This class keeps the PM EON Layer Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3FA1610B0007
class PM_BbInhibitEon : public PM_BbInhibit
{

public:

    //Class default constructor.
	//##ModelId=3FA1610B016F
    PM_BbInhibitEon (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
	//##ModelId=3FA1610B017E
    virtual ~PM_BbInhibitEon();

    //Resets all PM values to zero.
	//##ModelId=3FA1610B0180
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
	//##ModelId=3FA1610B0182
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
	//##ModelId=3FA1610B0185
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
	//##ModelId=3FA1610B0190
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
	//##ModelId=3FA1610B0193
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
	//##ModelId=3FA1610B019D
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
	//##ModelId=3FA1610B01A0
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
	//##ModelId=3FA164BE037B
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeEon::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITEON_H

