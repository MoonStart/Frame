/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Update and keep the Tcm DELAY.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSTcmGAUGE_H
#define PM_BBSTATUSTcmGAUGE_H

#include <Monitoring/MON_TcmStatus.h>
#include <PM/PM_BbStatus.h>

using namespace std;

class PM_BbStatusTcmGauge : public PM_BbStatus
{
public:

    //Class default constructor.
    PM_BbStatusTcmGauge();

    //Class default destructor.
    virtual ~PM_BbStatusTcmGauge();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns DELAY value for last second.
    inline int32 GetDelay() const;

    void Update(MON_TcmStatus& theStatusMonitor);

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
inline int32 PM_BbStatusTcmGauge::GetDelay() const
{
    return myDelay;
}

#endif //PM_BBSTATUSTcmGAUGE_H

