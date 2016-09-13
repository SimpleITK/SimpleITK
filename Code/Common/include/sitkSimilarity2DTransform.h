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
#ifndef sitkSimilarity2DTransform_h
#define sitkSimilarity2DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \brief A similarity 2D transform with rotation in radians and
 * isotropic scaling around a fixed center with translation.
 *
 * \sa itk::Similarity2DTransform
 */
class SITKCommon_EXPORT Similarity2DTransform
  : public Transform
{
public:
  typedef Similarity2DTransform Self;
  typedef Transform Superclass;

// construct identity
  Similarity2DTransform();

  explicit Similarity2DTransform( double scaleFactor,
                                  double angle=0.0,
                                  const std::vector<double> &translation = std::vector<double>(2,0.0),
                                  const std::vector< double > &fixedCenter = std::vector<double>(2,0.0) );

  Similarity2DTransform( const Similarity2DTransform & );

  explicit Similarity2DTransform( const Transform & );

  Similarity2DTransform &operator=( const Similarity2DTransform & );

  /** Name of this class */
  std::string GetName() const { return std::string ("Similarity2DTransform"); }

/** fixed parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;

/** parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetAngle (double angle);
  double GetAngle () const;

  std::vector<double> GetTranslation( ) const;
  SITK_RETURN_SELF_TYPE_HEADER SetTranslation(const std::vector<double>& translation);

  SITK_RETURN_SELF_TYPE_HEADER SetScale(double scale);
  double GetScale() const;

  /** additional methods */
  std::vector<double> GetMatrix() const;
  SITK_RETURN_SELF_TYPE_HEADER SetMatrix(const std::vector<double> &matrix, double tolerance = 1e-10);

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);

  nsstd::function<void(const std::vector<double>&)> m_pfSetCenter;
  nsstd::function<std::vector<double>()> m_pfGetCenter;
  nsstd::function<void(double)> m_pfSetAngle;
  nsstd::function<double()> m_pfGetAngle;
  nsstd::function<void(const std::vector<double>&)> m_pfSetTranslation;
  nsstd::function<std::vector<double>()> m_pfGetTranslation;
  nsstd::function<void(double)> m_pfSetScale;
  nsstd::function<double()> m_pfGetScale;
  nsstd::function<std::vector<double>()> m_pfGetMatrix;
  nsstd::function<void(const std::vector<double>&, double)> m_pfSetMatrix;
};

}
}

#endif // sitkSimilarity2DTransform_h
