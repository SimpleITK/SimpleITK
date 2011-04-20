#ifndef __sitkRegistration_h
#define __sitkRegistration_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkMetric.h"
#include "sitkInterpolate.h"
#include "sitkTransform.h"
#include "sitkOptimizer.h"
#include "sitkMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

  class Registration
  {
  public:
    Registration();
    Registration& SetUseCenteredInitialization ( bool init );
    bool GetUseCenteredInitialization();
    Registration& SetUseCenteredInitializationOn();
    Registration& SetUseCenteredInitializationOff();
    Registration& SetTransform ( Transform *transform );
    // virtual Transform& GetTransform();
    virtual Registration& SetInterpolate ( Interpolate *interpolate );
    // virtual Interpolate& GetInterpolate();
    virtual Registration& SetMetric ( Metric *metric );
    // virtual Metric& GetMetric();
    virtual Registration& SetOptimizer ( Optimizer *optimizer );
    // virtual Optimizer& GetOptimizer();
    virtual std::vector<double> Execute ( const Image &fixed, const Image &moving );

  protected:
    bool m_UseCenteredInitialization;
    std::auto_ptr<Transform> m_Transform;
    std::auto_ptr<Interpolate> m_Interpolate;
    std::auto_ptr<Metric> m_Metric;
    std::auto_ptr<Optimizer> m_Optimizer;

    template<class TImage>
    std::vector<double> ExecuteInternal ( const Image &fixed, const Image &moving );

// SWIG does not appear to process private classes correctly
#ifndef SWIG
    template < class TMemberFunctionPointer >
    struct RegistrationAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImage >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template ExecuteInternal < TImage >;
      }
    };
#endif


    typedef std::vector<double> (Registration::*MemberFunctionType)( const Image &fixed, const Image &moving );
    friend struct RegistrationAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
  };

std::vector<double> Register ( const Image &fixed, const Image &moving, Transform *transform, Interpolate *interpolate, Metric *metric, Optimizer *optimizer );
}
}

#endif
