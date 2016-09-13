/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#ifndef sitkBSplineTransform_h
#define sitkBSplineTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \brief A deformable transform over a bounded spatial domain using a BSpline
 * representation for a 2D or 3D coordinate space.
 *
 * \sa itk::BSplineTransform
 */
class SITKCommon_EXPORT BSplineTransform
  : public Transform
{
public:
  typedef BSplineTransform Self;
  typedef Transform Superclass;

  explicit BSplineTransform(unsigned int dimensions, unsigned int order=3);

  BSplineTransform( const BSplineTransform & );

  explicit BSplineTransform( const Transform &);

  BSplineTransform &operator=( const BSplineTransform & );

  /** Name of this class */
  std::string GetName() const { return std::string ("BSplineTransform"); }

  /** parameters */

  /** fixed parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetTransformDomainDirection(const std::vector<double> &);
  std::vector<double>  GetTransformDomainDirection() const;
  SITK_RETURN_SELF_TYPE_HEADER SetTransformDomainMeshSize(const std::vector<unsigned int>&);
  std::vector<unsigned int> GetTransformDomainMeshSize() const;
  SITK_RETURN_SELF_TYPE_HEADER SetTransformDomainOrigin(const std::vector<double>&);
  std::vector<double> GetTransformDomainOrigin() const;
  SITK_RETURN_SELF_TYPE_HEADER SetTransformDomainPhysicalDimensions(const std::vector<double> &);
  std::vector<double> GetTransformDomainPhysicalDimensions() const;

  /* additional methods */

  /** \brief Get a vector of the coefficient images representing the BSpline
   *
   * A lazy shallow copy of the images from ITK are performed. If they
   * are modified in SimpleITK a deep copy will occur. However, if
   * the coefficients are modified in ITK, then no copy will occur and
   * the images help by SimpleITK may change.
   */
  std::vector<Image> GetCoefficientImages () const;

  unsigned int GetOrder() const;

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    BSplineTransform *that;
    template< typename TransformType >
    void operator() ( void ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t && (typeid(*t)==typeid(TransformType)))
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);

  static PimpleTransformBase *CreateBSplinePimpleTransform(unsigned int dimension, unsigned int order);

  template <unsigned int ND>
    static PimpleTransformBase *CreateBSplinePimpleTransform(unsigned int order);

  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainDirection;
  nsstd::function<void (const std::vector<double> &)> m_pfSetTransformDomainDirection;
  nsstd::function<std::vector<unsigned int> ()> m_pfGetTransformDomainMeshSize;
  nsstd::function<void (const std::vector<unsigned int>&)> m_pfSetTransformDomainMeshSize;
  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainOrigin;
  nsstd::function<void (const std::vector<double>&)> m_pfSetTransformDomainOrigin;
  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainPhysicalDimensions;
  nsstd::function<void (const std::vector<double> &)> m_pfSetTransformDomainPhysicalDimensions;

  nsstd::function<std::vector<Image> ()> m_pfGetCoefficientImages;
  nsstd::function< unsigned int()> m_pfGetOrder;

};

}
}

#endif // sitkBSplineTransform_h
