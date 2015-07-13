/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, January 07, 2002.
 DESCRIPTION:   Update and keep the PM status.
--------------------------------------------------------------------------*/

#include <PM/PM_BbStatus.h>


//-----------------------------------------------------------------
//##ModelId=3C50163500F6
PM_BbStatus::PM_BbStatus (uint32 theNumberOfParam)
    :myNumberOfParam(theNumberOfParam),
     myParam(NULL),
     myValidity(NULL)
{
    if(myNumberOfParam != 0)
    {
        myParam = new CT_PM_Value[myNumberOfParam];
        myValidity = new bool[myNumberOfParam];

        for (uint32 i = 0; i < myNumberOfParam; i++)
        {
            myParam[i].SignedValue = 0;
            myParam[i].UnsignedValue = 0;
            myValidity[i] = false;
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C5016350100
PM_BbStatus::~PM_BbStatus ()
{
    delete [] myParam;
    delete [] myValidity;

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F150390
void PM_BbStatus::Init(restart_type theRestart)
{
    // Nothing to do for now.

};


//-----------------------------------------------------------------
//##ModelId=3C5016350114
void PM_BbStatus::Update(MON_Object& theMonitor)
{
    FC_THROW_ERROR(FC_SWError, "PM: Update method is not supported by this layer");

}
