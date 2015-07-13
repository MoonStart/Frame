/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     December 12, 2001 Sebastien Cossette.
 DESCRIPTION:   Update and keep the PM status of Optical parameters.
--------------------------------------------------------------------------*/

#ifndef PM_BBSTATUSOPT_H
#define PM_BBSTATUSOPT_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_BbStatus.h>
#include <PM/src/PM_Defect.h>
#include <PM/PM_TypeOpt.h>


// Forward declaration of classes
class MON_OptStatus;
class MON_TxOptStatus;

using namespace std;

//This class keeps and updates the Status related to Optical 
//parameters.
//##ModelId=3C20AB6C032A
class PM_BbStatusOpt:    public PM_BbStatus
{
public:

    //Class default constructor.
    //##ModelId=3C20AB6D016A
    PM_BbStatusOpt ();

    //Class default destructor.
    //##ModelId=3C20AB6D0173
    virtual ~PM_BbStatusOpt();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F1001C6
    virtual void Init(restart_type theRestart);

    //Updates PM statuses of Optical parameters.
    //##ModelId=3C20AB6D01B9
    void Update(MON_OptStatus& theOptMonitor, MON_TxOptStatus& theTxOptMonitor);

	//Updates PM statuses of Optical parameters.
    void Update(MON_OptStatus& theOptMonitor);

    //Returns the OPT status.
    //##ModelId=3E6E4D0802DF
    inline int32 GetOPT() const;

    //Returns the OPR status.
    //##ModelId=3E6E4D090037
    inline int32 GetOPR() const;

    inline int32 GetDGD() const;

    inline int32 GetCD() const;

    inline int32 GetOSNR() const;

protected:
    
    //Stores the defects to the stream.
    //##ModelId=3C20AB6D01C4
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the defects from the stream.
    //##ModelId=3C20AB6D01D7
    virtual istream& ReadObject( istream& theStream );

};

//-----------------------------------------------------------------
//##ModelId=3E6E4D0802DF
inline int32 PM_BbStatusOpt::GetOPT() const
{
    return myParam[PM_TypeOpt::PM_OPT].SignedValue;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D090037
inline int32 PM_BbStatusOpt::GetOPR() const
{
    return myParam[PM_TypeOpt::PM_OPR].SignedValue;

}

//-----------------------------------------------------------------
inline int32 PM_BbStatusOpt::GetDGD() const
{
    return myParam[PM_TypeOpt::PM_DGD].SignedValue;
 
}

//-----------------------------------------------------------------
inline int32 PM_BbStatusOpt::GetCD() const
{
    return myParam[PM_TypeOpt::PM_CD].SignedValue;
 
}

//-----------------------------------------------------------------
inline int32 PM_BbStatusOpt::GetOSNR() const
{
    return myParam[PM_TypeOpt::PM_OSNR].SignedValue;
 
}
#endif //PM_BBSTATUSOPT_H
