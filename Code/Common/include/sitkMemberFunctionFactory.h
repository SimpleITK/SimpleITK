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
#ifndef sitkMemberFunctionFactory_h
#define sitkMemberFunctionFactory_h

#include "sitkDetail.h"
#include "sitkMemberFunctionFactoryBase.h"
#include "sitkPixelIDValues.h"

namespace itk
{
namespace simple
{
// this namespace is internal classes not part of the external simple ITK interface
namespace detail {

/** \class MemberFunctionFactory
 * \brief A class used to instantiate and generate function object to
 *  templated member functions.
 *
 *  \tparam TMemberFunctionPointer is the type of pointer to member
 *  function
 *
 *  Example member function pointer:
 *  \code
 *  typedef Self& (Self::*MemberFunctionType)( Image* );
 *  \endcode
 *
 *  The RegisterMemberFunctions instantiate the templeted member
 *  functions and registers the member function pointer, so that it
 *  be used for dispatch later. Later they can be retrieve
 *  with the GetMemberFunction methods, which return a function object
 *  with the same arguments as the templated member function pointer.
 *
 *  An instance of a MemberFunctionFactory is bound to a specific
 *  instance of an object, so that the returned function object does
 *  not need to have the calling object specified.
 */
template <typename TMemberFunctionPointer>
class MemberFunctionFactory
  : protected MemberFunctionFactoryBase<TMemberFunctionPointer, int>
{

public:

  typedef MemberFunctionFactoryBase<TMemberFunctionPointer, int> Superclass;
  typedef MemberFunctionFactory                                  Self;

  typedef TMemberFunctionPointer                                           MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType ObjectType;
  typedef typename Superclass::FunctionObjectType                          FunctionObjectType;

  /** \brief Constructor which permanently binds the constructed
  * object to pObject */
  MemberFunctionFactory( ObjectType *pObject );

  /** \brief Registers a specific member function.
   *
   * Registers a member function which will be dispatched to the
   * TImageType  type
   */
  template< typename TImageType >
  void Register( MemberFunctionType pfunc,  TImageType*  );

  /** \brief Registers all member functions in TPixelIDTypeList and
   * simple::InstantiatedPixelIDTypeList over itk::Image<Pixel,
   * ImageDimension>
   *
   *  \tparam TAddressor is the type of a class who as a
   *  templated operator() which returns TMemberFunctionPointer, this
   *  will default to detail::MemberFunctionAddressor if not specified
   *
   * Example usage:
   * \code
   * template < class TMemberFunctionPointer >
   * struct AllocateAddressor
   * {
   *   typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;
   *
   *   template< typename TImageType >
   *   TMemberFunctionPointer operator() ( void ) const
   *     {
   *       return &ObjectType::template AllocateInternal< TImageType >;
   *     }
   * };
   *
   * this->m_MemberFunctionFactory->RegisterMemberFunctions<PixelIDTypeList,
   *                                                        3,
   *                                                        AllocateAddressor<TMFP> > ();
   * \endcode
   *
   *
   * Example usage:
   * \code
   * this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
   * this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
   * \endcode
   * @{
   */
  template < typename TPixelIDTypeList,
             unsigned int VImageDimension,
             typename TAddressor >
  void RegisterMemberFunctions( void );
  template < typename TPixelIDTypeList, unsigned int VImageDimension >
  void RegisterMemberFunctions( void )
  {
    typedef detail::MemberFunctionAddressor< TMemberFunctionPointer > AddressorType;
    this->RegisterMemberFunctions< TPixelIDTypeList, VImageDimension, AddressorType >();
  }
  /** @} */

  /** \brief Query to determine if an member function has been
    * registered for pixelID and imageDimension
    */
  bool HasMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  ) const throw();

  /** \brief Returns a function object for the PixelIndex, and image
   *  dimension.
   *
   *  pixelID is the value of Image::GetPixelIDValue(), or
   *  PixelIDToPixelIDValue<PixelIDType>::Result
   *
   *  imageDimension is the the value returned by Image::GetDimension()
   *
   *  Example usage:
   *  \code
   *  PixelIDValueType pixelID = image->GetPixelIDValue();
   *  unsigned int dimension = image->GetDimension();
   *  return this->m_MemberFactory->GetMemberFunction( pixelID, dimension )( image );
   *  \endcode
   *
   *  If the requested member function is not registered then an
   *  exception is generated. The returned function object is
   *  guaranteed to be valid.
   */
  FunctionObjectType GetMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  );

protected:

  ObjectType *m_ObjectPointer;

};

} // end namespace detail
} // end namespace simple
} // end namespace itk

#include "sitkMemberFunctionFactory.hxx"

#endif //  sitkMemberFunctionFactory_h
