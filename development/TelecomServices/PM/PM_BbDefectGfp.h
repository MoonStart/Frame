/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004  Hemant Thakkar.
 DESCRIPTION:   Update and keep the PM defects of GFP layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTGFP_H
#define PM_BBDEFECTGFP_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_GfpDefects;

using namespace std;

//This class keeps and updates the GFP layer defect counters.
class PM_BbDefectGfp:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbDefectGfp ();

    //Class default destructor.
    virtual ~PM_BbDefectGfp();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the LOFD defect.
    inline bool EverPresentLOFD() const;

    //Updates PM defects for the Multiplex Section signal.
    void Update(MON_GfpDefects& theGfpMonitor);

protected:

    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The LOFD defect.
    PM_Defect myLOFDdefect;

};

//-----------------------------------------------------------------
inline bool PM_BbDefectGfp::EverPresentLOFD() const
{
    return myLOFDdefect.IsDeclared();

}

#endif //PM_BBDEFECTGFP_H
