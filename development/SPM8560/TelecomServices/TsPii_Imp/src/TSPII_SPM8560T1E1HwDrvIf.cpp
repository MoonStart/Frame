/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SPM8560T1E1HwDrvIf.cpp 
* Type:    C++ source
* Description:
*     Definition of the class TSPII_SPM8560T1E1HwDrvIf which defines the
*     T1E1 Interface entity of the SPM8560.        
*
*     The T1E1 entity is used to configure and monitor T1/E1 interface 
*     (Transceiver/Framer & BITS Clock source & hdp (for derived timing)) hardware, and also
*     the clock distribution and control. 
*
*************************************END***************************************
*/

#include "TsPii/TSPII_BaseIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii_Imp/TSPII_SPM8560T1E1HwDrvIf.h"



/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf constructor
*
* Description:
*     TSPII_SPM8560T1E1HwDrvIf class constructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_SPM8560T1E1HwDrvIf::TSPII_SPM8560T1E1HwDrvIf(uint theClkOutSize, uint theUnit) :
    TSPII_T1E1If(theClkOutSize, false),
    itsTimingCtrl(HdpTimingCard::GetInstance((theUnit == 0) ? HdpTiming::Reference::A : HdpTiming::Reference::B)),
	itsHdpDev(HdpSpecializedDevice::GetInstance((theUnit == 0) ? HdpApi::Hdp::A : HdpApi::Hdp::B))
{
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf destructor
*
* Description:
*     TSPII_SPM8560T1E1HwDrvIf class destructor
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     No return type
*
*************************************END***************************************
*/
TSPII_SPM8560T1E1HwDrvIf::~TSPII_SPM8560T1E1HwDrvIf()
{   
}

//////////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560T1E1HwDrvIf::UpdateValues()
{
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::SetLineCoding() class method
*
* Description:
*     Used to configure the Line Code for the T1/E1 framer hardware.
*
* Inputs:
*     Value which specifies the possible T1E1 framer hardware line codes.
*     
*     Values:
*         CT_LineCode_AMI   - Alternate Mark Inversion
*         CT_LineCode_B8ZS  - Binary Eight Zero Substitution
*         CT_LineCode_HDB3  - E1 line coding
*
* Outputs:
*     T1E1 framer hardware - line encoding is configured.
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SPM8560T1E1HwDrvIf::SetLineCoding(CT_FAC_LineCode LineCode)
{
    // since the enums are different TSPII needs to perform a translation
    if (LineCode == CT_LineCode_AMI)
    {
        itsTimingCtrl.setLineCode(ReferenceApi::LineCode::AMI);
    }
    else if (LineCode == CT_LineCode_B8ZS)
    {
        itsTimingCtrl.setLineCode(ReferenceApi::LineCode::B8ZS);
    }
    else if (LineCode == CT_LineCode_HDB3)
    {
        itsTimingCtrl.setLineCode(ReferenceApi::LineCode::HDB3);
    }

}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::SetFramingType() class method
*
* Description:
*     Used to configure the Framing Format for the T1/E1 framer hardware.
*
* Inputs:
*     Value which specifies the possible T1E1 framer formats.
*     
*     Values:
*         CT_FrameFormat_SF   - Super Frame
*         CT_FrameFormat_ESF  - Extended Super Frame
*         CT_FrameFormat_NOCRC4  - E1 Frame
*         CT_FrameFormat_CRC4  - E1 Frame
*
* Outputs:
*     T1E1 framer hardware - frame format is configured.
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SPM8560T1E1HwDrvIf::SetFramingType(CT_FAC_FrameFormat FramingType)
{
    // since the enums are different TSPII needs to perform a translation
    if (FramingType == CT_FrameFormat_SF)
    {
        itsTimingCtrl.setFrameFormat(ReferenceApi::FrameFormat::SF);
    }
    else if (FramingType == CT_FrameFormat_ESF)
    {
        itsTimingCtrl.setFrameFormat(ReferenceApi::FrameFormat::ESF);
    }
    else if (FramingType == CT_FrameFormat_NOCRC4)
    {
        itsTimingCtrl.setFrameFormat(ReferenceApi::FrameFormat::NOCRC4);
    }
    else if (FramingType == CT_FrameFormat_CRC4)
    {
        itsTimingCtrl.setFrameFormat(ReferenceApi::FrameFormat::CRC4);
    }
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::SetTimingSource() class method
*
* Description:
*     Used to configure the timing source for the hdp device
*
* Inputs:
*     Shelf and Slot Id
*
* Outputs:
*     The HDP is configured to select the correct timing source inputs
*            
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SPM8560T1E1HwDrvIf::SetTimingSource(CT_ShelfId theShelf, CT_SlotId theSlot)
{
	//Convert shelf and slot to Enum
	int i,j;
	HdpApi::TimingSource::Enum theTimingSource = HdpApi::TimingSource::LOCAL_BITS;

	switch (theShelf)
	{
	case OPTICAL_SHELF_1:
		switch (theSlot)
		{
		case UNKNOWN_SLOT_ID: // Shelf 1, Slot 0 maps to local BITS
            theTimingSource = HdpApi::TimingSource::LOCAL_BITS;
			break;
		default:
			for (i=1,j=(int)HdpApi::TimingSource::LOCAL_SLOT1; i<=19; i++,j++)
			{
				if (theSlot == i)
				{
                    theTimingSource = HdpApi::TimingSource::Enum(j);
					break;
				}
			}
			break;
		}
	default:
		for (i=PORT_SHELF_1, j=(int)HdpApi::TimingSource::REMOTE_SHELF1; i<= PORT_SHELF_12; i++,j++)
		{
			if (theShelf == i)
			{
                theTimingSource = HdpApi::TimingSource::Enum(j);
				break;
			}
		}
		break;
		
	}
	
	itsHdpDev.setTimingSource(theTimingSource);
}         
/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::SetSSMSaBit() class method
*
* Description:
*     Used to configure the SaBit containing the SSM for E1 framer hardware.
*
* Inputs:
*     Value which specifies the possible E1 Sa Bits used for SSM.
*     
*     Values:
*         CT_SaBit_4 .. CT_SaBit_8, CT_SaBit_UNKNOWN
*
* Outputs:
*     T1E1 framer hardware - E1 Sa Bit used for SSM is configured.
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SPM8560T1E1HwDrvIf::SetSSMSaBit(CT_FAC_SaBit theSaBit)
{
    // since the enums are different TSPII needs to perform a translation
    switch( theSaBit )
    {
        case CT_SaBit_4:
            itsTimingCtrl.setSsmSaBit(ReferenceApi::SsmSaBit::SaBit_4 );
            break;
        case CT_SaBit_5:
            itsTimingCtrl.setSsmSaBit(ReferenceApi::SsmSaBit::SaBit_5 );
            break;
        case CT_SaBit_6:
            itsTimingCtrl.setSsmSaBit(ReferenceApi::SsmSaBit::SaBit_6 );
            break;
        case CT_SaBit_7:
            itsTimingCtrl.setSsmSaBit(ReferenceApi::SsmSaBit::SaBit_7 );
            break;
        case CT_SaBit_8:
            itsTimingCtrl.setSsmSaBit(ReferenceApi::SsmSaBit::SaBit_8 );
            break;
        default:
            // Don't write hardware
            break;
    }
    return;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetLineCoding() class method
*
* Description:
*     Used to read the line code from the Timing Controller.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     CT_FAC_LineCode theFACLineCode
*
*************************************END***************************************
*/
CT_FAC_LineCode TSPII_SPM8560T1E1HwDrvIf::GetLineCoding(void)
{
    ReferenceApi::LineCode::Enum theRefLineCode;
    CT_FAC_LineCode theFACLineCode = CT_FAC_LineCode(CT_LineCode_ALL);

    // read the timing reference
    theRefLineCode = itsTimingCtrl.getLineCode();

    // since the enums are different TSPII needs to perform a translation
    if (theRefLineCode == ReferenceApi::LineCode::AMI)
    {
        theFACLineCode = CT_FAC_LineCode(CT_LineCode_AMI);
    }
    else if (theRefLineCode == ReferenceApi::LineCode::B8ZS)
    {
        theFACLineCode = CT_FAC_LineCode(CT_LineCode_B8ZS);
    }
    else if (theRefLineCode == ReferenceApi::LineCode::HDB3)
    {
        theFACLineCode = CT_FAC_LineCode(CT_LineCode_HDB3);
    }
    else
    {
        theFACLineCode = CT_FAC_LineCode(CT_LineCode_ALL);
    }

    return theFACLineCode;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetFramingType() class method
*
* Description:
*     Used to read the frame format from the the Timing Controller.
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     CT_FAC_FrameFormat theFACFrameFormat
*
*************************************END***************************************
*/
CT_FAC_FrameFormat TSPII_SPM8560T1E1HwDrvIf::GetFramingType(void)
{
    ReferenceApi::FrameFormat::Enum theRefFrameFormat;
    CT_FAC_FrameFormat theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_ALL);

    // read the timing reference
    theRefFrameFormat = itsTimingCtrl.getFrameFormat();

    // since the enums are different TSPII needs to perform a translation
    if (theRefFrameFormat == ReferenceApi::FrameFormat::ESF)
    {
        theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_ESF);
    }
    else if (theRefFrameFormat == ReferenceApi::FrameFormat::SF)
    {
        theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_SF);
    }
    else if (theRefFrameFormat == ReferenceApi::FrameFormat::NOCRC4)
    {
        theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_NOCRC4);
    }
    else if (theRefFrameFormat == ReferenceApi::FrameFormat::CRC4)
    {
        theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_CRC4);
    }
    else
    {
        theFACFrameFormat = CT_FAC_FrameFormat(CT_FrameFormat_ALL);
    }
    
    return theFACFrameFormat; 
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetTimingSource() class method
*
* Description:
*     Used to retrieve the input source timing configuration from the hdp device
*
* Inputs:
*     None
*
* Outputs:
*     Update itsTimingSourceShelf
*            itsTimingSourceSlot
*
* Returns:
*     void
*
*************************************END***************************************
*/
bool TSPII_SPM8560T1E1HwDrvIf::GetTimingSource(CT_ShelfId& theShelf, CT_SlotId& theSlot) const
{
	bool found = false;
	HdpApi::TimingSource::Enum theTimingSource = itsHdpDev.getTimingSource();
    int i, j;

	if (theTimingSource == HdpApi::TimingSource::LOCAL_BITS)
	{
		theShelf = OPTICAL_SHELF_1;
		theSlot  = UNKNOWN_SLOT_ID;
		found = true;
	}
	else
	{
		for (i=(int)HdpApi::TimingSource::LOCAL_SLOT1,j=1; i<=(int)HdpApi::TimingSource::LOCAL_SLOT19; i++,j++)
		{
			if (theTimingSource == HdpApi::TimingSource::Enum(i))
			{
                theShelf = OPTICAL_SHELF_1;
		        theSlot  = (CT_SlotId)j;
				found = true;
				break;
			}
		}

		if (found == false)
		{
			for (i=(int)HdpApi::TimingSource::REMOTE_SHELF1,j=PORT_SHELF_1; i<=(int)HdpApi::TimingSource::REMOTE_SHELF12; i++,j++)
			{
			    if (theTimingSource == HdpApi::TimingSource::Enum(i))
				{
                    theShelf = (CT_ShelfId)j;
		            theSlot  = 0;
				    found = true;
				    break;
				}
			}
		}
	}
	
	return found;
}
/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetSSMSaBit() class method
*
* Description:
*     Used to retrieve the SaBit containing the SSM for E1 framer hardware.
*
* Inputs:
*     None
*
* Outputs:
*     CT_SaBit_4 .. CT_SaBit_8, CT_SaBit_UNKNOWN
*
* Returns:
*     void
*
*************************************END***************************************
*/
CT_FAC_SaBit TSPII_SPM8560T1E1HwDrvIf::GetSSMSaBit(void)
{
    ReferenceApi::SsmSaBit::Enum theTcSaBit;
    CT_FAC_SaBit theSaBit;

    theTcSaBit = itsTimingCtrl.getSsmSaBit();

    // since the enums are different TSPII needs to perform a translation
    switch( theTcSaBit )
    {
        case ReferenceApi::SsmSaBit::SaBit_4:
            theSaBit = CT_SaBit_4;
            break;
        case ReferenceApi::SsmSaBit::SaBit_5:
            theSaBit = CT_SaBit_5;
            break;
        case ReferenceApi::SsmSaBit::SaBit_6:
            theSaBit = CT_SaBit_6;
            break;
        case ReferenceApi::SsmSaBit::SaBit_7:
            theSaBit = CT_SaBit_7;
            break;
        case ReferenceApi::SsmSaBit::SaBit_8:
            theSaBit = CT_SaBit_8;
            break;
        case ReferenceApi::SsmSaBit::UNKNOWN:
        default:
            theSaBit = CT_SaBit_UNKNOWN;
            break;
    }
    return( theSaBit );
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetRxSsm() class method
*
* Description:
*     Used to read the Sync Status Message being received at the Timing 
*     controller for the T1/E1 facility. 
*
* Inputs:
*     None
*
* Outputs:
*     None
*
* Returns:
*     CT_FAC_RxSsm theFACSsm
*
*************************************END***************************************
*/
CT_FAC_RxSsm TSPII_SPM8560T1E1HwDrvIf::GetRxSsm(void)
{
    ReferenceApi::Ssm::Enum theRefSsm;
    CT_FAC_RxSsm theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ALL);

    theRefSsm = itsTimingCtrl.pollSSM();

    switch (theRefSsm) 
    {
    case ReferenceApi::Ssm::DUS:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_DUS);
        break;

    case ReferenceApi::Ssm::PNO:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_PNO);
        break;

    case ReferenceApi::Ssm::PRS:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_PRS);
        break;

    case ReferenceApi::Ssm::SMC:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_SMC);
        break;

    case ReferenceApi::Ssm::ST2:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ST2);
        break;

    case ReferenceApi::Ssm::ST3:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ST3);
        break;

    case ReferenceApi::Ssm::ST3E:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ST3E);
        break;

    case ReferenceApi::Ssm::ST4:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ST4);
        break;

    case ReferenceApi::Ssm::STU:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_STU);
        break;
    
    case ReferenceApi::Ssm::TNC:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_TNC);
        break;

    case ReferenceApi::Ssm::UNKNOWN:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ALL);
        break;

    // SDH SSM values
    case ReferenceApi::Ssm::PRC:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_PRC);
        break;

    case ReferenceApi::Ssm::SSUA:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_SSUA);
        break;

    case ReferenceApi::Ssm::SSUB:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_SSUB);
        break;

    case ReferenceApi::Ssm::SEC:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_SEC);
        break;

    case ReferenceApi::Ssm::DNU:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_DNU);
        break;

    default:
        theFACSsm = CT_FAC_RxSsm(CT_RxSsm_ALL);
        break;
    }

    return theFACSsm; 
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetAis() class method
*
* Description:
*     Used to read the current AIS (Alarm Indication Signal) defect.
*
* Inputs:
*     None
*
* Outputs:
*     Updated AIS defect counter
*
* Returns:
*     itsAisDefect
*
*************************************END***************************************
*/
uint32 TSPII_SPM8560T1E1HwDrvIf::GetAis(void)
{
    bool CurState;    // Current state of the T1E1 AIS (Alarm Indication Signal)
    bool PrevState;   // State from previous Getxxx()

    // This method is called to detect the current AIS alarm and 
    // update the AIS defect state counter
    CurState = itsTimingCtrl.getAIS();
    PrevState = TSPII_DEFECT(itsAisDefect);

    if (CurState != PrevState)
    {
        // Compared current to previous and detected a transition
        itsAisDefect++;
    }
    else
    {
        // No change in alarm state.
    }

    return itsAisDefect;  
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetLof() class method
*
* Description:
*     Used to read the current LOF (Loss Of Frame) defect.  
*
* Inputs:
*     None
*
* Outputs:
*     Updated LOF defect counter
*
* Returns:
*     itsLofDefect
*
*************************************END***************************************
*/
uint32 TSPII_SPM8560T1E1HwDrvIf::GetLof(void)
{
    bool CurState;    // Current state of the T1E1 LOF (Loss of Frame)
    bool PrevState;   // State from previous Getxxx()

    // This method is called to detect the current LOF state and 
    // update the LOF defect state counter
    CurState = itsTimingCtrl.getLOF();
    PrevState = TSPII_DEFECT(itsLofDefect);

    if (CurState != PrevState)
    {
        // Compared current to previous and detected a transition
        itsLofDefect++;
    }
    else
    {
        // No change in state.
    }

    return itsLofDefect;  
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetLos() class method
*
* Description:
*     Used to read the current LOS (Loss Of Signal) defect.  
*
* Inputs:
*     None
*
* Outputs:
*     Updated LOS defect counter
*
* Returns:
*     itsLosDefect
*
*************************************END***************************************
*/
uint32 TSPII_SPM8560T1E1HwDrvIf::GetLos(void)
{
    bool CurState;    // Current state of the T1E1 LOS (Loss Of Signal)  
    bool PrevState;   // State from previous Getxxx()

    // This method is called to detect the current LOF state and 
    // update the LOF defect state counter
    CurState = itsTimingCtrl.getLOS();
    PrevState = TSPII_DEFECT(itsLosDefect);

    if (CurState != PrevState)
    {
        // Compared current to previous and detected a transition
        itsLosDefect++;
   }
    else
    {
        // No change in state.
    }

    return itsLosDefect;
}

/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::SetClkDisqualifyRef() class method
*
* Description:
*     Used to configure the clock reference availability 
*
* Inputs:
*
* Outputs:
*
* Returns:
*     void
*
*************************************END***************************************
*/
void TSPII_SPM8560T1E1HwDrvIf::SetClkDisqualifyRef(bool theClkRefDisqualified)
{
    itsTimingCtrl.setRefAvail(!theClkRefDisqualified); 
}


/************************************BEGIN*************************************
*
* Function:    TSPII_SPM8560T1E1HwDrvIf::GetClkDisqualifyRef() class method
*
* Description:
*     Used to read back the clock reference availability.
*
* Inputs:
*     None
*
* Outputs:
*
* Returns:
*     itsClkRefDisqualified
*
*************************************END***************************************
*/
bool TSPII_SPM8560T1E1HwDrvIf::GetClkDisqualifyRef(void)
{
	return itsTimingCtrl.getRefAvail();
}



