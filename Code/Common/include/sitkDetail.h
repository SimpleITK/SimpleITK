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
#ifndef sitkDetail_h
#define sitkDetail_h

#include "sitkMemberFunctionFactoryBase.h"
#include "Ancillary/FunctionTraits.h"

namespace itk {
namespace simple {

// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


template < class TMemberFunctionPointer >
struct MemberFunctionAddressor
{
  using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

  template< typename TImageType >
  TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template ExecuteInternal< TImageType >;
    }
};

template < class TMemberFunctionPointer >
struct DualExecuteInternalAddressor
{
  using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

  template< typename TImageType1, typename TImageType2 >
  TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template DualExecuteInternal< TImageType1, TImageType2 >;
    }


  template< typename TImageType>
  TMemberFunctionPointer operator() ( ) const
  {
    return &ObjectType::template DualExecuteInternal< TImageType, TImageType >;
  }
};

/** An addressor of ExecuteInternalCast to be utilized with
 * registering member functions with the factory.
 */
template < class TMemberFunctionPointer >
struct ExecuteInternalVectorImageAddressor
{
  using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

  template< typename TImageType >
  TMemberFunctionPointer operator() ( ) const
  {
    return &ObjectType::template ExecuteInternalVectorImage< TImageType >;
  }
};


/** An addressor of ExecuteInternalCast to be utilized with
 * registering member functions with the factory.
 */
template < class TMemberFunctionPointer >
struct DualExecuteInternalVectorAddressor
{
  using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

  template< typename TImageType1, typename TImageType2 >
  TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template DualExecuteInternalVector< TImageType1, TImageType2 >;
    }
};

/** An addressor of ExecuteInternal to be utilized with
 * registering member functions with the factory.
 */
template < class TMemberFunctionPointer >
struct ExecuteInternalLabelImageAddressor
{
  using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

  template< typename TImageType >
  TMemberFunctionPointer operator() ( ) const
  {
    return &ObjectType::template ExecuteInternalLabelImage< TImageType >;
  }
};


}
}
}
#endif
