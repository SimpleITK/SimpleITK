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
template<typename T> class Versor;

namespace simple {

/** \brief A function which does nothing
 *
 * This function is to be used to mark parameters as unused to suppress
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

  using itkPointVectorType = TITKPointVector;
  itkPointVectorType out;

  unsigned int Dimension = itkPointVectorType::value_type::GetPointDimension();

  for( unsigned int i = 0; i + Dimension <= in.size(); i += Dimension )
    {
    typename itkPointVectorType::value_type pt(&in[i]);
    out.push_back(pt);
    }
  return out;

}

/** \brief Copy the elements of an std::vector into an ITK fixed width vector
 *
 * If there are more elements in parameter "in" than the templated ITK
 * vector type, they are truncated. If less, then an exception is
 * generated.
 */
template< typename TITKVector, typename TType>
TITKVector SITKCommon_HIDDEN sitkSTLVectorToITK( const std::vector< TType > & in )
{
  using itkVectorType = TITKVector;
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

/** \brief Convert an ITK style array of ITK fixed width vector to std::vector
 *
 * An example input type is itk::FixedArray<itk::Point<3>, 3>
 */
template<typename TType,  typename TVectorOfITKVector>
std::vector<TType> SITKCommon_HIDDEN sitkVectorOfITKVectorToSTL( const TVectorOfITKVector & in )
{
  using ITKVectorType = typename TVectorOfITKVector::ValueType;
  std::vector<TType> out;
  out.reserve( in.Size()*ITKVectorType::Dimension );
  for( unsigned int i = 0; i < in.Size(); ++i )
    {
    const std::vector<TType> &temp =  sitkITKVectorToSTL<TType>(in[i]);
    out.insert(out.end(), temp.begin(), temp.end());
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

  if ( direction.empty() )
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


template< typename T, typename TType>
itk::Versor<T> SITKCommon_HIDDEN  sitkSTLVectorToITKVersor( const std::vector< TType > & in )
{
  using itkVectorType = itk::Versor<T>;
  if ( in.size() != 4 )
    {
    sitkExceptionMacro(<<"Unable to convert vector to ITK Versor type\n"
                      << "Expected vector of length " <<  4
                       << " but got " << in.size() << " elements." );
    }
  itkVectorType out;
  out.Set(in[0],in[1],in[2],in[3]);
  return out;
}


template< typename TType, typename T>
std::vector<TType> SITKCommon_HIDDEN  sitkITKVersorToSTL( const itk::Versor<T> & in )
{
  std::vector<TType> out(4);
  out[0] = in.GetX();
  out[1] = in.GetY();
  out[2] = in.GetZ();
  out[3] = in.GetW();
  return out;
}

// Based on p0052r8 : Generic Scope Guard and RAII Wrapper for the
// Standard Library
// by Peter Sommerlad and Andrew L. Sandoval
template <typename F>
struct scope_exit {
  F f_;
  bool run_;
  explicit scope_exit(F f) noexcept : f_(std::move(f)), run_(true) {}
  scope_exit(scope_exit&& rhs) noexcept : f_((rhs.run_ = false, std::move(rhs.f_))), run_(true) {}
  ~scope_exit()
  {
    if (run_)
      f_();
  }

  scope_exit& operator=(scope_exit&& rhs) = delete;
  scope_exit(scope_exit const&) = delete;
  scope_exit& operator=(scope_exit const&) = delete;
};

template <typename F>
scope_exit<F> make_scope_exit(F&& f) noexcept
{
  return scope_exit<F>{ std::forward<F>(f) };
}


}
}

#endif
