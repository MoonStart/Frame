/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : Telecom Services
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2003/5/20
 DESCRIPTION : Generic class for cascaded first order filters.
--------------------------------------------------------------------------*/

#ifndef TEL_FILTER_H
#define TEL_FILTER_H

class TEL_Filter
{
public:
    /*
    ** theRatio: 0 -> instantaneous response
    **           1 -> frozen
    */
    /* Constructor */ TEL_Filter(int theOrder, float theRatio);
    /* Destructor */  ~TEL_Filter();
    void              Filter(float theValue);
    void              Reset(float theValue);
    float             GetFilteredValue();
    float             GetFilteredValueRate();

private:
    int               myOrder;
    float             myOutput;
    float             myOutputRate;
    float             myRatio1;
    float             myRatio2;
    float *           myFilters;
}; 

#endif // TEL_Filter_H
