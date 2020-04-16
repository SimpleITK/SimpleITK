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
#ifndef sitkCreateKernel_h
#define sitkCreateKernel_h


#include "sitkKernel.h"
#include <itkFlatStructuringElement.h>

namespace itk
{

namespace simple
{

#define sitkKernelPolygonCreateMacro(n) \
  case sitkPolygon##n: return ITKKernelType::Polygon( radius, n )

template< unsigned int VImageDimension >
itk::FlatStructuringElement< VImageDimension >
CreateKernel( KernelEnum kernelType, const std::vector<uint32_t> &size )
{
  using ITKKernelType = typename itk::FlatStructuringElement< VImageDimension >;

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
    sitkKernelPolygonCreateMacro(3);
    sitkKernelPolygonCreateMacro(4);
    sitkKernelPolygonCreateMacro(5);
    sitkKernelPolygonCreateMacro(6);
    sitkKernelPolygonCreateMacro(7);
    sitkKernelPolygonCreateMacro(8);
    sitkKernelPolygonCreateMacro(9);
    default:
      sitkExceptionMacro( "Logic Error: Unknown Kernel Type" );
    }

#undef sitkKernelPolygonCreateMacro


}


} // end namespace simple
} // end namespace itk


#endif // sitkCreateKernel_h
