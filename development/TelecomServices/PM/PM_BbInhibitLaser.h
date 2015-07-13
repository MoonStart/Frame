/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring. 
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITLASER_H
#define PM_BBINHIBITLASER_H

#include <PM/PM_TypeLaser.h>
#include <PM/PM_BbInhibit.h>


//This class keeps the PM Laser Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3C1F6F58017A
class PM_BbInhibitLaser : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5803A1
    PM_BbInhibitLaser (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    //##ModelId=3C1F6F5803AC
    virtual ~PM_BbInhibitLaser();

    //Resets all PM values to zero.
    //##ModelId=3C1F6F5803B5
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255AF0130
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255AF0158
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CD50245
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CD5029F
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5803BF
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5803CA
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3C1F6F5803DD
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeLaser::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITLASER_H

