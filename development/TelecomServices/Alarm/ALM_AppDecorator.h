/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Signal Alarm application decorator definition.
--------------------------------------------------------------------------*/
#ifndef __ALM_APP_DECORATOR_H__
#define __ALM_APP_DECORATOR_H__

#include <AppFramework/FC_BbAppDecoratorImp.h>
#include "ALM_AppIf.h"

class FC_Context;
class ALM_LayerFailures;
template <class OBJECT_TYPE> class ALM_FailureRegionImp;
class T6100_CardActiveRegion;

//This is the alarm processing application interface decorator use by Signal Alarm only.
//##ModelId=3C506C3502C7
class ALM_AppDecorator : public FC_BbAppDecoratorImp<ALM_AppIf>
{
public:

	//Class constructor.
    //
    //PARAM ALM_AppIf* theAppIfPtr: a pointer to the alarm application interface to decorate.
    //
    //PARAM bool theAutoDelete = true: the auto delete flag. If true, this decorator will be responsible to delete the instance pointed by theAppIfPtr.
	//##ModelId=3C506C350373
	ALM_AppDecorator(ALM_AppIf* theAppIfPtr, bool theAutoDelete = true);

	//Virtual destructor.
	//##ModelId=3C506C35037E
	virtual ~ALM_AppDecorator();

	//This method returns a pointer to the filtered region.
    //
    //RETURN ALM_FailureRegionImp<ALM_FailureBase>*: a pointer to the filtered failure region.
    //##ModelId=3C6D0E600289
	virtual ALM_FailureRegionImp<ALM_FailureBase>* GetFilteredRegionPtr() const;

	//This method returns the number of BB objects in the region.
    //
    //RETURN int: the number of BB object (element) in the region instantiated in this application.
	//##ModelId=3C603CA20185
    virtual int GetNumberOfElement() const;

    //This method returns the offset to be used, if any, into the monitored
    // region.
    //
    //RETURN int: the offset instantiated in this application.
    virtual int GetMonElementOffset() const;

	//Get the pointer to the layer failure instance according to the index
	//
	//PARAM int theIndex: The index of the layer failure object in the vector. 
	//This index corresponds to the BB object index in the region.
	//
	//RETURN ALM_LayerFailures*: a pointer to the corresponding layer failure.
	//##ModelId=3C95FE0B014C
    virtual ALM_LayerFailures* GetLayerFailurePtr(int theIndex) const;

    //Return a flag to indicate that all defects must be masked.
    //
    //PARAM int theIndex: the BB object index in the region.
    //
    //RETURN bool: the value of the flag.
	//##ModelId=3CC4D1D502F1
    virtual bool GetMaskAllDefectFlag(int theIndex) const;

    //Return the suffix of a blackboard key.
    //
    //RETURN const string&: the suffix of a blackboard key.
	//##ModelId=3CC4D1D50391
    virtual const string& GetKeySuffix() const;

    //Return the instance name of this instance as a string of characters.
    //
    //RETURN const char*: a pointer to the instance name.
	//##ModelId=3CC4D1D503E1
    virtual const char* GetInstanceName(void ) const;

    //Return the context of this application as a FC_Context.
	//##ModelId=3CC4D1D6008F
    virtual FC_Context& GetContext() const;

	//Get the context status region.
	//
	//RETURN T6100_CardActiveRegion&: a reference to the card active region.
	//##ModelId=3DBFFAEA0088
    virtual T6100_CardActiveRegion& GetContextStatusRegion(void) const;

	//Wakeup polling process.
	//##ModelId=3DBFFAEA0114
    virtual bool WakeUpAlm();

	//Suspend polling process.
	//##ModelId=3DBFFAEA0164
    virtual bool SuspendAlm();

	//Get the polling process current state.
    virtual bool GetAlmAppState();

    // Set the application global debug flag
    virtual void SetTraceFlag(bool theDebugFlag);

};

#endif  // __ALM_APP_DECORATOR_H__
