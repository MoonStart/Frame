/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The PM blackboard region.
--------------------------------------------------------------------------*/

#ifndef PM_REGIONIMP_H
#define PM_REGIONIMP_H

#include "PM_Def.h"
#include "CommonTypes/CT_PM_Definition.h"
#include <TelCommon/TEL_BbRegionBase.h>
#include <BaseClass/FC_TextStream.h>


//Blackboard region template class for TCS Performance 
//Monitoring BB objects. This class can contain any type of 
//PM related BB objects. The Allocate method performs an 
//allocation of the good BB object type. The operator[] 
//returns a reference to the good BB object type.
//
//PARAM OBJECT_TYPE: the type of BB object handled by this 
//region.
//##ModelId=3C1F6F6802E5
template<class OBJECT_TYPE>
class PM_RegionImp:    public TEL_BbRegionBase
{

public:

    //Constructor for this class template.
    //##ModelId=3C1F6F69012F
    PM_RegionImp ( const FC_BbKey& theKey = "unnamed",
                   uint32          theInitialSize = 0,
                   uint32          theNumberOfParam = 0,
                   CT_PM_Period    thePeriod = CT_PM_PERIOD_UNKNOWN) :
        TEL_BbRegionBase(theKey),
        myNumberOfParam(theNumberOfParam),
        myPeriod(thePeriod),
        myTcaPresent(false)
    {
         Resize(theInitialSize);

    }

    //Class default destructor.
    //##ModelId=3C1F6F69014C
    virtual ~PM_RegionImp();

    //Allocates one instance of OBJECT_TYPE class. Returns a 
    //reference to the new object. Passes the number of 
    //parameters to the instance to be constructed. It 
    //returns the pointer to the allocated BB object.
    //##ModelId=3C1F6F69014E
    virtual FC_BbObject* Allocate(bbindex_t theIndex);

    //Deletes object from region.
    //##ModelId=3C1F6F690158
    virtual void Deallocate(FC_BbObject* theObject);

    //Deletes and removes object from region.
    virtual void DeleteElementAt(bbindex_t theIndex);

    //Returns the BB object indexed by theIndex parameter.
    //##ModelId=3C1F6F69016A
    OBJECT_TYPE& operator[] ( int theIndex ) const
    {
        return static_cast<OBJECT_TYPE&> (ElementAt(theIndex));

    }

    // Retrieve TCA present state.
    virtual bool IsTcaPresent();

    // Set TCA present state.
    virtual void SetTcaPresent( bool theTcaState );

    virtual ostream& WriteObject( ostream& theStream );

    virtual istream& ReadObject( istream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    CT_PM_Period GetPeriod() { return myPeriod; }

protected:

    //The number of parameters supported by the object 
    //allocated in this region. It depens of the signal (or 
    //layer) represented by this region. From now one, the 
    //only signal supported are Optical, Regenerator and 
    //Multiplexor Section. They are seen like a single signal.
    //##ModelId=3C1F6F690174
    int myNumberOfParam;

    //The accumulation period type.
    //##ModelId=3C1F6F690193
    CT_PM_Period myPeriod;

private:

    bool myTcaPresent;

};

//-----------------------------------------------------------------
//##ModelId=3C1F6F69014C
template<class OBJECT_TYPE>
inline PM_RegionImp<OBJECT_TYPE>::~PM_RegionImp() 
{
    Resize(0);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F69014E
template<class OBJECT_TYPE>
inline FC_BbObject* PM_RegionImp<OBJECT_TYPE>::Allocate(bbindex_t theIndex)
{
    return new OBJECT_TYPE (myNumberOfParam, myPeriod);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F690158
template<class OBJECT_TYPE>
inline void PM_RegionImp<OBJECT_TYPE>::Deallocate(FC_BbObject* theObject)
{
    delete theObject;

}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline bool PM_RegionImp<OBJECT_TYPE>::IsTcaPresent()
{
    return myTcaPresent;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline void PM_RegionImp<OBJECT_TYPE>::SetTcaPresent( bool theTcaState )
{
    myTcaPresent = theTcaState;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline ostream& PM_RegionImp<OBJECT_TYPE>::WriteObject( ostream& theStream )
{
    TEL_BbRegionBase::WriteObject( theStream );
    theStream << FC_InsertVar(myTcaPresent);

    return theStream;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline istream& PM_RegionImp<OBJECT_TYPE>::ReadObject( istream& theStream ) 
{
    TEL_BbRegionBase::ReadObject( theStream );
    theStream >> FC_ExtractVar(myTcaPresent);

    return theStream;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline FC_Stream& PM_RegionImp<OBJECT_TYPE>::WriteObjectBinary( FC_Stream& theStream ) 
{   
    TEL_BbRegionBase::WriteObjectBinary( theStream );
    theStream << myTcaPresent;

    return theStream;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline FC_Stream& PM_RegionImp<OBJECT_TYPE>::ReadObjectBinary( FC_Stream& theStream ) 
{
    TEL_BbRegionBase::ReadObjectBinary( theStream );
    theStream >> myTcaPresent;

    return theStream;
}

//-----------------------------------------------------------------
template<class OBJECT_TYPE>
inline void PM_RegionImp<OBJECT_TYPE>::DeleteElementAt(bbindex_t theIndex)
{
    FC_BbObject* elementPtr = &((*this)[theIndex]);
    (*this).Deallocate(elementPtr);
    (*this).RemoveAt(theIndex);
}

#endif //PM_REGIONIMP_H

