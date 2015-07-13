/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 19, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Equipment Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMFACADE_H__
#define __TL1_PMFACADE_H__

#include <string>

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#include <Facade/FC_FacadeOper.h>

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __TL1_PMDOMAIN_H__
#include <TL1Core/TL1_PmDomain.h>
#endif

#ifndef __TL1_PMSYSTEMDOMAIN_H__
#include <TL1Core/TL1_PmSysDomain.h>
#endif

#ifndef __TL1_PMOCHDOMAIN_H__
#include <TL1Core/TL1_PmOchDomain.h>
#endif

#ifndef __TL1_PMPROFILEENTITY_H__
#include <TL1Core/TL1_PmProfileEntity.h>
#endif

//forward class definition
class TL1_Response;
class CT_TL1_RtrvPmArg;
class T7100_TL1PmIf;



class TL1_PmFacade 
{
public:

    //Constructor of this class.
    TL1_PmFacade(){};

    //Destructor of this class.
    virtual ~TL1_PmFacade(){};

    virtual void RtrvPm(CT_TL1_PmArg& theArg, TL1_Response& theResponse) = 0;
    virtual void RtrvStats(CT_TL1_StatsArg& theArg, TL1_Response& theResponse) = 0;

};
#if defined WIN32 || defined LINUX
template <> class GetFacadeOperObj<TL1_PmFacade> :
        public FC_FacadeOper<TL1_PmFacade>
#else
//This class Implements the Façade Operation use to retrieve the PM data.
class GetFacadeOperObj<TL1_PmFacade>: public FC_FacadeOper<TL1_PmFacade>
#endif
{
public:
    GetFacadeOperObj(){;};

    virtual ~GetFacadeOperObj(){;};

    virtual void RtrvPm(CT_TL1_PmArg& theArg, TL1_Response& theResponse);
    virtual void RtrvStats(CT_TL1_StatsArg& theArg, TL1_Response& theResponse);

private:

    void RtrvPmAllEquipment(CT_TL1_PmArg& theArg, TL1_Response& theResponse);
    void RtrvPmAllEntity(CT_TL1_PmArg& theArg, TL1_Response& theResponse);
    void RtrvPmAllFacility(CT_TL1_PmArg& theArg, TL1_Response& theResponse);
    void RtrvPmEntity(CT_TL1_PmArg& theArg, TL1_Response& theResponse, bool isTermPt);

    void RtrvPmLongOper(CT_TL1_PmArg& theArg,
                        TL1_Response& theResponse,
                        T7100_TL1PmIf* theEntityPtr,
                        bool isTermPt);

    void RtrvPmLongOperTermPt(CT_TL1_PmArg& theArg,
                        TL1_Response& theResponse,
                        T7100_TL1PmIf* theEntityPtr);

    void RtrvStatsLongOper(CT_TL1_StatsArg& theArg,
                        TL1_Response& theResponse,
                        T7100_TL1PmIf* theEntityPtr);

    enum PM_RequestType
    {
        PM_RequestAllEquipment,
        PM_RequestAllFacility,
        PM_RequestAllEntity,
        PM_RequestEntity
    };

    PM_RequestType GetRequestType(const string& anEntityName);

    class PM_RequestTypeMap;

    friend class PM_RequestTypeMap;

    static PM_RequestTypeMap myRequestTypeMap;
};



#define FACI_AlwPmRept(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, AlwPmRept(theArg, theResponse))

#define FACI_AlwPmFile(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, AlwPmFile(theArg, theResponse))

#define FACI_InhPmReport(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InhPmReport(theArg, theResponse))

#define FACI_InhPmReport(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InhPmReport(theArg, theResponse))

#define FACI_InhPmFile(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InhPmFile(theArg, theResponse))

#define FACI_InitReg(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InitReg(theArg, theResponse))

#define FACI_RtrvPm(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPm(theArg, theResponse))

#define FACI_RtrvPmDay(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPmDay(theArg, theResponse))

#define FACI_RtrvPmMode(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPmMode(theArg, theResponse))

#define FACI_RtrvPmSched(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPmSched(theArg, theResponse))

#define FACI_RtrvPmFileSched(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPmFileSched(theArg, theResponse))

#define FACI_RtrvTca(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTca(theArg, theResponse))

#define FACI_RtrvTcaMode(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTcaMode(theArg, theResponse))

#define FACI_RtrvTh(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTh(theArg, theResponse))

#define FACI_SchedPmRept(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SchedPmRept(theArg, theResponse))

#define FACI_SchedPmFile(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SchedPmFile(theArg, theResponse))

#define FACI_SetOptThOch(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetOptThOch(theArg, theResponse))

#define FACI_SetPmDay(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetPmDay(theArg, theResponse))

#define FACI_SetPmMode(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetPmMode(theArg, theResponse))

#define FACI_SetTcaMode(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetTcaMode(theArg, theResponse))

#define FACI_SetTh(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetTh(theArg, theResponse))

#define FACI_EdPmProfile( theAidType, theProfile, theArg, thePmName, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdPmProfile( theAidType, theProfile, theArg, thePmName,theResponse ))

#define FACI_RtrvPmProfile( theAidType, theProfile, theArg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPmProfile( theAidType, theProfile, theArg, theResponse ))

#define FACI_InitStats(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InitStats(theArg, theResponse))

#define FACI_RtrvStats(theArg, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvStats(theArg, theResponse))

#endif // __TL1_PmFacade_H__
