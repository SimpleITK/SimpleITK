#ifndef __sitkMacro_h
#define __sitkMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
#include <stdint.h>
#endif

#include <assert.h>

#include "sitkConfigure.h"

#include "sitkPixelIDTypeLists.h"
#include "sitkPixelIDValues.h"
#include "sitkExceptionObject.h"

#include <vector>

namespace itk {

template< unsigned int D > class Index;
template< unsigned int D > class Size;
namespace simple {

#define printStdVector(vec, os)\
  {\
  os << "[";\
  for(unsigned int cntr = 0; cntr < vec.size()-1; ++cntr)\
    {\
    os << vec[cntr] << ",";\
    }\
  os << vec[vec.size()-1] << "]";\
  }

#define sitkExceptionMacro(x)                                           \
  {                                                                     \
      std::ostringstream message;                                       \
      message << "sitk::ERROR: " x;                                     \
      ::itk::simple::GenericException e_(__FILE__, __LINE__, message.str().c_str(), ITK_LOCATION); \
      throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
    }


template <typename T>
void Unused( const T &) {};

#ifdef SITK_SUPPORTS_STATIC_ASSERT
// utilize the c++0x static_assert if available
#define sitkStaticAssert( expr, str) static_assert( expr, str )
#else

template<bool> struct StaticAssertFailure;
template<> struct StaticAssertFailure<true>{ enum { Value = 1 }; };

#define BOOST_JOIN( X, Y ) BOOST_DO_JOIN( X, Y )
#define BOOST_DO_JOIN( X, Y ) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2( X, Y ) X##Y

#define sitkStaticAssert( expr, str ) enum { BOOST_JOIN( static_assert_typedef, __LINE__) = sizeof( itk::simple::StaticAssertFailure<((expr) == 0 ? false : true )> ) };


#endif


/** \brief Copy the elements of an std::vector into a ITK fixed width vector
 *
 * If there are more elements in paramters in then the templated ITK
 * vector type, they are truncated. If less then an exception is
 * generated.
 */
template<  typename TITKVector, typename TType>
TITKVector sitkSTLVectorToITK( const std::vector< TType > & in )
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
template< unsigned int VDimension, typename TType>
itk::Index<VDimension> sitkSTLVectorToITK( const std::vector< TType > & in )
{
  typedef itk::Index<VDimension> itkVectorType;
  if ( in.size() < VDimension )
    {
    sitkExceptionMacro(<<"Unable to convert vector to ITK type\n"
                      << "Expected vector of length " <<  itkVectorType::Dimension
                       << " but only got " << in.size() << " elements." );
    }
  itkVectorType out;
  for( unsigned int i = 0; i <VDimension; ++i )
    {
    out[i] = in[i];
    }
  return out;
}

template<typename TType,  typename TITKVector>
std::vector<TType> sitkITKVectorToSTL( const TITKVector & in )
{
  std::vector<TType> out( TITKVector::Dimension );
  std::copy( in.Begin(), in.End(), out.begin() );
  return out;
}
template<typename TType,  unsigned int VDimension>
std::vector<TType> sitkITKVectorToSTL( const itk::Size<VDimension> & in )
{
  std::vector<TType> out( VDimension );
  for ( unsigned int i = 0; i < VDimension; ++i )
    {
    out[i] = in[i];
    }
  return out;
}
template<typename TType,  unsigned int VDimension>
std::vector<TType> sitkITKVectorToSTL( const itk::Index<VDimension> & in )
{
  std::vector<TType> out( VDimension );
  for ( unsigned int i = 0; i < VDimension; ++i )
    {
    out[i] = in[i];
    }
  return out;
}

}
}


#endif
