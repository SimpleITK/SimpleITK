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
#ifndef sitkScaleSkewVersor3DTransform_h
#define sitkScaleSkewVersor3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \class ScaleSkewVersor3DTransform
 *  \brief A over parameterized 3D Affine transform composed of the
 * addition of a versor rotation matrix, a scale matrix and a skew
 * matrix around a fixed center with translation.
 *
 * \sa itk::ScaleSkewVersor3DTransform
 */
class SITKCommon_EXPORT ScaleSkewVersor3DTransform
  : public Transform
{
public:
  using Self = ScaleSkewVersor3DTransform;
  using Superclass = Transform;

  ~ScaleSkewVersor3DTransform() override;

  // construct identity
  ScaleSkewVersor3DTransform();

  ScaleSkewVersor3DTransform( const ScaleSkewVersor3DTransform & );

  explicit ScaleSkewVersor3DTransform( const Transform & );

  ScaleSkewVersor3DTransform( const std::vector< double > &scale,
                              const std::vector< double> &skew,
                              const std::vector< double > &versor,
                              const std::vector< double > &translation=std::vector< double >(3, 0.0),
                              const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0) );

  ScaleSkewVersor3DTransform( const std::vector< double > &scale,
                              const std::vector< double> &skew,
                              const std::vector< double > &axis, double angle,
                              const std::vector< double > &translation=std::vector< double >(3, 0.0),
                              const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0) );

  ScaleSkewVersor3DTransform &operator=( const ScaleSkewVersor3DTransform & );

  /** Name of this class */
  std::string GetName() const override { return std::string ("ScaleSkewVersor3DTransform"); }

/** fixed parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;


/** parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetRotation(const std::vector<double> &versor);
  SITK_RETURN_SELF_TYPE_HEADER SetRotation(const std::vector<double> &axis,  double angle);
  std::vector<double> GetVersor() const;

  std::vector<double> GetTranslation( ) const;
  SITK_RETURN_SELF_TYPE_HEADER SetTranslation(const std::vector<double>& translation);

  std::vector<double> GetScale( ) const;
  SITK_RETURN_SELF_TYPE_HEADER SetScale( const std::vector<double> & scale );

  std::vector<double> GetSkew( ) const;
  SITK_RETURN_SELF_TYPE_HEADER SetSkew( const std::vector<double> & skew );

/** additional methods */
  SITK_RETURN_SELF_TYPE_HEADER Translate(const std::vector<double> &offset);
  std::vector<double> GetMatrix() const;

protected:

  void SetPimpleTransform( PimpleTransformBase *pimpleTransform ) override;

private:

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);


  std::function<void(const std::vector<double>&)> m_pfSetCenter;
  std::function<std::vector<double>()> m_pfGetCenter;
  std::function<void(const std::vector<double>&)> m_pfSetRotation1;
  std::function<void(const std::vector<double>&,double)> m_pfSetRotation2;
  std::function<std::vector<double>()> m_pfGetVersor;
  std::function<void(const std::vector<double>&)> m_pfSetTranslation;
  std::function<std::vector<double>()> m_pfGetTranslation;
  std::function<void(const std::vector<double>&)> m_pfSetScale;
  std::function<std::vector<double>()> m_pfGetScale;
  std::function<void(const std::vector<double>&)> m_pfSetSkew;
  std::function<std::vector<double>()> m_pfGetSkew;
  std::function<void(const std::vector<double> &)> m_pfTranslate;
  std::function<std::vector<double>()> m_pfGetMatrix;
};

}
}

#endif // sitkVersorTransform_h
