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
see UnaryFunctorImageFilter
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
see UnaryFunctorImageFilter
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
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryClosingByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::BinaryClosingByReconstructionImageFilter "/** binary closing by reconstruction of an image.

This filter removes small ( i.e., smaller than the structuring element) holes in the image. It is defined as: Closing(f) = ReconstructionByErosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

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
see MorphologyImageFilter, ClosingByReconstructionImageFilter, BinaryOpeningByReconstructionImageFilter

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
see LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
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
see LabelContourImageFilter BinaryErodeImageFilter SimpleContourExtractorImageFilter
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
see ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
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
see ImageToImageFilter BinaryErodeImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryDilateImageFilter,Dilate a binary image}


*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryErodeImageFilter.xml
%typemap(javaimports) itk::simple::BinaryErodeImageFilter "/** Fast binary erosion.

 BinaryErodeImageFilteris a binary erosion morphologic operation. This implementation is based on the papers:
L.Vincent Morphological transformations of binary images with arbitrary structuring elements, and
N.Nikopoulos et al. An efficient algorithm for 3d binary morphological transformations with 3d structuring elements for arbitrary size and shape. IEEE Transactions on ImageProcessing. Vol. 9. No. 3. 2000. pp. 283-286.
Gray scale images can be processed as binary images by selecting a ErodeValue. Pixel values matching the dilate value are considered the foreground and all other pixels are background. This is useful in processing segmented images where all pixels in segment #1 have value 1 and pixels in segment #2 have value 2, etc. A particular segment number can be processed. ErodeValue defaults to the maximum possible value of the PixelType. The eroded pixels will receive the BackgroundValue (defaults to 0).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel. A reasonable choice of structuring element is itk::BinaryBallStructuringElement.
see ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
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
see ImageToImageFilter BinaryDilateImageFilter BinaryMorphologyImageFilter
li {Morphology/BinaryErodeImageFilter,Erode a binary image}


*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryFillholeImageFilter.xml
%typemap(javaimports) itk::simple::BinaryFillholeImageFilter "/** Remove holes not connected to the boundary of the image.

 BinaryFillholeImageFilterfills holes in a binary image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/584orhttp://www.insight-journal.org/browse/publication/176
see GrayscaleFillholeImageFilter

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
see GrayscaleFillholeImageFilter

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
see GrayscaleGrindPeakImageFilter

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
see GrayscaleGrindPeakImageFilter

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
see BinaryMinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see MinMaxCurvatureFlowImageFilter

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
see BinaryMinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see MinMaxCurvatureFlowImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1BinaryMorphologicalClosingImageFilter.xml
%typemap(javaimports) itk::simple::BinaryMorphologicalClosingImageFilter "/** binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalClosingImageFilter::execute() "
/**binary morphological closing of an image.

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalClosing "/**
binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) holes and tube like structures in the interior or at the boundaries of the image. The morphological closing of an image f is defined as: Closing(f) = Erosion(Dilation(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

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
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalOpeningImageFilter::execute() "
/**binary morphological closing of an image.

*/"
%javamethodmodifiers itk::simple::BinaryMorphologicalOpening "/**
binary morphological closing of an image.

This filter removes small ( i.e., smaller than the structuring element) structures in the interior or at the boundaries of the image. The morphological opening of an image f is defined as: Opening(f) = Dilatation(Erosion(f)).
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleErodeImageFilter

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
see MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

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
see MorphologyImageFilter, OpeningByReconstructionImageFilter, BinaryClosingByReconstructionImageFilter

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
see MorphologyImageFilter

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
see MorphologyImageFilter

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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ClosingByReconstructionImageFilter.xml
%typemap(javaimports) itk::simple::ClosingByReconstructionImageFilter "/** Closing by reconstruction of an image.

This filter is similar to the morphological closing, but contrary to the mophological closing, the closing by reconstruction preserves the shape of the components. The closing by reconstruction of an image f is defined as:
ClosingByReconstruction(f) = ErosionByReconstruction(f, Dilation(f)).
Closing by reconstruction not only preserves structures preserved by the dilation, but also levels raises the contrast of the darkest regions. If PreserveIntensities is on, a subsequent reconstruction by dilation using a marker image that is the original image for all unaffected pixels.
Closing by reconstruction is described in Chapter 6.3.9 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see GrayscaleMorphologicalClosingImageFilter

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
see GrayscaleMorphologicalClosingImageFilter

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
see WrapPadImageFilter, MirrorPadImageFilter
li {Images/ConstantPadImageFilter,Pad an image with a constant value}


*/"
%javamethodmodifiers itk::simple::ConstantPadImageFilter::execute() "
/**Increase the image size by padding with a constant value.

*/"
%javamethodmodifiers itk::simple::ConstantPad "/**
Increase the image size by padding with a constant value.

 ConstantPadImageFilterchanges the output image region. If the output image region is larger than the input image region, the extra pixels are filled in by a constant value. The output image region must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, MirrorPadImageFilter
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
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
see CurvatureNDAnisotropicDiffusionFunction

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
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
see CurvatureNDAnisotropicDiffusionFunction

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
see DenseFiniteDifferenceImageFilter
see CurvatureFlowFunction
see MinMaxCurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter
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
see DenseFiniteDifferenceImageFilter
see CurvatureFlowFunction
see MinMaxCurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter
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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DilateObjectMorphologyImageFilter.xml
%typemap(javaimports) itk::simple::DilateObjectMorphologyImageFilter "/** dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::DilateObjectMorphologyImageFilter::execute() "
/**dilation of an object in an image

*/"
%javamethodmodifiers itk::simple::DilateObjectMorphology "/**
dilation of an object in an image

Dilate an image using binary morphology. Pixel values matching the object value are considered the foreground and all other pixels are background. This is useful in processing mask images containing only one object.
If a pixel's value is equal to the object value and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the object value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, ErodeObjectMorphologyImageFilter
see BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1DivideByConstantImageFilter.xml
%typemap(javaimports) itk::simple::DivideByConstantImageFilter "/** Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::DivideByConstantImageFilter::execute() "
/**Divide input pixels by a constant.

*/"
%javamethodmodifiers itk::simple::DivideByConstant "/**
Divide input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

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
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::DoubleThresholdImageFilter::execute() "
/**Binarize an input image using double thresholding.

*/"
%javamethodmodifiers itk::simple::DoubleThreshold "/**
Binarize an input image using double thresholding.

Double threshold addresses the difficulty in selecting a threshold that will select the objects of interest without selecting extraneous objects. Double threshold considers two threshold ranges: a narrow range and a wide range (where the wide range encompasses the narrow range). If the wide range was used for a traditional threshold (where values inside the range map to the foreground and values outside the range map to the background), many extraneous pixels may survive the threshold operation. If the narrow range was used for a traditional threshold, then too few pixels may survive the threshold.
Double threshold uses the narrow threshold image as a marker image and the wide threshold image as a mask image in the geodesic dilation. Essentially, the marker image (narrow threshold) is dilated but constrained to lie within the mask image (wide threshold). Thus, only the objects of interest (those pixels that survived the narrow threshold) are extracted but the those objects appear in the final image as they would have if the wide threshold was used.
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1ErodeObjectMorphologyImageFilter.xml
%typemap(javaimports) itk::simple::ErodeObjectMorphologyImageFilter "/** Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::ErodeObjectMorphologyImageFilter::execute() "
/**Erosion of an object in an image.

*/"
%javamethodmodifiers itk::simple::ErodeObjectMorphology "/**
Erosion of an object in an image.

Erosion of an image using binary morphology. Pixel values matching the object value are considered the object and all other pixels are background. This is useful in processing mask images containing only one object.
If the pixel covered by the center of the kernel has the pixel value ObjectValue and the pixel is adjacent to a non-object valued pixel, then the kernel is centered on the object-value pixel and neighboring pixels covered by the kernel are assigned the background value. The structuring element is assumed to be composed of binary values (zero or one).
see ObjectMorphologyImageFilter, BinaryFunctionErodeImageFilter
see BinaryErodeImageFilter

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
see SegmentationLevelSetImageFilter
see GeodesicActiveContourLevelSetFunction
see SparseFieldLevelSetImageFilter

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
see SegmentationLevelSetImageFilter
see GeodesicActiveContourLevelSetFunction
see SparseFieldLevelSetImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GradientAnisotropicDiffusionImageFilter.xml
%typemap(javaimports) itk::simple::GradientAnisotropicDiffusionImageFilter "/** 
This filter performs anisotropic diffusion on a scalar itk::Imageusing the classic Perona-Malik, gradient magnitude based equation implemented in itkGradientNDAnisotropicDiffusionFunction. For detailed information on anisotropic diffusion, see itkAnisotropicDiffusionFunction and itkGradientNDAnisotropicDiffusionFunction.
par Inputs and Outputs
The input to this filter should be a scalar itk::Imageof any dimensionality. The output image will be a diffused copy of the input.
par Parameters
Please see the description of parameters given in itkAnisotropicDiffusionImageFilter.
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
seeGradientAnisotropicDiffusionFunction

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
see AnisotropicDiffusionImageFilter
see AnisotropicDiffusionFunction
seeGradientAnisotropicDiffusionFunction

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

Define which normalization factor will be used for the Gaussiansee RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::GradientMagnitudeRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::GradientMagnitudeRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleDilateImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleDilateImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

*/"
%javamethodmodifiers itk::simple::GrayscaleDilateImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleDilate "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

li {Morphology/GrayscaleDilateImageFilter,Dilate a grayscale image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleErodeImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleErodeImageFilter "/** gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

*/"
%javamethodmodifiers itk::simple::GrayscaleErodeImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleErode "/**
gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

li {Morphology/GrayscaleErodeImageFilter,Erode a grayscale image}

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleFillholeImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleFillholeImageFilter "/** Remove local minima not connected to the boundary of the image.

 GrayscaleFillholeImageFilterfills holes in a grayscale image. Holes are local minima in the grayscale topography that are not connected to boundaries of the image. Gray level values adjacent to a hole are extrapolated across the hole.
This filter is used to smooth over local minima without affecting the values of local maxima. If you take the difference between the output of this filter and the original image (and perhaps threshold the difference above a small value), you'll obtain a map of the local minima.
This filter uses the ReconstructionByErosionImageFilter. It provides its own input as the mask input to the geodesic erosion. The marker image for the geodesic erosion is constructed such that boundary pixels match the boundary pixels of the input image and the interior pixels are set to the maximum pixel value in the input image.
Geodesic morphology and the Fillhole algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see ReconstructionByErosionImageFilter
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

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
see ReconstructionByErosionImageFilter
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

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
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

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
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter, ReconstructionByDilationImageFilter

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
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

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
see MorphologyImageFilter, GrayscaleErodeImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter, ReconstructionByErosionImageFilter

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
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see GrayscaleGeodesicDilateImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalClosingImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalClosing "/**
gray scale dilation of an image

Erode an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1GrayscaleMorphologicalOpeningImageFilter.xml
%typemap(javaimports) itk::simple::GrayscaleMorphologicalOpeningImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalOpeningImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::GrayscaleMorphologicalOpening "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HConcaveImageFilter.xml
%typemap(javaimports) itk::simple::HConcaveImageFilter "/** Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConcaveImageFilter::execute() "
/**Identify local minima whose depth below the baseline is greater than h.

*/"
%javamethodmodifiers itk::simple::HConcave "/**
Identify local minima whose depth below the baseline is greater than h.

 HConcaveImageFilterextract local minima that are more than h intensity units below the (local) background. This has the effect of extracting objects that are darker than the background by at least h intensity units.
This filter uses the HMinimaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMaximaImageFilter,
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::HConvexImageFilter::execute() "
/**Identify local maxima whose height above the baseline is greater than h.

*/"
%javamethodmodifiers itk::simple::HConvex "/**
Identify local maxima whose height above the baseline is greater than h.

 HConvexImageFilterextract local maxima that are more than h intensity units above the (local) background. This has the effect of extracting objects that are brighter than background by at least h intensity units.
This filter uses the HMaximaImageFilter.
Geodesic morphology and the H-Convex algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1HMaximaImageFilter.xml
%typemap(javaimports) itk::simple::HMaximaImageFilter "/** Suppress local maxima whose height above the baseline is less than h.

 HMaximaImageFiltersuppresses local maxima that are less than h intensity units above the (local) background. This has the effect of smoothing over the high parts of the noise in the image without smoothing over large changes in intensity (region boundaries). See the HMinimaImageFilterto suppress the local minima whose depth is less than h intensity units below the (local) background.
If the output of HMaximaImageFilteris subtracted from the original image, the signicant peaks in the image can be identified. This is what the HConvexImageFilterprovides.
This filter uses the ReconstructionByDilationImageFilter. It provides its own input as the mask input to the geodesic dilation. The marker image for the geodesic dilation is the input image minus the height parameter h.
Geodesic morphology and the H-Maxima algorithm is described in Chapter 6 of Pierre Soille's book Morphological ImageAnalysis: Principles and Applications, Second Edition, Springer, 2003.
The height parameter is set using SetHeight.
see ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see ReconstructionByDilationImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see GrayscaleGeodesicDilateImageFilter, HMinimaImageFilter, HConvexImageFilter
see MorphologyImageFilter, GrayscaleDilateImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

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
see IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

*/"
%javamethodmodifiers itk::simple::InvertIntensityImageFilter::execute() "
/**Invert intensity of an image.

*/"
%javamethodmodifiers itk::simple::InvertIntensity "/**
Invert intensity of an image.

 InvertIntensityImageFilterinvert intensity of pixels by subtracting pixel value to a maximum value. The maximum value can be set with SetMaximum and defaults the maximum of input pixel type. This filter can be used to invert, for example, a binary image, a distance map, etc.
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see IntensityWindowingImageFilter ShiftScaleImageFilter

li {ImageProcessing/InvertIntensityImageFilter,Invert an image}

*/"
%javamethodmodifiers itk::simple::InvertIntensityImageFilter::setMaximum "/**
virtual void itk::InvertIntensityImageFilter::SetMaximum(InputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::InvertIntensityImageFilter::getMaximum "/**
virtual const InputPixelType& itk::InvertIntensityImageFilter::GetMaximum()

*/"

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1LabelContourImageFilter.xml
%typemap(javaimports) itk::simple::LabelContourImageFilter "/** Labels the pixels on the border of the objects in a labeled image.

 LabelContourImageFiltertakes a labeled image as input, where the pixels in the objects are the pixels with a value different of the BackgroundValue. Only the pixels on the contours of the objects are kept. The pixels not on the border are changed to BackgroundValue. The labels of the object are the same in the input and in the output image.
The connectivity can be changed to minimum or maximum connectivity with SetFullyConnected(). Full connectivity produces thicker contours.
http://hdl.handle.net/1926/1352
author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
see BinaryContourImageFilter

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
see BinaryContourImageFilter

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

Define which normalization factor will be used for the Gaussiansee RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::LaplacianRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::LaplacianRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

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
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MaskImageFilter.xml
%typemap(javaimports) itk::simple::MaskImageFilter "/** Implements an operator for pixel-wise masking of the input image with the mask.

This class is parametrized over the types of the input image type, the mask image type and the type of the output image. Numeric conversions (castings) are done by the C++ defaults.
The pixel type of the input 2 image must have a valid defintion of the operator != with zero. This condition is required because internally this filter will perform the operation
if pixel_from_mask_image != 0 pixel_output_image = pixel_input_image else pixel_output_image = outside_value
The pixel from the input 1 is cast to the pixel type of the output image.
Note that the input and the mask images must be of the same size.
warning Any pixel value other than 0 will not be masked out.
see MaskNegatedImageFilter

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
see MaskNegatedImageFilter

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
see MaskImageFilter

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
see MaskImageFilter

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
see MinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter

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
see MinMaxCurvatureFlowFunction
see CurvatureFlowImageFilter
see BinaryMinMaxCurvatureFlowImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MirrorPadImageFilter.xml
%typemap(javaimports) itk::simple::MirrorPadImageFilter "/** Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, ConstantPadImageFilter

*/"
%javamethodmodifiers itk::simple::MirrorPadImageFilter::execute() "
/**Increase the image size by padding with replicants of the input image value.

*/"
%javamethodmodifiers itk::simple::MirrorPad "/**
Increase the image size by padding with replicants of the input image value.

 MirrorPadImageFilterchanges the image bounds of an image. Any added pixels are filled in with a mirrored replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the left boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see WrapPadImageFilter, ConstantPadImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MorphologicalGradientImageFilter.xml
%typemap(javaimports) itk::simple::MorphologicalGradientImageFilter "/** gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
%javamethodmodifiers itk::simple::MorphologicalGradientImageFilter::execute() "
/**gray scale dilation of an image

*/"
%javamethodmodifiers itk::simple::MorphologicalGradient "/**
gray scale dilation of an image

Dilate an image using grayscale morphology. Dilation takes the maximum of all the pixels identified by the structuring element.
The structuring element is assumed to be composed of binary values (zero or one). Only elements of the structuring element having values > 0 are candidates for affecting the center pixel.
see MorphologyImageFilter, GrayscaleFunctionDilateImageFilter, BinaryDilateImageFilter

*/"
// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1MultiplyByConstantImageFilter.xml
%typemap(javaimports) itk::simple::MultiplyByConstantImageFilter "/** Multiply input pixels by a constant.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter
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
see UnaryFunctorImageFilter
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
see GrayscaleMorphologicalOpeningImageFilter

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
see GrayscaleMorphologicalOpeningImageFilter

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
see OtsuThresholdImageCalculator
see BinaryThresholdImageFilter

li {Segmentation/OtsuThresholdImageFilter,Separate foreground and background using Otsu's method}

*/"
%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::execute() "
/**Threshold an image using the Otsu Threshold.

*/"
%javamethodmodifiers itk::simple::OtsuThreshold "/**
Threshold an image using the Otsu Threshold.

This filter creates a binary thresholded image that separates an image into foreground and background components. The filter computes the threshold using the OtsuThresholdImageCalculatorand applies that theshold to the input image using the BinaryThresholdImageFilter. The NunberOfHistogram bins can be set for the Calculator. The InsideValue and OutsideValue can be set for the BinaryThresholdImageFilter.
see OtsuThresholdImageCalculator
see BinaryThresholdImageFilter

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

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::setNumberOfHistogramBins "/**
virtual void itk::OtsuThresholdImageFilter::SetNumberOfHistogramBins(SizeValueType _arg)

Set/Get the number of histogram bins. Defaults is 128.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::getNumberOfHistogramBins "/**
virtual SizeValueType itk::OtsuThresholdImageFilter::GetNumberOfHistogramBins() const

*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::setOutsideValue "/**
virtual void itk::OtsuThresholdImageFilter::SetOutsideValue(OutputPixelType _arg)

Set the outside pixel value. The default value NumericTraits<OutputPixelType>::Zero.
*/"

%javamethodmodifiers itk::simple::OtsuThresholdImageFilter::getOutsideValue "/**
virtual OutputPixelType itk::OtsuThresholdImageFilter::GetOutsideValue() const

Get the outside pixel value.
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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RecursiveGaussianImageFilter.xml
%typemap(javaimports) itk::simple::RecursiveGaussianImageFilter "/** Base class for computing IIR convolution with an approximation of a Gaussian kernel.

 f[ frac{ 1 }{ sigma sqrt{ 2 pi } } exp{ left( - frac{x^2}{ 2 sigma^2 } right) } f]  
 RecursiveGaussianImageFilteris the base class for recursive filters that approximate convolution with the Gaussian kernel. This class implements the recursive filtering method proposed by R.Deriche in IEEE-PAMI Vol.12, No.1, January 1990, pp 78-87, Fast Algorithms for Low-Level Vision
Details of the implementation are described in the technical report: R. Deriche, Recursively Implementing The Gaussian and Its Derivatives, INRIA, 1993,ftp://ftp.inria.fr/INRIA/tech-reports/RR/RR-1893.ps.gz
Further improvements of the algorithm are described in: G. Farneback & C.-F. Westin, On Implementation of Recursive Gaussian Filters, so far unpublished.
As compared to itk::DiscreteGaussianImageFilter, this filter tends to be faster for large kernels, and it can take the derivative of the blurred image in one step. Also, note that we have itk::RecursiveGaussianImageFilter::SetSigma(), but itk::DiscreteGaussianImageFilter::SetVariance().
see DiscreteGaussianImageFilter
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
see DiscreteGaussianImageFilter
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

// Generated for ClassName from ../ITK-doxygen/Utilities/Doxygen/xml/classitk_1_1RescaleIntensityImageFilter.xml
%typemap(javaimports) itk::simple::RescaleIntensityImageFilter "/** Applies a linear transformation to the intensity levels of the input Image.

 RescaleIntensityImageFilterapplies pixel-wise a linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.
The following equation gives the mapping of the intensity values
par  f[ outputPixel = ( inputPixel - inputMin) cdot frac{(outputMax - outputMin )}{(inputMax - inputMin)} + outputMin f]  
All computations are performed in the precison of the input pixel's RealType. Before assigning the computed value to the output pixel.
NOTE: In this filter the minimum and maximum values of the input image are computed internally using the MinimumMaximumImageCalculator. Users are not supposed to set those values in this filter. If you need a filter where you can set the minimum and maximum values of the input, please use the IntensityWindowingImageFilter. If you want a filter that can use a user-defined linear transformation for the intensity, then please use the ShiftScaleImageFilter.
see IntensityWindowingImageFilter

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
see IntensityWindowingImageFilter

li {ImageProcessing/RescaleIntensityImageFilter,Rescale the intensity values of an image to a specified range}

*/"
%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::setOutputMaximum "/**
virtual void itk::RescaleIntensityImageFilter::SetOutputMaximum(OutputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::getOutputMaximum "/**
virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMaximum()

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::setOutputMinimum "/**
virtual void itk::RescaleIntensityImageFilter::SetOutputMinimum(OutputPixelType _arg)

*/"

%javamethodmodifiers itk::simple::RescaleIntensityImageFilter::getOutputMinimum "/**
virtual const OutputPixelType& itk::RescaleIntensityImageFilter::GetOutputMinimum()

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
see SegmentationLevelSetImageFilter
see ShapeDetectionLevelSetFunction
see SparseFieldLevelSetImageFilter

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
see SegmentationLevelSetImageFilter
see ShapeDetectionLevelSetFunction
see SparseFieldLevelSetImageFilter

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
see RecursiveGaussianImageFilter::SetNormalizeAcrossScale

*/"

%javamethodmodifiers itk::simple::SmoothingRecursiveGaussianImageFilter::getNormalizeAcrossScale "/**
virtual bool itk::SmoothingRecursiveGaussianImageFilter::GetNormalizeAcrossScale() const

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
see UnaryFunctorImageFilter

*/"
%javamethodmodifiers itk::simple::SubtractConstantFromImageFilter::execute() "
/**Subract a constant from all input pixels.

*/"
%javamethodmodifiers itk::simple::SubtractConstantFrom "/**
Subract a constant from all input pixels.

This filter is templated over the input image type and the output image type.
author Tom Vercauteren, INRIA & Mauna Kea Technologies
This implementation was taken from the Insight Journal paper:http://hdl.handle.net/1926/510
see UnaryFunctorImageFilter

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
see MirrorPadImageFilter, ConstantPadImageFilter

*/"
%javamethodmodifiers itk::simple::WrapPadImageFilter::execute() "
/**Increase the image size by padding with replicants of the input image value.

*/"
%javamethodmodifiers itk::simple::WrapPad "/**
Increase the image size by padding with replicants of the input image value.

 WrapPadImageFilterchanges the image bounds of an image. Added pixels are filled in with a wrapped replica of the input image. For instance, if the output image needs a pixel that istwo pixels to the left of the LargestPossibleRegionof the input image, the value assigned will be from the pixeltwo pixels inside the right boundary of the LargestPossibleRegion. The image bounds of the output must be specified.
Visual explanation of padding regions.This filter is implemented as a multithreaded filter. It provides a ThreadedGenerateData()method for its implementation.
see MirrorPadImageFilter, ConstantPadImageFilter

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
