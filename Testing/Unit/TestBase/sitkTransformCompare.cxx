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
#include <SimpleITK.h>
#include <memory>
#include "sitkTransformCompare.h"
#include "sitkTransformToDisplacementFieldFilter.h"

TransformCompare::TransformCompare()
  : m_Tolerance(0.0)
{
}


float TransformCompare::Compare( const itk::simple::Transform &transform,
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


float
TransformCompare::Compare(const itk::simple::Transform & transform,
                          const itk::simple::Image &     baselineDisplacement,
                          bool                           reportErrors)
{
  namespace sitk = itk::simple;

  sitk::TransformToDisplacementFieldFilter toDisplacementField;
  toDisplacementField.SetOutputPixelType(baselineDisplacement.GetPixelID());
  toDisplacementField.SetReferenceImage(baselineDisplacement);
  sitk::Image displacement = toDisplacementField.Execute(transform);

  sitk::Image magnitude = sitk::VectorMagnitude(sitk::Subtract(displacement, baselineDisplacement));

  sitk::Image diff_squared = sitk::Multiply(magnitude, magnitude);

  sitk::StatisticsImageFilter stats;
  stats.Execute(diff_squared);
  double rms = std::sqrt(stats.GetMean());

  if (reportErrors && rms > m_Tolerance)
  {
    std::ostringstream msg;
    msg << "TransformCompare: transformed image points Root Mean Square (RMS) difference was " << rms
        << " which exceeds the tolerance of " << m_Tolerance;
    msg << "\n";
    m_Message = msg.str();

    std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << m_Tolerance << "</DartMeasurement>"
              << std::endl;
  }

  return float(rms);
}
