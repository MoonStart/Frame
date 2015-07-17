#ifndef _TSPII_DPMTESTMENU_H
#define _TSPII_DPMTESTMENU_H
/*-----------------------------------------------------------------------------
Copyright(c) Tellabs, Inc. All rights reserved.

SUBSYSTEM:      TSPII Services
TARGET:         DPM
AUTHOR:         Anoop Mathew
DESCRIPTION:    Test menu class for TSPII on DPM
-----------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_TestMenu.h"
#include "CsPii/CSPII_ShelfIF.h"


class TSPII_DpmTestMenu : public TSPII_TestMenu
{
public:
   /* CTOR */                     TSPII_DpmTestMenu();
   virtual                        ~TSPII_DpmTestMenu();

   //Dpm specific test menu commands
   static FC_CmdProcessor::STATUS HwDump    (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwRefresh(int argc, char** argv);
   static FC_CmdProcessor::STATUS TspiiDrtrDisplay  (int argc, char** argv);
   static FC_CmdProcessor::STATUS HwVers    (int argc, char** argv);
   static FC_CmdProcessor::STATUS TspiiDdltDisplay  (int argc, char** argv);

protected:
   static const FC_CmdProcessor::CMD_TABLE_STRUCT ourTspiiDpmMainMenu[];
   
private:
};

#endif // _TSPII_DPMTESTMENU_H
