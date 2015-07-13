/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITCOP_H
#define PM_BBINHIBITCOP_H

#include <PM/PM_TypeCop.h>
#include <PM/PM_BbInhibit.h>

//This class keeps the PM Optical Channel Control, which 
//correspond to inhibition of entity layer and resets of 
//parameters on parameter basis for near-end parameters.
//##ModelId=3C1F6F53010F
class PM_BbInhibitCop : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5302B3
    PM_BbInhibitCop (uint32 dummy1 = 0, uint32 dummy2 =0);

    //Class default destructor.
    //##ModelId=3C1F6F5302BD
    virtual ~PM_BbInhibitCop();

    //Resets all PM values to zero.
    //##ModelId=3C1F6F5302C7
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255B301C2
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255B301EA
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CDA008A
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CDA00DA
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5302C9
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5302DB
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3C1F6F5302E6
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeCop::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITCOP_H

