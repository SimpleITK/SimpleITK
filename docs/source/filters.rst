.. _lbl_filter:

SimpleITK Filters
=================

.. list-table::
   :widths: 50 100
   :stub-columns: 1
   :header-rows: 1

   * - Filter Name
     - Brief Description
   * - `AbsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AbsImageFilter.html>`_
     - Computes the absolute value of each pixel.
   * - `AbsoluteValueDifferenceImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AbsoluteValueDifferenceImageFilter.html>`_
     - Implements pixel-wise the computation of absolute value difference.
   * - `AcosImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AcosImageFilter.html>`_
     - Computes the inverse cosine of each pixel.
   * - `AdaptiveHistogramEqualizationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AdaptiveHistogramEqualizationImageFilter.html>`_
     - Power Law Adaptive Histogram Equalization.
   * - `AddImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AddImageFilter.html>`_
     - Pixel-wise addition of two images.
   * - `AdditiveGaussianNoiseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AdditiveGaussianNoiseImageFilter.html>`_
     - Alter an image with additive Gaussian white noise.
   * - `AggregateLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AggregateLabelMapFilter.html>`_
     - Collapses all labels into the first label.
   * - `AndImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AndImageFilter.html>`_
     - Implements the AND bitwise operator pixel-wise between two images.
   * - `AntiAliasBinaryImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AntiAliasBinaryImageFilter.html>`_
     - A method for estimation of a surface from a binary volume.
   * - `ApproximateSignedDistanceMapImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ApproximateSignedDistanceMapImageFilter.html>`_
     - Create a map of the approximate signed distance from the boundaries of a binary image.
   * - `AsinImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AsinImageFilter.html>`_
     - Computes the sine of each pixel.
   * - `Atan2ImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Atan2ImageFilter.html>`_
     - Computes two argument inverse tangent.
   * - `AtanImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1AtanImageFilter.html>`_
     - Computes the one-argument inverse tangent of each pixel.
   * - `BSplineDecompositionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BSplineDecompositionImageFilter.html>`_
     - Calculates the B-Spline coefficients of an image. Spline order may be from 0 to 5.
   * - `BilateralImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BilateralImageFilter.html>`_
     - Blurs an image while preserving edges.
   * - `BinShrinkImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinShrinkImageFilter.html>`_
     - Reduce the size of an image by an integer factor in each dimension while performing averaging of an input neighborhood.
   * - `BinaryClosingByReconstructionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryClosingByReconstructionImageFilter.html>`_
     - binary closing by reconstruction of an image.
   * - `BinaryContourImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryContourImageFilter.html>`_
     - Labels the pixels on the border of the objects in a binary image.
   * - `BinaryDilateImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryDilateImageFilter.html>`_
     - Fast binary dilation.
   * - `BinaryErodeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryErodeImageFilter.html>`_
     - Fast binary erosion.
   * - `BinaryFillholeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFillholeImageFilter.html>`_
     - Remove holes not connected to the boundary of the image.
   * - `BinaryGrindPeakImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryGrindPeakImageFilter.html>`_
     - Remove the objects not connected to the boundary of the image.
   * - `BinaryImageToLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryImageToLabelMapFilter.html>`_
     - Label the connected components in a binary image and produce a collection of label objects.
   * - `BinaryMagnitudeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryMagnitudeImageFilter.html>`_
     - Computes the square root of the sum of squares of corresponding input pixels.
   * - `BinaryMedianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryMedianImageFilter.html>`_
     - Applies a version of the median filter optimized for binary images.
   * - `BinaryMinMaxCurvatureFlowImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryMinMaxCurvatureFlowImageFilter.html>`_
     - Denoise a binary image using min/max curvature flow.
   * - `BinaryMorphologicalClosingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryMorphologicalClosingImageFilter.html>`_
     - binary morphological closing of an image.
   * - `BinaryMorphologicalOpeningImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryMorphologicalOpeningImageFilter.html>`_
     - binary morphological opening of an image.
   * - `BinaryNotImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryNotImageFilter.html>`_
     - Implements the BinaryNot logical operator pixel-wise between two images.
   * - `BinaryOpeningByReconstructionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryOpeningByReconstructionImageFilter.html>`_
     - binary morphological closing of an image.
   * - `BinaryProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryProjectionImageFilter.html>`_
     - Binary projection.
   * - `BinaryReconstructionByDilationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryReconstructionByDilationImageFilter.html>`_
     - binary reconstruction by dilation of an image
   * - `BinaryReconstructionByErosionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryReconstructionByErosionImageFilter.html>`_
     - binary reconstruction by erosion of an image
   * - `BinaryThinningImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryThinningImageFilter.html>`_
     - This filter computes one-pixel-wide edges of the input image.
   * - `BinaryThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryThresholdImageFilter.html>`_
     - Binarize an input image by thresholding.
   * - `BinaryThresholdProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryThresholdProjectionImageFilter.html>`_
     - BinaryThreshold projection.
   * - `BinomialBlurImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinomialBlurImageFilter.html>`_
     - Performs a separable blur on each dimension of an image.
   * - `BitwiseNotImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1UnaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation on one image.
   * - `BlackTopHatImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BlackTopHatImageFilter.html>`_
     - Black top hat extracts local minima that are smaller than the structuring element.
   * - `BoundedReciprocalImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BoundedReciprocalImageFilter.html>`_
     - Computes 1/(1+x) for each pixel in the image.
   * - `BoxMeanImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BoxMeanImageFilter.html>`_
     - Implements a fast rectangular mean filter using the accumulator approach.
   * - `BoxSigmaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BoxSigmaImageFilter.html>`_
     - Implements a fast rectangular sigma filter using the accumulator approach.
   * - `CannyEdgeDetectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CannyEdgeDetectionImageFilter.html>`_
     - This filter is an implementation of a Canny edge detector for scalar-valued images.
   * - `CannySegmentationLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CannySegmentationLevelSetImageFilter.html>`_
     - Segments structures in images based on image features derived from pseudo-canny-edges.
   * - `ChangeLabelImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ChangeLabelImageFilter.html>`_
     - Change Sets of Labels.
   * - `ChangeLabelLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ChangeLabelLabelMapFilter.html>`_
     - Replace the label Ids of selected LabelObjects with new label Ids.
   * - `CheckerBoardImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CheckerBoardImageFilter.html>`_
     - Combines two images in a checkerboard pattern.
   * - `ClampImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ClampImageFilter.html>`_
     - Casts input pixels to output pixel type and clamps the output pixel values to a specified range.
   * - `ClosingByReconstructionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ClosingByReconstructionImageFilter.html>`_
     - Closing by reconstruction of an image.
   * - `CoherenceEnhancingDiffusionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CoherenceEnhancingDiffusionImageFilter.html>`_
     - Coherence enhancing diffusion and edge enhancing diffusion.
   * - `CollidingFrontsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CollidingFrontsImageFilter.html>`_
     - Selects a region of space where two independent fronts run towards each other.
   * - `ComplexToImaginaryImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComplexToImaginaryImageFilter.html>`_
     - Computes pixel-wise the imaginary part of a complex image.
   * - `ComplexToModulusImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComplexToModulusImageFilter.html>`_
     - Computes pixel-wise the Modulus of a complex image.
   * - `ComplexToPhaseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComplexToPhaseImageFilter.html>`_
     - Computes pixel-wise the modulus of a complex image.
   * - `ComplexToRealImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComplexToRealImageFilter.html>`_
     - Computes pixel-wise the real(x) part of a complex image.
   * - `ComposeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComposeImageFilter.html>`_
     - ComposeImageFilter combine several scalar images into a multicomponent image.
   * - `ConfidenceConnectedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ConfidenceConnectedImageFilter.html>`_
     - Segment pixels with similar statistics using connectivity.
   * - `ConnectedComponentImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ConnectedComponentImageFilter.html>`_
     - Label the objects in a binary image.
   * - `ConnectedThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ConnectedThresholdImageFilter.html>`_
     - Label pixels that are connected to a seed and lie within a range of values.
   * - `ConstantPadImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ConstantPadImageFilter.html>`_
     - Increase the image size by padding with a constant value.
   * - `ConvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ConvolutionImageFilter.html>`_
     - Convolve a given image with an arbitrary image kernel.
   * - `CosImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CosImageFilter.html>`_
     - Computes the cosine of each pixel.
   * - `CropImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CropImageFilter.html>`_
     - Decrease the image size by cropping the image by an itk::Size at both the upper and lower bounds of the largest possible region.
   * - `CurvatureAnisotropicDiffusionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CurvatureAnisotropicDiffusionImageFilter.html>`_
     -
   * - `CurvatureFlowImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CurvatureFlowImageFilter.html>`_
     - Denoise an image using curvature driven flow.
   * - `CyclicShiftImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1CyclicShiftImageFilter.html>`_
     - Perform a cyclic spatial shift of image intensities on the image grid.
   * - `DanielssonDistanceMapImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DanielssonDistanceMapImageFilter.html>`_
     - This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.
   * - `DemonsRegistrationFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DemonsRegistrationFilter.html>`_
     - Deformably register two images using the demons algorithm.
   * - `DerivativeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DerivativeImageFilter.html>`_
     - Computes the directional derivative of an image. The directional derivative at each pixel location is computed by convolution with a derivative operator of user-specified order.
   * - `DiffeomorphicDemonsRegistrationFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DiffeomorphicDemonsRegistrationFilter.html>`_
     - Deformably register two images using a diffeomorphic demons algorithm.
   * - `DilateObjectMorphologyImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DilateObjectMorphologyImageFilter.html>`_
     - dilation of an object in an image
   * - `DiscreteGaussianDerivativeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DiscreteGaussianDerivativeImageFilter.html>`_
     - Calculates image derivatives using discrete derivative gaussian kernels. This filter calculates Gaussian derivative by separable convolution of an image and a discrete Gaussian derivative operator (kernel).
   * - `DiscreteGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DiscreteGaussianImageFilter.html>`_
     - Blurs an image by separable convolution with discrete gaussian kernels. This filter performs Gaussian blurring by separable convolution of an image and a discrete Gaussian operator (kernel).
   * - `DisplacementFieldJacobianDeterminantFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DisplacementFieldJacobianDeterminantFilter.html>`_
     - Computes a scalar image from a vector image (e.g., deformation field) input, where each output scalar at each pixel is the Jacobian determinant of the vector field at that location. This calculation is correct in the case where the vector image is a "displacement" from the current location. The computation for the jacobian determinant is: det[ dT/dx ] = det[ I + du/dx ].
   * - `DivideFloorImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `DivideImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DivideImageFilter.html>`_
     - Pixel-wise division of two images.
   * - `DivideRealImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `DoubleThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1DoubleThresholdImageFilter.html>`_
     - Binarize an input image using double thresholding.
   * - `EdgePotentialImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1EdgePotentialImageFilter.html>`_
     - Computes the edge potential of an image from the image gradient.
   * - `EqualImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `ErodeObjectMorphologyImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ErodeObjectMorphologyImageFilter.html>`_
     - Erosion of an object in an image.
   * - `ExpImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ExpImageFilter.html>`_
     - Computes the exponential function of each pixel.
   * - `ExpNegativeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ExpNegativeImageFilter.html>`_
     - Computes the function exp(-K.x) for each input pixel.
   * - `ExpandImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ExpandImageFilter.html>`_
     - Expand the size of an image by an integer factor in each dimension.
   * - `ExtractImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ExtractImageFilter.html>`_
     - Decrease the image size by cropping the image to the selected region bounds.
   * - `FFTConvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FFTConvolutionImageFilter.html>`_
     - Convolve a given image with an arbitrary image kernel using multiplication in the Fourier domain.
   * - `FFTNormalizedCorrelationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FFTNormalizedCorrelationImageFilter.html>`_
     - Calculate normalized cross correlation using FFTs.
   * - `FFTPadImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FFTPadImageFilter.html>`_
     - Pad an image to make it suitable for an FFT transformation.
   * - `FFTShiftImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FFTShiftImageFilter.html>`_
     - Shift the zero-frequency components of a Fourier transform to the center of the image.
   * - `FastApproximateRankImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FastApproximateRankImageFilter.html>`_
     - A separable rank filter.
   * - `FastMarchingBaseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FastMarchingImageFilterBase.html>`_
     - Apply the Fast Marching method to solve an Eikonal equation on an image.
   * - `FastMarchingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FastMarchingImageFilter.html>`_
     - Solve an Eikonal equation using Fast Marching.
   * - `FastMarchingUpwindGradientImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FastMarchingUpwindGradientImageFilter.html>`_
     - Generates the upwind gradient field of fast marching arrival times.
   * - `FastSymmetricForcesDemonsRegistrationFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FastSymmetricForcesDemonsRegistrationFilter.html>`_
     - Deformably register two images using a symmetric forces demons algorithm.
   * - `FlipImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1FlipImageFilter.html>`_
     - Flips an image across user specified axes.
   * - `ForwardFFTImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ForwardFFTImageFilter.html>`_
     - Base class for forward Fast Fourier Transform .
   * - `GaborImageSource <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GaborImageSource.html>`_
     - Generate an n-dimensional image of a Gabor filter.
   * - `GaussianImageSource <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GaussianImageSource.html>`_
     - Generate an n-dimensional image of a Gaussian.
   * - `GeodesicActiveContourLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GeodesicActiveContourLevelSetImageFilter.html>`_
     - Segments structures in images based on a user supplied edge potential map.
   * - `GradientAnisotropicDiffusionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GradientAnisotropicDiffusionImageFilter.html>`_
     -
   * - `GradientImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GradientImageFilter.html>`_
     - Computes the gradient of an image using directional derivatives.
   * - `GradientMagnitudeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GradientMagnitudeImageFilter.html>`_
     - Computes the gradient magnitude of an image region at each pixel.
   * - `GradientMagnitudeRecursiveGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GradientMagnitudeRecursiveGaussianImageFilter.html>`_
     - Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.
   * - `GradientRecursiveGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GradientRecursiveGaussianImageFilter.html>`_
     - Computes the gradient of an image by convolution with the first derivative of a Gaussian.
   * - `GrayscaleConnectedClosingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleConnectedClosingImageFilter.html>`_
     - Enhance pixels associated with a dark object (identified by a seed pixel) where the dark object is surrounded by a brighter object.
   * - `GrayscaleConnectedOpeningImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleConnectedOpeningImageFilter.html>`_
     - Enhance pixels associated with a bright object (identified by a seed pixel) where the bright object is surrounded by a darker object.
   * - `GrayscaleDilateImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleDilateImageFilter.html>`_
     - Grayscale dilation of an image.
   * - `GrayscaleErodeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleErodeImageFilter.html>`_
     - Grayscale erosion of an image.
   * - `GrayscaleFillholeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleFillholeImageFilter.html>`_
     - Remove local minima not connected to the boundary of the image.
   * - `GrayscaleGeodesicDilateImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleGeodesicDilateImageFilter.html>`_
     - geodesic gray scale dilation of an image
   * - `GrayscaleGeodesicErodeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleGeodesicErodeImageFilter.html>`_
     - geodesic gray scale erosion of an image
   * - `GrayscaleGrindPeakImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleGrindPeakImageFilter.html>`_
     - Remove local maxima not connected to the boundary of the image.
   * - `GrayscaleMorphologicalClosingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleMorphologicalClosingImageFilter.html>`_
     - gray scale dilation of an image
   * - `GrayscaleMorphologicalOpeningImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GrayscaleMorphologicalOpeningImageFilter.html>`_
     - gray scale dilation of an image
   * - `GreaterEqualImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `GreaterImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `GridImageSource <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1GridImageSource.html>`_
     - Generate an n-dimensional image of a grid.
   * - `HConcaveImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HConcaveImageFilter.html>`_
     - Identify local minima whose depth below the baseline is greater than h.
   * - `HConvexImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HConvexImageFilter.html>`_
     - Identify local maxima whose height above the baseline is greater than h.
   * - `HMaximaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HMaximaImageFilter.html>`_
     - Suppress local maxima whose height above the baseline is less than h.
   * - `HMinimaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HMinimaImageFilter.html>`_
     - Suppress local minima whose depth below the baseline is less than h.
   * - `HalfHermitianToRealInverseFFTImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HalfHermitianToRealInverseFFTImageFilter.html>`_
     - Base class for specialized complex-to-real inverse Fast Fourier Transform .
   * - `HausdorffDistanceImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HausdorffDistanceImageFilter.html>`_
     - Computes the Hausdorff distance between the set of non-zero pixels of two images.
   * - `HistogramMatchingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HistogramMatchingImageFilter.html>`_
     - Normalize the grayscale values between two images by histogram matching.
   * - `HuangThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1HuangThresholdImageFilter.html>`_
     - Threshold an image using the Huang Threshold.
   * - `IntensityWindowingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IntensityWindowingImageFilter.html>`_
     - Applies a linear transformation to the intensity levels of the input Image that are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.
   * - `IntermodesThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IntermodesThresholdImageFilter.html>`_
     - Threshold an image using the Intermodes Threshold.
   * - `InverseDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1InverseDeconvolutionImageFilter.html>`_
     - The direct linear inverse deconvolution filter.
   * - `InverseDisplacementFieldImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1InverseDisplacementFieldImageFilter.html>`_
     - Computes the inverse of a displacement field.
   * - `InverseFFTImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1InverseFFTImageFilter.html>`_
     - Base class for inverse Fast Fourier Transform .
   * - `InvertDisplacementFieldImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1InvertDisplacementFieldImageFilter.html>`_
     - Iteratively estimate the inverse field of a displacement field.
   * - `InvertIntensityImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1InvertIntensityImageFilter.html>`_
     - Invert the intensity of an image.
   * - `IsoContourDistanceImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IsoContourDistanceImageFilter.html>`_
     - Compute an approximate distance from an interpolated isocontour to the close grid points.
   * - `IsoDataThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IsoDataThresholdImageFilter.html>`_
     - Threshold an image using the IsoData Threshold.
   * - `IsolatedConnectedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IsolatedConnectedImageFilter.html>`_
     - Label pixels that are connected to one set of seeds but not another.
   * - `IsolatedWatershedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IsolatedWatershedImageFilter.html>`_
     - Isolate watershed basins using two seeds.
   * - `IterativeInverseDisplacementFieldImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1IterativeInverseDisplacementFieldImageFilter.html>`_
     - Computes the inverse of a displacement field.
   * - `JoinSeriesImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1JoinSeriesImageFilter.html>`_
     - Join N-D images into an (N+1)-D image.
   * - `KittlerIllingworthThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1KittlerIllingworthThresholdImageFilter.html>`_
     - Threshold an image using the KittlerIllingworth Threshold.
   * - `LabelContourImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelContourImageFilter.html>`_
     - Labels the pixels on the border of the objects in a labeled image.
   * - `LabelImageToLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelImageToLabelMapFilter.html>`_
     - convert a labeled image to a label collection image
   * - `LabelIntensityStatisticsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelImageToStatisticsLabelMapFilter.html>`_
     - a convenient class to convert a label image to a label map and valuate the statistics attributes at once
   * - `LabelMapContourOverlayImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapContourOverlayImageFilter.html>`_
     - Apply a colormap to the contours (outlines) of each object in a label map and superimpose it on top of the feature image.
   * - `LabelMapMaskImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapMaskImageFilter.html>`_
     - Mask and image with a LabelMap .
   * - `LabelMapOverlayImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapOverlayImageFilter.html>`_
     - Apply a colormap to a label map and superimpose it on an image.
   * - `LabelMapToBinaryImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapToBinaryImageFilter.html>`_
     - Convert a LabelMap to a binary image.
   * - `LabelMapToLabelImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapToLabelImageFilter.html>`_
     - Converts a LabelMap to a labeled image.
   * - `LabelMapToRGBImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelMapToRGBImageFilter.html>`_
     - Convert a LabelMap to a colored image.
   * - `LabelOverlapMeasuresImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelOverlapMeasuresImageFilter.html>`_
     - Computes overlap measures between the set same set of labels of pixels of two images. Background is assumed to be 0.
   * - `LabelOverlayImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelOverlayImageFilter.html>`_
     - Apply a colormap to a label image and put it on top of the input image.
   * - `LabelSetDilateImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelSetDilateImageFilter.html>`_
     - Class for binary morphological erosion of label images.
   * - `LabelSetErodeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelSetErodeImageFilter.html>`_
     - Class for binary morphological erosion of label images.
   * - `LabelShapeStatisticsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelImageToShapeLabelMapFilter.html>`_
     - Converts a label image to a label map and valuates the shape attributes.
   * - `LabelStatisticsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelStatisticsImageFilter.html>`_
     - Given an intensity image and a label map, compute min, max, variance and mean of the pixels associated with each label or segment.
   * - `LabelToRGBImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelToRGBImageFilter.html>`_
     - Apply a colormap to a label image.
   * - `LabelUniqueLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelUniqueLabelMapFilter.html>`_
     - Make sure that the objects are not overlapping.
   * - `LabelVotingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LabelVotingImageFilter.html>`_
     - This filter performs pixelwise voting among an arbitrary number of input images, where each of them represents a segmentation of the same scene (i.e., image).
   * - `LandweberDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LandweberDeconvolutionImageFilter.html>`_
     - Deconvolve an image using the Landweber deconvolution algorithm.
   * - `LaplacianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LaplacianImageFilter.html>`_
     -
   * - `LaplacianRecursiveGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LaplacianRecursiveGaussianImageFilter.html>`_
     - Computes the Laplacian of Gaussian (LoG) of an image.
   * - `LaplacianSegmentationLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LaplacianSegmentationLevelSetImageFilter.html>`_
     - Segments structures in images based on a second derivative image features.
   * - `LaplacianSharpeningImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LaplacianSharpeningImageFilter.html>`_
     - This filter sharpens an image using a Laplacian. LaplacianSharpening highlights regions of rapid intensity change and therefore highlights or enhances the edges. The result is an image that appears more in focus.
   * - `LessEqualImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `LessImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `LevelSetMotionRegistrationFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LevelSetMotionRegistrationFilter.html>`_
     - Deformably register two images using level set motion.
   * - `LiThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LiThresholdImageFilter.html>`_
     - Threshold an image using the Li Threshold.
   * - `Log10ImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Log10ImageFilter.html>`_
     - Computes the log10 of each pixel.
   * - `LogImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1LogImageFilter.html>`_
     - Computes the log() of each pixel.
   * - `MagnitudeAndPhaseToComplexImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MagnitudeAndPhaseToComplexImageFilter.html>`_
     - Implements pixel-wise conversion of magnitude and phase data into complex voxels.
   * - `MaskImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaskImageFilter.html>`_
     - Mask an image with a mask.
   * - `MaskNegatedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaskNegatedImageFilter.html>`_
     - Mask an image with the negation (or logical compliment) of a mask.
   * - `MaskedFFTNormalizedCorrelationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaskedFFTNormalizedCorrelationImageFilter.html>`_
     - Calculate masked normalized cross correlation using FFTs.
   * - `MaximumEntropyThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaximumEntropyThresholdImageFilter.html>`_
     - Threshold an image using the MaximumEntropy Threshold.
   * - `MaximumImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaximumImageFilter.html>`_
     - Implements a pixel-wise operator Max(a,b) between two images.
   * - `MaximumProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MaximumProjectionImageFilter.html>`_
     - Maximum projection.
   * - `MeanImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MeanImageFilter.html>`_
     - Applies an averaging filter to an image.
   * - `MeanProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MeanProjectionImageFilter.html>`_
     - Mean projection.
   * - `MedianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MedianImageFilter.html>`_
     - Applies a median filter to an image.
   * - `MedianProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MedianProjectionImageFilter.html>`_
     - Median projection.
   * - `MergeLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MergeLabelMapFilter.html>`_
     - Merges several Label Maps.
   * - `MinMaxCurvatureFlowImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MinMaxCurvatureFlowImageFilter.html>`_
     - Denoise an image using min/max curvature flow.
   * - `MinimumImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MinimumImageFilter.html>`_
     - Implements a pixel-wise operator Min(a,b) between two images.
   * - `MinimumMaximumImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MinimumMaximumImageFilter.html>`_
     - Computes the minimum and the maximum intensity values of an image.
   * - `MinimumProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MinimumProjectionImageFilter.html>`_
     - Minimum projection.
   * - `MirrorPadImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MirrorPadImageFilter.html>`_
     - Increase the image size by padding with replicants of the input image value.
   * - `ModulusImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ModulusImageFilter.html>`_
     - Computes the modulus (x % dividend) pixel-wise.
   * - `MomentsThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MomentsThresholdImageFilter.html>`_
     - Threshold an image using the Moments Threshold.
   * - `MorphologicalGradientImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MorphologicalGradientImageFilter.html>`_
     - gray scale dilation of an image
   * - `MorphologicalWatershedFromMarkersImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MorphologicalWatershedFromMarkersImageFilter.html>`_
     - Morphological watershed transform from markers.
   * - `MorphologicalWatershedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MorphologicalWatershedImageFilter.html>`_
     - Watershed segmentation implementation with morphological operators.
   * - `MultiLabelSTAPLEImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MultiLabelSTAPLEImageFilter.html>`_
     - This filter performs a pixelwise combination of an arbitrary number of input images, where each of them represents a segmentation of the same scene (i.e., image).
   * - `MultiplyImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1MultiplyImageFilter.html>`_
     - Pixel-wise multiplication of two images.
   * - `N4BiasFieldCorrectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1N4BiasFieldCorrectionImageFilter.html>`_
     - Implementation of the N4 bias field correction algorithm.
   * - `NaryAddImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NaryAddImageFilter.html>`_
     - Pixel-wise addition of N images.
   * - `NaryMaximumImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NaryMaximumImageFilter.html>`_
     - Computes the pixel-wise maximum of several images.
   * - `NeighborhoodConnectedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NeighborhoodConnectedImageFilter.html>`_
     - Label pixels that are connected to a seed and lie within a neighborhood.
   * - `NoiseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NoiseImageFilter.html>`_
     - Calculate the local noise in an image.
   * - `NormalizeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NormalizeImageFilter.html>`_
     - Normalize an image by setting its mean to zero and variance to one.
   * - `NormalizeToConstantImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NormalizeToConstantImageFilter.html>`_
     - Scales image pixel intensities to make the sum of all pixels equal a user-defined constant.
   * - `NormalizedCorrelationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NormalizedCorrelationImageFilter.html>`_
     - Computes the normalized correlation of an image and a template.
   * - `NotEqualImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1BinaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation of two images, or of an image and a constant.
   * - `NotImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1NotImageFilter.html>`_
     - Implements the NOT logical operator pixel-wise on an image.
   * - `ObjectnessMeasureImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ObjectnessMeasureImageFilter.html>`_
     - Enhance M-dimensional objects in N-dimensional images.
   * - `OpeningByReconstructionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1OpeningByReconstructionImageFilter.html>`_
     - Opening by reconstruction of an image.
   * - `OrImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1OrImageFilter.html>`_
     - Implements the OR bitwise operator pixel-wise between two images.
   * - `OtsuMultipleThresholdsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1OtsuMultipleThresholdsImageFilter.html>`_
     - Threshold an image using multiple Otsu Thresholds.
   * - `OtsuThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1OtsuThresholdImageFilter.html>`_
     - Threshold an image using the Otsu Threshold.
   * - `PasteImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1PasteImageFilter.html>`_
     - Paste an image into another image.
   * - `PatchBasedDenoisingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1PatchBasedDenoisingImageFilter.html>`_
     - Derived class implementing a specific patch-based denoising algorithm, as detailed below.
   * - `PermuteAxesImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1PermuteAxesImageFilter.html>`_
     - Permutes the image axes according to a user specified order.
   * - `PhysicalPointImageSource <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1PhysicalPointImageSource.html>`_
     - Generate an image of the physical locations of each pixel.
   * - `PowImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1PowImageFilter.html>`_
     - Computes the powers of 2 images.
   * - `ProjectedLandweberDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ProjectedLandweberDeconvolutionImageFilter.html>`_
     - Deconvolve an image using the projected Landweber deconvolution algorithm.
   * - `RankImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RankImageFilter.html>`_
     - Rank filter of a greyscale image.
   * - `RealAndImaginaryToComplexImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ComposeImageFilter.html>`_
     - ComposeImageFilter combine several scalar images into a multicomponent image.
   * - `RealToHalfHermitianForwardFFTImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RealToHalfHermitianForwardFFTImageFilter.html>`_
     - Base class for specialized real-to-complex forward Fast Fourier Transform .
   * - `ReconstructionByDilationImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ReconstructionByDilationImageFilter.html>`_
     - grayscale reconstruction by dilation of an image
   * - `ReconstructionByErosionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ReconstructionByErosionImageFilter.html>`_
     - grayscale reconstruction by erosion of an image
   * - `RecursiveGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RecursiveGaussianImageFilter.html>`_
     - Base class for computing IIR convolution with an approximation of a Gaussian kernel.
   * - `RegionOfInterestImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RegionOfInterestImageFilter.html>`_
     - Extract a region of interest from the input image.
   * - `RegionalMaximaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RegionalMaximaImageFilter.html>`_
     - Produce a binary image where foreground is the regional maxima of the input image.
   * - `RegionalMinimaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RegionalMinimaImageFilter.html>`_
     - Produce a binary image where foreground is the regional minima of the input image.
   * - `RelabelComponentImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RelabelComponentImageFilter.html>`_
     - Relabel the components in an image such that consecutive labels are used.
   * - `RelabelLabelMapFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RelabelLabelMapFilter.html>`_
     - This filter relabels the LabelObjects; the new labels are arranged consecutively with consideration for the background value.
   * - `RenyiEntropyThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RenyiEntropyThresholdImageFilter.html>`_
     - Threshold an image using the RenyiEntropy Threshold.
   * - `ResampleImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ResampleImageFilter.html>`_
     - Resample an image via a coordinate transform.
   * - `RescaleIntensityImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RescaleIntensityImageFilter.html>`_
     - Applies a linear transformation to the intensity levels of the input Image .
   * - `RichardsonLucyDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RichardsonLucyDeconvolutionImageFilter.html>`_
     - Deconvolve an image using the Richardson-Lucy deconvolution algorithm.
   * - `RoundImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1RoundImageFilter.html>`_
     - Rounds the value of each pixel.
   * - `SLICImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SLICImageFilter.html>`_
     - Simple Linear Iterative Clustering (SLIC) super-pixel segmentation.
   * - `STAPLEImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1STAPLEImageFilter.html>`_
     - The STAPLE filter implements the Simultaneous Truth and Performance Level Estimation algorithm for generating ground truth volumes from a set of binary expert segmentations.
   * - `SaltAndPepperNoiseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SaltAndPepperNoiseImageFilter.html>`_
     - Alter an image with fixed value impulse noise, often called salt and pepper noise.
   * - `ScalarChanAndVeseDenseLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScalarChanAndVeseDenseLevelSetImageFilter.html>`_
     - Dense implementation of the Chan and Vese multiphase level set image filter.
   * - `ScalarConnectedComponentImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScalarConnectedComponentImageFilter.html>`_
     - A connected components filter that labels the objects in an arbitrary image. Two pixels are similar if they are within threshold of each other. Uses ConnectedComponentFunctorImageFilter .
   * - `ScalarImageKmeansImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScalarImageKmeansImageFilter.html>`_
     - Classifies the intensity values of a scalar image using the K-Means algorithm.
   * - `ScalarToRGBColormapImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ScalarToRGBColormapImageFilter.html>`_
     - Implements pixel-wise intensity->rgb mapping operation on one image.
   * - `ShanbhagThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ShanbhagThresholdImageFilter.html>`_
     - Threshold an image using the Shanbhag Threshold.
   * - `ShapeDetectionLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ShapeDetectionLevelSetImageFilter.html>`_
     - Segments structures in images based on a user supplied edge potential map.
   * - `ShiftScaleImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ShiftScaleImageFilter.html>`_
     - Shift and scale the pixels in an image.
   * - `ShotNoiseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ShotNoiseImageFilter.html>`_
     - Alter an image with shot noise.
   * - `ShrinkImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ShrinkImageFilter.html>`_
     - Reduce the size of an image by an integer factor in each dimension.
   * - `SigmoidImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SigmoidImageFilter.html>`_
     - Computes the sigmoid function pixel-wise.
   * - `SignedDanielssonDistanceMapImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SignedDanielssonDistanceMapImageFilter.html>`_
     -
   * - `SignedMaurerDistanceMapImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SignedMaurerDistanceMapImageFilter.html>`_
     - This filter calculates the Euclidean distance transform of a binary image in linear time for arbitrary dimensions.
   * - `SimilarityIndexImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SimilarityIndexImageFilter.html>`_
     - Measures the similarity between the set of non-zero pixels of two images.
   * - `SimpleContourExtractorImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SimpleContourExtractorImageFilter.html>`_
     - Computes an image of contours which will be the contour of the first image.
   * - `SinImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SinImageFilter.html>`_
     - Computes the sine of each pixel.
   * - `SliceImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SliceImageFilter.html>`_
     - Slices an image based on a starting index and a stopping index, and a step size.
   * - `SmoothingRecursiveGaussianImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SmoothingRecursiveGaussianImageFilter.html>`_
     - Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.
   * - `SobelEdgeDetectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SobelEdgeDetectionImageFilter.html>`_
     - A 2D or 3D edge detection using the Sobel operator.
   * - `SpeckleNoiseImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SpeckleNoiseImageFilter.html>`_
     - Alter an image with speckle (multiplicative) noise.
   * - `SqrtImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SqrtImageFilter.html>`_
     - Computes the square root of each pixel.
   * - `SquareImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SquareImageFilter.html>`_
     - Computes the square of the intensity values pixel-wise.
   * - `SquaredDifferenceImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SquaredDifferenceImageFilter.html>`_
     - Implements pixel-wise the computation of squared difference.
   * - `StandardDeviationProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1StandardDeviationProjectionImageFilter.html>`_
     - Mean projection.
   * - `StatisticsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1StatisticsImageFilter.html>`_
     - Compute min. max, variance and mean of an Image .
   * - `StochasticFractalDimensionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1StochasticFractalDimensionImageFilter.html>`_
     - This filter computes the stochastic fractal dimension of the input image.
   * - `SubtractImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SubtractImageFilter.html>`_
     - Pixel-wise subtraction of two images.
   * - `SumProjectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SumProjectionImageFilter.html>`_
     - Sum projection.
   * - `SymmetricForcesDemonsRegistrationFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1SymmetricForcesDemonsRegistrationFilter.html>`_
     - Deformably register two images using the demons algorithm.
   * - `TanImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TanImageFilter.html>`_
     - Computes the tangent of each input pixel.
   * - `TernaryAddImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TernaryAddImageFilter.html>`_
     - Pixel-wise addition of three images.
   * - `TernaryMagnitudeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TernaryMagnitudeImageFilter.html>`_
     - Compute the pixel-wise magnitude of three images.
   * - `TernaryMagnitudeSquaredImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TernaryMagnitudeSquaredImageFilter.html>`_
     - Compute the pixel-wise squared magnitude of three images.
   * - `ThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ThresholdImageFilter.html>`_
     - Set image values to a user-specified value if they are below, above, or between simple threshold values.
   * - `ThresholdMaximumConnectedComponentsImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ThresholdMaximumConnectedComponentsImageFilter.html>`_
     - Finds the threshold value of an image based on maximizing the number of objects in the image that are larger than a given minimal size.
   * - `ThresholdSegmentationLevelSetImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ThresholdSegmentationLevelSetImageFilter.html>`_
     - Segments structures in images based on intensity values.
   * - `TikhonovDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TikhonovDeconvolutionImageFilter.html>`_
     - An inverse deconvolution filter regularized in the Tikhonov sense.
   * - `TileImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TileImageFilter.html>`_
     - Tile multiple input images into a single output image.
   * - `TobogganImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TobogganImageFilter.html>`_
     - toboggan image segmentation The Toboggan segmentation takes a gradient magnitude image as input and produces an (over-)segmentation of the image based on connecting each pixel to a local minimum of gradient. It is roughly equivalent to a watershed segmentation of the lowest level.
   * - `TransformToDisplacementFieldFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TransformToDisplacementFieldFilter.html>`_
     - Generate a displacement field from a coordinate transform.
   * - `TriangleThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1TriangleThresholdImageFilter.html>`_
     - Threshold an image using the Triangle Threshold.
   * - `UnaryMinusImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1UnaryFunctorImageFilter.html>`_
     - Implements pixel-wise generic operation on one image.
   * - `UnsharpMaskImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1UnsharpMaskImageFilter.html>`_
     - Edge enhancement filter.
   * - `ValuedRegionalMaximaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ValuedRegionalMaximaImageFilter.html>`_
     - Transforms the image so that any pixel that is not a regional maxima is set to the minimum value for the pixel type. Pixels that are regional maxima retain their value.
   * - `ValuedRegionalMinimaImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ValuedRegionalMinimaImageFilter.html>`_
     - Transforms the image so that any pixel that is not a regional minima is set to the maximum value for the pixel type. Pixels that are regional minima retain their value.
   * - `VectorConfidenceConnectedImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VectorConfidenceConnectedImageFilter.html>`_
     - Segment pixels with similar statistics using connectivity.
   * - `VectorConnectedComponentImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VectorConnectedComponentImageFilter.html>`_
     - A connected components filter that labels the objects in a vector image. Two vectors are pointing similar directions if one minus their dot product is less than a threshold. Vectors that are 180 degrees out of phase are similar. Assumes that vectors are normalized.
   * - `VectorIndexSelectionCastImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VectorIndexSelectionCastImageFilter.html>`_
     - Extracts the selected index of the vector that is the input pixel type.
   * - `VectorMagnitudeImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VectorMagnitudeImageFilter.html>`_
     - Take an image of vectors as input and produce an image with the magnitude of those vectors.
   * - `VotingBinaryHoleFillingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VotingBinaryHoleFillingImageFilter.html>`_
     - Fills in holes and cavities by applying a voting operation on each pixel.
   * - `VotingBinaryImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VotingBinaryImageFilter.html>`_
     - Applies a voting operation in a neighborhood of each pixel.
   * - `VotingBinaryIterativeHoleFillingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1VotingBinaryIterativeHoleFillingImageFilter.html>`_
     - Fills in holes and cavities by iteratively applying a voting operation.
   * - `WarpImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1WarpImageFilter.html>`_
     - Warps an image using an input displacement field.
   * - `WhiteTopHatImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1WhiteTopHatImageFilter.html>`_
     - White top hat extracts local maxima that are larger than the structuring element.
   * - `WienerDeconvolutionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1WienerDeconvolutionImageFilter.html>`_
     - The Wiener deconvolution image filter is designed to restore an image convolved with a blurring kernel while keeping noise enhancement to a minimum.
   * - `WrapPadImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1WrapPadImageFilter.html>`_
     - Increase the image size by padding with replicants of the input image value.
   * - `XorImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1XorImageFilter.html>`_
     - Computes the XOR bitwise operator pixel-wise between two images.
   * - `YenThresholdImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1YenThresholdImageFilter.html>`_
     - Threshold an image using the Yen Threshold.
   * - `ZeroCrossingBasedEdgeDetectionImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ZeroCrossingBasedEdgeDetectionImageFilter.html>`_
     - This filter implements a zero-crossing based edge detecor.
   * - `ZeroCrossingImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ZeroCrossingImageFilter.html>`_
     - This filter finds the closest pixel to the zero-crossings (sign changes) in a signed itk::Image .
   * - `ZeroFluxNeumannPadImageFilter <https://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ZeroFluxNeumannPadImageFilter.html>`_
     - Increase the image size by padding according to the zero-flux Neumann boundary condition.
