// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_LOCATIONPAIR_38FF467C0013_INCLUDED
#define _INC_SP_LOCATIONPAIR_38FF467C0013_INCLUDED

//This template class contains a local and a remote location 
//(CLSR protection type). Use normally for a relative access 
//of information instead of absolute (east/west).
//##ModelId=38FF467C0013
template<class T>
class SP_LocationPair 
{
public:
	//Remote element.
	//##ModelId=38FF46980294
	T remote;

	//Local element.
	//##ModelId=38FF469C018C
	T local;

	//Default constructor.
	//##ModelId=39170C2D0317
    SP_LocationPair()
    {};

	//Constructor. Takes local and remote initial value.
	//##ModelId=39170C2D0321
    SP_LocationPair(T theLocal, T theRemote):
        remote(theRemote),
        local(theLocal) 
    {};

	//Copy constructor.
	//##ModelId=39170C2D034A
    SP_LocationPair(const SP_LocationPair<T>& thePair):
        local(thePair.local),
        remote(thePair.remote) 
    {};


};

#endif /* _INC_SP_LOCATIONPAIR_38FF467C0013_INCLUDED */

