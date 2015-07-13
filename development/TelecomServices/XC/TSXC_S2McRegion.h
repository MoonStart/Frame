/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Two Multicast Region Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S2MCASTREGION_H
#define _INC_TSXC_S2MCASTREGION_H

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_BaseRegion.h>
#include <XC/TSXC_S2MCast.h>

//------------------------------------------------------------------------------------------------------------------------
//--- This region is used to store multicast configuration on FAB modules 
//
//--- Note:  This region is always created without any objects.
//---        The size of the objects are adjusted when SetMyCardType() method is invoked with appropriate card types.
//------------------------------------------------------------------------------------------------------------------------

template <class T>  class TSXC_S2McRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_S2McRegion(const FC_BbKey theKey) :
                    TSXC_BaseRegion<T>(theKey)
    {
    }

	// Destructor
    virtual ~TSXC_S2McRegion()
    {
    }

    ostream& WriteObject( ostream& theStream );

    // External Interfaces
    bool AddMcGroup(uint16            theMcastId,
                    uint8             theShelfId[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN],
                    uint16            theMembers[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN],
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true,
                    uint8             theNumResponses = 1);

    void DeleteMcGroup(uint16         theMcastId,
                    CT_XC_CQMID*      theRespId = NULL,
                    bool              theImmediateCommit = true,
                    uint8             theNumResponses = 1);

protected:

    virtual void          PopulateSPFAB();
    virtual void          PopulateUFAB();
    virtual void          PopulateMFAB();
};

// ----------------------------------------------------------------------------------------
template<class T> ostream& TSXC_S2McRegion<T>::WriteObject( ostream& theStream )
{
    bool    IsEmpty = true;

    for (int objIndex = 0; objIndex < this->Size(); objIndex++)
    {
        if ( !((*this)[objIndex].IsEmpty()) )
        {
            IsEmpty = false;
            theStream   <<    FC_InsertVar(objIndex); // display the Object Index
            (*this)[objIndex].WriteObject(theStream); // display the Object contents
        }
    }

    if ( IsEmpty )
    {
        fc_cout << endl << "TSXC_S2MCast region is blank!" << endl << endl;
    }
 
    return theStream;
}

// ----------------------------------------------------------------------------------------
template<class T> bool TSXC_S2McRegion<T>::AddMcGroup(uint16            theMcastId,
                                                      uint8             theShelfId[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN],
                                                      uint16            theMembers[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN],
                                                      CT_XC_CQMID*      theRespId,
                                                      bool              theImmediateCommit,
                                                      uint8             theNumResponses)
{
    int               regionIndex;
    bool              retVal = true;
    uint8             shelf;
    TSXC_DESTINATION  mcastDest[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN];

    //--- Clear the eight shelf array for the future use. 
    for(shelf = 0; shelf < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; shelf++)
    {
        mcastDest[shelf].Shelf       = 0;
        mcastDest[shelf].ImuxSlotMap = 0;
    }
                
    // Populate mcast destinations.
    for(shelf = 0; shelf < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; shelf++)
    {
        mcastDest[shelf].Shelf       = theShelfId[shelf];
        mcastDest[shelf].ImuxSlotMap = theMembers[shelf];
    }

    // Calculate index into region for this mcastId.
    regionIndex = theMcastId % TSXC_S2MC_REGION_SIZE;

    // Set Destinations
    (*this)[regionIndex].SetShelfSlots(mcastDest);

    this->SetRespIdAndCommit(theRespId, theImmediateCommit, theNumResponses);

    return retVal;
}

// ----------------------------------------------------------------------------------------
template<class T> void TSXC_S2McRegion<T>::DeleteMcGroup(uint16            theMcastId,
                                                         CT_XC_CQMID*      theRespId,
                                                         bool              theImmediateCommit,
                                                         uint8             theNumResponses)
{
    int    regionIndex;

    // Calculate index into region for this mcastId.
    regionIndex = theMcastId % TSXC_S2MC_REGION_SIZE;

    (*this)[regionIndex].InitMCast();

    this->SetRespIdAndCommit(theRespId, theImmediateCommit, theNumResponses);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_S2McRegion<T>::PopulateSPFAB()
{
    this->Resize(TSXC_S2MC_REGION_SIZE);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_S2McRegion<T>::PopulateUFAB()
{
    this->Resize(TSXC_S2MC_REGION_SIZE);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_S2McRegion<T>::PopulateMFAB()
{
    this->Resize(TSXC_S2MC_REGION_SIZE);

    for (size_t regionIndex = 0; regionIndex < this->Size(); regionIndex++)
    {
        (*this)[regionIndex].InitMCast();
    }
}
#endif // _INC_TSXC_S2MCASTREGION_H
