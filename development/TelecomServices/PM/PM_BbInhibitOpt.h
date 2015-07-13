/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders.
 AUTHOR   :     December 13, 2001.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITOPT_H
#define PM_BBINHIBITOPT_H

#include <PM/PM_TypeOpt.h>
#include <PM/PM_BbInhibit.h>

//This class keeps the PM OPT Layer Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3C50162702FE
class PM_BbInhibitOpt : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3C50162800CF
    PM_BbInhibitOpt (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    //##ModelId=3C50162800DA
    virtual ~PM_BbInhibitOpt();

    //Resets all PM values to zero.
    //##ModelId=3C50162800E3
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255B60040
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255B6004C
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CCB0100
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CCB0150
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3C50162800E5
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C50162800F7
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3C5016280101
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeOpt::PM_PARAM_NUM];

};

class PM_BbInhibitOptCounter : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitOptCounter (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitOptCounter();

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
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeOptCounter::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITOPT_H

