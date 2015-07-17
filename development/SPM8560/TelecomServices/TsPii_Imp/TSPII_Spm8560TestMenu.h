#ifndef TSPII_SPM8560TESTMENU_H
#define TSPII_SPM8560TESTMENU_H
/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TSPII Services
TARGET:         SPM8560
AUTHOR:         Anoop Mathew
DESCRIPTION:    Test menu class for TSPII on SPM8560
-----------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_OscCommonTestMenu.h"
#include "TsPii_Imp/TSPII_TestMenu.h"
#include "TsPii_Imp/TSPII_ShelfTestMenu.h"
#include "ExecutionSupport/FC_Action.h"
#include "CsPii/CSPII_ShelfIF.h"

class FC_PeriodicProcess;
class TSPII_Spm8560TestMapperAction;

#define TSPII_SPM8560_NB_STATE_MAPPER_TEST 12

enum TSPII_Spm8560TestMapperState
{
    TEST_IDLE,
    TEST_OTS_PMI,
    TEST_OTS_BDIP,
    TEST_OTS_BDIO,
    TEST_OMS_PMI,
    TEST_OMS_BDIP,
    TEST_OMS_BDIO,
    TEST_OMS_FDIP,
    TEST_OMS_FDIO,
    TEST_OCH_OCI,
    TEST_OCH_FDIP,
    TEST_OCH_FDIO
};

// Test class used by test menu
class TSPII_Spm8560TestMapperAction : public FC_Action
{
public:

   TSPII_Spm8560TestMapperAction();
   ~TSPII_Spm8560TestMapperAction();
   static TSPII_Spm8560TestMapperAction* GetInstance();
   virtual void         Run(FC_Object* theObject = NULL);
   virtual FC_Object *  DoRunWithReason(unsigned theRunReason, FC_Object * theInvokerObj, FC_Object * theParam = NULL);
   inline FC_PeriodicProcess & GetProcess() {return *myMapperTestProcess;}
   void Reset();
   void DisplayResults();
   inline TSPII_Spm8560TestMapperState GetState() {return myState;}

private:

   uint32                          myIterationCount;
   bool                            myIsDualOsc;
   uint32                          myOscIndex;
   uint32                          myOchIndex;
   FC_PeriodicProcess*             myMapperTestProcess;
   bool                            myResultTable[TSPII_MAX_OSC*2][TSPII_SPM8560_NB_STATE_MAPPER_TEST][2][32];
   bool                            myTTIResult[TSPII_MAX_OSC*2];
   static TSPII_Spm8560TestMapperAction* ourInstance;
   TSPII_Spm8560TestMapperState    myState;
};


// global function prototype
class TSPII_Spm8560TestMenu : public TSPII_OscCommonTestMenu, public TSPII_TestMenu, public TSPII_ShelfTestMenu
{
public:

   /* CTOR */                     TSPII_Spm8560TestMenu();
   virtual                        ~TSPII_Spm8560TestMenu();
   static FC_CmdProcessor::STATUS HwDumpOsc(int argc, char** argv);
   static FC_CmdProcessor::STATUS HwRefresh(int argc, char** argv);
   static FC_CmdProcessor::STATUS HwTestMapper(int argc, char** argv);

   //active spm specific test menu commands
   static FC_CmdProcessor::STATUS HwDump    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwPe      (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwPt      (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwAmpOsa  (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwAmm     (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwAmpOlim (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwCopm    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwDcd     (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwOM      (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwTdm     (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwSlave   (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwRcmm    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwRoam    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwDemux   (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwWss     (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwFwStatus(int argc, char** argv);
   static FC_CmdProcessor::STATUS HwSpur    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwStorage (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwVers    (int argc, char** argv);
   static FC_CmdProcessor::STATUS TspiiDrtrDisplay  (int argc, char** argv);
   static FC_CmdProcessor::STATUS TspiiDdltDisplay  (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwNcm     (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwNcmSlave(int argc, char** argv);

protected:

   static const FC_CmdProcessor::CMD_TABLE_STRUCT ourTspiiSpm8560MainMenu[];
   static TSPII_Spm8560TestMapperAction*   myMapperAction;
   static unsigned int            Slot2Tdm(unsigned int theSlot);
   static unsigned int            Tdm2Slot(unsigned int theTdm);

private:

    static void                   DisplayMatrixDataRecord(char *prefix, MatrixDataRecord *mdr);
   static char *                  Uint8ToHexASCII(uint8 what, char * where);
};

#endif // TSPII_SPM8560TESTMENU_H
