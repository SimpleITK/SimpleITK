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
#ifndef sitkMemberFunctionFactory_hxx
#define sitkMemberFunctionFactory_hxx

#include <cassert>

#include "sitkMemberFunctionFactory.h"
#include "sitkDetail.h"
#include "sitkPixelIDTokens.h"
#include "sitkExceptionObject.h"

namespace itk
{
namespace simple
{
// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


// a privately declared predicate for use with the typelist::ForEach
// algorithm
//
// This predicate calls the provided AddressorType on
// each valid ImageType defined from the pixel type id, and the
// provided dimension
template < typename TMemberFunctionFactory, unsigned int VImageDimension, typename TAddressor >
struct MemberFunctionInstantiater
{
  MemberFunctionInstantiater( TMemberFunctionFactory &factory )
    : m_Factory( factory )
    {}

  template <class TPixelIDType>
  typename std::enable_if< IsInstantiated<TPixelIDType, VImageDimension >::Value >::type
  operator()( TPixelIDType*id=nullptr ) const
    {
      Unused( id );
      using ImageType = typename PixelIDToImageType<TPixelIDType, VImageDimension>::ImageType;
      using AddressorType = TAddressor;

      AddressorType addressor;
      m_Factory.Register(addressor.CLANG_TEMPLATE operator()<ImageType>(), (ImageType*)(nullptr));

    }

  // this methods is conditionally enabled when the PixelID is not instantiated
  template <class TPixelIDType>
  typename std::enable_if< !IsInstantiated<TPixelIDType, VImageDimension>::Value >::type
  operator()( TPixelIDType*id=nullptr ) const
  {
    Unused( id );
  }

private:

  TMemberFunctionFactory &m_Factory;
};

template <typename TMemberFunctionPointer>
MemberFunctionFactory<TMemberFunctionPointer>
::MemberFunctionFactory( typename MemberFunctionFactory::ObjectType *pObject )
  : m_ObjectPointer( pObject )
{
  assert( pObject );
}

template <typename TMemberFunctionPointer>
template<typename TImageType >
void MemberFunctionFactory<TMemberFunctionPointer>
::Register( typename MemberFunctionFactory::MemberFunctionType pfunc,  TImageType*  )
{
  PixelIDValueType pixelID = ImageTypeToPixelIDValue<TImageType>::Result;

  // this shouldn't occur, just may be useful for debugging
  assert( pixelID >= 0 && pixelID < typelist::Length< InstantiatedPixelIDTypeList >::Result );

  static_assert( IsInstantiated<TImageType>::Value,
                    "UnInstantiated ImageType or dimension");
  static_assert( TImageType::ImageDimension <= SITK_MAX_DIMENSION, "Invalid ImageDimensions" );

  auto key = std::pair<unsigned int, int>(TImageType::GetImageDimension(), pixelID);

  Superclass::m_PFunction[key] = Superclass::BindObject( pfunc, m_ObjectPointer );
}

template <typename TMemberFunctionPointer>
template <typename TPixelIDTypeList,
          unsigned int VImageDimension,
          typename TAddressor>
void MemberFunctionFactory<TMemberFunctionPointer>
::RegisterMemberFunctions( )
{
  using InstantiaterType = MemberFunctionInstantiater< MemberFunctionFactory, VImageDimension,TAddressor >;

  // visit each type in the list, and register if instantiated
  typelist::Visit<TPixelIDTypeList> visitEachType;
  visitEachType( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer>
bool
MemberFunctionFactory< TMemberFunctionPointer >
::HasMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  ) const noexcept
{
  auto key = typename Superclass::KeyType( imageDimension, pixelID);
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
typename MemberFunctionFactory<TMemberFunctionPointer>::FunctionObjectType
MemberFunctionFactory<TMemberFunctionPointer>
::GetMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  )
{
  if ( pixelID >= typelist::Length< InstantiatedPixelIDTypeList >::Result || pixelID < 0 )
    {
    sitkExceptionMacro ( << "unexpected error pixelID is out of range " << pixelID << " "  << typeid(ObjectType).name() );
    }

  auto key = typename Superclass::KeyType(imageDimension, pixelID);

  // check if tr1::function has been set
  auto ret_pair = Superclass::m_PFunction.find( key ) ;
  if ( ret_pair != Superclass::m_PFunction.end() )
    {
    return ret_pair->second;
    }

  sitkExceptionMacro ( << "Pixel type: "
                       << GetPixelIDValueAsString(pixelID)
                       << " is not supported in " << imageDimension << "D by "
                       << typeid(ObjectType).name() << "." );
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  sitkMemberFunctionFactory_h
