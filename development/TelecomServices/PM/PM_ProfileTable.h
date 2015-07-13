/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TelecomServices Performance Monitoring

TARGET:         ActiveController, SMTMU, SSM

AUTHOR:         Michael Sharkey
-----------------------------------------------------------------------------*/ 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _INC_PM_PROFILE_TABLE_INCLUDED
#define _INC_PM_PROFILE_TABLE_INCLUDED

#include <Blackboard/FC_BbObject.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_PM_Definition.h>

#include "../incl/gdef.h"

using namespace std;

#include <vector>
#include <algorithm>

typedef vector<uint32> PM_ThresholdList;

class PM_ProfileTableElem;

class PM_ProfileTable : public FC_BbObject
{
public:

    PM_ProfileTable();
    virtual ~PM_ProfileTable();

    virtual ostream&   WriteObject(ostream& theStream);
    virtual istream&   ReadObject (istream& theStream);
    virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);

    void SetEntityType(CT_EntityType theEntityType);
    PM_ProfileTableElem* GetPMProfileTableElem(CT_DirectionFlag theDir, CT_PM_Period thePeriod);

protected:

private:

    CT_EntityType myEntityType;
    PM_ProfileTableElem* myPMProfileTable_DIR1_15M;
    PM_ProfileTableElem* myPMProfileTable_DIR2_15M;
    PM_ProfileTableElem* myPMProfileTable_DIR1_1DAY;
    PM_ProfileTableElem* myPMProfileTable_DIR2_1DAY;
};

class PM_ProfileTableElem
{
public:

    PM_ProfileTableElem(CT_EntityType theEntityType);
    virtual ~PM_ProfileTableElem();

    virtual ostream&   WriteObject(ostream& theStream);
    virtual istream&   ReadObject (istream& theStream);
    virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);

    bool   GetInUseState();
    uint32 GetCVPThreshold();
    uint32 GetESPThreshold();
    uint32 GetSESPThreshold();
    uint32 GetUASPThreshold();
    uint32 GetFCPThreshold();
    uint32 GetPJCDiffPThreshold();
    uint32 GetPJCSPGenThreshold();
    uint32 GetPJCSPDetThreshold();
    uint32 GetCVODUThreshold();
    uint32 GetESODUThreshold();
    uint32 GetSESODUThreshold();
    uint32 GetUASODUThreshold();
    uint32 GetCVTcmThreshold();
    uint32 GetESTcmThreshold();
    uint32 GetSESTcmThreshold();
    uint32 GetUASTcmThreshold();
    uint32 GetThreshold(CT_PM_Parameter theId);

    void SetInUseState        (bool   theInUseState);
    void SetCVPThreshold      (uint32 theCVPThreshold);
    void SetESPThreshold      (uint32 theESPThreshold);
    void SetSESPThreshold     (uint32 theSESPThreshold);
    void SetUASPThreshold     (uint32 theUASPThreshold);
    void SetFCPThreshold      (uint32 theFCPThreshold);
    void SetPJCDiffPThreshold (uint32 thePJCDiffPThreshold);
    void SetPJCSPGenThreshold (uint32 thePJCSPGenThreshold);
    void SetPJCSPDetThreshold (uint32 thePJCSPDetThreshold);
    void SetCVODUThreshold    (uint32 theCVODUThreshold);
    void SetESODUThreshold    (uint32 theESODUThreshold);
    void SetSESODUThreshold   (uint32 theSESODUThreshold);
    void SetUASODUThreshold   (uint32 theUASODUThreshold);
    void SetCVTcmThreshold    (uint32 theCVTcmThreshold);
    void SetESTcmThreshold    (uint32 theESTcmThreshold);
    void SetSESTcmThreshold   (uint32 theSESTcmThreshold);
    void SetUASTcmThreshold   (uint32 theUASTcmThreshold);
    void SetThreshold         (CT_PM_Parameter theId, uint32 theThreshold);

protected:

private:

    CT_EntityType myEntityType;
    uint8  myNbParams;
    bool   myInUseState;
    PM_ThresholdList myThresholdList;
};

#endif /* _INC_PM_PROFILE_TABLE_INCLUDED */
