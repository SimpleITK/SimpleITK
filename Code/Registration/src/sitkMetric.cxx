#include "sitkMetric.h"
#include "itkMattesMutualInformationImageToImageMetric.h"

namespace itk
{
namespace simple
{

class PimpleMetricBase
{
public:
  typedef PimpleMetricBase Self;

  virtual ~PimpleMetricBase( void ) {};

  virtual PimpleMetricBase *DeepCopy( void ) const
    {
      return new PimpleMetricBase;
    }


  itk::SingleValuedCostFunction* GetMetricBase( const Image & image )
    {

      // The pixel IDs supported
      typedef BasicPixelIDTypeList              PixelIDTypeList;

      typedef itk::SingleValuedCostFunction* (Self::*MemberFunctionType)(void );

      typedef GetMetricBaseMemberFunctionAddressor<MemberFunctionType> GetMetricBaseAddressor;

      detail::MemberFunctionFactory<MemberFunctionType> baseMemberFactory(this);
      baseMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 3,  GetMetricBaseAddressor > ();
      baseMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 2,  GetMetricBaseAddressor > ();

      assert( image.GetPixelIDValue() != sitkUnknown );

      return baseMemberFactory.GetMemberFunction( image.GetPixelIDValue(), image.GetDimension() )();
    }

  std::string ToString( void ) const
    {
      return std::string();
    }

protected:

    /** An addressor of GetMetricBaseInternal to be utilized with
     * registering member functions with the factory.
     */
    template < class TMemberFunctionPointer >
    struct GetMetricBaseMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImageType >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template GetMetricBaseInternal< TImageType >;
      }
    };

  template <typename TImageType>
  itk::SingleValuedCostFunction* GetMetricBaseInternal(void )
    {
      typedef ::itk::MattesMutualInformationImageToImageMetric<TImageType, TImageType> MetricType;
      typename MetricType::Pointer metric = MetricType::New();
      metric->SetNumberOfHistogramBins( 128 );
      metric->SetNumberOfSpatialSamples( 20000 );
      stash = metric.GetPointer();
      return metric.GetPointer();
    }

private:
  itk::Object::Pointer stash;
};

Metric::Metric( )
  : m_PimpleMetric( NULL )
{
  m_PimpleMetric = new PimpleMetricBase();
}

Metric::Metric( MetricEnum type)
  : m_PimpleMetric( NULL )
{
  this->InternalInitialization(type);
}

Metric::~Metric()
{
  delete m_PimpleMetric;
  this->m_PimpleMetric = NULL;
}

Metric::Metric( const Metric &txf )
  : m_PimpleMetric( NULL )
{
  m_PimpleMetric = txf.m_PimpleMetric->DeepCopy();
}

Metric& Metric::operator=( const Metric &m )
{
  // note: if m and this are the same,the following statements
  // will be safe. It's also exception safe.
  std::auto_ptr<PimpleMetricBase> temp( m.m_PimpleMetric->DeepCopy() );
  delete this->m_PimpleMetric;
  this->m_PimpleMetric = temp.release();
  return *this;
}

itk::SingleValuedCostFunction* Metric::GetITKBase( const Image & image ) const
{
  assert( m_PimpleMetric );
  return this->m_PimpleMetric->GetMetricBase(image);
}


std::string Metric::ToString( void ) const
{
  assert( m_PimpleMetric );
  return this->m_PimpleMetric->ToString();
}

void Metric::InternalInitialization( MetricEnum type )
{
}

} // end namespace simple
} // end namespace itk
