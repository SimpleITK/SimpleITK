// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AbsImageFilter.xml
%typemap(javaimports) itk::simple::AbsImageFilter "/** Computes the ABS(x) pixel-wise.


li {ImageProcessing/AbsImageFilter,Compute the absolute value of an image}

*/"
%javamethodmodifiers itk::simple::AbsImageFilter::execute() "
/**Computes the ABS(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Abs "/**
Computes the ABS(x) pixel-wise.


li {ImageProcessing/AbsImageFilter,Compute the absolute value of an image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AbsoluteValueDifferenceImageFilter.xml
%typemap(javaimports) itk::simple::AbsoluteValueDifferenceImageFilter "/** Implements pixel-wise the computation of absolute value difference.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the difference of the two pixel values
li compute the absolute value of the difference
li cast the double value resulting from the absolute value to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
%javamethodmodifiers itk::simple::AbsoluteValueDifferenceImageFilter::execute() "
/**Implements pixel-wise the computation of absolute value difference.

*/"
%javamethodmodifiers itk::simple::AbsoluteValueDifference "/**
Implements pixel-wise the computation of absolute value difference.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the difference of the two pixel values
li compute the absolute value of the difference
li cast the double value resulting from the absolute value to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AcosImageFilter.xml
%typemap(javaimports) itk::simple::AcosImageFilter "/** Computes the vcl_acos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_acos() function to the double value
li cast the double value resulting from vcl_acos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND).
*/"
%javamethodmodifiers itk::simple::AcosImageFilter::execute() "
/**Computes the vcl_acos(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Acos "/**
Computes the vcl_acos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_acos() function to the double value
li cast the double value resulting from vcl_acos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND).
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AddConstantToImageFilter.xml
%typemap(javaimports) itk::simple::AddConstantToImageFilter "/** Add a constant to all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
Based on filters from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter
li {ImageProcessing/AddConstantToImageFilter,Add a constant to every pixel in an image}


*/"
%javamethodmodifiers itk::simple::AddConstantToImageFilter::execute() "
/**Add a constant to all input pixels.

*/"
%javamethodmodifiers itk::simple::AddConstantTo "/**
Add a constant to all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
Based on filters from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter
li {ImageProcessing/AddConstantToImageFilter,Add a constant to every pixel in an image}


*/"
%javamethodmodifiers itk::simple::AddConstantToImageFilter::setConstant "/**
void itk::AddConstantToImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
*/"

%javamethodmodifiers itk::simple::AddConstantToImageFilter::getConstant "/**
const TConstant& itk::AddConstantToImageFilter::GetConstant() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AddImageFilter.xml
%typemap(javaimports) itk::simple::AddImageFilter "/** Implements an operator for pixel-wise addition of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 1 image must have a valid defintion of the operator+ with a pixel type of the image 2. This condition is required because internally this filter will perform the operation
pixel_from_image_1 + pixel_from_image_2
Additionally the type resulting from the sum, will be cast to the pixel type of the output image.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel + input2_pixel )
For example, this filter could be used directly for adding images whose pixels are vectors of the same dimension, and to store the resulting vector in an output image of vector pixels.
The images to be added are set using the methods: SetInput1( image1 ); SetInput2( image2 );
warning No numeric overflow checking is performed in this filter.

li {ImageProcessing/AddImageFilter,Add two images together}

*/"
%javamethodmodifiers itk::simple::AddImageFilter::execute() "
/**Implements an operator for pixel-wise addition of two images.

*/"
%javamethodmodifiers itk::simple::Add "/**
Implements an operator for pixel-wise addition of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 1 image must have a valid defintion of the operator+ with a pixel type of the image 2. This condition is required because internally this filter will perform the operation
pixel_from_image_1 + pixel_from_image_2
Additionally the type resulting from the sum, will be cast to the pixel type of the output image.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel + input2_pixel )
For example, this filter could be used directly for adding images whose pixels are vectors of the same dimension, and to store the resulting vector in an output image of vector pixels.
The images to be added are set using the methods: SetInput1( image1 ); SetInput2( image2 );
warning No numeric overflow checking is performed in this filter.

li {ImageProcessing/AddImageFilter,Add two images together}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AndImageFilter.xml
%typemap(javaimports) itk::simple::AndImageFilter "/** Implements the AND logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical AND operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel & input2_pixel )
Where & is the boolean AND operator in C++.

li {ImageProcessing/AndImageFilter,Binary AND two images}

*/"
%javamethodmodifiers itk::simple::AndImageFilter::execute() "
/**Implements the AND logical operator pixel-wise between two images.

*/"
%javamethodmodifiers itk::simple::And "/**
Implements the AND logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical AND operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel & input2_pixel )
Where & is the boolean AND operator in C++.

li {ImageProcessing/AndImageFilter,Binary AND two images}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ApproximateSignedDistanceMapImageFilter.xml
%typemap(javaimports) itk::simple::ApproximateSignedDistanceMapImageFilter "/** Create a map of the approximate signed distance from the boundaries of a binary image.

The ApproximateSignedDistanceMapImageFiltertakes as input a binary image and produces a signed distance map. Each pixel value in the output contains the approximate distance from that pixel to the nearest object in the binary image. This filter differs from the DanielssonDistanceMapImageFilterin that it calculates the distance to the object edge for pixels within the object.
Negative values in the output indicate that the pixel at that position is within an object in the input image. The absolute value of a negative pixel represents the approximate distance to the nearest object boundary pixel.
WARNING: This filter requires that the output type be floating-point. Otherwise internal calculations will not be performed to the appropriate precision, resulting in completely incorrect (read: zero-valued) output.
The distances computed by this filter are Chamfer distances, which are only an approximation to Euclidian distances, and are not as exact approximations as those calculated by the DanielssonDistanceMapImageFilter. On the other hand, this filter is faster.
This filter requires that an inside value and outside value be set as parameters. The inside value is the intensity value of the binary image which corresponds to objects, and the outside value is the intensity of the background. (A typical binary image often repesents objects as black (0) and background as white (usually 255), or vice-versa.) Note that this filter is slightly faster if the inside value is less than the outside value. Otherwise an extra iteration through the image is required.
This filter uses the FastChamferDistanceImageFilterand the IsoContourDistanceImageFilterinernally to perform the distance calculations.
see  DanielssonDistanceMapImageFilter, SignedDanielssonDistanceMapImageFilter
see  FastChamferDistanceImageFilter, IsoContourDistanceImageFilter
author Zach Pincus

*/"
%javamethodmodifiers itk::simple::ApproximateSignedDistanceMapImageFilter::execute() "
/**Create a map of the approximate signed distance from the boundaries of a binary image.

*/"
%javamethodmodifiers itk::simple::ApproximateSignedDistanceMap "/**
Create a map of the approximate signed distance from the boundaries of a binary image.

The ApproximateSignedDistanceMapImageFiltertakes as input a binary image and produces a signed distance map. Each pixel value in the output contains the approximate distance from that pixel to the nearest object in the binary image. This filter differs from the DanielssonDistanceMapImageFilterin that it calculates the distance to the object edge for pixels within the object.
Negative values in the output indicate that the pixel at that position is within an object in the input image. The absolute value of a negative pixel represents the approximate distance to the nearest object boundary pixel.
WARNING: This filter requires that the output type be floating-point. Otherwise internal calculations will not be performed to the appropriate precision, resulting in completely incorrect (read: zero-valued) output.
The distances computed by this filter are Chamfer distances, which are only an approximation to Euclidian distances, and are not as exact approximations as those calculated by the DanielssonDistanceMapImageFilter. On the other hand, this filter is faster.
This filter requires that an inside value and outside value be set as parameters. The inside value is the intensity value of the binary image which corresponds to objects, and the outside value is the intensity of the background. (A typical binary image often repesents objects as black (0) and background as white (usually 255), or vice-versa.) Note that this filter is slightly faster if the inside value is less than the outside value. Otherwise an extra iteration through the image is required.
This filter uses the FastChamferDistanceImageFilterand the IsoContourDistanceImageFilterinernally to perform the distance calculations.
see  DanielssonDistanceMapImageFilter, SignedDanielssonDistanceMapImageFilter
see  FastChamferDistanceImageFilter, IsoContourDistanceImageFilter
author Zach Pincus

*/"
%javamethodmodifiers itk::simple::ApproximateSignedDistanceMapImageFilter::setInsideValue "/**
virtual void itk::ApproximateSignedDistanceMapImageFilter::SetInsideValue(InputPixelType _arg)

Set/Get intensity value representing the interior of objects in the mask
*/"

%javamethodmodifiers itk::simple::ApproximateSignedDistanceMapImageFilter::getInsideValue "/**
virtual InputPixelType itk::ApproximateSignedDistanceMapImageFilter::GetInsideValue() const

*/"

%javamethodmodifiers itk::simple::ApproximateSignedDistanceMapImageFilter::setOutsideValue "/**
virtual void itk::ApproximateSignedDistanceMapImageFilter::SetOutsideValue(InputPixelType _arg)

Set/Get intensity value representing non-objects in the mask
*/"

%javamethodmodifiers itk::simple::ApproximateSignedDistanceMapImageFilter::getOutsideValue "/**
virtual InputPixelType itk::ApproximateSignedDistanceMapImageFilter::GetOutsideValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AsinImageFilter.xml
%typemap(javaimports) itk::simple::AsinImageFilter "/** Computes the vcl_asin(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_asin() function to the double value
li cast the double value resulting from vcl_asin() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
%javamethodmodifiers itk::simple::AsinImageFilter::execute() "
/**Computes the vcl_asin(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Asin "/**
Computes the vcl_asin(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_asin() function to the double value
li cast the double value resulting from vcl_asin() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1Atan2ImageFilter.xml
%typemap(javaimports) itk::simple::Atan2ImageFilter "/** Computes arctangent pixel-wise from two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Both pixel input types are casted to double in order to be used as parameters of vcl_atan2() . The resulting double value is casted to the output pixel type.
*/"
%javamethodmodifiers itk::simple::Atan2ImageFilter::execute() "
/**Computes arctangent pixel-wise from two images.

*/"
%javamethodmodifiers itk::simple::Atan2 "/**
Computes arctangent pixel-wise from two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Both pixel input types are casted to double in order to be used as parameters of vcl_atan2() . The resulting double value is casted to the output pixel type.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AtanImageFilter.xml
%typemap(javaimports) itk::simple::AtanImageFilter "/** Computes the vcl_atan(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_atan() function to the double value
li cast the double value resulting from vcl_atan() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
%javamethodmodifiers itk::simple::AtanImageFilter::execute() "
/**Computes the vcl_atan(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Atan "/**
Computes the vcl_atan(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_atan() function to the double value
li cast the double value resulting from vcl_atan() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BilateralImageFilter.xml
%typemap(javaimports) itk::simple::BilateralImageFilter "/** Blurs an image while preserving edges.

This filter uses bilateral filtering to blur an image using both domain and range neighborhoods. Pixels that are close to a pixel in the image domain and similar to a pixel in the image range are used to calculate the filtered value. Two gaussian kernels (one in the image domain and one in the image range) are used to smooth the image. The result is an image that is smoothed in homogeneous regions yet has edges preserved. The result is similar to anisotropic diffusion but the implementation in non-iterative. Another benefit to bilateral filtering is that any distance metric can be used for kernel smoothing the image range. Hence, color images can be smoothed as vector images, using the CIE distances between intensity values as the similarity metric (the Gaussian kernel for the image domain is evaluated using CIE distances). A separate version of this filter will be designed for color and vector images.
Bilateral filtering is capable of reducing the noise in an image by an order of magnitude while maintaining edges.
The bilateral operator used here was described by Tomasi and Manduchi (Bilateral Filtering for Gray and ColorImages. IEEE ICCV. 1998.)
see  GaussianOperator
see  RecursiveGaussianImageFilter
see  DiscreteGaussianImageFilter
see  AnisotropicDiffusionImageFilter
see  Image
see  Neighborhood
see  NeighborhoodOperator
TodoSupport color images
Support vector images
li {Smoothing/BilateralImageFilter,Bilateral filter an image}


*/"
%javamethodmodifiers itk::simple::BilateralImageFilter::execute() "
/**Blurs an image while preserving edges.

*/"
%javamethodmodifiers itk::simple::Bilateral "/**
Blurs an image while preserving edges.

This filter uses bilateral filtering to blur an image using both domain and range neighborhoods. Pixels that are close to a pixel in the image domain and similar to a pixel in the image range are used to calculate the filtered value. Two gaussian kernels (one in the image domain and one in the image range) are used to smooth the image. The result is an image that is smoothed in homogeneous regions yet has edges preserved. The result is similar to anisotropic diffusion but the implementation in non-iterative. Another benefit to bilateral filtering is that any distance metric can be used for kernel smoothing the image range. Hence, color images can be smoothed as vector images, using the CIE distances between intensity values as the similarity metric (the Gaussian kernel for the image domain is evaluated using CIE distances). A separate version of this filter will be designed for color and vector images.
Bilateral filtering is capable of reducing the noise in an image by an order of magnitude while maintaining edges.
The bilateral operator used here was described by Tomasi and Manduchi (Bilateral Filtering for Gray and ColorImages. IEEE ICCV. 1998.)
see  GaussianOperator
see  RecursiveGaussianImageFilter
see  DiscreteGaussianImageFilter
see  AnisotropicDiffusionImageFilter
see  Image
see  Neighborhood
see  NeighborhoodOperator
TodoSupport color images
Support vector images
li {Smoothing/BilateralImageFilter,Bilateral filter an image}


*/"
%javamethodmodifiers itk::simple::BilateralImageFilter::setDomainSigma "/**
void itk::BilateralImageFilter::SetDomainSigma(const double v)

Convenience get/set methods for setting all domain parameters to the same values.
*/"

%javamethodmodifiers itk::simple::BilateralImageFilter::getDomainSigma "/**
virtual const ArrayType itk::BilateralImageFilter::GetDomainSigma() const

*/"

%javamethodmodifiers itk::simple::BilateralImageFilter::setRangeSigma "/**
virtual void itk::BilateralImageFilter::SetRangeSigma(double _arg)

*/"

%javamethodmodifiers itk::simple::BilateralImageFilter::getRangeSigma "/**
virtual double itk::BilateralImageFilter::GetRangeSigma() const

*/"

%javamethodmodifiers itk::simple::BilateralImageFilter::setNumberOfRangeGaussianSamples "/**
virtual void itk::BilateralImageFilter::SetNumberOfRangeGaussianSamples(unsigned long _arg)

Set/Get the number of samples in the approximation to the Gaussian used for the range smoothing. Samples are only generated in the range of [0, 4*m_RangeSigma]. Default is 100.
*/"

%javamethodmodifiers itk::simple::BilateralImageFilter::getNumberOfRangeGaussianSamples "/**
virtual unsigned long itk::BilateralImageFilter::GetNumberOfRangeGaussianSamples() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryClosingByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::BinaryClosingByReconstructionImageFilter "/** binary closing by reconstruction of an image.

This filter removes small ( i.e., smaller than the structuring element) holes in the image. It is defined as: Closing(f) = ReconstructionByErosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryClosingByReconstructionImageFilter::execute() "
/**binary closing by reconstruction of an image.

*/"
%javamethodmodifiers itk::simple::BinaryClosingByReconstruction "/**
binary closing by reconstruction of an image.

This filter removes small ( i.e., smaller than the structuring element) holes in the image. It is defined as: Closing(f) = ReconstructionByErosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryClosingByReconstructionImageFilter::setFullyConnected "/**
virtual void itk::BinaryClosingByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::BinaryClosingByReconstructionImageFilter::getFullyConnected "/**
virtual const bool& itk::BinaryClosingByReconstructionImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryContourImageFilter.xml
%typemap(javaimports) itk::simple::BinaryContourImageFilter "/** Labels the pixels on the border of the objects in a binary image.

 BinaryContourImageFiltertakes a binary image as input, where the pixels in the objects are the pixels with a value equal to ForegroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
li {EdgesAndGradients/BinaryContourImageFilter,Extract the boundaries of connected regions in a binary image} {EdgesAndGradients/BinaryBoundaries,Extract the inner and outer boundaries of blobs in a binary image}


*/"
%javamethodmodifiers itk::simple::BinaryContourImageFilter::execute() "
/**Labels the pixels on the border of the objects in a binary image.

*/"
%javamethodmodifiers itk::simple::BinaryContour "/**
Labels the pixels on the border of the objects in a binary image.

 BinaryContourImageFiltertakes a binary image as input, where the pixels in the objects are the pixels with a value equal to ForegroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
li {EdgesAndGradients/BinaryContourImageFilter,Extract the boundaries of connected regions in a binary image} {EdgesAndGradients/BinaryBoundaries,Extract the inner and outer boundaries of blobs in a binary image}


*/"
%javamethodmodifiers itk::simple::BinaryContourImageFilter::setFullyConnected "/**
virtual void itk::BinaryContourImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::BinaryContourImageFilter::getFullyConnected "/**
virtual const bool& itk::BinaryContourImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::BinaryContourImageFilter::setBackgroundValue "/**
virtual void itk::BinaryContourImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the background value used to mark the pixels not on the border of the objects.
*/"

%javamethodmodifiers itk::simple::BinaryContourImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::BinaryContourImageFilter::GetBackgroundValue() const

*/"

%javamethodmodifiers itk::simple::BinaryContourImageFilter::setForegroundValue "/**
virtual void itk::BinaryContourImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set/Get the foreground value used to identify the objects in the input and output images.
*/"

%javamethodmodifiers itk::simple::BinaryContourImageFilter::getForegroundValue "/**
virtual InputImagePixelType itk::BinaryContourImageFilter::GetForegroundValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryDilateImageFilter.xml
%typemap(javaimports) itk::simple::BinaryDilateImageFilter "/** Fast binary dilation.

 BinaryDilateImageFilteris a binary dilation morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a DilateValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. DilateValue defaults to the maximum possible value of the PixelType.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see  ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryDilateImageFilter,Dilate a binary image}


*/"
%javamethodmodifiers itk::simple::BinaryDilateImageFilter::execute() "
/**Fast binary dilation.

*/"
%javamethodmodifiers itk::simple::BinaryDilate "/**
Fast binary dilation.

 BinaryDilateImageFilteris a binary dilation morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a DilateValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. DilateValue defaults to the maximum possible value of the PixelType.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see  ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryDilateImageFilter,Dilate a binary image}


*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryErodeImageFilter.xml
%typemap(javaimports) itk::simple::BinaryErodeImageFilter "/** Fast binary erosion.

 BinaryErodeImageFilteris a binary erosion morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a ErodeValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. ErodeValue defaults to the maximum possible value of the PixelType. The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see  ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryErodeImageFilter,Erode a binary image}


*/"
%javamethodmodifiers itk::simple::BinaryErodeImageFilter::execute() "
/**Fast binary erosion.

*/"
%javamethodmodifiers itk::simple::BinaryErode "/**
Fast binary erosion.

 BinaryErodeImageFilteris a binary erosion morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a ErodeValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. ErodeValue defaults to the maximum possible value of the PixelType. The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see  ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryErodeImageFilter,Erode a binary image}


*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryFillholeImageFilter.xml
%typemap(javaimports) itk::simple::BinaryFillholeImageFilter "/** Remove holes not connected to the boundary of the image.

 BinaryFillholeImageFilterfills holes in a binary image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  GrayscaleFillholeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryFillholeImageFilter::execute() "
/**Remove holes not connected to the boundary of the image.

*/"
%javamethodmodifiers itk::simple::BinaryFillhole "/**
Remove holes not connected to the boundary of the image.

 BinaryFillholeImageFilterfills holes in a binary image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  GrayscaleFillholeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryFillholeImageFilter::setFullyConnected "/**
virtual void itk::BinaryFillholeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::BinaryFillholeImageFilter::getFullyConnected "/**
virtual const bool& itk::BinaryFillholeImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::BinaryFillholeImageFilter::setForegroundValue "/**
virtual void itk::BinaryFillholeImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
*/"

%javamethodmodifiers itk::simple::BinaryFillholeImageFilter::getForegroundValue "/**
virtual InputImagePixelType itk::BinaryFillholeImageFilter::GetForegroundValue()

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryGrindPeakImageFilter.xml
%typemap(javaimports) itk::simple::BinaryGrindPeakImageFilter "/** Remove the objects not connected to the boundary of the image.

 BinaryGrindPeakImageFilterginds peaks in a grayscale image.
Geodesic morphology and the grind peak algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  GrayscaleGrindPeakImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::execute() "
/**Remove the objects not connected to the boundary of the image.

*/"
%javamethodmodifiers itk::simple::BinaryGrindPeak "/**
Remove the objects not connected to the boundary of the image.

 BinaryGrindPeakImageFilterginds peaks in a grayscale image.
Geodesic morphology and the grind peak algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  GrayscaleGrindPeakImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::setFullyConnected "/**
virtual void itk::BinaryGrindPeakImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::getFullyConnected "/**
virtual const bool& itk::BinaryGrindPeakImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::setForegroundValue "/**
virtual void itk::BinaryGrindPeakImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
*/"

%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::getForegroundValue "/**
virtual InputImagePixelType itk::BinaryGrindPeakImageFilter::GetForegroundValue()

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
*/"

%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::setBackgroundValue "/**
virtual void itk::BinaryGrindPeakImageFilter::SetBackgroundValue(InputImagePixelType _arg)

Set the value in eroded part of the image. Defaults to zero
*/"

%javamethodmodifiers itk::simple::BinaryGrindPeakImageFilter::getBackgroundValue "/**
virtual InputImagePixelType itk::BinaryGrindPeakImageFilter::GetBackgroundValue()

Set the value in eroded part of the image. Defaults to zero
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMagnitudeImageFilter.xml
%typemap(javaimports) itk::simple::BinaryMagnitudeImageFilter "/** Implements pixel-wise the computation of square root of the sum of squares.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the sum of squares of the two pixel values
li compute the square root of the sum
li cast the double value resulting from vcl_sqrt() to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
%javamethodmodifiers itk::simple::BinaryMagnitudeImageFilter::execute() "
/**Implements pixel-wise the computation of square root of the sum of squares.

*/"
%javamethodmodifiers itk::simple::BinaryMagnitude "/**
Implements pixel-wise the computation of square root of the sum of squares.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the sum of squares of the two pixel values
li compute the square root of the sum
li cast the double value resulting from vcl_sqrt() to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMinMaxCurvatureFlowImageFilter.xml
%typemap(javaimports) itk::simple::BinaryMinMaxCurvatureFlowImageFilter "/** Denoise a binary image using min/max curvature flow.

 BinaryMinMaxCurvatureFlowImageFilterimplements a curvature driven image denosing algorithm. This filter assumes that the image is essentially binary: consisting of two classes. Iso-brightness contours in the input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = min(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ max(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is a user specified value which discriminates between the two pixel classes.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a BinaryMinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  BinaryMinMaxCurvatureFlowFunction
see  CurvatureFlowImageFilter
see  MinMaxCurvatureFlowImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMinMaxCurvatureFlowImageFilter::execute() "
/**Denoise a binary image using min/max curvature flow.

*/"
%javamethodmodifiers itk::simple::BinaryMinMaxCurvatureFlow "/**
Denoise a binary image using min/max curvature flow.

 BinaryMinMaxCurvatureFlowImageFilterimplements a curvature driven image denosing algorithm. This filter assumes that the image is essentially binary: consisting of two classes. Iso-brightness contours in the input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = min(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ max(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is a user specified value which discriminates between the two pixel classes.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a BinaryMinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  BinaryMinMaxCurvatureFlowFunction
see  CurvatureFlowImageFilter
see  MinMaxCurvatureFlowImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMorphologicalClosingImageFilter.xml
%typemap(javaimports) itk::simple::BinaryMorphologicalClosingImageFilter "/** binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalClosingImageFilter::execute() "
/**binary morphological closing of an image.

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalClosing "/**
binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalClosingImageFilter::setForegroundValue "/**
virtual void itk::BinaryMorphologicalClosingImageFilter::SetForegroundValue(InputPixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
*/"

%javamethodmodifiers itk::simple::BinaryMorphologicalClosingImageFilter::getForegroundValue "/**
virtual InputPixelType itk::BinaryMorphologicalClosingImageFilter::GetForegroundValue() const

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMorphologicalOpeningImageFilter.xml
%typemap(javaimports) itk::simple::BinaryMorphologicalOpeningImageFilter "/** binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) structures in the interior or at the boundaries of the image. The morphological opening of an image f is defined as: Opening(f) = Dilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::execute() "
/**binary morphological closing of an image.

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalOpening "/**
binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) structures in the interior or at the boundaries of the image. The morphological opening of an image f is defined as: Opening(f) = Dilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::setBackgroundValue "/**
virtual void itk::BinaryMorphologicalOpeningImageFilter::SetBackgroundValue(PixelType _arg)

Set the value in eroded part of the image. Defaults to zero
*/"

%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::getBackgroundValue "/**
virtual PixelType itk::BinaryMorphologicalOpeningImageFilter::GetBackgroundValue() const

Set the value in eroded part of the image. Defaults to zero
*/"

%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::setForegroundValue "/**
virtual void itk::BinaryMorphologicalOpeningImageFilter::SetForegroundValue(PixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of PixelType.
*/"

%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::getForegroundValue "/**
virtual PixelType itk::BinaryMorphologicalOpeningImageFilter::GetForegroundValue() const

Get the value in the image considered as foreground. Defaults to maximum value of PixelType.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryOpeningByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::BinaryOpeningByReconstructionImageFilter "/** binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) objects in the image. It is defined as: Opening(f) = ReconstructionByDilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryOpeningByReconstructionImageFilter::execute() "
/**binary morphological closing of an image.

*/"
%javamethodmodifiers itk::simple::BinaryOpeningByReconstruction "/**
binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) objects in the image. It is defined as: Opening(f) = ReconstructionByDilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryOpeningByReconstructionImageFilter::setFullyConnected "/**
virtual void itk::BinaryOpeningByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::BinaryOpeningByReconstructionImageFilter::getFullyConnected "/**
virtual const bool& itk::BinaryOpeningByReconstructionImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryThinningImageFilter.xml
%typemap(javaimports) itk::simple::BinaryThinningImageFilter "/** This filter computes one-pixel-wide edges of the input image.

This class is parametrized over the type of the input image and the type of the output image.
The input is assumed to be a binary image. If the foreground pixels of the input image do not have a value of 1, they are rescaled to 1 internally to simplify the computation.
The filter will produce a skeleton of the object. The output background values are 0, and the foreground values are 1.
This filter is a sequential thinning algorithm and known to be computational time dependable on the image size. The algorithm corresponds with the 2D implementation described in:
Rafael C. Gonzales and Richard E. Woods. Digital ImageProcessing. Addison Wesley, 491-494, (1993).
To do: Make this filter ND.
see  MorphologyImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryThinningImageFilter::execute() "
/**This filter computes one-pixel-wide edges of the input image.

*/"
%javamethodmodifiers itk::simple::BinaryThinning "/**
This filter computes one-pixel-wide edges of the input image.

This class is parametrized over the type of the input image and the type of the output image.
The input is assumed to be a binary image. If the foreground pixels of the input image do not have a value of 1, they are rescaled to 1 internally to simplify the computation.
The filter will produce a skeleton of the object. The output background values are 0, and the foreground values are 1.
This filter is a sequential thinning algorithm and known to be computational time dependable on the image size. The algorithm corresponds with the 2D implementation described in:
Rafael C. Gonzales and Richard E. Woods. Digital ImageProcessing. Addison Wesley, 491-494, (1993).
To do: Make this filter ND.
see  MorphologyImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryThresholdImageFilter.xml
%typemap(javaimports) itk::simple::BinaryThresholdImageFilter "/** Binarize an input image by thresholding.

This filter produces an output image whose pixels are either one of two values ( OutsideValue or InsideValue ), depending on whether the corresponding input image pixels lie between the two thresholds ( LowerThreshold and UpperThreshold ). Values equal to either threshold is considered to be between the thresholds.
More precisely f[ Output(x_i) = begin{cases} InsideValue & text{if f$LowerThreshold leq x_i leq UpperThresholdf$}  OutsideValue & text{otherwise} end{cases} f]  
This filter is templated over the input image type and the output image type.
The filter expect both images to have the same number of dimensions.
The default values for LowerThreshold and UpperThreshold are: LowerThreshold = NumericTraits<TInput>::NonpositiveMin(); UpperThreshold = NumericTraits<TInput>::max(); Therefore, generally only one of these needs to be set, depending on whether the user wants to threshold above or below the desired threshold.

li {ImageProcessing/BinaryThresholdImageFilter,Threshold an image}

*/"
%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::execute() "
/**Binarize an input image by thresholding.

*/"
%javamethodmodifiers itk::simple::BinaryThreshold "/**
Binarize an input image by thresholding.

This filter produces an output image whose pixels are either one of two values ( OutsideValue or InsideValue ), depending on whether the corresponding input image pixels lie between the two thresholds ( LowerThreshold and UpperThreshold ). Values equal to either threshold is considered to be between the thresholds.
More precisely f[ Output(x_i) = begin{cases} InsideValue & text{if f$LowerThreshold leq x_i leq UpperThresholdf$}  OutsideValue & text{otherwise} end{cases} f]  
This filter is templated over the input image type and the output image type.
The filter expect both images to have the same number of dimensions.
The default values for LowerThreshold and UpperThreshold are: LowerThreshold = NumericTraits<TInput>::NonpositiveMin(); UpperThreshold = NumericTraits<TInput>::max(); Therefore, generally only one of these needs to be set, depending on whether the user wants to threshold above or below the desired threshold.

li {ImageProcessing/BinaryThresholdImageFilter,Threshold an image}

*/"
%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::setLowerThreshold "/**
virtual void itk::BinaryThresholdImageFilter::SetLowerThreshold(const InputPixelType threshold)

*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::getLowerThreshold "/**
virtual InputPixelType itk::BinaryThresholdImageFilter::GetLowerThreshold() const

*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::setUpperThreshold "/**
virtual void itk::BinaryThresholdImageFilter::SetUpperThreshold(const InputPixelType threshold)

Set the thresholds. The default lower threshold is NumericTraits<InputPixelType>::NonpositiveMin(). The default upper threshold is NumericTraits<InputPixelType>::max. An execption is thrown if the lower threshold is greater than the upper threshold.
*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::getUpperThreshold "/**
virtual InputPixelType itk::BinaryThresholdImageFilter::GetUpperThreshold() const

Get the threshold values.
*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::setInsideValue "/**
virtual void itk::BinaryThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::getInsideValue "/**
virtual const OutputPixelType& itk::BinaryThresholdImageFilter::GetInsideValue()

Get the inside pixel value.
*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::setOutsideValue "/**
virtual void itk::BinaryThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::BinaryThresholdImageFilter::getOutsideValue "/**
virtual const OutputPixelType& itk::BinaryThresholdImageFilter::GetOutsideValue()

Get the outside pixel value.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BlackTopHatImageFilter.xml
%typemap(javaimports) itk::simple::BlackTopHatImageFilter "/** Black top hat extract local minima that are smaller than the structuring element.

Black top hat extract local minima that are smaller than the structuring element. It subtract the background in the input image. The output of the filter transforms the black peaks in white peaks.
Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::BlackTopHatImageFilter::execute() "
/**Black top hat extract local minima that are smaller than the structuring element.

*/"
%javamethodmodifiers itk::simple::BlackTopHat "/**
Black top hat extract local minima that are smaller than the structuring element.

Black top hat extract local minima that are smaller than the structuring element. It subtract the background in the input image. The output of the filter transforms the black peaks in white peaks.
Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::BlackTopHatImageFilter::setSafeBorder "/**
virtual void itk::BlackTopHatImageFilter::SetSafeBorder(bool _arg)

A safe border is added to input image to avoid borders effects and remove it once the closing is done
*/"

%javamethodmodifiers itk::simple::BlackTopHatImageFilter::getSafeBorder "/**
virtual const bool& itk::BlackTopHatImageFilter::GetSafeBorder()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BoundedReciprocalImageFilter.xml
%typemap(javaimports) itk::simple::BoundedReciprocalImageFilter "/** Computes 1/(1+x) for each pixel in the image.

The filter expect both the input and output images to have the same number of dimensions, and both of a scalar image type.
*/"
%javamethodmodifiers itk::simple::BoundedReciprocalImageFilter::execute() "
/**Computes 1/(1+x) for each pixel in the image.

*/"
%javamethodmodifiers itk::simple::BoundedReciprocal "/**
Computes 1/(1+x) for each pixel in the image.

The filter expect both the input and output images to have the same number of dimensions, and both of a scalar image type.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CannyEdgeDetectionImageFilter.xml
%typemap(javaimports) itk::simple::CannyEdgeDetectionImageFilter "/** 
This filter is an implementation of a Canny edge detector for scalar-valued images. Based on John Canny's paper A Computational Approach to Edge Detection(IEEE Transactions on Pattern Analysis and Machine Intelligence, Vol. PAMI-8, No.6, November 1986), there are four major steps used in the edge-detection scheme: (1) Smooth the input image with Gaussian filter. (2) Calculate the second directional derivatives of the smoothed image. (3) Non-Maximum Suppression: the zero-crossings of 2nd derivative are found, and the sign of third derivative is used to find the correct extrema. (4) The hysteresis thresholding is applied to the gradient magnitude (multiplied with zero-crossings) of the smoothed image to find and link edges.
par Inputs and Outputs
The input to this filter should be a scalar, real-valued Itk image of arbitrary dimension. The output should also be a scalar, real-value Itk image of the same dimensionality.
par Parameters
There are four parameters for this filter that control the sub-filters used by the algorithm.
par Variance and Maximum error are used in the Gaussian smoothing of the input image. See itkDiscreteGaussianImageFilter for information on these parameters.
par Threshold is the lowest allowed value in the output image. Its data type is the same as the data type of the output image. Any values below the Threshold level will be replaced with the OutsideValue parameter value, whose default is zero.
TodoEdge-linking will be added when an itk connected component labeling algorithm is available.
see  DiscreteGaussianImageFilter
see  ZeroCrossingImageFilter
see  ThresholdImageFilter

*/"
%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::CannyEdgeDetection "/**

This filter is an implementation of a Canny edge detector for scalar-valued images. Based on John Canny's paper A Computational Approach to Edge Detection(IEEE Transactions on Pattern Analysis and Machine Intelligence, Vol. PAMI-8, No.6, November 1986), there are four major steps used in the edge-detection scheme: (1) Smooth the input image with Gaussian filter. (2) Calculate the second directional derivatives of the smoothed image. (3) Non-Maximum Suppression: the zero-crossings of 2nd derivative are found, and the sign of third derivative is used to find the correct extrema. (4) The hysteresis thresholding is applied to the gradient magnitude (multiplied with zero-crossings) of the smoothed image to find and link edges.
par Inputs and Outputs
The input to this filter should be a scalar, real-valued Itk image of arbitrary dimension. The output should also be a scalar, real-value Itk image of the same dimensionality.
par Parameters
There are four parameters for this filter that control the sub-filters used by the algorithm.
par Variance and Maximum error are used in the Gaussian smoothing of the input image. See itkDiscreteGaussianImageFilter for information on these parameters.
par Threshold is the lowest allowed value in the output image. Its data type is the same as the data type of the output image. Any values below the Threshold level will be replaced with the OutsideValue parameter value, whose default is zero.
TodoEdge-linking will be added when an itk connected component labeling algorithm is available.
see  DiscreteGaussianImageFilter
see  ZeroCrossingImageFilter
see  ThresholdImageFilter

*/"
%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::setLowerThreshold "/**
virtual void itk::CannyEdgeDetectionImageFilter::SetLowerThreshold(OutputImagePixelType _arg)

*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::getLowerThreshold "/**
virtual OutputImagePixelType itk::CannyEdgeDetectionImageFilter::GetLowerThreshold() const

*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::setUpperThreshold "/**
virtual void itk::CannyEdgeDetectionImageFilter::SetUpperThreshold(OutputImagePixelType _arg)
* Set the Threshold value for detected edges. */

*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::getUpperThreshold "/**
virtual OutputImagePixelType itk::CannyEdgeDetectionImageFilter::GetUpperThreshold() const

*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::setVariance "/**
void itk::CannyEdgeDetectionImageFilter::SetVariance(const typename ArrayType::ValueType v)

Set/Get the Variance parameter used by the Gaussian smoothing filter in this algorithm
*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::getVariance "/**
virtual const ArrayType itk::CannyEdgeDetectionImageFilter::GetVariance() const

*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::setMaximumError "/**
void itk::CannyEdgeDetectionImageFilter::SetMaximumError(const typename ArrayType::ValueType v)

Set/Get the MaximumError paramter used by the Gaussian smoothing filter in this algorithm
*/"

%javamethodmodifiers itk::simple::CannyEdgeDetectionImageFilter::getMaximumError "/**
virtual const ArrayType itk::CannyEdgeDetectionImageFilter::GetMaximumError() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CheckerBoardImageFilter.xml
%typemap(javaimports) itk::simple::CheckerBoardImageFilter "/** Combines two images in a checkerboard pattern.

 CheckerBoardImageFiltertakes two input images that must have the same dimension, size, origin and spacing and produces an output image of the same size by combinining the pixels from the two input images in a checkerboard pattern. This filter is commonly used for visually comparing two images, in particular for evaluating the results of an image registration process.
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Inspection/CheckerBoardImageFilter,Combine two images by alternating blocks of a checkerboard pattern}

*/"
%javamethodmodifiers itk::simple::CheckerBoardImageFilter::execute() "
/**Combines two images in a checkerboard pattern.

*/"
%javamethodmodifiers itk::simple::CheckerBoard "/**
Combines two images in a checkerboard pattern.

 CheckerBoardImageFiltertakes two input images that must have the same dimension, size, origin and spacing and produces an output image of the same size by combinining the pixels from the two input images in a checkerboard pattern. This filter is commonly used for visually comparing two images, in particular for evaluating the results of an image registration process.
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Inspection/CheckerBoardImageFilter,Combine two images by alternating blocks of a checkerboard pattern}

*/"
%javamethodmodifiers itk::simple::CheckerBoardImageFilter::setCheckerPattern "/**
virtual void itk::CheckerBoardImageFilter::SetCheckerPattern(PatternArrayType _arg)

Set array with number of checks to make per image dimension
*/"

%javamethodmodifiers itk::simple::CheckerBoardImageFilter::getCheckerPattern "/**
virtual const PatternArrayType& itk::CheckerBoardImageFilter::GetCheckerPattern()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ClosingByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::ClosingByReconstructionImageFilter "/** Closing by reconstruction of an image.

This filter is similar to the morphological closing, but contrary to the mophological closing, the closing by reconstruction preserves the shape of the components. The closing by reconstruction of an image f is defined as:
ClosingByReconstruction(f) = ErosionByReconstruction(f, Dilation(f)).
Closing by reconstruction not only preserves structures preserved by the dilation, but also levels raises the contrast of the darkest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Closing by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  GrayscaleMorphologicalClosingImageFilter

*/"
%javamethodmodifiers itk::simple::ClosingByReconstructionImageFilter::execute() "
/**Closing by reconstruction of an image.

*/"
%javamethodmodifiers itk::simple::ClosingByReconstruction "/**
Closing by reconstruction of an image.

This filter is similar to the morphological closing, but contrary to the mophological closing, the closing by reconstruction preserves the shape of the components. The closing by reconstruction of an image f is defined as:
ClosingByReconstruction(f) = ErosionByReconstruction(f, Dilation(f)).
Closing by reconstruction not only preserves structures preserved by the dilation, but also levels raises the contrast of the darkest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Closing by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  GrayscaleMorphologicalClosingImageFilter

*/"
%javamethodmodifiers itk::simple::ClosingByReconstructionImageFilter::setFullyConnected "/**
virtual void itk::ClosingByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::ClosingByReconstructionImageFilter::getFullyConnected "/**
virtual const bool& itk::ClosingByReconstructionImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::ClosingByReconstructionImageFilter::setPreserveIntensities "/**
virtual void itk::ClosingByReconstructionImageFilter::SetPreserveIntensities(bool _arg)

Set/Get whether the original intensities of the image retained for those pixels unaffected by the opening by reconstrcution. If Off, the output pixel contrast will be reduced.
*/"

%javamethodmodifiers itk::simple::ClosingByReconstructionImageFilter::getPreserveIntensities "/**
virtual const bool& itk::ClosingByReconstructionImageFilter::GetPreserveIntensities()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ComplexToImaginaryImageFilter.xml
%typemap(javaimports) itk::simple::ComplexToImaginaryImageFilter "/** Computes pixel-wise the imaginary part of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToImaginaryImageFilter::execute() "
/**Computes pixel-wise the imaginary part of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToImaginary "/**
Computes pixel-wise the imaginary part of a complex image.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ComplexToModulusImageFilter.xml
%typemap(javaimports) itk::simple::ComplexToModulusImageFilter "/** Computes pixel-wise the Modulus of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToModulusImageFilter::execute() "
/**Computes pixel-wise the Modulus of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToModulus "/**
Computes pixel-wise the Modulus of a complex image.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ComplexToPhaseImageFilter.xml
%typemap(javaimports) itk::simple::ComplexToPhaseImageFilter "/** Computes pixel-wise the modulus of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToPhaseImageFilter::execute() "
/**Computes pixel-wise the modulus of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToPhase "/**
Computes pixel-wise the modulus of a complex image.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ComplexToRealImageFilter.xml
%typemap(javaimports) itk::simple::ComplexToRealImageFilter "/** Computes pixel-wise the real(x) part of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToRealImageFilter::execute() "
/**Computes pixel-wise the real(x) part of a complex image.

*/"
%javamethodmodifiers itk::simple::ComplexToReal "/**
Computes pixel-wise the real(x) part of a complex image.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ConnectedThresholdImageFilter.xml
%typemap(javaimports) itk::simple::ConnectedThresholdImageFilter "/** Label pixels that are connected to a seed and lie within a range of values.

 ConnectedThresholdImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND lie within a Lower and Upper threshold range.
*/"
%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::execute() "
/**Label pixels that are connected to a seed and lie within a range of values.

*/"
%javamethodmodifiers itk::simple::ConnectedThreshold "/**
Label pixels that are connected to a seed and lie within a range of values.

 ConnectedThresholdImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND lie within a Lower and Upper threshold range.
*/"
%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::setUpper "/**
virtual void itk::ConnectedThresholdImageFilter::SetUpper(InputImagePixelType)

Set Upper and Lower Threshold inputs as values
*/"

%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::getUpper "/**
virtual InputImagePixelType itk::ConnectedThresholdImageFilter::GetUpper() const

Get Upper and Lower Threshold inputs as values
*/"

%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::setLower "/**
virtual void itk::ConnectedThresholdImageFilter::SetLower(InputImagePixelType)

*/"

%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::getLower "/**
virtual InputImagePixelType itk::ConnectedThresholdImageFilter::GetLower() const

*/"

%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::setReplaceValue "/**
virtual void itk::ConnectedThresholdImageFilter::SetReplaceValue(OutputImagePixelType _arg)

Set/Get value to replace thresholded pixels. Pixels that lie * within Lower and Upper (inclusive) will be replaced with this value. The default is 1.
*/"

%javamethodmodifiers itk::simple::ConnectedThresholdImageFilter::getReplaceValue "/**
virtual OutputImagePixelType itk::ConnectedThresholdImageFilter::GetReplaceValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ConstantPadImageFilter.xml
%typemap(javaimports) itk::simple::ConstantPadImageFilter "/** Increase the image size by padding with a constant value.

 ConstantPadImageFilterchanges the output image region. If the output image region is larger than the input image region, the extra pixels are filled in by a constant value. The output image region must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  WrapPadImageFilter, MirrorPadImageFilter
li {Images/ConstantPadImageFilter,Pad an image with a constant value}


*/"
%javamethodmodifiers itk::simple::ConstantPadImageFilter::execute() "
/**Increase the image size by padding with a constant value.

*/"
%javamethodmodifiers itk::simple::ConstantPad "/**
Increase the image size by padding with a constant value.

 ConstantPadImageFilterchanges the output image region. If the output image region is larger than the input image region, the extra pixels are filled in by a constant value. The output image region must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  WrapPadImageFilter, MirrorPadImageFilter
li {Images/ConstantPadImageFilter,Pad an image with a constant value}


*/"
%javamethodmodifiers itk::simple::ConstantPadImageFilter::setConstant "/**
virtual void itk::ConstantPadImageFilter::SetConstant(OutputImagePixelType _arg)

Set/Get the pad value. Default is Zero.
*/"

%javamethodmodifiers itk::simple::ConstantPadImageFilter::getConstant "/**
virtual OutputImagePixelType itk::ConstantPadImageFilter::GetConstant() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CosImageFilter.xml
%typemap(javaimports) itk::simple::CosImageFilter "/** Computes the vcl_cos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_cos() function to the double value
li cast the double value resulting from vcl_cos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
%javamethodmodifiers itk::simple::CosImageFilter::execute() "
/**Computes the vcl_cos(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Cos "/**
Computes the vcl_cos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_cos() function to the double value
li cast the double value resulting from vcl_cos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CropImageFilter.xml
%typemap(javaimports) itk::simple::CropImageFilter "/** Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.

 CropImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region is not specified in advance, but calculated in BeforeThreadedGenerateData().
This filter uses ExtractImageFilterto perform the cropping.

li {ImageProcessing/CropImageFilter,Crop an image}

*/"
%javamethodmodifiers itk::simple::CropImageFilter::execute() "
/**Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.

*/"
%javamethodmodifiers itk::simple::Crop "/**
Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.

 CropImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region is not specified in advance, but calculated in BeforeThreadedGenerateData().
This filter uses ExtractImageFilterto perform the cropping.

li {ImageProcessing/CropImageFilter,Crop an image}

*/"
%javamethodmodifiers itk::simple::CropImageFilter::setLowerBoundaryCropSize "/**
virtual void itk::CropImageFilter::SetLowerBoundaryCropSize(SizeType _arg)

*/"

%javamethodmodifiers itk::simple::CropImageFilter::getLowerBoundaryCropSize "/**
virtual SizeType itk::CropImageFilter::GetLowerBoundaryCropSize() const

*/"

%javamethodmodifiers itk::simple::CropImageFilter::setUpperBoundaryCropSize "/**
virtual void itk::CropImageFilter::SetUpperBoundaryCropSize(SizeType _arg)

Set/Get the cropping sizes for the upper and lower boundaries.
*/"

%javamethodmodifiers itk::simple::CropImageFilter::getUpperBoundaryCropSize "/**
virtual SizeType itk::CropImageFilter::GetUpperBoundaryCropSize() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CurvatureAnisotropicDiffusionImageFilter.xml
%typemap(javaimports) itk::simple::CurvatureAnisotropicDiffusionImageFilter "/** 
This filter performs anisotropic diffusion on a scalar itk::Imageusing the modified curvature diffusion equation (MCDE) implemented in itkCurvatureNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion and the MCDE see itkAnisotropicDiffusionFunction and itkCurvatureNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input and output to this filter must be a scalar itk::Imagewith numerical pixel types (float or double). A user defined type which correctly defines arithmetic operations with floating point accuracy should also give correct results.
par Parameters
Please first read all the documentation found in AnisotropicDiffusionImageFilterand AnisotropicDiffusionFunction. Also see CurvatureNDAnisotropicDiffusionFunction.
The default time step for this filter is set to the maximum theoretically stable value: 0.5 / 2^N, where N is the dimensionality of the image. For a 2D image, this means valid time steps are below 0.1250. For a 3D image, valid time steps are below 0.0625.
see  AnisotropicDiffusionImageFilter
see  AnisotropicDiffusionFunction
see  CurvatureNDAnisotropicDiffusionFunction

*/"
%javamethodmodifiers itk::simple::CurvatureAnisotropicDiffusionImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::CurvatureAnisotropicDiffusion "/**

This filter performs anisotropic diffusion on a scalar itk::Imageusing the modified curvature diffusion equation (MCDE) implemented in itkCurvatureNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion and the MCDE see itkAnisotropicDiffusionFunction and itkCurvatureNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input and output to this filter must be a scalar itk::Imagewith numerical pixel types (float or double). A user defined type which correctly defines arithmetic operations with floating point accuracy should also give correct results.
par Parameters
Please first read all the documentation found in AnisotropicDiffusionImageFilterand AnisotropicDiffusionFunction. Also see CurvatureNDAnisotropicDiffusionFunction.
The default time step for this filter is set to the maximum theoretically stable value: 0.5 / 2^N, where N is the dimensionality of the image. For a 2D image, this means valid time steps are below 0.1250. For a 3D image, valid time steps are below 0.0625.
see  AnisotropicDiffusionImageFilter
see  AnisotropicDiffusionFunction
see  CurvatureNDAnisotropicDiffusionFunction

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CurvatureFlowImageFilter.xml
%typemap(javaimports) itk::simple::CurvatureFlowImageFilter "/** Denoise an image using curvature driven flow.

 CurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = kappa |nabla I| f]  wheref$ kappa f$ is the curvature.
The advantage of this approach is that sharp boundaries are preserved with smoothing occuring only within a region. However, it should be noted that continuous application of this scheme will result in the eventual removal of all information as each contour shrinks to zero and disappear.
Note that unlike level set segmentation algorithms, the image to be denoised is already the level set and can be set directly as the input using the SetInput()method.
This filter has two parameters: the number of update iterations to be performed and the timestep between each update.
The timestep should be small enough to ensure numerical stability. Stability is guarantee when the timestep meets the CFL (Courant-Friedrichs-Levy) condition. Broadly speaking, this condition ensures that each contour does not move more than one grid position at each timestep. In the literature, the timestep is typically user specified and have to manually tuned to the application.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a CurvatureFlowFunctionobject. A zero flux Neumann boundary condition when computing derivatives near the data boundary.
This filter may be streamed. To support streaming this filter produces a padded output which takes into account edge effects. The size of the padding is m_NumberOfIterations on each edge. Users of this filter should only make use of the center valid central region.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a floating point type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  DenseFiniteDifferenceImageFilter
see  CurvatureFlowFunction
see  MinMaxCurvatureFlowImageFilter
see  BinaryMinMaxCurvatureFlowImageFilter
Input/Output Restrictions: TInputImage and TOutputImage must have the same dimension. TOutputImage's pixel type must be a real number type.
*/"
%javamethodmodifiers itk::simple::CurvatureFlowImageFilter::execute() "
/**Denoise an image using curvature driven flow.

*/"
%javamethodmodifiers itk::simple::CurvatureFlow "/**
Denoise an image using curvature driven flow.

 CurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = kappa |nabla I| f]  wheref$ kappa f$ is the curvature.
The advantage of this approach is that sharp boundaries are preserved with smoothing occuring only within a region. However, it should be noted that continuous application of this scheme will result in the eventual removal of all information as each contour shrinks to zero and disappear.
Note that unlike level set segmentation algorithms, the image to be denoised is already the level set and can be set directly as the input using the SetInput()method.
This filter has two parameters: the number of update iterations to be performed and the timestep between each update.
The timestep should be small enough to ensure numerical stability. Stability is guarantee when the timestep meets the CFL (Courant-Friedrichs-Levy) condition. Broadly speaking, this condition ensures that each contour does not move more than one grid position at each timestep. In the literature, the timestep is typically user specified and have to manually tuned to the application.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a CurvatureFlowFunctionobject. A zero flux Neumann boundary condition when computing derivatives near the data boundary.
This filter may be streamed. To support streaming this filter produces a padded output which takes into account edge effects. The size of the padding is m_NumberOfIterations on each edge. Users of this filter should only make use of the center valid central region.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a floating point type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  DenseFiniteDifferenceImageFilter
see  CurvatureFlowFunction
see  MinMaxCurvatureFlowImageFilter
see  BinaryMinMaxCurvatureFlowImageFilter
Input/Output Restrictions: TInputImage and TOutputImage must have the same dimension. TOutputImage's pixel type must be a real number type.
*/"
%javamethodmodifiers itk::simple::CurvatureFlowImageFilter::setTimeStep "/**
virtual void itk::CurvatureFlowImageFilter::SetTimeStep(TimeStepType _arg)

Set the timestep parameter.
*/"

%javamethodmodifiers itk::simple::CurvatureFlowImageFilter::getTimeStep "/**
virtual TimeStepType itk::CurvatureFlowImageFilter::GetTimeStep() const

Get the timestep parameter.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DanielssonDistanceMapImageFilter.xml
%typemap(javaimports) itk::simple::DanielssonDistanceMapImageFilter "/** This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.

TInputImage Input ImageType  TOutputImage Output ImageType
The input is assumed to contain numeric codes defining objects. The filter will produce as output the following images:

li A Voronoi partition using the same numeric codes as the input.
li A distance map with the approximation to the euclidean distance. from a particular pixel to the nearest object to this pixel in the input image.
li A vector map containing the component of the vector relating the current pixel with the closest point of the closest object to this pixel. Given that the components of the distance are computed in pixels, the vector is represented by an itk::Offset. That is, physical coordinates are not used.
This filter is N-dimensional and known to be efficient in computational time. The algorithm is the N-dimensional version of the 4SED algorithm given for two dimensions in:
Danielsson, Per-Erik. Euclidean Distance Mapping. Computer Graphics and ImageProcessing 14, 227-248 (1980).
*/"
%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::execute() "
/**This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.

*/"
%javamethodmodifiers itk::simple::DanielssonDistanceMap "/**
This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.

TInputImage Input ImageType  TOutputImage Output ImageType
The input is assumed to contain numeric codes defining objects. The filter will produce as output the following images:

li A Voronoi partition using the same numeric codes as the input.
li A distance map with the approximation to the euclidean distance. from a particular pixel to the nearest object to this pixel in the input image.
li A vector map containing the component of the vector relating the current pixel with the closest point of the closest object to this pixel. Given that the components of the distance are computed in pixels, the vector is represented by an itk::Offset. That is, physical coordinates are not used.
This filter is N-dimensional and known to be efficient in computational time. The algorithm is the N-dimensional version of the 4SED algorithm given for two dimensions in:
Danielsson, Per-Erik. Euclidean Distance Mapping. Computer Graphics and ImageProcessing 14, 227-248 (1980).
*/"
%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::setInputIsBinary "/**
virtual void itk::DanielssonDistanceMapImageFilter::SetInputIsBinary(bool _arg)

Set if the input is binary. If this variable is set, each nonzero pixel in the input image will be given a unique numeric code to be used by the Voronoi partition. If the image is binary but you are not interested in the Voronoi regions of the different nonzero pixels, then you need not set this.
*/"

%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::getInputIsBinary "/**
virtual const bool& itk::DanielssonDistanceMapImageFilter::GetInputIsBinary()

Get if the input is binary. See SetInputIsBinary().
*/"

%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::setSquaredDistance "/**
virtual void itk::DanielssonDistanceMapImageFilter::SetSquaredDistance(bool _arg)

Set if the distance should be squared.
*/"

%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::getSquaredDistance "/**
virtual const bool& itk::DanielssonDistanceMapImageFilter::GetSquaredDistance()

Get the distance squared.
*/"

%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::setUseImageSpacing "/**
virtual void itk::DanielssonDistanceMapImageFilter::SetUseImageSpacing(bool _arg)

Set if image spacing should be used in computing distances.
*/"

%javamethodmodifiers itk::simple::DanielssonDistanceMapImageFilter::getUseImageSpacing "/**
virtual const bool& itk::DanielssonDistanceMapImageFilter::GetUseImageSpacing()

Get whether spacing is used.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DerivativeImageFilter.xml
%typemap(javaimports) itk::simple::DerivativeImageFilter "/** Computes the directional derivative of an image. The directional derivative at each pixel location is computed by convolution with a derivative operator of user-specified order.

SetOrder specifies the order of the derivative.
SetDirection specifies the direction of the derivative with respect to the coordinate axes of the image.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

li {EdgesAndGradients/DerivativeImageFilter,Compute the derivative of an image in a particular direction}

*/"
%javamethodmodifiers itk::simple::DerivativeImageFilter::execute() "
/**Computes the directional derivative of an image. The directional derivative at each pixel location is computed by convolution with a derivative operator of user-specified order.

*/"
%javamethodmodifiers itk::simple::Derivative "/**
Computes the directional derivative of an image. The directional derivative at each pixel location is computed by convolution with a derivative operator of user-specified order.

SetOrder specifies the order of the derivative.
SetDirection specifies the direction of the derivative with respect to the coordinate axes of the image.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

li {EdgesAndGradients/DerivativeImageFilter,Compute the derivative of an image in a particular direction}

*/"
%javamethodmodifiers itk::simple::DerivativeImageFilter::setDirection "/**
virtual void itk::DerivativeImageFilter::SetDirection(unsigned int _arg)

*/"

%javamethodmodifiers itk::simple::DerivativeImageFilter::getDirection "/**
virtual unsigned int itk::DerivativeImageFilter::GetDirection() const

*/"

%javamethodmodifiers itk::simple::DerivativeImageFilter::setOrder "/**
virtual void itk::DerivativeImageFilter::SetOrder(unsigned int _arg)

End concept checking Standard get/set macros for filter parameters.
*/"

%javamethodmodifiers itk::simple::DerivativeImageFilter::getOrder "/**
virtual unsigned int itk::DerivativeImageFilter::GetOrder() const

*/"

%javamethodmodifiers itk::simple::DerivativeImageFilter::setUseImageSpacing "/**
virtual void itk::DerivativeImageFilter::SetUseImageSpacing(bool _arg)

Set/Get whether or not the filter will use the spacing of the input image in its calculations
*/"

%javamethodmodifiers itk::simple::DerivativeImageFilter::getUseImageSpacing "/**
virtual bool itk::DerivativeImageFilter::GetUseImageSpacing() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DilateObjectMorphologyImageFilter.xml
%typemap(javaimports) itk::simple::DilateObjectMorphologyImageFilter "/** dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see  ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see  BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::DilateObjectMorphologyImageFilter::execute() "
/**dilation of an object in an image

*/"
%javamethodmodifiers itk::simple::DilateObjectMorphology "/**
dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see  ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see  BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DivideByConstantImageFilter.xml
%typemap(javaimports) itk::simple::DivideByConstantImageFilter "/** Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::DivideByConstantImageFilter::execute() "
/**Divide input pixels by a constant.

*/"
%javamethodmodifiers itk::simple::DivideByConstant "/**
Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::DivideByConstantImageFilter::setConstant "/**
void itk::DivideByConstantImageFilter::SetConstant(TConstant ct)

Set the constant value that will be used for dividing all the image pixels
*/"

%javamethodmodifiers itk::simple::DivideByConstantImageFilter::getConstant "/**
const TConstant& itk::DivideByConstantImageFilter::GetConstant() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DivideImageFilter.xml
%typemap(javaimports) itk::simple::DivideImageFilter "/** Implements an operator for pixel-wise division of two images.

This class is parametrized over the types of the two input images and the type of the output image. When the divisor is zero, the division result is set to the maximum number that can be represneted by default to avoid exception. Numeric conversions (castings) are done by the C++ defaults.
*/"
%javamethodmodifiers itk::simple::DivideImageFilter::execute() "
/**Implements an operator for pixel-wise division of two images.

*/"
%javamethodmodifiers itk::simple::Divide "/**
Implements an operator for pixel-wise division of two images.

This class is parametrized over the types of the two input images and the type of the output image. When the divisor is zero, the division result is set to the maximum number that can be represneted by default to avoid exception. Numeric conversions (castings) are done by the C++ defaults.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DoubleThresholdImageFilter.xml
%typemap(javaimports) itk::simple::DoubleThresholdImageFilter "/** Binarize an input image using double thresholding.

Double threshold addresses the difficulty in selecting a threshold that will select the objects of interest without selecting extraneous objects. Double threshold considers two threshold ranges: a narrow range and a wide range (where the wide range encompasses the narrow range). If the wide range was used for a traditional threshold (where values inside the range map to the foreground and values outside the range map to the background), many extraneous pixels may survive the threshold operation. If the narrow range was used for a traditional threshold, then too few pixels may survive the threshold.
Double threshold uses the narrow threshold image as a marker image and the wide threshold image as a mask image in the geodesic dilation. Essentially, the marker image (narrow threshold) is dilated but constrained to lie within the mask image (wide threshold). Thus, only the objects of interest (those pixels that survived the narrow threshold) are extracted but the those objects appear in the final image as they would have if the wide threshold was used.
see  GrayscaleGeodesicDilateImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::execute() "
/**Binarize an input image using double thresholding.

*/"
%javamethodmodifiers itk::simple::DoubleThreshold "/**
Binarize an input image using double thresholding.

Double threshold addresses the difficulty in selecting a threshold that will select the objects of interest without selecting extraneous objects. Double threshold considers two threshold ranges: a narrow range and a wide range (where the wide range encompasses the narrow range). If the wide range was used for a traditional threshold (where values inside the range map to the foreground and values outside the range map to the background), many extraneous pixels may survive the threshold operation. If the narrow range was used for a traditional threshold, then too few pixels may survive the threshold.
Double threshold uses the narrow threshold image as a marker image and the wide threshold image as a mask image in the geodesic dilation. Essentially, the marker image (narrow threshold) is dilated but constrained to lie within the mask image (wide threshold). Thus, only the objects of interest (those pixels that survived the narrow threshold) are extracted but the those objects appear in the final image as they would have if the wide threshold was used.
see  GrayscaleGeodesicDilateImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setThreshold1 "/**
virtual void itk::DoubleThresholdImageFilter::SetThreshold1(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getThreshold1 "/**
virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold1() const

Get the threshold values.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setThreshold2 "/**
virtual void itk::DoubleThresholdImageFilter::SetThreshold2(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getThreshold2 "/**
virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold2() const

Get the threshold values.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setThreshold3 "/**
virtual void itk::DoubleThresholdImageFilter::SetThreshold3(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getThreshold3 "/**
virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold3() const

Get the threshold values.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setThreshold4 "/**
virtual void itk::DoubleThresholdImageFilter::SetThreshold4(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getThreshold4 "/**
virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold4() const

Get the threshold values.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setInsideValue "/**
virtual void itk::DoubleThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getInsideValue "/**
virtual OutputPixelType itk::DoubleThresholdImageFilter::GetInsideValue() const

Get the inside pixel value.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setOutsideValue "/**
virtual void itk::DoubleThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getOutsideValue "/**
virtual OutputPixelType itk::DoubleThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::setFullyConnected "/**
virtual void itk::DoubleThresholdImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::getFullyConnected "/**
virtual const bool& itk::DoubleThresholdImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1EdgePotentialImageFilter.xml
%typemap(javaimports) itk::simple::EdgePotentialImageFilter "/** Computes the edge potential of an image from the image gradient.

Input to this filter should be a CovariantVectorimage representing the image gradient.
The filter expect both the input and output images to have the same number of dimensions, and the output to be of a scalar image type.
*/"
%javamethodmodifiers itk::simple::EdgePotentialImageFilter::execute() "
/**Computes the edge potential of an image from the image gradient.

*/"
%javamethodmodifiers itk::simple::EdgePotential "/**
Computes the edge potential of an image from the image gradient.

Input to this filter should be a CovariantVectorimage representing the image gradient.
The filter expect both the input and output images to have the same number of dimensions, and the output to be of a scalar image type.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ErodeObjectMorphologyImageFilter.xml
%typemap(javaimports) itk::simple::ErodeObjectMorphologyImageFilter "/** Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see  ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see  BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::ErodeObjectMorphologyImageFilter::execute() "
/**Erosion of an object in an image.

*/"
%javamethodmodifiers itk::simple::ErodeObjectMorphology "/**
Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see  ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see  BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::ErodeObjectMorphologyImageFilter::setBackgroundValue "/**
virtual void itk::ErodeObjectMorphologyImageFilter::SetBackgroundValue(PixelType _arg)

Set the value to be assigned to eroded pixels
*/"

%javamethodmodifiers itk::simple::ErodeObjectMorphologyImageFilter::getBackgroundValue "/**
virtual PixelType itk::ErodeObjectMorphologyImageFilter::GetBackgroundValue() const

Get the value to be assigned to eroded pixels
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ExpImageFilter.xml
%typemap(javaimports) itk::simple::ExpImageFilter "/** Computes the vcl_exp(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::ExpImageFilter::execute() "
/**Computes the vcl_exp(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Exp "/**
Computes the vcl_exp(x) pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ExpNegativeImageFilter.xml
%typemap(javaimports) itk::simple::ExpNegativeImageFilter "/** Computes the function vcl_exp(-K.x) pixel-wise.

Every output pixel is equal to vcl_exp(-K.x ). where x is the intensity of the homologous input pixel, and K is a user-provided constant.
*/"
%javamethodmodifiers itk::simple::ExpNegativeImageFilter::execute() "
/**Computes the function vcl_exp(-K.x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::ExpNegative "/**
Computes the function vcl_exp(-K.x) pixel-wise.

Every output pixel is equal to vcl_exp(-K.x ). where x is the intensity of the homologous input pixel, and K is a user-provided constant.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ExtractImageFilter.xml
%typemap(javaimports) itk::simple::ExtractImageFilter "/** Decrease the image size by cropping the image to the selected region bounds.

 ExtractImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region must be specified.
 ExtractImageFilteralso collapses dimensions so that the input image may have more dimensions than the output image ( i.e. 4-D input image to a 3-D output image). To specify what dimensions to collapse, the ExtractionRegion must be specified. For any dimension dim where ExtractionRegion.Size[dim] = 0, that dimension is collapsed. The index to collapse on is specified by ExtractionRegion.Index[dim]. For example, we have a image 4D = a 4x4x4x4 image, and we want to get a 3D image, 3D = a 4x4x4 image, specified as [x,y,z,2] from 4D ( i.e. the 3rd time slice from 4D). The ExtractionRegion.Size = [4,4,4,0] and ExtractionRegion.Index = [0,0,0,2].
The number of dimension in ExtractionRegion.Size and Indexmust = InputImageDimension. The number of non-zero dimensions in ExtractionRegion.Size must = OutputImageDimension.
The output image produced by this filter will have the same origin as the input image, while the ImageRegionof the output image will start at the starting index value provided in the ExtractRegion parameter. If you are looking for a filter that will re-compute the origin of the output image, and provide an output image region whose index is set to zeros, then you may want to use the RegionOfInterestImageFilter. The output spacing is is simply the collapsed version of the input spacing.
Determining the direction of the collapsed output image from an larger dimensional input space is an ill defined problem in general. It is required that the application developer select the desired transformation strategy for collapsing direction cosigns. It is REQUIRED that a strategy be explicitly requested ( i.e. there is no working default). Direction Collapsing Strategies: 1) DirectionCollapseToUnknown(); This is the default and the filter can not run when this is set. The reason is to explicitly force the application developer to define their desired behavior. 1) DirectionCollapseToIdentity(); Output has identity direction no matter what 2) DirectionCollaspeToSubmatrix(); Output direction is the sub-matrix if it is positive definite, else throw an exception.
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  CropImageFilter

*/"
%javamethodmodifiers itk::simple::ExtractImageFilter::execute() "
/**Decrease the image size by cropping the image to the selected region bounds.

*/"
%javamethodmodifiers itk::simple::Extract "/**
Decrease the image size by cropping the image to the selected region bounds.

 ExtractImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region must be specified.
 ExtractImageFilteralso collapses dimensions so that the input image may have more dimensions than the output image ( i.e. 4-D input image to a 3-D output image). To specify what dimensions to collapse, the ExtractionRegion must be specified. For any dimension dim where ExtractionRegion.Size[dim] = 0, that dimension is collapsed. The index to collapse on is specified by ExtractionRegion.Index[dim]. For example, we have a image 4D = a 4x4x4x4 image, and we want to get a 3D image, 3D = a 4x4x4 image, specified as [x,y,z,2] from 4D ( i.e. the 3rd time slice from 4D). The ExtractionRegion.Size = [4,4,4,0] and ExtractionRegion.Index = [0,0,0,2].
The number of dimension in ExtractionRegion.Size and Indexmust = InputImageDimension. The number of non-zero dimensions in ExtractionRegion.Size must = OutputImageDimension.
The output image produced by this filter will have the same origin as the input image, while the ImageRegionof the output image will start at the starting index value provided in the ExtractRegion parameter. If you are looking for a filter that will re-compute the origin of the output image, and provide an output image region whose index is set to zeros, then you may want to use the RegionOfInterestImageFilter. The output spacing is is simply the collapsed version of the input spacing.
Determining the direction of the collapsed output image from an larger dimensional input space is an ill defined problem in general. It is required that the application developer select the desired transformation strategy for collapsing direction cosigns. It is REQUIRED that a strategy be explicitly requested ( i.e. there is no working default). Direction Collapsing Strategies: 1) DirectionCollapseToUnknown(); This is the default and the filter can not run when this is set. The reason is to explicitly force the application developer to define their desired behavior. 1) DirectionCollapseToIdentity(); Output has identity direction no matter what 2) DirectionCollaspeToSubmatrix(); Output direction is the sub-matrix if it is positive definite, else throw an exception.
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  CropImageFilter

*/"
%javamethodmodifiers itk::simple::ExtractImageFilter::setDirectionCollapseToStrategy "/**
void itk::ExtractImageFilter::SetDirectionCollapseToStrategy(const DIRECTIONCOLLASPESTRATEGY choosenStrategy)

Set the strategy to be used to collapse pysical space dimensions.
itk::itkExtractImageFilter::DIRECTIONCOLLASPETOIDENTITY Set the strategy so that all collapsed images have an identity direction. Use this strategy when you know that retention of the physical space orientation of the collapsed image is not important.
itk::itkExtractImageFilter::DIRECTIONCOLLASPETOGUESS Set the strategy so that all collapsed images where output direction is the sub-matrix it it is positive definite, else return identity. This is backwards compatible with ITKv3, but is highly discouraged because the results are difficult to anticipate under differing data scenerios.
itk::itkExtractImageFilter::DIRECTIONCOLLASPETOSUBMATRIX Set the strategy so that all collapsed images where output direction is the sub-matrix it it is positive definite, else throw an exception. Use this strategy when it is known that properly identified physical space sub-volumes can be reliably extracted from a higher dimensional space. For example when the applicaiton programmer knows that a 4D image is 3D+time, and that the 3D sub-space is properly defined.
*/"

%javamethodmodifiers itk::simple::ExtractImageFilter::getDirectionCollapseToStrategy "/**
DIRECTIONCOLLASPESTRATEGY itk::ExtractImageFilter::GetDirectionCollapseToStrategy() const

Get the currently set strategy for collapsing directions of physical space.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1FastMarchingImageFilter.xml
%typemap(javaimports) itk::simple::FastMarchingImageFilter "/** Solve an Eikonal equation using Fast Marching.

Fast marching solves an Eikonal equation where the speed is always non-negative and depends on the position only. Starting from an initial position on the front, fast marching systematically moves the front forward one grid point at a time.
Updates are preformed using an entropy satisfy scheme where only upwind neighborhoods are used. This implementation of Fast Marching uses a std::priority_queue to locate the next proper grid position to update.
Fast Marching sweeps through N grid points in (N log N) steps to obtain the arrival time value as the front propagates through the grid.
Implementation of this class is based on Chapter 8 of Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Second edition, 1999.
This class is templated over the level set image type and the speed image type. The initial front is specified by two containers: one containing the known points and one containing the trial points. Alive points are those that are already part of the object, and trial points are considered for inclusion. In order for the filter to evolve, at least some trial points must be specified. These can for instance be specified as the layer of pixels around the alive points.
The speed function can be specified as a speed image or a speed constant. The speed image is set using the method SetInput(). If the speed image is NULL, a constant speed function is used and is specified using method the SetSpeedConstant().
If the speed function is constant and of value one, fast marching results in an approximate distance function from the initial alive points. FastMarchingImageFilteris used in the ReinitializeLevelSetImageFilterobject to create a signed distance function from the zero level set.
The algorithm can be terminated early by setting an appropriate stopping value. The algorithm terminates when the current arrival time being processed is greater than the stopping value.
There are two ways to specify the output image information ( LargestPossibleRegion, Spacing, Origin): (a) it is copied directly from the input speed image or (b) it is specified by the user. Default values are used if the user does not specify all the information.
The output information is computed as follows. If the speed image is NULL or if the OverrideOutputInformation is set to true, the output information is set from user specified parameters. These parameters can be specified using methods SetOutputRegion(), SetOutputSpacing(), SetOutputDirection(), and SetOutputOrigin(). Else if the speed image is not NULL, the output information is copied from the input speed image.
Possible Improvements: In the current implemenation, std::priority_queue only allows taking nodes out from the front and putting nodes in from the back. To update a value already on the heap, a new node is added to the heap. The defunct old node is left on the heap. When it is removed from the top, it will be recognized as invalid and not used. Future implementations can implement the heap in a different way allowing the values to be updated. This will generally require some sift-up and sift-down functions and an image of back-pointers going from the image to heap in order to locate the node which is to be updated.
see  LevelSetTypeDefault

*/"
%javamethodmodifiers itk::simple::FastMarchingImageFilter::execute() "
/**Solve an Eikonal equation using Fast Marching.

*/"
%javamethodmodifiers itk::simple::FastMarching "/**
Solve an Eikonal equation using Fast Marching.

Fast marching solves an Eikonal equation where the speed is always non-negative and depends on the position only. Starting from an initial position on the front, fast marching systematically moves the front forward one grid point at a time.
Updates are preformed using an entropy satisfy scheme where only upwind neighborhoods are used. This implementation of Fast Marching uses a std::priority_queue to locate the next proper grid position to update.
Fast Marching sweeps through N grid points in (N log N) steps to obtain the arrival time value as the front propagates through the grid.
Implementation of this class is based on Chapter 8 of Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Second edition, 1999.
This class is templated over the level set image type and the speed image type. The initial front is specified by two containers: one containing the known points and one containing the trial points. Alive points are those that are already part of the object, and trial points are considered for inclusion. In order for the filter to evolve, at least some trial points must be specified. These can for instance be specified as the layer of pixels around the alive points.
The speed function can be specified as a speed image or a speed constant. The speed image is set using the method SetInput(). If the speed image is NULL, a constant speed function is used and is specified using method the SetSpeedConstant().
If the speed function is constant and of value one, fast marching results in an approximate distance function from the initial alive points. FastMarchingImageFilteris used in the ReinitializeLevelSetImageFilterobject to create a signed distance function from the zero level set.
The algorithm can be terminated early by setting an appropriate stopping value. The algorithm terminates when the current arrival time being processed is greater than the stopping value.
There are two ways to specify the output image information ( LargestPossibleRegion, Spacing, Origin): (a) it is copied directly from the input speed image or (b) it is specified by the user. Default values are used if the user does not specify all the information.
The output information is computed as follows. If the speed image is NULL or if the OverrideOutputInformation is set to true, the output information is set from user specified parameters. These parameters can be specified using methods SetOutputRegion(), SetOutputSpacing(), SetOutputDirection(), and SetOutputOrigin(). Else if the speed image is not NULL, the output information is copied from the input speed image.
Possible Improvements: In the current implemenation, std::priority_queue only allows taking nodes out from the front and putting nodes in from the back. To update a value already on the heap, a new node is added to the heap. The defunct old node is left on the heap. When it is removed from the top, it will be recognized as invalid and not used. Future implementations can implement the heap in a different way allowing the values to be updated. This will generally require some sift-up and sift-down functions and an image of back-pointers going from the image to heap in order to locate the node which is to be updated.
see  LevelSetTypeDefault

*/"
%javamethodmodifiers itk::simple::FastMarchingImageFilter::setNormalizationFactor "/**
virtual void itk::FastMarchingImageFilter::SetNormalizationFactor(double _arg)

Set/Get the Normalization Factor for the Speed Image. The values in the Speed Imageis divided by this factor. This allows the use of images with integer pixel types to represent the speed.
*/"

%javamethodmodifiers itk::simple::FastMarchingImageFilter::getNormalizationFactor "/**
virtual double itk::FastMarchingImageFilter::GetNormalizationFactor() const

*/"

%javamethodmodifiers itk::simple::FastMarchingImageFilter::setStoppingValue "/**
virtual void itk::FastMarchingImageFilter::SetStoppingValue(double _arg)

Set the Fast Marching algorithm Stopping Value. The Fast Marching algorithm is terminated when the value of the smallest trial point is greater than the stopping value.
*/"

%javamethodmodifiers itk::simple::FastMarchingImageFilter::getStoppingValue "/**
virtual const double& itk::FastMarchingImageFilter::GetStoppingValue()

Get the Fast Marching algorithm Stopping Value.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1FFTShiftImageFilter.xml
%typemap(javaimports) itk::simple::FFTShiftImageFilter "/** Shift the zero-frequency components to center of the image.

The fourier transform produce an image where the zero frequency components are in the corner of the image, making it difficult to understand. This filter shift the component to the center of the image. Note that with images with odd size, applying this filter twice will not produce the same image than the original one without using SetInverse(true) on one (and only one) of the two filters.
http://hdl.handle.net/1926/321
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  FFTRealToComplexConjugateImageFilter, FFTComplexConjugateToRealImageFilter, Log10ImageFilter, RescaleIntensityImageFilter

*/"
%javamethodmodifiers itk::simple::FFTShiftImageFilter::execute() "
/**Shift the zero-frequency components to center of the image.

*/"
%javamethodmodifiers itk::simple::FFTShift "/**
Shift the zero-frequency components to center of the image.

The fourier transform produce an image where the zero frequency components are in the corner of the image, making it difficult to understand. This filter shift the component to the center of the image. Note that with images with odd size, applying this filter twice will not produce the same image than the original one without using SetInverse(true) on one (and only one) of the two filters.
http://hdl.handle.net/1926/321
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  FFTRealToComplexConjugateImageFilter, FFTComplexConjugateToRealImageFilter, Log10ImageFilter, RescaleIntensityImageFilter

*/"
%javamethodmodifiers itk::simple::FFTShiftImageFilter::setInverse "/**
virtual void itk::FFTShiftImageFilter::SetInverse(bool _arg)

Set/Get whether the filter must perform an inverse transform or not. This option has no effect if none of the size of the input image is odd, but is required to be able to restore the original image if at least one of the size is odd.
*/"

%javamethodmodifiers itk::simple::FFTShiftImageFilter::getInverse "/**
virtual const bool& itk::FFTShiftImageFilter::GetInverse()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1FlipImageFilter.xml
%typemap(javaimports) itk::simple::FlipImageFilter "/** Flips an image across user specified axes.

 FlipImageFilterflips an image across user specified axes. The flip axes are set via method SetFlipAxes( array ) where the input is a FixedArray<bool,ImageDimension>. The image is flipped across axes for which array[i] is true.
In terms of grid coordinates the image is flipped within the LargestPossibleRegion of the input image. As such, the LargestPossibleRegion of the ouput image is the same as the input.
In terms of geometric coordinates, the output origin is such that the image is flipped with respect to the coordinate axes.

li {Images/FlipImageFilter,Flip an image over specified axes}

*/"
%javamethodmodifiers itk::simple::FlipImageFilter::execute() "
/**Flips an image across user specified axes.

*/"
%javamethodmodifiers itk::simple::Flip "/**
Flips an image across user specified axes.

 FlipImageFilterflips an image across user specified axes. The flip axes are set via method SetFlipAxes( array ) where the input is a FixedArray<bool,ImageDimension>. The image is flipped across axes for which array[i] is true.
In terms of grid coordinates the image is flipped within the LargestPossibleRegion of the input image. As such, the LargestPossibleRegion of the ouput image is the same as the input.
In terms of geometric coordinates, the output origin is such that the image is flipped with respect to the coordinate axes.

li {Images/FlipImageFilter,Flip an image over specified axes}

*/"
%javamethodmodifiers itk::simple::FlipImageFilter::setFlipAxes "/**
virtual void itk::FlipImageFilter::SetFlipAxes(FlipAxesArrayType _arg)

Set/Get the axis to be flipped. The image is flipped along axes for which array[i] is true.
*/"

%javamethodmodifiers itk::simple::FlipImageFilter::getFlipAxes "/**
virtual FlipAxesArrayType itk::FlipImageFilter::GetFlipAxes() const

*/"

%javamethodmodifiers itk::simple::FlipImageFilter::setFlipAboutOrigin "/**
virtual void itk::FlipImageFilter::SetFlipAboutOrigin(bool _arg)

*/"

%javamethodmodifiers itk::simple::FlipImageFilter::getFlipAboutOrigin "/**
virtual bool itk::FlipImageFilter::GetFlipAboutOrigin() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GeodesicActiveContourLevelSetImageFilter.xml
%typemap(javaimports) itk::simple::GeodesicActiveContourLevelSetImageFilter "/** Segments structures in images based on a user supplied edge potential map.

par IMPORTANT
The SegmentationLevelSetImageFilterclass and the GeodesicActiveContourLevelSetFunctionclass contain additional information necessary to gain full understanding of how to use this filter.
par OVERVIEW
This class is a level set method segmentation filter. An initial contour is propagated outwards (or inwards) until it ''sticks'' to the shape boundaries. This is done by using a level set speed function based on a user supplied edge potential map.
par INPUTS
This filter requires two inputs. The first input is a initial level set. The initial level set is a real image which contains the initial contour/surface as the zero level set. For example, a signed distance function from the initial contour/surface is typically used. Unlike the simpler ShapeDetectionLevelSetImageFilterthe initial contour does not have to lie wholly within the shape to be segmented. The intiial contour is allow to overlap the shape boundary. The extra advection term in the update equation behaves like a doublet and attracts the contour to the boundary. This approach for segmentation follows that of Caselles et al (1997).
par The second input is the feature image. For this filter, this is the edge potential map. General characteristics of an edge potential map is that it has values close to zero in regions near the edges and values close to one inside the shape itself. Typically, the edge potential map is compute from the image gradient, for example:
 f[ g(I) = 1 / ( 1 + | (nabla * G)(I)| ) f]   f[ g(I) = exp^{-|(nabla * G)(I)|} f]  
wheref$ I f$ is image intensity andf$ (nabla * G) f$ is the derivative of Gaussian operator.
par See SegmentationLevelSetImageFilterand SparseFieldLevelSetImageFilterfor more information on Inputs.
par PARAMETERS
The PropagationScaling parameter can be used to switch from propagation outwards (POSITIVE scaling parameter) versus propagating inwards (NEGATIVE scaling parameter).
This implementation allows the user to set the weights between the propagation, advection and curvature term using methods SetPropagationScaling(), SetAdvectionScaling(), SetCurvatureScaling(). In general, the larger the CurvatureScaling, the smoother the resulting contour. To follow the implementation in Caselles et al paper, set the PropagationScaling tof$ c f$ (the inflation or ballon force) and AdvectionScaling and CurvatureScaling both to 1.0.
par OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative values in the output image represent the inside of the segmented region and positive values in the image represent the outside of the segmented region. The zero crossings of the image correspond to the position of the propagating front.
par See SparseFieldLevelSetImageFilterand SegmentationLevelSetImageFilterfor more information.
par REFERENCES
par Geodesic Active Contours, V. Caselles, R. Kimmel and G. Sapiro. International Journal on Computer Vision, Vol 22, No. 1, pp 61-97, 1997
see  SegmentationLevelSetImageFilter
see  GeodesicActiveContourLevelSetFunction
see  SparseFieldLevelSetImageFilter

*/"
%javamethodmodifiers itk::simple::GeodesicActiveContourLevelSetImageFilter::execute() "
/**Segments structures in images based on a user supplied edge potential map.

*/"
%javamethodmodifiers itk::simple::GeodesicActiveContourLevelSet "/**
Segments structures in images based on a user supplied edge potential map.

par IMPORTANT
The SegmentationLevelSetImageFilterclass and the GeodesicActiveContourLevelSetFunctionclass contain additional information necessary to gain full understanding of how to use this filter.
par OVERVIEW
This class is a level set method segmentation filter. An initial contour is propagated outwards (or inwards) until it ''sticks'' to the shape boundaries. This is done by using a level set speed function based on a user supplied edge potential map.
par INPUTS
This filter requires two inputs. The first input is a initial level set. The initial level set is a real image which contains the initial contour/surface as the zero level set. For example, a signed distance function from the initial contour/surface is typically used. Unlike the simpler ShapeDetectionLevelSetImageFilterthe initial contour does not have to lie wholly within the shape to be segmented. The intiial contour is allow to overlap the shape boundary. The extra advection term in the update equation behaves like a doublet and attracts the contour to the boundary. This approach for segmentation follows that of Caselles et al (1997).
par The second input is the feature image. For this filter, this is the edge potential map. General characteristics of an edge potential map is that it has values close to zero in regions near the edges and values close to one inside the shape itself. Typically, the edge potential map is compute from the image gradient, for example:
 f[ g(I) = 1 / ( 1 + | (nabla * G)(I)| ) f]   f[ g(I) = exp^{-|(nabla * G)(I)|} f]  
wheref$ I f$ is image intensity andf$ (nabla * G) f$ is the derivative of Gaussian operator.
par See SegmentationLevelSetImageFilterand SparseFieldLevelSetImageFilterfor more information on Inputs.
par PARAMETERS
The PropagationScaling parameter can be used to switch from propagation outwards (POSITIVE scaling parameter) versus propagating inwards (NEGATIVE scaling parameter).
This implementation allows the user to set the weights between the propagation, advection and curvature term using methods SetPropagationScaling(), SetAdvectionScaling(), SetCurvatureScaling(). In general, the larger the CurvatureScaling, the smoother the resulting contour. To follow the implementation in Caselles et al paper, set the PropagationScaling tof$ c f$ (the inflation or ballon force) and AdvectionScaling and CurvatureScaling both to 1.0.
par OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative values in the output image represent the inside of the segmented region and positive values in the image represent the outside of the segmented region. The zero crossings of the image correspond to the position of the propagating front.
par See SparseFieldLevelSetImageFilterand SegmentationLevelSetImageFilterfor more information.
par REFERENCES
par Geodesic Active Contours, V. Caselles, R. Kimmel and G. Sapiro. International Journal on Computer Vision, Vol 22, No. 1, pp 61-97, 1997
see  SegmentationLevelSetImageFilter
see  GeodesicActiveContourLevelSetFunction
see  SparseFieldLevelSetImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GradientAnisotropicDiffusionImageFilter.xml
%typemap(javaimports) itk::simple::GradientAnisotropicDiffusionImageFilter "/** 
This filter performs anisotropic diffusion on a scalar itk::Imageusing the classic Perona-Malik, gradient magnitude based equation implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion, see itkAnisotropicDiffusionFunction and itkGradientNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any dimensionality. The output image will be a diffused copy of the input.
par Parameters
Please see the description of parameters given in itkAnisotropicDiffusionImageFilter.
see  AnisotropicDiffusionImageFilter
see  AnisotropicDiffusionFunction
see GradientAnisotropicDiffusionFunction

*/"
%javamethodmodifiers itk::simple::GradientAnisotropicDiffusionImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::GradientAnisotropicDiffusion "/**

This filter performs anisotropic diffusion on a scalar itk::Imageusing the classic Perona-Malik, gradient magnitude based equation implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion, see itkAnisotropicDiffusionFunction and itkGradientNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any dimensionality. The output image will be a diffused copy of the input.
par Parameters
Please see the description of parameters given in itkAnisotropicDiffusionImageFilter.
see  AnisotropicDiffusionImageFilter
see  AnisotropicDiffusionFunction
see GradientAnisotropicDiffusionFunction

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GradientMagnitudeRecursiveGaussianImageFilter.xml
%typemap(javaimports) itk::simple::GradientMagnitudeRecursiveGaussianImageFilter "/** Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/GradientMagnitudeRecursiveGaussianImageFilter,Find the gradient magnitude of the image first smoothed with a Gaussian kernel}

*/"
%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::execute() "
/**Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.

*/"
%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussian "/**
Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/GradientMagnitudeRecursiveGaussianImageFilter,Find the gradient magnitude of the image first smoothed with a Gaussian kernel}

*/"
%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::setSigma "/**
void itk::GradientMagnitudeRecursiveGaussianImageFilter::SetSigma(RealType sigma)

Set Sigma value. Sigma is measured in the units of image spacing.
*/"

%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::getSigma "/**
RealType itk::GradientMagnitudeRecursiveGaussianImageFilter::GetSigma()

*/"

%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::setNormalizeAcrossScale "/**
void itk::GradientMagnitudeRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

Define which normalization factor will be used for the Gaussiansee  RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::GradientMagnitudeRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleDilateImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleDilateImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

*/"
%javamethodmodifiers itk::simple::GrayscaleDilateImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleDilate "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleErodeImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleErodeImageFilter "/** gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

*/"
%javamethodmodifiers itk::simple::GrayscaleErodeImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleErode "/**
gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleFillholeImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleFillholeImageFilter "/** Remove local minima not connected to the boundary of the image.

 GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes are local minima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a hole are extrapolated across the hole.
This filter is used to smooth over local minima without affecting the values of local maxima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local minima.
This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the maximum pixel value in the input image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  ReconstructionByErosionImageFilter
see  MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleFillholeImageFilter::execute() "
/**Remove local minima not connected to the boundary of the image.

*/"
%javamethodmodifiers itk::simple::GrayscaleFillhole "/**
Remove local minima not connected to the boundary of the image.

 GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes are local minima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a hole are extrapolated across the hole.
This filter is used to smooth over local minima without affecting the values of local maxima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local minima.
This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the maximum pixel value in the input image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  ReconstructionByErosionImageFilter
see  MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleFillholeImageFilter::setFullyConnected "/**
virtual void itk::GrayscaleFillholeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::GrayscaleFillholeImageFilter::getFullyConnected "/**
virtual const bool& itk::GrayscaleFillholeImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGeodesicDilateImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleGeodesicDilateImageFilter "/** geodesic gray scale dilation of an image

Geodesic dilation operates on a marker image and a mask image. The marker image is dilated using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise minimum of the dilated marker image and the mask image.
Geodesic dilation is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by dilation. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be less than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByDilationImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicDiliateImageFilter as part of their implementation have been converted to use the ReconstructionByDilationImageFilter. The GrayscaleGeodesicDilateImageFilteris maintained for backward compatibility.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicDilateImageFilter::execute() "
/**geodesic gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicDilate "/**
geodesic gray scale dilation of an image

Geodesic dilation operates on a marker image and a mask image. The marker image is dilated using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise minimum of the dilated marker image and the mask image.
Geodesic dilation is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by dilation. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be less than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByDilationImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicDiliateImageFilter as part of their implementation have been converted to use the ReconstructionByDilationImageFilter. The GrayscaleGeodesicDilateImageFilteris maintained for backward compatibility.
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicDilateImageFilter::setRunOneIteration "/**
virtual void itk::GrayscaleGeodesicDilateImageFilter::SetRunOneIteration(bool _arg)

Set/Get whether the filter should run one iteration or until convergence. When run to convergence, this filter is equivalent to reconstruction by dilation. Default is off.
*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicDilateImageFilter::getRunOneIteration "/**
virtual bool itk::GrayscaleGeodesicDilateImageFilter::GetRunOneIteration() const

*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicDilateImageFilter::setFullyConnected "/**
virtual void itk::GrayscaleGeodesicDilateImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicDilateImageFilter::getFullyConnected "/**
virtual const bool& itk::GrayscaleGeodesicDilateImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGeodesicErodeImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleGeodesicErodeImageFilter "/** geodesic gray scale erosion of an image

Geodesic erosion operates on a marker image and a mask image. The marker image is eroded using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise maximum of the eroded marker image and the mask image.
Geodesic erosion is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by erosion. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be greater than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByErosionImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicErodeImageFilteras part of their implementation have been converted to use the ReconstructionByErosionImageFilter. The GrayscaleGeodesicErodeImageFilteris maintained for backward compatibility.
see  MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicErodeImageFilter::execute() "
/**geodesic gray scale erosion of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicErode "/**
geodesic gray scale erosion of an image

Geodesic erosion operates on a marker image and a mask image. The marker image is eroded using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise maximum of the eroded marker image and the mask image.
Geodesic erosion is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by erosion. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be greater than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByErosionImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicErodeImageFilteras part of their implementation have been converted to use the ReconstructionByErosionImageFilter. The GrayscaleGeodesicErodeImageFilteris maintained for backward compatibility.
see  MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGeodesicErodeImageFilter::setRunOneIteration "/**
virtual void itk::GrayscaleGeodesicErodeImageFilter::SetRunOneIteration(bool _arg)

Set/Get whether the filter should run one iteration or until convergence. When run to convergence, this filter is equivalent to reconstruction by erosion. Default is off.
*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicErodeImageFilter::getRunOneIteration "/**
virtual bool itk::GrayscaleGeodesicErodeImageFilter::GetRunOneIteration() const

*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicErodeImageFilter::setFullyConnected "/**
virtual void itk::GrayscaleGeodesicErodeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::GrayscaleGeodesicErodeImageFilter::getFullyConnected "/**
virtual const bool& itk::GrayscaleGeodesicErodeImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGrindPeakImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleGrindPeakImageFilter "/** Remove local maxima not connected to the boundary of the image.

 GrayscaleGrindPeakImageFilterremoves peaks in a grayscale image. Peaks are local maxima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a peak are extrapolated through the peak.
This filter is used to smooth over local maxima without affecting the values of local minima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local maxima.
This filter uses the GrayscaleGeodesicDilateImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the minimum pixel value in the input image.
This filter is the dual to the GrayscaleFillholeImageFilterwhich implements the Fillhole algorithm. Since it is a dual, it is somewhat superfluous but is provided as a convenience.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGrindPeakImageFilter::execute() "
/**Remove local maxima not connected to the boundary of the image.

*/"
%javamethodmodifiers itk::simple::GrayscaleGrindPeak "/**
Remove local maxima not connected to the boundary of the image.

 GrayscaleGrindPeakImageFilterremoves peaks in a grayscale image. Peaks are local maxima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a peak are extrapolated through the peak.
This filter is used to smooth over local maxima without affecting the values of local minima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local maxima.
This filter uses the GrayscaleGeodesicDilateImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the minimum pixel value in the input image.
This filter is the dual to the GrayscaleFillholeImageFilterwhich implements the Fillhole algorithm. Since it is a dual, it is somewhat superfluous but is provided as a convenience.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleGrindPeakImageFilter::setFullyConnected "/**
virtual void itk::GrayscaleGrindPeakImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::GrayscaleGrindPeakImageFilter::getFullyConnected "/**
virtual const bool& itk::GrayscaleGrindPeakImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleMorphologicalClosingImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleMorphologicalClosingImageFilter "/** gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalClosingImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalClosing "/**
gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleMorphologicalOpeningImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleMorphologicalOpeningImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalOpeningImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalOpening "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HausdorffDistanceImageFilter.xml
%typemap(javaimports) itk::simple::HausdorffDistanceImageFilter "/** Computes the Hausdorff distance between the set of non-zero pixels of two images.

 HausdorffDistanceImageFiltercomputes the distance between the set non-zero pixels of two images using the following formula: f[ H(A,B) = max(h(A,B),h(B,A)) f]  where f[ h(A,B) = max_{a in A} min_{b in B} | a - b| f]  is the directed Hausdorff distance andf$Af$ andf$Bf$ are respectively the set of non-zero pixels in the first and second input images.
In particular, this filter uses the DirectedHausdorffImageFilter inside to compute the two directed distances and then select the largest of the two.
The Hausdorff distance measures the degree of mismatch between two sets and behaves like a metric over the set of all closedm bounded sets - with properties of identity, symmetry and triangle inequality.
This filter requires the largest possible region of the first image and the same corresponding region in the second image. It behaves as filter with two input and one output. Thus it can be inserted in a pipeline with other filters. The filter passes the first input through unmodified.
This filter is templated over the two input image type. It assume both image have the same number of dimensions.
see  DirectedHausdorffDistanceImageFilter

*/"
%javamethodmodifiers itk::simple::HausdorffDistanceImageFilter::execute() "
/**Computes the Hausdorff distance between the set of non-zero pixels of two images.

*/"
%javamethodmodifiers itk::simple::HausdorffDistance "/**
Computes the Hausdorff distance between the set of non-zero pixels of two images.

 HausdorffDistanceImageFiltercomputes the distance between the set non-zero pixels of two images using the following formula: f[ H(A,B) = max(h(A,B),h(B,A)) f]  where f[ h(A,B) = max_{a in A} min_{b in B} | a - b| f]  is the directed Hausdorff distance andf$Af$ andf$Bf$ are respectively the set of non-zero pixels in the first and second input images.
In particular, this filter uses the DirectedHausdorffImageFilter inside to compute the two directed distances and then select the largest of the two.
The Hausdorff distance measures the degree of mismatch between two sets and behaves like a metric over the set of all closedm bounded sets - with properties of identity, symmetry and triangle inequality.
This filter requires the largest possible region of the first image and the same corresponding region in the second image. It behaves as filter with two input and one output. Thus it can be inserted in a pipeline with other filters. The filter passes the first input through unmodified.
This filter is templated over the two input image type. It assume both image have the same number of dimensions.
see  DirectedHausdorffDistanceImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HConcaveImageFilter.xml
%typemap(javaimports) itk::simple::HConcaveImageFilter "/** Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConcaveImageFilter::execute() "
/**Identify local minima whose depth below the baseline is greater than h.

*/"
%javamethodmodifiers itk::simple::HConcave "/**
Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConcaveImageFilter::setHeight "/**
virtual void itk::HConcaveImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
*/"

%javamethodmodifiers itk::simple::HConcaveImageFilter::getHeight "/**
virtual InputImagePixelType itk::HConcaveImageFilter::GetHeight() const

*/"

%javamethodmodifiers itk::simple::HConcaveImageFilter::setFullyConnected "/**
virtual void itk::HConcaveImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::HConcaveImageFilter::getFullyConnected "/**
virtual const bool& itk::HConcaveImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HConvexImageFilter.xml
%typemap(javaimports) itk::simple::HConvexImageFilter "/** Identify local maxima whose height above the baseline is greater than h.

 HConvexImageFilterextract local maxima that are more than h intensity units above the (local) background. This has the effect of extracting objects that are brighter than background by at least h intensity units.
This filter uses the HMaximaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConvexImageFilter::execute() "
/**Identify local maxima whose height above the baseline is greater than h.

*/"
%javamethodmodifiers itk::simple::HConvex "/**
Identify local maxima whose height above the baseline is greater than h.

 HConvexImageFilterextract local maxima that are more than h intensity units above the (local) background. This has the effect of extracting objects that are brighter than background by at least h intensity units.
This filter uses the HMaximaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConvexImageFilter::setHeight "/**
virtual void itk::HConvexImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
*/"

%javamethodmodifiers itk::simple::HConvexImageFilter::getHeight "/**
virtual InputImagePixelType itk::HConvexImageFilter::GetHeight() const

*/"

%javamethodmodifiers itk::simple::HConvexImageFilter::setFullyConnected "/**
virtual void itk::HConvexImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::HConvexImageFilter::getFullyConnected "/**
virtual const bool& itk::HConvexImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HistogramMatchingImageFilter.xml
%typemap(javaimports) itk::simple::HistogramMatchingImageFilter "/** Normalize the grayscale values between two image by histogram matching.

 HistogramMatchingImageFilternormalizes the grayscale values of a source image based on the grayscale values of a reference image. This filter uses a histogram matching technique where the histograms of the two images are matched only at a specified number of quantile values.
This filter was orginally designed to normalize MR images of the same MR protocol and same body part. The algorithm works best if background pixels are excluded from both the source and reference histograms. A simple background exclusion method is to exclude all pixels whose grayscale values are smaller than the mean grayscale value. ThresholdAtMeanIntensityOn()switches on this simple background exclusion method.
The source image can be set via either SetInput()or SetSourceImage(). The reference image can be set via SetReferenceImage().
 SetNumberOfHistogramLevels()sets the number of bins used when creating histograms of the source and reference images. SetNumberOfMatchPoints()governs the number of quantile values to be matched.
This filter assumes that both the source and reference are of the same type and that the input and output image type have the same number of dimension and have scalar pixel types.
*/"
%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::execute() "
/**Normalize the grayscale values between two image by histogram matching.

*/"
%javamethodmodifiers itk::simple::HistogramMatching "/**
Normalize the grayscale values between two image by histogram matching.

 HistogramMatchingImageFilternormalizes the grayscale values of a source image based on the grayscale values of a reference image. This filter uses a histogram matching technique where the histograms of the two images are matched only at a specified number of quantile values.
This filter was orginally designed to normalize MR images of the same MR protocol and same body part. The algorithm works best if background pixels are excluded from both the source and reference histograms. A simple background exclusion method is to exclude all pixels whose grayscale values are smaller than the mean grayscale value. ThresholdAtMeanIntensityOn()switches on this simple background exclusion method.
The source image can be set via either SetInput()or SetSourceImage(). The reference image can be set via SetReferenceImage().
 SetNumberOfHistogramLevels()sets the number of bins used when creating histograms of the source and reference images. SetNumberOfMatchPoints()governs the number of quantile values to be matched.
This filter assumes that both the source and reference are of the same type and that the input and output image type have the same number of dimension and have scalar pixel types.
*/"
%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::setNumberOfHistogramLevels "/**
virtual void itk::HistogramMatchingImageFilter::SetNumberOfHistogramLevels(SizeValueType _arg)

Set/Get the number of histogram levels used.
*/"

%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::getNumberOfHistogramLevels "/**
virtual SizeValueType itk::HistogramMatchingImageFilter::GetNumberOfHistogramLevels() const

*/"

%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::setNumberOfMatchPoints "/**
virtual void itk::HistogramMatchingImageFilter::SetNumberOfMatchPoints(SizeValueType _arg)

Set/Get the number of match points used.
*/"

%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::getNumberOfMatchPoints "/**
virtual SizeValueType itk::HistogramMatchingImageFilter::GetNumberOfMatchPoints() const

*/"

%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::setThresholdAtMeanIntensity "/**
virtual void itk::HistogramMatchingImageFilter::SetThresholdAtMeanIntensity(bool _arg)

Set/Get the threshold at mean intensity flag. If true, only source (reference) pixels which are greater than the mean source (reference) intensity is used in the histogram matching. If false, all pixels are used.
*/"

%javamethodmodifiers itk::simple::HistogramMatchingImageFilter::getThresholdAtMeanIntensity "/**
virtual bool itk::HistogramMatchingImageFilter::GetThresholdAtMeanIntensity() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HMaximaImageFilter.xml
%typemap(javaimports) itk::simple::HMaximaImageFilter "/** Suppress local maxima whose height above the baseline is less than h.

 HMaximaImageFiltersuppresses local maxima that are less than h intensity units above the (local) background. This has the effect of smoothing over the high parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMinimaImageFilterto suppress the local minima whose depth is less than h intensity units below the (local) background.
If the output of HMaximaImageFilteris subtracted from the original image, the signicant peaks in the image can be identified. This is what the HConvexImageFilterprovides.
This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image minus the height parameter h.
Geodesic morphology and the H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
The height parameter is set using SetHeight.
see  ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HMaximaImageFilter::execute() "
/**Suppress local maxima whose height above the baseline is less than h.

*/"
%javamethodmodifiers itk::simple::HMaxima "/**
Suppress local maxima whose height above the baseline is less than h.

 HMaximaImageFiltersuppresses local maxima that are less than h intensity units above the (local) background. This has the effect of smoothing over the high parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMinimaImageFilterto suppress the local minima whose depth is less than h intensity units below the (local) background.
If the output of HMaximaImageFilteris subtracted from the original image, the signicant peaks in the image can be identified. This is what the HConvexImageFilterprovides.
This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image minus the height parameter h.
Geodesic morphology and the H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
The height parameter is set using SetHeight.
see  ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HMaximaImageFilter::setHeight "/**
virtual void itk::HMaximaImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
*/"

%javamethodmodifiers itk::simple::HMaximaImageFilter::getHeight "/**
virtual InputImagePixelType itk::HMaximaImageFilter::GetHeight() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HMinimaImageFilter.xml
%typemap(javaimports) itk::simple::HMinimaImageFilter "/** Suppress local minima whose depth below the baseline is less than h.

 HMinimaImageFiltersuppresses local minima that are less than h intensity units below the (local) background. This has the effect of smoothing over the low parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMaximaImageFilterto suppress the local maxima whose height is less than h intensity units above the (local) background.
If original image is subtracted from the output of HMinimaImageFilter, the signicant valleys in the image can be identified. This is what the HConcaveImageFilterprovides.
This filter uses the GrayscaleGeodesicErodeImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image plus the height parameter h.
Geodesic morphology and the H-Minima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HMinimaImageFilter::execute() "
/**Suppress local minima whose depth below the baseline is less than h.

*/"
%javamethodmodifiers itk::simple::HMinima "/**
Suppress local minima whose depth below the baseline is less than h.

 HMinimaImageFiltersuppresses local minima that are less than h intensity units below the (local) background. This has the effect of smoothing over the low parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMaximaImageFilterto suppress the local maxima whose height is less than h intensity units above the (local) background.
If original image is subtracted from the output of HMinimaImageFilter, the signicant valleys in the image can be identified. This is what the HConcaveImageFilterprovides.
This filter uses the GrayscaleGeodesicErodeImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image plus the height parameter h.
Geodesic morphology and the H-Minima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see  GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see  MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HMinimaImageFilter::setHeight "/**
virtual void itk::HMinimaImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
*/"

%javamethodmodifiers itk::simple::HMinimaImageFilter::getHeight "/**
virtual InputImagePixelType itk::HMinimaImageFilter::GetHeight() const

*/"

%javamethodmodifiers itk::simple::HMinimaImageFilter::setFullyConnected "/**
virtual void itk::HMinimaImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::HMinimaImageFilter::getFullyConnected "/**
virtual const bool& itk::HMinimaImageFilter::GetFullyConnected()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1IntensityWindowingImageFilter.xml
%typemap(javaimports) itk::simple::IntensityWindowingImageFilter "/** Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.

 IntensityWindowingImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have and the lower and upper limits of the intensity window of the input image. This operation is very common in visualization, and can also be applied as a convenient preprocessing operation for image segmentation.
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.

li {ImageProcessing/IntensityWindowingImageFilter, IntensityWindowingImageFilter}

*/"
%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::execute() "
/**Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.

*/"
%javamethodmodifiers itk::simple::IntensityWindowing "/**
Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.

 IntensityWindowingImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have and the lower and upper limits of the intensity window of the input image. This operation is very common in visualization, and can also be applied as a convenient preprocessing operation for image segmentation.
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.

li {ImageProcessing/IntensityWindowingImageFilter, IntensityWindowingImageFilter}

*/"
%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::setWindowMinimum "/**
virtual void itk::IntensityWindowingImageFilter::SetWindowMinimum(InputPixelType _arg)

Set/Get the values of the maximum and minimum intensities of the input intensity window
*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::getWindowMinimum "/**
virtual const InputPixelType& itk::IntensityWindowingImageFilter::GetWindowMinimum()

*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::setWindowMaximum "/**
virtual void itk::IntensityWindowingImageFilter::SetWindowMaximum(InputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::getWindowMaximum "/**
virtual const InputPixelType& itk::IntensityWindowingImageFilter::GetWindowMaximum()

*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::setOutputMinimum "/**
virtual void itk::IntensityWindowingImageFilter::SetOutputMinimum(OutputPixelType _arg)

Set/Get the values of the maximum and minimum intensities of the outputimage
*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::getOutputMinimum "/**
virtual const OutputPixelType& itk::IntensityWindowingImageFilter::GetOutputMinimum()

*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::setOutputMaximum "/**
virtual void itk::IntensityWindowingImageFilter::SetOutputMaximum(OutputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::IntensityWindowingImageFilter::getOutputMaximum "/**
virtual const OutputPixelType& itk::IntensityWindowingImageFilter::GetOutputMaximum()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1InvertIntensityImageFilter.xml
%typemap(javaimports) itk::simple::InvertIntensityImageFilter "/** Invert intensity of an image.

 InvertIntensityImageFilterinvert intensity of pixels by subtracting pixel value to a maximum value. The maximum value can be set with SetMaximum and defaults the maximum of input pixel type. This filter can be used to invert, for example, a binary image, a distance map, etc.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

*/"
%javamethodmodifiers itk::simple::InvertIntensityImageFilter::execute() "
/**Invert intensity of an image.

*/"
%javamethodmodifiers itk::simple::InvertIntensity "/**
Invert intensity of an image.

 InvertIntensityImageFilterinvert intensity of pixels by subtracting pixel value to a maximum value. The maximum value can be set with SetMaximum and defaults the maximum of input pixel type. This filter can be used to invert, for example, a binary image, a distance map, etc.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

*/"
%javamethodmodifiers itk::simple::InvertIntensityImageFilter::setMaximum "/**
virtual void itk::InvertIntensityImageFilter::SetMaximum(InputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::InvertIntensityImageFilter::getMaximum "/**
virtual const InputPixelType& itk::InvertIntensityImageFilter::GetMaximum()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1IsoContourDistanceImageFilter.xml
%typemap(javaimports) itk::simple::IsoContourDistanceImageFilter "/** Compute an approximate distance from an interpolated isocontour to the close grid points.

For standard level set algorithms, it is useful to periodically reinitialize the evolving image to prevent numerical accuracy problems in computing derivatives. This reinitialization is done by computing a signed distance map to the current level set. This class provides the first step in this reinitialization by computing an estimate of the distance from the interpolated isocontour to the pixels (or voxels) that are close to it, i.e. for which the isocontour crosses a segment between them and one of their direct neighbors. This class supports narrowbanding. If the input narrowband is provided, the algorithm will only locate the level set within the input narrowband.
Implementation of this class is based on Fast and Accurate Redistancing for Level Set Methods `Krissian K. and Westin C.F.', EUROCAST NeuroImaging Workshop Las Palmas Spain, Ninth International Conference on Computer Aided Systems Theory , pages 48-51, Feb 2003.
*/"
%javamethodmodifiers itk::simple::IsoContourDistanceImageFilter::execute() "
/**Compute an approximate distance from an interpolated isocontour to the close grid points.

*/"
%javamethodmodifiers itk::simple::IsoContourDistance "/**
Compute an approximate distance from an interpolated isocontour to the close grid points.

For standard level set algorithms, it is useful to periodically reinitialize the evolving image to prevent numerical accuracy problems in computing derivatives. This reinitialization is done by computing a signed distance map to the current level set. This class provides the first step in this reinitialization by computing an estimate of the distance from the interpolated isocontour to the pixels (or voxels) that are close to it, i.e. for which the isocontour crosses a segment between them and one of their direct neighbors. This class supports narrowbanding. If the input narrowband is provided, the algorithm will only locate the level set within the input narrowband.
Implementation of this class is based on Fast and Accurate Redistancing for Level Set Methods `Krissian K. and Westin C.F.', EUROCAST NeuroImaging Workshop Las Palmas Spain, Ninth International Conference on Computer Aided Systems Theory , pages 48-51, Feb 2003.
*/"
%javamethodmodifiers itk::simple::IsoContourDistanceImageFilter::setLevelSetValue "/**
virtual void itk::IsoContourDistanceImageFilter::SetLevelSetValue(InputPixelType _arg)

Set/Get the value of the level set to be located. The default value is 0.
*/"

%javamethodmodifiers itk::simple::IsoContourDistanceImageFilter::getLevelSetValue "/**
virtual InputPixelType itk::IsoContourDistanceImageFilter::GetLevelSetValue() const

*/"

%javamethodmodifiers itk::simple::IsoContourDistanceImageFilter::setFarValue "/**
virtual void itk::IsoContourDistanceImageFilter::SetFarValue(PixelType _arg)

Set/Get the value of the level set to be located. The default value is 0.
*/"

%javamethodmodifiers itk::simple::IsoContourDistanceImageFilter::getFarValue "/**
virtual PixelType itk::IsoContourDistanceImageFilter::GetFarValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelContourImageFilter.xml
%typemap(javaimports) itk::simple::LabelContourImageFilter "/** Labels the pixels on the border of the objects in a labeled image.

 LabelContourImageFiltertakes a labeled image as input, where the pixels in the objects are the pixels with a value different of the BackgroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue. The labels of the object are the same in the input and in the output image.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  BinaryContourImageFilter

*/"
%javamethodmodifiers itk::simple::LabelContourImageFilter::execute() "
/**Labels the pixels on the border of the objects in a labeled image.

*/"
%javamethodmodifiers itk::simple::LabelContour "/**
Labels the pixels on the border of the objects in a labeled image.

 LabelContourImageFiltertakes a labeled image as input, where the pixels in the objects are the pixels with a value different of the BackgroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue. The labels of the object are the same in the input and in the output image.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  BinaryContourImageFilter

*/"
%javamethodmodifiers itk::simple::LabelContourImageFilter::setFullyConnected "/**
virtual void itk::LabelContourImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff.note For objects that are 1 pixel wide, use FullyConnectedOn.

*/"

%javamethodmodifiers itk::simple::LabelContourImageFilter::getFullyConnected "/**
virtual const bool& itk::LabelContourImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::LabelContourImageFilter::setBackgroundValue "/**
virtual void itk::LabelContourImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the background value used to identify the objects and mark the pixels not on the border of the objects.
*/"

%javamethodmodifiers itk::simple::LabelContourImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::LabelContourImageFilter::GetBackgroundValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelMapMaskImageFilter.xml
%typemap(javaimports) itk::simple::LabelMapMaskImageFilter "/** Mask and image with a LabelMap.

 LabelMapMaskImageFiltermask the content of an input image according to the content of the input LabelMap. The masked pixel of the input image are set to the BackgroundValue. LabelMapMaskImageFiltercan keep the input image for one label only, with Negated = false (the default) or it can mask the input image for a single label, when Negated equals true. In Both cases, the label is set with SetLabel().
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::execute() "
/**Mask and image with a LabelMap.

*/"
%javamethodmodifiers itk::simple::LabelMapMask "/**
Mask and image with a LabelMap.

 LabelMapMaskImageFiltermask the content of an input image according to the content of the input LabelMap. The masked pixel of the input image are set to the BackgroundValue. LabelMapMaskImageFiltercan keep the input image for one label only, with Negated = false (the default) or it can mask the input image for a single label, when Negated equals true. In Both cases, the label is set with SetLabel().
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::setLabel "/**
virtual void itk::LabelMapMaskImageFilter::SetLabel(InputImagePixelType _arg)

The label to mask or to not mask, depending on the value of the Negated ivar.
*/"

%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::getLabel "/**
virtual InputImagePixelType itk::LabelMapMaskImageFilter::GetLabel() const

*/"

%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::setBackgroundValue "/**
virtual void itk::LabelMapMaskImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the value used as background in the output image. Defaults to NumericTraits<PixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::LabelMapMaskImageFilter::GetBackgroundValue() const

*/"

%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::setNegated "/**
virtual void itk::LabelMapMaskImageFilter::SetNegated(bool _arg)

Set/Get whether the Label should be masked or not.
*/"

%javamethodmodifiers itk::simple::LabelMapMaskImageFilter::getNegated "/**
virtual const bool& itk::LabelMapMaskImageFilter::GetNegated()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelMapOverlayImageFilter.xml
%typemap(javaimports) itk::simple::LabelMapOverlayImageFilter "/** Apply a colormap to a label map and put it on top of the input image.

Apply a colormap to a label map and put it on top of the input image. The set of colors is a good selection of distinct colors. The opacity of the label map can be defined by the user. A background label produce a gray pixel with the same intensity than the input one.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapOverlayImageFilter::execute() "
/**Apply a colormap to a label map and put it on top of the input image.

*/"
%javamethodmodifiers itk::simple::LabelMapOverlay "/**
Apply a colormap to a label map and put it on top of the input image.

Apply a colormap to a label map and put it on top of the input image. The set of colors is a good selection of distinct colors. The opacity of the label map can be defined by the user. A background label produce a gray pixel with the same intensity than the input one.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapOverlayImageFilter::setOpacity "/**
virtual void itk::LabelMapOverlayImageFilter::SetOpacity(double _arg)

Set/Get the opacity of the colored label image. The value must be between 0 and 1
*/"

%javamethodmodifiers itk::simple::LabelMapOverlayImageFilter::getOpacity "/**
virtual const double& itk::LabelMapOverlayImageFilter::GetOpacity()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelMapToBinaryImageFilter.xml
%typemap(javaimports) itk::simple::LabelMapToBinaryImageFilter "/** Convert a LabelMapto a binary image.

 LabelMapToBinaryImageFilterto a binary image. All the objects in the image are used as foreground. The background values of the original binary image can be restored by passing this image to the filter with the SetBackgroundImage()method.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  LabelMapToLabelImageFilter, LabelMapMaskImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapToBinaryImageFilter::execute() "
/**Convert a LabelMapto a binary image.

*/"
%javamethodmodifiers itk::simple::LabelMapToBinary "/**
Convert a LabelMapto a binary image.

 LabelMapToBinaryImageFilterto a binary image. All the objects in the image are used as foreground. The background values of the original binary image can be restored by passing this image to the filter with the SetBackgroundImage()method.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  LabelMapToLabelImageFilter, LabelMapMaskImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapToBinaryImageFilter::setBackgroundValue "/**
virtual void itk::LabelMapToBinaryImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the value used as background in the output image. Defaults to NumericTraits<PixelType>::NonpositiveMin().
*/"

%javamethodmodifiers itk::simple::LabelMapToBinaryImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::LabelMapToBinaryImageFilter::GetBackgroundValue() const

*/"

%javamethodmodifiers itk::simple::LabelMapToBinaryImageFilter::setForegroundValue "/**
virtual void itk::LabelMapToBinaryImageFilter::SetForegroundValue(OutputImagePixelType _arg)

Set/Get the value used as foreground in the output image. Defaults to NumericTraits<PixelType>::max().
*/"

%javamethodmodifiers itk::simple::LabelMapToBinaryImageFilter::getForegroundValue "/**
virtual OutputImagePixelType itk::LabelMapToBinaryImageFilter::GetForegroundValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelMapToLabelImageFilter.xml
%typemap(javaimports) itk::simple::LabelMapToLabelImageFilter "/** Converts a LabelMapto a labeled image.

 LabelMapToBinaryImageFilterto a label image.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapMaskImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapToLabelImageFilter::execute() "
/**Converts a LabelMapto a labeled image.

*/"
%javamethodmodifiers itk::simple::LabelMapToLabel "/**
Converts a LabelMapto a labeled image.

 LabelMapToBinaryImageFilterto a label image.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapMaskImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelMapToRGBImageFilter.xml
%typemap(javaimports) itk::simple::LabelMapToRGBImageFilter "/** Convert a LabelMapto a colored image.

author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapMaskImageFilter

*/"
%javamethodmodifiers itk::simple::LabelMapToRGBImageFilter::execute() "
/**Convert a LabelMapto a colored image.

*/"
%javamethodmodifiers itk::simple::LabelMapToRGB "/**
Convert a LabelMapto a colored image.

author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see  LabelMapToBinaryImageFilter, LabelMapMaskImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LaplacianImageFilter.xml
%typemap(javaimports) itk::simple::LaplacianImageFilter "/** 
This filter computes the Laplacian of a scalar-valued image. The Laplacian is an isotropic measure of the 2nd spatial derivative of an image. The Laplacian of an image highlights regions of rapid intensity change and is therefore often used for edge detection. Often, the Laplacian is applied to an image that has first been smoothed with a Gaussian filter in order to reduce its sensitivity to noise.
par The Laplacian at each pixel location is computed by convolution with the itk::LaplacianOperator.
par Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary dimension. The output is a scalar-valued itk::Image.
warning The pixel type of the input and output images must be of real type (float or double). ConceptChecking is used here to enforce the input pixel type. You will get a compilation error if the pixel type of the input and output images is not float or double.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator
see  LaplacianOperator

li {ImageProcessing/LaplacianImageFilter,Compute the Laplacian of an image}

*/"
%javamethodmodifiers itk::simple::LaplacianImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::Laplacian "/**

This filter computes the Laplacian of a scalar-valued image. The Laplacian is an isotropic measure of the 2nd spatial derivative of an image. The Laplacian of an image highlights regions of rapid intensity change and is therefore often used for edge detection. Often, the Laplacian is applied to an image that has first been smoothed with a Gaussian filter in order to reduce its sensitivity to noise.
par The Laplacian at each pixel location is computed by convolution with the itk::LaplacianOperator.
par Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary dimension. The output is a scalar-valued itk::Image.
warning The pixel type of the input and output images must be of real type (float or double). ConceptChecking is used here to enforce the input pixel type. You will get a compilation error if the pixel type of the input and output images is not float or double.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator
see  LaplacianOperator

li {ImageProcessing/LaplacianImageFilter,Compute the Laplacian of an image}

*/"
%javamethodmodifiers itk::simple::LaplacianImageFilter::setUseImageSpacing "/**
virtual void itk::LaplacianImageFilter::SetUseImageSpacing(bool _arg)

Set/Get whether or not the filter will use the spacing of the input image in its calculations
*/"

%javamethodmodifiers itk::simple::LaplacianImageFilter::getUseImageSpacing "/**
virtual bool itk::LaplacianImageFilter::GetUseImageSpacing() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LaplacianRecursiveGaussianImageFilter.xml
%typemap(javaimports) itk::simple::LaplacianRecursiveGaussianImageFilter "/** Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/LaplacianRecursiveGaussianImageFilter,Compute the Laplacian of an image}

*/"
%javamethodmodifiers itk::simple::LaplacianRecursiveGaussianImageFilter::execute() "
/**Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.

*/"
%javamethodmodifiers itk::simple::LaplacianRecursiveGaussian "/**
Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/LaplacianRecursiveGaussianImageFilter,Compute the Laplacian of an image}

*/"
%javamethodmodifiers itk::simple::LaplacianRecursiveGaussianImageFilter::setSigma "/**
void itk::LaplacianRecursiveGaussianImageFilter::SetSigma(RealType sigma)

Set Sigma value. Sigma is measured in the units of image spacing.
*/"

%javamethodmodifiers itk::simple::LaplacianRecursiveGaussianImageFilter::setNormalizeAcrossScale "/**
void itk::LaplacianRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

Define which normalization factor will be used for the Gaussiansee  RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::LaplacianRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::LaplacianRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LaplacianSharpeningImageFilter.xml
%typemap(javaimports) itk::simple::LaplacianSharpeningImageFilter "/** 
This filter sharpens an image using a Laplacian. LaplacianSharpening highlights regions of rapid intensity change and therefore highlights or enhances the edges. The result is an image that appears more in focus.
par The LaplacianSharpening at each pixel location is computed by
convolution with the itk::LaplacianOperator.
par Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary dimension. The output is a scalar-valued itk::Image.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator
see  LaplacianOperator

*/"
%javamethodmodifiers itk::simple::LaplacianSharpeningImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::LaplacianSharpening "/**

This filter sharpens an image using a Laplacian. LaplacianSharpening highlights regions of rapid intensity change and therefore highlights or enhances the edges. The result is an image that appears more in focus.
par The LaplacianSharpening at each pixel location is computed by
convolution with the itk::LaplacianOperator.
par Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary dimension. The output is a scalar-valued itk::Image.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator
see  LaplacianOperator

*/"
%javamethodmodifiers itk::simple::LaplacianSharpeningImageFilter::setUseImageSpacing "/**
virtual void itk::LaplacianSharpeningImageFilter::SetUseImageSpacing(bool _arg)

Set/Get whether or not the filter will use the spacing of the input image in its calculations
*/"

%javamethodmodifiers itk::simple::LaplacianSharpeningImageFilter::getUseImageSpacing "/**
virtual bool itk::LaplacianSharpeningImageFilter::GetUseImageSpacing() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1Log10ImageFilter.xml
%typemap(javaimports) itk::simple::Log10ImageFilter "/** Computes the vcl_log10(x) pixel-wise
-.

*/"
%javamethodmodifiers itk::simple::Log10ImageFilter::execute() "
/**Computes the vcl_log10(x) pixel-wise
-.

*/"
%javamethodmodifiers itk::simple::Log10 "/**
Computes the vcl_log10(x) pixel-wise
-.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LogImageFilter.xml
%typemap(javaimports) itk::simple::LogImageFilter "/** Computes the vcl_log(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::LogImageFilter::execute() "
/**Computes the vcl_log(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Log "/**
Computes the vcl_log(x) pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MagnitudeAndPhaseToComplexImageFilter.xml
%typemap(javaimports) itk::simple::MagnitudeAndPhaseToComplexImageFilter "/** Implements pixel-wise conversion of magnitude and phase data into complex voxels.

This filter is parametrized over the types of the two input images and the type of the output image.
The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
%javamethodmodifiers itk::simple::MagnitudeAndPhaseToComplexImageFilter::execute() "
/**Implements pixel-wise conversion of magnitude and phase data into complex voxels.

*/"
%javamethodmodifiers itk::simple::MagnitudeAndPhaseToComplex "/**
Implements pixel-wise conversion of magnitude and phase data into complex voxels.

This filter is parametrized over the types of the two input images and the type of the output image.
The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaskImageFilter.xml
%typemap(javaimports) itk::simple::MaskImageFilter "/** Implements an operator for pixel-wise masking of the input image with the mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = pixel_input_image else pixel_output_image = outside_value
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see  MaskNegatedImageFilter

li {ImageProcessing/MaskImageFilter,Apply a mask to an image}

*/"
%javamethodmodifiers itk::simple::MaskImageFilter::execute() "
/**Implements an operator for pixel-wise masking of the input image with the mask.

*/"
%javamethodmodifiers itk::simple::Mask "/**
Implements an operator for pixel-wise masking of the input image with the mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = pixel_input_image else pixel_output_image = outside_value
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see  MaskNegatedImageFilter

li {ImageProcessing/MaskImageFilter,Apply a mask to an image}

*/"
%javamethodmodifiers itk::simple::MaskImageFilter::setOutsideValue "/**
void itk::MaskImageFilter::SetOutsideValue(const typename TOutputImage::PixelType &outsideValue)

Method to explicitly set the outside value of the mask. Defaults to 0
*/"

%javamethodmodifiers itk::simple::MaskImageFilter::getOutsideValue "/**
const TOutputImage::PixelType& itk::MaskImageFilter::GetOutsideValue() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaskNegatedImageFilter.xml
%typemap(javaimports) itk::simple::MaskNegatedImageFilter "/** Implements an operator for pixel-wise masking of the input image with the negative of a mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = output_value else pixel_output_image = pixel_input_image
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see  MaskImageFilter

*/"
%javamethodmodifiers itk::simple::MaskNegatedImageFilter::execute() "
/**Implements an operator for pixel-wise masking of the input image with the negative of a mask.

*/"
%javamethodmodifiers itk::simple::MaskNegated "/**
Implements an operator for pixel-wise masking of the input image with the negative of a mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = output_value else pixel_output_image = pixel_input_image
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see  MaskImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaximumImageFilter.xml
%typemap(javaimports) itk::simple::MaximumImageFilter "/** Implements a pixel-wise operator Max(a,b) between two images.

The pixel values of the output image are the maximum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MaximumImageFilter,Pixel wise compare two input images and set the output pixel to their max}

*/"
%javamethodmodifiers itk::simple::MaximumImageFilter::execute() "
/**Implements a pixel-wise operator Max(a,b) between two images.

*/"
%javamethodmodifiers itk::simple::Maximum "/**
Implements a pixel-wise operator Max(a,b) between two images.

The pixel values of the output image are the maximum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MaximumImageFilter,Pixel wise compare two input images and set the output pixel to their max}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MinimumImageFilter.xml
%typemap(javaimports) itk::simple::MinimumImageFilter "/** Implements a pixel-wise operator Min(a,b) between two images.

The pixel values of the output image are the minimum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults. + *

li {ImageProcessing/MinimumImageFilter,Pixel wise compare two input images and set the output pixel to their min}

*/"
%javamethodmodifiers itk::simple::MinimumImageFilter::execute() "
/**Implements a pixel-wise operator Min(a,b) between two images.

*/"
%javamethodmodifiers itk::simple::Minimum "/**
Implements a pixel-wise operator Min(a,b) between two images.

The pixel values of the output image are the minimum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults. + *

li {ImageProcessing/MinimumImageFilter,Pixel wise compare two input images and set the output pixel to their min}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MinMaxCurvatureFlowImageFilter.xml
%typemap(javaimports) itk::simple::MinMaxCurvatureFlowImageFilter "/** Denoise an image using min/max curvature flow.

 MinMaxCurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = max(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ min(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is the average intensity obtained in the direction perpendicular to the gradient at pointf$ x f$ at the extrema of the local neighborhood.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a MinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images, however for dimensions greater than 3D, an expensive brute-force search is used to compute the local threshold.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  MinMaxCurvatureFlowFunction
see  CurvatureFlowImageFilter
see  BinaryMinMaxCurvatureFlowImageFilter

*/"
%javamethodmodifiers itk::simple::MinMaxCurvatureFlowImageFilter::execute() "
/**Denoise an image using min/max curvature flow.

*/"
%javamethodmodifiers itk::simple::MinMaxCurvatureFlow "/**
Denoise an image using min/max curvature flow.

 MinMaxCurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = max(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ min(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is the average intensity obtained in the direction perpendicular to the gradient at pointf$ x f$ at the extrema of the local neighborhood.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a MinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images, however for dimensions greater than 3D, an expensive brute-force search is used to compute the local threshold.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see  MinMaxCurvatureFlowFunction
see  CurvatureFlowImageFilter
see  BinaryMinMaxCurvatureFlowImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MirrorPadImageFilter.xml
%typemap(javaimports) itk::simple::MirrorPadImageFilter "/** Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  WrapPadImageFilter, ConstantPadImageFilter

*/"
%javamethodmodifiers itk::simple::MirrorPadImageFilter::execute() "
/**Increase the image size by padding with replicants of the input image value.

*/"
%javamethodmodifiers itk::simple::MirrorPad "/**
Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  WrapPadImageFilter, ConstantPadImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ModulusImageFilter.xml
%typemap(javaimports) itk::simple::ModulusImageFilter "/** Computes the modulus (x % dividend) pixel-wise.

The input pixel type must support the c++ modulus operator (%).
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::ModulusImageFilter::execute() "
/**Computes the modulus (x % dividend) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Modulus "/**
Computes the modulus (x % dividend) pixel-wise.

The input pixel type must support the c++ modulus operator (%).
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::ModulusImageFilter::setDividend "/**
virtual void itk::ModulusImageFilter::SetDividend(InputPixelType _arg)

Set/Get the dividend
*/"

%javamethodmodifiers itk::simple::ModulusImageFilter::getDividend "/**
virtual const InputPixelType& itk::ModulusImageFilter::GetDividend()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MorphologicalGradientImageFilter.xml
%typemap(javaimports) itk::simple::MorphologicalGradientImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::MorphologicalGradientImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::MorphologicalGradient "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see  MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MultiplyByConstantImageFilter.xml
%typemap(javaimports) itk::simple::MultiplyByConstantImageFilter "/** Multiply input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter
li {ImageProcessing/MultiplyByConstantImageFilter,Multiply every pixel in an image by a constant}


*/"
%javamethodmodifiers itk::simple::MultiplyByConstantImageFilter::execute() "
/**Multiply input pixels by a constant.

*/"
%javamethodmodifiers itk::simple::MultiplyByConstant "/**
Multiply input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter
li {ImageProcessing/MultiplyByConstantImageFilter,Multiply every pixel in an image by a constant}


*/"
%javamethodmodifiers itk::simple::MultiplyByConstantImageFilter::setConstant "/**
void itk::MultiplyByConstantImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
*/"

%javamethodmodifiers itk::simple::MultiplyByConstantImageFilter::getConstant "/**
const TConstant& itk::MultiplyByConstantImageFilter::GetConstant() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MultiplyImageFilter.xml
%typemap(javaimports) itk::simple::MultiplyImageFilter "/** Implements an operator for pixel-wise multiplication of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MultiplyImageFilter,Multiply two images together}

*/"
%javamethodmodifiers itk::simple::MultiplyImageFilter::execute() "
/**Implements an operator for pixel-wise multiplication of two images.

*/"
%javamethodmodifiers itk::simple::Multiply "/**
Implements an operator for pixel-wise multiplication of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MultiplyImageFilter,Multiply two images together}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1N4MRIBiasFieldCorrectionImageFilter.xml
%typemap(javaimports) itk::simple::N4MRIBiasFieldCorrectionImageFilter "/** Implementation of the N4 MRI bias field correction algorithm.

The nonparametric nonuniform intensity normalization (N3) algorithm, as introduced by Sled et al. in 1998 is a method for correcting nonuniformity associated with MR images. The algorithm assumes a simple parametric model (Gaussian) for the bias field and does not require tissue class segmentation. In addition, there are only a couple of parameters to tune with the default values performing quite well. N3 has been publicly available as a set of perl scripts (http://www.bic.mni.mcgill.ca/ServicesSoftwareAdvancedImageProcessingTools/HomePage)
The N4 algorithm, encapsulated with this class, is a variation of the original N3 algorithm with the additional benefits of an improved B-spline fitting routine which allows for multiple resolutions to be used during the correction process. We also modify the iterative update component of algorithm such that the residual bias field is continually updated
Notes for the user: 1. Since much of the image manipulation is done in the log space of the intensities, input images with negative and small values (< 1) can produce poor results. 2. The original authors recommend performing the bias field correction on a downsampled version of the original image. 3. A binary mask or a weighted image can be supplied. If a binary mask is specified, those voxels in the input image which correspond to the voxels in the mask image with a value equal to m_MaskLabel, are used to estimate the bias field. If a confidence image is specified, the input voxels are weighted in the b-spline fitting routine according to the confidence voxel values. 4. The filter returns the corrected image. If the bias field is wanted, one can reconstruct it using the class itkBSplineControlPointImageFilter. See the IJ article and the test file for an example. 5. The 'Z' parameter in Sled's 1998 paper is the square root of the class variable 'm_WienerFilterNoise'.
The basic algorithm iterates between sharpening the intensity histogram of the corrected input image and spatially smoothing those results with a B-spline scalar field estimate of the bias field.
author Nicholas J. Tustison
Contributed by Nicholas J. Tustison, James C. Gee in the Insight Journal paper:http://hdl.handle.net/10380/3053
par REFERENCE
J.G. Sled, A.P. Zijdenbos and A.C. Evans. A Nonparametric Method for Automatic Correction of Intensity Nonuniformity in MRI Data IEEE Transactions on Medical Imaging, Vol 17, No 1. Feb 1998.
N.J. Tustison, B.B. Avants, P.A. Cook, Y. Zheng, A. Egan, P.A. Yushkevich, and J.C. Gee. N4ITK: Improved N3 Bias Correction IEEE Transactions on Medical Imaging, 29(6):1310-1320, June 2010.
*/"
%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::execute() "
/**Implementation of the N4 MRI bias field correction algorithm.

*/"
%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrection "/**
Implementation of the N4 MRI bias field correction algorithm.

The nonparametric nonuniform intensity normalization (N3) algorithm, as introduced by Sled et al. in 1998 is a method for correcting nonuniformity associated with MR images. The algorithm assumes a simple parametric model (Gaussian) for the bias field and does not require tissue class segmentation. In addition, there are only a couple of parameters to tune with the default values performing quite well. N3 has been publicly available as a set of perl scripts (http://www.bic.mni.mcgill.ca/ServicesSoftwareAdvancedImageProcessingTools/HomePage)
The N4 algorithm, encapsulated with this class, is a variation of the original N3 algorithm with the additional benefits of an improved B-spline fitting routine which allows for multiple resolutions to be used during the correction process. We also modify the iterative update component of algorithm such that the residual bias field is continually updated
Notes for the user: 1. Since much of the image manipulation is done in the log space of the intensities, input images with negative and small values (< 1) can produce poor results. 2. The original authors recommend performing the bias field correction on a downsampled version of the original image. 3. A binary mask or a weighted image can be supplied. If a binary mask is specified, those voxels in the input image which correspond to the voxels in the mask image with a value equal to m_MaskLabel, are used to estimate the bias field. If a confidence image is specified, the input voxels are weighted in the b-spline fitting routine according to the confidence voxel values. 4. The filter returns the corrected image. If the bias field is wanted, one can reconstruct it using the class itkBSplineControlPointImageFilter. See the IJ article and the test file for an example. 5. The 'Z' parameter in Sled's 1998 paper is the square root of the class variable 'm_WienerFilterNoise'.
The basic algorithm iterates between sharpening the intensity histogram of the corrected input image and spatially smoothing those results with a B-spline scalar field estimate of the bias field.
author Nicholas J. Tustison
Contributed by Nicholas J. Tustison, James C. Gee in the Insight Journal paper:http://hdl.handle.net/10380/3053
par REFERENCE
J.G. Sled, A.P. Zijdenbos and A.C. Evans. A Nonparametric Method for Automatic Correction of Intensity Nonuniformity in MRI Data IEEE Transactions on Medical Imaging, Vol 17, No 1. Feb 1998.
N.J. Tustison, B.B. Avants, P.A. Cook, Y. Zheng, A. Egan, P.A. Yushkevich, and J.C. Gee. N4ITK: Improved N3 Bias Correction IEEE Transactions on Medical Imaging, 29(6):1310-1320, June 2010.
*/"
%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setConvergenceThreshold "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetConvergenceThreshold(RealType _arg)

Set the convergence threshold. Convergence is determined by the coefficient of variation of the difference image between the current bias field estimate and the previous estimate. If this value is less than the specified threshold, the algorithm proceeds to the next fitting level or terminates if it is at the last level.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getConvergenceThreshold "/**
virtual RealType itk::N4MRIBiasFieldCorrectionImageFilter::GetConvergenceThreshold() const

Get the convergence threshold. Convergence is determined by the coefficient of variation of the difference image between the current bias field estimate and the previous estimate. If this value is less than the specified threshold, the algorithm proceeds to the next fitting level or terminates if it is at the last level.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setMaximumNumberOfIterations "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetMaximumNumberOfIterations(VariableSizeArrayType _arg)

Set the maximum number of iterations specified at each fitting level. Default = 50.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getMaximumNumberOfIterations "/**
virtual VariableSizeArrayType itk::N4MRIBiasFieldCorrectionImageFilter::GetMaximumNumberOfIterations() const

Get the maximum number of iterations specified at each fitting level. Default = 50.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setBiasFieldFullWidthAtHalfMaximum "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetBiasFieldFullWidthAtHalfMaximum(RealType _arg)

Set the full width at half maximum parameter characterizing the width of the Gaussian deconvolution. Default = 0.15.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getBiasFieldFullWidthAtHalfMaximum "/**
virtual RealType itk::N4MRIBiasFieldCorrectionImageFilter::GetBiasFieldFullWidthAtHalfMaximum() const

Get the full width at half maximum parameter characterizing the width of the Gaussian deconvolution. Default = 0.15.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setWienerFilterNoise "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetWienerFilterNoise(RealType _arg)

Set the noise estimate defining the Wiener filter. Default = 0.01.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getWienerFilterNoise "/**
virtual RealType itk::N4MRIBiasFieldCorrectionImageFilter::GetWienerFilterNoise() const

Get the noise estimate defining the Wiener filter. Default = 0.01.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setNumberOfHistogramBins "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetNumberOfHistogramBins(unsigned int _arg)

Set number of bins defining the log input intensity histogram. Default = 200.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getNumberOfHistogramBins "/**
virtual unsigned int itk::N4MRIBiasFieldCorrectionImageFilter::GetNumberOfHistogramBins() const

Get number of bins defining the log input intensity histogram. Default = 200.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setNumberOfControlPoints "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetNumberOfControlPoints(ArrayType _arg)

Set the control point grid size definining the B-spline estimate of the scalar bias field. In each dimension, the B-spline mesh size is equal to the number of control points in that dimension minus the spline order. Default = 4 control points in each dimension for a mesh size of 1 in each dimension.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getNumberOfControlPoints "/**
virtual ArrayType itk::N4MRIBiasFieldCorrectionImageFilter::GetNumberOfControlPoints() const

Get the control point grid size definining the B-spline estimate of the scalar bias field. In each dimension, the B-spline mesh size is equal to the number of control points in that dimension minus the spline order. Default = 4 control points in each dimension for a mesh size of 1 in each dimension.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::setSplineOrder "/**
virtual void itk::N4MRIBiasFieldCorrectionImageFilter::SetSplineOrder(unsigned int _arg)

Set the spline order defining the bias field estimate. Default = 3.
*/"

%javamethodmodifiers itk::simple::N4MRIBiasFieldCorrectionImageFilter::getSplineOrder "/**
virtual unsigned int itk::N4MRIBiasFieldCorrectionImageFilter::GetSplineOrder() const

Get the spline order defining the bias field estimate. Default = 3.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1NeighborhoodConnectedImageFilter.xml
%typemap(javaimports) itk::simple::NeighborhoodConnectedImageFilter "/** Label pixels that are connected to a seed and lie within a neighborhood.

 NeighborhoodConnectedImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND whose neighbors all lie within a Lower and Upper threshold range.
*/"
%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::execute() "
/**Label pixels that are connected to a seed and lie within a neighborhood.

*/"
%javamethodmodifiers itk::simple::NeighborhoodConnected "/**
Label pixels that are connected to a seed and lie within a neighborhood.

 NeighborhoodConnectedImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND whose neighbors all lie within a Lower and Upper threshold range.
*/"
%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::setUpper "/**
virtual void itk::NeighborhoodConnectedImageFilter::SetUpper(InputImagePixelType _arg)

Set/Get the upper threshold. The default is the largest possible value for the InputPixelType.
*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::getUpper "/**
virtual InputImagePixelType itk::NeighborhoodConnectedImageFilter::GetUpper() const

*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::setLower "/**
virtual void itk::NeighborhoodConnectedImageFilter::SetLower(InputImagePixelType _arg)

Set/Get the lower threshold. The default is 0.
*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::getLower "/**
virtual InputImagePixelType itk::NeighborhoodConnectedImageFilter::GetLower() const

*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::setReplaceValue "/**
virtual void itk::NeighborhoodConnectedImageFilter::SetReplaceValue(OutputImagePixelType _arg)

Set/Get value to replace thresholded pixels. Pixels that lie * within Lower and Upper (inclusive) will be replaced with this value. The default is 1.
*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::getReplaceValue "/**
virtual OutputImagePixelType itk::NeighborhoodConnectedImageFilter::GetReplaceValue() const

*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::setRadius "/**
virtual void itk::NeighborhoodConnectedImageFilter::SetRadius(InputImageSizeType _arg)

Set the radius of the neighborhood used for a mask.
*/"

%javamethodmodifiers itk::simple::NeighborhoodConnectedImageFilter::getRadius "/**
virtual const InputImageSizeType& itk::NeighborhoodConnectedImageFilter::GetRadius()

Get the radius of the neighborhood used to compute the median
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1NormalizeImageFilter.xml
%typemap(javaimports) itk::simple::NormalizeImageFilter "/** Normalize an image by setting its mean to zero and variance to one.

 NormalizeImageFiltershifts and scales an image so that the pixels in the image have a zero mean and unit variance. This filter uses StatisticsImageFilterto compute the mean and variance of the input and then applies ShiftScaleImageFilterto shift and scale the pixels.
NB: since this filter normalizes the data to lie within -1 to 1, integral types will produce an image that DOES NOT HAVE a unit variance.

li {ImageProcessing/NormalizeImageFilter,Normalize an image}

*/"
%javamethodmodifiers itk::simple::NormalizeImageFilter::execute() "
/**Normalize an image by setting its mean to zero and variance to one.

*/"
%javamethodmodifiers itk::simple::Normalize "/**
Normalize an image by setting its mean to zero and variance to one.

 NormalizeImageFiltershifts and scales an image so that the pixels in the image have a zero mean and unit variance. This filter uses StatisticsImageFilterto compute the mean and variance of the input and then applies ShiftScaleImageFilterto shift and scale the pixels.
NB: since this filter normalizes the data to lie within -1 to 1, integral types will produce an image that DOES NOT HAVE a unit variance.

li {ImageProcessing/NormalizeImageFilter,Normalize an image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1NotImageFilter.xml
%typemap(javaimports) itk::simple::NotImageFilter "/** Implements the NOT logical operator pixel-wise on an image.

This class is parametrized over the types of an input image and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical NOT operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( !input_pixel )
Where ! is the unary NOT operator in C++.
*/"
%javamethodmodifiers itk::simple::NotImageFilter::execute() "
/**Implements the NOT logical operator pixel-wise on an image.

*/"
%javamethodmodifiers itk::simple::Not "/**
Implements the NOT logical operator pixel-wise on an image.

This class is parametrized over the types of an input image and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical NOT operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( !input_pixel )
Where ! is the unary NOT operator in C++.
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OpeningByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::OpeningByReconstructionImageFilter "/** Opening by reconstruction of an image.

This filter preserves regions, in the foreground, that can completely contain the structuring element. At the same time, this filter eliminates all other regions of foreground pixels. Contrary to the mophological opening, the opening by reconstruction preserves the shape of the components that are not removed by erosion. The opening by reconstruction of an image f is defined as:
OpeningByReconstruction(f) = DilationByRecontruction(f, Erosion(f)).
Opening by reconstruction not only removes structures destroyed by the erosion, but also levels down the contrast of the brightest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Opening by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  GrayscaleMorphologicalOpeningImageFilter

*/"
%javamethodmodifiers itk::simple::OpeningByReconstructionImageFilter::execute() "
/**Opening by reconstruction of an image.

*/"
%javamethodmodifiers itk::simple::OpeningByReconstruction "/**
Opening by reconstruction of an image.

This filter preserves regions, in the foreground, that can completely contain the structuring element. At the same time, this filter eliminates all other regions of foreground pixels. Contrary to the mophological opening, the opening by reconstruction preserves the shape of the components that are not removed by erosion. The opening by reconstruction of an image f is defined as:
OpeningByReconstruction(f) = DilationByRecontruction(f, Erosion(f)).
Opening by reconstruction not only removes structures destroyed by the erosion, but also levels down the contrast of the brightest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Opening by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see  GrayscaleMorphologicalOpeningImageFilter

*/"
%javamethodmodifiers itk::simple::OpeningByReconstructionImageFilter::setFullyConnected "/**
virtual void itk::OpeningByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
*/"

%javamethodmodifiers itk::simple::OpeningByReconstructionImageFilter::getFullyConnected "/**
virtual const bool& itk::OpeningByReconstructionImageFilter::GetFullyConnected()

*/"

%javamethodmodifiers itk::simple::OpeningByReconstructionImageFilter::setPreserveIntensities "/**
virtual void itk::OpeningByReconstructionImageFilter::SetPreserveIntensities(bool _arg)

Set/Get whether the original intensities of the image retained for those pixels unaffected by the opening by reconstrcution. If Off, the output pixel contrast will be reduced.
*/"

%javamethodmodifiers itk::simple::OpeningByReconstructionImageFilter::getPreserveIntensities "/**
virtual const bool& itk::OpeningByReconstructionImageFilter::GetPreserveIntensities()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OrImageFilter.xml
%typemap(javaimports) itk::simple::OrImageFilter "/** Implements the OR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical OR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel | input2_pixel )
Where | is the boolean OR operator in C++.

li {ImageProcessing/OrImageFilter,Binary OR two images}

*/"
%javamethodmodifiers itk::simple::OrImageFilter::execute() "
/**Implements the OR logical operator pixel-wise between two images.

*/"
%javamethodmodifiers itk::simple::Or "/**
Implements the OR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical OR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel | input2_pixel )
Where | is the boolean OR operator in C++.

li {ImageProcessing/OrImageFilter,Binary OR two images}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OtsuThresholdImageFilter.xml
%typemap(javaimports) itk::simple::OtsuThresholdImageFilter "/** Threshold an image using the Otsu Threshold.

This filter creates a binary thresholded image that separates an image into foreground and background components. The filter computes the threshold using the OtsuThresholdImageCalculatorand applies that theshold to the input image using the BinaryThresholdImageFilter. The NunberOfHistogram bins can be set for the Calculator. The InsideValue and OutsideValue can be set for the BinaryThresholdImageFilter.
see  OtsuThresholdImageCalculator
see  BinaryThresholdImageFilter

li {Segmentation/OtsuThresholdImageFilter,Separate foreground and background using Otsu's method}

*/"
%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::execute() "
/**Threshold an image using the Otsu Threshold.

*/"
%javamethodmodifiers itk::simple::OtsuThreshold "/**
Threshold an image using the Otsu Threshold.

This filter creates a binary thresholded image that separates an image into foreground and background components. The filter computes the threshold using the OtsuThresholdImageCalculatorand applies that theshold to the input image using the BinaryThresholdImageFilter. The NunberOfHistogram bins can be set for the Calculator. The InsideValue and OutsideValue can be set for the BinaryThresholdImageFilter.
see  OtsuThresholdImageCalculator
see  BinaryThresholdImageFilter

li {Segmentation/OtsuThresholdImageFilter,Separate foreground and background using Otsu's method}

*/"
%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::setInsideValue "/**
virtual void itk::OtsuThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::getInsideValue "/**
virtual OutputPixelType itk::OtsuThresholdImageFilter::GetInsideValue() const

Get the inside pixel value.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::setOutsideValue "/**
virtual void itk::OtsuThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::getOutsideValue "/**
virtual OutputPixelType itk::OtsuThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::setNumberOfHistogramBins "/**
virtual void itk::OtsuThresholdImageFilter::SetNumberOfHistogramBins(SizeValueType _arg)

Set/Get the number of histogram bins. Defaults is 128.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::getNumberOfHistogramBins "/**
virtual SizeValueType itk::OtsuThresholdImageFilter::GetNumberOfHistogramBins() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1PasteImageFilter.xml
%typemap(javaimports) itk::simple::PasteImageFilter "/** Paste an image into another image.

 PasteImageFilterallows you to take a section of one image and paste into another image. The SetDestinationIndex()method prescribes where in the first input to start pasting data from the second input. The SetSourceRegion method prescribes the section of the second image to paste into the first. If the output requested region does not have include the SourceRegion after it has been repositioned to DestinationIndex, then the output will just be a copy of the input.
The two inputs and output image will have the same pixel type.

li {ImageProcessing/PasteImageFilter,Paste a part of one image into another image}

*/"
%javamethodmodifiers itk::simple::PasteImageFilter::execute() "
/**Paste an image into another image.

*/"
%javamethodmodifiers itk::simple::Paste "/**
Paste an image into another image.

 PasteImageFilterallows you to take a section of one image and paste into another image. The SetDestinationIndex()method prescribes where in the first input to start pasting data from the second input. The SetSourceRegion method prescribes the section of the second image to paste into the first. If the output requested region does not have include the SourceRegion after it has been repositioned to DestinationIndex, then the output will just be a copy of the input.
The two inputs and output image will have the same pixel type.

li {ImageProcessing/PasteImageFilter,Paste a part of one image into another image}

*/"
%javamethodmodifiers itk::simple::PasteImageFilter::setDestinationIndex "/**
virtual void itk::PasteImageFilter::SetDestinationIndex(InputImageIndexType _arg)

Set/Get the destination index (where in the first input the second input will be pasted.
*/"

%javamethodmodifiers itk::simple::PasteImageFilter::getDestinationIndex "/**
virtual InputImageIndexType itk::PasteImageFilter::GetDestinationIndex() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1PermuteAxesImageFilter.xml
%typemap(javaimports) itk::simple::PermuteAxesImageFilter "/** Permutes the image axes according to a user specified order.

PermuateAxesImageFilter permutes the image axes according to a user specified order. The permutation order is set via method SetOrder( order ) where the input is an array of ImageDimension number of unsigned int. The elements of the array must be a rearrangment of the numbers from 0 to ImageDimension - 1.
The i-th axis of the output image corresponds with the order[i]-th axis of the input image.
The output meta image information (LargestPossibleRegion, spacing, origin) is computed by permuting the corresponding input meta information.

li {ImageProcessing/PermuteAxesImageFilter,Switch the axes of an image}

*/"
%javamethodmodifiers itk::simple::PermuteAxesImageFilter::execute() "
/**Permutes the image axes according to a user specified order.

*/"
%javamethodmodifiers itk::simple::PermuteAxes "/**
Permutes the image axes according to a user specified order.

PermuateAxesImageFilter permutes the image axes according to a user specified order. The permutation order is set via method SetOrder( order ) where the input is an array of ImageDimension number of unsigned int. The elements of the array must be a rearrangment of the numbers from 0 to ImageDimension - 1.
The i-th axis of the output image corresponds with the order[i]-th axis of the input image.
The output meta image information (LargestPossibleRegion, spacing, origin) is computed by permuting the corresponding input meta information.

li {ImageProcessing/PermuteAxesImageFilter,Switch the axes of an image}

*/"
%javamethodmodifiers itk::simple::PermuteAxesImageFilter::setOrder "/**
void itk::PermuteAxesImageFilter::SetOrder(const PermuteOrderArrayType &order)

Set the permutation order. The elements of order must be a rearrangement of the numbers from 0 to ImageDimension - 1.
*/"

%javamethodmodifiers itk::simple::PermuteAxesImageFilter::getOrder "/**
virtual const PermuteOrderArrayType& itk::PermuteAxesImageFilter::GetOrder()

Get the permutation order.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RealAndImaginaryToComplexImageFilter.xml
%typemap(javaimports) itk::simple::RealAndImaginaryToComplexImageFilter "/** Implements pixel-wise conversion of real and imaginary data into complex voxels.

This filter is parametrized over the types of the two input images and the type of the output image.
The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
%javamethodmodifiers itk::simple::RealAndImaginaryToComplexImageFilter::execute() "
/**Implements pixel-wise conversion of real and imaginary data into complex voxels.

*/"
%javamethodmodifiers itk::simple::RealAndImaginaryToComplex "/**
Implements pixel-wise conversion of real and imaginary data into complex voxels.

This filter is parametrized over the types of the two input images and the type of the output image.
The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)
*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RecursiveGaussianImageFilter.xml
%typemap(javaimports) itk::simple::RecursiveGaussianImageFilter "/** Base class for computing IIR convolution with an approximation of a Gaussian kernel.

 f[ frac{ 1 }{ sigma sqrt{ 2 pi } } exp{ left( - frac{x^2}{ 2 sigma^2 } right) } f]  
 RecursiveGaussianImageFilteris the base class for recursive filters that approximate convolution with the Gaussian kernel. This class implements the recursive filtering method proposed by R.Deriche in IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, Fast Algorithms for Low-Level Vision
Details of the implementation are described in the technical report: R. Deriche, Recursively Implementing The Gaussian and Its Derivatives, INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz
Further improvements of the algorithm are described in: G. Farneback & C.-F. Westin, On Implementation of Recursive Gaussian Filters, so far unpublished.
As compared to itk::DiscreteGaussianImageFilter, this filter tends to be faster for large kernels, and it can take the derivative of the blurred image in one step. Also, note that we have itk::RecursiveGaussianImageFilter::SetSigma(), but itk::DiscreteGaussianImageFilter::SetVariance().
see  DiscreteGaussianImageFilter
li {EdgesAndGradients/RecursiveGaussianImageFilter,Find higher derivatives of an image}


*/"
%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::execute() "
/**Base class for computing IIR convolution with an approximation of a Gaussian kernel.

*/"
%javamethodmodifiers itk::simple::RecursiveGaussian "/**
Base class for computing IIR convolution with an approximation of a Gaussian kernel.

 f[ frac{ 1 }{ sigma sqrt{ 2 pi } } exp{ left( - frac{x^2}{ 2 sigma^2 } right) } f]  
 RecursiveGaussianImageFilteris the base class for recursive filters that approximate convolution with the Gaussian kernel. This class implements the recursive filtering method proposed by R.Deriche in IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, Fast Algorithms for Low-Level Vision
Details of the implementation are described in the technical report: R. Deriche, Recursively Implementing The Gaussian and Its Derivatives, INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz
Further improvements of the algorithm are described in: G. Farneback & C.-F. Westin, On Implementation of Recursive Gaussian Filters, so far unpublished.
As compared to itk::DiscreteGaussianImageFilter, this filter tends to be faster for large kernels, and it can take the derivative of the blurred image in one step. Also, note that we have itk::RecursiveGaussianImageFilter::SetSigma(), but itk::DiscreteGaussianImageFilter::SetVariance().
see  DiscreteGaussianImageFilter
li {EdgesAndGradients/RecursiveGaussianImageFilter,Find higher derivatives of an image}


*/"
%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::setSigma "/**
virtual void itk::RecursiveGaussianImageFilter::SetSigma(ScalarRealType _arg)

Set/Get the Sigma, measured in world coordinates, of the Gaussian kernel. The default is 1.0.
*/"

%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::getSigma "/**
virtual ScalarRealType itk::RecursiveGaussianImageFilter::GetSigma() const

Set/Get the Sigma, measured in world coordinates, of the Gaussian kernel. The default is 1.0.
*/"

%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::setNormalizeAcrossScale "/**
virtual void itk::RecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool _arg)

Set/Get the flag for normalizing the gaussian over scale-space.
This flag enables the analysis of the differential shape of features independent of their size ( both pixels and physical size ). Following the notation of Tony Lindeberg:
Let f[ L(x; t) = g(x; t) ast f(x) f]  be the scale-space representation of image f[ f(x) f]  where f[ g(x; t) = frac{1}{ sqrt{ 2 pi t} } exp{ left( -frac{x^2}{ 2 t } right) } f]  is the Gaussian function and f[astf]  denotes convolution. This is a change from above with f[ t = sigma^2 f]  .
Then the normalized derivative operator for normalized coordinates across scale is:
 f[ partial_xi = sqrt{t} partial_x f]  
The resulting scaling factor is f[ sigma^N f]  where N is the order of the derivative.
When this flag is ON the filter will be normalized in such a way that the values of derivatives are not biased by the size of the object. That is to say the maximum value a feature reaches across scale is independent of the scale of the object.
For analyzing an image across scale-space you want to enable this flag. It is disabled by default.
note Not all scale space axioms are satisfied by this filter, some are only approximated. Particularly, at fine scales ( say less than 1 pixel ) other methods such as a discrete Gaussian kernel should be considered.

*/"

%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::RecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

*/"

%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::setOrder "/**
virtual void itk::RecursiveGaussianImageFilter::SetOrder(OrderEnumType _arg)

Set/Get the Order of the Gaussian to convolve with.
li ZeroOrder is equivalent to convolving with a Gaussian. This is the default.
li FirstOrder is equivalent to convolving with the first derivative of a Gaussian.
li SecondOrder is equivalent to convolving with the second derivative of a Gaussian.

*/"

%javamethodmodifiers itk::simple::RecursiveGaussianImageFilter::getOrder "/**
virtual OrderEnumType itk::RecursiveGaussianImageFilter::GetOrder() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RegionOfInterestImageFilter.xml
%typemap(javaimports) itk::simple::RegionOfInterestImageFilter "/** Extract a region of interest from the input image.

This filter produces an output image of the same dimension as the input image. The user specifies the region of the input image that will be contained in the output image. The origin coordinates of the output images will be computed in such a way that if mapped to physical space, the output image will overlay the input image with perfect registration. In other words, a registration process between the output image and the input image will return an identity transform.
If you are interested in changing the dimension of the image, you may want to consider the ExtractImageFilter. For example for extracting a 2D image from a slice of a 3D image.
The region to extract is set using the method SetRegionOfInterest.
see  ExtractImageFilter

li {ImageProcessing/RegionOfInterestImageFilter,Extract a portion of an image (region of interest)}

*/"
%javamethodmodifiers itk::simple::RegionOfInterestImageFilter::execute() "
/**Extract a region of interest from the input image.

*/"
%javamethodmodifiers itk::simple::RegionOfInterest "/**
Extract a region of interest from the input image.

This filter produces an output image of the same dimension as the input image. The user specifies the region of the input image that will be contained in the output image. The origin coordinates of the output images will be computed in such a way that if mapped to physical space, the output image will overlay the input image with perfect registration. In other words, a registration process between the output image and the input image will return an identity transform.
If you are interested in changing the dimension of the image, you may want to consider the ExtractImageFilter. For example for extracting a 2D image from a slice of a 3D image.
The region to extract is set using the method SetRegionOfInterest.
see  ExtractImageFilter

li {ImageProcessing/RegionOfInterestImageFilter,Extract a portion of an image (region of interest)}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RescaleIntensityImageFilter.xml
%typemap(javaimports) itk::simple::RescaleIntensityImageFilter "/** Applies a linear transformation to the intensity levels of the input Image.

 RescaleIntensityImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.
The following equation gives the mapping of the intensity values
par  f[ outputPixel = ( inputPixel - inputMin) cdot frac{(outputMax - outputMin )}{(inputMax - inputMin)} + outputMin f]  
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image are computed internally using the MinimumMaximumImageCalculator. Users are not supposed to set those values in this filter. If you need a filter where you can set the minimum and maximum values of the input, please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear transformation for the intensity, then please use the ShiftScaleImageFilter.
see  IntensityWindowingImageFilter

li {ImageProcessing/RescaleIntensityImageFilter,Rescale the intensity values of an image to a specified range}

*/"
%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::execute() "
/**Applies a linear transformation to the intensity levels of the input Image.

*/"
%javamethodmodifiers itk::simple::RescaleIntensity "/**
Applies a linear transformation to the intensity levels of the input Image.

 RescaleIntensityImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.
The following equation gives the mapping of the intensity values
par  f[ outputPixel = ( inputPixel - inputMin) cdot frac{(outputMax - outputMin )}{(inputMax - inputMin)} + outputMin f]  
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image are computed internally using the MinimumMaximumImageCalculator. Users are not supposed to set those values in this filter. If you need a filter where you can set the minimum and maximum values of the input, please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear transformation for the intensity, then please use the ShiftScaleImageFilter.
see  IntensityWindowingImageFilter

li {ImageProcessing/RescaleIntensityImageFilter,Rescale the intensity values of an image to a specified range}

*/"
%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::setOutputMinimum "/**
virtual void itk::RescaleIntensityImageFilter::SetOutputMinimum(OutputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::getOutputMinimum "/**
virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMinimum()

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::setOutputMaximum "/**
virtual void itk::RescaleIntensityImageFilter::SetOutputMaximum(OutputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::getOutputMaximum "/**
virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMaximum()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ShapeDetectionLevelSetImageFilter.xml
%typemap(javaimports) itk::simple::ShapeDetectionLevelSetImageFilter "/** Segments structures in images based on a user supplied edge potential map.

par IMPORTANT
The SegmentationLevelSetImageFilterclass and the ShapeDetectionLevelSetFunctionclass contain additional information necessary to gain full understanding of how to use this filter.
par OVERVIEW
This class is a level set method segmentation filter. An initial contour is propagated outwards (or inwards) until it ''sticks'' to the shape boundaries. This is done by using a level set speed function based on a user supplied edge potential map. This approach for segmentation follows that of Malladi et al (1995).
par INPUTS
This filter requires two inputs. The first input is a initial level set. The initial level set is a real image which contains the initial contour/surface as the zero level set. For example, a signed distance function from the initial contour/surface is typically used. Note that for this algorithm the initial contour has to be wholly within (or wholly outside) the structure to be segmented.
par The second input is the feature image. For this filter, this is the edge potential map. General characteristics of an edge potential map is that it has values close to zero in regions near the edges and values close to one inside the shape itself. Typically, the edge potential map is compute from the image gradient, for example:
 f[ g(I) = 1 / ( 1 + | (nabla * G)(I)| ) f]   f[ g(I) = exp^{-|(nabla * G)(I)|} f]  
wheref$ I f$ is image intensity andf$ (nabla * G) f$ is the derivative of Gaussian operator.
par See SegmentationLevelSetImageFilterand SparseFieldLevelSetImageFilterfor more information on Inputs.
par PARAMETERS
The PropagationScaling parameter can be used to switch from propagation outwards (POSITIVE scaling parameter) versus propagating inwards (NEGATIVE scaling parameter).
The smoothness of the resulting contour/surface can be adjusted using a combination of PropagationScaling and CurvatureScaling parameters. The larger the CurvatureScaling parameter, the smoother the resulting contour. The CurvatureScaling parameter should be non-negative for proper operation of this algorithm. To follow the implementation in Malladi et al paper, set the PropagtionScaling tof$pm 1.0f$ and CurvatureScaling tof$ epsilon f$ .
Note that there is no advection term for this filter. Setting the advection scaling will have no effect.
par OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative values in the output image represent the inside of the segmentated region and positive values in the image represent the outside of the segmented region. The zero crossings of the image correspond to the position of the propagating front.
par See SparseFieldLevelSetImageFilterand SegmentationLevelSetImageFilterfor more information.
par REFERENCES
par Shape Modeling with Front Propagation: A Level Set Approach, R. Malladi, J. A. Sethian and B. C. Vermuri. IEEE Trans. on Pattern Analysis and Machine Intelligence, Vol 17, No. 2, pp 158-174, February 1995
see  SegmentationLevelSetImageFilter
see  ShapeDetectionLevelSetFunction
see  SparseFieldLevelSetImageFilter

*/"
%javamethodmodifiers itk::simple::ShapeDetectionLevelSetImageFilter::execute() "
/**Segments structures in images based on a user supplied edge potential map.

*/"
%javamethodmodifiers itk::simple::ShapeDetectionLevelSet "/**
Segments structures in images based on a user supplied edge potential map.

par IMPORTANT
The SegmentationLevelSetImageFilterclass and the ShapeDetectionLevelSetFunctionclass contain additional information necessary to gain full understanding of how to use this filter.
par OVERVIEW
This class is a level set method segmentation filter. An initial contour is propagated outwards (or inwards) until it ''sticks'' to the shape boundaries. This is done by using a level set speed function based on a user supplied edge potential map. This approach for segmentation follows that of Malladi et al (1995).
par INPUTS
This filter requires two inputs. The first input is a initial level set. The initial level set is a real image which contains the initial contour/surface as the zero level set. For example, a signed distance function from the initial contour/surface is typically used. Note that for this algorithm the initial contour has to be wholly within (or wholly outside) the structure to be segmented.
par The second input is the feature image. For this filter, this is the edge potential map. General characteristics of an edge potential map is that it has values close to zero in regions near the edges and values close to one inside the shape itself. Typically, the edge potential map is compute from the image gradient, for example:
 f[ g(I) = 1 / ( 1 + | (nabla * G)(I)| ) f]   f[ g(I) = exp^{-|(nabla * G)(I)|} f]  
wheref$ I f$ is image intensity andf$ (nabla * G) f$ is the derivative of Gaussian operator.
par See SegmentationLevelSetImageFilterand SparseFieldLevelSetImageFilterfor more information on Inputs.
par PARAMETERS
The PropagationScaling parameter can be used to switch from propagation outwards (POSITIVE scaling parameter) versus propagating inwards (NEGATIVE scaling parameter).
The smoothness of the resulting contour/surface can be adjusted using a combination of PropagationScaling and CurvatureScaling parameters. The larger the CurvatureScaling parameter, the smoother the resulting contour. The CurvatureScaling parameter should be non-negative for proper operation of this algorithm. To follow the implementation in Malladi et al paper, set the PropagtionScaling tof$pm 1.0f$ and CurvatureScaling tof$ epsilon f$ .
Note that there is no advection term for this filter. Setting the advection scaling will have no effect.
par OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative values in the output image represent the inside of the segmentated region and positive values in the image represent the outside of the segmented region. The zero crossings of the image correspond to the position of the propagating front.
par See SparseFieldLevelSetImageFilterand SegmentationLevelSetImageFilterfor more information.
par REFERENCES
par Shape Modeling with Front Propagation: A Level Set Approach, R. Malladi, J. A. Sethian and B. C. Vermuri. IEEE Trans. on Pattern Analysis and Machine Intelligence, Vol 17, No. 2, pp 158-174, February 1995
see  SegmentationLevelSetImageFilter
see  ShapeDetectionLevelSetFunction
see  SparseFieldLevelSetImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ShiftScaleImageFilter.xml
%typemap(javaimports) itk::simple::ShiftScaleImageFilter "/** Shift and scale the pixels in an image.

 ShiftScaleImageFiltershifts the input pixel by Shift (default 0.0) and then scales the pixel by Scale (default 1.0). All computattions are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel, the value is clamped at the NonpositiveMin and max of the pixel type.
*/"
%javamethodmodifiers itk::simple::ShiftScaleImageFilter::execute() "
/**Shift and scale the pixels in an image.

*/"
%javamethodmodifiers itk::simple::ShiftScale "/**
Shift and scale the pixels in an image.

 ShiftScaleImageFiltershifts the input pixel by Shift (default 0.0) and then scales the pixel by Scale (default 1.0). All computattions are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel, the value is clamped at the NonpositiveMin and max of the pixel type.
*/"
%javamethodmodifiers itk::simple::ShiftScaleImageFilter::setShift "/**
virtual void itk::ShiftScaleImageFilter::SetShift(RealType _arg)

Set/Get the amount to Shift each Pixel. The shift is followed by a Scale.
*/"

%javamethodmodifiers itk::simple::ShiftScaleImageFilter::getShift "/**
virtual RealType itk::ShiftScaleImageFilter::GetShift() const

*/"

%javamethodmodifiers itk::simple::ShiftScaleImageFilter::setScale "/**
virtual void itk::ShiftScaleImageFilter::SetScale(RealType _arg)

Set/Get the amount to Scale each Pixel. The Scale is applied after the Shift.
*/"

%javamethodmodifiers itk::simple::ShiftScaleImageFilter::getScale "/**
virtual RealType itk::ShiftScaleImageFilter::GetScale() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ShrinkImageFilter.xml
%typemap(javaimports) itk::simple::ShrinkImageFilter "/** Reduce the size of an image by an integer factor in each dimension.

 ShrinkImageFilterreduces the size of an image by an integer factor in each dimension. The algorithm implemented is a simple subsample. The output image size in each dimension is given by:
outputSize[j] = max( vcl_floor(inputSize[j]/shrinkFactor[j]), 1 );
NOTE: The physical centers of the input and output will be the same. Because of this, the Origin of the output may not be the same as the Origin of the input. Since this filter produces an image which is a different resolution, origin and with different pixel spacing than its input image, it needs to override several of the methods defined in ProcessObjectin order to properly manage the pipeline execution model. In particular, this filter overrides ProcessObject::GenerateInputRequestedRegion()and ProcessObject::GenerateOutputInformation().
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Images/ShrinkImageFilter,Shrink an image}

*/"
%javamethodmodifiers itk::simple::ShrinkImageFilter::execute() "
/**Reduce the size of an image by an integer factor in each dimension.

*/"
%javamethodmodifiers itk::simple::Shrink "/**
Reduce the size of an image by an integer factor in each dimension.

 ShrinkImageFilterreduces the size of an image by an integer factor in each dimension. The algorithm implemented is a simple subsample. The output image size in each dimension is given by:
outputSize[j] = max( vcl_floor(inputSize[j]/shrinkFactor[j]), 1 );
NOTE: The physical centers of the input and output will be the same. Because of this, the Origin of the output may not be the same as the Origin of the input. Since this filter produces an image which is a different resolution, origin and with different pixel spacing than its input image, it needs to override several of the methods defined in ProcessObjectin order to properly manage the pipeline execution model. In particular, this filter overrides ProcessObject::GenerateInputRequestedRegion()and ProcessObject::GenerateOutputInformation().
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Images/ShrinkImageFilter,Shrink an image}

*/"
%javamethodmodifiers itk::simple::ShrinkImageFilter::setShrinkFactors "/**
virtual void itk::ShrinkImageFilter::SetShrinkFactors(ShrinkFactorsType _arg)

Set the shrink factors. Values are clamped to a minimum value of 1. Default is 1 for all dimensions.
*/"

%javamethodmodifiers itk::simple::ShrinkImageFilter::getShrinkFactors "/**
virtual const ShrinkFactorsType& itk::ShrinkImageFilter::GetShrinkFactors()

Get the shrink factors.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SigmoidImageFilter.xml
%typemap(javaimports) itk::simple::SigmoidImageFilter "/** Computes the sigmoid function pixel-wise.

A linear transformation is applied first on the argument of the sigmoid fuction. The resulting total transfrom is given by
 f[ f(x) = (Max-Min) cdot frac{1}{left(1+e^{- frac{ x - beta }{alpha}}right)} + Min f]  
Every output pixel is equal to f(x). Where x is the intensity of the homologous input pixel, and alpha and beta are user-provided constants.

li {ImageProcessing/SigmoidImageFilter,Pass image pixels through a sigmoid function}

*/"
%javamethodmodifiers itk::simple::SigmoidImageFilter::execute() "
/**Computes the sigmoid function pixel-wise.

*/"
%javamethodmodifiers itk::simple::Sigmoid "/**
Computes the sigmoid function pixel-wise.

A linear transformation is applied first on the argument of the sigmoid fuction. The resulting total transfrom is given by
 f[ f(x) = (Max-Min) cdot frac{1}{left(1+e^{- frac{ x - beta }{alpha}}right)} + Min f]  
Every output pixel is equal to f(x). Where x is the intensity of the homologous input pixel, and alpha and beta are user-provided constants.

li {ImageProcessing/SigmoidImageFilter,Pass image pixels through a sigmoid function}

*/"
%javamethodmodifiers itk::simple::SigmoidImageFilter::setAlpha "/**
void itk::SigmoidImageFilter::SetAlpha(double alpha)

*/"

%javamethodmodifiers itk::simple::SigmoidImageFilter::setBeta "/**
void itk::SigmoidImageFilter::SetBeta(double beta)

*/"

%javamethodmodifiers itk::simple::SigmoidImageFilter::setOutputMaximum "/**
void itk::SigmoidImageFilter::SetOutputMaximum(OutputPixelType max)

*/"

%javamethodmodifiers itk::simple::SigmoidImageFilter::setOutputMinimum "/**
void itk::SigmoidImageFilter::SetOutputMinimum(OutputPixelType min)

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SignedDanielssonDistanceMapImageFilter.xml
%typemap(javaimports) itk::simple::SignedDanielssonDistanceMapImageFilter "/** 
This class is parametrized over the type of the input image and the type of the output image.
This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.
For purposes of evaluating the signed distance map, the input is assumed to be binary composed of pixels with value 0 and non-zero.
The inside is considered as having negative distances. Outside is treated as having positive distances. To change the convention, use the InsideIsPositive(bool) function.
As a convention, the distance is evaluated from the boundary of the ON pixels.
The filter returns
li A signed distance map with the approximation to the euclidean distance.
li A voronoi partition. (See itkDanielssonDistanceMapImageFilter)
li A vector map containing the component of the vector relating the current pixel with the closest point of the closest object to this pixel. Given that the components of the distance are computed in pixels, the vector is represented by an itk::Offset. That is, physical coordinates are not used. (See itkDanielssonDistanceMapImageFilter)

This filter internally uses the DanielssonDistanceMap filter. This filter is N-dimensional.
see itkDanielssonDistanceMapImageFilter

*/"
%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::SignedDanielssonDistanceMap "/**

This class is parametrized over the type of the input image and the type of the output image.
This filter computes the distance map of the input image as an approximation with pixel accuracy to the Euclidean distance.
For purposes of evaluating the signed distance map, the input is assumed to be binary composed of pixels with value 0 and non-zero.
The inside is considered as having negative distances. Outside is treated as having positive distances. To change the convention, use the InsideIsPositive(bool) function.
As a convention, the distance is evaluated from the boundary of the ON pixels.
The filter returns
li A signed distance map with the approximation to the euclidean distance.
li A voronoi partition. (See itkDanielssonDistanceMapImageFilter)
li A vector map containing the component of the vector relating the current pixel with the closest point of the closest object to this pixel. Given that the components of the distance are computed in pixels, the vector is represented by an itk::Offset. That is, physical coordinates are not used. (See itkDanielssonDistanceMapImageFilter)

This filter internally uses the DanielssonDistanceMap filter. This filter is N-dimensional.
see itkDanielssonDistanceMapImageFilter

*/"
%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::setInsideIsPositive "/**
virtual void itk::SignedDanielssonDistanceMapImageFilter::SetInsideIsPositive(bool _arg)

Set if the inside represents positive values in the signed distance map. By convention ON pixels are treated as inside pixels.
*/"

%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::getInsideIsPositive "/**
virtual const bool& itk::SignedDanielssonDistanceMapImageFilter::GetInsideIsPositive()

Get if the inside represents positive values in the signed distance map. See GetInsideIsPositive()
*/"

%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::setSquaredDistance "/**
virtual void itk::SignedDanielssonDistanceMapImageFilter::SetSquaredDistance(bool _arg)

Set if the distance should be squared.
*/"

%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::getSquaredDistance "/**
virtual const bool& itk::SignedDanielssonDistanceMapImageFilter::GetSquaredDistance()

Get the distance squared.
*/"

%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::setUseImageSpacing "/**
virtual void itk::SignedDanielssonDistanceMapImageFilter::SetUseImageSpacing(bool _arg)

Set if image spacing should be used in computing distances.
*/"

%javamethodmodifiers itk::simple::SignedDanielssonDistanceMapImageFilter::getUseImageSpacing "/**
virtual const bool& itk::SignedDanielssonDistanceMapImageFilter::GetUseImageSpacing()

Get whether spacing is used.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SignedMaurerDistanceMapImageFilter.xml
%typemap(javaimports) itk::simple::SignedMaurerDistanceMapImageFilter "/** This filter calculates the squared Euclidean distance transform of a binary image in linear time for arbitrary dimensions.

par Inputs and Outputs
This is an image-to-image filter. The dimensionality is arbitrary. The only dimensionality constraint is that the input and output images be of the same dimensions and size. To maintain integer arithmetic within the filter, the default output is the signed squared distance. This implies that the input image should be of type unsigned int or int whereas the output image is of type int. Obviously, if the user wishes to utilize the image spacing or to have a filter with the Euclidean distance (as opposed to the squared distance), output image types of float or double should be used.
The inside is considered as having negative distances. Outside is treated as having positive distances. To change the convention, use the InsideIsPositive(bool) function.
par Parameters
Set/GetBackgroundValue specifies the background of the value of the input binary image. Normally this is zero and, as such, zero is the default value. Other than that, the usage is completely analagous to the itkDanielssonDistanceImageFilterClass except is does not return the Voronoi map.
Ref: C. R. Maurer, Jr., R. Qi, and V. Raghavan, A Linear Time Algorithm for Computing Exact Euclidean Distance Transforms of Binary Images in Arbitrary Dimensions, IEEE - Transactions on Pattern Analysis and Machine Intelligence, 25(2): 265-270, 2003.
*/"
%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::execute() "
/**This filter calculates the squared Euclidean distance transform of a binary image in linear time for arbitrary dimensions.

*/"
%javamethodmodifiers itk::simple::SignedMaurerDistanceMap "/**
This filter calculates the squared Euclidean distance transform of a binary image in linear time for arbitrary dimensions.

par Inputs and Outputs
This is an image-to-image filter. The dimensionality is arbitrary. The only dimensionality constraint is that the input and output images be of the same dimensions and size. To maintain integer arithmetic within the filter, the default output is the signed squared distance. This implies that the input image should be of type unsigned int or int whereas the output image is of type int. Obviously, if the user wishes to utilize the image spacing or to have a filter with the Euclidean distance (as opposed to the squared distance), output image types of float or double should be used.
The inside is considered as having negative distances. Outside is treated as having positive distances. To change the convention, use the InsideIsPositive(bool) function.
par Parameters
Set/GetBackgroundValue specifies the background of the value of the input binary image. Normally this is zero and, as such, zero is the default value. Other than that, the usage is completely analagous to the itkDanielssonDistanceImageFilterClass except is does not return the Voronoi map.
Ref: C. R. Maurer, Jr., R. Qi, and V. Raghavan, A Linear Time Algorithm for Computing Exact Euclidean Distance Transforms of Binary Images in Arbitrary Dimensions, IEEE - Transactions on Pattern Analysis and Machine Intelligence, 25(2): 265-270, 2003.
*/"
%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::setInsideIsPositive "/**
virtual void itk::SignedMaurerDistanceMapImageFilter::SetInsideIsPositive(bool _arg)

Set if the inside represents positive values in the signed distance map. By convention ON pixels are treated as inside pixels.
*/"

%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::getInsideIsPositive "/**
virtual const bool& itk::SignedMaurerDistanceMapImageFilter::GetInsideIsPositive()

Get if the inside represents positive values in the signed distance map. See GetInsideIsPositive()
*/"

%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::setSquaredDistance "/**
virtual void itk::SignedMaurerDistanceMapImageFilter::SetSquaredDistance(bool _arg)

Set if the distance should be squared.
*/"

%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::getSquaredDistance "/**
virtual const bool& itk::SignedMaurerDistanceMapImageFilter::GetSquaredDistance()

Get the distance squared.
*/"

%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::setUseImageSpacing "/**
virtual void itk::SignedMaurerDistanceMapImageFilter::SetUseImageSpacing(bool _arg)

Set if image spacing should be used in computing distances.
*/"

%javamethodmodifiers itk::simple::SignedMaurerDistanceMapImageFilter::getUseImageSpacing "/**
virtual const bool& itk::SignedMaurerDistanceMapImageFilter::GetUseImageSpacing()

Get whether spacing is used.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SinImageFilter.xml
%typemap(javaimports) itk::simple::SinImageFilter "/** Computes the vcl_sin(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::SinImageFilter::execute() "
/**Computes the vcl_sin(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Sin "/**
Computes the vcl_sin(x) pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SmoothingRecursiveGaussianImageFilter.xml
%typemap(javaimports) itk::simple::SmoothingRecursiveGaussianImageFilter "/** Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.

This filter is implemented using the recursive gaussian filters. For multi-component images, the filter works on each component independently.
For this filter to be able to run in-place the input and output image types need to be the same and/or the same type as the RealImageType.

li {Smoothing/SmoothingRecursiveGaussianImageFilter,Gaussian smoothing that works with image adaptors}

*/"
%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::execute() "
/**Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.

*/"
%javamethodmodifiers itk::simple::SmoothingRecursiveGaussian "/**
Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.

This filter is implemented using the recursive gaussian filters. For multi-component images, the filter works on each component independently.
For this filter to be able to run in-place the input and output image types need to be the same and/or the same type as the RealImageType.

li {Smoothing/SmoothingRecursiveGaussianImageFilter,Gaussian smoothing that works with image adaptors}

*/"
%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::setSigma "/**
void itk::SmoothingRecursiveGaussianImageFilter::SetSigma(ScalarRealType sigma)

*/"

%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::getSigma "/**
ScalarRealType itk::SmoothingRecursiveGaussianImageFilter::GetSigma() const

*/"

%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::setNormalizeAcrossScale "/**
void itk::SmoothingRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

This method does not effect the output of this filter.
see  RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::SmoothingRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SobelEdgeDetectionImageFilter.xml
%typemap(javaimports) itk::simple::SobelEdgeDetectionImageFilter "/** A 2D or 3D edge detection using the Sobel operator.

This filter uses the Sobel operator to calculate the image gradient and then finds the magnitude of this gradient vector. The Sobel gradient magnitude (square-root sum of squares) is an indication of edge strength.
see  ImageToImageFilter
see  SobelOperator
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

*/"
%javamethodmodifiers itk::simple::SobelEdgeDetectionImageFilter::execute() "
/**A 2D or 3D edge detection using the Sobel operator.

*/"
%javamethodmodifiers itk::simple::SobelEdgeDetection "/**
A 2D or 3D edge detection using the Sobel operator.

This filter uses the Sobel operator to calculate the image gradient and then finds the magnitude of this gradient vector. The Sobel gradient magnitude (square-root sum of squares) is an indication of edge strength.
see  ImageToImageFilter
see  SobelOperator
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SqrtImageFilter.xml
%typemap(javaimports) itk::simple::SqrtImageFilter "/** Computes the vcl_sqrt(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::SqrtImageFilter::execute() "
/**Computes the vcl_sqrt(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Sqrt "/**
Computes the vcl_sqrt(x) pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SquaredDifferenceImageFilter.xml
%typemap(javaimports) itk::simple::SquaredDifferenceImageFilter "/** Implements pixel-wise the computation of squared difference.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the difference of the two pixel values
li compute the square of the difference
li cast the double value resulting from sqr() to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)

li {ImageProcessing/SquaredDifferenceImageFilter,Compute the squared difference of corresponding pixels in two images}

*/"
%javamethodmodifiers itk::simple::SquaredDifferenceImageFilter::execute() "
/**Implements pixel-wise the computation of squared difference.

*/"
%javamethodmodifiers itk::simple::SquaredDifference "/**
Implements pixel-wise the computation of squared difference.

This filter is parametrized over the types of the two input images and the type of the output image.
Numeric conversions (castings) are done by the C++ defaults.
The filter will walk over all the pixels in the two input images, and for each one of them it will do the following:

li cast the input 1 pixel value to double 
li cast the input 2 pixel value to double 
li compute the difference of the two pixel values
li compute the square of the difference
li cast the double value resulting from sqr() to the pixel type of the output image
li store the casted value into the output image.

The filter expect all images to have the same dimension (e.g. all 2D, or all 3D, or all ND)

li {ImageProcessing/SquaredDifferenceImageFilter,Compute the squared difference of corresponding pixels in two images}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SquareImageFilter.xml
%typemap(javaimports) itk::simple::SquareImageFilter "/** Computes the square of the intensity values pixel-wise.

*/"
%javamethodmodifiers itk::simple::SquareImageFilter::execute() "
/**Computes the square of the intensity values pixel-wise.

*/"
%javamethodmodifiers itk::simple::Square "/**
Computes the square of the intensity values pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SubtractConstantFromImageFilter.xml
%typemap(javaimports) itk::simple::SubtractConstantFromImageFilter "/** Subract a constant from all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::SubtractConstantFromImageFilter::execute() "
/**Subract a constant from all input pixels.

*/"
%javamethodmodifiers itk::simple::SubtractConstantFrom "/**
Subract a constant from all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see  UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::SubtractConstantFromImageFilter::setConstant "/**
void itk::SubtractConstantFromImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
*/"

%javamethodmodifiers itk::simple::SubtractConstantFromImageFilter::getConstant "/**
const TConstant& itk::SubtractConstantFromImageFilter::GetConstant() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SubtractImageFilter.xml
%typemap(javaimports) itk::simple::SubtractImageFilter "/** Implements an operator for pixel-wise subtraction of two images.

Output = Input1 - Input2.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/SubtractImageFilter,Subtract two images}

*/"
%javamethodmodifiers itk::simple::SubtractImageFilter::execute() "
/**Implements an operator for pixel-wise subtraction of two images.

*/"
%javamethodmodifiers itk::simple::Subtract "/**
Implements an operator for pixel-wise subtraction of two images.

Output = Input1 - Input2.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/SubtractImageFilter,Subtract two images}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1TanImageFilter.xml
%typemap(javaimports) itk::simple::TanImageFilter "/** Computes the vcl_tan(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::TanImageFilter::execute() "
/**Computes the vcl_tan(x) pixel-wise.

*/"
%javamethodmodifiers itk::simple::Tan "/**
Computes the vcl_tan(x) pixel-wise.

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ThresholdImageFilter.xml
%typemap(javaimports) itk::simple::ThresholdImageFilter "/** Set image values to a user-specified value if they are below, above, or between simple threshold values.

 ThresholdImageFiltersets image values to a user-specified outside value (by default, black) if the image values are below, above, or between simple threshold values.
The pixels must support the operators >= and <=.

li {ImageProcessing/ThresholdImageFilter,Threshold an image}

*/"
%javamethodmodifiers itk::simple::ThresholdImageFilter::execute() "
/**Set image values to a user-specified value if they are below, above, or between simple threshold values.

*/"
%javamethodmodifiers itk::simple::Threshold "/**
Set image values to a user-specified value if they are below, above, or between simple threshold values.

 ThresholdImageFiltersets image values to a user-specified outside value (by default, black) if the image values are below, above, or between simple threshold values.
The pixels must support the operators >= and <=.

li {ImageProcessing/ThresholdImageFilter,Threshold an image}

*/"
%javamethodmodifiers itk::simple::ThresholdImageFilter::setLower "/**
virtual void itk::ThresholdImageFilter::SetLower(PixelType _arg)

Set/Get methods to set the lower threshold
*/"

%javamethodmodifiers itk::simple::ThresholdImageFilter::getLower "/**
virtual PixelType itk::ThresholdImageFilter::GetLower() const

*/"

%javamethodmodifiers itk::simple::ThresholdImageFilter::setUpper "/**
virtual void itk::ThresholdImageFilter::SetUpper(PixelType _arg)

Set/Get methods to set the upper threshold
*/"

%javamethodmodifiers itk::simple::ThresholdImageFilter::getUpper "/**
virtual PixelType itk::ThresholdImageFilter::GetUpper() const

*/"

%javamethodmodifiers itk::simple::ThresholdImageFilter::setOutsideValue "/**
virtual void itk::ThresholdImageFilter::SetOutsideValue(PixelType _arg)

Set the outside pixel value. The default value NumericTraits<PixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::ThresholdImageFilter::getOutsideValue "/**
virtual PixelType itk::ThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1VectorIndexSelectionCastImageFilter.xml
%typemap(javaimports) itk::simple::VectorIndexSelectionCastImageFilter "/** Extracts the selected index of the vector that is the input pixel type.

This filter is templated over the input image type and output image type.
The filter expect the input image pixel type to be a vector and the output image pixel type to be a scalar. The only requirement on the type used for representing the vector is that it must provide an operator[].

li {VectorImages/VectorIndexSelectionCastImageFilter,Extract a component of an itkVectorImage}

*/"
%javamethodmodifiers itk::simple::VectorIndexSelectionCastImageFilter::execute() "
/**Extracts the selected index of the vector that is the input pixel type.

*/"
%javamethodmodifiers itk::simple::VectorIndexSelectionCast "/**
Extracts the selected index of the vector that is the input pixel type.

This filter is templated over the input image type and output image type.
The filter expect the input image pixel type to be a vector and the output image pixel type to be a scalar. The only requirement on the type used for representing the vector is that it must provide an operator[].

li {VectorImages/VectorIndexSelectionCastImageFilter,Extract a component of an itkVectorImage}

*/"
%javamethodmodifiers itk::simple::VectorIndexSelectionCastImageFilter::setIndex "/**
void itk::VectorIndexSelectionCastImageFilter::SetIndex(unsigned int i)

Get/Set methods for the index
*/"

%javamethodmodifiers itk::simple::VectorIndexSelectionCastImageFilter::getIndex "/**
unsigned int itk::VectorIndexSelectionCastImageFilter::GetIndex(void) const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1WhiteTopHatImageFilter.xml
%typemap(javaimports) itk::simple::WhiteTopHatImageFilter "/** White top hat extract local maxima that are larger than the structuring element.

Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::WhiteTopHatImageFilter::execute() "
/**White top hat extract local maxima that are larger than the structuring element.

*/"
%javamethodmodifiers itk::simple::WhiteTopHat "/**
White top hat extract local maxima that are larger than the structuring element.

Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

*/"
%javamethodmodifiers itk::simple::WhiteTopHatImageFilter::setSafeBorder "/**
virtual void itk::WhiteTopHatImageFilter::SetSafeBorder(bool _arg)

A safe border is added to input image to avoid borders effects and remove it once the closing is done
*/"

%javamethodmodifiers itk::simple::WhiteTopHatImageFilter::getSafeBorder "/**
virtual const bool& itk::WhiteTopHatImageFilter::GetSafeBorder()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1WrapPadImageFilter.xml
%typemap(javaimports) itk::simple::WrapPadImageFilter "/** Increase the image size by padding with replicants of the input image value.

 WrapPadImageFilterchanges the image bounds of an image. Added pixels are filled in with a wrapped replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the right boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  MirrorPadImageFilter, ConstantPadImageFilter

*/"
%javamethodmodifiers itk::simple::WrapPadImageFilter::execute() "
/**Increase the image size by padding with replicants of the input image value.

*/"
%javamethodmodifiers itk::simple::WrapPad "/**
Increase the image size by padding with replicants of the input image value.

 WrapPadImageFilterchanges the image bounds of an image. Added pixels are filled in with a wrapped replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the right boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see  MirrorPadImageFilter, ConstantPadImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1XorImageFilter.xml
%typemap(javaimports) itk::simple::XorImageFilter "/** Implements the XOR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical XOR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel ^ input2_pixel )
Where ^ is the boolean XOR operator in C++.

li {ImageProcessing/XorImageFilter,Binary XOR (exclusive OR) two images}

*/"
%javamethodmodifiers itk::simple::XorImageFilter::execute() "
/**Implements the XOR logical operator pixel-wise between two images.

*/"
%javamethodmodifiers itk::simple::Xor "/**
Implements the XOR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical XOR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel ^ input2_pixel )
Where ^ is the boolean XOR operator in C++.

li {ImageProcessing/XorImageFilter,Binary XOR (exclusive OR) two images}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ZeroCrossingBasedEdgeDetectionImageFilter.xml
%typemap(javaimports) itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter "/** 
This filter implements a zero-crossing based edge detecor. The zero-crossing based edge detector looks for pixels in the Laplacian of an image where the value of the Laplacian passes through zero --- points where the Laplacian changes sign. Such points often occur at ``edges'' in images --- i.e. points where the intensity of the image changes rapidly, but they also occur at places that are not as easy to associate with edges. It is best to think of the zero crossing detector as some sort of feature detector rather than as a specific edge detector.
/par Zero crossings always lie on closed contours and so the output from the zero crossing detector is usually a binary image with single pixel thickness lines showing the positions of the zero crossing points.
/par In this implementation, the input image is first smoothed with a Gaussian filter, then the LaplacianImageFilteris applied to smoothed image. Finally the zero-crossing of the Laplacian of the smoothed image is detected. The output is a binary image.
/par Inputs and Outputs The input to the filter should be a scalar, itk::Imageof arbitrary dimension. The output image is a binary, labeled image. See itkZeroCrossingImageFilter for more information on requirements of the data type of the output.
/par To use this filter, first set the parameters (variance and maximum error) needed by the embedded DiscreteGaussianImageFilter, i.e. See DiscreteGaussianImageFilterfor information about these parameters. Optionally, you may also set foreground and background values for the zero-crossing filter. The default label values are Zero for the background and One for the foreground, as defined in NumericTraitsfor the data type of the output image.
see  DiscreteGaussianImageFilter
see  LaplacianImageFilter
see  ZeroCrossingImageFilter

*/"
%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetection "/**

This filter implements a zero-crossing based edge detecor. The zero-crossing based edge detector looks for pixels in the Laplacian of an image where the value of the Laplacian passes through zero --- points where the Laplacian changes sign. Such points often occur at ``edges'' in images --- i.e. points where the intensity of the image changes rapidly, but they also occur at places that are not as easy to associate with edges. It is best to think of the zero crossing detector as some sort of feature detector rather than as a specific edge detector.
/par Zero crossings always lie on closed contours and so the output from the zero crossing detector is usually a binary image with single pixel thickness lines showing the positions of the zero crossing points.
/par In this implementation, the input image is first smoothed with a Gaussian filter, then the LaplacianImageFilteris applied to smoothed image. Finally the zero-crossing of the Laplacian of the smoothed image is detected. The output is a binary image.
/par Inputs and Outputs The input to the filter should be a scalar, itk::Imageof arbitrary dimension. The output image is a binary, labeled image. See itkZeroCrossingImageFilter for more information on requirements of the data type of the output.
/par To use this filter, first set the parameters (variance and maximum error) needed by the embedded DiscreteGaussianImageFilter, i.e. See DiscreteGaussianImageFilterfor information about these parameters. Optionally, you may also set foreground and background values for the zero-crossing filter. The default label values are Zero for the background and One for the foreground, as defined in NumericTraitsfor the data type of the output image.
see  DiscreteGaussianImageFilter
see  LaplacianImageFilter
see  ZeroCrossingImageFilter

*/"
%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::setVariance "/**
void itk::ZeroCrossingBasedEdgeDetectionImageFilter::SetVariance(const typename ArrayType::ValueType v)

Set the variance parameter needed by the embedded gaussian filter
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::getVariance "/**
virtual const ArrayType itk::ZeroCrossingBasedEdgeDetectionImageFilter::GetVariance() const

*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::setForegroundValue "/**
virtual void itk::ZeroCrossingBasedEdgeDetectionImageFilter::SetForegroundValue(OutputImagePixelType _arg)

Get/Set the label values for the ZeroCrossingImageFilter
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::getForegroundValue "/**
virtual OutputImagePixelType itk::ZeroCrossingBasedEdgeDetectionImageFilter::GetForegroundValue() const

Get/Set the label values for the ZeroCrossingImageFilter
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::setBackgroundValue "/**
virtual void itk::ZeroCrossingBasedEdgeDetectionImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Get/Set the label values for the ZeroCrossingImageFilter
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::ZeroCrossingBasedEdgeDetectionImageFilter::GetBackgroundValue() const

Get/Set the label values for the ZeroCrossingImageFilter
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::setMaximumError "/**
void itk::ZeroCrossingBasedEdgeDetectionImageFilter::SetMaximumError(const typename ArrayType::ValueType v)

Set the MaximumError parameter needed by the embedded gaussian filter This value is used to set the desired maximum error of the gaussian approximation. Maximum error is the difference between the area under the discrete Gaussian curve and the area under the continuous Gaussian. Maximum error affects the Gaussian operator size. The value must be between 0.0 and 1.0.
*/"

%javamethodmodifiers itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::getMaximumError "/**
virtual const ArrayType itk::ZeroCrossingBasedEdgeDetectionImageFilter::GetMaximumError() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ZeroCrossingImageFilter.xml
%typemap(javaimports) itk::simple::ZeroCrossingImageFilter "/** 
This filter finds the closest pixel to the zero-crossings (sign changes) in a signed itk::Image. Pixels closest to zero-crossings are labeled with a foreground value. All other pixels are marked with a background value. The algorithm works by detecting differences in sign among neighbors using city-block style connectivity (4-neighbors in 2d, 6-neighbors in 3d, etc.).
par Inputs and Outputs
The input to this filter is an itk::Imageof arbitrary dimension. The algorithm assumes a signed data type (zero-crossings are not defined for unsigned data types), and requires that operator>, operator<, operator==, and operator!= are defined.
par The output of the filter is a binary, labeled image of user-specified type. By default, zero-crossing pixels are labeled with a default ``foreground'' value of itk::NumericTraits<OutputDataType>::One, where OutputDataType is the data type of the output image. All other pixels are labeled with a default ``background'' value of itk::NumericTraits<OutputDataType>::Zero.
par Parameters
There are two parameters for this filter. ForegroundValue is the value that marks zero-crossing pixels. The BackgroundValue is the value given to all other pixels.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

*/"
%javamethodmodifiers itk::simple::ZeroCrossingImageFilter::execute() "
/**
*/"
%javamethodmodifiers itk::simple::ZeroCrossing "/**

This filter finds the closest pixel to the zero-crossings (sign changes) in a signed itk::Image. Pixels closest to zero-crossings are labeled with a foreground value. All other pixels are marked with a background value. The algorithm works by detecting differences in sign among neighbors using city-block style connectivity (4-neighbors in 2d, 6-neighbors in 3d, etc.).
par Inputs and Outputs
The input to this filter is an itk::Imageof arbitrary dimension. The algorithm assumes a signed data type (zero-crossings are not defined for unsigned data types), and requires that operator>, operator<, operator==, and operator!= are defined.
par The output of the filter is a binary, labeled image of user-specified type. By default, zero-crossing pixels are labeled with a default ``foreground'' value of itk::NumericTraits<OutputDataType>::One, where OutputDataType is the data type of the output image. All other pixels are labeled with a default ``background'' value of itk::NumericTraits<OutputDataType>::Zero.
par Parameters
There are two parameters for this filter. ForegroundValue is the value that marks zero-crossing pixels. The BackgroundValue is the value given to all other pixels.
see  Image
see  Neighborhood
see  NeighborhoodOperator
see  NeighborhoodIterator

*/"
%javamethodmodifiers itk::simple::ZeroCrossingImageFilter::setForegroundValue "/**
virtual void itk::ZeroCrossingImageFilter::SetForegroundValue(OutputImagePixelType _arg)

Set/Get the label value for zero-crossing pixels.
*/"

%javamethodmodifiers itk::simple::ZeroCrossingImageFilter::getForegroundValue "/**
virtual OutputImagePixelType itk::ZeroCrossingImageFilter::GetForegroundValue() const

*/"

%javamethodmodifiers itk::simple::ZeroCrossingImageFilter::setBackgroundValue "/**
virtual void itk::ZeroCrossingImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the label value for non-zero-crossing pixels.
*/"

%javamethodmodifiers itk::simple::ZeroCrossingImageFilter::getBackgroundValue "/**
virtual OutputImagePixelType itk::ZeroCrossingImageFilter::GetBackgroundValue() const

*/"

