/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Performance Monitoring Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMDOMAIN_H__
#define __TL1_PMDOMAIN_H__

class TL1_Response;
class CT_TL1_PmArg;
class CT_TL1_StatsArg;
class CT_PM_Ftp;

/**
   CLASS TL1_PmDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of PM related TL1 commands, that a TL1 Entities
   for a PM is expected to implement. This class contains no
   data member nor any default implementation.
 */

// Not completetely defined for AP100, to be updated later.

class TL1_PmDomain
{
public:

    virtual void AlwPmRept(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse){};

    virtual void InhPmReport(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void InitReg(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void RtrvPm(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void RtrvPmMode(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void RtrvPmSched(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void RtrvTca(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void RtrvTcaMode(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void RtrvTh(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void SchedPmRept(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void SetPmMode(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse){};

    virtual void SetTcaMode(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void SetTh(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void AlwPmFile(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void InhPmFile(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void RtrvPmFileSched(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse)const {};

    virtual void SchedPmFile(CT_TL1_PmArg& theArg,
		TL1_Response& theResponse) {};

    virtual void InitStats(CT_TL1_StatsArg& theArg,
		TL1_Response& theResponse) {};

    virtual void RtrvStats(CT_TL1_StatsArg& theArg,
		TL1_Response& theResponse) {};
};

#endif
