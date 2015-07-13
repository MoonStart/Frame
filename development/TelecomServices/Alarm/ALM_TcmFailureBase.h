/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Xinlun Fang
 DESCRIPTION:   This class defines the failure type of ODU-TCM
--------------------------------------------------------------------------*/

#ifndef  ALM_TCMFAILUREBASE_H
#define  ALM_TCMFAILUREBASE_H

#include <CommonTypes/CT_OduDefinitions.h>
#include "Alarm/ALM_FailureBase.h"

class ALM_TcmFailureBase : public ALM_FailureBase, public CT_ODU_Identifier
{
public:

    ALM_TcmFailureBase (int theIndex, bool theDefaultStatus = false );

    virtual ~ALM_TcmFailureBase();

	virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

	virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex( int theIndex) const;

    virtual int GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetSigProtTypeFromIndex( int theIndex) const;

	virtual void PrintHeader() const;

    int  GetSignalType() const;
    void SetSignalType(int signalType);

    //uint8 GetTcmLevel() {return myTcmLevel;}
    

    enum ALM_FailureType
    {
        BDI_Tcm = 0,

        BER_Tcm,

        TIM_NSA_Tcm,
        TIM_Tcm,

        OCI_Tcm,

        LCK_Tcm,

        AIS_Tcm,

        LTC_NSA_Tcm,
        
        LTC_Tcm, 

        UPPER_NSA_Tcm,
 
        UPPER_SA_Tcm,

        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

    enum ALM_SP_DefectType
    {
        SP_NOT_SERVICE_AFFECTING = 0,

        ALM_SP_INVALID_DEFECT,

        ALM_SP_NB_OF_DEFECT = ALM_SP_INVALID_DEFECT
    };

protected:

    int itsSignalType;
    //uint8 myTcmLevel;

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    virtual ostream& WriteObject(ostream& theStream);

    virtual istream& ReadObject(istream& theStream);

};

#endif // ALM_TCMFAILUREBASE_H
