/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     12 Feb 2004  Hemant Thakkar.
 DESCRIPTION:   The failure counters and states.
--------------------------------------------------------------------------*/

#ifndef PM_FAILURE_H
#define PM_FAILURE_H

#include <gdef.h>
#include <istream>
#include <ostream>


// Bit use in counter to keep the failure status
#define PM_FAIL_BIT      0x80

using namespace std;


//Keeps the failure counters. Keep also the 
//current state of the failure. This class does not derive 
//from FC_Object nor the class possesses virtual destructor. 
//This is because it is a simple class that from which plenty 
//of objects will be instantiated. The cost in memory to have 
//virtual functions and destructor is too high versus the gain.
class PM_Failure
{
public:

    //Class default constructor.
    PM_Failure ();

    //Class default destructor.
    virtual ~PM_Failure();

    //Returns the condition of the failure for the current 
    //second.
    //
    //RETURN: true if the failure has at least one transition 
    //from cleared to declared or the state is currently true.
    bool DidTransitionToDeclared() const;

    //Updates the counters and the state of the failure. The 
    //last counter value has the current value and the 
    //current counter has the new value. Then the state is 
    //update.
    void Update(bool theState);

    //Stores the specified failure to the stream.
    friend ostream& operator <<( ostream& theStream, PM_Failure& theFailure );

    //Retrieve the specified failure to the stream.
    friend istream& operator >>( istream& theStream, PM_Failure& theFailure );

private:

    //The current transition counter of the failure. The bits 
    //0 to 6 contain the count and the bit 7 contains the 
    //state of the failure.
    uint8 myCurrentCount;

    //The last transition counter of the failure. The bits 0 
    //to 6 contain the count and the bit 7 contains always 0.
    uint8 myLastCount;

};

#endif //PM_FAILURE_H
