/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004  Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of GFP layer
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTGFP_H
#define PM_BBCOUNTGFP_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


/* Forward declaration of classes */
class MON_GfpCounters;

using namespace std;

//Keeps various GFP counters up to date for the current second.
class PM_BbCountGfp: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbCountGfp();

    //Class default destructor.
    virtual ~PM_BbCountGfp();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of 10B_ERR errors from the GFP
    inline uint32 Get10BErr() const;

    //Updates the PM counters for the Multiplex Section.
    void Update(MON_GfpCounters& theGfpCounter);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that memorizes the number of 10B_ERR for this second.
    PM_Counter my10BErrCounter;

};

//-----------------------------------------------------------------
inline uint32 PM_BbCountGfp::Get10BErr() const
{
    return my10BErrCounter.GetCount();
}

#endif //PM_BBCOUNTGFP_H
