/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Jessica Chen - July 2010
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_TcmIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_TcmIf::TSPII_TcmIf(bool theDefault):
    TSPII_DwIf(theDefault)    
{   
    Reset();
}


///////////////////////////////////////////////////////////////////////////////
TSPII_TcmIf::~TSPII_TcmIf()
{
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::RefreshGet()
{
    // Monitoring attributes
    itsLTC       = GetLTC();
    itsIAE       = GetIAE();
    itsLCK       = GetLCK();
    itsOCI       = GetOCI();
    itsAIS       = GetAIS();
    itsBDI       = GetBDI();   
    itsBIAE      = GetBIAE(); 
    itsBerSd     = GetBerSd();   
    itsBip8Count = GetBip8Count();
    itsHighBip8Count = GetHighBip8Count();
    itsRxTrace   = GetRxTrace();
    itsTcmDelay  = GetTcmDelay();

    // Configuration attributes
    itsForcedTCMIndication  = GetForcedTCMIndication();    
    itsForcedBDI            = GetForcedBDI(); 
    itsForcedBIAE           = GetForcedBIAE();   
    itsBerSdThreshold       = GetBerSdThreshold();
    itsTxTrace              = GetTxTrace();
    itsTCMMode              = GetTCMMode(); 
    itsBurstySdBerIntervals = GetBurstyBerSdIntervals();
    itsBurstySdBerThreshold = GetBurstyBerSdThreshold();
    itsSsfActive            = GetTcmSsf();
	itsTcmLTCActEnabled     = GetTcmLTCActEnabled();
    itsServer               = GetServer();
    itsTcmDelayEnabled      = GetTcmDelayEnabled();
    
    //for autoIndicaiton
    itsAutoLTC              = GetAutoTCMIndication(CT_TCM_INDICATION_LTC);
    itsAutoIAE              = GetAutoTCMIndication(CT_TCM_INDICATION_IAE);
    itsAutoLCK              = GetAutoTCMIndication(CT_TCM_INDICATION_LCK);
    itsAutoOCI              = GetAutoTCMIndication(CT_TCM_INDICATION_OCI);
    itsAutoAIS              = GetAutoTCMIndication(CT_TCM_INDICATION_AIS);
    itsAutoBIAE             = GetAutoTCMIndication(CT_TCM_INDICATION_BIAE);

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::RefreshSet()
{
   
    // Configuration attributes
    ForceTCMIndication(itsForcedTCMIndication);    
    ForceBDI(itsForcedBDI); 
    ForceBIAE(itsForcedBIAE);   
    SetBerSdThreshold(itsBerSdThreshold);
    SetTxTrace(itsTxTrace);
    SetTCMMode(itsTCMMode);
    SetBurstyBerSdThreshold(itsBurstySdBerIntervals, itsBurstySdBerThreshold);
    SetTcmSsf(itsSsfActive);
	SetTcmLTCActEnabled(itsTcmLTCActEnabled);
		
    SetServer(itsServer);
    SetTcmDelayEnabled(itsTcmDelayEnabled);

    //for autoIndicaiton
    SetAutoTCMIndication(CT_TCM_INDICATION_LTC,itsAutoLTC);
    SetAutoTCMIndication(CT_TCM_INDICATION_IAE,itsAutoIAE);
    SetAutoTCMIndication(CT_TCM_INDICATION_BIAE,itsAutoBIAE);
    SetAutoTCMIndication(CT_TCM_INDICATION_AIS,itsAutoAIS);
    SetAutoTCMIndication(CT_TCM_INDICATION_LCK,itsAutoLCK);
    SetAutoTCMIndication(CT_TCM_INDICATION_OCI,itsAutoOCI );    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::Reset()
{
   
    TSPII_BaseIf::Reset();

    //clear the itsTcmMap
    itsTcmMapRecord.Clear();

    // Monitoring attributes
    itsLTC       = 0;
    itsIAE       = 0;
    itsLCK       = 0;
    itsOCI       = 0;
    itsAIS       = 0; 
    
    itsBDI       = 0;
    itsBIAE      = 0;    
    itsBerSd     = 0;    
    itsBip8Count = 0;
    itsHighBip8Count = 0;
    itsTcmDelay  = 0;
    itsRxTrace   = CT_G709Trace(); 

    // Configuration attributes
    itsForcedTCMIndication	= CT_TCM_INDICATION_UNKNOWN;    
    itsForcedBDI            = false;  
    itsForcedBIAE           = false;  
    itsBerSdThreshold       = CT_TEL_NO_BER;
    itsTxTrace              = CT_G709Trace();
    itsTCMMode              = CT_TCM_MODE_NONE;
    itsBurstySdBerIntervals = 0;
    itsBurstySdBerThreshold = 0;
    itsSsfActive            = false;
	itsTcmLTCActEnabled     = false;
    itsServer               = CT_ODU_ServerID::SERVER_DEFAULT;
    itsTcmDelayEnabled      = false;
    itsTcmOrder             = CT_TCM_Order_END;

    //for autoIndicaiton
    itsAutoLTC              = false;
    itsAutoIAE              = false;
    itsAutoLCK              = false;
    itsAutoOCI              = false;    
    itsAutoAIS              = false;    
    itsAutoBIAE             = false;
    
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::SetTcmMap(const TSPII_TcmMapRecord & theMap)
{
    itsTcmMapRecord.operator=(theMap);
    
}
///////////////////////////////////////////////////////////////////////////////
TSPII_TcmMapRecord* TSPII_TcmIf::GetTcmMap()
{
    return (&(itsTcmMapRecord));
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::CommitTcm()
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::SetAutoTCMIndication(CT_TCM_IndicationType theIndication,bool theEnable)
{
    switch(theIndication)
    {
        case CT_TCM_INDICATION_LTC:
            itsAutoLTC = theEnable;
            break;
        case CT_TCM_INDICATION_IAE:
            itsAutoIAE = theEnable;
            break;
        case CT_TCM_INDICATION_BIAE:
            itsAutoBIAE = theEnable;
            break;
        case CT_TCM_INDICATION_AIS:
            itsAutoAIS = theEnable;
            break;
        case  CT_TCM_INDICATION_LCK:
            itsAutoLCK = theEnable;
            break;
        case CT_TCM_INDICATION_OCI:
            itsAutoOCI = theEnable;
            break;
        default:
            break;
    }
}
///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::GetAutoTCMIndication(CT_TCM_IndicationType theIndication)
{
    bool aVal = false;
    switch(theIndication)
    {
        case CT_TCM_INDICATION_LTC:
            aVal = itsAutoLTC;
            break;
        case CT_TCM_INDICATION_IAE:
            aVal = itsAutoIAE;
            break;
        case CT_TCM_INDICATION_BIAE:
            aVal = itsAutoBIAE;
            break;
        case CT_TCM_INDICATION_AIS:
            aVal = itsAutoAIS;
            break;
        case  CT_TCM_INDICATION_LCK:
            aVal = itsAutoLCK;
            break;
        case CT_TCM_INDICATION_OCI:
            aVal = itsAutoOCI;
            break;
        default:
            //aVal = false;
            break;
    }
    return aVal;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::ForceTCMIndication(CT_TCM_IndicationType theIndication)
{
    itsForcedTCMIndication = theIndication;
}
///////////////////////////////////////////////////////////////////////////////
CT_TCM_IndicationType TSPII_TcmIf::GetForcedTCMIndication() const
{
    return itsForcedTCMIndication;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_TcmIf::GetLTC()
{
    return itsLTC;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_TcmIf::GetIAE()
{
    return itsIAE;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_TcmIf::GetBIAE()
{
    return itsBIAE;
}
///////////////////////////////////////////////////////////////////////////////
int32 TSPII_TcmIf::GetTcmDelay()
{
    return itsTcmDelay;
}

///////////////////////////////////////////////////////////////////////////////
CT_TCM_Mode TSPII_TcmIf::GetTCMMode()
{
    return itsTCMMode;
}
///////////////////////////////////////////////////////////////////////////////
void     TSPII_TcmIf::SetTCMMode(CT_TCM_Mode theMode)
{ 
    itsTCMMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::ForceBIAE(bool theEnable)
{
    itsForcedBIAE = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::GetForcedBIAE() const 
{
    return itsForcedBIAE;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::SetTcmSsf(bool ssfActive)
{
  itsSsfActive = ssfActive;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::GetTcmSsf() const
{
  return itsSsfActive;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::SetTcmOrder(CT_TCM_Order theTcmOrder)
{
  itsTcmOrder = theTcmOrder;
}

void TSPII_TcmIf::SetTcmLTCActEnabled(bool theEnable)
{
  itsTcmLTCActEnabled = theEnable;
}

bool TSPII_TcmIf::GetTcmLTCActEnabled()
{
   return itsTcmLTCActEnabled;
}
///////////////////////////////////////////////////////////////////////////////
CT_TCM_Order TSPII_TcmIf::GetTcmOrder() 
{
  return itsTcmOrder;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::SetTcmDelayEnabled(bool theEnable)
{
  itsTcmDelayEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::GetTcmDelayEnabled() const
{
  return itsTcmDelayEnabled;
}


///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_TcmIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();
    
    int aBerSdThreshold = itsBerSdThreshold;
    uint32 aServer = itsServer.GetIdValue();

    //map    
    theStream << itsTcmMapRecord.TcmChannel;
    theStream << itsTcmMapRecord.TcmLevel;
    theStream << itsTcmMapRecord.TcmDirection;
    theStream << itsTcmMapRecord.OduIndex;
    theStream << itsTcmMapRecord.OduKLevel;    
    // Monitoring
    theStream << itsRxTrace;
    theStream << itsLTC;
    theStream << itsIAE;
    theStream << itsLCK;
    theStream << itsOCI;
    theStream << itsAIS;
    theStream << itsBDI;
    theStream << itsBIAE;    
    theStream << itsBerSd;    
    theStream << itsBip8Count; 
    theStream << itsHighBip8Count; 
    theStream << itsTcmDelay; 

    // Configuration
    theStream << itsTxTrace;
    theStream << itsForcedTCMIndication;    
    theStream << itsForcedBDI; 
    theStream << itsForcedBIAE;   
    theStream << aBerSdThreshold;
    theStream << itsTCMMode;
    theStream << itsBurstySdBerIntervals;
    theStream << itsBurstySdBerThreshold;
    theStream << itsSsfActive;
    theStream << aServer;
    theStream << itsTcmDelayEnabled;
	theStream << itsTcmLTCActEnabled;
    theStream << itsTcmOrder;

    
    //Auto Configuration
    theStream << itsAutoLTC;
    theStream << itsAutoIAE;
    theStream << itsAutoLCK;
    theStream << itsAutoOCI;    
    theStream << itsAutoAIS;
    theStream << itsAutoBIAE;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_TcmIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aBerSdThreshold;   
    uint32 aServer;

    //map
    theStream >> itsTcmMapRecord.TcmChannel;
    theStream >> ((int&)itsTcmMapRecord.TcmLevel);
    theStream >> ((int&)itsTcmMapRecord.TcmDirection);
    theStream >> itsTcmMapRecord.OduIndex;
    theStream >> ((int&)itsTcmMapRecord.OduKLevel);
    // Monitoring
    theStream >> itsRxTrace;
    theStream >> itsLTC;
    theStream >> itsIAE;
    theStream >> itsLCK;
    theStream >> itsOCI;
    theStream >> itsAIS;
    theStream >> itsBDI;
    theStream >> itsBIAE;    
    theStream >> itsBerSd;    
    theStream >> itsBip8Count; 
    theStream >> itsHighBip8Count; 
    theStream >> itsTcmDelay; 

    // Configuration
    theStream >> itsTxTrace;
    theStream >> ((int&)itsForcedTCMIndication);   
    theStream >> itsForcedBDI; 
    theStream >> itsForcedBIAE;    
    theStream >> aBerSdThreshold;
    theStream >> ((int&)itsTCMMode);
    theStream >> itsBurstySdBerIntervals;
    theStream >> itsBurstySdBerThreshold;
    theStream >> itsSsfActive;
    theStream >> aServer;
    theStream >> itsTcmDelayEnabled;
	theStream >> itsTcmLTCActEnabled;
    theStream >> ((int&)itsTcmOrder);
    
    //Auto Configuration
    theStream >> itsAutoLTC;
    theStream >> itsAutoIAE;
    theStream >> itsAutoLCK;
    theStream >> itsAutoOCI;    
    theStream >> itsAutoAIS;
    theStream >> itsAutoBIAE;

    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsServer         = (CT_ODU_ServerID)aServer;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_TcmIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();
    
    int aBerSdThreshold = itsBerSdThreshold;
    uint32 aServer = itsServer.GetIdValue();

     //map    
    theStream << FC_InsertVar(itsTcmMapRecord.TcmChannel);
    theStream << FC_InsertVar((int&)itsTcmMapRecord.TcmLevel);
    theStream << FC_InsertVar((int&)itsTcmMapRecord.TcmDirection);
    theStream << FC_InsertVar(itsTcmMapRecord.OduIndex);
    theStream << FC_InsertVar((int&)itsTcmMapRecord.OduKLevel);

    // Monitoring
    theStream << itsRxTrace;
    theStream << FC_InsertVar(itsLTC);
    theStream << FC_InsertVar(itsIAE);
    theStream << FC_InsertVar(itsLCK);
    theStream << FC_InsertVar(itsOCI);
    theStream << FC_InsertVar(itsAIS);
    theStream << FC_InsertVar(itsBDI);
    theStream << FC_InsertVar(itsBIAE);    
    theStream << FC_InsertVar(itsBerSd);    
    theStream << FC_InsertVar(itsBip8Count);
    theStream << FC_InsertVar(itsHighBip8Count);
    theStream << FC_InsertVar(itsTcmDelay);

    // Configuration
    theStream << itsTxTrace;
    theStream << FC_InsertVar((int&)itsForcedTCMIndication);    
    theStream << FC_InsertVar(itsForcedBDI); 
    theStream << FC_InsertVar(itsForcedBIAE);    
    theStream << FC_InsertVar(aBerSdThreshold);
    theStream << FC_InsertVar((int&)itsTCMMode);
    theStream << FC_InsertVar(itsBurstySdBerIntervals);
    theStream << FC_InsertVar(itsBurstySdBerThreshold);
    theStream << FC_InsertVar(itsSsfActive);
    theStream << FC_InsertVar(aServer);
    theStream << FC_InsertVar(itsTcmDelayEnabled);
	theStream << FC_InsertVar(itsTcmLTCActEnabled);
    theStream << FC_InsertVar((int&)itsTcmOrder);
    
    //Auto Configuration
    theStream << FC_InsertVar(itsAutoLTC);
    theStream << FC_InsertVar(itsAutoIAE);
    theStream << FC_InsertVar(itsAutoLCK);
    theStream << FC_InsertVar(itsAutoOCI);    
    theStream << FC_InsertVar(itsAutoAIS);
    theStream << FC_InsertVar(itsAutoBIAE);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_TcmIf::ReadObject(istream & theStream)
{
    int aBerSdThreshold;
    uint32 aServer;

    //map    
    theStream >> FC_ExtractVar(itsTcmMapRecord.TcmChannel);
    theStream >> FC_ExtractVar((int&)itsTcmMapRecord.TcmLevel);
    theStream >> FC_ExtractVar((int&)itsTcmMapRecord.TcmDirection);
    theStream >> FC_ExtractVar(itsTcmMapRecord.OduIndex);
    theStream >> FC_ExtractVar((int&)itsTcmMapRecord.OduKLevel);
    // Monitoring
    theStream >> itsRxTrace;    
    theStream >> FC_ExtractVar(itsLTC);
    theStream >> FC_ExtractVar(itsIAE);
    theStream >> FC_ExtractVar(itsLCK);    
    theStream >> FC_ExtractVar(itsOCI);
    theStream >> FC_ExtractVar(itsAIS);
    theStream >> FC_ExtractVar(itsBDI);
    theStream >> FC_ExtractVar(itsBIAE);    
    theStream >> FC_ExtractVar(itsBerSd);    
    theStream >> FC_ExtractVar(itsBip8Count);
    theStream >> FC_ExtractVar(itsHighBip8Count);
    theStream >> FC_ExtractVar(itsTcmDelay);

    // Configuration
    theStream >> itsTxTrace;
    theStream >> FC_ExtractVar((int&)itsForcedTCMIndication);    
    theStream >> FC_ExtractVar(itsForcedBDI);  
    theStream >> FC_ExtractVar(itsForcedBIAE);  
    theStream >> FC_ExtractVar(aBerSdThreshold);
    theStream >> FC_ExtractVar((int&)itsTCMMode);
    theStream >> FC_ExtractVar(itsBurstySdBerIntervals);
    theStream >> FC_ExtractVar(itsBurstySdBerThreshold);
    theStream >> FC_ExtractVar(itsSsfActive);
    theStream >> FC_ExtractVar(aServer);
    theStream >> FC_ExtractVar(itsTcmDelayEnabled);
    theStream >> FC_ExtractVar(itsTcmLTCActEnabled); 
    theStream >> FC_ExtractVar((int&)itsTcmOrder);
    
    //Auto Configuration
    theStream >> FC_ExtractVar(itsAutoLTC);
    theStream >> FC_ExtractVar(itsAutoIAE);    
    theStream >> FC_ExtractVar(itsAutoLCK);
    theStream >> FC_ExtractVar(itsAutoOCI);
    theStream >> FC_ExtractVar(itsAutoAIS);
    theStream >> FC_ExtractVar(itsAutoBIAE); 

    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsServer         = (CT_ODU_ServerID)aServer;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();
    
    theStream << "  Digital Wrapper (TCM) Mapping Info\n";
    theStream << "      TCM Channel           = "<<(itsTcmMapRecord.TcmChannel)<<"\n";
    theStream << "      TCM Direction         = "<< DISPLAY_ODU_DIRECTION(itsTcmMapRecord.TcmDirection)<<"\n";
    theStream << "      TCM Level             = "<<DISPLAY_TCM_Level(itsTcmMapRecord.TcmLevel)<<"\n";
    theStream << "      TCM mapping ODU Level = "<< DISPLAY_CT_ODU_Layer(itsTcmMapRecord.OduKLevel)<<"\n";
    theStream << "      TCM mapping ODU Index = "<<(itsTcmMapRecord.OduIndex)<<"\n";
    theStream << "  Digital Wrapper (TCM) Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      TCM TX Trace  = Sapi  = " << itsTxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsTxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "           OperatorSpecific = " << itsTxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsTxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsTxTrace.IsValid())          << "\n";
    theStream << "      TCM ind forced        = " << DISPLAY_TCM_INDICATION(itsForcedTCMIndication) << "\n";
    theStream << "      TCM BDI forced        = " << TEXT_ON_OFF(itsForcedBDI)                  << "\n";
    theStream << "      TCM BIAE forced       = " << TEXT_ON_OFF(itsForcedBIAE)                 << "\n";
    theStream << "      TCM BerSdThreshold    = " << DISPLAY_BER(itsBerSdThreshold)             << "\n";
    theStream << "      TCM Mode              = " << DISPLAY_TCM_MODE(itsTCMMode)               << "\n";
    theStream << "      TCM Bursty BER Thresh = DEGM(" << itsBurstySdBerIntervals << ") DEGTHR(" << itsBurstySdBerThreshold << ")\n";
    theStream << "      AUTO TCM LTC          = " << TEXT_ON_OFF(itsAutoLTC)                    << "\n";
    theStream << "      AUTO TCM IAE          = " << TEXT_ON_OFF(itsAutoIAE)                    << "\n";
    theStream << "      AUTO TCM LCK          = " << TEXT_ON_OFF(itsAutoLCK)                    << "\n";
    theStream << "      AUTO TCM OCI          = " << TEXT_ON_OFF(itsAutoOCI)                    << "\n";
    theStream << "      AUTO TCM AIS          = " << TEXT_ON_OFF(itsAutoAIS)                    << "\n";
    theStream << "      AUTO TCM BIAE         = " << TEXT_ON_OFF(itsAutoBIAE)                   << "\n";
    theStream << "      TCM SSF Active        = " << TEXT_ON_OFF(itsSsfActive)                  << "\n";
    theStream << "      TCM Server ID         = 0x" << hex << itsServer.GetIdValue() << dec << itsServer.DisplayServerID() << "\n";
    theStream << "      TCM Delay Enabled     = " << TEXT_ON_OFF(itsTcmDelayEnabled)            << "\n";
    theStream << "      TCM Order     = " << (uint32)itsTcmOrder<< "\n";
    theStream << "    MONITORING\n";
    theStream << "      TCM RX Trace  = Sapi  = " << itsRxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsRxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "           OperatorSpecific = " << itsRxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsRxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsRxTrace.IsValid())          << "\n";
    theStream << "      TCM LTC defect        = " << TEXT_DEFECT(itsLTC)                        << "\n";
    theStream << "      TCM IAE defect        = " << TEXT_DEFECT(itsIAE)                        << "\n";
    theStream << "      TCM LCK defect        = " << TEXT_DEFECT(itsLCK)                        << "\n";
    theStream << "      TCM OCI defect        = " << TEXT_DEFECT(itsOCI)                        << "\n";
    theStream << "      TCM AIS defect        = " << TEXT_DEFECT(itsAIS)                        << "\n";
    theStream << "      TCM BDI defect        = " << TEXT_DEFECT(itsBDI)                        << "\n";
    theStream << "      TCM BIAE defect       = " << TEXT_DEFECT(itsBIAE)                       << "\n";
    theStream << "      TCM BerSd defect      = " << TEXT_DEFECT(itsBerSd)                      << "\n";
    theStream << "      BIP8                  = " << itsBip8Count                               << "\n";
    theStream << "      HIGH BIP8             = " << itsHighBip8Count                               << "\n";
    theStream << "      TCM Delay             = " << itsTcmDelay                               << "\n";
    theStream << "      TCM LTCAct            = " << TEXT_ON_OFF(itsTcmLTCActEnabled)           << "\n";
    
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::Set(int argc, char ** argv)
{
    TSPII_TcmMapRecord      aMap;    
    char     aOutBuf[256];    
    bool     printUsage = false;

    if ((argc == 3) && (strcmp(argv[0], "settcmmap") == 0))
    {
         //<tcmchannel,tcmlevel,oduindex,oduklevel> <tcmdirection>
        if (strlen(argv[1]) < 256)
        {//<tcmchannel,tcmlevel,oduindex,oduklevel>
            // Read the Map record as a comma seperated string. 
            strcpy(aOutBuf, argv[1]);
            strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
            aMap.TcmChannel   = (uint16) atoi(strtok(aOutBuf, ","));
            aMap.TcmLevel  = (CT_TCM_Level) atoi(strtok(NULL, ","));                     
            aMap.OduIndex = (uint16) atoi(strtok(NULL, ","));
            aMap.OduKLevel = (CT_ODU_Layer) atoi(strtok(NULL, ","));
            //<tcmdirection>
            aMap.TcmDirection = TSPII_TCM_DIRECTION_GET(argv[2]);
            if(aMap.TcmChannel < MAX_NUM_TCMPOOL_PER_SHELF)
            {   //set the itsTcmMap
                SetTcmMap(aMap);
                printUsage =  false;
           }
       }
    }
    else if ((argc >=1) && (strcmp(argv[0], "deletetcmmap") == 0)) 
    {
       //clear the itsTcmMap
       aMap.Clear();  
       SetTcmMap(aMap);     
       printUsage = false;
    }
    else if (argc == 4 && strcmp(argv[0], "txtrace") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3]);
        SetTxTrace(trace);
    }
    else if (argc ==2 && strcmp(argv[0],"setmode") == 0 )
    {   
        if(strcmp(argv[1], "source") == 0)
        {
            SetTCMMode(CT_TCM_MODE_SOURCE);
        }
        else if(strcmp(argv[1], "sink") == 0)
        {
            SetTCMMode(CT_TCM_MODE_SINK);
        }
        else if(strcmp(argv[1], "src_snk") == 0)
        {
            SetTCMMode(CT_TCM_MODE_SRC_SNK);
        }
        else if(strcmp(argv[1], "snk_nim") == 0)
        {
            SetTCMMode(CT_TCM_MODE_SNK_NIM);
        }
        else if(strcmp(argv[1], "src_snk_nim") == 0)
        {
            SetTCMMode(CT_TCM_MODE_SRC_SNK_NIM);
        }
        else if(strcmp(argv[1], "unknown") == 0)
        {
            SetTCMMode(CT_TCM_MODE_UNKNOWN);
        }
        else if(strcmp(argv[1], "none") == 0)
        {
            SetTCMMode(CT_TCM_MODE_NONE);
        }
        else
        {
            printUsage = true;
        } 
    }
    else if (argc == 2 && strcmp(argv[0], "forceind") == 0)
    {
        if (strcmp(argv[1], "ltc") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_LTC);
        }
        else if (strcmp(argv[1], "iae") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_IAE);
        }
        else if (strcmp(argv[1], "lck") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_LCK);
        }
        else if (strcmp(argv[1], "oci") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_OCI);
        }
        else if (strcmp(argv[1], "ais") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_AIS);
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_UNKNOWN);
        }
        else if (strcmp(argv[1], "none") == 0)
        {
            ForceTCMIndication(CT_TCM_INDICATION_NONE);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "autoind") == 0)
    {   bool aEnable = false;
        if (strcmp(argv[2], "on") == 0)
        {
            aEnable = true;
        }
        
        if (strcmp(argv[1], "ltc") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_LTC,aEnable);
        }
        else if (strcmp(argv[1], "iae") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_IAE,aEnable);
        }
        else if (strcmp(argv[1], "lck") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_LCK,aEnable);
        }
        else if (strcmp(argv[1], "oci") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_OCI,aEnable);
        }        
        else if (strcmp(argv[1], "ais") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_AIS,aEnable);
        }        
        else if(strcmp(argv[1],"biae") == 0)
        {
            SetAutoTCMIndication(CT_TCM_INDICATION_BIAE,aEnable);
        }
        else
        {
            printUsage = true;
        }
    }
    
    else if (argc == 2 && strcmp(argv[0], "forcebdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            ForceBDI(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            ForceBDI(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forcebiae") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            ForceBIAE(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            ForceBIAE(false);
        }
        else
        {
            printUsage = true;
        }
    }
	if (argc == 2 && strcmp(argv[0], "SetTcmLTCAct") == 0)
	{
           if (strcmp(argv[1], "on") == 0)
        {
            SetTcmLTCActEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTcmLTCActEnabled(false);
        }
        else
        {
            printUsage = true;
        }
	}
    else if ((argc == 3) && (strcmp(argv[0], "bursty-bersdthres") == 0))
    {
        itsBurstySdBerIntervals = static_cast<unsigned int>(strtoul(argv[1], NULL, 0));
        itsBurstySdBerThreshold = static_cast<unsigned long int>(strtoul(argv[2], NULL, 0));
        SetBurstyBerSdThreshold(itsBurstySdBerIntervals, itsBurstySdBerThreshold);
    }
    else if ((argc == 2) && strcmp(argv[0], "bersdthres") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_INFINITE_BER; i++) if (strcmp(argv[1], DISPLAY_BER(i)) == 0)
        {
            SetBerSdThreshold((CT_TEL_BERLevels)i);
            printUsage = false;
            break;
        }
    }
    // Must parse "Error free" as two arguments since FC parser doesn't do it if quoted.
    else if ((argc == 3) && (strcmp(argv[0], "bersdthres") == 0) &&
             (strcmp(argv[1], "Error") == 0) &&
             (strcmp(argv[2], "free") == 0))
    {
        SetBerSdThreshold(CT_TEL_NO_BER);
        printUsage = false;
    }
    else if ((argc == 2) && strcmp(argv[0], "setssf") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetTcmSsf(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTcmSsf(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "server") == 0 )
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: Server ID must be a hex number" << endl;
            printUsage = true;
        }
        else
        {
            SetServer(CT_ODU_ServerID(strtoul(argv[1], NULL, 0)));
            printUsage = false;
        }         
    }
    else if ((argc == 2) && strcmp(argv[0], "tdenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetTcmDelayEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTcmDelayEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
          fc_cout <<"Usage: tspii settcmp [1-136] settcmmap <tcmchannel,tcmlevel,oduindex,oduklevel> <tcmdirection>\n"
                   "                             - tcm chanel = [0-135] for Tcm Channel 1-136.  \n"
                   "                             - tcm level  = [1-6] for Tcm Level 1-6\n"                   
                   "                             - oduindex = the odu Index : 0~31 for ODU1 32 instances,\n"
                   "                                                          0~7  for ODU2 8 instances,\n "
                   "                                                          0~63 for ODU0 64 instances.\n"                   
                   "                             - odu k level = the oduklevel[0-2]for ODU0,ODU1,ODU2 \n"
                   "                             - tcm direction = a or b \n"
                   "                             deletetcmmap \n"
                   "    txtrace         <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>\n"
                   "    forceind        <ltc|iae|lck|oci|ais|unknown|none>\n"
                   "    autoind         <ltc|iae|lck|oci|ais|biae>  <on|off>\n"                   
                   "    forcebdi        <on|off>\n"  
                   "    forcebiae       <on|off>\n"                 
                   "    tdenabled       <on|off>\n"                 
                   "    bersdthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    bursty-bersdthres <DEGM(uint> <DEGTHR(uint32)>\n"
                   "    setmode         <source|sink|src_snk|snk_nim|src_snk_nim|unknown|none>\n"
                   "    setssf          <on|off>\n"
                   "    SetTcmLTCAct    <on|off>\n"
                   "    server          <uint16>\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_TcmIf::Simul(int argc, char ** argv)
{
    bool     printUsage = false;

    if (argc == 4 && strcmp(argv[0], "rxtrace") == 0)
    {
        itsRxTrace = CT_G709Trace(argv[1], argv[2], argv[3], 0, CT_TEL_STANDARD_TRACE); 
    }
    else if (argc == 2 && strcmp(argv[0], "ltc") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLTC)) itsLTC++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLTC)) itsLTC++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "iae") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsIAE)) itsIAE++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsIAE)) itsIAE++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "lck") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLCK)) itsLCK++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLCK)) itsLCK++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "oci") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsOCI)) itsOCI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsOCI)) itsOCI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsAIS)) itsAIS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsAIS)) itsAIS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "bdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBDI)) itsBDI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBDI)) itsBDI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "biae") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBIAE)) itsBIAE++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBIAE)) itsBIAE++;
        }
        else
        {
            printUsage = true;
        }
    }     
    else if ((argc == 2) && (strcmp(argv[0], "bersd") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBerSd)) itsBerSd++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBerSd)) itsBerSd++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "bursty-bersdthres") == 0))
    {
        itsBurstySdBerIntervals = static_cast<unsigned int>(strtoul(argv[1], NULL, 0));
        itsBurstySdBerThreshold = static_cast<unsigned long int>(strtoul(argv[2], NULL, 0));       
    }
    
    else if (argc == 2 && strcmp(argv[0], "bip8") == 0)
    {
        itsBip8Count = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incbip8") == 0)
    {
        itsBip8Count += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highbip8") == 0)
    {
        itsHighBip8Count = strtoul(argv[1], NULL, 0);
    }    
    else if (argc == 2 && strcmp(argv[0], "delay") == 0)
    {
        itsTcmDelay = strtoul(argv[1], NULL, 0);
    }

    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    rxtrace         <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>\n"
                   "    ltc             <on|off>\n"
                   "    iae             <on|off>\n"
                   "    lck             <on|off>\n"                   
                   "    oci             <on|off>\n"
                   "    ais             <on|off>\n"
                   "    bdi             <on|off>\n"   
                   "    biae            <on|off>\n"                   
                   "    bersd           <on|off>\n" 
                   "    bursty-bersdthres <DEGM(uint> <DEGTHR(uint32)>\n"
                   "    bip8            <count>\n"
                   "    incbip8         <increment>\n"
                   "    highbip8        <count>\n"
                   "    delay           <0-2147483647>\n"<< endl;
    }
    return printUsage;
}
    
///////////////////////////////////////////////////////////////////////////////
void TSPII_TcmIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
