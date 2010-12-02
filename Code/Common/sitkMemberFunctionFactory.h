#ifndef __sitkMemberFunctionFactory_h
#define __sitkMemberFunctionFactory_h

#include "sitkMemberFunctionFactoryBase.h"
#include "sitkDetail.h"

namespace itk
{
namespace simple
{
// this namespace is internal classes not part of the external simple ITK interface
namespace detail {

/// \brief A class used to instantiate and generate function object to
/// templated member functions.
///
/// \tparam TMemberFunctionPointer is the type of pointer to member
/// function
/// \tparam TMemberFunctionAddressor is the type of a class who as a
/// templated operator() which returns TMemberFunctionPointer
///
/// Example member function pointer:
/// \code
/// typedef Self& (Self::*MemberFunctionType)( Image::Pointer );
/// \endcode
///
/// The MemberFunctionAddressor will instantiate the templeted member
/// functions by taking their adress. These addresses need to be
/// registered with the RegisterMethods. Later they can be retrieve
/// with the GetMemberFunction methods, which return a function object
/// with the same arguments as the templated member function pointer.
///
/// An instance of a MemberFunctionFactory is bound to a specific
/// instance of an object, so that the returned function object does
/// not need to have the calling object specified.
template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor = detail::MemberFunctionAddressor< TMemberFunctionPointer > >
class MemberFunctionFactory
  : protected MemberFunctionFactoryBase<TMemberFunctionPointer>
{

public:

  typedef MemberFunctionFactoryBase<TMemberFunctionPointer> Superclass;
  typedef MemberFunctionFactory                             Self;

  typedef TMemberFunctionPointer                                           MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType ObjectType;
  typedef TMemberFunctionAddressor                                         AddressorType;
  typedef typename Superclass::FunctionObjectType                          FunctionObjectType;

  /// \brief Constructor which permanently binds the constructed
  /// object to pObject
  MemberFunctionFactory( ObjectType *pObject );

  /// \brief Registers a specific member function.
  ///
  /// Registers a member function templated over TImageType
  template< typename TImageType >
  void Register( MemberFunctionType pfunc,  TImageType*  );

  /// \brief Registers all member functions in TPixelIDTypeList and
  /// simple::InstantiatedPixelIDTypeList over itk::Image<Pixel,
  /// ImageDimension>
  ///
  /// Example usage:
  /// \code
  /// this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  /// this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  /// \endcode
  ///
  template < typename TPixelIDTypeList, unsigned int ImageDimension >
  void RegisterMemberFunctions( void );


  /// \brief Returns a function object for the PixelIndex, and image
  /// dimension.
  ///
  /// imageDataType is the value of Image::GetDataType(), or
  /// typelist::IndexOf< InstantiatedPixelIDTypeList, PixelIDType>::Result
  ///
  /// imageDimension is the the value returned by Image::GetDimension()
  ///
  /// Example usage:
  /// \code
  /// ImageDataType type = image->GetDataType();
  /// unsigned int dimension = image->GetDimension();
  /// return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  /// \endcode
  ///
  /// If the requested member function is not registered then an
  /// exception is generated. The returned function object is
  /// guaranteed to be valid.
  FunctionObjectType GetMemberFunction( ImageDataType imageDataType, unsigned int imageDimension  );

protected:

  ObjectType *m_ObjectPointer;

private:
  Self &operator=(const Self&); // Not Implemented
  MemberFunctionFactory( const Self &); // Not Implemented

};

} // end namespace detail
} // end namespace simple
} // end namespace itk

#include "sitkMemberFunctionFactory.txx"

#endif //  __sitkMemberFunctionFactory_h
