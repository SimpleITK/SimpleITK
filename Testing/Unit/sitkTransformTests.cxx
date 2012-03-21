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

#include "sitkTransform.h"

#include "SimpleITKTestHarness.h"

namespace sitk = itk::simple;


TEST(TransformTest, Construction) {


  sitk::Transform tx0( 2, sitk::sitkIdentity);
  std::cout << tx0.ToString() << std::endl;
  sitk::Transform tx1( 3, sitk::sitkIdentity);
  std::cout << tx1.ToString() << std::endl;

  sitk::Transform tx2( 2, sitk::sitkTranslation);
  std::cout << tx2.ToString() << std::endl;
  sitk::Transform tx3( 3, sitk::sitkTranslation);
  std::cout << tx3.ToString() << std::endl;

  sitk::Transform tx4( 2, sitk::sitkScale);
  std::cout << tx4.ToString() << std::endl;
  sitk::Transform tx5( 3, sitk::sitkScale);
  std::cout << tx5.ToString() << std::endl;

  sitk::Transform tx6( 2, sitk::sitkScaleLogarithmic);
  std::cout << tx6.ToString() << std::endl;
  sitk::Transform tx7( 3, sitk::sitkScaleLogarithmic);
  std::cout << tx7.ToString() << std::endl;

  sitk::Transform tx8( 2, sitk::sitkQuaternionRigid);
  std::cout << tx8.ToString() << std::endl;
  sitk::Transform tx9( 3, sitk::sitkQuaternionRigid);
  std::cout << tx9.ToString() << std::endl;

  sitk::Transform tx10( 2, sitk::sitkVersor);
  std::cout << tx10.ToString() << std::endl;
  sitk::Transform tx11( 3, sitk::sitkVersor);
  std::cout << tx11.ToString() << std::endl;

  sitk::Transform tx12( 2, sitk::sitkAffine);
  std::cout << tx12.ToString() << std::endl;
  sitk::Transform tx13( 3, sitk::sitkAffine);
  std::cout << tx13.ToString() << std::endl;

  sitk::Transform tx14( 2, sitk::sitkAffine);
  std::cout << tx14.ToString() << std::endl;
  sitk::Transform tx15( 3, sitk::sitkAffine);
  std::cout << tx15.ToString() << std::endl;


  // default constructable
  sitk::Transform tx16;
  std::cout << tx0.ToString() << std::endl;
}
