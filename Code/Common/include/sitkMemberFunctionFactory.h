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
#ifndef sitkMemberFunctionFactory_h
#define sitkMemberFunctionFactory_h

#include "sitkDetail.h"
#include "sitkMemberFunctionFactoryBase.h"
#include "sitkPixelIDValues.h"

namespace itk::simple::detail
{

/** \class MemberFunctionFactory
 * \brief A class used to instantiate and generate function object to
 *  templated member functions.
 *
 *  \tparam TMemberFunctionPointer is the type of pointer to member
 *  function
 *
 *  Example member function pointer:
 *  \code
 *  type alias Self& (Self::*MemberFunctionType)( Image* );
 *  \endcode
 *
 *  The RegisterMemberFunctions instantiate the templated member
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
class MemberFunctionFactory : protected MemberFunctionFactoryBase<TMemberFunctionPointer, std::pair<unsigned int, int>>
{

public:
  using Superclass = MemberFunctionFactoryBase<TMemberFunctionPointer, std::pair<unsigned int, int>>;
  using Self = MemberFunctionFactory;

  using MemberFunctionType = TMemberFunctionPointer;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;
  using FunctionObjectType = typename Superclass::FunctionObjectType;

  constexpr MemberFunctionFactory() = default;

  /** \brief Registers a specific member function.
   *
   * Registers a member function which will be dispatched to the
   * TImageType  type
   */
  template <typename TImageType>
  void
  Register(MemberFunctionType pfunc, TImageType *);

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
   *   using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;
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
   *
   * A range can also be used:
   * \code
   * this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, 3 > ();
   * \endcode
   * @{
   */
  template <typename TPixelIDTypeList, unsigned int VImageDimension, typename TAddressor>
  void
  RegisterMemberFunctions();
  template <typename TPixelIDTypeList, unsigned int VImageDimension>
  void
  RegisterMemberFunctions()
  {
    using AddressorType = detail::MemberFunctionAddressor<TMemberFunctionPointer>;
    this->RegisterMemberFunctions<TPixelIDTypeList, VImageDimension, AddressorType>();
  }

  template <typename TPixelIDTypeList, unsigned int VImageDimension, unsigned int VImageDimensionStop>
  void
  RegisterMemberFunctions()
  {
    using AddressorType = detail::MemberFunctionAddressor<TMemberFunctionPointer>;
    this->RegisterMemberFunctions<TPixelIDTypeList, VImageDimension, VImageDimensionStop, AddressorType>();
  }
  template <typename TPixelIDTypeList,
            unsigned int VImageDimension,
            unsigned int VImageDimensionStop,
            typename TAddressor>
  void
  RegisterMemberFunctions()
  {
    this->RegisterMemberFunctions<TPixelIDTypeList, VImageDimensionStop, TAddressor>();
    if constexpr (VImageDimensionStop > VImageDimension)
    {
      this->RegisterMemberFunctions<TPixelIDTypeList, VImageDimension, VImageDimensionStop - 1, TAddressor>();
    }
  }
  /** @} */

  /** \brief Query to determine if an member function has been
   * registered for pixelID and imageDimension
   */
  bool
  HasMemberFunction(PixelIDValueType pixelID, unsigned int imageDimension) const noexcept;

  /** \brief Returns a function object for the PixelID and image
   *  dimension.
   *
   *  pixelID is the value of Image::GetPixelIDValue(), or
   *  PixelIDToPixelIDValue<PixelIDType>::Result
   *
   *  imageDimension is the value returned by Image::GetDimension()
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
  FunctionObjectType
  GetMemberFunction(PixelIDValueType pixelID, unsigned int imageDimension, ObjectType * objectPointer) const;
};

} // namespace itk::simple::detail

#include "sitkMemberFunctionFactory.hxx"

#endif //  sitkMemberFunctionFactory_h
