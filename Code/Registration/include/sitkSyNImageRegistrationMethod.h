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
#ifndef sitkSyNImageRegistrationMethod_h
#define sitkSyNImageRegistrationMethod_h

#include "sitkRegistration.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkProcessObject.h"

#include "sitkRandomSeed.h"
#include "sitkInterpolator.h"
#include "sitkTransform.h"
#include "sitkDisplacementFieldTransform.h"

namespace itk
{

#ifndef SWIG
template <typename TFixedImage,
          typename TMovingImage,
          typename TVirtualImage,
          typename TInternalComputationValueType,
          typename TMetricTraits>
class ImageToImageMetricv4;

template <typename TFixedImageType, typename TMovingImageType, typename TVirtualImageType, typename TCoordRep>
class DefaultImageToImageMetricTraitsv4;

template <unsigned int VDimension>
class SpatialObject;

class Command;
class EventObject;
#endif


namespace simple
{

/** \brief Symmetric normalization (SyN) deformable registration.
 *
 * This class drives itk::SyNImageRegistrationMethod, the greedy SyN
 * algorithm of Avants et al. that antsRegistration runs for its
 * "SyN" transform stage. The fixed and moving images are both
 * deformed toward a virtual midpoint, each by a displacement field
 * transform with an explicit inverse. The result is a single
 * DisplacementFieldTransform mapping the fixed image domain to the
 * moving image domain, with its inverse field also set.
 *
 * The interface mirrors ImageRegistrationMethod for the metric,
 * masks, sampling, and multi-resolution pyramid. There is no
 * optimizer; the per-iteration update is a gradient step of fixed
 * size controlled by SetLearningRate, followed by Gaussian
 * regularization of the update and total fields.
 *
 * The default parameters are those of the antsRegistrationSyN.sh
 * script (ANTs): SyN[0.2,3,0], ANTS neighborhood correlation with
 * radius 2, convergence [100x70x50x20,1e-6,10], shrink factors
 * 8x4x2x1, and smoothing sigmas 3x2x1x0 in voxels.
 *
 * A linear (rigid or affine) stage should be run first with
 * ImageRegistrationMethod and passed to SetMovingInitialTransform.
 * The complete mapping is then the composite of the linear transform
 * and the returned displacement field transform.
 *
 * \sa itk::SyNImageRegistrationMethod
 * \sa ImageRegistrationMethod
 * \sa DisplacementFieldTransform
 */
class SITKRegistration_EXPORT SyNImageRegistrationMethod : public ProcessObject
{
public:
  using Self = SyNImageRegistrationMethod;
  using Superclass = ProcessObject;

  ~SyNImageRegistrationMethod() override;

  SyNImageRegistrationMethod();

  std::string
  GetName() const override
  {
    return std::string("SyNImageRegistrationMethod");
  }

  /** \brief Print the information about the object to a string. */
  std::string
  ToString() const override;

  /** \brief Set and get the interpolator used to evaluate the images.
   *
   * @{
   */
  InterpolatorEnum
  GetInterpolator() const
  {
    return this->m_Interpolator;
  }
  void
  SetInterpolator(InterpolatorEnum Interpolator)
  {
    this->m_Interpolator = Interpolator;
  }
  /** @} */

  /** \brief Set the initial displacement field transform to optimize.
   *
   * The transform must be a DisplacementFieldTransform of the same
   * dimension as the images. If its displacement field is empty, a
   * zero field on the fixed image grid is allocated when Execute is
   * called. Otherwise registration starts from that field: it seeds the
   * fixed-to-middle half of SyN and the moving-to-middle half starts at
   * zero. If no initial transform is set, an identity displacement
   * field transform on the fixed image grid is created.
   *
   * If inPlace is true, the transform object passed is the one
   * modified during registration and returned by Execute. Otherwise
   * a copy is made and the passed object is left unchanged.
   *
   * \sa itk::ImageRegistrationMethodv4::SetInitialTransform
   * @{
   */
#if !defined(SWIG) || defined(JAVASWIG) || defined(CSHARPSWIG)
  // Only wrap this method if the wrapping language is strongly typed
  void
  SetInitialTransform(const Transform & transform);
#endif
  void
  SetInitialTransform(Transform & transform, bool inPlace = true);
  Transform
  GetInitialTransform() const
  {
    return this->m_InitialTransform;
  }
  bool
  GetInitialTransformInPlace() const
  {
    return this->m_InitialTransformInPlace;
  }
  /** @} */

  /** \brief Set a fixed transform component towards the moving domain.
   *
   * This transform is applied before the displacement field
   * transform being optimized and is typically the result of a prior
   * rigid or affine stage. Its parameters are not modified.
   *
   * \sa itk::ImageRegistrationMethodv4::SetMovingInitialTransform
   * @{
   */
  void
  SetMovingInitialTransform(const Transform & transform)
  {
    this->m_MovingInitialTransform = transform;
  }
  Transform
  GetMovingInitialTransform() const
  {
    return this->m_MovingInitialTransform;
  }
  /**@}*/

  /** \brief Set a transform mapping from the virtual domain to the
   * fixed image domain.
   *
   * \sa itk::ImageRegistrationMethodv4::SetFixedInitialTransform
   * @{
   */
  void
  SetFixedInitialTransform(const Transform & transform)
  {
    this->m_FixedInitialTransform = transform;
  }
  Transform
  GetFixedInitialTransform() const
  {
    return this->m_FixedInitialTransform;
  }
  /**@}*/

  /** \brief Use normalized cross correlation over a neighborhood of
   * each voxel. This is the "CC" metric of antsRegistration and the
   * default of this class.
   *
   * \sa itk::ANTSNeighborhoodCorrelationImageToImageMetricv4
   */
  void
  SetMetricAsANTSNeighborhoodCorrelation(unsigned int radius = 2);

  /** \brief Use negative normalized cross correlation image metric.
   *
   * \sa itk::CorrelationImageToImageMetricv4
   */
  void
  SetMetricAsCorrelation();

  /** \brief Use demons image metric.
   *
   * \sa itk::DemonsImageToImageMetricv4
   */
  void
  SetMetricAsDemons(double intensityDifferenceThreshold = 0.001);

  /** \brief Use mutual information between two images.
   *
   * \sa itk::JointHistogramMutualInformationImageToImageMetricv4
   */
  void
  SetMetricAsJointHistogramMutualInformation(unsigned int numberOfHistogramBins = 20,
                                             double       varianceForJointPDFSmoothing = 1.5);

  /** \brief Use negative means squares image metric.
   *
   * \sa itk::MeanSquaresImageToImageMetricv4
   */
  void
  SetMetricAsMeanSquares();

  /** \brief Use the mutual information between two images to be
   * registered using the method of Mattes et al.
   *
   * \sa itk::MattesMutualInformationImageToImageMetricv4
   */
  void
  SetMetricAsMattesMutualInformation(unsigned int numberOfHistogramBins = 32);

  /** \brief Set an image mask to restrict the points used by the metric
   * in the fixed image space.
   *
   * The image is expected to be in the same physical space as the
   * fixed image, and is cast to UInt8 if needed.
   *
   * \sa itk::ImageToImageMetricv4::SetFixedImageMask
   */
  void
  SetMetricFixedMask(const Image & binaryMask);

  /** \brief Set an image mask to restrict the points used by the metric
   * in the moving image space.
   *
   * \sa itk::ImageToImageMetricv4::SetMovingImageMask
   */
  void
  SetMetricMovingMask(const Image & binaryMask);

  /** \brief Set percentage of pixels sampled for metric evaluation.
   *
   * The seed parameter is used to seed the pseudo-random number
   * generator used in generating the sampling set of points. If the
   * seed parameter is 0, then the wall clock is used, otherwise the
   * fixed seed is used for reproducible behavior.
   *
   * When providing multiple values the number of entries must match
   * the number of levels.
   *
   * \sa itk::ImageRegistrationMethodv4::SetMetricSamplingPercentage
   * @{
   */
  void
  SetMetricSamplingPercentage(double percentage, unsigned int seed = sitkWallClock);
  void
  SetMetricSamplingPercentagePerLevel(const std::vector<double> & percentage, unsigned int seed = sitkWallClock);
  /** @} */

  /** \brief Get the percentage of pixels used for metric evaluation. */
  const std::vector<double> &
  GetMetricSamplingPercentagePerLevel() const;

  /** \brief Sampling strategies for obtaining points.
   *
   * - NONE: use all voxels, sampled points are the voxel centers.
   * - REGULAR: sample every n-th voxel while traversing the image
   *            in scan-line order, then within each voxel randomly
   *            perturb from center.
   * - RANDOM: sample image voxels with replacement using a uniform
   *           distribution, then within each voxel randomly perturb
   *           from center.
   */
  enum MetricSamplingStrategyType
  {
    NONE,
    REGULAR,
    RANDOM
  };

  /** \brief Set sampling strategy for sample generation. The default
   * is NONE, dense sampling, as used by antsRegistration for SyN.
   *
   * \sa itk::ImageRegistrationMethodv4::SetMetricSamplingStrategy
   */
  void
  SetMetricSamplingStrategy(MetricSamplingStrategyType strategy);

  /** \brief Enable fixed image gradient computation by a filter.
   *
   * If enabled the image gradient is computed by
   * itk::GradientRecursiveGaussianImageFilter, otherwise by central
   * differences as needed. The default is off, as in antsRegistration.
   *
   * \sa itk::ImageToImageMetricv4::SetUseFixedImageGradientFilter
   * @{
   */
  void
  SetMetricUseFixedImageGradientFilter(bool);
  void
  MetricUseFixedImageGradientFilterOn()
  {
    return this->SetMetricUseFixedImageGradientFilter(true);
  }
  void
  MetricUseFixedImageGradientFilterOff()
  {
    return this->SetMetricUseFixedImageGradientFilter(false);
  }
  /** @} */

  /** \brief Enable moving image gradient computation by a filter.
   *
   * \sa itk::ImageToImageMetricv4::SetUseMovingImageGradientFilter
   * @{
   */
  void
  SetMetricUseMovingImageGradientFilter(bool);
  void
  MetricUseMovingImageGradientFilterOn()
  {
    return this->SetMetricUseMovingImageGradientFilter(true);
  }
  void
  MetricUseMovingImageGradientFilterOff()
  {
    return this->SetMetricUseMovingImageGradientFilter(false);
  }
  /** @} */

  /** \brief Set the isotropic shrink factors for each level.
   *
   * The number of levels is the number of shrink factors. The
   * default is 8, 4, 2, 1.
   *
   * \sa  itk::ImageRegistrationMethodv4::SetShrinkFactorsPerLevel
   */
  void
  SetShrinkFactorsPerLevel(const std::vector<unsigned int> & shrinkFactors);

  /** \brief Set the sigmas of the Gaussian used to smooth the fixed
   * and moving images at each level.
   *
   * The number of sigmas must match the number of shrink factors.
   * The default is 3, 2, 1, 0.
   *
   * \sa  itk::ImageRegistrationMethodv4::SetSmoothingSigmasPerLevel
   */
  void
  SetSmoothingSigmasPerLevel(const std::vector<double> & smoothingSigmas);

  /** \brief Specify the smoothing sigmas in physical units or in
   * voxels. The default is voxels (false), as in antsRegistrationSyN.sh.
   *
   * \sa   itk::ImageRegistrationMethodv4::SetSmoothingSigmasAreSpecifiedInPhysicalUnits
   * @{
   */
  void
  SetSmoothingSigmasAreSpecifiedInPhysicalUnits(bool arg);
  void
  SmoothingSigmasAreSpecifiedInPhysicalUnitsOn()
  {
    this->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(true);
  }
  void
  SmoothingSigmasAreSpecifiedInPhysicalUnitsOff()
  {
    this->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(false);
  }
  /** @} */

  /** \brief Set the maximum number of iterations at each level.
   *
   * The number of entries must match the number of shrink factors.
   * The default is 100, 70, 50, 20.
   *
   * \sa itk::SyNImageRegistrationMethod::SetNumberOfIterationsPerLevel
   * @{
   */
  void
  SetNumberOfIterationsPerLevel(const std::vector<unsigned int> & iterations);
  const std::vector<unsigned int> &
  GetNumberOfIterationsPerLevel() const
  {
    return this->m_NumberOfIterationsPerLevel;
  }
  /** @} */

  /** \brief Set the gradient step, the maximum displacement in voxels
   * applied per iteration. This is the first SyN parameter of
   * antsRegistration. The default is 0.2.
   *
   * \sa itk::SyNImageRegistrationMethod::SetLearningRate
   * @{
   */
  void
  SetLearningRate(double learningRate);
  double
  GetLearningRate() const
  {
    return this->m_LearningRate;
  }
  /** @} */

  /** \brief Set the convergence threshold and window size.
   *
   * The convergence value is the negated slope of a line fit to the
   * last windowSize metric values, normalized by their magnitude. A
   * level stops when this value drops below the threshold, which
   * includes any negative value, so a level ends as soon as the
   * metric stops improving over the window. The defaults are 1e-6
   * and 10.
   *
   * \sa itk::SyNImageRegistrationMethod::SetConvergenceThreshold
   * \sa itk::SyNImageRegistrationMethod::SetConvergenceWindowSize
   * @{
   */
  void
  SetConvergenceThreshold(double threshold);
  double
  GetConvergenceThreshold() const
  {
    return this->m_ConvergenceThreshold;
  }
  void
  SetConvergenceWindowSize(unsigned int windowSize);
  unsigned int
  GetConvergenceWindowSize() const
  {
    return this->m_ConvergenceWindowSize;
  }
  /** @} */

  /** \brief Set the variance, in voxels of the virtual domain, of the
   * Gaussian used to smooth the update field at each iteration. This
   * is the second SyN parameter of antsRegistration. The default is 3.
   *
   * \sa itk::SyNImageRegistrationMethod::SetGaussianSmoothingVarianceForTheUpdateField
   * @{
   */
  void
  SetGaussianSmoothingVarianceForTheUpdateField(double variance);
  double
  GetGaussianSmoothingVarianceForTheUpdateField() const
  {
    return this->m_GaussianSmoothingVarianceForTheUpdateField;
  }
  /** @} */

  /** \brief Set the variance, in voxels of the virtual domain, of the
   * Gaussian used to smooth the total field at each iteration. This
   * is the third SyN parameter of antsRegistration. The default is 0,
   * no smoothing.
   *
   * \sa itk::SyNImageRegistrationMethod::SetGaussianSmoothingVarianceForTheTotalField
   * @{
   */
  void
  SetGaussianSmoothingVarianceForTheTotalField(double variance);
  double
  GetGaussianSmoothingVarianceForTheTotalField() const
  {
    return this->m_GaussianSmoothingVarianceForTheTotalField;
  }
  /** @} */

  /** \brief Compute the metric derivatives on images resampled to the
   * virtual domain of the current level rather than at full
   * resolution. The default is true, the classic SyN behavior.
   *
   * \sa itk::SyNImageRegistrationMethod::SetDownsampleImagesForMetricDerivatives
   * @{
   */
  void
  SetDownsampleImagesForMetricDerivatives(bool arg);
  bool
  GetDownsampleImagesForMetricDerivatives() const
  {
    return this->m_DownsampleImagesForMetricDerivatives;
  }
  void
  DownsampleImagesForMetricDerivativesOn()
  {
    this->SetDownsampleImagesForMetricDerivatives(true);
  }
  void
  DownsampleImagesForMetricDerivativesOff()
  {
    this->SetDownsampleImagesForMetricDerivatives(false);
  }
  /** @} */

  /** \brief Average the fixed-to-middle and moving-to-middle update
   * fields to further reduce bias. The default is false.
   *
   * \sa itk::SyNImageRegistrationMethod::SetAverageMidPointGradients
   * @{
   */
  void
  SetAverageMidPointGradients(bool arg);
  bool
  GetAverageMidPointGradients() const
  {
    return this->m_AverageMidPointGradients;
  }
  void
  AverageMidPointGradientsOn()
  {
    this->SetAverageMidPointGradients(true);
  }
  void
  AverageMidPointGradientsOff()
  {
    this->SetAverageMidPointGradients(false);
  }
  /** @} */

  /** \brief Run the registration.
   *
   * The fixed and moving images must have the same real pixel type
   * (sitkFloat32 or sitkFloat64) and dimension (2 or 3).
   *
   * The returned transform maps points of the fixed image domain to
   * the moving image domain; its displacement field is the one
   * needed to resample the moving image onto the fixed image, and
   * its inverse displacement field is also set. Both fields are
   * defined on the virtual domain grid of the last level, which is
   * the fixed image grid when the last shrink factor is 1.
   */
  DisplacementFieldTransform
  Execute(const Image & fixed, const Image & moving);

  /** \brief Active measurements available during callbacks and after
   * execution.
   *
   * GetCurrentIteration is the number of iterations completed at the
   * current level. GetMetricValue is the mean of the two half-way
   * metric values of the last iteration. GetConvergenceValue is the
   * windowed convergence value described at SetConvergenceThreshold.
   * @{
   */
  unsigned int
  GetCurrentLevel() const;
  unsigned int
  GetCurrentIteration() const;
  double
  GetMetricValue() const;
  double
  GetConvergenceValue() const;
  /** @} */

  /** \brief Number of points in the virtual domain used by the last
   * metric evaluation.
   *
   * \sa itk::ImageToImageMetricv4::GetNumberOfValidPoints
   */
  uint64_t
  GetMetricNumberOfValidPoints() const;

  /** \brief Description of why the last level stopped, available
   * after execution.
   */
  std::string
  GetStopConditionDescription() const;

protected:
  template <class TImage>
  DisplacementFieldTransform
  ExecuteInternal(const Image & fixed, const Image & moving);

  template <unsigned int VDimension>
  itk::SpatialObject<VDimension> *
  CreateSpatialObjectMask(const Image & mask);

  template <class TImageType>
  itk::ImageToImageMetricv4<TImageType,
                            TImageType,
                            TImageType,
                            double,
                            itk::DefaultImageToImageMetricTraitsv4<TImageType, TImageType, TImageType, double>> *
  CreateMetric();

  template <class TImageType>
  void
  SetupMetric(
    itk::ImageToImageMetricv4<TImageType,
                              TImageType,
                              TImageType,
                              double,
                              itk::DefaultImageToImageMetricTraitsv4<TImageType, TImageType, TImageType, double>> *,
    const TImageType *,
    const TImageType *);

  void
  OnActiveProcessDelete() noexcept override;
  unsigned long
  AddITKObserver(const itk::EventObject &, itk::Command *) override;

private:
  std::function<unsigned int()> m_pfGetCurrentLevel;
  std::function<unsigned int()> m_pfGetCurrentIteration;
  std::function<double()>       m_pfGetMetricValue;
  std::function<double()>       m_pfGetConvergenceValue;
  std::function<uint64_t()>     m_pfGetMetricNumberOfValidPoints;

  typedef DisplacementFieldTransform (SyNImageRegistrationMethod::*MemberFunctionType)(const Image & fixed,
                                                                                       const Image & moving);
  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

  InterpolatorEnum m_Interpolator;
  Transform        m_InitialTransform;
  bool             m_InitialTransformInPlace;
  Transform        m_MovingInitialTransform;
  Transform        m_FixedInitialTransform;

  // metric
  enum MetricType
  {
    ANTSNeighborhoodCorrelation,
    Correlation,
    Demons,
    JointHistogramMutualInformation,
    MeanSquares,
    MattesMutualInformation
  };
  MetricType   m_MetricType;
  unsigned int m_MetricRadius;
  double       m_MetricIntensityDifferenceThreshold;
  unsigned int m_MetricNumberOfHistogramBins;
  double       m_MetricVarianceForJointPDFSmoothing;

  Image m_MetricFixedMaskImage;
  Image m_MetricMovingMaskImage;

  std::vector<double>        m_MetricSamplingPercentage;
  MetricSamplingStrategyType m_MetricSamplingStrategy;
  unsigned int               m_MetricSamplingSeed;

  bool m_MetricUseFixedImageGradientFilter;
  bool m_MetricUseMovingImageGradientFilter;

  std::vector<unsigned int> m_ShrinkFactorsPerLevel;
  std::vector<double>       m_SmoothingSigmasPerLevel;
  bool                      m_SmoothingSigmasAreSpecifiedInPhysicalUnits;

  // SyN parameters
  std::vector<unsigned int> m_NumberOfIterationsPerLevel;
  double                    m_LearningRate;
  double                    m_ConvergenceThreshold;
  unsigned int              m_ConvergenceWindowSize;
  double                    m_GaussianSmoothingVarianceForTheUpdateField;
  double                    m_GaussianSmoothingVarianceForTheTotalField;
  bool                      m_DownsampleImagesForMetricDerivatives;
  bool                      m_AverageMidPointGradients;

  // measurements after execution
  std::string  m_StopConditionDescription;
  unsigned int m_CurrentLevel;
  unsigned int m_Iteration;
  double       m_MetricValue;
  double       m_ConvergenceValue;
  uint64_t     m_NumberOfValidPoints;
};

} // namespace simple
} // namespace itk

#endif // sitkSyNImageRegistrationMethod_h
