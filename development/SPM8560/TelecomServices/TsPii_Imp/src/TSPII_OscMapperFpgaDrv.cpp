/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : OSC8250
 AUTHOR      : Martin Piotte, 2003/1/20
 DESCRIPTION : Device driver for OSC mapper FPGA on OSC8250.
 NOTES       :
   TBD       = to be done or to be determined

--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"
#include "BaseClass/FC_Stream.h"

// Static members
TSPII_OscMapperFpgaDrv * TSPII_OscMapperFpgaDrv::ourInstance = NULL;
#ifdef __SIMULATION__
    uint32 gOscMapperDrvMem[TSPII_OSC_MAPPER_DRV_MEM_SPACE];
#endif

#define DISPLAY_GENERAL(x)     (sprintf(line, "[%04X] %-37s = 0x%04X\n", OSC_FPGA_##x, #x, word = Read(OSC_FPGA_##x)), fc_cout << line)
#define DISPLAY_CHANNEL(x, a, y)  (sprintf(line, "[%04X] %-37s = 0x%04X\n", OSC_FPGA_##y + a, #y, word = ChannelRead(x, OSC_FPGA_##y)), fc_cout << line)
#define DISPLAY_BYTES(x, a, y, z) for (j = -1; j < (z); j++) (j == -1 ? sprintf(line, "[%04X] %-37s =\n          ", OSC_FPGA_##y + a, #y) : sprintf(line, j == (z) - 1 ? " %02X %02X\n" : j%8 == 7 ? " %02X %02X\n          " : " %02X %02X", *(ChannelGetAddr(x, OSC_FPGA_##y) + j) >> 8 , *(ChannelGetAddr(x, OSC_FPGA_##y) + j) & 0xFF)), fc_cout << line
#define DISPLAY_WORDS(x, a, y, z, b) for (j = -1; j < (z); j++) (j == -1 ? sprintf(line, "[%04X] %-37s =\n          ", OSC_FPGA_##y + a, #y) : sprintf(line, j == (z) - 1 ? "  %04X\n"     : j%8 == 7 ? "  %04X\n          "     : "  %04X",     *(OchChannelGetAddr(x, (j+b),OSC_FPGA_##y) + j)                                                     )), fc_cout << line
#define DISPLAY_WORDS_OCH(x, a, y, z, b) for (j = -1; j < (z); j++) (j == -1 ? sprintf(line, "[%04X] %-37s =\n          ", OSC_FPGA_##y + a, #y) : sprintf(line, j == (z) - 1 ? "  %04X\n"     : j%8 == 7 ? "  %04X\n          "     : "  %04X",     *(OchChannelGetAddr(x, (j+b), OSC_FPGA_##y) + (j << OSC_FPGA_OCH_OFFSET))             )), fc_cout << line

#define DISPLAY_BIT(x)         (bit ? (sprintf(line, "           [%04X] %-26s = %s\n",   OSC_FPGA_##x, #x, word & OSC_FPGA_##x ? "ON" : "OFF"), fc_cout << line) : fc_cout)
#define DISPLAY_FIELD(x)       (bit ? (sprintf(line, "           [%04X] %-26s = 0x%X\n", OSC_FPGA_##x##_MASK, #x, (word & OSC_FPGA_##x##_MASK) >> OSC_FPGA_##x##_SHIFT), fc_cout << line) : fc_cout)
#define DISPLAY_OCH_RX(x, y, z, a, b)   if (och) for (j = (a); j < (z); j++) sprintf(line, "           OCh#%02d %5s %5s %3s\n", j + 1, *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + ( (j-b) << OSC_FPGA_OCH_OFFSET)) & OSC_FPGA_OCH_FDIP ? "FDI-P" : "", *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + ((j-b) << OSC_FPGA_OCH_OFFSET)) & OSC_FPGA_OCH_FDIO ? "FDI-O" : "", *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + ((j-b) << OSC_FPGA_OCH_OFFSET)) & OSC_FPGA_OCH_OCI ? "OCI"   : ""), fc_cout << line
#define DISPLAY_OCH_TX(x, y, z, a, b)   if (och) for (j = (a); j < (z); j++) sprintf(line, "           OCh#%02d %5s %5s %3s\n", j + 1, *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + (j-b)) & OSC_FPGA_OCH_FDIP ? "FDI-P" : "", *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + (j-b)) & OSC_FPGA_OCH_FDIO ? "FDI-O" : "", *(OchChannelGetAddr(x, j, OSC_FPGA_##y) + (j-b)) & OSC_FPGA_OCH_OCI ? "OCI"   : ""), fc_cout << line

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaDrv & TSPII_OscMapperFpgaDrv::GetInstance()
{
	if (ourInstance == NULL) ourInstance = new TSPII_OscMapperFpgaDrv(TSPII_OSC_MAPPER_DRV_BASE_ADDRESS);
	return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaDrv::DeleteInstance()
{
    delete ourInstance;
    ourInstance = NULL;
}

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaDrv::TSPII_OscMapperFpgaDrv(uint32 theBase) :
	HWIF_Device<TSPII_OscMapperFpgaGeneralReg, uint16, uint16>(theBase)
{
}

////////////////////////////////////////////////////////////////////////////////
TSPII_OscMapperFpgaDrv::~TSPII_OscMapperFpgaDrv()
{
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaDrv::Init()
{ 
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaDrv::WriteStaticRegisters()
{
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_OscMapperFpgaDrv::DisplayContent(int argc, char ** argv)
{
    int    i;
    int    j;
    uint16 word;
    char   line[256];
    bool   ip         = false;
    bool   bit        = false;
    bool   och        = false;
    bool   general    = false;
    bool   channel[4] = { false, false, false, false }; // TSPII_MAX_OSC*2
    //bool   auxilary   = false;
    bool   invalid    = false;

    // Parse argument line
    for (i = 0; i < argc; i++) for (j = 0; argv[i][j]; j++) switch (argv[i][j])
    {
        case 'a': channel[0] = channel[1] = channel[2] = channel[3] = general = true; break;
        case '1': channel[0] = true; break;
        case '2': channel[1] = true; break;
        case '3': channel[2] = true; break;
        case '4': channel[3] = true; break;
        case 'g': general    = true; break;
        case 'b': bit        = true; break;
        case 'i': ip         = true; break;
        case 'o': och        = true; break;
        //case 'x': auxilary   = true; break;
        default:  invalid    = true; break;
    }
    if (invalid || (!general && !channel[0] && !channel[1] && !channel[2] && !channel[3]))
    {
        fc_cout << "Usage: hw dumpOsc fpga [1|2|3|4|g(eneral)|a(ll)]+ [b(it)] [o(ch)] [i(p)] [(au)x(ilary)]" << endl;
        fc_cout << "where 1 = slot 1, 2 = slot 5, 3 = slot 13, and 4 = slot 19" << endl;
        return;
    }

    if (general)
    {
        DISPLAY_GENERAL(IDENTIFICATION);
        DISPLAY_GENERAL(REVISION);
        DISPLAY_GENERAL(INITIALIZATION);
        DISPLAY_GENERAL(MAPPER_CONFIGURATION);
            DISPLAY_FIELD(TX_FIFO_HI_WM);
            DISPLAY_FIELD(TX_FIFO_LO_WM);
            DISPLAY_BIT(CHANNEL_AB_DEST_SELECT);
            DISPLAY_BIT(FORMAT_E1);
        DISPLAY_GENERAL(PHY_CONTROL_FULL_DUPLEX);
            DISPLAY_BIT(PHY8B);
            DISPLAY_BIT(PHY8A);
        DISPLAY_GENERAL(PHY_IRQ_STATUS);
            DISPLAY_BIT(PHY8B);
            DISPLAY_BIT(PHY8A);
        DISPLAY_GENERAL(PHY_IRQ_LATCH);
            DISPLAY_BIT(PHY8B);
            DISPLAY_BIT(PHY8A);
        DISPLAY_GENERAL(PHY_INTERRUPT_ENABLE);
            DISPLAY_BIT(PHY8B);
            DISPLAY_BIT(PHY8A);
        DISPLAY_GENERAL(INTERRUPT_SUMMARY);
            DISPLAY_BIT(PHY_IRQ        );
            DISPLAY_BIT(BPCIA_B        );
            DISPLAY_BIT(ECC_B          );
            DISPLAY_BIT(OSC_CHANNEL_B  );
            DISPLAY_BIT(SMII_B         );
            DISPLAY_BIT(OCH_ALARM_B    );
            DISPLAY_BIT(OOS_ALARM_B    );
            DISPLAY_BIT(INGRESS_ALARM_B);
            DISPLAY_BIT(BPCIA_A        );
            DISPLAY_BIT(ECC_A          );
            DISPLAY_BIT(OSC_CHANNEL_A  );
            DISPLAY_BIT(SMII_A         );
            DISPLAY_BIT(OCH_ALARM_A    );
            DISPLAY_BIT(OOS_ALARM_A    );
            DISPLAY_BIT(INGRESS_ALARM_A);
        DISPLAY_GENERAL(INTERRUPT_SUMMARY_2);
            DISPLAY_BIT(BACKPLANE_CHANNEL_IRQ_ACTIVE_D);
            DISPLAY_BIT(ECC_IRQ_ACTIVE_D              );
            DISPLAY_BIT(OSC_CHANNEL_IRQ_ACTIVE_D      );
            DISPLAY_BIT(SMII_IRQ_ACTIVE_D             );
            DISPLAY_BIT(ALARM_IRQ_ACTIVE_D            );
            DISPLAY_BIT(OOS_ALARM_IRQ_ACTIVE_D        );
            DISPLAY_BIT(INGRESS_ALARM_IRQ_ACTIVE_D    );
            DISPLAY_BIT(BACKPLANE_CHANNEL_IRQ_ACTIVE_C);
            DISPLAY_BIT(ECC_IRQ_ACTIVE_C              );
            DISPLAY_BIT(OSC_CHANNEL_IRQ_ACTIVE_C      );
            DISPLAY_BIT(SMII_IRQ_ACTIVE_C             );
            DISPLAY_BIT(ALARM_IRQ_ACTIVE_C            );
            DISPLAY_BIT(OOS_ALARM_IRQ_ACTIVE_C        );
            DISPLAY_BIT(INGRESS_ALARM_IRQ_ACTIVE_C    );
        DISPLAY_GENERAL(BACKPLANE_CHANNEL_CONFIGURATION);
            DISPLAY_BIT(SIGNAL_DETECT_POLARITY       );
            DISPLAY_BIT(LINE_LOOPBACK_ENABLE         );
            DISPLAY_BIT(SERIAL_CLOCK_LOOP_TIME_SELECT);
            DISPLAY_BIT(TRANSMIT_SERIAL_CLOCK_OUT_OFF);
            DISPLAY_BIT(CSU_CLOCK_OUT_OFF            );
            DISPLAY_BIT(DIAGNOSTIC_LOOPBACK_ENABLE   );
    }
    for (i = 0; i < 4; i++) if (channel[i])
    {
        TSPII_OscMapperFpgaChannel c = OSC_FPGA_CHANNEL1;
		uint16 theOffSet = 0;
        if (i==0)
		{
			c = OSC_FPGA_CHANNEL1;
			theOffSet = 0;
		}
		else if (i==1)
		{
            c = OSC_FPGA_CHANNEL2;
			theOffSet = OSC_FPGA_CHANNEL_OFFSET;
		}
		else if (i==2)
		{
			c = OSC_FPGA_CHANNEL3;
			theOffSet = OSC_FPGA_CHANNEL_OFFSET*2;
		}
		else if (i==3)
		{
			c = OSC_FPGA_CHANNEL4;
			theOffSet = OSC_FPGA_CHANNEL_OFFSET*3;
		}
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_CONTROL);
            DISPLAY_BIT(DISABLE_LASER);
            DISPLAY_BIT(LOOP_TIMING_OPER_MODE_0);
            DISPLAY_BIT(OPT_FAC_LOOP_CTRL);
            DISPLAY_BIT(OPT_EQUIP_LOOP_CTRL);
            DISPLAY_BIT(LOS_TTL);
            DISPLAY_BIT(STS12_SELECT);
            DISPLAY_BIT(INTERNAL_LOS_DETECTION);
            DISPLAY_BIT(DISABLE_CRU);
            DISPLAY_BIT(OUT_OF_FRAME);
            DISPLAY_BIT(LOOP_TIMING_MODE1);
            DISPLAY_BIT(CRU_EQUIPMENT_LOOPBACK);
            DISPLAY_BIT(FACILITY_LOOPBACK);
            DISPLAY_BIT(EQUIPMENT_LOOPBACK);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_STATUS);
            DISPLAY_BIT(INTERNAL_FRAME_PULSE);
            DISPLAY_BIT(FRAME_PULSE);
            DISPLAY_BIT(CMU_LOCK_DETECT);
            DISPLAY_BIT(CRU_LOCK_DETECT);
            DISPLAY_BIT(LOS_DETECT);
            DISPLAY_BIT(LOL_DETECT);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_STATUS_LATCH);
            DISPLAY_BIT(INTERNAL_FRAME_PULSE);
            DISPLAY_BIT(FRAME_PULSE);
            DISPLAY_BIT(CMU_LOCK_DETECT);
            DISPLAY_BIT(CRU_LOCK_DETECT);
            DISPLAY_BIT(LOS_DETECT);
            DISPLAY_BIT(LOL_DETECT);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_STATUS_INTERRUPT_ENABLE);
            DISPLAY_BIT(INTERNAL_FRAME_PULSE);
            DISPLAY_BIT(FRAME_PULSE);
            DISPLAY_BIT(CMU_LOCK_DETECT);
            DISPLAY_BIT(CRU_LOCK_DETECT);
            DISPLAY_BIT(LOS_DETECT);
            DISPLAY_BIT(LOL_DETECT);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_BACKPLANE_CHANNEL_CONTROL);
		    DISPLAY_BIT(MASTERSHIP_CONTROL);
            DISPLAY_BIT(OPTICAL_SWITCH_CONTROL);
            DISPLAY_BIT(SIGNAL_DETECT);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_BACKPLANE_CHANNEL_STATUS);
            DISPLAY_BIT(OC3_TX_19M_CLOCK_OUT_OF_RANGE);
            DISPLAY_BIT(BAM_OOF);
            DISPLAY_BIT(BAM_LOF);
            DISPLAY_BIT(BAM_IF);
            DISPLAY_BIT(AMCC_S1213_RECEIVE_LOCK);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_BACKPLANE_CHANNEL_STATUS_LATCH);
            DISPLAY_BIT(OC3_TX_19M_CLOCK_OUT_OF_RANGE);
            DISPLAY_BIT(BAM_OOF);
            DISPLAY_BIT(BAM_LOF);
            DISPLAY_BIT(BAM_IF);
            DISPLAY_BIT(AMCC_S1213_RECEIVE_LOCK);
        DISPLAY_CHANNEL(c, theOffSet, CHANNEL_BACKPLANE_CHANNEL_STATUS_IRQ_ENABLE);
            DISPLAY_BIT(OC3_TX_19M_CLOCK_OUT_OF_RANGE);
            DISPLAY_BIT(BAM_OOF);
            DISPLAY_BIT(BAM_LOF);
            DISPLAY_BIT(BAM_IF);
            DISPLAY_BIT(AMCC_S1213_RECEIVE_LOCK);

        if (ip)
        {
            DISPLAY_CHANNEL(c, theOffSet, SMII_CONFIGURATION);
                DISPLAY_BIT(CFG_RXD0                  );
                DISPLAY_BIT(CFG_100MB                 );
                DISPLAY_BIT(CFG_FULL_DUPLEX           );
                DISPLAY_BIT(CFG_LINK_UP               );
                DISPLAY_BIT(CFG_JABBER_ERROR          );
                DISPLAY_BIT(CFG_UPPER_NIBBLE_OK       );
                DISPLAY_BIT(CFG_FALSE_CARRIER_DETECTED);
                DISPLAY_BIT(CFG_RXD7                  );
            DISPLAY_CHANNEL(c, theOffSet, SMII_STATUS);
                DISPLAY_BIT(STAT_TX_ER             );
                DISPLAY_BIT(STAT_100MB             );
                DISPLAY_BIT(STAT_FULL_DUPLEX       );
                DISPLAY_BIT(STAT_LINK_UP           );
                DISPLAY_BIT(STAT_JABBER_ERROR      );
            DISPLAY_CHANNEL(c, theOffSet, SMII_LATCH);
                DISPLAY_BIT(STAT_TX_ER             );
                DISPLAY_BIT(STAT_100MB             );
                DISPLAY_BIT(STAT_FULL_DUPLEX       );
                DISPLAY_BIT(STAT_LINK_UP           );
                DISPLAY_BIT(STAT_JABBER_ERROR      );
            DISPLAY_CHANNEL(c, theOffSet, SMII_INTERRUPT_ENABLE);
                DISPLAY_BIT(STAT_TX_ER             );
                DISPLAY_BIT(STAT_100MB             );
                DISPLAY_BIT(STAT_FULL_DUPLEX       );
                DISPLAY_BIT(STAT_LINK_UP           );
                DISPLAY_BIT(STAT_JABBER_ERROR      );
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_DEST_ADDR_1_2);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_1);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_2);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_DEST_ADDR_3_4);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_3);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_4);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_DEST_ADDR_5_6);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_5);
                DISPLAY_FIELD(ETHERNET_DEST_ADDR_BYTE_6);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_SOURCE_ADDR_BYTE_1_2);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_1);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_2);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_SOURCE_ADDR_BYTE_3_4);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_3);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_4);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_SOURCE_ADDR_BYTE_5_6);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_5);
                DISPLAY_FIELD(ETHERNET_SOURCE_ADDR_BYTE_6);
            DISPLAY_CHANNEL(c, theOffSet, ETHERNET_TYPE_BYTE_1_2);
                DISPLAY_FIELD(ETHERNET_TYPE_BYTE_1);
                DISPLAY_FIELD(ETHERNET_TYPE_BYTE_2);
            DISPLAY_CHANNEL(c, theOffSet, ECC_CONTROL);
                DISPLAY_BIT(TX_CTRL_MESSAGE_READY);
                DISPLAY_FIELD(HDLC_CONTROL_FIELD);
                DISPLAY_BIT(RX_CTRL_MESSAGE_CLEAR);
                DISPLAY_BIT(CFG_RX_PCKT_SNIFF_ENABLE);
                DISPLAY_BIT(ETH_SRC_ADDR_SEL);
                DISPLAY_BIT(CFG_PCKT_OUT_ENABLE);
                DISPLAY_BIT(CFG_PCKT_IN_ENABLE);
            DISPLAY_CHANNEL(c, theOffSet, ECC_STATUS);
                DISPLAY_BIT(TX_PCKT_FIFO_FULL);
                DISPLAY_BIT(HDLC_FRAMER_FIFO_FULL);
                DISPLAY_BIT(HDLC_STUFFER_FIFO_FULL);
                DISPLAY_BIT(HDLC_DESTUFFER_FIFO_FULL);
                DISPLAY_BIT(RX_PCKT_FIFO_FULL);
                DISPLAY_BIT(TX_CTRL_MESSAGE_SENT_ACK);
                DISPLAY_BIT(RX_CTRL_MESSAGE_READY);
                DISPLAY_FIELD(RX_CTRL_MESSAGE_ID);
            DISPLAY_CHANNEL(c, theOffSet, ECC_LATCH);
                DISPLAY_BIT(TX_PCKT_FIFO_FULL);
                DISPLAY_BIT(HDLC_FRAMER_FIFO_FULL);
                DISPLAY_BIT(HDLC_STUFFER_FIFO_FULL);
                DISPLAY_BIT(HDLC_DESTUFFER_FIFO_FULL);
                DISPLAY_BIT(RX_PCKT_FIFO_FULL);
                DISPLAY_BIT(TX_CTRL_MESSAGE_SENT_ACK);
                DISPLAY_BIT(RX_CTRL_MESSAGE_READY);
                DISPLAY_FIELD(RX_CTRL_MESSAGE_ID);
            DISPLAY_CHANNEL(c, theOffSet, ECC_INTERRUPT_ENABLE);
                DISPLAY_BIT(TX_PCKT_FIFO_FULL);
                DISPLAY_BIT(HDLC_FRAMER_FIFO_FULL);
                DISPLAY_BIT(HDLC_STUFFER_FIFO_FULL);
                DISPLAY_BIT(HDLC_DESTUFFER_FIFO_FULL);
                DISPLAY_BIT(RX_PCKT_FIFO_FULL);
                DISPLAY_BIT(TX_CTRL_MESSAGE_SENT_ACK);
                DISPLAY_BIT(RX_CTRL_MESSAGE_READY);
                DISPLAY_FIELD(RX_CTRL_MESSAGE_ID);
        }
        DISPLAY_CHANNEL(c, theOffSet, INGRESS_ALARM_STATUS);
            DISPLAY_BIT(OTS_TTI_LOF);
            DISPLAY_BIT(J0_LOF);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(SEF);
            DISPLAY_BIT(OOF);
            DISPLAY_BIT(LOF);
        DISPLAY_CHANNEL(c, theOffSet, INGRESS_ALARM_LATCH);
            DISPLAY_BIT(OTS_TTI_LOF);
            DISPLAY_BIT(J0_LOF);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(SEF);
            DISPLAY_BIT(OOF);
            DISPLAY_BIT(LOF);
        DISPLAY_CHANNEL(c, theOffSet, INGRESS_ALARM_INTERRUPT_ENABLE);
            DISPLAY_BIT(OTS_TTI_LOF);
            DISPLAY_BIT(J0_LOF);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(CV_LVL_2);
            DISPLAY_BIT(SEF);
            DISPLAY_BIT(OOF);
            DISPLAY_BIT(LOF);
        DISPLAY_CHANNEL(c, theOffSet, OOS_OVERHEAD_TRANSMIT);
            DISPLAY_BIT(OTS_BDIP);
            DISPLAY_BIT(OTS_BDIO);
            DISPLAY_BIT(OTS_PMI);
            DISPLAY_BIT(OMS_FDIP);
            DISPLAY_BIT(OMS_FDIO);
            DISPLAY_BIT(OMS_BDIP);
            DISPLAY_BIT(OMS_BDIO);
            DISPLAY_BIT(OMS_PMI);
        DISPLAY_CHANNEL(c, theOffSet, OOS_OVERHEAD_RECEIVE_STATUS);
            DISPLAY_BIT(OTS_BDIP);
            DISPLAY_BIT(OTS_BDIO);
            DISPLAY_BIT(OTS_PMI);
            DISPLAY_BIT(OMS_FDIP);
            DISPLAY_BIT(OMS_FDIO);
            DISPLAY_BIT(OMS_BDIP);
            DISPLAY_BIT(OMS_BDIO);
            DISPLAY_BIT(OMS_PMI );
        DISPLAY_CHANNEL(c, theOffSet, OOS_OVERHEAD_RECEIVE_LATCH);
            DISPLAY_BIT(OTS_BDIP);
            DISPLAY_BIT(OTS_BDIO);
            DISPLAY_BIT(OTS_PMI);
            DISPLAY_BIT(OMS_FDIP);
            DISPLAY_BIT(OMS_FDIO);
            DISPLAY_BIT(OMS_BDIP);
            DISPLAY_BIT(OMS_BDIO);
            DISPLAY_BIT(OMS_PMI );
        DISPLAY_CHANNEL(c, theOffSet, OOS_OVERHEAD_RECEIVE_INTERRUPT_ENABLE);
            DISPLAY_BIT(OTS_BDIP);
            DISPLAY_BIT(OTS_BDIO);
            DISPLAY_BIT(OTS_PMI);
            DISPLAY_BIT(OMS_FDIP);
            DISPLAY_BIT(OMS_FDIO);
            DISPLAY_BIT(OMS_BDIP);
            DISPLAY_BIT(OMS_BDIO);
            DISPLAY_BIT(OMS_PMI );
        DISPLAY_CHANNEL(c, theOffSet, K1_K2_TRANSMIT);
            DISPLAY_FIELD(K2);
            DISPLAY_FIELD(K1);
        DISPLAY_CHANNEL(c, theOffSet, K1_K2_RECEIVE);
            DISPLAY_FIELD(K2);
            DISPLAY_FIELD(K1);
        DISPLAY_CHANNEL(c, theOffSet, TRANSMIT_POWER_VALUE);
            DISPLAY_FIELD(TRANSMIT_POWER_VALUE_BYTE_2);
            DISPLAY_FIELD(TRANSMIT_POWER_VALUE_BYTE_1);
        DISPLAY_CHANNEL(c, theOffSet, RECEIVE_POWER_VALUE);
            DISPLAY_FIELD(RECEIVE_POWER_VALUE_BYTE_2);
            DISPLAY_FIELD(RECEIVE_POWER_VALUE_BYTE_1);
        DISPLAY_CHANNEL(c, theOffSet, OCH_IRQ_1_16);
        DISPLAY_CHANNEL(c, theOffSet, OCH_IRQ_17_32);
        DISPLAY_CHANNEL(c, theOffSet, OCH_IRQ_33_48);
        DISPLAY_CHANNEL(c, theOffSet, OCH_IRQ_49_64);
        DISPLAY_CHANNEL(c, theOffSet, DEBUG);
            DISPLAY_BIT(ETHERNET_CRC_INVALIDATE);
            DISPLAY_BIT(FRAMING_ALM_DISABLE);
            DISPLAY_BIT(HDLC_FCS_INVALIDATE);
            DISPLAY_BIT(B2_INVALIDATE);
            DISPLAY_BIT(B1_INVALIDATE);
            DISPLAY_BIT(DESCRAMBLING_DISABLE);
            DISPLAY_BIT(SCRAMBLING_DISABLE);
        DISPLAY_CHANNEL(c, theOffSet, COUNTER_RESET_CONTROL1);
            DISPLAY_BIT(TX_FIFO_MAX_DEPTH_RST);
            DISPLAY_BIT(TX_FIFO_HI_WM_RST);
            DISPLAY_BIT(TX_FIFO_OVERRUN_RST);
            DISPLAY_BIT(HDLC_FCS_ERROR_RST);
            DISPLAY_BIT(ETHER_CRC_ERROR_RST);
            DISPLAY_BIT(B2_RST);
            DISPLAY_BIT(B1_RST);
        DISPLAY_CHANNEL(c, theOffSet, COUNTER_RESET_CONTROL2);
            DISPLAY_BIT(PAUSE_FRAME_RST);
            DISPLAY_BIT(SMII_RX_PACKET_RST);
            DISPLAY_BIT(ECC_RX_CTRL_MSG_RST);
            DISPLAY_BIT(ECC_RX_PACKET_RST);
            DISPLAY_BIT(HDLC_DEFRAMER_RST);
            DISPLAY_BIT(HDLC_DESTUFFER_RST);
            DISPLAY_BIT(HDLC_STUFFER_RST);
            DISPLAY_BIT(HDLC_FRAMER_RST);
            DISPLAY_BIT(ECC_TX_CTRL_MSG_RST);
            DISPLAY_BIT(ECC_TX_PACKET_RST);
            DISPLAY_BIT(SMII_TX_PACKET_RST);
        if (ip)
        {
            DISPLAY_CHANNEL(c, theOffSet, PRBS_GENERATOR_CONFIGURATION);
                DISPLAY_FIELD(TEST_PATTERN);
                DISPLAY_BIT(PATTERN_SELECT);
                DISPLAY_BIT(E1_OC3_PRBS_RESET);
                DISPLAY_BIT(OC3_PRBS_ENABLE);
            DISPLAY_CHANNEL(c, theOffSet, PRBS_ANALYZER_CONFIGURATION);
                DISPLAY_FIELD(TEST_PATTERN);
                DISPLAY_BIT(PATTERN_SELECT);
                DISPLAY_BIT(E1_OC3_PRBS_RESET);
                DISPLAY_BIT(OC3_PRBS_ENABLE);
            DISPLAY_CHANNEL(c, theOffSet, ETHER_TX_CRC_ERR_COUNTER   );
            DISPLAY_CHANNEL(c, theOffSet, PRBS_ANALYZER_ERROR_COUNTER);
            DISPLAY_CHANNEL(c, theOffSet, HDLC_FCS_ERROR_COUNTER     );
            DISPLAY_CHANNEL(c, theOffSet, TX_FIFO_OVERRUN_COUNTER    );
            DISPLAY_CHANNEL(c, theOffSet, TX_FIFO_HI_WM_COUNTER      );
            DISPLAY_CHANNEL(c, theOffSet, TX_FIFO_MAX_DEPTH_COUNTER  );
            DISPLAY_CHANNEL(c, theOffSet, TX_SMII_IP_PACKET_COUNTER  );
            DISPLAY_CHANNEL(c, theOffSet, TX_ECC_IP_PACKET_COUNTER   );
            DISPLAY_CHANNEL(c, theOffSet, TX_ECC_CTRL_MESSAGE_COUNTER);
            DISPLAY_CHANNEL(c, theOffSet, HDLC_FRAMER_COUNTER        );
            DISPLAY_CHANNEL(c, theOffSet, HDLC_STUFFER_COUNTER       );
            DISPLAY_CHANNEL(c, theOffSet, RX_SMII_IP_PACKET_COUNTER  );
            DISPLAY_CHANNEL(c, theOffSet, RX_ECC_IP_PACKET_COUNTER   );
            DISPLAY_CHANNEL(c, theOffSet, RX_ECC_CTRL_MESSAGE_COUNTER);
            DISPLAY_CHANNEL(c, theOffSet, HDLC_DEFRAMER_COUNTER      );
            DISPLAY_CHANNEL(c, theOffSet, HDLC_DESTUFFER_COUNTER     );
            DISPLAY_CHANNEL(c, theOffSet, RX_PAUSE_COUNTER           );
        }
        DISPLAY_CHANNEL(c, theOffSet, B1_ERROR_COUNTER);
        DISPLAY_CHANNEL(c, theOffSet, B2_ERROR_COUNTER);
        DISPLAY_BYTES(c, theOffSet, SONET_J0_TRANSMIT_BRAM, 8);
        DISPLAY_BYTES(c, theOffSet, SONET_J0_RECEIVE_BRAM, 8);
        DISPLAY_BYTES(c, theOffSet, OTS_TTI_TRANSMIT_BRAM, 32);
        DISPLAY_BYTES(c, theOffSet, OTS_TTI_RECEIVE_BRAM, 32);

        if (och)
        {
            DISPLAY_WORDS_OCH(c, theOffSet, OCH_RECEIVE_BRAM, 64, 0);
            DISPLAY_WORDS_OCH(c, theOffSet+OSC_FPGA_OCH_64_87_OFFSET, OCH_RECEIVE_BRAM, 24, OSC_FPGA_OCH_64_VAL);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_BRAM, 64, 0, 0);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_BRAM, 88, 64, OSC_FPGA_OCH_64_VAL);
            DISPLAY_WORDS_OCH(c, theOffSet, OCH_RECEIVE_LATCH_BRAM, 64, 0);
            DISPLAY_WORDS_OCH(c, theOffSet+OSC_FPGA_OCH_64_87_OFFSET, OCH_RECEIVE_LATCH_BRAM, 24, OSC_FPGA_OCH_64_VAL);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_LATCH_BRAM, 64, 0, 0);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_LATCH_BRAM, 88, 64, OSC_FPGA_OCH_64_VAL);
            DISPLAY_WORDS_OCH(c, theOffSet, OCH_RECEIVE_INTERRUPT_ENABLE_BRAM, 64, 0);
            DISPLAY_WORDS_OCH(c, theOffSet+OSC_FPGA_OCH_64_87_OFFSET, OCH_RECEIVE_INTERRUPT_ENABLE_BRAM, 24, OSC_FPGA_OCH_64_VAL);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_INTERRUPT_ENABLE_BRAM, 64, 0, 0);
                DISPLAY_OCH_RX(c, OCH_RECEIVE_INTERRUPT_ENABLE_BRAM, 88, 64, OSC_FPGA_OCH_64_VAL);
            DISPLAY_WORDS(c, theOffSet, OCH_TRANSMIT_BRAM, 64, 0);
            DISPLAY_WORDS(c, theOffSet+OSC_FPGA_OCH_64_87_OFFSET, OCH_TRANSMIT_BRAM, 24, OSC_FPGA_OCH_64_VAL);
                DISPLAY_OCH_TX(c, OCH_TRANSMIT_BRAM, 64, 0, 0);
                DISPLAY_OCH_TX(c, OCH_TRANSMIT_BRAM, 88, 64, OSC_FPGA_OCH_64_VAL);
        }
    }
}
