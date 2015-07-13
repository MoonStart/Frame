/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITGFP_H
#define PM_BBINHIBITGFP_H

#include <PM/PM_BbInhibit.h>
#include <PM/PM_TypeGfp.h>


class PM_BbInhibitGfp : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitGfp (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitGfp();

    //Resets all PM values to zero.
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeGfp::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITGFP_H

