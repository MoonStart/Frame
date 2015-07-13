/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Response Parameter template
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#define __TL1_SMARTPARAMETER_H__

#ifndef __FC_ERROR_H__
#include <ErrorService/FC_Error.h>
#endif

#include <typeinfo>

#define VALIDATE_SMART_PARAM(x) \
    try \
    { \
        (x).GetValue(); \
    } \
    catch ( ... ) \
    { \
        FC_REPORT_ERROR( FC_RuntimeError, ""); \
        throw;  \
    }



template <class ParamType>
class TL1_SmartParameter
{
public:
    TL1_SmartParameter() : itsPresenceFlag(false) {}

    TL1_SmartParameter( const ParamType& theParam ) : 
        itsValue( theParam ),
        itsPresenceFlag( true )
    {
    }

    TL1_SmartParameter( const ParamType* theParam ) :
        itsPresenceFlag( false )
    {
        if ( theParam )
        {
            itsValue = *theParam;
            itsPresenceFlag = true;
        }
    }

    TL1_SmartParameter( const TL1_SmartParameter<ParamType>& theParam ) :
        itsValue( theParam.itsValue ),
        itsPresenceFlag( theParam.itsPresenceFlag )
    {
    }

    TL1_SmartParameter<ParamType>& operator=( const TL1_SmartParameter<ParamType>& theParam )
    {
        itsPresenceFlag = theParam.itsPresenceFlag;

        if (itsPresenceFlag)
            itsValue = theParam.itsValue;

        return *this;
    }

    bool operator==( const TL1_SmartParameter<ParamType>& theParam ) const
    {
        bool isEqual = false;

        // Params are equal when they are both empty or when the content is the 
        // same.
        if ( !itsPresenceFlag && !theParam.itsPresenceFlag )
        {
            isEqual = true;
        }
        else if ( itsPresenceFlag && theParam.itsPresenceFlag &&
                  itsValue == theParam.itsValue )
        {
            isEqual = true;
        }

        return isEqual;
    }

    const ParamType& GetValue() const
    {
        if (!itsPresenceFlag )
        {
            string errStr("Attempted to read an inexistent value, type: ");
            string typeName(typeid(itsValue).name());
            char sizestr[20];
            sprintf(sizestr, ", size: %d", sizeof(ParamType));
            string finalErr = errStr + typeName + sizestr;
            FC_THROW_ERROR( FC_LogicError, finalErr.c_str() );
        }

        return itsValue;
    }

    const ParamType* GetPointer() const
    {
        const ParamType* result = 0;

        if (itsPresenceFlag )
        {
            result = &itsValue;
        }

        return result;
    }

    bool IsPresent() const { return itsPresenceFlag; }

private:
    ParamType itsValue;
    bool itsPresenceFlag;
};

#endif

