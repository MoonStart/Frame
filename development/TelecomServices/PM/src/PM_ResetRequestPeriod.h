/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Class to handle a reset request of any signal.
--------------------------------------------------------------------------*/

#ifndef PM_RESETREQUESTPERIOD_H
#define PM_RESETREQUESTPERIOD_H

#include <PM/PM_BbCfg.h>
#include <EPM/src/PM_RulesRmonGauge.h>


// Forward declaration of classes
class PM_BbValue;
class PM_GenericApplication;

//This class is responsible to handle the reset of the 
//parameter's value per parameter basis. It processes the 
//reset command received from the Admin.
//##ModelId=3C1F6F610303
class PM_ResetRequestPeriod
{
public:

    //Class default constructor.
    //##ModelId=3C1F6F6200CA
    PM_ResetRequestPeriod(uint8                     theNumberOfIndex, 
                          PM_GenericApplication&    theGenericApplication,
                          uint32                    thePortNumber);

    //Class default destructor.
    //##ModelId=3C1F6F6200D5
    virtual~ PM_ResetRequestPeriod();

    //Verifies if TCA and values has to be reset due to 
    //a reset counter request.
	//##ModelId=3E6E4CE20398
    virtual bool CheckResetCounterReqChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

    //Verifies if TCA and values has to be reset due to a reset gauge request.
    virtual bool CheckResetGaugeReqChange(PM_BbCfg&     theConfig, 
                                          PM_BbValue&   theValue,
                                          bool          theOduEntity=false,
                                          bool          theTcmEntity=false,
                                          bbindex_t     theOduTcmIndex=0);

    // Verifies if TCA and values has to be reset due to 
    // a reset RMON gauge request. This method was specifically 
    // created to augment the generic gauge behavior by resetting the
    // state of the status object if the current value register is to
    // be reset.
    virtual bool CheckResetRmonGaugeReqChange( PM_BbCfg&          theControl, 
                                               PM_BbValue&        theValue,
                                               PM_RulesRmonGauge& theRules );

protected:

    //Reference to the generic PM application.
	//##ModelId=3E6E4CE300D4
    PM_GenericApplication &myGenericApplication;

private:

    //Pointer to an array of reset counter for current value.
	//##ModelId=3E6E4CE3012E
    uint8 *myResetCurCount;

    //Pointer to an array of reset counter for minimum value.
	//##ModelId=3E6E4CE30174
    uint8 *myResetMinCount;

    //Pointer to an array of reset counter for maximum value.
	//##ModelId=3E6E4CE301F6
    uint8 *myResetMaxCount;

    //The number of counter handled by this class (in the 
    //array pointed by myResetCount).
    //##ModelId=3C1F6F620107
    uint16 myNumberOfParam;

    //The port number on which the reset request applied.
	//##ModelId=3E6E4CE3028B
    uint32 myPortNumber;

};

#endif //PM_RESETREQUESTPERIOD_H
