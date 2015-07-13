/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_COUNTER_H
#define SNMP_COUNTER_H

#include <gdef.h>
#include <SNMP/SNMP_Defs.h>
#include <istream>
#include <ostream>

using namespace std;


//Keeps the current and the last second of any free running 
//counter. This class does not derive from FC_Object 
//nor the class possesses virtual destructor. This is because 
//it is a simple class that from which plenty of objects will 
//be instantiated. 
class SNMP_Counter
{
public:

    //Class default constructor.
    SNMP_Counter ();

    //Class default destructor.
    virtual ~SNMP_Counter ();

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
    //operator is used to write SNMP_Counter object content in 
    //a stream.
    friend ostream& operator <<( ostream& theStream, SNMP_Counter& theCounter );

    //Retrieve the specified counter to the stream. This 
    //operator is used to retrieve the SNMP_Counter object 
    //content from a stream. 
    friend istream& operator >>( istream& theStream, SNMP_Counter& theCounter );

protected:

    //The current free running counter value.
    uint32 myCurrentCount;

    //The last second free running counter value.
    uint32 myLastCount;

};

//-----------------------------------------------------------------
inline uint32 SNMP_Counter::GetCount() const
{
    if (myCurrentCount != 0)
	{
		if (myCurrentCount >= myLastCount) 
		{
			return myCurrentCount - myLastCount;
	    }
	    else
		{
			uint32 myRetValue = myCurrentCount;
			myRetValue += SNMP_MAX_COUNTER32 - myLastCount;
			return myRetValue;
		}
	}
	return myCurrentCount;
}

//-----------------------------------------------------------------
inline void SNMP_Counter::Update(uint32 theNewCount) 
{
    myLastCount = myCurrentCount;
    myCurrentCount = theNewCount;

}

inline void SNMP_Counter::ResetCount() 
{
    myLastCount = 0;
    myCurrentCount = 0;

}

#endif //SNMP_COUNTER_H
