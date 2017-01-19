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

// This example is based on ITK's DeformableRegistration2.cxx example


#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

namespace sitk = itk::simple;


class IterationUpdate
  : public sitk::Command
{
public:
  IterationUpdate( const sitk::DemonsRegistrationFilter &m)
    : m_Filter(m)
    {}

  virtual void Execute( )
    {
      // use sitk's output operator for std::vector etc..
      using sitk::operator<<;

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      std::cout << std::setw(3) << m_Filter.GetElapsedIterations();
      std::cout << " = " << std::setw(10) << m_Filter.GetMetric();
      std::cout << std::endl;

      std::cout.copyfmt(state);
    }

private:
  const sitk::DemonsRegistrationFilter &m_Filter;

};



int main(int argc, char *argv[])
{

  if ( argc < 4 )
    {
    std::cerr << "Usage: " << argv[0] << " <fixedImageFilter> <movingImageFile> <outputTransformFile>" << std::endl;
    return 1;
    }

  sitk::Image fixed = sitk::ReadImage( argv[1], sitk::sitkFloat32 );

  sitk::Image moving = sitk::ReadImage( argv[2], sitk::sitkFloat32 );

  sitk::HistogramMatchingImageFilter matcher;
  matcher.SetNumberOfHistogramLevels( 1024 );
  matcher.SetNumberOfMatchPoints( 7 );
  matcher.ThresholdAtMeanIntensityOn();
  moving = matcher.Execute(moving, fixed);

  sitk::DemonsRegistrationFilter filter;

  IterationUpdate cmd(filter);
  filter.AddCommand( sitk::sitkIterationEvent, cmd );

  filter.SetNumberOfIterations( 50 );
  filter.SetStandardDeviations( 1.0 );

  sitk::Image displacementField = filter.Execute( fixed, moving );

  std::cout << "-------" << std::endl;
  std::cout << "Number Of Iterations: " << filter.GetElapsedIterations() << std::endl;
  std::cout << " RMS: " << filter.GetRMSChange() << std::endl;

  sitk::DisplacementFieldTransform outTx( displacementField );

  sitk::WriteTransform(outTx, argv[3]);

  return 0;
}
