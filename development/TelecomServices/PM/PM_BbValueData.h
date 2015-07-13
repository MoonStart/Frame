/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     9 April, 1999 Dominic Levesque.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Data (RS, FICON,ESCON, GbE, GOPT).
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEDATA_H
#define PM_BBVALUEDATA_H

#include <PM/PM_TypeData.h>
#include "PM_BbCounterValue.h"
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the Data. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
//##ModelId=3C9255B800CF
class PM_BbValueData : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;
    friend class PM_BbValueOSC;
    friend class PM_BbValueSMTM;

    //Class default constructor.
    //##ModelId=3C9255B80332
    PM_BbValueData(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3C9255B8033D
    virtual ~PM_BbValueData();

protected:

    //Stores the values to the stream.
    //##ModelId=3C9255B803B4
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C9255B803BF
    virtual istream& ReadObject( istream& theStream );

    //Handle 64Bit values (e.g. ODU4 CV-ODU)
    virtual bool IsParam64BitValue( const CT_PM_Parameter theParameter );
    virtual CT_PM_64BitValue Get64BitValue( const CT_PM_Parameter theParameter );
    virtual void             Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue );
};

#endif //PM_BBVALUEDATA_H
