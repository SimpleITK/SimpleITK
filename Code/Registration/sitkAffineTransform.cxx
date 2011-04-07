#include "sitkAffineTransform.h"

namespace itk
{
namespace simple
{
  AffineTransform::AffineTransform() {
  }

  std::vector<double> AffineTransform::GetOptimizerScales ( int dimension )
  {
    unsigned int NumberOfParameters = this->GetTransform ( dimension )->GetNumberOfParameters();
    std::vector<double> scales;
    for ( unsigned int idx = 0; idx < NumberOfParameters; idx++ )
    {
      scales.push_back ( 1.0 );
      if ( idx >= (unsigned int)(dimension*dimension) )
        {
        scales[idx] = 0.0001;
        }
    }
    return scales;
  }

  ::itk::TransformBase::Pointer AffineTransform::GetTransform ( int dimension )
  {
    ::itk::TransformBase::Pointer xform;
    switch ( dimension )
      {
      case 2:
        xform = (::itk::TransformBase*)::itk::AffineTransform<double,2>::New();
        return xform;
        break;
      case 3:
        xform = (::itk::TransformBase*)::itk::AffineTransform<double,3>::New();
        return xform;
        break;
      }
    sitkExceptionMacro ( << "Transforms must be 2 or 3 dimensional" );
    return NULL;
  }

}
}


