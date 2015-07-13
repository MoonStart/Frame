// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_GfpIf.h>
#include "../CFG_HwRefreshGfp.h"
#include "../CFG_Gfp.h"
#include "../CFG_GfpAutomatic.h"
#include "../CFG_GfpProt.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

#define CFG_DEFAULT_SESSION_COUNTER 0xFFFFFFFF

CFG_HwRefreshGfp::CFG_HwRefreshGfp(CFG_AppIf& theCfgIf,
                                   CFG_GfpAutomaticCfgRegion* theAutomaticCfgRegion,
                                   CFG_GfpProtCfgRegion* theProtCfgRegion,
                                   uint8 theNumGfp,
                                   TSPII_GfpRegion& theGfpPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myProtCfgRegion(theProtCfgRegion),
    myGfpPiiRegion(theGfpPiiRegion),
    myNumGfp(theNumGfp)
{
    myLocalAutoNegSessionCounters = new uint32[myNumGfp];
    int i;
    for (i=0; i<myNumGfp; i++)
    {
        myLocalAutoNegSessionCounters[i] = CFG_DEFAULT_SESSION_COUNTER;
    }

	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    if (myProtCfgRegion) GetBbAction()->AddInputRegion(myProtCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshGfp::~CFG_HwRefreshGfp()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    if (myProtCfgRegion) GetBbAction()->RemoveInputRegion(myProtCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    delete [] myLocalAutoNegSessionCounters;
}

FC_Object* CFG_HwRefreshGfp::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // Loop thru all of the Gfps's.
    for (int16 anIndex = 0; anIndex < myNumGfp; anIndex++) 
    {

	    CFG_Gfp& aCfgObject = static_cast<CFG_Gfp&>((*GetCfgIf().GetCfgRegion())[anIndex]);
   
        TSPII_GfpIf& aGfpPiiObject = myGfpPiiRegion[anIndex];

        //If the session counter is default, then do not consider received session
        //counter as a change. Update the local counter with the received value.
        if (myLocalAutoNegSessionCounters[anIndex] == CFG_DEFAULT_SESSION_COUNTER)
        {
            myLocalAutoNegSessionCounters[anIndex] = aCfgObject.GetAutoNegSessionCounter();
        }

        // Set Enable Auto-Negotiation.
        if ((aCfgObject.GetAutoNegotiationEnabled()) &&
            (aCfgObject.GetAutoNegSessionCounter() != myLocalAutoNegSessionCounters[anIndex])) 
        {
            myLocalAutoNegSessionCounters[anIndex] = aCfgObject.GetAutoNegSessionCounter();
            aGfpPiiObject.EnableAutoNegotiation(false);
        }
        aGfpPiiObject.EnableAutoNegotiation(aCfgObject.GetAutoNegotiationEnabled()); 

        if (myAutomaticCfgRegion)
        {
           CFG_GfpAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[anIndex];

           // Set client management frame type if GFP is enabled
           aGfpPiiObject.SetForceClientMgmtFrame(aAutomaticCfgObject.GetForceClientMgmtFrame());

           // Set force of 8b/10b illegal codes.
           aGfpPiiObject.SetForce8B10BIllegalCodes(aAutomaticCfgObject.GetForce10BError());

           // Set force of GenericLayerFail.
           aGfpPiiObject.SetForceGenericLayerFail(aAutomaticCfgObject.GetForceGenericLayerFail());

		   // Set force of idle codes
           aGfpPiiObject.SetForceIdles(aAutomaticCfgObject.GetForceIdle());
 
           // Set One Way GBE.
           aGfpPiiObject.EnableOneWayGbe(aAutomaticCfgObject.GetOneWayGbe());

           // Set Port Index of Facility when the Gfp is pooled.
           aGfpPiiObject.SetPortIndex(aAutomaticCfgObject.GetPortIndex());

           // Auto Negotiation can be set in Gfp or Mac layer
           bool anAutoNegEnabled = (aCfgObject.GetAutoNegotiationEnabled()     || 
                                    aAutomaticCfgObject.GetMacAutoNegEnabled()  );

           // Write it down to Tspii again 
           // I didn't want to change the code above since something might be order dependent
           // This should only change to true if the Mac layer has it enabled and that was on the SSM.
           // The SSM isn't using the session counter above (yet).  If that changes, restrucure the code
           // and put all auto negotiation after the Automatic region is checked.
           aGfpPiiObject.EnableAutoNegotiation(anAutoNegEnabled); 


           // Check if Auto-Negotiation is enabled.
           if (anAutoNegEnabled) 
           {
   
               if (myProtCfgRegion)
               {
                   CFG_GfpProt& aProtCfgObject = (*myProtCfgRegion)[0]; 

                   if (aProtCfgObject.GetForceLinkFailTx())
                   {
                       //Force link fail.
                       aGfpPiiObject.SetLinkFailTx(true);
                   }
                   else
                   {
                       // Set link fail based on cfg
                       aGfpPiiObject.SetLinkFailTx(aAutomaticCfgObject.GetForceLinkFailTx());           
			       }
               }
               else
               {
                   // Set link fail based on cfg
                   aGfpPiiObject.SetLinkFailTx(aAutomaticCfgObject.GetForceLinkFailTx());       
               }
           
               // Set remote fault
               aGfpPiiObject.SetRemoteFaultTx(aAutomaticCfgObject.GetForceRemoteFault());    

           }
           else
           {
                //Don't force CR0 if Auto-Negotiation is disabled.
                aGfpPiiObject.SetLinkFailTx(false);
           }

        }

        //Set GFP User Payload Id
        aGfpPiiObject.SetUpi(aCfgObject.GetUpi());

        // Set framing mode
        aGfpPiiObject.SetFramingMode(aCfgObject.GetFramingMode());

        // Set enable mode
        aGfpPiiObject.SetEnabled(aCfgObject.GetEnableMode());

        // Set superblock size
        aGfpPiiObject.SetSuperblockSize(aCfgObject.GetSuperblockSize());

        //Set Frame Discard mode
        if (aCfgObject.GetPauseDiscardEnabled())
        {
            aGfpPiiObject.EnablePauseFrameTransparency(false);        
        }
        else
        {
            aGfpPiiObject.EnablePauseFrameTransparency(true);     
        }

        //Set Linear Extention Enabled
        aGfpPiiObject.SetExtEnabled(aCfgObject.GetExtEnabled());

        //Set Linear Extention Channel Id
        aGfpPiiObject.SetExtCid(aCfgObject.GetExtChannelId());

        // Let TSPII know that GFP updates are complete for this port.
        // NOTE:  This call must be last.
        aGfpPiiObject.CommitGfp();
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

