// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AbsImageFilter.xml
%feature("docstring") itk::simple::AbsImageFilter "Computes the ABS(x) pixel-wise.


li {ImageProcessing/AbsImageFilter,Compute the absolute value of an image}

"
%feature("docstring") itk::simple::AbsImageFilter::Execute "Computes the ABS(x) pixel-wise.
"
%feature("docstring") itk::simple::Abs "Computes the ABS(x) pixel-wise.


li {ImageProcessing/AbsImageFilter,Compute the absolute value of an image}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AcosImageFilter.xml
%feature("docstring") itk::simple::AcosImageFilter "Computes the vcl_acos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_acos() function to the double value
li cast the double value resulting from vcl_acos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND).
"
%feature("docstring") itk::simple::AcosImageFilter::Execute "Computes the vcl_acos(x) pixel-wise.
"
%feature("docstring") itk::simple::Acos "Computes the vcl_acos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_acos() function to the double value
li cast the double value resulting from vcl_acos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND).
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AddConstantToImageFilter.xml
%feature("docstring") itk::simple::AddConstantToImageFilter "Add a constant to all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
Based on filters from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter
li {ImageProcessing/AddConstantToImageFilter,Add a constant to every pixel in an image}


"
%feature("docstring") itk::simple::AddConstantToImageFilter::Execute "Add a constant to all input pixels.
"
%feature("docstring") itk::simple::AddConstantTo "Add a constant to all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
Based on filters from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter
li {ImageProcessing/AddConstantToImageFilter,Add a constant to every pixel in an image}


"
%feature("docstring") itk::simple::AddConstantToImageFilter::SetConstant "void itk::AddConstantToImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
"

%feature("docstring") itk::simple::AddConstantToImageFilter::GetConstant "const TConstant& itk::AddConstantToImageFilter::GetConstant() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AddImageFilter.xml
%feature("docstring") itk::simple::AddImageFilter "Implements an operator for pixel-wise addition of two images.

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

"
%feature("docstring") itk::simple::AddImageFilter::Execute "Implements an operator for pixel-wise addition of two images.
"
%feature("docstring") itk::simple::Add "Implements an operator for pixel-wise addition of two images.

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

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AndImageFilter.xml
%feature("docstring") itk::simple::AndImageFilter "Implements the AND logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical AND operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel & input2_pixel )
Where & is the boolean AND operator in C++.

li {ImageProcessing/AndImageFilter,Binary AND two images}

"
%feature("docstring") itk::simple::AndImageFilter::Execute "Implements the AND logical operator pixel-wise between two images.
"
%feature("docstring") itk::simple::And "Implements the AND logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical AND operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel & input2_pixel )
Where & is the boolean AND operator in C++.

li {ImageProcessing/AndImageFilter,Binary AND two images}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AsinImageFilter.xml
%feature("docstring") itk::simple::AsinImageFilter "Computes the vcl_asin(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_asin() function to the double value
li cast the double value resulting from vcl_asin() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
%feature("docstring") itk::simple::AsinImageFilter::Execute "Computes the vcl_asin(x) pixel-wise.
"
%feature("docstring") itk::simple::Asin "Computes the vcl_asin(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_asin() function to the double value
li cast the double value resulting from vcl_asin() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1Atan2ImageFilter.xml
%feature("docstring") itk::simple::Atan2ImageFilter "Computes arctangent pixel-wise from two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Both pixel input types are casted to double in order to be used as parameters of vcl_atan2() . The resulting double value is casted to the output pixel type.
"
%feature("docstring") itk::simple::Atan2ImageFilter::Execute "Computes arctangent pixel-wise from two images.
"
%feature("docstring") itk::simple::Atan2 "Computes arctangent pixel-wise from two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Both pixel input types are casted to double in order to be used as parameters of vcl_atan2() . The resulting double value is casted to the output pixel type.
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1AtanImageFilter.xml
%feature("docstring") itk::simple::AtanImageFilter "Computes the vcl_atan(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_atan() function to the double value
li cast the double value resulting from vcl_atan() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
%feature("docstring") itk::simple::AtanImageFilter::Execute "Computes the vcl_atan(x) pixel-wise.
"
%feature("docstring") itk::simple::Atan "Computes the vcl_atan(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_atan() function to the double value
li cast the double value resulting from vcl_atan() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryClosingByReconstructionImageFilter.xml
%feature("docstring") itk::simple::BinaryClosingByReconstructionImageFilter "binary closing by reconstruction of an image.

This filter removes small ( i.e., smaller than the structuring element) holes in the image. It is defined as: Closing(f) = ReconstructionByErosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

"
%feature("docstring") itk::simple::BinaryClosingByReconstructionImageFilter::Execute "binary closing by reconstruction of an image.
"
%feature("docstring") itk::simple::BinaryClosingByReconstruction "binary closing by reconstruction of an image.

This filter removes small ( i.e., smaller than the structuring element) holes in the image. It is defined as: Closing(f) = ReconstructionByErosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

"
%feature("docstring") itk::simple::BinaryClosingByReconstructionImageFilter::SetFullyConnected "virtual void itk::BinaryClosingByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::BinaryClosingByReconstructionImageFilter::GetFullyConnected "virtual const bool& itk::BinaryClosingByReconstructionImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryContourImageFilter.xml
%feature("docstring") itk::simple::BinaryContourImageFilter "Labels the pixels on the border of the objects in a binary image.

 BinaryContourImageFiltertakes a binary image as input, where the pixels in the objects are the pixels with a value equal to ForegroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
li {EdgesAndGradients/BinaryContourImageFilter,Extract the boundaries of connected regions in a binary image} {EdgesAndGradients/BinaryBoundaries,Extract the inner and outer boundaries of blobs in a binary image}


"
%feature("docstring") itk::simple::BinaryContourImageFilter::Execute "Labels the pixels on the border of the objects in a binary image.
"
%feature("docstring") itk::simple::BinaryContour "Labels the pixels on the border of the objects in a binary image.

 BinaryContourImageFiltertakes a binary image as input, where the pixels in the objects are the pixels with a value equal to ForegroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
li {EdgesAndGradients/BinaryContourImageFilter,Extract the boundaries of connected regions in a binary image} {EdgesAndGradients/BinaryBoundaries,Extract the inner and outer boundaries of blobs in a binary image}


"
%feature("docstring") itk::simple::BinaryContourImageFilter::SetFullyConnected "virtual void itk::BinaryContourImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::BinaryContourImageFilter::GetFullyConnected "virtual const bool& itk::BinaryContourImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::BinaryContourImageFilter::SetBackgroundValue "virtual void itk::BinaryContourImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the background value used to mark the pixels not on the border of the objects.
"

%feature("docstring") itk::simple::BinaryContourImageFilter::GetBackgroundValue "virtual OutputImagePixelType itk::BinaryContourImageFilter::GetBackgroundValue() const

"

%feature("docstring") itk::simple::BinaryContourImageFilter::SetForegroundValue "virtual void itk::BinaryContourImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set/Get the foreground value used to identify the objects in the input and output images.
"

%feature("docstring") itk::simple::BinaryContourImageFilter::GetForegroundValue "virtual InputImagePixelType itk::BinaryContourImageFilter::GetForegroundValue() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryDilateImageFilter.xml
%feature("docstring") itk::simple::BinaryDilateImageFilter "Fast binary dilation.

 BinaryDilateImageFilteris a binary dilation morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a DilateValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. DilateValue defaults to the maximum possible value of the PixelType.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryDilateImageFilter,Dilate a binary image}


"
%feature("docstring") itk::simple::BinaryDilateImageFilter::Execute "Fast binary dilation.
"
%feature("docstring") itk::simple::BinaryDilate "Fast binary dilation.

 BinaryDilateImageFilteris a binary dilation morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a DilateValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. DilateValue defaults to the maximum possible value of the PixelType.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryDilateImageFilter,Dilate a binary image}


"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryErodeImageFilter.xml
%feature("docstring") itk::simple::BinaryErodeImageFilter "Fast binary erosion.

 BinaryErodeImageFilteris a binary erosion morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a ErodeValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. ErodeValue defaults to the maximum possible value of the PixelType. The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryErodeImageFilter,Erode a binary image}


"
%feature("docstring") itk::simple::BinaryErodeImageFilter::Execute "Fast binary erosion.
"
%feature("docstring") itk::simple::BinaryErode "Fast binary erosion.

 BinaryErodeImageFilteris a binary erosion morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a ErodeValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. ErodeValue defaults to the maximum possible value of the PixelType. The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryErodeImageFilter,Erode a binary image}


"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryFillholeImageFilter.xml
%feature("docstring") itk::simple::BinaryFillholeImageFilter "Remove holes not connected to the boundary of the image.

 BinaryFillholeImageFilterfills holes in a binary image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see GrayscaleFillholeImageFilter

"
%feature("docstring") itk::simple::BinaryFillholeImageFilter::Execute "Remove holes not connected to the boundary of the image.
"
%feature("docstring") itk::simple::BinaryFillhole "Remove holes not connected to the boundary of the image.

 BinaryFillholeImageFilterfills holes in a binary image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see GrayscaleFillholeImageFilter

"
%feature("docstring") itk::simple::BinaryFillholeImageFilter::SetFullyConnected "virtual void itk::BinaryFillholeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::BinaryFillholeImageFilter::GetFullyConnected "virtual const bool& itk::BinaryFillholeImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::BinaryFillholeImageFilter::SetForegroundValue "virtual void itk::BinaryFillholeImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
"

%feature("docstring") itk::simple::BinaryFillholeImageFilter::GetForegroundValue "virtual InputImagePixelType itk::BinaryFillholeImageFilter::GetForegroundValue()

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryGrindPeakImageFilter.xml
%feature("docstring") itk::simple::BinaryGrindPeakImageFilter "Remove the objects not connected to the boundary of the image.

 BinaryGrindPeakImageFilterginds peaks in a grayscale image.
Geodesic morphology and the grind peak algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see GrayscaleGrindPeakImageFilter

"
%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::Execute "Remove the objects not connected to the boundary of the image.
"
%feature("docstring") itk::simple::BinaryGrindPeak "Remove the objects not connected to the boundary of the image.

 BinaryGrindPeakImageFilterginds peaks in a grayscale image.
Geodesic morphology and the grind peak algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see GrayscaleGrindPeakImageFilter

"
%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::SetFullyConnected "virtual void itk::BinaryGrindPeakImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::GetFullyConnected "virtual const bool& itk::BinaryGrindPeakImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::SetForegroundValue "virtual void itk::BinaryGrindPeakImageFilter::SetForegroundValue(InputImagePixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
"

%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::GetForegroundValue "virtual InputImagePixelType itk::BinaryGrindPeakImageFilter::GetForegroundValue()

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
"

%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::SetBackgroundValue "virtual void itk::BinaryGrindPeakImageFilter::SetBackgroundValue(InputImagePixelType _arg)

Set the value in eroded part of the image. Defaults to zero
"

%feature("docstring") itk::simple::BinaryGrindPeakImageFilter::GetBackgroundValue "virtual InputImagePixelType itk::BinaryGrindPeakImageFilter::GetBackgroundValue()

Set the value in eroded part of the image. Defaults to zero
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMagnitudeImageFilter.xml
%feature("docstring") itk::simple::BinaryMagnitudeImageFilter "Implements pixel-wise the computation of square root of the sum of squares.

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
"
%feature("docstring") itk::simple::BinaryMagnitudeImageFilter::Execute "Implements pixel-wise the computation of square root of the sum of squares.
"
%feature("docstring") itk::simple::BinaryMagnitude "Implements pixel-wise the computation of square root of the sum of squares.

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
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMinMaxCurvatureFlowImageFilter.xml
%feature("docstring") itk::simple::BinaryMinMaxCurvatureFlowImageFilter "Denoise a binary image using min/max curvature flow.

 BinaryMinMaxCurvatureFlowImageFilterimplements a curvature driven image denosing algorithm. This filter assumes that the image is essentially binary: consisting of two classes. Iso-brightness contours in the input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = min(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ max(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is a user specified value which discriminates between the two pixel classes.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a BinaryMinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see BinaryMinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see MinMaxCurvatureFlowImageFilter

"
%feature("docstring") itk::simple::BinaryMinMaxCurvatureFlowImageFilter::Execute "Denoise a binary image using min/max curvature flow.
"
%feature("docstring") itk::simple::BinaryMinMaxCurvatureFlow "Denoise a binary image using min/max curvature flow.

 BinaryMinMaxCurvatureFlowImageFilterimplements a curvature driven image denosing algorithm. This filter assumes that the image is essentially binary: consisting of two classes. Iso-brightness contours in the input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = min(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ max(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is a user specified value which discriminates between the two pixel classes.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a BinaryMinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see BinaryMinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see MinMaxCurvatureFlowImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMorphologicalClosingImageFilter.xml
%feature("docstring") itk::simple::BinaryMorphologicalClosingImageFilter "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

"
%feature("docstring") itk::simple::BinaryMorphologicalClosingImageFilter::Execute "binary morphological closing of an image.
"
%feature("docstring") itk::simple::BinaryMorphologicalClosing "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

"
%feature("docstring") itk::simple::BinaryMorphologicalClosingImageFilter::SetForegroundValue "virtual void itk::BinaryMorphologicalClosingImageFilter::SetForegroundValue(InputPixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of InputPixelType.
"

%feature("docstring") itk::simple::BinaryMorphologicalClosingImageFilter::GetForegroundValue "virtual InputPixelType itk::BinaryMorphologicalClosingImageFilter::GetForegroundValue() const

Get the value in the image considered as foreground. Defaults to maximum value of InputPixelType.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMorphologicalOpeningImageFilter.xml
%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) structures in the interior or at the boundaries of the image. The morphological opening of an image f is defined as: Opening(f) = Dilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

"
%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter::Execute "binary morphological closing of an image.
"
%feature("docstring") itk::simple::BinaryMorphologicalOpening "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) structures in the interior or at the boundaries of the image. The morphological opening of an image f is defined as: Opening(f) = Dilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

"
%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter::SetBackgroundValue "virtual void itk::BinaryMorphologicalOpeningImageFilter::SetBackgroundValue(PixelType _arg)

Set the value in eroded part of the image. Defaults to zero
"

%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter::GetBackgroundValue "virtual PixelType itk::BinaryMorphologicalOpeningImageFilter::GetBackgroundValue() const

Set the value in eroded part of the image. Defaults to zero
"

%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter::SetForegroundValue "virtual void itk::BinaryMorphologicalOpeningImageFilter::SetForegroundValue(PixelType _arg)

Set the value in the image to consider as foreground. Defaults to maximum value of PixelType.
"

%feature("docstring") itk::simple::BinaryMorphologicalOpeningImageFilter::GetForegroundValue "virtual PixelType itk::BinaryMorphologicalOpeningImageFilter::GetForegroundValue() const

Get the value in the image considered as foreground. Defaults to maximum value of PixelType.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryOpeningByReconstructionImageFilter.xml
%feature("docstring") itk::simple::BinaryOpeningByReconstructionImageFilter "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) objects in the image. It is defined as: Opening(f) = ReconstructionByDilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

"
%feature("docstring") itk::simple::BinaryOpeningByReconstructionImageFilter::Execute "binary morphological closing of an image.
"
%feature("docstring") itk::simple::BinaryOpeningByReconstruction "binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) objects in the image. It is defined as: Opening(f) = ReconstructionByDilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

"
%feature("docstring") itk::simple::BinaryOpeningByReconstructionImageFilter::SetFullyConnected "virtual void itk::BinaryOpeningByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::BinaryOpeningByReconstructionImageFilter::GetFullyConnected "virtual const bool& itk::BinaryOpeningByReconstructionImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryThinningImageFilter.xml
%feature("docstring") itk::simple::BinaryThinningImageFilter "This filter computes one-pixel-wide edges of the input image.

This class is parametrized over the type of the input image and the type of the output image.
The input is assumed to be a binary image. If the foreground pixels of the input image do not have a value of 1, they are rescaled to 1 internally to simplify the computation.
The filter will produce a skeleton of the object. The output background values are 0, and the foreground values are 1.
This filter is a sequential thinning algorithm and known to be computational time dependable on the image size. The algorithm corresponds with the 2D implementation described in:
Rafael C. Gonzales and Richard E. Woods. Digital ImageProcessing. Addison Wesley, 491-494, (1993).
To do: Make this filter ND.
see MorphologyImageFilter

"
%feature("docstring") itk::simple::BinaryThinningImageFilter::Execute "This filter computes one-pixel-wide edges of the input image.
"
%feature("docstring") itk::simple::BinaryThinning "This filter computes one-pixel-wide edges of the input image.

This class is parametrized over the type of the input image and the type of the output image.
The input is assumed to be a binary image. If the foreground pixels of the input image do not have a value of 1, they are rescaled to 1 internally to simplify the computation.
The filter will produce a skeleton of the object. The output background values are 0, and the foreground values are 1.
This filter is a sequential thinning algorithm and known to be computational time dependable on the image size. The algorithm corresponds with the 2D implementation described in:
Rafael C. Gonzales and Richard E. Woods. Digital ImageProcessing. Addison Wesley, 491-494, (1993).
To do: Make this filter ND.
see MorphologyImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryThresholdImageFilter.xml
%feature("docstring") itk::simple::BinaryThresholdImageFilter "Binarize an input image by thresholding.

This filter produces an output image whose pixels are either one of two values ( OutsideValue or InsideValue ), depending on whether the corresponding input image pixels lie between the two thresholds ( LowerThreshold and UpperThreshold ). Values equal to either threshold is considered to be between the thresholds.
More precisely f[ Output(x_i) = begin{cases} InsideValue & text{if f$LowerThreshold leq x_i leq UpperThresholdf$}  OutsideValue & text{otherwise} end{cases} f]  
This filter is templated over the input image type and the output image type.
The filter expect both images to have the same number of dimensions.
The default values for LowerThreshold and UpperThreshold are: LowerThreshold = NumericTraits<TInput>::NonpositiveMin(); UpperThreshold = NumericTraits<TInput>::max(); Therefore, generally only one of these needs to be set, depending on whether the user wants to threshold above or below the desired threshold.

li {ImageProcessing/BinaryThresholdImageFilter,Threshold an image}

"
%feature("docstring") itk::simple::BinaryThresholdImageFilter::Execute "Binarize an input image by thresholding.
"
%feature("docstring") itk::simple::BinaryThreshold "Binarize an input image by thresholding.

This filter produces an output image whose pixels are either one of two values ( OutsideValue or InsideValue ), depending on whether the corresponding input image pixels lie between the two thresholds ( LowerThreshold and UpperThreshold ). Values equal to either threshold is considered to be between the thresholds.
More precisely f[ Output(x_i) = begin{cases} InsideValue & text{if f$LowerThreshold leq x_i leq UpperThresholdf$}  OutsideValue & text{otherwise} end{cases} f]  
This filter is templated over the input image type and the output image type.
The filter expect both images to have the same number of dimensions.
The default values for LowerThreshold and UpperThreshold are: LowerThreshold = NumericTraits<TInput>::NonpositiveMin(); UpperThreshold = NumericTraits<TInput>::max(); Therefore, generally only one of these needs to be set, depending on whether the user wants to threshold above or below the desired threshold.

li {ImageProcessing/BinaryThresholdImageFilter,Threshold an image}

"
%feature("docstring") itk::simple::BinaryThresholdImageFilter::SetLowerThreshold "virtual void itk::BinaryThresholdImageFilter::SetLowerThreshold(const InputPixelType threshold)

"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::GetLowerThreshold "virtual InputPixelType itk::BinaryThresholdImageFilter::GetLowerThreshold() const

"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::SetUpperThreshold "virtual void itk::BinaryThresholdImageFilter::SetUpperThreshold(const InputPixelType threshold)

Set the thresholds. The default lower threshold is NumericTraits<InputPixelType>::NonpositiveMin(). The default upper threshold is NumericTraits<InputPixelType>::max. An execption is thrown if the lower threshold is greater than the upper threshold.
"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::GetUpperThreshold "virtual InputPixelType itk::BinaryThresholdImageFilter::GetUpperThreshold() const

Get the threshold values.
"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::SetInsideValue "virtual void itk::BinaryThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::GetInsideValue "virtual const OutputPixelType& itk::BinaryThresholdImageFilter::GetInsideValue()

Get the inside pixel value.
"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::SetOutsideValue "virtual void itk::BinaryThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
"

%feature("docstring") itk::simple::BinaryThresholdImageFilter::GetOutsideValue "virtual const OutputPixelType& itk::BinaryThresholdImageFilter::GetOutsideValue()

Get the outside pixel value.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BlackTopHatImageFilter.xml
%feature("docstring") itk::simple::BlackTopHatImageFilter "Black top hat extract local minima that are smaller than the structuring element.

Black top hat extract local minima that are smaller than the structuring element. It subtract the background in the input image. The output of the filter transforms the black peaks in white peaks.
Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

"
%feature("docstring") itk::simple::BlackTopHatImageFilter::Execute "Black top hat extract local minima that are smaller than the structuring element.
"
%feature("docstring") itk::simple::BlackTopHat "Black top hat extract local minima that are smaller than the structuring element.

Black top hat extract local minima that are smaller than the structuring element. It subtract the background in the input image. The output of the filter transforms the black peaks in white peaks.
Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

"
%feature("docstring") itk::simple::BlackTopHatImageFilter::SetSafeBorder "virtual void itk::BlackTopHatImageFilter::SetSafeBorder(bool _arg)

A safe border is added to input image to avoid borders effects and remove it once the closing is done
"

%feature("docstring") itk::simple::BlackTopHatImageFilter::GetSafeBorder "virtual const bool& itk::BlackTopHatImageFilter::GetSafeBorder()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ClosingByReconstructionImageFilter.xml
%feature("docstring") itk::simple::ClosingByReconstructionImageFilter "Closing by reconstruction of an image.

This filter is similar to the morphological closing, but contrary to the mophological closing, the closing by reconstruction preserves the shape of the components. The closing by reconstruction of an image f is defined as:
ClosingByReconstruction(f) = ErosionByReconstruction(f, Dilation(f)).
Closing by reconstruction not only preserves structures preserved by the dilation, but also levels raises the contrast of the darkest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Closing by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see GrayscaleMorphologicalClosingImageFilter

"
%feature("docstring") itk::simple::ClosingByReconstructionImageFilter::Execute "Closing by reconstruction of an image.
"
%feature("docstring") itk::simple::ClosingByReconstruction "Closing by reconstruction of an image.

This filter is similar to the morphological closing, but contrary to the mophological closing, the closing by reconstruction preserves the shape of the components. The closing by reconstruction of an image f is defined as:
ClosingByReconstruction(f) = ErosionByReconstruction(f, Dilation(f)).
Closing by reconstruction not only preserves structures preserved by the dilation, but also levels raises the contrast of the darkest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Closing by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see GrayscaleMorphologicalClosingImageFilter

"
%feature("docstring") itk::simple::ClosingByReconstructionImageFilter::SetFullyConnected "virtual void itk::ClosingByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::ClosingByReconstructionImageFilter::GetFullyConnected "virtual const bool& itk::ClosingByReconstructionImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::ClosingByReconstructionImageFilter::SetPreserveIntensities "virtual void itk::ClosingByReconstructionImageFilter::SetPreserveIntensities(bool _arg)

Set/Get whether the original intensities of the image retained for those pixels unaffected by the opening by reconstrcution. If Off, the output pixel contrast will be reduced.
"

%feature("docstring") itk::simple::ClosingByReconstructionImageFilter::GetPreserveIntensities "virtual const bool& itk::ClosingByReconstructionImageFilter::GetPreserveIntensities()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ConnectedThresholdImageFilter.xml
%feature("docstring") itk::simple::ConnectedThresholdImageFilter "Label pixels that are connected to a seed and lie within a range of values.

 ConnectedThresholdImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND lie within a Lower and Upper threshold range.
"
%feature("docstring") itk::simple::ConnectedThresholdImageFilter::Execute "Label pixels that are connected to a seed and lie within a range of values.
"
%feature("docstring") itk::simple::ConnectedThreshold "Label pixels that are connected to a seed and lie within a range of values.

 ConnectedThresholdImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND lie within a Lower and Upper threshold range.
"
%feature("docstring") itk::simple::ConnectedThresholdImageFilter::SetUpper "virtual void itk::ConnectedThresholdImageFilter::SetUpper(InputImagePixelType)

Set Upper and Lower Threshold inputs as values
"

%feature("docstring") itk::simple::ConnectedThresholdImageFilter::GetUpper "virtual InputImagePixelType itk::ConnectedThresholdImageFilter::GetUpper() const

Get Upper and Lower Threshold inputs as values
"

%feature("docstring") itk::simple::ConnectedThresholdImageFilter::SetLower "virtual void itk::ConnectedThresholdImageFilter::SetLower(InputImagePixelType)

"

%feature("docstring") itk::simple::ConnectedThresholdImageFilter::GetLower "virtual InputImagePixelType itk::ConnectedThresholdImageFilter::GetLower() const

"

%feature("docstring") itk::simple::ConnectedThresholdImageFilter::SetReplaceValue "virtual void itk::ConnectedThresholdImageFilter::SetReplaceValue(OutputImagePixelType _arg)

Set/Get value to replace thresholded pixels. Pixels that lie * within Lower and Upper (inclusive) will be replaced with this value. The default is 1.
"

%feature("docstring") itk::simple::ConnectedThresholdImageFilter::GetReplaceValue "virtual OutputImagePixelType itk::ConnectedThresholdImageFilter::GetReplaceValue() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ConstantPadImageFilter.xml
%feature("docstring") itk::simple::ConstantPadImageFilter "Increase the image size by padding with a constant value.

 ConstantPadImageFilterchanges the output image region. If the output image region is larger than the input image region, the extra pixels are filled in by a constant value. The output image region must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, MirrorPadImageFilter
li {Images/ConstantPadImageFilter,Pad an image with a constant value}


"
%feature("docstring") itk::simple::ConstantPadImageFilter::Execute "Increase the image size by padding with a constant value.
"
%feature("docstring") itk::simple::ConstantPad "Increase the image size by padding with a constant value.

 ConstantPadImageFilterchanges the output image region. If the output image region is larger than the input image region, the extra pixels are filled in by a constant value. The output image region must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, MirrorPadImageFilter
li {Images/ConstantPadImageFilter,Pad an image with a constant value}


"
%feature("docstring") itk::simple::ConstantPadImageFilter::SetConstant "virtual void itk::ConstantPadImageFilter::SetConstant(OutputImagePixelType _arg)

Set/Get the pad value. Default is Zero.
"

%feature("docstring") itk::simple::ConstantPadImageFilter::GetConstant "virtual OutputImagePixelType itk::ConstantPadImageFilter::GetConstant() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CosImageFilter.xml
%feature("docstring") itk::simple::CosImageFilter "Computes the vcl_cos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_cos() function to the double value
li cast the double value resulting from vcl_cos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
%feature("docstring") itk::simple::CosImageFilter::Execute "Computes the vcl_cos(x) pixel-wise.
"
%feature("docstring") itk::simple::Cos "Computes the vcl_cos(x) pixel-wise.

This filter is templated over the pixel type of the input image and the pixel type of the output image.
The filter will walk over all the pixels in the input image, and for each one of them it will do the following:

li cast the pixel value to double ,
li apply the vcl_cos() function to the double value
li cast the double value resulting from vcl_cos() to the pixel type of the output image
li store the casted value into the output image.

The filter expect both images to have the same dimension (e.g. both 2D, or both 3D, or both ND)
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CropImageFilter.xml
%feature("docstring") itk::simple::CropImageFilter "Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.

 CropImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region is not specified in advance, but calculated in BeforeThreadedGenerateData().
This filter uses ExtractImageFilterto perform the cropping.

li {ImageProcessing/CropImageFilter,Crop an image}

"
%feature("docstring") itk::simple::CropImageFilter::Execute "Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.
"
%feature("docstring") itk::simple::Crop "Decrease the image size by cropping the image by an itk::Sizeat both the upper and lower bounds of the largest possible region.

 CropImageFilterchanges the image boundary of an image by removing pixels outside the target region. The target region is not specified in advance, but calculated in BeforeThreadedGenerateData().
This filter uses ExtractImageFilterto perform the cropping.

li {ImageProcessing/CropImageFilter,Crop an image}

"
%feature("docstring") itk::simple::CropImageFilter::SetLowerBoundaryCropSize "virtual void itk::CropImageFilter::SetLowerBoundaryCropSize(SizeType _arg)

"

%feature("docstring") itk::simple::CropImageFilter::GetLowerBoundaryCropSize "virtual SizeType itk::CropImageFilter::GetLowerBoundaryCropSize() const

"

%feature("docstring") itk::simple::CropImageFilter::SetUpperBoundaryCropSize "virtual void itk::CropImageFilter::SetUpperBoundaryCropSize(SizeType _arg)

Set/Get the cropping sizes for the upper and lower boundaries.
"

%feature("docstring") itk::simple::CropImageFilter::GetUpperBoundaryCropSize "virtual SizeType itk::CropImageFilter::GetUpperBoundaryCropSize() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CurvatureAnisotropicDiffusionImageFilter.xml
%feature("docstring") itk::simple::CurvatureAnisotropicDiffusionImageFilter "
This filter performs anisotropic diffusion on a scalar itk::Imageusing the modified curvature diffusion equation (MCDE) implemented in itkCurvatureNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion and the MCDE see itkAnisotropicDiffusionFunction and itkCurvatureNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input and output to this filter must be a scalar itk::Imagewith numerical pixel types (float or double). A user defined type which correctly defines arithmetic operations with floating point accuracy should also give correct results.
par Parameters
Please first read all the documentation found in AnisotropicDiffusionImageFilterand AnisotropicDiffusionFunction. Also see CurvatureNDAnisotropicDiffusionFunction.
The default time step for this filter is set to the maximum theoretically stable value: 0.5 / 2^N, where N is the dimensionality of the image. For a 2D image, this means valid time steps are below 0.1250. For a 3D image, valid time steps are below 0.0625.
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
see CurvatureNDAnisotropicDiffusionFunction

"
%feature("docstring") itk::simple::CurvatureAnisotropicDiffusionImageFilter::Execute ""
%feature("docstring") itk::simple::CurvatureAnisotropicDiffusion "
This filter performs anisotropic diffusion on a scalar itk::Imageusing the modified curvature diffusion equation (MCDE) implemented in itkCurvatureNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion and the MCDE see itkAnisotropicDiffusionFunction and itkCurvatureNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input and output to this filter must be a scalar itk::Imagewith numerical pixel types (float or double). A user defined type which correctly defines arithmetic operations with floating point accuracy should also give correct results.
par Parameters
Please first read all the documentation found in AnisotropicDiffusionImageFilterand AnisotropicDiffusionFunction. Also see CurvatureNDAnisotropicDiffusionFunction.
The default time step for this filter is set to the maximum theoretically stable value: 0.5 / 2^N, where N is the dimensionality of the image. For a 2D image, this means valid time steps are below 0.1250. For a 3D image, valid time steps are below 0.0625.
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
see CurvatureNDAnisotropicDiffusionFunction

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1CurvatureFlowImageFilter.xml
%feature("docstring") itk::simple::CurvatureFlowImageFilter "Denoise an image using curvature driven flow.

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
see DenseFiniteDifferenceImageFilter
see CurvatureFlowFunction
see MinMaxCurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter
Input/Output Restrictions: TInputImage and TOutputImage must have the same dimension. TOutputImage's pixel type must be a real number type.
"
%feature("docstring") itk::simple::CurvatureFlowImageFilter::Execute "Denoise an image using curvature driven flow.
"
%feature("docstring") itk::simple::CurvatureFlow "Denoise an image using curvature driven flow.

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
see DenseFiniteDifferenceImageFilter
see CurvatureFlowFunction
see MinMaxCurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter
Input/Output Restrictions: TInputImage and TOutputImage must have the same dimension. TOutputImage's pixel type must be a real number type.
"
%feature("docstring") itk::simple::CurvatureFlowImageFilter::SetTimeStep "virtual void itk::CurvatureFlowImageFilter::SetTimeStep(TimeStepType _arg)

Set the timestep parameter.
"

%feature("docstring") itk::simple::CurvatureFlowImageFilter::GetTimeStep "virtual TimeStepType itk::CurvatureFlowImageFilter::GetTimeStep() const

Get the timestep parameter.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DilateObjectMorphologyImageFilter.xml
%feature("docstring") itk::simple::DilateObjectMorphologyImageFilter "dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see BinaryDilateImageFilter

"
%feature("docstring") itk::simple::DilateObjectMorphologyImageFilter::Execute "dilation of an object in an image
"
%feature("docstring") itk::simple::DilateObjectMorphology "dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see BinaryDilateImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DivideByConstantImageFilter.xml
%feature("docstring") itk::simple::DivideByConstantImageFilter "Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

"
%feature("docstring") itk::simple::DivideByConstantImageFilter::Execute "Divide input pixels by a constant.
"
%feature("docstring") itk::simple::DivideByConstant "Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

"
%feature("docstring") itk::simple::DivideByConstantImageFilter::SetConstant "void itk::DivideByConstantImageFilter::SetConstant(TConstant ct)

Set the constant value that will be used for dividing all the image pixels
"

%feature("docstring") itk::simple::DivideByConstantImageFilter::GetConstant "const TConstant& itk::DivideByConstantImageFilter::GetConstant() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DivideImageFilter.xml
%feature("docstring") itk::simple::DivideImageFilter "Implements an operator for pixel-wise division of two images.

This class is parametrized over the types of the two input images and the type of the output image. When the divisor is zero, the division result is set to the maximum number that can be represneted by default to avoid exception. Numeric conversions (castings) are done by the C++ defaults.
"
%feature("docstring") itk::simple::DivideImageFilter::Execute "Implements an operator for pixel-wise division of two images.
"
%feature("docstring") itk::simple::Divide "Implements an operator for pixel-wise division of two images.

This class is parametrized over the types of the two input images and the type of the output image. When the divisor is zero, the division result is set to the maximum number that can be represneted by default to avoid exception. Numeric conversions (castings) are done by the C++ defaults.
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DoubleThresholdImageFilter.xml
%feature("docstring") itk::simple::DoubleThresholdImageFilter "Binarize an input image using double thresholding.

Double threshold addresses the difficulty in selecting a threshold that will select the objects of interest without selecting extraneous objects. Double threshold considers two threshold ranges: a narrow range and a wide range (where the wide range encompasses the narrow range). If the wide range was used for a traditional threshold (where values inside the range map to the foreground and values outside the range map to the background), many extraneous pixels may survive the threshold operation. If the narrow range was used for a traditional threshold, then too few pixels may survive the threshold.
Double threshold uses the narrow threshold image as a marker image and the wide threshold image as a mask image in the geodesic dilation. Essentially, the marker image (narrow threshold) is dilated but constrained to lie within the mask image (wide threshold). Thus, only the objects of interest (those pixels that survived the narrow threshold) are extracted but the those objects appear in the final image as they would have if the wide threshold was used.
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::DoubleThresholdImageFilter::Execute "Binarize an input image using double thresholding.
"
%feature("docstring") itk::simple::DoubleThreshold "Binarize an input image using double thresholding.

Double threshold addresses the difficulty in selecting a threshold that will select the objects of interest without selecting extraneous objects. Double threshold considers two threshold ranges: a narrow range and a wide range (where the wide range encompasses the narrow range). If the wide range was used for a traditional threshold (where values inside the range map to the foreground and values outside the range map to the background), many extraneous pixels may survive the threshold operation. If the narrow range was used for a traditional threshold, then too few pixels may survive the threshold.
Double threshold uses the narrow threshold image as a marker image and the wide threshold image as a mask image in the geodesic dilation. Essentially, the marker image (narrow threshold) is dilated but constrained to lie within the mask image (wide threshold). Thus, only the objects of interest (those pixels that survived the narrow threshold) are extracted but the those objects appear in the final image as they would have if the wide threshold was used.
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetThreshold1 "virtual void itk::DoubleThresholdImageFilter::SetThreshold1(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetThreshold1 "virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold1() const

Get the threshold values.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetThreshold2 "virtual void itk::DoubleThresholdImageFilter::SetThreshold2(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetThreshold2 "virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold2() const

Get the threshold values.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetThreshold3 "virtual void itk::DoubleThresholdImageFilter::SetThreshold3(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetThreshold3 "virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold3() const

Get the threshold values.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetThreshold4 "virtual void itk::DoubleThresholdImageFilter::SetThreshold4(InputPixelType _arg)

Set the thresholds. Four thresholds should be specified. The two lower thresholds default to NumericTraits<InputPixelType>::NonpositiveMin(). The two upper thresholds default NumericTraits<InputPixelType>::max. Threshold1 <= Threshold2 <= Threshold3 <= Threshold4.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetThreshold4 "virtual InputPixelType itk::DoubleThresholdImageFilter::GetThreshold4() const

Get the threshold values.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetInsideValue "virtual void itk::DoubleThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetInsideValue "virtual OutputPixelType itk::DoubleThresholdImageFilter::GetInsideValue() const

Get the inside pixel value.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetOutsideValue "virtual void itk::DoubleThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetOutsideValue "virtual OutputPixelType itk::DoubleThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::SetFullyConnected "virtual void itk::DoubleThresholdImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::DoubleThresholdImageFilter::GetFullyConnected "virtual const bool& itk::DoubleThresholdImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ErodeObjectMorphologyImageFilter.xml
%feature("docstring") itk::simple::ErodeObjectMorphologyImageFilter "Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see BinaryErodeImageFilter

"
%feature("docstring") itk::simple::ErodeObjectMorphologyImageFilter::Execute "Erosion of an object in an image.
"
%feature("docstring") itk::simple::ErodeObjectMorphology "Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see BinaryErodeImageFilter

"
%feature("docstring") itk::simple::ErodeObjectMorphologyImageFilter::SetBackgroundValue "virtual void itk::ErodeObjectMorphologyImageFilter::SetBackgroundValue(PixelType _arg)

Set the value to be assigned to eroded pixels
"

%feature("docstring") itk::simple::ErodeObjectMorphologyImageFilter::GetBackgroundValue "virtual PixelType itk::ErodeObjectMorphologyImageFilter::GetBackgroundValue() const

Get the value to be assigned to eroded pixels
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ExpImageFilter.xml
%feature("docstring") itk::simple::ExpImageFilter "Computes the vcl_exp(x) pixel-wise.

"
%feature("docstring") itk::simple::ExpImageFilter::Execute "Computes the vcl_exp(x) pixel-wise.
"
%feature("docstring") itk::simple::Exp "Computes the vcl_exp(x) pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ExpNegativeImageFilter.xml
%feature("docstring") itk::simple::ExpNegativeImageFilter "Computes the function vcl_exp(-K.x) pixel-wise.

Every output pixel is equal to vcl_exp(-K.x ). where x is the intensity of the homologous input pixel, and K is a user-provided constant.
"
%feature("docstring") itk::simple::ExpNegativeImageFilter::Execute "Computes the function vcl_exp(-K.x) pixel-wise.
"
%feature("docstring") itk::simple::ExpNegative "Computes the function vcl_exp(-K.x) pixel-wise.

Every output pixel is equal to vcl_exp(-K.x ). where x is the intensity of the homologous input pixel, and K is a user-provided constant.
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1FlipImageFilter.xml
%feature("docstring") itk::simple::FlipImageFilter "Flips an image across user specified axes.

 FlipImageFilterflips an image across user specified axes. The flip axes are set via method SetFlipAxes( array ) where the input is a FixedArray<bool,ImageDimension>. The image is flipped across axes for which array[i] is true.
In terms of grid coordinates the image is flipped within the LargestPossibleRegion of the input image. As such, the LargestPossibleRegion of the ouput image is the same as the input.
In terms of geometric coordinates, the output origin is such that the image is flipped with respect to the coordinate axes.

li {Images/FlipImageFilter,Flip an image over specified axes}

"
%feature("docstring") itk::simple::FlipImageFilter::Execute "Flips an image across user specified axes.
"
%feature("docstring") itk::simple::Flip "Flips an image across user specified axes.

 FlipImageFilterflips an image across user specified axes. The flip axes are set via method SetFlipAxes( array ) where the input is a FixedArray<bool,ImageDimension>. The image is flipped across axes for which array[i] is true.
In terms of grid coordinates the image is flipped within the LargestPossibleRegion of the input image. As such, the LargestPossibleRegion of the ouput image is the same as the input.
In terms of geometric coordinates, the output origin is such that the image is flipped with respect to the coordinate axes.

li {Images/FlipImageFilter,Flip an image over specified axes}

"
%feature("docstring") itk::simple::FlipImageFilter::SetFlipAxes "virtual void itk::FlipImageFilter::SetFlipAxes(FlipAxesArrayType _arg)

Set/Get the axis to be flipped. The image is flipped along axes for which array[i] is true.
"

%feature("docstring") itk::simple::FlipImageFilter::GetFlipAxes "virtual FlipAxesArrayType itk::FlipImageFilter::GetFlipAxes() const

"

%feature("docstring") itk::simple::FlipImageFilter::SetFlipAboutOrigin "virtual void itk::FlipImageFilter::SetFlipAboutOrigin(bool _arg)

"

%feature("docstring") itk::simple::FlipImageFilter::GetFlipAboutOrigin "virtual bool itk::FlipImageFilter::GetFlipAboutOrigin() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GeodesicActiveContourLevelSetImageFilter.xml
%feature("docstring") itk::simple::GeodesicActiveContourLevelSetImageFilter "Segments structures in images based on a user supplied edge potential map.

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
see SegmentationLevelSetImageFilter
see GeodesicActiveContourLevelSetFunction
see SparseFieldLevelSetImageFilter

"
%feature("docstring") itk::simple::GeodesicActiveContourLevelSetImageFilter::Execute "Segments structures in images based on a user supplied edge potential map.
"
%feature("docstring") itk::simple::GeodesicActiveContourLevelSet "Segments structures in images based on a user supplied edge potential map.

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
see SegmentationLevelSetImageFilter
see GeodesicActiveContourLevelSetFunction
see SparseFieldLevelSetImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GradientAnisotropicDiffusionImageFilter.xml
%feature("docstring") itk::simple::GradientAnisotropicDiffusionImageFilter "
This filter performs anisotropic diffusion on a scalar itk::Imageusing the classic Perona-Malik, gradient magnitude based equation implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion, see itkAnisotropicDiffusionFunction and itkGradientNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any dimensionality. The output image will be a diffused copy of the input.
par Parameters
Please see the description of parameters given in itkAnisotropicDiffusionImageFilter.
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
seeGradientAnisotropicDiffusionFunction

"
%feature("docstring") itk::simple::GradientAnisotropicDiffusionImageFilter::Execute ""
%feature("docstring") itk::simple::GradientAnisotropicDiffusion "
This filter performs anisotropic diffusion on a scalar itk::Imageusing the classic Perona-Malik, gradient magnitude based equation implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion, see itkAnisotropicDiffusionFunction and itkGradientNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any dimensionality. The output image will be a diffused copy of the input.
par Parameters
Please see the description of parameters given in itkAnisotropicDiffusionImageFilter.
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
seeGradientAnisotropicDiffusionFunction

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GradientMagnitudeRecursiveGaussianImageFilter.xml
%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter "Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/GradientMagnitudeRecursiveGaussianImageFilter,Find the gradient magnitude of the image first smoothed with a Gaussian kernel}

"
%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::Execute "Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.
"
%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussian "Computes the Magnitude of the Gradient of an image by convolution with the first derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/GradientMagnitudeRecursiveGaussianImageFilter,Find the gradient magnitude of the image first smoothed with a Gaussian kernel}

"
%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::SetSigma "void itk::GradientMagnitudeRecursiveGaussianImageFilter::SetSigma(RealType sigma)

Set Sigma value. Sigma is measured in the units of image spacing.
"

%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GetSigma "RealType itk::GradientMagnitudeRecursiveGaussianImageFilter::GetSigma()

"

%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::SetNormalizeAcrossScale "void itk::GradientMagnitudeRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

Define which normalization factor will be used for the Gaussiansee RecursiveGaussianImageFilter::SetNormalizeAcrossScale

"

%feature("docstring") itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::GetNormalizeAcrossScale "virtual bool itk::GradientMagnitudeRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleDilateImageFilter.xml
%feature("docstring") itk::simple::GrayscaleDilateImageFilter "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

"
%feature("docstring") itk::simple::GrayscaleDilateImageFilter::Execute "gray scale dilation of an image
"
%feature("docstring") itk::simple::GrayscaleDilate "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleErodeImageFilter.xml
%feature("docstring") itk::simple::GrayscaleErodeImageFilter "gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

"
%feature("docstring") itk::simple::GrayscaleErodeImageFilter::Execute "gray scale dilation of an image
"
%feature("docstring") itk::simple::GrayscaleErode "gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleFillholeImageFilter.xml
%feature("docstring") itk::simple::GrayscaleFillholeImageFilter "Remove local minima not connected to the boundary of the image.

 GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes are local minima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a hole are extrapolated across the hole.
This filter is used to smooth over local minima without affecting the values of local maxima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local minima.
This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the maximum pixel value in the input image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see ReconstructionByErosionImageFilter
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

"
%feature("docstring") itk::simple::GrayscaleFillholeImageFilter::Execute "Remove local minima not connected to the boundary of the image.
"
%feature("docstring") itk::simple::GrayscaleFillhole "Remove local minima not connected to the boundary of the image.

 GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes are local minima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a hole are extrapolated across the hole.
This filter is used to smooth over local minima without affecting the values of local maxima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local minima.
This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the maximum pixel value in the input image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see ReconstructionByErosionImageFilter
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

"
%feature("docstring") itk::simple::GrayscaleFillholeImageFilter::SetFullyConnected "virtual void itk::GrayscaleFillholeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::GrayscaleFillholeImageFilter::GetFullyConnected "virtual const bool& itk::GrayscaleFillholeImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGeodesicDilateImageFilter.xml
%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter "geodesic gray scale dilation of an image

Geodesic dilation operates on a marker image and a mask image. The marker image is dilated using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise minimum of the dilated marker image and the mask image.
Geodesic dilation is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by dilation. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be less than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByDilationImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicDiliateImageFilter as part of their implementation have been converted to use the ReconstructionByDilationImageFilter. The GrayscaleGeodesicDilateImageFilteris maintained for backward compatibility.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

"
%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter::Execute "geodesic gray scale dilation of an image
"
%feature("docstring") itk::simple::GrayscaleGeodesicDilate "geodesic gray scale dilation of an image

Geodesic dilation operates on a marker image and a mask image. The marker image is dilated using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise minimum of the dilated marker image and the mask image.
Geodesic dilation is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by dilation. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be less than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByDilationImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicDiliateImageFilter as part of their implementation have been converted to use the ReconstructionByDilationImageFilter. The GrayscaleGeodesicDilateImageFilteris maintained for backward compatibility.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

"
%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter::SetRunOneIteration "virtual void itk::GrayscaleGeodesicDilateImageFilter::SetRunOneIteration(bool _arg)

Set/Get whether the filter should run one iteration or until convergence. When run to convergence, this filter is equivalent to reconstruction by dilation. Default is off.
"

%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter::GetRunOneIteration "virtual bool itk::GrayscaleGeodesicDilateImageFilter::GetRunOneIteration() const

"

%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter::SetFullyConnected "virtual void itk::GrayscaleGeodesicDilateImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::GrayscaleGeodesicDilateImageFilter::GetFullyConnected "virtual const bool& itk::GrayscaleGeodesicDilateImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGeodesicErodeImageFilter.xml
%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter "geodesic gray scale erosion of an image

Geodesic erosion operates on a marker image and a mask image. The marker image is eroded using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise maximum of the eroded marker image and the mask image.
Geodesic erosion is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by erosion. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be greater than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByErosionImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicErodeImageFilteras part of their implementation have been converted to use the ReconstructionByErosionImageFilter. The GrayscaleGeodesicErodeImageFilteris maintained for backward compatibility.
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

"
%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter::Execute "geodesic gray scale erosion of an image
"
%feature("docstring") itk::simple::GrayscaleGeodesicErode "geodesic gray scale erosion of an image

Geodesic erosion operates on a marker image and a mask image. The marker image is eroded using an elementary structuring element (neighborhood of radius one using only the face connected neighbors). The resulting image is then compared with the mask image. The output image is the pixelwise maximum of the eroded marker image and the mask image.
Geodesic erosion is run either one iteration or until convergence. In the convergence case, the filter is equivalent to reconstruction by erosion. This filter is implemented to handle both scenarios. The one iteration case is multi-threaded. The convergence case is delegated to another instance of the same filter (but configured to run a single iteration).
The marker image must be greater than or equal to the mask image (on a pixel by pixel basis).
Geodesic morphology is described in Chapter 6 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
A noniterative version of this algorithm can be found in the ReconstructionByErosionImageFilter. This noniterative solution is much faster than the implementation provided here. All ITK filters that previously used GrayscaleGeodesicErodeImageFilteras part of their implementation have been converted to use the ReconstructionByErosionImageFilter. The GrayscaleGeodesicErodeImageFilteris maintained for backward compatibility.
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

"
%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter::SetRunOneIteration "virtual void itk::GrayscaleGeodesicErodeImageFilter::SetRunOneIteration(bool _arg)

Set/Get whether the filter should run one iteration or until convergence. When run to convergence, this filter is equivalent to reconstruction by erosion. Default is off.
"

%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter::GetRunOneIteration "virtual bool itk::GrayscaleGeodesicErodeImageFilter::GetRunOneIteration() const

"

%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter::SetFullyConnected "virtual void itk::GrayscaleGeodesicErodeImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::GrayscaleGeodesicErodeImageFilter::GetFullyConnected "virtual const bool& itk::GrayscaleGeodesicErodeImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleGrindPeakImageFilter.xml
%feature("docstring") itk::simple::GrayscaleGrindPeakImageFilter "Remove local maxima not connected to the boundary of the image.

 GrayscaleGrindPeakImageFilterremoves peaks in a grayscale image. Peaks are local maxima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a peak are extrapolated through the peak.
This filter is used to smooth over local maxima without affecting the values of local minima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local maxima.
This filter uses the GrayscaleGeodesicDilateImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the minimum pixel value in the input image.
This filter is the dual to the GrayscaleFillholeImageFilterwhich implements the Fillhole algorithm. Since it is a dual, it is somewhat superfluous but is provided as a convenience.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::GrayscaleGrindPeakImageFilter::Execute "Remove local maxima not connected to the boundary of the image.
"
%feature("docstring") itk::simple::GrayscaleGrindPeak "Remove local maxima not connected to the boundary of the image.

 GrayscaleGrindPeakImageFilterremoves peaks in a grayscale image. Peaks are local maxima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a peak are extrapolated through the peak.
This filter is used to smooth over local maxima without affecting the values of local minima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local maxima.
This filter uses the GrayscaleGeodesicDilateImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the minimum pixel value in the input image.
This filter is the dual to the GrayscaleFillholeImageFilterwhich implements the Fillhole algorithm. Since it is a dual, it is somewhat superfluous but is provided as a convenience.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::GrayscaleGrindPeakImageFilter::SetFullyConnected "virtual void itk::GrayscaleGrindPeakImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::GrayscaleGrindPeakImageFilter::GetFullyConnected "virtual const bool& itk::GrayscaleGrindPeakImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleMorphologicalClosingImageFilter.xml
%feature("docstring") itk::simple::GrayscaleMorphologicalClosingImageFilter "gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

"
%feature("docstring") itk::simple::GrayscaleMorphologicalClosingImageFilter::Execute "gray scale dilation of an image
"
%feature("docstring") itk::simple::GrayscaleMorphologicalClosing "gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleMorphologicalOpeningImageFilter.xml
%feature("docstring") itk::simple::GrayscaleMorphologicalOpeningImageFilter "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::GrayscaleMorphologicalOpeningImageFilter::Execute "gray scale dilation of an image
"
%feature("docstring") itk::simple::GrayscaleMorphologicalOpening "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HConcaveImageFilter.xml
%feature("docstring") itk::simple::HConcaveImageFilter "Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HConcaveImageFilter::Execute "Identify local minima whose depth below the baseline is greater than h.
"
%feature("docstring") itk::simple::HConcave "Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HConcaveImageFilter::SetHeight "virtual void itk::HConcaveImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
"

%feature("docstring") itk::simple::HConcaveImageFilter::GetHeight "virtual InputImagePixelType itk::HConcaveImageFilter::GetHeight() const

"

%feature("docstring") itk::simple::HConcaveImageFilter::SetFullyConnected "virtual void itk::HConcaveImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::HConcaveImageFilter::GetFullyConnected "virtual const bool& itk::HConcaveImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HConvexImageFilter.xml
%feature("docstring") itk::simple::HConvexImageFilter "Identify local maxima whose height above the baseline is greater than h.

 HConvexImageFilterextract local maxima that are more than h intensity units above the (local) background. This has the effect of extracting objects that are brighter than background by at least h intensity units.
This filter uses the HMaximaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HConvexImageFilter::Execute "Identify local maxima whose height above the baseline is greater than h.
"
%feature("docstring") itk::simple::HConvex "Identify local maxima whose height above the baseline is greater than h.

 HConvexImageFilterextract local maxima that are more than h intensity units above the (local) background. This has the effect of extracting objects that are brighter than background by at least h intensity units.
This filter uses the HMaximaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HConvexImageFilter::SetHeight "virtual void itk::HConvexImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
"

%feature("docstring") itk::simple::HConvexImageFilter::GetHeight "virtual InputImagePixelType itk::HConvexImageFilter::GetHeight() const

"

%feature("docstring") itk::simple::HConvexImageFilter::SetFullyConnected "virtual void itk::HConvexImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::HConvexImageFilter::GetFullyConnected "virtual const bool& itk::HConvexImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HMaximaImageFilter.xml
%feature("docstring") itk::simple::HMaximaImageFilter "Suppress local maxima whose height above the baseline is less than h.

 HMaximaImageFiltersuppresses local maxima that are less than h intensity units above the (local) background. This has the effect of smoothing over the high parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMinimaImageFilterto suppress the local minima whose depth is less than h intensity units below the (local) background.
If the output of HMaximaImageFilteris subtracted from the original image, the signicant peaks in the image can be identified. This is what the HConvexImageFilterprovides.
This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image minus the height parameter h.
Geodesic morphology and the H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
The height parameter is set using SetHeight.
see ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HMaximaImageFilter::Execute "Suppress local maxima whose height above the baseline is less than h.
"
%feature("docstring") itk::simple::HMaxima "Suppress local maxima whose height above the baseline is less than h.

 HMaximaImageFiltersuppresses local maxima that are less than h intensity units above the (local) background. This has the effect of smoothing over the high parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMinimaImageFilterto suppress the local minima whose depth is less than h intensity units below the (local) background.
If the output of HMaximaImageFilteris subtracted from the original image, the signicant peaks in the image can be identified. This is what the HConvexImageFilterprovides.
This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image minus the height parameter h.
Geodesic morphology and the H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
The height parameter is set using SetHeight.
see ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HMaximaImageFilter::SetHeight "virtual void itk::HMaximaImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
"

%feature("docstring") itk::simple::HMaximaImageFilter::GetHeight "virtual InputImagePixelType itk::HMaximaImageFilter::GetHeight() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HMinimaImageFilter.xml
%feature("docstring") itk::simple::HMinimaImageFilter "Suppress local minima whose depth below the baseline is less than h.

 HMinimaImageFiltersuppresses local minima that are less than h intensity units below the (local) background. This has the effect of smoothing over the low parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMaximaImageFilterto suppress the local maxima whose height is less than h intensity units above the (local) background.
If original image is subtracted from the output of HMinimaImageFilter, the signicant valleys in the image can be identified. This is what the HConcaveImageFilterprovides.
This filter uses the GrayscaleGeodesicErodeImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image plus the height parameter h.
Geodesic morphology and the H-Minima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HMinimaImageFilter::Execute "Suppress local minima whose depth below the baseline is less than h.
"
%feature("docstring") itk::simple::HMinima "Suppress local minima whose depth below the baseline is less than h.

 HMinimaImageFiltersuppresses local minima that are less than h intensity units below the (local) background. This has the effect of smoothing over the low parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMaximaImageFilterto suppress the local maxima whose height is less than h intensity units above the (local) background.
If original image is subtracted from the output of HMinimaImageFilter, the signicant valleys in the image can be identified. This is what the HConcaveImageFilterprovides.
This filter uses the GrayscaleGeodesicErodeImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image plus the height parameter h.
Geodesic morphology and the H-Minima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::HMinimaImageFilter::SetHeight "virtual void itk::HMinimaImageFilter::SetHeight(InputImagePixelType _arg)

Set/Get the height that a local maximum must be above the local background (local contrast) in order to survive the processing. Local maxima below this value are replaced with an estimate of the local background.
"

%feature("docstring") itk::simple::HMinimaImageFilter::GetHeight "virtual InputImagePixelType itk::HMinimaImageFilter::GetHeight() const

"

%feature("docstring") itk::simple::HMinimaImageFilter::SetFullyConnected "virtual void itk::HMinimaImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::HMinimaImageFilter::GetFullyConnected "virtual const bool& itk::HMinimaImageFilter::GetFullyConnected()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1IntensityWindowingImageFilter.xml
%feature("docstring") itk::simple::IntensityWindowingImageFilter "Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.

 IntensityWindowingImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have and the lower and upper limits of the intensity window of the input image. This operation is very common in visualization, and can also be applied as a convenient preprocessing operation for image segmentation.
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.

li {ImageProcessing/IntensityWindowingImageFilter, IntensityWindowingImageFilter}

"
%feature("docstring") itk::simple::IntensityWindowingImageFilter::Execute "Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.
"
%feature("docstring") itk::simple::IntensityWindowing "Applies a linear transformation to the intensity levels of the input Imagethat are inside a user-defined interval. Values below this interval are mapped to a constant. Values over the interval are mapped to another constant.

 IntensityWindowingImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have and the lower and upper limits of the intensity window of the input image. This operation is very common in visualization, and can also be applied as a convenient preprocessing operation for image segmentation.
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.

li {ImageProcessing/IntensityWindowingImageFilter, IntensityWindowingImageFilter}

"
%feature("docstring") itk::simple::IntensityWindowingImageFilter::SetWindowMinimum "virtual void itk::IntensityWindowingImageFilter::SetWindowMinimum(InputPixelType _arg)

Set/Get the values of the maximum and minimum intensities of the input intensity window
"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::GetWindowMinimum "virtual const InputPixelType& itk::IntensityWindowingImageFilter::GetWindowMinimum()

"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::SetWindowMaximum "virtual void itk::IntensityWindowingImageFilter::SetWindowMaximum(InputPixelType _arg)

"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::GetWindowMaximum "virtual const InputPixelType& itk::IntensityWindowingImageFilter::GetWindowMaximum()

"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::SetOutputMinimum "virtual void itk::IntensityWindowingImageFilter::SetOutputMinimum(OutputPixelType _arg)

Set/Get the values of the maximum and minimum intensities of the outputimage
"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::GetOutputMinimum "virtual const OutputPixelType& itk::IntensityWindowingImageFilter::GetOutputMinimum()

"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::SetOutputMaximum "virtual void itk::IntensityWindowingImageFilter::SetOutputMaximum(OutputPixelType _arg)

"

%feature("docstring") itk::simple::IntensityWindowingImageFilter::GetOutputMaximum "virtual const OutputPixelType& itk::IntensityWindowingImageFilter::GetOutputMaximum()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1InvertIntensityImageFilter.xml
%feature("docstring") itk::simple::InvertIntensityImageFilter "Invert intensity of an image.

 InvertIntensityImageFilterinvert intensity of pixels by subtracting pixel value to a maximum value. The maximum value can be set with SetMaximum and defaults the maximum of input pixel type. This filter can be used to invert, for example, a binary image, a distance map, etc.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

"
%feature("docstring") itk::simple::InvertIntensityImageFilter::Execute "Invert intensity of an image.
"
%feature("docstring") itk::simple::InvertIntensity "Invert intensity of an image.

 InvertIntensityImageFilterinvert intensity of pixels by subtracting pixel value to a maximum value. The maximum value can be set with SetMaximum and defaults the maximum of input pixel type. This filter can be used to invert, for example, a binary image, a distance map, etc.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

"
%feature("docstring") itk::simple::InvertIntensityImageFilter::SetMaximum "virtual void itk::InvertIntensityImageFilter::SetMaximum(InputPixelType _arg)

"

%feature("docstring") itk::simple::InvertIntensityImageFilter::GetMaximum "virtual const InputPixelType& itk::InvertIntensityImageFilter::GetMaximum()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelContourImageFilter.xml
%feature("docstring") itk::simple::LabelContourImageFilter "Labels the pixels on the border of the objects in a labeled image.

 LabelContourImageFiltertakes a labeled image as input, where the pixels in the objects are the pixels with a value different of the BackgroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue. The labels of the object are the same in the input and in the output image.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see BinaryContourImageFilter

"
%feature("docstring") itk::simple::LabelContourImageFilter::Execute "Labels the pixels on the border of the objects in a labeled image.
"
%feature("docstring") itk::simple::LabelContour "Labels the pixels on the border of the objects in a labeled image.

 LabelContourImageFiltertakes a labeled image as input, where the pixels in the objects are the pixels with a value different of the BackgroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue. The labels of the object are the same in the input and in the output image.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see BinaryContourImageFilter

"
%feature("docstring") itk::simple::LabelContourImageFilter::SetFullyConnected "virtual void itk::LabelContourImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff.note For objects that are 1 pixel wide, use FullyConnectedOn.

"

%feature("docstring") itk::simple::LabelContourImageFilter::GetFullyConnected "virtual const bool& itk::LabelContourImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::LabelContourImageFilter::SetBackgroundValue "virtual void itk::LabelContourImageFilter::SetBackgroundValue(OutputImagePixelType _arg)

Set/Get the background value used to identify the objects and mark the pixels not on the border of the objects.
"

%feature("docstring") itk::simple::LabelContourImageFilter::GetBackgroundValue "virtual OutputImagePixelType itk::LabelContourImageFilter::GetBackgroundValue() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LaplacianRecursiveGaussianImageFilter.xml
%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter "Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/LaplacianRecursiveGaussianImageFilter,Compute the Laplacian of an image}

"
%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter::Execute "Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.
"
%feature("docstring") itk::simple::LaplacianRecursiveGaussian "Computes the Laplacian of an image by convolution with the second derivative of a Gaussian.

This filter is implemented using the recursive gaussian filters

li {EdgesAndGradients/LaplacianRecursiveGaussianImageFilter,Compute the Laplacian of an image}

"
%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter::SetSigma "void itk::LaplacianRecursiveGaussianImageFilter::SetSigma(RealType sigma)

Set Sigma value. Sigma is measured in the units of image spacing.
"

%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter::SetNormalizeAcrossScale "void itk::LaplacianRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

Define which normalization factor will be used for the Gaussiansee RecursiveGaussianImageFilter::SetNormalizeAcrossScale

"

%feature("docstring") itk::simple::LaplacianRecursiveGaussianImageFilter::GetNormalizeAcrossScale "virtual bool itk::LaplacianRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1Log10ImageFilter.xml
%feature("docstring") itk::simple::Log10ImageFilter "Computes the vcl_log10(x) pixel-wise
-.

"
%feature("docstring") itk::simple::Log10ImageFilter::Execute "Computes the vcl_log10(x) pixel-wise
-.
"
%feature("docstring") itk::simple::Log10 "Computes the vcl_log10(x) pixel-wise
-.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LogImageFilter.xml
%feature("docstring") itk::simple::LogImageFilter "Computes the vcl_log(x) pixel-wise.

"
%feature("docstring") itk::simple::LogImageFilter::Execute "Computes the vcl_log(x) pixel-wise.
"
%feature("docstring") itk::simple::Log "Computes the vcl_log(x) pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaskImageFilter.xml
%feature("docstring") itk::simple::MaskImageFilter "Implements an operator for pixel-wise masking of the input image with the mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = pixel_input_image else pixel_output_image = outside_value
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see MaskNegatedImageFilter

li {ImageProcessing/MaskImageFilter,Apply a mask to an image}

"
%feature("docstring") itk::simple::MaskImageFilter::Execute "Implements an operator for pixel-wise masking of the input image with the mask.
"
%feature("docstring") itk::simple::Mask "Implements an operator for pixel-wise masking of the input image with the mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = pixel_input_image else pixel_output_image = outside_value
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see MaskNegatedImageFilter

li {ImageProcessing/MaskImageFilter,Apply a mask to an image}

"
%feature("docstring") itk::simple::MaskImageFilter::SetOutsideValue "void itk::MaskImageFilter::SetOutsideValue(const typename TOutputImage::PixelType &outsideValue)

Method to explicitly set the outside value of the mask. Defaults to 0
"

%feature("docstring") itk::simple::MaskImageFilter::GetOutsideValue "const TOutputImage::PixelType& itk::MaskImageFilter::GetOutsideValue() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaskNegatedImageFilter.xml
%feature("docstring") itk::simple::MaskNegatedImageFilter "Implements an operator for pixel-wise masking of the input image with the negative of a mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = output_value else pixel_output_image = pixel_input_image
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see MaskImageFilter

"
%feature("docstring") itk::simple::MaskNegatedImageFilter::Execute "Implements an operator for pixel-wise masking of the input image with the negative of a mask.
"
%feature("docstring") itk::simple::MaskNegated "Implements an operator for pixel-wise masking of the input image with the negative of a mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = output_value else pixel_output_image = pixel_input_image
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see MaskImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaximumImageFilter.xml
%feature("docstring") itk::simple::MaximumImageFilter "Implements a pixel-wise operator Max(a,b) between two images.

The pixel values of the output image are the maximum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MaximumImageFilter,Pixel wise compare two input images and set the output pixel to their max}

"
%feature("docstring") itk::simple::MaximumImageFilter::Execute "Implements a pixel-wise operator Max(a,b) between two images.
"
%feature("docstring") itk::simple::Maximum "Implements a pixel-wise operator Max(a,b) between two images.

The pixel values of the output image are the maximum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MaximumImageFilter,Pixel wise compare two input images and set the output pixel to their max}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MinimumImageFilter.xml
%feature("docstring") itk::simple::MinimumImageFilter "Implements a pixel-wise operator Min(a,b) between two images.

The pixel values of the output image are the minimum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults. + *

li {ImageProcessing/MinimumImageFilter,Pixel wise compare two input images and set the output pixel to their min}

"
%feature("docstring") itk::simple::MinimumImageFilter::Execute "Implements a pixel-wise operator Min(a,b) between two images.
"
%feature("docstring") itk::simple::Minimum "Implements a pixel-wise operator Min(a,b) between two images.

The pixel values of the output image are the minimum between the corresponding pixels of the two input images.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults. + *

li {ImageProcessing/MinimumImageFilter,Pixel wise compare two input images and set the output pixel to their min}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MinMaxCurvatureFlowImageFilter.xml
%feature("docstring") itk::simple::MinMaxCurvatureFlowImageFilter "Denoise an image using min/max curvature flow.

 MinMaxCurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = max(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ min(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is the average intensity obtained in the direction perpendicular to the gradient at pointf$ x f$ at the extrema of the local neighborhood.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a MinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images, however for dimensions greater than 3D, an expensive brute-force search is used to compute the local threshold.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see MinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter

"
%feature("docstring") itk::simple::MinMaxCurvatureFlowImageFilter::Execute "Denoise an image using min/max curvature flow.
"
%feature("docstring") itk::simple::MinMaxCurvatureFlow "Denoise an image using min/max curvature flow.

 MinMaxCurvatureFlowImageFilterimplements a curvature driven image denoising algorithm. Iso-brightness contours in the grayscale input image are viewed as a level set. The level set is then evolved using a curvature-based speed function:
 f[ I_t = F_{mbox{minmax}} |nabla I| f]  
wheref$ F_{mbox{minmax}} = max(kappa,0) f$ iff$ mbox{Avg}_{mbox{stencil}}(x) f$ is less than or equal tof$ T_{thresold} f$ andf$ min(kappa,0) f$ , otherwise.f$ kappa f$ is the mean curvature of the iso-brightness contour at pointf$ x f$ .
In min/max curvature flow, movement is turned on or off depending on the scale of the noise one wants to remove. Switching depends on the average image value of a region of radiusf$ R f$ around each point. The choice off$ R f$ , the stencil radius, governs the scale of the noise to be removed.
The threshold valuef$ T_{threshold} f$ is the average intensity obtained in the direction perpendicular to the gradient at pointf$ x f$ at the extrema of the local neighborhood.
This filter make use of the multi-threaded finite difference solver hierarchy. Updates are computed using a MinMaxCurvatureFlowFunctionobject. A zero flux Neumann boundary condition is used when computing derivatives near the data boundary.
warning This filter assumes that the input and output types have the same dimensions. This filter also requires that the output image pixels are of a real type. This filter works for any dimensional images, however for dimensions greater than 3D, an expensive brute-force search is used to compute the local threshold.
Reference: Level Set Methods and Fast Marching Methods, J.A. Sethian, Cambridge Press, Chapter 16, Second edition, 1999.
see MinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MirrorPadImageFilter.xml
%feature("docstring") itk::simple::MirrorPadImageFilter "Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, ConstantPadImageFilter

"
%feature("docstring") itk::simple::MirrorPadImageFilter::Execute "Increase the image size by padding with replicants of the input image value.
"
%feature("docstring") itk::simple::MirrorPad "Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, ConstantPadImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MorphologicalGradientImageFilter.xml
%feature("docstring") itk::simple::MorphologicalGradientImageFilter "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
%feature("docstring") itk::simple::MorphologicalGradientImageFilter::Execute "gray scale dilation of an image
"
%feature("docstring") itk::simple::MorphologicalGradient "gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MultiplyByConstantImageFilter.xml
%feature("docstring") itk::simple::MultiplyByConstantImageFilter "Multiply input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter
li {ImageProcessing/MultiplyByConstantImageFilter,Multiply every pixel in an image by a constant}


"
%feature("docstring") itk::simple::MultiplyByConstantImageFilter::Execute "Multiply input pixels by a constant.
"
%feature("docstring") itk::simple::MultiplyByConstant "Multiply input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter
li {ImageProcessing/MultiplyByConstantImageFilter,Multiply every pixel in an image by a constant}


"
%feature("docstring") itk::simple::MultiplyByConstantImageFilter::SetConstant "void itk::MultiplyByConstantImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
"

%feature("docstring") itk::simple::MultiplyByConstantImageFilter::GetConstant "const TConstant& itk::MultiplyByConstantImageFilter::GetConstant() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MultiplyImageFilter.xml
%feature("docstring") itk::simple::MultiplyImageFilter "Implements an operator for pixel-wise multiplication of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MultiplyImageFilter,Multiply two images together}

"
%feature("docstring") itk::simple::MultiplyImageFilter::Execute "Implements an operator for pixel-wise multiplication of two images.
"
%feature("docstring") itk::simple::Multiply "Implements an operator for pixel-wise multiplication of two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/MultiplyImageFilter,Multiply two images together}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1NeighborhoodConnectedImageFilter.xml
%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter "Label pixels that are connected to a seed and lie within a neighborhood.

 NeighborhoodConnectedImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND whose neighbors all lie within a Lower and Upper threshold range.
"
%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::Execute "Label pixels that are connected to a seed and lie within a neighborhood.
"
%feature("docstring") itk::simple::NeighborhoodConnected "Label pixels that are connected to a seed and lie within a neighborhood.

 NeighborhoodConnectedImageFilterlabels pixels with ReplaceValue that are connected to an initial Seed AND whose neighbors all lie within a Lower and Upper threshold range.
"
%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::SetUpper "virtual void itk::NeighborhoodConnectedImageFilter::SetUpper(InputImagePixelType _arg)

Set/Get the upper threshold. The default is the largest possible value for the InputPixelType.
"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::GetUpper "virtual InputImagePixelType itk::NeighborhoodConnectedImageFilter::GetUpper() const

"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::SetLower "virtual void itk::NeighborhoodConnectedImageFilter::SetLower(InputImagePixelType _arg)

Set/Get the lower threshold. The default is 0.
"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::GetLower "virtual InputImagePixelType itk::NeighborhoodConnectedImageFilter::GetLower() const

"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::SetReplaceValue "virtual void itk::NeighborhoodConnectedImageFilter::SetReplaceValue(OutputImagePixelType _arg)

Set/Get value to replace thresholded pixels. Pixels that lie * within Lower and Upper (inclusive) will be replaced with this value. The default is 1.
"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::GetReplaceValue "virtual OutputImagePixelType itk::NeighborhoodConnectedImageFilter::GetReplaceValue() const

"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::SetRadius "virtual void itk::NeighborhoodConnectedImageFilter::SetRadius(InputImageSizeType _arg)

Set the radius of the neighborhood used for a mask.
"

%feature("docstring") itk::simple::NeighborhoodConnectedImageFilter::GetRadius "virtual const InputImageSizeType& itk::NeighborhoodConnectedImageFilter::GetRadius()

Get the radius of the neighborhood used to compute the median
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1NotImageFilter.xml
%feature("docstring") itk::simple::NotImageFilter "Implements the NOT logical operator pixel-wise on an image.

This class is parametrized over the types of an input image and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical NOT operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( !input_pixel )
Where ! is the unary NOT operator in C++.
"
%feature("docstring") itk::simple::NotImageFilter::Execute "Implements the NOT logical operator pixel-wise on an image.
"
%feature("docstring") itk::simple::Not "Implements the NOT logical operator pixel-wise on an image.

This class is parametrized over the types of an input image and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical NOT operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( !input_pixel )
Where ! is the unary NOT operator in C++.
"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OpeningByReconstructionImageFilter.xml
%feature("docstring") itk::simple::OpeningByReconstructionImageFilter "Opening by reconstruction of an image.

This filter preserves regions, in the foreground, that can completely contain the structuring element. At the same time, this filter eliminates all other regions of foreground pixels. Contrary to the mophological opening, the opening by reconstruction preserves the shape of the components that are not removed by erosion. The opening by reconstruction of an image f is defined as:
OpeningByReconstruction(f) = DilationByRecontruction(f, Erosion(f)).
Opening by reconstruction not only removes structures destroyed by the erosion, but also levels down the contrast of the brightest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Opening by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see GrayscaleMorphologicalOpeningImageFilter

"
%feature("docstring") itk::simple::OpeningByReconstructionImageFilter::Execute "Opening by reconstruction of an image.
"
%feature("docstring") itk::simple::OpeningByReconstruction "Opening by reconstruction of an image.

This filter preserves regions, in the foreground, that can completely contain the structuring element. At the same time, this filter eliminates all other regions of foreground pixels. Contrary to the mophological opening, the opening by reconstruction preserves the shape of the components that are not removed by erosion. The opening by reconstruction of an image f is defined as:
OpeningByReconstruction(f) = DilationByRecontruction(f, Erosion(f)).
Opening by reconstruction not only removes structures destroyed by the erosion, but also levels down the contrast of the brightest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Opening by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see GrayscaleMorphologicalOpeningImageFilter

"
%feature("docstring") itk::simple::OpeningByReconstructionImageFilter::SetFullyConnected "virtual void itk::OpeningByReconstructionImageFilter::SetFullyConnected(bool _arg)

Set/Get whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.
"

%feature("docstring") itk::simple::OpeningByReconstructionImageFilter::GetFullyConnected "virtual const bool& itk::OpeningByReconstructionImageFilter::GetFullyConnected()

"

%feature("docstring") itk::simple::OpeningByReconstructionImageFilter::SetPreserveIntensities "virtual void itk::OpeningByReconstructionImageFilter::SetPreserveIntensities(bool _arg)

Set/Get whether the original intensities of the image retained for those pixels unaffected by the opening by reconstrcution. If Off, the output pixel contrast will be reduced.
"

%feature("docstring") itk::simple::OpeningByReconstructionImageFilter::GetPreserveIntensities "virtual const bool& itk::OpeningByReconstructionImageFilter::GetPreserveIntensities()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OrImageFilter.xml
%feature("docstring") itk::simple::OrImageFilter "Implements the OR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical OR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel | input2_pixel )
Where | is the boolean OR operator in C++.

li {ImageProcessing/OrImageFilter,Binary OR two images}

"
%feature("docstring") itk::simple::OrImageFilter::Execute "Implements the OR logical operator pixel-wise between two images.
"
%feature("docstring") itk::simple::Or "Implements the OR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical OR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel | input2_pixel )
Where | is the boolean OR operator in C++.

li {ImageProcessing/OrImageFilter,Binary OR two images}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1OtsuThresholdImageFilter.xml
%feature("docstring") itk::simple::OtsuThresholdImageFilter "Threshold an image using the Otsu Threshold.

This filter creates a binary thresholded image that separates an image into foreground and background components. The filter computes the threshold using the OtsuThresholdImageCalculatorand applies that theshold to the input image using the BinaryThresholdImageFilter. The NunberOfHistogram bins can be set for the Calculator. The InsideValue and OutsideValue can be set for the BinaryThresholdImageFilter.
see OtsuThresholdImageCalculator
see BinaryThresholdImageFilter

li {Segmentation/OtsuThresholdImageFilter,Separate foreground and background using Otsu's method}

"
%feature("docstring") itk::simple::OtsuThresholdImageFilter::Execute "Threshold an image using the Otsu Threshold.
"
%feature("docstring") itk::simple::OtsuThreshold "Threshold an image using the Otsu Threshold.

This filter creates a binary thresholded image that separates an image into foreground and background components. The filter computes the threshold using the OtsuThresholdImageCalculatorand applies that theshold to the input image using the BinaryThresholdImageFilter. The NunberOfHistogram bins can be set for the Calculator. The InsideValue and OutsideValue can be set for the BinaryThresholdImageFilter.
see OtsuThresholdImageCalculator
see BinaryThresholdImageFilter

li {Segmentation/OtsuThresholdImageFilter,Separate foreground and background using Otsu's method}

"
%feature("docstring") itk::simple::OtsuThresholdImageFilter::SetInsideValue "virtual void itk::OtsuThresholdImageFilter::SetInsideValue(OutputPixelType _arg)

Set the inside pixel value. The default value NumericTraits<OutputPixelType>::max()
"

%feature("docstring") itk::simple::OtsuThresholdImageFilter::GetInsideValue "virtual OutputPixelType itk::OtsuThresholdImageFilter::GetInsideValue() const

Get the inside pixel value.
"

%feature("docstring") itk::simple::OtsuThresholdImageFilter::SetNumberOfHistogramBins "virtual void itk::OtsuThresholdImageFilter::SetNumberOfHistogramBins(SizeValueType _arg)

Set/Get the number of histogram bins. Defaults is 128.
"

%feature("docstring") itk::simple::OtsuThresholdImageFilter::GetNumberOfHistogramBins "virtual SizeValueType itk::OtsuThresholdImageFilter::GetNumberOfHistogramBins() const

"

%feature("docstring") itk::simple::OtsuThresholdImageFilter::SetOutsideValue "virtual void itk::OtsuThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
"

%feature("docstring") itk::simple::OtsuThresholdImageFilter::GetOutsideValue "virtual OutputPixelType itk::OtsuThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1PermuteAxesImageFilter.xml
%feature("docstring") itk::simple::PermuteAxesImageFilter "Permutes the image axes according to a user specified order.

PermuateAxesImageFilter permutes the image axes according to a user specified order. The permutation order is set via method SetOrder( order ) where the input is an array of ImageDimension number of unsigned int. The elements of the array must be a rearrangment of the numbers from 0 to ImageDimension - 1.
The i-th axis of the output image corresponds with the order[i]-th axis of the input image.
The output meta image information (LargestPossibleRegion, spacing, origin) is computed by permuting the corresponding input meta information.

li {ImageProcessing/PermuteAxesImageFilter,Switch the axes of an image}

"
%feature("docstring") itk::simple::PermuteAxesImageFilter::Execute "Permutes the image axes according to a user specified order.
"
%feature("docstring") itk::simple::PermuteAxes "Permutes the image axes according to a user specified order.

PermuateAxesImageFilter permutes the image axes according to a user specified order. The permutation order is set via method SetOrder( order ) where the input is an array of ImageDimension number of unsigned int. The elements of the array must be a rearrangment of the numbers from 0 to ImageDimension - 1.
The i-th axis of the output image corresponds with the order[i]-th axis of the input image.
The output meta image information (LargestPossibleRegion, spacing, origin) is computed by permuting the corresponding input meta information.

li {ImageProcessing/PermuteAxesImageFilter,Switch the axes of an image}

"
%feature("docstring") itk::simple::PermuteAxesImageFilter::SetOrder "void itk::PermuteAxesImageFilter::SetOrder(const PermuteOrderArrayType &order)

Set the permutation order. The elements of order must be a rearrangement of the numbers from 0 to ImageDimension - 1.
"

%feature("docstring") itk::simple::PermuteAxesImageFilter::GetOrder "virtual const PermuteOrderArrayType& itk::PermuteAxesImageFilter::GetOrder()

Get the permutation order.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RecursiveGaussianImageFilter.xml
%feature("docstring") itk::simple::RecursiveGaussianImageFilter "Base class for computing IIR convolution with an approximation of a Gaussian kernel.

 f[ frac{ 1 }{ sigma sqrt{ 2 pi } } exp{ left( - frac{x^2}{ 2 sigma^2 } right) } f]  
 RecursiveGaussianImageFilteris the base class for recursive filters that approximate convolution with the Gaussian kernel. This class implements the recursive filtering method proposed by R.Deriche in IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, Fast Algorithms for Low-Level Vision
Details of the implementation are described in the technical report: R. Deriche, Recursively Implementing The Gaussian and Its Derivatives, INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz
Further improvements of the algorithm are described in: G. Farneback & C.-F. Westin, On Implementation of Recursive Gaussian Filters, so far unpublished.
As compared to itk::DiscreteGaussianImageFilter, this filter tends to be faster for large kernels, and it can take the derivative of the blurred image in one step. Also, note that we have itk::RecursiveGaussianImageFilter::SetSigma(), but itk::DiscreteGaussianImageFilter::SetVariance().
see DiscreteGaussianImageFilter
li {EdgesAndGradients/RecursiveGaussianImageFilter,Find higher derivatives of an image}


"
%feature("docstring") itk::simple::RecursiveGaussianImageFilter::Execute "Base class for computing IIR convolution with an approximation of a Gaussian kernel.
"
%feature("docstring") itk::simple::RecursiveGaussian "Base class for computing IIR convolution with an approximation of a Gaussian kernel.

 f[ frac{ 1 }{ sigma sqrt{ 2 pi } } exp{ left( - frac{x^2}{ 2 sigma^2 } right) } f]  
 RecursiveGaussianImageFilteris the base class for recursive filters that approximate convolution with the Gaussian kernel. This class implements the recursive filtering method proposed by R.Deriche in IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, Fast Algorithms for Low-Level Vision
Details of the implementation are described in the technical report: R. Deriche, Recursively Implementing The Gaussian and Its Derivatives, INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz
Further improvements of the algorithm are described in: G. Farneback & C.-F. Westin, On Implementation of Recursive Gaussian Filters, so far unpublished.
As compared to itk::DiscreteGaussianImageFilter, this filter tends to be faster for large kernels, and it can take the derivative of the blurred image in one step. Also, note that we have itk::RecursiveGaussianImageFilter::SetSigma(), but itk::DiscreteGaussianImageFilter::SetVariance().
see DiscreteGaussianImageFilter
li {EdgesAndGradients/RecursiveGaussianImageFilter,Find higher derivatives of an image}


"
%feature("docstring") itk::simple::RecursiveGaussianImageFilter::SetSigma "virtual void itk::RecursiveGaussianImageFilter::SetSigma(ScalarRealType _arg)

Set/Get the Sigma, measured in world coordinates, of the Gaussian kernel. The default is 1.0.
"

%feature("docstring") itk::simple::RecursiveGaussianImageFilter::GetSigma "virtual ScalarRealType itk::RecursiveGaussianImageFilter::GetSigma() const

Set/Get the Sigma, measured in world coordinates, of the Gaussian kernel. The default is 1.0.
"

%feature("docstring") itk::simple::RecursiveGaussianImageFilter::SetNormalizeAcrossScale "virtual void itk::RecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool _arg)

Set/Get the flag for normalizing the gaussian over scale-space.
This flag enables the analysis of the differential shape of features independent of their size ( both pixels and physical size ). Following the notation of Tony Lindeberg:
Let f[ L(x; t) = g(x; t) ast f(x) f]  be the scale-space representation of image f[ f(x) f]  where f[ g(x; t) = frac{1}{ sqrt{ 2 pi t} } exp{ left( -frac{x^2}{ 2 t } right) } f]  is the Gaussian function and f[astf]  denotes convolution. This is a change from above with f[ t = sigma^2 f]  .
Then the normalized derivative operator for normalized coordinates across scale is:
 f[ partial_xi = sqrt{t} partial_x f]  
The resulting scaling factor is f[ sigma^N f]  where N is the order of the derivative.
When this flag is ON the filter will be normalized in such a way that the values of derivatives are not biased by the size of the object. That is to say the maximum value a feature reaches across scale is independent of the scale of the object.
For analyzing an image across scale-space you want to enable this flag. It is disabled by default.
note Not all scale space axioms are satisfied by this filter, some are only approximated. Particularly, at fine scales ( say less than 1 pixel ) other methods such as a discrete Gaussian kernel should be considered.

"

%feature("docstring") itk::simple::RecursiveGaussianImageFilter::GetNormalizeAcrossScale "virtual bool itk::RecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

"

%feature("docstring") itk::simple::RecursiveGaussianImageFilter::SetOrder "virtual void itk::RecursiveGaussianImageFilter::SetOrder(OrderEnumType _arg)

Set/Get the Order of the Gaussian to convolve with.
li ZeroOrder is equivalent to convolving with a Gaussian. This is the default.
li FirstOrder is equivalent to convolving with the first derivative of a Gaussian.
li SecondOrder is equivalent to convolving with the second derivative of a Gaussian.

"

%feature("docstring") itk::simple::RecursiveGaussianImageFilter::GetOrder "virtual OrderEnumType itk::RecursiveGaussianImageFilter::GetOrder() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RescaleIntensityImageFilter.xml
%feature("docstring") itk::simple::RescaleIntensityImageFilter "Applies a linear transformation to the intensity levels of the input Image.

 RescaleIntensityImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.
The following equation gives the mapping of the intensity values
par  f[ outputPixel = ( inputPixel - inputMin) cdot frac{(outputMax - outputMin )}{(inputMax - inputMin)} + outputMin f]  
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image are computed internally using the MinimumMaximumImageCalculator. Users are not supposed to set those values in this filter. If you need a filter where you can set the minimum and maximum values of the input, please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear transformation for the intensity, then please use the ShiftScaleImageFilter.
see IntensityWindowingImageFilter

li {ImageProcessing/RescaleIntensityImageFilter,Rescale the intensity values of an image to a specified range}

"
%feature("docstring") itk::simple::RescaleIntensityImageFilter::Execute "Applies a linear transformation to the intensity levels of the input Image.
"
%feature("docstring") itk::simple::RescaleIntensity "Applies a linear transformation to the intensity levels of the input Image.

 RescaleIntensityImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.
The following equation gives the mapping of the intensity values
par  f[ outputPixel = ( inputPixel - inputMin) cdot frac{(outputMax - outputMin )}{(inputMax - inputMin)} + outputMin f]  
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image are computed internally using the MinimumMaximumImageCalculator. Users are not supposed to set those values in this filter. If you need a filter where you can set the minimum and maximum values of the input, please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear transformation for the intensity, then please use the ShiftScaleImageFilter.
see IntensityWindowingImageFilter

li {ImageProcessing/RescaleIntensityImageFilter,Rescale the intensity values of an image to a specified range}

"
%feature("docstring") itk::simple::RescaleIntensityImageFilter::SetOutputMaximum "virtual void itk::RescaleIntensityImageFilter::SetOutputMaximum(OutputPixelType _arg)

"

%feature("docstring") itk::simple::RescaleIntensityImageFilter::GetOutputMaximum "virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMaximum()

"

%feature("docstring") itk::simple::RescaleIntensityImageFilter::SetOutputMinimum "virtual void itk::RescaleIntensityImageFilter::SetOutputMinimum(OutputPixelType _arg)

"

%feature("docstring") itk::simple::RescaleIntensityImageFilter::GetOutputMinimum "virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMinimum()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ShapeDetectionLevelSetImageFilter.xml
%feature("docstring") itk::simple::ShapeDetectionLevelSetImageFilter "Segments structures in images based on a user supplied edge potential map.

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
see SegmentationLevelSetImageFilter
see ShapeDetectionLevelSetFunction
see SparseFieldLevelSetImageFilter

"
%feature("docstring") itk::simple::ShapeDetectionLevelSetImageFilter::Execute "Segments structures in images based on a user supplied edge potential map.
"
%feature("docstring") itk::simple::ShapeDetectionLevelSet "Segments structures in images based on a user supplied edge potential map.

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
see SegmentationLevelSetImageFilter
see ShapeDetectionLevelSetFunction
see SparseFieldLevelSetImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ShrinkImageFilter.xml
%feature("docstring") itk::simple::ShrinkImageFilter "Reduce the size of an image by an integer factor in each dimension.

 ShrinkImageFilterreduces the size of an image by an integer factor in each dimension. The algorithm implemented is a simple subsample. The output image size in each dimension is given by:
outputSize[j] = max( vcl_floor(inputSize[j]/shrinkFactor[j]), 1 );
NOTE: The physical centers of the input and output will be the same. Because of this, the Origin of the output may not be the same as the Origin of the input. Since this filter produces an image which is a different resolution, origin and with different pixel spacing than its input image, it needs to override several of the methods defined in ProcessObjectin order to properly manage the pipeline execution model. In particular, this filter overrides ProcessObject::GenerateInputRequestedRegion()and ProcessObject::GenerateOutputInformation().
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Images/ShrinkImageFilter,Shrink an image}

"
%feature("docstring") itk::simple::ShrinkImageFilter::Execute "Reduce the size of an image by an integer factor in each dimension.
"
%feature("docstring") itk::simple::Shrink "Reduce the size of an image by an integer factor in each dimension.

 ShrinkImageFilterreduces the size of an image by an integer factor in each dimension. The algorithm implemented is a simple subsample. The output image size in each dimension is given by:
outputSize[j] = max( vcl_floor(inputSize[j]/shrinkFactor[j]), 1 );
NOTE: The physical centers of the input and output will be the same. Because of this, the Origin of the output may not be the same as the Origin of the input. Since this filter produces an image which is a different resolution, origin and with different pixel spacing than its input image, it needs to override several of the methods defined in ProcessObjectin order to properly manage the pipeline execution model. In particular, this filter overrides ProcessObject::GenerateInputRequestedRegion()and ProcessObject::GenerateOutputInformation().
This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.

li {Images/ShrinkImageFilter,Shrink an image}

"
%feature("docstring") itk::simple::ShrinkImageFilter::SetShrinkFactors "virtual void itk::ShrinkImageFilter::SetShrinkFactors(ShrinkFactorsType _arg)

Set the shrink factors. Values are clamped to a minimum value of 1. Default is 1 for all dimensions.
"

%feature("docstring") itk::simple::ShrinkImageFilter::GetShrinkFactors "virtual const ShrinkFactorsType& itk::ShrinkImageFilter::GetShrinkFactors()

Get the shrink factors.
"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SigmoidImageFilter.xml
%feature("docstring") itk::simple::SigmoidImageFilter "Computes the sigmoid function pixel-wise.

A linear transformation is applied first on the argument of the sigmoid fuction. The resulting total transfrom is given by
 f[ f(x) = (Max-Min) cdot frac{1}{left(1+e^{- frac{ x - beta }{alpha}}right)} + Min f]  
Every output pixel is equal to f(x). Where x is the intensity of the homologous input pixel, and alpha and beta are user-provided constants.

li {ImageProcessing/SigmoidImageFilter,Pass image pixels through a sigmoid function}

"
%feature("docstring") itk::simple::SigmoidImageFilter::Execute "Computes the sigmoid function pixel-wise.
"
%feature("docstring") itk::simple::Sigmoid "Computes the sigmoid function pixel-wise.

A linear transformation is applied first on the argument of the sigmoid fuction. The resulting total transfrom is given by
 f[ f(x) = (Max-Min) cdot frac{1}{left(1+e^{- frac{ x - beta }{alpha}}right)} + Min f]  
Every output pixel is equal to f(x). Where x is the intensity of the homologous input pixel, and alpha and beta are user-provided constants.

li {ImageProcessing/SigmoidImageFilter,Pass image pixels through a sigmoid function}

"
%feature("docstring") itk::simple::SigmoidImageFilter::SetAlpha "void itk::SigmoidImageFilter::SetAlpha(double alpha)

"

%feature("docstring") itk::simple::SigmoidImageFilter::SetBeta "void itk::SigmoidImageFilter::SetBeta(double beta)

"

%feature("docstring") itk::simple::SigmoidImageFilter::SetOutputMaximum "void itk::SigmoidImageFilter::SetOutputMaximum(OutputPixelType max)

"

%feature("docstring") itk::simple::SigmoidImageFilter::SetOutputMinimum "void itk::SigmoidImageFilter::SetOutputMinimum(OutputPixelType min)

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SinImageFilter.xml
%feature("docstring") itk::simple::SinImageFilter "Computes the vcl_sin(x) pixel-wise.

"
%feature("docstring") itk::simple::SinImageFilter::Execute "Computes the vcl_sin(x) pixel-wise.
"
%feature("docstring") itk::simple::Sin "Computes the vcl_sin(x) pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SmoothingRecursiveGaussianImageFilter.xml
%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter "Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.

This filter is implemented using the recursive gaussian filters. For multi-component images, the filter works on each component independently.
For this filter to be able to run in-place the input and output image types need to be the same and/or the same type as the RealImageType.

li {Smoothing/SmoothingRecursiveGaussianImageFilter,Gaussian smoothing that works with image adaptors}

"
%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter::Execute "Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.
"
%feature("docstring") itk::simple::SmoothingRecursiveGaussian "Computes the smoothing of an image by convolution with the Gaussian kernels implemented as IIR filters.

This filter is implemented using the recursive gaussian filters. For multi-component images, the filter works on each component independently.
For this filter to be able to run in-place the input and output image types need to be the same and/or the same type as the RealImageType.

li {Smoothing/SmoothingRecursiveGaussianImageFilter,Gaussian smoothing that works with image adaptors}

"
%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter::SetSigma "void itk::SmoothingRecursiveGaussianImageFilter::SetSigma(ScalarRealType sigma)

"

%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter::GetSigma "ScalarRealType itk::SmoothingRecursiveGaussianImageFilter::GetSigma() const

"

%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter::SetNormalizeAcrossScale "void itk::SmoothingRecursiveGaussianImageFilter::SetNormalizeAcrossScale(bool normalizeInScaleSpace)

This method does not effect the output of this filter.
see RecursiveGaussianImageFilter::SetNormalizeAcrossScale

"

%feature("docstring") itk::simple::SmoothingRecursiveGaussianImageFilter::GetNormalizeAcrossScale "virtual bool itk::SmoothingRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SqrtImageFilter.xml
%feature("docstring") itk::simple::SqrtImageFilter "Computes the vcl_sqrt(x) pixel-wise.

"
%feature("docstring") itk::simple::SqrtImageFilter::Execute "Computes the vcl_sqrt(x) pixel-wise.
"
%feature("docstring") itk::simple::Sqrt "Computes the vcl_sqrt(x) pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SquaredDifferenceImageFilter.xml
%feature("docstring") itk::simple::SquaredDifferenceImageFilter "Implements pixel-wise the computation of squared difference.

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

"
%feature("docstring") itk::simple::SquaredDifferenceImageFilter::Execute "Implements pixel-wise the computation of squared difference.
"
%feature("docstring") itk::simple::SquaredDifference "Implements pixel-wise the computation of squared difference.

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

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SquareImageFilter.xml
%feature("docstring") itk::simple::SquareImageFilter "Computes the square of the intensity values pixel-wise.

"
%feature("docstring") itk::simple::SquareImageFilter::Execute "Computes the square of the intensity values pixel-wise.
"
%feature("docstring") itk::simple::Square "Computes the square of the intensity values pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SubtractConstantFromImageFilter.xml
%feature("docstring") itk::simple::SubtractConstantFromImageFilter "Subract a constant from all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

"
%feature("docstring") itk::simple::SubtractConstantFromImageFilter::Execute "Subract a constant from all input pixels.
"
%feature("docstring") itk::simple::SubtractConstantFrom "Subract a constant from all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

"
%feature("docstring") itk::simple::SubtractConstantFromImageFilter::SetConstant "void itk::SubtractConstantFromImageFilter::SetConstant(TConstant ct)

Set the constant that will be used to multiply all the image pixels
"

%feature("docstring") itk::simple::SubtractConstantFromImageFilter::GetConstant "const TConstant& itk::SubtractConstantFromImageFilter::GetConstant() const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1SubtractImageFilter.xml
%feature("docstring") itk::simple::SubtractImageFilter "Implements an operator for pixel-wise subtraction of two images.

Output = Input1 - Input2.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/SubtractImageFilter,Subtract two images}

"
%feature("docstring") itk::simple::SubtractImageFilter::Execute "Implements an operator for pixel-wise subtraction of two images.
"
%feature("docstring") itk::simple::Subtract "Implements an operator for pixel-wise subtraction of two images.

Output = Input1 - Input2.
This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.

li {ImageProcessing/SubtractImageFilter,Subtract two images}

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1TanImageFilter.xml
%feature("docstring") itk::simple::TanImageFilter "Computes the vcl_tan(x) pixel-wise.

"
%feature("docstring") itk::simple::TanImageFilter::Execute "Computes the vcl_tan(x) pixel-wise.
"
%feature("docstring") itk::simple::Tan "Computes the vcl_tan(x) pixel-wise.

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1VectorIndexSelectionCastImageFilter.xml
%feature("docstring") itk::simple::VectorIndexSelectionCastImageFilter "Extracts the selected index of the vector that is the input pixel type.

This filter is templated over the input image type and output image type.
The filter expect the input image pixel type to be a vector and the output image pixel type to be a scalar. The only requirement on the type used for representing the vector is that it must provide an operator[].

li {VectorImages/VectorIndexSelectionCastImageFilter,Extract a component of an itkVectorImage}

"
%feature("docstring") itk::simple::VectorIndexSelectionCastImageFilter::Execute "Extracts the selected index of the vector that is the input pixel type.
"
%feature("docstring") itk::simple::VectorIndexSelectionCast "Extracts the selected index of the vector that is the input pixel type.

This filter is templated over the input image type and output image type.
The filter expect the input image pixel type to be a vector and the output image pixel type to be a scalar. The only requirement on the type used for representing the vector is that it must provide an operator[].

li {VectorImages/VectorIndexSelectionCastImageFilter,Extract a component of an itkVectorImage}

"
%feature("docstring") itk::simple::VectorIndexSelectionCastImageFilter::SetIndex "void itk::VectorIndexSelectionCastImageFilter::SetIndex(unsigned int i)

Get/Set methods for the index
"

%feature("docstring") itk::simple::VectorIndexSelectionCastImageFilter::GetIndex "unsigned int itk::VectorIndexSelectionCastImageFilter::GetIndex(void) const

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1WhiteTopHatImageFilter.xml
%feature("docstring") itk::simple::WhiteTopHatImageFilter "White top hat extract local maxima that are larger than the structuring element.

Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

"
%feature("docstring") itk::simple::WhiteTopHatImageFilter::Execute "White top hat extract local maxima that are larger than the structuring element.
"
%feature("docstring") itk::simple::WhiteTopHat "White top hat extract local maxima that are larger than the structuring element.

Top-hats are described in Chapter 4.5 of Pierre Soille's book Morphological Image Analysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.

"
%feature("docstring") itk::simple::WhiteTopHatImageFilter::SetSafeBorder "virtual void itk::WhiteTopHatImageFilter::SetSafeBorder(bool _arg)

A safe border is added to input image to avoid borders effects and remove it once the closing is done
"

%feature("docstring") itk::simple::WhiteTopHatImageFilter::GetSafeBorder "virtual const bool& itk::WhiteTopHatImageFilter::GetSafeBorder()

"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1WrapPadImageFilter.xml
%feature("docstring") itk::simple::WrapPadImageFilter "Increase the image size by padding with replicants of the input image value.

 WrapPadImageFilterchanges the image bounds of an image. Added pixels are filled in with a wrapped replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the right boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see MirrorPadImageFilter, ConstantPadImageFilter

"
%feature("docstring") itk::simple::WrapPadImageFilter::Execute "Increase the image size by padding with replicants of the input image value.
"
%feature("docstring") itk::simple::WrapPad "Increase the image size by padding with replicants of the input image value.

 WrapPadImageFilterchanges the image bounds of an image. Added pixels are filled in with a wrapped replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the right boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see MirrorPadImageFilter, ConstantPadImageFilter

"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1XorImageFilter.xml
%feature("docstring") itk::simple::XorImageFilter "Implements the XOR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical XOR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel ^ input2_pixel )
Where ^ is the boolean XOR operator in C++.

li {ImageProcessing/XorImageFilter,Binary XOR (exclusive OR) two images}

"
%feature("docstring") itk::simple::XorImageFilter::Execute "Implements the XOR logical operator pixel-wise between two images.
"
%feature("docstring") itk::simple::Xor "Implements the XOR logical operator pixel-wise between two images.

This class is parametrized over the types of the two input images and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
Since the logical XOR operation is only defined in C++ for integer types, the images passed to this filter must comply with the requirement of using integer pixel type.
The total operation over one pixel will be
output_pixel = static_cast<OutputPixelType>( input1_pixel ^ input2_pixel )
Where ^ is the boolean XOR operator in C++.

li {ImageProcessing/XorImageFilter,Binary XOR (exclusive OR) two images}

"
