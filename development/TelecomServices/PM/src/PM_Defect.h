/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     15 May, 1998 Jean-Francois Birtz.
 DESCRIPTION:   The defect counters and states.
--------------------------------------------------------------------------*/

#ifndef PM_DEFECT_H
#define PM_DEFECT_H

#include <gdef.h>
#include <istream>
#include <ostream>


// Bit use in counter to keep the defect status
#define PM_DEF_BIT      0x80

using namespace std;


//Keeps the defect counters for the current and the last 
//second. Keep also the current state of the defect. This 
//class does not derive from FC_Object nor the class 
//possesses virtual destructor. This is because it is a 
//simple class that from which plenty of objects will be 
//instantiated. The cost in memory to have virtual functions 
//and destructor is too high versus the gain.
//##ModelId=3C1F6F83023A
class PM_Defect
{
public:

    //Class default constructor.
    //##ModelId=3C1F6F8400AB
    PM_Defect ();

    //Class default destructor.
    //##ModelId=3C1F6F8400AC
    virtual ~PM_Defect();

    //Returns the condition of the defect for the current 
    //second.
    //
    //RETURN: true if the defect has at least one transition 
    //from cleared to declared or the state is currently true.
    //##ModelId=3C1F6F8400B5
    bool IsDeclared() const;

    //Updates the counters and the state of the defect. The 
    //last counter value has the current value and the 
    //current counter has the new value. Then the state is 
    //update.
    //##ModelId=3C1F6F8400BF
    void Update(bool theState, uint32 theNewCount);

    //Stores the specified defect to the stream.
    //##ModelId=3C1F6F840105
    friend ostream& operator <<( ostream& theStream, PM_Defect& theDefect );

    //Retrieve the specified defect to the stream.
    //##ModelId=3C1F6F84011A
    friend istream& operator >>( istream& theStream, PM_Defect& theDefect );

private:

    //The current transition counter of the defect. The bits 
    //0 to 6 contain the count and the bit 7 contains the 
    //state of the defect.
    //##ModelId=3C1F6F8400D4
    uint8 myCurrentCount;

    //The last transition counter of the defect. The bits 0 
    //to 6 contain the count and the bit 7 contains always 0.
    //##ModelId=3C1F6F8400E8
    uint8 myLastCount;

};

#endif //PM_DEFECT_H
