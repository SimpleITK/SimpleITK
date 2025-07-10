/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitkLandmarkBasedTransformInitializerFilter_h
#define sitkLandmarkBasedTransformInitializerFilter_h

#include <memory>

#include "sitkBasicFilters.h"
#include "sitkImageFilter.h"

namespace itk::simple
{

/**\class LandmarkBasedTransformInitializerFilter


This class computes the transform that aligns the fixed and moving
images given a set of pair landmarks. The class is templated over the
Transform type as well as fixed image and moving image types. The
transform computed gives the best fit transform that maps the fixed
and moving images in a least squares sense. The indices are taken to
correspond, so point 1 in the first set will get mapped close to point
1 in the second set, etc.

Currently, the following transforms are supported by the class:
- VersorRigid3DTransform
- Similarity3DTransform
- Rigid2DTransform
- AffineTransform
- BSplineTransform

An equal number of fixed and moving landmarks need to be specified
using SetFixedLandmarks() and SetMovingLandmarks() . Any number of
landmarks may be specified. In the case of using Affine or BSpline
transforms, each landmark pair can contribute in the final transform
based on its defined weight. Number of weights should be equal to the
number of landmarks and can be specified using SetLandmarkWeight()
. By defaults are weights are set to one. Call InitializeTransform()
to initialize the transform.

The class is based in part on Hybrid/vtkLandmarkTransform originally implemented in python by David G. Gobbi.

The solution is based on Berthold K. P. Horn (1987), "Closed-form solution of absolute orientation
using unit quaternions," http://people.csail.mit.edu/bkph/papers/Absolute_Orientation.pdf

The Affine Transform initializer is based on an algorithm by H Spaeth, and is described in the Insight Journal Article
"Affine Transformation for Landmark Based Registration Initializer in ITK" by Kim E.Y., Johnson H., Williams N.
available at https://www.midasjournal.org/browse/publication/825

\par Wiki Examples:

\li All Examples

\li Rigidly register one image to another using manually specified landmarks
\sa itk::simple::LandmarkBasedTransformInitializerFilter for the procedural interface
\sa itk::LandmarkBasedTransformInitializer for the Doxygen on the original ITK class.
 */
class SITKBasicFilters_EXPORT LandmarkBasedTransformInitializerFilter : public ImageFilter
{
public:
  using Self = LandmarkBasedTransformInitializerFilter;

  /** Destructor */
  ~LandmarkBasedTransformInitializerFilter() override;


  /** Default Constructor that takes no arguments and initializes
   * default parameters */
  LandmarkBasedTransformInitializerFilter();

  /** Define the pixels types supported by this filter */
  using PixelIDTypeList = typelist2::typelist<BasicPixelID<float>>;


  /**
   * Set the Fixed landmark point containers
   */
  void
  SetFixedLandmarks(const std::vector<double> & FixedLandmarks)
  {
    this->m_FixedLandmarks = FixedLandmarks;
  }

  /**
   *
   */
  std::vector<double>
  GetFixedLandmarks() const
  {
    return this->m_FixedLandmarks;
  }

  /**
   * Set the Moving landmark point containers
   */
  void
  SetMovingLandmarks(const std::vector<double> & MovingLandmarks)
  {
    this->m_MovingLandmarks = MovingLandmarks;
  }

  /**
   * Get the shrink factors.
   */
  std::vector<double>
  GetMovingLandmarks() const
  {
    return this->m_MovingLandmarks;
  }

  /**
   * Set the landmark weight point containers Weight includes diagonal elements of weight matrix
   */
  void
  SetLandmarkWeight(const std::vector<double> & LandmarkWeight)
  {
    this->m_LandmarkWeight = LandmarkWeight;
  }

  /**
   *
   */
  std::vector<double>
  GetLandmarkWeight() const
  {
    return this->m_LandmarkWeight;
  }

  /**
   * Set the reference image to define the parametric domain for the BSpline transform
   */
  void
  SetReferenceImage(const Image & ReferenceImage)
  {
    this->m_ReferenceImage = ReferenceImage;
  }

  /**
   */
  Image
  GetReferenceImage() const
  {
    return this->m_ReferenceImage;
  }

  /**
   * Set/Get the number of control points
   */
  void
  SetBSplineNumberOfControlPoints(unsigned int BSplineNumberOfControlPoints)
  {
    this->m_BSplineNumberOfControlPoints = BSplineNumberOfControlPoints;
  }

  /**
   * Set/Get the number of control points
   */
  unsigned int
  GetBSplineNumberOfControlPoints() const
  {
    return this->m_BSplineNumberOfControlPoints;
  }
  /** Name of this class */
  std::string
  GetName() const override
  {
    return std::string("LandmarkBasedTransformInitializerFilter");
  }

  /** Print ourselves out */
  std::string
  ToString() const override;


  /** Execute the filter on the input image */
  Transform
  Execute(const Transform & transform);


private:
  /** Setup for member function dispatching */

  typedef Transform (Self::*MemberFunctionType)(const Transform * transform);
  template <class TImageType>
  Transform
  ExecuteInternal(const Transform * transform);


  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

  detail::MemberFunctionFactory<MemberFunctionType> m_MemberFactory;


  /*  */
  std::vector<double> m_FixedLandmarks;
  /*  */
  std::vector<double> m_MovingLandmarks;
  /*  */
  std::vector<double> m_LandmarkWeight;

  Image        m_ReferenceImage;
  unsigned int m_BSplineNumberOfControlPoints;
};


/**
 * \brief itk::simple::LandmarkBasedTransformInitializerFilter Procedural Interface
 *
 * This function directly calls the execute method of LandmarkBasedTransformInitializerFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::LandmarkBasedTransformInitializerFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT Transform
LandmarkBasedTransformInitializer(const Transform &           transform,
                                  const std::vector<double> & fixedLandmarks = std::vector<double>(),
                                  const std::vector<double> & movingLandmarks = std::vector<double>(),
                                  const std::vector<double> & landmarkWeight = std::vector<double>(),
                                  const Image &               referenceImage = Image(),
                                  unsigned int                numberOfControlPoints = 4u);

} // namespace itk::simple
#endif
