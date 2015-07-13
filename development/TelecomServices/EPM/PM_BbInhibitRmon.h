/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and SMTM.
 AUTHOR   :     December 2005, Teresa Chen
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITRMON_H
#define PM_BBINHIBITRMON_H

#include <EPM/PM_TypeRmon.h>
#include <PM/PM_BbInhibit.h>

using namespace std;

//This class keeps the PM RMON Layer Control.
class PM_BbInhibitRmonCounter : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitRmonCounter (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitRmonCounter();

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
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeRmonCounter::PM_PARAM_NUM-9]; // No HIGH ORDER 64Bits!

};


//------------------------------------------------------
class PM_BbInhibitRmonGauge : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitRmonGauge (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitRmonGauge();

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
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeRmonGauge::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITRMON_H
