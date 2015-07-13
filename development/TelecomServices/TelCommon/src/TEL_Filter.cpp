/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : Telecom Services
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2003/5/20
 DESCRIPTION : Generic class for cascaded first order filters.
--------------------------------------------------------------------------*/

#include "TelCommon/TEL_Filter.h"
#include <math.h>

TEL_Filter::TEL_Filter(int theOrder, float theRatio) :
    myOrder(theOrder),
    myRatio1(theRatio),
    myRatio2(1.0f - theRatio),
    myOutput(0.0f),
    myOutputRate(0.0f),
    myFilters(new float[theOrder])
{
    Reset(0.0f);
}

TEL_Filter::~TEL_Filter()
{
    delete [] myFilters;
}

void TEL_Filter::Filter(float theValue)
{
    int i;

    myFilters[0] = myFilters[0]*myRatio1 + theValue*myRatio2;
    for (i = 1; i < myOrder; i++) myFilters[i] = myFilters[i]*myRatio1 + myFilters[i - 1]*myRatio2;
    myOutputRate = myFilters[myOrder - 1] - myOutput;
    myOutput     = myFilters[myOrder - 1];
}

void TEL_Filter::Reset(float theValue)
{
    int   i;

    for (i = 0; i < myOrder; i++) myFilters[i] = theValue;
    myOutput     = theValue;
    myOutputRate = 0.0f;
}

float TEL_Filter::GetFilteredValue()
{
    return myOutput;
}

float TEL_Filter::GetFilteredValueRate()
{
    return myOutputRate;
}
