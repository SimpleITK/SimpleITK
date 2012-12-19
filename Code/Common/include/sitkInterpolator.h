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
#ifndef __sitkInterpolator_h
#define __sitkInterpolator_h


namespace itk
{
namespace simple
{

enum InterpolatorEnum { sitkNearestNeighbor = 1,
                        sitkLinear = 2,
                        sitkBSpline = 3,
                        sitkGaussian = 4,
                        sitkLabelGaussian = 5,
                        sitkHammingWindowedSinc = 6,
                        sitkCosineWindowedSinc = 7,
                        sitkWelchWindowedSinc = 8,
                        sitkLanczosWindowedSinc = 9,
                        sitkBlackmanWindowedSinc = 10
};


} // end namespace simple
} // end namespace itk


#endif //__sitkInterpolator_h
