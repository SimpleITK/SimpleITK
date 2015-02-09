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

#include "sitkImageRegistrationMethod_CreateMetric.hxx"
#include "itkImage.h"
namespace itk
{
namespace simple
{
template SITKRegistration_EXPORT
itk::ImageToImageMetricv4<itk::Image<float, 2>,
                          itk::Image<float, 2>,
                          itk::Image<float, 2>,
                          double,
                          DefaultImageToImageMetricTraitsv4< itk::Image<float, 2>, itk::Image<float, 2>, itk::Image<float, 2>, double >
                          >*ImageRegistrationMethod::CreateMetric<itk::Image<float, 2> >( );


template SITKRegistration_EXPORT
itk::ImageToImageMetricv4<itk::Image<double, 2>,
                          itk::Image<double, 2>,
                          itk::Image<double, 2>,
                          double,
                          DefaultImageToImageMetricTraitsv4< itk::Image<double, 2>, itk::Image<double, 2>, itk::Image<double, 2>, double >
                          >*ImageRegistrationMethod::CreateMetric<itk::Image<double, 2> >( );


template SITKRegistration_EXPORT
itk::ImageToImageMetricv4<itk::Image<float, 3>,
                          itk::Image<float, 3>,
                          itk::Image<float, 3>,
                          double,
                          DefaultImageToImageMetricTraitsv4< itk::Image<float, 3>, itk::Image<float, 3>, itk::Image<float, 3>, double >
                          >*ImageRegistrationMethod::CreateMetric<itk::Image<float, 3> >( );


template SITKRegistration_EXPORT
itk::ImageToImageMetricv4<itk::Image<double, 3>,
                          itk::Image<double, 3>,
                          itk::Image<double, 3>,
                          double,
                          DefaultImageToImageMetricTraitsv4< itk::Image<double, 3>, itk::Image<double, 3>, itk::Image<double, 3>, double >
                          >*ImageRegistrationMethod::CreateMetric<itk::Image<double, 3> >( );

}
}
