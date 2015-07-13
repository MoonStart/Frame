#ifndef TSPII_COMMON_H
#define TSPII_COMMON_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     TSPII
 TARGET   :     All.
 AUTHOR   :     18 Jan, 2002 Eric Bernier
 DESCRIPTION:   Tspii common uses
--------------------------------------------------------------------------*/

#include "BaseClass/FC_Stream.h"
#include "ErrorService/FC_Error.h"

#ifdef PSOS
    #define TSPII_PACKED __packed__(1,1)
#else // PSOS
    #define TSPII_PACKED
#endif // PSOS

#define TEXT_ON_OFF(x) ((x) ? "ON" : "OFF")
#define TEXT_DEFECT(y) TEXT_ON_OFF(TSPII_DEFECT(y)) << " " << (y)

extern bool gDebugThrowErrorWithoutReport;
// gTspiiCopmPowerMonitorTest is used by the Tspii test menu
// this extern is to fix a redundant occurance in the test menu under
// controller services and the test menu under the OSC directory
//extern uint8 gTspiiCopmPowerMonitorTest[17][2][100]; //[TdmSlot][port0-port1][Sample]
//extern uint8 *gTspiiCopmPowerMonitorTest[][]; //[TdmSlot][port0-port1][Sample]

#define TSPII_THROW_ERROR_IF_WITHOUT_REPORT(theCondition, theErrorString) \
    if(theCondition) \
    { \
        if (gDebugThrowErrorWithoutReport) \
            fc_cout << theErrorString << endl; \
        throw FC_HWError(theErrorString); \
    } \
    else ;

#define DISPLAY_TSPII_REGION(x, y, showsimul) \
{ \
    TSPII_##x##Region * region = app.Get##x(unit, slot); \
    if (region && ((showsimul) || !(*region)[0].IsDefault())) \
    { \
        fc_cout << "\nSLOT #" << slot << " UNIT #" << unit << " " << y << " CONFIGURATION and MONITORING" << endl; \
        unsigned int n = region->Size(); \
        unsigned int i; \
        for (i = 0; i < n; i++) \
        { \
            if (n > 1) fc_cout << "OBJECT #" << (i + 1); \
            (*region)[i].Display(fc_cout); \
        } \
    } \
}

#define DISPLAY_TSPII_REGION_W_INDEX(x, y, z) \
{ \
    TSPII_##x##Region * region = app.Get##x(unit, slot); \
    if (region) \
    { \
        fc_cout << "\nSLOT #" << slot << " UNIT #" << unit << " " << y << " CONFIGURATION and MONITORING" << endl; \
        unsigned int n = region->Size(); \
        if (n > 1 && (z-1 < n)) fc_cout << "OBJECT #" << z << endl; \
            (*region)[z-1].DisplayVerbose(fc_cout); \
    } \
}

#define RESET_TSPII_REGION(x) \
{ \
    TSPII_##x##Region * region = app.Get##x(unit, slot); \
    if (region) \
    { \
        unsigned int n = region->Size(); \
        unsigned int i; \
        for (i = 0; i < n; i++) \
        { \
            (*region)[i].Reset(); \
        } \
    } \
}

#define SET_CALDATA_UINT8(display, tag, object, attribute) \
    if (argc == 4 && strcmp(argv[2], #attribute) == 0) (object).attribute = strtoul(argv[3], NULL, 0), printUsage = false; \
    if ((display) || (argc == 4 && strcmp(argv[2], #attribute) == 0)) fc_cout << (sprintf(line, "        (%2s) %-50s = %5u (  0x%02X)\n", tag, #attribute, (object).attribute, (object).attribute), line);

#define SET_CALDATA_UINT16(display, tag, object, attribute) \
    if (argc == 4 && strcmp(argv[2], #attribute) == 0) (object).attribute = strtoul(argv[3], NULL, 0), printUsage = false; \
    if ((display) || (argc == 4 && strcmp(argv[2], #attribute) == 0)) fc_cout << (sprintf(line, "        (%2s) %-50s = %5u (0x%04X)\n", tag, #attribute, (object).attribute, (object).attribute), line);

#define SET_CALDATA_FLOAT(display, tag, object, attribute) \
    if (argc == 4 && strcmp(argv[2], #attribute) == 0) (object).attribute = atof(argv[3]), printUsage = false; \
    if ((display) || (argc == 4 && strcmp(argv[2], #attribute) == 0)) fc_cout << (sprintf(line, "        (%2s) %-50s = %11.5f\n", tag, #attribute, (object).attribute), line);

#define READ_EEPROM_BYTE(key, value)          (aCspiiEeprom->GetUint8 ((key), tempChar )                     ? (value) : tempChar )
#define READ_EEPROM_BYTE_NONZERO(key, value)  (aCspiiEeprom->GetUint8 ((key), tempChar ) || tempChar  == 0   ? (value) : tempChar )
#define READ_EEPROM_UINT(key, value)          (aCspiiEeprom->GetUint16((key), tempInt  )                     ? (value) : tempInt  )
#define READ_EEPROM_UINT_NONZERO(key, value)  (aCspiiEeprom->GetUint16((key), tempInt  ) || tempInt   == 0   ? (value) : tempInt  )
#define READ_EEPROM_FLOAT(key, value)         (aCspiiEeprom->GetFloat ((key), tempFloat)                     ? (value) : tempFloat)
#define READ_EEPROM_FLOAT_NONZERO(key, value) (aCspiiEeprom->GetFloat ((key), tempFloat) || tempFloat == 0.0 ? (value) : tempFloat)

#endif //TSPII_COMMON_H

