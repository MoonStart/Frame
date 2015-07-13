/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Update and keep the ODU DELAY.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSODUGAUGE_H
#define PM_BBSTATUSODUGAUGE_H

#include <Monitoring/MON_OduStatus.h>
#include <PM/PM_BbStatus.h>

using namespace std;

class PM_BbStatusOduGauge : public PM_BbStatus
{
public:

    //Class default constructor.
    PM_BbStatusOduGauge();

    //Class default destructor.
    virtual ~PM_BbStatusOduGauge();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns DELAY value for last second.
    inline int32 GetDelay() const;

    void Update(MON_OduStatus& theStatusMonitor);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //Memorizes Delay for this second.
    int32 myDelay;
};

//-----------------------------------------------------------------
inline int32 PM_BbStatusOduGauge::GetDelay() const
{
    return myDelay;
}

#endif //PM_BBSTATUSODUGAUGE_H

