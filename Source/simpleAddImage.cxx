#include "simpleAddImage.h"
#include <itkAddImageFilter.h>

namespace itk {
namespace simple {

AddImage::AddImage ()
  {
  }

std::string AddImage::toString() 
  {
  std::ostringstream out;
  out << "itk::simple::AddImage\n" << "\n";
  return out.str();
  }

Image::Pointer AddImage::execute ( Image::Pointer image1, Image::Pointer image2 ) 
  {
  // Would likely want to check to see if the images are null
  switch ( image1->getImageDataType() ) 
    {
    sitkImageDataTypeSwitch
      ( DataType1,
      switch (image2->getImageDataType() ) 
        {
        sitkImageDataTypeSwitch
          ( DataType2,
          return (this->executeInternal<DataType1, DataType2>(image1, image2))  // Note the extra parens
          );
        }
      );
    }
  return NULL;
  }

template <class TInPixel1, class TInPixel2> 
Image::Pointer AddImage::executeInternal ( Image::Pointer inImage1, Image::Pointer inImage2 ) 
  {
  typedef itk::Image<TInPixel1,3> InputImageType1;
  typedef itk::Image<TInPixel2,3> InputImageType2;
  typedef itk::Image<float,3> OutputImageType;
  typename InputImageType1::Pointer image1 = dynamic_cast <InputImageType1*> ( inImage1->getITKImage().GetPointer() );
  typename InputImageType2::Pointer image2 = dynamic_cast <InputImageType2*> ( inImage2->getITKImage().GetPointer() );
  
  if ( image1.IsNull() || image2.IsNull() ) 
    {
    // Take some action
    return NULL;
    }
  
  typedef itk::AddImageFilter<InputImageType1, InputImageType2, OutputImageType> AddImageFilterType;
  typename AddImageFilterType::Pointer filter = AddImageFilterType::New();
  
  filter->SetInput1 ( image1 );
  filter->SetInput2 ( image2 );
  filter->Update();
  
  Image::Pointer out = new Image ( filter->GetOutput(), sitkFloat32 );
  out->getITKImage()->DisconnectPipeline();
  return out;
  }

} // end namespace simple
} // end namespace itk
