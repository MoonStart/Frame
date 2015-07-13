#ifndef __TSPII_OchOsaDebounce__
#define __TSPII_OchOsaDebounce__
/***********************************************************************
    Copyright (C) 2012. Tellabs, Inc. All Rights Reserved.

Name
    TSPII_CntrlOchOsaDebounce.h

Description
    Class and methods to validate the OCH power readings obtained by the OCM
    devices to eliminate "flase" readings or what MON calls spike detection.

    This class is intended to be included by other classes and provides the
    spike detection and menu interfaces similar to what MON implements.

Notes

***********************************************************************/
#include "ss_gdef.h"    // Tellabs std types
#include "CommonTypes/CT_Telecom.h"
#include "ExecutionSupport/FC_Action.h"
#include "ExecutionSupport/FC_PeriodicProcess.h"
#include <time.h>

namespace TSPIIOchOsaDebounce
{
    const uint32        OCH_PWR_HISTORY_SIZE = 30;
    const CT_TEL_mBm    TEL_DEFAULT_OCH_POWER_DEBOUNCE_THRESHOLD = 250;
    const time_t        TEL_DEFAULT_OCH_POWER_DEBOUNCE_PERIOD    = 2;
    const CT_TEL_mBm    TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_THRESHOLD = 250;
    const time_t        TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_PERIOD    = 2;


    enum eSpikeEvent
    {
        UNKNOWN_EVT     = 0,    //unknown condition
        PWR_SPIKE_EVT   = 1     //a power spike reported by the hardware
    };

    typedef struct
    {
        CT_TEL_mBm  prevPwr;
        CT_TEL_mBm  curPwr;
        time_t      myTimestamp;
        eSpikeEvent event;
    } tHistEvent;

    typedef struct
    {
        tHistEvent myHistMax;
        tHistEvent myHistMin;
        tHistEvent myHistEvent[OCH_PWR_HISTORY_SIZE];
        uint32     myHistoryIndex;
        CT_TEL_mBm theCurPwr;
        CT_TEL_mBm theCurSnr;
        CT_TEL_mBm thePrevPwr;
        time_t     prevSampleTime;
    } tHistory;
}

#define DISPLAY_OCH_EVENT(x) (\
    (x) == PWR_SPIKE_EVT        ? "PWR_SPIKE" : \
                                  "UNKNOWN  ")

#define DISPLAY_OCH_EVENT_DES(x) (\
    (x) == PWR_SPIKE _EVT       ? "OCH Power spike reported by the hardware" : \
                                  "Unknown condition")

class TSPII_OchOsaDebounce
{
    public:
        TSPII_OchOsaDebounce( void );
        virtual ~TSPII_OchOsaDebounce();


        void Update(uint32 theIndex, CT_TEL_mBm aPwr, CT_TEL_mBm aSnr);
        CT_TEL_mBm GetPower( uint32 theIndex );
        CT_TEL_mBm GetOsnr( uint32 theIndex );
        void ClearAllHistory(void);
        void ClearHistoryForAllCh(void);
        void ClearHistoryForCh(uint32 theIndex);
        void RecordHistory(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime, TSPIIOchOsaDebounce::eSpikeEvent event);
        void RecordHysteresis(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime);
        void DisplayHistoryForAllCh();
        void DisplayHistoryForCh(uint32 theIndex);
        void DisplayHysteresis();

        void SetNumberOfWavelengths( uint32 theNumber ) {myNumberOfWavelengths = theNumber;}
        void SetPeriod( time_t thePeriod ) {myOchPowerDebouncePeriod = thePeriod;}
        unsigned long GetPeriod(void) {return myOchPowerDebouncePeriod;}
        void SetThreshold(CT_TEL_mBm theThresh) {myOchPowerDebounceThreshold = theThresh;}
        CT_TEL_mBm GetThreshold(void) {return myOchPowerDebounceThreshold;}

        void DisplayHelp(void);
        void Menu(int argc, char **argv);

    private:
        void GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len);

        CT_TEL_mBm      myOchPowerDebounceThreshold;
        time_t          myOchPowerDebouncePeriod;
        uint32          myHistoryDepth;
        uint32          myNumberOfWavelengths;

        TSPIIOchOsaDebounce::tHistory myHistory[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
};

#endif // __TSPII_OchOsaDebounce__
// vim:sw=4:expandtab:cindent:
