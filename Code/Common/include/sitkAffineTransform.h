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
#ifndef sitkAffineTransform_h
#define sitkAffineTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \class AffineTransform
 * \brief An affine transformation about a fixed center with
 * translation for a 2D or 3D coordinate.
 *
 * \sa itk::AffineTransform
 */
class SITKCommon_EXPORT AffineTransform
  : public Transform
{
public:
  using Self = AffineTransform;
  using Superclass = Transform;

  ~AffineTransform() override;

  explicit AffineTransform(unsigned int dimensions);

  AffineTransform( const AffineTransform & );

  explicit AffineTransform( const Transform & );

  AffineTransform( const std::vector< double> &matrix,
                   const std::vector< double> &translation,
                   const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0));


  AffineTransform &operator=( const AffineTransform & );

  /** Name of this class */
  std::string GetName() const override { return std::string ("AffineTransform"); }

  /** parameters */
  std::vector<double> GetTranslation( ) const;
  SITK_RETURN_SELF_TYPE_HEADER SetTranslation( const std::vector<double>& translation);

  SITK_RETURN_SELF_TYPE_HEADER SetMatrix( const std::vector<double> &matrix);
  std::vector<double> GetMatrix() const;

  /** fixed parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;

  /** additional methods */
  SITK_RETURN_SELF_TYPE_HEADER Scale(const std::vector<double> & factor, bool pre=false);
  SITK_RETURN_SELF_TYPE_HEADER Scale(double factor, bool pre=false);

  SITK_RETURN_SELF_TYPE_HEADER Shear(int axis1, int axis2, double coef, bool pre=false);

  SITK_RETURN_SELF_TYPE_HEADER Translate(const std::vector<double> &offset, bool pre=false);

  SITK_RETURN_SELF_TYPE_HEADER Rotate(int axis1, int axis2, double angle, bool pre=false);

protected:

  void SetPimpleTransform( PimpleTransformBase *pimpleTransform ) override;

private:

  struct MyVisitor
  {
    itk::TransformBase *transform;
    AffineTransform *that;
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


  std::function<void(const std::vector<double>&)> m_pfSetCenter;
  std::function<std::vector<double>()> m_pfGetCenter;
  std::function<void(const std::vector<double>&)> m_pfSetMatrix;
  std::function<std::vector<double>()> m_pfGetMatrix;
  std::function<void(const std::vector<double>&)> m_pfSetTranslation;
  std::function<std::vector<double>()> m_pfGetTranslation;

  std::function<void(const std::vector<double> &, bool)> m_pfScale1;
  std::function<void(double, bool)> m_pfScale2;
  std::function<void(int, int, double, bool)> m_pfShear;
  std::function<void(const std::vector<double> &, bool)> m_pfTranslate;
  std::function<void(int, int, double, bool)> m_pfRotate;

};

}
}

#endif // sitkAffineTransform_h
