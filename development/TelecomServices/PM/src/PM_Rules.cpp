/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Rule base class. Specify how to update period.
--------------------------------------------------------------------------*/

#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_Rules.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C50162A03AD
PM_Rules::PM_Rules (PM_GenericApplication&  theGenericApplication,
                    uint16                  theIndex,
                    uint32                  theNumberOfParam):
    myGenericApplication(theGenericApplication),
    myIndex(theIndex),
    myNumberOfParam(theNumberOfParam),
    myCurrentValueParam(NULL),
    myValidityState(NULL)
{
    if(myNumberOfParam != 0)
    {
        myCurrentValueParam = new CT_PM_64BitValue[theNumberOfParam];
        myValidityState = new bool[theNumberOfParam];

        Init();
    }
}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3C1F6F6001F5
PM_Rules::~PM_Rules ()
{
    delete [] myCurrentValueParam;
    delete [] myValidityState;
}

//-----------------------------------------------------------------
//##ModelId=3FA161020079
void PM_Rules::Init()
{
    for (uint32 i = 0; i < myNumberOfParam; i++)
    {
        myCurrentValueParam[i].SignedValue = 0;
        myCurrentValueParam[i].UnsignedValue = 0;
        myValidityState[i] = true;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F600200
void PM_Rules::AddAccumulationPeriod(PM_AccumulationPeriod* theAccPeriod)
{
    myVectorOfAccumulationPeriod.push_back(theAccPeriod);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6001FE
void PM_Rules::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage)
{
    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator i;

    // for all Accumulation period
    for( i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++ )
    {
        (*i)->AccumulateParameter(myValidityState, theFilteringStateFirstStage, theFilteringStateSecondStage);
    }

}

//-----------------------------------------------------------------
//##ModelId=3C50162B000B
CT_PM_64BitValue PM_Rules::GetValueParam(uint32 theIndex)
{
    FC_THROW_ERROR_IF(theIndex >= myNumberOfParam, FC_SWError, "");

    return myCurrentValueParam[theIndex];

}

