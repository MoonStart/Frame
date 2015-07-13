/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM defects of Near-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTMSNEAREND_H
#define PM_BBDEFECTMSNEAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_MsDefects;

using namespace std;

//This class keeps and updates the Near-End SONET/SDH MS layer defect counters.
class PM_BbDefectMsNearEnd:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbDefectMsNearEnd ();

    //Class default destructor.
    virtual ~PM_BbDefectMsNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the MS-AIS defect.
    inline bool EverPresentAIS() const;

    //Updates PM defects for the Multiplex Section signal.
    void Update(MON_MsDefects& theMsMonitor);

protected:

    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The MS-AIS defect.
    PM_Defect myAISdefect;

};

//-----------------------------------------------------------------
inline bool PM_BbDefectMsNearEnd::EverPresentAIS() const
{
    return myAISdefect.IsDeclared();

}

#endif //PM_BBDEFECTMSNEAREND_H
