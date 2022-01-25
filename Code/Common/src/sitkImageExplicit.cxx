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

#if defined(_MSC_VER) && _MSC_VER == 1700
// VS11 (Visual Studio 2012) has limited variadic argument support for
// std::bind, the following increases the number of supported
// arguments.
// https://connect.microsoft.com/VisualStudio/feedback/details/723448/very-few-function-arguments-for-std-bind

 #if defined(_VARIADIC_MAX) && _VARIADIC_MAX < 10
  #error "_VARIADIC_MAX already defined. Some STL classes may have insufficient number of template parameters."
 #else
  #define _VARIADIC_MAX 10
 #endif
#endif


#include "sitkImage.hxx"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
  namespace simple
  {


  /** A class to explicitly instantiate the Image::InternalInitialization method over the compiled pixel types and the
   * image dimensions.
  **/
  template <typename... Ts>
  struct InternalInitializationInstantiator;
  template <typename... Ts>
  struct InternalInitializationInstantiator<typelist2::typelist<Ts...>>
  {
    InternalInitializationInstantiator(void)
    {
      (void)instantiate_function();
    }
  private:

    static void
    instantiate_function(void)
    {
      instantiate_with_sequence(std::make_integer_sequence<unsigned int, SITK_MAX_DIMENSION + 1 - min_dimension>{});
    }

  private:

    static const unsigned int min_dimension = 2;

    template <typename TImageType>
    static int
    f()
    {
      (void)&Image::InternalInitialization<ImageTypeToPixelIDValue<TImageType>::Result, TImageType::ImageDimension>;
      return 0;
    }

    template <unsigned int D>
    static int
    instantiate_fs(void)
    {
      (void)std::initializer_list<int>{ f<typename PixelIDToImageType<Ts, min_dimension + D>::ImageType>()... };
      return 0;
    }

    template <unsigned int... Ds>
    static void
    instantiate_with_sequence(const std::integer_sequence<unsigned int, Ds...> &)
    {
      (void)std::initializer_list<int>{ instantiate_fs<Ds>()... };
    }
  };

  static const InternalInitializationInstantiator<InstantiatedPixelIDTypeList> instantiator;

  void Image::Allocate ( const std::vector<unsigned int> &_size, PixelIDValueEnum ValueEnum, unsigned int numberOfComponents )
    {
      // initialize member function factory for allocating images

      // The pixel IDs supported
      using PixelIDTypeList = AllPixelIDTypeList;

      typedef void ( Self::*MemberFunctionType )( const std::vector<unsigned int> &, unsigned int );

      using AllocateAddressor = AllocateMemberFunctionAddressor< MemberFunctionType >;

      detail::MemberFunctionFactory< MemberFunctionType > allocateMemberFactory( this );
      allocateMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 2, SITK_MAX_DIMENSION, AllocateAddressor > ();

      if ( ValueEnum == sitkUnknown )
        {
        sitkExceptionMacro( "Unable to construct image of unsupported pixel type" );
        }

      if (_size.size() < 2 || _size.size() > SITK_MAX_DIMENSION)
        {
        sitkExceptionMacro("Unsupported number of dimesions specified by size: " << _size << "!\n"
                           << "The maximum supported Image dimension is " << SITK_MAX_DIMENSION << "." );
        }

      allocateMemberFactory.GetMemberFunction( ValueEnum, _size.size() )( _size, numberOfComponents );
    }
  }
}
