/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004  Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of Near-End SONET/SDH HOP layer
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTHOPNEAREND_H
#define PM_BBCOUNTHOPNEAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


/* Forward declaration of classes */
class MON_HopCounters;

using namespace std;

//Keeps various Near-End SONET/SDH HOP counters up to date for the current second.
class PM_BbCountHopNearEnd: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbCountHopNearEnd();

    //Class default destructor.
    virtual ~PM_BbCountHopNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the current count of BIP errors from the 
    //HOP layer (current hardware counter minus 
    //last hardware counter).
    uint32 GetBIP() const;

	// Returns the current count the positive pointer
	// justifications detected on a particular STS-1 path
	// (current hardware counter minus last hardware counter).
	uint32 GetPPJCDET() const;

	// Returns the current count the negative pointer
	// justifications detected on a particular STS-1 path
	// (current hardware counter minus last hardware counter).
	uint32 GetNPJCDET() const;

	// Returns the current count the positive pointer
	// justifications generated on a particular STS-1 path
	// (current hardware counter minus last hardware counter).
	uint32 GetPPJCGEN() const;

	// Returns the current count the negative pointer
	// justifications generated on a particular STS-1 path
	// (current hardware counter minus last hardware counter).
	uint32 GetNPJCGEN() const;

	//Updates the PM counters for the Multiplex Section.
    void Update(MON_HopCounters& theHopCounter);

protected:

    //Stores the counter to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter that memorizes the number of BIP errors for this second.
    PM_Counter myBIPCounter;

	// The PM counter containing the Positive Pointer Justification Count - Detected.
	PM_Counter myPPJCDETCounter;

	// The PM counter containing the Negative Pointer Justification Count - Detected.
	PM_Counter myNPJCDETCounter;

	// The PM counter containing the Positive Pointer Justification Count - Generated.
	PM_Counter myPPJCGENCounter;

	// The PM counter containing the Positive Pointer Justification Count - Generated.
	PM_Counter myNPJCGENCounter;
};

//-----------------------------------------------------------------
inline uint32 PM_BbCountHopNearEnd::GetBIP() const
{
    return myBIPCounter.GetCount();
}

//-----------------------------------------------------------------
inline uint32 PM_BbCountHopNearEnd::GetPPJCDET() const
{
    return myPPJCDETCounter.GetCount();
}

//-----------------------------------------------------------------
inline uint32 PM_BbCountHopNearEnd::GetNPJCDET() const
{
    return myNPJCDETCounter.GetCount();
}

//-----------------------------------------------------------------
inline uint32 PM_BbCountHopNearEnd::GetPPJCGEN() const
{
    return myPPJCGENCounter.GetCount();
}

//-----------------------------------------------------------------
inline uint32 PM_BbCountHopNearEnd::GetNPJCGEN() const
{
    return myNPJCGENCounter.GetCount();
}
#endif //PM_BBCOUNTHOPNEAREND_H
