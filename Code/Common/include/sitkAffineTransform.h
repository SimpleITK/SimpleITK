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
#ifndef __sitkAffineTransform_h
#define __sitkAffineTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \brief An affine transformation about a fixed center with
 * translation for a 2D or 3D coordinate.
 *
 * \sa itk::AffineTransform
 */
class SITKCommon_EXPORT AffineTransform
  : public Transform
{
public:
  typedef AffineTransform Self;
  typedef Transform Superclass;
  explicit AffineTransform(unsigned int dimensions);

  AffineTransform( const AffineTransform & );

  explicit AffineTransform( const Transform & );

  AffineTransform( const std::vector< double> &matrix,
                   const std::vector< double> &translation,
                   const std::vector< double> &fixedCenter=std::vector< double >(3, 0.0));


  AffineTransform &operator=( const AffineTransform & );

  /** Name of this class */
  std::string GetName() const { return std::string ("AffineTransform"); }

  /** parameters */
  std::vector<double> GetTranslation( ) const;
  Self &SetTranslation( const std::vector<double>& translation);

  Self &SetMatrix( const std::vector<double> &matrix);
  std::vector<double> GetMatrix() const;

  /** fixed parameter */
  Self &SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;

  /** additional methods */
  Self &Scale(const std::vector<double> & factor, bool pre=false);
  Self &Scale(double factor, bool pre=false);

  Self &Shear(int axis1, int axis2, double coef, bool pre=false);

  Self &Translate(const std::vector<double> &offset, bool pre=false);

  Self &Rotate(int axis1, int axis2, double angle, bool pre=false);

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    AffineTransform *that;
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


  nsstd::function<void(const std::vector<double>&)> m_pfSetCenter;
  nsstd::function<std::vector<double>()> m_pfGetCenter;
  nsstd::function<void(const std::vector<double>&)> m_pfSetMatrix;
  nsstd::function<std::vector<double>()> m_pfGetMatrix;
  nsstd::function<void(const std::vector<double>&)> m_pfSetTranslation;
  nsstd::function<std::vector<double>()> m_pfGetTranslation;

  nsstd::function<void(const std::vector<double> &, bool)> m_pfScale1;
  nsstd::function<void(double, bool)> m_pfScale2;
  nsstd::function<void(int, int, double, bool)> m_pfShear;
  nsstd::function<void(const std::vector<double> &, bool)> m_pfTranslate;
  nsstd::function<void(int, int, double, bool)> m_pfRotate;

};

}
}

#endif // __sitkAffineTransform_h
