//Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef CFG_DEFINITIONS_H
#define CFG_DEFINITIONS_H

#include <TelCommon/TEL_RegionBaseImpWithIndex.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Object.h>

const uint32 LINE_SIDE_PROTECTION_HOLDOFF     = 3000;
const uint32 CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO = 0;

const uint8  CFG_GFP_DEFAULT_PORT_INDEX       = 255;

// Forward Declarator
class CFG_Lprf;
class CFG_Pprf;
class CFG_Dccl;
class CFG_Dccp;
class CFG_DcclAutomatic;
class CFG_DcclProt;
class CFG_Tarp;
class CFG_Drtr;
class CFG_DrtrAutomatic;
class CFG_Ddlt;
class CFG_DdltAutomatic;
class CFG_Sync;
class CFG_SyncProt;
class CFG_T1E1;
class CFG_T1E1Automatic;
class CFG_Gfp;
class CFG_GfpAutomatic;
class CFG_GfpProt;
class CFG_Vcg;
class CFG_Hop;
class CFG_HopAutomatic;
class CFG_Layer2;
class CFG_Evc;
class CFG_EvcAutomatic;
class CFG_Lag;
class CFG_Mac;
class CFG_MacAutomatic;
class CFG_Misc;
class CFG_SwitchDomain;
//class CFG_Mesh;
class CFG_Bwpf;
class CFG_Cfpf;
class CFG_Ms;
class CFG_MsAutomatic;
class CFG_MsProt;
class CFG_Rs;
class CFG_RsAutomatic;
class CFG_Opt;
class CFG_OptAutomatic;
class CFG_OptAutoRateLock;
class CFG_OptProt;
class CFG_Otu;
class CFG_OtuAutomatic;
class CFG_Odu;
class CFG_OduAutomatic;
class CFG_OduCritical;
class CFG_Tcm;
class CFG_TcmAutomatic;
class CFG_Och;
class CFG_OchAutomatic;
class CFG_OchHistory;
class CFG_Oms;
class CFG_OmsAutomatic;
class CFG_OmsAutomaticShutdown;
class CFG_OmsAutomaticPwrAdj;
class CFG_Ots;
class CFG_OtsOH;
class CFG_OtsAutomatic;
class CFG_OtsAutomaticTxPwrShut;
class CFG_OtsOchOHAutomatic;
class CFG_TxOchAutomatic;
class CFG_CmmOosAutomatic;
class CFG_Gcc;
class CFG_GccAutomatic;
class CFG_OchAutoOnSC;
class CFG_IbEth;

//This is the region that contains the Dcc Link Profile Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Lprf>  CFG_LprfCfgRegion;
//This is the region that contains the Dcc Link Profile Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Pprf>  CFG_PprfCfgRegion;
//This is the region that contains the Dccl Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Dccl>  CFG_DcclCfgRegion;
//This is the region that contains the Dccl Alt Config Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Dccp>  CFG_DccpCfgRegion;
//This is the region that contains the Dccl Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_DcclAutomatic>  CFG_DcclAutomaticCfgRegion;
//This is a dummy region that represent Dccl Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_DcclOutputCfgRegion;
//This is the region that contains the Dccl protection configuration Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_DcclProt>  CFG_DcclProtCfgRegion;


//This is the region that contains the Tarp Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Tarp>  CFG_TarpCfgRegion;
//This is the region that contains the Drtr Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Drtr>  CFG_DrtrCfgRegion;
//This is the region that contains the Drtr Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_DrtrAutomatic>  CFG_DrtrAutomaticCfgRegion;
//This is a dummy region that represent Drtr Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_DrtrOutputCfgRegion;

//This is the region that contains the Ddlt Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Ddlt>  CFG_DdltCfgRegion;
//This is the region that contains the Ddlt Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_DdltAutomatic>  CFG_DdltAutomaticCfgRegion;
//This is a dummy region that represent Ddlt Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_DdltOutputCfgRegion;


//This is the region that contains the Sync protection configuration Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_SyncProt>  CFG_SyncProtCfgRegion;
//This is the region that contains the Sync Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Sync>  CFG_SyncCfgRegion;
//This is a dummy region that represent SYNC Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_SyncOutputCfgRegion;

//This is the region that contains the T1E1 Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_T1E1>  CFG_T1E1CfgRegion;
//This is the region that contains the T1E1 Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_T1E1Automatic>  CFG_T1E1AutomaticCfgRegion;
//This is a dummy region that represent T1E1 Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_T1E1OutputCfgRegion;

//This is the region that contains the Gfp Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Gfp>  CFG_GfpCfgRegion;
//This is the region that contains the Gfp Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_GfpAutomatic>  CFG_GfpAutomaticCfgRegion;
//This is a dummy region that represent Gfp Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_GfpOutputCfgRegion;
//This is the region that contains the GFP protection configuration Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_GfpProt>  CFG_GfpProtCfgRegion;

//This is the region that contains the Vcg Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Vcg>  CFG_VcgCfgRegion;
//This is a dummy region that represent Vcg Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_VcgOutputCfgRegion;

//This is the region that contains the Hop Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Hop>  CFG_HopCfgRegion;
//This is the region that contains the Hop Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_HopAutomatic>  CFG_HopAutomaticCfgRegion;
//This is a dummy region that represent Hop Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_HopOutputCfgRegion;

//This is the region that contains the Layer2 Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Layer2>  CFG_Layer2CfgRegion;
//This is a dummy region that represent Layer2 Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_Layer2OutputCfgRegion;

//This is the region that contains the Mac Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Mac>  CFG_MacCfgRegion;
//This is the region that contains the Mac Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_MacAutomatic>  CFG_MacAutomaticCfgRegion;
//This is a dummy region that represent Mac Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_MacOutputCfgRegion;

//This is the region that contains the Mac Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Misc>  CFG_MiscCfgRegion;
//This is a dummy region that represent Mac Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_MiscOutputCfgRegion;

//This is the region that contains the multishelf switchdomain object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_SwitchDomain> CFG_SwitchDomainCfgRegion;
//This is a dummy region that represent Mac Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_SwitchDomainOutputCfgRegion;


//This is the region that contains the Mac Object.
//typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Mesh>  CFG_MeshCfgRegion;
//This is a dummy region that represent Mac Configuration Output .
//typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_MeshOutputCfgRegion;

//This is the region that contains the Lag Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Lag>  CFG_LagCfgRegion;
//This is a dummy region that represent Lag Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_LagOutputCfgRegion;

//This is the region that contains the Evc Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Evc>  CFG_EvcCfgRegion;
//This is the region that contains the Evc Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_EvcAutomatic>  CFG_EvcAutomaticCfgRegion;
//This is a dummy region that represent Evc Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_EvcOutputCfgRegion;

//This is the region that contains the BandWidth Profile Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Bwpf>  CFG_BwpfCfgRegion;

//This is the region that contains the Control Frame Profile Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Cfpf>  CFG_CfpfCfgRegion;

//This is the region that contains the Ms protection configuration Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_MsProt>  CFG_MsProtCfgRegion;
//This is the region that contains the Ms Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Ms>  CFG_MsCfgRegion;
//This is the region that contains the Ms Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_MsAutomatic>  CFG_MsAutomaticCfgRegion;
//This is a dummy region that represent Ms Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_MsOutputCfgRegion;

//This is the region that contains the Rs Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Rs>  CFG_RsCfgRegion;
//This is the region that contains the Rs Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_RsAutomatic>  CFG_RsAutomaticCfgRegion;
//This is a dummy region that represent Rs Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_RsOutputCfgRegion;

//This is the region that contains the Opt Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Opt> CFG_OptCfgRegion;
//This is the region that contains the Opt Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OptAutomatic> CFG_OptAutomaticCfgRegion;
//This is the region that contains the Opt Automatic Rate Lock Down Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OptAutoRateLock>  CFG_OptAutoRateLockRegion;
//This is a dummy region that represent Opt Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_OptOutputCfgRegion;
//This is the region that contains the OPT protection configuration Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OptProt>  CFG_OptProtCfgRegion;

//This is the region that contains the ODU Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Odu> CFG_OduCfgRegion;
//This is the region that contains the ODU Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OduAutomatic> CFG_OduAutomaticCfgRegion;
//This is a dummy region that represent ODU Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_OduOutputCfgRegion;
//This is the region that contains the ODU Critical Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OduCritical> CFG_OduCfgCriticalRegion;

//This is the region that contains the TCM Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Tcm> CFG_TcmCfgRegion;
//This is the region that contains the TCM Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_TcmAutomatic> CFG_TcmAutomaticCfgRegion;
//This is a dummy region that represent TCM Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_TcmOutputCfgRegion;

//This is the region that contains the OTU Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Otu> CFG_OtuCfgRegion;
//This is the region that contains the OTU Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OtuAutomatic> CFG_OtuAutomaticCfgRegion;
//This is a dummy region that represent OTU Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_OtuOutputCfgRegion;

//This is the region that contains the OCH Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Och> CFG_OchCfgRegion;
//This is the region that contains the OCH Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OchAutomatic> CFG_OchAutomaticCfgRegion;
//This is a dummy region that represent OCH Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object> CFG_OchOutputCfgRegion;
//This is region that represent OCH Configuration History.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OchHistory> CFG_OchHistoryCfgRegion;

typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OchAutoOnSC> CFG_OchAutoCfgOnSCRegion;

//This is the region that contains the OTS Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Ots> CFG_OtsCfgRegion;
//This is the region that contains the OTS Overhead Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OtsOH> CFG_OtsOHCfgRegion;
//This is the region that contains the OTS Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OtsAutomatic> CFG_OtsAutomaticCfgRegion;
//This is the region that contains the OTS Automatic Object for CATPS.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OtsAutomaticTxPwrShut> CFG_OtsAutomaticTxPwrShutRegion;
//This is the region that contains the OTS OCH OH Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OtsOchOHAutomatic> CFG_OtsOchOHAutomaticCfgRegion;
//This is a dummy region that represent OTS Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_OtsOutputCfgRegion;

//This is the region that contains the OMS Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Oms> CFG_OmsCfgRegion;
//This is the region that contains the OMS Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OmsAutomatic> CFG_OmsAutomaticCfgRegion;
//This is the region that contains the OMS Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OmsAutomaticShutdown> CFG_OmsAutomaticShutdownRegion;
//This is the region that contains the OMS Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_OmsAutomaticPwrAdj> CFG_OmsAutomaticPwrAdjRegion;
//This is a dummy region that represent OMS Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_OmsOutputCfgRegion;
//This is the region that contains the Cmm Oos Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_CmmOosAutomatic> CFG_CmmOosAutomaticRegion;

typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_TxOchAutomatic>  CFG_TxOchAutomaticCfgRegion;

//GCC regions definition
//This is the region that contains the Gcc Config Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Gcc>  CFG_GccCfgRegion;
//This is the region that contains the Gcc Automatic Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_GccAutomatic>  CFG_GccAutomaticCfgRegion;
//This is a dummy region that represent Gcc Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_GccOutputCfgRegion;


//IBETH regions definition
//This is the region that contains the IBETH Config Object.
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_IbEth>  CFG_IBETHCfgRegion;
//This is a dummy region that represent IBETH Configuration Output .
typedef TEL_RegionBaseImpWithIndex<CFG_Region, CFG_Object>  CFG_IBETHOutputCfgRegion;

enum CFG_RateLockState
{
    CFG_RATE_DISABLED,
    CFG_RATE_NO_SIGNAL,
    CFG_RATE_NOT_LOCKED,
    CFG_RATE_LOCKED,
	CFG_RATE_WARM_RESTART
};

#define DISPLAY_RATE_LOCK_STATE(state) ((state==CFG_RATE_DISABLED) ? "DISABLED" :\
                                        (state==CFG_RATE_NO_SIGNAL) ? "NO SIGNAL" : \
                                        (state==CFG_RATE_NOT_LOCKED) ? "NOT LOCKED" : \
										(state==CFG_RATE_WARM_RESTART) ? "WARM RESTART" : \
                                        (state==CFG_RATE_LOCKED) ? "LOCKED" : "invalid")


#define CFG_STRING_TO_SIGNAL_TYPE(string) ((!strcmp(string,"oc3"))    ? CT_TEL_SIGNAL_OC3:\
                                           (!strcmp(string,"oc12"))   ? CT_TEL_SIGNAL_OC12:\
                                           (!strcmp(string,"oc48"))   ? CT_TEL_SIGNAL_OC48:\
                                           (!strcmp(string,"oc192"))  ? CT_TEL_SIGNAL_OC192:\
                                           (!strcmp(string,"oc768"))  ? CT_TEL_SIGNAL_OC768:\
                                           (!strcmp(string,"10b8b"))  ? CT_TEL_SIGNAL_10B8B:\
                                           (!strcmp(string,"e1"))     ? CT_TEL_SIGNAL_E1:\
                                           (!strcmp(string,"stm1"))   ? CT_TEL_SIGNAL_STM1:\
                                           (!strcmp(string,"stm4"))   ? CT_TEL_SIGNAL_STM4:\
                                           (!strcmp(string,"stm16"))  ? CT_TEL_SIGNAL_STM16:\
                                           (!strcmp(string,"stm64"))  ? CT_TEL_SIGNAL_STM64:\
                                           (!strcmp(string,"stm256")) ? CT_TEL_SIGNAL_STM256:\
                                           (!strcmp(string,"gopt"))   ? CT_TEL_SIGNAL_GOPT:\
                                           (!strcmp(string,"gbep"))   ? CT_TEL_SIGNAL_GBEP:\
                                           (!strcmp(string,"tgbep"))  ? CT_TEL_SIGNAL_TGBEP: \
                                           (!strcmp(string,"tglan"))  ? CT_TEL_SIGNAL_TGLAN: \
                                           (!strcmp(string,"tglf"))   ? CT_TEL_SIGNAL_TGLAN_FRAME: \
                                           (!strcmp(string,"tglp"))   ? CT_TEL_SIGNAL_TGLAN_PREAMBLE: \
                                           (!strcmp(string,"tglwfs")) ? CT_TEL_SIGNAL_TGLAN_WFS: \
                                           (!strcmp(string,"tglfstd"))? CT_TEL_SIGNAL_TGLAN_FRAME_STD: \
                                           (!strcmp(string,"escon"))  ? CT_TEL_SIGNAL_ESCON: \
                                           (!strcmp(string,"ficon"))  ? CT_TEL_SIGNAL_FICON: \
                                           (!strcmp(string,"ficon2g"))? CT_TEL_SIGNAL_FICON2G: \
                                           (!strcmp(string,"fc"))     ? CT_TEL_SIGNAL_FC: \
                                           (!strcmp(string,"fc1g"))   ? CT_TEL_SIGNAL_FC1G: \
                                           (!strcmp(string,"fc2g"))   ? CT_TEL_SIGNAL_FC2G: \
                                           (!strcmp(string,"fc4g"))   ? CT_TEL_SIGNAL_FC4G: \
                                           (!strcmp(string,"fc10g"))  ? CT_TEL_SIGNAL_TGFC: \
                                           (!strcmp(string,"fc266m")) ? CT_TEL_SIGNAL_FC266M: \
                                           (!strcmp(string,"fc531m")) ? CT_TEL_SIGNAL_FC531M: \
                                           (!strcmp(string,"fc133m")) ? CT_TEL_SIGNAL_FC133M: \
                                           (!strcmp(string,"100bfx")) ? CT_TEL_SIGNAL_100BFX: \
                                           (!strcmp(string,"d1v"))    ? CT_TEL_SIGNAL_D1VIDEO: \
                                           (!strcmp(string,"dvbasi")) ? CT_TEL_SIGNAL_DVBASI: \
                                           (!strcmp(string,"isc"))    ? CT_TEL_SIGNAL_ISC: \
                                           (!strcmp(string,"isc2g"))  ? CT_TEL_SIGNAL_ISC2G: \
                                           (!strcmp(string,"vcg"))    ? CT_TEL_SIGNAL_VCG: \
                                           (!strcmp(string,"dv6000")) ? CT_TEL_SIGNAL_DV6000: \
                                           (!strcmp(string,"sdi"))    ? CT_TEL_SIGNAL_SDI: \
                                           (!strcmp(string,"hdsdi"))  ? CT_TEL_SIGNAL_HDSDI: \
                                           (!strcmp(string,"hdsdi30"))? CT_TEL_SIGNAL_HDSDI30: \
                                           (!strcmp(string,"3gsdi"))  ? CT_TEL_SIGNAL_3GSDI: \
                                           (!strcmp(string,"3gsdi30"))? CT_TEL_SIGNAL_3GSDI30: \
                                           (!strcmp(string,"vs411"))  ? CT_TEL_SIGNAL_VS411: \
                                           (!strcmp(string,"vs811"))  ? CT_TEL_SIGNAL_VS811: \
                                           (!strcmp(string,"odu0"))   ? CT_TEL_SIGNAL_ODU0: \
                                           (!strcmp(string,"odu1"))   ? CT_TEL_SIGNAL_ODU1: \
                                           (!strcmp(string,"odu2"))   ? CT_TEL_SIGNAL_ODU2: \
                                           (!strcmp(string,"odu3"))   ? CT_TEL_SIGNAL_ODU3: \
                                           (!strcmp(string,"otu1"))   ? CT_TEL_SIGNAL_OTU1: \
                                           (!strcmp(string,"otu2"))   ? CT_TEL_SIGNAL_OTU2: \
                                           (!strcmp(string,"otu3"))   ? CT_TEL_SIGNAL_OTU3: \
                                           (!strcmp(string,"otu3e2")) ? CT_TEL_SIGNAL_OTU3e2: \
                                           (!strcmp(string,"otu_tglwfs"))     ? CT_TEL_SIGNAL_OTU_TGLAN_WFS: \
                                           (!strcmp(string,"otu4"))   ? CT_TEL_SIGNAL_OTU4: \
                                           (!strcmp(string,"eth"))    ? CT_TEL_SIGNAL_ETH: \
                                           (!strcmp(string,"eth10"))  ? CT_TEL_SIGNAL_ETH10M: \
                                           (!strcmp(string,"eth100")) ? CT_TEL_SIGNAL_ETH100M: \
                                           (!strcmp(string,"eth1000"))? CT_TEL_SIGNAL_ETH1000M: \
                                           (!strcmp(string,"hge"))    ? CT_TEL_SIGNAL_HGE: \
                                           (!strcmp(string,"hgegfp")) ? CT_TEL_SIGNAL_HGE_GFP: \
                                           (!strcmp(string,"fge"))    ? CT_TEL_SIGNAL_FGE: \
                                           (!strcmp(string,"ds1"))    ? CT_TEL_SIGNAL_DS1:\
                                           (!strcmp(string,"ochp"))   ? CT_TEL_SIGNAL_OCH_P:\
                                           (!strcmp(string,"otu_tgfcwofs"))   ? CT_TEL_SIGNAL_OTU_TGFC_WOFS:\
                                           (!strcmp(string,"otu_tglwofs"))    ? CT_TEL_SIGNAL_OTU_TGLAN_WOFS:  CT_TEL_SIGNAL_UNKNOWN)
                                           

#define CFG_STRING_TO_HOP_SPE_MAPPING(string) ((!strcmp(string,"sts1"))     ? CT_TEL_HOP_MAPPING_STS1:\
                                                (!strcmp(string,"sts3c"))    ? CT_TEL_HOP_MAPPING_STS3C:\
                                                (!strcmp(string,"sts12c"))   ? CT_TEL_HOP_MAPPING_STS12C:\
                                                (!strcmp(string,"sts48c"))   ? CT_TEL_HOP_MAPPING_STS48C:\
                                                (!strcmp(string,"sts192c"))  ? CT_TEL_HOP_MAPPING_STS192C:\
                                                (!strcmp(string,"sts3t"))    ? CT_TEL_HOP_MAPPING_STS3T:\
                                                (!strcmp(string,"sts12t"))   ? CT_TEL_HOP_MAPPING_STS12T:\
                                                (!strcmp(string,"sts48t"))   ? CT_TEL_HOP_MAPPING_STS48T:\
                                                (!strcmp(string,"sts1c22v")) ? CT_TEL_HOP_MAPPING_STS1C22V:\
                                                (!strcmp(string,"concat"))   ? CT_TEL_HOP_MAPPING_CONCAT: CT_TEL_HOP_MAPPING_UNKNOWN)

                           

#define CFG_STRING_TO_VCG_TYPE(string) ((!strcmp(string,"sts1-4v"))   ? CT_TEL_VCG_STS1_4V:\
                                        (!strcmp(string,"sts1-5v"))   ? CT_TEL_VCG_STS1_5V:\
                                        (!strcmp(string,"sts1-10v"))  ? CT_TEL_VCG_STS1_10V:\
                                        (!strcmp(string,"sts1-19v"))  ? CT_TEL_VCG_STS1_19V:\
                                        (!strcmp(string,"sts1-22v"))  ? CT_TEL_VCG_STS1_22V:\
                                        (!strcmp(string,"sts3c-2v"))  ? CT_TEL_VCG_STS3C_2V:\
                                        (!strcmp(string,"sts3c-3v"))  ? CT_TEL_VCG_STS3C_3V:\
                                        (!strcmp(string,"sts3c-6v"))  ? CT_TEL_VCG_STS3C_6V:\
                                        (!strcmp(string,"sts3c-7v"))  ? CT_TEL_VCG_STS3C_7V: CT_TEL_VCG_UNKNOWN)
                                        

#define CFG_STRING_TO_GFP_FRAMING_MODE(string) ((!strcmp(string,"f"))  ? CT_TEL_GFP_FRAMING_FRAMED:\
                                                (!strcmp(string,"t"))  ? CT_TEL_GFP_FRAMING_TRANSPARENT: CT_TEL_GFP_FRAMING_UNKNOWN) 
                                                

#define CFG_STRING_TO_BAND(string)        ((!strcmp(string,"1310"))  ? CT_TEL_1310_NM:\
                                           (!strcmp(string,"1550"))  ? CT_TEL_1550_NM:\
                                           (!strcmp(string,"15xx"))  ? CT_TEL_15xx_NM: CT_TEL_UNKNOWN_BAND)

#define CFG_STRING_TO_FREQ_PLAN(string)   ((!strncmp(string,"44bst",5)) ? CT_TEL_44BST_CHAN_PLAN:\
	                                       (!strncmp(string,"32",2))    ? CT_TEL_32CHAN_PLAN:\
										   (!strncmp(string,"88",2))    ? CT_TEL_88CHAN_PLAN:\
                                           (!strncmp(string,"80oem",5)) ? CT_TEL_80_OEM_CHAN_PLAN:\
                                           (!strncmp(string,"44",2))    ? CT_TEL_44CHAN_PLAN: CT_TEL_UNKNOWN_PLAN)

#define CFG_STRING_TO_TIMING_MODE(string) ((!strncmp(string,"l",1))  ? CT_TEL_LINE_TIMING:\
                                           (!strncmp(string,"e",1))  ? CT_TEL_EXTERNAL_TIMING:\
                                           (!strncmp(string,"t",1))  ? CT_TEL_THROUGH_TIMING:\
                                           (!strncmp(string,"b",1))  ? CT_TEL_LOOPBACK_TIMING:\
                                           (!strncmp(string,"se",2)) ? CT_TEL_SELF_TIMING:\
                                           (!strncmp(string,"m",1))  ? CT_TEL_MATE_TIMING:\
                                           (!strncmp(string,"sp",2)) ? CT_TEL_SPFAB_TIMING: CT_TEL_UNKNOWN_TIMING)
                                          
#define CFG_STRING_TO_TIMING_REF(string)  ((!strncmp(string,"p",1))  ? CT_TEL_CLKSEL_REF_PRIMARY:\
                                           (!strncmp(string,"s",1))  ? CT_TEL_CLKSEL_REF_SECONDARY:\
                                           (!strncmp(string,"i",1))  ? CT_TEL_CLKSEL_REF_INTERNAL: CT_TEL_CLKSEL_REF_UNKNOWN)
                                           

#define CFG_STRING_TO_LINECODE(string)    ((!strncmp(string,"a",1))  ? CT_LineCode_AMI:\
                                           (!strncmp(string,"b",1))  ? CT_LineCode_B8ZS:\
                                           (!strncmp(string,"h",1))  ? CT_LineCode_HDB3: CT_LineCode_ALL) 
                                           
#define CFG_STRING_TO_FRAMINGTYPE(string) ((!strncmp(string,"s",1))  ? CT_FrameFormat_SF:\
                                           (!strncmp(string,"e",1))  ? CT_FrameFormat_ESF:\
										   (!strncmp(string,"c",1))  ? CT_FrameFormat_CRC4:\
                                           (!strncmp(string,"n",1))  ? CT_FrameFormat_NOCRC4: CT_FrameFormat_ALL) 

#define CFG_STRING_TO_SABIT(string)       ((!strncmp(string,"4",1))  ? CT_SaBit_4:\
                                           (!strncmp(string,"5",1))  ? CT_SaBit_5:\
										   (!strncmp(string,"6",1))  ? CT_SaBit_6:\
                                           (!strncmp(string,"7",1))  ? CT_SaBit_7:\
                                           (!strncmp(string,"8",1))  ? CT_SaBit_8: CT_SaBit_UNKNOWN) 
                                           
#define CFG_STRING_TO_REF_TYPE(string)    ((!strncmp(string,"n",1))  ? CT_TEL_MS_TREF_NONE:\
                                           (!strncmp(string,"p",1))  ? CT_TEL_MS_TREF_PRIMARY:\
                                           (!strncmp(string,"s",1))  ? CT_TEL_MS_TREF_SECONDARY: CT_TEL_MS_TREF_UNKNOWN)


// Macros used in converting string to approriate values for test menu
#define CFG_STRING_TO_BER(string)         ((!strcmp(string,"0"))   ? CT_TEL_NO_BER:\
                                           (!strcmp(string,"3"))   ? CT_TEL_E3:\
                                           (!strcmp(string,"4"))   ? CT_TEL_E4:\
                                           (!strcmp(string,"5"))   ? CT_TEL_E5:\
                                           (!strcmp(string,"6"))   ? CT_TEL_E6:\
                                           (!strcmp(string,"7"))   ? CT_TEL_E7:\
                                           (!strcmp(string,"8"))   ? CT_TEL_E8:\
                                           (!strcmp(string,"9"))   ? CT_TEL_E9:\
                                           (!strcmp(string,"10"))  ? CT_TEL_E10:\
                                           (!strcmp(string,"11"))  ? CT_TEL_E11:\
                                           (!strcmp(string,"12"))  ? CT_TEL_E12: CT_TEL_INFINITE_BER)

#define CFG_STRING_TO_DEV(string)      ((!strcmp(string,"dev0"))   ? CT_TEL_DEVICENONE:\
                                        (!strcmp(string,"dev1"))   ? CT_TEL_DEVICE1:\
                                        (!strcmp(string,"dev2"))  ? CT_TEL_DEVICE2:\
                                        (!strcmp(string,"dev3"))  ? CT_TEL_DEVICE3:\
                                        (!strcmp(string,"dev4"))  ? CT_TEL_DEVICE4:\
                                        (!strcmp(string,"dev5"))  ? CT_TEL_DEVICE5:\
                                        (!strcmp(string,"dev6"))  ? CT_TEL_DEVICE6:\
                                        (!strcmp(string,"dev7"))  ? CT_TEL_DEVICE7:\
                                        (!strcmp(string,"dev8"))  ? CT_TEL_DEVICE8:\
                                        (!strcmp(string,"dev9"))  ? CT_TEL_DEVICE9:\
                                        (!strcmp(string,"dev10"))  ? CT_TEL_DEVICE10:\
                                        (!strcmp(string,"4gdev1"))  ? CT_TEL_4GDEVICE1:\
                                        (!strcmp(string,"4gdev2"))  ? CT_TEL_4GDEVICE2:\
                                        (!strcmp(string,"crossa1"))  ? CT_TEL_CROSSOVERA1:\
                                        (!strcmp(string,"crossa2"))  ? CT_TEL_CROSSOVERA2:\
                                        (!strcmp(string,"crossb1"))  ? CT_TEL_CROSSOVERB1:\
                                        (!strcmp(string,"crossb2"))  ? CT_TEL_CROSSOVERB2: CT_TEL_END_DEVICES)

#define CFG_STRING_TO_SSM_DEV(string)  ((!strcmp(string,"dev0"))      ? CT_TEL_SSM_DEVICENONE:\
                                        (!strcmp(string,"dev1"))      ? CT_TEL_SSM_DEVICE1_D1G:\
                                        (!strcmp(string,"dev2"))      ? CT_TEL_SSM_DEVICE2_D1G:\
                                        (!strcmp(string,"dev3"))      ? CT_TEL_SSM_DEVICE3_D1G:\
                                        (!strcmp(string,"dev4"))      ? CT_TEL_SSM_DEVICE4_D1G:\
                                        (!strcmp(string,"dev5"))      ? CT_TEL_SSM_DEVICE5_D1G:\
                                        (!strcmp(string,"dev6"))      ? CT_TEL_SSM_DEVICE6_D1G:\
                                        (!strcmp(string,"dev7"))      ? CT_TEL_SSM_DEVICE7_D1G:\
                                        (!strcmp(string,"dev8"))      ? CT_TEL_SSM_DEVICE8_D1G:\
                                        (!strcmp(string,"dev9"))      ? CT_TEL_SSM_DEVICE9_D1G:\
                                        (!strcmp(string,"dev10"))     ? CT_TEL_SSM_DEVICE10_D1G:\
                                        (!strcmp(string,"dev11"))     ? CT_TEL_SSM_DEVICE11_D1G:\
                                        (!strcmp(string,"dev12"))     ? CT_TEL_SSM_DEVICE12_D1G:\
                                        (!strcmp(string,"10gdev13"))  ? CT_TEL_SSM_DEVICE13_D10G:\
                                        (!strcmp(string,"sdev1"))     ? CT_TEL_SSM_DEVICE1_S2G:\
                                        (!strcmp(string,"sdev2"))     ? CT_TEL_SSM_DEVICE2_S2G:\
                                        (!strcmp(string,"sdev3"))     ? CT_TEL_SSM_DEVICE3_S2G:\
                                        (!strcmp(string,"sdev4"))     ? CT_TEL_SSM_DEVICE4_S2G:\
                                        (!strcmp(string,"sdev5"))     ? CT_TEL_SSM_DEVICE5_S2G:\
                                        (!strcmp(string,"sdev6"))     ? CT_TEL_SSM_DEVICE6_S2G:\
                                        (!strcmp(string,"sdev7"))     ? CT_TEL_SSM_DEVICE7_S2G:\
                                        (!strcmp(string,"sdev8"))     ? CT_TEL_SSM_DEVICE8_S2G:\
                                        (!strcmp(string,"sdev9"))     ? CT_TEL_SSM_DEVICE9_S2G:\
                                        (!strcmp(string,"sdev10"))    ? CT_TEL_SSM_DEVICE10_S2G:\
                                        (!strcmp(string,"s10gdev11")) ? CT_TEL_SSM_DEVICE11_S10G: CT_TEL_SSM_END_DEVICES)


#define CFG_STRING_TO_TRANSFER_MODE(string)     ((!strncmp(string,"ui",2))  ? CT_LPF_UITS:\
                                                 (!strncmp(string,"ai",2))  ? CT_LPF_AITS:\
                                                 (!strncmp(string,"qo",2))  ? CT_LPF_QOS: CT_LPF_UNKNOWN)


#define CFG_STRING_TO_SIDE_ASSIGNMENT(string)   ((!strncmp(string,"us",2))  ? CT_LPF_User:\
                                                 (!strncmp(string,"ne",2))  ? CT_LPF_Network:\
                                                 (!strncmp(string,"au",2))  ? CT_LPF_Auto: CT_LPF_Unknown)


#define CFG_STRING_TO_DCC_OPERATION(string)     ((!strncmp(string,"cr",2))  ? CT_DCC_CREATE:\
                                                 (!strncmp(string,"ed",2))  ? CT_DCC_EDIT:\
                                                 (!strncmp(string,"de",2))  ? CT_DCC_DELETE:\
                                                 (!strncmp(string,"re",2))  ? CT_DCC_REFRESH: CT_DCC_NONE)


#define CFG_STRING_TO_DCC_SEQUENCE(string)      ((!strncmp(string,"tidbe",5))     ? CT_DCC_TID_BEGIN:\
                                                 (!strncmp(string,"tidco",5))     ? CT_DCC_TID_COMMIT:\
                                                 (!strncmp(string,"routerbe",8))  ? CT_DCC_ROUTER_BEGIN:\
                                                 (!strncmp(string,"routerco",8))  ? CT_DCC_ROUTER_COMMIT:\
                                                 (!strncmp(string,"tarpbe",6))    ? CT_DCC_TARP_BEGIN:\
                                                 (!strncmp(string,"tarpco",6))    ? CT_DCC_TARP_COMMIT:\
                                                 (!strncmp(string,"linkbe",6))    ? CT_DCC_LINK_BEGIN:\
                                                 (!strncmp(string,"linkco",6))    ? CT_DCC_LINK_COMMIT: CT_DCC_IDLE)

#define CFG_STRING_TO_DT_MODE(string)           ((!strncmp(string,"no",2))    ? CT_DT_SOURCE_NONE:\
                                                 (!strncmp(string,"srca",4))  ? CT_DT_SOURCE_A:\
												 (!strncmp(string,"srcb",4))  ? CT_DT_SOURCE_B:\
                                                 (!strncmp(string,"ab",2))    ? CT_DT_SOURCE_A_B: CT_DT_SOURCE_UNKNOWN)

#define CFG_STRING_TO_TL_ADDR_TYPE(string)       ((!strncmp(string,"UnN",3))  ? CT_DCC_TL_UNNUMBERED:\
                                                 (!strncmp(string,"Num",3))  ? CT_DCC_TL_NUMBERED:\
                                                 (!strncmp(string,"Non",3))  ? CT_DCC_TL_NONE: CT_DCC_TL_UNKNOWN_TYPE)

#define CFG_STRING_TO_DUPLEX_MD(string)         ((!strncmp(string,"full",4))  ? CT_TEL_MAC_FULL_DUPLEX:\
                                                 (!strncmp(string,"half",4))  ? CT_TEL_MAC_HALF_DUPLEX: CT_TEL_MAC_DUPLEX_UNKNOWN)

#define CFG_STRING_TO_COLOR_MD(string)          ((!strncmp(string,"blind",5))  ? CT_TEL_BW_CM_BLIND:\
                                                 (!strncmp(string,"aware",5))  ? CT_TEL_BW_CM_AWARE: CT_TEL_BW_CM_UNKNOWN)

#define CFG_STRING_TO_METER_TYPE(string)        ((!strncmp(string,"srTCM",5))  ? CT_TEL_BW_METERTYPE_srTCM:\
                                                 (!strncmp(string,"trTCM",5))  ? CT_TEL_BW_METERTYPE_trTCM: CT_TEL_BW_METERTYPE_UNKNOWN)

#define CFG_STRING_TO_VCAT_TYPE(string)         ((!strncmp(string,"sts1",4))   ? CT_TEL_VCAT_STS1:\
                                                 (!strncmp(string,"sts3c",5))  ? CT_TEL_VCAT_STS3C:\
                                                 (!strncmp(string,"vc4",3))    ? CT_TEL_VCAT_VC3:\
                                                 (!strncmp(string,"vc5",3))    ? CT_TEL_VCAT_VC4: CT_TEL_VCAT_UNKNOWN)

#define CFG_STRING_TO_ADVT_FLWCTRL(string)      ((!strncmp(string,"nopause",7))   ? CT_TEL_MAC_ADFLW_NOPAUSE:\
                                                 (!strncmp(string,"spause",6))    ? CT_TEL_MAC_ADFLW_SPAUSE:\
                                                 (!strncmp(string,"apause",6))    ? CT_TEL_MAC_ADFLW_APAUSE:\
                                                 (!strncmp(string,"bpause",6))    ? CT_TEL_MAC_ADFLW_BPAUSE: CT_TEL_MAC_ADFLW_UNKNOWN)

#define CFG_STRING_TO_FLOWCTRL(string)          ((!strncmp(string,"txrx",4))   ? CT_TEL_MAC_FLWTXRX:\
                                                 (!strncmp(string,"tx",2))     ? CT_TEL_MAC_FLWTX:\
                                                 (!strncmp(string,"rx",2))     ? CT_TEL_MAC_FLWRX: CT_TEL_MAC_FLW_UNKNOWN)

#define CFG_STRING_TO_SUBTYPE(string)           ((!strncmp(string,"eth",3))   ? FAC_SUBTYPE_ETH:\
                                                 (!strncmp(string,"lag",3))   ? FAC_SUBTYPE_LAG: FAC_SUBTYPE_UNKNOWN)

#define CFG_STRING_TO_LNKRATE(string)           ((!strncmp(string,"6gbs",4))   ? CT_TEL_LinkRate6Gbs:\
                                                 (!strncmp(string,"3gbs",4))   ? CT_TEL_LinkRate3Gbs:\
                                                 (!strncmp(string,"sonet",5))  ? CT_TEL_LinkRateSonet:\
                                                 (!strncmp(string,"pkt",3))    ? CT_TEL_LinkRatePkt:\
                                                 (!strncmp(string,"5gbs",4))   ? CT_TEL_LinkRate5Gbs: CT_TEL_LinkRateNone)

#define CFG_STRING_TO_QLOVERRIDE(string)        ((!strncmp(string,"dnu",3))    ? CT_QualityLevelOverride_DNU:\
                                                 (!strncmp(string,"prc",3))    ? CT_QualityLevelOverride_PRC:\
                                                 (!strncmp(string,"sec",3))    ? CT_QualityLevelOverride_SEC:\
                                                 (!strncmp(string,"ssua",4))   ? CT_QualityLevelOverride_SSU_A:\
                                                 (!strncmp(string,"ssub",4))   ? CT_QualityLevelOverride_SSU_B:\
                                                 (!strncmp(string,"stu",3))    ? CT_QualityLevelOverride_STU: CT_QualityLevelOverride_DISABLED)

#define CFG_STRING_TO_RXSSM(string)             ((!strncmp(string,"dnu",3))    ? CT_RxSsm_DNU:\
                                                 (!strncmp(string,"prc",3))    ? CT_RxSsm_PRC:\
                                                 (!strncmp(string,"sec",3))    ? CT_RxSsm_SEC:\
                                                 (!strncmp(string,"ssua",4))   ? CT_RxSsm_SSUA:\
                                                 (!strncmp(string,"ssub",4))   ? CT_RxSsm_SSUB:\
                                                 (!strncmp(string,"stu",3))    ? CT_RxSsm_STU: CT_RxSsm_DNU)


#define CFG_STRING_TO_CBRMAP(string)            ((!strncmp(string,"async",5))   ? ASYNC_CBR_MAPPING:\
                                                 (!strncmp(string,"sync",4))   ? BIT_SYNC_CBR_MAPPING: NULL_MAPPING)

#define CFG_STRING_TO_IVCG_FORMAT(string)       ((!strncmp(string,"gfp",3))       ? CT_TEL_IVCG_FRAMEFORMAT_GFP:\
                                                 (!strncmp(string,"bitx86",6))   ? CT_TEL_IVCG_FRAMEFORMAT_BITX86:\
                                                 (!strncmp(string,"bytex86",7))  ? CT_TEL_IVCG_FRAMEFORMAT_BYTEX86: CT_TEL_IVCG_FRAMEFORMAT_UNKNOWN)



#define CFG_STRING_TO_ODU_TYPE(string)          ((!strncmp(string,"reg",3))  ? CT_ODU_REGULAR_TYPE:\
                                                 (!strncmp(string,"wi",2))   ? CT_ODU_POOL_ODU_WITHIN_CLIENT:\
                                                 (!strncmp(string,"in",2))   ? CT_ODU_POOL_CLIENT_INSIDE_ODU:\
                                                 (!strncmp(string,"mux",3))  ? CT_ODU_POOL_MUX:\
                                                 (!strncmp(string,"not",3))  ? CT_ODU_POOL_NOT_ASSIGNED: CT_ODU_UNKNOWN_TYPE)

#define CFG_STRING_TO_LACP_TIMEOUT(string)      ((!strncmp(string,"sho",3))  ? CT_TEL_LacpTimeoutMode_SHORT:\
                                                 (!strncmp(string,"lon",3))  ? CT_TEL_LacpTimeoutMode_LONG:\
                                                 (!strncmp(string,"all",3))  ? CT_TEL_LacpTimeoutMode_ALL: CT_TEL_LacpTimeoutMode_UNKNOWN)

#define CFG_STRING_TO_PARTI_MODE(string)        ((!strncmp(string,"act",3))  ? CT_TEL_LacpPartiMode_ACTIVE:\
                                                 (!strncmp(string,"sta",3))  ? CT_TEL_LacpPartiMode_STATIC:\
                                                 (!strncmp(string,"pas",3))  ? CT_TEL_LacpPartiMode_PASSIVE:\
                                                 (!strncmp(string,"all",3))  ? CT_TEL_LacpPartiMode_ALL: CT_TEL_LacpPartiMode_UNKNOWN)

#define CFG_STRING_TO_MAC_MODE(string)          ((!strncmp(string,"uni",3))  ? CT_TEL_MacMode_UNICAST:\
                                                 (!strncmp(string,"mul",3))  ? CT_TEL_MacMode_MULTICAST:\
                                                 (!strncmp(string,"all",3))  ? CT_TEL_MacMode_ALL: CT_TEL_MacMode_UNKNOWN)


#define CFG_STRING_TO_CLOCK_TYPE(string)        ((!strcmp(string,"g709"))     ? CT_TEL_CLK_G709:\
                                                 (!strcmp(string,"ovr_fs"))   ? CT_TEL_CLK_OVRCLKFS:\
                                                 (!strcmp(string,"ovr_nofs")) ? CT_TEL_CLK_OVRCLKNOFS:\
                                                 (!strcmp(string,"ovr_fc"))   ? CT_TEL_CLK_OVRCLKFC:\
                                                 (!strcmp(string,"odu3"))     ? CT_TEL_CLK_ODU3:\
                                                 (!strcmp(string,"odu3e2"))   ? CT_TEL_CLK_ODU3e2: CT_TEL_CLK_UNKNOWN)


#define CFG_STRING_TO_TS_SIZE(string)           ((!strcmp(string,"2G5"))     ? CT_TEL_TS_2G5:\
                                                 (!strcmp(string,"1G25"))    ? CT_TEL_TS_1G25: CT_TEL_TS_UNKNOWN)

#define CFG_STRING_TO_TCM_MODE(string)           ((!strncmp(string,"src_snk",7))    ? CT_TCM_MODE_SRC_SNK:\
                                                 (!strncmp(string,"src",3))        ? CT_TCM_MODE_SOURCE:\
                                                 (!strncmp(string,"snk",3))        ? CT_TCM_MODE_SINK:\
                                                 (!strncmp(string,"snk_nim",7))    ? CT_TCM_MODE_SNK_NIM:\
                                                 (!strncmp(string,"src_snk_nim",11))? CT_TCM_MODE_SRC_SNK_NIM:\
                                                 (!strncmp(string,"unknown",6))    ? CT_TCM_MODE_UNKNOWN: CT_TCM_MODE_NONE)

#define CFG_STRING_TO_GCC_TYPE(string)           ((!strncmp(string,"gcc0",4))  ? CT_GCC_0:\
                                                  (!strncmp(string,"gcc1",4))  ? CT_GCC_1:\
                                                  (!strncmp(string,"gcc2",4))  ? CT_GCC_2:\
                                                  (!strncmp(string,"gcc12",5)) ? CT_GCC_1_2:\
                                                  (!strncmp(string,"none",4))   ? CT_GCC_NONE: CT_GCC_UNKNOWN)

#endif /* CFG_DEFINITIONS_H */

