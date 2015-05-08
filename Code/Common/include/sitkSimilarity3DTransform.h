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
#ifndef __sitkSimilarity3DTransform_h
#define __sitkSimilarity3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \brief A similarity 3D transform with rotation as a versor, and
 * isotropic scaling around a fixed center with translation.
 *
 * \sa itk::Similarity3DTransform
 */
class SITKCommon_EXPORT Similarity3DTransform
  : public Transform
{
public:
typedef Similarity3DTransform Self;
typedef Transform Superclass;

// construct identity
Similarity3DTransform();

Similarity3DTransform( const Similarity3DTransform & );

explicit Similarity3DTransform( const Transform & );

Similarity3DTransform( double scaleFactor, const std::vector< double > &versor,
                       const std::vector< double > &translation=std::vector< double >(3, 0.0),
                       const std::vector< double > &fixedCenter=std::vector< double >(3, 0.0) );

Similarity3DTransform( double scaleFactor, const std::vector< double > &axis, double angle,
                       const std::vector< double > &translation=std::vector< double >(3, 0.0),
                       const std::vector< double > &fixedCenter=std::vector< double >(3, 0.0) );

Similarity3DTransform &operator=( const Similarity3DTransform & );

/** Name of this class */
std::string GetName() const { return std::string ("Similarity3DTransform"); }

/** fixed parameter */
Self &SetCenter(const std::vector<double> &params);
std::vector<double> GetCenter( ) const;


/** parameter */
Self &SetRotation(const std::vector<double> &versor);
Self &SetRotation(const std::vector<double> &axis,  double angle);
std::vector<double> GetVersor() const;

Self &SetScale(double scale);
double GetScale() const;

std::vector<double> GetTranslation( ) const;
Self &SetTranslation(const std::vector<double>& translation);


/** additional methods */
Self &Translate(const std::vector<double> &offset);
std::vector<double> GetMatrix() const;
Self &SetMatrix(const std::vector<double> &matrix, double tolerance = 1e-10);

protected:

virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

using Superclass::AddTransform;

void InternalInitialization(itk::TransformBase *transform);

template <typename TransformType>
void InternalInitialization(TransformType *transform);

nsstd::function<void(const std::vector<double>&)> m_pfSetCenter;
nsstd::function<std::vector<double>()> m_pfGetCenter;
nsstd::function<void(const std::vector<double>&)> m_pfSetRotation1;
nsstd::function<void(const std::vector<double>,double&)> m_pfSetRotation2;
nsstd::function<std::vector<double>()> m_pfGetVersor;
nsstd::function<void(double)> m_pfSetScale;
nsstd::function<double()> m_pfGetScale;
nsstd::function<void(const std::vector<double>&)> m_pfSetTranslation;
nsstd::function<std::vector<double>()> m_pfGetTranslation;
nsstd::function<void(const std::vector<double> &)> m_pfTranslate;
nsstd::function<std::vector<double>()> m_pfGetMatrix;
nsstd::function<void(const std::vector<double>&, double)> m_pfSetMatrix;
};

}
}

#endif // __sitkSimilarity3DTransform_h
