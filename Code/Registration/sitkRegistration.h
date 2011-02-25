#ifndef __sitkRegistration_h
#define __sitkRegistration_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkPixelContainer.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
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
    std::vector<double> Execute ( Image* fixed, Image* moving );

  protected:
    template<class TImage>
    std::vector<double> ExecuteInternal ( Image* fixed, Image* moving );

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

    typedef std::vector<double> (Registration::*MemberFunctionType)( Image* fixed, Image* moving );
    friend struct RegistrationAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
  };
}
}

#endif
