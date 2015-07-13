/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/


#ifndef PWR_DEFINITIONS_H
#define PWR_DEFINITIONS_H

#include <time.h>
#include "ExecutionSupport/FC_Milliseconds.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_SystemIds.h"

enum PWR_MenuResult
{
    PWR_MENU_SUCCESS,
    PWR_MENU_SUCCESS_MODIFIED,
    PWR_MENU_FAILURE
};

///////////////////////////////////////////////////////////////////////////////
// Algorithm parameters.
///////////////////////////////////////////////////////////////////////////////
const int             PWR_CXM_PORT_NUMBER                 			= 16;
const int             PWR_CXM_WAVELENGTH_CAPACITY         			= 88;
const CT_TEL_mBm      PWR_CX16U_INIT_ATTN                        	= 800; // 800
const CT_TEL_mBm      PWR_CX16U_TARGET_POWER               	        = -1000; // -1000 mB
const CT_TEL_mBm      PWR_CX16U_GAP_PD_EDFA               	        = -50; // -50 mB


const CT_TEL_mBm      PWR_CX16U_INIT_DROP_ATTN_USS_WITHOUT_OPSC        			=      600; // maybe 1000 mB
const CT_TEL_mBm      PWR_CX16U_INIT_DROP_ATTN_NANO_WITHOUT_OPSC       			=      400; // maybe 1000 mB
const CT_TEL_mBm      PWR_CX16U_INIT_DROP_ATTN_USS_WITH_OPSC       			    =      0; // maybe 1000 mB
const CT_TEL_mBm      PWR_CX16U_INIT_DROP_ATTN_NANO_WITH_OPSC       			=      0; // maybe 1000 mB
const CT_TEL_mBm      PWR_CX16U_INIT_DROP_ATTN                        			=      0; 


const CT_TEL_mBm      PWR_CX16U_ALLOWED_MIN_OUTPUT_POWER   			=  -2000; // mB
const CT_TEL_mBm      PWR_CX16U_ALLOWED_MIN_INPUT_POWER   			=  -1300; // mB

const CT_TEL_mBm      PWR_CX16U_FIXED_EDFA_GAIN          			=     1300; // mB
const CT_TEL_mBm      PWR_CX16U_WSS_IL          					=     630; // mB

const CT_TEL_mBm  	  PWR_CX16U_EVOA_MIN_ATTN 						= 0; // mB
const CT_TEL_mBm  	  PWR_CX16U_EVOA_MAX_ATTN 						= 1500; // mB
const CT_TEL_mBm  	  PWR_CX16U_EVOA_BLOCK_ATTN 					= 2500; // mB

const CT_TEL_mBm      PWR_CX16U_EVOA_MIN_GAIN             			=  -1500; // mB
const CT_TEL_mBm      PWR_CX16U_EVOA_MAX_GAIN             			=   0;    // mB

const CT_TEL_mBm      PWR_CX16U_EVOA_MIN_CHANGE_MB             		=     10; // mB evoa ganularity
const CT_TEL_mBm      PWR_CX16U_EVOA_MAX_CHANGE_MB             		=    200; // mB eova max change (to avoid BER)

const CT_TEL_mBm      PWR_CX16U_EVOA_DEAD_BAND_MB_RCMM      	    =     85; 
const CT_TEL_mBm      PWR_CX16U_EVOA_DEAD_BAND_MB_OADM         	    =     85;

const FC_Milliseconds PWR_CX16U_CONTROL_PERIOD_MS          			= 2000; // ms
const FC_Milliseconds PWR_CX16U_DEFAULT_PERIOD_MS          			= 2000; // ms
const FC_Milliseconds PWR_CX16U_QACT_PERIOD_MS             			= 2000; // ms
const FC_Milliseconds PWR_CX16U_INIT_PD_WAIT_MS            			= 2000; // ms

// General
const int             HISTORY_SIZE                   				=    120;

enum ePWR_Event
{
    PWR_XC              = 1,        //cross-connects present in the system
    PWR_NO_XC,                      //NO cross-connects present in the system
    PWR_ADD_XC,                     //cross-connect added
    PWR_DEL_XC,                     //cross-connect deleted
    PWR_SET_FIRSTXC,  
    PWR_SET_INTG,                   //error exists
    PWR_CLR_INTG,                   //error cleared
    PWR_LOOP,                       //FSM should stay in the same state
    PWR_UNKNOWN                  //unknown condition
};

const uint32        PWR_NO_CH_NUM_ASSIGNMENT = 0xff;
typedef struct
{
    uint32     ch;              //channel number zero-based
    ePWR_Event ev;              //event for channel
    time_t     timestamp;
}PWR_Event;

#define DISPLAY_PWR_EVENT(x) (\
    (x) == PWR_XC                   ? " PWR_XC                    " : \
    (x) == PWR_NO_XC                ? " PWR_NO_XC                 " : \
    (x) == PWR_ADD_XC               ? " PWR_ADD_XC                " : \
    (x) == PWR_DEL_XC               ? " PWR_DEL_XC                " : \
    (x) == PWR_SET_FIRSTXC          ? " PWR_SET_FIRSTXC           " : \
    (x) == PWR_SET_INTG             ? " PWR_SET_INTG              " : \
    (x) == PWR_CLR_INTG             ? " PWR_CLR_INTG              " : \
                                      " PWR_UNKNOWN               ")

#define DISPLAY_PWR_EVENT_DES(x) (\
    (x) == PWR_XC               ? "Cross-connects are present in the system" : \
    (x) == PWR_NO_XC            ? "Cross-connects are present in the system" : \
    (x) == PWR_ADD_XC           ? "Cross-connect has been added" : \
    (x) == PWR_DEL_XC           ? "Cross-connect has been deleted" : \
    (x) == PWR_SET_FIRSTXC      ? "First Cross-connect has been created" : \
    (x) == PWR_SET_INTG                 ? "error exist" : \
    (x) == PWR_CLR_INTG                 ? "error cleared" : \
                                  "Unknown condition")

enum PWR_State
{
    _INIT = 0,          //Initial State
    _FAST,              //Fast State
    _ASYN,              //A-Synch State
    _STDY,              //Steady State
    _REST,              //Reset State
    _INTG,              //Integration State
    _UNKN = 0xff        //Unknown State
};

#define DISPLAY_PWR_CTRL_STATE(x) (\
    (x) == _INIT        ? " _INIT " : \
    (x) == _FAST        ? " _FAST " : \
    (x) == _ASYN        ? " _ASYN " : \
    (x) == _STDY        ? " _STDY " : \
    (x) == _REST        ? " _REST " : \
    (x) == _INTG        ? " _INTG " : \
                          " _UNKN ")



enum ePWR_CorrMode
{
    PWR_INIT = 1,       //Instantenous Correction
    PWR_INST,           //Fast Correction
    PWR_REST,           //HW Restore Correction
    PWR_MANU,
    PWR_LOS,
    PWR_UNKN = 0xff     //unknown correction type
};

#define DISPLAY_PWR_CORR_MODE(x) (\
	(x) == PWR_INIT         ? "INIT" : \
    (x) == PWR_INST         ? "INST" : \
    (x) == PWR_MANU         ? "MANU" : \
    (x) == PWR_REST         ? "REST" : \
    (x) == PWR_LOS          ? "LOS" : \
                              "UNKN")
enum ePWR_TraceLevel
{
    PWR_DEFAULT = 0,    //default trace level
    PWR_DEBUG,          //debugging trace level
    PWR_DETAIL          //detailed debugging trace level
};

#define DISPLAY_PWR_TRACE_LEVEL(x) (\
    (x) == PWR_DEFAULT      ? "DEFAULT" : \
    (x) == PWR_DEBUG        ? "DEBUG"   : \
    (x) == PWR_DETAIL       ? "DETAIL"  : \
                              "UNKN")

//corrected amp/evoa value based on the min step size allowed by the HW
#define PWR_CORRECTED_VAL(x, y) ( (x%y == 0) ? x : (x + y - (x%y)) )
#define PWR_CORRECTED_SIGN(x)   ( (x >= 0) ? +1 : -1)


#endif // PWR_DEFINITIONS_H


