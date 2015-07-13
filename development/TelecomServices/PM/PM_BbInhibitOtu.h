/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002. Sebastien Cossette
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITOTU_H
#define PM_BBINHIBITOTU_H

#include <PM/PM_TypeOtu.h>
#include <PM/PM_BbInhibit.h>


//This class keeps the PM OTU Layer Control, which correspond 
//to inhibition of entity layer and resets of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3C1F6F5E00C4
class PM_BbInhibitOtu : public PM_BbInhibit
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5E02F6
    PM_BbInhibitOtu (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    //##ModelId=3C1F6F5E0300
    virtual ~PM_BbInhibitOtu();

    //Resets all PM values to zero.
    //##ModelId=3C1F6F5E030A
    virtual void Reset();

    //Returns accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255AB00C6
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets accumulation and TCA inhibition state on a parameter basis.
    //##ModelId=3C9255AB00EE
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Returns TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CCE030D
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets TCA inhibition state on a parameter basis.
    //##ModelId=3E6E4CCE0368
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5E0314
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5E0327
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    //##ModelId=3C1F6F5E0332
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeOtu::PM_PARAM_NUM-2]; // No High Order 64Bit!

};

//------------------------------------------------------
class PM_BbInhibitOtuGauge : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitOtuGauge (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitOtuGauge();

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
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeOtuGauge::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITOTU_H

