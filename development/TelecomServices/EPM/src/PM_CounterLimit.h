/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     23 October 2006 Larry M. Wolfrum.
 DESCRIPTION:   The errors counter with a limit.
--------------------------------------------------------------------------*/

#ifndef PM_COUNTERLIMIT_H
#define PM_COUNTERLIMIT_H

#include <gdef.h>
#include <istream>
#include <ostream>


using namespace std;


//Keeps the current and the last second of any free running 
//error counter. This class does not derive from FC_Object 
//nor the class possesses virtual destructor. This is because 
//it is a simple class that from which plenty of objects will 
//be instantiated. The cost in memory to have virtual 
//functions and destructor is too high versus the gain.
// This class also limits the delta reported by the 
// GetCount() method.
class PM_CounterLimit
{

public:

    //Class  constructor.
    PM_CounterLimit ( uint32 theLimit );

    //Class default destructor.
    virtual ~PM_CounterLimit ();

    //This method updates the counter value with the new 
    //counter. The last counter has the current counter value 
    //while the current counter has the new value.
    inline void Update(uint32 theNewCount);

    //Returns the current count (current hardware counter 
    //minus last hardware counter).
    inline uint32 GetCount() const;

    //Resets the current count value.
    inline void ResetCount();
    
    //Stores the specified counter to the stream. This 
    //operator is used to write PM_Counter object content in 
    //a stream.
    friend ostream& operator <<( ostream& theStream, PM_CounterLimit& theCounter );

    //Retrieve the specified counter to the stream. This 
    //operator is used to retrieve the PM_Counter object 
    //content from a stream. 
    friend istream& operator >>( istream& theStream, PM_CounterLimit& theCounter );

protected:

    //The current free running counter value.
    uint32 myCurrentCount;

    //The last second free running counter value.
    uint32 myLastCount;

	//The limit for returning a delta from the GetCount() method.
	uint32 myLimit;

};

//-----------------------------------------------------------------
inline uint32 PM_CounterLimit::GetCount() const
{
	uint32 delta;

	delta = myCurrentCount - myLastCount;

	// Check to see if the delta for this last second is 
	// outrageously large. If so, this is likely due to
	// a uint32 wrap-around. 
	if( delta <= myLimit )
	{
		return delta;
	}
	else
	{
		// Assume this was a uint32 wrap-around and
		// the starting point was zero.
		return myCurrentCount;
	}
}

//-----------------------------------------------------------------
inline void PM_CounterLimit::Update(uint32 theNewCount) 
{
    myLastCount = myCurrentCount;
    myCurrentCount = theNewCount;

}

//-----------------------------------------------------------------
inline void PM_CounterLimit::ResetCount() 
{
    myLastCount = 0;
    myCurrentCount = 0;

}

#endif //PM_COUNTERLIMIT_H

