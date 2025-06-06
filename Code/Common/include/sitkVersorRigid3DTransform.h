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
#ifndef sitkVersorRigid3DTransform_h
#define sitkVersorRigid3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk::simple
{


/** \class VersorRigid3DTransform
 * \brief A rotation as a versor around a fixed center with
 * translation of a 3D coordinate space.
 *
 * \sa itk::VersorRigid3DTransform
 */
class SITKCommon_EXPORT VersorRigid3DTransform : public Transform
{
public:
  using Self = VersorRigid3DTransform;
  using Superclass = Transform;

  ~VersorRigid3DTransform() override;

  // construct identity
  VersorRigid3DTransform();

  VersorRigid3DTransform(const VersorRigid3DTransform &);

  explicit VersorRigid3DTransform(const Transform &);

  explicit VersorRigid3DTransform(const std::vector<double> & versor,
                                  const std::vector<double> & translation = std::vector<double>(3, 0.0),
                                  const std::vector<double> & fixedCenter = std::vector<double>(3, 0.0));

  VersorRigid3DTransform(const std::vector<double> & axis,
                         double                      angle,
                         const std::vector<double> & translation = std::vector<double>(3, 0.0),
                         const std::vector<double> & fixedCenter = std::vector<double>(3, 0.0));

  VersorRigid3DTransform &
  operator=(const VersorRigid3DTransform &);

  /** Name of this class */
  std::string
  GetName() const override
  {
    return std::string("VersorRigid3DTransform");
  }

  /** fixed parameter */
  void
  SetCenter(const std::vector<double> & params);
  std::vector<double>
  GetCenter() const;


  /** parameter */
  void
  SetRotation(const std::vector<double> & versor);
  void
  SetRotation(const std::vector<double> & axis, double angle);
  std::vector<double>
  GetVersor() const;

  std::vector<double>
  GetTranslation() const;
  void
  SetTranslation(const std::vector<double> & translation);

  /** additional methods */
  void
  Translate(const std::vector<double> & offset);
  std::vector<double>
  GetMatrix() const;
  void
  SetMatrix(const std::vector<double> & matrix, double tolerance = 1e-10);

protected:
  void
  SetPimpleTransform(std::unique_ptr<PimpleTransformBase> && pimpleTransform) override;

private:
  void
  InternalInitialization(itk::TransformBase * transform);

  template <typename TransformType>
  void
  InternalInitialization(TransformType * transform);


  std::function<void(const std::vector<double> &)>         m_pfSetCenter;
  std::function<std::vector<double>()>                     m_pfGetCenter;
  std::function<void(const std::vector<double> &)>         m_pfSetRotation1;
  std::function<void(const std::vector<double> &, double)> m_pfSetRotation2;
  std::function<std::vector<double>()>                     m_pfGetVersor;
  std::function<void(const std::vector<double> &)>         m_pfSetTranslation;
  std::function<std::vector<double>()>                     m_pfGetTranslation;
  std::function<void(const std::vector<double> &)>         m_pfTranslate;
  std::function<std::vector<double>()>                     m_pfGetMatrix;
  std::function<void(const std::vector<double> &, double)> m_pfSetMatrix;
};

} // namespace itk::simple

#endif // sitkVersorTransform_h
