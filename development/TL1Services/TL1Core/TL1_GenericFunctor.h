/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         June 2, 2003- Jean-Francois Tremblay
DESCRIPTION:    Generic Functors Definitions
-----------------------------------------------------------------------------*/ 

#ifndef __TL1_GENERICFUNCTOR_H__
#define __TL1_GENERICFUNCTOR_H__

#include <functional>

using namespace std;

#if defined WIN32 || defined LINUX
template <class _Operation1, class _Operation2, class _Operation3>
class binary_compose
  : public unary_function<typename _Operation2::argument_type,
                          typename _Operation1::result_type> {
protected:
  _Operation1 _M_fn1;
  _Operation2 _M_fn2;
  _Operation3 _M_fn3;
public:
  binary_compose(const _Operation1& __x, const _Operation2& __y, 
                 const _Operation3& __z) 
    : _M_fn1(__x), _M_fn2(__y), _M_fn3(__z) { }
  typename _Operation1::result_type
  operator()(const typename _Operation2::argument_type& __x) const {
    return _M_fn1(_M_fn2(__x), _M_fn3(__x));
  }
};

template <class _Operation1, class _Operation2, class _Operation3>
inline binary_compose<_Operation1, _Operation2, _Operation3> 
compose2(const _Operation1& __fn1, const _Operation2& __fn2, 
         const _Operation3& __fn3)
{
  return binary_compose<_Operation1,_Operation2,_Operation3>
    (__fn1, __fn2, __fn3);
}
#endif


/*-------------------------------------------------------------------------
// Functors declarations
//-----------------------------------------------------------------------*/

template < class Functor, class FilterFunctor >
struct FunctorFilter : public unary_function< typename Functor::argument_type, bool >
{
    FunctorFilter( Functor theFunctor, FilterFunctor theFilter ) :
        itsFunctor( theFunctor ),
        itsFilter( theFilter )
    {}

    bool operator()( const typename Functor::argument_type& theParam ) const
    {
        bool succeed = false;

        if ( itsFilter( theParam ) )
        {
            itsFunctor( theParam );
            succeed = true;
        }
        return succeed;
    }
    Functor itsFunctor;
    FilterFunctor itsFilter;
};

template < class Functor, class FilterFunctor >
FunctorFilter< Functor, FilterFunctor > EvaluateConditional( Functor theFunctor,
                                                             FilterFunctor theFilter )
{
    return FunctorFilter< Functor, FilterFunctor >( theFunctor, theFilter );
}
                                                         
/** Class TypeAdaptor
    This is a functor decorator as well as a type adaptor. If it succeed
    in adapting the parameter passed to the targeted type it calls the
    decorated functor.
    It takes two parameters.
    BaseType: the type that will be received and must adapted from
    Functor: the type of the functor to call.

  Comment:
    DerivedType: the target type, the type that must be successully adapted
                 for the decorated functor to be called. It is deduced
                 from the decorated functor

*/
template < class BaseType, class Functor >
struct TypeAdaptor : public unary_function< BaseType, bool >
{
    typedef typename Functor::argument_type FnArgument;
    TypeAdaptor( Functor theFunctor ) : itsFunctor( theFunctor ) {}

    bool operator()( const BaseType& theObject ) const
    {
        bool succeed = false;

        const FnArgument* derivedObject =
            dynamic_cast<const FnArgument*>(&theObject) ;
        if ( derivedObject )
        {
            itsFunctor( *derivedObject );
            succeed = true;
        }
        return succeed;
    }
    Functor itsFunctor;
};

#ifdef WIN32
template < class SourceFunctorProto, class Functor > 
TypeAdaptor< typename SourceFunctorProto::argument_type, Functor >
AdaptFunctorType( SourceFunctorProto baseProto, Functor theFunctor )
{
    return TypeAdaptor< SourceFunctorProto::argument_type, Functor >( theFunctor );
}
#else
// pSOS doesn't fully support typename...
template < class SourceFunctorProto, class Functor > 
TypeAdaptor< typename SourceFunctorProto::argument_type, Functor >
AdaptFunctorType( SourceFunctorProto baseProto, Functor theFunctor )
{
    return TypeAdaptor< typename SourceFunctorProto::argument_type, Functor >( theFunctor );
}
#endif


#endif
