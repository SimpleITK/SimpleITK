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

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkNumericTraits.h"
#include "itkNumericTraitsVariableLengthVectorPixel.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkComposeImageFilter.h"

#include "itkVersorRigid3DTransform.h"
#include "sitkCenteredVersorTransformInitializerFilter.h"
#include "itkCenteredVersorTransformInitializer.h"

// Additional include files
#include "sitkTransform.h"
// Done with additional include files

namespace itk {
namespace simple {

//-----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
CenteredVersorTransformInitializerFilter::CenteredVersorTransformInitializerFilter ()
{

  this->m_ComputeRotation = false;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();

}

//
// Destructor
//
CenteredVersorTransformInitializerFilter::~CenteredVersorTransformInitializerFilter ()
{

}


//
// ToString
//
std::string CenteredVersorTransformInitializerFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::CenteredVersorTransformInitializerFilter\n";
  out << "  ComputeRotation: ";
  this->ToStringHelper(out, this->m_ComputeRotation);
  out << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

//
// Execute
//
Transform CenteredVersorTransformInitializerFilter::Execute ( const Image & fixedImage, const Image & movingImage, const Transform & transform,  bool computeRotation )
{
  this->SetComputeRotation ( computeRotation );

  return this->Execute ( fixedImage, movingImage, transform );
}


Transform CenteredVersorTransformInitializerFilter::Execute ( const Image & fixedImage, const Image & movingImage, const Transform & transform )
{
  PixelIDValueEnum type = fixedImage.GetPixelID();
  unsigned int dimension = fixedImage.GetDimension();

  if ( type != movingImage.GetPixelIDValue() || dimension != movingImage.GetDimension() )
    {
    sitkExceptionMacro ( "Moving Image parameter for " << this->GetName() << " doesn't match type or dimension!" );
    }
  if ( dimension != transform.GetDimension() ) { sitkExceptionMacro( "Transform parameter for " << this->GetName() << " doesn't match dimension!" ); }

  return this->m_MemberFactory->GetMemberFunction( type, dimension )( &fixedImage, &movingImage, &transform );
}


//-----------------------------------------------------------------------------

//
// Custom Casts
//
namespace {

}

//-----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Transform CenteredVersorTransformInitializerFilter::ExecuteInternal ( const Image * inFixedImage, const Image * inMovingImage, const Transform * inTransform )
{

  typedef itk::CenteredVersorTransformInitializer< TImageType, TImageType> FilterType;
  // Set up the ITK filter
  typename FilterType::Pointer filter = FilterType::New();


  assert( inFixedImage != NULL );
  filter->SetFixedImage( this->CastImageToITK<typename FilterType::FixedImageType>(*inFixedImage) );
  assert( inMovingImage != NULL );
  typename FilterType::MovingImageType::ConstPointer image2 = this->CastImageToITK<typename FilterType::MovingImageType>( *inMovingImage );
  filter->SetMovingImage( image2 );
  assert( inTransform != NULL );

  // This initializers modifies the input, we copy the transform to
  // prevent this change
  Transform copyTransform(*inTransform);
  copyTransform.SetFixedParameters(copyTransform.GetFixedParameters());

  const typename FilterType::TransformType *itkTx = dynamic_cast<const typename FilterType::TransformType *>(copyTransform.GetITKBase() );
  if ( !itkTx )
    {
    sitkExceptionMacro( "Error converting input transform to required versor transform type.\n" );
    }
  else { filter->SetTransform( const_cast<typename FilterType::TransformType*>(itkTx) ); }


  filter->SetComputeRotation ( this->m_ComputeRotation );

  filter->InitializeTransform();

  return copyTransform;
}

//-----------------------------------------------------------------------------

Transform CenteredVersorTransformInitializer ( const Image & fixedImage, const Image & movingImage, const Transform & transform, bool computeRotation )
{
  CenteredVersorTransformInitializerFilter filter;
  return filter.Execute( fixedImage, movingImage, transform, computeRotation );
}

} // end namespace simple
} // end namespace itk
