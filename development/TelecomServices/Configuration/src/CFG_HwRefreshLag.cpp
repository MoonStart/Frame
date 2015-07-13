// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_LagIf.h>
#include "../CFG_HwRefreshLag.h"
#include "../CFG_Lag.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

CFG_HwRefreshLag::CFG_HwRefreshLag(CFG_AppIf& theCfgIf,
                                   uint8 theNumLag,
                                   TSPII_LagRegion& theLagPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myNumLag(theNumLag),
    myLagPiiRegion(theLagPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshLag::~CFG_HwRefreshLag()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshLag::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // First of all pass down removed LAG's.
    // Loop thru all of the Lag's.
    for (int16 anIndex = 0; anIndex < myNumLag; anIndex++) 
    {

        CFG_Lag& aCfgObject = static_cast<CFG_Lag&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        TSPII_LagIf& aLagPiiObject = myLagPiiRegion[anIndex];
   
        if ( aCfgObject.GetLagId() == -1)
        {
            // Pass the ID of this Lag.
            aLagPiiObject.SetLagId(aCfgObject.GetLagId());

            // Indicate if this Lag is the master.
            aLagPiiObject.SetMaster(aCfgObject.GetLagMaster());

            // Pass down lag list.     	
            list<CT_Port>::iterator i;
            vector<TSPII_LagMember> aTSPIILagList;
            aTSPIILagList.erase(aTSPIILagList.begin(), aTSPIILagList.end());

            for (i = aCfgObject.GetLagListBegin(); i != aCfgObject.GetLagListEnd(); i++)
            {
        
                CT_Port aPort;
                aPort = CT_Port(*i);
                TSPII_LagMember aMember;
            
                aMember.Slot = (uint16)aPort.GetSlotId();
                aMember.Port = (uint16)aPort.GetPortId();
                aTSPIILagList.push_back(aMember);
    
            }
            aLagPiiObject.SetMembers(aTSPIILagList);

            aLagPiiObject.SetLacpTimeoutMode(aCfgObject.GetLacpTimeoutMode());
            aLagPiiObject.SetLacpSystemPriority(aCfgObject.GetLacpSystemPriority());
            aLagPiiObject.SetLacpSystemID(aCfgObject.GetLacpSystemID());
            aLagPiiObject.SetAdminKey(aCfgObject.GetAdminKey());
            // Send LacpEnabled last
            aLagPiiObject.SetLacpEnabled(aCfgObject.GetLacpEnabled());
        }
    }

    // Now pass down Configured LAG's
    // Loop thru all of the Lag's.
    for (int16 anIndex = 0; anIndex < myNumLag; anIndex++) 
    {

        CFG_Lag& aCfgObject = static_cast<CFG_Lag&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        TSPII_LagIf& aLagPiiObject = myLagPiiRegion[anIndex];
   
        if ( aCfgObject.GetLagId() != -1)
        {
            // Pass the ID of this Lag.
            aLagPiiObject.SetLagId(aCfgObject.GetLagId());

            // Indicate if this Lag is the master.
            aLagPiiObject.SetMaster(aCfgObject.GetLagMaster());

            // Pass down lag list.     	
            list<CT_Port>::iterator i;
            vector<TSPII_LagMember> aTSPIILagList;
            aTSPIILagList.erase(aTSPIILagList.begin(), aTSPIILagList.end());

            for (i = aCfgObject.GetLagListBegin(); i != aCfgObject.GetLagListEnd(); i++)
            {
        
                CT_Port aPort;
                aPort = CT_Port(*i);
                TSPII_LagMember aMember;
            
                aMember.Slot = (uint16)aPort.GetSlotId();
                aMember.Port = (uint16)aPort.GetPortId();
                aTSPIILagList.push_back(aMember);
    
            }
            aLagPiiObject.SetMembers(aTSPIILagList);

            aLagPiiObject.SetLacpTimeoutMode(aCfgObject.GetLacpTimeoutMode());
            aLagPiiObject.SetLacpSystemPriority(aCfgObject.GetLacpSystemPriority());
            aLagPiiObject.SetLacpSystemID(aCfgObject.GetLacpSystemID());
            aLagPiiObject.SetAdminKey(aCfgObject.GetAdminKey());
            // Send LacpEnabled last
            aLagPiiObject.SetLacpEnabled(aCfgObject.GetLacpEnabled());
        }
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

