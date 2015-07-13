/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         April 10, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for the Generic TL1 Notification multiple 
                observer tag implementation
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MULTIPLEOBSERVERTAG_H__
#define __TL1_MULTIPLEOBSERVERTAG_H__

#include <gdef.h>

#ifndef FC_BBTAG_H
#include <Blackboard/FC_BbTag.h>
#endif

class TL1_DeferredObserverFactoryIf;
class FC_BbRegionObserver;
class FC_BbRegion;
class TL1_WakeUpAction;

#include <map>

using namespace std;

class TL1_MultipleObserverTag : public FC_BbTag
{
public:

    /** The Constructor
     */
    TL1_MultipleObserverTag( FC_BbTagId theId, TL1_DeferredObserverFactoryIf *theObserverFactory );

    /** The Destructor
     *  @Warning The destructor will deallocate the memory allocated 
     *   for the TL1_DeferredObserverFactoryIf ptr.
     */
    virtual ~TL1_MultipleObserverTag();

    //
    // Tag Specific
    // 
    virtual void Install( FC_BbRegion& theRegion );
    virtual void Uninstall( FC_BbRegion& theRegion );

    // Template method to add specific behavior before observer addition to the region
    virtual void DoInstall( FC_BbRegion& theRegion );

    /** This method return the observer, for the given region or 0 if
        there's none
        @param FC_BbRegion*: a pointer to the region for which the observer
        is searched. If "0" this return the tag observer if applicable.
        @return FC_Action*: The observer searched.
     */
    virtual FC_BbRegionObserver* GetObserver( FC_BbRegion* theRegion = 0 );

    /** Determine if the tag is installed on the given region
        @param FC_BbRegion&: the region to test
        @return bool: True if the tag is installed on the region, False otherwise
     */
    virtual bool IsInstalledOn( FC_BbRegion& theRegion );

private:

    struct RegionComp
    {
        bool operator()( FC_BbRegion* theFirst,
                         FC_BbRegion* theSecond ) const
        {
            return theFirst < theSecond;
        }
    };

    typedef map< FC_BbRegion*, TL1_WakeUpAction*, RegionComp > RegionObserverMap;

	/** The list of member regions
     */
    RegionObserverMap itsMemberRegions;

    TL1_DeferredObserverFactoryIf* itsObserverFactory;
};


#endif