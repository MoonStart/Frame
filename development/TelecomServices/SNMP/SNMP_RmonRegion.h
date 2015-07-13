/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:
TARGET:
AUTHOR:
DESCRIPTION:
-----------------------------------------------------------------------------*/

#ifndef SNMP_RMONREGION_H
#define SNMP_RMONREGION_H

#include <SNMP/SNMP_Region.h>
#include <SNMP/SNMP_RmonEtherStatsData.h>
#include <SNMP/SNMP_RmonEtherHistData.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ErrorService/FC_Error.h>

class SNMP_BbRmonEtherHistRequest;
class SNMP_BbRmonEtherStatsRequest;
class SNMP_BbRmonEtherHistCfg;
class SNMP_BbRmonEtherStatsCfg;
class SNMP_BbRmonEtherCount;

template <class T>
class SNMP_RmonDataRegion : public SNMP_BbRegion<T>
{
public:
    SNMP_RmonDataRegion(const FC_BbKey theKey,
                        size_t numberOfElement) :
        SNMP_BbRegion<T>(theKey,numberOfElement) { }

    ~SNMP_RmonDataRegion() { }

    T& GetEntry(CT_SNMP_Integer32 theIndex,
                bool theCreateNewFlag = false) throw (FC_RuntimeError);
    T& GetFirstEntry();
    T& GetNextEntry() throw (FC_RuntimeError);
    bool DoesEntryExist(CT_SNMP_Integer32 theIndex);
    T& GetUnusedEntry() throw (FC_RuntimeError);
    T& CreateNewEntry(CT_SNMP_Integer32 theIndex) throw (FC_RuntimeError);
    void DeleteEntry(CT_SNMP_Integer32 theIndex);
    bool DoesUnusedEntryExist();
};

template <class T>
inline T& SNMP_RmonDataRegion<T>::GetEntry(CT_SNMP_Integer32 theIndex,
                                           bool theCreateNewFlag) throw (FC_RuntimeError)
{
    unsigned int index;
    T* theObjPtr;
    for (index = 0; index < this->Size(); index++)
    {
        theObjPtr = &((*this)[index]);
        if (theObjPtr->GetIndex() == theIndex)
        {
            break;
        }
    }
    if (index == this->Size())
    {
        if (theCreateNewFlag)
        {
            try
            {
                theObjPtr = &(CreateNewEntry(theIndex));
            }
            catch (FC_RuntimeError)
            {
                throw;
            }
        }
        else
        {
            FC_THROW_ERROR(FC_RuntimeError, "RMON data not found");
        }
    }
    return *theObjPtr;
}

#ifndef LINUX
//
// g++ 3.4.5 tries to bind myCurrEntryPtr at compile time
// causing a fatal error with these two templates.
// myCurrEntryPtr is not defined anywhere, so I
// assume these are not used (arossett 10/30/06)
//
template <class T>
inline T& SNMP_RmonDataRegion<T>::GetFirstEntry()
{
    this->myCurrEntryPtr = 0;
    myCurrEntryPtr = 0;

    return ((*this)[myCurrEntryPtr++]);
}

template <class T>
inline T& SNMP_RmonDataRegion<T>::GetNextEntry() throw (FC_RuntimeError)
{
    T* theObjPtr;

    if (myCurrEntryPtr == this->Size())

    {
        FC_THROW_ERROR(FC_RuntimeError, "End of RMON table");
    }
    else
    {
        theObjPtr = &((*this)[myCurrEntryPtr++]);
    }
    return *theObjPtr;
}

#endif

template <class T>
bool SNMP_RmonDataRegion<T>::DoesEntryExist(CT_SNMP_Integer32 theIndex)
{
    bool retCode = false;
    unsigned int index;
    T* theObjPtr;
    for (index = 0; index < this->Size(); index++)
    {
        theObjPtr = &((*this)[index]);
        if (theObjPtr->GetIndex() == theIndex)
        {
            retCode = true;
            break;
        }
    }
    return retCode;
}

template <class T>
inline T& SNMP_RmonDataRegion<T>::GetUnusedEntry() throw (FC_RuntimeError)
{
    unsigned int index;
    T* theObjPtr;
    for (index = 0; index < this->Size(); index++)
    {
        theObjPtr = &((*this)[index]);
        SNMP_BbRmonData* theBasePtr = static_cast<SNMP_BbRmonData *> (theObjPtr);
        if (!(theBasePtr->IsCollectionEnabled()))
        {
            break;
        }
    }
    if (index == this->Size())
    {
        FC_THROW_ERROR(FC_RuntimeError, "No unused RMON entry found");
    }
    return *theObjPtr;
}

template <class T>
inline T& SNMP_RmonDataRegion<T>::CreateNewEntry(CT_SNMP_Integer32 theIndex)
    throw (FC_RuntimeError)
{
    try
    {
        T& theObj = GetUnusedEntry();
        theObj.ResetAll();
        return theObj;
    }
    catch (FC_RuntimeError)
    {
        // Stats entry table full
        throw;
    }
}

template <class T>
inline void SNMP_RmonDataRegion<T>::DeleteEntry(CT_SNMP_Integer32 theIndex)
{
    try
    {
        T& theObj = GetEntry(theIndex);
        theObj.ResetAll();
    }
    catch (FC_RuntimeError)
    {
        // Didnot find the entry
        cout << "Attempt to delete non-existing RMON entry" << endl;
    }
}

template <class T>
bool SNMP_RmonDataRegion<T>::DoesUnusedEntryExist()
{
    bool retCode = false;
    unsigned int index;
    T* theObjPtr;
    for (index = 0; index < this->Size(); index++)
    {
        theObjPtr = &((*this)[index]);
        SNMP_BbRmonData* theBasePtr = static_cast<SNMP_BbRmonData *> (theObjPtr);
        if (theBasePtr->IsCollectionEnabled() == false)
        {
            retCode = true;
            break;
        }
    }
    return retCode;
}

typedef SNMP_RmonDataRegion<SNMP_BbRmonEtherHistStorage>    SNMP_RmonEtherHistStorageRegion;
typedef SNMP_RmonDataRegion<SNMP_BbRmonEtherHistData>       SNMP_RmonEtherHistDataRegion;
typedef SNMP_BbRegion<SNMP_BbRmonEtherHistRequest>          SNMP_RmonEtherHistReqRegion;
typedef SNMP_BbRegion<SNMP_BbRmonEtherHistCfg>              SNMP_RmonEtherHistCfgRegion;

typedef SNMP_BbRegion<SNMP_BbRmonEtherCount>                SNMP_RmonEtherCountRegion;


typedef SNMP_RmonDataRegion<SNMP_BbRmonEtherStatsData>      SNMP_RmonEtherStatsDataRegion;
typedef SNMP_BbRegion<SNMP_BbRmonEtherStatsRequest>         SNMP_RmonEtherStatsReqRegion;
typedef SNMP_BbRegion<SNMP_BbRmonEtherStatsCfg>             SNMP_RmonEtherStatsCfgRegion;

#endif // SNMP_BB_REGION_H
