//Copyright(c) Tellabs Transport Group. All rights reserved

#include <Monitoring/MON_AppIf.h>
#include <ErrorService/FC_Error.h>
#include <Facade/FC_FacadeApp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Blackboard/FC_BbTagGeneric.h>
#include <T6100_CardIf.h>
#include "../MON_UpdateStatusAction.h"
#include "../MON_SubNodeParameters.h"
#include "../MON_UpdateStatusAction.h"

//##ModelId=3C3B53140190
MON_AppIf::MON_AppIf(T6100_TelecomIf& theContext):
    TEL_AppIf(theContext)
{}

//##ModelId=3C3B53140191
MON_AppIf::~MON_AppIf()
{}

//##ModelId=3C3B5314019A
MON_Region*   MON_AppIf::GetDefectsRegion()  { return NULL;}
//##ModelId=3C3B531401A3
MON_Region*   MON_AppIf::GetStatusRegion()   { return NULL;}
//##ModelId=3C3B531401A5
MON_Region*   MON_AppIf::GetCountersRegion() { return NULL;}
//##ModelId=3C3B531401AD
MON_Region*   MON_AppIf::GetConfigRegion()   { return NULL;}
//
MON_Region*   MON_AppIf::GetProtConfigRegion()   { return NULL;}

//##ModelId=3C7170F70270
MON_Region*   MON_AppIf::GetRequestRegion()  { return NULL;}
//##ModelId=3C7170F70285
MON_Region*   MON_AppIf::GetResultRegion()   { return NULL;}

MON_Region*   MON_AppIf::GetAltRequestRegion()  { return NULL;}
MON_Region*   MON_AppIf::GetAltResultRegion()   { return NULL;}

MON_UpdateStatusAction* MON_AppIf::GetUpdateStatusAction() { return NULL;}

void MON_AppIf::DoInitWarm(FC_Object* theObject)
{
    // Same thing as DoInitCold()
    DoInitCold(theObject);
}

void MON_AppIf::DoInitCold(FC_Object* theObject)
{
    // Must reset and invalidate all the regions.
    MON_Region* aRegionPtr=NULL;

    aRegionPtr = GetDefectsRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }

    aRegionPtr = GetStatusRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }
    aRegionPtr = GetCountersRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }
    aRegionPtr = GetConfigRegion();
    if (aRegionPtr)
    {
        aRegionPtr->SetForceInvalidFlag(true);
        aRegionPtr->Reset();

        // if region is not own locally, make is persistant
        if (aRegionPtr->GetOwner()==NULL)
            FC_INSTALL_TAG(FC_PERSISTENT_TAG, *aRegionPtr);

    }
    aRegionPtr = GetProtConfigRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }
    aRegionPtr = GetRequestRegion();
    if (aRegionPtr)
    {
        aRegionPtr->SetForceInvalidFlag(true);
        aRegionPtr->Reset();
    }

    aRegionPtr = GetResultRegion();
    if (aRegionPtr)
    {
        aRegionPtr->Reset();
        aRegionPtr->SetForceInvalidFlag(true);
    }
}

void MON_AppIf::DoInitConfig(FC_Object* theObject)
{
    // Same thing as DoInitCold()
    DoInitCold(theObject);
}

void MON_AppIf::Display(FC_Stream& theStream, uint16 theObjectIndex)
{
    MON_Region* aConfigRegion = GetConfigRegion();
    MON_Region* aProtConfigRegion = GetProtConfigRegion();
    MON_Region* aDefectsRegion = GetDefectsRegion();
    MON_Region* aStatusRegion = GetStatusRegion();
    MON_Region* aCountersRegion = GetCountersRegion();
    MON_Region* aRequestRegion = GetRequestRegion();
    MON_Region* aResultRegion = GetResultRegion();
    uint32 aConfigRegionSize = 0;
    uint32 aProtConfigRegionSize = 0;
    uint32 aDefectsRegionSize = 0;
    uint32 aStatusRegionSize = 0;
    uint32 aCountersRegionSize = 0;
    uint32 aRequestRegionSize = 0;
    uint32 aResultRegionSize = 0;
    uint32 anIndex = 0;
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();
    char outBuf[32];

    if (aConfigRegion)
    {
        aConfigRegionSize = aConfigRegion->Size();
        if (theObjectIndex < aConfigRegionSize )
        {
            anIndex = theObjectIndex;
            aConfigRegionSize  = theObjectIndex + 1;
        }
        else if (aConfigRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aConfigRegionSize  = 0;
            fc_cout << "Valid Index required for Config Region." << endl;
        }
    }

    if (aProtConfigRegion)
    {
        aProtConfigRegionSize = aProtConfigRegion->Size();
        if (theObjectIndex < aProtConfigRegionSize )
        {
            anIndex = theObjectIndex;
            aProtConfigRegionSize  = theObjectIndex + 1;
        }
        else if (aProtConfigRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aProtConfigRegionSize  = 0;
            fc_cout << "Valid Index required for Config Region." << endl;
        }
    }

    if (aDefectsRegion)
    {
        aDefectsRegionSize = aDefectsRegion->Size();
        if (theObjectIndex < aDefectsRegionSize )
        {
            anIndex = theObjectIndex;
            aDefectsRegionSize  = theObjectIndex + 1;
        }
        else if (aDefectsRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aDefectsRegionSize  = 0;
            fc_cout << "Valid Index required for Defects Region." << endl;
        }
    }

    if (aStatusRegion)
    {
        aStatusRegionSize = aStatusRegion->Size();
        if (theObjectIndex < aStatusRegionSize )
        {
            anIndex = theObjectIndex;
            aStatusRegionSize  = theObjectIndex + 1;
        }
        else if (aStatusRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aStatusRegionSize  = 0;
            fc_cout << "Valid Index required for Status Region." << endl;
        }
    }

    if (aCountersRegion)
    {
        aCountersRegionSize = aCountersRegion->Size();
        if (theObjectIndex < aCountersRegionSize )
        {
            anIndex = theObjectIndex;
            aCountersRegionSize  = theObjectIndex + 1;
        }
        else if (aCountersRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aCountersRegionSize  = 0;
            fc_cout << "Valid Index required for Counters Region." << endl;
        }
    }

    if (aRequestRegion)
    {
        aRequestRegionSize = aRequestRegion->Size();
        if (theObjectIndex < aRequestRegionSize )
        {
            anIndex = theObjectIndex;
            aRequestRegionSize  = theObjectIndex + 1;
        }
        else if (aRequestRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aRequestRegionSize  = 0;
            fc_cout << "Valid Index required for Request Region." << endl;
        }
    }

    if (aResultRegion)
    {
        aResultRegionSize = aResultRegion->Size();
        if (theObjectIndex < aResultRegionSize )
        {
            anIndex = theObjectIndex;
            aResultRegionSize  = theObjectIndex + 1;
        }
        else if (aResultRegionSize > omsWavelengthCapacity)
        {
            // When the object index is greater or equal to the region size (from the if statement above)
            // and the region size is large (currently 32 in the else if statement), then do not print
            // any objects and give a nice error meesage to boot.
            anIndex = 0;
            aResultRegionSize  = 0;
            fc_cout << "Valid Index required for Result Region." << endl;
        }
    }



    while ((anIndex < aConfigRegionSize) ||
           (anIndex < aDefectsRegionSize) ||
           (anIndex < aStatusRegionSize) ||
           (anIndex < aCountersRegionSize) ||
           (anIndex < aRequestRegionSize) ||
           (anIndex < aResultRegionSize))
    {
        if ((aConfigRegionSize > 1) || (aDefectsRegionSize > 1) || (aStatusRegionSize > 1) ||
            (aCountersRegionSize > 1) || (aRequestRegionSize > 1) || (aResultRegionSize > 1))
        {
            fc_cout << endl <<"************** Index = " << anIndex << " *****************" << endl << endl;
        }
        if ((aConfigRegion) && (anIndex < aConfigRegionSize))
        {
            theStream << "------------------=== CONFIG ===------------------" << endl;
            (*aConfigRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aProtConfigRegion) && (anIndex < aProtConfigRegionSize))
        {
            theStream << "----------------=== PROT CONFIG ===---------------" << endl;
            (*aProtConfigRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aDefectsRegion) && (anIndex < aDefectsRegionSize))
        {
            theStream << "------------------=== DEFECTS ===-----------------" << endl;
            (*aDefectsRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aStatusRegion) && (anIndex < aStatusRegionSize))
        {
            theStream << "------------------=== STATUS ==="; 
            sprintf(outBuf, "-----%11d -----", aStatusRegion->GetModificationCounter()); 
            theStream << outBuf << endl;
            (*aStatusRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aCountersRegion) && (anIndex < aCountersRegionSize))
        {
            theStream << "-----------------=== COUNTERS ===-----------------" << endl;
            (*aCountersRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aRequestRegion) && (anIndex < aRequestRegionSize))
        {
            theStream << "------------------=== REQUEST ===-----------------" << endl;
            (*aRequestRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        if ((aResultRegion) && (anIndex < aResultRegionSize))
        {
            theStream << "------------------=== RESULT ===------------------" << endl;
            (*aResultRegion)[(bbindex_t)anIndex].Display(theStream);
        }
        ++anIndex;
    }
}

FC_CmdProcessor::STATUS MON_AppIf::Set(int argc,char** argv)
{
    FC_CmdProcessor::STATUS aStatus = FC_CmdProcessor::E_SUCCESS;

    if (argc>0 && !strcmp("update", argv[0]))
    {
        if (argc == 2)
            MON_UpdateStatusAction::myEnable = !strcmp("on", argv[1]);
        fc_cout << "Update of monitoring is "
                << (MON_UpdateStatusAction::myEnable ? "enabled.": "disabled.") << endl;
        fc_cout << "update <on|off>" << endl;
        return FC_CmdProcessor::E_SUCCESS;
    } else  if (argc == 0)
    {
        fc_cout << "update <on|off>" << endl;
    }

    bool aProtConfigSet = false;
    // Now check for Prot Config region
    // Might also have to check for argv[0] as well as [1]
    if (argc>1 && !strcmp("protConfig", argv[1]))
    {
        aProtConfigSet = true;
    }

    MON_Region* theRegion = NULL;
    if (aProtConfigSet)
    {
        theRegion = GetProtConfigRegion();
    }
    else
    {
        theRegion = GetConfigRegion();
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
                    fc_cout << "To access och config object commands:" << endl;
                    fc_cout << "    mon set <path>/<index> <command|help> <params>" << endl;
                    return FC_CmdProcessor::E_FAILURE;
                }
                argc--;
                argv++;
            }
        }

        FC_THROW_ERROR_IF (anIndex >= theRegion->Size(),
                           FC_ArgumentOutOfRangeError,
                           "Not that many objects in this region");

        aStatus = (*theRegion)[(bbindex_t)anIndex].Set(argc,argv);
        theRegion->IncModificationCounter();
        theRegion->UpdateNotify();

    }
    return aStatus;
}


FC_CmdProcessor::STATUS MON_AppIf::Debug(int argc,char** argv)
{
    FC_CmdProcessor::STATUS aStatus = FC_CmdProcessor::E_SUCCESS;

    MON_Region* theRegion = GetConfigRegion();
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
                    fc_cout << "To access och config object commands:" << endl;
                    fc_cout << "    mon set <path>/<index> <command|help> <params>" << endl;
                    return FC_CmdProcessor::E_FAILURE;
                }
                argc--;
                argv++;
            }
        }

        FC_THROW_ERROR_IF (anIndex >= theRegion->Size(),
                           FC_ArgumentOutOfRangeError,
                           "Not that many objects in this region");

        // Put new code here?
        // aStatus = (*theRegion)[anIndex].Debug(argc,argv);

    }
    return aStatus;
}


void MON_AppIf::Reset()
{
    MON_Region* aConfigRegion = GetConfigRegion();
    MON_Region* aProtConfigRegion = GetProtConfigRegion();
    MON_Region* aDefectsRegion = GetDefectsRegion();
    MON_Region* aStatusRegion = GetStatusRegion();
    MON_Region* aCountersRegion = GetCountersRegion();
    MON_Region* aRequestRegion = GetRequestRegion();
    MON_Region* aResultRegion = GetResultRegion();
    uint32 aConfigRegionSize = 0;
    uint32 aProtConfigRegionSize = 0;
    uint32 aDefectsRegionSize = 0;
    uint32 aStatusRegionSize = 0;
    uint32 aCountersRegionSize = 0;
    uint32 aRequestRegionSize = 0;
    uint32 aResultRegionSize = 0;
    uint32 anIndex = 0;

    if (aConfigRegion)
    {
        aConfigRegionSize = aConfigRegion->Size();
    }
    if (aProtConfigRegion)
    {
        aProtConfigRegionSize = aProtConfigRegion->Size();
    }
    if (aDefectsRegion)
    {
        aDefectsRegionSize = aDefectsRegion->Size();
    }
    if (aStatusRegion)
    {
        aStatusRegionSize = aStatusRegion->Size();
    }
    if (aCountersRegion)
    {
        aCountersRegionSize = aCountersRegion->Size();
    }
    if (aRequestRegion)
    {
        aRequestRegionSize = aRequestRegion->Size();
    }
    if (aResultRegion)
    {
        aResultRegionSize = aResultRegion->Size();
    }

    while ((anIndex < aConfigRegionSize) ||
           (anIndex < aProtConfigRegionSize) ||
           (anIndex < aDefectsRegionSize) ||
           (anIndex < aStatusRegionSize) ||
           (anIndex < aCountersRegionSize) ||
           (anIndex < aRequestRegionSize) ||
           (anIndex < aResultRegionSize))
    {
        if ((aConfigRegion) && (anIndex < aConfigRegionSize))
        {
            (*aConfigRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aProtConfigRegion) && (anIndex < aProtConfigRegionSize))
        {
            (*aProtConfigRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aDefectsRegion) && (anIndex < aDefectsRegionSize))
        {
            (*aDefectsRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aStatusRegion) && (anIndex < aStatusRegionSize))
        {
            (*aStatusRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aCountersRegion) && (anIndex < aCountersRegionSize))
        {
            (*aCountersRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aRequestRegion) && (anIndex < aRequestRegionSize))
        {
            (*aRequestRegion)[(bbindex_t)anIndex].Reset();
        }
        if ((aResultRegion) && (anIndex < aResultRegionSize))
        {
            (*aResultRegion)[(bbindex_t)anIndex].Reset();
        }
        ++anIndex;
    }

    if (aConfigRegion)
    {
        aConfigRegion->IncModificationCounter();
        aConfigRegion->UpdateNotify();
    }
    if (aProtConfigRegion)
    {
        aProtConfigRegion->IncModificationCounter();
        aProtConfigRegion->UpdateNotify();
    }
    if (aDefectsRegion)
    {
        aDefectsRegion->IncModificationCounter();
        aDefectsRegion->UpdateNotify();
    }
    if (aStatusRegion)
    {
        aStatusRegion->IncModificationCounter();
        aStatusRegion->UpdateNotify();
    }
    if (aCountersRegion)
    {
        aCountersRegion->IncModificationCounter();
        aCountersRegion->UpdateNotify();
    }
    if (aRequestRegion)
    {
        aRequestRegion->IncModificationCounter();
        aRequestRegion->UpdateNotify();
    }
    if (aResultRegion)
    {
        aResultRegion->IncModificationCounter();
        aResultRegion->UpdateNotify();
    }
}
