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
#include <SimpleITKTestHarness.h>

#include "sitkImageFileWriter.h"
#include "sitkImageFileReader.h"
#include "sitkGaussianImageSource.h"


TEST(IO,DicomMetaData) {

  namespace sitk = itk::simple;


  sitk::GaussianImageSource gaussian;


  std::vector<unsigned int> size(3);
  size[0] = 64;
  size[1] = 64;
  size[2] = 1;

  std::vector<double> sigma(3);
  sigma[0] = 8.0;
  sigma[1] = 16.0;
  sigma[2] = 24.0;

  std::vector<double> mean(3);
  mean[0] = 24.0;
  mean[1] = 32.0;
  mean[2] = 40.0;

  std::vector<double> origin(3);
  origin[0] = -5.0;
  origin[1] = 6.0;
  origin[2] = 7.0;

  std::vector<double> spacing(3);
  spacing[0] = 0.8;
  spacing[1] = 0.8;
  spacing[2] = 1.0;


  sitk::Image fromSource( 0, 0, sitk::sitkUInt16 );

  gaussian.SetOutputPixelType(sitk::sitkInt16);
  gaussian.SetSize(size);
  gaussian.SetSigma(sigma);
  gaussian.SetMean(mean);
  gaussian.SetScale(255.0);
  gaussian.SetOrigin(origin);
  gaussian.SetSpacing(spacing);
  fromSource = gaussian.Execute();

  // Write the Gaussian out as a Dicom image
  std::string filename = dataFinder.GetOutputDirectory()+"/gauss.dcm";

  sitk::WriteImage(fromSource, filename);


  sitk::Image dcm( 0, 0, sitk::sitkUInt16 );

  // Read the Dicom back in
  dcm = sitk::ReadImage(filename);

  // MetaData Key for Image Patient Position
  EXPECT_EQ(dcm.HasMetaDataKey ("0020|0032"), 1);
  // MetaData Key for Pixel Spacing
  EXPECT_EQ(dcm.HasMetaDataKey ("0028|0030"), 1);
}
