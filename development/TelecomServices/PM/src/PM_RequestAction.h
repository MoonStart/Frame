/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Action invoked when a request of current or previous
                data was performed on Admin.
--------------------------------------------------------------------------*/

#ifndef PM_GETREQUESTACTION_H
#define PM_GETREQUESTACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_PM_Definition.h>


// Forward declaration of classes.
class PM_BbValue;
class PM_BbRequest;

template <class OBJECT_TYPE> class PM_RegionImp;

//This action registers itself to the requested region given 
//at the construction of the object. The Run method is called 
//when the requested region has changed. It is responsible 
//to updateNotify the requested region (also given at the 
//construction of the object) when the requested region has 
//changed.
//##ModelId=3C1F6F62012E
class PM_RequestAction: public FC_Action
{
public:

    //The class constructor.
    //##ModelId=3C1F6F620324
    PM_RequestAction(PM_RegionImp<PM_BbRequest>& theRequestRegion,
                     PM_RegionImp<PM_BbValue>&   the15MValueCurrentRegion,
                     PM_RegionImp<PM_BbValue>&   theDayValueCurrentRegion,
                     PM_RegionImp<PM_BbValue>&   the15MValuePreviousRegion,
                     PM_RegionImp<PM_BbValue>&   theDayValuePreviousRegion,
                     uint32                      numberOfObject);

    //Destructor of that class.
    //##ModelId=3C1F6F620341
    virtual ~PM_RequestAction();

    //This method Updates Notifies the requested region, if 
    //my Request Id is defferent of the Request Id received in 
    //the requested region.
    //##ModelId=3C1F6F620342
    virtual void Run(FC_Object* theObject = NULL);

private:

    //A reference to the requested region, i.e. the region 
    //for which this action registesr itself using the method 
    //AddModificationAction.
    //##ModelId=3C1F8CB90252
    PM_RegionImp<PM_BbRequest>& myRequestRegion;

    //Reference to the current region for 15 m period; it 
    //includes Values, IDFs and TCAs.
    //##ModelId=3C1F8CBA0100
    PM_RegionImp<PM_BbValue>& my15MCurrentValueRegion;

    //Reference to the current region for the 1 day period; 
    //it includes Values, IDFs and TCAs.
    //##ModelId=3C1F8CBA01E5
    PM_RegionImp<PM_BbValue>& myDayCurrentValueRegion;

    //Reference to the previous region for 15 m period; it 
    //includes Values, IDFs and TCAs.
	//##ModelId=3FA1610F0371
    PM_RegionImp<PM_BbValue>& my15MPreviousValueRegion;

    //Reference to the previous region for the 1 day period; 
    //it includes Values, IDFs and TCAs.
	//##ModelId=3FA161100063
    PM_RegionImp<PM_BbValue>& myDayPreviousValueRegion;

    //The last request id.
    //##ModelId=3C1F6F6502CE
    CT_PM_RequestId myRequestId;

    //The number of object.
    //##ModelId=3E6E4CE500D6
    uint32 myNumberOfObject;

};

#endif // PM_GETREQUESTACTION_H
