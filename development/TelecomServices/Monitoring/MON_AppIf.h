//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef MON_APPIF_H
#define MON_APPIF_H

#include <TelCommon/TEL_AppIf.h>
#include <CommonTypes/CT_SystemIds.h>
#include "MON_Region.h"
#include <T6100_TelecomIf.h>

class T6100_CardActiveRegion;

class MON_UpdateStatusAction;

//This is the implementation monitoring application.
//##ModelId=3C3B531302C4
class MON_AppIf: public TEL_AppIf
{
public:

	//Constructor.
	//##ModelId=3C3B53140190
    MON_AppIf(T6100_TelecomIf& theContext);

	//Virtual destructor.
	//##ModelId=3C3B53140191
    virtual ~MON_AppIf();


	//##ModelId=3C3B5314019A
    virtual MON_Region*   GetDefectsRegion();
	//##ModelId=3C3B531401A3
    virtual MON_Region*   GetStatusRegion();
	//##ModelId=3C3B531401A5
    virtual MON_Region*   GetCountersRegion();
	//##ModelId=3C3B531401AD
    virtual MON_Region*   GetConfigRegion();
    //
    virtual MON_Region*   GetProtConfigRegion();

	//##ModelId=3C7170F70270
    virtual MON_Region*   GetRequestRegion();
	//##ModelId=3C7170F70285
    virtual MON_Region*   GetResultRegion();

    virtual MON_Region*   GetAltRequestRegion();
    virtual MON_Region*   GetAltResultRegion();

    virtual MON_UpdateStatusAction* GetUpdateStatusAction();

    virtual void DoInitWarm(FC_Object* theObject);
    virtual void DoInitCold(FC_Object* theObject);
    virtual void DoInitConfig(FC_Object* theObject);

    virtual void Display(FC_Stream& theStream, uint16 theObjectIndex = USHRT_MAX);
    virtual FC_CmdProcessor::STATUS Set(int argc,char** argv);
    virtual FC_CmdProcessor::STATUS Debug(int argc,char** argv);
    virtual void Reset();

private:

};



#endif //MON_APPIF_H

