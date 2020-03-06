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

#include "sitkInterpolator.h"

#define sitkInterpolatorToStringCaseMacro(n) case sitk##n: return ( os << #n )

namespace itk
{
namespace simple
{

std::ostream& operator<<(std::ostream& os, const InterpolatorEnum i)
{
  switch (i)
    {
    sitkInterpolatorToStringCaseMacro(NearestNeighbor);
    sitkInterpolatorToStringCaseMacro(Linear);
    sitkInterpolatorToStringCaseMacro(BSpline);
    sitkInterpolatorToStringCaseMacro(Gaussian);
    sitkInterpolatorToStringCaseMacro(LabelGaussian);
    sitkInterpolatorToStringCaseMacro(HammingWindowedSinc);
    sitkInterpolatorToStringCaseMacro(CosineWindowedSinc);
    sitkInterpolatorToStringCaseMacro(WelchWindowedSinc);
    sitkInterpolatorToStringCaseMacro(LanczosWindowedSinc);
    sitkInterpolatorToStringCaseMacro(BlackmanWindowedSinc);
    sitkInterpolatorToStringCaseMacro(BSplineResamplerOrder1);
    sitkInterpolatorToStringCaseMacro(BSplineResamplerOrder2);
//  sitkBSplineResampler = 11,
    sitkInterpolatorToStringCaseMacro(BSplineResamplerOrder3);
    sitkInterpolatorToStringCaseMacro(BSplineResamplerOrder4);
    sitkInterpolatorToStringCaseMacro(BSplineResamplerOrder5);
    }
  return os;
}

} // end namespace simple
} // end namespace itk
