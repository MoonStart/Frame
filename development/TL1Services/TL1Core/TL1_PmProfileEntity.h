/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 27, 2009- Maggie Zhang
DESCRIPTION:    Header file for TL1 Path PM Profile Entity declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMPROFILEENTITY_H__
#define __TL1_PMPROFILEENTITY_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_TL1_PM_H__
#include <CommonTypes/CT_TL1_Pm.h>
#endif

#ifndef __TL1_PMRSPBLK_H__
#include <Response/TL1_PmRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __CT_PM_DEFINITION_H__
#include <CommonTypes/CT_PM_Definition.h>
#endif

#ifndef __PMA_PROFILE_TABLE_H__
#include <PMA/PMA_ProfileTable.h>
#endif

/**
   CLASS TL1_PmProfileEntity

   This is a logical entity which provides an interface to query and edit
   pm profile.
 */
class TL1_PmProfileEntity : public TL1_Entity
{
public:
    TL1_PmProfileEntity();

    virtual ~TL1_PmProfileEntity();

    virtual void EdPmProfile( const CT_EntityType& theEntityType,
                              const CT_PMProfileTableId& theProfile,
                              CT_TL1_PmArg thePmArg,
                              const string* thePmName,
                              TL1_Response& theResponse ) const = 0;

    virtual void RtrvPmProfile( const CT_EntityType& theEntityType,
                                const CT_PMProfileTableId& theProfile,
                                CT_TL1_PmArg thePmArg,
                                TL1_Response& theResponse ) const = 0;

    /** CLASS AppendPmProfileFunctor
    This functor append a pm response block to a TL1Response
    given an entity, entity address and a pm object
    */
    class AppendPmProfileFunctor : public unary_function< PMA_ProfileTableElem, void >
    {
    public:
        AppendPmProfileFunctor( const CT_EntityType& theEntityType,
                                const CT_PMProfileTableId& theProfile,
                                TL1_Response& theResponse ) :
            itsEntityType( theEntityType ),
            itsProfileId( theProfile ),
            itsResponse( theResponse )
        {}
        
        // fill TL1_PmProfileRspBlk 
        void operator()( const PMA_ProfileTableElem& theProfileElem ) const
        {    
        }
        
    private:
        const CT_EntityType& itsEntityType;
        const CT_PMProfileTableId& itsProfileId;
        TL1_Response& itsResponse;
    };
    
    class TL1_PmProfileFilter : public unary_function< PMA_ProfileTableElem, bool >
    {
    public:
        TL1_PmProfileFilter( const CT_TL1_PmArg& thePmArg):
            itsPmArg(thePmArg)
        {}
        
        bool operator()( const PMA_ProfileTableElem& theProfileElem ) const
        {
            bool result = true;
            
            // Validate MonType, Locn, TmPer in thePmArg
            // Check if they match the value passed in from TL1 request
            // T7100_TL1RtrvThFunc as reference

            return result;
        }
        
    private:
        const CT_TL1_PmArg itsPmArg;
    };
};

#endif
