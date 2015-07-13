/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Update and keep the error count of ODU layer
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTODU_H
#define PM_BBCOUNTODU_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <PM/src/PM_Counter.h>


/* Forward declaration of classes */
class MON_OduCounters;

using namespace std;

//Keeps various Near-End SONET/SDH HOP counters up to date for the current second.
class PM_BbCountOdu: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbCountOdu();

    //Class default destructor.
    virtual ~PM_BbCountOdu();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of BIP errors from the 
    //ODU layer (current hardware counter minus 
    //last hardware counter).
    unsigned long long GetBIP() const;

	//Updates the PM counters for the ODU layer.
    void Update(MON_OduCounters& theOduCounter);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that memorizes the number of BIP errors for this second.
    PM_Counter myBIPCounter;

};

//-----------------------------------------------------------------
inline unsigned long long PM_BbCountOdu::GetBIP() const
{
    return myBIPCounter.GetCount();
}

#endif //PM_BBCOUNTODU_H
