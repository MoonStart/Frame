/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM failures of Far-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBFAILUREMSFAREND_H
#define PM_BBFAILUREMSFAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Failure.h"


// Forward declaration of classes
class ALM_MsFailureBase;

using namespace std;

//This class keeps and updates the Far-End SONET/SDH MS layer failure counters.
class PM_BbFailureMsFarEnd:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbFailureMsFarEnd ();

    //Class default destructor.
    virtual ~PM_BbFailureMsFarEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns true if MS-RDI failure was declared during last one second.
    inline bool EverDeclaredRDI() const;

    //Updates PM failures for the Multiplex Section signal.
    void Update(ALM_FailureBase& theMsMonitor);

protected:

    //Stores the failures to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the failures from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The MS-RDI failure.
    PM_Failure myRDIfailure;

};

//-----------------------------------------------------------------
inline bool PM_BbFailureMsFarEnd::EverDeclaredRDI() const
{
    return myRDIfailure.DidTransitionToDeclared();

}

#endif //PM_BBFAILUREMSFAREND_H
