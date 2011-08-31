#ifndef __sitkInterpolate_h
#define __sitkInterpolate_h

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

}
}

#endif // __sitkInterpolate_h
