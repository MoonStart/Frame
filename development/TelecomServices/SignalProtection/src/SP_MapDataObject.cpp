// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_MapDataObject.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>


SP_MapDataObject::SP_MapDataObject()
{
}

SP_MapDataObject::~SP_MapDataObject()
{
    myMap.erase(myMap.begin(), myMap.end());
}

bool SP_MapDataObject::Set(uint32 theKey)
{
    if (IsSet(theKey))
    {
        return false;
    }
    else
    {
        myMap[theKey] = true;
        return true;
    }
}
bool SP_MapDataObject::IsSet(uint32 theKey)
{
    SP_Map::const_iterator aIter = myMap.find(theKey);
    if(aIter != myMap.end() &&
      (*aIter).second == true)
    {
        return true;
    }
    return false;
}
bool SP_MapDataObject::Clear(uint32 theKey)
{
    SP_Map::iterator aIter = myMap.find(theKey);
    if(aIter != myMap.end())
    {
        myMap.erase(aIter);
        return true;
    }
    else
    {
        return false;
    }
}

ostream& SP_MapDataObject::WriteObject( ostream& theStream )
{
    SP_Map::iterator iter;

    //Serialize the size of the map
    uint32 aMapSize = myMap.size();
    theStream   << FC_InsertVar(aMapSize);

    //Serialize the map
    for (iter = myMap.begin(); iter != myMap.end(); iter++)
    {
        uint32 aKey = (*iter).first;
        bool  aVal = (*iter).second;

        theStream   << FC_InsertVar(aKey);
        theStream   << FC_InsertVar(aVal);
    }
    return theStream;
}

istream& SP_MapDataObject::ReadObject( istream& theStream )
{
    //Serialize the size of the map
    uint32 aMapSize = 0;
    theStream   >> FC_ExtractVar(aMapSize);

    //Deserialize the map
    myMap.erase(myMap.begin(), myMap.end());
    for (uint8 i=0; i<aMapSize; i++)
    {
        uint32 aKey;
        bool aVal;
        theStream   >> FC_ExtractVar(aKey);
        theStream   >> FC_ExtractVar(aVal);
        myMap[aKey] = aVal;
    }

    return theStream;
}

FC_Stream& SP_MapDataObject::WriteObjectBinary( FC_Stream& theStream )
{
    SP_Map::iterator iter;

    //Serialize the size of the map
    uint32 aMapSize = myMap.size();
    theStream   << aMapSize;

    //Serialize the map
    for (iter = myMap.begin(); iter != myMap.end(); iter++)
    {
        uint32 aKey = (*iter).first;
        bool  aVal = (*iter).second;

        theStream   << aKey;
        theStream   << aVal;
    }
    return theStream;

}

FC_Stream& SP_MapDataObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    //Serialize the size of the map
    uint32 aMapSize = 0;
    theStream   >> aMapSize;

    //Deserialize the map
    myMap.erase(myMap.begin(), myMap.end());

    if (aMapSize != 0)
    {
        for (uint8 i=0; i<aMapSize; i++)
        {
            uint32 aKey;
            bool aVal;
            theStream   >> aKey;
            theStream   >> aVal;
            myMap[aKey] = aVal;
        }
    }

    return theStream;

}

void SP_MapDataObject::GetKeys(vector<uint32>* theKeys)
{
    SP_Map::const_iterator iter;

    for (iter = myMap.begin(); iter != myMap.end(); iter++)
    {
        theKeys->push_back((*iter).first);
    }

}
void SP_MapDataObject::GetValues(vector<uint32>* theValues)
{
    SP_Map::const_iterator iter;

    for (iter = myMap.begin(); iter != myMap.end(); iter++)
    {
        theValues->push_back((*iter).second);
    }
}