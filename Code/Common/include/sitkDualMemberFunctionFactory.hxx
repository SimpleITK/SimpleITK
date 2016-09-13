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
#ifndef sitkDualMemberFunctionFactory_hxx
#define sitkDualMemberFunctionFactory_hxx

#include "sitkDualMemberFunctionFactory.h"

#include "sitkPixelIDTokens.h"
#include "sitkExceptionObject.h"

namespace itk
{
namespace simple
{
// this namespace is internal classes not part of the external simple ITK interface
namespace detail
{

// a privately declared predicate for use with the typelist::Visit
// algorithm
//
// \todo doc
//
// This predicate calls the member function factories AddressorType on
// each valid ImageType defined from the pixel type id, and the
// provided dimension
template < typename TMemberFunctionFactory, unsigned int VImageDimension, typename TAddressor >
struct DualMemberFunctionInstantiater
{
  DualMemberFunctionInstantiater( TMemberFunctionFactory &factory )
    : m_Factory( factory )
    {}
  template <class TPixelIDType1, class TPixelIDType2>
  typename EnableIf< IsInstantiated<TPixelIDType1,VImageDimension>::Value &&
                     IsInstantiated<TPixelIDType2,VImageDimension>::Value >::Type
  operator()( TPixelIDType1* t1=NULL, TPixelIDType2*t2=NULL ) const
    {
      (void)t1;
      (void)t2;
      typedef typename PixelIDToImageType<TPixelIDType1, VImageDimension>::ImageType ImageType1;
      typedef typename PixelIDToImageType<TPixelIDType2, VImageDimension>::ImageType ImageType2;
      typedef TAddressor                                                             AddressorType;

      AddressorType addressor;
      m_Factory.Register(addressor.CLANG_TEMPLATE operator()<ImageType1, ImageType2>(), (ImageType1*)(NULL), (ImageType2*)(NULL) );

    }

  // this methods is conditionally enabled when the PixelID is not instantiated
  template <class TPixelIDType1, class TPixelIDType2>
  typename DisableIf< IsInstantiated<TPixelIDType1,VImageDimension>::Value &&
                     IsInstantiated<TPixelIDType2,VImageDimension>::Value >::Type
  operator()( TPixelIDType1*t1=NULL, TPixelIDType2*t2=NULL ) const
    {
      (void)t1;
      (void)t2;
    }

private:

  TMemberFunctionFactory &m_Factory;
};

template <typename TMemberFunctionPointer>
DualMemberFunctionFactory< TMemberFunctionPointer >
::DualMemberFunctionFactory( ObjectType *pObject )
  : m_ObjectPointer( pObject )
{
  assert( pObject );
}

template <typename TMemberFunctionPointer>
template< typename TImageType1, typename TImageType2 >
void
DualMemberFunctionFactory< TMemberFunctionPointer >
::Register( MemberFunctionType pfunc,  TImageType1*, TImageType2*  )
{
  PixelIDValueType pixelID1 = ImageTypeToPixelIDValue<TImageType1>::Result;
  PixelIDValueType pixelID2 = ImageTypeToPixelIDValue<TImageType2>::Result;

  // this shouldn't occour, just may be useful for debugging
  assert( pixelID1 >= 0 && pixelID1 < typelist::Length< InstantiatedPixelIDTypeList >::Result );
  assert( pixelID2 >= 0 && pixelID2 < typelist::Length< InstantiatedPixelIDTypeList >::Result );

  sitkStaticAssert( TImageType1::ImageDimension == 2 || TImageType1::ImageDimension == 3,
                    "Image Dimension out of range" );
  sitkStaticAssert( int(TImageType1::ImageDimension) == int(TImageType2::ImageDimension),
                    "Image Dimensions do not match" );
  sitkStaticAssert( IsInstantiated<TImageType1>::Value,
                    "invalid pixel type for argument one");
  sitkStaticAssert( IsInstantiated<TImageType2>::Value,
                    "invalid pixel type for argument two");

  if ( pixelID1 >= 0 && pixelID1 < typelist::Length< InstantiatedPixelIDTypeList >::Result &&
       pixelID2 >= 0 && pixelID2 < typelist::Length< InstantiatedPixelIDTypeList >::Result )
    {
    typename Superclass::KeyType key(pixelID1, pixelID2);

    switch( int(TImageType1::ImageDimension) )
      {
      case 3:
        Superclass::m_PFunction3[ key ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      case 2:
        Superclass::m_PFunction2[ key ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      default:
        break;
      }
    }
}

template <typename TMemberFunctionPointer>
template < typename TPixelIDTypeList1, typename TPixelIDTypeList2, unsigned int VImageDimension, typename TAddressor >
void
DualMemberFunctionFactory< TMemberFunctionPointer >
::RegisterMemberFunctions( void )
{
  typedef DualMemberFunctionInstantiater< Self, VImageDimension, TAddressor > InstantiaterType;

  // initialize function array with pointer
  typelist::DualVisit<TPixelIDTypeList1, TPixelIDTypeList2> visitEachComboInLists;
  visitEachComboInLists( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer>
bool
DualMemberFunctionFactory< TMemberFunctionPointer >
::HasMemberFunction( PixelIDValueType pixelID1, PixelIDValueType pixelID2, unsigned int imageDimension  ) const throw()
{
  try
    {

    typename Superclass::KeyType key(pixelID1, pixelID2);

    switch ( imageDimension )
      {
      case 3:
        // check if tr1::function has been set in map
        return Superclass::m_PFunction3.find( key ) != Superclass::m_PFunction3.end();
      case 2:
        // check if tr1::function has been set in map
        return Superclass::m_PFunction2.find( key ) != Superclass::m_PFunction2.end();
      default:
        return false;
      }
    }
  // we do not throw exceptions
  catch(...)
    {
    return false;
    }
}

template <typename TMemberFunctionPointer>
typename DualMemberFunctionFactory< TMemberFunctionPointer >::FunctionObjectType
DualMemberFunctionFactory< TMemberFunctionPointer >
::GetMemberFunction( PixelIDValueType pixelID1, PixelIDValueType pixelID2, unsigned int imageDimension  )
{
  if ( pixelID1 >= typelist::Length< InstantiatedPixelIDTypeList >::Result || pixelID1 < 0 )
    {
    sitkExceptionMacro ( << "unexpected error pixelID1 is out of range " << pixelID1 << " "  << typeid(ObjectType).name() );
    }

  if ( pixelID2 >= typelist::Length< InstantiatedPixelIDTypeList >::Result || pixelID2 < 0 )
    {
    sitkExceptionMacro ( << "unexpected error pixelID2 is out of range " << pixelID2 << " "  << typeid(ObjectType).name() );
    }

  typename Superclass::KeyType key(pixelID1, pixelID2);

  switch ( imageDimension )
    {
    case 3:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction3.find( key ) != Superclass::m_PFunction3.end() )
        {
        return Superclass::m_PFunction3[ key ];
        }

      // todo updated exceptions here
      sitkExceptionMacro ( << "Pixel type: "
                           << GetPixelIDValueAsString(pixelID1)
                           << " is not supported in 3D by"
                           << typeid(ObjectType).name() );

      break;
    case 2:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction2.find( key ) != Superclass::m_PFunction2.end() )
        {
        return Superclass::m_PFunction2[ key ];
        }

      sitkExceptionMacro ( << "Pixel type: "
                           << GetPixelIDValueAsString(pixelID1)
                           << " is not supported in 2D by"
                           << typeid(ObjectType).name() );

      break;
    default:
      sitkExceptionMacro ( << "Image dimension " << imageDimension << " is not supported" );
    }
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  sitkDualMemberFunctionFactory_hxx
