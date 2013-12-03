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
#ifndef __sitkCreateKernel_h
#define __sitkCrateKernel_h


#include "sitkKernel.h"
#include <itkFlatStructuringElement.h>

namespace itk
{

namespace simple
{

template< unsigned int VImageDimension >
itk::FlatStructuringElement< VImageDimension >
CreateKernel( KernelEnum kernelType, const std::vector<uint32_t> &size )
{
  typedef typename itk::FlatStructuringElement< VImageDimension > ITKKernelType;

  typename ITKKernelType::SizeType radius = sitkSTLVectorToITK<typename ITKKernelType::SizeType>( size );

  switch (kernelType)
    {
    case sitkAnnulus:
      return ITKKernelType::Annulus( radius, 1, false );
    case sitkBall:
      return ITKKernelType::Ball( radius );
    case sitkBox:
      return ITKKernelType::Box( radius );
    case sitkCross:
      return ITKKernelType::Cross( radius );
    case sitkPolygon3:
      return ITKKernelType::Polygon( radius, 3 );
    case sitkPolygon4:
      return ITKKernelType::Polygon( radius, 4 );
    case sitkPolygon5:
      return ITKKernelType::Polygon( radius, 5 );
    case sitkPolygon6:
      return ITKKernelType::Polygon( radius, 6 );
    case sitkPolygon7:
      return ITKKernelType::Polygon( radius, 7 );
    case sitkPolygon8:
      return ITKKernelType::Polygon( radius, 8 );
    case sitkPolygon9:
      return ITKKernelType::Polygon( radius, 9 );
    default:
      sitkExceptionMacro( "Logic Error: Unknown Kernel Type" );
    }


}


} // end namespace simple
} // end namespace itk


#endif //__sitkCreateInterpolator_h
