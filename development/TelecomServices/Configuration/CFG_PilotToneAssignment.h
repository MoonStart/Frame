/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_PilotToneAssignment.h
 *    DATE:          07/05/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Pilot Tone Assignment 
 *    OVERVIEW:      Pilot Tone Assignment for 44 channels
 *    FEATURE PACK:  FP3.2
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#ifndef __CFG_PILOTTONEASSIGNMENT_H__
#define __CFG_PILOTTONEASSIGNMENT_H__

#include <gdef.h>
#include <ss_gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Wavelength.h>
#include <Monitoring/MON_Definitions.h>

class CFG_PilotToneAssignment
{
public:
    virtual                             ~CFG_PilotToneAssignment();
    static CFG_PilotToneAssignment &    GetInstance();
    static void                         DeleteInstance();

    void                                Menu(int argc, char ** argv);
    CT_TEL_PilotToneID                  PT_FREQ_TO_OTID(CT_TEL_Hz freq);
    CT_TEL_Hz                           OTID_TO_PT_FREQ(CT_TEL_PilotToneID otid);
    uint8                               OTID_TO_CH_ID(CT_TEL_PilotToneID otid);
    CT_TEL_PilotToneID                  CH_ID_TO_OTID(uint8 chid, MON_RelativeTraceId theRelativeId);
    CT_TEL_Hz                           CH_ID_TO_CENTER_FREQ(uint8 chid);

private:
    /* Constructor */                   CFG_PilotToneAssignment();
    void								Display();
	void 								SetFreq(uint8 ch, CT_TEL_Hz freq);

    static CFG_PilotToneAssignment *    ourInstance;

    uint32                              myFreqToChTableSize;
    uint32                              myNumOfWaveLengths;
};

#endif //__CFG_PILOTTONEASSIGNMENT_H__
