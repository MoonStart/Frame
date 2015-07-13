/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders FGTMM and FGTM.
 AUTHOR   :     June, 2009, Larry Wolfrum.
 DESCRIPTION:   Update and keep the FEC BER of OCH-P.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSOTUGAUGE_H
#define PM_BBSTATUSOTUGAUGE_H

#include <Monitoring/MON_OtuStatus.h>
#include <PM/PM_BbStatus.h>

using namespace std;

class PM_BbStatusOtuGauge : public PM_BbStatus
{
public:

    //Class default constructor.
    PM_BbStatusOtuGauge();

    //Class default destructor.
    virtual ~PM_BbStatusOtuGauge();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns BER value for last second.
    inline int32 GetBER() const;

    //Updates BER.
    void Update(MON_OtuStatus& theStatusMonitor);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //Memorizes BER for this second.
    int32 myBer;
};

//-----------------------------------------------------------------
inline int32 PM_BbStatusOtuGauge::GetBER() const
{
    return myBer;
}

#endif //PM_BBSTATUSOTUGAUGE_H

