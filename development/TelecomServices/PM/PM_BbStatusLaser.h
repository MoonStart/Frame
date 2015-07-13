/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 07, 2002.
 DESCRIPTION:   Update and keep the PM status of the Laser.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSLASER_H
#define PM_BBSTATUSLASER_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Defect.h>
#include <PM/PM_BbStatus.h>
#include <PM/PM_TypeLaser.h>


// Forward declaration of classes
class MON_TxOptStatus;

using namespace std;

//This class keeps and updates the Status related to Laser.
//##ModelId=3C20AB6C0009
class PM_BbStatusLaser: public PM_BbStatus
{
public:

    //Class default constructor.
    //##ModelId=3C20AB6C0208
    PM_BbStatusLaser ();

    //Class default destructor.
    //##ModelId=3C20AB6C0212
    virtual ~PM_BbStatusLaser();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F0F002A
    virtual void Init(restart_type theRestart);

    //Updates PM statuses for the TX OPT layer.
    //##ModelId=3C50163102F8
    void Update(MON_TxOptStatus& theTxOptMonitor);

    //Returns the LT status.
    //##ModelId=3E6E4D040301
    inline int32 GetLT() const;

    //Returns the LBC status.
    //##ModelId=3E6E4D050045
    inline int32 GetLBC() const;

protected:

    //Stores the defects to the stream.
    //##ModelId=3C20AB6C023A
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3C20AB6C024E
    virtual istream& ReadObject( istream& theStream );

};

//-----------------------------------------------------------------
//##ModelId=3E6E4D040301
inline int32 PM_BbStatusLaser::GetLT() const
{
    return myParam[PM_TypeLaser::PM_LT].SignedValue;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D050045
inline int32 PM_BbStatusLaser::GetLBC() const
{
    return myParam[PM_TypeLaser::PM_LBC].SignedValue;

}

#endif //PM_BBSTATUSLASER_H
