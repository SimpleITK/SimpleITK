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

#include "SimpleITK.h"
#include "sitkExtractImageFilter.h"

#include <cstdlib>
#include <iostream>

namespace sitk = itk::simple;

using itk::simple::operator<<;

// Forward declaration to specialize the implementation with the function's
// argument and returns types.
template <class T> struct SliceBySliceDecorator;

/* \brief A function decorator to adapt an function to process an image as a
 * sequence of 2D (slices or) images.
 *
 * For ease of use the makeSliceBySlice procedure should be used to construct
 * the SliceBySliceDecorator.
 *
 * The overloaded function call operator(), enable objects to be used as
 * functions.
 *
 * The return image is the first argument modified with the slice by slice
 * results of the f function.
 */
template <class R, class ImageArg, class... Args>
struct SliceBySliceDecorator<R(ImageArg, Args...)>
{
  using FunctionType = std::function<R(ImageArg, Args...)>;

  explicit SliceBySliceDecorator(FunctionType f) : f_(std::move(f)) {}

  R operator()(sitk::Image &image, Args... args)
  {
    const auto image_size = image.GetSize();

    unsigned int dim = image.GetDimension();

    if (dim <= iter_dim)
    {
      // If no sub-dimension extraction is required then directly run the
      // function on the input and replace it.
      image = f_(image, args...);
      return image;
    }

    std::vector<unsigned int> extract_size = image.GetSize();
    std::fill(extract_size.begin() + iter_dim, extract_size.end(), 0);

    std::vector<int> extract_index(dim, 0);

    // The extract filter is used to extract a 2D image from the higher
    // dimensional input image.
    sitk::ExtractImageFilter extractor;
    extractor.SetSize(extract_size);

    // The paste filter places the processed slice back into the original image
    // at the same location where the extraction occurred. The default
    // value of DestinationSkipAxes is [ false, false, true, ... ], which is
    // correct for the situation of preserving the first dimensions and
    // collapsing the remainder.
    sitk::PasteImageFilter paster;
    paster.SetSourceSize(std::vector<unsigned int>(
        extract_size.begin(), extract_size.begin() + iter_dim));


    while (static_cast<unsigned int>(extract_index.back()) < image.GetSize().back())
    {
      extractor.SetIndex(extract_index);

      // Store the results of the function as a r-value, so that the
      // paste filter will run "in place" and reuse the buffer for output.
      sitk::Image &&temp_image = f_(extractor.Execute(image), args...);

      paster.SetDestinationIndex(extract_index);

      image = paster.Execute(image, temp_image);

      // increment extraction index
      ++extract_index[iter_dim];
      for (unsigned int e = iter_dim; e + 1 < dim; ++e)
      {
        // if the index element is beyond the size, propagate to next element.
        if (static_cast<unsigned int>(extract_index[e]) > image.GetSize()[e])
        {
          extract_index[e] = 0;
          ++extract_index[e + 1];
        }
      }
    }
    return image;
  }
  FunctionType f_;
  constexpr static unsigned int iter_dim = 2;
};

/** Construct a function object to wrap a function f to process a volume slice by
 * slice with the f function.
 *
 * The f function must take an sitk::Image object as the first parameter and
 * return an sitk::Image.
 */
template <class R, class... Args>
SliceBySliceDecorator<R(Args...)> makeSliceBySlice(R (*f)( Args...))
{
  using DecoratorType = SliceBySliceDecorator<R(Args...)>;
  return DecoratorType(typename DecoratorType::FunctionType(f));
}

int main( int argc, char *argv[])
{

  if ( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0] << " <inputImage> <outputImage>" << std::endl;
    return 1;
  }

  sitk::Image tempImage = sitk::ReadImage(argv[1]);

  // The parameters to the filter are hard coded to simplify the example.
  float alpha = 0.3f;
  float beta = 0.3f;
  std::vector<unsigned int> radius(2, 20);

  // The return type of the function decorator is complex, so the auto type is
  // used for brevity.
  auto AdaptiveHistogramEqualization2D = makeSliceBySlice(sitk::AdaptiveHistogramEqualization);

  // Execute the decorated function.
  tempImage = AdaptiveHistogramEqualization2D(tempImage, radius, alpha, beta);

  sitk::WriteImage(tempImage, argv[2]);

  return 0;
}
