#ifndef __sitkInterpolate_h
#define __sitkInterpolate_h

#include "itkLinearInterpolateImageFunction.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkWindowedSincInterpolateImageFunction.h"


namespace itk
{
namespace simple
{

enum InterpolateFunctionEnum {
  sitkUnknow = -1,
  sitkNearestNeighbor = 1,
  sitkLinearInterpolate = 2,
  sitkWindowedSinc = 3
};

namespace detail
{

template< typename TImageType >
typename itk::InterpolateImageFunction<TImageType, double>::Pointer CreateInterpolator( InterpolateFunctionEnum interp )
{
  typename itk::InterpolateImageFunction<TImageType, double>::Pointer interpolator;
switch( interp )
  {
  case sitkNearestNeighbor:
    interpolator = NearestNeighborInterpolateImageFunction< TImageType, double >::New();
    break;
  case sitkLinearInterpolate:
    interpolator = LinearInterpolateImageFunction< TImageType, double >::New();
    break;
  case sitkWindowedSinc:

    typedef itk::ConstantBoundaryCondition< TImageType >  BoundaryConditionType;
    //const unsigned int WindowRadius = 5;
    typedef itk::Function::HammingWindowFunction<5>  WindowFunctionType;
    interpolator = WindowedSincInterpolateImageFunction< TImageType,
                                                             5,
                                                             WindowFunctionType,
                                                             BoundaryConditionType,
                                                             double >::New();
    break;
  default:
    sitkExceptionMacro( "unknow interpolator" );
  }

return interpolator;
}
}

}
}

#endif // __sitkInterpolate_h
