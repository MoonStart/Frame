/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   Update and keep the PM status of Optical Channel.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSCOP_H
#define PM_BBSTATUSCOP_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Defect.h>
#include <PM/PM_BbStatus.h>
#include <PM/PM_TypeCop.h>


// Forward declaration of classes
class MON_OchStatus;
class MON_OptStatus;

using namespace std;

//This class keeps and updates the Status related to  
//Optical Channel.
//##ModelId=3C50163103B7
class PM_BbStatusCop:    public PM_BbStatus
{
public:

    //Class default constructor.
    //##ModelId=3C5016320214
    PM_BbStatusCop ();

    //Class default destructor.
    //##ModelId=3C5016320215
    virtual ~PM_BbStatusCop();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F0F026F
    virtual void Init(restart_type theRestart);

    //Updates PM statuses for the Optical Channel.
    //##ModelId=3C5016320233
    void Update(MON_OchStatus& theOchMonitor, bool theAltPower = false);

    //Updates PM statuses for the Optical Channel.
    void Update(MON_OptStatus& theOchMonitor);

    //Returns the Cop status.
    //##ModelId=3E6E4CFF0051
    inline int32 GetCop() const;

protected:
    
    //Stores the defects to the stream.
    //##ModelId=3C501632023D
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3C5016320248
    virtual istream& ReadObject( istream& theStream );

};

//-----------------------------------------------------------------
//##ModelId=3E6E4CFF0051
inline int32 PM_BbStatusCop::GetCop() const
{
    return myParam[PM_TypeCop::PM_COP].SignedValue;

}

#endif //PM_BBSTATUSCOP_H
