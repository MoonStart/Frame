//Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef MON_DEFINITIONS_INCLUDED
#define MON_DEFINITIONS_INCLUDED

#include <TelCommon/TEL_RegionBaseImpWithIndex.h>
#include <CommonTypes/CT_Telecom.h>

// Macros used for defects monitoring/filtering.
#define IS_RISING_EDGE(prevfiltered, curraw, intRF)             \
        (                                                       \
            ( (intRF) && (!(prevfiltered) || (curraw) ) )   ||  \
            ( (!(prevfiltered)) && (curraw) )                   \
        )

#define IS_DIFFERENT(value1, value2)                            \
        (                                                       \
            ( (value1) != (value2) )                            \
        )

#define HAS_CHANGED(previous, current, transition)              \
        (                                                       \
            IS_DIFFERENT(previous, current) || (transition)     \
        )

#define HAS_GLITCHED(previous, current, transition)             \
        (                                                       \
            ((previous)==(current)) && (transition)             \
        )


// Forward Declarator
class MON_DcclDefects;
class MON_DrtrDefects;
class MON_SyncDefects;
class MON_T1E1Defects;
class MON_VcgDefects;
class MON_AltVcgDefects;
class MON_GfpDefects;
class MON_HopDefects;
class MON_MacDefects;
class MON_MsDefects;
class MON_RsDefects;
class MON_OptDefects;
class MON_OtuDefects;
class MON_OduDefects;
class MON_TcmDefects;
class MON_OtsDefects;
class MON_OtsOHDefects;
class MON_OmsDefects;
class MON_OchDefects;
class MON_GccDefects;
class MON_OchMainDefects;
class MON_OtsOchOHDefects;
class MON_DcclConfig;
class MON_DrtrConfig;
class MON_T1E1Config;
class MON_RmonConfig;
class MON_VcgConfig;
class MON_HopConfig;
class MON_MsConfig;
class MON_RsConfig;
class MON_OchConfig;
class MON_OtuConfig;
class MON_OduConfig;
class MON_TcmConfig;
class MON_OptConfig;
class MON_OptProtConfig;
class MON_GccConfig;
class MON_IBETHConfig;
class MON_OtsConfig;
class MON_GfpConfig;
class MON_DcclStatus;
class MON_DrtrStatus;
class MON_SyncStatus;
class MON_T1E1Status;
class MON_RmonStatus;
class MON_HopStatus;
class MON_MsStatus;
class MON_RsStatus;
class MON_OptStatus;
class MON_OtuStatus;
class MON_OduStatus;
class MON_TcmStatus;
class MON_OchStatus;
class MON_OchAltStatus;
class MON_OtsStatus;
class MON_OmsStatus;
class MON_MacStatus;
class MON_VcgStatus;
class MON_TxOptStatus;
class MON_GccStatus;
class MON_IBETHStatus;
class MON_DcclCounters;
class MON_DrtrCounters;
class MON_RmonCounters;
class MON_GfpCounters;
class MON_HopCounters;
class MON_MsCounters;
class MON_RsCounters;
class MON_OtuCounters;
class MON_OduCounters;
class MON_TcmCounters;
class MON_GccCounters;
class MON_TxOptRequest;
class MON_OchRequest;
class MON_PilotToneProcessorRequest;
class MON_TxOptResult;
class MON_OchResult;

class MON_Region;

// DEFECTS REGIONS


//This class is the region that hold Dccl defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DcclDefects>      MON_DcclDefectsRegion;
//This class is the region that hold Drtr defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DrtrDefects>      MON_DrtrDefectsRegion;
//This class is the region that hold Sync defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_SyncDefects>      MON_SyncDefectsRegion;
//This class is the region that hold T1E1 defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_T1E1Defects>      MON_T1E1DefectsRegion;
//This class is the region that hold VCG defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_VcgDefects>       MON_VcgDefectsRegion;
//This class is the region that hold VCG defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_AltVcgDefects>    MON_AltVcgDefectsRegion;
//This class is the region that hold GFP defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GfpDefects>       MON_GfpDefectsRegion;
//This class is the region that hold HOP defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_HopDefects>       MON_HopDefectsRegion;
//This class is the region that hold MAC defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MacDefects>       MON_MacDefectsRegion;
//This class is the region that hold MS defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MsDefects>        MON_MsDefectsRegion;
//This class is the region that hold RS defects object.
//##ModelId=3C3B52FD03D0
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RsDefects>        MON_RsDefectsRegion;
//This class is the region that hold optical defects object.
//##ModelId=3C3B52FF0008
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OptDefects>       MON_OptDefectsRegion;
//This class is the region that holds ODU defects object.
//##ModelId=3C3B53000027
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OduDefects>       MON_OduDefectsRegion;
//This class is the region that holds TCM defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TcmDefects>       MON_TcmDefectsRegion;
//This class is the region that holds OTU defects object.
//##ModelId=3C3B53010047
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtuDefects>       MON_OtuDefectsRegion ;
//This class is the region that hold Och defects objects.
//##ModelId=3C3B53020066
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchDefects>       MON_OchDefectsRegion ;
//This class is the region that hold Och Main defects objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchMainDefects>   MON_OchMainDefectsRegion ;
//This class is the region that holds OTS defects object.           
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtsDefects>       MON_OtsDefectsRegion;
//This class is the region that holds OTS OH defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtsOHDefects>     MON_OtsOHDefectsRegion;
//This class is the region that holds OTS defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OmsDefects>       MON_OmsDefectsRegion;
//This class is the region that holds OTS OCH OH defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtsOchOHDefects>  MON_OtsOchOHDefectsRegion;
//This class is the region that holds GCC defects object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GccDefects>       MON_GccDefectsRegion;

// STATUS REGIONS

//This class is the region that hold Dccl status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DcclStatus>    MON_DcclStatusRegion;
//This class is the region that hold Drtr status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DrtrStatus>    MON_DrtrStatusRegion;
//This class is the region that hold SYNC status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_SyncStatus>    MON_SyncStatusRegion;
//This class is the region that hold T1E1 status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_T1E1Status>    MON_T1E1StatusRegion;
//This class is the region that hold Rmon status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RmonStatus>    MON_RmonStatusRegion;
//This class is the region that hold HOP status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_HopStatus>     MON_HopStatusRegion;
//This class is the region that hold MS status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MsStatus>      MON_MsStatusRegion ;
//This class is the region that hold RS status object.
//##ModelId=3C3B53030086
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RsStatus>      MON_RsStatusRegion ;
//This class is the region that hold optical status object.
//##ModelId=3C3B530400A5
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OptStatus>     MON_OptStatusRegion;
//This class is the region that hold optical transmission status object.
//##ModelId=3C3B530400A5
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TxOptStatus>   MON_TxOptStatusRegion;
//This class is the region that holds ODU status object.
//##ModelId=3C3B530500C5
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OduStatus>     MON_OduStatusRegion;
//This class is the region that holds TCM status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TcmStatus>     MON_TcmStatusRegion;
//This class is the region that holds OTU status object.
//##ModelId=3C3B530600E4
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtuStatus>     MON_OtuStatusRegion;
//This class is a region that hold the Och status objects.
//##ModelId=3C3B53070104
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchStatus>     MON_OchStatusRegion;
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchAltStatus>  MON_OchAltStatusRegion;
//This class is the region that holds OTS status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtsStatus>     MON_OtsStatusRegion;
//This class is the region that holds OTS status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OmsStatus>     MON_OmsStatusRegion;

//This class is the region that holds Mac status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MacStatus>     MON_MacStatusRegion;

//This class is the region that holds Mac status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_VcgStatus>     MON_VcgStatusRegion;
//This class is the region that holds GCC status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GccStatus>     MON_GccStatusRegion;

//This class is the region that holds IBETH status object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_IBETHStatus>   MON_IBETHStatusRegion;

// COUNTERS REGIONS

//This class is the region that hold Dccl counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DcclCounters>  MON_DcclCountersRegion;
//This class is the region that hold Drtr counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DrtrCounters>  MON_DrtrCountersRegion;
//This class is the region that hold RMON counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RmonCounters>  MON_RmonCountersRegion;
//This class is the region that hold GFP counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GfpCounters>   MON_GfpCountersRegion;
//This class is the region that hold HOP counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_HopCounters>   MON_HopCountersRegion;
//This class is the region that hold MS counters object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MsCounters>    MON_MsCountersRegion;
//This class is the region that hold RS counters object.
//##ModelId=3C3B53080123
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RsCounters>    MON_RsCountersRegion;
//This class is the region that hold ODU counter object.
//##ModelId=3C3B53090143
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OduCounters>   MON_OduCountersRegion;
//This class is the region that hold TCM counter object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TcmCounters>   MON_TcmCountersRegion;
//This class is the region that holds OTU counter object.
//##ModelId=3C3B530A0162
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtuCounters>   MON_OtuCountersRegion;
//This class is the region that hold GCC counter object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GccCounters>   MON_GccCountersRegion;

// CONFIG REGIONS

//This class is the region that hold Dccl config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DcclConfig>    MON_DcclConfigRegion;
//This class is the region that hold Drtr config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_DrtrConfig>    MON_DrtrConfigRegion;
//This class is the region that hold T1E1 config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_T1E1Config>    MON_T1E1ConfigRegion;
//This class is the region that hold RMON config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RmonConfig>    MON_RmonConfigRegion;
//This class is the region that hold Vcg config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_VcgConfig>     MON_VcgConfigRegion;
//This class is the region that hold HOP config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_HopConfig>     MON_HopConfigRegion;
//This class is the region that hold MS configuration object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_MsConfig>      MON_MsConfigRegion;
//This class is the region that hold RS configuration object.
//##ModelId=3C3B530B0182
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_RsConfig>      MON_RsConfigRegion;
//This class is the region that hold ODU configuration object.
//##ModelId=3C3B530D01C1
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OduConfig>     MON_OduConfigRegion;
//This class is the region that hold TCM configuration object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TcmConfig>     MON_TcmConfigRegion;
//This class is the region that hold OTU configuration object.
//##ModelId=3C3B530E01D6
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtuConfig>     MON_OtuConfigRegion;
//This class is the region that hold OPT configuration object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OptConfig>     MON_OptConfigRegion;
//This class is the region that hold OPT protection config object.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OptProtConfig> MON_OptProtConfigRegion;
//This class is the region that hold Och configuration objects.
//##ModelId=3C3B530F01F5
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchConfig>     MON_OchConfigRegion;
//This class is the region that hold Ots configuration objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OtsConfig>     MON_OtsConfigRegion;
//This class is the region that hold GCC configuration objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GccConfig>     MON_GccConfigRegion;
//This class is the region that hold GCC configuration objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_GfpConfig>     MON_GfpConfigRegion;
//This class is the region that hold GCC configuration objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_IBETHConfig>   MON_IBETHConfigRegion;


// REQUEST REGIONS

//This class is the region that hold Tx OPT on-demand request objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TxOptRequest>  MON_TxOptRequestRegion;
//This class is the region that hold Och on-demand request objects.
//##ModelId=3C4826D70395
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchRequest>    MON_OchRequestRegion;
//##ModelId=3C7170F3006C
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_PilotToneProcessorRequest>  MON_PilotToneProcessorRequestRegion;

// RESULT REGIONS

//This class is the region that holds Tx Opt on-demand results objects.
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_TxOptResult>   MON_TxOptResultRegion;
//This class is the region that holds Och on-demand results objects.
//##ModelId=3C4829BA0366
typedef TEL_RegionBaseImpWithIndex<MON_Region, MON_OchResult>     MON_OchResultRegion;


//##ModelId=3C7170F40045
typedef uint32 MON_RequestID;


const uint8  MON_NUMBER_OF_ID_PER_LAMBDA = 3;
const uint32 MON_PT_EXACTMODE_NUM_SAMPLE = 1024;   /* Number of samples for exact mode */
const uint32 MON_PT_FASTMODE_NUM_SAMPLE  = 64;      /* Number of samples for fast mode */
const float  MON_PT_BAND_LOWER_FREQ      = 750500.0;     
const uint32 MON_PT_SIGNAL_BANDWIDTH     = 1008; /* 10000000/9920  -> 0.992 ms per samples -> 1.00806kHz */
const uint32 MON_PT_TONE_BANDWIDTH       = 200;   /* Hz */
const uint32 MON_PT_EXACT_MODE_TONE_NUM_SAMPLE = 202;
   //((PT_EXACTMODE_NUM_SAMPLE*PT_TONE_BANDWIDTH + PT_SIGNAL_BANDWIDTH/2)/PT_SIGNAL_BANDWIDTH)
const uint32 MON_PT_TX_FSK_RATE          = 10 ;          /* Hz */
const uint32 MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING = ((MON_PT_EXACTMODE_NUM_SAMPLE*MON_PT_TX_FSK_RATE   + MON_PT_SIGNAL_BANDWIDTH/2) / MON_PT_SIGNAL_BANDWIDTH);
const uint32 MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING = ((MON_PT_EXACTMODE_NUM_SAMPLE*MON_PT_TX_FSK_RATE*2 + MON_PT_SIGNAL_BANDWIDTH/2) / MON_PT_SIGNAL_BANDWIDTH);
const float  MON_PT_TX_FSK_BASE_HARMONIC_POWER_FACTOR  = 0.53143f;     /* 53% of original tone power */

const CT_TEL_mBm TEL_DEFAULT_OCH_POWER_DEBOUNCE_THRESHOLD = 250;	//2.50dBm
const time_t	 TEL_DEFAULT_OCH_POWER_DEBOUNCE_PERIOD    = 2;		//2sec

const CT_TEL_mBm TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_THRESHOLD = 250;  //2.50dBm
const time_t	 TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_PERIOD    = 2;    //2sec

enum MON_RelativeTraceId
{
    MON_ID_FIRST=0,
    MON_ID_SECOND,
    MON_ID_DEBUG,
    MON_ID_NOISE,
    MON_ID_UNKNOWN
};
#define DISPLAY_REL_TRACE_ID(id)  ((id==MON_ID_FIRST) ? "FIRST" :\
                                   (id==MON_ID_SECOND) ? "SECOND" : \
                                   (id==MON_ID_DEBUG) ? "DEBUG" : \
                                   (id==MON_ID_NOISE) ? "NOISE" : \
                                   (id==MON_ID_UNKNOWN) ? "UNKNOWN" : "invalid")

const CT_TEL_mBm TEL_DEFAULT_MINIMUM_SN_RATIO = 900; //9 dB
const CT_TEL_mBm TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD = -3800; //was -27 dB
const CT_TEL_mBm TEL_DEFAULT_MINIMUM_SN_RATIO_OSA = 100;
const CT_TEL_mBm TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA = -1000;
const CT_TEL_mBm TEL_DEFAULT_OVERLOAD_THRESHOLD = 0; //0 dBm
// Delta used to clear the Optical Signal Degrade Power Defect (+2dBm over the threshold)
const CT_TEL_mBm CT_TEL_SDPWR_THRESHOLD_CLEARING_DELTA = 200;  // 2dBm


enum eMON_Event
{
    MON_PWR_SPIKE			= 1, //a power spike repored by the hardware
    MON_UNKNOWN                  //unknown condition
};

#define DISPLAY_MON_EVENT(x) (\
    (x) == MON_PWR_SPIKE			? "MON_PWR_SPIKE" : \
                                      "MON_UNKNOWN  ")

#define DISPLAY_MON_EVENT_DES(x) (\
    (x) == MON_PWR_SPIKE			? "OCH Power spike repored by the hardware" : \
                                      "Unknown condition")

// Macros used in converting string to approriate values for test menu
#define MON_STRING_TO_BER(string) ((!strcmp(string,"3"))   ? CT_TEL_E3:\
                                   (!strcmp(string,"4"))   ? CT_TEL_E4:\
                                   (!strcmp(string,"5"))   ? CT_TEL_E5:\
                                   (!strcmp(string,"6"))   ? CT_TEL_E6:\
                                   (!strcmp(string,"7"))   ? CT_TEL_E7:\
                                   (!strcmp(string,"8"))   ? CT_TEL_E8:\
                                   (!strcmp(string,"9"))   ? CT_TEL_E9:\
                                   (!strcmp(string,"10"))  ? CT_TEL_E10:\
                                   (!strcmp(string,"11"))  ? CT_TEL_E11:\
                                   (!strcmp(string,"12"))  ? CT_TEL_E12: CT_TEL_INFINITE_BER)
#endif /* MON_DEFINITIONS_INCLUDED */

