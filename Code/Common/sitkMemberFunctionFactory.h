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

template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor =
          detail::MemberFunctionAddressor< typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType, TMemberFunctionPointer > >
class MemberFunctionFactory
  : public MemberFunctionFactoryBase<TMemberFunctionPointer>
{

public:
  typedef MemberFunctionFactoryBase<TMemberFunctionPointer>                Superclass;
  typedef TMemberFunctionPointer                                           MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType ObjectType;
  typedef TMemberFunctionAddressor                                         AddressorType;


public:

  MemberFunctionFactory( ObjectType *pObject );

  template< typename TImageType >
  void Register( MemberFunctionType pfunc,  TImageType*  );

  template < typename TPixelTypeList, unsigned int ImageDimension >
  void RegisterMemberFunctions( void );


protected:

  ObjectType *m_ObjectPointer;


};

} // end namespace detail
} // end namespace simple
} // end namespace itk

#include "sitkMemberFunctionFactory.txx"

#endif //  __sitkMemberFunctionFactory_h
