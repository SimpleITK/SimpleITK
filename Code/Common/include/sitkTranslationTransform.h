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
#ifndef sitkTranslationTransform_h
#define sitkTranslationTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{


/** \brief Translation of a 2D or 3D coordinate space.
 *
 * \sa itk::TranslationTransform
 */
class SITKCommon_EXPORT TranslationTransform
  : public Transform
{
public:
typedef TranslationTransform Self;
typedef Transform Superclass;

explicit TranslationTransform(unsigned int dimensions,
                              const std::vector<double> &offset = std::vector<double>(3,0.0) );

TranslationTransform( const TranslationTransform & );

TranslationTransform( const Transform & );

TranslationTransform &operator=( const TranslationTransform & );

SITK_RETURN_SELF_TYPE_HEADER SetOffset(const std::vector<double> &params);
std::vector<double> GetOffset( ) const;

protected:

virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

using Superclass::AddTransform;

struct MyVisitor
{
  itk::TransformBase *transform;
  TranslationTransform *that;
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

nsstd::function<void(const std::vector<double> &)> m_pfSetOffset;
nsstd::function<std::vector<double>()> m_pfGetOffset;

};

}
}

#endif // sitkTranslationTransform_h
