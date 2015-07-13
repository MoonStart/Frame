/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004  Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of Far-End SONET/SDH MS layer
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTMSFAREND_H
#define PM_BBCOUNTMSFAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


/* Forward declaration of classes */
class MON_MsCounters;

using namespace std;

//Keeps various Far-End SONET/SDH MS counters up to date for the current second.
class PM_BbCountMsFarEnd: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbCountMsFarEnd();

    //Class default destructor.
    virtual ~PM_BbCountMsFarEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of REI errors from the 
    //Multiplex Section (current hardware counter minus 
    //last hardware counter).
    inline uint32 GetREI() const;

    //Updates the PM counters for the Multiplex Section.
    void Update(MON_MsCounters& theMsCounter);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that memorizes the number of REI errors for this second.
    PM_Counter myREICounter;
};

inline uint32 PM_BbCountMsFarEnd::GetREI() const
{
    return myREICounter.GetCount();
}

#endif //PM_BBCOUNTMSFAREND_H
