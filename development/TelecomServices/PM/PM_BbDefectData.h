/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   Update and keep the PM defects of Data.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTDATA_H
#define PM_BBDEFECTDATA_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_RsDefects;
class MON_OptDefects;

using namespace std;

//This class keeps and updates the Data defect 
//counters.
//##ModelId=3C20AB6E0020
class PM_BbDefectData: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    //##ModelId=3C20AB6E023E
    PM_BbDefectData ();

    //Class default destructor.
    //##ModelId=3C20AB6E0247
    virtual ~PM_BbDefectData();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F120151
    virtual void Init(restart_type theRestart);

    //Returns the LOS defect.
    //##ModelId=3C20AB6E0265
    inline bool EverPresentLOS() const;

    //Returns the LOF defect.
    //##ModelId=3C20AB6E026F
    inline bool EverPresentLOF() const;

    //Returns the SEF defect.
    //##ModelId=3C20AB6E0279
    inline bool EverPresentSEF() const;

    //Returns the TIM defect.
    //##ModelId=3E6E4D2600BB
    inline bool EverPresentTIM() const;

    //Updates PM defects for the Regenerator Section signal.
    //##ModelId=3C20AB6E0283
    void Update(MON_RsDefects& theRsMonitor, MON_OptDefects* theOptMonitorPtr=NULL);

    // Updates PM defects based on Optical signal
    // Certain applications depend on OPT-LOS due to
    // unavailability of RS-LOS measurements.
    void Update(MON_OptDefects* theOptMonitorWorking, MON_OptDefects* theOptMonitorProtect = 0,
                bool theProtectSelected = false);

protected:

    //Stores the defects to the stream.
    //##ModelId=3C20AB6E028E
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3C20AB6E02A1
    virtual istream& ReadObject( istream& theStream );

private:

    // The LOS defect.In case of protection pair,
    // this is the working facility monitor
    //##ModelId=3C20AB6E02C0
    PM_Defect myLOSdefect;
    
    // In case of protection pair,
    // this is the protect facility monitor
    PM_Defect myLOSdefectProtect;

    //The LOF defect.
    //##ModelId=3C20AB6E02E8
    PM_Defect myLOFdefect;

    //The SEF defect.
    //##ModelId=3C20AB6E0310
    PM_Defect mySEFdefect;

    //The TIM defect.
    //##ModelId=3E6E4D2700C8
    PM_Defect myTIMdefect;

    // Is the protect facility the selected facility?
    bool myProtectSelected;

};

//-----------------------------------------------------------------
//##ModelId=3C20AB6E0265
inline bool PM_BbDefectData::EverPresentLOS() const
{
    bool retValue;

    if (myProtectSelected) 
    {
        retValue = myLOSdefectProtect.IsDeclared();
    }
    else
    {
        retValue = myLOSdefect.IsDeclared();
    }
    return retValue;
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E026F
inline bool PM_BbDefectData::EverPresentLOF() const
{
    return myLOFdefect.IsDeclared();
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E0279
inline bool PM_BbDefectData::EverPresentSEF() const
{
    return mySEFdefect.IsDeclared();
}

//-----------------------------------------------------------------
//##ModelId=3E6E4D2600BB
inline bool PM_BbDefectData::EverPresentTIM() const
{
    return myTIMdefect.IsDeclared();
}

#endif //PM_BBDEFECTDATA_H
