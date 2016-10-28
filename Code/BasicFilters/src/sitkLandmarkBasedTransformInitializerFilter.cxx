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

#include "sitkLandmarkBasedTransformInitializerFilter.h"
#include "itkLandmarkBasedTransformInitializer.h"

// Additional include files
#include "sitkTransform.h"
// Done with additional include files

namespace itk {
namespace simple {

//-----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
LandmarkBasedTransformInitializerFilter::LandmarkBasedTransformInitializerFilter ()
{

    this->m_FixedLandmarks = std::vector<double>();
    this->m_MovingLandmarks = std::vector<double>();
    this->m_LandmarkWeight = std::vector<double>();
    this->m_ReferenceImage = Image();
    this->m_BSplineNumberOfControlPoints = 4u;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
}

//
// Destructor
//
LandmarkBasedTransformInitializerFilter::~LandmarkBasedTransformInitializerFilter ()
{

}



//
// ToString
//
std::string LandmarkBasedTransformInitializerFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::LandmarkBasedTransformInitializerFilter\n";
  out << "  FixedLandmarks: ";
  this->ToStringHelper(out, this->m_FixedLandmarks);
  out << std::endl;
  out << "  MovingLandmarks: ";
  this->ToStringHelper(out, this->m_MovingLandmarks);
  out << std::endl;
  out << "  LandmarkWeight: ";
  this->ToStringHelper(out, this->m_LandmarkWeight);
  out << std::endl;
  // out << "  ReferenceImage: ";
  // this->ToStringHelper(out, this->m_ReferenceImage);
  out << std::endl;
  out << "  BSplineNumberOfControlPoints: ";
  this->ToStringHelper(out, this->m_BSplineNumberOfControlPoints);
  out << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

//
// Execute
//
Transform LandmarkBasedTransformInitializerFilter::Execute ( const Transform & transform, const std::vector<double> & fixedLandmarks, const std::vector<double> & movingLandmarks, const std::vector<double> & landmarkWeight, const Image & referenceImage, unsigned int numberOfControlPoints )
{
  this->SetFixedLandmarks ( fixedLandmarks );
  this->SetMovingLandmarks ( movingLandmarks );
  this->SetLandmarkWeight ( landmarkWeight );
  this->SetReferenceImage ( referenceImage );
  this->SetBSplineNumberOfControlPoints ( numberOfControlPoints );

  return this->Execute ( transform );
}


Transform LandmarkBasedTransformInitializerFilter::Execute ( const Transform & transform )
{
  unsigned int dimension = transform.GetDimension();

  // The dimension of the reference image which the user explicitly
  // set (GetSize()!=[0...0]), and the dimension of the transform do not match
  if ( this->m_ReferenceImage.GetSize() != std::vector<unsigned int>(this->m_ReferenceImage.GetDimension(), 0u) &&
       dimension != this->m_ReferenceImage.GetDimension() )
    {
    sitkExceptionMacro ( "ReferenceImage for LandmarkBasedTransformInitializerFilter does not match dimension of the transform!" );
    }

  return this->m_MemberFactory->GetMemberFunction( sitkFloat32, dimension )( &transform );
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
Transform LandmarkBasedTransformInitializerFilter::ExecuteInternal ( const Transform * inTransform )
{

  // Define the input and output image types
  typedef itk::ImageBase<TImageType::ImageDimension>  InputImageType;
  const unsigned int Dimension = InputImageType::ImageDimension;


  typedef itk::LandmarkBasedTransformInitializer< itk::Transform< double, Dimension, Dimension >, InputImageType, InputImageType> FilterType;
  // Set up the ITK filter
  typename FilterType::Pointer filter = FilterType::New();

  // This initializers modifies the input, we copy the transform to
  // prevent this change
  Transform copyTransform(*inTransform);
  copyTransform.SetFixedParameters(copyTransform.GetFixedParameters());


  const typename FilterType::TransformType *itkTx = dynamic_cast<const typename FilterType::TransformType *>(copyTransform.GetITKBase());

  if ( !itkTx )
    {
    sitkExceptionMacro( "Unexpected error converting transform! Possible miss matching dimensions!" );
    }
  else { filter->SetTransform( const_cast<typename FilterType::TransformType*>(itkTx) ); }



  typedef typename FilterType::LandmarkPointContainer PointContainer;
  PointContainer fixedITKPoints;
  fixedITKPoints = sitkSTLVectorToITKPointVector<PointContainer,double>(m_FixedLandmarks);
  filter->SetFixedLandmarks(fixedITKPoints);

  PointContainer movingITKPoints;
  movingITKPoints = sitkSTLVectorToITKPointVector<PointContainer,double>(m_MovingLandmarks);
  filter->SetMovingLandmarks(movingITKPoints);

  filter->SetLandmarkWeight ( this->m_LandmarkWeight );

  // BSpline specific setup
  if( itkTx->GetTransformCategory() == itkTx->BSpline )
    {
    if ( this->m_ReferenceImage.GetSize() == std::vector<unsigned int>(this->m_ReferenceImage.GetDimension(), 0u) )
      {
      sitkExceptionMacro( "Image not set for BSplineTransform initializer." );
      }
    // Get the pointer to the ITK image contained in image1
    typename InputImageType::ConstPointer referenceImage = this->CastImageToITK<InputImageType>( this->m_ReferenceImage );
    filter->SetReferenceImage ( referenceImage.GetPointer() );
    filter->SetBSplineNumberOfControlPoints ( this->m_BSplineNumberOfControlPoints );
    }

  if (this->GetDebug())
    {
    std::cout << "Executing ITK filter:" << std::endl;
    filter->Print(std::cout);
    }

  filter->InitializeTransform();

  return copyTransform;

}

//-----------------------------------------------------------------------------


//
// Function to run the Execute method of this filter
//
Transform LandmarkBasedTransformInitializer ( const Transform & transform, const std::vector<double> & fixedLandmarks, const std::vector<double> & movingLandmarks, const std::vector<double> & landmarkWeight, const Image & referenceImage, unsigned int numberOfControlPoints )
{
  LandmarkBasedTransformInitializerFilter filter;
  return filter.Execute ( transform, fixedLandmarks, movingLandmarks, landmarkWeight, referenceImage, numberOfControlPoints );
}


} // end namespace simple
} // end namespace itk
