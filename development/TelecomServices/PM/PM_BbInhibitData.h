/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 13, 2001.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITDATA_H
#define PM_BBINHIBITDATA_H

#include <PM/PM_BbInhibit.h>
#include <PM/PM_TypeData.h>


//This class keeps the PM Data Layer Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3C9255BA01FE
class PM_BbInhibitData : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3C9255BB0070
    PM_BbInhibitData (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    //##ModelId=3C9255BB007B
    virtual ~PM_BbInhibitData();

    //Resets all PM values to zero.
    //##ModelId=3C9255BB0084
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255BB008E
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255BB0098
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CE002EB
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CE00363
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3C9255BB00AB
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C9255BB00B6
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3C9260910123
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeData::PM_PARAM_NUM-1]; // No High Order 64Bit!

};

#endif //PM_BBINHIBITDATA_H

