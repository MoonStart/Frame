//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_AppIf.h"
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <CsPii/CSPII_CardIF.h>
#include <Blackboard/FC_BbTagGeneric.h>
#include <T6100_TelecomIf.h>
#include "../CFG_HwRefreshAction.h"
#include "../CFG_OptAutoRateLock.h"
#include "../CFG_OptAutomaticAction.h"
#include "../CFG_OduAutomaticAction.h"
#include "../CFG_RsAutomaticAction.h"
#include "../CFG_GfpAutomaticAction.h"
#include "../CFG_OtsOchOHAutomaticAction.h"
#include <Monitoring/MON_SubNodeParameters.h>


//##ModelId=3C3B463E0342
CFG_AppIf::CFG_AppIf(T6100_TelecomIf& theContext):
    TEL_AppIf(theContext)
{}

//##ModelId=3C3B463E0343
CFG_AppIf::~CFG_AppIf()
{}

//##ModelId=3C3B463E0345
CFG_Region*    CFG_AppIf::GetCfgRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetAutomaticCfgRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetOutputCfgRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetProtCfgRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetHistoryCfgRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetAltConfigRegion()  { return NULL;}

CFG_Region*    CFG_AppIf::GetCriticalCfgRegion()  { return NULL;}


CFG_OptAutoRateLockRegion* CFG_AppIf::GetAutoRateLockRegion() { return NULL;}

CFG_OptAutomaticAction* CFG_AppIf::GetAutomaticAutomaticAction() { return NULL;}
CFG_OduAutomaticAction* CFG_AppIf::GetOduAutomaticAction()       { return NULL;}
CFG_RsAutomaticAction*  CFG_AppIf::GetRsAutomaticAction()        { return NULL;}
CFG_GfpAutomaticAction* CFG_AppIf::GetGfpAutomaticAction()       { return NULL;}
CFG_OtsOchOHAutomaticAction* CFG_AppIf::GetOtsOchOHAutomaticAction()   { return NULL;}
//implemented in sub application
CFG_HoldOffTimer*       CFG_AppIf::GetHoldOffTimer(uint32 theInstance) { return NULL;}
CFG_HoldOffTimer*       CFG_AppIf::GetAltHoldOffTimer(uint32 theInstance) { return NULL;}
void CFG_AppIf::WakeUpNextRun() {return;}


void CFG_AppIf::DoInitWarm(FC_Object* theObject)
{
    // Same thing as DoInitCold()
    DoInitCold(theObject);
}

void CFG_AppIf::DoInitCold(FC_Object* theObject)
{
    // Must reset and invalidate all the regions.
    CFG_Region* aRegionPtr=NULL;

    aRegionPtr = GetCfgRegion();
    if (aRegionPtr)
    {
        aRegionPtr->SetForceInvalidFlag(true);
        aRegionPtr->Reset();

        // if region is not own locally, make is persistant
        if (aRegionPtr->GetOwner()==NULL)
            FC_INSTALL_TAG(FC_PERSISTENT_TAG, *aRegionPtr);

    }

    aRegionPtr = GetAltConfigRegion();
    if (aRegionPtr)
    {
        aRegionPtr->SetForceInvalidFlag(true);
        aRegionPtr->Reset();

        // if region is not own locally, make is persistant
        if (aRegionPtr->GetOwner()==NULL)
            FC_INSTALL_TAG(FC_PERSISTENT_TAG, *aRegionPtr);

    }

    aRegionPtr = GetCriticalCfgRegion();
    if (aRegionPtr)
    {
        aRegionPtr->SetForceInvalidFlag(true);
        aRegionPtr->Reset();

        // if region is not own locally, make is persistant
        if (aRegionPtr->GetOwner()==NULL)
            FC_INSTALL_TAG(FC_PERSISTENT_TAG, *aRegionPtr);

    }

    aRegionPtr = GetAutomaticCfgRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }

    aRegionPtr = GetOutputCfgRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }
}

void CFG_AppIf::DoInitConfig(FC_Object* theObject)
{
    // Same thing as DoInitCold()
    DoInitCold(theObject);
}

void CFG_AppIf::Display(FC_Stream& theStream, uint16 theObjectIndex)
{
    CFG_Region* aCfgRegion = GetCfgRegion();
    CFG_Region* aAutoRegion = GetAutomaticCfgRegion();
    CFG_Region* aProtRegion = GetProtCfgRegion();
    CFG_Region* aHistRegion = GetHistoryCfgRegion();
    CFG_Region* aAltConfigRegion = GetAltConfigRegion();
    CFG_Region* aCritConfigRegion = GetCriticalCfgRegion();

    uint32 aCfgRegionSize = 0;
    uint32 aAutoRegionSize = 0;
    uint32 aProtRegionSize = 0;
    uint32 aHistRegionSize = 0;
    uint32 aAltConfigRegionSize = 0;
    uint32 aCritConfigRegionSize = 0;
    uint32 anIndex = 0;
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    if (aCfgRegion)
    {
        aCfgRegionSize = aCfgRegion->Size();
        if (theObjectIndex < aCfgRegionSize )
        {
            anIndex = theObjectIndex;
            aCfgRegionSize  = theObjectIndex + 1;
        }
        else if (aCfgRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aCfgRegionSize  = 0;
            fc_cout << "Valid Index required for Config Region." << endl;
        }
    }

    if (aAutoRegion)
    {
        aAutoRegionSize = aAutoRegion->Size();
        if (theObjectIndex < aAutoRegionSize )
        {
            anIndex = theObjectIndex;
            aAutoRegionSize  = theObjectIndex + 1;
        }
        else if (aAutoRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aAutoRegionSize  = 0;
            fc_cout << "Valid Index required for Automatic Region." << endl;
        }
    }

    if (aProtRegion)
    {
        aProtRegionSize = aProtRegion->Size();
        if (theObjectIndex < aProtRegionSize )
        {
            anIndex = theObjectIndex;
            aProtRegionSize  = theObjectIndex + 1;
        }
        else if (aProtRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aProtRegionSize  = 0;
            fc_cout << "Valid Index required for Protection Region." << endl;
        }
    }

    if (aHistRegion)
    {
        aHistRegionSize = aHistRegion->Size();
        if (theObjectIndex < aHistRegionSize)
        {
            anIndex = theObjectIndex;
            aHistRegionSize  = theObjectIndex + 1;
        }
        else if (aHistRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aHistRegionSize  = 0;
            fc_cout << "Valid Index required for History Region." << endl;
        }
    }

    if (aAltConfigRegion)
    {
        aAltConfigRegionSize = aAltConfigRegion->Size();
        if (theObjectIndex < aAltConfigRegionSize)
        {
            anIndex = theObjectIndex;
            aAltConfigRegionSize  = theObjectIndex + 1;
        }
        else if (aAltConfigRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aAltConfigRegionSize  = 0;
            fc_cout << "Valid Index required for Alt Config Region." << endl;
        }
    }

    if (aCritConfigRegion)
    {
        aCritConfigRegionSize = aCritConfigRegion->Size();
        if (theObjectIndex < aCritConfigRegionSize)
        {
            anIndex = theObjectIndex;
            aCritConfigRegionSize  = theObjectIndex + 1;
        }
        else if (aCritConfigRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aCritConfigRegionSize  = 0;
            fc_cout << "Valid Index required for Crit Config Region." << endl;
        }
    }

    while ((anIndex < aAutoRegionSize)  ||
           (anIndex < aProtRegionSize)  ||
           (anIndex < aCfgRegionSize)   ||
           (anIndex < aHistRegionSize)  ||
           (anIndex < aAltConfigRegionSize) ||
           (anIndex < aCritConfigRegionSize) )
    {
        if ((aAutoRegionSize > 1) || (aProtRegionSize > 1) || (aCfgRegionSize > 1) || (aHistRegionSize > 1) || (aAltConfigRegionSize > 1) || (aCritConfigRegionSize > 1))
        {
            fc_cout << endl <<"************** Index = " << anIndex << " *****************" << endl << endl;
        }
        if ((aProtRegion) &&
            (anIndex < aProtRegionSize))
        {
            (*aProtRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aAutoRegion) &&
            (anIndex < aAutoRegionSize))
        {
            (*aAutoRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aCfgRegion) &&
            (anIndex < aCfgRegionSize))
        {
            (*aCfgRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aHistRegion) &&
            (anIndex < aHistRegionSize))
        {
            (*aHistRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aAltConfigRegion) &&
            (anIndex < aAltConfigRegionSize))
        {
            (*aAltConfigRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aCritConfigRegion) &&
            (anIndex < aCritConfigRegionSize))
        {
            (*aCritConfigRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        ++anIndex;
    }
}


FC_CmdProcessor::STATUS CFG_AppIf::Set(int argc,char** argv)
{
    FC_CmdProcessor::STATUS aStatus = FC_CmdProcessor::E_SUCCESS;

    if (argc>0 && !strcmp("update", argv[0]))
    {
        if (argc == 2)
            CFG_HwRefreshAction::myEnable = !strcmp("on", argv[1]);
        fc_cout << "Update of monitoring is "
                << (CFG_HwRefreshAction::myEnable ? "enabled.": "disabled.") << endl;
        fc_cout << "update <on|off>" << endl;
        return FC_CmdProcessor::E_SUCCESS;
    } else  if (argc == 0)
    {
        fc_cout << "update <on|off>" << endl;
    }
    else if (argc>0 && !strcmp("help", argv[0]))
    {
        fc_cout << "update <on|off>:   enable/disable CFG_HwRefreshAction" << endl;
        return aStatus;
    }


    bool aAltConfigSet = false;
    // Now check for Alt Config region
    // Might also have to check for argv[0] as well as [1]
    if (argc>1 && !strcmp("altConfig", argv[1]))
    {
        aAltConfigSet = true;
    }

    bool aCritConfigSet = false;
    // Now check for Crit Config region
    // Might also have to check for argv[0] as well as [1]
    if (argc>1 && !strcmp("critConfig", argv[1]))
    {
        aCritConfigSet = true;
    }

    CFG_Region* theRegion = NULL;
    if (aAltConfigSet)
    {
        theRegion = GetAltConfigRegion();
    }
    else if (aCritConfigSet)
    {
        theRegion = GetCriticalCfgRegion();
    }
    else
    {
        theRegion = GetCfgRegion();
    }
    if(theRegion)
    {
        // check if region index was provided
        uint32 anIndex=0;
        if (theRegion->Size() > 1)
        {
            if (argc > 0 )
            {
                char* endPtr;
                anIndex = strtoul(argv[0], &endPtr, 0);
                if (*endPtr!=0)
                {
                    fc_cout << "expecting index --> set <index> params..." << endl;
                    return FC_CmdProcessor::E_FAILURE;
                }
                argc--;
                argv++;
            }
        }

        FC_THROW_ERROR_IF (anIndex >= theRegion->Size(),
                           FC_ArgumentOutOfRangeError,
                           "Not that many objects in this region");

        // if AltConfigRegion, then update argv/argc
        if (aAltConfigSet)
        {
            argc--;
            argv++;
        }
        if (aCritConfigSet)
        {
            argc--;
            argv++;
        }
        aStatus = (*theRegion)[(bbindex_t)anIndex].Set(argc,argv);
        theRegion->IncModificationCounter();
        theRegion->UpdateNotify();

    }
    return aStatus;
}


FC_CmdProcessor::STATUS CFG_AppIf::Debug(int argc,char** argv)
{
    FC_CmdProcessor::STATUS aStatus = FC_CmdProcessor::E_SUCCESS;


    CFG_Region* theRegion = GetCfgRegion();
    if(theRegion)
    {
        // check if region index was provided
        uint32 anIndex=0;
        if (theRegion->Size() > 1)
        {
            if (argc > 0 )
            {
                char* endPtr;
                anIndex = strtoul(argv[0], &endPtr, 0);
                if (*endPtr!=0)
                {
                    fc_cout << "expecting index --> debug <index> params..." << endl;
                    return FC_CmdProcessor::E_FAILURE;
                }
                argc--;
                argv++;
            }
        }

        FC_THROW_ERROR_IF (anIndex >= theRegion->Size(),
                           FC_ArgumentOutOfRangeError,
                           "Not that many objects in this region");

        CFG_OptAutomaticAction* anAction = GetAutomaticAutomaticAction();
        if (anAction)
        {
            aStatus = (*anAction).Debug(argc,argv);
        }
        else
        {
            // Try Odu
            CFG_OduAutomaticAction* anAction = GetOduAutomaticAction();
            if (anAction)
            {
                aStatus = (*anAction).Debug(argc,argv);
            }
            else
            {
                // Try Rs
                CFG_RsAutomaticAction* anAction = GetRsAutomaticAction();
                if (anAction)
                {
                    aStatus = (*anAction).Debug(argc,argv);
                }
                else
                {
                    // Try Gfp
                    CFG_GfpAutomaticAction* anAction = GetGfpAutomaticAction();
                    if (anAction)
                    {
                        aStatus = (*anAction).Debug(argc,argv);
                    }
                    else
                    {
                        CFG_OtsOchOHAutomaticAction* anAction = GetOtsOchOHAutomaticAction();
                        if (anAction)
                        {
                            aStatus = (*anAction).Debug(argc,argv);
                        }
                        else
                        {
                            fc_cout << "Automatic Action not present for this valid context" << endl;
                            return FC_CmdProcessor::E_FAILURE;
                        } // for OTS
                    } // for Gfp
                } // for Rs
            } // for Odu
        } // for Opt

    }  // if(theRegion)
    return aStatus;
}


void CFG_AppIf::Reset(void)
{
    CFG_Region* aCfgRegion = GetCfgRegion();
    CFG_Region* aAutoRegion = GetAutomaticCfgRegion();
    CFG_Region* aProtRegion = GetProtCfgRegion();
    CFG_Region* aHistRegion = GetHistoryCfgRegion();
    CFG_Region* aAltConfigRegion = GetAltConfigRegion();
    CFG_Region* aCritConfigRegion = GetCriticalCfgRegion();
    uint32 aCfgRegionSize = 0;
    uint32 aAutoRegionSize = 0;
    uint32 aProtRegionSize = 0;
    uint32 aHistRegionSize = 0;
    uint32 aAltConfigRegionSize = 0;
    uint32 aCritConfigRegionSize = 0;
    uint32 anIndex = 0;

    if (aCfgRegion)
    {
        aCfgRegionSize = aCfgRegion->Size();
    }
    if (aAutoRegion)
    {
        aAutoRegionSize = aAutoRegion->Size();
    }
    if (aProtRegion)
    {
        aProtRegionSize = aProtRegion->Size();
    }
    if (aHistRegion)
    {
        aHistRegionSize = aHistRegion->Size();
    }
    if (aAltConfigRegion)
    {
        aAltConfigRegionSize = aAltConfigRegion->Size();
    }
    if (aCritConfigRegion)
    {
        aCritConfigRegionSize = aCritConfigRegion->Size();
    }

    while ((anIndex < aAutoRegionSize)  ||
           (anIndex < aProtRegionSize)  ||
           (anIndex < aCfgRegionSize)   ||
           (anIndex < aHistRegionSize)  ||
           (anIndex < aAltConfigRegionSize) ||
           (anIndex < aCritConfigRegionSize) )
    {
        if ((aCritConfigRegion) &&
            (anIndex < aCritConfigRegionSize))
        {
            (*aCritConfigRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aAltConfigRegion) &&
            (anIndex < aAltConfigRegionSize))
        {
            (*aAltConfigRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aHistRegion) &&
            (anIndex < aHistRegionSize))
        {
            (*aHistRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aProtRegion) &&
            (anIndex < aProtRegionSize))
        {
            (*aProtRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aAutoRegion) &&
            (anIndex < aAutoRegionSize))
        {
            (*aAutoRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aCfgRegion) &&
            (anIndex < aCfgRegionSize))
        {
            (*aCfgRegion)[(bbindex_t)anIndex].Reset();
        }
        ++anIndex;
    }
    if (aCfgRegion)
    {
        aCfgRegion->IncModificationCounter();
        aCfgRegion->UpdateNotify();
    }
    if (aAutoRegion)
    {
        aAutoRegion->IncModificationCounter();
        aAutoRegion->UpdateNotify();
    }
    if (aProtRegion)
    {
        aProtRegion->IncModificationCounter();
        aProtRegion->UpdateNotify();
    }
    if (aHistRegion)
    {
        aHistRegion->IncModificationCounter();
        aHistRegion->UpdateNotify();
    }
    if (aAltConfigRegion)
    {
        aAltConfigRegion->IncModificationCounter();
        aAltConfigRegion->UpdateNotify();
    }
    if (aCritConfigRegion)
    {
        aCritConfigRegion->IncModificationCounter();
        aCritConfigRegion->UpdateNotify();
    }
}
