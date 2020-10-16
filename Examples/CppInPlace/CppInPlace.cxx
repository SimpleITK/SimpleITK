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
#include "sitkImageOperators.h"

#include <cstdlib>
#include <iostream>

namespace sitk = itk::simple;


// Rescale the intensity range for image to -1 to 1.
sitk::Image MinusOneToOne(const sitk::Image &image)
{
  sitk::MinimumMaximumImageFilter mm;
  mm.Execute(image);

  const double shift = 0.5 * (mm.GetMinimum() + mm.GetMaximum());
  const double scale = (mm.GetMaximum() - mm.GetMinimum())*2.0;

  // The CastImageFilter does not operate in-place, so the image argument to
  // this function is declared as a constant reference.
  //
  // The Image operators use in-place execution with the rvalue reference
  // returned from the Cast procedure.
  return  (sitk::Cast(image, sitk::sitkFloat32) - shift) / scale;
}


// Compute the difference between two Gaussian convoluted images.
sitk::Image DifferenceOfGaussian(sitk::Image image, double sigma1, double sigma2)
{
  sitk::SmoothingRecursiveGaussianImageFilter g1;
  g1.SetSigma(sigma1);

  sitk::SmoothingRecursiveGaussianImageFilter g2;
  g2.SetSigma(sigma2);

  // This temporary is create to ensure the method is executed before image is
  // moved and made invalid.
  sitk::Image &&temp = g1.Execute(image);

  // Both Subtract and g2 are executed inplace.
  return sitk::Subtract(temp, g2.Execute(std::move(image)));
}

int main( int argc, char *argv[])
{

  //
  // Check command line parameters
  //
  if( argc < 5 )
  {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage outputImage lowerSigma upperSigma" << std::endl;
    return 1;
  }


  const double sigma1 = atof(argv[3]);
  const double sigma2 = atof(argv[4]);

  //
  // Read the image
  //
  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );


  // The below explicitly declares the image variable as a rvalue temporary.
  // Having a rvalue typed variable enables explicit declaration of temporary
  // temporary images used between filters.Alternatively this could be written
  // in one line at the sacrifice of readability and explicitness:
  // image = DifferenceOfGaussian(MinusOneToOne(reader.Execute()), sigma1, sigma2);
  //

  sitk::Image &&image = reader.Execute();
  image = MinusOneToOne(image);
  image = DifferenceOfGaussian(image, sigma1, sigma2);


  //
  // Set up writer
  //
  sitk::WriteImage( image, std::string( argv[2] ) );

  return 0;
}
