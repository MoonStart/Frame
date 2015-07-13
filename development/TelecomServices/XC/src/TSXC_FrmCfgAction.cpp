// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <XC/TSXC_FrmCfgAction.h>

#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_SubApplication.h>
             
bool TSXC_FrmCfgAction::myDisplayFrmDelete = false;
bool TSXC_FrmCfgAction::myDisplayFrmAdd = false;

//------------------------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------------------------
TSXC_FrmCfgAction::TSXC_FrmCfgAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myFrmCfg_Region(NULL)
{
}

//------------------------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------------------------
TSXC_FrmCfgAction::~TSXC_FrmCfgAction()
{

}

//------------------------------------------------------------------------------------------------------------
void TSXC_FrmCfgAction::SetFrmCfgRegion(TSXC_FrmCfgRegion<TSXC_Connect>* theFrmCfgRegion)
{
    myFrmCfg_Region = theFrmCfgRegion;
}

//------------------------------------------------------------------------------------------------------------
void TSXC_FrmCfgAction::SetDisplayFrmDelete(bool theValue)
{
    myDisplayFrmDelete = theValue;
}

//------------------------------------------------------------------------------------------------------------
void TSXC_FrmCfgAction::SetDisplayFrmAdd(bool theValue)
{
    myDisplayFrmAdd = theValue;
}

//------------------------------------------------------------------------------------------------------------
FC_Object* TSXC_FrmCfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    TSPII_XcRegion* tspiiXcRegion = NULL;
    CT_CardType aCardType = CARD_TYPE_UNKNOWN;

    aCardType = myFrmCfg_Region->GetMyCardType();
    
    if(aCardType == CARD_TYPE_OSM1S)
    {
        // 0(default) means cfg, 2 means frm, 3 means mux
        tspiiXcRegion = TSPII_SubApplication::GetInstance()->GetXc(2);
    }

    if(tspiiXcRegion != NULL)
    {
        START_TIME(TSXC_DEBUG_LEVEL01);

        UINT32 srcFac = 0, srcFacEndpt = 0, dstFac = 0, dstFacEndpt = 0;
        CT_XC_ConnectType connType = CT_XC_TYPE_UNSPECIFIED;
        CT_XC_ConnectState FRM_ConnState = CT_XC_STATE_NOTCONNECTED;
        TSPII_XcRecord tspiiConn;

        UINT32 maxRegionIndex = (*myFrmCfg_Region).Size();

        for(UINT32 regionIndex = 0; regionIndex < maxRegionIndex; regionIndex++)
        {
            TSXC_Connect* FRM_CfgObjectPtr = &((*myFrmCfg_Region)[(bbindex_t)regionIndex]);
            FRM_ConnState = FRM_CfgObjectPtr->GetState();

            srcFac      = FRM_CfgObjectPtr->GetInputFacility();
            srcFacEndpt = FRM_CfgObjectPtr->GetInputFacilityEndpoint();
            dstFac      = FRM_CfgObjectPtr->GetOutputFacility();
            dstFacEndpt = FRM_CfgObjectPtr->GetOutputFacilityEndpoint();
            connType    = FRM_CfgObjectPtr->GetType();

            if(FRM_ConnState == CT_XC_STATE_CONNECTED)
            {
                tspiiConn.Type     = ConnectTypeToTspii(connType);
                tspiiConn.InPort   = (*tspiiXcRegion)[0].TsPortToTspiiPort(srcFac);
                tspiiConn.InTslot  = srcFacEndpt - 1;
                tspiiConn.OutPort  = (*tspiiXcRegion)[0].TsPortToTspiiPort(dstFac);
                tspiiConn.OutTslot = dstFacEndpt - 1;

                (*tspiiXcRegion)[0].AddXconn(tspiiConn);

                if(myDisplayFrmAdd == true)
                {
                    fc_cout << "TSXC_FrmCfgAction::Invoking tspii\n" \
                            << "AddXconn(srcFac      = " << tspiiConn.InPort << "\n" \
                            << "         srcFacEndpt = " << tspiiConn.InTslot << "\n" \
                            << "         dstFac      = " << tspiiConn.OutPort << "\n" \
                            << "         dstFacEndpt = " << tspiiConn.OutTslot << "\n" \
                            << "         connType    = " << TSPII_XC_TYPE_DISPLAY(tspiiConn.Type) << ")\n" << endl;
                }

            }
            else
            {
                tspiiConn.Type     = ConnectTypeToTspii(connType);
                tspiiConn.OutPort  = (*tspiiXcRegion)[0].TsPortToTspiiPort(dstFac);
                tspiiConn.OutTslot = dstFacEndpt - 1;

                (*tspiiXcRegion)[0].DeleteXconn(tspiiConn);

                if(myDisplayFrmDelete == true)
                {
                    fc_cout << "TSXC_FrmCfgAction::Invoking tspii\n" \
                            << "DeleteXconn(dstFac      = " << tspiiConn.OutPort << "\n" \
                            << "            dstFacEndpt = " << tspiiConn.OutTslot << "\n" \
                            << "            connType    = " << TSPII_XC_TYPE_DISPLAY(tspiiConn.Type) << ")\n" << endl;

                }
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSXC FRM provision time : ");

        START_TIME(TSXC_DEBUG_LEVEL01);
        (*tspiiXcRegion)[0].CommitXconns();
        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSXC FRM commit time : ");
    }

    Respond(myFrmCfg_Region->GetCQMRequest());

    return NULL;
}

//------------------------------------------------------------------------------------------------------------
TSPII_XcType TSXC_FrmCfgAction::ConnectTypeToTspii(CT_XC_ConnectType connType)
{
    TSPII_XcType retVal = TSPII_XC_TYPE_UNKNOWN;

    switch(connType)
    {
        case CT_XC_TYPE_UNSPECIFIED:    retVal = TSPII_XC_TYPE_UNKNOWN;     break;
        case CT_XC_TYPE_ODU0:           retVal = TSPII_XC_TYPE_ODU0;        break;
        case CT_XC_TYPE_ODU1:           retVal = TSPII_XC_TYPE_ODU1;        break;
        case CT_XC_TYPE_ODU2:           retVal = TSPII_XC_TYPE_ODU2;        break;
        case CT_XC_TYPE_ODU2E:          retVal = TSPII_XC_TYPE_ODU2E;       break;
        case CT_XC_TYPE_ODU3:           retVal = TSPII_XC_TYPE_ODU3;        break;
        case CT_XC_TYPE_ODU4:           retVal = TSPII_XC_TYPE_ODU4;        break;
        case CT_XC_TYPE_ODUF:           retVal = TSPII_XC_TYPE_ODUF;        break;
        default:                        retVal =  TSPII_XC_TYPE_UNKNOWN;    break;
    }

    return retVal;
}

