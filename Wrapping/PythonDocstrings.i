

%feature("docstring") CastImageFilter "

Generates a hash string from an image.



This class utlizes low level buffer pointer access, to work with
itk::Image and itk::VectorImage. It is modeled after the access an
ImageFileWriter provides to an ImageIO.
Todo
complete documentation

Update in-place on to default after fixing bug in InPlaceImageFilter


C++ includes: itkHashImageFilter.h
";


%feature("docstring") ImageFilterExecuteBase "

This class is a abstract base class which provides a protype of the
Execute method with a variable number of image parameters.

C++ includes: sitkImageFilterExecuteBase.h
";


%feature("docstring") MemberFunctionFactoryBase "

A base class for the MemberFunctionFactory.


This class is for specialization needed for different arity for the
templated member function pointer

C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") Tranform "

A simplified wrapper around a variety of ITK transforms.

C++ includes: sitkTransform.h
";


%feature("docstring") itk::Functor::DivFloor "

Cast arguments to double, performs division then takes the floor.

C++ includes: itkDivideFloorFunctor.h
";


%feature("docstring") itk::Functor::DivReal "

Promotes arguments to real type and performs division.

C++ includes: itkDivideRealFunctor.h
";


%feature("docstring") itk::Functor::UnaryMinus "
C++ includes: itkUnaryMinusImageFilter.h
";

%feature("docstring")  itk::Functor::UnaryMinus::UnaryMinus "
";

%feature("docstring")  itk::Functor::UnaryMinus::~UnaryMinus "
";


%feature("docstring") itk::HashImageFilter "
C++ includes: itkHashImageFilter.h
";

%feature("docstring")  itk::HashImageFilter::GetHash "

Get the computed Hash values

";

%feature("docstring")  itk::HashImageFilter::GetHashOutput "
";

%feature("docstring")  itk::HashImageFilter::GetHashOutput "
";

%feature("docstring")  itk::HashImageFilter::itkGetMacro "
";

%feature("docstring")  itk::HashImageFilter::itkNewMacro "

Method for creation through the object factory.

";

%feature("docstring")  itk::HashImageFilter::itkSetMacro "

Set/Get hashing function as enumerated type

";

%feature("docstring")  itk::HashImageFilter::itkTypeMacro "

Runtime information support.

";

%feature("docstring")  itk::HashImageFilter::MakeOutput "
";


%feature("docstring") itk::ImageIOFactoryRegisterManager "
C++ includes: itkImageIOFactoryRegisterManager.h
";

%feature("docstring")  itk::ImageIOFactoryRegisterManager::ImageIOFactoryRegisterManager "
";


%feature("docstring") itk::SliceImageFilter "

Slices an image based on a starting index and a stopping index, and a
step size.


This class is designed to facilitate the implementation of extended
sliced based indexing into images.

The input and output image must be of the same dimension.

The input parameters are a starting and stopping index as well as a
stepping size. The staring index indicates the first pixels to used
and for each dimension the index is incremented by the step until the
index is equal to or \"beyond\" the stopping index. If the step is
negative then the image will be revered in the dimension, and the
stopping index is expected to be less then the starting index. If the
stopping index is already beyond the starting then a image of zero
size will be returned.

The output image's starting index is always zero. The origin is the
physical location of the starting index. The output directions cosine
matrix is that of the input but with sign changes matching that of the
step's sign.


In certain combination such as with start=1, and step>1 while the
physical location of the center of the pixel remains the same, the
extent (edge to edge space) of the pixel will beyond the extent of the
original image.


C++ includes: itkSliceImageFilter.h
";

%feature("docstring")  itk::SliceImageFilter::GenerateInputRequestedRegion "
";

%feature("docstring")  itk::SliceImageFilter::GenerateOutputInformation "

 SliceImageFilter produces an image which is a different resolution and with a
different pixel spacing than its input image.
See:
ProcessObject::GenerateOutputInformaton()


";

%feature("docstring")  itk::SliceImageFilter::itkGetConstReferenceMacro "
";

%feature("docstring")  itk::SliceImageFilter::itkGetConstReferenceMacro "
";

%feature("docstring")  itk::SliceImageFilter::itkGetConstReferenceMacro "
";

%feature("docstring")  itk::SliceImageFilter::itkNewMacro "

Method for creation through the object factory.

";

%feature("docstring")  itk::SliceImageFilter::itkSetMacro "

Set/Get the stride of indexes extracted

An exception will be generated if 0.

";

%feature("docstring")  itk::SliceImageFilter::itkSetMacro "

Set/Get the excluded end of the range

";

%feature("docstring")  itk::SliceImageFilter::itkSetMacro "

Set/Get the first index extracted from the input image

";

%feature("docstring")  itk::SliceImageFilter::itkStaticConstMacro "
";

%feature("docstring")  itk::SliceImageFilter::itkStaticConstMacro "

ImageDimension enumeration.

";

%feature("docstring")  itk::SliceImageFilter::itkTypeMacro "

Run-time type information (and related methods).

";

%feature("docstring")  itk::SliceImageFilter::SetStart "
";

%feature("docstring")  itk::SliceImageFilter::SetStep "
";

%feature("docstring")  itk::SliceImageFilter::SetStop "
";


%feature("docstring") itk::TransformIOFactoryRegisterManager "
C++ includes: itkTransformIOFactoryRegisterManager.h
";

%feature("docstring")  itk::TransformIOFactoryRegisterManager::TransformIOFactoryRegisterManager "
";


%feature("docstring") itk::simple::AbsImageFilter "

Computes the absolute value of each pixel.


vnl_math_abs() is used to perform the computation.Wiki Examples:

All Examples

Compute the absolute value of an image

See:
 itk::simple::Abs for the procedural interface


C++ includes: sitkAbsImageFilter.h
";

%feature("docstring")  itk::simple::AbsImageFilter::AbsImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AbsImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AbsImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AbsImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AbsoluteValueDifferenceImageFilter "

Implements pixel-wise the computation of absolute value difference.


This filter is parametrized over the types of the two input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults. The filter will walk over all the pixels in the
two input images, and for each one of them it will do the following:


Cast the input 1 pixel value to double .

Cast the input 2 pixel value to double .

Compute the difference of the two pixel values.

Compute the absolute value of the difference.

Cast the double value resulting from the absolute value to the pixel
type of the output image.

Store the casted value into the output image. The filter expects all
images to have the same dimension (e.g. all 2D, or all 3D, or all ND).Wiki Examples:


All Examples

Compute the absolute value of the difference of corresponding pixels
in two images

See:
 itk::simple::AbsoluteValueDifference for the procedural interface


C++ includes: sitkAbsoluteValueDifferenceImageFilter.h
";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::AbsoluteValueDifferenceImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::Execute "
";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AbsoluteValueDifferenceImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AcosImageFilter "

Computes the inverse cosine of each pixel.


This filter is templated over the pixel type of the input image and
the pixel type of the output image. The filter walks over all the
pixels in the input image, and for each pixel does do the following:


cast the pixel value to double ,

apply the vcl_acos() function to the double value

cast the double value resulting from vcl_acos() to the pixel type of
the output image

store the casted value into the output image. The filter expects both
images to have the same dimension (e.g. both 2D, or both 3D, or both
ND).

See:
 itk::simple::Acos for the procedural interface


C++ includes: sitkAcosImageFilter.h
";

%feature("docstring")  itk::simple::AcosImageFilter::AcosImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AcosImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AcosImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AcosImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AdaptiveHistogramEqualizationImageFilter "

Power Law Adaptive Histogram Equalization.


Histogram equalization modifies the contrast in an image. The
AdaptiveHistogramEqualizationImageFilteris a superset of many contrast
enhancing filters. By modifying its parameters (alpha, beta, and
window), the AdaptiveHistogramEqualizationImageFiltercan produce an
adaptively equalized histogram or a version of unsharp mask (local
mean subtraction). Instead of applying a strict histogram equalization
in a window about a pixel, this filter prescribes a mapping function
(power law) controlled by the parameters alpha and beta. The parameter
alpha controls how much the filter acts like the classical histogram
equalization method (alpha=0) to how much the filter acts like an
unsharp mask (alpha=1). The parameter beta controls how much the
filter acts like an unsharp mask (beta=0) to much the filter acts like
pass through (beta=1, with alpha=1). The parameter window controls the
size of the region over which local statistics are calculated. By
altering alpha, beta and window, a host of equalization and unsharp
masking filters is available. For detail description, reference \"Adaptive Image Contrast  Enhancement using
Generalizations of Histogram Equalization.\" J.Alex Stark. IEEE
Transactions on ImageProcessing, May 2000.Wiki Examples:

All Examples

Adaptive histogram equalization

See:
 itk::simple::AdaptiveHistogramEqualization for the procedural interface


C++ includes: sitkAdaptiveHistogramEqualizationImageFilter.h
";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::AdaptiveHistogramEqualizationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::GetAlpha "

Set/Get the value of alpha. Alpha=0 produces the adaptive histogram
equalization (provided beta=0). Alpha=1 produces an unsharp mask.
Default is 0.3.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::GetBeta "

Set/Get the value of beta. If beta=1 (and alpha=1), then the output
image matches the input image. As beta approaches 0, the filter
behaves as an unsharp mask. Default is 0.3.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::GetUseLookupTable "

Set/Get whether an optimized lookup table for the intensity mapping
function is used. Default is off.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::SetAlpha "

Set/Get the value of alpha. Alpha=0 produces the adaptive histogram
equalization (provided beta=0). Alpha=1 produces an unsharp mask.
Default is 0.3.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::SetBeta "

Set/Get the value of beta. If beta=1 (and alpha=1), then the output
image matches the input image. As beta approaches 0, the filter
behaves as an unsharp mask. Default is 0.3.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::SetUseLookupTable "

Set/Get whether an optimized lookup table for the intensity mapping
function is used. Default is off.

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::UseLookupTableOff "
";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualizationImageFilter::UseLookupTableOn "

Set the value of UseLookupTable to true or false respectfully.

";


%feature("docstring") itk::simple::AddImageFilter "

Pixel-wise addition of two images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. The pixel type of the input 1 image must have a
valid defintion of the operator+ with a pixel type of the image 2.
This condition is required because internally this filter will perform
the operation pixel_from_image_1+pixel_from_image_2 Additionally the
type resulting from the sum, will be cast to the pixel type of the
output image. The total operation over one pixel will beoutput_pixel=static_cast<OutputPixelType>(input1_pixel+input2_pixel) For example, this filter could be used directly for adding images
whose pixels are vectors of the same dimension, and to store the
resulting vector in an output image of vector pixels. The images to be
added are set using the methods: SetInput1(image1); SetInput2(image2);
Additionally, this filter can be used to add a constant to every pixel
of an image by using SetInput1(image1); SetConstant2(constant);
WARNING:
No numeric overflow checking is performed in this filter.
Wiki Examples: {http://www.itk.org/Wiki/ITK/Examples}
{ImageProcessing/AddImageFilter,Add two images together}
{ImageProcessing/AddConstantToImageFilter,Add a constant to every
pixel in an image}

See:
 itk::simple::Add for the procedural interface


C++ includes: sitkAddImageFilter.h
";

%feature("docstring")  itk::simple::AddImageFilter::AddImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AddImageFilter::Execute "
";

%feature("docstring")  itk::simple::AddImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::AddImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::AddImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AddImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AndImageFilter "

Implements the AND logical operator pixel-wise between two images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. Since the logical AND operation is only defined in
C++ for integer types, the images passed to this filter must comply
with the requirement of using integer pixel type. The total operation
over one pixel will beoutput_pixel=static_cast<OutputPixelType>(input1
_pixel&input2_pixel)Where \"&\" is the boolean AND operator in C++.Wiki Examples:

All Examples

Binary AND two images

See:
 itk::simple::And for the procedural interface


C++ includes: sitkAndImageFilter.h
";

%feature("docstring")  itk::simple::AndImageFilter::AndImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AndImageFilter::Execute "
";

%feature("docstring")  itk::simple::AndImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::AndImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::AndImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AndImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AntiAliasBinaryImageFilter "


See:
 itk::simple::AntiAliasBinary for the procedural interface


C++ includes: sitkAntiAliasBinaryImageFilter.h
";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::AntiAliasBinaryImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::GetMaximumRMSError "
";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::GetRMSChange "

The Root Mean Square of the levelset upon termination.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::SetMaximumRMSError "
";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::AntiAliasBinaryImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ApproximateSignedDistanceMapImageFilter "

Create a map of the approximate signed distance from the boundaries of
a binary image.


The ApproximateSignedDistanceMapImageFiltertakes as input a binary
image and produces a signed distance map. Each pixel value in the
output contains the approximate distance from that pixel to the
nearest \"object\" in the binary image. This filter differs from the
DanielssonDistanceMapImageFilterin that it calculates the distance to
the \"object edge\" for pixels within the object. Negative values in
the output indicate that the pixel at that position is within an
object in the input image. The absolute value of a negative pixel
represents the approximate distance to the nearest object boundary
pixel. WARNING: This filter requires that the output type be floating-
point. Otherwise internal calculations will not be performed to the
appropriate precision, resulting in completely incorrect (read: zero-
valued) output. The distances computed by this filter are Chamfer
distances, which are only an approximation to Euclidian distances, and
are not as exact approximations as those calculated by the DanielssonDistanceMapImageFilter. On the other hand, this filter is faster. This filter requires that
an \"inside value\" and \"outside value\" be set as parameters. The
\"inside value\" is the intensity value of the binary image which
corresponds to objects, and the \"outside value\" is the intensity of
the background. (A typical binary image often repesents objects as
black (0) and background as white (usually 255), or vice-versa.) Note
that this filter is slightly faster if the inside value is less than
the outside value. Otherwise an extra iteration through the image is
required. This filter uses the FastChamferDistanceImageFilterand the
IsoContourDistanceImageFilterinernally to perform the distance
calculations.
See:
 DanielssonDistanceMapImageFilter, SignedDanielssonDistanceMapImageFilter


FastChamferDistanceImageFilter, IsoContourDistanceImageFilter

Zach Pincus
Wiki Examples:

All Examples

Compute a distance map from objects in a binary image

See:
 itk::simple::ApproximateSignedDistanceMap for the procedural interface


C++ includes: sitkApproximateSignedDistanceMapImageFilter.h
";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::ApproximateSignedDistanceMapImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::GetInsideValue "

Set/Get intensity value representing the interior of objects in the
mask.

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::GetOutsideValue "

Set/Get intensity value representing non-objects in the mask.

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::SetInsideValue "

Set/Get intensity value representing the interior of objects in the
mask.

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::SetOutsideValue "

Set/Get intensity value representing non-objects in the mask.

";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMapImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AsinImageFilter "

Computes the sine of each pixel.


This filter is templated over the pixel type of the input image and
the pixel type of the output image. The filter walks over all the
pixels in the input image, and for each pixel does the following:


cast the pixel value to double ,

apply the vcl_asin() function to the double value,

cast the double value resulting from vcl_asin() to the pixel type of
the output image,

store the casted value into the output image. The filter expects both
images to have the same dimension (e.g. both 2D, or both 3D, or both
ND)

See:
 itk::simple::Asin for the procedural interface


C++ includes: sitkAsinImageFilter.h
";

%feature("docstring")  itk::simple::AsinImageFilter::AsinImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AsinImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AsinImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AsinImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::Atan2ImageFilter "

Computes two argument inverse tangent.


The first argument to the atan function is provided by a pixel in the
first input image ( SetInput1()) and the corresponding pixel in the
second input image ( SetInput2()) is used as the second argument. This
class is templated over the types of the two input images and the type
of the output image. Numeric conversions (castings) are done by the
C++ defaults. Both pixel input types are cast to double in order to be
used as parameters of vcl_atan2() . The resulting double value is cast
to the output pixel type.Wiki Examples:

All Examples

Compute the arctangent of each pixel.

See:
 itk::simple::Atan2 for the procedural interface


C++ includes: sitkAtan2ImageFilter.h
";

%feature("docstring")  itk::simple::Atan2ImageFilter::Atan2ImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::Atan2ImageFilter::Execute "
";

%feature("docstring")  itk::simple::Atan2ImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::Atan2ImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::Atan2ImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::Atan2ImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::AtanImageFilter "

Computes the one-argument inverse tangent of each pixel.


This filter is templated over the pixel type of the input image and
the pixel type of the output image. The filter walks over all the
pixels in the input image, and for each pixel does the following:


cast the pixel value to double ,

apply the vcl_atan() function to the double value,

cast the double value resulting from vcl_atan() to the pixel type of
the output image,

store the cast value into the output image.

See:
 itk::simple::Atan for the procedural interface


C++ includes: sitkAtanImageFilter.h
";

%feature("docstring")  itk::simple::AtanImageFilter::AtanImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::AtanImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::AtanImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::AtanImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BilateralImageFilter "

Blurs an image while preserving edges.


This filter uses bilateral filtering to blur an image using both
domain and range \"neighborhoods\". Pixels that are close to a pixel
in the image domain and similar to a pixel in the image range are used
to calculate the filtered value. Two gaussian kernels (one in the
image domain and one in the image range) are used to smooth the image.
The result is an image that is smoothed in homogeneous regions yet has
edges preserved. The result is similar to anisotropic diffusion but
the implementation in non-iterative. Another benefit to bilateral
filtering is that any distance metric can be used for kernel smoothing
the image range. Hence, color images can be smoothed as vector images,
using the CIE distances between intensity values as the similarity
metric (the Gaussian kernel for the image domain is evaluated using
CIE distances). A separate version of this filter will be designed for
color and vector images. Bilateral filtering is capable of reducing
the noise in an image by an order of magnitude while maintaining
edges. The bilateral operator used here was described by Tomasi and
Manduchi (Bilateral Filtering for Gray and ColorImages. IEEE ICCV.
1998.)
See:
GaussianOperator


 RecursiveGaussianImageFilter


 DiscreteGaussianImageFilter


AnisotropicDiffusionImageFilter


 Image


Neighborhood


NeighborhoodOperator TodoSupport color images Support vector images
Wiki Examples:

All Examples

Bilateral filter an image

See:
 itk::simple::Bilateral for the procedural interface


C++ includes: sitkBilateralImageFilter.h
";

%feature("docstring")  itk::simple::BilateralImageFilter::BilateralImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BilateralImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BilateralImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BilateralImageFilter::GetDomainSigma "

Standard get/set macros for filter parameters. DomainSigma is
specified in the same units as the Imagespacing. RangeSigma is
specified in the units of intensity.

";

%feature("docstring")  itk::simple::BilateralImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BilateralImageFilter::GetNumberOfRangeGaussianSamples "

Set/Get the number of samples in the approximation to the Gaussian
used for the range smoothing. Samples are only generated in the range
of [0, 4*m_RangeSigma]. Default is 100.

";

%feature("docstring")  itk::simple::BilateralImageFilter::GetRangeSigma "

Standard get/set macros for filter parameters. DomainSigma is
specified in the same units as the Imagespacing. RangeSigma is
specified in the units of intensity.

";

%feature("docstring")  itk::simple::BilateralImageFilter::SetDomainSigma "

Convenience get/set methods for setting all domain parameters to the
same values.

";

%feature("docstring")  itk::simple::BilateralImageFilter::SetNumberOfRangeGaussianSamples "

Set/Get the number of samples in the approximation to the Gaussian
used for the range smoothing. Samples are only generated in the range
of [0, 4*m_RangeSigma]. Default is 100.

";

%feature("docstring")  itk::simple::BilateralImageFilter::SetRangeSigma "

Standard get/set macros for filter parameters. DomainSigma is
specified in the same units as the Imagespacing. RangeSigma is
specified in the units of intensity.

";

%feature("docstring")  itk::simple::BilateralImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryClosingByReconstructionImageFilter "

binary closing by reconstruction of an image.


This filter removes small (i.e., smaller than the structuring element)
holes in the image. It is defined as: Closing(f) =
ReconstructionByErosion(Dilation(f)). The structuring element is
assumed to be composed of binary values (zero or one). Only elements
of the structuring element having values > 0 are candidates for
affecting the center pixel.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

 itk::simple::BinaryClosingByReconstruction for the procedural interface


C++ includes: sitkBinaryClosingByReconstructionImageFilter.h
";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::BinaryClosingByReconstructionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::SetForegroundValue "

Set the value in the image to consider as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryClosingByReconstructionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryContourImageFilter "

Labels the pixels on the border of the objects in a binary image.


BinaryContourImageFiltertakes a binary image as input, where the
pixels in the objects are the pixels with a value equal to
ForegroundValue. Only the pixels on the contours of the objects are
kept. The pixels not on the border are changed to BackgroundValue. The
connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.http://hdl.handle.net/1926/1352
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
Wiki Examples:

All Examples

Extract the boundaries of connected regions in a binary image

Extract the inner and outer boundaries of blobs in a binary image

See:
 itk::simple::BinaryContour for the procedural interface


C++ includes: sitkBinaryContourImageFilter.h
";

%feature("docstring")  itk::simple::BinaryContourImageFilter::BinaryContourImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryContourImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::GetBackgroundValue "

Set/Get the background value used to mark the pixels not on the border
of the objects.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::GetForegroundValue "

Set/Get the foreground value used to identify the objects in the input
and output images.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::SetBackgroundValue "

Set/Get the background value used to mark the pixels not on the border
of the objects.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::SetForegroundValue "

Set/Get the foreground value used to identify the objects in the input
and output images.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryContourImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryDilateImageFilter "

Fast binary dilation.


BinaryDilateImageFilteris a binary dilation morphologic operation.
This implementation is based on the papers: L.Vincent \"Morphological
transformations of binary images with  arbitrary structuring
elements\", and N.Nikopoulos et al. \"An efficient algorithm for 3d
binary morphological transformations with 3d structuring elements for
arbitrary size and shape\". IEEE Transactions on ImageProcessing. Vol.
9. No. 3. 2000. pp. 283-286. Gray scale images can be processed as
binary images by selecting a \"DilateValue\". Pixel values matching
the dilate value are considered the \"foreground\" and all other
pixels are \"background\". This is useful in processing segmented
images where all pixels in segment #1 have value 1 and pixels in
segment #2 have value 2, etc. A particular \"segment number\" can be
processed. DilateValue defaults to the maximum possible value of the
PixelType. The structuring element is assumed to be composed of binary
values (zero or one). Only elements of the structuring element having
values > 0 are candidates for affecting the center pixel. A reasonable
choice of structuring element is itk::BinaryBallStructuringElement.
See:
ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
Wiki Examples:

All Examples

Dilate a binary image

See:
 itk::simple::BinaryDilate for the procedural interface


C++ includes: sitkBinaryDilateImageFilter.h
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::BinaryDilateImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::BoundaryToForegroundOff "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::BoundaryToForegroundOn "

Set the value of BoundaryToForeground to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetBackgroundValue "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetBoundaryToForeground "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetForegroundValue "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetBackgroundValue "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetBoundaryToForeground "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetForegroundValue "
";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryDilateImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryErodeImageFilter "

Fast binary erosion.


BinaryErodeImageFilteris a binary erosion morphologic operation. This
implementation is based on the papers: L.Vincent \"Morphological
transformations of binary images with  arbitrary structuring
elements\", and N.Nikopoulos et al. \"An efficient algorithm for 3d
binary morphological transformations with 3d structuring elements for
arbitrary size and shape\". IEEE Transactions on ImageProcessing. Vol.
9. No. 3. 2000. pp. 283-286. Gray scale images can be processed as
binary images by selecting a \"ErodeValue\". Pixel values matching the
erode value are considered the \"foreground\" and all other pixels are
\"background\". This is useful in processing segmented images where
all pixels in segment #1 have value 1 and pixels in segment #2 have
value 2, etc. A particular \"segment number\" can be processed.
ErodeValue defaults to the maximum possible value of the PixelType.
The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values
(zero or one). Only elements of the structuring element having values
> 0 are candidates for affecting the center pixel. A reasonable choice
of structuring element is itk::BinaryBallStructuringElement.
See:
ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
Wiki Examples:

All Examples

Erode a binary image

See:
 itk::simple::BinaryErode for the procedural interface


C++ includes: sitkBinaryErodeImageFilter.h
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::BinaryErodeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::BoundaryToForegroundOff "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::BoundaryToForegroundOn "

Set the value of BoundaryToForeground to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetBackgroundValue "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetBoundaryToForeground "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetForegroundValue "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetBackgroundValue "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetBoundaryToForeground "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetForegroundValue "
";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryErodeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryFillholeImageFilter "

Remove holes not connected to the boundary of the image.


BinaryFillholeImageFilterfills holes in a binary image. Geodesic
morphology and the Fillhole algorithm is described in Chapter 6 of
Pierre Soille's book \"Morphological Image Analysis:  Principles and
Applications\", Second Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 GrayscaleFillholeImageFilter

 itk::simple::BinaryFillhole for the procedural interface


C++ includes: sitkBinaryFillholeImageFilter.h
";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::BinaryFillholeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::SetForegroundValue "

End concept checking Set the value in the image to consider as
\"foreground\". Defaults to maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryFillholeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryGrindPeakImageFilter "

Remove the objects not connected to the boundary of the image.


BinaryGrindPeakImageFilterginds peaks in a grayscale image. Geodesic
morphology and the grind peak algorithm is described in Chapter 6 of
Pierre Soille's book \"Morphological Image Analysis:  Principles and
Applications\", Second Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 GrayscaleGrindPeakImageFilter

 itk::simple::BinaryGrindPeak for the procedural interface


C++ includes: sitkBinaryGrindPeakImageFilter.h
";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::BinaryGrindPeakImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::GetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::SetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::SetForegroundValue "

End concept checking Set the value in the image to consider as
\"foreground\". Defaults to maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryGrindPeakImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryMagnitudeImageFilter "

Computes the square root of the sum of squares of corresponding input
pixels.


This filter is templated over the types of the two input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults. The filter walks over all of the pixels in the
two input images, and for each pixel does the following:


cast the input 1 pixel value to double

cast the input 2 pixel value to double

compute the sum of squares of the two pixel values

compute the square root of the sum

cast the double value resulting from vcl_sqrt() to the pixel type of
the output image

store the cast value into the output image. The filter expects all
images to have the same dimension (e.g. all 2D, or all 3D, or all ND)

See:
 itk::simple::BinaryMagnitude for the procedural interface


C++ includes: sitkBinaryMagnitudeImageFilter.h
";

%feature("docstring")  itk::simple::BinaryMagnitudeImageFilter::BinaryMagnitudeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryMagnitudeImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::BinaryMagnitudeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryMagnitudeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryMedianImageFilter "

Applies a version of the median filter optimized for binary images.


This filter was contributed by Bjorn Hanch Sollie after identifying
that the generic Median filter performed unnecessary operations when
the input image is binary. This filter computes an image where a given
pixel is the median value of the pixels in a neighborhood about the
corresponding input pixel. For the case of binary images the median
can be obtained by simply counting the neighbors that are foreground.
A median filter is one of the family of nonlinear filters. It is used
to smooth an image without being biased by outliers or shot noise.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::BinaryMedian for the procedural interface


C++ includes: sitkBinaryMedianImageFilter.h
";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::BinaryMedianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::GetBackgroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::GetForegroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::GetRadius "

Get the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::SetBackgroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::SetForegroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::SetRadius "

Set the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::BinaryMedianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryMinMaxCurvatureFlowImageFilter "

Denoise a binary image using min/max curvature flow.


BinaryMinMaxCurvatureFlowImageFilterimplements a curvature driven
image denosing algorithm. This filter assumes that the image is
essentially binary: consisting of two classes. Iso-brightness contours
in the input image are viewed as a level set. The level set is then
evolved using a curvature-based speed function: \\\\[ I_t = F_{\\\\mbox{minmax}} |\\\\nabla I| \\\\] where $ F_{\\\\mbox{minmax}} = \\\\min(\\\\kappa,0) $ if $ \\\\mbox{Avg}_{\\\\mbox{stencil}}(x) $ is less than or equal to $ T_{thresold} $ and $ \\\\max(\\\\kappa,0) $ , otherwise. $ \\\\kappa $ is the mean curvature of the iso-brightness contour at point $ x $ . In min/max curvature flow, movement is turned on or off depending
on the scale of the noise one wants to remove. Switching depends on
the average image value of a region of radius $ R $ around each point. The choice of $ R $ , the stencil radius, governs the scale of the noise to be removed.
The threshold value $ T_{threshold} $ is a user specified value which discriminates between the two pixel
classes. This filter make use of the multi-threaded finite difference
solver hierarchy. Updates are computed using a
BinaryMinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary
condition is used when computing derivatives near the data boundary.
WARNING:
This filter assumes that the input and output types have the same
dimensions. This filter also requires that the output image pixels are
of a real type. This filter works for any dimensional images.
Reference: \"Level Set Methods and Fast Marching Methods\", J.A.
Sethian, Cambridge Press, Chapter 16, Second edition, 1999.

See:
BinaryMinMaxCurvatureFlowFunction


 CurvatureFlowImageFilter


 MinMaxCurvatureFlowImageFilter

 itk::simple::BinaryMinMaxCurvatureFlow for the procedural interface


C++ includes: sitkBinaryMinMaxCurvatureFlowImageFilter.h
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::BinaryMinMaxCurvatureFlowImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::GetStencilRadius "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::GetThreshold "

Set/Get the threshold value.

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::GetTimeStep "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::SetStencilRadius "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::SetThreshold "

Set/Get the threshold value.

";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::SetTimeStep "
";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlowImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryMorphologicalClosingImageFilter "

binary morphological closing of an image.


This filter removes small (i.e., smaller than the structuring element)
holes and tube like structures in the interior or at the boundaries of
the image. The morphological closing of an image \"f\" is defined as:
Closing(f) = Erosion(Dilation(f)). The structuring element is assumed
to be composed of binary values (zero or one). Only elements of the
structuring element having values > 0 are candidates for affecting the
center pixel. This code was contributed in the Insight Journal paper:
\"Binary morphological closing and opening image filters\" by Lehmann
G.http://hdl.handle.net/1926/141http://www.insight-
journal.org/browse/publication/58
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

 itk::simple::BinaryMorphologicalClosing for the procedural interface


C++ includes: sitkBinaryMorphologicalClosingImageFilter.h
";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::BinaryMorphologicalClosingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::GetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SafeBorderOff "
";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SafeBorderOn "

Set the value of SafeBorder to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SetForegroundValue "

Set the value in the image to consider as \"foreground\". Defaults to
maximum value of InputPixelType.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::SetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter "

binary morphological opening of an image.


This filter removes small (i.e., smaller than the structuring element)
structures in the interior or at the boundaries of the image. The
morphological opening of an image \"f\" is defined as: Opening(f) =
Dilatation(Erosion(f)). The structuring element is assumed to be
composed of binary values (zero or one). Only elements of the
structuring element having values > 0 are candidates for affecting the
center pixel. This code was contributed in the Insight Journal paper:
\"Binary morphological closing and opening image filters\" by Lehmann
G.http://hdl.handle.net/1926/141http://www.insight-
journal.org/browse/publication/58
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

 itk::simple::BinaryMorphologicalOpening for the procedural interface


C++ includes: sitkBinaryMorphologicalOpeningImageFilter.h
";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::BinaryMorphologicalOpeningImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::GetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::SetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::SetForegroundValue "

Set the value in the image to consider as \"foreground\". Defaults to
maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpeningImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryNotImageFilter "

Implements the BinaryNot logical operator pixel-wise between two
images.


This class is parametrized over the types of the two input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults. The total operation over one pixel will be
output_pixel = static_cast<PixelType>( input1_pixel != input2_pixel )
Where \"!=\" is the equality operator in C++.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176
Wiki Examples:

All Examples

Invert an image using the Binary Not operation

See:
 itk::simple::BinaryNot for the procedural interface


C++ includes: sitkBinaryNotImageFilter.h
";

%feature("docstring")  itk::simple::BinaryNotImageFilter::BinaryNotImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::GetBackgroundValue "

Get the value used as \"background\". Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::GetForegroundValue "

Set/Get the value in the image considered as \"foreground\". Defaults
to maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::SetBackgroundValue "

Set the value used as \"background\". Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::SetForegroundValue "

Set/Get the value in the image considered as \"foreground\". Defaults
to maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryNotImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryOpeningByReconstructionImageFilter "

binary morphological closing of an image.


This filter removes small (i.e., smaller than the structuring element)
objects in the image. It is defined as: Opening(f) =
ReconstructionByDilatation(Erosion(f)). The structuring element is
assumed to be composed of binary values (zero or one). Only elements
of the structuring element having values > 0 are candidates for
affecting the center pixel.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

 itk::simple::BinaryOpeningByReconstruction for the procedural interface


C++ includes: sitkBinaryOpeningByReconstructionImageFilter.h
";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::BinaryOpeningByReconstructionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetBackgroundValue "

Set the value in eroded part of the image. Defaults to zero.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetForegroundValue "

Set the value in the image to consider as \"foreground\". Defaults to
maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstructionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryProjectionImageFilter "

Binary projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
the original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MeanProjectionImageFilter


 MeanProjectionImageFilter


 MaximumProjectionImageFilter


 MinimumProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter

 itk::simple::BinaryProjection for the procedural interface


C++ includes: sitkBinaryProjectionImageFilter.h
";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::BinaryProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::GetBackgroundValue "

Get the value used as \"background\". Any pixel value which is not
DilateValue is considered background. BackgroundValue is used for
defining boundary conditions. Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::GetForegroundValue "

Get the value in the image considered as \"foreground\". Defaults to
maximum value of PixelType.

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::SetBackgroundValue "

Set the value used as \"background\". Any pixel value which is not
DilateValue is considered background. BackgroundValue is used for
defining boundary conditions. Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::SetForegroundValue "

Set the value in the image to consider as \"foreground\". Defaults to
maximum value of PixelType. Subclasses may alias this to DilateValue
or ErodeValue.

";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::BinaryProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryReconstructionByDilationImageFilter "

binary reconstruction by dilation of an image


Reconstruction by dilation operates on a \"marker\" image and a
\"mask\" image, and is defined as the dilation of the marker image
with respect to the mask image iterated until stability. Geodesic
morphology is described in Chapter 6.2 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
MorphologyImageFilter, ReconstructionByDilationImageFilter, BinaryReconstructionByErosionImageFilter

 itk::simple::BinaryReconstructionByDilation for the procedural interface


C++ includes: sitkBinaryReconstructionByDilationImageFilter.h
";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::BinaryReconstructionByDilationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::GetBackgroundValue "

End concept checking Set/Get the value used as \"background\" in the
output image. Defaults to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::GetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::SetBackgroundValue "

End concept checking Set/Get the value used as \"background\" in the
output image. Defaults to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::SetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryReconstructionByDilationImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryReconstructionByErosionImageFilter "

binary reconstruction by erosion of an image


Reconstruction by erosion operates on a \"marker\" image and a
\"mask\" image, and is defined as the erosion of the marker image with
respect to the mask image iterated until stability. Geodesic
morphology is described in Chapter 6.2 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
MorphologyImageFilter, ReconstructionByErosionImageFilter, BinaryReconstructionByDilationImageFilter

 itk::simple::BinaryReconstructionByErosion for the procedural interface


C++ includes: sitkBinaryReconstructionByErosionImageFilter.h
";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::BinaryReconstructionByErosionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::GetBackgroundValue "

End concept checking Set/Get the value used as \"background\" in the
output image. Defaults to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::GetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::SetBackgroundValue "

End concept checking Set/Get the value used as \"background\" in the
output image. Defaults to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::SetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::BinaryReconstructionByErosionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryThinningImageFilter "

This filter computes one-pixel-wide edges of the input image.


This class is parametrized over the type of the input image and the
type of the output image. The input is assumed to be a binary image.
If the foreground pixels of the input image do not have a value of 1,
they are rescaled to 1 internally to simplify the computation. The
filter will produce a skeleton of the object. The output background
values are 0, and the foreground values are 1. This filter is a
sequential thinning algorithm and known to be computational time
dependable on the image size. The algorithm corresponds with the 2D
implementation described in: Rafael C. Gonzales and Richard E. Woods.
Digital ImageProcessing. Addison Wesley, 491-494, (1993). To do: Make
this filter ND.
See:
MorphologyImageFilter
Wiki Examples:

All Examples

Skeletonize/thin an image

See:
 itk::simple::BinaryThinning for the procedural interface


C++ includes: sitkBinaryThinningImageFilter.h
";

%feature("docstring")  itk::simple::BinaryThinningImageFilter::BinaryThinningImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryThinningImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryThinningImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryThinningImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryThresholdImageFilter "

Binarize an input image by thresholding.


This filter produces an output image whose pixels are either one of
two values ( OutsideValue or InsideValue ), depending on whether the
corresponding input image pixels lie between the two thresholds (
LowerThreshold and UpperThreshold ). Values equal to either threshold
is considered to be between the thresholds. More precisely \\\\[ Output(x_i) = \\\\begin{cases} InsideValue & \\\\text{if
\\\\f$LowerThreshold \\\\leq x_i \\\\leq UpperThreshold\\\\f$}
\\\\\\\\ OutsideValue & \\\\text{otherwise} \\\\end{cases} \\\\] This filter is templated over the input image type and the output
image type. The filter expect both images to have the same number of
dimensions. The default values for LowerThreshold and UpperThreshold
are: LowerThreshold = NumericTraits<TInput>::NonpositiveMin();
UpperThreshold = NumericTraits<TInput>::max(); Therefore, generally
only one of these needs to be set, depending on whether the user wants
to threshold above or below the desired threshold.Wiki Examples:

All Examples

Threshold an image

See:
 itk::simple::BinaryThreshold for the procedural interface


C++ includes: sitkBinaryThresholdImageFilter.h
";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::BinaryThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::GetLowerThreshold "
";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::GetUpperThreshold "

Get the threshold values.

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value. The default value
NumericTraits<OutputPixelType>::max().

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::SetLowerThreshold "
";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::SetUpperThreshold "

Set the thresholds. The default lower threshold is
NumericTraits<InputPixelType>::NonpositiveMin(). The default upper
threshold is NumericTraits<InputPixelType>::max. An execption is
thrown if the lower threshold is greater than the upper threshold.

";

%feature("docstring")  itk::simple::BinaryThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinaryThresholdProjectionImageFilter "

BinaryThreshold projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
the original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MeanProjectionImageFilter


 MeanProjectionImageFilter


 MaximumProjectionImageFilter


 MinimumProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter

 itk::simple::BinaryThresholdProjection for the procedural interface


C++ includes: sitkBinaryThresholdProjectionImageFilter.h
";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::BinaryThresholdProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::GetBackgroundValue "

Set/Get the output value used as \"background\". Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::GetForegroundValue "

Set/Get the output value used as \"foreground\". Defaults to maximum
value of PixelType.

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::GetThresholdValue "

Set/Get the input value consider as \"threshold\". Defaults to
NumericTraits<InputPixelType>::max().

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::SetBackgroundValue "

Set/Get the output value used as \"background\". Defaults to
NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::SetForegroundValue "

Set/Get the output value used as \"foreground\". Defaults to maximum
value of PixelType.

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::SetThresholdValue "

Set/Get the input value consider as \"threshold\". Defaults to
NumericTraits<InputPixelType>::max().

";

%feature("docstring")  itk::simple::BinaryThresholdProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BinomialBlurImageFilter "

Performs a separable blur on each dimension of an image.


The binomial blur consists of a nearest neighbor average along each
image dimension. The net result after n-iterations approaches
convultion with a gaussian.Wiki Examples:

All Examples

Blur an image

See:
 itk::simple::BinomialBlur for the procedural interface


C++ includes: sitkBinomialBlurImageFilter.h
";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::BinomialBlurImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::GetRepetitions "

Get and set the number of times to repeat the filter.

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::SetRepetitions "

Get and set the number of times to repeat the filter.

";

%feature("docstring")  itk::simple::BinomialBlurImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BlackTopHatImageFilter "

Black top hat extract local minima that are smaller than the
structuring element.


Black top hat extract local minima that are smaller than the
structuring element. It subtract the background in the input image.
The output of the filter transforms the black peaks in white peaks.
Top-hats are described in Chapter 4.5 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 itk::simple::BlackTopHat for the procedural interface


C++ includes: sitkBlackTopHatImageFilter.h
";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::BlackTopHatImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::GetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SafeBorderOff "
";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SafeBorderOn "

Set the value of SafeBorder to true or false respectfully.

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::SetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::BlackTopHatImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BoundedReciprocalImageFilter "

Computes 1/(1+x) for each pixel in the image.


The filter expect both the input and output images to have the same
number of dimensions, and both of a scalar image type.


See:
 itk::simple::BoundedReciprocal for the procedural interface


C++ includes: sitkBoundedReciprocalImageFilter.h
";

%feature("docstring")  itk::simple::BoundedReciprocalImageFilter::BoundedReciprocalImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BoundedReciprocalImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BoundedReciprocalImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BoundedReciprocalImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BoxMeanImageFilter "

Implements a fast rectangular mean filter using the accumulator
approach.


This code was contributed in the Insight Journal paper: \"Efficient
implementation of kernel filtering\" by Beare R., Lehmann
Ghttp://hdl.handle.net/1926/555http://www.insight-
journal.org/browse/publication/160
Richard Beare

See:
 itk::simple::BoxMean for the procedural interface


C++ includes: sitkBoxMeanImageFilter.h
";

%feature("docstring")  itk::simple::BoxMeanImageFilter::BoxMeanImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BoxMeanImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BoxMeanImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BoxMeanImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BoxMeanImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::BoxMeanImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::BoxMeanImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::BoxMeanImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::BoxSigmaImageFilter "

Implements a fast rectangular sigma filter using the accumulator
approach.


This code was contributed in the Insight Journal paper: \"Efficient
implementation of kernel filtering\" by Beare R., Lehmann
Ghttp://hdl.handle.net/1926/555http://www.insight-
journal.org/browse/publication/160
Gaetan Lehmann

See:
 itk::simple::BoxSigma for the procedural interface


C++ includes: sitkBoxSigmaImageFilter.h
";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::BoxSigmaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::BoxSigmaImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CannyEdgeDetectionImageFilter "

This filter is an implementation of a Canny edge detector for scalar-
valued images. Based on John Canny's paper \"A Computational Approach
to Edge Detection\"(IEEE Transactions on Pattern Analysis and Machine
Intelligence, Vol. PAMI-8, No.6, November 1986), there are four major
steps used in the edge-detection scheme: (1) Smooth the input image
with Gaussian filter. (2) Calculate the second directional derivatives
of the smoothed image. (3) Non-Maximum Suppression: the zero-crossings
of 2nd derivative are found, and the sign of third derivative is used
to find the correct extrema. (4) The hysteresis thresholding is
applied to the gradient magnitude (multiplied with zero-crossings) of
the smoothed image to find and link edges.


Inputs and Outputs
The input to this filter should be a scalar, real-valued Itk image of
arbitrary dimension. The output should also be a scalar, real-value
Itk image of the same dimensionality.
Parameters
There are four parameters for this filter that control the sub-filters
used by the algorithm.
Variance and Maximum error are used in the Gaussian smoothing of the
input image. See itkDiscreteGaussianImageFilter for information on
these parameters.
Threshold is the lowest allowed value in the output image. Its data
type is the same as the data type of the output image. Any values
below the Threshold level will be replaced with the OutsideValue
parameter value, whose default is zero.
TodoEdge-linking will be added when an itk connected component labeling algorithm is available.

See:
 DiscreteGaussianImageFilter


 ZeroCrossingImageFilter


 ThresholdImageFilter

 itk::simple::CannyEdgeDetection for the procedural interface


C++ includes: sitkCannyEdgeDetectionImageFilter.h
";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::CannyEdgeDetectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::GetLowerThreshold "
";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::GetMaximumError "

Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::GetUpperThreshold "
";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::GetVariance "

Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::SetLowerThreshold "
";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::SetMaximumError "

Set/Get the MaximumError parameter used by the Gaussian smoothing
filter in this algorithm.

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::SetUpperThreshold "

TODO: Document in the ITKv4 migration guide that the SetThreshold
member function was removed from the CannyEdgeDetectionImageFilter, and that both UpperThreshold and LowerThreshold need to be set. To
get the same results as with the SetThreshold method change
\"myfilter->SetThrehsold\" to \"myfilter->SetUpperThreshold\", and add
\"myfilter->SetLowerThreshold(GetUpperThreshold()/2.0)\"* Set the
Threshold value for detected edges.

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::SetVariance "

Set/Get the Variance parameter used by the Gaussian smoothing filter
in this algorithm.

";

%feature("docstring")  itk::simple::CannyEdgeDetectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CastImageFilter "

A hybrid cast image filter to convert images to other types of images.


Several different ITK classes are implemented under the hood, to
convert between different image types.


See:
 itk::simple::Cast for the procedural interface


C++ includes: sitkCastImageFilter.h
";

%feature("docstring")  itk::simple::CastImageFilter::CastImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CastImageFilter::Execute "
";

%feature("docstring")  itk::simple::CastImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CastImageFilter::GetOutputPixelType "
";

%feature("docstring")  itk::simple::CastImageFilter::SetOutputPixelType "
";

%feature("docstring")  itk::simple::CastImageFilter::SetOutputPixelType "

Set/Get the output pixel type

";

%feature("docstring")  itk::simple::CastImageFilter::ToString "
";


%feature("docstring") itk::simple::ChangeLabelImageFilter "

Change Sets of Labels.


This filter produces an output image whose pixels are either copied
from the input if they are not being changed or are rewritten based on
the change parameters This filter is templated over the input image
type and the output image type. The filter expect both images to have
the same number of dimensions.
Tim Kelliher. GE Research, Niskayuna, NY.

This work was supported by a grant from DARPA, executed by the U.S.
Army Medical Research and Materiel Command/TATRC Assistance Agreement,
Contract::W81XWH-05-2-0059.

See:
 itk::simple::ChangeLabel for the procedural interface


C++ includes: sitkChangeLabelImageFilter.h
";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::ChangeLabelImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::GetChangeMap "
";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::SetChangeMap "

Set the entire change map.

";

%feature("docstring")  itk::simple::ChangeLabelImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CheckerBoardImageFilter "

Combines two images in a checkerboard pattern.


CheckerBoardImageFiltertakes two input images that must have the same
dimension, size, origin and spacing and produces an output image of
the same size by combinining the pixels from the two input images in a
checkerboard pattern. This filter is commonly used for visually
comparing two images, in particular for evaluating the results of an
image registration process. This filter is implemented as a
multithreaded filter. It provides a ThreadedGenerateData()method for
its implementation.Wiki Examples:

All Examples

Combine two images by alternating blocks of a checkerboard pattern

See:
 itk::simple::CheckerBoard for the procedural interface


C++ includes: sitkCheckerBoardImageFilter.h
";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::CheckerBoardImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::GetCheckerPattern "

Set array with number of checks to make per image dimension.

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::SetCheckerPattern "

Set array with number of checks to make per image dimension.

";

%feature("docstring")  itk::simple::CheckerBoardImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ClosingByReconstructionImageFilter "

Closing by reconstruction of an image.


This filter is similar to the morphological closing, but contrary to
the mophological closing, the closing by reconstruction preserves the
shape of the components. The closing by reconstruction of an image
\"f\" is defined as: ClosingByReconstruction(f) =
ErosionByReconstruction(f, Dilation(f)). Closing by reconstruction not
only preserves structures preserved by the dilation, but also levels
raises the contrast of the darkest regions. If PreserveIntensities is
on, a subsequent reconstruction by dilation using a marker image that
is the original image for all unaffected pixels. Closing by
reconstruction is described in Chapter 6.3.9 of Pierre Soille's book
\"Morphological Image Analysis: Principles and  Applications\", Second
Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 GrayscaleMorphologicalClosingImageFilter

 itk::simple::ClosingByReconstruction for the procedural interface


C++ includes: sitkClosingByReconstructionImageFilter.h
";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::ClosingByReconstructionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::GetPreserveIntensities "

Set/Get whether the original intensities of the image retained for
those pixels unaffected by the opening by reconstrcution. If Off, the
output pixel contrast will be reduced.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::PreserveIntensitiesOff "
";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::PreserveIntensitiesOn "

Set the value of PreserveIntensities to true or false respectfully.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::SetPreserveIntensities "

Set/Get whether the original intensities of the image retained for
those pixels unaffected by the opening by reconstrcution. If Off, the
output pixel contrast will be reduced.

";

%feature("docstring")  itk::simple::ClosingByReconstructionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ComplexToImaginaryImageFilter "

Computes pixel-wise the imaginary part of a complex image.



See:
 itk::simple::ComplexToImaginary for the procedural interface


C++ includes: sitkComplexToImaginaryImageFilter.h
";

%feature("docstring")  itk::simple::ComplexToImaginaryImageFilter::ComplexToImaginaryImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ComplexToImaginaryImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ComplexToImaginaryImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ComplexToImaginaryImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ComplexToModulusImageFilter "

Computes pixel-wise the Modulus of a complex image.



See:
 itk::simple::ComplexToModulus for the procedural interface


C++ includes: sitkComplexToModulusImageFilter.h
";

%feature("docstring")  itk::simple::ComplexToModulusImageFilter::ComplexToModulusImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ComplexToModulusImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ComplexToModulusImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ComplexToModulusImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ComplexToPhaseImageFilter "

Computes pixel-wise the modulus of a complex image.



See:
 itk::simple::ComplexToPhase for the procedural interface


C++ includes: sitkComplexToPhaseImageFilter.h
";

%feature("docstring")  itk::simple::ComplexToPhaseImageFilter::ComplexToPhaseImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ComplexToPhaseImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ComplexToPhaseImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ComplexToPhaseImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ComplexToRealImageFilter "

Computes pixel-wise the real(x) part of a complex image.



See:
 itk::simple::ComplexToReal for the procedural interface


C++ includes: sitkComplexToRealImageFilter.h
";

%feature("docstring")  itk::simple::ComplexToRealImageFilter::ComplexToRealImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ComplexToRealImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ComplexToRealImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ComplexToRealImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ComposeImageFilter "

ComposeImageFiltercombine several scalar images into a multicomponent
image.


ComposeImageFiltercombine several scalar images into an itk::Imageof
vector pixel ( itk::Vector, itk::RGBPixel, ...), of std::complex
pixel, or in an itk::VectorImage.Inputs and Usage
filter->SetInput(0,image0);filter->SetInput(1,image1);...filter->Updat
e(); itk::VectorImage< PixelType, dimension
>::Pointer=filter->GetOutput();All input images are expected to have
the same template parameters and have the same size and origin.

See:
VectorImage
Wiki Examples:

All Examples

Create a vector image from a collection of scalar images

Compose a vector image (with 3 components) from three scalar images

Convert a real image and an imaginary image to a complex image

See:
 itk::simple::Compose for the procedural interface


C++ includes: sitkComposeImageFilter.h
";

%feature("docstring")  itk::simple::ComposeImageFilter::ComposeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "
";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "
";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "
";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "
";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "
";

%feature("docstring")  itk::simple::ComposeImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ComposeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ComposeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ConfidenceConnectedImageFilter "

Segment pixels with similar statistics using connectivity.


This filter extracts a connected set of pixels whose pixel intensities
are consistent with the pixel statistics of a seed point. The mean and
variance across a neighborhood (8-connected, 26-connected, etc.) are
calculated for a seed point. Then pixels connected to this seed point
whose values are within the confidence interval for the seed point are
grouped. The width of the confidence interval is controlled by the
\"Multiplier\" variable (the confidence interval is the mean plus or
minus the \"Multiplier\" times the standard deviation). If the
intensity variations across a segment were gaussian, a \"Multiplier\"
setting of 2.5 would define a confidence interval wide enough to
capture 99% of samples in the segment. After this initial segmentation
is calculated, the mean and variance are re-calculated. All the pixels
in the previous segmentation are used to calculate the mean the
standard deviation (as opposed to using the pixels in the neighborhood
of the seed point). The segmentation is then recalculated using these
refined estimates for the mean and variance of the pixel values. This
process is repeated for the specified number of iterations. Setting
the \"NumberOfIterations\" to zero stops the algorithm after the
initial segmentation from the seed point. NOTE: the lower and upper
threshold are restricted to lie within the valid numeric limits of the
input data pixel type. Also, the limits may be adjusted to contain the
seed point's intensity.Wiki Examples:

All Examples

Segment pixels with similar statistics using connectivity

See:
 itk::simple::ConfidenceConnected for the procedural interface


C++ includes: sitkConfidenceConnectedImageFilter.h
";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::AddSeed "

AddSeed - Add a seed to the end of the list

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::ClearSeeds "

ClearSeeds - Clear out all seeds in the list

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::ConfidenceConnectedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetInitialNeighborhoodRadius "

Get/Set the radius of the neighborhood over which the statistics are
evaluated.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetMultiplier "

Set/Get the multiplier to define the confidence interval. Multiplier
can be anything greater than zero. A typical value is 2.5.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetNumberOfIterations "

Set/Get the number of iterations.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetReplaceValue "

Set/Get value to replace thresholded pixels.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::GetSeedList "

Get SeedList

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetInitialNeighborhoodRadius "

Get/Set the radius of the neighborhood over which the statistics are
evaluated.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetMultiplier "

Set/Get the multiplier to define the confidence interval. Multiplier
can be anything greater than zero. A typical value is 2.5.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetNumberOfIterations "

Set/Get the number of iterations.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetReplaceValue "

Set/Get value to replace thresholded pixels.

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetSeed "

SetSeed - Set list to a single seed

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::SetSeedList "

Set SeedList

";

%feature("docstring")  itk::simple::ConfidenceConnectedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ConnectedComponentImageFilter "

Label the objects in a binary image.


ConnectedComponentImageFilterlabels the objects in a binary image.
Each distinct object is assigned a unique label. The filter
experiments with some improvements to the existing implementation, and
is based on run length encoding along raster lines. The final object
labels start with 1 and are consecutive. Objects that are reached
earlier by a raster order scan have a lower label. This is different
to the behaviour of the original connected component image filter
which did not produce consecutive labels or impose any particular
ordering.
See:
ImageToImageFilter
Wiki Examples:

All Examples

Label connected components in a binary image

See:
 itk::simple::ConnectedComponent for the procedural interface


C++ includes: sitkConnectedComponentImageFilter.h
";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::ConnectedComponentImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::ConnectedComponentImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ConnectedThresholdImageFilter "

Label pixels that are connected to a seed and lie within a range of
values.


ConnectedThresholdImageFilterlabels pixels with ReplaceValue that are
connected to an initial Seed AND lie within a Lower and Upper
threshold range.


See:
 itk::simple::ConnectedThreshold for the procedural interface


C++ includes: sitkConnectedThresholdImageFilter.h
";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::AddSeed "

AddSeed - Add a seed to the end of the list

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::ClearSeeds "

ClearSeeds - Clear out all seeds in the list

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::ConnectedThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::GetLower "
";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::GetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie * within
Lower and Upper (inclusive) will be replaced with this value. The
default is 1.

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::GetSeedList "

Get SeedList

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::GetUpper "

Get Upper and Lower Threshold inputs as values.

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::SetLower "

Set Upper and Lower Threshold inputs as values.

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::SetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie * within
Lower and Upper (inclusive) will be replaced with this value. The
default is 1.

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::SetSeed "

SetSeed - Set list to a single seed

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::SetSeedList "

Set SeedList

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::SetUpper "

Set Upper and Lower Threshold inputs as values.

";

%feature("docstring")  itk::simple::ConnectedThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ConstantPadImageFilter "

Increase the image size by padding with a constant value.


ConstantPadImageFilterchanges the output image region. If the output
image region is larger than the input image region, the extra pixels
are filled in by a constant value. The output image region must be
specified. Visual explanation of padding regions.This filter is
implemented as a multithreaded filter. It provides a
ThreadedGenerateData()method for its implementation.
See:
 WrapPadImageFilter, MirrorPadImageFilter
Wiki Examples:

All Examples

Pad an image with a constant value

See:
 itk::simple::ConstantPad for the procedural interface


C++ includes: sitkConstantPadImageFilter.h
";

%feature("docstring")  itk::simple::ConstantPadImageFilter::ConstantPadImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::GetConstant "

Set/Get the pad value. Default is Zero.

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::GetPadLowerBound "
";

%feature("docstring")  itk::simple::ConstantPadImageFilter::GetPadUpperBound "
";

%feature("docstring")  itk::simple::ConstantPadImageFilter::SetConstant "

Set/Get the pad value. Default is Zero.

";

%feature("docstring")  itk::simple::ConstantPadImageFilter::SetPadLowerBound "
";

%feature("docstring")  itk::simple::ConstantPadImageFilter::SetPadUpperBound "
";

%feature("docstring")  itk::simple::ConstantPadImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ConvolutionImageFilter "

Convolve a given image with an arbitrary image kernel.


This filter operates by centering the flipped kernel at each pixel in
the image and computing the inner product between pixel values in the
image and pixel values in the kernel. The center of the kernel is
defined as $ \\\\lfloor (2*i+s-1)/2 \\\\rfloor $ where $i$ is the index and $s$ is the size of the largest possible region of the kernel image. For
kernels with odd sizes in all dimensions, this corresponds to the
center pixel. If a dimension of the kernel image has an even size,
then the center index of the kernel in that dimension will be the
largest integral index that is less than the continuous index of the
image center. The kernel can optionally be normalized to sum to 1
using NormalizeOn(). Normalization is off by default.
WARNING:
This filter ignores the spacing, origin, and orientation of the kernel
image and treats them as identical to those in the input image. This
code was contributed in the Insight Journal paper: \"Image Kernel
Convolution\" by Tustison N., Gee
J.http://hdl.handle.net/1926/1323http://www.insight-
journal.org/browse/publication/208

Nicholas J. Tustison James C. Gee
Wiki Examples:

All Examples

Convolve an image with a kernel

See:
 itk::simple::Convolution for the procedural interface


C++ includes: sitkConvolutionImageFilter.h
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::ConvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::ConvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::ConvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CosImageFilter "

Computes the cosine of each pixel.


This filter is templated over the pixel type of the input image and
the pixel type of the output image. The filter walks over all of the
pixels in the input image, and for each pixel does the following:


cast the pixel value to double ,

apply the vcl_cos() function to the double value,

cast the double value resulting from vcl_cos() to the pixel type of
the output image,

store the cast value into the output image. The filter expects both
images to have the same dimension (e.g. both 2D, or both 3D, or both
ND)

See:
 itk::simple::Cos for the procedural interface


C++ includes: sitkCosImageFilter.h
";

%feature("docstring")  itk::simple::CosImageFilter::CosImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CosImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::CosImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CosImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CropImageFilter "

Decrease the image size by cropping the image by an itk::Sizeat both
the upper and lower bounds of the largest possible region.


CropImageFilterchanges the image boundary of an image by removing
pixels outside the target region. The target region is not specified
in advance, but calculated in BeforeThreadedGenerateData(). This
filter uses ExtractImageFilterto perform the cropping.Wiki Examples:

All Examples

Crop an image by specifying the region to throw away

See:
 itk::simple::Crop for the procedural interface


C++ includes: sitkCropImageFilter.h
";

%feature("docstring")  itk::simple::CropImageFilter::CropImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CropImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::CropImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::CropImageFilter::GetLowerBoundaryCropSize "

Set/Get the cropping sizes for the upper and lower boundaries.

";

%feature("docstring")  itk::simple::CropImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CropImageFilter::GetUpperBoundaryCropSize "

Set/Get the cropping sizes for the upper and lower boundaries.

";

%feature("docstring")  itk::simple::CropImageFilter::SetLowerBoundaryCropSize "

Set/Get the cropping sizes for the upper and lower boundaries.

";

%feature("docstring")  itk::simple::CropImageFilter::SetUpperBoundaryCropSize "

Set/Get the cropping sizes for the upper and lower boundaries.

";

%feature("docstring")  itk::simple::CropImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CurvatureAnisotropicDiffusionImageFilter "

This filter performs anisotropic diffusion on a scalar itk::Imageusing
the modified curvature diffusion equation (MCDE) implemented in
itkCurvatureNDAnisotropicDiffusionFunction. For detailed information
on anisotropic diffusion and the MCDE see
itkAnisotropicDiffusionFunction and
itkCurvatureNDAnisotropicDiffusionFunction.


Inputs and Outputs
The input and output to this filter must be a scalar itk::Imagewith
numerical pixel types (float or double). A user defined type which
correctly defines arithmetic operations with floating point accuracy
should also give correct results.
Parameters
Please first read all the documentation found in
AnisotropicDiffusionImageFilterand AnisotropicDiffusionFunction. Also
see CurvatureNDAnisotropicDiffusionFunction. The default time step for
this filter is set to the maximum theoretically stable value: 0.5 /
2^N, where N is the dimensionality of the image. For a 2D image, this
means valid time steps are below 0.1250. For a 3D image, valid time
steps are below 0.0625.

See:
AnisotropicDiffusionImageFilter


AnisotropicDiffusionFunction


CurvatureNDAnisotropicDiffusionFunction

 itk::simple::CurvatureAnisotropicDiffusion for the procedural interface


C++ includes: sitkCurvatureAnisotropicDiffusionImageFilter.h
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::CurvatureAnisotropicDiffusionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::EstimateOptimalTimeStep "

This method autmatically sets the optimal timestep for an image given
its spacing.

";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::GetConductanceParameter "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::GetConductanceScalingUpdateInterval "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::GetTimeStep "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::SetConductanceParameter "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::SetConductanceScalingUpdateInterval "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::SetTimeStep "
";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::CurvatureFlowImageFilter "

Denoise an image using curvature driven flow.


CurvatureFlowImageFilterimplements a curvature driven image denoising
algorithm. Iso-brightness contours in the grayscale input image are
viewed as a level set. The level set is then evolved using a
curvature-based speed function: \\\\[ I_t = \\\\kappa |\\\\nabla I| \\\\] where $ \\\\kappa $ is the curvature. The advantage of this approach is that sharp
boundaries are preserved with smoothing occurring only within a
region. However, it should be noted that continuous application of
this scheme will result in the eventual removal of all information as
each contour shrinks to zero and disappear. Note that unlike level set
segmentation algorithms, the image to be denoised is already the level
set and can be set directly as the input using the SetInput()method.
This filter has two parameters: the number of update iterations to be
performed and the timestep between each update. The timestep should be
\"small enough\" to ensure numerical stability. Stability is guarantee
when the timestep meets the CFL (Courant-Friedrichs-Levy) condition.
Broadly speaking, this condition ensures that each contour does not
move more than one grid position at each timestep. In the literature,
the timestep is typically user specified and have to manually tuned to
the application. This filter make use of the multi-threaded finite
difference solver hierarchy. Updates are computed using a
CurvatureFlowFunctionobject. A zero flux Neumann boundary condition
when computing derivatives near the data boundary. This filter may be
streamed. To support streaming this filter produces a padded output
which takes into account edge effects. The size of the padding is
m_NumberOfIterations on each edge. Users of this filter should only
make use of the center valid central region.
WARNING:
This filter assumes that the input and output types have the same
dimensions. This filter also requires that the output image pixels are
of a floating point type. This filter works for any dimensional
images. Reference: \"Level Set Methods and Fast Marching Methods\",
J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.

See:
DenseFiniteDifferenceImageFilter


CurvatureFlowFunction


 MinMaxCurvatureFlowImageFilter


 BinaryMinMaxCurvatureFlowImageFilter Input/Output Restrictions: TInputImage and TOutputImage must have the
same dimension. TOutputImage's pixel type must be a real number type.

 itk::simple::CurvatureFlow for the procedural interface


C++ includes: sitkCurvatureFlowImageFilter.h
";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::CurvatureFlowImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::GetTimeStep "

Get the timestep parameter.

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::SetTimeStep "

Set the timestep parameter.

";

%feature("docstring")  itk::simple::CurvatureFlowImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::DanielssonDistanceMapImageFilter "

This filter computes the distance map of the input image as an
approximation with pixel accuracy to the Euclidean distance.


TInputImageInput ImageType TOutputImageOutput ImageType
TVoronoiImageVoronoi ImageType. Note the default value is TInputImage.
The input is assumed to contain numeric codes defining objects. The
filter will produce as output the following images:


AVoronoi partitionusing the same numeric codes as the input.

Adistance mapwith the approximation to the euclidean distance. from a
particular pixel to the nearest object to this pixel in the input
image.

Avector mapcontaining the component of the vector relating the current
pixel with the closest point of the closest object to this pixel.
Given that the components of the distance are computed in \"pixels\",
the vector is represented by an itk::Offset. That is, physical
coordinates are not used. This filter is N-dimensional and known to be
efficient in computational time. The algorithm is the N-dimensional
version of the 4SED algorithm given for two dimensions in: Danielsson,
Per-Erik. Euclidean Distance Mapping. Computer Graphics and
ImageProcessing 14, 227-248 (1980).

See:
 itk::simple::DanielssonDistanceMap for the procedural interface


C++ includes: sitkDanielssonDistanceMapImageFilter.h
";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::DanielssonDistanceMapImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::GetInputIsBinary "

Get if the input is binary. See SetInputIsBinary().

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::GetSquaredDistance "

Get the distance squared.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::GetUseImageSpacing "

Get whether spacing is used.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::InputIsBinaryOff "
";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::InputIsBinaryOn "

Set the value of InputIsBinary to true or false respectfully.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::SetInputIsBinary "

Set if the input is binary. If this variable is set, each nonzero
pixel in the input image will be given a unique numeric code to be
used by the Voronoi partition. If the image is binary but you are not
interested in the Voronoi regions of the different nonzero pixels,
then you need not set this.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::SetSquaredDistance "

Set if the distance should be squared.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::SetUseImageSpacing "

Set if image spacing should be used in computing distances.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::SquaredDistanceOff "
";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::SquaredDistanceOn "

Set the value of SquaredDistance to true or false respectfully.

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::DanielssonDistanceMapImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::DerivativeImageFilter "

Computes the directional derivative of an image. The directional
derivative at each pixel location is computed by convolution with a
derivative operator of user-specified order.


SetOrder specifies the order of the derivative. SetDirection specifies
the direction of the derivative with respect to the coordinate axes of
the image.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Compute the derivative of an image in a particular direction

See:
 itk::simple::Derivative for the procedural interface


C++ includes: sitkDerivativeImageFilter.h
";

%feature("docstring")  itk::simple::DerivativeImageFilter::DerivativeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DerivativeImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::DerivativeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::DerivativeImageFilter::GetDirection "

End concept checking Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DerivativeImageFilter::GetOrder "

End concept checking Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::SetDirection "

End concept checking Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::SetOrder "

End concept checking Standard get/set macros for filter parameters.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::DerivativeImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::DerivativeImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::DerivativeImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::DilateObjectMorphologyImageFilter "

dilation of an object in an image


Dilate an image using binary morphology. Pixel values matching the
object value are considered the \"foreground\" and all other pixels
are \"background\". This is useful in processing mask images
containing only one object. If a pixel's value is equal to the object
value and the pixel is adjacent to a non-object valued pixel, then the
kernel is centered on the object-value pixel and neighboring pixels
covered by the kernel are assigned the object value. The structuring
element is assumed to be composed of binary values (zero or one).
See:
ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter


 BinaryDilateImageFilter

 itk::simple::DilateObjectMorphology for the procedural interface


C++ includes: sitkDilateObjectMorphologyImageFilter.h
";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::DilateObjectMorphologyImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::GetObjectValue "
";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::SetObjectValue "
";

%feature("docstring")  itk::simple::DilateObjectMorphologyImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::DiscreteGaussianImageFilter "

Blurs an image by separable convolution with discrete gaussian
kernels. This filter performs Gaussian blurring by separable
convolution of an image and a discrete Gaussian operator (kernel).


The Gaussian operator used here was described by Tony Lindeberg
(Discrete Scale-Space Theory and the Scale-Space Primal Sketch.
Dissertation. Royal Institute of Technology, Stockholm, Sweden. May
1991.) The Gaussian kernel used here was designed so that smoothing
and derivative operations commute after discretization. The variance
or standard deviation (sigma) will be evaluated as pixel units if
SetUseImageSpacing is off (false) or as physical units if
SetUseImageSpacing is on (true, default). The variance can be set
independently in each dimension. When the Gaussian kernel is small,
this filter tends to run faster than
itk::RecursiveGaussianImageFilter.
See:
GaussianOperator


 Image


Neighborhood


NeighborhoodOperator


 RecursiveGaussianImageFilter
Wiki Examples:

All Examples

Smooth an image with a discrete Gaussian filter

See:
 itk::simple::DiscreteGaussian for the procedural interface


C++ includes: sitkDiscreteGaussianImageFilter.h
";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::DiscreteGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::GetMaximumError "

The algorithm will size the discrete kernel so that the error
resulting from truncation of the kernel is no greater than
MaximumError. The default is 0.01 in each dimension.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::GetMaximumKernelWidth "

Set the kernel to be no wider than MaximumKernelWidth pixels, even if
MaximumError demands it. The default is 32 pixels.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::GetVariance "

The variance for the discrete Gaussian kernel. Sets the variance
independently for each dimension, but see also SetVariance(const double v). The default is 0.0 in each dimension. If UseImageSpacing is true,
the units are the physical units of your image. If UseImageSpacing is
false then the units are pixels.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::SetMaximumError "
";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::SetMaximumKernelWidth "

Set the kernel to be no wider than MaximumKernelWidth pixels, even if
MaximumError demands it. The default is 32 pixels.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::SetVariance "
";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::DiscreteGaussianImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::DivideFloorImageFilter "


See:
 itk::simple::DivideFloor for the procedural interface


C++ includes: sitkDivideFloorImageFilter.h
";

%feature("docstring")  itk::simple::DivideFloorImageFilter::DivideFloorImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DivideFloorImageFilter::Execute "
";

%feature("docstring")  itk::simple::DivideFloorImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::DivideFloorImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::DivideFloorImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DivideFloorImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::DivideImageFilter "

Pixel-wise division of two images.


This class is templated over the types of the two input images and the
type of the output image. When the divisor is zero, the division
result is set to the maximum number that can be represented by default
to avoid exception. Numeric conversions (castings) are done by the C++
defaults.Wiki Examples:

All Examples

Pixel-wise division of two images

See:
 itk::simple::Divide for the procedural interface


C++ includes: sitkDivideImageFilter.h
";

%feature("docstring")  itk::simple::DivideImageFilter::DivideImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DivideImageFilter::Execute "
";

%feature("docstring")  itk::simple::DivideImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::DivideImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::DivideImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DivideImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::DivideRealImageFilter "


See:
 itk::simple::DivideReal for the procedural interface


C++ includes: sitkDivideRealImageFilter.h
";

%feature("docstring")  itk::simple::DivideRealImageFilter::DivideRealImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DivideRealImageFilter::Execute "
";

%feature("docstring")  itk::simple::DivideRealImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::DivideRealImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::DivideRealImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DivideRealImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::DoubleThresholdImageFilter "

Binarize an input image using double thresholding.


Double threshold addresses the difficulty in selecting a threshold
that will select the objects of interest without selecting extraneous
objects. Double threshold considers two threshold ranges: a narrow
range and a wide range (where the wide range encompasses the narrow
range). If the wide range was used for a traditional threshold (where
values inside the range map to the foreground and values outside the
range map to the background), many extraneous pixels may survive the
threshold operation. If the narrow range was used for a traditional
threshold, then too few pixels may survive the threshold. Double
threshold uses the narrow threshold image as a marker image and the
wide threshold image as a mask image in the geodesic dilation.
Essentially, the marker image (narrow threshold) is dilated but
constrained to lie within the mask image (wide threshold). Thus, only
the objects of interest (those pixels that survived the narrow
threshold) are extracted but the those objects appear in the final
image as they would have if the wide threshold was used.
See:
 GrayscaleGeodesicDilateImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::DoubleThreshold for the procedural interface


C++ includes: sitkDoubleThresholdImageFilter.h
";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::DoubleThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetThreshold1 "

Get the threshold values.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetThreshold2 "

Get the threshold values.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetThreshold3 "

Get the threshold values.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::GetThreshold4 "

Get the threshold values.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value. The default value
NumericTraits<OutputPixelType>::max().

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetThreshold1 "

Set the thresholds. Four thresholds should be specified. The two lower
thresholds default to NumericTraits<InputPixelType>::NonpositiveMin().
The two upper thresholds default NumericTraits<InputPixelType>::max.
Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetThreshold2 "

Set the thresholds. Four thresholds should be specified. The two lower
thresholds default to NumericTraits<InputPixelType>::NonpositiveMin().
The two upper thresholds default NumericTraits<InputPixelType>::max.
Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetThreshold3 "

Set the thresholds. Four thresholds should be specified. The two lower
thresholds default to NumericTraits<InputPixelType>::NonpositiveMin().
The two upper thresholds default NumericTraits<InputPixelType>::max.
Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::SetThreshold4 "

Set the thresholds. Four thresholds should be specified. The two lower
thresholds default to NumericTraits<InputPixelType>::NonpositiveMin().
The two upper thresholds default NumericTraits<InputPixelType>::max.
Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.

";

%feature("docstring")  itk::simple::DoubleThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::EdgePotentialImageFilter "

Computes the edge potential of an image from the image gradient.


Input to this filter should be a CovariantVectorimage representing the
image gradient. The filter expect both the input and output images to
have the same number of dimensions, and the output to be of a scalar
image type.


See:
 itk::simple::EdgePotential for the procedural interface


C++ includes: sitkEdgePotentialImageFilter.h
";

%feature("docstring")  itk::simple::EdgePotentialImageFilter::EdgePotentialImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::EdgePotentialImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::EdgePotentialImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::EdgePotentialImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::EqualImageFilter "


See:
 itk::simple::Equal for the procedural interface


C++ includes: sitkEqualImageFilter.h
";

%feature("docstring")  itk::simple::EqualImageFilter::EqualImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::EqualImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::EqualImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::EqualImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::EqualImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::EqualImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::EqualImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::EqualImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ErodeObjectMorphologyImageFilter "

Erosion of an object in an image.


Erosion of an image using binary morphology. Pixel values matching the
object value are considered the \"object\" and all other pixels are
\"background\". This is useful in processing mask images containing
only one object. If the pixel covered by the center of the kernel has
the pixel value ObjectValue and the pixel is adjacent to a non-object
valued pixel, then the kernel is centered on the object-value pixel
and neighboring pixels covered by the kernel are assigned the
background value. The structuring element is assumed to be composed of
binary values (zero or one).
See:
ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter


 BinaryErodeImageFilter

 itk::simple::ErodeObjectMorphology for the procedural interface


C++ includes: sitkErodeObjectMorphologyImageFilter.h
";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::ErodeObjectMorphologyImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::GetBackgroundValue "

Get the value to be assigned to eroded pixels.

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::GetObjectValue "
";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::SetBackgroundValue "

Set the value to be assigned to eroded pixels.

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::SetObjectValue "
";

%feature("docstring")  itk::simple::ErodeObjectMorphologyImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ExpImageFilter "

Computes the exponential function of each pixel.


The computation is performed using vcl_exp(x).


See:
 itk::simple::Exp for the procedural interface


C++ includes: sitkExpImageFilter.h
";

%feature("docstring")  itk::simple::ExpImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ExpImageFilter::ExpImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ExpImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ExpImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ExpNegativeImageFilter "

Computes the function exp(-K.x) for each input pixel.


Every output pixel is equal to vcl_exp(-K.x ). where x is the
intensity of the homologous input pixel, and K is a user-provided
constant.


See:
 itk::simple::ExpNegative for the procedural interface


C++ includes: sitkExpNegativeImageFilter.h
";

%feature("docstring")  itk::simple::ExpNegativeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ExpNegativeImageFilter::ExpNegativeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ExpNegativeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ExpNegativeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ExpandImageFilter "

Expand the size of an image by an integer factor in each dimension.


ExpandImageFilterincreases the size of an image by an integer factor
in each dimension using a interpolation method. The output image size
in each dimension is given by: OutputSize[j] = InputSize[j] *
ExpandFactors[j] The output values are obtained by interpolating the
input image. The default interpolation type used is the
LinearInterpolateImageFunction. The user can specify a particular
interpolation function via SetInterpolator(). Note that the input interpolator must derive from base class
InterpolateImageFunction. This filter will produce an output with
different pixel spacing that its input image such that:
OutputSpacing[j] = InputSpacing[j] / ExpandFactors[j] The filter is
templated over the input image type and the output image type. This
filter is implemented as a multithreaded filter and supports
streaming.
WARNING:
This filter only works for image with scalar pixel types. For vector
images use VectorExpandImageFilter. This filter assumes that the input
and output image has the same number of dimensions.

See:
InterpolateImageFunction


LinearInterpolationImageFunction


VectorExpandImageFilter

 itk::simple::Expand for the procedural interface


C++ includes: sitkExpandImageFilter.h
";

%feature("docstring")  itk::simple::ExpandImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ExpandImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ExpandImageFilter::ExpandImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ExpandImageFilter::GetExpandFactors "

Get the expand factors.

";

%feature("docstring")  itk::simple::ExpandImageFilter::GetInterpolator "

Get a pointer to the interpolator function.

";

%feature("docstring")  itk::simple::ExpandImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ExpandImageFilter::SetExpandFactor "

Custom public declarations

";

%feature("docstring")  itk::simple::ExpandImageFilter::SetExpandFactors "

Set the expand factors. Values are clamped to a minimum value of 1.
Default is 1 for all dimensions.

";

%feature("docstring")  itk::simple::ExpandImageFilter::SetInterpolator "

Set the interpolator function.

";

%feature("docstring")  itk::simple::ExpandImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ExtractImageFilter "

Decrease the image size by cropping the image to the selected region
bounds.


ExtractImageFilterchanges the image boundary of an image by removing
pixels outside the target region. The target region must be specified.
ExtractImageFilteralso collapses dimensions so that the input image
may have more dimensions than the output image (i.e. 4-D input image
to a 3-D output image). To specify what dimensions to collapse, the
ExtractionRegion must be specified. For any dimension dim where
ExtractionRegion.Size[dim] = 0, that dimension is collapsed. The index
to collapse on is specified by ExtractionRegion.Index[dim]. For
example, we have a image 4D = a 4x4x4x4 image, and we want to get a 3D
image, 3D = a 4x4x4 image, specified as [x,y,z,2] from 4D (i.e. the
3rd \"time\" slice from 4D). The ExtractionRegion.Size = [4,4,4,0] and
ExtractionRegion.Index = [0,0,0,2]. The number of dimension in
ExtractionRegion.Size and Indexmust = InputImageDimension. The number
of non-zero dimensions in ExtractionRegion.Size must =
OutputImageDimension. The output image produced by this filter will
have the same origin as the input image, while the ImageRegionof the
output image will start at the starting index value provided in the
ExtractRegion parameter. If you are looking for a filter that will re-
compute the origin of the output image, and provide an output image
region whose index is set to zeros, then you may want to use the RegionOfInterestImageFilter. The output spacing is is simply the collapsed version of the input
spacing. Determining the direction of the collapsed output image from
an larger dimensional input space is an ill defined problem in
general. It is required that the application developer select the
desired transformation strategy for collapsing direction cosigns. It
is REQUIRED that a strategy be explicitly requested (i.e. there is no
working default). Direction Collapsing Strategies: 1)
DirectionCollapseToUnknown(); This is the default and the filter can
not run when this is set. The reason is to explicitly force the
application developer to define their desired behavior. 1)
DirectionCollapseToIdentity(); Output has identity direction no matter
what 2) DirectionCollapseToSubmatrix(); Output direction is the sub-
matrix if it is positive definite, else throw an exception. This
filter is implemented as a multithreaded filter. It provides a
ThreadedGenerateData()method for its implementation.
This filter is derived from InPlaceImageFilter. When the input to this
filter matched the output requirested region, like with streaming
filter for input, then setting this filter to run in-place will result
in no copying of the bulk pixel data.

See:
 CropImageFilter
Wiki Examples:

All Examples

Crop an image by specifying the region to keep

See:
 itk::simple::Extract for the procedural interface


C++ includes: sitkExtractImageFilter.h
";

%feature("docstring")  itk::simple::ExtractImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ExtractImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ExtractImageFilter::ExtractImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ExtractImageFilter::GetDirectionCollapseToStrategy "

NOTE: The SetDirectionCollapseToUknown is explicitly not defined. It
is a state that a filter can be in only when it is first instantiate
prior to being initialized. Get the currently set strategy for
collapsing directions of physical space.

";

%feature("docstring")  itk::simple::ExtractImageFilter::GetIndex "
";

%feature("docstring")  itk::simple::ExtractImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ExtractImageFilter::GetSize "
";

%feature("docstring")  itk::simple::ExtractImageFilter::SetDirectionCollapseToStrategy "

Set the strategy to be used to collapse pysical space dimensions.
itk::itkExtractImageFilter::DIRECTIONCOLLAPSETOIDENTITY Set the
strategy so that all collapsed images have an identity direction. Use
this strategy when you know that retention of the physical space
orientation of the collapsed image is not important.
itk::itkExtractImageFilter::DIRECTIONCOLLAPSETOGUESS Set the strategy
so that all collapsed images where output direction is the sub-matrix
it it is positive definite, else return identity. This is backwards
compatible with ITKv3, but is highly discouraged because the results
are difficult to anticipate under differing data scenerios.
itk::itkExtractImageFilter::DIRECTIONCOLLAPSETOSUBMATRIX Set the
strategy so that all collapsed images where output direction is the
sub-matrix it it is positive definite, else throw an exception. Use
this strategy when it is known that properly identified physical space
sub-volumes can be reliably extracted from a higher dimensional space.
For example when the application programmer knows that a 4D image is
3D+time, and that the 3D sub-space is properly defined.

";

%feature("docstring")  itk::simple::ExtractImageFilter::SetIndex "

odo the internal setting of the method needs work!!!

";

%feature("docstring")  itk::simple::ExtractImageFilter::SetSize "
";

%feature("docstring")  itk::simple::ExtractImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FFTConvolutionImageFilter "

Convolve a given image with an arbitrary image kernel using
multiplication in the Fourier domain.


This filter produces output equivalent to the output of the ConvolutionImageFilter. However, it takes advantage of the convolution theorem to accelerate
the convolution computation when the kernel is large.
WARNING:
This filter ignores the spacing, origin, and orientation of the kernel
image and treats them as identical to those in the input image. This
code was adapted from the Insight Journal contribution: \"FFT Based
Convolution\" by Gaetan Lehmannhttp://hdl.handle.net/10380/3154

See:
 ConvolutionImageFilter

 itk::simple::FFTConvolution for the procedural interface


C++ includes: sitkFFTConvolutionImageFilter.h
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::FFTConvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::FFTConvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FFTNormalizedCorrelationImageFilter "

Calculate normalized cross correlation using FFTs.


This filter calculates the normalized cross correlation (NCC) of two
images using FFTs instead of spatial correlation. It is much faster
than spatial correlation for reasonably large structuring elements.
This filter is a subclass of the more general
MaskedFFTNormalizedCorrelationImageFilterand operates by essentially
setting the masks in that algorithm to images of ones. As described in detail in the references below, there is no computational overhead to
utilizing the more general masked algorithm because the FFTs of the
images of ones are still necessary for the computations. Inputs: Two
images are required as inputs, fixedImage and movingImage. In the
context of correlation, inputs are often defined as: \"image\" and
\"template\". In this filter, the fixedImage plays the role of the
image, and the movingImage plays the role of the template. However,
this filter is capable of correlating any two images and is not
restricted to small movingImages (templates). Optional parameters: The
RequiredNumberOfOverlappingPixels enables the user to specify how many
voxels of the two images must overlap; any location in the correlation
map that results from fewer than this number of voxels will be set to
zero. Larger values zero-out pixels on a larger border around the
correlation image. Thus, larger values remove less stable computations
but also limit the capture range. If RequiredNumberOfOverlappingPixels
is set to 0, the default, no zeroing will take place. Imagesize:
fixedImage and movingImage need not be the same size. Furthermore,
whereas some algorithms require that the \"template\" be smaller than
the \"image\" because of errors in the regions where the two are not
fully overlapping, this filter has no such restriction. Imagespacing:
Since the computations are done in the pixel domain, all input images
must have the same spacing. Outputs; The output is an image of
RealPixelType that is the NCC of the two images and its values range
from -1.0 to 1.0. The size of this NCC image is, by definition,
size(fixedImage) + size(movingImage) - 1. Example filter usage:typedef
itk::FFTNormalizedCorrelationImageFilter< ShortImageType,
DoubleImageType >FilterType;FilterType::Pointerfilter=FilterTypeNew();
filter->SetFixedImage(fixedImage);filter->SetMovingImage(movingImage);
filter->SetRequiredNumberOfOverlappingPixels(20);filter->Update();
WARNING:
The pixel type of the output image must be of real type (float or
double). ConceptChecking is used to enforce the output pixel type. You
will get a compilation error if the pixel type of the output image is
not float or double. References: 1) D. Padfield. \"Masked object
registration in the Fourier domain.\" Transactions on ImageProcessing.
2) D. Padfield. \"Masked FFT registration\". In Proc. Computer Vision
and Pattern Recognition, 2010.

: Dirk Padfield, GE Global Research,padfield@research.ge.com

See:
 itk::simple::FFTNormalizedCorrelation for the procedural interface


C++ includes: sitkFFTNormalizedCorrelationImageFilter.h
";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::FFTNormalizedCorrelationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::GetRequiredNumberOfOverlappingPixels "
";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::SetRequiredNumberOfOverlappingPixels "
";

%feature("docstring")  itk::simple::FFTNormalizedCorrelationImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FFTShiftImageFilter "

Shift the zero-frequency components of a Fourier transfrom to the
center of the image.


The Fourier transform produces an image where the zero frequency
components are in the corner of the image, making it difficult to
understand. This filter shifts the component to the center of the
image.
For images with an odd-sized dimension, applying this filter twice
will not produce the same image as the original one without using
SetInverse(true) on one (and only one) of the two filters.http://hdl.handle.net/1926/321

Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 ForwardFFTImageFilter, InverseFFTImageFilter

 itk::simple::FFTShift for the procedural interface


C++ includes: sitkFFTShiftImageFilter.h
";

%feature("docstring")  itk::simple::FFTShiftImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::FFTShiftImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::GetInverse "

Set/Get whether the filter must invert the transform or not. This
option has no effect if none of the size of the input image is even,
but is required to restore the original image if at least one of the
dimensions has an odd size.

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::InverseOff "
";

%feature("docstring")  itk::simple::FFTShiftImageFilter::InverseOn "

Set the value of Inverse to true or false respectfully.

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::SetInverse "

Set/Get whether the filter must invert the transform or not. This
option has no effect if none of the size of the input image is even,
but is required to restore the original image if at least one of the
dimensions has an odd size.

";

%feature("docstring")  itk::simple::FFTShiftImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FastApproximateRankImageFilter "


See:
 itk::simple::FastApproximateRank for the procedural interface


C++ includes: sitkFastApproximateRankImageFilter.h
";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::FastApproximateRankImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::GetRank "
";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::SetRank "
";

%feature("docstring")  itk::simple::FastApproximateRankImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FastMarchingImageFilter "

Solve an Eikonal equation using Fast Marching.


Fast marching solves an Eikonal equation where the speed is always
non-negative and depends on the position only. Starting from an
initial position on the front, fast marching systematically moves the
front forward one grid point at a time. Updates are preformed using an
entropy satisfy scheme where only \"upwind\" neighborhoods are used.
This implementation of Fast Marching uses a std::priority_queue to
locate the next proper grid position to update. Fast Marching sweeps
through N grid points in (N log N) steps to obtain the arrival time
value as the front propagates through the grid. Implementation of this
class is based on Chapter 8 of \"Level Set Methods and Fast Marching
Methods\", J.A. Sethian, Cambridge Press, Second edition, 1999. This
class is templated over the level set image type and the speed image
type. The initial front is specified by two containers: one containing
the known points and one containing the trial points. Alive points are
those that are already part of the object, and trial points are
considered for inclusion. In order for the filter to evolve, at least
some trial points must be specified. These can for instance be
specified as the layer of pixels around the alive points. The speed
function can be specified as a speed image or a speed constant. The
speed image is set using the method SetInput(). If the speed image is
NULL, a constant speed function is used and is specified using method
the SetSpeedConstant(). If the speed function is constant and of value
one, fast marching results in an approximate distance function from
the initial alive points. FastMarchingImageFilteris used in the
ReinitializeLevelSetImageFilterobject to create a signed distance
function from the zero level set. The algorithm can be terminated
early by setting an appropriate stopping value. The algorithm
terminates when the current arrival time being processed is greater
than the stopping value. There are two ways to specify the output
image information ( LargestPossibleRegion, Spacing, Origin): (a) it is
copied directly from the input speed image or (b) it is specified by
the user. Default values are used if the user does not specify all the
information. The output information is computed as follows. If the
speed image is NULL or if the OverrideOutputInformation is set to
true, the output information is set from user specified parameters.
These parameters can be specified using methods SetOutputRegion(),
SetOutputSpacing(), SetOutputDirection(), and SetOutputOrigin(). Else
if the speed image is not NULL, the output information is copied from
the input speed image. Possible Improvements: In the current
implemenation, std::priority_queue only allows taking nodes out from
the front and putting nodes in from the back. To update a value
already on the heap, a new node is added to the heap. The defunct old
node is left on the heap. When it is removed from the top, it will be
recognized as invalid and not used. Future implementations can
implement the heap in a different way allowing the values to be
updated. This will generally require some sift-up and sift-down
functions and an image of back-pointers going from the image to heap
in order to locate the node which is to be updated.
See:
LevelSetTypeDefault

 itk::simple::FastMarching for the procedural interface


C++ includes: sitkFastMarchingImageFilter.h
";

%feature("docstring")  itk::simple::FastMarchingImageFilter::AddTrialPoint "

Add trial point

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::ClearTrialPoints "

Clear trial points

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::FastMarchingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::GetNormalizationFactor "

Set/Get the Normalization Factor for the Speed Image. The values in the Speed Imageis divided by this factor. This allows
the use of images with integer pixel types to represent the speed.

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::GetStoppingValue "

Get the Fast Marching algorithm Stopping Value.

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::GetTopologyCheck "
";

%feature("docstring")  itk::simple::FastMarchingImageFilter::GetTrialPoints "

Get trial points

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::SetNormalizationFactor "

Set/Get the Normalization Factor for the Speed Image. The values in the Speed Imageis divided by this factor. This allows
the use of images with integer pixel types to represent the speed.

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::SetStoppingValue "

Set the Fast Marching algorithm Stopping Value. The Fast Marching
algorithm is terminated when the value of the smallest trial point is
greater than the stopping value.

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::SetTopologyCheck "
";

%feature("docstring")  itk::simple::FastMarchingImageFilter::SetTrialPoints "

Set trial points. The default trial value (i.e. 0.0) is used for each
index.

";

%feature("docstring")  itk::simple::FastMarchingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::FlipImageFilter "

Flips an image across user specified axes.


FlipImageFilterflips an image across user specified axes. The flip
axes are set via method SetFlipAxes( array ) where the input is a
FixedArray<bool,ImageDimension>. The image is flipped across axes for
which array[i] is true. In terms of grid coordinates the image is
flipped within the LargestPossibleRegion of the input image. As such,
the LargestPossibleRegion of the ouput image is the same as the input.
In terms of geometric coordinates, the output origin is such that the
image is flipped with respect to the coordinate axes.Wiki Examples:

All Examples

Flip an image over specified axes

See:
 itk::simple::Flip for the procedural interface


C++ includes: sitkFlipImageFilter.h
";

%feature("docstring")  itk::simple::FlipImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::FlipImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::FlipImageFilter::FlipAboutOriginOff "
";

%feature("docstring")  itk::simple::FlipImageFilter::FlipAboutOriginOn "

Set the value of FlipAboutOrigin to true or false respectfully.

";

%feature("docstring")  itk::simple::FlipImageFilter::FlipImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::FlipImageFilter::GetFlipAboutOrigin "

Controls how the output origin is computed. If FlipAboutOrigin is
\"on\", the flip will occur about the origin of the axis, otherwise,
the flip will occur about the center of the axis.

";

%feature("docstring")  itk::simple::FlipImageFilter::GetFlipAxes "

Set/Get the axis to be flipped. The image is flipped along axes for
which array[i] is true.

";

%feature("docstring")  itk::simple::FlipImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::FlipImageFilter::SetFlipAboutOrigin "

Controls how the output origin is computed. If FlipAboutOrigin is
\"on\", the flip will occur about the origin of the axis, otherwise,
the flip will occur about the center of the axis.

";

%feature("docstring")  itk::simple::FlipImageFilter::SetFlipAxes "

Set/Get the axis to be flipped. The image is flipped along axes for
which array[i] is true.

";

%feature("docstring")  itk::simple::FlipImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ForwardFFTImageFilter "

Base class for forward Fast Fourier Transform.


This is a base class for the \"forward\" or \"direct\" discrete
Fourier Transform. This is an abstract base class: the actual implementation is
provided by the best child class available on the system when the
object is created via the object factory system. This class transforms
a real input image into its full complex Fourier transform. The
Fourier transform of a real input image has Hermitian symmetry: $ f(\\\\mathbf{x}) = f^*(-\\\\mathbf{x}) $ . That is, when the result of the transform is split in half along
the x-dimension, the values in the second half of the transform are
the complex conjugates of values in the first half reflected about the
center of the image in each dimension. This filter works only for real
single-component input image types.
See:
 InverseFFTImageFilter, FFTComplexToComplexImageFilter

 itk::simple::ForwardFFT for the procedural interface


C++ includes: sitkForwardFFTImageFilter.h
";

%feature("docstring")  itk::simple::ForwardFFTImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ForwardFFTImageFilter::ForwardFFTImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ForwardFFTImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ForwardFFTImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GaborImageSource "


See:
 itk::simple::GaborImageSource for the procedural interface


C++ includes: sitkGaborImageSource.h
";

%feature("docstring")  itk::simple::GaborImageSource::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GaborImageSource::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GaborImageSource::GaborImageSource "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GaborImageSource::GetDirection "
";

%feature("docstring")  itk::simple::GaborImageSource::GetFrequency "
";

%feature("docstring")  itk::simple::GaborImageSource::GetMean "
";

%feature("docstring")  itk::simple::GaborImageSource::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GaborImageSource::GetOrigin "
";

%feature("docstring")  itk::simple::GaborImageSource::GetOutputPixelType "
";

%feature("docstring")  itk::simple::GaborImageSource::GetSigma "
";

%feature("docstring")  itk::simple::GaborImageSource::GetSize "
";

%feature("docstring")  itk::simple::GaborImageSource::GetSpacing "
";

%feature("docstring")  itk::simple::GaborImageSource::SetDirection "
";

%feature("docstring")  itk::simple::GaborImageSource::SetFrequency "
";

%feature("docstring")  itk::simple::GaborImageSource::SetMean "
";

%feature("docstring")  itk::simple::GaborImageSource::SetOrigin "
";

%feature("docstring")  itk::simple::GaborImageSource::SetOutputPixelType "
";

%feature("docstring")  itk::simple::GaborImageSource::SetSigma "
";

%feature("docstring")  itk::simple::GaborImageSource::SetSize "
";

%feature("docstring")  itk::simple::GaborImageSource::SetSpacing "
";

%feature("docstring")  itk::simple::GaborImageSource::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GaussianImageSource "


See:
 itk::simple::GaussianImageSource for the procedural interface


C++ includes: sitkGaussianImageSource.h
";

%feature("docstring")  itk::simple::GaussianImageSource::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GaussianImageSource::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GaussianImageSource::GaussianImageSource "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GaussianImageSource::GetDirection "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetMean "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GaussianImageSource::GetOrigin "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetOutputPixelType "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetScale "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetSigma "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetSize "
";

%feature("docstring")  itk::simple::GaussianImageSource::GetSpacing "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetDirection "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetMean "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetOrigin "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetOutputPixelType "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetScale "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetSigma "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetSize "
";

%feature("docstring")  itk::simple::GaussianImageSource::SetSpacing "
";

%feature("docstring")  itk::simple::GaussianImageSource::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GenericException "

The base SimpleITK exception class.

C++ includes: sitkExceptionObject.h
";

%feature("docstring")  itk::simple::GenericException::GenericException "
 throw ()
Constructor. Needed to ensure the exception object can be copied.

";

%feature("docstring")  itk::simple::GenericException::GenericException "
 throw ()
Constructor. Needed to ensure the exception object can be copied.

";

%feature("docstring")  itk::simple::GenericException::GenericException "
 throw ()
Constructor. Needed to ensure the exception object can be copied.

";

%feature("docstring")  itk::simple::GenericException::GenericException "
 throw ()";

%feature("docstring")  itk::simple::GenericException::GenericException "
 throw ()
Default constructor. Needed to ensure the exception object can be
copied.

";

%feature("docstring")  itk::simple::GenericException::GetDescription "
";

%feature("docstring")  itk::simple::GenericException::GetFile "

What file did the exception occur in?

";

%feature("docstring")  itk::simple::GenericException::GetLine "

What line did the exception occur in?

";

%feature("docstring")  itk::simple::GenericException::GetLocation "
";

%feature("docstring")  itk::simple::GenericException::GetNameOfClass "
";

%feature("docstring")  itk::simple::GenericException::ToString "

Return a description of the error

";

%feature("docstring")  itk::simple::GenericException::what "
 throw ()";

%feature("docstring")  itk::simple::GenericException::~GenericException "
 throw ( )
Virtual destructor needed for subclasses. Has to have empty throw().

";


%feature("docstring") itk::simple::GeodesicActiveContourLevelSetImageFilter "

Segments structures in images based on a user supplied edge potential
map.


IMPORTANT
The SegmentationLevelSetImageFilterclass and the
GeodesicActiveContourLevelSetFunctionclass contain additional
information necessary to gain full understanding of how to use this
filter.
OVERVIEW
This class is a level set method segmentation filter. An initial
contour is propagated outwards (or inwards) until it ''sticks'' to the
shape boundaries. This is done by using a level set speed function
based on a user supplied edge potential map.
INPUTS
This filter requires two inputs. The first input is a initial level
set. The initial level set is a real image which contains the initial
contour/surface as the zero level set. For example, a signed distance
function from the initial contour/surface is typically used. Unlike
the simpler ShapeDetectionLevelSetImageFilterthe initial contour does
not have to lie wholly within the shape to be segmented. The initial
contour is allow to overlap the shape boundary. The extra advection
term in the update equation behaves like a doublet and attracts the
contour to the boundary. This approach for segmentation follows that
of Caselles et al (1997).
The second input is the feature image. For this filter, this is the
edge potential map. General characteristics of an edge potential map
is that it has values close to zero in regions near the edges and
values close to one inside the shape itself. Typically, the edge
potential map is compute from the image gradient, for example:
 \\\\[ g(I) = 1 / ( 1 + | (\\\\nabla * G)(I)| ) \\\\] \\\\[ g(I) = \\\\exp^{-|(\\\\nabla * G)(I)|} \\\\] where $ I $ is image intensity and $ (\\\\nabla * G) $ is the derivative of Gaussian operator.
See SegmentationLevelSetImageFilterand
SparseFieldLevelSetImageFilterfor more information on Inputs.
PARAMETERS
The PropagationScaling parameter can be used to switch from
propagation outwards (POSITIVE scaling parameter) versus propagating
inwards (NEGATIVE scaling parameter). This implementation allows the
user to set the weights between the propagation, advection and
curvature term using methods SetPropagationScaling(), SetAdvectionScaling(), SetCurvatureScaling(). In general, the larger the CurvatureScaling, the smoother the
resulting contour. To follow the implementation in Caselles et al
paper, set the PropagationScaling to $ c $ (the inflation or ballon force) and AdvectionScaling and
CurvatureScaling both to 1.0.
OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative
values in the output image represent the inside of the segmented
region and positive values in the image represent the outside of the
segmented region. The zero crossings of the image correspond to the
position of the propagating front.
See SparseFieldLevelSetImageFilterand
SegmentationLevelSetImageFilterfor more information.
REFERENCES
Geodesic Active Contours
, V. Caselles, R. Kimmel and G. Sapiro. International Journal on
Computer Vision, Vol 22, No. 1, pp 61-97, 1997

See:
SegmentationLevelSetImageFilter


GeodesicActiveContourLevelSetFunction


SparseFieldLevelSetImageFilter

 itk::simple::GeodesicActiveContourLevelSet for the procedural interface


C++ includes: sitkGeodesicActiveContourLevelSetImageFilter.h
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GeodesicActiveContourLevelSetImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetAdvectionScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetCurvatureScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetMaximumRMSError "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetPropagationScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::GetRMSChange "

The Root Mean Square of the levelset upon termination.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::ReverseExpansionDirectionOff "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::ReverseExpansionDirectionOn "

Set the value of ReverseExpansionDirection to true or false
respectfully.

";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetAdvectionScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetCurvatureScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetMaximumRMSError "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetPropagationScaling "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::SetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSetImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GradientAnisotropicDiffusionImageFilter "

This filter performs anisotropic diffusion on a scalar itk::Imageusing
the classic Perona-Malik, gradient magnitude based equation
implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed
information on anisotropic diffusion, see
itkAnisotropicDiffusionFunction and
itkGradientNDAnisotropicDiffusionFunction.


Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any
dimensionality. The output image will be a diffused copy of the input.
Parameters
Please see the description of parameters given in
itkAnisotropicDiffusionImageFilter.

See:
AnisotropicDiffusionImageFilter


AnisotropicDiffusionFunction


GradientAnisotropicDiffusionFunction

 itk::simple::GradientAnisotropicDiffusion for the procedural interface


C++ includes: sitkGradientAnisotropicDiffusionImageFilter.h
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::EstimateOptimalTimeStep "

This method autmatically sets the optimal timestep for an image given
its spacing.

";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GetConductanceParameter "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GetConductanceScalingUpdateInterval "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GetTimeStep "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::GradientAnisotropicDiffusionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::SetConductanceParameter "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::SetConductanceScalingUpdateInterval "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::SetTimeStep "
";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GradientImageFilter "

Computes the gradient of an image using directional derivatives.


Computes the gradient of an image using directional derivatives. The
directional derivative at each pixel location is computed by
convolution with a first-order derivative operator. The second
template parameter defines the value type used in the derivative
operator (defaults to float). The third template parameter defines the
value type used for output image (defaults to float). The output image
is defined as a covariant vector image whose value type is specified
as this third template parameter.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::Gradient for the procedural interface


C++ includes: sitkGradientImageFilter.h
";

%feature("docstring")  itk::simple::GradientImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GradientImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GradientImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GradientImageFilter::GetUseImageDirection "

End concept checking The UseImageDirection flag determines whether
image derivatives are computed with respect to the image grid or with
respect to the physical space. When this flag is ON the derivatives
are computed with respect to the coodinate system of physical space.
The difference is whether we take into account the image Direction or
not. The flag ON will take into account the image direction and will
result in an extra matrix multiplication compared to the amount of
computation performed when the flag is OFF. The default value of this
flag is On.

";

%feature("docstring")  itk::simple::GradientImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::GradientImageFilter::GradientImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GradientImageFilter::SetUseImageDirection "

End concept checking The UseImageDirection flag determines whether
image derivatives are computed with respect to the image grid or with
respect to the physical space. When this flag is ON the derivatives
are computed with respect to the coodinate system of physical space.
The difference is whether we take into account the image Direction or
not. The flag ON will take into account the image direction and will
result in an extra matrix multiplication compared to the amount of
computation performed when the flag is OFF. The default value of this
flag is On.

";

%feature("docstring")  itk::simple::GradientImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::GradientImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::GradientImageFilter::UseImageDirectionOff "
";

%feature("docstring")  itk::simple::GradientImageFilter::UseImageDirectionOn "

Set the value of UseImageDirection to true or false respectfully.

";

%feature("docstring")  itk::simple::GradientImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::GradientImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::GradientMagnitudeImageFilter "

Computes the gradient magnitude of an image region at each pixel.



See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Compute the gradient magnitude image

See:
 itk::simple::GradientMagnitude for the procedural interface


C++ includes: sitkGradientMagnitudeImageFilter.h
";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::GradientMagnitudeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::GradientMagnitudeImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter "

Computes the Magnitude of the Gradient of an image by convolution with
the first derivative of a Gaussian.


This filter is implemented using the recursive gaussian filtersWiki Examples:

All Examples

Find the gradient magnitude of the image first smoothed with a
Gaussian kernel

See:
 itk::simple::GradientMagnitudeRecursiveGaussian for the procedural interface


C++ includes: sitkGradientMagnitudeRecursiveGaussianImageFilter.h
";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GetSigma "

Set Sigma value. Sigma is measured in the units of image spacing.

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GradientMagnitudeRecursiveGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::NormalizeAcrossScaleOff "
";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::NormalizeAcrossScaleOn "

Set the value of NormalizeAcrossScale to true or false respectfully.

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::SetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::SetSigma "

Set Sigma value. Sigma is measured in the units of image spacing.

";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GradientRecursiveGaussianImageFilter "

Computes the gradient of an image by convolution with the first
derivative of a Gaussian.


This filter is implemented using the recursive gaussian filtersWiki Examples:

All Examples

Compute the gradient of an image by convolution with the first
derivative of a Gaussian

See:
 itk::simple::GradientRecursiveGaussian for the procedural interface


C++ includes: sitkGradientRecursiveGaussianImageFilter.h
";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::GetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::GetSigma "

Set Sigma value. Sigma is measured in the units of image spacing.

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::GetUseImageDirection "

The UseImageDirection flag determines whether the gradients are
computed with respect to the image grid or with respect to the
physical space. When this flag is ON the gradients are computed with
respect to the coodinate system of physical space. The difference is
whether we take into account the image Direction or not. The flag ON
will take into account the image direction and will result in an extra
matrix multiplication compared to the amount of computation performed
when the flag is OFF. The default value of this flag is On.

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::GradientRecursiveGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::NormalizeAcrossScaleOff "
";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::NormalizeAcrossScaleOn "

Set the value of NormalizeAcrossScale to true or false respectfully.

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::SetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::SetSigma "

Set Sigma value. Sigma is measured in the units of image spacing.

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::SetUseImageDirection "

The UseImageDirection flag determines whether the gradients are
computed with respect to the image grid or with respect to the
physical space. When this flag is ON the gradients are computed with
respect to the coodinate system of physical space. The difference is
whether we take into account the image Direction or not. The flag ON
will take into account the image direction and will result in an extra
matrix multiplication compared to the amount of computation performed
when the flag is OFF. The default value of this flag is On.

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::UseImageDirectionOff "
";

%feature("docstring")  itk::simple::GradientRecursiveGaussianImageFilter::UseImageDirectionOn "

Set the value of UseImageDirection to true or false respectfully.

";


%feature("docstring") itk::simple::GrayscaleConnectedClosingImageFilter "

Enhance pixels associated with a dark object (identified by a seed
pixel) where the dark object is surrounded by a brigher object.


GrayscaleConnectedClosingImagefilter is useful for enhancing dark
objects that are surrounded by bright borders. This filter makes it
easier to threshold the image and extract just the object of interest.
Geodesic morphology and the connected closing algorithm are described
in Chapter 6 of Pierre Soille's book \"Morphological Image Analysis:
Principles and Applications\", Second Edition, Springer, 2003.
See:
 GrayscaleGeodesicDilateImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::GrayscaleConnectedClosing for the procedural interface


C++ includes: sitkGrayscaleConnectedClosingImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::GetSeed "

Set/Get the seed pixel for the segmentation.

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::GrayscaleConnectedClosingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::SetSeed "

Set/Get the seed pixel for the segmentation.

";

%feature("docstring")  itk::simple::GrayscaleConnectedClosingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleConnectedOpeningImageFilter "

Enhance pixels associated with a bright object (identified by a seed
pixel) where the bright object is surrounded by a darker object.


GrayscaleConnectedOpeningImagefilter is useful for enhancing bright
objects that are surrounded by dark borders. This filter makes it
easier to threshold the image and extract just the object of interest.
Geodesic morphology and the connected opening algorithm is described
in Chapter 6 of Pierre Soille's book \"Morphological Image Analysis:
Principles and Applications\", Second Edition, Springer, 2003.
See:
 GrayscaleGeodesicDilateImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::GrayscaleConnectedOpening for the procedural interface


C++ includes: sitkGrayscaleConnectedOpeningImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::GetSeed "

Set/Get the seed pixel for the segmentation.

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::GrayscaleConnectedOpeningImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::SetSeed "

Set/Get the seed pixel for the segmentation.

";

%feature("docstring")  itk::simple::GrayscaleConnectedOpeningImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleDilateImageFilter "

gray scale dilation of an image


Dilate an image using grayscale morphology. Dilation takes the maximum
of all the pixels identified by the structuring element. The
structuring element is assumed to be composed of binary values (zero
or one). Only elements of the structuring element having values > 0
are candidates for affecting the center pixel.
See:
MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter
Wiki Examples:

All Examples

Dilate a grayscale image

See:
 itk::simple::GrayscaleDilate for the procedural interface


C++ includes: sitkGrayscaleDilateImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::GrayscaleDilateImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::GrayscaleDilateImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleErodeImageFilter "

gray scale dilation of an image


Erode an image using grayscale morphology. Dilation takes the maximum
of all the pixels identified by the structuring element. The
structuring element is assumed to be composed of binary values (zero
or one). Only elements of the structuring element having values > 0
are candidates for affecting the center pixel.
See:
MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter
Wiki Examples:

All Examples

Erode a grayscale image

See:
 itk::simple::GrayscaleErode for the procedural interface


C++ includes: sitkGrayscaleErodeImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::GrayscaleErodeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::GrayscaleErodeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleFillholeImageFilter "

Remove local minima not connected to the boundary of the image.


GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes
are local minima in the grayscale topography that are not connected to
boundaries of the image. Gray level values adjacent to a hole are
extrapolated across the hole. This filter is used to smooth over local
minima without affecting the values of local maxima. If you take the
difference between the output of this filter and the original image
(and perhaps threshold the difference above a small value), you'll
obtain a map of the local minima. This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the \"mask\" input to the geodesic
erosion. The \"marker\" image for the geodesic erosion is constructed
such that boundary pixels match the boundary pixels of the input image
and the interior pixels are set to the maximum pixel value in the
input image. Geodesic morphology and the Fillhole algorithm is
described in Chapter 6 of Pierre Soille's book \"Morphological Image
Analysis:  Principles and Applications\", Second Edition, Springer,
2003.
See:
 ReconstructionByErosionImageFilter


MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

 itk::simple::GrayscaleFillhole for the procedural interface


C++ includes: sitkGrayscaleFillholeImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::GrayscaleFillholeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleFillholeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter "

geodesic gray scale dilation of an image


Geodesic dilation operates on a \"marker\" image and a \"mask\" image.
The marker image is dilated using an elementary structuring element
(neighborhood of radius one using only the face connected neighbors).
The resulting image is then compared with the mask image. The output
image is the pixelwise minimum of the dilated marker image and the
mask image. Geodesic dilation is run either one iteration or until
convergence. In the convergence case, the filter is equivalent to
\"reconstruction by dilation\". This filter is implemented to handle
both scenarios. The one iteration case is multi-threaded. The
convergence case is delegated to another instance of the same filter
(but configured to run a single iteration). The marker image must be
less than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003. A noniterative version of this algorithm can
be found in the ReconstructionByDilationImageFilter. This noniterative solution is much faster than the implementation
provided here. All ITK filters that previously used
GrayscaleGeodesicDiliateImageFilter as part of their implementation
have been converted to use the ReconstructionByDilationImageFilter. The GrayscaleGeodesicDilateImageFilteris maintained for backward
compatibility.
See:
MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

 itk::simple::GrayscaleGeodesicDilate for the procedural interface


C++ includes: sitkGrayscaleGeodesicDilateImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::GetRunOneIteration "

Set/Get whether the filter should run one iteration or until
convergence. When run to convergence, this filter is equivalent to
\"reconstruction by dilation\". Default is off.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::GrayscaleGeodesicDilateImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::RunOneIterationOff "
";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::RunOneIterationOn "

Set the value of RunOneIteration to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::SetRunOneIteration "

Set/Get whether the filter should run one iteration or until
convergence. When run to convergence, this filter is equivalent to
\"reconstruction by dilation\". Default is off.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilateImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter "

geodesic gray scale erosion of an image


Geodesic erosion operates on a \"marker\" image and a \"mask\" image.
The marker image is eroded using an elementary structuring element
(neighborhood of radius one using only the face connected neighbors).
The resulting image is then compared with the mask image. The output
image is the pixelwise maximum of the eroded marker image and the mask
image. Geodesic erosion is run either one iteration or until
convergence. In the convergence case, the filter is equivalent to
\"reconstruction by erosion\". This filter is implemented to handle
both scenarios. The one iteration case is multi-threaded. The
convergence case is delegated to another instance of the same filter
(but configured to run a single iteration). The marker image must be
greater than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003. A noniterative version of this algorithm can
be found in the ReconstructionByErosionImageFilter. This noniterative solution is much faster than the implementation
provided here. All ITK filters that previously used
GrayscaleGeodesicErodeImageFilteras part of their implementation have
been converted to use the ReconstructionByErosionImageFilter. The GrayscaleGeodesicErodeImageFilteris maintained for backward
compatibility.
See:
MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

 itk::simple::GrayscaleGeodesicErode for the procedural interface


C++ includes: sitkGrayscaleGeodesicErodeImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::GetRunOneIteration "

Set/Get whether the filter should run one iteration or until
convergence. When run to convergence, this filter is equivalent to
\"reconstruction by erosion\". Default is off.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::GrayscaleGeodesicErodeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::RunOneIterationOff "
";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::RunOneIterationOn "

Set the value of RunOneIteration to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::SetRunOneIteration "

Set/Get whether the filter should run one iteration or until
convergence. When run to convergence, this filter is equivalent to
\"reconstruction by erosion\". Default is off.

";

%feature("docstring")  itk::simple::GrayscaleGeodesicErodeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleGrindPeakImageFilter "

Remove local maxima not connected to the boundary of the image.


GrayscaleGrindPeakImageFilterremoves peaks in a grayscale image. Peaks
are local maxima in the grayscale topography that are not connected to
boundaries of the image. Gray level values adjacent to a peak are
extrapolated through the peak. This filter is used to smooth over
local maxima without affecting the values of local minima. If you take
the difference between the output of this filter and the original
image (and perhaps threshold the difference above a small value),
you'll obtain a map of the local maxima. This filter uses the GrayscaleGeodesicDilateImageFilter. It provides its own input as the \"mask\" input to the geodesic
erosion. The \"marker\" image for the geodesic erosion is constructed
such that boundary pixels match the boundary pixels of the input image
and the interior pixels are set to the minimum pixel value in the
input image. This filter is the dual to the
GrayscaleFillholeImageFilterwhich implements the Fillhole algorithm.
Since it is a dual, it is somewhat superfluous but is provided as a
convenience. Geodesic morphology and the Fillhole algorithm is
described in Chapter 6 of Pierre Soille's book \"Morphological Image
Analysis:  Principles and Applications\", Second Edition, Springer,
2003.
See:
 GrayscaleGeodesicDilateImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::GrayscaleGrindPeak for the procedural interface


C++ includes: sitkGrayscaleGrindPeakImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::GrayscaleGrindPeakImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::GrayscaleGrindPeakImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleMorphologicalClosingImageFilter "

gray scale dilation of an image


Erode an image using grayscale morphology. Dilation takes the maximum
of all the pixels identified by the structuring element. The
structuring element is assumed to be composed of binary values (zero
or one). Only elements of the structuring element having values > 0
are candidates for affecting the center pixel.
See:
MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

 itk::simple::GrayscaleMorphologicalClosing for the procedural interface


C++ includes: sitkGrayscaleMorphologicalClosingImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::GetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::GrayscaleMorphologicalClosingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SafeBorderOff "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SafeBorderOn "

Set the value of SafeBorder to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::SetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GrayscaleMorphologicalOpeningImageFilter "

gray scale dilation of an image


Dilate an image using grayscale morphology. Dilation takes the maximum
of all the pixels identified by the structuring element. The
structuring element is assumed to be composed of binary values (zero
or one). Only elements of the structuring element having values > 0
are candidates for affecting the center pixel.
See:
MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::GrayscaleMorphologicalOpening for the procedural interface


C++ includes: sitkGrayscaleMorphologicalOpeningImageFilter.h
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::GetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::GrayscaleMorphologicalOpeningImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SafeBorderOff "
";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SafeBorderOn "

Set the value of SafeBorder to true or false respectfully.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::SetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpeningImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GreaterEqualImageFilter "


See:
 itk::simple::GreaterEqual for the procedural interface


C++ includes: sitkGreaterEqualImageFilter.h
";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::GreaterEqualImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterEqualImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GreaterImageFilter "


See:
 itk::simple::Greater for the procedural interface


C++ includes: sitkGreaterImageFilter.h
";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "
";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "
";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::GreaterImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::GreaterImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GreaterImageFilter::GreaterImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GreaterImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::GreaterImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::GridImageSource "


See:
 itk::simple::GridImageSource for the procedural interface


C++ includes: sitkGridImageSource.h
";

%feature("docstring")  itk::simple::GridImageSource::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::GridImageSource::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::GridImageSource::GetDirection "
";

%feature("docstring")  itk::simple::GridImageSource::GetGridOffset "
";

%feature("docstring")  itk::simple::GridImageSource::GetGridSpacing "
";

%feature("docstring")  itk::simple::GridImageSource::GetName "

Name of this class

";

%feature("docstring")  itk::simple::GridImageSource::GetOrigin "
";

%feature("docstring")  itk::simple::GridImageSource::GetOutputPixelType "
";

%feature("docstring")  itk::simple::GridImageSource::GetScale "
";

%feature("docstring")  itk::simple::GridImageSource::GetSigma "
";

%feature("docstring")  itk::simple::GridImageSource::GetSize "
";

%feature("docstring")  itk::simple::GridImageSource::GetSpacing "
";

%feature("docstring")  itk::simple::GridImageSource::GridImageSource "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::GridImageSource::SetDirection "
";

%feature("docstring")  itk::simple::GridImageSource::SetGridOffset "
";

%feature("docstring")  itk::simple::GridImageSource::SetGridSpacing "
";

%feature("docstring")  itk::simple::GridImageSource::SetOrigin "
";

%feature("docstring")  itk::simple::GridImageSource::SetOutputPixelType "
";

%feature("docstring")  itk::simple::GridImageSource::SetScale "
";

%feature("docstring")  itk::simple::GridImageSource::SetSigma "
";

%feature("docstring")  itk::simple::GridImageSource::SetSize "
";

%feature("docstring")  itk::simple::GridImageSource::SetSpacing "
";

%feature("docstring")  itk::simple::GridImageSource::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HConcaveImageFilter "

Identify local minima whose depth below the baseline is greater than
h.


HConcaveImageFilterextract local minima that are more than h intensity
units below the (local) background. This has the effect of extracting
objects that are darker than the background by at least h intensity
units. This filter uses the HMinimaImageFilter. Geodesic morphology and the H-Convex algorithm is described in
Chapter 6 of Pierre Soille's book \"Morphological Image Analysis:
Principles and Applications\", Second Edition, Springer, 2003.
See:
 GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::HConcave for the procedural interface


C++ includes: sitkHConcaveImageFilter.h
";

%feature("docstring")  itk::simple::HConcaveImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HConcaveImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HConcaveImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::HConcaveImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::HConcaveImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HConcaveImageFilter::GetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HConcaveImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HConcaveImageFilter::HConcaveImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HConcaveImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HConcaveImageFilter::SetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HConcaveImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HConvexImageFilter "

Identify local maxima whose height above the baseline is greater than
h.


HConvexImageFilterextract local maxima that are more than h intensity
units above the (local) background. This has the effect of extracting
objects that are brighter than background by at least h intensity
units. This filter uses the HMaximaImageFilter. Geodesic morphology and the H-Convex algorithm is described in
Chapter 6 of Pierre Soille's book \"Morphological Image Analysis:
Principles and Applications\", Second Edition, Springer, 2003.
See:
 GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::HConvex for the procedural interface


C++ includes: sitkHConvexImageFilter.h
";

%feature("docstring")  itk::simple::HConvexImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HConvexImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HConvexImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::HConvexImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::HConvexImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HConvexImageFilter::GetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HConvexImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HConvexImageFilter::HConvexImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HConvexImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HConvexImageFilter::SetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HConvexImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HMaximaImageFilter "

Suppress local maxima whose height above the baseline is less than h.


HMaximaImageFiltersuppresses local maxima that are less than h
intensity units above the (local) background. This has the effect of
smoothing over the \"high\" parts of the noise in the image without
smoothing over large changes in intensity (region boundaries). See the
HMinimaImageFilterto suppress the local minima whose depth is less
than h intensity units below the (local) background. If the output of
HMaximaImageFilteris subtracted from the original image, the signicant
\"peaks\" in the image can be identified. This is what the
HConvexImageFilterprovides. This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the \"mask\" input to the geodesic
dilation. The \"marker\" image for the geodesic dilation is the input
image minus the height parameter h. Geodesic morphology and the
H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book
\"Morphological Image Analysis:  Principles and Applications\", Second
Edition, Springer, 2003. The height parameter is set using SetHeight.
See:
 ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::HMaxima for the procedural interface


C++ includes: sitkHMaximaImageFilter.h
";

%feature("docstring")  itk::simple::HMaximaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HMaximaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HMaximaImageFilter::GetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HMaximaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HMaximaImageFilter::HMaximaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HMaximaImageFilter::SetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HMaximaImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HMinimaImageFilter "

Suppress local minima whose depth below the baseline is less than h.


HMinimaImageFiltersuppresses local minima that are less than h
intensity units below the (local) background. This has the effect of
smoothing over the \"low\" parts of the noise in the image without
smoothing over large changes in intensity (region boundaries). See the
HMaximaImageFilterto suppress the local maxima whose height is less
than h intensity units above the (local) background. If original image
is subtracted from the output of HMinimaImageFilter, the signicant \"valleys\" in the image can be identified. This is
what the HConcaveImageFilterprovides. This filter uses the GrayscaleGeodesicErodeImageFilter. It provides its own input as the \"mask\" input to the geodesic
dilation. The \"marker\" image for the geodesic dilation is the input
image plus the height parameter h. Geodesic morphology and the
H-Minima algorithm is described in Chapter 6 of Pierre Soille's book
\"Morphological Image Analysis:  Principles and Applications\", Second
Edition, Springer, 2003.
See:
 GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter


MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::HMinima for the procedural interface


C++ includes: sitkHMinimaImageFilter.h
";

%feature("docstring")  itk::simple::HMinimaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HMinimaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HMinimaImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::HMinimaImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::HMinimaImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HMinimaImageFilter::GetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HMinimaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HMinimaImageFilter::HMinimaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HMinimaImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::HMinimaImageFilter::SetHeight "

Set/Get the height that a local maximum must be above the local
background (local contrast) in order to survive the processing. Local
maxima below this value are replaced with an estimate of the local
background.

";

%feature("docstring")  itk::simple::HMinimaImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HalfHermitianToRealInverseFFTImageFilter "

Base class for specialized complex-to-real inverse Fast Fourier Transform.


This is a base class for the \"inverse\" or \"reverse\" Discrete
Fourier Transform. This is an abstract base class: the actual implementation is
provided by the best child class available on the system when the
object is created via the object factory system. The input to this
filter is assumed to have the same format as the output of the RealToHalfHermitianForwardFFTImageFilter. That is, the input is assumed to consist of roughly half the full
complex image resulting from a real-to-complex discrete Fourier
transform. This half is expected to be the first half of the image in
the X-dimension. Because this filter assumes that the input stores
only about half of the non-redundant complex pixels, the output is
larger in the X-dimension than it is in the input. To determine the
actual size of the output image, this filter needs additional
information in the form of a flag indicating whether the output image
has an odd size in the X-dimension. Use SetActualXDimensionIsOdd()to set this flag.
See:
 ForwardFFTImageFilter, HalfHermitianToRealInverseFFTImageFilter

 itk::simple::HalfHermitianToRealInverseFFT for the procedural interface


C++ includes: sitkHalfHermitianToRealInverseFFTImageFilter.h
";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::ActualXDimensionIsOddOff "
";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::ActualXDimensionIsOddOn "

Set the value of ActualXDimensionIsOdd to true or false respectfully.

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::GetActualXDimensionIsOdd "

Was the original truncated dimension size odd?

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::HalfHermitianToRealInverseFFTImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::SetActualXDimensionIsOdd "

Was the original truncated dimension size odd?

";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFTImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HashImageFilter "

Compute the sha1 or md5 hash of an image.



See:
 itk::simple::Hash for the procedural interface


C++ includes: sitkHashImageFilter.h
";

%feature("docstring")  itk::simple::HashImageFilter::Execute "
";

%feature("docstring")  itk::simple::HashImageFilter::GetHashFunction "
";

%feature("docstring")  itk::simple::HashImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HashImageFilter::HashImageFilter "
";

%feature("docstring")  itk::simple::HashImageFilter::SetHashFunction "
";

%feature("docstring")  itk::simple::HashImageFilter::ToString "
";


%feature("docstring") itk::simple::HausdorffDistanceImageFilter "

Computes the Hausdorff distance between the set of non-zero pixels of
two images.


HausdorffDistanceImageFiltercomputes the distance between the set non-
zero pixels of two images using the following formula: \\\\[ H(A,B) = \\\\max(h(A,B),h(B,A)) \\\\] where \\\\[ h(A,B) = \\\\max_{a \\\\in A} \\\\min_{b \\\\in B} \\\\| a -
b\\\\| \\\\] is the directed Hausdorff distance and $A$ and $B$ are respectively the set of non-zero pixels in the first and second
input images. In particular, this filter uses the
DirectedHausdorffImageFilter inside to compute the two directed
distances and then select the largest of the two. The Hausdorff
distance measures the degree of mismatch between two sets and behaves
like a metric over the set of all closed bounded sets - with
properties of identity, symmetry and triangle inequality. This filter
requires the largest possible region of the first image and the same
corresponding region in the second image. It behaves as filter with
two inputs and one output. Thus it can be inserted in a pipeline with
other filters. The filter passes the first input through unmodified.
This filter is templated over the two input image types. It assume
both images have the same number of dimensions.
See:
DirectedHausdorffDistanceImageFilter

 itk::simple::HausdorffDistance for the procedural interface


C++ includes: sitkHausdorffDistanceImageFilter.h
";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::GetAverageHausdorffDistance "

*


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::GetHausdorffDistance "

*


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::HausdorffDistanceImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HausdorffDistanceImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HistogramMatchingImageFilter "

Normalize the grayscale values between two images by histogram
matching.


HistogramMatchingImageFilternormalizes the grayscale values of a
source image based on the grayscale values of a reference image. This
filter uses a histogram matching technique where the histograms of the
two images are matched only at a specified number of quantile values.
This filter was originally designed to normalize MR images of the same
MR protocol and same body part. The algorithm works best if background
pixels are excluded from both the source and reference histograms. A simple background exclusion method is to exclude all pixels whose grayscale
values are smaller than the mean grayscale value. ThresholdAtMeanIntensityOn()switches on this simple background exclusion method. The source image can be set via either
SetInput()or SetSourceImage(). The reference image can be set via
SetReferenceImage(). SetNumberOfHistogramLevels()sets the number of bins used when creating histograms of the source
and reference images. SetNumberOfMatchPoints()governs the number of quantile values to be matched. This filter
assumes that both the source and reference are of the same type and
that the input and output image type have the same number of dimension
and have scalar pixel types.REFERENCE
Laszlo G. Nyul, Jayaram K. Udupa, and Xuan Zhang, \"New Variants of a
Method  of MRI Scale Standardization\", IEEE Transactions on Medical
Imaging, 19(2):143-150, 2000.

See:
 itk::simple::HistogramMatching for the procedural interface


C++ includes: sitkHistogramMatchingImageFilter.h
";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::GetNumberOfHistogramLevels "

Set/Get the number of histogram levels used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::GetNumberOfMatchPoints "

Set/Get the number of match points used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::GetThresholdAtMeanIntensity "

Set/Get the threshold at mean intensity flag. If true, only source
(reference) pixels which are greater than the mean source (reference)
intensity is used in the histogram matching. If false, all pixels are
used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::HistogramMatchingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::SetNumberOfHistogramLevels "

Set/Get the number of histogram levels used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::SetNumberOfMatchPoints "

Set/Get the number of match points used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::SetThresholdAtMeanIntensity "

Set/Get the threshold at mean intensity flag. If true, only source
(reference) pixels which are greater than the mean source (reference)
intensity is used in the histogram matching. If false, all pixels are
used.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::ThresholdAtMeanIntensityOff "
";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::ThresholdAtMeanIntensityOn "

Set the value of ThresholdAtMeanIntensity to true or false
respectfully.

";

%feature("docstring")  itk::simple::HistogramMatchingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::HuangThresholdImageFilter "

Threshold an image using the Huang Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the HuangThresholdCalculatorand applies that theshold
to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::HuangThreshold for the procedural interface


C++ includes: sitkHuangThresholdImageFilter.h
";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::HuangThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value. The default value
NumericTraits<OutputPixelType>::max().

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins. Defaults is 128.

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::HuangThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::Image "

The main Image class for SimpleITK.

C++ includes: sitkImage.h
";

%feature("docstring")  itk::simple::Image::CopyInformation "

Copy common meta-data from an image to this one.


Copies the Origin, Spacing, and Direction from the source image to
this image.

It is required for the source Image's dimension and size to match,
this image's attributes, otherwise an exception will be generated.

";

%feature("docstring")  itk::simple::Image::GetDepth "
";

%feature("docstring")  itk::simple::Image::GetDimension "
";

%feature("docstring")  itk::simple::Image::GetDirection "

Set/Get the Direction.


Internally, the Direction is represented by a matrix 2x2 for a 2D and
and 3x3 for a 3D image. The matrix is passed as a 1D array in row-
major form.

";

%feature("docstring")  itk::simple::Image::GetHeight "
";

%feature("docstring")  itk::simple::Image::GetNumberOfComponentsPerPixel "

Get the number of components for each pixel.


For scalar images this methods returns 1. For vector images the number
of components for each pixel is returned.

";

%feature("docstring")  itk::simple::Image::GetOrigin "

Get/Set the Origin

";

%feature("docstring")  itk::simple::Image::GetPixelID "
";

%feature("docstring")  itk::simple::Image::GetPixelIDTypeAsString "
";

%feature("docstring")  itk::simple::Image::GetPixelIDValue "
";

%feature("docstring")  itk::simple::Image::GetSize "
";

%feature("docstring")  itk::simple::Image::GetSpacing "

Get the Spacing

";

%feature("docstring")  itk::simple::Image::GetWidth "
";

%feature("docstring")  itk::simple::Image::Image "
";

%feature("docstring")  itk::simple::Image::Image "

Default constructor, creates an image of size 0.

";

%feature("docstring")  itk::simple::Image::SetDirection "
";

%feature("docstring")  itk::simple::Image::SetOrigin "
";

%feature("docstring")  itk::simple::Image::SetSpacing "
";

%feature("docstring")  itk::simple::Image::ToString "
";

%feature("docstring")  itk::simple::Image::TransformIndexToPhysicalPoint "

 Transform index to physical point

";

%feature("docstring")  itk::simple::Image::TransformPhysicalPointToIndex "

 Transform physical point to index

";

%feature("docstring")  itk::simple::Image::~Image "
";


%feature("docstring") itk::simple::ImageFileReader "

Read a 2D or 3D image and return a smart pointer to a SimpleITK image.


This reader handles scalar and vector images and returns an image with
the same type as the file on disk.


See:
 itk::simple::ReadImage for the procedural interface


C++ includes: sitkImageFileReader.h
";

%feature("docstring")  itk::simple::ImageFileReader::Execute "
";

%feature("docstring")  itk::simple::ImageFileReader::GetFileName "
";

%feature("docstring")  itk::simple::ImageFileReader::ImageFileReader "
";

%feature("docstring")  itk::simple::ImageFileReader::SetFileName "
";


%feature("docstring") itk::simple::ImageFileWriter "

Write out a SimpleITK image to the specified file location.


This writer tries to write the image out using the image's type to the
location specified in FileName. If writing fails, an ITK exception is
thrown.


See:
 itk::simple::WriteImage for the procedural interface


C++ includes: sitkImageFileWriter.h
";

%feature("docstring")  itk::simple::ImageFileWriter::Execute "
";

%feature("docstring")  itk::simple::ImageFileWriter::Execute "
";

%feature("docstring")  itk::simple::ImageFileWriter::GetFileName "
";

%feature("docstring")  itk::simple::ImageFileWriter::ImageFileWriter "
";

%feature("docstring")  itk::simple::ImageFileWriter::SetFileName "
";


%feature("docstring") itk::simple::ImageFilter "

The base interface for SimpleITK filters that take one input image.


All SimpleITK filters which take one input image should inherit from
this class

C++ includes: sitkImageFilter.h
";

%feature("docstring")  itk::simple::ImageFilter::GetName "

return user readable name fo the filter

";

%feature("docstring")  itk::simple::ImageFilter::ImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ImageFilter::ToString "
";

%feature("docstring")  itk::simple::ImageFilter::~ImageFilter "

Default Destructor

";


%feature("docstring") itk::simple::ImageReaderBase "

An abract base class for image readers.

C++ includes: sitkImageReaderBase.h
";


%feature("docstring") itk::simple::ImageSeriesReader "

Read series of image into a SimpleITK image.



See:
 itk::simple::ReadImage for the procedural interface


C++ includes: sitkImageSeriesReader.h
";

%feature("docstring")  itk::simple::ImageSeriesReader::Execute "
";

%feature("docstring")  itk::simple::ImageSeriesReader::GetFileNames "
";

%feature("docstring")  itk::simple::ImageSeriesReader::ImageSeriesReader "
";

%feature("docstring")  itk::simple::ImageSeriesReader::SetFileNames "
";


%feature("docstring") itk::simple::ImportImageFilter "

Compose a 2D or 3D image and return a smart pointer to a SimpleITK
image.


This filter is intended to interface SimpleITK to other image
processing libraries and applications that may have their own
representation of an image class.


See:
 itk::simple::ImportAsInt8, itk::simple::ImportAsUInt8, itk::simple::ImportAsInt16, itk::simple::ImportAsUInt16, itk::simple::ImportAsInt32, itk::simple::ImportAsUInt32, itk::simple::ImportAsInt64, itk::simple::ImportAsUInt64, itk::simple::ImportAsFloat, itk::simple::ImportAsDouble for the procedural interfaces.


C++ includes: sitkImportImageFilter.h
";

%feature("docstring")  itk::simple::ImportImageFilter::Execute "
";

%feature("docstring")  itk::simple::ImportImageFilter::GetDirection "
";

%feature("docstring")  itk::simple::ImportImageFilter::GetOrigin "
";

%feature("docstring")  itk::simple::ImportImageFilter::GetSize "
";

%feature("docstring")  itk::simple::ImportImageFilter::GetSpacing "
";

%feature("docstring")  itk::simple::ImportImageFilter::ImportImageFilter "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsDouble "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsFloat "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsInt16 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsInt32 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsInt8 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsUInt16 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsUInt32 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetBufferAsUInt8 "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetDirection "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetOrigin "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetSize "
";

%feature("docstring")  itk::simple::ImportImageFilter::SetSpacing "
";

%feature("docstring")  itk::simple::ImportImageFilter::ToString "
";


%feature("docstring") itk::simple::IntensityWindowingImageFilter "

Applies a linear transformation to the intensity levels of the input
Imagethat are inside a user-defined interval. Values below this
interval are mapped to a constant. Values over the interval are mapped
to another constant.


IntensityWindowingImageFilterapplies pixel-wise a linear
transformation to the intensity values of input image pixels. The
linear transformation is defined by the user in terms of the minimum
and maximum values that the output image should have and the lower and
upper limits of the intensity window of the input image. This
operation is very common in visualization, and can also be applied as
a convenient preprocessing operation for image segmentation. All
computations are performed in the precison of the input pixel's
RealType. Before assigning the computed value to the output pixel.Wiki Examples:

All Examples

 IntensityWindowingImageFilter
See:
 RescaleIntensityImageFilter

 itk::simple::IntensityWindowing for the procedural interface



C++ includes: sitkIntensityWindowingImageFilter.h
";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::GetOutputMaximum "

Set/Get the values of the maximum and minimum intensities of the
outputimage.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::GetOutputMinimum "

Set/Get the values of the maximum and minimum intensities of the
outputimage.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::GetWindowMaximum "

Set/Get the values of the maximum and minimum intensities of the input
intensity window.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::GetWindowMinimum "

Set/Get the values of the maximum and minimum intensities of the input
intensity window.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::IntensityWindowingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::SetOutputMaximum "

Set/Get the values of the maximum and minimum intensities of the
outputimage.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::SetOutputMinimum "

Set/Get the values of the maximum and minimum intensities of the
outputimage.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::SetWindowMaximum "

Set/Get the values of the maximum and minimum intensities of the input
intensity window.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::SetWindowMinimum "

Set/Get the values of the maximum and minimum intensities of the input
intensity window.

";

%feature("docstring")  itk::simple::IntensityWindowingImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::IntermodesThresholdImageFilter "

Threshold an image using the Intermodes Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the IntermodesThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::IntermodesThreshold for the procedural interface


C++ includes: sitkIntermodesThresholdImageFilter.h
";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::IntermodesThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::IntermodesThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::InverseDeconvolutionImageFilter "

The direct linear inverse deconvolution filter.


The inverse filter is the most straightforward deconvolution method.
Considering that convolution of two images in the spatial domain is
equivalent to multiplying the Fourier transform of the two images, the
inverse filter consists of inverting the multiplication. In other
words, this filter computes the following: \\\\[ hat{F}(\\\\omega) = \\\\begin{cases} G(\\\\omega) / H(\\\\omega)
& \\\\text{if \\\\f$|H(\\\\omega)| \\\\geq \\\\epsilon\\\\f$} \\\\\\\\
0 & \\\\text{otherwise} \\\\end{cases} \\\\] where $\\\\hat{F}(\\\\omega)$ is the Fourier transform of the estimate produced by this filter, $G(\\\\omega)$ is the Fourier transform of the input blurred image, $H(\\\\omega)$ is the Fourier transform of the blurring kernel, and $\\\\epsilon$ is a constant real non-negative threshold (called
KernelZeroMagnitudeThreshold in this filter) that determines when the
magnitude of a complex number is considered zero.
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Cory Quammen, The University of North
Carolina at Chapel Hill

See:
 itk::simple::InverseDeconvolution for the procedural interface


C++ includes: sitkInverseDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::GetKernelZeroMagnitudeThreshold "

Set/get the threshold value uused to determine whether a frequency of
the Fourier transform of the blurring kernel is considered to be zero.
Default value is 1.0e-4.

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::InverseDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::SetKernelZeroMagnitudeThreshold "

Set/get the threshold value uused to determine whether a frequency of
the Fourier transform of the blurring kernel is considered to be zero.
Default value is 1.0e-4.

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::InverseDeconvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::InverseFFTImageFilter "

Base class for inverse Fast Fourier Transform.


This is a base class for the \"inverse\" or \"reverse\" Discrete
Fourier Transform. This is an abstract base class: the actual implementation is
provided by the best child available on the system when the object is
created via the object factory system. This class transforms a full
complex image with Hermitian symmetry into its real spatial domain
representation. If the input does not have Hermitian symmetry, the
imaginary component is discarded.
See:
 ForwardFFTImageFilter, InverseFFTImageFilter

 itk::simple::InverseFFT for the procedural interface


C++ includes: sitkInverseFFTImageFilter.h
";

%feature("docstring")  itk::simple::InverseFFTImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::InverseFFTImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::InverseFFTImageFilter::InverseFFTImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::InverseFFTImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::InvertIntensityImageFilter "

Invert the intensity of an image.


InvertIntensityImageFilterinverts intensity of pixels by subtracting
pixel value to a maximum value. The maximum value can be set with
SetMaximum and defaults the maximum of input pixel type. This filter
can be used to invert, for example, a binary image, a distance map,
etc.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 IntensityWindowingImageFilter ShiftScaleImageFilter
Wiki Examples:

All Examples

Invert an image

See:
 itk::simple::InvertIntensity for the procedural interface


C++ includes: sitkInvertIntensityImageFilter.h
";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::GetMaximum "
";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::InvertIntensityImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::SetMaximum "
";

%feature("docstring")  itk::simple::InvertIntensityImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::IsoContourDistanceImageFilter "

Compute an approximate distance from an interpolated isocontour to the
close grid points.


For standard level set algorithms, it is useful to periodically
reinitialize the evolving image to prevent numerical accuracy problems
in computing derivatives. This reinitialization is done by computing a
signed distance map to the current level set. This class provides the
first step in this reinitialization by computing an estimate of the
distance from the interpolated isocontour to the pixels (or voxels)
that are close to it, i.e. for which the isocontour crosses a segment
between them and one of their direct neighbors. This class supports
narrowbanding. If the input narrowband is provided, the algorithm will
only locate the level set within the input narrowband. Implementation
of this class is based on Fast and Accurate Redistancing for Level Set
Methods `Krissian K. and Westin C.F.', EUROCAST NeuroImaging Workshop
Las Palmas Spain, Ninth International Conference on Computer Aided
Systems Theory , pages 48-51, Feb 2003.


See:
 itk::simple::IsoContourDistance for the procedural interface


C++ includes: sitkIsoContourDistanceImageFilter.h
";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::GetFarValue "

Set/Get the value of the level set to be located. The default value is
0.

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::GetLevelSetValue "

Set/Get the value of the level set to be located. The default value is
0.

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::IsoContourDistanceImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::SetFarValue "

Set/Get the value of the level set to be located. The default value is
0.

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::SetLevelSetValue "

Set/Get the value of the level set to be located. The default value is
0.

";

%feature("docstring")  itk::simple::IsoContourDistanceImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::IsoDataThresholdImageFilter "

Threshold an image using the IsoData Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the IsoDataThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::IsoDataThreshold for the procedural interface


C++ includes: sitkIsoDataThresholdImageFilter.h
";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::IsoDataThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::IsoDataThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::IsolatedConnectedImageFilter "

Label pixels that are connected to one set of seeds but not another.


IsolatedConnectedImageFilterfinds the optimal threshold to separate
two regions. It has two modes, one to separate dark regions surrounded
by bright regions by automatically finding a minimum isolating upper
threshold, and another to separate bright regions surrounded by dark
regions by automatically finding a maximum lower isolating threshold.
The mode can be chosen by setting FindUpperThresholdOn()/Off(). In both cases, the isolating threshold is retrieved with GetIsolatedValue(). The algorithm labels pixels with ReplaceValue that are connected to
Seeds1 AND NOT connected to Seeds2. When finding the threshold to
separate two dark regions surrounded by bright regions, given a fixed
lower threshold, the filter adjusts the upper threshold until the two
sets of seeds are not connected. The algorithm uses a binary search to
adjust the upper threshold, starting at Upper. The reverse is true for
finding the threshold to separate two bright regions. Lower defaults
to the smallest possible value for the InputImagePixelType, and Upper
defaults to the largest possible value for the InputImagePixelType.
The user can also supply the Lower and Upper values to restrict the
search. However, if the range is too restrictive, it could happen that
no isolating threshold can be found between the user specified Lower
and Upper values. Therefore, unless the user is sure of the bounds to
set, it is recommended that the user set these values to the lowest
and highest intensity values in the image, respectively. The user can
specify more than one seed for both regions to separate. The algorithm
will try find the threshold that ensures that all of the first seeds
are contained in the resulting segmentation and all of the second
seeds are not contained in the segmentation. It is possible that the
algorithm may not be able to find the isolating threshold because no
such threshold exists. The user can check for this by querying the GetThresholdingFailed()flag.


See:
 itk::simple::IsolatedConnected for the procedural interface


C++ includes: sitkIsolatedConnectedImageFilter.h
";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::FindUpperThresholdOff "
";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::FindUpperThresholdOn "

Set the value of FindUpperThreshold to true or false respectfully.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetFindUpperThreshold "

Set/Get whether to find an upper threshold (separating two dark
regions) or a lower threshold (separating two bright regions).

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetIsolatedValue "

This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetIsolatedValueTolerance "

Set/Get the precision required for the intensity threshold value. The
default is 1.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetLower "

Set/Get the limit on the lower threshold value. The default is the
NonpositiveMin() for the InputPixelType.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie within
the thresholds will be replaced with this value. The default is 1.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetSeed1 "
";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetSeed2 "
";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetThresholdingFailed "

This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::GetUpper "

Set/Get the limit on the upper threshold value. The default is the
max() for the InputPixelType.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::IsolatedConnectedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetFindUpperThreshold "

Set/Get whether to find an upper threshold (separating two dark
regions) or a lower threshold (separating two bright regions).

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetIsolatedValueTolerance "

Set/Get the precision required for the intensity threshold value. The
default is 1.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetLower "

Set/Get the limit on the lower threshold value. The default is the
NonpositiveMin() for the InputPixelType.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie within
the thresholds will be replaced with this value. The default is 1.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetSeed1 "

Set seed point 1. This seed will be isolated from Seed2 (if possible).
All pixels connected to this seed will be replaced with ReplaceValue.
This method is deprecated, please use AddSeed().

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetSeed2 "

Set seed point 2. This seed will be isolated from Seed1 (if possible).
This method is deprecated, please use AddSeed().

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::SetUpper "

Set/Get the limit on the upper threshold value. The default is the
max() for the InputPixelType.

";

%feature("docstring")  itk::simple::IsolatedConnectedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::IsolatedWatershedImageFilter "

Isolate watershed basins using two seeds.


IsolatedWatershedImageFilterlabels pixels with ReplaceValue1 that are
in the same watershed basin as Seed1 AND NOT the same as Seed2. The
filter adjusts the waterlevel until the two seeds are not in different
basins. The user supplies a Watershed threshold. The algorithm uses a
binary search to adjust the upper waterlevel, starting at
UpperValueLimit. UpperValueLimit defaults to the 1.0.


See:
 itk::simple::IsolatedWatershed for the procedural interface


C++ includes: sitkIsolatedWatershedImageFilter.h
";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetIsolatedValueTolerance "

Set/Get the precision required for the intensity threshold value. The
default is .001.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetReplaceValue1 "

Set/Get value to replace Seed1(Seed2) pixels, pixels that are within
the basin that contains Seed1(Seed2) this value. The default is 1(0).

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetReplaceValue2 "

Set/Get value to replace Seed1(Seed2) pixels, pixels that are within
the basin that contains Seed1(Seed2) this value. The default is 1(0).

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetSeed1 "
";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetSeed2 "
";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetThreshold "

Set/Get the Watershed threshold. The default is 0.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::GetUpperValueLimit "

Set/Get the limit on the upper waterlevel value. The default is 1.0.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::IsolatedWatershedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetIsolatedValueTolerance "

Set/Get the precision required for the intensity threshold value. The
default is .001.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetReplaceValue1 "

Set/Get value to replace Seed1(Seed2) pixels, pixels that are within
the basin that contains Seed1(Seed2) this value. The default is 1(0).

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetReplaceValue2 "

Set/Get value to replace Seed1(Seed2) pixels, pixels that are within
the basin that contains Seed1(Seed2) this value. The default is 1(0).

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetSeed1 "

Set seed point 1. This seed will be isolated from Seed2 (if possible).
All pixels connected to this seed will be replaced with ReplaceValue1.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetSeed2 "

Set seed point 2. This seed will be isolated from Seed1 (if possible).
All pixels connected to this seed will be replaced with ReplaceValue2.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetThreshold "

Set/Get the Watershed threshold. The default is 0.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::SetUpperValueLimit "

Set/Get the limit on the upper waterlevel value. The default is 1.0.

";

%feature("docstring")  itk::simple::IsolatedWatershedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::JoinSeriesImageFilter "

Join N-D images into an (N+1)-D image.


This filter is templated over the input image type and the output
image type. The pixel type of them must be the same and the input
dimension must be less than the output dimension. When the input
images are N-dimensinal, they are joined in order and the size of the
N+1'th dimension of the output is same as the number of the inputs.
The spacing and the origin (where the first input is placed) for the
N+1'th dimension is specified in this filter. The output image
informations for the first N dimensions are taken from the first
input. Note that all the inputs should have the same information.
Hideaki Hiraki Contributed in the users
listhttp://public.kitware.com/pipermail/insight-
users/2004-February/006542.html

See:
 itk::simple::JoinSeries for the procedural interface


C++ includes: sitkJoinSeriesImageFilter.h
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "
";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::GetOrigin "

Set/Get origin of the new dimension.

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::GetSpacing "

Set/Get spacing of the new dimension.

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::JoinSeriesImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::SetOrigin "

Set/Get origin of the new dimension.

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::SetSpacing "

Set/Get spacing of the new dimension.

";

%feature("docstring")  itk::simple::JoinSeriesImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::KittlerIllingworthThresholdImageFilter "

Threshold an image using the KittlerIllingworth Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the KittlerIllingworthThresholdCalculatorand applies
that theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::KittlerIllingworthThreshold for the procedural interface


C++ includes: sitkKittlerIllingworthThresholdImageFilter.h
";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::KittlerIllingworthThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::KittlerIllingworthThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelContourImageFilter "

Labels the pixels on the border of the objects in a labeled image.


LabelContourImageFiltertakes a labeled image as input, where the
pixels in the objects are the pixels with a value different of the
BackgroundValue. Only the pixels on the contours of the objects are
kept. The pixels not on the border are changed to BackgroundValue. The
labels of the object are the same in the input and in the output
image. The connectivity can be changed to minimum or maximum
connectivity with SetFullyConnected(). Full connectivity produces thicker contours.http://hdl.handle.net/1926/1352
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 BinaryContourImageFilter
Wiki Examples:

All Examples

Label the contours of connected components

See:
 itk::simple::LabelContour for the procedural interface


C++ includes: sitkLabelContourImageFilter.h
";

%feature("docstring")  itk::simple::LabelContourImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LabelContourImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LabelContourImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::LabelContourImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::LabelContourImageFilter::GetBackgroundValue "

Set/Get the background value used to identify the objects and mark the
pixels not on the border of the objects.

";

%feature("docstring")  itk::simple::LabelContourImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff.



For objects that are 1 pixel wide, use FullyConnectedOn.


";

%feature("docstring")  itk::simple::LabelContourImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelContourImageFilter::LabelContourImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelContourImageFilter::SetBackgroundValue "

Set/Get the background value used to identify the objects and mark the
pixels not on the border of the objects.

";

%feature("docstring")  itk::simple::LabelContourImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff.



For objects that are 1 pixel wide, use FullyConnectedOn.


";

%feature("docstring")  itk::simple::LabelContourImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapContourOverlayImageFilter "

Apply a colormap to the contours (outlines) of each object in a label
map and superimpose it on top of the feature image.


The feature image is typically the image from which the labeling was
produced. Use the SetInput function to set the LabelMap, and the
SetFeatureImage function to set the feature image. Apply a colormap to
a label map and put it on top of the input image. The set of colors is
a good selection of distinct colors. The opacity of the label map can
be defined by the user. A background label produce a gray pixel with
the same intensity than the input one.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter, LabelMapOverlayImageFilter
Wiki Examples:

All Examples

Color the boundaries of labeled regions in an image

See:
 itk::simple::LabelMapContourOverlay for the procedural interface


C++ includes: sitkLabelMapContourOverlayImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetContourThickness "

Set/Get the contour thickness - 1 by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetContourType "

Set/Get the overlay type - CONTOUR is used by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetDilationRadius "

Set/Get the object dilation radius - 0 by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetPriority "

Set/Get the object priority - HIGH_LABEL_ON_TOP by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::GetSliceDimension "

Set/Get the slice dimension - defaults to image dimension - 1.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::LabelMapContourOverlayImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetContourThickness "

Set/Get the contour thickness - 1 by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetContourType "

Set/Get the overlay type - CONTOUR is used by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetDilationRadius "

Set/Get the object dilation radius - 0 by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetPriority "

Set/Get the object priority - HIGH_LABEL_ON_TOP by default.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::SetSliceDimension "

Set/Get the slice dimension - defaults to image dimension - 1.

";

%feature("docstring")  itk::simple::LabelMapContourOverlayImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapMaskImageFilter "

Mask and image with a LabelMap.


LabelMapMaskImageFiltermask the content of an input image according to
the content of the input LabelMap. The masked pixel of the input image
are set to the BackgroundValue. LabelMapMaskImageFiltercan keep the
input image for one label only, with Negated = false (the default) or
it can mask the input image for a single label, when Negated equals
true. In Both cases, the label is set with SetLabel().
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

 itk::simple::LabelMapMask for the procedural interface


C++ includes: sitkLabelMapMaskImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::GetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::Zero.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::GetLabel "

The label to mask or to not mask, depending on the value of the
Negated ivar.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::GetNegated "

Set/Get whether the Label should be masked or not.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::LabelMapMaskImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::NegatedOff "
";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::NegatedOn "

Set the value of Negated to true or false respectfully.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::SetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::Zero.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::SetLabel "

The label to mask or to not mask, depending on the value of the
Negated ivar.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::SetNegated "

Set/Get whether the Label should be masked or not.

";

%feature("docstring")  itk::simple::LabelMapMaskImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapOverlayImageFilter "

Apply a colormap to a label map and superimpose it on an image.


Apply a colormap to a label map and put it on top of the feature
image. The feature image is typically the image from which the
labeling was produced. Use the SetInput function to set the LabelMap,
and the SetFeatureImage function to set the feature image. The set of
colors is a good selection of distinct colors. The opacity of the
label map can be defined by the user. A background label produce a
gray pixel with the same intensity than the input one.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 LabelMapToBinaryImageFilter, LabelMapToLabelImageFilter

 itk::simple::LabelMapOverlay for the procedural interface


C++ includes: sitkLabelMapOverlayImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::GetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::LabelMapOverlayImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::SetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelMapOverlayImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapToBinaryImageFilter "

Convert a LabelMapto a binary image.


LabelMapToBinaryImageFilterto a binary image. All the objects in the
image are used as foreground. The background values of the original
binary image can be restored by passing this image to the filter with
the SetBackgroundImage()method. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 LabelMapToLabelImageFilter, LabelMapMaskImageFilter

 itk::simple::LabelMapToBinary for the procedural interface


C++ includes: sitkLabelMapToBinaryImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::GetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::GetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::LabelMapToBinaryImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::SetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::SetForegroundValue "

Set/Get the value used as \"foreground\" in the output image. Defaults
to NumericTraits<PixelType>::max().

";

%feature("docstring")  itk::simple::LabelMapToBinaryImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapToLabelImageFilter "

Converts a LabelMapto a labeled image.


LabelMapToBinaryImageFilterto a label image.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 LabelMapToBinaryImageFilter, LabelMapMaskImageFilter
Wiki Examples:

All Examples

Convert a LabelMap to a normal image with different values
representing each region

See:
 itk::simple::LabelMapToLabel for the procedural interface


C++ includes: sitkLabelMapToLabelImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapToLabelImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LabelMapToLabelImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapToLabelImageFilter::LabelMapToLabelImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapToLabelImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelMapToRGBImageFilter "

Convert a LabelMapto a colored image.



Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This implementation was taken from the
Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www
.insight-journal.org/browse/publication/176

See:
 LabelMapToBinaryImageFilter, LabelMapMaskImageFilter

 itk::simple::LabelMapToRGB for the procedural interface


C++ includes: sitkLabelMapToRGBImageFilter.h
";

%feature("docstring")  itk::simple::LabelMapToRGBImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LabelMapToRGBImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelMapToRGBImageFilter::LabelMapToRGBImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelMapToRGBImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelOverlayImageFilter "

Apply a colormap to a label image and put it on top of the input
image.


Apply a colormap to a label image and put it on top of the input
image. The set of colors is a good selection of distinct colors. The
opacity of the label image can be defined by the user. The user can
also choose if the want to use a background and which label value is
the background. A background label produce a gray pixel with the same
intensity than the input one.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. This class was contributed to the Insight
Journalhttp://hdl.handle.net/1926/172

See:
ScalarToRGBPixelFunctor LabelToRGBImageFilter
Wiki Examples:

All Examples

Overlay a LabelMap on an image

See:
 itk::simple::LabelOverlay for the procedural interface


C++ includes: sitkLabelOverlayImageFilter.h
";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::GetBackgroundValue "

Set/Get the background value.

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::GetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::LabelOverlayImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::SetBackgroundValue "

Set/Get the background value.

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::SetOpacity "

Set/Get the opacity of the colored label image. The value must be
between 0 and 1.

";

%feature("docstring")  itk::simple::LabelOverlayImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LabelStatisticsImageFilter "

Compute min, max, variance, and mean of an image.



See:
 itk::simple::LabelStatistics for the procedural interface


C++ includes: sitkLabelStatisticsImageFilter.h
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::Execute "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetCount "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetLabelStatisticsMap "

Return the entire statistics map

";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetMaximum "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetMean "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetMeasurementMap "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetMedian "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetMinimum "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetSigma "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetSum "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetValidLabels "

A convenience function to return a dense list of valid labels found in
the label image

";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::GetVariance "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::HasLabel "
";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::LabelStatisticsImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelStatisticsImageFilter::ToString "
";


%feature("docstring") itk::simple::LabelToRGBImageFilter "

Apply a colormap to a label image.


Apply a colormap to a label image. The set of colors is a good
selection of distinct colors. The user can choose to use a background
value. In that case, a gray pixel with the same intensity than the
background label is produced. This code was contributed in the Insight
Journal paper: \"The watershed transform in ITK - discussion and new
developments\" by Beare R., Lehmann
G.http://hdl.handle.net/1926/202http://www.insight-
journal.org/browse/publication/92
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. Richard Beare. Department of Medicine,
Monash University, Melbourne, Australia.

See:
ScalarToRGBPixelFunctor LabelOverlayImageFilter

 itk::simple::LabelToRGB for the procedural interface


C++ includes: sitkLabelToRGBImageFilter.h
";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::GetBackgroundValue "

Set/Get the background value.

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::LabelToRGBImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::SetBackgroundValue "

Set/Get the background value.

";

%feature("docstring")  itk::simple::LabelToRGBImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LandweberDeconvolutionImageFilter "

Deconvolve an image using the Landweber deconvolution algorithm.


This filter implements the Landweber deconvolution algorthm as defined
in Bertero M and Boccacci P, \"Introduction to Inverse  Problems in
Imaging\", 1998. The algorithm assumes that the input image has been
formed by a linear shift-invariant system with a known kernel. The
Landweber algorithm converges to a solution that minimizes the sum of
squared errors $||f \\\\otimes h - g||$ where $f$ is the estimate of the unblurred image, $\\\\otimes$ is the convolution operator, $h$ is the blurring kernel, and $g$ is the blurred input image. As such, it is best suited for images
that have zero-mean Gaussian white noise. This is the base
implementation of the Landweber algorithm. It may produce results with
negative values. For a version of this algorithm that enforces a
positivity constraint on each intermediate solution, see ProjectedLandweberDeconvolutionImageFilter. This code was adapted from the Insight Journal contribution:
\"Deconvolution: infrastructure and reference algorithms\" by Gaetan
Lehmannhttp://hdl.handle.net/10380/3207
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Cory Quammen, The University of North
Carolina at Chapel Hill

See:
IterativeDeconvolutionImageFilter


 RichardsonLucyDeconvolutionImageFilter


 ProjectedLandweberDeconvolutionImageFilter

 itk::simple::LandweberDeconvolution for the procedural interface


C++ includes: sitkLandweberDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetAlpha "

Set/get relaxation factor.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetNumberOfIterations "

Get the number of iterations.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::LandweberDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::SetAlpha "

Set/get relaxation factor.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::SetNumberOfIterations "

Set the number of iterations.

";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::LandweberDeconvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LaplacianImageFilter "

This filter computes the Laplacian of a scalar-valued image. The
Laplacian is an isotropic measure of the 2nd spatial derivative of an
image. The Laplacian of an image highlights regions of rapid intensity
change and is therefore often used for edge detection. Often, the
Laplacian is applied to an image that has first been smoothed with a
Gaussian filter in order to reduce its sensitivity to noise.


The Laplacian at each pixel location is computed by convolution with
the itk::LaplacianOperator.
Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary
dimension. The output is a scalar-valued itk::Image.

WARNING:
The pixel type of the input and output images must be of real type
(float or double). ConceptChecking is used here to enforce the input
pixel type. You will get a compilation error if the pixel type of the
input and output images is not float or double.

See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator


LaplacianOperator
Wiki Examples:

All Examples

Compute the Laplacian of an image

See:
 itk::simple::Laplacian for the procedural interface


C++ includes: sitkLaplacianImageFilter.h
";

%feature("docstring")  itk::simple::LaplacianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LaplacianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LaplacianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LaplacianImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::LaplacianImageFilter::LaplacianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LaplacianImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::LaplacianImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::LaplacianImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::LaplacianImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter "

Computes the Laplacian of Gaussian (LoG) of an image.


Computes the Laplacian of Gaussian (LoG) of an image by convolution
with the second derivative of a Gaussian. This filter is implemented
using the recursive gaussian filters.Wiki Examples:

All Examples

Compute the Laplacian of Gaussian (LoG) of an image

See:
 itk::simple::LaplacianRecursiveGaussian for the procedural interface


C++ includes: sitkLaplacianRecursiveGaussianImageFilter.h
";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::GetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::GetSigma "
";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::LaplacianRecursiveGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::NormalizeAcrossScaleOff "
";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::NormalizeAcrossScaleOn "

Set the value of NormalizeAcrossScale to true or false respectfully.

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::SetNormalizeAcrossScale "

Define which normalization factor will be used for the Gaussian.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::SetSigma "

Set Sigma value. Sigma is measured in the units of image spacing.

";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LaplacianSegmentationLevelSetImageFilter "

Segments structures in images based on a second derivative image
features.


IMPORTANT
The SegmentationLevelSetImageFilterclass and the
LaplacianSegmentationLevelSetFunctionclass contain additional
information necessary to the full understanding of how to use this
filter.
OVERVIEW
This class is a level set method segmentation filter. It constructs a
speed function which is zero at image edges as detected by a Laplacian
filter. The evolving level set front will therefore tend to lock onto
zero crossings in the image. The level set front moves fastest near
edges.
The Laplacian segmentation filter is intended primarily as a tool for
refining existing segmentations. The initial isosurface (as given in
the seed input image) should ideally be very close to the segmentation
boundary of interest. The idea is that a rough segmentation can be
refined by allowing the isosurface to deform slightly to achieve a
better fit to the edge features of an image. One example of such an
application is to refine the output of a hand segmented image.
Because values in the Laplacian feature image will tend to be low
except near edge features, this filter is not effective for segmenting
large image regions from small seed surfaces.
INPUTS
This filter requires two inputs. The first input is a seed image. This
seed image must contain an isosurface that you want to use as the seed
for your segmentation. It can be a binary, graylevel, or floating
point image. The only requirement is that it contain a closed
isosurface that you will identify as the seed by setting the
IsosurfaceValue parameter of the filter. For a binary image you will
want to set your isosurface value halfway between your on and off
values (i.e. for 0's and 1's, use an isosurface value of 0.5).
The second input is the feature image. This is the image from which
the speed function will be calculated. For most applications, this is
the image that you want to segment. The desired isosurface in your
seed image should lie within the region of your feature image that you
are trying to segment.
Note that this filter does no preprocessing of the feature image
before thresholding. Because second derivative calculations are highly
sensitive to noise, isotropic or anisotropic smoothing of the feature
image can dramatically improve the results.
See SegmentationLevelSetImageFilterfor more information on Inputs.
OUTPUTS
The filter outputs a single, scalar, real-valued image. Positive
*values in the output image are inside the segmentated region and
negative *values in the image are outside of the inside region. The
zero crossings of *the image correspond to the position of the level
set front.
See SparseFieldLevelSetImageFilterand
SegmentationLevelSetImageFilterfor more information.
PARAMETERS
This filter has no parameters other than those described in
SegmentationLevelSetImageFilter.

See:
SegmentationLevelSetImageFilter


LaplacianSegmentationLevelSetFunction,


SparseFieldLevelSetImageFilter

 itk::simple::LaplacianSegmentationLevelSet for the procedural interface


C++ includes: sitkLaplacianSegmentationLevelSetImageFilter.h
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetCurvatureScaling "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetMaximumRMSError "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetPropagationScaling "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::GetRMSChange "

The Root Mean Square of the levelset upon termination.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::LaplacianSegmentationLevelSetImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::ReverseExpansionDirectionOff "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::ReverseExpansionDirectionOn "

Set the value of ReverseExpansionDirection to true or false
respectfully.

";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::SetCurvatureScaling "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::SetMaximumRMSError "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::SetPropagationScaling "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::SetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSetImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LaplacianSharpeningImageFilter "

This filter sharpens an image using a Laplacian. LaplacianSharpening
highlights regions of rapid intensity change and therefore highlights
or enhances the edges. The result is an image that appears more in
focus.


The LaplacianSharpening at each pixel location is computed by
convolution with the itk::LaplacianOperator.
Inputs and Outputs
The input to this filter is a scalar-valued itk::Imageof arbitrary
dimension. The output is a scalar-valued itk::Image.

See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator


LaplacianOperator
Wiki Examples:

All Examples

Sharpen an image

See:
 itk::simple::LaplacianSharpening for the procedural interface


C++ includes: sitkLaplacianSharpeningImageFilter.h
";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::GetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::LaplacianSharpeningImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::SetUseImageSpacing "

Set/Get whether or not the filter will use the spacing of the input
image in its calculations.

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::LaplacianSharpeningImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::LessEqualImageFilter "


See:
 itk::simple::LessEqual for the procedural interface


C++ includes: sitkLessEqualImageFilter.h
";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LessEqualImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LessEqualImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::LessEqualImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::LessEqualImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LessEqualImageFilter::LessEqualImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LessEqualImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::LessEqualImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::LessEqualImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LessImageFilter "


See:
 itk::simple::Less for the procedural interface


C++ includes: sitkLessImageFilter.h
";

%feature("docstring")  itk::simple::LessImageFilter::Execute "
";

%feature("docstring")  itk::simple::LessImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::LessImageFilter::Execute "
";

%feature("docstring")  itk::simple::LessImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::LessImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::LessImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::LessImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::LessImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::LessImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LessImageFilter::LessImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LessImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::LessImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::LessImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LiThresholdImageFilter "

Threshold an image using the Li Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the LiThresholdCalculatorand applies that theshold to
the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::LiThreshold for the procedural interface


C++ includes: sitkLiThresholdImageFilter.h
";

%feature("docstring")  itk::simple::LiThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::LiThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::LiThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::LiThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::Log10ImageFilter "

Computes the log10 of each pixel.


The computation is performed using vcl_log10(x).


See:
 itk::simple::Log10 for the procedural interface


C++ includes: sitkLog10ImageFilter.h
";

%feature("docstring")  itk::simple::Log10ImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::Log10ImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::Log10ImageFilter::Log10ImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::Log10ImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::LogImageFilter "

Computes the log() of each pixel.



See:
 itk::simple::Log for the procedural interface


C++ includes: sitkLogImageFilter.h
";

%feature("docstring")  itk::simple::LogImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::LogImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::LogImageFilter::LogImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::LogImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MagnitudeAndPhaseToComplexImageFilter "

Implements pixel-wise conversion of magnitude and phase data into
complex voxels.


This filter is parametrized over the types of the two input images and
the type of the output image. The filter expect all images to have the
same dimension (e.g. all 2D, or all 3D, or all ND)


See:
 itk::simple::MagnitudeAndPhaseToComplex for the procedural interface


C++ includes: sitkMagnitudeAndPhaseToComplexImageFilter.h
";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::Execute "
";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::MagnitudeAndPhaseToComplexImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplexImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaskImageFilter "

Mask an image with a mask. image with the mask.


This class is templated over the types of the input image type, the
mask image type and the type of the output image. Numeric conversions
(castings) are done by the C++ defaults. The pixel type of the input 2
image must have a valid definition of the operator != with zero. This
condition is required because internally this filter will perform the
operation ifpixel_from_mask_image!=0pixel_output_image=pixel_input_ima
geelsepixel_output_image=outside_value The pixel from the input 1 is
cast to the pixel type of the output image. Note that the input and
the mask images must be of the same size.
WARNING:
Any pixel value other than 0 will not be masked out.

See:
 MaskNegatedImageFilter
Wiki Examples:

All Examples

Apply a mask to an image

See:
 itk::simple::Mask for the procedural interface


C++ includes: sitkMaskImageFilter.h
";

%feature("docstring")  itk::simple::MaskImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::MaskImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MaskImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaskImageFilter::GetOutsideValue "
";

%feature("docstring")  itk::simple::MaskImageFilter::MaskImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaskImageFilter::SetOutsideValue "

Method to explicitly set the outside value of the mask. Defaults to 0.

";

%feature("docstring")  itk::simple::MaskImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaskNegatedImageFilter "

Mask an image with the negative of a mask.


This class is templated over the types of the input image type, the
mask image type and the type of the output image. Numeric conversions
(castings) are done by the C++ defaults. The pixel type of the input 2
image must have a valid definition of the operator != with zero. This
condition is required because internally this filter will perform the
operation ifpixel_from_mask_image!=0pixel_output_image=output_valueels
epixel_output_image=pixel_input_image The pixel from the input 1 is
cast to the pixel type of the output image. Note that the input and
the mask images must be of the same size.
WARNING:
Any pixel value other than 0 will not be masked out.

See:
 MaskImageFilter
Wiki Examples:

All Examples

Apply the inverse of a mask to an image

See:
 itk::simple::MaskNegated for the procedural interface


C++ includes: sitkMaskNegatedImageFilter.h
";

%feature("docstring")  itk::simple::MaskNegatedImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MaskNegatedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaskNegatedImageFilter::MaskNegatedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaskNegatedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaskedFFTNormalizedCorrelationImageFilter "

Calculate masked normalized cross correlation using FFTs.


This filter calculates the masked normalized cross correlation (NCC)
of two images under masks using FFTs instead of spatial correlation.
It is much faster than spatial correlation for reasonably large
structuring elements. This filter is not equivalent to simply masking
the images first and then correlating them; the latter approach yields
incorrect results because the zeros in the images still affect the
metric in the correlation process. This filter implements the masked
NCC correctly so that the masked-out regions are completely ignored.
The fundamental difference is described in detail in the references below. If the masks are set to images of all ones,
the result of this filter is the same as standard NCC. Inputs: Two
images are required as inputs, fixedImage and movingImage, and two are
optional, fixedMask and movingMask. In the context of correlation,
inputs are often defined as: \"image\" and \"template\". In this
filter, the fixedImage plays the role of the image, and the
movingImage plays the role of the template. However, this filter is
capable of correlating any two images and is not restricted to small
movingImages (templates). In the fixedMask and movingMask, non-zero
positive values indicate locations of useful information in the
corresponding image, whereas zero and negative values indicate
locations that should be masked out (ignored). Internally, the masks
are converted to have values of only 0 and 1. For each optional mask
that is not set, the filter internally creates an image of ones, which
is equivalent to not masking the image. Thus, if both masks are not
set, the result will be equivalent to unmasked NCC. For example, if
only a mask for the fixed image is needed, the movingMask can either
not be set or can be set to an image of ones. Optional parameters: The
RequiredNumberOfOverlappingPixels enables the user to specify how many
voxels of the two images must overlap; any location in the correlation
map that results from fewer than this number of voxels will be set to
zero. Larger values zero-out pixels on a larger border around the
correlation image. Thus, larger values remove less stable computations
but also limit the capture range. If RequiredNumberOfOverlappingPixels
is set to 0, the default, no zeroing will take place. Imagesize:
fixedImage and movingImage need not be the same size, but fixedMask
must be the same size as fixedImage, and movingMask must be the same
size as movingImage. Furthermore, whereas some algorithms require that
the \"template\" be smaller than the \"image\" because of errors in
the regions where the two are not fully overlapping, this filter has
no such restriction. Imagespacing: Since the computations are done in
the pixel domain, all input images must have the same spacing.
Outputs; The output is an image of RealPixelType that is the masked
NCC of the two images and its values range from -1.0 to 1.0. The size
of this NCC image is, by definition, size(fixedImage) +
size(movingImage) - 1. Example filter usage:typedef
itk::MaskedFFTNormalizedCorrelationImageFilter< ShortImageType,
DoubleImageType >FilterType;FilterType::Pointerfilter=FilterTypeNew();
filter->SetFixedImage(fixedImage);filter->SetMovingImage(movingImage);
filter->SetFixedImageMask(fixedMask);filter->SetMovingImageMask(moving
Mask);filter->SetRequiredNumberOfOverlappingPixels(20);filter->Update(
);
WARNING:
The pixel type of the output image must be of real type (float or
double). ConceptChecking is used to enforce the output pixel type. You
will get a compilation error if the pixel type of the output image is
not float or double. References: 1) D. Padfield. \"Masked object
registration in the Fourier domain.\" Transactions on ImageProcessing.
2) D. Padfield. \"Masked FFT registration\". In Proc. Computer Vision
and Pattern Recognition, 2010.

: Dirk Padfield, GE Global Research,padfield@research.ge.com

See:
 itk::simple::MaskedFFTNormalizedCorrelation for the procedural interface


C++ includes: sitkMaskedFFTNormalizedCorrelationImageFilter.h
";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::GetRequiredNumberOfOverlappingPixels "

Set and get the required percentage of overlapping pixels.

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::MaskedFFTNormalizedCorrelationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::SetRequiredNumberOfOverlappingPixels "

Set and get the required percentage of overlapping pixels.

";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelationImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaximumEntropyThresholdImageFilter "

Threshold an image using the MaximumEntropy Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the MaximumEntropyThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::MaximumEntropyThreshold for the procedural interface


C++ includes: sitkMaximumEntropyThresholdImageFilter.h
";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::MaximumEntropyThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::MaximumEntropyThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaximumImageFilter "

Implements a pixel-wise operator Max(a,b) between two images.


The pixel values of the output image are the maximum between the
corresponding pixels of the two input images. This class is templated
over the types of the two input images and the type of the output
image. Numeric conversions (castings) are done by the C++ defaults.Wiki Examples:

All Examples

Pixel wise compare two input images and set the output pixel to their
max

See:
 itk::simple::Maximum for the procedural interface


C++ includes: sitkMaximumImageFilter.h
";

%feature("docstring")  itk::simple::MaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::MaximumImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::MaximumImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MaximumImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaximumImageFilter::MaximumImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaximumImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MaximumProjectionImageFilter "

Maximum projection.


this class was contributed to the insight journal by Gaetan Lehmann.
the original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la reproduction, inra
de jouy-en-josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MeanProjectionImageFilter


 MinimumProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter


 BinaryProjectionImageFilter

 itk::simple::MaximumProjection for the procedural interface


C++ includes: sitkMaximumProjectionImageFilter.h
";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::MaximumProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::MaximumProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MeanImageFilter "

Applies an averaging filter to an image.


Computes an image where a given pixel is the mean value of the the
pixels in a neighborhood about the corresponding input pixel. A mean
filter is one of the family of linear filters.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Mean filter an image

See:
 itk::simple::Mean for the procedural interface


C++ includes: sitkMeanImageFilter.h
";

%feature("docstring")  itk::simple::MeanImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MeanImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MeanImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MeanImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::MeanImageFilter::MeanImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MeanImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::MeanImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::MeanImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MeanProjectionImageFilter "

Mean projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
The original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MinimumProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter


 BinaryProjectionImageFilter


 MaximumProjectionImageFilter

 itk::simple::MeanProjection for the procedural interface


C++ includes: sitkMeanProjectionImageFilter.h
";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::MeanProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::MeanProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MeasurementMap "

A generic class that simply holds key value pairs intended primarily
for holding measurements It is a thin wrapper around an
std::map<std::string,double> that adds some convenience functions.

C++ includes: sitkMeasurementMap.h
";

%feature("docstring")  itk::simple::MeasurementMap::GetBasicMeasurementMap "
";

%feature("docstring")  itk::simple::MeasurementMap::GetVectorOfMeasurementNames "
";

%feature("docstring")  itk::simple::MeasurementMap::GetVectorOfMeasurementValues "
";

%feature("docstring")  itk::simple::MeasurementMap::MeasurementMap "
";

%feature("docstring")  itk::simple::MeasurementMap::ToStream "
";

%feature("docstring")  itk::simple::MeasurementMap::ToString "
";


%feature("docstring") itk::simple::MedianImageFilter "

Applies a median filter to an image.


Computes an image where a given pixel is the median value of the the
pixels in a neighborhood about the corresponding input pixel. A median
filter is one of the family of nonlinear filters. It is used to smooth
an image without being biased by outliers or shot noise. This filter
requires that the input pixel type provides an operator<() (LessThan
Comparable).
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Median filter an image

Median filter an RGB image

See:
 itk::simple::Median for the procedural interface


C++ includes: sitkMedianImageFilter.h
";

%feature("docstring")  itk::simple::MedianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MedianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MedianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MedianImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::MedianImageFilter::MedianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MedianImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::MedianImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::MedianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MedianProjectionImageFilter "

Median projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
The original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter


 BinaryProjectionImageFilter


 MaximumProjectionImageFilter


 MinimumProjectionImageFilter


 MeanProjectionImageFilter

 itk::simple::MedianProjection for the procedural interface


C++ includes: sitkMedianProjectionImageFilter.h
";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::MedianProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::MedianProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MinMaxCurvatureFlowImageFilter "

Denoise an image using min/max curvature flow.


MinMaxCurvatureFlowImageFilterimplements a curvature driven image
denoising algorithm. Iso-brightness contours in the grayscale input
image are viewed as a level set. The level set is then evolved using a
curvature-based speed function: \\\\[ I_t = F_{\\\\mbox{minmax}} |\\\\nabla I| \\\\] where $ F_{\\\\mbox{minmax}} = \\\\max(\\\\kappa,0) $ if $ \\\\mbox{Avg}_{\\\\mbox{stencil}}(x) $ is less than or equal to $ T_{thresold} $ and $ \\\\min(\\\\kappa,0) $ , otherwise. $ \\\\kappa $ is the mean curvature of the iso-brightness contour at point $ x $ . In min/max curvature flow, movement is turned on or off depending
on the scale of the noise one wants to remove. Switching depends on
the average image value of a region of radius $ R $ around each point. The choice of $ R $ , the stencil radius, governs the scale of the noise to be removed.
The threshold value $ T_{threshold} $ is the average intensity obtained in the direction perpendicular to
the gradient at point $ x $ at the extrema of the local neighborhood. This filter make use of the
multi-threaded finite difference solver hierarchy. Updates are
computed using a MinMaxCurvatureFlowFunctionobject. A zero flux
Neumann boundary condition is used when computing derivatives near the
data boundary.
WARNING:
This filter assumes that the input and output types have the same
dimensions. This filter also requires that the output image pixels are
of a real type. This filter works for any dimensional images, however
for dimensions greater than 3D, an expensive brute-force search is
used to compute the local threshold. Reference: \"Level Set Methods
and Fast Marching Methods\", J.A. Sethian, Cambridge Press, Chapter
16, Second edition, 1999.

See:
MinMaxCurvatureFlowFunction


 CurvatureFlowImageFilter


 BinaryMinMaxCurvatureFlowImageFilter

 itk::simple::MinMaxCurvatureFlow for the procedural interface


C++ includes: sitkMinMaxCurvatureFlowImageFilter.h
";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::GetStencilRadius "

Set/Get the stencil radius.

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::GetTimeStep "
";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::MinMaxCurvatureFlowImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::SetStencilRadius "

Set/Get the stencil radius.

";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::SetTimeStep "
";

%feature("docstring")  itk::simple::MinMaxCurvatureFlowImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MinimumImageFilter "

Implements a pixel-wise operator Min(a,b) between two images.


The pixel values of the output image are the minimum between the
corresponding pixels of the two input images. This class is templated
over the types of the two input images and the type of the output
image. Numeric conversions (castings) are done by the C++ defaults.Wiki Examples:

All Examples

Pixel wise compare two input images and set the output pixel to their
min

See:
 itk::simple::Minimum for the procedural interface


C++ includes: sitkMinimumImageFilter.h
";

%feature("docstring")  itk::simple::MinimumImageFilter::Execute "
";

%feature("docstring")  itk::simple::MinimumImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::MinimumImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MinimumImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MinimumImageFilter::MinimumImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MinimumImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MinimumMaximumImageFilter "

Computes the minimum and the maximum intensity values of an image.


It is templated over input image type only. This filter just copies
the input image through this output to be included within the
pipeline. The implementation uses the StatisticsImageFilter.
See:
 StatisticsImageFilter

 itk::simple::MinimumMaximum for the procedural interface


C++ includes: sitkMinimumMaximumImageFilter.h
";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::GetMaximum "

The maximum value in the image.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::GetMinimum "

The minimum value in the image.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::MinimumMaximumImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MinimumMaximumImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MinimumProjectionImageFilter "

Minimum projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
The original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 StandardDeviationProjectionImageFilter


 SumProjectionImageFilter


 BinaryProjectionImageFilter


 MaximumProjectionImageFilter


 MeanProjectionImageFilter

 itk::simple::MinimumProjection for the procedural interface


C++ includes: sitkMinimumProjectionImageFilter.h
";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::MinimumProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::MinimumProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MirrorPadImageFilter "

Increase the image size by padding with replicants of the input image
value.


MirrorPadImageFilterchanges the image bounds of an image. Any added
pixels are filled in with a mirrored replica of the input image. For
instance, if the output image needs a pixel that istwo pixels to the
left of the LargestPossibleRegionof the input image, the value
assigned will be from the pixeltwo pixels inside the left boundary of
the LargestPossibleRegion. The image bounds of the output must be
specified. Visual explanation of padding regions.This filter is
implemented as a multithreaded filter. It provides a
ThreadedGenerateData()method for its implementation.
See:
 WrapPadImageFilter, ConstantPadImageFilter
Wiki Examples:

All Examples

Pad an image using mirroring over the boundaries

See:
 itk::simple::MirrorPad for the procedural interface


C++ includes: sitkMirrorPadImageFilter.h
";

%feature("docstring")  itk::simple::MirrorPadImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MirrorPadImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MirrorPadImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MirrorPadImageFilter::GetPadLowerBound "
";

%feature("docstring")  itk::simple::MirrorPadImageFilter::GetPadUpperBound "
";

%feature("docstring")  itk::simple::MirrorPadImageFilter::MirrorPadImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MirrorPadImageFilter::SetPadLowerBound "
";

%feature("docstring")  itk::simple::MirrorPadImageFilter::SetPadUpperBound "
";

%feature("docstring")  itk::simple::MirrorPadImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ModulusImageFilter "

Computes the modulus (x % y) pixel-wise.


The input pixel type must support the c++ modulus operator (%).
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 itk::simple::Modulus for the procedural interface


C++ includes: sitkModulusImageFilter.h
";

%feature("docstring")  itk::simple::ModulusImageFilter::Execute "
";

%feature("docstring")  itk::simple::ModulusImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::ModulusImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ModulusImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ModulusImageFilter::ModulusImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ModulusImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MomentsThresholdImageFilter "

Threshold an image using the Moments Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the MomentsThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::MomentsThreshold for the procedural interface


C++ includes: sitkMomentsThresholdImageFilter.h
";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::MomentsThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::MomentsThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MorphologicalGradientImageFilter "

gray scale dilation of an image


Dilate an image using grayscale morphology. Dilation takes the maximum
of all the pixels identified by the structuring element. The
structuring element is assumed to be composed of binary values (zero
or one). Only elements of the structuring element having values > 0
are candidates for affecting the center pixel.
See:
MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

 itk::simple::MorphologicalGradient for the procedural interface


C++ includes: sitkMorphologicalGradientImageFilter.h
";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::MorphologicalGradientImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::MorphologicalGradientImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MorphologicalWatershedFromMarkersImageFilter "

Morphological watershed transform from markers.


The watershed transform is a tool for image segmentation that is fast
and flexible and potentially fairly parameter free. It was originally
derived from a geophysical model of rain falling on a terrain and a
variety of more formal definitions have been devised to allow
development of practical algorithms. If an image is considered as a
terrain and divided into catchment basins then the hope is that each
catchment basin would contain an object of interest. The output is a
label image. A label image, sometimes referred to as a categorical
image, has unique values for each region. For example, if a watershed
produces 2 regions, all pixels belonging to one region would have
value A, and all belonging to the other might have value B. Unassigned
pixels, such as watershed lines, might have the background value (0 by
convention). The simplest way of using the watershed is to preprocess
the image we want to segment so that the boundaries of our objects are
bright (e.g apply an edge detector) and compute the watershed
transform of the edge image. Watershed lines will correspond to the
boundaries and our problem will be solved. This is rarely useful in
practice because there are always more regional minima than there are
objects, either due to noise or natural variations in the object
surfaces. Therefore, while many watershed lines do lie on significant
boundaries, there are many that don't. Various methods can be used to
reduce the number of minima in the image, like thresholding the
smallest values, filtering the minima and/or smoothing the image. This
filter use another approach to avoid the problem of over segmentation:
it let the user provide a marker image which mark the minima in the
input image and give them a label. The minima are imposed in the input
image by the markers. The labels of the output image are the label of
the marker image. The morphological watershed transform algorithm is
described in Chapter 9.2 of Pierre Soille's book \"Morphological Image
Analysis:  Principles and Applications\", Second Edition, Springer,
2003. This code was contributed in the Insight Journal paper: \"The
watershed transform in ITK - discussion and new developments\" by
Beare R., Lehmann G.http://hdl.handle.net/1926/202http://www.insight-
journal.org/browse/publication/92
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France. Richard Beare. Department of Medicine,
Monash University, Melbourne, Australia.

See:
WatershedImageFilter, MorphologicalWatershedImageFilter

 itk::simple::MorphologicalWatershedFromMarkers for the procedural interface


C++ includes: sitkMorphologicalWatershedFromMarkersImageFilter.h
";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::GetMarkWatershedLine "

Set/Get whether the watershed pixel must be marked or not. Default is
true. Set it to false do not only avoid writing watershed pixels, it
also decrease algorithm complexity.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::MarkWatershedLineOff "
";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::MarkWatershedLineOn "

Set the value of MarkWatershedLine to true or false respectfully.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::MorphologicalWatershedFromMarkersImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::SetMarkWatershedLine "

Set/Get whether the watershed pixel must be marked or not. Default is
true. Set it to false do not only avoid writing watershed pixels, it
also decrease algorithm complexity.

";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkersImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MorphologicalWatershedImageFilter "

TODO.


TODO Watershed pixel are labeled 0. TOutputImage should be an integer
type. Labels of output image are in no particular order. You can
reorder the labels such that object labels are consecutive and sorted
based on object size by passing the output of this filter to a RelabelComponentImageFilter. The morphological watershed transform algorithm is described in
Chapter 9.2 of Pierre Soille's book \"Morphological Image Analysis:
Principles and Applications\", Second Edition, Springer, 2003. This
code was contributed in the Insight Journal paper: \"The watershed
transform in ITK - discussion and new developments\" by Beare R.,
Lehmann G.http://hdl.handle.net/1926/202http://www.insight-
journal.org/browse/publication/92
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
WatershedImageFilter, MorphologicalWatershedFromMarkersImageFilter

 itk::simple::MorphologicalWatershed for the procedural interface


C++ includes: sitkMorphologicalWatershedImageFilter.h
";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::GetLevel "
";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::GetMarkWatershedLine "

Set/Get whether the watershed pixel must be marked or not. Default is
true. Set it to false do not only avoid writing watershed pixels, it
also decrease algorithm complexity.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::MarkWatershedLineOff "
";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::MarkWatershedLineOn "

Set the value of MarkWatershedLine to true or false respectfully.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::MorphologicalWatershedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::SetLevel "
";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::SetMarkWatershedLine "

Set/Get whether the watershed pixel must be marked or not. Default is
true. Set it to false do not only avoid writing watershed pixels, it
also decrease algorithm complexity.

";

%feature("docstring")  itk::simple::MorphologicalWatershedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::MultiplyImageFilter "

Pixel-wise multiplication of two images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults.Wiki Examples:

All Examples

Multiply two images together

Multiply every pixel in an image by a constant

See:
 itk::simple::Multiply for the procedural interface


C++ includes: sitkMultiplyImageFilter.h
";

%feature("docstring")  itk::simple::MultiplyImageFilter::Execute "
";

%feature("docstring")  itk::simple::MultiplyImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::MultiplyImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::MultiplyImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::MultiplyImageFilter::MultiplyImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::MultiplyImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::N4BiasFieldCorrectionImageFilter "

Implementation of the N4 bias field correction algorithm.


The nonparametric nonuniform intensity normalization (N3) algorithm,
as introduced by Sled et al. in 1998 is a method for correcting
nonuniformity associated with MR images. The algorithm assumes a simple parametric model (Gaussian) for the bias field and does not require
tissue class segmentation. In addition, there are only a couple of
parameters to tune with the default values performing quite well. N3
has been publicly available as a set of perl scripts (http://www.bic.mni.mcgill.ca/ServicesSoftwareAdvancedImageProcessingTo
ols/HomePage) The N4 algorithm, encapsulated with this class, is a variation of
the original N3 algorithm with the additional benefits of an improved
B-spline fitting routine which allows for multiple resolutions to be
used during the correction process. We also modify the iterative
update component of algorithm such that the residual bias field is
continually updated Notes for the user:
Since much of the image manipulation is done in the log space of the
intensities, input images with negative and small values (< 1) can
produce poor results.

The original authors recommend performing the bias field correction on
a downsampled version of the original image.

A binary mask or a weighted image can be supplied. If a binary mask is
specified, those voxels in the input image which correspond to the
voxels in the mask image with a value equal to m_MaskLabel, are used
to estimate the bias field. If a confidence image is specified, the
input voxels are weighted in the b-spline fitting routine according to
the confidence voxel values.

The filter returns the corrected image. If the bias field is wanted,
one can reconstruct it using the class
itkBSplineControlPointImageFilter. See the IJ article and the test
file for an example.

The 'Z' parameter in Sled's 1998 paper is the square root of the class
variable 'm_WienerFilterNoise'.
 The basic algorithm iterates between sharpening the intensity
histogram of the corrected input image and spatially smoothing those
results with a B-spline scalar field estimate of the bias field.
Nicholas J. Tustison Contributed by Nicholas J. Tustison, James C. Gee
in the Insight Journal paper:http://hdl.handle.net/10380/3053
REFERENCE
J.G. Sled, A.P. Zijdenbos and A.C. Evans. \"A Nonparametric Method for
Automatic Correction of Intensity Nonuniformity in  Data\" IEEE
Transactions on Medical Imaging, Vol 17, No 1. Feb 1998. N.J.
Tustison, B.B. Avants, P.A. Cook, Y. Zheng, A. Egan, P.A. Yushkevich,
and J.C. Gee. \"N4ITK:  Improved N3 Bias Correction\" IEEE
Transactions on Medical Imaging, 29(6):1310-1320, June 2010.

See:
 itk::simple::N4BiasFieldCorrection for the procedural interface


C++ includes: sitkN4BiasFieldCorrectionImageFilter.h
";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetBiasFieldFullWidthAtHalfMaximum "

Get the full width at half maximum parameter characterizing the width
of the Gaussian deconvolution. Default = 0.15.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetConvergenceThreshold "

Get the convergence threshold. Convergence is determined by the
coefficient of variation of the difference image between the current
bias field estimate and the previous estimate. If this value is less
than the specified threshold, the algorithm proceeds to the next
fitting level or terminates if it is at the last level.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetMaximumNumberOfIterations "

Get the maximum number of iterations specified at each fitting level.
Default = 50.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetNumberOfControlPoints "

Get the control point grid size defining the B-spline estimate of the
scalar bias field. In each dimension, the B-spline mesh size is equal
to the number of control points in that dimension minus the spline
order. Default = 4 control points in each dimension for a mesh size of
1 in each dimension.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetNumberOfHistogramBins "

Get number of bins defining the log input intensity histogram. Default
= 200.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetSplineOrder "

Get the spline order defining the bias field estimate. Default = 3.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::GetWienerFilterNoise "

Get the noise estimate defining the Wiener filter. Default = 0.01.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::N4BiasFieldCorrectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetBiasFieldFullWidthAtHalfMaximum "

Set the full width at half maximum parameter characterizing the width
of the Gaussian deconvolution. Default = 0.15.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetConvergenceThreshold "

Set the convergence threshold. Convergence is determined by the
coefficient of variation of the difference image between the current
bias field estimate and the previous estimate. If this value is less
than the specified threshold, the algorithm proceeds to the next
fitting level or terminates if it is at the last level.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetMaximumNumberOfIterations "

Set the maximum number of iterations specified at each fitting level.
Default = 50.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetNumberOfControlPoints "

Set the control point grid size defining the B-spline estimate of the
scalar bias field. In each dimension, the B-spline mesh size is equal
to the number of control points in that dimension minus the spline
order. Default = 4 control points in each dimension for a mesh size of
1 in each dimension.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetNumberOfHistogramBins "

Set number of bins defining the log input intensity histogram. Default
= 200.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetSplineOrder "

Set the spline order defining the bias field estimate. Default = 3.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::SetWienerFilterNoise "

Set the noise estimate defining the Wiener filter. Default = 0.01.

";

%feature("docstring")  itk::simple::N4BiasFieldCorrectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NaryAddImageFilter "

Pixel-wise addition of N images.


This class is templated over the types of the input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. The pixel type of the input images must have a valid
definition of the operator+ with each other. This condition is
required because internally this filter will perform the operation
pixel_from_image_N+pixel_from_image_(N+1) Additionally the type
resulting from the sum, will be cast to the pixel type of the output
image. The total operation over one pixel will be output_pixel=static_
cast<OutputPixelType>(input_pixel_N+input_pixel_(N+1)) For example,
this filter could be used directly for adding images whose pixels are
vectors of the same dimension, and to store the resulting vector in an
output image of vector pixels.
WARNING:
No numeric overflow checking is performed in this filter.

See:
 itk::simple::NaryAdd for the procedural interface


C++ includes: sitkNaryAddImageFilter.h
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryAddImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::NaryAddImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NaryAddImageFilter::NaryAddImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NaryAddImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NaryMaximumImageFilter "

Computes the pixel-wise maximum of several images.


This class is templated over the types of the input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. The pixel type of the output images must have a
valid definition of the operator<. This condition is required because
internally this filter will perform an operation similar to: constOutp
utPixelTypequery_value=static_cast<OutputPixelType>(pixel_from_input_n
);if(current_maximum<query_value){current_maximum=query_value;}(where
current_maximum is also of type OutputPixelType) for each of the n
input images. For example, this filter could be used directly to find
a \"maximum projection\" of a series of images, often used in
preliminary analysis of time-series data.
Zachary Pincus This filter was contributed by Zachary Pincus from the
Department of Biochemistry and Program in Biomedical Informatics at
Stanford University School of Medicine

See:
 itk::simple::NaryMaximum for the procedural interface


C++ includes: sitkNaryMaximumImageFilter.h
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "
";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::NaryMaximumImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NaryMaximumImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter "

Label pixels that are connected to a seed and lie within a
neighborhood.


NeighborhoodConnectedImageFilterlabels pixels with ReplaceValue that
are connected to an initial Seed AND whose neighbors all lie within a
Lower and Upper threshold range.


See:
 itk::simple::NeighborhoodConnected for the procedural interface


C++ includes: sitkNeighborhoodConnectedImageFilter.h
";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::AddSeed "

AddSeed - Add a seed to the end of the list

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::ClearSeeds "

ClearSeeds - Clear out all seeds in the list

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetLower "

Set/Get the lower threshold. The default is 0.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetRadius "

Get the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie * within
Lower and Upper (inclusive) will be replaced with this value. The
default is 1.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetSeedList "

Get SeedList

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::GetUpper "

Set/Get the upper threshold. The default is the largest possible value
for the InputPixelType.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::NeighborhoodConnectedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetLower "

Set/Get the lower threshold. The default is 0.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetRadius "

Set the radius of the neighborhood used for a mask.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetReplaceValue "

Set/Get value to replace thresholded pixels. Pixels that lie * within
Lower and Upper (inclusive) will be replaced with this value. The
default is 1.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetSeed "

SetSeed - Set list to a single seed

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetSeedList "

Set SeedList

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::SetUpper "

Set/Get the upper threshold. The default is the largest possible value
for the InputPixelType.

";

%feature("docstring")  itk::simple::NeighborhoodConnectedImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NoiseImageFilter "

Calculate the local noise in an image.


Computes an image where a given pixel is the standard deviation of the
pixels in a neighborhood about the corresponding input pixel. This
serves as an estimate of the local noise (or texture) in an image.
Currently, this noise estimate assume a piecewise constant image. This
filter should be extended to fitting a (hyper) plane to the
neighborhood and calculating the standard deviation of the residuals
to this (hyper) plane.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Compute the local noise in an image

See:
 itk::simple::Noise for the procedural interface


C++ includes: sitkNoiseImageFilter.h
";

%feature("docstring")  itk::simple::NoiseImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::NoiseImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NoiseImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NoiseImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::NoiseImageFilter::NoiseImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NoiseImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::NoiseImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::NoiseImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NonCopyable "

An inheratable class to disable copying of a class.


This class disable the implicit implementations of the assignment and
copy constructor for derived classes. The instantiation of the default
implementation for either method in a derived class will result in a
compile-time error because they are private in this class. However,
this policy is not absolute for derived classes because explicit
implementation of these methods could be implemented.

An advatange this apporach has is the class heiarchy makes it obvious
what the intent is, as compared to other appoaches.

For example you should not be able to copy singleton object, because
there should only be one of them. To utilize this class just derive
from it:

C++ includes: sitkNonCopyable.h
";


%feature("docstring") itk::simple::NormalizeImageFilter "

Normalize an image by setting its mean to zero and variance to one.


NormalizeImageFiltershifts and scales an image so that the pixels in
the image have a zero mean and unit variance. This filter uses
StatisticsImageFilterto compute the mean and variance of the input and
then applies ShiftScaleImageFilterto shift and scale the pixels. NB:
since this filter normalizes the data to lie within -1 to 1, integral
types will produce an image that DOES NOT HAVE a unit variance.
See:
 NormalizeToConstantImageFilter
Wiki Examples:

All Examples

Normalize an image

See:
 itk::simple::Normalize for the procedural interface


C++ includes: sitkNormalizeImageFilter.h
";

%feature("docstring")  itk::simple::NormalizeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NormalizeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NormalizeImageFilter::NormalizeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NormalizeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NormalizeToConstantImageFilter "

Scales image pixel intensities to make the sum of all pixels equal a
user-defined constant.


The default value of the constant is 1. It can be changed with SetConstant(). This transform is especially useful for normalizing a convolution
kernel. This code was contributed in the Insight Journal paper: \"FFT
based  convolution\" by Lehmann G.http://hdl.handle.net/10380/3154
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 NormalizeImageFilter


 StatisticsImageFilter


 DivideImageFilter
Wiki Examples:

All Examples

Scale all pixels so that their sum is a specified constant

See:
 itk::simple::NormalizeToConstant for the procedural interface


C++ includes: sitkNormalizeToConstantImageFilter.h
";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::GetConstant "

Set/get the normalization constant.

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::NormalizeToConstantImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::SetConstant "

Set/get the normalization constant.

";

%feature("docstring")  itk::simple::NormalizeToConstantImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NormalizedCorrelationImageFilter "

Computes the normalized correlation of an image and a template.


This filter calculates the normalized correlation between an image and
the template. Normalized correlation is frequently use in feature
detection because it is invariant to local changes in contrast. The
filter can be given a mask. When presented with an input image and a
mask, the normalized correlation is only calculated at those pixels
under the mask.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Normalized correlation

See:
 itk::simple::NormalizedCorrelation for the procedural interface


C++ includes: sitkNormalizedCorrelationImageFilter.h
";

%feature("docstring")  itk::simple::NormalizedCorrelationImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NormalizedCorrelationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NormalizedCorrelationImageFilter::NormalizedCorrelationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NormalizedCorrelationImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NotEqualImageFilter "


See:
 itk::simple::NotEqual for the procedural interface


C++ includes: sitkNotEqualImageFilter.h
";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "

Execute the filter on an image and a constant with the given
parameters

";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "
";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::NotEqualImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::NotEqualImageFilter::GetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::NotEqualImageFilter::GetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::NotEqualImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NotEqualImageFilter::NotEqualImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NotEqualImageFilter::SetBackgroundValue "

Set/Get the value used to mark the false pixels of the operator.

";

%feature("docstring")  itk::simple::NotEqualImageFilter::SetForegroundValue "

Set/Get the value used to mark the true pixels of the operator.

";

%feature("docstring")  itk::simple::NotEqualImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::NotImageFilter "

Implements the NOT logical operator pixel-wise on an image.


This class is templated over the types of an input image and the type
of the output image. Numeric conversions (castings) are done by the
C++ defaults. Since the logical NOT operation is only defined in C++
for integer types, the images passed to this filter must comply with
the requirement of using integer pixel type. The total operation over
one pixel will be
output_pixel=static_cast<OutputPixelType>(!input_pixel) Where \"!\" is
the unary NOT operator in C++.


See:
 itk::simple::Not for the procedural interface


C++ includes: sitkNotImageFilter.h
";

%feature("docstring")  itk::simple::NotImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::NotImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::NotImageFilter::NotImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::NotImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::OpeningByReconstructionImageFilter "

Opening by reconstruction of an image.


This filter preserves regions, in the foreground, that can completely
contain the structuring element. At the same time, this filter
eliminates all other regions of foreground pixels. Contrary to the
mophological opening, the opening by reconstruction preserves the
shape of the components that are not removed by erosion. The opening
by reconstruction of an image \"f\" is defined as:
OpeningByReconstruction(f) = DilationByRecontruction(f, Erosion(f)).
Opening by reconstruction not only removes structures destroyed by the
erosion, but also levels down the contrast of the brightest regions.
If PreserveIntensities is on, a subsequent reconstruction by dilation
using a marker image that is the original image for all unaffected
pixels. Opening by reconstruction is described in Chapter 6.3.9 of
Pierre Soille's book \"Morphological Image Analysis: Principles and
Applications\", Second Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 GrayscaleMorphologicalOpeningImageFilter

 itk::simple::OpeningByReconstruction for the procedural interface


C++ includes: sitkOpeningByReconstructionImageFilter.h
";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::GetPreserveIntensities "

Set/Get whether the original intensities of the image retained for
those pixels unaffected by the opening by reconstrcution. If Off, the
output pixel contrast will be reduced.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::OpeningByReconstructionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::PreserveIntensitiesOff "
";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::PreserveIntensitiesOn "

Set the value of PreserveIntensities to true or false respectfully.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::SetPreserveIntensities "

Set/Get whether the original intensities of the image retained for
those pixels unaffected by the opening by reconstrcution. If Off, the
output pixel contrast will be reduced.

";

%feature("docstring")  itk::simple::OpeningByReconstructionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::OrImageFilter "

Implements the OR logical operator pixel-wise between two images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. Since the logical OR operation is only defined in
C++ for integer types, the images passed to this filter must comply
with the requirement of using integer pixel type. The total operation
over one pixel will be
output_pixel=static_cast<OutputPixelType>(input1_pixel|input2_pixel)
Where \"|\" is the boolean OR operator in C++.Wiki Examples:

All Examples

Binary OR two images

See:
 itk::simple::Or for the procedural interface


C++ includes: sitkOrImageFilter.h
";

%feature("docstring")  itk::simple::OrImageFilter::Execute "
";

%feature("docstring")  itk::simple::OrImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::OrImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::OrImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::OrImageFilter::OrImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::OrImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::OtsuMultipleThresholdsImageFilter "

Threshold an image using multiple Otsu Thresholds.


This filter creates a labeled image that separates the input image
into various classes. The filter computes the thresholds using the
OtsuMultipleThresholdsCalculatorand applies those thesholds to the
input image using the ThresholdLabelerImageFilter. The
NumberOfHistogramBins and NumberOfThresholds can be set for the
Calculator. The LabelOffset can be set for the
ThresholdLabelerImageFilter.
See:
ScalarImageToHistogramGenerator


OtsuMultipleThresholdsCalculator


ThresholdLabelerImageFilter

 itk::simple::OtsuMultipleThresholds for the procedural interface


C++ includes: sitkOtsuMultipleThresholdsImageFilter.h
";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::GetLabelOffset "

Set/Get the offset which labels have to start from. Default is 0.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::GetNumberOfHistogramBins "

Set/Get the number of histogram bins. Default is 128.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::GetNumberOfThresholds "

Set/Get the number of thresholds. Default is 1.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::OtsuMultipleThresholdsImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::SetLabelOffset "

Set/Get the offset which labels have to start from. Default is 0.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins. Default is 128.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::SetNumberOfThresholds "

Set/Get the number of thresholds. Default is 1.

";

%feature("docstring")  itk::simple::OtsuMultipleThresholdsImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::OtsuThresholdImageFilter "

Threshold an image using the Otsu Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the OtsuThresholdCalculatorand applies that theshold
to the input image using the BinaryThresholdImageFilter.
Richard Beare Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811
Wiki Examples:

All Examples

Separate foreground and background using Otsu's method
See:
HistogramThresholdImageFitler

 itk::simple::OtsuThreshold for the procedural interface



C++ includes: sitkOtsuThresholdImageFilter.h
";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::OtsuThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value. The default value
NumericTraits<OutputPixelType>::max().

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins. Defaults is 128.

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::OtsuThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::PasteImageFilter "

Paste an image into another image.


PasteImageFilterallows you to take a section of one image and paste
into another image. The SetDestinationIndex()method prescribes where in the first input to start pasting data from
the second input. The SetSourceRegion method prescribes the section of
the second image to paste into the first. If the output requested
region does not have include the SourceRegion after it has been
repositioned to DestinationIndex, then the output will just be a copy
of the input. The two inputs and output image will have the same pixel
type.Wiki Examples:

All Examples

Paste a part of one image into another image

See:
 itk::simple::Paste for the procedural interface


C++ includes: sitkPasteImageFilter.h
";

%feature("docstring")  itk::simple::PasteImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::PasteImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::PasteImageFilter::GetDestinationIndex "

Set/Get the destination index (where in the first input the second
input will be pasted.

";

%feature("docstring")  itk::simple::PasteImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::PasteImageFilter::GetSourceIndex "
";

%feature("docstring")  itk::simple::PasteImageFilter::GetSourceSize "
";

%feature("docstring")  itk::simple::PasteImageFilter::PasteImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::PasteImageFilter::SetDestinationIndex "

Set/Get the destination index (where in the first input the second
input will be pasted.

";

%feature("docstring")  itk::simple::PasteImageFilter::SetSourceIndex "
";

%feature("docstring")  itk::simple::PasteImageFilter::SetSourceSize "
";

%feature("docstring")  itk::simple::PasteImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::PermuteAxesImageFilter "

Permutes the image axes according to a user specified order.


PermuateAxesImageFilter permutes the image axes according to a user
specified order. The permutation order is set via method SetOrder(
order ) where the input is an array of ImageDimension number of
unsigned int. The elements of the array must be a rearrangment of the
numbers from 0 to ImageDimension - 1. The i-th axis of the output
image corresponds with the order[i]-th axis of the input image. The
output meta image information (LargestPossibleRegion, spacing, origin)
is computed by permuting the corresponding input meta information.Wiki Examples:

All Examples

Switch the axes of an image

See:
 itk::simple::PermuteAxes for the procedural interface


C++ includes: sitkPermuteAxesImageFilter.h
";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::GetOrder "

Get the permutation order.

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::PermuteAxesImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::SetOrder "

Set the permutation order. The elements of order must be a
rearrangement of the numbers from 0 to ImageDimension - 1.

";

%feature("docstring")  itk::simple::PermuteAxesImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::PhysicalPointImageSource "


See:
 itk::simple::PhysicalPointImageSource for the procedural interface


C++ includes: sitkPhysicalPointImageSource.h
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::PhysicalPointImageSource::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetDirection "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetName "

Name of this class

";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetOrigin "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetOutputPixelType "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetSize "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::GetSpacing "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::PhysicalPointImageSource "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetDirection "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetOrigin "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetOutputPixelType "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetReferenceImage "

This methods sets the size, origin, spacing and direction to that of
the provided image

";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetSize "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::SetSpacing "
";

%feature("docstring")  itk::simple::PhysicalPointImageSource::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::PimpleImageBase "

Private implementation idiom image base class.


We utilize the private implementation ( or PImple) programming idiom
to modify the behavior of the simple image class based on the different image types.

This class is designed to utilize the trivial copy, and assgnement
operators

C++ includes: sitkPimpleImageBase.h
";

%feature("docstring")  itk::simple::PimpleImageBase::DeepCopy "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsDouble "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsDouble "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsFloat "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsFloat "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetBufferAsUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetDataBase "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetDataBase "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetDepth "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetDimension "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetDirection "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetHeight "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetNumberOfComponentsPerPixel "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetOrigin "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsComplexFloat32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsComplexFloat64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsDouble "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsFloat "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorFloat32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorFloat64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelAsVectorUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetPixelID "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetReferenceCountOfImage "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetSize "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetSize "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetSpacing "
";

%feature("docstring")  itk::simple::PimpleImageBase::GetWidth "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetDirection "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetOrigin "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsComplexFloat32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsComplexFloat64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsDouble "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsFloat "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorFloat32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorFloat64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorUInt16 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorUInt32 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorUInt64 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetPixelAsVectorUInt8 "
";

%feature("docstring")  itk::simple::PimpleImageBase::SetSpacing "
";

%feature("docstring")  itk::simple::PimpleImageBase::ShallowCopy "
";

%feature("docstring")  itk::simple::PimpleImageBase::ToString "
";

%feature("docstring")  itk::simple::PimpleImageBase::TransformIndexToPhysicalPoint "
";

%feature("docstring")  itk::simple::PimpleImageBase::TransformPhysicalPointToIndex "
";

%feature("docstring")  itk::simple::PimpleImageBase::~PimpleImageBase "
";


%feature("docstring") itk::simple::PowImageFilter "

Computes the powers of 2 images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. The output of the pow function will be cast to the
pixel type of the output image. The total operation over one pixel
will beoutput_pixel=static_cast<TOutput>(vcl_pow(static_cast<RealType>
(A),static_cast<RealType>(B))); The pow function can be applied to two
images with the following: SetInput1(image1); SetInput2(image2);
Additionally, this filter can be used to raise every pixel of an image
to a power of a constant by using SetInput1(image1);
SetConstant2(constant);


See:
 itk::simple::Pow for the procedural interface


C++ includes: sitkPowImageFilter.h
";

%feature("docstring")  itk::simple::PowImageFilter::Execute "
";

%feature("docstring")  itk::simple::PowImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::PowImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::PowImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::PowImageFilter::PowImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::PowImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ProjectedLandweberDeconvolutionImageFilter "

Deconvolve an image using the projected Landweber deconvolution
algorithm.


This filter performs the same calculation per iteration as the LandweberDeconvolutionImageFilter. However, at each iteration, negative pixels in the intermediate
result are projected (set) to zero. This is useful if the solution is
assumed to always be non-negative, which is the case when dealing with
images formed by counting photons, for example. This code was adapted
from the Insight Journal contribution: \"Deconvolution: infrastructure
and reference algorithms\" by Gaetan
Lehmannhttp://hdl.handle.net/10380/3207
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Cory Quammen, The University of North
Carolina at Chapel Hill

See:
IterativeDeconvolutionImageFilter


 RichardsonLucyDeconvolutionImageFilter


 LandweberDeconvolutionImageFilter

 itk::simple::ProjectedLandweberDeconvolution for the procedural interface


C++ includes: sitkProjectedLandweberDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetAlpha "

Get the relaxation factor.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetNumberOfIterations "

Get the number of iterations.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::ProjectedLandweberDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::SetAlpha "

Set the relaxation factor.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::SetNumberOfIterations "

Set the number of iterations.

";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RankImageFilter "


See:
 itk::simple::Rank for the procedural interface


C++ includes: sitkRankImageFilter.h
";

%feature("docstring")  itk::simple::RankImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RankImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RankImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RankImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::RankImageFilter::GetRank "
";

%feature("docstring")  itk::simple::RankImageFilter::RankImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RankImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::RankImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::RankImageFilter::SetRank "
";

%feature("docstring")  itk::simple::RankImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RealAndImaginaryToComplexImageFilter "

Implements pixel-wise conversion of real and imaginary data into
complex voxels.


This filter is parametrized over the types of the two input images and
the type of the output image. The filter expect all images to have the
same dimension (e.g. all 2D, or all 3D, or all ND)


See:
 itk::simple::RealAndImaginaryToComplex for the procedural interface


C++ includes: sitkRealAndImaginaryToComplexImageFilter.h
";

%feature("docstring")  itk::simple::RealAndImaginaryToComplexImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::RealAndImaginaryToComplexImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RealAndImaginaryToComplexImageFilter::RealAndImaginaryToComplexImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RealAndImaginaryToComplexImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RealToHalfHermitianForwardFFTImageFilter "

Base class for specialized real-to-complex forward Fast Fourier Transform.


This is a base class for the \"forward\" or \"direct\" discrete
Fourier Transform. This is an abstract base class: the actual implementation is
provided by the best child class available on the system when the
object is created via the object factory system. This class transforms
a real input image into its complex Fourier transform. The Fourier
transform of a real input image has Hermitian symmetry: $ f(\\\\mathbf{x}) = f^*(-\\\\mathbf{x}) $ . That is, when the result of the transform is split in half along
the X-dimension, the values in the second half of the transform are
the complex conjugates of values in the first half reflected about the
center of the image in each dimension. This filter takes advantage of
the Hermitian symmetry property and reduces the size of the output in
the first dimension to N/2+1, where N is the size of the input image
in that dimension and the division by 2 is rounded down.
See:
 HalfHermitianToRealInverseFFTImageFilter


 ForwardFFTImageFilter

 itk::simple::RealToHalfHermitianForwardFFT for the procedural interface


C++ includes: sitkRealToHalfHermitianForwardFFTImageFilter.h
";

%feature("docstring")  itk::simple::RealToHalfHermitianForwardFFTImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RealToHalfHermitianForwardFFTImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RealToHalfHermitianForwardFFTImageFilter::RealToHalfHermitianForwardFFTImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RealToHalfHermitianForwardFFTImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ReconstructionByDilationImageFilter "

grayscale reconstruction by dilation of an image


Reconstruction by dilation operates on a \"marker\" image and a
\"mask\" image, and is defined as the dilation of the marker image
with respect to the mask image iterated until stability. The marker
image must be less than or equal to the mask image (on a pixel by
pixel basis). Geodesic morphology is described in Chapter 6.2 of
Pierre Soille's book \"Morphological Image Analysis: Principles and
Applications\", Second Edition, Springer, 2003. Algorithm implemented
in this filter is based on algorithm described by Kevin Robinson and
Paul F. Whelan in \"Efficient Morphological    Reconstruction: A
Downhill Filter\", Pattern Recognition Letters, Volume 25, Issue 15,
November 2004, Pages 1759-1767. The algorithm, a description of the
transform and some applications can be found in \"Morphological
Grayscale Reconstruction in Image Analysis:    Applications and
Efficient Algorithms\", Luc Vincent, IEEE Transactions on image
processing, Vol. 2, April 1993.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia.

See:
MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByErosionImageFilter, OpeningByReconstructionImageFilter, ClosingByReconstructionImageFilter, ReconstructionImageFilter

 itk::simple::ReconstructionByDilation for the procedural interface


C++ includes: sitkReconstructionByDilationImageFilter.h
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::GetUseInternalCopy "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::ReconstructionByDilationImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::SetUseInternalCopy "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::UseInternalCopyOff "
";

%feature("docstring")  itk::simple::ReconstructionByDilationImageFilter::UseInternalCopyOn "

Set the value of UseInternalCopy to true or false respectfully.

";


%feature("docstring") itk::simple::ReconstructionByErosionImageFilter "

grayscale reconstruction by erosion of an image


Reconstruction by erosion operates on a \"marker\" image and a
\"mask\" image, and is defined as the erosion of the marker image with
respect to the mask image iterated until stability. The marker image
must be less than or equal to the mask image (on a pixel by pixel
basis). Geodesic morphology is described in Chapter 6.2 of Pierre
Soille's book \"Morphological Image Analysis: Principles and
Applications\", Second Edition, Springer, 2003. Algorithm implemented
in this filter is based on algorithm described by Kevin Robinson and
Paul F. Whelan in \"Efficient Morphological    Reconstruction: A
Downhill Filter\", Pattern Recognition Letters, Volume 25, Issue 15,
November 2004, Pages 1759-1767. The algorithm, a description of the
transform and some applications can be found in \"Morphological
Grayscale Reconstruction in Image Analysis:    Applications and
Efficient Algorithms\", Luc Vincent, IEEE Transactions on image
processing, Vol. 2, April 1993.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia.

See:
MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByErosionImageFilter, OpeningByReconstructionImageFilter, ClosingByReconstructionImageFilter, ReconstructionImageFilter

 itk::simple::ReconstructionByErosion for the procedural interface


C++ includes: sitkReconstructionByErosionImageFilter.h
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::GetUseInternalCopy "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::ReconstructionByErosionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::SetUseInternalCopy "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::UseInternalCopyOff "
";

%feature("docstring")  itk::simple::ReconstructionByErosionImageFilter::UseInternalCopyOn "

Set the value of UseInternalCopy to true or false respectfully.

";


%feature("docstring") itk::simple::RecursiveGaussianImageFilter "

Base class for computing IIR convolution with an approximation of a
Gaussian kernel.


 \\\\[ \\\\frac{ 1 }{ \\\\sigma \\\\sqrt{ 2 \\\\pi } } \\\\exp{
\\\\left( - \\\\frac{x^2}{ 2 \\\\sigma^2 } \\\\right) } \\\\] RecursiveGaussianImageFilteris the base class for recursive filters
that approximate convolution with the Gaussian kernel. This class
implements the recursive filtering method proposed by R.Deriche in
IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, \"Fast Algorithms for
Low-Level Vision\" Details of the implementation are described in the
technical report: R. Deriche, \"Recursively Implementing The Gaussian
and Its Derivatives\", INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz Further improvements of the algorithm are described in: G. Farneback
& C.-F. Westin, \"On Implementation of Recursive Gaussian  Filters\",
so far unpublished. As compared to itk::DiscreteGaussianImageFilter,
this filter tends to be faster for large kernels, and it can take the
derivative of the blurred image in one step. Also, note that we have
itk::RecursiveGaussianImageFilter::SetSigma(), but
itk::DiscreteGaussianImageFilter::SetVariance().
See:
 DiscreteGaussianImageFilter
Wiki Examples:

All Examples

Find higher derivatives of an image

See:
 itk::simple::RecursiveGaussian for the procedural interface


C++ includes: sitkRecursiveGaussianImageFilter.h
";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::GetDirection "
";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::GetNormalizeAcrossScale "
";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::GetOrder "

Set/Get the Order of the Gaussian to convolve with.



ZeroOrder is equivalent to convolving with a Gaussian. This is the
default.

FirstOrder is equivalent to convolving with the first derivative of a
Gaussian.

SecondOrder is equivalent to convolving with the second derivative of
a Gaussian.


";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::GetSigma "

Set/Get the Sigma, measured in world coordinates, of the Gaussian
kernel. The default is 1.0.

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::NormalizeAcrossScaleOff "
";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::NormalizeAcrossScaleOn "

Set the value of NormalizeAcrossScale to true or false respectfully.

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::RecursiveGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::SetDirection "
";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::SetNormalizeAcrossScale "

Set/Get the flag for normalizing the gaussian over scale-space.This
flag enables the analysis of the differential shape of features
independent of their size ( both pixels and physical size ). Following
the notation of Tony Lindeberg:.


Let  be the scale-space representation of image  where  is the Gaussian function and  denotes convolution. This is a change from above with .

Then the normalized derivative operator for normalized coordinates
across scale is: \\\\[ \\\\partial_\\\\xi = \\\\sqrt{t} \\\\partial_x \\\\] The resulting scaling factor is \\\\[ \\\\sigma^N \\\\] where N is the order of the derivative. When this flag is ON the
filter will be normalized in such a way that the values of derivatives
are not biased by the size of the object. That is to say the maximum
value a feature reaches across scale is independent of the scale of
the object. For analyzing an image across scale-space you want to
enable this flag. It is disabled by default.
Not all scale space axioms are satisfied by this filter, some are only
approximated. Particularly, at fine scales ( say less than 1 pixel )
other methods such as a discrete Gaussian kernel should be considered.


";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::SetOrder "

Set/Get the Order of the Gaussian to convolve with.



ZeroOrder is equivalent to convolving with a Gaussian. This is the
default.

FirstOrder is equivalent to convolving with the first derivative of a
Gaussian.

SecondOrder is equivalent to convolving with the second derivative of
a Gaussian.


";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::SetSigma "

Set/Get the Sigma, measured in world coordinates, of the Gaussian
kernel. The default is 1.0.

";

%feature("docstring")  itk::simple::RecursiveGaussianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RegionOfInterestImageFilter "

Extract a region of interest from the input image.


This filter produces an output image of the same dimension as the
input image. The user specifies the region of the input image that
will be contained in the output image. The origin coordinates of the
output images will be computed in such a way that if mapped to
physical space, the output image will overlay the input image with
perfect registration. In other words, a registration process between
the output image and the input image will return an identity
transform. If you are interested in changing the dimension of the
image, you may want to consider the ExtractImageFilter. For example for extracting a 2D image from a slice of a 3D image.
The region to extract is set using the method SetRegionOfInterest.
See:
 ExtractImageFilter
Wiki Examples:

All Examples

Extract a portion of an image (region of interest)

See:
 itk::simple::RegionOfInterest for the procedural interface


C++ includes: sitkRegionOfInterestImageFilter.h
";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::GetIndex "
";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::GetSize "
";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::RegionOfInterestImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::SetIndex "

odo the internal setting of the method need work!!!

";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::SetSize "
";

%feature("docstring")  itk::simple::RegionOfInterestImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RegionalMaximaImageFilter "

Produce a binary image where foreground is the regional maxima of the
input image.


Regional maxima are flat zones surrounded by pixels of lower value. If
the input image is constant, the entire image can be considered as a
maxima or not. The desired behavior can be selected with the SetFlatIsMaxima()method.
Gaetan Lehmann This class was contributed to the Insight Journal by
author Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. The paper can be found
athttp://hdl.handle.net/1926/153

See:
 ValuedRegionalMaximaImageFilter


 HConvexImageFilter


 RegionalMinimaImageFilter
Wiki Examples:

All Examples

 RegionalMaximaImageFilter

See:
 itk::simple::RegionalMaxima for the procedural interface


C++ includes: sitkRegionalMaximaImageFilter.h
";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::FlatIsMaximaOff "
";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::FlatIsMaximaOn "

Set the value of FlatIsMaxima to true or false respectfully.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::GetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::GetFlatIsMaxima "

Set/Get wether a flat image must be considered as a maxima or not.
Defaults to true.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::GetForegroundValue "

Set/Get the value in the output image to consider as \"foreground\".
Defaults to maximum value of PixelType.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::RegionalMaximaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::SetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::SetFlatIsMaxima "

Set/Get wether a flat image must be considered as a maxima or not.
Defaults to true.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::SetForegroundValue "

Set/Get the value in the output image to consider as \"foreground\".
Defaults to maximum value of PixelType.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::RegionalMaximaImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RegionalMinimaImageFilter "

Produce a binary image where foreground is the regional minima of the
input image.


Regional minima are flat zones surrounded by pixels of greater value.
If the input image is constant, the entire image can be considered as
a minima or not. The SetFlatIsMinima()method let the user choose which behavior to use. This class was
contribtued to the Insight Journal by
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.http://hdl.handle.net/1926/153
RegionalMaximaImageFilterMathematicalMorphologyImageFilters

See:
 ValuedRegionalMinimaImageFilter


 HConcaveImageFilter
Wiki Examples:

All Examples

 RegionalMinimaImageFilter

See:
 itk::simple::RegionalMinima for the procedural interface


C++ includes: sitkRegionalMinimaImageFilter.h
";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::FlatIsMinimaOff "
";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::FlatIsMinimaOn "

Set the value of FlatIsMinima to true or false respectfully.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::GetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::GetFlatIsMinima "

Set/Get wether a flat image must be considered as a minima or not.
Defaults to true.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::GetForegroundValue "

Set/Get the value in the output image to consider as \"foreground\".
Defaults to maximum value of PixelType.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::GetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::RegionalMinimaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::SetBackgroundValue "

Set/Get the value used as \"background\" in the output image. Defaults
to NumericTraits<PixelType>::NonpositiveMin().

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::SetFlatIsMinima "

Set/Get wether a flat image must be considered as a minima or not.
Defaults to true.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::SetForegroundValue "

Set/Get the value in the output image to consider as \"foreground\".
Defaults to maximum value of PixelType.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::SetFullyConnected "

Set/Get whether the connected components are defined strictly by face
connectivity or by face+edge+vertex connectivity. Default is
FullyConnectedOff. For objects that are 1 pixel wide, use
FullyConnectedOn.

";

%feature("docstring")  itk::simple::RegionalMinimaImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RelabelComponentImageFilter "

Relabel the components in an image such that consecutive labels are
used.


RelabelComponentImageFilterremaps the labels associated with the
objects in an image (as from the output of ConnectedComponentImageFilter) such that the label numbers are consecutive with no gaps between the
label numbers used. By default, the relabeling will also sort the
labels based on the size of the object: the largest object will have
label #1, the second largest will have label #2, etc. Label #0 is
assumed to be background is left unaltered by the relabeling.
RelabelComponentImageFilteris typically used on the output of the
ConnectedComponentImageFilterfor those applications that want to
extract the largest object or the \"k\" largest objects. Any
particular object can be extracted from the relabeled output using a BinaryThresholdImageFilter. A group of objects can be extracted from the relabled output using a ThresholdImageFilter. Once all the objects are relabeled, the application can query the
number of objects and the size of each object. Objectsizes are
returned in a vector. The size of the background is not calculated. So
the size of object #1 is GetSizeOfObjectsInPixels()[0], the size of
object #2 is GetSizeOfObjectsInPixels()[1], etc. If user sets a
minimum object size, all objects with fewer pixelss than the minimum
will be discarded, so that the number of objects reported will be only
those remaining. The GetOriginalNumberOfObjects method can be called
to find out how many objects were present before the small ones were
discarded. RelabelComponentImageFiltercan be run as an \"in place\"
filter, where it will overwrite its output. The default is run out of
place (or generate a separate output). \"In place\" operation can be
controlled via methods in the superclass,
InPlaceImageFilter::InPlaceOn()and InPlaceImageFilter::InPlaceOff().
See:
 ConnectedComponentImageFilter, BinaryThresholdImageFilter, ThresholdImageFilter
Wiki Examples:

All Examples

Assign contiguous labels to connected regions of an image

See:
 itk::simple::RelabelComponent for the procedural interface


C++ includes: sitkRelabelComponentImageFilter.h
";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::GetMinimumObjectSize "

Get the caller-defined minimum size of an object in pixels. If the
caller has not set the minimum, 0 will be returned, which is to be
interpreted as meaning that no minimum exists, and all objects in the
original label map will be passed through to the output.

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::RelabelComponentImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::SetMinimumObjectSize "

Set the minimum size in pixels for an object. All objects smaller than
this size will be discarded and will not appear in the output label
map. NumberOfObjects will count only the objects whose pixel counts
are greater than or equal to the minimum size. Call
GetOriginalNumberOfObjects to find out how many objects were present
in the original label map.

";

%feature("docstring")  itk::simple::RelabelComponentImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RenyiEntropyThresholdImageFilter "

Threshold an image using the RenyiEntropy Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the RenyiEntropyThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::RenyiEntropyThreshold for the procedural interface


C++ includes: sitkRenyiEntropyThresholdImageFilter.h
";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::RenyiEntropyThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::RenyiEntropyThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ResampleImageFilter "

Resample an image via a coordinate transform.


ResampleImageFilterresamples an existing image through some coordinate
transform, interpolating via some image function. The class is
templated over the types of the input and output images. Note that the
choice of interpolator function can be important. This function is set
via SetInterpolator(). The default is LinearInterpolateImageFunction<InputImageType,
TInterpolatorPrecisionType>, which is reasonable for ordinary medical
images. However, some synthetic images have pixels drawn from a finite
prescribed set. An example would be a mask indicating the segmentation
of a brain into a small number of tissue types. For such an image, one
does not want to interpolate between different pixel values, and so
NearestNeighborInterpolateImageFunction< InputImageType, TCoordRep >
would be a better choice. If an sample is taken from outside the image
domain, the default behavior is to use a default pixel value. If
different behavior is desired, an extrapolator function can be set
with SetExtrapolator(). Output information (spacing, size and
direction) for the output image should be set. This information has
the normal defaults of unit spacing, zero origin and identity
direction. Optionally, the output information can be obtained from a
reference image. If the reference image is provided and
UseReferenceImage is On, then the spacing, origin and direction of the
reference image will be used. Since this filter produces an image
which is a different size than its input, it needs to override several
of the methods defined in ProcessObjectin order to properly manage the
pipeline execution model. In particular, this filter overrides
ProcessObject::GenerateInputRequestedRegion()and
ProcessObject::GenerateOutputInformation(). This filter is implemented
as a multithreaded filter. It provides a ThreadedGenerateData()method
for its implementation.
WARNING:
For multithreading, the TransformPoint method of the user-designated
coordinate transform must be threadsafe.
Wiki Examples:

All Examples

Translate an image

Upsampling an image

Resample (stretch or compress) an image

See:
 itk::simple::Resample for the procedural interface


C++ includes: sitkResampleImageFilter.h
";

%feature("docstring")  itk::simple::ResampleImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ResampleImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetDefaultPixelValue "

Get the pixel value when a transformed pixel is outside of the image.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetInterpolator "

Get a pointer to the interpolator function.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetOutputDirection "

Set the output direciton cosine matrix.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetOutputOrigin "

Get the output image origin.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetOutputSpacing "

Get the output image spacing.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetSize "

Get the size of the output image.

";

%feature("docstring")  itk::simple::ResampleImageFilter::GetTransform "

Get a pointer to the coordinate transform.

";

%feature("docstring")  itk::simple::ResampleImageFilter::ResampleImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetDefaultPixelValue "

Set the pixel value when a transformed pixel is outside of the image.
The default default pixel value is 0.

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetInterpolator "

Set the interpolator function. The default is
LinearInterpolateImageFunction<InputImageType,
TInterpolatorPrecisionType>. Some other options are
NearestNeighborInterpolateImageFunction(useful for binary masks and
other images with a small number of possible pixel values), and
BSplineInterpolateImageFunction(which provides a higher order of
interpolation).

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetOutputDirection "

Set the output direciton cosine matrix.

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetOutputOrigin "

Set the output image origin.

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetOutputSpacing "

Set the output image spacing.

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetReferenceImage "

This methods sets the output size, origin, spacing and direction to
that of the provided image

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetSize "

Set the size of the output image.

";

%feature("docstring")  itk::simple::ResampleImageFilter::SetTransform "

Set the coordinate transformation. Set the coordinate transform to use
for resampling. Note that this must be in physical coordinates and it
is the output-to-input transform, NOT the input-to-output transform
that you might naively expect. By default the filter uses an Identity
transform. You must provide a different transform here, before
attempting to run the filter, if you do not want to use the default
Identity transform.

";

%feature("docstring")  itk::simple::ResampleImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RescaleIntensityImageFilter "

Applies a linear transformation to the intensity levels of the input Image.


RescaleIntensityImageFilterapplies pixel-wise a linear transformation
to the intensity values of input image pixels. The linear
transformation is defined by the user in terms of the minimum and
maximum values that the output image should have. The following
equation gives the mapping of the intensity values #44
All computations are performed in the precison of the input pixel's
RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image
are computed internally using the MinimumMaximumImageCalculator. Users
are not supposed to set those values in this filter. If you need a
filter where you can set the minimum and maximum values of the input,
please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear
transformation for the intensity, then please use the ShiftScaleImageFilter.

See:
 IntensityWindowingImageFilter
Wiki Examples:

All Examples

Rescale the intensity values of an image to a specified range

See:
 itk::simple::RescaleIntensity for the procedural interface


C++ includes: sitkRescaleIntensityImageFilter.h
";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::GetOutputMaximum "
";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::GetOutputMinimum "
";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::RescaleIntensityImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::SetOutputMaximum "
";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::SetOutputMinimum "
";

%feature("docstring")  itk::simple::RescaleIntensityImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::RichardsonLucyDeconvolutionImageFilter "

Deconvolve an image using the Richardson-Lucy deconvolution algorithm.


This filter implements the Richardson-Lucy deconvolution algorithm as
defined in Bertero M and Boccacci P, \"Introduction to Inverse
Problems in Imaging\", 1998. The algorithm assumes that the input
image has been formed by a linear shift-invariant system with a known
kernel. The Richardson-Lucy algorithm assumes that noise in the image
follows a Poisson distribution and that the distribution for each
pixel is independent of the other pixels. This code was adapted from
the Insight Journal contribution: \"Deconvolution: infrastructure and
reference algorithms\" by Gaetan
Lehmannhttp://hdl.handle.net/10380/3207
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Cory Quammen, The University of North
Carolina at Chapel Hill

See:
IterativeDeconvolutionImageFilter


 LandweberDeconvolutionImageFilter


 ProjectedLandweberDeconvolutionImageFilter

 itk::simple::RichardsonLucyDeconvolution for the procedural interface


C++ includes: sitkRichardsonLucyDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::GetNumberOfIterations "

Get the number of iterations.

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::RichardsonLucyDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::SetNumberOfIterations "

Set the number of iterations.

";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::STAPLEImageFilter "

The STAPLE filter implements the Simultaneous Truth and Performance
Level Estimation algorithm for generating ground truth volumes from a
set of binary expert segmentations.


The STAPLE algorithm treats segmentation as a pixelwise
classification, which leads to an averaging scheme that accounts for
systematic biases in the behavior of experts in order to generate a
fuzzy ground truth volume and simultaneous accuracy assessment of each
expert. The ground truth volumes produced by this filter are floating
point volumes of values between zero and one that indicate probability
of each pixel being in the object targeted by the segmentation. The
STAPLE algorithm is described in S. Warfield, K. Zou, W. Wells,
\"Validation of image segmentation and expert  quality with an
expectation-maximization algorithm\" in MICCAI 2002: Fifth
International Conference on Medical ImageComputing and Computer-
Assisted Intervention, Springer-Verlag, Heidelberg, Germany, 2002, pp.
298-306INPUTS
Input volumes to the STAPLE filter must be binary segmentations of an
image, that is, there must be a single foreground value that
represents positively classified pixels (pixels that are considered to
belong inside the segmentation). Any number of background pixel values
may be present in the input images. You can, for example, input
volumes with many different labels as long as the structure you are
interested in creating ground truth for is consistently labeled among
all input volumes. Pixel type of the input volumes does not matter.
Specify the label value for positively classified pixels using
SetForegroundValue. All other labels will be considered to be
negatively classified pixels (background). Input volumes must all
contain the same size RequestedRegions.
OUTPUTS
The STAPLE filter produces a single output volume with a range of
floating point values from zero to one. IT IS VERY IMPORTANT TO
INSTANTIATE THIS FILTER WITH A FLOATING POINT OUTPUT TYPE (floats or
doubles). You may threshold the output above some probability
threshold if you wish to produce a binary ground truth.
PARAMETERS
The STAPLE algorithm requires a number of inputs. You may specify any
number of input volumes using the SetInput(i, p_i) method, where i
ranges from zero to N-1, N is the total number of input segmentations,
and p_i is the SmartPointerto the i-th segmentation. The
SetConfidenceWeight parameter is a modifier for the prior probability
that any pixel would be classified as inside the target object. This
implementation of the STAPLE algorithm automatically calculates prior
positive classification probability as the average fraction of the
image volume filled by the target object in each input segmentation.
The ConfidenceWeight parameter allows for scaling the of this default
prior probability: if g_t is the prior probability that a pixel would
be classified inside the target object, then g_t is set to g_t *
ConfidenceWeight before iterating on the solution. In general
ConfidenceWeight should be left to the default of 1.0. You must
provide a foreground value using SetForegroundValue that the STAPLE
algorithm will use to identify positively classified pixels in the the
input images. All other values in the image will be treated as
background values. For example, if your input segmentations consist of
1's everywhere inside the segmented region, then use
SetForegroundValue(1). The STAPLE algorithm is an iterative E-M
algorithm and will converge on a solution after some number of
iterations that cannot be known a priori. After updating the filter,
the total elapsed iterations taken to converge on the solution can be
queried through GetElapsedIterations(). You may also specify a MaximumNumberOfIterations, after which the
algorithm will stop iterating regardless of whether or not it has
converged. This implementation of the STAPLE algorithm will find the
solution to within seven digits of precision unless it is stopped
early. Once updated, the Sensitivity (true positive fraction, q) and
Specificity (true negative fraction, q) for each expert input volume
can be queried using GetSensitivity(i) and GetSpecificity(i), where i
is the i-th input volume.
REQUIRED PARAMETERS
The only required parameters for this filter are the ForegroundValue
and the input volumes. All other parameters may be safely left to
their default values. Please see the paper cited above for more
information on the STAPLE algorithm and its parameters. A proper
understanding of the algorithm is important for interpreting the
results that it produces.
EVENTS
This filter invokes IterationEvent() at each iteration of the E-M
algorithm. Setting the AbortGenerateData() flag will cause the
algorithm to halt after the current iteration and produce results just
as if it had converged. The algorithm makes no attempt to report its
progress since the number of iterations needed cannot be known in
advance.

See:
 itk::simple::STAPLE for the procedural interface


C++ includes: sitkSTAPLEImageFilter.h
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "
";

%feature("docstring")  itk::simple::STAPLEImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetConfidenceWeight "

Scales the estimated prior probability that a pixel will be inside the
targeted object of segmentation. The default prior probability g_t is
calculated automatically as the average fraction of positively
classified pixels to the total size of the volume (across all input
volumes). ConfidenceWeight will scale this default value as g_t = g_t
* ConfidenceWeight. In general, ConfidenceWeight should be left to the
default of 1.0.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetForegroundValue "

Set get the binary ON value of the input image.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetMaximumIterations "

Set/Get the maximum number of iterations after which the STAPLE
algorithm will be considered to have converged. In general this SHOULD
NOT be set and the algorithm should be allowed to converge on its own.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetSensitivity "

After the filter is updated, this method returns a std::vector<double>
of all Sensitivity (true positive fraction, p) values for the expert
input volumes.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::GetSpecificity "

After the filter is updated, this method returns the Specificity (true
negative fraction, q) value for the i-th expert input volume.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::SetConfidenceWeight "

Scales the estimated prior probability that a pixel will be inside the
targeted object of segmentation. The default prior probability g_t is
calculated automatically as the average fraction of positively
classified pixels to the total size of the volume (across all input
volumes). ConfidenceWeight will scale this default value as g_t = g_t
* ConfidenceWeight. In general, ConfidenceWeight should be left to the
default of 1.0.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::SetForegroundValue "

Set get the binary ON value of the input image.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::SetMaximumIterations "

Set/Get the maximum number of iterations after which the STAPLE
algorithm will be considered to have converged. In general this SHOULD
NOT be set and the algorithm should be allowed to converge on its own.

";

%feature("docstring")  itk::simple::STAPLEImageFilter::STAPLEImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::STAPLEImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ScalarConnectedComponentImageFilter "

A connected components filter that labels the objects in an arbitrary
image. Two pixels are similar if they are within threshold of each
other. Uses ConnectedComponentFunctorImageFilter.


Wiki Examples:

All Examples

Label connected components in a grayscale image

See:
 itk::simple::ScalarConnectedComponent for the procedural interface


C++ includes: sitkScalarConnectedComponentImageFilter.h
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::GetDistanceThreshold "
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::ScalarConnectedComponentImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::SetDistanceThreshold "
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::ScalarConnectedComponentImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ScalarImageKmeansImageFilter "

Classifies the intensity values of a scalar image using the K-Means
algorithm.


Given an input image with scalar values, it uses the K-Means
statistical classifier in order to define labels for every pixel in
the image. The filter is templated over the type of the input image.
The output image is predefined as having the same dimension of the
input image and pixel type unsigned char, under the assumption that
the classifier will generate less than 256 classes. You may want to
look also at the RelabelImageFilter that may be used as a
postprocessing stage, in particular if you are interested in ordering
the labels by their relative size in number of pixels.
See:
 Image


ImageKmeansModelEstimator


KdTreeBasedKmeansEstimator, WeightedCentroidKdTreeGenerator, KdTree


RelabelImageFilter
Wiki Examples:

All Examples

Cluster the pixels in a greyscale image

See:
 itk::simple::ScalarImageKmeans for the procedural interface


C++ includes: sitkScalarImageKmeansImageFilter.h
";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::GetClassWithInitialMean "
";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::GetFinalMeans "

*


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::GetUseNonContiguousLabels "

Set/Get the UseNonContiguousLabels flag. When this is set to false the
labels are numbered contiguously, like in {0,1,3..N}. When the flag is
set to true, the labels are selected in order to span the dynamic
range of the output image. This last option is useful when the output
image is intended only for display. The default value is false.

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::ScalarImageKmeansImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::SetClassWithInitialMean "
";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::SetUseNonContiguousLabels "

Set/Get the UseNonContiguousLabels flag. When this is set to false the
labels are numbered contiguously, like in {0,1,3..N}. When the flag is
set to true, the labels are selected in order to span the dynamic
range of the output image. This last option is useful when the output
image is intended only for display. The default value is false.

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::UseNonContiguousLabelsOff "
";

%feature("docstring")  itk::simple::ScalarImageKmeansImageFilter::UseNonContiguousLabelsOn "

Set the value of UseNonContiguousLabels to true or false respectfully.

";


%feature("docstring") itk::simple::ScalarToRGBColormapImageFilter "

Implements pixel-wise intensity->rgb mapping operation on one image.


This class is parameterized over the type of the input image and the
type of the output image. The input image's scalar pixel values are
mapped into a color map. The color map is specified by passing the
SetColormap function one of the predefined maps. The following selects
the \"Hot\" colormap:RGBFilterType::PointercolormapImageFilter= RGBFil
terType::New();colormapImageFilter->SetColormap(RGBFilterType::Hot);
You can also specify a custom color map. This is done by creating a
CustomColormapFunction, and then creating lists of values for the red,
green, and blue channel. An example of setting the red channel of a
colormap with only 2 colors is given below. The blue and green
channels should be specified in the same manner.
Createthecustomcolormaptypedef itk::Function::CustomColormapFunction<R
ealImageType::PixelType,RGBImageType::PixelType> ColormapType;
ColormapType::Pointercolormap= ColormapType::New();//Setuptheredchanne
lofthecolormapColormapTypeChannelTyperedChannel;redChannel.push_back(0
);redChannel.push_back(255);colormap->SetRedChannel(channel); The
range of values present in the input image is the range that is mapped
to the entire range of colors. This code was contributed in the
Insight Journal paper: \"Meeting Andy Warhol Somewhere Over the
Rainbow: RGB Colormapping and ITK\" by Tustison N., Zhang H., Lehmann
G., Yushkevich P., Gee J.http://hdl.handle.net/1926/1452http://www
.insight-journal.org/browse/publication/285
See:
BinaryFunctionImageFilter TernaryFunctionImageFilter
Wiki Examples:

All Examples

Apply a color map to an image

See:
 itk::simple::ScalarToRGBColormap for the procedural interface


C++ includes: sitkScalarToRGBColormapImageFilter.h
";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::GetColormap "

Set/Get the colormap object.

";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::ScalarToRGBColormapImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::SetColormap "
";

%feature("docstring")  itk::simple::ScalarToRGBColormapImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ShanbhagThresholdImageFilter "

Threshold an image using the Shanbhag Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the ShanbhagThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::ShanbhagThreshold for the procedural interface


C++ includes: sitkShanbhagThresholdImageFilter.h
";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::ShanbhagThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ShanbhagThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ShapeDetectionLevelSetImageFilter "

Segments structures in images based on a user supplied edge potential
map.


IMPORTANT
The SegmentationLevelSetImageFilterclass and the
ShapeDetectionLevelSetFunctionclass contain additional information
necessary to gain full understanding of how to use this filter.
OVERVIEW
This class is a level set method segmentation filter. An initial
contour is propagated outwards (or inwards) until it ''sticks'' to the
shape boundaries. This is done by using a level set speed function
based on a user supplied edge potential map. This approach for
segmentation follows that of Malladi et al (1995).
INPUTS
This filter requires two inputs. The first input is a initial level
set. The initial level set is a real image which contains the initial
contour/surface as the zero level set. For example, a signed distance
function from the initial contour/surface is typically used. Note that
for this algorithm the initial contour has to be wholly within (or
wholly outside) the structure to be segmented.
The second input is the feature image. For this filter, this is the
edge potential map. General characteristics of an edge potential map
is that it has values close to zero in regions near the edges and
values close to one inside the shape itself. Typically, the edge
potential map is compute from the image gradient, for example:
 \\\\[ g(I) = 1 / ( 1 + | (\\\\nabla * G)(I)| ) \\\\] \\\\[ g(I) = \\\\exp^{-|(\\\\nabla * G)(I)|} \\\\] where $ I $ is image intensity and $ (\\\\nabla * G) $ is the derivative of Gaussian operator.
See SegmentationLevelSetImageFilterand
SparseFieldLevelSetImageFilterfor more information on Inputs.
PARAMETERS
The PropagationScaling parameter can be used to switch from
propagation outwards (POSITIVE scaling parameter) versus propagating
inwards (NEGATIVE scaling parameter). The smoothness of the resulting
contour/surface can be adjusted using a combination of
PropagationScaling and CurvatureScaling parameters. The larger the
CurvatureScaling parameter, the smoother the resulting contour. The
CurvatureScaling parameter should be non-negative for proper operation
of this algorithm. To follow the implementation in Malladi et al
paper, set the PropagtionScaling to $\\\\pm 1.0$ and CurvatureScaling to $ \\\\epsilon $ . Note that there is no advection term for this filter. Setting the
advection scaling will have no effect.
OUTPUTS
The filter outputs a single, scalar, real-valued image. Negative
values in the output image represent the inside of the segmentated
region and positive values in the image represent the outside of the
segmented region. The zero crossings of the image correspond to the
position of the propagating front.
See SparseFieldLevelSetImageFilterand
SegmentationLevelSetImageFilterfor more information.
REFERENCES
Shape Modeling with Front Propagation: A Level Set Approach
, R. Malladi, J. A. Sethian and B. C. Vermuri. IEEE Trans. on Pattern
Analysis and Machine Intelligence, Vol 17, No. 2, pp 158-174, February
1995

See:
SegmentationLevelSetImageFilter


ShapeDetectionLevelSetFunction


SparseFieldLevelSetImageFilter

 itk::simple::ShapeDetectionLevelSet for the procedural interface


C++ includes: sitkShapeDetectionLevelSetImageFilter.h
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetCurvatureScaling "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetMaximumRMSError "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetPropagationScaling "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::GetRMSChange "

The Root Mean Square of the levelset upon termination.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::ReverseExpansionDirectionOff "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::ReverseExpansionDirectionOn "

Set the value of ReverseExpansionDirection to true or false
respectfully.

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::SetCurvatureScaling "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::SetMaximumRMSError "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::SetPropagationScaling "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::SetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::ShapeDetectionLevelSetImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ShapeDetectionLevelSetImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ShiftScaleImageFilter "

Shift and scale the pixels in an image.


ShiftScaleImageFiltershifts the input pixel by Shift (default 0.0) and
then scales the pixel by Scale (default 1.0). All computattions are
performed in the precison of the input pixel's RealType. Before
assigning the computed value to the output pixel, the value is clamped
at the NonpositiveMin and max of the pixel type.


See:
 itk::simple::ShiftScale for the procedural interface


C++ includes: sitkShiftScaleImageFilter.h
";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::GetScale "

Set/Get the amount to Scale each Pixel. The Scale is applied after the
Shift.

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::GetShift "

Set/Get the amount to Shift each Pixel. The shift is followed by a
Scale.

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::SetScale "

Set/Get the amount to Scale each Pixel. The Scale is applied after the
Shift.

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::SetShift "

Set/Get the amount to Shift each Pixel. The shift is followed by a
Scale.

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::ShiftScaleImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ShiftScaleImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ShrinkImageFilter "

Reduce the size of an image by an integer factor in each dimension.


ShrinkImageFilterreduces the size of an image by an integer factor in
each dimension. The algorithm implemented is a simple subsample. The output image size in each dimension is given by:
outputSize[j] = max( vcl_floor(inputSize[j]/shrinkFactor[j]), 1 );
NOTE: The physical centers of the input and output will be the same.
Because of this, the Origin of the output may not be the same as the
Origin of the input. Since this filter produces an image which is a
different resolution, origin and with different pixel spacing than its
input image, it needs to override several of the methods defined in
ProcessObjectin order to properly manage the pipeline execution model.
In particular, this filter overrides
ProcessObject::GenerateInputRequestedRegion()and
ProcessObject::GenerateOutputInformation(). This filter is implemented
as a multithreaded filter. It provides a ThreadedGenerateData()method
for its implementation.Wiki Examples:

All Examples

Shrink an image

See:
 itk::simple::Shrink for the procedural interface


C++ includes: sitkShrinkImageFilter.h
";

%feature("docstring")  itk::simple::ShrinkImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ShrinkImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ShrinkImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ShrinkImageFilter::GetShrinkFactors "

Get the shrink factors.

";

%feature("docstring")  itk::simple::ShrinkImageFilter::SetShrinkFactor "

Custom public declarations

";

%feature("docstring")  itk::simple::ShrinkImageFilter::SetShrinkFactors "

Set the shrink factors. Values are clamped to a minimum value of 1.
Default is 1 for all dimensions.

";

%feature("docstring")  itk::simple::ShrinkImageFilter::ShrinkImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ShrinkImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SigmoidImageFilter "

Computes the sigmoid function pixel-wise.


A linear transformation is applied first on the argument of the
sigmoid fuction. The resulting total transfrom is given by \\\\[ f(x) = (Max-Min) \\\\cdot \\\\frac{1}{\\\\left(1+e^{- \\\\frac{
x - \\\\beta }{\\\\alpha}}\\\\right)} + Min \\\\] Every output pixel is equal to f(x). Where x is the intensity of the
homologous input pixel, and alpha and beta are user-provided
constants.Wiki Examples:

All Examples

Pass image pixels through a sigmoid function

See:
 itk::simple::Sigmoid for the procedural interface


C++ includes: sitkSigmoidImageFilter.h
";

%feature("docstring")  itk::simple::SigmoidImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SigmoidImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SigmoidImageFilter::GetAlpha "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::GetBeta "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SigmoidImageFilter::GetOutputMaximum "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::GetOutputMinimum "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::SetAlpha "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::SetBeta "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::SetOutputMaximum "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::SetOutputMinimum "
";

%feature("docstring")  itk::simple::SigmoidImageFilter::SigmoidImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SigmoidImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SignedDanielssonDistanceMapImageFilter "

This class is parametrized over the type of the input image and the
type of the output image. This filter computes the distance map of the
input image as an approximation with pixel accuracy to the Euclidean
distance. For purposes of evaluating the signed distance map, the
input is assumed to be binary composed of pixels with value 0 and non-
zero. The inside is considered as having negative distances. Outside
is treated as having positive distances. To change the convention, use
the InsideIsPositive(bool) function. As a convention, the distance is
evaluated from the boundary of the ON pixels. The filter returns.



A signed distance map with the approximation to the euclidean
distance.

A voronoi partition. (See itkDanielssonDistanceMapImageFilter)

A vector map containing the component of the vector relating the
current pixel with the closest point of the closest object to this
pixel. Given that the components of the distance are computed in
\"pixels\", the vector is represented by an itk::Offset. That is,
physical coordinates are not used. (See
itkDanielssonDistanceMapImageFilter)
 This filter internally uses the DanielssonDistanceMap filter. This
filter is N-dimensional.
See:
itkDanielssonDistanceMapImageFilter

 itk::simple::SignedDanielssonDistanceMap for the procedural interface


C++ includes: sitkSignedDanielssonDistanceMapImageFilter.h
";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::GetInsideIsPositive "

Get if the inside represents positive values in the signed distance
map. See GetInsideIsPositive().

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::GetSquaredDistance "

Get the distance squared.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::GetUseImageSpacing "

Get whether spacing is used.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::InsideIsPositiveOff "
";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::InsideIsPositiveOn "

Set the value of InsideIsPositive to true or false respectfully.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SetInsideIsPositive "

Set if the inside represents positive values in the signed distance
map. By convention ON pixels are treated as inside pixels.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SetSquaredDistance "

Set if the distance should be squared.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SetUseImageSpacing "

Set if image spacing should be used in computing distances.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SignedDanielssonDistanceMapImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SquaredDistanceOff "
";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::SquaredDistanceOn "

Set the value of SquaredDistance to true or false respectfully.

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMapImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::SignedMaurerDistanceMapImageFilter "

This filter calculates the Euclidean distance transform of a binary
image in linear time for arbitrary dimensions.


Inputs and Outputs
This is an image-to-image filter. The dimensionality is arbitrary. The
only dimensionality constraint is that the input and output images be
of the same dimensions and size. To maintain integer arithmetic within
the filter, the default output is the signed squared distance. This
implies that the input image should be of type \"unsigned int\" or
\"int\" whereas the output image is of type \"int\". Obviously, if the
user wishes to utilize the image spacing or to have a filter with the
Euclidean distance (as opposed to the squared distance), output image
types of float or double should be used. The inside is considered as
having negative distances. Outside is treated as having positive
distances. To change the convention, use the InsideIsPositive(bool)
function.
Parameters
Set/GetBackgroundValue specifies the background of the value of the
input binary image. Normally this is zero and, as such, zero is the
default value. Other than that, the usage is completely analogous to
the itk::DanielssonDistanceImageFilter class except it does not return
the Voronoi map. Reference: C. R. Maurer, Jr., R. Qi, and V. Raghavan,
\"A Linear Time Algorithm for Computing Exact Euclidean Distance
Transforms of Binary Images in Arbitrary Dimensions\", IEEE -
Transactions on Pattern Analysis and Machine Intelligence, 25(2):
265-270, 2003.

See:
 itk::simple::SignedMaurerDistanceMap for the procedural interface


C++ includes: sitkSignedMaurerDistanceMapImageFilter.h
";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::GetInsideIsPositive "

Get if the inside represents positive values in the signed distance
map.



See:
 GetInsideIsPositive()


";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::GetSquaredDistance "

Get the distance squared.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::GetUseImageSpacing "

Get whether spacing is used.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::InsideIsPositiveOff "
";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::InsideIsPositiveOn "

Set the value of InsideIsPositive to true or false respectfully.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SetInsideIsPositive "

Set if the inside represents positive values in the signed distance
map. By convention ON pixels are treated as inside pixels.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SetSquaredDistance "

Set if the distance should be squared.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SetUseImageSpacing "

Set if image spacing should be used in computing distances.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SignedMaurerDistanceMapImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SquaredDistanceOff "
";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::SquaredDistanceOn "

Set the value of SquaredDistance to true or false respectfully.

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::UseImageSpacingOff "
";

%feature("docstring")  itk::simple::SignedMaurerDistanceMapImageFilter::UseImageSpacingOn "

Set the value of UseImageSpacing to true or false respectfully.

";


%feature("docstring") itk::simple::SimilarityIndexImageFilter "

Measures the similarity between the set of non-zero pixels of two
images.


SimilarityIndexImageFiltermeasures the similarity between the set non-
zero pixels of two images using the following formula: \\\\[ S = \\\\frac{2 | A \\\\cap B |}{|A| + |B|} \\\\] where $A$ and $B$ are respectively the set of non-zero pixels in the first and second
input images. Operator $|\\\\cdot|$ represents the size of a set and $\\\\cap$ represents the intersection of two sets. The measure is derived from
a reliability measure known as the kappa statistic. $S$ is sensitive to both differences in size and in location and have
been in the literature for comparing two segmentation masks. For more
information see: \"Morphometric Analysis of White Matter Lesions in MR
Images: Method and  Validation\", A. P. Zijdenbos, B. M. Dawant, R. A.
Margolin and A. C. Palmer, IEEE Trans. on Medical Imaging, 13(4) pp
716-724,1994 This filter requires the largest possible region of the
first image and the same corresponding region in the second image. It
behaves as filter with two input and one output. Thus it can be
inserted in a pipeline with other filters. The filter passes the first
input through unmodified. This filter is templated over the two input
image type. It assume both image have the same number of dimensions.


See:
 itk::simple::SimilarityIndex for the procedural interface


C++ includes: sitkSimilarityIndexImageFilter.h
";

%feature("docstring")  itk::simple::SimilarityIndexImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::SimilarityIndexImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SimilarityIndexImageFilter::GetSimilarityIndex "

*


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::SimilarityIndexImageFilter::SimilarityIndexImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SimilarityIndexImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SimpleContourExtractorImageFilter "

Computes an image of contours which will be the contour of the first
image.


A pixel of the source image is considered to belong to the contour if
its pixel value is equal to the input foreground value and it has in
its neighborhood at least one pixel which its pixel value is equal to
the input background value. The output image will have pixels which
will be set to the output foreground value if they belong to the
contour, otherwise they will be set to the ouput background value. The
neighborhood \"radius\" is set thanks to the radius params.
See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::SimpleContourExtractor for the procedural interface


C++ includes: sitkSimpleContourExtractorImageFilter.h
";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetInputBackgroundValue "

Get the background value used in order to identify a background pixel
in the input image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetInputForegroundValue "

Get the foreground value used in order to identify a foreground pixel
in the input image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetOutputBackgroundValue "

Get the background value used in order to identify a background pixel
in the output image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetOutputForegroundValue "

Get the foreground value used in order to identify a foreground pixel
in the output image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetInputBackgroundValue "

Set the background value used in order to identify a background pixel
in the input image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetInputForegroundValue "

Set the foreground value used in order to identify a foreground pixel
in the input image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetOutputBackgroundValue "

Set the background value used in order to identify a background pixel
in the output image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetOutputForegroundValue "

Set the foreground value used in order to identify a foreground pixel
in the output image.

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::SimpleContourExtractorImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SimpleContourExtractorImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SinImageFilter "

Computes the sine of each pixel.


The computations are performed using vcl_sin(x).Wiki Examples:

All Examples

Compute the sine of each pixel.

See:
 itk::simple::Sin for the procedural interface


C++ includes: sitkSinImageFilter.h
";

%feature("docstring")  itk::simple::SinImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SinImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SinImageFilter::SinImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SinImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SliceImageFilter "


See:
 itk::simple::Slice for the procedural interface


C++ includes: sitkSliceImageFilter.h
";

%feature("docstring")  itk::simple::SliceImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SliceImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SliceImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SliceImageFilter::GetStart "
";

%feature("docstring")  itk::simple::SliceImageFilter::GetStep "
";

%feature("docstring")  itk::simple::SliceImageFilter::GetStop "
";

%feature("docstring")  itk::simple::SliceImageFilter::SetStart "
";

%feature("docstring")  itk::simple::SliceImageFilter::SetStep "
";

%feature("docstring")  itk::simple::SliceImageFilter::SetStop "
";

%feature("docstring")  itk::simple::SliceImageFilter::SliceImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SliceImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter "

Computes the smoothing of an image by convolution with the Gaussian
kernels implemented as IIR filters.


This filter is implemented using the recursive gaussian filters. For
multi-component images, the filter works on each component
independently. For this filter to be able to run in-place the input
and output image types need to be the same and/or the same type as the
RealImageType.Wiki Examples:

All Examples

Gaussian smoothing that works with image adaptors

See:
 itk::simple::SmoothingRecursiveGaussian for the procedural interface


C++ includes: sitkSmoothingRecursiveGaussianImageFilter.h
";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::GetNormalizeAcrossScale "

This method does not effect the output of this filter.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::GetSigma "
";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::NormalizeAcrossScaleOff "
";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::NormalizeAcrossScaleOn "

Set the value of NormalizeAcrossScale to true or false respectfully.

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::SetNormalizeAcrossScale "

This method does not effect the output of this filter.



See:
 RecursiveGaussianImageFilter::SetNormalizeAcrossScale


";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::SetSigma "

Set Sigma value. Sigma is measured in the units of image spacing. You
may use the method SetSigma to set the same value across each axis or
use the method SetSigmaArray if you need different values along each
axis.

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::SmoothingRecursiveGaussianImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussianImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SobelEdgeDetectionImageFilter "

A 2D or 3D edge detection using the Sobel operator.


This filter uses the Sobel operator to calculate the image gradient
and then finds the magnitude of this gradient vector. The Sobel
gradient magnitude (square-root sum of squares) is an indication of
edge strength.
See:
ImageToImageFilter


SobelOperator


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

 SobelEdgeDetectionImageFilter

See:
 itk::simple::SobelEdgeDetection for the procedural interface


C++ includes: sitkSobelEdgeDetectionImageFilter.h
";

%feature("docstring")  itk::simple::SobelEdgeDetectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SobelEdgeDetectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SobelEdgeDetectionImageFilter::SobelEdgeDetectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SobelEdgeDetectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SqrtImageFilter "

Computes the square root of each pixel.


The computations are performed using vcl_sqrt(x).


See:
 itk::simple::Sqrt for the procedural interface


C++ includes: sitkSqrtImageFilter.h
";

%feature("docstring")  itk::simple::SqrtImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SqrtImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SqrtImageFilter::SqrtImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SqrtImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SquareImageFilter "

Computes the square of the intensity values pixel-wise.


Wiki Examples:

All Examples

Square every pixel in an image

See:
 itk::simple::Square for the procedural interface


C++ includes: sitkSquareImageFilter.h
";

%feature("docstring")  itk::simple::SquareImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SquareImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SquareImageFilter::SquareImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SquareImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SquaredDifferenceImageFilter "

Implements pixel-wise the computation of squared difference.


This filter is parametrized over the types of the two input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults. The filter will walk over all the pixels in the
two input images, and for each one of them it will do the following:


cast the input 1 pixel value to double

cast the input 2 pixel value to double

compute the difference of the two pixel values

compute the square of the difference

cast the double value resulting from sqr() to the pixel type of the
output image

store the casted value into the output image.
 The filter expect all images to have the same dimension (e.g. all 2D,
or all 3D, or all ND)Wiki Examples:

All Examples

Compute the squared difference of corresponding pixels in two images

See:
 itk::simple::SquaredDifference for the procedural interface


C++ includes: sitkSquaredDifferenceImageFilter.h
";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::Execute "
";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::SquaredDifferenceImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SquaredDifferenceImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::StandardDeviationProjectionImageFilter "

Mean projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
The original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MeanProjectionImageFilter


 SumProjectionImageFilter


 MeanProjectionImageFilter


 MaximumProjectionImageFilter


 MinimumProjectionImageFilter


 BinaryProjectionImageFilter

 itk::simple::StandardDeviationProjection for the procedural interface


C++ includes: sitkStandardDeviationProjectionImageFilter.h
";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::StandardDeviationProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::StandardDeviationProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::StatisticsImageFilter "

Compute min, max, variance, and mean of an image.



See:
 itk::simple::Statistics for the procedural interface


C++ includes: sitkStatisticsImageFilter.h
";

%feature("docstring")  itk::simple::StatisticsImageFilter::Execute "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetMaximum "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetMean "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetMeasurementMap "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetMinimum "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetSigma "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetSum "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::GetVariance "
";

%feature("docstring")  itk::simple::StatisticsImageFilter::StatisticsImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::StatisticsImageFilter::ToString "
";


%feature("docstring") itk::simple::SubtractImageFilter "

Pixel-wise subtraction of two images.


Subtract each pixel from image2 from its corresponding pixel in
image1: Output=Input1-Input2. This is done using SetInput1(image1);
SetInput2(image2); This class is templated over the types of the two
input images and the type of the output image. Numeric conversions
(castings) are done by the C++ defaults. Additionally, a constant can
be subtracted from every pixel in an image using: SetInput1(image1);
SetConstant2(constant);
The result of AddImageFilterwith a negative constant is not
necessarily the same as SubtractImageFilter. This would be the case when the PixelType defines an operator-()that is not the inverse of operator+()
Wiki Examples:

All Examples

Subtract two images

Subtract a constant from every pixel in an image

See:
 itk::simple::Subtract for the procedural interface


C++ includes: sitkSubtractImageFilter.h
";

%feature("docstring")  itk::simple::SubtractImageFilter::Execute "
";

%feature("docstring")  itk::simple::SubtractImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::SubtractImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::SubtractImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SubtractImageFilter::SubtractImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SubtractImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::SumProjectionImageFilter "

Sum projection.


This class was contributed to the Insight Journal by Gaetan Lehmann.
The original paper can be found athttp://hdl.handle.net/1926/164
Gaetan Lehmann. Biologie du Developpement et de la Reproduction , INRA
de Jouy-en-Josas, France.

See:
ProjectionImageFilter


 MedianProjectionImageFilter


 MeanProjectionImageFilter


 MeanProjectionImageFilter


 MaximumProjectionImageFilter


 MinimumProjectionImageFilter


 BinaryProjectionImageFilter


 StandardDeviationProjectionImageFilter

 itk::simple::SumProjection for the procedural interface


C++ includes: sitkSumProjectionImageFilter.h
";

%feature("docstring")  itk::simple::SumProjectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::SumProjectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::SumProjectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::SumProjectionImageFilter::GetProjectionDimension "
";

%feature("docstring")  itk::simple::SumProjectionImageFilter::SetProjectionDimension "
";

%feature("docstring")  itk::simple::SumProjectionImageFilter::SumProjectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::SumProjectionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TanImageFilter "

Computes the tangent of each input pixel.


The computations are performed using vcl_tan(x).


See:
 itk::simple::Tan for the procedural interface


C++ includes: sitkTanImageFilter.h
";

%feature("docstring")  itk::simple::TanImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::TanImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TanImageFilter::TanImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TanImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TernaryAddImageFilter "

Pixel-wise addition of three images.


This class is templated over the types of the three input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults.


See:
 itk::simple::TernaryAdd for the procedural interface


C++ includes: sitkTernaryAddImageFilter.h
";

%feature("docstring")  itk::simple::TernaryAddImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::TernaryAddImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TernaryAddImageFilter::TernaryAddImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TernaryAddImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TernaryMagnitudeImageFilter "

Pixel-wise addition of three images.


This class is templated over the types of the three input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults.


See:
 itk::simple::TernaryMagnitude for the procedural interface


C++ includes: sitkTernaryMagnitudeImageFilter.h
";

%feature("docstring")  itk::simple::TernaryMagnitudeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::TernaryMagnitudeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TernaryMagnitudeImageFilter::TernaryMagnitudeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TernaryMagnitudeImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TernaryMagnitudeSquaredImageFilter "

Pixel-wise addition of three images.


This class is templated over the types of the three input images and
the type of the output image. Numeric conversions (castings) are done
by the C++ defaults.


See:
 itk::simple::TernaryMagnitudeSquared for the procedural interface


C++ includes: sitkTernaryMagnitudeSquaredImageFilter.h
";

%feature("docstring")  itk::simple::TernaryMagnitudeSquaredImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::TernaryMagnitudeSquaredImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TernaryMagnitudeSquaredImageFilter::TernaryMagnitudeSquaredImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TernaryMagnitudeSquaredImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ThresholdImageFilter "

Set image values to a user-specified value if they are below, above,
or between simple threshold values.


ThresholdImageFiltersets image values to a user-specified \"outside\"
value (by default, \"black\") if the image values are below, above, or
between simple threshold values. The pixels must support the operators >= and <=.Wiki Examples:

All Examples

Threshold an image

See:
 itk::simple::Threshold for the procedural interface


C++ includes: sitkThresholdImageFilter.h
";

%feature("docstring")  itk::simple::ThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ThresholdImageFilter::GetLower "

Set/Get methods to set the lower threshold.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::GetUpper "

Set/Get methods to set the upper threshold.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::SetLower "

Set/Get methods to set the lower threshold.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::SetOutsideValue "

End concept checking Set the \"outside\" pixel value. The default
value NumericTraits<PixelType>::Zero.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::SetUpper "

Set/Get methods to set the upper threshold.

";

%feature("docstring")  itk::simple::ThresholdImageFilter::ThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ThresholdImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ThresholdMaximumConnectedComponentsImageFilter "

Finds the threshold value of an image based on maximizing the number
of objects in the image that are larger than a given minimal size.


This method is based on Topological Stable State Thresholding to
calculate the threshold set point. This method is particularly
effective when there are a large number of objects in a microscopy
image. Compiling in Debug mode and enable the debug flag for this
filter to print debug information to see how the filter focuses in on
a threshold value. Please see the Insight Journal's MICCAI 2005
workshop for a complete description. References are below.
Parameters
The MinimumObjectSizeInPixels parameter is controlled through the
class Get/SetMinimumObjectSizeInPixels() method. Similar to the
standard itk::BinaryThresholdImageFilterthe Get/SetInside and
Get/SetOutside values of the threshold can be set. The
GetNumberOfObjects()and GetThresholdValue()methods return the number
of objects above the minimum pixel size and the calculated threshold
value.
Automatic Thresholding in ITK
There are multiple methods to automatically calculate the threshold
intensity value of an image. As of version 4.0, ITK has a Thresholding
( ITKThresholding ) module which contains numerous automatic
thresholding methods.implements two of these. Topological Stable State
Thresholding works well on images with a large number of objects to be
counted.
References:
1) Urish KL, August J, Huard J. \"Unsupervised segmentation for
myofiber  counting in immunoflourescent images\". Insight Journal. ISC
/NA-MIC/MICCAI Workshop on Open-Source Software (2005) Dspace
handle:http://hdl.handle.net/1926/482) Pikaz A, Averbuch, A. \"Digital
image thresholding based on topological  stable-state\". Pattern
Recognition, 29(5): 829-843, 1996.
Questions: email Ken Urish at ken.urish(at)gmail.com Please cc the itk
list serve for archival purposes.

See:
 itk::simple::ThresholdMaximumConnectedComponents for the procedural interface


C++ includes: sitkThresholdMaximumConnectedComponentsImageFilter.h
";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::GetInsideValue "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::GetMinimumObjectSizeInPixels "

Set the minimum pixel area used to count objects on the image. Thus,
only objects that have a pixel area greater than the minimum pixel
area will be counted as an object in the optimization portion of this
filter. Essentially, it eliminates noise from being counted as an
object. The default value is zero.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::GetOutsideValue "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::GetUpperBoundary "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::SetInsideValue "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::SetMinimumObjectSizeInPixels "

Set the minimum pixel area used to count objects on the image. Thus,
only objects that have a pixel area greater than the minimum pixel
area will be counted as an object in the optimization portion of this
filter. Essentially, it eliminates noise from being counted as an
object. The default value is zero.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::SetOutsideValue "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::SetUpperBoundary "

The following Set/Get methods are for the binary threshold function.
This class automatically calculates the lower threshold boundary. The
upper threshold boundary, inside value, and outside value can be
defined by the user, however the standard values are used as default
if not set by the user. The default value of the: Inside value is the
maximum pixel type intensity. Outside value is the minimum pixel type
intensity. Upper threshold boundary is the maximum pixel type
intensity.

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::ThresholdMaximumConnectedComponentsImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponentsImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::ThresholdSegmentationLevelSetImageFilter "

Segments structures in images based on intensity values.


IMPORTANT
The SegmentationLevelSetImageFilterclass and the
ThresholdSegmentationLevelSetFunctionclass contain additional
information necessary to the full understanding of how to use this
filter.
OVERVIEW
This class is a level set method segmentation filter. It constructs a
speed function which is close to zero at the upper and lower bounds of
an intensity window, effectively locking the propagating front onto
those edges. Elsewhere, the front will propagate quickly.
INPUTS
This filter requires two inputs. The first input is a seed image. This
seed image must contain an isosurface that you want to use as the seed
for your segmentation. It can be a binary, graylevel, or floating
point image. The only requirement is that it contain a closed
isosurface that you will identify as the seed by setting the
IsosurfaceValue parameter of the filter. For a binary image you will
want to set your isosurface value halfway between your on and off
values (i.e. for 0's and 1's, use an isosurface value of 0.5).
The second input is the feature image. This is the image from which
the speed function will be calculated. For most applications, this is
the image that you want to segment. The desired isosurface in your
seed image should lie within the region of your feature image that you
are trying to segment. Note that this filter does no preprocessing of
the feature image before thresholding.
See SegmentationLevelSetImageFilterfor more information on Inputs.
OUTPUTS
The filter outputs a single, scalar, real-valued image. Positive
values in the output image are inside the segmentated region and
negative values in the image are outside of the inside region. The
zero crossings of the image correspond to the position of the level
set front.
See SparseFieldLevelSetImageFilterand
SegmentationLevelSetImageFilterfor more information.
PARAMETERS
In addition to parameters described in
SegmentationLevelSetImageFilter, this filter adds the UpperThreshold
and LowerThreshold. See ThresholdSegmentationLevelSetFunctionfor a
description of how these values affect the segmentation.

See:
SegmentationLevelSetImageFilter


ThresholdSegmentationLevelSetFunction,


SparseFieldLevelSetImageFilter

 itk::simple::ThresholdSegmentationLevelSet for the procedural interface


C++ includes: sitkThresholdSegmentationLevelSetImageFilter.h
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetCurvatureScaling "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetElapsedIterations "

Number of iterations run.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetLowerThreshold "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetMaximumRMSError "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetNumberOfIterations "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetPropagationScaling "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetRMSChange "

The Root Mean Square of the levelset upon termination.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::GetUpperThreshold "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::ReverseExpansionDirectionOff "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::ReverseExpansionDirectionOn "

Set the value of ReverseExpansionDirection to true or false
respectfully.

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetCurvatureScaling "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetLowerThreshold "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetMaximumRMSError "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetNumberOfIterations "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetPropagationScaling "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetReverseExpansionDirection "
";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::SetUpperThreshold "

Get/Set the threshold values that will be used to calculate the speed
function.

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::ThresholdSegmentationLevelSetImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSetImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TikhonovDeconvolutionImageFilter "

An inverse deconvolution filter regularized in the Tikhonov sense.


The Tikhonov deconvolution filter is the inverse deconvolution filter
with a regularization term added to the denominator. The filter
minimizes the equation \\\\[ ||\\\\hat{f} \\\\otimes h - g||_{L_2}^2 + \\\\mu||\\\\hat{f}||^2
\\\\] where $\\\\hat{f}$ is the estimate of the unblurred image, $h$ is the blurring kernel, $g$ is the blurred image, and $\\\\mu$ is a non-negative real regularization function. The filter applies a
kernel described in the Fourier domain as $H^*(\\\\omega) / (|H(\\\\omega)|^2 + \\\\mu)$ where $H(\\\\omega)$ is the Fourier transform of $h$ . The term $\\\\mu$ is called RegularizationConstant in this filter. If $\\\\mu$ is set to zero, this filter is equivalent to the InverseDeconvolutionImageFilter.
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Cory Quammen, The University of North
Carolina at Chapel Hill

See:
 itk::simple::TikhonovDeconvolution for the procedural interface


C++ includes: sitkTikhonovDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::GetRegularizationConstant "

The regularization factor. Larger values reduce the dominance of noise
in the solution, but results in higher approximation error in the
deblurred image. Default value is 0.0, yielding the same results as
the InverseDeconvolutionImageFilter.

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::SetRegularizationConstant "

The regularization factor. Larger values reduce the dominance of noise
in the solution, but results in higher approximation error in the
deblurred image. Default value is 0.0, yielding the same results as
the InverseDeconvolutionImageFilter.

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::TikhonovDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TikhonovDeconvolutionImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::TileImageFilter "

Tile multiple input images into a single output image.


This filter will tile multiple images using a user-specified layout.
The tile sizes will be large enough to accommodate the largest image
for each tile. The layout is specified with the SetLayout method. The
layout has the same dimension as the output image. If all entries of
the layout are positive, the tiled output will contain the exact
number of tiles. If the layout contains a 0 in the last dimension, the
filter will compute a size that will accommodate all of the images.
Empty tiles are filled with the value specified with the SetDefault
value method. The input images must have a dimension less than or
equal to the output image. The output image have a larger dimension
than the input images. This filter can be used to create a volume from
a series of inputs by specifying a layout of 1,1,0.Wiki Examples:

All Examples

Tile multiple images into another image

Stack multiple 2D images into a 3D image

Tile multiple images side by side

See:
 itk::simple::Tile for the procedural interface


C++ includes: sitkTileImageFilter.h
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "
";

%feature("docstring")  itk::simple::TileImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::TileImageFilter::GetDefaultPixelValue "
";

%feature("docstring")  itk::simple::TileImageFilter::GetLayout "
";

%feature("docstring")  itk::simple::TileImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TileImageFilter::SetDefaultPixelValue "
";

%feature("docstring")  itk::simple::TileImageFilter::SetLayout "
";

%feature("docstring")  itk::simple::TileImageFilter::TileImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";

%feature("docstring")  itk::simple::TileImageFilter::ToString "

Print ourselves out

";


%feature("docstring") itk::simple::Transform "
C++ includes: sitkTransform.h
";

%feature("docstring")  itk::simple::Transform::AddTransform "
";

%feature("docstring")  itk::simple::Transform::GetDimension "

Return the dimension of the Transform ( 2D or 3D )

";

%feature("docstring")  itk::simple::Transform::ToString "
";

%feature("docstring")  itk::simple::Transform::Transform "

Construct a specific transformation.

";

%feature("docstring")  itk::simple::Transform::Transform "

Construct a SimpleITK Transform from a pointer to an ITK composite transform.

";

%feature("docstring")  itk::simple::Transform::Transform "

By default a 3-d identity transform is constructed.

";

%feature("docstring")  itk::simple::Transform::TransformPoint "
";

%feature("docstring")  itk::simple::Transform::WriteTransform "
";

%feature("docstring")  itk::simple::Transform::~Transform "
";


%feature("docstring") itk::simple::TriangleThresholdImageFilter "

Threshold an image using the Triangle Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the TriangleThresholdCalculatorand applies that
theshold to the input image using the BinaryThresholdImageFilter.
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia. Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::TriangleThreshold for the procedural interface


C++ includes: sitkTriangleThresholdImageFilter.h
";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::TriangleThresholdImageFilter::TriangleThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::UnaryMinusImageFilter "

Computes the negative of each pixel.



See:
 itk::simple::UnaryMinus for the procedural interface


C++ includes: sitkUnaryMinusImageFilter.h
";

%feature("docstring")  itk::simple::UnaryMinusImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::UnaryMinusImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::UnaryMinusImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::UnaryMinusImageFilter::UnaryMinusImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::ValuedRegionalMaximaImageFilter "

Transforms the image so that any pixel that is not a regional maxima
is set to the minimum value for the pixel type. Pixels that are
regional maxima retain their value.


Regional maxima are flat zones surrounded by pixels of lower value. A
completely flat image will be marked as a regional maxima by this
filter. This code was contributed in the Insight Journal paper:
\"Finding regional extrema - methods and performance\" by Beare R.,
Lehmann G.http://hdl.handle.net/1926/153http://www.insight-
journal.org/browse/publication/65
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia.

See:
 ValuedRegionalMinimaImageFilter


ValuedRegionalExtremaImageFilter


 HMinimaImageFilter
Wiki Examples:

All Examples

 ValuedRegionalMaximaImageFilter

See:
 itk::simple::ValuedRegionalMaxima for the procedural interface


C++ includes: sitkValuedRegionalMaximaImageFilter.h
";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::GetFlat "

This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ValuedRegionalMaximaImageFilter::ValuedRegionalMaximaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::ValuedRegionalMinimaImageFilter "

Transforms the image so that any pixel that is not a regional minima
is set to the maximum value for the pixel type. Pixels that are
regional minima retain their value.


Regional minima are flat zones surrounded by pixels of higher value. A
completely flat image will be marked as a regional minima by this
filter. This code was contributed in the Insight Journal paper:
\"Finding regional extrema - methods and performance\" by Beare R.,
Lehmann G.http://hdl.handle.net/1926/153http://www.insight-
journal.org/browse/publication/65
Richard Beare. Department of Medicine, Monash University, Melbourne,
Australia.

See:
 ValuedRegionalMaximaImageFilter, ValuedRegionalExtremaImageFilter,


 HMinimaImageFilter
Wiki Examples:

All Examples

 ValuedRegionalMinimaImageFilter

See:
 itk::simple::ValuedRegionalMinima for the procedural interface


C++ includes: sitkValuedRegionalMinimaImageFilter.h
";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::GetFlat "

This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ValuedRegionalMinimaImageFilter::ValuedRegionalMinimaImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VectorConfidenceConnectedImageFilter "

Segment pixels with similar statistics using connectivity.


This filter extracts a connected set of pixels whose pixel intensities
are consistent with the pixel statistics of a seed point. The mean and
variance across a neighborhood (8-connected, 26-connected, etc.) are
calculated for a seed point. Then pixels connected to this seed point
whose values are within the confidence interval for the seed point are
grouped. The width of the confidence interval is controlled by the
\"Multiplier\" variable (the confidence interval is the mean plus or
minus the \"Multiplier\" times the standard deviation). If the
intensity variations across a segment were gaussian, a \"Multiplier\"
setting of 2.5 would define a confidence interval wide enough to
capture 99% of samples in the segment. After this initial segmentation
is calculated, the mean and variance are re-calculated. All the pixels
in the previous segmentation are used to calculate the mean the
standard deviation (as opposed to using the pixels in the neighborhood
of the seed point). The segmentation is then recalculted using these
refined estimates for the mean and variance of the pixel values. This
process is repeated for the specified number of iterations. Setting
the \"NumberOfIterations\" to zero stops the algorithm after the
initial segmentation from the seed point. NOTE: the lower and upper
threshold are restricted to lie within the valid numeric limits of the
input data pixel type. Also, the limits may be adjusted to contain the
seed point's intensity.


See:
 itk::simple::VectorConfidenceConnected for the procedural interface


C++ includes: sitkVectorConfidenceConnectedImageFilter.h
";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::AddSeed "

AddSeed - Add a seed to the end of the list

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::ClearSeeds "

ClearSeeds - Clear out all seeds in the list

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetCovariance "

The Covariance matrix computed during segmentation.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetInitialNeighborhoodRadius "

Get/Set the radius of the neighborhood over which the statistics are
evaluated.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetMean "

The Mean vector computed during segmentation.


This is a measurement. Its value is updated in the Execute methods, so
the value will only be valid after an execution.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetMultiplier "

Set/Get the multiplier to define the confidence interval. Multiplier
can be anything greater than zero. A typical value is 2.5.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetNumberOfIterations "

Set/Get the number of iterations.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetReplaceValue "

Set/Get value to replace thresholded pixels.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::GetSeedList "

Get SeedList

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetInitialNeighborhoodRadius "

Get/Set the radius of the neighborhood over which the statistics are
evaluated.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetMultiplier "

Set/Get the multiplier to define the confidence interval. Multiplier
can be anything greater than zero. A typical value is 2.5.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetNumberOfIterations "

Set/Get the number of iterations.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetReplaceValue "

Set/Get value to replace thresholded pixels.

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetSeed "

SetSeed - Set list to a single seed

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::SetSeedList "

Set SeedList

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VectorConfidenceConnectedImageFilter::VectorConfidenceConnectedImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VectorConnectedComponentImageFilter "

A connected components filter that labels the objects in a vector
image. Two vectors are pointing similar directions if one minus their
dot product is less than a threshold. Vectors that are 180 degrees out
of phase are similar. Assumes that vectors are normalized.



See:
 itk::simple::VectorConnectedComponent for the procedural interface


C++ includes: sitkVectorConnectedComponentImageFilter.h
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::FullyConnectedOff "
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::FullyConnectedOn "

Set the value of FullyConnected to true or false respectfully.

";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::GetDistanceThreshold "
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::GetFullyConnected "
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::SetDistanceThreshold "
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::SetFullyConnected "
";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VectorConnectedComponentImageFilter::VectorConnectedComponentImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VectorIndexSelectionCastImageFilter "

Extracts the selected index of the vector that is the input pixel
type.


This filter is templated over the input image type and output image
type. The filter expect the input image pixel type to be a vector and
the output image pixel type to be a scalar. The only requirement on
the type used for representing the vector is that it must provide an
operator[].Wiki Examples:

All Examples

Extract a component/channel of a vector image

See:
 itk::simple::VectorIndexSelectionCast for the procedural interface


C++ includes: sitkVectorIndexSelectionCastImageFilter.h
";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::GetIndex "
";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::SetIndex "

Get/Set methods for the index.

";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VectorIndexSelectionCastImageFilter::VectorIndexSelectionCastImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VectorMagnitudeImageFilter "

Take an image of vectors as input and produce an image with the
magnitude of those vectors.


The filter expects the input image pixel type to be a vector and the
output image pixel type to be a scalar. This filter assumes that the
PixelType of the input image is a VectorType that provides a GetNorm()
method.Wiki Examples:

All Examples

Compute the magnitude of each pixel in a vector image to produce a
magnitude image

See:
 itk::simple::VectorMagnitude for the procedural interface


C++ includes: sitkVectorMagnitudeImageFilter.h
";

%feature("docstring")  itk::simple::VectorMagnitudeImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VectorMagnitudeImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VectorMagnitudeImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VectorMagnitudeImageFilter::VectorMagnitudeImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::Version "

 Version info for SimpleITK.

C++ includes: sitkVersion.h
";

%feature("docstring")  itk::simple::Version::ToString "
";


%feature("docstring") itk::simple::VotingBinaryHoleFillingImageFilter "

Fills in holes and cavities by applying a voting operation on each
pixel.



See:
 Image


 VotingBinaryImageFilter


 VotingBinaryIterativeHoleFillingImageFilter


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::VotingBinaryHoleFilling for the procedural interface


C++ includes: sitkVotingBinaryHoleFillingImageFilter.h
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::GetBackgroundValue "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::GetForegroundValue "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::GetMajorityThreshold "

Majority threshold. It is the number of pixels over 50% that will
decide whether an OFF pixel will become ON or not. For example, if the
neighborhood of a pixel has 124 pixels (excluding itself), the 50%
will be 62, and if you set upd a Majority threshold of 5, that means
that the filter will require 67 or more neighbor pixels to be ON in
order to switch the current OFF pixel to ON. The default value is 1.

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::GetRadius "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::SetBackgroundValue "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::SetForegroundValue "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::SetMajorityThreshold "

Majority threshold. It is the number of pixels over 50% that will
decide whether an OFF pixel will become ON or not. For example, if the
neighborhood of a pixel has 124 pixels (excluding itself), the 50%
will be 62, and if you set upd a Majority threshold of 5, that means
that the filter will require 67 or more neighbor pixels to be ON in
order to switch the current OFF pixel to ON. The default value is 1.

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::SetRadius "
";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VotingBinaryHoleFillingImageFilter::VotingBinaryHoleFillingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VotingBinaryImageFilter "

Applies a voting operation in a neighborhood of each pixel.



Pixels which are not Foreground or Background will remain unchanged.

See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::VotingBinary for the procedural interface


C++ includes: sitkVotingBinaryImageFilter.h
";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetBackgroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetBirthThreshold "

Birth threshold. Pixels that are OFF will turn ON when the number of
neighbors ON is larger than the value defined in this threshold.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetForegroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetRadius "

Get the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::GetSurvivalThreshold "

Survival threshold. Pixels that are ON will turn OFF when the number
of neighbors ON is smaller than the value defined in this survival
threshold.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetBackgroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetBirthThreshold "

Birth threshold. Pixels that are OFF will turn ON when the number of
neighbors ON is larger than the value defined in this threshold.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetForegroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetRadius "

Set the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::SetSurvivalThreshold "

Survival threshold. Pixels that are ON will turn OFF when the number
of neighbors ON is smaller than the value defined in this survival
threshold.

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VotingBinaryImageFilter::VotingBinaryImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::VotingBinaryIterativeHoleFillingImageFilter "

Fills in holes and cavities by iteratively applying a voting
operation.


This filter uses internally the VotingBinaryHoleFillingImageFilter, and runs it iteratively until no pixels are being changed or until
it reaches the maximum number of iterations. The purpose of the filter
is to fill in holes of medium size (tens of pixels in radius). In
principle the number of iterations is related to the size of the holes
to be filled in. The larger the holes, the more iteration must be run
with this filter in order to fill in the full hole. The size of the
neighborhood is also related to the curvature of the hole borders and
therefore the hole size. Note that as a collateral effect this filter
may also fill in cavities in the external side of structures. This
filter is templated over a single image type because the output image
type must be the same as the input image type. This is required in
order to make the iterations possible, since the output image of one
iteration is taken as the input image for the next iteration.
See:
 Image


 VotingBinaryImageFilter


 VotingBinaryHoleFillingImageFilter


Neighborhood


NeighborhoodOperator


NeighborhoodIterator

 itk::simple::VotingBinaryIterativeHoleFilling for the procedural interface


C++ includes: sitkVotingBinaryIterativeHoleFillingImageFilter.h
";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetBackgroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetForegroundValue "

Get the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetMajorityThreshold "

Majority threshold. It is the number of pixels over 50% that will
decide whether an OFF pixel will become ON or not. For example, if the
neighborhood of a pixel has 124 pixels (excluding itself), the 50%
will be 62, and if you set upd a Majority threshold of 5, that means
that the filter will require 67 or more neighbor pixels to be ON in
order to switch the current OFF pixel to ON. The default value is 1.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetMaximumNumberOfIterations "

Maximum number of iterations. This filter is executed iteratively as
long as at least one pixel has changed in a previous iteration, or
until the maximum number of iterations has been reached.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::GetRadius "

Get the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetBackgroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetForegroundValue "

Set the value associated with the Foreground (or the object) on the
binary input image and the Background .

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetMajorityThreshold "

Majority threshold. It is the number of pixels over 50% that will
decide whether an OFF pixel will become ON or not. For example, if the
neighborhood of a pixel has 124 pixels (excluding itself), the 50%
will be 62, and if you set upd a Majority threshold of 5, that means
that the filter will require 67 or more neighbor pixels to be ON in
order to switch the current OFF pixel to ON. The default value is 1.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetMaximumNumberOfIterations "

Maximum number of iterations. This filter is executed iteratively as
long as at least one pixel has changed in a previous iteration, or
until the maximum number of iterations has been reached.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetRadius "

Set the radius of the neighborhood used to compute the median.

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::SetRadius "

Custom public declarations

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFillingImageFilter::VotingBinaryIterativeHoleFillingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::WhiteTopHatImageFilter "

White top hat extract local maxima that are larger than the
structuring element.


Top-hats are described in Chapter 4.5 of Pierre Soille's book
\"Morphological Image Analysis: Principles and Applications\", Second
Edition, Springer, 2003.
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 itk::simple::WhiteTopHat for the procedural interface


C++ includes: sitkWhiteTopHatImageFilter.h
";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::GetKernelRadius "
";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::GetKernelType "
";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::GetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SafeBorderOff "
";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SafeBorderOn "

Set the value of SafeBorder to true or false respectfully.

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SetKernelRadius "

Set/Get the radius of the kernel structuring element as a vector.

If the dimension of the image is greater then the length of r, then
the radius will be padded. If it is less the r will be truncated.

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SetKernelRadius "

Kernel radius as a scale for isotropic structures

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SetKernelType "

Set/Get the kernel or structuring elemenent used for the morphology

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::SetSafeBorder "

A safe border is added to input image to avoid borders effects and
remove it once the closing is done.

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::WhiteTopHatImageFilter::WhiteTopHatImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::WienerDeconvolutionImageFilter "

The Wiener deconvolution image filter is designed to restore an image
convolved with a blurring kernel while keeping noise enhancement to a
minimum.


The Wiener filter aims to minimize noise enhancement induced by
frequencies with low signal-to-noise ratio. The Wiener filter kernel
is defined in the frequency domain as $W(\\\\omega) = H^*(\\\\omega) / (|H(\\\\omega)|^2 + (1 /
SNR(\\\\omega)))$ where $H(\\\\omega)$ is the Fourier transform of the blurring kernel with which the
original image was convolved and the signal-to-noise ratio $SNR(\\\\omega)$ . $SNR(\\\\omega)$ is defined by $P_f(\\\\omega) / P_n(\\\\omega)$ where $P_f(\\\\omega)$ is the power spectral density of the uncorrupted signal and $P_n(\\\\omega)$ is the power spectral density of the noise. When applied to the input
blurred image, this filter produces an estimate $\\\\hat{f}(x)$ of the true underlying signal $f(x)$ that minimizes the expected error between $\\\\hat{f}(x)$ and $f(x)$ . This filter requires two inputs, the image to be deconvolved and
the blurring kernel. These two inputs can be set using the methods
SetInput()and SetKernelImage(), respectively. The power spectral
densities of the signal and noise are typically unavailable for a
given problem. In particular, $P_f(\\\\omega)$ cannot be computed from $f(x)$ because this unknown signal is precisely the signal that this filter
aims to recover. Nevertheless, it is common for the noise to have a
power spectral density that is flat or decreasing significantly more
slowly than the power spectral density of a typical image as the
frequency $\\\\omega$ increases. Hence, $P_n(\\\\omega)$ can typically be approximated with a constant, and this filter makes
this assumption (see the NoiseVariance member variable). $P_f(\\\\omega)$ , on the other hand, will vary with input. This filter computes the
power spectral density of the input blurred image, subtracts the power
spectral density of the noise, and uses the result as the estimate of $P_f(\\\\omega)$ . For further information on the Wiener deconvolution filter, please
see \"Digital Signal Processing\" by Kenneth R. Castleman, Prentice
Hall, 1995
Gaetan Lehmann, Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France Chris Mullins, The University of North
Carolina at Chapel Hill Cory Quammen, The University of North Carolina
at Chapel Hill

See:
 itk::simple::WienerDeconvolution for the procedural interface


C++ includes: sitkWienerDeconvolutionImageFilter.h
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::Execute "

Execute the filter on the input images with the given parameters

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::GetBoundaryCondition "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::GetNoiseVariance "

Set/get the variance of the zero-mean Gaussian white noise assumed to
be added to the input.

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::GetNormalize "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::GetOutputRegionMode "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::NormalizeOff "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::NormalizeOn "

Set the value of Normalize to true or false respectfully.

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::SetBoundaryCondition "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::SetNoiseVariance "

Set/get the variance of the zero-mean Gaussian white noise assumed to
be added to the input.

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::SetNormalize "

Normalize the output image by the sum of the kernel components.

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::SetOutputRegionMode "
";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::WienerDeconvolutionImageFilter::WienerDeconvolutionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::WrapPadImageFilter "

Increase the image size by padding with replicants of the input image
value.


WrapPadImageFilterchanges the image bounds of an image. Added pixels
are filled in with a wrapped replica of the input image. For instance,
if the output image needs a pixel that istwo pixels to the left of the
LargestPossibleRegionof the input image, the value assigned will be
from the pixeltwo pixels inside the right boundary of the
LargestPossibleRegion. The image bounds of the output must be
specified. Visual explanation of padding regions.This filter is
implemented as a multithreaded filter. It provides a
ThreadedGenerateData()method for its implementation.
See:
 MirrorPadImageFilter, ConstantPadImageFilter
Wiki Examples:

All Examples

Pad an image by wrapping

See:
 itk::simple::WrapPad for the procedural interface


C++ includes: sitkWrapPadImageFilter.h
";

%feature("docstring")  itk::simple::WrapPadImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::WrapPadImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::WrapPadImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::WrapPadImageFilter::GetPadLowerBound "
";

%feature("docstring")  itk::simple::WrapPadImageFilter::GetPadUpperBound "
";

%feature("docstring")  itk::simple::WrapPadImageFilter::SetPadLowerBound "
";

%feature("docstring")  itk::simple::WrapPadImageFilter::SetPadUpperBound "
";

%feature("docstring")  itk::simple::WrapPadImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::WrapPadImageFilter::WrapPadImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::XorImageFilter "

Computes the XOR logical operator pixel-wise between two images.


This class is templated over the types of the two input images and the
type of the output image. Numeric conversions (castings) are done by
the C++ defaults. Since the logical XOR operation is only defined in
C++ for integer types, the images passed to this filter must comply
with the requirement of using integer pixel type. The total operation
over one pixel will be
output_pixel=static_cast<OutputPixelType>(input1_pixel^input2_pixel)
Where \"^\" is the boolean XOR operator in C++.Wiki Examples:

All Examples

Binary XOR (exclusive OR) two images

See:
 itk::simple::Xor for the procedural interface


C++ includes: sitkXorImageFilter.h
";

%feature("docstring")  itk::simple::XorImageFilter::Execute "
";

%feature("docstring")  itk::simple::XorImageFilter::Execute "

Execute the filter with an image and a constant

";

%feature("docstring")  itk::simple::XorImageFilter::Execute "

Execute the filter on the input images

";

%feature("docstring")  itk::simple::XorImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::XorImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::XorImageFilter::XorImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::YenThresholdImageFilter "

Threshold an image using the Yen Threshold.


This filter creates a binary thresholded image that separates an image
into foreground and background components. The filter computes the
threshold using the YenThresholdCalculatorand applies that theshold to
the input image using the BinaryThresholdImageFilter.
Richard Beare Gaetan Lehmann. Biologie du Developpement et de la
Reproduction, INRA de Jouy-en-Josas, France. This implementation was
taken from the Insight Journal
paper:http://hdl.handle.net/10380/3279orhttp://www.insight-
journal.org/browse/publication/811

See:
HistogramThresholdImageFitler

 itk::simple::YenThreshold for the procedural interface


C++ includes: sitkYenThresholdImageFilter.h
";

%feature("docstring")  itk::simple::YenThresholdImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::GetInsideValue "

Get the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::GetNumberOfHistogramBins "
";

%feature("docstring")  itk::simple::YenThresholdImageFilter::GetOutsideValue "

Get the \"outside\" pixel value.

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::SetInsideValue "

Set the \"inside\" pixel value.

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::SetNumberOfHistogramBins "

Set/Get the number of histogram bins.

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::SetOutsideValue "

Set the \"outside\" pixel value. The default value
NumericTraits<OutputPixelType>::Zero.

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::YenThresholdImageFilter::YenThresholdImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter "

This filter implements a zero-crossing based edge detecor.


The zero-crossing based edge detector looks for pixels in the
Laplacian of an image where the value of the Laplacian passes through
zeropoints where the Laplacian changes sign. Such points often occur
at ``edges'' in imagesi.e. points where the intensity of the image
changes rapidly, but they also occur at places that are not as easy to
associate with edges. It is best to think of the zero crossing
detector as some sort of feature detector rather than as a specific
edge detector.Zero crossings always lie on closed contours and so the output from
the zero crossing detector is usually a binary image with single pixel
thickness lines showing the positions of the zero crossing points.
In this implementation, the input image is first smoothed with a
Gaussian filter, then the LaplacianImageFilteris applied to smoothed
image. Finally the zero-crossing of the Laplacian of the smoothed
image is detected. The output is a binary image.
Inputs and Outputs
The input to the filter should be a scalar, itk::Imageof arbitrary
dimension. The output image is a binary, labeled image. See
itkZeroCrossingImageFilter for more information on requirements of the
data type of the output.
To use this filter, first set the parameters (variance and maximum
error) needed by the embedded DiscreteGaussianImageFilter, i.e. See
DiscreteGaussianImageFilterfor information about these parameters.
Optionally, you may also set foreground and background values for the
zero-crossing filter. The default label values are Zero for the
background and One for the foreground, as defined in NumericTraitsfor
the data type of the output image.

See:
 DiscreteGaussianImageFilter


 LaplacianImageFilter


 ZeroCrossingImageFilter

 itk::simple::ZeroCrossingBasedEdgeDetection for the procedural interface


C++ includes: sitkZeroCrossingBasedEdgeDetectionImageFilter.h
";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::GetBackgroundValue "

Get/Set the label values for the ZeroCrossingImageFilter.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::GetForegroundValue "

Get/Set the label values for the ZeroCrossingImageFilter.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::GetMaximumError "

Standard get/set macros for Gaussian filter parameters.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::GetVariance "

Standard get/set macros for Gaussian filter parameters.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::SetBackgroundValue "

Get/Set the label values for the ZeroCrossingImageFilter.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::SetForegroundValue "

Get/Set the label values for the ZeroCrossingImageFilter.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::SetMaximumError "

Set the MaximumError parameter needed by the embedded gaussian filter
This value is used to set the desired maximum error of the gaussian
approximation. Maximum error is the difference between the area under
the discrete Gaussian curve and the area under the continuous
Gaussian. Maximum error affects the Gaussian operator size. The value
must be between 0.0 and 1.0.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::SetVariance "

Set the variance parameter needed by the embedded gaussian filter.

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter::ZeroCrossingBasedEdgeDetectionImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::ZeroCrossingImageFilter "

This filter finds the closest pixel to the zero-crossings (sign
changes) in a signed itk::Image.


Pixels closest to zero-crossings are labeled with a foreground value.
All other pixels are marked with a background value. The algorithm
works by detecting differences in sign among neighbors using city-
block style connectivity (4-neighbors in 2d, 6-neighbors in 3d, etc.).Inputs and Outputs
The input to this filter is an itk::Imageof arbitrary dimension. The
algorithm assumes a signed data type (zero-crossings are not defined
for unsigned data types), and requires that operator>, operator<,
operator==, and operator!= are defined.
The output of the filter is a binary, labeled image of user-specified
type. By default, zero-crossing pixels are labeled with a default
``foreground'' value of itk::NumericTraits::One, where OutputDataType
is the data type of the output image. All other pixels are labeled
with a default ``background'' value of itk::NumericTraits::Zero.
Parameters
There are two parameters for this filter. ForegroundValue is the value
that marks zero-crossing pixels. The BackgroundValue is the value
given to all other pixels.

See:
 Image


Neighborhood


NeighborhoodOperator


NeighborhoodIterator
Wiki Examples:

All Examples

Find zero crossings in a signed image

See:
 itk::simple::ZeroCrossing for the procedural interface


C++ includes: sitkZeroCrossingImageFilter.h
";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::GetBackgroundValue "

Set/Get the label value for non-zero-crossing pixels.

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::GetForegroundValue "

Set/Get the label value for zero-crossing pixels.

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::SetBackgroundValue "

Set/Get the label value for non-zero-crossing pixels.

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::SetForegroundValue "

Set/Get the label value for zero-crossing pixels.

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ZeroCrossingImageFilter::ZeroCrossingImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::ZeroFluxNeumannPadImageFilter "

Increase the image size by padding according to the zero-flux Neumann
boundary condition.


A filter which extends the image size and fill the missing pixels
according to a Neumann boundary condition where first, upwind
derivatives on the boundary are zero. This is a useful condition in
solving some classes of differential equations. For example, invoking
this filter on an image with a corner like:****************12345(where
*denotespixelsthatlie**33556outsideoftheimageboundary)**44678returns
the following padded
image:1112345111234511123453333556(notethecornervalues)4444678
Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA
de Jouy-en-Josas, France.

See:
 WrapPadImageFilter, MirrorPadImageFilter, ConstantPadImageFilter, ZeroFluxNeumannBoundaryCondition

 itk::simple::ZeroFluxNeumannPad for the procedural interface


C++ includes: sitkZeroFluxNeumannPadImageFilter.h
";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::Execute "

Execute the filter on the input image with the given parameters

";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::Execute "

Execute the filter on the input image

";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::GetName "

Name of this class

";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::GetPadLowerBound "
";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::GetPadUpperBound "
";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::SetPadLowerBound "
";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::SetPadUpperBound "
";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::ToString "

Print ourselves out

";

%feature("docstring")  itk::simple::ZeroFluxNeumannPadImageFilter::ZeroFluxNeumannPadImageFilter "

Default Constructor that takes no arguments and initializes default
parameters

";


%feature("docstring") itk::simple::DualMemberFunctionFactory "

A class used to instantiate and generate function objects of templated
member functions with two template arguments.




Parameters:

TMemberFunctionPointer:
is the type of pointer to member function

 Example member function and pointer:

The provided Addressor will instantiate the templeted member functions
by taking the address in the RegisterMethods. Later they can be
retrieve with the GetMemberFunction method, which returns a function
object with the same arguments as the templated member function
pointer.

An instance of a MemberFunctionFactory is bound to a specific instance of an object, so that the returned
function object does not need to have the calling object specified.


WARNING:
Use this class with caution because it can instantiate a combinatorial
number of methods.

See:
 MemberFunctionFactory


C++ includes: sitkDualMemberFunctionFactory.h
";

%feature("docstring")  itk::simple::DualMemberFunctionFactory::DualMemberFunctionFactory "

Constructor which permanently binds the constructed object to pObject.

";

%feature("docstring")  itk::simple::DualMemberFunctionFactory::GetMemberFunction "

Returns a function object for the combination of PixelID1 and
PixelID2, and image dimension.


pixelID1 or pixelID2 is the value of Image::GetPixelIDValue(), or PixelIDToPixelIDValue<PixelIDType>::Result

imageDimension is the the value returned by Image::GetDimension()

Example usage:

If the requested member function is not registered then an exception
is generated. The returned function object is guaranteed to be valid.

";

%feature("docstring")  itk::simple::DualMemberFunctionFactory::HasMemberFunction "
 throw ()
Query to determine if an member function has been registered for
pixelID1, pixelID2 and imageDimension.

";

%feature("docstring")  itk::simple::DualMemberFunctionFactory::Register "

Registers a specific member function.


Registers a member function templated over TImageType1 and TImageType2

";


%feature("docstring") itk::simple::MemberFunctionFactory "

A class used to instantiate and generate function object to templated
member functions.




Parameters:

TMemberFunctionPointer:
is the type of pointer to member function

 Example member function pointer:

The RegisterMemberFunctions instantiate the templeted member functions
and registers the member function pointer, so that it be used for
dispatch later. Later they can be retrieve with the GetMemberFunction
methods, which return a function object with the same arguments as the
templated member function pointer.

An instance of a MemberFunctionFactory is bound to a specific instance of an object, so that the returned
function object does not need to have the calling object specified.

C++ includes: sitkMemberFunctionFactory.h
";

%feature("docstring")  itk::simple::MemberFunctionFactory::GetMemberFunction "

Returns a function object for the PixelIndex, and image dimension.


pixelID is the value of Image::GetPixelIDValue(), or PixelIDToPixelIDValue<PixelIDType>::Result

imageDimension is the the value returned by Image::GetDimension()

Example usage:

If the requested member function is not registered then an exception
is generated. The returned function object is guaranteed to be valid.

";

%feature("docstring")  itk::simple::MemberFunctionFactory::HasMemberFunction "
 throw ()
Query to determine if an member function has been registered for
pixelID and imageDimension.

";

%feature("docstring")  itk::simple::MemberFunctionFactory::MemberFunctionFactory "

Constructor which permanently binds the constructed object to pObject.

";

%feature("docstring")  itk::simple::MemberFunctionFactory::Register "

Registers a specific member function.


Registers a member function which will be dispatched to the TImageType
type

";


%feature("docstring") itk::simple::MemberFunctionFactoryBase< TMemberFunctionPointer, TKey, 0 > "
C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") itk::simple::MemberFunctionFactoryBase< TMemberFunctionPointer, TKey, 1 > "
C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") itk::simple::MemberFunctionFactoryBase< TMemberFunctionPointer, TKey, 2 > "
C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") itk::simple::MemberFunctionFactoryBase< TMemberFunctionPointer, TKey, 3 > "
C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") itk::simple::MemberFunctionFactoryBase< TMemberFunctionPointer, TKey, 4 > "
C++ includes: sitkMemberFunctionFactoryBase.h
";


%feature("docstring") std::allocator "

STL class.

";


%feature("docstring") std::auto_ptr "

STL class.

";


%feature("docstring") std::bad_alloc "

STL class.

";


%feature("docstring") std::bad_cast "

STL class.

";


%feature("docstring") std::bad_exception "

STL class.

";


%feature("docstring") std::bad_typeid "

STL class.

";


%feature("docstring") std::basic_fstream "

STL class.

";


%feature("docstring") std::basic_ifstream "

STL class.

";


%feature("docstring") std::basic_ios "

STL class.

";


%feature("docstring") std::basic_iostream "

STL class.

";


%feature("docstring") std::basic_istream "

STL class.

";


%feature("docstring") std::basic_istringstream "

STL class.

";


%feature("docstring") std::basic_ofstream "

STL class.

";


%feature("docstring") std::basic_ostream "

STL class.

";


%feature("docstring") std::basic_ostringstream "

STL class.

";


%feature("docstring") std::basic_string "

STL class.

";


%feature("docstring") std::basic_string::const_iterator "

STL iterator class.

";


%feature("docstring") std::basic_string::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::basic_string::iterator "

STL iterator class.

";


%feature("docstring") std::basic_string::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::basic_stringstream "

STL class.

";


%feature("docstring") std::bitset "

STL class.

";


%feature("docstring") std::complex "

STL class.

";


%feature("docstring") std::deque "

STL class.

";


%feature("docstring") std::deque::const_iterator "

STL iterator class.

";


%feature("docstring") std::deque::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::deque::iterator "

STL iterator class.

";


%feature("docstring") std::deque::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::domain_error "

STL class.

";


%feature("docstring") std::exception "

STL class.

";


%feature("docstring") std::fstream "

STL class.

";


%feature("docstring") std::ifstream "

STL class.

";


%feature("docstring") std::invalid_argument "

STL class.

";


%feature("docstring") std::ios "

STL class.

";


%feature("docstring") std::ios_base "

STL class.

";


%feature("docstring") std::ios_base::failure "

STL class.

";


%feature("docstring") std::istream "

STL class.

";


%feature("docstring") std::istringstream "

STL class.

";


%feature("docstring") std::length_error "

STL class.

";


%feature("docstring") std::list "

STL class.

";


%feature("docstring") std::list::const_iterator "

STL iterator class.

";


%feature("docstring") std::list::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::list::iterator "

STL iterator class.

";


%feature("docstring") std::list::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::logic_error "

STL class.

";


%feature("docstring") std::map "

STL class.

";


%feature("docstring") std::map::const_iterator "

STL iterator class.

";


%feature("docstring") std::map::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::map::iterator "

STL iterator class.

";


%feature("docstring") std::map::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::multimap "

STL class.

";


%feature("docstring") std::multimap::const_iterator "

STL iterator class.

";


%feature("docstring") std::multimap::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::multimap::iterator "

STL iterator class.

";


%feature("docstring") std::multimap::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::multiset "

STL class.

";


%feature("docstring") std::multiset::const_iterator "

STL iterator class.

";


%feature("docstring") std::multiset::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::multiset::iterator "

STL iterator class.

";


%feature("docstring") std::multiset::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::ofstream "

STL class.

";


%feature("docstring") std::ostream "

STL class.

";


%feature("docstring") std::ostringstream "

STL class.

";


%feature("docstring") std::out_of_range "

STL class.

";


%feature("docstring") std::overflow_error "

STL class.

";


%feature("docstring") std::priority_queue "

STL class.

";


%feature("docstring") std::queue "

STL class.

";


%feature("docstring") std::range_error "

STL class.

";


%feature("docstring") std::runtime_error "

STL class.

";


%feature("docstring") std::set "

STL class.

";


%feature("docstring") std::set::const_iterator "

STL iterator class.

";


%feature("docstring") std::set::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::set::iterator "

STL iterator class.

";


%feature("docstring") std::set::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::stack "

STL class.

";


%feature("docstring") std::string "

STL class.

";


%feature("docstring") std::string::const_iterator "

STL iterator class.

";


%feature("docstring") std::string::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::string::iterator "

STL iterator class.

";


%feature("docstring") std::string::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::stringstream "

STL class.

";


%feature("docstring") std::underflow_error "

STL class.

";


%feature("docstring") std::valarray "

STL class.

";


%feature("docstring") std::vector "

STL class.

";


%feature("docstring") std::vector::const_iterator "

STL iterator class.

";


%feature("docstring") std::vector::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::vector::iterator "

STL iterator class.

";


%feature("docstring") std::vector::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::wfstream "

STL class.

";


%feature("docstring") std::wifstream "

STL class.

";


%feature("docstring") std::wios "

STL class.

";


%feature("docstring") std::wistream "

STL class.

";


%feature("docstring") std::wistringstream "

STL class.

";


%feature("docstring") std::wofstream "

STL class.

";


%feature("docstring") std::wostream "

STL class.

";


%feature("docstring") std::wostringstream "

STL class.

";


%feature("docstring") std::wstring "

STL class.

";


%feature("docstring") std::wstring::const_iterator "

STL iterator class.

";


%feature("docstring") std::wstring::const_reverse_iterator "

STL iterator class.

";


%feature("docstring") std::wstring::iterator "

STL iterator class.

";


%feature("docstring") std::wstring::reverse_iterator "

STL iterator class.

";


%feature("docstring") std::wstringstream "

STL class.

";

%feature("docstring")  itk::Functor::BioRadImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::BMPImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::GDCMImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::GiplImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::HDF5ImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::HDF5TransformIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::JPEGImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::LSMImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::MatlabTransformIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::MetaImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::MRCImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::NiftiImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::NrrdImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::PNGImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::StimulateImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::TIFFImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::TxtTransformIOFactoryRegister__Private "
";

%feature("docstring")  itk::Functor::VTKImageIOFactoryRegister__Private "
";

%feature("docstring")  itk::simple::Abs "

 itk::simple::AbsImageFilter Procedural Interface


This function directly calls the execute method of AbsImageFilter in order to support a procedural API


See:
 itk::simple::AbsImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::AbsoluteValueDifference "
";

%feature("docstring")  itk::simple::AbsoluteValueDifference "
";

%feature("docstring")  itk::simple::AbsoluteValueDifference "

 itk::simple::AbsoluteValueDifferenceImageFilter Procedural Interface


This function directly calls the execute method of AbsoluteValueDifferenceImageFilter in order to support a procedural API


See:
 itk::simple::AbsoluteValueDifferenceImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Acos "

 itk::simple::AcosImageFilter Procedural Interface


This function directly calls the execute method of AcosImageFilter in order to support a procedural API


See:
 itk::simple::AcosImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::AdaptiveHistogramEqualization "

 itk::simple::AdaptiveHistogramEqualizationImageFilter Procedural Interface


This function directly calls the execute method of AdaptiveHistogramEqualizationImageFilter in order to support a procedural API


See:
 itk::simple::AdaptiveHistogramEqualizationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Add "
";

%feature("docstring")  itk::simple::Add "
";

%feature("docstring")  itk::simple::Add "

 itk::simple::AddImageFilter Procedural Interface


This function directly calls the execute method of AddImageFilter in order to support a procedural API


See:
 itk::simple::AddImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::And "
";

%feature("docstring")  itk::simple::And "
";

%feature("docstring")  itk::simple::And "

 itk::simple::AndImageFilter Procedural Interface


This function directly calls the execute method of AndImageFilter in order to support a procedural API


See:
 itk::simple::AndImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::AntiAliasBinary "

 itk::simple::AntiAliasBinaryImageFilter Procedural Interface


This function directly calls the execute method of AntiAliasBinaryImageFilter in order to support a procedural API


See:
 itk::simple::AntiAliasBinaryImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ApproximateSignedDistanceMap "

 itk::simple::ApproximateSignedDistanceMapImageFilter Procedural Interface


This function directly calls the execute method of ApproximateSignedDistanceMapImageFilter in order to support a procedural API


See:
 itk::simple::ApproximateSignedDistanceMapImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Asin "

 itk::simple::AsinImageFilter Procedural Interface


This function directly calls the execute method of AsinImageFilter in order to support a procedural API


See:
 itk::simple::AsinImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Atan "

 itk::simple::AtanImageFilter Procedural Interface


This function directly calls the execute method of AtanImageFilter in order to support a procedural API


See:
 itk::simple::AtanImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Atan2 "
";

%feature("docstring")  itk::simple::Atan2 "
";

%feature("docstring")  itk::simple::Atan2 "

 itk::simple::Atan2ImageFilter Procedural Interface


This function directly calls the execute method of Atan2ImageFilter in order to support a procedural API


See:
 itk::simple::Atan2ImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Bilateral "

 itk::simple::BilateralImageFilter Procedural Interface


This function directly calls the execute method of BilateralImageFilter in order to support a procedural API


See:
 itk::simple::BilateralImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryClosingByReconstruction "

 itk::simple::BinaryClosingByReconstructionImageFilter Functional Interface

This function directly calls the execute method of BinaryClosingByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryClosingByReconstruction "

 itk::simple::BinaryClosingByReconstructionImageFilter Functional Interface

This function directly calls the execute method of BinaryClosingByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryContour "

 itk::simple::BinaryContourImageFilter Procedural Interface


This function directly calls the execute method of BinaryContourImageFilter in order to support a procedural API


See:
 itk::simple::BinaryContourImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryDilate "

 itk::simple::BinaryDilateImageFilter Functional Interface

This function directly calls the execute method of BinaryDilateImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryDilate "

 itk::simple::BinaryDilateImageFilter Functional Interface

This function directly calls the execute method of BinaryDilateImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryErode "

 itk::simple::BinaryErodeImageFilter Functional Interface

This function directly calls the execute method of BinaryErodeImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryErode "

 itk::simple::BinaryErodeImageFilter Functional Interface

This function directly calls the execute method of BinaryErodeImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryFillhole "

 itk::simple::BinaryFillholeImageFilter Procedural Interface


This function directly calls the execute method of BinaryFillholeImageFilter in order to support a procedural API


See:
 itk::simple::BinaryFillholeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryGrindPeak "

 itk::simple::BinaryGrindPeakImageFilter Procedural Interface


This function directly calls the execute method of BinaryGrindPeakImageFilter in order to support a procedural API


See:
 itk::simple::BinaryGrindPeakImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryMagnitude "

 itk::simple::BinaryMagnitudeImageFilter Procedural Interface


This function directly calls the execute method of BinaryMagnitudeImageFilter in order to support a procedural API


See:
 itk::simple::BinaryMagnitudeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryMedian "

 itk::simple::BinaryMedianImageFilter Procedural Interface


This function directly calls the execute method of BinaryMedianImageFilter in order to support a procedural API


See:
 itk::simple::BinaryMedianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryMinMaxCurvatureFlow "

 itk::simple::BinaryMinMaxCurvatureFlowImageFilter Procedural Interface


This function directly calls the execute method of BinaryMinMaxCurvatureFlowImageFilter in order to support a procedural API


See:
 itk::simple::BinaryMinMaxCurvatureFlowImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryMorphologicalClosing "

 itk::simple::BinaryMorphologicalClosingImageFilter Functional Interface

This function directly calls the execute method of BinaryMorphologicalClosingImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryMorphologicalClosing "

 itk::simple::BinaryMorphologicalClosingImageFilter Functional Interface

This function directly calls the execute method of BinaryMorphologicalClosingImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpening "

 itk::simple::BinaryMorphologicalOpeningImageFilter Functional Interface

This function directly calls the execute method of BinaryMorphologicalOpeningImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryMorphologicalOpening "

 itk::simple::BinaryMorphologicalOpeningImageFilter Functional Interface

This function directly calls the execute method of BinaryMorphologicalOpeningImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryNot "

 itk::simple::BinaryNotImageFilter Procedural Interface


This function directly calls the execute method of BinaryNotImageFilter in order to support a procedural API


See:
 itk::simple::BinaryNotImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryOpeningByReconstruction "

 itk::simple::BinaryOpeningByReconstructionImageFilter Functional Interface

This function directly calls the execute method of BinaryOpeningByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryOpeningByReconstruction "

 itk::simple::BinaryOpeningByReconstructionImageFilter Functional Interface

This function directly calls the execute method of BinaryOpeningByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BinaryProjection "

 itk::simple::BinaryProjectionImageFilter Procedural Interface


This function directly calls the execute method of BinaryProjectionImageFilter in order to support a procedural API


See:
 itk::simple::BinaryProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryReconstructionByDilation "

 itk::simple::BinaryReconstructionByDilationImageFilter Procedural Interface


This function directly calls the execute method of BinaryReconstructionByDilationImageFilter in order to support a procedural API


See:
 itk::simple::BinaryReconstructionByDilationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryReconstructionByErosion "

 itk::simple::BinaryReconstructionByErosionImageFilter Procedural Interface


This function directly calls the execute method of BinaryReconstructionByErosionImageFilter in order to support a procedural API


See:
 itk::simple::BinaryReconstructionByErosionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryThinning "

 itk::simple::BinaryThinningImageFilter Procedural Interface


This function directly calls the execute method of BinaryThinningImageFilter in order to support a procedural API


See:
 itk::simple::BinaryThinningImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryThreshold "

 itk::simple::BinaryThresholdImageFilter Procedural Interface


This function directly calls the execute method of BinaryThresholdImageFilter in order to support a procedural API


See:
 itk::simple::BinaryThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinaryThresholdProjection "

 itk::simple::BinaryThresholdProjectionImageFilter Procedural Interface


This function directly calls the execute method of BinaryThresholdProjectionImageFilter in order to support a procedural API


See:
 itk::simple::BinaryThresholdProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BinomialBlur "

 itk::simple::BinomialBlurImageFilter Procedural Interface


This function directly calls the execute method of BinomialBlurImageFilter in order to support a procedural API


See:
 itk::simple::BinomialBlurImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BlackTopHat "

 itk::simple::BlackTopHatImageFilter Functional Interface

This function directly calls the execute method of BlackTopHatImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BlackTopHat "

 itk::simple::BlackTopHatImageFilter Functional Interface

This function directly calls the execute method of BlackTopHatImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::BoundedReciprocal "

 itk::simple::BoundedReciprocalImageFilter Procedural Interface


This function directly calls the execute method of BoundedReciprocalImageFilter in order to support a procedural API


See:
 itk::simple::BoundedReciprocalImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BoxMean "

 itk::simple::BoxMeanImageFilter Procedural Interface


This function directly calls the execute method of BoxMeanImageFilter in order to support a procedural API


See:
 itk::simple::BoxMeanImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::BoxSigma "

 itk::simple::BoxSigmaImageFilter Procedural Interface


This function directly calls the execute method of BoxSigmaImageFilter in order to support a procedural API


See:
 itk::simple::BoxSigmaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::CannyEdgeDetection "

 itk::simple::CannyEdgeDetectionImageFilter Procedural Interface


This function directly calls the execute method of CannyEdgeDetectionImageFilter in order to support a procedural API


See:
 itk::simple::CannyEdgeDetectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Cast "
";

%feature("docstring")  itk::simple::ChangeLabel "

 itk::simple::ChangeLabelImageFilter Procedural Interface


This function directly calls the execute method of ChangeLabelImageFilter in order to support a procedural API


See:
 itk::simple::ChangeLabelImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::CheckerBoard "

 itk::simple::CheckerBoardImageFilter Procedural Interface


This function directly calls the execute method of CheckerBoardImageFilter in order to support a procedural API


See:
 itk::simple::CheckerBoardImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ClosingByReconstruction "

 itk::simple::ClosingByReconstructionImageFilter Functional Interface

This function directly calls the execute method of ClosingByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::ClosingByReconstruction "

 itk::simple::ClosingByReconstructionImageFilter Functional Interface

This function directly calls the execute method of ClosingByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::ComplexToImaginary "

 itk::simple::ComplexToImaginaryImageFilter Procedural Interface


This function directly calls the execute method of ComplexToImaginaryImageFilter in order to support a procedural API


See:
 itk::simple::ComplexToImaginaryImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ComplexToModulus "

 itk::simple::ComplexToModulusImageFilter Procedural Interface


This function directly calls the execute method of ComplexToModulusImageFilter in order to support a procedural API


See:
 itk::simple::ComplexToModulusImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ComplexToPhase "

 itk::simple::ComplexToPhaseImageFilter Procedural Interface


This function directly calls the execute method of ComplexToPhaseImageFilter in order to support a procedural API


See:
 itk::simple::ComplexToPhaseImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ComplexToReal "

 itk::simple::ComplexToRealImageFilter Procedural Interface


This function directly calls the execute method of ComplexToRealImageFilter in order to support a procedural API


See:
 itk::simple::ComplexToRealImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Compose "
";

%feature("docstring")  itk::simple::Compose "
";

%feature("docstring")  itk::simple::Compose "
";

%feature("docstring")  itk::simple::Compose "
";

%feature("docstring")  itk::simple::Compose "
";

%feature("docstring")  itk::simple::Compose "

 itk::simple::ComposeImageFilter Procedural Interface


This function directly calls the execute method of ComposeImageFilter in order to support a procedural API


See:
 itk::simple::ComposeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ConfidenceConnected "

 itk::simple::ConfidenceConnectedImageFilter Functional Interface

This function directly calls the execute method of ConfidenceConnectedImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::ConnectedComponent "

 itk::simple::ConnectedComponentImageFilter Procedural Interface


This function directly calls the execute method of ConnectedComponentImageFilter in order to support a procedural API


See:
 itk::simple::ConnectedComponentImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ConnectedThreshold "

 itk::simple::ConnectedThresholdImageFilter Functional Interface

This function directly calls the execute method of ConnectedThresholdImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::ConstantPad "

 itk::simple::ConstantPadImageFilter Procedural Interface


This function directly calls the execute method of ConstantPadImageFilter in order to support a procedural API


See:
 itk::simple::ConstantPadImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Convolution "

 itk::simple::ConvolutionImageFilter Procedural Interface


This function directly calls the execute method of ConvolutionImageFilter in order to support a procedural API


See:
 itk::simple::ConvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Cos "

 itk::simple::CosImageFilter Procedural Interface


This function directly calls the execute method of CosImageFilter in order to support a procedural API


See:
 itk::simple::CosImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Crop "

 itk::simple::CropImageFilter Procedural Interface


This function directly calls the execute method of CropImageFilter in order to support a procedural API


See:
 itk::simple::CropImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::CurvatureAnisotropicDiffusion "

 itk::simple::CurvatureAnisotropicDiffusionImageFilter Procedural Interface


This function directly calls the execute method of CurvatureAnisotropicDiffusionImageFilter in order to support a procedural API


See:
 itk::simple::CurvatureAnisotropicDiffusionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::CurvatureFlow "

 itk::simple::CurvatureFlowImageFilter Procedural Interface


This function directly calls the execute method of CurvatureFlowImageFilter in order to support a procedural API


See:
 itk::simple::CurvatureFlowImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::DanielssonDistanceMap "

 itk::simple::DanielssonDistanceMapImageFilter Procedural Interface


This function directly calls the execute method of DanielssonDistanceMapImageFilter in order to support a procedural API


See:
 itk::simple::DanielssonDistanceMapImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Derivative "

 itk::simple::DerivativeImageFilter Procedural Interface


This function directly calls the execute method of DerivativeImageFilter in order to support a procedural API


See:
 itk::simple::DerivativeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::DilateObjectMorphology "

 itk::simple::DilateObjectMorphologyImageFilter Functional Interface

This function directly calls the execute method of DilateObjectMorphologyImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::DilateObjectMorphology "

 itk::simple::DilateObjectMorphologyImageFilter Functional Interface

This function directly calls the execute method of DilateObjectMorphologyImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::DiscreteGaussian "

 itk::simple::DiscreteGaussianImageFilter Procedural Interface


This function directly calls the execute method of DiscreteGaussianImageFilter in order to support a procedural API


See:
 itk::simple::DiscreteGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Divide "
";

%feature("docstring")  itk::simple::Divide "
";

%feature("docstring")  itk::simple::Divide "

 itk::simple::DivideImageFilter Procedural Interface


This function directly calls the execute method of DivideImageFilter in order to support a procedural API


See:
 itk::simple::DivideImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::DivideFloor "
";

%feature("docstring")  itk::simple::DivideFloor "
";

%feature("docstring")  itk::simple::DivideFloor "

 itk::simple::DivideFloorImageFilter Procedural Interface


This function directly calls the execute method of DivideFloorImageFilter in order to support a procedural API


See:
 itk::simple::DivideFloorImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::DivideReal "
";

%feature("docstring")  itk::simple::DivideReal "
";

%feature("docstring")  itk::simple::DivideReal "

 itk::simple::DivideRealImageFilter Procedural Interface


This function directly calls the execute method of DivideRealImageFilter in order to support a procedural API


See:
 itk::simple::DivideRealImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::DoubleThreshold "

 itk::simple::DoubleThresholdImageFilter Procedural Interface


This function directly calls the execute method of DoubleThresholdImageFilter in order to support a procedural API


See:
 itk::simple::DoubleThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::EdgePotential "

 itk::simple::EdgePotentialImageFilter Procedural Interface


This function directly calls the execute method of EdgePotentialImageFilter in order to support a procedural API


See:
 itk::simple::EdgePotentialImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Equal "
";

%feature("docstring")  itk::simple::Equal "
";

%feature("docstring")  itk::simple::Equal "

 itk::simple::EqualImageFilter Procedural Interface


This function directly calls the execute method of EqualImageFilter in order to support a procedural API


See:
 itk::simple::EqualImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ErodeObjectMorphology "

 itk::simple::ErodeObjectMorphologyImageFilter Functional Interface

This function directly calls the execute method of ErodeObjectMorphologyImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::ErodeObjectMorphology "

 itk::simple::ErodeObjectMorphologyImageFilter Functional Interface

This function directly calls the execute method of ErodeObjectMorphologyImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::Exp "

 itk::simple::ExpImageFilter Procedural Interface


This function directly calls the execute method of ExpImageFilter in order to support a procedural API


See:
 itk::simple::ExpImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Expand "

 itk::simple::ExpandImageFilter Procedural Interface


This function directly calls the execute method of ExpandImageFilter in order to support a procedural API


See:
 itk::simple::ExpandImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ExpNegative "

 itk::simple::ExpNegativeImageFilter Procedural Interface


This function directly calls the execute method of ExpNegativeImageFilter in order to support a procedural API


See:
 itk::simple::ExpNegativeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Extract "

 itk::simple::ExtractImageFilter Procedural Interface


This function directly calls the execute method of ExtractImageFilter in order to support a procedural API


See:
 itk::simple::ExtractImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::FastApproximateRank "

 itk::simple::FastApproximateRankImageFilter Procedural Interface


This function directly calls the execute method of FastApproximateRankImageFilter in order to support a procedural API


See:
 itk::simple::FastApproximateRankImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::FastMarching "

 itk::simple::FastMarchingImageFilter Functional Interface

This function directly calls the execute method of FastMarchingImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::FFTConvolution "

 itk::simple::FFTConvolutionImageFilter Procedural Interface


This function directly calls the execute method of FFTConvolutionImageFilter in order to support a procedural API


See:
 itk::simple::FFTConvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::FFTNormalizedCorrelation "

 itk::simple::FFTNormalizedCorrelationImageFilter Procedural Interface


This function directly calls the execute method of FFTNormalizedCorrelationImageFilter in order to support a procedural API


See:
 itk::simple::FFTNormalizedCorrelationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::FFTShift "

 itk::simple::FFTShiftImageFilter Procedural Interface


This function directly calls the execute method of FFTShiftImageFilter in order to support a procedural API


See:
 itk::simple::FFTShiftImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Flip "

 itk::simple::FlipImageFilter Procedural Interface


This function directly calls the execute method of FlipImageFilter in order to support a procedural API


See:
 itk::simple::FlipImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ForwardFFT "

 itk::simple::ForwardFFTImageFilter Procedural Interface


This function directly calls the execute method of ForwardFFTImageFilter in order to support a procedural API


See:
 itk::simple::ForwardFFTImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GaborSource "

 itk::simple::GaborImageSource Procedural Interface


This function directly calls the execute method of GaborImageSource in order to support a procedural API


See:
 itk::simple::GaborImageSource for the object oriented interface


";

%feature("docstring")  itk::simple::GaussianSource "

 itk::simple::GaussianImageSource Procedural Interface


This function directly calls the execute method of GaussianImageSource in order to support a procedural API


See:
 itk::simple::GaussianImageSource for the object oriented interface


";

%feature("docstring")  itk::simple::GeodesicActiveContourLevelSet "

 itk::simple::GeodesicActiveContourLevelSetImageFilter Procedural Interface


This function directly calls the execute method of GeodesicActiveContourLevelSetImageFilter in order to support a procedural API


See:
 itk::simple::GeodesicActiveContourLevelSetImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GetPixelIDValueAsString "
";

%feature("docstring")  itk::simple::GetPixelIDValueAsString "
";

%feature("docstring")  itk::simple::Gradient "

 itk::simple::GradientImageFilter Procedural Interface


This function directly calls the execute method of GradientImageFilter in order to support a procedural API


See:
 itk::simple::GradientImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GradientAnisotropicDiffusion "

 itk::simple::GradientAnisotropicDiffusionImageFilter Procedural Interface


This function directly calls the execute method of GradientAnisotropicDiffusionImageFilter in order to support a procedural API


See:
 itk::simple::GradientAnisotropicDiffusionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GradientMagnitude "

 itk::simple::GradientMagnitudeImageFilter Procedural Interface


This function directly calls the execute method of GradientMagnitudeImageFilter in order to support a procedural API


See:
 itk::simple::GradientMagnitudeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GradientMagnitudeRecursiveGaussian "

 itk::simple::GradientMagnitudeRecursiveGaussianImageFilter Procedural Interface


This function directly calls the execute method of GradientMagnitudeRecursiveGaussianImageFilter in order to support a procedural API


See:
 itk::simple::GradientMagnitudeRecursiveGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GradientRecursiveGaussian "

 itk::simple::GradientRecursiveGaussianImageFilter Procedural Interface


This function directly calls the execute method of GradientRecursiveGaussianImageFilter in order to support a procedural API


See:
 itk::simple::GradientRecursiveGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleConnectedClosing "

 itk::simple::GrayscaleConnectedClosingImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleConnectedClosingImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleConnectedClosingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleConnectedOpening "

 itk::simple::GrayscaleConnectedOpeningImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleConnectedOpeningImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleConnectedOpeningImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleDilate "

 itk::simple::GrayscaleDilateImageFilter Functional Interface

This function directly calls the execute method of GrayscaleDilateImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleDilate "

 itk::simple::GrayscaleDilateImageFilter Functional Interface

This function directly calls the execute method of GrayscaleDilateImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleErode "

 itk::simple::GrayscaleErodeImageFilter Functional Interface

This function directly calls the execute method of GrayscaleErodeImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleErode "

 itk::simple::GrayscaleErodeImageFilter Functional Interface

This function directly calls the execute method of GrayscaleErodeImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleFillhole "

 itk::simple::GrayscaleFillholeImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleFillholeImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleFillholeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleGeodesicDilate "

 itk::simple::GrayscaleGeodesicDilateImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleGeodesicDilateImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleGeodesicDilateImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleGeodesicErode "

 itk::simple::GrayscaleGeodesicErodeImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleGeodesicErodeImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleGeodesicErodeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleGrindPeak "

 itk::simple::GrayscaleGrindPeakImageFilter Procedural Interface


This function directly calls the execute method of GrayscaleGrindPeakImageFilter in order to support a procedural API


See:
 itk::simple::GrayscaleGrindPeakImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosing "

 itk::simple::GrayscaleMorphologicalClosingImageFilter Functional Interface

This function directly calls the execute method of GrayscaleMorphologicalClosingImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalClosing "

 itk::simple::GrayscaleMorphologicalClosingImageFilter Functional Interface

This function directly calls the execute method of GrayscaleMorphologicalClosingImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpening "

 itk::simple::GrayscaleMorphologicalOpeningImageFilter Functional Interface

This function directly calls the execute method of GrayscaleMorphologicalOpeningImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::GrayscaleMorphologicalOpening "

 itk::simple::GrayscaleMorphologicalOpeningImageFilter Functional Interface

This function directly calls the execute method of GrayscaleMorphologicalOpeningImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::Greater "
";

%feature("docstring")  itk::simple::Greater "
";

%feature("docstring")  itk::simple::Greater "

 itk::simple::GreaterImageFilter Procedural Interface


This function directly calls the execute method of GreaterImageFilter in order to support a procedural API


See:
 itk::simple::GreaterImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GreaterEqual "
";

%feature("docstring")  itk::simple::GreaterEqual "
";

%feature("docstring")  itk::simple::GreaterEqual "

 itk::simple::GreaterEqualImageFilter Procedural Interface


This function directly calls the execute method of GreaterEqualImageFilter in order to support a procedural API


See:
 itk::simple::GreaterEqualImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::GridSource "

 itk::simple::GridImageSource Procedural Interface


This function directly calls the execute method of GridImageSource in order to support a procedural API


See:
 itk::simple::GridImageSource for the object oriented interface


";

%feature("docstring")  itk::simple::HalfHermitianToRealInverseFFT "

 itk::simple::HalfHermitianToRealInverseFFTImageFilter Procedural Interface


This function directly calls the execute method of HalfHermitianToRealInverseFFTImageFilter in order to support a procedural API


See:
 itk::simple::HalfHermitianToRealInverseFFTImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Hash "
";

%feature("docstring")  itk::simple::HausdorffDistance "

 itk::simple::HausdorffDistanceImageFilter Procedural Interface


This function directly calls the execute method of HausdorffDistanceImageFilter in order to support a procedural API


See:
 itk::simple::HausdorffDistanceImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HConcave "

 itk::simple::HConcaveImageFilter Procedural Interface


This function directly calls the execute method of HConcaveImageFilter in order to support a procedural API


See:
 itk::simple::HConcaveImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HConvex "

 itk::simple::HConvexImageFilter Procedural Interface


This function directly calls the execute method of HConvexImageFilter in order to support a procedural API


See:
 itk::simple::HConvexImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HistogramMatching "

 itk::simple::HistogramMatchingImageFilter Procedural Interface


This function directly calls the execute method of HistogramMatchingImageFilter in order to support a procedural API


See:
 itk::simple::HistogramMatchingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HMaxima "

 itk::simple::HMaximaImageFilter Procedural Interface


This function directly calls the execute method of HMaximaImageFilter in order to support a procedural API


See:
 itk::simple::HMaximaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HMinima "

 itk::simple::HMinimaImageFilter Procedural Interface


This function directly calls the execute method of HMinimaImageFilter in order to support a procedural API


See:
 itk::simple::HMinimaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::HuangThreshold "

 itk::simple::HuangThresholdImageFilter Procedural Interface


This function directly calls the execute method of HuangThresholdImageFilter in order to support a procedural API


See:
 itk::simple::HuangThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ImportAsDouble "
";

%feature("docstring")  itk::simple::ImportAsFloat "
";

%feature("docstring")  itk::simple::ImportAsInt16 "
";

%feature("docstring")  itk::simple::ImportAsInt32 "
";

%feature("docstring")  itk::simple::ImportAsInt8 "
";

%feature("docstring")  itk::simple::ImportAsUInt16 "
";

%feature("docstring")  itk::simple::ImportAsUInt32 "
";

%feature("docstring")  itk::simple::ImportAsUInt8 "
";

%feature("docstring")  itk::simple::IntensityWindowing "

 itk::simple::IntensityWindowingImageFilter Procedural Interface


This function directly calls the execute method of IntensityWindowingImageFilter in order to support a procedural API


See:
 itk::simple::IntensityWindowingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::IntermodesThreshold "

 itk::simple::IntermodesThresholdImageFilter Procedural Interface


This function directly calls the execute method of IntermodesThresholdImageFilter in order to support a procedural API


See:
 itk::simple::IntermodesThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::InverseDeconvolution "

 itk::simple::InverseDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of InverseDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::InverseDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::InverseFFT "

 itk::simple::InverseFFTImageFilter Procedural Interface


This function directly calls the execute method of InverseFFTImageFilter in order to support a procedural API


See:
 itk::simple::InverseFFTImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::InvertIntensity "

 itk::simple::InvertIntensityImageFilter Procedural Interface


This function directly calls the execute method of InvertIntensityImageFilter in order to support a procedural API


See:
 itk::simple::InvertIntensityImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::IsoContourDistance "

 itk::simple::IsoContourDistanceImageFilter Procedural Interface


This function directly calls the execute method of IsoContourDistanceImageFilter in order to support a procedural API


See:
 itk::simple::IsoContourDistanceImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::IsoDataThreshold "

 itk::simple::IsoDataThresholdImageFilter Procedural Interface


This function directly calls the execute method of IsoDataThresholdImageFilter in order to support a procedural API


See:
 itk::simple::IsoDataThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::IsolatedConnected "

 itk::simple::IsolatedConnectedImageFilter Procedural Interface


This function directly calls the execute method of IsolatedConnectedImageFilter in order to support a procedural API


See:
 itk::simple::IsolatedConnectedImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::IsolatedWatershed "

 itk::simple::IsolatedWatershedImageFilter Procedural Interface


This function directly calls the execute method of IsolatedWatershedImageFilter in order to support a procedural API


See:
 itk::simple::IsolatedWatershedImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::JoinSeries "
";

%feature("docstring")  itk::simple::JoinSeries "
";

%feature("docstring")  itk::simple::JoinSeries "
";

%feature("docstring")  itk::simple::JoinSeries "
";

%feature("docstring")  itk::simple::JoinSeries "
";

%feature("docstring")  itk::simple::JoinSeries "

 itk::simple::JoinSeriesImageFilter Procedural Interface


This function directly calls the execute method of JoinSeriesImageFilter in order to support a procedural API


See:
 itk::simple::JoinSeriesImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::KittlerIllingworthThreshold "

 itk::simple::KittlerIllingworthThresholdImageFilter Procedural Interface


This function directly calls the execute method of KittlerIllingworthThresholdImageFilter in order to support a procedural API


See:
 itk::simple::KittlerIllingworthThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelContour "

 itk::simple::LabelContourImageFilter Procedural Interface


This function directly calls the execute method of LabelContourImageFilter in order to support a procedural API


See:
 itk::simple::LabelContourImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapContourOverlay "

 itk::simple::LabelMapContourOverlayImageFilter Procedural Interface


This function directly calls the execute method of LabelMapContourOverlayImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapContourOverlayImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapMask "

 itk::simple::LabelMapMaskImageFilter Procedural Interface


This function directly calls the execute method of LabelMapMaskImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapMaskImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapOverlay "

 itk::simple::LabelMapOverlayImageFilter Procedural Interface


This function directly calls the execute method of LabelMapOverlayImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapOverlayImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapToBinary "

 itk::simple::LabelMapToBinaryImageFilter Procedural Interface


This function directly calls the execute method of LabelMapToBinaryImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapToBinaryImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapToLabel "

 itk::simple::LabelMapToLabelImageFilter Procedural Interface


This function directly calls the execute method of LabelMapToLabelImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapToLabelImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelMapToRGB "

 itk::simple::LabelMapToRGBImageFilter Procedural Interface


This function directly calls the execute method of LabelMapToRGBImageFilter in order to support a procedural API


See:
 itk::simple::LabelMapToRGBImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelOverlay "

 itk::simple::LabelOverlayImageFilter Procedural Interface


This function directly calls the execute method of LabelOverlayImageFilter in order to support a procedural API


See:
 itk::simple::LabelOverlayImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LabelStatistics "
";

%feature("docstring")  itk::simple::LabelToRGB "

 itk::simple::LabelToRGBImageFilter Procedural Interface


This function directly calls the execute method of LabelToRGBImageFilter in order to support a procedural API


See:
 itk::simple::LabelToRGBImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LandweberDeconvolution "

 itk::simple::LandweberDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of LandweberDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::LandweberDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Laplacian "

 itk::simple::LaplacianImageFilter Procedural Interface


This function directly calls the execute method of LaplacianImageFilter in order to support a procedural API


See:
 itk::simple::LaplacianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LaplacianRecursiveGaussian "

 itk::simple::LaplacianRecursiveGaussianImageFilter Procedural Interface


This function directly calls the execute method of LaplacianRecursiveGaussianImageFilter in order to support a procedural API


See:
 itk::simple::LaplacianRecursiveGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LaplacianSegmentationLevelSet "

 itk::simple::LaplacianSegmentationLevelSetImageFilter Procedural Interface


This function directly calls the execute method of LaplacianSegmentationLevelSetImageFilter in order to support a procedural API


See:
 itk::simple::LaplacianSegmentationLevelSetImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LaplacianSharpening "

 itk::simple::LaplacianSharpeningImageFilter Procedural Interface


This function directly calls the execute method of LaplacianSharpeningImageFilter in order to support a procedural API


See:
 itk::simple::LaplacianSharpeningImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Less "
";

%feature("docstring")  itk::simple::Less "
";

%feature("docstring")  itk::simple::Less "

 itk::simple::LessImageFilter Procedural Interface


This function directly calls the execute method of LessImageFilter in order to support a procedural API


See:
 itk::simple::LessImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LessEqual "
";

%feature("docstring")  itk::simple::LessEqual "
";

%feature("docstring")  itk::simple::LessEqual "

 itk::simple::LessEqualImageFilter Procedural Interface


This function directly calls the execute method of LessEqualImageFilter in order to support a procedural API


See:
 itk::simple::LessEqualImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::LiThreshold "

 itk::simple::LiThresholdImageFilter Procedural Interface


This function directly calls the execute method of LiThresholdImageFilter in order to support a procedural API


See:
 itk::simple::LiThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Log "

 itk::simple::LogImageFilter Procedural Interface


This function directly calls the execute method of LogImageFilter in order to support a procedural API


See:
 itk::simple::LogImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Log10 "

 itk::simple::Log10ImageFilter Procedural Interface


This function directly calls the execute method of Log10ImageFilter in order to support a procedural API


See:
 itk::simple::Log10ImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplex "
";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplex "
";

%feature("docstring")  itk::simple::MagnitudeAndPhaseToComplex "

 itk::simple::MagnitudeAndPhaseToComplexImageFilter Procedural Interface


This function directly calls the execute method of MagnitudeAndPhaseToComplexImageFilter in order to support a procedural API


See:
 itk::simple::MagnitudeAndPhaseToComplexImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Mask "

 itk::simple::MaskImageFilter Procedural Interface


This function directly calls the execute method of MaskImageFilter in order to support a procedural API


See:
 itk::simple::MaskImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MaskedFFTNormalizedCorrelation "

 itk::simple::MaskedFFTNormalizedCorrelationImageFilter Procedural Interface


This function directly calls the execute method of MaskedFFTNormalizedCorrelationImageFilter in order to support a procedural API


See:
 itk::simple::MaskedFFTNormalizedCorrelationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MaskNegated "

 itk::simple::MaskNegatedImageFilter Procedural Interface


This function directly calls the execute method of MaskNegatedImageFilter in order to support a procedural API


See:
 itk::simple::MaskNegatedImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Maximum "
";

%feature("docstring")  itk::simple::Maximum "
";

%feature("docstring")  itk::simple::Maximum "

 itk::simple::MaximumImageFilter Procedural Interface


This function directly calls the execute method of MaximumImageFilter in order to support a procedural API


See:
 itk::simple::MaximumImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MaximumEntropyThreshold "

 itk::simple::MaximumEntropyThresholdImageFilter Procedural Interface


This function directly calls the execute method of MaximumEntropyThresholdImageFilter in order to support a procedural API


See:
 itk::simple::MaximumEntropyThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MaximumProjection "

 itk::simple::MaximumProjectionImageFilter Procedural Interface


This function directly calls the execute method of MaximumProjectionImageFilter in order to support a procedural API


See:
 itk::simple::MaximumProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Mean "

 itk::simple::MeanImageFilter Procedural Interface


This function directly calls the execute method of MeanImageFilter in order to support a procedural API


See:
 itk::simple::MeanImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MeanProjection "

 itk::simple::MeanProjectionImageFilter Procedural Interface


This function directly calls the execute method of MeanProjectionImageFilter in order to support a procedural API


See:
 itk::simple::MeanProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Median "

 itk::simple::MedianImageFilter Procedural Interface


This function directly calls the execute method of MedianImageFilter in order to support a procedural API


See:
 itk::simple::MedianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MedianProjection "

 itk::simple::MedianProjectionImageFilter Procedural Interface


This function directly calls the execute method of MedianProjectionImageFilter in order to support a procedural API


See:
 itk::simple::MedianProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Minimum "
";

%feature("docstring")  itk::simple::Minimum "
";

%feature("docstring")  itk::simple::Minimum "

 itk::simple::MinimumImageFilter Procedural Interface


This function directly calls the execute method of MinimumImageFilter in order to support a procedural API


See:
 itk::simple::MinimumImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MinimumMaximum "

 itk::simple::MinimumMaximumImageFilter Procedural Interface


This function directly calls the execute method of MinimumMaximumImageFilter in order to support a procedural API


See:
 itk::simple::MinimumMaximumImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MinimumProjection "

 itk::simple::MinimumProjectionImageFilter Procedural Interface


This function directly calls the execute method of MinimumProjectionImageFilter in order to support a procedural API


See:
 itk::simple::MinimumProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MinMaxCurvatureFlow "

 itk::simple::MinMaxCurvatureFlowImageFilter Procedural Interface


This function directly calls the execute method of MinMaxCurvatureFlowImageFilter in order to support a procedural API


See:
 itk::simple::MinMaxCurvatureFlowImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MirrorPad "

 itk::simple::MirrorPadImageFilter Procedural Interface


This function directly calls the execute method of MirrorPadImageFilter in order to support a procedural API


See:
 itk::simple::MirrorPadImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Modulus "
";

%feature("docstring")  itk::simple::Modulus "
";

%feature("docstring")  itk::simple::Modulus "

 itk::simple::ModulusImageFilter Procedural Interface


This function directly calls the execute method of ModulusImageFilter in order to support a procedural API


See:
 itk::simple::ModulusImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MomentsThreshold "

 itk::simple::MomentsThresholdImageFilter Procedural Interface


This function directly calls the execute method of MomentsThresholdImageFilter in order to support a procedural API


See:
 itk::simple::MomentsThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MorphologicalGradient "

 itk::simple::MorphologicalGradientImageFilter Functional Interface

This function directly calls the execute method of MorphologicalGradientImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::MorphologicalGradient "

 itk::simple::MorphologicalGradientImageFilter Functional Interface

This function directly calls the execute method of MorphologicalGradientImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::MorphologicalWatershed "

 itk::simple::MorphologicalWatershedImageFilter Procedural Interface


This function directly calls the execute method of MorphologicalWatershedImageFilter in order to support a procedural API


See:
 itk::simple::MorphologicalWatershedImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::MorphologicalWatershedFromMarkers "

 itk::simple::MorphologicalWatershedFromMarkersImageFilter Procedural Interface


This function directly calls the execute method of MorphologicalWatershedFromMarkersImageFilter in order to support a procedural API


See:
 itk::simple::MorphologicalWatershedFromMarkersImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Multiply "
";

%feature("docstring")  itk::simple::Multiply "
";

%feature("docstring")  itk::simple::Multiply "

 itk::simple::MultiplyImageFilter Procedural Interface


This function directly calls the execute method of MultiplyImageFilter in order to support a procedural API


See:
 itk::simple::MultiplyImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::N4BiasFieldCorrection "

 itk::simple::N4BiasFieldCorrectionImageFilter Procedural Interface


This function directly calls the execute method of N4BiasFieldCorrectionImageFilter in order to support a procedural API


See:
 itk::simple::N4BiasFieldCorrectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NaryAdd "
";

%feature("docstring")  itk::simple::NaryAdd "
";

%feature("docstring")  itk::simple::NaryAdd "
";

%feature("docstring")  itk::simple::NaryAdd "
";

%feature("docstring")  itk::simple::NaryAdd "
";

%feature("docstring")  itk::simple::NaryAdd "

 itk::simple::NaryAddImageFilter Procedural Interface


This function directly calls the execute method of NaryAddImageFilter in order to support a procedural API


See:
 itk::simple::NaryAddImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NaryMaximum "
";

%feature("docstring")  itk::simple::NaryMaximum "
";

%feature("docstring")  itk::simple::NaryMaximum "
";

%feature("docstring")  itk::simple::NaryMaximum "
";

%feature("docstring")  itk::simple::NaryMaximum "
";

%feature("docstring")  itk::simple::NaryMaximum "

 itk::simple::NaryMaximumImageFilter Procedural Interface


This function directly calls the execute method of NaryMaximumImageFilter in order to support a procedural API


See:
 itk::simple::NaryMaximumImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NeighborhoodConnected "

 itk::simple::NeighborhoodConnectedImageFilter Functional Interface

This function directly calls the execute method of NeighborhoodConnectedImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::Noise "

 itk::simple::NoiseImageFilter Procedural Interface


This function directly calls the execute method of NoiseImageFilter in order to support a procedural API


See:
 itk::simple::NoiseImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Normalize "

 itk::simple::NormalizeImageFilter Procedural Interface


This function directly calls the execute method of NormalizeImageFilter in order to support a procedural API


See:
 itk::simple::NormalizeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NormalizedCorrelation "

 itk::simple::NormalizedCorrelationImageFilter Procedural Interface


This function directly calls the execute method of NormalizedCorrelationImageFilter in order to support a procedural API


See:
 itk::simple::NormalizedCorrelationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NormalizeToConstant "

 itk::simple::NormalizeToConstantImageFilter Procedural Interface


This function directly calls the execute method of NormalizeToConstantImageFilter in order to support a procedural API


See:
 itk::simple::NormalizeToConstantImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Not "

 itk::simple::NotImageFilter Procedural Interface


This function directly calls the execute method of NotImageFilter in order to support a procedural API


See:
 itk::simple::NotImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::NotEqual "
";

%feature("docstring")  itk::simple::NotEqual "
";

%feature("docstring")  itk::simple::NotEqual "

 itk::simple::NotEqualImageFilter Procedural Interface


This function directly calls the execute method of NotEqualImageFilter in order to support a procedural API


See:
 itk::simple::NotEqualImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::OpeningByReconstruction "

 itk::simple::OpeningByReconstructionImageFilter Functional Interface

This function directly calls the execute method of OpeningByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::OpeningByReconstruction "

 itk::simple::OpeningByReconstructionImageFilter Functional Interface

This function directly calls the execute method of OpeningByReconstructionImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::Or "
";

%feature("docstring")  itk::simple::Or "
";

%feature("docstring")  itk::simple::Or "

 itk::simple::OrImageFilter Procedural Interface


This function directly calls the execute method of OrImageFilter in order to support a procedural API


See:
 itk::simple::OrImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::OtsuMultipleThresholds "

 itk::simple::OtsuMultipleThresholdsImageFilter Procedural Interface


This function directly calls the execute method of OtsuMultipleThresholdsImageFilter in order to support a procedural API


See:
 itk::simple::OtsuMultipleThresholdsImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::OtsuThreshold "

 itk::simple::OtsuThresholdImageFilter Procedural Interface


This function directly calls the execute method of OtsuThresholdImageFilter in order to support a procedural API


See:
 itk::simple::OtsuThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Paste "

 itk::simple::PasteImageFilter Procedural Interface


This function directly calls the execute method of PasteImageFilter in order to support a procedural API


See:
 itk::simple::PasteImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::PermuteAxes "

 itk::simple::PermuteAxesImageFilter Procedural Interface


This function directly calls the execute method of PermuteAxesImageFilter in order to support a procedural API


See:
 itk::simple::PermuteAxesImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::PhysicalPointSource "

 itk::simple::PhysicalPointImageSource Procedural Interface


This function directly calls the execute method of PhysicalPointImageSource in order to support a procedural API


See:
 itk::simple::PhysicalPointImageSource for the object oriented interface


";

%feature("docstring")  itk::simple::Pow "
";

%feature("docstring")  itk::simple::Pow "
";

%feature("docstring")  itk::simple::Pow "

 itk::simple::PowImageFilter Procedural Interface


This function directly calls the execute method of PowImageFilter in order to support a procedural API


See:
 itk::simple::PowImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ProjectedLandweberDeconvolution "

 itk::simple::ProjectedLandweberDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of ProjectedLandweberDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::ProjectedLandweberDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Rank "

 itk::simple::RankImageFilter Procedural Interface


This function directly calls the execute method of RankImageFilter in order to support a procedural API


See:
 itk::simple::RankImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ReadImage "
";

%feature("docstring")  itk::simple::ReadImage "
";

%feature("docstring")  itk::simple::ReadTransform "
";

%feature("docstring")  itk::simple::RealAndImaginaryToComplex "

 itk::simple::RealAndImaginaryToComplexImageFilter Procedural Interface


This function directly calls the execute method of RealAndImaginaryToComplexImageFilter in order to support a procedural API


See:
 itk::simple::RealAndImaginaryToComplexImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RealToHalfHermitianForwardFFT "

 itk::simple::RealToHalfHermitianForwardFFTImageFilter Procedural Interface


This function directly calls the execute method of RealToHalfHermitianForwardFFTImageFilter in order to support a procedural API


See:
 itk::simple::RealToHalfHermitianForwardFFTImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ReconstructionByDilation "

 itk::simple::ReconstructionByDilationImageFilter Procedural Interface


This function directly calls the execute method of ReconstructionByDilationImageFilter in order to support a procedural API


See:
 itk::simple::ReconstructionByDilationImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ReconstructionByErosion "

 itk::simple::ReconstructionByErosionImageFilter Procedural Interface


This function directly calls the execute method of ReconstructionByErosionImageFilter in order to support a procedural API


See:
 itk::simple::ReconstructionByErosionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RecursiveGaussian "

 itk::simple::RecursiveGaussianImageFilter Procedural Interface


This function directly calls the execute method of RecursiveGaussianImageFilter in order to support a procedural API


See:
 itk::simple::RecursiveGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RegionalMaxima "

 itk::simple::RegionalMaximaImageFilter Procedural Interface


This function directly calls the execute method of RegionalMaximaImageFilter in order to support a procedural API


See:
 itk::simple::RegionalMaximaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RegionalMinima "

 itk::simple::RegionalMinimaImageFilter Procedural Interface


This function directly calls the execute method of RegionalMinimaImageFilter in order to support a procedural API


See:
 itk::simple::RegionalMinimaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RegionOfInterest "

 itk::simple::RegionOfInterestImageFilter Procedural Interface


This function directly calls the execute method of RegionOfInterestImageFilter in order to support a procedural API


See:
 itk::simple::RegionOfInterestImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RelabelComponent "

 itk::simple::RelabelComponentImageFilter Procedural Interface


This function directly calls the execute method of RelabelComponentImageFilter in order to support a procedural API


See:
 itk::simple::RelabelComponentImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RenyiEntropyThreshold "

 itk::simple::RenyiEntropyThresholdImageFilter Procedural Interface


This function directly calls the execute method of RenyiEntropyThresholdImageFilter in order to support a procedural API


See:
 itk::simple::RenyiEntropyThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RescaleIntensity "

 itk::simple::RescaleIntensityImageFilter Procedural Interface


This function directly calls the execute method of RescaleIntensityImageFilter in order to support a procedural API


See:
 itk::simple::RescaleIntensityImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::RichardsonLucyDeconvolution "

 itk::simple::RichardsonLucyDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of RichardsonLucyDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::RichardsonLucyDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ScalarConnectedComponent "

 itk::simple::ScalarConnectedComponentImageFilter Procedural Interface


This function directly calls the execute method of ScalarConnectedComponentImageFilter in order to support a procedural API


See:
 itk::simple::ScalarConnectedComponentImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ScalarImageKmeans "

 itk::simple::ScalarImageKmeansImageFilter Procedural Interface


This function directly calls the execute method of ScalarImageKmeansImageFilter in order to support a procedural API


See:
 itk::simple::ScalarImageKmeansImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ScalarToRGBColormap "

 itk::simple::ScalarToRGBColormapImageFilter Procedural Interface


This function directly calls the execute method of ScalarToRGBColormapImageFilter in order to support a procedural API


See:
 itk::simple::ScalarToRGBColormapImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ShanbhagThreshold "

 itk::simple::ShanbhagThresholdImageFilter Procedural Interface


This function directly calls the execute method of ShanbhagThresholdImageFilter in order to support a procedural API


See:
 itk::simple::ShanbhagThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ShapeDetectionLevelSet "

 itk::simple::ShapeDetectionLevelSetImageFilter Procedural Interface


This function directly calls the execute method of ShapeDetectionLevelSetImageFilter in order to support a procedural API


See:
 itk::simple::ShapeDetectionLevelSetImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ShiftScale "

 itk::simple::ShiftScaleImageFilter Procedural Interface


This function directly calls the execute method of ShiftScaleImageFilter in order to support a procedural API


See:
 itk::simple::ShiftScaleImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Show "

Display an image using ImageJ

This function requires that ImageJ (http://rsb.info.nih.gov/ij/) be properly installed for Mac and Windows, and in the user's path
for Linux. ImageJ must have a plugin for reading Nifti formatted files
(http://www.loci.wisc.edu/bio-formats/imagej).

Nifti is the default file format used to export images. A different
format can by chosen by setting the SITK_SHOW_EXTENSION environment
variable. For example, set SITK_SHOW_EXTENSION to \".png\" to use PNG
format.

The user can specify an application other than ImageJ to view images
via the SITK_SHOW_COMMAND environment variable.

The user can also select applications specifically for color images or
3D images using the SITK_SHOW_COLOR_COMMAND and SITK_SHOW_3D_COMMAND
environment variables.

SITK_SHOW_COMMAND, SITK_SHOW_COLOR_COMMAND and SITK_SHOW_3D_COMMAND
allow the following tokens in their strings.


 \"%a\" for the ImageJ application

 \"%f\" for SimpleITK's temporary image file
 For example, the default SITK_SHOW_COMMAND string on Linux systems
is:


After token substitution it may become:


For another example, the default SITK_SHOW_COLOR_COMMAND string on Mac
OS X is:


After token substitution the string may become:


The string after \"-eval\" is an ImageJ macro the opens the file and runs ImageJ's Make
Composite command to display the image in color.

If the \"%f\" token is not found in the command string, the temporary file name is
automatically appended to the command argument list.

By default, for a 64-bit build of SimpleITK on Macs, sitkShow searches
for ImageJ64.app. For a 32-bit Mac build, sitkShow searches for
ImageJ.app. If the user prefers a different version of ImageJ (or a
different image viewer altogether), it can be specified using the
SITK_SHOW_COMMAND environment variable.

";

%feature("docstring")  itk::simple::Shrink "

 itk::simple::ShrinkImageFilter Procedural Interface


This function directly calls the execute method of ShrinkImageFilter in order to support a procedural API


See:
 itk::simple::ShrinkImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Sigmoid "

 itk::simple::SigmoidImageFilter Procedural Interface


This function directly calls the execute method of SigmoidImageFilter in order to support a procedural API


See:
 itk::simple::SigmoidImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SignedDanielssonDistanceMap "

 itk::simple::SignedDanielssonDistanceMapImageFilter Procedural Interface


This function directly calls the execute method of SignedDanielssonDistanceMapImageFilter in order to support a procedural API


See:
 itk::simple::SignedDanielssonDistanceMapImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SignedMaurerDistanceMap "

 itk::simple::SignedMaurerDistanceMapImageFilter Procedural Interface


This function directly calls the execute method of SignedMaurerDistanceMapImageFilter in order to support a procedural API


See:
 itk::simple::SignedMaurerDistanceMapImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SimilarityIndex "

 itk::simple::SimilarityIndexImageFilter Procedural Interface


This function directly calls the execute method of SimilarityIndexImageFilter in order to support a procedural API


See:
 itk::simple::SimilarityIndexImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SimpleContourExtractor "

 itk::simple::SimpleContourExtractorImageFilter Procedural Interface


This function directly calls the execute method of SimpleContourExtractorImageFilter in order to support a procedural API


See:
 itk::simple::SimpleContourExtractorImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Sin "

 itk::simple::SinImageFilter Procedural Interface


This function directly calls the execute method of SinImageFilter in order to support a procedural API


See:
 itk::simple::SinImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::sitkITKVectorToSTL "

Convert an ITK fixed width vector to a std::vector.

";

%feature("docstring")  itk::simple::sitkSTLVectorToITK "

Copy the elements of an std::vector into an ITK fixed width vector.


If there are more elements in paramter \"in\" than the templated ITK
vector type, they are truncated. If less, then an exception is
generated.

";

%feature("docstring")  itk::simple::Slice "

 itk::simple::SliceImageFilter Procedural Interface


This function directly calls the execute method of SliceImageFilter in order to support a procedural API


See:
 itk::simple::SliceImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SmoothingRecursiveGaussian "

 itk::simple::SmoothingRecursiveGaussianImageFilter Procedural Interface


This function directly calls the execute method of SmoothingRecursiveGaussianImageFilter in order to support a procedural API


See:
 itk::simple::SmoothingRecursiveGaussianImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SobelEdgeDetection "

 itk::simple::SobelEdgeDetectionImageFilter Procedural Interface


This function directly calls the execute method of SobelEdgeDetectionImageFilter in order to support a procedural API


See:
 itk::simple::SobelEdgeDetectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Sqrt "

 itk::simple::SqrtImageFilter Procedural Interface


This function directly calls the execute method of SqrtImageFilter in order to support a procedural API


See:
 itk::simple::SqrtImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Square "

 itk::simple::SquareImageFilter Procedural Interface


This function directly calls the execute method of SquareImageFilter in order to support a procedural API


See:
 itk::simple::SquareImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SquaredDifference "
";

%feature("docstring")  itk::simple::SquaredDifference "
";

%feature("docstring")  itk::simple::SquaredDifference "

 itk::simple::SquaredDifferenceImageFilter Procedural Interface


This function directly calls the execute method of SquaredDifferenceImageFilter in order to support a procedural API


See:
 itk::simple::SquaredDifferenceImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::StandardDeviationProjection "

 itk::simple::StandardDeviationProjectionImageFilter Procedural Interface


This function directly calls the execute method of StandardDeviationProjectionImageFilter in order to support a procedural API


See:
 itk::simple::StandardDeviationProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::STAPLE "
";

%feature("docstring")  itk::simple::STAPLE "
";

%feature("docstring")  itk::simple::STAPLE "
";

%feature("docstring")  itk::simple::STAPLE "
";

%feature("docstring")  itk::simple::STAPLE "
";

%feature("docstring")  itk::simple::STAPLE "

 itk::simple::STAPLEImageFilter Procedural Interface


This function directly calls the execute method of STAPLEImageFilter in order to support a procedural API


See:
 itk::simple::STAPLEImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Statistics "
";

%feature("docstring")  itk::simple::Subtract "
";

%feature("docstring")  itk::simple::Subtract "
";

%feature("docstring")  itk::simple::Subtract "

 itk::simple::SubtractImageFilter Procedural Interface


This function directly calls the execute method of SubtractImageFilter in order to support a procedural API


See:
 itk::simple::SubtractImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::SumProjection "

 itk::simple::SumProjectionImageFilter Procedural Interface


This function directly calls the execute method of SumProjectionImageFilter in order to support a procedural API


See:
 itk::simple::SumProjectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Tan "

 itk::simple::TanImageFilter Procedural Interface


This function directly calls the execute method of TanImageFilter in order to support a procedural API


See:
 itk::simple::TanImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::TernaryAdd "

 itk::simple::TernaryAddImageFilter Procedural Interface


This function directly calls the execute method of TernaryAddImageFilter in order to support a procedural API


See:
 itk::simple::TernaryAddImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::TernaryMagnitude "

 itk::simple::TernaryMagnitudeImageFilter Procedural Interface


This function directly calls the execute method of TernaryMagnitudeImageFilter in order to support a procedural API


See:
 itk::simple::TernaryMagnitudeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::TernaryMagnitudeSquared "

 itk::simple::TernaryMagnitudeSquaredImageFilter Procedural Interface


This function directly calls the execute method of TernaryMagnitudeSquaredImageFilter in order to support a procedural API


See:
 itk::simple::TernaryMagnitudeSquaredImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Threshold "

 itk::simple::ThresholdImageFilter Procedural Interface


This function directly calls the execute method of ThresholdImageFilter in order to support a procedural API


See:
 itk::simple::ThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ThresholdMaximumConnectedComponents "

 itk::simple::ThresholdMaximumConnectedComponentsImageFilter Procedural Interface


This function directly calls the execute method of ThresholdMaximumConnectedComponentsImageFilter in order to support a procedural API


See:
 itk::simple::ThresholdMaximumConnectedComponentsImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ThresholdSegmentationLevelSet "

 itk::simple::ThresholdSegmentationLevelSetImageFilter Procedural Interface


This function directly calls the execute method of ThresholdSegmentationLevelSetImageFilter in order to support a procedural API


See:
 itk::simple::ThresholdSegmentationLevelSetImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::TikhonovDeconvolution "

 itk::simple::TikhonovDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of TikhonovDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::TikhonovDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Tile "
";

%feature("docstring")  itk::simple::Tile "
";

%feature("docstring")  itk::simple::Tile "
";

%feature("docstring")  itk::simple::Tile "
";

%feature("docstring")  itk::simple::Tile "
";

%feature("docstring")  itk::simple::Tile "

 itk::simple::TileImageFilter Procedural Interface


This function directly calls the execute method of TileImageFilter in order to support a procedural API


See:
 itk::simple::TileImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::TriangleThreshold "

 itk::simple::TriangleThresholdImageFilter Procedural Interface


This function directly calls the execute method of TriangleThresholdImageFilter in order to support a procedural API


See:
 itk::simple::TriangleThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::UnaryMinus "

 itk::simple::UnaryMinusImageFilter Procedural Interface


This function directly calls the execute method of UnaryMinusImageFilter in order to support a procedural API


See:
 itk::simple::UnaryMinusImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::Unused "

A function which does nothing.


This function is to be used to mark parameters as unused to supress
compiler warning.

";

%feature("docstring")  itk::simple::ValuedRegionalMaxima "

 itk::simple::ValuedRegionalMaximaImageFilter Procedural Interface


This function directly calls the execute method of ValuedRegionalMaximaImageFilter in order to support a procedural API


See:
 itk::simple::ValuedRegionalMaximaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ValuedRegionalMinima "

 itk::simple::ValuedRegionalMinimaImageFilter Procedural Interface


This function directly calls the execute method of ValuedRegionalMinimaImageFilter in order to support a procedural API


See:
 itk::simple::ValuedRegionalMinimaImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VectorConfidenceConnected "

 itk::simple::VectorConfidenceConnectedImageFilter Functional Interface

This function directly calls the execute method of VectorConfidenceConnectedImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::VectorConnectedComponent "

 itk::simple::VectorConnectedComponentImageFilter Procedural Interface


This function directly calls the execute method of VectorConnectedComponentImageFilter in order to support a procedural API


See:
 itk::simple::VectorConnectedComponentImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VectorIndexSelectionCast "

 itk::simple::VectorIndexSelectionCastImageFilter Procedural Interface


This function directly calls the execute method of VectorIndexSelectionCastImageFilter in order to support a procedural API


See:
 itk::simple::VectorIndexSelectionCastImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VectorMagnitude "

 itk::simple::VectorMagnitudeImageFilter Procedural Interface


This function directly calls the execute method of VectorMagnitudeImageFilter in order to support a procedural API


See:
 itk::simple::VectorMagnitudeImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VotingBinary "

 itk::simple::VotingBinaryImageFilter Procedural Interface


This function directly calls the execute method of VotingBinaryImageFilter in order to support a procedural API


See:
 itk::simple::VotingBinaryImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VotingBinaryHoleFilling "

 itk::simple::VotingBinaryHoleFillingImageFilter Procedural Interface


This function directly calls the execute method of VotingBinaryHoleFillingImageFilter in order to support a procedural API


See:
 itk::simple::VotingBinaryHoleFillingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::VotingBinaryIterativeHoleFilling "

 itk::simple::VotingBinaryIterativeHoleFillingImageFilter Procedural Interface


This function directly calls the execute method of VotingBinaryIterativeHoleFillingImageFilter in order to support a procedural API


See:
 itk::simple::VotingBinaryIterativeHoleFillingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::WhiteTopHat "

 itk::simple::WhiteTopHatImageFilter Functional Interface

This function directly calls the execute method of WhiteTopHatImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::WhiteTopHat "

 itk::simple::WhiteTopHatImageFilter Functional Interface

This function directly calls the execute method of WhiteTopHatImageFilter in order to support a fully functional API

";

%feature("docstring")  itk::simple::WienerDeconvolution "

 itk::simple::WienerDeconvolutionImageFilter Procedural Interface


This function directly calls the execute method of WienerDeconvolutionImageFilter in order to support a procedural API


See:
 itk::simple::WienerDeconvolutionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::WrapPad "

 itk::simple::WrapPadImageFilter Procedural Interface


This function directly calls the execute method of WrapPadImageFilter in order to support a procedural API


See:
 itk::simple::WrapPadImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::WriteImage "
";

%feature("docstring")  itk::simple::WriteTransform "
";

%feature("docstring")  itk::simple::Xor "
";

%feature("docstring")  itk::simple::Xor "
";

%feature("docstring")  itk::simple::Xor "

 itk::simple::XorImageFilter Procedural Interface


This function directly calls the execute method of XorImageFilter in order to support a procedural API


See:
 itk::simple::XorImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::YenThreshold "

 itk::simple::YenThresholdImageFilter Procedural Interface


This function directly calls the execute method of YenThresholdImageFilter in order to support a procedural API


See:
 itk::simple::YenThresholdImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ZeroCrossing "

 itk::simple::ZeroCrossingImageFilter Procedural Interface


This function directly calls the execute method of ZeroCrossingImageFilter in order to support a procedural API


See:
 itk::simple::ZeroCrossingImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ZeroCrossingBasedEdgeDetection "

 itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter Procedural Interface


This function directly calls the execute method of ZeroCrossingBasedEdgeDetectionImageFilter in order to support a procedural API


See:
 itk::simple::ZeroCrossingBasedEdgeDetectionImageFilter for the object oriented interface


";

%feature("docstring")  itk::simple::ZeroFluxNeumannPad "

 itk::simple::ZeroFluxNeumannPadImageFilter Procedural Interface


This function directly calls the execute method of ZeroFluxNeumannPadImageFilter in order to support a procedural API


See:
 itk::simple::ZeroFluxNeumannPadImageFilter for the object oriented interface


";


%feature("docstring") itk::simple::BasicPixelID "

This type is used as an identity for pixel of itk::Image type

This is an empty type which is used for compile-time meta-programming.
It does not contain any information, an image type can be converted to
one of the PixelID types, and an PixelID can be converted to a value.
However, a run-time value can not be converted to this compile time
type.


See:
PixelIDToImageType

ImageTypeToPixelID

 ImageTypeToPixelIDValue

 PixelIDToPixelIDValue


C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::Conditional "
C++ includes: sitkConditional.h
";


%feature("docstring") itk::simple::ConditionalValue "
C++ includes: sitkConditional.h
";


%feature("docstring") itk::simple::DisableIf "
C++ includes: sitkEnableIf.h
";


%feature("docstring") itk::simple::EnableIf "
C++ includes: sitkEnableIf.h
";


%feature("docstring") itk::simple::ImageTypeToPixelIDValue "
C++ includes: sitkPixelIDValues.h
";


%feature("docstring") itk::simple::ImageTypeToPixelID< itk::Image< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::ImageTypeToPixelID< itk::VectorImage< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::IsBasic "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsBasic< BasicPixelID< TPixelType > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsBasic< itk::Image< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsInstantiated "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsInstantiated< itk::Image< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsInstantiated< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsInstantiated< itk::VectorImage< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsLabel "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsLabel< LabelPixelID< TPixelType > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsLabel< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsVector "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsVector< VectorPixelID< TPixelType > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::IsVector< itk::VectorImage< TPixelType, VImageDimension > > "
C++ includes: sitkPixelIDTokens.h
";


%feature("docstring") itk::simple::LabelPixelID "

This type is used as an identity for pixel of itk::LabelMap type

This is an empty type which is used for compile-time meta-programming.
It does not contain any information, an image type can be converted to
one of the PixelID types, and an PixelID can be converted to a value.
However, a run-time value can not be converted to this compile time
type.


See:
PixelIDToImageType

ImageTypeToPixelID

 ImageTypeToPixelIDValue

 PixelIDToPixelIDValue


C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::PixelIDToImageType< BasicPixelID< TPixelType >, VImageDimension > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::PixelIDToImageType< LabelPixelID< TLabelType >, VImageDimension > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::PixelIDToImageType< VectorPixelID< TVectorPixelType >, VImageDimension > "
C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::PixelIDToPixelIDValue "
C++ includes: sitkPixelIDValues.h
";


%feature("docstring") itk::simple::StaticAssertFailure< true > "
C++ includes: sitkMacro.h
";


%feature("docstring") itk::simple::VectorPixelID "

This type is used as an identity for pixel of itk::VectorImage type

This is an empty type which is used for compile-time meta-programming.
It does not contain any information, an image type can be converted to
one of the PixelID types, and an PixelID can be converted to a value.
However, a run-time value can not be converted to this compile time
type.


See:
PixelIDToImageType

ImageTypeToPixelID

 ImageTypeToPixelIDValue

 PixelIDToPixelIDValue


C++ includes: sitkPixelIDTypes.h
";


%feature("docstring") itk::simple::DualExecuteInternalAddressor "
C++ includes: sitkDetail.h
";


%feature("docstring") itk::simple::ExecuteInternalLabelImageAddressor "

An addressor of ExecuteInternal to be utilized with registering member
functions with the factory.

C++ includes: sitkDetail.h
";


%feature("docstring") itk::simple::ExecuteInternalVectorImageAddressor "

An addressor of ExecuteInternalCast to be utilized with registering
member functions with the factory.

C++ includes: sitkDetail.h
";


%feature("docstring") itk::simple::MemberFunctionAddressor "
C++ includes: sitkDetail.h
";
