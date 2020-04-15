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
#include "sitkImageFilter.h"

#include "itkProcessObject.h"

#include <iostream>


namespace itk {
namespace simple {

namespace
{

      void CheckImageMatchingDimension(const Image &image1, const Image& image2,
                                       const std::string &image2Name, const std::string &filterName  )
      {
        if ( image1.GetDimension() != image2.GetDimension() )
          {
          sitkExceptionMacro ( << "Input \"" << image2Name << "\" for \"" << filterName << "\" has dimension of "
                               << image2.GetDimension() << " which does not match the primary input's dimension of "
                               << image1.GetDimension() << "!" );
          }

      }

      void CheckImageMatchingPixelType(const Image &image1, const Image& image2,
                                       const std::string &image2Name,const std::string &filterName  )
      {
        if ( image1.GetPixelID() != image2.GetPixelIDValue() )
          {
          sitkExceptionMacro ( << "Input \"" << image2Name << "\" for \"" << filterName << "\" has pixel type of \""
                               << image2.GetPixelIDTypeAsString() << " which does not match the primary input's pixel type of \""
                               << image1.GetPixelIDTypeAsString() << "!\n"
                               << "The \"" << image2Name << "\" input may need casting to the \""
                               << image1.GetPixelIDTypeAsString() << "\" pixel type." );
          }
      }

      void CheckImageMatchingSize(const Image &image1, const Image& image2,
                                  const std::string &image2Name, const std::string &filterName  )
      {
        if ( image1.GetSize() != image2.GetSize() )
          {
          sitkExceptionMacro ( << "Input \"" << image2Name << "\" for \"" << filterName << "\" has size of "
                               << image2.GetSize() << " which does not match the primary input's size of "
                               << image1.GetSize() << "!" );
          }
      }

}


//----------------------------------------------------------------------------

ImageFilter::ImageFilter () = default;

ImageFilter::~ImageFilter () = default;



void ImageFilter::CheckImageMatchingDimension(const Image &image1, const Image& image2, const std::string &image2Name)
{
  return itk::simple::CheckImageMatchingDimension(image1, image2, image2Name, this->GetName());
}

void ImageFilter::CheckImageMatchingPixelType(const Image &image1, const Image& image2, const std::string &image2Name)
{
  return itk::simple::CheckImageMatchingPixelType(image1, image2, image2Name, this->GetName());
}

void ImageFilter::CheckImageMatchingSize(const Image &image1, const Image& image2, const std::string &image2Name)
{
  return itk::simple::CheckImageMatchingSize(image1, image2, image2Name, this->GetName());
}

} // end namespace simple
} // end namespace itk
