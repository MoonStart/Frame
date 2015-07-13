// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if !defined(AFX_MON_PILOTTONEPROCESSORREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_)
#define AFX_MON_PILOTTONEPROCESSORREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MON_Object.h"
#include "MON_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <TsPii/TSPII_PilotToneAction.h>

//##ModelId=3C7170DA01CE
class MON_PilotToneProcessorRequest : public MON_Object  
{
public:
	//##ModelId=3C7170DB0003
	MON_PilotToneProcessorRequest(CT_Wavelength theChannelId, 
                                  MON_RequestID theRequestId,
                                  uint32 theSamplingMode,
                                  TSPII_PilotTonePriority thePriority);
    MON_PilotToneProcessorRequest();

	//##ModelId=3C7170DB0005
	virtual ~MON_PilotToneProcessorRequest();

	//##ModelId=3C7170DB0021
    CT_Wavelength GetChannelId()    const { return myChannelId;}
    MON_RequestID GetRequestId()    const { return myRequestId;}
    uint32        GetSamplingMode() const { return mySamplingMode;}
    TSPII_PilotTonePriority GetPriority() const { return myPriority;}

	//##ModelId=3C7170DB0040
    MON_PilotToneProcessorRequest& operator=(const MON_PilotToneProcessorRequest& theRequest);
    virtual void Display(FC_Stream& theStream);
    bool operator==(const MON_PilotToneProcessorRequest& theRequest) const;
    
protected:
	//##ModelId=3C7170F10037
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C7170F1004B
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C7170F1005F
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C7170F10073
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//##ModelId=3C7170DB004A
    CT_Wavelength       myChannelId;
	//##ModelId=3C7170DB009A
    MON_RequestID       myRequestId;
    uint32              mySamplingMode;
    TSPII_PilotTonePriority myPriority;

};

#endif // !defined(AFX_MON_PILOTTONEPROCESSORREQUEST_H__C9070182_1978_11D6_96D6_0001022A1F94__INCLUDED_)
