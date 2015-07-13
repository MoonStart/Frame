#ifndef _TSPII_T1E1IF_H
#define _TSPII_T1E1IF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_T1E1If.h 
* Type:    C++ include
* Description:
*    Provides the generic platform independant interface for the T1/E1 
*    Transceiver/Framer & BITS clock source hardware.
*
*************************************END***************************************
*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_FacilityIds.h"
#include "CommonTypes/CT_SystemIds.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

#include <vector>

class TSPII_T1E1If : public TSPII_BaseIf
{

public:

    /*************************************************************************/
    /** Constructor                                                         **/
    /*************************************************************************/	
	TSPII_T1E1If(uint theClkOutSize, bool theDefault = false);
    
    /*************************************************************************/
	/** Destructor                                                          **/
    /*************************************************************************/
	virtual ~TSPII_T1E1If();

    /**************************************************************************/
	/** Utility functions                                                   **/
    /*************************************************************************/
    virtual void Reset();

    /*************************************************************************/
	/** T1E1 & Clock Entity configuration methods                           **/
    /*************************************************************************/
	virtual void SetLineCoding(CT_FAC_LineCode LineCode);
    virtual void SetFramingType(CT_FAC_FrameFormat FrameFormat);
    virtual void SetClkDisqualifyRef(bool);
	virtual void SetTimingSource(CT_ShelfId theShelf, CT_SlotId theSlot);
    virtual void SetSSMSaBit(CT_FAC_SaBit SaBit);

    /*************************************************************************/
    /** T1E1 & Clock Entity monitor methods                                 **/
    /*************************************************************************/
    virtual CT_FAC_LineCode GetLineCoding(void);
    virtual CT_FAC_FrameFormat GetFramingType(void);
	virtual bool GetTimingSource(CT_ShelfId& theShelf, CT_SlotId& theSlot) const;
    virtual CT_FAC_RxSsm GetRxSsm(void);
	virtual uint32 GetAis(void);
    virtual uint32 GetLof(void);
	virtual uint32 GetLos(void);
	virtual uint32 GetOffFreq(void);
    virtual bool GetClkDisqualifyRef(void);
    virtual CT_FAC_SaBit GetSSMSaBit(void);

    /*************************************************************************/
    /** Clock output control methods                                        **/
    /*************************************************************************/
    virtual void SetClkOutput(uint16 theSlotNum, bool theClkOutEnable);
    virtual void SetClkOutEnable(const vector<bool>& theClkOutEnableList);
    virtual bool GetClkOutEnable(uint16 mySlotNum);

    /*************************************************************************/
	/** Blackboard serialization                                            **/
    /*************************************************************************/
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream & WriteObject(ostream & theStream);
    virtual istream & ReadObject(istream & theStream);

    /*************************************************************************/
	/** Test Menus                                                          **/
    /*************************************************************************/
	virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void RefreshGet();
    void RefreshSet();

    /*************************************************************************/
	/** Configuration attributes                                            **/
    /*************************************************************************/
	CT_FAC_LineCode itsLineCode;       // Line Code for framer 
	CT_FAC_FrameFormat itsFramingType; // Framing Format 
	CT_ShelfId itsTimingSourceShelf;   // Source ref shelf id
	CT_SlotId  itsTimingSourceSlot;    // Source ref slot id
    CT_FAC_SaBit itsSsmSaBit;          // For E1s, need to configure which
                                       // bits is used for SSM value
    
    /*************************************************************************/
	/** Monitoring attributes                                               **/
    /*************************************************************************/
	CT_FAC_RxSsm itsSsmCode;    // T1E1 SSM (Sync Status Message) 
    uint32 itsLofDefect;        // T1E1 Loss of Frame
    uint32 itsLosDefect;        // T1E1 Loss of Signal
    uint32 itsAisDefect;        // T1E1 Alarm Indication Signal
	uint32 itsOffFreqDefect;    // T1E1 Off frequency defect

    /*************************************************************************/
	/** Clock enable/disqualify attributes                                  **/
    /*************************************************************************/
    bool   itsClkRefDisqualified;  // disqualified state

    // List of clock output enables that support the T1E1 facility
    vector<bool> myClkOutEnableList;
    uint   itsClkOutSize;         // Size of myClkOutEnableList
};

#endif // _TSPII_T1E1IF_H
