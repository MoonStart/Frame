/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : OSC8250
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : Device driver for OSC mapper FPGA on OSC8250.
 NOTES       :
   TBD       = to be done or to be determined

--------------------------------------------------------------------------*/
#ifndef TSPII_OSCMAPPERFPGADRV_H
#define TSPII_OSCMAPPERFPGADRV_H

#include <string.h>

// Base class for device drivers
#include "Device.h"

// Registers enumeration
enum TSPII_OscMapperFpgaGeneralReg
{
    // General
    OSC_FPGA_IDENTIFICATION                        = 0x000,
    OSC_FPGA_REVISION                              = 0x002,
    OSC_FPGA_INITIALIZATION                        = 0x004,
    OSC_FPGA_MAPPER_CONFIGURATION                  = 0x006,
    OSC_FPGA_PHY_CONTROL_FULL_DUPLEX               = 0x008,
    OSC_FPGA_PHY_IRQ_STATUS                        = 0x00A,
    OSC_FPGA_PHY_IRQ_LATCH                         = 0x00C,
    OSC_FPGA_PHY_INTERRUPT_ENABLE                  = 0x00E,
    OSC_FPGA_INTERRUPT_SUMMARY                     = 0x010,
    OSC_FPGA_INTERRUPT_SUMMARY_2                   = 0x012,
    OSC_FPGA_BACKPLANE_CHANNEL_CONFIGURATION       = 0x014
};

enum TSPII_OscMapperFpgaChannel
{
    OSC_FPGA_CHANNEL1,
    OSC_FPGA_CHANNEL2,
    OSC_FPGA_CHANNEL3,
    OSC_FPGA_CHANNEL4
};

enum TSPII_OscMapperFpgaChannelReg
{
    // OSC channel control/status registers
    OSC_FPGA_CHANNEL_CONTROL                       = 0x100,
    OSC_FPGA_CHANNEL_STATUS                        = 0x102,
    OSC_FPGA_CHANNEL_STATUS_LATCH                  = 0x104,
    OSC_FPGA_CHANNEL_STATUS_INTERRUPT_ENABLE       = 0x106,
    OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_CONTROL           = 0x108,
    OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS            = 0x10A,
    OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_LATCH      = 0x10C,
    OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_IRQ_ENABLE = 0x10E,

    // SMII transmit control/status registers
    OSC_FPGA_SMII_CONFIGURATION                    = 0x110,
    OSC_FPGA_SMII_STATUS                           = 0x112,
    OSC_FPGA_SMII_LATCH                            = 0x114,
    OSC_FPGA_SMII_INTERRUPT_ENABLE                 = 0x116,

    // Ethernet Configuration registers
    OSC_FPGA_ETHERNET_DEST_ADDR_1_2                = 0x122,
    OSC_FPGA_ETHERNET_DEST_ADDR_3_4                = 0x124,
    OSC_FPGA_ETHERNET_DEST_ADDR_5_6                = 0x126,
    OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_1_2         = 0x128,
    OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_3_4         = 0x12A,
    OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_5_6         = 0x12C,
    OSC_FPGA_ETHERNET_TYPE_BYTE_1_2                = 0x12E,

    // ECC transmit/receive control/status registers
    OSC_FPGA_ECC_CONTROL                           = 0x130,
    OSC_FPGA_ECC_STATUS                            = 0x132,
    OSC_FPGA_ECC_LATCH                             = 0x134,
    OSC_FPGA_ECC_INTERRUPT_ENABLE                  = 0x136,

    // Ingress alarm interrupt registers
    OSC_FPGA_INGRESS_ALARM_STATUS                  = 0x150,
    OSC_FPGA_INGRESS_ALARM_LATCH                   = 0x152,
    OSC_FPGA_INGRESS_ALARM_INTERRUPT_ENABLE        = 0x154,

    // OTS overhead transmit/receive registers
    OSC_FPGA_OOS_OVERHEAD_TRANSMIT                 = 0x160,
    OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS           = 0x162,
    OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH            = 0x164,
    OSC_FPGA_OOS_OVERHEAD_RECEIVE_INTERRUPT_ENABLE = 0x166,

    // K1/K2 tranmit/receive registers
    OSC_FPGA_K1_K2_TRANSMIT                        = 0x170,
    OSC_FPGA_K1_K2_RECEIVE                         = 0x172,

    // transmit/receive power value registers
    OSC_FPGA_TRANSMIT_POWER_VALUE                  = 0x174,
    OSC_FPGA_RECEIVE_POWER_VALUE                   = 0x176,

    // OCh interrupt registers
    OSC_FPGA_OCH_IRQ_1_16                          = 0x180,
    OSC_FPGA_OCH_IRQ_17_32                         = 0x182,
    OSC_FPGA_OCH_IRQ_33_48                         = 0x184,
    OSC_FPGA_OCH_IRQ_49_64                         = 0x186,
    OSC_FPGA_OCH_IRQ_65_80                         = 0x188,
    OSC_FPGA_OCH_IRQ_81_88                         = 0x18A,

    // Test register
    OSC_FPGA_DEBUG                                 = 0x190,
    // PRBS configuration registers
    OSC_FPGA_PRBS_GENERATOR_CONFIGURATION          = 0x192,
    OSC_FPGA_PRBS_ANALYZER_CONFIGURATION           = 0x194,
    OSC_FPGA_COUNTER_RESET_CONTROL1                = 0x196,
    OSC_FPGA_COUNTER_RESET_CONTROL2                = 0x198,

    // Counter registers
    OSC_FPGA_ETHER_TX_CRC_ERR_COUNTER              = 0x1A0,
    OSC_FPGA_PRBS_ANALYZER_ERROR_COUNTER           = 0x1A2,
    OSC_FPGA_HDLC_FCS_ERROR_COUNTER                = 0x1A4,
    OSC_FPGA_B1_ERROR_COUNTER                      = 0x1A6,
    OSC_FPGA_B2_ERROR_COUNTER                      = 0x1A8,
    OSC_FPGA_TX_FIFO_OVERRUN_COUNTER               = 0x1B0,
    OSC_FPGA_TX_FIFO_HI_WM_COUNTER                 = 0x1B2,
    OSC_FPGA_TX_FIFO_MAX_DEPTH_COUNTER             = 0x1B4,
    OSC_FPGA_TX_SMII_IP_PACKET_COUNTER             = 0x1C0,
    OSC_FPGA_TX_ECC_IP_PACKET_COUNTER              = 0x1C2,
    OSC_FPGA_TX_ECC_CTRL_MESSAGE_COUNTER           = 0x1C4,
    OSC_FPGA_HDLC_FRAMER_COUNTER                   = 0x1C6,
    OSC_FPGA_HDLC_STUFFER_COUNTER                  = 0x1C8,
    OSC_FPGA_HDLC_DESTUFFER_COUNTER                = 0x1D0,
    OSC_FPGA_HDLC_DEFRAMER_COUNTER                 = 0x1D2,
    OSC_FPGA_RX_ECC_IP_PACKET_COUNTER              = 0x1D4,
    OSC_FPGA_RX_ECC_CTRL_MESSAGE_COUNTER           = 0x1D6,
    OSC_FPGA_RX_SMII_IP_PACKET_COUNTER             = 0x1D8,
    OSC_FPGA_RX_PAUSE_COUNTER                      = 0x1DA,

    // SONET J0 overhead BRAMs
    OSC_FPGA_SONET_J0_TRANSMIT_BRAM                = 0x1E0,
    OSC_FPGA_SONET_J0_RECEIVE_BRAM                 = 0x1F0,

    // OTS TTI overhead BRAMs
    OSC_FPGA_OTS_TTI_TRANSMIT_BRAM                 = 0x200,
    OSC_FPGA_OTS_TTI_RECEIVE_BRAM                  = 0x240,

    // OTS TTI Trace ID
    OSC_FPGA_OTS_TTI_TRANSMIT_TRACE                = 0x220,
    OSC_FPGA_OTS_TTI_RECEIVE_TRACE                 = 0x260,

    // Auxillary BRAMs
    OSC_FPGA_CTRL_MSG_SNIFF_RX_BRAM                = 0x800,

    // OCh overhead BRAMs
    OSC_FPGA_OCH_TRANSMIT_BRAM                     = 0xC00,
    OSC_FPGA_OCH_RECEIVE_BRAM                      = 0xE00,
    OSC_FPGA_OCH_RECEIVE_LATCH_BRAM                = 0xE02,
    OSC_FPGA_OCH_RECEIVE_INTERRUPT_ENABLE_BRAM     = 0xE04
};

// Channel offsets
const uint16 OSC_FPGA_CHANNEL_OFFSET              = 0x1000;
const uint16 OSC_FPGA_OCH_64_87_OFFSET            = 0x4000;
const uint32 OSC_FPGA_OCH_64_VAL                  = 0x40;

// OSC_FPGA_IDENTIFICATION                        = 0x000
// nothing to do

// OSC_FPGA_REVISION                              = 0x002
// nothing to do

// OSC_FPGA_INITIALIZATION                        = 0x004
// nothing to do

// OSC_FPGA_MAPPER_CONFIGURATION                  = 0x006
const uint16 OSC_FPGA_TX_FIFO_HI_WM_MASK          = 0xF000;
const uint16 OSC_FPGA_TX_FIFO_HI_WM_SHIFT         = 12;
const uint16 OSC_FPGA_TX_FIFO_LO_WM_MASK          = 0x0F00;
const uint16 OSC_FPGA_TX_FIFO_LO_WM_SHIFT         = 8;
const uint16 OSC_FPGA_CHANNEL_AB_DEST_SELECT      = 0x0002;
const uint16 OSC_FPGA_FORMAT_E1                   = 0x0001;

// OSC_FPGA_PHY_CONTROL_FULL_DUPLEX               = 0x008
// OSC_FPGA_PHY_IRQ_STATUS                        = 0x00A
// OSC_FPGA_PHY_IRQ_LATCH                         = 0x00C
// OSC_FPGA_PHY_INTERRUPT_ENABLE                  = 0x00E
const uint16 OSC_FPGA_PHY8B                       = 0x0002;
const uint16 OSC_FPGA_PHY8A                       = 0x0001;

// OSC_FPGA_INTERRUPT_SUMMARY                     = 0x010
const uint16 OSC_FPGA_PHY_IRQ                     = 0x8000;
const uint16 OSC_FPGA_BPCIA_B                     = 0x4000;
const uint16 OSC_FPGA_ECC_B                       = 0x2000;
const uint16 OSC_FPGA_OSC_CHANNEL_B               = 0x1000;
const uint16 OSC_FPGA_SMII_B                      = 0x0800;
const uint16 OSC_FPGA_OCH_ALARM_B                 = 0x0400;
const uint16 OSC_FPGA_OOS_ALARM_B                 = 0x0200;
const uint16 OSC_FPGA_INGRESS_ALARM_B             = 0x0100;
const uint16 OSC_FPGA_BPCIA_A                     = 0x0040;
const uint16 OSC_FPGA_ECC_A                       = 0x0020;
const uint16 OSC_FPGA_OSC_CHANNEL_A               = 0x0010;
const uint16 OSC_FPGA_SMII_A                      = 0x0008;
const uint16 OSC_FPGA_OCH_ALARM_A                 = 0x0004;
const uint16 OSC_FPGA_OOS_ALARM_A                 = 0x0002;
const uint16 OSC_FPGA_INGRESS_ALARM_A             = 0x0001;

// OSC_FPGA_INTERRUPT_SUMMARY_2                       = 0x012
const uint16 OSC_FPGA_BACKPLANE_CHANNEL_IRQ_ACTIVE_D  = 0x4000;
const uint16 OSC_FPGA_ECC_IRQ_ACTIVE_D                = 0x2000;
const uint16 OSC_FPGA_OSC_CHANNEL_IRQ_ACTIVE_D        = 0x1000;
const uint16 OSC_FPGA_SMII_IRQ_ACTIVE_D               = 0x0800;
const uint16 OSC_FPGA_ALARM_IRQ_ACTIVE_D              = 0x0400;
const uint16 OSC_FPGA_OOS_ALARM_IRQ_ACTIVE_D          = 0x0200;
const uint16 OSC_FPGA_INGRESS_ALARM_IRQ_ACTIVE_D      = 0x0100;
const uint16 OSC_FPGA_BACKPLANE_CHANNEL_IRQ_ACTIVE_C  = 0x0040;
const uint16 OSC_FPGA_ECC_IRQ_ACTIVE_C                = 0x0020;
const uint16 OSC_FPGA_OSC_CHANNEL_IRQ_ACTIVE_C        = 0x0010;
const uint16 OSC_FPGA_SMII_IRQ_ACTIVE_C               = 0x0008;
const uint16 OSC_FPGA_ALARM_IRQ_ACTIVE_C              = 0x0004;
const uint16 OSC_FPGA_OOS_ALARM_IRQ_ACTIVE_C          = 0x0002;
const uint16 OSC_FPGA_INGRESS_ALARM_IRQ_ACTIVE_C      = 0x0001;

// OSC_FPGA_BACKPLANE_CHANNEL_CONFIGURATION           = 0x014
const uint16 OSC_FPGA_SIGNAL_DETECT_POLARITY          = 0x0020;
const uint16 OSC_FPGA_LINE_LOOPBACK_ENABLE            = 0x0010;
const uint16 OSC_FPGA_SERIAL_CLOCK_LOOP_TIME_SELECT   = 0x0008;
const uint16 OSC_FPGA_TRANSMIT_SERIAL_CLOCK_OUT_OFF   = 0x0004;
const uint16 OSC_FPGA_CSU_CLOCK_OUT_OFF               = 0x0002;
const uint16 OSC_FPGA_DIAGNOSTIC_LOOPBACK_ENABLE      = 0x0001;

// OSC_FPGA_CHANNEL_CONTROL                       = 0x100
const uint16 OSC_FPGA_DISABLE_LASER               = 0x8000;
const uint16 OSC_FPGA_LOOP_TIMING_OPER_MODE_0     = 0x0800;
const uint16 OSC_FPGA_OPT_FAC_LOOP_CTRL           = 0x0400;
const uint16 OSC_FPGA_OPT_EQUIP_LOOP_CTRL         = 0x0200;
const uint16 OSC_FPGA_LOS_TTL                     = 0x0100;
const uint16 OSC_FPGA_STS12_SELECT                = 0x0080;
const uint16 OSC_FPGA_INTERNAL_LOS_DETECTION      = 0x0040;
const uint16 OSC_FPGA_DISABLE_CRU                 = 0x0020;
const uint16 OSC_FPGA_OUT_OF_FRAME                = 0x0010;
const uint16 OSC_FPGA_LOOP_TIMING_MODE1           = 0x0008;
const uint16 OSC_FPGA_CRU_EQUIPMENT_LOOPBACK      = 0x0004;
const uint16 OSC_FPGA_FACILITY_LOOPBACK           = 0x0002;
const uint16 OSC_FPGA_EQUIPMENT_LOOPBACK          = 0x0001;

// OSC_FPGA_CHANNEL_STATUS                        = 0x102
// OSC_FPGA_CHANNEL_STATUS_LATCH                  = 0x104
// OSC_FPGA_CHANNEL_STATUS_INTERRUPT_ENABLE       = 0x106
const uint16 OSC_FPGA_INTERNAL_FRAME_PULSE        = 0x0020;
const uint16 OSC_FPGA_FRAME_PULSE                 = 0x0010;
const uint16 OSC_FPGA_CMU_LOCK_DETECT             = 0x0008;
const uint16 OSC_FPGA_CRU_LOCK_DETECT             = 0x0004;
const uint16 OSC_FPGA_LOS_DETECT                  = 0x0002;
const uint16 OSC_FPGA_LOL_DETECT                  = 0x0001;

// OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_CONTROL           = 0x108
const uint16 OSC_FPGA_MASTERSHIP_CONTROL                = 0x0004;
const uint16 OSC_FPGA_OPTICAL_SWITCH_CONTROL            = 0x0002;
const uint16 OSC_FPGA_SIGNAL_DETECT                     = 0x0001;


// OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS            = 0x10A
// OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_LATCH      = 0x10C
// OSC_FPGA_CHANNEL_BACKPLANE_CHANNEL_STATUS_IRQ_ENABLE = 0x10E
const uint16 OSC_FPGA_OC3_TX_19M_CLOCK_OUT_OF_RANGE     = 0x0010;
const uint16 OSC_FPGA_BAM_OOF                           = 0x0008;
const uint16 OSC_FPGA_BAM_LOF                           = 0x0004;
const uint16 OSC_FPGA_BAM_IF                            = 0x0002;
const uint16 OSC_FPGA_AMCC_S1213_RECEIVE_LOCK           = 0x0001;

// OSC_FPGA_SMII_CONFIGURATION                    = 0x110
const uint16 OSC_FPGA_CFG_RXD0                    = 0x0080;
const uint16 OSC_FPGA_CFG_100MB                   = 0x0040;
const uint16 OSC_FPGA_CFG_FULL_DUPLEX             = 0x0020;
const uint16 OSC_FPGA_CFG_LINK_UP                 = 0x0010;
const uint16 OSC_FPGA_CFG_JABBER_ERROR            = 0x0008;
const uint16 OSC_FPGA_CFG_UPPER_NIBBLE_OK         = 0x0004;
const uint16 OSC_FPGA_CFG_FALSE_CARRIER_DETECTED  = 0x0002;
const uint16 OSC_FPGA_CFG_RXD7                    = 0x0001;

//  OSC_FPGA_SMII_STATUS                          = 0x112,
//  OSC_FPGA_SMII_LATCH                           = 0x114,
//  OSC_FPGA_SMII_INTERRUPT_ENABLE                = 0x116,
const uint16 OSC_FPGA_STAT_TX_ER                  = 0x0010;
const uint16 OSC_FPGA_STAT_100MB                  = 0x0008;
const uint16 OSC_FPGA_STAT_FULL_DUPLEX            = 0x0004;
const uint16 OSC_FPGA_STAT_LINK_UP                = 0x0002;
const uint16 OSC_FPGA_STAT_JABBER_ERROR           = 0x0001;

// OSC_FPGA_ETHERNET_DEST_ADDR_1_2                = 0x122,
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_1_SHIFT= 8;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_1_MASK = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_2_SHIFT= 0;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_2_MASK = 0x00FF;

// OSC_FPGA_ETHERNET_DEST_ADDR_3_4                = 0x124,
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_3_SHIFT= 8;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_3_MASK = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_4_SHIFT= 0;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_4_MASK = 0x00FF;

// OSC_FPGA_ETHERNET_DEST_ADDR_5_6                = 0x126,
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_5_SHIFT= 8;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_5_MASK = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_6_SHIFT= 0;
const uint16 OSC_FPGA_ETHERNET_DEST_ADDR_BYTE_6_MASK = 0x00FF;

// OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_1_2         = 0x128,
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_1_SHIFT = 8;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_1_MASK  = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_2_SHIFT = 0;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_2_MASK  = 0x00FF;

// OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_3_4         = 0x12A,
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_3_SHIFT = 8;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_3_MASK  = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_4_SHIFT = 0;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_4_MASK  = 0x00FF;

// OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_5_6         = 0x12C,
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_5_SHIFT = 8;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_5_MASK  = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_6_SHIFT = 0;
const uint16 OSC_FPGA_ETHERNET_SOURCE_ADDR_BYTE_6_MASK  = 0x00FF;

// OSC_FPGA_ETHERNET_TYPE_BYTE_1_2                = 0x12E,
const uint16 OSC_FPGA_ETHERNET_TYPE_BYTE_1_SHIFT        = 8;
const uint16 OSC_FPGA_ETHERNET_TYPE_BYTE_1_MASK         = 0xFF00;
const uint16 OSC_FPGA_ETHERNET_TYPE_BYTE_2_SHIFT        = 0;
const uint16 OSC_FPGA_ETHERNET_TYPE_BYTE_2_MASK         = 0x00FF;

// OSC_FPGA_ECC_CONTROL                           = 0x130,
const uint16 OSC_FPGA_TX_CTRL_MESSAGE_READY       = 0x8000;
const uint16 OSC_FPGA_HDLC_CONTROL_FIELD_MASK     = 0x7000;
const uint16 OSC_FPGA_HDLC_CONTROL_FIELD_SHIFT    = 12;
const uint16 OSC_FPGA_RX_CTRL_MESSAGE_CLEAR       = 0x0800;
const uint16 OSC_FPGA_CFG_RX_PCKT_SNIFF_ENABLE    = 0x0008;
const uint16 OSC_FPGA_ETH_SRC_ADDR_SEL            = 0x0004;  // not used, Ethernet source address is programmable
const uint16 OSC_FPGA_CFG_PCKT_OUT_ENABLE         = 0x0002;
const uint16 OSC_FPGA_CFG_PCKT_IN_ENABLE          = 0x0001;

// OSC_FPGA_ECC_STATUS                            = 0x132,
// OSC_FPGA_ECC_LATCH                             = 0x134,
// OSC_FPGA_ECC_INTERRUPT_ENABLE                  = 0x136,
const uint16 OSC_FPGA_TX_PCKT_FIFO_FULL           = 0x4000;
const uint16 OSC_FPGA_HDLC_FRAMER_FIFO_FULL       = 0x2000;
const uint16 OSC_FPGA_HDLC_STUFFER_FIFO_FULL      = 0x1000;
const uint16 OSC_FPGA_HDLC_DESTUFFER_FIFO_FULL    = 0x0800;
const uint16 OSC_FPGA_RX_PCKT_FIFO_FULL           = 0x0400;
const uint16 OSC_FPGA_TX_CTRL_MESSAGE_SENT_ACK    = 0x0200;
const uint16 OSC_FPGA_RX_CTRL_MESSAGE_READY       = 0x0100;
const uint16 OSC_FPGA_RX_CTRL_MESSAGE_ID_MASK     = 0x00FF;
const uint16 OSC_FPGA_RX_CTRL_MESSAGE_ID_SHIFT    = 0;

// OSC_FPGA_INGRESS_ALARM_STATUS                  = 0x150
// OSC_FPGA_INGRESS_ALARM_LATCH                   = 0x152
// OSC_FPGA_INGRESS_ALARM_INTERRUPT_ENABLE        = 0x154
const uint16 OSC_FPGA_OTS_TTI_LOF                 = 0x0040;
const uint16 OSC_FPGA_J0_LOF                      = 0x0020;
const uint16 OSC_FPGA_CV_LVL_2                    = 0x0010;
const uint16 OSC_FPGA_CV_LVL_1                    = 0x0008;
const uint16 OSC_FPGA_SEF                         = 0x0004;
const uint16 OSC_FPGA_OOF                         = 0x0002;
const uint16 OSC_FPGA_LOF                         = 0x0001;

// OSC_FPGA_OOS_OVERHEAD_TRANSMIT                 = 0x160,
// OSC_FPGA_OOS_OVERHEAD_RECEIVE_STATUS           = 0x162,
// OSC_FPGA_OOS_OVERHEAD_RECEIVE_LATCH            = 0x164,
// OSC_FPGA_OOS_OVERHEAD_RECEIVE_INTERRUPT_ENABLE = 0x166,
const uint16 OSC_FPGA_OTS_PMI                     = 0x0800;
const uint16 OSC_FPGA_OTS_BDIO_MASK               = 0x0600;
const uint16 OSC_FPGA_OTS_BDIO                    = 0x0200;
const uint16 OSC_FPGA_OTS_BDIP                    = 0x0100;
const uint16 OSC_FPGA_OMS_FDIP                    = 0x0010;
const uint16 OSC_FPGA_OMS_FDIO                    = 0x0008;
const uint16 OSC_FPGA_OMS_BDIP                    = 0x0004;
const uint16 OSC_FPGA_OMS_BDIO                    = 0x0002;
const uint16 OSC_FPGA_OMS_PMI                     = 0x0001;

// OSC_FPGA_K1_K2_TRANSMIT                        = 0x170
// OSC_FPGA_K1_K2_RECEIVE                         = 0x172
const uint16 OSC_FPGA_K2_SHIFT                    = 8;
const uint16 OSC_FPGA_K2_MASK                     = 0xFF00;
const uint16 OSC_FPGA_K1_SHIFT                    = 0;
const uint16 OSC_FPGA_K1_MASK                     = 0x00FF;

// OSC_FPGA_TRANSMIT_POWER_VALUE                         = 0x174
// OSC_FPGA_RECEIVE_POWER_VALUE                          = 0x176
const uint16 OSC_FPGA_TRANSMIT_POWER_VALUE_BYTE_2_SHIFT  = 8;
const uint16 OSC_FPGA_TRANSMIT_POWER_VALUE_BYTE_2_MASK   = 0xff00;
const uint16 OSC_FPGA_TRANSMIT_POWER_VALUE_BYTE_1_SHIFT  = 0;
const uint16 OSC_FPGA_TRANSMIT_POWER_VALUE_BYTE_1_MASK   = 0x00ff;
const uint16 OSC_FPGA_RECEIVE_POWER_VALUE_BYTE_2_SHIFT   = 8;
const uint16 OSC_FPGA_RECEIVE_POWER_VALUE_BYTE_2_MASK    = 0xff00;
const uint16 OSC_FPGA_RECEIVE_POWER_VALUE_BYTE_1_SHIFT   = 0;
const uint16 OSC_FPGA_RECEIVE_POWER_VALUE_BYTE_1_MASK    = 0x00ff;

// OSC_FPGA_OCH_IRQ_1_16                          = 0x180
// OSC_FPGA_OCH_IRQ_17_32                         = 0x182
// OSC_FPGA_OCH_IRQ_33_48                         = 0x184
// OSC_FPGA_OCH_IRQ_49_64                         = 0x186

// OSC_FPGA_DEBUG                                 = 0x190
const uint16 OSC_FPGA_ETHERNET_CRC_INVALIDATE     = 0x0040;
const uint16 OSC_FPGA_HDLC_FCS_INVALIDATE         = 0x0020;
const uint16 OSC_FPGA_FRAMING_ALM_DISABLE         = 0x0010;
const uint16 OSC_FPGA_B2_INVALIDATE               = 0x0008;
const uint16 OSC_FPGA_B1_INVALIDATE               = 0x0004;
const uint16 OSC_FPGA_DESCRAMBLING_DISABLE        = 0x0002;
const uint16 OSC_FPGA_SCRAMBLING_DISABLE          = 0x0001;


// OSC_FPGA_PRBS_GENERATOR_CONFIGURATION          = 0x192
// OSC_FPGA_PRBS_ANALYZER_CONFIGURATION           = 0x194
const uint16 OSC_FPGA_TEST_PATTERN_SHIFT          = 8;
const uint16 OSC_FPGA_TEST_PATTERN_MASK           = 0xFF00;
const uint16 OSC_FPGA_PATTERN_SELECT              = 0x0004;
const uint16 OSC_FPGA_E1_OC3_PRBS_RESET           = 0x0002;
const uint16 OSC_FPGA_OC3_PRBS_ENABLE             = 0x0001;

// OSC_FPGA_COUNTER_RESET_CONTROL1                = 0x196
const uint16 OSC_FPGA_TX_FIFO_MAX_DEPTH_RST       = 0x0400;
const uint16 OSC_FPGA_TX_FIFO_HI_WM_RST           = 0x0200;
const uint16 OSC_FPGA_TX_FIFO_OVERRUN_RST         = 0x0100;
const uint16 OSC_FPGA_HDLC_FCS_ERROR_RST          = 0x0008;
const uint16 OSC_FPGA_ETHER_CRC_ERROR_RST         = 0x0004;
const uint16 OSC_FPGA_B2_RST                      = 0x0002;
const uint16 OSC_FPGA_B1_RST                      = 0x0001;

// OSC_FPGA_COUNTER_RESET_CONTROL2                = 0x198
const uint16 OSC_FPGA_PAUSE_FRAME_RST             = 0x2000;
const uint16 OSC_FPGA_SMII_RX_PACKET_RST          = 0x1000;
const uint16 OSC_FPGA_ECC_RX_CTRL_MSG_RST         = 0x0800;
const uint16 OSC_FPGA_ECC_RX_PACKET_RST           = 0x0400;
const uint16 OSC_FPGA_HDLC_DEFRAMER_RST           = 0x0200;
const uint16 OSC_FPGA_HDLC_DESTUFFER_RST          = 0x0100;
const uint16 OSC_FPGA_HDLC_STUFFER_RST            = 0x0010;
const uint16 OSC_FPGA_HDLC_FRAMER_RST             = 0x0008;
const uint16 OSC_FPGA_ECC_TX_CTRL_MSG_RST         = 0x0004;
const uint16 OSC_FPGA_ECC_TX_PACKET_RST           = 0x0002;
const uint16 OSC_FPGA_SMII_TX_PACKET_RST          = 0x0001;

// OSC_FPGA_OCH_TRANSMIT_BRAM                     = 0xC00,
// OSC_FPGA_OCH_RECEIVE_BRAM                      = 0xE00,
// OSC_FPGA_OCH_RECEIVE_LATCH_BRAM                = 0xE02,
// OSC_FPGA_OCH_RECEIVE_INTERRUPT_ENABLE_BRAM     = 0xE04
const uint16 OSC_FPGA_OCH_FDIP                    = 0x0004;
const uint16 OSC_FPGA_OCH_FDIO                    = 0x0002;
const uint16 OSC_FPGA_OCH_OCI                     = 0x0001;

// OCH Addresses Organization is as follow 
const uint32 OSC_FPGA_OCH_OFFSET                  = 0x00000002;
const uint32 OSC_FPGA_OCH_OFFSET_ADD              = 0x00000004;
const uint32 OSC_FPGA_OCH_LIVE                    = 0x00000000;
const uint32 OSC_FPGA_OCH_LATCHED                 = 0x00000001;
const uint32 OSC_FPGA_OCH_INT                     = 0x00000002;


// OSC_FPGA_AUXILIARY_RX_BRAM                     = 0x800
// OSC_FPGA_OTS_TTI_TRANSMIT_BRAM                 = 0xC00
// OSC_FPGA_OTS_TTI_RECEIVE_BRAM                  = 0xC40


#ifdef __SIMULATION__
    const uint32  TSPII_OSC_MAPPER_DRV_MEM_SPACE    = 0x8000;
    extern uint32 gOscMapperDrvMem[TSPII_OSC_MAPPER_DRV_MEM_SPACE];
    const uint32  TSPII_OSC_MAPPER_DRV_BASE_ADDRESS = (uint32)gOscMapperDrvMem;
#else
    const uint32  TSPII_OSC_MAPPER_DRV_BASE_ADDRESS =  0xFDFE8000;
#endif

class TSPII_OscMapperFpgaDrv : public HWIF_Device<TSPII_OscMapperFpgaGeneralReg, uint16, uint16>
{
public:
	/* Destructor */         ~TSPII_OscMapperFpgaDrv();
	void                     Init();
	void                     WriteStaticRegisters();
	void                     DisplayContent(int argc, char ** argv);
	static                   TSPII_OscMapperFpgaDrv & GetInstance();
    static void              DeleteInstance();

    inline volatile uint16 * ChannelGetAddr      (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg);
    inline volatile uint16 * OchChannelGetAddr   (TSPII_OscMapperFpgaChannel theChannel, uint32 theOch, TSPII_OscMapperFpgaChannelReg theReg);
    inline uint16            ChannelRead         (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg);
    inline uint16            ChannelReadW1C      (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask); 
    inline void              ChannelWrite        (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theVal);
    inline void              ChannelReadModWr    (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, uint16 theVal); 
    inline void              ChannelReadModWr    (TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, HWIF_BITOP theOperation);
    inline void              ChannelReadModWrBool(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, bool theOperation); 
    inline bool IsLoopbackDetected(TSPII_OscMapperFpgaChannel theChannel);

private:
    /* Constructor */ TSPII_OscMapperFpgaDrv(uint32 theBase);

    static TSPII_OscMapperFpgaDrv * ourInstance;
};

inline volatile uint16 * TSPII_OscMapperFpgaDrv::ChannelGetAddr(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg)
{
	uint16 theOffset = 0;
	switch(theChannel)
	{
	case OSC_FPGA_CHANNEL1:
		theOffset = 0;
		break;
	case OSC_FPGA_CHANNEL2:
		theOffset = OSC_FPGA_CHANNEL_OFFSET;
		break;
	case OSC_FPGA_CHANNEL3:
		theOffset = OSC_FPGA_CHANNEL_OFFSET*2;
		break;
	case OSC_FPGA_CHANNEL4:
		theOffset = OSC_FPGA_CHANNEL_OFFSET*3;
		break;
	default:
		break;
	}
    return (volatile uint16 *)(theReg + base + theOffset);
}

//Address based on passed in och #
inline volatile uint16 * TSPII_OscMapperFpgaDrv::OchChannelGetAddr (TSPII_OscMapperFpgaChannel theChannel, uint32 theOch, TSPII_OscMapperFpgaChannelReg theReg)
{
	uint16 theOffset = 0;
	switch(theChannel)
	{
	case OSC_FPGA_CHANNEL1:
        if (theOch <OSC_FPGA_OCH_64_VAL)
        {
		    theOffset = 0;
        }
        else
        {
            theOffset = OSC_FPGA_OCH_64_87_OFFSET;
        }
		break;
	case OSC_FPGA_CHANNEL2:
        if (theOch <OSC_FPGA_OCH_64_VAL)
        {
		    theOffset = OSC_FPGA_CHANNEL_OFFSET;
        }
        else
        {
            theOffset = OSC_FPGA_CHANNEL_OFFSET + OSC_FPGA_OCH_64_87_OFFSET;
        }
		break;
	case OSC_FPGA_CHANNEL3:
        if (theOch <OSC_FPGA_OCH_64_VAL)
        {
		    theOffset = OSC_FPGA_CHANNEL_OFFSET*2;
        }
        else
        {
            theOffset = (OSC_FPGA_CHANNEL_OFFSET*2) + OSC_FPGA_OCH_64_87_OFFSET;
        }
		break;
	case OSC_FPGA_CHANNEL4:
        if (theOch <OSC_FPGA_OCH_64_VAL)
        {
		    theOffset = OSC_FPGA_CHANNEL_OFFSET*3;
        }
        else
        {
            theOffset = (OSC_FPGA_CHANNEL_OFFSET*3) + OSC_FPGA_OCH_64_87_OFFSET;
        }
		break;
	default:
		break;
	}
    return (volatile uint16 *)(theReg + base + theOffset);
}

inline uint16 TSPII_OscMapperFpgaDrv::ChannelRead(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    return *p;
}

inline bool TSPII_OscMapperFpgaDrv::IsLoopbackDetected(TSPII_OscMapperFpgaChannel theChannel)
{
    char * txTrace = (char *) ChannelGetAddr(theChannel, OSC_FPGA_OTS_TTI_TRANSMIT_TRACE);
    char * rxTrace = (char *) ChannelGetAddr(theChannel, OSC_FPGA_OTS_TTI_RECEIVE_TRACE);
    int txlen = strlen(txTrace);
    int rxlen = strlen(rxTrace+1); // dont know why there is one byte offset

    if( rxlen && txlen == rxlen )
    {
        if( strncmp( txTrace, (rxTrace+1), (txlen-2)) )
            return false;
        else
            return true;
    }
    return false;
}


inline void TSPII_OscMapperFpgaDrv::ChannelWrite(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theVal)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    *p = theVal;
}

inline void TSPII_OscMapperFpgaDrv::ChannelReadModWr(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, uint16 theVal)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    *p = (*p & ~theBitmask) | (theVal & theBitmask);
}

inline void TSPII_OscMapperFpgaDrv::ChannelReadModWr(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, HWIF_BITOP theOperation)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    *p = (*p & ~theBitmask) | (theOperation == BSET ? theBitmask : 0);
}

inline void TSPII_OscMapperFpgaDrv::ChannelReadModWrBool(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask, bool theOperation)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    *p = (*p & ~theBitmask) | (theOperation ? theBitmask : 0);
}

inline uint16 TSPII_OscMapperFpgaDrv::ChannelReadW1C(TSPII_OscMapperFpgaChannel theChannel, TSPII_OscMapperFpgaChannelReg theReg, uint16 theBitmask)
{
    volatile uint16 * p = ChannelGetAddr(theChannel, theReg);
    uint16            v = *p & theBitmask;
#ifdef __SIMULATION__
    *p &= ~v;
#else
    *p = v;
#endif
    return v;
}

#endif // TSPII_OSCMAPPERFPGADRV_H
