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
#ifndef sitkMemberFunctionFactory_hxx
#define sitkMemberFunctionFactory_hxx

#include <cassert>

#include "sitkMemberFunctionFactory.h"
#include "sitkDetail.h"
#include "sitkPixelIDTokens.h"
#include "sitkEnableIf.h"
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
  typename EnableIf< IsInstantiated<TPixelIDType, VImageDimension >::Value >::Type
  operator()( TPixelIDType*id=NULL ) const
    {
      Unused( id );
      typedef typename PixelIDToImageType<TPixelIDType, VImageDimension>::ImageType ImageType;
      typedef TAddressor                                                            AddressorType;

      AddressorType addressor;
      m_Factory.Register(addressor.CLANG_TEMPLATE operator()<ImageType>(), (ImageType*)(NULL));

    }

  // this methods is conditionally enabled when the PixelID is not instantiated
  template <class TPixelIDType>
  typename DisableIf< IsInstantiated<TPixelIDType, VImageDimension>::Value >::Type
  operator()( TPixelIDType*id=NULL ) const
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

  // this shouldn't occour, just may be useful for debugging
  assert( pixelID >= 0 && pixelID < typelist::Length< InstantiatedPixelIDTypeList >::Result );

  sitkStaticAssert( IsInstantiated<TImageType>::Value,
                    "UnInstantiated ImageType or dimension");

  if ( pixelID >= 0 && pixelID < typelist::Length< InstantiatedPixelIDTypeList >::Result )
    {
    switch( int(TImageType::ImageDimension) )
      {
      case 4:
        Superclass::m_PFunction4[ pixelID ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      case 3:
        Superclass::m_PFunction3[ pixelID ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      case 2:
        Superclass::m_PFunction2[ pixelID ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      default:
        break;
      }
    }
}

template <typename TMemberFunctionPointer>
template <typename TPixelIDTypeList,
          unsigned int VImageDimension,
          typename TAddressor>
void MemberFunctionFactory<TMemberFunctionPointer>
::RegisterMemberFunctions( void )
{
  typedef MemberFunctionInstantiater< MemberFunctionFactory, VImageDimension,TAddressor > InstantiaterType;

  // visit each type in the list, and register if instantiated
  typelist::Visit<TPixelIDTypeList> visitEachType;
  visitEachType( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer>
bool
MemberFunctionFactory< TMemberFunctionPointer >
::HasMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  ) const throw()
{

  try
    {
    switch ( imageDimension )
      {
      case 4:
        // check if tr1::function has been set in map
        return Superclass::m_PFunction4.find( pixelID ) != Superclass::m_PFunction4.end();
      case 3:
        // check if tr1::function has been set in map
        return Superclass::m_PFunction3.find( pixelID ) != Superclass::m_PFunction3.end();
      case 2:
        // check if tr1::function has been set in map
        return Superclass::m_PFunction2.find( pixelID ) != Superclass::m_PFunction2.end();
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
typename MemberFunctionFactory<TMemberFunctionPointer>::FunctionObjectType
MemberFunctionFactory<TMemberFunctionPointer>
::GetMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  )
{
  if ( pixelID >= typelist::Length< InstantiatedPixelIDTypeList >::Result || pixelID < 0 )
    {
    sitkExceptionMacro ( << "unexpected error pixelID is out of range " << pixelID << " "  << typeid(ObjectType).name() );
    }

  switch ( imageDimension )
    {
    case 4:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction4.find( pixelID ) != Superclass::m_PFunction4.end() )
        {
        return Superclass::m_PFunction4[ pixelID ];
        }

      sitkExceptionMacro ( << "Pixel type: "
                           << GetPixelIDValueAsString(pixelID)
                           << " is not supported in 4D by "
                           << typeid(ObjectType).name()
                           << " or SimpleITK compiled with SimpleITK_4D_IMAGES set to OFF." );
    case 3:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction3.find( pixelID ) != Superclass::m_PFunction3.end() )
        {
        return Superclass::m_PFunction3[ pixelID ];
        }

      sitkExceptionMacro ( << "Pixel type: "
                           << GetPixelIDValueAsString(pixelID)
                           << " is not supported in 3D by"
                           << typeid(ObjectType).name() );

      break;
    case 2:
      // check if tr1::function has been set
      if (  Superclass::m_PFunction2.find( pixelID ) != Superclass::m_PFunction2.end() )
        {
        return Superclass::m_PFunction2[ pixelID ];
        }

        sitkExceptionMacro ( << "Pixel type: "
                             << GetPixelIDValueAsString(pixelID)
                             << " is not supported in 2D by"
                             << typeid(ObjectType).name() );

      break;
    default:
      sitkExceptionMacro ( << "Image dimension " << imageDimension << " is not supported" );
      throw;
    }
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  sitkMemberFunctionFactory_h
