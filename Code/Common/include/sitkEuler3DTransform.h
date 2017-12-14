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
#ifndef sitkEuler3DTransform_h
#define sitkEuler3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

/** \class Euler3DTransform
 * \brief A rigid 3D transform with rotation in radians around a
 * fixed center with translation.
 *
 * \sa itk::Euler3DTransform
 */
class SITKCommon_EXPORT Euler3DTransform
  : public Transform
{
public:
typedef Euler3DTransform Self;
typedef Transform        Superclass;

// construct identity
Euler3DTransform();

explicit Euler3DTransform(const std::vector<double> &fixedCenter,
                          double angleX=0.0,
                          double angleY=0.0,
                          double angleZ=0.0,
                          const std::vector<double> &translation = std::vector<double>(3,0.0) );

Euler3DTransform( const Euler3DTransform & );

explicit Euler3DTransform( const Transform & );

Euler3DTransform &operator=( const Euler3DTransform & );

/** Name of this class */
std::string GetName() const { return std::string ("Euler3DTransform"); }

/** fixed parameter */
SITK_RETURN_SELF_TYPE_HEADER SetCenter(const std::vector<double> &params);
std::vector<double> GetCenter( ) const;

double GetAngleX () const;
double GetAngleY () const;
double GetAngleZ () const;

/** parameter */
SITK_RETURN_SELF_TYPE_HEADER SetRotation (double angleX, double angleY, double angleZ);

std::vector<double> GetTranslation( ) const;
SITK_RETURN_SELF_TYPE_HEADER SetTranslation( const std::vector<double>& translation);

SITK_RETURN_SELF_TYPE_HEADER SetComputeZYX (bool _arg);
bool GetComputeZYX () const;
SITK_RETURN_SELF_TYPE_HEADER ComputeZYXOn () {return this->SetComputeZYX(true);}
SITK_RETURN_SELF_TYPE_HEADER ComputeZYXOff () {return this->SetComputeZYX(false);}


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
nsstd::function<void(double,double,double)> m_pfSetRotation;
nsstd::function<double()> m_pfGetAngleX;
nsstd::function<double()> m_pfGetAngleY;
nsstd::function<double()> m_pfGetAngleZ;
nsstd::function<void(const std::vector<double>&)> m_pfSetTranslation;
nsstd::function<std::vector<double>()> m_pfGetTranslation;
nsstd::function<void(bool)> m_pfSetComputeZYX;
nsstd::function<bool()> m_pfGetComputeZYX;
nsstd::function<std::vector<double>()> m_pfGetMatrix;
nsstd::function<void(const std::vector<double>&, double)> m_pfSetMatrix;


};

}
}

#endif // sitkEuler3DTransform_h
