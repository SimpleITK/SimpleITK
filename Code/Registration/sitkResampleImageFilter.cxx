#include "sitkResampleImageFilter.h"
#include "itkResampleImageFilter.h"
#include "sitkAffineTransform.h"
#include "sitkLinearInterpolate.h"
#include "sitkTransform.h"
#include "sitkInterpolate.h"
#include "sitkImage.h"
#include "itkImage.h"

namespace itk
{
namespace simple
{

ResampleImageFilter::ResampleImageFilter()
{
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );
  m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3> ();
  m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2> ();

  m_Transform.reset ( new AffineTransform() );
  m_Interpolate.reset ( new LinearInterpolate() );
  Image temp ( 1, 1, 1, sitkUInt8 );
  this->SetResampleParametersFromImage ( temp );
}

std::string ResampleImageFilter::ToString() const {
  itk::simple::Image image(1,1,itk::simple::sitkUInt8);
  ::itk::TransformBase::Pointer transformBase = m_Transform->GetTransform ( image.GetDimension() ).GetPointer();
  ::itk::Object::Pointer interpolatorBase = m_Interpolate->GetInterpolator ( image ).GetPointer();

  std::ostringstream out;
  out << "\n\nTransform:\n";
  transformBase->Print ( out );
  out << "\n\nInterpolator:\n";
  interpolatorBase->Print ( out );
  return out.str();
}

ResampleImageFilter& ResampleImageFilter::SetTransform ( Transform *transform )
{
  m_Transform.reset ( transform->Clone() );
  return *this;
}
ResampleImageFilter& ResampleImageFilter::SetInterpolate ( Interpolate &interpolate )
{
  m_Interpolate.reset ( interpolate.Clone() );
  return *this;
}

ResampleImageFilter& ResampleImageFilter::SetResampleParametersFromImage ( const Image& image )
{
  this->SetResampleOrigin ( image.GetOrigin() );
  this->SetResampleSpacing ( image.GetSpacing() );
  this->SetResampleSize ( image.GetSize() );
  this->SetResampleDirection ( image.GetDirection() );
  return *this;
}
ResampleImageFilter& ResampleImageFilter::SetResampleOrigin ( std::vector<double> origin )
{
m_Origin = origin;
return *this;
}
ResampleImageFilter& ResampleImageFilter::SetResampleDirection ( std::vector<std::vector< double> > direction )
{
m_Direction = direction;
return *this;
}
ResampleImageFilter& ResampleImageFilter::SetResampleSpacing ( std::vector<double> spacing )
{
m_Spacing = spacing;
return *this;
}
ResampleImageFilter& ResampleImageFilter::SetResampleSize ( std::vector<uint32_t> size )
{
m_Size = size;
return *this;
}



template <class TImageType>
Image ResampleImageFilter::ExecuteInternal ( const Image& inImage  )
{
  typedef TImageType InputImageType;
  typedef TImageType OutputImageType;
  typedef itk::ResampleImageFilter<InputImageType, OutputImageType> FilterType;
  typename InputImageType::ConstPointer image =
    dynamic_cast<const InputImageType*> ( inImage.GetImageBase() );

  // Check that ITK image pointer was properly retrieved
  if ( image.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  ::itk::TransformBase::Pointer transformBase = m_Transform->GetTransform ( inImage.GetDimension() ).GetPointer();
  ::itk::Object::Pointer interpolatorBase = m_Interpolate->GetInterpolator ( inImage ).GetPointer();
  if ( NULL == dynamic_cast<typename FilterType::TransformType*> ( transformBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Transform is not a valid type");
    }
  if ( NULL == dynamic_cast<typename FilterType::InterpolatorType*> ( interpolatorBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Interpolator is not a valid type");
    }

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetTransform ( dynamic_cast<typename FilterType::TransformType*> ( transformBase.GetPointer() ) );
  filter->SetInterpolator ( dynamic_cast<typename FilterType::InterpolatorType*> ( interpolatorBase.GetPointer() ) );

  typename FilterType::SpacingType spacing;
  typename FilterType::OriginPointType origin;
  typename FilterType::SizeType size;
  typename FilterType::DirectionType direction;

  for ( uint32_t dim = 0; dim < inImage.GetDimension(); dim++ )
    {
    spacing[dim] = m_Spacing[dim];
    origin[dim] = m_Origin[dim];
    size[dim] = m_Size[dim];
    for ( uint32_t j = 0; j < TImageType::ImageDimension; j++ )
      {
      direction[dim][j] = m_Direction[dim][j];
      }
    }
  filter->SetOutputSpacing ( spacing );
  filter->SetOutputOrigin ( origin );
  filter->SetSize ( size );
  filter->SetOutputDirection ( direction );

  filter->SetInput( image );
  filter->Update();
  return Image ( filter->GetOutput() );
}

  Image ResampleImageFilter::Execute ( const Image &image )
  {
  PixelIDValueType type = image.GetPixelIDValue();
  unsigned int dimension = image.GetDimension();

  return this->m_MemberFactory->GetMemberFunction( type, dimension )( image  );
  }

}
}
