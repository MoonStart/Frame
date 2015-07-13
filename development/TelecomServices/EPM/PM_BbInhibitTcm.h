/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   PM Parameter values class. Keep and set PM parameter values.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBITTCM_H
#define PM_BBINHIBITTCM_H

#include <PM/PM_BbInhibit.h>
#include <EPM/PM_TypeTcm.h>


class PM_BbInhibitTcm : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitTcm( uint32 dummy1 = 0, uint32 dummy2 = 0 );

    //Class default destructor.
    virtual ~PM_BbInhibitTcm();

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

    PM_ResetCounter GetPrivateResetCountCurrent(PM_TypeTcm::PM_Param theType) { return myPrivateResetCountCurrent[ theType ]; }
    void SetPrivateResetCountCurrent(PM_TypeTcm::PM_Param theType, PM_ResetCounter theResetCounter) 
         { myPrivateResetCountCurrent[ theType ] = theResetCounter; }

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Array of reset counters, one for each parameter 
    //supported by this layer. These counter are local to 
    //this object and they are used for comparaison with the 
    //one receive from the admin via the control region.
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeTcm::PM_PARAM_NUM-1]; // No High Order 64Bit!
};

//------------------------------------------------------
class PM_BbInhibitTcmGauge : public PM_BbInhibit
{

public:

    //Class default constructor.
    PM_BbInhibitTcmGauge (uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Class default destructor.
    virtual ~PM_BbInhibitTcmGauge();

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
    PM_ResetCounter myPrivateResetCountCurrent[PM_TypeTcmGauge::PM_PARAM_NUM];

};

#endif //PM_BBINHIBITTCM_H

