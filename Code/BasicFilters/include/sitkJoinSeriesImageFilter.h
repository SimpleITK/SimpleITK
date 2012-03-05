#ifndef __sitkJoinSeriesImageFilter_h
#define __sitkJoinSeriesImageFilter_h

#include "sitkImageFilter.h"
#include "sitkPixelIDTokens.h"
#include "sitkDualMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

/** \class JoinSeriesImageFilter
 *  Coverts a list of 2D images into a 3D volume
 *
 * This filter is templated over the input image type and the output image
 * type. The pixel type of them must be the same and the input dimension
 * must be less than the output dimension.
 * When the input images are N-dimensinal, they are joined in order and
 * the size of the N+1'th dimension of the output is same as the number of
 * the inputs. The spacing and the origin (where the first input is placed)
 * for the N+1'th dimension is specified in this filter. The output image
 * informations for the first N dimensions are taken from the first input.
 * Note that all the inputs should have the same information.
 *
 * \ingroup GeometricTransform
 * \ingroup MultiThreaded
 * \ingroup Streamed
 *
 * \author Hideaki Hiraki
 *
 * Contributed in the users list
 * http://public.kitware.com/pipermail/insight-users/2004-February/006542.html
 */
class SITKBasicFilters_EXPORT JoinSeriesImageFilter
  : public ImageFilter
{
public:
  typedef JoinSeriesImageFilter      Self;

  /**
   * Default Constructor that takes no arguments and initializes
   * default parameters
    */
  JoinSeriesImageFilter();

  /** Define the pixels types supported by this filter */
  typedef IntegerPixelIDTypeList  PixelIDTypeList;


  /** Name of this class */
  std::string GetName() const { return std::string ( "JoinSeries"); }

  // See super class for doxygen
  std::string ToString() const;

  // See super class for doxygen
  Image Execute ( const std::vector<Image> & );
  Image Execute ( const Image &image );

  /** Set/Get spacing of the new dimension */
  Self & SetSpacing( double spacing ) { this->m_Spacing = spacing; return *this; }
  double GetSpacing( void ) const { return this->m_Spacing; }

  /** Set/Get origin of the new dimension */
  Self & SetOrigin( double spacing ) { this->m_Origin = spacing; return *this; }
  double GetOrigin( void ) const { return this->m_Origin; }


private:


  /** Setup for member function dispatching */
  typedef Image (Self::*MemberFunctionType)( const std::vector<Image> & );
  template <class TImageType> Image ExecuteInternal ( const std::vector<Image>& images );


  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
  std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


  double m_Spacing;
  double m_Origin;

};

Image SITKBasicFilters_EXPORT JoinSeries ( const std::vector<Image>& images, double inSpacing = 1.0, double inOrigin = 0.0 );

}
}
#endif
