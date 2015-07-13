/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     September 16, 2002. Steve Thiffault
 DESCRIPTION:   Update and keep the PM defects of Optical 
                Transport Unit or FEC.
--------------------------------------------------------------------------*/

#ifndef PM_BBDEFECTOTU_H
#define PM_BBDEFECTOTU_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <Monitoring/MON_OptDefects.h>
#include "src/PM_Defect.h"


// Forward declaration of classes
class MON_OtuDefects;

using namespace std;

//This class keeps and updates OTU defects.
//##ModelId=3E6E4D1F021A
class PM_BbDefectOtu:    public TEL_BbObjectBase
{
public:

    //Class default constructor.
	//##ModelId=3E6E4D200280
    PM_BbDefectOtu ();

    //Class default destructor.
	//##ModelId=3E6E4D200289
    virtual ~PM_BbDefectOtu();

    //Initializes BB object according to the restart type.
	//##ModelId=3E6E4D200293
    virtual void Init(restart_type theRestart);

    //Returns the LOF/LOMF defect.
	//##ModelId=3E6E4D2002C5
    inline bool EverPresentLOF() const;

	//Returns the LOS defect.
	//##ModelId=3E6E4D2002C5
    inline bool EverPresentLOS() const;

    //Returns the TIM defect.
    inline bool EverPresentTIM() const;

    //Returns the IAE defect.
    inline bool EverPresentIAE() const;

    //Updates OTU PM defects for the OTU signal.
	//##ModelId=3E6E4D20032A
    void Update(MON_OtuDefects& theOtuMonitor);

	//Updates OPT PM defects for the OTU signal.
	void Update(MON_OptDefects& theOptMonitor);

protected:

    //Stores the defects to the stream.
	//##ModelId=3E6E4D20033D
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
	//##ModelId=3E6E4D200351
    virtual istream& ReadObject( istream& theStream );

private:

    //The LOF defect.
    PM_Defect myLOFdefect;

    //The LOM defect.
    PM_Defect myLOMdefect;

	// The LOS defect.
    PM_Defect myLOSdefect;

	// The TIM defect.
    PM_Defect myTIMdefect;

    // The IAE defect.
    PM_Defect myIAEdefect;
};

//-----------------------------------------------------------------
inline bool PM_BbDefectOtu::EverPresentLOF() const
{
    return ( myLOFdefect.IsDeclared() || myLOMdefect.IsDeclared() );
}

inline bool PM_BbDefectOtu::EverPresentLOS() const
{
    return myLOSdefect.IsDeclared();
}

inline bool PM_BbDefectOtu::EverPresentTIM() const
{
    return myTIMdefect.IsDeclared();
}

inline bool PM_BbDefectOtu::EverPresentIAE() const
{
    return myIAEdefect.IsDeclared();
}

#endif //PM_BBDEFECTOTU_H
