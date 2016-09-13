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
#ifndef sitkTemplateFunctions_h
#define sitkTemplateFunctions_h

#include "sitkMacro.h"
#include "sitkCommon.h"
#include "sitkExceptionObject.h"

#include <vector>
#include <ostream>
#include <iterator>

namespace itk {

template<unsigned int VImageDimension> class ImageRegion;

namespace simple {

/** \brief A function which does nothing
 *
 * This function is to be used to mark parameters as unused to supress
 * compiler warning.
 */
template <typename T>
void SITKCommon_HIDDEN Unused( const T &) {};

/**
 * \brief Output the element of an std::vector to the output stream
 *
 * The elements of the std::vector are required to have operator<<.
 *
 * The format of the output should be "[ T, T, T ]".
 */
template <typename T>
SITKCommon_HIDDEN std::ostream & operator<<( std::ostream & os, const std::vector<T>& v)
{
  if ( v.empty() )
    {
    return os << "[ ]";
    }

  os << "[ ";
  std::copy( v.begin(), v.end()-1, std::ostream_iterator<T>(os, ", ") );
  return os << v.back() << " ]";
}

template< typename TITKPointVector, typename TType>
TITKPointVector SITKCommon_HIDDEN sitkSTLVectorToITKPointVector( const std::vector< TType > & in )
{

  typedef TITKPointVector itkPointVectorType;
  itkPointVectorType out;

  unsigned int Dimension = itkPointVectorType::value_type::GetPointDimension();

  for( unsigned int i = 0; i <= in.size()- Dimension; i += Dimension )
    {
    typename itkPointVectorType::value_type pt(&in[i]);
    out.push_back(pt);
    }
  return out;

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
    out[i] = static_cast<TType>(in[i]);
    }
  return out;
}


template<typename TType,  typename TITKVector>
std::vector<TType> SITKCommon_HIDDEN sitkITKVectorToSTL( const std::vector<TITKVector> & in )
{
  std::vector<TType> out;
  out.reserve( in.size()*TITKVector::Dimension );
  typename std::vector<TITKVector>::const_iterator iter = in.begin();
  while(iter!=in.end())
    {
    for( unsigned int i = 0; i < TITKVector::Dimension; ++i )
      {
      out.push_back(static_cast<TType>((*iter)[i]));
      }
    ++iter;
    }

  return out;
}

/** \brief Convert an ITK ImageRegion to and std::vector with the
* first part being the start index followed by the size.
 */
template<unsigned int VImageDimension>
std::vector<unsigned int> SITKCommon_HIDDEN sitkITKImageRegionToSTL( const ImageRegion<VImageDimension> & in )
{
  std::vector<unsigned int> out( VImageDimension*2 );
  for( unsigned int i = 0; i < VImageDimension; ++i )
    {
    out[i] = static_cast<unsigned int>(in.GetIndex(i));
    out[VImageDimension+i] = static_cast<unsigned int>(in.GetSize(i));
    }
  return out;
}


/* \brief Convert to an itk::Matrix type, where the vector is in row
 * major form. If the vector is of 0-size then an identity matrix will
 * be constructed.
 */
template< typename TDirectionType >
TDirectionType SITKCommon_HIDDEN  sitkSTLToITKDirection( const std::vector<double> &direction )
{
  TDirectionType itkDirection;

  if ( direction.size() == 0 )
    {
    itkDirection.SetIdentity();
    }
  else if( direction.size() == TDirectionType::RowDimensions*TDirectionType::ColumnDimensions )
    {
    std::copy( direction.begin(), direction.end(), itkDirection.GetVnlMatrix().begin() );
    }
  else
    {
    sitkExceptionMacro(<<"Length of input ("<<direction.size()<<") does not match matrix dimensions ("
                       <<TDirectionType::RowDimensions<<", "<<TDirectionType::ColumnDimensions<<").\n");
    }
  return itkDirection;
}


template< typename TDirectionType >
std::vector<double> SITKCommon_HIDDEN  sitkITKDirectionToSTL( const TDirectionType & d)
{
  return std::vector<double>(  d.GetVnlMatrix().begin(), d.GetVnlMatrix().end() );
}



}
}

#endif
