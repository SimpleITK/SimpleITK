.. _lbl_registration_overview:

Registration Overview
---------------------

The goal of registration is to estimate the transformation which maps points
from one image to the corresponding points in another image. The
transformation estimated via registration is said to map points from the
**fixed image** coordinate system to the **moving image** coordinate system.

SimpleITK provides a configurable multi-resolution registration
framework, implemented in the `ImageRegistrationMethod
<https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html>`_ class.
In addition, a number of variations of the Demons registration algorithm are
implemented independently from this class as they do not fit into the framework.

Actual Code
...........

Code illustrating various aspects of the registration framework can be found in
the set of :ref:`examples <lbl_examples>` which are part of the SimpleITK distribution
and in the SimpleITK `Jupyter notebook repository <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`_.


ImageRegistrationMethod
........................

To create a specific registration instance using the ImageRegistrationMethod
you need to select several components which together define the registration instance:

1. Transformation.
2. Similarity metric.
3. Optimizer.
4. Interpolator.


Transform
+++++++++

The type of transformation defines the mapping between the two images. SimpleITK
supports a variety of global and local transformations. The available
transformations include:

* `TranslationTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TranslationTransform.html>`_.
* `VersorTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VersorTransform.html>`_.
* `VersorRigid3DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VersorRigid3DTransform.html>`_.
* `Euler2DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Euler2DTransform.html>`_.
* `Euler3DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Euler3DTransform.html>`_.
* `Similarity2DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Similarity2DTransform.html>`_.
* `Similarity3DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Similarity3DTransform.html>`_.
* `ScaleTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScaleTransform.html>`_.
* `ScaleVersor3DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScaleVersor3DTransform.html>`_.
* `ScaleSkewVersor3DTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScaleSkewVersor3DTransform.html>`_.
* `AffineTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AffineTransform.html>`_.
* `BSplineTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BSplineTransform.html>`_.
* `DisplacementFieldTransform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DisplacementFieldTransform.html>`_.
* `Composite Transform <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Transform.html>`_.

The parameters modified by the registration framework are those returned by the
transforms **GetParameters()** method. This requires special attention when the
using a composite transform, as the specific parameters vary
based on the content of your composite transformation.

Similarity Metric
++++++++++++++++++

The similarity metric reflects the relationship between the intensities of the
images (identity, affine, stochastic...). The available metrics include:

* `MeanSquares <http://www.itk.org/Doxygen/html/classitk_1_1MeanSquaresImageToImageMetricv4.html>`_ .
* `Demons <http://www.itk.org/Doxygen/html/classitk_1_1DemonsImageToImageMetricv4.html>`_.
* `Correlation <http://www.itk.org/Doxygen/html/classitk_1_1CorrelationImageToImageMetricv4.html>`_.
* `ANTSNeighborhoodCorrelation <http://www.itk.org/Doxygen/html/classitk_1_1ANTSNeighborhoodCorrelationImageToImageMetricv4.html>`_.
* `JointHistogramMutualInformation <http://www.itk.org/Doxygen/html/classitk_1_1JointHistogramMutualInformationImageToImageMetricv4.html>`_.
* `MattesMutualInformation <http://www.itk.org/Doxygen/html/classitk_1_1MattesMutualInformationImageToImageMetricv4.html>`_.

In the ITKv4 and consequentially in SimpleITK all similarity metrics are
minimized. For metrics whose optimum corresponds to a maximum, such as mutual
information, the metric value is negated internally. The selection of a
similarity metric is done using the ImageRegistrationMethod's **SetMetricAsX()**
methods.

Optimizer
+++++++++

The optimizer is selected using the **SetOptimizerAsX()** methods.
When selecting the optimizer you will also need to configure it (e.g. set the
number of iterations). The available optimizers include:

* Gradient free

  * `Exhaustive <http://www.itk.org/Doxygen/html/classitk_1_1ExhaustiveOptimizerv4.html>`_.
  * `Nelder-Mead downhill simplex <http://www.itk.org/Doxygen/html/classitk_1_1AmoebaOptimizerv4.html>`_ (Amoeba).
  * `Powell <https://itk.org/Doxygen/html/classitk_1_1PowellOptimizerv4.html>`_.
  * `1+1 evolutionary optimizer <https://itk.org/Doxygen/html/classitk_1_1OnePlusOneEvolutionaryOptimizerv4.html>`_.

* Gradient based:

  * `Gradient Descent <http://www.itk.org/Doxygen/html/classitk_1_1GradientDescentOptimizerv4Template.html>`_.
  * `Gradient Descent Line Search <http://www.itk.org/Doxygen/html/classitk_1_1GradientDescentLineSearchOptimizerv4Template.html>`_.
  * `Regular Step Gradient Descent <http://www.itk.org/Doxygen/html/classitk_1_1RegularStepGradientDescentOptimizerv4.html>`_.
  * `Conjugate Gradient Line Search <http://www.itk.org/Doxygen/html/classitk_1_1ConjugateGradientLineSearchOptimizerv4Template.html>`_.
  * `L-BFGS-B <http://www.itk.org/Doxygen/html/classitk_1_1LBFGSBOptimizerv4.html>`_. Limited memory Broyden, Fletcher, Goldfarb, Shannon, Bound Constrained (supports the use of simple constraints).

Interpolator
++++++++++++

SimpleITK has a large number of interpolators. In most cases linear
interpolation, the default setting, is sufficient. Unlike the similarity metric
and optimizer, the interpolator is set using the **SetInterpolator** method which
receives a `parameter <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a7cb1ef8bd02c669c02ea2f9f5aa374e5>`_
indicating the interpolator type.

Features of Interest
+++++++++++++++++++++

Transforms and image spaces
===========================

While the goal of registration, as defined above, refers to a single
transformation and two images, the ITKv4 registration and the
SimpleITK ImageRegistrationMethod provide additional flexibility in
registration configuration.

From a coordinate system standpoint ITKv4 introduced the
**virtual image domain**, making registration a symmetric process so that both
images are treated similarly. As a consequence the ImageRegistrationMethod
has methods for setting **three transformations**:

1. SetInitialTransform :math:`T_o` - composed with the moving initial transform, maps
points from the virtual image domain to the moving image domain, modified
during optimization.

2. SetFixedInitialTransform :math:`T_f` - maps points from the virtual image domain
to the fixed image domain, never modified.

3. SetMovingInitialTransform :math:`T_m`- maps points from the virtual image domain to
the moving image domain, never modified.

The transformation that maps points from the fixed to moving image domains is thus:

.. math::
   p_{moving}=T_o(T_m(T_f^{-1}(p_{fixed})))

Multi Resolution Framework
===========================

The ImageRegistrationMethod supports multi-resolution, pyramid, registration
via two methods `SetShrinkFactorsPerLevel <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a59fef92122919202cf4a00f84fd87ea5>`_
and `SetSmoothingSigmasPerLevel <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a0aea868182491c8d6900129955b4f5b4>`_.
The former receives the shrink factors to apply when moving from one level of
the pyramid to the next and the later receives the sigmas to use for smoothing
when moving from level to level. Sigmas can be specified either in voxel units
or physical units (default) using `SetSmoothingSigmasAreSpecifiedInPhysicalUnits <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a50c2a2242421fdcafdc42d548b994ed9>`_.

Sampling
========

For many registration tasks one can use a fraction of the image voxels to
estimate the similarity measure. Aggressive sampling can significantly reduce
the registration runtime. The ImageRegistration method allows you to
specify how/if to sample the voxels, `SetMetricSamplingStrategy <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#aa49fdfae5950c2ec6e01a75df59078f6>`_, and
if using a sampling, what percentage, `SetMetricSamplingPercentage <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a8b891c62404a8dc5010241fea619c932>`_.

Scaling in Parameter Space
==========================

The ITKv4 framework introduced automated methods for estimating scaling factors
for non-commensurate parameter units. These change the step size per parameter
so that the effect of a unit of change has similar effects in physical space
(think rotation of 1 radian and translation of 1 millimeter).
The relevant methods are `SetOptimizerScalesFromPhysicalShift <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a53934282121e152d37781ffa5224ec5f>`_,
`SetOptimizerScalesFromIndexShift <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a0ad235e8291716cb44c87a01c6b545a9>`_ and
`SetOptimizerScalesFromJacobian <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#afe20311a9a425f312e3cefaaf683fab4>`_.
In many cases this scaling is what determines if the the optimization converges to the
correct optimum.

Observing Registration Progress
================================

The ImageRegistrationMethod enables you to observe the registration process as it progresses.
This is done using the Command-Observer pattern, associating callbacks with specific events.
To associate a callback with a specific `event <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#aa7399868984d99493c5a307cce373ace>`_
use the `AddCommand <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ProcessObject.html#a2199e5cca19b45d504676a595e1f6cfd>`_
method.
