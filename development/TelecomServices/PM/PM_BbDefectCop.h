/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, March 3, 2003.
 DESCRIPTION:   Update and keep the PM defects of Channel Optical Power.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTCOP_H
#define PM_BBDEFECTCOP_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_OchDefects;
class MON_OptDefects;

using namespace std;

//This class keeps and updates the COP defect 
//counters.
//##ModelId=3E6E4D000265
class PM_BbDefectCop:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    //##ModelId=3E6E4D01031C
    PM_BbDefectCop ();

    //Class default destructor.
    //##ModelId=3E6E4D010325
    virtual ~PM_BbDefectCop();

    //Initializes BB object according to the restart type.
    //##ModelId=3E6E4D01032F
    virtual void Init(restart_type theRestart);

    //Returns the LOP defect.
    //##ModelId=3E6E4D010393
    inline bool EverPresentLOP() const;

    //Updates PM defects for the COP based on MON_OchDefect
    //##ModelId=3E6E4D0103A7
    void Update(MON_OchDefects& theCopMonitor);

    //Updates PM defects for the COP based on MON_OptDefect
    void Update(MON_OptDefects& theCopMonitor);
protected:

    //Stores the defects to the stream.
    //##ModelId=3E6E4D0103B2
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3E6E4D0103C6
    virtual istream& ReadObject( istream& theStream );

private:

    //The LOP defect.
    //##ModelId=3E6FC0490057
    PM_Defect myLOPdefect;

};

//-----------------------------------------------------------------
//##ModelId=3E6E4D010393
inline bool PM_BbDefectCop::EverPresentLOP() const
{
    return myLOPdefect.IsDeclared();

}

#endif //PM_BBDEFECTCOP_H
