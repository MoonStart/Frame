/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM defects of Near-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTHOPNEAREND_H
#define PM_BBDEFECTHOPNEAREND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_HopDefects;

using namespace std;

//This class keeps and updates the Near-End SONET/SDH HOP layer defect counters.
class PM_BbDefectHopNearEnd:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbDefectHopNearEnd ();

    //Class default destructor.
    virtual ~PM_BbDefectHopNearEnd();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the HOP-AIS defect.
    inline bool EverPresentAIS() const;

    //Returns the HOP-LOP defect.
    inline bool EverPresentLOP() const;

    //Returns the HOP-UNEQ defect.
    inline bool EverPresentUNEQ() const;

    //Returns the HOP-PLM defect.
    inline bool EverPresentPLM() const;

    //Updates PM defects for the Multiplex Section signal.
    void Update(MON_HopDefects& theHopMonitor);

protected:

    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The HOP-AIS defect.
    PM_Defect myAISdefect;
    //The HOP-LOP defect.
    PM_Defect myLOPdefect;
    //The HOP-UNEQ defect.
    PM_Defect myUNEQdefect;
    //The HOP-PLM defect.
    PM_Defect myPLMdefect;

};

//-----------------------------------------------------------------
inline bool PM_BbDefectHopNearEnd::EverPresentAIS() const
{
    return myAISdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectHopNearEnd::EverPresentLOP() const
{
    return myLOPdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectHopNearEnd::EverPresentUNEQ() const
{
    return myUNEQdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectHopNearEnd::EverPresentPLM() const
{
    return myPLMdefect.IsDeclared();

}

#endif //PM_BBDEFECTHOPNEAREND_H
