.. _lbl_registration_overview:

Registration Overview
---------------------

The goal of registration is to estimate the transformation which maps points
from one image to the corresponding points in another image. The
transformation estimated via registration is said to map points from the
**fixed image** coordinate system to the **moving image** coordinate system.

SimpleITK provides a configurable multi-resolution registration
framework, implemented in the `ImageRegistrationMethod
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html>`_ class.
In addition, a number of variations of the Demons registration algorithm are
implemented independently from this class as they do not fit into the framework.

Actual Code
...........

Code illustrating various aspects of the registration framework can be found in
the set of :ref:`examples <lbl_examples>` which are part of the SimpleITK distribution
and in the SimpleITK `Jupyter notebook repository <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`_.

Initialization and Center of Rotation
.....................................

The task of registration is formulated using non-linear optimization which requires an initial estimate. The two
most common initialization approaches are (1) Use the identity transform (a.k.a. forgot to initialize).
(2) Align the physical centers of the two images (see `CenteredTransformInitializerFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1CenteredTransformInitializerFilter.html>`_). If after initialization there is no overlap between the
images, registration will fail. The closer the initialization transformation is to the actual transformation, the higher the probability
of convergence to the correct solution.

If your registration involves the use of a global domain transform (:ref:`described here <lbl_transforms>`), you should also set
an appropriate center of rotation. In many cases you want the center of rotation to be the physical center of the fixed image
(the CenteredTransformCenteredTransformInitializerFilter ensures this). This is of significant importance for registration convergence due
to the non-linear nature of rotation. When the center of rotation is far from our physical region of interest (ROI), a small rotational angle
results in a large displacement. Think of moving the pivot/fulcrum point of a `lever <https://en.wikipedia.org/wiki/Lever>`_. For the same
rotation angle, the farther you are from the fulcrum the larger the displacement. For numerical stability we do not want our computations
to be sensitive to very small variations in the rotation angle, thus the ideal center of rotation is the point which minimizes the
distance to the farthest point in our ROI:

.. math::

   p_{center} = \underset{p_{rotation}} {\arg\min}\ dist(p_{rotation}, \{p_{roi}\})


Without additional knowledge we can only assume that the ROI is the whole fixed image. If your ROI is only in a sub
region of the image, a more appropriate point would be the center of the oriented bounding box of that ROI.


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

* `TranslationTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TranslationTransform.html>`_.
* `VersorTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1VersorTransform.html>`_.
* `VersorRigid3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1VersorRigid3DTransform.html>`_.
* `Euler2DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Euler2DTransform.html>`_.
* `Euler3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Euler3DTransform.html>`_.
* `Similarity2DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Similarity2DTransform.html>`_.
* `Similarity3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Similarity3DTransform.html>`_.
* `ScaleTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleTransform.html>`_.
* `ScaleVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleVersor3DTransform.html>`_.
* `ScaleSkewVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleSkewVersor3DTransform.html>`_.
* `ComposeScaleSkewVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ComposeScaleSkewVersor3DTransform.html>`_.
* `AffineTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1AffineTransform.html>`_.
* `BSplineTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1BSplineTransform.html>`_.
* `DisplacementFieldTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1DisplacementFieldTransform.html>`_.
* `Composite Transform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Transform.html>`_.

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
receives a `parameter <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#a7cb1ef8bd02c669c02ea2f9f5aa374e5>`_
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
via two methods `SetShrinkFactorsPerLevel <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a59fef92122919202cf4a00f84fd87ea5>`_
and `SetSmoothingSigmasPerLevel <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a0aea868182491c8d6900129955b4f5b4>`_.
The former receives the shrink factors to apply when moving from one level of
the pyramid to the next and the later receives the sigmas to use for smoothing
when moving from level to level. Sigmas can be specified either in voxel units
or physical units (default) using `SetSmoothingSigmasAreSpecifiedInPhysicalUnits <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a50c2a2242421fdcafdc42d548b994ed9>`_.

Sampling
========

For many registration tasks one can use a fraction of the image voxels to
estimate the similarity measure. Aggressive sampling can significantly reduce
the registration runtime. The ImageRegistration method allows you to
specify how/if to sample the voxels, `SetMetricSamplingStrategy <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#aa49fdfae5950c2ec6e01a75df59078f6>`_, and
if using a sampling, what percentage, `SetMetricSamplingPercentage <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a8b891c62404a8dc5010241fea619c932>`_.

The registration framework supports three sampling strategies:

1. NONE - use all voxels, sampled points are the voxel centers.
2. REGULAR - sample every n-th voxel while traversing the image
   in scan-line order, then within each voxel randomly
   perturb from center.
3. RANDOM - sample image voxels with replacement using a uniform distribution, then within each voxel randomly perturb from center.

When using the REGULAR or RANDOM sampling strategies, running the same
registration code multiple times will yield different results. To remove
the randomness, set the pseudo-random number generator's seed in the
`SetMetricSamplingPercentage <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a8b891c62404a8dc5010241fea619c932>`_
method to a constant. The default seed value is
wall clock time.

Note that using the RANDOM sampling strategy with a 100% sampling rate is not
equivalent to using the sampling strategy of NONE. Given an image with N voxels,
the former randomly selects N voxels with repetition and perturbs the points
within each voxel, the latter uses the centers of all N voxels. Thus, for
repeated random sampling with 100% rate, different samples are produced and likely
none of them is of the centers of all N voxels.

Combining a mask with sampling is done using a rejection approach. First a sample is generated and
then it is accepted or rejected if it is inside or outside the mask. This may cause
problems when the mask region occupies a very small region in the original image. Because the sampling
only discards data,the sample rate may be reduced from the requested one. For some similarity metrics (e.g. mutual information)
this can result in an insufficient number of samples for metric value computation, leading to registraiton failure.
Other metrics are more robust to small sample sizes (e.g. mean squares), but they all suffer from it.
In such cases it is better to use a cropped version of the image for registration, possibly the mask's bounding box,
instead of the original image with a mask.



Scaling in Parameter Space
==========================

The ITKv4 framework introduced automated methods for estimating scaling factors
for non-commensurate parameter units. These change the step size per parameter
so that the effect of a unit of change has similar effects in physical space
(think rotation of 1 radian and translation of 1 millimeter).
The relevant methods are `SetOptimizerScalesFromPhysicalShift <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a53934282121e152d37781ffa5224ec5f>`_,
`SetOptimizerScalesFromIndexShift <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#a0ad235e8291716cb44c87a01c6b545a9>`_ and
`SetOptimizerScalesFromJacobian <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html#afe20311a9a425f312e3cefaaf683fab4>`_.
In many cases this scaling is what determines if the the optimization converges to the
correct optimum.

Observing Registration Progress
================================

The ImageRegistrationMethod enables you to observe the registration process as it progresses.
This is done using the Command-Observer pattern, associating callbacks with specific events.
To associate a callback with a specific `event <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#aa7399868984d99493c5a307cce373ace>`_
use the `AddCommand <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ProcessObject.html#a2199e5cca19b45d504676a595e1f6cfd>`_
method.
