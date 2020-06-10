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
#ifndef sitkDisplacementFieldTransform_h
#define sitkDisplacementFieldTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"
#include "sitkInterpolator.h"

namespace itk
{
namespace simple
{

/** \class DisplacementFieldTransform
 * \brief A dense deformable transform over a bounded spatial domain
 * for 2D or 3D coordinates space.
 *
 * \sa itk::DisplacementFieldTransform
 */
class SITKCommon_EXPORT DisplacementFieldTransform
  : public Transform
{
public:
  using Self = DisplacementFieldTransform;
  using Superclass = Transform;

  ~DisplacementFieldTransform() override;

  explicit DisplacementFieldTransform( unsigned int dimensions );

  /** \brief Consume an image to construct a displacement field transform.
   *
   * \warning The input displacement image is transferred to the
   * constructed transform object. The input image is modified to be a
   * default constructed Image object.
   *
   * Image must be of sitkVectorFloat64 pixel type with the number of
   * components equal to the image dimension.
   *
   */
  explicit DisplacementFieldTransform( Image &);

  DisplacementFieldTransform( const DisplacementFieldTransform & );

  explicit DisplacementFieldTransform( const Transform & );

  DisplacementFieldTransform &operator=( const DisplacementFieldTransform & );

  /** Name of this class */
  std::string GetName() const override { return std::string ("DisplacementFieldTransform"); }

  /** parameters */

  /** \brief Consume an image, and set the displacement field
   *
   * \warning The ownership of the input displacement image is
   * transferred to the constructed transform object. The input image
   * is modified to be a default constructed Image object.
   *
   * Image must be of sitkVectorFloat64 pixel type with the number of
   * components equal to the image dimension.
   *
   */
  SITK_RETURN_SELF_TYPE_HEADER SetDisplacementField(Image &);

  /** \todo The returned image should not directly modify the
   * internal displacement field.
   */
  Image GetDisplacementField() const;

  /** fixed parameter */

  /* additional methods */
  SITK_RETURN_SELF_TYPE_HEADER SetInverseDisplacementField(Image &);

  /** \todo The returned image is should not directly modify the
   * internal displacement field.
   */
  Image GetInverseDisplacementField() const;

  /** Set the interpolator used between the field voxels. */
  SITK_RETURN_SELF_TYPE_HEADER SetInterpolator(InterpolatorEnum interp);
  // InterpolatorEnum GetInterpolator() const; How to do this?

  SITK_RETURN_SELF_TYPE_HEADER SetSmoothingOff();
  SITK_RETURN_SELF_TYPE_HEADER SetSmoothingGaussianOnUpdate( double varianceForUpdateField=1.75, double varianceForTotalField=0.5 );
  SITK_RETURN_SELF_TYPE_HEADER SetSmoothingBSplineOnUpdate( const std::vector<unsigned int> &numberOfControlPointsForUpdateField = std::vector<unsigned int>(3,4),
                                     const std::vector<unsigned int> &numberOfControlPointsForTotalField = std::vector<unsigned int>(3,4),
                                     bool enforceStationaryBoundary=true,
                                     unsigned int order=3 );


protected:

  void SetPimpleTransform( PimpleTransformBase *pimpleTransform ) override;

private:

  struct MyVisitor
  {
    itk::TransformBase *transform;
    DisplacementFieldTransform *that;
    template< typename TransformType >
    void operator() ( ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t && (typeid(*t) == typeid(TransformType)))
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);

  template< typename TDisplacementFieldTransform >
    static Image InternalGetDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx );
  template< typename TDisplacementFieldTransform >
    static Image InternalGetInverseDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx );

  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingOff(TDisplacementFieldTransform *itkDisplacement);
  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingGaussianOnUpdate( TDisplacementFieldTransform *itkDisplacement,
                                               double varianceForUpdateField,
                                               double varianceForTotalField );
  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingBSplineOnUpdate( TDisplacementFieldTransform *itkDisplacement,
                                              const std::vector<unsigned int> &numberOfControlPointsForUpdateField,
                                              const std::vector<unsigned int> &numberOfControlPointsForTotalField,
                                              bool enforceStationaryBoundary,
                                              unsigned int order );


  static PimpleTransformBase *CreateDisplacementFieldPimpleTransform(unsigned int dimension);

  std::function<void (Image &)> m_pfSetDisplacementField;
  std::function<Image ()> m_pfGetDisplacementField;

  std::function<void (Image &)> m_pfSetInverseDisplacementField;
  std::function<Image ()> m_pfGetInverseDisplacementField;

  std::function<void (InterpolatorEnum &)> m_pfSetInterpolator;
  std::function<InterpolatorEnum ()> m_pfGetInterpolator;

  std::function<void ()> m_pfSetSmoothingOff;
  std::function<void (double, double)> m_pfSetSmoothingGaussianOnUpdate;
  std::function<void (const std::vector<unsigned int> &,const std::vector<unsigned int>&, bool, unsigned int)> m_pfSetSmoothingBSplineOnUpdate;

};

}
}

#endif // sitkDisplacementFieldTransform_h
