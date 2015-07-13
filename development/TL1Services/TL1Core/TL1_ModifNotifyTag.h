/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 6, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for 7100 Specific TL1 Db Change Notif declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MODIFNOTIFYTAG_H__
#define __TL1_MODIFNOTIFYTAG_H__

#ifndef FC_BBTAG_H
#include <Blackboard/FC_BbTag.h>
#endif

#ifndef __FC_ERROR_H__
#include <ErrorService/FC_Error.h>
#endif

#ifndef __TL1_OBSERVERFACTORYIF_H__
#include <TL1Core/TL1_ObserverFactoryIf.h>
#endif

#ifndef FC_BBREGIONMODIFNOTIFYIMP
#include <Blackboard/FC_BbRegionModifNotifyImp.h>
#endif

#ifndef __TL1_AGENTREGIONOBSERVER_H__
#include <TL1Core/TL1_AgentRegionObserver.h>
#endif

#include <map>

using namespace std;

class FC_BbRegion;

/** This template class is used as a base class for tags that uses
 *  the FC_BbRegionModifObserverImp object.
 */
template <class ObservedRegionType, class ObservedRegionObjectType>
class TL1_ModifNotifyTag : public FC_BbTag
{
public:
    TL1_ModifNotifyTag( FC_BbTagId theId, 
        TL1_ObserverFactoryIf *theObsFactory ) :
        FC_BbTag(theId),
            itsObserverFactory(theObsFactory){}

    /** Destructor.
     * @Warning The destructor will deallocate the memory allocated 
     *  for the TL1_DeferredObserverFactoryIf ptr.
     */
    virtual ~TL1_ModifNotifyTag()
    {
        if( itsObserverFactory )
        {
            delete itsObserverFactory;
            itsObserverFactory = 0;
        }
    };
    
    virtual void Install( FC_BbRegion& theRegion )
    {
        // First make sure the observer has been correctly set
        FC_THROW_ERROR_IF( !itsObserverFactory,
                           FC_RuntimeError,
                           "Attempted to use undefined observer factory" );

        ObservedRegionType* aRegion = dynamic_cast<ObservedRegionType*>(&theRegion);
        FC_THROW_ERROR_IF( !aRegion, FC_RuntimeError,
            "Attempted to install a TL1_ModifNotifyTag on an invalid region type" );

        RegionModifNotifyImp* aModifNotifyRegion = 
            new RegionModifNotifyImp(*aRegion);

        FC_THROW_ERROR_IF( !aModifNotifyRegion,
            FC_RuntimeError,
            "Unable to create FC_BbRegionModifNotifyImp in TL1_ModifNotifyTag" );

        // Check first if region is already member
        typename RegionObserverMap::iterator it = itsMemberRegions.find( &theRegion );

        if ( it == itsMemberRegions.end() )
        {
            // Only add observer if it hasn't been added yet
            itsMemberRegions[&theRegion].first = aModifNotifyRegion;
            itsMemberRegions[&theRegion].second = itsObserverFactory->CreateObserver(theRegion);
            aModifNotifyRegion->AddModifAction( itsMemberRegions[&theRegion].second );
        }

        it = itsMemberRegions.find( &theRegion );
        FC_THROW_ERROR_IF( (it == itsMemberRegions.end()), FC_LogicError, 
            "Failed to register the region in the multiple observer map!" );
    }

    virtual void Uninstall( FC_BbRegion& theRegion )
    {

        typename RegionObserverMap::iterator it = itsMemberRegions.find(&theRegion);
        if ( it != itsMemberRegions.end() )
        {
            RegionModifNotifyImp* aModifNotifyRegion = (*it).second.first;
            TL1_AgentRegionObserver* anObs = (*it).second.second;

            // Deregister the observer from the FC_BbRegionModifNotifyImp instance
            aModifNotifyRegion->RemoveModifAction( anObs );
            // Delete the FC_BbRegionModifNotifyImp instance
            delete aModifNotifyRegion;
            // Delete the observer
            delete anObs;

            itsMemberRegions.erase( it );
        }
    }

    /** This method return the observer, for the given region or 0 if
        there's none
        @param FC_BbRegion*: a pointer to the region for which the observer
        is searched. If "0" this return the tag observer if applicable.
        @return FC_Action*: The observer searched.
     */
    virtual FC_BbRegionObserver* GetObserver( FC_BbRegion* theRegion = 0 )
    {
        typename RegionObserverMap::iterator it = itsMemberRegions.find(theRegion);
        if ( it != itsMemberRegions.end() )
        {
            return (*it).second.second;
        }
        else
        {
            return 0;
        }
    }

    /** Determine if the tag is installed on the given region
        @param FC_BbRegion&: the region to test
        @return bool: True if the tag is installed on the region, False otherwise
     */
    virtual bool IsInstalledOn( FC_BbRegion& theRegion )
    {
        typename RegionObserverMap::iterator it = itsMemberRegions.find( &theRegion );

        return (it != itsMemberRegions.end() )?true:false;
    }

protected:

    typedef FC_BbRegionModifNotifyImp< ObservedRegionType,
                                       ObservedRegionObjectType > 
                RegionModifNotifyImp;
    typedef pair< RegionModifNotifyImp*,
                  TL1_AgentRegionObserver* > RegionObserverPair;

    struct RegionComp
    {
        bool operator()( FC_BbRegion* theFirst,
                         FC_BbRegion* theSecond ) const
        {
            return theFirst < theSecond;
        }
    };

    typedef map< FC_BbRegion*, RegionObserverPair, RegionComp > RegionObserverMap;

private:
    /** The list of member regions
     */
    RegionObserverMap itsMemberRegions;

    TL1_ObserverFactoryIf* itsObserverFactory;
};

#endif
