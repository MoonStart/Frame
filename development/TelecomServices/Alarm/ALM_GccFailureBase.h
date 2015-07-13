/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     
 AUTHOR   :     Xinlun Fang
 DESCRIPTION:   This class defines the failure type of GCC Link layer.
--------------------------------------------------------------------------*/

#ifndef ALM_GCCFAILUREBASE_H
#define ALM_GCCFAILUREBASE_H

#include <CommonTypes/CT_OduDefinitions.h>
#include "Alarm/ALM_FailureBase.h"
#include "Alarm/src/ALM_DefectStatusDefinition.h"
#include "Alarm/ALM_FPCommon.h"


class ALM_GCCFailureBase : public ALM_FailureBase, public CT_ODU_Identifier
{
public:

    ALM_GCCFailureBase (int theIndex, bool theDefaultStatus = false );

    virtual ~ALM_GCCFailureBase();
    int GetSignalType() const;
    void SetSignalType(int signalType);

    virtual int GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const;

    virtual CT_TelAlarmCondition::CT_FacilityAlarmType GetTypeFromIndex(int theIndex) const;

    virtual void PrintHeader() const;

    enum ALM_FailureType
    {
        GCC_LINK_DOWN = 0,

        GCC_LINK_INCMPLT,

        UPPER_NSA_GCC,

        UPPER_SA_GCC,

        ALM_INVALID_FAILURE,

        ALM_NB_OF_FAILURE = ALM_INVALID_FAILURE
    };

protected:

    int itsSignalType;

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject(ostream& theStream);
    virtual istream& ReadObject(istream& theStream);

};

#endif //ALM_GCCFAILUREBASE_H
