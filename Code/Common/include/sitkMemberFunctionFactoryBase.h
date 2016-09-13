/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef sitkMemberFunctionFactoryBase_h
#define sitkMemberFunctionFactoryBase_h

#include "sitkConfigure.h"

#include "nsstd/functional.h"

#include "sitkPixelIDTypes.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkMacro.h"
#include "sitkNonCopyable.h"

#include "Ancillary/TypeList.h"
#include "Ancillary/FunctionTraits.h"

#if defined SITK_HAS_UNORDERED_MAP
#include "nsstd/unordered_map.h"
#else
#include <map>
#endif

namespace itk
{
namespace simple
{

// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


#if defined SITK_HAS_UNORDERED_MAP

template <typename T> struct hash : public nsstd::hash<T>{};

/** \brief A specialization of the hash function.
 */
template <>
struct hash< std::pair<int, int> >
  : public std::unary_function<std::pair<int,int>, std::size_t> {
  std::size_t operator()( const std::pair<int, int > &p ) const
    { return nsstd::hash<size_t>()( size_t(p.first) * prime + p.second ); }
private:
  static const std::size_t prime = 16777619u;
};
#endif

template< typename TMemberFunctionPointer,
          typename TKey,
          unsigned int TArity = ::detail::FunctionTraits<TMemberFunctionPointer>::arity>
class MemberFunctionFactoryBase;


/** \class MemberFunctionFactoryBase
 * \brief A base class for the MemberFunctionFactory
 *
 *  This class is for specialization needed for different arity for
 *  the templated member function pointer
 */
template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 0> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef nsstd::function< MemberFunctionResultType ( ) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object.
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc,objectPointer );
    }

  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif

};


/** \class MemberFunctionFactoryBase
 * \brief A base class for the MemberFunctionFactory
 *
 *  This class is for specialization needed for different arity for
 *  the templated member function pointer
 */
template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 1> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgumentType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef nsstd::function< MemberFunctionResultType ( MemberFunctionArgumentType ) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object.
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace nsstd::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc,objectPointer, _1 );
    }


  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif


};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 2> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object
   */
  typedef nsstd::function< MemberFunctionResultType ( MemberFunctionArgument0Type,  MemberFunctionArgument1Type) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace nsstd::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc, objectPointer, _1, _2 );
    }


  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif


};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 3> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type MemberFunctionArgument2Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef nsstd::function< MemberFunctionResultType ( MemberFunctionArgument0Type, MemberFunctionArgument1Type,  MemberFunctionArgument2Type) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace nsstd::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc, objectPointer, _1, _2, _3 );
    }


  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif

};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 4> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type MemberFunctionArgument2Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument3Type MemberFunctionArgument3Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef nsstd::function< MemberFunctionResultType ( MemberFunctionArgument0Type, MemberFunctionArgument1Type, MemberFunctionArgument2Type,  MemberFunctionArgument3Type) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace nsstd::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc, objectPointer, _1, _2, _3, _4 );
    }


  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif

};

template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 5> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type MemberFunctionArgument2Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument3Type MemberFunctionArgument3Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument4Type MemberFunctionArgument4Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void )
#if defined SITK_HAS_UNORDERED_MAP
    :  m_PFunction4( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction3( typelist::Length<InstantiatedPixelIDTypeList>::Result ),
       m_PFunction2( typelist::Length<InstantiatedPixelIDTypeList>::Result )
#endif
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef nsstd::function< MemberFunctionResultType ( MemberFunctionArgument0Type, MemberFunctionArgument1Type, MemberFunctionArgument2Type, MemberFunctionArgument3Type,  MemberFunctionArgument4Type ) > FunctionObjectType;


protected:

  typedef TKey KeyType;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace nsstd::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return nsstd::bind( pfunc, objectPointer, _1, _2, _3, _4, _5 );
    }


  // maps of Keys to pointers to member functions
#if defined SITK_HAS_UNORDERED_MAP
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction4;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction3;
  nsstd::unordered_map< TKey, FunctionObjectType, hash<TKey> > m_PFunction2;
#else
  std::map<TKey, FunctionObjectType> m_PFunction4;
  std::map<TKey, FunctionObjectType> m_PFunction3;
  std::map<TKey, FunctionObjectType> m_PFunction2;
#endif

};

} // end namespace detail
} // end namespace simple
} // end namespace itk

#endif // sitkMemberFunctionFactoryBase_h
