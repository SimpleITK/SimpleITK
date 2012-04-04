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
#ifndef __sitkTemplateFunctions_h
#define __sitkTemplateFunctions_h

#include "sitkMacro.h"
#include "sitkCommon.h"
#include "sitkExceptionObject.h"

#include <vector>
#include <ostream>

namespace itk {
namespace simple {

/** \brief A function which does nothing
 *
 * This function is to be used to mark parameters as unused to supress
 * compiler warning.
 */
template <typename T>
void SITKCommon_HIDDEN Unused( const T &) {};

/** \brief Print the elements of std::vector to the provided output stream
 *
 * The elements of the std::vector are required to have operator<<
 */
template< typename T >
void SITKCommon_HIDDEN printStdVector( const std::vector< T > & vec, std::ostream & os )
{
  os << "[";
  for(unsigned int cntr = 0; cntr < vec.size()-1; ++cntr)
    {
    os << vec[cntr] << ",";
    }
  os << vec[vec.size()-1] << "]";
}

/** \brief Copy the elements of an std::vector into an ITK fixed width vector
 *
 * If there are more elements in paramter "in" than the templated ITK
 * vector type, they are truncated. If less, then an exception is
 * generated.
 */
template< typename TITKVector, typename TType>
TITKVector SITKCommon_HIDDEN sitkSTLVectorToITK( const std::vector< TType > & in )
{
  typedef TITKVector itkVectorType;
  if ( in.size() < itkVectorType::Dimension )
    {
    sitkExceptionMacro(<<"Unable to convert vector to ITK type\n"
                      << "Expected vector of length " <<  itkVectorType::Dimension
                       << " but only got " << in.size() << " elements." );
    }
  itkVectorType out;
  for( unsigned int i = 0; i < itkVectorType::Dimension; ++i )
    {
    out[i] = in[i];
    }
  return out;
}

/** \brief Convert an ITK fixed width vector to a std::vector
 */
template<typename TType,  typename TITKVector>
std::vector<TType> SITKCommon_HIDDEN sitkITKVectorToSTL( const TITKVector & in )
{
  std::vector<TType> out( TITKVector::Dimension );
  for( unsigned int i = 0; i < TITKVector::Dimension; ++i )
    {
    out[i] = in[i];
    }
  return out;
}

}
}

#endif
