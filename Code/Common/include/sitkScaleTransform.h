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
#ifndef sitkScaleTransform_h
#define sitkScaleTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \brief A 2D or 3D anisotropic scale of coordinate space around
 * a fixed center.
 *
 * \sa itk::ScaleTransform
 */
class SITKCommon_EXPORT ScaleTransform
  : public Transform
{
public:
  typedef ScaleTransform Self;
  typedef Transform Superclass;

  explicit ScaleTransform(unsigned int dimensions,
                          const std::vector<double> &scale = std::vector<double>(3,1.0) );

  ScaleTransform( const ScaleTransform & );

  explicit ScaleTransform( const Transform & );

  /** Name of this class */
  std::string GetName() const { return std::string ("ScaleTransform"); }

  ScaleTransform &operator=( const ScaleTransform & );


  SITK_RETURN_SELF_TYPE_HEADER SetScale(const std::vector<double> &params);
  std::vector<double> GetScale( ) const;

  /** fixed parameter */
  SITK_RETURN_SELF_TYPE_HEADER SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;

  /** additional methods */
  std::vector<double> GetMatrix() const;

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    ScaleTransform *that;
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


  nsstd::function<void(std::vector<double>)> m_pfSetCenter;
  nsstd::function<std::vector<double>()> m_pfGetCenter;
  nsstd::function<void(std::vector<double>)> m_pfSetScale;
  nsstd::function<std::vector<double>()> m_pfGetScale;
  nsstd::function<std::vector<double>()> m_pfGetMatrix;


};

}
}

#endif // sitkScaleTransform_h
