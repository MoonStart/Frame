/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  Telecom Services - SPM8560 application
 TARGET   :  Platform independent
 AUTHOR   :  Telecom Services
 DESCRIPTION:
	Header file for SPM8560 Application class.
--------------------------------------------------------------------------*/

#ifndef SPM8560_APPLICATION_H
#define SPM8560_APPLICATION_H

#include <Controller_AppIf.h>
#include <CommonTypes/CT_CardInventory.h>


class Nm_ApplicationSpm8560;
class Nm_ApplicationDpm;
class SD_ManageCardTypeAction;
class Nm_MainApplication;
class DEV_ShellTestMenu;
class CLIApp;
class CSPII_BspTestMenuSpm;
class CPIF_TLim_cp_PipeApp;
class CPIF_Callback_PipeApp;
class CPIF_agccp_PipeApp;
class CPIF_dbwrapper_PipeApp;
class CPIF_RtrvAllTpPerFac_PipeApp;
class PMXferTaskCc;

//----------------------------------------------------------------------------
/** 
	This shall contain the Software Management required 
	functionnality for the SPM8560 card.
*///----------------------------------------------------------------------------
//##ModelId=37FBAFEA0090
class SPM8560_Application	: public Controller_AppIf
{

public:
    /**
    Default class constructor. 
    */
    //##ModelId=37FBAFEA0113
    SPM8560_Application();

    /**
    Default class desctructor.
    */
    //##ModelId=37FBAFEA0112
    ~SPM8560_Application();

    /**
    SPM8560 pre-initialization, to be defined by Telecom Services.

    @param theObject
    Generic parameter to be passed to the CreateRegions. By default this 
    parameter is set to NULL.
    */
    //##ModelId=37FBAFEA00F4
    virtual void DoCreateRegions(FC_Object* theObject);
    virtual void DoCreateActions( FC_Object* theObject = 0 );
    virtual void DoDeactivateActions(FC_Object* theObject = 0);

    /** At shutdown, the main application must ensure resources are not leaked. */
    virtual void DoDeleteRegions(FC_Object* theObject = 0);
    virtual void DoDeleteActions( FC_Object* theObject = 0 );    

    virtual void CreateSpecificDiagApps(void);
    virtual void CreateSpecificCudApps(void);
    virtual void CreateSpecificTsPiiApps(void);
    virtual void CreateSpecificNmApps(void);

    virtual void Restart(RESTART_TYPE theRestartType);

    // Initialization of Heap Memory Manager
    virtual void InitHeapMemMgr(void);


private:
    //----------------------------------------------------------------------------
    // Common application interface pointers
    //----------------------------------------------------------------------------
    Nm_ApplicationSpm8560*         mySpmNmApp;
    Nm_ApplicationDpm*             myDpmNmApp;
    Nm_MainApplication*            myNmMainApp;
    DEV_ShellTestMenu*             myDevTestMenu;
    CLIApp*                        myCliApp;

    CSPII_BspTestMenuSpm*          myBspTestMenu;

    CPIF_TLim_cp_PipeApp*          myTlimCpPipeApp;
    CPIF_Callback_PipeApp*         myCpifCallbackPipeApp;
    CPIF_agccp_PipeApp*            myCpifAgccpPipeApp;
    CPIF_dbwrapper_PipeApp*        myCpifDbwrapperPipeApp;
    CPIF_RtrvAllTpPerFac_PipeApp*  myCpifRtrvAllTpPerFacPipeApp;

    SD_ManageCardTypeAction* myManageCardTypeAction;

    PMXferTaskCc *                 myPMXferTask;

    //----------------------------------------------------------------------------
    // Internal methods for context creation according to the sub-node 
    // configuration
    //----------------------------------------------------------------------------
};


#endif //SPM8560_APPLICATION_H
