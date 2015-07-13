// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_TcmAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_Dispatcher.h>

#include "../CFG_AppIf.h"
#include "../CFG_TcmAutomatic.h"
#include "../CFG_Tcm.h"

CFG_TcmAutomaticAction::CFG_TcmAutomaticAction(CFG_AppIf&      theCfgIf,
                                               MON_TcmDefectsRegion&     theIncomingMonRegion,
                                               CT_NumberOfOdus theTcmsOnCard): 
    CFG_HwRefreshAction(theCfgIf),
    myIncomingMonRegion(theIncomingMonRegion),
    myTcmsOnCard(theTcmsOnCard)
{
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->AddInputRegion(&myIncomingMonRegion);

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_TcmAutomaticAction::~CFG_TcmAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->RemoveInputRegion(&myIncomingMonRegion);

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_TcmAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    bool hasChanged = false;    
    uint32 size = (GetCfgIf().GetCfgRegion()->Size() <= myIncomingMonRegion.Size()) ? GetCfgIf().GetCfgRegion()->Size() : myIncomingMonRegion.Size();
    uint32 aLTCCount = 0;
    bool   aLTCDefect = false;

    for (uint32 anIndex = 0; anIndex < size; anIndex++)    
    {        
        bool aForceBDI  = false;     

        CFG_TcmAutomatic& aTcmAutomaticConfig = static_cast<CFG_TcmAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[bbindex_t(anIndex)]);
        CFG_Tcm&          aTcmConfig          = static_cast<CFG_Tcm&>((*GetCfgIf().GetCfgRegion())[bbindex_t(anIndex)]);

        // Is this the correct MON region?
        MON_TcmDefects&   aIncomingDefectsIf  = static_cast<MON_TcmDefects&>(myIncomingMonRegion[bbindex_t(anIndex)]);
        CT_TCM_Mode       aTcmMode = aTcmConfig.GetTcmMode();


        /*BDI can only be inserted back in SRC_SNK and SRC_SNK_NIM mode*/
        if ( (CT_TCM_MODE_SRC_SNK == aTcmMode) || (CT_TCM_MODE_SRC_SNK_NIM == aTcmMode) )
        { 
            // Since NIM mode does set the Lock State, check LayerLocked is not enough
            // Therefore, check if the lock bit mask has been set for the current layer
            // to see it BDI should be sent.  That result will then ORed with the LayerLock.
            uint8 aLockBitMask    = aIncomingDefectsIf.GetLockBitMask();
            uint8 aCheckMask      = 1 << ( (uint8)(aTcmConfig.GetTcmIdentifier().GetTcmLevelEnum() - CT_TCM_Level_UNKNOWN) );
            bool  aMyLayerLocked  = ((aLockBitMask & aCheckMask) != 0);
            aMyLayerLocked       |= aIncomingDefectsIf.IsLayerLocked();

            //BDI is required to be inserted upon detection of dLTC for both LTCACT=ENABLED and LTCACT=DISABLED.
            aIncomingDefectsIf.GetDefectStatus(CT_TEL_TCM_LTC_DEFECT, &aLTCCount, &aLTCDefect);

            if ( aIncomingDefectsIf.IsLayerInDefects() || aMyLayerLocked ||  
                 aIncomingDefectsIf.IsLayerInDefectsNTA()                || 
                 aIncomingDefectsIf.IsLayerInNonPropagateDefectsNTA()    || 
                 aIncomingDefectsIf.IsInPropagateNextLayerDefectsTA()    ||
                 aLTCDefect)
            {
                aForceBDI  = true;
            }            
        }

        hasChanged |= aTcmAutomaticConfig.SetForceBDI(aForceBDI);        
    }

    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}
