#include "sitkAffineTransform.h"

namespace itk
{
namespace simple
{
  AffineTransform::AffineTransform()
  {
  }

  Transform* AffineTransform::Clone()
  {
    return new AffineTransform ( *this );
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
        {
        xform = (::itk::TransformBase*)::itk::AffineTransform<double,2>::New();
        if ( m_Parameters.size() != 0 )
          {
            // Set the parameters
            ::itk::AffineTransform<double,2>::ParametersType params = xform->GetParameters();
            if ( params.GetSize() != m_Parameters.size() )
              {
                sitkExceptionMacro( << "Expected " << params.GetSize() << " parameters, but was given " << m_Parameters.size() );
              }
            for ( size_t idx = 0; idx < params.GetSize(); idx++ )
              {
                params[idx] = m_Parameters[idx];
              }
            xform->SetParameters ( params );
          }
        return xform;
        break;
        }
      case 3:
        {
        xform = (::itk::TransformBase*)::itk::AffineTransform<double,3>::New();
        if ( m_Parameters.size() != 0 )
          {
          ::itk::AffineTransform<double,3>::ParametersType params = xform->GetParameters();
          if ( params.GetSize() != m_Parameters.size() )
            {
            sitkExceptionMacro( << "Expected " << params.GetSize() << " parameters, but was given " << m_Parameters.size() );
            }
          for ( size_t idx = 0; idx < params.GetSize(); idx++ )
            {
            params[idx] = m_Parameters[idx];
            }
          xform->SetParameters ( params );
          }
        return xform;
        break;
        }
      }
    sitkExceptionMacro ( << "Transforms must be 2 or 3 dimensional" );
    return NULL;
  }

}
}


