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


//
// There is only one templated function in the external interface
// which need to be instantiated, so that the itk::Image and the
// sitk::PimpleImage are completely encapsulated. That is the
// InternalInitialization method. The following uses a macro to
// explicitly instantiate for the expected image types.
//

#define SITK_TEMPLATE_InternalInitialization_D( I, D )                \
  namespace itk { namespace simple {                                    \
  template SITKCommon_EXPORT void \
  Image::InternalInitialization<I,D>(  PixelIDToImageType< typelist::TypeAt<InstantiatedPixelIDTypeList, \
                                       I>::Result,                      \
                                       D>::ImageType *i );              \
  } }

#if SITK_MAX_DIMENSION < 2 || SITK_MAX_DIMENSION > 9
#error "Unsupported SITK_MAX_DIMENSION value".
#endif

#define SITK_TEMPLATE_InternalInitialization_2( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 2 )
#define SITK_TEMPLATE_InternalInitialization_3( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 3 ) SITK_TEMPLATE_InternalInitialization_2( _I )
#define SITK_TEMPLATE_InternalInitialization_4( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 4 ) SITK_TEMPLATE_InternalInitialization_3( _I )
#define SITK_TEMPLATE_InternalInitialization_5( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 5 ) SITK_TEMPLATE_InternalInitialization_4( _I )
#define SITK_TEMPLATE_InternalInitialization_6( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 6 ) SITK_TEMPLATE_InternalInitialization_5( _I )
#define SITK_TEMPLATE_InternalInitialization_7( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 7 ) SITK_TEMPLATE_InternalInitialization_6( _I )
#define SITK_TEMPLATE_InternalInitialization_8( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 8 ) SITK_TEMPLATE_InternalInitialization_7( _I )
#define SITK_TEMPLATE_InternalInitialization_9( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 9 ) SITK_TEMPLATE_InternalInitialization_8( _I )


#define SITK_TEMPLATE_InternalInitialization_CONCAT( I ) sitkMacroJoin( SITK_TEMPLATE_InternalInitialization_, SITK_MAX_DIMENSION ) ( I )

#define SITK_TEMPLATE_InternalInitialization( I ) SITK_TEMPLATE_InternalInitialization_CONCAT ( I )


// Instantiate for all types in the lists
SITK_TEMPLATE_InternalInitialization( 0 );
SITK_TEMPLATE_InternalInitialization( 1 );
SITK_TEMPLATE_InternalInitialization( 2 );
SITK_TEMPLATE_InternalInitialization( 3 );
SITK_TEMPLATE_InternalInitialization( 4 );
SITK_TEMPLATE_InternalInitialization( 5 );
SITK_TEMPLATE_InternalInitialization( 6 );
SITK_TEMPLATE_InternalInitialization( 7 );
SITK_TEMPLATE_InternalInitialization( 8 );
SITK_TEMPLATE_InternalInitialization( 9 );
SITK_TEMPLATE_InternalInitialization( 10 );
SITK_TEMPLATE_InternalInitialization( 11 );
SITK_TEMPLATE_InternalInitialization( 12 );
SITK_TEMPLATE_InternalInitialization( 13 );
SITK_TEMPLATE_InternalInitialization( 14 );
SITK_TEMPLATE_InternalInitialization( 15 );
SITK_TEMPLATE_InternalInitialization( 16 );
SITK_TEMPLATE_InternalInitialization( 17 );
SITK_TEMPLATE_InternalInitialization( 18 );
SITK_TEMPLATE_InternalInitialization( 19 );
SITK_TEMPLATE_InternalInitialization( 20 );
SITK_TEMPLATE_InternalInitialization( 21 );
SITK_TEMPLATE_InternalInitialization( 22 );
SITK_TEMPLATE_InternalInitialization( 23 );
SITK_TEMPLATE_InternalInitialization( 24 );
SITK_TEMPLATE_InternalInitialization( 25 );
SITK_TEMPLATE_InternalInitialization( 26 );
SITK_TEMPLATE_InternalInitialization( 27 );
SITK_TEMPLATE_InternalInitialization( 28 );
SITK_TEMPLATE_InternalInitialization( 29 );


static_assert( typelist::Length<itk::simple::InstantiatedPixelIDTypeList>::Result < 30, "Number of explicitly instantiated pixel types is more then expected!" );
