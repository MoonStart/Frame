/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, March 07, 2002.
 DESCRIPTION:   PM end of period service.
--------------------------------------------------------------------------*/

#ifndef PM_BBENDOFPERIOD_H
#define PM_BBENDOFPERIOD_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <TimeService/FC_Time.h>

#include <PM/PM_Def.h>


//Performance monitoring end of period object class. Contains 
//data related to end of period.
//##ModelId=3C9255A6028C
class PM_BbEndOfPeriod: public TEL_BbObjectBase
{
public:
    //Constructor.
    //##ModelId=3C9255A700EA
    PM_BbEndOfPeriod();

    //Virtual destructor.
    //##ModelId=3C9255A700F3
    virtual ~PM_BbEndOfPeriod();

    //Sets the current 15m or 1 day period.
    //##ModelId=3C9255A700F5
    inline void SetPeriod(CT_PM_Period thePeriod, FC_Time theNumPeriod);

    //Gets the current 15 m or 1 day period.
    //##ModelId=3C9255A70108
    inline FC_Time GetPeriod(CT_PM_Period thePeriod);

    //Comparaison operator.
    //##ModelId=3C9255A70125
    bool operator==(const PM_BbEndOfPeriod& theAlarmObject);

    //Assignation operator.
    //##ModelId=3C9255A7012F
    PM_BbEndOfPeriod& operator =(const PM_BbEndOfPeriod& theAlarmObject);

private:

    //Stores the values to the binary stream.
    //##ModelId=3C9255A70139
    FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C9255A70144
    FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3C9255A70157
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C9255A70162
    virtual istream& ReadObject( istream& theStream );

    //The period array containing the period of 15 m and 1 day.
    //##ModelId=3E6FC01B0033
    FC_Time       myPeriod[CT_PM_PERIOD_UNKNOWN];

};

//##ModelId=3C9255A700F5
inline void PM_BbEndOfPeriod::SetPeriod(CT_PM_Period thePeriod, FC_Time theNumPeriod)
{
    myPeriod[thePeriod] = theNumPeriod;

}

//##ModelId=3C9255A70108
inline FC_Time PM_BbEndOfPeriod::GetPeriod(CT_PM_Period thePeriod)
{
    return myPeriod[thePeriod];

}

#endif //PM_BBENDOFPERIOD_H
