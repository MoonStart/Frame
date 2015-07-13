/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITOMS_H
#define PM_BBINHIBITOMS_H

#include <PM/PM_TypeOms.h>
#include <PM/PM_BbInhibit.h>

//This class keeps the PM OMS Layer Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3E6E4C9D0078
class PM_BbInhibitOms : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3E6E4C9E026E
    PM_BbInhibitOms (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    //##ModelId=3E6E4C9E028D
    virtual ~PM_BbInhibitOms();

    //Resets all PM values to zero.
    //##ModelId=3E6E4C9E0296
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4C9E02AA
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4C9E02C8
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4C9E02F0
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4C9E0304
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3E6E4C9E0319
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4C9E0340
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3E6FC01D0234
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeOms::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITOMS_H

