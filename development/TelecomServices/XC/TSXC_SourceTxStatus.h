/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_SourceTxStatus  Class Definition
--------------------------------------------------------------------------*/

#ifndef TSXC_SourceTxStatus_H
#define TSXC_SourceTxStatus_H
#include <XC/TSXC_CrossConnect.h>
//----------------------------------------------------------------------------------------------------------------------
//--- The purpose this module is to hold the snap shot of the curent and previous activation status.
//--- If a connection is deleted and it was active in the previous connection setup then that perticular 
//--- channel must be deactivated. This is all done at the TSXC Config action using this class.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
class TSXC_SourceTxStatus 
{
public:
	//--- Constructor 
	TSXC_SourceTxStatus(T6100_TelecomIf& theContext); 

	//--- Destructor
	~TSXC_SourceTxStatus();
    
    bool    IsDeactivationNeeded(UINT16 theChannel);        // zero based
    void    SetCurrentStatus(UINT16 theChannel);            // zero based
    void    ClearCurrent();    
    void    Reset();    
    
private:
    T6100_TelecomIf&                myContext;
    bool                            myCurrentActiveStatus [XC_MAX_XC_SSM_IM_LINE + XC_MAX_XC_SSM_IM_PORT];
    bool                            myPreviousActiveStatus[XC_MAX_XC_SSM_IM_LINE + XC_MAX_XC_SSM_IM_PORT];
};

#endif /* TSXC_SourceTxStatus_H */
