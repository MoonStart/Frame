/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM failures of Near-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBFAILUREHOPNEAREND_H
#define PM_BBFAILUREHOPNEAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Failure.h"


// Forward declaration of classes
class ALM_HopFailureBase;

using namespace std;

//This class keeps and updates the Near-End SONET/SDH HOP layer failure counters.
class PM_BbFailureHopNearEnd:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbFailureHopNearEnd ();

    //Class default destructor.
    virtual ~PM_BbFailureHopNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns true if HOP-AIS failure was declared during last one second.
    inline bool EverDeclaredAIS() const;

    //Returns true if HOP-LOP failure was declared during last one second.
    inline bool EverDeclaredLOP() const;

    //Returns true if HOP-UNEQ failure was declared during last one second.
    inline bool EverDeclaredUNEQ() const;

    //Returns true if HOP-PLM failure was declared during last one second.
    inline bool EverDeclaredPLM() const;

    //Returns true if HOP-Upper-SA failure was declared during last one second.
    inline bool EverDeclaredUpperSA() const;

    //Updates PM failures for the Multiplex Section signal.
    void Update(ALM_FailureBase& theHopAlm);

protected:

    //Stores the failures to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the failures from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The HOP-AIS failure.
    PM_Failure myAISfailure;

    //The HOP-LOP failure.
    PM_Failure myLOPfailure;

    //The HOP-UNEQ failure.
    PM_Failure myUNEQfailure;

    //The HOP-PLM failure.
    PM_Failure myPLMfailure;

	// The HOP-Upper-SA failure.
	PM_Failure myUpperSAfailure;

};

//-----------------------------------------------------------------
inline bool PM_BbFailureHopNearEnd::EverDeclaredAIS() const
{
    return myAISfailure.DidTransitionToDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbFailureHopNearEnd::EverDeclaredLOP() const
{
    return myLOPfailure.DidTransitionToDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbFailureHopNearEnd::EverDeclaredUNEQ() const
{
    return myUNEQfailure.DidTransitionToDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbFailureHopNearEnd::EverDeclaredPLM() const
{
    return myPLMfailure.DidTransitionToDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbFailureHopNearEnd::EverDeclaredUpperSA() const
{
    return myUpperSAfailure.DidTransitionToDeclared();

}

#endif //PM_BBFAILUREHOPNEAREND_H
