/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     February 8, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Update and keep the error count of Data (RS,
                FICON, ESCON, GbE, GOPT).
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTDATA_H
#define PM_BBCOUNTDATA_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


/* Forward declaration of classes */
class MON_RsCounters;

using namespace std;

//Keeps various Data counters up to date for the current second.
//##ModelId=3C9255C6021A
class PM_BbCountData: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    //##ModelId=3C9255C7009F
    PM_BbCountData();

    //Class default destructor.
    //##ModelId=3C9255C700A0
    virtual ~PM_BbCountData();

    //Initializes BB object according to the restart type.
    //##ModelId=3C9255C700AA
    virtual void Init(restart_type theRestart);

    //Returns the current count of BIP errors from the 
    //Regenerator Section (current hardware counter minus 
    //last hardware counter).
    inline CT_PM_64bit_ull GetBIP() const;

    void Update(MON_RsCounters& theCounter);

protected:

    //Stores the counter to the stream.
    //##ModelId=3C9255C700D2
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    //##ModelId=3C9255C700DD
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that memorizes the number of BIP errors for this second.
    PM_Counter myBIPCounter;
};

//-----------------------------------------------------------------
//##ModelId=3C9255C700BD
inline CT_PM_64bit_ull PM_BbCountData::GetBIP() const
{
    return myBIPCounter.GetCount();

}

#endif //PM_BBCOUNTDATA_H
