
//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef SNMP_BBAPPIF_H
#define SNMP_BBAPPIF_H

#include <AppFramework/FC_BbApp.h>
#include <CommonTypes/CT_SystemIds.h>
#include <Shell/FC_CmdProcessor.h>
#include <T6100_TelecomIf.h>
#include <T6100_CardIf.h>

class T6100_CardActiveRegion;

//This is the base application for Telecom Services.
class SNMP_BbAppIf: public FC_BbApp
{
public:

	//Constructor.
    SNMP_BbAppIf(T6100_TelecomIf& theContext);
    SNMP_BbAppIf();

	//Virtual destructor.
    virtual ~SNMP_BbAppIf();

    T6100_TelecomIf& GetTelecomContext();
    T6100_CardIf&    GetCardContext();
    CT_SlotId GetSlotId();
    
    virtual T6100_CardActiveRegion& GetTelecomContextStatusRegion();

private:
    T6100_TelecomIf* myTelecomContext;
};

#endif //SNMP_BBAPPIF_H

