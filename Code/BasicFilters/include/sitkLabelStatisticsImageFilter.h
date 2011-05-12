#ifndef __sitkLabelStatisticsImageFilter_h
#define __sitkLabelStatisticsImageFilter_h

#include "sitkImageFilter.h"
#include "sitkDualMemberFunctionFactory.h"

#include <map>


namespace itk {
  namespace simple {

    /** \class LabelStatisticsImageFilter
     * \brief Compute min, max, variance, and mean of an image
     */
    class LabelStatisticsImageFilter : public ImageFilter {
    public:
      typedef LabelStatisticsImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      LabelStatisticsImageFilter();

      typedef BasicPixelIDTypeList PixelIDTypeList;
      typedef IntegerPixelIDTypeList LabelPixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ( "LabelStatistics"); }

      // Print ourselves out
      std::string ToString() const;

      //HACK:  NOTE:  size_t should be based on largest integer type available in IntegerPixelIDTypeList
      //
      Image Execute ( const Image & , const Image & );
    private:

      typedef Image (Self::*MemberFunctionType)( const Image&, const Image& );
      template <class TImageType, class TLabelImageType> Image DualExecuteInternal ( const Image& image, const Image& labels );

      friend struct detail::DualExecuteInternalAddressor<MemberFunctionType>;
      std::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;

      std::map<size_t, double> m_Minimum;
      std::map<size_t, double> m_Maximum;
      std::map<size_t, double> m_Mean;
      std::map<size_t, double> m_Variance;
      std::map<size_t, bool>   m_HasLabel;

    public:
      double GetMinimum ( const size_t labelCode ) { return this->m_Minimum[labelCode]; }
      double GetMaximum ( const size_t labelCode ) { return this->m_Maximum[labelCode]; }
      double GetMean    ( const size_t labelCode ) { return this->m_Mean[labelCode]; }
      double GetVariance( const size_t labelCode ) { return this->m_Variance[labelCode]; }
      bool   HasLabel   ( const size_t labelCode ) { return ( this->m_HasLabel.find(labelCode) != this->m_HasLabel.end() ) ; }

    };


  }
}
#endif
