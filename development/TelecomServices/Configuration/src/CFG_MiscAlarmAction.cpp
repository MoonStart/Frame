/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM: Telecom Services/Facility AM subsystem
 TARGET   : SPM controller on first main shelf only
 AUTHOR   : Teresa Chen
 DESCRIPTION:
    Header file for the CFG_MiscAlarmAction class.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_FabIf.h>
#include <Configuration/CFG_MiscAlarmAction.h>
#include <Configuration/CFG_Misc.h>
#include <Configuration/CFG_AppIf.h>
#include <Blackboard/FC_BbAction.h>
#include <AM/AM_DefectCollector.h>
#include <AM/AM_DefectProcessor.h>

//---------------------------------------------------------------------------------
CFG_MiscAlarmAction::CFG_MiscAlarmAction(CFG_AppIf& theCfgIf, CT_ShelfId theShelfId)
:myCfgIf(theCfgIf)
,myLastSwitchDomainAlarm(AM_ID_UNDEF)
,myShelfId(theShelfId)
{
    myBbAction =  new FC_BbAction(this);
	myBbAction->AddInputRegion(theCfgIf.GetCfgRegion());
}

//---------------------------------------------------------------------------------
CFG_MiscAlarmAction::~CFG_MiscAlarmAction()
{
}

//---------------------------------------------------------------------------------
FC_Object* CFG_MiscAlarmAction::DoRunWithReason(unsigned theRunReason,
                                                     FC_Object* theInvokerObj,
                                                     FC_Object* theParam)
{
    CFG_Misc& aCfgObject = static_cast<CFG_Misc&>((*GetCfgIf().GetCfgRegion())[0]);
    CT_TEL_SwitchMode aSwitchMode = aCfgObject.GetSwitchMode();
    CT_ShelfType aShelfType = aCfgObject.GetShelfType();

    // Do nothing if not HCSS shelf type
    if (aShelfType != PORT_SHELF_HCSS_TYPE)
    {
        return NULL;
    }

    // myShelfId not active switched shelf
    if ((aSwitchMode != CT_TEL_SwitchMode_Cntr_Switch)
        || (myShelfId == UNKNOWN_SHELF_ID)
        || (myShelfId != aCfgObject.GetSwitchDomain()))
    {
        return NULL;
    }

    int aNbrOfSlots = aCfgObject.GetNbrOfSlots();
    CT_ProtLevel aProtLvl = aCfgObject.GetProtLvl();
    uint8 numFabSlice = aCfgObject.GetNumFabSlice();
    if ((aSwitchMode == CT_TEL_SwitchMode_Cntr_Switch) && (aNbrOfSlots != 0))
    {
        bool setAlm  = false;
        bool clrAlm = false;
        AM_UID currAlarm = GetCurrAlarm( aProtLvl, numFabSlice, setAlm, clrAlm);

        AM_DefectProcessor* aShelfDP = AM_DefectCollector::GetInstance()->GetDefectProcessor(CARD_FAM_UNKNOWN, myShelfId, UNKNOWN_SLOT_ID, (bool) false);

        if (clrAlm)
        {
            aShelfDP->ClearDefect(myLastSwitchDomainAlarm, AM_LOCAL, AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, myShelfId-1);
        }

        if (setAlm)
        {    
            FC_Time aTimeStamp; aTimeStamp.GetCurrentTime();
            aShelfDP->ReportDefect(currAlarm, AM_LOCAL, aTimeStamp.GetUTCTime(), AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, myShelfId-1);
        }

        myLastSwitchDomainAlarm = currAlarm;
    }
    return NULL;
}

//---------------------------------------------------------------------------------
AM_UID CFG_MiscAlarmAction::GetCurrAlarm( CT_ProtLevel aProtLvl, uint8 numFabSlice,
                                           bool& setAlm, bool& clrAlm )
{
    AM_UID currAlarm = GetAlm2ProtLvl(aProtLvl, numFabSlice);
    if (currAlarm == myLastSwitchDomainAlarm)
    {
        setAlm = false;
        clrAlm = false;
    }
    else if (currAlarm != myLastSwitchDomainAlarm)
    {
        if (currAlarm == AM_ID_UNDEF)
        {
            setAlm = false;
            clrAlm = true;
        }
        else if (myLastSwitchDomainAlarm == AM_ID_UNDEF)
        {
            setAlm = true;
            clrAlm = false;
        }
        else
        {
            setAlm = true;
            clrAlm = true;
        }
    }
    return currAlarm;
}

//---------------------------------------------------------------------------------
AM_UID CFG_MiscAlarmAction::GetAlm2ProtLvl( CT_ProtLevel aProtLvl, uint8 numFabSlice )
{
    for (int i = 0; i < CFG_HCSS_AlmCond_Size; i++)
    {
        if ((CFG_HCSS_AlmCond[i].protLvl == aProtLvl)
            && (CFG_HCSS_AlmCond[i].numFabSlice == numFabSlice))
        {
            return (CFG_HCSS_AlmCond[i].almCond);
        }
    }
    return AM_ID_UNDEF;
}
