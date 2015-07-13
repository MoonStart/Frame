/***********************************************************************
    Copyright (C) 2012. Tellabs, Inc. All Rights Reserved.

Name
    TSPII_OchOsaDebounce.cpp

Description
    Implement OSA power reading debounce logic similar to the service
    Monitoring provided. This code is copied from Monitoring and
    implmented as a generic class that might be used anywhere.

Notes

Contents

***********************************************************************/
#include "TSPII_OchOsaDebounce.h"
#include "ErrorService/FC_Error.h"
#include "ExecutionSupport/FC_EsReason.h"
#include "CsPii/CSPII_CardIF.h"
#include "CsPii/CSPII_ShelfIF.h"

// for debug purposes
bool gPrintOchOsaDebounce = false;

using namespace TSPIIOchOsaDebounce;

/***********************************************************************
Name
    ctor/dtor

Synopsis
    TSPII_OchOsaDebounce(uint32 theNumberOfWavelengths,
                              uint32 theHistoryDepth )
    ~TSPII_OchOsaDebounce()

Description

Inputs

Returns
    n/a

----------------------------------------------------------------------*/
TSPII_OchOsaDebounce::TSPII_OchOsaDebounce( void ) :
    myOchPowerDebounceThreshold(TEL_DEFAULT_OCH_POWER_DEBOUNCE_THRESHOLD),
    myOchPowerDebouncePeriod(TEL_DEFAULT_OCH_POWER_DEBOUNCE_PERIOD),
    myHistoryDepth(OCH_PWR_HISTORY_SIZE),
    myNumberOfWavelengths(CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY)
{
    if(CSPII_ShelfIF::GetInstance()->IsFPNANOShelfType())
    {
        myOchPowerDebounceThreshold = TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_THRESHOLD;
        myOchPowerDebouncePeriod = TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_PERIOD;
    }
    ClearAllHistory();
}

TSPII_OchOsaDebounce::~TSPII_OchOsaDebounce()
{
}

/***********************************************************************
Name
    Update

Synopsis
    Update(uint32 theIndex, CT_TEL_mBm curPwr, CT_TEL_mBm curSnr)

Description
    Update the history tables and debounce using the power and OSNR 
    values provided. A caller presumably reads power/OSNR from
    hardware and calls this method to update the history and perform
    the debounce algorithm.

Inputs
    theIndex -  0 based channel number. should use the standard channel
                numbers not a HW channel number.
    curPwr -    the MBM power value read from HW
    curSnr -    the matching OSNR value if needed

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::Update(uint32 theIndex, CT_TEL_mBm curPwr, CT_TEL_mBm curSnr)
{
    tHistory * myHistoryPtr = &myHistory[theIndex];
    // CT_TEL_mBm curPwr = myHistoryPtr->theCurPwr;
    CT_TEL_mBm prevPwr = myHistoryPtr->thePrevPwr;
    time_t curSampleTime = CSPII_CardIF::GetInstance()->GetUTCTime();
    time_t prevSampleTime = myHistoryPtr->prevSampleTime;

    if ( prevPwr == TRAFFIC_DEFAULT_POWER )
    {
        // this is the first time called to update. just save the current
        // power as a get started point
        RecordHysteresis( theIndex, curPwr, curPwr, curSampleTime );
        // update the per channel pwr/snr/timestamp
        myHistoryPtr->thePrevPwr = curPwr;
        myHistoryPtr->theCurPwr = curPwr;
        myHistoryPtr->theCurSnr = curSnr;
        myHistoryPtr->prevSampleTime = curSampleTime;
    }
    else
    {
        if ( (abs(curPwr - prevPwr) > myOchPowerDebounceThreshold)
        &&   ((curSampleTime - prevSampleTime) < myOchPowerDebouncePeriod) )
        {
            // a possible spike was detected. power changed by > theshold
            // and the time the curPwr was stable did not exceed the period
            // just store an event and don't update current power
            RecordHistory( theIndex, prevPwr, curPwr, curSampleTime, PWR_SPIKE_EVT );
        }
        else
        {
            // curPwr is stable and not ignored. update the hysteresis
            RecordHysteresis( theIndex, prevPwr, curPwr, curSampleTime );
            // update the per channel pwr/snr/timestamp
            myHistoryPtr->thePrevPwr = curPwr;
            myHistoryPtr->theCurPwr = curPwr;
            myHistoryPtr->theCurSnr = curSnr;
            myHistoryPtr->prevSampleTime = curSampleTime;
        }
    }
}

/***********************************************************************
Name
    GetPower

Synopsis
    CT_TEL_mBm TSPII_OchOsaDebounce::GetPower( uint32 theIndex )

Description
    Retrieve the current debounced power from the history tables

Inputs
    theIndex -  0-based channel number. same index used to update the
                history tables.

Returns
    CT_TEL_mBm - The current power from the history table is returned

----------------------------------------------------------------------*/
CT_TEL_mBm TSPII_OchOsaDebounce::GetPower( uint32 theIndex )
{
    return myHistory[theIndex].theCurPwr;
}

/***********************************************************************
Name
    GetOsnr

Synopsis
    CT_TEL_mBm TSPII_OchOsaDebounce::GetOsnr( uint32 theIndex )

Description
    Retrieve the current SNR value from the history tables

Inputs
    theIndex -  0-based channel number. same index used to update the
                history tables.

Returns
    CT_TEL_mBm - The current power from the history table is returned

----------------------------------------------------------------------*/
CT_TEL_mBm TSPII_OchOsaDebounce::GetOsnr( uint32 theIndex )
{
    return myHistory[theIndex].theCurSnr;
}

/***********************************************************************
Name
    ClearAllHistory

Synopsis
    void TSPII_OchOsaDebounce::ClearAllHistory()

Description
    Set the entire history table to defaults

Inputs
    None

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::ClearAllHistory()
{
    for(uint32 aIndex = 0; aIndex < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; aIndex++)
    {
        ClearHistoryForCh(aIndex);
        myHistory[aIndex].theCurPwr = TRAFFIC_DEFAULT_POWER;
        myHistory[aIndex].thePrevPwr = TRAFFIC_DEFAULT_POWER;
        myHistory[aIndex].theCurSnr = 0;
    }
}

/***********************************************************************
Name
    ClearHistoryForAllCh

Synopsis
    void TSPII_OchOsaDebounce::ClearHistoryForAllCh()

Description
    Set the entire history table to defaults

Inputs
    None

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::ClearHistoryForAllCh()
{
    for(uint32 aIndex = 0; aIndex < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; aIndex++)
        ClearHistoryForCh(aIndex);
}

/***********************************************************************
Name
    ClearHistoryForCh

Synopsis
    void TSPII_OchOsaDebounce::ClearHistoryForCh(uint32 theIndex)

Description
    Clear the history tables for the specific channel/index, but not
    the current power because it still needs to be valid

Inputs
    theIndex -  0-based channel/index

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::ClearHistoryForCh(uint32 theIndex)
{
    myHistory[theIndex].myHistMax.event  = UNKNOWN_EVT;
    myHistory[theIndex].myHistMax.prevPwr= TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMax.curPwr = TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMax.myTimestamp = 0;

    myHistory[theIndex].myHistMin.event  = UNKNOWN_EVT;
    myHistory[theIndex].myHistMin.prevPwr= TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMin.curPwr = TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMin.myTimestamp = 0;

    for(int i = 0; i < myHistoryDepth ; i++)
    {
        myHistory[theIndex].myHistEvent[i].event   = UNKNOWN_EVT;
        myHistory[theIndex].myHistEvent[i].prevPwr = TRAFFIC_DEFAULT_POWER;
        myHistory[theIndex].myHistEvent[i].curPwr  = TRAFFIC_DEFAULT_POWER;
    }
    myHistory[theIndex].myHistoryIndex = 0;
}

/***********************************************************************
Name
    RecordHistory

Synopsis
    void TSPII_OchOsaDebounce::RecordHistory(uint32 theIndex,
                                             CT_TEL_mBm prevPwr,
                                             CT_TEL_mBm curPwr,
                                             time_t curSampleTime,
                                             eSpikeEvent event)

Description
    Record a spike event in the history tables.

Inputs
    theIndex -          The 0-based channel index
    prevPwr -           the previous current power for this channel
    curPwr -            the new power value being considered for debounce
    curSampleTime       the current sample timestamp
    event               the spike event type

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::RecordHistory(uint32 theIndex,
                                         CT_TEL_mBm prevPwr,
                                         CT_TEL_mBm curPwr,
                                         time_t curSampleTime,
                                         eSpikeEvent event)
{
    uint32 hIndex = myHistory[theIndex].myHistoryIndex;

    myHistory[theIndex].myHistEvent[hIndex].myTimestamp = curSampleTime;
    myHistory[theIndex].myHistEvent[hIndex].event = event;
    myHistory[theIndex].myHistEvent[hIndex].prevPwr = prevPwr;
    myHistory[theIndex].myHistEvent[hIndex].curPwr = curPwr;

    if ( ++hIndex >= OCH_PWR_HISTORY_SIZE ) hIndex = 0;
    myHistory[theIndex].myHistoryIndex = hIndex;
}

/***********************************************************************
Name
    RecordHysteresis

Synopsis
    void TSPII_OchOsaDebounce::RecordHysteresis(uint32 theIndex,
                                                CT_TEL_mBm prevPwr,
                                                CT_TEL_mBm curPwr,
                                                time_t curSampleTime)

Description
    Using the previous and current power values, update the table
    that tracks the lowest and highest power values seen.

Inputs
    theIndex -          The 0-based channel index
    prevPwr -           the previous current power for this channel
    curPwr -            the new power value being considered for debounce
    curSampleTime       the current sample timestamp

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::RecordHysteresis(uint32 theIndex,
                                            CT_TEL_mBm prevPwr,
                                            CT_TEL_mBm curPwr,
                                            time_t curSampleTime)
{
    if(myHistory[theIndex].myHistMin.curPwr > curPwr ||
       myHistory[theIndex].myHistMin.curPwr == TRAFFIC_DEFAULT_POWER)
    {
        myHistory[theIndex].myHistMin.myTimestamp = curSampleTime;

        if(myHistory[theIndex].myHistMin.curPwr == TRAFFIC_DEFAULT_POWER)
            myHistory[theIndex].myHistMin.prevPwr = curPwr;
        else
            myHistory[theIndex].myHistMin.prevPwr = myHistory[theIndex].myHistMin.curPwr;

        myHistory[theIndex].myHistMin.curPwr = curPwr;
    }

    if(myHistory[theIndex].myHistMax.curPwr < curPwr ||
       myHistory[theIndex].myHistMax.curPwr == TRAFFIC_DEFAULT_POWER)
    {
        myHistory[theIndex].myHistMax.myTimestamp = curSampleTime;

        if(myHistory[theIndex].myHistMax.curPwr == TRAFFIC_DEFAULT_POWER)
            myHistory[theIndex].myHistMax.prevPwr = curPwr;
        else
            myHistory[theIndex].myHistMax.prevPwr = myHistory[theIndex].myHistMax.curPwr;

        myHistory[theIndex].myHistMax.curPwr = curPwr;
    }
}

/***********************************************************************
Name
    DisplayHistoryForAllCh

Synopsis
    void TSPII_OchOsaDebounce::DisplayHistoryForAllCh()

Description
    Debug menu method to display the event history for all channels

Inputs
    None

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::DisplayHistoryForAllCh()
{
    for(uint32 aIndex = 0; aIndex < myNumberOfWavelengths; aIndex++)
        DisplayHistoryForCh(aIndex);
}

/***********************************************************************
Name
    DisplayHistoryForCh

Synopsis
    void TSPII_OchOsaDebounce::DisplayHistoryForCh(uint32 theIndex)

Description
    Debug method to display the event history for the specified channel/index

Inputs
    theIndex -  the 0-based channel/index

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::DisplayHistoryForCh(uint32 theIndex)
{
    char line[160];

    char tstamp[20];
    char *pBuf = &tstamp[0];
    GetDateTimeStampStr(CSPII_CardIF::GetInstance()->GetUTCTime(), &pBuf, sizeof(tstamp));

    fc_cout << "\nOchPowerHistory-"<<theIndex<<": "<<tstamp<<endl;

    //display should not exceed 80 columns
    //                  10        20        30        40        50        60        70        80
    //          01234567890123456789012345678901234567890123456789012345678901234567890123456789
    fc_cout << "                                        prev  cur   " << endl;
    fc_cout << " Date       Time     Num  Event         pwr   pwr   " << endl;
    fc_cout << "----------------------------------------------------" << endl;
    for(int i = 0; i < OCH_PWR_HISTORY_SIZE; i++)
    {
        if(myHistory[theIndex].myHistEvent[i].event != UNKNOWN_EVT)
        {
            GetDateTimeStampStr(myHistory[theIndex].myHistEvent[i].myTimestamp, &pBuf, sizeof(tstamp));

            sprintf(line, " %s %-4d %13s %5d %5d",
                    tstamp,
                    i,
                    DISPLAY_OCH_EVENT(myHistory[theIndex].myHistEvent[i].event),
                    myHistory[theIndex].myHistEvent[i].prevPwr,
                    myHistory[theIndex].myHistEvent[i].curPwr);

            fc_cout << line << endl;
        }
    }
    fc_cout << endl << endl;
}

/***********************************************************************
Name
    DisplayHysteresis

Synopsis
    void TSPII_OchOsaDebounce::DisplayHysteresis()

Description
    Debug method to display the entire hysteresis table showing the
    high and low watermarks and the current power recorded for each channel

Inputs
    None

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::DisplayHysteresis()
{
    char line[160];

    char tstamp[20];
    char *pBuf = &tstamp[0];

    char tempstamp[20];
    char *pTempBuf = &tempstamp[0];

    GetDateTimeStampStr(CSPII_CardIF::GetInstance()->GetUTCTime(), &pBuf, sizeof(tstamp));

    fc_cout << "\nOchPowerHysteresis-"<<tstamp<<endl<<endl;

    //display should not exceed 80 columns
    //                  10        20        30        40        50        60        70        80
    //          01234567890123456789012345678901234567890123456789012345678901234567890123456789
    fc_cout << "               Minimum               |            Maximum              "    << endl;
    fc_cout << "                         prev  cur   |                     prev  cur     cur"    << endl;
    fc_cout << " Ch  Date       Time     pwr   pwr   | Date       Time     pwr   pwr     pwr"    << endl;
    fc_cout << "----------------------------------------------------------------------- -----"    << endl;
    for(uint32 i = 0; i < myNumberOfWavelengths; i++)
    {
        GetDateTimeStampStr(myHistory[i].myHistMin.myTimestamp, &pBuf, sizeof(tstamp));
        GetDateTimeStampStr(myHistory[i].myHistMax.myTimestamp, &pTempBuf, sizeof(tempstamp));

        sprintf(line, " %-3d %s %5d %5d | %s %5d %5d %5d",
                i,
                tstamp,
                myHistory[i].myHistMin.prevPwr,
                myHistory[i].myHistMin.curPwr,
                tempstamp,
                myHistory[i].myHistMax.prevPwr,
                myHistory[i].myHistMax.curPwr,
                myHistory[i].theCurPwr);

            fc_cout << line << endl;
    }
    fc_cout << endl << endl;
}

/***********************************************************************
Name
    DisplayHelp

Synopsis
    void TSPII_OchOsaDebounce::DisplayHelp(void)

Description
    Debug method to display the list of commands available for debugging

Inputs
    None

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::DisplayHelp(void)
{
    fc_cout << "d h        - display hysteresis for all channels\n";
    fc_cout << "d e [och#] - display history for a specific och (0 based)\n";
    fc_cout << "d e all    - display history for all och\n";
    fc_cout << "c [och#]   - clear history for a specific och (0 based)\n";
    fc_cout << "c all      - clear history for all och\n";
    fc_cout << "p <sec>    - display/set debounce period\n";
    fc_cout << "t <mBm>    - display/set debounce threshold" << endl;
}

/***********************************************************************
Name
    Menu

Synopsis
    void TSPII_OchOsaDebounce::Menu(int argc, char **argv)

Description
    Debug menu for this class. Takes a list of arguments as shown
    in the comments below. argc and argv are adjusted by the caller
    so that only the relevant arguments are passed to this method.

Inputs
    argc -      number of arguments in argv
    argv -      array of pointers with text

Returns
    N/A

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::Menu(int argc, char **argv)
{
    // "d h" display hysteresis
    // "d e och"
    // "d e all"
    // "c och"
    // "c all"
    // "p <ms>" - debounce period
    // "t <mbm>" - debounce threshold
    if ( argc == 0 )
    {
        DisplayHelp();
    }
    // force the output stream to decimal mode before any output
    fc_cout << dec;
    if ( argc == 1 )
    {
        if ( argv[0][0] == 'p' )
        {
            fc_cout << "Debounce Period = " << GetPeriod() << " Sec" << endl;
        }
        else if ( argv[0][0] == 't' )
        {
            fc_cout << "Debounce Threshold = " << GetThreshold() << " mBm" << endl;
        }
        else if ( argv[0][0] == 'h' )
        {
            DisplayHelp();
        }
    }
    else if ( argc == 2 )
    {
        if ( (argv[0][0] == 'd') && (argv[1][0] == 'h') )
        {
            DisplayHysteresis();
        }
        else if ( argv[0][0] == 'p' )
        {
            uint32 thePeriod;
            int count = sscanf( argv[1], "%u", &thePeriod );
            if ( count == 1 )
            {
                SetPeriod( thePeriod);
                fc_cout << "Debounce Period = " << GetPeriod() << " Sec" << endl;
            }
        }
        else if ( argv[0][0] == 't' )
        {
            uint32 theThrehsold;
            int count = sscanf( argv[1], "%u", &theThrehsold );
            if ( count == 1 )
            {
                SetThreshold(theThrehsold);
                fc_cout << "Debounce Threshold = " << GetThreshold() << " mBm" << endl;
            }
        }
        else if ( argv[0][0] == 'c' )
        {
            // clear event and hysteresis for OCH
            if ( strcmp( argv[1], "all") == 0 )
            {
                // clear all OCH
                ClearHistoryForAllCh();
            }
            else
            {
                uint32 theChannel;
                int count = sscanf( argv[1], "%u", &theChannel );
                if ( (count == 1) && (theChannel < myNumberOfWavelengths) )
                {
                    // a good channel number
                    ClearHistoryForCh(theChannel);
                }
                else
                {
                    fc_cout << "imvalid och#" << endl;
                }
            }
        }
    }
    else if ( argc == 3 )
    {
        if ( (argv[0][0] == 'd') && (argv[1][0] == 'e') )
        {
            // display event for OCH
            if ( strcmp( argv[2], "all") == 0 )
            {
                // display all OCH
                DisplayHistoryForAllCh();
            }
            else
            {
                uint32 theChannel;
                int count = sscanf( argv[2], "%u", &theChannel );
                if ( (count == 1) && (theChannel < myNumberOfWavelengths) )
                {
                    // a good channel number
                    DisplayHistoryForCh(theChannel);
                }
                else
                {
                    fc_cout << "imvalid och#" << endl;
                }
            }
        }
    }
}

/***********************************************************************
Name
    GetDateTimeStampStr

Synopsis
    void TSPII_OchOsaDebounce::GetDateTimeStampStr(time_t theTime,
                                                   char **pBuf, uint32 len)

Description
    convert a timestamp time_t value to a text string suitable for
    printing in the debug displays

Inputs
    theTime -   the time_t timestamp (in seconds)
    pBuf -      pointer to a buffer where the text string is stored
    len -       the length of the buffer pBuf (must be at least
                20 characters by default, but not checked).

Returns

----------------------------------------------------------------------*/
void TSPII_OchOsaDebounce::GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len)
{
    if(*pBuf == NULL)
        return;

    memset(*pBuf, 0x00, len);

    struct tm *stamp = NULL;

    if( (stamp = localtime(&theTime)) != NULL)
    {
        sprintf(*pBuf, "%2.2d/%2.2d/%4.4d-%2.2d:%2.2d:%2.2d",
                stamp->tm_mon+1, stamp->tm_mday, stamp->tm_year+1900,
                stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
    }
}

// vim:sw=4:expandtab:cindent:
