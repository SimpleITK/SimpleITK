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
#ifndef sitkComposeScaleSkewVersor3DTransform_h
#define sitkComposeScaleSkewVersor3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \class ComposeScaleSkewVersor3DTransform
 *  \brief This transform applies a versor rotation and translation & scale/skew
 *  to the space.
 *
 * The transform can be described as:
 *  \f$ (\textbf{R}_v * \textbf{S} * \textbf{K})\textbf{x}  \f$
 *  where \f$\textbf{R}_v\f$ is the rotation matrix given the versor,
 *  where \f$\textbf{S}\f$ is the diagonal scale matrix.
 *  where \f$\textbf{K}\f$ is the upper triangle skew (shear) matrix.
 *
 * \sa itk::ComposeScaleSkewVersor3DTransform
 */
class SITKCommon_EXPORT ComposeScaleSkewVersor3DTransform
  : public Transform
{
public:
  using Self = ComposeScaleSkewVersor3DTransform;
  using Superclass = Transform;

  ~ComposeScaleSkewVersor3DTransform() override;

  // construct identity
  ComposeScaleSkewVersor3DTransform();

  ComposeScaleSkewVersor3DTransform( const ComposeScaleSkewVersor3DTransform & );

  explicit ComposeScaleSkewVersor3DTransform( const Transform & );

  ComposeScaleSkewVersor3DTransform( const std::vector< double > &scale,
                                     const std::vector< double> &skew,
                                     const std::vector< double > &versor,
                                     const std::vector< double > &translation=std::vector< double >(3, 0.0),
                                     const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0) );

  ComposeScaleSkewVersor3DTransform( const std::vector< double > &scale,
                                     const std::vector< double> &skew,
                                     const std::vector< double > &axis, double angle,
                                     const std::vector< double > &translation=std::vector< double >(3, 0.0),
                                     const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0) );

  ComposeScaleSkewVersor3DTransform &operator=( const ComposeScaleSkewVersor3DTransform & );

  /** Name of this class */
  std::string GetName() const override { return std::string ("ComposeScaleSkewVersor3DTransform"); }

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

#endif // sitkComposeScaleSkewVersor3DTransform_h
