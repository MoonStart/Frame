/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Update and keep the PM defects of TCM layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTTCM_H
#define PM_BBDEFECTTCM_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <PM/src/PM_Defect.h>


// Forward declaration of classes
class MON_TcmDefects;

using namespace std;

//This class keeps and updates the TCM layer defect counters.
class PM_BbDefectTcm:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
    PM_BbDefectTcm ();

    //Class default destructor.
    virtual ~PM_BbDefectTcm();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestart);

    //Returns the TCM-AIS defect.
    inline bool EverPresentAIS() const;

    //Returns the TCM-LCK defect.
    inline bool EverPresentLCK() const;

    //Returns the TCM-OCI defect.
    inline bool EverPresentOCI() const;

    //Returns the TCM-TIM defect.
    inline bool EverPresentTIM() const;

    //Returns the TCM-LTC defect.
    inline bool EverPresentLTC() const;

    //Returns the TCM-IAE defect.
    inline bool EverPresentIAE() const;

    //Updates PM defects for the Multiplex Section signal.
    void Update(MON_TcmDefects& theTcmMonitor);

protected:

    //Stores the defects to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    virtual istream& ReadObject( istream& theStream );

private:

    //The TCM-AIS defect.
    PM_Defect myAISdefect;
    //The TCM-LCK defect.
    PM_Defect myLCKdefect;
    //The TCM-OCI defect.
    PM_Defect myOCIdefect;
    //The TCM-TIM defect.
    PM_Defect myTIMdefect;
    //The TCM-LTC defect.
    PM_Defect myLTCdefect;
    //The TCM-IAE defect.
    PM_Defect myIAEdefect;
};

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentAIS() const
{
    return myAISdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentLCK() const
{
    return myLCKdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentOCI() const
{
    return myOCIdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentTIM() const
{
    return myTIMdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentLTC() const
{
    return myLTCdefect.IsDeclared();

}

//-----------------------------------------------------------------
inline bool PM_BbDefectTcm::EverPresentIAE() const
{
    return myIAEdefect.IsDeclared();

}

#endif //PM_BBDEFECTTCM_H
