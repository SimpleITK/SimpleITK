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
#include <SimpleITK.h>
#include <memory>
#include "sitkTransformCompare.h"
#include "sitkTransformToDisplacementFieldFilter.h"

TransformCompare::TransformCompare()
  : m_Tolerance(0.0)
{
}



bool TransformCompare::Compare( const itk::simple::Transform &transform,
                                const itk::simple::Transform &baselineTransform,
                                const itk::simple::Image &fixedImage )
{
  namespace sitk = itk::simple;

  sitk::TransformToDisplacementFieldFilter toDisplacementField;
  toDisplacementField.SetOutputPixelType( sitk::sitkVectorFloat64 );
  toDisplacementField.SetReferenceImage( fixedImage );
  sitk::Image baselineDisplacement = toDisplacementField.Execute( baselineTransform );

  return this->Compare( transform, baselineDisplacement );
}


bool TransformCompare::Compare( const itk::simple::Transform &transform,
                                const itk::simple::Image &baselineDisplacement )
{
  namespace sitk = itk::simple;

  sitk::TransformToDisplacementFieldFilter toDisplacementField;
  toDisplacementField.SetOutputPixelType( baselineDisplacement.GetPixelID() );
  toDisplacementField.SetReferenceImage( baselineDisplacement );
  sitk::Image displacement = toDisplacementField.Execute( transform );

  sitk::Image diff =  sitk::Subtract( displacement, baselineDisplacement );

  diff = sitk::VectorMagnitude(diff);
  diff = sitk::Multiply(diff, diff);

  sitk::StatisticsImageFilter stats;
  stats.Execute ( diff );
  double rms = std::sqrt ( stats.GetMean() );

  std::cout << "<DartMeasurement name=\"RMSDifference\" type=\"numeric/float\">" << rms << "</DartMeasurement>" << std::endl;

  if ( rms > m_Tolerance )
    {
    std::ostringstream msg;
    msg << "TransformCompare: transformed image points Root Mean Square (RMS) difference was " << rms << " which exceeds the tolerance of " << m_Tolerance;
    msg << "\n";
    m_Message = msg.str();

    std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << m_Tolerance << "</DartMeasurement>" << std::endl;

    return false;
    }

  return true;
}
