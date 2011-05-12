#include "sitkLabelStatisticsImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"

//HACK until itkLabelStaticsImageFilter can return list of valid labels found
#include "itkMinimumMaximumImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
LabelStatisticsImageFilter::LabelStatisticsImageFilter ()
  {

    m_Minimum.clear();
    m_Maximum.clear();
    m_Mean.clear();
    m_Variance.clear();

  this->m_DualMemberFactory.reset( new detail::DualMemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, LabelPixelIDTypeList, 3 > ();
  this->m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, LabelPixelIDTypeList, 2 > ();
  }

//
// ToString
//
std::string LabelStatisticsImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::LabelStatisticsImageFilter\n";
  for( std::map<size_t,double>::const_iterator it=this->m_Minimum.begin();
    it != this->m_Minimum.end();
    ++it)
    {
    out << "\tMinimum[" << it->first << "]"  << this->m_Minimum.find(it->first)->second  << "\n";
    out << "\tMaximum[" << it->first << "]"  << this->m_Maximum.find(it->first)->second  << "\n";
    out << "\tMean[" << it->first << "]"     << this->m_Mean.find(it->first)->second     << "\n";
    out << "\tVariance[" << it->first << "]" << this->m_Variance.find(it->first)->second << "\n";
    }
  return out.str();
  }
//
// Execute
//

Image LabelStatisticsImageFilter::Execute ( const Image& image1 , const Image & labels )
  {
    PixelIDValueType type = image1.GetPixelIDValue();
    unsigned int dimension = image1.GetDimension();

    PixelIDValueType labeltype = labels.GetPixelIDValue();
    unsigned int labeldimension = labels.GetDimension();

    if ( dimension != labeldimension )
      {
      sitkExceptionMacro( "Labelmap and image MUST have same dimensions!" );
      }

    return this->m_DualMemberFactory->GetMemberFunction( type, labeltype, dimension )( image1, labels );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType, class TLabelImageType>
Image LabelStatisticsImageFilter::DualExecuteInternal ( const Image& inImage1, const Image& inLabels )
  {
  typename TImageType::ConstPointer image1 =
    dynamic_cast <const TImageType* > ( inImage1.GetImageBase() );

  if ( image1.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typename TLabelImageType::ConstPointer labelImage =
    dynamic_cast <const TLabelImageType* > ( inLabels.GetImageBase() );
  if ( labelImage.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typedef itk::LabelStatisticsImageFilter<TImageType,TLabelImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->SetLabelInput( labelImage );
  filter->Update();


    {
    //HACK until itk::LabelStatisticsImageFilter is instumented to provide a list of valid labels found
    //     we must search by brute force through all the possiblities looking for valid values.
    typedef itk::MinimumMaximumImageFilter<TLabelImageType> MinMaxType;
    typename MinMaxType::Pointer rangeFinderFilter=MinMaxType::New();
    rangeFinderFilter->SetInput(labelImage);
    rangeFinderFilter->Update();

    for( typename TLabelImageType::PixelType rangeIt=rangeFinderFilter->GetMinimum();
      rangeIt <= rangeFinderFilter->GetMaximum();
      ++rangeIt)
      {
      if( filter->HasLabel( rangeIt ) )
        {
        this->m_Minimum[rangeIt]  = filter->GetMinimum(rangeIt);
        this->m_Maximum[rangeIt]  = filter->GetMaximum(rangeIt);
        this->m_Mean[rangeIt]     = filter->GetMean(rangeIt);
        this->m_Variance[rangeIt] = filter->GetVariance(rangeIt);
        }
      }
    }
  //NOTE:  Input is passed through to output.
  return Image( filter->GetOutput() );
  }

} // end namespace simple
} // end namespace itk
