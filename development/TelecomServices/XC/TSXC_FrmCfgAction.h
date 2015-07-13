// Copyright(c) Tellabs Transport Group. All rights reserved.
#ifndef _INC_TSXC_FRMCFGACTION_INCLUDED
#define _INC_TSXC_FRMCFGACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_FrmCfgRegion.h>

#include <TsPii/TSPII_XcIf.h>

class QRS_ResponseRegion;

//------------------------------------------------------------------------------
// This class is responsible for applying framer cross connects.
//------------------------------------------------------------------------------
class TSXC_FrmCfgAction : public TSXC_BaseAction
{
public:

    TSXC_FrmCfgAction(T6100_CardIf& theCardContext);

    virtual ~TSXC_FrmCfgAction();

    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    void SetFrmCfgRegion(TSXC_FrmCfgRegion<TSXC_Connect>* theFrmCfgRegion);
    void SetDisplayFrmDelete(bool theValue);
    void SetDisplayFrmAdd(bool theValue);

    TSPII_XcType ConnectTypeToTspii(CT_XC_ConnectType connType);

private:
    
    TSXC_FrmCfgRegion<TSXC_Connect>*                        myFrmCfg_Region;

    static bool myDisplayFrmDelete;
    static bool myDisplayFrmAdd;
};

#endif /* _INC_TSXC_FRMCFGACTION_INCLUDED */
