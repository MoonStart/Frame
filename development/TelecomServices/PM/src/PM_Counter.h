/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   The errors counter.
--------------------------------------------------------------------------*/

#ifndef PM_COUNTER_H
#define PM_COUNTER_H

#include <gdef.h>
#include <istream>
#include <ostream>

#include <CommonTypes/CT_PM_Definition.h>

using namespace std;


//Keeps the current and the last second of any free running 
//error counter. This class does not derive from FC_Object 
//nor the class possesses virtual destructor. This is because 
//it is a simple class that from which plenty of objects will 
//be instantiated. The cost in memory to have virtual 
//functions and destructor is too high versus the gain.
//##ModelId=3C1F6F840155
class PM_Counter
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F8403B8
    PM_Counter ();

    //Class default destructor.
    //##ModelId=3C1F6F8403B9
    virtual ~PM_Counter ();

    //This method updates the counter value with the new 
    //counter. The last counter has the current counter value 
    //while the current counter has the new value.
    //##ModelId=3C1F6F8403C2
    inline void Update(CT_PM_64bit_ull theNewCount);

    //Returns the current count (current hardware counter 
    //minus last hardware counter).
    //##ModelId=3C1F6F8403CD
    CT_PM_64bit_ull GetCount() const;

    //Resets the current count value.
    //##ModelId=3C1F6F8403D7
    inline void ResetCount();
    
    //Stores the specified counter to the stream. This 
    //operator is used to write PM_Counter object content in 
    //a stream.
    //##ModelId=3C1F6F85002A
    friend ostream& operator <<( ostream& theStream, PM_Counter& theCounter );

    //Retrieve the specified counter to the stream. This 
    //operator is used to retrieve the PM_Counter object 
    //content from a stream. 
    //##ModelId=3C1F6F85003E
    friend istream& operator >>( istream& theStream, PM_Counter& theCounter );

    void Set64BitPMSupported(bool theValue){ my64BitPMSupported = theValue; }
    bool Get64BitPMSupported(){ return my64BitPMSupported; }

protected:

    //The current free running counter value.
    //##ModelId=3C1F6F850003
    CT_PM_64bit_ull myCurrentCount;

    //The last second free running counter value.
    //##ModelId=3C1F6F850017
    CT_PM_64bit_ull myLastCount;

private: 

    bool my64BitPMSupported;
};

//-----------------------------------------------------------------
//##ModelId=3C1F6F8403C2
inline void PM_Counter::Update(CT_PM_64bit_ull theNewCount) 
{
    myLastCount = myCurrentCount;
    myCurrentCount = theNewCount;

}

//##ModelId=3C1F6F8403D7
inline void PM_Counter::ResetCount() 
{
    myLastCount = 0;
    myCurrentCount = 0;

}

#endif //PM_COUNTER_H
