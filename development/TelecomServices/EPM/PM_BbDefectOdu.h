/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Update and keep the PM defects of ODU layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTODU_H
#define PM_BBDEFECTODU_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <PM/src/PM_Defect.h>


// Forward declaration of classes
class MON_OduDefects;

using namespace std;

//This class keeps and updates the ODU layer defect counters.
class PM_BbDefectOdu:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbDefectOdu ();

    //Class default destructor.
    virtual ~PM_BbDefectOdu();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the ODU-AIS defect.
    inline bool EverPresentAIS() const;

    //Returns the ODU-LCK defect.
    inline bool EverPresentLCK() const;

    //Returns the ODU-OCI defect.
    inline bool EverPresentOCI() const;

    //Returns the ODU-TIM defect.
    inline bool EverPresentTIM() const;

    //Updates PM defects for the Multiplex Section signal.
    void Update(MON_OduDefects& theOduMonitor);

protected:

    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The ODU-AIS defect.
    PM_Defect myAISdefect;
    //The ODU-LCK defect.
    PM_Defect myLCKdefect;
    //The ODU-OCI defect.
    PM_Defect myOCIdefect;
	// The ODU-TIM defect.
    PM_Defect myTIMdefect;
};

//-----------------------------------------------------------------
inline bool PM_BbDefectOdu::EverPresentAIS() const
{
    return myAISdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectOdu::EverPresentLCK() const
{
    return myLCKdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectOdu::EverPresentOCI() const
{
    return myOCIdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectOdu::EverPresentTIM() const
{
    return myTIMdefect.IsDeclared();

}

#endif //PM_BBDEFECTODU_H
