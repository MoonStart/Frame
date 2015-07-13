// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1SELECTOR_38F75FB60218_INCLUDED
#define _INC_SP_1PLUS1SELECTOR_38F75FB60218_INCLUDED

#include "SP_Definitions.h"
#include "SP_Selector.h"
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_1plus1ProtectionAction.h"
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_XcIf.h>
#include <Configuration/CFG_Definitions.h>

class TEL_Port;
class TEL_LinkedPort;

class SP_1plus1ProtectionAction;

//This class is responsible for performing the 1+1 signal 
//selection according to APS controller selection and 
//facility bandwidth. It also controls AIS-P/UNEQ-P 
//transmission according to configuration and selections. It 
//considered bidirectional and unidirectional mode as well 
//has Linear or UPSR mode.
class SP_1plus1Selector 
: public SP_Selector
{
protected:
	//Its protection action.
	SP_1plus1ProtectionAction& myProtectionAction;

	//The current side being selected.
    CT_SP_Protection mySelection;
	//The side (working or protection) chosen in the previous 
	//run (for switching statistic purposes).
    CT_SP_Protection myPreviousSelection;

	//Previous selection since last check.
    CT_SP_Protection mySelectionHistory;

public:
	//Resets connection to select working side.
    void Reset();

	//commit connections to hardware
	virtual void Commit();

	//Selects the working facility.
	void SelectWorking();

	//Selects the protection facility.
	void SelectProtection();

	//This method removes reset the AIS-P/UNEQ-P transmission 
	//to inactive (for APS purposes) using the CFG Protection 
	//regions.
	virtual void ClearConnections();

	//Constructor. Takes its protection action.
	SP_1plus1Selector(SP_1plus1ProtectionAction& theProtectionAction);

	//Destructor.
	virtual ~SP_1plus1Selector();
    virtual void Switch() = 0;


	//Connects the connection point (ingress) to the selected 
	//facility port. Also connect the connection point(s) 
	//(egress) to both facilities (bridged in bidir mode 
	//only) according to bandwidth. Updates the AIS-P/UNEQ-P 
	//transmission according to connection point 
	//configuration (linear mode only). Finally, updates the 
	//switching statistics accordingly (linear only).
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Returns current side selected.
    inline CT_SP_Protection GetSelection() {return mySelection;}

    //Dual module Y-Cable common switch implementation
    void YCableSelectorSwitch(TSPII_OpticalRegion* theTxOpticalRegion, 
                              TSPII_OpticalRegion* theRxOpticalRegion, 
                              CFG_OptProtCfgRegion* theProtRegion, 
                              bool portIsWorking);
    //Single module Y-Cable common laser control implementation
    void YCableLaserTxControl(TSPII_OpticalRegion* theWorkingTxOpticalRegion, 
                              TSPII_OpticalRegion* theProtectTxOpticalRegion, 
                              CFG_OptProtCfgRegion* theWorkingOptProtRegion,
                              CFG_OptProtCfgRegion* theProtectOptProtRegion);

	//Returns true if attributes have changes since last call.
    virtual bool HasChangedSinceLastCheck();

	//Sends the selector attributes to the stream.
    virtual ostream& WriteObject( ostream& theStream );
	//Extracts the selector attributes from the stream.
    virtual istream& ReadObject( istream& theStream );
	//Sends the selector attributes to the binary stream.
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extracts the selector attributes from the binary stream.
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//Returns its protection action.
    virtual SP_ProtectionAction&  GetProtectionAction() {return myProtectionAction;}

};

#endif /* _INC_SP_1PLUS1SELECTOR_38F75FB60218_INCLUDED */

