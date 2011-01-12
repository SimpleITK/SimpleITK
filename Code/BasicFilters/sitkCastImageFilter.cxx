#include "sitkCastImageFilter.h"

#include <itkCastImageFilter.h>
#include <itkImageToVectorImageFilter.h>
#include <itkLabelImageToLabelMapFilter.h>

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
CastImageFilter::CastImageFilter ()
  {
    this->m_OutputPixelType = sitkFloat32;


  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

//
// ToString
//
std::string CastImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::CastImageFilter\n"
      << "\tOutputPixelType: " << this->m_OutputPixelType << " "
      << GetPixelIDValueAsString( this->m_OutputPixelType ) << "\n";
  return out.str();
  }


//
// Execute
//
Image::Pointer CastImageFilter::Execute ( Image::Pointer image )
  {

    PixelIDValueType type = image->GetPixelIDValue();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image::Pointer CastImageFilter::ExecuteInternal ( Image::Pointer inImage )
  {
  typedef TImageType InputImageType;


  typename InputImageType::ConstPointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  if ( this->m_OutputPixelType == sitkUnknown )
    {
    sitkExceptionMacro( "Unable to convert to unknown pixel type." );
    return NULL;
    }
  else if ( this->m_OutputPixelType == sitkUInt8 )
    {
    typedef itk::Image< uint8_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkInt16 )
    {
    typedef itk::Image< int16_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkInt32 )
    {
    typedef itk::Image< int32_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkFloat32 )
    {
    typedef itk::Image< float, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkInt8 )
    {
    typedef itk::Image< int8_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkUInt16 )
    {
    typedef itk::Image< uint16_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkUInt32 )
    {
    typedef itk::Image< uint32_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkUInt64 )
    {
    typedef itk::Image< uint64_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkInt64 )
    {
    typedef itk::Image< int64_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkFloat64 )
    {
    typedef itk::Image< double, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkComplexFloat32 )
    {
    typedef itk::Image< std::complex< float >, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkComplexFloat64 )
    {
    typedef itk::Image< std::complex< double >, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToBasic< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorUInt8 )
    {
    typedef itk::VectorImage< uint8_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorInt8 )
    {
    typedef itk::VectorImage< int8_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorUInt16 )
    {
    typedef itk::VectorImage< uint16_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorInt16 )
    {
    typedef itk::VectorImage< int16_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorUInt32 )
    {
    typedef itk::VectorImage< uint32_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorInt32 )
    {
    typedef itk::VectorImage< int32_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorUInt64 )
    {
    typedef itk::VectorImage< uint64_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorInt64 )
    {
    typedef itk::VectorImage< int64_t, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorFloat32 )
    {
    typedef itk::VectorImage< float, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else if ( this->m_OutputPixelType == sitkVectorFloat64 )
    {
    typedef itk::VectorImage< double, InputImageType::ImageDimension > OutputImageType;
    return this->ExecuteInternalToVector< InputImageType,  OutputImageType >( image.GetPointer() );
    }
 else if ( this->m_OutputPixelType == sitkLabelUInt8 )
    {
    typedef itk::LabelMap< itk::LabelObject< uint8_t, InputImageType::ImageDimension > > OutputImageType;
    return this->ExecuteInternalToLabel< InputImageType,  OutputImageType >( image.GetPointer() );
    }
 else if ( this->m_OutputPixelType == sitkLabelUInt16 )
    {
    typedef itk::LabelMap< itk::LabelObject< uint16_t, InputImageType::ImageDimension > > OutputImageType;
    return this->ExecuteInternalToLabel< InputImageType,  OutputImageType >( image.GetPointer() );
    }
 else if ( this->m_OutputPixelType == sitkLabelUInt32 )
    {
    typedef itk::LabelMap< itk::LabelObject< uint32_t, InputImageType::ImageDimension > > OutputImageType;
    return this->ExecuteInternalToLabel< InputImageType,  OutputImageType >( image.GetPointer() );
    }
 else if ( this->m_OutputPixelType == sitkLabelUInt64 )
    {
    typedef itk::LabelMap< itk::LabelObject< uint64_t, InputImageType::ImageDimension > > OutputImageType;
    return this->ExecuteInternalToLabel< InputImageType,  OutputImageType >( image.GetPointer() );
    }
  else
    {
    sitkExceptionMacro( "Logic Error missing case" )
    }

  }


template<typename TImageType, typename TOutputImageType>
typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
CastImageFilter::ExecuteInternalToBasic(const TImageType* inImage )
 {
   typedef TImageType       InputImageType;
   typedef TOutputImageType OutputImageType;

   typedef itk::CastImageFilter<InputImageType, OutputImageType> FilterType;
   typename FilterType::Pointer filter = FilterType::New();

   filter->SetInput ( inImage );
   filter->Update();

   Image::Pointer out = new Image( filter->GetOutput() );

   return out;
 }



template<typename TImageType, typename TOutputImageType>
typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
CastImageFilter::ExecuteInternalToVector( const TImageType* inImage )
{

   typedef TImageType       InputImageType;
   typedef TOutputImageType OutputImageType;

   typedef itk::ImageToVectorImageFilter<InputImageType> FilterType;
   typename FilterType::Pointer filter = FilterType::New();
   filter->SetInput ( inImage );

   typedef itk::CastImageFilter< typename FilterType::OutputImageType, OutputImageType > CastFilterType;
   typename CastFilterType::Pointer caster = CastFilterType::New();
   caster->SetInput( filter->GetOutput() );
   caster->InPlaceOn();
   caster->Update();

   Image::Pointer out = new Image( caster->GetOutput() );

   return out;
}


template<typename TImageType, typename TOutputImageType>
typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
CastImageFilter::ExecuteInternalToLabel( const TImageType* inImage )
{
  typedef TImageType                                InputImageType;
  typedef TOutputImageType                          OutputImageType;
  typedef typename OutputImageType::LabelObjectType LabelObjectType;
  typedef typename LabelObjectType::LabelType       LabelType;

  typedef itk::Image<LabelType, InputImageType::ImageDimension> LabelImageType;

  typedef itk::LabelImageToLabelMapFilter<InputImageType, OutputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( inImage );
  filter->Update();

   Image::Pointer out = new Image( filter->GetOutput() );

   return out;
}

void CastImageFilter::ExecuteDispatchLogicError( void ) throw( GenericException )
{
  assert( false );
  sitkExceptionMacro( "Logic Error: should not have pixel id for uninstatiated pixels" );
}

} // end namespace simple
} // end namespace itk
