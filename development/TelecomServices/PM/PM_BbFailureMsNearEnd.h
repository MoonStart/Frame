/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM failures of Near-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBFAILUREMSNEAREND_H
#define PM_BBFAILUREMSNEAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Failure.h"


// Forward declaration of classes
class ALM_MsFailureBase;

using namespace std;

//This class keeps and updates the Near-End SONET/SDH MS layer failure counters.
class PM_BbFailureMsNearEnd:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbFailureMsNearEnd ();

    //Class default destructor.
    virtual ~PM_BbFailureMsNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns true if MS-AIS failure was declared during last one second.
    inline bool EverDeclaredAIS() const;

    //Returns true if MS-Upper-SA failure was declared during last one second.
    inline bool EverDeclaredUpperSA() const;

    //Updates PM failures for the Multiplex Section signal.
    void Update(ALM_FailureBase& theMsAlm);

protected:

    //Stores the failures to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the failures from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The MS-AIS failure.
    PM_Failure myAISfailure;

	// The MS-Upper-SA failure.
	PM_Failure myUpperSAfailure;

};

//-----------------------------------------------------------------
inline bool PM_BbFailureMsNearEnd::EverDeclaredAIS() const
{
    return myAISfailure.DidTransitionToDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbFailureMsNearEnd::EverDeclaredUpperSA() const
{
    return myUpperSAfailure.DidTransitionToDeclared();

}

#endif //PM_BBFAILUREMSNEAREND_H
