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
    virtual ~Registration();

    Registration& SetTransform ( const Transform &transform);
    const Transform &GetTransform( void ) const;


    Registration& SetInterpolator ( InterpolateFunctionEnum interp );
    InterpolateFunctionEnum GetInterpolator( void ) const;

    virtual Registration& SetMetric ( const Metric &metric );
    virtual const Metric& GetMetric() const;

    //virtual Registration& SetOptimizer ( SOptimizer *optimizer );
    // virtual Optimizer& GetOptimizer();

    virtual Transform Execute ( const Image &fixed, const Image &moving );

    std::string ToString () const;

  protected:
    Transform               m_Transform;
    InterpolateFunctionEnum m_Interpolator;
    Metric                  m_Metric;
    //std::auto_ptr<SOptimizer> m_Optimizer;

    template<class TImage>
    Transform ExecuteInternal ( const Image &fixed, const Image &moving );

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


    typedef Transform (Registration::*MemberFunctionType)( const Image &fixed, const Image &moving );
    friend struct RegistrationAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
  };

Transform Register ( const Image &fixed, const Image &moving, const Transform &transform, InterpolateFunctionEnum interpolator, const Metric &metric, SOptimizer *optimizer );
}
}

#endif
