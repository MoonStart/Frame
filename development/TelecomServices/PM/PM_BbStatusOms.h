/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Update and keep the PM status of Oms parameters.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSOMS_H
#define PM_BBSTATUSOMS_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Defect.h>
#include <PM/PM_BbStatus.h>
#include <PM/PM_TypeOms.h>


// Forward declaration of classes
class MON_OmsStatus;

using namespace std;

//This class keeps and updates the Status related to Oms 
//parameters.
//##ModelId=3E6E4CF6004E
class PM_BbStatusOms:    public PM_BbStatus
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CF70028
    PM_BbStatusOms ();

    //Class default destructor.
    //##ModelId=3E6E4CF70031
    virtual ~PM_BbStatusOms();

    //Initializes BB object according to the restart type.
    //##ModelId=3E6E4CF7003B
    virtual void Init(restart_type theRestart);

    //Updates PM statuses of Oms parameters.
    //##ModelId=3E6E4CF70063
    void Update(MON_OmsStatus& theOmsMonitor);

    //Returns the OPT status.
    //##ModelId=3E6E4CF7009F
    inline int32 GetOPT() const;

    //Returns the OPR status.
    //##ModelId=3E6E4CF700D2
    inline int32 GetOPR() const;

protected:
    
    //Stores the defects to the stream.
    //##ModelId=3E6E4CF700E6
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3E6E4CF70104
    virtual istream& ReadObject( istream& theStream );

};

//-----------------------------------------------------------------
//##ModelId=3E6E4CF7009F
inline int32 PM_BbStatusOms::GetOPT() const
{
    return myParam[PM_TypeOms::PM_OPT].SignedValue;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF700D2
inline int32 PM_BbStatusOms::GetOPR() const
{
    return myParam[PM_TypeOms::PM_OPR].SignedValue;

}

#endif //PM_BBSTATUSOMS_H
