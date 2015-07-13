/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Entity base class declaration
-----------------------------------------------------------------------------*/ 

#include <TL1Core/TL1_Entity.h>

#include <Blackboard/FC_BbRegion.h>


TL1_Entity::TL1_Entity() :
    itsAidName("")
{
}

TL1_Entity::~TL1_Entity()
{
}

void TL1_Entity::InstallNotifObservers( AS_Context& theContext )
{;}

void TL1_Entity::UninstallNotifObservers( AS_Context& theContext )
{;}

ostream& TL1_Entity::WriteObject( ostream& theStream )
{
    return theStream;
}

istream& TL1_Entity::ReadObject( istream& theStream )
{
    return theStream;
}

FC_Stream& TL1_Entity::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

FC_Stream& TL1_Entity::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

const string& TL1_Entity::GetEntityName() const
{
    return itsParent->GetBbKey();
}

const string& TL1_Entity::GetAidName() const
{
    // if an aid name has not been set, use the bbKey as the aid name.
    if (itsAidName=="")
        return itsParent->GetBbKey();
    else
        return itsAidName;
}


void TL1_Entity::SetAidName(const string& name)
{
    itsAidName= name;
}


void TL1_Entity::SetParent( FC_BbRegion& theParent )
{
    itsParent = &theParent;
}

void TL1_Entity::AddDirtyRegion(FC_BbRegion* theRegion)
{
    if(theRegion)
    {
        pair< RegionSet::iterator, bool > result =
            itsDirtyRegions.insert( theRegion );
    
        if(result.second)
        {
            theRegion->IncModificationCounter();
        }
    }
}

void TL1_Entity::NotifyDirtyRegions()
{
    RegionSet::iterator it;

    for(it = itsDirtyRegions.begin(); it != itsDirtyRegions.end(); ++it)
    {
        (*it)->UpdateNotify();
    }

    itsDirtyRegions.erase(itsDirtyRegions.begin(), itsDirtyRegions.end());
}
