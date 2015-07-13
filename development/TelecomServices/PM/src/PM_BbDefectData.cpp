/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   Update and keep the PM defects of Data.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <PM_BbDefectData.h>
#include <BaseClass/FC_TextStream.h>

//-----------------------------------------------------------------
//##ModelId=3C20AB6E023E
PM_BbDefectData::PM_BbDefectData ()  : 
   myProtectSelected(false)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E0247
PM_BbDefectData::~PM_BbDefectData ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E0283
void PM_BbDefectData::Update(MON_RsDefects& theRsMonitor, MON_OptDefects* theOptMonitorPtr) 
{
    uint32 count = 0, countOpt = 0;
    bool state = false, stateOpt = false;

    // Read the Pii LOS defect from the monitor
    // The myLOSdefect can be retrieved from both OPT layer or RS layer. 
    // The priority of OPT layer LOS is higher than RS layer LOS.
    theRsMonitor.GetDefectStatus(CT_TEL_PII_RS_LOS_DEFECT, &count, &state);
    if (theOptMonitorPtr) 
        theOptMonitorPtr->GetDefectStatus(CT_TEL_PII_OPT_LOSS_LIGHT_DEFECT, &countOpt, &stateOpt);

    if ( !theOptMonitorPtr || 
         (state && !stateOpt) ) 
        myLOSdefect.Update(state, count);
    else
        myLOSdefect.Update(stateOpt, countOpt);

    // Read the SEF defect from the monitor
    theRsMonitor.GetDefectStatus(CT_TEL_RS_OOF_DEFECT, &count, &state);
        mySEFdefect.Update(state, count);
    // Read the LOF defect from the monitor
    theRsMonitor.GetDefectStatus(CT_TEL_RS_LOF_DEFECT, &count, &state);
        myLOFdefect.Update(state, count);
    // Read the TIM defect from the monitor
    theRsMonitor.GetDefectStatus(CT_TEL_RS_TIM_DEFECT, &count, &state);
        myTIMdefect.Update(state, count);

}

void PM_BbDefectData::Update(MON_OptDefects* theOptMonitor, 
                             MON_OptDefects* theOptMonitorProtect,
                             bool theProtectSelected)

{
    uint32 count = 0;
    bool state = false;

    // Read the LOS defect from the monitor 
    // This is also the working facility monitor for protection pair case
    if (theOptMonitor) 
    {
        theOptMonitor->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &count, &state);
        myLOSdefect.Update(state, count);
    }

    // Read the LOS defect from the protect facility monitor, if applicable
    if (theOptMonitorProtect) 
    {
        theOptMonitorProtect->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &count, &state);
        myLOSdefectProtect.Update(state, count);
    }

    myProtectSelected = theProtectSelected;
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E028E
ostream& PM_BbDefectData::WriteObject( ostream& theStream )
{
    return theStream << myLOFdefect
                     << myLOSdefect
                     << myLOSdefectProtect
                     << mySEFdefect
                     << myTIMdefect
                     << FC_InsertVar(myProtectSelected);

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6E02A1
istream& PM_BbDefectData::ReadObject( istream& theStream )
{
    return theStream >> myLOFdefect
                     >> myLOSdefect
                     >> myLOSdefectProtect
                     >> mySEFdefect
                     >> myTIMdefect
                     >> FC_ExtractVar(myProtectSelected);

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F120151
void PM_BbDefectData::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
