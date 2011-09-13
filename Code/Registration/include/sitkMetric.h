#ifndef __sitkMetric_h
#define __sitkMetric_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{

// Forward declaration for pointer
class SingleValuedCostFunction;

namespace simple
{

class Registration;
class PimpleMetricBase;
enum MetricEnum {
  sitkMeansSquares,
  sitkNormalizedCorrelation,
  sitkGradientDifference };


class Metric
  {
  public:
    Metric();
    Metric( MetricEnum type );
    virtual ~Metric();

    //
    Metric &operator=( const Metric &);
    Metric( const Metric & );

    itk::SingleValuedCostFunction* GetITKBase( const Image & image ) const;

    std::string ToString( void ) const;
  protected:

    void InternalInitialization( MetricEnum type );

    PimpleMetricBase *m_PimpleMetric;
  };
}
}

#endif
