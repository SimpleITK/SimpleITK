/*=========================================================================
*
*  Copyright NumFOCUS
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

  template <class TPixelIDType1, class TPixelIDType2 = TPixelIDType1>
  typename std::enable_if< IsInstantiated<TPixelIDType1,VImageDimension>::Value &&
                              IsInstantiated<TPixelIDType2,VImageDimension>::Value >::type
  operator()( TPixelIDType1* t1=nullptr, TPixelIDType2*t2=nullptr ) const
    {
      (void)t1;
      (void)t2;
      using ImageType1 = typename PixelIDToImageType<TPixelIDType1, VImageDimension>::ImageType;
      using ImageType2 = typename PixelIDToImageType<TPixelIDType2, VImageDimension>::ImageType;
      using AddressorType = TAddressor;

      AddressorType addressor;
      m_Factory.Register(addressor.CLANG_TEMPLATE operator()<ImageType1, ImageType2>(), (ImageType1*)(nullptr), (ImageType2*)(nullptr) );

    }

  // this methods is conditionally enabled when the PixelID is not instantiated
  template <class TPixelIDType1, class TPixelIDType2 = TPixelIDType1>
  typename std::enable_if< ! (IsInstantiated<TPixelIDType1,VImageDimension>::Value &&
                              IsInstantiated<TPixelIDType2,VImageDimension>::Value) >::type
  operator()( TPixelIDType1*t1=nullptr, TPixelIDType2*t2=nullptr ) const
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

  // this shouldn't occur, just may be useful for debugging
  assert( pixelID1 >= 0 && pixelID1 < typelist::Length< InstantiatedPixelIDTypeList >::Result );
  assert( pixelID2 >= 0 && pixelID2 < typelist::Length< InstantiatedPixelIDTypeList >::Result );

  static_assert( TImageType1::ImageDimension >= 2 && TImageType1::ImageDimension <= SITK_MAX_DIMENSION,
                    "Image1 Dimension out of range" );
  static_assert( TImageType2::ImageDimension >= 2 && TImageType2::ImageDimension <= SITK_MAX_DIMENSION,
                    "Image2 Dimension out of range" );
  static_assert( int(TImageType1::ImageDimension) == int(TImageType2::ImageDimension),
                    "Image Dimensions do not match" );
  static_assert( IsInstantiated<TImageType1>::Value,
                    "invalid pixel type for argument one");
  static_assert( IsInstantiated<TImageType2>::Value,
                    "invalid pixel type for argument two");

  typename Superclass::KeyType key(TImageType1::GetImageDimension(), pixelID1,
                                   TImageType2::GetImageDimension(), pixelID2);

  Superclass::m_PFunction[ key ] = Superclass::BindObject( pfunc, m_ObjectPointer );

}

template <typename TMemberFunctionPointer>
template < typename TPixelIDTypeList1, typename TPixelIDTypeList2, unsigned int VImageDimension, typename TAddressor >
void
DualMemberFunctionFactory< TMemberFunctionPointer >
::RegisterMemberFunctions( )
{
  using InstantiaterType = DualMemberFunctionInstantiater< Self, VImageDimension, TAddressor >;

  // initialize function array with pointer
  typelist::DualVisit<TPixelIDTypeList1, TPixelIDTypeList2> visitEachComboInLists;
  visitEachComboInLists( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer>
template < typename TPixelIDTypeList, unsigned int VImageDimension, typename TAddressor >
void
DualMemberFunctionFactory< TMemberFunctionPointer >
::RegisterMemberFunctions( )
{

  using InstantiaterType = DualMemberFunctionInstantiater< Self, VImageDimension, TAddressor >;

  // initialize function array with pointer
  typelist::Visit<TPixelIDTypeList> visitEachComboInLists;
  visitEachComboInLists( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer>
bool
DualMemberFunctionFactory< TMemberFunctionPointer >
::HasMemberFunction( PixelIDValueType pixelID1, PixelIDValueType pixelID2, unsigned int imageDimension  ) const noexcept
{
  typename Superclass::KeyType key(imageDimension, pixelID1, imageDimension, pixelID2);
  try
    {
    // check if tr1::function has been set in map
    return Superclass::m_PFunction.find( key ) != Superclass::m_PFunction.end();
    }
  // we do not throw exceptions
  catch(...)
    {
    }
  return false;
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

  typename Superclass::KeyType key(imageDimension, pixelID1, imageDimension, pixelID2);

  // check if tr1::function has been set
  auto ret_pair = Superclass::m_PFunction.find( key ) ;
  if ( ret_pair != Superclass::m_PFunction.end() )
    {
    return ret_pair->second;
    }
  // todo updated exceptions here
  sitkExceptionMacro ( << "Pixel type: "
                       << GetPixelIDValueAsString(pixelID1)
                       << " is not supported in " << imageDimension << "D by"
                       << typeid(ObjectType).name() );

}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  sitkDualMemberFunctionFactory_hxx
